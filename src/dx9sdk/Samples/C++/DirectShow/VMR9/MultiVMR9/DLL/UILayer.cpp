//------------------------------------------------------------------------------
// File: UILayer.cpp
//
// Desc: DirectShow sample code - Implementation of CMultiVMR9UILayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "UILayer.h"


// CMultiVMR9UILayer

/******************************Public*Routine******************************\
* CMultiVMR9UILayer
*
* constructor
\**************************************************************************/
CMultiVMR9UILayer::CMultiVMR9UILayer(LPUNKNOWN pUnk, HRESULT *phr)
    : CUnknown(NAME("MultiVMR9 UI Layer"), pUnk)
{
}

/******************************Public*Routine******************************\
* ~CMultiVMR9UILayer
*
* destructor
\**************************************************************************/
CMultiVMR9UILayer::~CMultiVMR9UILayer()
{
    ;
}

///////////////////////// IUnknown /////////////////////////////////////////

/******************************Public*Routine******************************\
* CreateInstance
\**************************************************************************/
CUnknown* CMultiVMR9UILayer::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
    return new CMultiVMR9UILayer(pUnk, phr);
}

/******************************Public*Routine******************************\
* NonDelegatingQueryInterface
\**************************************************************************/
STDMETHODIMP
CMultiVMR9UILayer::NonDelegatingQueryInterface(
    REFIID riid,
    void ** ppv)
{
    HRESULT hr = E_NOINTERFACE;
    *ppv = NULL;

    if (riid == IID_IMultiVMR9UILayer) 
    {
        hr = GetInterface((IMultiVMR9UILayer *)this, ppv);
    }
    else 
    {
        hr = CUnknown::NonDelegatingQueryInterface(riid,ppv);
    }
    return hr;
}


///////////////////////// IMultiVMR9Wizard /////////////////////////////////


STDMETHODIMP CMultiVMR9UILayer::Initialize(IDirect3DDevice9 *pDevice)
{
    // TODO: Add your implementation code here

    return S_OK;
}

STDMETHODIMP CMultiVMR9UILayer::ProcessMessage(UINT msg, UINT wParam, LONG lParam)
{
    // TODO: Add your implementation code here

    return S_OK;
}

STDMETHODIMP CMultiVMR9UILayer::Render(IDirect3DDevice9 *pDevice)
{
    // TODO: Add your implementation code here

    return S_OK;
}

STDMETHODIMP CMultiVMR9UILayer::SetRenderEngineOwner(IMultiVMR9RenderEngine* pRenderEngine)
{
    // TODO: Add your implementation code here

    return S_OK;
}

STDMETHODIMP CMultiVMR9UILayer::GetRenderEngineOwner(IMultiVMR9RenderEngine** ppRenderEngine)
{
    // TODO: Add your implementation code here

    return S_OK;
}


