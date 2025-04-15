//-----------------------------------------------------------------------------
// File: ParticleSystem.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CParticleSystem::CParticleSystem( DWORD dwFlush, DWORD dwDiscard, float fRadius )
{
    m_fRadius        = fRadius;

    m_dwBase         = dwDiscard;
    m_dwFlush        = dwFlush;
	m_dwDiscard      = dwDiscard;

    m_dwParticles    = 0;
    m_dwParticlesLim = 2048;

    m_pParticles     = NULL;
    m_pParticlesFree = NULL;
	m_pVB            = NULL;
    m_fTime          = 0.0f;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CParticleSystem::~CParticleSystem()
{
	InvalidateDeviceObjects();

    while( m_pParticles )
    {
        PARTICLE* pSpark = m_pParticles;
        m_pParticles = pSpark->m_pNext;
        delete pSpark;
    }

    while( m_pParticlesFree )
    {
        PARTICLE *pSpark = m_pParticlesFree;
        m_pParticlesFree = pSpark->m_pNext;
        delete pSpark;
    }
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CParticleSystem::RestoreDeviceObjects()
{
    HRESULT hr;

    // Create a vertex buffer for the particle system.  The size of this buffer
    // does not relate to the number of particles that exist.  Rather, the
    // buffer is used as a communication channel with the device.. we fill in 
    // a bit, and tell the device to draw.  While the device is drawing, we
    // fill in the next bit using NOOVERWRITE.  We continue doing this until 
    // we run out of vertex buffer space, and are forced to DISCARD the buffer
    // and start over at the beginning.

    if(FAILED(hr = g_pd3dDevice->CreateVertexBuffer( m_dwDiscard * 
		sizeof(POINTVERTEX), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS, 
		D3DFVF_POINTVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL )))
	{
        return E_FAIL;
	}

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CParticleSystem::InvalidateDeviceObjects()
{
    SAFE_RELEASE( m_pVB );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CParticleSystem::Update( FLOAT fSecsPerFrame, DWORD dwNumParticlesToEmit,
                                 const D3DXCOLOR &clrEmitColor,
                                 const D3DXCOLOR &clrFadeColor, float fEmitVel,
                                 D3DXVECTOR3 vPosition, BOOL bEmitNewParticles )
{
//dwNumParticlesToEmit = 1;
    PARTICLE *pParticle, **ppParticle;
    m_fTime += fSecsPerFrame;

    ppParticle = &m_pParticles;

    while( *ppParticle )
    {
        pParticle = *ppParticle;

        // Calculate new position
        float fT = m_fTime - pParticle->m_fTime0;
        float fGravity;

        if( pParticle->m_bSpark )
        {
            fGravity = -5.0f;
            pParticle->m_fFade -= fSecsPerFrame * 2.25f;
        }
        else
        {
            fGravity = -9.8f;
            pParticle->m_fFade -= fSecsPerFrame * 0.25f;
        }

        pParticle->m_vPos    = pParticle->m_vVel0 * fT + pParticle->m_vPos0;
        pParticle->m_vPos.y += (0.5f * fGravity) * (fT * fT);
        pParticle->m_vVel.y  = pParticle->m_vVel0.y + fGravity * fT;

        if( pParticle->m_fFade < 0.0f )
            pParticle->m_fFade = 0.0f;

        // Kill old particles
        if( pParticle->m_vPos.y < m_fRadius ||
            pParticle->m_bSpark && pParticle->m_fFade <= 0.0f )
        {
            // Emit sparks
            if( !pParticle->m_bSpark )
            {
                for( int i=0; i<4; i++ )
                {
                    PARTICLE *pSpark;

                    if( m_pParticlesFree )
                    {
                        pSpark = m_pParticlesFree;
                        m_pParticlesFree = pSpark->m_pNext;
                    }
                    else
                    {
                        if( NULL == ( pSpark = new PARTICLE ) )
                            return E_OUTOFMEMORY;
                    }

                    pSpark->m_pNext = pParticle->m_pNext;
                    pParticle->m_pNext = pSpark;

                    pSpark->m_bSpark  = TRUE;
                    pSpark->m_vPos0   = pParticle->m_vPos;
                    pSpark->m_vPos0.y = m_fRadius;

                    FLOAT fRand1 = ((FLOAT)rand()/(FLOAT)RAND_MAX) * D3DX_PI * 2.00f;
                    FLOAT fRand2 = ((FLOAT)rand()/(FLOAT)RAND_MAX) * D3DX_PI * 0.25f;

                    pSpark->m_vVel0.x  = pParticle->m_vVel.x * 0.25f + cosf(fRand1) * sinf(fRand2);
                    pSpark->m_vVel0.z  = pParticle->m_vVel.z * 0.25f + sinf(fRand1) * sinf(fRand2);
                    pSpark->m_vVel0.y  = cosf(fRand2);
                    pSpark->m_vVel0.y *= ((FLOAT)rand()/(FLOAT)RAND_MAX) * 1.5f;

                    pSpark->m_vPos = pSpark->m_vPos0;
                    pSpark->m_vVel = pSpark->m_vVel0;

                    D3DXColorLerp( &pSpark->m_clrDiffuse, &pParticle->m_clrFade,
                                   &pParticle->m_clrDiffuse, pParticle->m_fFade );
                    pSpark->m_clrFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
                    pSpark->m_fFade   = 1.0f;
                    pSpark->m_fTime0  = m_fTime;
                }
            }

            // Kill particle
            *ppParticle = pParticle->m_pNext;
            pParticle->m_pNext = m_pParticlesFree;
            m_pParticlesFree = pParticle;

            if(!pParticle->m_bSpark)
                m_dwParticles--;
        }
        else
        {
            ppParticle = &pParticle->m_pNext;
        }
    }

    if( bEmitNewParticles )
    {
        // Emit new particles
        DWORD dwParticlesEmit = m_dwParticles + dwNumParticlesToEmit;
        while( m_dwParticles < m_dwParticlesLim && m_dwParticles < dwParticlesEmit )
        {
            if( m_pParticlesFree )
            {
                pParticle = m_pParticlesFree;
                m_pParticlesFree = pParticle->m_pNext;
            }
            else
            {
                if( NULL == ( pParticle = new PARTICLE ) )
                    return E_OUTOFMEMORY;
            }

            pParticle->m_pNext = m_pParticles;
            m_pParticles = pParticle;
            m_dwParticles++;

            // Emit new particle
            FLOAT fRand1 = ((FLOAT)rand()/(FLOAT)RAND_MAX) * D3DX_PI * 2.0f;
            FLOAT fRand2 = ((FLOAT)rand()/(FLOAT)RAND_MAX) * D3DX_PI * 0.25f;

            pParticle->m_bSpark = FALSE;

            pParticle->m_vPos0 = vPosition + D3DXVECTOR3( 0.0f, m_fRadius, 0.0f );

            pParticle->m_vVel0.x  = cosf(fRand1) * sinf(fRand2) * 2.5f;
            pParticle->m_vVel0.z  = sinf(fRand1) * sinf(fRand2) * 2.5f;
            pParticle->m_vVel0.y  = cosf(fRand2);
            pParticle->m_vVel0.y *= ((FLOAT)rand()/(FLOAT)RAND_MAX) * fEmitVel;

            pParticle->m_vPos = pParticle->m_vPos0;
            pParticle->m_vVel = pParticle->m_vVel0;

            pParticle->m_clrDiffuse = clrEmitColor;
            pParticle->m_clrFade    = clrFadeColor;
            pParticle->m_fFade      = 1.0f;
            pParticle->m_fTime0     = m_fTime;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Renders the particle system using either pointsprites (if supported)
//       or using 4 vertices per particle
//-----------------------------------------------------------------------------
HRESULT CParticleSystem::Render( const float fWrapOffsetX, const float fWrapOffsetZ )
{
    HRESULT hr;

    // TODO: remove particle blur

    // Set the render states for using point sprites
    g_pd3dDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_POINTSIZE,     FtoDW(0.08f) );
    g_pd3dDevice->SetRenderState( D3DRS_POINTSIZE_MIN, FtoDW(0.00f) );
    g_pd3dDevice->SetRenderState( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
    g_pd3dDevice->SetRenderState( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
    g_pd3dDevice->SetRenderState( D3DRS_POINTSCALE_C,  FtoDW(1.00f) );

    // Set up the vertex buffer to be rendered
    g_pd3dDevice->SetStreamSource( 0, m_pVB, 0, sizeof(POINTVERTEX) );
    g_pd3dDevice->SetFVF( D3DFVF_POINTVERTEX );

    PARTICLE*    pParticle = m_pParticles;
    POINTVERTEX* pVertices;
    DWORD        dwNumParticlesToRender = 0;

	// Lock the vertex buffer.  We fill the vertex buffer in small
	// chunks, using D3DLOCK_NOOVERWRITE.  When we are done filling
	// each chunk, we call DrawPrim, and lock the next chunk.  When
	// we run out of space in the vertex buffer, we start over at
	// the beginning, using D3DLOCK_DISCARD.

	m_dwBase += m_dwFlush;

	if(m_dwBase >= m_dwDiscard)
		m_dwBase = 0;

	if(FAILED(hr = m_pVB->Lock( m_dwBase * sizeof(POINTVERTEX), m_dwFlush * sizeof(POINTVERTEX),
		                        (void**) &pVertices, m_dwBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD)))
		return hr;

//    pParticle->m_vVel = D3DXVECTOR3(0,0,0);
//    pParticle->m_vPos = D3DXVECTOR3(0,0,0);

    // Render each particle
    while( pParticle )
    {
        D3DXVECTOR3 vPos(pParticle->m_vPos);
        D3DXVECTOR3 vVel(pParticle->m_vVel);
        FLOAT       fLengthSq = D3DXVec3LengthSq(&vVel);
        UINT        dwSteps;

        vPos.x += fWrapOffsetX;
        vPos.z += fWrapOffsetZ;
//vVel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        if( fLengthSq < 1.0f )        dwSteps = 2;
        else if( fLengthSq <  4.00f ) dwSteps = 3;
        else if( fLengthSq <  9.00f ) dwSteps = 4;
        else if( fLengthSq < 12.25f ) dwSteps = 5;
        else if( fLengthSq < 16.00f ) dwSteps = 6;
        else if( fLengthSq < 20.25f ) dwSteps = 7;
        else                          dwSteps = 8;

//dwSteps = 1;
        vVel *= -0.04f / (FLOAT)dwSteps;

        D3DXCOLOR clrDiffuse;
        D3DXColorLerp(&clrDiffuse, &pParticle->m_clrFade, &pParticle->m_clrDiffuse, pParticle->m_fFade);
        DWORD dwDiffuse = (DWORD) clrDiffuse;

        // Render each particle a bunch of times to get a blurring effect
        for( DWORD i = 0; i < dwSteps; i++ )
        {
            pVertices->v     = vPos;
/*            pVertices->v     = D3DXVECTOR3( (float)((rand() % 100)/100.0f)*100,
                                             20.0f+(float)((rand() % 100)/100.0f)*5,
                                            (float)((rand() % 100)/100.0f)*100 );
*/
            pVertices->color = dwDiffuse;
            pVertices++;

            if( ++dwNumParticlesToRender == m_dwFlush )
            {
                // Done filling this chunk of the vertex buffer.  Lets unlock and
                // draw this portion so we can begin filling the next chunk.

                m_pVB->Unlock();

                if(FAILED(hr = g_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, m_dwBase, dwNumParticlesToRender)))
					return hr;

                // Lock the next chunk of the vertex buffer.  If we are at the 
                // end of the vertex buffer, DISCARD the vertex buffer and start
                // at the beginning.  Otherwise, specify NOOVERWRITE, so we can
                // continue filling the VB while the previous chunk is drawing.
				m_dwBase += m_dwFlush;

				if(m_dwBase >= m_dwDiscard)
					m_dwBase = 0;

				if(FAILED(hr = m_pVB->Lock(m_dwBase * sizeof(POINTVERTEX), m_dwFlush * sizeof(POINTVERTEX),
		            (void**) &pVertices, m_dwBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD)))
                {
					return hr;
                }

                dwNumParticlesToRender = 0;
            }

            vPos += vVel;
        }

        pParticle = pParticle->m_pNext;
    }

    // Unlock the vertex buffer
    m_pVB->Unlock();

    // Render any remaining particles
    if( dwNumParticlesToRender )
    {
        if(FAILED(hr = g_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, m_dwBase, dwNumParticlesToRender )))
			return hr;
    }

    // Reset render states
    g_pd3dDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );

    return S_OK;
}

