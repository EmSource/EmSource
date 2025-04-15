#if !defined(AFX_CSTM2DLG_H__FD0D3670_3362_4FA7_ACCE_EE3DD80EDBA6__INCLUDED_)
#define AFX_CSTM2DLG_H__FD0D3670_3362_4FA7_ACCE_EE3DD80EDBA6__INCLUDED_

// cstm2dlg.h : header file
//
#include "chooser.h"

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog

class CCustom2Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom2Dlg( CDialogChooser* pChooser );
	virtual BOOL OnDismiss();
    void RemoveAllKeys();

    CDialogChooser* m_pChooser;
    BOOL m_bDlgInited;

    BOOL m_bShowBlank;
    BOOL m_bShowTriangle;
    BOOL m_bShowTeapot;

// Dialog Data
	//{{AFX_DATA(CCustom2Dlg)
	enum { IDD = IDD_CUSTOM2 };
	CStatic	m_Background;
	CStatic	m_Preview;
	BOOL	m_bD3DFont;
	BOOL	m_bXFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void UpdateInfo();

	// Generated message map functions
	//{{AFX_MSG(CCustom2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowBlank();
	afx_msg void OnShowTeapot();
	afx_msg void OnShowTriangle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM2DLG_H__FD0D3670_3362_4FA7_ACCE_EE3DD80EDBA6__INCLUDED_)
