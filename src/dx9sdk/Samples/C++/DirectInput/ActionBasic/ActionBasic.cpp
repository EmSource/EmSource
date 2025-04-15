//-----------------------------------------------------------------------------
// File: ActionBasic.cpp
//
// Desc: ActionBasic Sample 
//
// Copyright (c) 1997-2001 Microsoft Corporation. All rights reserved
//-----------------------------------------------------------------------------
#define STRICT
#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <commctrl.h>
#include <dinput.h>
#include <string.h>
#include <tchar.h>
#include <minmax.h>
#include "resource.h"


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
// This GUID must be unique for every game, and the same for every instance of 
// this app. The GUID allows DirectInput to remember input settings.
// {3AFABAD0-D2C0-4514-B47E-65FEF9B5142F}
const GUID g_guidApp = { 0x3afabad0, 0xd2c0, 0x4514, { 0xb4, 0x7e, 0x65, 0xfe, 0xf9, 0xb5, 0x14, 0x2f } };


// Global constants
const int MAX_DEVICES     = 8;    // The maximum number of allowed devices  
const int LENGTH_DEV_NAME = 40;   // The maximum length of device names
const int BUTTON_DOWN     = 0x80; // Mask for determining button state
const int NUM_OF_ACTIONS  = 9;    // Number of game action constants


// ****************************************************************************
// Step 1: Define the game actions. 
//         
// One of the big advantages of using action mapping to assist with game input
// is that it allows you to handle input in terms of game actions instead of
// device objects. For instance, this sample defines a small set of actions
// appropriate for a simple hand to hand combat game. When polling for user
// input, the data can be handled in terms of kicks and punches instead of
// button presses, axis movements, and keystrokes. This also allows to user
// to customize the controls without any further effort on the part of the
// developer.
//
// Each game action will be represented within your program as a 32 bit value.
// For this sample, the game actions correspond to indices within an array, but
// they could just as easily represent anything from variable addresses to
// function pointers. The value you choose for each game action will be
// returned by a call to GetDeviceData for triggered actions.
// ****************************************************************************

// Game action constants
// If you make changes to this list, make a corresponding change to the
// NUM_OF_ACTIONS global constant.
enum GAME_ACTIONS {
WALK,               // Separate inputs are needed in this case for
WALK_LEFT,          //   Walk/Left/Right because the joystick uses an
WALK_RIGHT,         //   axis to report both left and right, but the
BLOCK,              //   keyboard will use separate arrow keys.
KICK, 
PUNCH, 
THE_DEAPPETIZER,    // "The De-Appetizer" represents a special move
APOLOGIZE,          //   defined by this game.
QUIT
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

// ****************************************************************************
// Step 2: Define the action map. 
//         
// The action map instructs DirectInput on how to map game actions to device
// objects. By selecting a predefined game genre that closely matches our game,
// you can largely avoid dealing directly with device details. For this sample
// we've selected the DIVIRTUAL_FIGHTING_HAND2HAND, and this constant will need
// to be selected into the DIACTIONFORMAT structure later to inform DirectInput
// of our choice. Every device has a mapping from genre actions to device
// objects, so mapping your game actions to genre actions almost guarantees
// an appropriate device configuration for your game actions.
//
// If DirectInput has already been given an action map for this GUID, it
// will have created a user map for this application 
// (C:\Program Files\Common Files\DirectX\DirectInput\User Maps\*.ini). If a
// map exists, DirectInput will use the action map defined in the stored user 
// map instead of the map defined in your program. This allows the user to
// customize controls without losing changes when the game restarts. If you 
// wish to make changes to the default action map without changing the 
// GUID, you will need to delete the stored user map from your hard drive
// for the system to detect your changes and recreate a stored user map.
// ****************************************************************************

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
    { THE_DEAPPETIZER,  DIKEYBOARD_D,                 0,  ACTION_NAMES[THE_DEAPPETIZER], },
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


// Convenience wrapper for device pointers
struct DeviceState
{
    LPDIRECTINPUTDEVICE8 pDevice;   // Pointer to the device 
    TCHAR szName[LENGTH_DEV_NAME];  // Friendly name of the device
    bool  bAxisRelative;            // Relative x-axis data flag
    DWORD dwInput[NUM_OF_ACTIONS];  // Arrays of the current input values and
    DWORD dwPaint[NUM_OF_ACTIONS];  //   values when last painted
    bool  bMapped[NUM_OF_ACTIONS];  // Flags whether action was successfully
};                                  //   mapped to a device object


// Global variables
LPDIRECTINPUT8  g_pDI         = NULL;  // DirectInput access pointer
DIACTIONFORMAT  g_diaf        = {0};   // DIACTIONFORMAT structure, used for
                                       //   enumeration and viewing config
HFONT           g_hActionFont = NULL;  // Defines the fonts to be used for
HFONT           g_hDeviceFont = NULL;  //   drawing action and device names
HWND            g_hDlg        = NULL;  // Handle to the dialog window
bool            g_bRefChart   = TRUE;  // Flags a chart sizing refresh
DeviceState     g_aDevices[MAX_DEVICES] = {0};  // List of devices
int             g_iNumDevices = 0;     // Total number of stored devices


// Function prototypes
INT_PTR CALLBACK DialogProc( HWND, UINT, WPARAM, LPARAM );
BOOL    CALLBACK EnumDevicesCallback( LPCDIDEVICEINSTANCE, LPDIRECTINPUTDEVICE8, DWORD, DWORD, LPVOID );

HRESULT InitDirectInput();
void    PaintChart( HDC, RECT* );
void    CheckInput();
void    CreateFonts();
void    DisplayHelp();
void    Cleanup();




//-----------------------------------------------------------------------------
// Name: WinMain
// Desc: Program entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    LPSTR lpCmdLine, INT iCmdShow )
{
    InitCommonControls();

    // Create a modeless dialog box to serve as the user interface. A modeless
    // dialog was selected so our message loop will run while the interface
    // is displayed, which allows us to trap keyboard input.
    CreateDialog( hInstance, MAKEINTRESOURCE(IDD_APPDIALOG), NULL, DialogProc );


    MSG msg;

    // Background message loop
    while( GetMessage( &msg, NULL, 0, 0) )
    {
        // Filter out unused keyboard input. Windows continues to handle
        // keyboard messages even when the keyboard is acquired through
        // DirectInput. 
        if( msg.message == WM_KEYDOWN )
        {
            if( msg.wParam == VK_F1 )
            {
                // Display the help screen for this sample
                DisplayHelp();
            }
            else if( msg.wParam == VK_ESCAPE )
            {
                // Exit program. Let the dialog handle this
            }
            else
            {
                // Block all other keyboard messages
                continue;
            }
        }
       
        if( !IsDialogMessage( g_hDlg, &msg ) )  
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

        if( msg.message == WM_QUIT )
        {
            DestroyWindow( g_hDlg );
            break;
        }
    }
 
    Cleanup();
    return 0;
}




//-----------------------------------------------------------------------------
// Name: DialogProc
// Desc: Handles dialog box messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK DialogProc( HWND hDlg, UINT message, 
                             WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
        case WM_INITDIALOG:
        {
            // All initialization code is performed here

            g_hDlg = hDlg;

            CreateFonts();

            // Initialize DirectInput
            if( FAILED(InitDirectInput()) )
            {
                MessageBox( hDlg, TEXT("Failed to initialize DirectInput.\n")
                                  TEXT("The sample will now exit."),
                                  TEXT("Error"), MB_ICONEXCLAMATION | MB_OK );
                PostQuitMessage(0);
            }

            // Start the timer. This timer is set to notify the dialog 30 times
            // per second. Each timer tick signals that it's time to check
            // for device input and refresh the interface.
            SetTimer( hDlg, 1, 1000/30, NULL );
            return TRUE;
        }

        case WM_DRAWITEM:
        {
            // The action chart is drawn upon a win32 user-drawn button, and
            // this event signals that all or part of the button needs to be
            // redrawn due to a window event.
            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT) lParam;

            if( pdis->itemAction == ODA_DRAWENTIRE )
                PaintChart( pdis->hDC, &pdis->rcItem );

            return TRUE;
        }

        case WM_COMMAND:
        {    
            // Handle button input from the user
            switch( LOWORD(wParam) )
            {
                case IDC_CONFIG:
                {
                    // The user has clicked on the "View Configuration" button.
                    // DirectInput has supports a native UI for viewing or
                    // changing the current device mappings.
                    DICONFIGUREDEVICESPARAMS diCDParams;

                    ZeroMemory( &diCDParams, sizeof(DICONFIGUREDEVICESPARAMS) );
                    diCDParams.dwSize = sizeof(DICONFIGUREDEVICESPARAMS);
                    diCDParams.dwcFormats = 1;
                    diCDParams.lprgFormats = &g_diaf;
                    diCDParams.hwnd = g_hDlg;

                    g_pDI->ConfigureDevices( NULL, &diCDParams, DICD_DEFAULT, NULL );
                    break;
                }

                case IDCANCEL:
                {
                    PostQuitMessage( 0 );
                    EndDialog( hDlg, 0 );
                    return TRUE;
                }
            }

            break;
        }  

        case WM_TIMER:
        {
            CheckInput();
            break;
        }
    }

    return FALSE;
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
    _tcscpy( g_diaf.tszActionMap, _T("ActionMap Sample") );
 
    if( FAILED( hr = g_pDI->EnumDevicesBySemantics( NULL, &g_diaf,  
                                                    EnumDevicesCallback,
                                                    NULL, DIEDBSFL_ATTACHEDONLY ) ) )
        return hr;

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

    if( g_iNumDevices < MAX_DEVICES )
    {
        // ********************************************************************
        // Step 4: Build the action map against the device, inspect the
        //         results, and set the action map.
        //
        // It's a good idea to inspect the results after building the action
        // map against the current device. The contents of the action map
        // structure indicate how and to what object the action was mapped. 
        // This sample simply verifies the action was mapped to an object on
        // the current device, and stores the result. Note that not all actions
        // will necessarily be mapped to an object on all devices. For instance,
        // this sample did not request that QUIT be mapped to any device other
        // than the keyboard.
        // ********************************************************************

   
        // Build the action map against the device
        if( FAILED(hr = lpdid->BuildActionMap( &g_diaf, NULL, DIDBAM_DEFAULT )) )
            // There was an error while building the action map. Ignore this
            // device, and contine with the enumeration
            return DIENUM_CONTINUE;

        
        // Inspect the results
        for( UINT i=0; i < g_diaf.dwNumActions; i++ )
        {
            DIACTION *dia = &(g_diaf.rgoAction[i]);

            if( dia->dwHow != DIAH_ERROR && dia->dwHow != DIAH_UNMAPPED )
                g_aDevices[g_iNumDevices].bMapped[dia->uAppData] = TRUE;
        }

        // Set the action map
        if( FAILED(hr = lpdid->SetActionMap( &g_diaf, NULL, DIDSAM_DEFAULT )) )
        {
            // An error occured while trying the set the action map for the 
            // current device. Clear the stored values, and continue to the
            // next device.
            ZeroMemory( g_aDevices[g_iNumDevices].bMapped, 
                 sizeof(g_aDevices[g_iNumDevices].bMapped) );
            return DIENUM_CONTINUE;
        }

        // The current device has been successfully mapped. By storing the
        // pointer and informing COM that we've added a reference to the 
        // device, we can use this pointer later when gathering input.
        g_aDevices[g_iNumDevices].pDevice = lpdid;
        lpdid->AddRef();

        // Store the device's friendly name for display on the chart.
        _tcsncat( g_aDevices[g_iNumDevices].szName, lpddi->tszInstanceName, LENGTH_DEV_NAME-5 );
    
        if( _tcslen( lpddi->tszInstanceName ) > LENGTH_DEV_NAME-5 )
            _tcscat( g_aDevices[g_iNumDevices].szName, TEXT("...") );

        // Store axis absolute/relative flag
        DIPROPDWORD dipdw;  
        dipdw.diph.dwSize       = sizeof(DIPROPDWORD); 
        dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
        dipdw.diph.dwObj        = 0; 
        dipdw.diph.dwHow        = DIPH_DEVICE; 
 
        hr = lpdid->GetProperty( DIPROP_AXISMODE, &dipdw.diph ); 
        if (SUCCEEDED(hr)) 
            g_aDevices[g_iNumDevices].bAxisRelative = ( DIPROPAXISMODE_REL == dipdw.dwData );

        g_bRefChart = TRUE; // Signal a chart resize
        g_iNumDevices++;    // Increment the global device index   
    }
   
    // Ask for the next device
    return DIENUM_CONTINUE;
}




//-----------------------------------------------------------------------------
// Name: CheckInput
// Desc: Poll the attached devices and update the display
//-----------------------------------------------------------------------------
void CheckInput()
{
    HRESULT hr;
    
    // For each device gathered during enumeration, gather input. Although when
    // using action maps the input is received according to actions, each device 
    // must still be polled individually. Although for most actions your
    // program will follow the same logic regardless of which device generated
    // the action, there are special cases which require checking from which
    // device an action originated.

    for( int iDevice=0; iDevice < g_iNumDevices; iDevice++ )
    {
        LPDIRECTINPUTDEVICE8 pdidDevice = g_aDevices[iDevice].pDevice;
        DIDEVICEOBJECTDATA rgdod[10];
        DWORD   dwItems = 10;

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
            continue;

        // For each buffered data item, extract the game action and perform
        // necessary game state changes. A more complex program would certainly
        // handle each action separately, but this sample simply stores raw
        // axis data for a WALK action, and button up or button down states for
        // all other game actions. 

        // Relative axis data is never reported to be zero since relative data
        // is given in relation to the last position, and only when movement 
        // occurs. Manually set relative data to zero before checking input.
        if( g_aDevices[iDevice].bAxisRelative )
            g_aDevices[iDevice].dwInput[WALK] = 0;

        for( DWORD j=0; j<dwItems; j++ )
        {
            UINT_PTR dwAction = rgdod[j].uAppData;
            DWORD dwData = 0;

            // The value stored in dwAction equals the 32 bit value stored in 
            // the uAppData member of the DIACTION structure. For this sample
            // we selected these action constants to be indices into an array,
            // but we could have chosen these values to represent anything
            // from variable addresses to function pointers.

            switch( dwAction )
            {
                case WALK:  
                {
                    // Axis data. Absolute axis data is already scaled to the
                    // boundaries selected in the DIACTIONFORMAT structure, but
                    // relative data is reported as relative motion change 
                    // since the last report. This sample scales relative data
                    // and clips it to axis data boundaries.

                    dwData = rgdod[j].dwData;   
                    
                    if( g_aDevices[iDevice].bAxisRelative )
                    {
                        // scale relative data
                        dwData *= 5;

                        // clip to boundaries
                        if( (int)dwData < 0 )
                            dwData = max( (int)dwData, g_diaf.lAxisMin );
                        else
                            dwData = min( (int)dwData, g_diaf.lAxisMax );
                    }
                    
                    break;
                }

                default:
                {
                    dwData = rgdod[j].dwData & BUTTON_DOWN ?    1 : 0;
                    break;
                }
            }

            g_aDevices[iDevice].dwInput[dwAction] = dwData;
        }
    }

    // Paint new data
    HWND hChart = GetDlgItem( g_hDlg, IDCHART );
    HDC hDC = GetDC( hChart );
    PaintChart( hDC, NULL );
    ReleaseDC( hChart, hDC );
}




//-----------------------------------------------------------------------------
// Name: PaintChart
// Desc: Output the device/action chart
// Args: hDC - Device context handle
//       prcWindow - Pointer to a RECT defining the window boundaries. If NULL,
//                  the function will only draw cell changes. 
//-----------------------------------------------------------------------------
void PaintChart( HDC hDC, RECT *prcWindow )
{   

    // Almost all of the code in this function is devoted to correctly
    // positioning the chart, drawing labels, and minimizing flicker. The small
    // portion of the code which deals with examining and painting the game
    // data is clearly offset with comment lines.

    static const int GUTTER_SIZE     = 10;   // Chart display constants
    static const int CELL_SIZE       = 15;

    static RECT rcChart = {0};  // Bounding RECT for the chart (grid and titles)
    static RECT rcGrid  = {0};  // Bounding RECT for the grid

    int  iX=0, iY=0;             // Temp variables
    RECT rc;

    HBRUSH hBrCell    = CreateSolidBrush( GetSysColor( COLOR_HIGHLIGHT ) );
    HBRUSH hBrUnmap   = CreateHatchBrush( HS_BDIAGONAL, GetSysColor( COLOR_HIGHLIGHT ) );
    HPEN   hPenGrid   = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNSHADOW ) );
    HPEN   hPenAxis   = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNFACE ) );
    POINT  aPoints[4] = {0};

    HBRUSH hFontOld   = (HBRUSH) GetCurrentObject( hDC, OBJ_FONT );
    HPEN   hPenOld    = (HPEN) GetCurrentObject( hDC, OBJ_PEN );

    // Since this function can be called either when new data is available, or
    // when a window event has caused a portion of the chart to become invalid,
    // there are rare times when the labels and grid need to be painted. 
    
    // The  g_bRefChart flag is raised when the chart's size may have changed.
    // The prcWindow RECT is filled when the chart's labels and grid must be
    // painted.

    // Refresh chart (sizing and positioning)
    if( g_bRefChart && prcWindow )
    {
        g_bRefChart = FALSE;

        int iMaxActionSize=0, iMaxDeviceSize=0;   
        SIZE size;

        // Determine the largest action name size
        SelectObject( hDC, g_hActionFont );
        for( int i=0; i < NUM_OF_ACTIONS; i++ )
        {
            GetTextExtentPoint32( hDC, ACTION_NAMES[i], lstrlen( ACTION_NAMES[i] ), &size );
            iMaxActionSize = max( size.cx, iMaxActionSize );
        }

        // Determine the largest device name size
        SelectObject( hDC, g_hDeviceFont );
        for( int j=0; j < g_iNumDevices; j++ )
        {
            GetTextExtentPoint32( hDC, g_aDevices[j].szName, lstrlen( g_aDevices[j].szName ), &size );
            iMaxDeviceSize = max( size.cx, iMaxDeviceSize );
        }

        // Determine the bounding rectangle for the chart and grid
        rcGrid.left    = iMaxDeviceSize + GUTTER_SIZE;
        rcGrid.top     = iMaxActionSize + GUTTER_SIZE;

        rcChart.right  = rcGrid.left + ( CELL_SIZE * NUM_OF_ACTIONS );
        rcChart.bottom = rcGrid.top  + ( CELL_SIZE * g_iNumDevices );
        rcChart.left   = ( prcWindow->right  - rcChart.right  ) / 2;
        rcChart.top    = ( prcWindow->bottom - rcChart.bottom ) / 2;

        rcChart.right  += rcChart.left;
        rcChart.bottom += rcChart.top;

        rcGrid.left += rcChart.left;
        rcGrid.top  += rcChart.top;
        rcGrid.right = rcChart.right;
        rcGrid.bottom = rcChart.bottom;
    }

    // Repaint chart labels and grid
    if( prcWindow )
    {
        SelectObject( hDC, g_hActionFont );
        SelectObject( hDC, hPenGrid );

        iX = rcGrid.left;
        iY = rcGrid.top - GUTTER_SIZE;

        for( int i=0; i < NUM_OF_ACTIONS; i++ )
        {
            TextOut( hDC, iX+2, iY, ACTION_NAMES[i], lstrlen(ACTION_NAMES[i]) );

            aPoints[0].x = iX;
            aPoints[0].y = rcGrid.top;
            aPoints[1].x = iX + CELL_SIZE;
            aPoints[1].y = rcGrid.top;
            aPoints[2].x = iX + CELL_SIZE;
            aPoints[2].y = rcGrid.bottom;
            aPoints[3].x = iX;
            aPoints[3].y = rcGrid.bottom;
            Polyline( hDC, aPoints, 4 );

            iX += CELL_SIZE;
        }

        // Paint the legend
        rc.left = 10;
        rc.right = 19;

        SelectObject( hDC, g_hDeviceFont );
        SelectObject( hDC, hPenGrid );

        // Inactive key 
        TextOut(  hDC, 25,  8, TEXT("Inactive"), 8 );
        MoveToEx( hDC,  8,  8, NULL );
        LineTo(   hDC, 20,  8 );
        LineTo(   hDC, 20, 20 );
        LineTo(   hDC,  8, 20 );
        LineTo(   hDC,  8,  8 );

        // Active key
        TextOut(  hDC, 25, 24, TEXT("Active"), 6 );
        MoveToEx( hDC,  8, 24, NULL );
        LineTo(   hDC, 20, 24 );
        LineTo(   hDC, 20, 36 );
        LineTo(   hDC,  8, 36 );
        LineTo(   hDC,  8, 24 );

        rc.top = 26;
        rc.bottom = rc.top + 9;
        FillRect( hDC, &rc, hBrCell );

        // Unmapped key
        TextOut(  hDC, 25, 40, TEXT("Unmapped"), 8 );
        MoveToEx( hDC,  8, 40, NULL );
        LineTo(   hDC, 20, 40 );
        LineTo(   hDC, 20, 52 );
        LineTo(   hDC,  8, 52 );
        LineTo(   hDC,  8, 40 );

        rc.top = 42;
        rc.bottom = rc.top + 9;
        FillRect( hDC, &rc, hBrUnmap );

    }

    SelectObject( hDC, g_hDeviceFont );
    SetTextAlign( hDC, TA_RIGHT );
    iY = rcGrid.top;

    // For each device, examine and paint the stored data.
    for( int iDevice=0; iDevice < g_iNumDevices; iDevice++ )
    {
        if( prcWindow )
        {
            TextOut( hDC, rcGrid.left - GUTTER_SIZE, iY+1, g_aDevices[iDevice].szName, lstrlen( g_aDevices[iDevice].szName ) );
           
            aPoints[0].x = rcGrid.right;
            aPoints[0].y = iY;
            aPoints[1].x = rcGrid.left;
            aPoints[1].y = iY;
            aPoints[2].x = rcGrid.left;
            aPoints[2].y = iY + CELL_SIZE;
            aPoints[3].x = rcGrid.right;
            aPoints[3].y = iY + CELL_SIZE;
           
            Polyline( hDC, aPoints, 4 );
        }

        rc.top      = iY + 3;
        rc.bottom   = rc.top + 10;
        rc.left     = rcGrid.left + 3;
        rc.right    = rc.left + 10;
        

        // ____________________________________________________________________
        // BEGIN paint stored data

        // Cycle through each game action
        for( int i=0; i < NUM_OF_ACTIONS; i++ )
        {
            // If the action data has not changed since the last painting, we
            // can skip to the next action to avoid flicker
            if( prcWindow || g_aDevices[iDevice].dwInput[i] != g_aDevices[iDevice].dwPaint[i] )
            {
                // If the current action was not mapped to an object on the current
                // device, select a cross-hatch brush into the DC. Else select
                // either a highlight or background colored brush, depending on
                // whether the current action is active.

                HBRUSH hBrFill = NULL;
                if( !g_aDevices[iDevice].bMapped[i] )
                    hBrFill = hBrUnmap;
                else if( g_aDevices[iDevice].dwInput[i] )
                    hBrFill = hBrCell;
                else
                    hBrFill = (HBRUSH) GetSysColorBrush( COLOR_BTNFACE );

                // Fill the cell corresponding to the current device and action,
                // and store the current data to avoid unnecessary repainting.
                FillRect( hDC, &rc, hBrFill );
                g_aDevices[iDevice].dwPaint[i] = g_aDevices[iDevice].dwInput[i];

                // For axis data, also draw an arrow to indicate the current
                // axis position. 
                if( i == WALK && g_aDevices[iDevice].dwInput[i] )
                {   
                    // Scale the axis data to the size of the cell 
                    int iTempX = rc.left+1 + (g_aDevices[iDevice].dwInput[i] + 100)/25; 

                    HPEN hPenPrev = (HPEN) SelectObject( hDC, hPenAxis );
                    MoveToEx( hDC, iTempX,   rc.bottom-2, NULL );
                    LineTo(   hDC, iTempX,   rc.top );
                    MoveToEx( hDC, iTempX-1, rc.top+2,    NULL );
                    LineTo(   hDC, iTempX+2, rc.top+2 );
                    MoveToEx( hDC, iTempX-2, rc.top+3,    NULL );
                    LineTo(   hDC, iTempX+3, rc.top+3 );
                    SelectObject( hDC, hPenPrev );
                }
            }

            // Advance the painting position over to the next action
            rc.left += CELL_SIZE;
            rc.right += CELL_SIZE;
        }
        // ____________________________________________________________________
        // END paint stored data

        // Advance the painting position down to the next device
        iY += CELL_SIZE;
    }

    // Restore the DC to it's original state, and destroy created objects
    SelectObject( hDC, hFontOld );
    SelectObject( hDC, hPenOld );

    DeleteObject( hBrCell );
    DeleteObject( hBrUnmap );
    DeleteObject( hPenGrid );
    DeleteObject( hPenAxis );

}




//-----------------------------------------------------------------------------
// Name: DisplayHelp
// Desc: Displays the help screen
//-----------------------------------------------------------------------------
void DisplayHelp()
{
    MessageBox( g_hDlg, TEXT("The chart shows the list of devices found ")
                        TEXT("attached to your computer, plotted against a\n")
                        TEXT("defined set of actions for an imaginary fighting ")
                        TEXT("game.\n\n")
                        TEXT("30 times per second, the program polls for new ") 
                        TEXT("input from the devices, and displays which actions\n")
                        TEXT("are currently being sent by each device. During ")
                        TEXT("initialization, the program attempts to establish\n")
                        TEXT("a mapping between actions and device objects for ")
                        TEXT("each attached device. Actions which were not\n")
                        TEXT("mapped to a device object are shown as a ")
                        TEXT("crosshatch-filled cell on the chart.\n\n")
                        TEXT("To view the current action mappings for all the ")
                        TEXT("devices, click the \"View Configuration\" button,\n")
                        TEXT("which will access the default configuration UI ")
                        TEXT("managed by DirectInput."),
                        TEXT("ActionBasic Help"), MB_OK );
}




//-----------------------------------------------------------------------------
// Name: CreateFonts
// Desc: Creates the display fonts.
//-----------------------------------------------------------------------------
VOID CreateFonts()
{
    // Create display fonts. These fonts will be used to draw the action and
    // device names on the chart.

    LOGFONT lf;
    ZeroMemory( &lf, sizeof(LOGFONT) );
    lf.lfHeight = 14;
    lf.lfWeight = 500;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
    _tcscpy( lf.lfFaceName, TEXT("arial") );

    g_hDeviceFont = CreateFontIndirect( &lf );

    lf.lfEscapement = 900;
    lf.lfHeight = 12;
    g_hActionFont = CreateFontIndirect( &lf );
}




//-----------------------------------------------------------------------------
// Name: Cleanup
// Desc: Release and clear all COM pointers
//-----------------------------------------------------------------------------
void Cleanup()
{
    // Release resources
    DeleteObject( g_hDeviceFont );
    DeleteObject( g_hActionFont );

    // Release device pointers
    for( int i=0; i < g_iNumDevices; i++ )
    {
        if( g_aDevices[i].pDevice )
        {
            g_aDevices[i].pDevice->Unacquire();
            g_aDevices[i].pDevice->Release();
            g_aDevices[i].pDevice = NULL;
        }
    }

    // Release DirectInput
    if( g_pDI )
    {
        g_pDI->Release();
        g_pDI = NULL;
    }
}

