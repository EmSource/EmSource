//------------------------------------------------------------------------------
// File: RateSource.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "ratesource.h"

const AMOVIESETUP_FILTER sudRateSource =
{
    &CLSID_RateSource,    // Filter CLSID
    L"RateSource",        // String name
    MERIT_DO_NOT_USE,     // Filter merit
    0,                    // Number pins
    NULL                  // Pin details
};

CUnknown * WINAPI CRateSource::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CRateSource(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//****************************************************************************
// Initialise a CRateSourceStream object so that we have a pin.
//****************************************************************************
//
CRateSource::CRateSource(LPUNKNOWN lpunk, HRESULT *phr)
    : CSource(NAME("RateSource"), lpunk, CLSID_RateSource)
{
    ASSERT(phr);
    CAutoLock cAutoLock(&m_cStateLock);

    m_paStreams = (CSourceStream **) new CRateSourceStream*[1];
    if (m_paStreams == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_paStreams[0] = new CRateSourceStream(phr, this, L"RateSource!");
    if (m_paStreams[0] == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }
}

CRateSource::~CRateSource()
{
}

//****************************************************************************
// 
//****************************************************************************
//
STDMETHODIMP CRateSource::NonDelegatingQueryInterface( REFIID riid, void ** ppv )
{
    return CSource::NonDelegatingQueryInterface(riid, ppv);
}

int CRateSource::GetPinCount()
{
    return 1;
}

CBasePin * CRateSource::GetPin(int n)
{
    return m_paStreams[0];
}

