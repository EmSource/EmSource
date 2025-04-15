//-----------------------------------------------------------------------------
// File: Bullet.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

class CBullet : public C3DDisplayObject
{
public:
    CBullet();
    virtual ~CBullet(void);

public:
    virtual HRESULT OneTimeSceneInit( CBulletParameter* pBulletParam, const D3DXVECTOR3& vStartPos, const D3DXMATRIX* pmOrientation, const D3DXVECTOR3& vVel );

    virtual HRESULT FrameMove( const float fElapsedTime );
    virtual HRESULT GetArtificialForces( const float fElapsedTime );
    virtual HRESULT Render( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts );

public:
    CBulletParameter* m_pBulletParam;
    float m_fExpireCountdown;
    D3DMATERIAL9 m_mtrl;
};
