//------------------------------------------------------------------------------
// File: keyprovider.h
//
// Desc: DirectShow sample code - describes CKeyProvider helper class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


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
