//------------------------------------------------------------------------------
// File: MultiGraphSession.h
//
// Desc: DirectShow sample code - MultiVMR9 MultiPlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "VMR9Subgraph.h"
#include <list>

using namespace std;

class CMultigraphSession
{
public:

    CMultigraphSession();
    virtual ~CMultigraphSession();

    virtual HRESULT Initialize()=0;
    virtual HRESULT Terminate();

    HRESULT AddSource(WCHAR *wcPath, DWORD_PTR& dwID);
    HRESULT DeleteSource( DWORD_PTR dwID );

    // get functions
    CVMR9Subgraph*   GetSubgraph(  DWORD_PTR dwID  );
    int              GetFrameRate();
    int              GetSize(){ return (int)(m_sources.size()); }
    HWND             GetWindow(){ return m_hwndVideo; }


    IMultiVMR9Wizard* GetWizard( );
    IMultiVMR9RenderEngine* GetRenderEngine();
    IMultiVMR9MixerControl* GetMixerControl();
    IMultiVMR9UILayer* GetUILayer();

    // set functions
    HRESULT SetFrameRate( int nFPS);
    HRESULT SetColor( COLORREF color );

    void LoopSources();

    // video window processing
    static LRESULT CALLBACK VideoWndProc(
                                        HWND hwnd,      // handle to window
                                        UINT uMsg,      // message identifier
                                        WPARAM wParam,  // first message parameter
                                        LPARAM lParam   // second message parameter
                                        );

    // private methods
protected:

    HRESULT CreateVideoWindow_(UINT Width, UINT Height, DWORD dwStyle);

    // private data 
protected:
    list<CVMR9Subgraph*>        m_sources;
    IMultiVMR9Wizard*           m_pWizard;
    IMultiVMR9RenderEngine*     m_pRenderEngine;
    IMultiVMR9MixerControl*     m_pMixerControl;
    IMultiVMR9UILayer*          m_pUILayer;
    HWND                        m_hwndVideo;
};

