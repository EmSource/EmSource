//------------------------------------------------------------------------------
// File: Source24.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "Source24.h"

const AMOVIESETUP_FILTER sudSource24Bit =
{
    &CLSID_Source24Bit,    // Filter CLSID
    L"Source24Bit",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

//****************************************************************************
// 
//****************************************************************************
//
CUnknown * WINAPI CSource24Bit::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CSource24Bit(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//****************************************************************************
// Initialise a CSource24BitStream object so that we have a pin.
//****************************************************************************
//
CSource24Bit::CSource24Bit(LPUNKNOWN lpunk, HRESULT *phr)
    : CSource(NAME("Source24Bit"), lpunk, CLSID_Source24Bit)
{
    ASSERT(phr);
    CAutoLock cAutoLock(&m_cStateLock);

    m_paStreams = (CSourceStream **) new CSource24BitStream*[1];
    if (m_paStreams == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_paStreams[0] = new CSource24BitStream(phr, this, L"Source24Bit!");
    if (m_paStreams[0] == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }
}

CSource24Bit::~CSource24Bit()
{
}

//****************************************************************************
// 
//****************************************************************************
//
STDMETHODIMP CSource24Bit::NonDelegatingQueryInterface( REFIID riid, void ** ppv )
{
    return CSource::NonDelegatingQueryInterface(riid, ppv);
}

int CSource24Bit::GetPinCount()
{
    return 1;
}

CBasePin * CSource24Bit::GetPin(int n)
{
    return m_paStreams[0];
}

