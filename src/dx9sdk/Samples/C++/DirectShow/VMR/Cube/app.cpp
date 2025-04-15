//------------------------------------------------------------------------------
// File: app.cpp
//
// Desc: DirectShow sample code - VMR-based Cube video player
//
// Copyright (c) 1994 - 2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"
#include "vmrutil.h"

#include <commctrl.h>
#include <initguid.h>
#include <atlbase.h>
#include "resource.h"

#include <stdarg.h>
#include <stdio.h>


/* -------------------------------------------------------------------------
** Global variables that are initialized at run time and then stay constant.
** -------------------------------------------------------------------------
*/
HINSTANCE           g_hInst=0;
HICON               g_hIconCube=0;
HWND                g_hwndApp=0;
HWND                g_hwndToolbar=0;
CMovie*             g_pMovie;

namespace {
BOOL m_bFullScreen = FALSE;

};

/* -------------------------------------------------------------------------
** Constants
** -------------------------------------------------------------------------
*/
const TCHAR szClassName[] = TEXT("VMR_CubePlayer_CLASS");
const TCHAR g_szNULL[]    = TEXT("\0");
const TCHAR g_szEmpty[]   = TEXT("");

/*
** User interface values
*/
      int   dyToolbar;
const int   dxBitmap        = 16;
const int   dyBitmap        = 15;
const int   dxButtonSep     = 8;
const TCHAR g_chNULL        = TEXT('\0');
const LONG  g_Style         = WS_THICKFRAME | WS_POPUP | WS_CAPTION  |
                              WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
                              WS_CLIPCHILDREN;

#ifdef _WIN64
#define RESERVED    0,0,0,0,0,0  /* BYTE bReserved[6]  // padding for alignment */

#else
#define RESERVED    0,0          /* BYTE bReserved[2]  // padding for alignment */
#endif

const TBBUTTON tbButtons[DEFAULT_TBAR_SIZE] = {
    { IDX_SEPARATOR,    1,                    0,               TBSTYLE_SEP           },
    { IDX_1,            IDM_MOVIE_PLAY,       TBSTATE_ENABLED, TBSTYLE_BUTTON, RESERVED, 0, -1 },
    { IDX_2,            IDM_MOVIE_PAUSE,      TBSTATE_ENABLED, TBSTYLE_BUTTON, RESERVED, 0, -1 },
    { IDX_3,            IDM_MOVIE_STOP,       TBSTATE_ENABLED, TBSTYLE_BUTTON, RESERVED, 0, -1 },
    { IDX_SEPARATOR,    1,                    0,               TBSTYLE_SEP           },
    { IDX_4,            IDM_MOVIE_FULL_SCREEN,TBSTATE_ENABLED, TBSTYLE_CHECK,  RESERVED, 0, -1 }
};


/* -------------------------------------------------------------------------
** Local function prototypes
** -------------------------------------------------------------------------
*/
void ToggleFullScreen();
BOOL IsFullScreenMode();
LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


/******************************Public*Routine******************************\
* WinMain
*
*
* Windows recognizes this function by name as the initial entry point
* for the program.  This function calls the application initialization
* routine, and then executes a message
* retrieval and dispatch loop that is the top-level control structure
* for the remainder of execution.  The loop is terminated when a WM_QUIT
* message is received, at which time this function exits the application
* instance by returning the value passed by PostQuitMessage().
*
* If this function must abort before entering the message loop, it
* returns the conventional value NULL.
*
\**************************************************************************/
int PASCAL
WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLineOld,
    int nCmdShow
    )
{
    USES_CONVERSION;

    HRESULT hres = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if(hres == S_FALSE)
    {
        CoUninitialize();
    }

    if(!InitApplication(hInstance))
    {
        return FALSE;
    }
    
    if(!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    /* Verify that the VMR is present on this system */
    if(!VerifyVMR())
        return FALSE;

    /*
    ** Acquire and dispatch messages until a WM_QUIT message is received.
    */
    int iRet = DoMainLoop();
    QzUninitialize();
    return iRet;
}


/*****************************Private*Routine******************************\
* DoMainLoop
*
* Process the main message loop
*
\**************************************************************************/
int
DoMainLoop(
    void
    )
{
    MSG         msg;
    HANDLE      ahObjects[8];
    int         cObjects;
    HACCEL      haccel = LoadAccelerators(g_hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

    //
    // message loop lasts until we get a WM_QUIT message
    //
    for(;;)
    {
        if(g_pMovie != NULL)
        {
            cObjects = 1;
            ahObjects[0] = g_pMovie->GetMovieEventHandle();
        }
        else
        {
            ahObjects[0] = NULL;
            cObjects = 0;
        }

        if(ahObjects[0] == NULL)
        {
            WaitMessage();
        }
        else
        {
            //
            // wait for any message sent or posted to this queue
            // or for a graph notification
            //
            DWORD result;

            result = MsgWaitForMultipleObjects(cObjects, ahObjects, FALSE,
                                               INFINITE, QS_ALLINPUT);
            if(result != (WAIT_OBJECT_0 + cObjects))
            {
                Cube_OnGraphNotify(result - WAIT_OBJECT_0);
                continue;
            }
        }

        //
        // When here, we either have a message or no event handle
        // has been created yet.
        //
        // read all of the messages in this next loop
        // removing each message as we read it
        //
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                return (int) msg.wParam;
            }

            if(!TranslateAccelerator(g_hwndApp, haccel, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

} // DoMainLoop


/*****************************Private*Routine******************************\
* InitApplication(HANDLE)
*
* This function is called at initialization time only if no other
* instances of the application are running.  This function performs
* initialization tasks that can be done once for any number of running
* instances.
*
* In this case, we initialize a window class by filling out a data
* structure of type WNDCLASS and calling the Windows RegisterClass()
* function.  Since all instances of this application use the same window
* class, we only need to do this when the first instance is initialized.
*
\**************************************************************************/
BOOL
InitApplication(
    HINSTANCE hInstance
    )
{
    WNDCLASS  wc;

    /*
    ** Fill in window class structure with parameters that describe the
    ** main window.
    */
    g_hIconCube   = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_VIDEOCD_ICON));

    wc.style         = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc   = CubeWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = g_hIconCube;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)NULL;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAIN_MENU);
    wc.lpszClassName = szClassName;

    /*
    ** Register the window class and return success/failure code.
    */
    return RegisterClass(&wc);
}


/*****************************Private*Routine******************************\
* InitInstance
*
* This function is called at initialization time for every instance of
* this application.  This function performs initialization tasks that
* cannot be shared by multiple instances.
*
* In this case, we save the instance handle in a static variable and
* create and display the main program window.
*
\**************************************************************************/
BOOL
InitInstance(
    HINSTANCE hInstance,
    int nCmdShow
    )
{
    HWND    hwnd;
    TCHAR   title[100];

    /*
    ** Save the instance handle in static variable, which will be used
    ** in many subsequent calls to Windows.
    */
    g_hInst = hInstance;
    
    /*
    ** Create a main window for this application instance.
    */
    hwnd = CreateWindow(szClassName, IdStr(STR_APP_TITLE, title, sizeof title), g_Style,
                        100, 100,
                        400, 400,
                        NULL, NULL, hInstance, NULL);

    /*
    ** If window could not be created, return "failure"
    */
    if(NULL == hwnd)
    {
        return FALSE;
    }
    g_hwndApp = hwnd;

    /*
    ** Make the window visible; update its client area; and return "success"
    */
    SetPlayButtonsEnableState();
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return TRUE;
}


/*****************************Private*Routine******************************\
* GetMoviePosition
*
* Place the movie in the centre of the client window.  
* We do not stretch the the movie yet.
*
\**************************************************************************/
void
GetMoviePosition(
    HWND hwnd,
    long* xPos,
    long* yPos,
    long* pcx,
    long* pcy
    )
{
    RECT rc;

    GetAdjustedClientRect(&rc);

    *xPos = rc.left;
    *yPos = rc.top;
    *pcx = rc.right - rc.left;
    *pcy = rc.bottom - rc.top;
}


/******************************Public*Routine******************************\
* RepositionMovie
*
\**************************************************************************/
void
RepositionMovie(HWND hwnd)
{
    if(g_pMovie)
    {
        long xPos, yPos, cx, cy;

        GetMoviePosition(hwnd, &xPos, &yPos, &cx, &cy);

        g_pMovie->PutMoviePosition(xPos, yPos, cx, cy);
        InvalidateRect(hwnd, NULL, false);
        UpdateWindow(hwnd);
    }
}


/*****************************Private*Routine******************************\
* Cube_OnMove
*
\**************************************************************************/
void
Cube_OnMove(
    HWND hwnd,
    int x,
    int y
    )
{
    if(g_pMovie)
    {
        if(g_pMovie->GetStateMovie() != State_Running)
        {
            RepositionMovie(hwnd);
        }
        else
        {
            long xPos, yPos, cx, cy;

            // Reposition movie but don't invalidate the rect, since
            // the next video frame will handle the redraw.
            GetMoviePosition(hwnd, &xPos, &yPos, &cx, &cy);
            g_pMovie->PutMoviePosition(xPos, yPos, cx, cy);
        }
    }
}


/******************************Public*Routine******************************\
* CubeWndProc
*
\**************************************************************************/
LRESULT CALLBACK
CubeWndProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
    )
{
    switch(message)
    {
        HANDLE_MSG(hwnd, WM_CREATE,            Cube_OnCreate);
        HANDLE_MSG(hwnd, WM_PAINT,             Cube_OnPaint);
        HANDLE_MSG(hwnd, WM_COMMAND,           Cube_OnCommand);
        HANDLE_MSG(hwnd, WM_CLOSE,             Cube_OnClose);
        HANDLE_MSG(hwnd, WM_DESTROY,           Cube_OnDestroy);
        HANDLE_MSG(hwnd, WM_SIZE,              Cube_OnSize);
        HANDLE_MSG(hwnd, WM_SYSCOLORCHANGE,    Cube_OnSysColorChange);
        HANDLE_MSG(hwnd, WM_INITMENUPOPUP,     Cube_OnInitMenuPopup);
        HANDLE_MSG(hwnd, WM_NOTIFY,            Cube_OnNotify);
        HANDLE_MSG(hwnd, WM_KEYUP,             Cube_OnKeyUp);
        HANDLE_MSG(hwnd, WM_MOVE,              Cube_OnMove);

        case WM_DISPLAYCHANGE:
        {
            if(g_pMovie)
            {
                g_pMovie->DisplayModeChanged();
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0L;
}


/*****************************Private*Routine******************************\
* Cube_OnCreate
*
\**************************************************************************/
BOOL
Cube_OnCreate(
    HWND hwnd,
    LPCREATESTRUCT lpCreateStruct
    )
{
    InitCommonControls();

    /*
    ** Create the toolbar and statusbar.
    */
    g_hwndToolbar = CreateToolbarEx(hwnd,
                                    WS_VISIBLE | WS_CHILD |
                                    TBSTYLE_TOOLTIPS | CCS_NODIVIDER | TBSTYLE_FLAT,
                                    ID_TOOLBAR, NUMBER_OF_BITMAPS,
                                    g_hInst, IDR_TOOLBAR, tbButtons,
                                    DEFAULT_TBAR_SIZE, dxBitmap, dyBitmap,
                                    dxBitmap, dyBitmap, sizeof(TBBUTTON));
    if(g_hwndToolbar == NULL)
    {
        return FALSE;
    }

    return TRUE;
}


/*****************************Private*Routine******************************\
* Cube_OnKeyUp
*
\**************************************************************************/
void
Cube_OnKeyUp(
    HWND hwnd,
    UINT vk,
    BOOL fDown,
    int cRepeat,
    UINT flags
    )
{
    // Catch escape sequences to stop fullscreen mode
    if((vk == VK_ESCAPE) || (vk == VK_RETURN))
    {
        if(g_pMovie && IsFullScreenMode())
        {
            ToggleFullScreen();
            SetPlayButtonsEnableState();
        }
    }
}


/*****************************Private*Routine******************************\
* Cube_OnPaint
*
\**************************************************************************/
void
Cube_OnPaint(
    HWND hwnd
    )
{
    PAINTSTRUCT ps;
    HDC         hdc;
    RECT        rc1, rc2;

    /*
    ** Draw a frame around the movie playback area.
    */
    GetClientRect(hwnd, &rc2);

    hdc = BeginPaint(hwnd, &ps);

    if(g_pMovie)
    {
        long xPos, yPos, cx, cy;
        GetMoviePosition(hwnd, &xPos, &yPos, &cx, &cy);
        SetRect(&rc1, xPos, yPos, xPos + cx, yPos + cy);

        HRGN rgnClient = CreateRectRgnIndirect(&rc2);
        HRGN rgnVideo  = CreateRectRgnIndirect(&rc1);
        CombineRgn(rgnClient, rgnClient, rgnVideo, RGN_DIFF);

        HBRUSH hbr = GetSysColorBrush(COLOR_BTNFACE);
        FillRgn(hdc, rgnClient, hbr);
        DeleteObject(hbr);
        DeleteObject(rgnClient);
        DeleteObject(rgnVideo);

        g_pMovie->RepaintVideo(hwnd, hdc);
    }
    else
    {
        FillRect(hdc, &rc2, (HBRUSH)(COLOR_BTNFACE + 1));
    }

    EndPaint(hwnd, &ps);
}


/*****************************Private*Routine******************************\
* AboutDlgProc
*
\**************************************************************************/
LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            if(wParam == IDOK)
            {
                EndDialog(hWnd, TRUE);
                return TRUE;
            }
            break;
    }

    return FALSE;
}


/*****************************Private*Routine******************************\
* Cube_OnCommand
*
\**************************************************************************/
void
Cube_OnCommand(
    HWND hwnd,
    int id,
    HWND hwndCtl,
    UINT codeNotify
    )
{
    switch(id)
    {
        case IDM_FILE_OPEN:
            if(CubeOpenCmd())
                CubePlayCmd();
            break;

        case IDM_FILE_CLOSE:
            CubeCloseCmd();
            QzFreeUnusedLibraries();
            break;

        case IDM_FILE_ABOUT:
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX),
                hwnd,  (DLGPROC) AboutDlgProc);
            break;

        case IDM_FILE_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0L);
            break;

        case IDM_MOVIE_PLAY:
            CubePlayCmd();
            break;

        case IDM_MOVIE_STOP:
            CubeStopCmd();
            CubeRewindCmd();
            break;

        case IDM_MOVIE_PAUSE:
            CubePauseCmd();
            break;

        case IDM_MOVIE_FULL_SCREEN:
            if(g_pMovie)
            {
                ToggleFullScreen();
            }
            break;
    }

    SetPlayButtonsEnableState();
}


/******************************Public*Routine******************************\
* Cube_OnDestroy
*
\**************************************************************************/
void
Cube_OnDestroy(
    HWND hwnd
    )
{
    PostQuitMessage(0);
}


/******************************Public*Routine******************************\
* Cube_OnClose
*
\**************************************************************************/
void
Cube_OnClose(
    HWND hwnd
    )
{
    CubeCloseCmd();
    DestroyWindow(hwnd);
}


/******************************Public*Routine******************************\
* Cube_OnSize
*
\**************************************************************************/
void
Cube_OnSize(
    HWND hwnd,
    UINT state,
    int dx,
    int dy
    )
{
    if(IsWindow(g_hwndToolbar))
        SendMessage(g_hwndToolbar, WM_SIZE, 0, 0L);

    RepositionMovie(hwnd);
}


/*****************************Private*Routine******************************\
* Cube_OnSysColorChange
*
\**************************************************************************/
void
Cube_OnSysColorChange(
    HWND hwnd
    )
{
    FORWARD_WM_SYSCOLORCHANGE(g_hwndToolbar, SendMessage);
}


/*****************************Private*Routine******************************\
* Cube_OnInitMenuPopup
*
\**************************************************************************/
void
Cube_OnInitMenuPopup(
    HWND hwnd,
    HMENU hMenu,
    UINT item,
    BOOL fSystemMenu
    )
{
    UINT uFlags;

    if(item == 0)
    { // File menu

        if( GetMovieMode() == MOVIE_NOTOPENED)
        {
            uFlags = (MF_BYCOMMAND | MF_GRAYED);
        }
        else
        {
            uFlags = (MF_BYCOMMAND | MF_ENABLED);
        }

        // Disable menu items until a movie is opened
        EnableMenuItem(hMenu, IDM_FILE_CLOSE, uFlags);
        EnableMenuItem(hMenu, IDM_MOVIE_STOP, uFlags);
        EnableMenuItem(hMenu, IDM_MOVIE_PLAY, uFlags);
        EnableMenuItem(hMenu, IDM_MOVIE_PAUSE, uFlags);
    }
}


/*****************************Private*Routine******************************\
* Cube_OnGraphNotify
*
* This is where we get any notifications from the filter graph.
*
\**************************************************************************/
void
Cube_OnGraphNotify(
    int stream
    )
{
    long lEventCode = g_pMovie->GetMovieEventCode();

    switch(lEventCode)
    {
        case EC_FULLSCREEN_LOST:
            SetPlayButtonsEnableState();
            break;

        case EC_USERABORT:
        case EC_ERRORABORT:
            CubeStopCmd();
            SetPlayButtonsEnableState();
            break;

        case EC_COMPLETE:
            CubeStopCmd();
            CubeRewindCmd();
            CubePlayCmd();
            break;

        default:
            break;
    }
}


/*****************************Private*Routine******************************\
* Cube_OnNotify
*
* This is where we get the text for tooltips
*
\**************************************************************************/
LRESULT
Cube_OnNotify(
    HWND hwnd,
    int idFrom,
    NMHDR FAR* pnmhdr
    )
{
    switch(pnmhdr->code)
    {
        case TTN_NEEDTEXT:
        {
            LPTOOLTIPTEXT   lpTt;
            lpTt = (LPTOOLTIPTEXT)pnmhdr;

            LoadString(g_hInst, (UINT) lpTt->hdr.idFrom, lpTt->szText,
                NUMELMS(lpTt->szText));
        }
        break;
    }

    return 0;
}


/******************************Public*Routine******************************\
* SetPlayButtonsEnableState
*
\**************************************************************************/
void
SetPlayButtonsEnableState(
    void
    )
{
    SendMessage(g_hwndToolbar, TB_ENABLEBUTTON, IDM_MOVIE_PLAY, 
        GetMovieMode() != MOVIE_NOTOPENED
        && GetMovieMode() != MOVIE_PLAYING );

    SendMessage(g_hwndToolbar, TB_ENABLEBUTTON, IDM_MOVIE_STOP, 
        GetMovieMode() != MOVIE_NOTOPENED
        && GetMovieMode() != MOVIE_STOPPED );

    // NOTE: pause button is enabled both when 
    // the movie is paused and when it's not
    // so people can press and depress the button
    SendMessage(g_hwndToolbar, TB_ENABLEBUTTON, IDM_MOVIE_PAUSE, 
        GetMovieMode() != MOVIE_NOTOPENED );
    SendMessage(g_hwndToolbar, TB_CHECKBUTTON, IDM_MOVIE_PAUSE, 
        MAKELONG(GetMovieMode() == MOVIE_PAUSED,0));

    SendMessage(g_hwndToolbar, TB_ENABLEBUTTON, IDM_MOVIE_FULL_SCREEN, 
        GetMovieMode() == MOVIE_PLAYING 
        || GetMovieMode() == MOVIE_PAUSED );
    SendMessage(g_hwndToolbar, TB_CHECKBUTTON, IDM_MOVIE_FULL_SCREEN, 
        MAKELONG(IsFullScreenMode(),0));
}


/*****************************Private*Routine******************************\
* GetAdjustedClientRect
*
* Calculate the size of the client rect and then adjusts it to take into
* account the space taken by the toolbar and status bar.
*
\**************************************************************************/
void
GetAdjustedClientRect(
    RECT *prc
    )
{
    RECT    rcTool;

    GetClientRect(g_hwndApp, prc);

    if(IsWindowVisible(g_hwndToolbar))
    {
        GetWindowRect(g_hwndToolbar, &rcTool);
        prc->top += (rcTool.bottom - rcTool.top);
    }
}


/******************************Public*Routine******************************\
* IdStr
*
* Loads the given string resource ID into the passed storage.
*
\**************************************************************************/
LPCTSTR
IdStr(
    int idResource,
    LPTSTR buffer,
    DWORD length
    )
{
    if( LoadString(g_hInst, idResource, buffer, length) == 0)
        return g_szEmpty;

    return buffer;
}


/******************************Public*Routine******************************\
* ToggleFullScreen
*
\**************************************************************************/
void
ToggleFullScreen( )
{
    // Defer until we activate the movie
    if(g_pMovie->GetStateMovie() != State_Running)
    {
        if( ! IsFullScreenMode() )
            return;
    }

    m_bFullScreen = ! m_bFullScreen ;

    static HMENU hMenu;
    static LONG  lStyle;
    static int xs, ys, cxs, cys;

    HDC hdcScreen = GetDC(NULL);
    int cx = GetDeviceCaps(hdcScreen,HORZRES);
    int cy = GetDeviceCaps(hdcScreen,VERTRES);
    ReleaseDC(NULL, hdcScreen);

    if( m_bFullScreen )
    {
        hMenu = GetMenu(g_hwndApp);
        lStyle = GetWindowStyle(g_hwndApp);

        WINDOWPLACEMENT wp;
        wp.length = sizeof(WINDOWPLACEMENT);
        GetWindowPlacement(g_hwndApp, &wp);

        xs = wp.rcNormalPosition.left;
        ys = wp.rcNormalPosition.top;
        cxs = wp.rcNormalPosition.right - xs;
        cys = wp.rcNormalPosition.bottom - ys;

        ShowWindow(g_hwndToolbar, SW_HIDE);
        SetMenu(g_hwndApp, NULL);
        SetWindowLong(g_hwndApp, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowPos(g_hwndApp, HWND_TOP, 0, 0, cx, cy, SWP_NOACTIVATE);
        ShowCursor(FALSE);
    }
    else
    {
        ShowCursor(TRUE);
        ShowWindow(g_hwndToolbar, SW_SHOW);
        SetMenu(g_hwndApp, hMenu);
        SetWindowLong(g_hwndApp, GWL_STYLE, lStyle);
        SetWindowPos(g_hwndApp, HWND_TOP, xs, ys, cxs, cys, SWP_NOACTIVATE);
    }
}


/******************************Public*Routine******************************\
* IsFullScreenMode()
*
\**************************************************************************/
BOOL
IsFullScreenMode()
{
    return m_bFullScreen;
}


EMovieMode GetMovieMode()
{
    if( g_pMovie )
    {
        return g_pMovie->GetMovieMode();
    }
    else
    {
        return MOVIE_NOTOPENED;
    }
}

