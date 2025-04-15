//------------------------------------------------------------------------------
// File: AlphaSource.cpp
//
// Desc: DirectShow sample code - implementation of RGBFilters sample filters
//
// Copyright (c) 2000-2002  Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "..\iRGBFilters.h"
#include "AlphaSource.h"

const AMOVIESETUP_FILTER sudAlphaSource =
{
    &CLSID_AlphaSource,    // Filter CLSID
    L"SourceARGB",       // String name
    MERIT_DO_NOT_USE,       // Filter merit
    0,                      // Number pins
    NULL               // Pin details
};

//****************************************************************************
// 
//****************************************************************************
//
CUnknown * WINAPI CAlphaSource::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    
    CUnknown *punk = new CAlphaSource(lpunk, phr);
    if (punk == NULL) 
    {
        *phr = E_OUTOFMEMORY;
    }
    return punk;

} // CreateInstance


//****************************************************************************
// Initialise a CAlphaSourceStream object so that we have a pin.
//****************************************************************************
//
CAlphaSource::CAlphaSource(LPUNKNOWN lpunk, HRESULT *phr)
    : CSource(NAME("SourceARGB"), lpunk, CLSID_AlphaSource)
{
    ASSERT(phr);
    CAutoLock cAutoLock(&m_cStateLock);

    m_paStreams = (CSourceStream **) new CAlphaSourceStream*[1];
    if (m_paStreams == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }

    m_paStreams[0] = new CAlphaSourceStream(phr, this, L"SourceARGB!");
    if (m_paStreams[0] == NULL) 
    {
        *phr = E_OUTOFMEMORY;
        return;
    }
}

CAlphaSource::~CAlphaSource()
{
}

//****************************************************************************
// 
//****************************************************************************
//
STDMETHODIMP CAlphaSource::NonDelegatingQueryInterface( REFIID riid, void ** ppv )
{
    return CSource::NonDelegatingQueryInterface(riid, ppv);
}

int CAlphaSource::GetPinCount()
{
    return 1;
}

CBasePin * CAlphaSource::GetPin(int n)
{
    return m_paStreams[0];
}

