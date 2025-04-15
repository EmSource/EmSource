//-----------------------------------------------------------------------------
// File: Textures.cpp
//
// Desc: DirectShow sample code - uses the Direct3D Textures Tutorial05 as 
//       a base to create an application that uses DirectShow to draw a video 
//       on a DirectX 9.0 Texture surface.

// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

#include "textures.h"
#include "resource.h"
#include "d3dfont.h"
#include <math.h>
#include <streams.h>


#pragma warning( disable : 4100 4238)

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL; // Buffer to hold vertices
LPDIRECT3DTEXTURE9      g_pTexture   = NULL; // Our texture
HINSTANCE               hInstance    = 0;
HWND                    g_hWnd       = 0;
bool                    g_bDeviceLost = false;

CD3DFont*   g_pFont = NULL;
const int nGrid = 50;

BYTE bkRed = 50;
BYTE bkGrn = 100;
BYTE bkBlu = 150;
DWORD g_StartTime = 0L;

extern TCHAR* g_pachRenderMethod;
extern CComPtr<IBaseFilter> g_pRenderer;    // our custom renderer

// A structure for our custom vertex type. We added texture coordinates.
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // The position
    D3DCOLOR    color;    // The color
    FLOAT       tu, tv;   // The texture coordinates
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define CLASSNAME   TEXT("DirectShow Texture3D9 Sample")

#define TIMER_ID    100
#define TIMER_RATE  20      // milliseconds

// Function prototypes
void AddAboutMenuItem(HWND hWnd);
LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    HRESULT hr;

    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Get the current desktop display mode, so we can set up a back
    // buffer of the same format
    D3DDISPLAYMODE d3ddm;
    if ( FAILED( hr = g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
    {
        Msg(TEXT("Could not read adapter display mode!  hr=0x%x"), hr);
        return hr;
    }

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed               = TRUE;
    d3dpp.SwapEffect             = D3DSWAPEFFECT_COPY;
    d3dpp.BackBufferFormat       = d3ddm.Format;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the D3DDevice
    hr = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                               D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                               &d3dpp, &g_pd3dDevice );                                     
    if (FAILED(hr))                                      
    {
        Msg(TEXT("Could not create the D3D9 device!  hr=0x%x\r\n\r\n")
            TEXT("This sample is attempting to create a buffer that might not\r\n")
            TEXT("be supported by your video card in its current mode.\r\n\r\n")
            TEXT("You may want to reduce your screen resolution or bit depth\r\n")
            TEXT("and try to run this sample again."), hr);
        return hr;
    }

    hr = g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP );
    hr = g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP );

    // Add filtering
    hr = g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    hr = g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    // set maximum ambient light
    hr = g_pd3dDevice->SetRenderState(D3DRS_AMBIENT,RGB(255,255,255));

    // Turn off culling
    hr = g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting
    hr = g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    // Turn on the zbuffer
    hr = g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Set texture states
    hr = g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    hr = g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    hr = g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    hr = g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

    g_pFont = new CD3DFont(TEXT("Trebuchet MS"), 10);
    if( g_pFont )
    {
        hr = g_pFont->InitDeviceObjects( g_pd3dDevice );
        if( FAILED(hr))
        {
            delete g_pFont;
            g_pFont = NULL;
        }
        else
        {
            hr = g_pFont->RestoreDeviceObjects();
            if( FAILED(hr))
            {
                delete g_pFont;
                g_pFont = NULL;
            }
        }
    }

    return hr;
}

//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Create the textures and vertex buffers
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
    HRESULT hr;

    // Create the vertex buffer.
    if( FAILED( hr = g_pd3dDevice->CreateVertexBuffer( nGrid*2*sizeof(CUSTOMVERTEX),
                                      0, D3DFVF_CUSTOMVERTEX,
                                      D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        Msg(TEXT("Could not create a vertex buffer!  hr=0x%x"), hr);
        return E_FAIL;
    }

    // Fill the vertex buffer. We are setting the tu and tv texture
    // coordinates, which range from 0.0 to 1.0
    CUSTOMVERTEX* pVertices;
    if ( FAILED( hr = g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
    {
        Msg(TEXT("Could not lock the vertex buffer!  hr=0x%x"), hr);
        return E_FAIL;
    }

    for( DWORD i=0; i<nGrid; i++ )
    {
        FLOAT theta = (2*D3DX_PI*i)/(nGrid-1) + (FLOAT)(D3DX_PI/2.f);

        pVertices[2*i+0].position = D3DXVECTOR3( sinf(theta),-1.0f, cosf(theta) );
        pVertices[2*i+0].color    = 0xffffffff;
        pVertices[2*i+0].tu       = ((FLOAT)i)/((FLOAT)nGrid-1.f);
        pVertices[2*i+0].tv       = 1.0f; 

        pVertices[2*i+1].position = D3DXVECTOR3( sinf(theta), 1.0f, cosf(theta) );
        pVertices[2*i+1].color    = 0xffffffff;
        pVertices[2*i+1].tu       = ((FLOAT)i)/((FLOAT)nGrid-1.f);
        pVertices[2*i+1].tv       = 0.0f;
    }

    g_pVB->Unlock();

    // DShow: Set up filter graph with our custom renderer.
    if( FAILED( InitDShowTextureRenderer() ) )
        return E_FAIL;

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: UpgradeGeometry()
//-----------------------------------------------------------------------------
HRESULT UpgradeGeometry( LONG lActualW, LONG lTextureW,
                         LONG lActualH, LONG lTextureH )
{
    HRESULT hr = S_OK;
    if( 0 == lTextureW || 0 == lTextureH )
    {
        return E_INVALIDARG;
    }
    FLOAT tuW = (FLOAT)lActualW / (FLOAT)lTextureW;
    FLOAT tvH = (FLOAT)lActualH / (FLOAT)lTextureH;

    // Fill the vertex buffer. We are setting the tu and tv texture
    // coordinates, which range from 0.0 to 1.0
    CUSTOMVERTEX* pVertices;
    if ( FAILED( hr = g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
    {
        Msg(TEXT("Could not lock the vertex buffer!  hr=0x%x"), hr);
        return E_FAIL;
    }

    for( DWORD i=0; i<nGrid; i++ )
    {
        FLOAT theta = (2*D3DX_PI*i)/(nGrid-1) + (FLOAT)(D3DX_PI/2.f);

        pVertices[2*i+0].tu       = tuW * ((FLOAT)i)/((FLOAT)nGrid-1.f);
        pVertices[2*i+0].tv       = tvH; 

        pVertices[2*i+1].tu       = tuW * ((FLOAT)i)/((FLOAT)nGrid-1.f);
        pVertices[2*i+1].tv       = 0.0f;
    }

    g_pVB->Unlock();
    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    CleanupDShow();

    if( g_pTexture != NULL )   
        g_pTexture->Release();
        
    if( g_pVB != NULL )
        g_pVB->Release();
        
    if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();
        
    if( g_pD3D != NULL )
        g_pD3D->Release();

    if( g_pFont )
    {
        delete g_pFont;
        g_pFont = NULL;
    }
}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
    HRESULT hr;

    if( 0 == g_StartTime )
    {
        srand( timeGetTime());
        g_StartTime = (DWORD)(timeGetTime()/2000.0f);
    }

    // For our world matrix, we will just leave it as the identity
    D3DXMATRIX matWorld;
    D3DXMatrixIdentity( &matWorld );
    D3DXMatrixRotationX( &matWorld, (FLOAT)(timeGetTime()/2000.0f - g_StartTime + D3DX_PI/2.0));

    hr = g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
    if (FAILED(hr))                                      
    {
        Msg(TEXT("Could not set D3DTS_WORLD transform!  hr=0x%x"), hr);
    }

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to look at, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 3.0f,-3.0f ),
                                  &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                                  &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
    hr = g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
    if (FAILED(hr))                                      
    {
        Msg(TEXT("Could not set D3DTS_VIEW transform!  hr=0x%x"), hr);
    }

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );

    hr = g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
    if (FAILED(hr))                                      
    {
        Msg(TEXT("Could not set D3DTS_PROJECTION transform!  hr=0x%x"), hr);
    }
}

//-----------------------------------------------------------------------------
// Name: CalculateShades()
// Desc: Calculates shades of vertices depending on current time and background color
//-----------------------------------------------------------------------------
void CalculateShades()
{
    float cost = (float)cos(timeGetTime()/2000.0f - g_StartTime);

    static BYTE btRed1, btGrn1, btBlu1;
    static BYTE btRed2, btGrn2, btBlu2;

    CUSTOMVERTEX* pVertices = 0;
    if ( SUCCEEDED( g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
    {
        {
            btRed1 = (BYTE)(((0xFF-bkRed)*cost + (0xFF+bkRed))/2);
            btGrn1 = (BYTE)(((0xFF-bkGrn)*cost + (0xFF+bkGrn))/2);
            btBlu1 = (BYTE)(((0xFF-bkBlu)*cost + (0xFF+bkBlu))/2);
        }

        {
            btRed2 = (BYTE)(((bkRed-0xFF)*cost + (0xFF+bkRed))/2);
            btGrn2 = (BYTE)(((bkGrn-0xFF)*cost + (0xFF+bkGrn))/2);
            btBlu2 = (BYTE)(((bkBlu-0xFF)*cost + (0xFF+bkBlu))/2);
        }

        for( DWORD i=0; i<nGrid; i++ )
        {
            pVertices[2*i+0].color    = D3DCOLOR_XRGB(btRed1, btGrn1, btBlu1);
            pVertices[2*i+1].color    = D3DCOLOR_XRGB(btRed2, btGrn2, btBlu2);
        }
        g_pVB->Unlock();
    }
}

//-----------------------------------------------------------------------------
// Name: DrawText()
// Desc: Draws help text over the scene
//-----------------------------------------------------------------------------
VOID DrawText()
{
    HRESULT hr = S_OK;
    if( !g_pFont )
        return;

    TCHAR achMsg[MAX_PATH];
    int nFPS = 0;
    CComPtr<IQualProp> pQp;

    if( g_pRenderer )
    {
        hr = g_pRenderer->QueryInterface( IID_IQualProp, (void**)&(pQp.p));
        if( SUCCEEDED(hr))
        {
            hr = pQp->get_AvgFrameRate( &nFPS );
            if( SUCCEEDED(hr))
            {
                _stprintf( achMsg, TEXT("FPS = %5.3f"), (float)nFPS / 100.f);
            }
            g_pFont->DrawText(5, 20, D3DCOLOR_ARGB(0xCC,0xFF,0xFF,0x00), achMsg );
        }
    }

    if( g_pachRenderMethod )
    {
        _stprintf( achMsg, TEXT("Rendering method: %s"), g_pachRenderMethod);
        g_pFont->DrawText(5, 40, D3DCOLOR_ARGB(0xCC,0xFF,0xFF,0x00), achMsg );
    }

    _stprintf( achMsg, TEXT("[Space]: change background color"));
    g_pFont->DrawText(5, 60, D3DCOLOR_ARGB(0xCC,0xFF,0xFF,0x00), achMsg );
    _stprintf( achMsg, TEXT("[Enter]: set background color to black"));
    g_pFont->DrawText(5, 80, D3DCOLOR_ARGB(0xCC,0xFF,0xFF,0x00), achMsg );

}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    HRESULT hr = S_OK;

    if (!g_pd3dDevice)
        return;

    // Handle the loss of the Direct3D surface (for example, by switching
    // to a full-screen command prompt and back again)
    if( g_bDeviceLost )
    {
        // Test the cooperative level to see if it's okay to render
        if( FAILED( hr = g_pd3dDevice->TestCooperativeLevel() ) )
        {
            // If the device was lost, do not render until we get it back
            if( D3DERR_DEVICELOST == hr )
                return;

            // Check if the device needs to be reset.
            if( D3DERR_DEVICENOTRESET == hr )
            {
                // Reset the D3D environment
                Cleanup();
                hr = InitD3D(g_hWnd);
                hr = InitGeometry();
            }

            return;
        }

        // TestCooperativeLevel() succeeded, so we have regained the device
        g_bDeviceLost = false;
    }


    // Clear the backbuffer and the zbuffer
    hr = g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                              D3DCOLOR_XRGB(bkRed,bkGrn,bkBlu), 1.0f, 0 );

    // Begin the scene
    hr = g_pd3dDevice->BeginScene();

    // Setup the world, view, and projection matrices
    SetupMatrices();

    CalculateShades();

    // Setup our texture. Using textures introduces the texture stage states,
    // which govern how textures get blended together (in the case of multiple
    // textures) and lighting information. In this case, we are modulating
    // (blending) our texture with the diffuse color of the vertices.
    hr = g_pd3dDevice->SetTexture( 0, g_pTexture );

    // Render the vertex buffer contents
    hr = g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
    hr = g_pd3dDevice->SetVertexShader( NULL );
    hr = g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
    hr = g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2*nGrid-2 );

    DrawText();
    // End the scene
    hr = g_pd3dDevice->EndScene();

    // Present the backbuffer contents to the display
    hr = g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

    // If the Present call failed because we lost the Direct3D surface,
    // set a state variable for the next render pass, where we will attempt
    // to recover the lost surface.
    if( D3DERR_DEVICELOST == hr )
        g_bDeviceLost = true;

    // Check to see if we need to restart the movie
    CheckMovieStatus();
}


//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

        case WM_TIMER:
        case WM_PAINT:
            Render();       // Update the main window when needed
            break;

        // If the display mode changes, tear down the graph and rebuild it.
        // The resolution may have changed or we may have lost surfaces due to
        // a transition from another application's full screen exclusive mode.
        case WM_DISPLAYCHANGE:
            Cleanup();
            InitD3D(hWnd);
            InitGeometry();
            break;

        case WM_CHAR:
        {
            // Close the app if the ESC key is pressed
            if (wParam == VK_ESCAPE)
            {
                PostMessage(hWnd, WM_CLOSE, 0, 0);
            }
            // else maybe background color change by space
            else if(wParam == VK_SPACE)
            {
                bkRed = (BYTE)(rand()%0xFF);
                bkGrn = (BYTE)(rand()%0xFF);
                bkBlu = (BYTE)(rand()%0xFF);
            }
            // else if 'enter' return to black
            else if(wParam == VK_RETURN )
            {
                bkRed = bkGrn = bkBlu = 0x0;
            }
        }
        break;

        case WM_SYSCOMMAND:
        {
            switch (wParam)
            {
                case ID_HELP_ABOUT:
                    // Create a modeless dialog to prevent rendering interruptions
                    CreateDialog(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, 
                                (DLGPROC) AboutDlgProc);
                    return 0;
            }
        }
        break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


//-----------------------------------------------------------------------------
// Name: AboutDlgProc()
// Desc: Message handler for About box
//-----------------------------------------------------------------------------

LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            if (wParam == IDOK)
            {
                EndDialog(hWnd, TRUE);
                return TRUE;
            }
            break;
    }
    return FALSE;
}


//-----------------------------------------------------------------------------
// Name: AddAboutMenuItem()
// Desc: Adds a menu item to the end of the app's system menu
//-----------------------------------------------------------------------------
void AddAboutMenuItem(HWND hWnd)
{
    // Add About box menu item
    HMENU hwndMain = GetSystemMenu(hWnd, FALSE);

    // Add separator
    BOOL rc = AppendMenu(hwndMain, MF_SEPARATOR, 0, NULL);

    // Add menu item
    rc = AppendMenu(hwndMain, MF_STRING | MF_ENABLED, 
                    ID_HELP_ABOUT, 
                    TEXT("About Texture3D9...\0"));
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpCmdLine, INT nCmdShow)
{
    UINT uTimerID=0;

    // Initialize COM
    CoInitialize (NULL);

    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), 
                      LoadIcon(hInst, MAKEINTRESOURCE(IDI_TEXTURES)), 
                      NULL, NULL, NULL,
                      CLASSNAME, NULL };
    RegisterClassEx( &wc );
    hInstance = hInst;

    // Create the application's window
    g_hWnd = CreateWindow( CLASSNAME, TEXT("DirectShow Texture3D9 Sample"),
                           WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                           GetDesktopWindow(), NULL, wc.hInstance, NULL );

    // Add a menu item to the app's system menu
    AddAboutMenuItem(g_hWnd);

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( g_hWnd ) ) )
    {
        // Create the scene geometry
        if( SUCCEEDED( InitGeometry() ) )
        {
            //
            // Set a timer to queue render operations
            //
            uTimerID = (UINT) SetTimer(g_hWnd, TIMER_ID, TIMER_RATE, NULL);

            // Show the window
            ShowWindow( g_hWnd, SW_SHOWDEFAULT );
            UpdateWindow( g_hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );

            // Main message loop
            while( msg.message!=WM_QUIT )
            {
                if(GetMessage( &msg, NULL, 0, 0))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }
    }

    // Stop the rendering timer
    KillTimer(g_hWnd, TIMER_ID);

    // Clean up everything and exit the app
    Cleanup();
    UnregisterClass( CLASSNAME, wc.hInstance );
    CoUninitialize();

    return 0L;
}

