//-----------------------------------------------------------------------------
// File: meastool.cpp
//
// Desc: Implements an object based on IDirectMusicTool
//       that updates a UI square to blink red on the measure, and 
//       blink green on the beat. 
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <dmusici.h>
#include "MeasTool.h"
#include "resource.h"

CMeasureTool* g_pMusicTool = NULL;

//-----------------------------------------------------------------------------
// Name: CMeasureTool::CMeasureTool()
// Desc: 
//-----------------------------------------------------------------------------
CMeasureTool::CMeasureTool(HWND hwndParent)
{
    m_cRef = 1;             // Set to 1 so one call to Release() will free this
    m_hwndParent = hwndParent;
    g_pMusicTool = this;
}




//-----------------------------------------------------------------------------
// Name: CMeasureTool::~CMeasureTool()
// Desc: 
//-----------------------------------------------------------------------------
CMeasureTool::~CMeasureTool()
{
}




//-----------------------------------------------------------------------------
// Name: CMeasureTool::QueryInterface()
// Desc: 
//-----------------------------------------------------------------------------
STDMETHODIMP CMeasureTool::QueryInterface(const IID &iid, void **ppv)
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
// Name: CMeasureTool::AddRef()
// Desc: 
//-----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CMeasureTool::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}




//-----------------------------------------------------------------------------
// Name: CMeasureTool::Release()
// Desc: 
//-----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CMeasureTool::Release()
{
    if( 0 == InterlockedDecrement(&m_cRef) )
    {
        delete this;
        return 0;
    }

    return m_cRef;
}




//-----------------------------------------------------------------------------
// Name: CMeasureTool::Init()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMeasureTool::Init( IDirectMusicGraph* pGraph )
{
    // This tool has no need to do any type of initialization.
    return E_NOTIMPL;
}




//-----------------------------------------------------------------------------
// Name: CMeasureTool::GetMsgDeliveryType()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMeasureTool::GetMsgDeliveryType( DWORD* pdwDeliveryType )
{
    // This tool wants messages AT the TIME that they are to be processed.  This 
    // is so that the "beat indicator" blinks ON THE BEAT rather than before.
    *pdwDeliveryType = DMUS_PMSGF_TOOL_ATTIME;
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CMeasureTool::GetMediaTypeArraySize()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMeasureTool::GetMediaTypeArraySize( DWORD* pdwNumElements )
{
    // This tool only wants note messages, patch messages, sysex, and MIDI messages, so set
    // *pdwNumElements to 4.
    
    *pdwNumElements = 1;
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CMeasureTool::GetMediaTypes()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMeasureTool::GetMediaTypes( DWORD** padwMediaTypes, 
                                                    DWORD dwNumElements )
{
    // Fill in the array padwMediaTypes with the type of
    // messages this tool wants to process. In this case,
    // dwNumElements will be 3, since that is what this
    // tool returns from GetMediaTypeArraySize().
    
    if( dwNumElements == 1 )
    {
        // Set the elements in the array to DMUS_PMSGT_NOTE,
        // DMUS_PMSGT_MIDI, and DMUS_PMSGT_PATCH
        (*padwMediaTypes)[0] = DMUS_PMSGT_NOTIFICATION;
        return S_OK;
    }
    else
    {
        // This should never happen
        return E_FAIL;
    }
}


// ------------------------------------------------------------------------------
#define DUMPGUID(g)     if (pNotiMsg->guidNotificationType == (g))  OutputDebugString(#g "\n")

//-----------------------------------------------------------------------------
// Name: CMeasureTool::ProcessPMsg()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE 
CMeasureTool::ProcessPMsg
( 
    IDirectMusicPerformance* pPerf, 
    DMUS_PMSG*               pPMsg 
)
{
    DMUS_NOTIFICATION_PMSG*  pNotiMsg = (DMUS_NOTIFICATION_PMSG*)pPMsg;

    // Returning S_FREE frees the message. If StampPMsg()
    // fails, there is no destination for this message so
    // free it.
    if(( NULL == pPMsg->pGraph ) ||
        FAILED(pPMsg->pGraph->StampPMsg(pPMsg)))
    {
        return DMUS_S_FREE;
    }

    // The Tool is set up to only receive messages of types
    // DMUS_PMSGT_NOTIFICATION
    if (pNotiMsg->guidNotificationType == GUID_NOTIFICATION_MEASUREANDBEAT)
    {
        if (pNotiMsg->dwField1 == 0)
            Blink(eMeasure);
        else
            Blink(eBeat);
    }    

    // Return DMUS_S_REQUEUE so the original message is requeued
    return DMUS_S_REQUEUE;
}

//-----------------------------------------------------------------------------
// Name: CMeasureTool::Flush()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CMeasureTool::Flush( IDirectMusicPerformance* pPerf, 
                                            DMUS_PMSG* pDMUS_PMSG,
                                            REFERENCE_TIME rt)
{
    // This toilette does not need to flush.
    return E_NOTIMPL;
}


// ------------------------------------------------------------------------------
// Name: CMeasureTool::Blink()
// Desc: 
// ------------------------------------------------------------------------------
void CMeasureTool::Blink(EBeatType eType)
{
    HWND hwndBox = GetDlgItem(m_hwndParent, IDC_BLINKY);

    if (hwndBox)
    {
        HDC         hdcBox = GetDC(hwndBox);
        RECT        rcBox;
        HBRUSH      hbrColored, hbrOld;
        COLORREF    color = RGB(0, 0, 0); 
        UINT        nTimerId = 0;  // using 'this' as a LUID
        
        switch (eType)
        {
            case eOff:
                KillTimer(m_hwndParent, nTimerId);    
                color = GetSysColor(COLOR_3DFACE);
                break;
            case eMeasure:
                SetTimer(m_hwndParent, nTimerId, 100, Unblink);
                color = RGB(255, 0, 0); // blink red on the measure
                break;
            case eBeat:
                SetTimer(m_hwndParent, nTimerId, 100, Unblink);
                color = RGB(0, 255, 0); // blink green on the beat
        }
        
        hbrColored = (HBRUSH)CreateSolidBrush(color);
        hbrOld = (HBRUSH)SelectObject(hdcBox, hbrColored);

        GetClientRect(hwndBox, &rcBox);
        Rectangle(hdcBox, rcBox.left, rcBox.top, rcBox.right, rcBox.bottom);

        SelectObject(hdcBox, hbrOld);
        DeleteObject(hbrColored);
        ReleaseDC(hwndBox, hdcBox);
    }
}

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
void CALLBACK Unblink
(
    HWND        hwnd,
    UINT        uMsg,
    UINT_PTR    idEvent,
    DWORD       dwTime
)
{
    if( g_pMusicTool )
        g_pMusicTool->Blink(eOff);
}
 
