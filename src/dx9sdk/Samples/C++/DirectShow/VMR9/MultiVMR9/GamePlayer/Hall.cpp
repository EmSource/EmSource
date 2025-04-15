//------------------------------------------------------------------------------
// File: Hall.cpp
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Hall.h"
#include "d3dutil.h"
#include "dxutil.h"
#include "resource.h"

const TCHAR g_achFloorFile[] = TEXT("floor.bmp");
const TCHAR g_achWallFile[]  = TEXT("env2.bmp");

D3DFORMAT* g_pEnvFormat = NULL; // Preferred format for the hall objects

// if D3DFMT_A4R4G4B4 is not supported, we will try one of the following:
D3DFORMAT g_EnvAlternatives[] = 
    {
        D3DFMT_A4R4G4B4,
        D3DFMT_A1R5G5B5,
        D3DFMT_X1R5G5B5,
        D3DFMT_A8B8G8R8,
    };

int g_nEnvAlternatives = sizeof(g_EnvAlternatives) / sizeof(D3DFORMAT);


        //  LB     LT      RT      RB
D3DXMATRIX g_matFloor(
         380.f,  -380.f, -380.f,   380.f,
        2000.f,  2000.f, -2000.f,-2000.f,
         -14.f,   -14.f,  -14.f,   -14.f,
           0.f,     0.f,    0.f,     0.f
        );

    //  LB      LT       RT       RB
D3DXMATRIX g_matWall(
    -380.f,  -380.f,  -380.f,   -380.f,
    2000.f,  2000.f, -2000.f,  -2000.f,
     -14.f,  1000.f,  1000.f,    -14.f,
       0.f,     0.f,     0.f,      0.f
    );


/********************Public*Routine****************************************\
* CHall
* constructor
\**************************************************************************/
CHall::CHall()
    : m_pFloor( NULL )
    , m_pWall( NULL )
    , m_fSpeed( 0.f )
{
}

/********************Public*Routine****************************************\
* ~CHall
* destructor
\**************************************************************************/
CHall::~CHall()
{
    if( m_pFloor )
    {
        delete m_pFloor;
        m_pFloor = NULL;
    }
    if( m_pWall )
    {
        delete m_pWall;
        m_pWall = NULL;
    }
}

/********************Public*Routine****************************************\
* Initialize
* 
\**************************************************************************/
HRESULT CHall::Initialize( IDirect3DDevice9* pDevice)
{
    HRESULT hr = S_OK;
    IDirect3D9* pD3D = NULL;

    if( !pDevice )
    {
        return E_POINTER;
    }

    try
    {
        // decide on the format
        if( !g_pEnvFormat )
        {
            D3DDISPLAYMODE d3dMode;
            
            CHECK_HR(
                pDevice->GetDirect3D( &pD3D ),
                DbgMsg("CHall::Initialize: cannot get IDirect3D9 from the device"));

            CHECK_HR(
                pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3dMode),
                DbgMsg("CHall::Initialize: cannot get adapter display mode"));


            for( int i=0; i<g_nEnvAlternatives; i++)
            {
                hr = pD3D->CheckDeviceFormat(   D3DADAPTER_DEFAULT,
                                                D3DDEVTYPE_HAL,
                                                d3dMode.Format,
                                                0,
                                                D3DRTYPE_TEXTURE,
                                                g_EnvAlternatives[i] );
                if( D3D_OK == hr ) // we found the format
                {
                    g_pEnvFormat = &(g_EnvAlternatives[i]);
                    break;
                }
            }// for
            CHECK_HR(
                g_pEnvFormat ? S_OK : E_FAIL,
                DbgMsg("CHall::Initialize: selected device and/or display mode does not allow to initialize D3D environment correctly"));
        }

        if( m_pFloor )
        {
            delete m_pFloor;
            m_pFloor = NULL;
        }
        if( m_pWall )
        {
            delete m_pWall;
            m_pWall = NULL;
        }

        m_pFloor = new CHall::CPlane(
                                    pDevice,
                                    (TCHAR*)g_achFloorFile,
                                    MAKEINTRESOURCE( IDB_BITMAP_FLOOR),
                                    10.f, 
                                    1.f, 
                                    g_matFloor,
                                    0.25f,
                                    &hr);
        CHECK_HR(
            FAILED(hr) ? hr : ( (!m_pFloor) ? E_OUTOFMEMORY : S_OK ),
            DbgMsg("CHall::Initialize: failed in new CHall::CPlane() for the floor"));

        m_pWall = new CHall::CPlane(
                                    pDevice,
                                    (TCHAR*)g_achWallFile,
                                    MAKEINTRESOURCE( IDB_BITMAP_WALL),
                                    10.f, 
                                    1.f, 
                                    g_matWall, 
                                    0.25f,
                                    &hr);
        CHECK_HR(
            FAILED(hr) ? hr : ( (!m_pFloor) ? E_OUTOFMEMORY : S_OK ),
            DbgMsg("CHall::Initialize: failed in new CHall::CPlane() for the wall"));
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    RELEASE( pD3D );

    return hr;
}

/********************Public*Routine****************************************\
* RestoreDeviceObjects
* 
\**************************************************************************/
HRESULT CHall::RestoreDeviceObjects( IDirect3DDevice9* pDevice)
{
    HRESULT hr = S_OK;
    if( !pDevice )
    {
        return E_POINTER;
    }

    try
    {
        CHECK_HR(
            hr = pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DRS_ALPHABLENDENABLE/TRUE, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DRS_SRCBLEND/D3DBLEND_SRCALPHA, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DRS_DESTBLEND/D3DBLEND_INVSRCALPHA, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE ),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DRS_DITHERENABLE/TRUE, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState( D3DRS_AMBIENT, 0xFFFFFFFF ),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DRS_AMBIENT/0xFFFFFFFF, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState(D3DRS_LIGHTING, FALSE),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DRS_LIGHTING/FALSE, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DRS_CULLMODE/D3DCULL_NONE, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU ,D3DTADDRESS_WRAP),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DSAMP_ADDRESSU/D3DTADDRESS_WRAP, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV ,D3DTADDRESS_WRAP),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DSAMP_ADDRESSV/D3DTADDRESS_WRAP, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DTSS_ALPHAOP/D3DTOP_SELECTARG1, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DTSS_ALPHAARG1/D3DTA_DIFFUSE, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetFVF(g_FVFHall),
            DbgMsg("CHall::RestoreDeviceObjects failed to set SetFVF, hr = 0x%08x", hr));

    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    return hr;
}

/********************Public*Routine****************************************\
* Compose
* 
\**************************************************************************/
HRESULT CHall::Compose( DWORD t )
{
    HRESULT hr = S_OK;
    HRESULT hr1 = S_OK;
    HRESULT hr2 = S_OK;

    if( m_pFloor )
    {
        hr1 = m_pFloor->Compose( t );
    }
    if( m_pWall )
    {
        hr2 = m_pWall->Compose( t );
    }

    hr = FAILED(hr1) ? hr1 : ( FAILED(hr2) ? hr2 : S_OK ); 
    return hr;
}


/********************Public*Routine****************************************\
* Render
* 
\**************************************************************************/
HRESULT CHall::Render( IDirect3DDevice9* pDevice)
{
    HRESULT hr = S_OK;

    if( !pDevice )
    {
        return E_POINTER;
    }

    try
    {
        CHECK_HR(
            hr = RestoreDeviceObjects( pDevice ),
            DbgMsg("CHall::Render: failed in RestoreDeviceObjects",hr));

        if( m_pFloor )
        {
            CHECK_HR(
                hr = m_pFloor->Render( pDevice ),
                DbgMsg("CHall::Render: failed to render the floor",hr));
        }
        if( m_pWall )
        {
            CHECK_HR(
                hr = m_pWall->Render( pDevice ),
                DbgMsg("CHall::Render: failed to render the wall",hr));
        }
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    return hr;
}

/********************Public*Routine****************************************\
* SetSpeed
* 
\**************************************************************************/
HRESULT CHall::SetSpeed( float fSpeed )
{
    m_fSpeed = fSpeed;

    if( m_pFloor )
    {
        m_pFloor->SetSpeed( m_fSpeed );
    }
    if( m_pWall )
    {
        m_pWall->SetSpeed( m_fSpeed );
    }
    return S_OK;
}

///////////////////////  CPlane //////////////////////////////////////////////

/********************Public*Routine****************************************\
* CPlane
* 
\**************************************************************************/
CHall::CPlane::CPlane(
                  IDirect3DDevice9* pDevice,
                  TCHAR *achName, 
                  LPCTSTR lpResourceName,
                  float fU, 
                  float fV, 
                  D3DXMATRIX& M,
                  float a,
                  HRESULT *phr)
    : m_du( 0.f)
    , m_fU( fU )
    , m_fV( fV )
    , m_fSpeed( 0.f )
    , m_pTexture( NULL )
{
    HRESULT hr = S_OK;

    TCHAR achTexturePath[MAX_PATH];

    D3DXVECTOR3 vLB( M(0,0), M(1,0), M(2,0));
    D3DXVECTOR3 vLT( M(0,1), M(1,1), M(2,1));
    D3DXVECTOR3 vRT( M(0,2), M(1,2), M(2,2));
    D3DXVECTOR3 vRB( M(0,3), M(1,3), M(2,3));
    D3DXVECTOR3 V;

    try
    {
        if( !achName )
            throw E_POINTER;

        hr = FindMediaFile( achTexturePath,
            sizeof(TCHAR)*MAX_PATH,
            achName,
            lpResourceName,
            RT_BITMAP);
        if( FAILED(hr))
        {
            TCHAR achMsg[MAX_PATH];
            _stprintf( achMsg, TEXT("Cannot find media file '%s'. ")
                       TEXT("Make sure you have valid installation of DirectX SDK"), 
                       achName);
            ::MessageBox( NULL, achMsg, TEXT("Error"), MB_OK);
            if( phr )
            {
                *phr = hr;
                return;
            }
        }

        if( !pDevice )
            throw E_POINTER;

        if( a<0.01f || a>0.5f )
            throw E_INVALIDARG;

        D3DXVECTOR3 vecDiff = vLB - vLT;
        if( D3DXVec3LengthSq( &vecDiff )< 0.001f )
            throw E_INVALIDARG;

        if( m_fU < 0.001f || m_fV < 0.001f )
            throw E_INVALIDARG;

        CHECK_HR(
            hr = DXUtil_FindMediaFileCb( achTexturePath, sizeof(TCHAR)*MAX_PATH, achName ),
            DbgMsg("CPlane::CPlane: cannot find bitmap file %s in SDK media folder", achTexturePath));

        // load texture
        ASSERT( g_pEnvFormat );
        CHECK_HR(
            hr = D3DUtil_CreateTexture( pDevice, achTexturePath, &m_pTexture, *g_pEnvFormat ),
            DbgMsg("CPlane::CPlane: failed to create the texture, hr = 0x%08x", hr));

        // initialize geometry

        // POSITION

        // corners
        
        memcpy( &(m_V[0].Pos), &vLB, sizeof(D3DVECTOR));
        memcpy( &(m_V[1].Pos), &vLT, sizeof(D3DVECTOR));
        memcpy( &(m_V[2].Pos), &vRB, sizeof(D3DVECTOR));
        memcpy( &(m_V[3].Pos), &vRT, sizeof(D3DVECTOR));

        // TEXTURE COORD
        m_V[0].tu = 0.f;    m_V[0].tv = fV;
        m_V[1].tu = 0.f;    m_V[1].tv = 0.f;
        m_V[2].tu =  fU;    m_V[2].tv = fV;
        m_V[3].tu =  fU;    m_V[3].tv = 0.f;

        // corners are transparent, middle vertices are opaque
        m_V[0].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, 0xFF);
        m_V[1].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, 0xFF);
        m_V[2].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, 0xFF);
        m_V[3].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, 0xFF);

    }
    catch( HRESULT hr1 )
    {
        RELEASE( m_pTexture );
        hr = hr1;
    }

    if( phr )
    {
        *phr = hr;
    }
}

/********************Public*Routine****************************************\
* ~CPlane
* 
\**************************************************************************/
CHall::CPlane::~CPlane()
{
    RELEASE( m_pTexture );
}

/********************Public*Routine****************************************\
* SetSpeed
* 
\**************************************************************************/
HRESULT CHall::CPlane::SetSpeed( float S )
{
    D3DXVECTOR3 vW = D3DXVECTOR3( m_V[3].Pos ) - D3DXVECTOR3( m_V[1].Pos );

    float W = D3DXVec3Length( &vW );

    if( W<0.001f )
    {
        return E_UNEXPECTED;
    }
    m_fSpeed = m_fU * S / W; // speed in texture mapped U,V coordinates
    return S_OK;
}
/********************Public*Routine****************************************\
* Compose
* 
\**************************************************************************/
HRESULT CHall::CPlane::Compose( DWORD t )
{
    m_du = m_fSpeed * t - (int)( m_fSpeed * t / m_fU) * m_fU;
    return S_OK;
}

/********************Public*Routine****************************************\
* Render
* 
\**************************************************************************/
HRESULT CHall::CPlane::Render( IDirect3DDevice9* pDevice )
{
    HRESULT hr = S_OK;
    int i;

    if( !pDevice )
    {
        return E_POINTER;
    }

    try
    {
        CHECK_HR(
            hr = pDevice->SetTexture(0, m_pTexture),
            DbgMsg("CPlane::Render: failed in SetTexture, hr = 0x%08x", hr));

        for( i=0; i<4; i++)
        {
            m_V[i].tu += m_du;
        }

        CHECK_HR(
            hr = pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
                                          2,
                                          (LPVOID)(m_V),
                                          sizeof(m_V[0])),
            DbgMsg("CPlane::Render: failed in DrawPrimitiveUP, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetTexture(0, NULL),
            DbgMsg("CPlane::Render: failed in SetTexture(NULL), hr = 0x%08x", hr));

        for( i=0; i<4; i++)
        {
            m_V[i].tu -= m_du;
        }
    }
    catch( HRESULT hr1)
    {
        hr = hr1;
    }

    return hr;
}


