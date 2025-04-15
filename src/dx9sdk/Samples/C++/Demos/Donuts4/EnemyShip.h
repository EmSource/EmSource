//-----------------------------------------------------------------------------
// File: EnemyShip.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

class CEnemyShip : public C3DDisplayObject
{
public:
    CEnemyShip();
    ~CEnemyShip(void);

public:
    virtual HRESULT OneTimeSceneInit( const DWORD dwStyle, const D3DXVECTOR3& vStartPos, const D3DXMATRIX* pmOrientation, const C3DModel* pModel );
    HRESULT GetArtificialForces( const float fElapsedTime );
    HRESULT Render( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts );

    float m_fChangeDirCountdown;
    float m_fThrustCountdown;
    float m_fTurnCountdown;
    float m_fInvulnerableCountdown;
    float m_fHitAnimationCountdown;
    float m_fDeathAnimationCountdown;
    bool  m_bDeathAnimationActive;
    float m_fMoment;
};
