//-----------------------------------------------------------------------------
// File: ClipVolume.cpp
//
// Desc: Sample code showing how to use a vertex shader and a pixel shader to do
//       a non-planar clipping effect in D3D.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <Windows.h>
#include <commctrl.h>
#include <D3DX9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFont.h"
#include "D3DUtil.h"
#include "resource.h"




//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
    CD3DFont*          m_pFont;        // Font for drawing text
    CD3DFont*          m_pFontSmall;   // Font for drawing text
    CD3DArcBall        m_ArcBall;      // Mouse rotation utility

    LPD3DXMESH         m_pTeapotMesh;  // Teapot mesh
    LPD3DXMESH         m_pSphereMesh;  // Sphere mesh
    LPD3DXEFFECT       m_pEffect;      // Effect containing the shaders

    D3DXMATRIX         m_matTeapotWorld;
    D3DXMATRIX         m_matSphereWorld;
    D3DXMATRIX         m_matArcballWorld;
    D3DXMATRIX         m_matProjection;

    FLOAT              m_fSphereMove;      // Sphere per-second movement delta
    D3DXVECTOR4        m_vecSphereCenter;  // Center of sphere

    BOOL               m_bShowHelp;

protected:
    HRESULT ConfirmDevice( D3DCAPS9*, DWORD, D3DFORMAT, D3DFORMAT );
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT Render();
    HRESULT FrameMove();
    HRESULT FinalCleanup();

public:
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
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
    m_strWindowTitle  = _T("ClipVolume");
    m_d3dEnumeration.AppUsesDepthBuffer = TRUE;
    m_bShowCursorWhenFullscreen      = TRUE;

    m_pFont           = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pFontSmall      = new CD3DFont( _T("Arial"),  9, D3DFONT_BOLD );

    m_pTeapotMesh     = NULL;
    m_pSphereMesh     = NULL;
    m_pEffect         = NULL;

    m_bShowHelp       = FALSE;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    // Update translation matrix for sphere
    if( m_vecSphereCenter.x > 2.0f )
        m_fSphereMove = -0.6f;
    else if( m_vecSphereCenter.x < -2.0f )
        m_fSphereMove = 0.6f;
    m_vecSphereCenter.x += m_fSphereMove * m_fElapsedTime;
    D3DXMatrixTranslation( &m_matSphereWorld, m_vecSphereCenter.x,
                                              m_vecSphereCenter.y,
                                              m_vecSphereCenter.z );
    D3DXMatrixTranspose( &m_matSphereWorld, &m_matSphereWorld );

    // Update rotation matrix from ArcBall
    D3DXMatrixTranspose( &m_matArcballWorld, m_ArcBall.GetRotationMatrix() );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Render the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_RGBA(0,0,0,0), 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        UINT numPasses;
        UINT iPass;

        // Draw teapot mesh using teapot effect
        m_pd3dDevice->SetVertexShaderConstantF(  0, m_matArcballWorld, 4 );
        m_pd3dDevice->SetVertexShaderConstantF(  4, m_matTeapotWorld,  4 );
        m_pd3dDevice->SetVertexShaderConstantF(  8, m_matProjection,   4 );
        m_pd3dDevice->SetVertexShaderConstantF( 12, m_vecSphereCenter, 1 );
        D3DXHANDLE hTechniqueTeapot = m_pEffect->GetTechniqueByName( "Teapot" );
        m_pEffect->SetTechnique( hTechniqueTeapot );
        m_pEffect->Begin( &numPasses, 0 );
        for( iPass = 0; iPass < numPasses; iPass ++ )
        {
            m_pEffect->Pass( iPass );
            m_pTeapotMesh->DrawSubset( 0 );
        }
        m_pEffect->End();

        // Draw sphere mesh using sphere effect
        m_pd3dDevice->SetVertexShaderConstantF( 4, m_matSphereWorld, 4 );
        D3DXHANDLE hTechniqueSphere = m_pEffect->GetTechniqueByName( "Sphere" );
        m_pEffect->SetTechnique( hTechniqueSphere );
        m_pEffect->Begin( &numPasses, 0 );
        for( iPass = 0; iPass < numPasses; iPass ++ )
        {
            m_pEffect->Pass( iPass );
            m_pSphereMesh->DrawSubset( 0 );
        }
        m_pEffect->End();

        // Output statistics
        m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );

        // Toggle help text
        if( m_bShowHelp )
        {
            m_pFontSmall->DrawText( 2, 42, D3DCOLOR_ARGB(255,0,255,255), 
                                    TEXT("Use mouse to rotate the teapot") );
        }
        else
        {
            m_pFontSmall->DrawText( 2, 42, D3DCOLOR_ARGB(255,255,0,255), 
                                    TEXT("Press F1 for Help") );
        }

        // End the scene
        m_pd3dDevice->EndScene();
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
    // Translation matrix for teapot mesh
    // NOTE: This translation is fixed and will preceded by the ArcBall
    //       rotation that is calculated per-frame in FrameMove
    D3DXMatrixTranslation( &m_matTeapotWorld, 0.0f, 0.0f, 5.0f );
    D3DXMatrixTranspose( &m_matTeapotWorld, &m_matTeapotWorld );

    // Translation matrix for sphere mesh
    // NOTE: This is built per-frame in FrameMove

    // VIEW matrix for the entire scene
    // NOTE: This is fixed to an identity matrix

    // PROJECTION matrix for the entire scene
    // NOTE: The projection is based on the window dimensions
    //       and is built in RestoreDeviceObjects

    // Initial per-second movement delta for sphere
    m_fSphereMove = 0.6f;

    // Initial location of center of sphere
    // NOTE: .xyz = center of sphere
    //       .w   = radius of sphere
    m_vecSphereCenter = D3DXVECTOR4(0.0f, 0.0f, 5.0f, 1.0f);

    // Set cursor to indicate that user can move the object with the mouse
#ifdef _WIN64
    SetClassLongPtr( m_hWnd, GCLP_HCURSOR, (LONG_PTR)LoadCursor( NULL, IDC_SIZEALL ) );
#else
    SetClassLong( m_hWnd, GCL_HCURSOR, HandleToLong( LoadCursor( NULL, IDC_SIZEALL ) ) );
#endif

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: This creates all device-dependent managed objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;
    TCHAR strPath[MAX_PATH];

    // Initialize the font's internal textures
    m_pFont->InitDeviceObjects( m_pd3dDevice );
    m_pFontSmall->InitDeviceObjects( m_pd3dDevice );

    // Create teapot mesh and sphere mesh
    if( FAILED( hr = D3DXCreateTeapot( m_pd3dDevice, &m_pTeapotMesh, NULL ) ) )
        return hr;

    if( FAILED( hr = D3DXCreateSphere( m_pd3dDevice, 1.0f, 30, 30, &m_pSphereMesh, NULL ) ) )
        return hr;

    // Load effect
    if( FAILED( hr = DXUtil_FindMediaFileCch( strPath, MAX_PATH, TEXT("ClipVolume.fx") ) ) )
        return hr;
    if( FAILED( hr = D3DXCreateEffectFromFile( m_pd3dDevice, strPath, NULL, NULL, 
                                               0, NULL, &m_pEffect, NULL ) ) )
    {
        return hr;
    }

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
    // Need to support post-pixel processing (for alpha blending)
    if( FAILED( m_pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
        adapterFormat, D3DUSAGE_RENDERTARGET | D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
        D3DRTYPE_SURFACE, backBufferFormat ) ) )
    {
        return E_FAIL;
    }

    // Device should support at least both VS.1.1 and PS.1.1
    if( (pCaps->VertexShaderVersion >= D3DVS_VERSION(1, 1)) &&
        (pCaps->PixelShaderVersion  >= D3DPS_VERSION(1, 1)) )
    {
        return S_OK;
    }

    return E_FAIL;
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

    SAFE_RELEASE( m_pTeapotMesh );
    SAFE_RELEASE( m_pSphereMesh );
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
    SAFE_DELETE( m_pFont );
    SAFE_DELETE( m_pFontSmall );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Called when the device-dependent objects are about to be lost.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();
    m_pFontSmall->InvalidateDeviceObjects();

    if( m_pEffect != NULL )
        m_pEffect->OnLostDevice();

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
    m_pFontSmall->RestoreDeviceObjects();

    m_ArcBall.SetWindow( m_d3dsdBackBuffer.Width, m_d3dsdBackBuffer.Height );

    // Update projection matrix based on window dimensions
    FLOAT fAspect = ((FLOAT)m_d3dsdBackBuffer.Width) / m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &m_matProjection,
                                D3DX_PI / 4, fAspect, 1.0f, 60.0f );
    D3DXMatrixTranspose( &m_matProjection, &m_matProjection );

    if( m_pEffect != NULL )
        m_pEffect->OnResetDevice();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Message proc function to handle user input
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam )
{
    // Pass mouse messages to the ArcBall so it can build internal matrices
    m_ArcBall.HandleMouseMessages( hWnd, uMsg, wParam, lParam );

    if( uMsg == WM_COMMAND)
    {
        switch( LOWORD(wParam) )
        {
        case IDM_TOGGLEHELP:
            m_bShowHelp = !m_bShowHelp;
            break;
        }
    }

    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}
