#if !defined(AFX_CSTM5DLG_H__8215A9CC_EE15_5E55_8DC7_7BB31F51D8CE__INCLUDED_)
#define AFX_CSTM5DLG_H__8215A9CC_EE15_5E55_8DC7_7BB31F51D8CE__INCLUDED_

// cstm5dlg.h : header file
//
#include "chooser.h"

/////////////////////////////////////////////////////////////////////////////
// CCustom5Dlg dialog

class CCustom5Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom5Dlg( CDialogChooser* pChooser );
	virtual BOOL OnDismiss();
    void RemoveAllKeys();

    CDialogChooser* m_pChooser;
    BOOL m_bDlgInited;

// Dialog Data
	//{{AFX_DATA(CCustom5Dlg)
	enum { IDD = IDD_CUSTOM5 };
	CStatic	m_Preview;
	CStatic	m_Background;
	BOOL	m_bDPlayVoice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom5Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom5Dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM5DLG_H__8215A9CC_EE15_5E55_8DC7_7BB31F51D8CE__INCLUDED_)
