//------------------------------------------------------------------------------
// File: AudioboxDlg.cpp
//
// Desc: DirectShow sample code - implementation of CAudioboxDlg class.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <atlbase.h>
#include <shlobj.h>
#include "Audiobox.h"
#include "AudioboxDlg.h"
#include "mediatypes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CSIDL values are defined in <shlobj.h> and require Windows 98 or greater.
// If the user is using VC 6.0 with pre-Win98 headers, these values
// may not yet be defined.
#ifndef CSIDL_MYMUSIC
#define CSIDL_MYMUSIC                   0x000d        // "My Music" folder
#define CSIDL_PERSONAL                  0x0005        // "My Documents" folder
#define CSIDL_DESKTOPDIRECTORY          0x0010        // <user name>\Desktop
#endif

// Global data
FILTER_STATE g_psCurrent=State_Stopped;
BOOL g_bLooping=FALSE, g_bGlobalMute=FALSE, g_bRandomize=FALSE;

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
// CAudioboxDlg dialog

CAudioboxDlg::CAudioboxDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CAudioboxDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CAudioboxDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAudioboxDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAudioboxDlg)
    DDX_Control(pDX, IDC_CHECK_FAVORITE, m_ButtonFavorite);
    DDX_Control(pDX, IDC_SLIDER_VOLUME, m_VolumeSlider);
    DDX_Control(pDX, IDC_LIST_DIR, m_ListDir);
    DDX_Control(pDX, IDC_LIST_FILES, m_ListFiles);
    DDX_Control(pDX, IDC_STATIC_POSITION, m_StrPosition);
    DDX_Control(pDX, IDC_SLIDER, m_Seekbar);
    DDX_Control(pDX, IDC_STATIC_DURATION, m_StrDuration);
    DDX_Control(pDX, IDC_EDIT_MEDIADIR, m_EditMediaDir);
    DDX_Control(pDX, IDC_SPIN_FILES, m_SpinFiles);
    DDX_Control(pDX, IDC_CHECK_MUTE, m_CheckMute);
    DDX_Control(pDX, IDC_BUTTON_STOP, m_ButtonStop);
    DDX_Control(pDX, IDC_BUTTON_PLAY, m_ButtonPlay);
    DDX_Control(pDX, IDC_BUTTON_PAUSE, m_ButtonPause);
    DDX_Control(pDX, IDC_CHECK_RANDOMIZE, m_CheckRandomize);
    DDX_Control(pDX, IDC_CHECK_LOOP, m_CheckLoop);
    DDX_Control(pDX, IDC_STATIC_FILEDATE, m_StrFileDate);
    DDX_Control(pDX, IDC_STATIC_FILESIZE, m_StrFileSize);
    DDX_Control(pDX, IDC_STATIC_FILELIST, m_StrFileList);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAudioboxDlg, CDialog)
    //{{AFX_MSG_MAP(CAudioboxDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_INITMENUPOPUP()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CLOSE()
    ON_LBN_SELCHANGE(IDC_LIST_FILES, OnSelectFile)
    ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnPause)
    ON_BN_CLICKED(IDC_BUTTON_PLAY, OnPlay)
    ON_BN_CLICKED(IDC_BUTTON_STOP, OnStop)
    ON_BN_CLICKED(IDC_CHECK_MUTE, OnCheckMute)
    ON_BN_CLICKED(IDC_CHECK_LOOP, OnCheckLoop)
    ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FILES, OnDeltaposSpinFiles)
    ON_BN_CLICKED(IDC_BUTTON_SET_MEDIADIR, OnButtonSetMediadir)
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_CHECK_RANDOMIZE, OnCheckRandomize)
    ON_LBN_DBLCLK(IDC_LIST_DIR, OnDblclkListDir)
    ON_COMMAND(ID_ADD_FAVORITE, OnAddFavorite)
    ON_COMMAND(ID_CLEAR_FAVORITES, OnClearFavorites)
    ON_BN_CLICKED(IDC_CHECK_FAVORITE, OnCheckFavorite)
    //}}AFX_MSG_MAP
    ON_COMMAND_RANGE(ID_FAVORITE_BASE, ID_FAVORITE_MAX, OnSelectFavorite)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAudioboxDlg message handlers

void CAudioboxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAudioboxDlg::OnPaint() 
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
HCURSOR CAudioboxDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}


/////////////////////////////////////////////////////////////////////////////
// CAudioboxDlg DirectShow code and message handlers


BOOL CAudioboxDlg::OnInitDialog()
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
    
    ////////////////////////////////////////////////////////////////////////
    //
    //  DirectShow-specific initialization code

    // Initialize COM
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    
    // Initialize DirectShow interfaces
    m_pGB = NULL;
    m_pMS = NULL;
    m_pMC = NULL;
    m_pME = NULL;
    m_pBA = NULL;

    // Initialize global variables
    g_wTimerID = 0;
    g_rtTotalTime = 0;
    m_lCurrentVolume = VOLUME_FULL;
    m_nCurrentFileSelection = -1;     // No selection yet
    ClearFileInfo();
    m_szCurrentDir[0] = m_szActiveDir[0] = TEXT('\0');

    // Initialize DirectShow and query for needed interfaces
    HRESULT hr = InitDirectShow();
    if(FAILED(hr))
    {
        FreeDirectShow();
        RetailOutput(TEXT("Failed to initialize DirectShow!  hr=0x%x\r\n"), hr);
        return FALSE;
    }

    // Propagate the files list and select the first item
    InitMediaDirectory();
   
    // Initialize seeking trackbar range
    m_Seekbar.SetRange(0, 100, TRUE);
    m_Seekbar.SetTicFreq(10);
    m_VolumeSlider.SetRange(0, MINIMUM_VOLUME, TRUE);
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}


void CAudioboxDlg::InitMediaDirectory(void)
{
    // Fill the media file list, starting with the directory passed
    // on the command line.  If no directory is passed, then read the
    // default media path for the DirectX SDK.
    TCHAR szDir[MAX_PATH + 10];
    LONG lResult=0;

    if (theApp.m_lpCmdLine[0] == L'\0')
    {
        // First attempt to set the initial folder to the user's
        // 'My Music' folder, where many audio files are often stored
        if (FALSE == InitCustomDirectory(CSIDL_MYMUSIC))
        {
            // If that fails, try the DirectX SDK's media path instead,
            // which ships with a predefined set of audio/video media files.
            lResult = GetDXMediaPath(szDir);

            // If the DirectX SDK is not installed, use the Windows media
            // directory instead.
            if (lResult != 0)
            {
                if (GetWindowsDirectory(szDir, MAX_PATH))
                {
                    _tcscat(szDir, _T("\\Media\\\0") );
                }
                else
                {
                    szDir[0] = TEXT('\\');  // Default to root directory
                    szDir[1] = TEXT('\0');
                }
            }
        }
        else
        {
            _tcsncpy(szDir, m_szCurrentDir, MAX_PATH);
            szDir[MAX_PATH-1] = 0;  // Ensure null-termination
        }
    }
    else
    {
        // The user supplied a startup folder
        _tcsncpy(szDir, theApp.m_lpCmdLine, MAX_PATH);
        szDir[MAX_PATH-1] = 0;      // Ensure null-termination
    }

    // Save current directory name for later use
    _tcsncpy(m_szCurrentDir, szDir, NUMELMS(m_szCurrentDir));
    m_szCurrentDir[NUMELMS(m_szCurrentDir) - 1] = 0;  // Ensure NULL termination

    m_EditMediaDir.SetLimitText(MAX_PATH);
    m_EditMediaDir.SetWindowText(szDir);

    // Find all files in this directory and fill the list box
    FillFileList(m_szCurrentDir);
}


LONG CAudioboxDlg::GetDXMediaPath(TCHAR *szPath)
{
    HKEY  hKey;
    DWORD dwType, dwSize = MAX_PATH;

    // Open the appropriate registry key
    LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                _T("Software\\Microsoft\\DirectX SDK"),
                                0, KEY_READ, &hKey );
    if( ERROR_SUCCESS != lResult )
        return -1;

    // Start with DirectX9 SDK
    lResult = RegQueryValueEx( hKey, _T("DX9SDK Samples Path"), NULL,
                              &dwType, (BYTE*)szPath, &dwSize );

    if( ERROR_SUCCESS != lResult )
    {
        // Next try DirectX 8.1 SDK
        lResult = RegQueryValueEx( hKey, _T("DX81SDK Samples Path"), NULL,
                                  &dwType, (BYTE*)szPath, &dwSize );
        if( ERROR_SUCCESS != lResult )
        {
            // Finally, try DirectX 8.0 SDK
            lResult = RegQueryValueEx( hKey, _T("DX8SDK Samples Path"), NULL,
                                      &dwType, (BYTE*)szPath, &dwSize );
            if( ERROR_SUCCESS != lResult )
            {
                RegCloseKey( hKey );
                return -1;
            }
        }
    }

    RegCloseKey( hKey );

    // Now that we have the location of the installed SDK samples path,
    // append the name of the folder where media files are stored
    _tcscat( szPath, _T("\\Media\\\0") );
    return 0;
}


void CAudioboxDlg::FillFileList(LPTSTR pszRootDir)
{
    UINT attr = 0;

    m_ListFiles.ResetContent();
    ClearFileInfo();
    SetWindowText(APPNAME);

    ::SetCurrentDirectory(pszRootDir);
    FillDirList(pszRootDir);

    // Update the edit box with the current path
    m_EditMediaDir.SetWindowText(pszRootDir);
    ClearPositionLabel();
    
    // Add all of our known supported media types to the file list.
    // Add files of each type in order.
    for (int i=0; i < NUM_MEDIA_TYPES; i++)
    {
        m_ListFiles.Dir(attr, TypeInfo[i].pszType);
    }

    // Update list box title with number of items added
    int nItems  = m_ListFiles.GetCount();
    TCHAR szTitle[64];
    wsprintf(szTitle, TEXT("Media files (%d found)\0"), nItems);
    m_StrFileList.SetWindowText(szTitle);
    
    // Automatically select the first file in the list once
    // the dialog is displayed.
    m_nCurrentFileSelection = -1;     // No selection yet
    PostMessage(WM_FIRSTFILE, 0, 0L);
}


void CAudioboxDlg::FillDirList(LPTSTR pszRootDir)
{
    TCHAR szDir[MAX_PATH];

    m_ListDir.ResetContent();

    _tcsncpy(szDir, pszRootDir, MAX_PATH);
    szDir[MAX_PATH-1] = 0;  // Ensure NULL termination

    if (DlgDirList(szDir, IDC_LIST_DIR, IDC_STATUS_DIRECTORY, 
                   DDL_DIRECTORY | DDL_EXCLUSIVE))
    {
        // Copy the currently active directory for use with favorites
        _tcsncpy(m_szActiveDir, pszRootDir, NUMELMS(m_szActiveDir));
        m_szActiveDir[NUMELMS(m_szActiveDir)-1] = 0;  // Ensure NULL termination

        // Check favorites button
        if (IsFavorite(m_szActiveDir))
            m_ButtonFavorite.SetCheck(BST_CHECKED);
        else
            m_ButtonFavorite.SetCheck(BST_UNCHECKED);
    }
}


void CAudioboxDlg::OnDblclkListDir() 
{
    TCHAR szNewDir[MAX_PATH];

    // Stop any current playback
    OnStop();

    // Free DirectShow interfaces, since we are changing directories.
    // Otherwise, the user could click Play now to play the previous track.
    FreeDirectShow();
    m_ButtonPlay.EnableWindow(FALSE);

    // Read the name of the selected directory
    DlgDirSelectEx(GetSafeHwnd(), szNewDir, MAX_PATH-1, IDC_LIST_DIR);
    szNewDir[MAX_PATH-1] = 0;   // Ensure NULL-termination

    // Let Windows translate relative paths (like "..") into valid
    // directory names
    ::SetCurrentDirectory(szNewDir);
    ::GetCurrentDirectory(MAX_PATH-1, szNewDir);

    // Fill the file list with the contents of the selected directory
    FillFileList(szNewDir);
}


void CAudioboxDlg::OnClose() 
{
    // Release DirectShow interfaces
    StopMedia();
    FreeDirectShow();

    // Release COM
    CoUninitialize();

    CDialog::OnClose();
}


void CAudioboxDlg::OnDestroy() 
{
    FreeDirectShow();   

    CDialog::OnDestroy();
}


void CAudioboxDlg::OnSelectFile() 
{
    HRESULT hr;
    TCHAR szFilename[MAX_PATH]={0};

    // If this is the currently selected file and we're already
    // playing audio, do nothing
    int nItem = m_ListFiles.GetCurSel();
    if ((nItem == m_nCurrentFileSelection) && (g_psCurrent == State_Running))
        return;

    // If there are no files in this directory, make sure we stop
    if (nItem == -1)
    {
        OnStop();
        ClearPositionLabel();
        m_ButtonPlay.EnableWindow(FALSE);
        return;
    }

    // Read file name from list box
    m_ListFiles.GetText(nItem, szFilename);

    // Remember current play state to restart playback
    int nCurrentState = g_psCurrent;

    // First release any existing interfaces
    ResetDirectShow();

    // Load the selected media file
    hr = PrepareMedia(szFilename);
    if (FAILED(hr))
    {
        // Error - disable play button and give feedback
        m_ButtonPlay.EnableWindow(FALSE);
        MessageBeep(0);
        return;
    }
    else
    {
        m_ButtonPlay.EnableWindow(TRUE);
        TCHAR szTitle[MAX_PATH + 10];

        wsprintf(szTitle, TEXT("AudioBox - %s\0"), szFilename);
        SetWindowText(szTitle);
    }

    // Remember the current selection
    m_nCurrentFileSelection = nItem;

    // Display useful information about this file
    DisplayFileInfo(szFilename);
    DisplayFileDuration();

    // Set up the seeking trackbar and read capabilities
    ConfigureSeekbar();

    // Read the current volume slider setting so that the current
    // global volume will be preserved
    m_VolumeSlider.EnableWindow(TRUE);
    HandleVolumeSlider(0);

    // If the user has asked to mute audio then we
    // need to mute this new clip before continuing.
    if (g_bGlobalMute)
        MuteAudio();

    // If we were running when the user changed selection,
    // start running the newly selected clip
    if (nCurrentState == State_Running)
    {
        OnPlay();
    }
    else
    {
        // Cue the first video frame
        OnStop();
    }
}


BOOL CAudioboxDlg::IsWindowsMediaFile(LPTSTR lpszFile)
{
    TCHAR szFilename[MAX_PATH];

    // Copy the file name to a local string and convert to lowercase
    _tcsncpy(szFilename, lpszFile, NUMELMS(szFilename));
    szFilename[MAX_PATH-1] = 0;     // Ensure NULL termination
    _tcslwr(szFilename);

    if (_tcsstr(szFilename, TEXT(".asf")) ||
        _tcsstr(szFilename, TEXT(".wma")) ||
        _tcsstr(szFilename, TEXT(".wmv")))
        return TRUE;
    else
        return FALSE;
}


HRESULT CAudioboxDlg::PrepareMedia(LPTSTR lpszMovie)
{
    USES_CONVERSION;
    HRESULT hr = S_OK;

    if ((!m_pGB) || (!m_pME))
        return E_NOINTERFACE;

    // Is this a Windows Media file (ASF, WMA, WMV)?  If so, use the WM
    // ASF Reader filter, which is faster and much better at seeking than
    // the default ASF Reader filter used by default with RenderFile.
    if (IsWindowsMediaFile(lpszMovie))
    {
        hr = RenderWMFile(T2W(lpszMovie));
        if (FAILED(hr)) {
            RetailOutput(TEXT("*** Failed(%08lx) to Render WM File(%s)!\r\n"),
                     hr, lpszMovie);
            return hr;
        }
    }
    else
    {
        // Allow DirectShow to create the FilterGraph for this media file
        hr = m_pGB->RenderFile(T2W(lpszMovie), NULL);
        if (FAILED(hr)) {
            RetailOutput(TEXT("*** Failed(%08lx) in RenderFile(%s)!\r\n"),
                     hr, lpszMovie);
            return hr;
        }
    }

    // Have the graph signal event via window callbacks
    hr = m_pME->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
    return hr;
}


HRESULT CAudioboxDlg::RenderWMFile(LPCWSTR wFile)
{
    HRESULT hr=S_OK;
    IFileSourceFilter *pFS=NULL;
    IBaseFilter *pReader=NULL;

    // Load the improved ASF reader filter by CLSID
    hr = CreateFilter(CLSID_WMAsfReader, &pReader);
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Failed to create WMAsfWriter filter!  hr=0x%x\n"), hr);
        return hr;
    }

    // Add the ASF reader filter to the graph.  For ASF/WMV/WMA content,
    // this filter is NOT the default and must be added explicitly.
    hr = m_pGB->AddFilter(pReader, L"ASF Reader");
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Failed to add ASF reader filter to graph!  hr=0x%x\n"), hr);
        return hr;
    }

//
// Windows Media 9 Series (code named 'Corona') no longer requires 
// a stub library.  If using WMF9, we don't need to provide a CKeyProvider
// implementation, and we don't need to link with the WMStub.lib library.
//
#ifndef TARGET_WMF9
    // Create the key provider that will be used to unlock the WM SDK
    JIF(AddKeyProvider(m_pGB));
#endif

    // Set its source filename
    JIF(pReader->QueryInterface(IID_IFileSourceFilter, (void **) &pFS));
    JIF(pFS->Load(wFile, NULL));
    pFS->Release();

    // Render the output pins of the ASF reader to build the
    // remainder of the graph automatically
    JIF(RenderOutputPins(m_pGB, pReader));

    // Since the graph is built and the filters are added to the graph,
    // the WM ASF reader interface can be released.
    pReader->Release();

CLEANUP:
    return hr;
}


//
// Windows Media 9 Series (code named 'Corona') no longer requires 
// a stub library.  If using WMF9, we don't need to provide a CKeyProvider
// implementation, and we don't need to link with the WMStub.lib library.
//
#ifndef TARGET_WMF9

HRESULT CAudioboxDlg::AddKeyProvider(IGraphBuilder *pGraph)
{
    HRESULT hr;

    // Instantiate the key provider class, and AddRef it
    // so that COM doesn't try to free our static object.
    prov.AddRef();  // Don't let COM try to free our static object.

    // Give the graph an IObjectWithSite pointer to us for callbacks & QueryService.
    IObjectWithSite* pObjectWithSite = NULL;

    hr = pGraph->QueryInterface(IID_IObjectWithSite, (void**)&pObjectWithSite);
    if (SUCCEEDED(hr))
    {
        // Use the IObjectWithSite pointer to specify our key provider object.
        // The filter graph manager will use this pointer to call
        // QueryService to do the unlocking.
        // If the unlocking succeeds, then we can build our graph.
            
        hr = pObjectWithSite->SetSite((IUnknown *) (IServiceProvider *) &prov);
        pObjectWithSite->Release();
    }

    return hr;
}

#endif


HRESULT CAudioboxDlg::CreateFilter(REFCLSID clsid, IBaseFilter **ppFilter)
{
    HRESULT hr;

    hr = CoCreateInstance(clsid, NULL,
                          CLSCTX_INPROC_SERVER,
                          IID_IBaseFilter,
                          (void **) ppFilter);

    if(FAILED(hr))
    {
        RetailOutput(TEXT("CreateFilter: Failed to create filter!  hr=0x%x\n"), hr);
        *ppFilter = NULL;
        return hr;
    }

    return S_OK;
}


HRESULT CAudioboxDlg::RenderOutputPins(IGraphBuilder *pGB, IBaseFilter *pFilter)
{
    HRESULT         hr = S_OK;
    IEnumPins *     pEnumPin = NULL;
    IPin *          pConnectedPin = NULL, * pPin;
    PIN_DIRECTION   PinDirection;
    ULONG           ulFetched;

    // Enumerate all pins on the filter
    hr = pFilter->EnumPins( &pEnumPin );

    if(SUCCEEDED(hr))
    {
        // Step through every pin, looking for the output pins
        while (S_OK == (hr = pEnumPin->Next( 1L, &pPin, &ulFetched)))
        {
            // Is this pin connected?  We're not interested in connected pins.
            hr = pPin->ConnectedTo(&pConnectedPin);
            if (pConnectedPin)
            {
                pConnectedPin->Release();
                pConnectedPin = NULL;
            }

            // If this pin is not connected, render it.
            if (VFW_E_NOT_CONNECTED == hr)
            {
                hr = pPin->QueryDirection( &PinDirection );
                if ( ( S_OK == hr ) && ( PinDirection == PINDIR_OUTPUT ) )
                {
                    hr = pGB->Render(pPin);
                }
            }
            pPin->Release();

            // If there was an error, stop enumerating
            if (FAILED(hr))                      
                break;
        }
    }

    // Release pin enumerator
    pEnumPin->Release();
    return hr;
}


void CAudioboxDlg::OnPause() 
{  
    if (g_psCurrent == State_Paused)
    {
        RunMedia();
        StartSeekTimer();
        m_ButtonPause.EnableWindow(TRUE);
        m_ButtonPlay.EnableWindow(FALSE);
    }
    else if (g_psCurrent == State_Running)
    {
        StopSeekTimer();
        PauseMedia();
        m_ButtonPause.EnableWindow(FALSE);
        m_ButtonPlay.EnableWindow(TRUE);
    }
}


void CAudioboxDlg::OnPlay() 
{
    if (SUCCEEDED(RunMedia()))
    {
        // Set button states
        m_ButtonPlay.EnableWindow(FALSE);
        m_ButtonStop.EnableWindow(TRUE);
        m_ButtonPause.EnableWindow(TRUE);

        StartSeekTimer();
    }
}


void CAudioboxDlg::OnStop() 
{
    HRESULT hr;

    // Stop playback immediately with IMediaControl::Stop().
    StopSeekTimer();
    StopMedia();

    // Set button states
    m_ButtonPlay.EnableWindow(TRUE);
    m_ButtonStop.EnableWindow(FALSE);
    m_ButtonPause.EnableWindow(FALSE);

    if ((!m_pMC) || (!m_pMS))
        return;

    // Wait for the stop to propagate to all filters
    OAFilterState fs;
    hr = m_pMC->GetState(500, &fs);
    if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed to read graph state!  hr=0x%x\r\n"), hr);
    }

    // Reset to beginning of media clip
    LONGLONG pos=0;
    hr = m_pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                             NULL, AM_SEEKING_NoPositioning);
  
    // StopWhenReady() pauses all filters internally, after which
    // it sets the filters to the stopped state.
    hr = m_pMC->StopWhenReady();
    if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed in StopWhenReady!  hr=0x%x\r\n"), hr);
    }

    // Reset slider bar and position label back to zero
    ReadMediaPosition();
}


HRESULT CAudioboxDlg::InitDirectShow(void)
{
    HRESULT hr = S_OK;

    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, 
                          IID_IGraphBuilder, (void **)&m_pGB);
    if (FAILED(hr))
        return hr;

    if (FAILED(hr = m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC)))
        return hr;

    if (FAILED(hr = m_pGB->QueryInterface(IID_IMediaSeeking, (void **)&m_pMS)))
        return hr;

    if (FAILED(hr = m_pGB->QueryInterface(IID_IMediaEventEx, (void **)&m_pME)))
        return hr;

    if (FAILED(hr = m_pGB->QueryInterface(IID_IBasicAudio,   (void **)&m_pBA)))
        return hr;

    return S_OK;
}


HRESULT CAudioboxDlg::FreeDirectShow(void)
{
    HRESULT hr=S_OK;

    // Disable event callbacks
    if (m_pME)
    {
        hr = m_pME->SetNotifyWindow((OAHWND)NULL, 0, 0);
        SAFE_RELEASE(m_pME);
    }

    StopSeekTimer();
    StopMedia();

    // Remember the current volume slider position so that the
    // same volume level can be applied to the next clip
    HandleVolumeSlider(0);

    SAFE_RELEASE(m_pMC);
    SAFE_RELEASE(m_pMS);
    SAFE_RELEASE(m_pGB);
    SAFE_RELEASE(m_pBA);

    return hr;
}


void CAudioboxDlg::ResetDirectShow(void)
{
    // Destroy the current filter graph its filters.
    FreeDirectShow();

    // Reinitialize graph builder and query for interfaces
    InitDirectShow();
}


LRESULT CAudioboxDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // Field notifications from the DirectShow filter graph manager
    // and those posted by the application
    switch (message)
    {
        case WM_GRAPHNOTIFY:
            HandleGraphEvent();
            break;

        case WM_HSCROLL:
            HandleSeekbar(LOWORD(wParam));
            break;

        case WM_VSCROLL:
            HandleVolumeSlider(LOWORD(wParam));
            break;

        case WM_NEXTFILE:
            PlayNextFile();
            break;

        case WM_PREVIOUSFILE:
            PlayPreviousFile();
            break;

        case WM_PLAYFILE:
            PlaySelectedFile();
            break;

        case WM_RANDOMFILE:
            PlayRandomFile();
            break;

        case WM_FIRSTFILE:
            // Select the first item in the list
            m_ListFiles.SetCurSel(0);
            OnSelectFile();
            break;

        case WM_CLOSE:
            FreeDirectShow();
            break;

        // Handle menu commands
        case WM_COMMAND:
            switch (wParam)
            {
                case IDM_PLAY:
                    OnPlay();
                    break;
                case IDM_PAUSE:
                    OnPause();
                    break;
                case IDM_STOP:
                    OnStop();
                    break;

                // Provide a means to set the current directory to
                // popular Windows folders
                case IDM_MYMUSIC:
                    InitCustomDirectory(CSIDL_MYMUSIC);
                    break;
                case IDM_MYDOCS:
                    InitCustomDirectory(CSIDL_PERSONAL);
                    break;
                case IDM_MYDESKTOP:
                    InitCustomDirectory(CSIDL_DESKTOPDIRECTORY);
                    break;
                case IDM_SDK_MEDIA:
                    {
                        TCHAR szDir[MAX_PATH];
                        if (!GetDXMediaPath(szDir))
                            FillFileList(szDir);
                        else
                            MessageBox(TEXT("Couldn't find DirectX SDK Media path!"));
                    }
                    break;

                case IDM_WINDOWS_MEDIA:
                    {
                        TCHAR szDir[MAX_PATH];
                        if (GetWindowsDirectory(szDir, MAX_PATH))
                        {
                            _tcscat(szDir, _T("\\Media\\\0") );
                            FillFileList(szDir);
                        }
                        else
                            MessageBox(TEXT("Couldn't find Windows Media path!"));
                    }
                    break;

                case IDM_DRIVE_ROOT:
                    FillFileList(TEXT("c:\\\0"));
                    break;

                case IDM_EXIT:
                    PostMessage(WM_CLOSE, 0, 0);
                    break;

                case IDM_ABOUT:
                    CAboutDlg dlgAbout;
                    dlgAbout.DoModal();
                    break;
            }
            break;
    }

    return CDialog::WindowProc(message, wParam, lParam);
}


HRESULT CAudioboxDlg::HandleGraphEvent(void)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

    // Since we may have a scenario where we're shutting down the application,
    // but events are still being generated, make sure that the event
    // interface is still valid before using it.  It's possible that
    // the interface could be freed during shutdown but later referenced in
    // this callback before the app completely exits.
    if (!m_pME)
        return S_OK;
    
    while(SUCCEEDED(m_pME->GetEvent(&evCode, (LONG_PTR *) &evParam1, 
                    (LONG_PTR *) &evParam2, 0)))
    {
        // Spin through the events
        if(EC_COMPLETE == evCode)
        {
            // If looping, reset to beginning and continue playing
            if (g_bLooping)
            {
                if (m_pMS)
                {
                    LONGLONG pos=0;

                    // Reset to first frame of movie
                    hr = m_pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                           NULL, AM_SEEKING_NoPositioning);
                    if (FAILED(hr))
                    {
                        // Some custom filters (like the Windows CE MIDI filter) 
                        // may not implement seeking interfaces (IMediaSeeking)
                        // to allow seeking to the start.  In that case, just stop 
                        // and restart for the same effect.  This should not be
                        // necessary in most cases.
                        StopMedia();
                        RunMedia();
                    }
                }
            }
            else if (g_bRandomize)
            {
                // Tell the app to select the next file in the list
                PostMessage(WM_RANDOMFILE, 0, 0);
            }
            else
            {
                // Tell the app to select the next file in the list
                PostMessage(WM_NEXTFILE, 0, 0);
            }
        }

        // Free memory associated with this event
        hr = m_pME->FreeEventParams(evCode, evParam1, evParam2);
    }

    return hr;
}


void CAudioboxDlg::OnCheckMute() 
{
    // Remember global mute status for next file.  When you destroy a
    // filtergraph, you lose all of its audio settings.  Therefore, when
    // we create the next graph, we will mute the audio before running
    // the graph if this global variable is set.
    g_bGlobalMute ^= 1; 

    if (g_bGlobalMute)
    {
        MuteAudio();
        m_VolumeSlider.EnableWindow(FALSE);
    }
    else
    {
        ResumeAudio();
        if (m_pBA)
            m_VolumeSlider.EnableWindow(TRUE);
    }
}

void CAudioboxDlg::OnCheckLoop() 
{
    g_bLooping ^= 1;
}

void CAudioboxDlg::OnCheckRandomize() 
{
    g_bRandomize ^= 1;
}


void CAudioboxDlg::OnButtonSetMediadir() 
{
    TCHAR szEditPath[MAX_PATH];
    DWORD dwAttr;

    // Make sure that we're not playing media
    OnStop();

    // Free DirectShow interfaces, since we are changing directories.
    // Otherwise, the user could click Play now to play the previous track.
    FreeDirectShow();
    m_ButtonPlay.EnableWindow(FALSE);

    // Read the string in the media directory edit box.
    m_EditMediaDir.GetWindowText(szEditPath, MAX_PATH);

    // Is this a valid directory name?
    dwAttr = GetFileAttributes(szEditPath);
    if ((dwAttr == (DWORD) -1) || (! (dwAttr & FILE_ATTRIBUTE_DIRECTORY)))
    {
        MessageBox(TEXT("Please enter a valid directory name."), TEXT("Media error"));
        return;
    }

    // Save current directory name.  Append the trailing '\' to match
    // the string created by GetDXSDKMediaPath() (if not present)
    int nLength = _tcslen(szEditPath);
    if (szEditPath[nLength - 1] != TEXT('\\'))
        wsprintf(m_szCurrentDir, TEXT("%s\\\0"), szEditPath);

    // Propagate the files list and select the first item
    FillFileList(szEditPath);
}


void CAudioboxDlg::PlaySelectedFile() 
{
    OnPlay();
}


void CAudioboxDlg::OnDeltaposSpinFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

    if (pNMUpDown->iDelta > 0)
        PostMessage(WM_NEXTFILE, 0, 0L);
    else
        PostMessage(WM_PREVIOUSFILE, 0, 0L);

    *pResult = 0;
}


void CAudioboxDlg::PlayNextFile(void)
{
    int nItems  = m_ListFiles.GetCount();

    // Return if the list is empty
    if (!nItems)
        return;
        
    int nCurSel = m_ListFiles.GetCurSel();
    int nNewSel = (nCurSel + 1) % nItems;

    // Select the next item in the list, wrapping to top if needed
    m_ListFiles.SetCurSel(nNewSel);
    OnSelectFile();

    // Set the keyboard focus on the Stop button so that tabbed
    // navigation will still work
    m_ButtonStop.SetFocus();
}


void CAudioboxDlg::PlayPreviousFile(void)
{
    int nItems  = m_ListFiles.GetCount();

    // Return if the list is empty
    if (!nItems)
        return;
        
    int nCurSel = m_ListFiles.GetCurSel();
    int nNewSel = nCurSel - 1;

    // If moved off top of list, select last item in list
    if (nNewSel < 0)
        nNewSel = nItems - 1;

    // Select the next item in the list, wrapping to top if needed
    m_ListFiles.SetCurSel(nNewSel);
    OnSelectFile();

    // Set the keyboard focus on the Stop button so that tabbed
    // navigation will still work
    m_ButtonStop.SetFocus();
}


void CAudioboxDlg::PlayRandomFile(void)
{
    int nItems  = m_ListFiles.GetCount();

    // Return if the list is empty
    if (!nItems)
        return;
        
    int nCurSel = m_ListFiles.GetCurSel();
    int nNewSel = (int)(rand() % nItems);

    // Don't play the same file again
    if (nNewSel == nCurSel)
        PlayNextFile();
    else
    {
        // Select the random item, wrapping to top if needed
        m_ListFiles.SetCurSel(nNewSel);
        OnSelectFile();

        // Set the keyboard focus on the Stop button so that tabbed
        // navigation will still work
        m_ButtonStop.SetFocus();
    }
}


BOOL CAudioboxDlg::DisplayFileInfo(LPTSTR szFile)
{
    HANDLE hFile;
    LONGLONG llSize=0;
    DWORD dwSizeLow=0, dwSizeHigh=0;
    TCHAR szScrap[64];

    // Open the specified file to read size and date information
    hFile = CreateFile(szFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,
                       (DWORD) 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        RetailOutput(TEXT("*** Failed(0x%x) to open file (to read size)!\r\n"),
                     GetLastError());
        return FALSE;
    }

    dwSizeLow = GetFileSize(hFile, &dwSizeHigh);
    if ((dwSizeLow == 0xFFFFFFFF) && (GetLastError() != NO_ERROR))
    {
        RetailOutput(TEXT("*** Error(0x%x) reading file size!\r\n"),
                     GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }

    // Large files will also use the upper DWORD to report size.
    // Add them together for the true size if necessary.
    if (dwSizeHigh)
        llSize = (dwSizeHigh << 16) + dwSizeLow;
    else
        llSize = dwSizeLow;

    // Read date information
    BY_HANDLE_FILE_INFORMATION fi;
    if (GetFileInformationByHandle(hFile, &fi))
    {
        CTime time(fi.ftLastWriteTime);

        wsprintf(szScrap, TEXT("File date: %02d/%02d/%d\0"), 
                 time.GetMonth(), time.GetDay(), time.GetYear());
        m_StrFileDate.SetWindowText(szScrap);
    }

    CloseHandle(hFile);

    // Update size/date windows
    wsprintf(szScrap, TEXT("Size: %d bytes\0"), dwSizeLow);
    m_StrFileSize.SetWindowText(szScrap);

    return TRUE;
}


HRESULT CAudioboxDlg::DisplayFileDuration(void)
{
    HRESULT hr;

    if (!m_pMS)
        return E_NOINTERFACE;

    // Initialize the display in case we can't read the duration
    m_StrDuration.SetWindowText(TEXT("<00:00.000>"));

    // Is media time supported for this file?
    if (S_OK != m_pMS->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME))
        return E_NOINTERFACE;

    // Read the time format to restore later
    GUID guidOriginalFormat;
    hr = m_pMS->GetTimeFormat(&guidOriginalFormat);
    if (FAILED(hr))
        return hr;

    // Ensure media time format for easy display
    hr = m_pMS->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
    if (FAILED(hr))
        return hr;

    // Read the file's duration
    LONGLONG llDuration=0;
    hr = m_pMS->GetDuration(&llDuration);
    if (FAILED(hr))
        return hr;

    // Return to the original format
    if (guidOriginalFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = m_pMS->SetTimeFormat(&guidOriginalFormat);
        if (FAILED(hr))
            return hr;
    }

    // Convert the LONGLONG duration into human-readable format
    unsigned long nTotalMS = (unsigned long) ((float) llDuration / 10000.0); // 100ns -> ms
    int nSeconds = nTotalMS / (int) 1000;
    int nMinutes = nSeconds / (int) 60;
    nSeconds %= 60;

    // Update the display
    TCHAR szDuration[64];
    wsprintf(szDuration, _T("Duration: %d min %2d sec\0"), nMinutes, nSeconds);
    m_StrDuration.SetWindowText(szDuration);

    return hr;
}


void CAudioboxDlg::ConfigureSeekbar()
{
    HRESULT hr;

    // Reset tracker/position label and media duration
    m_Seekbar.SetPos(0);
    g_rtTotalTime=0;

    // Disable the seekbar by default, in case there is no valid media file
    m_Seekbar.EnableWindow(FALSE);

    if (!m_pMS)
        return;

    // If we can read the file's duration, enable the seek bar
    hr = m_pMS->GetDuration(&g_rtTotalTime);
    if (SUCCEEDED(hr))
        m_Seekbar.EnableWindow(TRUE);
}


void CAudioboxDlg::StartSeekTimer() 
{
    // Cancel any pending timer event
    StopSeekTimer();

    // Create a new timer
    g_wTimerID = SetTimer(TIMERID, TICKLEN, NULL);
}


void CAudioboxDlg::StopSeekTimer() 
{
    // Cancel the timer
    if(g_wTimerID)        
    {                
        KillTimer(g_wTimerID);
        g_wTimerID = 0;
    }
}


void CAudioboxDlg::OnTimer(UINT nIDEvent) 
{
    ReadMediaPosition();

    CDialog::OnTimer(nIDEvent);
}


void CAudioboxDlg::ReadMediaPosition()
{
    HRESULT hr;
    REFERENCE_TIME rtNow;

    if (!m_pMS)
        return;
    
    // Read the current stream position
    hr = m_pMS->GetCurrentPosition(&rtNow);
    if (FAILED(hr))
        return;

    // Convert position into a percentage value and update slider position
    if (g_rtTotalTime != 0)
    {
        long lTick = (long)((rtNow * 100.0) / g_rtTotalTime);
        m_Seekbar.SetPos(lTick);
    }
    else
        m_Seekbar.SetPos(0);
    
    // Update the 'current position' string on the main dialog
    UpdatePosition(rtNow);
}


void CAudioboxDlg::UpdatePosition(REFERENCE_TIME rtNow) 
{
    HRESULT hr;

    if (!m_pMS)
        return;

    // If no reference time was passed in, read the current position
    if (rtNow == 0)
    {
        // Read the current stream position
        hr = m_pMS->GetCurrentPosition(&rtNow);
        if (FAILED(hr))
            return;
    }

    // Convert the LONGLONG duration into human-readable format
    unsigned long nTotalMS = (unsigned long) ((float) rtNow / 10000.0); // 100ns -> ms
    int nSeconds = nTotalMS / (int) 1000;
    int nMinutes = nSeconds / (int) 60;
    nSeconds %= 60;

    // Update the display
    TCHAR szPosition[64], szCurrentString[64];
    wsprintf(szPosition, _T("Position: %02dm:%02ds\0"), nMinutes, nSeconds);

    // Read current string and compare to the new string.  To prevent flicker,
    // don't update this label unless the string has changed.
    m_StrPosition.GetWindowText(szCurrentString, 24);

    if (_tcscmp(szCurrentString, szPosition))
        m_StrPosition.SetWindowText(szPosition);
}


void CAudioboxDlg::ClearPositionLabel() 
{
    // Clear the current position in case there are no media files
    m_StrPosition.SetWindowText(TEXT("\0"));
}


void CAudioboxDlg::HandleSeekbar(WPARAM wReq)
{
    HRESULT hr;
    static OAFilterState state;
    static BOOL bStartOfScroll = TRUE;

    if ((!m_pMC) || (!m_pMS))
        return;

    // If the file is not seekable, the trackbar is disabled. 
    DWORD dwPosition = m_Seekbar.GetPos();

    // Pause when the scroll action begins.
    if (bStartOfScroll) 
    {       
        hr = m_pMC->GetState(10, &state);
        bStartOfScroll = FALSE;
        hr = m_pMC->Pause();
    }
    
    // Update the position continuously.
    REFERENCE_TIME rtNew = (g_rtTotalTime * dwPosition) / 100;

    hr = m_pMS->SetPositions(&rtNew, AM_SEEKING_AbsolutePositioning,
                             NULL,   AM_SEEKING_NoPositioning);

    // Restore the state at the end.
    if (wReq == TB_ENDTRACK)
    {
        if (state == State_Stopped)
            hr = m_pMC->Stop();
        else if (state == State_Running) 
            hr = m_pMC->Run();

        bStartOfScroll = TRUE;
    }

    // Update the 'current position' string on the main dialog.
    UpdatePosition(rtNew);
}


void CAudioboxDlg::HandleVolumeSlider(WPARAM wReq)
{
    HRESULT hr=S_OK;
    long lVolume;

    // Disregard ENDSCROLL messages, which are redundant
    if ((!m_pBA) || (wReq == SB_ENDSCROLL))
        return;

    // Since the IBasicAudio interface adjusts volume on a logarithmic
    // scale from -10000 to 0, volumes below -4000 sound like silence.
    // Therefore, the slider covers a smaller range.
    int nPosition = m_VolumeSlider.GetPos();

    // Since slider goes from MINIMUM_VOLUME to 0, use the negative value
    lVolume = -1 * nPosition;

    // Save current volume to global variable for use with Mute/Resume audio
    m_lCurrentVolume = lVolume;

    // Set new volume
    hr = m_pBA->put_Volume(lVolume);
}


HRESULT CAudioboxDlg::RunMedia()
{
    HRESULT hr=S_OK;

    if (!m_pMC)
        return E_NOINTERFACE;

    // Start playback
    hr = m_pMC->Run();
    if (FAILED(hr)) {
        RetailOutput(TEXT("\r\n*** Failed(%08lx) in Run()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent = State_Running;
    return hr;
}


HRESULT CAudioboxDlg::StopMedia()
{
    HRESULT hr=S_OK;

    if (!m_pMC)
        return E_NOINTERFACE;

    // If we're already stopped, don't check again
    if (g_psCurrent == State_Stopped)
        return hr;

    // Stop playback
    hr = m_pMC->Stop();
    if (FAILED(hr)) {
        RetailOutput(TEXT("\r\n*** Failed(%08lx) in Stop()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent = State_Stopped;
    return hr;
}


HRESULT CAudioboxDlg::PauseMedia(void)
{
    HRESULT hr=S_OK;

    if (!m_pMC)
        return E_NOINTERFACE;

    // Play/pause
    if(g_psCurrent != State_Running)
        return S_OK;

    hr = m_pMC->Pause();
    if (FAILED(hr)) {
        RetailOutput(TEXT("\r\n*** Failed(%08lx) in Pause()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent = State_Paused;
    return hr;
}


HRESULT CAudioboxDlg::MuteAudio(void)
{
    HRESULT hr=S_OK;
    long lVolume;

    if (!m_pBA)
        return E_NOINTERFACE;

    // Read current volume
    hr = m_pBA->get_Volume(&lVolume);
    if (FAILED(hr))
    {
        return hr;
    }

    // Save the current volume level for resuming later
    m_lCurrentVolume = lVolume;

    // Set new volume to MUTE
    lVolume = VOLUME_SILENCE;
    hr = m_pBA->put_Volume(lVolume);

    return hr;
}


HRESULT CAudioboxDlg::ResumeAudio(void)
{
    HRESULT hr=S_OK;

    if (!m_pBA)
        return E_NOINTERFACE;

    // Set new volume to previously saved value
    hr = m_pBA->put_Volume(m_lCurrentVolume);

    return hr;
}


void CAudioboxDlg::RetailOutput(TCHAR *szFormat, ...)
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

    OutputDebugString(szBuffer);
}


BOOL CAudioboxDlg::InitCustomDirectory(int nCustomDir)
{
    TCHAR szFolder[MAX_PATH];

    // Get the path of the system folder (My Music, My Documents, etc.)
    if (SHGetSpecialFolderPath(GetSafeHwnd(), szFolder, nCustomDir, 0))
    {
        // Stop current playback
        OnStop();
        FillFileList(szFolder);

        // Save the current directory for later use
        _tcsncpy(m_szCurrentDir, szFolder, NUMELMS(m_szCurrentDir));
        m_szCurrentDir[NUMELMS(m_szCurrentDir) - 1] = 0;  // Ensure NULL termination
        return TRUE;
    }
    else
        return FALSE;   // Failed to set custom folder
}


void CAudioboxDlg::ClearFileInfo(void)
{
    m_StrPosition.SetWindowText(TEXT("\0"));
    m_StrDuration.SetWindowText(TEXT("\0"));
    m_StrFileDate.SetWindowText(TEXT("\0"));
    m_StrFileSize.SetWindowText(TEXT("\0"));

    // Disable volume slider
    m_VolumeSlider.EnableWindow(FALSE);
}


HRESULT CAudioboxDlg::ModifyFavorite(const TCHAR *szMediaDirectory, DWORD dwEnable)
{
    HKEY hKey;

    if (!szMediaDirectory || szMediaDirectory[0] == 0)
        return E_INVALIDARG;

    // Open or create the AudioBox favorites registry key
    LONG lResult = RegCreateKeyEx(HKEY_CURRENT_USER, g_szRegFav, 0,
                                  0,                      // class string
                                  0,                      // options
                                  KEY_READ | KEY_WRITE,
                                  0,                      // security
                                  &hKey,
                                  0);                     // disposition

    if(lResult == ERROR_SUCCESS)
    {
        if (dwEnable == TRUE)
        {
            // Add the media directory key to the favorites list.  Set the key's value
            // to TRUE or FALSE, which will determine whether the media directory 
            // will be displayed on the Favorites menu.
            lResult = RegSetValueEx(hKey, szMediaDirectory, 0, REG_DWORD,
                (BYTE *) &dwEnable, // TRUE to enable display on menu
                sizeof(DWORD));

            if (lResult != ERROR_SUCCESS)
                MessageBox(TEXT("Failed to add favorite!"), TEXT("Add Favorite"));
        }
        else
        {
            // Delete the favorite from the registry
            lResult = RegDeleteValue(hKey, szMediaDirectory);
            if (lResult != ERROR_SUCCESS)
                MessageBox(TEXT("Failed to delete favorite!"), TEXT("Delete Favorite"));
        }

        RegCloseKey(hKey);
        return S_OK;
    }
    else
    {
        MessageBox(TEXT("There was an error modifying this folder in your favorites list.\0"),
                   TEXT("Modify Favorite\0"), MB_OK | MB_ICONEXCLAMATION);
        return E_FAIL;
    }
}


BOOL CAudioboxDlg::IsFavorite(const TCHAR *szMediaDirectory)
{
    HKEY hKey=0;
    DWORD dwValue=0, dwSize=sizeof(DWORD), dwType=REG_DWORD;

    if (!szMediaDirectory || szMediaDirectory[0] == 0)
        return FALSE;

    // Open or create the AudioBox favorites registry key
    LONG lResult = RegCreateKeyEx(
                                HKEY_CURRENT_USER,
                                g_szRegFav,
                                0,                      // reserved
                                0,                      // class string
                                0,                      // options
                                KEY_READ,
                                0,                      // security
                                &hKey,
                                0);                     // disposition

    if(lResult == ERROR_SUCCESS)
    {
        // Read whether this value is enabled
        lResult = RegQueryValueEx(
                                hKey,
                                szMediaDirectory,
                                0,                  // reserved
                                &dwType,
                                (BYTE *) &dwValue,  // TRUE or FALSE
                                &dwSize);

        RegCloseKey(hKey);

        if ((lResult == ERROR_SUCCESS) && dwValue == TRUE)
            return TRUE;
    }

    return FALSE;
}


void CAudioboxDlg::OnClearFavorites()
{
    HKEY hKey;

    // By user request, verify that the user really intended to click on
    // the 'Clear Favorites' menu item
    int nDecision = MessageBox(TEXT("Are you sure that you want to delete all favorites?\0"),
                               TEXT("Clear Favorites\0"), MB_YESNO);
    if (nDecision == IDNO)
        return;

    // Open the main AudioBox key
    LONG lResult = RegOpenKeyEx(HKEY_CURRENT_USER, g_szRegAudioBox, 0,
                                KEY_ALL_ACCESS, &hKey);

    // Delete the Favorites subkey (which will delete all of the favorites)
    if(lResult == ERROR_SUCCESS)
    {
        lResult = RegDeleteKey(hKey, TEXT("Favorites\0"));
        RegCloseKey(hKey);

        // Clear the "Folder Favorite" check button
        m_ButtonFavorite.SetCheck(BST_UNCHECKED);
    }

    // Catch failure in RegOpenKey and RegDeleteKey calls
    if (lResult != ERROR_SUCCESS)
    {
        MessageBox(TEXT("There was an error deleting your favorites.\0"),
                   TEXT("Clear Favorites\0"), MB_OK | MB_ICONEXCLAMATION);
    }
}


void CAudioboxDlg::OnAddFavorite() 
{
    // Add this favorite to the registry and menu.
    // Also check the box indicating that the current folder is a Favorite.
    if (SUCCEEDED(ModifyFavorite(m_szActiveDir, TRUE)))
        m_ButtonFavorite.SetCheck(BST_CHECKED);
}

void CAudioboxDlg::OnCheckFavorite() 
{
    DWORD dwIsFavorite=0;

    // Is this a favorite folder?
    dwIsFavorite = m_ButtonFavorite.GetCheck();

    // Enable or disable this folder as a favorite
    ModifyFavorite(m_szActiveDir, dwIsFavorite);
}

void CAudioboxDlg::OnSelectFavorite(UINT nID)
{
    UINT nFavoriteNumber = nID - ID_FAVORITE_BASE;

    // Make sure that playback is stopped
    OnStop();

    // Get the full folder path saved in the g_szFavorites and
    // use it to set the current media diretory.
    FillFileList(g_szFavorites[nFavoriteNumber]);
}


// Comparison callback used by qsort()
int CompareStrings( const void *str1, const void *str2 )
{
   // Compare all of both strings
    return _tcsicmp( (TCHAR *) str1, (TCHAR *) str2);
}


void CAudioboxDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
    CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
    
    // If selecting the Favorites menu, rebuild the menu from scratch,
    // since the list of favorites could be adjusted at any time.
    if (nIndex == emFavorites && !bSysMenu)
    {
        HKEY hk;
        int nItems = pPopupMenu->GetMenuItemCount();

        // Delete all menu items at position 4 and above
        // Pos 0: "Add to Favorites"
        // Pos 1: Separator
        // Pos 2: "Clear Favorites"
        // Pos 3: Separator
        for (int i=4; i < nItems; i++)
            pPopupMenu->RemoveMenu(4, MF_BYPOSITION);

        // Now we have a clear menu.  Open the Favorites registry key.
        LONG lResult = RegOpenKeyEx(HKEY_CURRENT_USER, g_szRegFav, 0, KEY_READ, &hk);

        if(lResult == ERROR_SUCCESS)
        {
            // Enumerate all of the items in the Favorites key. 
            // For each item, add it to the menu and save the full folder path
            DWORD dwIndex=0, dwType=REG_DWORD;
            const int nValNameSize=260, nValDataSize=sizeof(DWORD);
            TCHAR szValueName[nValNameSize];
            DWORD dwValueData;
            DWORD dwValueNameSize=nValNameSize, dwValueDataSize=nValDataSize;

            while (ERROR_NO_MORE_ITEMS != 
                   RegEnumValue(hk, dwIndex, 
                                szValueName, &dwValueNameSize, NULL, 
                                &dwType, (BYTE *)&dwValueData, &dwValueDataSize))
            {
                // Save the full folder name in a global structure.  The folder name 
                // will be retrieved when the user selects a favorite.
                _tcsncpy(g_szFavorites[dwIndex], szValueName, NUMELMS(g_szFavorites[dwIndex]));
                g_szFavorites[dwIndex][MAX_PATH-1] = 0;     // Null-terminate

                // Reset for next pass
                dwValueNameSize=nValNameSize;
                dwValueDataSize=nValDataSize;

                // Only support a limited number of favorites
                dwIndex++;
                if (dwIndex >= MAX_FAVORITES)
                    break;
            }

            RegCloseKey(hk);

            // Sort the favorites folders alphabetically
            qsort(g_szFavorites, dwIndex, MAX_PATH * sizeof(TCHAR), CompareStrings);
            
            // Add the sorted array of folders to the Favorites menu           
            for (DWORD i=0; i < dwIndex; i++)
            {
                // Get the folder name without the full path
                TCHAR szShortName[MAX_PATH];                  
                GetShortName(g_szFavorites[i], szShortName);                    

                // Add the folder name to the favorites menu
                pPopupMenu->AppendMenu(MF_STRING, ID_FAVORITE_BASE + i, szShortName);
            }
        }
    }
}


void CAudioboxDlg::GetShortName(TCHAR *pszFullPath, TCHAR *pszFolder)
{
    int nLength;
    TCHAR szPath[MAX_PATH]={0};
    BOOL bSetFilename=FALSE;

    // Strip full path and return just the folder's short path
    _tcsncpy(szPath, pszFullPath, MAX_PATH);
    nLength = (int) _tcslen(szPath);

    // Is the last character a backslash?  (eg: c:\)
    // If so, then delete the trailing backslash
    if (szPath[nLength-1] == TEXT('\\'))
    {
        szPath[nLength-1] = 0;
        nLength--;
    }

    for (int i=nLength-1; i>=0; i--)
    {
        if ((szPath[i] == TEXT('\\')) || (szPath[i] == TEXT('/')))
        {
            szPath[i] = 0;
            lstrcpyn(pszFolder, &szPath[i+1], MAX_PATH);
            bSetFilename = TRUE;
            break;
        }
    }

    // If there was no full path given (just a folder name), then
    // just copy the full path to the target folder name.
    if (!bSetFilename)
        _tcsncpy(pszFolder, pszFullPath, MAX_PATH);
}


