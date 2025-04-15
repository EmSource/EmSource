//------------------------------------------------------------------------------
// File: RateSource.h
//
// Desc: DirectShow sample code - header for RGBFilters component
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#ifndef __RGBFilters__RateSource_H
#define __RGBFilters__RateSource_H

extern const AMOVIESETUP_FILTER sudRateSource;

class CRateSource 
    : public CSource
{
protected:

    // the filename we're hosting
    //
    WCHAR m_Filename[_MAX_PATH];

public:

    // only way to make one of these
    //
    static CUnknown * WINAPI CreateInstance(LPUNKNOWN lpunk, HRESULT *phr);

private:

    // required
    //
    DECLARE_IUNKNOWN
    CRateSource(LPUNKNOWN lpunk, HRESULT *phr);
    ~CRateSource();
    
    STDMETHODIMP NonDelegatingQueryInterface( REFIID riid, void ** ppv );

    int GetPinCount();
    CBasePin *GetPin(int n);
};


// CRateSourceStream manages the data flow from the output pin.
//
class CRateSourceStream 
    : public CSourceStream
    , public CSourceSeeking
{
    HBITMAP     m_DibSection;
    HDC         m_DC;
    void *      m_pDibBits;
    HGDIOBJ     m_OldObject;

    friend CRateSource;

public:

    CRateSourceStream(HRESULT *phr, CRateSource *pParent, LPCWSTR pPinName);
    ~CRateSourceStream();
    STDMETHODIMP NonDelegatingQueryInterface( REFIID riid, void ** ppv );

    // Fills in the bits for our output frame
    //
    HRESULT FillBuffer(IMediaSample *pms);

    // Ask for buffers of the size appropriate to the agreed media type
    //
    HRESULT DecideBufferSize(IMemAllocator *pIMemAlloc,
                             ALLOCATOR_PROPERTIES *pProperties);

    // Negotiate these for the correct output type
    //
    HRESULT CheckMediaType(const CMediaType *pMediaType);
    HRESULT GetMediaType(int iPosition, CMediaType *pmt);

    // Resets the stream time to zero
    //
    HRESULT OnThreadStartPlay( );

    // Need to override or we'll get an assert
    STDMETHODIMP Notify( IBaseFilter * pFilter, Quality q ) 
    { 
        return S_OK; 
    }

    // CSourceSeeking
    //
    HRESULT ChangeStart( );
    HRESULT ChangeStop( );
    HRESULT ChangeRate( );

protected:

    int       m_iDelivered;   // how many samples we delivered
    CCritSec  m_SeekLock;
    int       m_nBitDepth;
};

#endif
