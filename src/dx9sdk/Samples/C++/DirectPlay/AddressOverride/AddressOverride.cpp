//----------------------------------------------------------------------------
// File: AddressOverride.cpp
//
// Desc: The main game file for the AddressOverride sample.  AddressOverride
//       shows how to override the DirectPlay addressing in order to host or 
//       connect to another session on the network.
// 
//       After a new game has started the sample begins a very simplistic 
//       game called "The Greeting Game".  When two or more players are connected
//       to the game, the players have the option of sending a single simple 
//       DirectPlay message to all of the other players. When this message
//       is receieved by the other players, they simply display a dialog box.
//
// Copyright (c) 1999-2002 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef STRICT
#define STRICT
#endif // !STRICT

#include <windows.h>
#include <commctrl.h>
#include <basetsd.h>
#include <dplay8.h>
#include <dplobby8.h>
#include <dpaddr.h>
#include <dxerr9.h>
#include <tchar.h>
#include <stdio.h>
#include <cguid.h>
#include "DXUtil.h"
#include "resource.h"

//-----------------------------------------------------------------------------
// Platform-dependent includes
//-----------------------------------------------------------------------------
#ifdef UNDER_CE
    #include <aygshell.h>
#endif // UNDER_CE


//-----------------------------------------------------------------------------
// Player reference count defines
//
// We don't need to use a global critical section (or InterlockedIncrement)
// because we use DirectPlay in DoWork mode, and don't start any extra threads
// or our own so we don't need to worry about being thread-safe.
//-----------------------------------------------------------------------------
#define PLAYER_ADDREF( pPlayerInfo )    if( pPlayerInfo ) pPlayerInfo->lRefCount++;
#define PLAYER_RELEASE( pPlayerInfo )   if( pPlayerInfo ) { pPlayerInfo->lRefCount--; if( pPlayerInfo->lRefCount <= 0 ) SAFE_DELETE( pPlayerInfo ); } pPlayerInfo = NULL;


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
#define DPLAY_SAMPLE_KEY                TEXT("Software\\Microsoft\\DirectX DirectPlay Samples")
#define MAX_PLAYER_NAME                 14
#define WM_APP_UPDATE_STATS             (WM_APP + 0)
#define WM_APP_DISPLAY_WAVE             (WM_APP + 1)
#define DOWORK_TIMESLICE                8 // let DirectPlay work for 8 ms at a time
#define ADDRESSOVERRIDE_PORT            2501

// This GUID allows DirectPlay to find other instances of the same game on
// the network.  So it must be unique for every game, and the same for 
// every instance of that game.  // {02AE835D-9179-485f-8343-901D327CE794}
GUID g_guidApp = { 0x2ae835d, 0x9179, 0x485f, { 0x83, 0x43, 0x90, 0x1d, 0x32, 0x7c, 0xe7, 0x94 } };

struct APP_PLAYER_INFO
{
    LONG  lRefCount;                        // Ref count so we can cleanup when all routines 
                                            // are done w/ this object
    DPNID dpnidPlayer;                      // DPNID of player
    TCHAR strPlayerName[MAX_PLAYER_NAME];   // Player name, this is a duplicate of DirectPlay's copy
};




//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8ThreadPool *   g_pThreadPool                 = NULL;    // DirectPlay threadpool object
IDirectPlay8Peer*          g_pDP                         = NULL;    // DirectPlay peer object


HINSTANCE                  g_hInst                       = NULL;    // HINST of app
HWND                       g_hDlg                        = NULL;    // HWND of main dialog
DPNID                      g_dpnidLocalPlayer            = 0;       // DPNID of local player
DPNID                      g_dpnidHostPlayer             = 0;       // DPNID of host player
DWORD                      g_dwNumberOfActivePlayers     = 0;       // Number of players currently in game
TCHAR                      g_strAppName[256]             = TEXT("AddressOverride");
TCHAR                      g_strLocalPlayerName[MAX_PATH];          // Local player name
TCHAR                      g_strSessionName[MAX_PATH];              // Session name
TCHAR                      g_strPreferredProvider[MAX_PATH];        // Provider string
TCHAR                      g_strRemoteHostname[MAX_PATH];           // TCP/IP remote host

BOOL                       g_bHostPlayer                 = FALSE;   // TRUE if local player is host
GUID*                      g_pCurSPGuid                  = NULL;    // Currently selected guid
DPNHANDLE                  g_hConnectAsyncOp             = NULL;    // Async handle for connecting to host


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
INT_PTR CALLBACK OverrideDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK GreetingDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT          InitDirectPlay();
HRESULT          OnInitOverrideDialog( HWND hDlg );
VOID             SetupAddressFields( HWND hDlg );
HRESULT          EnumServiceProviders( HWND hDlg );
HRESULT          EnumAdapters( HWND hDlg, GUID* pSPGuid );
HRESULT          LaunchMultiplayerGame( HWND hDlg );
HRESULT          WaveToAllPlayers();
VOID             AppendTextToEditControl( HWND hDlg, TCHAR* strNewLogLine );
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
    BOOL    bRunning = TRUE;
    MSG     Msg;

#ifdef UNDER_CE
    // This is needed along with a hidden control in the RC file to make the
    // soft keyboard pop up when the user selects an edit control.
    SHInitExtraControls();
#endif // UNDER_CE

    InitCommonControls();

    g_hInst = hInst; 

    // Read persistent state information from registry
    RegCreateKeyEx( HKEY_CURRENT_USER, DPLAY_SAMPLE_KEY, 0, NULL,
                    REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL, 
                    &hDPlaySampleRegKey, NULL );
    DXUtil_ReadStringRegKeyCch( hDPlaySampleRegKey, TEXT("Player Name"), 
                             g_strLocalPlayerName, MAX_PATH, TEXT("TestPlayer") );
    DXUtil_ReadStringRegKeyCch( hDPlaySampleRegKey, TEXT("Session Name"), 
                             g_strSessionName, MAX_PATH, TEXT("TestGame") );
    DXUtil_ReadStringRegKeyCch( hDPlaySampleRegKey, TEXT("Preferred Provider"), 
                             g_strPreferredProvider, MAX_PATH, 
                             TEXT("DirectPlay8 TCP/IP Service Provider") );
    DXUtil_ReadStringRegKeyCch( hDPlaySampleRegKey, TEXT("Remote Hostname"), 
                             g_strRemoteHostname, MAX_PATH, 
                             TEXT("localhost") );

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

    // Create the initial dialog.
    g_hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_ADDRESS_OVERRIDE), NULL, OverrideDlgProc);

    // Loop until its time to quit.
    while (bRunning)
    {
        // Retrieve any windows messages.
        while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
        {
            if (Msg.message == WM_QUIT)
            {
                // Quit the application.
                bRunning = FALSE;
                break;
            }

            if (! IsDialogMessage(g_hDlg, &Msg))
            {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            }
        }

        // Let DirectPlay process network events and call our message handler.
        g_pThreadPool->DoWork(DOWORK_TIMESLICE, 0);

        // Give up the remainder of this thread's quantum to avoid 100% CPU usage
        // in this sample.  Most games will not do this and instead run the
        // graphics loop as fast as possible.
        Sleep(1);
    }

    if( g_pDP )
    {
        g_pDP->Close(0);
        g_pDP->Release();
        g_pDP = NULL;
    }

    if( g_pThreadPool )
    {
        g_pThreadPool->Close(0);
        g_pThreadPool->Release();
        g_pThreadPool = NULL;
    }

    // Write information to the registry
    DXUtil_WriteStringRegKey( hDPlaySampleRegKey, TEXT("Player Name"), g_strLocalPlayerName );
    DXUtil_WriteStringRegKey( hDPlaySampleRegKey, TEXT("Session Name"), g_strSessionName );
    DXUtil_WriteStringRegKey( hDPlaySampleRegKey, TEXT("Preferred Provider"), g_strPreferredProvider );
    DXUtil_WriteStringRegKey( hDPlaySampleRegKey, TEXT("Remote Hostname"), g_strRemoteHostname );
    
    RegCloseKey( hDPlaySampleRegKey );
    CoUninitialize();

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: InitDirectPlay()
// Desc: Create and initialize DirectPlay threadpool and peer objects
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay()
{
    HRESULT hr;

    // Create IDirectPlay8ThreadPool
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8ThreadPool, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8ThreadPool, 
                                       (LPVOID*) &g_pThreadPool ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance ThreadPool"), hr );

    // Turn off parameter validation in release builds
#ifdef _DEBUG
    const DWORD dwInitFlags = 0;
#else
    const DWORD dwInitFlags = DPNINITIALIZE_DISABLEPARAMVAL;
#endif // _DEBUG

    // Init IDirectPlay8ThreadPool
    if( FAILED( hr = g_pThreadPool->Initialize( NULL, DirectPlayMessageHandler, dwInitFlags ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Initialize ThreadPool"), hr );

	// Put DirectPlay in "DoWork" mode
    if( FAILED( hr = g_pThreadPool->SetThreadCount( (DWORD) -1, 0, 0 ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("SetThreadCount"), hr );

    // Create IDirectPlay8Peer
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Peer, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Peer, 
                                       (LPVOID*) &g_pDP ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance Peer"), hr );

    // Init IDirectPlay8Peer
    if( FAILED( hr = g_pDP->Initialize( NULL, DirectPlayMessageHandler, dwInitFlags ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Initialize Peer"), hr );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: OverrideDlgProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK OverrideDlgProc( HWND hDlg, UINT msg, 
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

            if( FAILED( hr = OnInitOverrideDialog( hDlg ) ) )
            {
                DXTRACE_ERR_MSGBOX( TEXT("OnInitOverrideDialog"), hr );
                MessageBox( NULL, TEXT("Failed initializing dialog box. ")
                            TEXT("The sample will now quit."),
                            g_strAppName, MB_OK | MB_ICONERROR );
                EndDialog( hDlg, 0 );
                PostQuitMessage( 0 );
            }
            break;
        }

        case WM_COMMAND:
        {   
            switch( LOWORD(wParam) )
            {
                case IDC_HOST_SESSION:
                    SetupAddressFields( hDlg );
                    break;

                case IDC_SP_COMBO:
                {
                    // If the pSPGuid changed then re-enum the adapters, and
                    // update the address fields.
                    int nSPIndex = (int) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETCURSEL, 0, 0 );
                    GUID* pSPGuid = (GUID*) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETITEMDATA, nSPIndex, 0 );
                    if( pSPGuid != NULL && g_pCurSPGuid != pSPGuid )
                    {
                        g_pCurSPGuid = pSPGuid;
                        SetupAddressFields( hDlg );
                        EnumAdapters( hDlg, pSPGuid );
                    }
                    break;
                }

                case IDOK:
                    GetDlgItemText( hDlg, IDC_PLAYER_NAME, g_strLocalPlayerName, MAX_PATH );
                    GetDlgItemText( hDlg, IDC_SESSION_NAME, g_strSessionName, MAX_PATH );

                    // Disable the OK button while we work.
                    EnableWindow( GetDlgItem( hDlg, IDOK ), FALSE);

                    if( FAILED( hr = LaunchMultiplayerGame( hDlg ) ) )
                    {
                        DXTRACE_ERR_MSGBOX( TEXT("LaunchMultiplayerGame"), hr );
                        MessageBox( NULL, TEXT("Failed to launch game. "),
                                    g_strAppName, MB_OK | MB_ICONERROR );

                        // Renable the OK button.
                        EnableWindow( GetDlgItem( hDlg, IDOK ), TRUE);
                    }
                    break;

                case IDCANCEL:
                    EndDialog( hDlg, 0 );
                    PostQuitMessage( 0 );
                    break;
            }
            break;
        }

        case WM_DESTROY:
        {
            GetDlgItemText( hDlg, IDC_PLAYER_NAME, g_strLocalPlayerName, MAX_PATH );
            GetDlgItemText( hDlg, IDC_SESSION_NAME, g_strSessionName, MAX_PATH );

            int nIndex = (int) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETCURSEL, 0, 0 );
            SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETLBTEXT, nIndex, (LPARAM) g_strPreferredProvider );

            int nCount,i;
            nCount = (int)SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETCOUNT, 0, 0 );
            for( i=0; i<nCount; i++ )
            {
                GUID* pGuid = (LPGUID) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETITEMDATA, i, 0 );
                SAFE_DELETE( pGuid );
            }

            nCount = (int)SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_GETCOUNT, 0, 0 );
            for( i=0; i<nCount; i++ )
            {
                GUID* pGuid = (LPGUID) SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, 
                                                           CB_GETITEMDATA, i, 0 );
                SAFE_DELETE( pGuid );
            }            
            break;
        }
    }

    return FALSE; // Didn't handle message
}




//-----------------------------------------------------------------------------
// Name: OnInitOverrideDialog
// Desc: Handler for dialog initialization
//-----------------------------------------------------------------------------
HRESULT OnInitOverrideDialog( HWND hDlg )
{
    HRESULT hr;

    // Load and set the icon
    HICON hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE( IDI_MAIN ) );
    SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
    SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

    CheckDlgButton( hDlg, IDC_HOST_SESSION, BST_CHECKED );

    SetDlgItemText( hDlg, IDC_PLAYER_NAME, g_strLocalPlayerName );
    SetDlgItemText( hDlg, IDC_SESSION_NAME, g_strSessionName );

    if( FAILED( hr = EnumServiceProviders( hDlg ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("EnumServiceProviders"), hr );
    
    SetupAddressFields( hDlg );

    int nSPIndex = (int) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETCURSEL, 0, 0 );
    GUID* pSPGuid = (GUID*) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETITEMDATA, nSPIndex, 0 );
    if( pSPGuid != NULL )
    {
        g_pCurSPGuid = pSPGuid;
        EnumAdapters( hDlg, pSPGuid );
    }

    return S_OK;
}





//-----------------------------------------------------------------------------
// Name: SetupAddressFields
// Desc: Based on the SP selected, update the address UI 
//-----------------------------------------------------------------------------
VOID SetupAddressFields( HWND hDlg )
{
    int nSPIndex = (int) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETCURSEL, 0, 0 );
    if( nSPIndex == LB_ERR )
        return;
    GUID* pGuid = (GUID*) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETITEMDATA, nSPIndex, 0 );
    if( pGuid == NULL )
        return;

    BOOL bHosting = IsDlgButtonChecked( hDlg, IDC_HOST_SESSION );

    if( *pGuid == CLSID_DP8SP_TCPIP ||
        *pGuid == CLSID_DP8SP_IPX )
    {
        TCHAR strPort[40];
        _itot( ADDRESSOVERRIDE_PORT, strPort, 10 );

        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE2), TRUE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE2, strPort );
        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE2_TEXT), TRUE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE2_TEXT, TEXT("Port:") );

        if( bHosting )
        {
            EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE1), FALSE );
            SetDlgItemText( hDlg, IDC_ADDRESS_LINE1, TEXT("") );
            EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE1_TEXT), FALSE );
            SetDlgItemText( hDlg, IDC_ADDRESS_LINE1_TEXT, TEXT("") );
        }
        else
        {
            EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE1), TRUE );
            SetDlgItemText( hDlg, IDC_ADDRESS_LINE1, TEXT("") );
            EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE1_TEXT), TRUE );
            SetDlgItemText( hDlg, IDC_ADDRESS_LINE1_TEXT, TEXT("Hostname:") );

            // TCP/IP only: As a convenience, we store the most recently used
            // remote IP in the registry, and should populate that field
            // with the stored value. Default is "localhost".
            if( *pGuid == CLSID_DP8SP_TCPIP )
                SetDlgItemText( hDlg, IDC_ADDRESS_LINE1, g_strRemoteHostname );

        }
    }
    else if( *pGuid == CLSID_DP8SP_MODEM )
    {
        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE1), TRUE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE1, TEXT("") );
        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE1_TEXT), TRUE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE1_TEXT, TEXT("Phone Number:") );

        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE2), FALSE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE2, TEXT("") );
        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE2_TEXT), FALSE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE2_TEXT, TEXT("") );
    }
    else 
    {
        // CLSID_DP8SP_SERIAL or unknown so disable all the address lines.
        // This sample does not support any other type of service provider.
        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE1), FALSE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE1, TEXT("") );
        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE1_TEXT), FALSE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE1_TEXT, TEXT("") );
        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE2), FALSE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE2, TEXT("") );
        EnableWindow( GetDlgItem(hDlg, IDC_ADDRESS_LINE2_TEXT), FALSE );
        SetDlgItemText( hDlg, IDC_ADDRESS_LINE2_TEXT, TEXT("") );
    }
}




//-----------------------------------------------------------------------------
// Name: EnumServiceProviders()
// Desc: Fills the combobox with service providers
//-----------------------------------------------------------------------------
HRESULT EnumServiceProviders( HWND hDlg )
{
    DPN_SERVICE_PROVIDER_INFO* pdnSPInfo = NULL;
    HRESULT hr;
    DWORD   dwItems = 0;
    DWORD   dwSize  = 0;
    int     nIndex;

    // Enumerate all DirectPlay service providers, and store them in the listbox
    hr = g_pDP->EnumServiceProviders( NULL, NULL, pdnSPInfo, &dwSize,
                                      &dwItems, 0 );
    if( hr != DPNERR_BUFFERTOOSMALL )
    {
        DXTRACE_ERR_MSGBOX( TEXT("EnumServiceProviders"), hr );
        goto LCleanReturn;
    }

    // Allocate space for service provider info
    pdnSPInfo = (DPN_SERVICE_PROVIDER_INFO*) new BYTE[dwSize];
    if( NULL == pdnSPInfo )
    {
        hr = E_OUTOFMEMORY;
        DXTRACE_ERR_MSGBOX( TEXT("EnumServiceProviders"), hr );
        goto LCleanReturn;
    }

    // Enumerate service providers
    if( FAILED( hr = g_pDP->EnumServiceProviders( NULL, NULL, pdnSPInfo,
                                                  &dwSize, &dwItems, 0 ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("EnumServiceProviders"), hr );
        goto LCleanReturn;
    }

    // Copy pointer for enumeration
    DPN_SERVICE_PROVIDER_INFO* pdnSPInfoEnum;
    pdnSPInfoEnum = pdnSPInfo;

    // For each detected service provider, add an item to the list
    DWORD i;
    for ( i = 0; i < dwItems; i++ )
    {
        TCHAR strName[MAX_PATH];
        DXUtil_ConvertWideStringToGenericCch( strName, pdnSPInfoEnum->pwszName, MAX_PATH );

        // Found a service provider, so put it in the listbox
        nIndex = (int)SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_ADDSTRING, 
                                              0, (LPARAM) strName );

        // Store pointer to GUID in listbox
        GUID* pGuid = new GUID;
        if( NULL == pGuid )
        {
            hr = E_OUTOFMEMORY;
            DXTRACE_ERR_MSGBOX( TEXT("EnumServiceProviders"), hr );
            goto LCleanReturn;
        }

        // Fill in the GUID structure
        memcpy( pGuid, &pdnSPInfoEnum->guid, sizeof(GUID) );
        SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_SETITEMDATA, 
                            nIndex, (LPARAM) pGuid );

        // Advance to the next service provider
        pdnSPInfoEnum++;
    }

    
    // Try to select the default preferred provider
    nIndex = (int)SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_FINDSTRINGEXACT, (WPARAM)-1,
                                      (LPARAM)g_strPreferredProvider );
    if( nIndex != LB_ERR )
        SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_SETCURSEL, nIndex, 0 );
    else
        SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_SETCURSEL, 0, 0 );

    hr = S_OK;

LCleanReturn:
    SAFE_DELETE_ARRAY( pdnSPInfo );

    return hr;
}




//-----------------------------------------------------------------------------
// Name: EnumAdapters()
// Desc: Fills the combobox with adapters for a specified SP
//-----------------------------------------------------------------------------
HRESULT EnumAdapters( HWND hDlg, GUID* pSPGuid )
{
    DPN_SERVICE_PROVIDER_INFO* pdnSPInfo = NULL;
    TCHAR   strName[MAX_PATH];
    HRESULT hr;
    DWORD   dwItems = 0;
    DWORD   dwSize  = 0;
    int     nIndex;
    int     nAllAdaptersIndex = 0;

    SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_RESETCONTENT, 0, 0 );

    // Enumerate all adapters for the given service provider, and store them 
    // in the listbox
    hr = g_pDP->EnumServiceProviders( pSPGuid, NULL, pdnSPInfo, &dwSize,
                                      &dwItems, 0 );
    if( hr != DPNERR_BUFFERTOOSMALL )
    {
        DXTRACE_ERR_MSGBOX( TEXT("EnumAdapters"), hr );
        goto LCleanReturn;
    }

    // Allocate space for adapter info
    pdnSPInfo = (DPN_SERVICE_PROVIDER_INFO*) new BYTE[dwSize];
    if( NULL == pdnSPInfo )
    {
        hr = E_OUTOFMEMORY;
        DXTRACE_ERR_MSGBOX( TEXT("EnumAdapters"), hr );
        goto LCleanReturn;
    }

    // Enumerate adapters
    if( FAILED( hr = g_pDP->EnumServiceProviders( pSPGuid, NULL, pdnSPInfo,
                                                  &dwSize, &dwItems, 0 ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("EnumAdapters"), hr );
        goto LCleanReturn;
    }

    // Copy the pointer for enumeration
    DPN_SERVICE_PROVIDER_INFO* pdnSPInfoEnum;
    pdnSPInfoEnum = pdnSPInfo;

    // For each detected adapter, add an item to the listbox
    DWORD i;
    for ( i = 0; i < dwItems; i++ )
    {
        DXUtil_ConvertWideStringToGenericCch( strName, pdnSPInfoEnum->pwszName, MAX_PATH );

        // Found an adapter, so put it in the listbox
        nIndex = (int)SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_ADDSTRING, 
                                          0, (LPARAM) strName );

        // Store pointer to GUID in listbox
        GUID* pGuid = new GUID;
        if( NULL == pGuid )
        {
            hr = E_OUTOFMEMORY;
            DXTRACE_ERR_MSGBOX( TEXT("EnumAdapters"), hr );
            goto LCleanReturn;
        }

        // Fill in the GUID structure
        memcpy( pGuid, &pdnSPInfoEnum->guid, sizeof(GUID) );

        SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_SETITEMDATA, 
                            nIndex, (LPARAM) pGuid );

        // Advance to the next adapter
        pdnSPInfoEnum++;
    }

    // Determine if this SP supports all-adapters, that is, not specifying
    // a device GUID and using all devices simultaneously.
    DPN_SP_CAPS dpnspCaps;
    memset(&dpnspCaps, 0, sizeof(DPN_SP_CAPS));
	dpnspCaps.dwSize = sizeof(DPN_SP_CAPS);
    hr = g_pDP->GetSPCaps(pSPGuid, &dpnspCaps, 0);
    if ( FAILED( hr ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("GetSPCaps"), hr );
        goto LCleanReturn;
    }
    if ( dpnspCaps.dwFlags & DPNSPCAPS_SUPPORTSALLADAPTERS )
    {
        // Add an "All Adapters" special item to the listbox
        nIndex = (int)SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_ADDSTRING, 
                                          0, (LPARAM) TEXT("* All Adapters *") );

        nAllAdaptersIndex = nIndex;

        // Store pointer to a placeholder GUID in listbox
        GUID* pGuid = new GUID;
        if( NULL == pGuid )
        {
            hr = E_OUTOFMEMORY;
            DXTRACE_ERR_MSGBOX( TEXT("EnumAdapters"), hr );
            goto LCleanReturn;
        }

        // Fill the GUID structure with all 0s (i.e. GUID_NULL)
        memset( pGuid, 0, sizeof(GUID) );

        SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_SETITEMDATA, 
                            nIndex, (LPARAM) pGuid );
    }

    // Select the first item, or "All Adapters" if the SP supports it.
    SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_SETCURSEL, nAllAdaptersIndex, 0 );
    hr = S_OK;

LCleanReturn:
    SAFE_DELETE_ARRAY( pdnSPInfo );

    return hr;
}




//-----------------------------------------------------------------------------
// Name: LaunchMultiplayerGame
// Desc: Use the settings in the configuration dialog to launch the session
//-----------------------------------------------------------------------------
HRESULT LaunchMultiplayerGame( HWND hDlg ) 
{
    HRESULT hr          = S_OK;
    BOOL    bOkToQuery  = FALSE;

    IDirectPlay8Address* pHostAddress     = NULL;
    IDirectPlay8Address* pDeviceAddress   = NULL;

    // Grab settings from the provided dialog
    int   nSPIndex  = (int)   SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETCURSEL,   0,        0 );
    GUID* pSPGuid   = (GUID*) SendDlgItemMessage( hDlg, IDC_SP_COMBO, CB_GETITEMDATA, nSPIndex, 0 );

    g_bHostPlayer = IsDlgButtonChecked( hDlg, IDC_HOST_SESSION );
    
    // If not the host
    if( !g_bHostPlayer )
    {
        // Create a host address if connecting to a host, 
        // otherwise keep it as NULL
        if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL, CLSCTX_INPROC_SERVER, 
                                           IID_IDirectPlay8Address, (void **) &pHostAddress ) ) )
        {
            DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
            goto LCleanReturn;
        }

        // Set the SP to pHostAddress
        if( FAILED( hr = pHostAddress->SetSP( pSPGuid ) ) )
        {
            DXTRACE_ERR_MSGBOX( TEXT("SetSP"), hr );
            goto LCleanReturn;
        }
    }

    // Create a device address to specify which device we are using 
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL, CLSCTX_INPROC_SERVER, 
                                       IID_IDirectPlay8Address, (void **) &pDeviceAddress ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
        goto LCleanReturn;
    }

    // Set the SP to pDeviceAddress
    if( FAILED( hr = pDeviceAddress->SetSP( pSPGuid ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("SetSP"), hr );
        goto LCleanReturn;
    }

    // Add the adapter to pDeviceAddress
    int nAdapterIndex;
    nAdapterIndex = (int) SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_GETCURSEL, 0, 0 );

    if( nAdapterIndex != CB_ERR )
    {
        // Get the GUID associated with the selected list item
        GUID* pAdapterGuid = (GUID*) SendDlgItemMessage( hDlg, IDC_ADAPTER_COMBO, CB_GETITEMDATA, 
                                                         nAdapterIndex, 0 );
        // Add the device GUID, unless its the special "All Adapters" placeholder
        if ( *pAdapterGuid != GUID_NULL )
        {
            if( FAILED( hr = pDeviceAddress->SetDevice( pAdapterGuid ) ) )
            {
                DXTRACE_ERR_MSGBOX( TEXT("SetDevice"), hr );
                goto LCleanReturn;
            }
        }
    }

    // --------------------------------
    // Service Provider: TCP/IP, IPX
    // --------------------------------
    if( *pSPGuid == CLSID_DP8SP_TCPIP ||
        *pSPGuid == CLSID_DP8SP_IPX )
    {
        TCHAR strHostname[MAX_PATH];
        TCHAR strPort[MAX_PATH];

        GetDlgItemText( hDlg, IDC_ADDRESS_LINE1, strHostname, MAX_PATH );
        GetDlgItemText( hDlg, IDC_ADDRESS_LINE2, strPort, MAX_PATH );

        // TCP/IP Only: As a convenience for the user, we store the
        // most recently used remote hostname in the registry when
        // the program exits.
        if( *pSPGuid == CLSID_DP8SP_TCPIP )
        {
            _tcsncpy( g_strRemoteHostname, strHostname, MAX_PATH );
            g_strRemoteHostname[MAX_PATH-1] = 0;
        }

        if( g_bHostPlayer )
        {
            if( _tcslen( strPort ) > 0 )
            {
                // Add the port to pDeviceAddress
                DWORD dwPort = _ttoi( strPort );
                if( FAILED( hr = pDeviceAddress->AddComponent( DPNA_KEY_PORT, 
                                                               &dwPort, sizeof(dwPort),
                                                               DPNA_DATATYPE_DWORD ) ) )
                {
                    DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
                    goto LCleanReturn;
                }
            }
        }
        else
        {
            // Add the hostname to pHostAddress
            if( _tcslen( strHostname ) > 0 )
            {
                WCHAR wstrHostname[MAX_PATH];
                DXUtil_ConvertGenericStringToWideCch( wstrHostname, strHostname, MAX_PATH );

                if( FAILED( hr = pHostAddress->AddComponent( DPNA_KEY_HOSTNAME, 
                                                             wstrHostname, (DWORD) (wcslen(wstrHostname)+1)*sizeof(WCHAR), 
                                                             DPNA_DATATYPE_STRING ) ) )
                {
                    DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
                    goto LCleanReturn;
                }
            }

            if( _tcslen( strPort ) > 0 )
            {
                // Add the port to pHostAddress
                DWORD dwPort = _ttoi( strPort );
                if( FAILED( hr = pHostAddress->AddComponent( DPNA_KEY_PORT, 
                                                             &dwPort, sizeof(dwPort),
                                                             DPNA_DATATYPE_DWORD ) ) )
                {
                    DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
                    goto LCleanReturn;
                }
            }
        }
    }
    // --------------------------------
    // Service Provider: Modem
    // --------------------------------
    else if( *pSPGuid == CLSID_DP8SP_MODEM )
    {
        TCHAR strPhone[MAX_PATH];
        GetDlgItemText( hDlg, IDC_ADDRESS_LINE1, strPhone, MAX_PATH );

        if( !g_bHostPlayer )
        {
            // Add the phonenumber to pHostAddress
            if( _tcslen( strPhone ) > 0 )
            {
                WCHAR wstrPhone[MAX_PATH];
                DXUtil_ConvertGenericStringToWideCch( wstrPhone, strPhone, MAX_PATH );

                if( FAILED( hr = pHostAddress->AddComponent( DPNA_KEY_PHONENUMBER, 
                                                             wstrPhone, (DWORD) (wcslen(wstrPhone)+1)*sizeof(WCHAR), 
                                                             DPNA_DATATYPE_STRING ) ) )
                {
                    DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
                    goto LCleanReturn;
                }
            }
        }
    }
    // --------------------------------
    // Service Provider: Serial Port
    // --------------------------------
    else if( *pSPGuid == CLSID_DP8SP_SERIAL )
    {
        // This simple client doesn't have UI to query for the various
        // fields needed for the serial.  So we just let DPlay popup a dialog
        // to ask the user which settings are needed.
        bOkToQuery = TRUE;
    }
    // --------------------------------
    // Service Provider: Unknown
    // --------------------------------
    else
    {
        // Unknown SP, so leave as is
        bOkToQuery = TRUE;
    }


    // Prepare local player name 
    WCHAR wszPeerName[MAX_PATH];
    DXUtil_ConvertGenericStringToWideCch( wszPeerName, g_strLocalPlayerName, MAX_PATH );

    // Fill in player info structure
    DPN_PLAYER_INFO dpPlayerInfo;
    ZeroMemory( &dpPlayerInfo, sizeof(DPN_PLAYER_INFO) );
    dpPlayerInfo.dwSize       = sizeof(DPN_PLAYER_INFO);
    dpPlayerInfo.dwInfoFlags  = DPNINFO_NAME;
    dpPlayerInfo.pwszName     = wszPeerName;
  
    // Set the peer info, and use the DPNOP_SYNC since by default this
    // is an async call.  If it is not DPNOP_SYNC, then the peer info may not
    // be set by the time we call Connect() below.  
    if( FAILED( hr = g_pDP->SetPeerInfo( &dpPlayerInfo, NULL, NULL, DPNOP_SYNC ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("SetPeerInfo"), hr );
        goto LCleanReturn;
    }

    // Fill in application description structure
    DPN_APPLICATION_DESC dpnAppDesc;
    ZeroMemory( &dpnAppDesc, sizeof(DPN_APPLICATION_DESC) );
    dpnAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpnAppDesc.dwFlags = DPNSESSION_NODPNSVR;
    dpnAppDesc.guidApplication = g_guidApp;
    dpnAppDesc.guidInstance    = GUID_NULL;
    dpnAppDesc.pwszSessionName = NULL;


    //---------------------------------
    // If we are hosting...
    //---------------------------------
    if( g_bHostPlayer )
    {
        // Set the dpnAppDesc.pwszSessionName
        TCHAR strSessionName[MAX_PATH];
        GetDlgItemText( hDlg, IDC_SESSION_NAME, strSessionName, MAX_PATH );
        
        if( _tcslen( strSessionName ) > 0 )
        {
            WCHAR wstrSessionName[ MAX_PATH ] = {0};
            DXUtil_ConvertGenericStringToWideCch( wstrSessionName, strSessionName, MAX_PATH );
            dpnAppDesc.pwszSessionName = wstrSessionName;
        }

        DWORD dwHostFlags = 0;
        if (bOkToQuery)
        {
            dwHostFlags |= DPNHOST_OKTOQUERYFORADDRESSING;
        }

        // Host a game as described by pSettings
        hr = g_pDP->Host( &dpnAppDesc,          // the application desc
                          &pDeviceAddress,      // array of addresses of the local devices used to connect to the host
                          1,                    // number in array
                          NULL, NULL,           // DPN_SECURITY_DESC, DPN_SECURITY_CREDENTIALS
                          NULL,                 // player context
                          dwHostFlags );        // flags
        if( FAILED(hr) )
        {
            DXTRACE_ERR_MSGBOX( TEXT("Host"), hr );  
            goto LCleanReturn;
        }

        // Close the existing dialog and create the "in-game" dialog.
        EndDialog( g_hDlg, 0 );
        g_hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_MAIN_GAME), NULL, GreetingDlgProc);
    }
    //---------------------------------
    // If we are connecting...
    //---------------------------------
    else
    {
        // We could enumerate the host first, but since we are overriding the defaults
        // with a specific address, we are probably expecting the host to be at that
        // address.  Connect directly.

        DWORD dwConnectFlags = 0;
        if (bOkToQuery)
        {
            dwConnectFlags |= DPNCONNECT_OKTOQUERYFORADDRESSING;
        }

        // Enumerate all the active DirectPlay games on the selected connection
        hr = g_pDP->Connect( &dpnAppDesc,            // application description
                             pHostAddress,           // host address
                             pDeviceAddress,         // device address
                             NULL,                   // security desc
                             NULL,                   // credentials
                             NULL,                   // user connect data
                             0,                      // user connect data size
                             NULL,                   // player context
                             NULL,                   // async op user context
                             &g_hConnectAsyncOp,     // place to store async op handle
                             dwConnectFlags );       // flags
        if( FAILED(hr) )
        {
            DXTRACE_ERR_MSGBOX( TEXT("Connect"), hr );
            goto LCleanReturn;
        }
    }

    hr = S_OK;

LCleanReturn:
    // Cleanup the addresses
    SAFE_RELEASE( pHostAddress );
    SAFE_RELEASE( pDeviceAddress );
    
    return hr;
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
            HICON hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            if( g_bHostPlayer )
                SetWindowText( hDlg, TEXT("AddressOverride (Host)") );
            else
                SetWindowText( hDlg, TEXT("AddressOverride") );

            // Display local player's name
            SetDlgItemText( hDlg, IDC_PLAYER_NAME, g_strLocalPlayerName );

            PostMessage( hDlg, WM_APP_UPDATE_STATS, 0, 0 );
            break;
        }

        case WM_APP_UPDATE_STATS:
        {
            // Update the number of players in the game
            TCHAR strNumberPlayers[32];

            wsprintf( strNumberPlayers, TEXT("%u"), g_dwNumberOfActivePlayers );
            SetDlgItemText( hDlg, IDC_NUM_PLAYERS, strNumberPlayers );

            // Update the status bar text
            RefreshStatusBarText( g_dpnidLocalPlayer, g_dpnidHostPlayer );
            break;
        }

        case WM_APP_DISPLAY_WAVE:
        {
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) wParam;
            
        
            // Make wave message and display it.
            TCHAR szWaveMessage[MAX_PATH];
            _sntprintf( szWaveMessage, MAX_PATH-1, TEXT("%s just waved at you, %s!\r\n"), 
                        pPlayerInfo->strPlayerName, g_strLocalPlayerName );
            szWaveMessage[ MAX_PATH-1 ] = 0;

            PLAYER_RELEASE( pPlayerInfo );  // Release player and cleanup if needed

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
                        EndDialog( hDlg, 0 );
                        PostQuitMessage( 0 );
                    }

                    return TRUE;

                case IDCANCEL:
                    EndDialog( hDlg, 0 );
                    PostQuitMessage( 0 );
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
//       DirectPlay as needed.  Since we are using DirectPlay in "DoWork" mode
//       and we only use a single thread, we do not have to worry about thread
//       synchronization problems
//-----------------------------------------------------------------------------
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, 
                                         DWORD dwMessageId, 
                                         PVOID pMsgBuffer )
{
    switch( dwMessageId )
    {
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
            pPlayerInfo->lRefCount   = 1; // initial reference, "transferred" to DPlay and removed in DESTROY_PLAYER
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
                                                       pdpPlayerInfo->pwszName, MAX_PLAYER_NAME );    
                                                       
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
            // UI.
            g_dwNumberOfActivePlayers++;
            if( g_hDlg != NULL )
                PostMessage( g_hDlg, WM_APP_UPDATE_STATS, 0, 0 );

            break;
        }

        case DPN_MSGID_DESTROY_PLAYER:
        {
            PDPNMSG_DESTROY_PLAYER pDestroyPlayerMsg;
            pDestroyPlayerMsg = (PDPNMSG_DESTROY_PLAYER)pMsgBuffer;
            APP_PLAYER_INFO* pPlayerInfo = (APP_PLAYER_INFO*) pDestroyPlayerMsg->pvPlayerContext;

            PLAYER_RELEASE( pPlayerInfo );  // Release player and cleanup if needed

            // Update the number of active players, and 
            // post a message to the dialog thread to update the 
            // UI.
            g_dwNumberOfActivePlayers--;
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
            PostQuitMessage( 0 );
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
                // This message is sent when a player has waved to us, so post a message to
                // update the UI.  We could make the update here, though generally we want
                // to spend as little time in DirectPlay callbacks as possible.  In this
                // example, we choose to queue it for the window message handler.
                //
                // Add a reference to the player object in case DPlay tells us that the
                // player is destroyed before we get a chance to process the window message.
                PLAYER_ADDREF( pPlayerInfo );
                PostMessage( g_hDlg, WM_APP_DISPLAY_WAVE, (WPARAM) pPlayerInfo, 0 );
            }
            break;
        }

        case DPN_MSGID_CONNECT_COMPLETE:
        {
            PDPNMSG_CONNECT_COMPLETE pConnectCompleteMsg;
            pConnectCompleteMsg = (PDPNMSG_CONNECT_COMPLETE)pMsgBuffer;

            g_hConnectAsyncOp = NULL;
            if( FAILED( pConnectCompleteMsg->hResultCode ) )
            {
                // The connect failed.  Generally we don't want to display dialog boxes and
                // block a DirectPlay message handler callback, but we are doing it in this
                // sample for simplicity.
                DXTRACE_ERR_MSGBOX( TEXT("DPN_MSGID_CONNECT_COMPLETE"), pConnectCompleteMsg->hResultCode );
                MessageBox( g_hDlg, TEXT("Unable to join game."),
                            g_strAppName, MB_OK | MB_ICONERROR );

                // Re-enable the OK button.
                EnableWindow( GetDlgItem( g_hDlg, IDOK ), TRUE);
                break;
            }

            // Otherwise, the connect succeeded.  Create the "in-game" dialog.
            EndDialog( g_hDlg, 0 );
            g_hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_MAIN_GAME), NULL, GreetingDlgProc);
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
    // the players or inform the player that there is no one around.
    if( g_dwNumberOfActivePlayers <= 1 )
    {
        MessageBox( g_hDlg, TEXT("No other players are around to see you wave!"), 
                    TEXT("AddressOverride"), MB_OK );
    }
    else
    {
        // Send a message to all of the players
        GAMEMSG_GENERIC msgWave;
        msgWave.dwType = GAME_MSGID_WAVE;

        DPN_BUFFER_DESC bufferDesc;
        bufferDesc.dwBufferSize = sizeof(GAMEMSG_GENERIC);
        bufferDesc.pBufferData  = (BYTE*) &msgWave;

        // Group sends with valid parameters will always succeed unless no player
        // received the message, so ignore any errors and just let the message
        // handler deal with things like players going away.
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