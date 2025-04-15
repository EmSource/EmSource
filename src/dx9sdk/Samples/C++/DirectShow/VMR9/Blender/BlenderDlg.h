//------------------------------------------------------------------------------
// File: BlenderDlg.h
//
// Desc: DirectShow sample code - header for CBlenderDlg class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#if !defined(AFX_BLENDERDLG_H__6856886E_8D59_4F30_83CF_E08E72D52C9F__INCLUDED_)
#define AFX_BLENDERDLG_H__6856886E_8D59_4F30_83CF_E08E72D52C9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dshow.h>

// VMR9 Headers
#include <d3d9.h>
#include <vmr9.h>

//
// Macros
//
#define SAFE_RELEASE(i) {if (i) i->Release(); i = NULL;}

#define JIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(0x%x) ") TEXT(#x) TEXT("\n\0"), hr); return hr;}

// File filter for OpenFile dialog
#define FILE_FILTER_TEXT \
    TEXT("Video Files (*.asf; *.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.wmv)\0*.asf; *.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v; *.wmv\0\0")

// Begin default media search at root directory
#define DEFAULT_MEDIA_PATH  TEXT("\\\0")

#define WM_GRAPHNOTIFY  WM_USER+13
#define REGISTER_FILTERGRAPH
#define STRM_A  0
#define STRM_B  1

//
// Constants
//
const int TICKLEN=100, TIMERID=55;


/////////////////////////////////////////////////////////////////////////////
// CBlenderDlg dialog

class CBlenderDlg : public CDialog
{
// Construction
public:
	CBlenderDlg(CWnd* pParent = NULL);	// standard constructor

    HRESULT PrepareMedia(LPTSTR lpszMovie);
    HRESULT InitDirectShow(void);
    HRESULT FreeDirectShow(void);
    HRESULT HandleGraphEvent(void);
	HRESULT UpdatePinAlpha(int nStreamID);
	HRESULT UpdatePinPos(int nStreamID);
	HRESULT RepaintVideo(void);

	HRESULT WaitForState(OAFilterState fsReq);
	HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);
	void RemoveGraphFromRot(DWORD pdwRegister);

    void ResetDirectShow(void);
    void CenterVideo(void);
	void MoveVideoWindow(void);
	BOOL GetClipFileName(LPTSTR szName);
	BOOL VerifyVMR9(void);
	HRESULT InitializeVideo(void);
	HRESULT InitializeWindowlessVMR(IBaseFilter **ppVmr9);
	HRESULT DisplayFileDuration(void);
	void UpdatePosition(void);

	void Msg(TCHAR *szFormat, ...);
	void RetailOutput(TCHAR *tszErr, ...);

	void InitStreamParams(void);
	void InitButtons(void);
	void InitControls(void);
	void EnableControls(BOOL bEnable);
	void SetSliders(void);
	void HandleHorizontalTrackbar(WPARAM wParam, LPARAM lParam);
	void HandleVerticalTrackbar(WPARAM wParam, LPARAM lParam);
	void StartTimer(void);
	void StopTimer(void);
    void DisplayCoordinates(int nStreamID, VMR9NormalizedRect& r);
    void DisplayAlpha(int nStreamID);

    HRESULT ConfigureMultiFileVMR9(WCHAR *wFile1, WCHAR *wFile2);
    HRESULT RenderFileToVMR9(WCHAR *wFileName, IBaseFilter *pRenderer, BOOL bRenderAudio);
    BOOL IsWindowsMediaFile(WCHAR *lpszFile);
    HRESULT GetUnconnectedPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir, IPin **ppPin);


// Dialog Data
	//{{AFX_DATA(CBlenderDlg)
	enum { IDD = IDD_BLENDER_DIALOG };
	CStatic	m_StrPosition;
	CStatic	m_StrDuration;
	CButton	m_ButtonStop;
	CButton	m_ButtonPause;
	CButton	m_ButtonPlay;
	CStatic	m_Screen;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlenderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	DWORD m_dwGraphRegister;
	HWND m_hwndScreen;
    UINT_PTR g_wTimerID;

	IGraphBuilder *pGB;
	IMediaSeeking *pMS;
	IMediaControl *pMC;
	IMediaEventEx *pME;
	IVMRWindowlessControl9 *pWC;
    IVMRMixerControl9 *pMix;

	TCHAR m_szFile1[MAX_PATH], m_szFile2[MAX_PATH];

	// Generated message map functions
	//{{AFX_MSG(CBlenderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStream1();
	afx_msg void OnButtonStream2();
	afx_msg void OnStop();
	afx_msg void OnPause();
	afx_msg void OnPlay();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckFlip();
	afx_msg void OnCheckMirror();
	afx_msg void OnCheckFlip2();
	afx_msg void OnCheckMirror2();
	afx_msg void OnButtonAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLENDERDLG_H__6856886E_8D59_4F30_83CF_E08E72D52C9F__INCLUDED_)
