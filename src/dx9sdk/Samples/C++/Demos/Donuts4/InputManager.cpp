//-----------------------------------------------------------------------------
// File: InputManager.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"


//-----------------------------------------------------------------------------
// Game actions (using DInput semantic mapper). The definitions here are kind
// of the whole point of this sample. The game uses these actions to map
// physical input like, "the user pressed the 'W' key", to a more useable
// constant for the game, like "if( dwInput == INPUT_CHANGEWEAPONS )...".
//-----------------------------------------------------------------------------

// Input semantics used by this game
enum INPUT_SEMANTICS
{
    // Gameplay semantics
    INPUT_AXIS_LR=1,     INPUT_AXIS_UD,       
    INPUT_TURNLEFT,      INPUT_TURNRIGHT,     INPUT_FORWARDTHRUST,
    INPUT_REVERSETHRUST, INPUT_FIREWEAPONS,   
    INPUT_CHANGEWEAPONS, INPUT_DISPLAYGAMEMENU,
    INPUT_QUITGAME,      INPUT_START,         INPUT_MOVELEFT,
    INPUT_MOVERIGHT,     INPUT_MOVE_LR,

    INPUT_CTRL,          INPUT_SHIFT,         
    INPUT_FLYDOWN,       INPUT_FLYUP,         INPUT_DEBUGMODE,

    // Menu semantics
    INPUT_MENU_UD,       INPUT_MENU_WHEEL,
    INPUT_MENU_UP,       INPUT_MENU_DOWN,     
    INPUT_MENU_SELECT,   INPUT_MENU_QUIT,
};

// Game actions used by this game.
DIACTION g_rgGameAction[] =
{
    // delete x:\Program Files\Common Files\DirectX\DirectInput\User Maps\*.ini
    // after changing this, otherwise settings won't reset and will be read 
    // from the out of date ini files 

    // Mouse input mappings
    { INPUT_AXIS_LR,         DIMOUSE_XAXIS,      0, TEXT("Look Left/Right"), },
    { INPUT_AXIS_UD,         DIMOUSE_YAXIS,      0, TEXT("Look Up/Down"), },
    { INPUT_FIREWEAPONS,     DIMOUSE_BUTTON0,    0, TEXT("Fire weapons"), },

    // Keyboard input mappings
    { INPUT_MOVELEFT,        DIKEYBOARD_LEFT,    0, TEXT("Strafe left"), },
    { INPUT_MOVERIGHT,       DIKEYBOARD_RIGHT,   0, TEXT("Strafe right"), },
    { INPUT_FORWARDTHRUST,   DIKEYBOARD_UP,      0, TEXT("Forward"), },
    { INPUT_REVERSETHRUST,   DIKEYBOARD_DOWN,    0, TEXT("Reverse"), },

    { INPUT_MOVELEFT,        DIKEYBOARD_A,       0, TEXT("Strafe left"), },
    { INPUT_MOVERIGHT,       DIKEYBOARD_D,       0, TEXT("Strafe right"), },
    { INPUT_FORWARDTHRUST,   DIKEYBOARD_W,       0, TEXT("Forward"), },
    { INPUT_REVERSETHRUST,   DIKEYBOARD_S,       0, TEXT("Reverse"), },

    { INPUT_FIREWEAPONS,     DIKEYBOARD_SPACE,   0, TEXT("Fire weapons"), },
    { INPUT_DISPLAYGAMEMENU, DIKEYBOARD_F1,      DIA_APPFIXED, TEXT("Display game menu"), },
    { INPUT_START,           DIKEYBOARD_PAUSE,   0, TEXT("Start/pause"), },
    { INPUT_DISPLAYGAMEMENU, DIKEYBOARD_ESCAPE,  DIA_APPFIXED, TEXT("Quit game"), },

    { INPUT_CTRL,            DIKEYBOARD_RCONTROL,DIA_APPFIXED, TEXT("Ctrl"), },
    { INPUT_SHIFT,           DIKEYBOARD_RSHIFT,  DIA_APPFIXED, TEXT("Shift"), },
    { INPUT_CTRL,            DIKEYBOARD_LCONTROL,DIA_APPFIXED, TEXT("Ctrl"), },
    { INPUT_SHIFT,           DIKEYBOARD_LSHIFT,  DIA_APPFIXED, TEXT("Shift"), },
    { INPUT_DEBUGMODE,       DIKEYBOARD_GRAVE,   DIA_APPFIXED, TEXT("Debug Mode"), },
    { INPUT_FLYUP,           DIKEYBOARD_PRIOR,   DIA_APPFIXED, TEXT("Debug Fly Up"), },
    { INPUT_FLYDOWN,         DIKEYBOARD_NEXT,    DIA_APPFIXED, TEXT("Debug Fly Down"), },
};

// Game actions used by this game.
DIACTION g_rgBrowserAction[] =
{
    // delete x:\Program Files\Common Files\DirectX\DirectInput\User Maps\*.ini
    // after changing this, otherwise settings won't reset and will be read 
    // from the out of date ini files 

    // Device input (joystick, etc.) that is pre-defined by DInput, according
    // to genre type. The genre for this app is space simulators.
    { INPUT_MENU_UD,         DIAXIS_BROWSER_MOVE,       0, TEXT("Up/down"), },
    { INPUT_MENU_UP,         DIBUTTON_BROWSER_PREVIOUS, 0, TEXT("Up"), },
    { INPUT_MENU_DOWN,       DIBUTTON_BROWSER_NEXT,     0, TEXT("Down"), },
    { INPUT_MENU_SELECT,     DIBUTTON_BROWSER_SELECT,   0, TEXT("Select"), },
    { INPUT_MENU_QUIT,       DIBUTTON_BROWSER_DEVICE,   0, TEXT("Quit menu"), },

    // Keyboard input mappings
    { INPUT_MENU_UP,         DIKEYBOARD_UP,          0, TEXT("Up"), },
    { INPUT_MENU_DOWN,       DIKEYBOARD_DOWN,        0, TEXT("Down"), },
    { INPUT_MENU_SELECT,     DIKEYBOARD_SPACE,       0, TEXT("Select"), },
    { INPUT_MENU_SELECT,     DIKEYBOARD_RETURN,      0, TEXT("Select"), },
    { INPUT_MENU_SELECT,     DIKEYBOARD_NUMPADENTER, 0, TEXT("Select"), },
    { INPUT_MENU_QUIT,       DIKEYBOARD_ESCAPE,      0, TEXT("Quit menu"), },

    // Mouse input mappings
    { INPUT_MENU_WHEEL,      DIMOUSE_WHEEL,      0, TEXT("Up/down"), },
    { INPUT_MENU_SELECT,     DIMOUSE_BUTTON0,    0, TEXT("Select"), },
};

// Number of actions
#define NUMBER_OF_GAMEACTIONS    (sizeof(g_rgGameAction)/sizeof(DIACTION))
#define NUMBER_OF_BROWSERACTIONS (sizeof(g_rgBrowserAction)/sizeof(DIACTION))


CInputManager::UserInput* g_pUserInput = NULL;              


//-----------------------------------------------------------------------------
// Name: CInputManager()
// Desc:
//-----------------------------------------------------------------------------
CInputManager::CInputManager( CMyApplication* pApp )
{
    m_pApp                  = pApp;
    m_pInputDeviceManager   = NULL;
    m_pMouseDeviceState     = NULL;
    m_pConfigSurface        = NULL; 
    ZeroMemory( &m_UserInput, sizeof(m_UserInput) );
    g_pUserInput = &m_UserInput;
}




//-----------------------------------------------------------------------------
// Name: ~CInputManager()
// Desc:
//-----------------------------------------------------------------------------
CInputManager::~CInputManager(void)
{
    FinalCleanup();
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CInputManager::OneTimeSceneInit( HWND hWnd, GUID* pGuidApp )
{
    HRESULT hr;

    m_hWndMain = hWnd;

    // Setup action format for the acutal gameplay
    ZeroMemory( &m_diafGame, sizeof(DIACTIONFORMAT) );
    m_diafGame.dwSize          = sizeof(DIACTIONFORMAT);
    m_diafGame.dwActionSize    = sizeof(DIACTION);
    m_diafGame.dwDataSize      = NUMBER_OF_GAMEACTIONS * sizeof(DWORD);
    m_diafGame.guidActionMap   = *pGuidApp;
    m_diafGame.dwGenre         = DIVIRTUAL_SPACESIM;
    m_diafGame.dwNumActions    = NUMBER_OF_GAMEACTIONS;
    m_diafGame.rgoAction       = g_rgGameAction;
    m_diafGame.lAxisMin        = -10;
    m_diafGame.lAxisMax        = 10;
    m_diafGame.dwBufferSize    = 16;
    _tcscpy( m_diafGame.tszActionMap, _T("Donuts4") );

    // Setup action format for the in-game menus
    ZeroMemory( &m_diafBrowser, sizeof(DIACTIONFORMAT) );
    m_diafBrowser.dwSize          = sizeof(DIACTIONFORMAT);
    m_diafBrowser.dwActionSize    = sizeof(DIACTION);
    m_diafBrowser.dwDataSize      = NUMBER_OF_BROWSERACTIONS * sizeof(DWORD);
    m_diafBrowser.guidActionMap   = *pGuidApp;
    m_diafBrowser.dwGenre         = DIVIRTUAL_BROWSER_CONTROL;
    m_diafBrowser.dwNumActions    = NUMBER_OF_BROWSERACTIONS;
    m_diafBrowser.rgoAction       = g_rgBrowserAction;
    m_diafBrowser.lAxisMin        = -10;
    m_diafBrowser.lAxisMax        = 10;
    m_diafBrowser.dwBufferSize    = 16;
    _tcscpy( m_diafBrowser.tszActionMap, _T("Donuts4 Menu") );

    // Create a new input device manager
    m_pInputDeviceManager = new CInputDeviceManager();
    if( NULL == m_pInputDeviceManager )
        return E_OUTOFMEMORY;

    if( FAILED( hr = m_pInputDeviceManager->Create( hWnd, NULL, m_diafGame,
                                                    StaticInputAddDeviceCB, this ) ) )
        return hr;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CInputManager::RestoreDeviceObjects( D3DFORMAT d3dfmtFullscreen )
{
/*
    HRESULT hr;

    // Create a surface for confguring DInput devices
    hr = g_pd3dDevice->CreateImageSurface( 640, 480, d3dfmtFullscreen, &m_pConfigSurface );
    if( FAILED(hr) )
        return hr;
*/   
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CInputManager::InvalidateDeviceObjects()
{
    SAFE_RELEASE( m_pConfigSurface );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CInputManager::DeleteDeviceObjects()
{
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: StaticInputAddDeviceCB()
// Desc: Static callback helper to call into CMyApplication class
//-----------------------------------------------------------------------------
HRESULT CALLBACK CInputManager::StaticInputAddDeviceCB( 
                                         CInputDeviceManager::DeviceInfo* pDeviceInfo, 
                                         const DIDEVICEINSTANCE* pdidi, 
                                         LPVOID pParam )
{
    CInputManager* pInputManager = (CInputManager*) pParam;
    return pInputManager->InputAddDeviceCB( pDeviceInfo, pdidi );
}




//-----------------------------------------------------------------------------
// Name: InputAddDeviceCB()
// Desc: Called from CInputDeviceManager whenever a device is added. 
//       Set the dead zone, and creates a new InputDeviceState for each device
//-----------------------------------------------------------------------------
HRESULT CInputManager::InputAddDeviceCB( CInputDeviceManager::DeviceInfo* pDeviceInfo, 
                                         const DIDEVICEINSTANCE* pdidi )
{
    // Setup the deadzone 
    DIPROPDWORD dipdw;
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = 500;
    pDeviceInfo->pdidDevice->SetProperty( DIPROP_DEADZONE, &dipdw.diph );

    // Create a new InputDeviceState for each device so the 
    // app can record its state 
    InputDeviceState* pNewInputDeviceState = new InputDeviceState;
    ZeroMemory( pNewInputDeviceState, sizeof(InputDeviceState) );
    pDeviceInfo->pParam = (LPVOID) pNewInputDeviceState;

    if( GET_DIDEVICE_TYPE(pdidi->dwDevType) == DI8DEVTYPE_MOUSE )
    {
        pDeviceInfo->pdidDevice->SetCooperativeLevel( m_hWndMain, DISCL_EXCLUSIVE|DISCL_FOREGROUND );
        m_pMouseDeviceState = pNewInputDeviceState;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc:
//-----------------------------------------------------------------------------
VOID CInputManager::FinalCleanup()
{
    if( m_pInputDeviceManager == NULL )
        return;
    
    // Get access to the list of semantically-mapped input devices
    // to delete all InputDeviceState structs
    CInputDeviceManager::DeviceInfo* pDeviceInfos;
    DWORD dwNumDevices;
    m_pInputDeviceManager->GetDevices( &pDeviceInfos, &dwNumDevices );

    for( DWORD i=0; i<dwNumDevices; i++ )
    {
        InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;
        SAFE_DELETE( pInputDeviceState );
        pDeviceInfos[i].pParam = NULL;
    }

    // Delete input device manager
    SAFE_DELETE( m_pInputDeviceManager );
}




//-----------------------------------------------------------------------------
// Name: StaticConfigureInputDevicesCB()
// Desc: Static callback helper to call into CMyD3DApplication class
//-----------------------------------------------------------------------------
BOOL CALLBACK CInputManager::StaticConfigureInputDevicesCB( IUnknown* pUnknown, VOID* pUserData )
{
    CInputManager* pInputManager = (CInputManager*) pUserData;
    return pInputManager->ConfigureInputDevicesCB( pUnknown );
}



//-----------------------------------------------------------------------------
// Name: ConfigureInputDevicesCB()
// Desc: Callback function for configuring input devices. This function is
//       called in fullscreen modes, so that the input device configuration
//       window can update the screen.
//-----------------------------------------------------------------------------
BOOL CInputManager::ConfigureInputDevicesCB( IUnknown* pUnknown )
{
/*
    if( m_pApp->IsFullScreen() )
    {
        // Get access to the surface
        LPDIRECT3DSURFACE9 pConfigSurface;
        if( FAILED( pUnknown->QueryInterface( IID_IDirect3DSurface9,
                                            (VOID**)&pConfigSurface ) ) )
            return TRUE;

        // Draw the scene, with the config surface blitted on top
        m_pApp->RenderFrame();

        RECT  rcSrc;
        SetRect( &rcSrc, 0, 0, 640, 480 );

        POINT ptDst;
        ptDst.x = (m_pApp->GetScreenWidth()-640)/2;
        ptDst.y = (m_pApp->GetScreenHeight()-480)/2;

        LPDIRECT3DSURFACE9 pBackBuffer;
        g_pd3dDevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer );
        g_pd3dDevice->CopyRects( pConfigSurface, &rcSrc, 1, pBackBuffer, &ptDst );
        pBackBuffer->Release();

        g_pd3dDevice->Present( 0, 0, 0, 0 );

        // Release the surface
        pConfigSurface->Release();
    }
*/
    return TRUE;
}




//-----------------------------------------------------------------------------
// Name: UpdateInput()
// Desc: Processes data from the input device.  Uses GetDeviceState().
//-----------------------------------------------------------------------------
void CInputManager::UpdateInput()
{
    if( NULL == m_pInputDeviceManager )
        return;

    if( m_pMouseDeviceState )
    {
        // Zero all the axis state for the mouse cause
        // these axis are relative so they don't like 
        // to zero on thier own
        m_pMouseDeviceState->fAxisMenuUD = 0.0f;
        m_pMouseDeviceState->fAxisMoveLR = 0.0f;
        m_pMouseDeviceState->fAxisMoveUD = 0.0f;
        m_pMouseDeviceState->fAxisRotateLR = 0.0f;
        m_pMouseDeviceState->fAxisRotateUD = 0.0f;
    }

    // Get access to the list of semantically-mapped input devices
    CInputDeviceManager::DeviceInfo* pDeviceInfos;
    DWORD dwNumDevices;
    m_pInputDeviceManager->GetDevices( &pDeviceInfos, &dwNumDevices );

    // Loop through all devices and check game input
    for( DWORD i=0; i<dwNumDevices; i++ )
    {
        DIDEVICEOBJECTDATA rgdod[10];
        DWORD   dwItems = 10;
        HRESULT hr;
        LPDIRECTINPUTDEVICE8 pdidDevice = pDeviceInfos[i].pdidDevice;
        InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;

        hr = pdidDevice->Acquire();
        hr = pdidDevice->Poll();
        hr = pdidDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA),
                                        rgdod, &dwItems, 0 );
        if( FAILED(hr) )
            continue;

        // Get the sematics codes for the game menu
        for( DWORD j=0; j<dwItems; j++ )
        {
            BOOL  bButtonState = (rgdod[j].dwData==0x80) ? TRUE : FALSE;
//            FLOAT fButtonState = (rgdod[j].dwData==0x80) ? 1.0f : 0.0f;
            FLOAT fAxisState   = (FLOAT)((int)rgdod[j].dwData)/10.0f;

            switch( rgdod[j].uAppData )
            {
                // Handle semantics for normal game play

                // Handle relative axis data
                case INPUT_AXIS_LR: 
                    pInputDeviceState->fAxisRotateLR = fAxisState;
                    break;
                case INPUT_AXIS_UD: 
                    pInputDeviceState->fAxisRotateUD = -fAxisState;
                    break;

                // Handle buttons separately so the button state data
                // doesn't overwrite the axis state data, and handle
                // each button separately so they don't overwrite each other
                case INPUT_TURNLEFT:      pInputDeviceState->bButtonRotateLeft    = bButtonState; break;
                case INPUT_TURNRIGHT:     pInputDeviceState->bButtonRotateRight   = bButtonState; break;
                case INPUT_MOVELEFT:      pInputDeviceState->bButtonMoveLeft      = bButtonState; break;
                case INPUT_MOVERIGHT:     pInputDeviceState->bButtonMoveRight     = bButtonState; break;
                case INPUT_FORWARDTHRUST: pInputDeviceState->bButtonForwardThrust = bButtonState; break;
                case INPUT_REVERSETHRUST: pInputDeviceState->bButtonReverseThrust = bButtonState; break;
                case INPUT_FIREWEAPONS:   pInputDeviceState->bButtonFireWeapons   = bButtonState; break;

                // Handle one-shot buttons
                case INPUT_CTRL:          pInputDeviceState->bButtonCtrl  = bButtonState; break;
                case INPUT_SHIFT:         pInputDeviceState->bButtonShift = bButtonState; break;

                case INPUT_DEBUGMODE:     if( bButtonState && m_UserInput.bButtonShift ) m_pApp->m_bDebugMode = !m_pApp->m_bDebugMode;  break;
                case INPUT_START:         if( bButtonState )                             m_pApp->m_bPaused    = !m_pApp->m_bPaused; break;
                case INPUT_FLYUP:         pInputDeviceState->bButtonFlyUp         = bButtonState; break;
                case INPUT_FLYDOWN:       pInputDeviceState->bButtonFlyDown       = bButtonState; break;

                case INPUT_DISPLAYGAMEMENU:
                    if( bButtonState )
                    {
                        PostMessage( m_hWndMain, WM_CLOSE, 0, 0 );
/*                        
                        PlaySoundEffect( m_pExplosionSphereSound, &g_Profile.ExplosionSphere);
                        m_pCurrentMenu = m_pMainMenu;
                        m_pInputDeviceManager->SetActionFormat( m_diafBrowser, FALSE );
*/
                    }
                    break;

                // Handle semantics for the game menu
                case INPUT_MENU_UD:     pInputDeviceState->fAxisMenuUD = -fAxisState; break;
                case INPUT_MENU_UP:     if( bButtonState ) m_UserInput.bDoMenuUp     = TRUE; break;
                case INPUT_MENU_DOWN:   if( bButtonState ) m_UserInput.bDoMenuDown   = TRUE; break;
                case INPUT_MENU_SELECT: if( bButtonState ) m_UserInput.bDoMenuSelect = TRUE; break;
                case INPUT_MENU_QUIT:   if( bButtonState ) m_UserInput.bDoMenuQuit   = TRUE; break;
                case INPUT_MENU_WHEEL:
                    if( fAxisState > 0.0f )
                        m_UserInput.bDoMenuUp = TRUE; 
                    else
                        m_UserInput.bDoMenuDown = TRUE; 
                    break;
            }
        }
    }

    m_UserInput.bButtonFireWeapons = FALSE; 
    m_UserInput.bButtonCtrl        = FALSE;
    m_UserInput.bButtonShift       = FALSE;
    m_UserInput.fAxisRotateLR = 0.0f;
    m_UserInput.fAxisRotateUD = 0.0f;
    m_UserInput.fAxisMoveUD   = 0.0f;
    m_UserInput.fAxisMoveLR   = 0.0f;
    m_UserInput.fAxisFlyUD    = 0.0f;

    // Accumulate inputs into m_UserInput

    // Concatinate the data from all the DirectInput devices
    for( i=0; i<dwNumDevices; i++ )
    {
        InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;

        // Use the axis data that is furthest from zero
        if( fabs(pInputDeviceState->fAxisRotateLR) > fabs(m_UserInput.fAxisRotateLR) )
            m_UserInput.fAxisRotateLR = pInputDeviceState->fAxisRotateLR;
        if( fabs(pInputDeviceState->fAxisRotateUD) > fabs(m_UserInput.fAxisRotateUD) )
            m_UserInput.fAxisRotateUD = pInputDeviceState->fAxisRotateUD;
        if( fabs(pInputDeviceState->fAxisMoveUD) > fabs(m_UserInput.fAxisMoveUD) )
            m_UserInput.fAxisMoveUD = pInputDeviceState->fAxisMoveUD;
        if( fabs(pInputDeviceState->fAxisMoveLR) > fabs(m_UserInput.fAxisMoveLR) )
            m_UserInput.fAxisMoveLR = pInputDeviceState->fAxisMoveLR;

        // Process the button data 
        if( pInputDeviceState->bButtonRotateRight )
            m_UserInput.fAxisRotateLR = -1.0f;
        else if( pInputDeviceState->bButtonRotateLeft )
            m_UserInput.fAxisRotateLR = 1.0f;

        if( pInputDeviceState->bButtonForwardThrust )
            m_UserInput.fAxisMoveUD = 1.0f;
        else if( pInputDeviceState->bButtonReverseThrust )
            m_UserInput.fAxisMoveUD = -1.0f;

        if( pInputDeviceState->bButtonMoveLeft )
            m_UserInput.fAxisMoveLR = -1.0f;
        else if( pInputDeviceState->bButtonMoveRight )
            m_UserInput.fAxisMoveLR = 1.0f;

        if( pInputDeviceState->bButtonFlyUp )
            m_UserInput.fAxisFlyUD = 1.0f;
        else if( pInputDeviceState->bButtonFlyDown )
            m_UserInput.fAxisFlyUD = -1.0f;

        if( pInputDeviceState->bButtonFireWeapons )
            m_UserInput.bButtonFireWeapons = TRUE;
        if( pInputDeviceState->bButtonCtrl )
            m_UserInput.bButtonCtrl = TRUE;
        if( pInputDeviceState->bButtonShift )
            m_UserInput.bButtonShift = TRUE;
    }
}




//-----------------------------------------------------------------------------
// Name: ViewDevices()
// Desc: 
//-----------------------------------------------------------------------------
void CInputManager::ViewDevices()
{
    // Put action format to game play actions
    m_pInputDeviceManager->SetActionFormat( m_diafGame, FALSE );

    // Configure the devices (with view capability only)
    if( m_pApp->IsFullScreen() )
        m_pInputDeviceManager->ConfigureDevices( m_hWndMain,
                                                    m_pConfigSurface,
                                                    (VOID*)StaticConfigureInputDevicesCB,
                                                    DICD_DEFAULT, this );
    else
        m_pInputDeviceManager->ConfigureDevices( m_hWndMain, NULL, NULL,
                                                    DICD_DEFAULT, this );
}




//-----------------------------------------------------------------------------
// Name: ConfigDevices()
// Desc: 
//-----------------------------------------------------------------------------
void CInputManager::ConfigDevices()
{
    // Put action format to game play actions
    m_pInputDeviceManager->SetActionFormat( m_diafGame, FALSE );

    // Get access to the list of semantically-mapped input devices
    // to delete all InputDeviceState structs before calling ConfigureDevices()
    CInputDeviceManager::DeviceInfo* pDeviceInfos;
    DWORD dwNumDevices;
    m_pInputDeviceManager->GetDevices( &pDeviceInfos, &dwNumDevices );

    for( DWORD i=0; i<dwNumDevices; i++ )
    {
        InputDeviceState* pInputDeviceState = (InputDeviceState*) pDeviceInfos[i].pParam;
        SAFE_DELETE( pInputDeviceState );
        pDeviceInfos[i].pParam = NULL;
    }

    // Configure the devices (with edit capability)
    if( m_pApp->IsFullScreen() )
        m_pInputDeviceManager->ConfigureDevices( m_hWndMain,
                                                    m_pConfigSurface,
                                                    (VOID*)StaticConfigureInputDevicesCB,
                                                    DICD_EDIT, this );
    else
        m_pInputDeviceManager->ConfigureDevices( m_hWndMain, NULL, NULL,
                                                    DICD_EDIT, this );
}




