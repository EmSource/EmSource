//-----------------------------------------------------------------------------
// File: Textures.cpp
//
// Desc: DirectShow sample code - uses the DirectShow Texture3D sample as 
//       a base to create an application that uses a custom renderer to draw
//       incoming live video (from a video capture device or camera)
//       onto a DirectX 9 Texture surface.

// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

#include "textures.h"
#include "resource.h"
#include "DShowTextures.h"
#include <d3dx9tex.h>

#pragma warning( disable : 4100 4238)

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
HINSTANCE               hInstance    = 0;
CCustomPresentation*    g_pPresentation = NULL;

// A structure for our custom vertex type. We added texture coordinates.
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // The position
    D3DXVECTOR3 n;        // Referenced as v3 in the vertex shader
    D3DCOLOR    color;    // The color
    FLOAT       tu, tv;   // The texture coordinates
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASSNAME   TEXT("DShow CaptureTex9 Sample")

#define TIMER_ID    100
#define TIMER_RATE  20      // milliseconds

// Function prototypes
void AddAboutMenuItem(HWND hWnd);
LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

const int   g_nWaves   = 1;     // number of waves on the "flag" -- we used flag-like 3D model
const int   g_nWaveN   = 100;   // number of vertices per wave (wave is a sin from 0 to 2 pi)
                                // we have g_nWaves * g_nWaveN for the top of the flag and
                                // the same number for the bottom, so we have (2 * g_nWaves * g_nWaveN )
                                // vertices for our 3D model

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
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpCmdLine, INT nCmdShow)
{
    HRESULT hr = S_OK;
    UINT uTimerID=0;

    // Initialize COM
    CoInitialize (NULL);

    hInstance = hInst;

    g_pPresentation = new CCustomPresentation();
    if( !g_pPresentation )
    {
        hr = E_OUTOFMEMORY;
        Msg( TEXT("Memory allocation error: failed to create CCustomPresentation object"), E_OUTOFMEMORY);
    }
    else
    {
        hr = g_pPresentation->Initialize();
    }

    if( SUCCEEDED(hr))
    {
        //
        // Set a timer to queue render operations
        //
        uTimerID = (UINT) SetTimer(g_pPresentation->m_hwnd, TIMER_ID, TIMER_RATE, NULL);

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

        // Stop the rendering timer
        KillTimer(g_pPresentation->m_hwnd, TIMER_ID);
    }

    // Clean up everything and exit the app
    if( g_pPresentation )
    {
        delete g_pPresentation;
        g_pPresentation = NULL;
    }

    CoUninitialize();
    return 0L;
}

//==========================================================================

// constructor
CCustomPresentation::CCustomPresentation()
: m_hwnd( NULL )
, m_dwROTReg( 0xfedcba98 )
, m_d3dcolorBackground( D3DCOLOR_XRGB(50, 100, 150) )
, m_dwStartTime( 0L)
, m_HAR( 1.f )
, m_VAR( 1.f )
, m_Width( 0)
, m_Height( 0)
{
    ZeroMemory( &m_TextureFormat, sizeof(D3DFORMAT));
}

// destructor
CCustomPresentation::~CCustomPresentation()
{
    UnregisterClass( CLASSNAME, hInstance );
    Cleanup();
}

//-----------------------------------------------------------------------------
// Name: Cleanup
// Desc: releases all allocated objects
//-----------------------------------------------------------------------------
void CCustomPresentation::Cleanup(void)
{
#ifdef REGISTER_FILTERGRAPH
    // Remove graph from Running Object Table
    RemoveFromROT();
#endif

    // Shut down the graph
    if( m_pMC )
    {
        m_pMC->Stop();
    }
}


HRESULT CCustomPresentation::Initialize()
{
    HRESULT hr = S_OK;

    srand( timeGetTime());
    m_dwStartTime = timeGetTime();

    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), 
                      LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEXTURES)), 
                      NULL, NULL, NULL,
                      CLASSNAME, NULL };
    RegisterClassEx( &wc );

    // Create the application's window
    m_hwnd = CreateWindow( CLASSNAME, CLASSNAME,
                           WS_OVERLAPPEDWINDOW, 100, 100, 500, 500,
                           GetDesktopWindow(), NULL, wc.hInstance, NULL );

    SetWindowLongPtr( m_hwnd, GWLP_USERDATA, (LONG_PTR)this);

    // Add About box menu item
    HMENU hwndMain = GetSystemMenu(m_hwnd, FALSE);

    // Add separator
    BOOL rc = AppendMenu(hwndMain, MF_SEPARATOR, 0, NULL);

    // Add menu item
    rc = AppendMenu(hwndMain, MF_STRING | MF_ENABLED, 
                    ID_HELP_ABOUT, 
                    TEXT("About DirectShow CaptureTex9...\0"));

    // first, initialize 3D environment
    hr = InitD3D();
    if( FAILED(hr))
    {
        return hr;
    }

    // second, initialize geometry
    hr = InitGeometry();
    if( FAILED(hr))
    {
        return hr;
    }

    // Show the main window.  The DirectShow components will
    // already be initialized.
    ShowWindow( m_hwnd, SW_SHOWDEFAULT );
    UpdateWindow( m_hwnd );

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
HRESULT CCustomPresentation::Render()
{
    HRESULT hr = S_OK;
    CAutoLock lock(&m_cs);

    try
    {
        // Clear the backbuffer and the zbuffer
        hr = m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                                  m_d3dcolorBackground, 1.0f, 0 );
        if( FAILED(hr))
        {
            return hr;
        }

        hr = CalculateVertices();
        if( FAILED(hr))
        {
            return hr;
        }

        // Begin the scene
        hr = m_pd3dDevice->BeginScene();
        if( FAILED(hr))
        {
            return hr;
        }

        // Setup our texture. Using textures introduces the texture stage states,
        // which govern how textures get blended together (in the case of multiple
        // textures) and lighting information. In this case, we are modulating
        // (blending) our texture with the diffuse color of the vertices.
        hr = m_pd3dDevice->SetTexture( 0, m_pTexture );
        if( FAILED(hr))
        {
            m_pd3dDevice->EndScene();
            return hr;
        }

        // Render the vertex buffer contents
        hr = m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
        if( FAILED(hr))
        {
            m_pd3dDevice->EndScene();
            return hr;
        }
        // we use FVF instead of pixel shader
        hr = m_pd3dDevice->SetVertexShader( NULL );
        if( FAILED(hr))
        {
            m_pd3dDevice->EndScene();
            return hr;
        }
        hr = m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
        if( FAILED(hr))
        {
            m_pd3dDevice->EndScene();
            return hr;
        }
        // draw flaf
        hr = m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 * g_nWaveN * g_nWaves -4 );
        if( FAILED(hr))
        {
            m_pd3dDevice->EndScene();
            return hr;
        }

        // End the scene
        m_pd3dDevice->EndScene();

        // Present the backbuffer contents to the display
        hr = m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
        if( FAILED(hr))
        {
            return hr;
        }

        // Check to see if we need to restart the movie
        CheckMovieStatus();
        hr = S_OK;
    }// try
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error when trying to render the scene."));
        hr = E_UNEXPECTED;
        // just in case scene is not ended
        m_pd3dDevice->EndScene();
    }

    return hr;
}

//-----------------------------------------------------------------------------
// Name: CCustomPresentation::InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT CCustomPresentation::InitD3D()
{
    HRESULT hr = S_OK;
    D3DDISPLAYMODE d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    try
    {
        // Create the D3D object.
        m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
        if( !m_pD3D )
        {
            return E_FAIL;
        }

        // Get the current desktop display mode, so we can set up a back
        // buffer of the same format
        hr = m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );
        if( FAILED(hr))
        {
            Msg(TEXT("Could not read adapter display mode.  hr=0x%x"), hr);
            return hr;
        }

        // Set up the structure used to create the D3DDevice. Since we are now
        // using more complex geometry, we will create a device with a zbuffer.
        ZeroMemory( &d3dpp, sizeof(d3dpp) );
        d3dpp.Windowed               = TRUE;
        d3dpp.SwapEffect             = D3DSWAPEFFECT_COPY;
        d3dpp.BackBufferFormat       = d3ddm.Format;
        d3dpp.EnableAutoDepthStencil = TRUE;
        d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

        // Create the D3DDevice
        hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwnd,
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                   &d3dpp, &m_pd3dDevice );                                     
        if (FAILED(hr))                                      
        {
            Msg(TEXT("Could not create the D3D device!  hr=0x%x\r\n\r\n")
                TEXT("This sample is attempting to create a buffer that might not\r\n")
                TEXT("be supported by your video card in its current mode.\r\n\r\n")
                TEXT("You may want to reduce your screen resolution or bit depth\r\n")
                TEXT("and try to run this sample again."), hr);
            return hr;
        }

        // Texture coordinates outside the range [0.0, 1.0] are set 
        // to the texture color at 0.0 or 1.0, respectively.
        hr = m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP );
        hr = m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP );

        // Set linear filtering quality
        hr = m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
        hr = m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

        // set maximum ambient light
        hr = m_pd3dDevice->SetRenderState(D3DRS_AMBIENT,RGB(255,255,255));

        // Turn off culling
        hr = m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

        // Turn on the zbuffer
        hr = m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );

        // Turn off lights
        hr = m_pd3dDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

        // Enable dithering
        hr = m_pd3dDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);

        // disable stencil
        hr = m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

        // manage blending
        hr = m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

        hr = m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

        hr = m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

        hr = m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

        hr = m_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x10);

        hr = m_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


        // Set texture states:

        // Modulate diffuse color of the vertex with texture color (50% and 50%)
        // then when we set color of lower vertices of the flag to background color,
        // it blends with texture and gives coloring of the lower part of the flag
        // correspondent to the background
        hr = m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
        hr = m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        hr = m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

        // turn off alpha operation
        hr = m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    }
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error.\r\n\r\n")
            TEXT("This sample is attempting to create a buffer that might not\r\n")
            TEXT("be supported by your video card in its current mode.\r\n\r\n")
            TEXT("You may want to reduce your screen resolution or bit depth\r\n")
            TEXT("and try to run this sample again."));
        hr = E_UNEXPECTED;
    }

    return hr;
}

//-----------------------------------------------------------------------------
// Name: CCustomPresentation::InitGeometry()
// Desc: Create the textures and vertex buffers
//-----------------------------------------------------------------------------
HRESULT CCustomPresentation::InitGeometry()
{
    HRESULT hr = S_OK;
    CUSTOMVERTEX* pVertices = NULL;
    DWORD N = g_nWaves * g_nWaveN;

    try
    {
        // DirectShow: Set up filter graph with our custom renderer.
        hr = InitDShowTextureRenderer();
        if( FAILED(hr) )
        {
            return E_FAIL;
        }

        // Create the vertex buffer.
        hr = m_pd3dDevice->CreateVertexBuffer(  g_nWaves * g_nWaveN * 2 * sizeof(CUSTOMVERTEX),
                                                0, D3DFVF_CUSTOMVERTEX,
                                                D3DPOOL_DEFAULT, &m_pVB, NULL );
        if( FAILED( hr ) )
        {
            Msg(TEXT("Could not create a vertex buffer.  hr=0x%x"), hr);
            return hr;
        }

        // Fill the vertex buffer. We are setting the tu and tv texture
        // coordinates, which range from 0.0 to 1.0
        if ( FAILED( hr = m_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
        {
            Msg(TEXT("Could not lock the vertex buffer.  hr=0x%x"), hr);
            return hr;
        }

        for( DWORD i=0; i<N; i++ )
        {
            // m_HAR and m_VAR recognize the fact that allocated surface
            // can be larger than requested (due to alignment, HW specific)

            // we are not going to change color for upper part of the flag                                    
            pVertices[2*i+0].color    = D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF); 
            pVertices[2*i+0].tu       = m_HAR *(1.f - ((FLOAT)i)/(N-1));
            pVertices[2*i+0].tv       = m_VAR;

            pVertices[2*i+1].tu       = m_HAR *(1.f - ((FLOAT)i)/(N-1));
            pVertices[2*i+1].tv       = 0.0f;
        }

        m_pVB->Unlock();

        // call CalculateVertices that changes other parameters of vertices dynamically,
        // depending on the time (animation)
        hr = CalculateVertices();
        if( FAILED(hr))
        {
            return hr;
        }
    
        // set up D3D world, view and perspective matrices 
        // (this function is called only once because we change object's coordinates
        // and do not change point of view)
        hr = SetupMatrices();
        if( FAILED(hr))
        {
            return hr;
        }

        // set up lights (if HW supports it). Since we do not change the lights 
        // during presentation, call it only once
        hr = SetupLights();
        if( FAILED(hr ))
        {
            return hr;
        }
    } // try
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error.\r\n\r\n")
            TEXT("This sample is attempting to create a buffer that might not\r\n")
            TEXT("be supported by your video card in its current mode.\r\n\r\n")
            TEXT("You may want to reduce your screen resolution or bit depth\r\n")
            TEXT("and try to run this sample again."));
        hr = E_UNEXPECTED;  

        // just in case that vertex buffer is locked, try to unlock it
        m_pVB->Unlock();
    }

    return hr;
}

//-----------------------------------------------------------------------------
// Name: CCustomPresentation::InitDShowTextureRenderer 
// Desc: Create and run DirectShow capture filter graph
//-----------------------------------------------------------------------------
HRESULT CCustomPresentation::InitDShowTextureRenderer()
{
    HRESULT hr = S_OK;

    CComPtr<IBaseFilter>    pRenderer;      // Texture Renderer Filter
    CComPtr<IBaseFilter>    pFSrc;          // Source Filter
    CComPtr<IPin>           pFSrcPinOut;    // Source Filter Output Pin   
    CTextureRenderer        *pCTR=0;        // DShow Texture renderer
    
    try
    {
        // Create the filter graph
        hr = m_pGB.CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC);
        if( FAILED(hr))
        {
            Msg(TEXT("Failed to create filter graph. hr = 0x%08x"), hr);
            return hr;
        }

        // Get the graph's media control and media event interfaces
        m_pGB.QueryInterface(&m_pMC);
        m_pGB.QueryInterface(&m_pME);
    
        // Create the Texture Renderer object
        pCTR = new CTextureRenderer(this, NULL, &hr);
        if (FAILED(hr) || !pCTR)
        {
            Msg(TEXT("Could not create texture renderer object.  hr=0x%x"), hr);
            return hr;
        }
    
        // Get a pointer to the IBaseFilter interface on the TextureRenderer
        // and add it to the existing graph
        pRenderer = pCTR;

        hr = m_pGB->AddFilter(pRenderer, L"Texture Renderer");
        if (FAILED(hr))
        {
            Msg(TEXT("Could not add renderer filter to graph.  hr=0x%x"), hr);
            return hr;
        }

        // Initialize the first attached video capture device and set
        // our 3D renderer to render the incoming video    
        hr = CaptureVideo( pRenderer );
        if (FAILED(hr))
        {
            // CaptureVideo will display an appropriate error message
            return hr;
        }
  
#ifdef REGISTER_FILTERGRAPH
        // Register the graph in the Running Object Table (for debug purposes)
        AddToROT(m_pGB);
#endif
    
        // Start the graph running
        hr = m_pMC->Run();
        if (FAILED(hr))
        {
            Msg(TEXT("Could not run the DirectShow graph.  hr=0x%x"), hr);
            return hr;
        }
    }// try
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error.\r\n\r\n")
            TEXT("This sample is attempting to build a DirectShow graph with\r\n")
            TEXT("a custom TextureRenderer. You may want to check video capture\r\n")
            TEXT("functionality on your system and try to run this sample again."));
        hr = E_UNEXPECTED;  
    }
    return hr;
}

HRESULT CCustomPresentation::CaptureVideo(IBaseFilter *pRenderer)
{
    HRESULT hr = S_OK;
    CComPtr<IBaseFilter> pSrcFilter;

    try
    {
        // Create the capture graph builder object to assist in building
        // the video capture filter graph
        hr = CoCreateInstance (CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC,
                               IID_ICaptureGraphBuilder2, (void **) &(m_pCapture.p));
        if (FAILED(hr))
        {
            Msg(TEXT("Could not create the capture graph builder!  hr=0x%x\0"), hr);
            return hr;
        }
    
        // Attach the existing filter graph to the capture graph
        hr = m_pCapture->SetFiltergraph(m_pGB);
        if (FAILED(hr))
        {
            Msg(TEXT("Failed to set capture filter graph!  hr=0x%x\0"), hr);
            return hr;
        }

        // Use the system device enumerator and class enumerator to find
        // a video capture/preview device, such as a desktop USB video camera.
        hr = FindCaptureDevice(&pSrcFilter);
        if (FAILED(hr))
        {
            // Don't display a message because FindCaptureDevice will handle it
            return hr;
        }
   
        // Add the returned capture filter to our graph.
        hr = m_pGB->AddFilter(pSrcFilter, L"Video Capture");
        if (FAILED(hr))
        {
            Msg(TEXT("Could not add the capture filter to the graph.  hr=0x%x\r\n\r\n")
                TEXT("Make sure that a video capture device is connected and functional\n")
                TEXT("and is not being used by another capture application.\0"), hr);
            return hr;
        }

        // Render the preview pin on the video capture filter.
        // This will create and connect any necessary transform filters.
        // We pass a pointer to the IBaseFilter interface of our CTextureRenderer
        // video renderer, which will draw the incoming video onto a D3D surface.
        hr = m_pCapture->RenderStream (&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
                                       pSrcFilter, NULL, pRenderer);
        if (FAILED(hr))
        {
            Msg(TEXT("Could not render the capture stream.  hr=0x%x\r\n\r\n")
                TEXT("Make sure that a video capture device is connected and functional\n")
                TEXT("and is not being used by another capture application.\0"), hr);
            return hr;
        }
    }// try
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error when trying to render the graph."));
        hr = E_UNEXPECTED;
    }

    return S_OK;
}

HRESULT CCustomPresentation::FindCaptureDevice(IBaseFilter ** ppSrcFilter)
{
    HRESULT hr = S_OK;
    CComPtr <IMoniker> pMoniker;
    CComPtr <ICreateDevEnum> pDevEnum;
    CComPtr <IEnumMoniker> pClassEnum;

    IBaseFilter * pSrc = NULL;
    ULONG cFetched;

    if (!ppSrcFilter)
        return E_POINTER;

    try
    {
        // Create the system device enumerator
        hr = CoCreateInstance (CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                            IID_ICreateDevEnum, (void **) &pDevEnum);
        if (FAILED(hr))
        {
            Msg(TEXT("Couldn't create system device enumerator.  hr=0x%x"), hr);
            return hr;
        }

        // Create an enumerator for the video capture devices
        hr = pDevEnum->CreateClassEnumerator (CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
        if (FAILED(hr))
        {
            Msg(TEXT("Couldn't create class enumerator for video input device category.  hr=0x%x"), hr);
            return hr;
        }

        // If there are no enumerators for the requested type, then 
        // CreateClassEnumerator will succeed, but pClassEnum will be NULL.
        if (pClassEnum == NULL)
        {
            MessageBox(NULL,TEXT("No video capture device was detected.\r\n\r\n")
                    TEXT("This sample requires a video capture device, such as a USB WebCam,\r\n")
                    TEXT("to be installed and working properly.  The sample will now close."),
                    TEXT("No Video Capture Hardware"), MB_OK | MB_ICONINFORMATION);
            return E_FAIL;
        }

        // Use the first video capture device on the device list.
        // Note that if the Next() call succeeds but there are no monikers,
        // it will return S_FALSE (which is not a failure).  Therefore, we
        // check that the return code is S_OK instead of using SUCCEEDED() macro.
        if (S_OK == (pClassEnum->Next (1, &pMoniker, &cFetched)))
        {
            // Bind Moniker to a filter object
            hr = pMoniker->BindToObject(0,0,IID_IBaseFilter, (void**)&pSrc);
            if (FAILED(hr))
            {
                Msg(TEXT("Couldn't bind moniker to filter object.  hr=0x%x"), hr);
                return hr;
            }
        }
        else
        {
            Msg(TEXT("Unable to access video capture device."));   
            return E_FAIL;
        }

        // Copy the found filter pointer to the output parameter.
        // Do NOT Release() the reference, since it will still be used
        // by the calling function.
        *ppSrcFilter = pSrc;

    }// try
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error when trying to find capture device."));
        hr = E_UNEXPECTED;
    }
    return hr;
}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
HRESULT CCustomPresentation::SetupMatrices()
{
    HRESULT hr = S_OK;;

    D3DXMATRIX matWorld;
    D3DXMATRIX matView;
    D3DXMATRIX matProj;

    D3DXMatrixIdentity( &matWorld );

    try
    {
        hr = m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
        if (FAILED(hr))                                      
        {
            Msg(TEXT("Could not set D3DTS_WORLD transform.  hr=0x%x"), hr);
            return hr;
        }
        // Set up our view matrix. A view matrix can be defined given an eye point,
        // a point to lookat, and a direction for which way is up. Here, we set the
        // eye nine units back along the z-axis and up four units, look at the
        // origin, and define "up" to be in the -y-direction.
        D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, -4.0f,-9.0f ),
                                      &D3DXVECTOR3( 0, 0.0f, 0.0f ),
                                      &D3DXVECTOR3( 0.0f, -1.0f, 0.0f ) );

        hr = m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
        if (FAILED(hr))                                      
        {
            Msg(TEXT("Could not set D3DTS_VIEW transform.  hr=0x%x"), hr);
            return hr;
        }

        // For the projection matrix, we set up a perspective transform (which
        // transforms geometry from 3D view space to 2D viewport space, with
        // a perspective divide making objects smaller in the distance). To build
        // a perpsective transform, we need the field of view (1/4 pi is common),
        // the aspect ratio, and the near and far clipping planes (which define at
        // what distances geometry should be no longer be rendered).
        D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );

        hr = m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
        if (FAILED(hr))                                      
        {
            Msg(TEXT("Could not set D3DTS_PROJECTION transform.  hr=0x%x"), hr);
            return hr;
        }
    }// try
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error when trying to set Direct3D environment."));
        hr = E_UNEXPECTED;
    }

    return hr;
}

//-----------------------------------------------------------------------------
// Name: CCustomPresentation::SetupMatrices()
// Desc: Sets up two lights: one is white directed from viewer's left, 
//       the other is pale yellow directed from viewer to the flag
//-----------------------------------------------------------------------------
HRESULT CCustomPresentation::SetupLights()
{
    HRESULT hr = S_OK;

    D3DXVECTOR3 vecDir;
    D3DLIGHT9 light;    
    D3DLIGHT9 lightAux;
    D3DCAPS9 d3dcaps;

    try
    {
        // check if HW supports lights
        m_pd3dDevice->GetDeviceCaps( &d3dcaps );
        if( NULL == (d3dcaps.DevCaps & (DWORD)D3DDEVCAPS_HWTRANSFORMANDLIGHT) )
        {
            // Turn off D3D lighting
            hr = m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
            return S_OK;
        }
        else// light is supported; try Gouraud first, if it fails, set flat
        {
            // Set to Gouraud shading. This is the default for Direct3D.
            hr = m_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
            if(FAILED(hr))
            {
                // Failed to set Gouraud, let's try flat shading
                hr = m_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
                if(FAILED(hr))
                {
                    // Turn off D3D lighting
                    hr = m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
                    return S_OK;
                }
            }
        }// else
    
        hr = m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

        // main light
        ZeroMemory( &light, sizeof(light) );
        light.Type = D3DLIGHT_DIRECTIONAL;

        // this light has maximum intensity
        light.Diffuse.r = 1.0f;
        light.Diffuse.g = 1.0f;
        light.Diffuse.b = 1.0f;

        // this light beams from the upper left , behind the viewer
        vecDir = D3DXVECTOR3( -1.f, -1.f, 1.0f);

        D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
        m_pd3dDevice->SetLight( 0, &light );
        m_pd3dDevice->LightEnable( 0, TRUE);

        // auxiliary light: yellowish
        ZeroMemory( &lightAux, sizeof(light) );
        lightAux.Type = D3DLIGHT_DIRECTIONAL;

        // not full intensity, dominant yellow color
        lightAux.Diffuse.r = 0.75f;
        lightAux.Diffuse.g = 0.75f;
        lightAux.Diffuse.b = 0.5f;

        // beams horizontally 
        vecDir = D3DXVECTOR3(-1.f, 1.f, 0.1f); 

        D3DXVec3Normalize( (D3DXVECTOR3*)&lightAux.Direction, &vecDir );
        m_pd3dDevice->SetLight( 1, &lightAux );
        m_pd3dDevice->LightEnable( 1, TRUE);
    } // try
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error when trying to set Direct3D lights."));
        hr = E_UNEXPECTED;
    }
    return hr;
}

//-----------------------------------------------------------------------------
// Name: CCustomPresentation::CalculateVertices()
// Desc: Calculates vertices of the flag to provide animation
//       DShow clock is animation parameter
//-----------------------------------------------------------------------------
HRESULT CCustomPresentation::CalculateVertices()
{
    HRESULT hr=S_OK;
    FLOAT theta;
    FLOAT arg;
    FLOAT dt = (timeGetTime() - m_dwStartTime)/500.f;

    static DWORD N = g_nWaveN * g_nWaves;
    static FLOAT pi3_4 = 3.0f*D3DX_PI/4.0f;
    FLOAT waveHeight = 0.4f + 0.1f * (cosf( 2.f*dt )+1.f);

    CUSTOMVERTEX* pVertices = NULL;
    try
    {
        hr = m_pVB->Lock( 0, 0, (void**)&pVertices, 0 );
        if ( FAILED( hr ) )
        {
            Msg(TEXT("Could not lock the vertex buffer.  hr=0x%x"), hr);
            return hr;
        }
    
        for( DWORD i=0; i<N-1; i++ )
        {
            // theta runs from -(2 pi) to zero
            theta = (2*D3DX_PI*i)/(N-1);
            arg = theta * (N-1) / (FLOAT)g_nWaveN + dt;
            theta -= D3DX_PI;
            
            //  only z-coord changes
            pVertices[2*i+0].position = D3DXVECTOR3( theta, -pi3_4, waveHeight * sinf(arg) );

            // we use normal to calculate shadows
            // since (x,y,z) = (t,C,A sin( B t + c)),
            //      n(x,y,z) = (1,0,- B A cos( B t + c)) (partial derivatives by t... or close to this ;-) )
            pVertices[2*i+0].n        = D3DXVECTOR3( 1.f, 0.f, -waveHeight * (N-1) / (FLOAT)g_nWaveN * cosf(arg) );

            // lower part delayed by pi/2 so that waves would not be completely vertical
            pVertices[2*i+1].position = D3DXVECTOR3( theta,  pi3_4, waveHeight * sinf(arg + D3DX_PI/2.f) );
            pVertices[2*i+1].n        = D3DXVECTOR3( 1.f, 0.f, -waveHeight * (N-1) / (FLOAT)g_nWaveN * cosf(arg + D3DX_PI/2.f) );

            // we have to update color every time because user can toggle background color by 
            // hitting 'space' or 'enter'
            pVertices[2*i+1].color    = m_d3dcolorBackground;
        }

        m_pVB->Unlock();

    }// try
    catch(...)
    {
        Msg(TEXT("Application encountered an unexpected error when trying to recalculate vertex buffer."));
        hr = E_UNEXPECTED;

        // just in case we did not unlock the buffer
        m_pVB->Unlock();
    }
    return hr;
}

//-----------------------------------------------------------------------------
// Name: CheckMovieStatus
// Desc: Wait for capture events like device removal
//-----------------------------------------------------------------------------
void CCustomPresentation::CheckMovieStatus(void)
{
    long lEventCode;
    long lParam1;
    long lParam2;
    HRESULT hr = S_OK;

    if (!m_pME)
    {
        return;
    }
        
    // Check for completion events
    hr = m_pME->GetEvent(&lEventCode, (LONG_PTR *) &lParam1, (LONG_PTR *) &lParam2, 0);
    if (SUCCEEDED(hr))
    {
        // Free any memory associated with this event
        hr = m_pME->FreeEventParams(lEventCode, lParam1, lParam2);
    }
}

void CCustomPresentation::SetColor( D3DCOLOR color )
{
    m_d3dcolorBackground = color;
}

IDirect3DDevice9 * CCustomPresentation::GetDevice()
{
    if( m_pd3dDevice )
    {
        return m_pd3dDevice;
    }
    return NULL;
}


HRESULT CCustomPresentation::CreateTexture( UINT Width, UINT Height, D3DFORMAT format)
{
    HRESULT hr = S_OK;
    D3DSURFACE_DESC ddsd;

    try
    {
        hr = m_pd3dDevice->CreateTexture( Width, Height, 1, 0, format, 
                                          D3DPOOL_MANAGED, &m_pTexture, NULL);
        if( FAILED(hr))
        {
            Msg(TEXT("Failed to create IDirect3DTexture9."), hr);
            return hr;
        }

        hr = m_pTexture->GetLevelDesc( 0, &ddsd );
        if( FAILED(hr))
        {
            Msg(TEXT("Failed to get level description of IDirect3DTexture9."), hr);
            return hr;
        }

        if (ddsd.Format != D3DFMT_A8R8G8B8 &&
            ddsd.Format != D3DFMT_A1R5G5B5) 
        {
            Msg(TEXT("Texture has a format we can't handle. Format = 0x%x"), ddsd.Format);
            return VFW_E_TYPE_NOT_ACCEPTED;
        }

        m_TextureFormat = ddsd.Format;
        m_Width = ddsd.Width;
        m_Height = ddsd.Height;
        m_HAR = (FLOAT)Width  / (FLOAT)ddsd.Width;
        m_VAR = (FLOAT)Height / (FLOAT)ddsd.Height;
    }
    catch(...)
    {
        Msg(TEXT("Application excountered unexpected error when trying to allocate IDirect3DTexture9."), 
            E_UNEXPECTED);
        hr = E_UNEXPECTED;
    }
    return hr;
}

HRESULT CCustomPresentation::BltToTexture(IDirect3DSurface9 *lpSurfSrc, UINT Width, UINT Height)
{
    HRESULT hr = S_OK;

    CAutoLock lock(&m_cs);
    CComPtr< IDirect3DSurface9> lpSurfDst;

    RECT rcDst;
    RECT rcSrc;

    if( !lpSurfSrc )
    {
        return E_POINTER;
    }
    try
    {
        hr = m_pTexture->GetSurfaceLevel( 0, &lpSurfDst);
        if( FAILED(hr))
        {
            Msg(TEXT("Cannot get IDirect3DSurface9 interface. hr = 0x%08x"), hr);
            return hr;
        }

        rcDst.left = rcDst.top = 0;
        rcDst.right = m_Width;
        rcDst.bottom = m_Height;

        ZeroMemory( &rcSrc, sizeof(RECT));
        rcSrc.right = Width;
        rcSrc.bottom = Height;
        
        hr = D3DXLoadSurfaceFromSurface( lpSurfDst, NULL, &rcDst, lpSurfSrc, NULL, &rcSrc, D3DX_DEFAULT, 0xFF000000);
        if( FAILED(hr))
        {
            Msg(TEXT("Cannot Blt onto texture surface. hr = 0x%08x"), hr);
            return hr;
        }
    }
    catch(...)
    {
        Msg(TEXT("Application excountered unexpected error when trying to Blt onto texture."), 
            E_UNEXPECTED);
        hr = E_UNEXPECTED;
    }
    return hr;
}

HRESULT CCustomPresentation::CopyMediaSample( IMediaSample *pSample, LONG lSamplePitch )
{
    HRESULT hr = S_OK;
    CAutoLock lock(&m_cs);

    BYTE * pSampleBuffer = NULL;
    BYTE * pTextureBuffer = NULL;
    BYTE * pbS = NULL;

    DWORD * pdwS = NULL;
    DWORD * pdwD = NULL;

    UINT row;
    UINT col;

    D3DLOCKED_RECT d3dlr;
    LONG  lTexturePitch;     // Pitch of texture

    if( !pSample )
        return E_POINTER;

    if( !m_pTexture )
        return E_UNEXPECTED;

    try
    {
        // Get the video bitmap buffer
        hr = pSample->GetPointer( &pSampleBuffer );
        if( FAILED(hr))
        {
            return hr;
        }

        // Lock the Texture
        hr = m_pTexture->LockRect( 0, &d3dlr, 0, 0 );
        if( FAILED(hr))
        {
            return E_FAIL;
        }

        // Get the texture buffer & pitch
        pTextureBuffer = static_cast<byte *>(d3dlr.pBits);
        lTexturePitch = d3dlr.Pitch;

        if( m_TextureFormat == D3DFMT_A1R5G5B5 )
        {
            for(row = 0; row < m_Height; row++ ) 
            {
                BYTE *pBmpBufferOld = pTextureBuffer;
                BYTE *pTxtBufferOld = pSampleBuffer;   

                for (col = 0; col < m_Width; col++) 
                {
                    *(WORD *)pTextureBuffer = (WORD)
                        (0x8000 +
                        ((pSampleBuffer[2] & 0xF8) << 7) +
                        ((pSampleBuffer[1] & 0xF8) << 2) +
                        (pSampleBuffer[0] >> 3));

                    pTextureBuffer += 2;
                    pSampleBuffer += 3;
                }
                pSampleBuffer  = pBmpBufferOld + lSamplePitch;
                pTextureBuffer = pTxtBufferOld + lTexturePitch;
            }
        }
        if( m_TextureFormat == D3DFMT_A8R8G8B8 )
        {
            for(row = 0; row < m_Height; row++ ) 
            {
                BYTE *pBmpBufferOld = pSampleBuffer;
                BYTE *pTxtBufferOld = pTextureBuffer;   

                for (col = 0; col < m_Width; col++) 
                {
                    pTextureBuffer[0] = pSampleBuffer[0];
                    pTextureBuffer[1] = pSampleBuffer[1];
                    pTextureBuffer[2] = pSampleBuffer[2];
                    pTextureBuffer[3] = 0xFF;//(BYTE)(0xFF * y / (m_lVidHeight-1));

                    pTextureBuffer += 4;
                    pSampleBuffer  += 3;
                }

                pSampleBuffer  = pBmpBufferOld + lSamplePitch;
                pTextureBuffer = pTxtBufferOld + lTexturePitch;
            }

        }

        hr = m_pTexture->UnlockRect(0);

    }
    catch(...)
    {
        hr = m_pTexture->UnlockRect(0);
        ASSERT(0);
    }
    return hr;
}


//-----------------------------------------------------------------------------
// Name: CCustomPresentation::MsgProc()
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
            if (g_pPresentation)
                g_pPresentation->Render();       // Update the main window when needed
            break;

        case WM_CHAR:
        {
            CCustomPresentation *pP = NULL;
            D3DCOLOR color;
            pP = (CCustomPresentation*)GetWindowLongPtr( hWnd, GWLP_USERDATA);

            // Close the app if the ESC key is pressed
            if (wParam == VK_ESCAPE)
            {
                PostMessage(hWnd, WM_CLOSE, 0, 0);
            }
            else if(wParam == VK_SPACE)
            {
                color = D3DCOLOR_XRGB(rand()%0xFF, rand()%0xFF, rand()%0xFF);
                if(pP)
                {
                    pP->SetColor(color);
                }
            }
            else if(wParam == VK_RETURN)
            {
                color = D3DCOLOR_XRGB(0, 0, 0);
                if(pP)
                {
                    pP->SetColor(color);
                }
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
// Running Object Table functions: Used to debug. By registering the graph
// in the running object table, GraphEdit is able to connect to the running
// graph. This code should be removed before the application is shipped in
// order to avoid third parties from spying on your graph.
//-----------------------------------------------------------------------------
#ifdef REGISTER_FILTERGRAPH

HRESULT CCustomPresentation::AddToROT(IUnknown *pUnkGraph) 
{
    HRESULT hr = S_OK;
    IMoniker * pmk = NULL;
    IRunningObjectTable *pROT = NULL;
    WCHAR wsz[256];
    
    if (FAILED(GetRunningObjectTable(0, &pROT))) 
    {
        return E_FAIL;
    }

    wsprintfW(wsz, L"FilterGraph %08x  pid %08x\0", (DWORD_PTR) 0, GetCurrentProcessId());

    hr = CreateItemMoniker(L"!", wsz, &pmk);
    if (SUCCEEDED(hr)) 
    {
        // Use the ROTFLAGS_REGISTRATIONKEEPSALIVE to ensure a strong reference
        // to the object.  Using this flag will cause the object to remain
        // registered until it is explicitly revoked with the Revoke() method.
        //
        // Not using this flag means that if GraphEdit remotely connects
        // to this graph and then GraphEdit exits, this object registration 
        // will be deleted, causing future attempts by GraphEdit to fail until
        // this application is restarted or until the graph is registered again.
        hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, 
                            pmk, &m_dwROTReg);
        pmk->Release();
    }

    pROT->Release();
    return hr;
}


void CCustomPresentation::RemoveFromROT(void)
{
    IRunningObjectTable *pirot=0;

    if (SUCCEEDED(GetRunningObjectTable(0, &pirot))) 
    {
        pirot->Revoke(m_dwROTReg);
        pirot->Release();
    }
}

#endif


