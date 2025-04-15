//------------------------------------------------------------------------------
// File: VmrGlobals.h
//
// Desc: DirectShow sample code - a simple full screen video playback sample.
//       Using the Windows XP Video Mixing Renderer, a video is played back in
//       a full screen exclusive mode.
//      
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#if !defined(AFX_VMRGLOBALS_H__7A339B0A_86D2_4B65_B371_8914BCEE37FC__INCLUDED_)
#define AFX_VMRGLOBALS_H__7A339B0A_86D2_4B65_B371_8914BCEE37FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// VMR objects
extern IFilterGraph*            g_pFilterGraph;
extern IGraphBuilder*           g_pGraphBuilder;
extern IBaseFilter*             g_pVmr;

// DirectDraw objects needed for exclusive mode
extern LPDIRECTDRAW7            g_dd7;
extern LPDIRECTDRAWSURFACE7     g_primarySurface;

//----------------------------------------------------------------------------
//  CreateVMRGlobals
// 
//  creates VMR Globals (look above
//
//  Parameters:
//
//  Return: true if success 
//----------------------------------------------------------------------------
BOOL 
CreateVMRGlobals();

//----------------------------------------------------------------------------
//  ReleaseVMRGlobals
// 
//  Releases the global VMR variables
//  calls ReleaseDDObjects()
//
//  Parameters:
//
//  Return: 
//----------------------------------------------------------------------------
void
ReleaseVMRGlobals();

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
//  Return: S_OK or HRESULT of the failed operation
//----------------------------------------------------------------------------
HRESULT 
CreateDDObjects(HWND hwnd, DWORD screenWidth, DWORD screenHeight, DWORD bitDepth);

//----------------------------------------------------------------------------
//  Release DD objects
// 
//  Releases the global VMR variables
//
//  Parameters:
//
//  Return: 
//----------------------------------------------------------------------------
void
ReleaseDDObjects();


#endif // !defined(AFX_VMRGLOBALS_H__7A339B0A_86D2_4B65_B371_8914BCEE37FC__INCLUDED_)
