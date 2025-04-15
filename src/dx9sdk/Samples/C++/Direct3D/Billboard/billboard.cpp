//-----------------------------------------------------------------------------
// File: Billboard.cpp
//
// Desc: Example code showing how to do billboarding. The sample uses
//       billboarding to draw some trees.
//
//       Note: This implementation is for billboards that are fixed to rotate
//       about the Y-axis, which is good for things like trees. For
//       unconstrained billboards, like explosions in a flight sim, the
//       technique is the same, but the the billboards are positioned slightly
//       differently. Try using the inverse of the view matrix, TL-vertices, or
//       some other technique.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <Windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <math.h>
#include <D3DX9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFile.h"
#include "D3DFont.h"
#include "D3DUtil.h"




//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define NUM_TREES 500

// Need global access to the eye direction used by the callback to sort trees
D3DXVECTOR3 g_vDir;

// Simple function to define "hilliness" for terrain
inline FLOAT HeightField( FLOAT x, FLOAT y )
{
    return 9*(cosf(x/20+0.2f)*cosf(y/15-0.2f)+1.0f);
}

// Custom vertex type for the trees
struct TREEVERTEX
{
    D3DXVECTOR3 p;      // Vertex position
    DWORD       color;  // Vertex color
    FLOAT       tu, tv; // Vertex texture coordinates

    static const DWORD FVF;
};
const DWORD TREEVERTEX::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

// Tree textures to use
TCHAR* g_strTreeTextures[] =
{
    _T("Tree02S.dds"),
    _T("Tree35S.dds"),
    _T("Tree01S.dds"),
};

#define NUMTREETEXTURES 3




//-----------------------------------------------------------------------------
// Name: Tree
// Desc: Simple structure to hold data for rendering a tree
//-----------------------------------------------------------------------------
struct Tree
{
    TREEVERTEX  v[4];           // Four corners of billboard quad
    D3DXVECTOR3 vPos;           // Origin of tree
    DWORD       dwTreeTexture;  // Which texture map to use
    DWORD       dwOffset;       // Offset into vertex buffer of tree's vertices
};




//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
    CD3DFont*     m_pFont;              // Font for drawing text
    CD3DMesh*     m_pTerrain;           // Terrain object
    CD3DMesh*     m_pSkyBox;            // Skybox background object

    LPDIRECT3DVERTEXBUFFER9 m_pTreeVB;  // Vertex buffer for rendering a tree
    LPDIRECT3DTEXTURE9      m_pTreeTextures[NUMTREETEXTURES]; // Tree images
    D3DXMATRIXA16    m_matBillboardMatrix; // Used for billboard orientation
    Tree          m_Trees[NUM_TREES];   // Array of tree info

    D3DXVECTOR3   m_vEyePt;             // Camera position

    BOOL    IsTreePositionValid( DWORD );
    HRESULT ConfirmDevice( D3DCAPS9*, DWORD, D3DFORMAT, D3DFORMAT );
    HRESULT DrawBackground();
    HRESULT DrawTrees();

protected:
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT FinalCleanup();
    HRESULT Render();
    HRESULT FrameMove();

public:
    CMyD3DApplication();
};


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything, and goes into a
//       message-processing loop. Idle time is used to render the scene.
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    CMyD3DApplication d3dApp;

    InitCommonControls();
    if( FAILED( d3dApp.Create( hInst ) ) )
        return 0;

    return d3dApp.Run();
}




//-----------------------------------------------------------------------------
// Name: CMyD3DApplication()
// Desc: Application constructor. Sets attributes for the app.
//-----------------------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
{
    m_strWindowTitle    = _T("Billboard: D3D Billboarding Example");
    m_d3dEnumeration.AppUsesDepthBuffer = TRUE;

    m_pFont        = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pSkyBox      = new CD3DMesh();
    m_pTerrain     = new CD3DMesh();
    m_pTreeVB      = NULL;

    for( DWORD i=0; i<NUMTREETEXTURES; i++ )
        m_pTreeTextures[i] = NULL;
}




//-----------------------------------------------------------------------------
// Name: IsTreePositionValid
// Desc: Verifies that the tree at the given index is sufficiently spaced
//       from the other trees. If trees are placed too closely, one tree
//       can quickly pop in front of the other as the camera angle changes.
//-----------------------------------------------------------------------------
BOOL CMyD3DApplication::IsTreePositionValid( DWORD iTree )
{
    FLOAT x = m_Trees[iTree].vPos.x;
    FLOAT z = m_Trees[iTree].vPos.z;

    for( DWORD i=0; i < iTree; i++ )
    {
        double fDeltaX = fabs( x - m_Trees[i].vPos.x );
        double fDeltaZ = fabs( z - m_Trees[i].vPos.z );

        if( 3.0 > pow( fDeltaX, 2 ) + pow( fDeltaZ, 2 ) )
            return FALSE;
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    // Initialize the tree data
    for( WORD i=0; i<NUM_TREES; i++ )
    {
        do
        {
            // Position the trees randomly
            FLOAT fTheta  = 2.0f*D3DX_PI*(FLOAT)rand()/RAND_MAX;
            FLOAT fRadius = 25.0f + 55.0f * (FLOAT)rand()/RAND_MAX;
            m_Trees[i].vPos.x  = fRadius * sinf(fTheta);
            m_Trees[i].vPos.z  = fRadius * cosf(fTheta);
            m_Trees[i].vPos.y  = HeightField( m_Trees[i].vPos.x, m_Trees[i].vPos.z );
        }
        while( !IsTreePositionValid( i ) );

        // Size the trees randomly
        FLOAT fWidth  = 1.0f + 0.2f * (FLOAT)(rand()-rand())/RAND_MAX;
        FLOAT fHeight = 1.4f + 0.4f * (FLOAT)(rand()-rand())/RAND_MAX;

        // Each tree is a random color between red and green
        DWORD r = (255-190) + (DWORD)(190*(FLOAT)(rand())/RAND_MAX);
        DWORD g = (255-190) + (DWORD)(190*(FLOAT)(rand())/RAND_MAX);
        DWORD b = 0;
        DWORD dwColor = 0xff000000 + (r<<16) + (g<<8) + (b<<0);

        m_Trees[i].v[0].p     = D3DXVECTOR3(-fWidth, 0*fHeight, 0.0f );
        m_Trees[i].v[0].color = dwColor;
        m_Trees[i].v[0].tu    = 0.0f;   m_Trees[i].v[0].tv = 1.0f;
        m_Trees[i].v[1].p     = D3DXVECTOR3(-fWidth, 2*fHeight, 0.0f  );
        m_Trees[i].v[1].color = dwColor;
        m_Trees[i].v[1].tu    = 0.0f;   m_Trees[i].v[1].tv = 0.0f;
        m_Trees[i].v[2].p     = D3DXVECTOR3( fWidth, 0*fHeight, 0.0f  );
        m_Trees[i].v[2].color = dwColor;
        m_Trees[i].v[2].tu    = 1.0f;   m_Trees[i].v[2].tv = 1.0f;
        m_Trees[i].v[3].p     = D3DXVECTOR3( fWidth, 2*fHeight, 0.0f  );
        m_Trees[i].v[3].color = dwColor;
        m_Trees[i].v[3].tu    = 1.0f;   m_Trees[i].v[3].tv = 0.0f;

        // Pick a random texture for the tree
        m_Trees[i].dwTreeTexture = (DWORD)( ( NUMTREETEXTURES * rand() ) / (FLOAT)RAND_MAX );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: TreeSortCB()
// Desc: Callback function for sorting trees in back-to-front order
//-----------------------------------------------------------------------------
int __cdecl TreeSortCB( const VOID* arg1, const VOID* arg2 )
{
    Tree* p1 = (Tree*)arg1;
    Tree* p2 = (Tree*)arg2;
    
    FLOAT d1 = p1->vPos.x * g_vDir.x + p1->vPos.z * g_vDir.z;
    FLOAT d2 = p2->vPos.x * g_vDir.x + p2->vPos.z * g_vDir.z;
    if (d1 < d2)
        return +1;

    return -1;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    // Get the eye and lookat points from the camera's path
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXVECTOR3 vEyePt;
    D3DXVECTOR3 vLookatPt;

    vEyePt.x = 30.0f*cosf( 0.8f * ( m_fTime ) );
    vEyePt.z = 30.0f*sinf( 0.8f * ( m_fTime ) );
    vEyePt.y = 4 + HeightField( vEyePt.x, vEyePt.z );

    vLookatPt.x = 30.0f*cosf( 0.8f * ( m_fTime + 0.5f ) );
    vLookatPt.z = 30.0f*sinf( 0.8f * ( m_fTime + 0.5f ) );
    vLookatPt.y = vEyePt.y - 1.0f;

    // Set the app view matrix for normal viewing
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // Set up a rotation matrix to orient the billboard towards the camera.
    D3DXVECTOR3 vDir = vLookatPt - vEyePt;
    if( vDir.x > 0.0f )
        D3DXMatrixRotationY( &m_matBillboardMatrix, -atanf(vDir.z/vDir.x)+D3DX_PI/2 );
    else
        D3DXMatrixRotationY( &m_matBillboardMatrix, -atanf(vDir.z/vDir.x)-D3DX_PI/2 );
    g_vDir   = vDir;

    // Sort trees in back-to-front order
    qsort( m_Trees, NUM_TREES, sizeof(Tree), TreeSortCB );

    // Store vectors used elsewhere
    m_vEyePt = vEyePt;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DrawTrees()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::DrawTrees()
{
    // Set diffuse blending for alpha set in vertices.
    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
    m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

    // Enable alpha testing (skips pixels with less than a certain alpha.)
    if( m_d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL )
    {
        m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
        m_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,        0x08 );
        m_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
    }

    // Loop through and render all trees
    m_pd3dDevice->SetStreamSource( 0, m_pTreeVB, 0, sizeof(TREEVERTEX) );
    m_pd3dDevice->SetFVF( TREEVERTEX::FVF );
    for( DWORD i=0; i<NUM_TREES; i++ )
    {
        // Quick culling for trees behind the camera
        // This calculates the tree position relative to the camera, and
        // projects that vector against the camera's direction vector. A
        // negative dot product indicates a non-visible tree.
        if( 0 > ( m_Trees[i].vPos.x - m_vEyePt.x ) * g_vDir.x + 
                ( m_Trees[i].vPos.z - m_vEyePt.z ) * g_vDir.z )
        {
            break;
        }
        
        // Set the tree texture
        m_pd3dDevice->SetTexture( 0, m_pTreeTextures[m_Trees[i].dwTreeTexture] );

        // Translate the billboard into place
        m_matBillboardMatrix._41 = m_Trees[i].vPos.x;
        m_matBillboardMatrix._42 = m_Trees[i].vPos.y;
        m_matBillboardMatrix._43 = m_Trees[i].vPos.z;
        m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matBillboardMatrix );

        // Render the billboard
        m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, m_Trees[i].dwOffset, 2 );
    }

    // Restore state
    D3DXMATRIXA16  matWorld;
    D3DXMatrixIdentity( &matWorld );
    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
    m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE,    FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   FALSE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        // Render the Skybox
        {
            // Center view matrix for skybox and disable zbuffer
            D3DXMATRIXA16 matView, matViewSave;
            m_pd3dDevice->GetTransform( D3DTS_VIEW, &matViewSave );
            matView = matViewSave;
            matView._41 = 0.0f; matView._42 = -0.3f; matView._43 = 0.0f;
            m_pd3dDevice->SetTransform( D3DTS_VIEW,      &matView );
            m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
            // Some cards do not disable writing to Z when 
            // D3DRS_ZENABLE is FALSE. So do it explicitly
            m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );

            // Render the skybox
            m_pSkyBox->Render( m_pd3dDevice );

            // Restore the render states
            m_pd3dDevice->SetTransform( D3DTS_VIEW,      &matViewSave );
            m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
            m_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
        }

        // Draw the terrain
        m_pTerrain->Render( m_pd3dDevice );

        // Draw the trees
        DrawTrees();

        // Output statistics
        m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );

        // End the scene.
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: This creates all device-dependent managed objects, such as managed
//       textures and managed vertex buffers.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;

    // Initialize the font's internal textures
    m_pFont->InitDeviceObjects( m_pd3dDevice );

    // Create the tree textures
    for( DWORD i=0; i<NUMTREETEXTURES; i++ )
    {
        if( FAILED( hr = D3DUtil_CreateTexture( m_pd3dDevice, g_strTreeTextures[i],
                                                &m_pTreeTextures[i] ) ) )
            return hr;
    }

    // Create a quad for rendering each tree
    if( FAILED( hr = m_pd3dDevice->CreateVertexBuffer( NUM_TREES*4*sizeof(TREEVERTEX),
                                                       D3DUSAGE_WRITEONLY, TREEVERTEX::FVF,
                                                       D3DPOOL_MANAGED, &m_pTreeVB, NULL ) ) )
    {
        return hr;
    }

    // Copy tree mesh data into vertexbuffer
    TREEVERTEX* v;
    m_pTreeVB->Lock( 0, 0, (void**)&v, 0 );

    INT iTree;
    DWORD dwOffset = 0;
    for( iTree = 0; iTree < NUM_TREES; iTree++ )
    {
        memcpy( &v[dwOffset], m_Trees[iTree].v, 4*sizeof(TREEVERTEX) );
        m_Trees[iTree].dwOffset = dwOffset;
        dwOffset += 4;
    }

    m_pTreeVB->Unlock();

    // Load the skybox
    if( FAILED( m_pSkyBox->Create( m_pd3dDevice, _T("SkyBox2.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;

    // Load the terrain
    if( FAILED( m_pTerrain->Create( m_pd3dDevice, _T("SeaFloor.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;

    // Add some "hilliness" to the terrain
    LPDIRECT3DVERTEXBUFFER9 pVB;
    if( SUCCEEDED( m_pTerrain->GetSysMemMesh()->GetVertexBuffer( &pVB ) ) )
    {
        struct VERTEX { FLOAT x,y,z,tu,tv; };
        VERTEX* pVertices;
        DWORD   dwNumVertices = m_pTerrain->GetSysMemMesh()->GetNumVertices();

        pVB->Lock( 0, 0, (void**)&pVertices, 0 );

        for( DWORD i=0; i<dwNumVertices; i++ )
            pVertices[i].y = HeightField( pVertices[i].x, pVertices[i].z );

        pVB->Unlock();
        pVB->Release();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Restore device-memory objects and state after a device is created or
//       resized.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    // Restore the device objects for the meshes and fonts
    m_pTerrain->RestoreDeviceObjects( m_pd3dDevice );
    m_pSkyBox->RestoreDeviceObjects( m_pd3dDevice );
    m_pFont->RestoreDeviceObjects();

    // Set the transform matrices (view and world are updated per frame)
    D3DXMATRIXA16 matProj;
    FLOAT fAspect = m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, fAspect, 1.0f, 100.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    // Set up the default texture states
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP );

    m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,      TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING,     FALSE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Called when the device-dependent objects are about to be lost.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pTerrain->InvalidateDeviceObjects();
    m_pSkyBox->InvalidateDeviceObjects();
    m_pFont->InvalidateDeviceObjects();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::DeleteDeviceObjects()
{
    m_pFont->DeleteDeviceObjects();

    m_pTerrain->Destroy();
    m_pSkyBox->Destroy();

    for( DWORD i=0; i<NUMTREETEXTURES; i++ )
        SAFE_RELEASE( m_pTreeTextures[i] );

    SAFE_RELEASE( m_pTreeVB )

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FinalCleanup()
{
    SAFE_DELETE( m_pFont );
    SAFE_DELETE( m_pTerrain );
    SAFE_DELETE( m_pSkyBox );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
                                          D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat )
{
    if( dwBehavior & D3DCREATE_PUREDEVICE )
        return E_FAIL; // GetTransform doesn't work on PUREDEVICE

    // Need to support post-pixel processing (for alpha blending)
    if( FAILED( m_pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
        adapterFormat, D3DUSAGE_RENDERTARGET | D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
        D3DRTYPE_SURFACE, backBufferFormat ) ) )
    {
        return E_FAIL;
    }

    // This sample uses alpha textures and/or straight alpha. Make sure the
    // device supports them
    if( pCaps->TextureCaps & D3DPTEXTURECAPS_ALPHAPALETTE )
        return S_OK;
    if( pCaps->TextureCaps & D3DPTEXTURECAPS_ALPHA )
        return S_OK;

    return E_FAIL;
}




