//-----------------------------------------------------------------------------
// File: NatResolver.cpp
//
// Desc: The NAT Resolver sample demonstrates how to create a NAT Resolver
//		 server.
//
// Copyright (c) 2002 Microsoft Corp. All rights reserved.
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
#define NATRESOLVER_PORT 2506  


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8NATResolver* g_pDPNATResolver   = NULL;         // DirectPlay NAT Resolver object
HWND                     g_hDlg             = NULL;         // Dialog window handle
DWORD                    g_dwPort           = NATRESOLVER_PORT; // Port number 


//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT  WINAPI   DirectPlayMessageHandler( PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer );
INT_PTR  CALLBACK DialogProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR  CALLBACK StartDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT  Start();
HRESULT  GetIPString( TCHAR* str, LPDIRECTPLAY8ADDRESS pAddress, DWORD dwBufferLen );






//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------
INT APIENTRY _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, 
                        LPTSTR pCmdLine, INT nCmdShow )
{
#ifdef UNDER_CE
    // This is needed along with a hidden control in the RC file to make the
    // soft keyboard pop up when the user selects an edit control.
    SHInitExtraControls();
#endif // UNDER_CE

    InitCommonControls();

    // Init COM so we can use CoCreateInstance
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

    // Ask the user for startup options
    int iResult = DialogBox( hInst, MAKEINTRESOURCE(IDD_STARTSERVER), NULL, (DLGPROC) StartDlgProc );
    if( iResult != IDOK )
        goto LCleanReturn;

    // For this sample, we just start a simple dialog box server
    DialogBox( hInst, MAKEINTRESOURCE(IDD_NATRESOLVER), NULL, (DLGPROC) DialogProc );

LCleanReturn:
    if( g_pDPNATResolver )
        g_pDPNATResolver->Close(0);

    SAFE_RELEASE( g_pDPNATResolver );
    CoUninitialize();

    return 0;
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

			// Pre-populate the edit box with a default password.
			SetWindowText( GetDlgItem( g_hDlg, IDE_USERSTRING ), _T("MyPassword") );

            // Load and set the icon
            HICON hIcon = LoadIcon( GetModuleHandle(NULL), MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            // Start the NAT Resolver
            if( FAILED( Start() ) )
            {
                MessageBox( NULL, TEXT("Failed to start the server.\n\n")
                                  TEXT("The sample will now exit."),
                                  TEXT("NAT Resolver Sample"), MB_ICONERROR | MB_OK );
                EndDialog( hDlg, 1 );
            }

            return TRUE;
        }

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
                case IDC_APPHELP:
                    DXUtil_LaunchReadme( hDlg, TEXT("DirectPlay\\NATResolver") );
                    return TRUE;

                case IDC_USERSTRING:
                    EnableWindow( GetDlgItem( hDlg, IDE_USERSTRING ), 
                                  IsDlgButtonChecked( hDlg, IDC_USERSTRING ) );
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
    static int   g_nNumQueries      = 0;       // Number of NAT Resolver queries received
    static int   g_nNumResponses    = 0;       // Number of NAT Resolver responses sent
           int   nCurrentNum        = 0;       // Current query/response counter
           int   nPasswordLength    = 0;       // Length of password string
           TCHAR strBuf[ 256 ]      = {0};     // Temp buffer

    switch( dwMessageId )
    {
        case DPN_MSGID_NAT_RESOLVER_QUERY:
        {
            DPNMSG_NAT_RESOLVER_QUERY *pMsgNATResolverQuery = (DPNMSG_NAT_RESOLVER_QUERY*) pMsgBuffer;

            nCurrentNum = InterlockedIncrement((LPLONG) (&g_nNumQueries));
            _sntprintf( strBuf, 255, TEXT("%d"), nCurrentNum );

            if( g_hDlg )
            {
                SendMessage( GetDlgItem( g_hDlg, IDC_QUERIES ), WM_SETTEXT, 0, 
                             (LPARAM) strBuf ); 

                // If a password is required, retrieve it.
                if ( SendMessage( GetDlgItem( g_hDlg, IDC_USERSTRING ), BM_GETCHECK, 0, 0 ) == BST_CHECKED )
                {
                    HRESULT hr;
                    WCHAR wstrBuf[ 256 ]     = {0};     // Temp buffer

                    nPasswordLength = GetWindowText( GetDlgItem( g_hDlg, IDE_USERSTRING ), strBuf, 255 );
                    if (nPasswordLength > 0)
                    {
                        hr = DXUtil_ConvertGenericStringToWideCch( wstrBuf, strBuf, 256 );
                        if (hr == S_OK)
                        {
                            // Reject queries that don't match our password.
							// Note that this password is transmitted in clear text, so you may
							// wish to have the clients encrypt the user string before they add
							// the DPNA_KEY_NAT_RESOLVER_USER_STRING component.  You would then
							// decrypt the string here before comparing.
							if ( ( pMsgNATResolverQuery->pwszUserString == NULL ) ||
								 ( wcscmp( wstrBuf, pMsgNATResolverQuery->pwszUserString ) != 0 ) )
                            {
								return DPNERR_GENERIC;
                            }
                        }
                    }
                }
            }

            // If we made it here, we're going to reply.
            nCurrentNum = InterlockedIncrement((LPLONG) (&g_nNumResponses));
            _sntprintf( strBuf, 255, TEXT("%d"), nCurrentNum );

            if( g_hDlg )
            {
                 SendMessage( GetDlgItem( g_hDlg, IDC_RESPONSES ), WM_SETTEXT, 0, 
                             (LPARAM) strBuf ); 
            }

            break;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Start
// Desc: Start a new DirectPlay NAT Resolver server
//-----------------------------------------------------------------------------
HRESULT Start()
{
    HRESULT hr = S_OK;
    PDIRECTPLAY8ADDRESS pDP8AddrLocal = NULL;
    PDIRECTPLAY8ADDRESS *ppDP8Addresses = NULL;
    DWORD dwNumAddresses = 0;
    
    

    // Create IDirectPlay8Server
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8NATResolver, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8NATResolver, 
                                       (LPVOID*) &g_pDPNATResolver ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );

    // Turn off parameter validation in release builds
#ifdef _DEBUG
    const DWORD dwInitFlags = 0;
#else
    const DWORD dwInitFlags = DPNINITIALIZE_DISABLEPARAMVAL;
#endif // _DEBUG

    // Init IDirectPlay8NATResolver
    if( FAILED( hr = g_pDPNATResolver->Initialize( NULL, DirectPlayMessageHandler, dwInitFlags ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Initialize"), hr );

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
    if( g_dwPort > 0 )
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

    hr = g_pDPNATResolver->Start( &pDP8AddrLocal, 1, 0  );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("Host"), hr );
        goto LCleanReturn;
    }

    // Retrieve the list of addresses for displaying in the window.
	hr = g_pDPNATResolver->GetAddresses( NULL, &dwNumAddresses, 0 );
    ppDP8Addresses = (PDIRECTPLAY8ADDRESS*) LocalAlloc(LPTR, (dwNumAddresses * sizeof(PDIRECTPLAY8ADDRESS)));
    if( ppDP8Addresses == NULL )
	{
        DXTRACE_ERR_MSGBOX( TEXT("LocalAlloc"), hr );
        goto LCleanReturn;
    }
    hr = g_pDPNATResolver->GetAddresses( ppDP8Addresses, &dwNumAddresses, 0 );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("GetAddresses"), hr );
        goto LCleanReturn;
    }

    if( g_hDlg )
        SendMessage( GetDlgItem( g_hDlg, IDC_ADDRESSES ), LB_RESETCONTENT, 0, 0 );

    // Append the addresses
    DWORD i;
    for( i=0; i < dwNumAddresses; i++ )
    {
        TCHAR strAddress[256];

        // Get the IP address
        if( FAILED( GetIPString( strAddress, ppDP8Addresses[i], 256 ) ) )
            continue;;

        if( g_hDlg )
            SendMessage( GetDlgItem( g_hDlg, IDC_ADDRESSES ), LB_ADDSTRING, 0, 
                         (LPARAM) strAddress );
     
    }

LCleanReturn:
    
    if( ppDP8Addresses )
    {
        for( i=0; i < dwNumAddresses; i++ )
            SAFE_RELEASE( ppDP8Addresses[i] );

        LocalFree(ppDP8Addresses);
    }

    SAFE_RELEASE( pDP8AddrLocal );
    return hr;
}




//-----------------------------------------------------------------------------
// Name: GetIPString
// Desc: Stores the IP address and port number of the given DirectPlay 
//       address in the provided string.
//-----------------------------------------------------------------------------
HRESULT GetIPString( TCHAR* str, LPDIRECTPLAY8ADDRESS pAddress, DWORD dwBufferLen )
{
    HRESULT hr = S_OK;

    // Sanity check
    if( NULL == str || NULL == pAddress )
        return E_FAIL;

    // Get the hostname string from the DirectPlay address
    WCHAR wstrHostname[ 256 ] = {0};
    DWORD dwSize = sizeof( wstrHostname );
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