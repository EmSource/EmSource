//------------------------------------------------------------------------------
// File: keyprovider.h
//
// Desc: DirectShow sample code - describes CKeyProvider helper class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

//
// Windows Media 9 Series (code named 'Corona') no longer requires 
// a stub library.  If using WMF9, we don't need to provide a CKeyProvider
// implementation, and we don't need to link with the WMStub.lib library.
//
#ifndef TARGET_WMF9

class CKeyProvider : public IServiceProvider
{
    public:
        //
        // IUnknown interface
        //
        STDMETHODIMP QueryInterface(REFIID riid, void ** ppv);
        STDMETHODIMP_(ULONG) AddRef();
        STDMETHODIMP_(ULONG) Release();

        CKeyProvider();

        // IServiceProvider
        STDMETHODIMP QueryService(REFIID siid, REFIID riid, void **ppv);

    private:
        volatile LONG m_cRef;
};

#endif
