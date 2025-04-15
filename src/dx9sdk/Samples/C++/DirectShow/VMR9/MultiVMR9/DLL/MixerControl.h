//------------------------------------------------------------------------------
// File: MixerControl.h
//
// Desc: DirectShow sample code - Declaration of the CMultiVMR9MixerControl
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once
#include "resource.h"       // main symbols
#include "MultiVMR9.h"

#pragma warning(push, 2)
#include <list>
using namespace std;
#pragma warning(pop)


static const MultiVMR9Mixer_DefaultFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

// CMultiVMR9MixerControl

class CMultiVMR9MixerControl : 
    public CUnknown,
    public IMultiVMR9MixerControl
{

public:
    CMultiVMR9MixerControl(LPUNKNOWN pUnk, HRESULT *phr);
    virtual ~CMultiVMR9MixerControl();

    // IUnknown implementation
    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);
    static CUnknown *CreateInstance(LPUNKNOWN, HRESULT *);

    // IMultiVMR9MixerControl implementation
    STDMETHOD(SetRenderEngineOwner)(
        IMultiVMR9RenderEngine* pRenderEngine
        );

    STDMETHOD(GetRenderEngineOwner)(
        IMultiVMR9RenderEngine** ppRenderEngine
        );

    STDMETHOD(Initialize)(
        IDirect3DDevice9 *pDevice
        );

    STDMETHOD(Compose)(
        void* lpParam
        );

    STDMETHOD(Render)(
        IDirect3DDevice9 *pDevice,
        void* lpParam
        );

    STDMETHOD(GetOutputRect)(
        DWORD_PTR dwID,
        NORMALIZEDRECT* lpNormRect
        );

    STDMETHOD(GetIdealOutputRect)(
        DWORD_PTR dwID,
        DWORD dwWidth,
        DWORD dwHeight,
        NORMALIZEDRECT* lpNormRect
        );

    STDMETHOD(SetOutputRect)(
        DWORD_PTR dwID,
        NORMALIZEDRECT* lpNormRect
        );

    STDMETHOD(GetZOrder)(
        DWORD_PTR dwID, 
        DWORD *pdwZ
        );

    STDMETHOD(SetZOrder)(
        DWORD_PTR dwID, 
        DWORD pdwZ
        );

    STDMETHOD(GetAlpha)(
        DWORD_PTR dwID, 
        float* pAlpha
        );

    STDMETHOD(SetAlpha)(
        DWORD_PTR dwID, 
        float Alpha
        );

    STDMETHOD(GetBackgroundColor)(
        COLORREF* pColor
        );

    STDMETHOD(SetBackgroundColor)(
        COLORREF Color
        );

    STDMETHOD(AddVideoSource)(
        DWORD_PTR dwID,
        LONG lImageWidth,
        LONG lImageHeight,
        LONG lTextureWidth,
        LONG lTextureHeight
        );

    STDMETHOD(DeleteVideoSource)(
        DWORD_PTR dwID
        );

    // private classes
private:

    // custom vertex, specific for default implementation of 
    // CLSID_MultiVMR9MixerControl
    typedef struct _MultiVMR9_Vertex
    {
        D3DVECTOR position;
        D3DCOLOR color;
        FLOAT tu;
        FLOAT tv;

    } MultiVMR9_Vertex;

    // custom primitive for a video source, 
    // specific for default implementation of CLSID_MultiVMR9MixerControl
    class CMultiVMR9_Frame
    {
    public:
        CMultiVMR9_Frame();
        ~CMultiVMR9_Frame();


        HRESULT Initialize( 
                    DWORD_PTR dwUserID,
                    LONG lWidth, 
                    LONG lHeight, 
                    LONG lTextureWidth,
                    LONG lTextureHeight,
                    LONG lRenderTargetWidth,
                    LONG lRenderTargetHeight,
                    float fAlpha);

        HRESULT UpdateDestination(NORMALIZEDRECT& newnrect);

        // data
        float                   m_WidthAR;
        float                   m_HeightAR;
        LONG                    m_lImageWidth;
        LONG                    m_lImageHeight;
        float                   m_ar;

        DWORD_PTR               m_dwID;
        MultiVMR9_Vertex        m_coord[4];
        float                   m_alpha;
        NORMALIZEDRECT          m_nrDst;
        DWORD                   m_dwZOrder;

    };


    // private methods
private:
    void Clean_();

    // private data
private:
    BOOL                    m_bInitialized;
    CCritSec                m_ObjectLock;       // this object has to be thread-safe
    list<CMultiVMR9_Frame*> m_listFrames;
    IMultiVMR9RenderEngine* m_pOwner;
    COLORREF                m_BackgroundColor;
    const DWORD             m_FVF;
};


// class factory
extern long g_CountMixerControl;

class CCFMultiVMR9MixerControl : public IClassFactory
{
public:
    // Constructor
    CCFMultiVMR9MixerControl() : m_RefCount(1) {} 

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
        CMultiVMR9MixerControl * pMixerControl = new CMultiVMR9MixerControl(punkOuter, &hr);
        if (NULL == pMixerControl)
            return E_OUTOFMEMORY;

        // now QI for the requested interface.  If this fails, delete the object
        hr = pMixerControl->QueryInterface(riid, ppvObject);
        if (FAILED(hr))
            delete pMixerControl;

        return hr;
    }

    STDMETHOD(LockServer)(BOOL fLock)
    {
        if (fLock)
            InterlockedIncrement(&g_CountMixerControl);
        else
            InterlockedDecrement(&g_CountMixerControl);
        return S_OK;
    }

private:
    LONG m_RefCount;
};
