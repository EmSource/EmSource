//------------------------------------------------------------------------------
// File: vcdplyer.cpp
//
// Desc: DirectShow sample code - VMR-based Cube video player
//
// Copyright (c) 1994-2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"

#include <commctrl.h>
#include <atlbase.h>
#include <stdarg.h>
#include <stdio.h>

const DWORD_PTR MY_USER_ID = 0x1234ACDE;

// Advertise the filter graphs created by this application for
// remote viewing by GraphEdit.
#define REGISTER_FILTERGRAPH



/******************************Public*Routine******************************\
* CMovie
*
* Constructors and destructors
*
\**************************************************************************/
CMovie::CMovie(HWND hwndApplication)
    : CUnknown(NAME("Allocator Presenter"), NULL),
      m_hwndApp(hwndApplication),
      m_bInitCube(false),
      m_pDDSTextureMirror(NULL),
      m_MediaEvent(NULL),
      m_Mode(MOVIE_NOTOPENED),
      m_Fg(NULL),
      m_Gb(NULL),
      m_Mc(NULL),
      m_Me(NULL),
      m_Wc(NULL),
      m_pBF(NULL),
      m_Ms(NULL),
      m_dwRegister(0),
      m_dwTexMirrorWidth(0),
      m_dwTexMirrorHeight(0)
{
    AddRef();
}

CMovie::~CMovie() 
{
}

/******************************Public*Routine******************************\
* NonDelegatingQueryInterface
*
\**************************************************************************/
STDMETHODIMP
CMovie::NonDelegatingQueryInterface(
    REFIID riid,
    void** ppv
    )
{
    if (riid == IID_IVMRImageCompositor) {
        return GetInterface((IVMRImageCompositor*)this, ppv);
    }

    return CUnknown::NonDelegatingQueryInterface(riid,ppv);
}


/*****************************Private*Routine******************************\
* SetRenderingMode
*
\**************************************************************************/
HRESULT
SetRenderingMode(
    IBaseFilter* pBaseFilter,
    VMRMode mode,
    int iNumStreams,
    IVMRImageCompositor* lpCompositor
    )
{
    CheckPointer(pBaseFilter,E_POINTER);
    
    IVMRFilterConfig* pConfig = NULL;
    HRESULT hr = S_OK;

    __try {

        CHECK_HR(hr = pBaseFilter->QueryInterface(IID_IVMRFilterConfig,
                                                  (LPVOID *)&pConfig));

        //
        // If you are pluging in a compositor you have to be in
        // mixing mode, that is, iNumStreams needs to be greater than 0.
        //
        if (lpCompositor && iNumStreams < 1) {
            iNumStreams = 1;
        }

        if (iNumStreams) {
            CHECK_HR(hr = pConfig->SetNumberOfStreams(iNumStreams));
        }

        if (lpCompositor) {
            CHECK_HR(hr = pConfig->SetImageCompositor(lpCompositor));
        }

        CHECK_HR(hr = pConfig->SetRenderingMode(mode));
    }
    __finally {
        RELEASE(pConfig);
    }

    return hr;
}


/*****************************Private*Routine******************************\
* AddVideoMixingRendererToFG()
*
\**************************************************************************/
HRESULT
CMovie::AddVideoMixingRendererToFG(DWORD dwStreams)
{
    HRESULT hRes = S_OK;

    __try {
        RELEASE( m_pBF );
        CHECK_HR(hRes = CoCreateInstance(CLSID_VideoMixingRenderer,
                                         NULL, CLSCTX_INPROC,IID_IBaseFilter,
                                         (LPVOID *)&m_pBF));

        CHECK_HR(hRes = m_Fg->AddFilter(m_pBF, L"Video Mixing Renderer"));
        CHECK_HR(hRes = SetRenderingMode(m_pBF, VMRMode_Windowless,
                                         dwStreams, (IVMRImageCompositor*)this));
 
        CHECK_HR(hRes = m_pBF->QueryInterface(IID_IVMRWindowlessControl, (LPVOID *)&m_Wc));
        CHECK_HR(hRes = m_Wc->SetVideoClippingWindow(m_hwndApp));

        // Don't use letterbox aspect ratio, since the sample is already
        // manipulating the video image by rendering on the 3D cube.
        CHECK_HR(hRes = m_Wc->SetAspectRatioMode(VMR_ARMODE_NONE));

    }
    __finally {
    }
    return hRes;
}

/*****************************Private*Routine******************************\
* GetNumberConnectedPins()
*
\**************************************************************************/
HRESULT 
CMovie::GetNumberConnectedPins( DWORD& number )
{
    if( m_pBF == NULL )
    {
        return E_FAIL;
    }
    number = 0;

    CComPtr<IEnumPins> pPE;
    HRESULT hr = m_pBF->EnumPins( & pPE );
    if( SUCCEEDED( hr ) )
    {
        hr = S_OK;
        CComPtr<IPin> pPin;
        while( hr == S_OK )
        {
            pPin = NULL;

            hr = pPE->Next( 1, &pPin, 0 );
            if( hr == S_OK )
            {
                CComPtr<IPin> pPinConnected;
                hr = pPin->ConnectedTo(& pPinConnected );
                if( SUCCEEDED( hr ) )
                {
                    if( pPinConnected != NULL )
                    {
                        number++;
                    }
                }
                else if( hr == VFW_E_NOT_CONNECTED ) // reset hr if the pPin is just telling us that
                {   //it's not connected.
                    hr = S_OK;
                }
            }
        }
    }
    return hr;
}



#ifdef REGISTER_FILTERGRAPH

HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
    IMoniker * pMoniker;
    IRunningObjectTable *pROT;

    if (FAILED(GetRunningObjectTable(0, &pROT))) {
        return E_FAIL;
    }
    WCHAR wsz[256];
    wsprintfW(wsz, L"FilterGraph %08p pid %08x\0", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());

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


void RemoveFromRot(DWORD pdwRegister)
{
    IRunningObjectTable *pROT;
    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
}

#endif


/******************************Public*Routine******************************\
* OpenMovie
*
\**************************************************************************/
HRESULT
CMovie::OpenMovie(
    TCHAR achFileName[][MAX_PATH],
    DWORD dwNumFiles
    )
{
    USES_CONVERSION;
    IUnknown        *pUnk = NULL;
    HRESULT         hres = S_OK;
    WCHAR           FileName[MAX_PATH];

    __try {
        CHECK_HR(hres = CoCreateInstance(CLSID_FilterGraph,
                                         NULL, CLSCTX_INPROC,
                                         IID_IUnknown, (LPVOID *)&pUnk));
        CHECK_HR(hres = pUnk->QueryInterface(IID_IFilterGraph, (LPVOID *)&m_Fg));
        CHECK_HR( hres = AddVideoMixingRendererToFG(4) );
        CHECK_HR(hres = pUnk->QueryInterface(IID_IGraphBuilder, (LPVOID *)&m_Gb));

#ifdef REGISTER_FILTERGRAPH
        AddToRot(m_Gb, &m_dwRegister);
#endif

        for (DWORD i = 0; i < dwNumFiles; i++)
        {
            wcsncpy(FileName, T2W(achFileName[i]), NUMELMS(FileName));
            CHECK_HR(hres = m_Gb->RenderFile(FileName, NULL));
        }

        DWORD numConnected;
        CHECK_HR( hres = GetNumberConnectedPins( numConnected ) );
        // we need all the files to be connected to the filter
        // if some of them did not connect it's a failure.
        if( numConnected != dwNumFiles )
        {
            hres = E_FAIL;
        }
        else
        {

            CHECK_HR(hres = pUnk->QueryInterface(IID_IMediaControl, (LPVOID *)&m_Mc));

            //
            // Not being able to get the IMediaEvent interface does
            // necessarly mean that we can't play the graph.
            //
            pUnk->QueryInterface(IID_IMediaEvent, (LPVOID *)&m_Me);
            GetMovieEventHandle();
            pUnk->QueryInterface(IID_IMediaSeeking, (LPVOID *)&m_Ms);
        
            // ok if we got to here w/o any problems we are good
            m_Mode = MOVIE_STOPPED;
        }
    }
    __finally {

        if (FAILED(hres)) {
            RELEASE(m_Ms);
            RELEASE(m_Me);
            RELEASE(m_Mc);
            RELEASE(m_Gb);
            RELEASE(m_Fg);
        }

        RELEASE(pUnk);
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

#ifdef REGISTER_FILTERGRAPH
    if (m_dwRegister)
    {
        RemoveFromRot(m_dwRegister);
        m_dwRegister = 0;
    }
#endif

    RELEASE(m_Ms);
    RELEASE(m_Mc);
    RELEASE(m_Me);
    RELEASE(m_Gb);
    RELEASE(m_Fg);
    RELEASE(m_Wc);        
    RELEASE(m_pBF);
    RELEASE(m_pDDSTextureMirror);

    return 0L;
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
    if (m_Wc) {
        bRet = (m_Wc->RepaintVideo(hwnd, hdc) == S_OK);
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
    if (m_Wc)
    {
        RECT rc;
        SetRect(&rc, x, y, x + cx, y + cy);
        BOOL bRet = (m_Wc->SetVideoPosition(NULL, &rc) == S_OK);

        return bRet;
    }
    else
        return FALSE;
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
    if (rtAbs < (REFTIME)0) {
        rtAbs = -rtAbs;
    }

    if (rtAbs <= (REFTIME)1) {
        SeekToPosition((REFTIME)0,FALSE);
    }

    //
    // Change mode after setting m_Mode but before starting the graph
    //
    m_Mode = MOVIE_PLAYING;
    HRESULT hr = m_Mc->Run();
    ASSERT(SUCCEEDED(hr));
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

    HRESULT hr = m_Mc->Pause();
    ASSERT(SUCCEEDED(hr));

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

    HRESULT hr = m_Mc->GetState(INFINITE,&State);
    ASSERT(SUCCEEDED(hr));

    return State;
}

/******************************Public*Routine******************************\
* GetMovieMode
*
\**************************************************************************/
EMovieMode
CMovie::GetMovieMode()
{
    return m_Mode;
}



/******************************Public*Routine******************************\
* StopMovie
*
\**************************************************************************/
BOOL
CMovie::StopMovie(
    )
{
    HRESULT hr = S_OK;
    OAFilterState state;

    m_Mode = MOVIE_STOPPED;

    hr = m_Mc->Stop();
    ASSERT(SUCCEEDED(hr));

    m_Mc->GetState( 100, &state);
    while( state != State_Stopped )
    {
        Sleep(10);
        m_Mc->GetState( 100, &state);
    }


    return TRUE;
}


/******************************Public*Routine******************************\
* GetMediaEventHandle
*
* Returns the IMediaEvent event hamdle for the filter graph iff the
* filter graph exists.
*
\**************************************************************************/
HANDLE
CMovie::GetMovieEventHandle(
    )
{
    HRESULT hr;

    if (m_Me != NULL) {

        if ( m_MediaEvent == NULL) {
            hr = m_Me->GetEventHandle((OAEVENT *)&m_MediaEvent);
        }
    }
    else {
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

    if (m_Me != NULL) 
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

    // Should we seek using IMediaSelection

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


/******************************Public*Routine******************************\
* GetCurrentPosition
*
* Returns the duration of the current movie
*
\**************************************************************************/
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
    LONGLONG llTime =
        LONGLONG(m_TimeFormat == TIME_FORMAT_MEDIA_TIME ? rt * double(UNITS) : rt);

    if (m_Ms != NULL) {

        FILTER_STATE fs;
        hr = m_Mc->GetState(100, (OAFilterState *)&fs);

        hr = m_Ms->SetPositions(&llTime, AM_SEEKING_AbsolutePositioning, NULL, 0);

        // This gets new data through to the renderers
        if (fs == State_Stopped && bFlushData){
            hr = m_Mc->Pause();
            hr = m_Mc->GetState(INFINITE, (OAFilterState *)&fs);
            hr = m_Mc->Stop();
        }

        if (SUCCEEDED(hr)) {
            return TRUE;
        }
    }
    return FALSE;
}


