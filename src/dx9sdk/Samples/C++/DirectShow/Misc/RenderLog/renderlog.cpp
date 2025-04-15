//------------------------------------------------------------------------------
// File: RenderLog.cpp
//
// Desc: DirectShow sample code - Tool to log RenderFile() output
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <dshow.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <tchar.h>
#include <atlbase.h>

#include <dxerr9.h>
#include "renderlog.h"

//
// Global data
//
HWND      ghApp=0;
HINSTANCE ghInst=0;
TCHAR     g_szFileName[MAX_PATH]={0}, g_szRenderLog[MAX_PATH]={0};
BOOL      g_bAudioOnly=FALSE, g_bAlwaysDisplayLog=FALSE, g_bAlwaysClearLog=TRUE;

// DirectShow interfaces
IGraphBuilder *pGB = NULL;
IMediaControl *pMC = NULL;
IVideoWindow  *pVW = NULL;
IBasicVideo   *pBV = NULL;


HRESULT RenderClip(LPTSTR szFile)
{
    USES_CONVERSION;
    WCHAR wFile[MAX_PATH];
    HRESULT hr=S_OK;
    HANDLE hRenderLog=INVALID_HANDLE_VALUE;

    // Check input string
    if (!szFile)
        return E_POINTER;

    // Clear open dialog remnants before calling RenderFile()
    // (helpful when opening large files or files on a network share)
    UpdateWindow(ghApp);

    // Convert filename to wide character string
    wcsncpy(wFile, T2W(szFile), NUMELMS(wFile));
    wFile[MAX_PATH-1] = 0;

    // Get the interface for DirectShow's GraphBuilder
    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                         IID_IGraphBuilder, (void **)&pGB));

    if(SUCCEEDED(hr))
    {
        // Open (or create) the RenderFile log
        hRenderLog = CreateFile( g_szRenderLog
                               , GENERIC_WRITE
                               , FILE_SHARE_READ
                               , NULL // no security
                               , OPEN_ALWAYS
                               , 0    // no attributes, no flags
                               , NULL // no template
                               );

        if (hRenderLog != INVALID_HANDLE_VALUE) 
        {
            // Seek to end of file to preserve existing content
            SetFilePointer(hRenderLog, 0, NULL, FILE_END);

            // Tell the graph builder to log RenderFile progress to a text file
            JIF(pGB->SetLogFile((DWORD_PTR) hRenderLog));
        }

        // Have the graph builder construct its the appropriate graph automatically
        hr = pGB->RenderFile(wFile, NULL);

        // Close the RenderFile log
        if (hRenderLog != INVALID_HANDLE_VALUE) 
        {
            HRESULT hrSetLog = pGB->SetLogFile(NULL);
            if (FAILED(hrSetLog))
                Msg(TEXT("Failed to set log file! hr=0x%x\n"), hrSetLog);
                
            CloseHandle(hRenderLog);
            hRenderLog = INVALID_HANDLE_VALUE;
        }

        if (FAILED(hr))
        {
            Msg(TEXT("Failed to render the file.  hr=0x%x\r\n\r\n%s\r\n\r\n%s\0"), 
                     hr, DXGetErrorString9(hr), DXGetErrorDescription9(hr));
            return hr;
        }

        // QueryInterface for DirectShow interfaces
        JIF(pGB->QueryInterface(IID_IMediaControl, (void **)&pMC));
        JIF(pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW));
        JIF(pGB->QueryInterface(IID_IBasicVideo, (void **)&pBV));
      
        // Is this an audio-only file (no video component)?
        CheckVisibility();
        if (!g_bAudioOnly)
        {
            JIF(pVW->put_Owner((OAHWND)ghApp));
            JIF(pVW->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN));
            JIF(InitVideoWindow(WINDOW_VIDEO));
        }
        else
        {
            JIF(InitVideoWindow(WINDOW_DEFAULT));
        }

        // Pause the graph to display the first frame of the media file
        JIF(pMC->Pause());

        // Wait for the pause to complete.  This prevents the application from
        // painting (black) on top of the first frame of video.
        OAFilterState fs;
        hr = pMC->GetState(500, &fs);      

        SetFocus(ghApp);
        UpdateWindow(ghApp);
    }

    return hr;
}


void SetRenderLog(void)
{
    OPENFILENAME ofn={0};

    // Provide a buffer to store the returned log name
    TCHAR szLogFile[MAX_PATH];
    _tcscpy(szLogFile, DEFAULT_LOG_FILE);

    // Fill in standard structure fields
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = ghApp;
    ofn.lpstrFilter       = LOG_FILTER_TEXT;
    ofn.lpstrCustomFilter = NULL;
    ofn.nFilterIndex      = 1;
    ofn.nMaxFile          = MAX_PATH;
    ofn.lpstrFile         = szLogFile;
    ofn.lpstrTitle        = TEXT("Specify or create a RenderFile log file...\0");
    ofn.lpstrFileTitle    = NULL;
    ofn.lpstrDefExt       = TEXT("txt\0");
    ofn.Flags             = OFN_HIDEREADONLY  | OFN_SHAREAWARE | 
                            OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    ofn.lpstrInitialDir   = DEFAULT_LOG_PATH;

    // Let the user provide a log file name.  If it succeeds, then copy the
    // name of the selected file into the global RenderFile log name.
    // The log file will be opened and written during the RenderFile process.
    BOOL bSuccess = GetSaveFileName((LPOPENFILENAME)&ofn);
    if (bSuccess)
    {
        _tcsncpy(g_szRenderLog, ofn.lpstrFile, NUMELMS(g_szRenderLog));
        g_szRenderLog[NUMELMS(g_szRenderLog) - 1] = 0;  // Ensure NULL-termination
    }
    else
    {
        DWORD dwDlgErr = CommDlgExtendedError();

        // Don't show output if user cancelled the selection (no dlg error)
        if (dwDlgErr)
            Msg(TEXT("GetClipFileName Failed! Error=0x%x\r\n"), dwDlgErr);
    }
}


void ViewRenderLog(void)
{
    USES_CONVERSION;
    TCHAR szAppName[MAX_PATH * 2 + 15];

    // If the log file exists, display it with Notepad
    if (GetFileAttributes(g_szRenderLog) != (DWORD) -1)
    {
        // For security purposes, be sure to execute the copy of notepad.exe
        // that exists in the Windows directory.  Allow for spaces in the path.

        // Prepend a quote to allow for paths with spaces
        szAppName[0] = TEXT('\"');   szAppName[1] = TEXT('\0');

        // Read windows directory and form the full application path
        if (0 != GetWindowsDirectory(szAppName+1, MAX_PATH - 20))
        {
            // Add the trailing quote to handle paths with spaces
            // (for example, "c:\Microsoft Windows")
            _tcscat(szAppName, TEXT("\\notepad.exe\" \0"));
        }
        else
        {
            // If GetWindowsDirectory fails, just use the executable name
            _tcscpy(szAppName, TEXT("notepad.exe \0"));
        }

        // Append the name of the RenderFile log to generate the full cmd line
        // (for example, "C:\Windows\notepad.exe" renderlog.txt)
        _tcsncat(szAppName, g_szRenderLog, MAX_PATH);

        // Execute the command line to display the log
        WinExec(T2A(szAppName), SW_SHOWNORMAL);
    }
    else
    {
        Msg(TEXT("The log file (%s) has not yet been created.\0"), g_szRenderLog);
    }
}


void ClearRenderLog(void)
{
    HANDLE hRenderLog = INVALID_HANDLE_VALUE;

    // Clear the existing RenderFile log
    hRenderLog = CreateFile( g_szRenderLog
                           , GENERIC_WRITE
                           , FILE_SHARE_READ
                           , NULL // no security
                           , TRUNCATE_EXISTING
                           , 0    // no attributes, no flags
                           , NULL // no template
                           );

    // Close the file handle
    if (hRenderLog != INVALID_HANDLE_VALUE)
        CloseHandle(hRenderLog);
}


HRESULT InitVideoWindow(int nWindowType)
{
    // If no video clip is loaded, display a default window
    if (nWindowType == WINDOW_DEFAULT)
    {
        // Reset to a default size for audio and after closing a clip
        SetWindowPos(ghApp, NULL, 0, 0,
                     DEFAULT_WIDTH, DEFAULT_HEIGHT,
                     SWP_NOMOVE | SWP_NOZORDER);
        return S_OK;
    }
    else
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

        int nTitleHeight  = GetSystemMetrics(SM_CYCAPTION);
        int nBorderWidth  = GetSystemMetrics(SM_CXBORDER);
        int nBorderHeight = GetSystemMetrics(SM_CYBORDER);

        // Account for size of title bar and borders for exact match
        // of window client area to default video size
        SetWindowPos(ghApp, NULL, 0, 0, lWidth + 2*nBorderWidth,
                lHeight + nTitleHeight + 2*nBorderHeight,
                SWP_NOMOVE | SWP_NOZORDER);

        GetClientRect(ghApp, &rect);
        JIF(pVW->SetWindowPosition(rect.left, rect.top, rect.right, rect.bottom));
        return hr;
    }
}


void MoveVideoWindow(void)
{
    HRESULT hr;

    // Track the movement of the container window and resize as needed
    if(pVW)
    {
        RECT client;
        GetClientRect(ghApp, &client);

        hr = pVW->SetWindowPosition(client.left, client.top,
                                    client.right, client.bottom);
    }
}


void CheckVisibility(void)
{
    long lVisible;
    HRESULT hr;

    if ((!pVW) || (!pBV))
    {
        // Audio-only files have no video interfaces.  This might also
        // be a file whose video component uses an unknown video codec.
        g_bAudioOnly = TRUE;
        return;
    }
    else
    {
        // Clear the global flag
        g_bAudioOnly = FALSE;
    }

    hr = pVW->get_Visible(&lVisible);
    if (FAILED(hr))
    {
        // If this is an audio-only clip, get_Visible() won't work.
        // Also, if this video is encoded with an unsupported codec,
        // we won't see any video, although the audio will work if it is
        // of a supported format.
        //
        if (hr == E_NOINTERFACE)
            g_bAudioOnly = TRUE;
    }
}


void OpenClip()
{
    HRESULT hr;

    // If no filename was specified by command line, show file open dialog
    if(g_szFileName[0] == L'\0')
    {
        TCHAR szFilename[MAX_PATH];

        // If no filename was specified on the command line, then our video
        // window has not been created or made visible.  Make our main window
        // visible and bring to the front to allow file selection.
        InitVideoWindow(WINDOW_DEFAULT);
        ShowWindow(ghApp, SW_SHOWNORMAL);
        SetForegroundWindow(ghApp);

        if (! GetClipFileName(szFilename))
        {
            DWORD dwDlgErr = CommDlgExtendedError();

            // Don't show output if user cancelled the selection (no dlg error)
            if (dwDlgErr)
                Msg(TEXT("GetClipFileName Failed! Error=0x%x\r\n"), GetLastError());
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

    // Empty the RenderFile() log
    if (g_bAlwaysClearLog)
        ClearRenderLog();
    
    // Display the media file
    hr = RenderClip(g_szFileName);

    // If we couldn't render the clip, clean up and display the render log
    if (FAILED(hr))
    {
        CloseClip();
        ViewRenderLog();
    }
    // If the file rendered successfully, but the user always wants to see
    // the RenderFile() log, then display it now
    else if (g_bAlwaysDisplayLog)
        ViewRenderLog();
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
    ofn.lpstrTitle        = TEXT("Open Media File...\0");
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
    // Free DirectShow interfaces
    CloseInterfaces();

    // Clear global flags
    g_bAudioOnly = TRUE;

    // Clear file name to allow selection of new file with open dialog
    g_szFileName[0] = L'\0';

    // Reset the player window
    RECT rect;
    GetClientRect(ghApp, &rect);
    InvalidateRect(ghApp, &rect, TRUE);
    InitVideoWindow(WINDOW_DEFAULT);
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

    // Release and zero DirectShow interfaces
    SAFE_RELEASE(pMC);
    SAFE_RELEASE(pBV);
    SAFE_RELEASE(pVW);
    SAFE_RELEASE(pGB);
}


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
    MessageBox(NULL, szBuffer, TEXT("RenderLog Sample"), MB_OK);
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
        // Resize the video when the window changes
        case WM_MOVE:
        case WM_SIZE:
            if ((hWnd == ghApp) && (!g_bAudioOnly))
                MoveVideoWindow();
            break;

        // Enforce a minimum window size
        case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO lpmm = (LPMINMAXINFO) lParam;
                lpmm->ptMinTrackSize.x = MINIMUM_VIDEO_WIDTH;
                lpmm->ptMinTrackSize.y = MINIMUM_VIDEO_HEIGHT;
            }
            break;

        case WM_KEYDOWN:

            switch(toupper((int) wParam))
            {
                case VK_ESCAPE:
                case VK_F12:
                    CloseClip();
                    PostQuitMessage(0);
                    break;
            }
            break;

        case WM_COMMAND:

            switch(wParam)
            { // Menus

                case ID_FILE_OPENCLIP:
                    CloseClip();
                    OpenClip();
                    break;

                case ID_FILE_CLOSE:
                    CloseClip();
                    break;

                case ID_FILE_INITCLIP:
                    OpenClip();
                    break;

                case ID_FILE_EXIT:
                    CloseClip();
                    PostQuitMessage(0);
                    break;

                case ID_VIEWLOG:
                    ViewRenderLog();
                    break;
                case ID_CLEARLOG:
                    ClearRenderLog();
                    break;
                case ID_SETLOG:
                    SetRenderLog();
                    break;

                case ID_ALWAYS_DISPLAY_LOG:
                    g_bAlwaysDisplayLog ^= 1;
                    CheckMenuItem(GetMenu(hWnd), ID_ALWAYS_DISPLAY_LOG, 
                                  g_bAlwaysDisplayLog ? MF_CHECKED : MF_UNCHECKED);
                    break;

                case ID_ALWAYS_CLEAR_LOG:
                    g_bAlwaysClearLog ^= 1;
                    CheckMenuItem(GetMenu(hWnd), ID_ALWAYS_CLEAR_LOG, 
                                  g_bAlwaysClearLog ? MF_CHECKED : MF_UNCHECKED);
                    break;

                case ID_HELP_ABOUT:
                    DialogBox(ghInst, MAKEINTRESOURCE(IDD_ABOUTBOX),
                              ghApp,  (DLGPROC) AboutDlgProc);
                    break;

            } // Menus
            break;


        case WM_CLOSE:
            SendMessage(ghApp, WM_COMMAND, ID_FILE_EXIT, 0);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);

    } // Window message handling

    // Pass this message to the video window for notification of system changes
    if (pVW)
        pVW->NotifyOwnerMessage((LONG_PTR) hWnd, message, wParam, lParam);

    return DefWindowProc(hWnd, message, wParam, lParam);
}


int PASCAL WinMain(HINSTANCE hInstC, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg={0};
    WNDCLASS wc;

    // Initialize COM
    if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        Msg(TEXT("CoInitialize Failed!\r\n"));
        exit(1);
    }

    // Was a filename specified on the command line?
    if (lpCmdLine[0] != '\0')
    {
        USES_CONVERSION;
        _tcsncpy(g_szFileName, A2T(lpCmdLine), NUMELMS(g_szFileName));        
    }
    g_szFileName[MAX_PATH-1] = 0;   // Null-terminate    

    // Register the window class
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc = WndMainProc;
    ghInst = wc.hInstance = hInstC;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(hInstC, MAKEINTRESOURCE(IDI_RENDERLOG));
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
                         DEFAULT_WIDTH, DEFAULT_HEIGHT,
                         0, 0, ghInst, 0);
                         
    if(ghApp)
    {
        // Initialize the RenderFile log name
        _tcsncpy(g_szRenderLog, DEFAULT_LOG_FILE, NUMELMS(g_szRenderLog));

        // If a filename was passed on the command line, open it at startup
        if(g_szFileName[0] != L'\0')
            PostMessage(ghApp, WM_COMMAND, ID_FILE_INITCLIP, 0L);
        

        // Main message loop
        while(GetMessage(&msg,NULL,0,0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Finished with COM
    CoUninitialize();

    return (int) msg.wParam;
}

