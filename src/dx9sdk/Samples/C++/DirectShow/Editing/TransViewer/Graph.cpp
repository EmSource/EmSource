//------------------------------------------------------------------------------
// File: Graph.cpp
//
// Desc: DirectShow sample code - TransViewer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "transviewer.h"
#include "Graph.h"


//-----------------------------------------------------------------------------
// Name: CGraphHelper
// Desc: Constructor
//-----------------------------------------------------------------------------

CGraphHelper::CGraphHelper() : 
              m_state(State_Stopped)
{
    // Empty
}


//-----------------------------------------------------------------------------
// Name: SetFilterGraph
// Desc: Sets the filter graph manager. Use NULL to release the graph.
//-----------------------------------------------------------------------------

HRESULT CGraphHelper::SetFilterGraph(IGraphBuilder *pGraph)
{
    HRESULT hr=S_OK;

    if (pGraph)
    {
        m_pGraph = pGraph;
        m_pGraph.QueryInterface(&m_pEvent);     // IMediaEventEx
        m_pGraph.QueryInterface(&m_pControl);   // IMediaControl
    }
    else        // Clear out the graph and related objects
    {
        if (m_pGraph)
        {           
            Stop();

            CComQIPtr<IVideoWindow> pVideo(m_pGraph);
            if (pVideo)
            {
                hr = pVideo->put_Visible(OAFALSE);
                hr = pVideo->put_Owner(NULL);
            }
        }

        m_pGraph = 0;
        m_pEvent = 0;
        m_pControl = 0;
    }
    
    return hr;
}


//-----------------------------------------------------------------------------
// Name: ProcessEvents
// Desc: Process all pending graph events, using an app-defined callback.
//
// fn:   Pointer to the callback function
//-----------------------------------------------------------------------------

HRESULT CGraphHelper::ProcessEvents(GRAPH_EVENT_CALLBACK_FN fn)
{
    HRESULT hr;
    LONG evCode = 0, param1 = 0, param2 = 0;

    ASSERT(fn);     // Assume that a callback function was provided

    // Verify that the IMediaEventEx interface is valid
    if (!m_pEvent)
        return E_UNEXPECTED;

    // Process all events
    while ((hr = m_pEvent->GetEvent(&evCode, (LONG_PTR *)&param1, 
                                  (LONG_PTR *)&param2, 0)) == S_OK)
    {
        // Call the specified callback function
        if (fn)
            fn(evCode, param1, param2);

        // Free memory associated with the callback
        m_pEvent->FreeEventParams(evCode, param1, param2);
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Stop 
// Desc: Stop the graph and seek to the beginning.
//-----------------------------------------------------------------------------

HRESULT CGraphHelper::Stop()
{
    HRESULT hr=S_OK;

    if (!m_pControl)
    {
        return E_UNEXPECTED;
    }

    if (m_state != State_Stopped)
    {
        hr = m_pControl->Pause();

        CComQIPtr<IMediaSeeking> pSeek(m_pGraph);
        if (pSeek)
        {
            LONGLONG rtTime = 0; 
            hr = pSeek->SetPositions(&rtTime, AM_SEEKING_AbsolutePositioning, 
                                     NULL, AM_SEEKING_NoPositioning);
        }
        
        hr = m_pControl->StopWhenReady();
        m_state = State_Stopped;
    }

    return hr;
}


//-----------------------------------------------------------------------------
// Name: Pause
// Desc: Pause the graph.
//-----------------------------------------------------------------------------

HRESULT CGraphHelper::Pause()
{
    if (!m_pControl)
    {
        return E_UNEXPECTED;
    }
    else if (m_state == State_Paused)
    {
        return S_FALSE;
    }
    else
    {
        m_state = State_Paused;
        return m_pControl->Pause();
    }
}


//-----------------------------------------------------------------------------
// Name: Run
// Desc: Run the graph.
//-----------------------------------------------------------------------------

HRESULT CGraphHelper::Run()
{
    if (m_pControl)
    {
        m_state = State_Running;
        return m_pControl->Run();
    }
    else
    {
        return E_UNEXPECTED;
    }
}


//-----------------------------------------------------------------------------
// Name: SetVideoWindow
// Desc: Set the owner window for the video window.
//
// The Video Window filter creates its own window to display the video.
// This function uses IVideoWindow to make the video window into the child 
// of an application window. 
//
//-----------------------------------------------------------------------------

HRESULT CGraphHelper::SetVideoWindow(HWND hwnd)
{
    HRESULT hr = E_FAIL;
    CComQIPtr<IVideoWindow> pVideo(m_pGraph);

    if (pVideo)
    {
        RECT grc;

        hr = pVideo->put_Owner((OAHWND)hwnd); 
        hr = pVideo->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);

        GetClientRect(hwnd, &grc);
        hr = pVideo->SetWindowPosition(0, 0, grc.right, grc.bottom);
    }

    return hr;
}


//-----------------------------------------------------------------------------
// Name: SetEventWindow
// Desc: Specifies a window to receive WM_GRAPHNOTIFY events whenever 
//       DirectShow graph events occur.
//-----------------------------------------------------------------------------

HRESULT CGraphHelper::SetEventWindow(HWND hwnd)
{
    if (m_pEvent)
    {
        return m_pEvent->SetNotifyWindow((OAHWND)hwnd, WM_GRAPHNOTIFY, 0);
    }
    else
    {
        return E_UNEXPECTED;
    }
}


