//------------------------------------------------------------------------------
// File: AudioBoxDlg.h
//
// Desc: DirectShow sample code - main dialog header file for the AudioBox
//       application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#if !defined(AFX_AUDIOBOXDLG_H__04AD8433_DF22_4491_9611_260EDAE17B96__INCLUDED_)
#define AFX_AUDIOBOXDLG_H__04AD8433_DF22_4491_9611_260EDAE17B96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dshow.h>

// Specify that Windows 98 is the minimum system required
#if (_WIN32_WINDOWS < 0x410)
#undef  _WIN32_WINDOWS
#define _WIN32_WINDOWS  0x0410
#endif

#include "keyprovider.h"

//
// Constants
//
const int TICKLEN=500, TIMERID=55;
const int VOLUME_FULL=0L;
const int VOLUME_SILENCE=-10000L;
const int MINIMUM_VOLUME=3000;
const int MAX_FAVORITES = ID_FAVORITE_MAX - ID_FAVORITE_BASE;

#define APPNAME TEXT("DirectShow AudioBox Sample\0")

enum MENUS { emFile, emFolders, emFavorites, emPlayback, emHelp };

// Application-defined messages
#define WM_GRAPHNOTIFY  WM_APP + 1
#define WM_FIRSTFILE    WM_APP + 2
#define WM_PLAYFILE     WM_APP + 3
#define WM_NEXTFILE     WM_APP + 4
#define WM_PREVIOUSFILE WM_APP + 5
#define WM_RANDOMFILE   WM_APP + 6

// Registry keys
const TCHAR g_szRegAudioBox[128] = {TEXT("SOFTWARE\\Microsoft\\Shared Tools\\AudioBox\0")};
const TCHAR g_szRegFav[128] = {TEXT("SOFTWARE\\Microsoft\\Shared Tools\\AudioBox\\Favorites\0")};

//
// Macros
//
#define SAFE_RELEASE(i) {if (i) i->Release(); i = NULL;}

#define JIF(x) if (FAILED(hr=(x))) \
    {RetailOutput(TEXT("FAILED(0x%x) ") TEXT(#x) TEXT("\n\0"), hr); goto CLEANUP;}



/////////////////////////////////////////////////////////////////////////////
// CAudioboxDlg dialog

class CAudioboxDlg : public CDialog
{
// Construction
public:
    CAudioboxDlg(CWnd* pParent = NULL); // standard constructor

    HRESULT PrepareMedia(LPTSTR lpszMovie);
    HRESULT DisplayFileDuration(void);

    HRESULT InitDirectShow(void);
    HRESULT FreeDirectShow(void);
    HRESULT HandleGraphEvent(void);
    HRESULT RunMedia(void);
    HRESULT StopMedia(void);
    HRESULT PauseMedia(void);
    HRESULT PlayMedia(LPTSTR lpszMovie, HINSTANCE hInstance);
    HRESULT CheckMovieState(BOOL *pbComplete);
    HRESULT GetInterfaces(void);
    HRESULT MuteAudio(void);
    HRESULT ResumeAudio(void);
    HRESULT RenderWMFile(LPCWSTR wFile);
    HRESULT CreateFilter(REFCLSID clsid, IBaseFilter **ppFilter);
    HRESULT AddKeyProvider(IGraphBuilder *pGraph);
    HRESULT RenderOutputPins(IGraphBuilder *pGB, IBaseFilter *pReader);

    void FillFileList(LPTSTR pszCmdLine);
    void FillDirList(LPTSTR pszRootDir);
    void InitMediaDirectory(void);
    void ClearFileInfo(void);
    void ResetDirectShow(void);
    void PlayNextFile(void);
    void PlayPreviousFile(void);
    void PlaySelectedFile(void);
    void PlayRandomFile(void);
    void ConfigureSeekbar(void);
    void StartSeekTimer(void);
    void StopSeekTimer(void);
    void HandleSeekbar(WPARAM wReq);
    void HandleVolumeSlider(WPARAM wReq);
    void UpdatePosition(REFERENCE_TIME rtNow);
    void ReadMediaPosition(void);
    void CleanupInterfaces(void);
    void RetailOutput(TCHAR *tszErr, ...);
    void ClearPositionLabel(void) ;

    void CALLBACK MediaTimer(UINT wTimerID, UINT msg, ULONG dwUser, ULONG dw1, ULONG dw2);

    LONG GetDXMediaPath(TCHAR *strPath);

    BOOL DisplayFileInfo(LPTSTR szFile);
    BOOL InitCustomDirectory(int nCustomDir);
    BOOL IsWindowsMediaFile(LPTSTR lpszFile);

    HRESULT ModifyFavorite(const TCHAR *szMediaDirectory, DWORD dwEnable);
    BOOL IsFavorite(const TCHAR *szMediaDirectory);
    void GetShortName(TCHAR *pszFull, TCHAR *pszFile);

   // Dialog Data
    //{{AFX_DATA(CAudioboxDlg)
    enum { IDD = IDD_AUDIOBOX_DIALOG };
    CButton m_ButtonFavorite;
    CSliderCtrl m_VolumeSlider;
    CListBox    m_ListDir;
    CListBox    m_ListFiles;
    CStatic m_StrPosition;
    CSliderCtrl m_Seekbar;
    CStatic m_StrDuration;
    CEdit   m_EditMediaDir;
    CSpinButtonCtrl m_SpinFiles;
    CStatic m_StrMediaPath;
    CButton m_CheckMute;
    CButton m_ButtonStop;
    CButton m_ButtonPlay;
    CButton m_ButtonPause;
    CButton m_CheckRandomize;
    CButton m_CheckLoop;
    CStatic m_StrFileDate;
    CStatic m_StrFileSize;
    CStatic m_StrFileList;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAudioboxDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;
    int   m_nCurrentFileSelection;
    long m_lCurrentVolume;
    REFERENCE_TIME g_rtTotalTime;
    UINT_PTR g_wTimerID;

    TCHAR m_szCurrentDir[MAX_PATH + 10];  // Full path + '\Media' folder
    TCHAR m_szActiveDir[MAX_PATH + 10];  // Full path + '\Media' folder
    TCHAR g_szFavorites[MAX_FAVORITES][MAX_PATH];

    IGraphBuilder *m_pGB;
    IMediaSeeking *m_pMS;
    IMediaControl *m_pMC;
    IMediaEventEx *m_pME;
    IBasicAudio   *m_pBA;

#ifndef TARGET_WMF9
    // Global key provider object created/released during the
    // Windows Media graph-building stage.
    CKeyProvider prov;
#endif

    // Generated message map functions
    //{{AFX_MSG(CAudioboxDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnClose();
    afx_msg void OnSelectFile();
    afx_msg void OnPause();
    afx_msg void OnPlay();
    afx_msg void OnStop();
    afx_msg void OnCheckMute();
    afx_msg void OnCheckLoop();
    afx_msg void OnDblclkListFilters();
    afx_msg void OnDeltaposSpinFiles(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonSetMediadir();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnDestroy();
    afx_msg void OnCheckRandomize();
    afx_msg void OnDblclkListDir();
    afx_msg void OnAddFavorite();
    afx_msg void OnClearFavorites();
    afx_msg void OnCheckFavorite();
    afx_msg void OnSelectFavorite(UINT nID);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIOBOXDLG_H__04AD8433_DF22_4491_9611_260EDAE17B96__INCLUDED_)
