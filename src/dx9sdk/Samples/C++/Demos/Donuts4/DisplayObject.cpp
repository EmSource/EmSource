//-----------------------------------------------------------------------------
// File: DisplayObject.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: CDisplayObject()
// Desc:
//-----------------------------------------------------------------------------
CDisplayObject::CDisplayObject( const OBJECT_TYPE ObjectType )
{
    static DWORD s_dwID = 0;
    s_dwID++;

    m_ObjectType    = ObjectType;
    m_bActive       = true;
    m_pNext         = NULL;
    m_pPrev         = NULL;
    m_vPos          = D3DXVECTOR3(0,0,0);
    m_pMeshNode     = NULL;
    m_dwID          = s_dwID;
    m_pPath         = NULL;
    m_fDistToPlayer = 0.0f;
    m_cullstate     = CS_UNKNOWN;
}




//-----------------------------------------------------------------------------
// Name: CDisplayObject()
// Desc:
//-----------------------------------------------------------------------------
CDisplayObject::~CDisplayObject(void)
{
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CDisplayObject::OneTimeSceneInit()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CDisplayObject::InitDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CDisplayObject::RestoreDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMoveFinalize()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CDisplayObject::FrameMoveFinalize( const float fElapsedTime )
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CullObject()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CDisplayObject::CullObject( const float fWrapOffsetX, const float fWrapOffsetZ, const CULLINFO* const pCullInfo )
{
    m_cullstate = CS_INSIDE;
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CDisplayObject::InvalidateDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CDisplayObject::DeleteDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc:
//-----------------------------------------------------------------------------
VOID CDisplayObject::FinalCleanup()
{
}





