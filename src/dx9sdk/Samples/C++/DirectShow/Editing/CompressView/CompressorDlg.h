//------------------------------------------------------------------------------
// File: CompressorDlg.h
//
// Desc: DirectShow sample code - main header file for CompressView sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#if !defined(AFX_COMPRESSORDLG_H__913F6184_B9CF_4048_AF62_75B42E96BA44__INCLUDED_)
#define AFX_COMPRESSORDLG_H__913F6184_B9CF_4048_AF62_75B42E96BA44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

interface IBaseFilter;

/////////////////////////////////////////////////////////////////////////////
// CCompressorDlg dialog

class CCompressorDlg : public CDialog
{
    HRESULT AddCompressorsToList();

    void GetCompressor(int n, IBaseFilter ** ppCompressor);
    void SetButtonStates(BOOL bState);
    void PumpMessages(void);
    void CCompressorDlg::PlayMedia(CString& strFile);
    void ResetPlayback(void);

    CComPtr<IBaseFilter>   m_pCompressor;
    CComPtr<IGraphBuilder> m_pPlaybackGraph;

    BOOL m_bCompressing;
    BOOL m_bCloseRequested;

// Construction
public:
    CCompressorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CCompressorDlg)
    enum { IDD = IDD_COMPRESSOR_DIALOG };
    CButton m_BtnBrowse;
    CButton m_BtnStop;
    CStatic m_Screen;
    CButton m_BtnPlayOutput;
    CButton m_BtnPlayInput;
    CButton m_BtnStart;
    CComboBox   m_CompressorList;
    CProgressCtrl   m_Progress;
    BOOL    m_bWantAudio;
    CString m_szInputFile;
    CString m_szOutputFile;
    CString m_sProgressText;
    BOOL    m_bSuppressWarning;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCompressorDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CCompressorDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBrowse();
    afx_msg void OnStart();
    afx_msg void OnSelchangeCompressor();
    afx_msg void OnButtonPlayInput();
    afx_msg void OnButtonPlayOutput();
    afx_msg void OnButtonStop();
    afx_msg void OnClose();
    afx_msg void OnDestroy();
    afx_msg BOOL OnEraseBkgnd(CDC *);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPRESSORDLG_H__913F6184_B9CF_4048_AF62_75B42E96BA44__INCLUDED_)
