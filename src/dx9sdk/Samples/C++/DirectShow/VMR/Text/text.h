//------------------------------------------------------------------------------
// File: Text.h
//
// Desc: DirectShow sample code - header file for VMR Text sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


//
// Function prototypes
//
HRESULT InitPlayerWindow(void);
HRESULT InitVideoWindow(int nMultiplier, int nDivider);
HRESULT HandleGraphEvent(void);

BOOL GetClipFileName(LPTSTR szName);
BOOL CheckVideoVisibility(void);

void MoveVideoWindow(void);
void CloseInterfaces(void);
void OpenClip(void);
void CloseClip(void);
void GetFilename(TCHAR *pszFull, TCHAR *pszFile);
void Msg(TCHAR *szFormat, ...);

HRESULT BlendApplicationImage(HWND hwndApp);
HRESULT InitializeWindowlessVMR(void);
void OnPaint(HWND hwnd);

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);
void RemoveGraphFromRot(DWORD pdwRegister);

//
// Constants
//

// File filter for OpenFile dialog
#define FILE_FILTER_TEXT \
    TEXT("Video Files (*.asf; *.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.wmv)\0*.asf; *.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.wmv\0\0")

// Begin default media search at root directory
#define DEFAULT_MEDIA_PATH  TEXT("\\\0")

// Defaults used with audio-only files
#define DEFAULT_PLAYER_WIDTH    240
#define DEFAULT_PLAYER_HEIGHT   120
#define DEFAULT_VIDEO_WIDTH     320
#define DEFAULT_VIDEO_HEIGHT    240
#define MINIMUM_VIDEO_WIDTH     200
#define MINIMUM_VIDEO_HEIGHT    120

#define APPLICATIONNAME TEXT("VMR Text\0")
#define CLASSNAME       TEXT("VMRText\0")

#define WM_GRAPHNOTIFY  WM_USER+13

//
// Global data
//
extern HWND      ghApp;
extern HMENU     ghMenu;
extern HINSTANCE ghInst;
extern TCHAR     g_szFileName[MAX_PATH];
extern DWORD     g_dwGraphRegister;

// DirectShow interfaces
extern IGraphBuilder *pGB;
extern IMediaControl *pMC;
extern IVMRWindowlessControl *pWC;
extern IMediaControl *pMC;
extern IMediaEventEx *pME;
extern IMediaSeeking *pMS;

//
// Macros
//
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

#define JIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}

#define LIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr);}

//
// Resource constants
//
#define IDC_STATIC                      -1
#define IDI_TEXT                        100
#define IDR_MENU                        101
#define IDD_HELP_ABOUT                  200

#define ID_FILE_OPENCLIP                301
#define ID_FILE_EXIT                    302
#define ID_FILE_CLOSE                   303
#define ID_FILE_INITCLIP                304
#define ID_SET_FONT                     310
#define ID_HELP_ABOUT                   320

