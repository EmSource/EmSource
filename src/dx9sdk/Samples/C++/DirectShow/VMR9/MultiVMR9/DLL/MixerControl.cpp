//------------------------------------------------------------------------------
// File: MixerControl.cpp
//
// Desc: DirectShow sample code - Implementation of CMultiVMR9MixerControl
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MixerControl.h"

#include <math.h>

/******************************Public*Routine******************************\
* CMultiVMR9MixerControl
*
* constructor
\**************************************************************************/
CMultiVMR9MixerControl::CMultiVMR9MixerControl(LPUNKNOWN pUnk, HRESULT *phr)
    : CUnknown(NAME("MultiVMR9 Mixer Control"), pUnk)
    , m_pOwner( NULL )
    , m_FVF( MultiVMR9Mixer_DefaultFVF )
    , m_BackgroundColor( RGB(0x00, 0x00, 0x00))
    , m_bInitialized( FALSE )
{
}

/******************************Public*Routine******************************\
* ~CMultiVMR9MixerControl
*
* destructor
\**************************************************************************/
CMultiVMR9MixerControl::~CMultiVMR9MixerControl()
{
    CAutoLock Lock(&m_ObjectLock);
    Clean_();
}

///////////////////////// IUnknown /////////////////////////////////////////

/******************************Public*Routine******************************\
* CreateInstance
\**************************************************************************/
CUnknown* CMultiVMR9MixerControl::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
    return new CMultiVMR9MixerControl(pUnk, phr);
}

/******************************Public*Routine******************************\
* NonDelegatingQueryInterface
\**************************************************************************/
STDMETHODIMP
CMultiVMR9MixerControl::NonDelegatingQueryInterface(
    REFIID riid,
    void ** ppv)
{
    HRESULT hr = E_NOINTERFACE;
    *ppv = NULL;

    if (riid == IID_IMultiVMR9MixerControl) 
    {
        hr = GetInterface((IMultiVMR9MixerControl *)this, ppv);
    }
    else 
    {
        hr = CUnknown::NonDelegatingQueryInterface(riid,ppv);
    }
    return hr;
}


///////////////////////// IMultiVMR9MixerControl ///////////////////////////////

/******************************Public*Routine******************************\
* SetRenderEngineOwner
*
* This method is called by IMultiVMR9RenderEngine  during initialization,
* sets IMultiVMR9RenderEngine object that manages this mixer control
*
* pRenderEngine - render engine
*
* Return error codes: none
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::SetRenderEngineOwner(
    IMultiVMR9RenderEngine* pRenderEngine)
{
    CAutoLock Lock(&m_ObjectLock);

    RELEASE( m_pOwner );

    if( pRenderEngine )
    {
        m_pOwner = pRenderEngine;
        m_pOwner->AddRef();
    }
    return S_OK;
}

/******************************Public*Routine******************************\
* GetRenderEngineOwner
*
* Call this method to obtain pointer to the IMultiVMR9RenderEngine that
* manages this mixer control
*
* ppRenderEngine - render engine
*
* Return error codes: E_POINTER (ppRenderEngine is NULL)
*                     VFW_E_NOT_FOUND (mixer control is not connected to any 
*                                        render engine)
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::GetRenderEngineOwner(
    IMultiVMR9RenderEngine** ppRenderEngine)
{
    if( !ppRenderEngine )
    {
        return E_POINTER;
    }
    if( !m_pOwner )
    {
        return VFW_E_NOT_FOUND;
    }

    *ppRenderEngine = m_pOwner;
    (*ppRenderEngine)->AddRef();

    return S_OK;
}

/******************************Public*Routine******************************\
* Initialize
*
* This method is called by the render engine when it creates Direct3D device
*
* pDevice - render engine
*
* Return error codes: E_POINTER (ppRenderEngine is NULL)
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::Initialize(
    IDirect3DDevice9 *pDevice)
{
    if( !pDevice )
    {
        return E_POINTER;
    }

    m_bInitialized = TRUE;
    return S_OK;
}

/******************************Public*Routine******************************\
* Compose
*
* This method allows to make necessary transformations of primitive's geometry
* (coordinates). Method is always called from IMultiVMR9RenderEngine::Render with 
* specified in the render engine frame rate. By default, lpParam is render engine's
* timer (time, in ms, since render engine started). You can use this timer for
* animation. You can also modify IMultiVMR9RenderEngine::Render to send here
* some other parameter.
*
* Here, in the default implementation of IMultiVMR9MixerControl, we expand
* IVMRMixerControl functionality on multi-graph environment, so we do not have
* to make any routing coordinate transformations (animation). So this method
* just copies frame vertices to correspondent vertex buffers
*
* lpParam - application specific parameter (timer of the render engine by default)
*
* Return error codes: S_FALSE (there were some errors during composing)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::Compose(void* lpParam)
{
    HRESULT hr = S_OK;
    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    // when overrriding this method, make sure you are thread safe
    CAutoLock Lock(&m_ObjectLock);

    return hr;
}

/******************************Public*Routine******************************\
* Render
*
* Method makes actual rendering of 3D primitives with applied textures that
* can be video sources. This method is always called from 
* IMultiVMR9RenderEngine::Render with specified in the render engine frame rate.  
* 
* Override this method to perform customized rendering.
* Please note, that when this method is called, render engine already made
* BeginScene() call to its Direct3D device. It will also call EndScene after
* Mixer control and UI layer (if present) finish their rendering.
* Do NOT call BeginScene() or EndScene() here!
*
* In the default implementation of the method, we go through primitives specified 
* by list of MultiVMR9_Frame in Z-order and draw rectangular primitives (coupled 
* triangle strip) one by one. Frame's coordinates and alpha level are already set
* in correspondent methods. By default, every frame occupies maximum area of the 
* back buffer and maintains aspect ratio, alpha level is 1; Z-order corresponds 
* to the order sources were connected to the wizard (last added will be on the front)
*
* pDevice - IDirect3DDevice9 from the render engine
* lpParam - application specific parameter (timer of the render engine by default,
*           as in Compose() above)
*
* Return error codes: S_FALSE (there were errors during rendering)
*                     E_POINTER (pDevice is NULL)
*                     E_UNEXPECTED (unexpected error)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::Render(IDirect3DDevice9 *pDevice, 
                                            void* lpParam)
{
    HRESULT hr = S_OK;
    HRESULT hrRen = S_OK;
    CMultiVMR9_Frame *pFrame = NULL;

    IMultiVMR9Wizard*   pHostWizard = NULL;
    IDirect3DTexture9*  pTexture    = NULL;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    if( !pDevice )
    {
        ::DbgMsg("CMultiVMR9MixerControl::Render: received NULL pointer");
        return E_POINTER;
    }

    if( !m_pOwner )
    {
        ::DbgMsg("CMultiVMR9MixerControl::Render: FATAL, cannot find IMultiVMR9RenderEngine owner");
        return E_UNEXPECTED;
    }

    CAutoLock Lock(&m_ObjectLock);

    try
    {
        CHECK_HR(
            hr = m_pOwner->GetWizardOwner( &pHostWizard ),
            ::DbgMsg("CMultiVMR9MixerControl::Render: FATAL, cannot find IMultiVMR9Wizard owner, "\
                "hr = 0x%08x, pWizard = 0x%08x", hr, pHostWizard));


        list<CMultiVMR9_Frame*>::iterator start, end, it;
        start = m_listFrames.begin();
        end = m_listFrames.end();

        for( it=start; it!=end; it++)
        {
            RELEASE( pTexture );
            pFrame = (CMultiVMR9_Frame*)(*it);

            CHECK_HR(
                hr = pHostWizard->GetTexture( pFrame->m_dwID, &pTexture ),
                ::DbgMsg("CMultiVMR9MixerControl::Render: cannot find the texture!, "\
                    "ID = 0x%08x, hr = 0x%08x, pTexture = 0x%08x",
                    pFrame->m_dwID,  hr, pTexture));

            CHECK_HR(
                hr = pDevice->SetTexture( 0, pTexture ),
                ::DbgMsg("CMultiVMR9MixerControl::Render: failed to set texture for "\
                    "ID = 0x%08x, hr = 0x%08x, pTexture = 0x%08x",
                    pFrame->m_dwID, hr, pTexture));

            CHECK_HR(
                hr = pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1),
                ::DbgMsg("CMultiVMR9MixerControl::Render: failed in SetTextureStageState(D3DTSS_ALPHAOP...), hr = 0x%08x", hr));

            CHECK_HR(
                hr = pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE),
                ::DbgMsg("CMultiVMR9MixerControl::Render: failed in SetTextureStageState(D3DTSS_ALPHAARG1...), hr = 0x%08x", hr));

            CHECK_HR(
                hr = pDevice->SetFVF(m_FVF),
                ::DbgMsg("CMultiVMR9MixerControl::Render: failed to set FVF "\
                    "ID = 0x%08x, hr = 0x%08x",
                    pFrame->m_dwID, hr));

            // draw the primitive
            CHECK_HR(
                hr = pDevice->DrawPrimitiveUP(  D3DPT_TRIANGLESTRIP,
                                                2,
                                                (LPVOID)(pFrame->m_coord),
                                                sizeof(pFrame->m_coord[0])),
                ::DbgMsg("CMultiVMR9MixerControl::Render: failed to DrawPrimitive "\
                    "ID = 0x%08x, hr = 0x%08x",
                    pFrame->m_dwID, hr));

            CHECK_HR(
                hr = pDevice->SetTexture( 0, NULL ),
                ::DbgMsg("CMultiVMR9MixerControl::Render: failed to SetTexture(0,NULL) "\
                    "ID = 0x%08x, hr = 0x%08x",
                    pFrame->m_dwID, hr));
        } // for all frames
    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    RELEASE( pTexture );
    RELEASE( pHostWizard );

    return hr;
}

/******************************Public*Routine******************************\
* AddVideoSource
*
* Upon this call, mixer control should allocate new primitive that
* will be used to draw the source.
* Override this method to use your own primitives. If you want to render something
* other than video sources, make a relevant modification of the render engine.
* 
* In the default implementation, MultiVMR9_Frame is used to describe the primitive.
* New frame is added to the end of the list and has least Z-order.
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     E_UNEXPECTED (unexpected error)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::AddVideoSource(
        DWORD_PTR dwID,
        LONG lImageWidth,
        LONG lImageHeight,
        LONG lTextureWidth,
        LONG lTextureHeight
        )
{
    HRESULT hr = S_OK;

    IMultiVMR9Wizard*   pHostWizard = NULL;
    IDirect3DDevice9*   pDevice     = NULL;
    IDirect3DSurface9*  pBackBuffer = NULL;

    CMultiVMR9_Frame *pFrame = NULL;

    LONG lRTWidth = 0L;
    LONG lRTHeight = 0L;

    D3DSURFACE_DESC ddsd;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    // sanity check
    if( !m_pOwner )
    {
        ::DbgMsg("CMultiVMR9MixerControl::AddVideoSource: FATAL, cannot find IMultiVMR9RenderEngine owner");
        return E_UNEXPECTED;
    }

    try
    {
        CHECK_HR(
            m_pOwner->GetWizardOwner( &pHostWizard ),
            ::DbgMsg("CMultiVMR9MixerControl::AddVideoSource: FATAL, cannot find IMultiVMR9Wizard owner"));

        CHECK_HR(
            m_pOwner->Get3DDevice( &pDevice ),
            ::DbgMsg("CMultiVMR9MixerControl::AddVideoSource: FATAL, cannot find IDirect3DDevice9"));

        CHECK_HR(
            hr = pDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer),
            ::DbgMsg("CMultiVMR9MixerControl::AddVideoSource: FATAL, cannot get back buffer, "\
                "hr = 0x%08x", hr));

        CHECK_HR(
            hr = pBackBuffer->GetDesc( &ddsd ),
            ::DbgMsg("CMultiVMR9MixerControl::AddVideoSource: FATAL, cannot get back buffer description"\
                "hr = 0x%08x", hr));

        lRTWidth = ddsd.Width;
        lRTHeight = ddsd.Height;

        // check if wizard knows about this dwID
        CHECK_HR(
            hr = pHostWizard->VerifyID( dwID ),
            ::DbgMsg("CMultiVMR9MixerControl::AddVideoSource: received invalid dwID (video source is not found), "\
                "hr = 0x%08x", hr));

        CAutoLock Lock(&m_ObjectLock);

        // ok, create new frame
        pFrame = new CMultiVMR9_Frame();

        CHECK_HR(
            ( !pFrame ) ? E_OUTOFMEMORY : S_OK,
            ::DbgMsg("CMultiVMR9MixerControl::AddVideoSource: memory allocation error"));

        CHECK_HR(
            hr = pFrame->Initialize(    dwID, 
                                        lImageWidth, 
                                        lImageHeight, 
                                        lRTWidth, 
                                        lRTHeight,
                                        lTextureWidth,
                                        lTextureHeight,
                                        1.f ),
            ::DbgMsg("CMultiVMR9MixerControl::AddVideoSource: failed in CMultiVMR9_Frame::Initialize, "\
                "hr = 0x%08x", hr));

        // now add the frame to the end of the list, incrementing Z-Order of already
        // existing frames

        list<CMultiVMR9_Frame*>::iterator start, end, it;

        start = m_listFrames.begin();
        end = m_listFrames.end();

        for( it=start; it!=end; it++)
        {
            (*it)->m_dwZOrder++;
        }
        pFrame->m_dwZOrder = 0;
        m_listFrames.push_back( pFrame );
    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
        if( pFrame )
        {
            delete pFrame;
            pFrame = NULL;
        }
    }

    RELEASE( pDevice );
    RELEASE( pHostWizard );
    RELEASE( pBackBuffer );
    return hr;
}

/******************************Public*Routine******************************\
* DeleteVideoSource
*
* Upon this call, mixer control should deletes correspondent primitive from
* the list
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     E_UNEXPECTED (unexpected error)
*                     VFW_E_WRONG_STATE(mixer was not initialized)  
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::DeleteVideoSource(
        DWORD_PTR dwID
        )
{
    HRESULT hr = S_OK;
    CMultiVMR9_Frame *pFrameDelete = NULL;
    CMultiVMR9_Frame *pFrame = NULL;
    int nCounter;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    // we do not have to check if this dwID is registered with the wizard, so
    // just go through the list and delete; decrease Z-order of all preceding frames
    list<CMultiVMR9_Frame*>::iterator start, end, it;
    start = m_listFrames.begin();
    end = m_listFrames.end();

    CAutoLock Lock(&m_ObjectLock);

    for( it=start; it!=end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( dwID == pFrame->m_dwID )
        {
            pFrameDelete = pFrame;
            break;
        }
    }

    if( !pFrameDelete ) // we did not find the frame
    {
        ::DbgMsg("CMultiVMR9MixerControl::DeleteVideoSource: cannot find frame for source 0x%08x", dwID);
        return VFW_E_NOT_FOUND;
    }

    m_listFrames.remove( pFrameDelete );
    
    start = m_listFrames.begin();
    end = m_listFrames.end();
    nCounter = m_listFrames.size()-1;

    for( it=start; it!=end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        pFrame->m_dwZOrder = (DWORD)nCounter;
        nCounter--;
    }

    delete pFrameDelete;
    pFrameDelete = NULL;
    return S_OK;
}

/******************************Public*Routine******************************\
* GetOutputRect
*
* Call this method to get output rectangle of a video source, in normalized coordinates
* with respect to the view area (which size can be obtained by 
* IMultiVMR9RenderEngine::GetViewPortSize()).
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
* lpNormRect -- receives output rect
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     E_POINTER (lpNormRect is NULL)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::GetOutputRect(     
    DWORD_PTR dwID,
    NORMALIZEDRECT* lpNormRect)
{
    CMultiVMR9_Frame *pFrameRequested = NULL;
    CMultiVMR9_Frame *pFrame = NULL;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    if( !lpNormRect )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetOutputRect: received NULL pointer");
        return E_POINTER;
    }
    list<CMultiVMR9_Frame*>::iterator start, end, it;

    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( dwID == pFrame->m_dwID )
        {
            pFrameRequested = pFrame;
            break;
        }
    }

    if( !pFrameRequested )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetOutputRect: requested video source 0x%08x was not found",
            dwID);
        return VFW_E_NOT_FOUND;
    }

    memcpy( (void*)lpNormRect, (void*)&(pFrame->m_nrDst), sizeof(NORMALIZEDRECT));
    return S_OK;
}

/******************************Public*Routine******************************\
* SetOutputRect
*
* Call this method to set output rectangle of a video source, in normalized coordinates
* with respect to the view area (which size can be obtained by 
* IMultiVMR9RenderEngine::GetViewPortSize()).
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
* lpNormRect -- specifies output rect
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     E_POINTER (lpNormRect is NULL)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::SetOutputRect(
    DWORD_PTR dwID,
    NORMALIZEDRECT* lpNormRect)
{
    HRESULT hr = S_OK;
    CMultiVMR9_Frame *pFrameRequested = NULL;
    CMultiVMR9_Frame *pFrame = NULL;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    if( !lpNormRect )
    {
        ::DbgMsg("CMultiVMR9MixerControl::SetOutputRect: received NULL pointer");
        return E_POINTER;
    }

    list<CMultiVMR9_Frame*>::iterator start, end, it;

    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( dwID == pFrame->m_dwID )
        {
            pFrameRequested = pFrame;
            break;
        }
    }

    if( !pFrameRequested )
    {
        ::DbgMsg("CMultiVMR9MixerControl::SetOutputRect: requested video source 0x%08x was not found",
            dwID);
        return VFW_E_NOT_FOUND;
    }

    CAutoLock Lock(&m_ObjectLock);

    hr = pFrame->UpdateDestination( *lpNormRect );
    if( FAILED(hr))
    {
        ::DbgMsg("CMultiVMR9MixerControl::SetOutputRect: failed in CMultiVMR9_Frame::UpdateDestination, "\
            "hr = 0x%08x", hr);
    }

    return hr;
}

/******************************Public*Routine******************************\
* GetIdealOutputRect
*
* Call this method to obtain an ideal normalized rectangle that takes 
* maximum space in screen coordinates of the area (dwWidth x dwHeight)
* and maintains video's aspect ratio
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
* dwWidth - width, in pixels, of the area where we want to fit the frame
* dwHeight - height, in pixels, of the area where we want to fit the frame
* lpNormRect -- [out] specifies ideal normalized output rect
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     E_POINTER (lpNormRect is NULL)
*                     E_INVALIDARG (dwWidth = 0, dwHeight=0)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::GetIdealOutputRect(
                                        DWORD_PTR dwID,
                                        DWORD dwWidth,
                                        DWORD dwHeight,
                                        NORMALIZEDRECT* lpNormRect
                                        )
{
    HRESULT hr = S_OK;
    CMultiVMR9_Frame *pFrameRequested = NULL;
    CMultiVMR9_Frame *pFrame = NULL;

    float ww; // width in window coord
    float wh; // height in window coord
    float nw; // width in normalized coord
    float nh; // height in normalized coord

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    if( !lpNormRect )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetIdealOutputRect: received NULL pointer");
        return E_POINTER;
    }
    if( 0 == dwWidth )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetIdealOutputRect: width of the area is 0");
        return E_INVALIDARG;
    }
    if( 0 == dwHeight )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetIdealOutputRect: width of the area is 0");
        return E_INVALIDARG;
    }

    list<CMultiVMR9_Frame*>::iterator start, end, it;

    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( dwID == pFrame->m_dwID )
        {
            pFrameRequested = pFrame;
            break;
        }
    }
    if( !pFrameRequested )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetIdealOutputRect: requested video source 0x%08x was not found",
            dwID);
        return VFW_E_NOT_FOUND;
    }

    if( 0.f == pFrameRequested->m_ar )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetIdealOutputRect: FATAL, aspect ratio of the source 0x%08x is 0.0",
            dwID);
        return E_UNEXPECTED;
    }
    // try fit horizontally
    ww = (float)dwWidth;
    wh = ww / ( pFrameRequested->m_ar );

    if( wh > (float)dwHeight ) // we do not fit vertically
    {
        wh = (float)dwHeight;
        ww = wh * ( pFrameRequested->m_ar );
    }

    // now map window coordinates to normalized coordinates
    nw = ww / (float)dwWidth;
    nh = wh / (float)dwHeight;

    // for further calculations we need half-width and half-height
    nw /= 2.f;
    nh /= 2.f;

    lpNormRect->left   = 0.5f - nw;
    lpNormRect->right  = 0.5f + nw;
    lpNormRect->top    = 0.5f - nh;
    lpNormRect->bottom = 0.5f + nh;

    return S_OK;
}


/******************************Public*Routine******************************\
* GetZOrder
*
* Call this method to get Z-Order of a video source, in normalized coordinates
* with respect to the view area (which size can be obtained by 
* IMultiVMR9RenderEngine::GetViewPortSize()).
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
* pdwZ -- receives Z-Order
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     E_POINTER (pdwZ is NULL)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::GetZOrder(DWORD_PTR dwID, DWORD *pdwZ)
{
    CMultiVMR9_Frame *pFrameRequested = NULL;
    CMultiVMR9_Frame *pFrame = NULL;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    if( !pdwZ )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetZOrder: received NULL pointer");
        return E_POINTER;
    }
    list<CMultiVMR9_Frame*>::iterator start, end, it;

    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( dwID == pFrame->m_dwID )
        {
            pFrameRequested = pFrame;
            break;
        }
    }
    if( !pFrameRequested )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetZOrder: requested video source 0x%08x was not found",
            dwID);
        return VFW_E_NOT_FOUND;
    }

    *pdwZ = pFrame->m_dwZOrder;
    return S_OK;
}

/******************************Public*Routine******************************\
* SetZOrder
*
* Call this method to get Z-Order of a video source, in normalized coordinates
* with respect to the view area (which size can be obtained by 
* IMultiVMR9RenderEngine::GetViewPortSize()). 
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
* dwZ -- specifies Z-Order. If dwZ is bigger than the number of primitives mixer 
*        control is processing, it is truncated to the (size_of_the_list -1)
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::SetZOrder(DWORD_PTR dwID, DWORD dwZ)
{
    CMultiVMR9_Frame *pFrameRequested = NULL;
    CMultiVMR9_Frame *pFrame = NULL;
    CMultiVMR9_Frame *pFrameTo = NULL;

    int nCounter;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    if( dwZ > m_listFrames.size() - 1)
    {
        dwZ = m_listFrames.size() - 1;
    }

    list<CMultiVMR9_Frame*>::iterator start, end, it;

    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( dwID == pFrame->m_dwID )
        {
            pFrameRequested = pFrame;
        }
        if( pFrame->m_dwZOrder == dwZ )
        {
            pFrameTo = pFrame;
        }
    }
    if( !pFrameRequested )
    {
        ::DbgMsg("CMultiVMR9MixerControl::SetZOrder: requested video source 0x%08x was not found",
            dwID);
        return VFW_E_NOT_FOUND;
    }

    CAutoLock Lock(&m_ObjectLock);

    if( dwZ == pFrameRequested->m_dwZOrder )
    {
        return S_FALSE;
    }

    // 1. remove pFrameRequested
    m_listFrames.remove( pFrameRequested);

    // 2. insert 
    start = m_listFrames.begin();
    end = m_listFrames.end();
    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( pFrame == pFrameTo )
        {
            if( dwZ < pFrameRequested->m_dwZOrder )
            {
                it++;
            }
            if( it == end )
            {
                m_listFrames.push_back( pFrameRequested );
            }
            else
            {
                m_listFrames.insert( it, pFrameRequested );
            }
            break;
        }
    }
    
    nCounter = m_listFrames.size()-1;
    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        pFrame->m_dwZOrder = (DWORD)nCounter;
        nCounter--;
    }

    return S_OK;
}

/******************************Public*Routine******************************\
* GetAlpha
*
* Call this method to get alpha-level (transparency) of a video source, normalized 
* to the range [0.0, 1.0] 
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
* pAlpha -- receives alpha-level
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     E_POINTER (pAlpha is NULL)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::GetAlpha(DWORD_PTR dwID, float* pAlpha)
{
    CMultiVMR9_Frame *pFrameRequested = NULL;
    CMultiVMR9_Frame *pFrame = NULL;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }
    if( !pAlpha )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetAlpha: received NULL pointer");
        return E_POINTER;
    }
    list<CMultiVMR9_Frame*>::iterator start, end, it;

    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( dwID == pFrame->m_dwID )
        {
            pFrameRequested = pFrame;
            break;
        }
    }
    if( !pFrameRequested )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetAlpha: requested video source 0x%08x was not found",
            dwID);
        return VFW_E_NOT_FOUND;
    }

    *pAlpha = pFrame->m_alpha;
    return S_OK;
}

/******************************Public*Routine******************************\
* SetAlpha
*
* Call this method to set alpha-level (transparency) of a video source, normalized 
* to the range [0.0, 1.0]
*
* dwID - ID of the video source assigned in IMultiVMR9Wizard::Attach(). This ID 
*        should be already registered with hosting wizard.
* Alpha -- specifies alpha-level. Value is always truncated to [0.0, 1.0] range
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)
*                     VFW_E_WRONG_STATE(mixer was not initialized)
\**************************************************************************/

STDMETHODIMP CMultiVMR9MixerControl::SetAlpha(DWORD_PTR dwID, float Alpha)
{
    CMultiVMR9_Frame *pFrameRequested = NULL;
    CMultiVMR9_Frame *pFrame = NULL;

    if( !m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    Alpha = (Alpha < 0.f ) ? 0.f : Alpha;
    Alpha = (Alpha > 1.f ) ? 1.f : Alpha;

    list<CMultiVMR9_Frame*>::iterator start, end, it;

    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it != end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        if( dwID == pFrame->m_dwID )
        {
            pFrameRequested = pFrame;
            break;
        }
    }
    if( !pFrameRequested )
    {
        ::DbgMsg("CMultiVMR9MixerControl::SetAlpha: requested video source 0x%08x was not found",
            dwID);
        return VFW_E_NOT_FOUND;
    }

    CAutoLock Lock(&m_ObjectLock);

    pFrame->m_alpha = Alpha;
    BYTE byteAlpha = (BYTE)(255.f * pFrame->m_alpha);

    for( int i=0; i<4; i++)
    {
        pFrame->m_coord[i].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, byteAlpha);
    }
    return S_OK;
}

/******************************Public*Routine******************************\
* GetBackgroundColor
*
* Call this method to get background color (as RGB value)
*
* pColor -- receives background color
*
* Return error codes: E_POINTER (pColor is NULL)
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::GetBackgroundColor(COLORREF* pColor)
{
    if( !pColor )
    {
        ::DbgMsg("CMultiVMR9MixerControl::GetBackgroundColor: received NULL pointer");
        return E_POINTER;
    }
    *pColor = m_BackgroundColor;
    return S_OK;
}

/******************************Public*Routine******************************\
* SetBackgroundColor
*
* Call this method to set background color (as RGB value)
*
* Color -- specifies background color
*
* Return error codes: none        
*                     
\**************************************************************************/
STDMETHODIMP CMultiVMR9MixerControl::SetBackgroundColor(COLORREF Color)
{
    CAutoLock Lock(&m_ObjectLock);
    m_BackgroundColor = Color;
    return S_OK;
}

/////////////////////// Private routine ///////////////////////////////////////

/******************************Private*Routine*****************************\
* Clean_
*
* cleans data, releases interfaces
*
* Return error codes: none
*                     
\**************************************************************************/
void CMultiVMR9MixerControl::Clean_()
{
    CMultiVMR9_Frame* pFrame = NULL;

    // go clean the list
    list<CMultiVMR9_Frame*>::iterator start, end, it;
    start = m_listFrames.begin();
    end = m_listFrames.end();

    for( it = start; it!= end; it++)
    {
        pFrame = (CMultiVMR9_Frame*)(*it);
        delete pFrame;
        pFrame = NULL;
    }
    m_listFrames.clear();
    RELEASE( m_pOwner );
}

/******************************Private*Routine*****************************\
* CMultiVMR9_Frame
*
* constructor
\**************************************************************************/
CMultiVMR9MixerControl::CMultiVMR9_Frame::CMultiVMR9_Frame()
    : m_dwID( 0L )
    , m_WidthAR( 0.f )
    , m_HeightAR( 0.f )
    , m_lImageWidth( 0L )
    , m_lImageHeight( 0L )
    , m_ar( 0.f )
    , m_alpha( 1.f )
    , m_dwZOrder( 0L )
{
    ZeroMemory( m_coord, sizeof( m_coord[0]));
    ZeroMemory( &m_nrDst, sizeof(NORMALIZEDRECT));
}

/******************************Private*Routine*****************************\
* ~CMultiVMR9_Frame
*
* destructor
\**************************************************************************/
CMultiVMR9MixerControl::CMultiVMR9_Frame::~CMultiVMR9_Frame()
{
}


/******************************Private*Routine*****************************\
* CMultiVMR9_Frame::Initialize
*
* 
\**************************************************************************/
HRESULT CMultiVMR9MixerControl::CMultiVMR9_Frame::Initialize( 
            DWORD_PTR dwUserID,
            LONG lWidth, 
            LONG lHeight, 
            LONG lTextureWidth,
            LONG lTextureHeight,
            LONG lRenderTargetWidth,
            LONG lRenderTargetHeight,
            float fAlpha)
{
    HRESULT hr = S_OK;
    NORMALIZEDRECT nrIdeal;
    BYTE byteAlpha;
    float rtw;  // ideal width, in RenderTarget pixel coords
    float rth;  // ideal height, in RenderTarget pixel coords
    float nw;   // ideal width, in normalized coords
    float nh;   // ideal height, in normalized coords

    m_dwID = dwUserID;

    // truncate alpha
    m_alpha = (fAlpha<0.f) ? 0.f : fAlpha;
    m_alpha = (fAlpha>1.f) ? 1.f : fAlpha;
    byteAlpha = (BYTE)(255.f * m_alpha);

    // make sure sizes are positive
    m_lImageWidth  = (lWidth  > 0) ? lWidth :  -lWidth;
    m_lImageHeight = (lHeight > 0) ? lHeight : -lHeight;

    // calculate aspect ratio
    if( 0 == m_lImageHeight )
    {
        ::DbgMsg("CMultiVMR9_Frame::Initialize: FATAL, received image height = 0");
        return E_UNEXPECTED;
    }
    if( 0 == m_lImageWidth )
    {
        ::DbgMsg("CMultiVMR9_Frame::Initialize: FATAL, received image width = 0");
        return E_UNEXPECTED;
    }
    if( 0 == lRenderTargetWidth)
    {
        ::DbgMsg("CMultiVMR9_Frame::Initialize: FATAL, received render target width = 0");
        return E_UNEXPECTED;
    }
    if( 0 == lRenderTargetHeight)
    {
        ::DbgMsg("CMultiVMR9_Frame::Initialize: FATAL, received render target height = 0");
        return E_UNEXPECTED;
    }
    if( 0 == lTextureWidth )
    {
        ::DbgMsg("CMultiVMR9_Frame::Initialize: FATAL, received texture width = 0");
        return E_UNEXPECTED;
    }
    if( 0 == lTextureHeight )
    {
        ::DbgMsg("CMultiVMR9_Frame::Initialize: FATAL, received texture height = 0");
        return E_UNEXPECTED;
    }


    m_ar = (float)m_lImageWidth / (float)m_lImageHeight;

    // calculate ideal rect

    // try to fit horiz.
    rtw = (float)lRenderTargetWidth;
    rth = rtw / m_ar;

    if( rth > (float)lRenderTargetHeight )
    {
        // fit vert.
        rth = (float)lRenderTargetHeight;
        rtw = rth * m_ar;
    }

    // convert Render Target coords to normalized
    nw = rtw / (float)lRenderTargetWidth;
    nh = rth / (float)lRenderTargetHeight;

    // for convinience, take half-width andf half-height
    nw /= 2.f;
    nh /= 2.f;

    // calculate nrect - destination
    nrIdeal.left   = 0.5f - nw;
    nrIdeal.right  = 0.5f + nw;
    nrIdeal.top    = 0.5f - nh;
    nrIdeal.bottom = 0.5f + nh;

    m_WidthAR  = (float)lWidth  / (float)lTextureWidth;
    m_HeightAR = (float)lHeight / (float)lTextureHeight;

    // set texture source coords
    m_coord[0].tu = 0.f;        m_coord[0].tv = 0.f;
    m_coord[1].tu = 1.f;        m_coord[1].tv = 0.f;
    m_coord[2].tu = 0.f;        m_coord[2].tv = 1.f;
    m_coord[3].tu = 1.f;        m_coord[3].tv = 1.f;

    // set diffuse color = white on all vertices
    m_coord[0].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, byteAlpha);
    m_coord[1].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, byteAlpha);
    m_coord[2].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, byteAlpha);
    m_coord[3].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, byteAlpha);

    hr = UpdateDestination( nrIdeal );

    return hr;
}

/******************************Private*Routine*****************************\
* UpdateDestination
*
* Updates destination normrect and (x,y) coordinates. 
\**************************************************************************/
HRESULT CMultiVMR9MixerControl::CMultiVMR9_Frame::UpdateDestination( 
    NORMALIZEDRECT& newnrect)
{
    HRESULT hr = S_OK;

    // coordinates in composition space [-1,1]x[1,-1]
    float cl; // left
    float ct; // top
    float cr; // right
    float cb; // bottom

    memcpy( (void*)(&m_nrDst), (const void*)(&newnrect), sizeof(NORMALIZEDRECT));

    // update composition space coordinates
    // comp_space_x = 2. * norm_space_x - 1.;
    // comp_space_x = 1. - 2. * norm_space_y;
    cl = 2.f * m_nrDst.left - 1.f;
    cr = 2.f * m_nrDst.right - 1.f;
    ct = 1.f - 2.f * m_nrDst.top;
    cb = 1.f - 2.f * m_nrDst.bottom;

    m_coord[0].position.x = cl;
    m_coord[0].position.y = ct;
    m_coord[0].position.z = 0.5f; 

    m_coord[1].position.x = cr;
    m_coord[1].position.y = ct;
    m_coord[1].position.z = 0.5f; 

    m_coord[2].position.x = cl;
    m_coord[2].position.y = cb;
    m_coord[2].position.z = 0.5f;

    m_coord[3].position.x = cr;
    m_coord[3].position.y = cb;
    m_coord[3].position.z = 0.5f;

    return S_OK;
}

