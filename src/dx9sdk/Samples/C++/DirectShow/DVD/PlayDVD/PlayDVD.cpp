//------------------------------------------------------------------------------
// File: PlayDVD.cpp
//
// Desc: DirectShow sample code - a simple windowed DVD player application
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include "playdvd.h"

//
// Global data
//
HWND      ghApp=0;
HMENU     ghMenu=0, ghNavigateMenu=0, ghOptionsMenu=0, ghControlMenu=0; 
HMENU     ghTitleMenu=0, ghChapterMenu=0;
HMENU     ghAngleMenu=0, ghAudioMenu=0, ghPresentationMenu=0;
HMENU     ghSubpictureMenu=0, ghMenuLanguageMenu=0;
HINSTANCE ghInst=0;
BOOL      g_bFullscreen=FALSE;
LONG      g_lVolume=VOLUME_FULL;
DWORD     g_dwGraphRegister=0;
PLAYSTATE g_psCurrent=Stopped;
double    g_PlaybackRate=1.0;

// DirectShow core interfaces
IGraphBuilder   *pGB = NULL;
IMediaControl   *pMC = NULL;
IMediaEventEx   *pME = NULL;
IVideoWindow    *pVW = NULL;
IBasicAudio     *pBA = NULL;
IBasicVideo     *pBV = NULL;
IMediaSeeking   *pMS = NULL;
IMediaPosition  *pMP = NULL;
IVideoFrameStep *pFS = NULL;

// DVD interfaces
IDvdGraphBuilder *pDvdGB      = NULL;
IDvdControl2     *pDvdControl = NULL;
IDvdInfo2        *pDvdInfo    = NULL;
IAMLine21Decoder *pLine21Dec  = NULL;
LCID             *g_pLanguageList = NULL;

// Local function prototypes
LRESULT CALLBACK WndMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void HandleCommand(WPARAM wParam, LPARAM lParam);
void HandleChar(WPARAM wParam, LPARAM lParam);
void HandleDVDKey(WPARAM wParam, LPARAM lParam);
void HandleKeyUp(WPARAM wParam, LPARAM lParam);


HRESULT PlayDVDInWindow(void)
{
    HRESULT hr;

    // Clear main window before rendering the DVD volume
    UpdateWindow(ghApp);

    // Create an instance of the DVD Graph Builder object.
    hr = CoCreateInstance(CLSID_DvdGraphBuilder,
                         NULL,
                         CLSCTX_INPROC_SERVER,
                         IID_IDvdGraphBuilder,
                         reinterpret_cast<void**>(&pDvdGB));

    // Get a pointer to the filter graph manager.
    JIF(hr = pDvdGB->GetFiltergraph(&pGB));

    // Get the event interface before rendering the DVD volume so that
    // we won't miss DVD events.
    JIF(hr = pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME));

    // Build the DVD filter graph.
    hr = RenderDVD();
    if (FAILED(hr))
        return hr;

    // Get the pointers to the DVD Navigator interfaces.
    JIF(hr = pDvdGB->GetDvdInterface(IID_IDvdInfo2, reinterpret_cast<void**>(&pDvdInfo)));
    JIF(hr = pDvdGB->GetDvdInterface(IID_IDvdControl2, reinterpret_cast<void**>(&pDvdControl)));

    // Get the optional Line21 decoder interface, which may not be present
    hr = pDvdGB->GetDvdInterface(IID_IAMLine21Decoder, reinterpret_cast<void**>(&pLine21Dec));

    // Set default DVD playback options (parental control, captioning, etc.)
    SetDVDPlaybackOptions();

    // QueryInterface for DirectShow interfaces
    JIF(hr = pGB->QueryInterface(IID_IMediaControl, (void **)&pMC));
    JIF(hr = pGB->QueryInterface(IID_IMediaSeeking, (void **)&pMS));
    JIF(hr = pGB->QueryInterface(IID_IMediaPosition, (void **)&pMP));
    GetFrameStepInterface();

    // Query for audio/video interfaces
    JIF(hr = pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW));
    JIF(hr = pGB->QueryInterface(IID_IBasicVideo, (void **)&pBV));
    JIF(hr = pGB->QueryInterface(IID_IBasicAudio, (void **)&pBA));

    // Have the graph signal events via window messages
    JIF(hr = pME->SetNotifyWindow((OAHWND)ghApp, WM_GRAPHNOTIFY, 0));

    // Set message drain to application main window
    JIF(hr = pVW->put_MessageDrain((OAHWND) ghApp));

    // Initialize the main window properties
    JIF(hr = pVW->put_Owner((OAHWND)ghApp));
    JIF(hr = pVW->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN));
    JIF(InitVideoWindow(1, 1));

    // Complete window initialization
    CheckSizeMenu(ID_SIZE_NORMAL);
    ShowWindow(ghApp, SW_SHOWNORMAL);
    UpdateWindow(ghApp);
    SetForegroundWindow(ghApp);
    SetFocus(ghApp);

    g_bFullscreen = FALSE;
    g_PlaybackRate = 1.0;
    UpdateMainTitle();

#ifdef REGISTER_FILTERGRAPH
    hr = AddGraphToRot(pGB, &g_dwGraphRegister);
    if (FAILED(hr))
    {
        Msg(TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
        g_dwGraphRegister = 0;
    }
#endif

    // Run the graph to play the DVD
    JIF(pMC->Run());
    g_psCurrent=Running;

    return hr;
}


HRESULT RenderDVD(void)
{
    HRESULT hr;
    AM_DVD_RENDERSTATUS buildStatus={0};

    // Render the default DVD volume (on the DVD drive)
    hr = pDvdGB->RenderDvdVideoVolume(NULL, AM_DVD_HWDEC_PREFER, &buildStatus);

    // If there is no DVD decoder, give a user-friendly message
    if (hr == VFW_E_DVD_DECNOTENOUGH)
    {
        MessageBox(NULL, MSG_NO_DECODER, TEXT("Can't initialize PlayDVD sample!"), MB_OK);
        PostMessage(ghApp, WM_CLOSE, 0, 0L);
    }

    // Check for partial rendering success
    else if (S_FALSE == hr)
    {
        // Give information about which part of the render process failed
        TCHAR szStatusText[1000] ;
        if (0 == GetStatusText(&buildStatus, szStatusText, NUMELMS(szStatusText)))
        {
            lstrcpy(szStatusText, TEXT("An unknown error has occurred!\0")) ;
        }

        MessageBox(NULL, szStatusText, TEXT("Partial DVD render failure!"), MB_OK);
        return E_FAIL;
    }

    // Other failure
    else if (FAILED(hr))
    {
        TCHAR szBuffer[100];
        AMGetErrorText(hr, szBuffer, NUMELMS(szBuffer));
        MessageBox(NULL, szBuffer, TEXT("RenderDVD Failed!"), MB_OK);
    }

    return hr;
}


HRESULT InitVideoWindow(int nMultiplier, int nDivider)
{
    LONG lHeight, lWidth;
    HRESULT hr = S_OK;
    RECT rect;

    if (!pBV || !pVW)
        return S_OK;

    // Read the default video size
    hr = pBV->GetVideoSize(&lWidth, &lHeight);
    if (hr == E_NOINTERFACE)
        return S_OK;

    // Account for requests of normal, half, or double size
    lWidth  = lWidth  * nMultiplier / nDivider;
    lHeight = lHeight * nMultiplier / nDivider;

    int nTitleHeight  = GetSystemMetrics(SM_CYCAPTION);
    int nBorderWidth  = GetSystemMetrics(SM_CXBORDER);
    int nBorderHeight = GetSystemMetrics(SM_CYBORDER);

    // Account for size of title bar and borders for exact match
    // of window client area to default video size
    SetWindowPos(ghApp, NULL, 0, 0, lWidth + 2*nBorderWidth,
            lHeight + nTitleHeight + 2*nBorderHeight,
            SWP_NOMOVE | SWP_NOOWNERZORDER);

    GetClientRect(ghApp, &rect);
    JIF(pVW->SetWindowPosition(rect.left, rect.top, rect.right, rect.bottom));

    return hr;
}


HRESULT InitPlayerWindow(void)
{
    // Reset to a default size for audio and after closing a clip
    SetWindowPos(ghApp, NULL, 0, 0,
                 DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
                 SWP_NOMOVE | SWP_NOOWNERZORDER);

    // Check the 'full size' menu item
    CheckSizeMenu(ID_SIZE_NORMAL);
    EnablePlaybackMenu(FALSE);
    return S_OK;
}


void MoveVideoWindow(void)
{
    // Track the movement of the container window and resize as needed
    if(pVW)
    {
        HRESULT hr;
        RECT client;

        GetClientRect(ghApp, &client);
        hr = pVW->SetWindowPosition(client.left, client.top,
                                    client.right, client.bottom);
    }
}


void PauseDVD(void)
{
    if (!pMC)
        return;

    if (SUCCEEDED(pMC->Pause()))
    {
        g_psCurrent = Paused;
        UpdateMainTitle();
    }
}


void PlayDVD(void)
{
    if (!pMC)
        return;

    if((g_psCurrent == Paused) || (g_psCurrent == Stopped))
    {
        if (SUCCEEDED(pMC->Run()))
        {
            g_psCurrent = Running;
            EnableStopDomainMenus(TRUE);
        }

        if (true == g_bStillOn)     // We are at a still without buttons
        {
            if (SUCCEEDED(pDvdControl->StillOff()))
                g_bStillOn = false;
        }
    }

    UpdateMainTitle();
}


void StopDVD(void)
{
    if ((!pMC) || (!pMS))
        return;

    // Stop and reset position to beginning
    if((g_psCurrent == Paused) || (g_psCurrent == Running))
    {
        HRESULT hr;

        // Reset the nav, stop the filtergraph, then disable nav reset
        hr = pDvdControl->SetOption(DVD_ResetOnStop, TRUE); 
        hr = pMC->Stop();
        hr = pDvdControl->SetOption(DVD_ResetOnStop, FALSE); 

        g_psCurrent = Stopped;
        EnableStopDomainMenus(FALSE);
    }

    // Reset to normal playback speed
    ResetRate();
    UpdateMainTitle();
}


void OpenDVDVolume()
{
    HRESULT hr;

    // Initialize main window
    UpdateMainTitle();
    InitPlayerWindow();
    ShowWindow(ghApp, SW_SHOWNORMAL);
    SetForegroundWindow(ghApp);

    // Reset status variables
    g_psCurrent = Stopped;
    g_lVolume = VOLUME_FULL;
    g_PlaybackRate = 1.0;

    // Render the DVD volume and play video in the main window
    hr = PlayDVDInWindow();

    // If we couldn't play the DVD, clean up
    if (FAILED(hr))
        CloseDVDVolume();
}


void CloseDVDVolume()
{
    HRESULT hr;

    // Stop media playback
    if(pMC)
        hr = pMC->Stop();

    // Clear global flags
    g_psCurrent = Stopped;
    g_bFullscreen = FALSE;
    g_bDisplayCC = g_bDisplaySubpicture = 0;
    g_PlaybackRate = 1.0;

    // Free DirectShow interfaces
    CloseInterfaces();

    // Disable the playback menu and clear check boxes
    EnablePlaybackMenu(FALSE);

    // Clear the current time and title/chapter
    g_ulCurChapter = g_ulCurTitle = 0;
    ZeroMemory(&g_CurTime, sizeof(DVD_HMSF_TIMECODE));

    // No current media state
    g_psCurrent = Init;

    // Reset the player window
    RECT rect;
    GetClientRect(ghApp, &rect);
    InvalidateRect(ghApp, &rect, TRUE);

    UpdateMainTitle();
    InitPlayerWindow();
}


void CloseInterfaces(void)
{
    HRESULT hr;

    // Relinquish ownership (IMPORTANT!) after hiding video window
    if(pVW)
    {
        hr = pVW->put_Visible(OAFALSE);
        hr = pVW->put_Owner(NULL);
    }

    // Disable event callbacks
    if (pME)
        hr = pME->SetNotifyWindow((OAHWND)NULL, 0, 0);

#ifdef REGISTER_FILTERGRAPH
    if (g_dwGraphRegister)
    {
        RemoveGraphFromRot(g_dwGraphRegister);
        g_dwGraphRegister = 0;
    }
#endif

    // Release and zero DVD interfaces
    SAFE_RELEASE(pLine21Dec);
    SAFE_RELEASE(pDvdGB);
    SAFE_RELEASE(pDvdControl);
    SAFE_RELEASE(pDvdInfo);

    // Release and zero core DirectShow interfaces
    SAFE_RELEASE(pME);
    SAFE_RELEASE(pMS);
    SAFE_RELEASE(pMP);
    SAFE_RELEASE(pMC);
    SAFE_RELEASE(pBA);
    SAFE_RELEASE(pBV);
    SAFE_RELEASE(pVW);
    SAFE_RELEASE(pFS);
    SAFE_RELEASE(pGB);

    // Delete the allocated Menu Language LCID array
    delete[] g_pLanguageList;
}


void UpdateMainTitle(void)
{
    USES_CONVERSION;
    TCHAR szTitle[1000]={0}, szRate[20], szTimeChapter[64];
    char szPlaybackRate[16];

    // Inform user if fast forwarding or rewinding
    if (g_PlaybackRate == 1.0)
        szPlaybackRate[0] = '\0';
    else
        sprintf(szPlaybackRate, "(Rate:%2.2f)", g_PlaybackRate);

    _tcsncpy(szRate, A2T(szPlaybackRate), NUMELMS(szRate));

    // Format the current time if it's not zero.  Don't display timecode for anything
    // other than title playback (ie. not while displaying a menu).
    if ((g_DVDDomain == DVD_DOMAIN_Title) && 
       ((g_CurTime.bHours != 0) || (g_CurTime.bMinutes != 0) || (g_CurTime.bSeconds != 0)))
    {
        wsprintf(szTimeChapter, TEXT("[%d:%02d:%02d] [Title %d Chapter %d] \0"), 
                 g_CurTime.bHours, g_CurTime.bMinutes, g_CurTime.bSeconds, 
                 g_ulCurTitle, g_ulCurChapter);
    }
    else
        szTimeChapter[0] = 0;

    // Update the window title to show current play state
    wsprintf(szTitle, TEXT("%s %s%s%s%s\0\0"),
            APPLICATIONNAME,
            (g_lVolume == VOLUME_SILENCE) ? TEXT("(Muted)\0") : TEXT("\0"),
            (g_psCurrent == Paused) ? TEXT("(Paused)\0") : TEXT("\0"),
            szTimeChapter,
            szRate);

    SetWindowText(ghApp, szTitle);
}


HRESULT HandleGraphEvent(void)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

    // Make sure that we don't access the media event interface
    // after it has already been released.
    if (!pME)
        return S_OK;

    // Process all queued events
    while(SUCCEEDED(pME->GetEvent(&evCode, (LONG_PTR *) &evParam1,
                    (LONG_PTR *) &evParam2, 0)))
    {
        if (EC_DVD_DISC_EJECTED == evCode)
        {
            hr = pME->FreeEventParams(evCode, evParam1, evParam2);
            HandleDiscEject();
            break;      // Leave the while loop
        }
        else
            OnDvdEvent(evCode, evParam1, evParam2);

        // Free memory associated with callback
        hr = pME->FreeEventParams(evCode, evParam1, evParam2);
    }

    return hr;
}


void HandleCommand(WPARAM wParam, LPARAM lParam)
{
    // Menu commands
    switch(wParam)
    { 
        case ID_FILE_OPENDVD:
            // If we have ANY file open, close it and shut down DirectShow
            if (g_psCurrent != Init)
                CloseDVDVolume();

            // Open the new clip
            OpenDVDVolume();
            break;

        case ID_FILE_EXIT:
            CloseDVDVolume();
            PostQuitMessage(0);
            break;

        case ID_PAUSE:
            PauseDVD();
            break;

        case ID_PLAY:
            PlayDVD();
            break;

        case ID_STOP:
            StopDVD();
            break;

        case ID_FILE_CLOSE:
            CloseDVDVolume();
            break;

        case ID_MUTE:
            ToggleMute();
            break;

        case ID_HELP_ABOUT:
            DialogBox(ghInst, MAKEINTRESOURCE(IDD_ABOUTBOX),
                      ghApp,  (DLGPROC) AboutDlgProc);
            break;

        case ID_SIZE_HALF:
            InitVideoWindow(1,2);
            CheckSizeMenu(wParam);
            break;
        case ID_SIZE_NORMAL:
            InitVideoWindow(1,1);
            CheckSizeMenu(wParam);
            break;
        case ID_SIZE_DOUBLE:
            InitVideoWindow(2,1);
            CheckSizeMenu(wParam);
            break;
        case ID_SIZE_THREEQUARTER:
            InitVideoWindow(3,4);
            CheckSizeMenu(wParam);
            break;
        case ID_SIZE_FULLSCREEN:
            SetFullScreen();
            break;

        case ID_SINGLE_STEP:
            StepOneFrame();
            break;

        case ID_RATE_DECREASE:     // Reduce playback speed
            ModifyRate(-0.5);
            break;
        case ID_RATE_INCREASE:     // Increase playback speed
            ModifyRate(0.5);
            break;

        case ID_RATE_NORMAL:       // Set playback speed to normal
            SetRate(1.0);
            break;
        case ID_RATE_HALF:         // Set playback speed to 1/2 normal
            SetRate(0.5);
            break;
        case ID_RATE_QUAD:         // Set playback speed to 4x normal
            SetRate(4.0);
            break;
        case ID_RATE_FAST:         // Set playback speed to 8x normal
            SetRate(8.0);
            break;
        case ID_RATE_MAX:          // Set playback speed to 16x normal
            SetRate(16.0);
            break;
        case ID_RATE_QUAD_BACK:
            SetRate(-4.0);
            break;
        case ID_RATE_FAST_BACK:
            SetRate(-8.0);
            break;
        case ID_RATE_MAX_BACK:
            SetRate(-16.0);
            break;

        // DVD-specific control commands
        case ID_DVD_SHOWSUBPICTURE:
        case ID_DVD_SHOWCC:
        case ID_DVD_NEXTCHAPTER:
        case ID_DVD_PREVIOUSCHAPTER:
        case ID_DVD_REPLAYCHAPTER:
        case ID_DVD_STARTMOVIE:
        case ID_MENU_ROOT:
        case ID_MENU_TITLE:
        case ID_MENU_RESUME:
            HandleDVDCommand(wParam, lParam);
            break;

        default:
            CheckSubmenuMessage(wParam, lParam);
            break;        

    } // Menus
}


void CheckSubmenuMessage(WPARAM wParam, LPARAM lParam)
{
    // Check for subpicture stream control messages
    if (wParam >= ID_DVD_SUBPICTURE_BASE && wParam <= ID_DVD_SUBPICTURE_MAX)
    {
        // Set the subpicture stream based on the dynamically created menu
        SetSubpictureStream((int) (wParam - ID_DVD_SUBPICTURE_BASE));
        return;
    }

    else if (wParam >= ID_DVD_AUDIO_BASE && wParam <= ID_DVD_AUDIO_MAX)
    {
        // Set the audio stream based on the dynamically created menu
        SetAudioStream((int) (wParam - ID_DVD_AUDIO_BASE));
        return;
    }

    else if (wParam >= ID_DVD_ANGLE_BASE && wParam <= ID_DVD_ANGLE_MAX)
    {
        // Set the angle based on the dynamically created menu
        SetAngle((int) (wParam - ID_DVD_ANGLE_BASE));
        return;
    }

    else if (wParam >= ID_DVD_TITLE_BASE && wParam <= ID_DVD_TITLE_MAX)
    {
        // Set the title based on the dynamically created menu
        SetTitle((int) (wParam - ID_DVD_TITLE_BASE));
        return;
    }

    else if (wParam >= ID_DVD_CHAPTER_BASE && wParam <= ID_DVD_CHAPTER_MAX)
    {
        // Set the chapter based on the dynamically created menu
        SetChapter((int) (wParam - ID_DVD_CHAPTER_BASE));
        return;
    }

    else if (wParam >= ID_DVD_MENULANG_BASE && wParam <= ID_DVD_MENULANG_MAX)
    {
        // Set the angle based on the dynamically created menu
        SetMenuLanguage((int) (wParam - ID_DVD_MENULANG_BASE));
        return;
    }

    // Otherwise, process the specific presentation mode requests
    switch (wParam)
    {
        case ID_DVD_PRESENTATION_DEFAULT:
        case ID_DVD_16x9:
        case ID_DVD_PANSCAN:
        case ID_DVD_LETTERBOX:
            SetPresentationMode((int) (wParam - ID_DVD_PRESENTATION_DEFAULT));
            break;
    }
}


void HandleChar(WPARAM wParam, LPARAM lParam)
{
    int nKey = (int) wParam;
    if (isalpha(nKey))
        nKey = toupper(nKey);

    switch(nKey)
    {
        case 'P':
            PauseDVD();
            break;
        case 'L':
            PlayDVD();
            break;
        case 'S':
            StopDVD();
            break;
        case 'M':
            ToggleMute();
            break;

        case 'N':
            PostMessage(ghApp, WM_COMMAND, ID_DVD_NEXTCHAPTER, 0);
            break;
        case 'B':
            PostMessage(ghApp, WM_COMMAND, ID_DVD_PREVIOUSCHAPTER, 0);
            break;
        case 'R':
            PostMessage(ghApp, WM_COMMAND, ID_DVD_REPLAYCHAPTER, 0);
            break;

        case 'G':
            PostMessage(ghApp, WM_COMMAND, ID_DVD_STARTMOVIE, 0);
            break;
        case 'T':
            PostMessage(ghApp, WM_COMMAND, ID_MENU_TITLE, 0);
            break;
        case 'O':
            PostMessage(ghApp, WM_COMMAND, ID_MENU_ROOT, 0);
            break;

        case 'F':
            SetFullScreen();
            break;

        case '1':           // Set playback speed to normal
            SetRate(1.0);
            break;
    }
}


void HandleKeyUp(WPARAM wParam, LPARAM lParam)
{
    switch(wParam)
    {
        case VK_ADD:
            ModifyRate(0.5);
            break;

        case VK_SUBTRACT:
            ModifyRate(-0.5);
            break;

        case VK_BACK:
            SetRate(1.0);
            break;

        case VK_DIVIDE:
            SetRate(0.5);
            break;

        case VK_RETURN: // activate the currently selected button
        case VK_LEFT:   // select the left button
        case VK_RIGHT:  // select the right button
        case VK_UP:     // select the upper button
        case VK_DOWN:   // select the lower button
            HandleDVDKey(wParam, lParam);
            break;

        case VK_F12:
            CloseDVDVolume();
            break;

        // Frame stepping
        case VK_SPACE:
            StepOneFrame();
            break;

        case VK_ESCAPE:
            if (g_bFullscreen)
                ClearFullScreen();
            break;
    }
}


void HandleDVDKey(WPARAM wParam, LPARAM lParam)
{
    HRESULT hr;
    if (!pDvdControl)
        return;

    if (!g_bMenuOn)
        return;

    switch(wParam)
    {
        case VK_RETURN: // activate the currently selected button
            hr = pDvdControl->ActivateButton();
            break;

        case VK_LEFT: // select the left button
            hr = pDvdControl->SelectRelativeButton(DVD_Relative_Left);
            break;

        case VK_RIGHT: // select the right button
            hr = pDvdControl->SelectRelativeButton(DVD_Relative_Right);
            break;

        case VK_UP: // select the upper button
            hr = pDvdControl->SelectRelativeButton(DVD_Relative_Upper);
            break;

        case VK_DOWN: // select the lower button
            hr = pDvdControl->SelectRelativeButton(DVD_Relative_Lower);
            break;
    }
}


LRESULT CALLBACK WndMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        // Resize the video when the window changes
        case WM_MOVE:
        case WM_SIZE:
            if (hWnd == ghApp)
                MoveVideoWindow();
            break;

        // Enforce a minimum size
        case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO lpmm = (LPMINMAXINFO) lParam;
                lpmm->ptMinTrackSize.x = MINIMUM_VIDEO_WIDTH;
                lpmm->ptMinTrackSize.y = MINIMUM_VIDEO_HEIGHT;
            }
            break;

        case WM_MOUSEMOVE:      // DVD menu-related mouse movements
        case WM_LBUTTONUP:
            OnMouseEvent(message, wParam, lParam);
            break;

        case WM_INITMENUPOPUP:
            if ((HMENU) wParam == ghChapterMenu)
            {
                // Since the current chapter can change at any time
                // due to navigation, DVD authoring, etc., dynamically
                // create the chapter menu items before displaying it.
                ConfigureChapterMenu();
                return 0;
            }
            break;

        case WM_KEYUP:
            HandleKeyUp(wParam, lParam);
            break;

        case WM_CHAR:
            HandleChar(wParam, lParam);
            break;

        case WM_COMMAND:        // Menu commands
            HandleCommand(wParam, lParam);
            break;

        case WM_GRAPHNOTIFY:    // DirectShow graph notification
            HandleGraphEvent();
            break;

        case WM_CLOSE:
            SendMessage(ghApp, WM_COMMAND, ID_FILE_EXIT, 0);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);

    } // Window messages handling

    // Pass this message to the video window for notification of system changes
    if (pVW)
        pVW->NotifyOwnerMessage((LONG_PTR) hWnd, message, wParam, lParam);

    return DefWindowProc(hWnd, message, wParam, lParam);
}


int PASCAL WinMain(HINSTANCE hInstC, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg={0};
    WNDCLASS wc;
    USES_CONVERSION;

    // Initialize COM
    if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        Msg(TEXT("CoInitialize Failed!\r\n"));
        exit(1);
    }

    // Set initial media state
    g_psCurrent = Init;

    // Register the window class
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc = WndMainProc;
    ghInst = wc.hInstance = hInstC;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(hInstC, MAKEINTRESOURCE(IDI_PLAYDVD));
    if(!RegisterClass(&wc))
    {
        Msg(TEXT("RegisterClass Failed! Error=0x%x\r\n"), GetLastError());
        CoUninitialize();
        exit(1);
    }

    // Create the main window.  The WS_CLIPCHILDREN style is required.
    ghApp = CreateWindow(CLASSNAME, APPLICATIONNAME,
                         WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         0, 0, ghInst, 0);

    if(ghApp)
    {
        GetMenuHandles();
        InitPlayerWindow();
        ShowWindow(ghApp, SW_SHOWNORMAL);

        // Main message loop
        while(GetMessage(&msg,NULL,0,0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    else
    {
        Msg(TEXT("Failed to create the main window! Error=0x%x\r\n"), GetLastError());
    }

    // Finished with COM
    CoUninitialize();

    return (int) msg.wParam;
}




