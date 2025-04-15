#if !defined(AFX_CSTM7DLG_H__BB7348B9_0968_45AC_8377_A9B46D20C8B8__INCLUDED_)
#define AFX_CSTM7DLG_H__BB7348B9_0968_45AC_8377_A9B46D20C8B8__INCLUDED_

// cstm7dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom7Dlg dialog

class CCustom7Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom7Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom7Dlg)
	enum { IDD = IDD_CUSTOM7 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom7Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom7Dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM7DLG_H__BB7348B9_0968_45AC_8377_A9B46D20C8B8__INCLUDED_)
