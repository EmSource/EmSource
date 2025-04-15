//-----------------------------------------------------------------------------
// File: ParticleSystem.h
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once
#include <math.h>
#include <stdio.h>
#include "DXUtil.h"




// Helper function to stuff a FLOAT into a DWORD argument
inline DWORD FtoDW( FLOAT f ) { return *((DWORD*)&f); }




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
class CParticleSystem
{
public:
    //-----------------------------------------------------------------------------
    // Custom vertex types
    //-----------------------------------------------------------------------------
    struct COLORVERTEX
    {
        D3DXVECTOR3 v;
        D3DCOLOR    color;
        FLOAT       tu;
        FLOAT       tv;
    };

    #define D3DFVF_COLORVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)


    struct POINTVERTEX
    {
        D3DXVECTOR3 v;
        D3DCOLOR    color;
    };

    #define D3DFVF_POINTVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)



    //-----------------------------------------------------------------------------
    // Global data for the particles
    //-----------------------------------------------------------------------------
    struct PARTICLE
    {
        BOOL        m_bSpark;     // Sparks are less energetic particles that
                                // are generated where/when the main particles
                                // hit the ground

        D3DXVECTOR3 m_vPos;       // Current position
        D3DXVECTOR3 m_vVel;       // Current velocity

        D3DXVECTOR3 m_vPos0;      // Initial position
        D3DXVECTOR3 m_vVel0;      // Initial velocity
        FLOAT       m_fTime0;     // Time of creation

        D3DXCOLOR   m_clrDiffuse; // Initial diffuse color
        D3DXCOLOR   m_clrFade;    // Faded diffuse color
        FLOAT       m_fFade;      // Fade progression

        PARTICLE*   m_pNext;      // Next particle in list
    };



protected:
    FLOAT     m_fRadius;
    FLOAT     m_fTime;

    DWORD     m_dwBase;
	DWORD     m_dwFlush;
    DWORD     m_dwDiscard;

    DWORD     m_dwParticles;
    DWORD     m_dwParticlesLim;
    PARTICLE* m_pParticles;
    PARTICLE* m_pParticlesFree;

    // Geometry
    LPDIRECT3DVERTEXBUFFER9 m_pVB;

public:
    CParticleSystem( DWORD dwFlush, DWORD dwDiscard, FLOAT fRadius );
   ~CParticleSystem();

    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();

    HRESULT Update( FLOAT fSecsPerFrame, DWORD dwNumParticlesToEmit,
                    const D3DXCOLOR &dwEmitColor, const D3DXCOLOR &dwFadeColor,
                    FLOAT fEmitVel, D3DXVECTOR3 vPosition, BOOL bEmitNewParticles );

    HRESULT Render( const float fWrapOffsetX, const float fWrapOffsetZ );
    HRESULT GetNumActiveParticles() { return m_dwParticles; }
};




