//------------------------------------------------------------------------------
// File: TransNull555.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "TransNull555.h"

const AMOVIESETUP_FILTER sudTransNull555 =
{
    &CLSID_TransNull555,    // Filter CLSID
    L"TransNull555",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

CUnknown * WINAPI CTransNull555::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CTransNull555(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

}

CTransNull555::CTransNull555(LPUNKNOWN punk,HRESULT *phr) 
    : CTransInPlaceFilter(TEXT("TransNull555"), punk, CLSID_TransNull555, phr)
{
}

HRESULT CTransNull555::CheckInputType(const CMediaType *mtIn)
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

    if( *mtIn->Subtype( ) != MEDIASUBTYPE_RGB555 )
    {
        return E_INVALIDARG;
    }

    return NOERROR;
}

HRESULT CTransNull555::Transform(IMediaSample *pSample)
{
    return NOERROR;
}

