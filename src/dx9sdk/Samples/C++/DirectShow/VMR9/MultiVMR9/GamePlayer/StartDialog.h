//------------------------------------------------------------------------------
// File: StartDialog.h
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once
#include "afxcmn.h"


// CStartDialog dialog
class CStartDialog : public CDialog
{
// Construction
public:
    CStartDialog(CWnd* pParent = NULL);                 // standard constructor

// Dialog Data
    enum { IDD = IDD_GAMEPLAYER_DIALOG };

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

public:

private:
    UINT_PTR m_nTimer;
    CListCtrl m_ListSources;
    CGamePlayerSession* m_pSession;

    void UpdateControls_();

public:
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnBnClickedButtonStart();
    afx_msg void OnBnClickedButtonStop();
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);
};

