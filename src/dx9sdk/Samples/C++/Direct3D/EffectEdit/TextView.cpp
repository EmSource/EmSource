// TextView.cpp : implementation file
//

#include "stdafx.h"
#include "EffectEdit.h"
#include "OptionsView.h"
#include "EffectDoc.h"
#include "MainFrm.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CFormView)

CTextView::CTextView()
	: CFormView(CTextView::IDD)
{
	//{{AFX_DATA_INIT(CTextView)
	m_strEdit = _T("");
	//}}AFX_DATA_INIT
}

CTextView::~CTextView()
{
}

void CTextView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextView)
	DDX_Text(pDX, IDC_EDIT, m_strEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextView, CFormView)
	//{{AFX_MSG_MAP(CTextView)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT, OnChangeEdit)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextView diagnostics

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTextView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEffectDoc* CTextView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEffectDoc)));
	return (CEffectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers

void CTextView::OnSize(UINT nType, int cx, int cy) 
{
    SetScrollSizes( MM_TEXT, CSize(cx, cy) );

	CFormView::OnSize(nType, cx, cy);
	
    CWnd* pGroup = GetDlgItem(IDC_GROUPBOX);
    CWnd* pEdit = GetDlgItem(IDC_EDIT);

    if( pGroup != NULL && 
        pEdit != NULL )
    {
        CRect rc;

        pGroup->SetWindowPos(NULL, 7, 2, cx - 7 - 4, cy - 2 - 10, SWP_NOZORDER);

        pGroup->GetClientRect(&rc);
        pGroup->MapWindowPoints(this, &rc);

        rc.InflateRect( -10, -17, -10, -10 );
        pEdit->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
    }
}

void CTextView::OnInitialUpdate() 
{
    if( m_MyEdit.GetSafeHwnd() == NULL )
    {
        m_MyEdit.SubclassDlgItem( IDC_EDIT, this );
        m_MyEdit.SetOptions(ECOOP_OR, ECO_SAVESEL);
    }

    // Set the event mask so that the parent gets notified when the text
    // of the rich edit control changes. 
    m_MyEdit.SetEventMask( m_MyEdit.GetEventMask() | ENM_CHANGE );

    m_strEdit = ((CEffectDoc*)GetDocument())->GetCode();
    UpdateData(FALSE); // Update the edit box with the contents of m_strEdit

    UpdateFont();

    // Trigger an OnSize so scrollbars will appear
    m_MyEdit.SetWindowPos( NULL, 0, 0, 0, 0, SWP_NOZORDER );
    CRect rc;
    GetClientRect(&rc);
    OnSize( 0, rc.Width(), rc.Height() );

    m_MyEdit.RequestResize();

    CFormView::OnInitialUpdate();
}

void CTextView::UpdateFont()
{
    DWORD dwFontSize = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("FontSize"), 9 );
    CString strFontName = AfxGetApp()->GetProfileString( TEXT("Settings"), TEXT("FontName"), TEXT("Courier") );
    CHARFORMAT cf;
    cf.cbSize = sizeof(cf);
    cf.dwMask = CFM_SIZE | CFM_FACE | CFM_ITALIC;
    if( GetDocument()->UsingExternalEditor() )
        cf.dwEffects = CFM_ITALIC;
    else
        cf.dwEffects = 0;
    cf.yHeight = 20 * dwFontSize;
    lstrcpy( cf.szFaceName, strFontName );
    m_MyEdit.SetDefaultCharFormat(cf);
}

void CTextView::OnChangeEdit() 
{
    UpdateData();
    GetDocument()->SetCode(m_strEdit);

    SetTimer( 0, 1000, NULL );
}


void CTextView::OnTimer(UINT nIDEvent)
{
    if( nIDEvent == 0 ) // User edited the doc and has been idle for 1000ms, so recompile
    {
        KillTimer( 0 );
        GetDocument()->Compile();
    }
    else if( nIDEvent == 1 ) // Check to see if doc has changed in external editor
    {
        CFileStatus fileStatus;
        CTime timeLastChanged;
        if( GetDocument()->GetLastModifiedTime( &timeLastChanged ) )
        {
            if( timeLastChanged > m_timeLastChanged )
            {
                GetDocument()->ReloadFromFile();
                m_strEdit = ((CEffectDoc*)GetDocument())->GetCode();
                UpdateData(FALSE);
                m_timeLastChanged = timeLastChanged;
            }
        }
    }
}

void CTextView::SelectLine(int nLine)
{
    int nBegin = m_MyEdit.LineIndex( nLine );
    int nEnd = nBegin + m_MyEdit.LineLength( nLine );
    m_MyEdit.SetSel( nBegin, nBegin/*nEnd*/ );
}

void CTextView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
    CView::OnUpdate( pSender, lHint, pHint );

    int iLineSelected = GetDocument()->GetSelectedLine();
    if( iLineSelected != -1 )
        SelectLine( iLineSelected );
	
}

void CTextView::OnEditUndo() 
{
    m_MyEdit.Undo();	
}

void CTextView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable( m_MyEdit.CanUndo() );
}

void CTextView::OnEditCopy() 
{
    m_MyEdit.Copy();	
}

void CTextView::OnEditCut() 
{
    m_MyEdit.Cut();	
}

void CTextView::OnEditPaste() 
{
    m_MyEdit.Paste();	
}

void CTextView::SetExternalEditorMode(BOOL bExternal)
{
    UpdateFont();
    m_MyEdit.SetReadOnly( bExternal );
    if( bExternal )
    {
        GetDocument()->GetLastModifiedTime( &m_timeLastChanged );
        SetTimer( 1, 1000, NULL );
    }
    else
    {
        KillTimer( 1 );
    }
}


/////////////////////////////////////////////////////////////////////////////
// CMyRichEditCtrl



BEGIN_MESSAGE_MAP(CMyRichEditCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(CMyRichEditCtrl)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyRichEditCtrl::CMyRichEditCtrl()
{
	m_hRELibrary = LoadLibrary( TEXT("RICHED20.DLL") );
}

CMyRichEditCtrl::~CMyRichEditCtrl()
{
	if( m_hRELibrary )
		FreeLibrary( m_hRELibrary );
}

void CMyRichEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    // Convert tabs to spaces
    if( nChar == 9 )
    {
        BOOL bKeepTabs = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("Keep Tabs"), FALSE );
        int numSpaces = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("Num Spaces"), 4 );

        if( bKeepTabs )
        {
            SendMessage(EM_REPLACESEL, TRUE, (LPARAM)"\t");
        }
        else
        {
            for( int iSpace = 0; iSpace < numSpaces; iSpace++ )
                SendMessage(EM_REPLACESEL, TRUE, (LPARAM)" ");
        }
    }
    else
    {
	    CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
    }
}
