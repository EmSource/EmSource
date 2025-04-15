//------------------------------------------------------------------------------
// File: RateStream.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "ratesource.h"
#include "uuids.h"

// Constants
const long gScale = 1;
const long gRate = 24;
const long DEFAULT_WIDTH = 320;
const long DEFAULT_HEIGHT = 240;
const REFERENCE_TIME DEFAULT_DURATION = 768 * UNITS;

#define DBGLVL 3
#define OUTPUTTYPE MEDIASUBTYPE_RGB24


LONGLONG inline Time2Frame( REFERENCE_TIME rt, long Scale, long Rate )
{
    return llMulDiv( rt, Rate, Scale * UNITS, 0 );
}

REFERENCE_TIME inline Frame2Time( LONGLONG Frame, long Scale, long Rate )
{
    return llMulDiv( Frame, Scale * UNITS, Rate, Rate - 1 );
}

//**************************************************************************
// 
//**************************************************************************
//
CRateSourceStream::CRateSourceStream(HRESULT *phr, CRateSource *pParent, LPCWSTR pPinName)
     : CSourceStream(NAME("RateSource"),phr, pParent, pPinName)
     , CSourceSeeking( NAME("RateSource"), (IPin*) this, phr, &m_SeekLock )
     , m_iDelivered( 0 )
     , m_pDibBits(NULL)
     , m_DibSection(NULL)
     , m_DC(NULL)
     , m_OldObject(NULL)
{
    // m_rtDuration is defined as the length of the source clip.
    // we default to the maximum amount of time.
    //
    m_rtDuration = DEFAULT_DURATION;
    m_rtStop = m_rtDuration;

    // no seeking to absolute pos's and no seeking backwards!
    //
    m_dwSeekingCaps = 
        AM_SEEKING_CanSeekForwards |
        AM_SEEKING_CanGetStopPos   |
        AM_SEEKING_CanGetDuration  |
        AM_SEEKING_CanSeekAbsolute;

}

//**************************************************************************
// 
//**************************************************************************
//
CRateSourceStream::~CRateSourceStream()
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

//**************************************************************************
// 
//**************************************************************************
//
STDMETHODIMP CRateSourceStream::NonDelegatingQueryInterface( REFIID riid, void ** ppv )
{
    if( riid == IID_IMediaSeeking ) 
    {
        return CSourceSeeking::NonDelegatingQueryInterface( riid, ppv );
    }
    return CSourceStream::NonDelegatingQueryInterface(riid, ppv);
}

//**************************************************************************
// 
//**************************************************************************
//
HRESULT CRateSourceStream::ChangeRate( )
{
    return NOERROR;
}

//**************************************************************************
// GetMediaType. Return the only output format this one supports.
//**************************************************************************
//
HRESULT CRateSourceStream::GetMediaType(int iPosition, CMediaType *pmt)
{
    CheckPointer(pmt,E_POINTER);

    if (iPosition < 0) 
    {
        return E_INVALIDARG;
    }

    // Have we run off the end of types

    if( iPosition > 0 ) 
    {
        return VFW_S_NO_MORE_ITEMS;
    }

    VIDEOINFOHEADER vih;
    memset( &vih, 0, sizeof( vih ) );
    vih.bmiHeader.biCompression = BI_RGB;
    vih.bmiHeader.biBitCount    = 24;
    vih.bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);
    vih.bmiHeader.biWidth        = DEFAULT_WIDTH;
    vih.bmiHeader.biHeight       = DEFAULT_HEIGHT;
    vih.bmiHeader.biPlanes       = 1;
    vih.bmiHeader.biSizeImage    = GetBitmapSize(&vih.bmiHeader);
    vih.bmiHeader.biClrImportant = 0;
    vih.AvgTimePerFrame = UNITS * gScale / gRate;

    pmt->SetType(&MEDIATYPE_Video);
    pmt->SetFormatType(&FORMAT_VideoInfo);
    pmt->SetFormat( (BYTE*) &vih, sizeof( vih ) );
    pmt->SetSubtype(&OUTPUTTYPE);
    pmt->SetSampleSize(vih.bmiHeader.biSizeImage);
    m_nBitDepth = 24;

    return NOERROR;
}

//**************************************************************************
// CheckMediaType
//**************************************************************************
//
HRESULT CRateSourceStream::CheckMediaType(const CMediaType *pMediaType)
{
    CheckPointer(pMediaType,E_POINTER);

    // we only want fixed size video
    //
    if( *(pMediaType->Type()) != MEDIATYPE_Video )
    {
        return E_INVALIDARG;
    }
    if( !pMediaType->IsFixedSize( ) ) 
    {
        return E_INVALIDARG;
    }
    if( *pMediaType->Subtype( ) != OUTPUTTYPE)
    {
        return E_INVALIDARG;
    }
    if( *pMediaType->FormatType( ) != FORMAT_VideoInfo )
    {
        return E_INVALIDARG;
    }

    // Get the format area of the media type
    //
    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) pMediaType->Format();

    if (pvi == NULL)
    {
        return E_INVALIDARG;
    }

    return S_OK;

}

//**************************************************************************
// DecideBufferSize
//
// This will always be called after the format has been sucessfully
// negotiated. So we have a look at m_mt to see what size image we agreed.
// Then we can ask for buffers of the correct size to contain them.
//**************************************************************************
//
HRESULT CRateSourceStream::DecideBufferSize(IMemAllocator *pAlloc,
                                            ALLOCATOR_PROPERTIES *pProperties)
{
    CheckPointer(pAlloc,E_POINTER);
    CheckPointer(pProperties,E_POINTER);
    HRESULT hr = NOERROR;

    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) m_mt.Format();
    ASSERT(pvi);
    
    pProperties->cBuffers = 1;
    pProperties->cbBuffer = pvi->bmiHeader.biSizeImage;

    ASSERT(pProperties->cbBuffer);

    // Ask the allocator to reserve us some sample memory, NOTE the function
    // can succeed (that is return NOERROR) but still not have allocated the
    // memory that we requested, so we must check we got whatever we wanted

    ALLOCATOR_PROPERTIES Actual;
    hr = pAlloc->SetProperties(pProperties,&Actual);
    if (FAILED(hr)) 
    {
        return hr;
    }

    // Is this allocator unsuitable

    if (Actual.cbBuffer < pProperties->cbBuffer) 
    {
        return E_FAIL;
    }

    ASSERT( Actual.cBuffers == 1 );

    return NOERROR;
}

//**************************************************************************
//
//**************************************************************************
//
HRESULT CRateSourceStream::OnThreadStartPlay( )
{
    DeliverNewSegment( m_rtStart, m_rtStop, 1.0 );
    return CSourceStream::OnThreadStartPlay( );
}

//**************************************************************************
// FillBuffer. This routine fills up the given IMediaSample
//**************************************************************************
//
HRESULT CRateSourceStream::FillBuffer(IMediaSample *pms)
{
    CheckPointer(pms,E_POINTER);    
    HRESULT hr = 0;

    // you NEED to have a lock on the critsec you sent to CSourceSeeking, so
    // it doesn't fill while you're changing positions, because the timestamps
    // won't be right. m_iDelivered will be off.
    //
    CAutoLock Lock( &m_SeekLock );

    REFERENCE_TIME NextSampleStart = Frame2Time( m_iDelivered, gScale, gRate );
    REFERENCE_TIME NextSampleStop =  Frame2Time( m_iDelivered + 1, gScale, gRate );

    // calculate the second being delivered
    //
    double dSecondStart = double( NextSampleStart ) / UNITS;
    long SecondStart = (long) dSecondStart;
    dSecondStart -= double( SecondStart );
    dSecondStart *= gRate;

    long Frame = long( dSecondStart );
    long ActualFrame = Frame;
    if( SecondStart % 2 == 0 )
    {
        Frame = gRate - 1 - Frame;
    }

    // return S_FALSE if we've hit EOS. Parent class will send EOS for us
    //
    if( NextSampleStart > m_rtStop )
    {
        return S_FALSE;
    }

    // get the buffer and the bits
    //
    RGBTRIPLE * pData = NULL;
    hr = pms->GetPointer( (BYTE**) &pData );
    if( FAILED( hr ) )
    {
        return hr;
    }

    long lDataLen = pms->GetSize( );
    if( lDataLen == 0 )
    {
        return NOERROR;
    }

    memset( pData, 0, DEFAULT_WIDTH * DEFAULT_HEIGHT * 3 );

    for( int y = 0 ; y < DEFAULT_HEIGHT ; y++ )
    {
        long BlockY = y / ( DEFAULT_HEIGHT / 8 );

        for( int x = 0 ; x < DEFAULT_WIDTH ; x++ )
        {
            long BlockX = x / ( DEFAULT_WIDTH / 8 );

            long Block = BlockY * 8 + BlockX;

            if( Block < 32 )
            {
                if( ( SecondStart >> Block ) & 1 )
                {
                    pData->rgbtBlue = 255;
                    pData->rgbtGreen = 255;
                    pData->rgbtRed = 255;
                }
            }

            pData++;
        }
    }

    pms->GetPointer( (BYTE**) &pData );

    if( m_DibSection == NULL )
    {
        CMediaType mtype;
        GetMediaType( 0, &mtype );

        VIDEOINFO* pVI = (VIDEOINFO*) mtype.Format( );

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
        {
            return E_FAIL;
        }
        ReleaseDC( NULL, hdc );

        m_OldObject = SelectObject( m_DC, m_DibSection );
        if( !m_OldObject )
        {
            return E_FAIL;
        }
    }

    double dStart = double( NextSampleStart ) / UNITS;
    ASSERT( !IsBadReadPtr( m_pDibBits, DEFAULT_WIDTH * DEFAULT_HEIGHT * ( m_nBitDepth / 8 ) ) );

    memset( m_pDibBits, 0, DEFAULT_WIDTH * DEFAULT_HEIGHT * 3 );

    TCHAR string[256];
    wsprintf( string, TEXT("Frame %8.8ld"), m_iDelivered );
    BOOL worked = TextOut( m_DC, 10, 10, string, _tcslen( string ) );

    GdiFlush( );
    char * pBits = (char*) m_pDibBits;
    memcpy( 
        pData + DEFAULT_WIDTH * DEFAULT_HEIGHT * 9 / 10, // don't multiply by size
        pBits + DEFAULT_WIDTH * DEFAULT_HEIGHT * ( m_nBitDepth / 8 ) * 9 / 10, 
        DEFAULT_WIDTH * DEFAULT_HEIGHT * ( m_nBitDepth / 8 )  / 10 );

    pms->GetPointer( (BYTE**) &pData );

    for( y = 0 ; y < DEFAULT_HEIGHT ; y++ )
    {
        ( pData + ( DEFAULT_WIDTH * Frame / gRate ) + ( y * DEFAULT_WIDTH ) )->rgbtBlue  = 255;
        ( pData + ( DEFAULT_WIDTH * Frame / gRate ) + ( y * DEFAULT_WIDTH ) )->rgbtGreen = 255;
    }
    for( y = 0 ; y < DEFAULT_WIDTH ; y++ )
    {
        ( pData + y + ( DEFAULT_WIDTH * DEFAULT_HEIGHT * Frame / gRate ) )->rgbtRed   = 255;
        ( pData + y + ( DEFAULT_WIDTH * DEFAULT_HEIGHT * Frame / gRate ) )->rgbtGreen = 255;
    }

    m_iDelivered++;

    // set the timestamp
    //
    pms->SetTime( &NextSampleStart, &NextSampleStop );

    // set the sync point
    //
    pms->SetSyncPoint(true);

    return NOERROR;
}

//**************************************************************************
// 
//**************************************************************************
//
HRESULT CRateSourceStream::ChangeStart( )
{
    m_iDelivered = 0;

    if (ThreadExists()) 
    {
        // next time round the loop the worker thread will
        // pick up the position change.
        // We need to flush all the existing data - we must do that here
        // as our thread will probably be blocked in GetBuffer otherwise
        DeliverBeginFlush();

        // make sure we have stopped pushing
        Stop();

        // complete the flush
        DeliverEndFlush();

        // restart
        Run();
    }

    return NOERROR;
}

//**************************************************************************
// 
//**************************************************************************
//
HRESULT CRateSourceStream::ChangeStop( )
{
    return NOERROR;
}

