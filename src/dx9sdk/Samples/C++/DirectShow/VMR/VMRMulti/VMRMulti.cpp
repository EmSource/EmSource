//----------------------------------------------------------------------------
//  File:   VMRMulti.cpp
//
//  Desc:   DirectShow sample code
//          Application-level global functions
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "project.h"
#include <commdlg.h>
#include "vmrutil.h"


//-------------------------------------------------------------------------
//  Functions prototypes
//-------------------------------------------------------------------------
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

// -------------------------------------------------------------------------
// VMRMulti window class prototypes
// -------------------------------------------------------------------------

LPARAM CALLBACK VMRMultiWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LPARAM CALLBACK VMRMultiPBWnd(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//-------------------------------------------------------------------------
//  Global variables
//-------------------------------------------------------------------------
LPSTR       g_lpCmdLine=0;
HINSTANCE   g_hInst=0;
HWND        g_hwndApp=0;
HWND        g_hwndPB=0;
HWND        g_hwndTrackbar=0;

float       g_TrackBarScale = 1.0F;

CMultiSAP*  g_pMultiSAP=0;
DWORD       g_dwUserID=0;


//-------------------------------------------------------------------------
//  Constants
//-------------------------------------------------------------------------
const TCHAR szClassName[] = TEXT("SJE_VMRMulti_CLASS");
const TCHAR szAppTitle[]  = TEXT("VMRMulti Test Application");
const int g_nToolTips = 5;

extern const int MaxNumberOfMovies;

TCHAR szTTPlay[]  = TEXT("Play\0");
TCHAR szTTPause[] = TEXT("Pause\0");
TCHAR szTTEject[] = TEXT("Delete movie from the list\0");
TCHAR szTTSlide[] = TEXT("Change media position for selected movie\0");
TCHAR szTTList[]  = TEXT("Double click on the movie to activate\0");

// tooltips support
UINT g_ToolTipIDs[] = { IDC_PLAY, IDC_STOP, IDC_EJECT, IDC_SLIDER, IDC_ACTIVE_PB };

TCHAR * g_lpstrToolTipText[] = { szTTPlay, szTTPause, szTTEject, szTTSlide, szTTList};

HWND     g_hwndToolTips[g_nToolTips];
TOOLINFO g_ti[g_nToolTips];


//-------------------------------------------------------------------------
//  WinMain
//-------------------------------------------------------------------------
int PASCAL
WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
    )
{
    MSG msg;

    g_lpCmdLine = lpCmdLine;

    //
    // Verify that the Video Mixing Renderer is present on this system
    //
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    if(!VerifyVMR())
        return FALSE;

    // Uninitialize COM because it will be reinitialized elsewhere
    // when a movie file is opened.
    CoUninitialize();

    if (!hPrevInstance) {
        if (!InitApplication(hInstance)) {
            return FALSE;
        }
    }

    /*
    ** Perform initializations that apply to a specific instance
    */
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    /*
    ** Acquire and dispatch messages until a WM_QUIT message is received.
    */
    while (GetMessage(&msg, NULL, 0, 0)) {

        if (!IsDialogMessage(g_hwndApp, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return ((int) msg.wParam);
}


//-------------------------------------------------------------------------
//  InitApplication(HINSTANCE)
//-------------------------------------------------------------------------
BOOL
InitApplication(
    HINSTANCE hInstance
    )
{
    g_hInst = hInstance;
    InitCommonControls();
    return TRUE;
}


//-------------------------------------------------------------------------
//  InitInstance
//  
//  creates dialog and playback windows, initializes application
//-------------------------------------------------------------------------
BOOL
InitInstance(
    HINSTANCE hInstance,
    int nCmdShow
    )
{
    HWND        hwnd;
    WNDCLASS    cls;

    cls.lpszClassName  = TEXT("VMRMulti");
    cls.hCursor        = LoadCursor(NULL, IDC_ARROW);
    cls.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    cls.lpszMenuName   = NULL;
    cls.hbrBackground  = (HBRUSH)(COLOR_BTNFACE + 1);
    cls.hInstance      = hInstance;
    cls.style          = CS_DBLCLKS;
    cls.lpfnWndProc    = DefDlgProc;
    cls.cbClsExtra     = 0;
    cls.cbWndExtra     = DLGWINDOWEXTRA;
    if (!RegisterClass(&cls)) {
        return FALSE;
    }

    cls.lpszClassName  = TEXT("VMRMultiPBWnd");
    cls.hCursor        = LoadCursor(NULL, IDC_ARROW);
    cls.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    cls.lpszMenuName   = NULL;
    cls.hbrBackground  = NULL;
    cls.hInstance      = hInstance;
    cls.style          = CS_DBLCLKS;
    cls.lpfnWndProc    = VMRMultiPBWnd;
    cls.cbClsExtra     = 0;
    cls.cbWndExtra     = 0;
    if (!RegisterClass(&cls)) {
        return FALSE;
    }

    /*
    ** Create a main window for this application instance.
    */
    hwnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_VMR_MULTI),
                        (HWND)NULL, (DLGPROC)VMRMultiWndProc );

    /*
    ** If window could not be created, return "failure"
    */
    if (!hwnd) {
        return FALSE;
    }

    g_hwndApp = hwnd;
    ShowWindow(g_hwndApp, SW_SHOW);
    UpdateWindow(g_hwndApp);

    return TRUE;
}


//-------------------------------------------------------------------------
//  OnButtonAddsrc  
//
//  calls FileOpen dialog and returns the file; 
//-------------------------------------------------------------------------
void OnButtonAddsrc(HWND hwnd) 
{
    OPENFILENAME ofn;
    TCHAR szBuffer[MAX_PATH];

    HWND hwndList = GetDlgItem(hwnd, IDC_ACTIVE_PB);

    if( !IsWindow(hwnd) || !IsWindow( hwndList ))
    {
        return;
    }

    if( ListBox_GetCount(hwndList) >= MaxNumberOfMovies )
    {
        TCHAR szMsg[MAX_PATH];
        wsprintf(szMsg, _T("This application supports up to %d open movies.\0"), 
                 MaxNumberOfMovies );
        MessageBox(hwnd, szMsg, szAppTitle, MB_OK);
        return;
    }

    lstrcpy(szBuffer, TEXT(""));
    static TCHAR szFilter[]  = _T("Video Files (.AVI,.MOV,.MPG,.VOB,.QT)\0")
                               _T("*.AVI;*.MOV;*.MPG;*.VOB;*.QT\0")
                               _T("All Files (*.*)\0*.*\0\0");
    ZeroStruct(ofn);
    ofn.lStructSize   = sizeof(OPENFILENAME);
    ofn.lpstrFilter   = szFilter;
    ofn.nFilterIndex  = 1;
    ofn.lpstrFile     = szBuffer;
    ofn.nMaxFile      = _MAX_PATH;
    ofn.lpstrTitle    = TEXT("VMRMulti: Select a video file to play...");
    ofn.Flags         = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt   = TEXT("avi");
    
    if (GetOpenFileName (&ofn))  // user specified a file
    {
        USES_CONVERSION;        
        sMovieInfo * psMovInfo = NULL;
        psMovInfo = new sMovieInfo;
        TCHAR szUserID[MAX_PATH+12];

        if( !psMovInfo )
        {
            MessageBox(hwnd, _T("Memory allocation error when trying to add a new entry"),
                       szAppTitle, MB_OK);
            return;
        }

        psMovInfo->pdwUserID = g_dwUserID++;

#ifdef UNICODE
        lstrcpyn(psMovInfo->achPath, T2W(ofn.lpstrFile), NUMELMS(psMovInfo->achPath));
        _stprintf(szUserID, _T("0x%08x\t%s\0"), psMovInfo->pdwUserID, T2W(psMovInfo->achPath));
#else
        MultiByteToWideChar(CP_ACP, 0, (const char*)ofn.lpstrFile, -1, psMovInfo->achPath, MOVIEINFO_PATH_CHARS); 
        wsprintf( szUserID, _T("0x%08x\t%S\0"), psMovInfo->pdwUserID,  psMovInfo->achPath);
#endif

        // inform CMultiSAP about new movie
        g_pMultiSAP->CmdAddMovie(psMovInfo);

        if( g_pMultiSAP->GetMovieEventHandle( psMovInfo->pdwUserID))
        {
            // add to the list
            int nItem = ListBox_InsertString(hwndList, ListBox_GetCount(hwndList), szUserID);
            ListBox_SetItemData(hwndList, nItem, (DWORD_PTR) psMovInfo);
            ListBox_SetCurSel(hwndList, nItem);
        }
    }
}


//-------------------------------------------------------------------------
//  SetDurationLength
//
//  Updates pane 0 on the status bar
//-------------------------------------------------------------------------
void
SetDurationLength(
    REFTIME rt
    )
{
    g_TrackBarScale = 1.0;
    while (rt / g_TrackBarScale > 30000)
        g_TrackBarScale *= 10;

    SendMessage(g_hwndTrackbar, TBM_SETRANGE, TRUE,
                MAKELONG(0, (WORD)(rt / g_TrackBarScale)));

    SendMessage(g_hwndTrackbar, TBM_SETTICFREQ, (WPARAM)((int)(rt / g_TrackBarScale) / 9), 0);
    SendMessage(g_hwndTrackbar, TBM_SETPAGESIZE, 0, (LPARAM)((int)(rt / g_TrackBarScale) / 9));
}


//-------------------------------------------------------------------------
//  SetCurrentPosition
//
//  Updates pane 1 on the status bar
//-------------------------------------------------------------------------
void
SetCurrentPosition(
    REFTIME rt
    )
{
    SendMessage(g_hwndTrackbar, TBM_SETPOS, TRUE, (LPARAM)(rt / g_TrackBarScale));
}


//-------------------------------------------------------------------------
//  GetCurrentActiveMovie
//  
//  returns data on currently selected movie
//-------------------------------------------------------------------------
sMovieInfo* GetCurrentActiveMovie(HWND hwnd)
{
    HWND hwndList = GetDlgItem(hwnd, IDC_ACTIVE_PB);

    int nItem = ListBox_GetCurSel(hwndList);
    if( -1 == nItem)
    {
        return NULL;
    }

    return (sMovieInfo*)ListBox_GetItemData(hwndList, nItem);
}

//-------------------------------------------------------------------------
//  OnButtonPlay
//  
//  sends "play" command to CMultiSAP
//-------------------------------------------------------------------------
void OnButtonPlay(HWND hwnd) 
{
    sMovieInfo* pMovInf = GetCurrentActiveMovie(hwnd);
    if( !pMovInf)
        return;

    g_pMultiSAP->CmdPlayMovie(pMovInf);
}

//-------------------------------------------------------------------------
//  OnButtonPause
//
//  sends "Pause" command to CMultiSAP
//-------------------------------------------------------------------------
void OnButtonPause(HWND hwnd) 
{
    sMovieInfo* pMovInf = GetCurrentActiveMovie(hwnd);
    if( !pMovInf)
        return;

    g_pMultiSAP->CmdPauseMovie(pMovInf);
}

//-------------------------------------------------------------------------
//  OnButtonEject
//
//  sends "Eject" command to CMultiSAP
//-------------------------------------------------------------------------
void OnButtonEject(HWND hwnd) 
{
    HWND hwndList = GetDlgItem(hwnd, IDC_ACTIVE_PB);
    sMovieInfo* pMovInf = GetCurrentActiveMovie(hwnd);
    if( !pMovInf)
        return;

    sMovieInfo *pInf = NULL;
    g_pMultiSAP->CmdEjectMovie(pMovInf);

    // delete this movie from the list box
    int nItem = ListBox_GetCurSel(hwndList);
    pInf = (sMovieInfo*)ListBox_GetItemData( hwndList, nItem);
    ListBox_DeleteString(hwndList, nItem);

    if( pInf )
        delete pInf;
}


//-------------------------------------------------------------------------
//  OnButtonSwitch
//-------------------------------------------------------------------------
void OnButtonSwitch(HWND hwnd) 
{
    sMovieInfo* pMovInf = GetCurrentActiveMovie(hwnd);
    if( !pMovInf)
    {
        return;
    }

    g_pMultiSAP->CmdExpandMovie(pMovInf);
}


//-------------------------------------------------------------------------
//  VMRMulti_OnCommand
//
//  processes dialog commands
//-------------------------------------------------------------------------
void
VMRMulti_OnCommand(
    HWND hwnd,
    int id,
    HWND hwndCtl,
    UINT codeNotify
    )
{
    switch (id) 
    {
        case IDC_ACTIVE_PB:
            if (codeNotify == LBN_DBLCLK ) 
            {
                OnButtonSwitch(hwnd);
            }
            break;

        case IDC_ADD:
            if (codeNotify == BN_CLICKED) 
            {
                OnButtonAddsrc(hwnd);
            }
            break;

        case IDOK:
            if (codeNotify == BN_CLICKED) 
            {
                PostMessage(hwnd, WM_CLOSE, 0, 0L);
            }
            break;


        case IDC_PLAY:
            if (codeNotify == BN_CLICKED) 
            {
                OnButtonPlay(hwnd);
            }
            break;

        case IDC_STOP:
            if (codeNotify == BN_CLICKED) 
            {
                OnButtonPause(hwnd);
            }
            break;

        case IDC_EJECT:
            if (codeNotify == BN_CLICKED) 
            {
                OnButtonEject(hwnd);
            }
            break;

        case IDC_SWITCH:
            if (codeNotify == BN_CLICKED) 
            {
                OnButtonSwitch(hwnd);
            }
            break;
    }
}


//-------------------------------------------------------------------------
//  VMRMulti_OnInitDialog
//
//  Initializes dialog, loads tooltips
//-------------------------------------------------------------------------
BOOL
VMRMulti_OnInitDialog(
    HWND hwnd,
    HWND hwndFocus,
    LPARAM lParam
    )
{
    // set bitmap buttons
    HBITMAP hbm = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_PLAY));
    SendDlgItemMessage(hwnd, IDC_PLAY, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);

    hbm = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_STOP));
    SendDlgItemMessage(hwnd, IDC_STOP, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);

    hbm = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_EJECT));
    SendDlgItemMessage(hwnd, IDC_EJECT, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);

    hbm = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_SWITCH));
    SendDlgItemMessage(hwnd, IDC_SWITCH, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);

    g_hwndPB = CreateWindow(TEXT("VMRMultiPBWnd"), TEXT("PlaybackWindow"), 
                            WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, 
                            NULL, NULL, g_hInst, NULL);

    g_hwndTrackbar = GetDlgItem(hwnd, IDC_SLIDER);

    SetDurationLength((REFTIME)0);
    SetCurrentPosition((REFTIME)0);
    SetTimer(hwnd, 0x12346, 500, NULL);

    // initialize tool tips
    for( int i=0; i< g_nToolTips; i++ )
    {
        g_hwndToolTips[i] = CreateWindow(TOOLTIPS_CLASS, NULL,
                                         WS_POPUP | TTS_NOPREFIX,
                                         0, 0, 0, 0, NULL, NULL, g_hInst, NULL );
        if( g_hwndToolTips[i] )
        {
            SetWindowPos( g_hwndToolTips[i], HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE );

            HWND hwndBtn = GetDlgItem( hwnd, g_ToolTipIDs[i]);
            if( !IsWindow( hwndBtn ) )
            {
                continue;
            }

            g_ti[i].cbSize = sizeof( TOOLINFO );
            g_ti[i].uFlags = TTF_TRANSPARENT | TTF_CENTERTIP | TTF_SUBCLASS | TTF_IDISHWND;
            g_ti[i].hwnd = hwndBtn;
            g_ti[i].uId =  (UINT_PTR)hwndBtn;
            g_ti[i].hinst = g_hInst;
            g_ti[i].lpszText = g_lpstrToolTipText[i];
            GetClientRect( g_hwndToolTips[i], &(g_ti[i].rect));
 
            LRESULT lRes = SendMessage( g_hwndToolTips[i], TTM_ADDTOOL, 0, (LPARAM)&(g_ti[i]) );
        }
    }// for
    
    return FALSE;
}


//-------------------------------------------------------------------------
//  VMRMulti_OnDestroy
//  Unloads button bitmaps, releases tooltips
//-------------------------------------------------------------------------
void VMRMulti_OnDestroy( HWND hwnd )

{
    HBITMAP hbm = (HBITMAP)SendDlgItemMessage(hwnd, IDC_PLAY, BM_SETIMAGE, IMAGE_BITMAP, 0);
    DeleteObject((HGDIOBJ)hbm);

    hbm = (HBITMAP)SendDlgItemMessage(hwnd, IDC_STOP, BM_SETIMAGE, IMAGE_BITMAP, 0);
    DeleteObject((HGDIOBJ)hbm);

    hbm = (HBITMAP)SendDlgItemMessage(hwnd, IDC_EJECT, BM_SETIMAGE, IMAGE_BITMAP, 0);
    DeleteObject((HGDIOBJ)hbm);

    hbm = (HBITMAP)SendDlgItemMessage(hwnd, IDC_SWITCH, BM_SETIMAGE, IMAGE_BITMAP, 0);
    DeleteObject((HGDIOBJ)hbm);

    for( int i=0; i<g_nToolTips; i++)
    {
        SendMessage( g_hwndToolTips[i], TTM_DELTOOL, 0, (LPARAM)&(g_ti[i]) );
        DestroyWindow( g_hwndToolTips[i] );
    }

    PostQuitMessage(0);
}


//-------------------------------------------------------------------------
//  VMRMulti_OnClose
//
//  destroys dialog window and playback window
//-------------------------------------------------------------------------
void VMRMulti_OnClose( HWND hwnd )
{
    DestroyWindow(g_hwndPB);
    DestroyWindow(hwnd);
}


//-------------------------------------------------------------------------
//  VMRMulti_OnTimer
//
//  We use OnTimer event to update slider and status of the movie;
//  also, restart movies that reached their end
//-------------------------------------------------------------------------
void VMRMulti_OnTimer( HWND hwnd, UINT id )
{
    sMovieInfo* pMovInf = GetCurrentActiveMovie(hwnd);
    if(!pMovInf)
    {
        return;
    }

    static OAFilterState OldState;

    static DWORD dwTime;
    static DWORD dwFrameNum;

    static int nSlowCounter = 0;


    OAFilterState State = g_pMultiSAP->CmdGetMovieState(pMovInf);
    SetDurationLength(g_pMultiSAP->CmdGetMovieDuration(pMovInf));   
    SetCurrentPosition(g_pMultiSAP->CmdGetMoviePosition(pMovInf));   

    DWORD dwTimeCurr = timeGetTime();
    DWORD dwFrameCurr = g_pMultiSAP->GetCurrentFrameNumber();

    TCHAR WindowText[64];

    int f = ((dwFrameCurr - dwFrameNum) * 100000) / (dwTimeCurr - dwTime);
    dwTime = dwTimeCurr;
    dwFrameNum = dwFrameCurr;

    wsprintf(WindowText,
         TEXT("PlaybackWindow: Frame Rate %d.%.2d / Sec"),
         f / 100, f % 100 );

    SetWindowText(hwnd, WindowText);


    if (OldState != State) {

        switch (State) {
        case State_Running:
            SetDlgItemText(hwnd, IDC_STATUS, _T("Running"));
            break;

        case State_Paused:
        case State_Stopped:
            SetDlgItemText(hwnd, IDC_STATUS, _T("Stopped"));
            break;
        }
    };

    OldState = State;

    nSlowCounter++;
    if( nSlowCounter == 4 )
    {
        nSlowCounter = 0;
    }
    if( 3 == nSlowCounter ) // every fourth time, i.e. every 2 sec, check if we need to re-run stopped movies
    {
        HWND hwndList = GetDlgItem(hwnd, IDC_ACTIVE_PB);
        sMovieInfo *pInf = NULL;
        REFTIME rtPos;
        REFTIME rtDuration;

        int nItems = ListBox_GetCount(hwndList);
        for( int i=0; i< nItems; i++)
        {
            pInf = NULL;
            int nItem = ListBox_GetCurSel(hwndList);

            pInf = (sMovieInfo*)ListBox_GetItemData( hwndList, i);
            if( pInf )
            {
                rtPos = g_pMultiSAP->CmdGetMoviePosition( pInf );
                rtDuration = g_pMultiSAP->CmdGetMovieDuration( pInf);
                if( rtDuration - rtPos < 0.05)
                {
                    g_pMultiSAP->CmdSetMoviePosition(pInf, 0);
                    g_pMultiSAP->CmdPlayMovie( pInf );
                }
            }
        }// for all movies in the list
    }
}


//-------------------------------------------------------------------------
//  VMRMultiSeekCmd
//  
//  performs "seek" command
//-------------------------------------------------------------------------
void VMRMultiSeekCmd( sMovieInfo* pMovInf, REFTIME rtSeekBy )
{
    REFTIME rt;
    REFTIME rtDur;

    rtDur = g_pMultiSAP->CmdGetMovieDuration(pMovInf);
    rt = g_pMultiSAP->CmdGetMoviePosition(pMovInf) + rtSeekBy;

    rt = max(0, min(rt, rtDur));

    g_pMultiSAP->CmdSetMoviePosition(pMovInf, rt);
    SetCurrentPosition(g_pMultiSAP->CmdGetMoviePosition(pMovInf));
}


//-------------------------------------------------------------------------
//  VMRMulti_OnHScroll
//
//  processes the command to change media position from the slider
//-------------------------------------------------------------------------
void VMRMulti_OnHScroll( HWND hwnd, HWND hwndCtl, UINT code, int pos )
{
    static BOOL fWasPlaying = FALSE;
    static BOOL fBeginScroll = FALSE;

    sMovieInfo* pMovInf = GetCurrentActiveMovie(hwnd);
    if(!pMovInf)
    {
        return;
    }

    if (hwndCtl == g_hwndTrackbar) 
    {
        REFTIME  rtCurrPos;
        REFTIME  rtTrackPos;
        REFTIME  rtDuration;
        
        pos = (int)SendMessage(g_hwndTrackbar, TBM_GETPOS, 0, 0);
        rtTrackPos = (REFTIME)pos * g_TrackBarScale;

        switch (code) 
        {
            case TB_BOTTOM:           
                rtDuration = g_pMultiSAP->CmdGetMovieDuration(pMovInf);
                rtCurrPos = g_pMultiSAP->CmdGetMoviePosition(pMovInf);
                VMRMultiSeekCmd(pMovInf, rtDuration - rtCurrPos);
                break;

            case TB_TOP:
                rtCurrPos = g_pMultiSAP->CmdGetMoviePosition(pMovInf);
                VMRMultiSeekCmd(pMovInf,-rtCurrPos);
                break;

            case TB_LINEDOWN:
                VMRMultiSeekCmd(pMovInf,10.0);
                break;

            case TB_LINEUP:
                VMRMultiSeekCmd(pMovInf,-10.0);
                break;

            case TB_ENDTRACK:
                fBeginScroll = FALSE;
                if (fWasPlaying) 
                {
                    g_pMultiSAP->CmdPauseMovie(pMovInf);
                    fWasPlaying = FALSE;
                }
                break;

            case TB_THUMBTRACK:
                if (!fBeginScroll) 
                {
                    fBeginScroll = TRUE;
                    fWasPlaying = (g_pMultiSAP->CmdGetMovieState(pMovInf) & State_Running);
                    if (fWasPlaying) 
                    {
                        g_pMultiSAP->CmdPauseMovie(pMovInf);
                    }
                }
            case TB_PAGEUP:
            case TB_PAGEDOWN:
                rtCurrPos = g_pMultiSAP->CmdGetMoviePosition(pMovInf);
                VMRMultiSeekCmd(pMovInf, rtTrackPos - rtCurrPos);
                break;
        }
    }
}


//-------------------------------------------------------------------------
//  VMRMultiWndProc
//
//  message processing for dialog
//-------------------------------------------------------------------------
LPARAM CALLBACK VMRMultiWndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch (message) 
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG,     VMRMulti_OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND,        VMRMulti_OnCommand);
        HANDLE_MSG(hwnd, WM_CLOSE,          VMRMulti_OnClose);
        HANDLE_MSG(hwnd, WM_DESTROY,        VMRMulti_OnDestroy);
        HANDLE_MSG(hwnd, WM_TIMER,          VMRMulti_OnTimer);
        HANDLE_MSG(hwnd, WM_HSCROLL,        VMRMulti_OnHScroll);

        default:
            return FALSE;
    }
}


//  THE FOLLOWING FUNCTIONS PROCESS MESSAGES FOR VIDEO WINDOW

//-------------------------------------------------------------------------
//  VideoMultiVMR_OnDestroy
//  
//  delete movie list, destroy custom AP
//-------------------------------------------------------------------------
void VideoMultiVMR_OnDestroy( HWND hwnd )
{
    g_pMultiSAP->DeleteAllMovies();
    delete g_pMultiSAP;
    g_pMultiSAP = NULL;

    PostQuitMessage( 0 );
}


//-------------------------------------------------------------------------
//  VideoMultiVMR_OnSize
//
//  updates movie's position
//-------------------------------------------------------------------------
void VideoMultiVMR_OnSize( HWND hwnd, UINT state, int dx, int dy)
{
    if( g_pMultiSAP )
    {
        g_pMultiSAP->RepositionMovie();
    }
}


//-------------------------------------------------------------------------
//  VideoMultiVMR_OnMove
//-------------------------------------------------------------------------
void VideoMultiVMR_OnMove( HWND hwnd, int x, int y )
{
    if(g_pMultiSAP)
    {
        RECT rcPos;

        // Reposition movie but don't invalidate the rect, since
        // the next video frame will handle the redraw.
        g_pMultiSAP->GetMoviePosition(&rcPos);
        g_pMultiSAP->PutMoviePosition(rcPos);
    }
}


//-------------------------------------------------------------------------
//  VideoMultiVMR_OnActivate
//-------------------------------------------------------------------------
void VideoMultiVMR_OnActivate( HWND hwnd, WPARAM wParam, LPARAM lParam )
{
    if((UINT)LOWORD(wParam))
    {
        // we are being activated - tell the Filter graph (for Sound follows focus)
        if(g_pMultiSAP)
        {
            g_pMultiSAP->SetFocus();
        }
    }
}


//-------------------------------------------------------------------------
//  VideoMultiVMR_OnDblClk
// 
//  User double clicked on the video window
//-------------------------------------------------------------------------
void VideoMultiVMR_OnDblClk( HWND hwnd, WPARAM wParam, LPARAM lParam)
{
    int xPos = GET_X_LPARAM( lParam );
    int yPos = GET_Y_LPARAM( lParam );

    if( g_pMultiSAP )
    {
        g_pMultiSAP->CmdProcessDoubleClick( xPos, yPos );
    }

}


//-------------------------------------------------------------------------
//  VideoMultiVMR_OnCreate
//  Creates and initializes custom AP (CMultiSAP)
//-------------------------------------------------------------------------
BOOL VideoMultiVMR_OnCreate( HWND hwnd, LPCREATESTRUCT lpCreateStruct )
{
    HRESULT hr = S_OK;

    g_pMultiSAP = new CMultiSAP(hwnd, &hr);
    if (!g_pMultiSAP || FAILED(hr)) 
    {
        delete g_pMultiSAP;
        g_pMultiSAP = NULL;
        return FALSE;
    }

    g_pMultiSAP->Initialize();

    return TRUE;
}


//-------------------------------------------------------------------------
//  VMRMultiPBWnd
//  
//  Message processing for video window
//-------------------------------------------------------------------------
LPARAM CALLBACK VMRMultiPBWnd( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch (message) 
    {
        HANDLE_MSG(hwnd, WM_CREATE,            VideoMultiVMR_OnCreate);
        HANDLE_MSG(hwnd, WM_DESTROY,           VideoMultiVMR_OnDestroy);
        HANDLE_MSG(hwnd, WM_SIZE,              VideoMultiVMR_OnSize);
        HANDLE_MSG(hwnd, WM_MOVE,              VideoMultiVMR_OnMove);

        case WM_PAINT:
            if(g_pMultiSAP)
            {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                g_pMultiSAP->RePaint();
                EndPaint(hwnd, &ps);
            }
            break;

        // Note: we do not use HANDLE_MSG here as we want to call
        // DefWindowProc after we have notifed the FilterGraph Resource Manager,
        // otherwise our window will not finish its activation process.

        case WM_ACTIVATE: 
            VideoMultiVMR_OnActivate(hwnd, wParam, lParam);
            break;

        case WM_LBUTTONDBLCLK: 
            VideoMultiVMR_OnDblClk(hwnd, wParam, lParam);
            // IMPORTANT - let this drop through to DefWindowProc

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0L;
}


