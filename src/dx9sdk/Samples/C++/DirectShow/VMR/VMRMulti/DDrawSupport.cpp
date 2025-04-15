//----------------------------------------------------------------------------
//  File:   DDrawSupport.cpp
//
//  Desc:   DirectShow sample code
//          Implementation of DDrawObject that provides basic DDraw functionality
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "project.h"

#include <initguid.h>
#include <d3dxmath.h>

#include "D3DHelpers\\d3dutil.h"
#include "D3DHelpers\\d3dmath.h"

DEFINE_GUID( IID_IDirect3D7,         0xf5049e77,0x4861,0x11d2,0xa4,0x7,0x0,0xa0,0xc9,0x6,0x29,0xa8);
DEFINE_GUID( IID_IDirect3DRGBDevice, 0xA4665C60,0x2673,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56 );
DEFINE_GUID( IID_IDirect3DHALDevice, 0x84E63dE0,0x46AA,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E );

float g_maxz = -100000.f;
float g_minz =  100000.f;
float g_maxb = 0.f;
float g_minb = 0.f;


//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
CD3DHelper::CD3DHelper(LPDIRECTDRAWSURFACE7 lpDDSDst, HRESULT* phr) :
     m_pDD(NULL)
    ,m_pD3D(NULL)
    ,m_pD3DDevice(NULL)
    ,m_lpDDBackBuffer(NULL)
    ,m_lpDDMirror(NULL)
    ,m_lpDDM32(NULL)
    ,m_lpDDM16(NULL)
    ,m_fPowerOf2(false)
    ,m_fSquare(false)
{
    ASSERT(phr);
    ZeroMemory(&m_ddsdM32, sizeof(m_ddsdM32));
    ZeroMemory(&m_ddsdM16, sizeof(m_ddsdM16));

    HRESULT hr;
    hr = lpDDSDst->GetDDInterface((LPVOID *)&m_pDD);
    if (FAILED(hr))
    {
        m_pDD = NULL;
        *phr = hr;
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pDD->QueryInterface(IID_IDirect3D7, (LPVOID *)&m_pD3D);
        if (FAILED(hr))
        {
            m_pD3D = NULL;
            *phr = hr;
        }
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pD3D->CreateDevice(IID_IDirect3DHALDevice,
                                  lpDDSDst,
                                  &m_pD3DDevice);
        if (FAILED(hr))
        {
            m_pD3DDevice = NULL;
            *phr = hr;
        }
        else
        {
            m_lpDDBackBuffer = lpDDSDst;
        }
    }

    *phr = hr;
  
    if (SUCCEEDED(hr))
    {

        D3DDEVICEDESC7 ddDesc;
        if (DD_OK == m_pD3DDevice->GetCaps(&ddDesc))
        {
            if (ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_POW2)
            {
                m_fPowerOf2 = true;
            }

            if (ddDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_SQUAREONLY)
            {
                m_fSquare = true;
            }
        }
        else
        {
            *phr = hr;
        }
    }    
}


//----------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------
CD3DHelper::~CD3DHelper()
{
    ;
}


//----------------------------------------------------------------------------
//  Name:   MirrorSourceSurface
//  Desc:   
//          The mirror surface cab be either 16 or 32 bit RGB depending
//          upon the format of the source surface.
//          Of course it should have the "texture" flag
//          set and should be in VRAM.  If we can't create the
//          surface then the AlphaBlt should fail
//----------------------------------------------------------------------------
HRESULT CD3DHelper::MirrorSourceSurface( LPDIRECTDRAWSURFACE7 lpDDS,
                                         DDSURFACEDESC2& ddsd )
{
    HRESULT hr = DD_OK;
    DWORD dwMirrorBitDepth = 0;
    DDSURFACEDESC2 ddsdMirror={0};

    //
    // I use the following rules:
    //  if ddsd is a FOURCC surface the mirror should be 32 bit
    //  if ddsd is RGB then the mirror's bit depth should match
    //      that of ddsd.
    //
    // Also, the mirror must be large enough to actually hold
    // the surface to be blended
    //

    m_lpDDMirror = NULL;

    if (ddsd.ddpfPixelFormat.dwFlags == DDPF_FOURCC ||
        ddsd.ddpfPixelFormat.dwRGBBitCount == 32) 
    {
        if (ddsd.dwWidth > m_ddsdM32.dwWidth ||
            ddsd.dwHeight > m_ddsdM32.dwHeight) 
        {
            m_lpDDM32 = NULL;
        }

        if (!m_lpDDM32) 
        {
            dwMirrorBitDepth = 32;
        }
        else 
        {
            m_lpDDMirror = m_lpDDM32;
            ddsdMirror = m_ddsdM32;
        }
    }
    else if (ddsd.ddpfPixelFormat.dwRGBBitCount == 16) 
    {
        if (ddsd.dwWidth > m_ddsdM16.dwWidth ||
            ddsd.dwHeight > m_ddsdM16.dwHeight) 
        {
            m_lpDDM16 = NULL;
        }

        if (!m_lpDDM16) 
        {
            dwMirrorBitDepth = 16;
        }
        else 
        {
            m_lpDDMirror = m_lpDDM16;
            ddsdMirror = m_ddsdM16;
        }
    }
    else 
    {
        // we are not supporting RGB24 or RGB8 !
        return E_INVALIDARG;
    }

    if (!m_lpDDMirror) 
    {
        INITDDSTRUCT(ddsdMirror);
        ddsdMirror.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
        ddsdMirror.ddpfPixelFormat.dwFlags = DDPF_RGB;
        ddsdMirror.ddpfPixelFormat.dwRGBBitCount = dwMirrorBitDepth;

        switch (dwMirrorBitDepth) 
        {
            case 16:
                ddsdMirror.ddpfPixelFormat.dwRBitMask = 0x0000F800;
                ddsdMirror.ddpfPixelFormat.dwGBitMask = 0x000007E0;
                ddsdMirror.ddpfPixelFormat.dwBBitMask = 0x0000001F;
                break;

            case 32:
                ddsdMirror.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
                ddsdMirror.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
                ddsdMirror.ddpfPixelFormat.dwBBitMask = 0x000000FF;
                break;
        }

        ddsdMirror.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_TEXTURE;
        ddsdMirror.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT;

        if (m_fPowerOf2) 
        {
            for (ddsdMirror.dwWidth = 1;
                 ddsd.dwWidth > ddsdMirror.dwWidth;
                 ddsdMirror.dwWidth <<= 1);

            for (ddsdMirror.dwHeight = 1;
                 ddsd.dwHeight > ddsdMirror.dwHeight;
                 ddsdMirror.dwHeight <<= 1);
        }
        else 
        {
            ddsdMirror.dwWidth = ddsd.dwWidth;
            ddsdMirror.dwHeight = ddsd.dwHeight;
        }

        if (m_fSquare) 
        {
            if (ddsdMirror.dwHeight > ddsdMirror.dwWidth) 
            {
                ddsdMirror.dwWidth = ddsdMirror.dwHeight;
            }

            if (ddsdMirror.dwWidth > ddsdMirror.dwHeight) 
            {
                ddsdMirror.dwHeight = ddsdMirror.dwWidth;
            }
        }
        __try 
        {
            // Attempt to create the surface with theses settings
            CHECK_HR(hr = m_pDD->CreateSurface(&ddsdMirror, &m_lpDDMirror, NULL));

            INITDDSTRUCT(ddsdMirror);
            CHECK_HR(hr =  m_lpDDMirror->GetSurfaceDesc(&ddsdMirror));

            switch (dwMirrorBitDepth) 
            {
                case 16:
                    m_ddsdM16 = ddsdMirror;
                    m_lpDDM16 = m_lpDDMirror;
                    break;

                case 32:
                    m_ddsdM32 = ddsdMirror;
                    m_lpDDM32 = m_lpDDMirror;
                    break;
            }

        } __finally {}
    }

    if (hr == DD_OK) 
    {
        __try 
        {
            RECT rc = {0, 0, ddsd.dwWidth, ddsd.dwHeight};
            CHECK_HR(hr = m_lpDDMirror->Blt(&rc, lpDDS, &rc, DDBLT_WAIT, NULL));
            ddsd = ddsdMirror;

        } __finally {}
    }

    return hr;
}


//-------------------------------------------------------------------------
// IsSurfaceBlendable
//
// Checks the DD surface description and the given
// alpha value to determine if this surface is
// blendable.
//-------------------------------------------------------------------------
bool CD3DHelper::IsSurfaceBlendable( DDSURFACEDESC2& ddsd )
{
    //
    // Is the surface already a D3D texture ?
    //
    if (ddsd.ddsCaps.dwCaps & DDSCAPS_TEXTURE) 
    {
        return true;
    }
    //
    // OK we have to mirror the surface
    //
    return false;
}


//----------------------------------------------------------------------------
//  RenderFrame
//  Renders a movie frame
//----------------------------------------------------------------------------
HRESULT CD3DHelper::RenderFrame(LPDIRECTDRAWSURFACE7 lpDDSSrc,  // source surface
                                Vertex *pv,                     // vertex buffer, it is always of size 4 here   
                                RECT rcDest,                    // destination rectangle
                                RECT rcOriginalTarget,          // we calculate all the scene settings for some 
                                                                // fixed rectangle and rescale it here according to
                                                                // the currect video window size
                                BOOL bSelectedMovie)            // TRUE if rendering frames of selected channel         
{
    HRESULT hr = S_OK;
    BYTE alpha = 0xC0; // alpha-level of the movie frame
    D3DCOLOR clrFrame = 0xFF006E7F; // color of the frame
    int nFrameThickness = 1; 
    
    if( !lpDDSSrc || !pv )
    {
        return E_POINTER;
    }

    if( bSelectedMovie )
    {
        alpha = 0xE0;
        clrFrame = 0xFFDDDD00;
        nFrameThickness = 2;
    }

    // check if we are provided with valid render target rectangle
    if( 0 >= rcOriginalTarget.right - rcOriginalTarget.left ||
        0 >= rcOriginalTarget.bottom - rcOriginalTarget.top ||
        0 >= rcDest.right - rcDest.left ||
        0 >= rcDest.bottom - rcDest.top )
    {
        return E_INVALIDARG;
    }

    Vertex pVertices[4];
    DDSURFACEDESC2 ddsd;
    float dx = (rcDest.left + rcDest.right)/2.f;    // center of the render target
    float dy = (rcDest.top + rcDest.bottom)/2.f;
    float h;
    float w;

    // in effects, scene is calculated for rcOriginalTarget, so we need to rescale it here
    // to fit in rcDest
    h = (float)(rcDest.bottom - rcDest.top);
    w = (float)(rcOriginalTarget.right - rcOriginalTarget.left) * h / (float)(rcOriginalTarget.bottom - rcOriginalTarget.top);

    if( w > (float)(rcDest.right - rcDest.left) )
    {
        w = (float)(rcDest.right - rcDest.left);
        h = (float)(rcOriginalTarget.bottom - rcOriginalTarget.top) * w / (float)(rcOriginalTarget.right - rcOriginalTarget.left);
    }

    // scaling factor from render target rect to the real render target of the window
    float scale = h / (float)(rcOriginalTarget.bottom - rcOriginalTarget.top);
    
    for( int i=0; i<4; i++)
    {
        pVertices[i] = pv[i];
        pVertices[i].x = (pv[i].x - dx) * scale + dx;
        pVertices[i].y = (pv[i].y - dy) * scale + dy;
        pVertices[i].clr = RGBA_MAKE(0xff,0xff,0xff,alpha);
    }

    __try 
    {

        INITDDSTRUCT(ddsd);
        CHECK_HR(hr = lpDDSSrc->GetSurfaceDesc(&ddsd));

        // if HW/driver does not support alpha-blending, use mirror surface
        if (!IsSurfaceBlendable(ddsd)) 
        {
            CHECK_HR(hr = MirrorSourceSurface(lpDDSSrc, ddsd));
            lpDDSSrc = m_lpDDMirror;
        }

        BeginScene();

        //
        // Setup D3D
        //
        m_pD3DDevice->SetTexture(0, lpDDSSrc);
        m_pD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
        m_pD3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING, FALSE);
        m_pD3DDevice->SetRenderState(D3DRENDERSTATE_BLENDENABLE, TRUE);
        m_pD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
        m_pD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

        // use diffuse alpha from vertices, not texture alpha
        m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

        // use texture to fill triangles
        m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

        // set dithering quality of the picture
        CHECK_HR(hr = m_pD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT));
        CHECK_HR(hr = m_pD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT));
        CHECK_HR(hr = m_pD3DDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_POINT));

        m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ADDRESS, D3DTADDRESS_CLAMP);

        CHECK_HR(hr = m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
                                                  D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1,
                                                  pVertices, 4, D3DDP_WAIT));

        EndScene(); 

    }// try
    __finally
    {
        m_pD3DDevice->SetTexture(0, NULL);
    }

    BeginScene();
    m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    FrameRect( pVertices[0].x, pVertices[0].y, pVertices[3].x, pVertices[3].y, clrFrame, nFrameThickness);
    EndScene();

    return hr;
}


//----------------------------------------------------------------------------
//  FrameRect
//  Draws rectangle frame of specified color
//----------------------------------------------------------------------------
HRESULT CD3DHelper::FrameRect(LPRECT lpDst, D3DCOLOR clr)
{
    struct 
    {
        float x, y, z, rhw;
        D3DCOLOR clr;

    } pVertices[5];

    pVertices[0].x   = (float)lpDst->left;
    pVertices[0].y   = (float)lpDst->top;
    pVertices[0].z   = 0.5f;
    pVertices[0].rhw = 2.0f;
    pVertices[0].clr = clr;

    pVertices[1].x   = (float)lpDst->right;
    pVertices[1].y   = (float)lpDst->top;
    pVertices[1].z   = 0.5f;
    pVertices[1].rhw = 2.0f;
    pVertices[1].clr = clr;

    pVertices[2].x   = (float)lpDst->right;
    pVertices[2].y   = (float)lpDst->bottom;
    pVertices[2].z   = 0.5f;
    pVertices[2].rhw = 2.0f;
    pVertices[2].clr = clr;

    pVertices[3].x   = (float)lpDst->left;
    pVertices[3].y   = (float)lpDst->bottom;
    pVertices[3].z   = 0.5f;
    pVertices[3].rhw = 2.0f;
    pVertices[3].clr = clr;

    pVertices[4] = pVertices[0];

    return m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP,
                                       D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
                                       pVertices, 5, D3DDP_WAIT);
}


//----------------------------------------------------------------------------
//  FrameRect
//  Draws rectangle frame of specified color and specified width
//----------------------------------------------------------------------------
HRESULT CD3DHelper::FrameRect(FLOAT fLeft, FLOAT fTop, FLOAT fRight, 
                              FLOAT fBottom, D3DCOLOR clr, long lPenWidth)
{
    struct 
    {
        float x, y, z, rhw;
        D3DCOLOR clr;

    } pVertices[10];

    // 1st Triangle V0, V1, V2
    pVertices[0].x   = fLeft;
    pVertices[0].y   = fTop;
    pVertices[0].z   = 0.5f;
    pVertices[0].rhw = 2.0f;
    pVertices[0].clr = clr;

    pVertices[1].x   = fLeft + (FLOAT)lPenWidth;
    pVertices[1].y   = fTop  + (FLOAT)lPenWidth;
    pVertices[1].z   = 0.5f;
    pVertices[1].rhw = 2.0f;
    pVertices[1].clr = clr;

    pVertices[2].x   = fRight;
    pVertices[2].y   = fTop;
    pVertices[2].z   = 0.5f;
    pVertices[2].rhw = 2.0f;
    pVertices[2].clr = clr;

    // 2nd Triangle V1, V2, V3
    pVertices[3].x   = fRight - (FLOAT)lPenWidth;
    pVertices[3].y   = fTop   + (FLOAT)lPenWidth;
    pVertices[3].z   = 0.5f;
    pVertices[3].rhw = 2.0f;
    pVertices[3].clr = clr;

    // 3rd Triangle V2, V3, V4
    pVertices[4].x   = fRight;
    pVertices[4].y   = fBottom;
    pVertices[4].z   = 0.5f;
    pVertices[4].rhw = 2.0f;
    pVertices[4].clr = clr;

    // 4th Triangle V3, V4, V5
    pVertices[5].x   = fRight  - (FLOAT)lPenWidth;
    pVertices[5].y   = fBottom - (FLOAT)lPenWidth;
    pVertices[5].z   = 0.5f;
    pVertices[5].rhw = 2.0f;
    pVertices[5].clr = clr;

    // 5th Triangle V4, V5, V6
    pVertices[6].x   = fLeft;
    pVertices[6].y   = fBottom;
    pVertices[6].z   = 0.5f;
    pVertices[6].rhw = 2.0f;
    pVertices[6].clr = clr;

    // 6th Triangle V5, V6, V7
    pVertices[7].x   = fLeft  + (FLOAT)lPenWidth;
    pVertices[7].y   = fBottom - (FLOAT)lPenWidth;
    pVertices[7].z   = 0.5f;
    pVertices[7].rhw = 2.0f;
    pVertices[7].clr = clr;

    // 7th Triangle V6, V7, V8
    pVertices[8] = pVertices[0];

    // 8th Triangle V7, V8, V9
    pVertices[9] = pVertices[1];

    return m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
                                       D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
                                       pVertices, 10, D3DDP_WAIT);
}


//----------------------------------------------------------------------------
//  FrameRect
//  Draws rectangle of specified color
//----------------------------------------------------------------------------
HRESULT CD3DHelper::PaintRect(RECT* lpDst, D3DCOLOR clr)
{
    HRESULT hr;
    struct 
    {
        float x, y, z, rhw;
        D3DCOLOR clr;

    } pVertices[4];

    pVertices[0].x   = (float)lpDst->left;
    pVertices[0].y   = (float)lpDst->top;
    pVertices[0].z   = 0.5f;
    pVertices[0].rhw = 2.0f;
    pVertices[0].clr = clr;

    pVertices[1].x   = (float)lpDst->right;
    pVertices[1].y   = (float)lpDst->top;
    pVertices[1].z   = 0.5f;
    pVertices[1].rhw = 2.0f;
    pVertices[1].clr = clr;

    pVertices[2].x   = (float)lpDst->left;
    pVertices[2].y   = (float)lpDst->bottom;
    pVertices[2].z   = 0.5f;
    pVertices[2].rhw = 2.0f;
    pVertices[2].clr = clr;

    pVertices[3].x   = (float)lpDst->right;
    pVertices[3].y   = (float)lpDst->bottom;
    pVertices[3].z   = 0.5f;
    pVertices[3].rhw = 2.0f;
    pVertices[3].clr = clr;

    hr = m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
                                     D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
                                     pVertices, 4, D3DDP_WAIT);
    return hr;
}


