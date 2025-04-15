//------------------------------------------------------------------------------
// File: Watermark.h
//
// Desc: DirectShow sample code - header file for video in window movie
//       player application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


//
// Function prototypes
//
HRESULT InitPlayerWindow(void);
HRESULT InitVideoWindow(int nMultiplier, int nDivider);
HRESULT HandleGraphEvent(void);
HRESULT StepOneFrame(void);
HRESULT StepFrames(int nFramesToStep);

BOOL GetClipFileName(LPTSTR szName);
BOOL CheckVideoVisibility(void);

void PaintAudioWindow(void);
void MoveVideoWindow(void);
void CloseInterfaces(void);

void OpenClip(void);
void PauseClip(void);
void StopClip(void);
void CloseClip(void);

HRESULT BlendApplicationImage(HWND hwndApp);
HRESULT InitializeWindowlessVMR(void);
void OnPaint(HWND hwnd);

void UpdateMainTitle(void);
void EnablePlaybackMenu(BOOL bEnable);
void GetFilename(TCHAR *pszFull, TCHAR *pszFile);
void Msg(TCHAR *szFormat, ...);

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);
void RemoveGraphFromRot(DWORD pdwRegister);

//
// Constants
//
#define VOLUME_FULL     0L
#define VOLUME_SILENCE  -10000L

#define BFT_BITMAP 0x4d42   /* 'BM' */

// File filter for OpenFile dialog
#define FILE_FILTER_TEXT \
    TEXT("Video Files (*.asf; *.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.wmv)\0*.asf; *.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.wmv\0\0")

// Begin default media search at root directory
#define DEFAULT_MEDIA_PATH  TEXT("\\\0")

// Defaults used with audio-only files
#define DEFAULT_AUDIO_WIDTH     240
#define DEFAULT_AUDIO_HEIGHT    120
#define DEFAULT_VIDEO_WIDTH     320
#define DEFAULT_VIDEO_HEIGHT    240
#define MINIMUM_VIDEO_WIDTH     200
#define MINIMUM_VIDEO_HEIGHT    120

#define APPLICATIONNAME TEXT("VMR Watermark\0")
#define CLASSNAME       TEXT("VMRWatermarkPlayer\0")

#define WM_GRAPHNOTIFY  WM_USER+13

#define MARK_FLIP       0x1
#define MARK_MIRROR     0x2
#define MARK_ANIMATE    0x4
#define MARK_SLIDE      0x8
#define MARK_STROBE     0x10
#define MARK_DISABLE    0x80

//
// Enumerated types
//
enum PLAYSTATE {Stopped, Paused, Running, Init};

//
// Global data
//
extern HWND      ghApp;
extern HMENU     ghMenu;
extern HINSTANCE ghInst;
extern TCHAR     g_szFileName[MAX_PATH];
extern LONG      g_lVolume;
extern DWORD     g_dwGraphRegister;
extern DWORD     g_dwWatermarkFlags;
extern PLAYSTATE g_psCurrent;

// DirectShow interfaces
extern IGraphBuilder *pGB;
extern IMediaControl *pMC;
extern IMediaEventEx *pME;
extern IBasicAudio   *pBA;
extern IMediaSeeking *pMS;
extern IVMRWindowlessControl *pWC;


//
// Macros
//
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

#define JIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}

#define LIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr);}

// DIB Macros
#define DibNumColors(lpbi)      ((lpbi)->biClrUsed == 0 && (lpbi)->biBitCount <= 8 \
                                    ? (int)(1 << (int)(lpbi)->biBitCount)          \
                                    : (int)(lpbi)->biClrUsed)

#define DibSize(lpbi)           ((lpbi)->biSize + (lpbi)->biSizeImage + (int)(lpbi)->biClrUsed * sizeof(RGBQUAD))

#define DibPaletteSize(lpbi)    (DibNumColors(lpbi) * sizeof(RGBQUAD))

//
// Resource constants
//
#define IDI_WATERMARK                   100
#define IDR_MENU                        101
#define IDR_VMR_WIDE                    102
#define IDD_ABOUTBOX                    200

#define ID_FILE_OPENCLIP                40001
#define ID_FILE_EXIT                    40002
#define ID_FILE_PAUSE                   40003
#define ID_FILE_STOP                    40004
#define ID_FILE_CLOSE                   40005
#define ID_FILE_MUTE                    40006
#define ID_FLIP                         40007
#define ID_MIRROR                       40008
#define ID_ANIMATE                      40009
#define ID_SLIDE                        40010
#define ID_DISABLE                      40011
#define ID_STROBE                       40012
#define ID_ALL_EFFECTS                  40013
#define ID_HELP_ABOUT                   40014
#define ID_NO_EFFECTS                   40015

