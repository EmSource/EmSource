//------------------------------------------------------------------------------
// File: DShowUtils.cpp
//
// Desc: DirectShow sample code - a simple full screen video playback sample.
//       Using the Windows XP Video Mixing Renderer, a video is played back in
//       a full screen exclusive mode.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

// Precompiled headers
#include "stdafx.h"

// Directx and global headers
#include <atlbase.h> // included for atl conversion routines
#include <atlconv.h>

// Project headers
#include "DShowUtils.h"
#include "Helpers.h"
using namespace Helpers;
#include "VMRXclBasic.h"
#include "vmruuids.h"


namespace DShowUtils {

#include "vmrutil.h"

//----------------------------------------------------------------------------
//  OpenMediaFile
// 
//  Opens a movie file
//
//  Parameters:
//          hwndOwner
//          pGB - pointer to an initialized graphBuilder interface
//          achFoundFile - file name that has been opened by the user
//----------------------------------------------------------------------------
HRESULT
OpenMediaFile(HWND           hwndOwner,
              IGraphBuilder* pGB,
              LPTSTR         achFoundFile
    )
{
    USES_CONVERSION; // this is needed for ATL conversion
    HRESULT hr;

    if( ! pGB ) 
    {
        return E_INVALIDARG;
    }
    
    hr = pGB->RenderFile(T2W(achFoundFile),NULL);
    if( FAILED( hr ) )
    {
        MessageBox(hwndOwner, TEXT("Failed to open the movie"),
                   g_szTitle, MB_OK );

    }

    // we need to refresh the window after we are done opening the file.
    if( SUCCEEDED( hr ) ) 
    {
        InvalidateRect( hwndOwner, NULL, FALSE );
        UpdateWindow( hwndOwner );
    }

    return ( hr );
}

//----------------------------------------------------------------------------
//  AddVmrToFilterGraph
// 
//  Creates VMR filter and adds to to the filter graph
//
//  Parameters:
//              pGraph - filter graph
//              ppBaseFilter - out parameter - the created base filter
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
HRESULT
AddVmrToFilterGraph(IFilterGraph* pGraph, IBaseFilter** ppBaseFilter)
{
    if( ! pGraph || ! ppBaseFilter )
    {
        return E_POINTER;
    }

    RELEASE(*ppBaseFilter);

    HRESULT hr; 
    hr = CoCreateInstance(CLSID_VideoMixingRenderer,
                          NULL, CLSCTX_INPROC,IID_IBaseFilter,
                          (LPVOID *)ppBaseFilter);

    if( SUCCEEDED( hr ) ) 
    {
        hr = pGraph->AddFilter(*ppBaseFilter,L"Video Mixing Renderer");
        if( SUCCEEDED( hr ) )
        {
            hr = SetRenderingMode(*ppBaseFilter, VMRMode_Renderless);

            if( FAILED( hr ) )
            {
                RELEASE(*ppBaseFilter);         
            }
        }
        else
        {
            RELEASE(*ppBaseFilter);
        }
    }

    return hr;
}


//----------------------------------------------------------------------------
//  SetRenderingMode
//
//  Set rendering mode of VMR (Windowless, Windowed, Renderless)
//
//  Parameters:
//              pBaseFilter -- pointer to the base filter
//              mode -- the desired mode
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
HRESULT
SetRenderingMode( IBaseFilter* pBaseFilter, VMRMode mode )
{
    if (!pBaseFilter)
        return E_POINTER;

    IVMRFilterConfig* pFilterConfig;
    HRESULT hr = pBaseFilter->QueryInterface(__uuidof(IVMRFilterConfig),
                                             (LPVOID *)&pFilterConfig);

    if( SUCCEEDED( hr )) 
    {
        hr = pFilterConfig->SetRenderingMode( mode );
        pFilterConfig->Release();
    }

    return hr;
}


//----------------------------------------------------------------------------
//  ConfigureExclusiveMode
//  
//  1. Creates the Exclusive Mode Allocator-Presenter
//  2. Configures the new Allocator-Presenter
//  
//  Parameters:
//              pBaseFilter -- pointer to the VMR filter
//              ppWindowlessControl
//                          --  a pointer that is going to receive the 
//                              windowless control interface
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
HRESULT
ConfigureExclusiveMode( IBaseFilter*            pBaseFilter,            
                        LPDIRECTDRAW7           dd7,
                        LPDIRECTDRAWSURFACE7    primarySurface,
                        DWORD_PTR               userId,
                        HWND                    hwndMain,
                        IVMRWindowlessControl** ppWindowlessControl
                        )
{
    IVMRImagePresenterExclModeConfig* pExclModeConfig;

    if( ! pBaseFilter || ! ppWindowlessControl )
        return E_POINTER;

    HRESULT hr = CoCreateInstance(
                                CLSID_AllocPresenterDDXclMode,
                                NULL,
                                CLSCTX_INPROC_SERVER,
                                IID_IVMRImagePresenterExclModeConfig,
                                (void**)&pExclModeConfig );

    if( SUCCEEDED( hr ) )
    {
        hr = pExclModeConfig->SetXlcModeDDObjAndPrimarySurface(dd7, primarySurface);

        hr = SUCCEEDED(hr) ? pExclModeConfig->SetRenderingPrefs(RenderPrefs_AllowOffscreen|RenderPrefs_AllowOverlays) : hr;

        hr = SUCCEEDED(hr) ? pExclModeConfig->QueryInterface(IID_IVMRWindowlessControl,
                                                            (LPVOID*)ppWindowlessControl) : hr;
        if( SUCCEEDED( hr ) ) 
        {
            hr = (*ppWindowlessControl)->SetVideoClippingWindow(hwndMain);
            // don't release because we are returning this
        }

        IVMRSurfaceAllocator* surfaceAllocator=NULL;
        hr = SUCCEEDED(hr) ? pExclModeConfig->QueryInterface(IID_IVMRSurfaceAllocator, 
                                                            (void**) &surfaceAllocator) : hr;
        if( SUCCEEDED( hr ) )
        {
            hr = SetAllocatorPresenter(pBaseFilter, surfaceAllocator, userId);
            surfaceAllocator->Release();
        }

        pExclModeConfig->Release();
    }

    return hr;
}


//----------------------------------------------------------------------------
//  SetAllocatorPresenter
//  
//  
//  Parameters:
//              baseFilter -- pointer to the VMR filter
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
HRESULT
SetAllocatorPresenter( IBaseFilter*             pBaseFilter,
                       IVMRSurfaceAllocator*    pSurfaceAllocator,
                       DWORD_PTR                dwUserId )
{
    HRESULT hr;
    IVMRSurfaceAllocatorNotify* pNotify;

    if( ! pBaseFilter || ! pSurfaceAllocator )
    {
        return E_POINTER;
    }

    // Here we need to let the filter know that it's supposed to use
    // the surfaceAllocator and let the surfaceAllocator know that
    // it's supposed to notify the filter.
    // Missing one or the other step makes the filter unusable and the 
    // filter graph loads a new one.

    hr = pBaseFilter->QueryInterface(__uuidof(IVMRSurfaceAllocatorNotify), (void**)(&pNotify));
    if( SUCCEEDED( hr ) ) 
    {
        // tell the surface allocator to notify our VMR 
        // and tell VMR to use the surface allocator.

        hr = pSurfaceAllocator->AdviseNotify( pNotify );
        if( SUCCEEDED( hr ) )
        {
            hr = pNotify->AdviseSurfaceAllocator( dwUserId, pSurfaceAllocator );    
        }

        pNotify->Release();
    }

    return hr;
}

//----------------------------------------------------------------------------
//  SetVideoPosition
//
//  This will set the video position to occupy the entire screen
//  
//  Parameters:
//              pWc -- initialized windowless control
//              width of the screen
//              height of the screen
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
void SetVideoPosition(IVMRWindowlessControl *pWc, 
                      DWORD width, DWORD height) 
{ 
    RECT rcSrc, rcDest; //Source and destination rectangles.
    long videoWidth, videoHeight; 

    if (pWc)
    {
        pWc->GetNativeVideoSize(&videoWidth, &videoHeight, NULL, NULL); 
        SetRect(&rcSrc,  0, 0, videoWidth, videoHeight); 
        SetRect(&rcDest, 0, 0, width, height); 

        pWc->SetVideoPosition(&rcSrc, &rcDest); 
    }
}




}

