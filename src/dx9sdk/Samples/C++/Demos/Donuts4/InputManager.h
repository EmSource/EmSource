//-----------------------------------------------------------------------------
// File: InputManager.h
//
// Desc: Class to handle DirectInput action mapper 
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

class CInputManager
{
public:
    // DirectInput action mapper reports events only when buttons/axis change
    // so we need to remember the present state of relevant axis/buttons for 
    // each DirectInput device.  The CInputDeviceManager will store a 
    // pointer for each device that points to this struct
    struct InputDeviceState
    {
        FLOAT fAxisMoveUD;
        FLOAT fAxisMoveLR;
        BOOL  bButtonForwardThrust;
        BOOL  bButtonReverseThrust;
        BOOL  bButtonFlyDown;
        BOOL  bButtonFlyUp;
        BOOL  bButtonCtrl;
        BOOL  bButtonShift;

        FLOAT fAxisRotateLR;
        FLOAT fAxisRotateUD;
        BOOL  bButtonRotateLeft;
        BOOL  bButtonRotateRight;
        BOOL  bButtonMoveLeft;
        BOOL  bButtonMoveRight;

        BOOL  bButtonFireWeapons;

        // Menu input variables
        FLOAT fAxisMenuUD;
    };

    // Struct to store the current input state
    struct UserInput
    {
        FLOAT fAxisMoveUD;
        FLOAT fAxisMoveLR;
        FLOAT fAxisRotateLR;
        FLOAT fAxisRotateUD;
        FLOAT fAxisFlyUD;
        BOOL  bButtonFireWeapons;
        BOOL  bButtonEnableShield;

        BOOL  bButtonCtrl;
        BOOL  bButtonShift;

        // One-shot variables
        BOOL  bDoChangeView;    

        // Menu input variables
        BOOL  bDoMenuUp;
        BOOL  bDoMenuDown;
        BOOL  bDoMenuSelect;
        BOOL  bDoMenuQuit;

    };

public:
    CInputManager( CMyApplication* pApp );
    ~CInputManager(void);

    HRESULT     OneTimeSceneInit( HWND hWnd, GUID* pGuidApp );
    HRESULT     RestoreDeviceObjects( D3DFORMAT d3dfmtFullscreen );
    void        UpdateInput();
    UserInput*  GetUserInput() { return &m_UserInput; };
    HRESULT     InvalidateDeviceObjects();
    HRESULT     DeleteDeviceObjects();
    VOID        FinalCleanup();

    void        ViewDevices();
    void        ConfigDevices();

    HRESULT InputAddDeviceCB( CInputDeviceManager::DeviceInfo* pDeviceInfo, const DIDEVICEINSTANCE* pdidi );
    static HRESULT CALLBACK StaticInputAddDeviceCB( CInputDeviceManager::DeviceInfo* pDeviceInfo, const DIDEVICEINSTANCE* pdidi, LPVOID pParam );   
    BOOL    ConfigureInputDevicesCB( IUnknown* pUnknown );
    static BOOL CALLBACK StaticConfigureInputDevicesCB( IUnknown* pUnknown, VOID* pUserData );

    // DirectInput objects
    HWND                 m_hWndMain;
    CMyApplication*      m_pApp;
    CInputDeviceManager* m_pInputDeviceManager;     // Class for managing DInput devices
    InputDeviceState*    m_pMouseDeviceState;
    LPDIRECT3DSURFACE9   m_pConfigSurface;          // Surface for config'ing DInput devices
    UserInput            m_UserInput;               // Struct for storing user input 
    DIACTIONFORMAT       m_diafGame;                // Action format for game play
    DIACTIONFORMAT       m_diafBrowser;             // Action format for menu navigation
};
