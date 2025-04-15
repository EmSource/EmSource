//-----------------------------------------------------------------------------
// File: notifytool.h
//
// Desc: Class that implements IDirectMusicTool that will watch
//       for lyrics embedded in the dmusic content and trigger
//       game events when found.  Great for syncing the music and
//       the game state
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

class CMyApplication;

class CNotifyTool : public IDirectMusicTool
{
public:
    CNotifyTool( CMyApplication* pApp );

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

private:
    long    m_cRef;             // Reference counter
    CMyApplication* m_pApp;
};
