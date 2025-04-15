//-----------------------------------------------------------------------------
// File: EchoTool.h
//
// Desc: Implements an object based on IDirectMusicTool
//       that provides echoing effects.
//
// Copyright (c) 1998-2000 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef _MEASTOOL_H
#define _MEASTOOL_H

#include <dmusici.h>

typedef enum { eOff, eMeasure, eBeat } EBeatType;

class CMeasureTool : public IDirectMusicTool
{
public:
	CMeasureTool(HWND hwndParent);
    ~CMeasureTool();

    HWND        m_hwndParent;

public:
// IUnknown
    virtual STDMETHODIMP QueryInterface(const IID &iid, void **ppv);
    virtual STDMETHODIMP_(ULONG) AddRef();
    virtual STDMETHODIMP_(ULONG) Release();

// IDirectMusicTool
	HRESULT STDMETHODCALLTYPE Init( IDirectMusicGraph* pGraph );
	HRESULT STDMETHODCALLTYPE GetMsgDeliveryType( DWORD* pdwDeliveryType );
	HRESULT STDMETHODCALLTYPE GetMediaTypeArraySize( DWORD* pdwNumElements );
	HRESULT STDMETHODCALLTYPE GetMediaTypes( DWORD** padwMediaTypes, DWORD dwNumElements) ;
	HRESULT STDMETHODCALLTYPE ProcessPMsg( IDirectMusicPerformance* pPerf, DMUS_PMSG* pDMUS_PMSG );
	HRESULT STDMETHODCALLTYPE Flush( IDirectMusicPerformance* pPerf, DMUS_PMSG* pDMUS_PMSG, REFERENCE_TIME rt );
    void    Blink(EBeatType);

private:
	long    m_cRef;			    // Reference counter
};

void CALLBACK Unblink(HWND, UINT, UINT_PTR, DWORD);

#endif // _MEASTOOL_H
