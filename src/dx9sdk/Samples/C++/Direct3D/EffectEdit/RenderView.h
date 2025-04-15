// RenderView.h : interface of the CRenderView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RENDERVIEW_H__204F6922_00F7_44FD_8F0D_61EC78118D87__INCLUDED_)
#define AFX_RENDERVIEW_H__204F6922_00F7_44FD_8F0D_61EC78118D87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRenderView : public CFormView, public CD3DApplication
{
protected: // create from serialization only
    CRenderView();
    DECLARE_DYNCREATE(CRenderView)

public:
    //{{AFX_DATA(CRenderView)
    enum{ IDD = IDD_RENDER_FORM };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

// Attributes
public:
    CEffectDoc* GetDocument();

// Operations
public:
    void SetTechnique( int iTech, CString strTechName );
    void SetPass( int iPass, CString strPassName );
    void GetPassNameList( int iTech, CStringList& passNameList );
    void ResetCamera();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRenderView)
    public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnInitialUpdate(); // called first time after construct
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL

// Implementation
public:
    HRESULT CompileEffect(CString strEffect, BOOL bUseShaderOptimizations, BOOL bFromFile, CString& strErrors, CStringList& techniqueNameList, int* piTechnique, BOOL* pbTryLater);
    HRESULT ParseParameters(CString &strErrors);
    HRESULT LoadMesh(CString &strErrors);
    void    UnloadMesh();
    void    ShowStats( BOOL bShowStats ) { m_bShowStats = bShowStats; }
    void    SetWireframe( BOOL bWireframe ) { m_bWireframe = bWireframe; }
    void    SetNoTextures( BOOL bNoTextures ) { m_bNoTextures = bNoTextures; }
    void    SetSelectedPassOnly( BOOL bSelectedPassOnly ) { m_bSelectedPassOnly = bSelectedPassOnly; }
    void    SetUpToSelectedPassOnly( BOOL bUpToSelectedPassOnly ) { m_bUpToSelectedPassOnly = bUpToSelectedPassOnly; }
    BOOL    GetShowStats() { return m_bShowStats; }
    void    RequestUIReset() { m_bUINeedsReset = TRUE; }
    virtual ~CRenderView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    void OnToggleFullscreen(void) { ToggleFullscreen(); }
    virtual HRESULT AdjustWindowForChange();
    virtual HRESULT FrameMove();
    virtual HRESULT Render();
    virtual HRESULT OneTimeSceneInit();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT InvalidateDeviceObjects();
    HRESULT FinalCleanup();

    void ChangeDevice();
    HRESULT EE_FindMediaFileCb( TCHAR* szDestPath, int cbDest, TCHAR* strFilename );
    HRESULT EE_FindMediaFileCch( TCHAR* szDestPath, int cchDest, TCHAR* strFilename );

protected:
    BOOL m_bShowStats;
    BOOL m_bWireframe;
    BOOL m_bNoTextures;
    BOOL m_bSelectedPassOnly;
    BOOL m_bUpToSelectedPassOnly;
    BOOL m_bUINeedsReset;
    CD3DFont* m_pFont;
    CD3DArcBall m_ArcBall;          // mouse rotation utility

    D3DXMATRIX m_matWorld;
    D3DXMATRIX m_matView;
    D3DXMATRIX m_matProj;

    // Effect
    ID3DXEffect* m_pEffect;
    D3DXEFFECT_DESC m_EffectDesc;
    int m_iTechnique;
    int m_iPass;
    BOOL m_bTechniqueValid;
    BOOL m_bTechniqueValidValid;
    D3DXHANDLE m_MatWorldEffectHandle;
    D3DXHANDLE m_MatViewEffectHandle;
    D3DXHANDLE m_MatProjEffectHandle;
    D3DXHANDLE m_MatWorldViewEffectHandle;
    D3DXHANDLE m_MatViewProjEffectHandle;
    D3DXHANDLE m_MatWorldViewProjEffectHandle;
    D3DXHANDLE m_VecCameraPosEffectHandle;
    D3DXHANDLE m_MaterialAmbientEffectHandle;
    D3DXHANDLE m_MaterialDiffuseEffectHandle;
    D3DXHANDLE m_MaterialSpecularEffectHandle;
    D3DXHANDLE m_MaterialSpecularPowerEffectHandle;
    D3DXHANDLE m_TimeEffectHandle;
    D3DXHANDLE m_MeshRadiusEffectHandle;

    LPD3DXMESH m_pMeshSphere;

    CUIElements m_UIElements;

    // XFile
    char m_strMesh[MAX_PATH];
    LPD3DXMESH          m_pMeshSysMem;
    D3DXMATERIAL*       m_pMaterials;
    LPDIRECT3DTEXTURE9* m_ppTextures;
    DWORD               m_dwNumMaterials;
    LPD3DXBUFFER        m_pbufMaterials;    // contains both the materials data and the filename strings
    D3DXVECTOR3         m_vObjectCenter;    // Center of bounding sphere of object
    FLOAT               m_fObjectRadius;    // Radius of bounding sphere of object

    // Scene background
    char m_strBackgroundTexture[MAX_PATH];
    LPDIRECT3DTEXTURE9 m_pBackgroundTexture;    
    DWORD m_dwBackgroundColor;
    LPDIRECT3DVERTEXBUFFER9 m_pVBBackground;


// Generated message map functions
protected:
    HWND m_hwndRenderFullScreen;
    HWND m_hwndRenderWindow;
    //{{AFX_MSG(CRenderView)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnRender();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RenderView.cpp
inline CEffectDoc* CRenderView::GetDocument()
   { return (CEffectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENDERVIEW_H__204F6922_00F7_44FD_8F0D_61EC78118D87__INCLUDED_)
