//------------------------------------------------------------------------------
// File: MultiPlayerDlg.h
//
// Desc: DirectShow sample code - MultiVMR9 MultiPlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MultiGraphSession.h"


const int g_nButtons = 6;    

// CMultiPlayerSession
class CMultiPlayerSession
    : public CMultigraphSession
{
public: 
    HRESULT Initialize();
    HRESULT Terminate();
};


// CMultiPlayerDlg dialog
class CMultiPlayerDlg : public CDialog
{
// Construction
public:
    CMultiPlayerDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
    enum { IDD = IDD_DEFAULTMULTIPLAYER_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:
    // private methods
    void Clean_();
    void UpdateState_();
    void UpdateSubgraphInfo_();
    void UpdateMediaButtons_();
    void UpdateOutputRect_();
    void SetSliderPosition_( CSliderCtrl& slider, int Pos);

    CString GetHHMMSS( LONGLONG llT );

private:
    // data
    CMultiPlayerSession*        m_pSession;
    DWORD                       m_dwSourceCounter; 
    DWORD                       m_dwTotalSources;   // total number of sources attached to the wizard
    UINT_PTR                    m_nTimer;           // timer tag

    float                       m_fSetFPS;          // desired frames per sec rate
    float                       m_fGetFPS;          // actual frames per sec rate

    // bitmaps for buttons
    HBITMAP m_bmpAttach;
    HBITMAP m_bmpAttachGray;
    HBITMAP m_bmpDetach;
    HBITMAP m_bmpDetachGray;
    HBITMAP m_bmpPlay;
    HBITMAP m_bmpPlayGray;
    HBITMAP m_bmpPause;
    HBITMAP m_bmpPauseGray;
    HBITMAP m_bmpScale;
    HBITMAP m_bmpScaleGray;
    HBITMAP m_bmpColor;
    HBITMAP m_bmpColorGray;

    // UI-related members
    CComboBox m_comboSources;   // selection of the sources

    CString m_strTotal;         // total number of sources playing
    CString m_strPath;          // file path to the source
    CString m_strSourceState;   // state of the video source (playing or paused)
    CString m_strAlpha;         // alpha-level of the source
    CString m_strXPos;          // horizontal position of the video source (from -1 to 1)
    CString m_strXSize;         // horizontal size of the video source (from -1 to 1)
    CString m_strYPos;          // vertical position of the video source (from -1 to 1)
    CString m_strYSize;         // vertical size of the video source (from -1 to 1; negative means flipping)
    CString m_strZOrder;        // Z-order of the video source
    CString m_strFPS;           // frames per second rate user sets
    CString m_strStartTime;     // start time
    CString m_strCurTime;       // current time
    CString m_strStopTime;      // stop time

    CSliderCtrl m_sliderAlpha;  // control for setting the alpha-level
    CSliderCtrl m_sliderTime;   // timeline
    CSliderCtrl m_sliderXPos;   // control for setting X-position of the video source
    CSliderCtrl m_sliderXSize;  // control for setting the horiz. size of the source
    CSliderCtrl m_sliderYPos;   // control for setting vert. position of the video source
    CSliderCtrl m_sliderYSize;  // control for setting vert. size of the video source
    CSliderCtrl m_sliderZOrder; // control for setting Z-order
    CSliderCtrl m_sliderFPS;    // control to set desired FPS

public:
    // dialog-related
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);

    // buttons
    afx_msg void OnOK();
    afx_msg void OnBnClickedButtonAttach();
    afx_msg void OnBnClickedButtonDetach();
    afx_msg void OnBnClickedButtonPlay();
    afx_msg void OnBnClickedButtonPause();
    afx_msg void OnBnClickedButtonFit();
    afx_msg void OnBnClickedButtonColor();

    // combo boxes
    afx_msg void OnCbnSelchangeComboSources();

    // sliders
    afx_msg void OnNMReleasedcaptureSliderAlpha(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderSetfps(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderTime(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderZorder(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderXpos(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderYpos(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderXsize(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderYsize(NMHDR *pNMHDR, LRESULT *pResult);

    // tooltips
    HWND        m_hwndToolTips[g_nButtons];
    TOOLINFO    m_ti[g_nButtons];
};

