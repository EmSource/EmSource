//------------------------------------------------------------------------------
// File: TransNull32a.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "TransNull32a.h"

const AMOVIESETUP_FILTER sudTransNull32a =
{
    &CLSID_TransNull32a,    // Filter CLSID
    L"TransNull32a",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

CUnknown * WINAPI CTransNull32a::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CTransNull32a(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

}

CTransNull32a::CTransNull32a(LPUNKNOWN punk,HRESULT *phr) 
    : CTransInPlaceFilter(TEXT("TransNull32a"), punk, CLSID_TransNull32a, phr)
{
}

HRESULT CTransNull32a::CheckInputType(const CMediaType *mtIn)
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

    if( *mtIn->Subtype( ) != MEDIASUBTYPE_ARGB32 )
    {
        return E_INVALIDARG;
    }

    return NOERROR;
}

HRESULT CTransNull32a::Transform(IMediaSample *pSample)
{
    return NOERROR;
}

