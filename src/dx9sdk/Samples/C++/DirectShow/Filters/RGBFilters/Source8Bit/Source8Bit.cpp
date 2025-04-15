//------------------------------------------------------------------------------
// File: Source8Bit.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "Source8Bit.h"

const AMOVIESETUP_FILTER sudSource8Bit =
{
    &CLSID_Source8Bit,    // Filter CLSID
    L"Source8Bit",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

//****************************************************************************
// 
//****************************************************************************
//
CUnknown * WINAPI CSource8Bit::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CSource8Bit(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//****************************************************************************
// Initialise a CSource8BitStream object so that we have a pin.
//****************************************************************************
//
CSource8Bit::CSource8Bit(LPUNKNOWN lpunk, HRESULT *phr)
    : CSource(NAME("Source8Bit"), lpunk, CLSID_Source8Bit)
{
    ASSERT(phr);
    CAutoLock cAutoLock(&m_cStateLock);

    m_paStreams = (CSourceStream **) new CSource8BitStream*[1];
    if (m_paStreams == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_paStreams[0] = new CSource8BitStream(phr, this, L"Source8Bit!");
    if (m_paStreams[0] == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }
}

CSource8Bit::~CSource8Bit()
{
}

//****************************************************************************
// 
//****************************************************************************
//
STDMETHODIMP CSource8Bit::NonDelegatingQueryInterface( REFIID riid, void ** ppv )
{
    return CSource::NonDelegatingQueryInterface(riid, ppv);
}

int CSource8Bit::GetPinCount()
{
    return 1;
}

CBasePin * CSource8Bit::GetPin(int n)
{
    return m_paStreams[0];
}

