//-----------------------------------------------------------------------------
// File: MotionBlur.cpp
//
// Desc: Sample code showing how to use vertex shader to create a motion blur
//       effect in D3D.
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

    LPD3DXMESH          m_pMesh;
    LPD3DXEFFECT        m_pEffect;     // Effect containing the vertex shaders
    D3DXMATRIX          m_matWorld_Prev1;
    D3DXMATRIX          m_matWorld_Prev2;
    D3DXMATRIX          m_matWorld_Current1;
    D3DXMATRIX          m_matWorld_Current2;
    D3DXMATRIX          m_matArcballWorld;
    D3DXMATRIX          m_matView;
    D3DXMATRIX          m_matProjection;
    FLOAT               m_fTrailLength;
    FLOAT               m_fRotateAngle1;
    FLOAT               m_fRotateAngle2;
    BOOL                m_bFirstObjInFront;

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
    m_strWindowTitle          = _T("MotionBlur");
    m_d3dEnumeration.AppUsesDepthBuffer = TRUE;
    m_bShowCursorWhenFullscreen      = TRUE;

    m_pFont                   = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pFontSmall              = new CD3DFont( _T("Arial"),  9, D3DFONT_BOLD );

    m_pEffect                 = NULL;
    m_pMesh                   = NULL;

    m_bShowHelp               = FALSE;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    m_fRotateAngle1 += 2.0f * m_fElapsedTime;
    m_fRotateAngle2 += 2.0f * m_fElapsedTime;

    m_matWorld_Prev1 = m_matWorld_Current1;
    m_matWorld_Prev2 = m_matWorld_Current2;

    D3DXVECTOR3 pos1( 14 * cosf(m_fRotateAngle1), 0.0f, 7 * sinf(m_fRotateAngle1) );
    D3DXVECTOR3 pos2( 14 * cosf(m_fRotateAngle2), 0.0f, 7 * sinf(m_fRotateAngle2) );

    D3DXMatrixTranslation( &m_matWorld_Current1, pos1.x, pos1.y, pos1.z );
    D3DXMatrixTranslation( &m_matWorld_Current2, pos2.x, pos2.y, pos2.z );

    // Transform positions into camera space to see which is in front
    D3DXMATRIX matWorldView;
    matWorldView = m_matWorld_Current1 * m_matArcballWorld * m_matView;
    D3DXVec3TransformCoord( &pos1, &pos1, &matWorldView);

    matWorldView = m_matWorld_Current2 * m_matArcballWorld * m_matView;
    D3DXVec3TransformCoord( &pos2, &pos2, &matWorldView);

    m_bFirstObjInFront = ( pos1.z < pos2.z );

    D3DXMATRIX matViewT;

    D3DXMatrixTranspose( &m_matWorld_Current1, &m_matWorld_Current1 );
    D3DXMatrixTranspose( &m_matWorld_Current2, &m_matWorld_Current2 );
    D3DXMatrixTranspose( &matViewT, &m_matView );

    // Update rotation matrix from ArcBall
    D3DXMatrixTranspose( &m_matArcballWorld, m_ArcBall.GetRotationMatrix() );
    m_pd3dDevice->SetVertexShaderConstantF( 8, (float*)&m_matArcballWorld, 4 );

    m_pd3dDevice->SetVertexShaderConstantF( 12, (float*)&matViewT,       4 );
    m_pd3dDevice->SetVertexShaderConstantF( 16, (float*)&m_matProjection, 4 );

    D3DXVECTOR4 vecMisc = D3DXVECTOR4( m_fTrailLength, 0.0f, 1.0f, 0.0f );
    m_pd3dDevice->SetVertexShaderConstantF( 20, (float*)&vecMisc, 1 );

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
                         D3DCOLOR_RGBA(0,0,255,0), 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        UINT numPasses;
        UINT iPass;

        // draw first sphere mesh
        if( m_bFirstObjInFront )
        {
            m_pd3dDevice->SetVertexShaderConstantF( 0, (float*)&m_matWorld_Prev2,    4 );
            m_pd3dDevice->SetVertexShaderConstantF( 4, (float*)&m_matWorld_Current2, 4 );
        }
        else
        {
            m_pd3dDevice->SetVertexShaderConstantF( 0, (float*)&m_matWorld_Prev1,    4 );
            m_pd3dDevice->SetVertexShaderConstantF( 4, (float*)&m_matWorld_Current1, 4 );
        }
        m_pEffect->Begin( &numPasses, 0 );
        for( iPass = 0; iPass < numPasses; iPass ++ )
        {
            m_pEffect->Pass( iPass );
            m_pMesh->DrawSubset( 0 );
        }
        m_pEffect->End();

        // draw second sphere mesh
        if( m_bFirstObjInFront )
        {
            m_pd3dDevice->SetVertexShaderConstantF( 0, (float*)&m_matWorld_Prev1,    4 );
            m_pd3dDevice->SetVertexShaderConstantF( 4, (float*)&m_matWorld_Current1, 4 );
        }
        else
        {
            m_pd3dDevice->SetVertexShaderConstantF( 0, (float*)&m_matWorld_Prev2,    4 );
            m_pd3dDevice->SetVertexShaderConstantF( 4, (float*)&m_matWorld_Current2, 4 );
        }
        m_pEffect->Begin( &numPasses, 0 );
        for( iPass = 0; iPass < numPasses; iPass ++ )
        {
            m_pEffect->Pass( iPass );
            m_pMesh->DrawSubset( 0 );
        }
        m_pEffect->End();

        // Output statistics
        m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );

        // Toggle help text
        if( m_bShowHelp )
        {
            m_pFontSmall->DrawText( 2, 42, D3DCOLOR_ARGB(255,0,255,255), 
                                    TEXT("Use mouse to rotate the scene") );
            m_pFontSmall->DrawText( 2, 62, D3DCOLOR_ARGB(255,0,255,255), 
                                    TEXT("Increase Trail Length") );
            m_pFontSmall->DrawText( 150, 62, D3DCOLOR_ARGB(255,0,255,255), 
                                    TEXT("Up Arrow Key") );
            m_pFontSmall->DrawText( 2, 80, D3DCOLOR_ARGB(255,0,255,255), 
                                    TEXT("Decrease Trail Length") );
            m_pFontSmall->DrawText( 150, 80, D3DCOLOR_ARGB(255,0,255,255), 
                                    TEXT("Down Arrow Key") );
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
    // World matrix for previous frame
    // NOTE: We need one-time initialization for previous frame (for 1st frame)

    D3DXMatrixTranslation( &m_matWorld_Current1, 0.0f, 0.0f, 7.0f );
    D3DXMatrixTranspose( &m_matWorld_Current1, &m_matWorld_Current1 );
    D3DXMatrixTranslation( &m_matWorld_Current2, -14.0f, 0.0f, 0.0f );
    D3DXMatrixTranspose( &m_matWorld_Current2, &m_matWorld_Current2 );

    // VIEW matrix for the entire scene
    // NOTE: VIEW matrix is fixed
    D3DXVECTOR3 vFromPt( 0.0f, 0.0f, -26.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &m_matView, &vFromPt, &vLookatPt, &vUpVec );

    m_fRotateAngle1 = D3DX_PI / 2.0f;
    m_fRotateAngle2 = D3DX_PI;

    m_fTrailLength = 3.0f;

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

    // Load sphere mesh
    D3DXCreateSphere(m_pd3dDevice, 1.2f, 36, 36, &m_pMesh, NULL );

    // Load effect file
    if( FAILED( hr = DXUtil_FindMediaFileCch( strPath, MAX_PATH, 
                                              TEXT("MotionBlur.fx") ) ) )
    {
        return hr;
    }
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

    // Device should support at least VS.1.1
    if( dwBehavior & D3DCREATE_SOFTWARE_VERTEXPROCESSING ||
        pCaps->VertexShaderVersion >= D3DVS_VERSION(1, 1) )
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

    SAFE_RELEASE( m_pEffect );
    SAFE_RELEASE( m_pMesh );

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

    if( m_pEffect != NULL )
        m_pEffect->OnResetDevice();

    m_ArcBall.SetWindow( m_d3dsdBackBuffer.Width, m_d3dsdBackBuffer.Height );

    // PROJECTION matrix for the entire scene
    // NOTE: The projection is fixed
    FLOAT fAspect = ((FLOAT)m_d3dsdBackBuffer.Width) / m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &m_matProjection,
                                D3DX_PI / 4, fAspect, 1.0f, 60.0f );
    D3DXMatrixTranspose( &m_matProjection, &m_matProjection );

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
        case IDM_INCREASETRAILLENGTH:
            if( m_fTrailLength < 8.0f )
                m_fTrailLength += 0.3f;
            break;
        case IDM_DECREASETRAILLENGTH:
            if( m_fTrailLength > 2.0f )
                m_fTrailLength -= 0.3f;
            break;
        case IDM_TOGGLEHELP:
            m_bShowHelp = !m_bShowHelp;
            break;
        }
    }

    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}
