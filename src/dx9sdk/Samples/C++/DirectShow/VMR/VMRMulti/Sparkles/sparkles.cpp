//-----------------------------------------------------------------------------
// File: sparkles.cpp
//
// Desc: DirectShow sample code
//		 Example code showing how to do a random "sparkles". Similar to flares,
//       sparkles use alpha blending 1-1 to achieve cool transparent blends
//
//       Note: This code uses the D3D Framework helper library.
//
//	Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#include "..\project.h"
#include <math.h>

#define D3D_OVERLOADS
#include "..\D3DHelpers\D3DMath.h"
#include "..\D3DHelpers\D3DTextr.h"
#include "..\D3DHelpers\D3DUtil.h"


//-----------------------------------------------------------------------------
// Declare the application globals for use in screensaver.cpp
//-----------------------------------------------------------------------------

TCHAR  g_strScreenSaverName[] = TEXT("MSDNSparkles\0");
BOOL   g_bAppUseZBuffer    = FALSE;   // Create/use a z-buffering
BOOL   g_bAppUseBackBuffer = TRUE;    // Create/use a back buffer


//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------

UINT nMaxNumSparkles            = MAX_SPARKLES;
UINT nCurNumSparkles            = CUR_SPARKLES;
D3DCOLOR bckColor;

//BLENDING
D3DBLEND srcBlend = D3DBLEND_ONE;
D3DBLEND dstBlend = D3DBLEND_ONE;

//colors
D3DVECTOR   white(1.0f, 1.0f, 1.0f);
D3DVECTOR   black(0.0f, 0.0f, 0.0f);
D3DVECTOR   red(1.0f, 0.0f, 0.0f);
D3DVECTOR   green(0.0f, 1.0f, 0.0f);
D3DVECTOR   blue(0.0f, 0.0f, 1.0f);
D3DVECTOR   cyan(0.0f, 1.0f, 1.0f);
D3DVECTOR   magenta(1.0f, 0.0f, 1.0f);
D3DVECTOR   yellow(1.0f, 1.0f, 0.0f);

//viewing
D3DVECTOR       from(-8.0f, 4.0f, -8.0f);
D3DVECTOR       at(  0.0f, 0.0f, 0.0f);
D3DVECTOR       up(  0.0f, 1.0f, 0.0f);
D3DMATRIX       proj, view, world;
D3DVIEWPORT7    vp;

//textures
const   int NumTextures = 6;
LPDIRECTDRAWSURFACE7  g_ptexSparkleTextures[NumTextures];
TCHAR* g_szSparkleTextures[NumTextures][80];

// sparkle mesh
D3DLVERTEX  s_mesh[MAX_SPARKLES*4];
WORD        s_indices[MAX_SPARKLES*6];

//dynamics
#define MAX_FORCE       0.02f
#define MAX_VELOCITY    0.8
#define DAMP            0.998f
#define MAX_DIST       60.0f

//sparkle
typedef struct t_sparkle 
{
    int         texture;
    int         age, cur_age;   // start at age and tick down to 0
    float       scale, delta_scale;
    D3DVECTOR   position;
    D3DVECTOR   velocity;
    D3DVECTOR   color;
} Sparkle;

Sparkle     *sparkle;

//random rendering parameters
int                 texture         = 0;
unsigned int        texture_age     = 1500;//500;
const unsigned int  min_texture_age = 1500;//500;
const unsigned int  max_texture_age = 8000;//2000;

const unsigned int  min_age = 100;
const unsigned int  max_age = 200;
float               start_scale = 0.1f;
const float         min_delta = 1.015f;
const float         max_delta = 1.02f;
float               world_size = 200.0f;
const float         orbit_size = 10.f;//20.0f;

const int           NumColorModes = 2;
// 0==random, 1==rgb bounce
int                 color_mode = 0;
unsigned int        color_age       = 3000;//1000;
const unsigned int  min_color_age   = 3000;//1000;
const unsigned int  max_color_age   = 6000;//2000;
const float         min_color_delta = 0.0003f;
const float         max_color_delta = 0.03f;

const int           NumColorModifierModes = 5;//6;
// 0==no change, 1==full saturation, 2==jewel tones, 3==pastels, 4==brighter, 5==darker, cool but not for the masses
int                 color_modifier_mode    = 0;
unsigned int        color_modifier_age     = 1500;//750;
const unsigned int  min_color_modifier_age = 1500;//750;
const unsigned int  max_color_modifier_age = 3000;//1500;

//macro
#define rnd() float(rand())/RAND_MAX




//-----------------------------------------------------------------------------
// Name: RandomViewpoint()
// Desc: set up a random viewpoint
//-----------------------------------------------------------------------------
void
RandomViewpoint(LPDIRECT3DDEVICE7 pd3dDevice,float tic)
{
    float fromX, fromY, fromZ;

    fromX = (float)sin(tic*0.59);
    fromZ = (float)cos(tic*0.59);
    if ( texture <= 9 )
        fromY = (float)sin(tic*0.72);
    else
        fromY = (float)cos(tic*0.72);
    from = D3DVECTOR(orbit_size*fromX,
                     orbit_size*fromY,
                     orbit_size*fromZ );

    D3DUtil_SetViewMatrix( view, from, at, up );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_VIEW, &view);
}


//-----------------------------------------------------------------------------
// Name: RandomTexture()
// Desc: set up a random texture value to select active texture.
//-----------------------------------------------------------------------------
int
RandomTexture(int texture, int overflow)
{
    int retVal;

    if (texture == NumTextures)
    {
        retVal = overflow;  // init to random from the n case, overflow
    }
    else
    {
        retVal = texture;   // init to current in the 0..n-1 case
    }
    return retVal;
}


//-----------------------------------------------------------------------------
// Name: RandomSparkle()
// Desc: set up a random sparkle.
//-----------------------------------------------------------------------------
Sparkle
RandomSparkle(void)
{
    Sparkle ret;
    static float    red = 1.0f, grn = 1.0f, blu = 1.0f;
    static float    d_red = -(min_color_delta + rnd()*max_color_delta);
    static float    d_grn = -(min_color_delta + rnd()*max_color_delta);
    static float    d_blu = -(min_color_delta + rnd()*max_color_delta);

    ret.age         = min_age + (int)(rnd() * (max_age-min_age));
    ret.cur_age     = ret.age;
    ret.scale       = start_scale;
    ret.delta_scale = min_delta + rnd() * (max_delta - min_delta);
    ret.position    = D3DVECTOR(world_size * (rnd()-rnd()),
                                world_size * (rnd()-rnd()),
                                world_size * (rnd()-rnd()));
    ret.velocity    = D3DVECTOR(0.0f);
    ret.texture     = RandomTexture(texture, rand() % (NumTextures-1));

    switch (color_mode) {
        case 0 : //random
            ret.color = D3DVECTOR(rnd(), rnd(), rnd());
            break;
        case 1 : //rgb bounce
            red += d_red;
            if (red > 1.0f) {
                red = 1.0f;
                d_red = -(min_color_delta + rnd()*max_color_delta);
            } else if (red < 0.0f) {
                red = 0.0f;
                d_red = min_color_delta + rnd()*max_color_delta;
            }
            grn += d_grn;
            if (grn > 1.0f) {
                grn = 1.0f;
                d_grn = -(min_color_delta + rnd()*max_color_delta);
            } else if (grn < 0.0f) {
                grn = 0.0f;
                d_grn = min_color_delta + rnd()*max_color_delta;
            }
            blu += d_blu;
            if (blu > 1.0f) {
                blu = 1.0f;
                d_blu = -(min_color_delta + rnd()*max_color_delta);
            } else if (blu < 0.0f) {
                blu = 0.0f;
                d_blu = min_color_delta + rnd()*max_color_delta;
            }

            ret.color = D3DVECTOR(red, grn, blu);
            break;
        default :
            ret.color = D3DVECTOR(0.0f, 0.5f, 1.0f);
            break;
    }

    switch (color_modifier_mode) {
        case 0 :    // no change
            break;
        case 1 :    // full saturation
            ret.color /= Max(ret.color);
            break;
        case 2 :    // jewel tones
            ret.color -= Min(ret.color);
            ret.color /= Max(ret.color);
            break;
        case 3 :    // pastels
            ret.color -= Min(ret.color);
            ret.color /= Max(ret.color);
            ret.color = D3DVECTOR(0.6f) + 0.4f * ret.color;
            break;
        case 4 :    // brighter, cool and could be for the masses
            ret.color *= 1.2f;
            break;
        case 5 :    // darker, cool but not for the masses
            ret.color *= 0.2f;
            break;
        default :
            break;
    }

    return ret;
}


//-----------------------------------------------------------------------------
// Name: InitSparkles()
// Desc: changes texture and sets up quad
//-----------------------------------------------------------------------------
void
InitSparkles(void)
{
    texture = 1;   // start with dx7 bitmap

    sparkle = (Sparkle *) malloc(nMaxNumSparkles * sizeof(Sparkle));
    if (!sparkle)
        return;
    
    for (UINT i=0; i<nCurNumSparkles; i++) {
        sparkle[i] = RandomSparkle();
    }

    // set up indices
    for (i=0; i<nMaxNumSparkles; i++) {
        s_indices[i*6+0] = (WORD) (4*i + 0);
        s_indices[i*6+1] = (WORD) (4*i + 1);
        s_indices[i*6+2] = (WORD) (4*i + 2);
        s_indices[i*6+3] = (WORD) (4*i + 0);
        s_indices[i*6+4] = (WORD) (4*i + 2);
        s_indices[i*6+5] = (WORD) (4*i + 3);
    }
}   // end of InitSparkles()


//-----------------------------------------------------------------------------
// Name: UpdateSparkles
// Desc: mods the random rendering parameters.
//-----------------------------------------------------------------------------
void
UpdateSparkles(void)
{
    UINT    i;
//0..n 0..n-1==current, n==random
    texture_age--;
    if (texture_age == 0) {
        texture_age = min_texture_age + (unsigned int)(rnd()*(max_texture_age - min_texture_age));
        texture = rand() % (NumTextures);
        texture = RandomTexture(texture, rand() % (NumTextures-1));
    }
//0..1 0==random, 1==rgb bounce
    color_age--;
    if (color_age == 0) {
        color_age = min_color_age + (int)(rnd()*(max_color_age - min_color_age));
        color_mode = rand() % NumColorModes;
    }
//0..5 0==no change, 1==full saturation, 2==jewel tones, 3==pastels, 4==brighter, 5==darker, cool but not for the masses,
    color_modifier_age--;
    if (color_modifier_age == 0) {
        color_modifier_age = min_color_modifier_age + (int)(rnd()*(max_color_modifier_age - min_color_modifier_age));
        color_modifier_mode = rand() % NumColorModifierModes;
    }
    //update sparkles
    for (i=0; i<nCurNumSparkles; i++) {
        sparkle[i].cur_age--;
        if (sparkle[i].cur_age == 0) {
            sparkle[i] = RandomSparkle();
        }

        sparkle[i].scale *= sparkle[i].delta_scale;
    }

}   // end of UpdateSparkles()


//-----------------------------------------------------------------------------
// Name: DrawSparkles
// Desc: draw the sparkles swarming around.
//-----------------------------------------------------------------------------
BOOL
DrawSparkles(LPDIRECT3DDEVICE7 lpDev, D3DVECTOR from, D3DVECTOR at)
{
    D3DVECTOR   view_dir, position, dx, dy;
    UINT        i;

    view_dir = Normalize(at - from);
    dx = CrossProduct(view_dir, D3DVECTOR(0.0f, 1.0f, 0.0f));
    dy = CrossProduct(view_dir, dx);
    dx = CrossProduct(view_dir, dy);

    // draw the sparkles
    // In order to be more efficient we want to batch up all the sparkles
    // which use the same texture and just do a single DrawPrim call.
    int flags[NumTextures];
    for (int tex=0; tex<NumTextures; tex++) {
        flags[tex] = 0;
    }
    // figure out which textures are being used
    for (i=0; i<nCurNumSparkles; i++) {
        flags[sparkle[i].texture]++;
    }
    // for each texture that is used, batch up the sparkles and draw them
    for (tex=0; tex<NumTextures; tex++) {
        if (flags[tex] == 0)
            continue;

        // set the right material/texture combo for this batch of sparkles
        lpDev->SetTexture(0,g_ptexSparkleTextures[tex]);

        //cons up the quads for the batch
        int num = 0;
        for (i=0; i<nCurNumSparkles; i++) {
            if (sparkle[i].texture != tex)
                continue;

            D3DVECTOR   sx  = dx * sparkle[i].scale;
            D3DVECTOR   sy  = dy * sparkle[i].scale;
            float       color_scale = (float)sparkle[i].cur_age/sparkle[i].age;
            D3DVECTOR   cur_color = sparkle[i].color * color_scale;
            D3DCOLOR    color = D3DRGB(cur_color[0], cur_color[1], cur_color[2]);

            position = sparkle[i].position;

            s_mesh[num*4+0] = D3DLVERTEX(position+sx+sy, color, 0, 1.0f, 1.0f);
            s_mesh[num*4+1] = D3DLVERTEX(position-sx+sy, color, 0, 0.0f, 1.0f);
            s_mesh[num*4+2] = D3DLVERTEX(position-sx-sy, color, 0, 0.0f, 0.0f);
            s_mesh[num*4+3] = D3DLVERTEX(position+sx-sy, color, 0, 1.0f, 0.0f);

            num++;
        }

        // done creating the batch, now render it
        if (lpDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,D3DFVF_LVERTEX,
            (LPVOID)s_mesh, 4*flags[tex], s_indices, 6*flags[tex], 0) != D3D_OK)
            return FALSE;
    }

    return TRUE;
}   // end of DrawSparkles()


//-----------------------------------------------------------------------------
// Name: App_OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT App_OneTimeSceneInit()
{
    // seed the random number generator
    srand(timeGetTime());

    //init the background color
    bckColor = D3DRGB(0,0,0);

    //load texture data
    memcpy(g_szSparkleTextures[0],_T("shine1.bmp\0"),sizeof(_T("shine1.bmp\0")));
    memcpy(g_szSparkleTextures[1],_T("shine2.bmp\0"),sizeof(_T("shine2.bmp\0")));
    memcpy(g_szSparkleTextures[2],_T("shine3.bmp\0"),sizeof(_T("shine3.bmp\0")));
    memcpy(g_szSparkleTextures[3],_T("shine4.bmp\0"),sizeof(_T("shine4.bmp\0")));
    memcpy(g_szSparkleTextures[4],_T("shine5.bmp\0"),sizeof(_T("shine5.bmp\0")));
    memcpy(g_szSparkleTextures[5],_T("shine6.bmp\0"),sizeof(_T("shine6.bmp\0")));

    for ( int i = 0; i < NumTextures; i++)
        D3DTextr_CreateTextureFromFile((TCHAR *)g_szSparkleTextures[i]);

    InitSparkles();

    return S_OK;
}


//-----------------------------------------------------------------------------
//	SetTextureState
//-----------------------------------------------------------------------------
void SetTextureState(LPDIRECT3DDEVICE7 pd3dDevice )
{
    // Setup texture states
    D3DTextr_RestoreAllTextures( pd3dDevice );

    //load texture surfaces
    for( int i=0; i<NumTextures; i++ )
        g_ptexSparkleTextures[i] = D3DTextr_GetSurface( (TCHAR *)g_szSparkleTextures[i]);

}


//-----------------------------------------------------------------------------
//	SetRenderState
//
//  Configures Direct3D for rendering sparkles
//-----------------------------------------------------------------------------
void SetRenderState(LPDIRECT3DDEVICE7 pd3dDevice )
{
    // alphablend states
    pd3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
    pd3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND,  srcBlend);
    pd3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, dstBlend);

    // filter states
    pd3dDevice->SetTextureStageState(0,D3DTSS_MINFILTER,  D3DFILTER_LINEAR);
    pd3dDevice->SetTextureStageState(0,D3DTSS_MAGFILTER,  D3DFILTER_LINEAR);
    pd3dDevice->SetTextureStageState(0,D3DTSS_MIPFILTER,  D3DFILTER_LINEAR);

    // Setup non-texture render states
    pd3dDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, FALSE);
    pd3dDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
    pd3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
    pd3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
    pd3dDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);


    // Note: in DX7, setting D3DRENDERSTATE_LIGHTING to FALSE is needed to
    // turn off vertex lighting (and use the color in the D3DLVERTEX instead.)
    pd3dDevice->SetRenderState( D3DRENDERSTATE_LIGHTING, FALSE );

}


//-----------------------------------------------------------------------------
//	SetViewState
//
//	Configures ViewPort for rendering sparkles
//-----------------------------------------------------------------------------

void SetViewState(LPDIRECT3DDEVICE7 pd3dDevice )
{
    // Get the aspect ratio
    pd3dDevice->GetViewport(&vp);
    FLOAT fAspect = ((FLOAT)vp.dwHeight) / vp.dwWidth;

    // set up transform matrices
    D3DUtil_SetProjectionMatrix( proj,
                                 g_PI/4,//1.0f;
                                 fAspect,
                                 1.0f, MAX_DIST );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION, &proj);
    D3DUtil_SetViewMatrix( view, from, at, up );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_VIEW, &view);
    D3DUtil_SetIdentityMatrix( world );
    pd3dDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &world);
}


//-----------------------------------------------------------------------------
// Name: App_InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT App_InitDeviceObjects( HWND hWnd, LPDIRECT3DDEVICE7 pd3dDevice)
{
    // Check parameters
    if( NULL==pd3dDevice )
        return E_INVALIDARG;

    // Setup texture states
    SetTextureState( pd3dDevice );

    // Setup renderstates
    SetRenderState( pd3dDevice );

    // Setup view system
    SetViewState( pd3dDevice );

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: App_FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT App_FrameMove( LPDIRECT3DDEVICE7 pd3dDevice, FLOAT fTimeKey )
{
    // ok, now play with sparkles
    UpdateSparkles();

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: App_Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT App_Render( LPDIRECT3DDEVICE7 pd3dDevice )
{
    static float        tic = -rnd() * 10000.0f;

    // Clear the viewport
    pd3dDevice->Clear( 0UL, NULL, D3DCLEAR_TARGET,
                       bckColor,
                       1.0f, 0L );

    // Begin the scene
    if( FAILED( pd3dDevice->BeginScene() ) )
        return S_OK; // Don't return a "fatal" error

    // tic to move things around
    tic += 0.005f;

    //used in random positioning
    start_scale = 0.05f + (float)(sin(tic * 0.100) + 1.0f)*0.4f;
    world_size  = 0.10f + (float)(cos(tic * 0.072) + 1.0f)*10.0f;

    //modify viewpoint
    RandomViewpoint(pd3dDevice,tic);

    // draw sparkles
    if (!DrawSparkles(pd3dDevice, from, at))
        return E_FAIL;

    // End the scene.
    pd3dDevice->EndScene();

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: App_DeleteDeviceObjects()
// Desc: Called when the app is exitting, or the device is being changed,
//       this function deletes any device dependant objects.
//-----------------------------------------------------------------------------
VOID App_DeleteDeviceObjects( HWND hWnd, LPDIRECT3DDEVICE7 pd3dDevice)
{
    D3DTextr_InvalidateAllTextures();
}


//-----------------------------------------------------------------------------
// Name: App_FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT App_FinalCleanup()
{
    free(sparkle);

    return S_OK;
}


//----------------------------------------------------------------------------
// Name: App_RestoreSurfaces
// Desc: Restores any previously lost surfaces. Must do this for all surfaces
//       (including textures) that the app created.
//----------------------------------------------------------------------------
HRESULT App_RestoreSurfaces()
{
    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: App_ConfirmDevice()
// Desc: Called during device intialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------

HRESULT App_ConfirmDevice( DDCAPS* pddDriverCaps,
                           D3DDEVICEDESC7* pd3dDeviceDesc )
{
        // Get triangle caps (Hardware or software) and check for alpha blending
    LPD3DPRIMCAPS pdpc = &pd3dDeviceDesc->dpcTriCaps;

    if( 0 == ( pdpc->dwSrcBlendCaps & pdpc->dwDestBlendCaps & D3DBLEND_ONE ) )
        return E_FAIL;

    return S_OK;
}



