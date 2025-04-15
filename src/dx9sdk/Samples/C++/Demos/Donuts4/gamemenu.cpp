//-----------------------------------------------------------------------------
// File: GameMenu.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CMenuItem::CMenuItem( TCHAR* strNewLabel, DWORD dwNewID )
{
    _tcscpy( strLabel, strNewLabel );
    dwID           = dwNewID;
    pParent        = NULL;
    dwNumChildren  = 0L;
    dwSelectedMenu = 0L;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CMenuItem::~CMenuItem()
{
    while( dwNumChildren )
        delete pChild[--dwNumChildren];
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CMenuItem* CMenuItem::Add( CMenuItem* pNewChild )
{
    pChild[dwNumChildren++] = pNewChild;
    pNewChild->pParent = this;

    return pNewChild;
}



//-----------------------------------------------------------------------------
// Name: Render()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMenuItem::Render( CD3DFont* pFont )
{
    // Check parameters
    if( NULL == pFont )
        return E_INVALIDARG;

    // Save current matrices
    D3DXMATRIX matViewSaved, matProjSaved;
    g_pd3dDevice->GetTransform( D3DTS_VIEW,       &matViewSaved );
    g_pd3dDevice->GetTransform( D3DTS_PROJECTION, &matProjSaved );

    // Setup new view and proj matrices for head-on viewing
    D3DXMATRIX matView, matProj;

    D3DXVECTOR3 vAt = D3DXVECTOR3(0.0f,0.0f,-30.0f);
    D3DXVECTOR3 vLookAt = D3DXVECTOR3(0.0f,0.0f,0.0f);
    D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
    
    D3DXMatrixLookAtLH( &matView, &vAt, &vLookAt, &vUp );
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_VIEW,       &matView );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    // Establish colors for selected vs. normal menu items
    D3DMATERIAL9 mtrlNormal, mtrlSelected, mtrlTitle;
    D3DUtil_InitMaterial( mtrlTitle,    1.0f, 0.0f, 0.0f, 1.0f );
    D3DUtil_InitMaterial( mtrlNormal,   1.0f, 1.0f, 1.0f, 0.5f );
    D3DUtil_InitMaterial( mtrlSelected, 1.0f, 1.0f, 0.0f, 1.0f );

    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT,  0xffffffff );

    // Translate the menuitem into place
    D3DXMATRIX matWorld;
    D3DXMatrixScaling( &matWorld, 0.4f, 0.4f, 0.4f );
    matWorld._42 = (dwNumChildren*1.0f) + 2.0f;
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    g_pd3dDevice->SetMaterial( &mtrlTitle );

    // Render the menuitem's label
    pFont->Render3DText( strLabel, D3DFONT_CENTERED_X|D3DFONT_TWOSIDED );

    // Loop through and render all menuitem lables
    for( DWORD i=0; i<dwNumChildren; i++ )
    {
        D3DXMATRIX matWorld;
        D3DXMatrixScaling( &matWorld, 0.3f, 0.3f, 0.3f );
        g_pd3dDevice->SetMaterial( &mtrlNormal );

        // Give a different effect for selected items
        if( dwSelectedMenu == i )
        {
            D3DXMATRIX matRotate;
            D3DXMatrixRotationY( &matRotate, (D3DX_PI/3)*sinf(timeGetTime()/200.0f) );
            D3DXMatrixMultiply( &matWorld, &matWorld, &matRotate );
            g_pd3dDevice->SetMaterial( &mtrlSelected );
        }

        // Translate the menuitem into place
        matWorld._42 = (dwNumChildren*1.0f) - (i*2.0f);
        g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

        // Render the menuitem's label
        pFont->Render3DText( pChild[i]->strLabel, 
                             D3DFONT_CENTERED_X|D3DFONT_TWOSIDED );
    }

    // Restore matrices
    g_pd3dDevice->SetTransform( D3DTS_VIEW,       &matViewSaved );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProjSaved );

    return S_OK;
}




