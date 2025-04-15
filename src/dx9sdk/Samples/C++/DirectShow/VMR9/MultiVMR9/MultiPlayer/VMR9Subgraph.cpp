//------------------------------------------------------------------------------
// File: VMR9Subgraph.cpp
//
// Desc: DirectShow sample code - MultiVMR9 MultiPlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MultiVMR9.h"
#include "VMR9Subgraph.h"

/******************************Public*Routine******************************\
* CVMR9Subgraph
*
* constructor
\**************************************************************************/

CVMR9Subgraph::CVMR9Subgraph()
    : m_dwID( NULL)
{
    m_wcPath[0] = L'\0';
    m_achPath[0] = TEXT('\0');
}

/******************************Public*Routine******************************\
* CVMR9Subgraph
*
* destructor
\**************************************************************************/
CVMR9Subgraph::~CVMR9Subgraph()
{
}

/******************************Public*Routine******************************\
* BuildAndRender
*
* Builds the filter graph to render the media file located at wcPath with use of VMR9; 
* if wizard is provided, VMR9 is set to the renderless mode and custom allocator-
* presenter (which is pWizard in this sample) is advised.
*
* Return values: errors from the filter graph and wizard
\**************************************************************************/
HRESULT CVMR9Subgraph::BuildAndRender( WCHAR *wcPath, CComPtr<IMultiVMR9Wizard> pWizard )
{
    HRESULT hr = S_OK;
    CComPtr<IVMRFilterConfig9> pConfig;
    CComPtr<IGraphBuilder>  pGb;

    if( !wcPath )
    {
        return E_POINTER;
    }

    USES_CONVERSION;
    wcsncpy( m_wcPath, wcPath, MAX_PATH);
    _tcsncpy( m_achPath, W2T(wcPath), MAX_PATH);

    // first, check that file exists
    if( INVALID_FILE_ATTRIBUTES == GetFileAttributes( m_achPath))
    {
        MessageBox(NULL, TEXT("Requested media file was not found"), TEXT("Error"), MB_OK);
        return VFW_E_NOT_FOUND;
    }

    // create graph
    hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
        IID_IFilterGraph, (void**)&(m_pGraph.p) );
    if( FAILED(hr))
    {
        MessageBox(NULL, TEXT("Failed to create the filter graph"), TEXT("Error"), MB_OK);
        return hr;
    }

    // create and add VMR9
    hr = CoCreateInstance( CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER,
        IID_IBaseFilter, (void**)&(m_pVMR.p) );
    if( FAILED(hr))
    {
        MessageBox(NULL, TEXT("Failed to create instance of VMR9"), TEXT("Error"), MB_OK);
        return hr;
    }

    hr = m_pGraph->AddFilter( m_pVMR, L"VMR9");
    if( FAILED(hr))
    {
        MessageBox(NULL, TEXT("Failed to add VMR9 to the graph"), TEXT("Error"), MB_OK);
        return hr;
    }
    // configure VMR9
    hr = m_pVMR->QueryInterface( IID_IVMRFilterConfig9, (void**)&(pConfig.p) );
    if( FAILED(hr))
    {
        MessageBox(NULL, TEXT("Cannot get IVMRFilterConfig9 from VMR9"), TEXT("Error"), MB_OK);
        return hr;
    }
    
    // if wizard is provided, set VMR to the renderless code and attach to the wizard
    if( pWizard )
    {
        // set VMR to the renderless mode
        hr = pConfig->SetRenderingMode( VMR9Mode_Renderless );
        if( FAILED(hr))
        {
            MessageBox(NULL, TEXT("Failed to set VMR9 to the renderless mode"), TEXT("Error"), MB_OK);
            return hr;
        }

        hr = pWizard->Attach( m_pVMR, &m_dwID );
        if( FAILED(hr))
        {
            MessageBox(NULL, TEXT("Failed to attach graph to the wizard"), TEXT("Error"), MB_OK);
            return hr;
        }
    }

    // try to render media source
    hr = m_pGraph->QueryInterface( IID_IGraphBuilder, (void**)&(pGb.p) );
    if( FAILED(hr))
    {
        MessageBox(NULL, TEXT("Cannot get IGraphBuilder from the filter graph"), TEXT("Error"), MB_OK);
        return hr;
    }

    hr = pGb->RenderFile( m_wcPath, NULL);
    if( FAILED(hr))
    {
        MessageBox(NULL, TEXT("Failed to render specified media file"), TEXT("Error"), MB_OK);
        return hr;
    }

    hr = CheckVMRConnection();
    if( FAILED(hr))
    {
        hr = pWizard->Detach( m_dwID );
        MessageBox(NULL, TEXT("Application does not support this media type.\r\nTry some other media source"),
            TEXT("Error"), MB_OK);
        return hr;
    }

    // ok, all is rendered, now get MediaControl, MediaSeeking and continue
    hr = m_pGraph->QueryInterface( IID_IMediaControl, (void**)&(m_pMc.p) );
    if( FAILED(hr))
    {
        MessageBox(NULL, TEXT("Cannot find IMediaControl interface"), TEXT("Error"), MB_OK);
        return hr;
    }

    hr = m_pGraph->QueryInterface( IID_IMediaSeeking, (void**)&(m_pMs.p) );
    if( FAILED(hr))
    {
        MessageBox(NULL, TEXT("Cannot find IMediaSeeking interface"), TEXT("Error"), MB_OK);
        return hr;
    }

    return hr;
}


/******************************Public*Routine******************************\
* CheckVMRConnection
\**************************************************************************/
HRESULT CVMR9Subgraph::CheckVMRConnection()
{
    HRESULT hr = S_OK;
    bool bConnected = false;

    CComPtr<IEnumPins> pEnum;
    CComPtr<IPin> pPin;

    if( !m_pVMR )
        return E_UNEXPECTED;

    hr = m_pVMR->EnumPins( &pEnum );
    if( FAILED(hr))
        return hr;

    hr = pEnum->Next( 1, &pPin, NULL);
    while( SUCCEEDED(hr) && pPin)
    {
        CComPtr<IPin> pConnectedPin;
        hr = pPin->ConnectedTo( &pConnectedPin );

        if( SUCCEEDED(hr) && pConnectedPin )
        {
            bConnected = true;
            break;
        }

        pPin = NULL;
        hr = pEnum->Next( 1, &pPin, NULL);
    }// while

    hr = (true == bConnected) ? S_OK : E_FAIL;
    return hr;
}

/******************************Public*Routine******************************\
* Run
\**************************************************************************/
HRESULT CVMR9Subgraph::Run()
{
    HRESULT hr = S_OK;

    if( !m_pMc )
    {
        return E_UNEXPECTED;
    }
    hr = m_pMc->Run();

    return hr;
}

/******************************Public*Routine******************************\
* Pause
\**************************************************************************/
HRESULT CVMR9Subgraph::Pause()
{
    HRESULT hr = S_OK;

    if( !m_pMc )
    {
        return E_UNEXPECTED;
    }
    hr = m_pMc->Pause();

    return hr;
}

/******************************Public*Routine******************************\
* Stop
\**************************************************************************/
HRESULT CVMR9Subgraph::Stop()
{
    HRESULT hr = S_OK;
    OAFilterState state;

    if( !m_pMc )
    {
        return E_UNEXPECTED;
    }

    hr = m_pMc->Stop();
    state = State_Running;

    while( State_Stopped != state && SUCCEEDED(hr))
    {
        hr = m_pMc->GetState(100, &state);
        Sleep(100);
    }

    return hr;
}

/******************************Public*Routine******************************\
* GetState
*
* Returns OAFilterState from IMediaControl of the graph
*
* Return values: errors from the filter graph and wizard
\**************************************************************************/
OAFilterState CVMR9Subgraph::GetState()
{
    OAFilterState state = State_Stopped;
    if( m_pMc )
    {
        HRESULT hr = m_pMc->GetState( 20, &state );
    }
    return state;
}

/******************************Public*Routine******************************\
* SetTime
*
*
\**************************************************************************/
HRESULT CVMR9Subgraph::SetTime( LONGLONG llCur)
{
    HRESULT hr = S_OK;
    LONGLONG llDur = 0L;

    if( !m_pMs )
        return E_FAIL;

    hr = m_pMs->SetPositions(   &llCur, AM_SEEKING_AbsolutePositioning, 
                                &llDur, AM_SEEKING_NoPositioning);

    return hr;
}

/******************************Public*Routine******************************\
* GetTimes
*
\**************************************************************************/
HRESULT CVMR9Subgraph::GetTimes( LONGLONG& llCur, LONGLONG& llDur)
{
    HRESULT hr = S_OK;
    if( !m_pMs )
        return E_FAIL;

    hr = m_pMs->GetPositions( &llCur, &llDur );
    return hr;
}

/******************************Public*Routine******************************\
* GetPathT, GetPathW
*
\**************************************************************************/
void CVMR9Subgraph::GetPathT( TCHAR* achPath )
{
    if( achPath )
    {
        _tcscpy( achPath, m_achPath);
    }
}

void CVMR9Subgraph::GetPathW( WCHAR* wcPath )
{
    if( wcPath )
    {
        wcscpy( wcPath, m_wcPath);
    }
}


/******************************Public*Routine******************************\
* DestroyGraph
*
* Stops the graph, destroys and removes all the filters (VMR9 is removed last)
*
\**************************************************************************/
HRESULT CVMR9Subgraph::DestroyGraph()
{
    HRESULT hr = S_OK;
    OAFilterState state;

    if( !m_pGraph )
    {
        return E_POINTER;
    }

    FILTER_INFO fi;
    CComPtr<IMediaControl> pMc;
    CComPtr<IEnumFilters> pEnum;
    CComPtr<IBaseFilter> pFilter;
    CComPtr<IBaseFilter> pVMR = NULL;

    // 1. stop the graph
    hr = m_pGraph->QueryInterface( IID_IMediaControl, (void**)&(pMc.p) );
    if( FAILED(hr))
    {
        return hr;
    }

    do
    {
        hr = pMc->GetState(100, &state);
    } while( S_OK == hr && State_Stopped != state );

    hr = m_pGraph->EnumFilters( &(pEnum.p) );
    if( FAILED(hr))
    {
        return hr;
    }

    // tear off
    hr = pEnum->Next(1, &(pFilter.p), NULL);
    while( S_OK == hr && pFilter )
    {
        hr = DisconnectPins( pFilter );
        pFilter = NULL;
        hr = pEnum->Next(1, &(pFilter.p), NULL);
    }
    pFilter = NULL;

    // remove filters
    hr = pEnum->Reset();
    hr = pEnum->Next(1, &(pFilter.p), NULL);
    while( S_OK == hr && pFilter )
    {
        hr = pFilter->QueryFilterInfo( &fi);
        if( fi.pGraph)
            fi.pGraph->Release();

        if( 0 == wcscmp( fi.achName, L"VMR9"))
        {
            pVMR = pFilter;
        }
        hr = m_pGraph->RemoveFilter( pFilter);
        pFilter = NULL;

        hr = pEnum->Reset();
        hr = pEnum->Next(1, &pFilter, NULL);
    }

    pFilter = NULL;
    pEnum = NULL;
    pVMR = NULL;

    return S_OK;
}

/******************************Public*Routine******************************\
* DisconnectPins
*
* Disconnects pins of a filter
*
\**************************************************************************/
HRESULT CVMR9Subgraph::DisconnectPins( CComPtr<IBaseFilter> pFilter)
{
    HRESULT hr = S_OK;

    CComPtr<IEnumPins> pEnum;
    CComPtr<IPin> pPin;

    if( !pFilter )
    {
        return E_POINTER;
    }

    hr = pFilter->EnumPins( &pEnum );
    if( FAILED(hr))
    {
        return hr;
    }
    hr = pEnum->Next( 1, &pPin, NULL);

    while( S_OK == hr && pPin )
    {
        hr = pPin->Disconnect();
        pPin = NULL;
        hr = pEnum->Next( 1, &pPin, NULL);
    }

    pPin = NULL;
    pEnum = NULL;

    return S_OK;
}

