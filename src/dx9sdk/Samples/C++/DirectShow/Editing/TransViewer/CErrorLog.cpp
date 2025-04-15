//------------------------------------------------------------------------------
// File: CErrorLog.cpp
//
// Desc: DirectShow sample code - TransViewer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "transviewer.h"
#include "cerrorlog.h"

STDMETHODIMP CErrorLog::QueryInterface(REFIID riid, void **ppv)
{
    CheckPointer(ppv,E_POINTER);
    
    *ppv = NULL;

    if (riid == IID_IUnknown)
        *ppv = (IAMErrorLog*)this;

    else if (riid == IID_IAMErrorLog)
        *ppv = (IAMErrorLog*)this;

    else if (riid == IID_IAMErrorLogEx)
        *ppv = (IAMErrorLogEx*)this;
        
    if (*ppv) 
    {
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) CErrorLog::AddRef()
{
    return InterlockedIncrement(&m_lRef);
}


STDMETHODIMP_(ULONG) CErrorLog::Release()
{
    if (InterlockedDecrement(&m_lRef) == 0)
    {
        delete this;
        return 0;
    }
    return m_lRef;
}


// LogError: Log an error to the application window.

STDMETHODIMP CErrorLog::LogError(
        LONG Severity, 
        BSTR ErrorString,
        LONG ErrorCode, 
        HRESULT hresult, 
        VARIANT *pExtraInfo)
{
    if (m_fEnabled)
    {
        PostMessage(m_hwnd, WM_ERRORLOG, (WPARAM)SysAllocString(ErrorString), 0);
    }

    return hresult;
}


