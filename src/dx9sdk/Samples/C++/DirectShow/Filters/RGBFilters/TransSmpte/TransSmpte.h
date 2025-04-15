//------------------------------------------------------------------------------
// File: TransSmpte.h
//
// Desc: DirectShow sample code - header for RGBFilters component
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

extern const AMOVIESETUP_FILTER sudTransSmpte;

class CTransSmpte : public CTransInPlaceFilter
{
public:

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    DECLARE_IUNKNOWN;

    HRESULT Transform(IMediaSample *pSample);
    HRESULT CheckInputType(const CMediaType *mtIn);
    HRESULT SetMediaType( PIN_DIRECTION pindir, const CMediaType *pMediaType);

private:

    // Constructor
    CTransSmpte( LPUNKNOWN punk, HRESULT *phr );
    ~CTransSmpte( );

    int         m_nWidth;
    int         m_nHeight;
    HBITMAP     m_DibSection;
    HDC         m_DC;
    void *      m_pDibBits;
    HGDIOBJ     m_OldObject;
    double      m_dFPS;
};

