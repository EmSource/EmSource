// ErrorsView.cpp : implementation file
//

#include "stdafx.h"
#include "EffectDoc.h"
#include "EffectEdit.h"
#include "ErrorsView.h"
#include "DXUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorsView

IMPLEMENT_DYNCREATE(CErrorsView, CFormView)

CErrorsView::CErrorsView()
    : CFormView(CErrorsView::IDD)
{
    //{{AFX_DATA_INIT(CErrorsView)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_bNeedToParseErrors = FALSE;
}

CErrorsView::~CErrorsView()
{
}

void CErrorsView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CErrorsView)
    DDX_Control(pDX, IDC_LIST, m_ListBox);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CErrorsView, CFormView)
    //{{AFX_MSG_MAP(CErrorsView)
    ON_WM_SIZE()
    ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorsView diagnostics

#ifdef _DEBUG
void CErrorsView::AssertValid() const
{
    CFormView::AssertValid();
}

void CErrorsView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CEffectDoc* CErrorsView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEffectDoc)));
    return (CEffectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CErrorsView message handlers

void CErrorsView::OnSize(UINT nType, int cx, int cy) 
{
    SetScrollSizes( MM_TEXT, CSize(cx, cy) );

    CFormView::OnSize(nType, cx, cy);
    
    CWnd* pGroup = GetDlgItem(IDC_GROUPBOX);
    CWnd* pList = GetDlgItem(IDC_LIST);

    if( pGroup != NULL && 
        pList != NULL )
    {
        CRect rc;

        pGroup->SetWindowPos(NULL, 7, 2, cx - 7 - 4, cy - 2 - 10, SWP_NOZORDER);

        pGroup->GetClientRect(&rc);
        pGroup->MapWindowPoints(this, &rc);

        rc.InflateRect( -10, -17, -10, -10 );
        pList->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
    }
}


void CErrorsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
    if( m_bNeedToParseErrors )
        ParseErrors();
    CView::OnUpdate( pSender, lHint, pHint );
}


void CErrorsView::ParseErrors()
{
    if( m_ListBox.GetSafeHwnd() == NULL )
    {
        m_bNeedToParseErrors = TRUE;
        return;
    }

    CString strErrors = GetDocument()->GetErrorString();
    // Rebuild list based on new error data
    while( m_ListBox.DeleteString( 0 ) > 0 )
    {
    }

    CString strEntry;
    for( INT ich = 0; ich < strErrors.GetLength(); ich++ )
    {
        TCHAR ch = strErrors[ich];
        if( ch == TEXT('\n') )
        {
            m_ListBox.AddString(strEntry);
            strEntry.Empty();
        }
        else
        {
            strEntry += ch;
        }
    }

    if( m_ListBox.GetCount() == 0 )
        m_ListBox.AddString( TEXT("No errors") );
    m_ListBox.SetCurSel(0);

    // Set horizontal extent of list box to length of longest string, so scrolling will work.

    // Find the longest string in the list box.
    CString      str;
    CSize      sz;
    int      dx = 0;
    TEXTMETRIC   tm;
    CDC*      pDC = m_ListBox.GetDC();
    CFont*      pFont = m_ListBox.GetFont();

    // Select the listbox font, save the old font
    CFont* pOldFont = pDC->SelectObject(pFont);
    // Get the text metrics for avg char width
    pDC->GetTextMetrics(&tm); 

    for (int i = 0; i < m_ListBox.GetCount(); i++)
    {
          m_ListBox.GetText(i, str);
       sz = pDC->GetTextExtent(str);

       // Add the avg width to prevent clipping
       sz.cx += tm.tmAveCharWidth;

       if (sz.cx > dx)
                dx = sz.cx;
    }
    // Select the old font back into the DC
    pDC->SelectObject(pOldFont);
    m_ListBox.ReleaseDC(pDC);

    // Set the horizontal extent so every character of all strings 
    // can be scrolled to.
    m_ListBox.SetHorizontalExtent(dx);
}

void CErrorsView::OnDblclkList() 
{
    int iLine = m_ListBox.GetCurSel();
    if( iLine < 0 )
        return;
    CString str;
    m_ListBox.GetText( iLine, str );

    if( 1 == _stscanf( str, TEXT("(%d)"), &iLine ) )
    {
        iLine--; // go from one-based (d3dx line numbers) to zero-based (CEdit line numbers)
        ((CEffectEditApp*)AfxGetApp())->SelectLine( iLine );
        PostMessage(WM_COMMAND, ID_PREV_PANE);
    }
}
