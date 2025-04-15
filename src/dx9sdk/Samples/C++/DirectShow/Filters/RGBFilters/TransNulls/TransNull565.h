//------------------------------------------------------------------------------
// File: TransNull565.h
//
// Desc: DirectShow sample code - header for RGBFilters component
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

extern const AMOVIESETUP_FILTER sudTransNull565;

class CTransNull565 : public CTransInPlaceFilter
{
public:

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

    DECLARE_IUNKNOWN;

    HRESULT Transform(IMediaSample *pSample);
    HRESULT CheckInputType(const CMediaType *mtIn);

private:

    // Constructor
    CTransNull565( LPUNKNOWN punk, HRESULT *phr );
};

