//------------------------------------------------------------------------------
// File: Character.h
//
// Desc: DirectShow sample code - MultiVMR9 GamePlayer
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once

// see Direct3D sample 'SkinnedMesh' for more details about frame-hierarchy-related classes

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

//-----------------------------------------------------------------------------
// Name: class CAllocateHierarchy
// Desc: Custom version of ID3DXAllocateHierarchy with custom methods to create
//       frames and meshcontainers.
//-----------------------------------------------------------------------------
class CAllocateHierarchy: public ID3DXAllocateHierarchy
{
public:
    CAllocateHierarchy(IDirect3DDevice9* pDevice);
    virtual ~CAllocateHierarchy();

    STDMETHOD(CreateFrame)(
        THIS_ LPCTSTR Name, 
        LPD3DXFRAME *ppNewFrame
        );

    STDMETHOD(CreateMeshContainer)(
        THIS_ LPCTSTR Name, 
        LPD3DXMESHDATA pMeshData,
        LPD3DXMATERIAL pMaterials, 
        LPD3DXEFFECTINSTANCE pEffectInstances, 
        DWORD NumMaterials, 
        DWORD *pAdjacency, 
        LPD3DXSKININFO pSkinInfo, 
        LPD3DXMESHCONTAINER *ppNewMeshContainer
        );

    STDMETHOD(DestroyFrame)(
        THIS_ LPD3DXFRAME pFrameToFree
        );

    STDMETHOD(DestroyMeshContainer)(
        THIS_ LPD3DXMESHCONTAINER pMeshContainerBase
        );

private:
    HRESULT GenerateSkinnedMesh_(D3DXMESHCONTAINER_DERIVED *pMeshContainer);

    //data
private:
    IDirect3DDevice9 *m_pDevice;
};


//-----------------------------------------------------------------------------
// Name: class CCharacter
// Desc: Representation of the "walking figure".
//-----------------------------------------------------------------------------
class CCharacter
{
public:
    CCharacter();
    virtual ~CCharacter();

    HRESULT Initialize( IDirect3DDevice9 *pDevice );
    HRESULT RestoreDeviceObjects(IDirect3DDevice9* pDevice);
    HRESULT Compose(DWORD t);
    HRESULT Render(IDirect3DDevice9* pDevice);

// private methods
private:
HRESULT SetupBoneMatrixPointers_(LPD3DXFRAME);
HRESULT SetupBoneMatrixPointersOnMesh_(LPD3DXMESHCONTAINER pMeshContainerBase);
HRESULT DrawFrame_(IDirect3DDevice9* pDevice, LPD3DXFRAME pFrame);
HRESULT DrawMeshContainer_(IDirect3DDevice9* pDevice,
                           LPD3DXMESHCONTAINER pMeshContainer, 
                           LPD3DXFRAME pFrame);
HRESULT UpdateFrameMatrices_(LPD3DXFRAME pFrameBase, D3DXMATRIX* pM);


// data
private:
    BOOL                        m_bInitialized;
    LPD3DXFRAME                 m_pFrameRoot;
    IDirect3DDevice9*           m_pDevice;
    ID3DXAnimationController*   m_pAnimController;
    D3DXVECTOR3                 m_vObjectCenter;    // Center of bounding sphere of the character
    D3DXMATRIXA16*              m_pBoneMatrices;
    UINT                        m_NumBoneMatricesMax;
    FLOAT                       m_fObjectRadius;
};

