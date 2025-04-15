//-----------------------------------------------------------------------------
// File: DisplayObject.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Name: enum OBJECT_TYPE
// Desc: Game object types
//-----------------------------------------------------------------------------
enum OBJECT_TYPE
{ 
    OBJ_ENEMY, 
    OBJ_PLAYER, 
    OBJ_BULLET,
    OBJ_PARTICLE,
    OBJ_SPRITE
};

class C3DAudioPath;

class CDisplayObject
{
public:
    CDisplayObject( const OBJECT_TYPE ObjectType );
    virtual ~CDisplayObject(void);
    
    virtual HRESULT OneTimeSceneInit();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT FrameMove( const float fElapsedTime ) = 0;
    virtual HRESULT HandleNearbyObject( const float fElapsedTime, CDisplayObject* pObject ) = 0;
    virtual HRESULT FrameMoveFinalize( const float fElapsedTime );
    virtual HRESULT CullObject( const float fWrapOffsetX, const float fWrapOffsetZ, const CULLINFO* const pCullInfo );
    virtual HRESULT Render( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts ) = 0;
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual VOID    FinalCleanup();

public:
    CDisplayObject*     m_pNext;            // Link to next object
    CDisplayObject*     m_pPrev;            // Link to previous object
    D3DXVECTOR3         m_vPos;             // Position of center of mass in world coords
    OBJECT_TYPE         m_ObjectType;       // Type of object
    bool                m_bActive;          // Is the object active
    CTerrainEngine::MESH_NODE* m_pMeshNode; // The mesh the object is in
    DWORD               m_dwID;
    C3DAudioPath*       m_pPath;
    CULLSTATE           m_cullstate;
    float               m_fDistToPlayer;
};
