//------------------------------------------------------------------------------
// File: UILayer.h
//
// Desc: DirectShow sample code - Declaration of the CMultiVMR9UILayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once
#include "resource.h"       // main symbols

#include "MultiVMR9.h"


// CMultiVMR9UILayer

class CMultiVMR9UILayer : 
    public CUnknown,
    public IMultiVMR9UILayer
{
public:
    CMultiVMR9UILayer(LPUNKNOWN pUnk, HRESULT *phr);
    virtual ~CMultiVMR9UILayer();

    // IUnknown implementation
    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);
    static CUnknown *CreateInstance(LPUNKNOWN, HRESULT *);

    // IMultiVMR9UILayer implementation
    STDMETHOD(Initialize)(IDirect3DDevice9 *pDevice);
    STDMETHOD(ProcessMessage)(UINT msg, UINT wParam, LONG lParam);
    STDMETHOD(Render)(IDirect3DDevice9 *pDevice);
    STDMETHOD(SetRenderEngineOwner)(IMultiVMR9RenderEngine* pRenderEngine);
    STDMETHOD(GetRenderEngineOwner)(IMultiVMR9RenderEngine** ppRenderEngine);
};

// class factory
extern long g_CountUILayer;

class CCFMultiVMR9UILayer : public IClassFactory
{
public:
    // Constructor
    CCFMultiVMR9UILayer() : m_RefCount(1) {} 

    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, void ** ppv)
    {
        if (IID_IUnknown == riid)
            *ppv = static_cast<IUnknown *>(this);
        else if (IID_IClassFactory == riid)
            *ppv = static_cast<IClassFactory *>(this);
        else
        {
            *ppv = NULL;
            return E_NOINTERFACE;
        }
        static_cast<IUnknown *>(*ppv)->AddRef();
        return S_OK;
    }

    STDMETHOD_(ULONG, AddRef())
    {
        return InterlockedIncrement(&m_RefCount);
    }

    STDMETHOD_(ULONG, Release())
    {
        LONG ref = InterlockedDecrement(&m_RefCount);
        if (0 == ref)
        {
            delete this;
        }
        return ref;
    }

    // IClassFactory methods
    STDMETHOD(CreateInstance)(IUnknown * punkOuter, REFIID riid, void ** ppvObject)
    {
        HRESULT hr = S_OK;
        if (NULL == ppvObject)
            return E_POINTER;

        *ppvObject = NULL; // initialize the pointer
        // we don't support aggregation
        if (NULL != punkOuter)
            return CLASS_E_NOAGGREGATION;

        // create a new Wizard object
        CMultiVMR9UILayer * pUILayer = new CMultiVMR9UILayer(punkOuter, &hr);
        if (NULL == pUILayer)
            return E_OUTOFMEMORY;

        // now QI for the requested interface.  If this fails, delete the object
        hr = pUILayer->QueryInterface(riid, ppvObject);
        if (FAILED(hr))
            delete pUILayer;

        return hr;
    }

    STDMETHOD(LockServer)(BOOL fLock)
    {
        if (fLock)
            InterlockedIncrement(&g_CountUILayer);
        else
            InterlockedDecrement(&g_CountUILayer);
        return S_OK;
    }

private:
    LONG m_RefCount;
};


