//-----------------------------------------------------------------------------
// File: main.cpp
//
// Desc: Sample that demonstrates action mapping with DirectSound
//
// Copyright( c ) 1998-2001 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>
#include <tchar.h>
#include <dinput.h>
#include "dxutil.h"
#include <dxerr9.h>
#include "resource.h"
#include "drumpad.h"



//-----------------------------------------------------------------------------
// enumeration of hypothetical control functions
//-----------------------------------------------------------------------------
enum eGameActions
{
    BASS_DRUM,           // base drum
    SNARE_DRUM,          // snare drum
    HIHAT_OPEN,          // open hihat
    HIHAT_CLOSE,         // closed hihat
    CRASH,               // crash
    USER1,               // user assigned one
    USER2,               // user assigned two
    USER3,               // user assigned three

    NUM_ACTIONS         // auto count for number of enumerated actions
};




//-----------------------------------------------------------------------------
// actions array
//-----------------------------------------------------------------------------
// Be sure to delete user map files 
// (C:\Program Files\Common Files\DirectX\DirectInput\User Maps\*.ini)
// after changing this, otherwise settings won't reset and will be read 
// from the out of date ini files 
static DIACTION g_rgActions[] = 
{
    // genre defined virtual buttons
    { BASS_DRUM,     DIBUTTON_TPS_ACTION,    0, TEXT("Bass Drum") , } ,
    { SNARE_DRUM,    DIBUTTON_TPS_JUMP,      0, TEXT("Snare Drum") , } ,
    { HIHAT_OPEN,    DIBUTTON_TPS_USE,       0, TEXT("Open Hi-Hat") , } ,
    { HIHAT_CLOSE,   DIBUTTON_TPS_RUN,       0, TEXT("Closed Hi-Hat") , } ,
    { CRASH,         DIBUTTON_TPS_MENU,      0, TEXT("Crash") , } ,
    { USER1,         DIBUTTON_TPS_DODGE,     0, TEXT("User 1") , } ,
    { USER2,         DIBUTTON_TPS_SELECT,    0, TEXT("User 2") , } ,
    { USER3,         DIBUTTON_TPS_VIEW,      0, TEXT("User 3") , } ,

    // keyboard mapping
    { BASS_DRUM,     DIKEYBOARD_B,           0, TEXT("Bass Drum") , } ,
    { SNARE_DRUM,    DIKEYBOARD_N,           0, TEXT("Snare Drum") , } ,
    { HIHAT_OPEN,    DIKEYBOARD_A,           0, TEXT("Open Hi-Hat") , } ,
    { HIHAT_CLOSE,   DIKEYBOARD_Z,           0, TEXT("Closed Hi-Hat") , } ,
    { CRASH,         DIKEYBOARD_C,           0, TEXT("Crash") , } ,
    { USER1,         DIKEYBOARD_K,           0, TEXT("User 1") , } ,
    { USER2,         DIKEYBOARD_L,           0, TEXT("User 2") , } ,
    { USER3,         DIKEYBOARD_SEMICOLON,   0, TEXT("User 3") , } ,

    // mouse mapping
    { BASS_DRUM,     DIMOUSE_BUTTON2,        0, TEXT("Bass Drum") , } ,
    { SNARE_DRUM,    DIMOUSE_BUTTON1,        0, TEXT("Snare Drum") , } ,
    { HIHAT_OPEN,    DIMOUSE_BUTTON3,        0, TEXT("Open Hi-Hat") , } ,
    { HIHAT_CLOSE,   DIMOUSE_BUTTON4,        0, TEXT("Closed Hi-Hat") , } ,
    { CRASH,         DIMOUSE_WHEEL,          0, TEXT("Crash") , } ,
    { USER1,         DIMOUSE_BUTTON5,        0, TEXT("User 1") , } ,
    { USER2,         DIMOUSE_BUTTON6,        0, TEXT("User 2") , } ,
    { USER3,         DIMOUSE_BUTTON7,        0, TEXT("User 3") , }
};




//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define     DV_MAX_DEVICES          128

// the coordinate of the rectangles that respond to buttons
#define     RECT_TOP                36
#define     RECT_LEFT               325

FLOAT       g_boxColors[NUM_ACTIONS] = { 0, };

// application specific guid {21BEE2A7-32D7-43c8-9241-1D380B06D005}
const GUID g_AppGuid = { 0x21bee2a7, 0x32d7, 0x43c8, { 0x92, 0x41, 0x1d, 0x38, 0xb, 0x6, 0xd0, 0x5 } };


LPDIRECTINPUT8          g_pDI               = NULL;
LPDIRECTINPUTDEVICE8    g_pDevices[DV_MAX_DEVICES] = {0};
DIACTIONFORMAT          g_diaf              = {0};
DWORD                   g_dwNumDevices      = 0;
HINSTANCE               g_hInstance         = NULL;
HICON                   g_hIcon             = NULL;
DrumPad*                g_lpDrumPad         = NULL;


//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
HRESULT          InitDirectInput( LPDIACTIONFORMAT lpDiaf );
VOID             ConstructActionMap( LPDIACTIONFORMAT lpDiaf );
VOID             FreeDirectInput();
VOID             FreeGlobals();
HRESULT          ProcessInput( HWND hwnd );
VOID             UpdateUI( HWND hwndDlg );
VOID             DrawRects( HWND hwnd, FLOAT* colors, DWORD numColors, BOOL drawBlack );
VOID             OnOpenSoundFile( HWND hDlg, DWORD sampleID);
HRESULT          ValidateWaveFile( HWND hDlg, TCHAR* strFileName, DWORD sampleID );
BOOL CALLBACK    EnumDevicesBySemanticsCallback( const DIDEVICEINSTANCE* pdidInstance, LPDIRECTINPUTDEVICE8 lpdid, DWORD dwFlags, DWORD dwRemainging, VOID* lpRef );
INT_PTR CALLBACK MainDlgProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam );






//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Win32 entry point to application
//-----------------------------------------------------------------------------
int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                        LPSTR lpCmdLine, int nShowCmd ) 
{
    HRESULT hr;
    
    CoInitialize( NULL );
    InitCommonControls();

    g_hInstance = hInstance;

    // Allocate a new DrumPad
    g_lpDrumPad = new DrumPad;

    // Fill in the action map to our desired set of actions
    ConstructActionMap( &g_diaf );

    // Initialize direct input, this will try to 
    // get a list of devices for the action map
    if( FAILED( hr = InitDirectInput( &g_diaf ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("InitDirectInput"), hr );
        MessageBox( NULL, TEXT("Error Initializing DirectInput"), 
                    TEXT("DrumPad Sample"), MB_ICONERROR | MB_OK );
        return 1;
    }

    // Load the icon - will be set during WM_INITDIALOG
    g_hIcon = LoadIcon( g_hInstance, MAKEINTRESOURCE( IDI_ICON ) );

    // Create the window
    HWND hwnd = CreateDialog( hInstance, MAKEINTRESOURCE( IDD_DLG_MAIN ), 
                              NULL, MainDlgProc );
    if( NULL == hwnd )
        return FALSE;

    ShowWindow( hwnd, nShowCmd );
    
    for(;;)
    {
        MSG msg;

        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if( FALSE == GetMessage( &msg, NULL, 0, 0 ) )
            {
                EndDialog( hwnd, 0 );
                break;
            }

            if( msg.message == WM_KEYDOWN )
            {
                switch( msg.wParam )
                {
                    case VK_ESCAPE:
                    case VK_F1:
                    case VK_SPACE:
                    case VK_TAB:
                    case VK_UP:
                    case VK_DOWN:
                    case VK_LEFT:
                    case VK_RIGHT:
                        // Let the dialog see these keys
                        break;

                    default:
                        // Block all other keyboard message
                        continue;
                }
            }

            // Process the message
            IsDialogMessage( hwnd, &msg );
        }
        else
        {
            // Game loop
            if( FAILED( ProcessInput( hwnd ) ) )
            {
                MessageBox( hwnd, TEXT("Error while processing input.\n\n")
                                  TEXT("The sample will now exit"), TEXT("Drumpad Error"), 
                                  MB_OK | MB_ICONERROR );
                EndDialog( hwnd, 0 );
                break;
            }
        }
    }

    // clean up DirectInput
    FreeDirectInput();

    // clean up dynamic data
    FreeGlobals();
    
    CoUninitialize();    
    
    return 0;
}




//-----------------------------------------------------------------------------
// Name: ProcessInput()
// Desc: Gathers user input, plays audio, and draws output. Input is gathered 
//       from the DInput devices, and output is displayed in the app's window.
//-----------------------------------------------------------------------------
HRESULT ProcessInput( HWND hwnd )
{
    static BOOL button_states[NUM_ACTIONS] = { FALSE , };

    DWORD i, j;

    DIDEVICEOBJECTDATA didObjData;
    ZeroMemory( &didObjData, sizeof(didObjData) );

    // This simple sample does a sleep for 10 ms to avoid maxing out the CPU.  
    Sleep( 10 ); 
        
    // Loop through all devices and check game input
    for( i = 0; i < g_dwNumDevices; i++ )
    {
        DWORD              dwItems = 10;
        DIDEVICEOBJECTDATA adod[10];
        HRESULT            hr;

        // Need to ensure that the devices are acquired, and pollable devices
        // are polled.
        g_pDevices[i]->Acquire();
        g_pDevices[i]->Poll();

        // This call gets the data from the i'th device. 
        hr = g_pDevices[i]->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), adod, &dwItems, 0 );
        if( FAILED(hr) )
            continue;
                                                 
        // Get the sematics codes. The number of input events is stored in
        // "dwItems", and all the events are stored in the "adod" array. Each
        // event has a type stored in "uAppDate", and actual data stored in
        // "dwData".
        for( j = 0; j < dwItems; j++ )
        {
            // Non-axis data is recieved as "button pressed" or "button
            // released". Parse input as such.
            BOOL bState = (adod[j].dwData == 0x80 ) ? TRUE : FALSE;
            INT  index  = (INT) adod[j].uAppData;

            if( button_states[index] == FALSE && bState )
            {
                g_lpDrumPad->Play(index, 0, 0);
                g_boxColors[index] = 255.0f;
            }

            button_states[index] = bState;
        }
    }
    
    DrawRects( hwnd, g_boxColors, NUM_ACTIONS, FALSE );
    
    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: DrawRects()
// Desc: Draw rectangles
//-----------------------------------------------------------------------------
VOID DrawRects( HWND hwnd, FLOAT* colors, DWORD numColors, BOOL drawAll )
{
    COLORREF cr;
    UINT i;

    // get the DC of the window
    HDC hdc = GetDC( hwnd );
    // create solid pen
    HPEN hpen = CreatePen( PS_SOLID, 1, RGB( 0xff, 0x99, 0 ) );
    HPEN hpenOld = (HPEN) SelectObject( hdc, hpen );

    for( i = 0; i < numColors; i++ )
    {
        RECT rect = { RECT_LEFT, 0, RECT_LEFT + 28, 16 };
        if( colors[i] >= 0.0f || drawAll )
        {
            // make sure color is not negative
            if( colors[i] < 0.0f )
                colors[i] = 0.0f;

            // figure out what color to use
            cr = RGB( (DWORD) colors[i] / 2, (DWORD) colors[i], 0);
            HBRUSH hbrush = CreateSolidBrush( cr );
            HBRUSH hbrushOld = (HBRUSH) SelectObject( hdc, hbrush );

            rect.top    += RECT_TOP +( LONG )( i*( 32.5f ) );
            rect.bottom += rect.top;

            // draw the rectangle
            Rectangle( hdc, rect.left, rect.top, rect.right, rect.bottom );
            // fade the color to black
            colors[i] -= 2.5f;

            // clean up
            SelectObject( hdc, hbrushOld );
            DeleteObject( hbrush );
        }
    }

    // clean up
    SelectObject( hdc, hpenOld );
    DeleteObject( hpen );
    ReleaseDC( hwnd, hdc );
}




//-----------------------------------------------------------------------------
// Name: MainDlgProc()
// Desc: Callback for all Windows messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDlgProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_INITDIALOG:
        {
            // initialize the drumpad
            g_lpDrumPad->Initialize( NUM_ACTIONS, hwnd );

            // load the default sounds
            TCHAR strMediaPath[512];
            DXUtil_GetDXSDKMediaPathCch( strMediaPath, 512 );
            TCHAR strFile[MAX_PATH];
            
            wsprintf( strFile, TEXT("%sdrumpad-bass_drum.wav"), strMediaPath );
            g_lpDrumPad->Load( BASS_DRUM, strFile );
            
            wsprintf( strFile, TEXT("%sdrumpad-snare_drum.wav"), strMediaPath );
            g_lpDrumPad->Load( SNARE_DRUM, strFile );

            wsprintf( strFile, TEXT("%sdrumpad-hhat_down.wav"), strMediaPath );
            g_lpDrumPad->Load( HIHAT_CLOSE, strFile );

            wsprintf( strFile, TEXT("%sdrumpad-hhat_up.wav"), strMediaPath );
            g_lpDrumPad->Load( HIHAT_OPEN, strFile );

            wsprintf( strFile, TEXT("%sdrumpad-crash.wav"), strMediaPath );
            g_lpDrumPad->Load( CRASH, strFile );

            wsprintf( strFile, TEXT("%sdrumpad-voc_female_ec.wav"), strMediaPath );
            g_lpDrumPad->Load( USER2, strFile );

            wsprintf( strFile, TEXT("%sdrumpad-speech.wav"), strMediaPath );
            g_lpDrumPad->Load( USER1, strFile );

            UINT i;
            // Set the box color for load
            for( i = 0; i < NUM_ACTIONS; i++ )
                g_boxColors[i] = 255.0f;

            UpdateUI( hwnd );

            SendMessage( hwnd, WM_SETICON, ICON_BIG,( LPARAM ) g_hIcon );
            SendMessage( hwnd, WM_SETICON, ICON_SMALL,( LPARAM ) g_hIcon );

            UpdateWindow( hwnd );
        }
        break;

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
                case IDCANCEL:
                case IDOK:
                    PostQuitMessage(0);
                    break;
                    
                case IDC_BUTTON_DEVICE:
                    // DirectInput has supports a native UI for viewing or
                    // changing the current device mappings.
                    DICONFIGUREDEVICESPARAMS diCDParams;

                    ZeroMemory( &diCDParams, sizeof(DICONFIGUREDEVICESPARAMS) );
                    diCDParams.dwSize = sizeof(DICONFIGUREDEVICESPARAMS);
                    diCDParams.dwcFormats = 1;
                    diCDParams.lprgFormats = &g_diaf;
                    diCDParams.hwnd = hwnd;

                    g_pDI->ConfigureDevices( NULL, &diCDParams, DICD_DEFAULT, NULL );
                    break;
                    
                default:
                {
                    if( LOWORD(wParam) >= IDC_BUTTON_BASS && LOWORD(wParam) <= IDC_BUTTON_USER3 )
                    {
                        OnOpenSoundFile( hwnd, LOWORD(wParam) - IDC_BUTTON_BASS );
                        UpdateUI( hwnd );
                        return TRUE;
                    }
                    return FALSE;
                }
            }
        }
        break;

        case WM_PAINT:
        {
            // draw all boxes
            DrawRects( hwnd, g_boxColors, NUM_ACTIONS, TRUE );
            return FALSE;
        }
        break;

        default: 
            return FALSE;
    }

    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: ConstructActionMap()
// Desc: Prepares the action map to be used
//-----------------------------------------------------------------------------
void ConstructActionMap( LPDIACTIONFORMAT lpDiaf )
{
    ZeroMemory( lpDiaf, sizeof( DIACTIONFORMAT ) );
    
    lpDiaf->dwSize = sizeof(DIACTIONFORMAT);
    lpDiaf->dwActionSize = sizeof(DIACTION);
    lpDiaf->dwNumActions = sizeof(g_rgActions) / sizeof(DIACTION);
    
    // Size of device data to be returned by the device
    lpDiaf->dwDataSize = lpDiaf->dwNumActions * sizeof(DWORD);
    
    // Allocate and copy static DIACTION array
    lpDiaf->rgoAction = new DIACTION[ lpDiaf->dwNumActions ];
    memcpy( lpDiaf->rgoAction, g_rgActions, lpDiaf->dwNumActions * sizeof(DIACTION) );
    
    // Set the application GUID
    lpDiaf->guidActionMap = g_AppGuid;
    lpDiaf->dwBufferSize = 16;
    lpDiaf->lAxisMin = -100;
    lpDiaf->lAxisMax = 100;
    
    // Game genre
    lpDiaf->dwGenre = DIVIRTUAL_FIGHTING_THIRDPERSON;

    // Friendly name for this mapping
    lstrcpy( lpDiaf->tszActionMap, TEXT("DeviceView - Sample Action Map") );
}




//-----------------------------------------------------------------------------
// Name: InitDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
HRESULT InitDirectInput( LPDIACTIONFORMAT lpDiaf )
{
    HRESULT hr;

    // Register with the DirectInput subsystem and get a pointer
    // to a IDirectInput interface we can use.
    // Create a DInput object
    if( FAILED( hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, 
                                         IID_IDirectInput8,( VOID** )&g_pDI, NULL ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("DirectInput8Create"), hr );

    // Look for a simple joystick we can use for this sample program.
    if( FAILED( hr = g_pDI->EnumDevicesBySemantics( NULL, lpDiaf, EnumDevicesBySemanticsCallback, 
                                                     NULL, DIEDBSFL_ATTACHEDONLY ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("EnumDevicesBySemantics"), hr );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: EnumDevicesBySemanticsCallback()
// Desc: Callback function for enumerating suitable devices. 
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumDevicesBySemanticsCallback( const DIDEVICEINSTANCE* pdidi,
                                               LPDIRECTINPUTDEVICE8 pdidDevice, 
                                               DWORD dwFlags,
                                               DWORD dwRemainingDevices,
                                               VOID* pContext )
{
    
    if( g_dwNumDevices < DV_MAX_DEVICES )
    {
        // Set up the action mapping for the device
        if( FAILED( pdidDevice->BuildActionMap( &g_diaf, NULL, DIDBAM_DEFAULT ) ) )
            return DIENUM_CONTINUE;

        if( FAILED( pdidDevice->SetActionMap( &g_diaf, NULL, DIDSAM_DEFAULT ) ) )
            return DIENUM_CONTINUE;

        // Add a reference to the device
        pdidDevice->AddRef();
       
        // Save a reference to the device
        g_pDevices[g_dwNumDevices++] = pdidDevice;
    }
    else
    {
        // Max number of devices reached for the sample.
        // modify DV_MAX_DEVICES to change this limit
        MessageBox( NULL, TEXT("Sample maximum number of devices reached"), 
                     TEXT("DrumPad Sample"), MB_ICONERROR | MB_OK );

        // Stop enumerating suitable devices
        return DIENUM_STOP;
    }

    // Continue enumerating suitable devices
    return DIENUM_CONTINUE;
}




//-----------------------------------------------------------------------------
// Name: FreeDirectInput()
// Desc: Free the DirectInput variables.
//-----------------------------------------------------------------------------
VOID FreeDirectInput()
{
    DWORD i;

    // Go through global array of joysticks
    for( i = 0; i < g_dwNumDevices; i++)
    {
        // Unacquire the device one last time just in case 
        // the app tried to exit while the device is still acquired.
        g_pDevices[i]->Unacquire();
    
        // Release any DirectInput objects.
        SAFE_RELEASE( g_pDevices[i] );
    }

    // Release the DirectInput object
    SAFE_RELEASE( g_pDI );
}




//-----------------------------------------------------------------------------
// Name: FreeGlobals()
// Desc: Free dynamic memory allocated by app
//-----------------------------------------------------------------------------
VOID FreeGlobals()
{
    SAFE_DELETE( g_lpDrumPad );
    SAFE_DELETE_ARRAY( g_diaf.rgoAction );
}




//-----------------------------------------------------------------------------
// Name: OnOpenSoundFile()
// Desc: Called when the user requests to open a sound file
//-----------------------------------------------------------------------------
VOID OnOpenSoundFile( HWND hDlg, DWORD id ) 
{
    static TCHAR strFileName[MAX_PATH] = TEXT("");
    static TCHAR strPath[MAX_PATH] = TEXT("");
    
    // Setup the OPENFILENAME structure
    OPENFILENAME ofn = { sizeof(OPENFILENAME), hDlg, NULL,
                         TEXT("Wave Files\0*.wav\0All Files\0*.*\0\0"), NULL,
                         0, 1, strFileName, MAX_PATH, NULL, 0, strPath,
                         TEXT("Open Sound File"),
                         OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, 0, 0,
                         TEXT(".wav"), 0, NULL, NULL };

    // Get the default media path (something like C:\WINDOWS\MEDIA)
    if( TEXT('\0') == strPath[0] )
    {
        if (0 == GetWindowsDirectory( strPath, MAX_PATH )) return;
        if(lstrcmp( &strPath[lstrlen(strPath)], TEXT("\\") ) )
           lstrcat( strPath, TEXT("\\") );
       lstrcat( strPath, TEXT("MEDIA") );
    }

    // Display the OpenFileName dialog. Then, try to load the specified file
    if( TRUE != GetOpenFileName( &ofn ) )
    {
        return;
    }

    // Make sure wave file is a valid wav file
    ValidateWaveFile( hDlg, strFileName, id );

    // Remember the path for next time
    lstrcpy( strPath, strFileName );
    TCHAR* strLastSlash = _tcsrchr( strPath, TEXT('\\') );
    strLastSlash[0] = TEXT('\0');
}




//-----------------------------------------------------------------------------
// Name: ValidateWaveFile()
// Desc: Open the wave file with the helper 
//       class CWaveFile to make sure it is valid
//-----------------------------------------------------------------------------
HRESULT ValidateWaveFile( HWND hwndDlg, TCHAR* tszFilename, DWORD id )
{
    HRESULT hr;
    CWaveFile waveFile;

    if( -1 == GetFileAttributes( tszFilename ) )
        return E_FAIL;
    
    // Load the wave file
    if( FAILED( hr = waveFile.Open( tszFilename, NULL, WAVEFILE_READ ) ) )
    {
        waveFile.Close();
        MessageBox( hwndDlg, TEXT("File Cannot Be Openned As WAV"), TEXT("Sample Warning"), NULL );
        return hr; 
        /*DXTRACE_ERR_MSGBOX( TEXT("Open"), hr ); */
    }

    waveFile.Close();

    g_lpDrumPad->Load( id, tszFilename );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: UpdateUI()
// Desc: Update the UI
//-----------------------------------------------------------------------------
VOID UpdateUI( HWND hwndDlg )
{
    DWORD i;
    const TCHAR* str;

    for( i = IDC_TEXT_FILENAME1; i <= IDC_TEXT_FILENAME8; i++ )
    {
        str = g_lpDrumPad->GetName( i - IDC_TEXT_FILENAME1 );
        if( NULL == str )
            SetDlgItemText( hwndDlg, i, TEXT( "< no sample loaded >" ) );
        else
        {
            TCHAR* strLastSlash = _tcsrchr( str, TEXT('\\') );
            if( strLastSlash != NULL )
                SetDlgItemText( hwndDlg, i, strLastSlash + 1 );
            else
                SetDlgItemText( hwndDlg, i, str );
        }
    }
}


