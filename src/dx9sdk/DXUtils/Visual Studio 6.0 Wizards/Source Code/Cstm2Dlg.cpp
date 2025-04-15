// cstm2dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DxAppWiz.h"
#include "cstm2dlg.h"
#include "DXaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog


CCustom2Dlg::CCustom2Dlg( CDialogChooser* pChooser )
	: CAppWizStepDlg(CCustom2Dlg::IDD)
{
    m_pChooser = pChooser;
    m_pChooser->m_pDlg2Preview = &m_Preview;

    m_bDlgInited    = FALSE;

    m_bShowBlank    = m_pChooser->m_bShowBlank;
    m_bShowTriangle = m_pChooser->m_bShowTriangle;
    m_bShowTeapot   = m_pChooser->m_bShowTeapot;

	//{{AFX_DATA_INIT(CCustom2Dlg)
	m_bD3DFont      = TRUE;
	m_bXFile        = TRUE;
	//}}AFX_DATA_INIT
}


void CCustom2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom2Dlg)
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Control(pDX, IDC_PREVIEW, m_Preview);
	DDX_Check(pDX, IDC_D3DFONT, m_bD3DFont);
	DDX_Check(pDX, IDC_XFILE, m_bXFile);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom2Dlg::OnDismiss()
{
    if( m_bDlgInited )
	    UpdateData(TRUE);

    if( m_bD3DFont )
        DirectXaw.m_Dictionary["D3DFONT"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("D3DFONT");

    if( m_bXFile )
        DirectXaw.m_Dictionary["X_FILE"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("X_FILE");

    if( m_bShowBlank )
        DirectXaw.m_Dictionary["SHOW_BLANK"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("SHOW_BLANK");

    if( m_bShowTriangle )
        DirectXaw.m_Dictionary["SHOW_TRIANGLE"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("SHOW_TRIANGLE");

    if( m_bShowTeapot )
        DirectXaw.m_Dictionary["SHOW_TEAPOT"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("SHOW_TEAPOT");

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


void CCustom2Dlg::RemoveAllKeys()
{
    DirectXaw.m_Dictionary.RemoveKey("D3DFONT");
    DirectXaw.m_Dictionary.RemoveKey("X_FILE");
    DirectXaw.m_Dictionary.RemoveKey("SHOW_BLANK");
    DirectXaw.m_Dictionary.RemoveKey("SHOW_TRIANGLE");
    DirectXaw.m_Dictionary.RemoveKey("SHOW_TEAPOT");
}

BEGIN_MESSAGE_MAP(CCustom2Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom2Dlg)
	ON_BN_CLICKED(IDC_SHOW_BLANK, OnShowBlank)
	ON_BN_CLICKED(IDC_SHOW_TEAPOT, OnShowTeapot)
	ON_BN_CLICKED(IDC_SHOW_TRIANGLE, OnShowTriangle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg message handlers

BOOL CCustom2Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();

    m_bDlgInited = TRUE;
	
    CheckDlgButton( IDC_SHOW_BLANK, (m_bShowBlank) ? BST_CHECKED : BST_UNCHECKED  );
    CheckDlgButton( IDC_SHOW_TEAPOT, (m_bShowTeapot) ? BST_CHECKED : BST_UNCHECKED  );
    CheckDlgButton( IDC_SHOW_TRIANGLE, (m_bShowTriangle) ? BST_CHECKED : BST_UNCHECKED );	
    CheckDlgButton( IDC_D3DFONT, (m_bD3DFont) ? BST_CHECKED : BST_UNCHECKED  );
    CheckDlgButton( IDC_XFILE, (m_bXFile) ? BST_CHECKED : BST_UNCHECKED  );
	
    m_Background.SetBitmap( m_pChooser->m_hBackgroundBitmap );
    m_pChooser->UpdatePreviewAndSteps( &m_Preview );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustom2Dlg::UpdateInfo() 
{
    m_bShowBlank    = IsDlgButtonChecked( IDC_SHOW_BLANK );
    m_bShowTriangle = IsDlgButtonChecked( IDC_SHOW_TRIANGLE );
    m_bShowTeapot   = IsDlgButtonChecked( IDC_SHOW_TEAPOT );

    m_pChooser->m_bShowBlank    = m_bShowBlank;
    m_pChooser->m_bShowTriangle = m_bShowTriangle;
    m_pChooser->m_bShowTeapot   = m_bShowTeapot;

    m_pChooser->UpdatePreviewAndSteps( &m_Preview );
}

void CCustom2Dlg::OnShowBlank() 
{
    UpdateInfo();
}

void CCustom2Dlg::OnShowTriangle() 
{
    UpdateInfo();
}

void CCustom2Dlg::OnShowTeapot() 
{
    UpdateInfo();
}

