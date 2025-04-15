//-----------------------------------------------------------------------------
// File: ThrottleServer.cpp
//
// Desc: The Throttle sample demonstrates how to monitor the send queue and
//       scale the rate of network communication.
//
// Copyright (c) 1999-2001 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef STRICT
#define STRICT
#endif // !STRICT

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <tchar.h>
#include <dplay8.h>
#include <dxerr9.h>
#include "DXUtil.h"
#include "resource.h"

//-----------------------------------------------------------------------------
// Platform-dependent includes
//-----------------------------------------------------------------------------
#ifdef UNDER_CE
    #include <aygshell.h>
#endif // UNDER_CE


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
const DWORD THROTTLESERVER_PORT        = 2510;  // Arbitrary port number 

// Application guid
const GUID g_guidApp = 
{ 0x634a8295, 0x2d6b, 0x4023, { 0x98, 0xc2, 0x23, 0x80, 0xf9, 0xaf, 0xf0, 0xb2 } };


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8Server* g_pDPServer        = NULL;    // DirectPlay server object
DWORD               g_dwSleepTime      = 30;      // To simulate server load
HWND                g_hDlg             = NULL;    // Dialog window handle
DWORD               g_dwPort           = THROTTLESERVER_PORT; // Port number


//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT  WINAPI   DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
INT_PTR  CALLBACK StartDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR  CALLBACK DialogProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT  InitDirectPlay();
HRESULT  Host();
HRESULT  RefreshStatusBarText();
HRESULT  GetHostnamePortString( TCHAR* str, LPDIRECTPLAY8ADDRESS pAddress, DWORD dwBufferLen );






//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------
INT APIENTRY _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, 
                        LPTSTR pCmdLine, INT nCmdShow )
{
    HRESULT hr = S_OK;

    InitCommonControls();

#ifdef UNDER_CE
    // This is needed along with a hidden control in the RC file to make the
    // soft keyboard pop up when the user selects an edit control.
    SHInitExtraControls();
#endif // UNDER_CE

    // Init COM so we can use CoCreateInstance
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

    // Initialize DirectPlay
    if( FAILED( hr = InitDirectPlay() ) )
    {
        MessageBox( NULL, TEXT("Failed initialize IDirectPlay8Server.\n\n")
                          TEXT("The sample will now exit."),
                    TEXT("Throttle Sample"), MB_ICONERROR | MB_OK );
        
        goto LCleanReturn;
    }

    // Run connection loop
    do
    {
        // Ask the user for startup options
        if( IDOK != DialogBox( hInst, MAKEINTRESOURCE(IDD_STARTSERVER), 
                               NULL, (DLGPROC) StartDlgProc ) )
        {
            goto LCleanReturn;
        }

        hr = Host();

    } while( FAILED(hr) );

    // For this sample, we just start a simple dialog box server
    DialogBox( hInst, MAKEINTRESOURCE(IDD_SERVER), NULL, (DLGPROC) DialogProc );

LCleanReturn:
    if( g_pDPServer )
        g_pDPServer->Close(0);

    SAFE_RELEASE( g_pDPServer );
    CoUninitialize();

    return 0;
}




//-----------------------------------------------------------------------------
// Name: InitDirectPlay()
// Desc: Initialize the DirectPlay Server object
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay()
{
    HRESULT hr = S_OK;

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

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: StartDlgProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK StartDlgProc( HWND hDlg, UINT msg, 
                               WPARAM wParam, LPARAM lParam )
{ 
    switch( msg )
    {
        case WM_INITDIALOG:
        {
            // Set the default port number
            TCHAR strPort[40];
            _itot( g_dwPort, strPort, 10 );
            SetDlgItemText( hDlg, IDC_PORT, strPort );
            return TRUE;
        }

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
                case IDOK:
                    // Get the user selected port number
                    TCHAR strPort[40];
                    GetDlgItemText( hDlg, IDC_PORT, strPort, 40 );
                    strPort[39] = 0;

                    g_dwPort = _ttoi( strPort );
                    EndDialog( hDlg, IDOK );
                    return TRUE;

                case IDCANCEL:
                    EndDialog( hDlg, IDCANCEL );
                    return TRUE;
            }

            break;
        }
    }

    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: DialogProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK DialogProc( HWND hDlg, UINT msg, 
                             WPARAM wParam, LPARAM lParam )
{ 
    switch( msg ) 
    {        
        case WM_INITDIALOG:
        {
            g_hDlg = hDlg;


#if defined(WIN32_PLATFORM_PSPC) && (_WIN32_WCE >= 300)
            SHINITDLGINFO   shidi;
            memset( &shidi, 0, sizeof(SHINITDLGINFO) );
            shidi.dwMask = SHIDIM_FLAGS;
            shidi.dwFlags = SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
            shidi.hDlg = hDlg;

            SetForegroundWindow( hDlg );
            SHInitDialog( &shidi );
#endif // WIN32_PLATFORM_PSPC

            // Set the slider range
            SendMessage( GetDlgItem( hDlg, IDC_SERVER_LOAD ), TBM_SETRANGE,
                         (WPARAM) TRUE, (LPARAM) MAKELONG( 0, 200 ) );

            SendMessage( GetDlgItem( hDlg, IDC_SERVER_LOAD ), TBM_SETPOS,
                         (WPARAM) TRUE, (LPARAM) g_dwSleepTime );

            // Load and set the icon
            HICON hIcon = LoadIcon( GetModuleHandle(NULL), MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            RefreshStatusBarText();
            return TRUE;
        }

        case WM_HSCROLL:
        {
            g_dwSleepTime = SendMessage( GetDlgItem( hDlg, IDC_SERVER_LOAD ), 
                                         TBM_GETPOS, 0, 0 );
            return TRUE;
        }

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
                case IDC_APPHELP:
                    DXUtil_LaunchReadme( hDlg, TEXT("DirectPlay\\Throttle") );
                    return TRUE;

                case IDCANCEL:
                    g_hDlg = NULL;
                    EndDialog( hDlg, 0 );
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
    static int   g_nNumConnections = -1;      // Number of active connections
    static DWORD g_dwBytesRecvd     = 0;       // Total bytes received
           TCHAR strBuf[ 56 ]       = {0};     // Temp buffer

    switch( dwMessageId )
    {
        case DPN_MSGID_CREATE_PLAYER:
        {
            g_nNumConnections++;
            _sntprintf( strBuf, 55, TEXT("%d"), g_nNumConnections );

            if( g_hDlg )
            {
                SendMessage( GetDlgItem( g_hDlg, IDC_CONNECTIONS ), WM_SETTEXT, 0, 
                             (LPARAM) strBuf ); 
            }

            break;
        }

        case DPN_MSGID_DESTROY_PLAYER:
        {
            g_nNumConnections--;
            _sntprintf( strBuf, 55, TEXT("%d"), g_nNumConnections );

            if( g_hDlg )
            {
                SendMessage( GetDlgItem( g_hDlg, IDC_CONNECTIONS ), WM_SETTEXT, 0, 
                             (LPARAM) strBuf ); 
            }

            break;
        }

        case DPN_MSGID_RECEIVE:
        {
            // Add the received size to the dialog
            DPNMSG_RECEIVE* pMsg = (DPNMSG_RECEIVE*) pMsgBuffer;

            g_dwBytesRecvd += pMsg->dwReceiveDataSize;
            _sntprintf( strBuf, 55, TEXT("%d kb"), g_dwBytesRecvd / 1024 );

            if( g_hDlg )
            {
                SendMessage( GetDlgItem( g_hDlg, IDC_RECEIVED ), WM_SETTEXT, 0, 
                             (LPARAM) strBuf ); 
            }
   
            // Simulate server load
            Sleep( g_dwSleepTime );

            break;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Host
// Desc: Start a new DirectPlay session
//-----------------------------------------------------------------------------
HRESULT Host()
{
    HRESULT hr;
    PDIRECTPLAY8ADDRESS pDP8AddrLocal = NULL;

    hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL, 
                           CLSCTX_ALL, IID_IDirectPlay8Address, 
                           (LPVOID*) &pDP8AddrLocal );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
        goto LCleanReturn;
    }

    hr = pDP8AddrLocal->SetSP( &CLSID_DP8SP_TCPIP );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("SetSP"), hr );
        goto LCleanReturn;
    }

    // Add the port to pDP8AddrLocal
    if( g_dwPort != 0 )
    {
        if( FAILED( hr = pDP8AddrLocal->AddComponent( DPNA_KEY_PORT, 
                                                          &g_dwPort, 
                                                          sizeof(DWORD),
                                                          DPNA_DATATYPE_DWORD ) ) )
        {
            DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
            goto LCleanReturn;
        }
    }

    DPN_APPLICATION_DESC dpnAppDesc;
    ZeroMemory( &dpnAppDesc, sizeof(DPN_APPLICATION_DESC) );
    dpnAppDesc.dwSize           = sizeof( DPN_APPLICATION_DESC );
    dpnAppDesc.dwFlags          = DPNSESSION_CLIENT_SERVER | DPNSESSION_NODPNSVR;
    dpnAppDesc.guidApplication  = g_guidApp;
    
    hr = g_pDPServer->Host( &dpnAppDesc, &pDP8AddrLocal, 1, NULL, NULL, NULL, 0  );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("Host"), hr );
        goto LCleanReturn;
    }

LCleanReturn:
    SAFE_RELEASE( pDP8AddrLocal );
    return hr;
}




//-----------------------------------------------------------------------------
// Name: RefreshStatusBarText()
// Desc: Refresh the current status bar text based on connection state
//-----------------------------------------------------------------------------
HRESULT RefreshStatusBarText()
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

    // Server is always running while main dialog is running
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