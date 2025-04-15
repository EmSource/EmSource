//------------------------------------------------------------------------------
// File: RenderEngine.cpp
//
// Desc: DirectShow sample code - Implementation of CMultiVMR9RenderEngine
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "RenderEngine.h"
#include <d3dx9.h>

/******************************Public*Routine******************************\
* CMultiVMR9RenderEngine
*
* constructor
\**************************************************************************/
CMultiVMR9RenderEngine::CMultiVMR9RenderEngine(LPUNKNOWN pUnk, HRESULT *phr)
    : CUnknown(NAME("MultiVMR9 Render Engine"), pUnk)
    , m_hwnd( NULL )
    , m_pDevice( NULL)
    , m_pUILayer( NULL )
    , m_pMixerControl( NULL )
    , m_pOwner( NULL )
    , m_pRenderTarget( NULL )
    , m_bInitialized( FALSE )
    , m_Timer( NULL )
    , m_setFPS( 100000 )
    , m_getFPS( 0 )
    , m_interframe( 33)
    , m_interframeInstant( 0L )
    , m_dwFramesDrawn( 0)
    , m_dwStart(0)
    , m_dwLastRender( 0)
{
    // make sure timer is at least 2 ms accurate
    timeBeginPeriod(2);
}

/******************************Public*Routine******************************\
* CMultiVMR9RenderEngine
*
* destructor
\**************************************************************************/
CMultiVMR9RenderEngine::~CMultiVMR9RenderEngine()
{
    HRESULT hr = S_OK;
    CAutoLock Lock(&m_ObjectLock);

    // here we have to disconnect child IMultiVMR9UILayer and IMultiVMR9MixerControl
    if( m_pUILayer )
    {
        hr = m_pUILayer->SetRenderEngineOwner( NULL);
        if( FAILED(hr))
        {
            ::DbgMsg("~CMultiVMR9RenderEngine: failed to disconnect child UILayer, he = 0x%08x", hr);
        }
    }
    if( m_pMixerControl )
    {
        hr = m_pMixerControl->SetRenderEngineOwner(NULL);
        if( FAILED(hr))
        {
            ::DbgMsg("~CMultiVMR9RenderEngine: failed to disconnect child mixer control, he = 0x%08x", hr);
        }
    }
    
    Clean_();
    // call off the timer
    timeEndPeriod(2);
}

///////////////////////// IUnknown /////////////////////////////////////////

/******************************Public*Routine******************************\
* CreateInstance
\**************************************************************************/
CUnknown* CMultiVMR9RenderEngine::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
    return new CMultiVMR9RenderEngine(pUnk, phr);
}

/******************************Public*Routine******************************\
* NonDelegatingQueryInterface
\**************************************************************************/
STDMETHODIMP
CMultiVMR9RenderEngine::NonDelegatingQueryInterface(
    REFIID riid,
    void ** ppv)
{
    HRESULT hr = E_NOINTERFACE;
    *ppv = NULL;

    if (riid == IID_IMultiVMR9RenderEngine) 
    {
        hr = GetInterface((IMultiVMR9RenderEngine *)this, ppv);
    }
    else 
    {
        hr = CUnknown::NonDelegatingQueryInterface(riid,ppv);
    }
    return hr;
}


///////////////////////// IMultiVMR9RenderEngine //////////////////////////////

/******************************Public*Routine******************************\
* Initialize
*
* Call this method right after IMultiVMR9Wizard object is created to configure 
* and initialize internal structures as well as D3D environment.
*
* hWnd  - handle to valid video window
* dwFlags - Configuration flags
* lViewWidth - desired width of the view port. If <=0, render engine will use
*              default backbuffer width
* lVieweHeight - desired height of the view port. if <=0, render engine 
*                will use default value of backbuffer height
* pMixerControl - customized IMultiVMR9MixerControl, use NULL for the default
* pUILayer - customized IMultiVMR9UILayer, use NULL if there is no UI layer
*
* Return error codes: E_INVALIDARG (invalid config flags or hWnd), 
*                     VFW_E_WRONG_STATE (method was already called before)
*                     E_FAIL (unexpected error), 
* 
\**************************************************************************/

STDMETHODIMP CMultiVMR9RenderEngine::Initialize(
    HWND hWnd, 
    DWORD dwFlags,
    IMultiVMR9MixerControl* pMixerControl,
    IMultiVMR9UILayer* pUILayer
    )
{
    HRESULT hr = S_OK;
    D3DPRESENT_PARAMETERS pp;
    IDirect3D9*     pD3D9 = NULL;

    if( FALSE == IsWindow( hWnd ))
    {
        ::DbgMsg("CMultiVMR9RenderEngine::Initialize: received invalid window handle");
        return E_INVALIDARG;
    }

    if( m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::Initialize: method was already called");
        return VFW_E_WRONG_STATE;
    }

    CAutoLock Lock(&m_ObjectLock);

    try
    {
        m_hwnd = hWnd;

        // TODO: check flags
        m_dwCfgFlags = dwFlags;

        if( pMixerControl )
        {
            m_pMixerControl = pMixerControl;
            m_pMixerControl->AddRef();

        }
        else // create default mixer control
        {
            CHECK_HR(
                hr = CoCreateInstance(  CLSID_MultiVMR9MixerControl, 
                                        NULL, CLSCTX_INPROC_SERVER,
                                        IID_IMultiVMR9MixerControl, 
                                        (void**)&m_pMixerControl),
                ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed to create default MultiVMR9MixerControl, "\
                    "hr = 0x%08x", hr));
        }
        CHECK_HR(
            m_pMixerControl->SetRenderEngineOwner( this ),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed to advise 'this' owner to the mixer control"));

        if( pUILayer )
        {
            m_pUILayer = pUILayer;
            m_pUILayer->AddRef();
            CHECK_HR(
                m_pUILayer->SetRenderEngineOwner( this ),
                ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed to advise 'this' owner to the UI layer"));
        }

        // create Direct3D
        pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

        CHECK_HR( 
            pD3D9 ? S_OK : E_FAIL,
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed to create Direct3D9 object"));

        // create device
        D3DFORMAT D3DFormatAlternatives[] = 
                    {
                        D3DFMT_X8R8G8B8,
                        D3DFMT_R5G6B5,
                        D3DFMT_A8B8G8R8,
                        D3DFMT_X4R4G4B4,
                        D3DFMT_A4R4G4B4,
                        D3DFMT_A1R5G5B5,
                        D3DFMT_X1R5G5B5,
                    };

        int nD3DFormatAlternatives = sizeof(D3DFormatAlternatives) / sizeof(D3DFORMAT);

        // try different alternatives
        for( int nFmt = 0; nFmt < nD3DFormatAlternatives; nFmt++)
        {
            D3DFORMAT fmt = D3DFormatAlternatives[ nFmt ];

            ZeroMemory( &pp, sizeof(D3DPRESENT_PARAMETERS));
            pp.Windowed = TRUE;
            pp.hDeviceWindow = m_hwnd;
            pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
            pp.BackBufferCount = 1;
            pp.BackBufferFormat = fmt;
            pp.EnableAutoDepthStencil = TRUE;
            pp.AutoDepthStencilFormat = D3DFMT_D16;
            pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
            pp.PresentationInterval = 0x80000000;

            
            hr = pD3D9->CreateDevice(D3DADAPTER_DEFAULT ,
                                    D3DDEVTYPE_HAL,
                                    m_hwnd,
                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                    &pp,
                                    &m_pDevice);
            if( SUCCEEDED(hr) && m_pDevice )
                break;
        }// for

        hr = m_pDevice ? S_OK : hr;
        CHECK_HR(
            hr,
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed to create device, error code 0x%08x", hr));

        //maximum ambient light
        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_AMBIENT,RGB(255,255,255)),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_AMBIENT...)"));

        //lighting disabled
        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_LIGHTING,FALSE),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_LIGHTING...)"));

        //don't cull backside
        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_CULLMODE...)"));

        //DISABLE depth buffering
        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_FALSE),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_ZENABLE...)"));

        // enable dithering
        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_DITHERENABLE...)"));

        // disable stensil
        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_STENCILENABLE...)"));

        // manage blending
        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_ALPHABLENDENABLE...)"));

        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_SRCBLEND...)"));

        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_DESTBLEND...)"));

        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_ALPHATESTENABLE...)"));

        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x10),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_ALPHAREF...)"));

        CHECK_HR(
            m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetRenderState(D3DRS_ALPHAFUNC...)"));

        // set up sampler

        CHECK_HR(
            m_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetSamplerState(D3DSAMP_ADDRESSU...)"));

        CHECK_HR(
            m_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetSamplerState(D3DSAMP_ADDRESSV...)"));

        CHECK_HR(
            m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetSamplerState(D3DSAMP_MAGFILTER...)"));

        CHECK_HR(
            m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed in SetSamplerState(D3DSAMP_MINFILTER...)"));

        CHECK_HR(
            hr = m_pMixerControl->Initialize( m_pDevice ),
            ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed to initialize mixer control, hr = 0x%08x", hr));

        if( m_pUILayer )
        {
            CHECK_HR(
                hr = m_pUILayer->Initialize( m_pDevice ),
                ::DbgMsg("CMultiVMR9RenderEngine::Initialize: failed to initialize UI Layer, hr = 0x%08x", hr));
        }

        m_bInitialized = TRUE;
    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    RELEASE( pD3D9 );
    return hr;
}

/******************************Public*Routine******************************\
* Terminate
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::Terminate( void )
{
    HRESULT hr = S_OK;
    if( m_pMixerControl )
    {
        hr = m_pMixerControl->SetRenderEngineOwner(NULL);
        if( FAILED(hr))
        {
            ::DbgMsg("CMultiVMR9RenderEngine::Terminate: failed to unadvise RenderEngineOwner for mixer control, hr = 0x%08x", hr);
            return hr;
        }
        RELEASE( m_pMixerControl );
    }

    if( m_pUILayer )
    {
        hr = m_pUILayer->SetRenderEngineOwner(NULL);
        if( FAILED(hr))
        {
            ::DbgMsg("CMultiVMR9RenderEngine::Terminate: failed to unadvise RenderEngineOwner for UI layer, hr = 0x%08x", hr);
            return hr;
        }
        RELEASE( m_pUILayer );
    }
    return S_OK;
}

/******************************Public*Routine******************************\
* Render
*
* This method is called from a separate thread asynchronously from VMR calls
* First, method checks internal timer, and if it is time to render new scene,
* method calls mixer control's methods Compose() and Render(). After that, if 
* UI layer is present, we also call for its Render() method. We also keep track on
* actual FPS rate here
*
* Return error codes: E_INVALIDARG (invalid config flags or hWnd), 
*                     VFW_E_WRONG_STATE (method was already called before)
*                     E_FAIL (unexpected error), 
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::Render(void)
{
    HRESULT hr = S_OK;
    HRESULT hrMC = S_OK;
    HRESULT hrUI = S_OK;
    COLORREF clr = RGB(0,0,0);
    D3DCOLOR backgroundColor;

    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::Render: object is not initialized");
        return VFW_E_WRONG_STATE;
    }

    DWORD dwCurTime = timeGetTime();

    if( 0 == m_dwStart )
    {
        m_dwStart = timeGetTime();
    }

    if( dwCurTime - (m_dwStart + m_Timer) < m_interframe )
    {
        return S_OK; // to early to do anything
    }

    // time is up: render
    CAutoLock Lock(&m_ObjectLock);

    m_interframeInstant = dwCurTime - (m_dwStart + m_Timer);
    
    m_Timer = dwCurTime - m_dwStart;

    if( !m_pMixerControl )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::Render: FATAL, cannot find IMultiVMR9MixerControl");
        return E_UNEXPECTED;
    }

    hr = m_pMixerControl->GetBackgroundColor( &clr );

    if( FAILED(hr))
    {
        backgroundColor = D3DCOLOR_XRGB( 0x00, 0x00, 0x00);
    }
    else
    {
        backgroundColor = D3DCOLOR_XRGB( GetRValue( clr), GetGValue( clr), GetBValue( clr));
    }

    try
    {
        hr = m_pMixerControl->Compose( (void*)m_Timer );
        if( FAILED(hr))
        {
            ::DbgMsg("CMultiVMR9RenderEngine::Render: failed in IMultiVMR9MixerControl::Compose, hr = 0x%08x", hr);
            return hr;
        }

        // render the scene
        CHECK_HR(
            hr = m_pDevice->Clear(  0L,                             // no rects (clear all)
                                    NULL,                           // clear entire viewport
                                    D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,// clear render target
                                    backgroundColor,
                                    1.0f,                           // clear all the depth
                                    0L ),                           // no stencil
            ::DbgMsg("CMultiVMR9RenderEngine::Render: failed in IDirect3DDevice9::Clear, hr = 0x%08x", hr));

        CHECK_HR(
            hr = m_pDevice->BeginScene(),
            ::DbgMsg("CMultiVMR9RenderEngine::Render: failed in BeginScene(), hr = 0x%08x",hr));

        // first, render all the video source by means of mixer control
        hrMC = m_pMixerControl->Render( m_pDevice, (void*)m_Timer );

        if( m_pUILayer )
        {
            hrUI = m_pUILayer->Render( m_pDevice );
        }
        
        CHECK_HR(
            hr = m_pDevice->EndScene(),
            ::DbgMsg("CMultiVMR9RenderEngine::Render: failed in EndScene(), hr = 0x%08x",hr));

        CHECK_HR(
            hr = m_pDevice->Present(NULL,NULL,NULL,NULL),
            ::DbgMsg("CMultiVMR9RenderEngine::Render: failed in IDirect3DDevice9::Present(), hr = 0x%08x",hr));

        if( FAILED( hrMC ))
        {
            ::DbgMsg("CMultiVMR9RenderEngine::Render: failed in IMultiVMR9MixerControl::Render, error code 0x%08x", hrMC);
            hr = hrMC;
        }
        if( FAILED( hrUI ))
        {
            ::DbgMsg("CMultiVMR9RenderEngine::Render: failed in IMultiVMR9UILayer::Render, error code 0x%08x", hrUI);
            hr = FAILED(hr) ? hrUI : hr;
        }

        m_dwFramesDrawn++;
        if( m_dwFramesDrawn == ULONG_MAX ) // we have been running renderer for sooo long
        {
            // flush counters
            m_dwFramesDrawn = 0;
        }

        if( m_dwFramesDrawn > 1 )
        {
            m_interframeAvg = m_interframeAvg *(m_dwFramesDrawn-1) + (m_Timer - m_dwLastRender);
            m_interframeAvg /= m_dwFramesDrawn;
        }
        else
        {
            m_interframeAvg = m_interframeInstant;
        }

    } // try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    m_dwLastRender = m_Timer;

    return hr;
}

/******************************Public*Routine******************************\
* GetUILayer
*
* Call this method to obtain pointer to currently used UI layer. 
* if there is no UI Layer involved, method returns *ppUILayer = NULL;
*
* Return error codes: E_POINTER (ppUILayer is NULL)
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::GetUILayer(IMultiVMR9UILayer** ppUILayer)
{
    HRESULT hr = S_OK;

    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetUILayer: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    if( !ppUILayer )
    {
        return E_POINTER;
    }
    if( m_pUILayer )
    {
        *ppUILayer = m_pUILayer;
        (*ppUILayer)->AddRef();
    }
    else
    {
        *ppUILayer = NULL;
    }

    return hr;
}

/******************************Public*Routine******************************\
* SetFrameRate
*
* Call this method to specify desired frame rate, in (frames per sec)x100
* Render engine will try to keep desired rate, but does not guarantee it,
* use GetFrameRate() to get actual frame rate
*
* Return error codes: E_INVALIDARG (nFramesPerSecBy100 is less than 1 or bigger than 100000)
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::SetFrameRate(int nFramesPerSecBy100)
{
    HRESULT hr = S_OK;
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::SetFrameRate: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    if( nFramesPerSecBy100 <1 ||
        nFramesPerSecBy100 >100000 )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::SetFrameRate: desired rate must be between 1 and 100000");
        return E_INVALIDARG;
    }

    CAutoLock Lock(&m_ObjectLock);
    m_setFPS = nFramesPerSecBy100;
    // update m_interframe which is inverse of FPS
    m_interframe = 100000 / m_setFPS;

    // we also have to flush counters for actual FPS
    m_interframeAvg = m_interframe;

    return hr;
}

/******************************Public*Routine******************************\
* GetFrameRate
*
* Call this method to obtain actual frame rate (instanteneous from the last rendering),
* in (frames per sec)x100. Once started, renderer stops only when destroyed 
* (and if all the subgraphs are idle, it will be drawing last available images), 
*
* Return error codes: E_POINTER (pnFramesPerSecBy100 is NULL)
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::GetFrameRate(int* pnFramesPerSecBy100)
{
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetFrameRate: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    if( !pnFramesPerSecBy100 )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetFrameRate: received NULL pointer");
        return E_POINTER;
    }
    if( m_interframeInstant )
    {
        m_getFPS = 100000L / m_interframeInstant;
    }
    else
    {
        m_getFPS = 0L;
    }

    *pnFramesPerSecBy100 = m_getFPS;
    return S_OK;
}

/******************************Public*Routine******************************\
* GetFrameRateAvg
*
* Call this method to obtain actual frame rate, smoothed and averaged in time, 
* in (frames per sec)x100. Once started, renderer stops only when destroyed 
* (and if all the subgraphs are idle, it will be drawing last available images), 
* so we calculate actual frame rate as
* 
* InterFrameTime_ms = (InterFrameTime_ms *(FramesDrawn-1) + (time_from_the_last_rendering_ms)) / FramesDrawn;
* FrameRateAvg = 100000 / InterFrameTime_ms;
*
* Actual calculations are performed in Render().
*
* Return error codes: E_POINTER (pnFramesPerSecBy100 is NULL)
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::GetFrameRateAvg( int* pnFramesPerSecBy100 )
{
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetFrameRate: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    if( !pnFramesPerSecBy100 )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetFrameRate: received NULL pointer");
        return E_POINTER;
    }
    if( m_interframeAvg )
    {
        *pnFramesPerSecBy100 = 100000L / m_interframeAvg;
    }
    else
    {
        *pnFramesPerSecBy100 = 0L;
    }
    return S_OK;
}

/******************************Public*Routine******************************\
* GetMixingPrefs
*
* Call this method to obtain flags with which this render engine was initialized
*
* Return error codes: E_POINTER (pdwPrefs is NULL)
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::GetMixingPrefs(DWORD* pdwPrefs)
{
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetMixingPrefs: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    if( !pdwPrefs )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetMixingPrefs: received NULL pointer");
        return E_POINTER;
    }

    *pdwPrefs = m_dwCfgFlags;
    return S_OK;
}

/******************************Public*Routine******************************\
* SetWizardOwner
*
* This method is called by IMultiVMR9Wizard when it takes 'this' as a render engine
*
* Return error codes: 
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::SetWizardOwner(IMultiVMR9Wizard* pWizard)
{
    HRESULT hr = S_OK;
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::SetWizardOwner: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    CAutoLock Lock(&m_ObjectLock);

    RELEASE( m_pOwner );

    if( pWizard )
    {
        m_pOwner = pWizard;
        m_pOwner->AddRef();
    }

    return hr;
}

/******************************Public*Routine******************************\
* GetWizardOwner
*
* Call this method to obtain pointer to IMultiVMR9Wizard that owns 
* 'this' as a render engine
*
* Return error codes: E_POINTER ( ppWizard is NULL )
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::GetWizardOwner(IMultiVMR9Wizard** ppWizard)
{
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetWizardOwner: object is not initialized");
        return VFW_E_WRONG_STATE;
    }

    if( !ppWizard )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetWizardOwner: received NULL pointer");
        return E_POINTER;
    }

    if( m_pOwner )
    {
        *ppWizard = m_pOwner;
        (*ppWizard)->AddRef();
    }
    else
    {
        *ppWizard = NULL;
    }
    return S_OK;
}

/******************************Public*Routine******************************\
* GetMixerControl
*
* Call this method to obtain pointer to IMultiVMR9MixerControl that is used by
* 'this' render engine. Mixer Control is advised in Initialize() method.
*
* Return error codes: E_POINTER ( ppMixerControl is NULL )
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::GetMixerControl(IMultiVMR9MixerControl** ppMixerControl)
{
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetMixerControl: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    if( !ppMixerControl )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetMixerControl: received NULL pointer");
        return E_POINTER;
    }
    if( m_pMixerControl )
    {
        *ppMixerControl = m_pMixerControl;
        (*ppMixerControl)->AddRef();
    }
    else
    {
        *ppMixerControl = NULL;
    }

    return S_OK;
}

/******************************Public*Routine******************************\
* Get3DDevice
*
* Call this method to obtain Direct3DDevice9 used for rendering.
* This device is created by 'Initialize()' method
*
* Return error codes: E_POINTER ( ppDevice is NULL )
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::Get3DDevice(IDirect3DDevice9 ** ppDevice)
{
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::Get3DDevice: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    if( !ppDevice )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::Get3DDevice: received NULL pointer");
        return E_POINTER;
    }
    if( m_pDevice )
    {
        *ppDevice = m_pDevice;
        (*ppDevice)->AddRef();
    }
    else
    {
        *ppDevice = NULL;
    }

    return S_OK;
}

/******************************Public*Routine******************************\
* GetVideoWindow
*
* Call this method to obtain handle to the video window. 
* This handle is sent to 'Initialize()' method
*
* Return error codes: E_POINTER ( phwnd is NULL )
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
\**************************************************************************/
STDMETHODIMP CMultiVMR9RenderEngine::GetVideoWindow(HWND *phwnd)
{
    if( FALSE == m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetVideoWindow: object is not initialized");
        return VFW_E_WRONG_STATE;
    }
    if( !phwnd )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::GetVideoWindow: received NULL pointer");
        return E_POINTER;
    }

    *phwnd = m_hwnd;
    return S_OK;
}

/////////////////////// Private routine ///////////////////////////////////////

/******************************Private*Routine******************************\
* Clean_
*
* clean all the data, release all interfaces
\**************************************************************************/
void CMultiVMR9RenderEngine::Clean_()
{
    if( m_pOwner ) { m_pOwner->Release(); m_pOwner = NULL; }
    if( m_pMixerControl ) { m_pMixerControl->Release(); m_pMixerControl = NULL; }
    if( m_pUILayer ){ m_pUILayer->Release(); m_pUILayer = NULL; }
    if( m_pDevice ){ m_pDevice->Release(); m_pDevice = NULL; }
    if( m_pRenderTarget ){ m_pRenderTarget->Release(); m_pRenderTarget = NULL;}
}
