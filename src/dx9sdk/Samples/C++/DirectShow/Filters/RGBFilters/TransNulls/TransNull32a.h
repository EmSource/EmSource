//------------------------------------------------------------------------------
// File: TransNull32a.h
//
// Desc: DirectShow sample code - header for RGBFilters component
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

extern const AMOVIESETUP_FILTER sudTransNull32a;

class CTransNull32a : public CTransInPlaceFilter
{
public:

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    DECLARE_IUNKNOWN;

    HRESULT Transform(IMediaSample *pSample);
    HRESULT CheckInputType(const CMediaType *mtIn);

private:

    // Constructor
    CTransNull32a( LPUNKNOWN punk, HRESULT *phr );
};

