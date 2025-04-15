//------------------------------------------------------------------------------
// File: CustomMixer.cpp
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "hall.h"
#include "CustomMixer.h"
#include "MultiVMR9_i.c"

// world matrix (combined projection and view)
D3DXMATRIX g_matWorld(
            -0.681917f,   -0.094384f,  -0.725303f, 0.f,
            -0.727560f,    0.189257f,   0.659417f, 0.f,
             0.075027f,    0.977377f,  -0.197721f, 0.f,
          -318.524170f, -210.488570f,  81.793221f, 1.f
                      );

const D3DCOLOR g_colorPale   = D3DCOLOR_RGBA( 0xFD, 0xBB, 0x40, 0x30 );
const D3DCOLOR g_colorGold   = D3DCOLOR_RGBA( 0xFD, 0xBB, 0x40, 0xC0 );

// start position of the left top corner of the first movie screen
const float g_fXStart = -370.f;
const float g_fYStart = -1900.f;
const float g_fZStart = 610.f;

const float g_fMovieSlotWidth = 600.f;  // width of the movie screen
const float g_fMovieSlotHeight = 450.f; // height of the movie screen

const float g_fFrameWidth = 5.f; // width of the frame for the movie screen

const float g_fDelta = 100.f; // distance between movies
const float g_fDarknessRange[] = {-2000.f, -1500.f, 1500.f, 2000.f}; 
const float g_fSpeed = 0.19f; // gait speed

/******************************Public*Routine******************************\
* CGameMixer
*
* constructor
\**************************************************************************/
CGameMixer::CGameMixer(LPUNKNOWN pUnk, HRESULT *phr)
    : CUnknown(NAME("GameMixer Control for MultiVMR9"), pUnk)
    , m_bInitialized( FALSE )
    , m_pOwner( NULL )
    , m_fSpeed( g_fSpeed )
    , m_dwPrevTick( NULL )
    , m_pFont( NULL )
    , m_Left( 0)
    , m_bAnimate( TRUE )
    , m_pActiveMovie( NULL)
{
    float fAspect;
    int i;

    m_matWorld = g_matWorld;

    D3DXVECTOR3 vEye( 0, 0, -700.f );
    D3DXVECTOR3 vAt( 0, 0, 0 );
    D3DXVECTOR3 vUp( 0, 1, 0 );

    m_pFont = new CD3DFont( _T("Trebuchet MS"), 12, D3DFONT_BOLD );

    D3DXMatrixLookAtLH( &m_matView, &vEye, &vAt, &vUp);

    fAspect = 4.f / 3.f;

    D3DXMatrixPerspectiveFovLH( &m_matProj, 
                                D3DX_PI/4.f, // FOV
                                4.f/3.f,     // aspect ratio: always 4:3
                                10.f,        // nearest plane
                                100000.f);   // far plane

    D3DVECTOR vecStart;
    vecStart.x = g_fXStart;
    vecStart.y = g_fYStart;
    vecStart.z = g_fZStart;

    for( i=0; i<8; i++)
    {
        m_Frames[i].Calculate(i, vecStart, NULL);
    }
}

/******************************Public*Routine******************************\
* ~CMultiVMR9MixerControl
*
* destructor
\**************************************************************************/
CGameMixer::~CGameMixer()
{
    CAutoLock Lock(&m_ObjectLock);
    Clean_();
}

///////////////////////// IUnknown /////////////////////////////////////////

/******************************Public*Routine******************************\
* CreateInstance
\**************************************************************************/
CUnknown* CGameMixer::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
    return new CGameMixer(pUnk, phr);
}

/******************************Public*Routine******************************\
* NonDelegatingQueryInterface
\**************************************************************************/
STDMETHODIMP
CGameMixer::NonDelegatingQueryInterface(
    REFIID riid,
    void ** ppv)
{
    HRESULT hr = E_NOINTERFACE;
    *ppv = NULL;

    if (riid == IID_IMultiVMR9MixerControl) 
    {
        hr = GetInterface((IMultiVMR9MixerControl *)this, ppv);
    }
    else 
    {
        hr = CUnknown::NonDelegatingQueryInterface(riid,ppv);
    }
    return hr;
}

///////////////////////// IMultiVMR9MixerControl ///////////////////////////////

/******************************Public*Routine******************************\
* Compose
\**************************************************************************/
STDMETHODIMP
CGameMixer::Compose(
        void* lpParam)
{
    HRESULT hr = S_OK;

    DWORD t = reinterpret_cast<DWORD>(lpParam);
    LONG dt;
    float dy;

    if( 0L == m_dwPrevTick )
    {
        m_dwPrevTick = t;
        return S_OK;
    }

    dt = t - m_dwPrevTick;
    m_dwPrevTick = t;

    CAutoLock Lock(&m_ObjectLock);

    try
    {
        CHECK_HR(
            ( !m_bInitialized ) ? VFW_E_WRONG_STATE : S_OK,
            DbgMsg("CGameMixer::Compose: mixer was not initialized!"));

        if( m_bAnimate )
        {
            // compose the hall
            CHECK_HR(
                hr = m_hall.Compose( t ),
                DbgMsg("CGameMixer::Compose: failed to compose the hall, hr = 0x%08x",hr));
            
            // compose the figure
            CHECK_HR(
                hr = m_character.Compose( t ),
                DbgMsg("CGameMixer::Compose: failed to compose the character, hr = 0x%08x",hr));
            
            // compose frames
            dy = m_fSpeed * dt;

            // check if we have to flip "left"
            if( m_Frames[m_Left].m_S[1].Pos.y +dy > g_fDarknessRange[3])
            {
                m_Frames[m_Left].FlipToEnd( 8 );
                m_Left++;
                if( 8 == m_Left )
                {
                    m_Left = 0;
                }
            }

            // update coordinates for "left"
            m_Frames[m_Left].MoveY( dy );
        }// if animate

    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    return hr;
}

/******************************Public*Routine******************************\
* Compose
\**************************************************************************/
STDMETHODIMP
CGameMixer::Render(
                   IDirect3DDevice9* pDevice, 
                   void *lpParam )
{
    HRESULT hr = S_OK;
    list<CMovie*>::iterator start, end, it;
    CMovie* pMovie = NULL;
    int FrameRate100 = 0;
    int FrameRateAvg100 = 0;
    TCHAR achFrameRate[MAX_PATH];
    
    CComPtr<IMultiVMR9Wizard> pWizard;
    CComPtr<IDirect3DTexture9> pTexture;

    if( !pDevice )
    {
        return E_POINTER;
    }

    CAutoLock Lock(&m_ObjectLock);

    try
    {
        // error if not initialized
        CHECK_HR(
            m_bInitialized ? S_OK : VFW_E_WRONG_STATE,
            DbgMsg("CGameMixer::Render: mixer was not initialized!"));

        CHECK_HR(
            m_pOwner ? S_OK : E_UNEXPECTED,
            DbgMsg("CGameMixer::Render: mixer is initialized, but has no Render engine owner!"));

        CHECK_HR(
            hr = m_pOwner->GetWizardOwner( &(pWizard.p) ),
            DbgMsg("CGameMixer::Render: mixer has owner, but has no parent wizard!"));

        if( m_bAnimate )
        {
            // make sure we are in the right world
            CHECK_HR(
                hr = pDevice->SetTransform( D3DTS_WORLD, &m_matWorld ),
                DbgMsg("CGameMixer::Render: failed to set the world transform, hr = 0x%08x", hr));

            // render the figure
            CHECK_HR(
                hr = m_character.Render( pDevice ),
                DbgMsg("CGameMixer::Render: failed to render the character, hr = 0x%08x", hr));

            // make sure we are in the right world
            CHECK_HR(
                hr = pDevice->SetTransform( D3DTS_WORLD, &m_matWorld ),
                DbgMsg("CGameMixer::Render: failed to set the world transform, hr = 0x%08x", hr));
            


            // render the hall
            CHECK_HR(
                hr = m_hall.Render( pDevice ),
                DbgMsg("CGameMixer::Render: failed to render the hall, hr = 0x%08x", hr));


            // restore device objects for movies
            CHECK_HR(
                hr = RestoreDeviceObjects( pDevice ),
                DbgMsg("CGameMixer::Render: failed in RestoreDeviceObjects, hr = 0x%08x", hr));

            // render all the movies
            start = m_listMovies.begin();
            end = m_listMovies.end();

            if( false == m_listMovies.empty() )
            {
                int Index;
                D3DVECTOR vecStart;

                vecStart.x = g_fXStart;
                vecStart.z = g_fZStart;

                it = start;
                for( int i=0; i<8; i++)
                {
                    pMovie = (CMovie*)(*it);

                    CHECK_HR(
                        pMovie ? S_OK : E_UNEXPECTED,
                        DbgMsg("CGameMixer::Render: FATAL, list contains NULL movies"));

                    CHECK_HR(
                        hr = pWizard->GetTexture( pMovie->m_dwID, &pTexture ),
                        DbgMsg("CGameMixer::Render: failed to get the texture for movie %ld, hr = 0x%08x", pMovie->m_dwID, hr));

                    Index = i - m_Left;
                    if( Index < 0 )
                    {
                        Index += 8;
                    }

                    vecStart.y = m_Frames[m_Left].m_S[0].Pos.y;

                    CHECK_HR(
                        hr = m_Frames[i].Calculate( Index, vecStart, pMovie),
                        DbgMsg("CGameMixer::Render: failed to recalculate coordinates for frame %d, movie %ld, hr = 0x%08x", i, pMovie->m_dwID, hr));

                    CHECK_HR(
                        hr = m_Frames[i].Render( pDevice, pTexture),
                        DbgMsg("CGameMixer::Render: failed to render movie %ld, hr = 0x%08x", pMovie->m_dwID, hr));

                    it++;
                    if( it == end )
                    {
                        it = start;
                    }
                    pTexture = NULL;
                }
            }// if list is not empty
        }// if animate
        else // draw selected movie
        {
            if( m_pActiveMovie )
            {
                D3DXMATRIX matPlainWorld;
                D3DXMatrixIdentity( &matPlainWorld );

                pDevice->SetTransform( D3DTS_WORLD, &matPlainWorld);
                
                // restore device objects for movies
                CHECK_HR(
                    hr = RestoreDeviceObjects( pDevice ),
                    DbgMsg("CGameMixer::Render: failed in RestoreDeviceObjects, hr = 0x%08x", hr));

                CHECK_HR(
                    hr = pWizard->GetTexture( m_pActiveMovie->m_dwID, &pTexture ),
                    DbgMsg("CGameMixer::Render: failed to get the texture for active movie %ld, hr = 0x%08x", m_pActiveMovie->m_dwID, hr));

                CHECK_HR(
                    hr = m_ActiveMovieFrame.CalculateInFocus( m_pActiveMovie ),
                    DbgMsg("CGameMixer::Render: hr = 0x%08x", hr));

                CHECK_HR(
                    hr = m_ActiveMovieFrame.Render( pDevice, pTexture),
                    DbgMsg("CGameMixer::Render: failed to render 'active' movie %ld, hr = 0x%08x", m_pActiveMovie->m_dwID, hr));

                pDevice->SetTransform( D3DTS_WORLD, &m_matWorld );

            }// if active movie
        }

        hr = m_pOwner->GetFrameRate( &FrameRate100 );
        hr = m_pOwner->GetFrameRateAvg( &FrameRateAvg100 );
        _stprintf( achFrameRate, TEXT("FPS: %6.2f\t (average %6.2f fps)"), (float)FrameRate100/100.f, (float)FrameRateAvg100/100.f);

        if( m_pFont )
        {
            m_pFont->DrawText( 20,  570, D3DCOLOR_ARGB(180,133,197,235), achFrameRate );
        }

    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* AddVideoSource
\**************************************************************************/
STDMETHODIMP
CGameMixer::AddVideoSource(
                            DWORD_PTR dwID,
                            LONG lImageWidth,
                            LONG lImageHeight,
                            LONG lTextureWidth,
                            LONG lTextureHeight)
{
    HRESULT hr = S_OK;
    CMovie *pMovie = NULL;
    float dy = 0.f;

    CAutoLock Lock(&m_ObjectLock);

    try
    {
        pMovie = new CMovie( dwID, 
                             lImageWidth, 
                             lImageHeight, 
                             lTextureWidth, 
                             lTextureHeight);
        CHECK_HR(
            pMovie ? S_OK: E_OUTOFMEMORY,
            DbgMsg("CGameMixer::AddVideoSource: failed to create new CMovieFrame object"));

        m_listMovies.push_back( pMovie );
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* DeleteVideoSource
\**************************************************************************/
STDMETHODIMP
CGameMixer::DeleteVideoSource(
                        DWORD_PTR dwID)
{
    HRESULT hr = S_OK;

    list<CMovie*>::iterator start, end, it;
    CMovie* pMovie = NULL;
    CMovie* pMovieRequested = NULL;

    start = m_listMovies.begin();
    end = m_listMovies.end();

    CAutoLock Lock(&m_ObjectLock);

    try
    {
        for( it=start; it!=end; it++)
        {
            pMovie = (CMovie*)(*it);
            
            CHECK_HR(
                pMovie? S_OK : E_UNEXPECTED,
                DbgMsg("CGameMixer::DeleteVideoSource: FATAL, list contains NULL movies!"));
            
            if( dwID == pMovie->m_dwID )
            {
                pMovieRequested = pMovie;
                break;
            }
        }

        CHECK_HR(
            pMovieRequested ? S_OK : VFW_E_NOT_FOUND,
            DbgMsg("CGameMixer::DeleteVideoSource: requested movie ID = 0x%08x was not found in the list", dwID));

        // if movie found, delete it from the list
        m_listMovies.remove( pMovieRequested );
        delete pMovieRequested;
        pMovieRequested = NULL;

    }
    catch(HRESULT hr1)
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* SetRenderEngineOwner
\**************************************************************************/
STDMETHODIMP
CGameMixer::SetRenderEngineOwner(
        IMultiVMR9RenderEngine* pRenderEngine)
{
    HRESULT hr = S_OK;
    CAutoLock Lock(&m_ObjectLock);

    try
    {
        RELEASE( m_pOwner );
        if( pRenderEngine )
        {
            m_pOwner = pRenderEngine;
            m_pOwner->AddRef();
        }
    }
    catch( HRESULT hr1)
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* GetRenderEngineOwner
\**************************************************************************/
STDMETHODIMP
CGameMixer::GetRenderEngineOwner(
        IMultiVMR9RenderEngine** ppRenderEngine)
{
    if( !ppRenderEngine )
    {
        return E_POINTER;
    }
    if( !m_pOwner )
    {
        return VFW_E_NOT_FOUND;
    }

    *ppRenderEngine = m_pOwner;
    (*ppRenderEngine)->AddRef();

    return S_OK;
}

/******************************Public*Routine*****************************\
* Initialize
\**************************************************************************/
STDMETHODIMP
CGameMixer::Initialize(
                       IDirect3DDevice9 *pDevice)
{
    HRESULT hr = S_OK;
    TCHAR achMessage[MAX_PATH];

    CAutoLock Lock(&m_ObjectLock);

    achMessage[0] = TEXT('\0');

    if( m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }

    if( !pDevice )
    {
        return E_POINTER;
    }

    try
    {
        CHECK_HR(
            hr = m_pFont->InitDeviceObjects( pDevice ),
            DbgMsg("CGameMixer::Initialize: failed to initialize font, hr = 0x%08x", hr));

        CHECK_HR(
            hr = m_pFont->RestoreDeviceObjects(),
            DbgMsg("CGameMixer::Initialize: failed to RestoreDeviceObjects for the font, hr = 0x%08x", hr));

        CHECK_HR(
            hr = m_hall.Initialize( pDevice ),
            DbgMsg("CGameMixer::Initialize: failed to initialize the hall, hr = 0x%08x", hr));

        CHECK_HR(
            hr = m_character.Initialize( pDevice ),
            DbgMsg("CGameMixer::Initialize: failed to initialize the character, hr = 0x%08x", hr));

        m_hall.SetSpeed( g_fSpeed );

        CHECK_HR(
            hr = pDevice->SetTransform( D3DTS_VIEW, &m_matView ),
            DbgMsg("CGameMixer::Initialize: failed to set the view matrix, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetTransform( D3DTS_PROJECTION, &m_matProj ),
            DbgMsg("CGameMixer::Initialize: failed to set the projection matrix, hr = 0x%08x", hr));

        m_bInitialized = TRUE;
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    return hr;
}

/******************************Public*Routine******************************\
* RestoreDeviceObjects
\**************************************************************************/
HRESULT CGameMixer::RestoreDeviceObjects( IDirect3DDevice9 *pDevice )
{
    HRESULT hr = S_OK;

    if( !pDevice )
    {
        return E_POINTER;
    }

    try
    {

        CHECK_HR(
            hr = pDevice->SetRenderState( D3DRS_AMBIENT,      0x00FFFFFF ),
            DbgMsg("CGameMixer::RestoreDeviceObjects: failed to set render state D3DRS_AMBIENT/0xFFFFFFFF, hr = 0x%08x",hr));
        CHECK_HR(
            hr = pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE),
            DbgMsg("CGameMixer::RestoreDeviceObjects: failed to set render state D3DRS_CULLMODE/D3DCULL_NONE, hr = 0x%08x",hr));
        CHECK_HR(
            hr = pDevice->SetRenderState(D3DRS_ZENABLE, TRUE),
            DbgMsg("CGameMixer::RestoreDeviceObjects: failed to set render state D3DRS_ZENABLE/FALSE, hr = 0x%08x",hr));

        CHECK_HR(
            hr = pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU ,D3DTADDRESS_CLAMP),
            DbgMsg("CGameMixer::RestoreDeviceObjects: failed to set sampler state D3DSAMP_ADDRESSU/D3DTADDRESS_CLAMP, hr = 0x%08x",hr));
        CHECK_HR(
            hr = pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV ,D3DTADDRESS_CLAMP),
            DbgMsg("CGameMixer::RestoreDeviceObjects: failed to set sampler state D3DSAMP_ADDRESSV/D3DTADDRESS_CLAMP, hr = 0x%08x",hr));

    }
    catch(HRESULT hr1)
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* SetWorldMatrix
\**************************************************************************/
HRESULT CGameMixer::SetWorldMatrix( D3DXMATRIX& M )
{
    m_matWorld = M;
    return S_OK;
}

/******************************Public*Routine******************************\
* Animate
\**************************************************************************/
HRESULT CGameMixer::Animate( BOOL bAnimate)
{
    DWORD_PTR dwID = NULL;
    int nIndex = 0;
    float dY_min;
    float dY_cur;

    m_bAnimate = bAnimate;
    if( m_bAnimate == FALSE )
    {
        // do not stop if movie list is empty
        if( m_listMovies.empty())
        {
            m_bAnimate = TRUE;
            return S_FALSE;
        }
        // select movie that is closest to the center
        nIndex = 0;
        dY_min = (m_Frames[0].m_S[0].Pos.y + m_Frames[0].m_S[1].Pos.y) / 2.f;
        if( dY_min < 0.f )
        {
            dY_min  = - dY_min;
        }
        for( int i=1; i<8; i++)
        {
            dY_cur = (m_Frames[i].m_S[0].Pos.y + m_Frames[i].m_S[1].Pos.y) / 2.f;
            if( dY_cur < 0.f )
            {
                dY_cur  = - dY_cur;
            }
            if( dY_cur < dY_min )
            {
                dY_min = dY_cur;
                nIndex = i;
            }
        }// for

        dwID = m_Frames[nIndex].m_dwID;
        // try to find this movie in the list
        list<CMovie*>::iterator start, end, it;

        m_pActiveMovie = NULL;
        start = m_listMovies.begin();
        end = m_listMovies.end();
        for( it=start; it!=end; it++)
        {
            if( (*it)->m_dwID == dwID )
            {
                m_pActiveMovie = (*it);
                break;
            }
        }
        if( !m_pActiveMovie )
        {
            m_bAnimate = TRUE;
            return S_FALSE;
        }
        return S_OK;
    }

    m_pActiveMovie = NULL;
    return S_OK;
}

////////////////////////////// CMovie /////////////////////////////////////
/******************************Public*Routine******************************\
* CMovie
\**************************************************************************/
CGameMixer::CMovie::CMovie( 
                DWORD_PTR dwID, 
                LONG lImageWidth, 
                LONG lImageHeight, 
                LONG lTextureWidth, 
                LONG lTextureHeight)
    : m_dwID( dwID)
{
    float w;
    float h;
    float ar; // aspect ratio

    m_fU = 1.f;//( lTextureWidth  ) ? (float)lImageWidth/(float)lTextureWidth : 1.f;
    m_fV = 1.f;//( lTextureHeight ) ? (float)lImageHeight/(float)lTextureHeight : 1.f;

    ar = (float)lImageWidth / (float)lImageHeight;

    // try to fit movie withing the width
    w = g_fMovieSlotWidth;
    h = (float)w / ar;

    if( h > g_fMovieSlotHeight )
    {
        h = g_fMovieSlotHeight;
        w = h * ar;
    }

    m_fY = (g_fMovieSlotWidth - w)/2.f;
    m_fZ = (g_fMovieSlotHeight -h)/2.f;
}

////////////////////////////// CFrame /////////////////////////////////////

/******************************Public*Routine******************************\
* CFrame
* constructor
\**************************************************************************/
CGameMixer::CFrame::CFrame( )
{
    int i;

    for( i=0; i<4; i++)
    {
        m_V[i].color = D3DCOLOR_ARGB( 0xCC, 0xFF, 0xFF, 0xFF );
    }
    for( i=0; i<10; i++)
    {
        m_F[i].color = g_colorPale;
    }
}

/******************************Public*Routine******************************\
* Calculate
* calculates position of the movie screen in the "walking girl" scene
\**************************************************************************/
HRESULT CGameMixer::CFrame::Calculate(  int n, 
                                        D3DVECTOR& v0, 
                                        CGameMixer::CMovie* pMovie )
{
    HRESULT hr = S_OK;
    int j;

    if( n<0 || n>8 )
        return E_FAIL;

    float fYShift = -(g_fMovieSlotWidth + g_fDelta) * n;

    float fCenter;
    float c, l, t, r, b, a;
    D3DCOLOR colorFrame;

    float x0 = v0.x;
    float y0 = v0.y;
    float z0 = v0.z;

    float fy = 0.f;
    float fz = 0.f;
    float fU = 0.f;
    float fV = 0.f;

    if( pMovie )
    {
        fy = pMovie->m_fY;
        fz = pMovie->m_fZ;
        fU = pMovie->m_fU;
        fV = pMovie->m_fV;
    }

    m_S[0].Pos.x = x0;
    m_S[0].Pos.y = y0 + fYShift;
    m_S[0].Pos.z = z0;

    m_V[0].Pos.x = m_S[0].Pos.x;  
    m_V[0].Pos.y = m_S[0].Pos.y - fy;   
    m_V[0].Pos.z = m_S[0].Pos.z - fz;

    m_S[1].Pos.x = x0;
    m_S[1].Pos.y = y0 + fYShift - g_fMovieSlotWidth;
    m_S[1].Pos.z = z0;

    m_V[1].Pos.x = m_S[1].Pos.x;  
    m_V[1].Pos.y = m_S[1].Pos.y + fy;   
    m_V[1].Pos.z = m_S[1].Pos.z - fz;

    m_S[2].Pos.x = x0;
    m_S[2].Pos.y = y0 + fYShift;
    m_S[2].Pos.z = z0 - g_fMovieSlotHeight;

    m_V[2].Pos.x = m_S[2].Pos.x;  
    m_V[2].Pos.y = m_S[2].Pos.y - fy;   
    m_V[2].Pos.z = m_S[2].Pos.z + fz;

    m_S[3].Pos.x = x0;
    m_S[3].Pos.y = y0 + fYShift - g_fMovieSlotWidth;
    m_S[3].Pos.z = z0 - g_fMovieSlotHeight;

    m_V[3].Pos.x = m_S[3].Pos.x;  
    m_V[3].Pos.y = m_S[3].Pos.y + fy;   
    m_V[3].Pos.z = m_S[3].Pos.z + fz;

    m_V[0].tu = 0.f;    m_V[0].tv = 0.f;
    m_V[1].tu =  fU;    m_V[1].tv = 0.f;
    m_V[2].tu = 0.f;    m_V[2].tv = fV;
    m_V[3].tu =  fU;    m_V[3].tv = fV;

    // calculate frame

    c = m_V[0].Pos.x;
    a = g_fFrameWidth;
    l = m_V[0].Pos.y;
    r = m_V[1].Pos.y;
    t = m_V[0].Pos.z;
    b = m_V[2].Pos.z;

    m_F[0].Pos.x = c;   m_F[0].Pos.y = l+a;     m_F[0].Pos.z = t+a;
    m_F[1].Pos.x = c;   m_F[1].Pos.y = l;       m_F[1].Pos.z = t;
    m_F[2].Pos.x = c;   m_F[2].Pos.y = r-a;     m_F[2].Pos.z = t+a;
    m_F[3].Pos.x = c;   m_F[3].Pos.y = r;       m_F[3].Pos.z = t;
    m_F[4].Pos.x = c;   m_F[4].Pos.y = r-a;     m_F[4].Pos.z = b-a;
    m_F[5].Pos.x = c;   m_F[5].Pos.y = r;       m_F[5].Pos.z = b;
    m_F[6].Pos.x = c;   m_F[6].Pos.y = l+a;     m_F[6].Pos.z = b-a;
    m_F[7].Pos.x = c;   m_F[7].Pos.y = l;       m_F[7].Pos.z = b;
    m_F[8].Pos.x = c;   m_F[8].Pos.y = l+a;     m_F[8].Pos.z = t+a;
    m_F[9].Pos.x = c;   m_F[9].Pos.y = l;       m_F[9].Pos.z = t;

    fCenter = (m_V[0].Pos.y + m_V[1].Pos.y)/2.f;

    if( fCenter > -350.f && fCenter < 350.f)
    {
        colorFrame = g_colorGold;
    }
    else
    {
        colorFrame = g_colorPale;
    }
    for( j=0; j<10; j++)
    {
        m_F[j].color = colorFrame;
    }

    m_dwID = pMovie? pMovie->m_dwID : NULL;

    return S_OK;
}

/******************************Public*Routine******************************\
* CalculateInFocus
* calculates position of the movie screen in the "in-focus" scene
\**************************************************************************/
HRESULT CGameMixer::CFrame::CalculateInFocus(CGameMixer::CMovie* pMovie)
{
    HRESULT hr = S_OK;

    int i;

    if( !pMovie )
        return E_POINTER;

    float left = -380.f + pMovie->m_fY/600.f*760.f;
    float right = 380.f - pMovie->m_fY/600.f*760.f;
    float top = 285.f - pMovie->m_fZ/450.f*570.f;
    float bottom = -285.f + pMovie->m_fZ/450.f*570.f;

    m_V[0].Pos.x = left;    m_V[0].Pos.y = top;     m_V[0].Pos.z = 0.f;
    m_V[1].Pos.x = right;   m_V[1].Pos.y = top;     m_V[1].Pos.z = 0.f;
    m_V[2].Pos.x = left;    m_V[2].Pos.y = bottom;  m_V[2].Pos.z = 0.f;
    m_V[3].Pos.x = right;   m_V[3].Pos.y = bottom;  m_V[3].Pos.z = 0.f;

    m_V[0].tu = 0.f;            m_V[0].tv = 0.f;
    m_V[1].tu = pMovie->m_fU;   m_V[1].tv = 0.f;
    m_V[2].tu = 0.f;            m_V[2].tv = pMovie->m_fV;
    m_V[3].tu = pMovie->m_fU;   m_V[3].tv = pMovie->m_fV;

    for( i=0; i<4; i++)
    {
        m_V[i].color = D3DCOLOR_RGBA( 0xFF, 0xFF, 0xFF, 0xFF);
    }

    float c = 0.f;
    float a = g_fFrameWidth;
    float l = m_V[0].Pos.x;
    float r = m_V[1].Pos.x;
    float t = m_V[0].Pos.y;
    float b = m_V[2].Pos.y;

    m_F[0].Pos.x = l-a;     m_F[0].Pos.y = t+a;     m_F[0].Pos.z = c;
    m_F[1].Pos.x = l;       m_F[1].Pos.y = t;       m_F[1].Pos.z = c;
    m_F[2].Pos.x = r+a;     m_F[2].Pos.y = t+a;     m_F[2].Pos.z = c;
    m_F[3].Pos.x = r;       m_F[3].Pos.y = t;       m_F[3].Pos.z = c;
    m_F[4].Pos.x = r+a;     m_F[4].Pos.y = b-a;     m_F[4].Pos.z = c;
    m_F[5].Pos.x = r;       m_F[5].Pos.y = b;       m_F[5].Pos.z = c;
    m_F[6].Pos.x = l-a;     m_F[6].Pos.y = b-a;     m_F[6].Pos.z = c;
    m_F[7].Pos.x = l;       m_F[7].Pos.y = b;       m_F[7].Pos.z = c;
    m_F[8].Pos.x = l-a;     m_F[8].Pos.y = t+a;     m_F[8].Pos.z = c;
    m_F[9].Pos.x = l;       m_F[9].Pos.y = t;       m_F[9].Pos.z = c;

    for( i=0; i<10; i++)
    {
        m_F[i].color = g_colorGold;
    }

    return hr;
}

/******************************Public*Routine******************************\
* Render
\**************************************************************************/
HRESULT CGameMixer::CFrame::Render(
                                        IDirect3DDevice9* pDevice,
                                        IDirect3DTexture9* pTexture)
{
    HRESULT hr = S_OK;

    if( !pDevice || !pTexture)
    {
        return E_POINTER;
    }
    try
    {
        CHECK_HR(
            hr = pDevice->SetTexture(0, pTexture),
            DbgMsg("CFrame::Render: failed in SetTexture, hr = 0x%08x",hr));

        CHECK_HR(
            hr = pDevice->SetFVF( g_FVFMixer ),
            DbgMsg("CFrame::Render: failed to set FVF, hr = 0x%08x",hr));

        CHECK_HR(
            hr = pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1),
            DbgMsg("CFrame::Render: failed to set texture stage state D3DTSS_ALPHAOP/D3DTOP_MODULATE, hr = 0x%08x",hr));

        CHECK_HR(
            hr = pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE),
            DbgMsg("CFrame::Render: failed to set texture stage state D3DTSS_ALPHAARG1/D3DTA_TEXTURE, hr = 0x%08x",hr));

        CHECK_HR(
            hr = pDevice->DrawPrimitiveUP(  D3DPT_TRIANGLESTRIP,
                                            2,
                                            (LPVOID)(m_V),
                                            sizeof(m_V[0])),
            DbgMsg("CFrame::Render: failed in DrawPrimitiveUP, hr = 0x%08x", hr));


        CHECK_HR(
            hr = pDevice->SetTexture(0, NULL),
            DbgMsg("CFrame::Render: failed in SetTexture(NULL), hr = 0x%08x",hr));

        // draw frame around the movie

        CHECK_HR(
            hr = pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1),
            DbgMsg("CFrame::Render: failed to set texture stage state D3DTSS_ALPHAOP/D3DTOP_MODULATE, hr = 0x%08x",hr));
        CHECK_HR(
            hr = pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE),
            DbgMsg("CFrame::Render: failed to set texture stage state D3DTSS_ALPHAARG1/D3DTA_TEXTURE, hr = 0x%08x",hr));

        CHECK_HR(
            hr = pDevice->SetFVF( g_FVFframe ),
            DbgMsg("CFrame::Render: failed to set FVFhr = 0x%08x",hr));

        CHECK_HR(
            hr = pDevice->DrawPrimitiveUP(  D3DPT_TRIANGLESTRIP,
                                            8,
                                            (LPVOID)(m_F),
                                            sizeof(m_F[0])),
            DbgMsg("CFrame::Render: failed in DrawPrimitiveUP for the frame, hr = 0x%08x", hr));

    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    return hr;
}

/******************************Public*Routine******************************\
* FlipToEnd
\**************************************************************************/
void CGameMixer::CFrame::FlipToEnd( int N)
{
    float Shift = -( g_fMovieSlotWidth + g_fDelta ) * N;

    MoveY( Shift);
}

/******************************Public*Routine******************************\
* MoveY
\**************************************************************************/
void CGameMixer::CFrame::MoveY( float Shift )
{
    int i;
    for( i=0; i<4; i++)
    {
        //m_V[i].Pos.y += Shift;
        m_S[i].Pos.y += Shift;
    }
    /*
    for( i=0; i<10; i++)
    {
        m_F[i].Pos.y += Shift;
    }
    */
}
///////////////////////////// PRIVATE DOMAIN ///////////////////////////////////

/******************************Private*Routine*****************************\
* Clean_
\**************************************************************************/
void CGameMixer::Clean_()
{
    RELEASE(m_pOwner);

    // clean the list
    list<CMovie*>::iterator start, end, it;
    CMovie *pMovie = NULL;
    
    start = m_listMovies.begin();
    end = m_listMovies.end();

    for( it=start; it!=end; it++)
    {
        pMovie = (CMovie*)(*it);
        if( pMovie )
        {
            delete pMovie;
            pMovie = NULL;
        }
    }
    m_listMovies.clear();

    if( m_pFont )
    {
        m_pFont->InvalidateDeviceObjects();
        m_pFont->DeleteDeviceObjects();
        delete m_pFont;
        m_pFont = NULL;
    }
}


