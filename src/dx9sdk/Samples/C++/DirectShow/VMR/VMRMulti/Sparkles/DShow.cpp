//-----------------------------------------------------------------------------
// File: DShow.cpp
//
// Desc: DirectShow sample code
/
//  Copyright (c) 1992-2002 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include <streams.h>
#include <amstream.h>
#include <olectl.h>
#include <initguid.h>

#include <ddraw.h>
#define D3D_OVERLOADS
#include <d3d.h>
#include "bltalpha.h"
#include "dshow.h"

HRESULT App_OneTimeSceneInit();
HRESULT App_InitDeviceObjects( HWND hWnd, LPDIRECT3DDEVICE7 pd3dDevice );
HRESULT App_FrameMove( LPDIRECT3DDEVICE7 pd3dDevice, FLOAT fTimeKey );
HRESULT App_Render( LPDIRECT3DDEVICE7 pd3dDevice );

// Setup data

const AMOVIESETUP_MEDIATYPE sudOpPinTypes =
{
    &MEDIATYPE_Video,       // Major type
    &MEDIASUBTYPE_NULL      // Minor type
};

const AMOVIESETUP_PIN sudOpPin =
{
    L"Output",              // Pin string name
    FALSE,                  // Is it rendered
    TRUE,                   // Is it an output
    FALSE,                  // Can we have none
    FALSE,                  // Can we have many
    &CLSID_NULL,            // Connects to filter
    NULL,                   // Connects to pin
    1,                      // Number of types
    &sudOpPinTypes };       // Pin details

const AMOVIESETUP_FILTER sudBallax =
{
    &CLSID_Sparkle,         // Filter CLSID
    L"VMR Sparkle",         // String name
    MERIT_DO_NOT_USE,       // Filter merit
    1,                      // Number pins
    &sudOpPin               // Pin details
};


// COM global table of objects in this dll

CFactoryTemplate g_Templates[] = {
  { L"VMR Ball"
  , &CLSID_Sparkle
  , CSparkle::CreateInstance
  , NULL
  , &sudBallax }
};
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);


//
// DllRegisterServer
//
// Exported entry points for registration and unregistration
//
STDAPI DllRegisterServer()
{
    return AMovieDllRegisterServer2( TRUE );

} // DllRegisterServer


//
// DllUnregisterServer
//
STDAPI DllUnregisterServer()
{
    return AMovieDllRegisterServer2( FALSE );

} // DllUnregisterServer


//
// CreateInstance
//
// The only allowed way to create Bouncing balls!
//
CUnknown * WINAPI CSparkle::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    CUnknown *punk = new CSparkle(lpunk, phr);
    if (punk == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//
// Constructor
//
// Initialise a CSparkleStream object so that we have a pin.
//
CSparkle::CSparkle(LPUNKNOWN lpunk, HRESULT *phr) :
    CSource(NAME("VMR Sparkle"), lpunk, CLSID_Sparkle)
{
    CAutoLock cAutoLock(&m_cStateLock);

    m_paStreams    = (CSourceStream **) new CSparkleStream*[1];
    if (m_paStreams == NULL) {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_paStreams[0] = new CSparkleStream(phr, this, L"A Bouncing Ball!");
    if (m_paStreams[0] == NULL) {
        *phr = E_OUTOFMEMORY;
        return;
    }

} // (Constructor)


//
// Constructor
//
CSparkleStream::CSparkleStream(HRESULT *phr,
                         CSparkle *pParent,
                         LPCWSTR pPinName) :
    CSourceStream(NAME("Bouncing Ball"),phr, pParent, pPinName),
    m_iImageWidth(640),
    m_iImageHeight(480),
    m_lpAlphaBlt(NULL),
    m_rSampleTime(0)
{
} // (Constructor)


//
// Destructor
//
CSparkleStream::~CSparkleStream()
{

} // (Destructor)


//
// FillBuffer
//
// Plots a ball into the supplied video buffer
//
HRESULT CSparkleStream::FillBuffer(IMediaSample *pms)
{
    AM_MEDIA_TYPE   *pmt;
    pms->GetMediaType(&pmt);
    if (pmt) {
        CMediaType cmt(*pmt);
        SetMediaType(&cmt);
    }

    //
    // Try for a VMR connection
    //

    IVMRSurface* lpVMRSurf;
    HRESULT hr = pms->QueryInterface(IID_IVMRSurface, (LPVOID*)&lpVMRSurf);

    if (SUCCEEDED(hr)) {
        LPDIRECTDRAWSURFACE7 lpDDSurf;
        hr = lpVMRSurf->GetSurface(&lpDDSurf);

        if (SUCCEEDED(hr)) {

            if (!m_lpAlphaBlt) {
                HRESULT hr = S_OK;
                m_lpAlphaBlt = new CAlphaBlt(lpDDSurf, m_iImageWidth, m_iImageHeight, &hr);
                App_OneTimeSceneInit();
                App_InitDeviceObjects(NULL, m_lpAlphaBlt->GetD3DDevice());
            }


            // Get the relative time, in seconds
            FLOAT fTime = timeGetTime() * 0.001f;

            // FrameMove (animate) the scene
            if( FAILED( App_FrameMove( m_lpAlphaBlt->GetD3DDevice(), fTime ) ) )
                return E_FAIL;

            //Render the scene
            if( FAILED( App_Render( m_lpAlphaBlt->GetD3DDevice() ) ) )
                return E_FAIL;


            lpDDSurf->Release();
        }

        lpVMRSurf->Release();
    }


    {
        // The current time is the sample's start
        REFERENCE_TIME rStart = m_rSampleTime;

        //m_rSampleTime += 500000;      // 20.00
          m_rSampleTime += 416667;      // 24.00
        //m_rSampleTime += 333667;      // 29.97
        //m_rSampleTime += 333333;      // 30,00
        //m_rSampleTime += 166833;      // 59.94
        //m_rSampleTime += 166667;      // 60,00
        //m_rSampleTime += 166113;      // 60.20

        pms->SetTime(&rStart, &m_rSampleTime);
    }

    pms->SetSyncPoint(TRUE);
    return NOERROR;

} // FillBuffer


//
// Notify
//
// Alter the repeat rate according to quality management messages sent from
// the downstream filter (often the renderer).  Wind it up or down according
// to the flooding level - also skip forward if we are notified of Late-ness
//
STDMETHODIMP CSparkleStream::Notify(IBaseFilter * pSender, Quality q)
{
    return NOERROR;

} // Notify


//
// GetMediaType
//
// I _prefer_ 5 formats - 8, 16 (*2), 24 or 32 bits per pixel
//
// Prefered types should be ordered by quality, zero as highest quality
// Therefore iPosition =
// 0    return a 32bit mediatype
// 1    return a 24bit mediatype
// 2    return 16bit RGB565
// 3    return a 16bit mediatype (rgb555)
// 4    return 8 bit palettised format
// (iPosition > 4 is invalid)
//
HRESULT CSparkleStream::GetMediaType(int iPosition, CMediaType *pmt)
{
    CAutoLock cAutoLock(m_pFilter->pStateLock());
    if (iPosition < 0) {
        return E_INVALIDARG;
    }

    // Have we run off the end of types

    if (iPosition > 1) {
        return VFW_S_NO_MORE_ITEMS;
    }

    VIDEOINFO *pvi = (VIDEOINFO *)pmt->AllocFormatBuffer(sizeof(VIDEOINFO));
    if (NULL == pvi) {
        return(E_OUTOFMEMORY);
    }
    ZeroMemory(pvi, sizeof(VIDEOINFO));

    switch (iPosition) {
        case 1: {   

            pvi->bmiHeader.biCompression = BI_BITFIELDS;
            pvi->bmiHeader.biBitCount    = 16;
            pvi->TrueColorInfo.dwBitMasks[2] = 0x000F;
            pvi->TrueColorInfo.dwBitMasks[1] = 0x00F0;
            pvi->TrueColorInfo.dwBitMasks[0] = 0x0F00;
            pmt->SetSubtype(&MEDIASUBTYPE_RGB16_D3D_DX7_RT);
            //pmt->SetSubtype(&MEDIASUBTYPE_ARGB4444_D3D_DX7_RT);
        }
        break;

        case 0: {   

            pvi->bmiHeader.biCompression = BI_RGB;
            pvi->bmiHeader.biBitCount    = 32;
            pvi->TrueColorInfo.dwBitMasks[2] = 0x000000FF;
            pvi->TrueColorInfo.dwBitMasks[1] = 0x0000FF00;
            pvi->TrueColorInfo.dwBitMasks[0] = 0x00FF0000;
            pmt->SetSubtype(&MEDIASUBTYPE_RGB32_D3D_DX7_RT);
            //pmt->SetSubtype(&MEDIASUBTYPE_ARGB32_D3D_DX7_RT);
        }
        break;

   }

    pvi->bmiHeader.biSize       = sizeof(BITMAPINFOHEADER);
    pvi->bmiHeader.biWidth      = m_iImageWidth;
    pvi->bmiHeader.biHeight     = m_iImageHeight;
    pvi->bmiHeader.biPlanes     = 1;
    pvi->bmiHeader.biSizeImage  = GetBitmapSize(&pvi->bmiHeader);
    pvi->bmiHeader.biClrImportant   = 0;

    SetRectEmpty(&(pvi->rcSource)); // we want the whole image area rendered.
    SetRectEmpty(&(pvi->rcTarget)); // no particular destination rectangle

    pmt->SetType(&MEDIATYPE_Video);
    pmt->SetFormatType(&FORMAT_VideoInfo);
    pmt->SetTemporalCompression(FALSE);
    pmt->SetSampleSize(pvi->bmiHeader.biSizeImage);

    return NOERROR;

} // GetMediaType


//
// CheckMediaType
//
// We will accept 8, 16, 24 or 32 bit video formats, in any
// image size that gives room to bounce.
// Returns E_INVALIDARG if the mediatype is not acceptable
//
HRESULT CSparkleStream::CheckMediaType(const CMediaType *pMediaType)
{
    CAutoLock cAutoLock(m_pFilter->pStateLock());

    if ((*(pMediaType->Type()) != MEDIATYPE_Video) ||  // we only output video!
         !(pMediaType->IsFixedSize()) ) {              // ...in fixed size samples
                return E_INVALIDARG;
    }

    // Check for the subtypes we support
    const GUID *SubType = pMediaType->Subtype();
    if ((*SubType != MEDIASUBTYPE_ARGB32_D3D_DX7_RT) &&
        (*SubType != MEDIASUBTYPE_ARGB4444_D3D_DX7_RT) &&
        (*SubType != MEDIASUBTYPE_RGB32_D3D_DX7_RT) &&
        (*SubType != MEDIASUBTYPE_RGB16_D3D_DX7_RT))
    {
        return E_INVALIDARG;
    }

    // Get the format area of the media type
    VIDEOINFO *pvi = (VIDEOINFO *) pMediaType->Format();

    if (pvi == NULL)
        return E_INVALIDARG;

    return S_OK;  // This format is acceptable.

} // CheckMediaType


//
// DecideBufferSize
//
// This will always be called after the format has been sucessfully
// negotiated. So we have a look at m_mt to see what size image we agreed.
// Then we can ask for buffers of the correct size to contain them.
//
HRESULT CSparkleStream::DecideBufferSize(IMemAllocator *pAlloc,ALLOCATOR_PROPERTIES *pProperties)
{
    CAutoLock cAutoLock(m_pFilter->pStateLock());

    ASSERT(pAlloc);
    ASSERT(pProperties);
    HRESULT hr = NOERROR;

    VIDEOINFO *pvi = (VIDEOINFO *) m_mt.Format();
    pProperties->cBuffers = 1;
    pProperties->cbBuffer = pvi->bmiHeader.biSizeImage;

    ASSERT(pProperties->cbBuffer);

    // Ask the allocator to reserve us some sample memory, NOTE the function
    // can succeed (that is return NOERROR) but still not have allocated the
    // memory that we requested, so we must check we got whatever we wanted

    ALLOCATOR_PROPERTIES Actual;
    hr = pAlloc->SetProperties(pProperties,&Actual);
    if (FAILED(hr)) {
        return hr;
    }

    // Is this allocator unsuitable

    if (Actual.cbBuffer < pProperties->cbBuffer) {
        return E_FAIL;
    }

    // Make sure that we have only 1 buffer (we erase the ball in the
    // old buffer to save having to zero a 200k+ buffer every time
    // we draw a frame)

    ASSERT( Actual.cBuffers == 1 );
    return NOERROR;

} // DecideBufferSize


//
// SetMediaType
//
// Called when a media type is agreed between filters
//
HRESULT CSparkleStream::SetMediaType(const CMediaType *pMediaType)
{
    CAutoLock cAutoLock(m_pFilter->pStateLock());

    // Pass the call up to my base class

    HRESULT hr = CSourceStream::SetMediaType(pMediaType);
    if (SUCCEEDED(hr)) {

        VIDEOINFO * pvi = (VIDEOINFO *) m_mt.Format();
        switch (pvi->bmiHeader.biBitCount) {

        case 16:    
        case 24:    
        case 32:    
            break;

        default:
            // We should never agree any other pixel sizes
            ASSERT("Tried to agree inappropriate format");
        }

        RECT rc = pvi->rcTarget;
        if (IsRectEmpty(&rc)) {
            SetRect(&rc, 0, 0,
                    pvi->bmiHeader.biWidth, 
                    abs(pvi->bmiHeader.biHeight));
        }

        return NOERROR;

    } else {
        return hr;
    }

} // SetMediaType


//
// OnThreadCreate
//
// As we go active reset the stream time to zero
//
HRESULT CSparkleStream::OnThreadCreate()
{
    m_rSampleTime = 0;
    return NOERROR;

} // OnThreadCreate



HRESULT CSparkleStream::DoBufferProcessingLoop(void)
{

    Command com;

    OnThreadStartPlay();

    do {
    while (!CheckRequest(&com)) {

        IMediaSample *pSample;

        HRESULT hr = GetDeliveryBuffer(&pSample,NULL,NULL, AM_GBF_NODDSURFACELOCK);
        if (FAILED(hr)) {
            Sleep(1);
            continue;   // go round again. Perhaps the error will go away
                        // or the allocator is decommited & we will be asked to
                        // exit soon.
        }

        // Virtual function user will override.
        hr = FillBuffer(pSample);

        if (hr == S_OK) {
            hr = Deliver(pSample);
            pSample->Release();

            // downstream filter returns S_FALSE if it wants us to
            // stop or an error if it's reporting an error.
            if(hr != S_OK)
            {
              DbgLog((LOG_TRACE, 2, TEXT("Deliver() returned %08x; stopping"), hr));
              return S_OK;
            }

        } else if (hr == S_FALSE) {
            // derived class wants us to stop pushing data
            pSample->Release();
            DeliverEndOfStream();
            return S_OK;

        } else {
            // derived class encountered an error
            pSample->Release();
            DbgLog((LOG_ERROR, 1, TEXT("Error %08lX from FillBuffer!!!"), hr));
            DeliverEndOfStream();
            m_pFilter->NotifyEvent(EC_ERRORABORT, hr, 0);
            return hr;
        }

            // all paths release the sample
    }

        // For all commands sent to us there must be a Reply call!

    if (com == CMD_RUN || com == CMD_PAUSE) {
        Reply(NOERROR);
    } else if (com != CMD_STOP) {
        Reply((DWORD) E_UNEXPECTED);
        DbgLog((LOG_ERROR, 1, TEXT("Unexpected command!!!")));
    }

    } while (com != CMD_STOP);

    return S_FALSE;
}

extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE hInstance, ULONG ulReason, LPVOID pv);
BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason, LPVOID pv)
{
    return DllEntryPoint(hInstance, ulReason, pv);
}
