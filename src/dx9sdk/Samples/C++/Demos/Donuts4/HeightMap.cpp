//-----------------------------------------------------------------------------
// File: heightmap.cpp
//
// Desc: Class to read a height map from a file or create one using a simple
//       function.
//
// Copyright (C) 1995-2001 Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"

extern float g_fVar1;




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CHeightMap::CHeightMap( CTerrainEngine* pTerrainEngine, float fWorldOffsetX, float fWorldOffsetZ )
{
    m_nXSize = 0;
    m_nZSize = 0;
    m_fXSize = 0.0f;
    m_fZSize = 0.0f;
    m_pMap   = NULL;
    g_pTerrainEngine = pTerrainEngine;
    m_fWorldOffsetX  = fWorldOffsetX;
    m_fWorldOffsetZ  = fWorldOffsetZ;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CHeightMap::~CHeightMap()
{
    SAFE_DELETE_ARRAY( m_pMap );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CHeightMap::Create( int nXSize, int nZSize )
{
    m_nXSize = nXSize;
    m_nZSize = nZSize;
    m_fXSize = (float) m_nXSize;
    m_fZSize = (float) m_nZSize;

    m_pMap   = new FLOAT[ m_nXSize * m_nZSize ];
    if( m_pMap == NULL )
        return E_OUTOFMEMORY;

    ZeroMemory( m_pMap, m_nXSize * m_nZSize * sizeof(FLOAT) );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CHeightMap::CreateTestMap( FLOAT fHeight )
{
    for( int iZ=0; iZ<m_nZSize; iZ++ )
    {
        for( int iX=0; iX<m_nXSize; iX++ )
        {
            m_pMap[ iZ*m_nXSize + iX ] = fHeight;
        }
    }

    if( fHeight == 0.0f )
    {
        for( int iZ=5; iZ<40; iZ++ )
        {
            for( int iX=5; iX<40; iX++ )
            {
                m_pMap[ iZ*m_nXSize + iX ] = 10.0f;
            }
        }

        for( iZ=6; iZ<39; iZ++ )
        {
            for( int iX=6; iX<39; iX++ )
            {
                m_pMap[ iZ*m_nXSize + iX ] += 2.0f;
            }
        }

    }
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CHeightMap::CreateMountain()
{
    CreateSmallHills();

    int iCenterX = m_nXSize/2;
    int iCenterZ = m_nZSize/2;

    RaiseLand( iCenterX, iCenterZ, 9.0f, 1.0f );
    RaiseLand( iCenterX, iCenterZ, 7.0f, 2.0f );
    RaiseLand( iCenterX, iCenterZ, 5.0f, 4.0f );
    RaiseLand( iCenterX, iCenterZ, 4.0f, 1.0f );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CHeightMap::RaiseLand( int iCenterX, int iCenterZ, float fRadius, float fHeight )
{
    for( float fAngle=0.0f; fAngle<3.14f*2.0f; fAngle += 0.1f )
    {
        int fIncX = (int) (cos(fAngle) * fRadius);
        int fIncZ = (int) (sin(fAngle) * fRadius);

        int iX = iCenterX+fIncX;
        int iZ = iCenterZ+fIncZ;

        if( !IsOutOfRangeObj( iX, iZ ) )
            m_pMap[ iZ*m_nXSize + iX ] += fHeight;
    }
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CHeightMap::CreateSmallHills()
{
    int i;

    for( i=0; i<1500; i++ )
    {
        int iX = rand() % (m_nXSize-1);
        int iZ = rand() % (m_nZSize-1);
        float fIncSize = 2.0f;
        if( m_pMap[ iZ*m_nXSize + iX ] + fIncSize < MAX_HEIGHT_OF_MAP )
            m_pMap[ iZ*m_nXSize + iX ] += fIncSize;
    }
    for( i=0; i<500; i++ )
    {
        int iX = rand() % (m_nXSize-1);
        int iZ = rand() % (m_nZSize-1);
        float fIncSize = 1.0f;
        if( m_pMap[ iZ*m_nXSize + iX ] + fIncSize < MAX_HEIGHT_OF_MAP )
            m_pMap[ iZ*m_nXSize + iX ] += fIncSize;
    }

    SmoothSingleMap();
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CHeightMap::CreateFromFile( TCHAR* strFileName )
{
    HRESULT hr;

    D3DSURFACE_DESC desc;
    IDirect3DTexture9* pTexture = NULL;

    // Create a D3DFMT_R5G6B5 texture -- use D3DPOOL_SCRATCH to 
    // ensure that this will succeeded independent of the device
    hr = D3DXCreateTextureFromFileEx( g_pd3dDevice, strFileName, 
                                 ZONE_WIDTH, ZONE_HEIGHT, 1, 0, 
                                 D3DFMT_R5G6B5, D3DPOOL_SCRATCH, 
                                 D3DX_FILTER_NONE, D3DX_FILTER_NONE,
                                 0, NULL, NULL, &pTexture );
    if( FAILED(hr) )
        return hr;

    pTexture->GetLevelDesc( 0, &desc ); 

    m_nXSize = desc.Width;
    m_nZSize = desc.Height;
    m_fXSize = (float) m_nXSize;
    m_fZSize = (float) m_nZSize;

    assert( desc.Format == D3DFMT_R5G6B5 );

    // create an array of floats to store the values of the bmp
    m_pMap = new FLOAT[ m_nXSize * m_nZSize ];
    if( m_pMap == NULL )
    {
        SAFE_RELEASE( pTexture );
        return E_OUTOFMEMORY;
    }

    ZeroMemory( m_pMap, m_nXSize * m_nZSize * sizeof(FLOAT) );

    D3DLOCKED_RECT lockedRect;

    hr = pTexture->LockRect( 0, &lockedRect, NULL, D3DLOCK_READONLY );
    if( SUCCEEDED(hr) )
    {
        WORD* pBuffer = (WORD*) lockedRect.pBits;
        for( DWORD iY=0; iY<desc.Height; iY++ )
        {
            pBuffer = (WORD*) ((BYTE*)lockedRect.pBits + lockedRect.Pitch * iY);

            for( DWORD iX=0; iX<desc.Width; iX++ )
            {
                // Normalize the values between 0.0f and 1.0f
                FLOAT fValue = (float)(*pBuffer) / (float) 0xFFFF;

                // Invert Y, so it appears the same as the bmp
                m_pMap[ (desc.Height-1-iY)*m_nXSize + iX] = fValue * 50.0f;
                pBuffer++;
            }
        }

        pTexture->UnlockRect( 0 );
    }
                                 
    SAFE_RELEASE( pTexture );
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CHeightMap::SmoothSingleMap()
{
    // Smooth the map so its not so jaggy
    FLOAT* pSmoothMap = new FLOAT[ m_nXSize * m_nZSize ];
    if( pSmoothMap == NULL )
        return E_OUTOFMEMORY;

    for( float iZ=0.0f; iZ<m_nZSize; iZ++ )
    {
        for( float iX=0.0f; iX<m_nXSize; iX++ )
        {
            float fAvg;

            if( iZ==0.0f || iX==0.0f || 
                iZ==m_nZSize-1 || iX==m_nXSize-1 )
            {
                // Don't smoooth the edges cause they neighbor 
                // maps haven't been created yet, and if we use 0 for
                // the 'off the map' values, it will change the height
                // around the border
                fAvg = GetCellHeightObj( iX, iZ );
            }
            else
            {
                // 3x3 smooth the middle
                FLOAT f11 = GetCellHeightObj( iX-1, iZ-1 );
                FLOAT f12 = GetCellHeightObj( iX-1, iZ-0 );
                FLOAT f13 = GetCellHeightObj( iX-1, iZ+1 );

                FLOAT f21 = GetCellHeightObj( iX-0, iZ-1 );
                FLOAT f22 = GetCellHeightObj( iX-0, iZ-0 );
                FLOAT f23 = GetCellHeightObj( iX-0, iZ+1 );

                FLOAT f31 = GetCellHeightObj( iX+1, iZ-1 );
                FLOAT f32 = GetCellHeightObj( iX+1, iZ-0 );
                FLOAT f33 = GetCellHeightObj( iX+1, iZ+1 );

                fAvg = (f22+f12+f21+f23+f32+f11+f13+f31+f33)/9.0f;
            }

            pSmoothMap[ (int) (iZ*m_nXSize + iX) ] = fAvg;
        }
    }

    SAFE_DELETE_ARRAY( m_pMap );
    m_pMap = pSmoothMap;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CHeightMap::SmoothMap()
{
    // Smooth the map so its not so jaggy
    m_pSmoothMap = new FLOAT[ m_nXSize * m_nZSize ];
    if( m_pSmoothMap == NULL )
        return E_OUTOFMEMORY;

    for( float iZ=m_fWorldOffsetZ; iZ<m_fWorldOffsetZ+m_nZSize; iZ++ )
    {
        for( float iX=m_fWorldOffsetX; iX<m_fWorldOffsetX+m_nXSize; iX++ )
        {
            float fAvg;

            // 3x3 -- use g_pTerrainEngine to have it ask the right map what the cell value is
            FLOAT f11 = g_pTerrainEngine->GetHeight( iX-1, iZ-1 );
            FLOAT f12 = g_pTerrainEngine->GetHeight( iX-1, iZ-0 );
            FLOAT f13 = g_pTerrainEngine->GetHeight( iX-1, iZ+1 );

            FLOAT f21 = g_pTerrainEngine->GetHeight( iX-0, iZ-1 );
            FLOAT f22 = g_pTerrainEngine->GetHeight( iX-0, iZ-0 );
            FLOAT f23 = g_pTerrainEngine->GetHeight( iX-0, iZ+1 );

            FLOAT f31 = g_pTerrainEngine->GetHeight( iX+1, iZ-1 );
            FLOAT f32 = g_pTerrainEngine->GetHeight( iX+1, iZ-0 );
            FLOAT f33 = g_pTerrainEngine->GetHeight( iX+1, iZ+1 );

            fAvg = (f22+f12+f21+f23+f32+f11+f13+f31+f33)/9.0f;
            m_pSmoothMap[ (int) ((iZ-m_fWorldOffsetZ)*m_nXSize + (iX-m_fWorldOffsetX)) ] = fAvg;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CHeightMap::FinalizeSmooth()
{
    SAFE_DELETE_ARRAY( m_pMap );
    m_pMap = m_pSmoothMap;

    return S_OK;  
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
BOOL CHeightMap::IsOutOfRangeObj( float x, float z )
{
    if( x < 0.0f        || 
        z < 0.0f        ||
        x >= m_fXSize   || 
        z >= m_fZSize )
        return TRUE;
    
    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
BOOL CHeightMap::IsOutOfRangeObj( int x, int z )
{
    if( x < 0           || 
        z < 0           ||
        x >= m_nXSize   || 
        z >= m_nZSize )
        return TRUE;
    
    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
float CHeightMap::GetCellHeightObj( float x, float z )
{
    // If we're trying to access out of range for this zone, then ask the engine 
    // for the height of this coord, and it will find the zone that this coord lies 
    // in and ask it.
    if( IsOutOfRangeObj( x, z ) )
        return g_pTerrainEngine->GetHeight( x + m_fWorldOffsetX, z + m_fWorldOffsetZ );

    return m_pMap[ (int) (z*m_fXSize + x) ]; 
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
float CHeightMap::GetCellHeightObj( int x, int z )
{
    if( IsOutOfRangeObj( x, z ) )
        return 0.0f;

    return m_pMap[ z*m_nXSize + x ]; 
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
FLOAT CHeightMap::GetHeightObj( float fObjCoordX, float fObjCoordZ ) 
{ 
    // Do sub-cell calculation to find the exact height at this location 
    float fXLow   = (float) floor(fObjCoordX);
    float fXHigh  = (float) ceil(fObjCoordX);
    float fZLow   = (float) floor(fObjCoordZ);
    float fZHigh  = (float) ceil(fObjCoordZ);

    if( fXLow == fXHigh && fZLow == fZHigh )
    {
        return GetCellHeightObj( fXHigh, fZHigh );
    }
    else
    {
        float fPtHH = GetCellHeightObj( fXHigh, fZHigh );
        float fPtHL = GetCellHeightObj( fXHigh, fZLow ); 
        float fPtLH = GetCellHeightObj( fXLow,  fZHigh ); 
        float fPtLL = GetCellHeightObj( fXLow,  fZLow ); 

        float fWeightX  = fObjCoordX - fXLow;
        float fWeightZ  = fObjCoordZ - fZLow;

        float fAvgZ_H   = fPtHH*fWeightX + fPtLH*(1.0f-fWeightX);       // avg( HH -> LH )
        float fAvgZ_L   = fPtHL*fWeightX + fPtLL*(1.0f-fWeightX);       // avg( HL -> LL )
        float fAvg      = fAvgZ_H*fWeightZ + fAvgZ_L*(1.0f-fWeightZ);   // avg( Z_H -> Z_L )

        return fAvg;
    }
}

