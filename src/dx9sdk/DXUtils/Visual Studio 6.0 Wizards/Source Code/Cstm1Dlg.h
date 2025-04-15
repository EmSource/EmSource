#if !defined(AFX_CSTM1DLG_H__3546CC7D_D0EA_4E14_BBED_B42A4412D859__INCLUDED_)
#define AFX_CSTM1DLG_H__3546CC7D_D0EA_4E14_BBED_B42A4412D859__INCLUDED_

// cstm1dlg.h : header file
//
#include "chooser.h"

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog

class CCustom1Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom1Dlg( CDialogChooser* pChooser );
	virtual BOOL OnDismiss();

    CDialogChooser* m_pChooser;

    BOOL    m_bWindow;
    BOOL    m_bMFCDialog;

// Dialog Data
	//{{AFX_DATA(CCustom1Dlg)
	enum { IDD = IDD_CUSTOM1 };
	CStatic	m_Preview;
	CStatic	m_Background;
	BOOL	m_bDirectInput;
	BOOL	m_bDirectMusic;
	BOOL	m_bDirectPlay;
	BOOL	m_bDirectSound;
	BOOL	m_bDirect3D;
	BOOL	m_bRegAccess;
	BOOL	m_bIncludeMenu;
	//}}AFX_DATA

    int m_nSteps;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void UpdateInfo();

	// Generated message map functions
	//{{AFX_MSG(CCustom1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirect3d();
	afx_msg void OnDplay();
	afx_msg void OnMfcdialog();
	afx_msg void OnWindow();
	afx_msg void OnDinput();
	afx_msg void OnDmusic();
	afx_msg void OnDsound();
	afx_msg void OnReginclude();
	afx_msg void OnAddmenus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM1DLG_H__3546CC7D_D0EA_4E14_BBED_B42A4412D859__INCLUDED_)
