//-----------------------------------------------------------------------------
// File: [!output PROJECT_NAME].h
//
// Desc: Header file [!output PROJECT_NAME] sample app
//-----------------------------------------------------------------------------
#pragma once
[!if DPLAY]




//-----------------------------------------------------------------------------
// Player context locking defines
//-----------------------------------------------------------------------------
CRITICAL_SECTION g_csPlayerContext;
#define PLAYER_LOCK()                   EnterCriticalSection( &g_csPlayerContext ); 
#define PLAYER_ADDREF( pPlayerInfo )    if( pPlayerInfo ) pPlayerInfo->lRefCount++;
#define PLAYER_RELEASE( pPlayerInfo )   if( pPlayerInfo ) { pPlayerInfo->lRefCount--; if( pPlayerInfo->lRefCount <= 0 ) SAFE_DELETE( pPlayerInfo ); } pPlayerInfo = NULL;
#define PLAYER_UNLOCK()                 LeaveCriticalSection( &g_csPlayerContext );

CRITICAL_SECTION g_csWorldStateContext;
#define WORLD_LOCK()                   EnterCriticalSection( &g_csWorldStateContext ); 
#define WORLD_UNLOCK()                 LeaveCriticalSection( &g_csWorldStateContext );
[!endif]




//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
// TODO: change "DirectX AppWizard Apps" to your name or the company name
#define DXAPP_KEY        TEXT("Software\\DirectX AppWizard Apps\\[!output PROJECT_NAME]")



[!if DPLAY]
// Associate a structure with every network player
struct APP_PLAYER_INFO
{
    // TODO: change as needed
    LONG  lRefCount;                        // Ref count so we can cleanup when all threads 
                                            // are done w/ this object
    DPNID dpnidPlayer;                      // DPNID of player
    TCHAR strPlayerName[MAX_PATH];          // Player name

[!if ACTIONMAPPER]
    FLOAT fAxisRotateUD;                    // State of axis for this player
    FLOAT fAxisRotateLR;                    // State of axis for this player
[!else]
    BOOL  bRotateUp;                       // State of up button or this player
    BOOL  bRotateDown;                     // State of down button or this player
    BOOL  bRotateLeft;                     // State of left button or this player
    BOOL  bRotateRight;                    // State of right button or this player
[!endif]
[!if DPLAYVOICE]

    BOOL  bHalfDuplex;                      // TRUE if player is in half-duplex mode
    BOOL  bTalking;                         // TRUE if player is talking
[!endif]

    APP_PLAYER_INFO* pNext;
    APP_PLAYER_INFO* pPrev;
};


[!endif]
[!if ACTIONMAPPER]
// DirectInput action mapper reports events only when buttons/axis change
// so we need to remember the present state of relevant axis/buttons for 
// each DirectInput device.  The CInputDeviceManager will store a 
// pointer for each device that points to this struct
struct InputDeviceState
{
    // TODO: change as needed
    FLOAT fAxisRotateLR;
    BOOL  bButtonRotateLeft;
    BOOL  bButtonRotateRight;

    FLOAT fAxisRotateUD;
    BOOL  bButtonRotateUp;
    BOOL  bButtonRotateDown;
[!if DMUSIC || DSOUND]

    BOOL  bButtonPlaySoundButtonDown;
[!endif]
};


[!endif]
// Struct to store the current input state
struct UserInput
{
[!if KEYBOARD]
    BYTE diks[256];   // DirectInput keyboard state buffer 

[!endif]
    // TODO: change as needed
[!if ACTIONMAPPER]
    FLOAT fAxisRotateUD;
    FLOAT fAxisRotateLR;
[!else]
    BOOL bRotateUp;
    BOOL bRotateDown;
    BOOL bRotateLeft;
    BOOL bRotateRight;
[!endif]
[!if DMUSIC || DSOUND]
    BOOL bPlaySoundButtonDown;
[!endif]
[!if ACTIONMAPPER]
    BOOL bDoConfigureInput;
[!endif]
[!if DPLAYVOICE]
    BOOL bDoConfigureVoice;
[!endif]
};


[!if DPLAY]
//-----------------------------------------------------------------------------
// App specific DirectPlay messages and structures 
//-----------------------------------------------------------------------------

// TODO: change or add app specific DirectPlay messages and structures as needed
#define GAME_MSGID_WORLDSTATE    1
#define GAME_MSGID_INPUTSTATE    2
#define GAME_MSGID_HOSTPAUSE     3

// Change compiler pack alignment to be BYTE aligned, and pop the current value
#pragma pack( push, 1 )

struct GAMEMSG_GENERIC
{
    // One of GAME_MSGID_* IDs so the app knows which GAMEMSG_* struct
    // to cast the msg pointer into.
    WORD nType; 
};

struct GAMEMSG_WORLDSTATE : public GAMEMSG_GENERIC
{
    FLOAT fWorldRotX;
    FLOAT fWorldRotY;
};

struct GAMEMSG_INPUTSTATE : public GAMEMSG_GENERIC
{
[!if ACTIONMAPPER]
    FLOAT fAxisRotateUD;
    FLOAT fAxisRotateLR;
[!else]
    BOOL  bRotateUp;   
    BOOL  bRotateDown; 
    BOOL  bRotateLeft; 
    BOOL  bRotateRight;
[!endif]
};

struct GAMEMSG_HOSTPAUSE : public GAMEMSG_GENERIC
{
    BOOL bHostPause;
};

// Pop the old pack alignment
#pragma pack( pop )


[!endif]



//-----------------------------------------------------------------------------
// Name: class CMyApplication 
// Desc: Application class.
//-----------------------------------------------------------------------------
class CMyApplication 
{
    BOOL                    m_bLoadingApp;          // TRUE, if the app is loading
    BOOL              	    m_bHasFocus;	    // TRUE, if the app has focus
    TCHAR*                  m_strWindowTitle;       // Title for the app's window
    HWND                    m_hWnd;                 // The main app window
    FLOAT                   m_fTime;                // Current time in seconds
    FLOAT                   m_fElapsedTime;         // Time elapsed since last frame

    DWORD                   m_dwCreationWidth;      // Width used to create window
    DWORD                   m_dwCreationHeight;     // Height used to create window

[!if KEYBOARD]
    LPDIRECTINPUT8          m_pDI;                  // DirectInput object
    LPDIRECTINPUTDEVICE8    m_pKeyboard;            // DirectInput keyboard device
[!endif]
[!if ACTIONMAPPER]
    CInputDeviceManager*    m_pInputDeviceManager;  // DirectInput device manager
    DIACTIONFORMAT          m_diafGame;             // Action format for game play
[!endif]
    UserInput               m_UserInput;            // Struct for storing user input 

[!if DMUSIC || DSOUND]
    FLOAT                   m_fSoundPlayRepeatCountdown; // Sound repeat timer
[!if DMUSIC]
    CMusicManager*          m_pMusicManager;        // DirectMusic manager class
    CMusicSegment*          m_pBounceSound;         // Bounce sound
[!else]
    CSoundManager*          m_pSoundManager;        // DirectSound manager class
    CSound*                 m_pBounceSound;         // Bounce sound
[!endif]

[!endif]
[!if DPLAY]
    IDirectPlay8Peer*       m_pDP;                  // DirectPlay peer object
    CNetConnectWizard*      m_pNetConnectWizard;    // Connection wizard
    IDirectPlay8LobbiedApplication* m_pLobbiedApp;  // DirectPlay lobbied app 
    BOOL                    m_bWasLobbyLaunched;    // TRUE if lobby launched
    DPNID                   m_dpnidLocalPlayer;     // DPNID of local player
    LONG                    m_lNumberOfActivePlayers;        // Number of players currently in game
    TCHAR                   m_strLocalPlayerName[MAX_PATH];  // Local player name
    TCHAR                   m_strSessionName[MAX_PATH];      // Session name
    TCHAR                   m_strPreferredProvider[MAX_PATH];// Provider string
    APP_PLAYER_INFO         m_PlayInfoList;         // List of players
    APP_PLAYER_INFO*        m_pLocalPlayerInfo;     // APP_PLAYER_INFO struct for local player
    HRESULT                 m_hrNet;                // HRESULT of DirectPlay events
    FLOAT                   m_fWorldSyncTimer;      // Timer for syncing world state between players
    BOOL                    m_bHostPausing;         // Has the host paused the app?
    UserInput               m_CombinedNetworkInput; // Combined input from all network players

[!endif]
[!if DPLAYVOICE]
    CNetVoice*              m_pNetVoice;            // DirectPlay voice helper class
    DVCLIENTCONFIG          m_dvClientConfig;       // Voice client config
    GUID                    m_guidDVSessionCT;      // GUID for choosen voice compression
    BOOL                    m_bNetworkPlayersTalking; // TRUE if any of the network players are talking
    BOOL                    m_bLocalPlayerTalking;  // TRUE if the local player is talking

[!endif]
    FLOAT                   m_fWorldRotX;           // World rotation state X-axis
    FLOAT                   m_fWorldRotY;           // World rotation state Y-axis

protected:
    virtual HRESULT OneTimeSceneInit();
    virtual HRESULT Render();
    virtual HRESULT FrameMove();
    virtual HRESULT FinalCleanup();

    HRESULT RenderText();

[!if DINPUT]
    HRESULT InitInput( HWND hWnd );
[!endif]
    void    UpdateInput( UserInput* pUserInput );
[!if DPLAY]
    HRESULT CombineInputFromAllPlayers( UserInput* pCombinedUserInput );
[!endif]
[!if DINPUT]
    void    CleanupDirectInput();
[!endif]

[!if DMUSIC || DSOUND]
    HRESULT InitAudio( HWND hWnd );

[!endif]
[!if DPLAY]
    HRESULT InitDirectPlay();
    void    CleanupDirectPlay();
    HRESULT ConnectViaDirectPlay();
    HRESULT SendLocalInputIfChanged();
    HRESULT SendWorldStateToAll();
    HRESULT SendPauseMessageToAll( BOOL bPause );

[!endif]
[!if DPLAYVOICE]
    HRESULT InitDirectPlayVoice();
    VOID    UpdateTalkingVariables();
    HRESULT UserConfigVoice();

[!endif]
    VOID    ReadSettings();
    VOID    WriteSettings();

public:
    HRESULT Create( HINSTANCE hInstance );
    INT     Run();
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    VOID    Pause( BOOL bPause );

    CMyApplication();
    virtual ~CMyApplication();
[!if ACTIONMAPPER]

    HRESULT InputAddDeviceCB( CInputDeviceManager::DeviceInfo* pDeviceInfo, const DIDEVICEINSTANCE* pdidi );
    static HRESULT CALLBACK StaticInputAddDeviceCB( CInputDeviceManager::DeviceInfo* pDeviceInfo, const DIDEVICEINSTANCE* pdidi, LPVOID pParam );   
[!endif]
[!if DPLAY]

    static HRESULT WINAPI StaticDirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
    HRESULT DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
    static HRESULT WINAPI StaticDirectPlayLobbyMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
    HRESULT DirectPlayLobbyMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
[!endif]
[!if DPLAYVOICE]

    static HRESULT WINAPI StaticDirectPlayVoiceServerMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
    HRESULT DirectPlayVoiceServerMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
    static HRESULT WINAPI StaticDirectPlayVoiceClientMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
    HRESULT DirectPlayVoiceClientMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
[!endif]
};



