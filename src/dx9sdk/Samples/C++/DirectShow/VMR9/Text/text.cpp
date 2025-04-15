//------------------------------------------------------------------------------
// File: Text.cpp
//
// Desc: DirectShow sample code - a simple text-over-video app
//       Using the DirectX 9 Video Mixing Renderer, a generated bitmap
//       containing app-specified text is blended with a running video.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <dshow.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <tchar.h>
#include <atlbase.h>

#include "text.h"
#include "bitmap.h"
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
TCHAR     g_szFileName[MAX_PATH]={0};
DWORD     g_dwGraphRegister=0;
RECT      g_rcDest={0};

// DirectShow interfaces
IGraphBuilder *pGB = NULL;
IMediaControl *pMC = NULL;
IMediaEventEx *pME = NULL;
IMediaSeeking *pMS = NULL;
IVMRWindowlessControl9 *pWC = NULL;


HRESULT PlayMovieInWindow(LPTSTR szFile)
{
    USES_CONVERSION;
    WCHAR wFile[MAX_PATH];
    HRESULT hr;

    // Check input string
    if (szFile == NULL)
        return E_POINTER;

    // Clear open dialog remnants before calling RenderFile()
    UpdateWindow(ghApp);

    // Convert filename to wide character string
    wcsncpy(wFile, T2W(szFile), NUMELMS(wFile)-1);
    wFile[MAX_PATH-1] = 0;

    // Get the interface for DirectShow's GraphBuilder
    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                         IID_IGraphBuilder, (void **)&pGB));

    if(SUCCEEDED(hr))
    {
        CComPtr <IBaseFilter> pVmr;

        // Create the Video Mixing Renderer and add it to the graph
        JIF(InitializeWindowlessVMR(&pVmr));

        // Render the file programmatically to use the VMR9 as renderer.
        // We pass a pointer to the VMR9 so that it will be used as the 
        // video renderer.  Pass TRUE to create an audio renderer also.
        if (FAILED(hr = RenderFileToVMR9(pGB, wFile, pVmr, TRUE)))
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
            // This sample requires a video clip to be loaded
            Msg(TEXT("This sample requires media with a video component.  ")
                TEXT("Please select another file."));
            return E_FAIL;
        }

        // Have the graph signal event via window callbacks for performance
        JIF(pME->SetNotifyWindow((OAHWND)ghApp, WM_GRAPHNOTIFY, 0));

        // Select a text font if not already set
        if (!g_hFont)
            g_hFont = SetTextFont(FALSE);  // Don't display the Font Select dialog

        // Add the dynamic text bitmap to the VMR's input
        // If the initial blend fails, post a close message to exit the app
        hr = BlendText(ghApp, g_szAppText);
        if (FAILED(hr))
            PostMessage(ghApp, WM_CLOSE, 0, 0);

        // Complete the window setup
        ShowWindow(ghApp, SW_SHOWNORMAL);
        UpdateWindow(ghApp);
        SetForegroundWindow(ghApp);
        SetFocus(ghApp);

#ifdef REGISTER_FILTERGRAPH
        if (FAILED(AddGraphToRot(pGB, &g_dwGraphRegister)))
        {
            Msg(TEXT("Failed to register filter graph with ROT!\0"));
            g_dwGraphRegister = 0;
        }
#endif

        // Run the graph to play the media file
        JIF(pMC->Run());

        // Start the text update timer
        StartTimer();
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
    if (FAILED(hr))
        Msg(TEXT("SetVideoPosition FAILED!  hr=0x%x\r\n"), hr);

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
        if (FAILED(hr))
            Msg(TEXT("SetVideoPosition FAILED!  hr=0x%x\r\n"), hr);
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


void OpenClip()
{
    HRESULT hr;

    // If no filename specified by command line, show file open dialog
    if(g_szFileName[0] == L'\0')
    {
        TCHAR szFilename[MAX_PATH];

        InitPlayerWindow();
        SetForegroundWindow(ghApp);

        if (! GetClipFileName(szFilename))
        {
            DWORD dwDlgErr = CommDlgExtendedError();

            // Don't show output if user cancelled the selection (no dlg error)
            if (dwDlgErr)
            {
                Msg(TEXT("GetClipFileName Failed! Error=0x%x\r\n"), GetLastError());
            }
            return;
        }

        // This sample does not support playback of ASX playlists.
        // Since this could be confusing to a user, display a warning
        // message if an ASX file was opened.
        if (_tcsstr((_tcslwr(szFilename)), TEXT(".asx")))
        {
            Msg(TEXT("ASX Playlists are not supported by this application.\n\n")
                TEXT("Please select a valid media file.\0"));
            return;
        }

        lstrcpyn(g_szFileName, szFilename, NUMELMS(g_szFileName));
    }

    // Start playing the media file
    hr = PlayMovieInWindow(g_szFileName);

    // If we couldn't play the clip, clean up
    if (FAILED(hr))
        CloseClip();
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
    ofn.lpstrFilter       = NULL;
    ofn.lpstrFilter       = FILE_FILTER_TEXT;
    ofn.lpstrCustomFilter = NULL;
    ofn.nFilterIndex      = 1;
    ofn.lpstrFile         = szName;
    ofn.nMaxFile          = MAX_PATH;
    ofn.lpstrTitle        = TEXT("Open Image File...\0");
    ofn.lpstrFileTitle    = NULL;
    ofn.lpstrDefExt       = TEXT("*\0");
    ofn.Flags             = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;

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


void CloseClip()
{
    HRESULT hr;

    // Stop the text update timer
    StopTimer();

    // Stop media playback
    if(pMC)
        hr = pMC->Stop();

    // Free DirectShow interfaces
    CloseInterfaces();

    // Clear file name to allow selection of new file with open dialog
    g_szFileName[0] = L'\0';

    // Reset the player window
    RECT rect;
    GetClientRect(ghApp, &rect);
    InvalidateRect(ghApp, &rect, TRUE);

    InitPlayerWindow();
}


void CloseInterfaces(void)
{
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
    SAFE_RELEASE(pBMP);
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

            // Reset to first frame of movie
            hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                   NULL, AM_SEEKING_NoPositioning);
            if (FAILED(hr))
            {
                // If seeking failed, just stop and restart playback
                StopTimer();
                hr = pMC->Stop();

                // Wait for the state to propagate to all filters
                OAFilterState fs;
                hr = pMC->GetState(500, &fs);

                hr = pMC->Run();
                StartTimer();
            }
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
    MessageBox(NULL, szBuffer, TEXT("VMR Text Sample"), MB_OK);
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
                if (lpmm)
                {
                    lpmm->ptMinTrackSize.x = MINIMUM_VIDEO_WIDTH;
                    lpmm->ptMinTrackSize.y = MINIMUM_VIDEO_HEIGHT;
                }
            }
            break;

        case WM_KEYDOWN:

            switch(toupper((int) wParam))
            {
                case VK_ESCAPE:
                case VK_F12:
                    CloseClip();
                    break;

                // When spacebar is presssed, advance to the next text string
                case VK_SPACE:
                    StopTimer();
                    UpdateText();
                    StartTimer();
                    break;
            }
            break;

        case WM_COMMAND:

            switch(wParam)
            { // Menus

                case ID_FILE_OPENCLIP:
                    // If we have ANY file open, close it and shut down DirectShow
                    CloseClip();                   
                    OpenClip();   // Open the new clip
                    break;

                case ID_FILE_INITCLIP:
                    OpenClip();
                    break;

                case ID_FILE_EXIT:
                    CloseClip();
                    PostQuitMessage(0);
                    break;

                case ID_FILE_CLOSE:
                    CloseClip();
                    break;

                case ID_SET_FONT:
                    g_hFont = UserSelectFont();   // Change the current font
                    break;

                case ID_HELP_ABOUT:
                    DialogBox(ghInst, MAKEINTRESOURCE(IDD_HELP_ABOUT),
                              ghApp,  (DLGPROC) AboutDlgProc);
                    break;

            } // Menus
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

    } // Window msgs handling

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
        return FALSE;
    }

    // Verify that the VMR is present on this system
    if(!VerifyVMR9())
        return FALSE;

    // Was a filename specified on the command line?
    if(lpCmdLine[0] != '\0')
    {
        USES_CONVERSION;
        _tcsncpy(g_szFileName, A2T(lpCmdLine), NUMELMS(g_szFileName));        
    }

    // Register the window class
    ZeroMemory(&wc, sizeof wc);
    ghInst = wc.hInstance = hInstC;
    wc.lpfnWndProc   = WndMainProc;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(hInstC, MAKEINTRESOURCE(IDI_TEXT));
    if(!RegisterClass(&wc))
    {
        Msg(TEXT("RegisterClass Failed! Error=0x%x\r\n"), GetLastError());
        CoUninitialize();
        exit(1);
    }

    // Create the main window.  The WS_CLIPCHILDREN style is required.
    ghApp = CreateWindow(CLASSNAME, APPLICATIONNAME,
                         WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN | WS_VISIBLE,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         DEFAULT_PLAYER_WIDTH, DEFAULT_PLAYER_HEIGHT,
                         0, 0, ghInst, 0);

    if(ghApp)
    {
        // Save menu handle for later use
        ghMenu = GetMenu(ghApp);

        // Set default dynamic text
        _tcsncpy(g_szAppText, BLEND_TEXT, NUMELMS(g_szAppText));

        // If a media file was specified on the command line, open it now.
        // (If the first character in the string isn't NULL, post an open clip message.)
        if (g_szFileName[0] != 0)
            PostMessage(ghApp, WM_COMMAND, ID_FILE_INITCLIP, 0);

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


HRESULT InitializeWindowlessVMR(IBaseFilter **ppVmr9)
{
    IBaseFilter* pVmr = NULL;

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

            hr = pVmr->QueryInterface(IID_IVMRWindowlessControl9, (void**)&pWC);
            if( SUCCEEDED(hr)) 
            {
                hr = pWC->SetVideoClippingWindow(ghApp);
                hr = pWC->SetBorderColor(RGB(0,0,0));
            }

#ifndef BILINEAR_FILTERING
            // Request point filtering (instead of bilinear filtering)
            // to improve the text quality.  In general, if you are 
            // not scaling the app image, you should use point filtering.
            // This is very important if you are doing source color keying.
            IVMRMixerControl9 *pMix;

            hr = pVmr->QueryInterface(IID_IVMRMixerControl9, (void**)&pMix);
            if( SUCCEEDED(hr)) 
            {
                DWORD dwPrefs=0;
                hr = pMix->GetMixingPrefs(&dwPrefs);

                if (SUCCEEDED(hr))
                {
                    dwPrefs |= MixerPref_PointFiltering;
                    dwPrefs &= ~(MixerPref_BiLinearFiltering);

                    hr = pMix->SetMixingPrefs(dwPrefs);
                }
                pMix->Release();
            }
#endif

            // Get alpha-blended bitmap interface
            hr = pVmr->QueryInterface(IID_IVMRMixerBitmap9, (void**)&pBMP);
        }
        else
            Msg(TEXT("Failed to add VMR to graph!  hr=0x%x\r\n"), hr);

        // Don't release the pVmr interface because we are copying it into
        // the caller's ppVmr9 pointer
        *ppVmr9 = pVmr;
    }
    else
        Msg(TEXT("Failed to create VMR!  hr=0x%x\r\n"), hr);

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


