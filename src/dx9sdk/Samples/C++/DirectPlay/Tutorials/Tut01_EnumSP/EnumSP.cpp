//----------------------------------------------------------------------------
// File: EnumSP.cpp
//
// Desc: This simple program inits DirectPlay and enumerates the available
//       DirectPlay Service Providers.
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
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8Peer* g_pDP   = NULL;    // DirectPlay peer object
HWND              g_hDlg  = NULL;    // UI dialog handle
HINSTANCE         g_hInst = NULL;    // Program instance handle

// Load the application window title into this global from the string table.
// Since the Pocket PC doesn't support multiple instances, the title text
// will be used to find currently active instances.
TCHAR g_strAppTitle[MAX_PATH] = {0};

//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT InitDirectPlay();
HRESULT ListServiceProviders();
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

            // Find and list detected service providers 
            if( FAILED( ListServiceProviders() ) )
            {
                OutputError( TEXT("An error occured during provider enumeration.")
                             TEXT("\n\nThe sample will now exit.") );
                EndDialog( hDlg, 0 );
            }

            return TRUE;

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
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
// Name: ListServiceProviders()
// Desc: Enumerative the list of local service providers and add detected
//       providers to the UI list.
//-----------------------------------------------------------------------------
HRESULT ListServiceProviders()
{
    HRESULT                     hr              = S_OK;
    DWORD                       i               = 0;
    DPN_SERVICE_PROVIDER_INFO*  pdnSPInfo       = NULL;
    DPN_SERVICE_PROVIDER_INFO*  pdnSPInfoEnum   = NULL;
    DWORD                       dwItems         = 0;
    DWORD                       dwSize          = 0;   
    TCHAR                       strBuf[256]     = {0};

    // Enumerate all the Service Providers available
    hr = g_pDP->EnumServiceProviders(NULL, NULL, NULL, &dwSize, &dwItems, 0);

    if( FAILED(hr) && hr != DPNERR_BUFFERTOOSMALL)
    {
        OutputError( TEXT("Failed Enumerating Service Providers"), hr );
        goto LCleanup;
    }

    pdnSPInfo = (DPN_SERVICE_PROVIDER_INFO*) new BYTE[dwSize];
    
    if( FAILED( hr = g_pDP->EnumServiceProviders(NULL, NULL, pdnSPInfo, &dwSize, &dwItems, 0 ) ) )
    {
        OutputError( TEXT("Failed Enumerating Service Providers"), hr );
        goto LCleanup;
    }

    // Run through each provider desc printing them all out
    pdnSPInfoEnum = pdnSPInfo;
    for ( i = 0; i < dwItems; i++ )
    {
        DXUtil_ConvertWideStringToGenericCch( strBuf, pdnSPInfoEnum->pwszName, 256 );
        SendMessage( GetDlgItem( g_hDlg, IDC_PROVIDERS ), 
                     LB_ADDSTRING, 0, (LPARAM) strBuf );
 
        pdnSPInfoEnum++;
    }

    if( 0 == dwItems )
        SendMessage( GetDlgItem( g_hDlg, IDC_PROVIDERS ),
                     LB_ADDSTRING, 0, (LPARAM) TEXT("No service providers found") );
 
    hr = S_OK;

LCleanup:
    SAFE_DELETE_ARRAY(pdnSPInfo);

    return hr;
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



