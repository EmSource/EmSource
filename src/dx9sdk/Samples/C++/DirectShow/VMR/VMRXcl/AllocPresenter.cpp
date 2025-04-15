//----------------------------------------------------------------------------
//  File:   AllocPresenter.cpp
//
//  Desc:   DirectShow sample code
//          Implementation of user-provided allocator-presenter for VMR
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "project.h"

#include <math.h>
#include "D3DTextr.h"
#include "utils.h"

#pragma warning(disable:4702) //disable "unreachable code" warning

#ifndef __INITDDSTRUCT_DEFINED
#define __INITDDSTRUCT_DEFINED

template <typename T>
__inline void INITDDSTRUCT(T& dd)
{
    ZeroMemory(&dd, sizeof(dd));
    dd.dwSize = sizeof(dd);
}
#endif


//----------------------------------------------------------------------------
// CreateDefaultAllocatorPresenter
//
// creates user-provides allocator presenter
// 
// Usually you have to actually override several functions of AllocatorPresenter
// For the rest, QI IVMRImagePresenter and call default functions
//----------------------------------------------------------------------------
HRESULT
CMovie::CreateDefaultAllocatorPresenter(
    LPDIRECTDRAW7 lpDD,
    LPDIRECTDRAWSURFACE7 lpPS
    )
{
    HRESULT hr = S_OK;
    IVMRImagePresenterExclModeConfig* lpConfig = NULL;

    __try {
        // for exclusive mode, we do need AllocPresenterDDXclMode of IVMRSurfaceAllocator
        CHECK_HR(hr = CoCreateInstance(CLSID_AllocPresenterDDXclMode, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       __uuidof(IVMRSurfaceAllocator),
                                       (LPVOID*)&m_lpDefSA));

        CHECK_HR(hr = m_lpDefSA->QueryInterface(__uuidof(IVMRImagePresenterExclModeConfig),
                                                (LPVOID*)&lpConfig));

        CHECK_HR(hr = lpConfig->SetRenderingPrefs(RenderPrefs_ForceOffscreen));
        
        // this sets exclusive mode
        CHECK_HR(hr = lpConfig->SetXlcModeDDObjAndPrimarySurface(lpDD, lpPS));

        CHECK_HR(hr = m_lpDefSA->QueryInterface(__uuidof(IVMRImagePresenter),
                                                (LPVOID*)&m_lpDefIP));

        CHECK_HR(hr = m_lpDefSA->QueryInterface(__uuidof(IVMRWindowlessControl),
                                                (LPVOID*)&m_lpDefWC));

        CHECK_HR(hr = m_lpDefWC->SetVideoClippingWindow(m_hwndApp));
        CHECK_HR(hr = m_lpDefSA->AdviseNotify(this));
        ShowWindow( m_hwndApp, SW_SHOW);
    }
    __finally {

        RELEASE(lpConfig);

        if (FAILED(hr)) {
            RELEASE(m_lpDefWC);
            RELEASE(m_lpDefIP);
            RELEASE(m_lpDefSA);
        }
    }

    return hr;
}


//----------------------------------------------------------------------------
// NonDelegatingQueryInterface
//
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::NonDelegatingQueryInterface(
    REFIID riid,
    void** ppv
    )
{
    if (riid == __uuidof(IVMRSurfaceAllocator)) {
        return GetInterface((IVMRSurfaceAllocator*)this, ppv);
    }
    else if (riid == __uuidof(IVMRImagePresenter)) {
        return GetInterface((IVMRImagePresenter*)this, ppv);
    }
    else if(riid == __uuidof(IAMGraphBuilderCallback)) {
        return GetInterface((IAMGraphBuilderCallback*)this, ppv);
    }
    return CUnknown::NonDelegatingQueryInterface(riid,ppv);
}

//////////////////////////////////////////////////////////////////////////////
//
// IAMGraphBuilderCallback-overriden functions
// this interface allows to verify which filters are to be added to
// the graph by GraphBuilder, so we can prevent unwanted instances of
// "default" VMRs
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// SelectedFilter
//
//----------------------------------------------------------------------------
STDMETHODIMP CMovie::SelectedFilter(IMoniker *pMon)
{
    HRESULT hr = S_OK;
    IBindCtx * pBCtx = NULL;
    IBaseFilter * pBf = NULL;
    IUnknown *pUnk = NULL;

    if( !pMon )
        return E_POINTER;

    hr = CreateBindCtx(0, (LPBC*)&pBCtx );
    if( !pBCtx || FAILED(hr))
        return E_UNEXPECTED;

    hr = pMon->BindToObject( pBCtx, NULL, __uuidof(IBaseFilter), (void**)&pBf );
    RELEASE( pBCtx );
    if( FAILED(hr) || !pBf )
    {
        return E_UNEXPECTED;
    }

    // query some i-face unique for VMR7
    hr = pBf->QueryInterface( __uuidof(IVMRFilterConfig), (void**)&pUnk );
    if( FAILED( hr ) || !pUnk )
    {
        // this is not VMR7; is this old video renderer?
        RELEASE( pUnk );
        hr = pBf->QueryInterface( __uuidof(IBasicVideo), (void**)&pUnk );
        if( FAILED( hr ) || !pUnk )
        {
            // this is not VMR7 or old renderer: approve
            RELEASE( pUnk );
            RELEASE( pBf );
            return S_OK;
        }
        else
        {
            // this is an old renderer: reject
            RELEASE( pUnk );
            RELEASE( pBf );
            return E_FAIL;
        }
    } // if
    else
    {
        RELEASE( pUnk );
        // this is VMR7: let's see if this is OUR VMR7
        if( pBf == this->m_pBF )
        {
            // approve
            RELEASE( pBf );
            return S_OK;
        }
        else
        {
            // reject 
            RELEASE( pBf );
            return E_FAIL;
        }
    }

    // we should never hit this point
    return E_UNEXPECTED;
}

//----------------------------------------------------------------------------
// CreatedFilter
//
//----------------------------------------------------------------------------
STDMETHODIMP CMovie::CreatedFilter(IBaseFilter *pBf)
{
    HRESULT hr = S_OK;
    IUnknown *pUnk = NULL;

    // query some i-face unique for VMR7
    hr = pBf->QueryInterface( __uuidof(IVMRFilterConfig), (void**)&pUnk );
    if( FAILED( hr ) || !pUnk )
    {
        // this is not VMR7; is this old video renderer?
        RELEASE( pUnk );
        hr = pBf->QueryInterface( __uuidof(IBasicVideo), (void**)&pUnk );
        if( FAILED( hr ) || !pUnk )
        {
            // this is not VMR7 or old renderer: approve
            RELEASE( pUnk );
            return S_OK;
        }
        else
        {
            // this is an old renderer: reject
            RELEASE( pUnk );
            return E_FAIL;
        }
    } // if
    else
    {
        RELEASE( pUnk );
        // this is VMR7: let's see if this is OUR VMR7
        if( pBf == this->m_pBF )
        {
            // approve
            return S_OK;
        }
        else
        {
            // reject 
            return E_FAIL;
        }
    }

    // we should never hit this point
    return E_UNEXPECTED;
}


//////////////////////////////////////////////////////////////////////////////
//
// IVMRSurfaceAllocator-overriden functions
//
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// AllocateSurfaces
//
// call default AllocateSurface
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::AllocateSurface(
    DWORD_PTR dwUserID,
    VMRALLOCATIONINFO* lpAllocInfo,
    DWORD* lpdwBuffer,
    LPDIRECTDRAWSURFACE7* lplpSurface
    )
{
    HRESULT hr = m_lpDefSA->AllocateSurface(dwUserID, lpAllocInfo,
                                            lpdwBuffer, lplpSurface);
    if( SUCCEEDED(hr))
    {
        m_lpSurf = *lplpSurface;
    }
    return hr;
}


//----------------------------------------------------------------------------
// FreeSurfaces()
//
// Call default FreeSurface
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::FreeSurface(
    DWORD_PTR dwUserID
    )
{
    HRESULT hr = m_lpDefSA->FreeSurface(dwUserID);

    if( SUCCEEDED(hr))
    {
        m_lpSurf = NULL;
    }
    return hr;
}


//----------------------------------------------------------------------------
// PrepareSurface
//
// call default PrepareSurface
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::PrepareSurface(
    DWORD_PTR dwUserID,
    LPDIRECTDRAWSURFACE7 lplpSurface,
    DWORD dwSurfaceFlags
    )
{
    return m_lpDefSA->PrepareSurface(dwUserID, lplpSurface, dwSurfaceFlags);
}


//----------------------------------------------------------------------------
// AdviseNotify
//
// call default AdviseNotify
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::AdviseNotify(
    IVMRSurfaceAllocatorNotify* lpIVMRSurfAllocNotify
    )
{
    return m_lpDefSA->AdviseNotify(lpIVMRSurfAllocNotify);
}


//////////////////////////////////////////////////////////////////////////////
//
// IVMRSurfaceAllocatorNotify-overriden functions
//
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// AdviseSurfaceAllocator
//
// standard AdviseSurfaceAllocator
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::AdviseSurfaceAllocator(
    DWORD_PTR dwUserID,
    IVMRSurfaceAllocator* lpIVRMSurfaceAllocator
    )
{
    return m_lpDefSAN->AdviseSurfaceAllocator(dwUserID, lpIVRMSurfaceAllocator);
}


//----------------------------------------------------------------------------
// SetDDrawDevice
//
// standard SetDDrawDevice
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::SetDDrawDevice(LPDIRECTDRAW7 lpDDrawDevice,HMONITOR hMonitor)
{
    return m_lpDefSAN->SetDDrawDevice(lpDDrawDevice, hMonitor);
}


//----------------------------------------------------------------------------
// ChangeDDrawDevice
//
// standard ChangeDDrawDevice
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::ChangeDDrawDevice(LPDIRECTDRAW7 lpDDrawDevice,HMONITOR hMonitor)
{
    return m_lpDefSAN->ChangeDDrawDevice(lpDDrawDevice, hMonitor);
}


//----------------------------------------------------------------------------
// RestoreDDrawSurfaces
//
// standard RestoreDDrawSurfaces
//----------------------------------------------------------------------------
STDMETHODIMP CMovie::RestoreDDrawSurfaces()
{
    HRESULT hr = S_OK;
    __try {
        CHECK_HR( hr = m_AlphaBlt->RestoreDDrawSurfaces() );
        CHECK_HR( hr = m_lpDefSAN->RestoreDDrawSurfaces() );
    }
    __finally {
    
    }

    return hr;
}


//----------------------------------------------------------------------------
// NotifyEvent
//
// standard NotifyEvent
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::NotifyEvent(LONG EventCode, LONG_PTR lp1, LONG_PTR lp2)
{
    return m_lpDefSAN->NotifyEvent(EventCode, lp1, lp2);
}


//----------------------------------------------------------------------------
// SetBorderColor
//
// default SetBorderColor
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::SetBorderColor(
    COLORREF clr
    )
{
    return m_lpDefSAN->SetBorderColor(clr);
}


//////////////////////////////////////////////////////////////////////////////
//
// IVMRImagePresenter overriden functions
// we perform all user customization here
//
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// StartPresenting()
//
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::StartPresenting(DWORD_PTR dwUserID)
{
    return m_lpDefIP->StartPresenting(dwUserID);
}


//----------------------------------------------------------------------------
// StopPresenting()
//
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::StopPresenting(DWORD_PTR dwUserID)
{
    return m_lpDefIP->StopPresenting(dwUserID);
}


//----------------------------------------------------------------------------
// PresentImage
//
// Here all the fun happens. lpPresInfo contains surface with current video image
// Call m_AlphaBlt->AlphaBlt to perform all the necessary transformation
//----------------------------------------------------------------------------
STDMETHODIMP
CMovie::PresentImage(
    DWORD_PTR dwUserID,
    VMRPRESENTATIONINFO* lpPresInfo
    )
{
    // clear the background
    DDBLTFX ddFX;
    INITDDSTRUCT(ddFX);

    RECT rcS = {0, 0, 640, 480};
    RECT rcD = {128, 96, 512, 384};
    RECT rcDt ={128, 0, 512, 288};

    m_lpDefWC->GetVideoPosition(&rcS, NULL);

    if( g_ss.bShowTwist )
    {
        m_AlphaBlt->AlphaBlt(&rcDt, lpPresInfo->lpSurf, &rcS, 0xFF);
    }
    else
    {
        m_AlphaBlt->AlphaBlt(&rcD, lpPresInfo->lpSurf, &rcS, 0xFF);
    }

    m_lpSurf->Flip(NULL,0);

    if( g_ss.bShowStatistics && m_Qp)
    {
        // call IQualProp functions here to get performance statistics
        GetPerformance();
    }

    // Show the scene
    m_pDDObject.GetFB()->Flip(NULL, /*DDFLIP_WAIT*/ 0);

    return S_OK;
}


//----------------------------------------------------------------------------
//  GetPerformance
//
//  Calls IQualProp::get_AvgFrameRate   
//  every 25 frames (to not overload VMR with senseless calculations)
//  and saves this value to g_ss, global SceneSettings structure
// 
//----------------------------------------------------------------------------
void 
CMovie::GetPerformance()
{
    static int nCounter = 0;
    static int nAvgFrameRate = 0;
    TCHAR szFrameRate[MAX_PATH];
    
    nCounter++;
    if( 25 == nCounter )
    {
        m_Qp->get_AvgFrameRate( &nAvgFrameRate);
        nCounter = 0;
    }

    _stprintf(szFrameRate, TEXT("FPS: %f  \0"), (float)nAvgFrameRate/100.0);
    _tcsncpy(g_ss.achFPS, szFrameRate, MAX_PATH);
}

