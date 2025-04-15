//------------------------------------------------------------------------------
// File: VMRPip.h
//
// Desc: DirectShow sample code - header file for VMR PIP sample
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
void CloseFiles(void);
void OpenFiles(void);
void GetFilename(TCHAR *pszFull, TCHAR *pszFile);
void Msg(TCHAR *szFormat, ...);

HRESULT InitializeWindowlessVMR(void);
HRESULT BlendVideo(LPTSTR szFile1, LPTSTR szFile2);
void SetNextQuadrant(int nStream);
void OnPaint(HWND hwnd);
void EnableMenus(BOOL bEnable);

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);
void RemoveGraphFromRot(DWORD pdwRegister);

LRESULT CALLBACK FilesDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
// Constants
//

// File filter for OpenFile dialog
#define FILE_FILTER_TEXT \
    TEXT("Video Files (*.asf; *.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.wmv)\0*.asf; *.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.wmv\0\0")

// Begin default media search at root directory
#define DEFAULT_MEDIA_PATH  TEXT("\\\0")

// Default window sizes
#define DEFAULT_PLAYER_WIDTH    260
#define DEFAULT_PLAYER_HEIGHT   120
#define DEFAULT_VIDEO_WIDTH     320
#define DEFAULT_VIDEO_HEIGHT    240
#define MINIMUM_VIDEO_WIDTH     200
#define MINIMUM_VIDEO_HEIGHT    120

#define APPLICATIONNAME TEXT("VMR Picture-In-Picture\0")
#define CLASSNAME       TEXT("VMRPIP\0")

#define WM_GRAPHNOTIFY  WM_USER+1

//
// Global data
//
extern HWND      ghApp;
extern HMENU     ghMenu;
extern HINSTANCE ghInst;
extern DWORD     g_dwGraphRegister;

// DirectShow interfaces
extern IGraphBuilder *pGB;
extern IMediaControl *pMC;
extern IVMRWindowlessControl *pWC;
extern IMediaControl *pMC;
extern IMediaEventEx *pME;
extern IMediaSeeking *pMS;
extern IVMRMixerControl *pMix;

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
#define IDI_SAMPLE                      100
#define IDR_MENU                        101

#define ID_FILE_OPENCLIPS               300
#define ID_FILE_EXIT                    301
#define ID_FILE_CLOSE                   302
#define ID_HELP_ABOUT                   303

#define IDD_DIALOG_FILES                400
#define IDD_HELP_ABOUT                  401

#define IDM_TOPLEFT                     500
#define IDM_TOPRIGHT                    501
#define IDM_BOTTOMRIGHT                 502
#define IDM_BOTTOMLEFT                  503
#define IDM_NEXTQUADRANT                504
#define IDM_LARGER                      505
#define IDM_SMALLER                     506
#define IDM_CENTER                      507
#define IDM_SWAP                        508
#define IDM_SWAP_ANIMATE                509

#define IDM_MIRROR_PRIMARY              510
#define IDM_MIRROR_SECONDARY            511
#define IDM_FLIP_PRIMARY                512
#define IDM_FLIP_SECONDARY              513

#define IDC_BUTTON_FILE1                600
#define IDC_BUTTON_FILE2                601
#define IDC_EDIT_FILE1                  602
#define IDC_EDIT_FILE2                  603

