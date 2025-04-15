#if !defined(AFX_CSTM8DLG_H__3D6D5409_6D3F_49BF_933F_9B2505078134__INCLUDED_)
#define AFX_CSTM8DLG_H__3D6D5409_6D3F_49BF_933F_9B2505078134__INCLUDED_

// cstm8dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom8Dlg dialog

class CCustom8Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom8Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom8Dlg)
	enum { IDD = IDD_CUSTOM8 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom8Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom8Dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM8DLG_H__3D6D5409_6D3F_49BF_933F_9B2505078134__INCLUDED_)
