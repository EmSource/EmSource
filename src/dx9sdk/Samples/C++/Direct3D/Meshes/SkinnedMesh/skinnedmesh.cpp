//-----------------------------------------------------------------------------
// File: SkinnedMesh.cpp
//
// Desc: Sample showing skinned meshes in D3D
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <commdlg.h>
#include <tchar.h>
#include <stdio.h>
#include <d3dx9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DApp.h"
#include "D3DFont.h"
#include "D3DUtil.h"
#include "resource.h"


// enum for various skinning modes possible
enum METHOD 
{
    D3DNONINDEXED,
    D3DINDEXED,
    SOFTWARE,
    D3DINDEXEDVS,
    D3DINDEXEDHLSLVS,
    NONE
};




//-----------------------------------------------------------------------------
// Name: struct D3DXFRAME_DERIVED
// Desc: Structure derived from D3DXFRAME so we can add some app-specific
//       info that will be stored with each frame
//-----------------------------------------------------------------------------
struct D3DXFRAME_DERIVED: public D3DXFRAME
{
    D3DXMATRIXA16        CombinedTransformationMatrix;
};




//-----------------------------------------------------------------------------
// Name: struct D3DXMESHCONTAINER_DERIVED
// Desc: Structure derived from D3DXMESHCONTAINER so we can add some app-specific
//       info that will be stored with each mesh
//-----------------------------------------------------------------------------
struct D3DXMESHCONTAINER_DERIVED: public D3DXMESHCONTAINER
{
    LPDIRECT3DTEXTURE9*  ppTextures;       // array of textures, entries are NULL if no texture specified    
                                
    // SkinMesh info             
    LPD3DXMESH           pOrigMesh;
    LPD3DXATTRIBUTERANGE pAttributeTable;
    DWORD                NumAttributeGroups; 
    DWORD                NumInfl;
    LPD3DXBUFFER         pBoneCombinationBuf;
    D3DXMATRIX**         ppBoneMatrixPtrs;
    D3DXMATRIX*          pBoneOffsetMatrices;
    DWORD                NumPaletteEntries;
    bool                 UseSoftwareVP;
    DWORD                iAttributeSW;     // used to denote the split between SW and HW if necessary for non-indexed skinning
};




class CMyD3DApplication;

//-----------------------------------------------------------------------------
// Name: class CAllocateHierarchy
// Desc: Custom version of ID3DXAllocateHierarchy with custom methods to create
//       frames and meshcontainers.
//-----------------------------------------------------------------------------
class CAllocateHierarchy: public ID3DXAllocateHierarchy
{
public:
    STDMETHOD(CreateFrame)(THIS_ LPCTSTR Name, LPD3DXFRAME *ppNewFrame);
    STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR Name, LPD3DXMESHDATA pMeshData,
                            LPD3DXMATERIAL pMaterials, LPD3DXEFFECTINSTANCE pEffectInstances, DWORD NumMaterials, 
                            DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, 
                            LPD3DXMESHCONTAINER *ppNewMeshContainer);
    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);
    CAllocateHierarchy(CMyD3DApplication *pApp) :m_pApp(pApp) {}

public:
    CMyD3DApplication* m_pApp;
};




//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
    TCHAR                       m_strMeshFilename[MAX_PATH];
    TCHAR                       m_strInitialDir[MAX_PATH];
                                
    LPD3DXFRAME                 m_pFrameRoot;
    LPD3DXANIMATIONCONTROLLER   m_pAnimController;

    CD3DFont*                   m_pFont;
    CD3DFont*                   m_pFontSmall;
    CD3DArcBall                 m_ArcBall;          // mouse rotation utility
    D3DXVECTOR3                 m_vObjectCenter;    // Center of bounding sphere of object
    FLOAT                       m_fObjectRadius;    // Radius of bounding sphere of object

    METHOD                      m_SkinningMethod;   // Current skinning method
    D3DXMATRIXA16*              m_pBoneMatrices;
    UINT                        m_NumBoneMatricesMax;

    LPDIRECT3DVERTEXSHADER9     m_pIndexedVertexShader[4];
    LPD3DXEFFECT                m_pEffect;
    D3DXMATRIXA16               m_matView;

protected:
    HRESULT OneTimeSceneInit();
    HRESULT InitDeviceObjects();
    HRESULT ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior, 
		D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat );
    HRESULT RestoreDeviceObjects();
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();
    HRESULT Render();
    HRESULT FrameMove();
    HRESULT FinalCleanup();
    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    void DrawMeshContainer( LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase );
    void DrawFrame( LPD3DXFRAME pFrame );

    HRESULT SetupBoneMatrixPointersOnMesh( LPD3DXMESHCONTAINER pMeshContainer );
    HRESULT SetupBoneMatrixPointers( LPD3DXFRAME pFrame );
    void UpdateFrameMatrices( LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix );
    void UpdateSkinningMethod( LPD3DXFRAME pFrameBase );

public:
    CMyD3DApplication();

    HRESULT GenerateSkinnedMesh( D3DXMESHCONTAINER_DERIVED *pMeshContainer );
};




//-----------------------------------------------------------------------------
// Name: AllocateName()
// Desc: Allocates memory for a string to hold the name of a frame or mesh
//-----------------------------------------------------------------------------
HRESULT AllocateName( LPCTSTR Name, LPTSTR *pNewName )
{
    UINT cbLength;

    if (Name != NULL)
    {
        cbLength = lstrlen(Name) + 1;
        *pNewName = new TCHAR[cbLength];
        if (*pNewName == NULL)
            return E_OUTOFMEMORY;
        memcpy(*pNewName, Name, cbLength*sizeof(TCHAR));
    }
    else
    {
        *pNewName = NULL;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::CreateFrame()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateFrame(LPCTSTR Name, LPD3DXFRAME *ppNewFrame)
{
    HRESULT hr = S_OK;
    D3DXFRAME_DERIVED *pFrame;

    *ppNewFrame = NULL;

    pFrame = new D3DXFRAME_DERIVED;
    if (pFrame == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto e_Exit;
    }

    hr = AllocateName(Name, &pFrame->Name);
    if (FAILED(hr))
        goto e_Exit;

    // initialize other data members of the frame
    D3DXMatrixIdentity(&pFrame->TransformationMatrix);
    D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

    pFrame->pMeshContainer = NULL;
    pFrame->pFrameSibling = NULL;
    pFrame->pFrameFirstChild = NULL;

    *ppNewFrame = pFrame;
    pFrame = NULL;
e_Exit:
    delete pFrame;
    return hr;
}




//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::CreateMeshContainer()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateMeshContainer(LPCTSTR Name, LPD3DXMESHDATA pMeshData,
                            LPD3DXMATERIAL pMaterials, LPD3DXEFFECTINSTANCE pEffectInstances, DWORD NumMaterials, 
                            DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, 
                            LPD3DXMESHCONTAINER *ppNewMeshContainer) 
{
    HRESULT hr;
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;
    UINT NumFaces;
    UINT iMaterial;
    UINT iBone, cBones;
    LPDIRECT3DDEVICE9 pd3dDevice = NULL;

    LPD3DXMESH pMesh = NULL;

    *ppNewMeshContainer = NULL;

    // this sample does not handle patch meshes, so fail when one is found
    if (pMeshData->Type != D3DXMESHTYPE_MESH)
    {
        hr = E_FAIL;
        goto e_Exit;
    }

    // get the pMesh interface pointer out of the mesh data structure
    pMesh = pMeshData->pMesh;

    // this sample does not FVF compatible meshes, so fail when one is found
    if (pMesh->GetFVF() == 0)
    {
        hr = E_FAIL;
        goto e_Exit;
    }

    // allocate the overloaded structure to return as a D3DXMESHCONTAINER
    pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
    if (pMeshContainer == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto e_Exit;
    }
    memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

    // make sure and copy the name.  All memory as input belongs to caller, interfaces can be addref'd though
    hr = AllocateName(Name, &pMeshContainer->Name);
    if (FAILED(hr))
        goto e_Exit;        

    pMesh->GetDevice(&pd3dDevice);
    NumFaces = pMesh->GetNumFaces();

    // if no normals are in the mesh, add them
    if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
    {
        pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

        // clone the mesh to make room for the normals
        hr = pMesh->CloneMeshFVF( pMesh->GetOptions(), 
                                    pMesh->GetFVF() | D3DFVF_NORMAL, 
                                    pd3dDevice, &pMeshContainer->MeshData.pMesh );
        if (FAILED(hr))
            goto e_Exit;

        // get the new pMesh pointer back out of the mesh container to use
        // NOTE: we do not release pMesh because we do not have a reference to it yet
        pMesh = pMeshContainer->MeshData.pMesh;

        // now generate the normals for the pmesh
        D3DXComputeNormals( pMesh, NULL );
    }
    else  // if no normals, just add a reference to the mesh for the mesh container
    {
        pMeshContainer->MeshData.pMesh = pMesh;
        pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

        pMesh->AddRef();
    }
        
    // allocate memory to contain the material information.  This sample uses
    //   the D3D9 materials and texture names instead of the EffectInstance style materials
    pMeshContainer->NumMaterials = max(1, NumMaterials);
    pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
    pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
    pMeshContainer->pAdjacency = new DWORD[NumFaces*3];
    if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
    {
        hr = E_OUTOFMEMORY;
        goto e_Exit;
    }

    memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces*3);
    memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

    // if materials provided, copy them
    if (NumMaterials > 0)            
    {
        memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

        for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
        {
            if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
            {
                TCHAR strTexturePath[MAX_PATH] = _T("");
                DXUtil_FindMediaFileCb( strTexturePath, sizeof(strTexturePath), pMeshContainer->pMaterials[iMaterial].pTextureFilename );
                if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, strTexturePath, 
                                                        &pMeshContainer->ppTextures[iMaterial] ) ) )
                    pMeshContainer->ppTextures[iMaterial] = NULL;


                // don't remember a pointer into the dynamic memory, just forget the name after loading
                pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
            }
        }
    }
    else // if no materials provided, use a default one
    {
        pMeshContainer->pMaterials[0].pTextureFilename = NULL;
        memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
        pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
    }

    // if there is skinning information, save off the required data and then setup for HW skinning
    if (pSkinInfo != NULL)
    {
        // first save off the SkinInfo and original mesh data
        pMeshContainer->pSkinInfo = pSkinInfo;
        pSkinInfo->AddRef();

        pMeshContainer->pOrigMesh = pMesh;
        pMesh->AddRef();

        // Will need an array of offset matrices to move the vertices from the figure space to the bone's space
        cBones = pSkinInfo->GetNumBones();
        pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];
        if (pMeshContainer->pBoneOffsetMatrices == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto e_Exit;
        }

        // get each of the bone offset matrices so that we don't need to get them later
        for (iBone = 0; iBone < cBones; iBone++)
        {
            pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
        }

        // GenerateSkinnedMesh will take the general skinning information and transform it to a HW friendly version
        hr = m_pApp->GenerateSkinnedMesh(pMeshContainer);
        if (FAILED(hr))
            goto e_Exit;
    }

    *ppNewMeshContainer = pMeshContainer;
    pMeshContainer = NULL;
e_Exit:
    SAFE_RELEASE(pd3dDevice);

    // call Destroy function to properly clean up the memory allocated 
    if (pMeshContainer != NULL)
    {
        DestroyMeshContainer(pMeshContainer);
    }

    return hr;
}




//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::DestroyFrame()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree) 
{
    SAFE_DELETE_ARRAY( pFrameToFree->Name );
    SAFE_DELETE( pFrameToFree );
    return S_OK; 
}




//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::DestroyMeshContainer()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
    UINT iMaterial;
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

    SAFE_DELETE_ARRAY( pMeshContainer->Name );
    SAFE_DELETE_ARRAY( pMeshContainer->pAdjacency );
    SAFE_DELETE_ARRAY( pMeshContainer->pMaterials );
    SAFE_DELETE_ARRAY( pMeshContainer->pBoneOffsetMatrices );

    // release all the allocated textures
    if (pMeshContainer->ppTextures != NULL)
    {
        for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
        {
            SAFE_RELEASE( pMeshContainer->ppTextures[iMaterial] );
        }
    }

    SAFE_DELETE_ARRAY( pMeshContainer->ppTextures );
    SAFE_DELETE_ARRAY( pMeshContainer->ppBoneMatrixPtrs );
    SAFE_RELEASE( pMeshContainer->pBoneCombinationBuf );
    SAFE_RELEASE( pMeshContainer->MeshData.pMesh );
    SAFE_RELEASE( pMeshContainer->pSkinInfo );
    SAFE_RELEASE( pMeshContainer->pOrigMesh );
    SAFE_DELETE( pMeshContainer );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything, and goes into a
//       message-processing loop. Idle time is used to render the scene.
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    CMyD3DApplication d3dApp;

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
    m_strWindowTitle    = _T("Skinned Mesh");
    m_d3dEnumeration.AppUsesDepthBuffer   = TRUE;
    m_d3dEnumeration.AppUsesMixedVP = TRUE;
    m_bShowCursorWhenFullscreen = TRUE;

    m_pFont         = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_pFontSmall    = new CD3DFont( _T("Arial"),  9, D3DFONT_BOLD );

    m_pAnimController = NULL;
    m_pFrameRoot = NULL;

    DXUtil_GetDXSDKMediaPathCb( m_strInitialDir, sizeof(m_strInitialDir) );
    _tcscpy( m_strMeshFilename, _T("tiny.x") );

    m_SkinningMethod = D3DNONINDEXED;
    m_pBoneMatrices = NULL;
    m_NumBoneMatricesMax = 0;
}




//-----------------------------------------------------------------------------
// Name: GenerateSkinnedMesh()
// Desc: Called either by CreateMeshContainer when loading a skin mesh, or when 
//       changing methods.  This function uses the pSkinInfo of the mesh 
//       container to generate the desired drawable mesh and bone combination 
//       table.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::GenerateSkinnedMesh(D3DXMESHCONTAINER_DERIVED *pMeshContainer)
{
    HRESULT hr = S_OK;

    if (pMeshContainer->pSkinInfo == NULL)
        return hr;

    SAFE_RELEASE( pMeshContainer->MeshData.pMesh );
    SAFE_RELEASE( pMeshContainer->pBoneCombinationBuf );

    // if non-indexed skinning mode selected, use ConvertToBlendedMesh to generate drawable mesh
    if (m_SkinningMethod == D3DNONINDEXED)
    {

        hr = pMeshContainer->pSkinInfo->ConvertToBlendedMesh
                                   (
                                       pMeshContainer->pOrigMesh,
                                       D3DXMESH_MANAGED|D3DXMESHOPT_VERTEXCACHE, 
                                       pMeshContainer->pAdjacency, 
                                       NULL, NULL, NULL, 
                                       &pMeshContainer->NumInfl,
                                       &pMeshContainer->NumAttributeGroups, 
                                       &pMeshContainer->pBoneCombinationBuf, 
                                       &pMeshContainer->MeshData.pMesh
                                   );
        if (FAILED(hr))
            goto e_Exit;


        /* If the device can only do 2 matrix blends, ConvertToBlendedMesh cannot approximate all meshes to it
           Thus we split the mesh in two parts: The part that uses at most 2 matrices and the rest. The first is
           drawn using the device's HW vertex processing and the rest is drawn using SW vertex processing. */
        LPD3DXBONECOMBINATION rgBoneCombinations  = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

        // look for any set of bone combinations that do not fit the caps
        for (pMeshContainer->iAttributeSW = 0; pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups; pMeshContainer->iAttributeSW++)
        {
            DWORD cInfl   = 0;

            for (DWORD iInfl = 0; iInfl < pMeshContainer->NumInfl; iInfl++)
            {
                if (rgBoneCombinations[pMeshContainer->iAttributeSW].BoneId[iInfl] != UINT_MAX)
                {
                    ++cInfl;
                }
            }

            if (cInfl > m_d3dCaps.MaxVertexBlendMatrices)
            {
                break;
            }
        }

        // if there is both HW and SW, add the Software Processing flag
        if (pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups)
        {
            LPD3DXMESH pMeshTmp;

            hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(D3DXMESH_SOFTWAREPROCESSING|pMeshContainer->MeshData.pMesh->GetOptions(), 
                                                pMeshContainer->MeshData.pMesh->GetFVF(),
                                                m_pd3dDevice, &pMeshTmp);
            if (FAILED(hr))
            {
                goto e_Exit;
            }

            pMeshContainer->MeshData.pMesh->Release();
            pMeshContainer->MeshData.pMesh = pMeshTmp;
            pMeshTmp = NULL;
        }
    }
    // if indexed skinning mode selected, use ConvertToIndexedsBlendedMesh to generate drawable mesh
    else if (m_SkinningMethod == D3DINDEXED)
    {
        DWORD NumMaxFaceInfl;
        DWORD Flags = D3DXMESHOPT_VERTEXCACHE;

        LPDIRECT3DINDEXBUFFER9 pIB;
        hr = pMeshContainer->pOrigMesh->GetIndexBuffer(&pIB);
        if (FAILED(hr))
            goto e_Exit;

        hr = pMeshContainer->pSkinInfo->GetMaxFaceInfluences(pIB, pMeshContainer->pOrigMesh->GetNumFaces(), &NumMaxFaceInfl);
        pIB->Release();
        if (FAILED(hr))
            goto e_Exit;

        // 12 entry palette guarantees that any triangle (4 independent influences per vertex of a tri)
        // can be handled
        NumMaxFaceInfl = min(NumMaxFaceInfl, 12);

        if (m_d3dCaps.MaxVertexBlendMatrixIndex + 1 < NumMaxFaceInfl)
        {
            // HW does not support indexed vertex blending. Use SW instead
            pMeshContainer->NumPaletteEntries = min(256, pMeshContainer->pSkinInfo->GetNumBones());
            pMeshContainer->UseSoftwareVP = true;
            Flags |= D3DXMESH_SYSTEMMEM;
        }
        else
        {
            // using hardware - determine palette size from caps and number of bones
            // If normals are present in the vertex data that needs to be blended for lighting, then 
            // the number of matrices is half the number specified by MaxVertexBlendMatrixIndex.
            pMeshContainer->NumPaletteEntries = min( ( m_d3dCaps.MaxVertexBlendMatrixIndex + 1 ) / 2, 
                                                     pMeshContainer->pSkinInfo->GetNumBones() );
            pMeshContainer->UseSoftwareVP = false;
            Flags |= D3DXMESH_MANAGED;
        }

        hr = pMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh
                                                (
                                                pMeshContainer->pOrigMesh,
                                                Flags, 
                                                pMeshContainer->NumPaletteEntries, 
                                                pMeshContainer->pAdjacency, 
                                                NULL, NULL, NULL, 
                                                &pMeshContainer->NumInfl,
                                                &pMeshContainer->NumAttributeGroups, 
                                                &pMeshContainer->pBoneCombinationBuf, 
                                                &pMeshContainer->MeshData.pMesh);
        if (FAILED(hr))
            goto e_Exit;
    }
    // if vertex shader indexed skinning mode selected, use ConvertToIndexedsBlendedMesh to generate drawable mesh
    else if ((m_SkinningMethod == D3DINDEXEDVS) || (m_SkinningMethod == D3DINDEXEDHLSLVS))
    {
        // Get palette size
        // First 9 constants are used for other data.  Each 4x3 matrix takes up 3 constants.
        // (96 - 9) /3 i.e. Maximum constant count - used constants 
        UINT MaxMatrices = 26; 
        pMeshContainer->NumPaletteEntries = min(MaxMatrices, pMeshContainer->pSkinInfo->GetNumBones());

        DWORD Flags = D3DXMESHOPT_VERTEXCACHE;
        if (m_d3dCaps.VertexShaderVersion >= D3DVS_VERSION(1, 1))
        {
            pMeshContainer->UseSoftwareVP = false;
            Flags |= D3DXMESH_MANAGED;
        }
        else
        {
            pMeshContainer->UseSoftwareVP = true;
            Flags |= D3DXMESH_SYSTEMMEM;
        }

        SAFE_RELEASE(pMeshContainer->MeshData.pMesh);

        hr = pMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh
                                                (
                                                pMeshContainer->pOrigMesh,
                                                Flags, 
                                                pMeshContainer->NumPaletteEntries, 
                                                pMeshContainer->pAdjacency, 
                                                NULL, NULL, NULL,             
                                                &pMeshContainer->NumInfl,
                                                &pMeshContainer->NumAttributeGroups, 
                                                &pMeshContainer->pBoneCombinationBuf, 
                                                &pMeshContainer->MeshData.pMesh);
        if (FAILED(hr))
            goto e_Exit;


        // FVF has to match our declarator. Vertex shaders are not as forgiving as FF pipeline
        DWORD NewFVF = (pMeshContainer->MeshData.pMesh->GetFVF() & D3DFVF_POSITION_MASK) | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4;
        if (NewFVF != pMeshContainer->MeshData.pMesh->GetFVF())
        {
            LPD3DXMESH pMesh;
            hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(), NewFVF, m_pd3dDevice, &pMesh);
            if (!FAILED(hr))
            {
                pMeshContainer->MeshData.pMesh->Release();
                pMeshContainer->MeshData.pMesh = pMesh;
                pMesh = NULL;
            }
        }

        D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
        LPD3DVERTEXELEMENT9 pDeclCur;
        hr = pMeshContainer->MeshData.pMesh->GetDeclaration(pDecl);
        if (FAILED(hr))
            goto e_Exit;

        // the vertex shader is expecting to interpret the UBYTE4 as a D3DCOLOR, so update the type 
        //   NOTE: this cannot be done with CloneMesh, that would convert the UBYTE4 data to float and then to D3DCOLOR
        //          this is more of a "cast" operation
        pDeclCur = pDecl;
        while (pDeclCur->Stream != 0xff)
        {
            if ((pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) && (pDeclCur->UsageIndex == 0))
                pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
            pDeclCur++;
        }

        hr = pMeshContainer->MeshData.pMesh->UpdateSemantics(pDecl);
        if (FAILED(hr))
            goto e_Exit;

        // allocate a buffer for bone matrices, but only if another mesh has not allocated one of the same size or larger
        if (m_NumBoneMatricesMax < pMeshContainer->pSkinInfo->GetNumBones())
        {
            m_NumBoneMatricesMax = pMeshContainer->pSkinInfo->GetNumBones();

            // Allocate space for blend matrices
            delete []m_pBoneMatrices; 
            m_pBoneMatrices  = new D3DXMATRIXA16[m_NumBoneMatricesMax];
            if (m_pBoneMatrices == NULL)
            {
                hr = E_OUTOFMEMORY;
                goto e_Exit;
            }
        }

    }
    // if software skinning selected, use GenerateSkinnedMesh to create a mesh that can be used with UpdateSkinnedMesh
    else if (m_SkinningMethod == SOFTWARE)
    {
        hr = pMeshContainer->pOrigMesh->CloneMeshFVF(D3DXMESH_MANAGED, pMeshContainer->pOrigMesh->GetFVF(),
                                              m_pd3dDevice, &pMeshContainer->MeshData.pMesh);
        if (FAILED(hr))
            goto e_Exit;

        hr = pMeshContainer->MeshData.pMesh->GetAttributeTable(NULL, &pMeshContainer->NumAttributeGroups);
        if (FAILED(hr))
            goto e_Exit;

        delete[] pMeshContainer->pAttributeTable;
        pMeshContainer->pAttributeTable  = new D3DXATTRIBUTERANGE[pMeshContainer->NumAttributeGroups];
        if (pMeshContainer->pAttributeTable == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto e_Exit;
        }

        hr = pMeshContainer->MeshData.pMesh->GetAttributeTable(pMeshContainer->pAttributeTable, NULL);
        if (FAILED(hr))
            goto e_Exit;

        // allocate a buffer for bone matrices, but only if another mesh has not allocated one of the same size or larger
        if (m_NumBoneMatricesMax < pMeshContainer->pSkinInfo->GetNumBones())
        {
            m_NumBoneMatricesMax = pMeshContainer->pSkinInfo->GetNumBones();

            // Allocate space for blend matrices
            delete []m_pBoneMatrices; 
            m_pBoneMatrices  = new D3DXMATRIXA16[m_NumBoneMatricesMax];
            if (m_pBoneMatrices == NULL)
            {
                hr = E_OUTOFMEMORY;
                goto e_Exit;
            }
        }
    }
    else  // invalid m_SkinningMethod value
    {        
        // return failure due to invalid skinning method value
        hr = E_INVALIDARG;
        goto e_Exit;
    }

e_Exit:
    return hr;
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    // Set cursor to indicate that user can move the object with the mouse
#ifdef _WIN64
    SetClassLongPtr( m_hWnd, GCLP_HCURSOR, (LONG_PTR)LoadCursor( NULL, IDC_SIZEALL ) );
#else
    SetClassLong( m_hWnd, GCL_HCURSOR, HandleToLong( LoadCursor( NULL, IDC_SIZEALL ) ) );
#endif
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
     // Setup world matrix
    D3DXMATRIXA16 matWorld;
    D3DXMatrixTranslation( &matWorld, -m_vObjectCenter.x,
                                      -m_vObjectCenter.y,
                                      -m_vObjectCenter.z );
    D3DXMatrixMultiply( &matWorld, &matWorld, m_ArcBall.GetRotationMatrix() );
    D3DXMatrixMultiply( &matWorld, &matWorld, m_ArcBall.GetTranslationMatrix() );
    m_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    D3DXVECTOR3 vEye( 0, 0, -2*m_fObjectRadius );
    D3DXVECTOR3 vAt( 0, 0, 0 );
    D3DXVECTOR3 vUp( 0, 1, 0 );
    D3DXMatrixLookAtLH( &m_matView, &vEye, &vAt, &vUp);

    m_pd3dDevice->SetTransform( D3DTS_VIEW,  &m_matView );

    if (m_pAnimController != NULL)
        m_pAnimController->SetTime(m_pAnimController->GetTime() + m_fElapsedTime);

    UpdateFrameMatrices(m_pFrameRoot, &matWorld);

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DrawMeshContainer()
// Desc: Called to render a mesh in the hierarchy
//-----------------------------------------------------------------------------
void CMyD3DApplication::DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
    D3DXFRAME_DERIVED *pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
    UINT iMaterial;
    UINT NumBlend;
    UINT iAttrib;
    DWORD AttribIdPrev;
    LPD3DXBONECOMBINATION pBoneComb;

    UINT iMatrixIndex;
    UINT iPaletteEntry;
    D3DXMATRIXA16 matTemp;

    // first check for skinning
    if (pMeshContainer->pSkinInfo != NULL)
    {
        if (m_SkinningMethod == D3DNONINDEXED)
        {
            AttribIdPrev = UNUSED32; 
            pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

            // Draw using default vtx processing of the device (typically HW)
            for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
            {
                NumBlend = 0;
                for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
                {
                    if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
                    {
                        NumBlend = i;
                    }
                }

                if (m_d3dCaps.MaxVertexBlendMatrices >= NumBlend + 1)
                {
                    // first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
                    for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
                    {
                        iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
                        if (iMatrixIndex != UINT_MAX)
                        {
                            D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex] );
                            m_pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTemp );
                        }
                    }

                    m_pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);

                    // lookup the material used for this subset of faces
                    if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
                    {
                        m_pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
                        m_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
                        AttribIdPrev = pBoneComb[iAttrib].AttribId;
                    }

                    // draw the subset now that the correct material and matrices are loaded
                    pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
                }
            }

            // If necessary, draw parts that HW could not handle using SW
            if (pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups)
            {
                AttribIdPrev = UNUSED32; 
                m_pd3dDevice->SetSoftwareVertexProcessing(TRUE);
                for (iAttrib = pMeshContainer->iAttributeSW; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
                {
                    NumBlend = 0;
                    for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
                    {
                        if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
                        {
                            NumBlend = i;
                        }
                    }

                    if (m_d3dCaps.MaxVertexBlendMatrices < NumBlend + 1)
                    {
                        // first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
                        for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
                        {
                            iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
                            if (iMatrixIndex != UINT_MAX)
                            {
                                D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex] );
                                m_pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTemp );
                            }
                        }

                        m_pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);

                        // lookup the material used for this subset of faces
                        if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
                        {
                            m_pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
                            m_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
                            AttribIdPrev = pBoneComb[iAttrib].AttribId;
                        }

                        // draw the subset now that the correct material and matrices are loaded
                        pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
                    }
                }
                m_pd3dDevice->SetSoftwareVertexProcessing(FALSE);
            }

            m_pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);
        }
        else if (m_SkinningMethod == D3DINDEXED)
        {
            // if hw doesn't support indexed vertex processing, switch to software vertex processing
            if (pMeshContainer->UseSoftwareVP)
            {
                m_pd3dDevice->SetSoftwareVertexProcessing(TRUE);
            }

            // set the number of vertex blend indices to be blended
            if (pMeshContainer->NumInfl == 1)
                m_pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_0WEIGHTS);
            else
                m_pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, pMeshContainer->NumInfl - 1);

            if (pMeshContainer->NumInfl)
                m_pd3dDevice->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, TRUE);

            // for each attribute group in the mesh, calculate the set of matrices in the palette and then draw the mesh subset
            pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
            for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
            {
                // first calculate all the world matrices
                for (iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
                {
                    iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
                    if (iMatrixIndex != UINT_MAX)
                    {
                        D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex] );
                        m_pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( iPaletteEntry ), &matTemp );
                    }
                }
                
                // setup the material of the mesh subset - REMEMBER to use the original pre-skinning attribute id to get the correct material id
                m_pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
                m_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );

                // finally draw the subset with the current world matrix palette and material state
                pMeshContainer->MeshData.pMesh->DrawSubset( iAttrib );
            }

            // reset blending state
            m_pd3dDevice->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE);
            m_pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);

            // remember to reset back to hw vertex processing if software was required
            if (pMeshContainer->UseSoftwareVP)
            {
                m_pd3dDevice->SetSoftwareVertexProcessing(FALSE);
            }
        }
        else if (m_SkinningMethod == D3DINDEXEDVS) 
        {
            // Use COLOR instead of UBYTE4 since Geforce3 does not support it
            // vConst.w should be 3, but due to COLOR/UBYTE4 issue, mul by 255 and add epsilon
            D3DXVECTOR4 vConst( 1.0f, 0.0f, 0.0f, 765.01f );

            if (pMeshContainer->UseSoftwareVP)
            {
                m_pd3dDevice->SetSoftwareVertexProcessing(TRUE);
            }

            m_pd3dDevice->SetVertexShader(m_pIndexedVertexShader[pMeshContainer->NumInfl - 1]);

            pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
            for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
            {
                // first calculate all the world matrices
                for (iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
                {
                    iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
                    if (iMatrixIndex != UINT_MAX)
                    {
                        D3DXMatrixMultiply(&matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
                        D3DXMatrixMultiplyTranspose(&matTemp, &matTemp, &m_matView);
                        m_pd3dDevice->SetVertexShaderConstantF(iPaletteEntry*3 + 9, (float*)&matTemp, 3);
                    }
                }

                // Sum of all ambient and emissive contribution
                D3DXCOLOR color1(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Ambient);
                D3DXCOLOR color2(.25, .25, .25, 1.0);
                D3DXCOLOR ambEmm;
                D3DXColorModulate(&ambEmm, &color1, &color2);
                ambEmm += D3DXCOLOR(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Emissive);

                // set material color properties 
                m_pd3dDevice->SetVertexShaderConstantF(8, (float*)&(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Diffuse), 1);
                m_pd3dDevice->SetVertexShaderConstantF(7, (float*)&ambEmm, 1);
                vConst.y = pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Power;
                m_pd3dDevice->SetVertexShaderConstantF(0, (float*)&vConst, 1);

                m_pd3dDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

                // finally draw the subset with the current world matrix palette and material state
                pMeshContainer->MeshData.pMesh->DrawSubset( iAttrib );
                
            }

            // remember to reset back to hw vertex processing if software was required
            if (pMeshContainer->UseSoftwareVP)
            {
                m_pd3dDevice->SetSoftwareVertexProcessing(FALSE);
            }
            m_pd3dDevice->SetVertexShader(NULL);

        }
        else if (m_SkinningMethod == D3DINDEXEDHLSLVS) 
        {
            if (pMeshContainer->UseSoftwareVP)
            {
                m_pd3dDevice->SetSoftwareVertexProcessing(TRUE);
            }

            pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
            for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
            { 
                // first calculate all the world matrices
                for (iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
                {
                    iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
                    if (iMatrixIndex != UINT_MAX)
                    {
                        D3DXMatrixMultiply(&matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
                        D3DXMatrixMultiply(&m_pBoneMatrices[iPaletteEntry], &matTemp, &m_matView);
                    }
                }
                m_pEffect->SetMatrixArray( "mWorldMatrixArray", m_pBoneMatrices, pMeshContainer->NumPaletteEntries);

                // Sum of all ambient and emissive contribution
                D3DXCOLOR color1(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Ambient);
                D3DXCOLOR color2(.25, .25, .25, 1.0);
                D3DXCOLOR ambEmm;
                D3DXColorModulate(&ambEmm, &color1, &color2);
                ambEmm += D3DXCOLOR(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Emissive);

                // set material color properties 
                m_pEffect->SetVector("MaterialDiffuse", (D3DXVECTOR4*)&(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Diffuse));
                m_pEffect->SetVector("MaterialAmbient", (D3DXVECTOR4*)&ambEmm);

                // setup the material of the mesh subset - REMEMBER to use the original pre-skinning attribute id to get the correct material id
                m_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );

                // Set CurNumBones to select the correct vertex shader for the number of bones
                m_pEffect->SetInt( "CurNumBones", pMeshContainer->NumInfl -1);

                // Start the effect now all parameters have been updated
                UINT numPasses;
                m_pEffect->Begin( &numPasses, D3DXFX_DONOTSAVESTATE );
                for( UINT iPass = 0; iPass < numPasses; iPass++ )
                {
                    m_pEffect->Pass( iPass );
                    // draw the subset with the current world matrix palette and material state
                    pMeshContainer->MeshData.pMesh->DrawSubset( iAttrib );
                }

                m_pEffect->End();        

                m_pd3dDevice->SetVertexShader(NULL);
            }

            // remember to reset back to hw vertex processing if software was required
            if (pMeshContainer->UseSoftwareVP)
            {
                m_pd3dDevice->SetSoftwareVertexProcessing(FALSE);
            }
        }
        else if (m_SkinningMethod == SOFTWARE)
        {
            D3DXMATRIX  Identity;
            DWORD       cBones  = pMeshContainer->pSkinInfo->GetNumBones();
            DWORD       iBone;
            PBYTE       pbVerticesSrc;
            PBYTE       pbVerticesDest;

            // set up bone transforms
            for (iBone = 0; iBone < cBones; ++iBone)
            {
                D3DXMatrixMultiply
                (
                    &m_pBoneMatrices[iBone],                 // output
                    &pMeshContainer->pBoneOffsetMatrices[iBone], 
                    pMeshContainer->ppBoneMatrixPtrs[iBone]
                );
            }

            // set world transform
            D3DXMatrixIdentity(&Identity);
            m_pd3dDevice->SetTransform(D3DTS_WORLD, &Identity);

            pMeshContainer->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pbVerticesSrc);
            pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, (LPVOID*)&pbVerticesDest);

            // generate skinned mesh
            pMeshContainer->pSkinInfo->UpdateSkinnedMesh(m_pBoneMatrices, NULL, pbVerticesSrc, pbVerticesDest);

            pMeshContainer->pOrigMesh->UnlockVertexBuffer();
            pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();

            for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
            {
                m_pd3dDevice->SetMaterial(&(pMeshContainer->pMaterials[pMeshContainer->pAttributeTable[iAttrib].AttribId].MatD3D));
                m_pd3dDevice->SetTexture(0, pMeshContainer->ppTextures[pMeshContainer->pAttributeTable[iAttrib].AttribId]);
                pMeshContainer->MeshData.pMesh->DrawSubset(pMeshContainer->pAttributeTable[iAttrib].AttribId);
            }
        }
        else // bug out as unsupported mode
        {
            return;
        }
    }
    else  // standard mesh, just draw it after setting material properties
    {
        m_pd3dDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);

        for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
        {
            m_pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D );
            m_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[iMaterial] );
            pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
        }
    }
}




//-----------------------------------------------------------------------------
// Name: DrawFrame()
// Desc: Called to render a frame in the hierarchy
//-----------------------------------------------------------------------------
void CMyD3DApplication::DrawFrame(LPD3DXFRAME pFrame)
{
    LPD3DXMESHCONTAINER pMeshContainer;

    pMeshContainer = pFrame->pMeshContainer;
    while (pMeshContainer != NULL)
    {
        DrawMeshContainer(pMeshContainer, pFrame);

        pMeshContainer = pMeshContainer->pNextMeshContainer;
    }

    if (pFrame->pFrameSibling != NULL)
    {
        DrawFrame(pFrame->pFrameSibling);
    }

    if (pFrame->pFrameFirstChild != NULL)
    {
        DrawFrame(pFrame->pFrameFirstChild);
    }
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{
    // Clear the backbuffer
    m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
                         0x000000ff, 1.0f, 0L );

    // Setup the light
    D3DLIGHT9 light;
    D3DUtil_InitLight( light, D3DLIGHT_DIRECTIONAL, 0.0f,-1.0f, 1.0f );
    m_pd3dDevice->SetLight(0, &light );
    m_pd3dDevice->LightEnable(0, TRUE );

    // Set Light for vertex shader
    D3DXVECTOR4 vLightDir( 0.0f, 1.0f, -1.0f, 0.0f );
    D3DXVec4Normalize( &vLightDir, &vLightDir );
    m_pd3dDevice->SetVertexShaderConstantF(1, (float*)&vLightDir, 1);

    // Setup the projection matrix
    D3DXMATRIXA16 matProj;
    FLOAT      fAspect = (FLOAT)m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, fAspect, 
                                m_fObjectRadius/64.0f, m_fObjectRadius*200.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    m_pEffect->SetMatrix( "mViewProj", &matProj);
    m_pEffect->SetVector( "lhtDir", &vLightDir);

    // set the projection matrix for the vertex shader based skinning method
    D3DXMatrixTranspose(&matProj, &matProj);
    m_pd3dDevice->SetVertexShaderConstantF(2, (float*)&matProj, 4);

    // Begin the scene
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
        DrawFrame(m_pFrameRoot);

        // Output statistics
        m_pFont->DrawText(   2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
        m_pFont->DrawText(   2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );
        TCHAR* pstrType;
        if( m_SkinningMethod == D3DNONINDEXED )
            pstrType = TEXT("Using non-indexed skinning");
        else if( m_SkinningMethod == D3DINDEXED )
            pstrType = TEXT("Using indexed skinning");
        else if( m_SkinningMethod == SOFTWARE )
            pstrType = TEXT("Using software skinning");
        else if( m_SkinningMethod == D3DINDEXEDVS )
            pstrType = TEXT("Using indexed skinning with a vertex shader");
        else if( m_SkinningMethod == D3DINDEXEDHLSLVS )
            pstrType = TEXT("Using indexed skinning with a HLSL vertex shader");
        else
            pstrType = TEXT("No skinning");
        m_pFontSmall->DrawText(   2, 40, D3DCOLOR_ARGB(255,255,255,255), pstrType );

        // End the scene.
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SetupBoneMatrixPointersOnMesh()
// Desc: Called to setup the pointers for a given bone to its transformation matrix
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase)
{
    UINT iBone, cBones;
    D3DXFRAME_DERIVED *pFrame;

    D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;

    // if there is a skinmesh, then setup the bone matrices
    if (pMeshContainer->pSkinInfo != NULL)
    {
        cBones = pMeshContainer->pSkinInfo->GetNumBones();

        pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[cBones];
        if (pMeshContainer->ppBoneMatrixPtrs == NULL)
            return E_OUTOFMEMORY;

        for (iBone = 0; iBone < cBones; iBone++)
        {
            pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone));
            if (pFrame == NULL)
                return E_FAIL;

            pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;
        }
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: SetupBoneMatrixPointers()
// Desc: Called to setup the pointers for a given bone to its transformation matrix
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::SetupBoneMatrixPointers(LPD3DXFRAME pFrame)
{
    HRESULT hr;

    if (pFrame->pMeshContainer != NULL)
    {
        hr = SetupBoneMatrixPointersOnMesh(pFrame->pMeshContainer);
        if (FAILED(hr))
            return hr;
    }

    if (pFrame->pFrameSibling != NULL)
    {
        hr = SetupBoneMatrixPointers(pFrame->pFrameSibling);
        if (FAILED(hr))
            return hr;
    }

    if (pFrame->pFrameFirstChild != NULL)
    {
        hr = SetupBoneMatrixPointers(pFrame->pFrameFirstChild);
        if (FAILED(hr))
            return hr;
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DrawFrame()
// Desc: Called to render a frame in the hierarchy
//-----------------------------------------------------------------------------
void CMyD3DApplication::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
    D3DXFRAME_DERIVED *pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

    if (pParentMatrix != NULL)
        D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
    else
        pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;

    if (pFrame->pFrameSibling != NULL)
    {
        UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
    }

    if (pFrame->pFrameFirstChild != NULL)
    {
        UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
    }
}




//-----------------------------------------------------------------------------
// Name: DrawFrame()
// Desc: Called to render a frame in the hierarchy
//-----------------------------------------------------------------------------
void CMyD3DApplication::UpdateSkinningMethod(LPD3DXFRAME pFrameBase)
{
    D3DXFRAME_DERIVED *pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
    D3DXMESHCONTAINER_DERIVED *pMeshContainer;

    pMeshContainer = (D3DXMESHCONTAINER_DERIVED *)pFrame->pMeshContainer;

    while (pMeshContainer != NULL)
    {
        GenerateSkinnedMesh(pMeshContainer);

        pMeshContainer = (D3DXMESHCONTAINER_DERIVED *)pMeshContainer->pNextMeshContainer;
    }

    if (pFrame->pFrameSibling != NULL)
    {
        UpdateSkinningMethod(pFrame->pFrameSibling);
    }

    if (pFrame->pFrameFirstChild != NULL)
    {
        UpdateSkinningMethod(pFrame->pFrameFirstChild);
    }
}




//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: This creates all device-dependent managed objects, such as managed
//       textures and managed vertex buffers.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    TCHAR      strMeshPath[MAX_PATH];
    TCHAR      strSkinnedMeshFXPath[MAX_PATH];
    HRESULT    hr;
    CAllocateHierarchy Alloc(this);

    // Initialize the font's internal textures
    m_pFont->InitDeviceObjects( m_pd3dDevice );
    m_pFontSmall->InitDeviceObjects( m_pd3dDevice );

    // Load the mesh from the specified file
    hr = DXUtil_FindMediaFileCb( strMeshPath, sizeof(strMeshPath), m_strMeshFilename );
    if (FAILED(hr))
        return hr;

    hr = D3DXLoadMeshHierarchyFromX(strMeshPath, D3DXMESH_MANAGED, m_pd3dDevice, &Alloc, NULL, &m_pFrameRoot, &m_pAnimController);
    if (FAILED(hr))
        return hr;

    hr = SetupBoneMatrixPointers(m_pFrameRoot);
    if (FAILED(hr))
        return hr;

    hr = D3DXFrameCalculateBoundingSphere(m_pFrameRoot, &m_vObjectCenter, &m_fObjectRadius);
    if (FAILED(hr))
        return hr;

    // Create Effect for HLSL skinning
    // Find the vertex shader file
    if( FAILED( hr = DXUtil_FindMediaFileCb( strSkinnedMeshFXPath, 
        sizeof(strSkinnedMeshFXPath), _T("SkinnedMesh.fx") ) ) )
        return hr;

    hr = D3DXCreateEffectFromFile( m_pd3dDevice, strSkinnedMeshFXPath, NULL,
                                       NULL, D3DXSHADER_DEBUG, NULL, &m_pEffect, NULL);
    if (FAILED(hr))
        return hr;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Restore device-memory objects and state after a device is created or
//       resized.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    HRESULT hr;

    // Setup render state
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING,         TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE,     TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_CULLMODE,         D3DCULL_CCW );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT,          0x33333333 );
    m_pd3dDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

    // Setup the arcball parameters
    m_ArcBall.SetWindow( m_d3dsdBackBuffer.Width, m_d3dsdBackBuffer.Height, 0.85f );
    m_ArcBall.SetRadius( m_fObjectRadius );

    // Restore Effect
    if ( m_pEffect )
        m_pEffect->OnResetDevice();

    // Restore the font
    m_pFont->RestoreDeviceObjects();
    m_pFontSmall->RestoreDeviceObjects();

    // load the indexed vertex shaders
    for (DWORD iInfl = 0; iInfl < 4; ++iInfl)
    {
        LPD3DXBUFFER pCode;

        // Assemble the vertex shader file
        if( FAILED( hr = D3DXAssembleShaderFromResource(NULL, MAKEINTRESOURCE(IDD_SHADER1 + iInfl), NULL, NULL, 0, &pCode, NULL ) ) )
            return hr;

        // Create the vertex shader
        if( FAILED( hr = m_pd3dDevice->CreateVertexShader( (DWORD*)pCode->GetBufferPointer(),
                                                           &m_pIndexedVertexShader[iInfl] ) ) )
        {
            return hr;
        }

        pCode->Release();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Called when the device-dependent objects are about to be lost.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();
    m_pFontSmall->InvalidateDeviceObjects();

    // release the vertex shaders
    for (DWORD iInfl = 0; iInfl < 4; ++iInfl)
    {
        SAFE_RELEASE(m_pIndexedVertexShader[iInfl]);
    }

    // Invalidate Effect
    if ( m_pEffect )
        m_pEffect->OnLostDevice();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::DeleteDeviceObjects()
{
    CAllocateHierarchy Alloc(this);

    m_pFont->DeleteDeviceObjects();
    m_pFontSmall->DeleteDeviceObjects();

    D3DXFrameDestroy(m_pFrameRoot, &Alloc);

    SAFE_RELEASE(m_pAnimController);

    SAFE_RELEASE(m_pEffect);

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FinalCleanup()
{
    SAFE_DELETE( m_pFont );
    SAFE_DELETE( m_pFontSmall );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Message proc function to handle key and menu input
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam )
{
    // Pass mouse messages to the ArcBall so it can build internal matrices
    m_ArcBall.HandleMouseMessages( hWnd, uMsg, wParam, lParam );

    // Trap context menu
    if( WM_CONTEXTMENU == uMsg )
        return 0;

    // Handle key presses
    if( WM_KEYDOWN == uMsg )
    {
        if( 'W' == (int)wParam )
            m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

        if( 'S' == (int)wParam )
            m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
    }
    else if( uMsg == WM_COMMAND )
    {
            // Handle the open file command
        if( LOWORD(wParam) == IDM_OPENFILE )
        {
            TCHAR g_strFilename[MAX_PATH]   = _T("");

            // Display the OpenFileName dialog. Then, try to load the specified file
            OPENFILENAME ofn = { sizeof(OPENFILENAME), NULL, NULL,
                                _T(".X Files (.x)\0*.x\0\0"), 
                                NULL, 0, 1, m_strMeshFilename, MAX_PATH, g_strFilename, MAX_PATH, 
                                m_strInitialDir, _T("Open Mesh File"), 
                                OFN_FILEMUSTEXIST, 0, 1, NULL, 0, NULL, NULL };

            if( TRUE == GetOpenFileName( &ofn ) )
            {
                _tcscpy( m_strInitialDir, m_strMeshFilename );
                TCHAR* pLastSlash =  _tcsrchr( m_strInitialDir, _T('\\') );
                if( pLastSlash )
                    *pLastSlash = 0;
                SetCurrentDirectory( m_strInitialDir );

                // Destroy and recreate everything
                InvalidateDeviceObjects();
                DeleteDeviceObjects();
                InitDeviceObjects();
                RestoreDeviceObjects();
            }
        }
        else if ((LOWORD(wParam) >= ID_OPTIONS_D3DNONINDEXED) && ((LOWORD(wParam) <= ID_OPTIONS_HLSLINDEXED)))
        {
            HMENU   hMenu = GetMenu(hWnd);
            METHOD  NewSkinningMethod = (METHOD)(LOWORD(wParam) - ID_OPTIONS_D3DNONINDEXED);
            
            CheckMenuItem(hMenu, ID_OPTIONS_D3DNONINDEXED, MF_UNCHECKED);
            CheckMenuItem(hMenu, ID_OPTIONS_D3DINDEXED, MF_UNCHECKED);
            CheckMenuItem(hMenu, ID_OPTIONS_SOFTWARESKINNING, MF_UNCHECKED);
            CheckMenuItem(hMenu, ID_OPTIONS_D3DINDEXEDVS, MF_UNCHECKED);
            CheckMenuItem(hMenu, ID_OPTIONS_HLSLINDEXED, MF_UNCHECKED);
            CheckMenuItem(hMenu, LOWORD(wParam), MF_CHECKED);

            // if the selected skinning method is different than the current one
            if (m_SkinningMethod != NewSkinningMethod)
            {
                m_SkinningMethod = NewSkinningMethod;

                // update the meshes to the new skinning method
                UpdateSkinningMethod(m_pFrameRoot);
            }
        }
    }
    
    // Pass remaining messages to default handler
    return CD3DApplication::MsgProc( hWnd, uMsg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice (D3DCAPS9* pCaps, DWORD dwBehavior, 
                                          D3DFORMAT adapterFormat, D3DFORMAT backBufferFormat )
{
    // Always request MIXED or SOFTWARE vertex processing do deal with fall backs
    if ((dwBehavior & D3DCREATE_PUREDEVICE) || (dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING))
        return E_FAIL;

    // If using mixed, make sure the hardware can do vertex blending
    if( ( dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING ) &&
        pCaps->MaxVertexBlendMatrices < 2 )
    {
        return E_FAIL;
    }

    return S_OK;
}
