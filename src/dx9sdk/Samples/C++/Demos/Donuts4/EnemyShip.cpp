//-----------------------------------------------------------------------------
// File: EnemyShip.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: CEnemyShip()
// Desc:
//-----------------------------------------------------------------------------
CEnemyShip::CEnemyShip() 
    : C3DDisplayObject( OBJ_ENEMY ) 
{
    m_fChangeDirCountdown = 0.0f;
    m_bDeathAnimationActive = false;
    m_fDeathAnimationCountdown = 0.0f;
    m_fHitAnimationCountdown = 0.0f;
    m_fInvulnerableCountdown = 0.0f;
    m_fThrustCountdown = 0.0f;
    m_fTurnCountdown = 0.0f;
    m_fMoment = 0.0f;
}




//-----------------------------------------------------------------------------
// Name: ~CEnemyShip()
// Desc:
//-----------------------------------------------------------------------------
CEnemyShip::~CEnemyShip(void)
{
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT CEnemyShip::OneTimeSceneInit( const DWORD dwStyle, const D3DXVECTOR3& vStartPos, const D3DXMATRIX* pmOrientation, const C3DModel* pModel )
{
    CEnemyStyle* pEnemyStyle = &g_Profile.aEnemyStyles[ m_dwStyle ];
    m_fMass = pEnemyStyle->fMass;
    m_fHealth = pEnemyStyle->fMaxHealth;

    return C3DDisplayObject::OneTimeSceneInit( dwStyle, vStartPos, pmOrientation, pModel );
}




//-----------------------------------------------------------------------------
// Name: GetArtificialForces()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CEnemyShip::GetArtificialForces( const float fElapsedTime )
{
    // Update the position and animation frame
    CEnemyStyle* pEnemyStyle = &g_Profile.aEnemyStyles[ m_dwStyle ];

    m_fInvulnerableCountdown -= fElapsedTime;
    m_fHitAnimationCountdown -= fElapsedTime;

    if( m_bDeathAnimationActive )
    {
        m_fDeathAnimationCountdown -= fElapsedTime;

        if( m_fDeathAnimationCountdown < 0.0f )
        {
            if( g_pApp->m_pExplosionDonutSound )
                g_pApp->m_pExplosionDonutSound->Play();

            if( g_pApp->m_pMusicScript )
            {
                g_pApp->m_pMusicScript->SetVariableNumber("ObjectCount",g_pTerrain->m_dwEnemyCount);
                g_pApp->m_pMusicScript->CallRoutine("ExplodeObject");
            }

            m_bActive = false;
        }
    }
    else if( m_fHealth <= 0.0f )
    {
        m_bDeathAnimationActive = true;
        m_fDeathAnimationCountdown = pEnemyStyle->fDeathAnimationCountdown;

        // Keep object still while it is dying
        m_bAllowObjectMovement = false; 
    }

    D3DXMATRIX mOInv;
    D3DXMatrixInverse( &mOInv, NULL, &m_pSource->m_mOrientation );
    D3DXVECTOR3 vXLocal = D3DXVECTOR3(1.0f,0.0f,0.0f);
    D3DXVECTOR3 vYLocal = D3DXVECTOR3(0.0f,1.0f,0.0f);
    D3DXVECTOR3 vZLocal = D3DXVECTOR3(0.0f,0.0f,1.0f);
    D3DXVECTOR3 vXWorldInv;
    D3DXVECTOR3 vYWorldInv;
    D3DXVECTOR3 vZWorldInv;
    D3DXVECTOR3 vXWorld;
    D3DXVECTOR3 vYWorld;
    D3DXVECTOR3 vZWorld;

    D3DXVec3TransformNormal( &vXWorldInv, &vXLocal, &mOInv ); 
    D3DXVec3TransformNormal( &vYWorldInv, &vYLocal, &mOInv ); 
    D3DXVec3TransformNormal( &vZWorldInv, &vZLocal, &mOInv ); 

    D3DXVec3TransformNormal( &vXWorld, &vXLocal, &m_pSource->m_mOrientation ); 
    D3DXVec3TransformNormal( &vYWorld, &vYLocal, &m_pSource->m_mOrientation ); 
    D3DXVec3TransformNormal( &vZWorld, &vZLocal, &m_pSource->m_mOrientation ); 

    m_pResult->m_vForcesLocal = D3DXVECTOR3(0,0,0);
    m_pResult->m_vMoments = D3DXVECTOR3(0,0,0);

    if( g_pApp->m_bDebugMode && this == g_pDebugFirstEnemy )
    {
        float fScale = 1.0f;
        if( g_pApp->m_pInputManager->m_UserInput.bButtonShift )
            fScale = 0.1f;
        m_pSource->m_vCMPos.x += g_vDebugMove.x * fScale;
        m_pSource->m_vCMPos.y += g_vDebugMove.y * fScale;
        m_pSource->m_vCMPos.z += g_vDebugMove.z * fScale;
        m_pResult->m_vMoments += g_vDebugRotate.x * vXWorld * 1000.f;
        m_pResult->m_vMoments += g_vDebugRotate.y * vYWorld * 1000.f;
        m_pResult->m_vMoments += g_vDebugRotate.z * vZWorld * 1000.f;
    }

    switch( pEnemyStyle->EnemyMovementType ) 
    {
        case EMT_None:
        {
            break;
        }

        case EMT_MoveRandom:
        {
            m_fChangeDirCountdown -= fElapsedTime;
            m_fThrustCountdown -= fElapsedTime;
            m_fTurnCountdown -= fElapsedTime;
            if( m_fChangeDirCountdown < 0.0f )
            {
                m_fChangeDirCountdown = pEnemyStyle->fMoveRandomCountdown;
                m_fThrustCountdown = pEnemyStyle->fThrustCountdown;
                m_fTurnCountdown = pEnemyStyle->fTurnCountdown;
                m_fMoment = rnd();
            }

            if( m_fTurnCountdown > 0.0f )
            {
                m_pResult->m_vMoments += m_fMoment * vYWorld * 1000.f;
            }

            if( m_fThrustCountdown > 0.0f )
            {
                float fThrust = 0.3f;
                m_pResult->m_vForcesLocal -= fThrust * vXLocal * 10000.f;
            }
            break;
        }

        case EMT_MoveTowards:
        {
            // Not implemented
            break;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CEnemyShip::Render( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts )
{
    float fX = m_pResult->m_vCMPos.x;
    float fY = m_pResult->m_vCMPos.y;
    float fZ = m_pResult->m_vCMPos.z;

    CEnemyStyle* pEnemyStyle = &g_Profile.aEnemyStyles[m_dwStyle];

    D3DMATERIAL9 mtrl;
    D3DXMATRIX matPos;
    D3DXMATRIX matScale;
    D3DXMATRIX matRot;
    D3DXMATRIX matWorld;
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, pEnemyStyle->dwEnemyAmbientLight );       
    g_pd3dDevice->SetTexture( 0, NULL );
/*
    if( m_fHitAnimationCountdown > 0.0f )
    {
        D3DUtil_InitMaterial( mtrl, 0.0f, 0.0f, 0.0f, 0.0f );
    }
    else
    {
        D3DXCOLOR clrOut;
        D3DXColorLerp( &clrOut, &pEnemyStyle->clrDead, &pEnemyStyle->clrAlive, m_fHealth/pEnemyStyle->fMaxHealth );
        D3DUtil_InitMaterial( mtrl, clrOut.r, clrOut.g, clrOut.b, clrOut.a );
    }
*/
    D3DUtil_InitMaterial( mtrl, pEnemyStyle->clrAlive.r, pEnemyStyle->clrAlive.g, pEnemyStyle->clrAlive.b, pEnemyStyle->clrAlive.a );

    pEnemyStyle->pModel->m_pMesh->m_pMaterials[1] = mtrl;
    D3DXMatrixTranslation( &matPos, fX + fWrapOffsetX, fY, fZ + fWrapOffsetZ );

    if( m_fDeathAnimationCountdown > 0.0f )
    {
        D3DXMATRIX matScale;
        D3DXMATRIX matJitter;
        float fZeroToOne = (pEnemyStyle->fDeathAnimationCountdown - m_fDeathAnimationCountdown)/pEnemyStyle->fDeathAnimationCountdown;
        float fScale = fZeroToOne*5.0f + 1.0f;

        D3DXMatrixTranslation( &matJitter, rnd()*0.3f, rnd()*0.3f, rnd()*0.3f );
        D3DXMatrixScaling( &matScale, fScale, fScale, fScale );
        D3DXMatrixMultiply( &matPos, &matScale, &matPos );
        D3DXMatrixMultiply( &matPos, &matJitter, &matPos );
    }

    D3DXMatrixMultiply( &matWorld, &m_pResult->m_mOrientation, &matPos );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    if( pEnemyStyle->pModel )
        pEnemyStyle->pModel->Render( pdwNumVerts );	

    return S_OK;
}




