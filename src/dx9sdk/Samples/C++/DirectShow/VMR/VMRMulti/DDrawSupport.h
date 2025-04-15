//----------------------------------------------------------------------------
//  File:   DDrawSupport.cpp
//
//  Desc:   DirectShow sample code
//          Prototype of DDrawObject that provides basic DDraw functionality
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#ifndef DDRAWSUPPORT_HEADER
#define DDRAWSUPPORT_HEADER

#include "D3DHelpers\d3dtextr.h"

// Constants
#define SCRN_BITDEPTH   32

//#define SCRN_WIDTH      640
//#define SCRN_HEIGHT     480


// Macros
#ifndef __INITDDSTRUCT_DEFINED
#define __INITDDSTRUCT_DEFINED
template <typename T>
__inline void INITDDSTRUCT(T& dd)
{
    ZeroMemory(&dd, sizeof(dd));
    dd.dwSize = sizeof(dd);
}
#endif
#ifndef __RELEASE_DEFINED
#define __RELEASE_DEFINED
template<typename T>
__inline void RELEASE( T* &p )
{
    if( p ) {
        p->Release();
        p = NULL;
    }
}
#endif

#ifndef CHECK_HR
    #define CHECK_HR(expr) do { if (FAILED(expr)) __leave; } while(0);
#endif


// Structures
typedef struct Vertex
{
    float x, y, z, rhw;
    D3DCOLOR clr;
    float tu, tv;

} Vertex;

typedef struct VertexFrame
{
    Vertex v[4];

    void SetFrame( RECT r)
    {
        for( int i=0; i<4; i++)
        {
            v[i].z = 0.5f;
            v[i].rhw = 2.0f;
            v[i].clr = RGBA_MAKE(0xff, 0xff, 0xff, 0xff);
        }

        v[0].x = (float)r.left;
        v[0].y = (float)r.top;
        v[0].tu = 0.f;
        v[0].tv = 0.f;
        
        v[1].x = (float)r.left;
        v[1].y = (float)r.bottom;
        v[1].tu = 0.f;
        v[1].tv = 1.f;

        v[2].x = (float)r.right;
        v[2].y = (float)r.top;
        v[2].tu = 1.f;
        v[2].tv = 0.f;

        v[3].x = (float)r.right;
        v[3].y = (float)r.bottom;
        v[3].tu = 1.f;
        v[3].tv = 1.f;
    }
} VertexFrame;


//----------------------------------------------------------------------------
// CD3DHelper
//
// Desc: texture surface to be used in PresentImage of the
//       customized allocator-presenter
//----------------------------------------------------------------------------
class CD3DHelper
{
private:

    CComPtr<IDirectDraw7>			m_pDD;
    CComPtr<IDirect3D7>				m_pD3D;
    CComPtr<IDirect3DDevice7>		m_pD3DDevice;
    CComPtr<IDirectDrawSurface7>	m_lpDDBackBuffer;	// all the rendering is performed on the back buffer
	CComPtr<IDirectDrawSurface7>	m_lpDDMirror;		// when HW is unable of alpha blending, mirror surface is used
    CComPtr<IDirectDrawSurface7>	m_lpDDM32;
    CComPtr<IDirectDrawSurface7>	m_lpDDM16;

    DDSURFACEDESC2              m_ddsdM32;
    DDSURFACEDESC2              m_ddsdM16;

    bool                        m_fPowerOf2;	// true if allocated surfaces are to be of power of 2
    bool                        m_fSquare;		// thre if allocated surfaces are to be square

    VertexFrame * m_pVF;	// vertex buffer for the movie's frame 

	bool IsSurfaceBlendable( DDSURFACEDESC2& ddsd );
	HRESULT MirrorSourceSurface( LPDIRECTDRAWSURFACE7 lpDDS,
								 DDSURFACEDESC2& ddsd );

public:

    CD3DHelper(LPDIRECTDRAWSURFACE7 lpDDSDst, HRESULT* phr);
    ~CD3DHelper();

	HRESULT RenderFrame(	LPDIRECTDRAWSURFACE7 lpDDSSrc, 
							Vertex *pv, 
							RECT rcDest, 
							RECT rcOriginalTarget, 
							BOOL bSelectedChannel );

	HRESULT FrameRect(LPRECT lpDst, D3DCOLOR clr);
	HRESULT FrameRect(FLOAT fLeft, FLOAT fTop, FLOAT fRight, FLOAT fBottom, D3DCOLOR clr, long lPenWidth);
	HRESULT PaintRect(RECT* lpDst, D3DCOLOR clr);

    bool IsPower2() { return m_fPowerOf2;}
    bool IsSquare() { return m_fSquare;}

    LPDIRECTDRAW7 GetDDInterface() 
	{
        return m_pDD;
    }

    LPDIRECT3DDEVICE7 GetD3DDevice() 
	{
        return m_pD3DDevice;
    }

    HRESULT ClearScene(D3DCOLOR clr) 
	{
        return m_pD3DDevice->Clear(0, NULL,D3DCLEAR_TARGET, clr, 1.0f, 0L);
    }

    HRESULT BeginScene() 
	{
        m_pD3DDevice->BeginScene();
        return S_OK;
    }

    HRESULT EndScene() 
	{
        return  m_pD3DDevice->EndScene();
    }

};

#endif
