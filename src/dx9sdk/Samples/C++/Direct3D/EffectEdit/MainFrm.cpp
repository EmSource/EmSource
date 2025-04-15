// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "EffectEdit.h"

#include "MainFrm.h"
#include "EffectDoc.h"
#include <D3D9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "UIElements.h"
#include "RenderView.h"
#include "OptionsView.h"
#include "TextView.h"
#include "ErrorsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySplitterWnd

void CMySplitterWnd::ActivateNext(BOOL bPrev)
{
    ASSERT_VALID(this);

    // find the coordinate of the current pane
    int row, col;
    if (GetActivePane(&row, &col) == NULL)
    {
        TRACE0("Warning: Cannot go to next pane - there is no current view.\n");
        return;
    }
    ASSERT(row >= 0 && row < m_nRows);
    ASSERT(col >= 0 && col < m_nCols);

    // determine next pane
    if (bPrev)
    {
        // prev
        if (--col < 0)
        {
            col = m_nCols - 1;
            if (--row < 0)
            {
                if( m_pSplitterWndPrev != NULL )
                {                               
                    row = m_pSplitterWndPrev->GetRowCount() - 1;
                    col = m_pSplitterWndPrev->GetColumnCount() - 1;
                    m_pSplitterWndPrev->SetActivePane(row, col);
                    CWnd* pWnd = m_pSplitterWndPrev->GetActivePane();
                    if( pWnd->IsKindOf( RUNTIME_CLASS( CRenderView ) ) )
                        m_pSplitterWndPrev->ActivateNext( bPrev );
                    return;
                }
                row = m_nRows - 1;
            }
        }
    }
    else
    {
        // next
        if (++col >= m_nCols)
        {
            col = 0;
            if (++row >= m_nRows)
            {
                if( m_pSplitterWndNext != NULL )
                {
                    m_pSplitterWndNext->SetActivePane(0, 0);
                    CWnd* pWnd = m_pSplitterWndPrev->GetActivePane();
                    if( pWnd->IsKindOf( RUNTIME_CLASS( CRenderView ) ) )
                        m_pSplitterWndPrev->ActivateNext( bPrev );
                    return;
                }
                row = 0;
            }
        }
    }

    // set newly active pane
    SetActivePane(row, col);
    CWnd* pWnd = GetActivePane();
    if( pWnd->IsKindOf( RUNTIME_CLASS( CRenderView ) ) )
        ActivateNext( bPrev );
}


void CMySplitterWnd::StopTracking(BOOL bAccept)
{
    m_bPreserveLastPaneSize = false;
    CSplitterWnd::StopTracking(bAccept);
}


void CMySplitterWnd::RecalcLayout()
{
    CRect rectClient;
    GetClientRect(rectClient);
    rectClient.InflateRect(-m_cxBorder, -m_cyBorder);

    if( m_nCols > 1 )
    {
        // It's the horizontal splitter
    }
    else
    {
        // It's one of the vertical splitters
        if( m_bPreserveLastPaneSize )
        {
            // Try to preserve the last row's current size
            int nLastCurSize = m_pRowInfo[m_nRows - 1].nCurSize;
            if( nLastCurSize != -1 )
            {
                if( rectClient.Height() - nLastCurSize - m_cySplitter > m_pRowInfo[0].nMinSize )
                    m_pRowInfo[0].nIdealSize = rectClient.Height() - nLastCurSize - m_cySplitter;
            }
            m_bPreserveLastPaneSize = false;
        }
    }
    
    CSplitterWnd::RecalcLayout();
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_COMMAND(ID_VIEW_RENDER, OnRender)
    ON_COMMAND(ID_VIEW_CHANGEDEVICE, OnViewChangeDevice)
    ON_WM_SIZE()
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
        | /*CBRS_GRIPPER | */CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this) ||
        !m_wndStatusBar.SetIndicators(indicators,
          sizeof(indicators)/sizeof(UINT)))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }
    ShowControlBar(&m_wndStatusBar, FALSE, FALSE); // Initially hide status bar

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
    // Set window size/placement to previous setting stored in the registry
    UINT wpSize;
    WINDOWPLACEMENT* pwp;
    if( AfxGetApp()->GetProfileBinary( TEXT("Settings"), TEXT("WindowPlacement"), (BYTE**)&pwp, &wpSize ) )
    {
        SetWindowPlacement( pwp );
        delete[] pwp;
    }

    // Create a vertical splitter with 1 row, 2 columns
    if (!m_wndSplitterMain.CreateStatic(this, 1, 2))
    {
        TRACE0("Failed to create vertical splitter\n");
        return FALSE;
    }

    // Add the left splitter pane - which is a nested splitter with 2 rows
    if (!m_wndSplitterLeft.CreateStatic(
        &m_wndSplitterMain,     // our parent window is the main vertical splitter
        2, 1,               // the new splitter is 2 rows, 1 column
        WS_CHILD | WS_VISIBLE,
        m_wndSplitterMain.IdFromRowCol(0, 0)
       ))
    {
        TRACE0("Failed to create left splitter\n");
        return FALSE;
    }
    
    // Add the right splitter pane - which is a nested splitter with 2 rows
    if (!m_wndSplitterRight.CreateStatic(
        &m_wndSplitterMain,     // our parent window is the main vertical splitter
        2, 1,               // the new splitter is 2 rows, 1 column
        WS_CHILD | WS_VISIBLE,
        m_wndSplitterMain.IdFromRowCol(0, 1)
       ))
    {
        TRACE0("Failed to create right splitter\n");
        return FALSE;
    }

    m_wndSplitterRight.SetPrev( &m_wndSplitterLeft );
    m_wndSplitterRight.SetNext( &m_wndSplitterLeft );
    
    m_wndSplitterLeft.SetPrev( &m_wndSplitterRight );
    m_wndSplitterLeft.SetNext( &m_wndSplitterRight );

    INT cx = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("LeftColumnWidth"), 400 );
    INT cyTopLeft = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("TopLeftPaneHeight"), 500 );
    INT cyTopRight = AfxGetApp()->GetProfileInt( TEXT("Settings"), TEXT("TopRightPaneHeight"), 400 );

    m_wndSplitterMain.SetColumnInfo( 0, cx, 50 );

    // Top right view: a CRenderView
    if (!m_wndSplitterRight.CreateView(0, 0,
        pContext->m_pNewViewClass, CSize(50, cyTopRight), pContext))
    {
        TRACE0("Failed to create CRenderView pane\n");
        return FALSE;
    }
    
    // Bottom right view: a COptionsView
    if (!m_wndSplitterRight.CreateView(1, 0,
        RUNTIME_CLASS(COptionsView), CSize(50, 50), pContext))
    {
        TRACE0("Failed to create COptionsView pane\n");
        return FALSE;
    }
    
    // Top left view: a CTextView
    if (!m_wndSplitterLeft.CreateView(0, 0,
        RUNTIME_CLASS(CTextView), CSize(50, cyTopLeft), pContext))
    {
        TRACE0("Failed to create CTextView pane\n");
        return FALSE;
    }
    
    // Bottom left view: a CErrorsView
    if (!m_wndSplitterLeft.CreateView(1, 0,
        RUNTIME_CLASS(CErrorsView), CSize(50, 50), pContext))
    {
        TRACE0("Failed to create CErrorsView pane\n");
        return FALSE;
    }
    return TRUE;
}

void CMainFrame::OnRender() 
{
    CRenderView* pRenderView = (CRenderView*)m_wndSplitterRight.GetPane(0, 0);
    pRenderView->SendMessage(WM_COMMAND, ID_VIEW_RENDER);
}

void CMainFrame::ActivateTextView()
{
    m_wndSplitterLeft.GetPane(0, 0)->SetActiveWindow();
}

void CMainFrame::ActivateErrorsView()
{
    m_wndSplitterLeft.GetPane(1, 0)->SetActiveWindow();
}

void CMainFrame::ActivateOptionsView()
{
    m_wndSplitterRight.GetPane(1, 0)->SetActiveWindow();
}

void CMainFrame::TextViewUpdateFont()
{
    CTextView* pTextView = (CTextView*)m_wndSplitterLeft.GetPane(0, 0);
    if( pTextView != NULL )
        pTextView->UpdateFont();
}


void CMainFrame::OnViewChangeDevice() 
{
    CRenderView* pRenderView = (CRenderView*)m_wndSplitterRight.GetPane(0, 0);
    pRenderView->ChangeDevice();
}

void CMainFrame::SelectLine(int iLine)
{
    CTextView* pTextView = (CTextView*)m_wndSplitterLeft.GetPane(0, 0);
    pTextView->SelectLine( iLine );
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
    CFrameWnd::OnSize(nType, cx, cy);
    
    // TODO: Add your message handler code here
    m_wndSplitterLeft.PreserveLastPaneSize();
    m_wndSplitterRight.PreserveLastPaneSize();
}

void CMainFrame::OnClose() 
{
    WINDOWPLACEMENT wp;
    GetWindowPlacement( &wp );
    AfxGetApp()->WriteProfileBinary( TEXT("Settings"), TEXT("WindowPlacement"), (BYTE*)&wp, wp.length );

    INT cxCur;
    INT cxMin;
    m_wndSplitterMain.GetColumnInfo( 0, cxCur, cxMin );

    AfxGetApp()->WriteProfileInt( TEXT("Settings"), TEXT("LeftColumnWidth"), cxCur );

    INT cyCur;
    INT cyMin;
    m_wndSplitterLeft.GetRowInfo( 0, cyCur, cyMin );
    AfxGetApp()->WriteProfileInt( TEXT("Settings"), TEXT("TopLeftPaneHeight"), cyCur );

    m_wndSplitterRight.GetRowInfo( 0, cyCur, cyMin );
    AfxGetApp()->WriteProfileInt( TEXT("Settings"), TEXT("TopRightPaneHeight"), cyCur );

    CFrameWnd::OnClose();
}
