//-----------------------------------------------------------------------------
// File: 3DModel.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"



//-----------------------------------------------------------------------------
// Name: C3DModel()
// Desc:
//-----------------------------------------------------------------------------
C3DModel::C3DModel() 
{
    m_pMesh = NULL;

    m_vBoundingMax = D3DXVECTOR3(0,0,0);
    m_vBoundingMin = D3DXVECTOR3(0,0,0);
    m_vCenter      = D3DXVECTOR3(0,0,0);
    m_fRadius      = 0.0f;
    m_dwNumFaces   = 0;
    m_pBoundingVB  = NULL;
}




//-----------------------------------------------------------------------------
// Name: C3DModel()
// Desc:
//-----------------------------------------------------------------------------
C3DModel::~C3DModel()
{
    FinalCleanup();
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DModel::OneTimeSceneInit()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DModel::InitDeviceObjects( TCHAR* strModelName, const BOOL bCreateTest, float fBoundingScale ) 
{
    HRESULT hr;

    m_pMesh = new CD3DMesh();
    if( NULL == m_pMesh )
        return E_OUTOFMEMORY;

    if( bCreateTest ) 
    {
        ID3DXMesh* pD3DXMesh; 
        D3DXCreateSphere( g_pd3dDevice, 1.0f, 16, 16, &pD3DXMesh, NULL );
        m_pMesh->m_pSysMemMesh = pD3DXMesh;

        m_pMesh->m_dwNumMaterials = 1;
        m_pMesh->m_pMaterials = new D3DMATERIAL9[1];
        if( NULL == m_pMesh->m_pMaterials )
            return E_OUTOFMEMORY;
        D3DUtil_InitMaterial( m_pMesh->m_pMaterials[0], 1.0f, 0.0f, 0.0f );
        m_pMesh->m_pTextures  = new LPDIRECT3DTEXTURE9[1];
        if( NULL == m_pMesh->m_pTextures )
            return E_OUTOFMEMORY;
        m_pMesh->m_pTextures[0] = NULL;
    }
    else
    {
        if( FAILED( hr = m_pMesh->Create( g_pd3dDevice, strModelName ) ) )
            return hr;
    }

    // Fix the m_pMesh->m_pMaterials[i].Ambient since the .x file doesn't update this value
    if( m_pMesh )
    {
        for( DWORD i=0; i<m_pMesh->m_dwNumMaterials; i++ )
            m_pMesh->m_pMaterials[i].Ambient = m_pMesh->m_pMaterials[i].Diffuse;
    }

    if( m_pMesh->m_pSysMemMesh )
    {
        m_dwNumFaces = m_pMesh->m_pSysMemMesh->GetNumFaces();

        BYTE* pData = NULL;
        if( SUCCEEDED( m_pMesh->m_pSysMemMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**) &pData ) ) )
        {           
            DWORD dwStride = D3DXGetFVFVertexSize( m_pMesh->m_pSysMemMesh->GetFVF() );
            D3DXComputeBoundingSphere( (D3DXVECTOR3*)pData, m_pMesh->m_pSysMemMesh->GetNumVertices(), 
                                       dwStride, 
                                       &m_vCenter, &m_fRadius );

            D3DXComputeBoundingBox( (D3DXVECTOR3*)pData, m_pMesh->m_pSysMemMesh->GetNumVertices(), 
                                    dwStride, 
                                    &m_vBoundingMin, &m_vBoundingMax );
            
            float fLargest = max(max(m_vBoundingMax.x,m_vBoundingMax.y),m_vBoundingMax.z);
            fLargest *= fBoundingScale;
            m_vBoundingMin = D3DXVECTOR3(-fLargest,-fLargest,-fLargest);
            m_vBoundingMax = D3DXVECTOR3(fLargest,fLargest,fLargest);

            m_pMesh->m_pSysMemMesh->UnlockVertexBuffer();

            m_vBoundingVertex[0] = D3DXVECTOR3( m_vBoundingMin.x, m_vBoundingMin.y, m_vBoundingMin.z ); // xyz
            m_vBoundingVertex[1] = D3DXVECTOR3( m_vBoundingMax.x, m_vBoundingMin.y, m_vBoundingMin.z ); // Xyz
            m_vBoundingVertex[2] = D3DXVECTOR3( m_vBoundingMin.x, m_vBoundingMax.y, m_vBoundingMin.z ); // xYz
            m_vBoundingVertex[3] = D3DXVECTOR3( m_vBoundingMax.x, m_vBoundingMax.y, m_vBoundingMin.z ); // XYz
            m_vBoundingVertex[4] = D3DXVECTOR3( m_vBoundingMin.x, m_vBoundingMin.y, m_vBoundingMax.z ); // xyZ
            m_vBoundingVertex[5] = D3DXVECTOR3( m_vBoundingMax.x, m_vBoundingMin.y, m_vBoundingMax.z ); // XyZ
            m_vBoundingVertex[6] = D3DXVECTOR3( m_vBoundingMin.x, m_vBoundingMax.y, m_vBoundingMax.z ); // xYZ
            m_vBoundingVertex[7] = D3DXVECTOR3( m_vBoundingMax.x, m_vBoundingMax.y, m_vBoundingMax.z ); // XYZ
        }

        hr = g_pd3dDevice->CreateVertexBuffer( 24 * sizeof(LINELIST_VERTEX),
                                            D3DUSAGE_WRITEONLY,
                                            LINELIST_FVF, D3DPOOL_MANAGED,
                                            &m_pBoundingVB, NULL );
        if( SUCCEEDED(hr) )
        {
            LINELIST_VERTEX* pVertexBuffer = NULL;
            hr = m_pBoundingVB->Lock( 0, 0, (void**) &pVertexBuffer, 0 );
            if( SUCCEEDED(hr) )
            {
                DWORD dw[24] = { 0,1, 2,3, 0,2, 1,3, 4,5, 6,7, 4,6, 5,7, 0,4, 2,6, 1,5, 3,7 };

                for( int i=0; i<24; i++ )
                {
                    pVertexBuffer->p = m_vBoundingVertex[ dw[i] ];
                    pVertexBuffer->c = 0xFFFFFFFF;
                    pVertexBuffer++;
                }

                m_pBoundingVB->Unlock(); 
            }
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DModel::RestoreDeviceObjects()
{
    if( m_pMesh )
        return m_pMesh->RestoreDeviceObjects( g_pd3dDevice ); 

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DModel::Render( DWORD* pdwNumVerts )
{
    *pdwNumVerts = m_dwNumFaces;

    if( m_pMesh )
        return m_pMesh->Render( g_pd3dDevice ); 

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DModel::RenderBoundingBox()
{
    D3DMATERIAL9 mtrl;
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
    g_pd3dDevice->SetTexture( 0, NULL );
    D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f );
    g_pd3dDevice->SetMaterial( &mtrl );
    g_pd3dDevice->SetFVF( LINELIST_FVF );
    g_pd3dDevice->SetStreamSource( 0, m_pBoundingVB, 0, sizeof(LINELIST_VERTEX) );
    g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, 12 );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DModel::InvalidateDeviceObjects()
{
    if( m_pMesh )
        return m_pMesh->InvalidateDeviceObjects(); 

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DModel::DeleteDeviceObjects()
{
    SAFE_RELEASE( m_pBoundingVB );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc:
//-----------------------------------------------------------------------------
VOID C3DModel::FinalCleanup()
{
    if( m_pMesh )
    {
        m_pMesh->Destroy(); 
        SAFE_DELETE( m_pMesh );
    }
}





