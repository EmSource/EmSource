//-----------------------------------------------------------------------------
// File: $$root$$.cpp
//
// Desc: DirectX window application created by the DirectX AppWizard
//-----------------------------------------------------------------------------
#define STRICT
$$IF(DINPUT)
#define DIRECTINPUT_VERSION 0x0800
$$ENDIF
#include <windows.h>
#include <basetsd.h>
#include <math.h>
#include <stdio.h>
#include <DXErr9.h>
#include <tchar.h>
$$IF(DINPUT)
#include <dinput.h>
$$ENDIF
$$IF(DPLAY)
#include <dplay8.h>
#include <dplobby8.h>
$$ENDIF
$$IF(ACTIONMAPPER)
#include "DIUtil.h"
$$ENDIF
$$IF(DMUSIC)
#include "DMUtil.h"
$$ENDIF
$$IF(DSOUND)
#include "DSUtil.h"
$$ENDIF
$$IF(DPLAY)
#include "NetConnect.h"
$$ENDIF
$$IF(DPLAYVOICE)
#include "NetVoice.h"
$$ENDIF
#include "DXUtil.h"
#include "resource.h"
#include "$$root$$.h"



$$IF(ACTIONMAPPER||DPLAY)
//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
// This GUID must be unique for every game, and the same for 
// every instance of this app.  // $$GUIDMSG$$
$$IF(DPLAY)
// The GUID allows DirectPlay to find other instances of the same game on
// the network.  
$$ENDIF // end DPLAY
$$IF(ACTIONMAPPER)
// The GUID allows DirectInput to remember input settings
$$ENDIF // end ACTIONMAPPER
GUID g_guidApp = $$GUIDSTRUCT$$;


$$ENDIF // end (ACTIONMAPPER|DPLAY)
$$IF(ACTIONMAPPER)




// Input semantics used by this app
enum INPUT_SEMANTICS
{
    // Gameplay semantics
    // TODO: change as needed
    INPUT_ROTATE_AXIS_LR=1, INPUT_ROTATE_AXIS_UD,       
    INPUT_ROTATE_LEFT,      INPUT_ROTATE_RIGHT,    
    INPUT_ROTATE_UP,        INPUT_ROTATE_DOWN,
    INPUT_CONFIG_INPUT,     
$$IF(DPLAYVOICE)
    INPUT_CONFIG_VOICE,     
$$ENDIF
$$IF(DMUSIC || DSOUND)
    INPUT_PLAY_SOUND,       
$$ENDIF
};

// Actions used by this app
DIACTION g_rgGameAction[] =
{
    // TODO: change as needed.  Be sure to delete user map files 
    // (C:\Program Files\Common Files\DirectX\DirectInput\User Maps\*.ini)
    // after changing this, otherwise settings won't reset and will be read 
    // from the out of date ini files 

    // Device input (joystick, etc.) that is pre-defined by DInput, according
    // to genre type. The genre for this app is space simulators.
    { INPUT_ROTATE_AXIS_LR,  DIAXIS_3DCONTROL_LATERAL,      0, TEXT("Rotate left/right"), },
    { INPUT_ROTATE_AXIS_UD,  DIAXIS_3DCONTROL_MOVE,         0, TEXT("Rotate up/down"), },
$$IF(DMUSIC || DSOUND)
    { INPUT_PLAY_SOUND,      DIBUTTON_3DCONTROL_SPECIAL,    0, TEXT("Play sound"), },
$$ENDIF

    // Keyboard input mappings
    { INPUT_ROTATE_LEFT,     DIKEYBOARD_LEFT,               0, TEXT("Rotate left"), },
    { INPUT_ROTATE_RIGHT,    DIKEYBOARD_RIGHT,              0, TEXT("Rotate right"), },
    { INPUT_ROTATE_UP,       DIKEYBOARD_UP,                 0, TEXT("Rotate up"), },
    { INPUT_ROTATE_DOWN,     DIKEYBOARD_DOWN,               0, TEXT("Rotate down"), },
$$IF(DMUSIC || DSOUND)
    { INPUT_PLAY_SOUND,      DIKEYBOARD_F5,                 0, TEXT("Play sound"), },
$$ENDIF
    { INPUT_CONFIG_INPUT,    DIKEYBOARD_F3,                 DIA_APPFIXED, TEXT("Configure Input"), },    
$$IF(DPLAYVOICE)
    { INPUT_CONFIG_VOICE,    DIKEYBOARD_F4,                 DIA_APPFIXED, TEXT("Configure Voice"), },    
$$ENDIF
};

#define NUMBER_OF_GAMEACTIONS    (sizeof(g_rgGameAction)/sizeof(DIACTION))




$$ENDIF
//-----------------------------------------------------------------------------
// Function prototypes 
//-----------------------------------------------------------------------------
LRESULT CALLBACK StaticMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );




//-----------------------------------------------------------------------------
// Global access to the app (needed for the global WndProc())
//-----------------------------------------------------------------------------
CMyApplication*    g_pApp  = NULL;
HINSTANCE          g_hInst = NULL;




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Application entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow )
{
    UNREFERENCED_PARAMETER( nCmdShow );
    CMyApplication app;

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
    g_pApp                      = this;

    m_hWnd                      = NULL;
    m_strWindowTitle            = TEXT( "$$root$$" );
    m_dwCreationWidth           = 500;
    m_dwCreationHeight          = 375;
    m_bLoadingApp               = TRUE;

$$IF(KEYBOARD)
    m_pDI                       = NULL;
    m_pKeyboard                 = NULL;
$$ENDIF
$$IF(ACTIONMAPPER)
    m_pInputDeviceManager       = NULL;
$$ENDIF
$$IF(DMUSIC || DSOUND)
$$IF(DMUSIC)
    m_pMusicManager             = NULL;
    m_pBounceSound              = NULL;
$$ELSE
    m_pSoundManager             = NULL;
    m_pBounceSound              = NULL;
$$ENDIF
$$ENDIF

    ZeroMemory( &m_UserInput, sizeof(m_UserInput) );
    m_fWorldRotX                = 0.0f;
    m_fWorldRotY                = 0.0f;
$$IF(DPLAY)

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
$$ENDIF
$$IF(DPLAYVOICE)

    m_pNetVoice                 = NULL;
$$ENDIF
$$IF(REGACCESS)

    // Read settings from registry
    ReadSettings();
$$ELSE
$$IF(DPLAY)
    lstrcpyn( m_strLocalPlayerName, TEXT("$$root$$ Player"), MAX_PATH  );
    lstrcpyn( m_strSessionName, TEXT("$$root$$ Game"), MAX_PATH );
	lstrcpyn( m_strPreferredProvider, TEXT("DirectPlay8 TCP/IP Service Provider"), MAX_PATH );
$$ENDIF
$$ENDIF
}




//-----------------------------------------------------------------------------
// Name: ~CMyApplication()
// Desc: Application destructor 
//-----------------------------------------------------------------------------
CMyApplication::~CMyApplication()
{
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyApplication::OneTimeSceneInit()
{
    // TODO: perform one time initialization

    // Drawing loading status message until app finishes loading
    SendMessage( m_hWnd, WM_PAINT, 0, 0 );

$$IF(DPLAY)
    // Init COM so we can use CoCreateInstance.  And be sure to init 
    // COM as multithreaded when using DirectPlay
    HRESULT hr;
    if( FAILED( hr = CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
        return hr;

$$ENDIF
$$IF(DINPUT)
    // Initialize DirectInput
    InitInput( m_hWnd );

$$ENDIF
$$IF(DMUSIC || DSOUND)
    // Initialize audio
    InitAudio( m_hWnd );

$$ENDIF
$$IF(DPLAY)
    // Initialize DirectPlay
    InitDirectPlay();

    // Create a new DirectPlay session or join to an existing DirectPlay session
    if( FAILED( hr = ConnectViaDirectPlay() ) )
        return hr;

$$ENDIF
    m_bLoadingApp = FALSE;

    return S_OK;
}




$$IF(REGACCESS)
//-----------------------------------------------------------------------------
// Name: ReadSettings()
// Desc: Read the app settings from the registry
//-----------------------------------------------------------------------------
VOID CMyApplication::ReadSettings()
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

$$IF(DPLAY)
        // Read the saved strings needed by DirectPlay
        DXUtil_ReadStringRegKeyCch( hkey, TEXT("Player Name"), 
                                 m_strLocalPlayerName, MAX_PATH, TEXT("$$root$$ Player") );
        DXUtil_ReadStringRegKeyCch( hkey, TEXT("Session Name"), 
                                 m_strSessionName, MAX_PATH, TEXT("$$root$$ Game") );
        DXUtil_ReadStringRegKeyCch( hkey, TEXT("Preferred Provider"), 
                                 m_strPreferredProvider, MAX_PATH, 
                                 TEXT("DirectPlay8 TCP/IP Service Provider") );

$$ENDIF
        RegCloseKey( hkey );
    }
}




//-----------------------------------------------------------------------------
// Name: WriteSettings()
// Desc: Write the app settings to the registry
//-----------------------------------------------------------------------------
VOID CMyApplication::WriteSettings()
{
    HKEY hkey;

    if( ERROR_SUCCESS == RegCreateKeyEx( HKEY_CURRENT_USER, DXAPP_KEY, 
        0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL ) )
    {
        // TODO: change as needed

        // Write the window width/height.  This is just an example,
        // of how to use DXUtil_Write*() functions.
        DXUtil_WriteIntRegKey( hkey, TEXT("Width"), m_dwCreationWidth );
        DXUtil_WriteIntRegKey( hkey, TEXT("Height"), m_dwCreationHeight );

$$IF(DPLAY)
        // Save the strings used by DirectPlay that were entered via the UI
        DXUtil_WriteStringRegKey( hkey, TEXT("Player Name"), m_strLocalPlayerName );
        DXUtil_WriteStringRegKey( hkey, TEXT("Session Name"), m_strSessionName );
        DXUtil_WriteStringRegKey( hkey, TEXT("Preferred Provider"), m_strPreferredProvider );
        
$$ENDIF
        RegCloseKey( hkey );
    }
}





$$ENDIF
$$IF(ACTIONMAPPER)
//-----------------------------------------------------------------------------
// Name: StaticInputAddDeviceCB()
// Desc: Static callback helper to call into CMyApplication class
//-----------------------------------------------------------------------------
HRESULT CALLBACK CMyApplication::StaticInputAddDeviceCB( 
                                         CInputDeviceManager::DeviceInfo* pDeviceInfo, 
                                         const DIDEVICEINSTANCE* pdidi, 
                                         LPVOID pParam )
{
    CMyApplication * pApp = (CMyApplication*) pParam;
    return pApp->InputAddDeviceCB( pDeviceInfo, pdidi );
}




//-----------------------------------------------------------------------------
// Name: InputAddDeviceCB()
// Desc: Called from CInputDeviceManager whenever a device is added. 
//       Set the dead zone, and creates a new InputDeviceState for each device
//-----------------------------------------------------------------------------
HRESULT CMyApplication::InputAddDeviceCB( CInputDeviceManager::DeviceInfo* pDeviceInfo, 
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




$$ENDIF
$$IF(DINPUT)
//-----------------------------------------------------------------------------
// Name: InitInput()
// Desc: Initialize DirectInput objects
//-----------------------------------------------------------------------------
HRESULT CMyApplication::InitInput( HWND hWnd )
{
    HRESULT hr;

$$IF(KEYBOARD)
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
$$ENDIF
$$IF(ACTIONMAPPER)
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
    _tcscpy( m_diafGame.tszActionMap, _T("$$root$$ Game") );

    // Create a new input device manager
    m_pInputDeviceManager = new CInputDeviceManager();

    if( FAILED( hr = m_pInputDeviceManager->Create( hWnd, NULL, m_diafGame, 
                                                    StaticInputAddDeviceCB, this ) ) )
        return DXTRACE_ERR( "m_pInputDeviceManager->Create", hr );
$$ENDIF

    return S_OK;
}




$$ENDIF
$$IF(DMUSIC || DSOUND)
//-----------------------------------------------------------------------------
// Name: InitAudio()
// Desc: Initialize DirectX audio objects
//-----------------------------------------------------------------------------
HRESULT CMyApplication::InitAudio( HWND hWnd )
{
    HRESULT hr;

$$IF(DMUSIC)
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

$$ELSE
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

$$ENDIF
    return S_OK;
}




$$ENDIF
$$IF(DPLAY)
//-----------------------------------------------------------------------------
// Name: InitDirectPlay()
// Desc: Initialize DirectPlay
//-----------------------------------------------------------------------------
HRESULT CMyApplication::InitDirectPlay()
{
    // Initialize critical sections
    InitializeCriticalSection( &g_csPlayerContext );
    InitializeCriticalSection( &g_csWorldStateContext );

    // Create helper class
    m_pNetConnectWizard = new CNetConnectWizard( g_hInst, m_hWnd, 
                                                 m_strWindowTitle, &g_guidApp );
$$IF(DPLAYVOICE)
    m_pNetVoice         = new CNetVoice( StaticDirectPlayVoiceClientMessageHandler, StaticDirectPlayVoiceServerMessageHandler );
$$ENDIF

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
HRESULT CMyApplication::ConnectViaDirectPlay()
{
    HRESULT hr;
    BOOL bConnectSuccess = FALSE;

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
            MessageBox( m_hWnd, TEXT("Failed to connect using lobby settings. ")
                        TEXT("The sample will now quit."),
                        TEXT("$$root$$"), MB_OK | MB_ICONERROR );

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
            MessageBox( m_hWnd, TEXT("Multiplayer connect failed. ")
                        TEXT("The sample will now quit."),
                        TEXT("$$root$$"), MB_OK | MB_ICONERROR );
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
$$IF(REGACCESS)

            // Write information to the registry
            WriteSettings();
$$ENDIF
        }
    }

$$IF(DPLAYVOICE)
    if( bConnectSuccess )
    {
        // Initialize DirectPlay voice
        if( FAILED( hr = InitDirectPlayVoice() ) )
        {
            bConnectSuccess = FALSE;

            if( hr == DVERR_USERBACK )
            {
                MessageBox( m_hWnd, TEXT("The user backed out of the wizard.  ")
                            TEXT("This simple sample does not handle this case, so ")
                            TEXT("the sample will quit."), TEXT("DirectPlay Sample"), MB_OK );
            }
            else if( hr == DVERR_USERCANCEL )
            {
                MessageBox( m_hWnd, TEXT("The user canceled the wizard. ")
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
            MessageBox( m_hWnd, TEXT("You are running in half duplex mode. ")
                        TEXT("In half duplex mode no recording takes place."), 
                        TEXT("blank"), MB_OK );
        }
    }

$$ENDIF
    if( FALSE == bConnectSuccess )
    {
        // Quit the app
        PostQuitMessage(0);
    }

    return S_OK;
}




$$ENDIF
$$IF(DPLAYVOICE)
//-----------------------------------------------------------------------------
// Name: InitDirectPlayVoice()
// Desc: Init DirectPlay Voice
//-----------------------------------------------------------------------------
HRESULT CMyApplication::InitDirectPlayVoice()
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
    if( FAILED( hr = m_pNetVoice->Init( m_hWnd, m_pNetConnectWizard->IsHostPlayer(), TRUE,
                                        m_pDP, DVSESSIONTYPE_PEER, 
                                        &m_guidDVSessionCT, &m_dvClientConfig ) ) )
        return hr;

    return S_OK;
}




$$ENDIF
//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyApplication::FrameMove()
{
    // TODO: update world

    // Update user input state
    UpdateInput( &m_UserInput );

$$IF(DPLAY)
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

$$ENDIF
$$IF(ACTIONMAPPER)
    // Respond to input
    if( m_UserInput.bDoConfigureInput )
    {
        // One-shot per keypress
        m_UserInput.bDoConfigureInput = FALSE;

        Pause( TRUE );

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
        m_pInputDeviceManager->ConfigureDevices( m_hWnd, NULL, NULL, DICD_EDIT, NULL );

        Pause( FALSE );
    }

$$ENDIF
$$IF(DPLAYVOICE)
    if( m_UserInput.bDoConfigureVoice )
    {
        // One-shot per keypress
        m_UserInput.bDoConfigureVoice = FALSE;

        Pause(TRUE);

        // Allow user to configure the voice settings
        UserConfigVoice();

        Pause(FALSE);
    }

$$ENDIF
$$IF(DPLAY)
    // Combining the input data from all players 
    // TODO: Combining the input data from all players is an unrealistic yet simple 
    //       usage of network data. Use it as a starting point to serve your needs
    CombineInputFromAllPlayers( &m_CombinedNetworkInput );

$$ENDIF
$$IF(DPLAYVOICE)
    // Update talking varibles 
    // TODO: The talking variables just update the text, but something more complex
    //       like animation could be done based on them
    UpdateTalkingVariables();

$$ENDIF
    // Update the world state according to user input

$$IF(DPLAY)
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
$$IF(ACTIONMAPPER)
        if( m_CombinedNetworkInput.fAxisRotateLR )
            m_fWorldRotY += m_fElapsedTime * m_CombinedNetworkInput.fAxisRotateLR;

        if( m_CombinedNetworkInput.fAxisRotateUD )
            m_fWorldRotX += m_fElapsedTime * m_CombinedNetworkInput.fAxisRotateUD;
$$ELSE // start !ACTIONMAPPER
        if( m_CombinedNetworkInput.bRotateLeft && !m_CombinedNetworkInput.bRotateRight )
            m_fWorldRotY += m_fElapsedTime;
        else if( m_CombinedNetworkInput.bRotateRight && !m_CombinedNetworkInput.bRotateLeft )
            m_fWorldRotY -= m_fElapsedTime;

        if( m_CombinedNetworkInput.bRotateUp && !m_CombinedNetworkInput.bRotateDown )
            m_fWorldRotX += m_fElapsedTime;
        else if( m_CombinedNetworkInput.bRotateDown && !m_CombinedNetworkInput.bRotateUp )
            m_fWorldRotX -= m_fElapsedTime;
$$ENDIF // end ACTIONMAPPER
    }

    // Leave the critical section
    WORLD_UNLOCK();

$$ENDIF // end DPLAY
$$IF(!DPLAY)
$$IF(ACTIONMAPPER)
    if( m_UserInput.fAxisRotateLR )
        m_fWorldRotY += m_fElapsedTime * m_UserInput.fAxisRotateLR;

    if( m_UserInput.fAxisRotateUD )
        m_fWorldRotX += m_fElapsedTime * m_UserInput.fAxisRotateUD;

$$ELSE // start !ACTIONMAPPER
    if( m_UserInput.bRotateLeft && !m_UserInput.bRotateRight )
        m_fWorldRotY += m_fElapsedTime;
    else if( m_UserInput.bRotateRight && !m_UserInput.bRotateLeft )
        m_fWorldRotY -= m_fElapsedTime;

    if( m_UserInput.bRotateUp && !m_UserInput.bRotateDown )
        m_fWorldRotX += m_fElapsedTime;
    else if( m_UserInput.bRotateDown && !m_UserInput.bRotateUp )
        m_fWorldRotX -= m_fElapsedTime;

$$ENDIF // end ACTIONMAPPER
$$ENDIF // end !DPLAY
$$IF(DMUSIC || DSOUND)
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

$$ENDIF // DMUSIC || DSOUND
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: UpdateInput()
// Desc: Update the user input.  Called once per frame 
//-----------------------------------------------------------------------------
void CMyApplication::UpdateInput( UserInput* pUserInput )
{
$$IF(ACTIONMAPPER)
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
$$IF(DMUSIC || DSOUND)
                case INPUT_PLAY_SOUND:   pInputDeviceState->bButtonPlaySoundButtonDown = bButtonState; break;
$$ENDIF // DMUSIC || DSOUND

                // Handle one-shot buttons
                case INPUT_CONFIG_INPUT:   if( bButtonState ) pUserInput->bDoConfigureInput = TRUE; break;
$$IF(DPLAYVOICE)
                case INPUT_CONFIG_VOICE:   if( bButtonState ) pUserInput->bDoConfigureVoice   = TRUE; break;
$$ENDIF
            }
        }
    }

    // TODO: change process code as needed

    // Process user input and store result into pUserInput struct
    pUserInput->fAxisRotateLR = 0.0f;
    pUserInput->fAxisRotateUD = 0.0f;
$$IF(DMUSIC || DSOUND)
    pUserInput->bPlaySoundButtonDown = FALSE;
$$ENDIF

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

$$IF(DMUSIC || DSOUND)
        if( pInputDeviceState->bButtonPlaySoundButtonDown )
            pUserInput->bPlaySoundButtonDown = TRUE;
$$ENDIF // DMUSIC || DSOUND
    } 
$$ENDIF // ACTIONMAPPER
$$IF(KEYBOARD)
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
$$IF(DMUSIC || DSOUND)
    pUserInput->bPlaySoundButtonDown   = ( (pUserInput->diks[DIK_F5] & 0x80)     == 0x80 );
$$ENDIF // DMUSIC || DSOUND
$$ENDIF // KEYBOARD
$$IF(!DINPUT)
    pUserInput->bRotateUp    = ( m_bHasFocus && (GetAsyncKeyState( VK_UP )    & 0x8000) == 0x8000 );
    pUserInput->bRotateDown  = ( m_bHasFocus && (GetAsyncKeyState( VK_DOWN )  & 0x8000) == 0x8000 );
    pUserInput->bRotateLeft  = ( m_bHasFocus && (GetAsyncKeyState( VK_LEFT )  & 0x8000) == 0x8000 );
    pUserInput->bRotateRight = ( m_bHasFocus && (GetAsyncKeyState( VK_RIGHT ) & 0x8000) == 0x8000 );
$$IF(DMUSIC || DSOUND)
    pUserInput->bPlaySoundButtonDown = ( m_bHasFocus && (GetAsyncKeyState( VK_F5 ) & 0x8000) == 0x8000 );
$$ENDIF // DMUSIC || DSOUND
$$ENDIF // !DINPUT
}




$$IF(DPLAY)
//-----------------------------------------------------------------------------
// Name: SendLocalInputIfChanged()
// Desc: Send local input to all network players if it changed
//-----------------------------------------------------------------------------
HRESULT CMyApplication::SendLocalInputIfChanged()
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
$$IF(ACTIONMAPPER)
    if( m_UserInput.fAxisRotateLR != m_pLocalPlayerInfo->fAxisRotateLR ||
        m_UserInput.fAxisRotateUD != m_pLocalPlayerInfo->fAxisRotateUD )
$$ELSE
    if( m_UserInput.bRotateUp    != m_pLocalPlayerInfo->bRotateUp   ||
        m_UserInput.bRotateDown  != m_pLocalPlayerInfo->bRotateDown ||
        m_UserInput.bRotateLeft  != m_pLocalPlayerInfo->bRotateLeft ||
        m_UserInput.bRotateRight != m_pLocalPlayerInfo->bRotateRight )
$$ENDIF
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
$$IF(ACTIONMAPPER)
        msgInputState.fAxisRotateLR = m_UserInput.fAxisRotateLR;
        msgInputState.fAxisRotateUD = m_UserInput.fAxisRotateUD;
$$ELSE
        msgInputState.bRotateUp    = m_UserInput.bRotateUp;
        msgInputState.bRotateDown  = m_UserInput.bRotateDown;
        msgInputState.bRotateLeft  = m_UserInput.bRotateLeft;
        msgInputState.bRotateRight = m_UserInput.bRotateRight;
$$ENDIF

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
HRESULT CMyApplication::SendWorldStateToAll()
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
HRESULT CMyApplication::SendPauseMessageToAll( BOOL bPause )
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




$$IF(ACTIONMAPPER)
//-----------------------------------------------------------------------------
// Name: CombineInputFromAllPlayers()
// Desc: Combine axis input from all network players
//-----------------------------------------------------------------------------
HRESULT CMyApplication::CombineInputFromAllPlayers( UserInput* pCombinedUserInput )
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




$$ELSE // start !ACTIONMAPPER
//-----------------------------------------------------------------------------
// Name: CombineInputFromAllPlayers()
// Desc: Combine axis input from all network players
//-----------------------------------------------------------------------------
HRESULT CMyApplication::CombineInputFromAllPlayers( UserInput* pCombinedUserInput )
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




$$ENDIF // end ACTIONMAPPER
$$ENDIF // end DPLAY
$$IF(DPLAYVOICE)
//-----------------------------------------------------------------------------
// Name: UpdateTalkingVariables()
// Desc: Update m_bNetworkPlayersTalking and m_bLocalPlayerTalking
//-----------------------------------------------------------------------------
VOID CMyApplication::UpdateTalkingVariables()
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




$$ENDIF // DPLAYVOICE
//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for rendering the 
//       world.
//-----------------------------------------------------------------------------
HRESULT CMyApplication::Render()
{
    // TODO: render world

    static COLORREF clrNormal  = RGB(255,255,0);
$$IF(DPLAY)
    static COLORREF clrWarning = RGB(0,255,255);
$$ENDIF
    TCHAR       szMsg[MAX_PATH] = TEXT("");
    HDC         hDC;
    RECT        rc;

    GetClientRect( m_hWnd, &rc ); 
    int nNextLine = rc.bottom;
 
    hDC = GetDC( m_hWnd );

    // Set background and text colors
    HBRUSH hBrushBackground = CreateSolidBrush( RGB(0,0,255) );
    FillRect( hDC, &rc, hBrushBackground );
    DeleteObject( hBrushBackground );
    SetBkColor( hDC, RGB(0,0,255) );
    SetTextColor( hDC, clrNormal );

$$IF(DPLAY)
$$IF(ACTIONMAPPER)
$$// ******************************************************
    sprintf( szMsg, TEXT("Network Combined L/R Axis: %0.2f U/D Axis: %0.2f "), 
              m_CombinedNetworkInput.fAxisRotateLR, m_CombinedNetworkInput.fAxisRotateUD );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ELSE // start !ACTIONMAPPER
$$// ******************************************************
    wsprintf( szMsg, TEXT("Network Combined Keys: U=%d D=%d L=%d R=%d"), 
              m_CombinedNetworkInput.bRotateUp, m_CombinedNetworkInput.bRotateDown, m_CombinedNetworkInput.bRotateLeft, m_CombinedNetworkInput.bRotateRight );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // ACTIONMAPPER
$$ENDIF // DPLAY
$$IF(ACTIONMAPPER)
$$// ******************************************************
$$IF(DPLAY)
    sprintf( szMsg, TEXT("Local Left/Right Axis: %0.2f Up/Down Axis: %0.2f "), 
              m_UserInput.fAxisRotateLR, m_UserInput.fAxisRotateUD );
$$ELSE
    sprintf( szMsg, TEXT("Left/Right Axis: %0.2f Up/Down Axis: %0.2f "), 
              m_UserInput.fAxisRotateLR, m_UserInput.fAxisRotateUD );
$$ENDIF
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ELSE // start !ACTIONMAPPER
$$IF(DPLAY)
$$// ******************************************************
    wsprintf( szMsg, TEXT("Local Arrow keys: U=%d D=%d L=%d R=%d"), 
              m_UserInput.bRotateUp, m_UserInput.bRotateDown, m_UserInput.bRotateLeft, m_UserInput.bRotateRight );
$$ELSE // DPLAY
    wsprintf( szMsg, TEXT("Arrow keys: Up=%d Down=%d Left=%d Right=%d"), 
              m_UserInput.bRotateUp, m_UserInput.bRotateDown, m_UserInput.bRotateLeft, m_UserInput.bRotateRight );
$$ENDIF // DPLAY
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // ACTIONMAPPER
$$IF(DPLAY)
$$// ******************************************************
    sprintf( szMsg, TEXT("%d player(s) in session %s"), 
                        m_lNumberOfActivePlayers, 
                        m_pNetConnectWizard->IsHostPlayer() ? TEXT("(Hosting)") : TEXT("") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // DPLAY
$$IF(DPLAYVOICE)
$$// ******************************************************
    sprintf( szMsg, TEXT("Local Player: %s  Network Players: %s"), 
                        m_bLocalPlayerTalking ? TEXT("Talking") : TEXT("Silent"), 
                        m_bNetworkPlayersTalking ? TEXT("Talking") : TEXT("Silent") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // DPLAYVOICE
$$IF(!SHOW_TRIANGLE)
$$IF(!SHOW_TEAPOT)
$$// ******************************************************
    sprintf( szMsg, TEXT("World State: %0.3f, %0.3f"), 
                    m_fWorldRotX, m_fWorldRotY );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // !SHOW_TEAPOT
$$ENDIF // !SHOW_TRIANGLE
$$IF(SHOW_TRIANGLE || SHOW_TEAPOT)
$$IF(ACTIONMAPPER)
$$// ******************************************************
    lstrcpy( szMsg, TEXT("Use arrow keys or joystick to rotate object") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ELSE // start !ACTIONMAPPER
$$// ******************************************************
    lstrcpy( szMsg, TEXT("Use arrow keys to rotate object") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // ACTIONMAPPER
$$ELSE // start !(SHOW_TRIANGLE || SHOW_TEAPOT)
$$IF(ACTIONMAPPER)
$$// ******************************************************
    lstrcpy( szMsg, TEXT("Use arrow keys or joystick to update input") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ELSE // start !ACTIONMAPPER
    lstrcpy( szMsg, TEXT("Use arrow keys to update input") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // ACTIONMAPPER
$$ENDIF // SHOW_TRIANGLE || SHOW_TEAPOT
$$IF(DMUSIC || DSOUND)
$$// ******************************************************
    lstrcpy( szMsg, TEXT("Hold 'F5' down to play and repeat a sound") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // DMUSIC || DSOUND
$$IF(DPLAYVOICE)
$$// ******************************************************
    lstrcpy( szMsg, TEXT("Press 'F4' to configure voice") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // DPLAYVOICE
$$IF(ACTIONMAPPER)
$$// ******************************************************
    lstrcpy( szMsg, TEXT("Press 'F3' to configure input") );
$$// ------------------------------------------------------
    nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------

$$ENDIF // ACTIONMAPPER
$$IF(DPLAY)
    if( m_bHostPausing )
    {
$$// ******************************************************
        lstrcpy( szMsg, TEXT("Paused waiting for host...") );
$$// ------------------------------------------------------
        SetTextColor( hDC, clrWarning );
        nNextLine -= 20; TextOut( hDC, 2, nNextLine, szMsg, lstrlen(szMsg) );
$$// ------------------------------------------------------   
    }

$$ENDIF // end DPLAY
    ReleaseDC( m_hWnd, hDC );

    return S_OK;
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
// Name: MainWndproc()
// Desc: Callback for all Windows messages
//-----------------------------------------------------------------------------
LRESULT CMyApplication::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        // TODO: Repond to Windows messages as needed

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
                case IDM_EXIT:
                    PostQuitMessage( 0 );
                    break;

$$IF(ACTIONMAPPER)
                case IDM_CONFIGINPUT:
                    m_UserInput.bDoConfigureInput = TRUE;
                    break;
$$ENDIF 
$$IF(DPLAYVOICE)

                case IDM_CONFIGVOICE:
                    m_UserInput.bDoConfigureVoice = TRUE;
                    break;
$$ENDIF
            }
            break;
        }

        case WM_ACTIVATEAPP:
            m_bHasFocus = wParam;
            break;

        case WM_ENTERSIZEMOVE:
        case WM_ENTERMENULOOP:
            // Halt frame movement while the app is sizing or moving
            // or when menus are displayed
            Pause( TRUE );
            break;

        case WM_EXITSIZEMOVE:
        case WM_EXITMENULOOP:
            Pause( FALSE );
            break;

        case WM_PAINT:
        {
            if( m_bLoadingApp )
            {
                // Draw on the window tell the user that the app is loading
                // TODO: change as needed
                HDC hDC = GetDC( hWnd );
                TCHAR strMsg[MAX_PATH];
                wsprintf( strMsg, TEXT("Loading... Please wait") );
                RECT rct;
                GetClientRect( hWnd, &rct );
                DrawText( hDC, strMsg, -1, &rct, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
                ReleaseDC( hWnd, hDC );
            }
            break;
        }

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: Pause()
// Desc: Called in to toggle the pause state of the app.
//-----------------------------------------------------------------------------
VOID CMyApplication::Pause( BOOL bPause )
{
    static DWORD dwAppPausedCount = 0L;

$$IF(DPLAY)
    // Tell the other apps to pause or unpause if this is the host
    if( m_pNetConnectWizard && m_pNetConnectWizard->IsHostPlayer() )
        SendPauseMessageToAll( bPause );

$$ENDIF
$$IF(ACTIONMAPPER)
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

$$ENDIF
    dwAppPausedCount += ( bPause ? +1 : -1 );

    // Handle the first pause request (of many, nestable pause requests)
    if( bPause && ( 1 == dwAppPausedCount ) )
    {
        // Stop the scene from animating
        DXUtil_Timer( TIMER_STOP );
    }

    if( 0 == dwAppPausedCount )
    {
        // Restart the timers
        DXUtil_Timer( TIMER_START );
    }
}




$$IF(DPLAYVOICE)
//-----------------------------------------------------------------------------
// Name: UserConfigVoice()
// Desc: Allow user to configure the voice settings
//-----------------------------------------------------------------------------
HRESULT CMyApplication::UserConfigVoice()
{
    HRESULT hr;
   
    // Configure the voice settings, store the settings in 
    // m_guidDVSessionCT & m_dvClientConfig
    if( m_pNetVoice )
    {
        hr = m_pNetVoice->DoVoiceSetupDialog( g_hInst, m_hWnd, &m_guidDVSessionCT, &m_dvClientConfig );

        // If the settings dialog was not canceled, then change the settings
        if( hr != DVERR_USERCANCEL )
            m_pNetVoice->ChangeVoiceClientSettings( &m_dvClientConfig );
    }

    return S_OK;
}




$$ENDIF
//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CMyApplication::FinalCleanup()
{
    // TODO: Perform any final cleanup needed
$$IF(DINPUT)
    // Cleanup DirectInput
    CleanupDirectInput();

$$ENDIF
$$IF(DMUSIC || DSOUND)
    // Cleanup DirectX audio objects
    SAFE_DELETE( m_pBounceSound );
$$IF(DMUSIC)
    SAFE_DELETE( m_pMusicManager );
$$ELSE // start !DMUSIC
    SAFE_DELETE( m_pSoundManager );
$$ENDIF // end DMUSIC

$$ENDIF // end (DMUSIC || DSOUND)
$$IF(DPLAY)
    // Cleanup DirectPlay
    CleanupDirectPlay();

    // Cleanup COM
    CoUninitialize();

$$ENDIF
$$IF(REGACCESS)
    // Write the settings to the registry
    WriteSettings();

$$ENDIF
    return S_OK;
}




$$IF(DPLAY)
//-----------------------------------------------------------------------------
// Name: CleanupDirectPlay()
// Desc: Cleanup DirectPlay 
//-----------------------------------------------------------------------------
VOID CMyApplication::CleanupDirectPlay()
{
$$IF(DPLAYVOICE)
    // Disconnect from the DirectPlayVoice session, 
    // and destroy it if we are the host player.
    SAFE_DELETE( m_pNetVoice ); 

$$ENDIF
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
        MessageBox( m_hWnd, TEXT("The DirectPlay session was lost. ")
                    TEXT("The sample will now quit."),
                    TEXT("DirectPlay Sample"), MB_OK | MB_ICONERROR );
    }
}



$$ENDIF
$$IF(DINPUT)
//-----------------------------------------------------------------------------
// Name: CleanupDirectInput()
// Desc: Cleanup DirectInput 
//-----------------------------------------------------------------------------
VOID CMyApplication::CleanupDirectInput()
{
$$IF(KEYBOARD)
    // Cleanup DirectX input objects
    SAFE_RELEASE( m_pKeyboard );
    SAFE_RELEASE( m_pDI );
$$ENDIF
$$IF(ACTIONMAPPER)
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
$$ENDIF
}




$$ENDIF
$$IF(DPLAY)
//-----------------------------------------------------------------------------
// Name: StaticDirectPlayMessageHandler
// Desc: Static callback helper to call into CMyApplication class
//-----------------------------------------------------------------------------
HRESULT WINAPI CMyApplication::StaticDirectPlayMessageHandler( PVOID pvUserContext, 
                                                                  DWORD dwMessageId, 
                                                                  PVOID pMsgBuffer )
{
    if( g_pApp )
        return g_pApp->DirectPlayMessageHandler( pvUserContext, dwMessageId, pMsgBuffer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayMessageHandler
// Desc: Handler for DirectPlay messages.  This function is called by
//       the DirectPlay message handler pool of threads, so be careful of thread
//       synchronization problems with shared memory
//-----------------------------------------------------------------------------
HRESULT CMyApplication::DirectPlayMessageHandler( PVOID pvUserContext, 
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

$$IF(ACTIONMAPPER)
                    pPlayerInfo->fAxisRotateLR = pInputStateMsg->fAxisRotateLR;
                    pPlayerInfo->fAxisRotateUD = pInputStateMsg->fAxisRotateUD;
$$ELSE
                    pPlayerInfo->bRotateUp    = pInputStateMsg->bRotateUp;
                    pPlayerInfo->bRotateDown  = pInputStateMsg->bRotateDown;
                    pPlayerInfo->bRotateLeft  = pInputStateMsg->bRotateLeft;
                    pPlayerInfo->bRotateRight = pInputStateMsg->bRotateRight;
$$ENDIF

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
            if( m_hWnd )
                PostMessage( m_hWnd, WM_QUIT, 0, 0 );
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
// Desc: Static callback helper to call into CMyApplication class
//-----------------------------------------------------------------------------
HRESULT WINAPI CMyApplication::StaticDirectPlayLobbyMessageHandler( PVOID pvUserContext, 
                                                                  DWORD dwMessageId, 
                                                                  PVOID pMsgBuffer )
{
    if( g_pApp )
        return g_pApp->DirectPlayLobbyMessageHandler( pvUserContext, dwMessageId, pMsgBuffer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayLobbyMessageHandler
// Desc: Handler for DirectPlay lobby messages.  This function is called by
//       the DirectPlay lobby message handler pool of threads, so be careful of 
//       thread synchronization problems with shared memory
//-----------------------------------------------------------------------------
HRESULT CMyApplication::DirectPlayLobbyMessageHandler( PVOID pvUserContext, 
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




$$ENDIF
$$IF(DPLAYVOICE)
//-----------------------------------------------------------------------------
// Name: StaticDirectPlayVoiceServerMessageHandler
// Desc: Static callback helper to call into CMyApplication class
//-----------------------------------------------------------------------------
HRESULT WINAPI CMyApplication::StaticDirectPlayVoiceServerMessageHandler( PVOID pvUserContext, 
                                                                  DWORD dwMessageId, 
                                                                  PVOID pMsgBuffer )
{
    if( g_pApp )
        return g_pApp->DirectPlayVoiceServerMessageHandler( pvUserContext, dwMessageId, pMsgBuffer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayVoiceServerMessageHandler()
// Desc: The callback for DirectPlayVoice server messages.  
//-----------------------------------------------------------------------------
HRESULT CMyApplication::DirectPlayVoiceServerMessageHandler( LPVOID lpvUserContext, DWORD dwMessageType,
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
// Desc: Static callback helper to call into CMyApplication class
//-----------------------------------------------------------------------------
HRESULT WINAPI CMyApplication::StaticDirectPlayVoiceClientMessageHandler( PVOID pvUserContext, 
                                                                  DWORD dwMessageId, 
                                                                  PVOID pMsgBuffer )
{
    if( g_pApp )
        return g_pApp->DirectPlayVoiceClientMessageHandler( pvUserContext, dwMessageId, pMsgBuffer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayVoiceClientMessageHandler()
// Desc: The callback for DirectPlayVoice client messages.  
//       This handles client messages and updates the UI the whenever a client 
//       starts or stops talking.  
//-----------------------------------------------------------------------------
HRESULT CMyApplication::DirectPlayVoiceClientMessageHandler( LPVOID lpvUserContext, DWORD dwMessageType,
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




$$ENDIF
//-----------------------------------------------------------------------------
// Name: Create()
// Desc: Creates the window
//-----------------------------------------------------------------------------
HRESULT CMyApplication::Create( HINSTANCE hInstance )
{
    // Register the window class
    WNDCLASS wndClass = { CS_DBLCLKS, StaticMsgProc, 0, 0, hInstance, NULL,
                          LoadCursor( NULL, IDC_ARROW ), 
                          (HBRUSH)GetSysColorBrush( COLOR_WINDOW ),
                          NULL, _T("$$root$$ Class") };
    RegisterClass( &wndClass );

    // Create our main window
    HMENU hMenu = LoadMenu( NULL, MAKEINTRESOURCE(IDR_MENU) );
    m_hWnd = CreateWindowEx( 0, _T("$$root$$ Class"), m_strWindowTitle,
                                WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT, 
                                m_dwCreationWidth, m_dwCreationHeight, 
                                NULL, hMenu, hInstance, NULL );
    if( NULL == m_hWnd )
        return E_FAIL;
    UpdateWindow( m_hWnd );

    // Initialize the application timer
    DXUtil_Timer( TIMER_START );

    // Initialize the app's custom scene stuff
    OneTimeSceneInit();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Run()
// Desc: Handles the message loop and calls FrameMove() and Render() when
//       idle.
//-----------------------------------------------------------------------------
INT CMyApplication::Run()
{
    MSG msg = {0};
    HACCEL hAccel = LoadAccelerators( g_hInst, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

    // Message loop to run the app
    for(;;)
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if( FALSE == GetMessage( &msg, NULL, 0, 0 ) )
                break;

            if( 0 == TranslateAccelerator( m_hWnd, hAccel, &msg ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
        }
        else
        {
            // Update the time variables
            m_fTime        = DXUtil_Timer( TIMER_GETAPPTIME );
            m_fElapsedTime = DXUtil_Timer( TIMER_GETELAPSEDTIME );

            // This app uses idle time processing for the game loop
            if( FAILED( FrameMove() ) )
                SendMessage( m_hWnd, WM_DESTROY, 0, 0 );
            if( FAILED( Render() ) ) 
                SendMessage( m_hWnd, WM_DESTROY, 0, 0 );

            Sleep( 20 );
        }
    }

    FinalCleanup();

    return (INT)msg.wParam;
}




