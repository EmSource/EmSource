//----------------------------------------------------------------------------
//  File:   AP.cpp
//
//  Desc:   DirectShow sample code
//          Implementation of Allocator-presenter part of CMultiSAP
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "project.h"
#include <stdio.h>

#pragma warning(disable:4702) // disable "unreachable code" warning
// Function prototypes
HRESULT App_FrameMove( LPDIRECT3DDEVICE7 pd3dDevice, FLOAT fTimeKey );
HRESULT App_Render( LPDIRECT3DDEVICE7 pd3dDevice );
HRESULT App_InitDeviceObjects( HWND hWnd, LPDIRECT3DDEVICE7 pd3dDevice, BOOL );



//-------------------------------------------------------------------------
//  NonDelegatingQueryInterface
//-------------------------------------------------------------------------
STDMETHODIMP
CMultiSAP::NonDelegatingQueryInterface(
                                       REFIID riid,
                                       void** ppv
                                       )
{
    if(riid == __uuidof(IVMRSurfaceAllocator))
    {
        return GetInterface((IVMRSurfaceAllocator*)this, ppv);
    }
    else if(riid == __uuidof(IVMRImagePresenter))
    {
        return GetInterface((IVMRImagePresenter*)this, ppv);
    }
    else if(riid == __uuidof(IAMGraphBuilderCallback))
    {
        return GetInterface((IAMGraphBuilderCallback*)this, ppv);
    }
    
    return CUnknown::NonDelegatingQueryInterface(riid,ppv);
}

//////////////////////////////////////////////////////////////////////////////
//
// IAMGraphBuilderCallback
//
//////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------
//  SelectedFilter
//  When we hook IAMGraphBuilderCallback to the graph builder, it calls us
//  to verify if it is possible to add this or that filter to the graph.
//  If rendering fails with our customized VMR, we do not want any default
//  renderers (i.e. unwanted "active movie" windows). SelectedFilter is called
//  by the filter graph when it is about to add a new filter to the graph.
//  Here we check of this is a video renderer, and if this is not OUR VMR,
//  we reject it returning E_FAIL. And we approve all the other filters returning 
//  S_OK
//-------------------------------------------------------------------------
STDMETHODIMP 
CMultiSAP::SelectedFilter( IMoniker *pMon )
{
	return S_OK;
}

//-------------------------------------------------------------------------
//  CreatedFilter
//  Here we check of this is a video renderer, and if this is not OUR VMR,
//  we reject it returning E_FAIL. And we approve all the other filters returning 
//  S_OK
//-------------------------------------------------------------------------
STDMETHODIMP 
CMultiSAP::CreatedFilter( IBaseFilter *pBf )
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
        // 
        FILTER_INFO fi;
        hr = pBf->QueryFilterInfo(&fi);
        RELEASE( fi.pGraph );
        if( NULL == wcsstr( fi.achName, L"VMR for VMRMulti"))
        {
            // reject 
            return E_FAIL;
        }
        else
        {
            // approve
            return S_OK;
        }
    }

    // we should never hit this point
    return E_UNEXPECTED;
}

//////////////////////////////////////////////////////////////////////////////
//
// IVMRSurfaceAllocator
//
//////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------
//  AllocateSurface
//  Here we allocate two surfaces: one is "CMovie::m_lpDDDecode" that is used 
//  by VMR in sync with the decoder; and "CMovie::m_lpDDTexture" that WE use 
//  for presenting
//-------------------------------------------------------------------------
STDMETHODIMP
CMultiSAP::AllocateSurface(
                           DWORD_PTR pdwUserID,
                           VMRALLOCATIONINFO *w,
                           DWORD* lpdwBuffer,
                           LPDIRECTDRAWSURFACE7* lplpSurface
                           )
{
    // before doing anything, let's check if pdwUserID is valid
    CMovie *pmovie = m_movieList.GetMovie(pdwUserID);   
    if( NULL == pmovie )
    {
        OutputDebugString(TEXT("AllocateSurface received a call from unrecognized VMR\n"));
        return E_INVALIDARG;
    }

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
    *lplpSurface = NULL;

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

            /*
            if (lpHdr->biCompression == BI_BITFIELDS) 
            {
                ddsdDisplay.
                const DWORD *pMonMasks = NULL;
                // GetBitMasks(&m_lpCurrMon->DispInfo.bmiHeader);

                DWORD *pBitMasks = (DWORD *)((LPBYTE)lpHdr + lpHdr->biSize);
                pBitMasks[0] = pMonMasks[0];
                pBitMasks[1] = pMonMasks[1];
                pBitMasks[2] = pMonMasks[2];
            }
            */
        }
    }

    hr = AllocateSurfaceWorker( pmovie,
                                dwFlags, 
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
        DDSURFACEDESC2 ddsdTexture;
        ZeroMemory( &ddsdTexture, sizeof(DDSURFACEDESC2));
        ddsdTexture.dwSize = sizeof(DDSURFACEDESC2);

        ddsdTexture.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;


        // Adjust width and height, if the driver requires it
        if (m_pD3DHelper->IsPower2()) 
        {
            
            for (ddsdTexture.dwWidth = 1; 
                (DWORD)abs(lpHdr->biWidth) > ddsdTexture.dwWidth;
                ddsdTexture.dwWidth <<= 1);
            
            for (ddsdTexture.dwHeight = 1; 
                (DWORD)abs(lpHdr->biHeight) > ddsdTexture.dwHeight;
                ddsdTexture.dwHeight <<= 1);        
        }
        else
        {
            ddsdTexture.dwWidth = (DWORD)abs(lpHdr->biWidth);
            ddsdTexture.dwHeight = (DWORD)abs(lpHdr->biHeight);
        }
        
        ddsdTexture.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_TEXTURE; 

        ddsdTexture.ddpfPixelFormat.dwFlags    = DDPF_RGB;
        ddsdTexture.ddpfPixelFormat.dwFourCC   = 0;
        ddsdTexture.ddpfPixelFormat.dwRGBBitCount = 32;
        ddsdTexture.ddpfPixelFormat.dwRBitMask = 0xff0000;
        ddsdTexture.ddpfPixelFormat.dwGBitMask = 0x00ff00;
        ddsdTexture.ddpfPixelFormat.dwBBitMask = 0x0000ff;

        hr = m_lpDDObj->CreateSurface(&ddsdTexture, &(pmovie->m_lpDDTexture), NULL);
        if( FAILED(hr))
        {
            if(  0x8876017c == hr )
            {
#ifdef SPARKLE
                _tcsncpy( m_achErrorMessage, TEXT("Direct3D object returned error code D3DERR_OUTOFVIDEOMEMORY,\r\n")\
                                             TEXT("which means there is not enough video memory to render this movie.\r\n")\
                                             TEXT("Naturally, this sample is supposed to demonstrate DirectShow capabilities\r\n")\
                                             TEXT("on high-end video cards. We are sorry for inconvenience.\r\n")\
                                             TEXT("You may want to try some video of a smaller size, turn off the background\r\n")\
                                             TEXT("(by commenting line '#define SPARKLE 1' in project.h and recompiling),\r\n")\
                                             TEXT("or try a different video driver."), 2048);
#else
                _tcsncpy( m_achErrorMessage, TEXT("Direct3D object returned error code D3DERR_OUTOFVIDEOMEMORY,\r\n")\
                                             TEXT("which means there is not enough video memory to render this movie.\r\n")\
                                             TEXT("Naturally, this sample is supposed to demonstrate DirectShow capabilities\r\n")\
                                             TEXT("on high-end video cards. We are sorry for inconvenience.\r\n")\
                                             TEXT("You may want to try some video of a smaller size, or try a different video driver."), 2048);
#endif
                _tcsncpy( m_achErrorTitle, TEXT("Out of video memory"), MAX_PATH);
                m_bErrorMessage = true;
            } // if outofmemeory
            else
            {
#ifdef UNICODE
                swprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#else
                sprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#endif
                _tcsncat( m_achErrorMessage,  TEXT("Please use DirectX Error Lookup tool and verify DirectX\r\n")\
                                              TEXT("capabilities of your video driver. We are sorry for inconvenience.\r\n")\
                                              TEXT("You may want to try a different media file, or try a different video driver."), 2048);

                _tcsncpy( m_achErrorTitle, TEXT("Direct3D error when allocating surface"), MAX_PATH);
                m_bErrorMessage = true;
            }
            pmovie->m_lpDDDecode = NULL;
        }
        else
        {
            pmovie->m_VideoAR = *lpAspectRatio;
            pmovie->m_VideoSize.cx = abs(lpHdr->biWidth);
            pmovie->m_VideoSize.cy = abs(lpHdr->biHeight);
        
            SetRect(    &(pmovie->m_rcDst), 0, 0, 
                            pmovie->m_VideoSize.cx, 
                            pmovie->m_VideoSize.cy);
        
            pmovie->m_rcSrc = pmovie->m_rcDst;
        
            DDBLTFX ddFX;
            INITDDSTRUCT(ddFX);
            pmovie->m_lpDDTexture->Blt(NULL, NULL, NULL, DDBLT_COLORFILL, &ddFX);

            //*lplpSurface = pmovie->m_lpDDDecode;
            //*lpdwBuffer = dwMaxBuffers;       
            pmovie->m_bDirectedFlips = (AMAP_DIRECTED_FLIP == (dwFlags & AMAP_DIRECTED_FLIP));
        }
    }

    return hr;

}

HRESULT
CMultiSAP::AllocateSurfaceWorker(
                                    CMovie *pmovie,
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

        hr = AllocateOffscreenSurface(  &(pmovie->m_lpDDDecode), 
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


        hr = AllocateOverlaySurface(    &(pmovie->m_lpDDDecode), 
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
                hr = AllocateOffscreenSurface(  &(pmovie->m_lpDDDecode), 
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

                hr = AllocateOffscreenSurface(  &(pmovie->m_lpDDDecode), 
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

    *lplpSurface = pmovie->m_lpDDDecode;
    return hr;
}

HRESULT
CMultiSAP::AllocateOverlaySurface(
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
CMultiSAP::AllocateOffscreenSurface(
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
                __leave;

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


//-------------------------------------------------------------------------
//  FreeSurface
//-------------------------------------------------------------------------
STDMETHODIMP
CMultiSAP::FreeSurface(DWORD_PTR pdwUserID)
{
    CMovie *pmovie = m_movieList.GetMovie( pdwUserID);
    
    if( NULL == pmovie )
    {
        OutputDebugString(TEXT("FreeSurface received a call from unrecognized VMR!\n"));
        return E_INVALIDARG;
    }
    
    if(pmovie->m_lpDDTexture)
    {
        pmovie->m_lpDDTexture = NULL;
    }
    
    return S_OK;
}


//-------------------------------------------------------------------------
//  PrepareSurface
//-------------------------------------------------------------------------
STDMETHODIMP
CMultiSAP::PrepareSurface(
                          DWORD_PTR w,
                          LPDIRECTDRAWSURFACE7 lplpSurface,
                          DWORD dwSurfaceFlags
                          )
{
    return S_OK;
}

//-------------------------------------------------------------------------
//  AdviseNotify
//-------------------------------------------------------------------------
STDMETHODIMP
CMultiSAP::AdviseNotify(
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

//-------------------------------------------------------------------------
//  StartPresenting
//-------------------------------------------------------------------------
STDMETHODIMP
CMultiSAP::StartPresenting(DWORD_PTR pdwUserID)
{
    CMovie *pmovie = m_movieList.GetMovie( pdwUserID );
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("StartPresenting received a call from unrecognized VMR\n"));
        return E_INVALIDARG;
    }

    pmovie->m_dwFrameCount = 0;
    return S_OK;
}


//-------------------------------------------------------------------------
//  StopPresenting
//-------------------------------------------------------------------------
STDMETHODIMP
CMultiSAP::StopPresenting(DWORD_PTR pdwUserID)
{
    CMovie *pmovie = m_movieList.GetMovie( pdwUserID );
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("StopPresenting received a call from unrecognized VMR\n"));
        return E_INVALIDARG;
    }

    return S_OK;
}

//-------------------------------------------------------------------------
//  PresentImage
//-------------------------------------------------------------------------
STDMETHODIMP
CMultiSAP::PresentImage(
                        DWORD_PTR pdwUserID,
                        VMRPRESENTATIONINFO* p
                        )
{
    HRESULT hr = S_OK;
    CAutoLock Lock(&m_AppImageLock);
        
    // first of all, let's check if dwUserID is valid
    CMovie *pmovie = m_movieList.GetMovie( pdwUserID );
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("StopPresenting received a call from unrecognized VMR\n"));
        return E_INVALIDARG;
    }
    
    hr = pmovie->m_lpDDTexture->Blt(&(pmovie->m_rcSrc), p->lpSurf, 
                                    &(pmovie->m_rcSrc), DDBLT_WAIT, NULL);
    pmovie->m_dwFrameCount++;
    pmovie->m_bPresented = TRUE;
    
    return S_OK;
}


/******************************Public*Routine******************************/
//-------------------------------------------------------------------------
//  ComposeThreadProc
//  
//-------------------------------------------------------------------------
DWORD WINAPI
CMultiSAP::ComposeThreadProc(
                             LPVOID lpParameter
                             )
{
    CMultiSAP* lp = (CMultiSAP*)lpParameter;
    return lp->ComposeThread();
}


//-------------------------------------------------------------------------
//  ComposeThread
//  starts presenting thread
//-------------------------------------------------------------------------
DWORD CMultiSAP::ComposeThread()
{
    timeBeginPeriod(1);
    
    const DWORD dwFrameRate = 30;
    
    DWORD dwFramePeriod = 1000 / dwFrameRate;
    DWORD dwStartTime = timeGetTime();
    
    m_pPresenter->StartPresenting(0);
    
    for ( ;; ) {
        
        DWORD dwTimeThisFrame = dwStartTime + ((m_dwFrameNum++ * 1000) / dwFrameRate);
        long lWaitTime = dwTimeThisFrame - timeGetTime();
        
        if (lWaitTime < 0) {
            continue;
        }
        
        DWORD rc = WaitForSingleObject(m_hQuitEvent, (DWORD)lWaitTime);
        if (rc == WAIT_OBJECT_0) {
            break;
        }
        
#ifdef SPARKLE
        if (m_pSparkle)
            m_pSparkle->RenderFrame();
#endif
        
        ComposeAndRender();
    }
    
    m_pPresenter->StopPresenting(0);
    
    timeEndPeriod(1);
    return 0;
}


//-------------------------------------------------------------------------
//  ComposeAndRender
//  this function actually performs D3D presentation of movies' buffers
//-------------------------------------------------------------------------
void CMultiSAP::ComposeAndRender()
{
    HRESULT hr = S_OK;

    RECT rcSrc;
    SetRect(&rcSrc, 0, 0, WIDTH(&m_rcDst), HEIGHT(&m_rcDst));
    
    // check if we need to change the movie
    if( m_movieList.GetSelectedMovieID() != m_pdwNextSelectedMovie )
    {
        if( !m_pEffect || m_pEffect->GetStage() != eEffectStageFinishing )
        {
            ReleaseFocus();
            // if so, change selection
            m_movieList.SelectMovie( m_pdwNextSelectedMovie );
            SetFocus();
        }
    }

    if( !m_pEffect || m_pEffect->IsComplete() )
    {
        // retrieve next effect from the queue
        CEffect *peffectNew = m_EffectQueue.Pop();
        if( !peffectNew )  // scenario is empty, set to default arrangement
        {
            peffectNew = new CEffectStillArrangement;//(eEffectStillArrangement/*eEffectDefault*/);
            if( !peffectNew )
            {
                OutputDebugStringA("Failed to create a new effect, keeping current effect");
            }
            else
            {
                hr = peffectNew->Initialize(&m_movieList, 1000, -1, 500);
                if( FAILED(hr))
                {
                    OutputDebugStringA("Failed to initialize new effect, keeping current effect");
                    delete peffectNew;
                }
                else
                {
                    if( m_pEffect )
                    {
                        delete m_pEffect;
                        m_pEffect = NULL;
                    }
                    m_pEffect = peffectNew;
                }
            }
        }
        else
        {
            delete m_pEffect;
            m_pEffect = peffectNew;
        }
    }// if we have no effect or it is time to change effect

    // clear the background to black or sparkles source filter
#ifdef SPARKLE
    if (m_pSparkle) 
    {
        m_lpBackBuffer->Blt(&rcSrc, m_pSparkle->GetFrame(), NULL,  DDBLT_WAIT, NULL);
    }
    else 
#endif
    {
        hr = m_pD3DHelper->ClearScene(RGB(0x00, 0x00, 0x00));
        if (hr != DD_OK) 
            OutputDebugStringA("ClearScene FAILED\n");
    }

    // compose scene; the switch below just recalculates coordinates and z-order for each frame
    
    switch( m_pEffect->GetType() )
    {
        case eEffectFountain:
        {
            CEffectFountain * pEF = (CEffectFountain*)m_pEffect;
            hr = pEF->Compose();
            break;
        }

        case eEffectStillArrangement:
        {
            CEffectStillArrangement * pEStill = (CEffectStillArrangement*)m_pEffect;
            hr = pEStill->Compose();
            break;
        }

        case eEffectFading:
        {
            CEffectFading *pEFade = (CEffectFading *)m_pEffect;
            if( eEffectStagePlaying == pEFade->GetStage() )
            {
                //CAutoLock Lock(&m_AppImageLock);
                ReleaseFocus();
                m_movieList.RemoveDeletedMovies();
                m_movieList.ActivateAll();
                SetFocus();
                pEFade->Invalidate();
            }
            hr = pEFade->Compose();
            break;
        }

        case eEffectDefault:
        default:
            hr = m_pEffect->CEffect::Compose();
            break;
    }
    
    if( hr != S_OK )
    {
        OutputDebugStringA("composing effect FAILED\n");
    }

    // draw frames; at this point they are sordet in z-order
    int nFrame = -1;
    BOOL bSelectedChannel = FALSE;
    CMovie *pmovie = NULL;

    for( int i=0; i<m_movieList.GetSize(); i++)
    {
        pmovie = m_movieList.GetMovieByIndex(i);

        if( !pmovie || FALSE == pmovie->m_bUseInTheScene ) // movie has'not been engaged in the scene yet
        {
            continue;
        }

        if( FALSE == pmovie->m_bPresented ) // do not draw empty uninitialized buffers
        {
            continue;
        }

        if( pmovie->m_dwUserID == m_movieList.GetSelectedMovieID() )
        {
            bSelectedChannel = TRUE;
        }
        else
        {
            bSelectedChannel = FALSE;
        }
        
        hr = m_pD3DHelper->RenderFrame( pmovie->m_lpDDTexture, pmovie->m_Vcur, m_rcDst, m_movieList.GetDefaultTarget(), bSelectedChannel);
        if( FAILED(hr))
        {
            OutputDebugStringA("rendering frame FAILED\n");
        }

    }// while 


    VMRPRESENTATIONINFO pi = 
    {
        0, 
        m_lpBackBuffer, 
        0,
        0,
        {4, 3},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        0,
        0
    };
    
    // IMPORTANT: always call default implementation of present image if you do not provide
    // WMV format support yourself (this format has different flip order of back buffers 
    // and default PresentImage takes care for it)
    m_pPresenter->PresentImage(0, &pi);
    return;
}


