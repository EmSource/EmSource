//------------------------------------------------------------------------------
// File: Hall.h
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once

static const DWORD  g_FVFHall = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;


///////////////////////////////////// CHall ///////////////////////////////////////
/*********************************************************************************\
* class CHall
* representation of the "hall" environment, a wall and a floor
\*********************************************************************************/
class CHall
{
public:
    CHall();
    virtual ~CHall();

    HRESULT Initialize( IDirect3DDevice9* pDevice);
    HRESULT RestoreDeviceObjects( IDirect3DDevice9* pDevice);
    HRESULT Render( IDirect3DDevice9* pDevice);
    HRESULT Compose( DWORD t );
    HRESULT SetSpeed( float fSpeed );

// subclasses
public:
    struct Vertex
    {
        D3DVECTOR Pos;
        D3DCOLOR  color;
        float     tu;
        float     tv;
    } Vertex;

private:
    // some textured 3D plane ( a wall or a floor)
    class CPlane
    {
    public:
        CPlane( IDirect3DDevice9* pDevice, 
                TCHAR *achName, 
                LPCTSTR lpResourceName,
                float fTilesU, 
                float fTilesV, 
                D3DXMATRIX& M, 
                float a,
                HRESULT *phr);

        ~CPlane();

        HRESULT Render( IDirect3DDevice9 *pDevice );
        HRESULT SetSpeed( float S);
        HRESULT Compose( DWORD t );

        // data
        IDirect3DTexture9*      m_pTexture;
        struct Vertex           m_V[4];
        D3DXMATRIXA16           m_M;
        TCHAR                   m_achTextureName[MAX_PATH];
        float                   m_fU;
        float                   m_fV;
        float                   m_du;
        float                   m_fSpeed;
    };// class CPlane

// data
public:

private:
    float           m_fSpeed;
    CPlane*         m_pFloor;
    CPlane*         m_pWall;
    D3DLIGHT9       m_light;
};

