// OptionsView.cpp : implementation file
//

#include "stdafx.h"
#include "EffectEdit.h"
#include "EffectDoc.h"
#include "OptionsView.h"
#include "UIElements.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsView

IMPLEMENT_DYNCREATE(COptionsView, CFormView)

COptionsView::COptionsView()
	: CFormView(COptionsView::IDD)
{
	//{{AFX_DATA_INIT(COptionsView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COptionsView::~COptionsView()
{
}

void COptionsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsView, CFormView)
	//{{AFX_MSG_MAP(COptionsView)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_TECHNIQUELIST, OnChangeTechnique)
	ON_CBN_SELCHANGE(IDC_PASSLIST, OnChangePass)
	ON_BN_CLICKED(IDC_SHOWSTATS, OnShowStats)
	ON_BN_CLICKED(IDC_WIREFRAME, OnFillModeChange)
	ON_BN_CLICKED(IDC_SELECTEDPASS, OnChangeRenderPass)
	ON_BN_CLICKED(IDC_NOTEXTURES, OnFillModeChange)
	ON_BN_CLICKED(IDC_WITHTEXTURES, OnFillModeChange)
	ON_BN_CLICKED(IDC_UPTOSELECTEDPASS, OnChangeRenderPass)
	ON_BN_CLICKED(IDC_ALLPASSES, OnChangeRenderPass)
	ON_BN_CLICKED(IDC_RESETCAMERA, OnResetCamera)
	ON_BN_CLICKED(IDC_RENDERCONTINUOUSLY, OnChangeRenderTiming)
	ON_BN_CLICKED(IDC_RENDERONREQUEST, OnChangeRenderTiming)
	ON_BN_CLICKED(IDC_RENDER, OnRender)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsView diagnostics

#ifdef _DEBUG
void COptionsView::AssertValid() const
{
	CFormView::AssertValid();
}

void COptionsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


CEffectDoc* COptionsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEffectDoc)));
	return (CEffectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COptionsView message handlers

void COptionsView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
}


void COptionsView::SetTechniqueNameList( CStringList& techniqueNameList, int iTechniqueCur )
{
    CComboBox* pComboBox = (CComboBox*)GetDlgItem( IDC_TECHNIQUELIST );
    if( pComboBox == NULL )
        return;

    pComboBox->ResetContent();

    POSITION pos = techniqueNameList.GetHeadPosition();
    while (pos != NULL)
    {
        CString str = techniqueNameList.GetNext(pos);
        pComboBox->AddString( str );
    }
    pComboBox->SetCurSel( iTechniqueCur );
    PostMessage( WM_COMMAND, 
                 MAKEWPARAM(IDC_TECHNIQUELIST, CBN_SELCHANGE), 
                 (LPARAM)GetDlgItem( IDC_TECHNIQUELIST )->GetSafeHwnd() );
    pComboBox->EnableWindow(pComboBox->GetCount() > 1);
}


void COptionsView::OnChangeTechnique() 
{
    CComboBox* pComboBox = (CComboBox*)GetDlgItem( IDC_TECHNIQUELIST );
    int iTech = pComboBox->GetCurSel();
    if( iTech >= 0 )
    {
        CString strTechName;
        pComboBox->GetLBText( iTech, strTechName );
        CRenderView* pRenderView = GetDocument()->GetRenderView();
        pRenderView->SetTechnique( iTech, strTechName );

        CStringList passNameList;
        pRenderView->GetPassNameList( iTech, passNameList );
        SetPassNameList( passNameList, 0 );
    }
}

void COptionsView::SetPassNameList( CStringList& passNameList, int iPassCur )
{
    CComboBox* pComboBox = (CComboBox*)GetDlgItem( IDC_PASSLIST );
    if( pComboBox == NULL )
        return;

    pComboBox->ResetContent();

    POSITION pos = passNameList.GetHeadPosition();
    while (pos != NULL)
    {
        CString str = passNameList.GetNext(pos);
        pComboBox->AddString( str );
    }
    pComboBox->SetCurSel( iPassCur );
    PostMessage( WM_COMMAND, 
                 MAKEWPARAM(IDC_PASSLIST, CBN_SELCHANGE), 
                 (LPARAM)GetDlgItem( IDC_PASSLIST )->GetSafeHwnd() );
    pComboBox->EnableWindow(pComboBox->GetCount() > 1);
}


void COptionsView::OnChangePass() 
{
    CComboBox* pComboBox = (CComboBox*)GetDlgItem( IDC_PASSLIST );
    int iPass = pComboBox->GetCurSel();
    if( iPass >= 0 )
    {
        CString strPassName;
        pComboBox->GetLBText( iPass, strPassName );
        CRenderView* pRenderView = GetDocument()->GetRenderView();
        pRenderView->SetPass( iPass, strPassName );
    }
}

void COptionsView::OnShowStats() 
{
    BOOL bShowStats = IsDlgButtonChecked( IDC_SHOWSTATS );
    GetDocument()->ShowStats( bShowStats );
}

void COptionsView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

    BOOL bShowStats = GetDocument()->GetShowStats();
    CheckDlgButton( IDC_SHOWSTATS, bShowStats );
    CheckRadioButton( IDC_WIREFRAME, IDC_WITHTEXTURES, IDC_WITHTEXTURES );
    CheckRadioButton( IDC_SELECTEDPASS, IDC_ALLPASSES, IDC_ALLPASSES );
    CheckRadioButton( IDC_RENDERCONTINUOUSLY, IDC_RENDERONREQUEST, 
        ((CEffectEditApp*)AfxGetApp())->RenderContinuously() ? IDC_RENDERCONTINUOUSLY : IDC_RENDERONREQUEST );
    GetDlgItem( IDC_RENDER )->EnableWindow(!((CEffectEditApp*)AfxGetApp())->RenderContinuously() );

    OnFillModeChange();
    OnChangeRenderPass();
    OnChangeRenderTiming();
}

void COptionsView::OnFillModeChange() 
{
    CRenderView* pRenderView = GetDocument()->GetRenderView();
    pRenderView->SetWireframe( IsDlgButtonChecked( IDC_WIREFRAME ) );
    pRenderView->SetNoTextures( IsDlgButtonChecked( IDC_NOTEXTURES ) );
}

void COptionsView::OnChangeRenderPass() 
{
    CRenderView* pRenderView = GetDocument()->GetRenderView();
    pRenderView->SetSelectedPassOnly( IsDlgButtonChecked( IDC_SELECTEDPASS ) );
    pRenderView->SetUpToSelectedPassOnly( IsDlgButtonChecked( IDC_UPTOSELECTEDPASS ) );
}

void COptionsView::OnResetCamera() 
{
    CRenderView* pRenderView = GetDocument()->GetRenderView();
    pRenderView->ResetCamera();
}

void COptionsView::OnChangeRenderTiming() 
{
    bool bRenderContinuously = (IsDlgButtonChecked( IDC_RENDERCONTINUOUSLY ) != 0);
    ((CEffectEditApp*)AfxGetApp())->SetRenderContinuously( bRenderContinuously );
    GetDlgItem( IDC_RENDER )->EnableWindow( !bRenderContinuously );
}

void COptionsView::OnRender() 
{
    AfxGetApp()->GetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_RENDER);
}
