//------------------------------------------------------------------------------
// File: TransNull32.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "TransNull32.h"

const AMOVIESETUP_FILTER sudTransNull32 =
{
    &CLSID_TransNull32,    // Filter CLSID
    L"TransNull32",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

CUnknown * WINAPI CTransNull32::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CTransNull32(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

}

CTransNull32::CTransNull32(LPUNKNOWN punk,HRESULT *phr) 
    : CTransInPlaceFilter(TEXT("TransNull32"), punk, CLSID_TransNull32, phr)
{
}

HRESULT CTransNull32::CheckInputType(const CMediaType *mtIn)
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

    if( *mtIn->Subtype( ) != MEDIASUBTYPE_RGB32 )
    {
        return E_INVALIDARG;
    }

    return NOERROR;
}

HRESULT CTransNull32::Transform(IMediaSample *pSample)
{
    return NOERROR;
}

