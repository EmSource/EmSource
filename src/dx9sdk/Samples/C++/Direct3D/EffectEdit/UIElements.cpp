// UIElements.cpp : implementation file
//

#include "stdafx.h"
#include "effectedit.h"
#include "UIElements.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUIElements

CUIElements::CUIElements()
{
    m_pd3dDevice = NULL;
    m_pMeshArrow = NULL;
    m_pEffect = NULL;
    m_pd3dFont = NULL;
    m_fObjectRadius = 1.0f;
}

CUIElements::~CUIElements()
{
    DeleteAllElements();
    SAFE_RELEASE( m_pd3dDevice );
    SAFE_DELETE( m_pd3dFont );
}

HRESULT CUIElements::InitDeviceObjects( LPDIRECT3DDEVICE9 pd3dDevice )
{
    SAFE_RELEASE( m_pd3dDevice );
    m_pd3dDevice = pd3dDevice;
    m_pd3dDevice->AddRef();

    if( m_pd3dFont == NULL )
        m_pd3dFont = new CD3DFont( TEXT("Arial"), 9, D3DFONT_BOLD );
    m_pd3dFont->InitDeviceObjects( pd3dDevice );

    D3DXLoadMeshFromXResource( NULL, (LPCSTR)MAKEINTRESOURCE(IDR_ARROW_X), "X", D3DXMESH_MANAGED, 
        m_pd3dDevice, NULL, NULL, NULL, NULL, &m_pMeshArrow );
    D3DXCreateEffectFromResource( m_pd3dDevice, NULL, MAKEINTRESOURCE(IDR_UIELEMENT_FX),
        NULL, NULL, 0, NULL, &m_pEffect, NULL );

    return S_OK;
}

HRESULT CUIElements::RestoreDeviceObjects()
{
    if( m_pEffect != NULL )
        m_pEffect->OnResetDevice();
    m_pd3dFont->RestoreDeviceObjects();
    return S_OK;
}

void CUIElements::InvalidateDeviceObjects()
{
    if( m_pEffect != NULL )
        m_pEffect->OnLostDevice();
    m_pd3dFont->InvalidateDeviceObjects();
}

void CUIElements::DeleteDeviceObjects()
{
    DeleteEffectObjects();
    SAFE_RELEASE( m_pMeshArrow );
    SAFE_RELEASE( m_pEffect );
    SAFE_RELEASE( m_pd3dDevice );
    m_pd3dFont->DeleteDeviceObjects();
}

void CUIElements::SetInfo( UINT bbWidth, UINT bbHeight, D3DXMATRIX* pMatProj )
{
    m_bbWidth = bbWidth;
    m_bbHeight = bbHeight;
    m_matProj = *pMatProj;
}

void CUIElements::SetMatView( D3DXMATRIX* pMatView )
{
    m_matView = *pMatView;
}

HRESULT CUIElements::RenderArrow( BOOL bSelected )
{
    UINT numPasses;
    if( bSelected )
        m_pEffect->SetTechnique( m_pEffect->GetTechniqueByName("Selected") );
    else
        m_pEffect->SetTechnique( m_pEffect->GetTechniqueByName("Unselected") );
    m_pEffect->Begin( &numPasses, 0 );
    for( UINT iPass = 0; iPass < numPasses; iPass++ )
    {
        m_pEffect->Pass( iPass );
        m_pMeshArrow->DrawSubset( 0 );
        m_pMeshArrow->DrawSubset( 1 );
    }
    m_pEffect->End();

    return S_OK;
}

HRESULT CUIElements::Render()
{
    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        pUIElement->Render( m_pd3dDevice );
    }
    return S_OK;
}

// Go through pEffect and hook up existing UI objects to parameters,
// and create new UI objects for other parameters
void CUIElements::InitEffectObjects( LPD3DXEFFECT pEffect )
{
    D3DXEFFECT_DESC EffectDesc;
    D3DXPARAMETER_DESC ParamDesc;
    D3DXHANDLE hParam;
    D3DXHANDLE hAnnot;
    CUIElement* pElement;
    LPCSTR pstrName;
    CString strParamName;
    CString strAnnotName;

    pEffect->GetDesc( &EffectDesc );
    for( UINT iParam = 0; iParam < EffectDesc.Parameters; iParam++ )
    {
        hParam = pEffect->GetParameter ( NULL, iParam );

        // See if param has a UIDirectional annotation
        hAnnot = pEffect->GetAnnotationByName( hParam, "UIDirectional" );
        if( hAnnot != NULL )
        {
            pEffect->GetParameterDesc( hParam, &ParamDesc );
            strParamName = ParamDesc.Name;

            // See if we already have a UIElement with with that name
            pEffect->GetString( hAnnot, &pstrName);
            strAnnotName = pstrName;
            if( FindElement( strAnnotName, &pElement ) )
            {
                // Element exists, so hook it up to this hParam
                pElement->SetParamName( strParamName );
                pElement->SetParam( pEffect, hParam, FALSE );
            }
            else
            {
                // Element doesn't exist, so create one based on the type
                CDirLight* pDirLight;
                pDirLight = new CDirLight(this);
                if( pDirLight == NULL )
                    return;
                pDirLight->SetAnnotName( strAnnotName );
                pDirLight->SetParamName( strParamName );
                pDirLight->SetParam( pEffect, hParam, TRUE );
                m_UIElementList.AddHead( pDirLight );
            }
        }
    }

    // Destroy any UIElements that aren't attached to a handle by now
    CUIElement* pUIElement;

    POSITION pos1, pos2;
    for( pos1 = m_UIElementList.GetHeadPosition(); (pos2 = pos1) != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos1 );
        if( pUIElement->GetParamHandle() == NULL )
        {
            pUIElement = (CUIElement*)m_UIElementList.GetAt(pos2);
            m_UIElementList.RemoveAt(pos2);
            delete pUIElement;
        }
    }
}

// Drop all effect-specific objects (parameter handles)
void CUIElements::DeleteEffectObjects()
{
    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        pUIElement->SetParam(NULL, NULL, FALSE);
    }
}

BOOL CUIElements::FindElement( CString& strAnnotName, CUIElement** ppElement )
{
    *ppElement = NULL;

    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        if( pUIElement->GetAnnotName() == strAnnotName )
        {
            *ppElement = pUIElement;
            return TRUE;
        }
    }    
    return FALSE;
}


void CUIElements::SetEffectParameters( LPD3DXEFFECT pEffect )
{
    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        pUIElement->SetEffectParameters( pEffect );
    }
}

void CUIElements::HandleMouseDown( INT x, INT y, BOOL* pbSetCapture )
{
    *pbSetCapture = FALSE;

    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        pUIElement->HandleMouseDown( x, y, pbSetCapture );
        if( *pbSetCapture )
            return;
    }
}

void CUIElements::HandleMouseMove( INT x, INT y )
{
    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        pUIElement->HandleMouseMove( x, y );
    }
}

void CUIElements::HandleMouseUp()
{
    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        pUIElement->HandleMouseUp();
    }
}


BOOL CUIElements::IsDragging()
{
    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        if( pUIElement->IsDragging() )
            return TRUE;
    }
    return FALSE;
}

void CUIElements::DeleteAllElements()
{
    CUIElement* pUIElement;

    for( POSITION pos = m_UIElementList.GetHeadPosition(); pos != NULL;  )
    {
        pUIElement = (CUIElement*)m_UIElementList.GetNext( pos );
        delete pUIElement;
    }
    m_UIElementList.RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// CDirLight

CDirLight::CDirLight(CUIElements* pUIElements)
{
    m_pUIElements = pUIElements;
    m_fTheta = D3DX_PI / 2;
    m_fRho = -D3DX_PI / 4;
    m_bDragging = FALSE;
    m_bSelected = FALSE;
    m_vec.x = 0.0f;
    m_vec.y = 0.0f;
    m_vec.z = 1.0f;
}

void CDirLight::Update()
{
    FLOAT fScaleFactor = m_pUIElements->m_fObjectRadius * 0.25f;
    D3DXMATRIX matScale;
    D3DXMATRIX matTrans;
    D3DXMATRIX matRot;
    D3DXMatrixScaling( &matScale, fScaleFactor, fScaleFactor, fScaleFactor );
    D3DXMatrixTranslation( &matTrans, 0, 0, m_pUIElements->m_fObjectRadius * 0.75f );
    D3DXMatrixRotationYawPitchRoll( &matRot, m_fTheta, m_fRho, 0 );
    m_matWorld = matScale * matTrans * matRot;

    D3DXVECTOR3 vec(0, 0, 1);
    D3DXVec3TransformCoord( &m_vec, &vec, &m_matWorld );
    m_vec = -m_vec;
    D3DXVec3Normalize(&m_vec, &m_vec);
}

void CDirLight::SetEffectParameters( LPD3DXEFFECT pEffect )
{
    Update();
    if( m_hParam != NULL )
    {
        D3DXVECTOR4 vec(m_vec.x, m_vec.y, m_vec.z, 1.0f);
        pEffect->SetVector( m_hParam, &vec );
    }
}

void CDirLight::Render( IDirect3DDevice9* pd3dDevice )
{
    pd3dDevice->SetTransform( D3DTS_WORLD, &m_matWorld );
    m_pUIElements->RenderArrow(m_bSelected);
    if( m_bSelected )
    {
        D3DXVECTOR3 vec;
        D3DXMATRIX mat;
        mat = m_matWorld * m_pUIElements->m_matView * m_pUIElements->m_matProj;
        vec.x = 0; vec.y = 0; vec.z = 0;
        D3DXVec3TransformCoord( &vec, &vec, &mat );
        vec.x = vec.x * m_pUIElements->m_bbWidth / 2 + m_pUIElements->m_bbWidth / 2;
        vec.y = -vec.y * m_pUIElements->m_bbHeight / 2 + m_pUIElements->m_bbHeight / 2;
        CString str;
        str.Format(TEXT("%s\n(%0.2f, %0.2f, %0.2f)"), m_strAnnotName, m_vec.x, m_vec.y, m_vec.z );
        m_pUIElements->m_pd3dFont->DrawText( vec.x + 1, vec.y + 1, 0xff000000, str);
        m_pUIElements->m_pd3dFont->DrawText( vec.x, vec.y, 0xffffffff, str);
    }
}

void CDirLight::SetParam( LPD3DXEFFECT pEffect, D3DXHANDLE hParam, BOOL bPickUpDefault )
{
    HRESULT hr;
    D3DXVECTOR4 vec;
    m_hParam = hParam;

    if( pEffect == NULL )
        return;

    if( bPickUpDefault )
    {
        hr = pEffect->GetVector( hParam, &vec );

        if( vec.x == 0 && vec.y == 0 && vec.z == 0 )
        {
            m_fTheta = D3DX_PI / 2;
            m_fRho = -D3DX_PI / 4;
        }
        else
        {
            vec = -vec;
            D3DXVec4Normalize( &vec, &vec );
            m_fTheta = atan2f(vec.x, vec.z);
            m_fRho = -vec.y * D3DX_PI / 2;
        }
        Update();
    }
}

void CDirLight::HandleMouseDown( INT x, INT y, BOOL* pbSetCapture )
{
    *pbSetCapture = FALSE;
    if( MouseOverLight( x, y ) ) 
    {
        *pbSetCapture = TRUE;
        m_hCur = SetCursor(NULL);
        m_bDragging = TRUE;
        m_xDown = x;
        m_yDown = y;
        m_fThetaDown = m_fTheta;
        m_fRhoDown = m_fRho;
    }
}

void CDirLight::HandleMouseMove( INT x, INT y )
{
    if( m_bDragging )
    {
        INT dx = m_xDown - x;
        INT dy = y - m_yDown;

        float fdx = dx / 100.0f;
        float fdy = dy / 100.0f;

        m_fTheta = m_fThetaDown + fdx;
        m_fRho = m_fRhoDown + fdy;

        if( m_fRho > D3DX_PI / 2 )
            m_fRho = D3DX_PI / 2;
        if( m_fRho < -D3DX_PI / 2 )
            m_fRho = -D3DX_PI / 2;
        Update();
    }
    else
    {
        if( MouseOverLight( x, y ) ) 
        {
            m_bSelected = TRUE;
        }
        else
        {
            m_bSelected = FALSE;
        }
    }
}

void CDirLight::HandleMouseUp()
{
    if( m_bDragging )
    {
        m_bDragging = FALSE;
        ReleaseCapture();
        SetCursor(m_hCur);
        m_hCur = NULL;
    }
}

BOOL CDirLight::MouseOverLight(INT x, INT y)
{
    D3DXVECTOR3 vecRayPos;
    D3DXVECTOR3 vecRayDir;
    BOOL bHit = FALSE;
 
    D3DXVECTOR3 vPickRayDir;
    D3DXVECTOR3 vPickRayOrig;

    // Get the pick ray from the mouse position

    // Compute the vector of the pick ray in screen space
    D3DXVECTOR3 v;
    v.x =  ( ( ( 2.0f * x ) / m_pUIElements->m_bbWidth  ) - 1 ) / m_pUIElements->m_matProj._11;
    v.y = -( ( ( 2.0f * y ) / m_pUIElements->m_bbHeight ) - 1 ) / m_pUIElements->m_matProj._22;
    v.z =  1.0f;

    // Get the inverse worldview matrix
    D3DXMATRIXA16 m1, m;
    m1 = m_matWorld * m_pUIElements->m_matView;
    D3DXMatrixInverse( &m, NULL, &m1 );

    // Transform the screen space pick ray into 3D space
    vPickRayDir.x  = v.x*m._11 + v.y*m._21 + v.z*m._31;
    vPickRayDir.y  = v.x*m._12 + v.y*m._22 + v.z*m._32;
    vPickRayDir.z  = v.x*m._13 + v.y*m._23 + v.z*m._33;
    vPickRayOrig.x = m._41;
    vPickRayOrig.y = m._42;
    vPickRayOrig.z = m._43;
    
    D3DXIntersect( m_pUIElements->m_pMeshArrow, &vPickRayOrig, &vPickRayDir, &bHit, 
        NULL, NULL, NULL, NULL, NULL, NULL );
    return bHit;
}

