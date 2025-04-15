//-----------------------------------------------------------------------------
// File: DShow.h
//
// Desc: DirectShow sample code
//
//  Copyright (c) 1992-2002 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

// The class managing the output pin
class CSparkleStream;

// Main object for a sparkle filter
class CSparkle : public CSource
{

public:

    // The only allowed way to create Bouncing balls!
    static CUnknown * WINAPI CreateInstance(LPUNKNOWN lpunk, HRESULT *phr);

private:

    // It is only allowed to to create these objects with CreateInstance
    CSparkle(LPUNKNOWN lpunk, HRESULT *phr);

}; // CSparkle


// CSparkleStream manages the data flow from the output pin.
class CSparkleStream : public CSourceStream
{

public:

    CSparkleStream(HRESULT *phr, CSparkle *pParent, LPCWSTR pPinName);
    ~CSparkleStream();

    // plots image into the supplied video frame
    HRESULT FillBuffer(IMediaSample *pms);

    // Ask for buffers of the size appropriate to the agreed media type
    HRESULT DecideBufferSize(IMemAllocator *pIMemAlloc,
                             ALLOCATOR_PROPERTIES *pProperties);

    // Set the agreed media type, and set up the necessary parameters
    HRESULT SetMediaType(const CMediaType *pMediaType);
    HRESULT CheckMediaType(const CMediaType *pMediaType);
    HRESULT GetMediaType(int iPosition, CMediaType *pmt);

    // Resets the stream time to zero
    HRESULT OnThreadCreate(void);

    // Quality control notifications sent to us
    STDMETHODIMP Notify(IBaseFilter * pSender, Quality q);

    HRESULT DoBufferProcessingLoop(void);    // the loop executed while running


private:
    int             m_iImageHeight;     // The current image height
    int             m_iImageWidth;      // And current image width
    REFERENCE_TIME  m_rSampleTime;      // The time stamp for each sample
    CAlphaBlt*      m_lpAlphaBlt;

}; // CSparkleStream
    
