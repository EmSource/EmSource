//-----------------------------------------------------------------------------
// File: 3DModel.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

struct LINELIST_VERTEX
{
    D3DXVECTOR3 p;
    DWORD		c;
};
#define LINELIST_FVF             (D3DFVF_XYZ|D3DFVF_DIFFUSE)

class C3DModel
{
public:
    C3DModel(void);
    ~C3DModel(void);

    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects( TCHAR* strModelName, const BOOL bCreateTest, float fBoundingScale );
    HRESULT RestoreDeviceObjects();
    HRESULT Render( DWORD* pdwNumVerts );
    HRESULT RenderBoundingBox();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    VOID    FinalCleanup();

public:
    CD3DMesh*           m_pMesh;

    D3DXVECTOR3         m_vBoundingMin;
    D3DXVECTOR3         m_vBoundingMax;
    D3DXVECTOR3         m_vCenter;
    float               m_fRadius;
    DWORD               m_dwNumFaces;

    D3DXVECTOR3         m_vBoundingVertex[8];
	LPDIRECT3DVERTEXBUFFER9 m_pBoundingVB;
};
