//-----------------------------------------------------------------------------
// File: PlayerShip.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

class CPlayerShip : public C3DDisplayObject
{
public:
    CPlayerShip();
    virtual ~CPlayerShip(void);

public:
    virtual HRESULT OneTimeSceneInit( const DWORD dwStyle, const D3DXVECTOR3& vStartPos, const D3DXMATRIX* pmOrientation, const C3DModel* pModel );
    virtual HRESULT Render( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts );

    virtual HRESULT GetArtificialForces( const float fElapsedTime );
    virtual HRESULT FrameMoveFinalize( const float fElapsedTime );

    HRESULT FireWeapon();

    float m_fBulletRechargeTime;
    float m_fShield;
    D3DXVECTOR3 m_vEulerAngles;
};
