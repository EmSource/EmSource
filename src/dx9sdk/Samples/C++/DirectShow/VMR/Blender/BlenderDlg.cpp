//------------------------------------------------------------------------------
// File: BlenderDlg.cpp
//
// Desc: DirectShow sample code - an MFC application that blends two video
//       streams using the Video Mixing Renderer.  Controls are provided for
//       manipulating each video stream's X, Y, size, and alpha values.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Blender.h"
#include "BlenderDlg.h"
#include <tchar.h>
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//  Global data
//
typedef struct
{
    FLOAT     xPos,  yPos;
    FLOAT     xSize, ySize;
    FLOAT     Alpha;
    BOOL      bFlipped, bMirrored;
} STRM_PARAM;

// Default initialization values for the video streams
const STRM_PARAM strParamInit[1] = {
    {0.0F, 0.0F, 1.0F, 1.0F, 0.7F, 0, 0}
};

// Contains initial and current values for the video streams
STRM_PARAM strParam[2] = {
    {0.0F, 0.0F, 1.0F, 1.0F, 0.7F, 0, 0},
    {0.0F, 0.0F, 1.0F, 1.0F, 0.7F, 0, 0}
};

// Resource IDs for dialog controls (for simple enumeration)
const int NUM_SLIDERS=10;
int nSliderIDs[NUM_SLIDERS] = {
    IDC_SLIDER_X,       IDC_SLIDER_X2,
    IDC_SLIDER_Y,       IDC_SLIDER_Y2,
    IDC_SLIDER_WIDTH,   IDC_SLIDER_WIDTH2,
    IDC_SLIDER_HEIGHT,  IDC_SLIDER_HEIGHT2,
    IDC_SLIDER_ALPHA,   IDC_SLIDER_ALPHA2
    };

const int NUM_CHECKS=4;
int nCheckIDs[NUM_CHECKS] = {
    IDC_CHECK_FLIP,     IDC_CHECK_FLIP2,
    IDC_CHECK_MIRROR,   IDC_CHECK_MIRROR2
};


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
// CBlenderDlg dialog

CBlenderDlg::CBlenderDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CBlenderDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CBlenderDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBlenderDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CBlenderDlg)
    DDX_Control(pDX, IDC_POSITION, m_StrPosition);
    DDX_Control(pDX, IDC_DURATION, m_StrDuration);
    DDX_Control(pDX, IDC_STOP, m_ButtonStop);
    DDX_Control(pDX, IDC_PAUSE, m_ButtonPause);
    DDX_Control(pDX, IDC_PLAY, m_ButtonPlay);
    DDX_Control(pDX, IDC_SCREEN, m_Screen);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBlenderDlg, CDialog)
    //{{AFX_MSG_MAP(CBlenderDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_STREAM1, OnButtonStream1)
    ON_BN_CLICKED(IDC_BUTTON_STREAM2, OnButtonStream2)
    ON_BN_CLICKED(IDC_STOP, OnStop)
    ON_BN_CLICKED(IDC_PAUSE, OnPause)
    ON_BN_CLICKED(IDC_PLAY, OnPlay)
    ON_WM_CLOSE()
    ON_WM_DESTROY()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_CHECK_FLIP, OnCheckFlip)
    ON_BN_CLICKED(IDC_CHECK_MIRROR, OnCheckMirror)
    ON_BN_CLICKED(IDC_CHECK_FLIP2, OnCheckFlip2)
    ON_BN_CLICKED(IDC_CHECK_MIRROR2, OnCheckMirror2)
    ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlenderDlg message handlers

void CBlenderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBlenderDlg::OnPaint() 
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
        // When using VMR Windowless mode, you must explicitly tell the
        // renderer when to repaint the video in response to WM_PAINT
        // messages.  This is most important when the video is stopped
        // or paused, since the VMR won't be automatically updating the
        // window as the video plays.
        MoveVideoWindow();
        RepaintVideo();

        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBlenderDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

BOOL CBlenderDlg::OnInitDialog()
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
    
    // Initialize COM
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    // Verify that the VMR is present on this system
    if(!VerifyVMR())
        exit(1);

    // Initialize the video screen
    m_Screen.ModifyStyle(0, WS_CLIPCHILDREN);
    m_hwndScreen = m_Screen.GetSafeHwnd();

    // Initialize global variables
    pGB = NULL;
    pMC = NULL;
    pMS = NULL;
    pME = NULL;
    pWC = NULL;
    pMix = NULL;
    m_szFile1[0] = m_szFile2[0] = TEXT('\0');
    g_wTimerID = 0;
    InitControls();
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}

#ifdef REGISTER_FILTERGRAPH

HRESULT CBlenderDlg::AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
    IMoniker * pMoniker;
    IRunningObjectTable *pROT;
    if (FAILED(GetRunningObjectTable(0, &pROT))) 
    {
        return E_FAIL;
    }

    WCHAR wsz[128];
    wsprintfW(wsz, L"FilterGraph %08x pid %08x", (DWORD_PTR)pUnkGraph, 
              GetCurrentProcessId());

    HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
    if (SUCCEEDED(hr)) 
    {
        // Use the ROTFLAGS_REGISTRATIONKEEPSALIVE to ensure a strong reference
        // to the object.  Using this flag will cause the object to remain
        // registered until it is explicitly revoked with the Revoke() method.
        //
        // Not using this flag means that if GraphEdit remotely connects
        // to this graph and then GraphEdit exits, this object registration 
        // will be deleted, causing future attempts by GraphEdit to fail until
        // this application is restarted or until the graph is registered again.
        hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, 
                            pMoniker, pdwRegister);
        pMoniker->Release();
    }

    pROT->Release();
    return hr;
}

void CBlenderDlg::RemoveGraphFromRot(DWORD pdwRegister)
{
    IRunningObjectTable *pROT;

    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) 
    {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
}

#endif

void CBlenderDlg::Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    // Display a message box with the formatted string
    MessageBox(szBuffer, TEXT("VMR Blender Sample"), MB_OK);
}

BOOL CBlenderDlg::GetClipFileName(LPTSTR szName)
{
    static OPENFILENAME ofn={0};
    static BOOL bSetInitialDir = FALSE;

    // Reset filename
    *szName = 0;

    // Fill in standard structure fields
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = GetSafeHwnd();
    ofn.lpstrFilter       = FILE_FILTER_TEXT;
    ofn.lpstrCustomFilter = NULL;
    ofn.nFilterIndex      = 1;
    ofn.lpstrFile         = szName;
    ofn.nMaxFile          = MAX_PATH;
    ofn.lpstrTitle        = TEXT("Open Video File...\0");
    ofn.lpstrFileTitle    = NULL;
    ofn.lpstrDefExt       = TEXT("*\0");
    ofn.Flags             = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;

    // Remember the path of the first selected file
    if (bSetInitialDir == FALSE)
    {
        ofn.lpstrInitialDir = DEFAULT_MEDIA_PATH;
        bSetInitialDir = TRUE;
    }
    else
        ofn.lpstrInitialDir = NULL;

    // Create the standard file open dialog and return its result
    return GetOpenFileName((LPOPENFILENAME)&ofn);
}

void CBlenderDlg::OnButtonStream1() 
{
    // Select a file
    if (GetClipFileName(m_szFile1))
    {
        // Enable the playback buttons
        InitButtons();

        // Reset the stream sliders and check buttons
        InitControls();

        // Display the selected filename and clear the second filename
        GetDlgItem(IDC_STATIC_STREAM1)->SetWindowText(m_szFile1);
        GetDlgItem(IDC_STATIC_STREAM2)->SetWindowText(TEXT("\0"));

        // Disable playback buttons until two files are properly loaded
        m_ButtonPlay.EnableWindow(FALSE);
        m_ButtonStop.EnableWindow(FALSE);
        m_ButtonPause.EnableWindow(FALSE);

        // Cleanup from the last playback, if it exists
        FreeDirectShow();

        // Enable the second stream select button
        GetDlgItem(IDC_BUTTON_STREAM2)->EnableWindow(TRUE);
    }
}

void CBlenderDlg::OnButtonStream2() 
{
    HRESULT hr;

    // Select a file
    if (GetClipFileName(m_szFile2))
    {
        // Display the selected file name
        GetDlgItem(IDC_STATIC_STREAM2)->SetWindowText(m_szFile2);

        // Initialize the global strParam structure with default values
        InitStreamParams();

        // Initialize DirectShow and configure the VMR for two streams.
        // Both media files will be rendered.
        hr = InitializeVideo();

        if (SUCCEEDED(hr))
        {
            EnableControls(TRUE);
            SetSliders();
            DisplayFileDuration();

            // Set video position, size, and alpha values
            UpdatePinPos(0);
            UpdatePinPos(1);
            UpdatePinAlpha(0);
            UpdatePinAlpha(1);
        }
    }
}

HRESULT CBlenderDlg::InitializeVideo(void)
{
    USES_CONVERSION;
    WCHAR wFile1[MAX_PATH], wFile2[MAX_PATH];
    HRESULT hr;

    // Clear open dialog remnants before calling RenderFile()
    UpdateWindow();

    // Convert filenames to wide character strings for RenderFile()
    wcsncpy(wFile1, T2W(m_szFile1), NUMELMS(wFile1)-1);
    wcsncpy(wFile2, T2W(m_szFile2), NUMELMS(wFile2)-1);
    wFile1[MAX_PATH-1] = wFile2[MAX_PATH-1] = 0;

    // Create a DirectShow GraphBuilder object
    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                         IID_IGraphBuilder, (void **)&pGB));

    if(SUCCEEDED(hr))
    {
        // Create the Video Mixing Renderer and add it to the graph
        JIF(InitializeWindowlessVMR());
        
        // Have the graph builder construct its the appropriate graph automatically
        JIF(pGB->RenderFile(wFile1, NULL));
        JIF(pGB->RenderFile(wFile2, NULL));

        // Get DirectShow interfaces
        JIF(pGB->QueryInterface(IID_IMediaControl, (void **)&pMC));
        JIF(pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME));
        JIF(pGB->QueryInterface(IID_IMediaSeeking, (void **)&pMS));

        // Have the graph signal event via window callbacks
        JIF(pME->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0));

#ifdef REGISTER_FILTERGRAPH
        m_dwGraphRegister = 0;
        hr = AddGraphToRot(pGB, &m_dwGraphRegister);
        if (FAILED(hr))
            Msg(TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
#endif

        // Run the graph to play the media files
        OnPlay();

        // Set initial movie position
        MoveVideoWindow();
        RepaintVideo();
    }

    return hr;
}

HRESULT CBlenderDlg::FreeDirectShow(void)
{
    HRESULT hr=S_OK;

    // Stop the position timer
    StopTimer();

    // Stop playback
    if (pMC)
        hr = pMC->Stop();

    // Disable event callbacks
    if (pME)
        hr = pME->SetNotifyWindow((OAHWND)NULL, 0, 0);

    // Release all active interfaces
    SAFE_RELEASE(pMC);
    SAFE_RELEASE(pMS);
    SAFE_RELEASE(pME);
    SAFE_RELEASE(pGB);
    SAFE_RELEASE(pWC);      // IVMRWindowlessControl
    SAFE_RELEASE(pMix);     // IVMRMixerControl

    return hr;
}

void CBlenderDlg::OnStop() 
{
    HRESULT hr;

    // Update button state
    m_ButtonPlay.EnableWindow(TRUE);
    m_ButtonStop.EnableWindow(FALSE);
    m_ButtonPause.EnableWindow(FALSE);

    // Stop the position timer
    StopTimer();

    // Stop playback
    if (pMC)
        hr = pMC->Stop();

    // Wait for the stop to propagate to all filters
    WaitForState(State_Stopped);

    // Reset to first frame of movie
    if (pMS)
    {
        LONGLONG pos=0;
        hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                               NULL, AM_SEEKING_NoPositioning);
    }

    // Refresh the current position text display
    UpdatePosition();
}

void CBlenderDlg::OnPause() 
{
    HRESULT hr;

    // Update button state
    m_ButtonPlay.EnableWindow(TRUE);
    m_ButtonPause.EnableWindow(FALSE);

    // Stop the position timer
    StopTimer();

    // Pause playback
    if (pMC)
        hr = pMC->Pause();

    // Wait for the pause to propagate to all filters
    WaitForState(State_Paused);
}

void CBlenderDlg::OnPlay() 
{
    HRESULT hr;

    // Update button state
    m_ButtonPlay.EnableWindow(FALSE);
    m_ButtonStop.EnableWindow(TRUE);
    m_ButtonPause.EnableWindow(TRUE);

    // Start the filter graph
    if (pMC)
        hr = pMC->Run();

    // Wait for the stop to propagate to all filters
    WaitForState(State_Running);

    // Start the position timer
    StartTimer();
}

void CBlenderDlg::InitButtons(void)
{
    // Set the default state of the media control buttons
    m_ButtonPlay.EnableWindow(TRUE);
    m_ButtonStop.EnableWindow(FALSE);
    m_ButtonPause.EnableWindow(FALSE);
}


BOOL CBlenderDlg::VerifyVMR(void)
{
    HRESULT hres;

    // Verify that the VMR exists on this system
    IBaseFilter* pBF = NULL;
    hres = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, CLSCTX_INPROC,
        IID_IBaseFilter, (LPVOID *)&pBF);

    if(SUCCEEDED(hres))
    {
        // VMR successfully created, so release it
        pBF->Release();
        return TRUE;
    }
    else
    {
        MessageBox(
            TEXT("This application requires the Video Mixing Renderer, which is present\r\n")
            TEXT("only on Windows XP systems with hardware video acceleration enabled.\r\n\r\n")

            TEXT("The Video Mixing Renderer (VMR) is not enabled when viewing a \r\n")
            TEXT("remote Windows XP machine through a Remote Desktop session.\r\n")
            TEXT("You can run VMR-enabled applications only on your local machine.\r\n\r\n")

            TEXT("To verify that hardware acceleration is enabled on a Windows XP\r\n")
            TEXT("system, follow these steps:\r\n")
            TEXT("-----------------------------------------------------------------------\r\n")
            TEXT(" - Open 'Display Properties' in the Control Panel\r\n")
            TEXT(" - Click the 'Settings' tab\r\n")
            TEXT(" - Click on the 'Advanced' button at the bottom of the page\r\n")
            TEXT(" - Click on the 'Troubleshooting' tab in the window that appears\r\n")
            TEXT(" - Verify that the 'Hardware Acceleration' slider is at the rightmost position\r\n")

            TEXT("\r\nThis sample will now exit."),

            TEXT("Video Mixing Renderer capabilities are required"), MB_OK);
        
        return FALSE;
    }
}

HRESULT CBlenderDlg::InitializeWindowlessVMR(void)
{
    IBaseFilter* pVmr = NULL;

    // Create the VMR and add it to the filter graph.
    HRESULT hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL,
                     CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr);
    if (SUCCEEDED(hr)) 
    {
        hr = pGB->AddFilter(pVmr, L"Video Mixing Renderer");
        if (SUCCEEDED(hr)) 
        {
            // Set the rendering mode and number of streams
            IVMRFilterConfig* pConfig;

            hr = pVmr->QueryInterface(IID_IVMRFilterConfig, (void**)&pConfig);
            if( SUCCEEDED(hr)) 
            {
                hr = pConfig->SetRenderingMode(VMRMode_Windowless);

                // Set two streams to enable mixing of both videos
                hr = pConfig->SetNumberOfStreams(2);
                pConfig->Release();
            }

            // Set the bounding window and border for the video
            hr = pVmr->QueryInterface(IID_IVMRWindowlessControl, (void**)&pWC);
            if( SUCCEEDED(hr)) 
            {
                hr = pWC->SetVideoClippingWindow(m_hwndScreen);
                hr = pWC->SetBorderColor(RGB(0,0,0));    // Black border

                // Set the VMR's color key to the same value as the MFC
                // dialog's default gray brush.
                hr = pWC->SetColorKey(RGB(128,128,128)); // Dialog's gray brush
            }

            // Get the mixer control interface for later manipulation of video 
            // stream output rectangles and alpha values
            hr = pVmr->QueryInterface(IID_IVMRMixerControl, (void**)&pMix);
        }

        pVmr->Release();
    }

    return hr;
}

void CBlenderDlg::OnClose() 
{
    // Release DirectShow interfaces
    FreeDirectShow();

    // Release COM
    CoUninitialize();

    CDialog::OnClose();
}

void CBlenderDlg::OnDestroy() 
{
    // Release DirectShow interfaces
    FreeDirectShow();   

    CDialog::OnDestroy();
}

HRESULT CBlenderDlg::UpdatePinAlpha(int nStreamID)
{
    HRESULT hr=S_OK;

    // Get a pointer to the selected stream's information
    STRM_PARAM* p = &strParam[nStreamID];

    // Update the alpha value for the selected stream
    if(pMix)
        hr = pMix->SetAlpha(nStreamID, p->Alpha);

    if (SUCCEEDED(hr))
        DisplayAlpha(nStreamID);

    return hr;
}

void CBlenderDlg::DisplayAlpha(int nStreamID)
{
    USES_CONVERSION;
    int nID[2] = {IDC_STATIC_ALPHA, IDC_STATIC_ALPHA2};
    char szAnsiLabel[32];
    TCHAR szLabel[32];

    // The wsprintf method doesn't support floating point, so use the
    // ANSI version and convert to UNICODE if necessary.
    sprintf(szAnsiLabel, "(%02.2f)\0", strParam[nStreamID].Alpha);
    _tcsncpy(szLabel, A2T(szAnsiLabel), NUMELMS(szLabel));

    CWnd *pWnd = GetDlgItem(nID[nStreamID]);
    pWnd->SetWindowText(szLabel);
}

HRESULT CBlenderDlg::UpdatePinPos(int nStreamID)
{
    HRESULT hr=S_OK;

    // Get a pointer to the selected stream's information
    STRM_PARAM* p = &strParam[nStreamID];

    // Set the left, right, top, and bottom coordinates
    NORMALIZEDRECT r = {p->xPos, p->yPos, p->xPos + p->xSize, p->yPos + p->ySize};

    // If mirrored, swap the left/right coordinates in the destination rectangle
    if (strParam[nStreamID].bMirrored)
    {
        float fLeft = strParam[nStreamID].xPos;
        float fRight = strParam[nStreamID].xPos + strParam[nStreamID].xSize;
        r.left = fRight;
        r.right = fLeft;
    }

    // If flipped, swap the top/bottom coordinates in the destination rectangle
    if (strParam[nStreamID].bFlipped)
    {
        float fTop = strParam[nStreamID].yPos;
        float fBottom = strParam[nStreamID].yPos + strParam[nStreamID].ySize;
        r.top = fBottom;
        r.bottom = fTop;
    }

    DisplayCoordinates(nStreamID, r);

    // Update the destination rectangle for the selected stream
    if(pMix)
        hr = pMix->SetOutputRect(nStreamID, &r);

    return hr;
}

void CBlenderDlg::DisplayCoordinates(int nStreamID, NORMALIZEDRECT& r)
{
    USES_CONVERSION;
    int nID[2] = {IDC_STATIC_GROUP1, IDC_STATIC_GROUP2};

    // Display composition space coordinates for this stream
    char szAnsiLabel[128];
    TCHAR szLabel[128];

    // The wsprintf method doesn't support floating point, so use the
    // ANSI version and convert to UNICODE if necessary.
    sprintf(szAnsiLabel, "Stream %d  (%02.2f x %02.2f) at (%02.2f, %02.2f)\0",
             nStreamID, (float) (r.right - r.left), (float)(r.bottom - r.top),
             r.left, r.top);  
    _tcsncpy(szLabel, A2T(szAnsiLabel), NUMELMS(szLabel));

    CWnd *pWnd = GetDlgItem(nID[nStreamID]);
    pWnd->SetWindowText(szLabel);
}

void CBlenderDlg::MoveVideoWindow(void)
{
    HRESULT hr;
    RECT rcDest={0};

    // Track the movement of the container window and resize as needed
    if (pWC)
    {
        m_Screen.GetClientRect(&rcDest);
        hr = pWC->SetVideoPosition(NULL, &rcDest);
    }
}

void CBlenderDlg::InitStreamParams(void)
{
    // Set default values for X, Y, Width, Height and Alpha values
    // for both streams.  These values will be adjusted by the user
    // at runtime by manipulating sliders and dialog controls.
    CopyMemory(&strParam[0], strParamInit, sizeof(strParamInit));
    CopyMemory(&strParam[1], strParamInit, sizeof(strParamInit));
}

HRESULT CBlenderDlg::RepaintVideo(void)
{
    HRESULT hr=S_OK;

    // Request the VMR to repaint the video.  This is especially 
    // necessary if the graph is paused or stopped, since the VMR
    // won't be automatically updating the screen when playing video frames.
    if (pWC)
    {
        HDC hdc;

        hdc = ::GetDC(m_hwndScreen);
        hr = pWC->RepaintVideo(m_hwndScreen, hdc);
        ::ReleaseDC(m_hwndScreen, hdc);
    }

    return hr;
} 

LRESULT CBlenderDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // Field notifications from the DirectShow filter graph manager
    // and those posted by the application
    switch (message)
    {
        case WM_HSCROLL:
            HandleHorizontalTrackbar(wParam, lParam);
            break;

        case WM_VSCROLL:
            HandleVerticalTrackbar(wParam, lParam);
            break;

        case WM_GRAPHNOTIFY:
            HandleGraphEvent();
            break;
    }

    return CDialog::WindowProc(message, wParam, lParam);
}

HRESULT CBlenderDlg::HandleGraphEvent(void)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

    // Make sure that we don't access the media event interface
    // after it has already been released.
    if (!pME)
        return S_OK;

    // Process all queued events
    while(SUCCEEDED(pME->GetEvent(&evCode, (LONG_PTR *) &evParam1,
                   (LONG_PTR *) &evParam2, 0)))
    {
        // Free memory associated with callback, since we're not using it
        hr = pME->FreeEventParams(evCode, evParam1, evParam2);

        // If this is the end of the clip, reset to beginning
        if(EC_COMPLETE == evCode)
        {
            // Restart from the beginning.  The OnStop call
            // seeks to the beginning of the clip.
            OnStop();
            OnPlay();
        }
    }

    return hr;
}

HRESULT CBlenderDlg::WaitForState(OAFilterState fsReq)
{
    HRESULT hr=S_OK;
    OAFilterState fs;

    if (pMC)
    {
        // Read the current graph state
        hr = pMC->GetState(500, &fs);

        // Wait for the state to propagate to all filters
        while ((SUCCEEDED(hr)) && (fs != fsReq))
            hr = pMC->GetState(500, &fs);
    }

    return hr;
}

void CBlenderDlg::StartTimer() 
{
    // Cancel any pending timer event
    StopTimer();

    // Create a new timer
    g_wTimerID = SetTimer(TIMERID, TICKLEN, NULL);
}

void CBlenderDlg::StopTimer() 
{
    // Cancel the timer
    if(g_wTimerID)        
    {                
        KillTimer(g_wTimerID);
        g_wTimerID = 0;
    }
}

void CBlenderDlg::OnTimer(UINT nIDEvent) 
{
    UpdatePosition();
    
    CDialog::OnTimer(nIDEvent);
}

void CBlenderDlg::OnCheckFlip() 
{
    strParam[0].bFlipped ^= 1;
    UpdatePinPos(0);
}

void CBlenderDlg::OnCheckMirror() 
{
    strParam[0].bMirrored ^= 1;
    UpdatePinPos(0);
}

void CBlenderDlg::OnCheckFlip2() 
{
    strParam[1].bFlipped ^= 1;
    UpdatePinPos(1);
}

void CBlenderDlg::OnCheckMirror2() 
{
    strParam[1].bMirrored ^= 1;
    UpdatePinPos(1);
}

void CBlenderDlg::OnButtonAbout() 
{
    CAboutDlg dlgAbout;
    dlgAbout.DoModal(); 
}

void CBlenderDlg::InitControls(void)
{
    int i;

    // Initialize and disable all stream sliders and check boxes
    for (i=0; i < NUM_SLIDERS; i++)
    {
        CSliderCtrl *pSlider;

        pSlider = (CSliderCtrl *) GetDlgItem(nSliderIDs[i]);
        pSlider->SetRange(0, 100, TRUE);
        pSlider->SetTicFreq(10);
        pSlider->EnableWindow(FALSE);
    }
    for (i=0; i < NUM_CHECKS; i++)
    {
        CButton *pButton = (CButton *) GetDlgItem(nCheckIDs[i]);
        pButton->SetCheck(0);
        pButton->EnableWindow(FALSE);
    }
}

void CBlenderDlg::EnableControls(BOOL bEnable)
{
    int i;

    // Enable/disable all stream sliders and check boxes.
    // These controls should be disabled until all streams are loaded
    // and the filter graph is fully configured.
    for (i=0; i < NUM_SLIDERS; i++)
    {
        CSliderCtrl *pSlider;

        pSlider = (CSliderCtrl *) GetDlgItem(nSliderIDs[i]);
        pSlider->EnableWindow(bEnable);
    }
    for (i=0; i < NUM_CHECKS; i++)
    {
        CButton *pButton = (CButton *) GetDlgItem(nCheckIDs[i]);
        pButton->EnableWindow(bEnable);
    }
}

void CBlenderDlg::SetSliders(void)
{
    CSliderCtrl *pSlider;

    // Set the sliders to reflect the current state of their 
    // associated streams, using data stored in the global strParam array

    // Set X, Y, and Alpha for stream 1
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_X);
    pSlider->SetPos((int) (100.0 * strParam[0].xPos));
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_Y);
    pSlider->SetPos((int) (100.0 * strParam[0].yPos));
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_ALPHA);
    pSlider->SetPos((int) (100.0 * strParam[0].Alpha));

    // Set width and height for stream 1
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_WIDTH);
    pSlider->SetPos((int) (100.0 * (strParam[0].xSize - strParam[0].xPos)));
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_HEIGHT);
    pSlider->SetPos((int) (100.0 * (strParam[0].ySize - strParam[0].yPos)));

    // Set X, Y, and Alpha for stream 2
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_X2);
    pSlider->SetPos((int) (100.0 * strParam[1].xPos));
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_Y2);
    pSlider->SetPos((int) (100.0 * strParam[1].yPos));
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_ALPHA2);
    pSlider->SetPos((int) (100.0 * strParam[1].Alpha));

    // Set width and height for stream 2
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_WIDTH2);
    pSlider->SetPos((int) (100.0 * (strParam[1].xSize - strParam[1].xPos)));
    pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER_HEIGHT2);
    pSlider->SetPos((int) (100.0 * (strParam[1].ySize - strParam[1].yPos)));
}

void CBlenderDlg::HandleHorizontalTrackbar(WPARAM wParam, LPARAM lParam)
{
    if (wParam != SB_ENDSCROLL)
    {
        // First determine which slider was adjusted
        HWND hwnd = (HWND) lParam;
        int nID = ::GetWindowLong(hwnd, GWL_ID);
        CSliderCtrl *pSlider = (CSliderCtrl *)GetDlgItem(nID);

        // Read the current value of the adjusted slider
        DWORD dwPosition = pSlider->GetPos();

        // Convert the 0-100 decimal value to a 0.0 to 1.0 float value
        // to represent position in VMR composition space
        FLOAT fPos = (FLOAT) dwPosition * (FLOAT) 0.01;

        switch (nID)
        {
            case IDC_SLIDER_X:
                strParam[0].xPos = fPos;
                UpdatePinPos(0);
                break;
            case IDC_SLIDER_X2:
                strParam[1].xPos = fPos;
                UpdatePinPos(1);
                break;

            case IDC_SLIDER_WIDTH:
                strParam[0].xSize = fPos;
                UpdatePinPos(0);
                break;
            case IDC_SLIDER_WIDTH2:
                strParam[1].xSize = fPos;
                UpdatePinPos(1);
                break;

            case IDC_SLIDER_ALPHA:
                strParam[0].Alpha = fPos;
                UpdatePinAlpha(0);
                break;
            case IDC_SLIDER_ALPHA2:
                strParam[1].Alpha = fPos;
                UpdatePinAlpha(1);
                break;
        }
    }
}

void CBlenderDlg::HandleVerticalTrackbar(WPARAM wParam, LPARAM lParam)
{
    if (wParam != SB_ENDSCROLL)
    {
        // First determine which slider was adjusted
        HWND hwnd = (HWND) lParam;
        int nID = ::GetWindowLong(hwnd, GWL_ID);
        CSliderCtrl *pSlider = (CSliderCtrl *)GetDlgItem(nID);

        // Read the current value of the adjusted slider
        DWORD dwPosition = pSlider->GetPos();

        // Convert the 0-100 decimal value to a 0.0 to 1.0 float value
        // to represent position in VMR composition space
        FLOAT fPos = (FLOAT) dwPosition * (FLOAT) 0.01;

        switch (nID)
        {
            case IDC_SLIDER_Y:
                strParam[0].yPos = fPos;
                UpdatePinPos(0);
                break;
            case IDC_SLIDER_Y2:
                strParam[1].yPos = fPos;
                UpdatePinPos(1);
                break;

            case IDC_SLIDER_HEIGHT:
                strParam[0].ySize = fPos;
                UpdatePinPos(0);
                break;
            case IDC_SLIDER_HEIGHT2:
                strParam[1].ySize = fPos;
                UpdatePinPos(1);
                break;
        }
    }
}

HRESULT CBlenderDlg::DisplayFileDuration(void)
{
    HRESULT hr;

    if (!pMS)
        return E_NOINTERFACE;

    // Initialize the display in case we can't read the duration
    m_StrDuration.SetWindowText(TEXT("<00:00.000>"));

    // Is media time supported for this file?
    if (S_OK != pMS->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME))
        return E_NOINTERFACE;

    // Read the time format to restore later
    GUID guidOriginalFormat;
    hr = pMS->GetTimeFormat(&guidOriginalFormat);
    if (FAILED(hr))
        return hr;

    // Ensure media time format for easy display
    hr = pMS->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
    if (FAILED(hr))
        return hr;

    // Read the file's duration
    LONGLONG llDuration;
    hr = pMS->GetDuration(&llDuration);
    if (FAILED(hr))
        return hr;

    // Return to the original format
    if (guidOriginalFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = pMS->SetTimeFormat(&guidOriginalFormat);
        if (FAILED(hr))
            return hr;
    }

    // Convert the LONGLONG duration into human-readable format
    unsigned long nTotalMS = (unsigned long) llDuration / 10000; // 100ns -> ms
    int nMS = nTotalMS % 1000;
    int nSeconds = nTotalMS / 1000;
    int nMinutes = nSeconds / 60;
    nSeconds %= 60;

    // Update the display
    TCHAR szDuration[24];
    wsprintf(szDuration, _T("%02dm:%02d.%03ds\0"), nMinutes, nSeconds, nMS);
    m_StrDuration.SetWindowText(szDuration);

    return hr;
}

void CBlenderDlg::UpdatePosition(void) 
{
    HRESULT hr;
    REFERENCE_TIME rtNow;

    // Read the current stream position
    hr = pMS->GetCurrentPosition(&rtNow);
    if (FAILED(hr))
        return;

    // Convert the LONGLONG duration into human-readable format
    unsigned long nTotalMS = (unsigned long) rtNow / 10000; // 100ns -> ms
    int nSeconds = nTotalMS / 1000;
    int nMinutes = nSeconds / 60;
    nSeconds %= 60;

    // Update the display
    TCHAR szPosition[24], szCurrentString[24];
    wsprintf(szPosition, _T("%02dm:%02ds\0"), nMinutes, nSeconds);

    // Read current string and compare to the new string.  To prevent flicker,
    // don't update this label unless the string has changed.
    m_StrPosition.GetWindowText(szCurrentString, 24);

    if (_tcscmp(szCurrentString, szPosition))
        m_StrPosition.SetWindowText(szPosition);
}


