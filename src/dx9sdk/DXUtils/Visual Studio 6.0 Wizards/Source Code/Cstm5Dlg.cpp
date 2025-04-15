// cstm5dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DxAppWiz.h"
#include "cstm5dlg.h"
#include "DXaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom5Dlg dialog


CCustom5Dlg::CCustom5Dlg( CDialogChooser* pChooser )
	: CAppWizStepDlg(CCustom5Dlg::IDD)
{
    m_pChooser = pChooser;
    m_pChooser->m_pDlg5Preview = &m_Preview;

    m_bDlgInited   = FALSE;

	//{{AFX_DATA_INIT(CCustom5Dlg)
	m_bDPlayVoice = FALSE;
	//}}AFX_DATA_INIT
}


void CCustom5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom5Dlg)
	DDX_Control(pDX, IDC_PREVIEW, m_Preview);
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Check(pDX, IDC_DPLAYVOICE, m_bDPlayVoice);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom5Dlg::OnDismiss()
{
    if( m_bDlgInited )
    {
        UpdateData(TRUE);
    }

    if( m_bDPlayVoice )
        DirectXaw.m_Dictionary["DPLAYVOICE"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("DPLAYVOICE");

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}

void CCustom5Dlg::RemoveAllKeys()
{
    DirectXaw.m_Dictionary.RemoveKey("DPLAYVOICE");
}

BEGIN_MESSAGE_MAP(CCustom5Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom5Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom5Dlg message handlers

BOOL CCustom5Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	
    m_bDlgInited = TRUE;

    if( m_bDPlayVoice )
        CheckDlgButton( IDC_DPLAYVOICE, BST_CHECKED );
	
    m_Background.SetBitmap( m_pChooser->m_hBackgroundBitmap );
    m_pChooser->UpdatePreviewAndSteps( &m_Preview );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
