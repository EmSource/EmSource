#if !defined(AFX_TEXTVIEW_H__B9E03A92_7060_4CD6_9661_714C5EA7C59A__INCLUDED_)
#define AFX_TEXTVIEW_H__B9E03A92_7060_4CD6_9661_714C5EA7C59A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMyRichEditCtrl : public CRichEditCtrl
{
public:
    CMyRichEditCtrl();
    ~CMyRichEditCtrl();

protected:
    // Generated message map functions
    //{{AFX_MSG(CMyRichEditCtrl)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    HMODULE m_hRELibrary;   // Rich Edit DLL handle
};

class CTextView : public CFormView
{
protected:
    CTextView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(CTextView)

// Form Data
public:
    //{{AFX_DATA(CTextView)
    enum { IDD = IDD_EFFECTTEXT_FORM };
    CString m_strEdit;
    //}}AFX_DATA

// Attributes
public:
    CEffectDoc* GetDocument();

// Operations
public:
    void SelectLine( int nLine );
    void UpdateFont();
    void SetExternalEditorMode(BOOL bExternal);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTextView)
    public:
    virtual void OnInitialUpdate();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    //}}AFX_VIRTUAL

// Implementation
protected:
    CMyRichEditCtrl m_MyEdit;
    CTime m_timeLastChanged;
    virtual ~CTextView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
    //{{AFX_MSG(CTextView)
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnChangeEdit();
    afx_msg void OnEditUndo();
    afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
    afx_msg void OnEditCopy();
    afx_msg void OnEditCut();
    afx_msg void OnEditPaste();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TextView.cpp
inline CEffectDoc* CTextView::GetDocument()
   { return (CEffectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTVIEW_H__B9E03A92_7060_4CD6_9661_714C5EA7C59A__INCLUDED_)
