// cstm1dlg.cpp : implementation file
//

#include "stdafx.h"
#include "DxAppWiz.h"
#include "cstm1dlg.h"
#include "DXaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg( CDialogChooser* pChooser )
	: CAppWizStepDlg(CCustom1Dlg::IDD)
{
    m_pChooser = pChooser;

    m_pChooser->m_pDlg1Preview = &m_Preview;

    m_bWindow      = m_pChooser->m_bWindow;
    m_bMFCDialog   = m_pChooser->m_bMFCDialog;

	//{{AFX_DATA_INIT(CCustom1Dlg)
	m_bDirectInput = m_pChooser->m_bDirectInput;
	m_bDirectMusic = m_pChooser->m_bDirectMusic;
	m_bDirectPlay  = m_pChooser->m_bDirectPlay;
	m_bDirectSound = m_pChooser->m_bDirectSound;
	m_bDirect3D    = m_pChooser->m_bDirect3D;
	m_bRegAccess   = m_pChooser->m_bRegAccess;
	m_bIncludeMenu = m_pChooser->m_bIncludeMenu;
	//}}AFX_DATA_INIT
}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Control(pDX, IDC_PREVIEW, m_Preview);
	DDX_Control(pDX, IDC_BACKGROUND, m_Background);
	DDX_Check(pDX, IDC_DINPUT, m_bDirectInput);
	DDX_Check(pDX, IDC_DMUSIC, m_bDirectMusic);
	DDX_Check(pDX, IDC_DPLAY, m_bDirectPlay);
	DDX_Check(pDX, IDC_DSOUND, m_bDirectSound);
	DDX_Check(pDX, IDC_DIRECT3D, m_bDirect3D);
	DDX_Check(pDX, IDC_REGINCLUDE, m_bRegAccess);
	DDX_Check(pDX, IDC_ADDMENUS, m_bIncludeMenu);
	//}}AFX_DATA_MAP
}

void CCustom1Dlg::UpdateInfo()
{
	UpdateData(TRUE);

    m_bWindow    = IsDlgButtonChecked( IDC_WINDOW );
    m_bMFCDialog = IsDlgButtonChecked( IDC_MFCDIALOG );
    m_pChooser->m_bWindow      = m_bWindow;
    m_pChooser->m_bMFCDialog   = m_bMFCDialog;
    
    m_pChooser->m_bDirectInput = m_bDirectInput;
	m_pChooser->m_bDirectMusic = m_bDirectMusic;
	m_pChooser->m_bDirectPlay  = m_bDirectPlay;
	m_pChooser->m_bDirectSound = m_bDirectSound;
	m_pChooser->m_bDirect3D    = m_bDirect3D;
	m_pChooser->m_bRegAccess = m_bRegAccess;
	m_pChooser->m_bIncludeMenu = m_bIncludeMenu;

    m_pChooser->UpdatePreviewAndSteps( &m_Preview );
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
    UpdateInfo();

    if( m_bMFCDialog )
        DirectXaw.m_Dictionary["DLG"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("DLG");

    if( m_bWindow )
        DirectXaw.m_Dictionary["WINDOW"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("WINDOW");

    if( m_bDirect3D )
        DirectXaw.m_Dictionary["D3D"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("D3D");
    
    if( m_bDirectInput )
        DirectXaw.m_Dictionary["DINPUT"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("DINPUT");

    if( m_bDirectMusic )
        DirectXaw.m_Dictionary["DMUSIC"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("DMUSIC");

    if( m_bDirectPlay )
        DirectXaw.m_Dictionary["DPLAY"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("DPLAY");

    if( m_bDirectSound )
        DirectXaw.m_Dictionary["DSOUND"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("DSOUND");

    if( m_bRegAccess )
        DirectXaw.m_Dictionary["REGACCESS"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("REGACCESS");

    if( m_bIncludeMenu )
        DirectXaw.m_Dictionary["MENUBAR"]="Yes";
    else
        DirectXaw.m_Dictionary.RemoveKey("MENUBAR");

    m_pChooser->InitDialogs();

    return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_BN_CLICKED(IDC_DIRECT3D, OnDirect3d)
	ON_BN_CLICKED(IDC_DPLAY, OnDplay)
	ON_BN_CLICKED(IDC_MFCDIALOG, OnMfcdialog)
	ON_BN_CLICKED(IDC_WINDOW, OnWindow)
	ON_BN_CLICKED(IDC_DINPUT, OnDinput)
	ON_BN_CLICKED(IDC_DMUSIC, OnDmusic)
	ON_BN_CLICKED(IDC_DSOUND, OnDsound)
	ON_BN_CLICKED(IDC_REGINCLUDE, OnReginclude)
	ON_BN_CLICKED(IDC_ADDMENUS, OnAddmenus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCustom1Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();

	::ShowWindow( ::GetDlgItem(::GetParent(m_hWnd), 0xE146), SW_HIDE );

    CheckDlgButton( IDC_WINDOW, (m_bWindow) ? BST_CHECKED : BST_UNCHECKED );
    CheckDlgButton( IDC_MFCDIALOG, (m_bMFCDialog) ? BST_CHECKED : BST_UNCHECKED );
    CheckDlgButton( IDC_DINPUT, (m_bDirectInput) ? BST_CHECKED : BST_UNCHECKED );
    CheckDlgButton( IDC_DMUSIC, (m_bDirectMusic) ? BST_CHECKED : BST_UNCHECKED );
    CheckDlgButton( IDC_DPLAY, (m_bDirectPlay) ? BST_CHECKED : BST_UNCHECKED );
    CheckDlgButton( IDC_DSOUND, (m_bDirectSound) ? BST_CHECKED : BST_UNCHECKED );
    CheckDlgButton( IDC_DIRECT3D, (m_bDirect3D) ? BST_CHECKED : BST_UNCHECKED );
    CheckDlgButton( IDC_REGINCLUDE, (m_bRegAccess) ? BST_CHECKED : BST_UNCHECKED );
    CheckDlgButton( IDC_ADDMENUS, (m_bIncludeMenu) ? BST_CHECKED : BST_UNCHECKED );

    m_Background.SetBitmap( m_pChooser->m_hBackgroundBitmap );
    UpdateInfo();

	return TRUE;  
}

void CCustom1Dlg::OnDirect3d() 
{
    UpdateInfo();
}

void CCustom1Dlg::OnDplay() 
{
    UpdateInfo();
}

void CCustom1Dlg::OnMfcdialog() 
{
    UpdateInfo();
}

void CCustom1Dlg::OnWindow() 
{
    UpdateInfo();
}

void CCustom1Dlg::OnDinput() 
{
    UpdateInfo();
}

void CCustom1Dlg::OnDmusic() 
{
    UpdateInfo();
}

void CCustom1Dlg::OnDsound() 
{
    UpdateInfo();
}

void CCustom1Dlg::OnReginclude() 
{
    UpdateInfo();
}

void CCustom1Dlg::OnAddmenus() 
{
    UpdateInfo();
}
