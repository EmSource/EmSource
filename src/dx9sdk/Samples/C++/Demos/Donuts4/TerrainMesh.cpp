//-----------------------------------------------------------------------------
// File: terrainmesh.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"

#define RVALUE(rgb)      ((BYTE)((rgb)>>16))
#define GVALUE(rgb)      ((BYTE)(((WORD)(rgb)) >> 8))
#define BVALUE(rgb)      ((BYTE)(rgb))


extern CProfile g_Profile;




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CTerrainMesh::CTerrainMesh( CTerrainEngine* pTerrainEngine )
{
    g_pTerrainEngine = pTerrainEngine;
    m_pMesh         = NULL;
    m_pMap          = NULL;
    m_pTexture      = NULL;
    m_dwNumFaces    = 0;
    m_dwNumVerties  = 0;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CTerrainMesh::~CTerrainMesh()
{
    FinalCleanup();
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::OneTimeSceneInit( CZoneStyleParameter* pLandStyle, const float fWorldOffsetX, const float fWorldOffsetZ, CTerrainMesh* pNorth, CTerrainMesh* pEast, CTerrainMesh* pNorthEast )
{
    m_pLandStyle = pLandStyle;

    m_pMap = new CHeightMap( g_pTerrainEngine, fWorldOffsetX, fWorldOffsetZ );
    if( m_pMap == NULL )
        return E_OUTOFMEMORY;

    m_pNorth    = pNorth;
    m_pEast     = pEast;
    m_pNorthEast = pNorthEast;
    m_fWorldOffsetX  = fWorldOffsetX;
    m_fWorldOffsetZ  = fWorldOffsetZ;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::InitDeviceObjects( D3DFORMAT fmtTexture )
{
    HRESULT hr;
    m_fmtTexture = fmtTexture;

    // Create height map using one of the following methods
    if( m_pLandStyle->HeightCreationType == HCT_FromFile )
    {
        TCHAR strFile[MAX_PATH];
        CMyApplication::FindMediaFileCch( strFile, MAX_PATH, m_pLandStyle->szHeightMap );
        if( FAILED( hr = m_pMap->CreateFromFile( strFile ) ) )
        {
            g_pApp->CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, m_pLandStyle->szHeightMap, strFile );
            return DXTRACE_ERR( TEXT("CreateFromFile"), hr );;
        }
    }
    else 
    {
        m_pMap->Create( ZONE_WIDTH, ZONE_HEIGHT );
        if( m_pLandStyle->HeightCreationType == HCT_CreateTest )
        {
//            m_pMap->CreateTestMap( 0.0f );
//            m_pMap->CreateSmallHills();
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
FLOAT CTerrainMesh::TextureColorFactor( DWORD iTexture, float fValue )
{
    float fHigh, fMid, fLow;

    fMid = m_pLandStyle->aLayerHeight[iTexture];

    if( iTexture==0 )
        fLow = -0.25f;
    else
        fLow = m_pLandStyle->aLayerHeight[iTexture-1];

    if( iTexture==m_pLandStyle->dwNumLayers-1 )
        fHigh = 1.25f;
    else
        fHigh = m_pLandStyle->aLayerHeight[iTexture+1];

    if( fValue > fHigh || fValue < fLow )
        return 0.0f;

    float fPercent;
    if( fValue > fMid )
        fPercent = (fHigh - fValue) / (fHigh - fMid);
    else
        fPercent = (fValue - fLow) / (fMid - fLow); 

    return fPercent;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
BYTE CTerrainMesh::TextureAlpha( float fHeight, int nIndex )
{
    BYTE aAlpha[MAX_SOURCE_TEXTURES];           
    BYTE aAlpha2[MAX_SOURCE_TEXTURES];           
    int  nTotalAlpha = 0;
    int  nTotalAlpha2 = 0;
    float aFactor[MAX_SOURCE_TEXTURES];
    float aFactor2[MAX_SOURCE_TEXTURES];
    float fTotalFactor = 0.0f;
    DWORD i;

    ZeroMemory( aAlpha, sizeof(BYTE)*MAX_SOURCE_TEXTURES );
    ZeroMemory( aAlpha2, sizeof(BYTE)*MAX_SOURCE_TEXTURES );
    ZeroMemory( aFactor, sizeof(float)*MAX_SOURCE_TEXTURES );
    ZeroMemory( aFactor2, sizeof(float)*MAX_SOURCE_TEXTURES );

    for( i=0; i<m_pLandStyle->dwNumLayers; i++ )
    {
        aFactor[i] = TextureColorFactor( i, fHeight );
        fTotalFactor += aFactor[i];
    }

    for( i=0; i<m_pLandStyle->dwNumLayers; i++ )
        aFactor[i] /= fTotalFactor;

    for( i=0; i<m_pLandStyle->dwNumLayers; i++ )
    {
        aAlpha[i] = (BYTE) (aFactor[i] * (float)0xFF);
        nTotalAlpha += (int) aAlpha[i];
    }

    for( i=0; i<m_pLandStyle->dwNumLayers; i++ )
    {
        aFactor2[i] = (float)aAlpha[i] / (float)nTotalAlpha;
        aAlpha2[i] = (BYTE) ( aFactor2[i] * 0xFF + 0.5f );
        nTotalAlpha2 += aAlpha2[i];
    }

    int nReturn = (int) (aAlpha[nIndex] * m_pLandStyle->fLayerBlendFactor[nIndex] );
    if( nReturn > 0xFF )
        nReturn = 0xFF;
    return (BYTE) nReturn;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::RestoreDeviceObjects( HWND hWndMain )
{
    HRESULT hr;

    int nWidth          = ZONE_WIDTH+1;
    int nHeight         = ZONE_HEIGHT+1;

    // Create texture using one of the following methods
    if( m_pLandStyle->TextureCreationType == TCT_FromFile )
    {
        // Read the texture from a file
        if( FAILED( hr = ReadTextureFromFile( nWidth, nHeight ) ) ) 
            return DXTRACE_ERR( TEXT("ReadTextureFromFile"), hr );
    }
    else if( m_pLandStyle->TextureCreationType == TCT_CreateTest )
    {
        if( FAILED( hr = CreateTestTexture( nWidth, nHeight ) ) ) 
            return DXTRACE_ERR( TEXT("CreateTestTexture"), hr );
    }
    else if( m_pLandStyle->TextureCreationType == TCT_CreateFromHeight )
    {
        // Create the texture based on the height map
        if( FAILED( hr = CreateTextureFromHeight( nWidth, nHeight ) ) ) 
            return DXTRACE_ERR( TEXT("CreateTextureFromHeight"), hr );
    }
    else if( m_pLandStyle->TextureCreationType == TCT_FromLayers )
    {
        if( g_Profile.bLoadFast )
        {
            if( FAILED( hr = CreateTestTexture( nWidth, nHeight ) ) ) 
                return DXTRACE_ERR( TEXT("CreateTestTexture"), hr );
        }
        else
        {
            // Create the texture by layering a number of detail textures
            if( FAILED( hr = CreateTextureFromLayers( nWidth, nHeight ) ) ) 
                return DXTRACE_ERR( TEXT("CreateTextureFromLayers"), hr );
        }
    }
    else
    {
        MessageBox( hWndMain, "Unknown texture creation type", "Donuts 4", MB_OK );
        return E_FAIL;
    }

    // Create mesh from the height map
    CreateMeshFromHeightMap( nWidth, nHeight );

    if( m_pLandStyle->bSaveMedia )
    {
        SaveMeshToXFile();
        SaveTextureToFile();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateMeshFromHeightMap
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::CreateMeshFromHeightMap( int nWidth, int nHeight )
{
    HRESULT hr;
    
    int nNumStrips      = (nWidth-1);
    int nQuadsPerStrip  = (nHeight-1);
    m_dwNumFaces    = nNumStrips * nQuadsPerStrip * 2;
    m_dwNumVerties  = nWidth * nHeight;

    hr = D3DXCreateMeshFVF( m_dwNumFaces, m_dwNumVerties, D3DXMESH_MANAGED, TERRIAN_FVF, g_pd3dDevice, &m_pMesh );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXCreateMeshFVF"), hr );

    WORD* pIndexBuffer = NULL;
    hr = m_pMesh->LockIndexBuffer( 0, (void**) &pIndexBuffer );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("LockIndexBuffer"), hr );

    int iStrip, iQuad;
    int iRow, iCol;
    float iX, iZ;

    for( iStrip = 0; iStrip<nNumStrips; iStrip++ )
    {
        WORD nCurRow1 = (iStrip+0)*nHeight;
        WORD nCurRow2 = (iStrip+1)*nHeight;

        for( iQuad = 0; iQuad<nQuadsPerStrip; iQuad++ )
        {
            // first tri 
            *pIndexBuffer++ = nCurRow1;
            *pIndexBuffer++ = nCurRow1 + 1;
            *pIndexBuffer++ = nCurRow2;

            // second tri 
            *pIndexBuffer++ = nCurRow1 + 1;
            *pIndexBuffer++ = nCurRow2 + 1;
            *pIndexBuffer++ = nCurRow2;

            nCurRow1++;
            nCurRow2++;
        }
    }

    hr = m_pMesh->UnlockIndexBuffer();
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("UnlockIndexBuffer"), hr );

    TERRIANVERTEX* pVertexBuffer = NULL;
    hr = m_pMesh->LockVertexBuffer( 0, (void**) &pVertexBuffer );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("LockVertexBuffer"), hr );

    float fSizeQuadX = 1.0f;
    float fSizeQuadZ = 1.0f;

    D3DSURFACE_DESC surfDesc;
    FLOAT fTexelSizeU;
    FLOAT fTexelSizeV;

    if( m_pTexture )
    {
        hr = m_pTexture->GetLevelDesc( 0, &surfDesc );
        fTexelSizeU = 1.0f/surfDesc.Width;
        fTexelSizeV = 1.0f/surfDesc.Height;
    }
    else
    {
        fTexelSizeU = 1.0f/256.0f;
        fTexelSizeV = 1.0f/256.0f;
    }

    iX = m_fWorldOffsetX;
    for( iCol = 0; iCol<nWidth; iCol++ )
    {
        iZ = m_fWorldOffsetZ;
        
        for( iRow = 0; iRow<nHeight; iRow++ )
        {
            // Add a nudge factor if we're along the edges to 
            // cover any minuate cracks in between the meshs
            FLOAT fNudgeX = 0.0f;
            FLOAT fNudgeZ = 0.0f;
            if( iRow==0 )
                fNudgeZ = -0.01f;
            if( iRow==nHeight-1 )
                fNudgeZ = 0.01f;
            if( iCol==0 )
                fNudgeX = -0.01f;
            if( iCol==nWidth-1 )
                fNudgeX = 0.01f;

            // Ask the terrain engine what the height is at this point
            pVertexBuffer->p = D3DXVECTOR3( fNudgeX+iX-m_fWorldOffsetX, 
                                            g_pTerrainEngine->GetHeight( iX, iZ ), 
                                            fNudgeZ+iZ-m_fWorldOffsetZ );

            // Compute the normal by hand
            D3DXVECTOR3 vecN;
            D3DXVECTOR3 vPt = D3DXVECTOR3( iX, g_pTerrain->GetHeight( iX, iZ ), iZ );
            D3DXVECTOR3 vN = D3DXVECTOR3( iX, g_pTerrain->GetHeight( iX+0.0f, iZ+1.0f ), iZ+1.0f );
            D3DXVECTOR3 vE = D3DXVECTOR3( iX+1.0f, g_pTerrain->GetHeight( iX+1.0f, iZ+0.0f ), iZ );
            D3DXVECTOR3 v1 = vN - vPt;
            D3DXVECTOR3 v2 = vE - vPt;
            D3DXVec3Cross( &vecN, &v1, &v2 );
            D3DXVec3Normalize(&vecN, &vecN);

            pVertexBuffer->n = vecN;

            // Set the texture coords from (0.0f + 0.5*texel) to (1.0f - 0.5*texel) 
            // to get perfect texel mapping on the mesh
            pVertexBuffer->tu = ( (float) iCol / (float) (nWidth-1)  ) * (1.0f-fTexelSizeU) + 0.5f*fTexelSizeU;
            pVertexBuffer->tv = ( (float) iRow / (float) (nHeight-1) ) * (1.0f-fTexelSizeV) + 0.5f*fTexelSizeV;

            pVertexBuffer++;
            iZ += fSizeQuadZ;
        }

        iX += fSizeQuadX;
    }

    hr = m_pMesh->UnlockVertexBuffer();
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("UnlockVertexBuffer"), hr );

    BOOL bGenAdj        = g_Profile.bOptimizeMesh || g_Profile.bCompactMesh || g_Profile.bSimplifyMesh;
    BOOL bOptimize      = g_Profile.bOptimizeMesh && bGenAdj;
    BOOL bCompact       = g_Profile.bCompactMesh && bOptimize;
    BOOL bSimplifyMesh  = g_Profile.bSimplifyMesh && bGenAdj;
    DWORD* pdwAdjaceny  = NULL;
    if( bGenAdj ) 
    {
        pdwAdjaceny = new DWORD[ 3 * m_pMesh->GetNumFaces() ];
        if( pdwAdjaceny == NULL )
            return E_OUTOFMEMORY;

        hr = m_pMesh->GenerateAdjacency( 0.01f, pdwAdjaceny );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("GenerateAdjacency"), hr );
    }

    if( bOptimize )
    {
        DWORD* pdwAdjacenyOut = NULL;
        if( bGenAdj )
        {
            pdwAdjacenyOut = new DWORD[ 3 * m_pMesh->GetNumFaces() ];
            if( pdwAdjacenyOut == NULL )
                return E_OUTOFMEMORY;
        }

        DWORD dwFlags = D3DXMESHOPT_VERTEXCACHE;
        if( bCompact )
            dwFlags |= D3DXMESHOPT_COMPACT;
        hr = m_pMesh->OptimizeInplace( dwFlags, pdwAdjaceny, pdwAdjacenyOut, NULL, NULL );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("D3DXSimplifyMesh"), hr );

        if( bGenAdj )
        {
            SAFE_DELETE_ARRAY( pdwAdjaceny );
            pdwAdjaceny = pdwAdjacenyOut;
        }
    }

    if( bGenAdj ) 
    {
        if( bSimplifyMesh )
        {
            ID3DXMesh* pMesh;
            D3DXATTRIBUTEWEIGHTS d3daw;
            ZeroMemory( &d3daw, sizeof(D3DXATTRIBUTEWEIGHTS) );
            d3daw.Position = 1.0f;
            d3daw.Boundary = 10000.0f;
            d3daw.Normal   = 1.0f;

            hr = D3DXSimplifyMesh( m_pMesh, pdwAdjaceny, &d3daw, NULL, (DWORD)(m_dwNumFaces*g_Profile.fSimplifyMeshFactor), D3DXMESHSIMP_FACE, &pMesh );
            if( FAILED(hr) )
                return DXTRACE_ERR( TEXT("D3DXSimplifyMesh"), hr );
            SAFE_RELEASE( m_pMesh );
            m_pMesh = pMesh;
        }

        SAFE_DELETE_ARRAY( pdwAdjaceny );
    }

    assert( m_pMesh != NULL );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::CorrectTextureEdge()
{
    HRESULT hr;

    if( NULL == m_pTexture )
        return S_OK;

    DWORD dwLevelCount = m_pTexture->GetLevelCount();
    
    for( DWORD iLevel=0; iLevel<dwLevelCount; iLevel++ )
    {
        D3DSURFACE_DESC surfDesc;
        hr = m_pTexture->GetLevelDesc( iLevel, &surfDesc );
    
        D3DLOCKED_RECT LockedRect;
        hr = m_pTexture->LockRect( iLevel, &LockedRect, NULL, 0 );
        if( FAILED(hr) )
            return S_OK; // can't lock texture if its a rendertarget
//            return DXTRACE_ERR( TEXT("LockRect"), hr );

        switch( surfDesc.Format )
        {
            case D3DFMT_A8R8G8B8:
            case D3DFMT_X8R8G8B8:
            {
                DWORD* pBits;
                for( DWORD iTexelZ=0; iTexelZ<surfDesc.Height; iTexelZ++ )
                {
                    FLOAT fMapZ = (float) iTexelZ / ( (float)surfDesc.Height / (float)m_pMap->m_nZSize );

                    pBits = (DWORD*) ((BYTE*)LockedRect.pBits + LockedRect.Pitch*iTexelZ);
                    pBits += (surfDesc.Width-1);
                    *pBits = g_pTerrainEngine->GetTexelColor( iLevel, 
                                                              m_fWorldOffsetX + m_pMap->m_fXSize,
                                                              m_fWorldOffsetZ + fMapZ );
                }        

                pBits = (DWORD*) ((BYTE*)LockedRect.pBits + LockedRect.Pitch*(surfDesc.Height-1));
                for( DWORD iTexelX=0; iTexelX<surfDesc.Width; iTexelX++ )
                {
                    FLOAT fMapX = (float) iTexelX / ( (float)surfDesc.Width / (float)m_pMap->m_nXSize );

                    *pBits = g_pTerrainEngine->GetTexelColor( iLevel, 
                                                              m_fWorldOffsetX + fMapX, 
                                                              m_fWorldOffsetZ + m_pMap->m_fZSize );

                    pBits++;
                }        

                break;
            }
        }

        hr = m_pTexture->UnlockRect( iLevel );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("UnlockRect"), hr );   
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::GenerateMipMaps()
{
    if( g_Profile.bGenerateMipMaps )
    {
        HRESULT hr;
        LPDIRECT3DTEXTURE9 pTexture = NULL;

        hr = D3DXCreateTexture( g_pd3dDevice, m_pLandStyle->dwTextureSize, m_pLandStyle->dwTextureSize, D3DX_DEFAULT, 0, 
                                m_fmtTexture, D3DPOOL_MANAGED, &pTexture );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );


        IDirect3DSurface9* pSurfaceSrc = NULL;
        IDirect3DSurface9* pSurfaceDest = NULL;
        pTexture->GetSurfaceLevel( 0, &pSurfaceDest );
        m_pTexture->GetSurfaceLevel( 0, &pSurfaceSrc );

        hr = D3DXLoadSurfaceFromSurface( pSurfaceDest, NULL, NULL, 
                                         pSurfaceSrc, NULL, NULL, 
                                         D3DX_FILTER_POINT, 0 );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("D3DXLoadSurfaceFromSurface"), hr );

        SAFE_RELEASE( pSurfaceDest );
        SAFE_RELEASE( pSurfaceSrc );

        SAFE_RELEASE( m_pTexture );
        m_pTexture = pTexture;
        pTexture = NULL;

        hr = D3DXFilterTexture( m_pTexture, NULL, 0, D3DX_FILTER_BOX );
    }

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::CreateTestTexture( int nWidth, int nHeight )
{
    HRESULT hr;
    
    hr = D3DXCreateTexture( g_pd3dDevice, nWidth, nHeight, 1, 0, 
                            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );
    
    D3DSURFACE_DESC surfDesc;
    hr = m_pTexture->GetLevelDesc( 0, &surfDesc );
    
    D3DLOCKED_RECT LockedRect;
    hr = m_pTexture->LockRect( 0, &LockedRect, NULL, 0 );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("LockRect"), hr );

    DWORD* pBits;
    for( DWORD iTexelZ=0; iTexelZ<surfDesc.Height; iTexelZ++ )
    {
        pBits = (DWORD*) ((BYTE*)LockedRect.pBits + LockedRect.Pitch*iTexelZ);

        for( DWORD iTexelX=0; iTexelX<surfDesc.Width; iTexelX++ )
        {
            *pBits = 0xFF00FF00;
            pBits++;
        }
    }        

    hr = m_pTexture->UnlockRect( 0 );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("UnlockRect"), hr );   

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::ReadTextureFromFile( int nWidth, int nHeight )
{
    HRESULT hr;

    D3DXIMAGE_INFO d3dxImageInfo;
    D3DXGetImageInfoFromFile( m_pLandStyle->szTextureMap, &d3dxImageInfo );

    // Create a texture w/ a format supported by the video card
    TCHAR strFile[MAX_PATH];
    CMyApplication::FindMediaFileCch( strFile, MAX_PATH, m_pLandStyle->szTextureMap );
    hr = D3DXCreateTextureFromFileEx( g_pd3dDevice, strFile,
                                      m_pLandStyle->dwTextureSize, m_pLandStyle->dwTextureSize, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR,
                                      D3DX_FILTER_LINEAR, 0, NULL, NULL, &m_pTexture );
    if( FAILED(hr) )
    {
        g_pApp->CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, m_pLandStyle->szTextureMap, strFile );
        return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateTextureFromLayers()
// Desc: This function takes a list of texture files and tiles them.  It does a 
//       multipass alpha blend into a final m_pTexture.  The alpha layers are 
//       created for each texture based on the height of the mesh.
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::CreateTextureFromLayers( int nWidth, int nHeight )
{
    HRESULT hr;
    D3DSURFACE_DESC surfDesc;
    D3DVIEWPORT9 vp;
    DWORD iTexture;
   
    LPDIRECT3DTEXTURE9 pSrcTex[MAX_SOURCE_TEXTURES];           
    ZeroMemory( pSrcTex, sizeof(LPDIRECT3DTEXTURE9)*MAX_SOURCE_TEXTURES );

    LPDIRECT3DTEXTURE9 pAlphaTex[MAX_SOURCE_TEXTURES];           
    ZeroMemory( pAlphaTex, sizeof(LPDIRECT3DTEXTURE9)*MAX_SOURCE_TEXTURES );

    DWORD i;

    // For each src texture, read the texture from a file and create an alpha mask for it
    for( i=0; i<m_pLandStyle->dwNumLayers; i++ )
    {
        // Read source texture from file.  
        TCHAR strFile[MAX_PATH];
        CMyApplication::FindMediaFileCch( strFile, MAX_PATH, m_pLandStyle->aLayerTexture[i] );
        hr = D3DXCreateTextureFromFileEx( g_pd3dDevice, strFile,
                                          D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 
                                          D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0, NULL, NULL, &pSrcTex[i] );
        if( FAILED(hr) )
        {
            g_pApp->CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, m_pLandStyle->aLayerTexture[i], strFile );
            return DXTRACE_ERR( TEXT("D3DXCreateTextureFromFileEx"), hr );
        }

        // Create alpha mask for each source texture.  
        hr = D3DXCreateTexture( g_pd3dDevice, nWidth, nHeight, 
                                1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
                                &pAlphaTex[i] );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );
    }

    // Get the backbuffer format
    LPDIRECT3DSURFACE9 pBackBuffer = NULL;
    D3DSURFACE_DESC    d3dsdBackBuffer;   // Surface desc of the backbuffer
    g_pd3dDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
    pBackBuffer->GetDesc( &d3dsdBackBuffer );
    SAFE_RELEASE( pBackBuffer );

    // Create a render target texture if possible
    hr = D3DXCreateTexture( g_pd3dDevice, m_pLandStyle->dwTextureSize, m_pLandStyle->dwTextureSize, 
                            1, D3DUSAGE_RENDERTARGET, 
                            D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture );
    if( FAILED(hr) )
    {
        // Fallback to a normal texture with the same format as the backbuffer
        // normally a RENDERTARGET surface can be created using the backbuffer format
        hr = D3DXCreateTexture( g_pd3dDevice, m_pLandStyle->dwTextureSize, m_pLandStyle->dwTextureSize, 1, 0, 
                                D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );
    }

    // Create a ID3DXRenderToSurface using the same height/width/format as the
    // texture that we're are going to use with this ID3DXRenderToSurface
    hr = m_pTexture->GetLevelDesc( 0, &surfDesc );
    ID3DXRenderToSurface* pRenderToSurface = NULL;
    hr = D3DXCreateRenderToSurface( g_pd3dDevice, surfDesc.Width, surfDesc.Height, surfDesc.Format, 
                                    FALSE, D3DFMT_UNKNOWN, &pRenderToSurface );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXCreateRenderToSurface"), hr );

    // Compute the alpha mask for each layer
    for( iTexture=0; iTexture<m_pLandStyle->dwNumLayers; iTexture++ )
    {
        hr = pAlphaTex[iTexture]->GetLevelDesc( 0, &surfDesc );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("GetLevelDesc"), hr );
        assert( surfDesc.Format == D3DFMT_A8R8G8B8 );

        D3DLOCKED_RECT LockedRect;
        hr = pAlphaTex[iTexture]->LockRect( 0, &LockedRect, NULL, 0 );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("LockRect"), hr );

        DWORD* pBits;
        for( DWORD iTexelZ=0; iTexelZ<surfDesc.Height; iTexelZ++ )
        {
            pBits = (DWORD*) ((BYTE*)LockedRect.pBits + LockedRect.Pitch*iTexelZ);

            for( DWORD iTexelX=0; iTexelX<surfDesc.Width; iTexelX++ )
            {
                FLOAT fHeight;
                BYTE  nAlpha;

                // The final mesh texture 
                float iMapX = ( (float) iTexelX / (float) surfDesc.Width )  * m_pMap->m_fXSize;
                float iMapZ = ( (float) iTexelZ / (float) surfDesc.Height ) * m_pMap->m_fZSize;

                // Get the height of the mesh at this point
                fHeight = g_pTerrainEngine->GetHeight( iMapX + m_fWorldOffsetX, iMapZ + m_fWorldOffsetZ );
                fHeight /= MAX_HEIGHT_OF_MAP;
 
                // The TextureAlpha() function will return the alpha for this
                // mask.  It also assures that the sum of the alpha mask at each point
                // adds up to 0xFF.
                nAlpha = TextureAlpha( fHeight, iTexture );  

                *pBits = (nAlpha << 24);
                pBits++;
            }
        }        
        hr = pAlphaTex[iTexture]->UnlockRect( 0 );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("UnlockRect"), hr );   
    } 

    // Create a RHW quad to render all the layers into.  The render target
    // will be the final texture, m_pTexture.
    int nMeshWidth      = 16;
    int nMeshHeight     = 16;
    int nNumStrips      = (nMeshWidth-1);
    int nQuadsPerStrip  = (nMeshHeight-1);
    DWORD dwNumFaces    = nNumStrips * nQuadsPerStrip * 2;
    DWORD dwNumVerties  = nMeshWidth * nMeshHeight;
    LPDIRECT3DINDEXBUFFER9  pIB = NULL;
    LPDIRECT3DVERTEXBUFFER9 pVB = NULL;

    hr = g_pd3dDevice->CreateIndexBuffer( dwNumFaces * 3 * sizeof(WORD),
                                         D3DUSAGE_WRITEONLY,
                                         D3DFMT_INDEX16, D3DPOOL_MANAGED,
                                         &pIB, NULL );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("CreateIndexBuffer"), hr );

    hr = g_pd3dDevice->CreateVertexBuffer( dwNumVerties * sizeof(RHW_VERTEX),
                                         D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
                                         RHW_FVF, D3DPOOL_DEFAULT ,
                                         &pVB, NULL );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("CreateVertexBuffer"), hr );

    WORD* pIndexBuffer = NULL;
    hr = pIB->Lock( 0, 0, (void**) &pIndexBuffer, 0 );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("LockIndexBuffer"), hr );

    int iStrip, iQuad;
    int iRow, iCol;
    float iX, iY;

    for( iStrip = 0; iStrip<nNumStrips; iStrip++ )
    {
        WORD nCurRow1 = (iStrip+0)*nMeshHeight;
        WORD nCurRow2 = (iStrip+1)*nMeshHeight;

        for( iQuad = 0; iQuad<nQuadsPerStrip; iQuad++ )
        {
            // first tri 
            *pIndexBuffer++ = nCurRow1;
            *pIndexBuffer++ = nCurRow1 + 1;
            *pIndexBuffer++ = nCurRow2;

            // second tri 
            *pIndexBuffer++ = nCurRow1 + 1;
            *pIndexBuffer++ = nCurRow2 + 1;
            *pIndexBuffer++ = nCurRow2;

            nCurRow1++;
            nCurRow2++;
        }
    }

    hr = pIB->Unlock();
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("UnlockIndexBuffer"), hr );

    // Setup the viewport for the ID3DXRenderToSurface.  Make the viewport the
    // same size as the surface that will be the target.
    hr = m_pTexture->GetLevelDesc( 0, &surfDesc );
    vp.Width  = surfDesc.Width;
    vp.Height = surfDesc.Height;
    vp.MinZ   = 0;
    vp.MaxZ   = 1.0f;
    vp.X      = 0;
    vp.Y      = 0;

    // Render to the surface of m_pTexture.  Use the ID3DXRenderToSurface 
    // to render surface, even if the surface isn't a render target.  Some
    // video cards don't support textures as render targets.
    IDirect3DSurface9* pRenderSurface = NULL;
    m_pTexture->GetSurfaceLevel( 0, &pRenderSurface );
    pRenderToSurface->BeginScene( pRenderSurface, &vp );

    g_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET, 0xFF000000, 1.0f, 0L );

    D3DMATERIAL9 mtrl;
    D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f );
    hr = g_pd3dDevice->SetMaterial( &mtrl );

    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

    hr = g_pd3dDevice->SetFVF( RHW_FVF );
    hr = g_pd3dDevice->SetStreamSource( 0, pVB, 0, sizeof(RHW_VERTEX) );
    hr = g_pd3dDevice->SetIndices( pIB );

    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,     D3DBLEND_SRCALPHA  );
    g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,    D3DBLEND_ONE );
    g_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, 0 );

    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1  );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1  );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );

    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_BLENDCURRENTALPHA );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_TFACTOR );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1  );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAARG1, D3DTA_CURRENT );

    g_pd3dDevice->SetTextureStageState( 2, D3DTSS_COLOROP,   D3DTOP_DISABLE );

    for( i=0; i<m_pLandStyle->dwNumLayers; i++ )
    {
        RHW_VERTEX* pVertexBuffer = NULL;
        hr = pVB->Lock( 0, 0, (void**) &pVertexBuffer, D3DLOCK_DISCARD );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("LockVertexBuffer"), hr );

        float fSizeQuadX = 1.0f;
        float fSizeQuadY = 1.0f;
        hr = m_pTexture->GetLevelDesc( 0, &surfDesc );

        iX = 0.0f;
        for( iCol = 0; iCol<nMeshWidth; iCol++ )
        {
            iY = 0.0f;
            
            for( iRow = 0; iRow<nMeshHeight; iRow++ )
            {
                // The first texture is the alpha mask.  
                float tu1 = (float) iRow / (float) (nMeshWidth-1);
                float tv1 = (float) iCol / (float) (nMeshHeight-1);

                // The second texture is the source texture, and it's tiled.
                // Also add a small amount of random variation to the tiling.
                float tu2 = (float) iRow / (float)  (nMeshWidth-1) * m_pLandStyle->aLayerTile[i] + ((float)(rand() % 100)/100.0f-0.50f)*m_pLandStyle->aLayerRandomness[i];
                float tv2 = (float) iCol / (float) (nMeshHeight-1) * m_pLandStyle->aLayerTile[i] + ((float)(rand() % 100)/100.0f-0.50f)*m_pLandStyle->aLayerRandomness[i];

                pVertexBuffer->p   = D3DXVECTOR4( tu1*surfDesc.Width, tv1*surfDesc.Height, 0.0f, 1.0f );
                pVertexBuffer->tu1 = tu1;
                pVertexBuffer->tv1 = tv1;

                pVertexBuffer->tu2 = tu2;
                pVertexBuffer->tv2 = tv2;

                pVertexBuffer++;

                iY += fSizeQuadY;
            }

            iX += fSizeQuadX;
        }

        hr = pVB->Unlock(); 
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("UnlockVertexBuffer"), hr );

        g_pd3dDevice->SetStreamSource( 0, pVB, 0, sizeof(RHW_VERTEX) );

        g_pd3dDevice->SetTexture( 0, pAlphaTex[i] );
        g_pd3dDevice->SetTexture( 1, pSrcTex[i] );

        g_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, dwNumVerties, 0, dwNumFaces );
    }

    hr = pRenderToSurface->EndScene( D3DX_FILTER_LINEAR );
    SAFE_RELEASE( pRenderSurface );

    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );

    SAFE_RELEASE( pIB );
    SAFE_RELEASE( pVB );

    SAFE_RELEASE( pRenderToSurface );

    for( i=0; i<m_pLandStyle->dwNumLayers; i++ )
    {
        SAFE_RELEASE( pSrcTex[i] );
        SAFE_RELEASE( pAlphaTex[i] );
    }
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::CreateTextureFromHeight( int nWidth, int nHeight )
{
    HRESULT hr;

    // Create a D3DFMT_A8R8G8B8 texture.  use D3DPOOL_SCRATCH to create this texture 
    // even if the video card doesn't support it.
    LPDIRECT3DTEXTURE9 pScratchTexture = NULL;
    hr = D3DXCreateTexture( g_pd3dDevice, nWidth*2, nHeight*2, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &pScratchTexture );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );

    D3DSURFACE_DESC surfDesc;
    hr = pScratchTexture->GetLevelDesc( 0, &surfDesc );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("GetLevelDesc"), hr );
    assert( surfDesc.Format == D3DFMT_A8R8G8B8 );

    D3DLOCKED_RECT LockedRect;
    hr = pScratchTexture->LockRect( 0, &LockedRect, NULL, 0 );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("LockRect"), hr );

    DWORD* pBits;
    for( DWORD iTexelZ=0; iTexelZ<surfDesc.Height; iTexelZ++ )
    {
        pBits = (DWORD*) ((BYTE*)LockedRect.pBits + LockedRect.Pitch*iTexelZ);

        for( DWORD iTexelX=0; iTexelX<surfDesc.Width; iTexelX++ )
        {
            FLOAT fHeight;

            fHeight = g_pTerrainEngine->GetHeight( iTexelX/2.0f + m_fWorldOffsetX, iTexelZ/2.0f + m_fWorldOffsetZ );
            fHeight /= MAX_HEIGHT_OF_MAP;

            float aClrFactor[10];
            DWORD iColor;
            for( iColor=0; iColor<m_pLandStyle->dwNumLayers; iColor++ )
            {
                float fHigh, fLow;

                if( iColor==0 )
                    fLow = -0.25f;
                else
                    fLow = m_pLandStyle->aLayerHeight[iColor-1];

                if( iColor==m_pLandStyle->dwNumLayers-1 )
                    fHigh = 1.25f;
                else
                    fHigh = m_pLandStyle->aLayerHeight[iColor+1];

                aClrFactor[iColor] = TextureColorFactor( iColor, fHeight );  
            }

            FLOAT fRed   = 0.0f;
            FLOAT fGreen = 0.0f;
            FLOAT fBlue  = 0.0f;

            for( iColor=0; iColor<m_pLandStyle->dwNumLayers; iColor++ )
            {
                fRed   += aClrFactor[iColor]*(float)RVALUE(m_pLandStyle->aLayerColor[iColor]);
                fGreen += aClrFactor[iColor]*(float)GVALUE(m_pLandStyle->aLayerColor[iColor]);
                fBlue  += aClrFactor[iColor]*(float)BVALUE(m_pLandStyle->aLayerColor[iColor]);
            }

            DWORD nRed   = (DWORD) fRed;
            DWORD nGreen = (DWORD) fGreen;
            DWORD nBlue  = (DWORD) fBlue;

            if( nRed > 0xFF )
                nRed = 0xFF;
            if( nGreen > 0xFF )
                nGreen = 0xFF;
            if( nBlue > 0xFF )
                nBlue = 0xFF;

            *pBits = (0xFF << 24) + (nRed << 16) + (nGreen << 8) + (nBlue << 0);
            pBits++;
        }
    }        

    hr = pScratchTexture->UnlockRect( 0 );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("UnlockRect"), hr );   

    // Create a texture w/ a format supported by the video card
    hr = D3DXCreateTexture( g_pd3dDevice, nWidth*2, nHeight*2, 1, 0, m_fmtTexture, D3DPOOL_MANAGED, &m_pTexture );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );

    // Use d3dx to convert from the scratch texture to a card supported texture format 
    IDirect3DSurface9* pSurfaceSrc = NULL;
    IDirect3DSurface9* pSurfaceDest = NULL;
    m_pTexture->GetSurfaceLevel( 0, &pSurfaceDest );
    pScratchTexture->GetSurfaceLevel( 0, &pSurfaceSrc );

    hr = D3DXLoadSurfaceFromSurface( pSurfaceDest, NULL, NULL, pSurfaceSrc, NULL, NULL, D3DX_FILTER_POINT, 0 );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXLoadSurfaceFromSurface"), hr );

    SAFE_RELEASE( pSurfaceDest );
    SAFE_RELEASE( pSurfaceSrc );

    SAFE_RELEASE( pScratchTexture );
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::FrameMove( const float fElapsedTime )
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::RenderFrame( float fWrapOffsetX, float fWrapOffsetZ, DWORD* pdwNumVerts )
{
    HRESULT hr = S_OK;

    assert( m_pMesh != NULL );

    // Setup a material
    D3DMATERIAL9 mtrl;
    D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f );
    g_pd3dDevice->SetMaterial( &mtrl );
    g_pd3dDevice->SetTexture( 0, m_pTexture );

    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,     D3DBLEND_SRCALPHA  );
    g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,    D3DBLEND_INVSRCALPHA );

    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE  );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1  );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

    D3DXMatrixTranslation( &m_matWorld, fWrapOffsetX + m_fWorldOffsetX, 0.0f, fWrapOffsetZ + m_fWorldOffsetZ );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matWorld );

    if( pdwNumVerts )
        *pdwNumVerts = m_pMesh->GetNumFaces();

    if( g_Profile.bRenderGround )
    {
        hr = m_pMesh->DrawSubset( 0 );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("DrawSubset"), hr );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::InvalidateDeviceObjects()
{
    SAFE_RELEASE( m_pMesh );
    SAFE_RELEASE( m_pTexture );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::DeleteDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CTerrainMesh::FinalCleanup()
{
    SAFE_DELETE( m_pMap );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
DWORD CTerrainMesh::GetTexelColor( DWORD iLevel, float x, float z )
{
    HRESULT hr;
    DWORD dwResult = 0;

    D3DSURFACE_DESC surfDesc;
    hr = m_pTexture->GetLevelDesc( iLevel, &surfDesc );
    
    x -= m_fWorldOffsetX;
    z -= m_fWorldOffsetZ;

    DWORD dwTexelX = (DWORD) ( x * (surfDesc.Width  / m_pMap->m_fXSize) );
    DWORD dwTexelZ = (DWORD) ( z * (surfDesc.Height / m_pMap->m_fZSize) );

    D3DLOCKED_RECT LockedRect;
    hr = m_pTexture->LockRect( iLevel, &LockedRect, NULL, 0 );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("LockRect"), hr );

    switch( surfDesc.Format )
    {
        case D3DFMT_A8R8G8B8:
        case D3DFMT_X8R8G8B8:
        {
            DWORD* pBits = (DWORD*) ((BYTE*)LockedRect.pBits + LockedRect.Pitch*dwTexelZ);
            pBits += dwTexelX;
            dwResult = *pBits;
            break;
        }
    }

    hr = m_pTexture->UnlockRect( iLevel );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("UnlockRect"), hr );   

    return dwResult;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::SaveMeshToXFile()
{
/*
    HRESULT hr;

    TCHAR strFileName[MAX_PATH];
    lstrcpy( strFileName, m_pLandStyle->szHeightMap );
    strFileName[lstrlen(strFileName)-4] = 0;
    lstrcat( strFileName, TEXT("-save.x") );

    DWORD* pdwAdjaceny  = NULL;
    pdwAdjaceny = new DWORD[ 3 * m_pMesh->GetNumFaces() ];
    if( pdwAdjaceny == NULL )
        return E_OUTOFMEMORY;

    hr = m_pMesh->GenerateAdjacency( 0.01f, pdwAdjaceny );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("GenerateAdjacency"), hr );

    hr = D3DXSaveMeshToX( strFileName, m_pMesh, pdwAdjaceny, NULL, 0, DXFILEFORMAT_TEXT );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXSaveMeshToX"), hr );
    
    SAFE_DELETE_ARRAY( pdwAdjaceny );
*/  
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CTerrainMesh::SaveTextureToFile()
{
    HRESULT hr;

    TCHAR strFileName[MAX_PATH];
    lstrcpy( strFileName, m_pLandStyle->szHeightMap );
    strFileName[lstrlen(strFileName)-4] = 0;
    lstrcat( strFileName, TEXT("-save.bmp") );

    hr = D3DXSaveTextureToFile( strFileName, D3DXIFF_BMP, m_pTexture, NULL );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXSaveTextureToFile"), hr );
    
    return S_OK;
}

