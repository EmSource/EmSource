//-----------------------------------------------------------------------------
// File: 3DDrawManager.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
C3DDrawManager::C3DDrawManager(void)
{
    ZeroMemory( m_aPtList, sizeof(DRAW_POINT)*MAX_POINTS );
    ZeroMemory( m_aLineList, sizeof(DRAW_LINE)*MAX_LINES );
    m_dwNumLines = 0;
    m_pSphere = NULL;
    m_pLineVB = NULL;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
C3DDrawManager::~C3DDrawManager(void)
{
    FinalCleanup();
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::OneTimeSceneInit()
{
    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::InitDeviceObjects()
{
    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::RestoreDeviceObjects()
{
    D3DXCreateSphere( g_pd3dDevice, 1.0f, 8, 8, &m_pSphere, NULL );

    HRESULT hr;
    hr = g_pd3dDevice->CreateVertexBuffer( MAX_LINES * 2 * sizeof(DRAW_LINE_VERTEX),
                                        D3DUSAGE_WRITEONLY,
                                        DRAW_LINE_FVF, D3DPOOL_MANAGED,
                                        &m_pLineVB, NULL );
    if( FAILED(hr) )
        return hr;

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::FrameMove( const float fElapsedTime )
{
    int i;
    for( i=0; i<MAX_POINTS; i++ )
    {
        if( m_aPtList[i].bInvalidateEveryFrame )
            m_aPtList[i].bValid = false;
    }
    for( i=0; i<MAX_LINES; i++ )
    {
        if( m_aLineList[i].bInvalidateEveryFrame )
            m_aLineList[i].bValid = false;
    }

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::Render()
{
    D3DXMATRIX matScale;
    D3DXMATRIX matTranslate;
    D3DXMATRIX mat;
    DWORD i;
    D3DMATERIAL9 mtrl;       
    HRESULT hr;

    if( !m_pLineVB )
        return S_OK;

    DRAW_LINE_VERTEX* pVertexBuffer = NULL;
    m_dwNumLines = 0;
    hr = m_pLineVB->Lock( 0, 0, (void**) &pVertexBuffer, 0 );
    if( SUCCEEDED(hr) )
    {
        for( i=0; i<MAX_LINES; i++ )
        {
            if( m_aLineList[i].bValid )
            {
                pVertexBuffer->p = m_aLineList[i].vPosFrom;
                pVertexBuffer->c = m_aLineList[i].dwColor;
                pVertexBuffer++;

                pVertexBuffer->p = m_aLineList[i].vPosTo;
                pVertexBuffer->c = m_aLineList[i].dwColor;
                pVertexBuffer++;

                m_dwNumLines++;
            }
        }

        m_pLineVB->Unlock(); 
    }

    if( m_dwNumLines > 0 )
    {
        D3DXMatrixIdentity( &mat );
        g_pd3dDevice->SetTransform( D3DTS_WORLD, &mat );
        g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
        g_pd3dDevice->SetTexture( 0, NULL );
        D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f );
        g_pd3dDevice->SetMaterial( &mtrl );
        g_pd3dDevice->SetFVF( DRAW_LINE_FVF );
        g_pd3dDevice->SetStreamSource( 0, m_pLineVB, 0, sizeof(DRAW_LINE_VERTEX) );
        g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, m_dwNumLines );
        g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    }

    for( i=0; i<MAX_POINTS; i++ )
    {
        if( m_aPtList[i].bValid )
        {
            D3DXMatrixScaling( &matScale, m_aPtList[i].fSize, m_aPtList[i].fSize, m_aPtList[i].fSize );
            D3DXMatrixTranslation( &matTranslate, m_aPtList[i].vPos.x, m_aPtList[i].vPos.y, m_aPtList[i].vPos.z );
            D3DXMatrixMultiply( &mat, &matScale, &matTranslate );

            float fR = ((m_aPtList[i].dwColor&0x00ff0000)>>16) / 255.0f;
            float fG = ((m_aPtList[i].dwColor&0x0000ff00)>>8)  / 255.0f;
            float fB = ((m_aPtList[i].dwColor&0x000000ff)>>0)  / 255.0f;
            D3DUtil_InitMaterial( mtrl, fR, fG, fB );
            g_pd3dDevice->SetTexture( 0, NULL );
            g_pd3dDevice->SetMaterial( &mtrl );

            g_pd3dDevice->SetTransform( D3DTS_WORLD, &mat );
            m_pSphere->DrawSubset(0);
        }
    }

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::InvalidateDeviceObjects()
{
    SAFE_RELEASE( m_pSphere );
    SAFE_RELEASE( m_pLineVB );

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::DeleteDeviceObjects()
{
    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID C3DDrawManager::FinalCleanup()
{
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::AddPoint( D3DXVECTOR3 vPos, float fSize, DWORD dwColor, DWORD dwID, bool bInvalidateEveryFrame )
{
    int iChoose;

    for( iChoose=0; iChoose<MAX_POINTS; iChoose++ )
    {
        if( !m_aPtList[iChoose].bValid )
            break;
    }

    if( iChoose < MAX_POINTS )
    {
        m_aPtList[iChoose].vPos    = vPos;
        m_aPtList[iChoose].fSize   = fSize;
        m_aPtList[iChoose].dwColor = dwColor;
        m_aPtList[iChoose].dwID    = dwID;
        m_aPtList[iChoose].bInvalidateEveryFrame = bInvalidateEveryFrame;
        m_aPtList[iChoose].bValid  = true;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::InvalidatePoints( DWORD dwID )
{
    for( int i=0; i<MAX_POINTS; i++ )
    {
        if( m_aPtList[i].dwID == dwID )
            m_aPtList[i].bValid = false;
    }

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::InvalidateLines( DWORD dwID )
{
    for( int i=0; i<MAX_LINES; i++ )
    {
        if( m_aLineList[i].dwID == dwID )
            m_aLineList[i].bValid = false;
    }

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT C3DDrawManager::AddLine( D3DXVECTOR3 vPosFrom, D3DXVECTOR3 vPosTo, DWORD dwColor, DWORD dwID, bool bInvalidateEveryFrame )
{
    int iChoose;

    for( iChoose=0; iChoose<MAX_LINES; iChoose++ )
    {
        if( !m_aLineList[iChoose].bValid )
            break;
    }

    if( iChoose < MAX_POINTS )
    {
        m_aLineList[iChoose].vPosFrom   = vPosFrom;
        m_aLineList[iChoose].vPosTo     = vPosTo;
        m_aLineList[iChoose].dwColor    = dwColor;
        m_aLineList[iChoose].dwID       = dwID;
        m_aLineList[iChoose].bInvalidateEveryFrame = bInvalidateEveryFrame;
        m_aLineList[iChoose].bValid     = true;
    }

    return S_OK;
}
