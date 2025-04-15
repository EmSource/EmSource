//------------------------------------------------------------------------------
// File: TransSmpte.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "TransSmpte.h"

const AMOVIESETUP_FILTER sudTransSmpte =
{
    &CLSID_TransSmpte,   // Filter CLSID
    L"TransSmpte",       // String name
    MERIT_DO_NOT_USE,    // Filter merit
    0,                   // Number pins
    NULL                 // Pin details
};

CUnknown * WINAPI CTransSmpte::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CTransSmpte(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

}

CTransSmpte::CTransSmpte(LPUNKNOWN punk,HRESULT *phr) 
    : CTransInPlaceFilter(TEXT("TransSmpte"), punk, CLSID_TransSmpte, phr)
    , m_nWidth(0)
    , m_nHeight(0)
    , m_pDibBits(NULL)
    , m_DibSection(NULL)
    , m_DC(NULL)
    , m_OldObject(NULL)
    , m_dFPS( 0.0 )
{
}

CTransSmpte::~CTransSmpte( )
{
    if( m_OldObject )
    {
        SelectObject( m_DC, m_OldObject );
        m_OldObject = NULL;
    }
    if( m_DC )
    {
        DeleteDC( m_DC );
        m_DC = NULL;
    }
    if( m_DibSection )
    {
        DeleteObject( m_DibSection );
        m_DibSection = NULL;
    }
}


HRESULT CTransSmpte::SetMediaType( PIN_DIRECTION pindir, const CMediaType *pMediaType)
{
    CheckPointer(pMediaType,E_POINTER);

    VIDEOINFO* pVI = (VIDEOINFO*) pMediaType->Format();
    CheckPointer(pVI,E_UNEXPECTED);

    m_nWidth  = pVI->bmiHeader.biWidth;
    m_nHeight = pVI->bmiHeader.biHeight;

    double tpf = double(pVI->AvgTimePerFrame) / UNITS;
    m_dFPS = tpf;

    return CTransInPlaceFilter::SetMediaType( pindir, pMediaType );
}


HRESULT CTransSmpte::CheckInputType(const CMediaType *mtIn)
{
    CheckPointer(mtIn,E_POINTER);

    if (*mtIn->FormatType() != FORMAT_VideoInfo)
    {
        return E_INVALIDARG;
    }

    if( *mtIn->Type( ) != MEDIATYPE_Video )
    {
        return E_INVALIDARG;
    }

    if( *mtIn->Subtype( ) != MEDIASUBTYPE_RGB32 )
    {
        return E_INVALIDARG;
    }

    VIDEOINFO *pVI = (VIDEOINFO *) mtIn->Format();
    CheckPointer(pVI,E_UNEXPECTED);

    if( pVI->bmiHeader.biBitCount != 32 )
    {
        return E_INVALIDARG;
    }

    // Reject negative height bitmaps to prevent drawing upside-down text
    if( pVI->bmiHeader.biHeight < 0 )
    {
        return E_INVALIDARG;
    }

    return NOERROR;
}


HRESULT CTransSmpte::Transform(IMediaSample *pSample)
{
    CheckPointer(pSample,E_POINTER);

    if( m_DibSection == NULL )
    {
        VIDEOINFO* pVI = (VIDEOINFO*) m_pInput->CurrentMediaType( ).Format( );
        CheckPointer(pVI,E_UNEXPECTED);

        m_DibSection = CreateDIBSection(
                                        NULL,
                                        (BITMAPINFO*) &pVI->bmiHeader,
                                        DIB_RGB_COLORS,
                                        &m_pDibBits,
                                        NULL,
                                        0
                                        );
        if( !m_DibSection )
        {
            return E_FAIL;
        }

        HDC hdc = GetDC( NULL );
        m_DC = CreateCompatibleDC( hdc );
        if( !m_DC )
            return E_FAIL;

        ReleaseDC( NULL, hdc );

        m_OldObject = SelectObject( m_DC, m_DibSection );
        if( !m_OldObject )
            return E_FAIL;
    }

    // Read the current frame time
    REFERENCE_TIME rtStart = 0;
    REFERENCE_TIME rtStop = 0;
    pSample->GetTime( &rtStart, &rtStop );

    // Convert the frame time into hours, minutes, seconds
    double dStart = double( double( rtStart ) / UNITS );
    int nHours   = (int) (dStart / ( 3600 ));
    int nMinutes = (int) (( dStart / 60 ) - ( nHours * 60 ));
    int nSeconds = (int) (( dStart ) - ( nMinutes * 60 ));
    int nFrames  = (int) (dStart / m_dFPS);

    char *pBuffer = 0;
    pSample->GetPointer( (LPBYTE*) &pBuffer );
    RGBQUAD * pBuffer2 = (RGBQUAD*) pBuffer;

    // Copy the frame into our DIB section, onto which we will draw
    // the frame time
    memcpy( m_pDibBits, pBuffer, m_nWidth * m_nHeight * 4 );

    // Set to medium blue text (on a white opaque background) for readability
    SetTextColor(m_DC, RGB(0,128,192));

    // Draw the current frame
    TCHAR szText[256];
    wsprintf( szText, TEXT("Frame %8.8ld\0"), nFrames );
    BOOL bWorked = TextOut( m_DC, 10, 10, szText, _tcslen( szText ) );

    // Draw the current frame time
    if (m_dFPS != 0)
    {
        nFrames = nFrames % long( 1.0 / m_dFPS );
        wsprintf( szText, TEXT("H:%2.2ld M:%2.2ld S:%2.2ld F:%2.2ld\0"), 
                  nHours, nMinutes, nSeconds, nFrames );
        bWorked = TextOut( m_DC, 10, 30, szText, _tcslen( szText ) );
    }
    else
    {
        wsprintf( szText, TEXT("H:%2.2ld M:%2.2ld S:%2.2ld F:?? ??\0"), 
                  nHours, nMinutes, nSeconds);
        bWorked = TextOut( m_DC, 10, 30, szText, _tcslen( szText ) );
    }

    // Draw the current frames-per-second calculation
    if (m_dFPS != 0)
    {
        wsprintf( szText, TEXT("FPS = %ld\0"), long( 1.0 / m_dFPS ) );
        bWorked = TextOut( m_DC, 10, 50, szText, _tcslen( szText ) );
    }
    else
    {
        wsprintf( szText, TEXT("FPS = ??\0") );
        bWorked = TextOut( m_DC, 10, 50, szText, _tcslen( szText ) );
    }

    // Copy our modified bitmap into the original sample buffer
    memcpy( pBuffer, m_pDibBits, m_nWidth * m_nHeight * 4 );

    return NOERROR;
}

