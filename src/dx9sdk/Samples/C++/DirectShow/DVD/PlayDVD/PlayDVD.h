//------------------------------------------------------------------------------
// File: PlayDVD.h
//
// Desc: DirectShow sample code - header file for simple DVD player sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include <dshow.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <tchar.h>
#include <atlbase.h>

#include <Il21dec.h>

#include "resource.h"

//
// Function prototypes
//
HRESULT InitPlayerWindow(void);
HRESULT InitVideoWindow(int nMultiplier, int nDivider);
HRESULT HandleGraphEvent(void);
HRESULT StepOneFrame(void);
HRESULT ModifyRate(double dRateAdjust);
HRESULT SetRate(double dRate);

BOOL GetFrameStepInterface(void);
BOOL GetClipFileName(LPTSTR szName);

void MoveVideoWindow(void);
void CloseInterfaces(void);
void GetMenuHandles(void);

void OpenDVDVolume(void);
void PauseDVD(void);
void PlayDVD(void);
void StopDVD(void);
void CloseDVDVolume(void);
void HandleDiscEject(void);

HRESULT RenderDVD(void);
HRESULT ToggleMute();
HRESULT SetFullScreen(void);
HRESULT ClearFullScreen(void);

void UpdateMainTitle(void);
void CheckSizeMenu(WPARAM wParam);
void EnablePlaybackMenu(BOOL bEnable);
void EnableAngleMenu(BOOL bEnable);
void EnableOptionsMenus(BOOL bEnable);
void EnableStopDomainMenus(BOOL bEnable);
void Msg(TCHAR *szFormat, ...);
void ResetRate(void);

DWORD GetStatusText(AM_DVD_RENDERSTATUS *pStatus, PTSTR pszStatusText, DWORD dwMaxText);

LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);
void RemoveGraphFromRot(DWORD pdwRegister);

void HandleDVDCommand(WPARAM wParam, LPARAM lParam);
void SetDVDVideoMode(WPARAM wParam, LPARAM lParam);

HRESULT SetDVDPlaybackOptions();
LRESULT OnMouseEvent(UINT uMessage, WPARAM wParam, LPARAM lParam);
LRESULT OnDvdEvent(LONG lEvent, LONG lParam1, LONG lParam2);

void ToggleCaptioning(void);
void EnableSubpicture(BOOL bEnable);
void EnablePresentationMenuItem(int nItem, BOOL bEnable);
void CheckSubmenuMessage(WPARAM wParam, LPARAM lParam);
void ReadDVDInformation(void);

HRESULT GetSubpictureInfo();
HRESULT GetAudioInfo();
HRESULT GetAngleInfo();
HRESULT GetTitleInfo();
HRESULT GetPresentationCaps();
HRESULT GetMenuLanguageInfo();

HRESULT UpdateAudioInfo();
HRESULT UpdateAngleInfo();
HRESULT UpdateSubpictureInfo();
HRESULT UpdateChapterCount(ULONG ulCurTitle);
HRESULT UpdateCurrentChapter(ULONG ulCurChapter);

void UpdateCurrentTitle(ULONG ulCurTitle);
void ClearSubmenu(HMENU hMenu);
void ConfigureChapterMenu(void);
void ShowValidUOPS(TCHAR *szAttemptedAction);

HRESULT SetAudioStream(int nStream);
HRESULT SetAngle(int nAngle);
HRESULT SetPresentationMode(int nMode);
HRESULT SetTitle(int nTitle);
HRESULT SetChapter(int nChapter);
HRESULT SetMenuLanguage(int nLanguageIndex);
HRESULT SetSubpictureStream(int nStream);


// An application can advertise the existence of its filter graph
// by registering the graph with a global Running Object Table (ROT).
// The GraphEdit application can detect and remotely view the running
// filter graph, allowing you to 'spy' on the graph with GraphEdit.
//
// To enable registration in this sample, define REGISTER_FILTERGRAPH.
//
#define REGISTER_FILTERGRAPH

//
// Constants
//
#define VOLUME_FULL     0L
#define VOLUME_SILENCE  -10000L

#define MAX_SCAN_RATE   16

// Defaults used with audio-only files
#define DEFAULT_WINDOW_WIDTH    300
#define DEFAULT_WINDOW_HEIGHT   120
#define DEFAULT_VIDEO_WIDTH     320
#define DEFAULT_VIDEO_HEIGHT    240
#define MINIMUM_VIDEO_WIDTH     300
#define MINIMUM_VIDEO_HEIGHT    120

#define APPLICATIONNAME TEXT("PlayDVD\0")
#define CLASSNAME       TEXT("PlayDVDPlayer\0")

#define WM_GRAPHNOTIFY  WM_USER+13

//
// Enumerated types
//
enum MENUS         {emFile, emControl, emNavigate, emOptions, emRate, emHelp};
enum OPT_SUBMENUS  {esmAngle, esmAudio, esmMenuLanguage, esmPresentation, esmSubpicture};
enum NAV_SUBMENUS  {esmTitle=9, esmChapter};
enum CONTROL_SUBMENUS {esmPlay, esmPause, esmStop, esmMute, esmFrameStep};
enum PLAYSTATE {Stopped, Paused, Running, Init};

//
// Macros
//
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

#define JIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}

#define LIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr);}

// External data
extern HWND      ghApp;
extern HMENU     ghMenu;
extern HINSTANCE ghInst;
extern BOOL      g_bFullscreen;
extern LONG      g_lVolume;
extern DWORD     g_dwGraphRegister;
extern PLAYSTATE g_psCurrent;
extern double    g_PlaybackRate;

extern HMENU     ghNavigateMenu, ghOptionsMenu, ghTitleMenu, ghChapterMenu;
extern HMENU     ghAngleMenu, ghAudioMenu, ghMenuLanguageMenu;
extern HMENU     ghPresentationMenu, ghSubpictureMenu, ghControlMenu;

// DirectShow interfaces
extern IGraphBuilder   *pGB;
extern IMediaControl   *pMC;
extern IMediaEventEx   *pME;
extern IVideoWindow    *pVW;
extern IBasicAudio     *pBA;
extern IBasicVideo     *pBV;
extern IMediaSeeking   *pMS;
extern IMediaPosition  *pMP;
extern IVideoFrameStep *pFS;

// DVD interfaces
extern IDvdGraphBuilder *pDvdGB;
extern IDvdControl2     *pDvdControl;
extern IDvdInfo2        *pDvdInfo ;
extern IAMLine21Decoder *pLine21Dec;
extern LCID             *g_pLanguageList;

// DVD information
extern ULONG g_ulCurChapter, g_ulNumChapters;
extern ULONG g_ulCurTitle, g_ulNumTitles;
extern DVD_HMSF_TIMECODE g_CurTime;
extern bool g_bStillOn, g_bMenuOn;
extern DVD_DOMAIN g_DVDDomain;
extern ULONG g_ulValidUOPS;

extern BOOL g_bDisplayCC, g_bDisplaySubpicture;


// Error message displayed if no DVD decoder is installed
#define MSG_NO_DECODER  \
        TEXT("The DVD sample could not locate a DVD decoder on your system.\r\n\r\n")     \
        TEXT("You must install a third-party DirectShow-compatible MPEG-2 decoder,\r\n")  \
        TEXT("either software or hardware-based. Microsoft does not supply an MPEG2\r\n") \
        TEXT("decoder with DirectShow or as an operating system component.\r\n\r\n")      \
        TEXT("Please contact your DVD or PC manufacturer for a DVD decoder.\r\n\r\n")     \
        TEXT("This sample will now exit.\0")

