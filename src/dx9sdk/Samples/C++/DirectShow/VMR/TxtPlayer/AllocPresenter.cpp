//------------------------------------------------------------------------------
// File: allocpresenter.cpp
//
// Desc: DirectShow sample code - Custom Allocator Presenter for VMR sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"

#include <math.h>

#include "alloclib.h"


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
* AllocateSurface
*
\**************************************************************************/
STDMETHODIMP
CMovie::AllocateSurface(
                           DWORD_PTR pdwUserID,
                           VMRALLOCATIONINFO *w,
                           DWORD* lpdwBuffer,
                           LPDIRECTDRAWSURFACE7* lplpSurface
                           )
{
    HRESULT hr = S_OK;

    if (!w) 
    {
        return E_POINTER;
    }

    DWORD dwFlags               = w->dwFlags;
    LPBITMAPINFOHEADER lpHdr    = w->lpHdr;
    LPDDPIXELFORMAT lpPixFmt    = w->lpPixFmt;
    LPSIZE lpAspectRatio        = &w->szAspectRatio;
    DWORD dwMinBuffers          = w->dwMinBuffers;
    DWORD dwMaxBuffers          = w->dwMaxBuffers;
    VIDEOINFO vi;
    DDSURFACEDESC2 ddsdDisplay;

    if (!lpHdr) 
    {
        return E_POINTER;
    }

    const DWORD AMAP_INVALID_FLAGS = (DWORD) ~(AMAP_PIXELFORMAT_VALID | AMAP_3D_TARGET |
                                       AMAP_ALLOW_SYSMEM | AMAP_FORCE_SYSMEM |
                                       AMAP_DIRECTED_FLIP | AMAP_DXVA_TARGET);

    if (dwFlags & AMAP_INVALID_FLAGS) 
    {
        return E_INVALIDARG;
    }

    const DWORD AMAP_SYSMEM_FLAGS = (AMAP_ALLOW_SYSMEM | AMAP_FORCE_SYSMEM);
    if (AMAP_SYSMEM_FLAGS == (dwFlags & AMAP_SYSMEM_FLAGS)) 
    {
        return E_INVALIDARG;
    }

    if (!lpAspectRatio) 
    {
        return E_POINTER;
    }

    if (!lplpSurface) 
    {
        return E_POINTER;
    }

    if (!lpdwBuffer) 
    {
        return E_POINTER;
    }

    if (dwMinBuffers == 0 || dwMaxBuffers == 0) 
    {
        return E_INVALIDARG;
    }

    if (dwMinBuffers > dwMaxBuffers) 
    {
        return E_INVALIDARG;
    }

    if (dwMaxBuffers > 16) 
    {
        return E_INVALIDARG;
    }

    if (dwFlags & AMAP_PIXELFORMAT_VALID) 
    {
        if (!lpPixFmt) 
        {
            return E_POINTER;
        }
    }
    else 
    {
        lpPixFmt = NULL;
    }

    if (lpAspectRatio->cx < 1 || lpAspectRatio->cy < 1) 
    {
        return E_INVALIDARG;
    }

    if (dwFlags & AMAP_3D_TARGET) 
    {

        CopyMemory(&vi.bmiHeader, lpHdr, lpHdr->biSize);
        lpHdr = &vi.bmiHeader;

        if (dwFlags & (AMAP_FORCE_SYSMEM | AMAP_ALLOW_SYSMEM)) 
        {
            return E_INVALIDARG;
        }

        if (lpHdr->biCompression == BI_RGB && lpHdr->biBitCount == 0) 
        {
            ZeroMemory( &ddsdDisplay, sizeof(DDSURFACEDESC2));
            ddsdDisplay.dwSize = sizeof(DDSURFACEDESC2);

            m_lpDDObj->GetDisplayMode( &ddsdDisplay );

            lpHdr->biBitCount = (unsigned short)(ddsdDisplay.ddpfPixelFormat.dwRGBBitCount);
            lpHdr->biCompression = ddsdDisplay.ddpfPixelFormat.dwFourCC;

        }
    }

    hr = AllocateSurfaceWorker( dwFlags, 
                                lpHdr, 
                                lpPixFmt, 
                                lpAspectRatio,
                                dwMinBuffers, 
                                dwMaxBuffers,
                                lpdwBuffer, 
                                lplpSurface,
                                &ddsdDisplay);

    if( SUCCEEDED(hr))
    {
        m_VideoAR = *lpAspectRatio;

        m_VideoSize.cx = abs(lpHdr->biWidth);
        m_VideoSize.cy = abs(lpHdr->biHeight);

        SetRect(&m_rcDst, 0, 0, m_VideoSize.cx, m_VideoSize.cy);
        m_rcSrc = m_rcDst;

        hr = PaintDDrawSurfaceBlack(m_lpDDTexture);

        *lplpSurface = m_lpDDTexture;
        *lpdwBuffer = 1;
    }

    return hr;

}

HRESULT
CMovie::AllocateSurfaceWorker(
                                    DWORD dwFlags,
                                    LPBITMAPINFOHEADER lpHdr,
                                    LPDDPIXELFORMAT lpPixFmt,
                                    LPSIZE lpAspectRatio,
                                    DWORD dwMinBackBuffers,
                                    DWORD dwMaxBackBuffers,
                                    DWORD* lpdwBackBuffer,
                                    LPDIRECTDRAWSURFACE7* lplpSurface,
                                    DDSURFACEDESC2* pddsdDisplay    )
{

    if (!lpHdr) 
    {
        return E_INVALIDARG;
    }

    if( !pddsdDisplay )
    {
        return E_INVALIDARG;
    }

    HRESULT hr = E_FAIL;
    LPDIRECTDRAWSURFACE7 lpSurface7 = NULL;

    DDSURFACEDESC2 ddsd;
    INITDDSTRUCT(ddsd);

    DDCAPS_DX7 hwCaps;
    ZeroMemory( &hwCaps, sizeof(DDCAPS_DX7));
    hwCaps.dwSize = sizeof(DDCAPS_DX7);
    m_lpDDObj->GetCaps( &hwCaps, NULL );

    bool bCanBltFourCCSysMem = false;
    BOOL bStretchCapsOk = TRUE;

    if( hwCaps.dwSVBCaps & DDCAPS_BLTFOURCC )
    {
        if (hwCaps.dwSVBCaps & DDCAPS_BLTSTRETCH)
        {
            const DWORD caps = DDFXCAPS_BLTSHRINKX | 
                                DDFXCAPS_BLTSHRINKX  |
                                DDFXCAPS_BLTSTRETCHX | 
                                DDFXCAPS_BLTSTRETCHY;
            if( (hwCaps.dwSVBFXCaps & caps) == caps )
            {
                bCanBltFourCCSysMem = true;
            }
        }
    }


    ddsd.dwWidth = abs(lpHdr->biWidth);
    ddsd.dwHeight = abs(lpHdr->biHeight);

    if (lpPixFmt) 
    {
        ddsd.ddpfPixelFormat = *lpPixFmt;
    }
    else 
    {
        ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);

        if (lpHdr->biCompression <= BI_BITFIELDS &&
            pddsdDisplay->ddpfPixelFormat.dwRGBBitCount <= lpHdr->biBitCount)
        {
            ddsd.ddpfPixelFormat.dwFourCC = BI_RGB;
            ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
            ddsd.ddpfPixelFormat.dwRGBBitCount = lpHdr->biBitCount;

            if (dwFlags & AMAP_3D_TARGET) 
            {
                ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
            }
            // Store the masks in the DDSURFACEDESC
            const DWORD *pBitMasks = NULL;
            if( lpHdr->biCompression == BI_RGB )
            {
                if( 15 == lpHdr->biBitCount )
                    pBitMasks = bits555;
                else
                    pBitMasks = bits888;
            }
            if( !pBitMasks )
                return E_FAIL;

            ddsd.ddpfPixelFormat.dwRBitMask = pBitMasks[0];
            ddsd.ddpfPixelFormat.dwGBitMask = pBitMasks[1];
            ddsd.ddpfPixelFormat.dwBBitMask = pBitMasks[2];
        }
        else if (lpHdr->biCompression > BI_BITFIELDS)
        {
            ddsd.ddpfPixelFormat.dwFourCC = lpHdr->biCompression;
            ddsd.ddpfPixelFormat.dwFlags = DDPF_FOURCC;
            ddsd.ddpfPixelFormat.dwYUVBitCount = lpHdr->biBitCount;
        }
        else
        {
            return E_FAIL;
        }
    }

    if (dwFlags & AMAP_FORCE_SYSMEM) 
    {

	    if (lpHdr->biCompression > BI_BITFIELDS && (false == bCanBltFourCCSysMem) ) 
        {
            return VFW_E_DDRAW_CAPS_NOT_SUITABLE;
	    }

        if (lpHdr->biCompression <= BI_BITFIELDS &&
            pddsdDisplay->ddpfPixelFormat.dwRGBBitCount != lpHdr->biBitCount) 
        {
            return DDERR_INCOMPATIBLEPRIMARY;
        }

        hr = AllocateOffscreenSurface(  &m_lpDDTexture, 
                                        AMAP_FORCE_SYSMEM, 
                                        &ddsd,
                                        dwMinBackBuffers, 
                                        dwMaxBackBuffers,
                                        lpdwBackBuffer, 
                                        FALSE);
    }
    else 
    {
        // figure out if we can stretchBlt
        {
            DWORD caps = 0;
            const DWORD dwFXCaps =  DDFXCAPS_BLTSHRINKX | 
                                    DDFXCAPS_BLTSHRINKX  |
                                    DDFXCAPS_BLTSTRETCHX | 
                                    DDFXCAPS_BLTSTRETCHY;
            if( lpHdr->biCompression <= BI_BITFIELDS )
            {
                caps = DDCAPS_BLTSTRETCH;
            }
            else
            {
                caps = DDCAPS_BLTFOURCC | DDCAPS_BLTSTRETCH;
            }
            bStretchCapsOk &= ((caps & hwCaps.dwCaps) == caps);
            bStretchCapsOk &= ((dwFXCaps & hwCaps.dwFXCaps) == dwFXCaps);
        }


        hr = AllocateOverlaySurface(    &m_lpDDTexture, 
                                        dwFlags, 
                                        &ddsd,
                                        dwMinBackBuffers, 
                                        dwMaxBackBuffers, 
                                        lpdwBackBuffer);
        if (hr != DD_OK) 
        {

            if (lpHdr->biCompression > BI_BITFIELDS) 
            {
                if( !bStretchCapsOk ) 
                {
                    return VFW_E_DDRAW_CAPS_NOT_SUITABLE;
                }
            }
            else 
            {
                //LPBITMAPINFOHEADER lpMon = &m_lpCurrMon->DispInfo.bmiHeader;
                if (lpHdr->biBitCount != pddsdDisplay->ddpfPixelFormat.dwRGBBitCount) 
                {
                    return DDERR_INCOMPATIBLEPRIMARY;
                }

                if (lpHdr->biCompression != pddsdDisplay->ddpfPixelFormat.dwFourCC) 
                {
                    if (lpHdr->biBitCount != 32) 
                    {
                        return DDERR_INCOMPATIBLEPRIMARY;
                    }
                    else 
                    {
                        OutputDebugString( TEXT("RGB32 should have BI_BITFIELDS set") );
                    }
                }
            }


            if( bStretchCapsOk ) 
            {
                hr = AllocateOffscreenSurface(  &m_lpDDTexture, 
                                                dwFlags, 
                                                &ddsd,
                                                dwMinBackBuffers, 
                                                dwMaxBackBuffers,
                                                lpdwBackBuffer, 
                                                TRUE);
            }
            else 
            {
                hr = VFW_E_DDRAW_CAPS_NOT_SUITABLE;
            }
        }

        if ( (hr != DD_OK) && (dwFlags & AMAP_ALLOW_SYSMEM) ) 
        {
            if( lpHdr->biCompression <= BI_BITFIELDS &&
                pddsdDisplay->ddpfPixelFormat.dwRGBBitCount == lpHdr->biBitCount) 
            {

                hr = AllocateOffscreenSurface(  &m_lpDDTexture, 
                                                AMAP_FORCE_SYSMEM, 
                                                &ddsd,
                                                dwMinBackBuffers, 
                                                dwMaxBackBuffers,
                                                lpdwBackBuffer, 
                                                TRUE);
            }
            else 
            {
                hr = VFW_E_DDRAW_CAPS_NOT_SUITABLE;
            }
        }
    }

    *lplpSurface = m_lpDDTexture;
    return hr;
}

HRESULT
CMovie::AllocateOverlaySurface(
                        LPDIRECTDRAWSURFACE7* lplpSurf,
                        DWORD dwFlags,
                        DDSURFACEDESC2* pddsd,
                        DWORD dwMinBuffers,
                        DWORD dwMaxBuffers,
                        DWORD* lpdwBuffer
                        )
{
    HRESULT hr = S_OK;
    LPDIRECTDRAWSURFACE7 lpSurface7 = NULL;

    pddsd->dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT |
                     DDSD_PIXELFORMAT | DDSD_BACKBUFFERCOUNT;

    pddsd->ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM |
                            DDSCAPS_OVERLAY | DDSCAPS_FLIP | DDSCAPS_COMPLEX;

    if (dwFlags & AMAP_3D_TARGET) 
    {
        pddsd->ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
    }

    DWORD dwMinBuff = dwMinBuffers;
    DWORD dwMaxBuff = dwMaxBuffers;

    for(    DWORD dwTotalBufferCount =  dwMaxBuff;
            dwTotalBufferCount >= dwMinBuff; 
            dwTotalBufferCount--) 
    {
        // CleanUp stuff from the last loop
        RELEASE(lpSurface7);

        pddsd->dwBackBufferCount = dwTotalBufferCount - 1;
        if(dwTotalBufferCount == 1) 
        {
            pddsd->dwFlags &= ~DDSD_BACKBUFFERCOUNT;
            pddsd->ddsCaps.dwCaps &= ~(DDSCAPS_FLIP | DDSCAPS_COMPLEX);
        }

        hr = m_lpDDObj->CreateSurface(pddsd, &lpSurface7, NULL);
        if( FAILED(hr))
        {
            TCHAR achT[MAX_PATH];
            _stprintf( achT, TEXT("<***> FAILED TO CREATE SURFACE (%s, #%ld), hr = 0x%08x"),
                __FILE__, __LINE__, hr);
            OutputDebugString(achT);
        }

        if (hr == DD_OK) 
        {

            // hr = CheckOverlayAvailable(lpSurface7);
            *lpdwBuffer = dwTotalBufferCount;
            break;
        }
    } // for 

    *lplpSurf = lpSurface7;
    return hr;
}

HRESULT
CMovie::AllocateOffscreenSurface(
                                    LPDIRECTDRAWSURFACE7* lplpSurf,
                                    DWORD dwFlags,
                                    DDSURFACEDESC2* pddsd,
                                    DWORD dwMinBuffers,
                                    DWORD dwMaxBuffers,
                                    DWORD* lpdwBuffer,
                                    BOOL fAllowBackBuffer
                                    )
{
    HRESULT hr = S_OK;
    LPDIRECTDRAWSURFACE7 lpSurf7FB = NULL;
    DWORD dwTotalBufferCount = 0;


    *lpdwBuffer = 0;
    pddsd->dwBackBufferCount = 0;
    pddsd->dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;

    if (dwFlags & AMAP_FORCE_SYSMEM) 
    {
        pddsd->ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    }
    else 
    {
        pddsd->ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM |
                                DDSCAPS_OFFSCREENPLAIN;
    }

    if (dwFlags & AMAP_3D_TARGET) 
    {
        pddsd->ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
    }

    hr = m_lpDDObj->CreateSurface(pddsd, &lpSurf7FB, NULL);
    if( FAILED(hr))
    {
        TCHAR achT[MAX_PATH];
        _stprintf( achT, TEXT("<***> FAILED TO CREATE SURFACE (%s, #%ld), hr = 0x%08x"),
            __FILE__, __LINE__, hr);
        OutputDebugString(achT);
    }

    if (hr != DD_OK) 
    {
        return hr;
    }

    DWORD dwMinBuff;
    DWORD dwMaxBuff;

    if (fAllowBackBuffer) 
    {
        dwMinBuff = dwMinBuffers + 1;
        dwMaxBuff = dwMaxBuffers + 1;

        if (dwMinBuffers <= 2) 
        {
            dwMinBuff = dwMinBuffers + 1;
        }

        if (dwMaxBuffers <= 2) 
        {
            dwMaxBuff = dwMaxBuffers + 1;
        }
    }
    else 
    {

        dwMinBuff = dwMinBuffers;
        dwMaxBuff = dwMaxBuffers;
    }

    dwTotalBufferCount = 1;

    __try {

        LPDIRECTDRAWSURFACE7 lpSurf7 = lpSurf7FB;

        for ( ; dwTotalBufferCount < dwMaxBuff; dwTotalBufferCount++) 
        {
            LPDIRECTDRAWSURFACE7 lpSurf7_2 = NULL;

            hr = m_lpDDObj->CreateSurface(pddsd, &lpSurf7_2, NULL);
            if (hr != DD_OK)
            {
                TCHAR achT[MAX_PATH];
                _stprintf( achT, TEXT("<***> FAILED TO CREATE SURFACE (%s, #%ld), hr = 0x%08x"),
                    __FILE__, __LINE__, hr);
                OutputDebugString(achT);
                __leave;
            }

            LPDIRECTDRAWSURFACE4 lp4FB;
            lpSurf7->QueryInterface(IID_IDirectDrawSurface4, (LPVOID*)&lp4FB);

            LPDIRECTDRAWSURFACE4 lp4BB;
            lpSurf7_2->QueryInterface(IID_IDirectDrawSurface4, (LPVOID*)&lp4BB);

            hr = lp4FB->AddAttachedSurface(lp4BB);

            RELEASE(lp4FB);
            RELEASE(lp4BB);

            lpSurf7 = lpSurf7_2;
            RELEASE(lpSurf7_2);

            if (hr != DD_OK)
                __leave;

        }
    }
    __finally 
    {
        if (hr != DD_OK) 
        {
            if (dwTotalBufferCount >= dwMinBuff) 
            {
                hr = DD_OK;
            }
            else 
            {
                dwTotalBufferCount = 0;
                RELEASE(lpSurf7FB);
            }
        }

        if (hr == DD_OK) 
        {
            *lpdwBuffer = dwTotalBufferCount;
        }
    }

    *lplpSurf = lpSurf7FB;
    return hr;
}


#if 0
STDMETHODIMP
CMovie::AllocateSurface(
    DWORD_PTR x,
    VMRALLOCATIONINFO *w,
    DWORD* lpdwBuffer,
    LPDIRECTDRAWSURFACE7* lplpSurface
    )
{
    CheckPointer(w,E_POINTER);

    DWORD dwFlags            = w->dwFlags;
    LPBITMAPINFOHEADER lpHdr = w->lpHdr;
    LPDDPIXELFORMAT lpPixFmt = w->lpPixFmt;
    LPSIZE lpAspectRatio     = &w->szAspectRatio;
    DWORD dwMinBuffers       = w->dwMinBuffers;
    DWORD dwMaxBuffers       = w->dwMaxBuffers;

    if(!lpHdr)
    {
        return E_POINTER;
    }

    if(!lpAspectRatio)
    {
        return E_POINTER;
    }

    if(dwFlags & AMAP_PIXELFORMAT_VALID)
    {
        if(!lpPixFmt)
        {
            return E_INVALIDARG;
        }
    }

    HRESULT hr = AllocateSurfaceWorker(dwFlags, lpHdr, lpPixFmt,
                                       lpAspectRatio,
                                       dwMinBuffers, dwMaxBuffers,
                                       lpdwBuffer, lplpSurface);
    return hr;
}


/******************************Public*Routine******************************\
* AllocateSurfaceWorker
*
\**************************************************************************/
HRESULT
CMovie::AllocateSurfaceWorker(
    DWORD dwFlags,
    LPBITMAPINFOHEADER lpHdr,
    LPDDPIXELFORMAT lpPixFmt,
    LPSIZE lpAspectRatio,
    DWORD dwMinBuffers,
    DWORD dwMaxBuffers,
    DWORD* lpdwBuffer,
    LPDIRECTDRAWSURFACE7* lplpSurface
    )
{
    LPBITMAPINFOHEADER lpHeader = lpHdr;
    if(!lpHeader)
    {
        DbgLog((LOG_ERROR, 1, TEXT("Can't get bitmapinfoheader from media type!!")));
        return E_INVALIDARG;
    }

    DDSURFACEDESC2 ddsd;
    INITDDSTRUCT(ddsd);
    ddsd.dwFlags  = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd.dwWidth  = abs(lpHeader->biWidth);
    ddsd.dwHeight = abs(lpHeader->biHeight);
    ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY /*| DDSCAPS_TEXTURE */;

    ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);

    if(lpHdr->biCompression <= BI_BITFIELDS &&
        m_DispInfo.bmiHeader.biBitCount <= lpHdr->biBitCount)
    {
        ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;

        if(lpHdr->biBitCount == 32)
        {
            ddsd.ddpfPixelFormat.dwRGBBitCount = 32;
            ddsd.ddpfPixelFormat.dwRBitMask = 0xff0000;
            ddsd.ddpfPixelFormat.dwGBitMask = 0xff00;
            ddsd.ddpfPixelFormat.dwBBitMask = 0xff;
        }
        else if(lpHdr->biBitCount == 16)
        {
            ddsd.ddpfPixelFormat.dwRGBBitCount = 16;
            ddsd.ddpfPixelFormat.dwRBitMask = 0xF800;
            ddsd.ddpfPixelFormat.dwGBitMask = 0x07e0;
            ddsd.ddpfPixelFormat.dwBBitMask = 0x001F;
        }
    }
    else if(lpHdr->biCompression > BI_BITFIELDS)
    {
        const DWORD dwCaps = (DDCAPS_BLTFOURCC | DDCAPS_BLTSTRETCH);
        if((dwCaps & m_ddHWCaps.dwCaps) != dwCaps)
        {
            DbgLog((LOG_ERROR, 1, TEXT("Can't BLT_FOURCC | BLT_STRETCH!!")));
            return E_FAIL;
        }

        ddsd.ddpfPixelFormat.dwFourCC = lpHdr->biCompression;
        ddsd.ddpfPixelFormat.dwFlags = DDPF_FOURCC;
        ddsd.ddpfPixelFormat.dwYUVBitCount = lpHdr->biBitCount;
    }
    else
    {
        return E_FAIL;
    }


    // Adjust width and height, if the driver requires it
    DWORD dwWidth  = ddsd.dwWidth;
    DWORD dwHeight = ddsd.dwHeight;

    HRESULT hr = m_lpDDObj->CreateSurface(&ddsd, &m_lpDDTexture, NULL);
    if( FAILED(hr))
    {
        TCHAR achT[MAX_PATH];
        _stprintf( achT, TEXT("<***> FAILED TO CREATE SURFACE (%s, #%ld), hr = 0x%08x"),
            __FILE__, __LINE__, hr);
        OutputDebugString(achT);
    }

    if(SUCCEEDED(hr))
    {
        m_VideoAR = *lpAspectRatio;

        m_VideoSize.cx = abs(lpHeader->biWidth);
        m_VideoSize.cy = abs(lpHeader->biHeight);

        SetRect(&m_rcDst, 0, 0, m_VideoSize.cx, m_VideoSize.cy);
        m_rcSrc = m_rcDst;

        hr = PaintDDrawSurfaceBlack(m_lpDDTexture);

        *lplpSurface = m_lpDDTexture;
        *lpdwBuffer = 1;
    }

    return hr;
}

#endif
/******************************Public*Routine******************************\
* FreeSurfaces()
*
\**************************************************************************/
STDMETHODIMP
CMovie::FreeSurface(DWORD_PTR w)
{
    if(m_lpDDTexture)
    {
        m_lpDDTexture->Release();
        m_lpDDTexture = NULL;
    }

    return S_OK;
}


/******************************Public*Routine******************************\
* PrepareSurface
*
\**************************************************************************/
STDMETHODIMP
CMovie::PrepareSurface(
    DWORD_PTR w,
    LPDIRECTDRAWSURFACE7 lplpSurface,
    DWORD dwSurfaceFlags
    )
{
    return S_OK;
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
    return E_NOTIMPL;
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
CMovie::StartPresenting(DWORD_PTR w)
{
    return S_OK;
}

/******************************Public*Routine******************************\
* StopPresenting()
*
\**************************************************************************/
STDMETHODIMP
CMovie::StopPresenting(DWORD_PTR w)
{
    return S_OK;
}

/******************************Public*Routine******************************\
* PresentImage
*
\**************************************************************************/
STDMETHODIMP
CMovie::PresentImage(
    DWORD_PTR w,
    VMRPRESENTATIONINFO* p
    )
{
    //
    // Call the app specific function to render the scene
    //
    return PresentImage();
}

/******************************Private*Routine*****************************\
* PresentImage
* this private function is the one actually presenting the image
* to show that the app specific presentation doesn't use any other parameters
* and also to call it from the frame steping it's been brought out
* into a seprate function
*
\**************************************************************************/
HRESULT 
CMovie::PresentImage()
{
    CAutoLock Lock(&m_AppImageLock);
    HRESULT hr;

    RECT rSrc = {0, 0, m_VideoSize.cx, m_VideoSize.cy};
    RECT rDst = {0, 0, WIDTH(&m_rcDst), HEIGHT(&m_rcDst)};

    hr = m_lpBackBuffer->Blt(&rDst, m_lpDDTexture, &rSrc, DDBLT_WAIT, NULL);
    if( FAILED( hr ) ) {
        return hr;
    }
    /*??*/
    m_lpDDTexture->Flip(NULL, DDFLIP_WAIT);

    rDst.left   = m_cxFontImg;
    rDst.top    = m_cyFontImg;
    rDst.right  = rDst.left + (m_cxFontImg * 40);
    rDst.bottom = rDst.top  + (m_cyFontImg * 4);

    rSrc.left   = 0;
    rSrc.top    = 0;
    rSrc.right  = (m_cxFontImg * 40);
    rSrc.bottom = (m_cyFontImg * 4);
    hr = m_lpBltAlpha->AlphaBlt(&rDst, m_lpDDAppImage, &rSrc, 0x80);
    if( FAILED( hr ) ) {
        return hr;
    }

    RECT rc = m_rcDst;
    RECT rcSrc;

    SetRect(&rcSrc, 0, 0, WIDTH(&rc), HEIGHT(&rc));
    return m_lpPriSurf->Blt(&rc, m_lpBackBuffer, &rcSrc, DDBLT_WAIT, NULL);
}



//////////////////////////////////////////////////////////////////////////////
//
// Allocator Presenter helper functions
//
//////////////////////////////////////////////////////////////////////////////


/*****************************Private*Routine******************************\
* InitDisplayInfo
*
\**************************************************************************/
BOOL
InitDisplayInfo(
    AMDISPLAYINFO* lpDispInfo
    )
{
    static char szDisplay[] = "DISPLAY\0";
    ZeroMemory(lpDispInfo, sizeof(*lpDispInfo));

    HDC hdcDisplay = CreateDCA(szDisplay, NULL, NULL, NULL);
    HBITMAP hbm = CreateCompatibleBitmap(hdcDisplay, 1, 1);

    lpDispInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    GetDIBits(hdcDisplay, hbm, 0, 1, NULL, (BITMAPINFO *)lpDispInfo, DIB_RGB_COLORS);
    GetDIBits(hdcDisplay, hbm, 0, 1, NULL, (BITMAPINFO *)lpDispInfo, DIB_RGB_COLORS);

    DeleteObject(hbm);
    DeleteDC(hdcDisplay);

    return TRUE;
}


/*****************************Private*Routine******************************\
* DDARGB32SurfaceInit
*
\**************************************************************************/
HRESULT
CMovie::DDARGB32SurfaceInit(
    LPDIRECTDRAWSURFACE7* lplpDDS,
    BOOL bTexture,
    DWORD cx,
    DWORD cy
    )
{
    DDSURFACEDESC2 ddsd;
    HRESULT hRet;

    CheckPointer(lplpDDS,E_POINTER);
    *lplpDDS = NULL;

    INITDDSTRUCT(ddsd);

    ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
    ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
    if(bTexture)
    {
        ddsd.ddpfPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
    }

    ddsd.ddpfPixelFormat.dwRGBBitCount = 32;
    if(bTexture)
    {
        ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000;
    }

    ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
    ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
    ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;

    if(bTexture)
    {
        ddsd.ddsCaps.dwCaps  =  DDSCAPS_TEXTURE;
        ddsd.ddsCaps.dwCaps2 = (DDSCAPS2_TEXTUREMANAGE | DDSCAPS2_HINTDYNAMIC);
    }
    else
    {
        ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN;
    }

    ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT;
    ddsd.dwBackBufferCount = 0;

    if(bTexture)
    {
        for(ddsd.dwWidth=1;  cx>ddsd.dwWidth;   ddsd.dwWidth<<=1);
        for(ddsd.dwHeight=1; cy>ddsd.dwHeight; ddsd.dwHeight<<=1);
    }
    else
    {
        ddsd.dwWidth=cx;
        ddsd.dwHeight=cy;
    }

    // Attempt to create the surface with these settings
    hRet = m_lpDDObj->CreateSurface(&ddsd, lplpDDS, NULL);
    if( FAILED( hRet ))
    {
        TCHAR achT[MAX_PATH];
        _stprintf( achT, TEXT("<***> FAILED TO CREATE SURFACE (%s, #%ld), hr = 0x%08x"),
            __FILE__, __LINE__, hRet);
        OutputDebugString(achT);
    }

    return hRet;
}


/*****************************Private*Routine******************************\
* CreateFontCache
*
\**************************************************************************/
HRESULT
CMovie::CreateFontCache(
    int cyFont
    )
{
    //
    // Initialize the LOGFONT structure - we want to
    // create an "anti-aliased" Lucida Consol font
    //
    LOGFONT lfChar;
    ZeroMemory(&lfChar, sizeof(lfChar));
    lfChar.lfHeight = -cyFont;
    lfChar.lfCharSet = OEM_CHARSET ;
    lfChar.lfPitchAndFamily = FIXED_PITCH | FF_MODERN ;
    lstrcpy(lfChar.lfFaceName, TEXT("Lucida Console\0")) ;
    lfChar.lfWeight = FW_NORMAL ;
    lfChar.lfOutPrecision = OUT_STRING_PRECIS ;
    lfChar.lfClipPrecision = CLIP_STROKE_PRECIS ;
    lfChar.lfQuality = ANTIALIASED_QUALITY;

    HFONT hFont = CreateFontIndirect(&lfChar) ;
    if(!hFont)
    {
        return E_OUTOFMEMORY;
    }

    //
    // The following magic is necessary to get GDI to rasterize
    // the font with anti-aliasing switched on when we later use
    // the font in a DDraw Surface.  The doc's say that this is only
    // necessary in Win9X - but Win2K seems to require it too.
    //
    SIZE size;
    HDC hdcWin = GetDC(NULL);
    hFont = (HFONT)SelectObject(hdcWin, hFont);
    GetTextExtentPoint32(hdcWin, TEXT("A"), 1, &size);

    hFont = (HFONT)SelectObject(hdcWin, hFont);
    ReleaseDC(NULL, hdcWin);

    //
    // Make sure that the font doesn't get too big.
    //
    if(size.cx * GRID_CX > 1024)
    {
        return S_OK;
    }

    //
    // Delete the old font and assign the new one
    //
    RELEASE(m_lpDDSFontCache);
    if(m_hFont)
    {
        DeleteObject(m_hFont);
    }
    m_cxFont = size.cx; m_cyFont = size.cy;
    m_hFont = hFont;


    //
    // Create the DDraw ARGB32 surface that we will use
    // for the font cache.
    //
    HRESULT hr = DDARGB32SurfaceInit(&m_lpDDSFontCache, TRUE, 16 * size.cx, 6 * size.cy);

    if(hr == DD_OK)
    {
        HDC hdcDest;

        m_lpDDSFontCache->GetDC(&hdcDest);

        //
        // Select the font into the DDraw surface and draw the characters
        //
        m_hFont = (HFONT)SelectObject(hdcDest, m_hFont);
        SetTextColor(hdcDest, RGB(255,255,255));
        SetBkColor(hdcDest, RGB(0,0,0));
        SetBkMode(hdcDest, OPAQUE);

        int row, col; TCHAR ch = (TCHAR)32;
        for(row = 0; row < 6; row++)
        {
            for(col = 0; col < 16; col++)
            {
                TextOut(hdcDest, col * size.cx, row * size.cy, &ch, 1);
                ch++;
            }
        }

        m_hFont = (HFONT)SelectObject(hdcDest, m_hFont);
        m_lpDDSFontCache->ReleaseDC(hdcDest);

        DDSURFACEDESC2 surfDesc;
        INITDDSTRUCT(surfDesc);

        hr = m_lpDDSFontCache->Lock(NULL, &surfDesc, DDLOCK_WAIT, NULL);
        if(hr == DD_OK)
        {
            LPDWORD lpDst = (LPDWORD)surfDesc.lpSurface;

            for(row = 0; row < 6 * size.cy; row++)
            {
                LPDWORD lp = lpDst;

                for(col = 0; col < 16 * size.cx; col++)
                {
                    DWORD dwPel = *lp;

                    if(dwPel)
                    {
                        dwPel <<= 24;
                        dwPel |= 0x00FFFFFF;
                    }
                    else
                    {
                        dwPel = 0x80000000;
                    }

                    *lp++ = dwPel;
                }
                lpDst += (surfDesc.lPitch / 4);
            }
            m_lpDDSFontCache->Unlock(NULL);
        }
    }

    return S_OK;
}


/*****************************Private*Routine******************************\
* Initialize3DEnvironment
*
\**************************************************************************/
HRESULT
CMovie::Initialize3DEnvironment(
    HWND hWnd,
    TCHAR* achError, 
    UINT uintLen
    )
{
    HRESULT hr;

    //
    // Create the IDirectDraw interface. The first parameter is the GUID,
    // which is allowed to be NULL. If there are more than one DirectDraw
    // drivers on the system, a NULL guid requests the primary driver. For
    // non-GDI hardware cards like the 3DFX and PowerVR, the guid would need
    // to be explicity specified . (Note: these guids are normally obtained
    // from enumeration, which is convered in a subsequent tutorial.)
    //

    m_hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

    hr = DirectDrawCreateEx(NULL, (VOID**)&m_lpDDObj, IID_IDirectDraw7, NULL);
    if(FAILED(hr))
        return hr;

    //
    // get the h/w caps for this device
    //
    INITDDSTRUCT(m_ddHWCaps);
    hr = m_lpDDObj->GetCaps(&m_ddHWCaps, NULL);
    if(FAILED(hr))
        return hr;

    InitDisplayInfo(&m_DispInfo);

    //
    // Set the Windows cooperative level. This is where we tell the system
    // whether we will be rendering in fullscreen mode or in a window. Note
    // that some hardware (non-GDI) may not be able to render into a window.
    // The flag DDSCL_NORMAL specifies windowed mode. Using fullscreen mode
    // is the topic of a subsequent tutorial. The DDSCL_FPUSETUP flag is a
    // hint to DirectX to optomize floating points calculations. See the docs
    // for more info on this. Note: this call could fail if another application
    // already controls a fullscreen, exclusive mode.
    //
    hr = m_lpDDObj->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
    if(FAILED(hr))
        return hr;

    //
    // Initialize a surface description structure for the primary surface. The
    // primary surface represents the entire display, with dimensions and a
    // pixel format of the display. Therefore, none of that information needs
    // to be specified in order to create the primary surface.
    //
    DDSURFACEDESC2 ddsd;
    ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    //
    // Create the primary surface.
    //
    hr = m_lpDDObj->CreateSurface(&ddsd, &m_lpPriSurf, NULL);
    if(FAILED(hr))
    {
        TCHAR achT[MAX_PATH];
        _stprintf( achT, TEXT("<***> FAILED TO CREATE SURFACE (%s, #%ld), hr = 0x%08x"),
            __FILE__, __LINE__, hr);
        OutputDebugString(achT);

        return hr;
    }

    //
    // Create a clipper object which handles all our clipping for cases when
    // our window is partially obscured by other windows. This is not needed
    // for apps running in fullscreen mode.
    //
    LPDIRECTDRAWCLIPPER pcClipper;
    hr = m_lpDDObj->CreateClipper(0, &pcClipper, NULL);
    if(FAILED(hr))
        return hr;

    //
    // Associate the clipper with our window. Note that, afterwards, the
    // clipper is internally referenced by the primary surface, so it is safe
    // to release our local reference to it.
    //
    pcClipper->SetHWnd(0, hWnd);
    m_lpPriSurf->SetClipper(pcClipper);
    pcClipper->Release();

    //
    // Before creating the device, check that we are NOT in a palettized
    // display. That case will cause CreateDevice() to fail, since this simple
    // tutorial does not bother with palettes.
    //
    ddsd.dwSize = sizeof(DDSURFACEDESC2);
    m_lpDDObj->GetDisplayMode(&ddsd);
    if(ddsd.ddpfPixelFormat.dwRGBBitCount <= 8)
        return DDERR_INVALIDMODE;

    DWORD dwRenderWidth  = ddsd.dwWidth;
    DWORD dwRenderHeight = ddsd.dwHeight;

    //
    // Setup a surface description to create a backbuffer. This is an
    // offscreen plain surface with dimensions equal to the current display
    // size.

    // The DDSCAPS_3DDEVICE is needed so we can later query this surface
    // for an IDirect3DDevice interface.
    //
    ZeroMemory(&ddsd, sizeof(DDSURFACEDESC2));
    ddsd.dwSize         = sizeof(DDSURFACEDESC2);
    ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_3DDEVICE;
    ddsd.dwWidth = dwRenderWidth;
    ddsd.dwHeight = dwRenderHeight;

    //
    // Create the backbuffer. The most likely reason for failure is running
    // out of video memory. (A more sophisticated app should handle this.)
    //
    hr = m_lpDDObj->CreateSurface(&ddsd, &m_lpBackBuffer, NULL);
    if(FAILED(hr))
    {
        if( achError )
        {
            lstrcpyn( achError, TEXT("Sample cannot continue because application failed to create the backbuffer\r\n")\
                TEXT("The possible reason can be the following DirectX warning:\r\n")\
                TEXT("AGP aware driver failed to set DDSCAPS_LOCALVIDMEM or DDSCAPS_NONLOCALVIDMEM.\r\n")\
                TEXT("You may want to modify this sample or try a different video driver."), uintLen);
        }
        TCHAR achT[MAX_PATH];
        _stprintf( achT, TEXT("<***> FAILED TO CREATE SURFACE (%s, #%ld), hr = 0x%08x"),
            __FILE__, __LINE__, hr);
        OutputDebugString(achT);
        return hr;
    }

    //
    // Create the textbuffer.
    //
    // The text buffer should be RGB32 (for now - later I'll try
    // ARGB16:4:4:4:4, but that is a lot more work).
    //
    hr = DDARGB32SurfaceInit(&m_lpDDAppImage, TRUE,
                             1024, MulDiv(4, (int)dwRenderHeight, GRID_CY));
    if(FAILED(hr))
        return hr;

    PaintDDrawSurfaceBlack(m_lpDDAppImage);

    //
    // Create the device. The device is created off of our back buffer, which
    // becomes the render target for the newly created device. Note that the
    // z-buffer must be created BEFORE the device
    //
    m_lpBltAlpha = new CAlphaBlt(m_lpBackBuffer, &hr);
    if(m_lpBltAlpha == NULL || hr != DD_OK)
    {
        if(m_lpBltAlpha == NULL)
        {
            hr = E_OUTOFMEMORY;
        }
        delete m_lpBltAlpha;
    }

    hr = CreateFontCache(32);

    return hr;
}


POINT LookUpChar(char ch, int cxFont, int cyFont)
{
    ch -= 32;

    int row = ch / 16;
    int col = ch % 16;

    POINT pt;

    pt.x = col * cxFont;
    pt.y = row * cyFont;

    return pt;
}


/******************************Public*Routine******************************\
* SetAppText
*
\**************************************************************************/
BOOL
CMovie::SetAppText(
    char* sz
    )
{
    DDBLTFX ddFX;
    INITDDSTRUCT(ddFX);
    ddFX.dwFillColor =  0xFF80FF80;

    CAutoLock Lock(&m_AppImageLock);
    m_lpDDAppImage->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &ddFX);

    m_cxFontImg = m_cxFont;
    m_cyFontImg = m_cyFont;
    RECT rcDst = {0, 0, m_cxFont, m_cyFont};

    while(*sz)
    {
        if(*sz == '\n')
        {
            OffsetRect(&rcDst, 0, m_cyFont);
            rcDst.left = 0;
            rcDst.right = m_cxFont;
        }
        else
        {
            POINT pt = LookUpChar(*sz, m_cxFont, m_cyFont);

            RECT rcSrc;
            rcSrc.left = pt.x;
            rcSrc.top  = pt.y;
            rcSrc.right = pt.x + m_cxFont;
            rcSrc.bottom  = pt.y + m_cyFont;

            m_lpDDAppImage->Blt(&rcDst, m_lpDDSFontCache, &rcSrc, DDBLT_WAIT, NULL);
            OffsetRect(&rcDst, m_cxFont, 0);
        }
        sz++;
    }

    return TRUE;
}


