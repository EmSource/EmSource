//------------------------------------------------------------------------------
// File: Source565.h
//
// Desc: DirectShow sample code - header for RGBFilters component
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#ifndef __RGBFilters__Source565_H
#define __RGBFilters__Source565_H

extern const AMOVIESETUP_FILTER sudSource565Bit;

class CSource565Bit 
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
    CSource565Bit(LPUNKNOWN lpunk, HRESULT *phr);
    ~CSource565Bit();
    
    STDMETHODIMP NonDelegatingQueryInterface( REFIID riid, void ** ppv );

    int GetPinCount();
    CBasePin *GetPin(int n);
};


// CSource565BitStream manages the data flow from the output pin.
//
class CSource565BitStream 
    : public CSourceStream
    , public CSourceSeeking
{
    HBITMAP     m_DibSection;
    HDC         m_DC;
    void *      m_pDibBits;
    HGDIOBJ     m_OldObject;
    long        m_nX;
    long        m_nY;
    long        m_nVx;
    long        m_nVy;
    long        m_nSize;

    friend CSource565Bit;

public:

    CSource565BitStream(HRESULT *phr, CSource565Bit *pParent, LPCWSTR pPinName);
    ~CSource565BitStream();
    STDMETHODIMP NonDelegatingQueryInterface( REFIID riid, void ** ppv );

    // fills in the bits for our output frame
    //
    HRESULT FillBuffer(IMediaSample *pms);

    // Ask for buffers of the size appropriate to the agreed media type
    //
    HRESULT DecideBufferSize(IMemAllocator *pIMemAlloc,
                             ALLOCATOR_PROPERTIES *pProperties);

    // negotiate these for the correct output type
    //
    HRESULT CheckMediaType(const CMediaType *pMediaType);
    HRESULT GetMediaType(int iPosition, CMediaType *pmt);

    // Resets the stream time to zero
    //
    HRESULT OnThreadStartPlay( );

    // need to override or we'll get an assert
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

    int       m_iDelivered;           // how many samples we delivered
    CCritSec  m_SeekLock;
};

#endif
