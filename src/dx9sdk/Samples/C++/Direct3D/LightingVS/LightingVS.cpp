//-----------------------------------------------------------------------------
// File: LightingVS.cpp
//
// Desc: Example code showing how to use D3D fixed-function lights and vertex 
//       shader lights.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <Windows.h>
#include <commctrl.h>
#include <basetsd.h>
#include <math.h>
#include <stdio.h>
#include <D3DX9.h>
#include <tchar.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFont.h"
#include "D3DUtil.h"
#include "resource.h"




//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------

// Custom D3D vertex format used by the vertex buffer
struct MYVERTEX
{
    D3DXVECTOR3 p;       // vertex position
    D3DXVECTOR3 n;       // vertex normal

    static const DWORD FVF;
};
const DWORD MYVERTEX::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

const DWORD MAXLIGHTS = 7;

// Number of vectors per light in vertex shader constants
static const int NUM_VECTORS_PER_LIGHT = 7;

//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
    LPD3DXMESH m_pWallMesh;            // Tessellated plane to serve as the walls and floor
    LPD3DXMESH m_pSphereMesh;          // Representation of a point light
    LPD3DXMESH m_pConeMesh;            // Representation of a dir/spot light
    CD3DFont* m_pFont;                 // Font for drawing text
    CD3DFont* m_pFontSmall;            // Font for drawing text
    D3DLIGHT9 m_light[MAXLIGHTS];      // Description of the D3D lights
    UINT m_n;                          // Number of vertices in the wall mesh along X
    UINT m_m;                          // Number of vertices in the wall mesh along Z
    UINT m_nTriangles;                 // Number of triangles in the wall mesh
    BOOL m_bShowHelp;
    BOOL m_bWireframe;

protected:
    HRESULT BuildWallMesh();

    HRESULT InitDeviceObjects();
    void SetMatrices(const D3DXMATRIX* pMatWorld, const D3DXMATRIX* pMatViewProj);
    void SetLight(DWORD LightIndex, D3DLIGHT9* light);
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT FrameMove();
    HRESULT Render();
    HRESULT FinalCleanup();
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    HRESULT ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior, 
		D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat );

    DWORD               m_dwNumLights;          // Number of moving lights
    LPD3DXEFFECT        m_pEffect;              // Effect containing vertex shaders
    UINT                m_iCurTechnique;        // Curent technique index
    LPCSTR              m_pCurTechniqueName;    // Name of current technique
    BOOL                m_bUseVertexShaders;    // Whether to use shaders or FF
    BOOL                m_bTechniqueValid;      // Whether current technique is supported
    D3DXMATRIXA16       m_matProj;              // Current projection matrix
    D3DXMATRIXA16       m_matView;              // Current view matrix
    D3DLIGHT9           m_light0;               // Light used to add ambient lighting to the walls
    D3DLIGHT9           m_light1;               // Light which affects light objects
    D3DLIGHTTYPE        m_CurrentLightType;     // Current type of moving lights (0 to cycle though light types)

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
    m_strWindowTitle            = TEXT( "Lighting" );
    m_d3dEnumeration.AppUsesDepthBuffer           = FALSE;

    m_pFont                     = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pFontSmall                = new CD3DFont( _T("Arial"), 9, D3DFONT_BOLD );
    m_pWallMesh                 = NULL;
    m_pSphereMesh               = NULL;
    m_pConeMesh                 = NULL;
    m_pEffect                   = NULL;
    m_iCurTechnique             = 0;
    m_pCurTechniqueName         = NULL;

    // Set up wall/floor mesh resolution.  Try changing m_n and m_m to see
    // how the lighting is affected.
    m_n = 32;
    m_m = 32;
    m_nTriangles = (m_n-1)*(m_m-1)*2;
    m_bShowHelp = FALSE;
    m_bWireframe = FALSE;
    m_dwNumLights = 2;
    m_bUseVertexShaders = TRUE;
    m_CurrentLightType = (D3DLIGHTTYPE)0;   // Cycle through light types
}




//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
                                          D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat )
{
    // The sample needs at least vertex shader 2_0. Software vertex processing 
    // supports vs_3_0, so it is allowed.
    if( pCaps->VertexShaderVersion >= D3DVS_VERSION(2,0) ||
        dwBehavior & D3DCREATE_SOFTWARE_VERTEXPROCESSING )
    {
        return S_OK;
    }

    return E_FAIL;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;
    TCHAR strPath[MAX_PATH];

    if( FAILED( hr = m_pFont->InitDeviceObjects( m_pd3dDevice ) ) )
        return hr;

    if( FAILED( hr = m_pFontSmall->InitDeviceObjects( m_pd3dDevice ) ) )
        return hr;

    // Load effect file containing the vertex shaders
    if( FAILED( hr = DXUtil_FindMediaFileCch( strPath, MAX_PATH, 
                                            TEXT("LightingVS.fx") ) ) )
    {
        return hr;
    }

    if( FAILED( hr = D3DXCreateEffectFromFile( m_pd3dDevice, strPath, NULL, NULL, 
                                            0, NULL, &m_pEffect, NULL ) ) )
    {
        return hr;
    }

    D3DXTECHNIQUE_DESC TechDesc;
    D3DXHANDLE hTech = m_pEffect->GetTechnique( m_iCurTechnique );
    m_pEffect->GetTechniqueDesc( hTech, &TechDesc );
    m_pCurTechniqueName = TechDesc.Name;

    m_pEffect->SetTechnique( hTech );
    m_bTechniqueValid = SUCCEEDED( m_pEffect->ValidateTechnique( hTech ) );

    ZeroMemory( &m_light0, sizeof(m_light0) );
    m_light0.Type = D3DLIGHT_DIRECTIONAL;
    m_light0.Direction = D3DXVECTOR3( 0.3f, -0.5f, 0.2f );
    m_light0.Diffuse.r = m_light0.Diffuse.g = m_light0.Diffuse.b = 0.25f;

    ZeroMemory( &m_light1, sizeof(m_light1) );
    m_light1.Type = D3DLIGHT_DIRECTIONAL;
    m_light1.Direction = D3DXVECTOR3( 0.5f, -0.5f, 0.5f );
    m_light1.Diffuse.r = m_light1.Diffuse.g = m_light1.Diffuse.b = 1.0f;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Restores scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    HRESULT hr;

    if( FAILED( hr = BuildWallMesh() ) )
        return hr;

    // Create sphere and cone meshes to represent the lights
    if (FAILED( D3DXCreateSphere(m_pd3dDevice, 0.25f, 20, 20, &m_pSphereMesh, NULL) ) )
        return E_FAIL;

    if (FAILED( D3DXCreateCylinder(m_pd3dDevice, 0.0f, 0.25f, 0.5f, 20, 20, &m_pConeMesh, NULL) ) )
        return E_FAIL;

    // Set up a material
    D3DMATERIAL9 mtrl;
    D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f );
    m_pd3dDevice->SetMaterial( &mtrl );

    // Set miscellaneous render states
    m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE,   FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );

    // Set the world matrix
    D3DXMATRIXA16 matIdentity;
    D3DXMatrixIdentity( &matIdentity );
    m_pd3dDevice->SetTransform( D3DTS_WORLD,  &matIdentity );

    // Set the view matrix.
    D3DXVECTOR3 vFromPt( -10, 10, -10);
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &m_matView, &vFromPt, &vLookatPt, &vUpVec );
    m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_matView );

    // Set the projection matrix
    FLOAT fAspect = ((FLOAT)m_d3dsdBackBuffer.Width) / m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4, fAspect, 1.0f, 100.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );

    // Turn on lighting.
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

    // Enable ambient lighting to a dim, grey light, so objects that
    // are not lit by the other lights are not completely black
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 
        D3DCOLOR_COLORVALUE( 0.25, 0.25, 0.25, 1.0 ) );

    // Set light #0 to be a simple, faint grey directional light so 
    // the walls and floor are slightly different shades of grey
    m_pd3dDevice->SetLight( 0, &m_light0 );

    // Set light #1 to be a simple, bright directional light to use 
    // on the mesh representing light #2
    m_pd3dDevice->SetLight( 1, &m_light1 );

    // Light #2 will be the light used to light the floor and walls.  It will
    // be set up in FrameMove() since it changes every frame.

    // Restore the font
    m_pFont->RestoreDeviceObjects();
    m_pFontSmall->RestoreDeviceObjects();

    if( m_pEffect != NULL )
        m_pEffect->OnLostDevice();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: BuildWallMesh()
// Desc: Builds the wall mesh based on m_m and m_n.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::BuildWallMesh()
{
    HRESULT hr = S_OK;
    MYVERTEX* v = NULL;
    LPD3DXMESH pWallMeshTemp = NULL;
    DWORD* pdwAdjacency = NULL;

    SAFE_RELEASE( m_pWallMesh );

    // Create a square grid m_n*m_m for rendering the wall
    if( FAILED( hr = D3DXCreateMeshFVF( m_nTriangles, m_nTriangles * 3, 
        D3DXMESH_SYSTEMMEM, MYVERTEX::FVF, m_pd3dDevice, &pWallMeshTemp ) ) )
    {
        goto End;
    }

    // Fill in the grid vertex data
    float dX;
    float dZ;
    UINT k;
    UINT z;
    if( FAILED( hr = pWallMeshTemp->LockVertexBuffer(0, (LPVOID*)&v) ) )
        goto End;
    dX = 1.0f/(m_n-1);
    dZ = 1.0f/(m_m-1);
    k = 0;
    for (z=0; z < (m_m-1); z++)
    {
        for (UINT x=0; x < (m_n-1); x++)
        {
            v[k].p  = D3DXVECTOR3(10 * x*dX, 0.0f, 10 * z*dZ );
            v[k].n  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
            k++;
            v[k].p  = D3DXVECTOR3(10 * x*dX, 0.0f, 10 * (z+1)*dZ );
            v[k].n  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
            k++;
            v[k].p  = D3DXVECTOR3(10 * (x+1)*dX, 0.0f, 10 * (z+1)*dZ );
            v[k].n  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
            k++;
            v[k].p  = D3DXVECTOR3(10 * x*dX, 0.0f, 10 * z*dZ );
            v[k].n  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
            k++;
            v[k].p  = D3DXVECTOR3(10 * (x+1)*dX, 0.0f, 10 * (z+1)*dZ );
            v[k].n  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
            k++;
            v[k].p  = D3DXVECTOR3(10 * (x+1)*dX, 0.0f, 10 * z*dZ );
            v[k].n  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
            k++;
        }
    }
    pWallMeshTemp->UnlockVertexBuffer();

    // Fill in index data
    WORD* pIndex;
    if( FAILED( hr = pWallMeshTemp->LockIndexBuffer(0, (LPVOID*)&pIndex) ) )
        goto End;
    WORD iIndex;
    for( iIndex = 0; iIndex < m_nTriangles * 3; iIndex++ )
    {
        *(pIndex++) = iIndex;
    }
    pWallMeshTemp->UnlockIndexBuffer();

    // Eliminate redundant vertices
    pdwAdjacency = new DWORD[3 * m_nTriangles];
    if( pdwAdjacency == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto End;
    }

    if( FAILED( hr = D3DXWeldVertices( pWallMeshTemp, D3DXWELDEPSILONS_WELDALL, NULL, NULL, pdwAdjacency, NULL, NULL ) ) )
    {
        goto End;
    }

    // Optimize the mesh
    if( FAILED( hr = pWallMeshTemp->OptimizeInplace( D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
        pdwAdjacency, NULL, NULL, NULL ) ) )
    {
        goto End;
    }
    // Copy the mesh into fast write-only memory
    if( FAILED( hr = pWallMeshTemp->CloneMeshFVF( D3DXMESH_WRITEONLY, MYVERTEX::FVF, m_pd3dDevice, &m_pWallMesh ) ) )
    {
        goto End;
    }

End:
    SAFE_RELEASE( pWallMeshTemp );
    SAFE_DELETE_ARRAY( pdwAdjacency );
    return hr;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    ZeroMemory( &m_light, sizeof(m_light) );

    D3DLIGHTTYPE lightType;
    if( m_CurrentLightType == 0 )
        // Rotate through the various light types
        lightType = (D3DLIGHTTYPE)(1+(((DWORD)m_fTime)/5)%3);
    else
        lightType = m_CurrentLightType;

    // Make sure the light type is supported by the device.  If 
    // D3DVTXPCAPS_POSITIONALLIGHTS is not set, the device does not support 
    // point or spot lights, so change light #2's type to a directional light.
    DWORD dwCaps = m_d3dCaps.VertexProcessingCaps;
    if( 0 == ( dwCaps & D3DVTXPCAPS_POSITIONALLIGHTS ) &&
        !(m_bUseVertexShaders) )
    {
        if( lightType == D3DLIGHT_POINT || lightType == D3DLIGHT_SPOT )
            lightType = D3DLIGHT_DIRECTIONAL;
    }

    for (DWORD i = 0; i < m_dwNumLights; i++)
    {
        m_light[i].Type = lightType;

        // Values for the light position, direction, and color
        FLOAT x = sinf( m_fTime*2.000f*(i+1.5f) );
        FLOAT y = sinf( m_fTime*2.246f*(i+1.5f) );
        FLOAT z = sinf( m_fTime*2.640f*(i+1.5f) );

        m_light[i].Diffuse.r  = 0.5f + 0.5f * x;
        m_light[i].Diffuse.g  = 0.5f + 0.5f * y;
        m_light[i].Diffuse.b  = 0.5f + 0.5f * z;
        m_light[i].Range      = 100.0f;
        
        switch( lightType )
        {
            case D3DLIGHT_POINT:
                m_light[i].Position     = 4.5f * D3DXVECTOR3( x, y, z );
                m_light[i].Attenuation1 = 0.4f;
                break;
            case D3DLIGHT_DIRECTIONAL:
                m_light[i].Direction    = D3DXVECTOR3( x, y, z );
                break;
            case D3DLIGHT_SPOT:
                m_light[i].Position     = 2.0f * D3DXVECTOR3( x, y, z );
                m_light[i].Direction    = D3DXVECTOR3( x, y, z );
                m_light[i].Theta        = 0.5f;
                m_light[i].Phi          = 1.0f;
                m_light[i].Falloff      = 1.0f;
                m_light[i].Attenuation0 = 1.0f;
        }
        m_pd3dDevice->SetLight( 2+i, &m_light[i] );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SetMatrices()
// Desc: Called once a world or view matrix is changed to update vertex shader
//       constants
//-----------------------------------------------------------------------------
void CMyD3DApplication::SetMatrices(const D3DXMATRIX* pMatWorld, const D3DXMATRIX* pMatViewProj)
{
    D3DXMATRIX m;
    D3DXMatrixMultiplyTranspose(&m, pMatWorld, pMatViewProj);
    m_pd3dDevice->SetVertexShaderConstantF(100, (float*)&m, 4);
    D3DXMatrixMultiplyTranspose(&m, pMatWorld, &m_matView);
    m_pd3dDevice->SetVertexShaderConstantF(104, (float*)&m, 4);
    D3DXMatrixMultiply(&m, pMatWorld, &m_matView);
    D3DXMatrixInverse(&m, NULL, &m);
    m_pd3dDevice->SetVertexShaderConstantF(108, (float*)&m, 4);
}




//-----------------------------------------------------------------------------
// Name: SetLight()
// Desc: Called to set light parameters as vertex shader constants
//       constants
//-----------------------------------------------------------------------------
void CMyD3DApplication::SetLight(DWORD LightIndex, D3DLIGHT9* light)
{
    m_pd3dDevice->SetVertexShaderConstantF(LightIndex*NUM_VECTORS_PER_LIGHT + 5, (float*)&light->Ambient,  1);
    m_pd3dDevice->SetVertexShaderConstantF(LightIndex*NUM_VECTORS_PER_LIGHT + 6, (float*)&light->Diffuse,  1);
    m_pd3dDevice->SetVertexShaderConstantF(LightIndex*NUM_VECTORS_PER_LIGHT + 7, (float*)&light->Specular, 1);
    // Transform light direction and position to the camera space
    D3DXVECTOR4 direction;
    D3DXVec3TransformNormal((D3DXVECTOR3*)&direction, (D3DXVECTOR3*)&light->Direction, &m_matView);
    D3DXVec3Normalize((D3DXVECTOR3*)&direction, (D3DXVECTOR3*)&direction);
    m_pd3dDevice->SetVertexShaderConstantF(LightIndex*NUM_VECTORS_PER_LIGHT + 8, (float*)&direction, 1);
    D3DXVECTOR4 position;
    D3DXVec3TransformCoord((D3DXVECTOR3*)&position, (D3DXVECTOR3*)&light->Position, &m_matView);
    m_pd3dDevice->SetVertexShaderConstantF(LightIndex * NUM_VECTORS_PER_LIGHT + 9, (float*)&position, 1);
    float tmp[] = 
    {
        light->Attenuation0, light->Attenuation1, light->Attenuation2, (float)light->Type,
        light->Falloff, 
        -cosf(light->Phi/2.0f), 
        1.0f/(cosf(light->Theta/2.0f) - cosf(light->Phi/2.0f)), 
        0
    };
    m_pd3dDevice->SetVertexShaderConstantF(LightIndex*NUM_VECTORS_PER_LIGHT + 10, tmp, sizeof(tmp) / (sizeof(float)*4));
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
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET, 0x000000ff, 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        // Only render the walls and lights if using the FF pipeline or
        // a valid effect technique
        if( m_bTechniqueValid || !m_bUseVertexShaders )
        {
            D3DXMATRIXA16 matWorld;
            D3DXMATRIXA16 matTrans;
            D3DXMATRIXA16 matRotate;

            if( m_bWireframe )
                m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
            else
                m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

            UINT numPasses;
            D3DXMATRIX matViewProj;
            if( m_bUseVertexShaders )
            {
                DWORD i;

                // Set vertex shader
                m_pEffect->Begin( &numPasses, 0 );

                // Precompute m_view * m_projection
                D3DXMatrixMultiply(&matViewProj, &m_matView, &m_matProj);

                // Set up material as vertex shader constants
                D3DMATERIAL9 mtrl;
                D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f );
                m_pd3dDevice->SetVertexShaderConstantF(0, (float*)&mtrl.Ambient, 1);
                m_pd3dDevice->SetVertexShaderConstantF(1, (float*)&mtrl.Emissive, 1);
                m_pd3dDevice->SetVertexShaderConstantF(2, (float*)&mtrl.Diffuse, 1);
                m_pd3dDevice->SetVertexShaderConstantF(3, (float*)&mtrl.Specular, 1);
                float tmp[4] = {mtrl.Power, 0,0,0};
                m_pd3dDevice->SetVertexShaderConstantF(4, tmp, 1);

                SetLight( 0, &m_light0 );

                DWORD dwNumDirectionalLights = 1;   // m_light0 is directional
                DWORD dwNumSpotLights = 0;
                DWORD dwNumPointLights = 0;
                // Go through the lights and find number of each light type
                for (i=0; i < m_dwNumLights; i++)
                {
                    switch (m_light[i].Type)
                    {
                    case D3DLIGHT_DIRECTIONAL:
                        dwNumDirectionalLights++;
                        break;
                    case D3DLIGHT_SPOT:
                        dwNumSpotLights++;
                        break;
                    case D3DLIGHT_POINT:
                        dwNumPointLights++;
                        break;
                    }
                }

                DWORD dwCurrentDirectionalLightIndex = 1;
                DWORD dwCurrentSpotLightIndex = 0;
                DWORD dwCurrentPointLightIndex = 0;
                // Set light params as vertex shader constants
                for (i=0; i < m_dwNumLights; i++)
                {
                    switch (m_light[i].Type)
                    {
                    case D3DLIGHT_DIRECTIONAL:
                        SetLight(dwCurrentDirectionalLightIndex, &m_light[i]);
                        dwCurrentDirectionalLightIndex++;
                        break;
                    case D3DLIGHT_SPOT:
                        SetLight(dwNumDirectionalLights + dwCurrentSpotLightIndex, &m_light[i]);
                        dwCurrentSpotLightIndex++;
                        break;
                    case D3DLIGHT_POINT:
                        SetLight(dwNumDirectionalLights + dwNumSpotLights + dwCurrentPointLightIndex, &m_light[i]);
                        dwCurrentPointLightIndex++;
                        break;
                    }
                }

                // Set various constants
                float c0[] = {
                    0,1,2,3,                            // Useful constants
                    0.25f, 0.25f, 0.25f, 1              // Global ambient factor
                };
                m_pd3dDevice->SetVertexShaderConstantF(112, c0, sizeof(c0) / (sizeof(float)*4));

                // Loop parameters for each light type
                int i0[] = {
                    dwNumDirectionalLights , 0, NUM_VECTORS_PER_LIGHT, 0,
                    dwNumSpotLights,  dwNumDirectionalLights * NUM_VECTORS_PER_LIGHT, NUM_VECTORS_PER_LIGHT, 0,
                    dwNumPointLights, (dwNumDirectionalLights + dwNumSpotLights) * NUM_VECTORS_PER_LIGHT, NUM_VECTORS_PER_LIGHT, 0
                };
                m_pd3dDevice->SetVertexShaderConstantI(0, i0, sizeof(i0) / (sizeof(int)*4));
            }
            else
            {
                numPasses = 1;
                // Turn on light #0 and #2, and turn off light #1
                m_pd3dDevice->LightEnable( 0, TRUE );
                m_pd3dDevice->LightEnable( 1, FALSE );
                for (DWORD i=0; i < m_dwNumLights; i++)
                    m_pd3dDevice->LightEnable( 2 + i, TRUE );
            }

            for( UINT iPass = 0; iPass < numPasses; iPass++ )
            {
                if( m_bUseVertexShaders )
                    m_pEffect->Pass( iPass );

                // Draw the floor
                D3DXMatrixTranslation( &matTrans, -5.0f, -5.0f, -5.0f );
                D3DXMatrixRotationZ( &matRotate, 0.0f );
                matWorld = matRotate * matTrans;
                if( m_bUseVertexShaders )
                    SetMatrices(&matWorld, &matViewProj);
                else
                    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
                m_pWallMesh->DrawSubset(0);

                // Draw the back wall
                D3DXMatrixTranslation( &matTrans, 5.0f,-5.0f, -5.0f );
                D3DXMatrixRotationZ( &matRotate, D3DX_PI/2 );
                matWorld = matRotate * matTrans;
                if( m_bUseVertexShaders )
                    SetMatrices(&matWorld, &matViewProj);
                else
                    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
                m_pWallMesh->DrawSubset(0);

                // Draw the side wall
                D3DXMatrixTranslation( &matTrans, -5.0f, -5.0f, 5.0f );
                D3DXMatrixRotationX( &matRotate,  -D3DX_PI/2 );
                matWorld = matRotate * matTrans;
                if( m_bUseVertexShaders )
                    SetMatrices(&matWorld, &matViewProj);
                else
                    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
                m_pWallMesh->DrawSubset(0);
            }
            if( m_bUseVertexShaders )
                m_pEffect->End();

            if( m_bUseVertexShaders )
            {
                SetLight(0, &m_light1);
                int i0[] = {1, 0, NUM_VECTORS_PER_LIGHT, 0,
                            0,0,0,0,
                            0,0,0,0};
                m_pd3dDevice->SetVertexShaderConstantI(0, i0, sizeof(i0) / (sizeof(int)*4));
            }
            else
            {
                // Turn on light #1, and turn off light #0 and #2
                m_pd3dDevice->LightEnable( 0, FALSE );
                m_pd3dDevice->LightEnable( 1, TRUE );
                for (DWORD i=0; i < m_dwNumLights; i++)
                    m_pd3dDevice->LightEnable( 2 + i, FALSE );
            }

            m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

            // Draw the mesh representing the light
            for (DWORD i=0; i < m_dwNumLights; i++)
            {
                if( m_light[i].Type == D3DLIGHT_POINT )
                {
                    // Just position the point light -- no need to orient it
                    D3DXMatrixTranslation( &matWorld, m_light[i].Position.x, 
                        m_light[i].Position.y, m_light[i].Position.z );
                    if( m_bUseVertexShaders )
                    {
                        SetMatrices (&matWorld, &matViewProj);
                        m_pEffect->Begin( &numPasses, 0 );
                        for( UINT iPass = 0; iPass < numPasses; iPass++ )
                        {
                            m_pEffect->Pass( iPass );
                            m_pSphereMesh->DrawSubset(0);
                        }
                        m_pEffect->End();
                    }
                    else
                    {
                        m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
                        m_pSphereMesh->DrawSubset(0);
                    }

                }
                else
                {
                    // Position the light and point it in the light's direction
                    D3DXVECTOR3 vecFrom( m_light[i].Position.x, m_light[i].Position.y, m_light[i].Position.z );
                    D3DXVECTOR3 vecAt( m_light[i].Position.x + m_light[i].Direction.x, 
                                    m_light[i].Position.y + m_light[i].Direction.y,
                                    m_light[i].Position.z + m_light[i].Direction.z );
                    D3DXVECTOR3 vecUp( 0, 1, 0);
                    D3DXMATRIXA16 matWorldInv;
                    D3DXMatrixLookAtLH( &matWorldInv, &vecFrom, &vecAt, &vecUp);
                    D3DXMatrixInverse( &matWorld, NULL, &matWorldInv);
                    if( m_bUseVertexShaders )
                    {
                        SetMatrices (&matWorld, &matViewProj);
                        m_pEffect->Begin( &numPasses, 0 );
                        for( UINT iPass = 0; iPass < numPasses; iPass++ )
                        {
                            m_pEffect->Pass( iPass );
                            m_pConeMesh->DrawSubset(0);
                        }
                        m_pEffect->End();
                    }
                    else
                    {
                        m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
                        m_pConeMesh->DrawSubset(0);
                    }
                }
            }
        }
        // Output statistics
        m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );
        TCHAR* strLight = (m_light[0].Type == D3DLIGHT_POINT ? TEXT("Point Lights") : 
            m_light[0].Type == D3DLIGHT_SPOT ? TEXT("Spot Lights") : TEXT("Directional Lights"));
        TCHAR strInfo[300];
        if( m_dwNumLights )
        {
            wsprintf( strInfo, TEXT("%d %s, %dx%d vertices in wall/floor mesh"), m_dwNumLights, strLight, m_n, m_m );
            m_pFontSmall->DrawText( 2, 40, D3DCOLOR_ARGB(255,255,255,255), strInfo );
        }
        if( m_bUseVertexShaders )
        {
            wsprintf( strInfo, TEXT("Using vertex shader: %s"), m_pCurTechniqueName);
            if( !m_bTechniqueValid )
                lstrcat( strInfo, TEXT(" (Warning: validation failed)") );
            m_pFontSmall->DrawText( 2, 60, D3DCOLOR_ARGB(255,255,255,255), strInfo );
        }
        else
            m_pFontSmall->DrawText( 2, 60, D3DCOLOR_ARGB(255,255,255,255), TEXT("Using fixed function"));
        if( m_bShowHelp )
        {
            m_pFontSmall->DrawText( 2, 80, D3DCOLOR_ARGB(255,255,255,255), 
                TEXT("Use arrow keys to change mesh density") );
            m_pFontSmall->DrawText( 2, 100, D3DCOLOR_ARGB(255,255,255,255), 
                TEXT("Press W to toggle wireframe mode") );
            m_pFontSmall->DrawText( 2, 120, D3DCOLOR_ARGB(255,255,255,255), 
                TEXT("Press S to toggle between fixed function and programmable vertex pipeline") );
            m_pFontSmall->DrawText( 2, 140, D3DCOLOR_ARGB(255,255,255,255), 
                TEXT("Press D to decrement number of lights") );
            m_pFontSmall->DrawText( 2, 160, D3DCOLOR_ARGB(255,255,255,255), 
                TEXT("Press I to increment number of lights") );
            m_pFontSmall->DrawText( 2, 180, D3DCOLOR_ARGB(255,255,255,255), 
                TEXT("Press T to change light type") );
            m_pFontSmall->DrawText( 2, 200, D3DCOLOR_ARGB(255,255,255,255), 
                TEXT("Press V to change vertex shader") );
        }
        else
        {
            m_pFontSmall->DrawText(  2, 80, D3DCOLOR_ARGB(255,255,255,255), 
                TEXT("Press F1 for help") );
        }

        // End the scene.
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Invalidates device objects.  
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    SAFE_RELEASE( m_pWallMesh );
    SAFE_RELEASE( m_pSphereMesh );
    SAFE_RELEASE( m_pConeMesh );
    m_pFont->InvalidateDeviceObjects();
    m_pFontSmall->InvalidateDeviceObjects();

    if( m_pEffect != NULL )
        m_pEffect->OnLostDevice();

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
    m_pFontSmall->DeleteDeviceObjects();

    SAFE_RELEASE( m_pEffect );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FinalCleanup()
{
    // Cleanup D3D font
    SAFE_DELETE( m_pFont );
    SAFE_DELETE( m_pFontSmall );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Message proc function
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam )
{
    switch( uMsg )
    {
    case WM_COMMAND:
        switch( LOWORD(wParam) )
        {
        case IDM_TOGGLEHELP:
            m_bShowHelp = !m_bShowHelp;
            break;
        case IDM_TOGGLEWIREFRAME:
            m_bWireframe = !m_bWireframe;
            break;
        case IDM_TOGGLESHADERS:
            m_bUseVertexShaders = !m_bUseVertexShaders;
            break;
        case IDM_TOGGLEVERTEXSHADERS:
            {
                D3DXEFFECT_DESC EffectDesc;
                m_pEffect->GetDesc( &EffectDesc );
                m_iCurTechnique++;
                if( m_iCurTechnique >= EffectDesc.Techniques )
                    m_iCurTechnique = 0;
                D3DXTECHNIQUE_DESC TechDesc;
                D3DXHANDLE hTech = m_pEffect->GetTechnique( m_iCurTechnique );
                m_pEffect->GetTechniqueDesc( hTech, &TechDesc );
                m_pCurTechniqueName = TechDesc.Name;
                m_pEffect->SetTechnique( hTech );
                m_bTechniqueValid = SUCCEEDED( m_pEffect->ValidateTechnique( hTech ) );
            }
            break;
        case IDM_INCNUMLIGHTS:
            if( m_dwNumLights < MAXLIGHTS )
                m_dwNumLights++;
            break;
        case IDM_DECNUMLIGHTS:
            if( m_dwNumLights > 0 )
                m_dwNumLights--;
            break;
        case IDM_CHANGELIGHTTYPE:
            m_CurrentLightType = (D3DLIGHTTYPE)((DWORD)m_CurrentLightType + 1);
            if( m_CurrentLightType > 3)
                m_CurrentLightType = (D3DLIGHTTYPE)0;
            break;
        case IDM_INCREASERESOLUTION:
            if( m_n < 64 && m_m < 64 )
            {
                m_n *= 2;
                m_m *= 2;
                m_nTriangles = (m_n-1) * (m_m-1) * 2;
                BuildWallMesh();
            }
            break;
        case IDM_DECREASERESOLUTION:
            if( m_n > 2 && m_m > 2 )
            {
                m_n /= 2;
                m_m /= 2;
                m_nTriangles = (m_n-1) * (m_m-1) * 2;
                BuildWallMesh();
            }
            break;
        }
        break;
    }

    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}
