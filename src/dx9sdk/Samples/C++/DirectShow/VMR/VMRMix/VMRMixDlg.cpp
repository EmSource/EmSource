//------------------------------------------------------------------------------
// File: VMRMixDlg.cpp
//
// Desc: DirectShow sample code
//       Implementation of the settings dialog
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <tchar.h>
#include "VMRMix.h"
#include "VMRMixDlg.h"
#include "DlgWait.h"
#include "Demonstration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CDemonstration;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVMRMixDlg dialog

CVMRMixDlg::CVMRMixDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CVMRMixDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CVMRMixDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_bFullScreen = true;
    m_bUseBitmap = true;
    m_nMaxSources = 16;
    m_nStreams = 5;         // Initial number of streams
    m_eState = eStop;
    m_szFolder[0] = 0;      // Null-terminate
}

void CVMRMixDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CVMRMixDlg)
    DDX_Control(pDX, IDC_CHECK_FULLSCREEN, m_chkFullScreen);
    DDX_Control(pDX, IDC_CHECK_APPLYBITMAP, m_chkBitmap);
    DDX_Control(pDX, IDC_SLIDER, m_Slider);
    DDX_Control(pDX, IDOK, m_btnOK);
    DDX_Control(pDX, IDC_BUTTON_PLAY, m_btnPlay);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVMRMixDlg, CDialog)
    //{{AFX_MSG_MAP(CVMRMixDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
    ON_COMMAND(ID_FILE_SELECTMEDIAFOLDER, SelectFolder)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, OnReleasedcaptureSlider)
    ON_BN_CLICKED(IDC_CHECK_APPLYBITMAP, OnCheckApplybitmap)
    ON_BN_CLICKED(IDC_CHECK_FULLSCREEN, OnCheckFullscreen)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVMRMixDlg message handlers

//-------------------------------------------------------------
// Windows message processing for CVMRMixDlg
//-------------------------------------------------------------

void CVMRMixDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVMRMixDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVMRMixDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

BOOL CVMRMixDlg::OnInitDialog()
{
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

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon


    //
    // Start VMRMix-specific initialization
    //
    SetNumberOfStreams(m_nStreams);

    // Upon initialization, ask user to specify media folder.
    // If failed, app cannot continue and quits
    while( !_tcslen(m_szFolder) )
    {
        SelectFolder();

        if( !_tcslen(m_szFolder) )
        {
            // If no media directory was specified, just exit
            PostQuitMessage(0);
            return FALSE;
        }

        m_MediaList.Initialize( m_szFolder );
        if( 0 == m_MediaList.Size() )
        {
            AfxMessageBox(_T("Selected folder does not contain any media files."));
            m_szFolder[0] = 0;      // Null-terminate
        }
    }

    // Read settings for the selected media file
    BOOL bRes = GetMediaSettings();

    if( bRes )
    {
        m_nMaxSources = (m_MediaList.Size() > 16) ? 16 : m_MediaList.Size();
        m_Slider.SetRange(1, m_nMaxSources);

        if( m_nStreams > m_nMaxSources)
            SetNumberOfStreams( m_nMaxSources );
    }

    m_chkFullScreen.SetCheck( m_bFullScreen);
    m_chkBitmap.SetCheck( m_bUseBitmap);

    RECT rSlider;
    m_Slider.GetWindowRect( &rSlider );
    LPARAM lparam = MAKELPARAM( (rSlider.left + rSlider.right)/2, (rSlider.top + rSlider.bottom)/2);
    m_Slider.SendMessage(WM_LBUTTONUP, NULL, lparam);

    return bRes;  // return TRUE  unless you set the focus to a control
}

void CVMRMixDlg::OnButtonPlay()
{
    ShowWindow(SW_HIDE);
    RunDemonstration();
    ShowWindow(SW_SHOW);
}

void CVMRMixDlg::OnCheckApplybitmap()
{
    m_bUseBitmap = ( m_chkBitmap.GetCheck() ) ? true : false;
}

void CVMRMixDlg::OnCheckFullscreen()
{
    m_bFullScreen = ( m_chkFullScreen.GetCheck() ) ? true : false;
}

void CVMRMixDlg::OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
    int nPos = m_Slider.GetPos();
    SetNumberOfStreams( nPos);

    if (pResult)
        *pResult = 0;
}


//-------------------------------------------------------------
// CVMRMixDlg::SetNumberOfStreams
// Desc: Sets number of source streams for presentation (m_nStreams)
//       and positions slider
// Return: true if successful and false otherwise
//-------------------------------------------------------------
bool CVMRMixDlg::SetNumberOfStreams( int n)
{
    if( n<1 || n>m_nMaxSources )
        return false;

    TCHAR szMsg[MAX_PATH];
    m_nStreams = n;

    _stprintf( szMsg, _T("%d\0"), m_nStreams);
    GetDlgItem(IDC_STATIC_NSRC)->SetWindowText(szMsg);
    m_Slider.SetPos( n);

    return true;
}


void CVMRMixDlg::SelectFolder()
{
    OPENFILENAME ofn;
    TCHAR  szBuffer[MAX_PATH];
    bool bFolderIsBad = true;

    _tcscpy(szBuffer, TEXT(""));

    static TCHAR szFilter[]  = _T("Video Files (.MOV, .AVI, .MPG, .VOB, .QT)\0*.AVI;*.MOV;*.MPG;*.VOB;*.QT\0") \
                              _T("All Files (*.*)\0*.*\0\0");

    ofn.lStructSize         = sizeof(OPENFILENAME);
    ofn.hwndOwner           = NULL;
    ofn.hInstance           = NULL;
    ofn.lpstrFilter         = szFilter;
    ofn.nFilterIndex        = 1;
    ofn.lpstrCustomFilter   = NULL;
    ofn.nMaxCustFilter      = 0;
    ofn.lpstrFile           = szBuffer;
    ofn.nMaxFile            = _MAX_PATH;
    ofn.lpstrFileTitle      = NULL;
    ofn.nMaxFileTitle       = 0;
    ofn.lpstrInitialDir     = NULL;
    ofn.lpstrTitle          = _T("Please open any video file to select the folder...");
    ofn.Flags               = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.nFileOffset         = 0;
    ofn.nFileExtension      = 0;
    ofn.lpstrDefExt         = NULL;
    ofn.lCustData           = 0L;
    ofn.lpfnHook            = NULL;
    ofn.lpTemplateName  = NULL;

    while( bFolderIsBad )
    {
        if (GetOpenFileName (&ofn))  // user specified a file
        {
            TCHAR szTmp[MAX_PATH];
            TCHAR *psz = NULL;
            _tcsncpy(szTmp, ofn.lpstrFile, NUMELMS(szTmp));

            // Verify that the folder contains a media file
            _tcsrev(szTmp);
            psz = _tcsstr(szTmp, _T("\\"));
            if( !psz )
            {
                if(IDNO == AfxMessageBox(_T("You must select a file folder with at least one media file. Continue?"), 
                                          MB_YESNO | MB_ICONQUESTION))
                {
                    bFolderIsBad = false;
                }
                else
                {
                    continue;
                }

            }
            else
            {
                _tcsncpy( m_szFolder, psz, NUMELMS(m_szFolder));
                _tcsrev( m_szFolder );
                return;
            }

        }// if
        else
        {
            // User pressed CANCEL on the file selection dialog
            break;
        }

    }// while( bFolderIsBad )

    if( bFolderIsBad )
    {
        _tcscpy( m_szFolder, _T("\0"));
    }
    return;
}


void CVMRMixDlg::PostNcDestroy()
{
    CDialog::PostNcDestroy();
}


//---------------------------------------------------------------
// CVMRMixDlg::GetMediaSettings
// Desc: scans media settings list, verifies media files,
//       and reads duration info
// return: true if success and false otherwise
//---------------------------------------------------------------
bool CVMRMixDlg::GetMediaSettings()
{
    HRESULT hr;
    int n;
    bool bRes;
    TCHAR szMsg[MAX_PATH], szInfo[MAX_PATH];

    CMediaList * pML = NULL;
    CMediaList MLClone; // cloned and verified copy of the media list
    CMediaList mlDirty;

    if( 2 > m_MediaList.Size())
    {
        AfxMessageBox(_T("You must select a folder with at least two valid media files.\r\n\r\nPlease try again."), MB_OK);
        exit(-1);
    }

    CDlgWait dlgWait(m_MediaList.Size());

    m_MediaList.Clone(m_MediaList.Size(), &mlDirty, 0);
    m_MediaList.Clean();

    pML = &mlDirty;
    ASSERT(pML);

    dlgWait.Create(IDD_DIALOG_PROGRESS);
    dlgWait.ShowWindow( SW_SHOW);

    for(n=0; n<pML->Size(); n++)
    {
        MLClone.Clean();

        bRes = pML->Clone(1, &MLClone, n);
        if( false == bRes )
        {
            _stprintf( szMsg, _T("CVMRModule::GetMediaSettings(): failed to clone element %ld, setting source for 5 sec\0"),n);
            DbgOutString( szMsg);
            pML->GetItem(n)->m_llDuration = (5L * 10000000L);
            continue;
        }

        IMediaSeeking * pMediaSeeking = NULL;
        LONGLONG llDuration = 0L;

        CVMRCore core(this, VMRMode_Renderless, NULL, &MLClone);

        hr = core.Play(true);
        if( FAILED(hr) )
        {
            _stprintf( szMsg, _T("*** failed to render source %s, method returned %s\n\0"),
                     pML->GetItem(n)->m_szPath, hresultNameLookup(hr));
            DbgOutString( szMsg);
            continue;
        }

        hr = core.GetIGraphBuilder()->QueryInterface(__uuidof(IMediaSeeking), reinterpret_cast<void**>(&pMediaSeeking));
        if( FAILED(hr))
        {
            DbgOutString(_T("Cannot find IMediaSeeking interface\n"));
            dlgWait.EndDialog(IDOK);
            continue;
        }

        // get source parameters
        core.GetMediaControl()->Stop();
        hr = pMediaSeeking->GetDuration( &llDuration);
        if( FAILED(hr) || llDuration < 100L)
        {
            DbgOutString(_T("Failed to obtain sample duration, setting to 5 sec\n"));
            llDuration = 5L * 10000000L;
        }

        pML->GetItem(n)->m_llDuration = llDuration;

        _stprintf( szInfo, _T("Source %d: name:%s, duration: %ld\n\0"),
                 n, pML->GetItem(n)->m_szPath, llDuration);
        DbgOutString(szInfo);

        SAFERELEASE(pMediaSeeking);

        // this media file is valid, we can add it to the media list
        SourceInfo * psi = NULL;
        psi = new SourceInfo;
        pML->GetItem(n)->CopyTo( psi);
        m_MediaList.Add(psi);
        dlgWait.SetPos(n);
    }

    dlgWait.EndDialog(IDOK);
    if( 1 > m_MediaList.Size() )
    {
        AfxMessageBox(_T("Some media sources are not supported with this ")
                      _T("application\r\n\r\nPlease try again with other sources."), 
                      MB_OK);
        exit(-1);
    }
    m_MediaList.AdjustDuration();
    return true;
}


//---------------------------------------------------------------
// CVMRMixDlg::RunDemonstration
// Desc: runs demonstration module
// return: HRESULT code
//---------------------------------------------------------------
HRESULT CVMRMixDlg::RunDemonstration()
{
    HRESULT hr = S_OK;

    m_MediaList.Shuffle();

    CDemonstration demo(this, &m_MediaList, m_nStreams, &hr);
    if( FAILED(hr))
    {
        DbgOutString(_T("Failed to initialize class CDemonstration\n"));
        return hr;
    }

    clock_t tStart = clock();
    hr = demo.Perform();

    TCHAR szMsg[MAX_PATH];
    _stprintf( szMsg, _T("TIME:: Actual: %ld ms, Expected: %ld ms\n\0"),
            (clock() - tStart) * 1000 / CLOCKS_PER_SEC, 
            m_MediaList.GetAvgDuration() / 10000);
    DbgOutString( szMsg);

    if( FAILED(hr))
    {
        DbgOutString(_T("Failed to Perform() demonstration\n"));
    }

    return hr;
}


