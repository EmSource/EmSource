//------------------------------------------------------------------------------
// File: RenderEngine.h
//
// Desc: DirectShow sample code - Declaration of the CMultiVMR9RenderEngine
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once
#include "resource.h"       // main symbols

#include "MultiVMR9.h"


// CMultiVMR9RenderEngine

class CMultiVMR9RenderEngine : 
    public CUnknown,
    public IMultiVMR9RenderEngine
{
public:
    CMultiVMR9RenderEngine(LPUNKNOWN pUnk, HRESULT *phr);
    virtual ~CMultiVMR9RenderEngine();

    // IUnknown implementation
    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);
    static CUnknown *CreateInstance(LPUNKNOWN, HRESULT *);

    // IMultiVMR9RenderEngine implementation
    STDMETHOD(Initialize)(
        HWND hWnd, 
        DWORD dwFlags,
        IMultiVMR9MixerControl* pMixerControl,
        IMultiVMR9UILayer* pUILayer
        );

    STDMETHOD(Terminate)(
        );

    STDMETHOD(Render)(
        void
        );

    STDMETHOD(GetUILayer)(
        IMultiVMR9UILayer** ppUILayer
        );

    STDMETHOD(SetFrameRate)(
        int nFramesPerSecBy100
        );

    STDMETHOD(GetFrameRate)(
        int* pnFramesPerSecBy100
        );

    STDMETHOD(GetFrameRateAvg)(
        int* pnFramesPerSecBy100
        );

    STDMETHOD(GetMixingPrefs)(
        DWORD* pdwPrefs
        );

    STDMETHOD(SetWizardOwner)(
        IMultiVMR9Wizard* pWizard
        );

    STDMETHOD(GetWizardOwner)(
        IMultiVMR9Wizard** ppWizard
        );

    STDMETHOD(GetMixerControl)(
        IMultiVMR9MixerControl** ppMixerControl
        );

    STDMETHOD(Get3DDevice)(
        IDirect3DDevice9 ** ppDevice
        );

    STDMETHOD(GetVideoWindow)(
        HWND *phwnd
        );

//private methods
private:
    void Clean_();

// private data
private:
    CCritSec                m_ObjectLock;   // this object has to be thread-safe
    BOOL                    m_bInitialized; // true if Initialize() was called
    HWND                    m_hwnd;         // handle to the video window
    IDirect3DDevice9*       m_pDevice;      // Direct3DDevice
    IMultiVMR9UILayer*      m_pUILayer;     // user interface layer
    IMultiVMR9MixerControl* m_pMixerControl;// MultiVMR9MixerControl
    IMultiVMR9Wizard*       m_pOwner;       // IMultiVMR9Wizard that controls this render engine
    IDirect3DSurface9*      m_pRenderTarget;
    DWORD                   m_dwCfgFlags;   // configuration flags
    DWORD                   m_Timer;        // Timer
    DWORD                   m_dwStart;      // time when rendering started
    DWORD                   m_dwLastRender; // last time we rendered the scene
    DWORD                   m_getFPS;       // actual FPS, in (frames per sec)x100
    DWORD                   m_interframe;   // ideal time, in ms, between frames
    DWORD                   m_interframeAvg;// average time, in ms, between frames
    DWORD                   m_interframeInstant;// last time, in ms, between frames
public:
    DWORD                   m_setFPS;       // requested FPS, in (frames per sec)x100
    DWORD                   m_dwFramesDrawn;// number of frames we drew
};

// class factory
extern long g_CountRenderEngine;

class CCFMultiVMR9RenderEngine : public IClassFactory
{
public:
    // Constructor
    CCFMultiVMR9RenderEngine() : m_RefCount(1) {} 

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
        CMultiVMR9RenderEngine * pRenderEngine = new CMultiVMR9RenderEngine(punkOuter, &hr);
        if (NULL == pRenderEngine)
            return E_OUTOFMEMORY;

        // now QI for the requested interface.  If this fails, delete the object
        hr = pRenderEngine->QueryInterface(riid, ppvObject);
        if (FAILED(hr))
            delete pRenderEngine;

        return hr;
    }

    STDMETHOD(LockServer)(BOOL fLock)
    {
        if (fLock)
            InterlockedIncrement(&g_CountRenderEngine);
        else
            InterlockedDecrement(&g_CountRenderEngine);
        return S_OK;
    }

private:
    LONG m_RefCount;
};


