//-----------------------------------------------------------------------------
// File: DepthOfField.cpp
//
// Desc: Example code showing how to do a depth of field effect.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <D3DX9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFile.h"
#include "D3DFont.h"
#include "D3DUtil.h"
#include "resource.h"


struct VERTEX 
{
    D3DXVECTOR4 pos;
    DWORD       clr;
    D3DXVECTOR2 tex1;
    D3DXVECTOR2 tex2;
    D3DXVECTOR2 tex3;
    D3DXVECTOR2 tex4;
    D3DXVECTOR2 tex5;
    D3DXVECTOR2 tex6;

    static const DWORD FVF;
};
const DWORD VERTEX::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX6;


class CMyD3DApplication : public CD3DApplication
{
private:
    CD3DFont*               m_pFont;              // Font for drawing text
    CD3DFont*               m_pFontSmall;
    float                   m_fAspectRatio;

    VERTEX                  m_Vertex[4];

    PALETTEENTRY            m_Palette[256];
    LPDIRECT3DTEXTURE9      m_pTexture;
    LPD3DXRENDERTOSURFACE   m_pRenderToSurface;
    LPDIRECT3DSURFACE9      m_pTextureSurf;

    LPD3DXMESH              m_pMesh;
    LPDIRECT3DTEXTURE9      m_pEarthTexture;
    LPD3DXEFFECT            m_pEffect;

    D3DXVECTOR4             m_vFocalPlaneDest;
    D3DXVECTOR4             m_vFocalPlaneSrc;
    FLOAT                   m_fChangeTime;
    BOOL                    m_bShowBlurFactor;
    BOOL                    m_bShowUnblurred;
    BOOL                    m_bDrawToRenderTarget;
    BOOL                    m_bDrawHelp;
    DWORD                   m_dwBackgroundColor;

    D3DVIEWPORT9            m_ViewportFB;
    D3DVIEWPORT9            m_ViewportOffscreen;

    FLOAT                   m_fBlurConst;

    static LPCSTR           m_TechniqueNames[];
    static const DWORD      m_TechniqueCount;
    DWORD                   m_TechniqueIndex;

protected:
    HRESULT InitDeviceObjects();
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT FinalCleanup();
    HRESULT Render();
    HRESULT FrameMove();
    HRESULT ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior, 
        D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat );

    void SetupQuad();
    void UpdateTechniqueSpecificVariables();

public:
    CMyD3DApplication();
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};



//-----------------------------------------------------------------------------
// Technique list
//-----------------------------------------------------------------------------
LPCSTR  CMyD3DApplication::m_TechniqueNames[]      = {"UsePS11NoRings",
                                                     "UsePS11NoRingsAsm",
                                                     "UsePS11WithRings",
                                                     "UsePS11WithRingsAsm",
                                                     "UsePS14NoRingsAsm",
                                                     "UsePS20SixTexcoords",
                                                     "UsePS20SevenLookups",
                                                     "UsePS20ThirteenLookups"};

const DWORD CMyD3DApplication::m_TechniqueCount = sizeof(m_TechniqueNames)/sizeof(LPCSTR);


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
    {
        return 0;
    }

    return d3dApp.Run();
}




//-----------------------------------------------------------------------------
// Name: CMyD3DApplication()
// Desc: Application constructor. Sets attributes for the app.
//-----------------------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
{
    m_strWindowTitle = _T("Depth of Field");
    m_d3dEnumeration.AppUsesDepthBuffer = TRUE;
    m_pFont = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pFontSmall        = new CD3DFont( _T("Arial"),  9, D3DFONT_BOLD );
    m_fAspectRatio = 0.0f;

    m_pTexture = NULL;
    m_pTextureSurf = NULL;
    m_pRenderToSurface = NULL;
    m_pEffect = NULL;

    m_vFocalPlaneDest = D3DXVECTOR4(0.0f, 0.0f, 1.0f, -0.5f);
    m_vFocalPlaneSrc = m_vFocalPlaneDest;
    m_fChangeTime = 0.0f;

    m_pMesh = NULL;
    m_pEarthTexture = NULL;
    m_bShowBlurFactor = FALSE;
    m_bShowUnblurred = FALSE;
    m_bDrawToRenderTarget = TRUE;
    m_bDrawHelp = FALSE;
    m_dwBackgroundColor = 0xff101010;

    m_fBlurConst = 4.0f;
    m_TechniqueIndex = 0;

    memset(m_Palette, 0xFF, 256 * sizeof(PALETTEENTRY));
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: This creates all device-dependent managed objects, such as managed
//       textures and managed vertex buffers.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;

    // Initialize the font's internal textures
    m_pFont->InitDeviceObjects( m_pd3dDevice );
    m_pFontSmall->InitDeviceObjects( m_pd3dDevice );

    DWORD *rgdwAdjacency = NULL;

    TCHAR str[MAX_PATH];
    DXUtil_FindMediaFileCb( str, sizeof(str), TEXT("sphere.x") );
    hr = D3DXLoadMeshFromX(str, D3DXMESH_MANAGED, 
                           m_pd3dDevice, NULL, NULL, NULL, NULL, &m_pMesh);

    if (FAILED(hr) || (m_pMesh == NULL))
    {
        return E_FAIL;
    }

    rgdwAdjacency = new DWORD[m_pMesh->GetNumFaces() * 3];

    if (rgdwAdjacency == NULL)
    {
        return E_FAIL;
    }

    m_pMesh->ConvertPointRepsToAdjacency(NULL, rgdwAdjacency);

    m_pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, rgdwAdjacency, NULL, NULL, NULL);
    delete []rgdwAdjacency;

    DXUtil_FindMediaFileCb( str, sizeof(str), TEXT("earth.bmp") );
    hr = D3DXCreateTextureFromFile(m_pd3dDevice, str, &m_pEarthTexture);
    if (FAILED(hr))
    {
        m_pEarthTexture = NULL;
    }

    return hr;
}




//-----------------------------------------------------------------------------
// Name: SetupQuad()
// Desc: 
//-----------------------------------------------------------------------------
void CMyD3DApplication::SetupQuad()
{
    RECT rc;
    D3DSURFACE_DESC desc;

    GetClientRect(m_hWnd, &rc);
    m_pTextureSurf->GetDesc(&desc);

    UINT Width = rc.right - rc.left;
    UINT Height = rc.bottom - rc.top;

    FLOAT fWidth5 = (FLOAT)Width - 0.5f;
    FLOAT fHeight5 = (FLOAT)Height - 0.5f;

    FLOAT fHalf = m_fBlurConst;
    FLOAT fOffOne = fHalf * 0.5f;
    FLOAT fOffTwo = fOffOne * sqrtf(3.0f);

    FLOAT fTexWidth1 = (FLOAT)Width / (FLOAT)desc.Width;
    FLOAT fTexHeight1 = (FLOAT)Height / (FLOAT)desc.Height;

    FLOAT fWidthMod = 1.0f / (FLOAT)desc.Width ;
    FLOAT fHeightMod = 1.0f / (FLOAT)desc.Height;

    // Create vertex buffer
    m_Vertex[0].pos = D3DXVECTOR4(fWidth5, -0.5f, 0.0f, 1.0f);
    m_Vertex[0].clr = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.66666f);
    m_Vertex[0].tex1 = D3DXVECTOR2(fTexWidth1, 0.0f);
    m_Vertex[0].tex2 = D3DXVECTOR2(fTexWidth1, 0.0f - fHalf*fHeightMod);
    m_Vertex[0].tex3 = D3DXVECTOR2(fTexWidth1 - fOffTwo*fWidthMod, 0.0f - fOffOne*fHeightMod);
    m_Vertex[0].tex4 = D3DXVECTOR2(fTexWidth1 + fOffTwo*fWidthMod, 0.0f - fOffOne*fHeightMod);
    m_Vertex[0].tex5 = D3DXVECTOR2(fTexWidth1 - fOffTwo*fWidthMod, 0.0f + fOffOne*fHeightMod);
    m_Vertex[0].tex6 = D3DXVECTOR2(fTexWidth1 + fOffTwo*fWidthMod, 0.0f + fOffOne*fHeightMod);

    m_Vertex[1].pos = D3DXVECTOR4(fWidth5, fHeight5, 0.0f, 1.0f);
    m_Vertex[1].clr = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.66666f);
    m_Vertex[1].tex1 = D3DXVECTOR2(fTexWidth1, fTexHeight1);
    m_Vertex[1].tex2 = D3DXVECTOR2(fTexWidth1, fTexHeight1 - fHalf*fHeightMod);
    m_Vertex[1].tex3 = D3DXVECTOR2(fTexWidth1 - fOffTwo*fWidthMod, fTexHeight1 - fOffOne*fHeightMod);
    m_Vertex[1].tex4 = D3DXVECTOR2(fTexWidth1 + fOffTwo*fWidthMod, fTexHeight1 - fOffOne*fHeightMod);
    m_Vertex[1].tex5 = D3DXVECTOR2(fTexWidth1 - fOffTwo*fWidthMod, fTexHeight1 + fOffOne*fHeightMod);
    m_Vertex[1].tex6 = D3DXVECTOR2(fTexWidth1 + fOffTwo*fWidthMod, fTexHeight1 + fOffOne*fHeightMod);

    m_Vertex[2].pos = D3DXVECTOR4(-0.5f, -0.5f, 0.0f, 1.0f);
    m_Vertex[2].clr = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.66666f);
    m_Vertex[2].tex1 = D3DXVECTOR2(0.0f, 0.0f);
    m_Vertex[2].tex2 = D3DXVECTOR2(0.0f, 0.0f - fHalf*fHeightMod);
    m_Vertex[2].tex3 = D3DXVECTOR2(0.0f - fOffTwo*fWidthMod, 0.0f - fOffOne*fHeightMod);
    m_Vertex[2].tex4 = D3DXVECTOR2(0.0f + fOffTwo*fWidthMod, 0.0f - fOffOne*fHeightMod);
    m_Vertex[2].tex5 = D3DXVECTOR2(0.0f - fOffTwo*fWidthMod, 0.0f + fOffOne*fHeightMod);
    m_Vertex[2].tex6 = D3DXVECTOR2(0.0f + fOffTwo*fWidthMod, 0.0f + fOffOne*fHeightMod);

    m_Vertex[3].pos = D3DXVECTOR4(-0.5f, fHeight5, 0.0f, 1.0f);
    m_Vertex[3].clr = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.66666f);
    m_Vertex[3].tex1 = D3DXVECTOR2(0.0f, fTexHeight1);
    m_Vertex[3].tex2 = D3DXVECTOR2(0.0f, fTexHeight1 - fHalf*fHeightMod);
    m_Vertex[3].tex3 = D3DXVECTOR2(0.0f - fOffTwo*fWidthMod, fTexHeight1 - fOffOne*fHeightMod);
    m_Vertex[3].tex4 = D3DXVECTOR2(0.0f + fOffTwo*fWidthMod, fTexHeight1 - fOffOne*fHeightMod);
    m_Vertex[3].tex5 = D3DXVECTOR2(0.0f + fOffTwo*fWidthMod, fTexHeight1 + fOffOne*fHeightMod);
    m_Vertex[3].tex6 = D3DXVECTOR2(0.0f - fOffTwo*fWidthMod, fTexHeight1 + fOffOne*fHeightMod);
}

//-----------------------------------------------------------------------------
// Name: UpdateTechniqueSpecificVariables()
// Desc: Certain parameters need to be specified for specific techniques
//          i.e. the MaxBlurFactor needs to be updated (retrieved from 
//              that technique annotation informaiton )
//-----------------------------------------------------------------------------
void CMyD3DApplication::UpdateTechniqueSpecificVariables()
{
    D3DXHANDLE hTech;
    D3DXHANDLE hBlurFactor, hNumKernelEntries, hInputArray, hOutputArray;
    float MaxBlurFactor = 3.0f / 4.0f;
    LPCSTR InputArrayName, OutputArrayName;
    int iEntry;
    int NumKernelEntries;

    SetupQuad();

    hTech = m_pEffect->GetTechniqueByName(m_TechniqueNames[m_TechniqueIndex]);

    // this shouldn't happen unless the effect file has been tampered with
    if(hTech == NULL)
        return;

    // get the MaxBlurFactor to set as a global variable
    hBlurFactor = m_pEffect->GetAnnotationByName(hTech, "MaxBlurFactor");
    if (hBlurFactor != NULL)
    {
        m_pEffect->GetFloat(hBlurFactor, &MaxBlurFactor);
    }

    m_pEffect->SetFloat("MaxBlurFactor", MaxBlurFactor);

    // if there is a kernel to scale, then do so
    hNumKernelEntries = m_pEffect->GetAnnotationByName(hTech, "NumKernelEntries");
    hInputArray = m_pEffect->GetAnnotationByName(hTech, "KernelInputArray");
    hOutputArray = m_pEffect->GetAnnotationByName(hTech, "KernelOutputArray");
    if ((hNumKernelEntries != NULL) && (hInputArray != NULL) && (hOutputArray != NULL))
    {
        m_pEffect->GetInt(hNumKernelEntries, &NumKernelEntries);
        m_pEffect->GetString(hInputArray, &InputArrayName);
        m_pEffect->GetString(hOutputArray, &OutputArrayName);

        if (NumKernelEntries > 0)
        {
            D3DXVECTOR2 *rgfTemp = new D3DXVECTOR2[NumKernelEntries];
            if (rgfTemp == NULL)
                return;

            m_pEffect->GetValue(InputArrayName, rgfTemp, sizeof(D3DXVECTOR2) * NumKernelEntries);

            D3DSURFACE_DESC desc;
            m_pTextureSurf->GetDesc(&desc);

            FLOAT fWidthMod = m_fBlurConst / (FLOAT)desc.Width ;
            FLOAT fHeightMod = m_fBlurConst / (FLOAT)desc.Height;


            for (iEntry = 0; iEntry < NumKernelEntries; iEntry++)
            {
                rgfTemp[iEntry].x *= fWidthMod;
                rgfTemp[iEntry].y *= fHeightMod;
            }

            m_pEffect->SetValue(OutputArrayName, rgfTemp, sizeof(D3DXVECTOR2) * NumKernelEntries);

            delete []rgfTemp;
        }       
    }
}

//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Restore device-memory objects and state after a device is created or
//       resized.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    HRESULT hr;

    m_pFont->RestoreDeviceObjects();
    m_pFontSmall->RestoreDeviceObjects();

    // Update view matrix
    D3DXVECTOR3 vecEye(0.0f, 0.0f, 3.0f);
    D3DXVECTOR3 vecAt (0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vecUp (0.0f, 1.0f, 0.0f);
    D3DMATERIAL9 mat;

    D3DXCOLOR colorWhite(1.0f, 1.0f, 1.0f, 1.0f);
    D3DXCOLOR colorBlack(0.0f, 0.0f, 0.0f, 1.0f);
    mat.Diffuse = colorWhite;
    mat.Ambient = colorWhite;
    mat.Specular = colorBlack;
    mat.Emissive = colorBlack;
    mat.Power = 4;
    
    m_pd3dDevice->SetMaterial(&mat);

    D3DXMATRIX matView;
    D3DXMatrixLookAtRH(&matView, &vecEye, &vecAt, &vecUp);

    D3DLIGHT9 light;

    light.Type        = D3DLIGHT_DIRECTIONAL;

    light.Diffuse.r = 1.0;
    light.Diffuse.g = 1.0;
    light.Diffuse.b = 1.0;
    light.Specular.r = 0;
    light.Specular.g = 0;
    light.Specular.b = 0;
    light.Ambient.r = 0.25;
    light.Ambient.g = 0.25;
    light.Ambient.b = 0.25;

    light.Position     = D3DXVECTOR3(0.0f, 0.0f, 20.0f);
    light.Direction    = D3DXVECTOR3( 1.0f, -1.0f, 1.0f);
    light.Attenuation0 = 0.0f;
    light.Attenuation1 = 0.0f;
    light.Attenuation2 = 0.0f;
    light.Range = ((float)sqrt(FLT_MAX));

    switch( light.Type )
    {
        case D3DLIGHT_POINT:
            light.Attenuation0 = 1.0f;
            break;
        case D3DLIGHT_DIRECTIONAL:
            light.Position     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            break;
        case D3DLIGHT_SPOT:
            light.Position     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            light.Range        =   1.0f;
            light.Falloff      = 100.0f;
            light.Theta        =   0.8f;
            light.Phi          =   1.0f;
            light.Attenuation2 =   1.0f;
    }

    hr = m_pd3dDevice->SetLight(0, &light );
    if (FAILED(hr))
    {
        return E_FAIL;
    }

    hr = m_pd3dDevice->LightEnable(0, TRUE);
    if (FAILED(hr))
    {
        return E_FAIL;
    }

    m_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

    // Setup render state
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0);

    m_pd3dDevice->SetPaletteEntries(0, m_Palette);
    m_pd3dDevice->SetCurrentTexturePalette(0);

    RECT rc;
    GetClientRect(m_hWnd, &rc);

    UINT Width = rc.right - rc.left;
    UINT Height = rc.bottom - rc.top;

    m_pd3dDevice->GetViewport(&m_ViewportFB);

    // backbuffer viewport is identical to frontbuffer, except starting at 0, 0
    m_ViewportOffscreen = m_ViewportFB;
    m_ViewportOffscreen.X = 0;
    m_ViewportOffscreen.Y = 0;

    // Create caustic texture
    D3DDISPLAYMODE mode;
    m_pd3dDevice->GetDisplayMode( 0, &mode );

    if(FAILED(hr = D3DXCreateTexture(m_pd3dDevice, Width, Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture)) &&
       FAILED(hr = D3DXCreateTexture(m_pd3dDevice, Width, Height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture)))
    {
        return hr;
    }

    D3DSURFACE_DESC desc;
    m_pTexture->GetSurfaceLevel(0, &m_pTextureSurf);
    m_pTextureSurf->GetDesc(&desc);

    if(FAILED(hr = D3DXCreateRenderToSurface(m_pd3dDevice, desc.Width, desc.Height, 
        desc.Format, TRUE, D3DFMT_D16, &m_pRenderToSurface)))
    {
        return hr;
    }

    // clear the surface alpha to 0 so that it does not bleed into a "blurry" background
    //   this is possible because of the avoidance of blurring in a non-blurred texel
    if(SUCCEEDED(m_pRenderToSurface->BeginScene(m_pTextureSurf, NULL)))
    {
        m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0x00, 1.0f, 0);
        m_pRenderToSurface->EndScene( 0 );
    }

    LPD3DXBUFFER pBufferErrors = NULL;
    TCHAR str[MAX_PATH];
    DXUtil_FindMediaFileCb( str, sizeof(str), TEXT("DepthOfField.fx") );
    hr = D3DXCreateEffectFromFile(m_pd3dDevice, str, NULL, NULL, 0, NULL, &m_pEffect, &pBufferErrors );
    if( FAILED( hr ) )
    {
        return hr;
    }

    m_pEffect->SetVector("Ambient", (D3DXVECTOR4*)&light.Ambient);
    m_pEffect->SetVector("Diffuse", (D3DXVECTOR4*)&colorWhite);
    m_pEffect->SetTexture("EarthTexture", m_pEarthTexture);
    m_pEffect->SetTexture("RenderTargetTexture", m_pTexture);

    UpdateTechniqueSpecificVariables();

    return hr;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Called when the device-dependent objects are about to be lost.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();
    m_pFontSmall->InvalidateDeviceObjects();

    SAFE_RELEASE(m_pTextureSurf);
    SAFE_RELEASE(m_pTexture);
    SAFE_RELEASE(m_pRenderToSurface);
    SAFE_RELEASE(m_pEffect);

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::DeleteDeviceObjects()
{
    m_pFont->DeleteDeviceObjects();
    m_pFontSmall->DeleteDeviceObjects();

    SAFE_RELEASE(m_pTextureSurf);
    SAFE_RELEASE(m_pTexture);
    SAFE_RELEASE(m_pRenderToSurface);

    SAFE_RELEASE(m_pMesh);
    SAFE_RELEASE(m_pEarthTexture);

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
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    D3DXMATRIXA16 matWorld;
    D3DXMATRIXA16 matWorldTemp;
    D3DXMATRIXA16 matProj;
    D3DXMATRIXA16 matView;

    UINT iPass, cPasses;

    if (m_bDrawToRenderTarget)
    {
        m_pRenderToSurface->BeginScene(m_pTextureSurf, &m_ViewportOffscreen);
    }
    else
    {
        m_pd3dDevice->BeginScene();
        m_pd3dDevice->SetViewport(&m_ViewportFB);
    }

    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, m_dwBackgroundColor, 1.0f, 0);

    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

    // Update view matrix
    D3DXVECTOR4 vFocalPlane;

    FLOAT fLerp = (m_fTime - m_fChangeTime) / 2.0f;
    fLerp = min(fLerp, 1.0f);

    D3DXVec4Lerp(&vFocalPlane, &m_vFocalPlaneSrc, &m_vFocalPlaneDest, fLerp);
    m_pEffect->SetVector("vFocalPlane", &vFocalPlane);

    // Generate view projection matrix
    D3DXVECTOR3 vecEye(0.0f, 0.0f, 3.0f);
    D3DXVECTOR3 vecAt (0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vecUp (0.0f, 1.0f, 0.0f);

    D3DXMatrixLookAtRH(&matView, &vecEye, &vecAt, &vecUp);
    D3DXMatrixPerspectiveFovRH(&matProj, D3DXToRadian(60.0f), m_fAspectRatio, 0.5f, 100.0f);
    D3DXMatrixMultiply(&matProj, &matView, &matProj);

    // Set world drawing technique
    m_pEffect->SetTechnique("World");
    m_pEffect->SetMatrix("mProjection", &matProj);

    float WorldPos[] = { 3.0f,  3.0f, -5.0f,
                        -0.5f, -0.5f,  0.5f,
                         1.0f,  1.0f, -2.0f};

    for(int iWorld=0; iWorld < 3; iWorld++)
    {
        // setup the world matrix for the current world
        D3DXMatrixRotationY(&matWorld, m_fTime * 0.66666f);
        D3DXMatrixTranslation(&matWorldTemp, WorldPos[iWorld *3], WorldPos[iWorld *3 + 1], WorldPos[iWorld *3 + 2]);
        D3DXMatrixMultiply(&matWorld, &matWorld, &matWorldTemp);

        m_pEffect->SetMatrix("mWorldView", &matWorld);

        m_pEffect->Begin(&cPasses, 0);
        for (iPass = 0; iPass < cPasses; iPass++)
        {
            m_pEffect->Pass(iPass);

            m_pMesh->DrawSubset(0);
        }
        m_pEffect->End();
    }

    if (m_bDrawToRenderTarget)
    {
        m_pRenderToSurface->EndScene( 0 );
    }
    else
    {
        m_pd3dDevice->EndScene();
    }

    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE );
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{
    // Clear the viewport
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET, 0x00000000, 1.0f, 0L );

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        // Update projection matrix
        FLOAT fAspectRatio = m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
        D3DXMATRIX matProjection;
        D3DXMatrixPerspectiveFovRH(&matProjection, D3DXToRadian(60.0f), fAspectRatio, 1.0f, 100.0f);
        m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProjection);

        m_fAspectRatio = fAspectRatio;


        if (m_bDrawToRenderTarget)
        {
            m_pd3dDevice->SetViewport(&m_ViewportFB);

            if (m_bShowBlurFactor)
                m_pEffect->SetTechnique("ShowAlpha");
            else if (m_bShowUnblurred)
                m_pEffect->SetTechnique("ShowUnmodified");
            else
                m_pEffect->SetTechnique(m_TechniqueNames[m_TechniqueIndex]);

            UINT iPass, cPasses;

            m_pEffect->Begin(&cPasses, 0);
            for (iPass = 0; iPass < cPasses; iPass++)
            {
                m_pEffect->Pass(iPass);
                m_pd3dDevice->SetFVF(VERTEX::FVF);
                m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Vertex, sizeof(VERTEX));
            }
            m_pEffect->End();
        }

        // Output statistics
        m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );
        m_pFontSmall->DrawText( 2, 40, D3DCOLOR_ARGB(255,255,255,255), _T("Technique:"));
        m_pFontSmall->DrawText( 100, 40, D3DCOLOR_ARGB(255,255,255,255), m_TechniqueNames[m_TechniqueIndex]);

        // Draw help
        if( m_bDrawHelp )
        {
            m_pFontSmall->DrawText( 2, 60, D3DCOLOR_ARGB(255,255,255,255),
                                    _T("Keyboard controls:"));
            m_pFontSmall->DrawText( 20, 80, D3DCOLOR_ARGB(255,255,255,255),
                                    _T("Show Blur Factor (Alpha)\nShow Unblurred\nToggle Background\n")
                                    _T("Increase Blur\nDecrease Blur\nReset Blur\nFocal Plane\nNext Technique\nPrev Technique\n")
                                    _T("Help\nChange Device\nQuit"));
            m_pFontSmall->DrawText( 240, 80, D3DCOLOR_ARGB(255,255,255,255),
                                    _T("A\nU\nB\n")
                                    _T("Y\nH\nN\n1,2,3\nPageDown\nPageUp\n")
                                    _T("F1\nF2\nEsc"));
        }
        else
        {
            m_pFontSmall->DrawText( 2, 60, D3DCOLOR_ARGB(255,255,255,255), _T("Press F1 for help"));
        }

        // End the scene.
        m_pd3dDevice->EndScene();
    }
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
                                          D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat )
{
    if( dwBehavior & D3DCREATE_PUREDEVICE )
        return E_FAIL;

    if( pCaps->PixelShaderVersion < D3DPS_VERSION(1,1) )
        return E_FAIL;

    // If device doesn't support 1.1 vertex shaders in HW, switch to SWVP.
    if( pCaps->VertexShaderVersion < D3DVS_VERSION(1,1) )
    {
        if( (dwBehavior & D3DCREATE_SOFTWARE_VERTEXPROCESSING ) == 0 )
        {
            return E_FAIL;
        }
    }

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Message proc function to handle key and menu input
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam )
{
    if(uMsg == WM_COMMAND && m_pD3D)
    {
        D3DXVECTOR4 vFocalPlane;
        m_pEffect->GetVector("vFocalPlane", &vFocalPlane);

        switch( LOWORD(wParam) )
        {
        case IDM_OPTIONS_SHOWBLURFACTOR:
            m_bShowBlurFactor = !m_bShowBlurFactor;
            if (m_bShowBlurFactor)
                m_bShowUnblurred = FALSE;
            CheckMenuItem( GetMenu(hWnd), IDM_OPTIONS_SHOWBLURFACTOR , m_bShowBlurFactor ? MF_CHECKED : MF_UNCHECKED);
            CheckMenuItem( GetMenu(hWnd), IDM_OPTIONS_SHOWUNBLURRED , m_bShowUnblurred ? MF_CHECKED : MF_UNCHECKED);
            break;

        case IDM_OPTIONS_SHOWUNBLURRED:
            m_bShowUnblurred = !m_bShowUnblurred;
            if (m_bShowUnblurred)
                m_bShowBlurFactor = FALSE;
            CheckMenuItem( GetMenu(hWnd), IDM_OPTIONS_SHOWBLURFACTOR , m_bShowBlurFactor ? MF_CHECKED : MF_UNCHECKED);
            CheckMenuItem( GetMenu(hWnd), IDM_OPTIONS_SHOWUNBLURRED , m_bShowUnblurred ? MF_CHECKED : MF_UNCHECKED);
            break;

        case IDM_OPTIONS_TOGGLEBACKGROUND:
            m_dwBackgroundColor = (m_dwBackgroundColor == 0xffffffff) ? 0xff101010 : 0xffffffff;
            break;

        case IDM_OPTIONS_NEXTTECHNIQUE:
        {
            DWORD OriginalTechnique = m_TechniqueIndex;
            do
            {
                m_TechniqueIndex++;

                if (m_TechniqueIndex == m_TechniqueCount)
                {
                    m_TechniqueIndex = 0;
                }

                D3DXHANDLE hTech = m_pEffect->GetTechniqueByName(m_TechniqueNames[m_TechniqueIndex]);
                if (SUCCEEDED(m_pEffect->ValidateTechnique(hTech)))
                {
                    break;
                }
            } while(OriginalTechnique != m_TechniqueIndex);

            UpdateTechniqueSpecificVariables();
            break;
        }

        case IDM_OPTIONS_PREVTECHNIQUE:
        {
            DWORD OriginalTechnique = m_TechniqueIndex;
            do
            {
                if (m_TechniqueIndex == 0)
                {
                    m_TechniqueIndex = m_TechniqueCount;
                }

                m_TechniqueIndex--;

                if (SUCCEEDED(m_pEffect->ValidateTechnique(m_TechniqueNames[m_TechniqueIndex])))
                {
                    break;
                }
            } while(OriginalTechnique != m_TechniqueIndex);

            UpdateTechniqueSpecificVariables();
            break;
        }

        case IDM_OPTIONS_FOCALPLANE1:
            m_fChangeTime = m_fTime;
            m_vFocalPlaneDest = D3DXVECTOR4(0.0f, 0.0f, 1.0f, -0.5f);
            m_vFocalPlaneSrc = vFocalPlane;
            break;

        case IDM_OPTIONS_FOCALPLANE2:
            m_fChangeTime = m_fTime;
            m_vFocalPlaneDest = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 2.0f);
            m_vFocalPlaneSrc = vFocalPlane;
            break;

        case IDM_OPTIONS_FOCALPLANE3:
            m_fChangeTime = m_fTime;
            m_vFocalPlaneDest = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 5.0f);
            m_vFocalPlaneSrc = vFocalPlane;
            break;

        case IDM_OPTIONS_INCREASEBLUR:
            m_fBlurConst += 0.25f;
            UpdateTechniqueSpecificVariables();
            break;

        case IDM_OPTIONS_DECREASEBLUR:
            m_fBlurConst -= 0.25f;
            UpdateTechniqueSpecificVariables();
            break;

        case IDM_OPTIONS_RESETBLUR:
            m_fBlurConst = 4.0f;
            UpdateTechniqueSpecificVariables();
            break;

        case IDM_TOGGLEHELP:
            m_bDrawHelp = !m_bDrawHelp;
            break;
        }
    }

    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}