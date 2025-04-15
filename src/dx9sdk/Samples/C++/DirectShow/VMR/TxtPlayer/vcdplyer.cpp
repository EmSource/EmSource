//------------------------------------------------------------------------------
// File: vcdplyer.cpp
//
// Desc: DirectShow sample code - VMR-enabled player app with text
//
// Copyright (c) 1994 - 2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"
#include "mpgcodec.h"

extern int FrameStepCount;


/******************************Public*Routine******************************\
* CMovie
*
* Constructors and destructors
*
\**************************************************************************/
CMovie::CMovie(HWND hwndApplication)
    : CUnknown(NAME("Allocator Presenter"), NULL),
      m_hwndApp(hwndApplication),
      m_MediaEvent(NULL),
      m_Mode(MOVIE_NOTOPENED),
      m_Fg(NULL),
      m_Gb(NULL),
      m_Mc(NULL),
      m_Ms(NULL),
      m_Me(NULL),
      m_Wc(NULL),
      m_SAN(NULL),
      m_bRndLess(TRUE),
      pMpegAudioDecoder(NULL),
      pVideoRenderer(NULL),
      m_TimeFormat(TIME_FORMAT_MEDIA_TIME),
      m_hFont(NULL),
      m_cxFont(0), m_cxFontImg(0),
      m_cyFont(0), m_cyFontImg(0),
      m_lpDDSFontCache(NULL),
      m_lpBltAlpha(NULL),
      m_lpDDAppImage(NULL)
{
    m_hMonitor = NULL;
    m_lpDDObj = NULL;
    m_lpPriSurf = NULL;
    m_lpBackBuffer = NULL;
    m_lpDDTexture = NULL;

    AddRef();
}

CMovie::~CMovie()
{
}


static HRESULT SetRenderingMode( IBaseFilter* pBaseFilter, VMRMode mode, bool bMixingMode )
{
    // Test VMRConfig, VMRMonitorConfig
    IVMRFilterConfig* pConfig;

    HRESULT hr = pBaseFilter->QueryInterface(IID_IVMRFilterConfig, (LPVOID *)&pConfig);
    if(SUCCEEDED(hr))
    {
        pConfig->SetRenderingMode(mode);
        pConfig->SetRenderingPrefs(RenderPrefs_AllowOverlays);

        if(  true == bMixingMode )
            pConfig->SetNumberOfStreams(2);

        pConfig->Release();
    }
    return hr;
}

/******************************Public*Routine******************************\
* AddVideoMixingRendererToFG
*
\**************************************************************************/
HRESULT
CMovie::AddVideoMixingRendererToFG( bool bMixingMode )
{
    IBaseFilter* pBF = NULL;
    HRESULT hRes = CoCreateInstance(CLSID_VideoMixingRenderer, NULL, CLSCTX_INPROC,
                                    IID_IBaseFilter, (LPVOID *)&pBF);

    if(SUCCEEDED(hRes))
    {
        hRes = m_Fg->AddFilter(pBF, L"Video Mixing Renderer");

        if(SUCCEEDED(hRes))
        {
            if(m_bRndLess)
            {
                hRes = SetRenderingMode(pBF, VMRMode_Renderless, bMixingMode);

                if(SUCCEEDED(hRes))
                {
                    hRes = pBF->QueryInterface(IID_IVMRSurfaceAllocatorNotify,
                                              (LPVOID *)&m_SAN);
                }

                if(SUCCEEDED(hRes))
                {
                    hRes = m_SAN->AdviseSurfaceAllocator(0, this);
                }

                if(SUCCEEDED(hRes))
                {
                    hRes = m_SAN->SetDDrawDevice(m_lpDDObj, m_hMonitor);
                }
            }
            else
            {
                hRes = SetRenderingMode(pBF, VMRMode_Windowless, bMixingMode);
                if(SUCCEEDED(hRes))
                {
                    hRes = pBF->QueryInterface(IID_IVMRWindowlessControl, (LPVOID *)&m_Wc);
                }

                if(SUCCEEDED(hRes))
                {
                    m_Wc->SetVideoClippingWindow(m_hwndApp);
                }
                else
                {
                    if(m_Wc)
                    {
                        m_Wc->Release();
                        m_Wc = NULL;
                    }
                }
            }
        }
    }

    if(pBF)
    {
        pBF->Release();
    }

    if(FAILED(hRes))
    {
        if(m_SAN)
        {
            m_SAN->Release();
            m_SAN = NULL;
        }
    }

    return hRes;
}

/******************************Public*Routine******************************\
* OpenMovie
*
\**************************************************************************/
HRESULT
CMovie::OpenMovie(
    TCHAR *lpFileName,
    TCHAR* achError, 
    UINT uintLen,     
    bool bMixingMode
    )
{
    USES_CONVERSION;
    IUnknown  *pUnk;
    HRESULT   hres;
    WCHAR     FileName[MAX_PATH];

    wcsncpy(FileName, T2W(lpFileName), NUMELMS(FileName));

    hres = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if(hres == S_FALSE)
    {
        CoUninitialize();
    }

    hres = Initialize3DEnvironment(m_hwndApp, achError, uintLen);
    if (hres != S_OK) {
        return hres;
    }

    hres = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
                            IID_IUnknown, (LPVOID *)&pUnk);

    if(SUCCEEDED(hres))
    {
        m_Mode = MOVIE_OPENED;
        hres = pUnk->QueryInterface(IID_IFilterGraph, (LPVOID *)&m_Fg);
        if(FAILED(hres))
        {
            pUnk->Release();
            return hres;
        }

        hres = AddVideoMixingRendererToFG(bMixingMode);
        if(FAILED(hres))
        {
            m_Fg->Release(); m_Fg = NULL;
            return hres;
        }

        hres = pUnk->QueryInterface(IID_IGraphBuilder, (LPVOID *)&m_Gb);
        if(FAILED(hres))
        {
            pUnk->Release();
            m_Fg->Release(); m_Fg = NULL;
            m_Wc->Release(); m_Wc = NULL;
            return hres;
        }

        hres = m_Gb->RenderFile(FileName, NULL);
        if(FAILED(hres))
        {
            pUnk->Release();
            m_Fg->Release(); m_Fg = NULL;
            if(m_Wc)
                m_Wc->Release(); m_Wc = NULL;
            m_Gb->Release(); m_Gb = NULL;
            return hres;
        }

        // check if any of VMR pin is connected; if not, report this as a failure
        {
            HRESULT hr = S_OK;
            bool bPinConnected = false;

            IBaseFilter *pBf = NULL;
            IEnumPins *pEnum = NULL;
            IPin* pPin = NULL;

            hr = m_SAN->QueryInterface( IID_IBaseFilter, (void**)&pBf);
            if( SUCCEEDED(hr))
            {
                hr = pBf->EnumPins( &pEnum );
                pBf->Release();
                if( SUCCEEDED(hr))
                {
                    hr = pEnum->Next(1, &pPin, NULL);
                    while( SUCCEEDED(hr) && pPin )
                    {
                        IPin *pPinConnected = NULL;
                        hr = pPin->ConnectedTo( &pPinConnected );
                        if( SUCCEEDED(hr) && pPinConnected )
                        {
                            bPinConnected = true;
                            pPin->Release();
                            pPin = NULL;
                            pPinConnected->Release();
                            pPinConnected = NULL;
                            break;
                        }
      
                        pPin->Release();
                        pPin = NULL;
                        hr = pEnum->Next(1, &pPin, NULL);
                    }// while
                    pEnum->Release();
                    pEnum = NULL;
                    if( false == bPinConnected )
                    {
                        pUnk->Release();
                        if(m_Fg){ m_Fg->Release(); m_Fg = NULL;}
                        if(m_Wc){ m_Wc->Release(); m_Wc = NULL;}
                        if(m_Gb){ m_Gb->Release(); m_Gb = NULL;}
                        return VFW_E_NOT_CONNECTED;
                    }
                }

            }
        }

        hres = pUnk->QueryInterface(IID_IMediaControl, (LPVOID *)&m_Mc);
        if(FAILED(hres))
        {
            pUnk->Release();
            m_Fg->Release(); m_Fg = NULL;
            m_Wc->Release(); m_Wc = NULL;
            m_Gb->Release(); m_Gb = NULL;
            return hres;
        }

        //
        // Not being able to get the IMediaEvent interface does not
        // necessarly mean that we can't play the graph.
        //
        pUnk->QueryInterface(IID_IMediaEvent, (LPVOID *)&m_Me);
        pUnk->QueryInterface(IID_IMediaSeeking, (LPVOID *)&m_Ms);

        GetMovieEventHandle();
        GetPerformanceInterfaces();

        pUnk->Release();
        return S_OK;

    }
    else
    {
        m_Fg = NULL;
    }

    return hres;
}


/******************************Public*Routine******************************\
* CloseMovie
*
\**************************************************************************/
DWORD
CMovie::CloseMovie(
    )
{
    m_Mode = MOVIE_NOTOPENED;

    if(m_Mc)
    {
        if(pMpegAudioDecoder)
        {
            pMpegAudioDecoder->Release();
            pMpegAudioDecoder = NULL;
        }

        if(pVideoRenderer)
        {
            pVideoRenderer->Release();
            pVideoRenderer = NULL;
        }

        if(m_Me)
        {
            m_MediaEvent = NULL;
            m_Me->Release();
            m_Me = NULL;
        }

        if(m_Ms)
        {
            m_Ms->Release();
            m_Ms = NULL;
        }

        if(m_Wc)
        {
            m_Wc->Release();
            m_Wc = NULL;
        }

        m_Mc->Release();
        m_Mc = NULL;

        if(m_SAN)
        {
            m_SAN->Release();
            m_SAN = NULL;
        }

        if(m_Gb)
        {
            m_Gb->Release();
            m_Gb = NULL;
        }

        if(m_Fg)
        {
            m_Fg->Release();
            m_Fg = NULL;
        }
    }

    delete m_lpBltAlpha;

    RELEASE(m_lpDDObj);
    RELEASE(m_lpPriSurf);
    RELEASE(m_lpBackBuffer);
    RELEASE(m_lpDDTexture);
    RELEASE(m_lpDDAppImage);

    if(m_hFont)
    {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }

    RELEASE(m_lpDDSFontCache);

    QzUninitialize();
    return 0L;
}


/******************************Public*Routine******************************\
* CMovie::GetNativeMovieSize
*
\**************************************************************************/
BOOL
CMovie::GetNativeMovieSize(
    LONG *pcx,
    LONG *pcy
    )
{
    BOOL    bRet = FALSE;
    if(m_Wc)
    {
        bRet = (m_Wc->GetNativeVideoSize(pcx, pcy, NULL, NULL) == S_OK);
    }

    return bRet;
}


/******************************Public*Routine******************************\
* GetMoviePosition
*
\**************************************************************************/
BOOL
CMovie::GetMoviePosition(
    LONG *px,
    LONG *py,
    LONG *pcx,
    LONG *pcy
    )
{
    BOOL    bRet = FALSE;

    if(m_Wc)
    {
        RECT src={0}, dest={0};
        HRESULT hr = m_Wc->GetVideoPosition(&src, &dest);
        *px = dest.left;
        *py = dest.right;
        *pcx = dest.right - dest.left;
        *pcy = dest.bottom - dest.top;
    }

    return bRet;
}

/******************************Public*Routine******************************\
* PutMoviePosition
*
\**************************************************************************/
BOOL
CMovie::PutMoviePosition(
    LONG x,
    LONG y,
    LONG cx,
    LONG cy
    )
{
    BOOL    bRet = TRUE;

    RECT rc;
    SetRect(&rc, x, y, x + cx, y + cy);

    if(m_bRndLess)
    {
        CAutoLock Lock(&m_AppImageLock);
        MapWindowRect(m_hwndApp, HWND_DESKTOP, &rc);
        m_rcDst = rc;
        CreateFontCache(HEIGHT(&m_rcDst) / GRID_CY);
    }
    else
    {
        if(m_Wc)
        {
            bRet = (m_Wc->SetVideoPosition(NULL, &rc) == S_OK);
        }
    }

    return bRet;
}


/******************************Public*Routine******************************\
* PlayMovie
*
\**************************************************************************/
BOOL
CMovie::PlayMovie(
    )
{
    REFTIME rt;
    REFTIME rtAbs;
    REFTIME rtDur;

    rt = GetCurrentPosition();
    rtDur = GetDuration();

    //
    // If we are near the end of the movie seek to the start, otherwise
    // stay where we are.
    //
    rtAbs = rt - rtDur;
    if(rtAbs < (REFTIME)0)
    {
        rtAbs = -rtAbs;
    }

    if(rtAbs < (REFTIME)1)
    {
        SeekToPosition((REFTIME)0,FALSE);
    }

    //
    // Change mode after setting m_Mode but before starting the graph
    //
    m_Mode = MOVIE_PLAYING;

    //
    // Start playing from the begining of the movie
    //
    m_Mc->Run();
    return TRUE;
}


/******************************Public*Routine******************************\
* PauseMovie
*
\**************************************************************************/
BOOL
CMovie::PauseMovie(
    )
{
    m_Mode = MOVIE_PAUSED;
    m_Mc->Pause();
    return TRUE;
}


/******************************Public*Routine******************************\
* GetStateMovie
*
\**************************************************************************/

OAFilterState
CMovie::GetStateMovie(
    )
{
    OAFilterState State;
    m_Mc->GetState(INFINITE,&State);
    return State;
}


/******************************Public*Routine******************************\
* StopMovie
*
\**************************************************************************/
BOOL
CMovie::StopMovie()
{
    m_Mode = MOVIE_STOPPED;
    m_Mc->Stop();
    return TRUE;
}


/******************************Public*Routine******************************\
* StatusMovie
*
\**************************************************************************/
EMovieMode
CMovie::StatusMovie()
{
    if(m_Mc)
    {
        FILTER_STATE    fs;
        HRESULT         hr;

        hr = m_Mc->GetState(100, (OAFilterState *)&fs);

        // Don't know what the state is so just stay at old state.
        if(hr == VFW_S_STATE_INTERMEDIATE)
        {
            return m_Mode;
        }

        switch(fs)
        {
            case State_Stopped:
                m_Mode = MOVIE_STOPPED;
                break;

            case State_Paused:
                m_Mode = MOVIE_PAUSED;
                break;

            case State_Running:
                m_Mode = MOVIE_PLAYING;
                break;
        }
    }

    return m_Mode;
}


/******************************Public*Routine******************************\
* CanMovieFrameStep
*
\**************************************************************************/
BOOL
CMovie::CanMovieFrameStep()
{
    IVideoFrameStep* lpFS;
    HRESULT hr;

    hr = m_Fg->QueryInterface(__uuidof(IVideoFrameStep), (LPVOID *)&lpFS);
    if(SUCCEEDED(hr))
    {
        hr = lpFS->CanStep(0L, NULL);
        lpFS->Release();
    }

    return SUCCEEDED(hr);
}


/******************************Public*Routine******************************\
* FrameStepMovie
*
\**************************************************************************/
BOOL
CMovie::FrameStepMovie()
{
    IVideoFrameStep* lpFS;
    HRESULT hr;

    hr = m_Fg->QueryInterface(__uuidof(IVideoFrameStep), (LPVOID *)&lpFS);
    if(SUCCEEDED(hr))
    {
        FrameStepCount++;

        hr = lpFS->Step(1, NULL);
        lpFS->Release();
    }

    return SUCCEEDED(hr);
}


/******************************Public*Routine******************************\
* GetMediaEventHandle
*
* Returns the IMediaEvent event hamdle for the filter graph iff the
* filter graph exists.
*
\**************************************************************************/
HANDLE
CMovie::GetMovieEventHandle()
{
    HRESULT     hr;

    if(m_Me != NULL)
    {
        if(m_MediaEvent == NULL)
        {
            hr = m_Me->GetEventHandle((OAEVENT *)&m_MediaEvent);
        }
    }
    else
    {
        m_MediaEvent = NULL;
    }

    return m_MediaEvent;
}


/******************************Public*Routine******************************\
* GetMovieEventCode
*
\**************************************************************************/
long
CMovie::GetMovieEventCode()
{
    HRESULT hr;
    long    lEventCode;
    LONG_PTR    lParam1, lParam2;

    if(m_Me != NULL)
    {
        hr = m_Me->GetEvent(&lEventCode, &lParam1, &lParam2, 0);
        if(SUCCEEDED(hr))
        {
            hr = m_Me->FreeEventParams(lEventCode, lParam1, lParam2);
            return lEventCode;
        }
    }

    return 0L;
}


/******************************Public*Routine******************************\
* GetDuration
*
* Returns the duration of the current movie
*
\**************************************************************************/
REFTIME
CMovie::GetDuration()
{
    HRESULT hr;
    LONGLONG Duration;

    if(m_TimeFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = m_Ms->GetDuration(&Duration);
        if(SUCCEEDED(hr))
        {
            return double(Duration);
        }
    }
    else if(m_Ms != NULL)
    {
        hr = m_Ms->GetDuration(&Duration);
        if(SUCCEEDED(hr))
        {
            return double(Duration) / UNITS;
        }
    }

    return 0;
}


/******************************Public*Routine******************************\
* GetCurrentPosition
*
* Returns the position of the current movie
*
\**************************************************************************/
REFTIME
CMovie::GetCurrentPosition()
{
    REFTIME rt = (REFTIME)0;
    HRESULT hr;
    LONGLONG Position;

    // Should we return a media position

    if(m_TimeFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = m_Ms->GetPositions(&Position, NULL);
        if(SUCCEEDED(hr))
        {
            return double(Position);
        }
    }
    else if(m_Ms != NULL)
    {
        hr = m_Ms->GetPositions(&Position, NULL);
        if(SUCCEEDED(hr))
        {
            return double(Position) / UNITS;
        }
    }

    return rt;
}


/*****************************Private*Routine******************************\
* SeekToPosition
*
\**************************************************************************/
BOOL
CMovie::SeekToPosition(
    REFTIME rt,
    BOOL bFlushData
    )
{
    HRESULT hr=S_OK;
    LONGLONG llTime = LONGLONG(m_TimeFormat == TIME_FORMAT_MEDIA_TIME ? rt * double(UNITS) : rt );

    if(m_Ms != NULL)
    {
        FILTER_STATE fs;
        m_Mc->GetState(100, (OAFilterState *)&fs);

        hr = m_Ms->SetPositions(&llTime, AM_SEEKING_AbsolutePositioning, NULL, 0);

        // This gets new data through to the renderers
        if(fs == State_Stopped && bFlushData)
        {
            m_Mc->Pause();
            hr = m_Mc->GetState(INFINITE, (OAFilterState *)&fs);
            m_Mc->Stop();
        }

        if(SUCCEEDED(hr))
        {
            return TRUE;
        }
    }
    return FALSE;
}


/*****************************Private*Routine******************************\
* GetPerformanceInterfaces
*
\**************************************************************************/
void
CMovie::GetPerformanceInterfaces(
    )
{
    FindInterfaceFromFilterGraph(IID_IMpegAudioDecoder, (LPVOID *)&pMpegAudioDecoder);
    FindInterfaceFromFilterGraph(IID_IQualProp, (LPVOID *)&pVideoRenderer);
}


HRESULT
CMovie::FindInterfaceFromFilterGraph(
    REFIID iid, // interface to look for
    LPVOID *lp  // place to return interface pointer in
    )
{
    IEnumFilters* pEF;
    IBaseFilter*  pFilter;

    // Grab an enumerator for the filter graph.
    HRESULT hr = m_Fg->EnumFilters(&pEF);

    if(FAILED(hr))
    {
        return hr;
    }

    // Check out each filter.
    while(pEF->Next(1, &pFilter, NULL) == S_OK)
    {
        hr = pFilter->QueryInterface(iid, lp);
        pFilter->Release();

        if(SUCCEEDED(hr))
        {
            break;
        }
    }

    pEF->Release();

    return hr;
}


/*****************************Public*Routine******************************\
* IsTimeFormatSupported
*
\**************************************************************************/
BOOL
CMovie::IsTimeFormatSupported(GUID Format)
{
    return m_Ms != NULL && m_Ms->IsFormatSupported(&Format) == S_OK;
}


/*****************************Public*Routine******************************\
* IsTimeSupported
*
\**************************************************************************/
BOOL
CMovie::IsTimeSupported()
{
    return m_Ms != NULL && m_Ms->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME) == S_OK;
}


/*****************************Public*Routine******************************\
* GetTimeFormat
*
\**************************************************************************/
GUID
CMovie::GetTimeFormat()
{
    return m_TimeFormat;
}

/*****************************Public*Routine******************************\
* SetTimeFormat
*
\**************************************************************************/
BOOL
CMovie::SetTimeFormat(GUID Format)
{
    HRESULT hr = m_Ms->SetTimeFormat(&Format);
    if(SUCCEEDED(hr))
    {
        m_TimeFormat = Format;
    }
    return SUCCEEDED(hr);
}

/******************************Public*Routine******************************\
* SetFocus
*
\**************************************************************************/
void
CMovie::SetFocus()
{
    if(m_Fg)
    {
        // Tell the resource manager that we are being made active.  This
        // will then cause the sound to switch to us.  This is especially
        // important when playing audio only files as there is no other
        // playback window.
        IResourceManager* pResourceManager;

        HRESULT hr = m_Fg->QueryInterface(IID_IResourceManager, (void**)&pResourceManager);

        if(SUCCEEDED(hr))
        {
            IUnknown* pUnknown;

            hr = m_Fg->QueryInterface(IID_IUnknown, (void**)&pUnknown);

            if(SUCCEEDED(hr))
            {
                pResourceManager->SetFocus(pUnknown);
                pUnknown->Release();
            }

            pResourceManager->Release();
        }
    }
}


/******************************Public*Routine******************************\
* RepaintVideo
*
\**************************************************************************/
BOOL
CMovie::RepaintVideo(
    HWND hwnd,
    HDC hdc
    )
{
    BOOL bRet = FALSE;

    if(m_Wc)
    {
        bRet = (m_Wc->RepaintVideo(hwnd, hdc) == S_OK);
    }
    else if( m_bRndLess )
    {
        bRet = SUCCEEDED( PresentImage() );
    }

    return bRet;
}


/******************************Public*Routine******************************\
* DisplayModeChanged
*
\**************************************************************************/
void CMovie::DisplayModeChanged(void)
{
    // Inform the VMR that the display has changed (bit depth, resolution, etc.)
    if (m_Wc)
        m_Wc->DisplayModeChanged();
    else
    {
        // Close the current media file and inform the user
        VcdPlayerCloseCmd();
        
        MessageBox(NULL, TEXT("The display mode has changed.\r\n\r\n")
                   TEXT("Please reopen the file or select a new media file."), 
                   TEXT("TextPlayer - Display mode changed"), MB_OK | MB_ICONINFORMATION);
    }
}
