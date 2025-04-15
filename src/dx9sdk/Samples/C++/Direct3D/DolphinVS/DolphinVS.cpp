//-----------------------------------------------------------------------------
// File: DolphinVS.cpp
//
// Desc: Sample of swimming dolphin
//
//       Note: This code uses the D3D Framework helper library.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <Windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <D3DX9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFile.h"
#include "D3DFont.h"
#include "D3DUtil.h"




//-----------------------------------------------------------------------------
// Globals variables and definitions
//-----------------------------------------------------------------------------
#define WATER_COLOR         0x00004080

struct D3DVERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR3 n;
    FLOAT       tu, tv;

    static const DWORD FVF;
};
const DWORD D3DVERTEX::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;



//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Main class to run this application. Most functionality is inherited
//       from the CD3DApplication base class.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
    // Font for drawing text
    CD3DFont* m_pFont;

    // Transform matrices
    D3DXMATRIXA16              m_matWorld;
    D3DXMATRIXA16              m_matView;
    D3DXMATRIXA16              m_matProj;

    // Dolphin object
    LPDIRECT3DTEXTURE9      m_pDolphinTexture;
    LPDIRECT3DVERTEXBUFFER9 m_pDolphinVB1;
    LPDIRECT3DVERTEXBUFFER9 m_pDolphinVB2;
    LPDIRECT3DVERTEXBUFFER9 m_pDolphinVB3;
    LPDIRECT3DINDEXBUFFER9  m_pDolphinIB;
    DWORD                   m_dwNumDolphinVertices;
    DWORD                   m_dwNumDolphinFaces;
    LPDIRECT3DVERTEXDECLARATION9        m_pDolphinVertexDeclaration;
    LPDIRECT3DVERTEXSHADER9      m_pDolphinVertexShader;
    LPDIRECT3DVERTEXSHADER9      m_pDolphinVertexShader2;

    // Seafloor object
    LPDIRECT3DTEXTURE9      m_pSeaFloorTexture;
    LPDIRECT3DVERTEXBUFFER9 m_pSeaFloorVB;
    LPDIRECT3DINDEXBUFFER9  m_pSeaFloorIB;
    DWORD                   m_dwNumSeaFloorVertices;
    DWORD                   m_dwNumSeaFloorFaces;
    LPDIRECT3DVERTEXDECLARATION9        m_pSeaFloorVertexDeclaration;
    LPDIRECT3DVERTEXSHADER9      m_pSeaFloorVertexShader;
    LPDIRECT3DVERTEXSHADER9      m_pSeaFloorVertexShader2;

    // Water caustics
    LPDIRECT3DTEXTURE9      m_pCausticTextures[32];
    LPDIRECT3DTEXTURE9      m_pCurrentCausticTexture;

public:
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT Render();
    HRESULT FrameMove();
    HRESULT FinalCleanup();
    HRESULT ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior, 
		D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat );

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
// Desc: Constructor
//-----------------------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
{
    // Override base class members
    m_strWindowTitle         = _T("DolphinVS: Tweening Vertex Shader");
    m_d3dEnumeration.AppUsesDepthBuffer        = TRUE;

    m_pFont                  = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );

    // Dolphin object
    m_pDolphinTexture        = NULL;
    m_pDolphinVB1            = NULL;
    m_pDolphinVB2            = NULL;
    m_pDolphinVB3            = NULL;
    m_pDolphinIB             = NULL;
    m_pDolphinVertexDeclaration = NULL;
    m_pDolphinVertexShader   = NULL;
    m_pDolphinVertexShader2  = NULL;

    // SeaFloor object
    m_pSeaFloorTexture       = NULL;
    m_pSeaFloorVB            = NULL;
    m_pSeaFloorIB            = NULL;
    m_pSeaFloorVertexDeclaration = NULL;
    m_pSeaFloorVertexShader  = NULL;
    m_pSeaFloorVertexShader2 = NULL;

    // Water caustics
    for( DWORD t=0; t<32; t++ )
        m_pCausticTextures[t] = NULL;
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    // Animation attributes for the dolphin
    FLOAT fKickFreq    = 2*m_fTime;
    FLOAT fPhase       = m_fTime/3;
    FLOAT fBlendWeight = sinf( fKickFreq );

    // Move the dolphin in a circle
    D3DXMATRIXA16 matDolphin, matTrans, matRotate1, matRotate2;
    D3DXMatrixScaling( &matDolphin, 0.01f, 0.01f, 0.01f );
    D3DXMatrixRotationZ( &matRotate1, -cosf(fKickFreq)/6 );
    D3DXMatrixMultiply( &matDolphin, &matDolphin, &matRotate1 );
    D3DXMatrixRotationY( &matRotate2, fPhase );
    D3DXMatrixMultiply( &matDolphin, &matDolphin, &matRotate2 );
    D3DXMatrixTranslation( &matTrans, -5*sinf(fPhase), sinf(fKickFreq)/2, 10-10*cosf(fPhase) );
    D3DXMatrixMultiply( &matDolphin, &matDolphin, &matTrans );

    // Animate the caustic textures
    DWORD tex = ((DWORD)(m_fTime*32))%32;
    m_pCurrentCausticTexture = m_pCausticTextures[tex];

    // Set the vertex shader constants. Note: outside of the blend matrices,
    // most of these values don't change, so don't need to really be set every
    // frame. It's just done here for clarity
    {
        // Some basic constants
        D3DXVECTOR4 vZero( 0.0f, 0.0f, 0.0f, 0.0f );
        D3DXVECTOR4 vOne( 1.0f, 0.5f, 0.2f, 0.05f );

        FLOAT fWeight1;
        FLOAT fWeight2;
        FLOAT fWeight3;

        if( fBlendWeight > 0.0f )
        {
            fWeight1 = fabsf(fBlendWeight);
            fWeight2 = 1.0f - fabsf(fBlendWeight);
            fWeight3 = 0.0f;
        }
        else
        {
            fWeight1 = 0.0f;
            fWeight2 = 1.0f - fabsf(fBlendWeight);
            fWeight3 = fabsf(fBlendWeight);
        }
        D3DXVECTOR4 vWeight( fWeight1, fWeight2, fWeight3, 0.0f );

        // Lighting vectors (in world space and in dolphin model space)
        // and other constants
        FLOAT fLight[]    = { 0.0f,  1.0f, 0.0f, 0.0f };
        FLOAT fLightDolphinSpace[]    = { 0.0f,  1.0f, 0.0f, 0.0f };
        FLOAT fDiffuse[]  = { 1.00f, 1.00f, 1.00f, 1.00f };
        FLOAT fAmbient[]  = { 0.25f, 0.25f, 0.25f, 0.25f };
        FLOAT fFog[]      = { 0.5f, 50.0f, 1.0f/(50.0f-1.0f), 0.0f };
        FLOAT fCaustics[] = { 0.05f, 0.05f, sinf(m_fTime)/8, cosf(m_fTime)/10 };

        D3DXMATRIXA16 matDolphinInv;
        D3DXMatrixInverse(&matDolphinInv, NULL, &matDolphin);
        D3DXVec4Transform((D3DXVECTOR4*)fLightDolphinSpace, (D3DXVECTOR4*)fLight, &matDolphinInv);
        D3DXVec4Normalize((D3DXVECTOR4*)fLightDolphinSpace, (D3DXVECTOR4*)fLightDolphinSpace);

        // Vertex shader operations use transposed matrices
        D3DXMATRIXA16 mat, matCamera, matTranspose, matCameraTranspose;
        D3DXMATRIXA16 matViewTranspose, matProjTranspose;
        D3DXMatrixMultiply(&matCamera, &matDolphin, &m_matView);
        D3DXMatrixMultiply(&mat, &matCamera, &m_matProj);
        D3DXMatrixTranspose(&matTranspose, &mat);
        D3DXMatrixTranspose(&matCameraTranspose, &matCamera);
        D3DXMatrixTranspose(&matViewTranspose, &m_matView);
        D3DXMatrixTranspose(&matProjTranspose, &m_matProj);

        // Set the vertex shader constants
        m_pd3dDevice->SetVertexShaderConstantF(  0, (float*)&vZero,     1 );
        m_pd3dDevice->SetVertexShaderConstantF(  1, (float*)&vOne,      1 );
        m_pd3dDevice->SetVertexShaderConstantF(  2, (float*)&vWeight,   1 );
        m_pd3dDevice->SetVertexShaderConstantF(  4, (float*)&matTranspose, 4 );
        m_pd3dDevice->SetVertexShaderConstantF(  8, (float*)&matCameraTranspose,  4 );
        m_pd3dDevice->SetVertexShaderConstantF( 12, (float*)&matViewTranspose,  4 );
        m_pd3dDevice->SetVertexShaderConstantF( 19, (float*)&fLightDolphinSpace,   1 );
        m_pd3dDevice->SetVertexShaderConstantF( 20, (float*)&fLight,    1 );
        m_pd3dDevice->SetVertexShaderConstantF( 21, (float*)&fDiffuse,  1 );
        m_pd3dDevice->SetVertexShaderConstantF( 22, (float*)&fAmbient,  1 );
        m_pd3dDevice->SetVertexShaderConstantF( 23, (float*)&fFog,      1 );
        m_pd3dDevice->SetVertexShaderConstantF( 24, (float*)&fCaustics, 1 );
        m_pd3dDevice->SetVertexShaderConstantF( 28, (float*)&matProjTranspose,  4 );
    }

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
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         WATER_COLOR, 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        FLOAT fAmbientLight[]  = { 0.25f, 0.25f, 0.25f, 0.25f };
        m_pd3dDevice->SetVertexShaderConstantF( 22, (float*)&fAmbientLight, 1 );

        // Render the seafloor
        m_pd3dDevice->SetTexture( 0, m_pSeaFloorTexture );
        m_pd3dDevice->SetVertexDeclaration( m_pSeaFloorVertexDeclaration );
        m_pd3dDevice->SetVertexShader( m_pSeaFloorVertexShader );
        m_pd3dDevice->SetStreamSource( 0, m_pSeaFloorVB, 0, sizeof(D3DVERTEX) );
        m_pd3dDevice->SetIndices( m_pSeaFloorIB );
        m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0,
                                            0, m_dwNumSeaFloorVertices,
                                            0, m_dwNumSeaFloorFaces );

        // Render the dolphin
        m_pd3dDevice->SetTexture( 0, m_pDolphinTexture );
        m_pd3dDevice->SetVertexDeclaration( m_pDolphinVertexDeclaration );
        m_pd3dDevice->SetVertexShader( m_pDolphinVertexShader );
        m_pd3dDevice->SetStreamSource( 0, m_pDolphinVB1, 0, sizeof(D3DVERTEX) );
        m_pd3dDevice->SetStreamSource( 1, m_pDolphinVB2, 0, sizeof(D3DVERTEX) );
        m_pd3dDevice->SetStreamSource( 2, m_pDolphinVB3, 0, sizeof(D3DVERTEX) );
        m_pd3dDevice->SetIndices( m_pDolphinIB );
        m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0,
                                            0, m_dwNumDolphinVertices,
                                            0, m_dwNumDolphinFaces );

        // Now, we are going to do a 2nd pass, to alpha-blend in the caustics.
        // The caustics use a 2nd set of texture coords that are generated
        // by the vertex shaders. Lighting from the light above is used, but
        // ambient is turned off to avoid lighting objects from below (for
        // instance, we don't want caustics appearing on the dolphin's
        // underbelly). Finally, fog color is set to black, so that caustics
        // fade in distance.

        // Turn on alpha blending
        m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
        
        m_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ONE );
        m_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

        // Setup the caustic texture
        m_pd3dDevice->SetTexture( 0, m_pCurrentCausticTexture );

        // Set ambient and fog colors to black
        FLOAT fAmbientDark[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        m_pd3dDevice->SetVertexShaderConstantF( 22, (float*)&fAmbientDark, 1 );
        m_pd3dDevice->SetRenderState( D3DRS_FOGCOLOR, 0x00000000 );

        // Render the caustic effects for the seafloor
        m_pd3dDevice->SetVertexDeclaration( m_pSeaFloorVertexDeclaration );
        m_pd3dDevice->SetVertexShader( m_pSeaFloorVertexShader2 );
        m_pd3dDevice->SetStreamSource( 0, m_pSeaFloorVB, 0, sizeof(D3DVERTEX) );
        m_pd3dDevice->SetIndices( m_pSeaFloorIB );
        m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0,
                                            0, m_dwNumSeaFloorVertices,
                                            0, m_dwNumSeaFloorFaces );

        // Finally, render the caustic effects for the dolphin
        m_pd3dDevice->SetVertexDeclaration( m_pDolphinVertexDeclaration );
        m_pd3dDevice->SetVertexShader( m_pDolphinVertexShader2 );
        m_pd3dDevice->SetStreamSource( 0, m_pDolphinVB1, 0, sizeof(D3DVERTEX) );
        m_pd3dDevice->SetStreamSource( 1, m_pDolphinVB2, 0, sizeof(D3DVERTEX) );
        m_pd3dDevice->SetStreamSource( 2, m_pDolphinVB3, 0, sizeof(D3DVERTEX) );
        m_pd3dDevice->SetIndices( m_pDolphinIB );
        m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0,
                                            0, m_dwNumDolphinVertices,
                                            0, m_dwNumDolphinFaces );

        // Restore modified render states
        m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
        m_pd3dDevice->SetRenderState( D3DRS_FOGCOLOR, WATER_COLOR );

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
// Desc: Initialize device-dependent objects. This is the place to create mesh
//       and texture objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;
    TCHAR strPath[MAX_PATH];
    LPD3DXBUFFER pCode = NULL;
    LPDIRECT3DVERTEXBUFFER9 pMeshSourceVB;
    LPDIRECT3DINDEXBUFFER9  pMeshSourceIB;
    D3DVERTEX*              pSrc;
    D3DVERTEX*              pDst;
    CD3DMesh                DolphinMesh01;
    CD3DMesh                DolphinMesh02;
    CD3DMesh                DolphinMesh03;
    CD3DMesh                SeaFloorMesh;

    // Initialize the font's internal textures
    m_pFont->InitDeviceObjects( m_pd3dDevice );

    // Create texture for the dolphin
    if( FAILED( D3DUtil_CreateTexture( m_pd3dDevice, _T("Dolphin.bmp"),
                                       &m_pDolphinTexture ) ) )
    {
        return D3DAPPERR_MEDIANOTFOUND;
    }

    // Create textures for the seafloor
    if( FAILED( D3DUtil_CreateTexture( m_pd3dDevice, _T("SeaFloor.bmp"),
                                       &m_pSeaFloorTexture ) ) )
    {
        return D3DAPPERR_MEDIANOTFOUND;
    }

    // Create textures for the water caustics
    for( DWORD t=0; t<32; t++ )
    {
        TCHAR strName[80];
        sprintf( strName, _T("Caust%02ld.tga"), t );
        if( FAILED( D3DUtil_CreateTexture( m_pd3dDevice, strName,
                                           &m_pCausticTextures[t] ) ) )
        {
            return D3DAPPERR_MEDIANOTFOUND;
        }
    }

    // Load the file-based mesh objects
    if( FAILED( DolphinMesh01.Create( m_pd3dDevice, _T("dolphin1.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;
    if( FAILED( DolphinMesh02.Create( m_pd3dDevice, _T("dolphin2.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;
    if( FAILED( DolphinMesh03.Create( m_pd3dDevice, _T("dolphin3.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;
    if( FAILED( SeaFloorMesh.Create( m_pd3dDevice, _T("SeaFloor.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;

    // Set the FVF type to match the vertex format we want
    DolphinMesh01.SetFVF( m_pd3dDevice, D3DVERTEX::FVF );
    DolphinMesh02.SetFVF( m_pd3dDevice, D3DVERTEX::FVF );
    DolphinMesh03.SetFVF( m_pd3dDevice, D3DVERTEX::FVF );
    SeaFloorMesh.SetFVF(  m_pd3dDevice, D3DVERTEX::FVF );

    // Get the number of vertices and faces for the meshes
    m_dwNumDolphinVertices  = DolphinMesh01.GetSysMemMesh()->GetNumVertices();
    m_dwNumDolphinFaces     = DolphinMesh01.GetSysMemMesh()->GetNumFaces();
    m_dwNumSeaFloorVertices = SeaFloorMesh.GetSysMemMesh()->GetNumVertices();
    m_dwNumSeaFloorFaces    = SeaFloorMesh.GetSysMemMesh()->GetNumFaces();

    // Create the dolphin and seafloor vertex and index buffers
    m_pd3dDevice->CreateVertexBuffer( m_dwNumDolphinVertices * sizeof(D3DVERTEX),
                                      D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED,
                                      &m_pDolphinVB1, NULL );
    m_pd3dDevice->CreateVertexBuffer( m_dwNumDolphinVertices * sizeof(D3DVERTEX),
                                      D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED,
                                      &m_pDolphinVB2, NULL );
    m_pd3dDevice->CreateVertexBuffer( m_dwNumDolphinVertices * sizeof(D3DVERTEX),
                                      D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED,
                                      &m_pDolphinVB3, NULL );
    m_pd3dDevice->CreateVertexBuffer( m_dwNumSeaFloorVertices * sizeof(D3DVERTEX),
                                      D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED,
                                      &m_pSeaFloorVB, NULL );
    m_pd3dDevice->CreateIndexBuffer( m_dwNumDolphinFaces * 3 * sizeof(WORD),
                                      D3DUSAGE_WRITEONLY,
                                      D3DFMT_INDEX16, D3DPOOL_MANAGED,
                                      &m_pDolphinIB, NULL );
    m_pd3dDevice->CreateIndexBuffer( m_dwNumSeaFloorFaces * 3 * sizeof(WORD),
                                      D3DUSAGE_WRITEONLY,
                                      D3DFMT_INDEX16, D3DPOOL_MANAGED,
                                      &m_pSeaFloorIB, NULL );

    // Copy vertices for mesh 01
    DolphinMesh01.GetSysMemMesh()->GetVertexBuffer( &pMeshSourceVB );
    m_pDolphinVB1->Lock( 0, 0, (void**)&pDst, 0 );
    pMeshSourceVB->Lock( 0, 0, (void**)&pSrc, 0 );
    memcpy( pDst, pSrc, m_dwNumDolphinVertices * sizeof(D3DVERTEX) );
    m_pDolphinVB1->Unlock();
    pMeshSourceVB->Unlock();
    pMeshSourceVB->Release();

    // Copy vertices for mesh 2
    DolphinMesh02.GetSysMemMesh()->GetVertexBuffer( &pMeshSourceVB );
    m_pDolphinVB2->Lock( 0, 0, (void**)&pDst, 0 );
    pMeshSourceVB->Lock( 0, 0, (void**)&pSrc, 0 );
    memcpy( pDst, pSrc, m_dwNumDolphinVertices * sizeof(D3DVERTEX) );
    m_pDolphinVB2->Unlock();
    pMeshSourceVB->Unlock();
    pMeshSourceVB->Release();

    // Copy vertices for mesh 3
    DolphinMesh03.GetSysMemMesh()->GetVertexBuffer( &pMeshSourceVB );
    m_pDolphinVB3->Lock( 0, 0, (void**)&pDst, 0 );
    pMeshSourceVB->Lock( 0, 0, (void**)&pSrc, 0 );
    memcpy( pDst, pSrc, m_dwNumDolphinVertices * sizeof(D3DVERTEX) );
    m_pDolphinVB3->Unlock();
    pMeshSourceVB->Unlock();
    pMeshSourceVB->Release();

    // Copy vertices for the seafloor mesh, and add some bumpiness
    SeaFloorMesh.GetSysMemMesh()->GetVertexBuffer( &pMeshSourceVB );
    m_pSeaFloorVB->Lock( 0, 0, (void**)&pDst, 0 );
    pMeshSourceVB->Lock( 0, 0, (void**)&pSrc, 0 );
    memcpy( pDst, pSrc, m_dwNumSeaFloorVertices * sizeof(D3DVERTEX) );
    srand(5);
    for( DWORD i=0; i<m_dwNumSeaFloorVertices; i++ )
    {
        ((D3DVERTEX*)pDst)[i].p.y += (rand()/(FLOAT)RAND_MAX);
        ((D3DVERTEX*)pDst)[i].p.y += (rand()/(FLOAT)RAND_MAX);
        ((D3DVERTEX*)pDst)[i].p.y += (rand()/(FLOAT)RAND_MAX);
        ((D3DVERTEX*)pDst)[i].tu  *= 10;
        ((D3DVERTEX*)pDst)[i].tv  *= 10;
    }
    m_pSeaFloorVB->Unlock();
    pMeshSourceVB->Unlock();
    pMeshSourceVB->Release();

    // Copy indices for the dolphin mesh
    DolphinMesh01.GetSysMemMesh()->GetIndexBuffer( &pMeshSourceIB );
    m_pDolphinIB->Lock( 0, 0, (void**)&pDst, 0 );
    pMeshSourceIB->Lock( 0, 0, (void**)&pSrc, 0 );
    memcpy( pDst, pSrc, 3 * m_dwNumDolphinFaces * sizeof(WORD) );
    m_pDolphinIB->Unlock();
    pMeshSourceIB->Unlock();
    pMeshSourceIB->Release();

    // Copy indices for the seafloor mesh
    SeaFloorMesh.GetSysMemMesh()->GetIndexBuffer( &pMeshSourceIB );
    m_pSeaFloorIB->Lock( 0, 0, (void**)&pDst, 0 );
    pMeshSourceIB->Lock( 0, 0, (void**)&pSrc, 0 );
    memcpy( pDst, pSrc, 3 * m_dwNumSeaFloorFaces * sizeof(WORD) );
    m_pSeaFloorIB->Unlock();
    pMeshSourceIB->Unlock();
    pMeshSourceIB->Release();

    // Create vertex shader for the dolphin
    D3DVERTEXELEMENT9 declDolphin[] =
    {
        // First stream is first mesh
        { 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0}, 
        { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0}, 
        { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0}, 
        // Second stream is second mesh
        { 1,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 1}, 
        { 1, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   1}, 
        { 1, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 1}, 
        // Third stream is third mesh
        { 2,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 2}, 
        { 2, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   2}, 
        { 2, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 2}, 
        D3DDECL_END()
    };
    if( FAILED( hr = m_pd3dDevice->CreateVertexDeclaration( declDolphin, &m_pDolphinVertexDeclaration ) ) )
        return hr;

    if( FAILED( hr = DXUtil_FindMediaFileCb( strPath, sizeof(strPath), TEXT("DolphinTween.vsh") ) ) )
        return hr;
    if( FAILED( hr = D3DXAssembleShaderFromFile( strPath, NULL, NULL, 0, &pCode, NULL ) ) )
        return hr;
    if( FAILED( hr = m_pd3dDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(),
                                                       &m_pDolphinVertexShader ) ) )
    {
        SAFE_RELEASE( pCode );
        return hr;
    }
    SAFE_RELEASE( pCode );

    if( FAILED( hr = DXUtil_FindMediaFileCb( strPath, sizeof(strPath), TEXT("DolphinTween2.vsh") ) ) )
        return hr;
    if( FAILED( hr = D3DXAssembleShaderFromFile( strPath, NULL, NULL, 0, &pCode, NULL ) ) )
        return hr;
    if( FAILED( hr = m_pd3dDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(),
                                                       &m_pDolphinVertexShader2 ) ) )
    {
        SAFE_RELEASE( pCode );
        return hr;
    }
    SAFE_RELEASE( pCode );

        // Create vertex shader for the seafloor
    D3DVERTEXELEMENT9 declSeaFloor[] =
    {
        { 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0}, 
        { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0}, 
        { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0}, 
        D3DDECL_END()
    };
    if( FAILED( hr = m_pd3dDevice->CreateVertexDeclaration( declSeaFloor, &m_pSeaFloorVertexDeclaration ) ) )
        return hr;

    if( FAILED( hr = DXUtil_FindMediaFileCb( strPath, sizeof(strPath), TEXT("SeaFloor.vsh") ) ) )
        return hr;
    if( FAILED( hr = D3DXAssembleShaderFromFile( strPath, NULL, NULL, 0, &pCode, NULL ) ) )
        return hr;
    if( FAILED( hr = m_pd3dDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(),
                                                       &m_pSeaFloorVertexShader ) ) )
    {
        SAFE_RELEASE( pCode );
        return hr;
    }
    SAFE_RELEASE( pCode );

    if( FAILED( hr = DXUtil_FindMediaFileCb( strPath, sizeof(strPath), TEXT("SeaFloor2.vsh") ) ) )
        return hr;
    if( FAILED( hr = D3DXAssembleShaderFromFile( strPath, NULL, NULL, 0, &pCode, NULL ) ) )
        return hr;
    if( FAILED( hr = m_pd3dDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(),
                                                       &m_pSeaFloorVertexShader2 ) ) )
    {
        SAFE_RELEASE( pCode );
        return hr;
    }
    SAFE_RELEASE( pCode );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Restore device-memory objects and state after a device is created or
//       resized.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    m_pFont->RestoreDeviceObjects();

    // Set the transform matrices
    D3DXVECTOR3 vEyePt      = D3DXVECTOR3( 0.0f, 0.0f, -5.0f );
    D3DXVECTOR3 vLookatPt   = D3DXVECTOR3( 0.0f, 0.0f,  0.0f );
    D3DXVECTOR3 vUpVec      = D3DXVECTOR3( 0.0f, 1.0f,  0.0f );
    FLOAT       fAspect = ((FLOAT)m_d3dsdBackBuffer.Width) / m_d3dsdBackBuffer.Height;
    D3DXMatrixIdentity( &m_matWorld );
    D3DXMatrixLookAtLH( &m_matView, &vEyePt, &vLookatPt, &vUpVec );
    D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/3, fAspect, 1.0f, 10000.0f );

    // Set default render states
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,        TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_FOGENABLE,      TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_FOGCOLOR,       WATER_COLOR );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Called when the device-dependent objects are about to be lost.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
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

    // Clean up vertex shaders
    SAFE_RELEASE( m_pDolphinVertexDeclaration );
    SAFE_RELEASE( m_pDolphinVertexShader );
    SAFE_RELEASE( m_pDolphinVertexShader2 );
    SAFE_RELEASE( m_pSeaFloorVertexDeclaration );
    SAFE_RELEASE( m_pSeaFloorVertexShader );
    SAFE_RELEASE( m_pSeaFloorVertexShader2 );

    // Clean up dolphin objects
    SAFE_RELEASE( m_pDolphinTexture );
    SAFE_RELEASE( m_pDolphinVB1 );
    SAFE_RELEASE( m_pDolphinVB2 );
    SAFE_RELEASE( m_pDolphinVB3 );
    SAFE_RELEASE( m_pDolphinIB );

    // Clean up seafoor objects
    SAFE_RELEASE( m_pSeaFloorTexture );
    SAFE_RELEASE( m_pSeaFloorVB );
    SAFE_RELEASE( m_pSeaFloorIB );

    // Clean up textures for water caustics
    for( DWORD i=0; i<32; i++ )
        SAFE_RELEASE( m_pCausticTextures[i] );

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
    if( ( dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING ) ||
        ( dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING ) )
    {
        if( pCaps->VertexShaderVersion < D3DVS_VERSION(1,0) )
            return E_FAIL;
    }

    // Need to support post-pixel processing (for fog)
    if( FAILED( m_pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
        adapterFormat, D3DUSAGE_RENDERTARGET | D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
        D3DRTYPE_SURFACE, backBufferFormat ) ) )
    {
        return E_FAIL;
    }

    return S_OK;
}




