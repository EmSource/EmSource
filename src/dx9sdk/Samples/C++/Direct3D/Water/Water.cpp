//-----------------------------------------------------------------------------
// File: Water.cpp
//
// Desc: 
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <Windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <stdio.h>
#include <d3dx9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFont.h"
#include "resource.h"

#define WATER_DEPTH 20.0f
#define WATER_CAUSTICS_SIZE 128

//-----------------------------------------------------------------------------
// Name: CEnvironment
// Desc: The environment that is reflected in the water
//-----------------------------------------------------------------------------
class CEnvironment
{
public:
    CEnvironment();
   ~CEnvironment();

    HRESULT Initialize(float fSize);

    HRESULT OnCreateDevice(IDirect3DDevice9* pDevice);
    HRESULT OnResetDevice();
    HRESULT OnLostDevice();
    HRESULT OnDestroyDevice();

    HRESULT SetSurfaces(
        IDirect3DTexture9* pXNeg, IDirect3DTexture9* pXPos, 
        IDirect3DTexture9* pYNeg, IDirect3DTexture9* pYPos,
        IDirect3DTexture9* pZNeg, IDirect3DTexture9* pZPos); 
        
    HRESULT Draw();

protected:
    float m_fSize;

    IDirect3DDevice9* m_pDevice;
    IDirect3DTexture9* m_pSurf[6];
};

struct WATER_REFRACT
{
    // Vrefract = (V + refract * N) * norm
    float fRefract;
    float fRefractNorm; 
    DWORD dwDiffuse;
};


struct WATER_SURFACE
{
    float fHeight;
    float fVelocity;
};


//-----------------------------------------------------------------------------
// Name: CWater
// Desc: The water that is rendered
//-----------------------------------------------------------------------------
class CWater
{
    FLOAT m_fSize;
    FLOAT m_fDepth;
    FLOAT m_fScaleTex;
    FLOAT m_fAvgHeight;

    FLOAT m_fSphereHeight;
    FLOAT m_fSphereRadius2;

    UINT m_uIndices;
    UINT m_uVertices;

    WATER_SURFACE *m_pSurface;
    WATER_REFRACT *m_pRefract;

    IDirect3DDevice9       *m_pDevice;
    IDirect3DIndexBuffer9  *m_pibIndices;
    IDirect3DVertexBuffer9 *m_pvbVertices;
    IDirect3DVertexBuffer9 *m_pvbCaustics;

public:
    CWater();
   ~CWater();

    HRESULT Initialize(float fSize, float fDepth);

    HRESULT OnCreateDevice(IDirect3DDevice9 *pDevice);
    HRESULT OnResetDevice();
    HRESULT OnLostDevice();
    HRESULT OnDestroyDevice();

    HRESULT Drop();
    HRESULT Update(D3DXVECTOR3 &vecPos, D3DXVECTOR3 &vecLight, BOOL bCalcCaustics);

    HRESULT DrawCaustics();
    HRESULT DrawSurface();
};


//-----------------------------------------------------------------------------
// Name: CMyD3DApplication
// Desc: 
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
public:
    CMyD3DApplication();
    HRESULT GetNextTechnique(INT nDir, BOOL bBypassValidate);

    virtual HRESULT OneTimeSceneInit();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual HRESULT FrameMove();
    virtual HRESULT Render();
    virtual HRESULT FinalCleanup();

    virtual LRESULT MsgProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

private:
    CWater                 m_Water;
    CEnvironment           m_Environment;

    LPD3DXEFFECT           m_pEffect;
    UINT                   m_iTechnique;
    LPD3DXRENDERTOSURFACE  m_pRenderToSurface;

    D3DXVECTOR4            m_vecLight;
    D3DXCOLOR              m_colorLight;

    LPDIRECT3DTEXTURE9     m_pFloorTex;
    LPDIRECT3DTEXTURE9     m_pCausticTex;
    LPDIRECT3DSURFACE9     m_pCausticSurf;
    LPDIRECT3DTEXTURE9     m_pSkyTex[6];
    LPDIRECT3DCUBETEXTURE9 m_pSkyCubeTex;

    CD3DFont*              m_pFont;
    CD3DFont*              m_pFontSmall;

    BYTE        m_bKey[256];

    BOOL        m_bPause;
    BOOL        m_bDrawWater;
    BOOL        m_bDrawCaustics;
    BOOL        m_bDrawEnvironment;
    BOOL        m_bShowHelp;

    FLOAT       m_fSpeed;
    FLOAT       m_fAngularSpeed;
    FLOAT       m_fTime;
    FLOAT       m_fSecsPerFrame;

    D3DXVECTOR3 m_vecVelocity;
    D3DXVECTOR3 m_vecAngularVelocity;

    D3DXMATRIXA16  m_matIdentity;
    D3DXMATRIXA16  m_matView;
    D3DXMATRIXA16  m_matPosition;
    D3DXMATRIXA16  m_matProjection;
};




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything, and goes into a
//       message-processing loop. Idle time is used to render the scene.
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    CMyD3DApplication d3dApp;

    InitCommonControls();
    if( FAILED( d3dApp.Create( hInst ) ) )
        return 0;

    return d3dApp.Run();
}




//-----------------------------------------------------------------------------
// Name: CMyD3DApplication
// Desc:
//-----------------------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
{
    m_strWindowTitle    = _T("Water");
    m_d3dEnumeration.AppUsesDepthBuffer   = TRUE;

    m_pFont         = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pFontSmall    = new CD3DFont( _T("Arial"),  9, D3DFONT_BOLD );

    // Water
    m_pEffect       = NULL;
    m_iTechnique    = 0;

    m_vecLight      = D3DXVECTOR4(0.5f, -1.0f, 1.0f, 0.0f);
    m_colorLight    = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    m_pFloorTex     = NULL;
    m_pCausticTex   = NULL;
    m_pCausticSurf  = NULL;
    m_pSkyCubeTex   = NULL;

    for(UINT i = 0; i < 6; i++)
        m_pSkyTex[i] = NULL;

    // Misc
    memset(m_bKey, 0x00, sizeof(m_bKey));

    m_fSpeed        = 25.0f;
    m_fAngularSpeed = 1.0f;
    m_fSecsPerFrame = 0.0f;
    m_fTime         = 0.0f;

    m_vecVelocity        = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_vecAngularVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    D3DXMatrixIdentity(&m_matIdentity);
    D3DXMatrixIdentity(&m_matView);
    D3DXMatrixIdentity(&m_matPosition);
    D3DXMatrixIdentity(&m_matProjection);

    m_bShowHelp         = FALSE;
    m_bPause            = FALSE;
}




//-----------------------------------------------------------------------------
// Name: GetNextTechnique
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::GetNextTechnique(INT nDir, BOOL bBypassValidate)
{
    D3DXEFFECT_DESC effect;
    UINT iTechnique = m_iTechnique;

    m_pEffect->GetDesc(&effect);

    for(;;)
    {
        iTechnique += nDir;

        // cast is needed because iTechnique is unsigned, so always >= 0
        if(((INT_PTR)iTechnique) < 0)
            iTechnique = effect.Techniques - 1;

        if(iTechnique >= effect.Techniques)
            iTechnique = 0;

        if(nDir && (iTechnique == m_iTechnique))
            break;

        if(!nDir)
            nDir = 1;

        m_pEffect->SetTechnique(m_pEffect->GetTechnique( iTechnique ));

        if(bBypassValidate || (iTechnique == effect.Techniques - 1) || 
          (m_bDrawCaustics || !m_pEffect->IsParameterUsed("tCAU", NULL)) && SUCCEEDED(m_pEffect->ValidateTechnique(NULL)))
        {
            m_iTechnique = iTechnique;

            char szText[256];
            sprintf(szText, "Water - Technique %d", m_iTechnique);
            SetWindowText(m_hWnd, szText);

            return S_OK;
        }
    }

    m_pEffect->SetTechnique(m_pEffect->GetTechnique( m_iTechnique ));
    return E_FAIL;
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    HRESULT hr;

    // Initialize Water
    if(FAILED(hr = m_Water.Initialize(64.0f, WATER_DEPTH)))
        return hr;

    // Initialize Environment
    if(FAILED(hr = m_Environment.Initialize(1000.0f)))
        return hr;

    // Misc stuff
    D3DXMatrixRotationX(&m_matPosition, D3DX_PI * -0.3f);
    m_matPosition._42 = 15.0f;
    m_matPosition._43 = 15.0f;

    D3DXMatrixInverse(&m_matView, NULL, &m_matPosition);
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;
    TCHAR sz[512];

    m_bDrawWater        = TRUE;
    m_bDrawCaustics     = TRUE;
    m_bDrawEnvironment  = TRUE;

    // Initialize the font's internal textures
    m_pFont->InitDeviceObjects( m_pd3dDevice );
    m_pFontSmall->InitDeviceObjects( m_pd3dDevice );

    // Floor
    if( FAILED( hr = DXUtil_FindMediaFileCb( sz, sizeof(sz), _T("Water.bmp") ) ) )
        return hr;
    D3DXCreateTextureFromFileEx(m_pd3dDevice, sz, D3DX_DEFAULT, D3DX_DEFAULT, 
        D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
        D3DX_DEFAULT, 0, NULL, NULL, &m_pFloorTex);

    // Sky
    TCHAR* szSkyTex[6] =
    {
        _T("lobbyxpos.jpg"), _T("lobbyxneg.jpg"),
        _T("lobbyypos.jpg"), _T("lobbyyneg.jpg"),
        _T("lobbyzpos.jpg"), _T("lobbyzneg.jpg")
    };

    for(UINT i = 0; i < 6; i++)
    {
        if( FAILED( hr = DXUtil_FindMediaFileCb(sz, sizeof(sz), szSkyTex[i]) ) )
            return hr;
        D3DXCreateTextureFromFileEx(m_pd3dDevice, sz, D3DX_DEFAULT, D3DX_DEFAULT, 
            1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 
            0, NULL, NULL, &m_pSkyTex[i]);
    }

    if( m_d3dCaps.TextureCaps & D3DPTEXTURECAPS_CUBEMAP )
    {
        if( FAILED( hr = DXUtil_FindMediaFileCb(sz, sizeof(sz), TEXT("LobbyCube.dds") ) ) )
            return hr;
        if( FAILED( hr = D3DXCreateCubeTextureFromFile( m_pd3dDevice, sz, &m_pSkyCubeTex ) ) )
            return hr;
    }

    // OnCreateDevice
    if(FAILED(hr = m_Water.OnCreateDevice(m_pd3dDevice)))
        return hr;

    if(FAILED(hr = m_Environment.OnCreateDevice(m_pd3dDevice)))
        return hr;

    // Effect
    DXUtil_FindMediaFileCb(sz, sizeof(sz), _T("water.fx"));

    if(FAILED(hr = D3DXCreateEffectFromFile(m_pd3dDevice, sz, NULL, NULL, 0, NULL, &m_pEffect, NULL)))
        return hr;

    return S_OK;
}



    
//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    HRESULT hr;

    // Restore the font
    m_pFont->RestoreDeviceObjects();
    m_pFontSmall->RestoreDeviceObjects();

    // Create light
    D3DLIGHT9 light;
    ZeroMemory(&light, sizeof(light));

    light.Type        = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r   = m_colorLight.r;
    light.Diffuse.g   = m_colorLight.g;
    light.Diffuse.b   = m_colorLight.b;
    light.Diffuse.a   = m_colorLight.a;
    light.Specular.r  = 1.0f;
    light.Specular.g  = 1.0f;
    light.Specular.b  = 1.0f;
    light.Specular.a  = 0.0f;
    light.Direction.x = m_vecLight.x;
    light.Direction.y = m_vecLight.y;
    light.Direction.z = m_vecLight.z;

    m_pd3dDevice->SetLight(0, &light);
    m_pd3dDevice->LightEnable(0, TRUE);

    // Create material
    D3DMATERIAL9 material;
    ZeroMemory(&material, sizeof(material));

    material.Diffuse.a  = 1.0f;
    material.Specular.r = 0.5f;
    material.Specular.g = 0.5f;
    material.Specular.b = 0.5f;
    material.Power      = 20.0f;

    m_pd3dDevice->SetMaterial(&material);

    // Setup render states
    m_pd3dDevice->SetFVF(D3DFVF_XYZ);

    m_pd3dDevice->SetTransform(D3DTS_VIEW,  &m_matView);
    m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_matIdentity);

    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING,       FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);

    m_pd3dDevice->SetRenderState(D3DRS_ZFUNC,     D3DCMP_LESSEQUAL);
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE,  D3DCULL_CW);
    m_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_DISABLE);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

    m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP,   D3DTOP_DISABLE);
    m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
    m_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE);
    m_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    m_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
    m_pd3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pd3dDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
    m_pd3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

    // Create caustic texture
    D3DDISPLAYMODE mode;
    m_pd3dDevice->GetDisplayMode( 0, &mode );

    if(FAILED(hr = D3DXCreateTexture(m_pd3dDevice, WATER_CAUSTICS_SIZE, WATER_CAUSTICS_SIZE, 1, D3DUSAGE_RENDERTARGET, mode.Format, D3DPOOL_DEFAULT, &m_pCausticTex)) &&
       FAILED(hr = D3DXCreateTexture(m_pd3dDevice, WATER_CAUSTICS_SIZE, WATER_CAUSTICS_SIZE, 1, 0, mode.Format, D3DPOOL_DEFAULT, &m_pCausticTex)))
    {
        return hr;
    }

    D3DSURFACE_DESC desc;
    m_pCausticTex->GetSurfaceLevel(0, &m_pCausticSurf);
    m_pCausticSurf->GetDesc(&desc);

    if(FAILED(hr = D3DXCreateRenderToSurface(m_pd3dDevice, desc.Width, desc.Height, 
        desc.Format, FALSE, D3DFMT_UNKNOWN, &m_pRenderToSurface)))
    {
        return hr;
    }

    // Effect
    m_pEffect->OnResetDevice();

    m_pEffect->SetMatrix("mID",  &m_matIdentity);
    m_pEffect->SetMatrix("mENV", &m_matIdentity);

    m_pEffect->SetTexture("tFLR", m_pFloorTex);
    m_pEffect->SetTexture("tCAU", m_pCausticTex);
    m_pEffect->SetTexture("tENV", m_pSkyCubeTex);

    if(FAILED(hr = GetNextTechnique(0, FALSE)))
        return hr;

    // Set surfaces
    if(FAILED(hr = m_Environment.SetSurfaces(
        m_pSkyTex[D3DCUBEMAP_FACE_NEGATIVE_X], m_pSkyTex[D3DCUBEMAP_FACE_POSITIVE_X], 
        m_pSkyTex[D3DCUBEMAP_FACE_NEGATIVE_Y], m_pSkyTex[D3DCUBEMAP_FACE_POSITIVE_Y],
        m_pSkyTex[D3DCUBEMAP_FACE_POSITIVE_Z], m_pSkyTex[D3DCUBEMAP_FACE_NEGATIVE_Z])))
    {
        return hr;
    }

    if(FAILED(hr = m_Water.OnResetDevice()))
        return hr;

    if(FAILED(hr = m_Environment.OnResetDevice()))
        return hr;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();
    m_pFontSmall->InvalidateDeviceObjects();

    m_Water.OnLostDevice();
    m_Environment.OnLostDevice();
    m_pEffect->OnLostDevice();

    SAFE_RELEASE(m_pRenderToSurface);
    SAFE_RELEASE(m_pCausticSurf);
    SAFE_RELEASE(m_pCausticTex);

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::DeleteDeviceObjects()
{
    m_pFont->DeleteDeviceObjects();
    m_pFontSmall->DeleteDeviceObjects();

    m_Water.OnDestroyDevice();
    m_Environment.OnDestroyDevice();

    SAFE_RELEASE(m_pFloorTex);
    SAFE_RELEASE(m_pSkyCubeTex);
    SAFE_RELEASE(m_pEffect);

    for(UINT i = 0; i < 6; i++)
        SAFE_RELEASE(m_pSkyTex[i]);

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    HRESULT hr;

    //
    // Process keyboard input
    //

    D3DXVECTOR3 vecT(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vecR(0.0f, 0.0f, 0.0f);

    if(m_bKey[VK_NUMPAD1] || m_bKey[VK_LEFT])  vecT.x -= 1.0f; // Slide Left
    if(m_bKey[VK_NUMPAD3] || m_bKey[VK_RIGHT]) vecT.x += 1.0f; // Slide Right
    if(m_bKey[VK_DOWN])                        vecT.y -= 1.0f; // Slide Down
    if(m_bKey[VK_UP])                          vecT.y += 1.0f; // Slide Up
    if(m_bKey['W'])                            vecT.z -= 2.0f; // Move Forward
    if(m_bKey['S'])                            vecT.z += 2.0f; // Move Backward
    if(m_bKey['A'] || m_bKey[VK_NUMPAD8])      vecR.x -= 1.0f; // Pitch Down
    if(m_bKey['Z'] || m_bKey[VK_NUMPAD2])      vecR.x += 1.0f; // Pitch Up
    if(m_bKey['E'] || m_bKey[VK_NUMPAD6])      vecR.y -= 1.0f; // Turn Right
    if(m_bKey['Q'] || m_bKey[VK_NUMPAD4])      vecR.y += 1.0f; // Turn Left
    if(m_bKey[VK_NUMPAD9])                     vecR.z -= 2.0f; // Roll CW
    if(m_bKey[VK_NUMPAD7])                     vecR.z += 2.0f; // Roll CCW

    m_vecVelocity = m_vecVelocity * 0.9f + vecT * 0.1f;
    m_vecAngularVelocity = m_vecAngularVelocity * 0.9f + vecR * 0.1f;

    //
    // Update position and view matricies
    //

    D3DXMATRIXA16 matT, matR;
    D3DXQUATERNION qR;

    vecT = m_vecVelocity * m_fElapsedTime * m_fSpeed;
    vecR = m_vecAngularVelocity * m_fElapsedTime * m_fAngularSpeed;

    D3DXMatrixTranslation(&matT, vecT.x, vecT.y, vecT.z);
    D3DXMatrixMultiply(&m_matPosition, &matT, &m_matPosition);

    D3DXQuaternionRotationYawPitchRoll(&qR, vecR.y, vecR.x, vecR.z);
    D3DXMatrixRotationQuaternion(&matR, &qR);

    D3DXMatrixMultiply(&m_matPosition, &matR, &m_matPosition);
    D3DXMatrixInverse(&m_matView, NULL, &m_matPosition);

    //
    // Update simulation
    //

    if(!m_bPause && m_bDrawWater)
    {
        BOOL bCaustics = m_bDrawCaustics && m_pEffect->IsParameterUsed("tCAU", NULL);
        D3DXVECTOR3 vecPos(m_matPosition._41, m_matPosition._42, m_matPosition._43);
        D3DXVECTOR3 vecLight(0.0f, 1.0f, 0.0f);

        m_Water.Update(vecPos, vecLight, bCaustics);
        m_fTime += m_fSecsPerFrame;

        if(bCaustics)
        {
            if(SUCCEEDED(m_pRenderToSurface->BeginScene(m_pCausticSurf, NULL)))
            {
                D3DXMATRIXA16 matProj;
                D3DXMATRIXA16 matView;

                D3DXMatrixOrthoRH(&matProj, 63.0f, 63.0f, 1.0f, 100.0f);
                D3DXMatrixRotationX(&matView, 0.5f * D3DX_PI);
                matView._43 = -50.0f;

                m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
                m_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

                m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0xff000000, 0.0f, 0);

                m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
                m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
                m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

                m_Water.DrawCaustics();

                m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
                m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

                m_pRenderToSurface->EndScene( 0 );
            }
            else
            {
                m_bDrawCaustics = FALSE;
                m_pEffect->SetTexture("tCAU", NULL);

                if(FAILED(hr = GetNextTechnique(0, FALSE)))
                    return hr;
            }
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{   
    HRESULT hr;

    if(FAILED(hr = m_pd3dDevice->BeginScene()))
        return hr;

    // Draw Environment
    FLOAT fAspectRatio = (FLOAT)m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovRH(&m_matProjection, D3DXToRadian(60.0f), fAspectRatio, 0.1f, 2000.0f);
    m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_matProjection);    

    if(m_bDrawEnvironment)
    {
        D3DXMATRIXA16 mat(m_matView);
        mat._41 = mat._42 = mat._43 = 0.0f;
        m_pd3dDevice->SetTransform(D3DTS_VIEW, &mat);

        m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
        m_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

        m_Environment.Draw();

        m_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
        m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
    }
    else
    {
        m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
    }

    m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);

    // Draw water
    if(m_bDrawWater)
    {
        // Setup matrices
        if(m_pEffect->IsParameterUsed("mENV", NULL))
        {
            D3DXMATRIXA16 matP(m_matPosition);
            matP._41 = matP._42 = matP._43 = 0.0f;

            D3DXMATRIXA16 mat;
            D3DXMatrixScaling(&mat, 1.0f, 1.0f, -1.0f);

            D3DXMatrixMultiply(&mat, &matP, &mat);

            // matCube
            m_pEffect->SetMatrix("mENV", &mat);
        }

        // Draw water
        UINT uPasses;
        m_pEffect->Begin(&uPasses, 0);

        for(UINT uPass = 0; uPass < uPasses; uPass++)
        {
            m_pEffect->Pass(uPass);
            m_Water.DrawSurface();
        }

        m_pEffect->End();
    }

    // Show info
    m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
    m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );

    TCHAR szText[100];
    wsprintf( szText, _T("Using Technique %d"), m_iTechnique );
    m_pFontSmall->DrawText( 2, 40, D3DCOLOR_ARGB(255,255,100,100), szText );
    
    if( m_bShowHelp )
    {
        m_pFontSmall->DrawText(  2, 60, D3DCOLOR_ARGB(255,100,100,200),
                                _T("Keyboard controls:") );
        m_pFontSmall->DrawText( 20, 80, D3DCOLOR_ARGB(255,100,100,200),
                                _T("Add Drop\n")
                                _T("Next Technique\n")
                                _T("Next Tech. (no validate)\n")
                                _T("Prev Technique\n")
                                _T("Prev Tech. (no validate)\n")
                                _T("Move\nTurn\nPitch\nSlide\n")
                                _T("Help\nChange device\nExit") );
        m_pFontSmall->DrawText( 210, 80, D3DCOLOR_ARGB(255,100,100,200),
                                _T("D\n")
                                _T("PageDn\nShift-PageDn\n")
                                _T("PageUp\nShift-PageUp\n")
                                _T("W,S\nE,Q\nA,Z\nArrow keys\n")
                                _T("F1\nF2\nEsc") );
    }
    else
    {
        m_pFontSmall->DrawText(  2, 60, D3DCOLOR_ARGB(255,100,100,200), 
                           _T("Press F1 for help") );
    }


    if(FAILED(hr = m_pd3dDevice->EndScene()))
        return hr;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FinalCleanup()
{
    SAFE_DELETE( m_pFont );
    SAFE_DELETE( m_pFontSmall );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc
// Desc:
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, 
                                    LPARAM lParam )
{
    switch( uMsg )
    {
        case WM_KEYDOWN:
            m_bKey[wParam] = TRUE;
            break;

        case WM_KEYUP:
            m_bKey[wParam] = FALSE;
            break;

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
            case IDM_ADDDROP:
                m_Water.Drop();
                break;

            case IDM_NEXT_TECHNIQUE:
                GetNextTechnique(1, FALSE);
                break;

            case IDM_NEXT_TECHNIQUE_NOVALIDATE:
                GetNextTechnique(1, TRUE);
                break;

            case IDM_PREV_TECHNIQUE:
                GetNextTechnique(-1, FALSE);
                break;

            case IDM_PREV_TECHNIQUE_NOVALIDATE:
                GetNextTechnique(-1, TRUE);
                break;

            case IDM_TOGGLEHELP:
                m_bShowHelp = !m_bShowHelp;
                break;
            }
        }
    }

    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}


//////////////////////////////////////////////////////////////////////////////
// Types /////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#pragma pack(4)
struct ENV_VERTEX
{
    D3DXVECTOR3 m_vecPos;
    D3DXVECTOR2 m_vecTex;

    static const DWORD FVF;
};

const DWORD ENV_VERTEX::FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0);




//////////////////////////////////////////////////////////////////////////////
// CEnvironment implementation ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

CEnvironment::CEnvironment()
{
    m_fSize = 1.0f;
    m_pDevice = NULL;

    memset(m_pSurf, 0x00, sizeof(m_pSurf));
}


CEnvironment::~CEnvironment()
{
}


HRESULT CEnvironment::Initialize(float fSize)
{
    m_fSize = fSize;
    return S_OK;
}


HRESULT CEnvironment::OnCreateDevice(IDirect3DDevice9* pDevice)
{
    m_pDevice = pDevice;
    return S_OK;
}


HRESULT CEnvironment::OnResetDevice()
{
    return S_OK;
}


HRESULT CEnvironment::OnLostDevice()
{
    return S_OK;
}


HRESULT CEnvironment::OnDestroyDevice()
{
    return S_OK;
}


HRESULT CEnvironment::SetSurfaces(
    IDirect3DTexture9* pXNeg, IDirect3DTexture9* pXPos, 
    IDirect3DTexture9* pYNeg, IDirect3DTexture9* pYPos,
    IDirect3DTexture9* pZNeg, IDirect3DTexture9* pZPos)
{
    m_pSurf[0] = pXNeg;
    m_pSurf[1] = pXPos;
    m_pSurf[2] = pYNeg;
    m_pSurf[3] = pYPos;
    m_pSurf[4] = pZNeg;
    m_pSurf[5] = pZPos;

    return S_OK;
}


HRESULT CEnvironment::Draw()
{
    float f;
    ENV_VERTEX vert[4];

    f = 0.5f / 512.0f;

    vert[0].m_vecTex = D3DXVECTOR2(0.0f + f, 0.0f + f);
    vert[1].m_vecTex = D3DXVECTOR2(0.0f + f, 1.0f - f);
    vert[2].m_vecTex = D3DXVECTOR2(1.0f - f, 0.0f + f);
    vert[3].m_vecTex = D3DXVECTOR2(1.0f - f, 1.0f - f);

    m_pDevice->SetFVF(ENV_VERTEX::FVF);
    f = m_fSize * 0.5f;

    // XNeg
    vert[0].m_vecPos = D3DXVECTOR3(-f,  f,  f);
    vert[1].m_vecPos = D3DXVECTOR3(-f, -f,  f);
    vert[2].m_vecPos = D3DXVECTOR3(-f,  f, -f);
    vert[3].m_vecPos = D3DXVECTOR3(-f, -f, -f);

    m_pDevice->SetTexture(0, m_pSurf[0]);
    m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID) vert, sizeof(ENV_VERTEX));

    // XPos
    vert[0].m_vecPos = D3DXVECTOR3( f,  f, -f);
    vert[1].m_vecPos = D3DXVECTOR3( f, -f, -f);
    vert[2].m_vecPos = D3DXVECTOR3( f,  f,  f);
    vert[3].m_vecPos = D3DXVECTOR3( f, -f,  f);

    m_pDevice->SetTexture(0, m_pSurf[1]);
    m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID) vert, sizeof(ENV_VERTEX));

    // YNeg
    vert[0].m_vecPos = D3DXVECTOR3(-f, -f, -f);
    vert[1].m_vecPos = D3DXVECTOR3(-f, -f,  f);
    vert[2].m_vecPos = D3DXVECTOR3( f, -f, -f);
    vert[3].m_vecPos = D3DXVECTOR3( f, -f,  f);

    m_pDevice->SetTexture(0, m_pSurf[2]);
    m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID) vert, sizeof(ENV_VERTEX));
    
    // YPos
    vert[0].m_vecPos = D3DXVECTOR3(-f,  f,  f);
    vert[1].m_vecPos = D3DXVECTOR3(-f,  f, -f);
    vert[2].m_vecPos = D3DXVECTOR3( f,  f,  f);
    vert[3].m_vecPos = D3DXVECTOR3( f,  f, -f);

    m_pDevice->SetTexture(0, m_pSurf[3]);
    m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID) vert, sizeof(ENV_VERTEX));

    // ZNeg
    vert[0].m_vecPos = D3DXVECTOR3(-f,  f, -f);
    vert[1].m_vecPos = D3DXVECTOR3(-f, -f, -f);
    vert[2].m_vecPos = D3DXVECTOR3( f,  f, -f);
    vert[3].m_vecPos = D3DXVECTOR3( f, -f, -f);

    m_pDevice->SetTexture(0, m_pSurf[4]);
    m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID) vert, sizeof(ENV_VERTEX));

    // ZPos
    vert[0].m_vecPos = D3DXVECTOR3( f,  f,  f);
    vert[1].m_vecPos = D3DXVECTOR3( f, -f,  f);
    vert[2].m_vecPos = D3DXVECTOR3(-f,  f,  f);
    vert[3].m_vecPos = D3DXVECTOR3(-f, -f,  f);

    m_pDevice->SetTexture(0, m_pSurf[5]);
    m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID) vert, sizeof(ENV_VERTEX));

    return S_OK;
}


#define WATER_SHIFT 6
#define WATER_SIZE  (1 << WATER_SHIFT)
#define WATER_AREA  (WATER_SIZE * WATER_SIZE)
#define WATER_MASK  (WATER_SIZE - 1)

#define WATER_SPHERE_HEIGHT   20.0f
#define WATER_SPHERE_RADIUS2  (35.0f * 35.0f)

#define WATER_INDEX(x, y) \
    ((x) | ((y) << WATER_SHIFT))

#define WATER_INDEX_WRAP(x, y) \
    (((x) & WATER_MASK) | (((y) & WATER_MASK) << WATER_SHIFT))


#if defined(_X86) && !defined(_WIN64)
inline int f2i(float flt) 
{
	volatile int n; 

	__asm 
	{
		fld flt
		fistp n
	}

	return n;
}
#else
inline int f2i(float flt) 
{
	return (int) flt;
}
#endif



//////////////////////////////////////////////////////////////////////////////
// Types /////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct WATER_VERTEX
{
    D3DXVECTOR3 m_vecPos;
    D3DXVECTOR3 m_vecNormal;
    D3DCOLOR    m_dwDiffuse;
    D3DXVECTOR2 m_vecTex;

    static const DWORD FVF;

};
const DWORD WATER_VERTEX::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE 
        | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0);


struct CAUSTICS_VERTEX
{
    D3DXVECTOR3 m_vecPos;
    D3DCOLOR    m_dwDiffuse;

    static const DWORD FVF;

};
const DWORD CAUSTICS_VERTEX::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

#pragma pack()


//////////////////////////////////////////////////////////////////////////////
// CWater implementation /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

CWater::CWater()
{
    m_fDepth    = 0.0f;
    m_fScaleTex = 1.0f;

    m_uIndices  = 0;
    m_uVertices = 0;

    m_pRefract     = NULL;
    m_pSurface     = NULL;

    m_pDevice      = NULL;
    m_pibIndices   = NULL;
    m_pvbVertices  = NULL;
    m_pvbCaustics  = NULL;
}


CWater::~CWater()
{
    if(m_pSurface)
        delete [] m_pSurface;
}


HRESULT CWater::Initialize(float fSize, float fDepth)
{
    m_fSize = fSize;
    m_fDepth = fDepth;
    m_fScaleTex = 1.0f / fSize;

    // Calculate number of vertices and indices
    m_uVertices = WATER_AREA;
    m_uIndices  = m_uVertices * 2;

    // Create refraction table
    static WATER_REFRACT Refract[512];

    if(!m_pRefract)
    {
        m_pRefract = &Refract[256];

        for(UINT u = 0; u < 256; u++)
        {        
            float fCos0 = (float) u / (float) 256.0f;
            float f0 = acosf(fCos0);
            float fSin0 = sinf(f0);

            float fSin1 = fSin0 / 1.333f; // water
            float f1 = asinf(fSin1);
            float fCos1 = cosf(f1);
        
            m_pRefract[u].fRefract = fSin0 / fSin1 * fCos1 - fCos0;
            m_pRefract[u].fRefractNorm = - fSin1 / fSin0;
            m_pRefract[u].dwDiffuse = ((((0xff - u)*(0xff - u)*(0xff - u)) << 8) & 0xff000000);

            Refract[u] = Refract[256];
        }
    }

    // Create maps
    if(!m_pSurface)
    {
        if( ( m_pSurface = new WATER_SURFACE[WATER_AREA] ) == NULL )
            return E_OUTOFMEMORY;

        memset(m_pSurface, 0x00, WATER_AREA * sizeof(WATER_SURFACE));
    }

    return S_OK;
}




HRESULT CWater::OnCreateDevice(IDirect3DDevice9 *pDevice)
{
    m_pDevice = pDevice;
    return S_OK;
}




HRESULT CWater::OnResetDevice()
{
    HRESULT hr;

    // Create indices
    if(!m_pibIndices)
    {
        WORD *pwIndices;

        if(FAILED(hr = m_pDevice->CreateIndexBuffer(m_uIndices * sizeof(WORD), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 
            D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pibIndices, NULL)))
        {
            return hr;
        }

        if(FAILED(hr = m_pibIndices->Lock(0, m_uIndices * sizeof(WORD), (void**) &pwIndices, D3DLOCK_DISCARD)))
            return hr;

        // Fill in indicies
        UINT uX = 0, uZ = 0;
        WORD *pwIndex = pwIndices;

        for(UINT uSize = WATER_SIZE; uSize != 0; uSize -= 2)
        {
            UINT u;

            // Top
            for(u = 0; u < uSize; u++)
            {
                *pwIndex++ = uX + uZ * WATER_SIZE;
                *pwIndex++ = uX + uZ * WATER_SIZE + WATER_SIZE;
                uX++;
            }

            uX--;
            uZ++;

            // Right
            for(u = 1; u < uSize; u++)
            {
                *pwIndex++ = uX + uZ * WATER_SIZE;
                *pwIndex++ = uX + uZ * WATER_SIZE - 1;
                uZ++;
            }

            uZ--;
            uX--;

            // Bottom
            for(u = 1; u < uSize; u++)
            {
                *pwIndex++ = uX + uZ * WATER_SIZE;
                *pwIndex++ = uX + uZ * WATER_SIZE - WATER_SIZE;
                uX--;
            }

            uX++;
            uZ--;

            // Left
            for(u = 2; u < uSize; u++)
            {
                *pwIndex++ = uX + uZ * WATER_SIZE;
                *pwIndex++ = uX + uZ * WATER_SIZE + 1;
                uZ--;
            }

            uZ++;
            uX++;
        }

        for(pwIndex = pwIndices; pwIndex < pwIndices + m_uIndices; pwIndex++)
        {
            if(*pwIndex >= m_uVertices)
                *pwIndex = 0;
        }

        m_pibIndices->Unlock();
    }
    
    // Create vertices
    if(!m_pvbVertices)
    {
        if(FAILED(hr = m_pDevice->CreateVertexBuffer(m_uVertices * sizeof(WATER_VERTEX), 
            D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, WATER_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pvbVertices, NULL)))
        {
            return hr;
        }
    }

    // Create caustics
    if(!m_pvbCaustics)
    {
        if(FAILED(hr = m_pDevice->CreateVertexBuffer(m_uVertices * sizeof(CAUSTICS_VERTEX), 
            D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, CAUSTICS_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pvbCaustics, NULL)))
        {
            return hr;
        }
    }

    return S_OK;
}




HRESULT CWater::OnLostDevice()
{
    SAFE_RELEASE( m_pibIndices );
    SAFE_RELEASE( m_pvbVertices );
    SAFE_RELEASE( m_pvbCaustics );
    return S_OK;
}




HRESULT CWater::OnDestroyDevice()
{
    m_pDevice = NULL;
    return S_OK;
}




HRESULT CWater::Drop()
{
    UINT uX = rand();
    UINT uY = rand();

    m_pSurface[WATER_INDEX_WRAP(uX, uY)].fVelocity -= 0.25f;

    m_pSurface[WATER_INDEX_WRAP(uX - 1, uY)].fVelocity -= 0.125f;
    m_pSurface[WATER_INDEX_WRAP(uX + 1, uY)].fVelocity -= 0.125f;
    m_pSurface[WATER_INDEX_WRAP(uX, uY - 1)].fVelocity -= 0.125f;
    m_pSurface[WATER_INDEX_WRAP(uX, uY + 1)].fVelocity -= 0.125f;

    m_pSurface[WATER_INDEX_WRAP(uX - 1, uY - 1)].fVelocity -= 0.0625f;
    m_pSurface[WATER_INDEX_WRAP(uX + 1, uY + 1)].fVelocity -= 0.0625f;
    m_pSurface[WATER_INDEX_WRAP(uX + 1, uY - 1)].fVelocity -= 0.0625f;
    m_pSurface[WATER_INDEX_WRAP(uX - 1, uY + 1)].fVelocity -= 0.0625f;

    return S_OK;
}




HRESULT CWater::Update(D3DXVECTOR3 &vecPos, D3DXVECTOR3 &vecLight, BOOL bCalcCaustics)
{
    HRESULT hr;
    UINT uXN, uX, uXP, uY, uYN, uY0, uYP;

    // Compute desired height
    m_fAvgHeight = 0.0f;
    WATER_SURFACE *pSurface = m_pSurface;

    uYN  = WATER_AREA - WATER_SIZE;
    uY0  = 0;
    uYP  = WATER_SIZE;

    do
    {
        uXN  = WATER_SIZE - 1;
        uX   = 0;
        uXP  = 1;

        do
        {
            // Bowl
            float fX = (float) uX - (WATER_SIZE >> 1);
            float fZ = (float) (uY0 >> WATER_SHIFT) - (WATER_SIZE >> 1);
            float fDesire;

            if((fX * fX + fZ * fZ) < (WATER_SPHERE_RADIUS2 -  WATER_SPHERE_HEIGHT * WATER_SPHERE_HEIGHT))
            {
                fDesire = 
                     (m_pSurface[uXN + uYN].fHeight + 
                      m_pSurface[uXP + uYN].fHeight + 
                      m_pSurface[uXN + uYP].fHeight + 
                      m_pSurface[uXP + uYP].fHeight) * (1.0f / 12.0f)
                      +
                     (m_pSurface[uX  + uYN].fHeight +
                      m_pSurface[uXN + uY0].fHeight +
                      m_pSurface[uXP + uY0].fHeight +
                      m_pSurface[uX  + uYP].fHeight) * (2.0f / 12.0f);
            }
            else
            {
                fDesire = 0.0f;
                pSurface->fHeight = 0.0f;
                pSurface->fVelocity = 0.0f;
            }

            // Update velocity
            if(pSurface->fVelocity > 0.01f || pSurface->fVelocity  < -0.01f)
                pSurface->fVelocity *= 0.99f;

            pSurface->fVelocity += 0.25f * (fDesire - pSurface->fHeight);
            m_fAvgHeight += pSurface->fHeight + pSurface->fVelocity;

            pSurface++;

            uXN = uX;
            uX  = uXP;
            uXP = (uXP + 1) & WATER_MASK;
        }
        while(uX);

        uYN = uY0;
        uY0 = uYP;
        uYP = (uYP + WATER_SIZE) & (WATER_MASK << WATER_SHIFT);
    }
    while(uY0);

    m_fAvgHeight /= (float) m_uVertices;

    // Calculate surface normals
    WATER_VERTEX *pVertices, *pVertex, *pVertexLim;

    D3DXVECTOR3 vec;
    D3DXVECTOR3 vecP, vecN;

    if(FAILED(hr = m_pvbVertices->Lock(0, m_uVertices * sizeof(WATER_VERTEX), (void**) &pVertices, D3DLOCK_DISCARD)))
        return hr;
    
    pVertex = pVertices;
    pVertexLim = pVertex + m_uVertices;
    pSurface = m_pSurface;

    float fInc = m_fSize / (float) (WATER_SIZE - 1);
    float fZ = m_fSize * -0.5f;

    uYN  = WATER_AREA - WATER_SIZE;
    uY0  = 0;
    uYP  = WATER_SIZE;

    do
    {
        float fX = m_fSize * -0.5f;

        uXN  = WATER_SIZE - 1;
        uX   = 0;
        uXP  = 1;

        do
        {
            // Update position and normal
            vecP.x = fX;
            vecP.y = pSurface->fHeight = pSurface->fHeight + pSurface->fVelocity - m_fAvgHeight;
            vecP.z = fZ;

            float f;
            f = m_pSurface[uXN + uYN].fHeight - m_pSurface[uXP + uYP].fHeight; vecN.x = vecN.z = f;           
            f = m_pSurface[uX  + uYN].fHeight - m_pSurface[uX  + uYP].fHeight; vecN.z += f;
            f = m_pSurface[uXP + uYN].fHeight - m_pSurface[uXN + uYP].fHeight; vecN.x -= f; vecN.z += f;
            f = m_pSurface[uXN + uY0].fHeight - m_pSurface[uXP + uY0].fHeight; vecN.x += f;

            vecN.y = 1.0f;
            D3DXVec3Normalize(&vecN, &vecN);

            pSurface++;

            // Update texture coords and diffuse based upon refraction
            D3DXVec3Subtract(&vec, &vecPos, &vecP);
            D3DXVec3Normalize(&vec, &vec);

            WATER_REFRACT *pRefract;
            pRefract = m_pRefract + f2i(D3DXVec3Dot(&vec, &vecN) * 255.0f);

            pVertex->m_vecPos = vecP;
            pVertex->m_vecNormal = vecN;
            pVertex->m_dwDiffuse = pRefract->dwDiffuse;

            // Bowl
            D3DXVECTOR3 vecD;
            vecD = (vecN * pRefract->fRefract + vec) * pRefract->fRefractNorm;
            vecP.y -= WATER_SPHERE_HEIGHT;

            float fC = D3DXVec3Dot(&vecP, &vecP) - WATER_SPHERE_RADIUS2;

            if(fC < 0.0f)
            {
                float fB = D3DXVec3Dot(&vecD, &vecP) * 2.0f;
                float fD = fB * fB - 4.0f * fC;
                float fScale = (-fB + sqrtf(fD)) * 0.5f;

                pVertex->m_vecTex.x = (vecD.x * fScale + vecP.x) * m_fScaleTex + 0.5f;
                pVertex->m_vecTex.y = (vecD.z * fScale + vecP.z) * m_fScaleTex + 0.5f;
            }
            else
            {
                pVertex->m_vecTex.x = vecP.x * m_fScaleTex + 0.5f;
                pVertex->m_vecTex.y = vecP.z * m_fScaleTex + 0.5f;
            }

            pVertex++;
            fX += fInc;

            uXN = uX;
            uX  = uXP;
            uXP = (uXP + 1) & WATER_MASK;
        }
        while(uX);

        fZ += fInc;

        uYN = uY0;
        uY0 = uYP;
        uYP = (uYP + WATER_SIZE) & (WATER_MASK << WATER_SHIFT);
    }
    while(uY0);

    // Calculate caustics
    if(bCalcCaustics)
    {
        CAUSTICS_VERTEX *pCaustics, *pCaustic;

        if(FAILED(hr = m_pvbCaustics->Lock(0, m_uVertices * sizeof(CAUSTICS_VERTEX), (void**) &pCaustics, D3DLOCK_DISCARD)))
            return hr;

        #define TABLE_SIZE 8
        static DWORD Table[TABLE_SIZE];
        if(!Table[0])
        {
            for(UINT u = 0; u < TABLE_SIZE; u++)
                Table[u] = (0x40 / (u + 1)) * 0x00010101;
        }

        pVertex = pVertices;
        pCaustic = pCaustics;

        for(uY = 0; uY < WATER_SIZE; uY++)
        {
            for(uX = 0; uX < WATER_SIZE; uX++)
            {
                WATER_REFRACT *pRefract;
                pRefract = m_pRefract + f2i(pVertex->m_vecNormal.y * 255.0f);

                // Bowl
                D3DXVECTOR3 vecD, vecP;
                vecD = (pVertex->m_vecNormal * pRefract->fRefract + vecLight) * pRefract->fRefractNorm;
                vecP = pVertex->m_vecPos;
                vecP.y -= WATER_SPHERE_HEIGHT;

                float fC = D3DXVec3Dot(&vecP, &vecP) - WATER_SPHERE_RADIUS2;

                if(fC < 0.0f)
                {
                    float fB = D3DXVec3Dot(&vecD, &vecP) * 2.0f;
                    float fD = fB * fB - 4.0f * fC;
                    float fScale = (-fB + sqrtf(fD)) * 0.5f;

                    pCaustic->m_vecPos.x = vecD.x * fScale + vecP.x;
                    pCaustic->m_vecPos.y = 0.0f;
                    pCaustic->m_vecPos.z = vecD.z * fScale + vecP.z;
                }
                else
                {
                    pCaustic->m_vecPos.x = vecP.x;
                    pCaustic->m_vecPos.y = 0.0f;
                    pCaustic->m_vecPos.z = vecP.z;
                }

                if(uX && uY)
                {
                    float fArea;
                    fArea = (pCaustic[-WATER_SIZE - 1].m_vecPos.x - pCaustic->m_vecPos.x) *
                            (pCaustic[-WATER_SIZE    ].m_vecPos.z - pCaustic->m_vecPos.z) -
                            (pCaustic[-WATER_SIZE - 1].m_vecPos.z - pCaustic->m_vecPos.z) *
                            (pCaustic[-WATER_SIZE    ].m_vecPos.x - pCaustic->m_vecPos.x);

                    if(fArea < 0.0f)
                        fArea = -fArea;

                    UINT u = f2i(fArea * fArea * 4.0f);
                    pCaustic->m_dwDiffuse = u < TABLE_SIZE ? Table[u] : 0;
                }

                pCaustic++;
                pVertex++;
            }

            pCaustic[-WATER_SIZE].m_dwDiffuse = pCaustic[-1].m_dwDiffuse;
        }

        for(uX = 0; uX < WATER_SIZE; uX++)
        {
            pCaustics[uX].m_dwDiffuse = pCaustics[uX + (WATER_AREA - WATER_SIZE)].m_dwDiffuse;
        }

        m_pvbCaustics->Unlock();
    }

    m_pvbVertices->Unlock();
    return S_OK;
}




HRESULT CWater::DrawCaustics()
{
    HRESULT hr;

    if(FAILED(hr = m_pDevice->SetFVF(CAUSTICS_VERTEX::FVF)))
        return hr;

    if(FAILED(hr = m_pDevice->SetStreamSource(0, m_pvbCaustics, 0, sizeof(CAUSTICS_VERTEX))))
        return hr;

    if(FAILED(hr = m_pDevice->SetIndices(m_pibIndices)))
        return hr;

    if(FAILED(hr = m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_uVertices, 0, m_uIndices - 2)))
        return hr;

    return S_OK;
}




HRESULT CWater::DrawSurface()
{
    HRESULT hr;

    if(FAILED(hr = m_pDevice->SetFVF(WATER_VERTEX::FVF)))
        return hr;

    if(FAILED(hr = m_pDevice->SetStreamSource(0, m_pvbVertices, 0, sizeof(WATER_VERTEX))))
        return hr;

    if(FAILED(hr = m_pDevice->SetIndices(m_pibIndices)))
        return hr;

    if(FAILED(hr = m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_uVertices, 0, m_uIndices - 2)))
        return hr;

    return S_OK;
}
