//{{NO_DEPENDENCIES}}
// Microsoft Developer Studio generated include file.
// Used by [!output PROJECT_NAME].rc
//
#define IDR_MAINFRAME          101
#define IDD_FORMVIEW           102
#define IDI_MAIN_ICON          101 // Application icon
#define IDR_MAIN_ACCEL         113 // Keyboard accelerator
#define IDR_MENU               141 // Application menu
#define IDR_POPUP              142 // Popup menu
#define IDD_SELECTDEVICE       144 // "Change Device" dialog box

#define IDC_DEVICE_COMBO                1000 
#define IDC_ADAPTER_COMBO               1002 
#define IDC_ADAPTERFORMAT_COMBO         1003
#define IDC_RESOLUTION_COMBO            1004
#define IDC_MULTISAMPLE_COMBO           1005 
#define IDC_REFRESHRATE_COMBO           1006
#define IDC_BACKBUFFERFORMAT_COMBO      1007
#define IDC_DEPTHSTENCILBUFFERFORMAT_COMBO 1008
#define IDC_VERTEXPROCESSING_COMBO      1009
#define IDC_PRESENTINTERVAL_COMBO       1010
#define IDC_MULTISAMPLE_QUALITY_COMBO   1011
#define IDC_WINDOW                      1016 
#define IDC_FULLSCREEN                  1018 

#define IDC_RENDERVIEW                  2002
#define IDC_VIEWFULLSCREEN              2003
#define IDC_CHANGEDEVICE                2004
[!if DPLAY]
#define IDD_MULTIPLAYER_CONNECT         10001
#define IDD_MULTIPLAYER_GAMES           10002
#define IDD_MULTIPLAYER_CREATE          10003
#define IDD_LOBBY_WAIT_STATUS           10004
#define IDC_PLAYER_NAME_EDIT            11002
#define IDC_GAMES_LIST                  11003
#define IDC_JOIN                        11004
#define IDC_CREATE                      11005
#define IDC_CONNECTION_LIST             11006
#define IDC_BACK                        11007
#define IDC_EDIT_SESSION_NAME           11009
#define IDC_SEARCH_CHECK                11010
#define IDC_WAIT_TEXT                   11012
[!endif]
[!if DPLAYVOICE]
#define IDD_VOICE_SETUP                 12008
#define IDC_SESSIONCOMPRESION_GROUP     12059
#define IDC_COMPRESSION_COMBO           12060
#define IDC_QUALITY_DEFAULT             12201
#define IDC_QUALITY_SET                 12202
#define IDC_QUALITY_SLIDER              12203
#define IDC_AGGRESSIVENESS_DEFAULT      12301
#define IDC_AGGRESSIVENESS_SET          12302
#define IDC_AGGRESSIVENESS_SLIDER       12303
#define IDC_RECORD_DEFAULT              12501
#define IDC_RECORD_SET                  12502
#define IDC_RECORD_AUTO                 12503
#define IDC_RECORD_SLIDER               12504
#define IDC_THRESHOLD_DEFAULT           12601
#define IDC_THRESHOLD_SET               12602
#define IDC_THRESHOLD_AUTO              12603
#define IDC_THRESHOLD_SLIDER            12604
#define IDC_PLAYBACK_DEFAULT            12701
#define IDC_PLAYBACK_SET                12702
#define IDC_PLAYBACK_SLIDER             12703
[!endif]
#define IDM_CHANGEDEVICE                40002 
#define IDM_TOGGLEFULLSCREEN            40003 
#define IDM_EXIT                        40006 
[!if DINPUT]
#define IDM_CONFIGINPUT                 40011
[!endif]
[!if DPLAYVOICE]
#define IDM_CONFIGVOICE                 40012
[!endif]

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_3D_CONTROLS                1
#define _APS_NEXT_RESOURCE_VALUE        201
#define _APS_NEXT_COMMAND_VALUE         40020
#define _APS_NEXT_CONTROL_VALUE         2005
#define _APS_NEXT_SYMED_VALUE           300
#endif
#endif
