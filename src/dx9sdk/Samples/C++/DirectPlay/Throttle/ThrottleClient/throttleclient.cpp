//----------------------------------------------------------------------------
// File: ThrottleClient.cpp
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
#include <math.h>
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
const DWORD TIMER_REFRESH              = 2;       // Refresh timer
const DWORD REFRESH_INTERVAL           = 250;     // Update 4 times per second
const DWORD THROTTLESERVER_PORT        = 2510;    // Arbitrary port number 
const DWORD OUTGOING_DATA_SIZE         = 512;     // Size of outgoing data
const double PI = 3.141592653589;   

// Application guid
const GUID g_guidApp = 
{ 0x634a8295, 0x2d6b, 0x4023, { 0x98, 0xc2, 0x23, 0x80, 0xf9, 0xaf, 0xf0, 0xb2 } };

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8Client* g_pDPClient        = NULL;    // DirectPlay client object
DWORD               g_dwSendInterval   = 5;       // Interval between sends (ms)
TCHAR               g_strHostname[256] = {0};     // Server location
DWORD               g_dwMaxQueueSize   = 100000;  // Maximum allowed send queue 
HWND                g_hDlg             = NULL;    // Dialog window handle
DWORD               g_dwPort           = THROTTLESERVER_PORT; // Port number

DWORD               g_dwMsgWaiting     = 0;       // Outgoing messages waiting
DWORD               g_dwQueueSize      = 0;       // Current outgoing queue
DWORD               g_dwLatency        = 0;       // Round trip latency (ms)      
DWORD               g_dwSent           = 0;       // Total bytes sent
DWORD               g_dwQueueWait      = 0;       // Time for last message to send

DWORD               g_dwBlocked        = 0;       // Total number of blocked messages
float               g_fBlockPercent    = 0;       // Percent of outgoing messages blocked

//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT  WINAPI   DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
INT_PTR  CALLBACK DialogProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR  CALLBACK ConnectDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT  InitDirectPlay();
HRESULT  Connect();
HRESULT  SendData();
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
        MessageBox( NULL, TEXT("Failed initializing IDirectPlay8Client.\n\n")
                          TEXT("The sample will now exit."),
                    TEXT("Throttle Sample"), MB_OK | MB_ICONERROR );
        
        goto LCleanReturn;
    }

    // Run connection loop
    do
    {
        // Get the hostname
        if( IDOK != DialogBox( hInst, MAKEINTRESOURCE(IDD_CONNECT), 
                               NULL, ConnectDlgProc ) )
        {
            goto LCleanReturn;
        }

        // Attempt the connection
        hr = Connect();

    } while( FAILED(hr) );


    CreateDialog( hInst, MAKEINTRESOURCE(IDD_CLIENT),
                         NULL, DialogProc );
    
    ShowWindow( g_hDlg, SW_SHOW );

    // Start a high performance timer
    DXUtil_Timer( TIMER_START );

    // While idle, send messages as fast as allowed by the current send rate
    // setting. This program allows for send intervals as short as 5 ms, which
    // is usually not a good idea for regularly-sent data, because you'll
    // almost certainly be sending data faster than the target computer can
    // process it. 
    MSG msg;
    for(;;)
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if( WM_QUIT == msg.message )
                break;

            IsDialogMessage( g_hDlg, &msg );
        }
        else
        {
            // If enough time has passed, send data
            if( DXUtil_Timer( TIMER_GETAPPTIME ) > g_dwSendInterval / 1000.0f )
            {
                SendData();

                DXUtil_Timer( TIMER_RESET );
            }
        }
    }

    DestroyWindow( g_hDlg );

LCleanReturn:
    // Cleanup DirectPlay and helper classes
    if( g_pDPClient )
    {
        g_pDPClient->CancelAsyncOperation( NULL, DPNCANCEL_SEND );
        g_pDPClient->Close(0);
    }
        

    SAFE_RELEASE( g_pDPClient );
    CoUninitialize();

    return 0;
}




//-----------------------------------------------------------------------------
// Name: ConnectDlgProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK ConnectDlgProc( HWND hDlg, UINT msg, 
                                 WPARAM wParam, LPARAM lParam )
{
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
        
            SendMessage( GetDlgItem( hDlg, IDC_HOSTNAME ), WM_SETTEXT, 
                         0, (LPARAM) TEXT("localhost") );
            SendMessage( GetDlgItem( hDlg, IDC_HOSTNAME ), EM_SETSEL,
                         0, -1 );

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
                    TCHAR strPort[40];

                    GetDlgItemText( hDlg, IDC_PORT, strPort, 40 );
                    strPort[39] = 0;
                    g_dwPort = _ttoi( strPort );

                    GetDlgItemText( hDlg, IDC_HOSTNAME, g_strHostname, 255 );
                    EndDialog( hDlg, IDOK );
                    return TRUE;

                case IDCANCEL:
                    EndDialog( hDlg, IDCANCEL );
                    return TRUE;
            }
            break;
        }
    }

    return FALSE; // Didn't handle message
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
        
            // Load and set the icon
            HICON hIcon = LoadIcon( GetModuleHandle(NULL), MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            // Set the slider range
            SendMessage( GetDlgItem( hDlg, IDC_SEND_INTERVAL ), TBM_SETRANGE,
                         (WPARAM) TRUE, (LPARAM) MAKELONG( 5, 100 ) );

            SendMessage( GetDlgItem( hDlg, IDC_SEND_INTERVAL ), TBM_SETPOS,
                         (WPARAM) TRUE, (LPARAM) g_dwSendInterval );

            // Set the slider range
            SendMessage( GetDlgItem( hDlg, IDC_MAX_QUEUE_SIZE ), TBM_SETRANGE,
                         (WPARAM) TRUE, (LPARAM) MAKELONG( 0, 500 ) );

            SendMessage( GetDlgItem( hDlg, IDC_MAX_QUEUE_SIZE ), TBM_SETPOS,
                         (WPARAM) TRUE, (LPARAM) g_dwMaxQueueSize/1024 );

            // Set queue monitoring as default
            CheckDlgButton( hDlg, IDC_REGULATE_OUTGOING_RATE, BST_CHECKED );

            RefreshStatusBarText();

            // Start timers
            SetTimer( hDlg, TIMER_REFRESH, REFRESH_INTERVAL, NULL );

            return TRUE;
        }

        case WM_TIMER:
        {
            TCHAR strBuf[ 256 ] = {0};
            DPN_CONNECTION_INFO dpnConInfo = {0};
            dpnConInfo.dwSize = sizeof(DPN_CONNECTION_INFO);
            g_pDPClient->GetConnectionInfo( &dpnConInfo, 0 );

            g_dwLatency = dpnConInfo.dwRoundTripLatencyMS;

            g_pDPClient->GetSendQueueInfo( &g_dwMsgWaiting,
                                           &g_dwQueueSize, 0 );

            // Refresh window info
            _sntprintf( strBuf, 255, TEXT("%d"), g_dwMsgWaiting );
            SendMessage( GetDlgItem( hDlg, IDC_MESSAGES_WAITING ),
                         WM_SETTEXT, 0, (LPARAM) strBuf );

            _sntprintf( strBuf, 255, TEXT("%d kb"), g_dwQueueSize/1024 );
            SendMessage( GetDlgItem( hDlg, IDC_QUEUE_SIZE ),
                         WM_SETTEXT, 0, (LPARAM) strBuf );

            _sntprintf( strBuf, 255, TEXT("%d ms"), g_dwLatency );
            SendMessage( GetDlgItem( hDlg, IDC_LATENCY ),
                         WM_SETTEXT, 0, (LPARAM) strBuf );

             _sntprintf( strBuf, 255, TEXT("%d ms"), g_dwQueueWait );
            SendMessage( GetDlgItem( hDlg, IDC_QUEUE_WAIT ),
                         WM_SETTEXT, 0, (LPARAM) strBuf );

            _sntprintf( strBuf, 255, TEXT("%d kb"), g_dwSent/1024 );
            SendMessage( GetDlgItem( hDlg, IDC_DATA_SENT ),
                         WM_SETTEXT, 0, (LPARAM) strBuf );

            _sntprintf( strBuf, 255, TEXT("%d kb"), g_dwBlocked/1024 );
            SendMessage( GetDlgItem( hDlg, IDC_BLOCKED ),
                         WM_SETTEXT, 0, (LPARAM) strBuf );

            _sntprintf( strBuf, 255, TEXT("%.1f"), g_fBlockPercent * 100 );
            SendMessage( GetDlgItem( hDlg, IDC_BLOCK_PERCENTAGE ),
                         WM_SETTEXT, 0, (LPARAM) strBuf );

            return TRUE;
        }

        case WM_HSCROLL:
        {
            DWORD dwLogPos = SendMessage( (HWND) lParam, TBM_GETPOS, 0, 0 );

            if( (HWND) lParam == GetDlgItem( hDlg, IDC_SEND_INTERVAL ) )
            {
                g_dwSendInterval = dwLogPos;
            }
            else if( (HWND) lParam == GetDlgItem( hDlg, IDC_MAX_QUEUE_SIZE ) )
            {
                g_dwMaxQueueSize = dwLogPos * 1024;
            }

            return TRUE;
        }

        case WM_CLOSE:
        {
            PostQuitMessage( 0 );
            return TRUE;
        }

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {  
                case IDC_APPHELP:
                {
                    DXUtil_LaunchReadme( hDlg, TEXT("DirectPlay\\Throttle") );
                    return TRUE;
                }
    
                case IDC_REGULATE_OUTGOING_RATE:
                {
                    BOOL bChecked = IsDlgButtonChecked( hDlg, IDC_REGULATE_OUTGOING_RATE );

                    EnableWindow( GetDlgItem( hDlg, IDC_MAX_QUEUE_SIZE_TEXT   ), bChecked );
                    EnableWindow( GetDlgItem( hDlg, IDC_MAX_QUEUE_SIZE        ), bChecked );
                    EnableWindow( GetDlgItem( hDlg, IDC_MIN_QUEUE_TEXT        ), bChecked );
                    EnableWindow( GetDlgItem( hDlg, IDC_MAX_QUEUE_TEXT        ), bChecked );
                    EnableWindow( GetDlgItem( hDlg, IDC_BLOCKED_TEXT          ), bChecked );
                    EnableWindow( GetDlgItem( hDlg, IDC_BLOCKED               ), bChecked );
                    EnableWindow( GetDlgItem( hDlg, IDC_BLOCK_PERCENTAGE_TEXT ), bChecked );
                    EnableWindow( GetDlgItem( hDlg, IDC_BLOCK_PERCENTAGE      ), bChecked );
                    return TRUE;
                }

                case IDCANCEL:
                {
                    PostQuitMessage( 0 );
                    return TRUE;
                }
            }
            break;
        }
    }

    return FALSE; // Didn't handle message
}




//-----------------------------------------------------------------------------
// Name: InitDirectPlay()
// Desc: Initialize the DirectPlay Client object
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay()
{
    HRESULT hr = S_OK;

    // Create IDirectPlay8Client
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8Client, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8Client, 
                                       (LPVOID*) &g_pDPClient ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );

    // Turn off parameter validation in release builds
#ifdef _DEBUG
    const DWORD dwInitFlags = 0;
#else
    const DWORD dwInitFlags = DPNINITIALIZE_DISABLEPARAMVAL;
#endif // _DEBUG

    // Init IDirectPlay8Client
    if( FAILED( hr = g_pDPClient->Initialize( NULL, DirectPlayMessageHandler, dwInitFlags ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Initialize"), hr );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Connect()
// Desc: Connect to the server
//-----------------------------------------------------------------------------
HRESULT Connect()
{
    HRESULT hr;
    PDIRECTPLAY8ADDRESS pDP8AddrLocal  = NULL;
    PDIRECTPLAY8ADDRESS pDP8AddrRemote = NULL;

    WCHAR wstrHostname[256] = {0};
    DXUtil_ConvertGenericStringToWideCch( wstrHostname, g_strHostname, 256 );

    

    // Create local address
    hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL, 
                           CLSCTX_ALL, IID_IDirectPlay8Address, 
                           (LPVOID*) &pDP8AddrLocal );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
        goto LCleanReturn;
    }

    // Create remote address
    hr = CoCreateInstance( CLSID_DirectPlay8Address, NULL, 
                           CLSCTX_ALL, IID_IDirectPlay8Address, 
                           (LPVOID*) &pDP8AddrRemote );
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

    // Set the SP
    hr = pDP8AddrRemote->SetSP( &CLSID_DP8SP_TCPIP );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("SetSP"), hr );
        goto LCleanReturn;
    }

    // Add the hostname to pDP8AddrRemote
    if( wcslen(wstrHostname) > 0 )
    {
        if( FAILED( hr = pDP8AddrRemote->AddComponent( DPNA_KEY_HOSTNAME, 
                                                       wstrHostname, 
                                                       (DWORD) (wcslen(wstrHostname)+1)*sizeof(WCHAR),
                                                       DPNA_DATATYPE_STRING ) ) )
        {
            DXTRACE_ERR_MSGBOX( TEXT("AddComponent"), hr );
            goto LCleanReturn;
        }
    }

    // Add the port to pDP8AddrRemote
    if( g_dwPort != 0 )
    {
        if( FAILED( hr = pDP8AddrRemote->AddComponent( DPNA_KEY_PORT, 
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
    dpnAppDesc.dwFlags          = DPNSESSION_CLIENT_SERVER;
    dpnAppDesc.guidApplication  = g_guidApp;
    
    hr = g_pDPClient->Connect( &dpnAppDesc, pDP8AddrRemote, pDP8AddrLocal,
                               NULL, NULL, NULL, NULL, NULL, NULL, DPNCONNECT_OKTOQUERYFORADDRESSING | DPNCONNECT_SYNC );
    if( FAILED(hr) )
    {
        switch( hr )
        {
            case DPNERR_NORESPONSE:
                MessageBox( g_hDlg, TEXT("The connection timed out.\n\n")
                                    TEXT("Please verify you've typed the server address\n")
                                    TEXT("correctly and try again."),
                            TEXT("ThrottleClient - No Response"), MB_OK | MB_ICONERROR );
                break;
            
            default:
                DXTRACE_ERR_MSGBOX( TEXT("Connect"), hr );
                break;
        }
        
        goto LCleanReturn;
    }

LCleanReturn:
    SAFE_RELEASE( pDP8AddrRemote );
    SAFE_RELEASE( pDP8AddrLocal );
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
    switch( dwMessageId )
    {   
        case DPN_MSGID_SEND_COMPLETE:
        {
            DPNMSG_SEND_COMPLETE* pMsg = (DPNMSG_SEND_COMPLETE*) pMsgBuffer;

            g_dwQueueWait = pMsg->dwSendTime;
            break;
        }

        case DPN_MSGID_TERMINATE_SESSION:
        {
            MessageBox( g_hDlg, TEXT("Connection lost or session was terminated by host\n\n")
                                TEXT("The sample will now exit"), 
                                TEXT("Throttle Sample"), MB_OK );
            
            PostMessage( g_hDlg, WM_CLOSE, 0, 0 );
            break;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SendData
// Desc: Send data to the server.
//-----------------------------------------------------------------------------
HRESULT  SendData()
{
    HRESULT hr;
    
    // Before sending the data, perform some screening if application-level
    // throttling is enabled. This could be very sophisticated, and messages
    // should probably be screened according to priority, since you wouldn't
    // want to block very important messages.

    // As a simple screening method, our application will allow outgoing
    // messages according to some simple rules: If the current queue size
    // is greater than the maximum, don't allow the message. If the queue
    // size is less that 10% of the maximum, allow the message. Otherwise,
    // randomly allow messages according to a sine distrubution

    if( g_hDlg && IsDlgButtonChecked( g_hDlg, IDC_REGULATE_OUTGOING_RATE ) )
    {
        if( g_dwQueueSize > g_dwMaxQueueSize )
        {
            g_dwBlocked += OUTGOING_DATA_SIZE;
            g_fBlockPercent = 1.0f;
            return S_OK;
        }
        else if( g_dwQueueSize < g_dwMaxQueueSize * 0.1f )
        {
            g_fBlockPercent = 0.0f;
        }
        else
        {
            g_fBlockPercent = (float) sin( ( (float)g_dwQueueSize / (g_dwMaxQueueSize+1) ) * PI/2 );
            if( (float)rand()/RAND_MAX < g_fBlockPercent )
            {
                g_dwBlocked += OUTGOING_DATA_SIZE;
                return S_OK;
            }
        }
    }

    BYTE         data[ OUTGOING_DATA_SIZE ] = {0};
    BUFFERDESC   bufDesc = {0};
    DPNHANDLE    async;

    bufDesc.dwBufferSize = OUTGOING_DATA_SIZE;
    bufDesc.pBufferData = data;

    hr = g_pDPClient->Send( &bufDesc, 1, 0, NULL, &async, DPNSEND_PRIORITY_LOW );
    if( FAILED(hr) )
        return DXTRACE_ERR( TEXT("Send"), hr );

    g_dwSent += OUTGOING_DATA_SIZE; 
    return S_OK;
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
    LPDIRECTPLAY8ADDRESS pAddress = NULL; // Host address    
    
    // Margin the status text
    _tcsncpy( strStatus, TEXT("   "), 1023 );
    strStatus[ 1023 ] = 0;

    
    // Player is always connected as long as main dialog is running
    _tcsncat( strStatus, TEXT("Connected"), 1023 - lstrlen( strStatus ) );
    strStatus[ 1023 ] = 0;
    
    // Retrieve the address
    hr = g_pDPClient->GetServerAddress( &pAddress, 0 );
    if( FAILED(hr) )
        goto LCleanReturn;
  

    // If we have an address to report, determine a reasonable way to output it
    if( pAddress != NULL )
    {
        // Get the provider from the DirectPlay address
        GUID guidSP;
        hr = pAddress->GetSP( &guidSP );
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
            // Get the IP address
            if( SUCCEEDED( GetHostnamePortString( strAddress, pAddress, 256 ) ) )
            {
                _tcsncat( strStatus, TEXT(" to "), 1023 - lstrlen( strStatus ) );
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
    SAFE_RELEASE( pAddress );

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


