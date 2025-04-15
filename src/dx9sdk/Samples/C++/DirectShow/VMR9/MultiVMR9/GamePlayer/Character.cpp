//------------------------------------------------------------------------------
// File: Character.cpp
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#define STRICT
#include "stdafx.h"
#include "Character.h"
#include <d3dx9anim.h>
#include <d3dx9mesh.h>
#include "d3dutil.h"
#include "dxutil.h"
#include "resource.h"

const TCHAR g_achMeshFile[] = TEXT("tiny.x");
const TCHAR g_achSkinFile[] = TEXT("Tiny_skin.bmp");

// world matrix (combined projection and view)
D3DXMATRIX g_matCharacterWorld(
             0.850856720f,  0.17622593f,   0.49494526f,  0.00000000f,
             0.031906456f,  0.92298937f,  -0.38349065f,  0.00000000f,
            -0.524415970f,  0.34209663f,   0.77970898f,  0.00000000f,
          -230.000000000f, 20.00000000f,   0.00000000f,  1.00000000f
            );

extern D3DXMATRIX g_matWorld;


/********************Public*Routine*of*Private*Class***********************\
* CCharacter
*
* constructor
\**************************************************************************/
CCharacter::CCharacter()
    : m_bInitialized( FALSE )
    , m_pFrameRoot( NULL )
    , m_pAnimController( NULL )
    , m_pDevice( NULL )
    , m_pBoneMatrices( NULL )
    , m_fObjectRadius( 0.f )
    , m_NumBoneMatricesMax( 0 )
{
    ZeroMemory( &m_vObjectCenter, sizeof(m_vObjectCenter));
}

/********************Public*Routine*of*Private*Class***********************\
* ~CCharacter
*
* destructor
\**************************************************************************/
CCharacter::~CCharacter()
{
    CAllocateHierarchy Alloc(m_pDevice);

    D3DXFrameDestroy(m_pFrameRoot, &Alloc);
    RELEASE( m_pAnimController );
    RELEASE( m_pDevice );

    if( m_pBoneMatrices )
    {
        delete[] m_pBoneMatrices;
        m_pBoneMatrices = NULL;
    }
}

/********************Public*Routine*of*Private*Class***********************\
* Initialize
*
* Loads "walking figure" from 'tiny.x' file as a skinned mesh
\**************************************************************************/
HRESULT CCharacter::Initialize( IDirect3DDevice9 *pDevice )
{
    HRESULT hr = S_OK;

    CString strMessage;
    TCHAR achMeshPath[MAX_PATH];
    CAllocateHierarchy Alloc( pDevice );

    if( !pDevice )
    {
        return E_POINTER;
    }

    m_pDevice = pDevice;
    m_pDevice->AddRef();

    if( m_bInitialized )
    {
        return VFW_E_WRONG_STATE;
    }
    
    try
    {
        hr = FindMediaFile( achMeshPath,
                            sizeof( TCHAR)*MAX_PATH,
                            (TCHAR*)g_achSkinFile,
                            MAKEINTRESOURCE(IDB_BITMAP_SKIN),
                            RT_BITMAP);
        if( FAILED(hr))
        {
            strMessage.Format(_T("Cannot find file '%s''. Make sure you have valid installation of DirectX SDK"), g_achSkinFile);
            AfxMessageBox( strMessage );
            return hr;
        }

        hr = FindMediaFile( achMeshPath,
                            sizeof( TCHAR)*MAX_PATH,
                            (TCHAR*)g_achMeshFile,
                            MAKEINTRESOURCE(IDR_DATA_MESH),
                            RT_RCDATA);
        if( FAILED(hr))
        {
            strMessage.Format(_T("Cannot find file '%s''. Make sure you have valid installation of DirectX SDK"), g_achMeshFile);
            AfxMessageBox( strMessage );
            return hr;
        }

        hr = D3DXLoadMeshHierarchyFromX(achMeshPath, 
                                        D3DXMESH_MANAGED, 
                                        pDevice, 
                                        (LPD3DXALLOCATEHIERARCHY)(&Alloc), 
                                        NULL, 
                                        (LPD3DXFRAME*)(&m_pFrameRoot), 
                                        (LPD3DXANIMATIONCONTROLLER*)(&m_pAnimController));
                                        
        if (FAILED(hr))
        {
            throw hr;
        }

        hr = SetupBoneMatrixPointers_(m_pFrameRoot);
        if (FAILED(hr))
        {
            throw hr;
        }

        hr = D3DXFrameCalculateBoundingSphere(m_pFrameRoot, &m_vObjectCenter, &m_fObjectRadius);
        if (FAILED(hr))
        {
            throw hr;
        }

        m_bInitialized = TRUE;
    }

    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    return hr;
}

/********************Public*Routine*of*Private*Class***********************\
* RestoreDeviceObjects
*
* restores device objects for "walking figure"
\**************************************************************************/
HRESULT CCharacter::RestoreDeviceObjects( IDirect3DDevice9* pDevice)
{
    HRESULT hr = S_OK;

    if( !pDevice )
    {
        return E_POINTER;
    }
    try
    {
        // Setup render state

        CHECK_HR(
            hr = pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU ,D3DTADDRESS_WRAP),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DSAMP_ADDRESSU/D3DTADDRESS_WRAP, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV ,D3DTADDRESS_WRAP),
            DbgMsg("CHall::RestoreDeviceObjects failed to set D3DSAMP_ADDRESSV/D3DTADDRESS_WRAP, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState( D3DRS_ZENABLE, TRUE ), 
            DbgMsg("CCharacter::RestoreDeviceObjects: failed to set render state D3DRS_ZENABLE/TRUE, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ),
            DbgMsg("CCharacter::RestoreDeviceObjects: failed to set render state D3DRS_CULLMODE/D3DCULL_CCW, hr = 0x%08x", hr));

        CHECK_HR(
            hr = pDevice->SetRenderState( D3DRS_AMBIENT, 0x55555555 ),
            DbgMsg("CCharacter::RestoreDeviceObjects: failed to set render state D3DRS_AMBIENT/0x33333333, hr = 0x%08x", hr));

    }// try
    catch(HRESULT hr1)
    {
        hr = hr1;
    }
    return hr;
}

/********************Public*Routine*of*Private*Class***********************\
* Compose
*
* restores device objects for "walking figure"
\**************************************************************************/
HRESULT CCharacter::Compose(DWORD t)
{
    HRESULT hr = S_OK;
    static DWORD dwLastTick = 0L;


    DOUBLE fElapsedTime;

    if( 0L == dwLastTick )
    {
        fElapsedTime = 0.f;
    }
    else
    {
        fElapsedTime = (DOUBLE)(t - dwLastTick)/1000.f;
    }
    dwLastTick = t;

    if (m_pAnimController != NULL)
        m_pAnimController->SetTime(m_pAnimController->GetTime() + fElapsedTime);

    UpdateFrameMatrices_(m_pFrameRoot, &g_matCharacterWorld);

    return hr;
}


/********************Public*Routine*of*Private*Class***********************\
* Render
*
\**************************************************************************/
HRESULT CCharacter::Render(IDirect3DDevice9* pDevice)
{
    HRESULT hr = S_OK;

    if( !pDevice )
    {
        return E_POINTER;
    }
    try
    {
        CHECK_HR(
            hr = RestoreDeviceObjects( pDevice ),
            DbgMsg("CCharacter::Render: failed in RestoreDeviceObjects, hr = 0x%08x", hr));

        CHECK_HR(
            hr = DrawFrame_(pDevice, m_pFrameRoot ),
            DbgMsg("CCharacter::Render: failed in DrawFrame_, hr = 0x%08x", hr));
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
    return hr;
}

/********************Private*Routine*of*Private*Class**********************\
* DrawFrame_
* Draws of frame of the frame hierarchy
\**************************************************************************/
HRESULT CCharacter::DrawFrame_(IDirect3DDevice9* pDevice, LPD3DXFRAME pFrame)
{
    HRESULT hr = S_OK;
    LPD3DXMESHCONTAINER pMeshContainer;

    pMeshContainer = pFrame->pMeshContainer;
    while (pMeshContainer != NULL)
    {
        DrawMeshContainer_(pDevice, pMeshContainer, pFrame);

        pMeshContainer = pMeshContainer->pNextMeshContainer;
    }

    if (pFrame->pFrameSibling != NULL)
    {
        DrawFrame_(pDevice, pFrame->pFrameSibling);
    }

    if (pFrame->pFrameFirstChild != NULL)
    {
        DrawFrame_(pDevice, pFrame->pFrameFirstChild);
    }
    return S_OK;
}

/********************Private*Routine*of*Private*Class**********************\
* DrawMeshContainer_
* 
\**************************************************************************/
HRESULT CCharacter::DrawMeshContainer_( IDirect3DDevice9* pDevice,
                                        LPD3DXMESHCONTAINER pMeshContainerBase, 
                                        LPD3DXFRAME pFrameBase)
{
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
    D3DXFRAME_DERIVED *pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
    UINT iMaterial;
    UINT NumBlend;
    UINT iAttrib;
    DWORD AttribIdPrev;
    LPD3DXBONECOMBINATION pBoneComb;

    UINT iMatrixIndex;
    D3DXMATRIXA16 matTemp;

    // first check for skinning
    if (pMeshContainer->pSkinInfo != NULL)
    {
        AttribIdPrev = UNUSED32; 
        pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(
                        pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

        // Draw using default vtx processing of the device (typically HW)
        for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
        {
            DWORD i;
            NumBlend = 0;
            for (i = 0; i < pMeshContainer->NumInfl; ++i)
            {
                if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
                {
                    NumBlend = i;
                }
            }

            // first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
            for (i = 0; i < pMeshContainer->NumInfl; ++i)
            {
                iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
                if (iMatrixIndex != UINT_MAX)
                {
                    pDevice->SetTransform(D3DTS_WORLDMATRIX(i), pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
                    pDevice->MultiplyTransform(D3DTS_WORLDMATRIX(i), &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex]);
                }
            }

            pDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);

            // lookup the material used for this subset of faces
            if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
            {
                pDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
                pDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
                AttribIdPrev = pBoneComb[iAttrib].AttribId;
            }

            // draw the subset now that the correct material and matrices are loaded
            pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
        }

        // If necessary, draw parts that HW could not handle using SW
        if (pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups)
        {
            AttribIdPrev = UNUSED32; 
            pDevice->SetSoftwareVertexProcessing(TRUE);
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

                // first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
                for (i = 0; i < pMeshContainer->NumInfl; ++i)
                {
                    iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
                    if (iMatrixIndex != UINT_MAX)
                    {
                        pDevice->SetTransform(D3DTS_WORLDMATRIX(i), pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
                        pDevice->MultiplyTransform(D3DTS_WORLDMATRIX(i), &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex]);
                    }
                }

                pDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);

                // lookup the material used for this subset of faces
                if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
                {
                    pDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
                    pDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
                    AttribIdPrev = pBoneComb[iAttrib].AttribId;
                }

                // draw the subset now that the correct material and matrices are loaded
                pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
            }
            pDevice->SetSoftwareVertexProcessing(FALSE);
        }

            pDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);
    }
    else  // standard mesh, just draw it after setting material properties
    {
        pDevice->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);

        for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
        {
            pDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D );
            pDevice->SetTexture( 0, pMeshContainer->ppTextures[iMaterial] );
            pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
        }
    }
    return S_OK;
}

/********************Private*Routine*of*Private*Class**********************\
* UpdateFrameMatrices_
* 
\**************************************************************************/
HRESULT CCharacter::UpdateFrameMatrices_(LPD3DXFRAME pFrameBase, D3DXMATRIX* pM)
{
    D3DXFRAME_DERIVED *pFrame = (D3DXFRAME_DERIVED*)pFrameBase;

    if (pM != NULL)
        D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pM);
    else
        pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;

    if (pFrame->pFrameSibling != NULL)
    {
        UpdateFrameMatrices_(pFrame->pFrameSibling, pM);
    }

    if (pFrame->pFrameFirstChild != NULL)
    {
        UpdateFrameMatrices_(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
    }

    return S_OK;
}

/********************Private*Routine*of*Private*Class***********************\
* SetupBoneMatrixPointers_
*
* Called to setup the pointers for a given bone to its transformation matrix
* ( see SkinnedMesh sample of Direct3D of this SDK )
\**************************************************************************/
HRESULT CCharacter::SetupBoneMatrixPointers_( LPD3DXFRAME pFrame)
{
    HRESULT hr = S_OK;

    if (pFrame->pMeshContainer != NULL)
    {
        hr = SetupBoneMatrixPointersOnMesh_(pFrame->pMeshContainer);
        if (FAILED(hr))
            return hr;
    }

    if (pFrame->pFrameSibling != NULL)
    {
        hr = SetupBoneMatrixPointers_(pFrame->pFrameSibling);
        if (FAILED(hr))
            return hr;
    }

    if (pFrame->pFrameFirstChild != NULL)
    {
        hr = SetupBoneMatrixPointers_(pFrame->pFrameFirstChild);
        if (FAILED(hr))
            return hr;
    }

    return S_OK;
}

/********************Private*Routine*of*Private*Class***********************\
* SetupBoneMatrixPointersOnMesh_
*
* Called to setup the pointers for a given bone to its transformation matrix
* ( see SkinnedMesh sample of Direct3D of this SDK )
\**************************************************************************/
HRESULT CCharacter::SetupBoneMatrixPointersOnMesh_(
                            LPD3DXMESHCONTAINER pMeshContainerBase)
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

//////////////////////////////// CAllocateHierarchy ///////////////////////////

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
// CAllocateHierarchy
// Constructor
//-----------------------------------------------------------------------------
CAllocateHierarchy::CAllocateHierarchy(IDirect3DDevice9* pDevice)
    : m_pDevice( NULL )
{
    if( pDevice )
    {
        m_pDevice = pDevice;
        m_pDevice->AddRef();
    }
}

//-----------------------------------------------------------------------------
// ~CAllocateHierarchy
// Destructor
//-----------------------------------------------------------------------------
CAllocateHierarchy::~CAllocateHierarchy()
{
    RELEASE( m_pDevice );
}

//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::CreateFrame()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateFrame(LPCTSTR Name, LPD3DXFRAME *ppNewFrame)
{
    HRESULT hr = S_OK;
    D3DXFRAME_DERIVED *pFrame = NULL;

    *ppNewFrame = NULL;

    try
    {

        pFrame = new D3DXFRAME_DERIVED;

        if (pFrame == NULL)
            throw E_OUTOFMEMORY;

        hr = AllocateName(Name, &pFrame->Name);
        if (FAILED(hr))
        {
            delete pFrame;
            throw hr;
        }

        // initialize other data members of the frame
        D3DXMatrixIdentity(&pFrame->TransformationMatrix);
        D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);

        pFrame->pMeshContainer = NULL;
        pFrame->pFrameSibling = NULL;
        pFrame->pFrameFirstChild = NULL;

        *ppNewFrame = pFrame;
        pFrame = NULL;
    }
    catch( HRESULT hr1 )
    {
        if( pFrame )
        {
            delete pFrame;
            hr = hr1;
        }
    }
    return hr;
}


//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::CreateMeshContainer()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::CreateMeshContainer(
                                    LPCTSTR Name, 
                                    LPD3DXMESHDATA pMeshData,
                                    LPD3DXMATERIAL pMaterials, 
                                    LPD3DXEFFECTINSTANCE pEffectInstances, 
                                    DWORD NumMaterials, 
                                    DWORD *pAdjacency, 
                                    LPD3DXSKININFO pSkinInfo, 
                                    LPD3DXMESHCONTAINER *ppNewMeshContainer) 
{
    HRESULT hr = S_OK;
    D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;
    UINT NumFaces;
    UINT iMaterial;
    UINT iBone, cBones;

    LPDIRECT3DDEVICE9 pd3dDevice = NULL;
    LPD3DXMESH pMesh = NULL;

    *ppNewMeshContainer = NULL;

    try
    {
        // this sample does not handle patch meshes, so fail when one is found
        if (pMeshData->Type != D3DXMESHTYPE_MESH)
            throw E_FAIL;

        // get the pMesh interface pointer out of the mesh data structure
        pMesh = pMeshData->pMesh;

        // this sample does not FVF compatible meshes, so fail when one is found
        if (pMesh->GetFVF() == 0)
            throw E_FAIL;

        // allocate the overloaded structure to return as a D3DXMESHCONTAINER
        pMeshContainer = new D3DXMESHCONTAINER_DERIVED;

        if (pMeshContainer == NULL)
            throw E_OUTOFMEMORY;

        memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

        // make sure and copy the name.  All memory as input belongs to caller, interfaces can be addref'd though
        hr = AllocateName(Name, &pMeshContainer->Name);
        if (FAILED(hr))
            throw hr;        

        pMesh->GetDevice(&pd3dDevice);
        NumFaces = pMesh->GetNumFaces();

        // if no normals are in the mesh, add them
        if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
        {
            pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

            // clone the mesh to make room for the normals
            hr = pMesh->CloneMeshFVF(   pMesh->GetOptions(), 
                                        pMesh->GetFVF() | D3DFVF_NORMAL, 
                                        pd3dDevice, 
                                        &pMeshContainer->MeshData.pMesh );
            if (FAILED(hr))
                throw hr;

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
            throw E_OUTOFMEMORY;

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
                throw E_OUTOFMEMORY;

            // get each of the bone offset matrices so that we don't need to get them later
            for (iBone = 0; iBone < cBones; iBone++)
            {
                pMeshContainer->pBoneOffsetMatrices[iBone] = 
                        *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
            }

            // GenerateSkinnedMesh will take the general skinning information and transform it to a HW friendly version
            hr = GenerateSkinnedMesh_(pMeshContainer);
            if (FAILED(hr))
                throw hr;
        }

        *ppNewMeshContainer = pMeshContainer;
        pMeshContainer = NULL;
    }// try
    catch( HRESULT hr1 )
    {
        DestroyMeshContainer(pMeshContainer);
        hr = hr1;
    }

    RELEASE(pd3dDevice);
    return hr;
}

//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::DestroyFrame()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree) 
{
    if( pFrameToFree->Name )
    {
        delete[] pFrameToFree->Name;
        pFrameToFree->Name = NULL;
    }
    if( pFrameToFree )
    {
        delete pFrameToFree;
        pFrameToFree = NULL;
    }
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

    if( pMeshContainer->Name )
    {
        delete[] pMeshContainer->Name;
        pMeshContainer->Name = NULL;
    }

    if( pMeshContainer->pAdjacency )
    {
        delete[] pMeshContainer->pAdjacency;
        pMeshContainer->pAdjacency = NULL;
    }

    if( pMeshContainer->pMaterials )
    {
        delete[] pMeshContainer->pMaterials;
        pMeshContainer->pMaterials = NULL;
    }

    if( pMeshContainer->pBoneOffsetMatrices )
    {
        delete[] pMeshContainer->pBoneOffsetMatrices;
        pMeshContainer->pBoneOffsetMatrices = NULL;
    }

    // release all the allocated textures
    if (pMeshContainer->ppTextures != NULL)
    {
        for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
        {
            RELEASE( pMeshContainer->ppTextures[iMaterial] );
        }
        delete[] pMeshContainer->ppTextures;
        pMeshContainer->ppTextures = NULL;
    }

    if( pMeshContainer->ppBoneMatrixPtrs )
    {
        delete[] pMeshContainer->ppBoneMatrixPtrs;
        pMeshContainer->ppBoneMatrixPtrs = NULL;
    }

    RELEASE( pMeshContainer->pBoneCombinationBuf );
    RELEASE( pMeshContainer->MeshData.pMesh );
    RELEASE( pMeshContainer->pSkinInfo );
    RELEASE( pMeshContainer->pOrigMesh );

    if( pMeshContainer )
    {
        delete pMeshContainer;
        pMeshContainer = NULL;
    }

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: CAllocateHierarchy::GenerateSkinnedMesh_()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CAllocateHierarchy::GenerateSkinnedMesh_(D3DXMESHCONTAINER_DERIVED *pMeshContainer)
{
    HRESULT hr = S_OK;
    
    if( !pMeshContainer )
    {
        return E_POINTER;
    }

    if (pMeshContainer->pSkinInfo == NULL)
        return hr;

    try
    {
        RELEASE( pMeshContainer->MeshData.pMesh );
        RELEASE( pMeshContainer->pBoneCombinationBuf );

        CHECK_HR(
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
                                   ),
        DbgMsg("CAllocateHierarchy::GenerateSkinnedMesh_: failed in ConvertToBlendedMesh, hr = 0x%08x", hr));

        LPD3DXBONECOMBINATION rgBoneCombinations  = reinterpret_cast<LPD3DXBONECOMBINATION>(
                            pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

        // if there is both HW and SW, add the Software Processing flag
        if (pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups)
        {
            LPD3DXMESH pMeshTmp;

            CHECK_HR(
            hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(
                            D3DXMESH_SOFTWAREPROCESSING | pMeshContainer->MeshData.pMesh->GetOptions(), 
                            pMeshContainer->MeshData.pMesh->GetFVF(),
                            m_pDevice, 
                            &pMeshTmp),
            DbgMsg("CAllocateHierarchy::GenerateSkinnedMesh_: failed in CloneMeshFVF, hr = 0x%08x", hr));

            pMeshContainer->MeshData.pMesh->Release();
            pMeshContainer->MeshData.pMesh = pMeshTmp;
            pMeshTmp = NULL;
        }
    }// try
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    return hr;
}

