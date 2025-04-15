//-----------------------------------------------------------------------------
// File: Bullet.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: CBullet()
// Desc:
//-----------------------------------------------------------------------------
CBullet::CBullet() 
    : C3DDisplayObject(OBJ_BULLET) 
{
    m_fExpireCountdown = 0.0f;
}




//-----------------------------------------------------------------------------
// Name: ~CBullet()
// Desc:
//-----------------------------------------------------------------------------
CBullet::~CBullet(void)
{
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CBullet::OneTimeSceneInit( CBulletParameter* pBulletParam, const D3DXVECTOR3& vStartPos, 
                                   const D3DXMATRIX* pmOrientation, const D3DXVECTOR3& vVel )
{
    m_pBulletParam = pBulletParam;
    m_pSource->m_vCMVel = vVel;
    m_fMass = pBulletParam->fMass;
    m_fLinearDragFactor = 0.1f;
    m_fExpireCountdown = pBulletParam->fExpireCountdown;
    m_bAutoLevel        = false;
    m_bHover            = false;
    m_bReallyGoodHover  = false;
    m_bAffectByGravity  = false;
    D3DUtil_InitMaterial( m_mtrl, rnd(0), rnd(0), rnd(0) );

    return C3DDisplayObject::OneTimeSceneInit( 0, vStartPos, pmOrientation, pBulletParam->pModel );
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CBullet::FrameMove( const float fElapsedTime )
{
    m_fExpireCountdown -= fElapsedTime;
    if( m_fExpireCountdown < 0.0f )
        m_bActive = false;

    return C3DDisplayObject::FrameMove( fElapsedTime );
}




//-----------------------------------------------------------------------------
// Name: GetArtificialForces()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CBullet::GetArtificialForces( const float fElapsedTime )
{
/*
            // Move the bullets
            CBullet2* pBullet = (CBullet2*)pObject;

            if( pBullet->bActive )
            {
                // Update the position and animation frame
                pBullet->vPos += pBullet->vVel * m_fElapsedTime;

                if( g_pTerrain )
                    g_pTerrain->GetWorldFromUniversal( pBullet->vPos.x, pBullet->vPos.z, &pBullet->vPos.x, &pBullet->vPos.z );

                pBullet->fExpireCountdown -= m_fElapsedTime;
            }

            // TODO: kill bullet if it hits mountain (optional)
            if( g_pTerrain )
            {
                FLOAT fTerrianHeight = g_pTerrain->GetHeight( pObject->vPos.x, pObject->vPos.z );
                if( fTerrianHeight > pBullet->pBulletStyle->fFollowTerrianStartHeight ) 
                    pBullet->vPos.y = fTerrianHeight + pBullet->pBulletStyle->fFollowTerrianOffset;
                else
                    pBullet->vPos.y = pBullet->pBulletStyle->fMinHeight;
            }

            if( pBullet->pParticleSystem && g_Profile.bRenderParticles )
            {
                D3DXVECTOR3 vEmitterPostion = pBullet->vPos;

                // Update particle system
                pBullet->pParticleSystem->Update( m_fElapsedTime, 
                                        pBullet->pBulletStyle->dwNumParticlesToEmit,
                                        pBullet->pBulletStyle->dwParticleColor,
                                        pBullet->pBulletStyle->dwParticleColorFade, 
                                        pBullet->pBulletStyle->fEmitVel,
                                        vEmitterPostion, pBullet->bActive );
            }

            // Remove bullets when the expire countdown is done && particles gone
            if( pBullet->fExpireCountdown < 0.0 )
                pBullet->bActive = FALSE;

            if( !pBullet->bActive )
            {
                if( (pBullet->pParticleSystem && pBullet->pParticleSystem->GetNumActiveParticles() == 0) ||
                    (pBullet->pParticleSystem == NULL) )
                {
                    CDisplayObject2* pVictim = pObject;
                    pObject = pObject->pPrev;
                    DeleteFromList( pVictim );
                }
            }
*/
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CBullet::Render( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts )
{
    float fX = m_pResult->m_vCMPos.x;
    float fY = m_pResult->m_vCMPos.y;
    float fZ = m_pResult->m_vCMPos.z;

    D3DXMATRIX matWorld;
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, m_pBulletParam->dwAmbientLight );       
    g_pd3dDevice->SetTexture( 0, NULL );
    g_pd3dDevice->SetMaterial( &m_mtrl );

    D3DXMatrixTranslation( &matWorld, fX + fWrapOffsetX, fY, fZ + fWrapOffsetZ );
    D3DXMatrixMultiply( &matWorld, &m_pResult->m_mOrientation, &matWorld );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    if( m_pBulletParam->pModel )
        m_pBulletParam->pModel->Render( pdwNumVerts );	

    return S_OK;
}

