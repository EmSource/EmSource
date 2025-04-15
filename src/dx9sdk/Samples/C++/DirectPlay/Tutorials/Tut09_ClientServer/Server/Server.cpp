//----------------------------------------------------------------------------
// File: Server.cpp
//
// Desc: This tutorial modifes the Send tutorial to be a client/server
//       topology instead of peer to peer. This file encapsultes the server
//       code.
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
const DWORD TUT09_CLIENTSERVER_PORT = 2609; // The default port number



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
IDirectPlay8Server*  g_pDPServer       = NULL;    // DirectPlay server object
IDirectPlay8Address* g_pDeviceAddress  = NULL;    // Local address
IDirectPlay8Address* g_pHostAddress    = NULL;    // Remote host address
HWND                 g_hDlg            = NULL;    // UI dialog handle
HINSTANCE            g_hInst           = NULL;    // Program instance handle
bool                 g_bHosting        = FALSE;   // Host connection status
TCHAR                g_strSession[128] = {0};     // Connected session name 
DWORD                g_dwLocalPort     = TUT09_CLIENTSERVER_PORT; // Host port
DWORD                g_dwRemotePort    = TUT09_CLIENTSERVER_PORT; // Connect port

// This GUID allows DirectPlay to find other instances of the same game on
// the network.  So it must be unique for every game, and the same for 
// every instance of that game.  // {1AD4CA3B-AC68-4d9b-9522-BE59CD485276}
GUID g_guidApp = { 0x1ad4ca3b, 0xac68, 0x4d9b, { 0x95, 0x22, 0xbe, 0x59, 0xcd, 0x48, 0x52, 0x76 } };

// Load the application window title into this global from the string table.
// Since the Pocket PC doesn't support multiple instances, the title text
// will be used to find currently active instances.
TCHAR g_strAppTitle[MAX_PATH] = {0};


//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay();
HRESULT CreateDeviceAddress();
HRESULT HostSession();
HRESULT Disconnect();
HRESULT SendDirectPlayMessage();
BOOL    IsServiceProviderValid( const GUID* pGuidSP );
void    OutputError( TCHAR* str, HRESULT hr = 0 );
void    CleanupDirectPlay();
void    UpdateUI();
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK HostDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
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
                    if( g_bHosting )
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

                    // Return
                    EndDialog( hDlg, IDOK );
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
    switch( dwMessageId )
    {
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
    hr = g_pDPServer->EnumServiceProviders( pGuidSP, NULL, NULL, &dwSize, &dwItems, 0);

    if( FAILED(hr) && hr != DPNERR_BUFFERTOOSMALL)
    {
        OutputError( TEXT("Failed Enumerating Service Providers"), hr );
        goto LCleanup;
    }

    pdnSPInfo = (DPN_SERVICE_PROVIDER_INFO*) new BYTE[dwSize];
    
    if( FAILED( hr = g_pDPServer->EnumServiceProviders( pGuidSP, NULL, pdnSPInfo, &dwSize, &dwItems, 0 ) ) )
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
HRESULT CreateDeviceAddress()
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
    if( g_dwLocalPort > 0 )
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
    DPN_PLAYER_INFO         dpPlayerInfo;
    WCHAR                   strHost[128] = {0};

    // Fill in the player info
    ZeroMemory(&dpPlayerInfo, sizeof(DPN_PLAYER_INFO));
    dpPlayerInfo.dwSize = sizeof(DPN_PLAYER_INFO);
    dpPlayerInfo.dwInfoFlags = DPNINFO_NAME;
    dpPlayerInfo.pwszName = L"Server";
    dpPlayerInfo.pvData = NULL;
    dpPlayerInfo.dwDataSize = NULL;
    dpPlayerInfo.dwPlayerFlags = 0;

    if( FAILED( hr = g_pDPServer->SetServerInfo( &dpPlayerInfo, NULL, NULL, 
                                                 DPNSETSERVERINFO_SYNC ) ) )
    {
        OutputError( TEXT("Failed Hosting"), hr );
        return hr;
    }

    // Get the session name and port number from dialog
    if( IDOK != DialogBox( g_hInst, MAKEINTRESOURCE(IDD_HOST), g_hDlg, HostDlgProc ) )
        return S_OK;

    DXUtil_ConvertGenericStringToWideCch( strHost, g_strSession, 128 );

    // Create an address for the local device
    if( FAILED( hr = CreateDeviceAddress() ) )
    {
        OutputError( TEXT("Failed creating device address"), hr );
        return hr;
    }

    // Now set up the Application Description
    ZeroMemory(&dpAppDesc, sizeof(DPN_APPLICATION_DESC));
    dpAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpAppDesc.guidApplication = g_guidApp;
    dpAppDesc.pwszSessionName = strHost;
    dpAppDesc.dwFlags = DPNSESSION_CLIENT_SERVER | DPNSESSION_NODPNSVR;

    // We are now ready to host the app
    if( FAILED( hr = g_pDPServer->Host( &dpAppDesc,            // AppDesc
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

    if( FAILED( hr = g_pDPServer->SendTo( DPNID_ALL_PLAYERS_GROUP, // dpnid
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
// Name: UpdateUI()
// Desc: Paint visual elements according to current state
//-----------------------------------------------------------------------------
void UpdateUI()
{
    TCHAR strOutput[128] = {0};       
    
    // Flush the incoming/outgoing messages box
    SendMessage( GetDlgItem( g_hDlg, IDC_INBOX ), LB_RESETCONTENT, 0, 0 );
    SendMessage( GetDlgItem( g_hDlg, IDC_OUTBOX ), WM_SETTEXT, 0, 
                 (LPARAM) TEXT("") );

    if( g_bHosting )
    {
        lstrcpy( strOutput, TEXT("Hosting session \"") );
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
                     (LPARAM) TEXT("You must first host a session.") );
    }

    EnableWindow( GetDlgItem( g_hDlg, IDC_INBOX ),    g_bHosting );
    EnableWindow( GetDlgItem( g_hDlg, IDC_OUTBOX ),   g_bHosting );
    EnableWindow( GetDlgItem( g_hDlg, IDC_SEND ),     g_bHosting );
}




//-----------------------------------------------------------------------------
// Name: Disconnect
// Desc: Close the current connection and reinitialize DirectPlay
//-----------------------------------------------------------------------------
HRESULT Disconnect()
{
    HRESULT hr = S_OK;

    g_bHosting = FALSE;
    UpdateUI();

    // Cleanup DirectPlay
    if( g_pDPServer)
        g_pDPServer->Close(0);

    // Init DirectPlay
    if( FAILED( hr = g_pDPServer->Initialize(NULL, DirectPlayMessageHandler, 0 ) ) )
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
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Server, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Server, 
                                       (LPVOID*) &g_pDPServer ) ) )
    {
        OutputError( TEXT("Failed Creating the IDirectPlay8Server Object"), hr );
        return hr;
    }

    // Init DirectPlay
    if( FAILED( hr = g_pDPServer->Initialize(NULL, DirectPlayMessageHandler, 0 ) ) )
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
    if( g_pDPServer)
        g_pDPServer->Close(0);
  
    SAFE_RELEASE(g_pDeviceAddress);
    SAFE_RELEASE(g_pDPServer);

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



