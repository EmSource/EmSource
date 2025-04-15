//-----------------------------------------------------------------------------
// File: Textures.h
//
// Desc: DirectShow sample code - header file for DirectShow/Direct3D8 video 
//       texturing
//       
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------


#include <d3dx8.h>
#include <windows.h>
#include <mmsystem.h>
#include <atlbase.h>
#include <stdio.h>

#include <d3d8types.h>
#include <dshow.h>

//-----------------------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------------------
HRESULT InitDShowTextureRenderer();

void CleanupD3D(void);
void CleanupDShow(void);
void Msg(TCHAR *szFormat, ...);

HRESULT Render(HWND hWnd);
HRESULT CaptureVideo(IBaseFilter *pRenderer);
HRESULT FindCaptureDevice(IBaseFilter ** ppSrcFilter);
HRESULT ReconnectDShowRenderer();

HRESULT AddToROT(IUnknown *pUnkGraph); 
void RemoveFromROT(void);

//-----------------------------------------------------------------------------
// Direct3D global variables
//-----------------------------------------------------------------------------
extern LPDIRECT3D8             g_pD3D;		 // Used to create the D3DDevice
extern LPDIRECT3DDEVICE8       g_pd3dDevice; // Our rendering device
extern LPDIRECT3DVERTEXBUFFER8 g_pVB;		 // Buffer to hold vertices
extern LPDIRECT3DTEXTURE8      g_pTexture;   // Our texture

extern ICaptureGraphBuilder2 * g_pCapture;
extern bool g_bDeviceLost;


//-----------------------------------------------------------------------------
// Helper macros
//-----------------------------------------------------------------------------
#define SAFE_RELEASE(x) { if (x) {(x)->Release(); x = NULL;}; }

