//------------------------------------------------------------------------------
// File: DShowUtils.h
//
// Desc: DirectShow sample code - a simple full screen video playback sample.
//       Using the Windows XP Video Mixing Renderer, a video is played back in
//       a full screen exclusive mode.
//      
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#if !defined(AFX_DSHOWUTILS_H__E79EFD45_7CD5_4CF8_9F8E_EE4BAD187EBF__INCLUDED_)
#define AFX_DSHOWUTILS_H__E79EFD45_7CD5_4CF8_9F8E_EE4BAD187EBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace DShowUtils {

//----------------------------------------------------------------------------
//  VerifyVMR
// 
//  Verifies that VMR COM Objects exist on the system
//
//  Returns: false if the objects are not instanciatable
//----------------------------------------------------------------------------
BOOL 
VerifyVMR(void);

//----------------------------------------------------------------------------
//  OpenMediaFile
// 
//  Opens a movie file
//
//  Parameters:
//          ownerWindow
//          pGB - pointer to an initialized graphBuilder interface
//          openedFileName 
//                      - the file name that has been opened by the user
//----------------------------------------------------------------------------
HRESULT
OpenMediaFile(
            HWND            hwndOwner,
            IGraphBuilder*  pGB,
            LPTSTR          openedFileName
    );

//----------------------------------------------------------------------------
//  AddVmrToFilterGraph
// 
//  creates VMR filter and adds to to the filter graph
//
//  Parameters:
//              pGraph - filter graph
//              ppBaseFilter - out parameter - the created base filter
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
HRESULT
AddVmrToFilterGraph(IFilterGraph* pGraph, IBaseFilter** ppBaseFilter);

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
SetRenderingMode( IBaseFilter* pBaseFilter, VMRMode mode );

//----------------------------------------------------------------------------
//  ConfigureExclusiveMode
//  
//  1. Creates the Exclusive Mode Allocator-Presenter
//  2. Configures the new Allocator-Presenter
//  
//  Parameters:
//              baseFilter -- pointer to the VMR filter
//              windowlessControl
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
                        );

//----------------------------------------------------------------------------
//  SetAllocatorPresenter
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
HRESULT
SetAllocatorPresenter(  IBaseFilter*            pBaseFilter,
                        IVMRSurfaceAllocator*   pSurfaceAllocator,
                        DWORD_PTR               userId
                        );

//----------------------------------------------------------------------------
//  INITDDSTRUCT
//  
//  Properly initializes direct draw struct
//  
//  Parameters:
//      dd -- directdraw struct
//
//  Return: void
//----------------------------------------------------------------------------
template <typename T>
inline void INITDDSTRUCT(T& dd)
{
    ZeroMemory(&dd, sizeof(dd));
    dd.dwSize = sizeof(dd);
}


//----------------------------------------------------------------------------
//  SetVideoPosition
//
//  This will set the video position to occupy the entire screen
//  
//  Parameters:
//              pWc -- initialized windowless control
//              height of the screen
//              width of the screen
//
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
void SetVideoPosition(IVMRWindowlessControl *pWc, 
                      DWORD width, DWORD height);

}


#endif // !defined(AFX_DSHOWUTILS_H__E79EFD45_7CD5_4CF8_9F8E_EE4BAD187EBF__INCLUDED_)
