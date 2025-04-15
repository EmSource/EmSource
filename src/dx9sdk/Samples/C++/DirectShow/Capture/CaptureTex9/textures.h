//-----------------------------------------------------------------------------
// File: Textures.h
//
// Desc: DirectShow sample code - header file for DirectShow/Direct3D9 video 
//       texturing
//       
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------


#include <d3dx9.h>
#include <windows.h>
#include <mmsystem.h>
#include <atlbase.h>
#include <stdio.h>
#include <Streams.h>

#include <d3d9types.h>
#include <dshow.h>

//-----------------------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------------------
HRESULT InitDShowTextureRenderer();

void CheckMovieStatus(void);
void CleanupDShow(void);
void Msg(TCHAR *szFormat, ...);

HRESULT CaptureVideo(IBaseFilter *pRenderer);
HRESULT FindCaptureDevice(IBaseFilter ** ppSrcFilter);

HRESULT AddToROT(IUnknown *pUnkGraph); 
void RemoveFromROT(void);


class CCustomPresentation
{
public:

    CCustomPresentation( );
    ~CCustomPresentation();

    HRESULT Initialize();
    HRESULT Render();
    void SetColor( D3DCOLOR color );
    IDirect3DDevice9 * GetDevice();

    HRESULT SetMediaFormat( GUID subtype);
    HRESULT CreateTexture( UINT Width, UINT Height, D3DFORMAT format);

    HRESULT BltToTexture(IDirect3DSurface9 *lpSurf, UINT Width, UINT Height);
    HRESULT CopyMediaSample( IMediaSample *pSample, LONG lSamplePitch );

    HWND    m_hwnd;         // video window

private:
    // methods
    void Cleanup(void);

    // Direct3D related
    HRESULT InitD3D();
    HRESULT InitGeometry();
    HRESULT SetupMatrices();
    HRESULT SetupLights();
    HRESULT CalculateVertices();
    
    // DirectShow related
    HRESULT InitDShowTextureRenderer();
    HRESULT CaptureVideo(IBaseFilter *pRenderer);
    HRESULT FindCaptureDevice(IBaseFilter ** ppSrcFilter);
    void CheckMovieStatus(void);

    // DirectShow debug
#ifdef REGISTER_FILTERGRAPH
    HRESULT AddToROT(IUnknown *pUnkGraph);
    void RemoveFromROT(void);
#endif


    // data
    CCritSec m_cs;
    CComPtr<IDirect3D9>             m_pD3D;         // Used to create the D3DDevice
    CComPtr<IDirect3DDevice9>       m_pd3dDevice;   // Our rendering device
    CComPtr<IDirect3DVertexBuffer9> m_pVB;          // Buffer to hold vertices
    CComPtr<IDirect3DTexture9>      m_pTexture;     // Our texture

    CComPtr<ICaptureGraphBuilder2>  m_pCapture;     // Helps to render capture graphs
    CComPtr<IGraphBuilder>          m_pGB;          // GraphBuilder
    CComPtr<IMediaControl>          m_pMC;          // Media Control
    CComPtr<IMediaEvent>            m_pME;          // Media Event

    FLOAT                   m_HAR;          // ratio of allocated width for m_pTexture to the 
                                            // actual width of the image it holds
    FLOAT                   m_VAR;          // ratio of allocated height for m_pTexture to the 
                                            // actual height of the image it holds

    UINT                    m_Width;        // actual image size
    UINT                    m_Height;

    D3DFORMAT               m_TextureFormat; // format of the texture we draw

    DWORD                   m_dwStartTime;  // start time for animation, 
                                            // animation current time = timeGetTime() - m_dwStartTime;

    D3DCOLOR                m_d3dcolorBackground; // background color

    // some constants

    DWORD m_dwROTReg;                       // id for ROT, allows to snap graph in the graphinfo
};
