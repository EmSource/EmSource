//----------------------------------------------------------------------------
// File: ThreadPool.cpp
//
// Desc: This tutorial uses the IDirectPlay8ThreadPool interface to control
//       when and for how long the DirectPlay worker threads are allowed to 
//       run.
//
// Copyright (c) 2000-2001 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <dplay8.h>
#include <dplobby8.h>
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
const DWORD TUT10_THREADPOOL_PORT = 2610; // The default port number

#define MAKE_RGB(r,g,b)  ((DWORD)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))
#define SEND_BUFFER_SIZE 100

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

struct PAINT_POINT
{
    DWORD dwX;
    DWORD dwY;
    DWORD dwColor;
};


//-----------------------------------------------------------------------------
// App specific DirectPlay messages and structures 
//-----------------------------------------------------------------------------
#define GAME_MSGID_PAINT 1
#define GAME_MSGID_CLEAR 2

// Change compiler pack alignment to be BYTE aligned, and pop the current value
#pragma pack( push, 1 )

struct GAMEMSG_GENERIC
{
    BYTE nType;
};

struct GAMEMSG_PAINT : public GAMEMSG_GENERIC
{
    DWORD dwNumPoints;
    PAINT_POINT points[SEND_BUFFER_SIZE];
};

// Pop the old pack alignment
#pragma pack( pop )


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
IDirectPlay8Peer*                g_pDP              = NULL;    // DirectPlay peer object
IDirectPlay8ThreadPool*          g_pThreadPool      = NULL;    // DirectPlay thread pool
IDirectPlay8LobbiedApplication*  g_pLobbyApp        = NULL;    // LobbyApp object
IDirectPlay8Address*             g_pDeviceAddress   = NULL;    // Local address
IDirectPlay8Address*             g_pHostAddress     = NULL;    // Remote host address
DPNHANDLE                        g_hLobbyHandle     = NULL;    // Lobby handle
DPNID                            g_dpnidLocalPlayer = 0;       // Local player ID
HWND                             g_hDlg             = NULL;    // UI dialog handle
HINSTANCE                        g_hInst            = NULL;    // Program instance handle
bool                             g_bMigrateHost     = FALSE;   // Host migration option
bool                             g_bHosting         = FALSE;   // Host connection status
bool                             g_bConnected       = FALSE;   // Peer connection status
int                              g_iSelectedHost    = 0;       // For connection dialog
TCHAR                            g_strSession[128]  = {0};     // Connected session name 
HOST_NODE*                       g_pHostList        = NULL;    // List of detected hosts
DWORD                            g_dwSelColorCtrl   = IDC_COLOR_RED; // Selected color control
DWORD                            g_dwCurColor       = MAKE_RGB(255, 0, 0);  // Current paint color
HBITMAP                          g_hBmpCanvas       = NULL;    // Canvas bitmap handle
BYTE*                            g_pCanvasData      = NULL;    // Pointer to canvas data
DWORD                            g_dwCanvasWidth    = 0;       // Canvas width
DWORD                            g_dwCanvasHeight   = 0;       // Canvas height
BOOL                             g_bLMouseDown      = FALSE;   // Left button currently down
DWORD                            g_dwLocalPort      = TUT10_THREADPOOL_PORT; // Host port
DWORD                            g_dwRemotePort     = TUT10_THREADPOOL_PORT; // Connect port
WNDPROC                          g_oldCanvasProc    = NULL;    // Former canvas item window procedure
GAMEMSG_PAINT                    g_SendBuffer;                 // Outgoing message
 
// This GUID allows DirectPlay to find other instances of the same game on
// the network.  So it must be unique for every game, and the same for 
// every instance of that game.  // {C301FCED-E884-41a9-94D7-DE66943EC7DB}
GUID g_guidApp = { 0xc301fced, 0xe884, 0x41a9, { 0x94, 0xd7, 0xde, 0x66, 0x94, 0x3e, 0xc7, 0xdb } };

// Since the Pocket PC doesn't support multiple instances, the title text
// will be used to find currently active instances.
TCHAR g_strAppTitle[] = TEXT("Tutorial 10: ThreadPool");

// Program friendly name and executable name will be used for lobby registration
WCHAR g_wstrAppName[] = L"ThreadPool";
WCHAR g_wstrExecutable[] = L"ThreadPool.exe";

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
HRESULT RegisterProgramWithLobby();
HRESULT UnRegisterProgramWithLobby();
HRESULT LobbyLaunch();
BOOL    IsServiceProviderValid( const GUID* pGuidSP );
void    OutputError( TCHAR* str, HRESULT hr = 0 );
void    CleanupDirectPlay();
void    ClearHostList();
void    OutputHostList( HWND hDlg );
void    UpdateUI();
HRESULT Render();
HRESULT DrawPoint( POINT pt, DWORD dwColor );
HRESULT ClearCanvas();
HRESULT CreateCanvas();
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK CanvasWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
void    HandleColorSelect( DWORD dwSelected );
INT_PTR CALLBACK HostDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
INT_PTR CALLBACK ConnectDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT WINAPI DirectPlayMessageHandler(PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer);
HRESULT WINAPI LobbyAppMessageHandler(PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer);


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application. 
//-----------------------------------------------------------------------------
INT APIENTRY _tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, 
                        LPTSTR pCmdLine, INT nCmdShow )
{
   
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

    // See if we were lobby launched
    if( g_hLobbyHandle != NULL )
    {
        // Attempt to host or connect to a session based on the
        // settings received from the lobby client
        if( FAILED( hr = LobbyLaunch() ) )
        {
            OutputError( TEXT("Failed to lobby launch"), hr );
            goto LCleanup;
        }
    }

    // Launch the user interface and begin the game loop
    CreateDialog( hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc );

    MSG msg;

    // Start the game loop
    for(;;)
    {
        // Handle dialog messages if present
        if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
            // Check for game exit
            if( WM_QUIT == msg.message )
                break;

            if( !IsDialogMessage( g_hDlg, &msg ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
        }
        else
        {
            // Send outgoing network data
            if( g_bConnected || g_bHosting )
                SendDirectPlayMessage();

            // Handle incoming network data
            // Here we're setting the allowed timeslice at 100 milliseconds.
            // The program will block while DoWork handles network communication
            // so we don't need to worry about thread synchronization issues as
            // we have on earlier tutorials.
            g_pThreadPool->DoWork( 100, 0 );
            
            // Render the scene
            Render();

            // Yield some time for other processes
            Sleep( 10 );
        }
    }

    DestroyWindow( g_hDlg );
    
LCleanup:
    // Cleanup DirectPlay
    CleanupDirectPlay();

    // Cleanup COM
    CoUninitialize(); 

    if( g_hBmpCanvas )
        DeleteObject( g_hBmpCanvas );

    return 0;
}




//-----------------------------------------------------------------------------
// Name: MainDlgProc
// Desc: Main dialog proceedure. 
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    HRESULT hr;

    switch( msg )
    {
        case WM_INITDIALOG:             
            // Set title bar name
            SendMessage( hDlg, WM_SETTEXT, 0, (LPARAM) g_strAppTitle );
//-------------------------------------
#if defined(WIN32_PLATFORM_PSPC) && (_WIN32_WCE >= 300)

            // Full-screen dialog code for POCKET PC only         
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
            mbi.nToolBarId = IDR_MAIN;
            mbi.hInstRes   = g_hInst;
            
            SHCreateMenuBar(&mbi); 
//                        * POCKET PC *
//-------------------------------------            
#else
            // Load the menu
            HMENU hMenu;
            hMenu = LoadMenu( g_hInst, MAKEINTRESOURCE(IDR_MAIN) );
            SetMenu( hDlg, hMenu );
#endif //Pocket PC            * WIN32 *   
//-------------------------------------

            // Sublass the canvas window to ensure we receive mouse messages
#ifdef _WIN64
            g_oldCanvasProc = (WNDPROC)SetWindowLongPtr( GetDlgItem( hDlg, IDC_CANVAS),
                                                         GWLP_WNDPROC, (LONG_PTR) CanvasWndProc );
#else
            g_oldCanvasProc = (WNDPROC)SetWindowLong( GetDlgItem( hDlg, IDC_CANVAS),
                                                      GWL_WNDPROC, (DWORD) CanvasWndProc );
#endif //_WIN64

            HICON hIcon;
            g_hDlg = hDlg;

            // Load and set the icon
            hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon
            
            RECT rect;
            GetWindowRect( GetDlgItem( hDlg, IDC_CANVAS ), &rect );

            // Determine the size of the canvas bitmap
            g_dwCanvasWidth = rect.right - rect.left;
            g_dwCanvasHeight = rect.bottom - rect.top;

            if( FAILED( CreateCanvas() ) )
            {
                OutputError( TEXT("Failed to create the canvas bitmap.")
                             TEXT("\n\nThe sample will now exit.") );
                EndDialog( hDlg, 0 );
            }

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

                case IDM_LOBBY_REGISTER:
                    if( SUCCEEDED( hr = RegisterProgramWithLobby() ) )
                        MessageBox( hDlg, TEXT("Successfully registered lobby support."),
                                    TEXT("DirectPlay Tutorial"), MB_OK );
                    else
                        OutputError( TEXT("Register failed"), hr );
                    break;

                case IDM_LOBBY_UNREGISTER:
                    if( SUCCEEDED( hr = UnRegisterProgramWithLobby() ) )
                        MessageBox( hDlg, TEXT("Application lobby information removed."),
                                    TEXT("DirectPlay Tutorial"), MB_OK );
                    else
                        OutputError( TEXT("Unregister failed"), hr );
                    break;

                case IDC_CLEAR:
                    ClearCanvas();
                    return TRUE;

                case IDC_COLOR_RED:
                case IDC_COLOR_GREEN:
                case IDC_COLOR_BLUE:
                case IDC_COLOR_BLACK:
                case IDC_COLOR_GRAY:
                case IDC_COLOR_WHITE:
                    HandleColorSelect( LOWORD(wParam) );
                    return TRUE;

                case IDOK:
                case IDCANCEL:
                    PostQuitMessage( 0 );
                    return TRUE;
            }
            break;

        case WM_DRAWITEM:
        {
            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT) lParam;
            HBRUSH hbrColor = NULL;
            
            switch( wParam )
            {   
                case IDC_COLOR_RED: 
                    hbrColor = CreateSolidBrush( RGB(255, 0, 0) );
                    break;
                    
                case IDC_COLOR_GREEN: 
                    hbrColor = CreateSolidBrush( RGB(0, 255, 0) );
                    break;

                case IDC_COLOR_BLUE: 
                    hbrColor = CreateSolidBrush( RGB(0, 0, 255) );
                    break;

                case IDC_COLOR_BLACK: 
                    hbrColor = CreateSolidBrush( RGB(0, 0, 0) );
                    break;

                case IDC_COLOR_GRAY: 
                    hbrColor = CreateSolidBrush( RGB(128, 128, 128) );
                    break;

                case IDC_COLOR_WHITE: 
                    hbrColor = CreateSolidBrush( RGB(255, 255, 255) );
                    break;
            }

            HBRUSH hbrOld;

            // If the current color is the highlighted color, draw the
            // highlight frame
            if( wParam == g_dwSelColorCtrl )
            {
                HBRUSH hbrHighlight;
                hbrHighlight = CreateSolidBrush( RGB(255, 255, 0) );
                
                if( hbrHighlight )
                {
                    hbrOld = (HBRUSH) SelectObject( pdis->hDC, hbrHighlight );
                    FillRect( pdis->hDC, &pdis->rcItem, hbrHighlight );
                    InflateRect( &pdis->rcItem, -2, -2 );
                    DeleteObject( SelectObject( pdis->hDC, hbrOld ) );
                    hbrHighlight = NULL;
                }
            }

            // Draw the paintbrush color on the button face
            if( hbrColor != NULL )
            {   
                hbrOld = (HBRUSH) SelectObject( pdis->hDC, hbrColor );
                FillRect( pdis->hDC, &pdis->rcItem, hbrColor );
                DeleteObject( SelectObject( pdis->hDC, hbrOld ) );
                hbrColor = NULL;    
            }

            return TRUE;
        }

        
    }

    return FALSE;
}




//-----------------------------------------------------------------------------
// Name: CanvasWndProc
// Desc: Canvas window subclass proceedure. 
//-----------------------------------------------------------------------------
INT_PTR CALLBACK CanvasWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch(msg)
    {
        case WM_LBUTTONDOWN:
            g_bLMouseDown = TRUE;
            return TRUE;

        case WM_LBUTTONUP:
            g_bLMouseDown = FALSE;
            return TRUE;

        case WM_MOUSEMOVE:
        {
            // If the left mouse button is down
            if( g_bLMouseDown )
            {
                POINT pt;
                
                pt.x = GET_X_LPARAM(lParam);
                pt.y = GET_Y_LPARAM(lParam);

                // Update the UI
                DrawPoint( pt, g_dwCurColor );   

                // Add this point to the send buffer
                if( g_SendBuffer.dwNumPoints < SEND_BUFFER_SIZE )
                {
                    g_SendBuffer.points[ g_SendBuffer.dwNumPoints ].dwColor = g_dwCurColor;
                    g_SendBuffer.points[ g_SendBuffer.dwNumPoints ].dwX = pt.x;
                    g_SendBuffer.points[ g_SendBuffer.dwNumPoints ].dwY = pt.y;
                    g_SendBuffer.dwNumPoints++;
                }  
            }

            return TRUE;
        }
    }

    return CallWindowProc(g_oldCanvasProc, hWnd, msg, wParam, lParam);

}




//-----------------------------------------------------------------------------
// Name: HandleColorSelect
// Desc: Handle a new color selection 
//-----------------------------------------------------------------------------
void HandleColorSelect( DWORD dwSelected )
{
    // Invalidate the old and new color buttons
    DWORD dwOldSelection = g_dwSelColorCtrl;
    g_dwSelColorCtrl = dwSelected;
    InvalidateRect( GetDlgItem( g_hDlg, dwOldSelection ), NULL, FALSE );
    InvalidateRect( GetDlgItem( g_hDlg, dwSelected ), NULL, FALSE );

    // Set the current brush color
    switch( dwSelected )
    {
        case IDC_COLOR_RED:   g_dwCurColor = MAKE_RGB(255,   0,   0); break;
        case IDC_COLOR_GREEN: g_dwCurColor = MAKE_RGB(  0, 255,   0); break;
        case IDC_COLOR_BLUE:  g_dwCurColor = MAKE_RGB(  0,   0, 255); break;
        case IDC_COLOR_BLACK: g_dwCurColor = MAKE_RGB(  0,   0,   0); break;
        case IDC_COLOR_GRAY:  g_dwCurColor = MAKE_RGB(128, 128, 128); break;
        case IDC_COLOR_WHITE: g_dwCurColor = MAKE_RGB(255, 255, 255); break;
    }
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
            pMsg = (PDPNMSG_RECEIVE) pMsgBuffer;
            
            GAMEMSG_GENERIC* pMsgGeneric = (GAMEMSG_GENERIC*) pMsg->pReceiveData;
            
            switch( pMsgGeneric->nType )
            {
                case GAME_MSGID_PAINT:
                    GAMEMSG_PAINT* pMsgPaint = (GAMEMSG_PAINT*) pMsg->pReceiveData;

                    for( UINT i=0; i < pMsgPaint->dwNumPoints; i++ )
                    {
                        POINT pt = {pMsgPaint->points[i].dwX, pMsgPaint->points[i].dwY};
                        DrawPoint( pt, pMsgPaint->points[i].dwColor );
                    }
                    break;
            }

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
// Name: LobbyAppMessageHandler
// Desc: Handler for DirectPlay lobby messages
//-----------------------------------------------------------------------------
HRESULT WINAPI LobbyAppMessageHandler(PVOID pvUserContext, DWORD dwMessageId, PVOID pMsgBuffer)
{
    HRESULT     hr = S_OK;

    switch (dwMessageId)
    {
        case DPL_MSGID_CONNECT:
        {
            PDPL_MESSAGE_CONNECT        pConnectMsg;
            PDPL_CONNECTION_SETTINGS    pSettings;

            pConnectMsg = (PDPL_MESSAGE_CONNECT)pMsgBuffer;
            pSettings = pConnectMsg->pdplConnectionSettings;

            // Register the lobby with directplay so we get automatic notifications
            hr = g_pDP->RegisterLobby(pConnectMsg->hConnectId, g_pLobbyApp, DPNLOBBY_REGISTER);
            break;
        }
    }
    return hr;
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
    
    if( g_SendBuffer.dwNumPoints > 0 )
    {
        // Initialize outgoing data
        g_SendBuffer.nType = GAME_MSGID_PAINT;
        dpnBuffer.pBufferData = (BYTE*) &g_SendBuffer;
        dpnBuffer.dwBufferSize = sizeof(GAMEMSG_GENERIC) + 
                                 sizeof(DWORD) +
                                 g_SendBuffer.dwNumPoints * sizeof(PAINT_POINT);
        
        DPNHANDLE hAsync;
        if( FAILED( hr = g_pDP->SendTo( DPNID_ALL_PLAYERS_GROUP, // dpnid
                                        &dpnBuffer,             // pBufferDesc
                                        1,                      // cBufferDesc
                                        0,                      // dwTimeOut
                                        NULL,                   // pvAsyncContext
                                        &hAsync,                // pvAsyncHandle
                                        DPNSEND_NOLOOPBACK ) ) )    // dwFlags
        {
            OutputError( TEXT("Failed Sending Data"), hr );
            return hr;
        }
    }

    // Clear the buffer
    g_SendBuffer.dwNumPoints = 0;

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

}




//-----------------------------------------------------------------------------
// Name: RegisterProgramWithLobby()
// Desc: Register app as lobby launchable
//-----------------------------------------------------------------------------
HRESULT RegisterProgramWithLobby()
{
    DPL_PROGRAM_DESC    dplDesc = {0};
    dplDesc.dwSize = sizeof(DPL_PROGRAM_DESC);
    dplDesc.guidApplication = g_guidApp;

    // Set the application friendly name and executable filename
    dplDesc.pwszApplicationName = g_wstrAppName;
    dplDesc.pwszExecutableFilename = g_wstrExecutable;

    TCHAR strPath[ MAX_PATH ] = {0};
    WCHAR wstrPath[ MAX_PATH ] = {0};

    // Determine the launch path from the location of the executable
    if( !GetModuleFileName( NULL, strPath, MAX_PATH ) )
        return E_FAIL;

    // Separate the path from the filename
    TCHAR* strLastSlash = _tcsrchr( strPath, TEXT('\\') );
    if( strLastSlash == NULL )
        return E_FAIL;

    // Slice off executable name
    *strLastSlash = TEXT('\0');
    
    DXUtil_ConvertGenericStringToWideCch( wstrPath, strPath, MAX_PATH ); 
    dplDesc.pwszExecutablePath = wstrPath;

    return g_pLobbyApp->RegisterProgram(&dplDesc, 0);   
}




//-----------------------------------------------------------------------------
// Name: UnRegisterProgramWithLobby()
// Desc: Unregister app as lobby launchable
//-----------------------------------------------------------------------------
HRESULT UnRegisterProgramWithLobby()
{
    HRESULT     hr = S_OK;

    hr = g_pLobbyApp->UnRegisterProgram(&g_guidApp, 0);

    return hr;
}




//-----------------------------------------------------------------------------
// Name: LobbyLaunch()
// Desc: Host or connect to session based on lobby launch settings
//-----------------------------------------------------------------------------
HRESULT LobbyLaunch()
{
    HRESULT                     hr = S_OK;
    DPL_CONNECTION_SETTINGS*    pSettings = NULL;
    DWORD                       dwSettingsSize = 0;

    // Get the lobby connection data
    // First see how big a buffer we need
    hr = g_pLobbyApp->GetConnectionSettings(g_hLobbyHandle, pSettings, &dwSettingsSize, 0);

    if( hr != DPNERR_BUFFERTOOSMALL)
    {
        OutputError( TEXT("Failed GetConnectionSettings"), hr);
        goto LCleanup;
    }

    pSettings = (DPL_CONNECTION_SETTINGS*) new BYTE[dwSettingsSize];

    if( pSettings == NULL)
    {
        OutputError( TEXT("Failed Allocating Buffer.") );
        hr = E_FAIL;
        goto LCleanup;
    }

    if( FAILED( hr = g_pLobbyApp->GetConnectionSettings(g_hLobbyHandle, pSettings, &dwSettingsSize, 0 ) ) )
    {
        OutputError( TEXT("Failed GetConnectionSettings"), hr );
        goto LCleanup;
    }

    if( pSettings->dwFlags & DPLCONNECTSETTINGS_HOST)
    {
        // We are to host the game
        if( FAILED( hr = g_pDP->Host(&pSettings->dpnAppDesc,        // dpnAppDesc
                                    pSettings->ppdp8DeviceAddresses,// prgpDeviceInfo
                                    pSettings->cNumDeviceAddresses, // cDeviceInfo
                                    NULL, NULL,                     // Security
                                    NULL,                           // pvPlayerContext
                                    0 ) ) )                         // dwFlags
        {
            OutputError( TEXT("Failed Host"), hr );
            goto LCleanup;
        }


        DXUtil_ConvertWideStringToGenericCch( g_strSession, pSettings->dpnAppDesc.pwszSessionName, 128 );
        g_bHosting = true;
    }
    else
    {
        // We need to connect
        if( FAILED( hr = g_pDP->Connect(&pSettings->dpnAppDesc,             // pdnAppDesc
                                        pSettings->pdp8HostAddress,         // pHostAddr
                                        pSettings->ppdp8DeviceAddresses[0], // pDeviceInfo
                                        NULL, NULL,                         // Security
                                        NULL, 0,                            // pvUserConnectData/Size
                                        NULL,                               // pvPlayerContext
                                        NULL, NULL,                         // pvAsyncContext/Handle
                                        DPNCONNECT_SYNC ) ) )               // dwFlags
        {
            OutputError( TEXT("Failed Lobby App Connect"), hr );
            goto LCleanup;
        }

        DXUtil_ConvertWideStringToGenericCch( g_strSession, pSettings->dpnAppDesc.pwszSessionName, 128 );
        g_bConnected = true;

    }
LCleanup:
    if( pSettings)
    {
        SAFE_RELEASE(pSettings->pdp8HostAddress);

        for (DWORD dwIndex = 0; dwIndex < pSettings->cNumDeviceAddresses; dwIndex++)
        {
            SAFE_RELEASE(pSettings->ppdp8DeviceAddresses[dwIndex]);
        }
    }
    SAFE_DELETE_ARRAY(pSettings);
    return hr;
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
    }

    EnableWindow( GetDlgItem( g_hDlg, IDC_CONNECT ), !(g_bHosting | g_bConnected) );
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Render the current frame
//-----------------------------------------------------------------------------
HRESULT Render()
{
    HDC hDCDest = GetDC( GetDlgItem( g_hDlg, IDC_CANVAS ) );
    HDC hDCSrc = CreateCompatibleDC(NULL);

    HBITMAP hBmpOld = (HBITMAP) SelectObject( hDCSrc, g_hBmpCanvas );
    
    BitBlt( hDCDest, 
            0, 0, 
            g_dwCanvasWidth, 
            g_dwCanvasHeight, 
            hDCSrc, 
            0, 0, 
            SRCCOPY );

    SelectObject( hDCSrc, hBmpOld );
    DeleteDC( hDCSrc );
    ReleaseDC( GetDlgItem( g_hDlg, IDC_CANVAS ), hDCDest );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DrawPoint()
// Desc: Draw the colored point to the canvas
//-----------------------------------------------------------------------------
HRESULT DrawPoint( POINT pt, DWORD dwColor )
{
    DWORD dwBytesPerLine = (g_dwCanvasWidth * 3) + (g_dwCanvasWidth % 4);

    // Update the UI
    for( int x = -1; x <= 1; x++ )
    {
        for( int y = -1; y <= 1; y++ )
        {
            int newX = pt.x + x;
            int newY = pt.y + y;

            if( newX >= 0 && newX < (int)g_dwCanvasWidth &&
                newY >= 0 && newY < (int)g_dwCanvasHeight )
            {
                CopyMemory( (void*)&g_pCanvasData[ (newY * dwBytesPerLine) + (newX * 3) ],
                            &dwColor, 3 );
            }
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ClearCanvas()
// Desc: Clear the shared canvas
//-----------------------------------------------------------------------------
HRESULT ClearCanvas()
{
    DWORD dwBytesPerLine = (g_dwCanvasWidth * 3) + (g_dwCanvasWidth % 4);

    FillMemory( (void*)g_pCanvasData,                  
                dwBytesPerLine * g_dwCanvasHeight, 
                0xff );
   

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateCanvas()
// Desc: Create the canvas bitmap
//-----------------------------------------------------------------------------
HRESULT CreateCanvas()
{
    // Start clean
    if( g_hBmpCanvas != NULL )
    {
        DeleteObject( g_hBmpCanvas );
        g_hBmpCanvas = NULL;
        g_pCanvasData = NULL;
    }

    HDC hDC = CreateCompatibleDC( NULL );
    BITMAPINFOHEADER bi = {0};

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = g_dwCanvasWidth;
    bi.biHeight = - (int)g_dwCanvasHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;

    g_hBmpCanvas = CreateDIBSection( hDC, 
                                     (BITMAPINFO*) &bi, 
                                     DIB_RGB_COLORS, 
                                     (VOID**) &g_pCanvasData, 
                                     NULL, 0 );

    if( NULL == g_hBmpCanvas )
    {
        OutputError( TEXT("CreateDIBSection failed") );
        return E_FAIL;
    }

    ClearCanvas();

    DeleteDC( hDC );
    return S_OK;
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

    // Create the thread pool interface
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlay8ThreadPool, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlay8ThreadPool,
                                       (LPVOID*) &g_pThreadPool ) ) )
    {
        OutputError( TEXT("Failed Creating the IDirectPlay8ThreadPool Object"), hr );
        return hr;
    }
  
    // Create the IDirectPlay8LobbiedApplication Object
    if( FAILED( hr = CoCreateInstance(CLSID_DirectPlay8LobbiedApplication, NULL, 
                                    CLSCTX_INPROC_SERVER,
                                    IID_IDirectPlay8LobbiedApplication, 
                                    (LPVOID*) &g_pLobbyApp ) ) )
    {
        OutputError( TEXT("Failed Creating the IDirectPlay8LobbiedApplication Object") , hr );
        return hr;
    }

    // Init ThreadPool
    if( FAILED( hr = g_pThreadPool->Initialize(NULL, DirectPlayMessageHandler, 0 ) ) )
    {
        OutputError( TEXT("Failed Initializing ThreadPool"), hr );
        return hr;
    }

    // Init DirectPlay
    if( FAILED( hr = g_pDP->Initialize(NULL, DirectPlayMessageHandler, 0 ) ) )
    {
        OutputError( TEXT("Failed Initializing DirectPlay"), hr );
        return hr;
    }

    // Init the Lobby interface
    if( FAILED( hr = g_pLobbyApp->Initialize(NULL, LobbyAppMessageHandler, &g_hLobbyHandle, 0 ) ) )
    {
        OutputError( TEXT("Failed Initializing Lobby"), hr );
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
  
    // Turn off worker DirectPlay worker threads since we'll be using the DoWork
    // method to synchronously handle network messages. 
    if( FAILED( hr = g_pThreadPool->SetThreadCount( (DWORD) -1, 0, 0 ) ) )
    {
        OutputError( TEXT("Failed calling SetThreadCount"), hr );
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
        g_pDP->Close(0);

    if( g_pThreadPool )
        g_pThreadPool->Close(0);

    if( g_pLobbyApp)
        g_pLobbyApp->Close(0);

    ClearHostList();

    SAFE_RELEASE(g_pDeviceAddress);
    SAFE_RELEASE(g_pHostAddress);
    SAFE_RELEASE(g_pDP);
    SAFE_RELEASE(g_pThreadPool);
    SAFE_RELEASE(g_pLobbyApp);

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


