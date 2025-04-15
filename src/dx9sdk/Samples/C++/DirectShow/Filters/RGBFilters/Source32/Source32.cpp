//------------------------------------------------------------------------------
// File: Source32.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "Source32.h"

const AMOVIESETUP_FILTER sudSource32Bit =
{
    &CLSID_Source32Bit,    // Filter CLSID
    L"Source32Bit",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

//****************************************************************************
// 
//****************************************************************************
//
CUnknown * WINAPI CSource32Bit::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CSource32Bit(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//****************************************************************************
// Initialise a CSource32BitStream object so that we have a pin.
//****************************************************************************
//
CSource32Bit::CSource32Bit(LPUNKNOWN lpunk, HRESULT *phr)
    : CSource(NAME("Source32Bit"), lpunk, CLSID_Source32Bit)
{
    ASSERT(phr);
    CAutoLock cAutoLock(&m_cStateLock);

    m_paStreams = (CSourceStream **) new CSource32BitStream*[1];
    if (m_paStreams == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_paStreams[0] = new CSource32BitStream(phr, this, L"Source32Bit!");
    if (m_paStreams[0] == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }
}

CSource32Bit::~CSource32Bit()
{
}

//****************************************************************************
// 
//****************************************************************************
//
STDMETHODIMP CSource32Bit::NonDelegatingQueryInterface( REFIID riid, void ** ppv )
{
    return CSource::NonDelegatingQueryInterface(riid, ppv);
}

int CSource32Bit::GetPinCount()
{
    return 1;
}

CBasePin * CSource32Bit::GetPin(int n)
{
    return m_paStreams[0];
}

