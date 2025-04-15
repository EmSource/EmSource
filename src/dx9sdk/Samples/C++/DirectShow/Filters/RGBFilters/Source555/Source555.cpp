//------------------------------------------------------------------------------
// File: Source555.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "Source555.h"

const AMOVIESETUP_FILTER sudSource555Bit =
{
    &CLSID_Source555Bit,    // Filter CLSID
    L"Source555Bit",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

//****************************************************************************
// 
//****************************************************************************
//
CUnknown * WINAPI CSource555Bit::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CSource555Bit(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//****************************************************************************
// Initialise a CSource555BitStream object so that we have a pin.
//****************************************************************************
//
CSource555Bit::CSource555Bit(LPUNKNOWN lpunk, HRESULT *phr)
    : CSource(NAME("Source555Bit"), lpunk, CLSID_Source555Bit)
{
    ASSERT(phr);
    CAutoLock cAutoLock(&m_cStateLock);

    m_paStreams = (CSourceStream **) new CSource555BitStream*[1];
    if (m_paStreams == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_paStreams[0] = new CSource555BitStream(phr, this, L"Source555Bit!");
    if (m_paStreams[0] == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }
}

CSource555Bit::~CSource555Bit()
{
}

//****************************************************************************
// 
//****************************************************************************
//
STDMETHODIMP CSource555Bit::NonDelegatingQueryInterface( REFIID riid, void ** ppv )
{
    return CSource::NonDelegatingQueryInterface(riid, ppv);
}

int CSource555Bit::GetPinCount()
{
    return 1;
}

CBasePin * CSource555Bit::GetPin(int n)
{
    return m_paStreams[0];
}

