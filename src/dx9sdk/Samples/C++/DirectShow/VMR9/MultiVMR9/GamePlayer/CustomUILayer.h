//------------------------------------------------------------------------------
// File: CustomUILayer.h
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once

static const DWORD m_FVFUILayer = D3DFVF_XYZ | D3DFVF_TEX1;

/******************************Public*Routine******************************\
* class CGameUILayer
*
* Customized version of IMultiVMR9UILayer
\**************************************************************************/
class CGameUILayer :
    public CUnknown,
    public IMultiVMR9UILayer
{
public:
    CGameUILayer(LPUNKNOWN pUnk, HRESULT *phr);
    virtual ~CGameUILayer();

    // IUnknown implementation
    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);
    static CUnknown *CreateInstance(LPUNKNOWN, HRESULT *);

    // IMultiVMR9UILayer implementation
    STDMETHOD(Initialize)(
        IDirect3DDevice9* pDevice
        );

    STDMETHOD(ProcessMessage)(
        UINT msg, 
        UINT wParam, 
        LONG lParam
        );

    STDMETHOD(Render)(
        IDirect3DDevice9 *pDevice
        );

    // method is called by the render engine during IMultiVMR9RenderEngine::SetUILayer
    STDMETHOD(SetRenderEngineOwner)(
        IMultiVMR9RenderEngine* pRenderEngine
        );

    // obtain pointer to IMultiVMR9RenderEngine that owns this UI layer
    STDMETHOD(GetRenderEngineOwner)(
        IMultiVMR9RenderEngine** ppRenderEngine
        );

    HRESULT SetMixer( CGameMixer* pMixer );
    // private methods
private:

private:
    struct Vertex
    {
        D3DVECTOR Pos;
        float tu;
        float tv;
    };

    // data
    CCritSec                    m_ObjectLock;       // this object has to be thread-safe
    BOOL                        m_bInitialized;
    IMultiVMR9RenderEngine*     m_pOwner;
    IDirect3DTexture9*          m_pTextureButtonResume;
    IDirect3DTexture9*          m_pTextureButtonView;
    CGameMixer*                 m_pMixer;
    BOOL                        m_bViewing;
    struct Vertex               m_V[4];
};

