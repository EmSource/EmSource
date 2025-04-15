//------------------------------------------------------------------------------
// File: VMRPip.cpp
//
// Desc: DirectShow sample code - video blending application for large 
//       primary stream and smaller subpicture stream.  User can manipulate
//       size and position of subpicture, along with swapping streams.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <dshow.h>
#include <tchar.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <atlbase.h>

#include "vmrpip.h"
#include "blend.h"
#include "vmrutil.h"

// An application can advertise the existence of its filter graph
// by registering the graph with a global Running Object Table (ROT).
// The GraphEdit application can detect and remotely view the running
// filter graph, allowing you to 'spy' on the graph with GraphEdit.
//
// To enable registration in this sample, define REGISTER_FILTERGRAPH.
//
#define REGISTER_FILTERGRAPH

//
// Global data
//
HWND      ghApp=0;
HMENU     ghMenu=0;
HINSTANCE ghInst=0;
DWORD     g_dwGraphRegister=0;
RECT      g_rcDest={0};
BOOL      g_bFilesSelected=FALSE;

// DirectShow interfaces
IGraphBuilder *pGB = NULL;
IMediaControl *pMC = NULL;
IMediaEventEx *pME = NULL;
IMediaSeeking *pMS = NULL;

IVMRWindowlessControl9 *pWC = NULL;
IVMRMixerControl9 *pMix = NULL;

// Video stream filenames
TCHAR g_szFile1[MAX_PATH]={0}, g_szFile2[MAX_PATH]={0};


HRESULT ConfigureMultiFileVMR9(WCHAR *wFile1, WCHAR *wFile2)
{
    HRESULT hr=S_OK;
    CComPtr <IBaseFilter> pVmr;

    // Create the Video Mixing Renderer and add it to the graph
    JIF(InitializeWindowlessVMR(&pVmr));
            
    // Render the files programmatically to use the VMR9 as renderer
    if (SUCCEEDED(hr = RenderFileToVMR9(pGB, wFile1, pVmr)))
        hr = RenderFileToVMR9(pGB, wFile2, pVmr);

    return hr;
}


HRESULT BlendVideo(LPTSTR szFile1, LPTSTR szFile2)
{
    USES_CONVERSION;
    WCHAR wFile1[MAX_PATH], wFile2[MAX_PATH];
    HRESULT hr;

    // Check input string
    if ((szFile1 == NULL) || (szFile2 == NULL))
        return E_POINTER;

    // Clear open dialog remnants before calling RenderFile()
    UpdateWindow(ghApp);

    // Convert filenames to wide character strings
    wcsncpy(wFile1, T2W(szFile1), NUMELMS(wFile1)-1);
    wcsncpy(wFile2, T2W(szFile2), NUMELMS(wFile2)-1);
    wFile1[MAX_PATH-1] = wFile2[MAX_PATH-1] = 0;

    // Get the interface for DirectShow's GraphBuilder
    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                         IID_IGraphBuilder, (void **)&pGB));

    if(SUCCEEDED(hr))
    {
        // Unlike the VMR7 in Windows XP, the VMR9 is not the default renderer
        // (to preserve backward compatibility).  In some multifile graphs,
        // the filter graph manager could decide to load the default Video Renderer
        // filter during RenderFile(), even though the VMR9 is already present
        // in the graph.  Since the default Video Renderer has a higher merit 
        // than the VMR9, it would be connected instead of the VMR9, leading to
        // the video streams being displayed in multiple separate windows.
        // This could be the case with AVI files created with legacy VfW codecs
        // or when two Color Space convertors must be used (each requiring its
        // own allocator).
        // Therefore, we render the files programmatically instead of using
        // the standard IGraphBuilder::RenderFile() method.
        if (FAILED(ConfigureMultiFileVMR9(wFile1, wFile2)))
            return hr;

        // QueryInterface for DirectShow interfaces
        JIF(pGB->QueryInterface(IID_IMediaControl, (void **)&pMC));
        JIF(pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME));
        JIF(pGB->QueryInterface(IID_IMediaSeeking, (void **)&pMS));

        // Is this an audio-only file (no video component)?
        if (CheckVideoVisibility())
        {
            JIF(InitVideoWindow(1, 1));
        }
        else
        {
            // This sample requires video clips to be loaded
            Msg(TEXT("This sample requires media with a video component.  ")
                TEXT("Please select another file."));
            return E_FAIL;
        }

        // Have the graph signal event via window callbacks
        JIF(pME->SetNotifyWindow((OAHWND)ghApp, WM_GRAPHNOTIFY, 0));

        // Complete the window setup
        ShowWindow(ghApp, SW_SHOWNORMAL);
        UpdateWindow(ghApp);
        SetForegroundWindow(ghApp);
        SetFocus(ghApp);

#ifdef REGISTER_FILTERGRAPH
        if (FAILED(AddGraphToRot(pGB, &g_dwGraphRegister)))
        {
            Msg(TEXT("Failed to register filter graph with ROT!"));
            g_dwGraphRegister = 0;
        }
#endif

        // Run the graph to play the media files
        MoveVideoWindow();
        JIF(pMC->Run());
        
        EnableMenus(TRUE);      
    }

    return hr;
}

HRESULT InitVideoWindow(int nMultiplier, int nDivider)
{
    LONG lHeight, lWidth;
    HRESULT hr = S_OK;

    if (!pWC)
        return S_OK;

    // Read the default video size
    hr = pWC->GetNativeVideoSize(&lWidth, &lHeight, NULL, NULL);
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

    GetClientRect(ghApp, &g_rcDest);
    hr = pWC->SetVideoPosition(NULL, &g_rcDest);

    return hr;
}

HRESULT InitPlayerWindow(void)
{
    // Reset to a default size for audio and after closing a clip
    SetWindowPos(ghApp, NULL, 0, 0,
                 DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT,
                 SWP_NOMOVE | SWP_NOOWNERZORDER);
    return S_OK;
}

void MoveVideoWindow(void)
{
    HRESULT hr;

    // Track the movement of the container window and resize as needed
    if(pWC)
    {
        GetClientRect(ghApp, &g_rcDest);
        hr = pWC->SetVideoPosition(NULL, &g_rcDest);
    }
}

BOOL CheckVideoVisibility(void)
{
    HRESULT hr;
    LONG lWidth=0, lHeight=0;

    //
    // Because this sample explicitly loads the VMR9 into the filter graph
    // before rendering a file, the IVMRWindowlessControl interface will exist
    // for all properly rendered files.  As a result, we can't depend on the
    // existence of the pWC interface to determine whether the media file has
    // a video component.  Instead, check the width and height values.
    //
    if (!pWC)
    {
        // Audio-only files have no video interfaces.  This might also
        // be a file whose video component uses an unknown video codec.
        return FALSE;
    }

    hr = pWC->GetNativeVideoSize(&lWidth, &lHeight, 0, 0);
    if (FAILED(hr))
    {
        // If this video is encoded with an unsupported codec,
        // we won't see any video, although the audio will work if it is
        // of a supported format.
        return FALSE;
    }

    // If this is an audio-only clip, width and height will be 0.
    if ((lWidth == 0) && (lHeight == 0))
        return FALSE;

    // Assume that this media file contains a video component
    return TRUE;
}

BOOL GetClipFileName(LPTSTR szName)
{
    static OPENFILENAME ofn={0};
    static BOOL bSetInitialDir = FALSE;

    // Reset filename
    *szName = 0;

    // Fill in standard structure fields
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = ghApp;
    ofn.lpstrFilter       = FILE_FILTER_TEXT;
    ofn.lpstrCustomFilter = NULL;
    ofn.nFilterIndex      = 1;
    ofn.lpstrFile         = szName;
    ofn.nMaxFile          = MAX_PATH;
    ofn.lpstrTitle        = TEXT("Open Video File...\0");
    ofn.lpstrFileTitle    = NULL;
    ofn.lpstrDefExt       = TEXT("*\0");
    ofn.Flags             = OFN_FILEMUSTEXIST | OFN_READONLY;

    // Remember the path of the first selected file
    if (bSetInitialDir == FALSE)
    {
        ofn.lpstrInitialDir = DEFAULT_MEDIA_PATH;
        bSetInitialDir = TRUE;
    }
    else
        ofn.lpstrInitialDir = NULL;

    // Create the standard file open dialog and return its result
    return GetOpenFileName((LPOPENFILENAME)&ofn);
}

void EnableMenus(BOOL bEnable)
{
    int nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION;

    EnableMenuItem(ghMenu, 1, nState);      // Subpicture menu
    EnableMenuItem(ghMenu, 2, nState);      // Effects menu
    DrawMenuBar(ghApp);    
}

void OpenFiles(void)
{
    HRESULT hr;

    // Display a custom file selection dialog to get both filenames
    DialogBox(ghInst, MAKEINTRESOURCE(IDD_DIALOG_FILES),
              ghApp,  (DLGPROC) FilesDlgProc);

    // If user clicked OK, then open the files
    if (g_bFilesSelected)
    {
        g_bFilesSelected = FALSE;

        // Initialize the global strParam structure with default values
        InitStreamParams();

        // Initialize DirectShow, render the files, and play the streams
        hr = BlendVideo(g_szFile1, g_szFile2);

        // If we couldn't play the streams, clean up
        if (FAILED(hr))
        {
            CloseFiles();
            return;
        }

        // Set video position, size, and alpha values
        UpdatePinPos(0);
        UpdatePinPos(1);
        UpdatePinAlpha(0);
        UpdatePinAlpha(1);
    }
}

void CloseFiles()
{
    HRESULT hr;

    // Stop any running timer
    StopTimer();

    // Stop media playback
    if(pMC)
        hr = pMC->Stop();

    // Free DirectShow interfaces
    CloseInterfaces();
    EnableMenus(FALSE);

    // Reset the player window
    RECT rect;
    GetClientRect(ghApp, &rect);
    InvalidateRect(ghApp, &rect, TRUE);

    InitPlayerWindow();
}

void CloseInterfaces(void)
{
    // Disable event callbacks
    if (pME)
        pME->SetNotifyWindow((OAHWND)NULL, 0, 0);

#ifdef REGISTER_FILTERGRAPH
    if (g_dwGraphRegister)
    {
        RemoveGraphFromRot(g_dwGraphRegister);
        g_dwGraphRegister = 0;
    }
#endif

    // Release and zero DirectShow interfaces
    SAFE_RELEASE(pME);
    SAFE_RELEASE(pMS);
    SAFE_RELEASE(pMC);
    SAFE_RELEASE(pWC);
    SAFE_RELEASE(pMix);
    SAFE_RELEASE(pGB);
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
        // Free memory associated with callback, since we're not using it
        hr = pME->FreeEventParams(evCode, evParam1, evParam2);

        // If this is the end of the clip, reset to beginning
        if(EC_COMPLETE == evCode)
        {
            LONGLONG pos=0;

            // If seeking failed, just stop and restart playback
            hr = pMC->Stop();

            // Wait for the state to propagate to all filters
            OAFilterState fs;
            hr = pMC->GetState(500, &fs);

            // Reset to first frame of movie
            hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                   NULL, AM_SEEKING_NoPositioning);
            hr = pMC->Run();
        }
    }

    return hr;
}

#ifdef REGISTER_FILTERGRAPH

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
    IMoniker * pMoniker;
    IRunningObjectTable *pROT;
    if (FAILED(GetRunningObjectTable(0, &pROT))) 
    {
        return E_FAIL;
    }

    WCHAR wsz[128];
    wsprintfW(wsz, L"FilterGraph %08x pid %08x", (DWORD_PTR)pUnkGraph, 
              GetCurrentProcessId());

    HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
    if (SUCCEEDED(hr)) 
    {
        // Use the ROTFLAGS_REGISTRATIONKEEPSALIVE to ensure a strong reference
        // to the object.  Using this flag will cause the object to remain
        // registered until it is explicitly revoked with the Revoke() method.
        //
        // Not using this flag means that if GraphEdit remotely connects
        // to this graph and then GraphEdit exits, this object registration 
        // will be deleted, causing future attempts by GraphEdit to fail until
        // this application is restarted or until the graph is registered again.
        hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, 
                            pMoniker, pdwRegister);
        pMoniker->Release();
    }

    pROT->Release();
    return hr;
}

void RemoveGraphFromRot(DWORD pdwRegister)
{
    IRunningObjectTable *pROT;

    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) 
    {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
}

#endif

void Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    // Display a message box with the formatted string
    MessageBox(NULL, szBuffer, TEXT("VMR PIP Sample"), MB_OK);
}

LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            if (wParam == IDOK)
            {
                EndDialog(hWnd, TRUE);
                return TRUE;
            }
            break;
    }
    return FALSE;
}

LRESULT CALLBACK FilesDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR szFile[MAX_PATH]={0};

    switch (message)
    {
        case WM_INITDIALOG:
            SetDlgItemText(hWnd, IDC_EDIT_FILE1, g_szFile1);
            SetDlgItemText(hWnd, IDC_EDIT_FILE2, g_szFile2);
            return TRUE;

        case WM_COMMAND:
            switch (wParam)
            {
                case IDCANCEL:
                    g_bFilesSelected = FALSE;
                    EndDialog(hWnd, TRUE);
                    break;

                case IDOK:
                    GetDlgItemText(hWnd, IDC_EDIT_FILE1, g_szFile1, MAX_PATH);
                    GetDlgItemText(hWnd, IDC_EDIT_FILE2, g_szFile2, MAX_PATH);

                    if ((g_szFile1[0] == 0) || (g_szFile2[0] == 0))
                    {
                        Msg(TEXT("Please provide two valid media filenames."));
                    }
                    else
                    {
                        g_bFilesSelected = TRUE;
                        EndDialog(hWnd, TRUE);
                    }
                    break;

                case IDC_BUTTON_FILE1:
                    if (GetClipFileName(szFile))
                        SetDlgItemText(hWnd, IDC_EDIT_FILE1, szFile);
                    break;

                case IDC_BUTTON_FILE2:
                    if (GetClipFileName(szFile))
                        SetDlgItemText(hWnd, IDC_EDIT_FILE2, szFile);
                    break;
            }
            break;
    }

    return FALSE;
}

LRESULT CALLBACK WndMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_PAINT:
            OnPaint(hWnd);
            break;

        case WM_DISPLAYCHANGE:
            if (pWC)
                pWC->DisplayModeChanged();
            break;
        
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

        case WM_KEYDOWN:

            switch(wParam)
            {
                case VK_ESCAPE:
                    CloseFiles();
                    break;

                case VK_SPACE:
                    SetNextQuadrant(g_nSubpictureID);
                    break;

                case VK_F1:
                case VK_F2:
                case VK_F3:
                case VK_F4:
                    PositionStream(g_nSubpictureID, (int) (wParam - VK_F1));
                    break;

                case VK_F5:
                    CenterStream(g_nSubpictureID);
                    break;

                case VK_UP:
                    AdjustVideo(g_nSubpictureID, 0, -MOVEVAL, 0, 0);
                    break;
                case VK_DOWN:
                    AdjustVideo(g_nSubpictureID, 0, MOVEVAL, 0, 0);
                    break;
                case VK_LEFT:
                    AdjustVideo(g_nSubpictureID, -MOVEVAL, 0, 0, 0);
                    break;
                case VK_RIGHT:
                    AdjustVideo(g_nSubpictureID, MOVEVAL, 0, 0, 0);
                    break;

                case VK_ADD:
                case VK_F7:
                    AdjustVideo(g_nSubpictureID, 0, 0, MOVEVAL, MOVEVAL);
                    break;

                case VK_SUBTRACT:
                case VK_F6:
                    AdjustVideo(g_nSubpictureID, 0, 0, -MOVEVAL, -MOVEVAL);
                    break;

                case VK_F8:
                    PostMessage(ghApp, WM_COMMAND, IDM_MIRROR_PRIMARY, 0L);
                    break;
                case VK_F9:
                    PostMessage(ghApp, WM_COMMAND, IDM_MIRROR_SECONDARY, 0L);
                    break;
                case VK_F11:
                    PostMessage(ghApp, WM_COMMAND, IDM_FLIP_PRIMARY, 0L);
                    break;
                case VK_F12:
                    PostMessage(ghApp, WM_COMMAND, IDM_FLIP_SECONDARY, 0L);
                    break;

                case VK_RETURN:
                    SwapStreams();
                    break;
                case VK_BACK:
                    StartSwapAnimation();
                    break;
            }
            break;

        case WM_COMMAND:

            switch(wParam)
            {
                case ID_FILE_OPENCLIPS:
                    CloseFiles();
                    OpenFiles();
                    break;

                case ID_FILE_EXIT:
                    CloseFiles();
                    PostQuitMessage(0);
                    break;

                case ID_FILE_CLOSE:
                    CloseFiles();
                    break;

                case IDM_TOPLEFT:
                case IDM_TOPRIGHT:
                case IDM_BOTTOMLEFT:
                case IDM_BOTTOMRIGHT:
                    PositionStream(g_nSubpictureID, (int) (wParam - IDM_TOPLEFT));
                    break;

                case IDM_LARGER:
                    AdjustVideo(g_nSubpictureID, 0, 0, MOVEVAL, MOVEVAL);
                    break;
                case IDM_SMALLER:
                    AdjustVideo(g_nSubpictureID, 0, 0, -MOVEVAL, -MOVEVAL);
                    break;

                case IDM_NEXTQUADRANT:
                    SetNextQuadrant(g_nSubpictureID);
                    break;
                case IDM_CENTER:
                    CenterStream(g_nSubpictureID);
                    break;

                case IDM_MIRROR_PRIMARY:
                    MirrorStream(PRIMARY_STREAM);
                    CheckMenuItem(ghMenu, IDM_MIRROR_PRIMARY, 
                                  strParam[0].bMirrored ? MF_CHECKED : MF_UNCHECKED);
                    break;
                case IDM_MIRROR_SECONDARY:
                    MirrorStream(SECONDARY_STREAM);
                    CheckMenuItem(ghMenu, IDM_MIRROR_SECONDARY, 
                                  strParam[1].bMirrored ? MF_CHECKED : MF_UNCHECKED);
                    break;

                case IDM_FLIP_PRIMARY:
                    FlipStream(PRIMARY_STREAM);
                    CheckMenuItem(ghMenu, IDM_FLIP_PRIMARY, strParam[0].bFlipped ?
                                  MF_CHECKED : MF_UNCHECKED);
                    break;
                case IDM_FLIP_SECONDARY:
                    FlipStream(SECONDARY_STREAM);
                    CheckMenuItem(ghMenu, IDM_FLIP_SECONDARY, strParam[1].bFlipped ?
                                  MF_CHECKED : MF_UNCHECKED);
                    break;

                case IDM_SWAP:
                    SwapStreams();
                    break;
                case IDM_SWAP_ANIMATE:
                    StartSwapAnimation();
                    break;

                case ID_HELP_ABOUT:
                    DialogBox(ghInst, MAKEINTRESOURCE(IDD_HELP_ABOUT),
                              ghApp,  (DLGPROC) AboutDlgProc);
                    break;
            }
            break;


        case WM_GRAPHNOTIFY:
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

    return DefWindowProc(hWnd, message, wParam, lParam);
}


HRESULT InitializeWindowlessVMR(IBaseFilter **ppVmr9)
{
    IBaseFilter *pVmr=NULL;

    if (!ppVmr9)
        return E_POINTER;
    *ppVmr9 = NULL;

    // Create the VMR and add it to the filter graph.
    HRESULT hr = CoCreateInstance(CLSID_VideoMixingRenderer9, NULL,
                                  CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr);

    if (SUCCEEDED(hr)) 
    {
        hr = pGB->AddFilter(pVmr, L"Video Mixing Renderer 9");
        if (SUCCEEDED(hr)) 
        {
            // Set the rendering mode and number of streams
            CComPtr <IVMRFilterConfig9> pConfig;

            JIF(pVmr->QueryInterface(IID_IVMRFilterConfig9, (void**)&pConfig));
            JIF(pConfig->SetRenderingMode(VMR9Mode_Windowless));
            JIF(pConfig->SetNumberOfStreams(2));

            // Set the bounding window and border for the video
            JIF(pVmr->QueryInterface(IID_IVMRWindowlessControl9, (void**)&pWC));
            JIF(pWC->SetVideoClippingWindow(ghApp));
            JIF(pWC->SetBorderColor(RGB(0,0,0)));    // Black border

            // Get the mixer control interface for later manipulation of video 
            // stream output rectangles and alpha values
            JIF(pVmr->QueryInterface(IID_IVMRMixerControl9, (void**)&pMix));
        }

        // Don't release the pVmr interface because we are copying it into
        // the caller's ppVmr9 pointer
        *ppVmr9 = pVmr;
    }

    return hr;
}

void OnPaint(HWND hwnd) 
{
    HRESULT hr;
    PAINTSTRUCT ps; 
    HDC         hdc; 
    RECT        rcClient; 

    GetClientRect(hwnd, &rcClient); 
    hdc = BeginPaint(hwnd, &ps); 

    if(pWC) 
    { 
        // When using VMR Windowless mode, you must explicitly tell the
        // renderer when to repaint the video in response to WM_PAINT
        // messages.  This is most important when the video is stopped
        // or paused, since the VMR won't be automatically updating the
        // window as the video plays.
        hr = pWC->RepaintVideo(hwnd, hdc);  
    } 
    else  // No video image. Just paint the whole client area. 
    { 
        FillRect(hdc, &rcClient, (HBRUSH)(COLOR_BTNFACE + 1)); 
    } 

    EndPaint(hwnd, &ps); 
} 


int PASCAL WinMain(HINSTANCE hInstC, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg={0};
    WNDCLASS wc;

    // Initialize COM
    if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        Msg(TEXT("CoInitialize Failed!\r\n"));
        return FALSE;
    }

    // Verify that the VMR is present on this system
    if(!VerifyVMR9())
        return FALSE;

    // Register the window class
    ZeroMemory(&wc, sizeof wc);
    ghInst = wc.hInstance = hInstC;
    wc.lpfnWndProc   = WndMainProc;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(hInstC, MAKEINTRESOURCE(IDI_SAMPLE));
    if(!RegisterClass(&wc))
    {
        Msg(TEXT("RegisterClass Failed! Error=0x%x\r\n"), GetLastError());
        CoUninitialize();
        exit(1);
    }

    // Create the main window
    ghApp = CreateWindow(CLASSNAME, APPLICATIONNAME,
                         WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN | WS_VISIBLE,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT,
                         0, 0, ghInst, 0);

    if(ghApp)
    {
        // Save menu handle for later use
        ghMenu = GetMenu(ghApp);
        EnableMenus(FALSE);

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


