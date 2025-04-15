//-----------------------------------------------------------------------------
// File: Profile.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CProfile::CProfile()
{
    nNumThemes = 0;
    aThemes = NULL;
    aEnemyStyles = NULL;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CProfile::~CProfile()
{
    SAFE_DELETE_ARRAY( aThemes );
    SAFE_DELETE_ARRAY( aEnemyStyles );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: this function reads our profile into member variables of the profile object.
//-----------------------------------------------------------------------------
VOID CProfile::GetProfile( LPCTSTR szIniName )
{
    HRESULT hr;
    lstrcpy( m_szIniName, szIniName );

    GetBulletParameters( "BULLET1", &Blaster );
    Get3DSoundParameters( "ExplosionDonut", &ExplosionDonut );

    GetShipParameters( "Ship", &Ship );

    bLoadAudio                  = GetLong(  "GLOBAL", TEXT("LoadAudio"),                    TEXT("1") );
    bRenderSplash               = GetLong(  "GLOBAL", TEXT("RenderSplash"),                 TEXT("1") );
    bRenderUI                   = GetLong(  "GLOBAL", TEXT("RenderUI"),                     TEXT("1") );
    bRenderRadar                = GetLong(  "GLOBAL", TEXT("RenderRadar"),                  TEXT("1") );
    bRenderGround               = GetLong(  "GLOBAL", TEXT("RenderGround"),                 TEXT("1") );
    bRenderSky                  = GetLong(  "GLOBAL", TEXT("RenderSky"),                    TEXT("1") );
    bRenderEnemies              = GetLong(  "GLOBAL", TEXT("RenderEnemies"),                TEXT("1") );
    bRenderParticles            = GetLong(  "GLOBAL", TEXT("RenderParticles"),              TEXT("1") );
    bFullScreen                 = GetLong(  "GLOBAL", TEXT("FullScreen"),                   TEXT("0") );
    bLoadFast                   = GetLong(  "GLOBAL", TEXT("LoadFast"),                     TEXT("0") );
    bForceREF                   = GetLong(  "GLOBAL", TEXT("ForceREF"),                     TEXT("0") );
    bForceSoftwareVP            = GetLong(  "GLOBAL", TEXT("ForceSoftwareVP"),              TEXT("0") );
    bForceHardwareVP            = GetLong(  "GLOBAL", TEXT("ForceHardwareVP"),              TEXT("0") );

    fChangeGunRecharge          = GetFloat( "GLOBAL", TEXT("ChangeGunRecharge"),            TEXT("0.5") );
    flDistanceFactor            = GetFloat( "GLOBAL", TEXT("DistanceFactor"),               TEXT("1.0") );
    flRolloffFactor             = GetFloat( "GLOBAL", TEXT("RolloffFactor"),                TEXT("1.0") );
    flDopplerFactor             = GetFloat( "GLOBAL", TEXT("DopplerFactor"),                TEXT("1.0") );

    nNumEnemiesPerLevelScale    = GetLong(  "GLOBAL", TEXT("NumEnemiesPerLevelScale"),      TEXT("2") );
    nNumEnemiesBase             = GetLong(  "GLOBAL", TEXT("NumEnemiesBase"),               TEXT("3") );

    nRenderTerrianStyle         = GetLong(  "GLOBAL", TEXT("RenderTerrainStyle"),           TEXT("1") );
    nWorldHeight                = GetLong(  "GLOBAL", TEXT("WorldHeight"),                  TEXT("3") );
    nWorldWidth                 = GetLong(  "GLOBAL", TEXT("WorldWidth"),                   TEXT("3") );
    dwRenderText                = GetLong(  "GLOBAL", TEXT("RenderText"),                   TEXT("1") );
    fFOV                        = GetFloat( "GLOBAL", TEXT("FOV"),                          TEXT("0.7853") );
    bGenerateMipMaps			= GetLong(  "GLOBAL", TEXT("GenerateMipMaps"),				TEXT("1") );
    bOptimizeMesh               = GetLong(  "GLOBAL", TEXT("OptimizeMesh"),                 TEXT("1") );
    bCompactMesh                = GetLong(  "GLOBAL", TEXT("CompactMesh"),                  TEXT("1") );
    bSimplifyMesh               = GetLong(  "GLOBAL", TEXT("SimplifyMesh"),                 TEXT("1") );
    fSimplifyMeshFactor         = GetFloat( "GLOBAL", TEXT("SimplifyMeshFactor"),           TEXT("0.25") );

    fRenderDist                 = GetFloat( "GLOBAL", TEXT("RenderDist"),                   TEXT("250.0f") );
    fZFarDist                   = GetFloat( "GLOBAL", TEXT("ZFarDist"),                     TEXT("250.0f") );
    fFogStart                   = GetFloat( "GLOBAL", TEXT("FogStart"),                     TEXT("80.0f") );
    fFogEnd                     = GetFloat( "GLOBAL", TEXT("FogEnd"),                       TEXT("300.0f") );

    nNumThemes                  = GetLong( "THEMES", TEXT("NumThemes"),                     TEXT("1") );
    if( NULL == aThemes )
    {
        aThemes = new CThemeStyle[nNumThemes];
        if( NULL == aThemes )
            return;
        ZeroMemory( aThemes, sizeof(CThemeStyle)*nNumThemes );
    }

    for( int iTheme=0; iTheme<nNumThemes; iTheme++ )
    {
        TCHAR strName[MAX_PATH];
        TCHAR strFileName[MAX_PATH];
        TCHAR strFilePath[MAX_PATH];
        wsprintf( strName, "Theme%d", iTheme+1 );
        GetString( strFileName, TEXT("THEMES"), strName, TEXT("theme1.ini") );
        if( FAILED( hr = CMyApplication::FindMediaFileCch( strFilePath, sizeof(strFilePath)/sizeof(TCHAR), strFileName ) ) )
        {
            g_pApp->CleanupAndDisplayError( DONUTSERR_ARTLOADFAILED, strFileName, strFilePath );
            DXTRACE_ERR( TEXT("FindMediaFileCch"), hr );
            return;
        }

        GetTheme( &aThemes[iTheme], strFilePath );
    }

    bForceThemeSelect = GetLong( "THEMES", TEXT("ForceThemeSelect"), TEXT("0") );
    nSelectTheme      = GetLong( "THEMES", TEXT("SelectTheme"),      TEXT("1") ) - 1;

    GetString( szUITextureMap,     TEXT("GLOBAL"), TEXT("UITextureMap"),     TEXT("ui.bmp") );
    GetString( szSplashTextureMap, TEXT("GLOBAL"), TEXT("SplashTextureMap"), TEXT("splash.bmp") );
    GetString( szAudioScript,      TEXT("GLOBAL"), TEXT("AudioScript"),      TEXT("donuts4.spt") );
    

    nNumEnemies         = GetLong( "GLOBAL", TEXT("NumEnemies"),            TEXT("1") );
    bForceEnemySelect   = GetLong( "GLOBAL", TEXT("ForceEnemySelect"),      TEXT("0") );
    nSelectEnemy        = GetLong( "GLOBAL", TEXT("SelectEnemy"),           TEXT("1") ) - 1;
    if( NULL == aEnemyStyles )
    {
        aEnemyStyles = new CEnemyStyle[nNumEnemies];
        if( NULL == aEnemyStyles )
            return;
        ZeroMemory( aEnemyStyles, sizeof(CEnemyStyle)*nNumEnemies );
    }

    for( int iEnemy=0; iEnemy<nNumEnemies; iEnemy++ )
    {
        TCHAR strName[MAX_PATH];
        wsprintf( strName, "ENEMY%d", iEnemy+1 );

        GetEnemyStyle( &aEnemyStyles[iEnemy], strName );
    }

    for( int i=0; i<10; i++ )
    {
        TCHAR strName[MAX_PATH];

        wsprintf( strName, "NTemp%d", i );
        nTemp[i] = GetLong( "GLOBAL", strName, TEXT("1") );
        wsprintf( strName, "FTemp%d", i );
        fTemp[i] = GetFloat( "GLOBAL", strName, TEXT("1.0f") );
    }

}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CProfile::GetEnemyStyle( CEnemyStyle* pEnemyStyle, TCHAR* strSection )
{
    TCHAR strName[MAX_PATH];
    GetString( strName, strSection, TEXT("EnemyCreationType"), TEXT("FromFile") );
    if( lstrcmp( strName, TEXT("FromFile" ) ) == 0 )
        pEnemyStyle->EnemyCreationType = ECT_FromFile;
    else if( lstrcmp( strName, TEXT("CreateTest" ) ) == 0 )
        pEnemyStyle->EnemyCreationType = ECT_CreateTest;

    GetString( pEnemyStyle->strEnemyModel, strSection, TEXT("EnemyModel"), TEXT("enemy.x") );
    pEnemyStyle->fEnemySpeedFactor   = GetFloat( strSection, TEXT("EnemySpeedFactor"),       TEXT("30.0f") );
    pEnemyStyle->dwEnemyAmbientLight = GetHex( strSection, TEXT("EnemyAmbientLight"), TEXT("0x00000000") );

    GetString( strName, strSection, TEXT("EnemyMovementType"), TEXT("MoveRandom") );
    if( lstrcmp( strName, TEXT("None" ) ) == 0 )
        pEnemyStyle->EnemyMovementType = EMT_None;
    else if( lstrcmp( strName, TEXT("MoveRandom" ) ) == 0 )
        pEnemyStyle->EnemyMovementType = EMT_MoveRandom;
    else if( lstrcmp( strName, TEXT("MoveTowards" ) ) == 0 )
        pEnemyStyle->EnemyMovementType = EMT_MoveTowards;
    else
        MessageBox( NULL, "Unknown EnemyMovementType", strName, MB_OK );

    GetString( strName, strSection, TEXT("EnemyAttackType"), TEXT("None") );
    if( lstrcmp( strName, TEXT("None" ) ) == 0 )
        pEnemyStyle->EnemyAttackType = EAT_None;
    else
        MessageBox( NULL, "Unknown EnemyAttackType", strName, MB_OK );

    pEnemyStyle->fMoveRandomCountdown    = GetFloat( strSection, TEXT("MoveRandomCountdown"),        TEXT("1.0f") );
    pEnemyStyle->fThrustCountdown        = GetFloat( strSection, TEXT("ThrustCountdown"),            TEXT("1.0f") );
    pEnemyStyle->fTurnCountdown          = GetFloat( strSection, TEXT("TurnCountdown"),              TEXT("0.1f") );
    pEnemyStyle->fMoveTowardsAccuracy    = GetFloat( strSection, TEXT("MoveTowardsAccuracy"),        TEXT("0.1f") );
    pEnemyStyle->fMaxHealth              = GetFloat( strSection, TEXT("MaxHealth"),                  TEXT("100.0") );
    pEnemyStyle->fMass                   = GetFloat( strSection, TEXT("Mass"),                       TEXT("5.0") );
    pEnemyStyle->fInvulnerableCountdown  = GetFloat( strSection, TEXT("InvulnerableCountdown"),      TEXT("0.0") );
    pEnemyStyle->fHitAnimationCountdown  = GetFloat( strSection, TEXT("HitAnimationCountdown"),      TEXT("1.0") );
    pEnemyStyle->fDeathAnimationCountdown= GetFloat( strSection, TEXT("DeathAnimationCountdown"),    TEXT("1.0") );
    pEnemyStyle->fDamage                 = GetFloat( strSection, TEXT("Damage"),                     TEXT("10.0") );
    DWORD dwColor;
    dwColor                              = GetHex( strSection, TEXT("AliveColor"),                   TEXT("0x00000000") );
    pEnemyStyle->clrAlive = dwColor;
    dwColor                              = GetHex( strSection, TEXT("DeadColor"),                    TEXT("0x00000000") );
    pEnemyStyle->clrDead  = dwColor;
    pEnemyStyle->fMass                   = GetFloat( strSection, TEXT("Mass"),                       TEXT("5.0") );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: This function gets the sound parameters from
//       the specified section of the private profile. 
//-----------------------------------------------------------------------------
VOID CProfile::GetLandType( CZoneStyleParameter* pLandType, TCHAR* strSection )
{
    TCHAR strName[MAX_PATH];

    GetString( strName, strSection, TEXT("HeightCreationType"), TEXT("FromFile") );
    if( lstrcmp( strName, TEXT("FromFile" ) ) == 0 )
        pLandType->HeightCreationType = HCT_FromFile;
    else if( lstrcmp( strName, TEXT("CreateTest" ) ) == 0 )
        pLandType->HeightCreationType = HCT_CreateTest;

    GetString( pLandType->szHeightMap, strSection, TEXT("HeightMap"), TEXT("land.bmp") );

    GetString( strName, strSection, TEXT("TextureCreationType"), TEXT("FromLayers") );
    if( lstrcmp( strName, TEXT("FromFile" ) ) == 0 )
        pLandType->TextureCreationType = TCT_FromFile;
    else if( lstrcmp( strName, TEXT("CreateTest" ) ) == 0 )
        pLandType->TextureCreationType = TCT_CreateTest;
    else if( lstrcmp( strName, TEXT("CreateFromHeight" ) ) == 0 )
        pLandType->TextureCreationType = TCT_CreateFromHeight;
    else if( lstrcmp( strName, TEXT("FromLayers" ) ) == 0 )
        pLandType->TextureCreationType = TCT_FromLayers;

    pLandType->dwTextureSize = GetLong( strSection, TEXT("TextureSize"), TEXT("256") );

    if( pLandType->TextureCreationType == TCT_FromLayers || 
        pLandType->TextureCreationType == TCT_CreateFromHeight )
    {
        pLandType->dwNumLayers           = GetLong( strSection, TEXT("NumLayers"), TEXT("1") );
        assert( pLandType->dwNumLayers <= MAX_SOURCE_TEXTURES );
        for( DWORD iLayer=0; iLayer<pLandType->dwNumLayers; iLayer++ )
        {
            wsprintf( strName, "LayerTexture%d", iLayer+1 );
            GetString( pLandType->aLayerTexture[iLayer], strSection, strName, TEXT("gfx\\land_sand64.bmp") );

            wsprintf( strName, "LayerHeight%d", iLayer+1 );
            pLandType->aLayerHeight[iLayer] = GetFloat( strSection, strName, TEXT("0.0f") ) / MAX_HEIGHT_OF_MAP;

            wsprintf( strName, "LayerTile%d", iLayer+1 );
            pLandType->aLayerTile[iLayer] = GetFloat( strSection, strName, TEXT("4.0f") );

            wsprintf( strName, "LayerRandomness%d", iLayer+1 );
            pLandType->aLayerRandomness[iLayer] = GetFloat( strSection, strName, TEXT("0.05f") );

            wsprintf( strName, "LayerColor%d", iLayer+1 );
            pLandType->aLayerColor[iLayer] = GetHex( strSection, strName, TEXT("0xFF0000FF") );

            wsprintf( strName, "LayerBlendFactor%d", iLayer+1 );
            pLandType->fLayerBlendFactor[iLayer] = GetFloat( strSection, strName, TEXT("1.4f") );
        }
    }

    GetString( pLandType->szTextureMap, strSection, TEXT("TextureMap"), TEXT("land.bmp") );
    pLandType->bSaveMedia = GetLong( strSection, TEXT("SaveMedia"), TEXT("0") );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CProfile::GetSkyParameters( CSkyParameter* pSky, LPCTSTR strSection )
{
    GetString( pSky->szModel, TEXT("SKY"), TEXT("Model"), TEXT("sky-model.x") );
    GetString( pSky->szTextureMap, TEXT("SKY"), TEXT("TextureMap"), TEXT("sky-texture.bmp") );
    pSky->dwFogColor = GetHex( TEXT("SKY"), TEXT("FogColor"), TEXT("0xFF0000FF") );
    pSky->dwClearColor = GetHex( TEXT("SKY"), TEXT("ClearColor"), TEXT("0xFF000000") );
    pSky->fOffsetY   = GetFloat( TEXT("SKY"), TEXT("OffsetY"), TEXT("-400.0f") );
    pSky->fScaleX    = GetFloat( TEXT("SKY"), TEXT("ScaleX"), TEXT("1.0f") );
    pSky->fScaleY    = GetFloat( TEXT("SKY"), TEXT("ScaleY"), TEXT("1.0f") );
    pSky->fScaleZ    = GetFloat( TEXT("SKY"), TEXT("ScaleZ"), TEXT("1.0f") );
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: This function gets the sound parameters from
//       the specified section of the private profile. 
//-----------------------------------------------------------------------------
VOID CProfile::GetSoundParameters(TCHAR* strSection, CSoundParameter* pSoundParam)
{
    TCHAR szBuffer[MAX_PATH];

    GetPrivateProfileString( strSection, TEXT("WavFile"), TEXT("\0"), 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    lstrcpy( pSoundParam->szFile, szBuffer );

    GetPrivateProfileString( strSection, TEXT("SampleRateOffset"), TEXT("0"), 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    pSoundParam->lSampleRateOffset = _ttol(szBuffer);

    GetPrivateProfileString( strSection, TEXT("SampleRateDelta"), TEXT("0"), 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    pSoundParam->lSampleRateDelta = _ttol(szBuffer);

    GetPrivateProfileString( strSection, TEXT("Volume"), TEXT("0"), 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    pSoundParam->lVolume = _ttol(szBuffer);

    GetPrivateProfileString( strSection, TEXT("BufferCount"), TEXT("1"), 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    pSoundParam->lBufferCount = _ttol(szBuffer);
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: Reads the parameters for a bullet from the specified section
//       of the private profile. 
//-----------------------------------------------------------------------------
VOID CProfile::Get3DSoundParameters(TCHAR* strSection, C3DSoundParameter * p3DSoundParam)
{   
    TCHAR szBuffer[MAX_PATH];

    GetSoundParameters(strSection, p3DSoundParam);

    GetPrivateProfileString( strSection, TEXT("MinDistance"), TEXT("0.0"), 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    p3DSoundParam->flMinDistance= (D3DVALUE)_tcstod(szBuffer,TEXT('\0'));

    GetPrivateProfileString( strSection, TEXT("MaxDistance"), TEXT("10.0"), 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    p3DSoundParam->flMaxDistance = (D3DVALUE)_tcstod(szBuffer,TEXT('\0'));
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: Reads the parameters for a bullet from the specified section
//       of the private profile. 
//-----------------------------------------------------------------------------
VOID CProfile::GetBulletParameters(TCHAR* strSection, CBulletParameter * pBulletParam)
{
    GetSoundParameters(strSection, pBulletParam);

    pBulletParam->fRechargeTime     = GetFloat( strSection, TEXT("RechargeTime"), TEXT("1.0f") );
    pBulletParam->fDamage           = GetFloat( strSection, TEXT("Damage"), TEXT("10.0f") );
    pBulletParam->fExpireCountdown  = GetFloat( strSection, TEXT("ExpireCountdown"), TEXT("5.0f") );
    pBulletParam->fSpeed            = GetFloat( strSection, TEXT("Speed"), TEXT("5.0f") );

    pBulletParam->bUseParticles             = GetLong(  strSection, TEXT("UseParticles"), TEXT("1") );
    GetString( pBulletParam->szParticleTextureMap, strSection, TEXT("ParticleTextureMap"), TEXT("particle.bmp") );
    pBulletParam->fParticleRadius           = GetFloat(  strSection, TEXT("ParticleRadius"), TEXT("0.03f") );
    pBulletParam->dwNumParticlesToEmit      = GetLong(  strSection, TEXT("NumParticlesToEmit"), TEXT("10") );
    pBulletParam->dwParticleColor           = GetHex( strSection, TEXT("ParticleColor"), TEXT("0xFFFFFFFF") );
    pBulletParam->dwParticleColorFade       = GetHex( strSection, TEXT("ParticleColorFade"), TEXT("0xFF3030FF") );
    pBulletParam->fEmitVel                  = GetFloat( strSection, TEXT("EmitVel"),                  TEXT("8.0") );
    pBulletParam->fMass                     = GetFloat( strSection, TEXT("Mass"),                      TEXT("5.0") );

    GetString( pBulletParam->strBulletModel, strSection, TEXT("Model"), TEXT("bullet.x") );
    pBulletParam->dwAmbientLight = GetHex( strSection, TEXT("AmbientLight"), TEXT("0x00000000") );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: Reads the parameters for a bullet from the specified section
//       of the private profile. 
//-----------------------------------------------------------------------------
VOID CProfile::GetShipParameters( TCHAR* strSection, CShipParameter * pShipParam)
{
    pShipParam->fShowDelay     = GetFloat( strSection, TEXT("ShowDelay"),     TEXT("2.0") );
    pShipParam->fAccelFactor   = GetFloat( strSection, TEXT("AccelFactor"),   TEXT("5.0") );
    pShipParam->fDecelFactor   = GetFloat( strSection, TEXT("DecelFactor"),   TEXT("0.5") );
    pShipParam->fSpeedFactor   = GetFloat( strSection, TEXT("SpeedFactor"),   TEXT("2.5") );
    pShipParam->fRollDecelFactor  = GetFloat( strSection, TEXT("RollDecelFactor"),   TEXT("0.9") );
    pShipParam->fStartX        = GetFloat( strSection, TEXT("StartX"),       TEXT("0.0") );
    pShipParam->fStartY        = GetFloat( strSection, TEXT("StartY"),       TEXT("0.0") );
    pShipParam->fStartZ        = GetFloat( strSection, TEXT("StartZ"),       TEXT("0.0") );
    pShipParam->fMaxSlope      = GetFloat( strSection, TEXT("MaxSlope"),     TEXT("2.0") );
    pShipParam->fFollowTerrianStartHeight = GetFloat( strSection, TEXT("FollowTerrianStartHeight"),  TEXT("10.0") );
    pShipParam->fFollowTerrianOffset      = GetFloat( strSection, TEXT("FollowTerrianOffset"),       TEXT("10.0") );
    pShipParam->fMinHeight                = GetFloat( strSection, TEXT("MinHeight"),                 TEXT("20.0") );
    pShipParam->fFallRate                 = GetFloat( strSection, TEXT("FallRate"),                 TEXT("5.0") );
    pShipParam->fRiseRate                 = GetFloat( strSection, TEXT("RiseRate"),                 TEXT("50.0") );
    pShipParam->fMass           = GetFloat( strSection, TEXT("Mass"),                 TEXT("5.0") );
    pShipParam->fMaxShield      = GetFloat( strSection, TEXT("MaxShield"),                  TEXT("100.0") );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CProfile::GetLight( CLightParameter* pLight, TCHAR* strSection )
{
    pLight->vDirection.x       = GetFloat( strSection, TEXT("DirectionX"),     TEXT("1.0") );
    pLight->vDirection.y       = GetFloat( strSection, TEXT("DirectionY"),     TEXT("-1.0") );
    pLight->vDirection.z       = GetFloat( strSection, TEXT("DirectionZ"),     TEXT("1.0") );

    pLight->vDiffuse.x       = GetFloat( strSection, TEXT("DiffuseR"),     TEXT("1.0") );
    pLight->vDiffuse.y       = GetFloat( strSection, TEXT("DiffuseG"),     TEXT("1.0") );
    pLight->vDiffuse.z       = GetFloat( strSection, TEXT("DiffuseB"),     TEXT("1.0") );

    pLight->vSpecular.x       = GetFloat( strSection, TEXT("SpecularR"),     TEXT("0.0") );
    pLight->vSpecular.y       = GetFloat( strSection, TEXT("SpecularG"),     TEXT("0.0") );
    pLight->vSpecular.z       = GetFloat( strSection, TEXT("SpecularB"),     TEXT("0.0") );

    pLight->vAmbient.x       = GetFloat( strSection, TEXT("AmbientR"),     TEXT("0.0") );
    pLight->vAmbient.y       = GetFloat( strSection, TEXT("AmbientG"),     TEXT("0.0") );
    pLight->vAmbient.z       = GetFloat( strSection, TEXT("AmbientB"),     TEXT("0.0") );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
VOID CProfile::GetTheme( CThemeStyle* pTheme, TCHAR* strFile )
{
    TCHAR szTmp[MAX_PATH];
    lstrcpy( szTmp, m_szIniName );

    lstrcpy( m_szIniName, strFile );
    lstrcpy( pTheme->szFile, strFile );

    pTheme->nNumZoneStyles = GetLong( "GLOBAL", TEXT("NumZoneStyles"),          TEXT("1") );
    if( NULL == pTheme->aZoneStyles )
    {
        pTheme->aZoneStyles = new CZoneStyleParameter[pTheme->nNumZoneStyles];
        if( NULL == pTheme->aZoneStyles )
            return;
        ZeroMemory( pTheme->aZoneStyles, sizeof(CZoneStyleParameter)*pTheme->nNumZoneStyles );
    }

    for( DWORD iLand=0; iLand<pTheme->nNumZoneStyles; iLand++ )
    {
        TCHAR strSection[MAX_PATH];
        wsprintf( strSection, "ZONESTYLE%d", iLand+1 );
        GetLandType( &pTheme->aZoneStyles[iLand], strSection );
    }

    pTheme->dwAmbientLight = GetHex( TEXT("GLOBAL"), TEXT("AmbientLight"), TEXT("0x44444444") );
    pTheme->nNumLights = GetLong( "GLOBAL", TEXT("NumLights"),          TEXT("1") );
    if( NULL == pTheme->aLights )
    {
        pTheme->aLights = new CLightParameter[pTheme->nNumLights];
        if( NULL == pTheme->aLights )
            return;
        ZeroMemory( pTheme->aLights, sizeof(CLightParameter)*pTheme->nNumLights );
    }

    for( int iLight=0; iLight<pTheme->nNumLights; iLight++ )
    {
        TCHAR strSection[MAX_PATH];
        wsprintf( strSection, "LIGHT%d", iLight+1 );
        GetLight( &pTheme->aLights[iLight], strSection );
    }

    GetSkyParameters( &pTheme->Sky, TEXT("SKY") );

    lstrcpy( m_szIniName, szTmp );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
DWORD CProfile::GetHex( TCHAR* strSection, TCHAR* szName, TCHAR* szDefault )
{
    TCHAR szBuffer[MAX_PATH];
    DWORD dwResult = 0;
    GetPrivateProfileString( strSection, szName, szDefault, 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    if( _stscanf( szBuffer, TEXT("0x%x"), &dwResult ) != 1 )
    {
        dwResult = 0;
    }

    return dwResult;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
float CProfile::GetFloat( TCHAR* strSection, TCHAR* szName, TCHAR* szDefault )
{
    TCHAR szBuffer[MAX_PATH];
    GetPrivateProfileString( strSection, szName, szDefault, 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    return (float)_tcstod(szBuffer,TEXT('\0'));
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
long CProfile::GetLong( TCHAR* strSection, TCHAR* szName, TCHAR* szDefault )
{
    TCHAR szBuffer[MAX_PATH];
    GetPrivateProfileString( strSection, szName, szDefault, 
                             szBuffer, sizeof(szBuffer), m_szIniName ); 
    return _tcstol(szBuffer,TEXT('\0'),10);  
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
void CProfile::GetString( TCHAR* szValue, TCHAR* strSection, TCHAR* szName, TCHAR* szDefault )
{
    GetPrivateProfileString( strSection, szName, szDefault, 
                             szValue, MAX_PATH, m_szIniName ); 
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CSoundParameter::CSoundParameter()
{
    lstrcpy( szFile, TEXT("") );
    lBufferCount        = 1;
    lVolume             = 0L;
    lSampleRateOffset   = 0L;
    lSampleRateDelta    = 0L;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CZoneStyleParameter::CZoneStyleParameter()
{
    HeightCreationType = HCT_FromFile;
    lstrcpy( szHeightMap, TEXT("") );

    TextureCreationType = TCT_FromFile;
    dwNumLayers = 0;
    dwTextureSize = 0;
    for( int i=0; i<MAX_SOURCE_TEXTURES; i++ )
    {
        lstrcpy( aLayerTexture[i], TEXT("") );
        aLayerColor[i] = 0;
        aLayerHeight[i] = 0.0f;
    }
}






//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CSkyParameter::CSkyParameter()
{
    lstrcpy( szModel, TEXT("") );
    lstrcpy( szTextureMap, TEXT("") );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CThemeStyle::CThemeStyle()
{  
    nNumZoneStyles = 0;
    aZoneStyles = NULL;
    aLights = NULL;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CEnemyStyle::CEnemyStyle()
{  
    pModel = NULL;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CEnemyStyle::~CEnemyStyle()
{  
    SAFE_DELETE( pModel );
}




//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CThemeStyle::~CThemeStyle()
{
    SAFE_DELETE_ARRAY( aZoneStyles );
    SAFE_DELETE_ARRAY( aLights );
}
