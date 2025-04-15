//-----------------------------------------------------------------------------
// File: Donuts.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------

// This GUID must be unique for every game, and the same for 
// every instance of this app.  // {769FCCA3-150E-4514-A9E2-E28449A7C401}
// The GUID allows DirectInput to remember input settings
GUID g_guidApp = { 0x769fcca3, 0x150e, 0x4514, { 0xa9, 0xe2, 0xe2, 0x84, 0x49, 0xa7, 0xc4, 0x01 } };

CMyApplication*    g_pApp       = NULL;             // Global access to the app 
HINSTANCE          g_hInst      = NULL;             // Global HINSTANCE
CProfile           g_Profile;                       // Read & stores settings for the game from .ini
CTerrainEngine*    g_pTerrain   = NULL;             // Terrian engine owns the graphics objects
IDirect3DDevice9*  g_pd3dDevice = NULL;             // Class to handle D3D device
C3DDrawManager*    g_p3DDrawManager = NULL;         // for debugging




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Application entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow )
{
    CMyApplication app;

    srand( timeGetTime() );

    g_hInst = hInstance;

    if( FAILED( app.Create( hInstance ) ) )
        return 0;

    return app.Run();
}




//-----------------------------------------------------------------------------
// Name: CMyApplication()
// Desc: Constructor
//-----------------------------------------------------------------------------
CMyApplication::CMyApplication()
{
    g_pApp                  = this;
    m_fTime                 = 0.0f;
    m_strAppName            = _T("Donuts 4: Revenge of the Space Torus");
    m_hWndMain              = NULL;               
    m_dwScreenWidth         = 1024;   
    m_dwScreenHeight        = 768;
    m_bFullScreen           = FALSE; 
    m_bIsActive             = FALSE; 
    m_bDisplayReady         = FALSE; 
    m_bMouseVisible         = FALSE;  
    m_dwAppState            = APPSTATE_LOADSPLASH;              
    m_dwLevel               = 0;     
    m_fFPS                  = 0.0f;
    m_pInputManager         = NULL;
    m_pShip                 = NULL;          
    m_pViewportVB           = NULL;
    m_pRadarVB              = NULL;
    m_pSkyDome              = NULL; 
    m_pFileWatch            = NULL;
    m_p3DListener           = NULL;
    m_pBullet1Sound         = NULL;
    m_pExplosionDonutSound  = NULL;
    m_pMusicManager         = NULL;
    m_pMusicScript          = NULL;
    m_pEnginePath           = NULL;
    m_pMusicManager         = NULL;  
    m_pSkyTexture           = NULL; 
    m_pRadarTexture         = NULL;
    m_pTempRadarTexture     = NULL;
    m_pUITexture            = NULL; 
    g_pTerrain              = NULL;
    m_pGameFont             = NULL;
    m_pMenuFont             = NULL;
    m_pMainMenu             = NULL;    
    m_pQuitMenu             = NULL;
    m_pCurrentMenu          = NULL;
    m_p3DDrawManager        = NULL;
    m_pSplashTexture        = NULL;
    m_bPaused               = FALSE;
    m_lSpeed                = 0;
    m_bDebugMode            = FALSE;
    m_bWireMode             = FALSE;
    m_fRadarTextureX        = 0.0f;
    m_fRadarTextureY        = 0.0f;
    m_fPhysicsSimCaryyOver  = 0.0f;
}




//-----------------------------------------------------------------------------
// Name: Create()
// Desc: Creates the window
//-----------------------------------------------------------------------------
HRESULT CMyApplication::Create( HINSTANCE hInstance )
{
    // Register the window class
    WNDCLASS wndClass = { CS_DBLCLKS, StaticMsgProc, 0, 0, hInstance,
                          LoadIcon( hInstance, MAKEINTRESOURCE(DONUTS_ICON) ),
                          LoadCursor( NULL, IDC_ARROW ),
                          (HBRUSH)GetStockObject( BLACK_BRUSH ),
                          NULL, TEXT("Donuts4Class") };
    RegisterClass( &wndClass );
    
    // Create our main window
    m_hWndMain = CreateWindowEx( 0, TEXT("Donuts4Class"), m_strAppName,
                                 WS_POPUP|WS_CAPTION|WS_SYSMENU,
                                 0, 0, 640, 480, NULL, NULL,
                                 hInstance, NULL );
    if( NULL == m_hWndMain )
        return E_FAIL;
    UpdateWindow( m_hWndMain );

    SetCursor( NULL );
    SetFocus( m_hWndMain );
    SetForegroundWindow( m_hWndMain );

    // Save window properties
    m_dwWindowStyle = GetWindowLong( m_hWndMain, GWL_STYLE );
    GetWindowRect( m_hWndMain, &m_rcWindowBounds );
    GetClientRect( m_hWndMain, &m_rcWindowClient );

    // Create the game objects (display objects, sounds, input devices,
    // menus, etc.)
    if( FAILED( OneTimeSceneInit( m_hWndMain ) ) )
    {
        DestroyWindow( m_hWndMain );
        return E_FAIL;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Run()
// Desc: Handles the message loop and calls UpdateScene() and Render() when
//       idle.
//-----------------------------------------------------------------------------
INT CMyApplication::Run()
{
    // Now we're ready to recieve and process Windows messages.
    BOOL bGotMsg;
    MSG  msg;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

    while( WM_QUIT != msg.message  )
    {
        // Use PeekMessage() if the app is active, so we can use idle time to
        // render the scene. Else, use GetMessage() to avoid eating CPU time.
        if( m_bIsActive )
            bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
        else
            bGotMsg = GetMessage( &msg, NULL, 0U, 0U );

        if( bGotMsg )
        {
            // Translate and dispatch the message
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            // Render a frame during idle time (no messages are waiting)
            if( m_bDisplayReady )
            {
                if( m_pFileWatch->HaveFilesChanged( TRUE ) )
                {
                    g_Profile.GetProfile( m_strProfilePath );
                }
                else
                {
                    UpdateScene();
                    RenderScene();
                }
            }
        }
    }

    return (int)msg.wParam;
}




//-----------------------------------------------------------------------------
// Name: StaticMsgProc()
// Desc: Static msg handler which passes messages to the application class.
//-----------------------------------------------------------------------------
LRESULT CALLBACK StaticMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    return g_pApp->MsgProc( hWnd, uMsg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Callback for all Windows messages
//-----------------------------------------------------------------------------
LRESULT CMyApplication::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_ACTIVATEAPP:
            m_bIsActive = (BOOL)wParam;

            if( m_bIsActive )
                DXUtil_Timer( TIMER_START );
            else
                DXUtil_Timer( TIMER_STOP );
            break;

        case WM_GETMINMAXINFO:
            ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 320;
            ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
            break;

        case WM_SETCURSOR:
            if( !m_bMouseVisible )
                SetCursor( NULL );
            else
                SetCursor( LoadCursor( NULL, IDC_ARROW ) );
            return TRUE;

        case WM_SYSCOMMAND:
            // Prevent moving/sizing and power loss
            switch( wParam )
            {
                case SC_MOVE:
                case SC_SIZE:
                case SC_MAXIMIZE:
                case SC_KEYMENU:
                case SC_MONITORPOWER:
                        return 1;
            }
            break;

        case WM_SYSKEYDOWN:
            // Handle Alt+Enter to do mode-switching
            if( VK_RETURN == wParam )
            {
                SwitchDisplayModes( !m_bFullScreen, m_dwScreenWidth,
                                    m_dwScreenHeight );
            }
            break;

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_KEYDOWN:

            // Move from splash screen when user presses a key
            if( m_dwAppState == APPSTATE_DISPLAYSPLASH )
            {
                // Advance to the first level
                m_dwAppState = APPSTATE_BEGINLEVELSCREEN;
                DXUtil_Timer( TIMER_START );
                AdvanceLevel();
                return 0;
            }

            if( msg == WM_KEYDOWN ) 
            {
                if( m_bDebugMode )
                {
                    switch( wParam )
                    {
                        case 'N':
                            // Reset ship position
                            m_pShip->m_pSource->m_vCMPos      = D3DXVECTOR3( 10.0f, 15.0f, 3.0f );
                            m_pShip->m_pSource->m_vAngularVel = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
                            m_pShip->m_pSource->m_vCMVel      = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
                            m_pShip->m_vEulerAngles           = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
                            break;

                        case 'C': g_bDebugFreezeZoneRender = TRUE; break;
                        case 'P': m_bPaused = !m_bPaused; break;
                        case 'I': m_bWireMode = !m_bWireMode;   break;
                        case 'G': g_Profile.bRenderGround = !g_Profile.bRenderGround; break;

                        case 'Q': g_vDebugMove.y = 1.0f; break;
                        case 'E': g_vDebugMove.y = -1.0f; break;
                        case 'W': g_vDebugMove.x = 1.0f; break;
                        case 'S': g_vDebugMove.x = -1.0f; break;
                        case 'A': g_vDebugMove.z = 1.0f; break;
                        case 'D': g_vDebugMove.z = -1.0f; break;

                        case '1': g_vDebugRotate.x = 1.0f; break;
                        case '2': g_vDebugRotate.x = -1.0f; break;
                        case '3': g_vDebugRotate.y = 1.0f; break;
                        case '4': g_vDebugRotate.y = -1.0f; break;
                        case 'R': g_vDebugRotate.z = 1.0f; break;
                        case 'F': g_vDebugRotate.z = -1.0f; break;
                    }
                }
            }

            return 0;

        case WM_KEYUP:
            if( m_bDebugMode )
            {
                switch( wParam )
                {
                    case 'Q': g_vDebugMove.y = 0.0f; break;
                    case 'E': g_vDebugMove.y = 0.0f; break;
                    case 'W': g_vDebugMove.x = 0.0f; break;
                    case 'S': g_vDebugMove.x = 0.0f; break;
                    case 'A': g_vDebugMove.z = 0.0f; break;
                    case 'D': g_vDebugMove.z = 0.0f; break;
                    case '1': g_vDebugRotate.x = 0.0f; break;
                    case '2': g_vDebugRotate.x = 0.0f; break;
                    case '3': g_vDebugRotate.y = 0.0f; break;
                    case '4': g_vDebugRotate.y = 0.0f; break;
                    case 'R': g_vDebugRotate.z = 0.0f; break;
                    case 'F': g_vDebugRotate.z = 0.0f; break;
                }
            }
            return 0;

        case WM_PAINT:
            if( m_bDisplayReady )
            {
                switch( m_dwAppState )
                {
                    case APPSTATE_DISPLAYSPLASH:
                    {
                        RenderSplash();
                        g_pd3dDevice->Present( 0, 0, 0, 0 );
                        break;
                    }

                    case APPSTATE_ACTIVE:
                    {
                        RenderFrame();
                        g_pd3dDevice->Present( 0, 0, 0, 0 );
                        break;
                    }
                }
            }
            break;

        case WM_DESTROY:
            InvalidateDeviceObjects();
            DeleteDeviceObjects();
            FinalCleanup();
            PostQuitMessage( 0 );
            m_bDisplayReady = FALSE;
            break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::OneTimeSceneInit( HWND hWnd )
{
    HRESULT hr;

    // Find the donuts4.ini file
    if( FAILED( hr = FindMediaFileCch( m_strProfilePath, sizeof(m_strProfilePath)/sizeof(TCHAR), TEXT("donuts4.ini") ) ) )
    {
        CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, TEXT("donuts4.ini"), m_strProfilePath );
        return DXTRACE_ERR( TEXT("FindMediaFileCch"), hr );
    }

    // Set the current working dir, so that the model loading 
    // code in d3dfile.cpp can find the textures
    lstrcpy( m_strCurrentWorkingDir, m_strProfilePath );
    TCHAR* pChar = _tcsrchr( m_strCurrentWorkingDir, TEXT('\\') );
    if (pChar)
        *pChar = 0;
    SetCurrentDirectory( m_strCurrentWorkingDir );

    // Read the ini file
    g_Profile.GetProfile( m_strProfilePath );

    // Watch this file to see if it changes.  If it does, reload everything
    m_pFileWatch = new CFileWatch();
    if( NULL == m_pFileWatch )
        return E_OUTOFMEMORY;
    m_pFileWatch->AddFileToWatch( m_strProfilePath );

    // Watch the theme files as well
    for( int iTheme=0; iTheme<g_Profile.nNumThemes; iTheme++ )
        m_pFileWatch->AddFileToWatch( g_Profile.aThemes[iTheme].szFile );

    m_pFileWatch->Start();

    // Use settings read from g_Profile
    m_bFullScreen   = g_Profile.bFullScreen;
    if( g_Profile.bForceThemeSelect )
        m_nCurTheme = g_Profile.nSelectTheme;
    else
        m_nCurTheme = rand() % g_Profile.nNumThemes;

    // In fullscreen mode, keep the window hidden so that
    // a blank window doesn't appear before d3d switches to fullscreen
    if( !m_bFullScreen )
        ShowWindow( m_hWndMain, SW_SHOW );

    // Initialize the input stuff
    m_pInputManager = new CInputManager( this );
    if( NULL == m_pInputManager )
        return E_OUTOFMEMORY;
    m_pInputManager->OneTimeSceneInit( hWnd, &g_guidApp );

    m_p3DDrawManager = new C3DDrawManager();
    if( NULL == m_pInputManager )
        return E_OUTOFMEMORY;
    g_p3DDrawManager = m_p3DDrawManager;
    if( m_p3DDrawManager )
        m_p3DDrawManager->OneTimeSceneInit();

    // Initialize the audio stuff. Note: if this call fails, we can continue with no sound.
    if( g_Profile.bLoadAudio )
        CreateSoundObjects( hWnd );

    // Initialize the display stuff
    if( FAILED( hr = InitDeviceObjects( hWnd ) ) )
        return hr;

    // Construct the game menus
    ConstructMenus();

    // Initial program state is to display the splash screen
    m_dwAppState = APPSTATE_LOADSPLASH;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::InitDeviceObjects( HWND hWnd )
{
    HRESULT hr;

    // Construct a new display
    LPDIRECT3D9 pD3D = Direct3DCreate9( D3D_SDK_VERSION );
    if( NULL == pD3D )
    {
        CleanupAndDisplayError( DONUTSERR_NODIRECT3D, NULL, NULL );
        return DXTRACE_ERR( TEXT("Direct3DCreate9"), E_FAIL );
    }

    // Get the current desktop format
    pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &m_DesktopMode );

    const D3DFORMAT fmtFullscreenArray[] = 
    {
        D3DFMT_A8R8G8B8,
        D3DFMT_X8R8G8B8,
        D3DFMT_X1R5G5B5,
        D3DFMT_A1R5G5B5,
        D3DFMT_R5G6B5,
    };
    const INT numFullscreenFmts = sizeof(fmtFullscreenArray) / sizeof(fmtFullscreenArray[0]);
    INT iFmt;

    // Find a pixel format that will be good for fullscreen back buffers
    for( iFmt = 0; iFmt < numFullscreenFmts; iFmt++ )
    {
        if( SUCCEEDED( pD3D->CheckDeviceType( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
            fmtFullscreenArray[iFmt], fmtFullscreenArray[iFmt], FALSE ) ) )
        {
            m_d3dfmtFullscreen = fmtFullscreenArray[iFmt];
            break;
        }
    }

    const D3DFORMAT fmtTextureArray[] = 
    {
        D3DFMT_A8R8G8B8,
        D3DFMT_A4R4G4B4,
        D3DFMT_A1R5G5B5,
    };
    const INT numTextureFmts = sizeof(fmtTextureArray) / sizeof(fmtTextureArray[0]);

    // Find a format that is supported as a texture map for the current mode
    for( iFmt = 0; iFmt < numTextureFmts; iFmt++ )
    {
        if( SUCCEEDED( pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
            m_DesktopMode.Format, 0, D3DRTYPE_TEXTURE, fmtTextureArray[iFmt] ) ) )
        {
            m_d3dfmtTexture = fmtTextureArray[iFmt];
            break;
        }
    }

    // Set up presentation parameters for the display
    ZeroMemory( &m_d3dpp, sizeof(m_d3dpp) );
    m_d3dpp.Windowed         = !m_bFullScreen;
    m_d3dpp.BackBufferCount  = 1;
    m_d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
    m_d3dpp.EnableAutoDepthStencil = TRUE;
    m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    if( m_bFullScreen )
    {
        m_d3dpp.hDeviceWindow    = hWnd;
        m_d3dpp.BackBufferWidth  = m_dwScreenWidth;
        m_d3dpp.BackBufferHeight = m_dwScreenHeight;
        m_d3dpp.BackBufferFormat = m_d3dfmtFullscreen;
    }
    else
    {
        m_d3dpp.BackBufferFormat = m_DesktopMode.Format;
    }

    D3DDEVTYPE dwDevType = D3DDEVTYPE_HAL;
    DWORD dwBehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    if( g_Profile.bForceREF )
        dwDevType = D3DDEVTYPE_REF;
    if( g_Profile.bForceSoftwareVP )
        dwBehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    if( g_Profile.bForceHardwareVP )
        dwBehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;

    // Create the device
    hr = pD3D->CreateDevice( D3DADAPTER_DEFAULT, dwDevType, hWnd,
                             dwBehaviorFlags, &m_d3dpp, &g_pd3dDevice );
    pD3D->Release();
    if( FAILED(hr) )
    {
        CleanupAndDisplayError( DONUTSERR_NOD3DDEVICE, NULL, NULL );
        return DXTRACE_ERR( TEXT("pD3D->CreateDevice"), hr );
    }

    // Create some game fonts
    m_pGameFont = new CD3DFont( _T("Tahoma"), 30, D3DFONT_BOLD );
    if( NULL == m_pGameFont )
        return E_OUTOFMEMORY;
    m_pGameFont->InitDeviceObjects( g_pd3dDevice );

    m_pMenuFont = new CD3DFont( _T("Impact"), 48, D3DFONT_BOLD );
    if( NULL == m_pMenuFont )
        return E_OUTOFMEMORY;
    m_pMenuFont->InitDeviceObjects( g_pd3dDevice );

    m_pMenuFont->RestoreDeviceObjects();
    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Erase the screen
        g_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0, 1.0f, 0L );

        m_pMenuFont->DrawTextScaled( -1.0f, -0.5f, 0.9f, 0.10f, 0.10f, 
                                     0xffffffff, _T("Loading. Please wait..."), D3DFONT_FILTERED|D3DFONT_CENTERED_X );
        m_pMenuFont->DrawTextScaled( -0.5f, 0.5f, 0.9f, 0.05f, 0.05f, 
                                     0xffffff00, _T("Controls:\nMovement: Arrow keys or W,A,S,D\nAim and fire: Mouse"), D3DFONT_FILTERED );

        // End the scene
        g_pd3dDevice->EndScene();
    }
    g_pd3dDevice->Present( 0, 0, 0, 0 );
    m_pMenuFont->InvalidateDeviceObjects();

    if( m_p3DDrawManager )
        m_p3DDrawManager->InitDeviceObjects();

    // Load the sky texture
    TCHAR strFile[MAX_PATH];
    FindMediaFileCch( strFile, MAX_PATH, g_Profile.aThemes[m_nCurTheme].Sky.szTextureMap );
    if( FAILED( hr = D3DUtil_CreateTexture( g_pd3dDevice, strFile, &m_pSkyTexture, m_d3dfmtTexture ) ) )
    {
        CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, g_Profile.aThemes[m_nCurTheme].Sky.szTextureMap, strFile );
        return DXTRACE_ERR( TEXT("D3DUtil_CreateTexture"), hr );
    }

    // Load UI texture 
    FindMediaFileCch( strFile, MAX_PATH, g_Profile.szUITextureMap );
    if( FAILED( hr = D3DXCreateTextureFromFileEx( g_pd3dDevice, strFile, 
                        D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, m_d3dfmtTexture, 
                        D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
                        D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 0, NULL, NULL, &m_pUITexture ) ) ) 
    {
        CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, g_Profile.szUITextureMap, strFile );
        return DXTRACE_ERR( TEXT("D3DXCreateTextureFromFileEx"), hr );
    }

    // Load splash texture 
    FindMediaFileCch( strFile, MAX_PATH, g_Profile.szSplashTextureMap );
    if( FAILED( hr = D3DXCreateTextureFromFileEx( g_pd3dDevice, strFile, 
                            D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, m_d3dfmtTexture, 
                            D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
                            D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 0, NULL, NULL, &m_pSplashTexture ) ) ) 
    {
        CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, g_Profile.szSplashTextureMap, strFile );
        return DXTRACE_ERR( TEXT("D3DXCreateTextureFromFileEx"), hr );
    }

    // Load particle texture
    FindMediaFileCch( strFile, MAX_PATH, g_Profile.Blaster.szParticleTextureMap );
    if( FAILED( hr = D3DUtil_CreateTexture( g_pd3dDevice, strFile,
                                       &g_Profile.Blaster.pParticleTexture, D3DFMT_A8R8G8B8 ) ) )
    {
        CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, g_Profile.Blaster.szParticleTextureMap, strFile );
        return DXTRACE_ERR( TEXT("D3DUtil_CreateTexture"), hr );
    }

    // Load sky dome mesh
    m_pSkyDome = new CD3DMesh();
    if( m_pSkyDome )
    {
        FindMediaFileCch( strFile, MAX_PATH, g_Profile.aThemes[m_nCurTheme].Sky.szModel );
        if( FAILED( hr = m_pSkyDome->Create( g_pd3dDevice, strFile ) ) )
        {
            CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, g_Profile.aThemes[m_nCurTheme].Sky.szModel, strFile );
            return DXTRACE_ERR( TEXT("m_pSkyDome->Create"), hr );
        }
        m_pSkyDome->m_bUseMaterials = FALSE;
    }

    // Create a vextex buffer for the viewport
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 4*sizeof(SCREENVERTEX),
                                       D3DUSAGE_WRITEONLY, D3DFVF_SCREENVERTEX,
                                       D3DPOOL_MANAGED, &m_pViewportVB, NULL ) ) )
        return DXTRACE_ERR( TEXT("g_pd3dDevice->CreateVertexBuffer"), hr );

    // Create a vextex buffer for the radar
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 4*sizeof(SCREENVERTEX),
                                       D3DUSAGE_WRITEONLY, D3DFVF_SCREENVERTEX,
                                       D3DPOOL_MANAGED, &m_pRadarVB, NULL ) ) )
        return DXTRACE_ERR( TEXT("g_pd3dDevice->CreateVertexBuffer"), hr );

    // Load the enemy models
    for( int iEnemy=0; iEnemy<g_Profile.nNumEnemies; iEnemy++ )
    {
        C3DModel* pModel = new C3DModel();
        if( pModel )
        {
            pModel->OneTimeSceneInit();

            FindMediaFileCch( strFile, MAX_PATH, g_Profile.aEnemyStyles[iEnemy].strEnemyModel );
            if( FAILED( hr = pModel->InitDeviceObjects( strFile, (g_Profile.aEnemyStyles[iEnemy].EnemyCreationType == ECT_CreateTest), 0.8f ) ) )
            {
                SAFE_DELETE( pModel );
                CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, g_Profile.aEnemyStyles[iEnemy].strEnemyModel, strFile );
                return DXTRACE_ERR( TEXT("pModel->InitDeviceObjects"), hr );
            }

            g_Profile.aEnemyStyles[iEnemy].pModel = pModel;
        }
    }

    // Load the bullet models
    {
        C3DModel* pModel = new C3DModel();
        if( pModel )
        {
            pModel->OneTimeSceneInit();
            FindMediaFileCch( strFile, MAX_PATH, g_Profile.Blaster.strBulletModel );
            if( FAILED( hr = pModel->InitDeviceObjects( strFile, false, 1.2f ) ) ) 
            {
                SAFE_DELETE( pModel );
                CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, g_Profile.Blaster.strBulletModel, strFile );
                return DXTRACE_ERR( TEXT("pModel->InitDeviceObjects"), hr );
            }

            if( pModel->m_pMesh )
                pModel->m_pMesh->UseMeshMaterials(false);
            g_Profile.Blaster.pModel = pModel;
        }
    }

    m_pShipModel = new C3DModel();
    if( NULL == m_pShipModel )
        return DXTRACE_ERR( TEXT("new"), E_OUTOFMEMORY );

    m_pShipModel->m_vBoundingMin = D3DXVECTOR3(-2.9f,-2.9f,-2.9f);
    m_pShipModel->m_vBoundingMax = D3DXVECTOR3( 2.9f,2.9f, 2.9f);
    m_pShipModel->m_fRadius      = sqrtf(2.0f);
    m_pShipModel->m_vBoundingVertex[0] = D3DXVECTOR3( m_pShipModel->m_vBoundingMin.x, m_pShipModel->m_vBoundingMin.y, m_pShipModel->m_vBoundingMin.z ); // xyz
    m_pShipModel->m_vBoundingVertex[1] = D3DXVECTOR3( m_pShipModel->m_vBoundingMax.x, m_pShipModel->m_vBoundingMin.y, m_pShipModel->m_vBoundingMin.z ); // Xyz
    m_pShipModel->m_vBoundingVertex[2] = D3DXVECTOR3( m_pShipModel->m_vBoundingMin.x, m_pShipModel->m_vBoundingMax.y, m_pShipModel->m_vBoundingMin.z ); // xYz
    m_pShipModel->m_vBoundingVertex[3] = D3DXVECTOR3( m_pShipModel->m_vBoundingMax.x, m_pShipModel->m_vBoundingMax.y, m_pShipModel->m_vBoundingMin.z ); // XYz
    m_pShipModel->m_vBoundingVertex[4] = D3DXVECTOR3( m_pShipModel->m_vBoundingMin.x, m_pShipModel->m_vBoundingMin.y, m_pShipModel->m_vBoundingMax.z ); // xyZ
    m_pShipModel->m_vBoundingVertex[5] = D3DXVECTOR3( m_pShipModel->m_vBoundingMax.x, m_pShipModel->m_vBoundingMin.y, m_pShipModel->m_vBoundingMax.z ); // XyZ
    m_pShipModel->m_vBoundingVertex[6] = D3DXVECTOR3( m_pShipModel->m_vBoundingMin.x, m_pShipModel->m_vBoundingMax.y, m_pShipModel->m_vBoundingMax.z ); // xYZ
    m_pShipModel->m_vBoundingVertex[7] = D3DXVECTOR3( m_pShipModel->m_vBoundingMax.x, m_pShipModel->m_vBoundingMax.y, m_pShipModel->m_vBoundingMax.z ); // XYZ

    // Load terrain textures and meshes
    g_pTerrain = new CTerrainEngine( this );
    if( g_pTerrain )
    {
        hr = g_pTerrain->OneTimeSceneInit( &g_Profile.aThemes[m_nCurTheme] );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("g_pTerrain->OneTimeSceneInit"), hr );

        hr = g_pTerrain->InitDeviceObjects( m_d3dfmtTexture );
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("g_pTerrain->InitDeviceObjects"), hr );
    }

    // Add a ship to the displaylist
    m_pShip = new CPlayerShip();
    if( NULL == m_pShip )
        return DXTRACE_ERR( TEXT("new"), E_OUTOFMEMORY );

    D3DXMATRIX mOrientation;
    D3DXMatrixIdentity( &mOrientation );
    D3DXVECTOR3 vPos;
    vPos.x = rnd(0.0f,1.0f)*ZONE_WIDTH*g_pTerrain->m_dwWorldWidth;
    vPos.z = rnd(0.0f,1.0f)*ZONE_HEIGHT*g_pTerrain->m_dwWorldHeight;   
    vPos.y = g_pTerrain->GetHeight( vPos.x, vPos.z ) + 10.0f;
    m_pShip->OneTimeSceneInit( 0, vPos, &mOrientation, m_pShipModel );
    m_pShip->InitDeviceObjects();

    if( g_pTerrain )
        g_pTerrain->AddDisplayObject( m_pShip );

    // Now that all the display objects are created, "restore" them (create
    // local mem objects and set state)
    if( FAILED( hr = RestoreDeviceObjects() ) )
        return DXTRACE_ERR( TEXT("RestoreDeviceObjects"), hr );

    // The display is now ready
    m_bDisplayReady = TRUE;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::RestoreDeviceObjects()
{
    HRESULT hr;
    HWND hWnd = m_hWndMain;

    if( FALSE == m_bFullScreen )
    {
        // If we are still a WS_POPUP window we should convert to a normal app
        // window so we look like a windows app.
        DWORD dwStyle  = GetWindowStyle( hWnd );
        dwStyle &= ~WS_POPUP;
        dwStyle |= WS_CAPTION | WS_MINIMIZEBOX;
        SetWindowLong( hWnd, GWL_STYLE, dwStyle );

        // Set window size
        RECT rc;
        SetRect( &rc, 0, 0, 640, 480 );

        SetWindowPos( hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
                      SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

        SetWindowPos( hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
                      SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );

        //  Make sure our window does not hang outside of the work area
        RECT rcWork;
        SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWork, 0 );
        GetWindowRect( hWnd, &rc );
        if( rc.left < rcWork.left ) rc.left = rcWork.left;
        if( rc.top  < rcWork.top )  rc.top  = rcWork.top;
        SetWindowPos( hWnd, NULL, rc.left, rc.top, 0, 0,
                      SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
    }

    if( m_p3DDrawManager )
        m_p3DDrawManager->RestoreDeviceObjects();

    // Create the device-dependent objects for the file-based mesh objects
    if( m_pSkyDome )
    {
        if( FAILED( hr = m_pSkyDome->RestoreDeviceObjects( g_pd3dDevice ) ) )
            return DXTRACE_ERR( TEXT("m_pSkyDome->RestoreDeviceObjects"), hr );
    }

    if( g_pTerrain )        
    {
        if( FAILED( hr = g_pTerrain->RestoreDeviceObjects( m_hWndMain ) ) )
            return DXTRACE_ERR( TEXT("g_pTerrain->RestoreDeviceObjects"), hr );
    }

    if( m_pGameFont )
    {
        if( FAILED( hr = m_pGameFont->RestoreDeviceObjects() ) )
            return DXTRACE_ERR( TEXT("m_pGameFont->RestoreDeviceObjects"), hr );
    }
    if( m_pMenuFont )
    {
        if( FAILED( hr = m_pMenuFont->RestoreDeviceObjects() ) )
            return DXTRACE_ERR( TEXT("m_pMenuFont->RestoreDeviceObjects"), hr );
    }

    // Get viewport dimensions
    D3DVIEWPORT9 vp;
    g_pd3dDevice->GetViewport(&vp);
    FLOAT sx = (FLOAT)vp.Width;
    FLOAT sy = (FLOAT)vp.Height;

    if( m_pViewportVB )
    {
        // Setup dimensions for the viewport covering square
        SCREENVERTEX* v;
        m_pViewportVB->Lock( 0, 0, (void**)&v, 0 );
        v[0].color = v[1].color = v[2].color = v[3].color = 0xFFFFFFFF;
        v[0].p = D3DXVECTOR4( 0,sy,0.0f,1.0f);
        v[0].tu = 0.0f;  v[0].tv = 1.0f; 
        v[1].p = D3DXVECTOR4( 0, 0,0.0f,1.0f);
        v[1].tu = 0.0f;  v[1].tv = 0.0f; 
        v[2].p = D3DXVECTOR4(sx,sy,0.0f,1.0f);
        v[2].tu = 1.0f;  v[2].tv = 1.0f; 
        v[3].p = D3DXVECTOR4(sx, 0,0.0f,1.0f);
        v[3].tu = 1.0f;  v[3].tv = 0.0f; 
        m_pViewportVB->Unlock();
    }

    m_fRadarTextureX = 0.20f*(float)vp.Height;
    m_fRadarTextureY = 0.20f*(float)vp.Height;

    // Create a texture for the radar overlay
    UINT x,y;
    x = (UINT) m_fRadarTextureX;
    y = (UINT) m_fRadarTextureY;
    D3DFORMAT f = m_d3dfmtTexture;
    D3DXCheckTextureRequirements( g_pd3dDevice, &x, &y, NULL, 0, &f, D3DPOOL_MANAGED );

    hr = D3DXCreateTexture( g_pd3dDevice, x, y, 1, 0, 
                            m_d3dfmtTexture, D3DPOOL_MANAGED, &m_pRadarTexture );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );

    // Create a radar texture that's on a scratch surface w/ a known format & size
    hr = D3DXCreateTexture( g_pd3dDevice, 256, 256, 1, 0, 
                            D3DFMT_A4R4G4B4, D3DPOOL_SCRATCH, 
                            &m_pTempRadarTexture );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );

    D3DSURFACE_DESC desc;
    m_pTempRadarTexture->GetLevelDesc( 0, &desc ); 
    if( desc.Height != 256 ||
        desc.Width  != 256 ||
        desc.Format != D3DFMT_A4R4G4B4 )
    {
        // Expect texture made in scratch surface to be what we ask for
        if( FAILED(hr) )
            return DXTRACE_ERR( TEXT("D3DXCreateTexture"), hr );
    }

    if( m_pRadarVB )
    {
        // Setup dimensions for the radar covering sqaure
        SCREENVERTEX* v;
        FLOAT x = 0.095f*sx;
        FLOAT y = 0.14f*sy;
        m_pRadarVB->Lock( 0, 0, (void**)&v, 0 );
        v[0].color = v[1].color = v[2].color = v[3].color = 0xFFFFFFFF;
        v[0].p = D3DXVECTOR4( x,m_fRadarTextureY+y,0.0f,1.0f);
        v[0].tu = 0.0f;  v[0].tv = 1.0f; 
        v[1].p = D3DXVECTOR4( x, y,0.0f,1.0f);
        v[1].tu = 0.0f;  v[1].tv = 0.0f; 
        v[2].p = D3DXVECTOR4(m_fRadarTextureX+x,m_fRadarTextureY+y,0.0f,1.0f);
        v[2].tu = 1.0f;  v[2].tv = 1.0f; 
        v[3].p = D3DXVECTOR4(m_fRadarTextureX+x, y,0.0f,1.0f);
        v[3].tu = 1.0f;  v[3].tv = 0.0f; 
        m_pRadarVB->Unlock();
    }

    // Set up the camera
    D3DXVECTOR3 vAt = D3DXVECTOR3(0.0f,0.0f,0.0f);
    D3DXVECTOR3 vLookAt = D3DXVECTOR3(0.0f,0.0f,1.0f);
    D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
    
    m_Camera.SetViewParams( vAt, vLookAt, vUp );
    m_Camera.SetProjParams( g_Profile.fFOV, 1.0f, 0.01f, 250.0f ); // 200.0f );

    // Set up default matrices (using the CD3DCamera class)
    D3DXMATRIX mView = m_Camera.GetViewMatrix();
    D3DXMATRIX mProj = m_Camera.GetProjMatrix();
    g_pd3dDevice->SetTransform( D3DTS_VIEW,       &mView );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &mProj );

    for( int iLight=0; iLight<g_Profile.aThemes[m_nCurTheme].nNumLights; iLight++ )
    {
        // Set up lighting states
        D3DLIGHT9 light;
        ZeroMemory( &light, sizeof(D3DLIGHT9) );
        light.Type        = D3DLIGHT_DIRECTIONAL;
        D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &g_Profile.aThemes[m_nCurTheme].aLights[iLight].vDirection );
        light.Diffuse.r   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vDiffuse.x;
        light.Diffuse.g   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vDiffuse.y;
        light.Diffuse.b   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vDiffuse.z;
        light.Ambient.r   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vAmbient.x;
        light.Ambient.g   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vAmbient.y;
        light.Ambient.b   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vAmbient.z;
        light.Specular.r   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vSpecular.x;
        light.Specular.g   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vSpecular.y;
        light.Specular.b   = g_Profile.aThemes[m_nCurTheme].aLights[iLight].vSpecular.z;
        g_pd3dDevice->SetLight( iLight, &light );
        g_pd3dDevice->LightEnable( iLight, TRUE );
    }

    // Disable the rest of the light states
    g_pd3dDevice->LightEnable( g_Profile.aThemes[m_nCurTheme].nNumLights, FALSE );

    // Set miscellaneous render states
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Set fog render states
    FLOAT fFogStart     = g_Profile.fFogStart; 
    FLOAT fFogEnd       = g_Profile.fFogEnd; 
    FLOAT fFogDensity   = 1.0f;
    g_pd3dDevice->SetRenderState( D3DRS_FOGENABLE,      TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_FOGCOLOR,       g_Profile.aThemes[m_nCurTheme].Sky.dwFogColor );
    g_pd3dDevice->SetRenderState( D3DRS_FOGVERTEXMODE,  D3DFOG_LINEAR );
    g_pd3dDevice->SetRenderState( D3DRS_FOGTABLEMODE,   D3DFOG_NONE );
    g_pd3dDevice->SetRenderState( D3DRS_FOGSTART,       *((DWORD*) (&fFogStart)) );
    g_pd3dDevice->SetRenderState( D3DRS_FOGEND,         *((DWORD*) (&fFogEnd)) );
    g_pd3dDevice->SetRenderState( D3DRS_FOGDENSITY,     *((DWORD*) (&fFogDensity)) );

    // Restore the enemy models
    for( int iEnemy=0; iEnemy<g_Profile.nNumEnemies; iEnemy++ )
    {
        C3DModel* pModel = g_Profile.aEnemyStyles[iEnemy].pModel;
        if( pModel )
            pModel->RestoreDeviceObjects();
    }

    C3DModel* pModel = g_Profile.Blaster.pModel;
    if( pModel )
        pModel->RestoreDeviceObjects();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: UpdateScene()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::UpdateScene()
{
    switch( m_dwAppState )
    {
        case APPSTATE_LOADSPLASH:
            if( g_Profile.bRenderSplash )
            {
                // Set the app state to displaying splash
                m_dwAppState = APPSTATE_DISPLAYSPLASH;
            }
            else
            {
                m_dwAppState = APPSTATE_BEGINACTIVESCREEN;
                DXUtil_Timer( TIMER_START );
                AdvanceLevel();
            }
            break;

        case APPSTATE_DISPLAYSPLASH:
            // Nothing to do here, but wait for a WM_KEYDOWN or button click to 
            // carry us to APPSTATE_BEGINLEVELSCREEN
            break;

        case APPSTATE_BEGINLEVELSCREEN:
            if( m_pMusicScript )
            {
                m_pMusicScript->SetVariableNumber("Level",m_dwLevel);
                m_pMusicScript->CallRoutine("AdvanceLevel");
            }
            DXUtil_Timer( TIMER_RESET );
            m_dwAppState = APPSTATE_DISPLAYLEVELSCREEN;
            break;

        case APPSTATE_DISPLAYLEVELSCREEN:           
            if( m_pInputManager )
                m_pInputManager->UpdateInput();

            // Should never happen because segment lyric should trigger first.
            if( DXUtil_Timer( TIMER_GETAPPTIME ) > 4.0f )
            {
                m_dwAppState = APPSTATE_BEGINACTIVESCREEN;
            }
            break;

        case APPSTATE_BEGINACTIVESCREEN:            
            SCREENVERTEX* v;
            if( m_pViewportVB )
            {
                m_pViewportVB->Lock( 0, 0, (void**)&v, 0 );
                v[0].color = v[1].color = v[2].color = v[3].color = 0xFFFFFFFF;
                m_pViewportVB->Unlock();
            }

            if( m_pMusicScript && g_pTerrain )
            {
                m_pMusicScript->SetVariableNumber("ObjectCount",g_pTerrain->m_dwEnemyCount);
                m_pMusicScript->CallRoutine("ExplodeObject");
            }

            m_dwAppState = APPSTATE_ACTIVE;
            if( m_pMusicScript )
                m_pMusicScript->CallRoutine("StartLevel");
            break;

        case APPSTATE_ACTIVE:
            FrameMove();

            if( g_pTerrain && g_pTerrain->GetEnemyCount() == 0 )
            {
                if( m_pMusicScript )
                {
                    m_pMusicScript->CallRoutine("EndLevel");
                    m_dwAppState = APPSTATE_WAITFORMUSICEND;
                }
                else
                {
                    m_dwAppState = APPSTATE_TRIGGERLEVELSCREEN;
                }                   
            }
            break;

        case APPSTATE_WAITFORMUSICEND:
            // An "AdvanceLevel" lyric will come in via the DirectMusic notification tool
            // and then state will be changed to APPSTATE_TRIGGERLEVELSCREEN
            FrameMove();
            break;

        case APPSTATE_TRIGGERLEVELSCREEN:
            FrameMove();
            AdvanceLevel();
            m_dwAppState = APPSTATE_BEGINLEVELSCREEN;
            break;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::FrameMove()
{
    m_fElapsedTime = DXUtil_Timer( TIMER_GETELAPSEDTIME );
    m_fTime = DXUtil_Timer( TIMER_GETAPPTIME );

    BOOL bPhysicsSimRan = FALSE;

    // Update input from the joystick/keyboard/etc
    if( m_pInputManager )
        m_pInputManager->UpdateInput();
    
    if( m_p3DDrawManager )
        m_p3DDrawManager->FrameMove( m_fElapsedTime );

    // Check for game menu condition
    if( m_pCurrentMenu )
    {
        UpdateMenus();
        return;
    }

    UpdateFarthestAudioPath();

    // Run the physics simulator at 60Hz
    if( g_pTerrain )
    {
        FLOAT fDeltaToSimulate;
        FLOAT fTimeToSimulate = m_fElapsedTime + m_fPhysicsSimCaryyOver;
        fDeltaToSimulate = 1.0f/60.0f;
        while( fTimeToSimulate > fDeltaToSimulate )
        {
            fDeltaToSimulate = 1.0f/60.0f;
            bPhysicsSimRan = TRUE;

            // This simulator runs at a constant 60Hz without 
            // even if there's penetration, so its not very accurate
            // but it is good enough for this simple game
            g_pTerrain->FrameMove( fDeltaToSimulate );

            fTimeToSimulate -= fDeltaToSimulate;
        }

        m_fPhysicsSimCaryyOver = fTimeToSimulate;
    }

    // If the physics advanced 
    if( bPhysicsSimRan )
    {
        // Update the view
        if( m_pShip )
        {
            D3DXVECTOR3 vEyePt;
            D3DXVECTOR3 vLookatPt;
            D3DXVECTOR3 vUpVec;

            m_pShip->GetViewParams( &vEyePt, &vLookatPt, &vUpVec );
            m_Camera.SetViewParams( vEyePt, vLookatPt, vUpVec );

            // Update the cull info now that the camera has changed
            D3DXMATRIXA16 mView = m_Camera.GetViewMatrix();
            D3DXMATRIXA16 mProj = m_Camera.GetProjMatrix();
            UpdateCullInfo( &m_cullinfo, &mView, &mProj );
        }
/*
        // Update the audio paths
        DWORD dwX;
        for (dwX = 0; dwX < MAX_AUDIOPATHS; dwX++)
        {
            // Find the paths that are replacements and restart the sounds
            C3DAudioPath* pAudioPath = &m_AudioPath[dwX];
            if( pAudioPath != NULL && pAudioPath->m_pPath != NULL && pAudioPath->m_bReplaceSound)
            {
                // Stop the playback of all segments on the path (who know what the script
                // has playing on this path...)
                m_pMusicManager->GetPerformance()->StopEx(pAudioPath->m_pPath,0,0);
                pAudioPath->m_bReplaceSound = FALSE;
                // Deactivate the path. This ensures that all audio in the buffer is cleared. 
                pAudioPath->m_pPath->Activate(FALSE);
                if (pAudioPath->m_pObject && m_pMusicScript )
                {
                    // The script will need the audiopath to play on.
                    m_pMusicScript->SetVariableObject("AudioPath",pAudioPath->m_pPath);
                    // Reactivate the path before starting playback.
                    pAudioPath->m_pPath->Activate(TRUE);
                    // Depending on the object type, call the appropriate script.

                    switch (pAudioPath->m_pObject->m_ObjectType)
                    {
                    case OBJ_ENEMY:
                        m_pMusicScript->CallRoutine("PlayCube");
                        break;
                    }
                }
            }
            // Now, position the object in 3D space.
            if (pAudioPath->m_pObject && pAudioPath->m_pPath)
            {
                // Get the 3d buffer interface from the audiopath and set it's params
                IDirectSound3DBuffer* pBuffer;
                if( SUCCEEDED( pAudioPath->m_pPath->GetObjectInPath( DMUS_PCHANNEL_ALL,DMUS_PATH_BUFFER, 0,
                                                                     GUID_NULL, 0, IID_IDirectSound3DBuffer, 
                                                                     (void **) &pBuffer ) ) )
                {
                    DS3DBUFFER DS3DBuffer;
                    DS3DBuffer.dwInsideConeAngle = 360;
                    DS3DBuffer.dwMode = DS3DMODE_NORMAL;
                    DS3DBuffer.dwOutsideConeAngle = 360;
                    DS3DBuffer.dwSize = sizeof(DS3DBuffer);
                    DS3DBuffer.flMaxDistance = 10.0f;     
                    DS3DBuffer.flMinDistance = 1.0f;
                    DS3DBuffer.lConeOutsideVolume = 0;
                    DS3DBuffer.vConeOrientation = D3DXVECTOR3(0.0f,0.0f,1.0f);
                    DS3DBuffer.vPosition = pAudioPath->m_pObject->m_vPos;
                    DS3DBuffer.vVelocity = D3DXVECTOR3(0,0,0);
                    if( pAudioPath->m_pObject->m_ObjectType == OBJ_ENEMY )
                    {
                        C3DDisplayObject* p3DDisplayObject = (C3DDisplayObject*) pAudioPath->m_pObject;
                        DS3DBuffer.vVelocity = p3DDisplayObject->m_pSource->m_vCMVel;
                    }

                    pBuffer->SetAllParameters( &DS3DBuffer, DS3D_IMMEDIATE );
                    pBuffer->Release();
                }
            }
        }
*/
        RenderRadarTexture();
    }

    // Convert speed and thrust into integers that can be passed to the music script
    static long slLastThrust = 0;
    long lSpeed = (long) (D3DXVec3Length(&m_pShip->m_pSource->m_vCMVel) * 100);
    long lThrust = (long) g_pUserInput->fAxisMoveUD;

    // If the speed changed, then set the frequency of the engine based on the speed
    if( m_pEnginePath && lSpeed != m_lSpeed)
    {
        // Get the dsound buffer from the m_pEnginePath audiopath, 
        // and set its frequency based on the current speed
        IDirectSoundBuffer *pBuffer;
        if( SUCCEEDED( m_pEnginePath->GetObjectInPath( DMUS_PCHANNEL_ALL,DMUS_PATH_BUFFER,0,
                            GUID_NULL, 0, IID_IDirectSoundBuffer, (void **) &pBuffer ) ) )
        {
            pBuffer->SetFrequency( (DWORD) 22050 + (lSpeed * 200) );
            SAFE_RELEASE( pBuffer );
        }

        m_lSpeed = lSpeed;
    }

    // Tell the audio script if the thrust changed
    if( m_pMusicScript && lThrust != slLastThrust)
    {
        if (lThrust > 0)
            m_pMusicScript->CallRoutine("ThrustForward");
        else if (lThrust < 0)
            m_pMusicScript->CallRoutine("ThrustReverse");
        else 
            m_pMusicScript->CallRoutine("ThrustOff");

        slLastThrust = lThrust;
    }

    // Set the listener orientation
    if( m_p3DListener )
    {
        // Listener Parameters
        DS3DLISTENER dsListener;
        dsListener.dwSize = sizeof(dsListener);

        //Get the current 3D Parameters
        m_p3DListener->GetAllParameters(&dsListener);

        //Update the ship information
        dsListener.vPosition    = m_Camera.GetEyePt();
        dsListener.vVelocity    = m_pShip->m_pSource->m_vCMVel;
        dsListener.vOrientFront = m_Camera.GetViewDir();
        dsListener.vOrientTop   = m_Camera.GetUpVec();

        //Set the Parameters
        m_p3DListener->SetAllParameters(&dsListener,DS3D_IMMEDIATE);
    }
}




//-----------------------------------------------------------------------------
// Name: UpdateCullInfo()
// Desc: Sets up the frustum planes, endpoints, and center for the frustum
//       defined by a given view matrix and projection matrix.  This info will 
//       be used when culling each object in CullObject().
//-----------------------------------------------------------------------------
VOID CMyApplication::UpdateCullInfo( CULLINFO* pCullInfo, D3DXMATRIXA16* pMatView, 
                                     D3DXMATRIXA16* pMatProj )
{
    D3DXMATRIXA16 mat;

    D3DXMatrixMultiply( &mat, pMatView, pMatProj );
    D3DXMatrixInverse( &mat, NULL, &mat );

    pCullInfo->vecFrustum[0] = D3DXVECTOR3(-1.0f, -1.0f,  0.0f); // xyz
    pCullInfo->vecFrustum[1] = D3DXVECTOR3( 1.0f, -1.0f,  0.0f); // Xyz
    pCullInfo->vecFrustum[2] = D3DXVECTOR3(-1.0f,  1.0f,  0.0f); // xYz
    pCullInfo->vecFrustum[3] = D3DXVECTOR3( 1.0f,  1.0f,  0.0f); // XYz
    pCullInfo->vecFrustum[4] = D3DXVECTOR3(-1.0f, -1.0f,  1.0f); // xyZ
    pCullInfo->vecFrustum[5] = D3DXVECTOR3( 1.0f, -1.0f,  1.0f); // XyZ
    pCullInfo->vecFrustum[6] = D3DXVECTOR3(-1.0f,  1.0f,  1.0f); // xYZ
    pCullInfo->vecFrustum[7] = D3DXVECTOR3( 1.0f,  1.0f,  1.0f); // XYZ

    for( INT i = 0; i < 8; i++ )
        D3DXVec3TransformCoord( &pCullInfo->vecFrustum[i], &pCullInfo->vecFrustum[i], &mat );

    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[0], &pCullInfo->vecFrustum[0], 
        &pCullInfo->vecFrustum[1], &pCullInfo->vecFrustum[2] ); // Near
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[1], &pCullInfo->vecFrustum[6], 
        &pCullInfo->vecFrustum[7], &pCullInfo->vecFrustum[5] ); // Far
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[2], &pCullInfo->vecFrustum[2], 
        &pCullInfo->vecFrustum[6], &pCullInfo->vecFrustum[4] ); // Left
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[3], &pCullInfo->vecFrustum[7], 
        &pCullInfo->vecFrustum[3], &pCullInfo->vecFrustum[5] ); // Right
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[4], &pCullInfo->vecFrustum[2], 
        &pCullInfo->vecFrustum[3], &pCullInfo->vecFrustum[6] ); // Top
    D3DXPlaneFromPoints( &pCullInfo->planeFrustum[5], &pCullInfo->vecFrustum[1], 
        &pCullInfo->vecFrustum[0], &pCullInfo->vecFrustum[4] ); // Bottom
}




//-----------------------------------------------------------------------------
// Name: RenderScene()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::RenderScene()
{
    HRESULT hr;

    // Test the cooperative level to see if it's okay to render
    if( FAILED( hr = g_pd3dDevice->TestCooperativeLevel() ) )
    {
        // If the device was lost, do not render until we get it back
        if( D3DERR_DEVICELOST == hr )
            return S_OK;

        // Check if the device needs to be resized.
        if( D3DERR_DEVICENOTRESET == hr )
        {
            m_bDisplayReady = FALSE;

            InvalidateDeviceObjects();

            // Resize the device
            if( SUCCEEDED( g_pd3dDevice->Reset( &m_d3dpp ) ) )
            {
                // Initialize the app's device-dependent objects
                if( SUCCEEDED( RestoreDeviceObjects() ) )
                {
                    m_bDisplayReady = TRUE;
                    return S_OK;
                }
            }

            PostMessage( m_hWndMain, WM_CLOSE, 0, 0 );
        }
        return hr;
    }

    // Render the scene based on current state of the app
    switch( m_dwAppState )
    {
        case APPSTATE_LOADSPLASH:
            // Nothing to render while loading the splash screen
            break;

        case APPSTATE_DISPLAYSPLASH:
            RenderSplash();
            g_pd3dDevice->Present( 0, 0, 0, 0 );
            break;

        case APPSTATE_BEGINLEVELSCREEN:
            // Nothing to render while starting sound to advance a level
            break;

        case APPSTATE_DISPLAYLEVELSCREEN:
            DisplayLevelIntroScreen( m_dwLevel );
            g_pd3dDevice->Present( 0, 0, 0, 0 );
            break;

        case APPSTATE_ACTIVE:
        case APPSTATE_WAITFORMUSICEND:
            RenderFrame();
            g_pd3dDevice->Present( 0, 0, 0, 0 );
            break;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RenderFrame()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::RenderFrame()
{
    // Set the world matrix
    D3DXMATRIX matWorld;
    D3DXMatrixIdentity( &matWorld );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set the app view matrix for normal viewing
    D3DXMATRIX mView = m_Camera.GetViewMatrix();
    g_pd3dDevice->SetTransform( D3DTS_VIEW,       &mView );

    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_WRAP );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_WRAP );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,      TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,     TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, g_Profile.aThemes[m_nCurTheme].dwAmbientLight );

    m_dwNumVerts = 0;
    
    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Clear the display
        g_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, g_Profile.aThemes[m_nCurTheme].Sky.dwClearColor, 1.0f, 0L );

        g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
        
        // Render the sky
        if( m_pSkyDome && !m_bWireMode && g_Profile.bRenderSky )
        {
            D3DXMATRIX matWorld;
            D3DXMATRIX matScale;
            D3DXMATRIX matTrans;
            D3DMATERIAL9 mtrl;
            D3DUtil_InitMaterial( mtrl, 1.0f, 1.0f, 1.0f );
            g_pd3dDevice->SetMaterial( &mtrl );
            D3DXMatrixScaling( &matScale, g_Profile.aThemes[m_nCurTheme].Sky.fScaleX, g_Profile.aThemes[m_nCurTheme].Sky.fScaleY, g_Profile.aThemes[m_nCurTheme].Sky.fScaleZ );
            D3DXMatrixTranslation( &matTrans, m_Camera.GetEyePt().x, 
                                              m_Camera.GetEyePt().y + g_Profile.aThemes[m_nCurTheme].Sky.fOffsetY, 
                                              m_Camera.GetEyePt().z );

            D3DXMatrixMultiply( &matWorld, &matTrans, &matScale );

            g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,     FALSE );
            g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,     D3DBLEND_ONE );
            g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,    D3DBLEND_ZERO );
            g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,      FALSE );
            g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
            g_pd3dDevice->SetRenderState( D3DRS_FOGENABLE,    FALSE );
        
            m_Camera.SetProjParams( g_Profile.fFOV, 1.0f, 0.01f, 1000.0f ); 
            D3DXMATRIX mProj = m_Camera.GetProjMatrix();
            g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &mProj );

            g_pd3dDevice->SetTexture( 0, m_pSkyTexture );
            g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
            m_pSkyDome->Render( g_pd3dDevice );
        }

        m_Camera.SetProjParams( g_Profile.fFOV, 1.0f, 0.01f, g_Profile.fZFarDist ); 
        D3DXMATRIX mProj = m_Camera.GetProjMatrix();
        g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &mProj );

        // Set either wireframe or SOLID
        if( m_bDebugMode && m_bWireMode )
            g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
        else
            g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

        g_pd3dDevice->SetRenderState( D3DRS_FOGENABLE,    TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,      TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,     TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
        g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE,  FALSE );
        g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, g_Profile.aThemes[m_nCurTheme].dwAmbientLight );

        // Draw the terrain
        if( g_pTerrain )
            g_pTerrain->RenderFrame( &m_dwNumVerts, &m_Camera );

        g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
        
        if( m_p3DDrawManager )
            m_p3DDrawManager->Render();

        // Render the UI
        if( m_pViewportVB && g_Profile.bRenderUI )
        {
            g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,         FALSE );
            g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
            g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
            g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
            g_pd3dDevice->SetRenderState( D3DRS_FOGENABLE,        FALSE );
            g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
            g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,     TRUE );
            g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE,  TRUE );
            g_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,         0x01 );
            g_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
            g_pd3dDevice->SetTexture( 0, m_pUITexture );
            g_pd3dDevice->SetFVF( D3DFVF_SCREENVERTEX );
            g_pd3dDevice->SetStreamSource( 0, m_pViewportVB, 0, sizeof(SCREENVERTEX) );
            g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0, 2 );
        }

        // Render the Radar
        if( m_pRadarVB && g_Profile.bRenderRadar )
        {
            g_pd3dDevice->SetTexture( 0, m_pRadarTexture );
            g_pd3dDevice->SetFVF( D3DFVF_SCREENVERTEX );
            g_pd3dDevice->SetStreamSource( 0, m_pRadarVB, 0, sizeof(SCREENVERTEX) );
            g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0, 2 );
        }

        // Render UI text
        TCHAR strBuffer[MAX_PATH];
        DWORD dwTextColor = 0xFFFFFF00;

        // Display enemy count
        if( m_pGameFont && g_pTerrain )
        {
            _stprintf( strBuffer, _T("%d"), g_pTerrain->m_dwEnemyCount );
            m_pGameFont->DrawTextScaled( 0.63f, -0.7f, 0.9f, 0.05f, 0.05f,
                                        dwTextColor, strBuffer, D3DFONT_FILTERED );
        }
/*
        // Display shield
        if( m_pGameFont && g_pTerrain )
        {
            _stprintf( strBuffer, _T("%0.0f"), m_pShip->m_fShield );
            m_pGameFont->DrawTextScaled( 0.63f, 0.0f, 0.9f, 0.05f, 0.05f,
                                        dwTextColor, strBuffer, D3DFONT_FILTERED );
        }
*/
        // Render any text
        if( m_bDebugMode && g_Profile.dwRenderText > 0 )
        {
            dwTextColor = 0xFFFFFF00;

            DWORD dwNumZonesInView = 0;
            if( g_pTerrain )
                dwNumZonesInView = g_pTerrain->m_dwNumZonesInView;

            _stprintf( strBuffer, _T("Tris=%d FPS=%.02f Zones=%d"), m_dwNumVerts, m_fFPS, dwNumZonesInView );
            m_pGameFont->DrawTextScaled( -1.0f, -1.0f, 0.9f, 0.05f, 0.05f,
                                         dwTextColor, strBuffer, D3DFONT_FILTERED );

            if( g_Profile.dwRenderText == 1 && m_pShip )
            {
                _stprintf( strBuffer, _T("CM P=(%0.1f,%0.1f,%0.1f) V=(%0.1f,%0.1f,%0.1f) A=(%0.1f,%0.1f,%0.1f)"), 
                            m_pShip->m_pSource->m_vCMPos.x, m_pShip->m_pSource->m_vCMPos.y, m_pShip->m_pSource->m_vCMPos.z, 
                            m_pShip->m_pSource->m_vCMVel.x, m_pShip->m_pSource->m_vCMVel.y, m_pShip->m_pSource->m_vCMVel.z,
                            m_pShip->m_pSource->m_vCMAcc.x, m_pShip->m_pSource->m_vCMAcc.y, m_pShip->m_pSource->m_vCMAcc.z );
                m_pGameFont->DrawTextScaled( -1.0f, 0.6f, 0.9f, 0.05f, 0.05f,
                                             dwTextColor, strBuffer, D3DFONT_FILTERED );

                _stprintf( strBuffer, _T("O=(%0.1f,%0.1f,%0.1f,%0.1f) AV=(%0.1f,%0.1f,%0.1f) AA=(%0.1f,%0.1f,%0.1f)"), 
                    m_pShip->m_pSource->m_qOrientation.x, m_pShip->m_pSource->m_qOrientation.y, m_pShip->m_pSource->m_qOrientation.z, m_pShip->m_pSource->m_qOrientation.w,
                    m_pShip->m_pSource->m_vAngularVel.x, m_pShip->m_pSource->m_vAngularVel.y, m_pShip->m_pSource->m_vAngularVel.z, 
                    m_pShip->m_pSource->m_vAngularMomentum.x, m_pShip->m_pSource->m_vAngularMomentum.y, m_pShip->m_pSource->m_vAngularMomentum.z );
                m_pGameFont->DrawTextScaled( -1.0f, 0.7f, 0.9f, 0.05f, 0.05f,
                                             dwTextColor, strBuffer, D3DFONT_FILTERED );

                // Display Object Count
                if( g_pTerrain )
                {
                    _stprintf( strBuffer, _T("Objects: %03ld"), g_pTerrain->m_dwObjectCount );
                    m_pGameFont->DrawTextScaled( -1.0f, 0.9f, 0.9f, 0.05f, 0.05f,
                                                dwTextColor, strBuffer, D3DFONT_FILTERED );
                }
            }
        }

        // Render "Paused" text if game is paused
        if( m_bPaused && m_pGameFont && !m_bDebugMode )
        {
            DarkenScene( 0.5f );
            g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
            g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
            m_pGameFont->DrawTextScaled( -0.3f, 0.0f, 0.9f, 0.10f, 0.10f, 0xffffffff, _T("Paused"), D3DFONT_FILTERED|D3DFONT_CENTERED_X|D3DFONT_CENTERED_Y );
        }

//        if( m_pShip->fShowDelay > 0.0f )
//            DarkenScene( m_pShip->fShowDelay/2.0f );

        // Render game menu
        if( m_pCurrentMenu )
        {
            DarkenScene( 0.5f );
            m_pCurrentMenu->Render( m_pMenuFont );
        }

        g_pd3dDevice->EndScene();
    }


    static FLOAT fLastTime = 0.0f;
    static DWORD dwFrames  = 0L;
    FLOAT fTime = DXUtil_Timer( TIMER_GETABSOLUTETIME );
    ++dwFrames;

    // Update the scene stats once per second
    if( fTime - fLastTime > 1.0f )
    {
        m_fFPS    = dwFrames / (fTime - fLastTime);
        fLastTime = fTime;
        dwFrames  = 0L;
    }

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::InvalidateDeviceObjects()
{
    if( m_p3DDrawManager )
        m_p3DDrawManager->InvalidateDeviceObjects();
    if( m_pSkyDome )
        m_pSkyDome->InvalidateDeviceObjects();
    if( g_pTerrain )
        g_pTerrain->InvalidateDeviceObjects();
    if( m_pGameFont )
        m_pGameFont->InvalidateDeviceObjects();
    if( m_pMenuFont )
        m_pMenuFont->InvalidateDeviceObjects();

    // Invalidate the enemy models
    for( int iEnemy=0; iEnemy<g_Profile.nNumEnemies; iEnemy++ )
    {
        C3DModel* pModel = g_Profile.aEnemyStyles[iEnemy].pModel;
        if( pModel )
            pModel->InvalidateDeviceObjects();
    }

    C3DModel* pModel = g_Profile.Blaster.pModel;
    if( pModel )
        pModel->InvalidateDeviceObjects();

    SAFE_RELEASE( m_pRadarTexture );
    SAFE_RELEASE( m_pTempRadarTexture );

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::DeleteDeviceObjects()
{
    if( m_p3DDrawManager )
        m_p3DDrawManager->DeleteDeviceObjects();

    SAFE_RELEASE( g_Profile.Blaster.pParticleTexture );
    SAFE_RELEASE( m_pSkyTexture );
    SAFE_RELEASE( m_pUITexture );
    SAFE_RELEASE( m_pSplashTexture );

    SAFE_DELETE( m_pGameFont );
    SAFE_DELETE( m_pMenuFont );

    if( g_pTerrain != NULL )
    {
        g_pTerrain->InvalidateDeviceObjects();
        g_pTerrain->DeleteDeviceObjects();
        g_pTerrain->FinalCleanup();
        m_pShip = NULL;
        SAFE_DELETE( m_pShipModel );
    }

    SAFE_DELETE( g_pTerrain );
    SAFE_DELETE( m_pSkyDome );

    SAFE_RELEASE( m_pViewportVB );
    SAFE_RELEASE( m_pRadarVB );

    for( int iEnemy=0; iEnemy<g_Profile.nNumEnemies; iEnemy++ )
    {
        C3DModel* pModel = g_Profile.aEnemyStyles[iEnemy].pModel;
        if( pModel )
            pModel->DeleteDeviceObjects();
        SAFE_DELETE( g_Profile.aEnemyStyles[iEnemy].pModel );
    }

    C3DModel* pModel = g_Profile.Blaster.pModel;
    if( pModel )
    {
        pModel->DeleteDeviceObjects();
        SAFE_DELETE( g_Profile.Blaster.pModel );
    }

    SAFE_RELEASE( g_pd3dDevice );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Cleanup everything
//-----------------------------------------------------------------------------
VOID CMyApplication::FinalCleanup()
{
    InvalidateDeviceObjects();
    DeleteDeviceObjects();
    DestroySoundObjects();
    SAFE_DELETE( m_pInputManager );
    SAFE_DELETE( m_p3DDrawManager );
    DestroyMenus();

    if( m_pFileWatch )
    {
        m_pFileWatch->Cleanup();
        SAFE_DELETE( m_pFileWatch );
    }
}




//-----------------------------------------------------------------------------
// Name: AdvanceLevel()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::AdvanceLevel()
{
    // Up the level
    m_dwLevel++;

    srand( timeGetTime() );

    // Clear any stray objects (anything but the ship) out of the display list
    if( g_pTerrain )
        g_pTerrain->ClearStrayObjects();

    // Reset ship position
    if( m_pShip )
    {
        D3DXVECTOR3 vPos;
        vPos.x = rnd(0.0f,1.0f)*ZONE_WIDTH*g_pTerrain->m_dwWorldWidth;
        vPos.z = rnd(0.0f,1.0f)*ZONE_HEIGHT*g_pTerrain->m_dwWorldHeight;   
        vPos.y = g_pTerrain->GetHeight( vPos.x, vPos.z ) + 10.0f;
        m_pShip->m_pSource->m_vCMPos      = vPos;
        m_pShip->m_pSource->m_vAngularVel = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
        m_pShip->m_pSource->m_vCMVel      = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
        m_pShip->m_vEulerAngles           = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    }

    // Create donuts for the new level
    for( WORD i=0; i<(g_Profile.nNumEnemiesPerLevelScale*m_dwLevel+g_Profile.nNumEnemiesBase); i++ )
    {
        DWORD dwEnemyStyle;
        if( g_Profile.bForceEnemySelect )
            dwEnemyStyle = g_Profile.nSelectEnemy;
        else
            dwEnemyStyle = rand() % g_Profile.nNumEnemies;

        CreateEnemy( dwEnemyStyle, NULL, rnd(-D3DX_PI,D3DX_PI) );
    }
}



//-----------------------------------------------------------------------------
// Name: DarkenScene()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::DarkenScene( FLOAT fAmount )
{
    if( g_pd3dDevice==NULL )
        return;

    // Setup a dark square to cover the scene
    DWORD dwAlpha = (fAmount<1.0f) ? ((DWORD)(255*fAmount))<<24L : 0xff000000;
    SCREENVERTEX* v;
    m_pViewportVB->Lock( 0, 0, (void**)&v, 0 );
    v[0].color = v[1].color = v[2].color = v[3].color = dwAlpha;
    m_pViewportVB->Unlock();

    // Set renderstates
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
    g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,   FALSE );
    g_pd3dDevice->SetTexture( 0, NULL );

    // Draw a big, gray square
    g_pd3dDevice->SetFVF( D3DFVF_SCREENVERTEX );
    g_pd3dDevice->SetStreamSource( 0, m_pViewportVB, 0, sizeof(SCREENVERTEX) );
    g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0, 2 );

    // Restore states
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );

    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP );
}




//-----------------------------------------------------------------------------
// Name: DisplayLevelIntroScreen()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::DisplayLevelIntroScreen( DWORD dwLevel )
{
    if( g_pd3dDevice==NULL )
        return;

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Erase the screen
        g_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0, 1.0f, 0L );
        g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
        g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

        TCHAR strLevel[80];
        _stprintf( strLevel, _T("Level %ld"), dwLevel );

        m_pGameFont->DrawTextScaled( -0.3f, 0.0f, 0.9f, 0.10f, 0.10f, 0xffffffff, strLevel, D3DFONT_FILTERED|D3DFONT_CENTERED_X|D3DFONT_CENTERED_Y );

        DarkenScene( 1.0f - sinf(D3DX_PI*DXUtil_Timer( TIMER_GETAPPTIME )/3.0f) );

        // End the scene
        g_pd3dDevice->EndScene();
    }
}



//-----------------------------------------------------------------------------
// Name: RenderSplash()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::RenderSplash()
{
    // Set the world matrix
    D3DXMATRIX matWorld;
    D3DXMatrixIdentity( &matWorld );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set the app view matrix for normal viewing
    D3DXMATRIX mView = m_Camera.GetViewMatrix();
    g_pd3dDevice->SetTransform( D3DTS_VIEW,       &mView );

    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,      TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,     TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, g_Profile.aThemes[m_nCurTheme].dwAmbientLight );

    m_dwNumVerts = 0;
    
    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Clear the display
        g_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, g_Profile.aThemes[m_nCurTheme].Sky.dwClearColor, 1.0f, 0L );
       
        // Render the UI
        g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
        g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,         FALSE );
        g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
        g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
        g_pd3dDevice->SetRenderState( D3DRS_FOGENABLE,        FALSE );
        g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,     TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE,  TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,         0x01 );
        g_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
        g_pd3dDevice->SetTexture( 0, m_pSplashTexture );
        g_pd3dDevice->SetFVF( D3DFVF_SCREENVERTEX );
        g_pd3dDevice->SetStreamSource( 0, m_pViewportVB, 0, sizeof(SCREENVERTEX) );
        g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,0, 2 );

        g_pd3dDevice->EndScene();
    }

    static FLOAT fLastTime = 0.0f;
    static DWORD dwFrames  = 0L;
    FLOAT fTime = DXUtil_Timer( TIMER_GETABSOLUTETIME );
    ++dwFrames;

    // Update the scene stats once per second
    if( fTime - fLastTime > 1.0f )
    {
        m_fFPS    = dwFrames / (fTime - fLastTime);
        fLastTime = fTime;
        dwFrames  = 0L;
    }
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::ConstructMenus()
{
    // Build video sub menu
    CMenuItem* pVideoSubMenu = new CMenuItem( _T("Video Menu"), MENU_VIDEO );
    if( NULL == pVideoSubMenu )
        return;

    pVideoSubMenu->Add( new CMenuItem( _T("Windowed"), MENU_WINDOWED ) );
    pVideoSubMenu->Add( new CMenuItem( _T("640x480"),  MENU_640x480 ) );
    pVideoSubMenu->Add( new CMenuItem( _T("800x600"),  MENU_800x600 ) );
    pVideoSubMenu->Add( new CMenuItem( _T("1024x768"), MENU_1024x768 ) );
    pVideoSubMenu->Add( new CMenuItem( _T("Back"),     MENU_BACK ) );

    // Build sound menu
    CMenuItem* pSoundSubMenu = new CMenuItem( _T("Sound Menu"), MENU_SOUND );
    if( NULL == pSoundSubMenu )
        return;
    pSoundSubMenu->Add( new CMenuItem( _T("Sound On"),  MENU_SOUNDON ) );
    pSoundSubMenu->Add( new CMenuItem( _T("Sound Off"), MENU_SOUNDOFF ) );
    pSoundSubMenu->Add( new CMenuItem( _T("Back"),      MENU_BACK ) );

    // Build input menu
    CMenuItem* pInputSubMenu = new CMenuItem( _T("Input Menu"), MENU_INPUT );
    if( NULL == pInputSubMenu )
        return;
    pInputSubMenu->Add( new CMenuItem( _T("View Devices"),   MENU_VIEWDEVICES ) );
    pInputSubMenu->Add( new CMenuItem( _T("Config Devices"), MENU_CONFIGDEVICES ) );
    pInputSubMenu->Add( new CMenuItem( _T("Back"),           MENU_BACK ) );

    // Build main menu
    m_pMainMenu = new CMenuItem( _T("Main Menu"),  MENU_MAIN );
    if( NULL == m_pMainMenu )
        return;
    m_pMainMenu->Add( new CMenuItem( _T("Resume"), MENU_BACK ) );
    m_pMainMenu->Add( pVideoSubMenu );
    m_pMainMenu->Add( pSoundSubMenu );
    m_pMainMenu->Add( pInputSubMenu );
    m_pMainMenu->Add( new CMenuItem( _T("Quit"), MENU_QUIT ) );

    return;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::DestroyMenus()
{
    SAFE_DELETE( m_pQuitMenu );
    SAFE_DELETE( m_pMainMenu );
}




//-----------------------------------------------------------------------------
// Name: UpdateMenus()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::UpdateMenus()
{
    if( m_pCurrentMenu == NULL )
        return;

    CInputManager::UserInput* pUserInput = NULL;
    pUserInput = m_pInputManager->GetUserInput();

    // Keep track of current selected menu, to check later for changes
    //DWORD dwCurrentSelectedMenu = m_pCurrentMenu->dwSelectedMenu;

    // Check for menu up/down input
    if( pUserInput->bDoMenuUp )
    {
        pUserInput->bDoMenuUp = FALSE;
        if( m_pCurrentMenu->dwSelectedMenu > 0 )
            m_pCurrentMenu->dwSelectedMenu--;
        else
            m_pCurrentMenu->dwSelectedMenu = m_pCurrentMenu->dwNumChildren - 1;
    }
    else if( pUserInput->bDoMenuDown )
    {
        pUserInput->bDoMenuDown = FALSE;
        if( (m_pCurrentMenu->dwSelectedMenu+1) < m_pCurrentMenu->dwNumChildren )
            m_pCurrentMenu->dwSelectedMenu++;
        else
            m_pCurrentMenu->dwSelectedMenu = 0;
    }

    // The the current menu changed, play a sound
//    if( dwCurrentSelectedMenu != m_pCurrentMenu->dwSelectedMenu )
//        PlaySoundEffect( m_pExplosionSphereSound, &g_Profile.ExplosionSphere);

    if( pUserInput->bDoMenuSelect )
    {
        pUserInput->bDoMenuSelect = FALSE;
//        PlaySoundEffect( m_pExplosionSphereSound, &g_Profile.ExplosionSphere);

        DWORD dwID = m_pCurrentMenu->pChild[m_pCurrentMenu->dwSelectedMenu]->dwID;

        switch( dwID )
        {
            case MENU_BACK:
                m_pCurrentMenu = m_pCurrentMenu->pParent;
                break;

            case MENU_VIDEO:
            case MENU_SOUND:
            case MENU_INPUT:
                m_pCurrentMenu = m_pCurrentMenu->pChild[m_pCurrentMenu->dwSelectedMenu];
                break;

            case MENU_WINDOWED:
                SwitchDisplayModes( FALSE, 0L, 0L );
                m_pCurrentMenu = NULL;
                break;

            case MENU_640x480:
                SwitchDisplayModes( TRUE, 640, 480 );
                m_pCurrentMenu = NULL;
                break;

            case MENU_800x600:
                SwitchDisplayModes( TRUE, 800, 600 );
                m_pCurrentMenu = NULL;
                break;

            case MENU_1024x768:
                SwitchDisplayModes( TRUE, 1024, 768 );
                m_pCurrentMenu = NULL;
                break;

            case MENU_SOUNDON:
                if( m_pMusicManager == NULL )
                    CreateSoundObjects( m_hWndMain );
                m_pCurrentMenu = NULL;
                break;

            case MENU_SOUNDOFF:
                if( m_pMusicManager )
                    DestroySoundObjects();
                m_pCurrentMenu = NULL;
                break;

            case MENU_VIEWDEVICES:
            {
                m_bMouseVisible = TRUE;
                DXUtil_Timer( TIMER_STOP );

                if( m_pInputManager )
                    m_pInputManager->ViewDevices();

                m_bMouseVisible = FALSE;
                DXUtil_Timer( TIMER_START );

                m_pCurrentMenu = NULL;
                break;
            }

            case MENU_CONFIGDEVICES:
            {
                m_bMouseVisible = TRUE;
                DXUtil_Timer( TIMER_STOP );

                if( m_pInputManager )
                    m_pInputManager->ConfigDevices();

                DXUtil_Timer( TIMER_START );
                m_bMouseVisible = FALSE;

                m_pCurrentMenu = NULL;
                break;
            }

            case MENU_QUIT:
                PostMessage( m_hWndMain, WM_CLOSE, 0, 0 );
                m_pCurrentMenu = NULL;
                break;
        }
    }

    // Check if the menu system is being exitted
    if( pUserInput->bDoMenuQuit )
    {
        pUserInput->bDoMenuQuit = FALSE;
        m_pCurrentMenu = NULL;
    }

    // If the menu is going away, go back to game play actions
//    if( m_pCurrentMenu == NULL )
//        m_pInputDeviceManager->SetActionFormat( m_diafGame, FALSE );
}




//-----------------------------------------------------------------------------
// Display support code (using Direct3D functionality from D3DUtil.h)
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
// Name: ReloadWorld()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::ReloadWorld()
{
    InvalidateDeviceObjects();
    DeleteDeviceObjects();
    FinalCleanup();

    g_Profile.GetProfile( m_strProfilePath );

    OneTimeSceneInit( m_hWndMain );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SwitchDisplayModes()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::SwitchDisplayModes( BOOL bFullScreen, DWORD dwWidth, DWORD dwHeight )
{
    HRESULT hr;

    if( FALSE==m_bIsActive || FALSE==m_bDisplayReady )
        return S_OK;

    // Check to see if a change was actually requested
    if( bFullScreen )
    {
        if( m_dwScreenWidth==dwWidth && m_dwScreenHeight==dwHeight &&
            m_bFullScreen==bFullScreen )
            return S_OK;
    }
    else
    {
//        if( m_bFullScreen == FALSE )
//            return S_OK;
    }
    
    // Invalidate the old display objects
    m_bDisplayReady = FALSE;
    InvalidateDeviceObjects();

    if( bFullScreen )
    {
        // Set windowed-mode style
        SetWindowLong( m_hWndMain, GWL_STYLE, m_dwWindowStyle|WS_VISIBLE );
    }
    else
    {
        // Set fullscreen-mode style
        SetWindowLong( m_hWndMain, GWL_STYLE, WS_POPUP|WS_SYSMENU|WS_VISIBLE );
    }
    
    // Set up the new presentation paramters
    if( bFullScreen )
    {
        m_d3dpp.Windowed         = FALSE;
        m_d3dpp.hDeviceWindow    = m_hWndMain;
        m_d3dpp.BackBufferWidth  = m_dwScreenWidth  = dwWidth;
        m_d3dpp.BackBufferHeight = m_dwScreenHeight = dwHeight;

        m_d3dpp.BackBufferFormat = m_d3dfmtFullscreen;
    }
    else
    {
        m_d3dpp.Windowed         = TRUE;
        m_d3dpp.hDeviceWindow    = NULL;
        m_d3dpp.BackBufferWidth  = 0L;
        m_d3dpp.BackBufferHeight = 0L;

        m_d3dpp.BackBufferFormat = m_DesktopMode.Format;
    }

    // Reset the device
    if( SUCCEEDED( hr = g_pd3dDevice->Reset( &m_d3dpp ) ) )
    {
        m_bFullScreen   = bFullScreen;
        if( SUCCEEDED( hr = RestoreDeviceObjects() ) )
        {
            m_bDisplayReady = TRUE;
            return S_OK;
        }
    }

    // If we get here, a fatal error occurred
    PostMessage( m_hWndMain, WM_CLOSE, 0, 0 );
    return E_FAIL;
}




//-----------------------------------------------------------------------------
// Sound support code (using DMusic functionality from DMUtil.h)
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
// Name: CreateSoundObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::CreateSoundObjects( HWND hWnd )
{
    HRESULT hr;

    // Create the music manager class, used to create the sounds
    m_pMusicManager = new CMusicManager();
    if( NULL == m_pMusicManager )
        return DXTRACE_ERR( TEXT("new"), E_OUTOFMEMORY );
    if( FAILED( hr = m_pMusicManager->Initialize( hWnd, 128, DMUS_APATH_DYNAMIC_STEREO, NULL ) ) )
        return DXTRACE_ERR( TEXT("m_pMusicManager->Initialize"), hr );

    // Instruct the music manager where to find the files
    TCHAR strSearchPath[MAX_PATH];
    lstrcpyn( strSearchPath, m_strCurrentWorkingDir, MAX_PATH-10 );
    lstrcat( strSearchPath, TEXT("\\audio") );
    m_pMusicManager->SetSearchDirectory( strSearchPath );

    // Set up scripting
    if( FAILED( hr = m_pMusicManager->CreateScriptFromFile( &m_pMusicScript, g_Profile.szAudioScript ) ) )
        return DXTRACE_ERR( TEXT("m_pMusicManager->CreateScriptFromFile"), hr );

    // Just in case there's anything that needs to be initialized in the script.
    if( FAILED( hr = m_pMusicScript->CallRoutine( "Init" ) ) )
        return DXTRACE_ERR( TEXT("m_pMusicScript->CallRoutine"), hr );

    // One thing the script does in Init is create an audiopath for the engine.
    // We need to retrieve it so we can access the buffer and call SetFrequency in response to 
    // speed changes.
    if( m_pMusicScript )
        m_pMusicScript->GetVariableObject( "EnginePath", IID_IDirectMusicAudioPath, (void **) &m_pEnginePath );

    // For lyric notifications, we need to insert a CNotifyTool in the performance graph. This ensures
    // that it receives lyrics generated by any segment on any audiopath.
    IDirectMusicAudioPath *pPath;
    if (SUCCEEDED(m_pMusicManager->GetPerformance()->GetDefaultAudioPath( &pPath ) ) )
    {
        IDirectMusicGraph *pGraph;
        if (SUCCEEDED(pPath->GetObjectInPath( 0, DMUS_PATH_PERFORMANCE_GRAPH, 0, 
                    CLSID_DirectMusicGraph, 0, IID_IDirectMusicGraph, (void **)&pGraph ) ) )
        {
            CNotifyTool *pTool = new CNotifyTool( this );
            if (pTool)
            {
                pGraph->InsertTool((IDirectMusicTool*) pTool,NULL,0,0); 
                pTool->Release();
            }
            pGraph->Release();
        }
    }

    // Create the audiopaths. These will be used to manage sound for the flying objects.
    for (DWORD dwX = 0; dwX < MAX_AUDIOPATHS; dwX++)
        m_pMusicManager->GetPerformance()->CreateStandardAudioPath( DMUS_APATH_DYNAMIC_3D, 16, 
                                                                    FALSE, &m_AudioPath[dwX].m_pPath );
    UpdateFarthestAudioPath();

    // Create the Sounds    
    m_pMusicManager->CreateSegmentFromFile( &m_pBullet1Sound, g_Profile.Blaster.szFile, TRUE, FALSE ); 
    m_pMusicManager->CreateSegmentFromFile( &m_pExplosionDonutSound, g_Profile.ExplosionDonut.szFile, TRUE, FALSE ); 

    m_p3DListener = m_pMusicManager->GetListener();
    m_pMusicManager->Set3DParameters( g_Profile.flDistanceFactor, g_Profile.flDopplerFactor, g_Profile.flRolloffFactor );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DestroySoundObjects()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::DestroySoundObjects()
{
    SAFE_DELETE( m_pMusicScript );
    for (DWORD dwI = 0; dwI < MAX_AUDIOPATHS; dwI++)  
        SAFE_RELEASE(m_AudioPath[dwI].m_pPath); 
    SAFE_RELEASE( m_pEnginePath );

    SAFE_DELETE( m_pBullet1Sound );
    SAFE_DELETE( m_pExplosionDonutSound );

    SAFE_DELETE( m_pMusicManager );
}




//-----------------------------------------------------------------------------
// Input support code (using DInput functionality from DIUtil.h)
//-----------------------------------------------------------------------------







//-----------------------------------------------------------------------------
// Error handling
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
// Name: CleanupAndDisplayError()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::CleanupAndDisplayError( DWORD dwError, TCHAR* strArg1, TCHAR* strArg2 )
{
    TCHAR* strDbgOut = NULL;
    TCHAR* strMsgBox = NULL;

    // Cleanup the app
    InvalidateDeviceObjects();
    DeleteDeviceObjects();
    FinalCleanup();

    // Make the cursor visible
    SetCursor( LoadCursor( NULL, IDC_ARROW ) );
    m_bMouseVisible = TRUE;

    // Get the appropriate error strings
    switch( dwError )
    {
        case DONUTSERR_NODIRECT3D:
            strDbgOut = _T("Could not create Direct3D\n");
            strMsgBox = _T("Could not create Direct3D.\n\n")
                        _T("Please make sure you have the latest DirectX\n")
                        _T(".dlls installed on your system.");
            break;
        case DONUTSERR_NOD3DDEVICE:
            strDbgOut = _T("Could not create a Direct3D device\n");
            strMsgBox = _T("Could not create a Direct3D device. Your\n")
                        _T("graphics accelerator is not sufficient to\n")
                        _T("run this demo, or your desktop is using\n")
                        _T("a color format that cannot be accelerated by\n")
                        _T("your graphics card (try 16-bit mode).");
            break;
        case DONUTSERR_ARTLOADFAILED:            
            strDbgOut = _T("Could not load game art\n");
            strMsgBox = _T("Couldn't load game art %s in %s. ")
                        _T("Either your graphics hardware does not have ")
                        _T("sufficient resources, or the DirectX SDK was ")
                        _T("not properly installed.");
            break;
        case DONUTSERR_NOINPUT:
            strDbgOut = _T("Could not create input objects\n");
            strMsgBox = _T("Could not create input objects.");
            break;
    }

    // Output the error strings
    if( strDbgOut && strMsgBox )
    {
        OutputDebugString( strDbgOut );
        TCHAR strMsg[512];
        _sntprintf( strMsg, 512, strMsgBox, strArg1, strArg2 );
        strMsg[511]=0;
        MessageBox( m_hWndMain, strMsg, m_strAppName, MB_OK );
    }
}




//-----------------------------------------------------------------------------
// Name: CreateEnemy()
// Desc:
//-----------------------------------------------------------------------------
VOID CMyApplication::CreateEnemy( DWORD dwEnemyStyle, D3DXVECTOR3* pvPosition, float fRotateY )
{
    D3DVECTOR vPosition; 
    if( !g_pTerrain )
        return;

    CEnemyStyle* pEnemyStyle = &g_Profile.aEnemyStyles[ dwEnemyStyle ];

    if( pvPosition )
    {
        vPosition = *pvPosition;
    }
    else
    {
        vPosition = D3DXVECTOR3( rnd(0.0f,1.0f)* (g_pTerrain->m_dwWorldWidth  * ZONE_WIDTH), 
                                 10.0f, 
                                 rnd(0.0f,1.0f)* (g_pTerrain->m_dwWorldHeight * ZONE_HEIGHT) );
        vPosition.y += g_pTerrain->GetHeight( vPosition.x, vPosition.z );
    }

    CEnemyShip* pEnemy = new CEnemyShip();
    if( NULL == pEnemy )
        return;

    if( g_pDebugFirstEnemy == NULL )
        g_pDebugFirstEnemy = pEnemy;

    D3DXMATRIX mOrientation;
    D3DXMatrixRotationY( &mOrientation, fRotateY );
    pEnemy->OneTimeSceneInit( 0, vPosition, &mOrientation, pEnemyStyle->pModel );
    pEnemy->InitDeviceObjects( );
    pEnemy->RestoreDeviceObjects();

    g_pTerrain->AddDisplayObject( pEnemy );
}




//-----------------------------------------------------------------------------
// Name: RenderRadarTexture()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::RenderRadarTexture()
{
   if( NULL == g_pTerrain )
        return S_OK;

    return g_pTerrain->RenderRadar( m_pRadarTexture, m_pTempRadarTexture );
}




//-----------------------------------------------------------------------------
// Name: FindMediaFileCch()
// Desc: Look for media in based on common places with the exe will be
//-----------------------------------------------------------------------------
HRESULT CMyApplication::FindMediaFileCch( TCHAR* strPath, const long cchPath, const TCHAR* strFile )
{
    TCHAR strDestPath[MAX_PATH];
    long cchDestPath;
    TCHAR* strShortNameTmp;
    HANDLE file;

    // Try ..\Donuts4\media   
    lstrcpyn(strDestPath, TEXT("..\\Donuts4\\media\\"), MAX_PATH);
    if( lstrlen(strDestPath) + lstrlen(strFile) < cchPath )
        lstrcat(strDestPath, strFile);
    cchDestPath = GetFullPathName(strDestPath, cchPath, strPath, &strShortNameTmp);
    file = CreateFile( strPath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                       OPEN_EXISTING, 0, NULL );
    if( INVALID_HANDLE_VALUE != file )
    {
        CloseHandle( file );
        return S_OK;
    }

    // Try current working dir
    lstrcpyn(strDestPath, TEXT(".\\"), MAX_PATH);
    if( lstrlen(strDestPath) + lstrlen(strFile) < cchPath )
        lstrcat(strDestPath, strFile);
    cchDestPath = GetFullPathName(strDestPath, cchPath, strPath, &strShortNameTmp);
    file = CreateFile( strPath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                       OPEN_EXISTING, 0, NULL );
    if( INVALID_HANDLE_VALUE != file )
    {
        CloseHandle( file );
        return S_OK;
    }
    
    // Try .\media 
    lstrcpyn(strDestPath, TEXT(".\\media\\"), MAX_PATH);
    if( lstrlen(strDestPath) + lstrlen(strFile) < cchPath )
        lstrcat(strDestPath, strFile);
    cchDestPath = GetFullPathName(strDestPath, cchPath, strPath, &strShortNameTmp);
    file = CreateFile( strPath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                       OPEN_EXISTING, 0, NULL );
    if( INVALID_HANDLE_VALUE != file )
    {
        CloseHandle( file );
        return S_OK;
    }

    // Try ..\media 
    lstrcpyn(strDestPath, TEXT("..\\media\\"), MAX_PATH);
    if( lstrlen(strDestPath) + lstrlen(strFile) < cchPath )
        lstrcat(strDestPath, strFile);
    cchDestPath = GetFullPathName(strDestPath, cchPath, strPath, &strShortNameTmp);
    file = CreateFile( strPath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                       OPEN_EXISTING, 0, NULL );
    if( INVALID_HANDLE_VALUE != file )
    {
        CloseHandle( file );
        return S_OK;
    }

    // Try ..\..\media 
    lstrcpyn(strDestPath, TEXT("..\\..\\media\\"), MAX_PATH);
    if( lstrlen(strDestPath) + lstrlen(strFile) < cchPath )
        lstrcat(strDestPath, strFile);
    cchDestPath = GetFullPathName(strDestPath, cchPath, strPath, &strShortNameTmp);
    file = CreateFile( strPath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                       OPEN_EXISTING, 0, NULL );
    if( INVALID_HANDLE_VALUE != file )
    {
        CloseHandle( file );
        return S_OK;
    }

    // Try \dxsdk\samples\c++\Demos\donuts4\media folder
    const TCHAR* strDonutsMedia = TEXT("..\\C++\\Demos\\Donuts4\\media\\");
    if( FAILED( DXUtil_GetDXSDKMediaPathCch( strDestPath, cchPath ) ) )
        return E_FAIL;
    if( lstrlen(strDestPath) + lstrlen(strDonutsMedia) < cchPath )
        lstrcat(strDestPath, strDonutsMedia);
    if( lstrlen(strDestPath) + lstrlen(strFile) < cchPath )
        lstrcat(strDestPath, strFile);
    cchDestPath = GetFullPathName(strDestPath, cchPath, strPath, &strShortNameTmp);
    file = CreateFile( strPath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                       OPEN_EXISTING, 0, NULL );
    if( INVALID_HANDLE_VALUE != file )
    {
        CloseHandle( file );
        return S_OK;
    }

    return E_FAIL;
}




//-----------------------------------------------------------------------------
// Name: UpdateFarthestAudioPath()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyApplication::UpdateFarthestAudioPath()
{
    FLOAT fMax = 0.0;
    DWORD dwX;
    DWORD dwBest = 0;
    for (dwX = 0; dwX < MAX_AUDIOPATHS; dwX++)
    {
        if (m_AudioPath[dwX].m_fDistance > fMax)
        {
            fMax = m_AudioPath[dwX].m_fDistance;
            dwBest = dwX;
        }
    }

    m_pFarthestAudioPath = &m_AudioPath[dwBest];

    return S_OK;
}
