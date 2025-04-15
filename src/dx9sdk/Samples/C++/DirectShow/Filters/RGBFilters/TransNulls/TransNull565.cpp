//------------------------------------------------------------------------------
// File: TransNull565.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "TransNull565.h"

const AMOVIESETUP_FILTER sudTransNull565 =
{
    &CLSID_TransNull565,    // Filter CLSID
    L"TransNull565",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

CUnknown * WINAPI CTransNull565::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CTransNull565(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

}

CTransNull565::CTransNull565(LPUNKNOWN punk,HRESULT *phr) 
    : CTransInPlaceFilter(TEXT("TransNull565"), punk, CLSID_TransNull565, phr)
{
}

HRESULT CTransNull565::CheckInputType(const CMediaType *mtIn)
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

    if( *mtIn->Subtype( ) != MEDIASUBTYPE_RGB565 )
    {
        return E_INVALIDARG;
    }

    return NOERROR;
}

HRESULT CTransNull565::Transform(IMediaSample *pSample)
{
    return NOERROR;
}

