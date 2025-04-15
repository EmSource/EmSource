//------------------------------------------------------------------------------
// File: KeyProvider.cpp
//
// Desc: DirectShow sample code - provides a class to unkey Windows Media
//       for use with ASF, WMA, WMV media files.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <atlbase.h>
#include <streams.h>
#include <stdio.h>
#include <tchar.h>

#include <dshowasf.h>
#include "keyprovider.h"

//
// Build warning to remind developers of the dependency on the 
// Windows Media Format SDK stub library, which does not ship with the DirectX SDK.
//
#pragma message("---------------------------------------------------------------------------------------")
#pragma message("NOTE: To link and run this sample, you must install the Windows Media Format SDK 7.1.1.")
#pragma message("\n")
#pragma message("  After downloading the Format SDK, you can extract a public version of the")
#pragma message("  WMStub.LIB library, which should be copied to the Samples\\C++\\DirectShow\\Common folder.")
#pragma message("  This library is necessary for enabling Windows Media content.")
#pragma message("\n")
#pragma message("  Without this library in the Common folder, the link will fail with:")
#pragma message("      LNK1104: cannot open file '..\\..\\common\\wmstub.lib'")
#pragma message("\n")
#pragma message("  If you remove the WMStub.lib from the project's linker settings, the linker")
#pragma message("  will fail with this unresolved reference:")
#pragma message("      WMCreateCertificate")
#pragma message("---------------------------------------------------------------------------------------")


CKeyProvider::CKeyProvider() : m_cRef(0)
{
}

//////////////////////////////////////////////////////////////////////////
//
// IUnknown methods
//
//////////////////////////////////////////////////////////////////////////

ULONG CKeyProvider::AddRef()
{
    InterlockedIncrement( &m_cRef );
    return m_cRef;
}

ULONG CKeyProvider::Release()
{
    ASSERT(m_cRef > 0);

    ULONG urc = (ULONG) InterlockedDecrement( &m_cRef ); 
    if (urc == 0 ) 
        delete this; 

    return urc; 
}

//
// QueryInterface
//
// We only support IUnknown and IServiceProvider
//
HRESULT CKeyProvider::QueryInterface(REFIID riid, void ** ppv)
{
    if(riid == IID_IServiceProvider || riid == IID_IUnknown)
    {
        *ppv = (void *) static_cast<IServiceProvider *>(this);
        AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP CKeyProvider::QueryService(REFIID siid, REFIID riid, void **ppv)
{
    if(siid == __uuidof(IWMReader) && riid == IID_IUnknown)
    {
        IUnknown *punkCert;

        HRESULT hr = WMCreateCertificate(&punkCert);

        if(SUCCEEDED(hr))
            *ppv = (void *) punkCert;
        else
            _tprintf(_T("CKeyProvider::QueryService failed to create certificate!  hr=0x%x\n"), hr);
    
        return hr;
    }

    return E_NOINTERFACE;
}

