// cstm7dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DxAppWiz.h"
#include "cstm7dlg.h"
#include "DXaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom7Dlg dialog


CCustom7Dlg::CCustom7Dlg()
	: CAppWizStepDlg(CCustom7Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom7Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCustom7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom7Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom7Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	// TODO: Set template variables based on the dialog's data.

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom7Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom7Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom7Dlg message handlers
