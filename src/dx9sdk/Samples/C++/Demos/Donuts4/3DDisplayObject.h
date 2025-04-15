//-----------------------------------------------------------------------------
// File: 3DDisplayObject.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

#define APP_S_NOCOLLIDE   S_FALSE   
#define APP_S_COLLIDING   MAKE_HRESULT(0,FACILITY_ITF,0x201)

class C3DDisplayObject : public CDisplayObject
{
public:
    C3DDisplayObject( const OBJECT_TYPE ObjectType );
    virtual ~C3DDisplayObject(void);

    virtual HRESULT OneTimeSceneInit( const DWORD dwStyle, const D3DXVECTOR3& vStartPos, const D3DXMATRIX* pmOrientation, const C3DModel* pModel );
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT FrameMove( const float fElapsedTime );
    virtual HRESULT HandleNearbyObject( const float fElapsedTime, CDisplayObject* pObject );
    virtual HRESULT FrameMoveFinalize( const float fElapsedTime );
    virtual HRESULT CullObject( const float fWrapOffsetX, const float fWrapOffsetZ, const CULLINFO* const pCullInfo );
    virtual HRESULT Render( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts ) = 0;
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual VOID    FinalCleanup();

    virtual HRESULT GetArtificialForces( const float fElapsedTime ) = 0;

    bool IsPointInQuad( const D3DXVECTOR3& vPt, const D3DXVECTOR3* pvQuad );
    bool IsPointInTriangle( const D3DXVECTOR3* pvPt, const D3DXVECTOR3* pA, const D3DXVECTOR3* pB, const D3DXVECTOR3* pC );
    bool ArePointsSameSideOfLine( const D3DXVECTOR3* pvP1, const D3DXVECTOR3* pvP2, const D3DXVECTOR3* pvA, const D3DXVECTOR3* pvB );

    HRESULT CheckForGroundCollsion();
    HRESULT ResolveCollsionWithGroundPt( const D3DXVECTOR3& vPtOnObjectWorld, const D3DXVECTOR3& vPtOnGround );
    static HRESULT C3DDisplayObject::ResolveCollsionWithObjectPt( const C3DDisplayObject* pObject1, const C3DDisplayObject* pObject2, const D3DXVECTOR3& vPtOnObject1World, const D3DXVECTOR3& vPtOnObject2World, const D3DXVECTOR3& vObject2FaceNormal );
    VOID    GetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt, D3DXVECTOR3* pvUpVec );

public:
    DWORD           m_dwStyle; 
    const C3DModel* m_pModel;

public:
    struct OBJECT_STATE
    {
        D3DXVECTOR3     m_vCMPos;       // Position of center of mass in world coords
        D3DXVECTOR3     m_vCMVel;       // Velocity of center of mass in world coords
        FLOAT           m_fSpeed;       // Magnitude of velocity
        D3DXVECTOR3     m_vCMAcc;       // Accelation of center of mass in world coords

        D3DXVECTOR3     m_vAngularVel;  // Angular Velocity in local coords
        D3DXMATRIX      m_mOrientation;
        D3DXVECTOR3     m_vAngularMomentum;  
        D3DXMATRIX      m_mInverseWorldInertiaTensor;
        D3DXQUATERNION  m_qOrientation; // Orientation in world coords

        D3DXVECTOR3     m_vForcesLocal; // Total forces on object in local coords
        D3DXVECTOR3     m_vMoments;     // Total moments on object (torque)
    };

    OBJECT_STATE    m_ObjStates[2];

    OBJECT_STATE*   m_pSource;
    OBJECT_STATE*   m_pResult;

    FLOAT           m_fMass;        // Mass of object
    D3DXMATRIX      m_mInertia;     // Mass moment of inertia in local coords
    D3DXMATRIX      m_mInertiaInv;  // Inverse of mass moment of inertia in local coords
    D3DXMATRIX      m_mInteriaWorldInv; // Inverse of moment of inertia in world coords
    D3DXVECTOR3     m_vBoundingVertexWorld[8];

    float           m_fHealth;
    float           m_fLinearDragFactor;
    float           m_fAngularDragFactor;
    bool            m_bAutoLevel;
    bool            m_bAffectByGravity;
    bool            m_bHover;
    bool            m_bReallyGoodHover;
    float           m_fCr; // coefficient of restituion (how bouncy collision is)
    float           m_fGravityFactor;
    bool            m_bRenderBoundingBox;
    bool            m_bAllowObjectMovement;

    bool            m_bGroundCollide;
    bool            m_bVelocityCollision;
};
