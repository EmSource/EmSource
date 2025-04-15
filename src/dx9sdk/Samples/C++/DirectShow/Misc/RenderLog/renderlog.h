//------------------------------------------------------------------------------
// File: RenderLog.h
//
// Desc: DirectShow sample code - header file for RenderFile logger sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

//
// Function prototypes
//
HRESULT InitVideoWindow(int nWindowType);
BOOL GetClipFileName(LPTSTR szName);

void PaintAudioWindow(void);
void MoveVideoWindow(void);
void CheckVisibility(void);
void CloseInterfaces(void);

void OpenClip(void);
void PauseClip(void);
void CloseClip(void);
void ViewRenderLog(void);
void ClearRenderLog(void);
void SetRenderLog(void);

void GetFilename(TCHAR *pszFull, TCHAR *pszFile);
void Msg(TCHAR *szFormat, ...);

//
// Constants
//

// File filter for OpenFile dialog
#define FILE_FILTER_TEXT \
    TEXT("Media Files (*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.jpg; *.gif; *.bmp; *.tga; *.wav; *.mpa; *.mp2; *.mp3; *.au; *.aif; *.aiff; *.snd)\0*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.jpg; *.gif; *.bmp; *.tga; *.wav; *.mpa; *.mp2; *.mp3; *.au; *.aif; *.aiff; *.snd\0")\
    TEXT("Video Files (*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v)\0*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v\0")\
    TEXT("Audio files (*.wav; *.mpa; *.mp2; *.mp3; *.au; *.aif; *.aiff; *.snd)\0*.wav; *.mpa; *.mp2; *.mp3; *.au; *.aif; *.aiff; *.snd\0")\
    TEXT("MIDI Files (*.mid, *.midi, *.rmi)\0*.mid; *.midi; *.rmi\0") \
    TEXT("Image Files (*.jpg, *.bmp, *.gif, *.tga)\0*.jpg; *.bmp; *.gif; *.tga\0") \
    TEXT("All Files (*.*)\0*.*;\0\0")

#define LOG_FILTER_TEXT   TEXT("Log Files (*.txt; *.log)\0*.txt; *.log\0All Files (*.*)\0*.*\0\0")

// Begin default media search at root directory
#define DEFAULT_MEDIA_PATH  TEXT("c:\\\0")
#define DEFAULT_LOG_PATH    TEXT("c:\\\0")
#define DEFAULT_LOG_FILE    TEXT("RenderFileLog.txt\0")

// Window defaults
#define DEFAULT_WIDTH           240
#define DEFAULT_HEIGHT          120
#define DEFAULT_VIDEO_WIDTH     320
#define DEFAULT_VIDEO_HEIGHT    240
#define MINIMUM_VIDEO_WIDTH     200
#define MINIMUM_VIDEO_HEIGHT    120

#define WINDOW_DEFAULT  0
#define WINDOW_VIDEO    1

#define APPLICATIONNAME TEXT("RenderLog Sample\0")
#define CLASSNAME       TEXT("RenderLogSample\0")

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
#define IDI_RENDERLOG                   100
#define IDR_MENU                        101
#define IDD_ABOUTBOX                    200
#define ID_FILE_OPENCLIP                301
#define ID_FILE_CLOSE                   302
#define ID_FILE_EXIT                    303
#define ID_FILE_INITCLIP                304
#define ID_VIEWLOG                      310
#define ID_CLEARLOG                     311
#define ID_SETLOG                       312
#define ID_ALWAYS_DISPLAY_LOG           320
#define ID_ALWAYS_CLEAR_LOG             321
#define ID_HELP_ABOUT                   330

