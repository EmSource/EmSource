//----------------------------------------------------------------------------
// File: terrainengine.h
//
// Desc: Class that owns all the terrian mesh objects and all 
//       the game objects. 
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

class CTerrainMesh;

#define MAX_VIEW_ZONE_X 21
#define MAX_VIEW_ZONE_Z 21

class CDisplayObject;

//-----------------------------------------------------------------------------
// Name: enum CULLSTATE
// Desc: Represents the result of the culling calculation on an object.
//-----------------------------------------------------------------------------
enum CULLSTATE
{
    CS_UNKNOWN,      // cull state not yet computed
    CS_INSIDE,       // object bounding box is at least partly inside the frustum
    CS_OUTSIDE       // object bounding box is outside the frustum
};


//-----------------------------------------------------------------------------
// Name: struct CULLINFO
// Desc: Stores information that will be used when culling objects.  It needs
//       to be recomputed whenever the view matrix or projection matrix changes.
//-----------------------------------------------------------------------------
struct CULLINFO
{
    D3DXVECTOR3 vecFrustum[8];    // corners of the view frustum
    D3DXPLANE planeFrustum[6];    // planes of the view frustum
};


class CTerrainEngine  
{
public:
    struct MESH_NODE
    {
        CTerrainMesh*   pMesh;
        CDisplayObject* pDisplayList;
        BOOL            bVisited;
    };

    struct VIEW_NODE
    {        
        bool        bValid;
        bool        bVisited;
        bool        bInView;
        CULLSTATE   cullstate;
        float       fZonePosX;
        float       fZonePosZ;
        int         iWorldX;
        int         iWorldZ;
        int         iZoneX;
        int         iZoneZ;
        D3DXVECTOR3 vecBoundsWorld[8];
        D3DXPLANE   planeBoundsWorld[6];
    };

public:
    CTerrainEngine( CMyApplication* pApp );
    virtual ~CTerrainEngine();

    HRESULT OneTimeSceneInit( CThemeStyle* pTheme );
    HRESULT InitDeviceObjects( D3DFORMAT fmtTexture );
    HRESULT RestoreDeviceObjects( HWND hWndMain );
    HRESULT FrameMove( const float fElapsedTime );
    HRESULT RenderFrame( DWORD* pdwNumVerts, CD3DCamera* pCam );
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    VOID    FinalCleanup();

    FLOAT   GetHeight( float x, float z );
    DWORD   GetTexelColor( DWORD iLevel, float x, float z );
    VOID    GetWrapOffset( float fPosX, float fPosZ, float* fOffsetX, float* fOffsetZ );
    VOID    RenderZone( int iWorldX, int iWorldZ, int iZoneX, int iZoneZ, BOOL bRenderObjects, BOOL bRenderTerrain, BOOL bCullObjects );

    static CULLSTATE CullObject( const CULLINFO* const pCullInfo, const D3DXVECTOR3* const pVecBounds, const D3DXPLANE* const pPlaneBounds );
    static BOOL      EdgeIntersectsFace( const D3DXVECTOR3* const pEdges, const D3DXVECTOR3* const pFacePoints, const D3DXPLANE* const pPlane );

    VOID    GetWorldFromPt( const float fX, const float fZ, int* pnWorldX, int* pnWorldZ );
    VOID    GetZoneFromPt( const float fX, const float fZ, int* pnZoneX, int* pnZoneZ );
    VOID    GetWorldFromUniversal( float fUniversalX, float fUniversalZ, float* pfWorldX, float* pfWorldZ );
    BOOL    CheckIfZoneInView( const float fZonePosX, const float fZonePosZ, const int iZoneIndexX, const int iZoneIndexZ );

    HRESULT RenderRadar( LPDIRECT3DTEXTURE9 pRadarTexture, LPDIRECT3DTEXTURE9 pTempRadarTexture );
    void    DrawDotOnBuffer( int nCenterX, int nCenterY, D3DLOCKED_RECT* plockedRect, D3DSURFACE_DESC* pdesc, WORD wColor );
    
    HRESULT HandleNearbyObjects( const float fElapsedTime, CDisplayObject* pObject1, int iX, int iZ );
    
    HRESULT ClearStrayObjects();
    HRESULT AddDisplayObject( CDisplayObject* pObject );
    HRESULT RemoveDisplayObject( CDisplayObject* pObject );
    DWORD   GetObjectCount() { return m_dwObjectCount; }
    DWORD   GetEnemyCount() { return m_dwEnemyCount; }

    DWORD               m_dwObjectCount;           // How many objects are in the world
    DWORD               m_dwEnemyCount;            // How many enemies are in the world
    MESH_NODE*          m_MeshArray;
    LONG                m_dwWorldWidth;
    LONG                m_dwWorldHeight;  
    D3DFORMAT           m_fmtTexture;
    DWORD               m_dwVertsRendered;
    DWORD               m_dwNumZonesInView;
    VIEW_NODE           m_aZoneView[MAX_VIEW_ZONE_X][MAX_VIEW_ZONE_Z];
    CThemeStyle*        m_pTheme;
    CMyApplication*     m_pApp;
};
