//----------------------------------------------------------------------------
// File: HostMigration.cpp
//
// Desc: This tutorials adds a host migration option to the session creation,
//       and tracks connection status using the DirectPlay callback function.
//
// Copyright (c) 2000-2001 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#include <windows.h>
#include <commctrl.h>
#include <dplay8.h>
#include <stdio.h>
#include <tchar.h>
#include "dxutil.h"
#include "resource.h"

//-----------------------------------------------------------------------------
// Platform-dependent includes
//-----------------------------------------------------------------------------
#ifdef UNDER_CE
    #include <aygshell.h>
#endif // UNDER_CE


//-----------------------------------------------------------------------------
// Global constants
//-----------------------------------------------------------------------------
const DWORD TUT06_HOSTMIGRATION_PORT = 2606; // The default port number



//-----------------------------------------------------------------------------
// App specific structures 
//-----------------------------------------------------------------------------
struct HOST_NODE
{
    DPN_APPLICATION_DESC*   pAppDesc;
    IDirectPlay8Address*    pHostAddress;
    TCHAR*                  strSessionName;

    HOST_NODE*             pNext;
};


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8Peer*    g_pDP              = NULL;    // DirectPlay peer object
IDirectPlay8Address* g_pDeviceAddress   = NULL;    // Local address
IDirectPlay8Address* g_pHostAddress     = NULL;    // Remote host address
DPNID                g_dpnidLocalPlayer = 0;       // Local player ID
HWND                 g_hDlg             = NULL;    // UI dialog handle
HINSTANCE            g_hInst            = NULL;    // Program instance handle
bool                 g_bMigrateHost     = FALSE;   // Host migration option
bool                 g_bHosting         = FALSE;   // Host connection status
bool                 g_bConnected       = FALSE;   // Peer connection status
int                  g_iSelectedHost    = 0;       // For connection dialog
TCHAR                g_strSession[128]  = {0};     // Connected session name 
HOST_NODE*           g_pHostList        = NULL;    // List of detected hosts
CRITICAL_SECTION     g_csHostList;                 // For synchronization
DWORD                g_dwLocalPort      = TUT06_HOSTMIGRATION_PORT; // Host port
DWORD                g_dwRemotePort     = TUT06_HOSTMIGRATION_PORT; // Connect port


// This GUID allows DirectPlay to find other instances of the same game on
// the network.  So it must be unique for every game, and the same for 
// every instance of that game.  // {2C6FEE8B-3088-4b74-B38F-A16D02DAD246}
GUID g_guidApp = { 0x2c6fee8b, 0x3088, 0x4b74, { 0xb3, 0x8f, 0xa1, 0x6d, 0x2, 0xda, 0xd2, 0x46 } };

// Load the application window title into this global from the string table.
// Since the Pocket PC doesn't support multiple instances, the title text
// will be used to find currently active instances.
TCHAR g_strAppTitle[MAX_PATH] = {0};


//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay();
HRESULT CreateDeviceAddress( bool bIsHost );
HRESULT HostSession();
HRESULT ConnectToSession();
HRESULT Disconnect();
HRESULT EnumDirectPlayHosts( HWND hDlg );
HRESULT CreateHostAddress( TCHAR* strHost );
HRESULT SendDirectPlayMessage();
BOOL    IsServiceProviderValid( const GUID* pGuidSP );
void    OutputError( TCHAR* str, HRESULT hr = 0 );
void    CleanupDirectPlay();
void    ClearHostList();
void    OutputHostList( HWND hDlg );
void    UpdateUI();
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK HostDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK ConnectDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT WINAPI DirectPlayMessageHandler(PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer);




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application. 
//-----------------------------------------------------------------------------
INT APIENTRY _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, 
                        LPTSTR pCmdLine, INT nCmdShow )
{
    // Load application title
    LoadString( hInst, IDS_APP_TITLE, g_strAppTitle, MAX_PATH );

//------------------------------------
#if defined(WIN32_PLATFORM_PSPC) && (_WIN32_WCE >= 300)               
    // Pocket PC applications must have only one running instance
    HWND    hWndFound = NULL;
    
    // Look for instance of dialog-based application with same title
    if( g_strAppTitle )
        hWndFound = FindWindow( TEXT("Dialog"), g_strAppTitle );

    if( hWndFound )
    {
        SetForegroundWindow( hWndFound );
        return FALSE;
    }

    // This is needed along with a hidden control in the RC file to make the
    // soft keyboard pop up when the user selects an edit control.
    SHInitExtraControls();
#endif // Pocket PC       * POCKET PC *
//-------------------------------------

    HRESULT hr = S_OK;
    g_hInst = hInst;

    InitCommonControls();

    // Init COM so we can use CoCreateInstance
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // Init the DirectPlay system
    if( FAILED( hr = InitDirectPlay() ) )
    {
        OutputError( TEXT("Failed to initialize DirectPlay.")
                     TEXT("\n\nThe sample will now exit.") );
        goto LCleanup;
    }

    // Create the mutex object
    InitializeCriticalSection(&g_csHostList);

    // Launch the user interface. This method will block until an error
    // or the user exits.
    DialogBox( hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc );
    
LCleanup:
    // Cleanup DirectPlay
    CleanupDirectPlay();

    // Cleanup COM
    CoUninitialize(); 

    return 0;
}




//-----------------------------------------------------------------------------
// Name: MainDlgProc
// Desc: Main dialog proceedure. 
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_INITDIALOG:
            // Set title bar name
            SendMessage( hDlg, WM_SETTEXT, 0, (LPARAM) g_strAppTitle );
//-------------------------------------
#if defined(WIN32_PLATFORM_PSPC) && (_WIN32_WCE >= 300)

            // Full-screen dialog code for Pocket PC only         
            SHINITDLGINFO   shidi;
            memset( &shidi, 0, sizeof(SHINITDLGINFO) );
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
            shidi.hDlg = hDlg;

            SHInitDialog( &shidi );

            SHMENUBARINFO mbi;
	        memset(&mbi, 0, sizeof(SHMENUBARINFO));
	        mbi.cbSize     = sizeof(SHMENUBARINFO);
	        mbi.hwndParent = hDlg;
            mbi.dwFlags = SHCMBF_EMPTYBAR;
            
	        SHCreateMenuBar(&mbi); 
#endif //Pocket PC        * POCKET PC *
//-------------------------------------
            HICON hIcon;
            g_hDlg = hDlg;

            // Load and set the icon
            hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            UpdateUI();
            return TRUE;

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDC_HOST:
                    if( g_bHosting || g_bConnected )
                    {
                        if( FAILED( Disconnect() ) )
                        {
                            OutputError( TEXT("Failed to re-initialize DirectPlay.")
                                         TEXT("\n\nThe sample will now exit.") );
                            EndDialog( hDlg, 0 );
                        }
                    }
                    else
                        HostSession();
                    return TRUE;

                case IDC_CONNECT:
                    ConnectToSession();
                    return TRUE;

                case IDC_SEND:
                    SendDirectPlayMessage();
                    return TRUE;

                case IDOK:
                case IDCANCEL:
                    EndDialog( hDlg, 0 );
                    return TRUE;
            }
            break;
    }

    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: HostDlgProc
// Desc: Session creation dialog proceedure. 
//-----------------------------------------------------------------------------
INT_PTR CALLBACK HostDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_INITDIALOG:
        {
            // Set default port
            TCHAR strPort[40];
            _itot( g_dwLocalPort, strPort, 10 );
            SetDlgItemText( hDlg, IDC_LOCAL_PORT, strPort );
            
            // Set default session name
            SetDlgItemText( hDlg, IDC_NAME, TEXT("New Host") );

            // Turn on host migration by default
            SendMessage( GetDlgItem( hDlg, IDC_MIGRATE ), BM_SETCHECK, 
                         (WPARAM) BST_CHECKED, 0 );
            return TRUE;
        }

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
                    EndDialog( hDlg, IDCANCEL );
                    return TRUE;

                case IDOK:
                    // Store the port
                    TCHAR strPort[40];
                    GetDlgItemText( hDlg, IDC_LOCAL_PORT, strPort, 40 );
                    strPort[39] = 0;
                    g_dwLocalPort = _ttoi( strPort );

                    // Store the session name
                    GetDlgItemText( hDlg, IDC_NAME, g_strSession, 128 );

                    // Store host migration option
                    g_bMigrateHost = ( BST_CHECKED == SendMessage( GetDlgItem( hDlg, IDC_MIGRATE ), 
                                                                   BM_GETCHECK, 0, 0 ) );
                                       
                    // return
                    EndDialog( hDlg, IDOK );
                    return TRUE;
            }
            break;
    }

    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: ConnectDlgProc
// Desc: Session creation dialog proceedure. 
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ConnectDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_INITDIALOG:
            SendMessage( GetDlgItem( hDlg, IDC_ADDRESS ), WM_SETTEXT, 0,
                         (LPARAM) TEXT("localhost") );
            SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_RESETCONTENT, 0, 0 );
            SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_ADDSTRING, 0,
                         (LPARAM) TEXT("Click \"Search\" to find hosts.") );

            // Set the default remote port
            TCHAR strPort[40];
            _itot( g_dwRemotePort, strPort, 10 );
            SetDlgItemText( hDlg, IDC_REMOTE_PORT, strPort );

            return TRUE;

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDC_SESSIONS:
                    switch( HIWORD(wParam) )
                    {
                        case LBN_SELCHANGE:
                            // Enable connection if a host is selected
                            EnableWindow( GetDlgItem( hDlg, IDOK ), ( LB_ERR !=
                                SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_GETCURSEL, 0, 0 ) ) );
                            return TRUE;
                    }
                    break;

                case IDC_SEARCH:
                    EnumDirectPlayHosts( hDlg );
                    return TRUE;

                case IDCANCEL:
                    EndDialog( hDlg, IDCANCEL );
                    return TRUE;

                case IDOK:
                    g_iSelectedHost = SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_GETCURSEL, 0, 0 );
                    EndDialog( hDlg, (g_iSelectedHost == LB_ERR) ? IDCANCEL : IDOK );
                    return TRUE;
            }
    }

    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: DirectPlayMessageHandler
// Desc: Handler for DirectPlay messages.  This tutorial doesn't repond to any
//       DirectPlay messages
//-----------------------------------------------------------------------------
HRESULT WINAPI DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, 
                                         PVOID pMsgBuffer)
{
    HRESULT     hr = S_OK;
    
    switch( dwMessageId )
    {
        case DPN_MSGID_ENUM_HOSTS_RESPONSE:
        {
            PDPNMSG_ENUM_HOSTS_RESPONSE     pEnumHostsResponseMsg;
            const DPN_APPLICATION_DESC*     pAppDesc;
            HOST_NODE*                      pHostNode = NULL;
            TCHAR*                          strSession = NULL;
        
            pEnumHostsResponseMsg = (PDPNMSG_ENUM_HOSTS_RESPONSE) pMsgBuffer;
            pAppDesc = pEnumHostsResponseMsg->pApplicationDescription;
        
            // Insert each host response if it isn't already present
            EnterCriticalSection(&g_csHostList);
        
            for (pHostNode = g_pHostList; pHostNode; pHostNode = pHostNode->pNext)
            {
                if( pAppDesc->guidInstance == pHostNode->pAppDesc->guidInstance)
                {
                    // This host is already in the list
                    pHostNode = NULL;
                    goto Break_ENUM_HOSTS_RESPONSE;
                }
            }
        
            // This host session is not in the list then so insert it.
            pHostNode = new HOST_NODE;
            if( pHostNode == NULL)
            {
                goto Break_ENUM_HOSTS_RESPONSE;
            }
        
            ZeroMemory(pHostNode, sizeof(HOST_NODE));
        
            // Copy the Host Address
            if( FAILED( pEnumHostsResponseMsg->pAddressSender->Duplicate(&pHostNode->pHostAddress ) ) )
            {
                goto Break_ENUM_HOSTS_RESPONSE;
            }
        
            pHostNode->pAppDesc = new DPN_APPLICATION_DESC;
        
            if( pHostNode == NULL)
            {
                goto Break_ENUM_HOSTS_RESPONSE;
            }
        
            ZeroMemory(pHostNode->pAppDesc, sizeof(DPN_APPLICATION_DESC));
            memcpy(pHostNode->pAppDesc, pAppDesc, sizeof(DPN_APPLICATION_DESC));
        
            // Null out all the pointers we aren't copying
            pHostNode->pAppDesc->pwszSessionName = NULL;
            pHostNode->pAppDesc->pwszPassword = NULL;
            pHostNode->pAppDesc->pvReservedData = NULL;
            pHostNode->pAppDesc->dwReservedDataSize = 0;
            pHostNode->pAppDesc->pvApplicationReservedData = NULL;
            pHostNode->pAppDesc->dwApplicationReservedDataSize = 0;
        
            if( pAppDesc->pwszSessionName)
            {
                DWORD dwNumChars = (DWORD) wcslen(pAppDesc->pwszSessionName) + 1;
                strSession = new TCHAR[ dwNumChars ];
            
                if( strSession)
                    DXUtil_ConvertWideStringToGenericCch( strSession, pAppDesc->pwszSessionName, dwNumChars );
            }
        
            pHostNode->strSessionName = strSession;
        
            // Insert it onto the front of the list
            pHostNode->pNext = g_pHostList;
            g_pHostList = pHostNode;
            pHostNode = NULL;
        
Break_ENUM_HOSTS_RESPONSE:
            LeaveCriticalSection(&g_csHostList);       

            if( pHostNode )
            {
                SAFE_RELEASE(pHostNode->pHostAddress);           
                SAFE_DELETE(pHostNode->pAppDesc);            
                delete pHostNode;
            }
        
            break;
        }
        case DPN_MSGID_RECEIVE:
        {
            PDPNMSG_RECEIVE     pMsg;
            TCHAR       strBuffer[256];


            pMsg = (PDPNMSG_RECEIVE) pMsgBuffer;
            DXUtil_ConvertWideStringToGenericCch( strBuffer, (WCHAR*) pMsg->pReceiveData, 256 );


            SendMessage( GetDlgItem( g_hDlg, IDC_INBOX ), LB_ADDSTRING, 0,
                         (LPARAM) strBuffer );
            break;
        }
        case DPN_MSGID_HOST_MIGRATE:
        {
            PDPNMSG_HOST_MIGRATE    pHostMigrateMsg;

            pHostMigrateMsg = (PDPNMSG_HOST_MIGRATE) pMsgBuffer;

            // See if we are the new host
            if( pHostMigrateMsg->dpnidNewHost == g_dpnidLocalPlayer)
            {
                g_bConnected = FALSE;
                g_bHosting = TRUE;
                UpdateUI();
            }
            break;
        }
    
        case DPN_MSGID_DESTROY_PLAYER:
            PDPNMSG_DESTROY_PLAYER  pDestroyPlayerMsg;

            pDestroyPlayerMsg = (PDPNMSG_DESTROY_PLAYER)pMsgBuffer;

            // See if we are the destroyed player
            if( pDestroyPlayerMsg->dpnidPlayer == g_dpnidLocalPlayer )
            {
                switch( pDestroyPlayerMsg->dwReason )
                {
                    case DPNDESTROYPLAYERREASON_CONNECTIONLOST:
                        OutputError( TEXT("Connection lost") );
                        break;
                    case DPNDESTROYPLAYERREASON_SESSIONTERMINATED:
                        OutputError( TEXT("Session terminated") );
                        break;
                    case DPNDESTROYPLAYERREASON_HOSTDESTROYEDPLAYER:
                        OutputError( TEXT("Host destroyed local player") );
                        break;
                }
                 
                g_bHosting = g_bConnected = FALSE;
                UpdateUI();
            }
            break;

        case DPN_MSGID_CREATE_PLAYER:
        {
            PDPNMSG_CREATE_PLAYER   pCreatePlayerMsg;
            DWORD                   dwSize = 0;
            DPN_PLAYER_INFO*        pdpPlayerInfo = NULL;

            pCreatePlayerMsg = (PDPNMSG_CREATE_PLAYER)pMsgBuffer;

            // check to see if we are the player being created
            hr = g_pDP->GetPeerInfo(pCreatePlayerMsg->dpnidPlayer, pdpPlayerInfo, &dwSize, 0);

            if( FAILED(hr) && hr != DPNERR_BUFFERTOOSMALL)
            {
                OutputError( TEXT("Failed GetPeerInfo"), hr );
                return hr;
            }

            pdpPlayerInfo = (DPN_PLAYER_INFO*) new BYTE[dwSize];
            ZeroMemory(pdpPlayerInfo, dwSize);
            pdpPlayerInfo->dwSize = sizeof(DPN_PLAYER_INFO);

            if( FAILED( hr = g_pDP->GetPeerInfo(pCreatePlayerMsg->dpnidPlayer, pdpPlayerInfo, &dwSize, 0 ) ) )
            {
                OutputError( TEXT("Failed GetPeerInfo"), hr );
                goto Error_DPN_MSGID_CREATE_PLAYER;
            }

            if( pdpPlayerInfo->dwPlayerFlags & DPNPLAYER_LOCAL)
                g_dpnidLocalPlayer = pCreatePlayerMsg->dpnidPlayer;

Error_DPN_MSGID_CREATE_PLAYER:
            SAFE_DELETE_ARRAY(pdpPlayerInfo);
            break;
        }

        case DPN_MSGID_TERMINATE_SESSION:
        {
            g_bHosting = g_bConnected = FALSE;
            UpdateUI();

            break;
        }

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
        OutputError( TEXT("Failed Enumerating Service Providers"), hr );
        goto LCleanup;
    }

    pdnSPInfo = (DPN_SERVICE_PROVIDER_INFO*) new BYTE[dwSize];
    
    if( FAILED( hr = g_pDP->EnumServiceProviders( pGuidSP, NULL, pdnSPInfo, &dwSize, &dwItems, 0 ) ) )
    {
        OutputError( TEXT("Failed Enumerating Service Providers"), hr );
        goto LCleanup;
    }

    // If the returned list is empty, the given service provider is unavailable.
    hr = ( dwItems ) ? S_OK : E_FAIL;

LCleanup:
    SAFE_DELETE_ARRAY(pdnSPInfo);

    return SUCCEEDED(hr);
}




//-----------------------------------------------------------------------------
// Name: CreateDeviceAddress()
// Desc: Creates a device address
//-----------------------------------------------------------------------------
HRESULT CreateDeviceAddress( bool bIsHost )
{
    HRESULT hr = S_OK;

    // Start clean
    SAFE_RELEASE( g_pDeviceAddress );

    // Create our IDirectPlay8Address Device Address
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Address,
                                       (LPVOID*) &g_pDeviceAddress ) ) )
    {
        OutputError( TEXT("Failed Creating the IDirectPlay8Address Object"), hr );
        return hr;
    }
    
    // Set the SP for our Device Address
    if( FAILED( hr = g_pDeviceAddress->SetSP(&CLSID_DP8SP_TCPIP ) ) )
    {
        OutputError( TEXT("Failed Setting the Service Provider"), hr );
        return hr;
    }

    // Set the port number on which to host
    if( bIsHost && g_dwLocalPort > 0 )
    {
        if( FAILED( hr = g_pDeviceAddress->AddComponent( DPNA_KEY_PORT, 
                                                         &g_dwLocalPort,
                                                         sizeof(DWORD),
                                                         DPNA_DATATYPE_DWORD ) ) )
        {
            OutputError( TEXT("Failed setting the local port"), hr );
            return hr;
        }
    }
    
    return hr;
}





//-----------------------------------------------------------------------------
// Name: HostSession()
// Desc: Host a DirectPlay session
//-----------------------------------------------------------------------------
HRESULT HostSession()
{
    HRESULT                 hr = S_OK;
    DPN_APPLICATION_DESC    dpAppDesc;
    WCHAR                   strHost[128] = {0};

    // Get the session name and port number from dialog
    if( IDOK != DialogBox( g_hInst, MAKEINTRESOURCE(IDD_HOST), g_hDlg, HostDlgProc ) )
        return S_OK;

    DXUtil_ConvertGenericStringToWideCch( strHost, g_strSession, 128 );

    // Create an address for the local device
    if( FAILED( hr = CreateDeviceAddress(true) ) )
    {
        OutputError( TEXT("Failed creating device address"), hr );
        return hr;
    }

    // Now set up the Application Description
    ZeroMemory(&dpAppDesc, sizeof(DPN_APPLICATION_DESC));
    dpAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpAppDesc.guidApplication = g_guidApp;
    dpAppDesc.pwszSessionName = strHost;
    dpAppDesc.dwFlags = DPNSESSION_NODPNSVR;

    // Set host migration option
    if( g_bMigrateHost )
        dpAppDesc.dwFlags |= DPNSESSION_MIGRATE_HOST;

    // We are now ready to host the app
    if( FAILED( hr = g_pDP->Host( &dpAppDesc,            // AppDesc
                                  &g_pDeviceAddress, 1,   // Device Address
                                  NULL, NULL,             // Reserved
                                  NULL,                   // Player Context
                                  0 ) ) )                 // dwFlags
    {
        OutputError( TEXT("Failed to host a new session"), hr );
        return hr;
    }
    else
    {     
        g_bHosting = true;
        UpdateUI();
    }

    return S_OK;
}





//-----------------------------------------------------------------------------
// Name: ConnectToSession()
// Desc: Connects to a DirectPlay session
//-----------------------------------------------------------------------------
HRESULT ConnectToSession()
{
    HRESULT               hr           = E_FAIL;
    DPN_APPLICATION_DESC  dpnAppDesc   = {0};
    HOST_NODE*            pHostNode    = NULL;
    IDirectPlay8Address*  pHostAddress = NULL;

    // Create an address for the local device
    if( FAILED( hr = CreateDeviceAddress(false) ) )
    {
        OutputError( TEXT("Failed creating device address"), hr );
        return hr;
    }

    // Get the selected host from the dialog box
    if( IDOK != DialogBox( g_hInst, MAKEINTRESOURCE(IDD_CONNECT), g_hDlg, ConnectDlgProc ) )
        return S_OK;

    ZeroMemory(&dpnAppDesc, sizeof(DPN_APPLICATION_DESC));
    dpnAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpnAppDesc.guidApplication = g_guidApp;

    EnterCriticalSection(&g_csHostList);

    // Advance to the correct host
    pHostNode = g_pHostList;
    while( pHostNode && g_iSelectedHost > 0 )
    {
        pHostNode = pHostNode->pNext;
        g_iSelectedHost--;
    }

    if( pHostNode )
    {
        if( SUCCEEDED(hr = pHostNode->pHostAddress->Duplicate(&pHostAddress ) ) )
        {
            hr = g_pDP->Connect(&dpnAppDesc,        // pdnAppDesc
                                pHostAddress,       // pHostAddr
                                g_pDeviceAddress,   // pDeviceInfo
                                NULL,               // pdnSecurity
                                NULL,               // pdnCredentials
                                NULL, 0,            // pvUserConnectData/Size
                                NULL,               // pvPlayerContext
                                NULL,               // pvAsyncContext
                                NULL,               // pvAsyncHandle
                                DPNCONNECT_SYNC);   // dwFlags

            if( SUCCEEDED(hr) )
            {
                g_bConnected = true;
                _tcsncpy( g_strSession, pHostNode->strSessionName, 128 );
                UpdateUI();
            }
            else
                OutputError( TEXT("Failed Connecting to Host"), hr );
        }
        else
        {
            OutputError( TEXT("Failed Duplicating Host Address"), hr );
        }
    }

    LeaveCriticalSection(&g_csHostList);

    SAFE_RELEASE(pHostAddress);

    return hr;
}






//-----------------------------------------------------------------------------
// Name: EnumDirectPlayHosts()
// Desc: Find active sessions and list them to the UI
//-----------------------------------------------------------------------------
HRESULT EnumDirectPlayHosts( HWND hDlg )
{
    HRESULT                 hr = S_OK;
    TCHAR                   strHost[128];
    DPN_APPLICATION_DESC    dpAppDesc;

    // Get the hostname/ip
    SendMessage( GetDlgItem( hDlg, IDC_ADDRESS ), WM_GETTEXT,
                 (WPARAM) 128, (LPARAM) strHost );
   
    // Store the current port
    TCHAR strPort[40];
    GetDlgItemText( hDlg, IDC_REMOTE_PORT, strPort, 40 );
    strPort[39] = 0;
    g_dwRemotePort = _ttoi( strPort );

    // Clear the results list
    SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_RESETCONTENT, 0, 0 );
    
    // Disable connections
    EnableWindow( GetDlgItem( hDlg, IDOK ), FALSE );
    EnableWindow( GetDlgItem( hDlg, IDC_SESSIONS ), FALSE );

    // Clear the stored host list
    ClearHostList();

    // Create an address for the local device
    if( FAILED( hr = CreateDeviceAddress(false) ) )
    {
        OutputError( TEXT("Failed creating device address"), hr );
        return hr;
    }

    // Create a search address for the remote host
    if( FAILED( hr = CreateHostAddress( strHost ) ) )
    {
        OutputError( TEXT("Failed Creating Host Address"), hr );
        
        // Set results text
        SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_ADDSTRING, 0, 
                     (LPARAM) TEXT("Could not create given address") );
        return hr;
    }

   
    // Now set up the Application Description
    ZeroMemory(&dpAppDesc, sizeof(DPN_APPLICATION_DESC));
    dpAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpAppDesc.guidApplication = g_guidApp;

    // We now have the host address so lets enum
    if( FAILED( hr = g_pDP->EnumHosts( &dpAppDesc,             // pApplicationDesc
                                       g_pHostAddress,         // pdpaddrHost
                                       g_pDeviceAddress,       // pdpaddrDeviceInfo
                                       NULL, 0,                // pvUserEnumData, size
                                       4,                      // dwEnumCount
                                       0,                      // dwRetryInterval
                                       0,                      // dwTimeOut
                                       NULL,                   // pvUserContext
                                       NULL,                   // pAsyncHandle
                                       DPNENUMHOSTS_SYNC ) ) ) // dwFlags
    {
        OutputError( TEXT("Failed Enumerating the Hosts"), hr );

        // Set results text
        SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_ADDSTRING, 0, 
                     (LPARAM) TEXT("Error occurred during search.") );
        return hr;
    }


    OutputHostList( hDlg );

    // Enable connections if hosts found
    EnableWindow( GetDlgItem( hDlg, IDC_SESSIONS ), (NULL != g_pHostList) );

    return S_OK;
}





//-----------------------------------------------------------------------------
// Name: SendDirectPlayMessage()
// Desc: Sends a DirectPlay message to all players
//-----------------------------------------------------------------------------
HRESULT SendDirectPlayMessage()
{
    HRESULT         hr = S_OK;
    DPN_BUFFER_DESC dpnBuffer;
    WCHAR           wszData[256];
    TCHAR           strBuffer[256];

    // Get the data from the user
    if( 0 == SendMessage( GetDlgItem( g_hDlg, IDC_OUTBOX ), WM_GETTEXT, 
                          (WPARAM) 256, (LPARAM) strBuffer ) )
    {
        // Empty string
        return S_OK;
    }

    SendMessage( GetDlgItem( g_hDlg, IDC_OUTBOX ), WM_SETTEXT, 0,
                 (LPARAM) TEXT("") );

    DXUtil_ConvertGenericStringToWideCch( wszData, strBuffer, 256 );

    dpnBuffer.pBufferData = (BYTE*) wszData;
    dpnBuffer.dwBufferSize = 2 * ( (UINT) wcslen(wszData) + 1 );

    if( FAILED( hr = g_pDP->SendTo( DPNID_ALL_PLAYERS_GROUP, // dpnid
                                    &dpnBuffer,             // pBufferDesc
                                    1,                      // cBufferDesc
                                    0,                      // dwTimeOut
                                    NULL,                   // pvAsyncContext
                                    NULL,                   // pvAsyncHandle
                                    DPNSEND_SYNC |
                                    DPNSEND_NOLOOPBACK ) ) )    // dwFlags
    {
        OutputError( TEXT("Failed Sending Data"), hr );
        return hr;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateHostAddress()
// Desc: Creates a host address
//-----------------------------------------------------------------------------
HRESULT CreateHostAddress( TCHAR* strHost )
{
    HRESULT         hr             = S_OK;
    WCHAR           strBuffer[128] = {0};

    // Start clean
    SAFE_RELEASE( g_pHostAddress );

    // Create our IDirectPlay8Address Host Address
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Address,
                                       (LPVOID*) &g_pHostAddress ) ) )
    {
        OutputError( TEXT("Failed Creating the IDirectPlay8Address Object"), hr );
        return hr;
    }
    
    // Set the SP for our Host Address
    if( FAILED( hr = g_pHostAddress->SetSP( &CLSID_DP8SP_TCPIP ) ) )
    {
        OutputError( TEXT("Failed Setting the Service Provider"),  hr );
        return hr;
    }

    // Convert the generic host string to UNICODE.
    DXUtil_ConvertGenericStringToWideCch( strBuffer, strHost, 128 );

    // Set the hostname into the address
    if( wcslen( strBuffer ) > 0 )
    {
        if( FAILED( hr = g_pHostAddress->AddComponent( DPNA_KEY_HOSTNAME, strBuffer,
                                                       2*((UINT)wcslen(strBuffer) + 1), /*bytes*/
                                                       DPNA_DATATYPE_STRING ) ) )
        {
            OutputError( TEXT("Failed Adding Hostname to Host Address"), hr );
            return hr;
        }
    }

    // Set the remote port
    if( g_dwRemotePort != 0 )
    {
        if( FAILED( hr = g_pHostAddress->AddComponent( DPNA_KEY_PORT, 
                                                       &g_dwRemotePort,
                                                       sizeof(DWORD),
                                                       DPNA_DATATYPE_DWORD ) ) )
        {
            OutputError( TEXT("Failed setting remote port"), hr );
            return hr;
        }
    }

    return S_OK;
}





//-----------------------------------------------------------------------------
// Name: ClearHostList()
// Desc: Remove all stored host information
//-----------------------------------------------------------------------------
void ClearHostList()
{
    HOST_NODE* pHostNode    = NULL;
    HOST_NODE* pHostNodetmp = NULL;

    // Clean up Host list
    EnterCriticalSection(&g_csHostList);

    pHostNode = g_pHostList;
    while( pHostNode != NULL )
    {       
        SAFE_RELEASE(pHostNode->pHostAddress);
        SAFE_DELETE(pHostNode->pAppDesc);
        SAFE_DELETE(pHostNode->strSessionName);

        pHostNodetmp = pHostNode;
        pHostNode    = pHostNode->pNext;
        SAFE_DELETE(pHostNodetmp);
    }

    g_pHostList      = NULL;
    LeaveCriticalSection(&g_csHostList);
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
    HOST_NODE*              pHostNode = NULL;
    DWORD                   dwNumChars = 0;

    // Clear the results list
    SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_RESETCONTENT, 0, 0 );

    // Go through and print out all the hosts URL's that we found
    EnterCriticalSection( &g_csHostList );
 
    for (pHostNode = g_pHostList; pHostNode; pHostNode = pHostNode->pNext, dwNumChars = 0)
    {
        hr = pHostNode->pHostAddress->GetURLW(NULL, &dwNumChars);

        if( hr == DPNERR_BUFFERTOOSMALL)
        {
            strURL = new WCHAR[dwNumChars];
            strBuffer = new TCHAR[dwNumChars];

            if( strURL && strBuffer &&
                SUCCEEDED( pHostNode->pHostAddress->GetURLW(strURL, &dwNumChars ) ) )
            {
                TCHAR* strTemp = NULL;
                DXUtil_ConvertWideStringToGenericCch( strBuffer, strURL, dwNumChars );

                // Compose output text
                if( pHostNode->strSessionName && lstrlen( pHostNode->strSessionName ) )
                    _tcsncpy( strOutput, pHostNode->strSessionName, 30 );
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
    if( NULL == g_pHostList )
        SendMessage( GetDlgItem( hDlg, IDC_SESSIONS ), LB_ADDSTRING, 
                     0, (WPARAM) TEXT("No hosts found.") );

    LeaveCriticalSection( &g_csHostList );
}




//-----------------------------------------------------------------------------
// Name: UpdateUI()
// Desc: Paint visual elements according to current state
//-----------------------------------------------------------------------------
void UpdateUI()
{
    TCHAR strOutput[128] = {0};

    if( g_bHosting )
        lstrcpy( strOutput, TEXT("Hosting session \"") );   
    else if( g_bConnected )
        lstrcpy( strOutput, TEXT("Connected to session \"") );

    // Flush the incoming/outgoing messages box
    SendMessage( GetDlgItem( g_hDlg, IDC_INBOX ), LB_RESETCONTENT, 0, 0 );
    SendMessage( GetDlgItem( g_hDlg, IDC_OUTBOX ), WM_SETTEXT, 0, 
                 (LPARAM) TEXT("") );

    if( g_bHosting || g_bConnected )
    {
        _tcsncat( strOutput, g_strSession, 40 );
        _tcscat( strOutput, TEXT("\"") );
        SendMessage( GetDlgItem( g_hDlg, IDC_STATUS ), WM_SETTEXT, 0, 
                     (LPARAM) strOutput );
        SendMessage( GetDlgItem( g_hDlg, IDC_HOST ), WM_SETTEXT, 0,
                     (LPARAM) TEXT("&Disconnect") );  
    }
    else
    {
        SendMessage( GetDlgItem( g_hDlg, IDC_STATUS ), WM_SETTEXT, 0, 
                         (LPARAM) TEXT("Not connected to a session.") );
        SendMessage( GetDlgItem( g_hDlg, IDC_HOST ), WM_SETTEXT, 0,
                     (LPARAM) TEXT("&Host...") );
        SendMessage( GetDlgItem( g_hDlg, IDC_INBOX ), LB_ADDSTRING, 0,
                     (LPARAM) TEXT("You must first connect to a session.") );
    }

    EnableWindow( GetDlgItem( g_hDlg, IDC_INBOX ), (g_bHosting | g_bConnected) );
    EnableWindow( GetDlgItem( g_hDlg, IDC_OUTBOX ), (g_bHosting | g_bConnected) );
    EnableWindow( GetDlgItem( g_hDlg, IDC_SEND ), (g_bHosting | g_bConnected) );
    EnableWindow( GetDlgItem( g_hDlg, IDC_CONNECT ), !(g_bHosting | g_bConnected) );
}




//-----------------------------------------------------------------------------
// Name: Disconnect
// Desc: Close the current connection and reinitialize DirectPlay
//-----------------------------------------------------------------------------
HRESULT Disconnect()
{
    HRESULT hr = S_OK;

    g_bHosting = g_bConnected = FALSE;
    UpdateUI();

    // Cleanup DirectPlay
    if( g_pDP)
        g_pDP->Close(0);

    // Init DirectPlay
    if( FAILED( hr = g_pDP->Initialize(NULL, DirectPlayMessageHandler, 0 ) ) )
    {
        OutputError( TEXT("Failed Initializing DirectPlay"), hr );
        return hr;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDirectPlay()
// Desc: Initialize DirectPlay
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay()
{
    HRESULT hr = S_OK;

    // Create the IDirectPlay8Peer Object
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Peer, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Peer, 
                                       (LPVOID*) &g_pDP ) ) )
    {
        OutputError( TEXT("Failed Creating the IDirectPlay8Peer Object"), hr );
        return hr;
    }

    // Init DirectPlay
    if( FAILED( hr = g_pDP->Initialize(NULL, DirectPlayMessageHandler, 0 ) ) )
    {
        OutputError( TEXT("Failed Initializing DirectPlay"), hr );
        return hr;
    }

    // Ensure that TCP/IP is a valid Service Provider
    if( FALSE == IsServiceProviderValid( &CLSID_DP8SP_TCPIP ) )
    {
        OutputError( TEXT("Failed validating CLSID_DP8SP_TCPIP.")
                     TEXT("\n\nYou must have TCP/IP installed on your")
                     TEXT("computer to run the DirectPlay tutorials.") );
        return E_FAIL;
    }
  
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CleanupDirectPlay()
// Desc: Cleanup DirectPlay
//-----------------------------------------------------------------------------
void CleanupDirectPlay()
{
    // Cleanup DirectPlay
    if( g_pDP)
        g_pDP->Close(0);

    ClearHostList();

    SAFE_RELEASE(g_pDeviceAddress);
    SAFE_RELEASE(g_pHostAddress);
    SAFE_RELEASE(g_pDP);

    DeleteCriticalSection(&g_csHostList);
}





//-----------------------------------------------------------------------------
// Name: OutputError
// Desc: Output the error and error code using a message box
//-----------------------------------------------------------------------------
void OutputError( TCHAR* str, HRESULT hr )
{
    TCHAR strBuf[256] = {0};

    if( hr )
        _stprintf( strBuf, TEXT("%s:  0x%X"), str, hr );
    else
        _stprintf( strBuf, TEXT("%s"), str );

    MessageBox( g_hDlg, strBuf, TEXT("DirectPlay Sample"), MB_OK );
}



