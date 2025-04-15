#if !defined(AFX_CSTM3DLG_H__17962FCC_B584_42E0_ABA0_41D88E0107A6__INCLUDED_)
#define AFX_CSTM3DLG_H__17962FCC_B584_42E0_ABA0_41D88E0107A6__INCLUDED_

// cstm3dlg.h : header file
//
#include "chooser.h"

/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg dialog

class CCustom3Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom3Dlg( CDialogChooser* pChooser );
	virtual BOOL OnDismiss();
    void UpdateInfo();
    void RemoveAllKeys();

    CDialogChooser* m_pChooser;
    BOOL m_bDlgInited;

    BOOL m_bActionmapper;
    BOOL m_bKeyboard;

// Dialog Data
	//{{AFX_DATA(CCustom3Dlg)
	enum { IDD = IDD_CUSTOM3 };
	CStatic	m_Background;
	CStatic	m_Preview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom3Dlg)
	afx_msg void OnKeyboard();
	afx_msg void OnActionmapper();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM3DLG_H__17962FCC_B584_42E0_ABA0_41D88E0107A6__INCLUDED_)
