//------------------------------------------------------------------------------
// File: Wizard.cpp
//
// Desc: DirectShow sample code - Implements the CMultiVMR9Wizard class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Wizard.h"
#include <multimon.h>
#ifdef _BUILD_FROM_VS
#include <Windows.h>
#endif

#include <list>
using namespace std;



/******************************Public*Routine******************************\
* CMultiVMR9Wizard
*
* constructor
\**************************************************************************/
CMultiVMR9Wizard::CMultiVMR9Wizard(LPUNKNOWN pUnk, HRESULT *phr)
    : CUnknown(NAME("MultiVMR9 Wizard"), pUnk)
    , m_dwConfigFlags( NULL )
    , m_pRenderEngine( NULL )
    , m_pNotify( NULL )
    , m_bInitialized (FALSE )
    , m_RenderThreadStatus( eNotStarted )
    , m_hwnd( NULL)
{
}

/******************************Public*Routine******************************\
* ~CMultiVMR9Wizard
*
* destructor
\**************************************************************************/
CMultiVMR9Wizard::~CMultiVMR9Wizard()
{
    HRESULT hr = Terminate();
}

///////////////////////// IUnknown /////////////////////////////////////////

/******************************Public*Routine******************************\
* CreateInstance
\**************************************************************************/
CUnknown* CMultiVMR9Wizard::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
    return new CMultiVMR9Wizard(pUnk, phr);
}

/******************************Public*Routine******************************\
* NonDelegatingQueryInterface
\**************************************************************************/
STDMETHODIMP
CMultiVMR9Wizard::NonDelegatingQueryInterface(
    REFIID riid,
    void ** ppv)
{
    HRESULT hr = E_NOINTERFACE;
    *ppv = NULL;

    if (riid == IID_IMultiVMR9Wizard) 
    {
        hr = GetInterface((IMultiVMR9Wizard *)this, ppv);
    }
    else if (riid == IID_IVMRSurfaceAllocator9) 
    {
        hr =  GetInterface((IVMRSurfaceAllocator9 *)this, ppv);
    }
    else if (riid == IID_IVMRImagePresenter9) 
    {
        hr = GetInterface((IVMRImagePresenter9 *)this, ppv );
    }
    else 
    {
        hr = CUnknown::NonDelegatingQueryInterface(riid,ppv);
    }
    return hr;
}


///////////////////////// IMultiVMR9Wizard /////////////////////////////////

/******************************Public*Routine******************************\
* Initialize
*
* Call this method right after IMultiVMR9Wizard object is created to configure 
* and initialize internal structures as well as D3D environment.
*
* dwFlags - Configuration flags
* hWnd  - handle to valid video window
* pRenderEngine - custom render engine (use NULL for default)
*
* Return error codes: E_INVALIDARG (invalid config flags or hWnd), 
*                     VFW_E_WRONG_STATE (method was already called before)
*                     E_FAIL (unexpected error), 
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::Initialize(
    DWORD dwFlags, 
    HWND hWnd,
    IMultiVMR9RenderEngine *pRenderEngine)
{
    HRESULT hr = S_OK;
    HWND hwndRE = NULL;

    if( m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9Wizard::Initialize: Wizard is already initialized");
        return VFW_E_WRONG_STATE;
    }

    if( FALSE == IsWindow( hWnd ))
    {
        ::DbgMsg("CMultiVMR9Wizard::Initialize: Invalid handle to the video window");
        return E_INVALIDARG;
    }
    m_hwnd = hWnd;

    // TODO: check flags
    m_dwConfigFlags = dwFlags;

    CAutoLock Lock(&m_ObjectLock);

    try
    {
        // initialize render engine. We assume that if custom render engine is provided,
        // it is already initialized
        RELEASE( m_pRenderEngine );
        if( pRenderEngine ) // user specified customized render engine
        {
            // check that pRenderEngine was initialized and they point to the same window
            CHECK_HR( 
                hr = pRenderEngine->GetVideoWindow( &hwndRE ),
                ::DbgMsg("CMultiVMR9Wizard::Initialize: Failed to get window handler from the provided RenderEngine, hr = 0x%08x", hr));

            CHECK_HR( 
                hwndRE != m_hwnd ? E_FAIL : S_OK,
                ::DbgMsg("CMultiVMR9Wizard::Initialize: specified render engine points to a different window than wizard"));

            m_pRenderEngine = pRenderEngine;
            m_pRenderEngine->AddRef();
            m_pRenderEngine->SetWizardOwner(this);
        }
        else 
        {
            // custom render engine was not provided; created one
            hr = CoCreateInstance( CLSID_MultiVMR9RenderEngine, NULL, CLSCTX_INPROC_SERVER,
                            IID_IMultiVMR9RenderEngine, (void**)&m_pRenderEngine );

            CHECK_HR(
                FAILED(hr) ? hr : ( (!m_pRenderEngine) ? E_FAIL : S_OK),
                ::DbgMsg("CMultiVMR9Wizard::Initialize: Failed to create MultiVMR9RenderEngine object, error code %08x", hr));

            if( FAILED(hr))
            {
                RELEASE( m_pRenderEngine );
            }
            CHECK_HR(
                hr = m_pRenderEngine->Initialize( m_hwnd, NULL, NULL, NULL), // TODO: second parameter is flags
                ::DbgMsg("CMultiVMR9Wizard::Initialize: failed to initialize default render engine, hr = 0x%08x", hr));

            m_pRenderEngine->SetWizardOwner(this);
        }
        m_bInitialized = TRUE;

        CHECK_HR(
            hr = StartRenderingThread_(),
            ::DbgMsg("CMultiVMR9Wizard::Initialize: failed in StartRenderingThread_, hr = 0x%08x", hr));

    }// __try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* Terminate
*
* This method must be called before destroying the wizard
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::Terminate()
{
    HRESULT hr = S_OK;
    
    // check that we do not have connected subgraphs
    if( m_listVideoSources.size() > 0 )
    {
        return VFW_E_WRONG_STATE;
    }

    try
    {
        CHECK_HR(
            hr = StopRenderingThread_(),
            ::DbgMsg("CMultiVMR9Wizard::Terminate: failed to stop rendering thread, hr = 0x%08x", hr));

        // Unadvise render engine
        if( m_pRenderEngine )
        {
            CHECK_HR( 
                hr = m_pRenderEngine->SetWizardOwner( NULL),
                ::DbgMsg("CMultiVMR9Wizard::Terminate: failed to unadvise WizardOwner for render engine, hr = 0x%08x", hr));

            CHECK_HR( 
                hr = m_pRenderEngine->Terminate(),
                ::DbgMsg("CMultiVMR9Wizard::Terminate: failed to terminate render engine, hr = 0x%08x", hr));

            RELEASE( m_pRenderEngine );
        }
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    return hr;
}


/******************************Public*Routine******************************\
* Attach
*
* Call this method to attach subgraph to MultiVMR9. Before this call, 
* correspondent VMR9 filter must be added to its graph and the graph must be 
* rendered and stopped. You must call Detach() method before destroying the graph. 
* If VMR was attached successfully, method will also 
* add MultiVMR9_VideoSource structure (associated with this video source) 
* to the list of active objects 
*
* pVMR - pointer to VMR9 filter of the correspondent subgraph
*
* pdwID - return value, a DWORD_PTR cookie associated with attached subgraph
*
* Return error codes: E_POINTER (pVMR is NULL or pdwID is NULL)
*                     VFW_E_NOT_STOPPED (correspondent graph is not stopped 
*                                        or pVMR was not added to the graph,
*                                        or pVMR is not in the renderless mode)
*                     VFW_E_WRONG_STATE (method Initialize() was not called )
*                     E_FAIL (unexpected error),
*                     E_NOINTERFACE (pVMR does not expose IVMRSurfaceAllocatorNotify9)
*                     E_OUTOFMEMORY (memory allocation error)
*                     or error code from IVMRSurfaceAllocatorNotify9
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::Attach(
    IBaseFilter* pVMR, 
    DWORD_PTR* pdwID)
{
    HRESULT hr = S_OK;

    FILTER_INFO fiVMR;
    OAFilterState state;
    DWORD dwVMRMode = 0L;;

    MultiVMR9_VideoSource*  pVideoSource    = NULL;
    IMediaControl*          pMediaControl   = NULL;
    IVMRFilterConfig9*      pFilterConfig   = NULL;
    IFilterGraph*           pFilterGraph    = NULL;
    IDirect3DDevice9*       pDevice         = NULL;

    IDirect3D9 *pd3d9 = NULL;
    HMONITOR hMonitor = NULL;

    // check that pointers are valid
    if( !pVMR || !pdwID )
    {
        ::DbgMsg("CMultiVMR9Wizard::Attach received NULL pointer");
        return E_POINTER;
    }

    if( !m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9Wizard::Attach: method Initialize() was not called!");
        return VFW_E_WRONG_STATE;
    }

    try
    {
        // check that provided VMR is part of the graph
        hr = pVMR->QueryFilterInfo( &fiVMR );
        CHECK_HR(
            (NULL == fiVMR.pGraph) ? E_FAIL : S_OK,
            ::DbgMsg("CMultiVMR9Wizard::Attach: provided VMR was not added to the graph"));

        pFilterGraph = fiVMR.pGraph;
        pFilterGraph->AddRef();

        // check that provided VMR is in renderless mode
        hr = pVMR->QueryInterface(  IID_IVMRFilterConfig9, 
                                    (void**)&pFilterConfig );
        CHECK_HR(
            FAILED(hr) ? hr : ( !pFilterConfig ? E_FAIL : S_OK ),
            ::DbgMsg("CMultiVMR9Wizard::Attach: failed to QI IVMRFilterConfig9, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pFilterConfig->GetRenderingMode( &dwVMRMode ),
            ::DbgMsg("CMultiVMR9Wizard::Attach: failed to get rendering mode, hr = 0x%08x", hr));

        CHECK_HR(
            (VMRMode_Renderless != dwVMRMode) ? VFW_E_WRONG_STATE : S_OK,
            ::DbgMsg("CMultiVMR9Wizard::Attach: provided VMR9 is not in renderless mode"));

        pVideoSource = new MultiVMR9_VideoSource;

        CHECK_HR(
            !pVideoSource ? E_OUTOFMEMORY : S_OK,
            ::DbgMsg("CMultiVMR9Wizard::Attach: failed to allocate MultiVMR9_VideoSource structure"));

        pVideoSource->dwID = (DWORD_PTR)pVideoSource;

        pVideoSource->pVMR = pVMR;
        pVideoSource->pVMR->AddRef();

        pVideoSource->pGraph = pFilterGraph;
        pVideoSource->pGraph->AddRef();

        // check that provided pVMR exposes IVMRSurfaceAllocatorNotify9 interfaces
        CHECK_HR(
            pVMR->QueryInterface( IID_IVMRSurfaceAllocatorNotify9, 
                            (void**)&pVideoSource->pDefaultNotify),
            ::DbgMsg("CMultiVMR9Wizard::Attach: cannot QI IVMRSurfaceAllocatorNotify9"));

        CHECK_HR(
            pVideoSource->pGraph->QueryInterface( IID_IMediaControl, 
                            (void**)&pMediaControl),
            ::DbgMsg("CMultiVMR9Wizard::Attach: cannot QI IMediaControl"));

        CHECK_HR(
            hr = pMediaControl->GetState( 100, &state),
            ::DbgMsg("CMultiVMR9Wizard::Attach: failed to get state of IMediaControl, hr = 0x%08x", hr));

        CHECK_HR(
            ( state != State_Stopped ) ? VFW_E_NOT_STOPPED : S_OK,
            ::DbgMsg("CMultiVMR9Wizard::Attach: graph is not stopped, state = %ld", state));

        // we have to be thread safe only here when we actually mess up with shared data
        CAutoLock Lock(&m_ObjectLock);

        // set device
        CHECK_HR(
            hr = m_pRenderEngine->Get3DDevice( &pDevice ),
            ::DbgMsg(   "CMultiVMR9Wizard::Attach: failed to obtain Direct3D device "\
                        "from the render engine, hr = 0x%08x", hr));

        // COMMENTED CODE works for VS.Net and PlatformSDK. If you use them, uncomment
        // the following block and comment the next one
        /*
        {
            CHECK_HR(
                hr = pVideoSource->pDefaultNotify->SetD3DDevice(
                        pDevice, 
                        MonitorFromWindow( m_hwnd, MONITOR_DEFAULTTOPRIMARY )),
                ::DbgMsg("CMultiVMR9Wizard::Attach: failed in SetD3DDevice() of IVMRSurfaceAllocatorNotify, "\
                        "hr = 0x%08x", hr));
        }
        */
        {

            CHECK_HR(
                hr = pDevice->GetDirect3D( &pd3d9 ),
                ::DbgMsg("CMultiVMR9Wizard::Attach: failed to retrieve IDirect3D9"));

            HMONITOR hMonitor = pd3d9->GetAdapterMonitor( D3DADAPTER_DEFAULT );

            CHECK_HR(
                hr = pVideoSource->pDefaultNotify->SetD3DDevice(
                        pDevice, 
                        hMonitor),
                ::DbgMsg("CMultiVMR9Wizard::Attach: failed in SetD3DDevice() of IVMRSurfaceAllocatorNotify, "\
                        "hr = 0x%08x", hr));

        }

        // try to advise 'this' custom allocator-presenter to the VMR
        CHECK_HR(
            hr = pVideoSource->pDefaultNotify->AdviseSurfaceAllocator( 
                                            pVideoSource->dwID, 
                                            (IVMRSurfaceAllocator9*)this),
            ::DbgMsg("CMultiVMR9Wizard::Attach: failed to advise A/P, hr = 0x%08x", hr));

        CHECK_HR(
            hr = StartPresenting( pVideoSource->dwID ),
            ::DbgMsg("CMultiVMR9Wizard::Attach: failed in StartPresenting(), hr = 0x%08x", hr));

        // we successfully attached subgraph, last thing left is to save 
        // pVideoSource in the list
        m_listVideoSources.push_back( pVideoSource );
        *pdwID = pVideoSource->dwID;

    } // try
    catch( HRESULT hr1 )
    {
        hr = hr1;
        if( pVideoSource )
        {
            delete pVideoSource;
            pVideoSource = NULL;
        }
    }
    RELEASE( pd3d9 );
    RELEASE( fiVMR.pGraph );
    RELEASE( pFilterGraph );
    RELEASE( pFilterConfig );
    RELEASE( pMediaControl );
    RELEASE( pDevice );

    return hr;
}

/******************************Public*Routine******************************\
* Detach
*
* Detaches VMR of particular subgraph (identified by dwID) and 
* unadvises custom allocator-presenter. Call this method before destroying 
* correspondent subgraph. Graph must be stopped before calling this method. 
* Pins of the correspondent VMR filter must be disconnected
*
* dwID  -- Number that uniquely identifies subgraph in the multi-graph environment. 
*          This number is assigned to the subgraph in Attach() method.
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID),
*                     VFW_E_WRONG_STATE (method Initalize() was never called)
*                     VFW_E_NOT_STOPPED (graph was not stopped),
*                     E_FAIL (unexpected), 
*                     or error code of IVMRSurfaceAllocatorNotify9.
\**************************************************************************/

STDMETHODIMP CMultiVMR9Wizard::Detach(DWORD_PTR dwID)
{
    HRESULT hr = S_OK;
    OAFilterState state;

    bool bSourceWasDeleted = false;

    IMediaControl*          pMc             = NULL;
    IMultiVMR9MixerControl* pMixerControl   = NULL;

    MultiVMR9_VideoSource*  pvideosource    = NULL;
    MultiVMR9_VideoSource*  pcursource      = NULL;

    if( !m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9Wizard::Detach: method 'Initialize' was never called");
        return VFW_E_WRONG_STATE;
    }

    hr = GetSourceInfo_( dwID, &pvideosource );
    if( FAILED(hr) || !pvideosource )
    {
        ::DbgMsg("CMultiVMR9Wizard::Detach: Failed in GetSourceInfo_()");
        return ( FAILED(hr) ? hr : VFW_E_NOT_FOUND );
    }

    if( !m_pRenderEngine )
    {
        ::DbgMsg("CMultiVMR9Wizard::Detach: FATAL IMultiVMR9RenderEngine pointer is NULL!");
        return E_UNEXPECTED;
    }

    if( !pvideosource->pGraph )
    {
        ::DbgMsg("CMultiVMR9Wizard::Detach: video source info does not contain pointer to IFilterGraph!");
        return VFW_E_NOT_FOUND; 
    }

    try
    {
        CHECK_HR(
            hr = (pvideosource->pGraph)->QueryInterface( 
                                    IID_IMediaControl, (void**)&pMc ),
            ::DbgMsg("CMultiVMR9Wizard::Detach: cannot QI IMediaControl of the graph, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pMc->GetState( 100, &state ),
            ::DbgMsg("CMultiVMR9Wizard::Detach: cannot obtain state from IMediaControl, hr = 0x%08x", hr));

        CHECK_HR(
            ( State_Stopped != state ) ? VFW_E_NOT_STOPPED : S_OK,
            ::DbgMsg("CMultiVMR9Wizard::Detach: correspondent graph was not stopped"));

        // advise NULL as A/P to VMR9 (this will return VMR9 to its default A/P)
        CHECK_HR(
            ( !(pvideosource->pDefaultNotify)) ? VFW_E_NOT_FOUND : S_OK,
            ::DbgMsg("CMultiVMR9Wizard::Detach: video source info does not contain pointer to IVMRSurfaceAllocatorNotify9"));

        CHECK_HR(
            hr = m_pRenderEngine->GetMixerControl( &pMixerControl ),
            ::DbgMsg("CMultiVMR9Wizard::Detach: FATAL, cannot find currently active IMultiVMR9MixerControl!"));

        // we have to be thread safe only here when we actually mess up with shared data
        CAutoLock Lock(&m_ObjectLock);

        CHECK_HR(
            hr = StopPresenting( pvideosource->dwID ),
            ::DbgMsg("CMultiVMR9Wizard::Detach: failed in StopPresenting(), hr = 0x%08x", hr));

        CHECK_HR(
            pvideosource->DisconnectPins(),
            ::DbgMsg("CMultiVMR9Wizard::Detach: FATAL, failed to disconnect pins of VMR"));

        CHECK_HR(
            hr = (pvideosource->pDefaultNotify)->AdviseSurfaceAllocator( 
                                                        dwID, NULL),
            ::DbgMsg("CMultiVMR9Wizard::Detach: failed to unadvise surface allocator, hr = 0x%08x", hr));
        
        // we unadvised custom allocator-presenter successfully, let's delete 
        // video source structure from the list
        list< MultiVMR9_VideoSource*>::iterator start, end, it;
        start = m_listVideoSources.begin();
        end = m_listVideoSources.end();

        for( it=start; it!=end; it++)
        {
            pcursource = (MultiVMR9_VideoSource*)(*it);

            CHECK_HR(
                ( NULL == pcursource ) ? E_UNEXPECTED : S_OK,
                ::DbgMsg("CMultiVMR9Wizard::Detach: FATAL, m_listVideoSources contains NULL pointer"));

            if( dwID == pcursource->dwID )
            {
                // delete this video source from the mixer
                CHECK_HR(
                    hr = pMixerControl->DeleteVideoSource( dwID ),
                    ::DbgMsg("CMultiVMR9Wizard::Detach: failed to delete source from "\
                            "the mixer (ID=0x%08x, hr=0x%08x)", dwID, hr));

                m_listVideoSources.remove( pcursource );
                delete pcursource;
                pcursource = NULL;
                bSourceWasDeleted = true;
                break;
            }
        }// for
        CHECK_HR(
            ( false == bSourceWasDeleted ) ? VFW_E_NOT_FOUND : S_OK,
            ::DbgMsg("CMultiVMR9Wizard::Detach: FATAL, failed to delete source from the list (source was not found)"));
    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    RELEASE( pMc );
    RELEASE( pMixerControl );

    return hr;
}

/******************************Public*Routine******************************\
* VerifyID
*
* Call this method to check if some dwID is registered with the wizard
*
* dwID  -- Number that uniquely identifies subgraph in the multi-graph environment. 
*          This number is assigned to the subgraph in Attach() method.
*
* Return error codes: VFW_E_NOT_FOUND (unknown dwID)            
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::VerifyID( DWORD_PTR dwID )
{
    HRESULT hr = S_OK;
    MultiVMR9_VideoSource *pSrc = NULL;

    hr = this->GetSourceInfo_( dwID, &pSrc);

    if( SUCCEEDED( hr ) && pSrc )
    {
        return S_OK;
    }
    else
    {
        return VFW_E_NOT_FOUND;
    }
}

/******************************Public*Routine******************************\
* GetGraph
*
* Returns pointer to IFilterGraph interface of the sub-graph identified by dwID
*
* dwID  -- Number that uniquely identifies subgraph in the multi-graph environment. 
*          This number is assigned to the subgraph in Attach() method.
* ppGraph -- [out] pointer to IFilterGraph
*
* Return error codes: E_POINTER (ppGraph is NULL),
*                     VFW_E_WRONG_STATE (method Initialize() was never called)
*                     VFW_E_NOT_FOUND (unknown dwID),
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::GetGraph(DWORD_PTR dwID, IFilterGraph** ppGraph)
{
    HRESULT hr = S_OK;
    MultiVMR9_VideoSource *pSrc = NULL;

    if( !ppGraph )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetGraph: second argument is NULL");
        return E_POINTER;
    }

    if( !m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetGraph: Method 'Initialize' was never called");
        return VFW_E_WRONG_STATE;
    }

    hr = this->GetSourceInfo_( dwID, &pSrc);

    if( SUCCEEDED(hr))
    {
        if( pSrc->pGraph )
        {
            *ppGraph = pSrc->pGraph;
            (*ppGraph)->AddRef();
            hr = S_OK;
        }
        else
        {
            ::DbgMsg("CMultiVMR9Wizard::GetGraph: FATAL: member of the list of video sources contain NULL IFilterGraph pointer");
            hr = VFW_E_NOT_FOUND;
        }
    }
    else
    {
        ::DbgMsg("CMultiVMR9Wizard::GetGraph: Failed in GetSourceInfo_(), hr = 0x%08x", hr);
    }
    return hr;
}

/******************************Public*Routine******************************\
* GetRenderEngine
*
* Call this method to obtain actively used render engine object
*
* ppRenderEngine  -- Pointer to IMultiVMR9RenderEngine
*
* Return error codes: E_POINTER (ppGraph is NULL)
*                     VFW_E_WRONG_STATE (method Initalize() was never called )
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::GetRenderEngine(
    IMultiVMR9RenderEngine** ppRenderEngine
    )
{
    HRESULT hr = S_OK;

    if( !ppRenderEngine )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetRenderEngine: first argument is NULL");
        return E_POINTER;
    }

    if( !m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetRenderEngine: Method 'Initialize' was never called");
        return VFW_E_WRONG_STATE;
    }

    *ppRenderEngine = m_pRenderEngine;
    (*ppRenderEngine)->AddRef();
    return S_OK;
}

/******************************Public*Routine******************************\
* GetMixerControl
*
* Call this method to obtain actively used mixer control object (IMultiVMR9MixerControl)
*
* ppMixerControl  -- Pointer to IMultiVMR9MixerControl
*
* Return error codes: E_POINTER (ppGraph is NULL)
*                     VFW_E_WRONG_STATE (method Initalize() was never called )
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::GetMixerControl(
        IMultiVMR9MixerControl** ppMixerControl
        )
{
    HRESULT hr = S_OK;
    if( !ppMixerControl )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetMixerControl: received NULL pointer");
        return E_POINTER;
    }
    if( !m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetMixerControl: Method 'Initialize' was never called");
        return VFW_E_WRONG_STATE;
    }
    if( !m_pRenderEngine )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetMixerControl: FATAL, cannot find IMultiVMR9RenderEngine");
        return E_UNEXPECTED;
    }

    hr = m_pRenderEngine->GetMixerControl( ppMixerControl );

    return hr;
}

/******************************Public*Routine******************************\
* GetTexture
*
* This method returns D3D9 texture of the video source identified by dwID 
* Render Engine calls this method. 
*
* dwID - ID of the video source assigned in Attach();
* ppTexture - pointer to IDirect3DTexture9 that receives texture to be rendered
*
* Return error codes: E_POINTER (ppTexture is NULL), 
*                     VFW_E_WRONG_STATE ( method Initialize() was never called )
*                     VFW_E_NOT_FOUND (ID was not found), 
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::GetTexture(
        DWORD_PTR dwID,
        LPDIRECT3DTEXTURE9* ppTexture 
        )
{
    HRESULT hr = E_FAIL;
    MultiVMR9_VideoSource *pSrc = NULL;

    if( !ppTexture )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetRenderEngine: second argument is NULL");
        return E_POINTER;
    }

    if( !m_bInitialized )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetRenderEngine: method 'Initialize' was never called");
        return VFW_E_WRONG_STATE;
    }

    hr = GetSourceInfo_( dwID, &pSrc );
    if( FAILED(hr))
    {
        ::DbgMsg("CMultiVMR9Wizard::GetRenderEngine: failed in GetSourceInfo_()  (video source was not found)");
        return VFW_E_NOT_FOUND;
    }

    *ppTexture = pSrc->pTexturePriv;
    (*ppTexture)->AddRef();

    return S_OK;
}

/******************************Public*Routine******************************\
* GetVideoSize
*
* Call this method to obtain native video size of the video source
* identified with dwID. Sizes correspond to VMR9AllocationInfo::dwWidth,
* VMR9AllocationInfo::dwHeight that is sent to CMultiVMR9Wizard::InitializeDevice
* See description of VMR9AllocationInfo in the DirectShow SDK documentation for
* other sizes that can be used 
*
* dwID - ID of the video source assigned in Attach();
* plWidth - pointer to the variable that receives width
* plHeight - pointer to the variable that receives height
* Return error codes: E_POINTER (either plWidth or plHeight is NULL), 
*                     VFW_E_NOT_FOUND (ID was not found), 
* 
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::GetVideoSize(
        DWORD_PTR dwID,
        LONG* plWidth,
        LONG* plHeight
        )
{
    HRESULT hr = S_OK;
    MultiVMR9_VideoSource *pSrc = NULL;

    if( !plWidth )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetVideoSize: received NULL for plWidth");
        return E_POINTER;
    }
    if( !plHeight )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetVideoSize: received NULL for plHeight");
        return E_POINTER;
    }

    hr = GetSourceInfo_( dwID, &pSrc );
    if( FAILED(hr))
    {
        ::DbgMsg("CMultiVMR9Wizard::GetVideoSize: failed in GetSourceInfo_()  (video source was not found)");
        *plWidth = 0L;
        *plHeight = 0L;
        return VFW_E_NOT_FOUND;
    }

    *plWidth = pSrc->lImageWidth;
    *plHeight = pSrc->lImageHeight;
    return S_OK;
}


///////////////////////// IVMRSurfaceAllocator9 ///////////////////////////////

/******************************Public*Routine******************************\
* AdviseNotify
*
* For usage, parameters and return codes
* see DirectX SDK documentation, IVMRSurfaceAllocator9 interface
*
* In custom implementation of this method, we do nothing. Why?
* When VMR is created, it creates its own (default) allocator-presenter
* and alltogether with IVMRSurfaceAllocatorNotify9::AdviseSurfaceAllocator,
* method IVMRSurfaceAllocator9::AdviseNotify() is used to make two objects
* talking to each other. We do not implement our custom IVMRSurfaceAllocatorNotify9
* in this sample, and we have complete control over our custom A/P (this class
* CMultiVMR9Wizard), so we do not have to tell A/P about VMR's notifier.
*
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::AdviseNotify(
        IVMRSurfaceAllocatorNotify9*  lpIVMRSurfAllocNotify
        )
{
    return S_OK;
}

/******************************Public*Routine******************************\
* InitializeDevice
*
* For usage, parameters and return codes
* see DirectX SDK documentation, IVMRSurfaceAllocator9 interface
* 
* In the custom implementation of this method, we provide Direct3D device 
* from CMultiVMR9RenderEngine that is responsible for actual Direct3D rendering.
* InitializeDevice() is called by VMR to make a request for allocation of the swap chain.
* We use Direct3DDevice9 from CMultiVMR9RenderEngine to allocate surfaces. Since 
* render engine uses Direct3D primitives (and video is applied on them as a texture),
* we must make sure that 
* VMR9AllocationInfo::dwFlags contain VMR9AllocFlag_TextureSurface. For actual
* surface allocation that works best on a particular device, we use 
* helper function IVMRSurfaceAllocatorNotify9::AllocateSurfaceHelper from 
* the default IVMRSurfaceAllocatorNotify9 of the VMR making request. (We saved 
* this pointer in MultiVMR9_VideoSource::pDefaultNotify in Attach(), while 
* connecting this VMR to our A/P). 
* Unlike VMR9Allocator sample of this SDK, we cannot use the same swap chain
* to make actual rendering, because we have to accumulate PresentImage() calls 
* from many different sources and keep CMultiVMR9RenderEngine rendering 
* asynchronously from VMR calls (with the frame rate specified by client app). 
* So in addition to swap chain allocation we also allocate private texture for
* each video source and will Blt on it every time correspondent VMR makes
* PresentImage() call. Then render engine renders whatever was written last
* to this private texture (i.e. some frames might be dropped and some will be 
* rendered several times, depending on the difference between native frame rate 
* and the frame rate our render engine is using).
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::InitializeDevice(
        DWORD_PTR  dwUserID,
        VMR9AllocationInfo*  lpAllocInfo,
        DWORD*  lpNumBuffers
        )
{
    HRESULT hr = S_OK;
    D3DFORMAT format;
    D3DSURFACE_DESC ddsd;
    D3DCAPS9 ddcaps;
    UINT width;
    UINT height;


    MultiVMR9_VideoSource*  pSrc    = NULL;
    IDirect3DDevice9*       pDevice = NULL;
    IDirect3DSurface9*      pS      = NULL;
    IMultiVMR9MixerControl* pMixerControl = NULL;

    // first, make sure we got a call from a known VMR
    hr = GetSourceInfo_( dwUserID, &pSrc );
    if( FAILED(hr) || !pSrc )
    {
        ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: cannot get info on the calling VMR, "\
            "dwUserID = 0x%08x, hr = 0x%08x, pSource = 0x%08x", dwUserID, hr, (void*)pSrc);
        return ( FAILED(hr)? hr : E_FAIL );
    }
    // check we are provided valid parameters
    if( !lpAllocInfo || !lpNumBuffers )
    {
        return E_POINTER;
    }

    if( *lpNumBuffers <1 )
    {
        *lpNumBuffers = 1;
    }
    // check we know about the default IVMRSurfaceAllocatorNotify9
    if(!(pSrc->pDefaultNotify) )
    {
        ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: FATAL: video source contains NULL pointer to IVMRSurfaceAllocatorNotify9");
        return E_FAIL;
    }

    try
    {
        // obtain device from the render engine
        CHECK_HR(
            hr = m_pRenderEngine->Get3DDevice( &pDevice ),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed to get Direct3D device from the render engine, "\
                "hr = 0x%08x, pDevice = 0x%08x", hr, pDevice));

        // we have to be thread safe only here when we actually mess up with shared data
        CAutoLock Lock(&m_ObjectLock);

        // just some insanity check
        RELEASE( pSrc->pTexturePriv ); 
        pSrc->DeleteSurfaces();

        // allocate surface buffer
        CHECK_HR(
            hr = pSrc->AllocateSurfaceBuffer( *lpNumBuffers ),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed to allocate surface buffer, hr = 0x%08x, dwBuffers = %ld",
                hr, *lpNumBuffers));

        // since we always copy data onto private textures, we create 
        // the swap chain as offscreen surface
        //lpAllocInfo->Usage = 0; // not a render target
        lpAllocInfo->dwFlags = VMR9AllocFlag_OffscreenSurface;//VMR9AllocFlag_3DRenderTarget | VMR9AllocFlag_TextureSurface;

        CHECK_HR(
            hr = pSrc->pDefaultNotify->AllocateSurfaceHelper(
                                                lpAllocInfo, 
                                                lpNumBuffers, 
                                                pSrc->ppSurface ),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed in "\
                    "IVMRSurfaceAllocatorNotify9::AllocateSurfaceHelper, "\
                    "hr = 0x%08x, dwBuffers = %ld", hr, *lpNumBuffers));

        pSrc->dwNumBufActuallyAllocated = *lpNumBuffers;

        // here we are creating private texture to be used by the render engine
        if (lpAllocInfo->Format > '0000') // surface is YUV.
        {
            format = D3DFMT_X8R8G8B8;// TODO: get current display format
        }
        else // RGB: use the same as original 
        {
            format =  lpAllocInfo->Format;
        }

        // first, check if we have to comply with pow2 requirement
        ZeroMemory( &ddcaps, sizeof(D3DCAPS9));

        CHECK_HR(
            hr = pDevice->GetDeviceCaps( &ddcaps ),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed to get device caps"));

        if( ddcaps.TextureCaps & D3DPTEXTURECAPS_POW2 ) // have to make it pow2 :-(
        {
            width = 2;
            while( width < lpAllocInfo->dwWidth )
                width = width << 1;

            height = 2;
            while( height < lpAllocInfo->dwHeight )
                height = height << 1;
        }
        else
        {
            width = lpAllocInfo->dwWidth;
            height = lpAllocInfo->dwHeight;
        }


        CHECK_HR(
            hr = pDevice->CreateTexture(width,                // width
                                        height,               // height
                                        1,                    // levels
                                        D3DUSAGE_RENDERTARGET,// usage
                                        format,               // format
                                        D3DPOOL_DEFAULT,      // we are not going to get into surface bits, so we do not need managed
                                        &(pSrc->pTexturePriv),
                                        NULL),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed to create "\
                    "private texture, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pSrc->pTexturePriv->GetSurfaceLevel(0, &pS),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed to get 0-level surface "\
                    "of the private texture, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->ColorFill( pS, NULL, D3DCOLOR_XRGB(0x00,0x00,0x00)),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed to fill the surface "\
                    "of the private texture with solid color, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pSrc->pTexturePriv->GetLevelDesc(0, &ddsd),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed to obtain "\
                    "surface description of the private texture, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pSrc->SetVideoSize( lpAllocInfo->dwWidth, lpAllocInfo->dwHeight),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed to save "\
                    "video size, hr = 0x%08x", hr));

        // tell the mixer we are "on"
        CHECK_HR(
            hr = this->GetMixerControl( &pMixerControl ),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: cannot find IMultiVMR9MixerControl!"));

        CHECK_HR(
            hr = pMixerControl->AddVideoSource( 
                                            pSrc->dwID, 
                                            pSrc->lImageWidth, 
                                            pSrc->lImageHeight,
                                            ddsd.Width,
                                            ddsd.Height),
            ::DbgMsg("CMultiVMR9Wizard::InitializeDevice: failed in "\
            "IMultiVMR9MixerControl::AddVideoSource(), hr = 0x%08x", hr));

    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    RELEASE( pS );
    RELEASE( pDevice );
    RELEASE( pMixerControl );

    return hr;
}

/******************************Public*Routine******************************\
* TerminateDevice
*
* For usage, parameters and return codes
* see DirectX SDK documentation, IVMRSurfaceAllocator9 interface
*
* In the custom implementation of this method, we just release the surface buffer
* associated with correspondent video source
*
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::TerminateDevice(
        DWORD_PTR  dwID
        )
{
    HRESULT hr = S_OK;

    MultiVMR9_VideoSource *pSrc = NULL;

    hr = GetSourceInfo_( dwID, &pSrc );
    if( FAILED(hr) || !pSrc)
    {
        ::DbgMsg("CMultiVMR9Wizard::TerminateDevice: failed in GetSourceInfo_() (wrong dwID), "\
            "hr = 0x%08x, pSource = 0x%08x", hr, pSrc);
        return (FAILED(hr)? hr : E_FAIL);
    }

    // we have to be thread safe only here when we actually mess up with shared data
    CAutoLock Lock(&m_ObjectLock);

    return hr;
}


/******************************Public*Routine******************************\
* GetSurface
*
* For usage, parameters and return codes
* see DirectX SDK documentation, IVMRSurfaceAllocator9 interface
*
* In the custom implementation of this method, we check that dwUserID is valid,
* that Surface index does not exceed number of allocated buffers, and return 
* pointer to correspondent surface
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::GetSurface(
        DWORD_PTR  dwUserID,
        DWORD  SurfaceIndex,
        DWORD  SurfaceFlags,
        IDirect3DSurface9**  lplpSurface
        )
{
    HRESULT hr = S_OK;

    MultiVMR9_VideoSource *pSrc = NULL;

    // check for NULL pointers
    if( !lplpSurface )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetSurface: fourth argument is NULL");
        return E_POINTER;
    }

    // check that dwUserID points to a known VMR
    hr = GetSourceInfo_( dwUserID, &pSrc );
    if( FAILED(hr) || !pSrc )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetSurface, failed in GetSourceInfo_() (wrong dwID), "\
            "hr = 0x%08x, pSource = 0x%08x", hr, pSrc);
        return ( FAILED(hr) ? hr : E_FAIL );
    }

    // check that requested index does not exceed number of actually allocated buffers
    if( SurfaceIndex >= pSrc->dwNumBufActuallyAllocated  )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetSurface: requested surface index %ld falls out of "\
            "valid range [0, %ld]", SurfaceIndex, pSrc->dwNumBufActuallyAllocated);
        return E_INVALIDARG;
    }

    // check that requested surface is not null
    if( NULL == pSrc->ppSurface[ SurfaceIndex ] )
    {
        ::DbgMsg("CMultiVMR9Wizard::GetSurface: FATAL, requested surface of index %ld is NULL!",
            SurfaceIndex);
        return E_UNEXPECTED;
    }

    // we have to be thread safe only here when we actually mess up with shared data
    CAutoLock Lock(&m_ObjectLock);

    // now we checked everything and can copy
    *lplpSurface = pSrc->ppSurface[ SurfaceIndex ];
    (*lplpSurface)->AddRef();

    return S_OK;
}

///////////////////////// IVMRImagePresenter9 ///////////////////////////////

/******************************Public*Routine******************************\
* StartPresenting
*
* For usage, parameters and return codes
* see DirectX SDK documentation, IVMRImagePresenter9 interface
*
* In the custom implementation of this method, we check that dwUserID is valid
* and Direct3Ddevice from the render engine is ready to go
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::StartPresenting(
        DWORD_PTR  dwUserID
        )
{
    HRESULT hr = S_OK;
    MultiVMR9_VideoSource*  pSrc    = NULL;
    IDirect3DDevice9*       pDevice = NULL;

    CAutoLock Lock(&m_ObjectLock);

    hr = GetSourceInfo_( dwUserID, &pSrc );
    if( FAILED(hr) || !pSrc )
    {
        ::DbgMsg("CMultiVMR9Wizard::StartPresenting: failed in GetSourceInfo_() (invalid dwID) ,"\
            "hr = 0x%08x, pSource = 0x%08x", hr, pSrc);
        return ( FAILED(hr) ? hr : VFW_E_NOT_FOUND );
    }

    if( !m_pRenderEngine )
    {
        ::DbgMsg("CMultiVMR9Wizard::StartPresenting: FATAL, Render engine is NULL");
        return E_UNEXPECTED;
    }

    hr = m_pRenderEngine->Get3DDevice( &pDevice );
    if( FAILED(hr) || !pDevice )
    {
        ::DbgMsg("CMultiVMR9Wizard::StartPresenting: FATAL, Direct3DDevice in the render engine is NULL, "\
            "hr = 0x%08x, pDirect3DDevice = 0x%08x", hr, pDevice);
        RELEASE( pDevice );
        return ( FAILED(hr) ? hr : E_UNEXPECTED);
    }

    RELEASE( pDevice );
    return hr;
}

/******************************Public*Routine******************************\
* StopPresenting
*
* For usage, parameters and return codes
* see DirectX SDK documentation, IVMRImagePresenter9 interface
*
* In the custom implementation of this method, we do nothing. By default, method 
* does not actually perform anything special, but one can use it to reflect on 
* the status of the rendering (vs. status of the graph) etc. 
*
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::StopPresenting(
        DWORD_PTR  dwUserID
        )
{
    return S_OK;
}


/******************************Public*Routine******************************\
* PresentImage
*
* For usage, parameters and return codes
* see DirectX SDK documentation, IVMRImagePresenter9 interface
*
* This is the place where all the fun happens. VMR calls this method every time
* it is ready to render the image. From each VMR (they are identified with 
* dwUserID cookies) we obtain VMR9PresentationInfo structure (see SDK docs) that
* contains the buffer to render, as well as presentation flags, timestamps 
* of the sample, aspect ratio, source and destination rectangles. 
* Here, in the custom implementation of the method, we just copy the sample
* to the private texture we created in InitializeDevice() (See header to 
* InitializeDevice() to figure out why do we have to Blt onto private texture 
* rather than using surface from VMR9PresentationInfo directly). 
*
* Attention! This is the performance bottle neck of our library, because this 
* method is called by each VMR every time it delivers the picture. You do not
* want to put a lot of computations here. Here is 
* the limitation we have to comply to not start losing frames: 
*
* Execution_time( PresentImage ) << 1000ms / SUM( FPS_i, i=0..N) ms, 
*       where N in total number of VMRs attached and FPS_i is the frame rate
*       of i-th VMR (in frames per sec)
*
* so if you have one mpeg 30fps and one DVD 50 mps, you have less that 12.5 ms
* (in fact, you have much less time because you also spend resources in the render engine)
* -- or give up on the promise to not lose frames
\**************************************************************************/
STDMETHODIMP CMultiVMR9Wizard::PresentImage(
        DWORD_PTR  dwUserID,
        VMR9PresentationInfo*  lpPresInfo
        )
{
    HRESULT hr = S_OK;
    MultiVMR9_VideoSource*  pSrc                = NULL;
    IDirect3DDevice9*       pSampleDevice       = NULL;
    IDirect3DSurface9*      pTexturePrivSurf    = NULL;
    
    // first, check for NULLs
    if( !lpPresInfo || !(lpPresInfo->lpSurf))
    {
        ::DbgMsg("CMultiVMR9Wizard::PresentImage: received NULL pointer");
        return E_POINTER;
    }

    // check that we know about dwUserID
    hr = GetSourceInfo_( dwUserID, &pSrc );
    if( FAILED(hr) || !pSrc )
    {
        ::DbgMsg("CMultiVMR9Wizard::PresentImage: failed in GetSourceInfo_() (invalid dwID), "\
            "hr = 0x%08x, pSource = 0x%08x", hr, pSrc);
        return ( FAILED(hr) ? hr : VFW_E_NOT_FOUND);
    }

    if(!(pSrc->pTexturePriv) )
    {
        ::DbgMsg("CMultiVMR9Wizard::PresentImage: FATAL, private texture of the source %ld is NULL", dwUserID);
        return E_UNEXPECTED;
    }

    // this is important to be thread safe here
    CAutoLock Lock(&m_ObjectLock);

    try
    {
        // now, get the device of the sample passed in (it is not necessarily the same
        // device we created in the render engine
        CHECK_HR(
            hr = lpPresInfo->lpSurf->GetDevice( &pSampleDevice ),
            ::DbgMsg("CMultiVMR9Wizard::PresentImage: failed to get the device of the surface passed in, "\
                "hr = 0x%08x, pSampleDevice = 0x%08x", hr, pSampleDevice));

        CHECK_HR(
            hr = pSrc->pTexturePriv->GetSurfaceLevel( 0, &pTexturePrivSurf),
            ::DbgMsg("CMultiVMR9Wizard::PresentImage: failed to get the 0-level surface from the private texture , "\
                "hr = 0x%08x, pPrivTextureSurf = 0x%08x", hr, pTexturePrivSurf));

        CHECK_HR(
            hr = pSampleDevice->StretchRect( lpPresInfo->lpSurf, 
                                            NULL, 
                                            pTexturePrivSurf,
                                            NULL,
                                            D3DTEXF_NONE ),
            ::DbgMsg("CMultiVMR9Wizard::PresentImage: failed to StretchRect() from the video surface to the "\
                "private texture, hr = 0x%08x", hr));

    } // try
    catch( HRESULT hr1)
    {
        hr = hr1;
    }
    RELEASE( pTexturePrivSurf );
    RELEASE( pSampleDevice );
    return hr;
}

/////////////////////// Private class CMultiVMR9_VideoSource ///////////////////////////////////////

/******************************Private*Routine******************************\
* MultiVMR9_VideoSource
*
* constructor
\**************************************************************************/
CMultiVMR9Wizard::MultiVMR9_VideoSource::MultiVMR9_VideoSource()
            : dwTag( VIDEO_SOURCE_TAG )
            , dwID( 0L )
            , dwNumBuf( 0L)
            , dwNumBufActuallyAllocated( 0L)
            , lImageWidth( 0L)
            , lImageHeight( 0L)
            , pTexturePriv( NULL )
            , ppSurface( NULL)
            , pGraph( NULL )
            , pDefaultNotify( NULL )
            , pVMR (NULL)
{
}

/******************************Private*Routine******************************\
* ~MultiVMR9_VideoSource
*
* destructor
\**************************************************************************/
CMultiVMR9Wizard::MultiVMR9_VideoSource::~MultiVMR9_VideoSource()
{
    dwID = NULL;
    dwTag = NULL;

    if( pTexturePriv   ) { pTexturePriv->Release();     pTexturePriv = NULL; }
    if( pGraph         ) { pGraph->Release();           pGraph = NULL;   }
    if( pDefaultNotify ) { pDefaultNotify->Release();   pDefaultNotify = NULL;}
    if( pVMR           ) { pVMR->Release();             pVMR = NULL; }

    DeleteSurfaces();
    lImageWidth = lImageHeight = 0L;
}

/******************************Private*Routine******************************\
* DisconnectPins
*
* Disconnects pins of VMR
\**************************************************************************/
HRESULT CMultiVMR9Wizard::MultiVMR9_VideoSource::DisconnectPins()
{
    HRESULT hr = S_OK;
    if( !pVMR )
    {
        return E_POINTER;
    }
    IEnumPins*  pEnum = NULL;
    IPin*       pPin = NULL;

    try
    {
        CHECK_HR(
            hr = pVMR->EnumPins( &pEnum ),
            ::DbgMsg("MultiVMR9_VideoSource::DisconnectPins: failed to enumerate pins, hr = 0x%08x", hr));

        hr = pEnum->Next(1, &pPin, NULL);
        while( S_OK == hr && pPin)
        {
            CHECK_HR(
                hr = pPin->Disconnect(),
                ::DbgMsg("MultiVMR9_VideoSource::DisconnectPins: failed to disconnect pin, hr = 0x%08x", hr));

            RELEASE(pPin);
            hr = pEnum->Next(1, &pPin, NULL);
        }
    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    RELEASE(pPin);
    RELEASE(pEnum);

    return hr;
}

/******************************Private*Routine******************************\
* DeleteSurfaces
*
* deletes allocated surface buffers
\**************************************************************************/
void CMultiVMR9Wizard::MultiVMR9_VideoSource::DeleteSurfaces()
{
    if( ppSurface )
    {
        for( DWORD dwS = 0; dwS<dwNumBuf; dwS++)
        {
            if( ppSurface[dwS] )
            {
                (ppSurface[dwS])->Release();
                ppSurface[dwS] = NULL;
            }
        }
        delete[] ppSurface;
        ppSurface = NULL;
    }
    dwNumBuf = 0L;
    dwNumBufActuallyAllocated = 0L;
}

/******************************Private*Routine******************************\
* AllocateSurfaceBuffer
*
* allocates buffer of dwN surfaces
\**************************************************************************/
HRESULT CMultiVMR9Wizard::MultiVMR9_VideoSource::AllocateSurfaceBuffer(
                                                        DWORD dwN )
{
    if( dwN < 1) 
    {
        return E_INVALIDARG;
    }

    DeleteSurfaces();
    dwNumBuf = dwN;
    ppSurface = new IDirect3DSurface9*[dwNumBuf];

    if( !ppSurface )
    {
        dwNumBuf = 0L;
        return E_OUTOFMEMORY;
    }

    ZeroMemory( ppSurface, dwNumBuf * sizeof(IDirect3DSurface9*));
    return S_OK;
}

/******************************Private*Routine******************************\
* SetVideoSize
*
* saves data on the video source image size
\**************************************************************************/
HRESULT CMultiVMR9Wizard::MultiVMR9_VideoSource::
                                SetVideoSize(   LONG lImageW, 
                                                LONG lImageH )
{
    if( lImageW < 1 ||
        lImageH < 1 )
    {
        ::DbgMsg("MultiVMR9_VideoSource::SetVideoSize: received invalid sizes: "\
            "image width = %ld, image height = %ld",
            lImageW, lImageH);
        return E_INVALIDARG;
    }

    lImageWidth = lImageW;
    lImageHeight = lImageH;
    return S_OK;
}

/////////////////////// Private routine ///////////////////////////////////////

/******************************Private*Routine******************************\
* Clean_
*
* clean all the data, release all interfaces
\**************************************************************************/
void CMultiVMR9Wizard::Clean_()
{
    HRESULT hr = S_OK;
    DWORD_PTR dwID = 0L;

    list<MultiVMR9_VideoSource*>::iterator it;

    while( false == m_listVideoSources.empty())
    {
        it = m_listVideoSources.begin();
        if( (MultiVMR9_VideoSource*)(*it) )
        {
            dwID = ((MultiVMR9_VideoSource*)(*it))->dwID;
            hr = Detach( dwID );
            DbgMsg( "Clean_: detaching %ld, return code 0x%08x", dwID, hr);
        }
    }

    RELEASE( m_pRenderEngine );
    RELEASE( m_pNotify );
}

/******************************Private*Routine******************************\
* GetSourceInfo_
*
* returns MultiVMR9_VideoSource associated with dwID
* 
* dwID -- sub-graph's cookie assigned in CMultiVMR9Wizard::Attach
* source -- [out] reference to MultiVMR9_VideoSource to fill
*
* Return error codes: VFW_E_NOT_FOUND -- source was not found
\**************************************************************************/
HRESULT CMultiVMR9Wizard::GetSourceInfo_(DWORD_PTR dwID, MultiVMR9_VideoSource** ppsource)
{
    HRESULT hr = S_OK;
    MultiVMR9_VideoSource *pSrc = NULL;

    if( !dwID )
    {
        return VFW_E_NOT_FOUND;
    }

    pSrc = reinterpret_cast<MultiVMR9_VideoSource*>(dwID);
    if( !pSrc )
    {
        return VFW_E_NOT_FOUND;
    }
    // check that Tag is VIDEO_SOURCE_TAG and we do not have pSrc filled with trash
    if( VIDEO_SOURCE_TAG != pSrc->dwTag )
    {
        return VFW_E_NOT_FOUND;
    }

    // ok, pSrc is a valid MultiVMR9_VideoSource; copy it to source
    *ppsource = pSrc;
    return S_OK;
}

/******************************Public*Routine******************************\
* RenderThreadProc_
*
* spins off rendering thread
*
\**************************************************************************/
HRESULT CMultiVMR9Wizard::StartRenderingThread_()
{
    HANDLE hThread = NULL;
    DWORD tid = NULL;

    if( !m_bInitialized || m_RenderThreadStatus != eNotStarted )
    {
        ::DbgMsg("CMultiVMR9Wizard::StartRenderingThread_: function called when wizard is not initialized or "\
            "render thread is already running / closed");
        return VFW_E_WRONG_STATE;
    }
    // since we initialized successfully, spin off rendering thread
    hThread = CreateThread( NULL,
                            NULL,
                            RenderThreadProc_, 
                            this, 
                            NULL, 
                            &tid);
    if( INVALID_HANDLE_VALUE == hThread )
    {
        ::DbgMsg("CMultiVMR9Wizard::Initialize: failed to create rendering thread");
        return E_UNEXPECTED;
    }

    m_RenderThreadStatus = eRunning;
    return S_OK;
}

/******************************Public*Routine******************************\
* RenderThreadProc_
*
* fires the end of the rendering thread and waits untils render thread closes
*
\**************************************************************************/
HRESULT CMultiVMR9Wizard::StopRenderingThread_()
{
    if( m_RenderThreadStatus != eRunning )
    {
        return S_FALSE;
    }

    m_RenderThreadStatus = eWaitingToStop;
    while( m_RenderThreadStatus != eFinished )
    {
        Sleep(50);
    }

    return S_OK;
}

/******************************Public*Routine******************************\
* RenderThreadProc_
*
* ThreadProc processing rendering of the Render Engine: calls for Render
*
\**************************************************************************/
DWORD WINAPI CMultiVMR9Wizard::RenderThreadProc_( LPVOID lpParameter )
{
    CMultiVMR9Wizard* This = NULL;
    IMultiVMR9RenderEngine* pRenderEngine = NULL;
    
    HRESULT hr = S_OK;

    This = (CMultiVMR9Wizard*)lpParameter;

    if( !This )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::RenderThreadProc: parameter is NULL");
        return 0;
    }
    This->AddRef();

    hr = This->GetRenderEngine( &pRenderEngine );
    if( FAILED(hr) || !pRenderEngine )
    {
        ::DbgMsg("CMultiVMR9RenderEngine::RenderThreadProc: cannot find IMultiVMR9RenderEngine");
        RELEASE( pRenderEngine );
        RELEASE( This );
        return 0;
    }

    while ( true ) 
    {
        hr = pRenderEngine->Render();
        // check if we have to exit
        {
            CAutoLock Lock(&(This->m_ObjectLock));
            if( eWaitingToStop == This->m_RenderThreadStatus )
            {
                break;
            }
        }
        Sleep(10);
    } // while true

    {
        CAutoLock Lock(&(This->m_ObjectLock));
        This->m_RenderThreadStatus = eFinished;
    }

    RELEASE( This );
    RELEASE( pRenderEngine );

    return 0;
}

