// cstm3dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DxAppWiz.h"
#include "cstm3dlg.h"
#include "DXaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg dialog


CCustom3Dlg::CCustom3Dlg( CDialogChooser* pChooser )
	: CAppWizStepDlg(CCustom3Dlg::IDD)
{
    m_pChooser = pChooser;
    m_pChooser->m_pDlg3Preview = &m_Preview;

    m_bDlgInited    = FALSE;

    m_bActionmapper = TRUE;
    m_bKeyboard     = FALSE;

	//{{AFX_DATA_INIT(CCustom3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCustom3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom3Dlg)
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Control(pDX, IDC_PREVIEW, m_Preview);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom3Dlg::OnDismiss()
{
    if( m_bDlgInited )
	    UpdateData(TRUE);

    if( m_bKeyboard )
        DirectXaw.m_Dictionary["KEYBOARD"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("KEYBOARD");

    if( m_bActionmapper )
        DirectXaw.m_Dictionary["ACTIONMAPPER"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("ACTIONMAPPER");

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


void CCustom3Dlg::RemoveAllKeys()
{
    DirectXaw.m_Dictionary.RemoveKey("KEYBOARD");
    DirectXaw.m_Dictionary.RemoveKey("ACTIONMAPPER");
}

BEGIN_MESSAGE_MAP(CCustom3Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom3Dlg)
	ON_BN_CLICKED(IDC_KEYBOARD, OnKeyboard)
	ON_BN_CLICKED(IDC_ACTIONMAPPER, OnActionmapper)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCustom3Dlg::UpdateInfo()
{
	UpdateData(TRUE);

    m_bActionmapper = IsDlgButtonChecked( IDC_ACTIONMAPPER );
    m_bKeyboard     = IsDlgButtonChecked( IDC_KEYBOARD );
}


void CCustom3Dlg::OnKeyboard() 
{
    UpdateInfo();
}

void CCustom3Dlg::OnActionmapper() 
{
    UpdateInfo();
}

BOOL CCustom3Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	
    m_bDlgInited = TRUE;	
	
    CheckDlgButton( IDC_ACTIONMAPPER, (m_bActionmapper) ? BST_CHECKED : BST_UNCHECKED  );
    CheckDlgButton( IDC_KEYBOARD, (m_bKeyboard) ? BST_CHECKED : BST_UNCHECKED  );
	
    m_Background.SetBitmap( m_pChooser->m_hBackgroundBitmap );
    m_pChooser->UpdatePreviewAndSteps( &m_Preview );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
