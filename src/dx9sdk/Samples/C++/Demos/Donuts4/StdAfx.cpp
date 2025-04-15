//----------------------------------------------------------------------------
// File: stdafx.cpp
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#define INITGUID
#include "stdafx.h"
#include <RMXFGUID.H>

// For debugging
D3DXVECTOR3     g_vDebugMove                = D3DXVECTOR3(0,0,0);
D3DXVECTOR3     g_vDebugRotate              = D3DXVECTOR3(0,0,0);
BOOL            g_bDebugIsZoneRenderFroze   = FALSE;
BOOL            g_bDebugFreezeZoneRender    = FALSE;     
CEnemyShip*     g_pDebugFirstEnemy          = NULL;            



D3DXMATRIX* Donuts_MatrixOrthroNormalize( D3DXMATRIX* pOut, D3DXMATRIX* pM )
{
    D3DXVECTOR3 vOrientationX = D3DXVECTOR3(pM->_11, pM->_21, pM->_31);
    D3DXVECTOR3 vOrientationY = D3DXVECTOR3(pM->_12, pM->_22, pM->_32);
    D3DXVECTOR3 vOrientationZ;
    D3DXVec3Normalize( &vOrientationX, &vOrientationX );
    D3DXVec3Cross( &vOrientationZ, &vOrientationX, &vOrientationY );
    D3DXVec3Cross( &vOrientationY, &vOrientationZ, &vOrientationX );
    D3DXVec3Normalize( &vOrientationZ, &vOrientationZ );
    D3DXVec3Normalize( &vOrientationY, &vOrientationY );

    pOut->_11 = vOrientationX.x;
    pOut->_12 = vOrientationY.x;
    pOut->_13 = vOrientationZ.x;
    pOut->_14 = 0.0f;
    pOut->_21 = vOrientationX.y;
    pOut->_22 = vOrientationY.y;
    pOut->_23 = vOrientationZ.y;
    pOut->_24 = 0.0f;
    pOut->_31 = vOrientationX.z;
    pOut->_32 = vOrientationY.z;
    pOut->_33 = vOrientationZ.z;
    pOut->_34 = 0.0f;
    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = 0.0f;
    pOut->_44 = 1.0f;

    return pOut;
}