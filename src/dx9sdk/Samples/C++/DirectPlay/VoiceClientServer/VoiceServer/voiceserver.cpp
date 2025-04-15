//----------------------------------------------------------------------------
// File: VoiceServer.cpp
//
// Desc: The VoiceClientServer sample is a simple DirectPlay 
//       voice-based client/server application. 
//
// Copyright (c) 1999-2001 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <basetsd.h>
#include <dplay8.h>
#include <dpaddr.h>
#include <dxerr9.h>
#include <stdio.h>
#include <tchar.h>
#include "NetVoice.h"
#include "VoiceClientServer.h"
#include "DXUtil.h"
#include "resource.h"




//-----------------------------------------------------------------------------
// Player context locking defines
//-----------------------------------------------------------------------------
CRITICAL_SECTION g_csPlayerContext;
#define PLAYER_LOCK()                   EnterCriticalSection( &g_csPlayerContext ); 
#define PLAYER_ADDREF( pPlayerInfo )    if( pPlayerInfo ) pPlayerInfo->lRefCount++;
#define PLAYER_RELEASE( pPlayerInfo )   if( pPlayerInfo ) { pPlayerInfo->lRefCount--; if( pPlayerInfo->lRefCount <= 0 ) SAFE_DELETE( pPlayerInfo ); } pPlayerInfo = NULL;
#define PLAYER_UNLOCK()                 LeaveCriticalSection( &g_csPlayerContext );


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
struct APP_PLAYER_INFO
{
    LONG  lRefCount;                        // Ref count so we can cleanup when all threads 
                                            // are done w/ this object
    DPNID dpnidPlayer;                      // DPNID of player
    TCHAR strPlayerName[MAX_PLAYER_NAME];   // Player name
};




//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8Server* g_pDPServer                  = NULL;    // DirectPlay server object
CNetVoice*         g_pNetVoice                   = NULL;    // DirectPlay voice helper class
HINSTANCE          g_hInst                       = NULL;    // HINST of app
HWND               g_hDlg                        = NULL;    // HWND of main dialog
LONG               g_lNumberOfActivePlayers      = 0;       // Number of players currently in game
TCHAR              g_strAppName[256]             = TEXT("VoiceServer");
TCHAR              g_strSessionName[MAX_PATH];              // Session name
DWORD              g_dwPort                      = VOICECLIENTSERVER_PORT; // Port
HRESULT            g_hrDialog;                              // Exit code for app 
BOOL               g_bServerStarted              = FALSE;   // TRUE if the server has started
GUID               g_guidDVSessionCT;                       // GUID for choosen voice compression




//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT WINAPI   DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
HRESULT CALLBACK DirectPlayVoiceServerMessageHandler( LPVOID lpvUserContext, DWORD dwMessageType, LPVOID lpMessage );
INT_PTR CALLBACK ServerDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT  StartServer( HWND hDlg );
VOID     StopServer( HWND hDlg );
VOID     DisplayPlayers( HWND hDlg );
HRESULT  SendCreatePlayerMsg( APP_PLAYER_INFO* pPlayerInfo, DPNID dpnidTarget );
HRESULT  SendWorldStateToNewPlayer( DPNID dpnidPlayer );
HRESULT  SendDestroyPlayerMsgToAll( APP_PLAYER_INFO* pPlayerInfo );
HRESULT  EnumVoiceCompressionCodecs( HWND hDlg );
HRESULT  RefreshStatusBarText( BOOL bIsHosting );
HRESULT  GetHostnamePortString( TCHAR* str, LPDIRECTPLAY8ADDRESS pAddress, DWORD dwBufferLen );





//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------
INT APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, 
                      LPSTR pCmdLine, INT nCmdShow )
{
    HKEY    hDPlaySampleRegKey;

    InitCommonControls();

    g_hInst = hInst; 
    InitializeCriticalSection( &g_csPlayerContext );

    // Read persistent state information from registry
    RegCreateKeyEx( HKEY_CURRENT_USER, DPLAY_SAMPLE_KEY, 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL, 
                    &hDPlaySampleRegKey, NULL );
    DXUtil_ReadStringRegKeyCch( hDPlaySampleRegKey, TEXT("Session Name"), 
                                g_strSessionName, MAX_PATH, TEXT("TestGame") );
 
    // Init COM so we can use CoCreateInstance
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

    // For this sample, we just start a simple dialog box server
    g_hrDialog = S_OK;
    DialogBox( hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC) ServerDlgProc );

    if( FAILED( g_hrDialog ) )
    {
        if( g_hrDialog == DPNERR_CONNECTIONLOST )
        {
            MessageBox( NULL, TEXT("The DirectPlay session was lost. ")
                        TEXT("The server will now quit."),
                        g_strAppName, MB_OK | MB_ICONERROR );
        }
        else
        {
            DXTRACE_ERR_MSGBOX( TEXT("DialogBox"), g_hrDialog );
            MessageBox( NULL, TEXT("An error occured. ")
                        TEXT("The server will now quit."),
                        g_strAppName, MB_OK | MB_ICONERROR );
        }
    }

    DXUtil_WriteStringRegKey( hDPlaySampleRegKey, TEXT("Session Name"), g_strSessionName );
    
    StopServer( NULL );

    RegCloseKey( hDPlaySampleRegKey );
    DeleteCriticalSection( &g_csPlayerContext );
    CoUninitialize();

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: ServerDlgProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ServerDlgProc( HWND hDlg, UINT msg, 
                                WPARAM wParam, LPARAM lParam )
{
    switch( msg ) 
    {
        case WM_INITDIALOG:
        {
            g_hDlg = hDlg;

            // Load and set the icon
            HICON hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            SetWindowText( hDlg, TEXT("VoiceServer") );
            SetDlgItemText( hDlg, IDC_SESSION_NAME, g_strSessionName );

            // Set the port to either a number or blank
            if( g_dwPort != 0 )
                SetDlgItemInt( hDlg, IDC_PORT, g_dwPort, FALSE );
            else
                SetDlgItemText( hDlg, IDC_PORT, TEXT("") );

            SetDlgItemText( hDlg, IDC_STATUS, TEXT("Server stopped.") );

            EnumVoiceCompressionCodecs( hDlg );
            CheckRadioButton( hDlg, IDC_FORWARDING, IDC_MIXING, IDC_FORWARDING );

            PostMessage( hDlg, WM_APP_UPDATE_STATS, 0, 0 );
            break;
        }

        case WM_APP_UPDATE_STATS:
        {
            // Update the number of players in the game
            TCHAR strNumberPlayers[32];

            wsprintf( strNumberPlayers, TEXT("%d"), g_lNumberOfActivePlayers );
            SetDlgItemText( hDlg, IDC_NUM_PLAYERS, strNumberPlayers );
            DisplayPlayers( hDlg );
            RefreshStatusBarText( g_bServerStarted );

            break;
        }

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
                case IDC_START:
                    if( !g_bServerStarted )
                    {
                        if( FAILED( g_hrDialog = StartServer( hDlg ) ) )
                        {
                            DXTRACE_ERR_MSGBOX( TEXT("StartServer"), g_hrDialog );
                            EndDialog( hDlg, 0 );
                        }
                    }
                    else
                    {
                        StopServer( hDlg );
                    }

                    // Update the UI
                    if( g_bServerStarted )
                        SetDlgItemText( hDlg, IDC_START, TEXT("Stop Server") );
                    else
                        SetDlgItemText( hDlg, IDC_START, TEXT("Start Server") );

                    EnableWindow( GetDlgItem( hDlg, IDC_SESSION_NAME ), !g_bServerStarted );
                    EnableWindow( GetDlgItem( hDlg, IDC_COMPRESSION_COMBO ), !g_bServerStarted );
                    EnableWindow( GetDlgItem( hDlg, IDC_FORWARDING ), !g_bServerStarted );
                    EnableWindow( GetDlgItem( hDlg, IDC_MIXING ), !g_bServerStarted );                                               
                    EnableWindow( GetDlgItem( hDlg, IDC_PORT ), !g_bServerStarted );

                    RefreshStatusBarText( g_bServerStarted );
                    break;

                case IDCANCEL:
                    StopServer( hDlg );
                    EndDialog( hDlg, 0 );
                    return TRUE;
            }
            break;
        }
    }

    return FALSE; // Didn't handle message
}




//-----------------------------------------------------------------------------
// Name: EnumVoiceCompressionCodecs()
// Desc: Asks DirectPlay Voice what voice compression codecs are availible
//       and fills the combo box thier names and GUIDs.
//-----------------------------------------------------------------------------
HRESULT EnumVoiceCompressionCodecs( HWND hDlg )
{
    LPDIRECTPLAYVOICECLIENT pVoiceClient        = NULL;
    LPDVCOMPRESSIONINFO     pdvCompressionInfo  = NULL;
    LPGUID  pGuid         = NULL;
    LPBYTE  pBuffer       = NULL;
    DWORD   dwSize        = 0;
    DWORD   dwNumElements = 0;
    HWND    hPulldown     = GetDlgItem( hDlg, IDC_COMPRESSION_COMBO );
    HRESULT hr;
    LONG    lIndex;
    LONG    lFirst        = -1;

    // Create a VoiceClient object
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlayVoiceClient, NULL, 
                                       CLSCTX_INPROC_SERVER, IID_IDirectPlayVoiceClient, 
                                       (VOID**) &pVoiceClient ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
        goto LCleanReturn;
    }

    // Determine space needed for compression info
    hr = pVoiceClient->GetCompressionTypes( pBuffer, &dwSize, &dwNumElements, 0 );
    if( FAILED(hr) && hr != DVERR_BUFFERTOOSMALL )
    {
        DXTRACE_ERR_MSGBOX( TEXT("GetCompressionTypes"), hr );
        goto LCleanReturn;
    }

    // Allocate space
    pBuffer = new BYTE[dwSize];
    if( NULL == pBuffer )
    {
        hr = E_OUTOFMEMORY;
        DXTRACE_ERR_MSGBOX( TEXT("EnumVoiceCompressionCodecs"), hr );
        goto LCleanReturn;
    }

    // Get compression types
    if( FAILED( hr = pVoiceClient->GetCompressionTypes( pBuffer, &dwSize, 
                                                        &dwNumElements, 0 ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("GetCompressionTypes"), hr );
        goto LCleanReturn;
    }

    pdvCompressionInfo = (LPDVCOMPRESSIONINFO) pBuffer;

    // For each detected type, add an item to the list
    DWORD dwIndex;
    for( dwIndex = 0; dwIndex < dwNumElements; dwIndex++ )
    {
        TCHAR strName[MAX_PATH];
        DXUtil_ConvertWideStringToGenericCch( strName, pdvCompressionInfo[dwIndex].lpszName, MAX_PATH );

        lIndex = (LONG)SendMessage( hPulldown, CB_ADDSTRING, 0, (LPARAM) strName );

        pGuid = new GUID;
        if( NULL == pGuid )
        {
            hr = E_OUTOFMEMORY;
            DXTRACE_ERR_MSGBOX( TEXT("EnumVoiceCompressionCodecs"), hr );
            goto LCleanReturn;
        }

        (*pGuid) = pdvCompressionInfo[dwIndex].guidType;
        SendMessage( hPulldown, CB_SETITEMDATA, lIndex, (LPARAM) pGuid );

        if( pdvCompressionInfo[dwIndex].guidType == DPVCTGUID_SC03 )
            lFirst = lIndex;
    }

    
    SendMessage( hPulldown, CB_SETCURSEL, lFirst, 0 );

    hr = S_OK;

LCleanReturn:
    SAFE_DELETE_ARRAY( pBuffer );
    SAFE_RELEASE( pVoiceClient );

    return hr;
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
        case DPN_MSGID_CREATE_PLAYER:
        {
            HRESULT hr;
            PDPNMSG_CREATE_PLAYER pCreatePlayerMsg;
            pCreatePlayerMsg = (PDPNMSG_CREATE_PLAYER)pMsgBuffer;

            // Determine the required size of the buffer
            DWORD dwSize = 0;
            DPN_PLAYER_INFO* pdpPlayerInfo = NULL;
            hr = g_pDPServer->GetClientInfo( pCreatePlayerMsg->dpnidPlayer, 
                                             pdpPlayerInfo, &dwSize, 0 );
            if( FAILED(hr) && hr != DPNERR_BUFFERTOOSMALL )
            {
                // Ignore this message if this is for the host
                if( hr != DPNERR_INVALIDPLAYER )
                    DXTRACE_ERR_MSGBOX( TEXT("GetClientInfo"), hr );

                break;
            }

            // Allocate space for client info
            pdpPlayerInfo = (DPN_PLAYER_INFO*) new BYTE[ dwSize ];
            if( NULL == pdpPlayerInfo )
            {
                DXTRACE_ERR_MSGBOX( TEXT("DPN_MSGID_CREATE_PLAYER"), E_OUTOFMEMORY );
                break;
            }

            ZeroMemory( pdpPlayerInfo, dwSize );
            pdpPlayerInfo->dwSize = sizeof(DPN_PLAYER_INFO);

            // Get the peer info and extract its name  
            hr = g_pDPServer->GetClientInfo( pCreatePlayerMsg->dpnidPlayer, 
                                       pdpPlayerInfo, &dwSize, 0 );
            if( FAILED(hr) )
            {
                DXTRACE_ERR_MSGBOX( TEXT("GetClientInfo"), hr );
                SAFE_DELETE_ARRAY( pdpPlayerInfo );
                break;
            }

            // Create a new and fill in a APP_PLAYER_INFO
            APP_PLAYER_INFO* pPlayerInfo = new APP_PLAYER_INFO;
            if( NULL == pPlayerInfo )
            {
                DXTRACE_ERR_MSGBOX( TEXT("DPN_MSGID_CREATE_PLAYER"), E_OUTOFMEMORY );
                SAFE_DELETE_ARRAY( pdpPlayerInfo );
                break;
            }

            ZeroMemory( pPlayerInfo, sizeof(APP_PLAYER_INFO) );
            pPlayerInfo->lRefCount   = 1;
            pPlayerInfo->dpnidPlayer = pCreatePlayerMsg->dpnidPlayer;

            // This stores a extra TCHAR copy of the player name for 
            // easier access.  This will be redundent copy since DPlay 
            // also keeps a copy of the player name in GetClientInfo()
            DXUtil_ConvertWideStringToGenericCch( pPlayerInfo->strPlayerName, 
                                                  pdpPlayerInfo->pwszName, MAX_PLAYER_NAME );

            SAFE_DELETE_ARRAY( pdpPlayerInfo );

            // Tell DirectPlay to store this pPlayerInfo 
            // pointer in the pvPlayerContext.
            pCreatePlayerMsg->pvPlayerContext = pPlayerInfo;

            // Send all connected players a message telling about this new player
            SendCreatePlayerMsg( pPlayerInfo, DPNID_ALL_PLAYERS_GROUP );

            // Tell this new player about the world state
            SendWorldStateToNewPlayer( pCreatePlayerMsg->dpnidPlayer );

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

            // Ignore this message if this is the host player
            if( pPlayerInfo == NULL )
                break; 

            // Send all connected players a message telling about this destroyed player
            SendDestroyPlayerMsgToAll( pPlayerInfo );

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

            g_hrDialog = DPNERR_CONNECTIONLOST;
            EndDialog( g_hDlg, 0 );
            break;
        }

        case DPN_MSGID_RECEIVE:
        {
            //PDPNMSG_RECEIVE pReceiveMsg = (PDPNMSG_RECEIVE)pMsgBuffer;
            //APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pReceiveMsg->pvPlayerContext;
            //GAMEMSG_GENERIC* pMsg = (GAMEMSG_GENERIC*) pReceiveMsg->pReceiveData;
            // This simple voice server doesn't expect any msgs from the clients
            break;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayVoiceServerMessageHandler()
// Desc: The callback for DirectPlayVoice server messages.  
//-----------------------------------------------------------------------------
HRESULT CALLBACK DirectPlayVoiceServerMessageHandler( LPVOID lpvUserContext, DWORD dwMessageType,
                                                      LPVOID lpMessage )
{
    // This simple sample doesn't respond to any server messages
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: StartServer
// Desc: 
//-----------------------------------------------------------------------------
HRESULT StartServer( HWND hDlg )
{
    DWORD dwSessionType;
    int lCurSelection;
    HRESULT hr;
    PDIRECTPLAY8ADDRESS pDP8AddrLocal = NULL;

    SetDlgItemText( hDlg, IDC_STATUS, TEXT("Starting server...") );
    SetCursor( LoadCursor(NULL, IDC_WAIT) );

    WCHAR wstrSessionName[MAX_PATH];
    GetDlgItemText( hDlg, IDC_SESSION_NAME, g_strSessionName, MAX_PATH );
    DXUtil_ConvertGenericStringToWideCch( wstrSessionName, g_strSessionName, MAX_PATH );

    BOOL bPortTranslated;
    g_dwPort = GetDlgItemInt( hDlg, IDC_PORT, &bPortTranslated, FALSE );
    if( !bPortTranslated )
        g_dwPort = 0;

    // Create IDirectPlay8Server
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Server, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Server, 
                                       (LPVOID*) &g_pDPServer ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );

    // Turn off parameter validation in release builds
#ifdef _DEBUG
    const DWORD dwInitFlags = 0;
#else
    const DWORD dwInitFlags = DPNINITIALIZE_DISABLEPARAMVAL;
#endif // _DEBUG

    // Init IDirectPlay8Server
    if( FAILED( hr = g_pDPServer->Initialize( NULL, DirectPlayMessageHandler, dwInitFlags ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Initialize"), hr );

    hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL, 
                           CLSCTX_ALL, IID_IDirectPlay8Address, 
                           (LPVOID*) &pDP8AddrLocal );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
        goto LCleanup;
    }

    hr = pDP8AddrLocal->SetSP( &CLSID_DP8SP_TCPIP );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("SetSP"), hr );
        goto LCleanup;
    }

    // Add the port to pDP8AddrLocal, if the port is non-zero.
    // If the port is 0, then DirectPlay will pick a port, 
    // Games will typically hard code the port so the 
    // user need not know it
    if( g_dwPort != 0 )
    {
        if( FAILED( hr = pDP8AddrLocal->AddComponent( DPNA_KEY_PORT, 
                                                      &g_dwPort, sizeof(g_dwPort),
                                                      DPNA_DATATYPE_DWORD ) ) )
            return DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
    }

    DPN_APPLICATION_DESC dpnAppDesc;
    ZeroMemory( &dpnAppDesc, sizeof(DPN_APPLICATION_DESC) );
    dpnAppDesc.dwSize           = sizeof( DPN_APPLICATION_DESC );
    dpnAppDesc.dwFlags          = DPNSESSION_CLIENT_SERVER;
    dpnAppDesc.guidApplication  = g_guidApp;
    dpnAppDesc.pwszSessionName  = wstrSessionName;

    hr = g_pDPServer->Host( &dpnAppDesc, &pDP8AddrLocal, 1, NULL, NULL, NULL, 0  );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("Host"), hr );
        goto LCleanup;
    }

    // Get the selected compression codec
    g_guidDVSessionCT = DPVCTGUID_DEFAULT;

    lCurSelection = (LONG)SendDlgItemMessage( hDlg, IDC_COMPRESSION_COMBO, CB_GETCURSEL, 0, 0 );
    if( lCurSelection != CB_ERR )
    {
        GUID* pGuidCT = (LPGUID) SendDlgItemMessage( hDlg, IDC_COMPRESSION_COMBO, 
                                                    CB_GETITEMDATA, lCurSelection, 0 );
        if( pGuidCT != NULL )
            g_guidDVSessionCT = (*pGuidCT);
    }

    // Create a DirectPlay Voice session
    g_pNetVoice = new CNetVoice( NULL, DirectPlayVoiceServerMessageHandler );
    if( NULL == g_pNetVoice )
    {
        hr = E_OUTOFMEMORY;
        DXTRACE_ERR_MSGBOX( TEXT("StartServer"), hr );
        goto LCleanup;
    }

    if( IsDlgButtonChecked( hDlg, IDC_MIXING ) == BST_CHECKED )
        dwSessionType = DVSESSIONTYPE_MIXING;
    else
        dwSessionType = DVSESSIONTYPE_FORWARDING;

    if( FAILED( g_hrDialog = g_pNetVoice->Init( hDlg, TRUE, FALSE,
                                                g_pDPServer, dwSessionType, 
                                                &g_guidDVSessionCT, NULL ) ) )
    {
        if( FAILED(g_hrDialog) ) 
            DXTRACE_ERR_MSGBOX( TEXT("Init"), g_hrDialog );

        EndDialog( hDlg, 0 );
        hr = g_hrDialog;
        goto LCleanup;
    }

    SetCursor( LoadCursor(NULL, IDC_ARROW) );
    g_bServerStarted = TRUE;
    SetDlgItemText( hDlg, IDC_STATUS, TEXT("Server started.") );

    hr = S_OK;

LCleanup:
    SAFE_RELEASE( pDP8AddrLocal );
    SAFE_RELEASE( pDP8AddrLocal );

    return hr;
}




//-----------------------------------------------------------------------------
// Name: StopServer
// Desc: 
//-----------------------------------------------------------------------------
VOID StopServer( HWND hDlg )
{
    if( hDlg )
        SetDlgItemText( hDlg, IDC_STATUS, TEXT("Stopping server...") );
    SetCursor( LoadCursor(NULL, IDC_WAIT) );

    // Disconnect from the DirectPlayVoice session, 
    // and destory it if we are the host player.
    SAFE_DELETE( g_pNetVoice ); 

    if( g_pDPServer )
    {
        g_pDPServer->Close(0);
        SAFE_RELEASE( g_pDPServer );
    }
    g_bServerStarted = FALSE;

    SetCursor( LoadCursor(NULL, IDC_ARROW) );
    if( hDlg )
        SetDlgItemText( hDlg, IDC_STATUS, TEXT("Server stopped.") );
}



    
//-----------------------------------------------------------------------------
// Name: DisplayPlayers
// Desc: 
//-----------------------------------------------------------------------------
VOID DisplayPlayers( HWND hDlg )
{
    HRESULT hr;
    DWORD dwNumPlayers = 0;
    DPNID* aPlayers = NULL;

    SendMessage( GetDlgItem(hDlg, IDC_PLAYER_LIST), LB_RESETCONTENT, 0, 0 );

    if( NULL == g_pDPServer )
        return;

    // Enumerate all the connected players 
    // A loop is needed here because a player could join between the call requesting
    // the size needed for the buffer and the call which performs the enumeration.
    for( ; ; )
    {
        hr = g_pDPServer->EnumPlayersAndGroups( aPlayers, &dwNumPlayers, DPNENUM_PLAYERS );
        if( SUCCEEDED(hr) )
            break;

        SAFE_DELETE_ARRAY( aPlayers );

        if( FAILED(hr) && hr != DPNERR_BUFFERTOOSMALL )
        {
            DXTRACE_ERR_MSGBOX( TEXT("EnumPlayersAndGroups"), hr );
            return;
        }

        aPlayers = new DPNID[ dwNumPlayers ];
        if( NULL == aPlayers )
        {
            DXTRACE_ERR_MSGBOX( TEXT("DisplayPlayers"), E_OUTOFMEMORY );
            return;
        }
    }

    // For each player, send a "create player" message to the new player
    for( DWORD i = 0; i<dwNumPlayers; i++ )
    {
        APP_PLAYER_INFO* pPlayerInfo = NULL;

        do
        {
            // Get the player context accosicated with this DPNID
            // Call GetPlayerContext() until it returns something other than DPNERR_NOTREADY
            // DPNERR_NOTREADY will be returned if the callback thread has not 
            // yet returned from DPN_MSGID_CREATE_PLAYER, which sets the player's context
            hr = g_pDPServer->GetPlayerContext( aPlayers[i], (LPVOID*) &pPlayerInfo, 0 );
        } 
        while( hr == DPNERR_NOTREADY ); 

        // Ignore this player if we can't get the context
        if( pPlayerInfo == NULL || FAILED(hr) )
            continue; 

        TCHAR strTemp[MAX_PATH];
        wsprintf( strTemp, TEXT("DPNID: 0x%0.8x (%s)"), pPlayerInfo->dpnidPlayer, pPlayerInfo->strPlayerName );
        SendMessage( GetDlgItem(hDlg, IDC_PLAYER_LIST), LB_ADDSTRING, 0, (LPARAM)strTemp );
    }

    SAFE_DELETE_ARRAY( aPlayers );
}



    
//-----------------------------------------------------------------------------
// Name: SendCreatePlayerMsg
// Desc: Send the target player a creation message about the player identified
//       in the APP_PLAYER_INFO struct.
//-----------------------------------------------------------------------------
HRESULT SendCreatePlayerMsg( APP_PLAYER_INFO* pPlayerAbout, DPNID dpnidTarget )
{
    GAMEMSG_CREATE_PLAYER msgCreatePlayer;
    msgCreatePlayer.dwType = GAME_MSGID_CREATE_PLAYER;
    msgCreatePlayer.dpnidPlayer = pPlayerAbout->dpnidPlayer;
    _tcscpy( msgCreatePlayer.strPlayerName, pPlayerAbout->strPlayerName );

    DPN_BUFFER_DESC bufferDesc;
    bufferDesc.dwBufferSize = sizeof(GAMEMSG_CREATE_PLAYER);
    bufferDesc.pBufferData  = (BYTE*) &msgCreatePlayer;

    // DirectPlay will tell via the message handler 
    // if there are any severe errors, so ignore any errors 
    DPNHANDLE hAsync;
    g_pDPServer->SendTo( dpnidTarget, &bufferDesc, 1,
                         0, NULL, &hAsync, DPNSEND_NOLOOPBACK | DPNSEND_GUARANTEED );

    return S_OK;
}



    
//-----------------------------------------------------------------------------
// Name: SendWorldStateToNewPlayer
// Desc: Send the world state to the new player.  For this sample, it is just
//       "create player" message for every connected player
//-----------------------------------------------------------------------------
HRESULT SendWorldStateToNewPlayer( DPNID dpnidNewPlayer )
{
    HRESULT hr;
    DWORD dwNumPlayers = 0;
    DPNID* aPlayers = NULL;

    // Tell this player the dpnid of itself
    GAMEMSG_SET_ID msgSetID;
    msgSetID.dwType      = GAME_MSGID_SET_ID;
    msgSetID.dpnidPlayer = dpnidNewPlayer;

    DPN_BUFFER_DESC bufferDesc;
    bufferDesc.dwBufferSize = sizeof(GAMEMSG_SET_ID);
    bufferDesc.pBufferData  = (BYTE*) &msgSetID;

    // DirectPlay will tell via the message handler 
    // if there are any severe errors, so ignore any errors 
    DPNHANDLE hAsync;
    g_pDPServer->SendTo( dpnidNewPlayer, &bufferDesc, 1,
                         0, NULL, &hAsync, DPNSEND_NOLOOPBACK | DPNSEND_GUARANTEED );

    // Enumerate all the connected players 
    // A loop is needed here because a player could join between the call requesting
    // the size needed for the buffer and the call which performs the enumeration.
    for( ; ; )
    {
        hr = g_pDPServer->EnumPlayersAndGroups( aPlayers, &dwNumPlayers, DPNENUM_PLAYERS );
        if( SUCCEEDED(hr) )
            break;

        SAFE_DELETE_ARRAY( aPlayers );

        if( FAILED(hr) && hr != DPNERR_BUFFERTOOSMALL )
            return DXTRACE_ERR_MSGBOX( TEXT("EnumPlayersAndGroups"), hr );

        aPlayers = new DPNID[ dwNumPlayers ];
        if( NULL == aPlayers )
            return DXTRACE_ERR_MSGBOX( TEXT("SendWorldStateToNewPlayer"), E_OUTOFMEMORY );
    }
    
    // For each player, send a "create player" message to the new player
    for( DWORD i = 0; i<dwNumPlayers; i++ )
    {
        APP_PLAYER_INFO* pPlayerInfo = NULL;

        // Don't send a create msg to the new player about itself.  This will 
        // be already done when we sent one to DPNID_ALL_PLAYERS_GROUP
        if( aPlayers[i] == dpnidNewPlayer )
            continue;  

        // Get the player context accosicated with this DPNID
        hr = g_pDPServer->GetPlayerContext( aPlayers[i], (LPVOID*) &pPlayerInfo, 0 );

        // Ignore this player if we can't get the context
        if( pPlayerInfo == NULL || FAILED(hr) )
            continue; 

        SendCreatePlayerMsg( pPlayerInfo, dpnidNewPlayer );
    }

    SAFE_DELETE_ARRAY( aPlayers );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SendDestroyPlayerMsgToAll
// Desc: 
//-----------------------------------------------------------------------------
HRESULT SendDestroyPlayerMsgToAll( APP_PLAYER_INFO* pPlayerInfo )
{
    GAMEMSG_DESTROY_PLAYER msgDestroyPlayer;
    msgDestroyPlayer.dwType = GAME_MSGID_DESTROY_PLAYER;
    msgDestroyPlayer.dpnidPlayer = pPlayerInfo->dpnidPlayer;

    DPN_BUFFER_DESC bufferDesc;
    bufferDesc.dwBufferSize = sizeof(GAMEMSG_DESTROY_PLAYER);
    bufferDesc.pBufferData  = (BYTE*) &msgDestroyPlayer;

    // DirectPlay will tell via the message handler 
    // if there are any severe errors, so ignore any errors 
    DPNHANDLE hAsync;
    g_pDPServer->SendTo( DPNID_ALL_PLAYERS_GROUP, &bufferDesc, 1,
                         0, NULL, &hAsync, DPNSEND_NOLOOPBACK | DPNSEND_GUARANTEED );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RefreshStatusBarText()
// Desc: Refresh the current status bar text based on connection state
//-----------------------------------------------------------------------------
HRESULT RefreshStatusBarText( BOOL bIsHosting )
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

    if( bIsHosting )
    {
        // Session has started
        _tcsncat( strStatus, TEXT("Hosting"), 1023 - lstrlen( strStatus ) );
        strStatus[ 1023 ] = 0;
        dwNumAddresses = 0;

        // Determine the buffer size needed to hold the addresses
        hr = g_pDPServer->GetLocalHostAddresses( rpAddresses, &dwNumAddresses, 0 );
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
        hr = g_pDPServer->GetLocalHostAddresses( rpAddresses, &dwNumAddresses, 0 );
        if( FAILED(hr) )
            goto LCleanReturn;  
    }
    else
    {
        // Server not started
        _tcsncat( strStatus, TEXT("Not connected"), 1023 - lstrlen( strStatus ) );
        strStatus[ 1023 ] = 0;
        dwNumAddresses = 0;
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
                TCHAR* strSpacing = ( i != 0 ) ? TEXT(", ") : TEXT(" at ");                      
        
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


