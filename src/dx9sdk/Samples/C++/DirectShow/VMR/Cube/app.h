//------------------------------------------------------------------------------
// File: app.h
//
// Desc: DirectShow sample code - prototypes for the Renderless player
//
// Copyright (c) 1994 - 2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

/* -------------------------------------------------------------------------
** Function prototypes
** -------------------------------------------------------------------------
*/
int DoMainLoop(void);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance,int nCmdShow);

void GetAdjustedClientRect(RECT *prc);

BOOL DrawStats(HDC hdc);
void CalcMovieRect(LPRECT lprc);

LPCTSTR IdStr(int idResource, LPTSTR buffer, DWORD length);
void UpdateSystemColors(void);

enum EMovieMode;
EMovieMode GetMovieMode();



/* -------------------------------------------------------------------------
** Message crackers
** -------------------------------------------------------------------------
*/
#define HANDLE_WM_USER(hwnd, wParam, lParam, fn) \
    ((fn)(hwnd, wParam, lParam), 0L)


/* -------------------------------------------------------------------------
** Cube Window handling messages
** -------------------------------------------------------------------------
*/
extern "C" LRESULT CALLBACK
CubeWndProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
    );

void
Cube_OnClose(
    HWND hwnd
    );

BOOL
Cube_OnQueryEndSession(
    HWND hwnd
    );

void
Cube_OnDestroy(
    HWND hwnd
    );

void
Cube_OnCommand(
    HWND hwnd,
    int id,
    HWND hwndCtl,
    UINT codeNotify
    );

void
Cube_OnPaint(
    HWND hwnd
    );

void
Cube_OnTimer(
    HWND hwnd,
    UINT id
    );

BOOL
Cube_OnCreate(
    HWND hwnd,
    LPCREATESTRUCT lpCreateStruct
    );

void
Cube_OnSize(
    HWND hwnd,
    UINT state,
    int cx,
    int cy
    );

void
Cube_OnKeyUp(
    HWND hwnd,
    UINT vk,
    BOOL fDown,
    int cRepeat,
    UINT flags
    );

void
Cube_OnHScroll(
    HWND hwnd,
    HWND hwndCtl,
    UINT code,
    int pos
    );

void
Cube_OnUser(
    HWND hwnd,
    WPARAM wParam,
    LPARAM lParam
    );

void
Cube_OnSysColorChange(
    HWND hwnd
    );

void
Cube_OnMenuSelect(
    HWND hwnd,
    HMENU hmenu,
    int item,
    HMENU hmenuPopup,
    UINT flags
    );

void
Cube_OnInitMenuPopup(
    HWND hwnd,
    HMENU hMenu,
    UINT item,
    BOOL fSystemMenu
    );

#ifdef WM_NOTIFY
LRESULT
Cube_OnNotify(
    HWND hwnd,
    int idFrom,
    NMHDR FAR* pnmhdr
    );
#endif

void
Cube_OnGraphNotify(
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
CubeSetLog(
    void
    );

BOOL
CubeSetPerfLogFile(
    void
    );

BOOL
CubeOpenCmd(
    void
    );

BOOL
CubeCloseCmd(
    void
    );

BOOL
CubePlayCmd(
    void
    );

BOOL
CubeStopCmd(
    void
    );

BOOL
CubePauseCmd(
    void
    );

BOOL
CubePauseCmd(
    void
    );

BOOL
CubeRewindCmd(
    void
    );

void
CubeSeekCmd(
    REFTIME rtSeekBy
    );

void
ProcessOpen(
    TCHAR achFileName[][MAX_PATH],
    DWORD dwNumFiles,
    BOOL bPlay = FALSE
    );


/* -------------------------------------------------------------------------
** Global Variables
** -------------------------------------------------------------------------
*/
extern int              g_cxMovie;
extern int              g_cyMovie;
extern HWND             g_hwndApp;

extern int              g_xOffset;
extern int              g_yOffset;
extern TCHAR            g_szPerfLog[];
extern int              g_TimeFormat;


/* -------------------------------------------------------------------------
** Constants
** -------------------------------------------------------------------------
*/
const DWORD LEFT_MARGIN = 0;
const DWORD MAXSTREAMS = 3;

enum {PerformanceTimer = 32, StatusTimer = 33};
