//------------------------------------------------------------------------------
// File: Source565.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "Source565.h"

const AMOVIESETUP_FILTER sudSource565Bit =
{
    &CLSID_Source565Bit,    // Filter CLSID
    L"Source565Bit",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

//****************************************************************************
// 
//****************************************************************************
//
CUnknown * WINAPI CSource565Bit::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CSource565Bit(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//****************************************************************************
// Initialise a CSource565BitStream object so that we have a pin.
//****************************************************************************
//
CSource565Bit::CSource565Bit(LPUNKNOWN lpunk, HRESULT *phr)
    : CSource(NAME("Source565Bit"), lpunk, CLSID_Source565Bit)
{
    ASSERT(phr);
    CAutoLock cAutoLock(&m_cStateLock);

    m_paStreams = (CSourceStream **) new CSource565BitStream*[1];
    if (m_paStreams == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_paStreams[0] = new CSource565BitStream(phr, this, L"Source565Bit!");
    if (m_paStreams[0] == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }
}

CSource565Bit::~CSource565Bit()
{
}

//****************************************************************************
// 
//****************************************************************************
//
STDMETHODIMP CSource565Bit::NonDelegatingQueryInterface( REFIID riid, void ** ppv )
{
    return CSource::NonDelegatingQueryInterface(riid, ppv);
}

int CSource565Bit::GetPinCount()
{
    return 1;
}

CBasePin * CSource565Bit::GetPin(int n)
{
    return m_paStreams[0];
}

