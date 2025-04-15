//------------------------------------------------------------------------------
// File: CustomMixer.h
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once

#include "Hall.h"

#include "D3DFont.h"

#include <list>
using namespace std;

class CGameMixer;

static const DWORD g_FVFframe = D3DFVF_XYZ | D3DFVF_DIFFUSE;
static const DWORD g_FVFMixer = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

/******************************Public*Routine******************************\
* class CGameMixer
*
* Customized version of IMultiVMR9MixerControl
\**************************************************************************/
class CGameMixer:
    public CUnknown,
    public IMultiVMR9MixerControl
{
public:
    CGameMixer(LPUNKNOWN pUnk, HRESULT *phr);
    virtual ~CGameMixer();

    // IUnknown implementation
    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);
    static CUnknown *CreateInstance(LPUNKNOWN, HRESULT *);

    // IMultiVMR9MixerControl implementation

    // IMultiVMR9MixerControl: methods we override
    STDMETHOD(Compose)(
        void* lpParam
        );

    STDMETHOD(Render)(
        IDirect3DDevice9 *pDevice,
        void* lpParam
        );

    STDMETHOD(AddVideoSource)(
        DWORD_PTR dwID,
        LONG lImageWidth,
        LONG lImageHeight,
        LONG lTextureWidth,
        LONG lTextureHeight
        );

    STDMETHOD(DeleteVideoSource)(
        DWORD_PTR dwID
        );

    STDMETHOD(SetRenderEngineOwner)(
        IMultiVMR9RenderEngine* pRenderEngine
        );

    STDMETHOD(GetRenderEngineOwner)(
        IMultiVMR9RenderEngine** ppRenderEngine
        );

    STDMETHOD(Initialize)(
        IDirect3DDevice9 *pDevice
        );

    // IMultiVMR9MixerControl: methods we do not implement (i.e. we do not need)
    STDMETHOD(GetOutputRect)(
        DWORD_PTR dwID,
        NORMALIZEDRECT* lpNormRect
        )
    { return E_NOTIMPL; }

    STDMETHOD(GetIdealOutputRect)(
        DWORD_PTR dwID,
        DWORD dwWidth,
        DWORD dwHeight,
        NORMALIZEDRECT* lpNormRect
        )
    { return E_NOTIMPL; }

    STDMETHOD(SetOutputRect)(
        DWORD_PTR dwID,
        NORMALIZEDRECT* lpNormRect
        )
    { return E_NOTIMPL; }


    STDMETHOD(GetZOrder)(
        DWORD_PTR dwID, 
        DWORD *pdwZ
        )
    { return E_NOTIMPL; }


    STDMETHOD(SetZOrder)(
        DWORD_PTR dwID, 
        DWORD pdwZ
        )
    { return E_NOTIMPL; }


    STDMETHOD(GetBackgroundColor)(
        COLORREF* pColor
        )
    { return E_NOTIMPL; }


    STDMETHOD(SetBackgroundColor)(
        COLORREF Color
        )
    { return E_NOTIMPL; }

    STDMETHOD(GetAlpha)(
        DWORD_PTR dwID, 
        float* pAlpha
        )
    { return E_NOTIMPL; }

    STDMETHOD(SetAlpha)(
        DWORD_PTR dwID, 
        float Alpha
        )
    { return E_NOTIMPL; }

    // class-specific public methods

    HRESULT RestoreDeviceObjects( IDirect3DDevice9 *pDevice );
    HRESULT SetWorldMatrix( D3DXMATRIX& M );
    HRESULT Animate( BOOL bAnimate);

private:
    // subclasses
        class CMovie
        {
        public:
            CMovie( DWORD_PTR dwID, 
                    LONG lImageWidth, 
                    LONG lImageHeight, 
                    LONG lTextureWidth, 
                    LONG lTextureHeight);
            // data
            DWORD_PTR       m_dwID;
            float           m_fY; 
            float           m_fZ;
            float           m_fU;
            float           m_fV;
        };

        class CFrame
        {
        public:
            CFrame( );
            HRESULT Calculate( int n, D3DVECTOR& v0, CMovie* pMovie );
            HRESULT CalculateInFocus( CMovie* pMovie );
            HRESULT Render( 
                IDirect3DDevice9 *pDevice, 
                IDirect3DTexture9* pTexture);
            void FlipToEnd( int N);
            void MoveY( float Shift );

            struct SpotVertex
            {
                D3DVECTOR Pos;
            };

            struct Vertex
            {
                D3DVECTOR Pos;
                D3DCOLOR  color;
                float     tu;
                float     tv;
            };

            struct FrameVertex
            {
                D3DVECTOR Pos;
                D3DCOLOR  color;
            };

            // data
            DWORD_PTR           m_dwID;
            struct SpotVertex   m_S[4];
            struct Vertex       m_V[4];
            struct FrameVertex  m_F[10];
        };// class CFrame

private:
    // class-specific private methods
        void Clean_();

    // data
public:

    private:
    CCritSec            m_ObjectLock;       // this object has to be thread-safe
    BOOL                m_bAnimate;
    CD3DFont*           m_pFont;
    BOOL                m_bInitialized;
    CHall               m_hall;
    CCharacter          m_character;
    CFrame              m_ActiveMovieFrame;
    CFrame              m_Frames[8];
    list<CMovie*>       m_listMovies;
    CMovie*             m_pActiveMovie;
    float               m_fSpeed;
    DWORD               m_dwPrevTick;
    int                 m_Left;

    IMultiVMR9RenderEngine* m_pOwner;

    D3DXMATRIX       m_matView;
    D3DXMATRIX       m_matWorld;
    D3DXMATRIX       m_matProj;
};

