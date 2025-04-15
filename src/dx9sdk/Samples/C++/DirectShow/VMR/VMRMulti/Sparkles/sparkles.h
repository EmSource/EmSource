//----------------------------------------------------------------------------
//	File:	sparkles.h
//
//	Desc:	DirectShow sample code
//			declaration of CSparkle class
//
//	Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------
#define UPPER 500
#define LOWER 1

#define MIN_SPARKLES		10
#define CUR_SPARKLES		60
#define MAX_SPARKLES		120
#define MIN_FRAME_RATE		10
#define CUR_FRAME_RATE		60
#define MAX_FRAME_RATE		120

extern HWND g_hMainWindow;
extern HINSTANCE g_hMainInstance;

extern UINT		nMaxNumSparkles;
extern UINT		nCurNumSparkles;

extern D3DCOLOR bckColor;

HRESULT App_OneTimeSceneInit();
HRESULT App_InitDeviceObjects( HWND hWnd, LPDIRECT3DDEVICE7 pd3dDevice );
HRESULT App_FrameMove( LPDIRECT3DDEVICE7 pd3dDevice, FLOAT fTimeKey );
HRESULT App_Render( LPDIRECT3DDEVICE7 pd3dDevice );

//----------------------------------------------------------------------------
//	CSparkle
//
//	Implementation of Direct3D background of the video window
//----------------------------------------------------------------------------
class CSparkle 
{

private:
    LPDIRECTDRAWSURFACE7        m_lpRenderTarget;
    CD3DHelper*                 m_pD3DHelper;
    LPDIRECTDRAW7               m_lpDDObj;

public:
 
    CSparkle(LPDIRECTDRAW7 lpDDObj) : 
        m_lpDDObj(lpDDObj), m_pD3DHelper(NULL), m_lpRenderTarget(NULL) {}
    
    HRESULT InitializeSparkle()
    {
        HRESULT hr = S_OK;

        DDSURFACEDESC2 ddsd = {sizeof(DDSURFACEDESC2)};
        m_lpDDObj->GetDisplayMode(&ddsd);

        if(ddsd.ddpfPixelFormat.dwRGBBitCount <= 8)
            return DDERR_INVALIDMODE;

        //
        // Setup a surface description to create a backbuffer. This is an
        // offscreen plain surface with dimensions equal to the current display
        // size.

        // The DDSCAPS_3DDEVICE is needed so we can later query this surface
        // for an IDirect3DDevice interface.
        //
        ddsd.dwFlags        = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_3DDEVICE;
        ddsd.dwWidth = 640;
        ddsd.dwHeight = 480;

        //
        // Create the backbuffer. The most likely reason for failure is running
        // out of video memory. (A more sophisticated app should handle this.)
        //
        hr = m_lpDDObj->CreateSurface(&ddsd, &m_lpRenderTarget, NULL);
        if (hr != DD_OK) {
            return hr;
        }

        m_pD3DHelper = new CD3DHelper(m_lpRenderTarget, &hr);
        if (!m_pD3DHelper || FAILED(hr)) {
            if (!m_pD3DHelper) {
                hr = E_OUTOFMEMORY;
            }
            return hr;
        }

        App_OneTimeSceneInit();
        App_InitDeviceObjects(NULL, m_pD3DHelper->GetD3DDevice());

        return hr;
    }

    HRESULT RenderFrame()
    {
        // Get the relative time, in seconds
        FLOAT fTime = timeGetTime() * 0.001f;

        // FrameMove (animate) the scene
        if (FAILED(App_FrameMove( m_pD3DHelper->GetD3DDevice(), fTime)))
            return E_FAIL;

        //Render the scene
        if (FAILED(App_Render( m_pD3DHelper->GetD3DDevice())))
            return E_FAIL;
        
        return S_OK;
    }

    HRESULT TerminateSparke()
    {

    }

    LPDIRECTDRAWSURFACE7 GetFrame()
    {
        return m_lpRenderTarget;
    }
};   