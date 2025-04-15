//------------------------------------------------------------------------------
// File: VmrGlobals.cpp
//
// Desc: DirectShow sample code - a simple full screen video playback sample.
//       Using the Windows XP Video Mixing Renderer, a video is played back in
//       a full screen exclusive mode.
//      
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

// Pre compiled header
#include "stdafx.h"

// Project headers
#include "VmrGlobals.h"
#include "Helpers.h"

using namespace Helpers;
#include "DShowUtils.h"
using namespace DShowUtils;

// VMR objects
IFilterGraph*           g_pFilterGraph=0;
IGraphBuilder*          g_pGraphBuilder=0;
IBaseFilter*            g_pVmr=0;

// DirectDraw objects needed for exclusive mode
LPDIRECTDRAW7           g_dd7=0;
LPDIRECTDRAWSURFACE7    g_primarySurface=0;
LPDIRECTDRAWSURFACE7    g_backBuffer=0;


// Text properties -- not essential to the exclusive mode
LPDIRECTDRAWSURFACE7    g_textSurface=0;
RECT                    g_textPlacement={0};
const DWORD             TEXT_SURFACE_HEIGHT = 100;
const LPCTSTR           g_text = _T("Press Esc or Alt+F4 to exit\0");



//----------------------------------------------------------------------------
//  CreateVMRGlobals
// 
//  Creates VMR Globals
//
//  Return: true if success 
//----------------------------------------------------------------------------
BOOL 
CreateVMRGlobals()
{
    HRESULT hr;

    ReleaseVMRGlobals();

    // Create Filter graph
    hr = CoCreateInstance(CLSID_FilterGraph,
                          NULL, CLSCTX_INPROC,
                          IID_IFilterGraph, (LPVOID *)&g_pFilterGraph);
    if( SUCCEEDED( hr) ) 
    {
        hr = g_pFilterGraph->QueryInterface(IID_IGraphBuilder, (LPVOID *)&g_pGraphBuilder);
        if( FAILED( hr ) )
        {
            RELEASE(g_pFilterGraph);
        }
        else
        {
            hr = AddVmrToFilterGraph( g_pFilterGraph, & g_pVmr );
            if( FAILED( hr ) )
            {
                RELEASE(g_pGraphBuilder);
                RELEASE(g_pFilterGraph);                
            }
        }
    }

    return SUCCEEDED( hr );
}


//----------------------------------------------------------------------------
//  ReleaseVMRGlobals
// 
//  Releases the global VMR variables
//
//  Return: 
//----------------------------------------------------------------------------
void
ReleaseVMRGlobals()
{
    ReleaseDDObjects();

    RELEASE(g_pVmr);
    RELEASE(g_pGraphBuilder);
    RELEASE(g_pFilterGraph);
}


//----------------------------------------------------------------------------
//  CreateDDObjects
// 
//  Creates the DirectDraw objects.
//
//  Parameters:
//      hwnd -- the main app window
//      screenWidth 
//      screenHeight 
//      bitDepth
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
HRESULT 
CreateDDObjects(HWND hwnd, DWORD screenWidth, DWORD screenHeight, DWORD bitDepth)
{
    HRESULT hr;
    DDSURFACEDESC2 ddsd={0};

    ReleaseDDObjects();

    hr = DirectDrawCreateEx(NULL, (LPVOID *)&g_dd7, IID_IDirectDraw7, NULL);
    if (FAILED(hr)) 
    {
        return hr;
    }

    // Get into fullscreen exclusive mode
    hr = g_dd7->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (FAILED(hr)) 
    {
        ReleaseDDObjects();
        return hr;
    }

    hr = g_dd7->SetDisplayMode(screenWidth, screenHeight, bitDepth, 0, NULL);
    if( FAILED( hr ) )
    {
        ReleaseDDObjects();
        ::ShowWindow( hwnd, SW_HIDE);
        ::MessageBox(NULL, TEXT("This sample cannot continue, because video driver does not support 640x480x32 mode.\r\n")\
                           TEXT("You may want to modify this sample or use a different video device. Application will now exit."), 
                           TEXT("Error"), MB_OK);
        return hr;
    }

    // Create the primary surface with 1 back buffer
    INITDDSTRUCT<DDSURFACEDESC2>(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP |
                          DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;
    ddsd.dwBackBufferCount = 1;

    hr = g_dd7->CreateSurface(&ddsd, &g_primarySurface, NULL);
    if (FAILED(hr)) 
    {
        ReleaseDDObjects();
        return hr;
    }

    // Get a pointer to the back buffer
    DDSCAPS2  ddscaps = { DDSCAPS_BACKBUFFER, 0, 0, 0 };

    hr = g_primarySurface->GetAttachedSurface(&ddscaps, &g_backBuffer);
    if (FAILED(hr)) 
    {
        ReleaseDDObjects();
        return hr;
    }

    return hr;
}


//----------------------------------------------------------------------------
//  Release DD objects
// 
//  Releases the global VMR variables
//
//  Return: 
//----------------------------------------------------------------------------
void
ReleaseDDObjects()
{
    // NOTE: If you have a secondary surface,
    //       releasing primary before secondary generates an exception
    RELEASE(g_primarySurface);
    RELEASE(g_dd7);
}


