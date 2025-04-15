//-----------------------------------------------------------------------------
// File: PlayerShip.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: CPlayerShip()
// Desc:
//-----------------------------------------------------------------------------
CPlayerShip::CPlayerShip() 
    : C3DDisplayObject(OBJ_PLAYER) 
{
    m_fBulletRechargeTime   = 0.0f; 
    m_fShield = 0.0f;
    m_vEulerAngles = D3DXVECTOR3(0,0,0);
}




//-----------------------------------------------------------------------------
// Name: ~CPlayerShip()
// Desc:
//-----------------------------------------------------------------------------
CPlayerShip::~CPlayerShip(void)
{
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT CPlayerShip::OneTimeSceneInit( const DWORD dwStyle, const D3DXVECTOR3& vStartPos, const D3DXMATRIX* pmOrientation, const C3DModel* pModel )
{
    m_fMass                 = g_Profile.Ship.fMass;
    m_bAffectByGravity      = true;
    m_bHover                = false;
    m_bReallyGoodHover      = true;
    m_bAutoLevel            = false;
    m_fGravityFactor        = 15.0f;
    m_fAngularDragFactor    = -10.0f;
    m_fBulletRechargeTime   = 0.0f; 
    m_fShield               = 0.0f;
    m_vEulerAngles          = D3DXVECTOR3(0,0,0);
    m_fShield               = g_Profile.Ship.fMaxShield;

    return C3DDisplayObject::OneTimeSceneInit( dwStyle, vStartPos, pmOrientation, pModel );
}




//-----------------------------------------------------------------------------
// Name: GetArtificialForces()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CPlayerShip::GetArtificialForces( const float fElapsedTime )
{
    if( NULL == g_pUserInput )
        return E_FAIL;

    if( g_pApp->m_bDebugMode )
    {
        D3DXVECTOR3 vUDThrust = D3DXVECTOR3(0.0f,1.0f,0.0f);
        vUDThrust *= g_pUserInput->fAxisFlyUD * g_Profile.Ship.fAccelFactor;
        m_pResult->m_vForcesLocal += vUDThrust;
    }

    D3DXVECTOR3 vForwardThrust = D3DXVECTOR3(0.0f,0.0f,1.0f);
    vForwardThrust *= g_pUserInput->fAxisMoveUD * g_Profile.Ship.fAccelFactor;
    m_pResult->m_vForcesLocal += vForwardThrust;

    D3DXVECTOR3 vSidewaysThrust = D3DXVECTOR3(1.0f,0.0f,0.0f);
    vSidewaysThrust *= g_pUserInput->fAxisMoveLR * g_Profile.Ship.fAccelFactor;
    m_pResult->m_vForcesLocal += vSidewaysThrust;

    // Mouselook based on euler angles
    m_vEulerAngles.y += 5.0f * g_pUserInput->fAxisRotateLR * fElapsedTime;
    m_vEulerAngles.x += -5.0f * g_pUserInput->fAxisRotateUD * fElapsedTime;

    // Trap the up-down to good values
    if( m_vEulerAngles.x < -D3DX_PI*0.5f )
        m_vEulerAngles.x = -D3DX_PI*0.5f;
    if( m_vEulerAngles.x > D3DX_PI*0.5f )
        m_vEulerAngles.x = D3DX_PI*0.5f;

    // Update the orientation based on the euler angles.  
    // This overrides the angluar momement code
    D3DXMatrixRotationYawPitchRoll( &m_pSource->m_mOrientation, 
                                    m_vEulerAngles.y, // look left-right
                                    m_vEulerAngles.x, // look up-down
                                    0.0f );           // no roll

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMoveFinalize()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CPlayerShip::FrameMoveFinalize( const float fElapsedTime )
{
    if( NULL == g_pUserInput )
        return E_FAIL;

    // Fire a bullet
    m_fBulletRechargeTime -= fElapsedTime;
    if( g_pUserInput->bButtonFireWeapons && m_fBulletRechargeTime <= 0.0f )
    {
        FireWeapon();
        m_fBulletRechargeTime = g_Profile.Blaster.fRechargeTime;
    }

    return C3DDisplayObject::FrameMoveFinalize( fElapsedTime );
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CPlayerShip::Render( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts )
{
    *pdwNumVerts = 0;
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FireWeapon()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CPlayerShip::FireWeapon()
{
    if( g_pApp->m_pBullet1Sound )
        g_pApp->m_pBullet1Sound->Play();

    D3DXVECTOR3 vAheadLocal = D3DXVECTOR3(0.0,0.0f,1.0f);
    D3DXVECTOR3 vAheadWorld;
    D3DXVec3TransformNormal( &vAheadWorld, &vAheadLocal, &m_pSource->m_mOrientation ); 

    CBullet* pBullet = new CBullet();
    if( pBullet )
    {
        D3DXMATRIX mOrientation;
        D3DXMatrixRotationYawPitchRoll( &mOrientation, rnd(-D3DX_PI,D3DX_PI), rnd(-D3DX_PI,D3DX_PI), rnd(-D3DX_PI,D3DX_PI) );
        float fDot = D3DXVec3Dot( &m_pSource->m_vCMVel, &vAheadWorld );

        D3DXVECTOR3 vStartPos = m_pSource->m_vCMPos + (fDot/10.0f + 1.0f) * vAheadWorld;
        D3DXVECTOR3 vStartVel = D3DXVECTOR3(m_pSource->m_vCMVel.x,0.0f,m_pSource->m_vCMVel.z) + g_Profile.Blaster.fSpeed * vAheadWorld;
        pBullet->OneTimeSceneInit( &g_Profile.Blaster, vStartPos, &mOrientation, vStartVel );
        pBullet->InitDeviceObjects();
        pBullet->RestoreDeviceObjects();
        g_pTerrain->AddDisplayObject( pBullet );
    }

    m_fBulletRechargeTime = g_Profile.Blaster.fRechargeTime;

    return S_OK;
}



