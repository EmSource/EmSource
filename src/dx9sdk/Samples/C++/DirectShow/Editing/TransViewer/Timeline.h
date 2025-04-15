// ---------------------------------------------------------------------------
// File: Timeline.h
// 
// Desc: Defines the CTimeline class
//      
// Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#pragma once

class CTimeline
{

private:

    CComPtr<IAMTimeline>    m_pTL;  // The timeline
    CComPtr<IRenderEngine>  m_pRenderEngine;

    CComPtr<IAMSetErrorLog> m_pSetErr;

    // These hold our important timeline objects
    CComPtr<IAMTimelineObj> m_pSource1;
    CComPtr<IAMTimelineObj> m_pSource2;
    CComPtr<IAMTimelineObj> m_pColor1;
    CComPtr<IAMTimelineObj> m_pColor2;
    CComPtr<IAMTimelineObj> m_pTrans;
    
    vector<CLSID>   m_TransList; // holds the list of transitions CLSIDs

    REFERENCE_TIME  m_rtClipStop;    // Default time
    REFERENCE_TIME  m_rtTransLength; // Default transition length

   
private:

    HRESULT AddCompToGroup(IAMTimelineGroup *pGroup, IAMTimelineComp **ppComp);
    HRESULT AddTrackToComp(IAMTimelineComp *pComp, IAMTimelineTrack **ppTrack);
    HRESULT AddSourceToTrack(IAMTimelineTrack *pTrack, IAMTimelineObj **ppSourceObj, 
            int nStretchMode = RESIZEF_PRESERVEASPECTRATIO);


public:

    CTimeline();
    ~CTimeline();

    HRESULT InitTimeline(RECT& VideoRect);
    HRESULT InitTransitionList(HWND hListBox);
    HRESULT SetTransition(int n);
    HRESULT SetFileName(int nSource, const TCHAR* szFileName);
    HRESULT SetSolidColor(int nSource, COLORREF color);
    HRESULT RenderTimeline();

    HRESULT SetProperties(HINSTANCE hinst, HWND hwnd);

    HRESULT GetFilterGraph(IGraphBuilder **ppGraph)
    {
        _ASSERTE(ppGraph != 0);

        if (m_pRenderEngine)
        {
            return m_pRenderEngine->GetFilterGraph(ppGraph);
        }
        else
        {
            *ppGraph = 0;
            return E_UNEXPECTED;
        }
    }

    HRESULT SetErrorLog(IAMErrorLog *pLog)
    {
        _ASSERTE(m_pSetErr != 0);
        return m_pSetErr->put_ErrorLog(pLog);
    }

    HRESULT GetErrorLog(IAMErrorLog **ppLog)
    {
        _ASSERTE(m_pSetErr != 0);
        return m_pSetErr->get_ErrorLog(ppLog);
    }

    REFERENCE_TIME GetClipLength() { return m_rtClipStop; }

    void SetClipLength(REFERENCE_TIME& rt) { m_rtClipStop = rt; }

};

