//-----------------------------------------------------------------------------
// File: 3DDrawManager.h
//
// Desc: 3D draw manager.  This is a helper class to draw lines or spheres
//       in the world primary used to debug the physics engine
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

#define MAX_POINTS 500
#define MAX_LINES  500

//-----------------------------------------------------------------------------
// Name: class C3DDrawManager
// Desc: 
//-----------------------------------------------------------------------------
class C3DDrawManager
{
private:
    struct DRAW_LINE_VERTEX
    {
        D3DXVECTOR3 p;
        DWORD		c;
    };
    #define DRAW_LINE_FVF (D3DFVF_XYZ|D3DFVF_DIFFUSE)

    struct DRAW_POINT
    {
        D3DXVECTOR3 vPos;
        float       fSize;        
        DWORD       dwColor;
        DWORD       dwID;
        bool        bValid;
        bool        bInvalidateEveryFrame;
    };

    struct DRAW_LINE
    {
        D3DXVECTOR3 vPosFrom;
        D3DXVECTOR3 vPosTo;
        DWORD       dwColor;
        DWORD       dwID;
        bool        bValid;
        bool        bInvalidateEveryFrame;
    };

public:
    C3DDrawManager(void);
    ~C3DDrawManager(void);

    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT FrameMove( const float fElapsedTime );
    HRESULT Render();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    VOID    FinalCleanup();

    HRESULT AddPoint( D3DXVECTOR3 vPos, float fSize = 1.0f, DWORD dwColor = 0xFFFFFFFF, DWORD dwID = 0, bool bInvalidateEveryFrame = true );
    HRESULT AddLine( D3DXVECTOR3 vPosFrom, D3DXVECTOR3 vPosTo, DWORD dwColor = 0xFFFFFFFF, DWORD dwID = 0, bool bInvalidateEveryFrame = true );
    HRESULT InvalidatePoints( DWORD dwID );
    HRESULT InvalidateLines( DWORD dwID );

public:
    DRAW_POINT m_aPtList[MAX_POINTS];
    DRAW_LINE  m_aLineList[MAX_LINES];
	LPDIRECT3DVERTEXBUFFER9 m_pLineVB;
    DWORD      m_dwNumLines;

    ID3DXMesh* m_pSphere;
};




