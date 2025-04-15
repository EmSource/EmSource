//------------------------------------------------------------------------------
// File: CustomUILayer.cpp
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "CustomMixer.h"
#include "CustomUILayer.h"
#include "resource.h"

/******************************Public*Routine******************************\
* CGameUILayer
* constructor
\**************************************************************************/
CGameUILayer::CGameUILayer(LPUNKNOWN pUnk, HRESULT *phr)
    : CUnknown(NAME("GameUILayer for MultiVMR9"), pUnk)
    , m_bInitialized( FALSE )
    , m_bViewing( TRUE )
    , m_pOwner( NULL )
    , m_pTextureButtonResume( NULL )
    , m_pTextureButtonView( NULL )
    , m_pMixer( NULL )
{
    // initialize vertices here
    m_V[0].Pos.x = 300.f;   m_V[0].Pos.y =  -200.f; m_V[0].Pos.z = 0.f;
    m_V[1].Pos.x = 364.f;   m_V[1].Pos.y =  -200.f; m_V[1].Pos.z = 0.f;
    m_V[2].Pos.x = 300.f;   m_V[2].Pos.y =  -264.f; m_V[2].Pos.z = 0.f;
    m_V[3].Pos.x = 364.f;   m_V[3].Pos.y =  -264.f; m_V[3].Pos.z = 0.f;

    m_V[0].tu = 0.f;    m_V[0].tv = 0.f;
    m_V[1].tu = 1.f;    m_V[1].tv = 0.f;
    m_V[2].tu = 0.f;    m_V[2].tv = 1.f;
    m_V[3].tu = 1.f;    m_V[3].tv = 1.f;
}

/******************************Public*Routine******************************\
* ~CGameUILayer
* destructor
\**************************************************************************/
CGameUILayer::~CGameUILayer()
{
    CAutoLock Lock(&m_ObjectLock);
    RELEASE( m_pOwner );
    RELEASE( m_pTextureButtonResume );
    RELEASE( m_pTextureButtonView );
    RELEASE( m_pMixer );
}

///////////////////////// IUnknown /////////////////////////////////////////

/******************************Public*Routine******************************\
* CreateInstance
\**************************************************************************/
CUnknown* CGameUILayer::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
    return new CGameUILayer(pUnk, phr);
}

/******************************Public*Routine******************************\
* NonDelegatingQueryInterface
\**************************************************************************/
STDMETHODIMP
CGameUILayer::NonDelegatingQueryInterface(
    REFIID riid,
    void ** ppv)
{
    HRESULT hr = E_NOINTERFACE;
    *ppv = NULL;

    if (riid == IID_IMultiVMR9UILayer) 
    {
        hr = GetInterface((IMultiVMR9UILayer *)this, ppv);
    }
    else 
    {
        hr = CUnknown::NonDelegatingQueryInterface(riid,ppv);
    }
    return hr;
}

////////////////////////////  IMultiVMR9UILayer ////////////////////////////////
/******************************Public*Routine******************************\
* SetRenderEngineOwner
\**************************************************************************/
STDMETHODIMP
CGameUILayer::SetRenderEngineOwner(
        IMultiVMR9RenderEngine* pRenderEngine)
{
    HRESULT hr = S_OK;
    CAutoLock Lock(&m_ObjectLock);

    try
    {
        RELEASE( m_pOwner );
        if( pRenderEngine )
        {
            m_pOwner = pRenderEngine;
            m_pOwner->AddRef();
        }
    }
    catch( HRESULT hr1)
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* GetRenderEngineOwner
\**************************************************************************/
STDMETHODIMP
CGameUILayer::GetRenderEngineOwner(
        IMultiVMR9RenderEngine** ppRenderEngine)
{
    if( !ppRenderEngine )
    {
        return E_POINTER;
    }
    if( !m_pOwner )
    {
        return VFW_E_NOT_FOUND;
    }

    *ppRenderEngine = m_pOwner;
    (*ppRenderEngine)->AddRef();

    return S_OK;
}

/******************************Public*Routine*****************************\
* Initialize
\**************************************************************************/
STDMETHODIMP
CGameUILayer::Initialize(
                       IDirect3DDevice9 *pDevice)
{
    HRESULT hr = S_OK;

    // load buttons from resources
    if( m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }
    if( !pDevice )
    {
        return E_POINTER;
    }

    try
    {
        CHECK_HR(
            hr = D3DXCreateTextureFromResource( pDevice,
                                                NULL,
                                                MAKEINTRESOURCE( IDB_UIBTN_RESUME ),
                                                &m_pTextureButtonView ),
        DbgMsg("CGameUILayer::Initialize: failed to load texture for the button, hr = 0x%08x", hr));

        CHECK_HR(
            hr = D3DXCreateTextureFromResource( pDevice,
                                                NULL,
                                                MAKEINTRESOURCE( IDB_UIBTN_VIEW ),
                                                &m_pTextureButtonResume ),
        DbgMsg("CGameUILayer::Initialize: failed to load texture for the button, hr = 0x%08x", hr));
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    return hr;
}


/******************************Public*Routine*****************************\
* Render
\**************************************************************************/
STDMETHODIMP
CGameUILayer::Render(
                     IDirect3DDevice9 *pDevice)
{
    HRESULT hr = S_OK;
    IDirect3DStateBlock9 *pState = NULL;
    D3DMATRIX matW;
    D3DXMATRIX matW1;

    if( !pDevice )
    {
        return E_POINTER;
    }

    try
    {
        CHECK_HR(
            hr = pDevice->BeginStateBlock(),
            DbgMsg(""));

        CHECK_HR(
            hr = pDevice->EndStateBlock(&pState),
            DbgMsg(""));

        pDevice->GetTransform( D3DTS_WORLD, &matW);
        D3DXMatrixIdentity( &matW1);
        pDevice->SetTransform( D3DTS_WORLD, &matW1);

        pDevice->SetRenderState( D3DRS_ZENABLE,  D3DZB_FALSE );
        pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
        pDevice->SetRenderState( D3DRS_SRCBLEND,    D3DBLEND_SRCALPHA );
        pDevice->SetRenderState( D3DRS_DESTBLEND,  D3DBLEND_INVSRCALPHA );
        pDevice->SetRenderState( D3DRS_ALPHATESTENABLE,  TRUE );
        pDevice->SetRenderState( D3DRS_ALPHAREF,         0x06 );
        pDevice->SetRenderState( D3DRS_ALPHAFUNC,  D3DCMP_GREATEREQUAL );

        CHECK_HR(
            hr = pDevice->SetRenderState( D3DRS_FILLMODE,   D3DFILL_SOLID ),
            DbgMsg(""));

        CHECK_HR(
            hr = pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 ),
            DbgMsg(""));

        CHECK_HR(
            hr = pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE ),
            DbgMsg(""));

        CHECK_HR(
            hr = pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 ),
            DbgMsg(""));

        CHECK_HR(
            hr = pDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE ),
            DbgMsg(""));

        if( m_bViewing )
        {
            CHECK_HR(
                hr = pDevice->SetTexture(0, m_pTextureButtonResume),
                DbgMsg(""));
        }
        else
        {
            CHECK_HR(
                hr = pDevice->SetTexture(0, m_pTextureButtonView),
                DbgMsg(""));
        }

        CHECK_HR(
            hr = pDevice->SetFVF( m_FVFUILayer ),
            DbgMsg(""));

        CHECK_HR(
            hr = pDevice->DrawPrimitiveUP(  D3DPT_TRIANGLESTRIP,
                                            2,
                                            (LPVOID)(m_V),
                                            sizeof(m_V[0])),
            DbgMsg(""));

        pDevice->SetTransform( D3DTS_WORLD, &matW);

        CHECK_HR(
            hr = pDevice->SetTexture(0, NULL),
            DbgMsg(""));

        CHECK_HR(
            hr = pState->Apply(),
            DbgMsg(""));
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    RELEASE( pState );
    return hr;
}

/******************************Public*Routine*****************************\
* ProcessMessage
\**************************************************************************/
STDMETHODIMP
CGameUILayer::ProcessMessage(
        UINT msg, 
        UINT wParam, 
        LONG lParam
        )
{
    switch( msg )
    {
        case WM_LBUTTONUP:
            {
                HRESULT hr = S_OK;
                int xPos = GET_X_LPARAM(lParam); 
                int yPos = GET_Y_LPARAM(lParam); 

                if( m_pMixer )
                {
                    if( xPos > 720 && xPos < 800 &&
                        yPos > 520 && yPos <600 )
                    {
                        hr = m_pMixer->Animate( !m_bViewing );
                        if( S_OK == hr )
                        {
                            m_bViewing = !m_bViewing;
                        }
                    }
                }
            }
            break;
    }

    return S_OK;
}


/******************************Public*Routine*****************************\
* SetMixer
\**************************************************************************/
HRESULT CGameUILayer::SetMixer( CGameMixer* pMixer )
{
    RELEASE( m_pMixer );

    if( pMixer )
    {
        m_pMixer = pMixer;
        m_pMixer->AddRef();
    }

    return S_OK;
}


