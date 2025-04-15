//----------------------------------------------------------------------------
// File: TerrainMesh.h
//
// Desc: Class that owns d3d mesh and the heightmap that created it
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

#include "HeightMap.h"

struct TERRIANVERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR3 n;
    FLOAT       tu, tv;
};

struct RHW_VERTEX
{
    D3DXVECTOR4 p;
    FLOAT       tu1, tv1;
    FLOAT       tu2, tv2;
};

#define TERRIAN_FVF         (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)
#define RHW_FVF             (D3DFVF_XYZRHW|D3DFVF_TEX2)

class CTerrainEngine;

class CTerrainMesh  
{
public:
    CTerrainMesh( CTerrainEngine* pTerrainEngine );
    virtual ~CTerrainMesh();

    HRESULT OneTimeSceneInit( CZoneStyleParameter* pLandStyle, const float fWorldOffsetX, const float fWorldOffsetZ, CTerrainMesh* pNorth, CTerrainMesh* pEast, CTerrainMesh* pNorthEast );
    HRESULT InitDeviceObjects( D3DFORMAT fmtTexture );
    HRESULT RestoreDeviceObjects( HWND hWndMain );
    HRESULT FrameMove( const float fElapsedTime );
    HRESULT RenderFrame( const float fWrapOffsetX, const float fWrapOffsetZ, DWORD* pdwNumVerts );
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    VOID    FinalCleanup();

    HRESULT SmoothMap() { return m_pMap->SmoothMap(); };
    HRESULT FinalizeSmooth() { return m_pMap->FinalizeSmooth(); };

    HRESULT CreateMeshFromHeightMap( int nWidth, int nHeight );

    HRESULT ReadTextureFromFile( int nWidth, int nHeight );
    HRESULT CreateTextureFromHeight( int nWidth, int nHeight );
    FLOAT   TextureColorFactor( DWORD iTexture, float fValue );

    HRESULT CreateTextureFromLayers( int nWidth, int nHeight );
    BYTE    TextureAlpha( float fHeight, int nIndex );

    HRESULT CreateTestTexture( int nWidth, int nHeight );

    HRESULT CorrectTextureEdge();
    HRESULT GenerateMipMaps();

    inline FLOAT GetHeightWorld( float x, float z ) { return m_pMap->GetHeightObj( x-m_fWorldOffsetX, z-m_fWorldOffsetZ ); };
    inline FLOAT GetHeightObj( float x, float z ) { return m_pMap->GetHeightObj( x, z ); };
    inline BOOL  IsOutOfRangeWorld( float x, float z ) { return m_pMap->IsOutOfRangeObj( x-m_fWorldOffsetX, z-m_fWorldOffsetZ ); };
    inline BOOL  IsOutOfRangeObj( float x, float z ) { return m_pMap->IsOutOfRangeObj( x, z ); };

    DWORD GetTexelColor( DWORD iLevel, float x, float z );
    HRESULT SaveMeshToXFile();
    HRESULT SaveTextureToFile();

    CZoneStyleParameter* m_pLandStyle;

    CHeightMap*         m_pMap;
    ID3DXMesh*          m_pMesh;
    DWORD               m_dwNumFaces;
    DWORD               m_dwNumVerties;
    FLOAT               m_fWorldOffsetX;
    FLOAT               m_fWorldOffsetZ;
    D3DXMATRIX          m_matWorld;
    CTerrainMesh*       m_pNorth;
    CTerrainMesh*       m_pEast;
    CTerrainMesh*       m_pNorthEast;
    CTerrainEngine*     g_pTerrainEngine;
    D3DFORMAT           m_fmtTexture;
    LPDIRECT3DTEXTURE9  m_pTexture;       
};

