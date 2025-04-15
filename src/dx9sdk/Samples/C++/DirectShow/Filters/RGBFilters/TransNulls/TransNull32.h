//------------------------------------------------------------------------------
// File: TransNull32.h
//
// Desc: DirectShow sample code - header for RGBFilters component
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

extern const AMOVIESETUP_FILTER sudTransNull32;

class CTransNull32 : public CTransInPlaceFilter
{
public:

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    DECLARE_IUNKNOWN;

    HRESULT Transform(IMediaSample *pSample);
    HRESULT CheckInputType(const CMediaType *mtIn);

private:

    // Constructor
    CTransNull32( LPUNKNOWN punk, HRESULT *phr );
};

