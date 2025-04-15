//------------------------------------------------------------------------------
// File: TransNull24.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "TransNull24.h"

const AMOVIESETUP_FILTER sudTransNull24 =
{
    &CLSID_TransNull24,    // Filter CLSID
    L"TransNull24",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

CUnknown * WINAPI CTransNull24::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CTransNull24(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

}

CTransNull24::CTransNull24(LPUNKNOWN punk,HRESULT *phr) 
    : CTransInPlaceFilter(TEXT("TransNull24"), punk, CLSID_TransNull24, phr)
{
}

HRESULT CTransNull24::CheckInputType(const CMediaType *mtIn)
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

    if( *mtIn->Subtype( ) != MEDIASUBTYPE_RGB24 )
    {
        return E_INVALIDARG;
    }

    return NOERROR;
}

HRESULT CTransNull24::Transform(IMediaSample *pSample)
{
    return NOERROR;
}

