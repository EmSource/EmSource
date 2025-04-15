// EffectEdit.h : main header file for the EFFECTEDIT application
//

#if !defined(AFX_EFFECTEDIT_H__B3612813_398C_4D84_9B03_CEA8089AB7EF__INCLUDED_)
#define AFX_EFFECTEDIT_H__B3612813_398C_4D84_9B03_CEA8089AB7EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEffectEditCommandLineInfo:
// See EffectEdit.cpp for the implementation of this class
//

class CEffectEditCommandLineInfo : public CCommandLineInfo
{
public:
    CEffectEditCommandLineInfo();
    virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
    BOOL UseExternalEditor() { return m_bUseExternalEditor; }

private:
    BOOL m_bUseExternalEditor;
};

/////////////////////////////////////////////////////////////////////////////
// CEffectEditDocManager:
// I override this class to customize DoPromptFileName to potentially
// default to the DXSDK media dir.
//
class CEffectEditDocManager : public CDocManager
{
public:
    virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
        DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);
};

/////////////////////////////////////////////////////////////////////////////
// CEffectEditApp:
// See EffectEdit.cpp for the implementation of this class
//

class CEffectEditApp : public CWinApp
{
private:
    bool m_bRenderContinuously;

public:
    void ActivateTextView();
    void ActivateErrorsView();
    void ActivateOptionsView();
    void SelectLine(int iLine);
    CEffectEditApp();
    bool RenderContinuously() { return m_bRenderContinuously; }
    void SetRenderContinuously(bool b) { m_bRenderContinuously = b; }

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CEffectEditApp)
    public:
    virtual BOOL InitInstance();
    virtual BOOL OnIdle(LONG lCount);
    //}}AFX_VIRTUAL

// Implementation
    //{{AFX_MSG(CEffectEditApp)
    afx_msg void OnAppAbout();
    afx_msg void OnViewChooseFont();
    afx_msg void OnViewTabOptions();
    afx_msg void OnFileDefaultToDxsdkMediaFolder();
    afx_msg void OnUpdateFileDefaultToDxsdkMediaFolder(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CTabOptionsDialog dialog

class CTabOptionsDialog : public CDialog
{
// Construction
public:
    CTabOptionsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CTabOptionsDialog)
    enum { IDD = IDD_TABS };
    UINT    m_numSpaces;
    int     m_TabsOrSpacesRadio;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTabOptionsDialog)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CTabOptionsDialog)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EFFECTEDIT_H__B3612813_398C_4D84_9B03_CEA8089AB7EF__INCLUDED_)
