// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__7B69EEA0_267A_429D_A21F_2420814F24DF__INCLUDED_)
#define AFX_MAINFRM_H__7B69EEA0_267A_429D_A21F_2420814F24DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMySplitterWnd : public CSplitterWnd
{
protected:
    CSplitterWnd* m_pSplitterWndPrev;
    CSplitterWnd* m_pSplitterWndNext;
    bool m_bPreserveLastPaneSize;

public:
    CMySplitterWnd() { m_bPreserveLastPaneSize = false; }
    void SetPrev(CSplitterWnd* pWnd) { m_pSplitterWndPrev = pWnd; }
    void SetNext(CSplitterWnd* pWnd) { m_pSplitterWndNext = pWnd; }
	virtual void ActivateNext(BOOL bPrev = FALSE);
    virtual void RecalcLayout();
  	virtual void StopTracking(BOOL bAccept);

    void PreserveLastPaneSize() { m_bPreserveLastPaneSize = true; }
};

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
    void ActivateTextView();
    void ActivateErrorsView();
    void ActivateOptionsView();
	void SelectLine(int iLine);
    void TextViewUpdateFont();

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	CMySplitterWnd m_wndSplitterLeft;
	CMySplitterWnd m_wndSplitterRight;
	CMySplitterWnd m_wndSplitterMain;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRender();
	afx_msg void OnViewChangeDevice();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7B69EEA0_267A_429D_A21F_2420814F24DF__INCLUDED_)
