//-----------------------------------------------------------------------------
// File: notifytool.cpp
//
// Copyright (C) 1995-2001 Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: CNotifyTool::CNotifyTool
// Desc: 
//-----------------------------------------------------------------------------
CNotifyTool::CNotifyTool( CMyApplication* pApp )
{
    m_pApp = pApp;
    m_cRef = 1; 
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::QueryInterface()
// Desc: 
//-----------------------------------------------------------------------------
STDMETHODIMP CNotifyTool::QueryInterface(const IID &iid, void **ppv)
{
    if (iid == IID_IUnknown || iid == IID_IDirectMusicTool)
    {
        *ppv = static_cast<IDirectMusicTool*>(this);
    } 
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    
    reinterpret_cast<IUnknown*>(this)->AddRef();
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::AddRef()
// Desc: 
//-----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CNotifyTool::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::Release()
// Desc: 
//-----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CNotifyTool::Release()
{
    if( 0 == InterlockedDecrement(&m_cRef) )
    {
        delete this;
        return 0;
    }

    return m_cRef;
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::Init()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CNotifyTool::Init( IDirectMusicGraph* pGraph )
{
    // This tool has no need to do any type of initialization.
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::GetMsgDeliveryType()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CNotifyTool::GetMsgDeliveryType( DWORD* pdwDeliveryType )
{
    // This tool wants messages at the time stamp, not before, since it
    // will synchronize graphics to the lyrics.
    
    *pdwDeliveryType = DMUS_PMSGF_TOOL_ATTIME;
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::GetMediaTypeArraySize()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CNotifyTool::GetMediaTypeArraySize( DWORD* pdwNumElements )
{
    // This tool only wants lyric messages. Since it receives them 
    // at DMUS_PMSGF_TOOL_ATTIME, it's important that it not process other message
    // types because it would cause a timing delay for music performance messages,
    // such as notes, that need to be sent at DMUS_PMSGF_TOOL_QUEUE time.
    
    *pdwNumElements = 1;
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::GetMediaTypes()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CNotifyTool::GetMediaTypes( DWORD** padwMediaTypes, 
                                                    DWORD dwNumElements )
{
    // Fill in the array padwMediaTypes with the type of
    // messages this tool wants to process. In this case,
    // dwNumElements will be 1, since that is what this
    // tool returns from GetMediaTypeArraySize().
    
    if( dwNumElements == 1 )
    {
        (*padwMediaTypes)[0] = DMUS_PMSGT_LYRIC;
        return S_OK;
    }
    else
    {
        // This should never happen
        return E_FAIL;
    }
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::ProcessPMsg()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CNotifyTool::ProcessPMsg( IDirectMusicPerformance* pPerf, 
                                                    DMUS_PMSG* pPMsg )
{
    // Since this tool is capturing only the lyric messages and promptly discarding them,
    // there is no need to call StampPMsg on the graph to set up the next tool to process
    // after this one.

    // Start by ensuring that this is indeed a lyric message. This should never fail, but
    // just to be safe...

    if (pPMsg->dwType == DMUS_PMSGT_LYRIC)
    {
        // Decode the lyric and use to set the app state.
        DMUS_LYRIC_PMSG *pLyric = (DMUS_LYRIC_PMSG *) pPMsg;
        if (!(_wcsicmp(pLyric->wszString,L"AdvanceLevel")))
        {
            // This string is sent when we transition to a new level screen.
            // It indicates that the wait for the music to end is now over.
            // So, go and directly reset the app state.
            m_pApp->SetAppState( APPSTATE_TRIGGERLEVELSCREEN );
        }
        else if (!(_wcsicmp(pLyric->wszString,L"StartLevel")))
        {
            // This indicates the change level music has
            // finished playing and we can now move on to the new level screen.
            m_pApp->SetAppState( APPSTATE_BEGINACTIVESCREEN );
        }
    }
 
    // Return DMUS_S_FREE since there's no need to do anything more with this lyric.
    return DMUS_S_FREE;
}




//-----------------------------------------------------------------------------
// Name: CNotifyTool::Flush()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CNotifyTool::Flush( IDirectMusicPerformance* pPerf, 
                                            DMUS_PMSG* pDMUS_PMSG,
                                            REFERENCE_TIME rt)
{
    // This tool does not need to flush.
    return E_NOTIMPL;
}
