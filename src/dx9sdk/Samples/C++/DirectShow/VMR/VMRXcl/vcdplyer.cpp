//----------------------------------------------------------------------------
//  File:   vcdplyer.cpp
//
//  Desc:   DirectShow sample code
//          Implementation of CMovie, a customized video player
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "project.h"

#include <stdarg.h>

#define MY_USER_ID 0x1234ACDE


//----------------------------------------------------------------------------
// CMovie
//
// Constructors and destructors
//
//----------------------------------------------------------------------------
CMovie::CMovie(HWND hwndApplication)
    : CUnknown(NAME("Allocator Presenter"), NULL),
      m_Mode(MOVIE_NOTOPENED),
      m_MediaEvent(NULL),
      m_hwndApp(hwndApplication),
      m_iDuration(-1),
      m_TimeFormat(TIME_FORMAT_MEDIA_TIME),
      m_AlphaBlt(NULL),
      m_lpSurf(NULL),
      m_pBF(NULL),
      m_Fg(NULL),
      m_Gb(NULL),
      m_Mc(NULL),
      m_Ms(NULL),
      m_Me(NULL),
      m_Qp(NULL),
      m_lpDefSA(NULL),
      m_lpDefSAN(NULL),
      m_lpDefIP(NULL),
      m_lpDefWC(NULL)
{
    AddRef();
}

CMovie::~CMovie() 
{
}

//----------------------------------------------------------------------------
// SetRenderingMode
//
// Set rendering mode of VMR (Windowless, Windowed, Renderless)
//----------------------------------------------------------------------------
HRESULT
SetRenderingMode(
    IBaseFilter* pBaseFilter,
    VMRMode mode
    )
{
    IVMRFilterConfig* pConfig;
    HRESULT hr = pBaseFilter->QueryInterface(__uuidof(IVMRFilterConfig),
                                             (LPVOID *)&pConfig);

    if( SUCCEEDED( hr )) {
        pConfig->SetRenderingMode( mode );
        pConfig->SetNumberOfStreams(2);
        pConfig->Release();
    }

    return hr;
}


//----------------------------------------------------------------------------
// AddVideoMixingRendererToFG()
//
// creates and adds VMR to the graph
//----------------------------------------------------------------------------
#define CHECK_HRES(expr) if (FAILED(expr)) {           \
    OutputDebugString( hresultNameLookup(expr));       \
    OutputDebugString( TEXT("\n"));                    \
    DbgLog((LOG_ERROR, 0,                              \
            TEXT("FAILED: %s\nat Line:%d of %s\n"),    \
            TEXT(#expr), __LINE__, TEXT(__FILE__) ));  \
            goto cleanup;}


HRESULT
CMovie::AddVideoMixingRendererToFG( TCHAR *achErrorMsg, UINT uintLen )
{
    HRESULT hRes = S_OK;
    m_AlphaBlt = NULL;

    CHECK_HRES(hRes = m_pDDObject.Initialize(m_hwndApp, achErrorMsg, uintLen ));

    CHECK_HRES(hRes = CoCreateInstance(CLSID_VideoMixingRenderer,
                                       NULL, CLSCTX_INPROC,IID_IBaseFilter,
                                       (LPVOID *)&m_pBF));

    CHECK_HRES(hRes = m_Fg->AddFilter(m_pBF, L"Video Mixing Renderer VMRXcl"));

    CHECK_HRES(hRes = SetRenderingMode(m_pBF, VMRMode_Renderless));

    CHECK_HRES(hRes = m_pBF->QueryInterface(__uuidof(IVMRSurfaceAllocatorNotify),
                            (LPVOID *)&m_lpDefSAN));

    m_AlphaBlt = new CAlphaBlt(m_pDDObject.GetBB(), &hRes);
    CHECK_HRES(hRes);

    CHECK_HRES(hRes = CreateDefaultAllocatorPresenter(m_pDDObject.GetDDObj(),
                                                    m_pDDObject.GetBB()));

    CHECK_HRES(hRes = m_lpDefSAN->AdviseSurfaceAllocator(MY_USER_ID, this));

cleanup:
    if (FAILED(hRes)) 
    {
        delete m_AlphaBlt;
        m_AlphaBlt= NULL;

        m_pDDObject.Terminate();
        RELEASE(m_pBF);
    }

    return hRes;
}


//----------------------------------------------------------------------------
// OpenMovie
//
// creates the graph, adds VMR, QIs relevant interfaces and renders the file
//----------------------------------------------------------------------------
HRESULT
CMovie::OpenMovie(
    TCHAR *lpFileName,
    TCHAR *achErrorMsg,
    UINT uintLen
    )
{
    USES_CONVERSION;
    IUnknown *pUnk = NULL;
    HRESULT  hres = S_OK;
    WCHAR    wszFileName[MAX_PATH];
    IObjectWithSite* pObjWithSite = NULL;

    wcsncpy(wszFileName, T2W(lpFileName), NUMELMS(wszFileName));

    __try {

        //
        // First check to see if the file can be rendered
        // Because we must add the VMR to the filter graph before 
        // calling RenderFile(), and because the add method also
        // configures a custom allocator-presenter with Direct3D
        // surfaces, notifications, etc., it is much easier to 
        // clean things up on RenderFile() failure if we haven't
        // yet instanciated the VMR.
        //
        // If RenderFile() fails here, we can exit gracefully.
        //
        CHECK_HR(hres = CoCreateInstance(CLSID_FilterGraph,
                                         NULL, CLSCTX_INPROC,
                                         IID_IUnknown, (LPVOID *)&pUnk));

        CHECK_HR(hres = pUnk->QueryInterface(IID_IGraphBuilder, (LPVOID *)&m_Gb));

        hres = m_Gb->RenderFile(wszFileName, NULL);
        if (FAILED(hres))
        {
            __leave;
        }

        // File rendered OK.  Tear down the graph and destroy interfaces.
        RELEASE(m_Gb);
        RELEASE(pUnk);

        //
        // Start over with a fresh playback graph 
        // (now that we know that the requested media file is valid)
        //
        CHECK_HR(hres = CoCreateInstance(CLSID_FilterGraph,
                                         NULL, CLSCTX_INPROC,
                                         IID_IUnknown, (LPVOID *)&pUnk));

        // Now do the exclusive mode setup with the VMR
        m_Mode = MOVIE_OPENED;

        CHECK_HR(hres = pUnk->QueryInterface(IID_IFilterGraph,  (LPVOID *)&m_Fg));
        CHECK_HR(hres = pUnk->QueryInterface(IID_IGraphBuilder, (LPVOID *)&m_Gb));
        CHECK_HR(hres = pUnk->QueryInterface(IID_IMediaControl, (LPVOID *)&m_Mc));
        CHECK_HR(hres = pUnk->QueryInterface(IID_IMediaSeeking, (LPVOID *)&m_Ms));

        // Hook verifier to the filter graph to prevent unwanted Video Renderers
        // and have control over whether graph utilizes our customized VMR
        CHECK_HR(hres = m_Fg->QueryInterface(IID_IObjectWithSite, (LPVOID*)&pObjWithSite));
        CHECK_HR(hres = pObjWithSite->SetSite( (IAMGraphBuilderCallback*)this ));

        // Build the graph
        CHECK_HR(hres = AddVideoMixingRendererToFG(achErrorMsg,uintLen));
        CHECK_HR(hres = m_Gb->RenderFile(wszFileName, NULL));

        // if we managed to build the graph, we do not need verifier anymore
        CHECK_HR(hres = pObjWithSite->SetSite( NULL));
        RELEASE(pObjWithSite);

        CHECK_HR(hres = m_pBF->QueryInterface(IID_IQualProp, (LPVOID *)&m_Qp));

        //
        // Not being able to get the IMediaEvent interface does
        // necessarly mean that we can't play the graph.
        //
        HRESULT hr = pUnk->QueryInterface(IID_IMediaEvent, (LPVOID *)&m_Me);
        GetMovieEventHandle();

    }
    __finally {

        if (FAILED(hres)) {
            RELEASE(m_Ms);
            RELEASE(m_Me);
            RELEASE(m_Mc);
            RELEASE(m_Qp);
            RELEASE(m_Gb);
            RELEASE(m_Fg);
            RELEASE(pObjWithSite);

            m_pDDObject.Terminate();
        }

        RELEASE(pUnk);
    }

    return hres;
}


//----------------------------------------------------------------------------
//  CloseMovie
//
//  Releases client-provided allocator-presenter, exits sxclusive mode
//----------------------------------------------------------------------------
DWORD
CMovie::CloseMovie(
    )
{
    m_Mode = MOVIE_NOTOPENED;

    RELEASE(m_Qp);
    RELEASE(m_Mc);
    RELEASE(m_Me);
    RELEASE(m_Ms);
    RELEASE(m_Gb);
    RELEASE(m_Fg);

    if (m_lpDefSAN) {
        m_lpDefSAN->AdviseSurfaceAllocator(0, NULL);
        RELEASE(m_lpDefSAN);
    }

    RELEASE(m_pBF);
    RELEASE(m_lpDefWC);
    RELEASE(m_lpDefSA);

    RELEASE(m_lpDefIP);

    delete m_AlphaBlt;
    m_pDDObject.Terminate();

    return 0L;
}


//----------------------------------------------------------------------------
// RepaintVideo
//----------------------------------------------------------------------------
BOOL
CMovie::RepaintVideo(
    HWND hwnd,
    HDC hdc
    )
{
    BOOL bRet = FALSE;
    if (m_lpDefWC) {
        bRet = (m_lpDefWC->RepaintVideo(hwnd, hdc) == S_OK);
    }

    return bRet;
}


//----------------------------------------------------------------------------
// PutMoviePosition
//----------------------------------------------------------------------------
BOOL
CMovie::PutMoviePosition(
    LONG x,
    LONG y,
    LONG cx,
    LONG cy
    )
{
    HRESULT hr;
    BOOL bRet = FALSE;

    if (m_lpDefWC) {
        RECT rc;
        SetRect(&rc, x, y, x + cx, y + cy);
        hr = m_lpDefWC->SetVideoPosition(NULL, &rc);
        bRet = (hr == S_OK);
    }

    return bRet;
}


//----------------------------------------------------------------------------
//  PlayMovie
//
//  Just runs IMediaControl
//
//----------------------------------------------------------------------------
BOOL
CMovie::PlayMovie()
{
    REFTIME rt;
    REFTIME rtDur;

    rt = GetCurrentPosition();
    rtDur = GetDuration();

    //
    // Change mode after setting m_Mode but before starting the graph
    //
    ::ShowWindow( m_hwndApp, SW_SHOW);
    ::UpdateWindow( m_hwndApp );
    Sleep( 1000);

    m_Mode = MOVIE_PLAYING;
    HRESULT hr = m_Mc->Run();
    return TRUE;
}


//----------------------------------------------------------------------------
// PauseMovie
//
//
//----------------------------------------------------------------------------
BOOL
CMovie::PauseMovie()
{
    m_Mode = MOVIE_PAUSED;
    if (m_Mc)
        m_Mc->Pause();

    return TRUE;
}


//----------------------------------------------------------------------------
// GetStateMovie
//
// returns state of the media control (running, paused, or stopped)
//----------------------------------------------------------------------------

OAFilterState
CMovie::GetStateMovie()
{
    OAFilterState State=0;
    if (m_Mc)
        m_Mc->GetState(100,&State);

    return State;
}


//----------------------------------------------------------------------------
// StopMovie
//
//----------------------------------------------------------------------------
BOOL
CMovie::StopMovie()
{
    m_Mode = MOVIE_STOPPED;
    if (m_Mc)
        m_Mc->Stop();

    return TRUE;
}


//----------------------------------------------------------------------------
// GetMediaEventHandle
//
// Returns the IMediaEvent event handle for the filter graph iff the
// filter graph exists.
//
//----------------------------------------------------------------------------
HANDLE
CMovie::GetMovieEventHandle()
{
    HRESULT     hr = S_OK;

    if (m_Me != NULL) 
    {
        if ( m_MediaEvent == NULL)
            hr = m_Me->GetEventHandle((OAEVENT *)&m_MediaEvent);
    }
    else 
    {
        m_MediaEvent = NULL;
    }

    return m_MediaEvent;
}


//----------------------------------------------------------------------------
// GetMovieEventCode
//
// Retrieves notification events from the graph through IMediaEvent interface
//----------------------------------------------------------------------------
long
CMovie::GetMovieEventCode()
{
    HRESULT hr;
    long    lEventCode;
    LONG_PTR    lParam1, lParam2;

    if (m_Me != NULL) {
        hr = m_Me->GetEvent(&lEventCode, &lParam1, &lParam2, 0);
        if (SUCCEEDED(hr)) {
            return lEventCode;
        }
    }

    return 0L;
}


//----------------------------------------------------------------------------
// GetDuration
//
// Returns the duration of the current movie
// NOTE that time format may vary with different media types
//
//----------------------------------------------------------------------------
REFTIME
CMovie::GetDuration()
{
    HRESULT hr;
    LONGLONG Duration;

    if (m_Ms != NULL && m_TimeFormat != TIME_FORMAT_MEDIA_TIME) {
        hr = m_Ms->GetDuration(&Duration);
        if (SUCCEEDED(hr)) {
            return double(Duration);
        }
    } else if (m_Ms != NULL) {
        hr = m_Ms->GetDuration(&Duration);
        if (SUCCEEDED(hr)) {
            return double(Duration) / UNITS;
        }
    }

    return 0;
}


//----------------------------------------------------------------------------
// GetCurrentPosition
//
// Returns the duration of the current movie
// NOTE that time format may vary with different media types
//
//----------------------------------------------------------------------------
REFTIME
CMovie::GetCurrentPosition()
{
    REFTIME rt = (REFTIME)0;
    HRESULT hr;
    LONGLONG Position;

    // Should we return a media position

    if (m_Ms != NULL && m_TimeFormat != TIME_FORMAT_MEDIA_TIME) {
        hr = m_Ms->GetPositions(&Position, NULL);
        if (SUCCEEDED(hr)) {
            return double(Position);
        }
    } else if (m_Ms != NULL) {
        hr = m_Ms->GetPositions(&Position, NULL);
        if (SUCCEEDED(hr)) {
            return double(Position) / UNITS;
        }
    }

    return rt;
}


//----------------------------------------------------------------------------
// SeekToPosition
//
// NOTE that time format may vary with different media types
//
//----------------------------------------------------------------------------
BOOL
CMovie::SeekToPosition(
    REFTIME rt,
    BOOL bFlushData
    )
{
    HRESULT hr=S_OK;
    LONGLONG llTime =
        LONGLONG(m_TimeFormat == TIME_FORMAT_MEDIA_TIME ? rt * double(UNITS) : rt);

    if (m_Ms != NULL) {

        FILTER_STATE fs;
        m_Mc->GetState(100, (OAFilterState *)&fs);

        hr = m_Ms->SetPositions(&llTime, AM_SEEKING_AbsolutePositioning, NULL, 0);

        // This gets new data through to the renderers

        if (fs == State_Stopped && bFlushData){
            m_Mc->Pause();
            hr = m_Mc->GetState(INFINITE, (OAFilterState *)&fs);
            m_Mc->Stop();
        }

        if (SUCCEEDED(hr)) {
            return TRUE;
        }
    }

    return FALSE;
}


