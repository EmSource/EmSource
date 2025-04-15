//-----------------------------------------------------------------------------
// File: 3DDisplayObject.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"



//-----------------------------------------------------------------------------
// Name: C3DDisplayObject()
// Desc:
//-----------------------------------------------------------------------------
C3DDisplayObject::C3DDisplayObject( const OBJECT_TYPE ObjectType ) 
        : CDisplayObject( ObjectType )
{
    m_dwStyle           = 0; 
    m_pModel            = NULL;
    m_fMass             = 0.0f;
    m_fLinearDragFactor = -10.0f;
    m_fAngularDragFactor = -0.8f;
    m_bAutoLevel        = true;
    m_bAffectByGravity  = true;
    m_bHover            = true;
    m_bReallyGoodHover  = false;
    m_fCr               = 0.4f;
    m_fGravityFactor    = 1.0f;
    m_bRenderBoundingBox = false;
    m_bAllowObjectMovement = true;
    m_fHealth           = 0.0f;

    m_pSource = &m_ObjStates[0];
    m_pResult = &m_ObjStates[1];

    ZeroMemory( m_pSource, sizeof(OBJECT_STATE) );
    ZeroMemory( m_pResult, sizeof(OBJECT_STATE) );

    m_pSource->m_vCMPos            = D3DXVECTOR3(0,0,0);
    m_pSource->m_vCMVel            = D3DXVECTOR3(0,0,0);
    m_pSource->m_vCMAcc            = D3DXVECTOR3(0,0,0);
    m_pSource->m_vAngularVel       = D3DXVECTOR3(0,0,0);
    m_pSource->m_vForcesLocal      = D3DXVECTOR3(0,0,0);
    m_pSource->m_vMoments          = D3DXVECTOR3(0,0,0);
    m_pSource->m_vAngularMomentum  = D3DXVECTOR3(0,0,0);
    D3DXMatrixIdentity( &m_pSource->m_mInverseWorldInertiaTensor );
    D3DXMatrixIdentity( &m_pSource->m_mOrientation );

    D3DXMatrixIdentity( &m_mInertiaInv );  
    D3DXMatrixIdentity( &m_mInteriaWorldInv );
}




//-----------------------------------------------------------------------------
// Name: C3DDisplayObject()
// Desc:
//-----------------------------------------------------------------------------
C3DDisplayObject::~C3DDisplayObject(void)
{
    FinalCleanup();
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::OneTimeSceneInit( const DWORD dwStyle, const D3DXVECTOR3& vStartPos, 
                                            const D3DXMATRIX* pmOrientation, const C3DModel* pModel )
{
    m_dwStyle   = dwStyle;
    m_pSource->m_vCMPos    = vStartPos;
    m_pSource->m_mOrientation = *pmOrientation;
    m_pModel    = pModel;

    assert( m_pModel != NULL );
    float fLength = m_pModel->m_vBoundingMax.x - m_pModel->m_vBoundingMin.x;
    float fHeight = m_pModel->m_vBoundingMax.y - m_pModel->m_vBoundingMin.y;
    float fWidth  = m_pModel->m_vBoundingMax.z - m_pModel->m_vBoundingMin.z;

    // Calc inertia tensor
    // For more information: 
    //      June 1997 Game Developer Magazine article "Physics, Part 4: The Third Dimension" by Chris Hecker
    //      "Physics for Game Developers" by David M. Bourg
    //      SIGGRAPH '95 course "An Introduction to Physically Based Modeling" by David Baraff 
    //      "Classical Mechanics" by Herbert Goldstein
    float Ixx, Iyy, Izz;    
    Ixx = m_fMass/12.0f * (fWidth*fWidth + fLength*fLength);
    Iyy = m_fMass/12.0f * (fHeight*fHeight + fLength*fLength);
    Izz = m_fMass/12.0f * (fWidth*fWidth + fHeight*fHeight);

    D3DXMATRIX mInertia;
    D3DXMatrixIdentity( &mInertia );
    mInertia._11 = Ixx;
    mInertia._22 = Iyy;
    mInertia._33 = Izz;

    // Store the inverse of the inertia tensor
    D3DXMatrixInverse( &m_mInertiaInv, NULL, &mInertia );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::InitDeviceObjects() 
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::RestoreDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: This handles the physics simulation for the 3d objects
//       This code uses Euler's method since it doesn't need to be accurate
//       but if interested check the references above for more information on
//       how to improve the numerical integration.
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::FrameMove( const float fElapsedTime )
{
    m_pResult->m_vForcesLocal = D3DXVECTOR3(0.0f,0.0f,0.0f);
    m_pResult->m_vMoments     = D3DXVECTOR3(0.0f,0.0f,0.0f);

    if( m_pPath )
    {
        // If the object is currently managed by an audiopath, update its distance there.
        D3DXVECTOR3 vDist = g_pApp->GetPlayerShip()->m_pSource->m_vCMPos - m_pSource->m_vCMPos;
        m_fDistToPlayer = D3DXVec3Length( &vDist );
        m_pPath->m_fDistance = m_fDistToPlayer;
    }

    C3DAudioPath* pFarthestPath = g_pApp->m_pFarthestAudioPath;
    if( pFarthestPath && m_ObjectType == OBJ_ENEMY )
    {
        if( m_pPath == NULL && m_fDistToPlayer < pFarthestPath->m_fDistance )
        {
            // This object is closer, so steal the audiopath.
            if (pFarthestPath->m_pObject)
                pFarthestPath->m_pObject->m_pPath = NULL;
            pFarthestPath->m_bReplaceSound = TRUE;
            pFarthestPath->m_pObject = this;
            this->m_pPath = pFarthestPath;

            // Okay, done. Now, get the new farthest path and use that to continue swapping
            g_pApp->UpdateFarthestAudioPath();
        }
    }

    // Ask the derived class if there's any artificial forces such as 
    // user input or AI that needs to be considered
    // These values are typically stored in m_pResult->m_vForcesLocal 
    // and m_pResult->m_vMoments
    GetArtificialForces( fElapsedTime );

    // Hover by thrusting upwards if object too low
    if( m_bHover )
    {
        D3DXMATRIX mOInv;
        D3DXMatrixInverse( &mOInv, NULL, &m_pSource->m_mOrientation );
        D3DXVECTOR3 vYLocal = D3DXVECTOR3(0.0f,1.0f,0.0f);
        D3DXVECTOR3 vYWorld;
        D3DXVec3TransformNormal( &vYWorld, &vYLocal, &mOInv ); 
        float fGroundY = g_pTerrain->GetHeight( m_pSource->m_vCMPos.x, m_pSource->m_vCMPos.z );
        float fHeightAboveGround = m_pSource->m_vCMPos.y - fGroundY;
        if( fHeightAboveGround < 12.0f )
        {
            float fThrustScaler;
            if( fHeightAboveGround < 8.0f )
                fThrustScaler = 1.0f;
            else 
                fThrustScaler = (1.0f - (fHeightAboveGround - 8.0f) / 3.0f);
            m_pResult->m_vForcesLocal += fThrustScaler * vYWorld * (9.8f + 4.0f)* m_fMass;
        }
    }

    if( m_bAutoLevel )
    {
        // Level the object with the ground by rotating the object so that the 
        // object's up vector in world coords becomes <0,1,0>.
        D3DXVECTOR3 vUp = D3DXVECTOR3(0.0,1.0f,0.0f);
        D3DXVECTOR3 vObjUpWorld;
        D3DXVECTOR3 vLevelingAxis;
        D3DXVec3TransformNormal( &vObjUpWorld, &vUp, &m_pSource->m_mOrientation ); 
        D3DXVec3Cross( &vLevelingAxis, &vObjUpWorld, &vUp  );
        m_pResult->m_vMoments += vLevelingAxis * 20.f * m_fMass;
    }

    // Convert forces from local to world coords
    D3DXVECTOR3 vForcesWorld;
    D3DXVec3TransformNormal( &vForcesWorld, &m_pResult->m_vForcesLocal, &m_pSource->m_mOrientation );     

    // Add linear drag 
    vForcesWorld += m_fLinearDragFactor * m_pSource->m_vCMVel;

    // Apply gravity
    if( m_bAffectByGravity )
        vForcesWorld.y -= 9.8f * m_fMass * m_fGravityFactor;

    // Update position based on linear velocity
    if( m_bAllowObjectMovement )
        m_pResult->m_vCMPos = m_pSource->m_vCMPos + m_pSource->m_vCMVel * fElapsedTime;
    else
        m_pResult->m_vCMPos = m_pSource->m_vCMPos;

    // Hover by setting the vCMPos.y if object too low
    if( m_bReallyGoodHover )
    {
        float fTerrianHeight = g_pTerrain->GetHeight( m_pResult->m_vCMPos.x, m_pResult->m_vCMPos.z );
        if( m_pResult->m_vCMPos.y < fTerrianHeight + 10.0f )
            m_pResult->m_vCMPos.y = fTerrianHeight + 10.0f;
        if( m_pResult->m_vCMPos.y > fTerrianHeight + 30.0f )
            m_pResult->m_vCMPos.y = fTerrianHeight + 30.0f;
    }

    // a = F/m
    m_pResult->m_vCMAcc = vForcesWorld / m_fMass; 

    // Update linear velocity based on linear acceleration
    m_pResult->m_vCMVel = m_pSource->m_vCMVel + m_pResult->m_vCMAcc * fElapsedTime;

    // Update the orientation quaternion based on angular velocity
    // Euler: f(t+dt) = f(t) + f'(t)dt
    D3DXMATRIX mSkewSymmetric;
    D3DXMATRIX mOrientationDelta;
    D3DXMatrixIdentity( &mSkewSymmetric );
    mSkewSymmetric._11 =                        0.0f;  mSkewSymmetric._21 = -m_pSource->m_vAngularVel.z; mSkewSymmetric._31 =  m_pSource->m_vAngularVel.y; 
    mSkewSymmetric._12 =  m_pSource->m_vAngularVel.z;  mSkewSymmetric._22 =                        0.0f; mSkewSymmetric._32 = -m_pSource->m_vAngularVel.x; 
    mSkewSymmetric._13 = -m_pSource->m_vAngularVel.y;  mSkewSymmetric._23 =  m_pSource->m_vAngularVel.x; mSkewSymmetric._33 =                        0.0f; 
    D3DXMatrixMultiply( &mOrientationDelta, &m_pSource->m_mOrientation, &mSkewSymmetric );
    if( m_bAllowObjectMovement )
        m_pResult->m_mOrientation = m_pSource->m_mOrientation + mOrientationDelta * fElapsedTime;
    else
        m_pResult->m_mOrientation = m_pSource->m_mOrientation;

    // Normalize the orientation
    Donuts_MatrixOrthroNormalize( &m_pResult->m_mOrientation, &m_pResult->m_mOrientation );

    // Add angular drag
    m_pResult->m_vMoments += m_fAngularDragFactor * m_pSource->m_vAngularMomentum;

    // Update angular momentum based on sum of moments
    m_pResult->m_vAngularMomentum = m_pSource->m_vAngularMomentum + m_pResult->m_vMoments * fElapsedTime;

    // Update angular momentum based on sum of moments
    D3DXMATRIX m4;
    D3DXMATRIX mOrientationTranspose;
    D3DXMatrixTranspose( &mOrientationTranspose, &m_pResult->m_mOrientation );
    D3DXMatrixMultiply( &m4, &m_mInertiaInv, &mOrientationTranspose );
    D3DXMatrixMultiply( &m_pResult->m_mInverseWorldInertiaTensor, &m_pResult->m_mOrientation, &m4 );

    // Update angular 
    D3DXVec3TransformNormal( &m_pResult->m_vAngularVel, &m_pResult->m_vAngularMomentum, &m_pResult->m_mInverseWorldInertiaTensor ); 

    if( !g_bDebugIsZoneRenderFroze || g_pApp->GetPlayerShip() != this ) // check for debugging 
    {
        // Ensure m_vCMPos lies inside the world map.  This will wrap the position if need be
        if( g_pTerrain )
            g_pTerrain->GetWorldFromUniversal( m_pResult->m_vCMPos.x, m_pResult->m_vCMPos.z, &m_pResult->m_vCMPos.x, &m_pResult->m_vCMPos.z );
    }

    // Convert bounding vertex's from local to world coords.
    for( int i=0; i<8; i++ )
    {
        D3DXVec3TransformNormal( &m_vBoundingVertexWorld[i], &m_pModel->m_vBoundingVertex[i], 
                                 &m_pResult->m_mOrientation ); 
        m_vBoundingVertexWorld[i] += m_pResult->m_vCMPos;
    }

    // Check for collisions
    CheckForGroundCollsion();

    if( !g_bDebugIsZoneRenderFroze || g_pApp->GetPlayerShip() != this ) // check for debugging 
    {
        // Ensure m_vCMPos lies inside the world map.  This will wrap the position if need be
        if( g_pTerrain )
            g_pTerrain->GetWorldFromUniversal( m_pResult->m_vCMPos.x, m_pResult->m_vCMPos.z, &m_pResult->m_vCMPos.x, &m_pResult->m_vCMPos.z );
    }

    m_vPos = m_pResult->m_vCMPos;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: HandleNearbyObject()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::HandleNearbyObject( const float fElapsedTime, 
                                              CDisplayObject* pObject2 )
{
    static const DWORD dwBoundFaces[6][4] = { {0,1, 2,3},  // front 
                            {4,5, 0,1},  // bottom
                            {1,5, 3,7},  // right
                            {4,0, 6,2},  // left
                            {5,4, 7,6},  // back
                            {2,3, 6,7} };// top

    // Skip these object types
    if( pObject2->m_ObjectType == OBJ_PARTICLE ||
        pObject2->m_ObjectType == OBJ_SPRITE || 
        pObject2->m_ObjectType == OBJ_PLAYER )
        return S_OK;

    C3DDisplayObject* p3DObject2 = (C3DDisplayObject*) pObject2;
    C3DDisplayObject* p3DObject1 = (C3DDisplayObject*) this;

    D3DXVECTOR3 vDelta = p3DObject2->m_pResult->m_vCMPos - m_pResult->m_vCMPos;
    float fDist = D3DXVec3Length( &vDelta );

    // Check if the objects are near enough to each 
    // other to collide by sphere testing
    if( fDist < this->m_pModel->m_fRadius + p3DObject2->m_pModel->m_fRadius )
    {
        D3DXVECTOR3 vBoundingFace[4];
        D3DXVECTOR3 vPtOnBoundingPlaneNearestObject;
        D3DXVECTOR3 vDeltaNorm;
        D3DXVECTOR3 v1, v2;
        D3DXVec3Normalize( &vDeltaNorm, &vDelta );
        float fDot;
        bool bBoundFaceShowing[6] = {0};  
        D3DXVECTOR3 vBoundFaceNormals[6];

        // Test each face on pObject2
        for( int iFace=0; iFace<6; iFace++ )
        {
            // Figure out the face normal
            v1 = p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][1]] - p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][0]];
            v2 = p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][2]] - p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][0]];
            D3DXVec3Cross( &vBoundFaceNormals[iFace], &v2, &v1 );
            D3DXVec3Normalize( &vBoundFaceNormals[iFace], &vBoundFaceNormals[iFace] );

            fDot = D3DXVec3Dot( &vBoundFaceNormals[iFace], &vDeltaNorm );

            // If this face on pObject2 is pointing towards pObject
            if( fDot < 0.0f )
            {
                bBoundFaceShowing[iFace] = true;

                vBoundingFace[0] = p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][0]];
                vBoundingFace[1] = p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][1]];
                vBoundingFace[2] = p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][2]];
                vBoundingFace[3] = p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][3]];

                D3DXVECTOR3 vPtOnObject2;
                bool bObjectCollide = false;
                int nNumCollides = 0;
                for(;;)
                {
                    // Test each vertex on pObject against this face on pObject2
                    for( int i=0; i<8; i++ )
                    {
                        float fObj2PlaneD = D3DXVec3Dot(&vBoundingFace[0],&vBoundFaceNormals[iFace]);
                        float fObjPlaneD  = D3DXVec3Dot(&m_vBoundingVertexWorld[i],&vBoundFaceNormals[iFace]);
                        vPtOnBoundingPlaneNearestObject = m_vBoundingVertexWorld[i] - vBoundFaceNormals[iFace] * (fObjPlaneD - fObj2PlaneD);

                        if( IsPointInQuad( vPtOnBoundingPlaneNearestObject, vBoundingFace ) )
                        {
                            D3DXVECTOR3 vDist = m_vBoundingVertexWorld[i] - vPtOnBoundingPlaneNearestObject;
                            fDist = D3DXVec3Length(&vDist);

                            if( fDist < 0.4f )
                            {
                                if( p3DObject1->m_ObjectType == OBJ_BULLET &&
                                    p3DObject2->m_ObjectType == OBJ_ENEMY &&
                                    p3DObject1->m_bActive )
                                {
                                    p3DObject1->m_bActive = false;
                                    CEnemyShip* pEnemyShip = (CEnemyShip*) p3DObject2;
                                    CBullet* pBullet = (CBullet*) p3DObject1;
                                    if( pEnemyShip->m_fInvulnerableCountdown < 0.0f )
                                    {
                                        pEnemyShip->m_fHealth -= pBullet->m_pBulletParam->fDamage;
                                        pEnemyShip->m_fInvulnerableCountdown = g_Profile.aEnemyStyles[ pEnemyShip->m_dwStyle ].fInvulnerableCountdown;
                                        pEnemyShip->m_fHitAnimationCountdown = g_Profile.aEnemyStyles[ pEnemyShip->m_dwStyle ].fHitAnimationCountdown;  
                                    }
                                }

                                if( p3DObject1->m_ObjectType == OBJ_PLAYER &&
                                    p3DObject2->m_ObjectType == OBJ_ENEMY && 
                                    p3DObject2->m_fHealth > 0.0f )
                                {
                                    CEnemyShip* pEnemyShip = (CEnemyShip*) p3DObject2;
                                    CPlayerShip* pPlayerShip = (CPlayerShip*) p3DObject1;
                                    pPlayerShip->m_fShield -= g_Profile.aEnemyStyles[ pEnemyShip->m_dwStyle ].fDamage;
                                    pEnemyShip->m_fHealth = 0.0f;
                                }

                                HRESULT hr = ResolveCollsionWithObjectPt( p3DObject1, p3DObject2, 
                                                                        m_vBoundingVertexWorld[i], 
                                                                        vPtOnBoundingPlaneNearestObject, 
                                                                        vBoundFaceNormals[iFace] );
                                if( hr == APP_S_COLLIDING )
                                {
                                    bObjectCollide = true;
                                    break;
                                }
                            }
                        }
                    }

                    // Stop if there weren't any collisions found
                    if( !bObjectCollide )
                        break;

                    nNumCollides++;

                    // Keep going if there's a lot of collides (unlikely)
                    if( nNumCollides > 20 )
                        break;

                }
            }

            if( m_bRenderBoundingBox )
            {
                D3DXVECTOR3 vP;
                DWORD dwColor;
                if( bBoundFaceShowing[iFace] )
                    dwColor = 0xFF00FF00;
                else
                    dwColor = 0xFF0000FF;
                vP = p3DObject2->m_vBoundingVertexWorld[dwBoundFaces[iFace][0]] + v1 / 2.0f + v2 / 2.0f;
                g_p3DDrawManager->AddLine( vP, vP + vBoundFaceNormals[iFace],
                                        dwColor, m_dwID+10000, FALSE );
            }
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMoveFinalize()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::FrameMoveFinalize( const float fElapsedTime )
{
    // Switch m_pSource & m_pResult.  If implementing a algorithm to 
    // back time up upon penetration then don't do this here since this 
    // function is called on a per object basis, so accepting the new state 
    // would have to be done after all the object collisions have resolved.
    OBJECT_STATE* pTempState = m_pSource;
    m_pSource = m_pResult;
    m_pResult = pTempState;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CullObject()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::CullObject( const float fWrapOffsetX, const float fWrapOffsetZ, const CULLINFO* const pCullInfo )
{
    D3DXPLANE planeBoundsWorld[6];
    D3DXVECTOR3 vecBoundsWorld[8];

    memcpy( vecBoundsWorld, m_vBoundingVertexWorld, sizeof(D3DXVECTOR3)*8 );

    for( int i=0; i<8; i++ )
    {
        vecBoundsWorld[i].x += fWrapOffsetX;
        vecBoundsWorld[i].z += fWrapOffsetZ;
    }

    // Calc the planes of the bounding box
    D3DXPlaneFromPoints( &planeBoundsWorld[0], &vecBoundsWorld[0], &vecBoundsWorld[1], &vecBoundsWorld[2] ); // Near
    D3DXPlaneFromPoints( &planeBoundsWorld[1], &vecBoundsWorld[6], &vecBoundsWorld[7], &vecBoundsWorld[5] ); // Far
    D3DXPlaneFromPoints( &planeBoundsWorld[2], &vecBoundsWorld[2], &vecBoundsWorld[6], &vecBoundsWorld[4] ); // Left
    D3DXPlaneFromPoints( &planeBoundsWorld[3], &vecBoundsWorld[7], &vecBoundsWorld[3], &vecBoundsWorld[5] ); // Right
    D3DXPlaneFromPoints( &planeBoundsWorld[4], &vecBoundsWorld[2], &vecBoundsWorld[3], &vecBoundsWorld[6] ); // Top
    D3DXPlaneFromPoints( &planeBoundsWorld[5], &vecBoundsWorld[1], &vecBoundsWorld[0], &vecBoundsWorld[4] ); // Bottom

    m_cullstate = CTerrainEngine::CullObject( pCullInfo, vecBoundsWorld, planeBoundsWorld );

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: GetViewParams()
// Desc:
//-----------------------------------------------------------------------------
VOID C3DDisplayObject::GetViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt, D3DXVECTOR3* pvUpVec )
{
    // First person
    D3DXVECTOR3 vAheadLocal = D3DXVECTOR3(0.0,0.0f,1.0f);
    D3DXVECTOR3 vAheadWorld;
    D3DXVec3TransformNormal( &vAheadWorld, &vAheadLocal, &m_pSource->m_mOrientation ); 

    D3DXVECTOR3 vUpLocal = D3DXVECTOR3(0.0,1.0f,0.0f);
    D3DXVECTOR3 vUpWorld;
    D3DXVec3TransformNormal( &vUpWorld, &vUpLocal, &m_pSource->m_mOrientation ); 

    *pvEyePt    = m_pSource->m_vCMPos;
    *pvLookatPt = m_pSource->m_vCMPos + vAheadWorld;
    *pvUpVec    = vUpWorld;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::CheckForGroundCollsion()
{
    bool bGroundCollide = false;
    D3DXVECTOR3 v1;
    D3DXVECTOR3 v2;
    D3DXVECTOR3 vP;
    D3DXVECTOR3 vN;
    D3DXVECTOR3 vPtOnGround;
    D3DXVECTOR3 vPtOnBoundingPlaneNearestGround;
    const D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);

    if( m_bRenderBoundingBox )
    {
        g_p3DDrawManager->InvalidatePoints( m_dwID );
        g_p3DDrawManager->InvalidateLines( m_dwID );
    }

    int nNumCollides = 0;
    for(;;)
    {
        bGroundCollide = false;
        for( int i=0; i<8; i++ )
        {
            vPtOnGround = m_vBoundingVertexWorld[i];
            vPtOnGround.y = g_pTerrain->GetHeight( vPtOnGround.x, vPtOnGround.z );       

            HRESULT hr = ResolveCollsionWithGroundPt( m_vBoundingVertexWorld[i], vPtOnGround );
            if( hr == APP_S_COLLIDING )
            {
                bGroundCollide = true;
                break;
            }
        }

        // Stop if there weren't any collisions found
        if( !bGroundCollide )
            break;

        nNumCollides++;

        // Keep going if there's a lot of collides (unlikely)
        if( nNumCollides > 20 )
            break;

        // If there have been too many collides then
        // cheat a little by raising the object up
        if( nNumCollides > 10 )
        {
            for( int i=0; i<8; i++ )
            {
                float fDelta = g_pTerrain->GetHeight( m_vBoundingVertexWorld[i].x, m_vBoundingVertexWorld[i].z ) - m_vBoundingVertexWorld[i].y;
                if( fDelta > 0.0f )
                {
                    // Raise all bounding box points and m_vCMPos
                    for( int j=0; j<8; j++ )
                        m_vBoundingVertexWorld[j].y += fDelta;
                    m_pResult->m_vCMPos.y += fDelta;
                }
            }
        }
    }

    if( m_bRenderBoundingBox )
    {
        D3DXVECTOR3 vNormalsVertexWorld[12];
        DWORD dwBounding[24] = { 0,1, 2,3, 0,2, 1,3, 4,5, 6,7, 4,6, 5,7, 0,4, 2,6, 1,5, 3,7 };
        DWORD dwColor;
        if( bGroundCollide )
            dwColor = 0xFFFF0000;
        else
            dwColor = 0xFFFFFFFF;

        g_p3DDrawManager->InvalidateLines( m_dwID+10000 );
        for( int i=0; i<12; i++ )
        {
            g_p3DDrawManager->AddLine( m_vBoundingVertexWorld[ dwBounding[i*2] ],
                                       m_vBoundingVertexWorld[ dwBounding[i*2+1] ],
                                       dwColor, m_dwID+10000, FALSE );
        }

        static const DWORD dwBoundFaces[6][4] = { {0,1, 2,3},  // front 
                                {4,5, 0,1},  // bottom
                                {1,5, 3,7},  // right
                                {4,0, 6,2},  // left
                                {5,4, 7,6},  // back
                                {2,3, 6,7} };// top
        D3DXVECTOR3 vBoundFaceNormals[6];
        for( int iFace=3; iFace<4; iFace++ )
        {
            dwColor = 0xFF0000FF;

            D3DXVECTOR3 vP;
            D3DXVECTOR3 vN;
            D3DXVECTOR3 vP2;

            v1 = m_pModel->m_vBoundingVertex[dwBoundFaces[iFace][1]] - m_pModel->m_vBoundingVertex[dwBoundFaces[iFace][0]];
            v2 = m_pModel->m_vBoundingVertex[dwBoundFaces[iFace][2]] - m_pModel->m_vBoundingVertex[dwBoundFaces[iFace][0]];
            vP2 = m_pModel->m_vBoundingVertex[dwBoundFaces[iFace][0]] + v1 / 2.0f + v2 / 2.0f;
            D3DXVec3TransformNormal( &vP, &vP2, &m_pResult->m_mOrientation ); 
            vP += m_pResult->m_vCMPos;

            D3DXVec3Cross( &vN, &v2, &v1 );
            D3DXVec3Normalize( &vN, &vN );
            D3DXVec3TransformNormal( &vBoundFaceNormals[iFace], &vN, &m_pResult->m_mOrientation ); 

            g_p3DDrawManager->AddLine( vP, vP + vBoundFaceNormals[iFace],
                                    dwColor, m_dwID+10000, FALSE );
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ResolveCollsionWithGroundPt()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::ResolveCollsionWithGroundPt( const D3DXVECTOR3& vPtOnObjectWorld, const D3DXVECTOR3& vPtOnGround )
{
    if( vPtOnGround.y > vPtOnObjectWorld.y - 0.001f )    
    {
        // Colliding
        D3DXVECTOR3 vAngularVelPt;
        D3DXVECTOR3 vVelRelative;

        // Calc the pt location in local coords
        D3DXVECTOR3 vPtOnObjectLocal = vPtOnObjectWorld - m_pResult->m_vCMPos;

        // Calc the angular velocity of the pt
        D3DXVec3Cross( &vAngularVelPt, &m_pResult->m_vAngularVel, &vPtOnObjectLocal );

        // Combine the linear and angular velocity 
        vVelRelative = m_pResult->m_vCMVel + vAngularVelPt;

        // Calc ground normal
        D3DXVECTOR3 vGroundN;
        D3DXVECTOR3 vN = D3DXVECTOR3( vPtOnGround.x, g_pTerrain->GetHeight( vPtOnGround.x+0.0f, vPtOnGround.z+1.0f ), vPtOnGround.z+1.0f ) - vPtOnGround;
        D3DXVECTOR3 vE = D3DXVECTOR3( vPtOnGround.x+1.0f, g_pTerrain->GetHeight( vPtOnGround.x+1.0f, vPtOnGround.z+0.0f ), vPtOnGround.z ) - vPtOnGround;
        D3DXVec3Cross( &vGroundN, &vN, &vE );
        D3DXVec3Normalize( &vGroundN, &vGroundN );

        // Calc velocity projected against the ground normal
        float fVelRN = D3DXVec3Dot( &vVelRelative, &vGroundN );
        if( fVelRN < 0.0f )
        {
            // Object is moving towards ground

            // Calc impluse force
            // For more information: 
            //      June 1997 Game Developer Magazine article "Physics, Part 4: The Third Dimension" by Chris Hecker
            //      "Physics for Game Developers" by David M. Bourg
            //      SIGGRAPH '95 course "An Introduction to Physically Based Modeling" by David Baraff 
            //      "Classical Mechanics" by Herbert Goldstein
            D3DXVECTOR3 v1;
            D3DXVECTOR3 v2;
            D3DXVECTOR3 v3;
            D3DXVec3Cross( &v1, &vPtOnObjectLocal, &vGroundN );
            D3DXVec3TransformNormal( &v2, &v1, &m_pResult->m_mInverseWorldInertiaTensor );
            D3DXVec3Cross( &v3, &v2, &vPtOnObjectLocal );
            float f4 = D3DXVec3Dot( &vGroundN, &v3 );
            float fImpluseNumer = -(1.0f+m_fCr) * fVelRN;
            float fImpluseDenom = 1.0f/m_fMass + f4;

            // Ignore this force if there's going to be a divide by near zero (unlikely)
            if( fabsf( fImpluseDenom ) > 0.001f )
            {
                float fImpulse = fImpluseNumer / fImpluseDenom;

                // Calc collision response vector
                D3DXVECTOR3 vCollisionResponse = fImpulse * vGroundN;

                // Calc collision 
                D3DXVECTOR3 vAngularMomemtumResponse;
                D3DXVec3Cross( &vAngularMomemtumResponse, &vPtOnObjectLocal, &vCollisionResponse );
                m_pResult->m_vAngularMomentum += vAngularMomemtumResponse;

                // Add impulse collision response to velocity
                m_pResult->m_vCMVel += vCollisionResponse / m_fMass;

                // Update angular velocity based on angular momentum and 
                // the inverse world inertia tensor.
                D3DXVec3TransformNormal( &m_pResult->m_vAngularVel, &m_pResult->m_vAngularMomentum, 
                                         &m_pResult->m_mInverseWorldInertiaTensor );

                return APP_S_COLLIDING;
            }
        }
    }

    return APP_S_NOCOLLIDE;
}




//-----------------------------------------------------------------------------
// Name: ResolveCollsionWithGroundPt()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::ResolveCollsionWithObjectPt( const C3DDisplayObject* pObject1, const C3DDisplayObject* pObject2, const D3DXVECTOR3& vPtOnObject1World, const D3DXVECTOR3& vPtOnObject2World, const D3DXVECTOR3& vObject2FaceNormal )
{
    // Colliding
    D3DXVECTOR3 vAngularVelPt;
    D3DXVECTOR3 vVelRelative;

    // Calc the pt location in local coords
    D3DXVECTOR3 vPtOnObject1Local = vPtOnObject1World - pObject1->m_pResult->m_vCMPos;

    // Calc the angular velocity of the pt
    D3DXVec3Cross( &vAngularVelPt, &pObject1->m_pResult->m_vAngularVel, &vPtOnObject1Local );

    // Combine the linear and angular velocity 
    vVelRelative = pObject1->m_pResult->m_vCMVel + vAngularVelPt;

    // Calc velocity projected against the object2 face normal
    float fVelRN = D3DXVec3Dot( &vVelRelative, &vObject2FaceNormal );
    if( fVelRN < 0.0f )
    {
        if( pObject1->m_bRenderBoundingBox )
        {
            g_p3DDrawManager->AddLine( vPtOnObject1World, vPtOnObject2World,
                                        0xFFFF0000, pObject1->m_dwID, TRUE );
        }

        // Object is moving towards object2's face

        // Calc impluse force
        // For more information: 
        //      June 1997 Game Developer Magazine article "Physics, Part 4: The Third Dimension" by Chris Hecker
        //      "Physics for Game Developers" by David M. Bourg
        //      SIGGRAPH '95 course "An Introduction to Physically Based Modeling" by David Baraff 
        //      "Classical Mechanics" by Herbert Goldstein
        D3DXVECTOR3 v1;
        D3DXVECTOR3 v2;
        D3DXVECTOR3 v3;
        D3DXVec3Cross( &v1, &vPtOnObject1Local, &vObject2FaceNormal );
        D3DXVec3TransformNormal( &v2, &v1, &pObject1->m_pResult->m_mInverseWorldInertiaTensor );
        D3DXVec3Cross( &v3, &v2, &vPtOnObject1Local );
        float f4 = D3DXVec3Dot( &vObject2FaceNormal, &v3 );
        float fImpluseNumer = -(1.0f+pObject1->m_fCr) * fVelRN;
        float fImpluseDenom = 1.0f/pObject1->m_fMass + f4;

        // Ignore this force if there's going to be a divide by near zero (unlikely)
        if( fabsf( fImpluseDenom ) > 0.001f )
        {
            float fImpulse = fImpluseNumer / fImpluseDenom;

            // Calc collision response vector
            D3DXVECTOR3 vCollisionResponse = fImpulse * vObject2FaceNormal;

            // Calc collision impact on object1
            D3DXVECTOR3 vAngularMomemtumResponse;                
            D3DXVec3Cross( &vAngularMomemtumResponse, &vPtOnObject1Local, &vCollisionResponse );
            pObject1->m_pResult->m_vAngularMomentum += vAngularMomemtumResponse;

            // Add impulse collision response to velocity
            pObject1->m_pResult->m_vCMVel += vCollisionResponse / pObject1->m_fMass;

            // Update angular velocity based on angular momentum and 
            // the inverse world inertia tensor.
            D3DXVec3TransformNormal( &pObject1->m_pResult->m_vAngularVel, &pObject1->m_pResult->m_vAngularMomentum, 
                                        &pObject1->m_pResult->m_mInverseWorldInertiaTensor );


            // Calc collision impact on object2
            vCollisionResponse = -vCollisionResponse;
            D3DXVECTOR3 vPtOnObject2Local = vPtOnObject2World - pObject2->m_pSource->m_vCMPos;
            D3DXVec3Cross( &vAngularMomemtumResponse, &vPtOnObject2Local, &vCollisionResponse );
            pObject2->m_pSource->m_vAngularMomentum += vAngularMomemtumResponse;

            // Add impulse collision response to velocity
            pObject2->m_pSource->m_vCMVel += vCollisionResponse / pObject2->m_fMass;

            // Update angular velocity based on angular momentum and 
            // the inverse world inertia tensor.
            D3DXVec3TransformNormal( &pObject2->m_pSource->m_vAngularVel, &pObject2->m_pSource->m_vAngularMomentum, 
                                        &pObject2->m_pSource->m_mInverseWorldInertiaTensor );

            return APP_S_COLLIDING;
        }
    }

    return APP_S_NOCOLLIDE;
}




//-----------------------------------------------------------------------------
// Name: ArePointsSameSideOfLine()
// Desc:
//-----------------------------------------------------------------------------
bool C3DDisplayObject::ArePointsSameSideOfLine( const D3DXVECTOR3* pvP1, const D3DXVECTOR3* pvP2, const D3DXVECTOR3* pvA, const D3DXVECTOR3* pvB )
{
    D3DXVECTOR3 v1 = *pvB - *pvA;
    D3DXVECTOR3 v2 = *pvP1 - *pvA;
    D3DXVECTOR3 v3 = *pvP2 - *pvA;
    D3DXVECTOR3 v4;
    D3DXVECTOR3 v5;

    D3DXVec3Cross(&v4,&v1,&v2);
    D3DXVec3Cross(&v5,&v1,&v3);

    if( D3DXVec3Dot( &v4, &v5 ) >= 0.0f )
        return true;   
    return false;
}




//-----------------------------------------------------------------------------
// Name: IsPointInTriangle()
// Desc:
//-----------------------------------------------------------------------------
bool C3DDisplayObject::IsPointInTriangle( const D3DXVECTOR3* pvPt, const D3DXVECTOR3* pA, const D3DXVECTOR3* pB, const D3DXVECTOR3* pC )
{
    if( ArePointsSameSideOfLine( pvPt, pA, pB, pC ) &&
        ArePointsSameSideOfLine( pvPt, pB, pA, pC ) &&
        ArePointsSameSideOfLine( pvPt, pC, pA, pB ) )
        return true;

    return false;
}




//-----------------------------------------------------------------------------
// Name: IsPointInQuad()
// Desc:
//-----------------------------------------------------------------------------
bool C3DDisplayObject::IsPointInQuad( const D3DXVECTOR3& vPt, const D3DXVECTOR3* pvQuad )
{
    if( IsPointInTriangle( &vPt, &pvQuad[0], &pvQuad[1], &pvQuad[2] ) ||
        IsPointInTriangle( &vPt, &pvQuad[1], &pvQuad[2], &pvQuad[3] ) )
        return true;

    return false;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::InvalidateDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT C3DDisplayObject::DeleteDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc:
//-----------------------------------------------------------------------------
VOID C3DDisplayObject::FinalCleanup()
{
    if( m_bRenderBoundingBox )
    {
        g_p3DDrawManager->InvalidateLines( m_dwID+10000 );
        g_p3DDrawManager->InvalidatePoints( m_dwID );
        g_p3DDrawManager->InvalidateLines( m_dwID );
    }
}


