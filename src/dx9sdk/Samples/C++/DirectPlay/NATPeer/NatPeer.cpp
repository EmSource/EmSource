//----------------------------------------------------------------------------
// File: NatPeer.cpp
//
// Desc: The main game file for the NAT Peer sample. 
//
// Copyright (c) 1999-2001 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef STRICT
#define STRICT
#endif // !STRICT

#include <windows.h>
#include <commctrl.h>
#include <basetsd.h>
#include <dplay8.h>
#include <dxerr9.h>
#include <tchar.h>
#include <stdio.h>
#include "DXUtil.h"
#include "resource.h"

//-----------------------------------------------------------------------------
// Platform-dependent includes
//-----------------------------------------------------------------------------
#ifdef UNDER_CE
    #include <aygshell.h>
#endif // UNDER_CE


//-----------------------------------------------------------------------------
// Player context locking defines
//-----------------------------------------------------------------------------
CRITICAL_SECTION g_csPlayerContext;
#define PLAYER_LOCK()                   EnterCriticalSection( &g_csPlayerContext ); 
#define PLAYER_ADDREF( pPlayerInfo )    if( pPlayerInfo ) pPlayerInfo->lRefCount++;
#define PLAYER_RELEASE( pPlayerInfo )   if( pPlayerInfo ) { pPlayerInfo->lRefCount--; if( pPlayerInfo->lRefCount <= 0 ) SAFE_DELETE( pPlayerInfo ); } pPlayerInfo = NULL;
#define PLAYER_UNLOCK()                 LeaveCriticalSection( &g_csPlayerContext );

CRITICAL_SECTION g_csHostContext;
#define HOST_LOCK()                     EnterCriticalSection( &g_csHostContext );
#define HOST_UNLOCK()                   LeaveCriticalSection( &g_csHostContext );


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
#define DPLAY_SAMPLE_KEY                TEXT("Software\\Microsoft\\DirectX DirectPlay Samples")
#define WM_APP_UPDATE_STATS             (WM_APP + 0)
#define WM_APP_DISPLAY_WAVE             (WM_APP + 1)
#define MAX_HOSTS                       16

#define DLG_EXIT_OK                     0
#define DLG_EXIT_CANCEL                 1
#define DLG_EXIT_ERROR                  2

#define NATPEER_PORT                    2505
#define NATRESOLVER_PORT                2506


//-----------------------------------------------------------------------------
// Custom types
//-----------------------------------------------------------------------------
struct APP_PLAYER_INFO
{
    LONG  lRefCount;                        // Ref count so we can cleanup when all threads 
                                            // are done w/ this object
    DPNID dpnidPlayer;                      // DPNID of player
    TCHAR strPlayerName[256];               // Player name
};

struct ConnectDlgOptions
{
    TCHAR strPlayerName[256];               // Local player name
    BOOL  bEnableResolution;                // Enable NAT address resolution
    TCHAR strServerAddress[256];            // NAT resolution server address
    DWORD dwServerPort;                     // NAT resolution server port
    TCHAR strPassword[256];                 // Server password
    BOOL  bHostSession;                     // Start as session host
    TCHAR strSessionName[256];              // Session name
    DWORD dwLocalPort;                      // Local port
};

struct HostInfo
{
    TCHAR strSessionName[256];              // Session name
    GUID guidInstance;                      // Instance GUID
    IDirectPlay8Address* pAddress;          // Host address
};



//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8Peer*       g_pDP                         = NULL;    // DirectPlay peer object
IDirectPlay8Address*    g_pAddressLocal               = NULL;    // Local device address
IDirectPlay8Address*    g_pAddressHost                = NULL;    // Remote host address
HWND                    g_hDlg                        = NULL;    // HWND of main dialog
DPNID                   g_dpnidLocalPlayer            = 0;       // DPNID of local player
DPNID                   g_dpnidHostPlayer             = 0;       // DPNID of host player
LONG                    g_lNumberOfActivePlayers      = 0;       // Number of players currently in game
TCHAR                   g_strAppName[256]             = TEXT("NAT Peer");

ConnectDlgOptions       g_DlgOptions                  = {0};     // Persistent dialog options
HostInfo                g_HostList[MAX_HOSTS]         = {0};     // List of detected hosts
DWORD                   g_dwNumHosts                  = 0;       // Number of detected hosts

DWORD                   g_dwRemotePort                = NATPEER_PORT;

// This GUID allows DirectPlay to find other instances of the same game on
// the network.  So it must be unique for every game, and the same for 
// every instance of that game.  // {02AE835D-9179-485f-8343-901D327CE794}
GUID g_guidApp = { 0x2ae835d, 0x9179, 0x485f, { 0x83, 0x43, 0x90, 0x1d, 0x32, 0x7c, 0xe7, 0x94 } };


//-----------------------------------------------------------------------------
// App specific DirectPlay messages and structures 
//-----------------------------------------------------------------------------
#define GAME_MSGID_WAVE        1

// Change compiler pack alignment to be BYTE aligned, and pop the current value
#pragma pack( push, 1 )

struct GAMEMSG_GENERIC
{
    DWORD dwType;
};

// Pop the old pack alignment
#pragma pack( pop )



//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT WINAPI   DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
INT_PTR CALLBACK ConnectDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK SearchDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK GreetingDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT          InitDirectPlay();
BOOL             IsServiceProviderValid( const GUID* pGuidSP );
VOID             OnInitConnectDialog( HWND hDlg );
VOID             OnCloseConnectDialog( HWND hDlg );
HRESULT          Host();
HRESULT          Connect( HWND hDlg );
HRESULT          EnumerateHosts( HWND hDlg, TCHAR* strSearch );
HRESULT          CreateLocalAddress();
HRESULT          CreateHostAddress( TCHAR* strHost );
HRESULT          WaveToAllPlayers();
VOID             AppendTextToEditControl( HWND hDlg, TCHAR* strNewLogLine );
VOID             OutputHostList( HWND hDlg );
HRESULT          RefreshStatusBarText( DPNID idLocal, DPNID idHost );
HRESULT          GetHostnamePortString( TCHAR* str, LPDIRECTPLAY8ADDRESS pAddress, DWORD dwBufferLen );




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------
INT APIENTRY _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, 
                      LPTSTR pCmdLine, INT nCmdShow )
{
    HRESULT hr;
    HKEY    hDPlaySampleRegKey;
    
#ifdef UNDER_CE
    // This is needed along with a hidden control in the RC file to make the
    // soft keyboard pop up when the user selects an edit control.
    SHInitExtraControls();
#endif // UNDER_CE

    InitCommonControls();

    InitializeCriticalSection( &g_csPlayerContext );
    InitializeCriticalSection( &g_csHostContext );
    
    // Read persistent state information from registry
    RegCreateKeyEx( HKEY_CURRENT_USER, DPLAY_SAMPLE_KEY, 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL, 
                    &hDPlaySampleRegKey, NULL );
    DXUtil_ReadStringRegKeyCch( hDPlaySampleRegKey, TEXT("Player Name"), 
                             g_DlgOptions.strPlayerName, MAX_PATH, TEXT("TestPlayer") );
    DXUtil_ReadStringRegKeyCch( hDPlaySampleRegKey, TEXT("Session Name"), 
                             g_DlgOptions.strSessionName, MAX_PATH, TEXT("TestGame") );
    
    g_DlgOptions.bEnableResolution = true;
    g_DlgOptions.bHostSession = true;
    g_DlgOptions.dwServerPort = NATRESOLVER_PORT;
    g_DlgOptions.dwLocalPort = NATPEER_PORT;

    // Init COM so we can use CoCreateInstance
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

    if( FAILED( hr = InitDirectPlay() ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("InitDirectPlay"), hr );
        MessageBox( NULL, TEXT("Failed initializing IDirectPlay8Peer. ")
                    TEXT("The sample will now quit."),
                    g_strAppName, MB_OK | MB_ICONERROR );
        return FALSE;
    }

    // Connect or host a DirectPlay session.  
    int nResult;
    nResult = DialogBox( GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CONNECT), NULL, 
                        (DLGPROC) ConnectDlgProc );
    
    

    if( DLG_EXIT_OK == nResult )
    {
        // Write information to the registry
        DXUtil_WriteStringRegKey( hDPlaySampleRegKey, TEXT("Player Name"), g_DlgOptions.strPlayerName );
        DXUtil_WriteStringRegKey( hDPlaySampleRegKey, TEXT("Session Name"), g_DlgOptions.strSessionName );

        // App is now connected via DirectPlay, so start the game.  
        // For this sample, we just start a simple dialog box game.
        DialogBox( hInst, MAKEINTRESOURCE(IDD_MAIN_GAME), NULL, 
                   (DLGPROC) GreetingDlgProc );
    }
    else if( DLG_EXIT_ERROR == nResult )
    {
        MessageBox( NULL, TEXT("Failed connecting or creating the session. ")
                    TEXT("Check debug output for more information.\n\n")
                    TEXT("The sample will now quit."),
                    g_strAppName, MB_OK | MB_ICONERROR );
    }
 
    if( g_pDP )
        g_pDP->Close(0);
    
    // Clear the stored host list
    UINT i;
    for( i=0; i < g_dwNumHosts; i++ )
        SAFE_RELEASE( g_HostList[i].pAddress );

    SAFE_RELEASE( g_pAddressLocal );
    SAFE_RELEASE( g_pAddressHost );
    SAFE_RELEASE( g_pDP );
    
    RegCloseKey( hDPlaySampleRegKey );
    DeleteCriticalSection( &g_csPlayerContext );
    DeleteCriticalSection( &g_csHostContext );
    CoUninitialize();

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: InitDirectPlay()
// Desc: Create and initialize DirectPlay peer object
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay()
{
    HRESULT hr;

    // Create IDirectPlay8Peer
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Peer, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Peer, 
                                       (LPVOID*) &g_pDP ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );

    // Turn off parameter validation in release builds
#ifdef _DEBUG
    const DWORD dwInitFlags = 0;
#else
    const DWORD dwInitFlags = DPNINITIALIZE_DISABLEPARAMVAL;
#endif // _DEBUG

    // Init IDirectPlay8Peer
    if( FAILED( hr = g_pDP->Initialize( NULL, DirectPlayMessageHandler, dwInitFlags ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Initialize"), hr );

    // Ensure that TCP/IP is a valid Service Provider
    if( FALSE == IsServiceProviderValid( &CLSID_DP8SP_TCPIP ) )
    {
        MessageBox(  NULL, TEXT("Failed validating CLSID_DP8SP_TCPIP.")
                     TEXT("\n\nYou must have TCP/IP installed on your")
                     TEXT("computer to run the NAT Peer sample."), 
                     TEXT("NAT Peer"), MB_ICONERROR | MB_OK );
        return E_FAIL;
    }

    return S_OK;
}





//-----------------------------------------------------------------------------
// Name: IsServiceProviderValid()
// Desc: Enumerates the list of local service providers to verify the passed
//       provider GUID is available.
//-----------------------------------------------------------------------------
BOOL IsServiceProviderValid( const GUID* pGuidSP )
{
    HRESULT                     hr              = S_OK;
    DPN_SERVICE_PROVIDER_INFO*  pdnSPInfo       = NULL;
    DWORD                       dwItems         = 0;
    DWORD                       dwSize          = 0;   
    
    // Enumerate all the Service Providers available
    hr = g_pDP->EnumServiceProviders( pGuidSP, NULL, NULL, &dwSize, &dwItems, 0);

    if( FAILED(hr) && hr != DPNERR_BUFFERTOOSMALL)
    {
        DXTRACE_ERR_MSGBOX( TEXT("EnumServiceProviders"), hr );
        goto LCleanup;
    }

    pdnSPInfo = (DPN_SERVICE_PROVIDER_INFO*) new BYTE[dwSize];
    
    if( FAILED( hr = g_pDP->EnumServiceProviders( pGuidSP, NULL, pdnSPInfo, &dwSize, &dwItems, 0 ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("EnumServiceProviders"), hr );
        goto LCleanup;
    }

    // If the returned list is empty, the given service provider is unavailable.
    hr = ( dwItems ) ? S_OK : E_FAIL;

LCleanup:
    SAFE_DELETE_ARRAY(pdnSPInfo);

    return SUCCEEDED(hr);
}




//-----------------------------------------------------------------------------
// Name: ConnectDlgProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ConnectDlgProc( HWND hDlg, UINT msg, 
                                 WPARAM wParam, LPARAM lParam )
{
    HRESULT hr;

    switch( msg ) 
    {
        case WM_INITDIALOG:
        {
#if defined(WIN32_PLATFORM_PSPC) && (_WIN32_WCE >= 300)
            SHINITDLGINFO   shidi;
            memset( &shidi, 0, sizeof(SHINITDLGINFO) );
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
            shidi.hDlg = hDlg;

            SetForegroundWindow( hDlg );
            SHInitDialog( &shidi );
#endif // WIN32_PLATFORM_PSPC

            g_hDlg = hDlg;
            OnInitConnectDialog( hDlg ); 
            return TRUE;
        }

        case WM_COMMAND:
        {   
            switch( LOWORD(wParam) )
            {
                case IDC_ENABLE_RESOLUTION:
                    EnableWindow( GetDlgItem( hDlg, IDC_SERVER_ADDRESS ), 
                                  IsDlgButtonChecked( hDlg, IDC_ENABLE_RESOLUTION ) );
                    EnableWindow( GetDlgItem( hDlg, IDC_SERVER_PORT ),
                                  IsDlgButtonChecked( hDlg, IDC_ENABLE_RESOLUTION ) );
                    EnableWindow( GetDlgItem( hDlg, IDC_PASSWORD ), 
                                  IsDlgButtonChecked( hDlg, IDC_ENABLE_RESOLUTION ) );
                    return TRUE;

                case IDC_HOST_SESSION:
                    EnableWindow( GetDlgItem( hDlg, IDC_SESSION_NAME ), 
                                  IsDlgButtonChecked( hDlg, IDC_HOST_SESSION ) );
                    EnableWindow( GetDlgItem( hDlg, IDC_LOCAL_PORT ),
                                  IsDlgButtonChecked( hDlg, IDC_HOST_SESSION ) );
                    return TRUE;

                case IDC_APPHELP:
                    DXUtil_LaunchReadme( hDlg, TEXT("DirectPlay\\NATPeer") );
                    return TRUE;

                case IDOK:
                    // Store dialog options
                    OnCloseConnectDialog( hDlg );
                    
                    // Valicate dialog input
                    if( g_DlgOptions.bEnableResolution && 
                        ( _tcslen( g_DlgOptions.strServerAddress ) == 0  ||
                          g_DlgOptions.dwServerPort == 0 ) )
                    {
                        MessageBox( hDlg, TEXT("If requesting NAT resolution, you must also specify\n")
                                          TEXT("the address and port of the NAT Resolver server."),
                                          TEXT("NAT Peer"), MB_OK );
                        return TRUE;            
                    }

                    if( g_DlgOptions.bHostSession )
                    {
                        // Hosting...
                        hr = Host();
                        if( FAILED(hr) )
                        {
                            DXTRACE_ERR( TEXT("Host"), hr );
                            return TRUE;
                        }
                    }
                    else
                    {
                        // Connecting...
                        ShowWindow( hDlg, SW_HIDE );

                        hr = Connect( hDlg );
                        if( FAILED(hr) )
                        {
                            if( hr == DPNERR_USERCANCEL )
                            {
                                ShowWindow( hDlg, SW_SHOW );
                            }
                            else
                            {
                                DXTRACE_ERR( TEXT("Connect"), hr );
                            }
                            return TRUE;
                        }
                    }

                    EndDialog( hDlg, DLG_EXIT_OK );
                    return TRUE;

                case IDCANCEL:
                    EndDialog( hDlg, DLG_EXIT_CANCEL );
                    return TRUE;
            }
            break;
        }
    }

    return FALSE; // Didn't handle message
}




//-----------------------------------------------------------------------------
// Name: OnInitConnectDialog
// Desc: Handler for dialog initialization
//-----------------------------------------------------------------------------
VOID OnInitConnectDialog( HWND hDlg )
{
    // Load and set the icon
    HICON hIcon = LoadIcon( GetModuleHandle(NULL), MAKEINTRESOURCE( IDI_MAIN ) );
    SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
    SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

    // Player Name
    SetDlgItemText( hDlg, IDC_PLAYER_NAME, g_DlgOptions.strPlayerName );

    // Enable NAT address resolution
    CheckDlgButton( hDlg, IDC_ENABLE_RESOLUTION, 
                    g_DlgOptions.bEnableResolution ? BST_CHECKED : BST_UNCHECKED );

    // Server Address
    SetDlgItemText( hDlg, IDC_SERVER_ADDRESS, g_DlgOptions.strServerAddress );
    EnableWindow( GetDlgItem( hDlg, IDC_SERVER_ADDRESS ), g_DlgOptions.bEnableResolution );

    // Server Port
    TCHAR strServerPort[40];
    _itot( g_DlgOptions.dwServerPort, strServerPort, 10 );
    SetDlgItemText( hDlg, IDC_SERVER_PORT, strServerPort );
    EnableWindow( GetDlgItem( hDlg, IDC_SERVER_PORT ), g_DlgOptions.bEnableResolution );

    // Password
    SetDlgItemText( hDlg, IDC_PASSWORD, g_DlgOptions.strPassword );
    EnableWindow( GetDlgItem( hDlg, IDC_PASSWORD ), g_DlgOptions.bEnableResolution );

    // Host Session
    CheckDlgButton( hDlg, IDC_HOST_SESSION,
                    g_DlgOptions.bHostSession ? BST_CHECKED : BST_UNCHECKED );

    // Session Name
    SetDlgItemText( hDlg, IDC_SESSION_NAME, g_DlgOptions.strSessionName );
    EnableWindow( GetDlgItem( hDlg, IDC_SESSION_NAME ), g_DlgOptions.bHostSession );

    // Local Port
    TCHAR strLocalPort[40];
    _itot( g_DlgOptions.dwLocalPort, strLocalPort, 10 );
    SetDlgItemText( hDlg, IDC_LOCAL_PORT, strLocalPort );
    EnableWindow( GetDlgItem( hDlg, IDC_LOCAL_PORT ), g_DlgOptions.bEnableResolution );
}




//-----------------------------------------------------------------------------
// Name: OnCloseConnectDialog
// Desc: Handler for dialog shutdown
//-----------------------------------------------------------------------------
VOID OnCloseConnectDialog( HWND hDlg )
{
    // Player Name                
    GetDlgItemText( hDlg, IDC_PLAYER_NAME, g_DlgOptions.strPlayerName, 256 );
    g_DlgOptions.strPlayerName[255] = 0;

    // Enable NAT address resolution
    g_DlgOptions.bEnableResolution = IsDlgButtonChecked( hDlg, IDC_ENABLE_RESOLUTION );
    
    // Server Address
    GetDlgItemText( hDlg, IDC_SERVER_ADDRESS, g_DlgOptions.strServerAddress, 256 );
    g_DlgOptions.strServerAddress[255] = 0;

    // Server Port
    TCHAR strServerPort[40];
    GetDlgItemText( hDlg, IDC_SERVER_PORT, strServerPort, 40 );
    strServerPort[39] = 0;
    g_DlgOptions.dwServerPort = _ttoi( strServerPort );

    // Password
    GetDlgItemText( hDlg, IDC_PASSWORD, g_DlgOptions.strPassword, 256 );
    g_DlgOptions.strPassword[255] = 0;

    // Host Session
    g_DlgOptions.bHostSession = IsDlgButtonChecked( hDlg, IDC_HOST_SESSION );
    
    // Session Name
    GetDlgItemText( hDlg, IDC_SESSION_NAME, g_DlgOptions.strSessionName, 256 );
    g_DlgOptions.strSessionName[255] = 0;

    // Local Port
    TCHAR strLocalPort[40];
    GetDlgItemText( hDlg, IDC_LOCAL_PORT, strLocalPort, 40 );
    strLocalPort[39] = 0;
    g_DlgOptions.dwLocalPort = _ttoi( strLocalPort );

}




//-----------------------------------------------------------------------------
// Name: Host
// Desc: Host a new session using the options in the configuration dialog
//-----------------------------------------------------------------------------
HRESULT Host() 
{
    HRESULT hr = S_OK;
    WCHAR wstrSession[256] = {0};
    WCHAR wstrPlayer[256] = {0};
    
    // Create device address
    if( FAILED( hr = CreateLocalAddress() ) )
        return hr;

    // Convert the strings for DirectPlay
    DXUtil_ConvertGenericStringToWideCch( wstrSession, g_DlgOptions.strSessionName, 256 );
    DXUtil_ConvertGenericStringToWideCch( wstrPlayer, g_DlgOptions.strPlayerName, 256 );

    // Create the player information
    DPN_PLAYER_INFO dpPlayerInfo = {0};
    dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
    dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
    dpPlayerInfo.pwszName = wstrPlayer;

    hr = g_pDP->SetPeerInfo( &dpPlayerInfo, NULL, NULL, DPNSETPEERINFO_SYNC );
    if( FAILED(hr) )
        return DXTRACE_ERR_MSGBOX( TEXT("SetPeerInfo"), hr );

    // Now set up the Application Description
    DPN_APPLICATION_DESC dpAppDesc = {0};
    dpAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpAppDesc.guidApplication = g_guidApp;
    dpAppDesc.pwszSessionName = wstrSession;
    dpAppDesc.dwFlags = DPNSESSION_NODPNSVR;

    // We are now ready to host the app
    hr = g_pDP->Host( &dpAppDesc,             // AppDesc
                      &g_pAddressLocal, 1,    // Device Address
                      NULL, NULL,             // Reserved
                      NULL,                   // Player Context
                      0 );                    // dwFlags
    
    if( FAILED(hr) )
        return DXTRACE_ERR_MSGBOX( TEXT("Host"), hr );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Connect
// Desc: Connect to a session using the options in the configuration dialog
//-----------------------------------------------------------------------------
HRESULT Connect( HWND hDlg ) 
{
    HRESULT hr = S_OK;
    WCHAR wstrPlayer[256] = {0};
    int nSelectedHost = 0;
    
    // Launch search dialog
    int nResult;
    nResult = DialogBoxParam( GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SEARCH), 
                              hDlg, SearchDlgProc, (LPARAM) &nSelectedHost );

    if( DLG_EXIT_OK != nResult )
        return ( nResult == DLG_EXIT_CANCEL ) ? DPNERR_USERCANCEL : E_FAIL;

    if( nSelectedHost < 0 || nSelectedHost >= (int) g_dwNumHosts )
        return E_FAIL;

    // Create device address
    if( FAILED( hr = CreateLocalAddress() ) )
        return hr;

    // Convert the player name for DirectPlay
    DXUtil_ConvertGenericStringToWideCch( wstrPlayer, g_DlgOptions.strPlayerName, 256 );

    // Create the player information
    DPN_PLAYER_INFO dpPlayerInfo = {0};
    dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
    dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
    dpPlayerInfo.pwszName = wstrPlayer;

    hr = g_pDP->SetPeerInfo( &dpPlayerInfo, NULL, NULL, DPNSETPEERINFO_SYNC );
    if( FAILED(hr) )
        return DXTRACE_ERR_MSGBOX( TEXT("SetPeerInfo"), hr );

    // Now set up the Application Description
    DPN_APPLICATION_DESC dpAppDesc = {0};
    dpAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpAppDesc.guidApplication = g_guidApp;
    dpAppDesc.guidInstance = g_HostList[nSelectedHost].guidInstance;
    
    // We are now ready to connect
    hr = g_pDP->Connect( &dpAppDesc,                          // AppDesc
                         g_HostList[nSelectedHost].pAddress, // Host Address
                         g_pAddressLocal,                     // Device Address
                         NULL, NULL,                          // Reserved
                         NULL, 0,                             // Connect Data
                         NULL, NULL,                          // Player Context
                         NULL,                                // Async Handle
                         DPNCONNECT_SYNC );                   // Flags
    
    if( FAILED(hr) )
        return DXTRACE_ERR_MSGBOX( TEXT("Connect"), hr );
    

    return S_OK;
}





//-----------------------------------------------------------------------------
// Name: EnumerateHosts
// Desc: Find active sessions
//-----------------------------------------------------------------------------
HRESULT EnumerateHosts( HWND hDlg, TCHAR* strSearch )
{
    HRESULT hr;
    UINT i=0; // Loop variable
    
    // Create a host address
    hr = CreateHostAddress( strSearch );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("CreateHostAddress"), hr );

    // Create device address
    hr = CreateLocalAddress();
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("CreateLocalAddress"), hr );

    // Clear the results list
    SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_RESETCONTENT, 0, 0 );
    EnableWindow( GetDlgItem( hDlg, IDC_CONNECT ), false );

    // Clear the stored host list
    for( i=0; i < g_dwNumHosts; i++ )
        SAFE_RELEASE( g_HostList[i].pAddress );

    g_dwNumHosts = 0;
   
    // Now set up the Application Description
    DPN_APPLICATION_DESC dpAppDesc = {0};
    dpAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpAppDesc.guidApplication = g_guidApp;

    // We now have the host address so lets enum
    hr = g_pDP->EnumHosts( &dpAppDesc,             // pApplicationDesc
                           g_pAddressHost,         // pdpaddrHost
                           g_pAddressLocal,        // pdpaddrDeviceInfo
                           NULL, 0,                // pvUserEnumData, size
                           4,                      // dwEnumCount
                           0,                      // dwRetryInterval
                           0,                      // dwTimeOut
                           NULL,                   // pvUserContext
                           NULL,                   // pAsyncHandle
                           DPNENUMHOSTS_SYNC );    // dwFlags

    if( FAILED(hr) )
        return DXTRACE_ERR_MSGBOX( TEXT("EnumHosts"), hr );

    // Output the host list
    OutputHostList( hDlg );

    return S_OK;
}
    



//-----------------------------------------------------------------------------
// Name: CreateLocalAddress
// Desc: Create the device address
//-----------------------------------------------------------------------------
HRESULT CreateLocalAddress() 
{
    HRESULT hr = S_OK;

    // Start clean
    SAFE_RELEASE( g_pAddressLocal );

    // Create our IDirectPlay8Address Device Address
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Address,
                                       (LPVOID*) &g_pAddressLocal ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
        return hr;
    }
    
    // Set the SP for our Device Address
    if( FAILED( hr = g_pAddressLocal->SetSP(&CLSID_DP8SP_TCPIP ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("SetSP"), hr );
        return hr;
    }

    // If NAT address resolution is enabled, set the parameters to enable
    // automatic connection to a NATResolver server.
    if( g_DlgOptions.bEnableResolution )
    {
        TCHAR strServer[256] = {0};

        // Append the port to the end of the NAT Resolver server address
        _sntprintf( strServer, 256, TEXT("%s:%d"), 
                    g_DlgOptions.strServerAddress, g_DlgOptions.dwServerPort );
        strServer[255] = 0;

        WCHAR wstrServer[256] = {0};
        WCHAR wstrPassword[256] = {0};

        DXUtil_ConvertGenericStringToWideCch( wstrServer, strServer, 256 );
        DXUtil_ConvertGenericStringToWideCch( wstrPassword, g_DlgOptions.strPassword, 256 );

        // Add the NATResolver server address
        if( wcslen( wstrServer ) > 0 )
        {
            hr = g_pAddressLocal->AddComponent( DPNA_KEY_NAT_RESOLVER,
                                                wstrServer,
                                                sizeof(WCHAR) * (DWORD)(wcslen(wstrServer)+1),
                                                DPNA_DATATYPE_STRING );
            if( FAILED(hr) )
                return DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
        }
      
        // Add the optional password
        if( wcslen( wstrPassword ) > 0 )
        {
            hr = g_pAddressLocal->AddComponent( DPNA_KEY_NAT_RESOLVER_USER_STRING,
                                                wstrPassword,
                                                sizeof(WCHAR) * (DWORD)(wcslen(wstrPassword)+1),
                                                DPNA_DATATYPE_STRING );
            if( FAILED(hr) )
                return DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
        }
    }

    // If the user is hosting and specified a local port, add it to the address
    if( g_DlgOptions.bHostSession && g_DlgOptions.dwLocalPort != 0 )
    {
        hr = g_pAddressLocal->AddComponent( DPNA_KEY_PORT,
                                            &(g_DlgOptions.dwLocalPort),
                                            sizeof(g_DlgOptions.dwLocalPort),
                                            DPNA_DATATYPE_DWORD );

        if( FAILED(hr) )
            return DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
    }
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateHostAddress()
// Desc: Creates a host address
//-----------------------------------------------------------------------------
HRESULT CreateHostAddress( TCHAR* strIPAddress )
{
    HRESULT hr = S_OK;
    WCHAR wszHostName[256] = {0};

    // Start clean
    SAFE_RELEASE( g_pAddressHost );

    // Create our IDirectPlay8Address Host Address
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Address,
                                       (LPVOID*) &g_pAddressHost ) ) )
    {
        return DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
    }
    
    // Set the SP for our Host Address
    if( FAILED( hr = g_pAddressHost->SetSP( &CLSID_DP8SP_TCPIP ) ) )
    {
        return DXTRACE_ERR_MSGBOX( TEXT("SetSP"), hr );
    }

    // If the user specified a hostname, add it to the search address
    if( strIPAddress != NULL && strIPAddress[0] != 0 )
	{
		DXUtil_ConvertGenericStringToWideCch( wszHostName, strIPAddress, 256 );

		hr = g_pAddressHost->AddComponent( DPNA_KEY_HOSTNAME, wszHostName, 
											(DWORD) (wcslen(wszHostName)+1)*sizeof(WCHAR), 
											DPNA_DATATYPE_STRING );
		if( FAILED(hr) )
			return DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
    }			
	
	// If the user specified a port, add it to the search address
	if( g_dwRemotePort != 0 )
	{
		hr = g_pAddressHost->AddComponent( DPNA_KEY_PORT, 
											&g_dwRemotePort, sizeof(g_dwRemotePort),
											DPNA_DATATYPE_DWORD );
		if( FAILED(hr) )
			return DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
			
	}


    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SearchDlgProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK SearchDlgProc( HWND hDlg, UINT msg, 
                                 WPARAM wParam, LPARAM lParam )
{
    HRESULT hr;
    static int* pnSelected = NULL;

    switch( msg ) 
    {
        case WM_INITDIALOG:
        {
#if defined(WIN32_PLATFORM_PSPC) && (_WIN32_WCE >= 300)
            SHINITDLGINFO   shidi;
            memset( &shidi, 0, sizeof(SHINITDLGINFO) );
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
            shidi.hDlg = hDlg;

            SetForegroundWindow( hDlg );
            SHInitDialog( &shidi );
#endif // WIN32_PLATFORM_PSPC

            pnSelected = (int*) lParam;

            SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_ADDSTRING, 0, 
                         (LPARAM) TEXT("Click \"Search\" to find hosts.") );
            EnableWindow( GetDlgItem( hDlg, IDC_CONNECT ), false );

            // Set the default port number
            if( g_dwRemotePort != 0 )
            {
                TCHAR strPort[40];
                _itot( g_dwRemotePort, strPort, 10 );
                strPort[39] = 0;
                SetDlgItemText( hDlg, IDC_REMOTE_PORT, strPort );
            }

            return TRUE;
        }

        case WM_COMMAND:
        {   
            switch( LOWORD(wParam) )
            {
                case IDC_SEARCH:
                    TCHAR strHostname[256];
                    TCHAR strPort[40];

                    GetDlgItemText( hDlg, IDC_SEARCH_ADDRESS, strHostname, 256 );
                    strHostname[255] = 0;

                    GetDlgItemText( hDlg, IDC_REMOTE_PORT, strPort, 40 );
                    strPort[39] = 0;
                    g_dwRemotePort = _ttoi( strPort );

                    hr = EnumerateHosts( hDlg, strHostname );
                    if( FAILED(hr) )
                    {
                        DXTRACE_ERR( TEXT("EnumerateHosts"), hr );
                        EndDialog( hDlg, DLG_EXIT_ERROR );
                    }
                    return TRUE;

                
                case IDC_CONNECT:
                    *pnSelected = SendDlgItemMessage( hDlg, IDC_SESSIONS, LB_GETCURSEL, 0, 0 );
                    EndDialog( hDlg, DLG_EXIT_OK );
                    return TRUE;

                case IDCANCEL:
                    EndDialog( hDlg, DLG_EXIT_CANCEL );
                    return TRUE;

                case IDC_SESSIONS:
                    int nSelected = SendDlgItemMessage( hDlg, IDC_SESSIONS, LB_GETCURSEL, 0, 0 );
                    EnableWindow( GetDlgItem( hDlg, IDC_CONNECT ), nSelected != LB_ERR );
                    return TRUE;
            }
            break;
        }
    }

    return FALSE; // Didn't handle message
}




//-----------------------------------------------------------------------------
// Name: GreetingDlgProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK GreetingDlgProc( HWND hDlg, UINT msg, 
                                  WPARAM wParam, LPARAM lParam )
{
    HRESULT hr;

    switch( msg ) 
    {
        case WM_INITDIALOG:
        {
#if defined(WIN32_PLATFORM_PSPC) && (_WIN32_WCE >= 300)
            SHINITDLGINFO   shidi;
            memset( &shidi, 0, sizeof(SHINITDLGINFO) );
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
            shidi.hDlg = hDlg;

            SetForegroundWindow( hDlg );
            SHInitDialog( &shidi );
#endif // WIN32_PLATFORM_PSPC

            g_hDlg = hDlg;

            // Load and set the icon
            HICON hIcon = LoadIcon( GetModuleHandle(NULL), MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            if( g_DlgOptions.bHostSession )
                SetWindowText( hDlg, TEXT("NAT Peer (Host)") );
            else
                SetWindowText( hDlg, TEXT("NAT Peer") );

            // Display local player's name
            SetDlgItemText( hDlg, IDC_PLAYER_NAME, g_DlgOptions.strPlayerName );

            PostMessage( hDlg, WM_APP_UPDATE_STATS, 0, 0 );
            break;
        }

        case WM_APP_UPDATE_STATS:
        {
            // Update the number of players in the game
            TCHAR strNumberPlayers[32];

            wsprintf( strNumberPlayers, TEXT("%d"), g_lNumberOfActivePlayers );
            SetDlgItemText( hDlg, IDC_NUM_PLAYERS, strNumberPlayers );

            // Update the status bar text
            RefreshStatusBarText( g_dpnidLocalPlayer, g_dpnidHostPlayer );
            break;
        }

        case WM_APP_DISPLAY_WAVE:
        {
            HRESULT          hr;
            DPNID            dpnidPlayer = (DWORD)wParam;
            APP_PLAYER_INFO* pPlayerInfo = NULL;
            
            PLAYER_LOCK(); // enter player context CS

            // Get the player context accosicated with this DPNID
            hr = g_pDP->GetPlayerContext( dpnidPlayer, 
                                          (LPVOID* const) &pPlayerInfo,
                                          0);

            PLAYER_ADDREF( pPlayerInfo ); // addref player, since we are using it now
            PLAYER_UNLOCK(); // leave player context CS

            if( FAILED(hr) || pPlayerInfo == NULL )
            {
                // The player who sent this may have gone away before this 
                // message was handled, so just ignore it
                break;
            }
            
            // Make wave message and display it.
            TCHAR szWaveMessage[MAX_PATH];
            _sntprintf( szWaveMessage, MAX_PATH-1, TEXT("%s just waved at you, %s!\r\n"), 
                        pPlayerInfo->strPlayerName, g_DlgOptions.strPlayerName );
            szWaveMessage[ MAX_PATH-1 ] = 0;

            PLAYER_LOCK();
            PLAYER_RELEASE( pPlayerInfo );  // Release player and cleanup if needed
            PLAYER_UNLOCK();

            AppendTextToEditControl( hDlg, szWaveMessage );
            break;
        }

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
                case IDC_WAVE:
                    if( FAILED( hr = WaveToAllPlayers() ) )
                    {
                        DXTRACE_ERR_MSGBOX( TEXT("WaveToAllPlayers"), hr );
                        EndDialog( hDlg, DLG_EXIT_ERROR );
                    }

                    return TRUE;

                case IDCANCEL:
                    EndDialog( hDlg, DLG_EXIT_CANCEL );
                    return TRUE;
            }
            break;
        }
    }

    return FALSE; // Didn't handle message
}




//-----------------------------------------------------------------------------
// Name: DirectPlayMessageHandler
// Desc: Handler for DirectPlay messages.  This function is called by
//       the DirectPlay message handler pool of threads, so be careful of thread
//       synchronization problems with shared memory
//-----------------------------------------------------------------------------
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, 
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
        case DPN_MSGID_ENUM_HOSTS_RESPONSE:
        {
            HRESULT hr = S_OK;
            BOOL bDuplicateHost = FALSE;
            PDPNMSG_ENUM_HOSTS_RESPONSE pEnumHostsResponseMsg;
            pEnumHostsResponseMsg = (PDPNMSG_ENUM_HOSTS_RESPONSE)pMsgBuffer;

            HOST_LOCK();

            // Make sure this host hasn't already been found
            for( UINT i=0; i < g_dwNumHosts; i++ )
            {
                if( g_HostList[i].guidInstance == pEnumHostsResponseMsg->pApplicationDescription->guidInstance )
                {
                    bDuplicateHost = TRUE;
                    break;
                }
            }

            if( !bDuplicateHost && g_dwNumHosts < MAX_HOSTS )
            {
                // Store information about detected host
                DXUtil_ConvertWideStringToGenericCch( g_HostList[g_dwNumHosts].strSessionName, 
                                                      pEnumHostsResponseMsg->pApplicationDescription->pwszSessionName, 256 );
            
                g_HostList[g_dwNumHosts].guidInstance = pEnumHostsResponseMsg->pApplicationDescription->guidInstance;
            
                hr = pEnumHostsResponseMsg->pAddressSender->Duplicate( &(g_HostList[g_dwNumHosts].pAddress) );
                if( FAILED(hr) )
                    DXTRACE_ERR( TEXT("Duplicate"), hr );

                if( SUCCEEDED(hr) )
                    g_dwNumHosts++;
            }

            HOST_UNLOCK();

            break;
        }

        case DPN_MSGID_CREATE_PLAYER:
        {
            HRESULT hr;
            PDPNMSG_CREATE_PLAYER pCreatePlayerMsg;
            pCreatePlayerMsg = (PDPNMSG_CREATE_PLAYER)pMsgBuffer;

            // Create a new and fill in a APP_PLAYER_INFO
            APP_PLAYER_INFO* pPlayerInfo = new APP_PLAYER_INFO;
            if( NULL == pPlayerInfo )
                break;

            ZeroMemory( pPlayerInfo, sizeof(APP_PLAYER_INFO) );
            pPlayerInfo->lRefCount   = 1;
            pPlayerInfo->dpnidPlayer = pCreatePlayerMsg->dpnidPlayer;

            // Get the peer info and extract its name
            DWORD dwSize = 0;
            DPN_PLAYER_INFO* pdpPlayerInfo = NULL;
            hr = DPNERR_CONNECTING;
            
            // GetPeerInfo might return DPNERR_CONNECTING when connecting, 
            // so just keep calling it if it does
            while( hr == DPNERR_CONNECTING ) 
                hr = g_pDP->GetPeerInfo( pCreatePlayerMsg->dpnidPlayer, pdpPlayerInfo, &dwSize, 0 );                                
                
            if( hr == DPNERR_BUFFERTOOSMALL )
            {
                pdpPlayerInfo = (DPN_PLAYER_INFO*) new BYTE[ dwSize ];
                if( NULL == pdpPlayerInfo )
                {
                    // Out of memory
                    SAFE_DELETE( pPlayerInfo );
                    break;
                }

                ZeroMemory( pdpPlayerInfo, dwSize );
                pdpPlayerInfo->dwSize = sizeof(DPN_PLAYER_INFO);
                
                hr = g_pDP->GetPeerInfo( pCreatePlayerMsg->dpnidPlayer, pdpPlayerInfo, &dwSize, 0 );
                if( SUCCEEDED(hr) )
                {
                    // This stores a extra TCHAR copy of the player name for 
                    // easier access.  This will be redundent copy since DPlay 
                    // also keeps a copy of the player name in GetPeerInfo()
                    DXUtil_ConvertWideStringToGenericCch( pPlayerInfo->strPlayerName, 
                                                       pdpPlayerInfo->pwszName, 256 );    
                                                       
                    if( pdpPlayerInfo->dwPlayerFlags & DPNPLAYER_LOCAL )
                        g_dpnidLocalPlayer = pCreatePlayerMsg->dpnidPlayer;
                    if( pdpPlayerInfo->dwPlayerFlags & DPNPLAYER_HOST )
                        g_dpnidHostPlayer = pCreatePlayerMsg->dpnidPlayer;
                }

                SAFE_DELETE_ARRAY( pdpPlayerInfo );
            }
                
            // Tell DirectPlay to store this pPlayerInfo 
            // pointer in the pvPlayerContext.
            pCreatePlayerMsg->pvPlayerContext = pPlayerInfo;

            // Update the number of active players, and 
            // post a message to the dialog thread to update the 
            // UI.  This keeps the DirectPlay message handler 
            // from blocking
            InterlockedIncrement( &g_lNumberOfActivePlayers );
            if( g_hDlg != NULL )
                PostMessage( g_hDlg, WM_APP_UPDATE_STATS, 0, 0 );

            break;
        }

        case DPN_MSGID_DESTROY_PLAYER:
        {
            PDPNMSG_DESTROY_PLAYER pDestroyPlayerMsg;
            pDestroyPlayerMsg = (PDPNMSG_DESTROY_PLAYER)pMsgBuffer;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pDestroyPlayerMsg->pvPlayerContext;

            PLAYER_LOCK();                  // enter player context CS
            PLAYER_RELEASE( pPlayerInfo );  // Release player and cleanup if needed
            PLAYER_UNLOCK();                // leave player context CS

            // Update the number of active players, and 
            // post a message to the dialog thread to update the 
            // UI.  This keeps the DirectPlay message handler 
            // from blocking
            InterlockedDecrement( &g_lNumberOfActivePlayers );
            if( g_hDlg != NULL )
                PostMessage( g_hDlg, WM_APP_UPDATE_STATS, 0, 0 );

            break;
        }

        case DPN_MSGID_TERMINATE_SESSION:
        {
            PDPNMSG_TERMINATE_SESSION pTerminateSessionMsg;
            pTerminateSessionMsg = (PDPNMSG_TERMINATE_SESSION)pMsgBuffer;

            // The session was terminated.  Generally we don't want to display dialog boxes
            // and block a DirectPlay message handler callback, but we are doing it in this
            // sample for simplicity.
            MessageBox( g_hDlg, TEXT("Session was terminated."),
                        g_strAppName, MB_OK | MB_ICONERROR );

            EndDialog( g_hDlg, 0 );
            break;
        }

        case DPN_MSGID_RECEIVE:
        {
            PDPNMSG_RECEIVE pReceiveMsg;
            pReceiveMsg = (PDPNMSG_RECEIVE)pMsgBuffer;

            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pReceiveMsg->pvPlayerContext;
            if( NULL == pPlayerInfo )
                break;

            // Validate incoming data: A malicious user could modify or create an application
            // to send bogus information; to help guard against logical errors and denial 
            // of service attacks, the size of incoming data should be checked against what
            // is expected.
            if( pReceiveMsg->dwReceiveDataSize < sizeof(GAMEMSG_GENERIC) )
                break;

            GAMEMSG_GENERIC* pMsg = (GAMEMSG_GENERIC*) pReceiveMsg->pReceiveData;
            if( pMsg->dwType == GAME_MSGID_WAVE )
            {
                // This message is sent when a player has waved to us, so 
                // post a message to the dialog thread to update the UI.  
                // This keeps the DirectPlay threads from blocking, and also
                // serializes the recieves since DirectPlayMessageHandler can
                // be called simultaneously from a pool of DirectPlay threads.
                PostMessage( g_hDlg, WM_APP_DISPLAY_WAVE, pPlayerInfo->dpnidPlayer, 0 );
            }
            break;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: WaveToAllPlayers()
// Desc: Send a app-defined "wave" DirectPlay message to all connected players
//-----------------------------------------------------------------------------
HRESULT WaveToAllPlayers()
{
    // This is called by the dialog UI thread.  This will send a message to all
    // the players or inform the player that there is no one to wave at.
    if( g_lNumberOfActivePlayers == 1 )
    {
        MessageBox( NULL, TEXT("No one is around to wave at! :("), 
                    TEXT("NAT Peer"), MB_OK );
    }
    else
    {
        // Send a message to all of the players
        GAMEMSG_GENERIC msgWave;
        msgWave.dwType = GAME_MSGID_WAVE;

        DPN_BUFFER_DESC bufferDesc;
        bufferDesc.dwBufferSize = sizeof(GAMEMSG_GENERIC);
        bufferDesc.pBufferData  = (BYTE*) &msgWave;

        // DirectPlay will tell via the message handler 
        // if there are any severe errors, so ignore any errors 
        DPNHANDLE hAsync;
        g_pDP->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1,
                       0, NULL, &hAsync, DPNSEND_NOLOOPBACK | DPNSEND_GUARANTEED );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: AppendTextToEditControl()
// Desc: Appends a string of text to the edit control
//-----------------------------------------------------------------------------
VOID AppendTextToEditControl( HWND hDlg, TCHAR* strNewLogLine )
{
    static TCHAR strText[1024*10];

    HWND hEdit = GetDlgItem( hDlg, IDC_LOG_EDIT );
    SendMessage( hEdit, WM_SETREDRAW, FALSE, 0 );
    GetWindowText( hEdit, strText, 1024*9 );

    _tcscat( strText, strNewLogLine );

    int nSecondLine = 0;
    if( SendMessage( hEdit, EM_GETLINECOUNT, 0, 0 ) > 9 )
        nSecondLine = (int)SendMessage( hEdit, EM_LINEINDEX, 1, 0 );

    SetWindowText( hEdit, &strText[nSecondLine] );

    SendMessage( hEdit, WM_SETREDRAW, TRUE, 0 );
    InvalidateRect( hEdit, NULL, TRUE );
    UpdateWindow( hEdit );
}




//-----------------------------------------------------------------------------
// Name: OutputHostList()
// Desc: Fill the UI sessions list with stored information
//-----------------------------------------------------------------------------
void OutputHostList( HWND hDlg )
{
    HRESULT                 hr;
    TCHAR                   strOutput[256];
    WCHAR*                  strURL = NULL;
    TCHAR*                  strBuffer = NULL;
    
    // Clear the results list
    SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_RESETCONTENT, 0, 0 );

    // Go through and print out all the hosts URL's that we found
    HOST_LOCK();

    for( UINT i=0; i < g_dwNumHosts; i++ )
    {
        DWORD dwNumChars = 0;

        hr = g_HostList[i].pAddress->GetURLW(NULL, &dwNumChars);

        if( hr == DPNERR_BUFFERTOOSMALL)
        {
            strURL = new WCHAR[dwNumChars];
            strBuffer = new TCHAR[dwNumChars];

            if( strURL && strBuffer &&
                SUCCEEDED( g_HostList[i].pAddress->GetURLW(strURL, &dwNumChars ) ) )
            {
                TCHAR* strTemp = NULL;
                DXUtil_ConvertWideStringToGenericCch( strBuffer, strURL, dwNumChars );

                // Compose output text
                if( g_HostList[i].strSessionName && lstrlen( g_HostList[i].strSessionName ) )
                    _tcsncpy( strOutput, g_HostList[i].strSessionName, 30 );
                else
                    lstrcpy( strOutput, TEXT("<unnamed>") );

                strTemp = _tcsstr( strBuffer, TEXT("hostname=") );
                if( strTemp )
                {
                    strTemp += lstrlen( TEXT("hostname=") );
                    lstrcat( strOutput, TEXT(" ( ") );
                    
                    while( *strTemp != 0 && *strTemp != TEXT(';') )
                    {
                        _tcsncat( strOutput, strTemp, 1 );
                        strTemp++;
                    }
                    
                    strTemp = _tcsstr( strBuffer, TEXT("port=") );
                    if( strTemp )
                    {
                        strTemp += lstrlen( TEXT("port=") );
                        lstrcat( strOutput, TEXT(":") );
                        
                        while( *strTemp != 0 && *strTemp != TEXT(';') )
                        {
                            _tcsncat( strOutput, strTemp, 1 );
                            strTemp++;
                        }
                    }

                    lstrcat( strOutput, TEXT(" )") );

                }
                SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_ADDSTRING,
                             0, (LPARAM) strOutput );
            }
        }

        SAFE_DELETE_ARRAY( strURL );
        SAFE_DELETE_ARRAY( strBuffer );
    }

    // Default message if no hosts found
    if( 0 == g_dwNumHosts )
        SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_ADDSTRING, 
                     0, (WPARAM) TEXT("No hosts found.") );

    HOST_UNLOCK();
}




//-----------------------------------------------------------------------------
// Name: RefreshStatusBarText()
// Desc: Refresh the current status bar text based on connection state
//-----------------------------------------------------------------------------
HRESULT RefreshStatusBarText( DPNID idLocal, DPNID idHost )
{
    HRESULT hr = S_OK; 
    TCHAR strStatus[ 1024 ] = {0};
    TCHAR strAddress[ 256 ] = {0};
    DWORD dwNumAddresses = 0; // Count of address objects
    LPDIRECTPLAY8ADDRESS *rpAddresses = NULL; // Range of addresses    
    DWORD i = 0; // Loop variable

    // Margin the status text
    _tcsncpy( strStatus, TEXT("   "), 1023 );
    strStatus[ 1023 ] = 0;

    if( idLocal == NULL || idHost == NULL )
    {
        // If the host or local dpnid is not set, this should mean the player
        // creation messages have not yet arrived
        _tcsncat( strStatus, TEXT("Not connected"), 1023 - lstrlen( strStatus ) );
        strStatus[ 1023 ] = 0;
        dwNumAddresses = 0;
    }
    else if( idLocal == idHost )
    {
        // Else if the host and local dpnid's are equal, the local player is
        // the session host
        _tcsncat( strStatus, TEXT("Hosting"), 1023 - lstrlen( strStatus ) );
        strStatus[ 1023 ] = 0;
        dwNumAddresses = 0;

        // Determine the buffer size needed to hold the addresses
        hr = g_pDP->GetLocalHostAddresses( rpAddresses, &dwNumAddresses, 0 );
        if( DPNERR_BUFFERTOOSMALL != hr )
            goto LCleanReturn;  

        // Allocate the array
        rpAddresses = new LPDIRECTPLAY8ADDRESS[ dwNumAddresses ];
        if( NULL == rpAddresses )
        {
            hr = E_OUTOFMEMORY;
            goto LCleanReturn;
        }

        ZeroMemory( rpAddresses, dwNumAddresses * sizeof(LPDIRECTPLAY8ADDRESS) );

        // Retrieve the addresses
        hr = g_pDP->GetLocalHostAddresses( rpAddresses, &dwNumAddresses, 0 );
        if( FAILED(hr) )
            goto LCleanReturn;  
    }
    else
    {
        // Else the local player is connected to a remote session
        _tcsncat( strStatus, TEXT("Connected"), 1023 - lstrlen( strStatus ) );
        strStatus[ 1023 ] = 0;
        dwNumAddresses = 1;

        // Allocate the array
        rpAddresses = new LPDIRECTPLAY8ADDRESS[ dwNumAddresses ];
        if( NULL == rpAddresses )
        {
            hr = E_OUTOFMEMORY;
            goto LCleanReturn;
        }

        ZeroMemory( rpAddresses, dwNumAddresses * sizeof(LPDIRECTPLAY8ADDRESS) );

        // Retrieve the address
        hr = g_pDP->GetPeerAddress( idHost, &rpAddresses[0], 0 );
        if( FAILED(hr) )
            goto LCleanReturn;
    }

    // If we have addresses to report, determine a reasonable way to output them
    if( dwNumAddresses > 0 )
    {
        // Get the provider from the DirectPlay address
        GUID guidSP;
        hr = rpAddresses[0]->GetSP( &guidSP );
        if( FAILED(hr) )
            goto LCleanReturn;

        TCHAR strProvider[ 256 ] = {0};
  
        if( CLSID_DP8SP_IPX == guidSP )
            _tcsncpy( strProvider, TEXT(" via IPX"), 256 );
        else if( CLSID_DP8SP_TCPIP == guidSP )
            _tcsncpy( strProvider, TEXT(" via TCP/IP"), 256 );
        else if( CLSID_DP8SP_MODEM == guidSP )
            _tcsncpy( strProvider, TEXT(" via Modem"), 256 );
        else if( CLSID_DP8SP_SERIAL == guidSP )
            _tcsncpy( strProvider, TEXT(" via Serial"), 256 );
        else if( CLSID_DP8SP_BLUETOOTH == guidSP )
            _tcsncpy( strProvider, TEXT(" via Bluetooth"), 256 );
        
        _tcsncat( strStatus, strProvider, 1023 - lstrlen( strStatus ) );
        strStatus[ 1023 ] = 0;

        // If we are using TCP/IP or IPX, display the address list
        if( CLSID_DP8SP_IPX == guidSP ||
            CLSID_DP8SP_TCPIP == guidSP )
        {
            // Append the addresses to the status text
            for( i=0; i < dwNumAddresses; i++ )
            {
                // Get the IP address
                if( FAILED( GetHostnamePortString( strAddress, rpAddresses[ i ], 256 ) ) )
                    break;

                // Add formatting characters
                TCHAR* strSpacing = ( i != 0 ) ? TEXT(", ") : 
                                    ( idLocal == idHost ) ? TEXT(" at ") : TEXT(" to ");                      
        
                _tcsncat( strStatus, strSpacing, 1023 - lstrlen( strStatus ) );
                strStatus[ 1023 ] = 0;


                // Add the IP address string
                _tcsncat( strStatus, strAddress, 1023 - lstrlen( strStatus ) );
                strStatus[ 1023 ] = 0;
     
            }
        }
    }

    // Margin the status text
    _tcsncat( strStatus, TEXT("   "), 1023 - lstrlen( strStatus ) );
    strStatus[ 1023 ] = 0;

    // Set the text
    SendDlgItemMessage( g_hDlg, IDC_STATUS_BAR_TEXT, WM_SETTEXT, 0, (LPARAM) strStatus );
    hr = S_OK;
  
LCleanReturn:
    for( i=0; i < dwNumAddresses; i++ )
        SAFE_RELEASE( rpAddresses[i] );

    SAFE_DELETE_ARRAY( rpAddresses );

    return hr;
}




//-----------------------------------------------------------------------------
// Name: GetHostnamePortString
// Desc: Stores the hostname and port number of the given DirectPlay 
//       address in the provided string.
//-----------------------------------------------------------------------------
HRESULT GetHostnamePortString( TCHAR* str, LPDIRECTPLAY8ADDRESS pAddress, DWORD dwBufferLen )
{
    HRESULT hr = S_OK;

    // Sanity check
    if( NULL == str || NULL == pAddress )
        return E_FAIL;

    // Get the hostname string from the DirectPlay address
    WCHAR wstrHostname[ 256 ] = {0};
    DWORD dwSize = sizeof(wstrHostname);
    DWORD dwDataType = 0;
    hr = pAddress->GetComponentByName( L"hostname", wstrHostname, &dwSize, &dwDataType );
    if( FAILED(hr) )
        return hr;

    // Convert from wide character to generic
    TCHAR strHostname[ 256 ] = {0};
    DXUtil_ConvertWideStringToGenericCch( strHostname, wstrHostname, 256 );

    // Get the port value from the DirectPlay address
    DWORD dwPort = 0;
    dwSize = sizeof(DWORD);
    hr = pAddress->GetComponentByName( L"port", &dwPort, &dwSize, &dwDataType );
    if( FAILED(hr) )
        return hr;

    // Copy the address string and null terminate the result
    _sntprintf( str, dwBufferLen, TEXT("%s:%d"), strHostname, dwPort );
    str[ dwBufferLen-1 ] = TEXT('\0');

    return S_OK;
}