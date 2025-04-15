//------------------------------------------------------------------------------
// File: PlayWndASF.cpp
//
// Desc: DirectShow sample code - a simple audio/video media file player
//       application for Windows Media content (ASF, WMV, WMA).  
//       Pause, stop, mute, and fullscreen mode toggle can be performed 
//       via keyboard commands.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include <dshow.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <tchar.h>
#include <atlbase.h>
#include <wmsdkidl.h>

#include "playwndasf.h"
#include "resource.h"
#include "keyprovider.h"
#include "nserror.h"
#include "urllaunch.h"

// An application can advertise the existence of its filter graph
// by registering the graph with a global Running Object Table (ROT).
// The GraphEdit application can detect and remotely view the running
// filter graph, allowing you to 'spy' on the graph with GraphEdit.
//
// To enable registration in this sample, define REGISTER_FILTERGRAPH.
//
#define REGISTER_FILTERGRAPH

//
// Global data
//
HWND      ghApp=0;
HMENU     ghMenu=0;
HINSTANCE ghInst=0;
TCHAR     g_szFileName[MAX_PATH]={0};
BOOL      g_bAudioOnly=FALSE, g_bFullscreen=FALSE;
LONG      g_lVolume=VOLUME_FULL;
DWORD     g_dwGraphRegister=0;
PLAYSTATE g_psCurrent=Stopped;

// DirectShow interfaces
IGraphBuilder *pGB = NULL;
IMediaControl *pMC = NULL;
IMediaEventEx *pME = NULL;
IVideoWindow  *pVW = NULL;
IBasicAudio   *pBA = NULL;
IBasicVideo   *pBV = NULL;
IMediaSeeking *pMS = NULL;
IVideoFrameStep *pFS = NULL;

// DRM support interfaces
IBaseFilter       *g_pReader = NULL;
IWMDRMReader      *g_pDRMReader = NULL;
IFileSourceFilter *g_pFileSource = NULL;

HANDLE g_hLicenseEvent=0;
BOOL g_bWaitingForLicense = FALSE;

// Global key provider object created/released during the
// Windows Media graph-building stage.
CKeyProvider prov;

const int AUDIO=1, VIDEO=2; // Used for enabling playback menu items

//
// Function prototypes
//
HRESULT HandleNoRightsEx( HRESULT hrStatus, WM_GET_LICENSE_DATA * pLicenseData );
HRESULT HandleNoRights( HRESULT hrStatus, WCHAR *wszChallengeURL);
HRESULT HandleAcquireLicense(HRESULT hrStatus, WM_GET_LICENSE_DATA *pLicenseData);


HRESULT PlayMovieInWindow(LPTSTR szFile, BOOL bReOpenAfterLicenseAcquired)
{
    USES_CONVERSION;
    WCHAR wFile[MAX_PATH];
    HRESULT hr;

    // Check input string
    if (!szFile)
        return E_POINTER;

    // Clear open dialog remnants before calling RenderFile()
    UpdateWindow(ghApp);

    // Convert filename to wide character string
    wcsncpy(wFile, T2W(szFile), NUMELMS(wFile)-1);
    wFile[MAX_PATH-1] = 0;

    // First pass of rendering the media file.  If a DRM license must
    // be acquired before the file can be loaded, then the reopen flag
    // will be set.
    if( !bReOpenAfterLicenseAcquired )
    {
        // Get the interface for DirectShow's GraphBuilder
        JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                             IID_IGraphBuilder, (void **)&pGB));

        JIF(pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME));

        if(SUCCEEDED(hr))
        {
            // Have the graph signal event via window callbacks
            //
            // Start this before we insert the reader filter, since we may need
            // to monitor DRM license acquistion messages on reader creation
            //
            JIF(pME->SetNotifyWindow((OAHWND)ghApp, WM_GRAPHNOTIFY, 0));

            // Use special handling for Windows Media files
            if (IsWindowsMediaFile(szFile))
            {
                // Load the improved ASF reader filter by CLSID
                hr = CreateFilter(CLSID_WMAsfReader, &g_pReader);
                if(FAILED(hr))
                {
                    Msg(TEXT("Failed to create WMAsfWriter filter!  hr=0x%x\0"), hr);
                    return hr;
                }

                // Add the ASF reader filter to the graph.  For ASF/WMV/WMA content,
                // this filter is NOT the default and must be added explicitly.
                hr = pGB->AddFilter(g_pReader, L"ASF Reader");
                if(FAILED(hr))
                {
                    Msg(TEXT("Failed to add ASF reader filter to graph!  hr=0x%x\0"), hr);
                    return hr;
                }

                // Create the key provider that will be used to unlock the WM SDK
                JIF(AddKeyProvider(pGB));
            
                // Create the DRM license event
                g_hLicenseEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
                if( !g_hLicenseEvent )
                {
                    return E_OUTOFMEMORY;
                }

                // Set its source filename
                JIF(g_pReader->QueryInterface(IID_IFileSourceFilter, (void **) &g_pFileSource));

                // Attempt to load this file
                hr = g_pFileSource->Load(wFile, NULL);

                // Handle Digital Rights Management (DRM) errors
                if(NS_E_LICENSE_REQUIRED == hr)
                {
                    Msg(TEXT("This media file is protected by DRM and needs a license.\r\n\r\n")
                        TEXT("Attempting to acquire a license...\0"));
                    g_bWaitingForLicense = TRUE;
                    return hr;
                }
                else if(NS_E_PROTECTED_CONTENT == hr)
                {
                    Msg(TEXT("This media file is protected by DRM and needs a license.\r\n\r\n")
                        TEXT("In order to play DRM-encoded content, you must acquire a DRM stub library\r\n")
                        TEXT("from Microsoft and link it with this application.  The default version of\r\n")
                        TEXT("the WMStub.lib library does not support Digital Rights Management (DRM)."));
                    return hr;
                }
                else if (FAILED(hr))
                {
                    Msg(TEXT("Failed to load file in source filter (g_pFileSource->Load())!  hr=0x%x\0"), hr);
                    return hr;
                }

                // Render the output pins of the ASF reader to build the
                // remainder of the graph automatically
                JIF(RenderOutputPins(pGB, g_pReader));

                // Since the graph is built and the filters are added to the graph,
                // the WM ASF reader interface can be released.
                g_pReader->Release();
                g_pReader = NULL;
            }

            // Not a Windows Media file, so just render the standard way
            else
            {
                // Have the graph builder construct the appropriate graph automatically
                JIF(pGB->RenderFile(wFile, NULL));
            }
        }
    }    
    else
    {
        hr = g_pFileSource->Load(wFile, NULL);
        if( SUCCEEDED( hr ) )
        {
            Msg(TEXT("Successfully loaded file after DRM license acquisition!"));

            // Render the output pins of the ASF reader to build the
            // remainder of the graph automatically
            JIF(RenderOutputPins(pGB, g_pReader));

            // Since the graph is built and the filters are added to the graph,
            // the WM ASF reader interface can be released.
            g_pReader->Release(); // not really necessary
            g_pReader = NULL;
        }
        else
        {
            Msg(TEXT("Failed to Load file after acquiring license!  hr=0x%x\0"), hr);
        }
    }

    if( SUCCEEDED( hr ) )
    {
        // QueryInterface for DirectShow interfaces
        JIF(pGB->QueryInterface(IID_IMediaControl, (void **)&pMC));
        JIF(pGB->QueryInterface(IID_IMediaSeeking, (void **)&pMS));

        // Query for video interfaces, which may not be relevant for audio files
        JIF(pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW));
        JIF(pGB->QueryInterface(IID_IBasicVideo,  (void **)&pBV));

        // Query for audio interfaces, which may not be relevant for video-only files
        JIF(pGB->QueryInterface(IID_IBasicAudio, (void **)&pBA));

        // Is this an audio-only file (no video component)?
        CheckVisibility();

        if (!g_bAudioOnly)
        {
            // Setup the video window
            JIF(pVW->put_Owner((OAHWND)ghApp));
            JIF(pVW->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN));

            JIF(InitVideoWindow(1, 1));
            GetFrameStepInterface();
        }
        else
        {
            // Initialize the default player size and enable playback menu items
            JIF(InitPlayerWindow());
            EnablePlaybackMenu(TRUE, AUDIO);
        }

        // Complete window initialization
        CheckSizeMenu(ID_FILE_SIZE_NORMAL);
        ShowWindow(ghApp, SW_SHOWNORMAL);
        UpdateWindow(ghApp);
        SetForegroundWindow(ghApp);
        g_bFullscreen = FALSE;
        UpdateMainTitle();

#ifdef REGISTER_FILTERGRAPH
        hr = AddGraphToRot(pGB, &g_dwGraphRegister);
        if (FAILED(hr))
        {
            Msg(TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
            g_dwGraphRegister = 0;
        }
#endif

        // Run the graph to play the media file
        JIF(pMC->Run());

        g_psCurrent=Running;
        SetFocus(ghApp);
    }

    return hr;
}


HRESULT RenderOutputPins(IGraphBuilder *pGB, IBaseFilter *pFilter)
{
    HRESULT         hr = S_OK;
    IEnumPins *     pEnumPin = NULL;
    IPin *          pConnectedPin = NULL, * pPin = NULL;
    PIN_DIRECTION   PinDirection;
    ULONG           ulFetched;

    // Enumerate all pins on the filter
    hr = pFilter->EnumPins(&pEnumPin);

    if(SUCCEEDED(hr))
    {
        // Step through every pin, looking for the output pins
        while (S_OK == (hr = pEnumPin->Next(1L, &pPin, &ulFetched)))
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
                hr = pPin->QueryDirection(&PinDirection);
                if ((S_OK == hr) && (PinDirection == PINDIR_OUTPUT))
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


HRESULT AddKeyProvider(IGraphBuilder *pGraph)
{
    HRESULT hr;

    // Instantiate the key provider class, and AddRef it
    // so that COM doesn't try to free our static object.
    prov.AddRef();

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


HRESULT CreateFilter(REFCLSID clsid, IBaseFilter **ppFilter)
{
    HRESULT hr;

    hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER,
        IID_IBaseFilter,
        (void **) ppFilter);

    if(FAILED(hr))
    {
        Msg(TEXT("CreateFilter: Failed to create filter!  hr=0x%x\n"), hr);
        if (ppFilter)
            *ppFilter = NULL;
        return hr;
    }

    return S_OK;
}


BOOL IsWindowsMediaFile(LPTSTR lpszFile)
{
    TCHAR szFilename[MAX_PATH];

    // Copy the file name to a local string and convert to lowercase
    _tcsncpy(szFilename, lpszFile, NUMELMS(szFilename));
    szFilename[MAX_PATH-1] = 0;
    _tcslwr(szFilename);

    if (_tcsstr(szFilename, TEXT(".asf")) ||
        _tcsstr(szFilename, TEXT(".wma")) ||
        _tcsstr(szFilename, TEXT(".wmv")))
        return TRUE;
    else
        return FALSE;
}


HRESULT InitVideoWindow(int nMultiplier, int nDivider)
{
    LONG lHeight, lWidth;
    HRESULT hr = S_OK;
    RECT rect;

    if (!pBV)
        return S_OK;

    // Read the default video size
    hr = pBV->GetVideoSize(&lWidth, &lHeight);
    if (hr == E_NOINTERFACE)
        return S_OK;

    EnablePlaybackMenu(TRUE, VIDEO);

    // Account for requests of normal, half, or double size
    lWidth  = lWidth  * nMultiplier / nDivider;
    lHeight = lHeight * nMultiplier / nDivider;

    int nTitleHeight  = GetSystemMetrics(SM_CYCAPTION);
    int nBorderWidth  = GetSystemMetrics(SM_CXBORDER);
    int nBorderHeight = GetSystemMetrics(SM_CYBORDER);

    // Account for size of title bar and borders for exact match
    // of window client area to default video size
    SetWindowPos(ghApp, NULL, 0, 0, lWidth + 2*nBorderWidth,
                 lHeight + nTitleHeight + 2*nBorderHeight,
                 SWP_NOMOVE | SWP_NOOWNERZORDER);

    GetClientRect(ghApp, &rect);
    JIF(pVW->SetWindowPosition(rect.left, rect.top, rect.right, rect.bottom));

    return hr;
}


HRESULT InitPlayerWindow(void)
{
    // Reset to a default size for audio and after closing a clip
    SetWindowPos(ghApp, NULL, 0, 0,
                 DEFAULT_AUDIO_WIDTH,
                 DEFAULT_AUDIO_HEIGHT,
                 SWP_NOMOVE | SWP_NOOWNERZORDER);

    // Check the 'full size' menu item
    CheckSizeMenu(ID_FILE_SIZE_NORMAL);
    EnablePlaybackMenu(FALSE, 0);

    return S_OK;
}


HRESULT HandleNoRightsEx( HRESULT hrStatus, WM_GET_LICENSE_DATA * pLicenseData )
{
    HRESULT hr = S_OK;
    BOOL fMonitoring = FALSE;
    BSTR bstrURL = NULL;
    
    if((NULL == pLicenseData) || (NULL == pLicenseData->wszLocalFilename))
    {
        return E_INVALIDARG;
    }
    
    if (FAILED(hrStatus) && (NS_E_DRM_NO_RIGHTS != hrStatus))
    {
        Msg(TEXT("Unable to obtain proper license!! Aborting playback...\r\n"));
        hr = hrStatus;
        return hr;
    }

    if( TRUE )
    {    
        IServiceProvider *pServiceProvider;

        JIF(g_pReader->QueryInterface(IID_IServiceProvider, (void **) &pServiceProvider));
        JIF(pServiceProvider->QueryService(IID_IWMDRMReader, IID_IWMDRMReader, 
                                          (void **) &g_pDRMReader));
        pServiceProvider->Release();

        // do silent license acquisition
        hr = g_pDRMReader->AcquireLicense(TRUE);
        if (FAILED(hr))
        {
            Msg(TEXT("AcquireLicense Failed!  hr=0x%x\n"), hr);
            SAFE_RELEASE(g_pDRMReader);
            return hr;
        }
    }
    else // non-silent acquisition
    {
        // convert wszs to bstrs so we can pass them to core
        bstrURL = SysAllocString(pLicenseData->wszLocalFilename);
        if (!bstrURL)
        {
            hr = E_OUTOFMEMORY;
        }
        else
        {       
            // start license monitoring
            hr = g_pDRMReader->MonitorLicenseAcquisition();
            if (FAILED(hr))
            {
                // wmp explicitly ignores hr here
                g_pDRMReader->CancelMonitorLicenseAcquisition(); 
            }
            else
            {
                fMonitoring = true;
            }

            SysFreeString(bstrURL);
        }
    }            
    
    SAFE_RELEASE(g_pDRMReader);
    return hr;
}


HRESULT HandleNoRights( HRESULT hrStatus, WCHAR *wszChallengeURL)
{   
    USES_CONVERSION;
    HRESULT hr = S_OK;
    LPWSTR pszEscapedURL = NULL;
    WCHAR pszURL[MAX_PATH];

    if( NULL == wszChallengeURL )
    {
        return E_INVALIDARG;
    }
    
    if( FAILED( hrStatus ) )
    {
        Msg(TEXT("Unable to obtain proper license!! (hrStatus = 0x%x) Aborting playback...\r\n"), hrStatus);
        return hr;
    }
    
    // Convert filename to wide character string
    wcsncpy(pszURL, T2W(g_szFileName), NUMELMS(pszURL)-1);
    pszURL[MAX_PATH-1] = 0;

    hr = MakeEscapedURL(pszURL, &pszEscapedURL);

    if( SUCCEEDED(hr) )
    {
        WCHAR szURL[ 0x1000 ];
        BSTR bstrChallengeURL = SysAllocString(wszChallengeURL);
        if (!bstrChallengeURL)
            return E_OUTOFMEMORY;

        swprintf(szURL, L"%s&filename=%s&embedded=false", bstrChallengeURL, pszEscapedURL);

        hr = LaunchURL(szURL);
        if( FAILED(hr))
        {
            Msg(TEXT("Unable to launch web browser to retrieve playback license (err = %#X)\n"), hr);
        }

        delete [] pszEscapedURL;
        SysFreeString(bstrChallengeURL);
    }

    return hr;
}


// Handler for (EC_)WMT_ACQUIRE_LICENSE
HRESULT HandleAcquireLicense(HRESULT hrStatus, WM_GET_LICENSE_DATA *pLicenseData)
{
    HRESULT hr = S_OK;

    if (NULL == pLicenseData)
    {
        return E_INVALIDARG;
    }
    
    // received notification that marks the end of license acquisition
    if (FAILED(hrStatus))
    {    
        //
        // NOTE:
        // We failed to acquire a license with silent acquisition.
        // Your application may want to try non-silent acquisition in this case.
        //

        // Windows XP can fail with a DRM license store error
        if (NS_E_DRM_LICENSE_STORE_ERROR == hrStatus)
        {
            Msg(TEXT("There was an error in the DRM license store! (hrStatus = 0x%x)\r\n"), hrStatus);
            return hr;
        }

        if (NS_E_DRM_LICENSE_NOTACQUIRED != hrStatus)
        {
            Msg(TEXT("Unable to acquire license! (hrStatus = 0x%x)\r\n"), hrStatus);
            return hr;
        }

        // make sure we have a challenge url
        if (NULL == pLicenseData->wszLocalFilename)
        {
            //DPF_ERR("HandleAcquireLicense: a null challenge url was passed");        
            return E_INVALIDARG;
        }
    }
    else
    {             
        // We successfully acquired the license, so reopen the file
        hr = PlayMovieInWindow(g_szFileName, TRUE);
        if (FAILED(hr))
        {
            Msg(TEXT("HandleAcquireLicense: Reader failed to open file! (hr = 0x%x)\r\n"), hr);
        }                    
    }

    return hr;
}


void MoveVideoWindow(void)
{
    HRESULT hr;
    
    // Track the movement of the container window and resize as needed
    if(pVW)
    {
        RECT client;

        GetClientRect(ghApp, &client);
        hr = pVW->SetWindowPosition(client.left, client.top, 
                                    client.right, client.bottom);
    }
}


void CheckVisibility(void)
{
    long lVisible;
    HRESULT hr;

    if ((!pVW) || (!pBV))
    {
        // Audio-only files have no video interfaces.  This might also
        // be a file whose video component uses an unknown video codec.
        g_bAudioOnly = TRUE;
        return;
    }
    else
    {
        // Clear the global flag
        g_bAudioOnly = FALSE;
    }

    hr = pVW->get_Visible(&lVisible);
    if (FAILED(hr))
    {
        // If this is an audio-only clip, get_Visible() won't work.
        //
        // Also, if this video is encoded with an unsupported codec,
        // we won't see any video, although the audio will work if it is
        // of a supported format.
        //
        if (hr == E_NOINTERFACE)
        {
            g_bAudioOnly = TRUE;
        }
        else
        {
            Msg(TEXT("Failed(%08lx) in pVW->get_Visible()!\r\n"), hr);
        }
    }
}


void PauseClip(void)
{
    if (!pMC)
        return;

    // Toggle play/pause behavior
    if((g_psCurrent == Paused) || (g_psCurrent == Stopped))
    {
        if (SUCCEEDED(pMC->Run()))
            g_psCurrent = Running;
    }
    else
    {
        if (SUCCEEDED(pMC->Pause()))
            g_psCurrent = Paused;
    }

    UpdateMainTitle();
}


void StopClip(void)
{
    HRESULT hr;
    
    if ((!pMC) || (!pMS))
        return;

    // Stop and reset postion to beginning
    if((g_psCurrent == Paused) || (g_psCurrent == Running))
    {
        LONGLONG pos = 0;
        hr = pMC->Stop();
        g_psCurrent = Stopped;

        // Seek to the beginning
        hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
            NULL, AM_SEEKING_NoPositioning);

        // Display the first frame to indicate the reset condition
        hr = pMC->Pause();
    }

    UpdateMainTitle();
}


void OpenClip()
{
    HRESULT hr;

    // If no filename specified by command line, show file open dialog
    if(g_szFileName[0] == L'\0')
    {
        TCHAR szFilename[MAX_PATH];

        UpdateMainTitle();

        // If no filename was specified on the command line, then our video
        // window has not been created or made visible.  Make our main window
        // visible and bring to the front to allow file selection.
        InitPlayerWindow();
        ShowWindow(ghApp, SW_SHOWNORMAL);
        SetForegroundWindow(ghApp);

        if (! GetClipFileName(szFilename))
        {
            DWORD dwDlgErr = CommDlgExtendedError();

            // Don't show output if user cancelled the selection (no dlg error)
            if (dwDlgErr)
            {
                Msg(TEXT("GetClipFileName Failed! Error=0x%x\r\n"), GetLastError());
            }
            return;
        }

        // This sample does not support playback of ASX playlists.
        // Since this could be confusing to a user, display a warning
        // message if an ASX file was opened.
        if (_tcsstr((_tcslwr(szFilename)), TEXT(".asx")))
        {
            Msg(TEXT("ASX Playlists are not supported by this application.\n\n")
                TEXT("Please select a valid media file.\0"));
            return;
        }

        lstrcpy(g_szFileName, szFilename);
    }

    // Reset status variables
    g_psCurrent = Stopped;
    g_lVolume = VOLUME_FULL;
    
    // Start playing the media file
    hr = PlayMovieInWindow(g_szFileName, FALSE);

    // If we couldn't play the clip, clean up
    if (FAILED(hr) && ( hr != NS_E_LICENSE_REQUIRED ) )
        CloseClip();
}


BOOL GetClipFileName(LPTSTR szName)
{
    static OPENFILENAME ofn={0};
    static BOOL bSetInitialDir = FALSE;

    // Reset filename
    *szName = 0;

    // Fill in standard structure fields
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = ghApp;
    ofn.lpstrFilter       = NULL;
    ofn.lpstrFilter       = FILE_FILTER_TEXT;
    ofn.lpstrCustomFilter = NULL;
    ofn.nFilterIndex      = 1;
    ofn.lpstrFile         = szName;
    ofn.nMaxFile          = MAX_PATH;
    ofn.lpstrTitle        = TEXT("Open Media File...\0");
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


void CloseClip()
{
    HRESULT hr;

    // Stop media playback
    if(pMC)
        hr = pMC->Stop();

    // Clear global flags
    g_psCurrent = Stopped;
    g_bAudioOnly = TRUE;
    g_bFullscreen = FALSE;

    // Free DirectShow interfaces
    CloseInterfaces();

    // Clear file name to allow selection of new file with open dialog
    g_szFileName[0] = L'\0';

    // No current media state
    g_psCurrent = Init;

    // Reset the player window
    RECT rect;
    GetClientRect(ghApp, &rect);
    InvalidateRect(ghApp, &rect, TRUE);

    UpdateMainTitle();
    InitPlayerWindow();
}


void CloseInterfaces(void)
{
    HRESULT hr;
    
    // Relinquish ownership (IMPORTANT!) after hiding video window
    if(pVW)
    {
        hr = pVW->put_Visible(OAFALSE);
        hr = pVW->put_Owner(NULL);
    }

    // Disable event callbacks
    if (pME)
        hr = pME->SetNotifyWindow((OAHWND)NULL, 0, 0);

#ifdef REGISTER_FILTERGRAPH
    if (g_dwGraphRegister)
    {
        RemoveGraphFromRot(g_dwGraphRegister);
        g_dwGraphRegister = 0;
    }
#endif

    // Release and zero DirectShow interfaces
    SAFE_RELEASE(g_pFileSource);
    SAFE_RELEASE(g_pDRMReader);
    SAFE_RELEASE(g_pReader);

    SAFE_RELEASE(pME);
    SAFE_RELEASE(pMS);
    SAFE_RELEASE(pFS);
    SAFE_RELEASE(pMC);
    SAFE_RELEASE(pBA);
    SAFE_RELEASE(pBV);
    SAFE_RELEASE(pVW);
    SAFE_RELEASE(pGB);

    // Destroy the license event
    if (g_hLicenseEvent)
    {
        CloseHandle(g_hLicenseEvent);
        g_hLicenseEvent = 0;
    }
}


#ifdef REGISTER_FILTERGRAPH

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
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

void RemoveGraphFromRot(DWORD pdwRegister)
{
    IRunningObjectTable *pROT;

    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) 
    {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
}

#endif


void Msg(TCHAR *szFormat, ...)
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
    MessageBox(NULL, szBuffer, TEXT("PlayWndASF Sample"), MB_OK);
}


HRESULT ToggleMute(void)
{
    HRESULT hr=S_OK;

    if ((!pGB) || (!pBA))
        return S_OK;

    // Read current volume
    hr = pBA->get_Volume(&g_lVolume);
    if (hr == E_NOTIMPL)
    {
        // Fail quietly if this is a video-only media file
        return S_OK;
    }
    else if (FAILED(hr))
    {
        Msg(TEXT("Failed to read audio volume!  hr=0x%x\r\n"), hr);
        return hr;
    }

    // Switch volume levels
    if (g_lVolume == VOLUME_FULL)
        g_lVolume = VOLUME_SILENCE;
    else
        g_lVolume = VOLUME_FULL;

    // Set new volume
    JIF(pBA->put_Volume(g_lVolume));

    UpdateMainTitle();
    return hr;
}


void UpdateMainTitle(void)
{
    TCHAR szTitle[MAX_PATH], szFile[MAX_PATH];

    // If no file is loaded, just show the application title
    if (g_szFileName[0] == L'\0')
    {
        _tcscpy(szTitle, APPLICATIONNAME);
    }

    // Otherwise, show useful information
    else
    {
        // Get file name without full path
        GetFilename(g_szFileName, szFile);

        // Update the window title to show filename and play state
        wsprintf(szTitle, TEXT("%s [%s] %s%s"),
                szFile,
                g_bAudioOnly ? TEXT("Audio") : TEXT("Video"),
                (g_lVolume == VOLUME_SILENCE) ? TEXT("(Muted)") : TEXT(""),
                (g_psCurrent == Paused) ? TEXT("(Paused)") : TEXT(""));
    }

    SetWindowText(ghApp, szTitle);
}


void GetFilename(TCHAR *pszFull, TCHAR *pszFile)
{
    int nLength;
    TCHAR szPath[MAX_PATH]={0};
    BOOL bSetFilename=FALSE;

    // Strip path and return just the file's name
    _tcsncpy(szPath, pszFull, MAX_PATH);
    szPath[MAX_PATH-1] = 0;

    nLength = (int) _tcslen(szPath);

    for (int i=nLength-1; i>=0; i--)
    {
        if ((szPath[i] == '\\') || (szPath[i] == '/'))
        {
            szPath[i] = '\0';
            lstrcpyn(pszFile, &szPath[i+1], MAX_PATH);
            bSetFilename = TRUE;
            break;
        }
    }

    // If there was no path given (just a file name), then
    // just copy the full path to the target path.
    if (!bSetFilename)
        _tcsncpy(pszFile, pszFull, MAX_PATH);
        
    pszFile[MAX_PATH-1] = 0;        // Ensure null-termination
}


HRESULT ToggleFullScreen(void)
{
    HRESULT hr=S_OK;
    LONG lMode;
    static HWND hDrain=0;

    // Don't bother with full-screen for audio-only files
    if ((g_bAudioOnly) || (!pVW))
        return S_OK;

    // Read current state
    JIF(pVW->get_FullScreenMode(&lMode));

    if (lMode == OAFALSE)
    {
        // Save current message drain
        LIF(pVW->get_MessageDrain((OAHWND *) &hDrain));

        // Set message drain to application main window
        LIF(pVW->put_MessageDrain((OAHWND) ghApp));

        // Switch to full-screen mode
        lMode = OATRUE;
        JIF(pVW->put_FullScreenMode(lMode));
        g_bFullscreen = TRUE;
    }
    else
    {
        // Switch back to windowed mode
        lMode = OAFALSE;
        JIF(pVW->put_FullScreenMode(lMode));

        // Undo change of message drain
        LIF(pVW->put_MessageDrain((OAHWND) hDrain));

        // Reset video window
        LIF(pVW->SetWindowForeground(-1));

        // Reclaim keyboard focus for player application
        UpdateWindow(ghApp);
        SetForegroundWindow(ghApp);
        SetFocus(ghApp);
        g_bFullscreen = FALSE;
    }

    return hr;
}


//
// Some video renderers support stepping media frame by frame with the 
// IVideoFrameStep interface.  See the interface documentation for more 
// details on frame stepping.
//
BOOL GetFrameStepInterface(void)
{
    HRESULT hr;
    IVideoFrameStep *pFSTest = NULL;

    // Get the frame step interface, if supported
    hr = pGB->QueryInterface(__uuidof(IVideoFrameStep), (PVOID *)&pFSTest);
    if (FAILED(hr))
        return FALSE;

    // Check if this decoder can step
    hr = pFSTest->CanStep(0L, NULL); 

    if (hr == S_OK)
    {
        pFS = pFSTest;  // Save interface to global variable for later use
        return TRUE;
    }
    else
    {
        pFSTest->Release();
        return FALSE;
    }
}


HRESULT StepOneFrame(void)
{
    HRESULT hr=S_OK;

    // If the Frame Stepping interface exists, use it to step one frame
    if (pFS)
    {
        // The graph must be paused for frame stepping to work
        if (g_psCurrent != State_Paused)
            PauseClip();

        // Step the requested number of frames, if supported
        hr = pFS->Step(1, NULL); 
    }

    return hr;
}

HRESULT StepFrames(int nFramesToStep)
{
    HRESULT hr=S_OK;

    // If the Frame Stepping interface exists, use it to step frames
    if (pFS)
    {
        // The renderer may not support frame stepping for more than one
        // frame at a time, so check for support.  S_OK indicates that the
        // renderer can step nFramesToStep successfully.
        if ((hr = pFS->CanStep(nFramesToStep, NULL)) == S_OK)
        {
            // The graph must be paused for frame stepping to work
            if (g_psCurrent != State_Paused)
                PauseClip();

            // Step the requested number of frames, if supported
            hr = pFS->Step(nFramesToStep, NULL); 
        }
    }

    return hr;
}


HRESULT HandleGraphEvent(void)
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
        // If this is the end of the clip, reset to beginning
        if(EC_COMPLETE == evCode)
        {
            LONGLONG pos=0;

            // Reset to first frame of movie
            hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                   NULL, AM_SEEKING_NoPositioning);
            if (FAILED(hr))
            {
                // Some custom filters (like the Windows CE MIDI filter) 
                // may not implement seeking interfaces (IMediaSeeking)
                // to allow seeking to the start.  In that case, just stop 
                // and restart for the same effect.  This should not be
                // necessary in most cases.
                if (FAILED(hr = pMC->Stop()))
                {
                    Msg(TEXT("Failed(0x%08lx) to stop media clip!\r\n"), hr);
                    break;
                }

                if (FAILED(hr = pMC->Run()))
                {
                    Msg(TEXT("Failed(0x%08lx) to reset media clip!\r\n"), hr);
                    break;
                }
            }
        }
        else if(EC_ERRORABORT == evCode)
        {
            Msg(TEXT("Playback error (EC_ERRORABORT - 0x%08lx). Aborting...\r\n"), evParam1);

            if (FAILED(hr = pMC->Stop()))
                Msg(TEXT("Failed(0x%08lx) to stop media clip!\r\n"), hr);

            hr = (HRESULT) evParam1;
            break;
        }
        else if( EC_WMT_EVENT == evCode )
        {
            AM_WMT_EVENT_DATA *pEventData = (AM_WMT_EVENT_DATA *)evParam2;
            hr = HandleWMTEvent(pEventData, evParam1);
        }
    }

    // Free memory associated with callback
    if( FAILED(pME->FreeEventParams(evCode, evParam1, evParam2)) )
    {
        CloseClip();
    }

    return hr;
}


HRESULT HandleWMTEvent(AM_WMT_EVENT_DATA *pEventData, LONG evParam1)
{
    HRESULT hr=S_OK;

    // If you attempt to play a DRM-encoded file with a version of this app
    // that was NOT built with a DRM stub library, then the event data will be NULL.
    // You must rebuild the sample with the proper library to enable DRM support.
    if( NULL == pEventData )
    {
        // Msg(TEXT("Received EC_WMT_EVENT but evParam2 is NULL!  Aborting...\r\n") );
        return E_FAIL;
    }

    switch( evParam1 )
    {
        case WMT_NO_RIGHTS:

            Msg(TEXT("Received WMT_NO_RIGHTS! (hrStatus = 0x%x)\0"), pEventData->hrStatus);
    
            if( pEventData->pData )
            {
                hr = HandleNoRights(pEventData->hrStatus, (WCHAR *)pEventData->pData);
            }
            else
            {
                hr = E_FAIL;
            }
            break;

        case WMT_NO_RIGHTS_EX:

            // license acquisition?
            Msg(TEXT("Received WMT_NO_RIGHTS_EX! (hrStatus = 0x%x)\r\n"), pEventData->hrStatus);

            if( pEventData->pData )
            {
                hr = HandleNoRightsEx(pEventData->hrStatus, 
                                     (WM_GET_LICENSE_DATA *)pEventData->pData);
            }
            else
            {
                hr = E_FAIL;
            }
            break;

        case WMT_ACQUIRE_LICENSE:

            Msg(TEXT("Received WMT_ACQUIRE_LICENSE! (hrStatus = 0x%x)\r\n"), pEventData->hrStatus);

            if( pEventData->pData )
            {
                hr = HandleAcquireLicense(pEventData->hrStatus, 
                                         (WM_GET_LICENSE_DATA *)pEventData->pData);
            }
            else
            {
                hr = E_FAIL;
            }
            break;
    }

    return hr;
}


void CheckSizeMenu(WPARAM wParam)
{
    WPARAM nItems[4] = {ID_FILE_SIZE_HALF,    ID_FILE_SIZE_DOUBLE, 
                        ID_FILE_SIZE_NORMAL,  ID_FILE_SIZE_THREEQUARTER};

    // Set/clear checkboxes that indicate the size of the video clip
    for (int i=0; i<4; i++)
    {
        // Check the selected item
        CheckMenuItem(ghMenu, (UINT) nItems[i],
                     (UINT) (wParam == nItems[i]) ? MF_CHECKED : MF_UNCHECKED);
    }
}


void EnablePlaybackMenu(BOOL bEnable, int nMediaType)
{
    int i;
    WPARAM nItems[9] = {ID_FILE_PAUSE,        ID_FILE_STOP,
                        ID_FILE_MUTE,         ID_SINGLE_STEP,
                        ID_FILE_SIZE_HALF,    ID_FILE_SIZE_DOUBLE,  
                        ID_FILE_SIZE_NORMAL,  ID_FILE_SIZE_THREEQUARTER, 
                        ID_FILE_FULLSCREEN};

    // Enable/disable menu items related to playback (pause, stop, mute)
    for (i=0; i<3; i++)
    {
        EnableMenuItem(ghMenu, (UINT) nItems[i],
                      (UINT) (bEnable) ? MF_ENABLED : MF_GRAYED);
    }

    // Enable/disable menu items related to video size
    for (i=3; i<9; i++)
    {
        EnableMenuItem(ghMenu, (UINT) nItems[i],
                     (UINT) (nMediaType == VIDEO) ? MF_ENABLED : MF_GRAYED);
    }
}


LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            if (wParam == IDOK)
            {   
                EndDialog(hWnd, TRUE);
                return TRUE;
            }
            break;
    }
    return FALSE;
}


LRESULT CALLBACK WndMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        // Resize the video when the window changes
        case WM_MOVE:
        case WM_SIZE:
            if ((hWnd == ghApp) && (!g_bAudioOnly))
                MoveVideoWindow();
            break;

        // Enforce a minimum size
        case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO lpmm = (LPMINMAXINFO) lParam;
                lpmm->ptMinTrackSize.x = MINIMUM_VIDEO_WIDTH;
                lpmm->ptMinTrackSize.y = MINIMUM_VIDEO_HEIGHT;
            }
            break;

        case WM_KEYDOWN:

            switch(toupper((int) wParam))
            {
                // Frame stepping
                case VK_SPACE:
                case '1':
                    StepOneFrame();
                    break;

                // Frame stepping (multiple frames)
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    StepFrames((int) wParam - '0');
                    break;

                case 'P':
                    PauseClip();
                    break;

                case 'S':
                    StopClip();
                    break;

                case 'M':
                    ToggleMute();
                    break;

                case 'F':
                case VK_RETURN:
                    ToggleFullScreen();
                    break;

               case 'H':
                    InitVideoWindow(1,2);
                    CheckSizeMenu(wParam);
                    break;
                case 'N':
                    InitVideoWindow(1,1);
                    CheckSizeMenu(wParam);
                    break;
                case 'D':
                    InitVideoWindow(2,1);
                    CheckSizeMenu(wParam);
                    break;
                case 'T':
                    InitVideoWindow(3,4);
                    CheckSizeMenu(wParam);
                    break;

                case VK_ESCAPE:
                    if (g_bFullscreen)
                        ToggleFullScreen();
                    else
                        CloseClip();
                    break;

                case VK_F12:
                case 'Q':
                case 'X':
                    CloseClip();
                    break;
            }
            break;

        case WM_COMMAND:

            switch(wParam)
            { // Menus

                case ID_FILE_OPENCLIP:
                    // If we have ANY file open, close it and shut down DirectShow
                    if (g_psCurrent != Init)
                        CloseClip();

                    // Open the new clip
                    OpenClip();
                    break;

                case ID_FILE_EXIT:
                    CloseClip();
                    PostQuitMessage(0);
                    break;

                case ID_FILE_PAUSE:
                    PauseClip();
                    break;

                case ID_FILE_STOP:
                    StopClip();
                    break;

                case ID_FILE_CLOSE:
                    CloseClip();
                    break;

                case ID_FILE_MUTE:
                    ToggleMute();
                    break;

                case ID_FILE_FULLSCREEN:
                    ToggleFullScreen();
                    break;

                case ID_HELP_ABOUT:
                    DialogBox(ghInst, MAKEINTRESOURCE(IDD_ABOUTBOX), 
                              ghApp,  (DLGPROC) AboutDlgProc);
                    break;

                case ID_FILE_SIZE_HALF:
                    InitVideoWindow(1,2);
                    CheckSizeMenu(wParam);
                    break;
                case ID_FILE_SIZE_NORMAL:
                    InitVideoWindow(1,1);
                    CheckSizeMenu(wParam);
                    break;
                case ID_FILE_SIZE_DOUBLE:
                    InitVideoWindow(2,1);
                    CheckSizeMenu(wParam);
                    break;
                case ID_FILE_SIZE_THREEQUARTER:
                    InitVideoWindow(3,4);
                    CheckSizeMenu(wParam);
                    break;

                case ID_SINGLE_STEP:
                    StepOneFrame();
                    break;

            } // Menus
            break;


        case WM_GRAPHNOTIFY:
            HandleGraphEvent();
            break;

        case WM_CLOSE:
            SendMessage(ghApp, WM_COMMAND, ID_FILE_EXIT, 0);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);

    } // Window msgs handling

    // Pass this message to the video window for notification of system changes
    if (pVW)
        pVW->NotifyOwnerMessage((LONG_PTR) hWnd, message, wParam, lParam);

    return DefWindowProc(hWnd, message, wParam, lParam);
}


int PASCAL WinMain(HINSTANCE hInstC, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg={0};
    WNDCLASS wc;

    // Initialize COM
    if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        Msg(TEXT("CoInitialize Failed!\r\n"));
        exit(1);
    }

    // Was a filename specified on the command line?
    if(lpCmdLine[0] != '\0')
    {
        USES_CONVERSION;
        _tcsncpy(g_szFileName, A2T(lpCmdLine), NUMELMS(g_szFileName));        
    }

    // Set initial media state
    g_psCurrent = Init;

    // Register the window class
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc = WndMainProc;
    ghInst = wc.hInstance = hInstC;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(hInstC, MAKEINTRESOURCE(IDI_PLAYWND));
    if(!RegisterClass(&wc))
    {
        Msg(TEXT("RegisterClass Failed! Error=0x%x\r\n"), GetLastError());
        CoUninitialize();
        exit(1);
    }

    // Create the main window.  The WS_CLIPCHILDREN style is required.
    ghApp = CreateWindow(CLASSNAME, APPLICATIONNAME,
                    WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN,
                    CW_USEDEFAULT, CW_USEDEFAULT,
                    CW_USEDEFAULT, CW_USEDEFAULT,
                    0, 0, ghInst, 0);

    if(ghApp)
    {
        // Save menu handle for later use
        ghMenu = GetMenu(ghApp);

        // Open the specified media file or prompt for a title
        PostMessage(ghApp, WM_COMMAND, ID_FILE_OPENCLIP, 0);

        // Main message loop
        while(GetMessage(&msg,NULL,0,0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    else
    {
        Msg(TEXT("Failed to create the main window! Error=0x%x\r\n"), GetLastError());
    }

    // Finished with COM
    CoUninitialize();

    return (int) msg.wParam;
}


