//-----------------------------------------------------------------------------
// File: [!output PROJECT_NAME].cpp
//
// Desc: DirectX MFC dialog application created by the DirectX AppWizard
//-----------------------------------------------------------------------------
#define STRICT
[!if DINPUT]
#define DIRECTINPUT_VERSION 0x0800
[!endif]
#include "stdafx.h"
#include "[!output PROJECT_NAME].h"




//-----------------------------------------------------------------------------
// Application globals
//-----------------------------------------------------------------------------
TCHAR*          g_strAppTitle       = _T( "[!output PROJECT_NAME]" );
CApp            g_App;
HINSTANCE       g_hInst = NULL;
CAppForm*       g_AppFormView = NULL;




//-----------------------------------------------------------------------------
// The MFC macros are all listed here
//-----------------------------------------------------------------------------
IMPLEMENT_DYNCREATE( CAppDoc,      CDocument )
IMPLEMENT_DYNCREATE( CAppFrameWnd, CFrameWnd )
IMPLEMENT_DYNCREATE( CAppForm,     CFormView )




BEGIN_MESSAGE_MAP( CApp, CWinApp )
    //{{AFX_MSG_MAP(CApp)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()




BEGIN_MESSAGE_MAP( CAppForm, CFormView )
    //{{AFX_MSG_MAP(CAppForm)
    ON_COMMAND(    IDC_VIEWFULLSCREEN, OnToggleFullScreen )
    ON_BN_CLICKED(IDC_CHANGEDEVICE, OnChangeDevice)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()




BEGIN_MESSAGE_MAP(CAppDoc, CDocument)
    //{{AFX_MSG_MAP(CAppDoc)
            // NOTE - the ClassWizard will add and remove mapping macros here.
            //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()




BEGIN_MESSAGE_MAP(CAppFrameWnd, CFrameWnd)
    //{{AFX_MSG_MAP(CAppFrameWnd)
    ON_COMMAND(IDM_CHANGEDEVICE, OnChangeDevice)
[!if ACTIONMAPPER]
    ON_COMMAND(IDM_CONFIGINPUT, OnConfigInput)
[!endif]
[!if DPLAYVOICE]
    ON_COMMAND(IDM_CONFIGVOICE, OnConfigVoice)
[!endif]
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()




//-----------------------------------------------------------------------------
// Name: CAppForm()
// Desc: Constructor for the dialog resource form.  Paired with ~CAppForm()
//       Member variables should be initialized to a known state here.  
//       The application window has not yet been created and no Direct3D device 
//       has been created, so any initialization that depends on a window or 
//       Direct3D should be deferred to a later stage. 
//-----------------------------------------------------------------------------
CAppForm::CAppForm()
         :CFormView( IDD_FORMVIEW )
{
    //{{AFX_DATA_INIT(CAppForm)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT

    g_AppFormView          = this;
    m_hwndRenderWindow     = NULL;
    m_hwndRenderFullScreen = NULL;
    m_hWndTopLevelParent   = NULL;

    // Override some CD3DApplication defaults:
    m_dwCreationWidth           = 500;
    m_dwCreationHeight          = 375;
    m_strWindowTitle            = TEXT( "[!output PROJECT_NAME]" );
    m_d3dEnumeration.AppUsesDepthBuffer   = TRUE;
	m_bStartFullscreen			= false;
	m_bShowCursorWhenFullscreen	= false;

[!if D3DFONT]
    // Create a D3D font using d3dfont.cpp
    m_pFont                     = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
[!else]
    m_pD3DXFont                 = NULL;
[!endif]
    m_bLoadingApp               = TRUE;
[!if SHOW_TRIANGLE]
    m_pVB                       = NULL;
[!endif]
[!if SHOW_TEAPOT]
    m_pD3DXMesh                 = NULL;
[!endif]
[!if KEYBOARD]
    m_pDI                       = NULL;
    m_pKeyboard                 = NULL;
[!endif]
[!if ACTIONMAPPER]
    m_pInputDeviceManager       = NULL;
[!endif]
[!if DMUSIC || DSOUND]
[!if DMUSIC]
    m_pMusicManager             = NULL;
    m_pBounceSound              = NULL;
[!else]
    m_pSoundManager             = NULL;
    m_pBounceSound              = NULL;
[!endif]
[!endif]
[!if ACTIONMAPPER]
    m_pDIConfigSurface          = NULL;
[!endif]

    ZeroMemory( &m_UserInput, sizeof(m_UserInput) );
    m_fWorldRotX                = 0.0f;
    m_fWorldRotY                = 0.0f;
[!if DPLAY]

    m_pDP                       = NULL;    
    m_pNetConnectWizard         = NULL;    
    m_pLobbiedApp               = NULL;    
    m_bWasLobbyLaunched         = FALSE;   
    m_dpnidLocalPlayer          = 0;       
    m_lNumberOfActivePlayers    = 0;       
    m_pLocalPlayerInfo          = NULL;
    m_hrNet                     = S_OK;
    m_fWorldSyncTimer           = 0.0f;
    m_bHostPausing              = FALSE;

    ZeroMemory( &m_PlayInfoList, sizeof(APP_PLAYER_INFO) );
    m_PlayInfoList.pNext = &m_PlayInfoList;
    m_PlayInfoList.pPrev = &m_PlayInfoList;
[!endif]
[!if DPLAYVOICE]

    m_pNetVoice                 = NULL;
[!endif]
[!if REGACCESS]

    // Read settings from registry
    ReadSettings();
[!else]
[!if DPLAY]
    lstrcpyn( m_strLocalPlayerName, TEXT("[!output PROJECT_NAME] Player"), MAX_PATH  );
    lstrcpyn( m_strSessionName, TEXT("[!output PROJECT_NAME] Game"), MAX_PATH );
	lstrcpyn( m_strPreferredProvider, TEXT("DirectPlay8 TCP/IP Service Provider"), MAX_PATH );
[!endif]
[!endif]
}




//-----------------------------------------------------------------------------
// Name: CAppForm::OneTimeSceneInit()
// Desc: Paired with FinalCleanup().
//       The window has been created and the IDirect3D9 interface has been
//       created, but the device has not been created yet.  Here you can
//       perform application-related initialization and cleanup that does
//       not depend on a device.
//-----------------------------------------------------------------------------
HRESULT CAppForm::OneTimeSceneInit()
{
    // TODO: perform one time initialization

[!if DPLAY]
    // Init COM so we can use CoCreateInstance.  And be sure to init 
    // COM as multithreaded when using DirectPlay
    HRESULT hr;
    if( FAILED( hr = CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
        return hr;

[!endif]
[!if DINPUT]
    // Initialize DirectInput
    InitInput( m_hWndTopLevelParent );

[!endif]
[!if DMUSIC || DSOUND]
    // Initialize audio
    InitAudio( m_hWndTopLevelParent );

[!endif]
[!if DPLAY]
    // Initialize DirectPlay
    InitDirectPlay();

    // Create a new DirectPlay session or join to an existing DirectPlay session
    if( FAILED( hr = ConnectViaDirectPlay() ) )
        return hr;

[!endif]
    m_bLoadingApp = FALSE;

    return S_OK;
}




[!if REGACCESS]
//-----------------------------------------------------------------------------
// Name: ReadSettings()
// Desc: Read the app settings from the registry
//-----------------------------------------------------------------------------
VOID CAppForm::ReadSettings()
{
    HKEY hkey;
    if( ERROR_SUCCESS == RegCreateKeyEx( HKEY_CURRENT_USER, DXAPP_KEY, 
        0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL ) )
    {
        // TODO: change as needed

        // Read the stored window width/height.  This is just an example,
        // of how to use DXUtil_Read*() functions.
        DXUtil_ReadIntRegKey( hkey, TEXT("Width"), &m_dwCreationWidth, m_dwCreationWidth );
        DXUtil_ReadIntRegKey( hkey, TEXT("Height"), &m_dwCreationHeight, m_dwCreationHeight );

[!if DPLAY]
        // Read the saved strings needed by DirectPlay
        DXUtil_ReadStringRegKeyCch( hkey, TEXT("Player Name"), 
                                 m_strLocalPlayerName, MAX_PATH, TEXT("[!output PROJECT_NAME] Player") );
        DXUtil_ReadStringRegKeyCch( hkey, TEXT("Session Name"), 
                                 m_strSessionName, MAX_PATH, TEXT("[!output PROJECT_NAME] Game") );
        DXUtil_ReadStringRegKeyCch( hkey, TEXT("Preferred Provider"), 
                                 m_strPreferredProvider, MAX_PATH, 
                                 TEXT("DirectPlay8 TCP/IP Service Provider") );

[!endif]
        RegCloseKey( hkey );
    }
}




//-----------------------------------------------------------------------------
// Name: WriteSettings()
// Desc: Write the app settings to the registry
//-----------------------------------------------------------------------------
VOID CAppForm::WriteSettings()
{
    HKEY hkey;

    if( ERROR_SUCCESS == RegCreateKeyEx( HKEY_CURRENT_USER, DXAPP_KEY, 
        0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL ) )
    {
        // TODO: change as needed

        // Write the window width/height.  This is just an example,
        // of how to use DXUtil_Write*() functions.
        DXUtil_WriteIntRegKey( hkey, TEXT("Width"), m_rcWindowClient.right );
        DXUtil_WriteIntRegKey( hkey, TEXT("Height"), m_rcWindowClient.bottom );

[!if DPLAY]
        // Save the strings used by DirectPlay that were entered via the UI
        DXUtil_WriteStringRegKey( hkey, TEXT("Player Name"), m_strLocalPlayerName );
        DXUtil_WriteStringRegKey( hkey, TEXT("Session Name"), m_strSessionName );
        DXUtil_WriteStringRegKey( hkey, TEXT("Preferred Provider"), m_strPreferredProvider );
        
[!endif]
        RegCloseKey( hkey );
    }
}
[!endif]





[!if ACTIONMAPPER]
//-----------------------------------------------------------------------------
// Name: StaticInputAddDeviceCB()
// Desc: Static callback helper to call into CAppForm class
//-----------------------------------------------------------------------------
HRESULT CALLBACK CAppForm::StaticInputAddDeviceCB( 
                                         CInputDeviceManager::DeviceInfo* pDeviceInfo, 
                                         const DIDEVICEINSTANCE* pdidi, 
                                         LPVOID pParam )
{
    CAppForm* pApp = (CAppForm*) pParam;
    return pApp->InputAddDeviceCB( pDeviceInfo, pdidi );
}




//-----------------------------------------------------------------------------
// Name: InputAddDeviceCB()
// Desc: Called from CInputDeviceManager whenever a device is added. 
//       Set the dead zone, and creates a new InputDeviceState for each device
//-----------------------------------------------------------------------------
HRESULT CAppForm::InputAddDeviceCB( CInputDeviceManager::DeviceInfo* pDeviceInfo, 
                                                   const DIDEVICEINSTANCE* pdidi )
{
    UNREFERENCED_PARAMETER( pdidi );
    
    // Setup the deadzone 
    DIPROPDWORD dipdw;
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = 500;
    pDeviceInfo->pdidDevice->SetProperty( DIPROP_DEADZONE, &dipdw.diph );

    // Create a new InputDeviceState for each device so the 
    // app can record its state 
    InputDeviceState* pNewInputDeviceState = new InputDeviceState;
    ZeroMemory( pNewInputDeviceState, sizeof(InputDeviceState) );
    pDeviceInfo->pParam = (LPVOID) pNewInputDeviceState;

    return S_OK;
}




[!endif]
[!if DINPUT]
//-----------------------------------------------------------------------------
// Name: InitInput()
// Desc: Initialize DirectInput objects
//-----------------------------------------------------------------------------
HRESULT CAppForm::InitInput( HWND hWnd )
{
    HRESULT hr;

[!if KEYBOARD]
    // Create a IDirectInput8*
    if( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
                                         IID_IDirectInput8, (VOID**)&m_pDI, NULL ) ) )
        return DXTRACE_ERR( "DirectInput8Create", hr );
    
    // Create a IDirectInputDevice8* for the keyboard
    if( FAILED( hr = m_pDI->CreateDevice( GUID_SysKeyboard, &m_pKeyboard, NULL ) ) )
        return DXTRACE_ERR( "CreateDevice", hr );
    
    // Set the keyboard data format
    if( FAILED( hr = m_pKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
        return DXTRACE_ERR( "SetDataFormat", hr );
    
    // Set the cooperative level on the keyboard
    if( FAILED( hr = m_pKeyboard->SetCooperativeLevel( hWnd, 
                                            DISCL_NONEXCLUSIVE | 
                                            DISCL_FOREGROUND | 
                                            DISCL_NOWINKEY ) ) )
        return DXTRACE_ERR( "SetCooperativeLevel", hr );

    // Acquire the keyboard
    m_pKeyboard->Acquire();
[!endif]
[!if ACTIONMAPPER]
    // Setup action format for the actual gameplay
    ZeroMemory( &m_diafGame, sizeof(DIACTIONFORMAT) );
    m_diafGame.dwSize          = sizeof(DIACTIONFORMAT);
    m_diafGame.dwActionSize    = sizeof(DIACTION);
    m_diafGame.dwDataSize      = NUMBER_OF_GAMEACTIONS * sizeof(DWORD);
    m_diafGame.guidActionMap   = g_guidApp;

    // TODO: change the genre as needed
    m_diafGame.dwGenre         = DIVIRTUAL_CAD_3DCONTROL; 

    m_diafGame.dwNumActions    = NUMBER_OF_GAMEACTIONS;
    m_diafGame.rgoAction       = g_rgGameAction;
    m_diafGame.lAxisMin        = -100;
    m_diafGame.lAxisMax        = 100;
    m_diafGame.dwBufferSize    = 16;
    _tcscpy( m_diafGame.tszActionMap, _T("[!output PROJECT_NAME] Game") );

    // Create a new input device manager
    m_pInputDeviceManager = new CInputDeviceManager();

    if( FAILED( hr = m_pInputDeviceManager->Create( hWnd, NULL, m_diafGame, 
                                                    StaticInputAddDeviceCB, this ) ) )
        return DXTRACE_ERR( "m_pInputDeviceManager->Create", hr );
[!endif]

    return S_OK;
}




[!endif]
[!if DMUSIC || DSOUND]
//-----------------------------------------------------------------------------
// Name: InitAudio()
// Desc: Initialize DirectX audio objects
//-----------------------------------------------------------------------------
HRESULT CAppForm::InitAudio( HWND hWnd )
{
    HRESULT hr;

[!if DMUSIC]
    // Create the music manager class, used to create the sounds
    m_pMusicManager = new CMusicManager();
    if( FAILED( hr = m_pMusicManager->Initialize( hWnd ) ) )
        return DXTRACE_ERR( "m_pMusicManager->Initialize", hr );

    // Instruct the music manager where to find the files
    // TODO: Set this to the media directory, or use resources
    TCHAR szPath[MAX_PATH];
    GetCurrentDirectory( MAX_PATH, szPath ); 
    m_pMusicManager->SetSearchDirectory( szPath );

    // TODO: load the sounds from resources (or files)
    m_pMusicManager->CreateSegmentFromResource( &m_pBounceSound, _T("BOUNCE"), _T("WAVE") );

[!else]
    // Create a static IDirectSound in the CSound class.  
    // Set coop level to DSSCL_PRIORITY, and set primary buffer 
    // format to stereo, 22kHz and 16-bit output.
    m_pSoundManager = new CSoundManager();

    if( FAILED( hr = m_pSoundManager->Initialize( hWnd, DSSCL_PRIORITY ) ) )
        return DXTRACE_ERR( TEXT("m_pSoundManager->Initialize"), hr );

    if( FAILED( hr = m_pSoundManager->SetPrimaryBufferFormat( 2, 22050, 16 ) ) )
        return DXTRACE_ERR( TEXT("m_pSoundManager->SetPrimaryBufferFormat"), hr );

    // TODO: load the sounds from resources (or files)
    m_pSoundManager->Create( &m_pBounceSound, TEXT("BOUNCE"), 0, GUID_NULL, 5 );

[!endif]
    return S_OK;
}




[!endif]
[!if DPLAY]
//-----------------------------------------------------------------------------
// Name: InitDirectPlay()
// Desc: Initialize DirectPlay
//-----------------------------------------------------------------------------
HRESULT CAppForm::InitDirectPlay()
{
    // Initialize critical sections
    InitializeCriticalSection( &g_csPlayerContext );
    InitializeCriticalSection( &g_csWorldStateContext );

    // Create helper class
    m_pNetConnectWizard = new CNetConnectWizard( g_hInst, m_hWndTopLevelParent, 
                                                 m_strWindowTitle, &g_guidApp );
[!if DPLAYVOICE]
    m_pNetVoice         = new CNetVoice( StaticDirectPlayVoiceClientMessageHandler, StaticDirectPlayVoiceServerMessageHandler );
[!endif]

    DPNHANDLE hLobbyLaunchedConnection = NULL;
    HRESULT hr;

    // Create IDirectPlay8Peer
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Peer, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Peer, 
                                       (LPVOID*) &m_pDP ) ) )
        return DXTRACE_ERR( TEXT("CoCreateInstance"), hr );

    // Create IDirectPlay8LobbiedApplication
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8LobbiedApplication, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8LobbiedApplication, 
                                       (LPVOID*) &m_pLobbiedApp ) ) )
        return DXTRACE_ERR( TEXT("CoCreateInstance"), hr );

    // Init the helper class, now that m_pDP and m_pLobbiedApp are valid
    m_pNetConnectWizard->Init( m_pDP, m_pLobbiedApp );

    // Turn off parameter validation in release builds
#ifdef _DEBUG
    const DWORD dwInitFlags = 0;
#else
    const DWORD dwInitFlags = DPNINITIALIZE_DISABLEPARAMVAL;
#endif // _DEBUG

    // Init IDirectPlay8Peer
    if( FAILED( hr = m_pDP->Initialize( NULL, StaticDirectPlayMessageHandler, dwInitFlags ) ) )
        return DXTRACE_ERR( TEXT("Initialize"), hr );

    // Init IDirectPlay8LobbiedApplication.  Before this Initialize() returns 
    // a DPL_MSGID_CONNECT msg may come in to the DirectPlayLobbyMessageHandler 
    // so be prepared ahead of time.
    if( FAILED( hr = m_pLobbiedApp->Initialize( NULL, StaticDirectPlayLobbyMessageHandler, 
                                                &hLobbyLaunchedConnection, dwInitFlags ) ) )
        return DXTRACE_ERR( TEXT("Initialize"), hr );

    // IDirectPlay8LobbiedApplication::Initialize returns a handle to a connection
    // if we have been lobby launched.  Initialize is guaranteed to return after 
    // the DPL_MSGID_CONNECT msg has been processed.  So unless a we are expected 
    // multiple lobby connections, we do not need to remember the lobby connection
    // handle since it will be recorded upon the DPL_MSGID_CONNECT msg.
    m_bWasLobbyLaunched = ( hLobbyLaunchedConnection != NULL );

        return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ConnectViaDirectPlay()
// Desc: Create a new DirectPlay session or join to an existing DirectPlay session
//-----------------------------------------------------------------------------
HRESULT CAppForm::ConnectViaDirectPlay()
{
    HRESULT hr;
    BOOL bWasFullscreen  = FALSE;
    BOOL bConnectSuccess = FALSE;

    // Can't display dialogs in fullscreen mode
    if( m_bWindowed == FALSE )
    {
        bWasFullscreen = TRUE;

        if( FAILED( ToggleFullscreen() ) )
        {
            DisplayErrorMsg( D3DAPPERR_RESETFAILED, MSGERR_APPMUSTEXIT );
            return E_FAIL;
        }
    }

    // If we were launched from a lobby client, then we may have connection settings
    // that we can use either host or join a game.  If not, then we'll need to prompt 
    // the user to determine how to connect.
    if( m_bWasLobbyLaunched && m_pNetConnectWizard->HaveConnectionSettingsFromLobby() )
    {
        // If were lobby launched then the DPL_MSGID_CONNECT has already been
        // handled, and since the lobby client also sent us connection settings
        // we can use them to either host or join a DirectPlay session. 
        if( FAILED( hr = m_pNetConnectWizard->ConnectUsingLobbySettings() ) )
        {
            DXTRACE_ERR( TEXT("ConnectUsingLobbySettings"), hr );
            MessageBox( TEXT("Failed to connect using lobby settings. ")
                        TEXT("The sample will now quit."),
                        TEXT("[!output PROJECT_NAME]"), MB_OK | MB_ICONERROR );

            bConnectSuccess = FALSE;
        }
        else
        {
            // Read information from m_pNetConnectWizard
            _tcscpy( m_strLocalPlayerName, m_pNetConnectWizard->GetPlayerName() );

            bConnectSuccess = TRUE; 
        }
    }
    else
    {
        // If not lobby launched, prompt the user about the network 
        // connection and which session they would like to join or 
        // if they want to create a new one.

        // Setup connection wizard
        m_pNetConnectWizard->SetPlayerName( m_strLocalPlayerName );
        m_pNetConnectWizard->SetSessionName( m_strSessionName );
        m_pNetConnectWizard->SetPreferredProvider( m_strPreferredProvider );

        // Start a connection wizard.  The wizard uses GDI dialog boxes.
        // More complex games can use this as a starting point and add a 
        // fancier graphics layer such as Direct3D.
        hr = m_pNetConnectWizard->DoConnectWizard( FALSE );        
        if( FAILED( hr ) ) 
        {
            DXTRACE_ERR( TEXT("DoConnectWizard"), hr );
            MessageBox( TEXT("Multiplayer connect failed. ")
                        TEXT("The sample will now quit."),
                        TEXT("[!output PROJECT_NAME]"), MB_OK | MB_ICONERROR );
            bConnectSuccess = FALSE;
        } 
        else if( hr == NCW_S_QUIT ) 
        {
            // The user canceled the Multiplayer connect
            bConnectSuccess = FALSE;
        }
        else
        {
            bConnectSuccess = TRUE; 

            // Read information from m_pNetConnectWizard
            _tcscpy( m_strLocalPlayerName, m_pNetConnectWizard->GetPlayerName() );
            _tcscpy( m_strSessionName, m_pNetConnectWizard->GetSessionName() );
            _tcscpy( m_strPreferredProvider, m_pNetConnectWizard->GetPreferredProvider() );
[!if REGACCESS]

            // Write information to the registry
            WriteSettings();
[!endif]
        }
    }

[!if DPLAYVOICE]
    if( bConnectSuccess )
    {
        // Initialize DirectPlay voice
        if( FAILED( hr = InitDirectPlayVoice() ) )
        {
            bConnectSuccess = FALSE;

            if( hr == DVERR_USERBACK )
            {
                MessageBox( TEXT("The user backed out of the wizard.  ")
                            TEXT("This simple sample does not handle this case, so ")
                            TEXT("the sample will quit."), TEXT("DirectPlay Sample"), MB_OK );
            }
            else if( hr == DVERR_USERCANCEL )
            {
                MessageBox( TEXT("The user canceled the wizard. ")
                            TEXT("This simple sample does not handle this case, so ")
                            TEXT("the sample will quit."), TEXT("DirectPlay Sample"), MB_OK );
            }
            else 
            {
                DXTRACE_ERR( TEXT("m_pNetVoice->Init"), hr );
            }
        }

        if( m_pNetVoice->IsHalfDuplex() ) 
        {
            MessageBox( TEXT("You are running in half duplex mode. ")
                        TEXT("In half duplex mode no recording takes place."), 
                        TEXT("blank"), MB_OK );
        }
    }

[!endif]
    if( FALSE == bConnectSuccess )
    {
        // Quit the app
        PostQuitMessage(0);
    }
    else
    {
        // Return to fullscreen mode after dialogs
        if( bWasFullscreen )
        {
            if( FAILED( ToggleFullscreen() ) )
            {
                DisplayErrorMsg( D3DAPPERR_RESETFAILED, MSGERR_APPMUSTEXIT );
                return E_FAIL;
            }
        }
    }

    return S_OK;
}




[!endif]
[!if DPLAYVOICE]
//-----------------------------------------------------------------------------
// Name: InitDirectPlayVoice()
// Desc: Init DirectPlay Voice
//-----------------------------------------------------------------------------
HRESULT CAppForm::InitDirectPlayVoice()
{
    HRESULT hr;

    // Set default DirectPlayVoice setup options
    // TODO: change as needed or ask user for settings
    ZeroMemory( &m_dvClientConfig, sizeof(m_dvClientConfig) );
    m_dvClientConfig.dwSize                 = sizeof(m_dvClientConfig);
    m_dvClientConfig.dwFlags                = DVCLIENTCONFIG_AUTOVOICEACTIVATED |
                                              DVCLIENTCONFIG_AUTORECORDVOLUME;
    m_dvClientConfig.lPlaybackVolume        = DVPLAYBACKVOLUME_DEFAULT;
    m_dvClientConfig.dwBufferQuality        = DVBUFFERQUALITY_DEFAULT;
    m_dvClientConfig.dwBufferAggressiveness = DVBUFFERAGGRESSIVENESS_DEFAULT;
    m_dvClientConfig.dwThreshold            = DVTHRESHOLD_UNUSED;
    m_dvClientConfig.lRecordVolume          = DVRECORDVOLUME_LAST;
    m_dvClientConfig.dwNotifyPeriod         = 0;

    m_guidDVSessionCT                       = DPVCTGUID_DEFAULT;

    // Creates and connects to DirectPlay Voice using the settings stored 
    // in m_guidDVSessionCT & m_dvClientConfig.  It also runs the DirectPlay
    // Voice wizard if it hasn't been run before on this machine
    if( FAILED( hr = m_pNetVoice->Init( m_hWndTopLevelParent, m_pNetConnectWizard->IsHostPlayer(), TRUE,
                                        m_pDP, DVSESSIONTYPE_PEER, 
                                        &m_guidDVSessionCT, &m_dvClientConfig ) ) )
        return hr;

    return S_OK;
}




[!endif]
//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the display device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CAppForm::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
                                          D3DFORMAT Format )
{
    UNREFERENCED_PARAMETER( pCaps );
    UNREFERENCED_PARAMETER( dwBehavior );
    UNREFERENCED_PARAMETER( Format );
    BOOL bCapsAcceptable;

    // TODO: Perform checks to see if these display caps are acceptable.
    bCapsAcceptable = TRUE;

    if( bCapsAcceptable )         
        return S_OK;
    else
        return E_FAIL;
}




//-----------------------------------------------------------------------------
// Name: CAppForm::InitDeviceObjects()
// Desc: Paired with DeleteDeviceObjects()
//       The device has been created.  Resources that are not lost on
//       Reset() can be created here -- resources in D3DPOOL_MANAGED,
//       D3DPOOL_SCRATCH, or D3DPOOL_SYSTEMMEM.  Image surfaces created via
//       CreateImageSurface are never lost and can be created here.  Vertex
//       shaders and pixel shaders can also be created here as they are not
//       lost on Reset().
//-----------------------------------------------------------------------------
HRESULT CAppForm::InitDeviceObjects()
{
    // TODO: create device objects

[!if SHOW_TRIANGLE || SHOW_TEAPOT]
    HRESULT hr;

[!endif]
[!if D3DFONT]
    // Init the font
    m_pFont->InitDeviceObjects( m_pd3dDevice );

[!endif]
[!if SHOW_TRIANGLE]
    // Create the vertex buffer
    if( FAILED( hr = m_pd3dDevice->CreateVertexBuffer( 3*2*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_MANAGED, &m_pVB, NULL ) ) )
        return DXTRACE_ERR( "CreateVertexBuffer", hr );

    // Fill the vertex buffer with 2 triangles
    CUSTOMVERTEX* pVertices;

    if( FAILED( hr = m_pVB->Lock( 0, 0, (VOID**)&pVertices, 0 ) ) )
        return DXTRACE_ERR( "Lock", hr );

    // Front triangle
    pVertices[0].position = D3DXVECTOR3( -1.0f, -1.0f,  0.0f );
    pVertices[0].normal   = D3DXVECTOR3(  0.0f,  0.0f, -1.0f );
    pVertices[1].position = D3DXVECTOR3(  0.0f,  1.0f,  0.0f );
    pVertices[1].normal   = D3DXVECTOR3(  0.0f,  0.0f, -1.0f );
    pVertices[2].position = D3DXVECTOR3(  1.0f, -1.0f,  0.0f );
    pVertices[2].normal   = D3DXVECTOR3(  0.0f,  0.0f, -1.0f );

    // Back triangle
    pVertices[3].position = D3DXVECTOR3( -1.0f, -1.0f,  0.0f );
    pVertices[3].normal   = D3DXVECTOR3(  0.0f,  0.0f,  1.0f );
    pVertices[4].position = D3DXVECTOR3(  1.0f, -1.0f,  0.0f );
    pVertices[4].normal   = D3DXVECTOR3(  0.0f,  0.0f,  1.0f );
    pVertices[5].position = D3DXVECTOR3(  0.0f,  1.0f,  0.0f );
    pVertices[5].normal   = D3DXVECTOR3(  0.0f,  0.0f,  1.0f );

    m_pVB->Unlock();

[!endif]
[!if SHOW_TEAPOT]
    // Create a teapot mesh using D3DX
    if( FAILED( hr = D3DXCreateTeapot( m_pd3dDevice, &m_pD3DXMesh, NULL ) ) )
        return DXTRACE_ERR( "D3DXCreateTeapot", hr );

[!endif]
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CAppForm::RestoreDeviceObjects()
// Desc: Paired with InvalidateDeviceObjects()
//       The device exists, but may have just been Reset().  Resources in
//       D3DPOOL_DEFAULT and any other device state that persists during
//       rendering should be set here.  Render states, matrices, textures,
//       etc., that don't change during rendering can be set once here to
//       avoid redundant state setting during Render() or FrameMove().
//-----------------------------------------------------------------------------
HRESULT CAppForm::RestoreDeviceObjects()
{
    // TODO: setup render states
[!if !D3DFONT || ACTIONMAPPER]
    HRESULT hr;
[!endif]

    // Setup a material
    D3DMATERIAL9 mtrl;
    D3DUtil_InitMaterial( mtrl, 1.0f, 0.0f, 0.0f );
    m_pd3dDevice->SetMaterial( &mtrl );

    // Set up the textures
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    // Set miscellaneous render states
    m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE,   FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,        TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT,        0x000F0F0F );

    // Set the world matrix
    D3DXMATRIX matIdentity;
    D3DXMatrixIdentity( &matIdentity );
    m_pd3dDevice->SetTransform( D3DTS_WORLD,  &matIdentity );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXMATRIX matView;
    D3DXVECTOR3 vFromPt   = D3DXVECTOR3( 0.0f, 0.0f, -5.0f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &matView, &vFromPt, &vLookatPt, &vUpVec );
    m_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // Set the projection matrix
    D3DXMATRIX matProj;
    FLOAT fAspect = ((FLOAT)m_d3dsdBackBuffer.Width) / m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, fAspect, 1.0f, 100.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    // Set up lighting states
    D3DLIGHT9 light;
    D3DUtil_InitLight( light, D3DLIGHT_DIRECTIONAL, -1.0f, -1.0f, 2.0f );
    m_pd3dDevice->SetLight( 0, &light );
    m_pd3dDevice->LightEnable( 0, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

[!if D3DFONT]
    // Restore the font
    m_pFont->RestoreDeviceObjects();
[!else]
    // Create a D3D font using D3DX
    HFONT hFont = CreateFont( 20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                              ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              ANTIALIASED_QUALITY, FF_DONTCARE, "Arial" );      
    if( FAILED( hr = D3DXCreateFont( m_pd3dDevice, hFont, &m_pD3DXFont ) ) )
        return DXTRACE_ERR( "D3DXCreateFont", hr );
[!endif]
[!if ACTIONMAPPER]

    if( !m_bWindowed )
    {
        // Create a surface for configuring DInput devices
        if( FAILED( hr = m_pd3dDevice->CreateOffscreenPlainSurface( 640, 480, 
                                        m_d3dsdBackBuffer.Format, D3DPOOL_DEFAULT, 
										&m_pDIConfigSurface, NULL ) ) ) 
            return DXTRACE_ERR( "CreateOffscreenPlainSurface", hr );
    }
[!endif]

    return S_OK;
}




[!if ACTIONMAPPER]
//-----------------------------------------------------------------------------
// Name: StaticConfigureInputDevicesCB()
// Desc: Static callback helper to call into CAppForm class
//-----------------------------------------------------------------------------
BOOL CALLBACK CAppForm::StaticConfigureInputDevicesCB( 
                                            IUnknown* pUnknown, VOID* pUserData )
{
    CAppForm* pApp = (CAppForm*) pUserData;
    return pApp->ConfigureInputDevicesCB( pUnknown );
}




//-----------------------------------------------------------------------------
// Name: ConfigureInputDevicesCB()
// Desc: Callback function for configuring input devices. This function is
//       called in fullscreen modes, so that the input device configuration
//       window can update the screen.
//-----------------------------------------------------------------------------
BOOL CAppForm::ConfigureInputDevicesCB( IUnknown* pUnknown )
{
    // Get access to the surface
    LPDIRECT3DSURFACE9 pConfigSurface = NULL;
    if( FAILED( pUnknown->QueryInterface( IID_IDirect3DSurface9,
                                          (VOID**)&pConfigSurface ) ) )
        return TRUE;

    // Render the scene, with the config surface blitted on top
    Render();

    RECT  rcSrc;
    SetRect( &rcSrc, 0, 0, 640, 480 );

    POINT ptDst;
    ptDst.x = (m_d3dsdBackBuffer.Width-640)/2;
    ptDst.y = (m_d3dsdBackBuffer.Height-480)/2;

    LPDIRECT3DSURFACE9 pBackBuffer;
    m_pd3dDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
    m_pd3dDevice->UpdateSurface( pConfigSurface, &rcSrc, pBackBuffer, &ptDst );
    pBackBuffer->Release();

    // Present the backbuffer contents to the front buffer
    m_pd3dDevice->Present( 0, 0, 0, 0 );

    // Release the surface
    pConfigSurface->Release();

    return TRUE;
}




[!endif]
//-----------------------------------------------------------------------------
// Name: CAppForm::FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CAppForm::FrameMove()
{
    // TODO: update world

    // Update user input state
    UpdateInput( &m_UserInput );

[!if DPLAY]
    // Send local input to all network players if it changed
    SendLocalInputIfChanged();

    if( m_pNetConnectWizard->IsHostPlayer() )
    {
        m_fWorldSyncTimer -= m_fElapsedTime;
        if( m_fWorldSyncTimer < 0.0f )
        {
            // If this player is the host and timer has expired
            // then reset timer and send the world state to all players
            m_fWorldSyncTimer = 0.1f;
            SendWorldStateToAll();
        }
    }

[!endif]
[!if ACTIONMAPPER]
    // Respond to input
    if( m_UserInput.bDoConfigureInput && m_bWindowed )  // full-screen configure disabled for now
    {
        // One-shot per keypress
        m_UserInput.bDoConfigureInput = FALSE;

        Pause( true );

        // Get access to the list of semantically-mapped input devices
        // to delete all InputDeviceState structs before calling ConfigureDevices()
        CInputDeviceManager::DeviceInfo* pDeviceInfos;
        DWORD dwNumDevices;
        m_pInputDeviceManager->GetDevices( &pDeviceInfos, &dwNumDevices );

        for( DWORD i=0; i<dwNumDevices; i++ )
        {
            InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;
            SAFE_DELETE( pInputDeviceState );
            pDeviceInfos[i].pParam = NULL;
        }

        // Configure the devices (with edit capability)
        if( m_bWindowed )
            m_pInputDeviceManager->ConfigureDevices( m_hWndTopLevelParent, NULL, NULL, DICD_EDIT, NULL );
        else
            m_pInputDeviceManager->ConfigureDevices( m_hwndRenderFullScreen,
                                                     m_pDIConfigSurface,
                                                     (VOID*)StaticConfigureInputDevicesCB,
                                                     DICD_EDIT, (LPVOID) this );

        Pause( false );
    }

    if( m_UserInput.bDoConfigureDisplay )
    {
        // One-shot per keypress
        m_UserInput.bDoConfigureDisplay = FALSE;

        OnChangeDevice();
    }

[!endif]
[!if DPLAYVOICE]
    if( m_UserInput.bDoConfigureVoice )
    {
        // One-shot per keypress
        m_UserInput.bDoConfigureVoice = FALSE;

        Pause(true);

        // Allow user to configure the voice settings
        UserConfigVoice();

        Pause(false);
    }

[!endif]
[!if DPLAY]
    // Combining the input data from all players 
    // TODO: Combining the input data from all players is an unrealistic yet simple 
    //       usage of network data. Use it as a starting point to serve your needs
    CombineInputFromAllPlayers( &m_CombinedNetworkInput );

[!endif]
[!if DPLAYVOICE]
    // Update talking variables
    // TODO: The talking variables just update the text, but something more complex
    //       like animation could be done based on them
    UpdateTalkingVariables();

[!endif]
    // Update the world state according to user input
    D3DXMATRIX matWorld;
    D3DXMATRIX matRotY;
    D3DXMATRIX matRotX;

[!if DPLAY]
    // Enter world state critical section before accessing world state data 
    // otherwise one of the DirectPlay threads may change the data
    // while this thread is accessing or changing it.
    WORLD_LOCK();

    // Rotate object according to user input from all network players
    // Only update the world state if the host hasn't told our to pause
    if( FALSE == m_bHostPausing )
    {
        // Update the m_fWorldRotY & m_fWorldRotX according 
        // to the combined input of all the network players
[!if ACTIONMAPPER]
        if( m_CombinedNetworkInput.fAxisRotateLR )
            m_fWorldRotY += m_fElapsedTime * m_CombinedNetworkInput.fAxisRotateLR;

        if( m_CombinedNetworkInput.fAxisRotateUD )
            m_fWorldRotX += m_fElapsedTime * m_CombinedNetworkInput.fAxisRotateUD;
[!else]
        if( m_CombinedNetworkInput.bRotateLeft && !m_CombinedNetworkInput.bRotateRight )
            m_fWorldRotY += m_fElapsedTime;
        else if( m_CombinedNetworkInput.bRotateRight && !m_CombinedNetworkInput.bRotateLeft )
            m_fWorldRotY -= m_fElapsedTime;

        if( m_CombinedNetworkInput.bRotateUp && !m_CombinedNetworkInput.bRotateDown )
            m_fWorldRotX += m_fElapsedTime;
        else if( m_CombinedNetworkInput.bRotateDown && !m_CombinedNetworkInput.bRotateUp )
            m_fWorldRotX -= m_fElapsedTime;
[!endif]
    }

    // Calculate and update the world matrix
    D3DXMatrixRotationX( &matRotX, m_fWorldRotX );
    D3DXMatrixRotationY( &matRotY, m_fWorldRotY );

    // Leave the critical section
    WORLD_UNLOCK();

[!endif]
[!if !DPLAY]
[!if ACTIONMAPPER]
    if( m_UserInput.fAxisRotateLR )
        m_fWorldRotY += m_fElapsedTime * m_UserInput.fAxisRotateLR;

    if( m_UserInput.fAxisRotateUD )
        m_fWorldRotX += m_fElapsedTime * m_UserInput.fAxisRotateUD;

[!else]
    if( m_UserInput.bRotateLeft && !m_UserInput.bRotateRight )
        m_fWorldRotY += m_fElapsedTime;
    else if( m_UserInput.bRotateRight && !m_UserInput.bRotateLeft )
        m_fWorldRotY -= m_fElapsedTime;

    if( m_UserInput.bRotateUp && !m_UserInput.bRotateDown )
        m_fWorldRotX += m_fElapsedTime;
    else if( m_UserInput.bRotateDown && !m_UserInput.bRotateUp )
        m_fWorldRotX -= m_fElapsedTime;

[!endif]
    D3DXMatrixRotationX( &matRotX, m_fWorldRotX );
    D3DXMatrixRotationY( &matRotY, m_fWorldRotY );

[!endif]
    D3DXMatrixMultiply( &matWorld, &matRotX, &matRotY );
    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

[!if DMUSIC || DSOUND]
    // Play the sound every so often while the button is pressed 
    if( m_UserInput.bPlaySoundButtonDown )
    {
        m_fSoundPlayRepeatCountdown -= m_fElapsedTime;
        if( m_fSoundPlayRepeatCountdown <= 0.0f )
        {
            m_fSoundPlayRepeatCountdown = 0.5f;
            if( m_pBounceSound )
                m_pBounceSound->Play();
        }
    }
    else
    {
        m_fSoundPlayRepeatCountdown = 0.0f;
    }

[!endif]
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: UpdateInput()
// Desc: Update the user input.  Called once per frame 
//-----------------------------------------------------------------------------
void CAppForm::UpdateInput( UserInput* pUserInput )
{
[!if ACTIONMAPPER]
    if( NULL == m_pInputDeviceManager )
        return;

    // Get access to the list of semantically-mapped input devices
    CInputDeviceManager::DeviceInfo* pDeviceInfos;
    DWORD dwNumDevices;
    m_pInputDeviceManager->GetDevices( &pDeviceInfos, &dwNumDevices );

    // Loop through all devices and check game input
    for( DWORD i=0; i<dwNumDevices; i++ )
    {
        DIDEVICEOBJECTDATA rgdod[10];
        DWORD   dwItems = 10;
        HRESULT hr;
        LPDIRECTINPUTDEVICE8 pdidDevice = pDeviceInfos[i].pdidDevice;
        InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;

        hr = pdidDevice->Acquire();
        hr = pdidDevice->Poll();
        hr = pdidDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA),
                                        rgdod, &dwItems, 0 );
        if( FAILED(hr) )
            continue;

        // Get the sematics codes for the game menu
        for( DWORD j=0; j<dwItems; j++ )
        {
            BOOL  bButtonState = (rgdod[j].dwData==0x80) ? TRUE : FALSE;
            FLOAT fButtonState = (rgdod[j].dwData==0x80) ? 1.0f : 0.0f;
            FLOAT fAxisState   = (FLOAT)((int)rgdod[j].dwData)/100.0f;
            UNREFERENCED_PARAMETER( fButtonState );

            switch( rgdod[j].uAppData )
            {
                // TODO: Handle semantics for the game 

                // Handle relative axis data
                case INPUT_ROTATE_AXIS_LR: 
                    pInputDeviceState->fAxisRotateLR = -fAxisState;
                    break;
                case INPUT_ROTATE_AXIS_UD:
                    pInputDeviceState->fAxisRotateUD = -fAxisState;
                    break;

                // Handle buttons separately so the button state data
                // doesn't overwrite the axis state data, and handle
                // each button separately so they don't overwrite each other
                case INPUT_ROTATE_LEFT:  pInputDeviceState->bButtonRotateLeft  = bButtonState; break;
                case INPUT_ROTATE_RIGHT: pInputDeviceState->bButtonRotateRight = bButtonState; break;
                case INPUT_ROTATE_UP:    pInputDeviceState->bButtonRotateUp    = bButtonState; break;
                case INPUT_ROTATE_DOWN:  pInputDeviceState->bButtonRotateDown  = bButtonState; break;
[!if DMUSIC || DSOUND]
                case INPUT_PLAY_SOUND:   pInputDeviceState->bButtonPlaySoundButtonDown = bButtonState; break;
[!endif]

                // Handle one-shot buttons
                case INPUT_CONFIG_INPUT:   if( bButtonState ) pUserInput->bDoConfigureInput = TRUE; break;
                case INPUT_CONFIG_DISPLAY: if( bButtonState ) pUserInput->bDoConfigureDisplay = TRUE; break;
[!if DPLAYVOICE]
                case INPUT_CONFIG_VOICE:   if( bButtonState ) pUserInput->bDoConfigureVoice   = TRUE; break;
[!endif]
            }
        }
    }

    // TODO: change process code as needed

    // Process user input and store result into pUserInput struct
    pUserInput->fAxisRotateLR = 0.0f;
    pUserInput->fAxisRotateUD = 0.0f;
[!if DMUSIC || DSOUND]
    pUserInput->bPlaySoundButtonDown = FALSE;
[!endif]

    // Concatinate the data from all the DirectInput devices
    for( i=0; i<dwNumDevices; i++ )
    {
        InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;

        // Use the axis data that is furthest from zero
        if( fabs(pInputDeviceState->fAxisRotateLR) > fabs(pUserInput->fAxisRotateLR) )
            pUserInput->fAxisRotateLR = pInputDeviceState->fAxisRotateLR;

        if( fabs(pInputDeviceState->fAxisRotateUD) > fabs(pUserInput->fAxisRotateUD) )
            pUserInput->fAxisRotateUD = pInputDeviceState->fAxisRotateUD;

        // Process the button data 
        if( pInputDeviceState->bButtonRotateLeft )
            pUserInput->fAxisRotateLR = 1.0f;
        else if( pInputDeviceState->bButtonRotateRight )
            pUserInput->fAxisRotateLR = -1.0f;

        if( pInputDeviceState->bButtonRotateUp )
            pUserInput->fAxisRotateUD = 1.0f;
        else if( pInputDeviceState->bButtonRotateDown )
            pUserInput->fAxisRotateUD = -1.0f;

[!if DMUSIC || DSOUND]
        if( pInputDeviceState->bButtonPlaySoundButtonDown )
            pUserInput->bPlaySoundButtonDown = TRUE;
[!endif]
    } 
[!endif]
[!if KEYBOARD]
    HRESULT hr;

    // Get the input's device state, and put the state in dims
    ZeroMemory( &pUserInput->diks, sizeof(pUserInput->diks) );
    hr = m_pKeyboard->GetDeviceState( sizeof(pUserInput->diks), &pUserInput->diks );
    if( FAILED(hr) ) 
    {
        m_pKeyboard->Acquire();
        return; 
    }

    // TODO: Process user input as needed
    pUserInput->bRotateLeft  = ( (pUserInput->diks[DIK_LEFT] & 0x80)  == 0x80 );
    pUserInput->bRotateRight = ( (pUserInput->diks[DIK_RIGHT] & 0x80) == 0x80 );
    pUserInput->bRotateUp    = ( (pUserInput->diks[DIK_UP] & 0x80)    == 0x80 );
    pUserInput->bRotateDown  = ( (pUserInput->diks[DIK_DOWN] & 0x80)  == 0x80 );
[!if DMUSIC || DSOUND]
    pUserInput->bPlaySoundButtonDown   = ( (pUserInput->diks[DIK_F5] & 0x80)     == 0x80 );
[!endif]
[!endif]
[!if !DINPUT]
    pUserInput->bRotateUp    = ( m_bActive && (GetAsyncKeyState( VK_UP )    & 0x8000) == 0x8000 );
    pUserInput->bRotateDown  = ( m_bActive && (GetAsyncKeyState( VK_DOWN )  & 0x8000) == 0x8000 );
    pUserInput->bRotateLeft  = ( m_bActive && (GetAsyncKeyState( VK_LEFT )  & 0x8000) == 0x8000 );
    pUserInput->bRotateRight = ( m_bActive && (GetAsyncKeyState( VK_RIGHT ) & 0x8000) == 0x8000 );
[!if DMUSIC || DSOUND]
    pUserInput->bPlaySoundButtonDown = ( m_bActive && (GetAsyncKeyState( VK_F5 ) & 0x8000) == 0x8000 );
[!endif]
[!endif]
}




[!if DPLAY]
//-----------------------------------------------------------------------------
// Name: SendLocalInputIfChanged()
// Desc: Send local input to all network players if it changed
//-----------------------------------------------------------------------------
HRESULT CAppForm::SendLocalInputIfChanged()
{
    if( NULL == m_pLocalPlayerInfo )
        return S_OK;

    // Enter player critical section before accessing player's state data 
    // otherwise the DirectPlay network threads may change the data
    // while this thread is accessing it.
    PLAYER_LOCK();                  

    // Compare the local input axis data from DirectInput against the 
    // state of the axis data stored in the local player's 
    // APP_PLAYER_INFO struct to see if input changed
    BOOL bLocalInputChanged = FALSE;
[!if ACTIONMAPPER]
    if( m_UserInput.fAxisRotateLR != m_pLocalPlayerInfo->fAxisRotateLR ||
        m_UserInput.fAxisRotateUD != m_pLocalPlayerInfo->fAxisRotateUD )
[!else]
    if( m_UserInput.bRotateUp    != m_pLocalPlayerInfo->bRotateUp   ||
        m_UserInput.bRotateDown  != m_pLocalPlayerInfo->bRotateDown ||
        m_UserInput.bRotateLeft  != m_pLocalPlayerInfo->bRotateLeft ||
        m_UserInput.bRotateRight != m_pLocalPlayerInfo->bRotateRight )
[!endif]
    {
        bLocalInputChanged = TRUE;
    }

    PLAYER_UNLOCK();                // leave player context CS

    // If it has changed then send it to all the network players
    // including the local player
    if( bLocalInputChanged )
    {
        GAMEMSG_INPUTSTATE msgInputState;
        msgInputState.nType = GAME_MSGID_INPUTSTATE;
[!if ACTIONMAPPER]
        msgInputState.fAxisRotateLR = m_UserInput.fAxisRotateLR;
        msgInputState.fAxisRotateUD = m_UserInput.fAxisRotateUD;
[!else]
        msgInputState.bRotateUp    = m_UserInput.bRotateUp;
        msgInputState.bRotateDown  = m_UserInput.bRotateDown;
        msgInputState.bRotateLeft  = m_UserInput.bRotateLeft;
        msgInputState.bRotateRight = m_UserInput.bRotateRight;
[!endif]

        DPN_BUFFER_DESC bufferDesc;
        bufferDesc.dwBufferSize = sizeof(GAMEMSG_INPUTSTATE);
        bufferDesc.pBufferData  = (BYTE*) &msgInputState;

        // Send it to all of the players including the local client
        // DirectPlay will tell via the message handler 
        // if there are any severe errors, so ignore any errors 
        DPNHANDLE hAsync;
        m_pDP->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1,
                       0, NULL, &hAsync, DPNSEND_GUARANTEED );
    }


    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SendWorldStateToAll()
// Desc: Send the world state to all players on the network
//-----------------------------------------------------------------------------
HRESULT CAppForm::SendWorldStateToAll()
{
    // Enter world state critical section before accessing world state data 
    // otherwise one of the DirectPlay threads may change the data
    // while this thread is accessing it.
    WORLD_LOCK();

    GAMEMSG_WORLDSTATE msgWorldState;
    msgWorldState.nType = GAME_MSGID_WORLDSTATE;
    msgWorldState.fWorldRotX = m_fWorldRotX;
    msgWorldState.fWorldRotY = m_fWorldRotY;

    // Leave the critical section
    WORLD_UNLOCK();

    DPN_BUFFER_DESC bufferDesc;
    bufferDesc.dwBufferSize = sizeof(GAMEMSG_WORLDSTATE);
    bufferDesc.pBufferData  = (BYTE*) &msgWorldState;

    // Send the message to all the players except the ourselves
    // DirectPlay will tell via the message handler 
    // if there are any severe errors, so ignore any errors 
    DPNHANDLE hAsync;
    m_pDP->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1,
                   0, NULL, &hAsync, DPNSEND_NOLOOPBACK );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SendPauseMessageToAll()
// Desc: Send a pause message to all players on the network
//-----------------------------------------------------------------------------
HRESULT CAppForm::SendPauseMessageToAll( bool bPause )
{
    GAMEMSG_HOSTPAUSE msgPause;
    msgPause.nType = GAME_MSGID_HOSTPAUSE;
    msgPause.bHostPause = bPause; 

    DPN_BUFFER_DESC bufferDesc;
    bufferDesc.dwBufferSize = sizeof(GAMEMSG_HOSTPAUSE);
    bufferDesc.pBufferData  = (BYTE*) &msgPause;

    // Send the message to all the players except the ourselves
    // DirectPlay will tell via the message handler 
    // if there are any severe errors, so ignore any errors 
    DPNHANDLE hAsync;
    m_pDP->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1,
                   0, NULL, &hAsync, DPNSEND_GUARANTEED | DPNSEND_NOLOOPBACK );

    return S_OK;
}




[!if ACTIONMAPPER]
//-----------------------------------------------------------------------------
// Name: CombineInputFromAllPlayers()
// Desc: Combine axis input from all network players
//-----------------------------------------------------------------------------
HRESULT CAppForm::CombineInputFromAllPlayers( UserInput* pCombinedUserInput )
{
    FLOAT fAxisRotateLRCombined = 0.0f;
    FLOAT fAxisRotateUDCombined = 0.0f;

    // Enter player context CS before accessing APP_PLAYER_INFO structs
    // otherwise one of the DirectPlay threads may delete the struct
    // while this thread is accessing it.
    PLAYER_LOCK();                  

    APP_PLAYER_INFO* pPlayerInfo = m_PlayInfoList.pNext;

    while( pPlayerInfo != &m_PlayInfoList )
    {
        // Use the player whose axis data that is furthest from zero
        // and if one player is at -1, and another is at +1 then always
        // choose the positive one.
        if( fabs(pPlayerInfo->fAxisRotateLR) == fabs(fAxisRotateLRCombined) &&
                pPlayerInfo->fAxisRotateLR > 0.0f )
            fAxisRotateLRCombined = pPlayerInfo->fAxisRotateLR;
        if( fabs(pPlayerInfo->fAxisRotateLR) > fabs(fAxisRotateLRCombined) )
            fAxisRotateLRCombined = pPlayerInfo->fAxisRotateLR;

        if( fabs(pPlayerInfo->fAxisRotateUD) == fabs(fAxisRotateUDCombined) && 
                pPlayerInfo->fAxisRotateUD > 0.0f )
            fAxisRotateUDCombined = pPlayerInfo->fAxisRotateUD;
        if( fabs(pPlayerInfo->fAxisRotateUD) > fabs(fAxisRotateUDCombined) )
            fAxisRotateUDCombined = pPlayerInfo->fAxisRotateUD;

        pPlayerInfo = pPlayerInfo->pNext;
    }

    // Leave player context CS
    PLAYER_UNLOCK();           
    
    pCombinedUserInput->fAxisRotateLR = fAxisRotateLRCombined;
    pCombinedUserInput->fAxisRotateUD = fAxisRotateUDCombined;

    return S_OK;
}




[!else]
//-----------------------------------------------------------------------------
// Name: CombineInputFromAllPlayers()
// Desc: Combine axis input from all network players
//-----------------------------------------------------------------------------
HRESULT CAppForm::CombineInputFromAllPlayers( UserInput* pCombinedUserInput )
{
    pCombinedUserInput->bRotateUp    = FALSE;
    pCombinedUserInput->bRotateDown  = FALSE;
    pCombinedUserInput->bRotateLeft  = FALSE;
    pCombinedUserInput->bRotateRight = FALSE;

    // Enter player context CS before accessing APP_PLAYER_INFO structs
    // otherwise one of the DirectPlay threads may delete the struct
    // while this thread is accessing it.
    PLAYER_LOCK();                  

    APP_PLAYER_INFO* pPlayerInfo = m_PlayInfoList.pNext;

    while( pPlayerInfo != &m_PlayInfoList )
    {
        // Use the player whose axis data that is furthest from zero
        // and if one player is at -1, and another is at +1 then always
        // choose the positive one.
        if( pPlayerInfo->bRotateUp )
            pCombinedUserInput->bRotateUp = TRUE;
        if( pPlayerInfo->bRotateDown )
            pCombinedUserInput->bRotateDown = TRUE;
        if( pPlayerInfo->bRotateLeft )
            pCombinedUserInput->bRotateLeft = TRUE;
        if( pPlayerInfo->bRotateRight )
            pCombinedUserInput->bRotateRight = TRUE;

        pPlayerInfo = pPlayerInfo->pNext;
    }

    // Leave player context CS
    PLAYER_UNLOCK();           
    
    return S_OK;
}




[!endif]
[!endif]
[!if DPLAYVOICE]
//-----------------------------------------------------------------------------
// Name: UpdateTalkingVariables()
// Desc: Update m_bNetworkPlayersTalking and m_bLocalPlayerTalking
//-----------------------------------------------------------------------------
VOID CAppForm::UpdateTalkingVariables()
{
    // Enter player critical section before accessing player's state data 
    // otherwise the DirectPlay network threads may change the data
    // while this thread is accessing it.
    PLAYER_LOCK();      

    APP_PLAYER_INFO* pPlayerInfo = m_PlayInfoList.pNext;

    m_bNetworkPlayersTalking = FALSE;
    while( pPlayerInfo != &m_PlayInfoList )
    {
        // If any player besides the local player is talking, then set
        // m_bNetworkPlayersTalking to TRUE
        if( pPlayerInfo != m_pLocalPlayerInfo && pPlayerInfo->bTalking )
            m_bNetworkPlayersTalking = TRUE;

        pPlayerInfo = pPlayerInfo->pNext;
    }

    // Update m_bLocalPlayerTalking
    m_bLocalPlayerTalking = m_pLocalPlayerInfo->bTalking;

    PLAYER_UNLOCK();                
}




[!endif]
//-----------------------------------------------------------------------------
// Name: CAppForm::Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT CAppForm::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         0x000000ff, 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        // TODO: render world
        
[!if SHOW_TRIANGLE]
        // Render the vertex buffer contents
        m_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(CUSTOMVERTEX) );
        m_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
        m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

[!endif]
[!if SHOW_TEAPOT]
        // Render the teapot mesh
        m_pD3DXMesh->DrawSubset(0);

[!endif]
        // Render stats and help text  
        RenderText();

        // End the scene.
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RenderText()
// Desc: Renders stats and help text to the scene.
//-----------------------------------------------------------------------------
HRESULT CAppForm::RenderText()
{
    D3DCOLOR fontColor        = D3DCOLOR_ARGB(255,255,255,0);
[!if DPLAY]
    D3DCOLOR fontWarningColor = D3DCOLOR_ARGB(255,0,255,255);
[!endif]
    TCHAR szMsg[MAX_PATH] = TEXT("");
[!if !D3DFONT]
    RECT rct;
    ZeroMemory( &rct, sizeof(rct) );       

    m_pD3DXFont->Begin();
    rct.left   = 2;
    rct.right  = m_d3dsdBackBuffer.Width - 20;
[!else]
[!endif]

    // Output display stats
[!if !D3DFONT]
    INT nNextLine = 40; 
[!else]
    FLOAT fNextLine = 40.0f; 
[!endif]

    lstrcpy( szMsg, m_strDeviceStats );
[!if D3DFONT]
    fNextLine -= 20.0f;
    m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

    lstrcpy( szMsg, m_strFrameStats );
[!if D3DFONT]
    fNextLine -= 20.0f;
    m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

    // Output statistics & help
[!if !D3DFONT]
    nNextLine = m_d3dsdBackBuffer.Height; 
[!else]
    fNextLine = (FLOAT) m_d3dsdBackBuffer.Height; 
[!endif]

[!if DPLAY]
[!if ACTIONMAPPER]
    sprintf( szMsg, TEXT("Network Combined L/R Axis: %0.2f U/D Axis: %0.2f "), 
              m_CombinedNetworkInput.fAxisRotateLR, m_CombinedNetworkInput.fAxisRotateUD );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!else]
    wsprintf( szMsg, TEXT("Network Combined Keys: U=%d D=%d L=%d R=%d"), 
              m_CombinedNetworkInput.bRotateUp, m_CombinedNetworkInput.bRotateDown, m_CombinedNetworkInput.bRotateLeft, m_CombinedNetworkInput.bRotateRight );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!endif]
[!if ACTIONMAPPER]
[!if DPLAY]
    sprintf( szMsg, TEXT("Local Left/Right Axis: %0.2f Up/Down Axis: %0.2f "), 
              m_UserInput.fAxisRotateLR, m_UserInput.fAxisRotateUD );
[!else]
    sprintf( szMsg, TEXT("Left/Right Axis: %0.2f Up/Down Axis: %0.2f "), 
              m_UserInput.fAxisRotateLR, m_UserInput.fAxisRotateUD );
[!endif]
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!else]
[!if DPLAY]
    wsprintf( szMsg, TEXT("Local Arrow keys: U=%d D=%d L=%d R=%d"), 
              m_UserInput.bRotateUp, m_UserInput.bRotateDown, m_UserInput.bRotateLeft, m_UserInput.bRotateRight );
[!else]
    wsprintf( szMsg, TEXT("Arrow keys: Up=%d Down=%d Left=%d Right=%d"), 
              m_UserInput.bRotateUp, m_UserInput.bRotateDown, m_UserInput.bRotateLeft, m_UserInput.bRotateRight );
[!endif]
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!if DPLAY]
    sprintf( szMsg, TEXT("%d player(s) in session %s"), 
                        m_lNumberOfActivePlayers, 
                        m_pNetConnectWizard->IsHostPlayer() ? TEXT("(Hosting)") : TEXT("") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!if DPLAYVOICE]
    sprintf( szMsg, TEXT("Local Player: %s  Network Players: %s"), 
                        m_bLocalPlayerTalking ? TEXT("Talking") : TEXT("Silent"), 
                        m_bNetworkPlayersTalking ? TEXT("Talking") : TEXT("Silent") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!if !SHOW_TRIANGLE]
[!if !SHOW_TEAPOT]
    sprintf( szMsg, TEXT("World State: %0.3f, %0.3f"), 
                    m_fWorldRotX, m_fWorldRotY );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!endif]
[!if SHOW_TRIANGLE || SHOW_TEAPOT]
[!if ACTIONMAPPER]
    lstrcpy( szMsg, TEXT("Use arrow keys or joystick to rotate object") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!else]
    lstrcpy( szMsg, TEXT("Use arrow keys to rotate object") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!else]
[!if ACTIONMAPPER]
    lstrcpy( szMsg, TEXT("Use arrow keys or joystick to update input") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!else]
    lstrcpy( szMsg, TEXT("Use arrow keys to update input") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!endif]
[!if DMUSIC || DSOUND]
    lstrcpy( szMsg, TEXT("Hold 'F5' down to play and repeat a sound") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!if DPLAYVOICE]
    lstrcpy( szMsg, TEXT("Press 'F4' to configure voice") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
[!if ACTIONMAPPER]
    lstrcpy( szMsg, TEXT("Press 'F3' to configure input") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!endif]
    lstrcpy( szMsg, TEXT("Press 'F2' to configure display") );
[!if D3DFONT]
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
[!else]
    nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
    m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontColor );
[!endif]

[!if DPLAY]
    if( m_bHostPausing )
    {
        lstrcpy( szMsg, TEXT("Paused waiting for host...") );
[!if D3DFONT]
        fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontWarningColor, szMsg );
[!else]
        nNextLine -= 20; rct.top = nNextLine; rct.bottom = rct.top + 20;    
        m_pD3DXFont->DrawText( szMsg, -1, &rct, 0, fontWarningColor );
[!endif]
    }

[!endif]
[!if !D3DFONT]
    m_pD3DXFont->End();

[!endif]
    return S_OK;
}




[!if DPLAY || ACTIONMAPPER]
//-----------------------------------------------------------------------------
// Name: Pause()
// Desc: Called in to toggle the pause state of the app.
//-----------------------------------------------------------------------------
VOID CAppForm::Pause( bool bPause )
{
[!if DPLAY]
    // Tell the other apps to pause or unpause if this is the host
    if( m_pNetConnectWizard && m_pNetConnectWizard->IsHostPlayer() )
        SendPauseMessageToAll( bPause );

[!endif]
[!if ACTIONMAPPER]
    // Get access to the list of semantically-mapped input devices
    // to zero the state of all InputDeviceState structs.  This is needed
    // because when using DISCL_FOREGROUND, the action mapper will not 
    // record actions when the focus switches, for example if a dialog appears.
    // This causes a problem when a button held down when loosing focus, and let
    // go when the focus is lost.  The app will not record that the button 
    // has been let go, so the state will be incorrect when focus returns.  
    // To fix this either use DISCL_BACKGROUND or zero the state when 
    // loosing focus.
    CInputDeviceManager::DeviceInfo* pDeviceInfos;
    DWORD dwNumDevices;
    m_pInputDeviceManager->GetDevices( &pDeviceInfos, &dwNumDevices );

    for( DWORD i=0; i<dwNumDevices; i++ )
    {
        InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;
        ZeroMemory( pInputDeviceState, sizeof(InputDeviceState) );
    }

[!endif]
    CD3DApplication::Pause( bPause );
}




[!endif]
//-----------------------------------------------------------------------------
// Name: DoDataExchange()
// Desc: DDX/DDV support
//-----------------------------------------------------------------------------
void CAppForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppForm)
	//}}AFX_DATA_MAP
}




//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: 
//-----------------------------------------------------------------------------
LRESULT CAppForm::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
[!if ACTIONMAPPER || DPLAYVOICE]
    switch( message )
    {
        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
[!if ACTIONMAPPER]
                case IDM_CONFIGINPUT:
                    m_UserInput.bDoConfigureInput = TRUE;
                    break;

                case IDC_CHANGEDEVICE:
                case IDM_CHANGEDEVICE:
                    m_UserInput.bDoConfigureDisplay = TRUE;
                    return 0; // Don't hand off to parent
[!endif]
[!if DPLAYVOICE]

                case IDM_CONFIGVOICE:
                    m_UserInput.bDoConfigureVoice = TRUE;
                    break;
[!endif]
            }
            break;
        }
    }
    
[!endif]
    return CFormView ::WindowProc(message, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Name: OnChangeDevice()
// Desc: Needed to enable dlg menu item 
//-----------------------------------------------------------------------------
void CAppFrameWnd::OnChangeDevice() 
{
[!if ACTIONMAPPER]
    g_AppFormView->m_UserInput.bDoConfigureDisplay = TRUE;
[!else]
    g_AppFormView->OnChangeDevice();
[!endif]
}




[!if ACTIONMAPPER]
//-----------------------------------------------------------------------------
// Name: OnConfigInput()
// Desc: 
//-----------------------------------------------------------------------------
void CAppFrameWnd::OnConfigInput() 
{
    g_AppFormView->m_UserInput.bDoConfigureInput = TRUE;
}




[!endif]
[!if DPLAYVOICE]
//-----------------------------------------------------------------------------
// Name: OnConfigVoice()
// Desc: 
//-----------------------------------------------------------------------------
void CAppFrameWnd::OnConfigVoice() 
{
    g_AppFormView->m_UserInput.bDoConfigureVoice = TRUE;
}




[!endif]
[!if DPLAYVOICE]
//-----------------------------------------------------------------------------
// Name: UserConfigVoice()
// Desc: Allow user to configure the voice settings
//-----------------------------------------------------------------------------
HRESULT CAppForm::UserConfigVoice()
{
    HRESULT hr;
    BOOL bWasFullscreen = FALSE;
   
    // Can't display dialogs in fullscreen mode
    if( m_bWindowed == FALSE )
    {
        bWasFullscreen = TRUE;

        if( FAILED( ToggleFullscreen() ) )
        {
            DisplayErrorMsg( D3DAPPERR_RESETFAILED, MSGERR_APPMUSTEXIT );
            return E_FAIL;
        }
    }

    // Configure the voice settings, store the settings in 
    // m_guidDVSessionCT & m_dvClientConfig
    // TODO: replace with a fancier graphics layer like D3D.
    if( m_pNetVoice )
    {
        hr = m_pNetVoice->DoVoiceSetupDialog( g_hInst, m_hWndTopLevelParent, &m_guidDVSessionCT, &m_dvClientConfig );

        // If the settings dialog was not canceled, then change the settings
        if( hr != DVERR_USERCANCEL )
            m_pNetVoice->ChangeVoiceClientSettings( &m_dvClientConfig );
    }

    // Return to fullscreen mode after dialogs
    if( bWasFullscreen )
    {
        if( FAILED( ToggleFullscreen() ) )
        {
            DisplayErrorMsg( D3DAPPERR_RESETFAILED, MSGERR_APPMUSTEXIT );
            return E_FAIL;
        }
    }
    
    return S_OK;
}




[!endif]
//-----------------------------------------------------------------------------
// Name: CAppForm::InvalidateDeviceObjects()
// Desc: Invalidates device objects.  Paired with RestoreDeviceObjects()
//-----------------------------------------------------------------------------
HRESULT CAppForm::InvalidateDeviceObjects()
{
    // TODO: Cleanup any objects created in RestoreDeviceObjects()
[!if D3DFONT]
    m_pFont->InvalidateDeviceObjects();
[!else]
    SAFE_RELEASE( m_pD3DXFont );
[!endif]
[!if ACTIONMAPPER]
    SAFE_RELEASE( m_pDIConfigSurface );
[!endif]

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CAppForm::DeleteDeviceObjects()
// Desc: Paired with InitDeviceObjects()
//       Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.  
//-----------------------------------------------------------------------------
HRESULT CAppForm::DeleteDeviceObjects()
{
    // TODO: Cleanup any objects created in InitDeviceObjects()
[!if D3DFONT]
    m_pFont->DeleteDeviceObjects();
[!endif]
[!if SHOW_TRIANGLE]
    SAFE_RELEASE( m_pVB );
[!endif]
[!if SHOW_TEAPOT]
    SAFE_RELEASE( m_pD3DXMesh );
[!endif]

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CAppForm::FinalCleanup()
// Desc: Paired with OneTimeSceneInit()
//       Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CAppForm::FinalCleanup()
{
    // TODO: Perform any final cleanup needed
[!if D3DFONT]
    // Cleanup D3D font
    SAFE_DELETE( m_pFont );

[!endif]
[!if DINPUT]
    // Cleanup DirectInput
    CleanupDirectInput();

[!endif]
[!if DMUSIC || DSOUND]
    // Cleanup DirectX audio objects
    SAFE_DELETE( m_pBounceSound );
[!if DMUSIC]
    SAFE_DELETE( m_pMusicManager );
[!else]
    SAFE_DELETE( m_pSoundManager );
[!endif]

[!endif]
[!if DPLAY]
    // Cleanup DirectPlay
    CleanupDirectPlay();

    // Cleanup COM
    CoUninitialize();

[!endif]
[!if REGACCESS]
    // Write the settings to the registry
    WriteSettings();

[!endif]
    return S_OK;
}




[!if DPLAY]
//-----------------------------------------------------------------------------
// Name: StaticDirectPlayMessageHandler
// Desc: Static callback helper to call into CAppForm class
//-----------------------------------------------------------------------------
HRESULT WINAPI CAppForm::StaticDirectPlayMessageHandler( PVOID pvUserContext, 
                                                                  DWORD dwMessageId, 
                                                                  PVOID pMsgBuffer )
{
    if( g_AppFormView )
        return g_AppFormView->DirectPlayMessageHandler( pvUserContext, dwMessageId, pMsgBuffer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayMessageHandler
// Desc: Handler for DirectPlay messages.  This function is called by
//       the DirectPlay message handler pool of threads, so be careful of thread
//       synchronization problems with shared memory
//-----------------------------------------------------------------------------
HRESULT CAppForm::DirectPlayMessageHandler( PVOID pvUserContext, 
                                                     DWORD dwMessageId, 
                                                     PVOID pMsgBuffer )
{
    // Try not to stay in this message handler for too long, otherwise
    // there will be a backlog of data.  The best solution is to 
    // queue data as it comes in, and then handle it on other threads.
    
    // This function is called by the DirectPlay message handler pool of 
    // threads, so be careful of thread synchronization problems with shared memory

    switch( dwMessageId )
    {
        case DPN_MSGID_CREATE_PLAYER:
        {
            HRESULT hr;
            PDPNMSG_CREATE_PLAYER pCreatePlayerMsg;
            pCreatePlayerMsg = (PDPNMSG_CREATE_PLAYER)pMsgBuffer;

            // Get the peer info and extract its name
            DWORD dwSize = 0;
            DPN_PLAYER_INFO* pdpPlayerInfo = NULL;
            hr = m_pDP->GetPeerInfo( pCreatePlayerMsg->dpnidPlayer, 
                                     pdpPlayerInfo, &dwSize, 0 );
            if( FAILED(hr) && hr != DPNERR_BUFFERTOOSMALL )
                return DXTRACE_ERR( TEXT("GetPeerInfo"), hr );
            pdpPlayerInfo = (DPN_PLAYER_INFO*) new BYTE[ dwSize ];
            ZeroMemory( pdpPlayerInfo, dwSize );
            pdpPlayerInfo->dwSize = sizeof(DPN_PLAYER_INFO);
            hr = m_pDP->GetPeerInfo( pCreatePlayerMsg->dpnidPlayer, 
                                     pdpPlayerInfo, &dwSize, 0 );
            if( FAILED(hr) )
                return DXTRACE_ERR( TEXT("GetPeerInfo"), hr );

            // Create a new and fill in a APP_PLAYER_INFO
            APP_PLAYER_INFO* pPlayerInfo = new APP_PLAYER_INFO;
            ZeroMemory( pPlayerInfo, sizeof(APP_PLAYER_INFO) );
            pPlayerInfo->lRefCount   = 1;
            pPlayerInfo->dpnidPlayer = pCreatePlayerMsg->dpnidPlayer;

            // This stores a extra TCHAR copy of the player name for 
            // easier access.  This will be redundant copy since DPlay 
            // also keeps a copy of the player name in GetPeerInfo()
            DXUtil_ConvertWideStringToGenericCch( pPlayerInfo->strPlayerName, 
                                               pdpPlayerInfo->pwszName, MAX_PATH );

            if( pdpPlayerInfo->dwPlayerFlags & DPNPLAYER_LOCAL )
            {
                m_dpnidLocalPlayer = pCreatePlayerMsg->dpnidPlayer;
                m_pLocalPlayerInfo = pPlayerInfo;

                // Increase the ref if this is the local player, so the struct 
                // won't be deleted when DirectPlay shuts down.  The
                // main window thread will release the struct when it is done
                pPlayerInfo->lRefCount++;
            }
            else
            {
                if( m_pNetConnectWizard->IsHostPlayer() )
                {
                    // If the local player is the host and 
                    // this DPN_MSGID_CREATE_PLAYER is not for the local player
                    // then set the m_fWorldSyncTimer to fire immediately so
                    // the new player will get the state of the world
                    m_fWorldSyncTimer = 0.0f;
                }
            }

            // Add the APP_PLAYER_INFO to the circular linked list, m_PlayInfoList
            pPlayerInfo->pNext = m_PlayInfoList.pNext;
            pPlayerInfo->pPrev = &m_PlayInfoList;
            m_PlayInfoList.pNext->pPrev = pPlayerInfo;    
            m_PlayInfoList.pNext = pPlayerInfo;    

            SAFE_DELETE_ARRAY( pdpPlayerInfo );

            // Tell DirectPlay to store this pPlayerInfo 
            // pointer in the pvPlayerContext.
            pCreatePlayerMsg->pvPlayerContext = pPlayerInfo;

            // Update the number of active players, and if the app needs to 
            // tell the UI immediately about this, then post a message to 
            // the window thread.  This keeps the DirectPlay message handler 
            // from blocking
            InterlockedIncrement( &m_lNumberOfActivePlayers );
            break;
        }

        case DPN_MSGID_RECEIVE:
        {
            PDPNMSG_RECEIVE pReceiveMsg;
            pReceiveMsg = (PDPNMSG_RECEIVE)pMsgBuffer;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pReceiveMsg->pvPlayerContext;

            GAMEMSG_GENERIC* pMsg = (GAMEMSG_GENERIC*) pReceiveMsg->pReceiveData;
            switch( pMsg->nType )
            {
                case GAME_MSGID_INPUTSTATE:
                {
                    // Update the APP_PLAYER_INFO struct associated with this
                    // network player with the data send in the GAMEMSG_INPUTSTATE.
                    GAMEMSG_INPUTSTATE* pInputStateMsg = (GAMEMSG_INPUTSTATE*) pMsg;

                    // Enter player critical section before accessing player's state data 
                    // otherwise the main thread or other DirectPlay threads may access the data
                    // while this thread is changing it.
                    PLAYER_LOCK();                  

[!if ACTIONMAPPER]
                    pPlayerInfo->fAxisRotateLR = pInputStateMsg->fAxisRotateLR;
                    pPlayerInfo->fAxisRotateUD = pInputStateMsg->fAxisRotateUD;
[!else]
                    pPlayerInfo->bRotateUp    = pInputStateMsg->bRotateUp;
                    pPlayerInfo->bRotateDown  = pInputStateMsg->bRotateDown;
                    pPlayerInfo->bRotateLeft  = pInputStateMsg->bRotateLeft;
                    pPlayerInfo->bRotateRight = pInputStateMsg->bRotateRight;
[!endif]

                    PLAYER_UNLOCK();                // leave player context CS
                    break;
                }

                case GAME_MSGID_WORLDSTATE:
                {
                    // Enter world state critical section before accessing world state data 
                    // otherwise the main thread or other DirectPlay threads may access the data
                    // while this thread is changing it.
                    WORLD_LOCK();

                    // Update the world state with the data from GAMEMSG_WORLDSTATE
                    GAMEMSG_WORLDSTATE* pMsgWorldState = (GAMEMSG_WORLDSTATE*) pMsg;
                    m_fWorldRotX = pMsgWorldState->fWorldRotX;
                    m_fWorldRotY = pMsgWorldState->fWorldRotY;

                    // Leave the critical section
                    WORLD_UNLOCK();
                    break;
                }

                case GAME_MSGID_HOSTPAUSE:
                {
                    GAMEMSG_HOSTPAUSE* pMsgPause = (GAMEMSG_HOSTPAUSE*) pMsg;

                    // Update the pause state with the data from GAMEMSG_HOSTPAUSE
                    m_bHostPausing = pMsgPause->bHostPause;
                    break;
                }
            }
            break;
        }

        case DPN_MSGID_DESTROY_PLAYER:
        {
            PDPNMSG_DESTROY_PLAYER pDestroyPlayerMsg;
            pDestroyPlayerMsg = (PDPNMSG_DESTROY_PLAYER)pMsgBuffer;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pDestroyPlayerMsg->pvPlayerContext;

            PLAYER_LOCK();                  // enter player context CS

            // Remove pPlayerInfo from the circular linked list
            pPlayerInfo->pNext->pPrev = pPlayerInfo->pPrev;
            pPlayerInfo->pPrev->pNext = pPlayerInfo->pNext;

            PLAYER_RELEASE( pPlayerInfo );  // Release player and cleanup if needed
            PLAYER_UNLOCK();                // leave player context CS

            // Update the number of active players, and if the app needs to 
            // tell the UI immediately about this, then post a message to 
            // the window thread.  This keeps the DirectPlay message handler 
            // from blocking
            InterlockedDecrement( &m_lNumberOfActivePlayers );
            break;
        }

        case DPN_MSGID_TERMINATE_SESSION:
        {
            PDPNMSG_TERMINATE_SESSION pTerminateSessionMsg;
            pTerminateSessionMsg = (PDPNMSG_TERMINATE_SESSION)pMsgBuffer;

            m_hrNet = DPNERR_CONNECTIONLOST;

            // Close the window, which shuts down the app
            PostMessage( WM_CLOSE, 0, 0 );
            break;
        }
    }

    // Make sure the DirectPlay MessageHandler calls the CNetConnectWizard handler, 
    // so it can be informed of messages such as DPN_MSGID_ENUM_HOSTS_RESPONSE.
    if( m_pNetConnectWizard )
        return m_pNetConnectWizard->MessageHandler( pvUserContext, dwMessageId, 
                                                    pMsgBuffer );
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: StaticDirectPlayLobbyMessageHandler
// Desc: Static callback helper to call into CAppForm class
//-----------------------------------------------------------------------------
HRESULT WINAPI CAppForm::StaticDirectPlayLobbyMessageHandler( PVOID pvUserContext, 
                                                                  DWORD dwMessageId, 
                                                                  PVOID pMsgBuffer )
{
    if( g_AppFormView )
        return g_AppFormView->DirectPlayLobbyMessageHandler( pvUserContext, dwMessageId, pMsgBuffer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayLobbyMessageHandler
// Desc: Handler for DirectPlay lobby messages.  This function is called by
//       the DirectPlay lobby message handler pool of threads, so be careful of 
//       thread synchronization problems with shared memory
//-----------------------------------------------------------------------------
HRESULT CAppForm::DirectPlayLobbyMessageHandler( PVOID pvUserContext, 
                                                          DWORD dwMessageId, 
                                                          PVOID pMsgBuffer )
{
    switch( dwMessageId )
    {
        case DPL_MSGID_CONNECT:
        {
            PDPL_MESSAGE_CONNECT pConnectMsg;
            pConnectMsg = (PDPL_MESSAGE_CONNECT)pMsgBuffer;

            // The CNetConnectWizard will handle this message for us,
            // so there is nothing we need to do here for this simple
            // sample.
            break;
        }

        case DPL_MSGID_DISCONNECT:
        {
            PDPL_MESSAGE_DISCONNECT pDisconnectMsg;
            pDisconnectMsg = (PDPL_MESSAGE_DISCONNECT)pMsgBuffer;

            // We should free any data associated with the lobby 
            // client here, but there is none.
            break;
        }

        case DPL_MSGID_RECEIVE:
        {
            PDPL_MESSAGE_RECEIVE pReceiveMsg;
            pReceiveMsg = (PDPL_MESSAGE_RECEIVE)pMsgBuffer;

            // The lobby client sent us data.  This sample doesn't
            // expected data from the client, but it is useful 
            // for more complex apps.
            break;
        }

        case DPL_MSGID_CONNECTION_SETTINGS:
        {
            PDPL_MESSAGE_CONNECTION_SETTINGS pConnectionStatusMsg;
            pConnectionStatusMsg = (PDPL_MESSAGE_CONNECTION_SETTINGS)pMsgBuffer;

            // The lobby client has changed the connection settings.  
            // This simple sample doesn't handle this, but more complex apps may
            // want to.
            break;
        }
    }

    // Make sure the DirectPlay MessageHandler calls the CNetConnectWizard handler, 
    // so the wizard can be informed of lobby messages such as DPL_MSGID_CONNECT
    if( m_pNetConnectWizard )
        return m_pNetConnectWizard->LobbyMessageHandler( pvUserContext, dwMessageId, 
                                                         pMsgBuffer );
    
    return S_OK;
}




[!endif]
[!if DPLAYVOICE]
//-----------------------------------------------------------------------------
// Name: StaticDirectPlayVoiceServerMessageHandler
// Desc: Static callback helper to call into CAppForm class
//-----------------------------------------------------------------------------
HRESULT WINAPI CAppForm::StaticDirectPlayVoiceServerMessageHandler( PVOID pvUserContext, 
                                                                  DWORD dwMessageId, 
                                                                  PVOID pMsgBuffer )
{
    if( g_AppFormView )
        return g_AppFormView->DirectPlayVoiceServerMessageHandler( pvUserContext, dwMessageId, pMsgBuffer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayVoiceServerMessageHandler()
// Desc: The callback for DirectPlayVoice server messages.  
//-----------------------------------------------------------------------------
HRESULT CAppForm::DirectPlayVoiceServerMessageHandler( LPVOID lpvUserContext, DWORD dwMessageType,
                                                                LPVOID lpMessage )
{
    UNREFERENCED_PARAMETER( lpvUserContext );
    UNREFERENCED_PARAMETER( dwMessageType );
    UNREFERENCED_PARAMETER( lpMessage );

    // This simple sample doesn't respond to any server messages
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: StaticDirectPlayVoiceClientMessageHandler
// Desc: Static callback helper to call into CAppForm class
//-----------------------------------------------------------------------------
HRESULT WINAPI CAppForm::StaticDirectPlayVoiceClientMessageHandler( PVOID pvUserContext, 
                                                                  DWORD dwMessageId, 
                                                                  PVOID pMsgBuffer )
{
    if( g_AppFormView )
        return g_AppFormView->DirectPlayVoiceClientMessageHandler( pvUserContext, dwMessageId, pMsgBuffer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayVoiceClientMessageHandler()
// Desc: The callback for DirectPlayVoice client messages.  
//       This handles client messages and updates the UI the whenever a client 
//       starts or stops talking.  
//-----------------------------------------------------------------------------
HRESULT CAppForm::DirectPlayVoiceClientMessageHandler( LPVOID lpvUserContext, DWORD dwMessageType,
                                                                LPVOID lpMessage )
{
    UNREFERENCED_PARAMETER( lpvUserContext );
    // Try not to stay in this message handler for too long, otherwise
    // there will be a backlog of data.  The best solution is to 
    // queue data as it comes in, and then handle it on other threads.
    
    // This function is called by the DirectPlay message handler pool of 
    // threads, so be care of thread synchronization problems with shared memory

    HRESULT hr;

    switch( dwMessageType )
    {
        case DVMSGID_CREATEVOICEPLAYER:
        {
            DVMSG_CREATEVOICEPLAYER* pCreateVoicePlayerMsg = (DVMSG_CREATEVOICEPLAYER*) lpMessage;
            APP_PLAYER_INFO* pPlayerInfo = NULL;

            // Enter player critical section before accessing player's state data 
            // otherwise the main thread or other DirectPlay threads may access the data
            // while this thread is changing it.
            PLAYER_LOCK(); 

            // Get the player context associated with this DPNID
            hr = m_pDP->GetPlayerContext( pCreateVoicePlayerMsg->dvidPlayer, 
                                          (LPVOID* const) &pPlayerInfo, 0);

            if( FAILED(hr) || pPlayerInfo == NULL )
            {
                // The player who sent this may have gone away before this 
                // message was handled, so just ignore it
                PLAYER_UNLOCK();
                break;
            }

            // Addref player struct, so it can used freely by the voice layer
            PLAYER_ADDREF( pPlayerInfo ); 

            pPlayerInfo->bHalfDuplex = ((pCreateVoicePlayerMsg->dwFlags & DVPLAYERCAPS_HALFDUPLEX) != 0);

            PLAYER_UNLOCK(); // leave player context CS

            // Set voice context value
            pCreateVoicePlayerMsg->pvPlayerContext = pPlayerInfo;

            // We're leaving the extra reference, so the voice layer will 
            // own that reference
            break;
        }

        case DVMSGID_DELETEVOICEPLAYER:
        {
            DVMSG_DELETEVOICEPLAYER* pMsg = (DVMSG_DELETEVOICEPLAYER*) lpMessage;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pMsg->pvPlayerContext;

            // Release our extra reference on the player info that we have for the voice
            // context value.  
            PLAYER_LOCK();
            PLAYER_RELEASE( pPlayerInfo );  
            PLAYER_UNLOCK();
            break;
        }            

        case DVMSGID_RECORDSTART:             
        { 
            DVMSG_RECORDSTART* pMsg = (DVMSG_RECORDSTART*) lpMessage;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pMsg->pvLocalPlayerContext;

            PLAYER_LOCK();
            if( pPlayerInfo )
                pPlayerInfo->bTalking = TRUE;   
            PLAYER_UNLOCK();
            break;
        }

        case DVMSGID_RECORDSTOP:             
        {
            DVMSG_RECORDSTOP* pMsg = (DVMSG_RECORDSTOP*) lpMessage;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pMsg->pvLocalPlayerContext;

            PLAYER_LOCK();
            if( pPlayerInfo )
                pPlayerInfo->bTalking = FALSE;  
            PLAYER_UNLOCK();
            break;
        }

        case DVMSGID_PLAYERVOICESTART:
        {
            DVMSG_PLAYERVOICESTART* pMsg = (DVMSG_PLAYERVOICESTART*) lpMessage;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pMsg->pvPlayerContext;

            PLAYER_LOCK();
            if( pPlayerInfo )
                pPlayerInfo->bTalking = TRUE;   
            PLAYER_UNLOCK();
            break;
        }

        case DVMSGID_PLAYERVOICESTOP:
        {
            DVMSG_PLAYERVOICESTOP* pMsg = (DVMSG_PLAYERVOICESTOP*) lpMessage;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pMsg->pvPlayerContext;

            PLAYER_LOCK();
            if( pPlayerInfo )
                pPlayerInfo->bTalking = FALSE;  
            PLAYER_UNLOCK();
            break;
        }
    }

    return S_OK;
}




[!endif]
[!if DPLAY]
//-----------------------------------------------------------------------------
// Name: CleanupDirectPlay()
// Desc: Cleanup DirectPlay 
//-----------------------------------------------------------------------------
VOID CAppForm::CleanupDirectPlay()
{
[!if DPLAYVOICE]
    // Disconnect from the DirectPlayVoice session, 
    // and destroy it if we are the host player.
    SAFE_DELETE( m_pNetVoice ); 

[!endif]
    // Cleanup DirectPlay and helper classes
    if( m_pNetConnectWizard )
        m_pNetConnectWizard->Shutdown();

    if( m_pDP )
    {
        m_pDP->Close(0);
        SAFE_RELEASE( m_pDP );
    }

    if( m_pLobbiedApp )
    {
        m_pLobbiedApp->Close( 0 );
        SAFE_RELEASE( m_pLobbiedApp );
    }    

    PLAYER_LOCK();                  // enter player context CS
    PLAYER_RELEASE( m_pLocalPlayerInfo ); // Release player and cleanup if needed
    PLAYER_UNLOCK();                // leave player context CS

    // Don't delete the wizard until we know that 
    // DirectPlay is out of its message handlers.
    // This will be true after Close() has been called. 
    SAFE_DELETE( m_pNetConnectWizard );
    DeleteCriticalSection( &g_csPlayerContext );
    DeleteCriticalSection( &g_csWorldStateContext );

    if( m_hrNet == DPNERR_CONNECTIONLOST )
    {
        MessageBox( TEXT("The DirectPlay session was lost. ")
                    TEXT("The sample will now quit."),
                    TEXT("DirectPlay Sample"), MB_OK | MB_ICONERROR );
    }
}



[!endif]
[!if DINPUT]
//-----------------------------------------------------------------------------
// Name: CleanupDirectInput()
// Desc: Cleanup DirectInput 
//-----------------------------------------------------------------------------
VOID CAppForm::CleanupDirectInput()
{
[!if KEYBOARD]
    // Cleanup DirectX input objects
    SAFE_RELEASE( m_pKeyboard );
    SAFE_RELEASE( m_pDI );

[!endif]
[!if ACTIONMAPPER]
    if( NULL == m_pInputDeviceManager )
        return;

    // Get access to the list of semantically-mapped input devices
    // to delete all InputDeviceState structs
    CInputDeviceManager::DeviceInfo* pDeviceInfos;
    DWORD dwNumDevices;
    m_pInputDeviceManager->GetDevices( &pDeviceInfos, &dwNumDevices );

    for( DWORD i=0; i<dwNumDevices; i++ )
    {
        InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;
        SAFE_DELETE( pInputDeviceState );
        pDeviceInfos[i].pParam = NULL;
    }

    // Cleanup DirectX input objects
    SAFE_DELETE( m_pInputDeviceManager );

[!endif]
}




[!endif]
//-----------------------------------------------------------------------------
// Name: InitInstance()
// Desc: This is the main entry point for the application. The MFC window stuff
//       is initialized here. See also the main initialization routine for the
//       CAppForm class, which is called indirectly from here.
//-----------------------------------------------------------------------------
BOOL CApp::InitInstance()
{
    // Asscociate the MFC app with the frame window and doc/view classes
    AddDocTemplate( new CSingleDocTemplate( IDR_MAINFRAME,
                                            RUNTIME_CLASS(CAppDoc),
                                            RUNTIME_CLASS(CAppFrameWnd),
                                            RUNTIME_CLASS(CAppForm) ) );

    // Dispatch commands specified on the command line (req'd by MFC). This
    // also initializes the the CAppDoc, CAppFrameWnd, and CAppForm classes.
    CCommandLineInfo cmdInfo;
    ParseCommandLine( cmdInfo );
    if( !ProcessShellCommand( cmdInfo ) )
        return FALSE;

    if( !g_AppFormView->IsReady() )
        return FALSE;

    g_AppFormView->GetParentFrame()->RecalcLayout();
    g_AppFormView->ResizeParentToFit( FALSE ); 
    
    m_pMainWnd->SetWindowText( g_strAppTitle );
    m_pMainWnd->UpdateWindow();

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: LoadFrame()
// Desc: Uses idle time to render the 3D scene.
//-----------------------------------------------------------------------------
BOOL CAppFrameWnd::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
    BOOL bResult = CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
    
[!if !MENUBAR]
    // Remove the menu bar.  Do it this way because CFrameWnd::LoadFrame() requires 
    // there be a menu called IDR_MAINFRAME.
	SetMenu( NULL );
	
[!endif]
    LoadAccelTable( MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

    return bResult;
}




//-----------------------------------------------------------------------------
// Name: OnIdle()
// Desc: Uses idle time to render the 3D scene.
//-----------------------------------------------------------------------------
BOOL CApp::OnIdle( LONG )
{
    // Do not render if the app is minimized
    if( m_pMainWnd->IsIconic() )
        return FALSE;

    TCHAR strStatsPrev[200];

    lstrcpy(strStatsPrev, g_AppFormView->PstrFrameStats());

    // Update and render a frame
    if( g_AppFormView->IsReady() )
    {
        g_AppFormView->CheckForLostFullscreen();
        g_AppFormView->RenderScene();
    }

    // Keep requesting more idle time
    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: PreCreateWindow()
// Desc: Change the window style (so it cannot maximize or be sized) before
//       the main frame window is created.
//-----------------------------------------------------------------------------
BOOL CAppFrameWnd::PreCreateWindow( CREATESTRUCT& cs )
{
    cs.style = WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX;

    return CFrameWnd::PreCreateWindow( cs );
}




//-----------------------------------------------------------------------------
// Name: ~CAppForm()
// Desc: Destructor for the dialog resource form. Shuts down the app
//-----------------------------------------------------------------------------
CAppForm::~CAppForm()
{
    Cleanup3DEnvironment();
    SAFE_RELEASE( m_pD3D );
    FinalCleanup();
}




//-----------------------------------------------------------------------------
// Name: OnToggleFullScreen()
// Desc: Called when user toggles the fullscreen mode
//-----------------------------------------------------------------------------
void CAppForm::OnToggleFullScreen()
{
    ToggleFullscreen();
}




//-----------------------------------------------------------------------------
// Name: OnChangeDevice()
// Desc: Use hit the "Change Device.." button. Display the dialog for the user
//       to select a new device/mode, and call Change3DEnvironment to
//       use the new device/mode.
//-----------------------------------------------------------------------------
VOID CAppForm::OnChangeDevice()
{
    Pause(true);

    UserSelectNewDevice();

    // Update UI
    UpdateUIForDeviceCapabilites();

    Pause(false);
}




//-----------------------------------------------------------------------------
// Name: AdjustWindowForChange()
// Desc: Adjusts the window properties for windowed or fullscreen mode
//-----------------------------------------------------------------------------
HRESULT CAppForm::AdjustWindowForChange()
{
    if( m_bWindowed )
    {
        ::ShowWindow( m_hwndRenderFullScreen, SW_HIDE );
        CD3DApplication::m_hWnd = m_hwndRenderWindow;
[!if ACTIONMAPPER]

        // Tell the action mapper that the focus wnd has changed
        m_pInputDeviceManager->SetFocus( m_hWndTopLevelParent );
[!endif]
[!if KEYBOARD]

        // Tell the action mapper that the focus wnd has changed
        m_pKeyboard->SetCooperativeLevel( m_hWndTopLevelParent, 
                                                DISCL_NONEXCLUSIVE | 
                                                DISCL_FOREGROUND | 
                                                DISCL_NOWINKEY );
[!endif]
    }
    else
    {
        if( ::IsIconic( m_hwndRenderFullScreen ) )
            ::ShowWindow( m_hwndRenderFullScreen, SW_RESTORE );
        ::ShowWindow( m_hwndRenderFullScreen, SW_SHOW );
        CD3DApplication::m_hWnd = m_hwndRenderFullScreen;
[!if ACTIONMAPPER]

        // Tell the action mapper that the focus wnd has changed
        m_pInputDeviceManager->SetFocus( m_hwndRenderFullScreen );
[!endif]
[!if KEYBOARD]

        // Tell the action mapper that the focus wnd has changed
        m_pKeyboard->SetCooperativeLevel( m_hwndRenderFullScreen, 
                                                DISCL_NONEXCLUSIVE | 
                                                DISCL_FOREGROUND | 
                                                DISCL_NOWINKEY );
[!endif]
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FullScreenWndProc()
// Desc: The WndProc funtion used when the app is in fullscreen mode. This is
//       needed simply to trap the ESC key.
//-----------------------------------------------------------------------------
LRESULT CALLBACK FullScreenWndProc( HWND hWnd, UINT msg, WPARAM wParam,
                                    LPARAM lParam )
{
    if( msg == WM_CLOSE )
    {
        // User wants to exit, so go back to windowed mode and exit for real
        g_AppFormView->OnToggleFullScreen();
        g_App.GetMainWnd()->PostMessage( WM_CLOSE, 0, 0 );
    }
    else if( msg == WM_SETCURSOR )
    {
        SetCursor( NULL );
    }
    else if( msg == WM_KEYUP && wParam == VK_ESCAPE )
    {
        // User wants to leave fullscreen mode
        g_AppFormView->OnToggleFullScreen();
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: CheckForLostFullscreen()
// Desc: If fullscreen and device was lost (probably due to alt-tab), 
//       automatically switch to windowed mode
//-----------------------------------------------------------------------------
HRESULT CAppForm::CheckForLostFullscreen()
{
    HRESULT hr;

    if( m_bWindowed )
        return S_OK;

    if( FAILED( hr = m_pd3dDevice->TestCooperativeLevel() ) )
        ForceWindowed();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: UpdateUIForDeviceCapabilites()
// Desc: Whenever we get a new device, call this function to enable/disable the
//       appropiate UI controls to match the device's capabilities.
//-----------------------------------------------------------------------------
VOID CAppForm::UpdateUIForDeviceCapabilites()
{
    // TODO: Check the capabilities of the device and update the UI as needed
    DWORD dwCaps = m_d3dCaps.RasterCaps;
    UNREFERENCED_PARAMETER( dwCaps );
}




//-----------------------------------------------------------------------------
// Name: OnInitialUpdate()
// Desc: When the AppForm object is created, this function is called to
//       initialize it. Here we getting access ptrs to some of the controls,
//       and setting the initial state of some of them as well.
//-----------------------------------------------------------------------------
VOID CAppForm::OnInitialUpdate()
{
    // Update the UI
    CFormView::OnInitialUpdate();

    // Get the top level parent hwnd
    m_hWndTopLevelParent = GetTopLevelParent()->GetSafeHwnd();

    // Save static reference to the render window
    m_hwndRenderWindow = GetDlgItem(IDC_RENDERVIEW)->GetSafeHwnd();

    // Register a class for a fullscreen window
    WNDCLASS wndClass = { CS_HREDRAW | CS_VREDRAW, FullScreenWndProc, 0, 0, NULL,
                          NULL, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL,
                          _T("Fullscreen Window") };
    RegisterClass( &wndClass );

    // We create the fullscreen window (not visible) at startup, so it can
    // be the focus window.  The focus window can only be set at CreateDevice
    // time, not in a Reset, so ToggleFullscreen wouldn't work unless we have
    // already set up the fullscreen focus window.
    m_hwndRenderFullScreen = CreateWindow( _T("Fullscreen Window"), NULL,
                                           WS_POPUP, CW_USEDEFAULT,
                                           CW_USEDEFAULT, 100, 100,
                                           m_hWndTopLevelParent, 0L, NULL, 0L );

    // Note that for the MFC samples, the device window and focus window
    // are not the same.
    CD3DApplication::m_hWnd = m_hwndRenderWindow;
    CD3DApplication::m_hWndFocus = m_hwndRenderFullScreen;
    CD3DApplication::Create( AfxGetInstanceHandle() );

    // TODO: Update the UI as needed
}




