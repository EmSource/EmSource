//------------------------------------------------------------------------------
// File: MultiGraphSession.cpp
//
// Desc: DirectShow sample code - MultiVMR9 MultiPlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MultiVMR9.h"
#include "VMR9Subgraph.h"
#include "MultigraphSession.h"

extern HINSTANCE g_hInstance;
const TCHAR g_achVideoWindowClass[] = TEXT("MultiVMR9 Video Window class");

/******************************Public*Routine******************************\
* CMultigraphSession
*
* constructor
\**************************************************************************/
CMultigraphSession::CMultigraphSession()
    : m_hwndVideo( NULL )
    , m_pWizard( NULL )
    , m_pRenderEngine( NULL )
    , m_pMixerControl( NULL )
    , m_pUILayer( NULL )
{
}

/******************************Public*Routine******************************\
* ~CMultigraphSession
*
* destructor
\**************************************************************************/
CMultigraphSession::~CMultigraphSession()
{
    Terminate();

    RELEASE( m_pWizard );
    RELEASE( m_pRenderEngine );
    RELEASE( m_pMixerControl );
    RELEASE( m_pUILayer );
}

/******************************Public*Routine******************************\
* AddSource
*
* adds new source to the list, attaches it to the wizard
\**************************************************************************/
HRESULT CMultigraphSession::AddSource(WCHAR *wcPath, DWORD_PTR& dwID)
{
    CVMR9Subgraph *pSubgraph = NULL;

    HRESULT hr = S_OK;
    if( !wcPath )
    {
        return E_POINTER;
    }
    if( !m_pWizard )
    {
        return VFW_E_WRONG_STATE;
    }

    try
    {
		// commented lines work fine on XP and NT4
		/*
        if( INVALID_FILE_ATTRIBUTES == ::GetFileAttributesW( wcPath))
        {
            throw VFW_E_NOT_FOUND;
        }*/

		// Unicode-related workaround for WindowsMe/98
		{
			char szPath[MAX_PATH];
			DWORD dwGFA = 0L;
			DWORD dwErr = 0L;

			WideCharToMultiByte(CP_ACP, 0, wcPath, -1, szPath, MAX_PATH, NULL, NULL);
			dwGFA = ::GetFileAttributesA( szPath);
			if( INVALID_FILE_ATTRIBUTES == dwGFA)
			{
				dwErr = GetLastError();
				throw VFW_E_NOT_FOUND;
			}
		}

        pSubgraph = new CVMR9Subgraph;
        if( !pSubgraph )
        {
            throw E_OUTOFMEMORY;
        }

        hr = pSubgraph->BuildAndRender( wcPath, m_pWizard );
        if( FAILED(hr))
        {
            throw hr;
        }

        //remember the ID, add to the list
        dwID = pSubgraph->GetID();

        m_sources.push_back( pSubgraph );
    }
    catch( HRESULT hr1 )
    {
        if( pSubgraph )
        {
            delete pSubgraph;
        }
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* DeleteSource
*
* deletes a source from the list, detaches it from the wizard
\**************************************************************************/
HRESULT CMultigraphSession::DeleteSource( DWORD_PTR dwID )
{
    HRESULT hr = S_OK;

    CVMR9Subgraph *pSubgraph = NULL;

    try
    {
        if( !m_pWizard )
        {
            throw VFW_E_WRONG_STATE;
        }

        pSubgraph = GetSubgraph( dwID );
        if( !pSubgraph )
        {
            throw VFW_E_NOT_FOUND;
        }

        hr = pSubgraph->Stop();
        if( FAILED(hr))
        {
            throw hr;
        }

        hr = m_pWizard->Detach( pSubgraph->GetID());
        if( FAILED(hr))
        {
            throw hr;
        }

        m_sources.remove( pSubgraph );

        delete pSubgraph;
        pSubgraph = NULL;
        hr = S_OK;
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    return hr;
}

/******************************Public*Routine******************************\
* Terminate
*
* terminates wizard
\**************************************************************************/
HRESULT CMultigraphSession::Terminate()
{
    HRESULT hr = S_OK;
    list<CVMR9Subgraph*>::iterator it;

    CVMR9Subgraph* pSubgraph = NULL;

    try
    {
        // 1. Detach all the existing subgraphs
        while( false == m_sources.empty())
        {
            it = m_sources.begin();
            pSubgraph = (CVMR9Subgraph*)(*it);
            ASSERT( pSubgraph );

            hr = DeleteSource( pSubgraph->GetID());
            if( FAILED(hr))
                throw hr;
        }

        // 2. Terminate Wizard, if there is any
        if( m_pWizard )
        {
            hr = m_pWizard->Terminate();
            if( FAILED(hr))
                throw hr;
        }

        // 3. Destroy video window
        if( IsWindow( m_hwndVideo ))
        {
            ::DestroyWindow( m_hwndVideo );
            m_hwndVideo = NULL;
        }

        UnregisterClass( g_achVideoWindowClass, g_hInstance);
    }
    catch( HRESULT hr1)
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* GetSubgraph
*
* find subgraph in the list by dwID
\**************************************************************************/
CVMR9Subgraph* CMultigraphSession::GetSubgraph(  DWORD_PTR dwID  )
{
    CVMR9Subgraph* pSubgraph = NULL;
    list<CVMR9Subgraph*>::iterator start, end, it;

    start = m_sources.begin();
    end = m_sources.end();

    for(it = start; it!= end; it++)
    {
        if( (*it) && (*it)->GetID() == dwID )
        {
            pSubgraph = (CVMR9Subgraph*)(*it);
            break;
        }
    }
    return pSubgraph;
}

/******************************Public*Routine******************************\
* GetWizard
*
\**************************************************************************/
IMultiVMR9Wizard* CMultigraphSession::GetWizard( )
{
    IMultiVMR9Wizard* pRes = NULL;
    if( m_pWizard )
    {
        pRes = m_pWizard;
        pRes->AddRef();
    }
    return pRes;
}

/******************************Public*Routine******************************\
* GetRenderEngine
*
\**************************************************************************/
IMultiVMR9RenderEngine* CMultigraphSession::GetRenderEngine( )
{
    IMultiVMR9RenderEngine* pRes = NULL;
    if( m_pRenderEngine )
    {
        pRes = m_pRenderEngine;
        pRes->AddRef();
    }
    return pRes;
}

/******************************Public*Routine******************************\
* GetMixerControl
*
\**************************************************************************/
IMultiVMR9MixerControl* CMultigraphSession::GetMixerControl( )
{
    IMultiVMR9MixerControl* pRes = NULL;
    if( m_pMixerControl )
    {
        pRes = m_pMixerControl;
        pRes->AddRef();
    }
    return pRes;
}

/******************************Public*Routine******************************\
* GetUILayer
*
\**************************************************************************/
IMultiVMR9UILayer* CMultigraphSession::GetUILayer( )
{
    IMultiVMR9UILayer* pRes = NULL;
    if( m_pUILayer )
    {
        pRes = m_pUILayer;
        pRes->AddRef();
    }
    return pRes;
}

/******************************Public*Routine******************************\
* GetFrameRate
*
\**************************************************************************/
int CMultigraphSession::GetFrameRate()
{
    int nRes = 0;

    if( !m_pRenderEngine )
        return 30;

    m_pRenderEngine->GetFrameRate( &nRes );
    return nRes;
}

/******************************Public*Routine******************************\
* SetColor
*
\**************************************************************************/
HRESULT CMultigraphSession::SetColor( COLORREF color )
{
    HRESULT hr = S_OK;

    if( !m_pMixerControl )
        return E_FAIL;

    hr = m_pMixerControl->SetBackgroundColor( color );

    return hr;
}

/******************************Public*Routine******************************\
* LoopSources
*
* go through the list and reset time to start if movie is close to the end
\**************************************************************************/
void CMultigraphSession::LoopSources()
{
    CVMR9Subgraph *pSource = NULL;
    LONGLONG llCur;
    LONGLONG llDur;

    list<CVMR9Subgraph*>::iterator start, end, it;
    start = m_sources.begin();
    end = m_sources.end();

    for( it = start; it != end; it++)
    {
        pSource = (CVMR9Subgraph*)(*it);
        if( !pSource )
            continue;

        pSource->GetTimes( llCur, llDur);
        // 100ms
        if( llDur - llCur < 1000000L )
        {
            pSource->SetTime( 0L );
        }
    }
}

/******************************Public*Routine******************************\
* CreateVideoWindow_
*
* creates video window
\**************************************************************************/
HRESULT CMultigraphSession::CreateVideoWindow_(UINT Width, UINT Height, DWORD dwStyle)
{
    HRESULT hr = S_OK;
    WNDCLASSEX wcex;
    RECT rc;
    RECT rcClient;
    int dx, dy;

    try
    {
        if( IsWindow( m_hwndVideo ))
            throw E_UNEXPECTED;

        wcex.cbSize = sizeof(WNDCLASSEX); 
        wcex.style          = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc    = (WNDPROC)CMultigraphSession::VideoWndProc;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = g_hInstance;
        wcex.hIcon          = NULL;
        wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
        wcex.lpszMenuName   = TEXT("");
        wcex.lpszClassName  = g_achVideoWindowClass;
        wcex.hIconSm        = NULL;

        RegisterClassEx( &wcex);

        m_hwndVideo  = CreateWindow(    g_achVideoWindowClass, 
                                        TEXT("VMR9 Custom Allocator-Presenter"), 
                                        dwStyle,
                                        100, 100, 
                                        800, 600, 
                                        NULL, 
                                        NULL, 
                                        g_hInstance, 
                                        NULL);
        if( !IsWindow( m_hwndVideo ))
            throw E_FAIL;

        ::SetWindowLong( m_hwndVideo, GWL_USERDATA, (LONG)this);

        // resize the window so that client area be 800x600
        ::GetClientRect( m_hwndVideo, &rcClient);

        ::GetWindowRect( m_hwndVideo, &rc);
        dx = rc.right - rc.left - rcClient.right;
        dy = rc.bottom - rc.top - rcClient.bottom;

        ::SetWindowPos( m_hwndVideo, HWND_TOP, 0, 0, Width+dx, Height+dy, SWP_NOMOVE);

    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    return hr;
}

/******************************Public*Routine******************************\
* VideoWndProc
*
\**************************************************************************/
LRESULT CALLBACK CMultigraphSession::VideoWndProc(
                                        HWND hwnd,      // handle to window
                                        UINT uMsg,      // message identifier
                                        WPARAM wParam,  // first message parameter
                                        LPARAM lParam   // second message parameter
                                        )
{
    CMultigraphSession* This = NULL;
    IMultiVMR9UILayer* pUI = NULL;
    LRESULT lRes = 0;

    This = (CMultigraphSession*)::GetWindowLong( hwnd, GWL_USERDATA);
    if( This )
    {
        pUI = This->GetUILayer();
    }

    lRes = DefWindowProc( hwnd, uMsg, wParam, lParam);

    if( pUI )
    {
        pUI->ProcessMessage( uMsg, (UINT)wParam, (LONG)lParam);
    }

    RELEASE( pUI );

    return lRes;
}

