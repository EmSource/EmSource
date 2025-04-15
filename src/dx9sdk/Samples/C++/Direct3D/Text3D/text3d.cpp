//-----------------------------------------------------------------------------
// File: Text3D.cpp
//
// Desc: Example code showing how to do text in a Direct3D scene.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <Windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <math.h>
#include <tchar.h>
#include <stdio.h>
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
    CD3DFont*     m_pFont;
    CD3DFont*     m_pStatsFont;
    LPD3DXMESH    m_pMesh3DText;
    LPD3DXFONT    m_pd3dxFont;

    TCHAR         m_strFont[LF_FACESIZE];
    DWORD         m_dwFontSize;

    D3DXMATRIXA16    m_matObj1;
    D3DXMATRIXA16    m_matObj2;

protected:
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT Render();
    HRESULT FrameMove();
    HRESULT FinalCleanup();
    HRESULT CreateD3DXTextMesh( LPD3DXMESH* ppMesh, TCHAR* pstrFont, DWORD dwSize );
    HRESULT CreateD3DXFont( LPD3DXFONT* ppd3dxFont, TCHAR* pstrFont, DWORD dwSize );

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
    m_strWindowTitle    = _T("Text3D: Text in a 3D scene");
    m_d3dEnumeration.AppUsesDepthBuffer   = TRUE;
    m_pMesh3DText       = NULL;
    m_pd3dxFont         = NULL;

    // Create fonts
    lstrcpy( m_strFont, _T("Arial") );
    m_dwFontSize  = 18;
    m_pFont       = NULL;
    m_pStatsFont  = NULL;
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    m_pFont = new CD3DFont( m_strFont, m_dwFontSize );
    if( m_pFont == NULL )
        return E_FAIL;

    m_pStatsFont = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    if( m_pStatsFont == NULL )
        return E_FAIL;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    // Setup five rotation matrices (for rotating text strings)
    D3DXVECTOR3 vAxis1(1.0f,2.0f,0.0f);
    D3DXVECTOR3 vAxis2(2.0f,1.0f,0.0f);
    D3DXMatrixRotationAxis( &m_matObj1, &vAxis1, m_fTime/2.0f  );
    D3DXMatrixRotationAxis( &m_matObj2, &vAxis2, m_fTime/2.0f  );

    // Add some translational values to the matrices
    m_matObj1._41 = 1.0f;   m_matObj1._42 = 6.0f;   m_matObj1._43 = 20.0f; 
    m_matObj2._41 = -4.0f;  m_matObj2._42 = -1.0f;  m_matObj2._43 = 0.0f; 

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
    D3DMATERIAL9 mtrl;

    // Clear the viewport
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L );

    // Begin the scene 
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        // Draw CD3DFont in 2D (red)
        m_pFont->DrawText( 60, 100, D3DCOLOR_ARGB(255,255,0,0), 
                           _T("CD3DFont::DrawText"), D3DFONT_FILTERED );

        // Draw CD3DFont scaled in 2D (cyan)
        m_pFont->DrawTextScaled( -1.0f, 0.8f, 0.5f, // position
                                 0.1f, 0.1f,         // scale
                                 D3DCOLOR_ARGB(255,0,255,255), 
                                 _T("CD3DFont::DrawTextScaled"), 
                                 D3DFONT_CENTERED_X|D3DFONT_FILTERED );

        // Draw CD3DFont in 3D (green)
        D3DUtil_InitMaterial( mtrl, 0.0f, 1.0f, 0.0f );
        m_pd3dDevice->SetMaterial( &mtrl );
        m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matObj1 );
        m_pFont->Render3DText( _T("CD3DFont::Render3DText"), 
                              D3DFONT_CENTERED_X|D3DFONT_CENTERED_Y|D3DFONT_TWOSIDED|D3DFONT_FILTERED );

        // Draw D3DXFont mesh in 3D (blue)
        if( m_pMesh3DText != NULL )
        {
            D3DUtil_InitMaterial( mtrl, 0.0f, 0.0f, 1.0f );
            m_pd3dDevice->SetMaterial( &mtrl );
            m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matObj2 );
            m_pMesh3DText->DrawSubset(0);
        }

        // Draw D3DXFont in 2D (purple)
        RECT rc;
        SetRect( &rc, 60, 200, 0, 0 );
        m_pd3dxFont->Begin();
        m_pd3dxFont->DrawText( _T("ID3DXFont::DrawText"), -1, &rc, 
            DT_SINGLELINE | DT_CALCRECT, 0 );
        m_pd3dxFont->DrawText( _T("ID3DXFont::DrawText"), -1, &rc, 
            DT_SINGLELINE, D3DCOLOR_ARGB(255, 255, 0, 255) );
        m_pd3dxFont->End();

        // Show frame rate
        m_pStatsFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pStatsFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );

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

    if( FAILED( hr = m_pFont->InitDeviceObjects( m_pd3dDevice ) ) )
        return hr;

    if( FAILED( hr = m_pStatsFont->InitDeviceObjects( m_pd3dDevice ) ) )
        return hr;

    SAFE_RELEASE( m_pd3dxFont );
    if( FAILED( hr = CreateD3DXFont( &m_pd3dxFont, m_strFont, m_dwFontSize ) ) )
        return hr;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateD3DXFont()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::CreateD3DXFont( LPD3DXFONT* ppd3dxFont, 
                                           TCHAR* pstrFont, DWORD dwSize )
{
    HRESULT hr;
    LPD3DXFONT pd3dxFontNew = NULL;
    HDC hDC;
    INT nHeight;
    HFONT hFont;

    hDC = GetDC( NULL );
    nHeight = -MulDiv( dwSize, GetDeviceCaps(hDC, LOGPIXELSY), 72 );
    ReleaseDC( NULL, hDC );
    hFont = CreateFont( nHeight, 0, 0, 0, FW_DONTCARE, false, false, false, 
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, pstrFont );
    if( hFont == NULL )
        return E_FAIL;
    hr = D3DXCreateFont( m_pd3dDevice, hFont, &pd3dxFontNew );
    DeleteObject( hFont );

    if( SUCCEEDED( hr ) )
        *ppd3dxFont = pd3dxFontNew;

    return hr;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    // Restore the fonts
    m_pFont->RestoreDeviceObjects();
    m_pStatsFont->RestoreDeviceObjects();
    m_pd3dxFont->OnResetDevice();

    // Restore the textures
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x80808080);
    D3DLIGHT9 light;
    D3DUtil_InitLight(light, D3DLIGHT_DIRECTIONAL, 10.0f, -10.0f, 10.0f);
    m_pd3dDevice->SetLight(0, &light );
    m_pd3dDevice->LightEnable(0, TRUE);

    // Set the transform matrices
    D3DXVECTOR3 vEyePt    = D3DXVECTOR3( 0.0f,-5.0f,-10.0f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f,  0.0f );
    D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f,  0.0f );
    D3DXMATRIXA16  matWorld, matView, matProj;

    D3DXMatrixIdentity( &matWorld );
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    FLOAT fAspect = m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, fAspect, 1.0f, 100.0f );

    m_pd3dDevice->SetTransform( D3DTS_WORLD,      &matWorld );
    m_pd3dDevice->SetTransform( D3DTS_VIEW,       &matView );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    SAFE_RELEASE( m_pMesh3DText );
    if( FAILED( CreateD3DXTextMesh( &m_pMesh3DText, m_strFont, m_dwFontSize ) ) )
        return E_FAIL;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateD3DXTextMesh()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::CreateD3DXTextMesh( LPD3DXMESH* ppMesh, 
                                               TCHAR* pstrFont, DWORD dwSize )
{
    HRESULT hr;
    LPD3DXMESH pMeshNew = NULL;
    HDC hdc = CreateCompatibleDC( NULL );
    HFONT hFont;
    HFONT hFontOld;
    LOGFONT lf;

    ZeroMemory(&lf, sizeof(lf));
    lf.lfHeight = dwSize;
    lf.lfStrikeOut = 1;
    lstrcpy(lf.lfFaceName, pstrFont);
    hFont = CreateFontIndirect(&lf);
    hFontOld = (HFONT)SelectObject(hdc, hFont); 
    hr = D3DXCreateText(m_pd3dDevice, hdc, _T("D3DXCreateText"), 
        0.001f, 0.4f, &pMeshNew, NULL, NULL);
    SelectObject(hdc, hFontOld);
    DeleteObject( hFont );
    DeleteDC( hdc );
    if( SUCCEEDED( hr ) )
        *ppMesh = pMeshNew;
    return hr;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();
    m_pStatsFont->InvalidateDeviceObjects();
    m_pd3dxFont->OnLostDevice();

    SAFE_RELEASE( m_pMesh3DText );
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
    m_pStatsFont->DeleteDeviceObjects();
    SAFE_RELEASE( m_pd3dxFont );

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
    SAFE_DELETE( m_pStatsFont );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Message proc function to handle key and menu input
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam )
{
    if( WM_COMMAND == uMsg )
    {
        switch( LOWORD(wParam) )
        {
            case IDM_FONT:
            {
                HDC hdc;
                LONG lHeight;
                hdc = GetDC( hWnd );
                lHeight = -MulDiv( m_dwFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72 );
                ReleaseDC( hWnd, hdc );
                hdc = NULL;

                LOGFONT lf;
                lstrcpy( lf.lfFaceName, m_strFont );
                lf.lfHeight = lHeight;

                CHOOSEFONT cf;
                ZeroMemory( &cf, sizeof(cf) );
                cf.lStructSize = sizeof(cf);
                cf.hwndOwner   = m_hWnd;
                cf.lpLogFont   = &lf;
                cf.Flags       = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | CF_TTONLY;
                
                if( ChooseFont( &cf ) )
                {
                    CD3DFont* pFontNew = NULL;
                    LPD3DXMESH pMesh3DTextNew = NULL;
                    LPD3DXFONT pd3dxFontNew = NULL;
                    TCHAR* pstrFontNameNew = lf.lfFaceName;
                    DWORD dwFontSizeNew = cf.iPointSize / 10;
                    bool bSuccess = false;

                    pFontNew = new CD3DFont( pstrFontNameNew, dwFontSizeNew );
                    if( NULL != pFontNew )
                    {
                        if( SUCCEEDED( pFontNew->InitDeviceObjects( m_pd3dDevice ) ) )
                        {
                            if( SUCCEEDED( pFontNew->RestoreDeviceObjects() ) )
                            {
                                if( SUCCEEDED( CreateD3DXTextMesh( &pMesh3DTextNew, pstrFontNameNew, dwFontSizeNew ) ) )
                                {
                                    if( SUCCEEDED( CreateD3DXFont( &pd3dxFontNew, pstrFontNameNew, dwFontSizeNew ) ) )
                                    {
                                        bSuccess = true;

                                        SAFE_DELETE( m_pFont );
                                        m_pFont = pFontNew;
                                        pFontNew = NULL;

                                        SAFE_RELEASE( m_pMesh3DText );
                                        m_pMesh3DText = pMesh3DTextNew;
                                        pMesh3DTextNew = NULL;

                                        SAFE_RELEASE( m_pd3dxFont );
                                        m_pd3dxFont = pd3dxFontNew;
                                        pd3dxFontNew = NULL;
                                        
                                        lstrcpy( m_strFont, pstrFontNameNew );
                                        m_dwFontSize = dwFontSizeNew;
                                    }
                                }
                            }
                        }
                    }
                    SAFE_RELEASE( pMesh3DTextNew );
                    SAFE_RELEASE( pd3dxFontNew );
                    SAFE_DELETE( pFontNew );

                    if( !bSuccess )
                    {
                        MessageBox( m_hWnd, TEXT("Could not create that font."), 
                            m_strWindowTitle, MB_OK );
                    }
                }
                break;
            }
        }
    }

    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}



