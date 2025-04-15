//-----------------------------------------------------------------------------
// File: main.cpp
//
// Desc: Example code showing a technique for rendering volumetric fog in D3D.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <Windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <math.h>
#include <stdio.h>
#include <d3dx9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "d3dapp.h"
#include "d3dfont.h"

#define RENDERTARGSIZE 512


// Maintains a set of triangles - its vertices and indices
struct TRIANGLESET
{
    LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
    DWORD dwNumVertices;
    DWORD dwNumTriangles;
    D3DXVECTOR3 Center;
    FLOAT fRadius;
};

struct FILEVERTEX
{
    FLOAT x,y,z;
    FLOAT nx,ny,nz;

    static const DWORD FVF;
};
const DWORD FILEVERTEX::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;



//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
protected:
    D3DXMATRIXA16  m_matObject;
    D3DXMATRIXA16  m_matView;
    D3DXMATRIXA16  m_matProj;
    D3DXMATRIXA16  m_matShadObject;

    BOOL m_bInsideFog;
    BOOL m_bUsePicShader;
    BOOL m_bDrawHelp;

    LPDIRECT3DVERTEXBUFFER9 m_pScreenVertBuf;
    LPDIRECT3DVERTEXBUFFER9 m_pScreenVertBuf2;
    LPDIRECT3DSURFACE9 m_pOldRenderTarget;
    LPDIRECT3DSURFACE9 m_pOldStencilZ;
    LPDIRECT3DSURFACE9 m_pTargetZ;

    TRIANGLESET m_FogVolume;
    TRIANGLESET m_MeshShaderObject;

    BYTE            m_bKey[256];
    D3DXVECTOR3     m_vVelocity;
    FLOAT           m_fYawVelocity;
    FLOAT           m_fPitchVelocity;
    D3DXMATRIXA16      m_matOrientation;
    D3DXVECTOR3     m_vPosition;
    FLOAT           m_fYaw;
    FLOAT           m_fPitch;

    LPDIRECT3DTEXTURE9 m_pBackFogDist;
    LPDIRECT3DTEXTURE9 m_pFrontFogDist;
    LPDIRECT3DTEXTURE9 m_pSceneDist;
    LPDIRECT3DTEXTURE9 m_pTempDist;

    LPDIRECT3DTEXTURE9 m_pStepTexture;
    
    LPDIRECT3DVERTEXDECLARATION9   m_pFogDeclaration;
    LPDIRECT3DVERTEXSHADER9 m_pFogShader;
    LPDIRECT3DVERTEXDECLARATION9   m_pFogDeclaration2;
    LPDIRECT3DVERTEXSHADER9 m_pFogShader2;
    LPDIRECT3DPIXELSHADER9 m_pSubPicShader;

    LPD3DXMESH    m_pMeshObject;
     
    CD3DFont*     m_pFont;
    CD3DFont*     m_pFontSmall;

public:
    CMyD3DApplication();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual HRESULT FinalCleanup();
    virtual HRESULT FrameMove();
    virtual HRESULT Render();
    virtual LRESULT MsgProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    virtual HRESULT ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior, 
        D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat );
    HRESULT SetFogMatrices();
    HRESULT SetObjMatrices();
    HRESULT LoadXFile(TCHAR*, TRIANGLESET *);
    HRESULT ComputeStepTexture();
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
// Name: CMyD3DApplication()
// Desc: Application constructor. Sets attributes for the app.
//-----------------------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
{
    m_d3dEnumeration.AppUsesDepthBuffer   = TRUE;

    m_strWindowTitle    = _T("VolumeFog");

    m_pFont         = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pFontSmall    = new CD3DFont( _T("Arial"),  9, D3DFONT_BOLD );

    for(int i=0;i<256;i++)
        m_bKey[i] = FALSE;

    D3DXMatrixIdentity(&m_matObject);
    D3DXMatrixIdentity(&m_matView);
    D3DXMatrixIdentity(&m_matProj);
    D3DXMatrixIdentity(&m_matShadObject);

    m_vPosition      = D3DXVECTOR3( 0.0f, 0.0f,-4.0f );
    m_vVelocity      = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    m_fYaw           = 0.0f;
    m_fYawVelocity   = 0.0f;
    m_fPitch         = 0.0f;
    m_fPitchVelocity = 0.0f;
    m_bDrawHelp      = FALSE;
   
    m_pOldRenderTarget = NULL;
    m_pOldStencilZ     = NULL;
    m_pScreenVertBuf   = NULL;
    m_pBackFogDist     = NULL;
    m_pSceneDist       = NULL;
    m_pTempDist        = NULL;
    m_pFrontFogDist    = NULL;
    m_pTargetZ         = NULL;
    m_pMeshObject      = NULL;
    m_pStepTexture     = NULL;
    m_pScreenVertBuf   = NULL;
    m_pScreenVertBuf2  = NULL;
    m_pFogDeclaration  = NULL;
    m_pFogShader       = NULL;
    m_pFogDeclaration2 = NULL;
    m_pFogShader2      = NULL;
    m_pSubPicShader    = NULL;

    memset(&m_MeshShaderObject,0,sizeof(m_MeshShaderObject));
    memset(&m_FogVolume,0,sizeof(m_FogVolume));
}




//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
                                          D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat )
{
    if( (dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING ) ||
        (dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING ) )
    {
        if( pCaps->VertexShaderVersion < D3DVS_VERSION(1,0) )
            return E_FAIL;
    }
          
    if( pCaps->PixelShaderVersion < D3DPS_VERSION(1,1) )
        return E_FAIL;
    
    if( dwBehavior & D3DCREATE_PUREDEVICE)
        return E_FAIL;

    if( backBufferFormat != D3DFMT_A8R8G8B8 && 
        backBufferFormat != D3DFMT_X8R8G8B8 && 
        backBufferFormat != D3DFMT_R8G8B8 )
    {
        return E_FAIL;
    }
  
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Process windows messages.
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_KEYUP:
        m_bKey[wParam] = FALSE;
        if( wParam == VK_F1 )
            m_bDrawHelp = !m_bDrawHelp;
        break;

    case WM_KEYDOWN:
        m_bKey[wParam] = TRUE;
        break;
    }

    return CD3DApplication::MsgProc( hwnd, uMsg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: ComputeStepTexture()
// Desc: This computes a step texture - used for high precision fogging.  The
//       step texture is a 4096 texture which increments from 0 to 4095. This 
//       is used because on a triangle basis - the texture interpolators are 
//       much higher precision than the color interpolators. Since we need a 
//       higher precision then 8 bits, we need a way to load in more bits into
//       every pixel. This is only way to do it on an 8 bit card.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ComputeStepTexture()
{
    D3DLOCKED_RECT Lock;
    HRESULT hr;
    unsigned int Width  = 4096;
    unsigned int Height = 8;
    unsigned char *pLine,*pBase;
    unsigned int x,y;
    float widthRatio = 1.0f;
    unsigned int scaledX;
    
    if( FAILED( hr = D3DXCreateTexture( m_pd3dDevice, Width, Height, 1, 0, D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED, &m_pStepTexture ) ) )
    {
        return hr;
    }

    // Adjust Width if D3DXCreateTexture had to pick a different texture 
    // width.  Texture contents will still go up to 4096, though.
    D3DSURFACE_DESC desc;
    m_pStepTexture->GetLevelDesc( 0, &desc );
    if( desc.Width != Width)
    {
        widthRatio = (float)Width / (float)desc.Width;
        Width = desc.Width;
    }

    if( FAILED( hr = m_pStepTexture->LockRect( 0, &Lock, NULL, 0 ) ) )
    {
        m_pStepTexture->Release();
        return hr;
    }

    pBase = (unsigned char *)Lock.pBits;

    for( y = 0; y < Height; y++ )
    {
        pLine = &pBase[y*Lock.Pitch];
        for( x = 0; x < Width; x++ )
        {
            scaledX = (unsigned int)( widthRatio * (float)x );
            pLine[0] =  scaledX & 0xF;  // red, lower 4 bits
            pLine[2] = (scaledX & 0xFF0) >> 4; // blue, upper 8 bits
            pLine[1] = 0; // green
            pLine[3] = 255; // alpha
            pLine += 4;
        }
    }

    m_pStepTexture->UnlockRect(0);
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: LoadXFile()
// Desc: This loads an xfile into the TRIANGLESET structure.  It is not enough 
//       to render an X-File blindly since the the data must be fed into our 
//       vertex shader.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::LoadXFile(TCHAR *pModel,TRIANGLESET *pTriSet)
{
    LPD3DXBUFFER pbufMaterials = NULL;    
    LPD3DXBUFFER pbufAdjacency = NULL;    
    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL;
    LPDIRECT3DINDEXBUFFER9 pIndexBuffer = NULL;
    D3DINDEXBUFFER_DESC IndexDesc;
    DWORD cMaterials;
    void* pSourceI;
    void* pDestI;
    LPD3DXMESH pMeshSysMem = NULL;
    LPD3DXMESH pTempMesh = NULL;
    HRESULT hr;
    FILEVERTEX* pVert;
    FILEVERTEX* pSource;
    DWORD dwGetFVF;
 
    pTriSet->pVertexBuffer = NULL;
    pTriSet->pIndexBuffer  = NULL;
    pVertexBuffer = NULL;

    //load the x file
    if( FAILED( hr = D3DXLoadMeshFromX( pModel, D3DXMESH_SYSTEMMEM, 
        m_pd3dDevice, &pbufAdjacency, &pbufMaterials, NULL, &cMaterials, &pTempMesh ) ) )
    {
        goto FAIL;
    }

    dwGetFVF = pTempMesh->GetFVF();

    // Change it to a mesh that has this vertex format if it is not that way
    if(dwGetFVF != FILEVERTEX::FVF)
    {
        hr = pTempMesh->CloneMeshFVF( 0, FILEVERTEX::FVF, m_pd3dDevice, &pMeshSysMem );
        pTempMesh->Release();
        if( FAILED( hr ) )
            goto FAIL;
    }
    else
    {
        pMeshSysMem = pTempMesh;
    }

    pTriSet->dwNumTriangles = pMeshSysMem->GetNumFaces();
    pTriSet->dwNumVertices  = pMeshSysMem->GetNumVertices();

    // Now copy the vertex buffers and index buffers into new ones that
    // have things set the way we want

    if( FAILED( hr = pMeshSysMem->GetVertexBuffer( &pVertexBuffer ) ) )
        goto FAIL;

    hr = m_pd3dDevice->CreateVertexBuffer( sizeof(FILEVERTEX) * pTriSet->dwNumVertices,
        D3DUSAGE_WRITEONLY, FILEVERTEX::FVF, D3DPOOL_MANAGED, 
        &(pTriSet->pVertexBuffer ), NULL );
    if( FAILED( hr ) )
        goto FAIL;

    hr = pTriSet->pVertexBuffer->Lock( 0, 0, (void**)(&pVert), 0 );
    if( FAILED( hr ) )
        goto FAIL;

    hr = pVertexBuffer->Lock(0, sizeof(FILEVERTEX)*pTriSet->dwNumVertices, (void**)&pSource, 0);
    if( FAILED( hr ) )
        goto FAIL;

    memcpy( pVert, pSource, sizeof(FILEVERTEX) * pTriSet->dwNumVertices );
    
    D3DXComputeBoundingSphere( (D3DXVECTOR3*)pVert, pTriSet->dwNumVertices, D3DXGetFVFVertexSize(FILEVERTEX::FVF), 
        &(pTriSet->Center), &(pTriSet->fRadius) );

    pVertexBuffer->Unlock();
    pTriSet->pVertexBuffer->Unlock();

    if( FAILED( hr = pMeshSysMem->GetIndexBuffer( &pIndexBuffer ) ) )
        goto FAIL;

    pIndexBuffer->GetDesc(&IndexDesc);

    if( FAILED( hr = m_pd3dDevice->CreateIndexBuffer(IndexDesc.Size, D3DUSAGE_WRITEONLY, 
        IndexDesc.Format, D3DPOOL_MANAGED, &(pTriSet->pIndexBuffer), NULL ) ) )
    {
        goto FAIL;
    }

    pIndexBuffer->Lock(0, IndexDesc.Size, &pSourceI, 0);
    pTriSet->pIndexBuffer->Lock(0, IndexDesc.Size, &pDestI, 0);
    memcpy(pDestI, pSourceI, IndexDesc.Size);

    pIndexBuffer->Unlock();
    pTriSet->pIndexBuffer->Unlock();
    
    //cleanup
    SAFE_RELEASE(pbufMaterials);
    SAFE_RELEASE(pbufAdjacency);
    SAFE_RELEASE(pMeshSysMem);
    SAFE_RELEASE(pVertexBuffer);
    SAFE_RELEASE(pIndexBuffer);
        
    return S_OK;

FAIL:
    SAFE_RELEASE(pMeshSysMem);
    SAFE_RELEASE(pVertexBuffer);
    SAFE_RELEASE(pTriSet->pVertexBuffer);
    SAFE_RELEASE(pTriSet->pIndexBuffer);
    SAFE_RELEASE(pIndexBuffer);
    SAFE_RELEASE(pbufMaterials);
    SAFE_RELEASE(pbufAdjacency);
    return hr;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    FLOAT fElapsedTime;

    if( m_fElapsedTime > 0.0f )
        fElapsedTime = m_fElapsedTime;
    else
        fElapsedTime = 0.05f;

    FLOAT fSpeed        = 3.0f*fElapsedTime;
    FLOAT fAngularSpeed = 1.0f*fElapsedTime;

    // De-accelerate the camera movement (for smooth motion)
    m_vVelocity      *= 0.9f;
    m_fYawVelocity   *= 0.9f;
    m_fPitchVelocity *= 0.9f;

    // Process keyboard input
    if( m_bKey[VK_RIGHT] )    m_vVelocity.x    += fSpeed; // Slide Right
    if( m_bKey[VK_LEFT] )     m_vVelocity.x    -= fSpeed; // Slide Left
    if( m_bKey[VK_UP] )       m_vVelocity.y    += fSpeed; // Slide Up
    if( m_bKey[VK_DOWN] )     m_vVelocity.y    -= fSpeed; // Slide Down
    if( m_bKey['W'] )         m_vVelocity.z    += fSpeed; // Move Forward
    if( m_bKey['S'] )         m_vVelocity.z    -= fSpeed; // Move Backward
    if( m_bKey['E'] )         m_fYawVelocity   += fSpeed; // Turn Right
    if( m_bKey['Q'] )         m_fYawVelocity   -= fSpeed; // Turn Left
    if( m_bKey['Z'] )         m_fPitchVelocity += fSpeed; // Turn Down
    if( m_bKey['A'] )         m_fPitchVelocity -= fSpeed; // Turn Up

    // Update the position vector
    D3DXVECTOR3 vT = m_vVelocity * fSpeed;
    D3DXVec3TransformNormal( &vT, &vT, &m_matOrientation );
    m_vPosition += vT;

    // Update the yaw-pitch-rotation vector
    m_fYaw   += fAngularSpeed * m_fYawVelocity;
    m_fPitch += fAngularSpeed * m_fPitchVelocity;

    // Set the view matrix
    D3DXQUATERNION qR;
    D3DXQuaternionRotationYawPitchRoll( &qR, m_fYaw, m_fPitch, 0.0f );
    D3DXMatrixAffineTransformation( &m_matOrientation, 1.25f, NULL, &qR, &m_vPosition );
    D3DXMatrixInverse( &m_matView, NULL, &m_matOrientation );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SetFogMatrices()
// Desc: Sets up the fog matrices, the matrices which represent the fog volume's 
//       position.  These have to be loaded into the right places in the vertex 
//       shader:
//       0-3 = object transformation matrix
//       16-19 = ObjectView
//       8-11 = Total matrix
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::SetFogMatrices()
{
    D3DXMATRIXA16  temp,tObject,m_matTot;
    
    D3DXMatrixMultiply(&m_matTot,  &m_matObject,&m_matView);
    D3DXMatrixTranspose(&temp,&m_matTot);
    m_pd3dDevice->SetVertexShaderConstantF( 16, (float*)&temp, 4 );
  
    D3DXMatrixMultiply(&m_matTot,&m_matTot,&m_matProj);

    D3DXMatrixTranspose(&m_matTot,&m_matTot);
    D3DXMatrixTranspose(&tObject,&m_matObject);

    //these need to be transposes
    m_pd3dDevice->SetVertexShaderConstantF( 0, (float*)&tObject, 4 );
    m_pd3dDevice->SetVertexShaderConstantF( 8, (float*)&m_matTot, 4 );

    //the w clip distance
 
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SetObjMatrices()
// Desc: Sets up the object's matrices, the matrices which represent the object 
//       (or the world) volume's position.  These have to be loaded into the 
//       right places in the vertex shader:
//       0-3 = object transformation matrix
//       16-19 = ObjectView
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::SetObjMatrices()
{
    D3DXMATRIXA16  temp,tObject,m_matTot;
    
    D3DXMatrixTranspose(&tObject,&m_matShadObject);
    m_pd3dDevice->SetVertexShaderConstantF( 0, (float*)&tObject, 4 );

    D3DXMatrixMultiply(&m_matTot, &m_matShadObject,&m_matView);
    D3DXMatrixTranspose(&temp,&m_matTot);
    m_pd3dDevice->SetVertexShaderConstantF( 16, (float*)&temp, 4 );
  
    D3DXMatrixMultiply(&m_matTot,&m_matTot,&m_matProj);

    D3DXMatrixTranspose(&m_matTot,&m_matTot);
    m_pd3dDevice->SetVertexShaderConstantF( 8, (float*)&m_matTot, 4 );

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
    D3DXVECTOR3 lightDir(1,0,0);
    D3DXVECTOR3 sub;
    D3DXVECTOR4 WClip;

    HRESULT hr;
    LPDIRECT3DSURFACE9 pSurface;
    D3DMATERIAL9 Mat;
        
    D3DVIEWPORT9 ViewPort,OldPort;
    VOID* pVerts;
    D3DLIGHT9 myLight;

    //WClip represents our near and far fog 'clipping' (the y index is the inverse of the rear
    //clipping plane)
    //planes. The higher precision one has a further clipping plane 
 
    WClip = D3DXVECTOR4(1,.015f,1,1);
    
    // Compute the current viewport
    // Since we might be on a pure device, we can't query it from the driver
    OldPort.X = 0;
    OldPort.Y = 0;
    OldPort.Width = m_d3dsdBackBuffer.Width;
    OldPort.Height = m_d3dsdBackBuffer.Height;
    OldPort.MaxZ = 1;
    OldPort.MinZ = 0;  

    FLOAT fAspectRatio = (FLOAT)OldPort.Width / (FLOAT) OldPort.Height;

    D3DXMATRIXA16  mat1,mat2;

    // Update projection matrix for a changed aspect ratio
    D3DXMatrixPerspectiveFovLH(&m_matProj, 0.75f, fAspectRatio, 1.0f, 100);

    lightDir = D3DXVECTOR3(2.5f, 2.25f, -2.55f);

    // Set up a set of points which represents the screen
    static struct { FLOAT x,y,z,w; DWORD color; FLOAT u,v; } s_Verts[] =
    {
        {1.0f,   1.0f, 0.5f, 1.0f , D3DCOLOR_XRGB( 0xff, 0xff, 0x8f ), 1,0 },
        {1.0f, -1.0f, 0.5f, 1.0f, D3DCOLOR_XRGB( 0xff, 0xff, 0x8f),  1,1},
        { -1.0f, 1.0f, 0.5f, 1.0f,   D3DCOLOR_XRGB( 0xff, 0xff, 0x8f),  0,0},
        { -1.0f,  -1.0f, 0.5f, 1.0f,  D3DCOLOR_XRGB( 0xff, 0xff, 0x8f),  0,1},
    };
     
    if( FAILED( hr = m_pScreenVertBuf->Lock( 0, sizeof(s_Verts), (void**)(&pVerts), 0 ) ) )
        goto FAIL;
    
    memcpy( (void*)pVerts, (void*)s_Verts, sizeof(s_Verts) );
    
    if( FAILED( hr = m_pScreenVertBuf->Unlock() ) )
        goto FAIL;

    //set the fog clipping into the vertex shader's constant register #12
    m_pd3dDevice->SetVertexShaderConstantF( 12, (float*)&WClip, 1 );
    
    m_pd3dDevice->BeginScene();

    //now we render the first half of the fog scene - or rather, the back side of the 
    //fog. what will be left in the buffer after we are done is the w depth of the 
    //back fog volume 

    ViewPort.X = 0;
    ViewPort.Y = 0;
    ViewPort.Height = RENDERTARGSIZE;
    ViewPort.Width =  RENDERTARGSIZE;
    ViewPort.MaxZ = 1;
    ViewPort.MinZ = 0;
     
    if( FAILED( hr = m_pScreenVertBuf2->Lock( 0, sizeof(s_Verts), (void**)(&pVerts), 0 ) ) )
        goto FAIL;
    
    memcpy( (void*)pVerts, (void*)s_Verts, sizeof(s_Verts) );
    
    if (FAILED(hr = m_pScreenVertBuf2->Unlock()) )
        goto FAIL;

    m_pd3dDevice->SetTexture(0,NULL);
    m_pd3dDevice->SetTexture(1,NULL);
    m_pd3dDevice->SetTexture(2,NULL);
    m_pd3dDevice->SetTexture(3,NULL);

    m_pd3dDevice->SetPixelShader(0);
        
    //we will just use a special vertex shader to fill the color and alpha as our w depth using the
    //step texture
    m_pd3dDevice->SetRenderState(D3DRS_WRAP0, 0 );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
    m_pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR,0x01010101);

    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );

   //use our step texture to get higher precision interpolating
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
        
    m_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    m_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
    
    m_pd3dDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
    m_pd3dDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);

    m_pd3dDevice->SetTexture(0,m_pStepTexture);
    m_pd3dDevice->SetTexture(1,NULL);
      
    //set up transform matrices for the fixed pipe.
    //this is only used for the rendering of the object
    m_pd3dDevice->SetTransform(D3DTS_VIEW,&m_matView);
    m_pd3dDevice->SetTransform(D3DTS_PROJECTION,&m_matProj );
    m_pd3dDevice->SetTransform(D3DTS_WORLD,&m_matObject);

    //Now we need to draw the scene, happens first to also set the Z 
    hr =  m_pSceneDist->GetSurfaceLevel(0, &pSurface);
    
    //first, render the scene with the depth encoding
    hr =  m_pd3dDevice->SetRenderTarget( 0, pSurface );
    hr =  m_pd3dDevice->SetDepthStencilSurface( m_pTargetZ );
    m_pd3dDevice->SetViewport(&ViewPort);
    hr =  m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
                                 D3DCOLOR_ARGB( 0x00, 0x00, 0x00, 0x00), 1.0,0);
 
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); 

    SetObjMatrices();
    m_pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, 0x00000000);
    m_pd3dDevice->SetIndices(m_MeshShaderObject.pIndexBuffer);
    m_pd3dDevice->SetStreamSource( 0,m_MeshShaderObject.pVertexBuffer, 0, sizeof(FILEVERTEX) );
    m_pd3dDevice->SetVertexDeclaration( m_pFogDeclaration );
    m_pd3dDevice->SetVertexShader( m_pFogShader );

    //no alpha blending since geometry is opaque
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);  
    hr = m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
        m_MeshShaderObject.dwNumVertices, 0, m_MeshShaderObject.dwNumTriangles);

    //Now Render the back side of the fog, the
    //z buffer is the same as the one set by the geometry
    //since elements of the fog behind the scene should not be rendered (since they are not visible)
    pSurface->Release();
    hr = m_pBackFogDist->GetSurfaceLevel(0,&pSurface);
    hr = m_pd3dDevice->SetRenderTarget( 0, pSurface );
    hr = m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 0x00, 0x00, 0x00, 0x00), 1.0,0);
    
    SetFogMatrices();
 
    //reverse the culling order to get the back side
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    
    //add up all the backsides, this is volumetric rendering so 
    //everything is totally transparent, want to check Z Buffer,
    //but not write to it.
    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);   
    m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE); 
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

    //the tfactor adds in the alpha so that we can keep track of the number
    //of times a pixel is in and out of a fog
    m_pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, 0x10101010);
    m_pd3dDevice->SetIndices(m_FogVolume.pIndexBuffer);
    m_pd3dDevice->SetStreamSource( 0, m_FogVolume.pVertexBuffer, 0, sizeof(FILEVERTEX) );
    m_pd3dDevice->SetVertexDeclaration( m_pFogDeclaration );
    m_pd3dDevice->SetVertexShader( m_pFogShader );
    hr = m_pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 
        m_FogVolume.dwNumVertices, 0, m_FogVolume.dwNumTriangles );
    pSurface->Release();

    //Now we need to draw the front end of the fog
    //same concept as above, but this time the front halves of the 
    //fog get drawn
    hr =  m_pFrontFogDist->GetSurfaceLevel(0, &pSurface);
    hr =  m_pd3dDevice->SetRenderTarget( 0, pSurface );
    m_pd3dDevice->SetViewport(&ViewPort);
    hr =  m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET  ,
                                 D3DCOLOR_ARGB( 0x00, 0x00, 0x00, 0x00), 1.0,0);

    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);   
    m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE,FALSE);  
    m_pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, 0x10101010);
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//DESTALPHA);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); 

    SetFogMatrices();
    m_pd3dDevice->SetIndices(m_FogVolume.pIndexBuffer);
    m_pd3dDevice->SetStreamSource( 0, m_FogVolume.pVertexBuffer, 0, sizeof(FILEVERTEX) );
    m_pd3dDevice->SetVertexDeclaration( m_pFogDeclaration );
    m_pd3dDevice->SetVertexShader( m_pFogShader );
    hr = m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
        m_FogVolume.dwNumVertices, 0, m_FogVolume.dwNumTriangles);
    pSurface->Release();

    //first we render the object, or whatever solid objects
    //we have in the scene. This will act as the back side of our
    //fog if it happens to be in the fog volume
 
    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);   
    m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE);  
   
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    //now we are ready to actually draw the scene
    m_pd3dDevice->SetRenderTarget( 0, m_pOldRenderTarget );
    m_pd3dDevice->SetDepthStencilSurface( m_pOldStencilZ );
    m_pd3dDevice->SetViewport(&OldPort);

    hr =  m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
                                  D3DCOLOR_ARGB( 0x00, 0x00, 0x00, 0x00), 1.0,0);

    //first draw the scene as it is.
    m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);
    m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_matProj );
    m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_matShadObject);
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
   
    memset(&Mat,0,sizeof(Mat));

    //generic light and generic scene.
    myLight.Type = D3DLIGHT_DIRECTIONAL;
    myLight.Diffuse.r = 0;
    myLight.Diffuse.g = 1;
    myLight.Diffuse.b = 0;
    myLight.Diffuse.a = 1;
    myLight.Range     = 1000000;
    myLight.Direction = D3DXVECTOR3(1,1,1);
    
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

    m_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
    m_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
    
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
    m_pd3dDevice->LightEnable(0, TRUE);

    m_pd3dDevice->SetLight(0, &myLight);
    
    Mat.Diffuse.r = 1;
    Mat.Diffuse.b = 1;
    Mat.Diffuse.g = 1;
    Mat.Diffuse.a = 1;

    m_pd3dDevice->SetMaterial(&Mat);
    
    m_pd3dDevice->SetTexture(0, NULL);
    m_pd3dDevice->SetTexture(1, NULL);

    D3DVERTEXBUFFER_DESC vDesc;
    m_MeshShaderObject.pVertexBuffer->GetDesc(&vDesc);
    m_pd3dDevice->SetStreamSource( 0,m_MeshShaderObject.pVertexBuffer, 0, sizeof(FILEVERTEX) );
    m_pd3dDevice->SetIndices(m_MeshShaderObject.pIndexBuffer);
    m_pd3dDevice->SetFVF( FILEVERTEX::FVF );
    m_pd3dDevice->SetVertexShader( NULL );
    hr = m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
        m_MeshShaderObject.dwNumVertices, 0, m_MeshShaderObject.dwNumTriangles);

    m_pd3dDevice->SetTexture(0, NULL);
    m_pd3dDevice->SetTexture(1, NULL);
    m_pd3dDevice->SetTexture(2, NULL);
    m_pd3dDevice->SetTexture(3, NULL);

    //draw the fog
    //this uses a complex pixel shader which is fully commented
    //this computes the amount of fog at every pixel on the screen

    m_pd3dDevice->SetRenderTarget( 0, m_pOldRenderTarget );
    m_pd3dDevice->SetDepthStencilSurface( m_pOldStencilZ );
    m_pd3dDevice->SetViewport(&OldPort);

    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); 
  
    m_pd3dDevice->SetRenderState(D3DRS_WRAP0, 0);
    m_pd3dDevice->SetRenderState(D3DRS_WRAP1, 0);
    m_pd3dDevice->SetRenderState(D3DRS_WRAP2, 0);

    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);

    m_pd3dDevice->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_POINT );
    m_pd3dDevice->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
    m_pd3dDevice->SetSamplerState( 1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
    m_pd3dDevice->SetSamplerState( 1, D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
    m_pd3dDevice->SetSamplerState( 1, D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);

    m_pd3dDevice->SetSamplerState( 2, D3DSAMP_MINFILTER, D3DTEXF_POINT );
    m_pd3dDevice->SetSamplerState( 2, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
    m_pd3dDevice->SetSamplerState( 2, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
    m_pd3dDevice->SetSamplerState( 2, D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
    m_pd3dDevice->SetSamplerState( 2, D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);

    m_pd3dDevice->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 0 );
    m_pd3dDevice->SetTextureStageState( 2, D3DTSS_TEXCOORDINDEX, 0 );
    
    m_pd3dDevice->SetPixelShader( m_pSubPicShader );
    m_pd3dDevice->SetTexture(0,m_pFrontFogDist);
    m_pd3dDevice->SetTexture(1,m_pBackFogDist);
    m_pd3dDevice->SetTexture(2,m_pSceneDist);
    
    //alpha blend on. If we want to do volumetric light, we use an additive rather
    //then blended mode
    m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);   
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);


    m_pd3dDevice->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 1 );
    m_pd3dDevice->SetTextureStageState( 2, D3DTSS_TEXCOORDINDEX, 2 );

    //simple vertex shader, just copies coordinates and stuff.
    m_pd3dDevice->SetVertexDeclaration( m_pFogDeclaration2 );
    m_pd3dDevice->SetVertexShader( m_pFogShader2 );
    m_pd3dDevice->SetStreamSource( 0, m_pScreenVertBuf, 0, 7 * sizeof(FLOAT) );
    m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

    m_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);   

    // Output statistics
    m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
    m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );
    
    // Draw help
    if( m_bDrawHelp )
    {
        m_pFontSmall->DrawText( 2, 40, 0xffffff00,
                                _T("Keyboard controls:") );
        m_pFontSmall->DrawText( 20, 60, 0xffffff00,
                                _T("Move\nTurn\nPitch\nSlide\n\nHelp\n"
                                   "Change device\n"
                                   "Exit") );
        m_pFontSmall->DrawText( 160, 60, 0xffffff00,
                                _T("W,S\nE,Q\nA,Z\nArrow keys\n\n"
                                   "F1\nF2\nEsc") );
    }
    else
    {
        m_pFontSmall->DrawText( 2, 40, 0xffffff00, _T("Press F1 for help") );
    }

    m_pd3dDevice->EndScene();

    return S_OK;

FAIL:
    return hr;
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    TCHAR model[160];
    TCHAR model2[160];
    HRESULT hr;

    m_pFont->InitDeviceObjects( m_pd3dDevice );
    m_pFontSmall->InitDeviceObjects( m_pd3dDevice );

    if( FAILED( hr = DXUtil_FindMediaFileCb( model, sizeof(model), _T("fog2.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;
    if( FAILED( hr = DXUtil_FindMediaFileCb( model2, sizeof(model2), _T("room2.x") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;
  
    if( D3DSHADER_VERSION_MAJOR( m_d3dCaps.PixelShaderVersion ) >= 1 )
        m_bUsePicShader = TRUE;
    else
        m_bUsePicShader = FALSE;

    if( FAILED( hr = LoadXFile( model, &m_FogVolume ) ) )
        return hr;

    if( FAILED( hr = LoadXFile( model2, &m_MeshShaderObject ) ) )
        return hr;

    if( FAILED( hr = D3DXLoadMeshFromX( model2, D3DXMESH_SYSTEMMEM, m_pd3dDevice, 
        NULL, NULL, NULL, NULL, &m_pMeshObject ) ) )
    {
        return hr;
    }

    if( FAILED( hr = m_pd3dDevice->CreateVertexBuffer( 7 * sizeof(FLOAT) * 4, 0,
        D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE, D3DPOOL_MANAGED, &m_pScreenVertBuf, NULL ) ) )
    {
        return hr;
    }
    
    if( FAILED( hr = m_pd3dDevice->CreateVertexBuffer( 7 * sizeof(FLOAT) * 4, 0,
        D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE, D3DPOOL_MANAGED, &m_pScreenVertBuf2, NULL ) ) )
    {
        return hr;
    }

    if( FAILED( hr = ComputeStepTexture() ) )
        return hr;

    D3DVERTEXELEMENT9 decl[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
        D3DDECL_END()
    };

    if( FAILED( hr = m_pd3dDevice->CreateVertexDeclaration( decl, &m_pFogDeclaration ) ) )
        return hr;

    D3DVERTEXELEMENT9 decl2[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        { 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
        { 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
        D3DDECL_END()
    };

    if( FAILED( hr = m_pd3dDevice->CreateVertexDeclaration( decl2, &m_pFogDeclaration2 ) ) )
        return hr;

    TCHAR strPath[MAX_PATH];
    LPD3DXBUFFER pCodeShader;

    if( FAILED( hr = DXUtil_FindMediaFileCb( strPath, sizeof(strPath), _T("fogshader.vsh") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;
    if( FAILED( hr = D3DXAssembleShaderFromFile(strPath, NULL, NULL, 0, &pCodeShader, NULL ) ) )
        return hr;
    SAFE_RELEASE( m_pFogShader );
    if (FAILED( hr = m_pd3dDevice->CreateVertexShader( (DWORD*)pCodeShader->GetBufferPointer(), &m_pFogShader ) ) )
        return hr;
    SAFE_RELEASE( pCodeShader );
    
    if( FAILED( hr = DXUtil_FindMediaFileCb( strPath, sizeof(strPath), _T("fogshader2.vsh") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;
    if( FAILED( hr = D3DXAssembleShaderFromFile(strPath, NULL, NULL, 0, &pCodeShader, NULL ) ) )
        return hr;
    SAFE_RELEASE( m_pFogShader2 );
    if (FAILED( hr = m_pd3dDevice->CreateVertexShader( (DWORD*)pCodeShader->GetBufferPointer(), &m_pFogShader2 ) ) )
        return hr;
    SAFE_RELEASE( pCodeShader );
  
    if( FAILED( hr = DXUtil_FindMediaFileCb( strPath, sizeof(strPath), _T("FogPixShader.psh") ) ) )
        return D3DAPPERR_MEDIANOTFOUND;
    if( FAILED( hr = D3DXAssembleShaderFromFile(strPath, NULL, NULL, 0, &pCodeShader, NULL ) ) )
        return hr;
    SAFE_RELEASE( m_pSubPicShader );
    if (FAILED( hr = m_pd3dDevice->CreatePixelShader( (DWORD*)pCodeShader->GetBufferPointer(), &m_pSubPicShader ) ) )
        return hr;
    SAFE_RELEASE( pCodeShader );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    HRESULT hr;
    
    m_pFont->RestoreDeviceObjects();
    m_pFontSmall->RestoreDeviceObjects();

    if( FAILED( hr = m_pd3dDevice->CreateTexture( RENDERTARGSIZE, RENDERTARGSIZE, 0,
        D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pBackFogDist, NULL ) ) )
    {
        return hr;
    }

    if( FAILED( hr = m_pd3dDevice->CreateTexture( RENDERTARGSIZE, RENDERTARGSIZE, 0,
        D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pFrontFogDist, NULL ) ) )
    {
        return hr;
    }

    if( FAILED( hr = m_pd3dDevice->CreateTexture( RENDERTARGSIZE, RENDERTARGSIZE, 0,
        D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pSceneDist, NULL ) ) )
    {
        return hr;
    }

    if( FAILED( hr = m_pd3dDevice->CreateTexture( RENDERTARGSIZE, RENDERTARGSIZE, 0,
        D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTempDist, NULL ) ) )
    {
        return hr;
    }

    if( FAILED( hr = m_pd3dDevice->CreateDepthStencilSurface( RENDERTARGSIZE,RENDERTARGSIZE,
        D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pTargetZ, NULL ) ) )
    {
        return hr;
    }

    if( FAILED( hr = m_pd3dDevice->GetRenderTarget( 0, &m_pOldRenderTarget ) ) )
        return hr;

    if( FAILED( hr = m_pd3dDevice->GetDepthStencilSurface( &m_pOldStencilZ ) ) )
        return hr;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();
    m_pFontSmall->InvalidateDeviceObjects();

    SAFE_RELEASE(m_pOldRenderTarget);
    SAFE_RELEASE(m_pOldStencilZ);
    SAFE_RELEASE(m_pFrontFogDist);
    SAFE_RELEASE(m_pBackFogDist);
    SAFE_RELEASE(m_pSceneDist);
    SAFE_RELEASE(m_pTempDist);
    SAFE_RELEASE(m_pTargetZ);
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
    SAFE_RELEASE(m_pScreenVertBuf);
    SAFE_RELEASE(m_pScreenVertBuf2);
    SAFE_RELEASE(m_FogVolume.pVertexBuffer);
    SAFE_RELEASE(m_FogVolume.pIndexBuffer);
    SAFE_RELEASE(m_MeshShaderObject.pVertexBuffer);
    SAFE_RELEASE(m_MeshShaderObject.pIndexBuffer);
    SAFE_RELEASE(m_pMeshObject);
    SAFE_RELEASE(m_pStepTexture);
    SAFE_RELEASE(m_pSubPicShader);
    SAFE_RELEASE(m_pFogDeclaration);
    SAFE_RELEASE(m_pFogShader);
    SAFE_RELEASE(m_pFogDeclaration2);
    SAFE_RELEASE(m_pFogShader2);

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
