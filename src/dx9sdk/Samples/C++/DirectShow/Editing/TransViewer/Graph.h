// ---------------------------------------------------------------------------
// File: CPoster.h
// 
// CGraphHelper: Manages filter graph operations, such as running and pausing. 
//               Basically a thin wrapper around the Filter Graph Manager
//      
// Copyright (c) 2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#pragma once

typedef void (*GRAPH_EVENT_CALLBACK_FN)(long evCode, long Param1, long Param2);


const long WM_GRAPHNOTIFY = WM_APP + 1;   // Window message for graph events

class CGraphHelper 
{

private:
    CComPtr<IGraphBuilder>  m_pGraph;
    CComPtr<IMediaEventEx>  m_pEvent;
    CComPtr<IMediaControl>  m_pControl;

    FILTER_STATE            m_state;

public:
    CGraphHelper();

    FILTER_STATE State() { return m_state; }

    HRESULT SetFilterGraph(IGraphBuilder *pGraph);

    HRESULT SetEventWindow(HWND hwnd);
    HRESULT ProcessEvents(GRAPH_EVENT_CALLBACK_FN fn);
    
    HRESULT SetVideoWindow(HWND hwnd);

    HRESULT Stop();
    HRESULT Pause();
    HRESULT Run();

};


