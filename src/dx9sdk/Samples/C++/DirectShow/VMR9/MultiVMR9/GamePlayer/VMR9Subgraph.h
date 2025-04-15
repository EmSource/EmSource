//------------------------------------------------------------------------------
// File: VMR9Subgraph.h
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#ifndef VMR9SUBGRAPH_HEADER
#define VMR9SUBGRAPH_HEADER

#pragma once

// CVMR9Subgraph

// This class represents a subgraph with VMR9 to be attached to the wizard
// This sample supports only media files, but any DirectShow filter graph
// with VMR9 can be used.

class CVMR9Subgraph
{
public:
    CVMR9Subgraph();
    ~CVMR9Subgraph();

    // public methods
    HRESULT BuildAndRender( WCHAR* wcPath, CComPtr<IMultiVMR9Wizard> pWizard );
    HRESULT Run();
    HRESULT Pause();
    HRESULT Stop();
    HRESULT SetTime( LONGLONG llCur);
    HRESULT DestroyGraph();
    HRESULT DisconnectPins( CComPtr<IBaseFilter> pFilter);
    HRESULT CheckVMRConnection();

    DWORD_PTR GetID(){ return m_dwID;};
    OAFilterState GetState();
    HRESULT GetTimes( LONGLONG& llCur, LONGLONG& llDur);
    void GetPathT( TCHAR* achPath );
    void GetPathW( WCHAR* wcPath );

private:
    // private members

private:
    // private data
    CComPtr<IFilterGraph>   m_pGraph;   // filter graph
    CComPtr<IBaseFilter>    m_pVMR;     // VMR9
    CComPtr<IMediaControl>  m_pMc;      // media control
    CComPtr<IMediaSeeking>  m_pMs;      // media seeking

    WCHAR m_wcPath[MAX_PATH];   // path to the media file, wide char
    TCHAR m_achPath[MAX_PATH];  // path to the media file, TCHAR

    DWORD_PTR m_dwID;   // actual cookie identifying the subgraph; assigned in
                        // IMultiVMR9Wizard::Attach
};

#endif

