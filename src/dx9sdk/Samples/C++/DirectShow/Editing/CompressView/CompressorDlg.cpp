//------------------------------------------------------------------------------
// File: CompressorDlg.cpp
//
// Desc: DirectShow sample code - CompressView main dialog
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

//
// This sample app demonstrates how to recompress a video/audio
// source file into another file with a different compression type.
// You can convert MPG, QT, AVI, or any video file that DirectShow
// can host into an AVI file, as long as you have the appropriate
// compressors and decompressors. 
//
// Note, however, that some compressors cannot be used because they 
// have Digital Rights Management (DRM) built into them or because the 
// compressors are not functioning as expected by this program.
//

#include "stdafx.h"
#include "qedit.h"          // For ISampleGrabber
#include "Compressor.h"
#include "CompressorDlg.h"
#include "dshowutil.h"

//
// Constants
//
#define ASSUMED_LENGTH  20.0    /* Default media length if unknown */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CCompressorDlg dialog

CCompressorDlg::CCompressorDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCompressorDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CCompressorDlg)
    m_bWantAudio = FALSE;
    m_szInputFile = _T("");
    m_szOutputFile = _T("");
    m_sProgressText = _T("");
    m_bSuppressWarning = FALSE;
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompressorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCompressorDlg)
    DDX_Control(pDX, IDC_BROWSE, m_BtnBrowse);
    DDX_Control(pDX, IDC_BUTTON_STOP, m_BtnStop);
    DDX_Control(pDX, IDC_SCREEN, m_Screen);
    DDX_Control(pDX, IDC_BUTTON_PLAYOUTPUT, m_BtnPlayOutput);
    DDX_Control(pDX, IDC_BUTTON_PLAYINPUT, m_BtnPlayInput);
    DDX_Control(pDX, IDC_START, m_BtnStart);
    DDX_Control(pDX, IDC_COMPRESSOR, m_CompressorList);
    DDX_Control(pDX, IDC_PROGRESS, m_Progress);
    DDX_Check(pDX, IDC_AUDIO, m_bWantAudio);
    DDX_Text(pDX, IDC_FILENAME, m_szInputFile);
    DDX_Text(pDX, IDC_OUTFILE, m_szOutputFile);
    DDX_Text(pDX, IDC_PROGRESS_TEXT, m_sProgressText);
    DDX_Check(pDX, IDC_SUPPRESS_SIZE_ERROR, m_bSuppressWarning);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCompressorDlg, CDialog)
    //{{AFX_MSG_MAP(CCompressorDlg)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_SYSCOMMAND()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
    ON_BN_CLICKED(IDC_START, OnStart)
    ON_CBN_SELCHANGE(IDC_COMPRESSOR, OnSelchangeCompressor)
    ON_BN_CLICKED(IDC_BUTTON_PLAYINPUT, OnButtonPlayInput)
    ON_BN_CLICKED(IDC_BUTTON_PLAYOUTPUT, OnButtonPlayOutput)
    ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
    ON_WM_CLOSE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCompressorDlg message handlers

void CCompressorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCompressorDlg::OnPaint() 
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
HCURSOR CCompressorDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}


BOOL CCompressorDlg::OnInitDialog()
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
    // when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);           // Set small icon
    
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    // fill our list box with a list of available DirectShow compressors
    //
    AddCompressorsToList();

    // find the last compressor selected by the user
    //
    TCHAR szNum[256];
    GetPrivateProfileString(TEXT("DexCompress"), TEXT("CompressorNumber"), TEXT("1"), 
                              szNum, 256, TEXT("DexCompress.ini"));
    szNum[255] = 0; // ensure this comes in null terminated

    // set the compressor to the one used last time
    //
    int n = _ttoi(szNum);
    m_CompressorList.SetCurSel(n);

    // store a pointer to the compressor that was selected
    //
    m_pCompressor.Release();
    GetCompressor(n, &m_pCompressor);

    // initialize user interface elements
    SetButtonStates(FALSE);

    // Since we're embedding video in a child window of a dialog,
    // we must set the WS_CLIPCHILDREN style to prevent the bounding
    // rectangle from drawing over our video frames.
    //
    // Neglecting to set this style can lead to situations when the video
    // is erased and replaced with the default color of the bounding rectangle.
    m_Screen.ModifyStyle(0, WS_CLIPCHILDREN);

    // ensure that our playback filter graph pointer is cleared
    m_pPlaybackGraph = NULL;
    m_bCloseRequested = m_bCompressing = FALSE;

    return TRUE;  // return TRUE  unless you set the focus to a control
}


void CCompressorDlg::OnBrowse() 
{
    CFileDialog cfd(TRUE, NULL, NULL, 
                     OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
                     TEXT("Video Files (.mpg;.mpeg;.avi;.qt;.mov)|*.mpg;*.mpeg;*.avi;*.qt;*.mov\0\0"), 
                     NULL);
    
    // prompt the user for an input file
    cfd.m_ofn.lpstrTitle = TEXT("Select an input file...");
    if (IDCANCEL == (int) cfd.DoModal())
        return;

    if(cfd.GetPathName().GetLength() < 5)
    {
        AfxMessageBox(TEXT("The filename is too short"));
        return;
    }

    // read current dialog data
    UpdateData(TRUE);

    // destroy any old playback filtergraph
    ResetPlayback();

    // set the internal filename
    m_szInputFile = cfd.GetPathName();

    // create an output filename based on the input filename (fileX.avi)
    m_szOutputFile = m_szInputFile.Left(m_szInputFile.GetLength() - 4) + 
                                         CString("X.avi\0");

    // create a media detector to see if the input media file has an audio stream
    CComPtr< IMediaDet > pDet;

    pDet.CoCreateInstance(CLSID_MediaDet);
    if(!pDet)
    {
        AfxMessageBox(TEXT("Could not create CLSID_MediaDet"));
    }
    else
    {
        USES_CONVERSION;
        HRESULT hr;
        bool FoundAudio = false;

        // For UNICODE support, copy the CString into a TCHAR array
        TCHAR szFilename[MAX_PATH];
        _tcscpy(szFilename, (LPCTSTR) m_szInputFile);

        hr = pDet->put_Filename(T2W(szFilename));
        if (FAILED(hr))
        {
            AfxMessageBox(TEXT("Failed to put filename"));
            return;
        }

        long StreamCount = 0;
        hr = pDet->get_OutputStreams(&StreamCount);
        if (FAILED(hr))
        {
            AfxMessageBox(TEXT("Failed to get output streams"));
            return;
        }

        for(int i = 0; i < StreamCount; i++)
        {
            hr = pDet->put_CurrentStream(i);
            if (FAILED(hr))
            {
                AfxMessageBox(TEXT("Failed to put current stream"));
                return;
            }

            GUID StreamType;

            hr = pDet->get_StreamType(&StreamType);
            if (FAILED(hr))
            {
                AfxMessageBox(TEXT("Failed to get stream type"));
                return;
            }

            if(StreamType == MEDIATYPE_Audio)
            {
                FoundAudio = true;
            }
        }

        if(FoundAudio)
            m_bWantAudio = true;
        else
            m_bWantAudio = false;

        SetButtonStates(TRUE);
    }

    // make the dialog reflect the variable
    UpdateData(FALSE);
}


void CCompressorDlg::OnSelchangeCompressor() 
{
    // read current dialog data
    UpdateData(TRUE);

    // find the compressor name and store it off so we can default to it later
    CString str;
    str.Format(TEXT("%ld\0"), m_CompressorList.GetCurSel());

    WritePrivateProfileString(TEXT("DexCompress"), TEXT("CompressorNumber"), 
                                str.GetBuffer(256), TEXT("DexCompress.ini"));

    // get a pointer to the compressor so we can put it in the graph
    m_pCompressor.Release();
    GetCompressor(m_CompressorList.GetCurSel(), &m_pCompressor);
}


/////////////////////////////////////////////////////////////////////////////
// This routine enumerates directshow compressors and adds them to a 
// UI drop down list box
/////////////////////////////////////////////////////////////////////////////

HRESULT CCompressorDlg::AddCompressorsToList()
{
    HRESULT hr = 0;

    // reset the list box contents
    m_CompressorList.ResetContent();

    // create an enumerator object
    CComPtr< ICreateDevEnum > pCreateDevEnum;
    hr = CoCreateInstance(
                        CLSID_SystemDeviceEnum, 
                        NULL, 
                        CLSCTX_INPROC_SERVER,
                        IID_ICreateDevEnum, 
                        (void**) &pCreateDevEnum);

    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Failed to create system enumerator"));
        return hr;
    }

    // tell the enumerator to enumerate Video Compressors
    CComPtr< IEnumMoniker > pEm;
    hr = pCreateDevEnum->CreateClassEnumerator(
                        CLSID_VideoCompressorCategory,
                        &pEm, 
                        0);

    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Failed to create class enumerator"));
        return hr;
    }

    // start enumerating at the beginning
    pEm->Reset();

    // Look for all Video Compressors and add them to the combo box.
    // Note that we do NOT alphabetize the compressors in the list,
    // because we expect them to be in the same order when the user selects
    // an item.  At that point, we will enumerate through the video compressors
    // again in the same order and select the requested item.
    while(1)
    {
        // Ask for the next VideoCompressor Moniker.
        // A Moniker represents an object, but is not the object itself.
        // You must get the object using the moniker's BindToObject
        // or you can get a "PropertyBag" by calling BindToStorage
        //
        ULONG cFetched = 0;
        CComPtr< IMoniker > pMoniker;

        hr = pEm->Next(1, &pMoniker, &cFetched);
        if(!pMoniker)
        {
            break;
        }
        
        // convert the Moniker to a PropertyBag, an object you can use to
        // ask the object's Name
        CComPtr< IPropertyBag > pBag;

        hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**) &pBag);
        if(!FAILED(hr))
        {
            // each video compressor has a name, so ask for it
            VARIANT var;
            var.vt = VT_BSTR;

            hr = pBag->Read(L"FriendlyName",&var, NULL);
            if(hr == NOERROR)
            {
                USES_CONVERSION;
                TCHAR * tName = W2T(var.bstrVal);
                SysFreeString(var.bstrVal);

                // add the object's name to the UI list
                m_CompressorList.AddString(tName);
            }
        }
    }

    // select the first compressor as a default
    m_CompressorList.SetCurSel(0);

    UpdateData(FALSE);
    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// ask for the n'th compressor in the list and return a pointer to a
// DirectShow filter
/////////////////////////////////////////////////////////////////////////////

void CCompressorDlg::GetCompressor(int n, IBaseFilter ** ppCompressor)
{
    HRESULT hr = 0;

    if (!ppCompressor)
    {
        AfxMessageBox(TEXT("GetCompressor received invalid pointer"));
        return;
    }

    *ppCompressor = 0;

    // we use the same technique in this routine as the one that
    // adds compressors to the UI list box, except this time we
    // return a pointer to an actual filter

    CComPtr< ICreateDevEnum > pCreateDevEnum;
    hr = CoCreateInstance(
                        CLSID_SystemDeviceEnum, 
                        NULL, 
                        CLSCTX_INPROC_SERVER,
                        IID_ICreateDevEnum, 
                        (void**) &pCreateDevEnum);

    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Failed to create system enumerator"));
        return;
    }

    CComPtr< IEnumMoniker > pEm;
    hr = pCreateDevEnum->CreateClassEnumerator(
                        CLSID_VideoCompressorCategory,
                        &pEm, 
                        0);

    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Failed to create class enumerator"));
        return;
    }

    pEm->Reset();

    while(1)
    {
        ULONG cFetched = 0;
        CComPtr< IMoniker > pMoniker;

        hr = pEm->Next(1, &pMoniker, &cFetched);
        if(!pMoniker)
        {
            break;
        }
    
        // if this is the object we wanted, then convert the Moniker
        // to an actual DirectShow filter by calling BindToObject on it
        //
        if(n == 0)
        {
            hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**) ppCompressor);
            if(FAILED(hr))
            {
                AfxMessageBox(TEXT("Failed to bind to object"));
            }
            return;
        }

        n--;
    }

    return;
}


void CCompressorDlg::OnStart() 
{
    HRESULT hr = 0;

    // make variables reflect dialog settings
    UpdateData(TRUE);

    if(m_szInputFile.GetLength() > MAX_PATH - 1)
    {
        AfxMessageBox(TEXT("The filename is too long."));
        return;
    }

    // Stop and reset any current playback
    OnButtonStop();
    ResetPlayback();

    // make the filename a WIDE string
    USES_CONVERSION;
    TCHAR * tFilename = m_szInputFile.GetBuffer(MAX_PATH);
    WCHAR * wFilename = T2W(tFilename);

    // First make sure that the file exists
    DWORD dwAttr = GetFileAttributes(tFilename);
    if ((dwAttr == (DWORD) -1) || (dwAttr == FILE_ATTRIBUTE_DIRECTORY))
    {
        AfxMessageBox(TEXT("The specified input file does not exist.\r\n\r\n")
                       TEXT("Please provide a valid media filename."));
        return;
    }
    
    // create a filter graph
    CComPtr< IGraphBuilder > pGraph;
    pGraph.CoCreateInstance(CLSID_FilterGraph);
    if(!pGraph)
    {
        AfxMessageBox(TEXT("Could not create a graph"));
        return;
    }

    // create a CaptureGraphBuilder to help connect filters
    CComPtr< ICaptureGraphBuilder > pBuilder;
    pBuilder.CoCreateInstance(CLSID_CaptureGraphBuilder);

    // tell the capture graph builder what graph we're using
    hr = pBuilder->SetFiltergraph(pGraph);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not setup capture graph"));
        return;
    }

    // ask directshow to add the appropriate source filter for the given file
    CComPtr< IBaseFilter > pSourceBase;
    hr = pGraph->AddSourceFilter(wFilename, L"Source", &pSourceBase);
    if(!pSourceBase)
    {
        AfxMessageBox(TEXT("Could not load source filter for file"));
        return;
    }

    // get a pointer to the compressor we want to use
    m_pCompressor.Release();
    GetCompressor(m_CompressorList.GetCurSel(), &m_pCompressor);

    // in order to force the source filter to produce uncompressed video,
    // we create a SampleGrabber (which only accepts compressed video) and
    // tell it what bit depth to accept
    CComPtr< IBaseFilter > pVideoFilter;
    pVideoFilter.CoCreateInstance(CLSID_SampleGrabber);
    if(!pVideoFilter)
    {
        AfxMessageBox(TEXT("Could not create SampleGrabber from Qedit.dll"));
        return;
    }

    // ask for the ISampleGrabber interface, so we can tell the Grabber to
    // only accept 24 bit uncompressed video
    CComQIPtr< ISampleGrabber, &IID_ISampleGrabber > pVideoGrab(pVideoFilter);

    CMediaType VideoType;
    VideoType.SetType(&MEDIATYPE_Video);
    VideoType.SetSubtype(&MEDIASUBTYPE_RGB24);

    hr = pVideoGrab->SetMediaType(&VideoType);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not set sample grabber's media type"));
        return;
    }

    // Have the graph builder automatically create a MUX and FileWriter for us,
    // and insert them into the graph, by just specifying an output filename
    CComPtr< IBaseFilter > pMux;
    CComPtr< IFileSinkFilter > pWriter;

    // For UNICODE support, copy the CString into a TCHAR array
    TCHAR szOutFilename[MAX_PATH];
    _tcscpy(szOutFilename, (LPCTSTR) m_szOutputFile);

    hr = pBuilder->SetOutputFileName(
                                    &MEDIASUBTYPE_Avi,
                                    T2W(szOutFilename),
                                    &pMux,
                                    &pWriter);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Cannot set up MUX and File Writer"));
        return;
    }

    CComQIPtr< IBaseFilter, &IID_IBaseFilter > pWriterBase(pWriter);

    // we have to add the SampleGrabber and Compressor ourselves, but the
    // other filters have already been added to the graph for us
    hr = pGraph->AddFilter(pVideoFilter, L"VideoGrabber");
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not add VideoGrabber to the graph"));
        return;
    }

    hr = pGraph->AddFilter(m_pCompressor, L"Compressor");
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not add selected compressor to the graph.\r\n\r\n")
                       TEXT("The input file format may not be compatible with the selected encoder.\r\n")
                       TEXT("Some encoders (like Windows Media encoders or DRM-enabled encoders)\r\n")
                       TEXT("cannot be used without appropriate licensing."));
        return;
    }

    // get a set of pins
    CComPtr<IPin> pSourcePin     = GetOutPin(pSourceBase,   0);
    CComPtr<IPin> pVideoIn       = GetInPin (pVideoFilter,  0);
    CComPtr<IPin> pVideoOut      = GetOutPin(pVideoFilter,  0);
    CComPtr<IPin> pCompressorIn  = GetInPin (m_pCompressor, 0);
    CComPtr<IPin> pCompressorOut = GetOutPin(m_pCompressor, 0);
    CComPtr<IPin> pMuxIn1        = GetInPin (pMux, 0);

    // connect the source to the sample grabber
    hr = pGraph->Connect(pSourcePin, pVideoIn);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Cannot connect up video chain"));
        return;
    }

    // connect the sample grabber to the compressor
    hr = pGraph->Connect(pVideoOut, pCompressorIn);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not connect video to selected compressor.\r\n\r\n")
                       TEXT("The input file format may not be compatible with the\r\n")
                       TEXT("selected encoder.  Not all encoders are compatible."));
        return;
    }

    // connect the compressor to the MUX
    hr = pGraph->Connect(pCompressorOut, pMuxIn1);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not connect compressor to mux.\r\n\r\n")
                      TEXT("The selected compressor may not be compatible with this content.\r\n")
                      TEXT("Some encoders (like Windows Media encoders or DRM-enabled encoders)\r\n")
                      TEXT("cannot be used without appropriate licensing."));
        return;
    }

    if(m_bWantAudio)
    {
        // we have to find the correct audio output pin
        CComPtr< IPin > pOtherPin;
        CComPtr< IPin > pSourceAudioOut;

        pCompressorIn->ConnectedTo(&pOtherPin);
        FindOtherSplitterPin(pOtherPin, MEDIATYPE_Audio, 0, &pSourceAudioOut);

        if(pSourceAudioOut)
        {
            // create a sample grabber, so we can force uncompressed audio to
            // run into the MUX
            CComPtr< IBaseFilter > pAudioFilter;
            pAudioFilter.CoCreateInstance(CLSID_SampleGrabber);
            if(!pAudioFilter)
            {
                AfxMessageBox(TEXT("Could not create SampleGrabber from Qedit.dll"));
                return;
            }

            CComQIPtr< ISampleGrabber, &IID_ISampleGrabber > pAudioGrab(pAudioFilter);

            CMediaType AudioType;
            AudioType.SetType(&MEDIATYPE_Audio);
            pAudioGrab->SetMediaType(&AudioType);

            // Add the audio sample grabber to the graph
            hr = pGraph->AddFilter(pAudioFilter, L"AudioGrabber");
            if(FAILED(hr))
            {
                AfxMessageBox(TEXT("Could not add audio filter to graph"));
                return;
            }

            // Connect the audio source through to the mux
            CComPtr<IPin> pAudioIn = GetInPin(pAudioFilter, 0);

            hr = pGraph->Connect(pSourceAudioOut, pAudioIn);
            if(FAILED(hr))
            {
                AfxMessageBox(TEXT("Could not connect audio source to grabber"));
                return;
            }

            CComPtr<IPin> pAudioOut = GetOutPin(pAudioFilter, 0);
            CComPtr<IPin> pMuxIn2   = GetInPin(pMux, 1);

            hr = pGraph->Connect(pAudioOut, pMuxIn2);
            if(FAILED(hr))
            {
                AfxMessageBox(TEXT("Could not connect audio to mux"));
                return;
            }
        }
    }

    // get filter graph interface pointers
    CComQIPtr< IMediaControl, &IID_IMediaControl > pControl(pGraph);
    CComQIPtr< IMediaSeeking, &IID_IMediaSeeking > pSeeking(pGraph);
    CComQIPtr< IMediaEvent,   &IID_IMediaEvent >   pEvent(pGraph);
    CComQIPtr< IMediaFilter,  &IID_IMediaFilter >  pMF(pGraph);

    // tell the graph to run as fast as possible, and not to skip any frames
    // Setting the sync source to NULL disables the clock.
    hr = pMF->SetSyncSource(NULL);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not SetSyncSource NULL on the graph"));
    }

    // ask the graph how long it's going to run
    DWORD dwCaps=0;
    hr = pSeeking->GetCapabilities(&dwCaps);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not read input file seeking capabilities"));
        return;
    }

    REFERENCE_TIME Duration = 0;
    hr = pSeeking->GetDuration(&Duration);

    // Some compressors have a bug where they don't field the GetDuration call
    // correctly. If this happens, then use a default media file duration.
    if(Duration == 0)
    {
        Duration = (REFERENCE_TIME) (ASSUMED_LENGTH * UNITS);

        if (!m_bSuppressWarning)
        {
            AfxMessageBox(TEXT("Could not get the duration of the source file.\r\n\r\n")
                           TEXT("Recompression should work properly, but the\r\n")
                           TEXT("progress bar will not exactly track compression progress."));
        }
    }

    // tell the mux to loosely interleave the audio and the video, if possible
    CComQIPtr< IConfigInterleaving, &IID_IConfigInterleaving > pConfig(pMux);
    hr = pConfig->put_Mode(INTERLEAVE_FULL);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not set interleaving mode"));
        return;
    }

    REFERENCE_TIME InterleaveTime = 1 * UNITS;
    REFERENCE_TIME PrerollTime    = 1 * UNITS;

    hr = pConfig->put_Interleaving(&InterleaveTime, &PrerollTime);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not put interleave time"));
        return;
    }

    // start running the graph to begin the compression process
    hr = pControl->Run();
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not run compression graph"));
        return;
    }

    // update user interface elements
    m_sProgressText = _T("Compressing to output file...");
    SetButtonStates(FALSE);
    m_BtnBrowse.EnableWindow(FALSE);

    // Remember that we're in the compressing state in case
    // the user wants to close the app
    m_bCompressing = TRUE;

    //
    // Pump messages and update UI while waiting for recompression to complete
    //
    while(1)
    {
        long EvCode = 0;

        // Have we received the EC_COMPLETE event?
        hr = pEvent->WaitForCompletion(100, &EvCode);

        // Continue pumping Windows messages during the long compression cycle
        PumpMessages();

        // If user is trying to close the app, stop compressing
        if (m_bCloseRequested)
            break;

        // Update the compression progress bar
        REFERENCE_TIME Start = 0;
        pSeeking->GetCurrentPosition(&Start);

        double done = double(Start) * 100 / double(Duration);
        m_Progress.SetPos((int) done);
        UpdateData(FALSE);

        // If compression is complete, leave the loop
        if(EvCode != 0)
        {
            break;
        }
    }

    // Stop the graph
    pControl->Stop();

    // update UI to indicate completion
    m_Progress.SetPos(0);
    m_sProgressText = _T("Compression complete.");
    SetButtonStates(TRUE);
    m_BtnBrowse.EnableWindow(TRUE);
    m_bCompressing = FALSE;

    MessageBeep(0);
    UpdateData(FALSE);
}


void CCompressorDlg::PumpMessages(void)
{
    MSG msg;

    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


void CCompressorDlg::SetButtonStates(BOOL bState)
{
    m_BtnStart.EnableWindow(bState);
    m_BtnPlayInput.EnableWindow(bState);
    m_BtnPlayOutput.EnableWindow(bState);
    m_BtnStop.EnableWindow(bState);
}


void CCompressorDlg::OnButtonPlayInput() 
{
    UpdateData(TRUE);
    PlayMedia(m_szInputFile);
}


void CCompressorDlg::OnButtonPlayOutput() 
{
    UpdateData(TRUE);
    PlayMedia(m_szOutputFile);
}


void CCompressorDlg::OnButtonStop() 
{
    HRESULT hr;

    // If there is no current graph, nothing needs to be done
    if (!m_pPlaybackGraph)
        return;

    // Get media control and media seeking interfaces
    CComQIPtr< IMediaControl, &IID_IMediaControl > pMediaControl(m_pPlaybackGraph);
    CComQIPtr< IMediaSeeking, &IID_IMediaSeeking > pMediaSeeking(m_pPlaybackGraph);

    // Stop the graph
    hr = pMediaControl->Stop();
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not stop graph"));
        return;
    }

    // Reset to first frame of movie (if the clip supports seeking)
    LONGLONG pos=0;
    hr = pMediaSeeking->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                     NULL, AM_SEEKING_NoPositioning);
  
    // Display the first frame of the movie.
    hr = pMediaControl->Pause();
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not pause graph"));
        return;
    }
}


void CCompressorDlg::PlayMedia(CString& strFile)
{
    HRESULT hr;

    if(strFile.GetLength() > MAX_PATH - 1)
    {
        AfxMessageBox(TEXT("Filename too long"));
        return;
    }

    // Destroy any existing playback filtergraph
    ResetPlayback();

    // Make the filename a WIDE string
    USES_CONVERSION;
    TCHAR * tFilename = strFile.GetBuffer(MAX_PATH);
    WCHAR * wFilename = T2W(tFilename);

    // First make sure that the file exists
    DWORD dwAttr = GetFileAttributes(tFilename);
    if ((dwAttr == (DWORD) -1) || (dwAttr == FILE_ATTRIBUTE_DIRECTORY))
    {
        AfxMessageBox(TEXT("The specified file does not exist.\r\n\r\n")
                       TEXT("Please provide a valid media filename."));
        return;
    }
    
    // Create a graph to play the requested file
    hr = m_pPlaybackGraph.CoCreateInstance(CLSID_FilterGraph);
    if(!m_pPlaybackGraph)
    {
        AfxMessageBox(TEXT("Could not create a graph"));
        return;
    }

    // Render the media file
    hr = m_pPlaybackGraph->RenderFile(wFilename, NULL);
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not render selected file"));
        return;
    }

    // Set video window to be a child window of the screen and
    // position it properly
    CComQIPtr< IVideoWindow, &IID_IVideoWindow > pVW(m_pPlaybackGraph);
    hr = pVW->put_Owner((OAHWND) m_Screen.GetSafeHwnd());

    // If the selected file has no video component, fail gracefully
    // and still play the audio portion
    if (SUCCEEDED(hr))
    {
        // The video window must have the WS_CHILD style
        hr = pVW->put_WindowStyle(WS_CHILD);

        // Read coordinates of video container window
        RECT rc;
        m_Screen.GetClientRect(&rc);
        long width =  rc.right - rc.left;
        long height = rc.bottom - rc.top;

        // Ignore the video's original size and stretch to fit bounding rectangle
        hr = pVW->SetWindowPosition(rc.left, rc.top, width, height);
        if (FAILED(hr))
        {
            AfxMessageBox(TEXT("Failed to set window position"));
            return;
        }
    }

    // Start running the graph
    CComQIPtr< IMediaControl, &IID_IMediaControl > m_pPlaybackControl(m_pPlaybackGraph);
    hr = m_pPlaybackControl->Run();
    if(FAILED(hr))
    {
        AfxMessageBox(TEXT("Could not run playback graph"));
        return;
    }
}


void CCompressorDlg::ResetPlayback(void)
{
    // If there is a current filter graph, destroy it
    if (m_pPlaybackGraph)
    {
        m_pPlaybackGraph.Release();
        m_pPlaybackGraph = NULL;
    }
}


void CCompressorDlg::OnClose() 
{
    // If there is a media playback graph built for previewing,
    // destroy it before closing down the app.
    ResetPlayback();

    m_bCloseRequested = TRUE;
    CDialog::OnClose();
}


void CCompressorDlg::OnDestroy() 
{
    OnClose();
    CDialog::OnDestroy();
}


BOOL CCompressorDlg::OnEraseBkgnd(CDC *pDC)
{
    // Intercept background erasing for the movie window, since the
    // video renderer will keep the screen painted.  Without this code,
    // your video window might get painted over with gray (the default
    // background brush) when it is obscured by another window and redrawn.
    CRect rc;

    // Get the bounding rectangle for the movie screen
    m_Screen.GetWindowRect(&rc);
    ScreenToClient(&rc);

    // Exclude the clipping region occupied by our movie screen
    pDC->ExcludeClipRect(&rc);
    
    // Erase the remainder of the dialog as usual
    return CDialog::OnEraseBkgnd(pDC);
}


