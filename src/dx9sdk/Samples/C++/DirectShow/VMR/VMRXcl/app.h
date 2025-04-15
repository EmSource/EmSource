//----------------------------------------------------------------------------
//  File:   app.h
//
//  Desc:   DirectShow sample code
//          Header file for customized video player application
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

/* -------------------------------------------------------------------------
** Function prototypes
** -------------------------------------------------------------------------
*/
int DoMainLoop(void);

BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
BOOL DrawStats(HDC hdc);

void GetAdjustedClientRect(RECT *prc);
void CalcMovieRect(LPRECT lprc);
void UpdateSystemColors(void);

LPCTSTR IdStr(int idResource);


/* -------------------------------------------------------------------------
** Message crackers
** -------------------------------------------------------------------------
*/
#define HANDLE_WM_USER(hwnd, wParam, lParam, fn) \
    ((fn)(hwnd, wParam, lParam), 0L)

#ifndef HANDLE_WM_NOTIFY
#define HANDLE_WM_NOTIFY(hwnd, wParam, lParam, fn) \
    (fn)((hwnd), (int)(wParam), (NMHDR FAR*)(lParam))
#endif


/* -------------------------------------------------------------------------
** VideoCd window class prototypes
** -------------------------------------------------------------------------
*/
extern "C" LRESULT CALLBACK
VideoCdWndProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
    );

void
VideoCd_OnClose(
    HWND hwnd
    );

BOOL
VideoCd_OnQueryEndSession(
    HWND hwnd
    );

void
VideoCd_OnDestroy(
    HWND hwnd
    );

void
VideoCd_OnClick(
    HWND hwnd,
    WPARAM pParam,
    LPARAM lParam);

void
VideoCd_OnClickHold(
    HWND hwnd,
    WPARAM pParam,
    LPARAM lParam);

void
VideoCd_OnCommand(
    HWND hwnd,
    int id,
    HWND hwndCtl,
    UINT codeNotify
    );

void
VideoCd_OnPaint(
    HWND hwnd
    );

void
VideoCd_OnTimer(
    HWND hwnd,
    UINT id
    );

BOOL
VideoCd_OnCreate(
    HWND hwnd,
    LPCREATESTRUCT lpCreateStruct
    );

void
VideoCd_OnSize(
    HWND hwnd,
    UINT state,
    int cx,
    int cy
    );

void
VideoCd_OnKeyUp(
    HWND hwnd,
    UINT vk,
    BOOL fDown,
    int cRepeat,
    UINT flags
    );

void
VideoCd_OnHScroll(
    HWND hwnd,
    HWND hwndCtl,
    UINT code,
    int pos
    );

void
VideoCd_OnUser(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    );

void
VideoCd_OnSysColorChange(
    HWND hwnd
    );

void
VideoCd_OnMenuSelect(
    HWND hwnd,
    HMENU hmenu,
    int item,
    HMENU hmenuPopup,
    UINT flags
    );

void
VideoCd_OnInitMenuPopup(
    HWND hwnd,
    HMENU hMenu,
    UINT item,
    BOOL fSystemMenu
    );

#ifdef WM_NOTIFY
LRESULT
VideoCd_OnNotify(
    HWND hwnd,
    int idFrom,
    NMHDR FAR* pnmhdr
    );
#endif


void
VideoCd_OnGraphNotify(
    int stream
    );

void
SetPlayButtonsEnableState(
    void
    );


/* -------------------------------------------------------------------------
** Command processing functions
** -------------------------------------------------------------------------
*/
BOOL
VcdPlayerSetLog(
    void
    );

BOOL
VcdPlayerSetPerfLogFile(
    void
    );

BOOL
VcdPlayerOpenCmd(
    void
    );

BOOL
VcdPlayerCloseCmd(
    void
    );

BOOL
VcdPlayerPlayCmd(
    void
    );

BOOL
VcdPlayerStopCmd(
    void
    );

BOOL
VcdPlayerPauseCmd(
    void
    );

BOOL
VcdPlayerPauseCmd(
    void
    );

void
VcdPlayerSeekCmd(
    REFTIME rtSeekBy
    );

BOOL
ProcessOpen(
    TCHAR *achFileName,
    BOOL bPlay = FALSE
    );


/* -------------------------------------------------------------------------
** Global Variables
** -------------------------------------------------------------------------
*/
extern int              cxMovie;
extern int              cyMovie;
extern HWND             hwndApp;

extern int              xOffset;
extern int              yOffset;
extern DWORD            g_State;
extern TCHAR            g_szPerfLog[];
extern int              g_TimeFormat;


/* -------------------------------------------------------------------------
** Constants
** -------------------------------------------------------------------------
*/
#define LEFT_MARGIN 0


/* -------------------------------------------------------------------------
** Player states: these are bit flags
** -------------------------------------------------------------------------
*/
#define VCD_PLAYING          0x0001
#define VCD_STOPPED          0x0002
#define VCD_PAUSED           0x0004
#define VCD_SKIP_F           0x0008
#define VCD_SKIP_B           0x0010
#define VCD_FF               0x0020
#define VCD_RW               0x0040
#define VCD_SEEKING          (VCD_FF | VCD_RW)
#define VCD_LOADED           0x0080
#define VCD_NO_CD            0x0100
#define VCD_DATA_CD_LOADED   0x0200
#define VCD_EDITING          0x0400
#define VCD_PAUSED_AND_MOVED 0x0800
#define VCD_PLAY_PENDING     0x1000
#define VCD_WAS_PLAYING      0x2000
#define VCD_IN_USE           0x4000


