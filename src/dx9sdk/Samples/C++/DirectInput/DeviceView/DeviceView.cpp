//-----------------------------------------------------------------------------
// File: DeviceView.cpp
//
// Desc: A simple custom device configuration UI using the DIDevImage framework
//
// Copyright (c) 2000-2001 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <dinput.h>
#include "didevimg.h"
#include "resource.h"

// {8C176D45-4AB1-4868-BCC1-C8ED85285BB1}
static const GUID g_guidApp = 
{ 0x8c176d45, 0x4ab1, 0x4868, { 0xbc, 0xc1, 0xc8, 0xed, 0x85, 0x28, 0x5b, 0xb1 } };

// Full range of axis data values
const int AXIS_RANGE = 200;


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECTINPUT8        g_pDI             = NULL;  // DirectInput access pointer
LPDIRECTINPUTDEVICE8  g_pDevices[10]    = {0};   // List of devices
DIACTIONFORMAT        g_diaf            = {0};   // DIACTIONFORMAT structure
CDIDevImage           g_DIDevImages[10];         // Image drawing framework
DWORD                 g_dwNumDevices    = 0;     // Total number of devices
DWORD                 g_dwCurDevice     = 0;     // Index of current device
HWND                  g_hDlg            = 0;     // Handle of the dialog
HINSTANCE             g_hInst           = 0;     // Program instance
DWORD                 g_dwCurTooltip    = 0;     // Current tooltip object
DWORD                 g_dwCurHighlight  = 0;     // Currently highlighted object
BOOL                  g_bHidden[10]     = {0};   // Stores the visual state of
                                                 //   the checkbox



// Game action constants
enum GAME_ACTIONS {
WALK,               // Separate inputs are needed in this case for
WALK_LEFT,          //   Walk/Left/Right because the joystick uses an
WALK_RIGHT,         //   axis to report both left and right, but the
BLOCK,              //   keyboard will use separate arrow keys.
KICK, 
PUNCH, 
THE_DEAPPETIZER,    // "The De-Appetizer" represents a special move
APOLOGIZE,          //   defined by this game.
QUIT,
NUM_OF_ACTIONS
};

// Friendly names for action constants are used by DirectInput for the
// built-in configuration UI
const TCHAR *ACTION_NAMES[] =
{
    TEXT("Walk left/right"),
    TEXT("Walk left"),
    TEXT("Walk right"),
    TEXT("Block"),
    TEXT("Kick"),
    TEXT("Punch"),
    TEXT("\"The De-Appetizer\""),
    TEXT("Apologize"),
    TEXT("Quit")
};


// Map the game actions to the genre and keyboard constants.
DIACTION g_adiaActionMap[] =
{
    // Device input (joystick, etc.) that is pre-defined by DInput according
    // to genre type. The genre for this app is Action->Hand to Hand Fighting.
    { WALK,             DIAXIS_FIGHTINGH_LATERAL,     0,  ACTION_NAMES[WALK], },
    { BLOCK,            DIBUTTON_FIGHTINGH_BLOCK,     0,  ACTION_NAMES[BLOCK], },
    { KICK,             DIBUTTON_FIGHTINGH_KICK,      0,  ACTION_NAMES[KICK], },
    { PUNCH,            DIBUTTON_FIGHTINGH_PUNCH,     0,  ACTION_NAMES[PUNCH], },
    { THE_DEAPPETIZER,  DIBUTTON_FIGHTINGH_SPECIAL1,  0,  ACTION_NAMES[THE_DEAPPETIZER], },

    // Map the apologize button to any button on the device. DirectInput
    // defines several "Any-Control Constants" for mapping game actions to
    // any device object of a particular type.
    { APOLOGIZE,        DIBUTTON_ANY(1),              0,  ACTION_NAMES[APOLOGIZE], },

    // Keyboard input mappings
    { WALK_LEFT,        DIKEYBOARD_LEFT,              0,  ACTION_NAMES[WALK_LEFT], },
    { WALK_RIGHT,       DIKEYBOARD_RIGHT,             0,  ACTION_NAMES[WALK_RIGHT], },
    { BLOCK,            DIKEYBOARD_B,                 0,  ACTION_NAMES[BLOCK], },
    { KICK,             DIKEYBOARD_K,                 0,  ACTION_NAMES[KICK], },
    { PUNCH,            DIKEYBOARD_P,                 0,  ACTION_NAMES[PUNCH], },
    { THE_DEAPPETIZER,  DIKEYBOARD_H,                 0,  ACTION_NAMES[THE_DEAPPETIZER], },
    { APOLOGIZE,        DIKEYBOARD_A,                 0,  ACTION_NAMES[APOLOGIZE], },

    // The DIA_APPFIXED constant can be used to instruct DirectInput that the
    // current mapping can not be changed by the user.
    { QUIT,             DIKEYBOARD_Q,      DIA_APPFIXED,  ACTION_NAMES[QUIT], },

    // Mouse input mappings
    { WALK,             DIMOUSE_XAXIS,                0,  ACTION_NAMES[WALK], },
    { PUNCH,            DIMOUSE_BUTTON0,              0,  ACTION_NAMES[PUNCH], },
    { KICK,             DIMOUSE_BUTTON1,              0,  ACTION_NAMES[KICK], },
};
inline DWORD GetNumOfMappings() { return sizeof(g_adiaActionMap)/sizeof(DIACTION); }

// Function prototypes
BOOL    CALLBACK EnumDevicesCallback( LPCDIDEVICEINSTANCE, LPDIRECTINPUTDEVICE8, DWORD, DWORD, LPVOID );
BOOL    CALLBACK InitAxes( LPCDIDEVICEOBJECTINSTANCE pddoi, LPVOID pvRef ); 
HRESULT InitDirectInput();
VOID    CheckInput();
VOID    OnTabChange();
VOID    OnViewChange();
VOID    RefreshViews();
VOID    ResizeDeviceImage();
BOOL    CALLBACK ToggleUnmapped( LPCDIDEVICEOBJECTINSTANCE pddoi, LPVOID pvRef );
VOID    Cleanup();





//-----------------------------------------------------------------------------
// Name: MainDialogProc
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    POINT pt;
    DWORD dwObj;
    DWORD dwState;
    RECT  rcImage = {0};
    HWND  hwndImage = NULL;

    switch( msg ) 
    {
        case WM_INITDIALOG:

            g_hDlg = hDlg;

            // Load and set the icon
            HICON hIcon;
            hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE( IDI_MAIN ) );
            SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
            SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

            // Initialize DirectInput
            if( FAILED( InitDirectInput() ) )
            {
                MessageBox( NULL, TEXT("Error Initializing DirectInput"), 
                            TEXT("DirectInput Sample"), MB_ICONERROR | MB_OK );
                EndDialog( hDlg, 0 );
            }

            
            // Set a timer to go off 30 times a second. At every timer message
            // the input device will be read
            SetTimer( hDlg, 0, 1000 / 30, NULL );

            return TRUE;

        case WM_TIMER:
            // Update the input device every timer message
            CheckInput();
            return TRUE;

        case WM_DRAWITEM:
            HDC hdc;

            hdc = ((LPDRAWITEMSTRUCT) lParam)->hDC;   
            g_DIDevImages[ g_dwCurDevice ].RenderToDC( hdc );
            return TRUE;

        case WM_MOUSEMOVE:      
            dwObj = 0;
            dwState = 0;

            hwndImage = GetDlgItem( hDlg, IDC_IMAGE );
            GetWindowRect( hwndImage, &rcImage );
               
            pt.x = GET_X_LPARAM(lParam);
            pt.y = GET_Y_LPARAM(lParam);

            ClientToScreen( hDlg, &pt );

            pt.x -= rcImage.left;
            pt.y -= rcImage.top;

            // Tooltip logic
            
            // If the current mouse pointer is within an object callout
            if( SUCCEEDED( g_DIDevImages[ g_dwCurDevice ].GetObjFromPoint( pt, &dwObj ) ) )
            {
                // And if the mouse is over a different object than the current tooltip
                // object
                if( g_dwCurTooltip != dwObj )
                {         
                    // Remove the tooltip from the last object
                    g_DIDevImages[ g_dwCurDevice ].GetCalloutState( g_dwCurTooltip, &dwState );
                    g_DIDevImages[ g_dwCurDevice ].SetCalloutState( g_dwCurTooltip, dwState & ~DIDICOS_TOOLTIP );
                    g_dwCurTooltip = 0;

                    // Set the tooltip for the current object
                    g_DIDevImages[ g_dwCurDevice ].GetCalloutState( dwObj, &dwState );
                    g_DIDevImages[ g_dwCurDevice ].SetCalloutState( dwObj, dwState | DIDICOS_TOOLTIP );
                    g_dwCurTooltip = dwObj;

                    // Repaint
                    InvalidateRect( hwndImage, NULL, FALSE );
                }
            }
            else
            {
                // The mouse isn't over any callouts. If there is a current tooltip object,
                // clear it.
                if( g_dwCurTooltip != 0 )
                {   
                    g_DIDevImages[ g_dwCurDevice ].GetCalloutState( g_dwCurTooltip, &dwState );
                    g_DIDevImages[ g_dwCurDevice ].SetCalloutState( g_dwCurTooltip, dwState & ~DIDICOS_TOOLTIP );
                    g_dwCurTooltip = 0;

                    // Repaint
                    InvalidateRect( hwndImage, NULL, FALSE );
                }
            }

            return TRUE; // Message handled

        case WM_LBUTTONDOWN:
            
            dwObj = 0;
            dwState = 0;
 
            hwndImage = GetDlgItem( hDlg, IDC_IMAGE );
            GetWindowRect( hwndImage, &rcImage );
               
            pt.x = GET_X_LPARAM(lParam); 
            pt.y = GET_Y_LPARAM(lParam); 

            ClientToScreen( hDlg, &pt );

            pt.x -= rcImage.left;
            pt.y -= rcImage.top;

            if( SUCCEEDED( g_DIDevImages[ g_dwCurDevice ].GetObjFromPoint( pt, &dwObj ) ) )
            {
                // We have selected a new object to be highlighted. Un-highlight the old one
                if( g_dwCurHighlight )
                {
                    g_DIDevImages[ g_dwCurDevice ].GetCalloutState( g_dwCurHighlight, &dwState );
                    g_DIDevImages[ g_dwCurDevice ].SetCalloutState( g_dwCurHighlight, dwState & ~DIDICOS_HIGHLIGHTED );
                }

                // Set the highlight flag
                g_dwCurHighlight = dwObj;
                g_DIDevImages[ g_dwCurDevice ].GetCalloutState( dwObj, &dwState );
                g_DIDevImages[ g_dwCurDevice ].SetCalloutState( dwObj, dwState | DIDICOS_HIGHLIGHTED );
            
                // Repaint
                InvalidateRect( hwndImage, NULL, FALSE );
            }

            return TRUE;

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
                    EndDialog( hDlg, 0 );
                    return TRUE;

                case IDC_HIDE:
                    // User has selected to toggle the visibility of device 
                    // objects which were not mapped to actions
                    
                    // Build the action map against the device, and enumerate
                    // through the objects with the ToggleUnmapped callback
                    if( SUCCEEDED(g_pDevices[ g_dwCurDevice ]->BuildActionMap( &g_diaf, NULL, DIDBAM_DEFAULT )) )    
                        g_pDevices[ g_dwCurDevice ]->EnumObjects( ToggleUnmapped, 0, DIDFT_ALL );
                
                    // Store checkbox state
                    g_bHidden[ g_dwCurDevice ] = !g_bHidden[ g_dwCurDevice ];

                    // This could have changed the number of views
                    RefreshViews();

                    // Repaint
                    hwndImage = GetDlgItem( g_hDlg, IDC_IMAGE );
                    InvalidateRect( hwndImage, NULL, FALSE );   
                    return TRUE;
      
                case IDC_CURVIEW:
                    switch( HIWORD(wParam) )
                    {
                        case EN_CHANGE:
                            // This could be reached before INITDIALOG
                            if( g_hDlg )
                                OnViewChange();
                            return TRUE;
                    }
                    break;
            }
            break;

        case WM_NOTIFY:
            switch( wParam )
            {
                case IDC_DEVICES:
                    switch( ((LPNMHDR)lParam)->code )
                    {
                        case TCN_SELCHANGE:
                            // User has selected one of the device tabs
                            OnTabChange();
                            return TRUE;
                
                    }
                    break;
            }
            break;

        case WM_DESTROY:
            // Cleanup everything
            KillTimer( hDlg, 0 );    
            Cleanup();    
            return TRUE;    
    }

    return FALSE; // Message not handled 
}





//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------
int APIENTRY WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{
    g_hInst = hInst;

    InitCommonControls();

    // Display the main dialog box.
    DialogBox( hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc );
    
    return TRUE;
}





//-----------------------------------------------------------------------------
// Name: InitDirectInput
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
HRESULT InitDirectInput()
{
    HRESULT hr;

    // Register with the DirectInput subsystem and get a pointer to an 
    // IDirectInput interface we can use.
    if( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
                                         IID_IDirectInput8, (VOID**)&g_pDI, NULL ) ) )
        return hr;


    // ************************************************************************
    // Step 3: Enumerate Devices.
    // 
    // Enumerate through devices according to the desired action map.
    // Devices are enumerated in a prioritized order, such that devices which
    // can best be mapped to the provided action map are returned first.
    // ************************************************************************

    // Setup action format for the actual gameplay
    ZeroMemory( &g_diaf, sizeof(DIACTIONFORMAT) );
    g_diaf.dwSize          = sizeof(DIACTIONFORMAT);
    g_diaf.dwActionSize    = sizeof(DIACTION);
    g_diaf.dwDataSize      = GetNumOfMappings() * sizeof(DWORD);
    g_diaf.guidActionMap   = g_guidApp;
    g_diaf.dwGenre         = DIVIRTUAL_FIGHTING_HAND2HAND; 
    g_diaf.dwNumActions    = GetNumOfMappings();
    g_diaf.rgoAction       = g_adiaActionMap;
    g_diaf.lAxisMin        = -99;
    g_diaf.lAxisMax        = 99;
    g_diaf.dwBufferSize    = 16;
    lstrcpy( g_diaf.tszActionMap, TEXT("ActionMap Sample") );
 
       
    if( FAILED( hr = g_pDI->EnumDevicesBySemantics( NULL, &g_diaf,  
                                                    EnumDevicesCallback,
                                                    NULL, DIEDBSFL_ATTACHEDONLY ) ) )
        return hr;
    
    // For each detected device, set the display settings
    RECT rc = {0};
    ResizeDeviceImage();

    GetWindowRect( GetDlgItem( g_hDlg, IDC_IMAGE ), &rc );

    for( UINT i=0; i < g_dwNumDevices; i++ )
    { 
        // Set the output image size to match the client area of the tab control
        g_DIDevImages[i].SetOutputImageSize( rc.right - rc.left, 
                                             rc.bottom - rc.top, 
                                             DIDISOIS_RESIZE );

        // Set the background color to match the dialog background. Since the 
        // device image framework allows for transparent backgrounds, the background
        // color is passed as a D3DCOLOR value. The framework provides an function
        // to convert between D3DCOLOR and COLORREF types.
        g_DIDevImages[i].SetColors( ColorFromCR( GetSysColor( COLOR_BTNFACE ) ), 
                                    RGB(100, 100, 100), RGB(200, 0, 0) );
    }
    OnTabChange();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: EnumDevicesCallback
// Desc: Callback function for EnumDevices. This particular function stores
//       a list of all currently attached devices for use on the input chart.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumDevicesCallback( LPCDIDEVICEINSTANCE lpddi, 
                                  LPDIRECTINPUTDEVICE8 lpdid, DWORD dwFlags, 
                                  DWORD dwRemaining, LPVOID pvRef )
{
    HRESULT hr;
    TCITEM tcItem         = {0};

    // Build the action map against the device
    if( FAILED(hr = lpdid->BuildActionMap( &g_diaf, NULL, DIDBAM_DEFAULT )) )
        // There was an error while building the action map. Ignore this
        // device, and contine with the enumeration
        return DIENUM_CONTINUE;

    // Set an appropriate data format for the device. Although we're using 
    // action mapping in order to label the device objects with game actions,
    // we need to use standard input methods in order to retrieve input from
    // unmapped device objects.
    switch( 0xff & lpddi->dwDevType )
    {
    case DI8DEVTYPE_KEYBOARD:
        lpdid->SetDataFormat( &c_dfDIKeyboard );
        break;
        
    case DI8DEVTYPE_MOUSE:
        lpdid->SetDataFormat( &c_dfDIMouse2 );
        break;

    default:
        lpdid->SetDataFormat( &c_dfDIJoystick2 );
        break;
    }

    // Set device properties
    DIPROPDWORD dipdw = {0};
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = 16;
    
    // Allocate a buffer for input events
    hr = lpdid->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
    if( FAILED(hr) )
        return DIENUM_CONTINUE;

    dipdw.dwData = DIPROPAXISMODE_REL;
    hr = lpdid->SetProperty( DIPROP_AXISMODE, &dipdw.diph );
    if( FAILED(hr) )
        return DIENUM_CONTINUE;
    
    // Set the range and axis mode for each axis object
    lpdid->EnumObjects( InitAxes, lpdid, DIDFT_AXIS );

    // Initialize the device image frame for the current device
    hr = g_DIDevImages[g_dwNumDevices].Init( lpdid );
    if( FAILED(hr) )
        return DIENUM_CONTINUE;

    // Enumerate through the actions to set the callout strings
    for( UINT i=0; i < g_diaf.dwNumActions; i++) 
    {
        DIACTION *dia = &g_diaf.rgoAction[i];
        g_DIDevImages[g_dwNumDevices].SetCalloutText( dia->dwObjID, dia->lptszActionName );
    } 
    
    // The current device has been successfully mapped. By storing the
    // pointer and informing COM that we've added a reference to the 
    // device, we can use this pointer later when gathering input.
    g_pDevices[g_dwNumDevices] = lpdid;
    lpdid->AddRef();

    tcItem.mask    = TCIF_TEXT;
    tcItem.pszText = (TCHAR*) lpddi->tszInstanceName;

    // Create a tab for this device
    SendMessage( GetDlgItem( g_hDlg, IDC_DEVICES ), TCM_INSERTITEM, (WPARAM) g_dwNumDevices, (LPARAM) &tcItem );

    // Increment the global device counter
    g_dwNumDevices++;

    // Ask for the next device
    return DIENUM_CONTINUE;
}




//-----------------------------------------------------------------------------
// Name: InitAxes
// Desc: Callback for EnumObjects sets the axis range and relative input mode.
//-----------------------------------------------------------------------------
BOOL CALLBACK InitAxes( LPCDIDEVICEOBJECTINSTANCE pddoi, LPVOID pvRef )
{
    DIPROPRANGE dipr = {0};
    LPDIRECTINPUTDEVICE8 pdid = (LPDIRECTINPUTDEVICE8) pvRef;

    dipr.diph.dwSize = sizeof(DIPROPRANGE);
    dipr.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipr.diph.dwObj = pddoi->dwType;
    dipr.diph.dwHow = DIPH_BYID;
    dipr.lMin = - (AXIS_RANGE / 2);
    dipr.lMax = (AXIS_RANGE / 2);

    pdid->SetProperty( DIPROP_RANGE, &dipr.diph );
    
    return DIENUM_CONTINUE;
}




//-----------------------------------------------------------------------------
// Name: CheckInput
// Desc: Poll the attached devices and update the display
//-----------------------------------------------------------------------------
void CheckInput()
{
    HRESULT hr;
    BOOL bRender = FALSE;
 
    LPDIRECTINPUTDEVICE8 pdidDevice = g_pDevices[g_dwCurDevice];
    if( !pdidDevice )
        return;

    DIDEVICEOBJECTDATA rgdod[16];
    DWORD   dwItems = 16;

    hr = pdidDevice->Acquire();  
    hr = pdidDevice->Poll();
    hr = pdidDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA),
                                    rgdod, &dwItems, 0 );

    
    // GetDeviceData can fail for several reasons, some of which are
    // expected during a program's execution. A device's acquisition is not
    // permanent, and your program might need to reacquire a device several
    // times. Since this sample is polling frequently, an attempt to
    // acquire a lost device will occur during the next call to CheckInput.
    if( FAILED(hr) )
        return;

    bRender = FALSE;
    for( DWORD j=0; j<dwItems; j++ )
    {
        bRender = TRUE;
        DIDEVICEOBJECTINSTANCE didoi = {0};
        didoi.dwSize = sizeof(DIDEVICEOBJECTINSTANCE);

        hr = pdidDevice->GetObjectInfo( &didoi, rgdod[j].dwOfs, DIPH_BYOFFSET );
        if( SUCCEEDED(hr) )
        {
            DWORD dwState = 0;
            BOOL  bHighlight = FALSE;
            
            // Determine whether the device object is active based on the 
            // object type
            if( didoi.dwType & DIDFT_BUTTON )
                bHighlight = rgdod[j].dwData & 0x80;
            else if( didoi.dwType & DIDFT_POV )
                bHighlight = rgdod[j].dwData != -1;
            else if( didoi.dwType & DIDFT_AXIS )
            {
                // Steering wheels and pedals are often harder to move
                // than joystick axes, and sometimes have half the 
                // resolution (so the full range of movement might be 
                // reported across half the data range). To compensate, 
                // we'll scale the threshold accordingly.
                if( didoi.dwType & DI8DEVTYPE_DRIVING )
                    bHighlight = labs( rgdod[j].dwData ) > (AXIS_RANGE / 20);
                else
                    bHighlight = labs( rgdod[j].dwData ) > (AXIS_RANGE / 5);
            }
          

            // Set or clear the highlight flag based on the object state
            if( bHighlight )
            {
                // Un-highlight the currently highlighted object
                if( g_dwCurHighlight )
                {
                    g_DIDevImages[g_dwCurDevice].GetCalloutState( g_dwCurHighlight, &dwState );
                    g_DIDevImages[g_dwCurDevice].SetCalloutState( g_dwCurHighlight, dwState & ~DIDICOS_HIGHLIGHTED );
                }

                g_dwCurHighlight = didoi.dwType;
                g_DIDevImages[g_dwCurDevice].GetCalloutState( didoi.dwType, &dwState );
                g_DIDevImages[g_dwCurDevice].SetCalloutState( didoi.dwType, dwState | DIDICOS_HIGHLIGHTED );
            }   
        }
    }

    if( bRender )
    {
        HWND hwndImage = GetDlgItem( g_hDlg, IDC_IMAGE );
        InvalidateRect( hwndImage, NULL, FALSE );   
    }
}




//-----------------------------------------------------------------------------
// Name: OnTabChange
// Desc: Handles tab change messages for switching the current device
//-----------------------------------------------------------------------------
VOID OnTabChange()
{
    HWND hwndTabs =  GetDlgItem( g_hDlg, IDC_DEVICES );
    HWND hwndImage = GetDlgItem( g_hDlg, IDC_IMAGE );
    HWND hwndHide  = GetDlgItem( g_hDlg, IDC_HIDE );
   
    // We're changing devices. Un-highlight the currently highlighted object
    if( g_dwCurHighlight )
    {
        DWORD dwState;
        g_DIDevImages[ g_dwCurDevice ].GetCalloutState( g_dwCurHighlight, &dwState );
        g_DIDevImages[ g_dwCurDevice ].SetCalloutState( g_dwCurHighlight, dwState & ~DIDICOS_HIGHLIGHTED );
        g_dwCurHighlight = 0;
    }

    // Get the currently selected device index
    g_dwCurDevice = SendMessage( hwndTabs, TCM_GETCURSEL, 0, 0 );

    // Set the checkbox state
    SendMessage( hwndHide, BM_SETCHECK, 
                 (WPARAM) ( g_bHidden[ g_dwCurDevice ] ? BST_CHECKED : BST_UNCHECKED ), 0 );

    RefreshViews();

    // Repaint and clear background
    InvalidateRect( hwndImage, NULL, TRUE );
}




//-----------------------------------------------------------------------------
// Name: OnViewChange
// Desc: Handles view change requests from the user
//-----------------------------------------------------------------------------
VOID OnViewChange()
{
    TCHAR strNextView[10] = {0};
    DWORD dwNextView = 0;

    DWORD dwCurView, dwNumOfViews;

    g_DIDevImages[ g_dwCurDevice ].GetActiveView( &dwCurView, &dwNumOfViews );
    dwCurView++; // Stored internally as an index. We need to increment.

    // The requested view is the current value of the IDC_CURVIEW control
    GetWindowText( GetDlgItem( g_hDlg, IDC_CURVIEW ), strNextView, 10 );
    dwNextView = _ttoi( strNextView );

    if( dwNextView != dwCurView )
    {
        // A new view has been requested. The number may or may not be valid.
        if( dwNextView > 0 && dwNextView <= dwNumOfViews )
        {
            // Valid request. Change the current view and repaint.
            // The offset is due to the discrpancy between viewed values and
            // internal indices.
            g_DIDevImages[ g_dwCurDevice ].SetActiveView( dwNextView-1 );
            InvalidateRect( GetDlgItem( g_hDlg, IDC_IMAGE ), NULL, FALSE );
        }
        else
        {
            // Invalid request. Revert the screen value to the current view.
            _itot( dwCurView, strNextView, 10 );
            SetWindowText( GetDlgItem( g_hDlg, IDC_CURVIEW ), strNextView );
        }
    }
}




//-----------------------------------------------------------------------------
// Name: RefreshViews
// Desc: Called after an action is taken that might change the number of views
//       available for the current device
//-----------------------------------------------------------------------------
VOID RefreshViews()
{
    DWORD dwCurView, dwNumOfViews;
    TCHAR strCurView[10], strNumOfViews[10];

    g_DIDevImages[ g_dwCurDevice ].GetActiveView( &dwCurView, &dwNumOfViews );
    
    // If the current view is invalid, reset
    if( dwCurView >= dwNumOfViews )
        g_DIDevImages[ g_dwCurDevice ].SetActiveView( dwCurView = 0 );
        
    dwCurView++; // Views are indexed from 0 up

    _itot( dwCurView, strCurView, 10 ); 
    _itot( dwNumOfViews, strNumOfViews, 10 );
  
    // Set the values for the current view, and number of views
    SetWindowText( GetDlgItem( g_hDlg, IDC_CURVIEW ), strCurView );
    SetWindowText( GetDlgItem( g_hDlg, IDC_MAXVIEW ), strNumOfViews );

    // Set the spin control ranges
    SendMessage( GetDlgItem( g_hDlg, IDC_SPIN ), UDM_SETRANGE, 0, 
                 (LPARAM) MAKELONG( (SHORT) dwCurView, (SHORT) dwNumOfViews ) );
}




//-----------------------------------------------------------------------------
// Name: ToggleUnmapped
// Desc: Callback function cycles through device objects and negates the
//       current visible flag for objects which are not mapped to an action.
//-----------------------------------------------------------------------------
BOOL CALLBACK ToggleUnmapped( LPCDIDEVICEOBJECTINSTANCE pddoi, LPVOID pvRef )
{

    // If action array has an object ID which matches the enumerated ID, then
    // the current device object has a corresponding action.
    for( UINT i=0; i < g_diaf.dwNumActions; i++) 
    {
        DIACTION *pdia = &g_diaf.rgoAction[i];

        if( pdia->dwHow == DIAH_ERROR || pdia->dwHow == DIAH_UNMAPPED )
            continue;
        
        if( pdia->dwObjID == pddoi->dwType )
            return DIENUM_CONTINUE;

    }

    // We're still here, so this object is unmapped
    DWORD dwState = 0;
    g_DIDevImages[ g_dwCurDevice ].GetCalloutState( pddoi->dwType, &dwState );

    if( dwState & DIDICOS_INVISIBLE )
        dwState &= ~DIDICOS_INVISIBLE;
    else
        dwState |= DIDICOS_INVISIBLE;

    g_DIDevImages[ g_dwCurDevice ].SetCalloutState( pddoi->dwType, dwState );

    return DIENUM_CONTINUE;
}




//-----------------------------------------------------------------------------
// Name: ResizeDeviceImage()
// Desc: Adjust the size and position of the device image based on the tabs
//-----------------------------------------------------------------------------
VOID    ResizeDeviceImage()
{
    // Based on the number of tabs, the tab control has a different client
    // size. Determine the current size and reposition the IDC_IMAGE control, 
    // which is being used as the background for the device image.

    RECT rc;
    HWND hwndTabs = GetDlgItem( g_hDlg, IDC_DEVICES );
    GetWindowRect( hwndTabs, &rc );
    TabCtrl_AdjustRect( hwndTabs, FALSE, &rc );

    POINT pt = { rc.left, rc.top };
    ScreenToClient( g_hDlg, &pt );

    OffsetRect( &rc, pt.x - rc.left, pt.y - rc.top);
    InflateRect( &rc, -10, -10 );
    MoveWindow( GetDlgItem( g_hDlg, IDC_IMAGE ), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, FALSE );

}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    for( UINT i=0; i < g_dwNumDevices; i++ )
    {
        if( g_pDevices[i] )
        {
            g_pDevices[i]->Unacquire();
            g_pDevices[i]->Release();
            g_pDevices[i] = NULL;
        }
    }

    SAFE_RELEASE( g_pDI );

    
}



