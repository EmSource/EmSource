// RenderView.cpp : implementation of the CRenderView class
//

#include "stdafx.h"
#include "EffectEdit.h"

#include "EffectDoc.h"
#include "UIElements.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenderView

IMPLEMENT_DYNCREATE(CRenderView, CFormView)

BEGIN_MESSAGE_MAP(CRenderView, CFormView)
    //{{AFX_MSG_MAP(CRenderView)
    ON_WM_SIZE()
    ON_COMMAND(ID_VIEW_RENDER, OnRender)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenderView construction/destruction

CRenderView::CRenderView()
    : CFormView(CRenderView::IDD)
{
    //{{AFX_DATA_INIT(CRenderView)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    // TODO: add construction code here
    m_bShowStats = TRUE;
    m_pFont = NULL;
    m_pEffect = NULL;
    m_pBackgroundTexture = NULL;
    m_dwBackgroundColor = D3DCOLOR_ARGB(0, 0, 0, 255);
    m_pVBBackground = NULL;
    m_iTechnique = -1;
    m_iPass = -1;
    m_strMesh[0] = 0;
    m_pMeshSysMem = NULL;
    m_pbufMaterials = NULL;
    m_dwNumMaterials = 0;
    m_ppTextures = NULL;
    m_strBackgroundTexture[0] = 0;
    m_vObjectCenter = D3DXVECTOR3(0, 0, 0);
    m_fObjectRadius = 1.0f;
    m_pMeshSphere = NULL;
    m_bWireframe = FALSE;
    m_bNoTextures = FALSE;
    m_bSelectedPassOnly = FALSE;
    m_bUpToSelectedPassOnly = FALSE;
    m_bUINeedsReset = TRUE;
}

CRenderView::~CRenderView()
{
    SAFE_RELEASE( m_pEffect );
    Cleanup3DEnvironment();
    SAFE_RELEASE( m_pD3D );
    FinalCleanup();
}

void CRenderView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CRenderView)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BOOL CRenderView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CFormView::PreCreateWindow(cs);
}

//-----------------------------------------------------------------------------
// Name: FullScreenWndProc()
// Desc: The WndProc funtion used when the app is in fullscreen mode. This is
//       needed simply to trap the ESC key.
//-----------------------------------------------------------------------------
LRESULT CALLBACK FullScreenWndProc( HWND hWnd, UINT msg, WPARAM wParam,
                                    LPARAM lParam )
{
    static CRenderView* s_pRenderView = NULL;

    if( msg == WM_CREATE )
    {
        s_pRenderView = (CRenderView*)((CREATESTRUCT*)lParam)->lpCreateParams;
    }
    else if( msg == WM_CLOSE )
    {
        // User wants to exit, so go back to windowed mode and exit for real
        s_pRenderView->OnToggleFullscreen();
        s_pRenderView->GetActiveWindow()->PostMessage( WM_CLOSE, 0, 0 );
        //g_App.GetMainWnd()->PostMessage( WM_CLOSE, 0, 0 );
    }
    else if( msg == WM_SETCURSOR )
    {
        SetCursor( NULL );
    }
    else if( msg == WM_KEYUP && wParam == VK_ESCAPE )
    {
        // User wants to leave fullscreen mode
        s_pRenderView->OnToggleFullscreen();
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


//-----------------------------------------------------------------------------
// Name: AdjustWindowForChange()
// Desc: Adjusts the window properties for windowed or fullscreen mode
//-----------------------------------------------------------------------------
HRESULT CRenderView::AdjustWindowForChange()
{
    if( m_bWindowed )
    {
        ::ShowWindow( m_hwndRenderFullScreen, SW_HIDE );
        CD3DApplication::m_hWnd = m_hwndRenderWindow;
    }
    else
    {
        if( ::IsIconic( m_hwndRenderFullScreen ) )
            ::ShowWindow( m_hwndRenderFullScreen, SW_RESTORE );
        ::ShowWindow( m_hwndRenderFullScreen, SW_SHOW );
        CD3DApplication::m_hWnd = m_hwndRenderFullScreen;
    }
    return S_OK;
}




void CRenderView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();

    // Save static reference to the render window
    m_hwndRenderWindow = GetDlgItem(IDC_RENDERWINDOW)->GetSafeHwnd();

    // Register a class for a fullscreen window
    WNDCLASS wndClass = { CS_HREDRAW | CS_VREDRAW, FullScreenWndProc, 0, 0, NULL,
                          NULL, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL,
                          _T("Fullscreen Window") };
    RegisterClass( &wndClass );

    // We create the fullscreen window (not visible) at startup, so it can
    // be the focus window.  The focus window can only be set at CreateDevice
    // time, not in a Reset, so ToggleFullscreen wouldn't work unless we have
    // already set up the fullscreen focus window.
    m_hwndRenderFullScreen = CreateWindow( _T("Fullscreen Window"), NULL,
                                           WS_POPUP, CW_USEDEFAULT,
                                           CW_USEDEFAULT, 100, 100,
                                           GetTopLevelParent()->GetSafeHwnd(), 0L, NULL, this );

    // Note that for the MFC samples, the device window and focus window
    // are not the same.
    CD3DApplication::m_hWnd = m_hwndRenderWindow;
    CD3DApplication::m_hWndFocus = m_hwndRenderFullScreen;
    CD3DApplication::m_d3dEnumeration.AppUsesDepthBuffer = true;
//    m_bShowCursorWhenFullscreen = true;

    // If we haven't initialized the D3D framework, do so now
    if( !m_bActive )
    {
        CRect rc;
        ::GetClientRect( m_hwndRenderWindow, &rc );
        if( rc.Width() == 0 || rc.Height() == 0 )
        {
            MessageBox( TEXT("The render view must be visible when EffectEdit starts.  Please change the window size or splitters and start EffectEdit again."),
                TEXT("EffectEdit") );
        }
        else
        {
            CD3DApplication::Create( AfxGetInstanceHandle() );
        }
    }
    GetDocument()->Compile();
}

/////////////////////////////////////////////////////////////////////////////
// CRenderView diagnostics

#ifdef _DEBUG
void CRenderView::AssertValid() const
{
    CFormView::AssertValid();
}


void CRenderView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}


CEffectDoc* CRenderView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEffectDoc)));
    return (CEffectDoc*)m_pDocument;
}
#endif //_DEBUG


HRESULT CRenderView::FrameMove()
{
     // Setup world matrix
    D3DXMatrixTranslation( &m_matWorld, -m_vObjectCenter.x,
                                      -m_vObjectCenter.y,
                                      -m_vObjectCenter.z );
    D3DXMatrixMultiply( &m_matWorld, &m_matWorld, m_ArcBall.GetRotationMatrix() );
    D3DXMatrixMultiply( &m_matWorld, &m_matWorld, m_ArcBall.GetTranslationMatrix() );
    m_pd3dDevice->SetTransform( D3DTS_WORLD, &m_matWorld );

    D3DXVECTOR3 vFrom( 0, 0, -2*m_fObjectRadius );
    D3DXVECTOR3 vAt( 0, 0, 0 );
    D3DXVECTOR3 vUp( 0, 1, 0 );
    D3DXMatrixLookAtLH( &m_matView, &vFrom, &vAt, &vUp );
    m_pd3dDevice->SetTransform( D3DTS_VIEW, &m_matView );
    
    m_UIElements.SetMatView( &m_matView );
    m_UIElements.SetObjectRadius( m_fObjectRadius );

    return S_OK;
}


HRESULT CRenderView::Render()
{
    HRESULT hr;

    // Clear the viewport
    m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         m_dwBackgroundColor, 1.0f, 0L );
    if( SUCCEEDED( hr = m_pd3dDevice->BeginScene() ) )
    {
        if( m_pEffect != NULL )
        {
            if( m_pBackgroundTexture != NULL )
            {
                // Render background image
                m_pd3dDevice->SetTexture(0, m_pBackgroundTexture);
                m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
                m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

                m_pd3dDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1);
                m_pd3dDevice->SetStreamSource( 0, m_pVBBackground, 0, 6*sizeof(float) );
                m_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
                
                m_pd3dDevice->SetTexture(0, NULL);
                m_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
            }

            // Render the mesh with the current effect
            if( m_pEffect != NULL )
            {
                if( m_MatWorldEffectHandle != NULL )
                    m_pEffect->SetMatrix( m_MatWorldEffectHandle, &m_matWorld );

                if( m_MatViewEffectHandle != NULL )
                    m_pEffect->SetMatrix( m_MatViewEffectHandle, &m_matView );

                if( m_MatProjEffectHandle != NULL )
                    m_pEffect->SetMatrix( m_MatProjEffectHandle, &m_matProj );

                if( m_MatWorldViewEffectHandle != NULL )
                {
                    D3DXMATRIX matWorldView = m_matWorld * m_matView;
                    m_pEffect->SetMatrix( m_MatWorldViewEffectHandle, &matWorldView );
                }

                if( m_MatViewProjEffectHandle != NULL )
                {
                    D3DXMATRIX matViewProj = m_matView * m_matProj;
                    m_pEffect->SetMatrix( m_MatViewProjEffectHandle, &matViewProj );
                }

                if( m_MatWorldViewProjEffectHandle != NULL )
                {
                    D3DXMATRIX matWorldViewProj = m_matWorld * m_matView * m_matProj;
                    m_pEffect->SetMatrix( m_MatWorldViewProjEffectHandle, &matWorldViewProj );
                }

                if( m_VecCameraPosEffectHandle != NULL )
                {
                    D3DXMATRIXA16 matViewInv;
                    D3DXMatrixInverse( &matViewInv, NULL, &m_matView );
                    D3DXVECTOR4 vecPosition( matViewInv._41, matViewInv._42, matViewInv._43, 1.0f );
                    m_pEffect->SetVector( m_VecCameraPosEffectHandle, &vecPosition );
                }

                if( m_TimeEffectHandle != NULL )
                    m_pEffect->SetFloat( m_TimeEffectHandle, m_fTime );

                if( m_MeshRadiusEffectHandle != NULL )
                    m_pEffect->SetFloat( m_MeshRadiusEffectHandle, m_fObjectRadius );

                m_UIElements.SetEffectParameters( m_pEffect );

                UINT numPasses;
                hr = m_pEffect->Begin( &numPasses, 0 );

                for( UINT iPass = 0; iPass < numPasses; iPass++ )
                {
                    if( m_bSelectedPassOnly )
                        iPass = m_iPass;

                    hr = m_pEffect->Pass( iPass );
                    
                    if( m_bWireframe )
                        m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
                    else
                        m_pd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
                    
                    if( m_bNoTextures )
                    {
                        for( UINT iStage = 0; iStage < m_d3dCaps.MaxTextureBlendStages; iStage++ )
                            m_pd3dDevice->SetTexture( iStage, NULL );
                    }

                    if( m_pMeshSysMem == NULL )
                    {
                        m_pMeshSphere->DrawSubset( 0 );
                    }
                    else
                    {
                        for( UINT i = 0; i < m_dwNumMaterials; i++ )
                        {
                            if( m_MaterialAmbientEffectHandle != NULL )
                                m_pEffect->SetVector( m_MaterialAmbientEffectHandle, (LPD3DXVECTOR4)&m_pMaterials[i].MatD3D.Ambient );
                            if( m_MaterialDiffuseEffectHandle != NULL )
                                m_pEffect->SetVector( m_MaterialDiffuseEffectHandle, (LPD3DXVECTOR4)&m_pMaterials[i].MatD3D.Diffuse );
                            if( m_MaterialSpecularEffectHandle != NULL )
                                m_pEffect->SetVector( m_MaterialSpecularEffectHandle, (LPD3DXVECTOR4)&m_pMaterials[i].MatD3D.Specular );
                            if( m_MaterialSpecularPowerEffectHandle != NULL )
                                m_pEffect->SetFloat( m_MaterialSpecularPowerEffectHandle, m_pMaterials[i].MatD3D.Power );
                            m_pMeshSysMem->DrawSubset( i );
                        }
                    }

                    if( m_bSelectedPassOnly || ( m_bUpToSelectedPassOnly && (int)iPass == m_iPass ) )
                        break;
                }

                hr = m_pEffect->End();

                // Render the UI objects
                m_UIElements.Render();

            }

        }

        if( m_bShowStats )
        {
            // Output statistics
            m_pFont->DrawText( 2,  0, D3DCOLOR_ARGB(255,255,255,0), m_strFrameStats );
            m_pFont->DrawText( 2, 20, D3DCOLOR_ARGB(255,255,255,0), m_strDeviceStats );
            if( m_pEffect == NULL )
                m_pFont->DrawText( 2, 40, D3DCOLOR_XRGB(255,0,0), TEXT("Error in effect file") );

            if( !m_bTechniqueValidValid )
            {
                m_bTechniqueValid = SUCCEEDED( m_pEffect->ValidateTechnique( m_pEffect->GetCurrentTechnique() ) );
                m_bTechniqueValidValid = TRUE;
            }

            if( !m_bTechniqueValid )
                m_pFont->DrawText( 2, 60, D3DCOLOR_ARGB(255, 255, 0, 0), TEXT("Warning: technique not valid with current device settings"));
        }
        // End the scene.
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CRenderView message handlers

void CRenderView::OnSize(UINT nType, int cx, int cy) 
{
    SetScrollSizes( MM_TEXT, CSize(cx, cy) );

    CFormView::OnSize(nType, cx, cy);
    
    CWnd* pGroup = GetDlgItem(IDC_GROUPBOX);
    CWnd* pRenderWnd = GetDlgItem(IDC_RENDERWINDOW);
    CWnd* pRenderText = GetDlgItem(IDC_RENDERTEXT);

    if( pGroup != NULL && 
        pRenderWnd != NULL &&
        pRenderText != NULL )
    {
        CRect rc;
        INT textHeight;
        pRenderText->GetClientRect(&rc);
        textHeight = rc.Height();

        pRenderText->SetWindowPos(NULL, 0, cy - textHeight - 5, cx, textHeight, SWP_NOZORDER);
        pRenderText->Invalidate();
        pGroup->SetWindowPos(NULL, 7, 2, cx - 7 - 4, cy - textHeight - 2 - 10, SWP_NOZORDER);

        pGroup->GetClientRect(&rc);
        pGroup->MapWindowPoints(this, &rc);


        RECT rcClientOld = m_rcWindowClient;
        
        rc.InflateRect( -10, -17, -10, -10 );
        pRenderWnd->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);

        if( m_pd3dDevice != NULL )
        {
            pRenderWnd->GetClientRect( &m_rcWindowClient );

            if( rcClientOld.right - rcClientOld.left !=
                m_rcWindowClient.right - m_rcWindowClient.left ||
                rcClientOld.bottom - rcClientOld.top !=
                m_rcWindowClient.bottom - m_rcWindowClient.top)
            {
                // If client is too small, don't try to Reset until it gets bigger
                if( m_rcWindowClient.right - m_rcWindowClient.left > 4 &&
                    m_rcWindowClient.bottom - m_rcWindowClient.top > 4 )
                {
                    // A new window size will require a new backbuffer
                    // size, so the 3D structures must be changed accordingly.
                    Pause( true );

                    m_d3dpp.BackBufferWidth  = m_rcWindowClient.right - m_rcWindowClient.left;
                    m_d3dpp.BackBufferHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;

                    // Reset the 3D environment
                    if( FAILED( Reset3DEnvironment() ) )
                    {
                        DisplayErrorMsg( D3DAPPERR_RESETFAILED, MSGERR_APPMUSTEXIT );
                    }
                    Pause( false );
                }
            }
        }
    }
}

void CRenderView::OnRender() 
{
    if( m_pd3dDevice != NULL )
        Render3DEnvironment();
}

HRESULT CRenderView::OneTimeSceneInit()
{
    m_pFont = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    if( m_pFont == NULL )
        return E_FAIL;

    return S_OK;
}

HRESULT CRenderView::InitDeviceObjects()
{
    HRESULT hr;
    
    if( FAILED( hr = m_pFont->InitDeviceObjects( m_pd3dDevice ) ) )
        return hr;

    if( FAILED( hr = D3DXCreateSphere( m_pd3dDevice, 1.0f, 40, 40, &m_pMeshSphere, NULL ) ) )
        return hr;

    if( FAILED( hr = m_UIElements.InitDeviceObjects( m_pd3dDevice ) ) )
        return hr;

    if( GetDocument()->GetCode().GetLength() > 0 )
        GetDocument()->Compile( true );

    return S_OK;
}

HRESULT CRenderView::DeleteDeviceObjects()
{
    m_pFont->DeleteDeviceObjects();
    SAFE_RELEASE( m_pBackgroundTexture );
    SAFE_RELEASE( m_pMeshSphere );
    m_UIElements.DeleteDeviceObjects();
    UnloadMesh();
    SAFE_RELEASE( m_pEffect );

    return S_OK;
}


HRESULT CRenderView::RestoreDeviceObjects()
{
    HRESULT hr;
    
    if( FAILED( hr = m_pFont->RestoreDeviceObjects() ) )
        return hr;

    if( FAILED( hr = m_UIElements.RestoreDeviceObjects() ) )
        return hr;

    // Build background image vertex buffer
    if ( FAILED( hr = m_pd3dDevice->CreateVertexBuffer( 6*sizeof(float)*4, 0,
        D3DFVF_XYZRHW | D3DFVF_TEX1, D3DPOOL_MANAGED, &m_pVBBackground, NULL ) ) )
    {
        return hr;
    }

    //set up a set of points which represents the screen
    static struct { float x,y,z,w; float u,v; } s_Verts[] =
    {
        {750.0f,  -0.5f, 0.5f, 1.0f, 1,0},
        {750.0f, 750.0f, 0.5f, 1.0f, 1,1},
        { -0.5f,  -0.5f, 0.5f, 1.0f, 0,0},
        { -0.5f, 750.0f, 0.5f, 1.0f, 0,1},
    };

    s_Verts[0].x = (float)m_d3dsdBackBuffer.Width - 0.5f;
    s_Verts[1].x = (float)m_d3dsdBackBuffer.Width - 0.5f;
    s_Verts[1].y = (float)m_d3dsdBackBuffer.Height - 0.5f;
    s_Verts[3].y = (float)m_d3dsdBackBuffer.Height - 0.5f; 
 
    //copy them into the buffer
    void *pVerts;
    if ( FAILED(hr = m_pVBBackground->Lock( 0, sizeof(s_Verts), (void**)&pVerts, 0 )) )
        return hr;

    memcpy( pVerts, s_Verts, sizeof(s_Verts) );

    m_pVBBackground->Unlock();

    if( m_pEffect != NULL )
        m_pEffect->OnResetDevice();

    // Setup the arcball parameters
    m_ArcBall.SetWindow( m_d3dsdBackBuffer.Width, m_d3dsdBackBuffer.Height, 0.85f );

    // Setup the projection matrix
    FLOAT      fAspect = (FLOAT)m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4, fAspect, 
                                m_fObjectRadius/64.0f, m_fObjectRadius*64.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );

    /*
    D3DLIGHT9 light;
    ZeroMemory( &light, sizeof(light) );
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r = 1.0;
    light.Diffuse.g = 1.0;
    light.Diffuse.b = 1.0;
    light.Diffuse.a = 1.0;
    light.Specular.r = 0.25f;
    light.Specular.g = 0.25f;
    light.Specular.b = 0.25f;
    light.Specular.a = 1.0f;
    light.Ambient.r = 0.15f;
    light.Ambient.g = 0.15f;
    light.Ambient.b = 0.15f;   
    light.Ambient.a = 1.0f;   
    light.Direction = D3DXVECTOR3(0.707f, 0.0f, .707f);
    hr = m_pd3dDevice->SetLight( 0, &light );
    if( FAILED( hr ) )
        return hr;
    m_pd3dDevice->LightEnable( 0, TRUE );
*/

    m_UIElements.SetInfo( m_d3dsdBackBuffer.Width, m_d3dsdBackBuffer.Height, &m_matProj );

    return S_OK;
}


HRESULT CRenderView::InvalidateDeviceObjects()
{
    m_pFont->InvalidateDeviceObjects();

    m_UIElements.InvalidateDeviceObjects();
    
    SAFE_RELEASE( m_pVBBackground );

    if( m_pEffect != NULL )
        m_pEffect->OnLostDevice();

    return S_OK;
}


HRESULT CRenderView::FinalCleanup()
{
    SAFE_DELETE( m_pFont );
    return S_OK;
}

// Helper class for D3DXCreateEffect() to be able to load include files
class CIncludeManager : public ID3DXInclude
{
protected:
    CRenderView* m_pView;

public:
    CIncludeManager( CRenderView* pView ) { m_pView = pView; }
    STDMETHOD(Open)(D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes);
    STDMETHOD(Close)(LPCVOID pData);
};


HRESULT CIncludeManager::Open(D3DXINCLUDE_TYPE IncludeType, LPCSTR pName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
{
    CFile f;
    TCHAR strFile[MAX_PATH];
    TCHAR strFileFull[MAX_PATH];

    DXUtil_ConvertAnsiStringToGenericCch( strFile, pName, MAX_PATH );

    if( FAILED( m_pView->EE_FindMediaFileCb( strFileFull, sizeof(strFileFull), strFile ) ) )
        return E_FAIL;

    if( !f.Open( strFileFull, CFile::modeRead ) ) 
        return E_FAIL;

    INT_PTR size = (INT_PTR)f.GetLength();

    BYTE* pData = new BYTE[size];
    if( pData == NULL )
        return E_OUTOFMEMORY;

    f.Read( pData, size );

    *ppData = pData;
    *pBytes = size;

    return S_OK;
}


HRESULT CIncludeManager::Close(LPCVOID pData)
{
    BYTE* pData2 = (BYTE*)pData;
    SAFE_DELETE_ARRAY( pData2 );
    return S_OK;
}


HRESULT CRenderView::CompileEffect(CString strEffect, BOOL bUseShaderOptimizations, BOOL bFromFile, CString &strErrors, 
                                   CStringList& techniqueNameList, int* piTechnique, BOOL* pbTryLater)
{
    HRESULT hr = S_OK;
    LPD3DXBUFFER pBufferErrors = NULL;
    CIncludeManager includeManager(this);

    *pbTryLater = FALSE;

    if( m_pd3dDevice == NULL )
    {
        *pbTryLater = TRUE;
        return E_FAIL;
    }

    SAFE_RELEASE( m_pEffect );
    m_MatWorldEffectHandle = NULL;
    m_MatViewEffectHandle = NULL;
    m_MatProjEffectHandle = NULL;
    m_MatWorldViewEffectHandle = NULL;
    m_MatViewProjEffectHandle = NULL;
    m_MatWorldViewProjEffectHandle = NULL;
    m_VecCameraPosEffectHandle = NULL;
    m_MaterialAmbientEffectHandle = NULL;
    m_MaterialDiffuseEffectHandle = NULL;
    m_MaterialSpecularEffectHandle = NULL;
    m_MaterialSpecularPowerEffectHandle = NULL;
    m_TimeEffectHandle = NULL;
    m_MeshRadiusEffectHandle = NULL;

    if( m_bUINeedsReset )
    {
        m_UIElements.DeleteAllElements();
        ResetCamera();
        UnloadMesh();
        m_fObjectRadius = 1.0f;
        m_vObjectCenter.x = 0;
        m_vObjectCenter.y = 0;
        m_vObjectCenter.z = 0;
        // Adjust near/far clip planes of projection matrix based on the object radius
        FLOAT fAspect = (FLOAT)m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
        D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4, fAspect, 
                                    m_fObjectRadius/64.0f, m_fObjectRadius*64.0f );
        m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );
        m_bUINeedsReset = FALSE;
    }
    else
    {
        // Delete all effect handles inside UI elements, but keep their other state
        m_UIElements.DeleteEffectObjects();
    }

    techniqueNameList.RemoveAll();
    GetDlgItem(IDC_RENDERTEXT)->SetWindowText( TEXT("(nothing to render)") );

    DWORD dwFlags = D3DXSHADER_DEBUG;
    if( !bUseShaderOptimizations )
        dwFlags |= D3DXSHADER_SKIPOPTIMIZATION;

    if( !bFromFile )
    {
        UINT EffectLength = strEffect.GetLength();
        char* strEffectA = new char[EffectLength + 1];
        if( strEffectA == NULL )
            return E_OUTOFMEMORY;
        DXUtil_ConvertGenericStringToAnsiCch( strEffectA, (LPCTSTR)strEffect, EffectLength + 1 );
        
        hr = D3DXCreateEffect( m_pd3dDevice, strEffectA, EffectLength, NULL, 
            &includeManager, dwFlags, NULL, &m_pEffect, &pBufferErrors );

        delete[] strEffectA;
    }
    else
    {
        hr = D3DXCreateEffectFromFile( m_pd3dDevice, strEffect, NULL, &includeManager, dwFlags, NULL, &m_pEffect, &pBufferErrors );
    }

    if( pBufferErrors != NULL )
        strErrors = (CHAR*)pBufferErrors->GetBufferPointer();
    else
        strErrors.Empty();

    if( strErrors.IsEmpty() )
        strErrors = TEXT("Effect compilation successful\n");

    SAFE_RELEASE( pBufferErrors );

    if( m_pEffect != NULL )
    {
        m_pEffect->GetDesc( &m_EffectDesc );

        ParseParameters( strErrors );

        // Look for UI elements
        m_UIElements.InitEffectObjects( m_pEffect );

        if( m_EffectDesc.Techniques == 0 )
            m_iTechnique = -1;
        else if( (UINT)m_iTechnique >= m_EffectDesc.Techniques )
            m_iTechnique = 0;
        else if( m_iTechnique == -1 )
            m_iTechnique = 0;
        *piTechnique = m_iTechnique;

        for( UINT iTech = 0; iTech < m_EffectDesc.Techniques; iTech++ )
        {
            D3DXTECHNIQUE_DESC desc;
            m_pEffect->GetTechniqueDesc( m_pEffect->GetTechnique( iTech ), &desc );
            techniqueNameList.AddTail(desc.Name);
        }
    }

    return hr;
}


HRESULT CRenderView::ParseParameters(CString &strErrors)
{
    HRESULT hr;
    D3DXPARAMETER_DESC Desc;

    if( m_pEffect == NULL )
        return E_FAIL;

    //look for background Texture
    const char* pstrBackTexture;
    SAFE_RELEASE( m_pBackgroundTexture );
    if( NULL != m_pEffect->GetParameterByName( NULL, "BIMG" ) &&
        SUCCEEDED( m_pEffect->GetParameterDesc( "BIMG", &Desc ) ) )
    {
        m_pEffect->GetString("BIMG", &pstrBackTexture);
        TCHAR strBackTexture[MAX_PATH];
        DXUtil_ConvertAnsiStringToGenericCch( strBackTexture, pstrBackTexture, MAX_PATH );
        TCHAR strPath[MAX_PATH];
        EE_FindMediaFileCb( strPath, sizeof(strPath), strBackTexture );
        if( FAILED( hr = D3DXCreateTextureFromFile( m_pd3dDevice, strPath, &m_pBackgroundTexture) ) )
        {
            strErrors += TEXT("Could not load background image texture ");
            strErrors += strBackTexture;
            strErrors += TEXT("\n");
        }
    }

    // Look at parameters for semantics and annotations that we know how to interpret
    D3DXPARAMETER_DESC ParamDesc;
    D3DXPARAMETER_DESC AnnotDesc;
    D3DXHANDLE hParam;
    D3DXHANDLE hAnnot;
    TCHAR strPath[MAX_PATH];
    LPDIRECT3DBASETEXTURE9 pTex = NULL;

    for( UINT iParam = 0; iParam < m_EffectDesc.Parameters; iParam++ )
    {
        LPCSTR pstrName = NULL;
        LPCSTR pstrFunction = NULL;
        LPCSTR pstrTarget = NULL;
        LPCSTR pstrTextureType = NULL;
        INT Width = D3DX_DEFAULT;
        INT Height= D3DX_DEFAULT;
        INT Depth = D3DX_DEFAULT;

        hParam = m_pEffect->GetParameter ( NULL, iParam );
        m_pEffect->GetParameterDesc( hParam, &ParamDesc );
        if( ParamDesc.Semantic != NULL && 
            ( ParamDesc.Class == D3DXPC_MATRIX_ROWS || ParamDesc.Class == D3DXPC_MATRIX_COLUMNS ) )
        {
            if( strcmpi( ParamDesc.Semantic, "world" ) == 0 )
                m_MatWorldEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "view" ) == 0 )
                m_MatViewEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "projection" ) == 0 )
                m_MatProjEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "worldview" ) == 0 )
                m_MatWorldViewEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "viewprojection" ) == 0 )
                m_MatViewProjEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "worldviewprojection" ) == 0 )
                m_MatWorldViewProjEffectHandle = hParam;
        }

        if( ParamDesc.Semantic != NULL && 
            ( ParamDesc.Class == D3DXPC_VECTOR ))
        {
            if( strcmpi( ParamDesc.Semantic, "materialambient" ) == 0 )
                m_MaterialAmbientEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "materialdiffuse" ) == 0 )
                m_MaterialDiffuseEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "materialspecular" ) == 0 )
                m_MaterialSpecularEffectHandle = hParam;
        }

        if( ParamDesc.Semantic != NULL && 
            ( ParamDesc.Class == D3DXPC_SCALAR ))
        {
            if( strcmpi( ParamDesc.Semantic, "materialpower" ) == 0 )
                m_MaterialSpecularPowerEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "time" ) == 0 )
                m_TimeEffectHandle = hParam;
            else if( strcmpi( ParamDesc.Semantic, "meshradius" ) == 0 )
                m_MeshRadiusEffectHandle = hParam;
        }

        for( UINT iAnnot = 0; iAnnot < ParamDesc.Annotations; iAnnot++ )
        {
            hAnnot = m_pEffect->GetAnnotation ( hParam, iAnnot );
            m_pEffect->GetParameterDesc( hAnnot, &AnnotDesc );
            if( strcmpi( AnnotDesc.Name, "name" ) == 0 )
                m_pEffect->GetString( hAnnot, &pstrName );
            else if ( strcmpi( AnnotDesc.Name, "function" ) == 0 )
                m_pEffect->GetString( hAnnot, &pstrFunction );
            else if ( strcmpi( AnnotDesc.Name, "target" ) == 0 )
                m_pEffect->GetString( hAnnot, &pstrTarget );
            else if ( strcmpi( AnnotDesc.Name, "width" ) == 0 )
                m_pEffect->GetInt( hAnnot, &Width );
            else if ( strcmpi( AnnotDesc.Name, "height" ) == 0 )
                m_pEffect->GetInt( hAnnot, &Height );
            else if ( strcmpi( AnnotDesc.Name, "depth" ) == 0 )
                m_pEffect->GetInt( hAnnot, &Depth );
            else if( strcmpi( AnnotDesc.Name, "type" ) == 0 )
                m_pEffect->GetString( hAnnot, &pstrTextureType );

        }
        if( pstrName != NULL )
        {
            pTex = NULL;
            TCHAR strName[MAX_PATH];
            DXUtil_ConvertAnsiStringToGenericCch( strName, pstrName, MAX_PATH );
            EE_FindMediaFileCb( strPath, sizeof(strPath), strName );
            if (pstrTextureType != NULL) 
            {
                if( strcmpi( pstrTextureType, "volume" ) == 0 )
                {
                    LPDIRECT3DVOLUMETEXTURE9 pVolumeTex = NULL;
                    if( SUCCEEDED( hr = D3DXCreateVolumeTextureFromFileEx( m_pd3dDevice, strPath, 
                        Width, Height, Depth, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
                        D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pVolumeTex ) ) )
                    {
                        pTex = pVolumeTex;
                    }
                    else
                    {
                        strErrors += TEXT("Could not load volume texture ");
                        strErrors += strName;
                        strErrors += TEXT("\n");
                    }
                }
                else if( strcmpi( pstrTextureType, "cube" ) == 0 )
                {
                    LPDIRECT3DCUBETEXTURE9 pCubeTex = NULL;
                    if( SUCCEEDED( hr = D3DXCreateCubeTextureFromFileEx( m_pd3dDevice, strPath, 
                        Width, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
                        D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pCubeTex ) ) )
                    {
                        pTex = pCubeTex;
                    }
                    else
                    {
                        strErrors += TEXT("Could not load cube texture ");
                        strErrors += strName;
                        strErrors += TEXT("\n");
                    }
                }
            }
            else
            {
                LPDIRECT3DTEXTURE9 p2DTex = NULL;
                if( SUCCEEDED( hr = D3DXCreateTextureFromFileEx( m_pd3dDevice, strPath, 
                    Width, Height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
                    D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &p2DTex ) ) )
                {
                    pTex = p2DTex;
                }
                else
                {
                    strErrors += TEXT("Could not load texture ");
                    strErrors += strName;
                    strErrors += TEXT("\n");
                }
            }

            // Apply successfully loaded texture to effect
            if( SUCCEEDED(hr) && pTex != NULL ) 
            {
                m_pEffect->SetTexture( m_pEffect->GetParameter( NULL, iParam ), pTex );
                SAFE_RELEASE( pTex );
            }
        }
        else if( pstrFunction != NULL )
        {
            LPD3DXBUFFER pTextureShader = NULL;
            CIncludeManager includeManager(this);
            CString strEffect = GetDocument()->GetCode();
            UINT EffectLength = strEffect.GetLength();
            char* strEffectA = new char[EffectLength + 1];
            if( strEffectA == NULL )
                return E_OUTOFMEMORY;
            DXUtil_ConvertGenericStringToAnsiCch( strEffectA, (LPCTSTR)strEffect, EffectLength + 1 );

            if( pstrTarget == NULL )
                pstrTarget = "tx_1_0";

            if( SUCCEEDED( hr = D3DXCompileShader( strEffectA, strlen(strEffectA), NULL, 
                &includeManager, pstrFunction, pstrTarget, 0, &pTextureShader, NULL, NULL ) ) )
            {
                if( Width == D3DX_DEFAULT )
                    Width = 64;
                if( Height == D3DX_DEFAULT )
                    Height = 64;
                if( Depth == D3DX_DEFAULT )
                    Depth = 64;

                if (pstrTextureType != NULL) 
                {
                    if( strcmpi( pstrTextureType, "volume" ) == 0 )
                    {
                        LPDIRECT3DVOLUMETEXTURE9 pVolumeTex = NULL;
                        if( SUCCEEDED( hr = D3DXCreateVolumeTexture( m_pd3dDevice, 
                            Width, Height, Depth, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pVolumeTex) ) )
                        {
                            if( SUCCEEDED( hr = D3DXFillVolumeTextureTX( pVolumeTex, 
                                (DWORD *)pTextureShader->GetBufferPointer(), NULL, 0 ) ) )
                            {
                                pTex = pVolumeTex;
                            }
                        }
                    }
                    else if( strcmpi( pstrTextureType, "cube" ) == 0 )
                    {
                        LPDIRECT3DCUBETEXTURE9 pCubeTex = NULL;
                        if( SUCCEEDED( hr = D3DXCreateCubeTexture( m_pd3dDevice, 
                            Width, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pCubeTex) ) )
                        {
                            if( SUCCEEDED( hr = D3DXFillCubeTextureTX( pCubeTex,
                                (DWORD *)pTextureShader->GetBufferPointer(), NULL, 0 ) ) )
                            {
                                pTex = pCubeTex;
                            }
                        }
                    }
                }
                else
                {
                    LPDIRECT3DTEXTURE9 p2DTex = NULL;
                    if( SUCCEEDED( hr = D3DXCreateTexture( m_pd3dDevice, Width, Height, 
                        D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &p2DTex) ) )
                    {
                        if( SUCCEEDED( hr = D3DXFillTextureTX( p2DTex, 
                            (DWORD *)pTextureShader->GetBufferPointer(), NULL, 0 ) ) )
                        {
                            pTex = p2DTex;
                        }
                    }
                }
                m_pEffect->SetTexture( m_pEffect->GetParameter( NULL, iParam ), pTex );
                SAFE_RELEASE(pTex);
                SAFE_RELEASE(pTextureShader);
            }

            delete[] strEffectA;
        }
    }

    //look for background Color
    if( NULL != m_pEffect->GetParameterByName( NULL, "BCLR" ) &&
        SUCCEEDED( m_pEffect->GetParameterDesc( "BCLR", &Desc ) ) )
        m_pEffect->GetInt("BCLR", (INT *)&m_dwBackgroundColor);
    else
        m_dwBackgroundColor = D3DCOLOR_ARGB(255, 0, 0, 255);


    // look for mesh
    if( NULL != m_pEffect->GetParameterByName( NULL, "XFile" ) &&
        SUCCEEDED( m_pEffect->GetParameterDesc( "XFile", &Desc ) ) )
    {
        const char *fileName;
    
        m_pEffect->GetString("XFile",&fileName);
        if( strcmpi( fileName, m_strMesh ) != 0 || m_pMeshSysMem == NULL )
        {
            UnloadMesh();
            strcpy( m_strMesh, fileName ); 
            
            //load the mesh
            LoadMesh( strErrors );
        }
    }
    else
    {
        if( strlen(m_strMesh) > 0 )
        {
            // There used to be an XFile, but no longer
            UnloadMesh();
            m_strMesh[0] = NULL;
        }
    }
    BOOL bUsesTangents = FALSE;

    // Look for tangents semantic
    D3DXEFFECT_DESC EffectDesc;
    D3DXHANDLE hTechnique;
    D3DXTECHNIQUE_DESC TechniqueDesc;
    D3DXHANDLE hPass;
    D3DXPASS_DESC PassDesc;

    m_pEffect->GetDesc( &EffectDesc );
    for( UINT iTech = 0; iTech < EffectDesc.Techniques; iTech++ )
    {
        hTechnique = m_pEffect->GetTechnique( iTech );
        m_pEffect->GetTechniqueDesc( hTechnique, &TechniqueDesc );
        for( UINT iPass = 0; iPass < TechniqueDesc.Passes; iPass++ )
        {
            hPass = m_pEffect->GetPass( hTechnique, iPass );
            m_pEffect->GetPassDesc( hPass, &PassDesc );
            for( UINT iSem = 0; iSem < PassDesc.VSSemanticsUsed; iSem++ )
            {
                if( PassDesc.VSSemantics[iSem].Usage == D3DDECLUSAGE_TANGENT )
                {
                    bUsesTangents = TRUE;
                    goto DoneLooking;
                }
            }
        }
    }

DoneLooking:
    if( bUsesTangents && m_pMeshSysMem != NULL )
    {
        D3DVERTEXELEMENT9 Declaration[MAX_FVF_DECL_SIZE];
        D3DVERTEXELEMENT9 End = D3DDECL_END();
        int iElem;
     
        m_pMeshSysMem->GetDeclaration( Declaration );
     
        BOOL bHasTangents = FALSE;
        for( iElem=0; Declaration[iElem].Stream != End.Stream; iElem++ )
        {   
            if( Declaration[iElem].Usage == D3DDECLUSAGE_TANGENT )
            {
                bHasTangents = TRUE;
                break;
            }
        }
     
        // Update Mesh Semantics if changed
        if( !bHasTangents ) 
        {
            Declaration[iElem].Stream = 0;
            Declaration[iElem].Offset = (WORD)m_pMeshSysMem->GetNumBytesPerVertex();
            Declaration[iElem].Type = D3DDECLTYPE_FLOAT3;
            Declaration[iElem].Method = D3DDECLMETHOD_DEFAULT;
            Declaration[iElem].Usage = D3DDECLUSAGE_TANGENT;
            Declaration[iElem].UsageIndex = 0;
            Declaration[iElem+1] = End;
            LPD3DXMESH pTempMesh;
            hr = m_pMeshSysMem->CloneMesh( D3DXMESH_SYSTEMMEM, Declaration, m_pd3dDevice, &pTempMesh );
            if( SUCCEEDED( hr ) )
            {
                SAFE_RELEASE( m_pMeshSysMem );
                m_pMeshSysMem = pTempMesh;
                hr = D3DXComputeTangent( m_pMeshSysMem, 0, 0, D3DX_DEFAULT, TRUE, NULL );
            }
        }
    }

    return S_OK;
}


HRESULT CRenderView::LoadMesh(CString &strErrors)
{
    if( strlen(m_strMesh) == 0 )
        return S_OK;

    LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
    void*      pVertices = NULL;
    LPD3DXMESH pTempMesh;
    TCHAR      strMeshT[MAX_PATH];
    TCHAR      strMeshPath[MAX_PATH];
    HRESULT    hr;

    // Load the mesh from the specified file
    DXUtil_ConvertAnsiStringToGenericCch( strMeshT, m_strMesh, MAX_PATH );
    if( FAILED( hr = EE_FindMediaFileCb( strMeshPath, sizeof(strMeshPath), strMeshT ) ) )
    {
        strErrors += TEXT("Could not find XFile ");
        strErrors += strMeshT;
        strErrors += TEXT("\n");
        return hr;
    }

    hr = D3DXLoadMeshFromX( strMeshPath, D3DXMESH_SYSTEMMEM, m_pd3dDevice, 
                            NULL, &m_pbufMaterials, NULL, &m_dwNumMaterials, 
                            &m_pMeshSysMem );
    if( FAILED(hr) )
    {
        strErrors += TEXT("Could not load XFile ");
        strErrors += strMeshT;
        strErrors += TEXT("\n");
        return hr;
    }

    // Lock the vertex buffer, to generate a simple bounding sphere
    hr = m_pMeshSysMem->GetVertexBuffer( &pVB );
    if( FAILED(hr) )
        return hr;

    hr = pVB->Lock( 0, 0, &pVertices, 0 );
    if( FAILED(hr) )
    {
        SAFE_RELEASE( pVB );
        return hr;
    }

    hr = D3DXComputeBoundingSphere( (D3DXVECTOR3*)pVertices, m_pMeshSysMem->GetNumVertices(), 
                                    D3DXGetFVFVertexSize(m_pMeshSysMem->GetFVF()), &m_vObjectCenter, 
                                    &m_fObjectRadius );
    if( FAILED(hr) )
    {
        pVB->Unlock();
        SAFE_RELEASE( pVB );
        return hr;
    }

    // Adjust near/far clip planes of projection matrix based on the object radius
    FLOAT fAspect = (FLOAT)m_d3dsdBackBuffer.Width / (FLOAT)m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4, fAspect, 
                                m_fObjectRadius/64.0f, m_fObjectRadius*64.0f );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );

    m_ArcBall.SetRadius( m_fObjectRadius );

    if( 0 == m_dwNumMaterials )
    {
        pVB->Unlock();
        SAFE_RELEASE( pVB );
        return E_INVALIDARG;
    }

    // Get the array of materials out of the returned buffer, allocate a
    // texture array, and load the textures
    m_pMaterials = (D3DXMATERIAL*)m_pbufMaterials->GetBufferPointer();
    m_ppTextures = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

    for( UINT i=0; i<m_dwNumMaterials; i++ )
    {
        m_ppTextures[i] = NULL;
        TCHAR strTextureName[MAX_PATH];
        TCHAR strTexturePath[MAX_PATH] = _T("");
        if( m_pMaterials[i].pTextureFilename != NULL && strlen( m_pMaterials[i].pTextureFilename ) != 0 )
        {
            DXUtil_ConvertAnsiStringToGenericCch( strTextureName, m_pMaterials[i].pTextureFilename, MAX_PATH );
            if( FAILED( hr = EE_FindMediaFileCb( strTexturePath, sizeof(strTexturePath), strTextureName ) ) )
            {
                strErrors += TEXT("Could not find texture ");
                strErrors += strTextureName;
                strErrors += TEXT(" referenced by XFile ");
                strErrors += strMeshT;
                strErrors += TEXT("\n");
            }
            else if( FAILED( hr = D3DXCreateTextureFromFile( m_pd3dDevice, strTexturePath, &m_ppTextures[i] ) ) )
            {
                strErrors += TEXT("Could not load texture ");
                strErrors += strTextureName;
                strErrors += TEXT(" referenced by XFile ");
                strErrors += strMeshT;
                strErrors += TEXT("\n");
            }
        }
    }

    pVB->Unlock();
    SAFE_RELEASE( pVB );

    // Make sure there are normals, which are required for the tesselation
    // enhancement
    if( !(m_pMeshSysMem->GetFVF() & D3DFVF_NORMAL) )
    {
        hr = m_pMeshSysMem->CloneMeshFVF( m_pMeshSysMem->GetOptions(), 
                                          m_pMeshSysMem->GetFVF() | D3DFVF_NORMAL, 
                                          m_pd3dDevice, &pTempMesh );
        if( FAILED(hr) )
            return hr;

        D3DXComputeNormals( pTempMesh, NULL );

        SAFE_RELEASE( m_pMeshSysMem );
        m_pMeshSysMem = pTempMesh;
    }

    return S_OK;
}


void CRenderView::UnloadMesh()
{
    for( UINT i = 0; i < m_dwNumMaterials; i++ )
        SAFE_RELEASE( m_ppTextures[i] );
    SAFE_DELETE_ARRAY( m_ppTextures );
    SAFE_RELEASE( m_pMeshSysMem );
    SAFE_RELEASE( m_pbufMaterials );
    m_dwNumMaterials = 0L;
    m_strMesh[0] = 0;
}

LRESULT CRenderView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    POINT pt;

    switch( message )
    {
    case WM_LBUTTONDOWN:
        pt.x = GET_X_LPARAM(lParam); 
        pt.y = GET_Y_LPARAM(lParam); 
        ::MapWindowPoints( GetSafeHwnd(), m_hwndRenderWindow, &pt, 1 );
        BOOL bSetCapture;
        m_UIElements.HandleMouseDown( pt.x, pt.y, &bSetCapture );
        if( bSetCapture )
            SetCapture();
        break;

    case WM_MOUSEMOVE:
        pt.x = GET_X_LPARAM(lParam); 
        pt.y = GET_Y_LPARAM(lParam); 
        ::MapWindowPoints( GetSafeHwnd(), m_hwndRenderWindow, &pt, 1 );
        m_UIElements.HandleMouseMove( pt.x, pt.y );
        break;
    case WM_LBUTTONUP:
        m_UIElements.HandleMouseUp();
        break;
    }

    if( !m_UIElements.IsDragging() )
    {
        // Pass mouse messages to the ArcBall so it can build internal matrices
        m_ArcBall.HandleMouseMessages( GetSafeHwnd(), message, wParam, lParam );
    }

    return CFormView::WindowProc(message, wParam, lParam);
}

void CRenderView::ChangeDevice() 
{
    Pause(true);
    UserSelectNewDevice();
    Pause(false);
}


void CRenderView::SetTechnique( int iTech, CString strTechName )
{
    CString str;
    str.Format( TEXT("Rendering using technique '%s'"), strTechName );
    m_iTechnique = iTech;
    GetDlgItem(IDC_RENDERTEXT)->SetWindowText( str );
    D3DXHANDLE hTechnique = m_pEffect->GetTechnique( m_iTechnique );
    m_pEffect->SetTechnique( hTechnique );
    m_bTechniqueValidValid = FALSE;
}


void CRenderView::SetPass( int iPass, CString strPassName )
{
    m_iPass = iPass;
}

void CRenderView::GetPassNameList( int iTech, CStringList& passNameList )
{
    passNameList.RemoveAll();

    if( m_pEffect == NULL )
        return;

    D3DXTECHNIQUE_DESC techniqueDesc;
    D3DXHANDLE hTech;
    hTech = m_pEffect->GetTechnique( iTech );
    m_pEffect->GetTechniqueDesc( hTech, &techniqueDesc );
    for( UINT iPass = 0; iPass < techniqueDesc.Passes; iPass++ )
    {
        D3DXPASS_DESC desc;
        m_pEffect->GetPassDesc( m_pEffect->GetPass( hTech, iPass ), &desc );
        passNameList.AddTail(desc.Name);
    }
}


void CRenderView::ResetCamera()
{
    m_ArcBall.Init();
    m_ArcBall.SetRadius( m_fObjectRadius );
}


BOOL FileExists( CString& strPath )
{
    HANDLE file;

    file = CreateFile( (LPCTSTR)strPath, GENERIC_READ, FILE_SHARE_READ, NULL, 
                       OPEN_EXISTING, 0, NULL );
    if( INVALID_HANDLE_VALUE != file )
    {
        CloseHandle( file );
        return TRUE;
    }
    return FALSE;
}

HRESULT CRenderView::EE_FindMediaFileCb( TCHAR* szDestPath, int cbDest, TCHAR* strFilename )
{
    return EE_FindMediaFileCch( szDestPath, cbDest / sizeof(TCHAR), strFilename );

}

// 1. Look in same dir as effects file (EffectFileDir)
// 2. Look in EffectFileDir\Media
// 3. Look in EffectFileDir\..\Media
// 4. Look in usual DxUtil_FindMediaFile paths
HRESULT CRenderView::EE_FindMediaFileCch( TCHAR* szDestPath, int cchDest, TCHAR* strFilename )
{
    CString strDoc = GetDocument()->GetPathName();
    CString strDocT;
    int iChar = strDoc.ReverseFind( TEXT('\\') );
    if( iChar >= 0 )
    {
        strDoc = strDoc.Left( iChar );

        strDocT = strDoc + TEXT("\\") + strFilename;
        if( FileExists( strDocT) )
        {
            _tcsncpy( szDestPath, strDocT, cchDest );
            szDestPath[cchDest-1] = 0; // _tcsncpy doesn't NULL term if it runs out of space
            return S_OK;
        }

        strDocT = strDoc + TEXT("\\Media\\") + strFilename;
        if( FileExists( strDocT) )
        {
            _tcsncpy( szDestPath, strDocT, cchDest );
            szDestPath[cchDest-1] = 0; // _tcsncpy doesn't NULL term if it runs out of space
            return S_OK;
        }

        strDocT = strDoc + TEXT("\\..\\Media\\" + strFilename);
        if( FileExists( strDocT) )
        {
            _tcsncpy( szDestPath, strDocT, cchDest );
            szDestPath[cchDest-1] = 0; // _tcsncpy doesn't NULL term if it runs out of space
            return S_OK;
        }
    }
    return DXUtil_FindMediaFileCch( szDestPath, cchDest, strFilename );
}

