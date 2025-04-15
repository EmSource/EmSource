//-----------------------------------------------------------------------------
// File: VertexBlend.cpp
//
// Desc: Example code showing how to do a skinning effect, using the vertex
//       blending feature of Direct3D. Normally, Direct3D transforms each
//       vertex through the world matrix. The vertex blending feature,
//       however, uses mulitple world matrices and a per-vertex blend factor
//       to transform each vertex.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <Windows.h>
#include <commctrl.h>
#include <math.h>
#include <stdio.h>
#include <D3DX9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFile.h"
#include "D3DFont.h"
#include "D3DUtil.h"
#include "resource.h"




//-----------------------------------------------------------------------------
// Name: struct BLENDVERTEX
// Desc: Custom vertex which includes a blending factor
//-----------------------------------------------------------------------------
struct BLENDVERTEX
{
    D3DXVECTOR3 v;       // Referenced as v0 in the vertex shader
    FLOAT       blend;   // Referenced as v1.x in the vertex shader
    D3DXVECTOR3 n;       // Referenced as v3 in the vertex shader
    FLOAT       tu, tv;  // Referenced as v7 in the vertex shader

    static const DWORD FVF;
};
const DWORD BLENDVERTEX::FVF = D3DFVF_XYZB1 | D3DFVF_NORMAL | D3DFVF_TEX1;



//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
    CD3DFont*    m_pFont;
    CD3DMesh*    m_pObject;           // Object to use for vertex blending
    DWORD        m_dwNumVertices;
    DWORD        m_dwNumFaces;
    LPDIRECT3DVERTEXBUFFER9 m_pVB;    
    LPDIRECT3DINDEXBUFFER9  m_pIB;

    D3DXMATRIXA16   m_matUpperArm;       // Vertex blending matrices
    D3DXMATRIXA16   m_matLowerArm;

    LPDIRECT3DVERTEXSHADER9 m_pVertexShader;    // Vertex shader
    BOOL         m_bUseVertexShader;

protected:
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT Render();
    HRESULT FrameMove();
    HRESULT FinalCleanup();
    HRESULT ConfirmDevice( D3DCAPS9*, DWORD, D3DFORMAT, D3DFORMAT );
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

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
    m_strWindowTitle    = _T("VertexBlend: Surface Skinning Example");
    m_d3dEnumeration.AppUsesDepthBuffer   = TRUE;

    m_pFont             = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pObject           = new CD3DMesh();
    m_pVB               = NULL;
    m_pIB               = NULL;
    m_pVertexShader     = NULL;
    m_bUseVertexShader  = FALSE;
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
    // Set the vertex blending matrices for this frame
    D3DXVECTOR3 vAxis( 2+sinf(m_fTime*3.1f), 2+sinf(m_fTime*3.3f), sinf(m_fTime*3.5f) ); 
    D3DXMatrixRotationAxis( &m_matLowerArm, &vAxis, sinf(3*m_fTime) );
    D3DXMatrixIdentity( &m_matUpperArm );

    // Set the vertex shader constants. Note: outside of the blend matrices,
    // most of these values don't change, so don't need to really be set every
    // frame. It's just done here for clarity
    if( m_bUseVertexShader )
    {
        // Some basic constants
        D3DXVECTOR4 vZero(0,0,0,0);
        D3DXVECTOR4 vOne(1,1,1,1);

        // Lighting vector (normalized) and material colors. (Use red light
        // to show difference from non-vertex shader case.)
        D3DXVECTOR4 vLight( 0.5f, 1.0f, -1.0f, 0.0f );
        D3DXVec4Normalize( &vLight, &vLight );
        FLOAT       fDiffuse[] = { 1.00f, 1.00f, 0.00f, 0.00f };
        FLOAT       fAmbient[] = { 0.25f, 0.25f, 0.25f, 0.25f };

        // Vertex shader operations use transposed matrices
        D3DXMATRIXA16 matWorld0Transpose, matWorld1Transpose;
        D3DXMATRIXA16 matView, matProj, matViewProj, matViewProjTranspose;
        m_pd3dDevice->GetTransform( D3DTS_VIEW,       &matView );
        m_pd3dDevice->GetTransform( D3DTS_PROJECTION, &matProj );
        D3DXMatrixMultiply( &matViewProj, &matView, &matProj );
        D3DXMatrixTranspose( &matWorld0Transpose, &m_matUpperArm );
        D3DXMatrixTranspose( &matWorld1Transpose, &m_matLowerArm );
        D3DXMatrixTranspose( &matViewProjTranspose, &matViewProj );

        // Set the vertex shader constants
        m_pd3dDevice->SetVertexShaderConstantF(  0, (float*)&vZero,    1 );
        m_pd3dDevice->SetVertexShaderConstantF(  1, (float*)&vOne,     1 );
        m_pd3dDevice->SetVertexShaderConstantF(  4, (float*)&matWorld0Transpose,   4 );
        m_pd3dDevice->SetVertexShaderConstantF(  8, (float*)&matWorld1Transpose,   4 );
        m_pd3dDevice->SetVertexShaderConstantF( 12, (float*)&matViewProjTranspose, 4 );
        m_pd3dDevice->SetVertexShaderConstantF( 20, (float*)&vLight,   1 );
        m_pd3dDevice->SetVertexShaderConstantF( 21, (float*)&fDiffuse, 1 );
        m_pd3dDevice->SetVertexShaderConstantF( 22, (float*)&fAmbient, 1 );
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
    // Clear the backbuffer
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
                         0x000000ff, 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        if( m_bUseVertexShader )        
        {
            m_pd3dDevice->SetFVF( BLENDVERTEX::FVF );
            m_pd3dDevice->SetVertexShader( m_pVertexShader );
            m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(BLENDVERTEX) );
            m_pd3dDevice->SetIndices( m_pIB );
            m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_dwNumVertices,
                                                0, m_dwNumFaces );
        }
        else
        {
            // Enable vertex blending using API
            m_pd3dDevice->SetVertexShader( NULL );
            m_pd3dDevice->SetTransform( D3DTS_WORLD,  &m_matUpperArm );
            m_pd3dDevice->SetTransform( D3DTS_WORLD1, &m_matLowerArm );
            m_pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, D3DVBF_1WEIGHTS );

            // Display the object
            m_pObject->Render( m_pd3dDevice );
        }

        // Output statistics
        m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );

        if( m_bUseVertexShader )
            m_pFont->DrawText( 2, 40, D3DCOLOR_ARGB(255,255,255,255), _T("Using vertex shader") );
        else
            m_pFont->DrawText( 2, 40, D3DCOLOR_ARGB(255,255,255,255), _T("Using D3DRS_VERTEXBLEND") );

        // End the scene.
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;

    // Initialize the font's internal textures
    m_pFont->InitDeviceObjects( m_pd3dDevice );

    // Load an object to render
    if( FAILED( m_pObject->Create( m_pd3dDevice, _T("mslogo.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;

    if( ( ( m_dwCreateFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING ) ||
          ( m_dwCreateFlags & D3DCREATE_MIXED_VERTEXPROCESSING ) ) &&
        m_d3dCaps.VertexShaderVersion < D3DVS_VERSION(1,0) )
    {
        // No VS available, so don't try to use it or allow user to
        // switch to it
        m_bUseVertexShader = FALSE;
        EnableMenuItem( GetMenu( m_hWnd ), IDM_USEVERTEXSHADER, MF_GRAYED );
    }
    else if( m_d3dCaps.MaxVertexBlendMatrices < 2 )
    {
        // No blend matrices available, so don't try to use them or 
        // allow user to switch to them
        m_bUseVertexShader = TRUE;
        EnableMenuItem( GetMenu( m_hWnd ), IDM_USEVERTEXSHADER, MF_GRAYED );
    }
    else
    {
        // Both techniques available, so default to blend matrices and 
        // allow the user to switch techniques
        m_bUseVertexShader = FALSE;
        EnableMenuItem( GetMenu( m_hWnd ), IDM_USEVERTEXSHADER, MF_ENABLED );
    }

    // Set a custom FVF for the mesh
    m_pObject->SetFVF( m_pd3dDevice, BLENDVERTEX::FVF );

    // Add blending weights to the mesh
    {
        // Gain acces to the mesh's vertices
        LPDIRECT3DVERTEXBUFFER9 pVB;
        BLENDVERTEX* pVertices;
        DWORD        dwNumVertices = m_pObject->GetSysMemMesh()->GetNumVertices();
        m_pObject->GetSysMemMesh()->GetVertexBuffer( &pVB );
        pVB->Lock( 0, 0, (void**)&pVertices, 0 );

        // Calculate the min/max z values for all the vertices
        FLOAT fMinX =  1e10f;
        FLOAT fMaxX = -1e10f;

        for( DWORD i=0; i<dwNumVertices; i++ )
        {
            if( pVertices[i].v.x < fMinX ) 
                fMinX = pVertices[i].v.x;
            if( pVertices[i].v.x > fMaxX ) 
                fMaxX = pVertices[i].v.x;
        }

        for( i=0; i<dwNumVertices; i++ )
        {
            // Set the blend factors for the vertices
            FLOAT a = ( pVertices[i].v.x - fMinX ) / ( fMaxX - fMinX );
            pVertices[i].blend = 1.0f-sinf(a*D3DX_PI*1.0f);
        }

        // Done with the mesh's vertex buffer data
        pVB->Unlock();
        pVB->Release();
    }

    if( ( m_dwCreateFlags & D3DCREATE_SOFTWARE_VERTEXPROCESSING ) ||
        m_d3dCaps.VertexShaderVersion >= D3DVS_VERSION(1,0) )
    {
        TCHAR        strVertexShaderPath[512];
        LPD3DXBUFFER pCode;

        // Find the vertex shader file
        if( FAILED( hr = DXUtil_FindMediaFileCb( strVertexShaderPath, 
            sizeof(strVertexShaderPath), _T("Blend.vsh") ) ) )
        { 
            return hr;
        }

        // Assemble the vertex shader from the file
        if( FAILED( hr = D3DXAssembleShaderFromFile( strVertexShaderPath, 
                                                     NULL, NULL, 0, &pCode, NULL ) ) )
        {
            return hr;
        }

        // Create the vertex shader
        hr = m_pd3dDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(),
                                               &m_pVertexShader );
        pCode->Release();
        if( FAILED( hr ) )
            return hr;
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
    m_pFont->RestoreDeviceObjects();

    // Restore mesh's local memory objects
    m_pObject->RestoreDeviceObjects( m_pd3dDevice );

    // Get access to the mesh vertex and index buffers
    m_pObject->GetLocalMesh()->GetVertexBuffer( &m_pVB );
    m_pObject->GetLocalMesh()->GetIndexBuffer( &m_pIB );
    m_dwNumVertices = m_pObject->GetLocalMesh()->GetNumVertices();
    m_dwNumFaces    = m_pObject->GetLocalMesh()->GetNumFaces();

    // Set miscellaneous render states
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00404040 );

    // Set the projection matrix
    D3DXMATRIXA16 matProj;
    FLOAT fAspect = m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, fAspect, 1.0f, 10000.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    // Set the app view matrix for normal viewing
    D3DXVECTOR3 vEyePt    = D3DXVECTOR3( 0.0f,-5.0f,-10.0f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f,  0.0f );
    D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f,  0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // Create a directional light. (Use yellow light to distinguish from
    // vertex shader case.)
    D3DLIGHT9 light;
    D3DUtil_InitLight( light, D3DLIGHT_DIRECTIONAL, -0.5f, -1.0f, 1.0f );
    light.Diffuse.r = 1.0f;
    light.Diffuse.g = 1.0f;
    light.Diffuse.b = 0.0f;
    m_pd3dDevice->SetLight( 0, &light );
    m_pd3dDevice->LightEnable( 0, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Called when the device-dependent objects are about to be lost.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();
    m_pObject->InvalidateDeviceObjects();

    SAFE_RELEASE( m_pVB );
    SAFE_RELEASE( m_pIB );

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
    m_pObject->Destroy();

    SAFE_RELEASE( m_pVertexShader );

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
    SAFE_DELETE( m_pObject );

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

    // Check that the device supports at least one of the two techniques
    // used in this sample: either a vertex shader, or at least two blend
    // matrices and a directional light.

    if( (dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING ) ||
        (dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING ) )
    {
        if( pCaps->VertexShaderVersion >= D3DVS_VERSION(1,0) )
            return S_OK;
    }
    else
    {
        // Software vertex processing always supports vertex shaders
        return S_OK;
    }

    // Check that the device can blend vertices with at least two matrices
    // (Software can always do up to 4 blend matrices)
    if( pCaps->MaxVertexBlendMatrices < 2 )
        return E_FAIL;

    // If this is a TnL device, make sure it supports directional lights
    if( (dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING ) ||
        (dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING ) )
    {
        if( !(pCaps->VertexProcessingCaps & D3DVTXPCAPS_DIRECTIONALLIGHTS ) )
            return E_FAIL;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Message proc function to handle key and menu input
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam )
{
    // Handle menu commands
    if( WM_COMMAND == uMsg )
    {
        switch( LOWORD(wParam) )
        {
            case IDM_USEVERTEXSHADER:
                m_bUseVertexShader = !m_bUseVertexShader;
                CheckMenuItem( GetMenu(hWnd), IDM_USEVERTEXSHADER,
                               m_bUseVertexShader ? MF_CHECKED : MF_UNCHECKED );
                break;
        }
    }

    // Pass remaining messages to default handler
    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}



