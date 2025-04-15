//----------------------------------------------------------------------------
// File: Host.cpp
//
// Desc: This simple program builds upon the last tutorial by adding the 
//       creation of an address object and hosting a session.
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
const DWORD TUT02_HOST_PORT = 2602; // The default port number


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8Peer*    g_pDP            = NULL;    // DirectPlay peer object
IDirectPlay8Address* g_pDeviceAddress = NULL;    // Local address
HWND                 g_hDlg           = NULL;    // UI dialog handle
HINSTANCE            g_hInst          = NULL;    // Program instance handle
bool                 g_bHosting       = FALSE;   // Connection status

// This GUID allows DirectPlay to find other instances of the same game on
// the network.  So it must be unique for every game, and the same for 
// every instance of that game.  // {5e4ab2ee-6a50-4614-807e-c632807b5eb1}
GUID g_guidApp = {0x5e4ab2ee, 0x6a50, 0x4614, {0x80, 0x7e, 0xc6, 0x32, 0x80, 0x7b, 0x5e, 0xb1}};

// Load the application window title into this global from the string table.
// Since the Pocket PC doesn't support multiple instances, the title text
// will be used to find currently active instances.
TCHAR g_strAppTitle[MAX_PATH] = {0};

//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay();
BOOL    IsServiceProviderValid( const GUID* pGuidSP );
HRESULT CreateDeviceAddress();
HRESULT HostSession();
HRESULT EndSession();
void    OutputError( TCHAR* str, HRESULT hr = 0 );
void    CleanupDirectPlay();
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
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

    // Create an address for the local device
    if( FAILED( hr = CreateDeviceAddress() ) )
    {
        OutputError( TEXT("Failed creating device address"), hr );
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
            shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_FULLSCREENNOMENUBAR;
            shidi.hDlg = hDlg;

            SHInitDialog( &shidi );
#endif //Pocket PC        * POCKET PC *
//-------------------------------------
            HICON hIcon;
            g_hDlg = hDlg;

            // Load and set the icon
            hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            return TRUE;

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDC_HOST:
                    if( g_bHosting )
                        EndSession();
                    else
                        HostSession();
                    return TRUE;

                case IDOK:
                case IDCANCEL:
                    EndDialog( hDlg, 0 );
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
HRESULT CreateDeviceAddress()
{
    HRESULT hr = S_OK;

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

    // Set the port number
    if( FAILED( hr = g_pDeviceAddress->AddComponent( DPNA_KEY_PORT,
                                                     &TUT02_HOST_PORT,
                                                     sizeof(DWORD),
                                                     DPNA_DATATYPE_DWORD ) ) )
    {
        OutputError( TEXT("Failed setting the port number"), hr );
        return hr;
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

    // Now set up the Application Description
    ZeroMemory(&dpAppDesc, sizeof(DPN_APPLICATION_DESC));
    dpAppDesc.dwSize = sizeof(DPN_APPLICATION_DESC);
    dpAppDesc.guidApplication = g_guidApp;
    dpAppDesc.dwFlags = DPNSESSION_NODPNSVR;

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
        SendMessage( GetDlgItem( g_hDlg, IDC_STATUS ), WM_SETTEXT, 0, 
                     (LPARAM) TEXT("Hosting a session.") );
        SendMessage( GetDlgItem( g_hDlg, IDC_HOST ), WM_SETTEXT, 0,
                     (LPARAM) TEXT("St&op Hosting") );
        g_bHosting = true;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: EndSession()
// Desc: Terminate a currently hosted session
//-----------------------------------------------------------------------------
HRESULT EndSession()
{
    HRESULT                 hr = S_OK;
    
    // Terminate the session
    if( FAILED( hr = g_pDP->TerminateSession( 0, 0, 0 ) ) )
    {
        OutputError( TEXT("Failed to end session"), hr );
        return hr;
    }
    else
    {
        SendMessage( GetDlgItem( g_hDlg, IDC_STATUS ), WM_SETTEXT, 0, 
                     (LPARAM) TEXT("Not connected to a session.") );
        SendMessage( GetDlgItem( g_hDlg, IDC_HOST ), WM_SETTEXT, 0,
                     (LPARAM) TEXT("Start &Hosting") );
        g_bHosting = false;
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
    if( g_pDP )
        g_pDP->Close( 0 );

    SAFE_RELEASE( g_pDeviceAddress );
    SAFE_RELEASE( g_pDP );
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



