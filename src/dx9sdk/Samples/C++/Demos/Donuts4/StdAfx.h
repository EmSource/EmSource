//----------------------------------------------------------------------------
// File: stdafx.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

#ifndef STRICT
#define STRICT
#endif

#define DIRECTINPUT_VERSION     0x0900
#define D3D_OVERLOADS
#include <tchar.h>
#include <Windows.h>
#include <mmsystem.h>
#include <windowsx.h>
#include <basetsd.h>
#include <cguid.h>
#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <dmerror.h>
#include <dmusicc.h>
#include <dmusici.h>
#include <dsound.h>
#include <dxerr9.h>

// Simple function for generating random numbers
inline FLOAT rnd( FLOAT low, FLOAT high )
{
    return low + ( high - low ) * ( (FLOAT)rand() ) / RAND_MAX;
}

FLOAT rnd( FLOAT low=-1.0f, FLOAT high=1.0f );

#include "D3DFile.h"
#include "D3DFont.h"
#include "D3DUtil.h"
#include "DIUtil.h"
#include "DMUtil.h"
#include "DSUtil.h"
#include "DXUtil.h"
#include "resource.h"
#include "3DDrawManager.h"
#include "3dmodel.h"
#include "gamemenu.h"
#include "filewatch.h"
#include "profile.h"
#include "notifytool.h"
#include "TerrainMesh.h"
#include "TerrainEngine.h"
#include "displayobject.h"
#include "3ddisplayobject.h"
#include "enemyship.h"
#include "playership.h"
#include "bullet.h"
#include "FileWatch.h"
#include "D3DFont.h"
#include "D3DUtil.h"
#include "notifytool.h"
#include "ParticleSystem.h"
#include "inputmanager.h"
#include "donuts.h"

extern HINSTANCE                    g_hInst;
extern CProfile                     g_Profile;
extern CTerrainEngine*              g_pTerrain;
extern CMyApplication*              g_pApp;              
extern CInputManager::UserInput*    g_pUserInput;              
extern IDirect3DDevice9*            g_pd3dDevice;
extern C3DDrawManager*              g_p3DDrawManager;
    
// For debugging
extern D3DXVECTOR3                  g_vDebugMove;
extern D3DXVECTOR3                  g_vDebugRotate;
extern BOOL                         g_bDebugFreezeZoneRender;
extern BOOL                         g_bDebugIsZoneRenderFroze;
extern BOOL                         g_bDebugFreezeZoneRender;     
extern CEnemyShip*                  g_pDebugFirstEnemy;            


D3DXMATRIX* Donuts_MatrixOrthroNormalize( D3DXMATRIX* pOut, D3DXMATRIX* pM );
