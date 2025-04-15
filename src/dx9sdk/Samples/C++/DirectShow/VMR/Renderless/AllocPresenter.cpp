//------------------------------------------------------------------------------
// File: allocpresenter.cpp
//
// Desc: DirectShow sample code - Custom allocator-presenter
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"

#include <math.h>


template <typename T>
__inline void INITDDSTRUCT(T& dd)
{
    ZeroMemory(&dd, sizeof(dd));
    dd.dwSize = sizeof(dd);
}


/*****************************Private*Routine******************************\
* CreateDefaultAllocatorPresenter
*
\**************************************************************************/
HRESULT
CMovie::CreateDefaultAllocatorPresenter()
{
    HRESULT hr = S_OK;

    __try {
        CHECK_HR(hr = CoCreateInstance(CLSID_AllocPresenter, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       IID_IVMRSurfaceAllocator,
                                       (LPVOID*)&m_lpDefSA));

        CHECK_HR(hr = m_lpDefSA->QueryInterface(IID_IVMRImagePresenter,
            (LPVOID*)&m_lpDefIP));

        CHECK_HR(hr = m_lpDefSA->QueryInterface(IID_IVMRWindowlessControl,
            (LPVOID*)&m_lpDefWC));

        CHECK_HR(hr = m_lpDefWC->SetVideoClippingWindow(m_hwndApp));
        CHECK_HR(hr = m_lpDefSA->AdviseNotify(this));
        }
    __finally {

        if(FAILED(hr)) {
            RELEASE(m_lpDefWC);
            RELEASE(m_lpDefIP);
            RELEASE(m_lpDefSA);
            }
    }

    return hr;
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
    if(riid == IID_IVMRSurfaceAllocator)
    {
        return GetInterface((IVMRSurfaceAllocator*)this, ppv);
    }
    else if(riid == IID_IVMRImagePresenter)
    {
        return GetInterface((IVMRImagePresenter*)this, ppv);
    }

    return CUnknown::NonDelegatingQueryInterface(riid,ppv);
}


//////////////////////////////////////////////////////////////////////////////
//
// IVMRSurfaceAllocator
//
//////////////////////////////////////////////////////////////////////////////

/******************************Public*Routine******************************\
* AllocateSurfaces
*
\**************************************************************************/
STDMETHODIMP
CMovie::AllocateSurface(
    DWORD_PTR dwUserID,
    VMRALLOCATIONINFO* lpAllocInfo,
    DWORD* lpdwBuffer,
    LPDIRECTDRAWSURFACE7* lplpSurface
    )
{
    if (m_lpDefSA)
    {
        return m_lpDefSA->AllocateSurface(dwUserID, lpAllocInfo,
                                          lpdwBuffer, lplpSurface);
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* FreeSurfaces()
*
\**************************************************************************/
STDMETHODIMP
CMovie::FreeSurface(
    DWORD_PTR dwUserID
    )
{
    if (m_lpDefSA)
    {
        return m_lpDefSA->FreeSurface(dwUserID);
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* PrepareSurface
*
\**************************************************************************/
STDMETHODIMP
CMovie::PrepareSurface(
    DWORD_PTR dwUserID,
    LPDIRECTDRAWSURFACE7 lplpSurface,
    DWORD dwSurfaceFlags
    )
{
    if (m_lpDefSA)
    {
        return m_lpDefSA->PrepareSurface(dwUserID, lplpSurface, dwSurfaceFlags);
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* AdviseNotify
*
\**************************************************************************/
STDMETHODIMP
CMovie::AdviseNotify(
    IVMRSurfaceAllocatorNotify* lpIVMRSurfAllocNotify
    )
{
    if (m_lpDefSA)
    {
        return m_lpDefSA->AdviseNotify(lpIVMRSurfAllocNotify);
    }
    else
        return E_POINTER;
}


//////////////////////////////////////////////////////////////////////////////
//
// IVMRSurfaceAllocatorNotify
//
//////////////////////////////////////////////////////////////////////////////

/******************************Public*Routine******************************\
* AdviseSurfaceAllocator
*
\**************************************************************************/
STDMETHODIMP
CMovie::AdviseSurfaceAllocator(
    DWORD_PTR dwUserID,
    IVMRSurfaceAllocator* lpIVRMSurfaceAllocator
    )
{
    if (m_lpDefSAN)
    {
        return m_lpDefSAN->AdviseSurfaceAllocator(dwUserID, lpIVRMSurfaceAllocator);
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* SetDDrawDevice
*
\**************************************************************************/
STDMETHODIMP
CMovie::SetDDrawDevice(LPDIRECTDRAW7 lpDDrawDevice,HMONITOR hMonitor)
{
    if (m_lpDefSAN)
    {
        return m_lpDefSAN->SetDDrawDevice(lpDDrawDevice, hMonitor);
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* ChangeDDrawDevice
*
\**************************************************************************/
STDMETHODIMP
CMovie::ChangeDDrawDevice(LPDIRECTDRAW7 lpDDrawDevice,HMONITOR hMonitor)
{
    if (m_lpDefSAN)
    {
        return m_lpDefSAN->ChangeDDrawDevice(lpDDrawDevice, hMonitor);
    }
    else
        return E_POINTER;
}


/*****************************Private*Routine******************************\
* DDSurfEnumFunc
*
\**************************************************************************/
HRESULT WINAPI
DDSurfEnumFunc(
    LPDIRECTDRAWSURFACE7 pdds,
    DDSURFACEDESC2* pddsd,
    void* lpContext
    )
{
    LPDIRECTDRAWSURFACE7* ppdds = (LPDIRECTDRAWSURFACE7*)lpContext;

    DDSURFACEDESC2 ddsd;
    INITDDSTRUCT(ddsd);

    HRESULT hr = pdds->GetSurfaceDesc(&ddsd);
    if(SUCCEEDED(hr))
    {
        if(ddsd.ddsCaps.dwCaps & DDSCAPS_PRIMARYSURFACE)
        {
            *ppdds = pdds;
            return DDENUMRET_CANCEL;
        }
    }

    pdds->Release();
    return DDENUMRET_OK;
}


/*****************************Private*Routine******************************\
* OnSetDDrawDevice
*
\**************************************************************************/
HRESULT
CMovie::OnSetDDrawDevice(
    LPDIRECTDRAW7 pDD,
    HMONITOR hMon
    )
{
    HRESULT hr = S_OK;

    RELEASE(m_pddsRenderT);
    RELEASE(m_pddsPriText);
    RELEASE(m_pddsPrimary);

    __try
    {

        DDSURFACEDESC2 ddsd;  // A surface description structure
        INITDDSTRUCT(ddsd);
        ddsd.dwFlags = DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

        CHECK_HR(hr = pDD->EnumSurfaces(DDENUMSURFACES_DOESEXIST | DDENUMSURFACES_ALL,
                                        &ddsd,
                                        &m_pddsPrimary,
                                        DDSurfEnumFunc));
        if(!m_pddsPrimary)
        {
            hr = E_FAIL;
            __leave;
        }

        MONITORINFO miInfo;
        miInfo.cbSize = sizeof(miInfo);
        GetMonitorInfo(hMon, &miInfo);

        INITDDSTRUCT(ddsd);
        ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
        ddsd.dwWidth = (miInfo.rcMonitor.right - miInfo.rcMonitor.left);
        ddsd.dwHeight = (miInfo.rcMonitor.bottom - miInfo.rcMonitor.top);

        CHECK_HR(hr = pDD->CreateSurface(&ddsd, &m_pddsPriText, NULL));
        CHECK_HR(hr = pDD->CreateSurface(&ddsd, &m_pddsRenderT, NULL));
    }
    __finally
    {
        if(FAILED(hr))
        {
            RELEASE(m_pddsRenderT);
            RELEASE(m_pddsPriText);
            RELEASE(m_pddsPrimary);
        }
    }

    return hr;
}


/******************************Public*Routine******************************\
* RestoreDDrawSurfaces
*
\**************************************************************************/
STDMETHODIMP CMovie::RestoreDDrawSurfaces()
{
    if (m_lpDefSAN)
    {
        return m_lpDefSAN->RestoreDDrawSurfaces();
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* RestoreDDrawSurfaces
*
\**************************************************************************/
STDMETHODIMP
CMovie::NotifyEvent(LONG EventCode, LONG_PTR lp1, LONG_PTR lp2)
{
    if (m_lpDefSAN)
    {
        return m_lpDefSAN->NotifyEvent(EventCode, lp1, lp2);
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* SetBorderColor
*
\**************************************************************************/
STDMETHODIMP
CMovie::SetBorderColor(
    COLORREF clr
    )
{
    if (m_lpDefSAN)
    {
        return m_lpDefSAN->SetBorderColor(clr);
    }
    else
        return E_POINTER;
}


//////////////////////////////////////////////////////////////////////////////
//
// IVMRImagePresenter
//
//////////////////////////////////////////////////////////////////////////////

/******************************Public*Routine******************************\
* StartPresenting()
*
\**************************************************************************/
STDMETHODIMP
CMovie::StartPresenting(DWORD_PTR dwUserID)
{
    if (m_lpDefIP)
    {
        return m_lpDefIP->StartPresenting(dwUserID);
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* StopPresenting()
*
\**************************************************************************/
STDMETHODIMP
CMovie::StopPresenting(DWORD_PTR dwUserID)
{
    if (m_lpDefIP)
    {
        return m_lpDefIP->StopPresenting(dwUserID);
    }
    else
        return E_POINTER;
}


/******************************Public*Routine******************************\
* PresentImage
*
\**************************************************************************/
STDMETHODIMP
CMovie::PresentImage(
    DWORD_PTR dwUserID,
    VMRPRESENTATIONINFO* lpPresInfo
    )
{
#if 0
    LPDIRECTDRAWSURFACE7 lpSurface = lpPresInfo->lpSurf;
    const REFERENCE_TIME rtNow = lpPresInfo->rtStart;
    const DWORD dwSurfaceFlags = lpPresInfo->dwFlags;

    if(m_iDuration > 0)
    {
        HRESULT hr;
        RECT rs, rd;
        DDSURFACEDESC2 ddsdV;

        INITDDSTRUCT(ddsdV);
        hr = lpSurface->GetSurfaceDesc(&ddsdV);

        DDSURFACEDESC2 ddsdP;
        INITDDSTRUCT(ddsdP);
        hr = m_pddsPriText->GetSurfaceDesc(&ddsdP);

        FLOAT fPos = (FLOAT)m_iDuration / 30.0F;
        FLOAT fPosInv = 1.0F - fPos;

        SetRect(&rs, 0, 0,
            MulDiv((int)ddsdV.dwWidth, 30 - m_iDuration, 30),
            ddsdV.dwHeight);

        SetRect(&rd, 0, 0,
            MulDiv((int)ddsdP.dwWidth, 30 - m_iDuration, 30),
            ddsdP.dwHeight);

        hr = m_pddsRenderT->Blt(&rd, lpSurface,
            &rs, DDBLT_WAIT, NULL);

        SetRect(&rs, 0, 0,
            MulDiv((int)ddsdP.dwWidth, m_iDuration, 30),
            ddsdP.dwHeight);

        SetRect(&rd,
            (int)ddsdP.dwWidth - MulDiv((int)ddsdP.dwWidth, m_iDuration, 30),
            0,
            ddsdP.dwWidth,
            ddsdP.dwHeight);

        hr = m_pddsRenderT->Blt(&rd, m_pddsPriText,
            &rs, DDBLT_WAIT, NULL);

        //
        // need to wait for VBlank before blt-ing
        //
        {
            LPDIRECTDRAW lpdd;
            hr = m_pddsPrimary->GetDDInterface((LPVOID*)&lpdd);
            if(SUCCEEDED(hr))
            {
                DWORD dwScanLine;
                for(; ;)
                {
                    hr = lpdd->GetScanLine(&dwScanLine);

                    if(hr ==  DDERR_VERTICALBLANKINPROGRESS)
                    {
                        break;
                    }

                    if(FAILED(hr))
                    {
                        break;
                    }

                    if((LONG)dwScanLine>= rd.top)
                    {
                        if((LONG)dwScanLine <= rd.bottom)
                        {
                            continue;
                        }
                    }

                    break;
                }

                RELEASE(lpdd);
            }
        }

        hr = m_pddsPrimary->Blt(NULL, m_pddsRenderT, NULL, DDBLT_WAIT, NULL);

        m_iDuration--;
        if(m_iDuration == 0 && (ddsdV.ddsCaps.dwCaps & DDSCAPS_OVERLAY))
        {
            // need to get the color key visible again.
            InvalidateRect(m_hwndApp, NULL, FALSE);
        }
        return hr;
    }
    else
    {
        return m_lpDefIP->PresentImage(dwUserID, lpPresInfo);
    }
#endif


    if (m_lpDefIP)
    {
        return m_lpDefIP->PresentImage(dwUserID, lpPresInfo);
    }
    else
        return E_POINTER;
}


