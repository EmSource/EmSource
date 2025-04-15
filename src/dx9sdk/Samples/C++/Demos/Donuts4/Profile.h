//-----------------------------------------------------------------------------
// File: Profile.h
//
// Desc: Class to read an ini file and store the information in a 
//       global struct for easy access.
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once


#define MAX_SOURCE_TEXTURES 10
#define MAX_HEIGHT_OF_MAP  1000.0f

enum HEIGHT_CREATE_TYPE { HCT_FromFile=1, HCT_CreateTest };
enum TEXTURE_CREATE_TYPE { TCT_FromFile=1, TCT_CreateTest, TCT_CreateFromHeight, TCT_FromLayers };
enum ENEMY_CREATE_TYPE { ECT_FromFile=1, ECT_CreateTest };
enum ENEMY_MOVEMENT_TYPE { EMT_None=1, EMT_MoveRandom, EMT_MoveTowards };
enum ENEMY_ATTACK_TYPE { EAT_None=1 };




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CZoneStyleParameter
{
public:
    CZoneStyleParameter();

public:
    HEIGHT_CREATE_TYPE HeightCreationType;
    TEXTURE_CREATE_TYPE TextureCreationType;
    DWORD dwTextureSize;
    DWORD dwNumLayers;
    TCHAR szHeightMap[MAX_PATH];
    TCHAR szTextureMap[MAX_PATH];
    TCHAR aLayerTexture[MAX_SOURCE_TEXTURES][MAX_PATH];
    DWORD aLayerColor[MAX_SOURCE_TEXTURES];
    FLOAT aLayerHeight[MAX_SOURCE_TEXTURES];
    FLOAT aLayerTile[MAX_SOURCE_TEXTURES];
    FLOAT aLayerRandomness[MAX_SOURCE_TEXTURES];  
    FLOAT fLayerBlendFactor[MAX_SOURCE_TEXTURES]; 
    BOOL  bSaveMedia;
};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CSkyParameter
{
public:
    CSkyParameter();

public:
    TCHAR szModel[MAX_PATH];
    TCHAR szTextureMap[MAX_PATH];
    DWORD dwFogColor;
    DWORD dwClearColor;
    FLOAT fOffsetY;
    FLOAT fScaleX;
    FLOAT fScaleY;
    FLOAT fScaleZ;
};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CSoundParameter
{
public:
    CSoundParameter();

public:
    TCHAR szFile[MAX_PATH];
    LONG  lBufferCount;
    LONG  lVolume;
    LONG  lSampleRateOffset;
    LONG  lSampleRateDelta;
};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CLightParameter
{
public:
    D3DXVECTOR3 vDirection;
    D3DXVECTOR3 vDiffuse;
    D3DXVECTOR3 vSpecular;
    D3DXVECTOR3 vAmbient;
};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class C3DSoundParameter : public CSoundParameter
{
public:
    D3DVALUE flMinDistance;
    D3DVALUE flMaxDistance;
};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CBulletParameter : public CSoundParameter
{
public:
    float fMass;
    float fDamage;
    float fRechargeTime;
    float fExpireCountdown;
    float fSpeed;

    TCHAR strBulletModel[MAX_PATH];
    C3DModel* pModel;
    DWORD dwAmbientLight;

    BOOL  bUseParticles;
    TCHAR szParticleTextureMap[MAX_PATH];
    float fParticleRadius;
    DWORD dwNumParticlesToEmit;
    DWORD dwParticleColor;
    DWORD dwParticleColorFade;
    float fEmitVel;
    LPDIRECT3DTEXTURE9 pParticleTexture;

};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CShipParameter
{
public:
    float    fShowDelay;
    float    fAccelFactor;
    float    fDecelFactor;
    float    fSpeedFactor;
    float    fRollDecelFactor;
    float    fStartX;
    float    fStartY;
    float    fStartZ;
    float    fMaxSlope;
    float    fFollowTerrianStartHeight;
    float    fFollowTerrianOffset;
    float    fMinHeight;
    float    fFallRate;
    float    fRiseRate;
    float    fMass;
    float    fMaxShield;
};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CThemeStyle
{
public:
    CThemeStyle();
    ~CThemeStyle();

public:
    TCHAR szFile[MAX_PATH];

    CSkyParameter Sky;
    DWORD    dwAmbientLight;

    DWORD           nNumZoneStyles;
    CZoneStyleParameter* aZoneStyles;
    
    int      nNumLights;
    CLightParameter* aLights;

};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CEnemyStyle
{
public:
    CEnemyStyle();
    ~CEnemyStyle();

public:
    ENEMY_CREATE_TYPE EnemyCreationType;
    TCHAR    strEnemyModel[MAX_PATH];
    DWORD    dwEnemyAmbientLight;
    float    fEnemySpeedFactor;
    float    fMoveRandomCountdown;
    float    fThrustCountdown;
    float    fTurnCountdown;
    float    fMoveTowardsAccuracy;
    ENEMY_MOVEMENT_TYPE EnemyMovementType;
    ENEMY_ATTACK_TYPE EnemyAttackType;
    float    fMass;
    float    fMaxHealth;
    float    fInvulnerableCountdown;
    float    fHitAnimationCountdown;
    float    fDeathAnimationCountdown;
    float    fDamage;
    D3DXCOLOR clrAlive;
    D3DXCOLOR clrDead;
    C3DModel* pModel;
};




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
class CProfile
{
public:
    CProfile();
    ~CProfile();

    // Read the ini file
    VOID GetProfile( LPCTSTR szIniName );

protected:
    TCHAR m_szIniName[MAX_PATH]; 
    VOID GetSoundParameters(TCHAR* szSection, CSoundParameter* pSoundParam);
    VOID Get3DSoundParameters(TCHAR* szSection, C3DSoundParameter * p3DSoundParam);
    VOID GetBulletParameters(TCHAR* szSection, CBulletParameter* pBulletParam);
    VOID GetShipParameters(TCHAR* szSection, CShipParameter* pShipParam);
    VOID GetLandType( CZoneStyleParameter* pLandType, TCHAR* strSection );
    VOID GetLight( CLightParameter* pLight, TCHAR* strSection );
    VOID GetSkyParameters( CSkyParameter* pSky, LPCTSTR strSection );
    VOID GetTheme( CThemeStyle* pTheme, TCHAR* strFile );
    VOID GetEnemyStyle( CEnemyStyle* pEnemy, TCHAR* strSection );

    float GetFloat( TCHAR* szSection, TCHAR* szName, TCHAR* szDefault );
    long  GetLong( TCHAR* szSection, TCHAR* szName, TCHAR* szDefault );
    void  GetString( TCHAR* szValue, TCHAR* szSection, TCHAR* szName, TCHAR* szDefault );
    DWORD GetHex( TCHAR* szSection, TCHAR* szName, TCHAR* szDefault );

public:
    CBulletParameter Blaster;

    C3DSoundParameter ExplosionDonut;
    C3DSoundParameter ExplosionPyramid;
    C3DSoundParameter ExplosionCube;
    C3DSoundParameter ExplosionSphere;

    CSoundParameter ChangeShip;
    CSoundParameter ChangeGun;

    CShipParameter Ship;

    BOOL     bLoadAudio;
    BOOL     bRenderSplash;
    BOOL     bRenderGround;
    BOOL     bRenderSky;
    BOOL     bFullScreen;
    BOOL     bLoadFast;
    BOOL     bRenderRadar;
    BOOL     bRenderUI;
    BOOL     bRenderEnemies;
    BOOL     bRenderParticles;
    BOOL     bForceREF;
    BOOL     bForceSoftwareVP;
    BOOL     bForceHardwareVP;

    float    fChangeGunRecharge;
    D3DVALUE flDistanceFactor;
    D3DVALUE flRolloffFactor;
    D3DVALUE flDopplerFactor;    
    long     nNumEnemiesPerLevelScale;
    long     nNumEnemiesBase;
    FLOAT    fFOV;
    DWORD    nRenderTerrianStyle;
    DWORD    nWorldHeight;
    DWORD    nWorldWidth;
    DWORD    dwRenderText;

    BOOL     bGenerateMipMaps;
    BOOL     bOptimizeMesh;
    BOOL     bCompactMesh;
    BOOL     bSimplifyMesh;
    FLOAT    fSimplifyMeshFactor;

    FLOAT    fRenderDist;
    FLOAT    fZFarDist;
    FLOAT    fFogStart;
    FLOAT    fFogEnd;  

    int      nNumThemes;
    CThemeStyle* aThemes;
    BOOL     bForceThemeSelect;
    int      nSelectTheme;

    TCHAR    szUITextureMap[MAX_PATH];
    TCHAR    szSplashTextureMap[MAX_PATH];
    TCHAR    szAudioScript[MAX_PATH];

    int      nNumEnemies;
    CEnemyStyle* aEnemyStyles;
    BOOL     bForceEnemySelect;
    int      nSelectEnemy;

    FLOAT    fTemp[10];
    LONG     nTemp[10];
};

