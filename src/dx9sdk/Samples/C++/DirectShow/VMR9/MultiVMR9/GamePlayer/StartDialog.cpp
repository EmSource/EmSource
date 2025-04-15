//------------------------------------------------------------------------------
// File: StartDialog.cpp
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GamePlayer.h"
#include "StartDialog.h"
#include <Cderr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern HINSTANCE g_hInstance;

const UINT_PTR g_TimerID = 0x54321;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    enum { IDD = IDD_ABOUTBOX };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CStartDialog dialog


/******************************Public*Routine******************************\
* CStartDialog
* constructor
\**************************************************************************/
CStartDialog::CStartDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CStartDialog::IDD, pParent)
    , m_pSession( NULL )
    , m_nTimer( NULL )
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

/******************************Public*Routine******************************\
* DoDataExchange
* 
\**************************************************************************/
void CStartDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SOURCES, m_ListSources);
}

/******************************Public*Routine******************************\
* MESSAGE_MAP
* 
\**************************************************************************/
BEGIN_MESSAGE_MAP(CStartDialog, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_START, OnBnClickedButtonStart)
    ON_BN_CLICKED(IDC_BUTTON_STOP, OnBnClickedButtonStop)
    ON_WM_DESTROY()
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CStartDialog message handlers

/******************************Public*Routine******************************\
* OnInitDialog
* 
\**************************************************************************/
BOOL CStartDialog::OnInitDialog()
{
    HRESULT hr = S_OK;
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    m_ListSources.DeleteColumn(0);
    m_ListSources.InsertColumn(0, TEXT("Media files"), LVCFMT_LEFT, 300, 0);

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    m_nTimer = SetTimer( g_TimerID, 500, 0);

    UpdateControls_();

    return TRUE;  // return TRUE  unless you set the focus to a control
}

/******************************Public*Routine******************************\
* OnSysCommand
* 
\**************************************************************************/
void CStartDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

/******************************Public*Routine******************************\
* OnPaint
* 
\**************************************************************************/
void CStartDialog::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

/******************************Public*Routine******************************\
* OnQueryDragIcon
* 
\**************************************************************************/
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStartDialog::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

/******************************Public*Routine******************************\
* OnBnClickedButtonAdd
* response to "Add" button
\**************************************************************************/
void CStartDialog::OnBnClickedButtonAdd()
{
    TCHAR achPath[MAX_PATH];
    TCHAR achFilePath[MAX_PATH];
    OPENFILENAME ofn;
    DWORD dwErr = 0;

    GetCurrentDirectory( MAX_PATH, achPath);

    static TCHAR szFilter[]  = TEXT("Video Files (.mpg;.mpeg;.avi;.wmv;.asf)\0*.mpg;*.mpeg;*.avi;*.wmv;*.asf\0") \
                               TEXT("All Files (*.*)\0*.*\0\0");
    lstrcpy(achFilePath, TEXT(""));

    ZeroMemory( &ofn, sizeof(ofn) );
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner           = NULL;
    ofn.hInstance           = NULL;
    ofn.lpstrFilter         = szFilter;
    ofn.nFilterIndex        = 1;
    ofn.lpstrCustomFilter   = NULL;
    ofn.nMaxCustFilter      = 0;
    ofn.lpstrFile           = achFilePath;
    ofn.nMaxFile            = MAX_PATH;
    ofn.lpstrFileTitle      = NULL;
    ofn.nMaxFileTitle       = 0;
    ofn.lpstrInitialDir     = NULL;
    ofn.lpstrFileTitle      = NULL;
    ofn.nMaxFileTitle       = 0;
    ofn.lpstrInitialDir     = NULL;
    ofn.nFileOffset         = 0;
    ofn.nFileExtension      = 0;
    ofn.lpstrDefExt         = NULL;
    ofn.lCustData           = 0L;
    ofn.lpfnHook            = NULL;
    ofn.lpTemplateName  = NULL; 

    if( TRUE == GetOpenFileName(&ofn ))
    {
        int nItem = m_ListSources.GetItemCount();
        CString str = ofn.lpstrFile;
        m_ListSources.InsertItem( nItem, str);
    }
    UpdateData( FALSE);
    SetCurrentDirectory( achPath );
}

/******************************Public*Routine******************************\
* OnBnClickedButtonDelete
* response to "Delete" button
\**************************************************************************/
void CStartDialog::OnBnClickedButtonDelete()
{
    int nItem = m_ListSources.GetNextItem( -1, LVNI_SELECTED|LVNI_FOCUSED);
    if( -1 == nItem )
        return;

    m_ListSources.DeleteItem(nItem);
    UpdateData( FALSE);
}

/******************************Public*Routine******************************\
* OnBnClickedButtonStart
* response to "Start" button
\**************************************************************************/
void CStartDialog::OnBnClickedButtonStart()
{
    HRESULT hr = S_OK;
    int nItems = 0;
    DWORD_PTR dwID = NULL;
    CVMR9Subgraph* pSource = NULL;
    
    if( m_pSession )
        return;

    m_pSession = new CGamePlayerSession();
    if( FAILED(hr))
    {
        AfxMessageBox(TEXT("Failed to create a new CGamePlayerSession"), MB_OK, 0);
        return;
    }

    hr = m_pSession->Initialize();
    if( FAILED(hr))
    {
        AfxMessageBox(TEXT("Failed to initialize CGamePlayerSession"), MB_OK, 0);
        return;
    }

    nItems = m_ListSources.GetItemCount();

    for( int i=0; i<nItems; i++)
    {
        TCHAR achPath[MAX_PATH];
        WCHAR wcPath[MAX_PATH];

        m_ListSources.GetItemText( i, 0, achPath, MAX_PATH);
#ifdef UNICODE
        wcscpy( wcPath, achPath);
#else
        MultiByteToWideChar(CP_ACP, 0, achPath, -1, wcPath, MAX_PATH); 
#endif
        hr = m_pSession->AddSource( wcPath, dwID );
        if( FAILED(hr))
        {
            CString strMsg;
            strMsg.Format(TEXT("Failed to add source\r\n%s\r\nto the session. Error code 0x%08x"),
                achPath, hr);
            AfxMessageBox( strMsg, MB_OK, 0);
        }
        pSource = m_pSession->GetSubgraph( dwID);

        if( pSource )
        {
            pSource->Run();
        }
        m_ListSources.SetItemData( i, dwID);
    }

    if( FAILED(hr))
    {
        CString strMsg;
        strMsg.Format(TEXT("Failed to run the session. Error code 0x%08x"), hr);
        AfxMessageBox( strMsg, MB_OK, 0);
    }
    UpdateControls_();
}

/******************************Public*Routine******************************\
* OnBnClickedButtonStop
* response to "Stop" button
\**************************************************************************/
void CStartDialog::OnBnClickedButtonStop()
{
    if( m_pSession )
    {
        delete m_pSession;
        m_pSession = NULL;
    }

    UpdateControls_();
}

/******************************Public*Routine******************************\
* OnDestroy
* WM_DESTROY
\**************************************************************************/
void CStartDialog::OnDestroy()
{
    CDialog::OnDestroy();

    if( m_pSession )
    {
        delete m_pSession;
        m_pSession = NULL;
    }

    ::KillTimer( GetSafeHwnd(), m_nTimer);
}

/******************************Public*Routine******************************\
* OnTimer
\**************************************************************************/
void CStartDialog::OnTimer(UINT nIDEvent)
{
    if( m_pSession )
    {
        m_pSession->LoopSources();
    }

    CDialog::OnTimer(nIDEvent);
}

/////////////////////////////// PRIVATE DOMAIN //////////////////////////////

/******************************Private*Routine*****************************\
* UpdateControls_
* udate controls depending on the state of the application
\**************************************************************************/
void CStartDialog::UpdateControls_()
{
    if( GetDlgItem(IDC_BUTTON_START))
        GetDlgItem(IDC_BUTTON_START)->EnableWindow( m_pSession ? FALSE : TRUE );

    if( GetDlgItem(IDC_BUTTON_STOP))
        GetDlgItem(IDC_BUTTON_STOP)->EnableWindow( m_pSession ? TRUE : FALSE );

    if( GetDlgItem(IDC_BUTTON_ADD))
        GetDlgItem(IDC_BUTTON_ADD)->EnableWindow( m_pSession ? FALSE : TRUE );

    if( GetDlgItem(IDC_BUTTON_DELETE))
        GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow( m_pSession ? FALSE : TRUE );

    if( GetDlgItem(IDOK))
        GetDlgItem(IDOK)->EnableWindow( m_pSession ? FALSE : TRUE );

    UpdateData( FALSE );
}

