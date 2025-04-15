//------------------------------------------------------------------------------
// File: AlphaRenderer.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "AlphaRenderer.h"

// This simple rendering filter will display a checkered window when 
// connected and will draw incoming ARGB on top of it, 
// alpha blended onto the checkerboard.

// Filter registration
AMOVIESETUP_FILTER sudAlphaRenderer =
{
    &CLSID_AlphaRenderer,
    L"AlphaRenderer",
    MERIT_DO_NOT_USE,
    0,                  // # of pins
    NULL                // pin struct
};

CAlphaRenderer::CAlphaRenderer( IUnknown * pUnk, HRESULT * phr )
    : CBaseRenderer( CLSID_AlphaRenderer, NAME("AlphaRenderer"), pUnk, phr )
    , m_hWnd( NULL )
    , m_hDC( NULL )
    , m_nWidth( 0 )
    , m_nHeight( 0 )
    , m_pCheckers( NULL )
{
}

CAlphaRenderer::~CAlphaRenderer( )
{
    _Clear( );
}

// throw away the window and the checkerboard pattern
//
void CAlphaRenderer::_Clear( )
{
    if( m_hDC )
    {
        ReleaseDC( m_hWnd, m_hDC );
    }
    if( m_hWnd )
    {
        DestroyWindow( m_hWnd );
    }
    if( m_pCheckers )
    {
        delete [] m_pCheckers;
    }
}

// Called when we go paused or running

HRESULT CAlphaRenderer::Active()
{
    // Make our renderer window visible
    ShowWindow(m_hWnd, SW_SHOWNORMAL);

    return CBaseRenderer::Active();
}


// Called when we go into a stopped state

HRESULT CAlphaRenderer::Inactive()
{
    // Hide our renderer window
    ShowWindow(m_hWnd, SW_HIDE);

    return CBaseRenderer::Inactive();
}

// make sure media type is what we want
//
HRESULT CAlphaRenderer::CheckMediaType( const CMediaType *pmtIn )
{
    CheckPointer(pmtIn,E_POINTER);

    // the major type must match
    //
    if( *pmtIn->Type( ) != MEDIATYPE_Video )
    {
        return E_INVALIDARG;
    }

    // the sub type must match
    //
    if( *pmtIn->Subtype( ) != MEDIASUBTYPE_ARGB32 )
    {
        return E_INVALIDARG;
    }

    // the format must match
    //
    if( *pmtIn->FormatType( ) != FORMAT_VideoInfo )
    {
        return E_INVALIDARG;
    }

    VIDEOINFOHEADER * pVIH = (VIDEOINFOHEADER*) pmtIn->Format( );

    // we could do more here to ensure the image is right-side up
    // by looking at the bitmap info header in the VIDEOINFO struct
    //
    return 0;
}

// have to ovverride this, render the incoming sample onto the checkerboard
//
HRESULT CAlphaRenderer::DoRenderSample( IMediaSample *pMediaSample )
{
    CheckPointer(pMediaSample,E_POINTER);

    BYTE * pBits;
    pMediaSample->GetPointer( &pBits );

    long len = pMediaSample->GetActualDataLength( );

    // now blend checkerboard into bits before we blit them
    
    // the incoming source
    //
    RGBQUAD * pSource = (RGBQUAD*) pBits;

    // the checkerboard buffer
    //
    RGBQUAD * pCheckers = (RGBQUAD*) m_pCheckers;

    // blend them
    //
    for( int x = 0 ; x < m_nWidth * m_nHeight ; x++ )
    {
        RGBQUAD d;
        d.rgbRed   = (BYTE) (pSource->rgbRed * pSource->rgbReserved / 256 + 
                        pCheckers->rgbRed  * ( 256 - pSource->rgbReserved ) / 256);

        d.rgbGreen = (BYTE) (pSource->rgbGreen * pSource->rgbReserved / 256 + 
                        pCheckers->rgbGreen * ( 256 - pSource->rgbReserved ) / 256);

        d.rgbBlue  = (BYTE) (pSource->rgbBlue * pSource->rgbReserved / 256 + 
                        pCheckers->rgbBlue * ( 256 - pSource->rgbReserved ) / 256);
        *pSource = d;
        pSource++;
        pCheckers++;
    }

    // put the bits into the window
    //
    StretchDIBits( m_hDC, 
                   0, 0, m_nWidth, m_nHeight, 
                   0, 0, m_nWidth, m_nHeight, 
                   pBits, (BITMAPINFO*) &m_BMI, 
                   DIB_RGB_COLORS, SRCCOPY );

    return 0;
}

// Must override this. We create the window here
//
HRESULT CAlphaRenderer::SetMediaType( const CMediaType *pmt )
{
    CheckPointer(pmt,E_POINTER);

    _Clear( );

    // we know it's a VIDEOINFOHEADER, since we demanded one
    // in CheckMediaType
    //
    VIDEOINFOHEADER * pVI = (VIDEOINFOHEADER*) pmt->Format( );
    CheckPointer(pVI,E_UNEXPECTED);

    long Width  = m_nWidth = pVI->bmiHeader.biWidth;
    long Height = m_nHeight = pVI->bmiHeader.biHeight;

    // save this off for lookin' at it later
    //
    m_BMI = pVI->bmiHeader;

    // create the window
    //
    m_hWnd = CreateWindow( TEXT("STATIC"), 
                           TEXT("Video Renderer"),
                           WS_POPUP,        // NOT Visible
                           0, 0, Width, Height, 
                           NULL, NULL, g_hInst, NULL );

    // get the DC
    //
    m_hDC = GetDC( m_hWnd );

    // create a checker buffer
    //
    m_pCheckers = new DWORD[ Width * Height ];

    // draw the checkers
    //
    for( int x = 0 ; x < Width ; x++ )
    {
        for( int y = 0 ; y < Height ; y++ )
        {
            bool OnOff = false;

            if( x / 8 % 2 == 0 )
            {
                OnOff = !OnOff;
            }
            if( y / 8 % 2 == 0 )
            {
                OnOff = !OnOff;
            }

            DWORD * p = (DWORD*) m_pCheckers;
            p += y * Width;
            p += x;

            if( !OnOff )
            {
                *p = 0;    
            }
            else
            {
                *p = 0xFFFFFF;
            }
        }
    }

    return 0;
}

// only way to make one of these
//
CUnknown * WINAPI CAlphaRenderer::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    return new CAlphaRenderer( lpunk, phr );
}

