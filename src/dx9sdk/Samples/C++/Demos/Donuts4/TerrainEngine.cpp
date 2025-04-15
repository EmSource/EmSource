//-----------------------------------------------------------------------------
// File: TerrianEngine.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: CTerrainEngine
// Desc: 
//-----------------------------------------------------------------------------
CTerrainEngine::CTerrainEngine( CMyApplication* pApp )
{
    m_pApp          = pApp;
    m_MeshArray     = NULL;
    m_dwObjectCount = 0;
    m_dwEnemyCount  = 0;
}




//-----------------------------------------------------------------------------
// Name: ~CTerrainEngine
// Desc: 
//-----------------------------------------------------------------------------
CTerrainEngine::~CTerrainEngine()
{
    FinalCleanup();
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::OneTimeSceneInit( CThemeStyle* pTheme )
{
    HRESULT hr;
    int iX, iZ;

    m_pTheme = pTheme;
    m_dwWorldWidth  = g_Profile.nWorldWidth;
    m_dwWorldHeight = g_Profile.nWorldHeight;

    m_MeshArray = new MESH_NODE[ m_dwWorldWidth * m_dwWorldHeight ];
    if( NULL == m_MeshArray )
        return E_OUTOFMEMORY;
    ZeroMemory( m_MeshArray, m_dwWorldWidth * m_dwWorldHeight * sizeof(MESH_NODE) );

    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh = new CTerrainMesh( this );
            if( m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh == NULL )
                return E_OUTOFMEMORY;
        }
    }

    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            int iNorth  = (iZ+1) % m_dwWorldHeight;
            int iEast   = (iX+1) % m_dwWorldWidth;
            CTerrainMesh* pNorth      = m_MeshArray[   iX+ m_dwWorldWidth*iNorth].pMesh;
            CTerrainMesh* pEast       = m_MeshArray[iEast+ m_dwWorldWidth*iZ].pMesh;
            CTerrainMesh* pNorthEast  = m_MeshArray[iEast+ m_dwWorldWidth*iNorth].pMesh;

            CZoneStyleParameter* pLandType = &m_pTheme->aZoneStyles[ rand() % m_pTheme->nNumZoneStyles ];
            
            hr = m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh->OneTimeSceneInit( pLandType,
                                                              (float)ZONE_WIDTH*iX, (float)ZONE_HEIGHT*iZ,
                                                              pNorth, pEast, pNorthEast );
            if( FAILED(hr) )
                return hr;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::InitDeviceObjects( D3DFORMAT fmtTexture )
{
    m_fmtTexture = fmtTexture;

    HRESULT hr;
    int iX, iZ;

    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            hr = m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh->InitDeviceObjects( m_fmtTexture );
            if( FAILED(hr) )
                return hr;
        }
    }

    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            hr = m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh->SmoothMap();
            if( FAILED(hr) )
                return hr;
        }
    }

    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            // The smooth processes uses the bordering meshs to smooth the mesh.
            // So we need lock down the results of the first step in a 2nd pass
            // otherwise while smoothing a mesh the border meshs will either be already
            // smoothed or not yet smoothed (depending if that mesh was already processed)
            // so it creates an gfx inconsistancy unless use all unsmoothed meshes 
            hr = m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh->FinalizeSmooth();
            if( FAILED(hr) )
                return hr;
        }
    }  

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::RestoreDeviceObjects( HWND hWndMain )
{
    HRESULT hr;
    int iX, iZ;

    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];

            CDisplayObject* pObject = pMeshNode->pDisplayList;
            while( pObject )
            {
                pObject->RestoreDeviceObjects();
                pObject = pObject->m_pNext;
            }

            hr = pMeshNode->pMesh->RestoreDeviceObjects( hWndMain );
            if( FAILED(hr) )
                return hr;
        }
    }

    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            hr = m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh->GenerateMipMaps();
            if( FAILED(hr) )
                return hr;
        }
    }

    if( m_dwWorldWidth != 1 && m_dwWorldHeight != 1 ) // Can't correct edge if its 1xN or Nx1
    {
        for( iX = 0; iX<m_dwWorldWidth; iX++ )
        {
            for( iZ = 0; iZ<m_dwWorldHeight; iZ++ )
            {
                hr = m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh->CorrectTextureEdge();
                if( FAILED(hr) )
                    return hr;
            }
        }
    }

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: AddDisplayObject
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::AddDisplayObject( CDisplayObject* pObject )
{
    if( NULL == pObject )
        return E_INVALIDARG;

    int iX, iZ;

    GetZoneFromPt( pObject->m_vPos.x, pObject->m_vPos.z, &iX, &iZ );

    MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];
    if( pMeshNode->pDisplayList )
    {
        pObject->m_pNext = pMeshNode->pDisplayList;
        pObject->m_pPrev = NULL;
        pMeshNode->pDisplayList->m_pPrev = pObject;
        pMeshNode->pDisplayList = pObject;
    }
    else
    {
        pMeshNode->pDisplayList = pObject;
        pObject->m_pNext = NULL;
        pObject->m_pPrev = NULL;
    }

    pObject->m_pMeshNode = pMeshNode;

    if( pObject->m_ObjectType == OBJ_ENEMY )
        m_dwEnemyCount++;
    m_dwObjectCount++;

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: RemoveDisplayObject
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::RemoveDisplayObject( CDisplayObject* pObject )
{
    if( NULL == pObject )
        return E_INVALIDARG;

    MESH_NODE* pMeshNode = pObject->m_pMeshNode;

    if( pMeshNode )
    {
        if( pMeshNode->pDisplayList == pObject )
        {
            pMeshNode->pDisplayList = pObject->m_pNext;
            if( pMeshNode->pDisplayList )
                pMeshNode->pDisplayList->m_pPrev = NULL;
        }
        else
        {
            if( pObject->m_pPrev )
                pObject->m_pPrev->m_pNext = pObject->m_pNext;
            if( pObject->m_pNext )
                pObject->m_pNext->m_pPrev = pObject->m_pPrev;
        }
    }

    pObject->m_pMeshNode = NULL;

    pObject->m_pNext = NULL;
    pObject->m_pPrev = NULL;

    if( pObject->m_ObjectType == OBJ_ENEMY )
        m_dwEnemyCount--;
    m_dwObjectCount--;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ClearStrayObjects
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::ClearStrayObjects()
{
    CPlayerShip* pPlayerShip = g_pApp->GetPlayerShip();

    for( int iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( int iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];

            CDisplayObject* pObject = pMeshNode->pDisplayList;
            CDisplayObject* pObjectNext;
            while( pObject )
            {
                pObjectNext = pObject->m_pNext;

                if( pObject != pPlayerShip )
                {
                    RemoveDisplayObject( pObject );
                    pObject->InvalidateDeviceObjects();
                    pObject->DeleteDeviceObjects();
                    pObject->FinalCleanup();
                    SAFE_DELETE( pObject );
                }

                pObject = pObjectNext;
            }
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::FrameMove( const float fElapsedTime )
{
    HRESULT hr;

    int iX;
    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( int iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];

            CDisplayObject* pObject = pMeshNode->pDisplayList;
            while( pObject )
            {
                if( pObject->m_bActive )
                {
                    if( !g_pApp->m_bPaused || 
                        (g_pApp->m_bPaused && g_pApp->m_bDebugMode && pObject == g_pApp->GetPlayerShip()) )
                    {
                        pObject->FrameMove( fElapsedTime );
                        HandleNearbyObjects( fElapsedTime, pObject, iX, iZ );
                    }
                }

                pObject = pObject->m_pNext;
            }

            if( pMeshNode->pMesh )
            {
                // The terrian mesh itself could animate
                if( FAILED( hr = pMeshNode->pMesh->FrameMove( fElapsedTime ) ) )
                    return hr;
            }
        }
    }

    // Make sure all the objects are in the right zone after moving around
    for( iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( int iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];
            int iCurZoneX, iCurZoneZ;

            CDisplayObject* pObject = pMeshNode->pDisplayList;
            CDisplayObject* pObjectNext;

            while( pObject )
            {
                pObjectNext = pObject->m_pNext;

                if( pObject->m_bActive )
                {
                    pObject->FrameMoveFinalize( fElapsedTime );

                    GetZoneFromPt( pObject->m_vPos.x, pObject->m_vPos.z, 
                                &iCurZoneX, &iCurZoneZ );

                    if( iCurZoneX != iX ||
                        iCurZoneZ != iZ )
                    {
                        RemoveDisplayObject( pObject );
                        AddDisplayObject( pObject );
                    }
                }
                else
                {
                    RemoveDisplayObject( pObject );
                    pObject->InvalidateDeviceObjects();
                    pObject->DeleteDeviceObjects();
                    pObject->FinalCleanup();
                    SAFE_DELETE( pObject );
                }

                pObject = pObjectNext;
            }
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: HandleNearbyObjects
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::HandleNearbyObjects( const float fElapsedTime, CDisplayObject* pObject1, 
                                             int iX, int iZ )
{
    MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];

    CDisplayObject* pObject2 = pMeshNode->pDisplayList;
    while( pObject2 )
    {
        // Skip object2 if its that same as object1
        if( pObject2 != pObject1 )
        {
            if( pObject2->m_bActive )
                pObject1->HandleNearbyObject( fElapsedTime, pObject2 );
        }

        pObject2 = pObject2->m_pNext;
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: DrawDotOnBuffer
// Desc: 
//-----------------------------------------------------------------------------
void CTerrainEngine::DrawDotOnBuffer( int nCenterX, int nCenterY, D3DLOCKED_RECT* plockedRect, D3DSURFACE_DESC* pdesc, WORD wColor )
{
    int nSize = 5;

    int nX = nCenterX;
    int nY = nCenterY;

    for( nY = nCenterY-nSize; nY < nCenterY+nSize; nY++ )
    {
        for( nX = nCenterX-nSize; nX < nCenterX+nSize; nX++ )
        {
            if( nX >= 0 && nY >= 0 &&
                nX < (int) pdesc->Width &&
                nY < (int) pdesc->Height )
            {
                WORD* pBuffer = (WORD*) ((BYTE*)plockedRect->pBits + plockedRect->Pitch * nY + nX*sizeof(WORD)); 
                *pBuffer = wColor;
            }
        }
    }
}



//-----------------------------------------------------------------------------
// Name: RenderRadar
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::RenderRadar( LPDIRECT3DTEXTURE9 pRadarTexture, LPDIRECT3DTEXTURE9 pTempRadarTexture )
{
    HRESULT hr;
    
    if( g_bDebugIsZoneRenderFroze )
        return S_OK; // debugging: don't render radar if camera pos froze

    D3DSURFACE_DESC desc;
    pTempRadarTexture->GetLevelDesc( 0, &desc ); 

    D3DLOCKED_RECT lockedRect;
    hr = pTempRadarTexture->LockRect( 0, &lockedRect, NULL, 0 );
    if( SUCCEEDED(hr) )
    {
        memset( lockedRect.pBits, 0x00, 256*lockedRect.Pitch );

        float fObjectX;
        float fObjectY;
        float fPlayerX;
        float fPlayerY;
        float fX;
        float fY;
        float fNewX;
        float fNewY;
        float fR;
        float fAngle;
        float iCopyX;
        float iCopyY;

        int nX = 0;
        int nY = 0;

        int iPlayerZoneX;
        int iPlayerZoneZ;
        int iPlayerWorldX;
        int iPlayerWorldZ;

        int iObjectZoneX;
        int iObjectZoneZ;
        int iObjectWorldX;
        int iObjectWorldZ;

        CPlayerShip* pPlayerShip = g_pApp->GetPlayerShip();
        g_pTerrain->GetZoneFromPt( pPlayerShip->m_vPos.x, pPlayerShip->m_vPos.z, &iPlayerZoneX, &iPlayerZoneZ );
        g_pTerrain->GetWorldFromPt( pPlayerShip->m_vPos.x, pPlayerShip->m_vPos.z, &iPlayerWorldX, &iPlayerWorldZ );

        D3DXVECTOR3 vAheadLocal = D3DXVECTOR3(0.0,0.0f,1.0f);
        D3DXVECTOR3 vAheadWorld;
        D3DXVec3TransformNormal( &vAheadWorld, &vAheadLocal, &pPlayerShip->m_pSource->m_mOrientation ); 
        float fAheadAngle = atan2f( vAheadWorld.x, vAheadWorld.z );

        // Loop through every mesh in world
        for( int iX = 0; iX<m_dwWorldWidth; iX++ )
        {
            for( int iZ = 0; iZ<m_dwWorldHeight; iZ++ )
            {
                MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];
                CDisplayObject* pObject = pMeshNode->pDisplayList;

                // For every object in every mesh
                while( pObject )
                {
                    if( pObject->m_ObjectType == OBJ_ENEMY )
                    {       
                        g_pTerrain->GetZoneFromPt( pObject->m_vPos.x, pObject->m_vPos.z, &iObjectZoneX, &iObjectZoneZ );
                        g_pTerrain->GetWorldFromPt( pObject->m_vPos.x, pObject->m_vPos.z, &iObjectWorldX, &iObjectWorldZ );

                        // Get coords of player & object between <0,0> and <1,1>
                        fPlayerX = pPlayerShip->m_vPos.x / (float) (ZONE_WIDTH*g_pTerrain->m_dwWorldWidth);
                        fPlayerY = pPlayerShip->m_vPos.z / (float) (ZONE_HEIGHT*g_pTerrain->m_dwWorldHeight);
                        fObjectX = pObject->m_vPos.x / (float) (ZONE_WIDTH*g_pTerrain->m_dwWorldWidth);
                        fObjectY = pObject->m_vPos.z / (float) (ZONE_HEIGHT*g_pTerrain->m_dwWorldHeight);

                        assert( fPlayerX >= 0.0f && fPlayerX <= 1.0f );
                        assert( fPlayerY >= 0.0f && fPlayerY <= 1.0f );
                        assert( fObjectX >= 0.0f && fObjectX <= 1.0f );
                        assert( fObjectY >= 0.0f && fObjectY <= 1.0f );

                        // Calc position of object with player at <0,0>
                        fX = fObjectX - fPlayerX;
                        fY = fObjectY - fPlayerY;

                        // Ship is now at (0,0) and object is between <-1,-1> and <1,1>
                        assert( fX >= -1.0f && fX <= 1.0f );
                        assert( fY >= -1.0f && fY <= 1.0f );

                        // Since the world wraps, we might need to draw the same object 
                        // multiple times, so find the min and loop to draw them all

                        // Find the smallest fX,fY that's above -1.0f, -1.0f
                        while( fX >= -1.0f && fX <= 1.0f ) 
                                fX -= 1.0f;
                        while( fY >= -1.0f && fY <= 1.0f ) 
                                fY -= 1.0f;
                        fX += 1.0f;
                        fY += 1.0f;

                        for( iCopyY=fY; iCopyY<= 1.0f; iCopyY += 1.0f )
                        {
                            for( iCopyX=fX; iCopyX<= 1.0f; iCopyX += 1.0f )
                            {
                                // Get radius and angle of object point
                                fR = sqrtf( iCopyX*iCopyX + iCopyY*iCopyY );
                                fAngle = atan2f( iCopyY, iCopyX );

                                // Rotation the point based on the ship's angle 
                                fAngle += fAheadAngle;

                                // Figure out the new enemy pt
                                fNewX = cosf(fAngle) * fR;
                                fNewY = sinf(fAngle) * fR;

                                // New range is between -sqrt(2), sqrt(2)
                                assert( fNewX >= -1.42f && fNewX <= 1.42f );
                                assert( fNewY >= -1.42f && fNewY <= 1.42f );

                                // Make the range to between -1 & 1
                                fNewX /= 1.414213562373095048801688f;
                                fNewY /= 1.414213562373095048801688f;

                                assert( fNewX >= -1.0f && fNewX <= 1.0f );
                                assert( fNewY >= -1.0f && fNewY <= 1.0f );

                                // Flip the Y coord so it looks right on the overhead map
                                fNewY = -fNewY;

                                // Make new range between -0.5 & 0.5
                                fNewX /= 2.0f;
                                fNewY /= 2.0f;

                                assert( fNewX >= -0.5f && fNewX <= 0.5f );
                                assert( fNewY >= -0.5f && fNewY <= 0.5f );

                                // Make new range between 0 & 1
                                fNewX += 0.5f;
                                fNewY += 0.5f;

                                float fRangeX = (g_pTerrain->m_dwWorldWidth/2.0f);
                                float fRangeY = (g_pTerrain->m_dwWorldHeight/2.0f);

                                // Make new range between 0 & X
                                fNewX *= fRangeX;
                                fNewY *= fRangeY;

                                // Make new range between -X/2 & X/2
                                fNewX -= fRangeX/2.0f;
                                fNewY -= fRangeY/2.0f;

                                // Only allow dots close to ship, -0.5 & 0.5
                                if( fNewX >= -0.5f && fNewX <= 0.5f &&
                                    fNewY >= -0.5f && fNewY <= 0.5f )
                                {
                                    // Get radius and angle of enemy point
                                    fR = sqrtf( fNewX*fNewX + fNewY*fNewY );
                                    fAngle = atan2f( fNewY, fNewX );

                                    float fAngleMin = -4.0f*D3DX_PI/4.0f;
                                    float fAngleMax = fAngleMin+1.2f*D3DX_PI/4.0f;

                                    // Limit the dots to a radius, and make a blind spot between fAngleMin & fAngleMax
                                    if( fR < 0.45f && 
                                        (!(fAngle > fAngleMin && fAngle < fAngleMax) || fR < 0.12f) )
                                    {
                                        // Make new range between 0 & 1
                                        fNewX += 0.5f;
                                        fNewY += 0.5f;

                                        nX = (int) (fNewX * 256.0f);
                                        nY = (int) (fNewY * 256.0f);

                                        FLOAT fColor = 0.45f - fR;
                                        fColor /= 0.45f;
                                        BYTE nAlpha = (BYTE)(fColor * 30);
                                        if( nAlpha > 0xF )
                                            nAlpha = 0xF;

                                        WORD wColor = (WORD) ( (nAlpha << 12) + 0x0FFF );

                                        DrawDotOnBuffer( nX, nY, &lockedRect, &desc, wColor );
                                    }
                                }
                            }
                        }
                    }

                    pObject = pObject->m_pNext;
                }
            }
        }

        pTempRadarTexture->UnlockRect( 0 );
    }

    IDirect3DSurface9* pSurfaceSrc = NULL;
    IDirect3DSurface9* pSurfaceDest = NULL;

    pRadarTexture->GetSurfaceLevel( 0, &pSurfaceDest );
    pTempRadarTexture->GetSurfaceLevel( 0, &pSurfaceSrc );
    if( pSurfaceSrc  != NULL && 
        pSurfaceDest != NULL )
    {
        D3DXLoadSurfaceFromSurface( pSurfaceDest, NULL, NULL, 
                                    pSurfaceSrc, NULL, NULL, 
                                    D3DX_FILTER_POINT, 0 );

        SAFE_RELEASE( pSurfaceDest );
        SAFE_RELEASE( pSurfaceSrc );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RenderFrame
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::RenderFrame( DWORD* pdwNumVerts, CD3DCamera* pCam )
{
    m_dwVertsRendered = 0;
    m_dwNumZonesInView = 0;

    switch( g_Profile.nRenderTerrianStyle )
    {
        case 0:
        {
            // Render zones (0..x,0..y)
            for( int iX = 0; iX<m_dwWorldWidth; iX++ )
            {
                for( int iZ = 0; iZ<m_dwWorldHeight; iZ++ )
                {
                    RenderZone( 0, 0, iX, iZ, TRUE, TRUE, FALSE );
                    m_dwNumZonesInView++;
                }
            }
            break;
        }

        case 1:
        {
            // Render zones near camera (and behind camera)
            D3DXVECTOR3 vCamEyePt    = pCam->GetEyePt();
            D3DXVECTOR3 vCamLookAtPt = pCam->GetLookatPt();

            D3DXVECTOR3 vX    = vCamLookAtPt - vCamEyePt;
            D3DXVECTOR3 vXPerp = D3DXVECTOR3( -vX.z, vX.y, vX.x );
            D3DXVec3Normalize( &vXPerp, &vXPerp );
    
            FLOAT       fXLen = D3DXVec3Length( &vX );
            FLOAT       fYLen = (float) ( tan( pCam->GetFOV() / 2.0f ) * fXLen );
            D3DXVECTOR3 vYPlus = vX + vXPerp * fYLen;
            D3DXVECTOR3 vYNeg  = vX - vXPerp * fYLen;

            int nArea=2;
            for( int iX=-nArea; iX<=nArea; iX++ )
            {
                for( int iZ=-nArea; iZ<=nArea; iZ++ )
                {
                    int iZoneX, iZoneZ;
                    int iWorldX, iWorldZ;

                    float fZoneWrapPosX = vCamEyePt.x + iX*ZONE_WIDTH;
                    float fZoneWrapPosZ = vCamEyePt.z + iZ*ZONE_HEIGHT;
                    GetZoneFromPt( fZoneWrapPosX, fZoneWrapPosZ, &iZoneX, &iZoneZ );
                    GetWorldFromPt( fZoneWrapPosX, fZoneWrapPosZ, &iWorldX, &iWorldZ );

                    RenderZone( iWorldX, iWorldZ, iZoneX, iZoneZ, TRUE, TRUE, FALSE ); 
                    m_dwNumZonesInView++;
                }
            }
            break;
        }
        
        case 2:
        {
            // Render only the zones ahead of camera but this is 
            // kind of complex since the world wraps
            static D3DXVECTOR3 s_vLastCamEyePt;
            static D3DXVECTOR3 s_vLastCamLookAtPt;
            static CULLINFO s_vLastCullInfo;

            D3DXVECTOR3 vCamEyePt    = pCam->GetEyePt();
            D3DXVECTOR3 vCamLookAtPt = pCam->GetLookatPt();

            if( g_bDebugFreezeZoneRender )
            {
                // For debugging: allows camera for zone rendering to be frozen,
                // but allows the real camera to continue to move so the 
                // zone's that were being rendered can be inspected
                if( !g_bDebugIsZoneRenderFroze )
                {
                    s_vLastCamEyePt    = vCamEyePt;
                    s_vLastCamLookAtPt = vCamLookAtPt;
                    s_vLastCullInfo  = g_pApp->m_cullinfo;
                }

                g_bDebugIsZoneRenderFroze = !g_bDebugIsZoneRenderFroze;
                g_bDebugFreezeZoneRender = FALSE;
            }

            if( g_bDebugIsZoneRenderFroze )
            {
                vCamEyePt    = s_vLastCamEyePt;
                vCamLookAtPt = s_vLastCamLookAtPt;
                g_pApp->m_cullinfo = s_vLastCullInfo;
            }

            // Get the worlds coords for the zone where the camera is
            int iCenterWorldX, iCenterWorldZ;
            int iCenterZoneX, iCenterZoneZ;
            GetZoneFromPt(  vCamEyePt.x, vCamEyePt.z, &iCenterZoneX, &iCenterZoneZ );
            GetWorldFromPt( vCamEyePt.x, vCamEyePt.z, &iCenterWorldX, &iCenterWorldZ );
            float fCenterZoneX = (float) iCenterWorldX * (ZONE_WIDTH  * m_dwWorldWidth) + iCenterZoneX*ZONE_WIDTH;
            float fCenterZoneZ = (float) iCenterWorldZ * (ZONE_HEIGHT * m_dwWorldHeight) + iCenterZoneZ*ZONE_HEIGHT;

            // The world wraps so track which zones are in view using m_aZoneView
            ZeroMemory( m_aZoneView, sizeof(VIEW_NODE)*MAX_VIEW_ZONE_X*MAX_VIEW_ZONE_Z );

            // CheckIfZoneInView() recursively checks neighbor zones to see if they are in view 
            // and updates m_aZoneView as it goes and along draw the terrain for each zone in view. 
            // The camera is always the center zone at m_aZoneView[MAX_VIEW_ZONE_X/2][MAX_VIEW_ZONE_Z/2]
            CheckIfZoneInView( fCenterZoneX, fCenterZoneZ, MAX_VIEW_ZONE_X/2, MAX_VIEW_ZONE_Z/2 );

            // Then draw the objects for each zone in view since objects may have alpha 
            // and the terrian needs to be rendered first

            // Render only objects in zones that are visable
            for( int iX = MAX_VIEW_ZONE_X-1; iX>=0; iX-- )
            {
                for( int iZ = MAX_VIEW_ZONE_Z-1; iZ>=0; iZ-- )
                {
                    if( m_aZoneView[iX][iZ].bInView )
                    {
                        RenderZone( m_aZoneView[iX][iZ].iWorldX, m_aZoneView[iX][iZ].iWorldZ, 
                                    m_aZoneView[iX][iZ].iZoneX, m_aZoneView[iX][iZ].iZoneZ, 
                                    TRUE, FALSE, TRUE );
                    }
                }
            }

            break;
        }
    }

    *pdwNumVerts = m_dwVertsRendered;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CheckIfZoneInView
// Desc: 
//-----------------------------------------------------------------------------
BOOL CTerrainEngine::CheckIfZoneInView( const float fZonePosX, const float fZonePosZ, 
                                        const int iZoneIndexX, const int iZoneIndexZ )
{
    if( iZoneIndexX < 0 || iZoneIndexX >= MAX_VIEW_ZONE_X )
        return FALSE;
    if( iZoneIndexZ < 0 || iZoneIndexZ >= MAX_VIEW_ZONE_Z )
        return FALSE;
    
    // Return if this zone point that has already been visited
    VIEW_NODE* pViewNode = &m_aZoneView[iZoneIndexX][iZoneIndexZ];

    if( pViewNode->bVisited )
        return FALSE;
    pViewNode->bVisited = TRUE;

    // Update the viewnode's bounding box state if it has changed since last time
    if( !pViewNode->bValid ||
        pViewNode->fZonePosX != fZonePosX ||
        pViewNode->fZonePosZ != fZonePosZ )
    {
        // Mark that this viewnode refers to the zone at (fZonePosX,fZonePosZ)
        pViewNode->bValid = true;
        m_aZoneView[iZoneIndexX][iZoneIndexZ].fZonePosX = fZonePosX;
        m_aZoneView[iZoneIndexX][iZoneIndexZ].fZonePosZ = fZonePosZ;

        // Set max & min vectors for the bound box of this zone in world coords
        // Set the upper & lower height to extremes so that even if the camera 
        // is looking down or up the zone is rendered
        D3DXVECTOR3 vMin = D3DXVECTOR3( fZonePosX, -10.0f, fZonePosZ );
        D3DXVECTOR3 vMax = D3DXVECTOR3( fZonePosX + ZONE_WIDTH, MAX_HEIGHT_OF_MAP, fZonePosZ + ZONE_HEIGHT );

        // Set the bounding box for this zone in world coords
        pViewNode->vecBoundsWorld[0] = D3DXVECTOR3( vMin.x, vMin.y, vMin.z ); // xyz
        pViewNode->vecBoundsWorld[1] = D3DXVECTOR3( vMax.x, vMin.y, vMin.z ); // Xyz
        pViewNode->vecBoundsWorld[2] = D3DXVECTOR3( vMin.x, vMax.y, vMin.z ); // xYz
        pViewNode->vecBoundsWorld[3] = D3DXVECTOR3( vMax.x, vMax.y, vMin.z ); // XYz
        pViewNode->vecBoundsWorld[4] = D3DXVECTOR3( vMin.x, vMin.y, vMax.z ); // xyZ
        pViewNode->vecBoundsWorld[5] = D3DXVECTOR3( vMax.x, vMin.y, vMax.z ); // XyZ
        pViewNode->vecBoundsWorld[6] = D3DXVECTOR3( vMin.x, vMax.y, vMax.z ); // xYZ
        pViewNode->vecBoundsWorld[7] = D3DXVECTOR3( vMax.x, vMax.y, vMax.z ); // XYZ

        // Calc the planes of the bounding box
        D3DXPlaneFromPoints( &pViewNode->planeBoundsWorld[0], &pViewNode->vecBoundsWorld[0], &pViewNode->vecBoundsWorld[1], &pViewNode->vecBoundsWorld[2] ); // Near
        D3DXPlaneFromPoints( &pViewNode->planeBoundsWorld[1], &pViewNode->vecBoundsWorld[6], &pViewNode->vecBoundsWorld[7], &pViewNode->vecBoundsWorld[5] ); // Far
        D3DXPlaneFromPoints( &pViewNode->planeBoundsWorld[2], &pViewNode->vecBoundsWorld[2], &pViewNode->vecBoundsWorld[6], &pViewNode->vecBoundsWorld[4] ); // Left
        D3DXPlaneFromPoints( &pViewNode->planeBoundsWorld[3], &pViewNode->vecBoundsWorld[7], &pViewNode->vecBoundsWorld[3], &pViewNode->vecBoundsWorld[5] ); // Right
        D3DXPlaneFromPoints( &pViewNode->planeBoundsWorld[4], &pViewNode->vecBoundsWorld[2], &pViewNode->vecBoundsWorld[3], &pViewNode->vecBoundsWorld[6] ); // Top
        D3DXPlaneFromPoints( &pViewNode->planeBoundsWorld[5], &pViewNode->vecBoundsWorld[1], &pViewNode->vecBoundsWorld[0], &pViewNode->vecBoundsWorld[4] ); // Bottom
    }

    // Cull the zone based on its bounding box 
    pViewNode->cullstate = CullObject( &g_pApp->m_cullinfo, pViewNode->vecBoundsWorld, pViewNode->planeBoundsWorld );

    // Only render this zone if its inside the camera's view
    if( pViewNode->cullstate == CS_INSIDE )
    {
        m_aZoneView[iZoneIndexX][iZoneIndexZ].bInView = TRUE;   
        m_dwNumZonesInView++;

        // Since the world wraps, recursively check to see if the 8 neighbor zones are in view
        CheckIfZoneInView( fZonePosX - ZONE_WIDTH, fZonePosZ              , iZoneIndexX-1, iZoneIndexZ+0 );
        CheckIfZoneInView( fZonePosX + ZONE_WIDTH, fZonePosZ              , iZoneIndexX+1, iZoneIndexZ+0 );
        CheckIfZoneInView( fZonePosX             , fZonePosZ - ZONE_HEIGHT, iZoneIndexX+0, iZoneIndexZ-1 );
        CheckIfZoneInView( fZonePosX             , fZonePosZ + ZONE_HEIGHT, iZoneIndexX+0, iZoneIndexZ+1 );
        CheckIfZoneInView( fZonePosX - ZONE_WIDTH, fZonePosZ - ZONE_HEIGHT, iZoneIndexX-1, iZoneIndexZ-1 );
        CheckIfZoneInView( fZonePosX - ZONE_WIDTH, fZonePosZ + ZONE_HEIGHT, iZoneIndexX-1, iZoneIndexZ+1 );
        CheckIfZoneInView( fZonePosX + ZONE_WIDTH, fZonePosZ - ZONE_HEIGHT, iZoneIndexX+1, iZoneIndexZ-1 );
        CheckIfZoneInView( fZonePosX + ZONE_WIDTH, fZonePosZ + ZONE_HEIGHT, iZoneIndexX+1, iZoneIndexZ+1 );

        GetZoneFromPt( fZonePosX+ZONE_WIDTH/2, fZonePosZ+ZONE_HEIGHT/2, &m_aZoneView[iZoneIndexX][iZoneIndexZ].iZoneX, &m_aZoneView[iZoneIndexX][iZoneIndexZ].iZoneZ );
        GetWorldFromPt( fZonePosX+ZONE_WIDTH/2, fZonePosZ+ZONE_HEIGHT/2, &m_aZoneView[iZoneIndexX][iZoneIndexZ].iWorldX, &m_aZoneView[iZoneIndexX][iZoneIndexZ].iWorldZ );

        // Render this zone
        RenderZone( m_aZoneView[iZoneIndexX][iZoneIndexZ].iWorldX, m_aZoneView[iZoneIndexX][iZoneIndexZ].iWorldZ,
                    m_aZoneView[iZoneIndexX][iZoneIndexZ].iZoneX, m_aZoneView[iZoneIndexX][iZoneIndexZ].iZoneZ,
                    FALSE, TRUE, TRUE ); 
        return TRUE;
    }

    return FALSE;
}



//-----------------------------------------------------------------------------
// Name: CullObject()
// Desc: Determine the cullstate for an object bounding box (OBB).  
//       The algorithm is:
//       1) If any OBB corner pt is inside the frustum, return CS_INSIDE
//       2) Else if all OBB corner pts are outside a single frustum plane, 
//          return CS_OUTSIDE
//       3) Else if any frustum edge penetrates a face of the OBB, return 
//          CS_INSIDE
//       4) Else if any OBB edge penetrates a face of the frustum, return
//          CS_INSIDE
//       5) Else if any point in the frustum is outside any plane of the 
//          OBB, return CS_OUTSIDE
//       6) Else return CS_INSIDE
//-----------------------------------------------------------------------------
CULLSTATE CTerrainEngine::CullObject( const CULLINFO* pCullInfo, const D3DXVECTOR3* pVecBounds, 
                                      const D3DXPLANE* pPlaneBounds )
{
    BYTE bOutside[8];
    ZeroMemory( &bOutside, sizeof(bOutside) );

    // Check boundary vertices against all 6 frustum planes, 
    // and store result (1 if outside) in a bitfield
    for( int iPoint = 0; iPoint < 8; iPoint++ )
    {
        for( int iPlane = 0; iPlane < 6; iPlane++ )
        {
            if( pCullInfo->planeFrustum[iPlane].a * pVecBounds[iPoint].x +
                pCullInfo->planeFrustum[iPlane].b * pVecBounds[iPoint].y +
                pCullInfo->planeFrustum[iPlane].c * pVecBounds[iPoint].z +
                pCullInfo->planeFrustum[iPlane].d < 0)
            {
                bOutside[iPoint] |= (1 << iPlane);
            }
        }
        // If any point is inside all 6 frustum planes, it is inside
        // the frustum, so the object must be rendered.
        if( bOutside[iPoint] == 0 )
            return CS_INSIDE;
    }

    // If all points are outside any single frustum plane, the object is
    // outside the frustum
    if( (bOutside[0] & bOutside[1] & bOutside[2] & bOutside[3] & 
        bOutside[4] & bOutside[5] & bOutside[6] & bOutside[7]) != 0 )
    {
        return CS_OUTSIDE;
    }

    // Now see if any of the frustum edges penetrate any of the faces of
    // the bounding box
    D3DXVECTOR3 edge[12][2] = 
    {
        pCullInfo->vecFrustum[0], pCullInfo->vecFrustum[1], // front bottom
        pCullInfo->vecFrustum[2], pCullInfo->vecFrustum[3], // front top
        pCullInfo->vecFrustum[0], pCullInfo->vecFrustum[2], // front left
        pCullInfo->vecFrustum[1], pCullInfo->vecFrustum[3], // front right
        pCullInfo->vecFrustum[4], pCullInfo->vecFrustum[5], // back bottom
        pCullInfo->vecFrustum[6], pCullInfo->vecFrustum[7], // back top
        pCullInfo->vecFrustum[4], pCullInfo->vecFrustum[6], // back left
        pCullInfo->vecFrustum[5], pCullInfo->vecFrustum[7], // back right
        pCullInfo->vecFrustum[0], pCullInfo->vecFrustum[4], // left bottom
        pCullInfo->vecFrustum[2], pCullInfo->vecFrustum[6], // left top
        pCullInfo->vecFrustum[1], pCullInfo->vecFrustum[5], // right bottom
        pCullInfo->vecFrustum[3], pCullInfo->vecFrustum[7], // right top
    };
    D3DXVECTOR3 face[6][4] =
    {
        pVecBounds[0], pVecBounds[2], pVecBounds[3], pVecBounds[1], // front
        pVecBounds[4], pVecBounds[5], pVecBounds[7], pVecBounds[6], // back
        pVecBounds[0], pVecBounds[4], pVecBounds[6], pVecBounds[2], // left
        pVecBounds[1], pVecBounds[3], pVecBounds[7], pVecBounds[5], // right
        pVecBounds[2], pVecBounds[6], pVecBounds[7], pVecBounds[3], // top
        pVecBounds[0], pVecBounds[4], pVecBounds[5], pVecBounds[1], // bottom
    };
    D3DXVECTOR3* pEdge;
    D3DXVECTOR3* pFace;
    pEdge = &edge[0][0];
    for( INT iEdge = 0; iEdge < 12; iEdge++ )
    {
        pFace = &face[0][0];
        for( INT iFace = 0; iFace < 6; iFace++ )
        {
            if( EdgeIntersectsFace( pEdge, pFace, &pPlaneBounds[iFace] ) )
            {
                return CS_INSIDE; // slow
            }
            pFace += 4;
        }
        pEdge += 2;
    }

    // Now see if any of the bounding box edges penetrate any of the faces of
    // the frustum
    D3DXVECTOR3 edge2[12][2] = 
    {
        pVecBounds[0], pVecBounds[1], // front bottom
        pVecBounds[2], pVecBounds[3], // front top
        pVecBounds[0], pVecBounds[2], // front left
        pVecBounds[1], pVecBounds[3], // front right
        pVecBounds[4], pVecBounds[5], // back bottom
        pVecBounds[6], pVecBounds[7], // back top
        pVecBounds[4], pVecBounds[6], // back left
        pVecBounds[5], pVecBounds[7], // back right
        pVecBounds[0], pVecBounds[4], // left bottom
        pVecBounds[2], pVecBounds[6], // left top
        pVecBounds[1], pVecBounds[5], // right bottom
        pVecBounds[3], pVecBounds[7], // right top
    };
    D3DXVECTOR3 face2[6][4] =
    {
        pCullInfo->vecFrustum[0], pCullInfo->vecFrustum[2], pCullInfo->vecFrustum[3], pCullInfo->vecFrustum[1], // front
        pCullInfo->vecFrustum[4], pCullInfo->vecFrustum[5], pCullInfo->vecFrustum[7], pCullInfo->vecFrustum[6], // back
        pCullInfo->vecFrustum[0], pCullInfo->vecFrustum[4], pCullInfo->vecFrustum[6], pCullInfo->vecFrustum[2], // left
        pCullInfo->vecFrustum[1], pCullInfo->vecFrustum[3], pCullInfo->vecFrustum[7], pCullInfo->vecFrustum[5], // right
        pCullInfo->vecFrustum[2], pCullInfo->vecFrustum[6], pCullInfo->vecFrustum[7], pCullInfo->vecFrustum[3], // top
        pCullInfo->vecFrustum[0], pCullInfo->vecFrustum[4], pCullInfo->vecFrustum[5], pCullInfo->vecFrustum[1], // bottom
    };
    pEdge = &edge2[0][0];
    for( iEdge = 0; iEdge < 12; iEdge++ )
    {
        pFace = &face2[0][0];
        for( INT iFace = 0; iFace < 6; iFace++ )
        {
            if( EdgeIntersectsFace( pEdge, pFace, &pCullInfo->planeFrustum[iFace] ) )
            {
                return CS_INSIDE; // slow
            }
            pFace += 4;
        }
        pEdge += 2;
    }

    // Now see if frustum is contained in bounding box
    // If any frustum corner point is outside any plane of the bounding box,
    // the frustum is not contained in the bounding box, so the object
    // is outside the frustum
    for( INT iPlane = 0; iPlane < 6; iPlane++ )
    {
        if( pPlaneBounds[iPlane].a * pCullInfo->vecFrustum[0].x +
            pPlaneBounds[iPlane].b * pCullInfo->vecFrustum[0].y +
            pPlaneBounds[iPlane].c * pCullInfo->vecFrustum[0].z +
            pPlaneBounds[iPlane].d  < 0 )
        {
            return CS_OUTSIDE; // slow 
        }
    }

    // Bounding box must contain the frustum, so render the object
    return CS_INSIDE; // slow
}




//-----------------------------------------------------------------------------
// Name: EdgeIntersectsFace()
// Desc: Determine if the edge bounded by the two vectors in pEdges intersects
//       the quadrilateral described by the four vectors in pFacePoints.  
//       Note: pPlane could be derived from pFacePoints using 
//       D3DXPlaneFromPoints, but it is precomputed in advance for greater
//       speed.
//-----------------------------------------------------------------------------
BOOL CTerrainEngine::EdgeIntersectsFace( const D3DXVECTOR3* const pEdges, const D3DXVECTOR3* const pFacePoints, 
                                         const D3DXPLANE* const pPlane )
{
    // If both edge points are on the same side of the plane, the edge does
    // not intersect the face
    FLOAT fDist1;
    FLOAT fDist2;
    fDist1 = pPlane->a * pEdges[0].x + pPlane->b * pEdges[0].y +
             pPlane->c * pEdges[0].z + pPlane->d;
    fDist2 = pPlane->a * pEdges[1].x + pPlane->b * pEdges[1].y +
             pPlane->c * pEdges[1].z + pPlane->d;
    if( fDist1 > 0 && fDist2 > 0 ||
        fDist1 < 0 && fDist2 < 0 )
    {
        return FALSE;
    }

    // Find point of intersection between edge and face plane (if they're
    // parallel, edge does not intersect face and D3DXPlaneIntersectLine 
    // returns NULL)
    D3DXVECTOR3 ptIntersection;
    if( NULL == D3DXPlaneIntersectLine( &ptIntersection, pPlane, &pEdges[0], &pEdges[1] ) )
        return FALSE;

    // Project onto a 2D plane to make the pt-in-poly test easier
    FLOAT fAbsA = (pPlane->a > 0 ? pPlane->a : -pPlane->a);
    FLOAT fAbsB = (pPlane->b > 0 ? pPlane->b : -pPlane->b);
    FLOAT fAbsC = (pPlane->c > 0 ? pPlane->c : -pPlane->c);
    D3DXVECTOR2 facePoints[4];
    D3DXVECTOR2 point;
    if( fAbsA > fAbsB && fAbsA > fAbsC )
    {
        // Plane is mainly pointing along X axis, so use Y and Z
        for( INT i = 0; i < 4; i++)
        {
            facePoints[i].x = pFacePoints[i].y;
            facePoints[i].y = pFacePoints[i].z;
        }
        point.x = ptIntersection.y;
        point.y = ptIntersection.z;
    }
    else if( fAbsB > fAbsA && fAbsB > fAbsC )
    {
        // Plane is mainly pointing along Y axis, so use X and Z
        for( INT i = 0; i < 4; i++)
        {
            facePoints[i].x = pFacePoints[i].x;
            facePoints[i].y = pFacePoints[i].z;
        }
        point.x = ptIntersection.x;
        point.y = ptIntersection.z;
    }
    else
    {
        // Plane is mainly pointing along Z axis, so use X and Y
        for( INT i = 0; i < 4; i++)
        {
            facePoints[i].x = pFacePoints[i].x;
            facePoints[i].y = pFacePoints[i].y;
        }
        point.x = ptIntersection.x;
        point.y = ptIntersection.y;
    }

    // If point is on the outside of any of the face edges, it is
    // outside the face.  
    // We can do this by taking the determinant of the following matrix:
    // | x0 y0 1 |
    // | x1 y1 1 |
    // | x2 y2 1 |
    // where (x0,y0) and (x1,y1) are points on the face edge and (x2,y2) 
    // is our test point.  If this value is positive, the test point is
    // "to the left" of the line.  To determine whether a point needs to
    // be "to the right" or "to the left" of the four lines to qualify as
    // inside the face, we need to see if the faces are specified in 
    // clockwise or counter-clockwise order (it could be either, since the
    // edge could be penetrating from either side).  To determine this, we
    // do the same test to see if the third point is "to the right" or 
    // "to the left" of the line formed by the first two points.
    // See http://forum.swarthmore.edu/dr.math/problems/scott5.31.96.html
    FLOAT x0, x1, x2, y0, y1, y2;
    x0 = facePoints[0].x;
    y0 = facePoints[0].y;
    x1 = facePoints[1].x;
    y1 = facePoints[1].y;
    x2 = facePoints[2].x;
    y2 = facePoints[2].y;
    BOOL bClockwise = FALSE;
    if( x1*y2 - y1*x2 - x0*y2 + y0*x2 + x0*y1 - y0*x1 < 0 )
        bClockwise = TRUE;
    x2 = point.x;
    y2 = point.y;
    for( INT i = 0; i < 4; i++ )
    {
        x0 = facePoints[i].x;
        y0 = facePoints[i].y;
        if( i < 3 )
        {
            x1 = facePoints[i+1].x;
            y1 = facePoints[i+1].y;
        }
        else
        {
            x1 = facePoints[0].x;
            y1 = facePoints[0].y;
        }
        if( ( x1*y2 - y1*x2 - x0*y2 + y0*x2 + x0*y1 - y0*x1 > 0 ) == bClockwise )
            return FALSE;
    }

    // If we get here, the point is inside all four face edges, 
    // so it's inside the face.
    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: GetZoneFromPt
// Desc: 
//-----------------------------------------------------------------------------
VOID CTerrainEngine::GetZoneFromPt( const float fX, const float fZ, int* pnZoneX, int* pnZoneZ )
{
    int iZoneX;
    int iZoneZ;
    
    if( fX >= 0.0f )
        iZoneX = (int) (fX / ZONE_WIDTH);
    else
        iZoneX = (int) (fX / ZONE_WIDTH) - 1;

    if( fZ >= 0.0f )
        iZoneZ = (int) (fZ / ZONE_HEIGHT);
    else
        iZoneZ = (int) (fZ / ZONE_HEIGHT) - 1;

    while( iZoneX < 0 )
        iZoneX += m_dwWorldWidth;
    while( iZoneZ < 0 )
        iZoneZ += m_dwWorldHeight;

    *pnZoneX = iZoneX % m_dwWorldWidth;
    *pnZoneZ = iZoneZ % m_dwWorldHeight;
}




//-----------------------------------------------------------------------------
// Name: GetWorldFromPt
// Desc: 
//-----------------------------------------------------------------------------
VOID CTerrainEngine::GetWorldFromPt( const float fX, const float fZ, int* pnWorldX, int* pnWorldZ )
{
    int iWorldX, iWorldZ;
    
    if( fX >= 0.0f )
        iWorldX = (int) ( fX / (ZONE_WIDTH  * m_dwWorldWidth) );
    else
        iWorldX = (int) ( fX / (ZONE_WIDTH  * m_dwWorldWidth) ) - 1;

    if( fZ >= 0.0f )
        iWorldZ = (int) ( fZ / (ZONE_HEIGHT * m_dwWorldHeight) );
    else
        iWorldZ = (int) ( fZ / (ZONE_HEIGHT * m_dwWorldHeight) ) - 1;

    *pnWorldX = iWorldX;
    *pnWorldZ = iWorldZ;
}




//-----------------------------------------------------------------------------
// Name: GetWorldFromUniversal
// Desc: output coords that are between <0,0> and 
//       <ZONE_WIDTH*m_dwWorldWidth,ZONE_HEIGHT*m_dwWorldHeight>
//-----------------------------------------------------------------------------
VOID CTerrainEngine::GetWorldFromUniversal( float fUniversalX, float fUniversalZ, 
                                            float* pfWorldX, float* pfWorldZ )
{
    // Wrap if needed
    while( fUniversalX < 0.0f )
        fUniversalX += ZONE_WIDTH*m_dwWorldWidth;
    while( fUniversalX >= ZONE_WIDTH*m_dwWorldWidth )
        fUniversalX -= ZONE_WIDTH*m_dwWorldWidth;

    while( fUniversalZ < 0.0f )
        fUniversalZ += ZONE_HEIGHT*m_dwWorldHeight;
    while( fUniversalZ >= ZONE_HEIGHT*m_dwWorldHeight )
        fUniversalZ -= ZONE_HEIGHT*m_dwWorldHeight;

    *pfWorldX = fUniversalX;
    *pfWorldZ = fUniversalZ;
}




//-----------------------------------------------------------------------------
// Name: RenderZone
// Desc: 
//-----------------------------------------------------------------------------
VOID CTerrainEngine::RenderZone( int iWorldX, int iWorldZ, int iZoneX, int iZoneZ, 
                                 BOOL bRenderObjects, BOOL bRenderTerrain, BOOL bCullObjects )
{
    float fWrapOffsetX = (float) iWorldX * (ZONE_WIDTH  * m_dwWorldWidth);
    float fWrapOffsetZ = (float) iWorldZ * (ZONE_HEIGHT * m_dwWorldHeight);

    MESH_NODE* pMeshNode = &m_MeshArray[iZoneX + m_dwWorldWidth*iZoneZ];

    if( bRenderTerrain && pMeshNode->pMesh )
    {
        DWORD dwNumTerrainVerts;
        // Set either wireframe or solid
        if( g_pApp->m_bDebugMode && g_pApp->m_bWireMode )
            g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
        else
            g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

        pMeshNode->pMesh->RenderFrame( fWrapOffsetX, fWrapOffsetZ, &dwNumTerrainVerts );  

        g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
        m_dwVertsRendered += dwNumTerrainVerts;
    }

    if( bRenderObjects )
    {
        DWORD dwNumModelVerts = 0;

        CDisplayObject* pObject = pMeshNode->pDisplayList;
        while( pObject )
        {
            if( pObject->m_bActive )
            {
                bool bRender = true;
                if( bCullObjects )
                {
                    // Only render if m_cullstate == CS_INSIDE
                    pObject->CullObject( fWrapOffsetX, fWrapOffsetZ, &g_pApp->m_cullinfo );
                    bRender = (pObject->m_cullstate == CS_INSIDE );
                }

                if( bRender )
                    pObject->Render( fWrapOffsetX, fWrapOffsetZ, &dwNumModelVerts );
            }
            m_dwVertsRendered += dwNumModelVerts;
            pObject = pObject->m_pNext;
        }
    }
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::InvalidateDeviceObjects()
{
    HRESULT hr;

    for( int iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( int iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];

            CDisplayObject* pObject = pMeshNode->pDisplayList;
            while( pObject )
            {
                pObject->InvalidateDeviceObjects();
                pObject = pObject->m_pNext;
            }

            hr = pMeshNode->pMesh->InvalidateDeviceObjects();
            if( FAILED(hr) )
                return hr;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainEngine::DeleteDeviceObjects()
{
    HRESULT hr;

    for( int iX = 0; iX<m_dwWorldWidth; iX++ )
    {
        for( int iZ = 0; iZ<m_dwWorldHeight; iZ++ )
        {
            MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];

            CDisplayObject* pObject = pMeshNode->pDisplayList;
            while( pObject )
            {
                pObject->DeleteDeviceObjects();
                pObject = pObject->m_pNext;
            }

            hr = pMeshNode->pMesh->DeleteDeviceObjects();
            if( FAILED(hr) )
                return hr;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup
// Desc: 
//-----------------------------------------------------------------------------
VOID CTerrainEngine::FinalCleanup()
{
    if( m_MeshArray )
    {
        for( int iX = 0; iX<m_dwWorldWidth; iX++ )
        {
            for( int iZ = 0; iZ<m_dwWorldHeight; iZ++ )
            {
                MESH_NODE* pMeshNode = &m_MeshArray[iX + m_dwWorldWidth*iZ];

                CDisplayObject* pObject = pMeshNode->pDisplayList;
                CDisplayObject* pObjectDelete;
                while( pObject )
                {
                    pObjectDelete = pObject;
                    pObject = pObject->m_pNext;
                    SAFE_DELETE( pObjectDelete );
                }
                pMeshNode->pDisplayList = NULL;

                if( m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh )
                    m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh->FinalCleanup();
                SAFE_DELETE( m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh );
            }
        }

        SAFE_DELETE_ARRAY( m_MeshArray );
    }
}




//-----------------------------------------------------------------------------
// Name: GetHeight
// Desc: returns the height of the ground at this point in universial coords 
//       Since the terrian engine is simple, there can only be one 1 ground height
//       at every point (no tunnels/etc)
//-----------------------------------------------------------------------------
FLOAT CTerrainEngine::GetHeight( float x, float z ) 
{ 
    // Doing this:
    // x = -0.0000001
    // x += 256.0f
    // x will equal 256.0f (it will loose bits of percision) which will throw 
    // off the calculations below so round off the percision while maintaining
    // the sign value
    x *= 10000.0f;
    if( x < 0 )
        x = floorf(x)/10000.0f;
    else
        x = ceilf(x)/10000.0f;

    z *= 10000.0f;
    if( z < 0 )
        z = floorf(z)/10000.0f;
    else
        z = ceilf(z)/10000.0f;

    // Figure out which zone this point is in
    int iX = (int)( (int)(x) / (int)ZONE_WIDTH );
    int iZ = (int)( (int)(z) / (int)ZONE_HEIGHT );

    // Compensate for negative values since iX = -10.0f / 64.0f = 0 
    // and we want iX=-1 if x=-10.0f
    if( x < 0.0f ) iX--;
    if( z < 0.0f ) iZ--;

    // Wrap the values around the world if needed
    while( iX < 0 )
    {
        iX += m_dwWorldWidth;
        x += ZONE_WIDTH*m_dwWorldWidth;
    }
    while( iX >= m_dwWorldWidth )
    {
        iX -= m_dwWorldWidth;
        x -= ZONE_WIDTH*m_dwWorldWidth;
    }

    while( iZ < 0 )
    {
        iZ += m_dwWorldHeight;
        z += ZONE_HEIGHT*m_dwWorldHeight;
    }   
    while( iZ >= m_dwWorldHeight )
    {
        iZ -= m_dwWorldHeight;
        z -= ZONE_HEIGHT*m_dwWorldHeight;
    }

    CTerrainMesh* pMesh = m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh;

    // Ensure that the mesh owns this point
    assert( FALSE == pMesh->IsOutOfRangeWorld( x, z ) );       

    // Now that we know the mesh index, ask the mesh what the value is at this point
    return pMesh->GetHeightWorld( x, z ); 
};




//-----------------------------------------------------------------------------
// Name: GetTexelColor
// Desc: same as above but returns the texel color at this point
//-----------------------------------------------------------------------------
DWORD CTerrainEngine::GetTexelColor( DWORD iLevel, float x, float z )
{ 
    x *= 10000.0f;
    if( x < 0 )
        x = floorf(x)/10000.0f;
    else
        x = ceilf(x)/10000.0f;

    z *= 10000.0f;
    if( z < 0 )
        z = floorf(z)/10000.0f;
    else
        z = ceilf(z)/10000.0f;

    int iX = (int)( x / (float) ZONE_WIDTH );
    int iZ = (int)( z / (float) ZONE_HEIGHT );

    if( x < 0.0f ) iX--;
    if( z < 0.0f ) iZ--;

    while( iX < 0 )
    {
        iX += m_dwWorldWidth;
        x += ZONE_WIDTH*m_dwWorldWidth;
    }
    while( iX >= m_dwWorldWidth )
    {
        iX -= m_dwWorldWidth;
        x -= ZONE_WIDTH*m_dwWorldWidth;
    }

    while( iZ < 0 )
    {
        iZ += m_dwWorldHeight;
        z += ZONE_HEIGHT*m_dwWorldHeight;
    }   
    while( iZ >= m_dwWorldHeight )
    {
        iZ -= m_dwWorldHeight;
        z -= ZONE_HEIGHT*m_dwWorldHeight;
    }
        
    return m_MeshArray[iX + m_dwWorldWidth*iZ].pMesh->GetTexelColor( iLevel, x, z ); 
}


