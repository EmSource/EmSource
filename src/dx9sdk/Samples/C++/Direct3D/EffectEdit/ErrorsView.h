#if !defined(AFX_ERRORSVIEW_H__088EA9EC_8793_48DC_8682_64E6BEFCF302__INCLUDED_)
#define AFX_ERRORSVIEW_H__088EA9EC_8793_48DC_8682_64E6BEFCF302__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErrorsView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CErrorsView : public CFormView
{
protected:
    CErrorsView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(CErrorsView)

// Form Data
public:
    //{{AFX_DATA(CErrorsView)
    enum { IDD = IDD_ERRORS_FORM };
    CListBox    m_ListBox;
    //}}AFX_DATA

// Attributes
public:
    CEffectDoc* GetDocument();
    void ParseErrors();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CErrorsView)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    //}}AFX_VIRTUAL

// Implementation
protected:
    BOOL m_bNeedToParseErrors;
    virtual ~CErrorsView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
    //{{AFX_MSG(CErrorsView)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnDblclkList();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ErrorsView.cpp
inline CEffectDoc* CErrorsView::GetDocument()
   { return (CEffectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORSVIEW_H__088EA9EC_8793_48DC_8682_64E6BEFCF302__INCLUDED_)
