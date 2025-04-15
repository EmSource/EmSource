//-----------------------------------------------------------------------------
// File: Donuts.h
//
// Desc: Donuts 4 game.  Uses Direct3D, DirectMusic, DirectSound, DirectInput 
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once


//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
// Error codes
#define DONUTSERR_NODIRECT3D       0x00000001
#define DONUTSERR_NOD3DDEVICE      0x00000002
#define DONUTSERR_ARTLOADFAILED    0x00000003
#define DONUTSERR_NOINPUT          0x00000004

// States the app can be in
enum APP_STATE_TYPE
{ 
    APPSTATE_LOADSPLASH, 
    APPSTATE_DISPLAYSPLASH, 
    APPSTATE_ACTIVE, 
    APPSTATE_WAITFORMUSICEND, 
    APPSTATE_TRIGGERLEVELSCREEN, 
    APPSTATE_BEGINLEVELSCREEN, 
    APPSTATE_DISPLAYLEVELSCREEN, 
    APPSTATE_BEGINACTIVESCREEN 
};

// Bullet types
enum BULLET_TYPE
{ 
    BULLET_BLASTER=0 
};

// Object dimensions and fixed properties
#define MAX_AUDIOPATHS     12

// Defines for the in-game menu
#define MENU_MAIN           1
#define MENU_SOUND          2
#define MENU_VIDEO          3
#define MENU_INPUT          4
#define MENU_VIEWDEVICES    5
#define MENU_CONFIGDEVICES  6
#define MENU_WINDOWED       7
#define MENU_640x480        8
#define MENU_800x600        9
#define MENU_1024x768      10
#define MENU_BACK          11
#define MENU_SOUNDON       12
#define MENU_SOUNDOFF      13
#define MENU_QUIT          14


//-----------------------------------------------------------------------------
// Name: C3DAudioPath
// Desc: 
//-----------------------------------------------------------------------------
class C3DAudioPath
{
public:
    C3DAudioPath() { m_pPath = NULL; m_pObject = NULL; m_fDistance = FLT_MAX; m_bReplaceSound = FALSE; };
    ~C3DAudioPath() { SAFE_RELEASE(m_pPath); };

    FLOAT                   m_fDistance;      // Distance, for comparisons
    BOOL                    m_bReplaceSound;  // Set when a sound is swapped or removed from this path.
    IDirectMusicAudioPath*  m_pPath;          // Audiopath 
    CDisplayObject*         m_pObject;        // Object that this sonifies
};




//-----------------------------------------------------------------------------
// Custom Direct3D vertex types
//-----------------------------------------------------------------------------
struct SCREENVERTEX
{
    D3DXVECTOR4 p;
    DWORD       color;
    FLOAT       tu, tv;
};

struct SPRITEVERTEX
{
    D3DXVECTOR3 p;
    DWORD       color;
    FLOAT       tu, tv;
};

struct MODELVERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR3 n;
    FLOAT       tu, tv;
};

#define D3DFVF_SCREENVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define D3DFVF_SPRITEVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define D3DFVF_MODELVERTEX  (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)




//-----------------------------------------------------------------------------
// Inline helper functions
//-----------------------------------------------------------------------------


// Convenient macros for playing sounds
inline VOID PlaySoundEffect( CMusicSegment* pSoundEffect, CSoundParameter* pSoundParameter )
{
    LONG lFrequency;
    
    lFrequency = pSoundParameter->lSampleRateOffset + (LONG)rnd((FLOAT)(-pSoundParameter->lSampleRateDelta),(FLOAT)(pSoundParameter->lSampleRateDelta));

    if (pSoundEffect)
    {   
        pSoundEffect->Play( DMUS_SEGF_SECONDARY, NULL ); // TODO: update , pSoundParameter->lVolume, lFrequency );
    }
}

class CTerrainEngine;


//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
LRESULT CALLBACK StaticMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


struct FRECT
{
    float top;
    float bottom;
    float left;
    float right;
};


//-----------------------------------------------------------------------------
// Name: class CMyApplication 
// Desc: Application class.
//-----------------------------------------------------------------------------
class CMyApplication 
{
public:
    CMyApplication();

    HRESULT Create( HINSTANCE hInstance );
    INT     Run();
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    VOID    SetAppState( DWORD dwAppState ) { m_dwAppState = dwAppState; }
    DWORD   GetScreenWidth() { return m_dwScreenWidth; }
    DWORD   GetScreenHeight() { return m_dwScreenHeight; }
    float   GetAppTime() { return m_fTime; }
    CPlayerShip* GetPlayerShip() { return m_pShip; }
    BOOL    IsFullScreen() { return m_bFullScreen; }
    HRESULT RenderFrame();
    HRESULT UpdateFarthestAudioPath();

    static HRESULT FindMediaFileCch( TCHAR* strPath, const long cchPath, const TCHAR* strFile );

    // Error handling
    VOID             CleanupAndDisplayError( DWORD dwError, TCHAR* strArg1, TCHAR* strArg2 );

protected:
    HRESULT          OneTimeSceneInit( HWND hWnd );
    HRESULT          UpdateScene();
    VOID             FrameMove();
    HRESULT          RenderScene();
    VOID             FinalCleanup();
    HRESULT          ReloadWorld();

    // Sound functions
    HRESULT          CreateSoundObjects( HWND hWnd );
    VOID             DestroySoundObjects();

    // Display functions
    HRESULT          InitDeviceObjects( HWND hWnd );
    HRESULT          RestoreDeviceObjects();
    HRESULT          InvalidateDeviceObjects();
    HRESULT          DeleteDeviceObjects();
    HRESULT          SwitchDisplayModes( BOOL bFullScreen, DWORD dwWidth, DWORD dwHeight );

    // Menu functions
    VOID             ConstructMenus();
    VOID             DestroyMenus();
    VOID             UpdateMenus();

    // Rendering functions
    VOID             RenderSplash();
    VOID             DarkenScene( FLOAT fAmount );
    VOID             RenderFieryText( CD3DFont* pFont, TCHAR* strText );
    HRESULT          RenderRadarTexture();

protected:
    // Misc game functions
    VOID             UpdateCullInfo( CULLINFO* pCullInfo, D3DXMATRIXA16* pMatView, D3DXMATRIXA16* pMatProj );
    VOID             DisplayLevelIntroScreen( DWORD dwLevel );
    VOID             AdvanceLevel();
    VOID             CheckForHits();
    bool             IntersectRects( FRECT* pRect1, FRECT* pRect2 );
    VOID             CreateEnemy( DWORD dwEnemyStyle, D3DXVECTOR3* pvPosition, float fRotateY );

    HRESULT          LoadTerrainModel();
    HRESULT          LoadShipModel();
    HRESULT          SwitchModel();

public:
    DWORD                m_dwWindowStyle;
    RECT                 m_rcWindowBounds;
    RECT                 m_rcWindowClient;

    BOOL                m_bDebugMode;
    BOOL                m_bWireMode;
    BOOL                m_bPaused;    

    TCHAR*               m_strAppName;
    HWND                 m_hWndMain;                // Main window
    DWORD                m_dwScreenWidth;           // Dimensions for fullscreen modes
    DWORD                m_dwScreenHeight;
    D3DDISPLAYMODE       m_DesktopMode;
    D3DFORMAT            m_d3dfmtFullscreen;        // Pixel format for fullscreen modes
    D3DFORMAT            m_d3dfmtTexture;           // Pixel format for textures
    BOOL                 m_bFullScreen;             // Whether app is fullscreen (or windowed)
    BOOL                 m_bIsActive;               // Whether app is active
    BOOL                 m_bDisplayReady;           // Whether display class is initialized
    BOOL                 m_bMouseVisible;           // Whether mouse is visible
    HBITMAP              m_hSplashBitmap;           // Bitmap for splash screen
    FLOAT                m_fPhysicsSimCaryyOver;

    DWORD                m_dwAppState;              // Current state the app is in
    DWORD                m_dwLevel;                 // Current game level
    DWORD                m_dwScore;                 // Current game score
    LONG                 m_lSpeed;
    int                  m_nCurTheme;
    float                m_fRadarTextureX;
    float                m_fRadarTextureY;

    // Player view mode
    CD3DCamera              m_Camera;                  // Camera used for 3D scene
    CULLINFO                m_cullinfo;                // Cull info updated from camera position

    // Display list and player ship
    CPlayerShip*            m_pShip;                   // Player's display object
	C3DModel*				m_pShipModel;

    // DirectDraw/Direct3D objects
    D3DPRESENT_PARAMETERS   m_d3dpp;
    LPDIRECT3DVERTEXBUFFER9 m_pViewportVB;
    LPDIRECT3DVERTEXBUFFER9 m_pRadarVB;
    LPDIRECT3DVERTEXBUFFER9 m_pSpriteVB;

    // Sky
    CD3DMesh*               m_pSkyDome;                

    // DirectMusic objects
    CMusicManager*          m_pMusicManager;           // Class to manage DMusic objects
    CMusicScript*           m_pMusicScript;
    LPDIRECTSOUND3DLISTENER m_p3DListener;
    C3DAudioPath            m_AudioPath[MAX_AUDIOPATHS];
    C3DAudioPath*           m_pFarthestAudioPath;
    IDirectMusicAudioPath*  m_pEnginePath;  // AudioPath to manage engine sounds.

    CMusicSegment*          m_pBullet1Sound;

    CMusicSegment*          m_pExplosionDonutSound;

    // Game objects
    LPDIRECT3DTEXTURE9      m_pUITexture;
    LPDIRECT3DTEXTURE9      m_pSplashTexture;
    LPDIRECT3DTEXTURE9      m_pSkyTexture;
    LPDIRECT3DTEXTURE9      m_pRadarTexture;
    LPDIRECT3DTEXTURE9      m_pTempRadarTexture;
    CD3DFont*               m_pGameFont;               // Font for displaying score, etc.
    CD3DFont*               m_pMenuFont;               // Font for displaying in-game menus

    CInputManager*          m_pInputManager;
    C3DDrawManager*         m_p3DDrawManager;

    // Menu objects
    CMenuItem*              m_pMainMenu;               // Menu class for in-game menus
    CMenuItem*              m_pQuitMenu;
    CMenuItem*              m_pCurrentMenu;

    DWORD                   m_dwNumVerts;

    FLOAT                   m_fTime;             // Current time in seconds
    FLOAT                   m_fElapsedTime;      // Time elapsed since last frame
    FLOAT                   m_fFPS;              // Instanteous frame rate
    TCHAR                   m_strDeviceStats[90];// String to hold D3D device stats

public:
    TCHAR m_strProfilePath[MAX_PATH];
    TCHAR m_strCurrentWorkingDir[MAX_PATH];
    TCHAR m_strEffectsFiles[10][MAX_PATH];
    int m_nEffectsFiles;

    HRESULT FindMedia( HWND hWnd, TCHAR* strFilePath, TCHAR* strFileName );

    CFileWatch* m_pFileWatch;
};

