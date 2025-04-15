#if !defined(AFX_CSTM6DLG_H__F742EF0D_D847_4D51_9D75_702421B82D78__INCLUDED_)
#define AFX_CSTM6DLG_H__F742EF0D_D847_4D51_9D75_702421B82D78__INCLUDED_

// cstm6dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom6Dlg dialog

class CCustom6Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom6Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom6Dlg)
	enum { IDD = IDD_CUSTOM6 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom6Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom6Dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM6DLG_H__F742EF0D_D847_4D51_9D75_702421B82D78__INCLUDED_)
