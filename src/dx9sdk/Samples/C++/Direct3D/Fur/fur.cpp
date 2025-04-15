//-----------------------------------------------------------------------------
// File: Fur.cpp
//
// Desc: Example code showing how to do real-time fur rendering.
//
// GEOMETRY
// An original copy of the geometry is maintained in vertex stream 0.
// A copy of the original vertex data is then appended to the same vertex buffer.
// This is because the fins will contain at most two vertices for every base
// vertex (The original vertex, plus its extruded position for the fin extent).
// Likewise, the index buffer contains one copy of the original indices.  These
// indices are used for the base pass as well as the shells.  Appended onto the
// end of these indices are the index data for the fins pass.
// Shell and fin texturing data are generated in a second stream (stream 1).
// VB(0):  VBChunk0 (original vertices) + VBChunk1 (second copy of original vertices)
// IB:     IBChunk0 (original indices) + IBChunk1 (fin indices)
// VB(1a): TexCoordA Shell texture coordinates
// VB(1b): TexCoordB Fin texture coordinates
// VBChunk0 and IBChunk0 comprise the original mesh.
// VBChunk1, IBChunk1, TexCoordA, and TexCoordB are generated in a pre-processing
// stage.
// BASE PASS DESCRIPTION
// Indices:  IBChunk0
// Stream 0: VBChunk0
// Stream 1: Not used
// Shader:   Normal FVF or shader.
// This draws the base object as it otherwise would normally appear.
// SHELL PASS DESCRIPTION
// Indices:  IBChunk0
// Stream 0: VBChunk0
// Stream 1: TexCoordA(Stream 1)
// Shader:   Displaces the shells outward around the mesh.
// FIN PASS DESCRIPTION
// Stream 0: VBChunk0 + VBChunk1
// Stream 1: TexCoordB
// Indices:  IBChunk1
// Shader:   The fin pass vertex shader extrudes the vertices using
// the Stream1 texture v coordinate as an extrusion factor.  The vertex in VBChunk0
// contains an equivalent in VBChunk1, however one will be extruded (by the texture
// coordinates) and the other will not.
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
#include "D3DFont.h"
#include "D3DUtil.h"
#include "resource.h"


// structure contains basic mesh vertex
struct MYVERTEX
{
    float x,y,z;
    float x0, y0, z0;
    DWORD diffuse;

    static const DWORD FVF;
};
const DWORD MYVERTEX::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

// both the shells and fins add a stream of texture coordinates to augment the basic mesh
struct MYTEXCOORD
{
    float u, v;
};



//-----------------------------------------------------------------------------
// Name: class CFuzzyMesh
// Desc: Geometry Class. The base class for a shells & fins mesh.
//-----------------------------------------------------------------------------
class CFuzzyMesh
{
public:
    virtual void Init( MYVERTEX* pVertices, WORD* pIndices, MYTEXCOORD* pShellTexcoords, MYTEXCOORD* pFinTexcoords ) = 0;
    virtual DWORD GetNumShellVertices() = 0;
    virtual DWORD GetNumFinVertices() = 0;
    virtual DWORD GetNumShellPrimitives() = 0;
    virtual DWORD GetNumFinPrimitives() = 0;
    static CFuzzyMesh* CreateCube( UINT WidthSlices, UINT nHeightSlices, DWORD dwColor, FLOAT fTextureScale );
};




//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
protected:
    CD3DFont*               m_pFont;
    bool                    m_bBasePass;
    bool                    m_bShellPass;
    bool                    m_bFinPass;
    UINT                    m_nShells;
    CFuzzyMesh*             m_pFuzzyMesh;
    LPDIRECT3DVERTEXDECLARATION9        m_pDeclaration;
    LPDIRECT3DVERTEXBUFFER9 m_pVB;
    LPDIRECT3DVERTEXBUFFER9 m_pShellTexVB;
    LPDIRECT3DVERTEXBUFFER9 m_pFinTexVB;
    LPDIRECT3DINDEXBUFFER9  m_pIB;
    LPDIRECT3DTEXTURE9*     m_pShellTextures;
    LPDIRECT3DTEXTURE9      m_pFinTexture;
    LPD3DXEFFECT            m_pEffect;
    UINT                    m_dwNumShellVertices;
    UINT                    m_dwNumShellPrimitives;
    UINT                    m_dwNumFinVertices;
    UINT                    m_dwNumFinPrimitives;
    D3DXHANDLE              m_hBaseTechnique;
    D3DXHANDLE              m_hFinsTechnique;
    D3DXHANDLE              m_hShellTechnique;
    D3DXHANDLE              m_hShellTexture;
    D3DXHANDLE              m_hShellScalingFactor;
    D3DXHANDLE              m_hWorldTransform;

protected:
    HRESULT ConfirmDevice( D3DCAPS9*, DWORD, D3DFORMAT, D3DFORMAT );
    HRESULT OneTimeSceneInit();
    HRESULT Render();
    HRESULT FrameMove();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects(); 
    HRESULT DeleteDeviceObjects();
    HRESULT FinalCleanup();
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    VOID    SetMenuStates();

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
    // inherited
    m_strWindowTitle    = _T("Fur: Fur rendering using shells and fins");
    m_d3dEnumeration.AppUsesDepthBuffer = TRUE;

    // intrinsic
    m_pFont            = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_dwNumShellVertices   = 0;
    m_dwNumShellPrimitives = 0;
    m_dwNumFinVertices     = 0;
    m_dwNumFinPrimitives   = 0;
    m_pFuzzyMesh           = NULL;

    // D3D Resources
    m_pVB            = NULL;
    m_pIB            = NULL;
    m_pDeclaration   = NULL;
    m_pEffect        = NULL;
    m_pShellTexVB    = NULL;
    m_pFinTexVB      = NULL;
    m_pShellTextures = NULL;
    m_pFinTexture    = NULL;

    // render control
    m_bBasePass  = true;
    m_bShellPass = true;
    m_bFinPass   = true;
    m_nShells = 16;
}




//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
                                          D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat )
{
    // Need to support post-pixel processing (for alpha blending)
    if( FAILED( m_pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
        adapterFormat, D3DUSAGE_RENDERTARGET | D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
        D3DRTYPE_SURFACE, backBufferFormat ) ) )
    {
        return E_FAIL;
    }

    if( (dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING ) ||
        (dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING ) )
    {
        if( pCaps->VertexShaderVersion < D3DVS_VERSION(1,1) )
            return E_FAIL;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    m_pFuzzyMesh = CFuzzyMesh::CreateCube( 8, 8, D3DCOLOR_XRGB(0x60, 0xa0, 0x40), 0.125f );
    if( NULL == m_pFuzzyMesh )
        return D3DAPPERR_MEDIANOTFOUND;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;
    TCHAR strPath[MAX_PATH];

    m_pFont->InitDeviceObjects( m_pd3dDevice );

    // Declaration - used for shell and fin passes
    D3DVERTEXELEMENT9 declShell[] =
    {
        { 0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, 
        { 0, 12, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0}, 
        { 0, 24, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,  0}, 
        { 1, 0,  D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0}, 
        D3DDECL_END()
    };

    if( FAILED( hr = m_pd3dDevice->CreateVertexDeclaration( declShell, &m_pDeclaration ) ) )
        return hr;

    // Load the effect file
    if( FAILED( hr = DXUtil_FindMediaFileCb( strPath, sizeof(strPath), TEXT("Fur.fx") ) ) )
        return hr;
    if( FAILED( hr = D3DXCreateEffectFromFile( m_pd3dDevice, strPath, NULL, NULL, 0, NULL, &m_pEffect, NULL) ) )
        return hr;
    
    // make sure the render pass options are set in the menu
    SetMenuStates();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    HRESULT hr;
    MYVERTEX* pBaseVertex = NULL;
    MYTEXCOORD* pShellTexVerts;
    MYTEXCOORD* pFinTexVerts;
    WORD* pBaseIndex = NULL;

    m_pFont->RestoreDeviceObjects();

    // create the shell textures
    m_pShellTextures = new LPDIRECT3DTEXTURE9[ m_nShells ];
    if( NULL == m_pShellTextures )
        return E_FAIL;

    // initialize the array of shell textures to NULL
    memset( m_pShellTextures, 0, m_nShells * sizeof(LPDIRECT3DTEXTURE9) );

    // the filename buffer
    TCHAR szFileName[MAX_PATH];
    szFileName[MAX_PATH-1] = '\0';

    // load each shell level
    for( UINT i = 0; i<m_nShells; i++ )
    {
        _sntprintf( szFileName, MAX_PATH-1, _T("fur_%02d.dds"), i );
        if( FAILED( D3DUtil_CreateTexture( m_pd3dDevice, szFileName, 
                                            m_pShellTextures + i, D3DFMT_A8R8G8B8 ) ) )
        {
            return D3DAPPERR_MEDIANOTFOUND;
        }
    }

    // create the fin texture
    if( FAILED( D3DUtil_CreateTexture( m_pd3dDevice, _T("fur_fin_00.dds"),
                                       &m_pFinTexture, D3DFMT_A8R8G8B8 ) ) )
    {
        return D3DAPPERR_MEDIANOTFOUND;
    }

    // proceed to load mesh data into the D3D Resources
    if( NULL == m_pFuzzyMesh )
    {
        return D3DAPPERR_MEDIANOTFOUND;
    }

    // save the number of vertices/primitives in the geometry
    m_dwNumShellVertices = m_pFuzzyMesh->GetNumShellVertices();
    m_dwNumShellPrimitives = m_pFuzzyMesh->GetNumShellPrimitives();
    m_dwNumFinVertices = m_pFuzzyMesh->GetNumFinVertices();
    m_dwNumFinPrimitives = m_pFuzzyMesh->GetNumFinPrimitives();

    DWORD dwBufferSize;
    dwBufferSize = m_dwNumShellPrimitives * 3 * sizeof(WORD) + m_dwNumFinPrimitives * 3 * sizeof(WORD);
    hr = m_pd3dDevice->CreateIndexBuffer( dwBufferSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, 0L );
    if( FAILED(hr) )
        return hr;

    dwBufferSize = m_dwNumFinVertices * sizeof(MYVERTEX);
    hr = m_pd3dDevice->CreateVertexBuffer( dwBufferSize, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pVB, 0L );
    if( FAILED(hr) )
        return hr;

    dwBufferSize = m_dwNumShellVertices * sizeof(MYTEXCOORD);
    hr = m_pd3dDevice->CreateVertexBuffer( dwBufferSize, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pShellTexVB, 0L );
    if( FAILED(hr) )
        return hr;
    
    dwBufferSize = m_dwNumFinVertices * sizeof(MYTEXCOORD);
    hr = m_pd3dDevice->CreateVertexBuffer( dwBufferSize, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_pFinTexVB, 0L );
    if( FAILED(hr) )
        return hr;

    if( FAILED(hr = m_pVB->Lock( 0, 0, (VOID**)&pBaseVertex, 0 )) )
        return hr;
    
    if( FAILED(hr = m_pShellTexVB->Lock( 0, 0, (VOID**)&pShellTexVerts, 0 )) )
        return hr;

    if( FAILED(hr = m_pFinTexVB->Lock( 0, 0, (VOID**)&pFinTexVerts, 0 )) )
        return hr;

    if( FAILED(hr = m_pIB->Lock( 0, 0, (VOID**)&pBaseIndex, 0 )) )
        return hr;

    // Load the mesh data into the buffers
    m_pFuzzyMesh->Init( pBaseVertex, pBaseIndex, pShellTexVerts, pFinTexVerts );

    // unlock the buffers and proceed
    m_pIB->Unlock();
    m_pFinTexVB->Unlock();
    m_pShellTexVB->Unlock();
    m_pVB->Unlock();
    
    // save frequently used handles
    m_hBaseTechnique      = m_pEffect->GetTechniqueByName( TEXT("Base") );
    m_hFinsTechnique      = m_pEffect->GetTechniqueByName( TEXT("Fins") );
    m_hShellTechnique     = m_pEffect->GetTechniqueByName( TEXT("Shells") );
    m_hShellTexture       = m_pEffect->GetParameterByName( NULL, TEXT("ShellTex") );
    m_hShellScalingFactor = m_pEffect->GetParameterByName( NULL, TEXT("ShellScalingFactor") );
    m_hWorldTransform     = m_pEffect->GetParameterBySemantic( NULL, TEXT("WORLD") );

    D3DXMATRIXA16 view, projection;
    D3DXVECTOR3 Eye = D3DXVECTOR3( 0.f, 0.f, -5.1f );
    D3DXVECTOR3 At  = D3DXVECTOR3( 0.f, 0.f, 0.f );
    D3DXVECTOR3 Up  = D3DXVECTOR3( 0.f, 1.f, 0.f );
    
    // Eye position
    m_pEffect->SetValue( m_pEffect->GetParameterByName( NULL, TEXT("Eye") ), &Eye, sizeof(D3DXVECTOR3) );

    // establish view matrix    
    D3DXMatrixLookAtLH( &view, &Eye, &At, &Up );
    m_pEffect->SetMatrix( m_pEffect->GetParameterBySemantic( NULL, TEXT("VIEW") ), &view );
    
    // establish projection matrix
    D3DXMatrixPerspectiveFovLH( &projection, D3DX_PI*0.25f,(float)m_dwCreationWidth / (float)m_dwCreationHeight, 0.1f, 100.f);
    m_pEffect->SetMatrix( m_pEffect->GetParameterBySemantic( NULL, TEXT("PROJECTION") ), &projection );

    // Fin texture
    m_pEffect->SetTexture( m_pEffect->GetParameterByName( NULL, TEXT("FinTex") ), m_pFinTexture );

    // Set default states for the application
    m_pEffect->SetTechnique( m_pEffect->GetTechniqueByName( TEXT("Init") ) );
    UINT numPasses;
    m_pEffect->Begin( &numPasses, D3DXFX_DONOTSAVESTATE );
    for( UINT iPass = 0; iPass < numPasses; iPass++ )
    {
        m_pEffect->Pass( iPass );
    }
    m_pEffect->End();

    if( m_pEffect != NULL )
        m_pEffect->OnResetDevice();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();
    SAFE_RELEASE( m_pIB );
    SAFE_RELEASE( m_pVB );
    SAFE_RELEASE( m_pShellTexVB );
    SAFE_RELEASE( m_pFinTexVB );
    SAFE_RELEASE( m_pFinTexture );
    if( m_pShellTextures )
    {
        for( UINT i = 0; i<m_nShells; i++ )
        {
            SAFE_RELEASE( *(m_pShellTextures+i) );
        }
        SAFE_DELETE_ARRAY( m_pShellTextures );
    }

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
    SAFE_RELEASE( m_pDeclaration );
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
    SAFE_DELETE( m_pFuzzyMesh );
    SAFE_DELETE( m_pFont );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    D3DXMATRIXA16 mat, world;

    // establish world matrix
    D3DXMatrixIdentity( &world );
    D3DXMatrixMultiply( &world, &world, D3DXMatrixRotationY( &mat, m_fTime * D3DX_PI * .2f ));
    D3DXMatrixMultiply( &world, &world, D3DXMatrixRotationX( &mat, m_fTime * D3DX_PI * .2f ));

    m_pEffect->SetMatrix( m_hWorldTransform, &world );

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
    // clear
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
        0x000000ff, 1.0f, 0L );

    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        UINT numPasses;

        // The main MYVERTEX vertex buffer is used for all 3 passes
        m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof MYVERTEX );

        // render the base object
        if( m_bBasePass )
        {
            m_pd3dDevice->SetStreamSource( 1, 0L, 0, 0 );
            m_pd3dDevice->SetIndices( m_pIB );

            m_pEffect->SetTechnique( m_hBaseTechnique );
            m_pEffect->Begin( &numPasses, 0 );
            for( UINT iPass = 0; iPass < numPasses; iPass++ )
            {
                m_pEffect->Pass( iPass );
                m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_dwNumShellVertices, 0, m_dwNumShellPrimitives );
            }
            m_pEffect->End();
        }

        // render fins
        if( m_bFinPass )
        {
            m_pd3dDevice->SetVertexDeclaration( m_pDeclaration );
            m_pd3dDevice->SetStreamSource( 1, m_pFinTexVB, 0, sizeof MYTEXCOORD );
            m_pd3dDevice->SetIndices( m_pIB );

            m_pEffect->SetTechnique( m_hFinsTechnique );
            m_pEffect->Begin( &numPasses, 0 );
            for( UINT iPass = 0; iPass < numPasses; iPass++ )
            {
                m_pEffect->Pass( iPass );
                m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_dwNumFinVertices, m_dwNumShellPrimitives*3, m_dwNumFinPrimitives );
            }
            m_pEffect->End();
        }

       
        // render shells
        if( m_bShellPass )
        {
            m_pd3dDevice->SetVertexDeclaration( m_pDeclaration );
            m_pd3dDevice->SetStreamSource( 1, m_pShellTexVB, 0, sizeof MYTEXCOORD );
            m_pd3dDevice->SetIndices( m_pIB );

            m_pEffect->SetTechnique( m_hShellTechnique );
            m_pEffect->Begin( &numPasses, 0 );
            for( UINT iPass = 0; iPass < numPasses; iPass++ )
            {
                m_pEffect->Pass( iPass );
                for( UINT iShell = 0; iShell < m_nShells; iShell++ )
                {
                    // set the texture for this layer
                    m_pEffect->SetTexture( m_hShellTexture, m_pShellTextures[iShell] );
                    m_pEffect->SetFloat( m_hShellScalingFactor, (FLOAT)(iShell + 1) / (FLOAT)m_nShells );

                    m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_dwNumShellVertices, 0, m_dwNumShellPrimitives );
                }
            }
            m_pEffect->End();
        }

        // Dump out the FPS
        m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Message proc function to handle key and menu input
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    // Handle key presses
    switch( uMsg )
    {
        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
            case IDM_BASE:
                m_bBasePass = !m_bBasePass;
                break;
            case IDM_SHELLS:
                m_bShellPass = !m_bShellPass;
                break;
            case IDM_FINS:
                m_bFinPass = !m_bFinPass;
                break;
            }

            // Update the menus, in case any state changes occurred
            SetMenuStates();
        }
    }

    // Pass remaining messages to default handler
    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: SetMenuStates()
// Desc:
//-----------------------------------------------------------------------------
void CMyD3DApplication::SetMenuStates()
{
    HMENU hMenu = GetMenu( m_hWnd );

    CheckMenuItem( hMenu, IDM_BASE,
                    m_bBasePass ? MF_CHECKED : MF_UNCHECKED );
    CheckMenuItem( hMenu, IDM_SHELLS,
                    m_bShellPass ? MF_CHECKED : MF_UNCHECKED );
    CheckMenuItem( hMenu, IDM_FINS,
                    m_bFinPass ? MF_CHECKED : MF_UNCHECKED );
}




//-----------------------------------------------------------------------------
// Q: What would it take to render an arbitrary mesh?
// A: The problem is in generating texture coordinates.
//    A patching algorithm would need to be implemented to apply texture patches
//    to the mesh in a locally flattened manner
//    Fins would then be grown from the mesh along the seams of such patches.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: class CFuzzyCubeMesh
// Desc: Implements a proceedural fuzzy cube mesh
//-----------------------------------------------------------------------------
class CFuzzyCubeMesh : public CFuzzyMesh
{
protected:
    UINT  m_nWidthSlices;
    UINT  m_nHeightSlices;
    DWORD m_dwColor;
    FLOAT m_fTextureScale;
    UINT  m_dwNumShellVertices;
    UINT  m_dwNumShellPrimitives;
    UINT  m_dwNumFinVertices;
    UINT  m_dwNumFinPrimitives;

public:
    CFuzzyCubeMesh( UINT WidthSlices, UINT nHeightSlices, DWORD dwColor, FLOAT fTextureScale );
    void Init( MYVERTEX* pVertices, WORD* pIndices, MYTEXCOORD* pShellTexcoords, MYTEXCOORD* pFinTexcoords );
    void TesselateQuad( const D3DVECTOR& normal, const D3DVECTOR& Left, MYVERTEX* pVertices,
                        WORD* pIndices, WORD dwIndexOffset );
    void FinQuad( WORD wExtrusionOffset, MYTEXCOORD* pShellTexCoords, MYTEXCOORD* pFinTexCoords, WORD* pIndices );
    void QuadVertex( const D3DVECTOR& normal, const D3DVECTOR& Left, const D3DVECTOR& Up, UINT x, UINT y,
                    UINT x_max, UINT y_max, MYVERTEX* pVertex );
    DWORD GetNumShellVertices()   { return m_dwNumShellVertices; }
    DWORD GetNumFinVertices()     { return m_dwNumFinVertices; }
    DWORD GetNumShellPrimitives() { return m_dwNumShellPrimitives; }
    DWORD GetNumFinPrimitives()   { return m_dwNumFinPrimitives; }
};




//-----------------------------------------------------------------------------
// Name: CFuzzyCubeMesh
// Desc: Constructor - calculates mesh expanses for later use
//-----------------------------------------------------------------------------
CFuzzyCubeMesh::CFuzzyCubeMesh( UINT WidthSlices, UINT nHeightSlices, DWORD dwColor, FLOAT fTextureScale )
    : m_nWidthSlices(WidthSlices), m_nHeightSlices(nHeightSlices), m_dwColor(dwColor), m_fTextureScale( fTextureScale )
{
    // save the number of vertices in the base/shells mesh
    m_dwNumShellVertices = 6 * (m_nWidthSlices+1) * (m_nHeightSlices+1);
    m_dwNumShellPrimitives = 6 * 2 * m_nWidthSlices * m_nHeightSlices;

    // for every shell vert there are two face vert
    m_dwNumFinVertices = m_dwNumShellVertices<<1;
    m_dwNumFinPrimitives = 6 * 2 * ((m_nWidthSlices+1) * (m_nHeightSlices)  + (m_nWidthSlices) * (m_nHeightSlices+1));
}




//-----------------------------------------------------------------------------
// Name: Init()
// Desc: Returns the vertices, indices, and texcoords
//-----------------------------------------------------------------------------
void CFuzzyCubeMesh::Init( MYVERTEX* pVertices, WORD* pIndices, MYTEXCOORD* pShellTexcoords, MYTEXCOORD* pFinTexcoords )
{
    static const D3DVECTOR face[12] =
    {
        1.f, 0.f, 0.f,    0.f,  1.f,  0.f, 
        0.f, 1.f, 0.f,   -1.f,  0.f,  0.f,
        0.f, 0.f, 1.f,    1.f,  0.f,  0.f, 

        -1.f, 0.f, 0.f,   0.f, -1.f,  0.f, 
        0.f, -1.f, 0.f,  -1.f,  0.f,  0.f,
        0.f, 0.f, -1.f,  -1.f,  0.f,  0.f, 
    };
    
    WORD wIndexOffset = 0;
    MYVERTEX* pBaseVertexStart = pVertices;
    DWORD dwPrimsPerFace = m_dwNumShellPrimitives / 6;
    DWORD dwVertsPerFace = m_dwNumShellVertices / 6;

    for( unsigned faces = 0; faces < 6; faces++ )
    {
        TesselateQuad( face[2*faces], face[2*faces+1], pVertices, pIndices, wIndexOffset);
        pVertices       += dwVertsPerFace;
        wIndexOffset    += (WORD)dwVertsPerFace;
        pIndices        += dwPrimsPerFace * 3;
    }
    // to extrude the vertices, we need an identical copy of the tesselated vertices
    // appended to the end of the tesselation
    memcpy( pVertices, pBaseVertexStart, m_dwNumShellVertices*sizeof(MYVERTEX) );
    
    // generate the fin texture coordinates and indices
    FinQuad( (WORD)m_dwNumShellVertices, pShellTexcoords, pFinTexcoords, pIndices );
}




//-----------------------------------------------------------------------------
// Name: TesselateQuad()
// Desc: Tesselates one Quad/Cube Face
//-----------------------------------------------------------------------------
void CFuzzyCubeMesh::TesselateQuad( const D3DVECTOR& normal, const D3DVECTOR& Left, MYVERTEX* pVertices,
                                      WORD* pIndices, WORD dwIndexOffset )
{
    // given the general surface normal, and a "left" width-traversal vector, calculate an "up" height-traversal direction
    D3DXVECTOR3 Up;
    D3DXVec3Cross( &Up, (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&Left);

    UINT height;
    UINT width;

    // loop through each vertex, left to right and top to bottom
    for( height = 0; height < (m_nHeightSlices+1); height++ )
    {
        for( width = 0; width < (m_nWidthSlices+1); width++ )
        {
            // generate the vertex position, normal, and diffuse color
            QuadVertex( normal, Left, Up, width, height, m_nWidthSlices, m_nHeightSlices, pVertices++);
        }
    }

    // create the index buffer members, quads starting from "upper left"
    for( height = 0; height < m_nHeightSlices; height++ )
    {
        for( width = 0; width < m_nWidthSlices; width++ )
        {
            // first triangle of quad
            *pIndices++ = dwIndexOffset + (height)*(m_nWidthSlices+1) + width;          // top left
            *pIndices++ = dwIndexOffset + (height)*(m_nWidthSlices+1) + (width+1);      // top right
            *pIndices++ = dwIndexOffset + (height+1)*(m_nWidthSlices+1) + width;        // bottom left
            // second triangle
            *pIndices++ = dwIndexOffset + (height+1)*(m_nWidthSlices+1) + width;        // bottom left
            *pIndices++ = dwIndexOffset + (height)*(m_nWidthSlices+1) + (width+1);      // top right
            *pIndices++ = dwIndexOffset + (height+1)*(m_nWidthSlices+1) + (width+1);    // bottom right
        }
    }
}




//-----------------------------------------------------------------------------
// Name: FinQuad()
// Desc: Generates fins matching TesselateQuad
//-----------------------------------------------------------------------------
void CFuzzyCubeMesh::FinQuad( WORD wExtOffset, MYTEXCOORD* pShellTexCoords, MYTEXCOORD* pFinTexCoords, WORD* pIndices )
{
    WORD vertices_per_quad_face = (m_nHeightSlices+1)*(m_nWidthSlices+1);
    
    UINT face;

    // anchored vertices
    for( face = 0; face < 6; face++ )
    {
        for( UINT height = 0; height < (m_nHeightSlices+1); height++ )
        {
            for( UINT width = 0; width < (m_nWidthSlices+1); width++ )
            {
                // set the shell tex coords
                pShellTexCoords->u = m_fTextureScale * (float)(width);
                pShellTexCoords->v = m_fTextureScale * (float)(height);
                pShellTexCoords++;

                // scale the texture larger by a factor of two
                pFinTexCoords->u = m_fTextureScale * (float)(width+height) * 0.5f;
                // this is the anchored vertex
                pFinTexCoords->v = 0.f;

                (pFinTexCoords+wExtOffset)->u = m_fTextureScale * (float)(width+height) * 0.5f;
                (pFinTexCoords+wExtOffset)->v = 1.f;
                pFinTexCoords++;
            }
        }
    }

    WORD dwIndexOffset = 0;
    // create "horizontal" fins
    for( face = 0; face < 6; face++ )
    {
        for( UINT height = 0; height <= m_nHeightSlices; height++ )
        {
            for( UINT width = 0; width < m_nWidthSlices; width++ )
            {
                // first triangle of quad
                WORD base_index;
                base_index = dwIndexOffset + (height)*(m_nWidthSlices+1) + width;
                *pIndices++ = base_index;                       // left base
                *pIndices++ = base_index + wExtOffset;         // left extruded
                *pIndices++ = base_index + 1;                   // right base
                // second triangle
                *pIndices++ = base_index + 1;                   // right base
                *pIndices++ = base_index + wExtOffset;         // left extruded
                *pIndices++ = base_index + wExtOffset + 1;     // right extruded
            }
        }
        dwIndexOffset += vertices_per_quad_face;
    }

    // create the "vertical" fins
    dwIndexOffset = 0;
    for( face = 0; face < 6; face++ )
    {
        for( UINT width = 0; width <= m_nWidthSlices; width++ )
        {
            for( UINT height = 0; height < m_nHeightSlices; height++ )
            {
                WORD base_index;
                base_index = dwIndexOffset + (height)*(m_nWidthSlices+1) + width;
                // first triangle of quad
                *pIndices++ = base_index;                                       // top base
                *pIndices++ = base_index + wExtOffset;                         // top extruded
                *pIndices++ = base_index + (m_nWidthSlices + 1);                // bottom base
                // second triangle
                *pIndices++ = base_index + (m_nWidthSlices +1 );                // bottom base
                *pIndices++ = base_index + wExtOffset;                         // top extruded
                *pIndices++ = base_index + (m_nWidthSlices + 1) + wExtOffset;  // bottom extruded
            }
        }
        dwIndexOffset += vertices_per_quad_face;
    }
}




//-----------------------------------------------------------------------------
// Name: QuadVertex()
// Desc: Generates vertex (minus tex coords) for a 2-d quad, scaled -1 to 1
//       
//-----------------------------------------------------------------------------
void CFuzzyCubeMesh::QuadVertex( const D3DVECTOR& normal, const D3DVECTOR& Left, const D3DVECTOR& Up,
                                   UINT x, UINT y, UINT x_max, UINT y_max, MYVERTEX* pVertex )
{
    D3DXVECTOR3 here;
    // starting 0,0,0 move this vertex outwards by the normal direction
    here = static_cast<D3DXVECTOR3>(normal);
    // travel all the way to the left of this face grid
    here += static_cast<D3DXVECTOR3>(Left);
    // travel now to the upper left corner
    here += static_cast<D3DXVECTOR3>(Up);
    // move back to the right, scaled by the correct position for this vertex
    here -= static_cast<D3DXVECTOR3>(Left) * 2 * (float)x / (float)x_max;
    // move back downwards, scaled by the correct position for this vertex
    here -= static_cast<D3DXVECTOR3>(Up)  * 2 * (float)y / (float)y_max;
    
    // we track a "total" normal whereas the edges will have blended normals
    D3DXVECTOR3 total_normal;
    total_normal = normal;
    // special case the edges
    if( 0 == y )
        total_normal += static_cast<D3DXVECTOR3>(Up);
    else if ( y_max == y )
        total_normal -= static_cast<D3DXVECTOR3>(Up);
    if( 0 == x )
        total_normal += static_cast<D3DXVECTOR3>(Left);
    else if ( x_max == x )
        total_normal -= static_cast<D3DXVECTOR3>(Left);
    
    // now normalize the new normal
    D3DXVec3Normalize(&total_normal, &total_normal);

    // set the vertex position
    pVertex->x = here.x;
    pVertex->y = here.y;
    pVertex->z = here.z;

    // set the vertex normal
    pVertex->x0 = total_normal.x;
    pVertex->y0 = total_normal.y;
    pVertex->z0 = total_normal.z;

    // diffuse color
    pVertex->diffuse = 0xff000000 | m_dwColor;
}




//-----------------------------------------------------------------------------
// Name: CreateCube
// Desc: create a Shells & Fins cube fuzzy mesh
//-----------------------------------------------------------------------------
CFuzzyMesh* CFuzzyMesh::CreateCube( UINT nWidthSlices, UINT nHeightSlices, DWORD dwColor, FLOAT fTextureScale )
{
    return new CFuzzyCubeMesh( nWidthSlices, nHeightSlices, dwColor, fTextureScale);
}
