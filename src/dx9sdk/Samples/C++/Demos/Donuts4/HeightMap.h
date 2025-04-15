//-----------------------------------------------------------------------------
// File: heightmap.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

#define MAX_HEIGHT_OF_MAP  1000.0f
#define ZONE_WIDTH          64
#define ZONE_HEIGHT         64

class CTerrainEngine;

class CHeightMap  
{
public:
    CHeightMap( CTerrainEngine* pTerrainEngine, float fWorldOffsetX, float fWorldOffsetZ );
    virtual ~CHeightMap();

    HRESULT Create( int nHeight, int nWidth ); 
    HRESULT CreateFromFile( TCHAR* strFileName );
    FLOAT   GetHeightObj( float fObjCoordX, float fObjCoordZ );

    BOOL    IsOutOfRangeObj( float x, float z );
    float   GetCellHeightObj( float x, float z );
    BOOL    IsOutOfRangeObj( int x, int z );
    float   GetCellHeightObj( int x, int z );

    HRESULT SmoothMap();
    HRESULT FinalizeSmooth();

    VOID    CreateSmallHills(); 
    VOID    CreateMountain();
    VOID    CreateTestMap( FLOAT fHeight );
    
protected:   
    HRESULT SmoothSingleMap();
    VOID    RaiseLand( int iCenterX, int iCenterZ, float fRadius, float fHeight );

public:
    int     m_nZSize;
    int     m_nXSize;
    FLOAT   m_fZSize;
    FLOAT   m_fXSize;

    FLOAT*  m_pMap;
    FLOAT*  m_pSmoothMap;

    CTerrainEngine* g_pTerrainEngine;
    FLOAT           m_fWorldOffsetX;
    FLOAT           m_fWorldOffsetZ;
};
