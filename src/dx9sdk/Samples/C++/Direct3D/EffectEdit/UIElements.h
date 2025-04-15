#if !defined(AFX_UIELEMENTS_H__5E5BABDA_4318_4644_8CCA_A0599B3925DF__INCLUDED_)
#define AFX_UIELEMENTS_H__5E5BABDA_4318_4644_8CCA_A0599B3925DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UIElements.h : header file
//

class CUIElement;

/////////////////////////////////////////////////////////////////////////////
// CUIElements 

class CUIElements : public CObject
{
private:
    LPDIRECT3DDEVICE9 m_pd3dDevice;
    CObList m_UIElementList;
    ID3DXEffect* m_pEffect;

public:
    FLOAT m_fObjectRadius;
    D3DXMATRIXA16 m_matView;
    D3DXMATRIXA16 m_matProj;
    UINT m_bbWidth;
    UINT m_bbHeight;
    CD3DFont* m_pd3dFont;
    LPD3DXMESH m_pMeshArrow;

public:
    CUIElements();
    ~CUIElements();
    HRESULT InitDeviceObjects( LPDIRECT3DDEVICE9 pd3dDevice );
    HRESULT RestoreDeviceObjects();
    void InvalidateDeviceObjects();
    void DeleteDeviceObjects();
    LPDIRECT3DDEVICE9 Pd3dDevice() { return m_pd3dDevice; }
    HRESULT Render();
    HRESULT RenderArrow( BOOL bSelected );

    void SetInfo( UINT bbWidth, UINT bbHeight, D3DXMATRIX* pMatProj );
    void SetMatView( D3DXMATRIX* pMatView );
    void SetObjectRadius( FLOAT fObjectRadius ) { m_fObjectRadius = fObjectRadius; }
    void SetEffectParameters( LPD3DXEFFECT pEffect );
    void InitEffectObjects( LPD3DXEFFECT pEffect );
    void DeleteEffectObjects();
    void DeleteAllElements();

    void HandleMouseDown( INT x, INT y, BOOL* pbSetCapture );
    void HandleMouseMove( INT x, INT y );
    void HandleMouseUp();
    BOOL IsDragging();

    BOOL FindElement( CString& strAnnotName, CUIElement** ppElement );
};

/////////////////////////////////////////////////////////////////////////////
// CUIElement
class CUIElement : public CObject
{
protected:
    CString m_strParamName;
    CString m_strAnnotName;
    D3DXHANDLE m_hParam;

public:
    CUIElement() { m_hParam = NULL; }

    virtual void Render( IDirect3DDevice9* pd3dDevice ) = NULL;
    virtual void SetEffectParameters( LPD3DXEFFECT pEffect ) = NULL;
    virtual void HandleMouseDown( INT x, INT y, BOOL* pbSetCapture ) = NULL;
    virtual void HandleMouseMove( INT x, INT y ) = NULL;
    virtual void HandleMouseUp() = NULL;
    virtual BOOL IsDragging() = NULL;
    CString& GetParamName() { return m_strParamName; }
    CString& GetAnnotName() { return m_strAnnotName; }
    void SetParamName(CString& strNew) { m_strParamName = strNew; }
    void SetAnnotName(CString& strNew) { m_strAnnotName = strNew; }
    virtual void SetParam( LPD3DXEFFECT pEffect, D3DXHANDLE hParam, BOOL bPickUpDefault ) = NULL;
    D3DXHANDLE GetParamHandle() { return m_hParam; }
};

/////////////////////////////////////////////////////////////////////////////
// CDirLight 

class CDirLight : public CUIElement
{
private:
    CUIElements* m_pUIElements;
    D3DXMATRIXA16 m_matWorld;
    float m_fTheta;
    float m_fRho;
    float m_fThetaDown;
    float m_fRhoDown;
    D3DXVECTOR3 m_vec;
    HCURSOR m_hCur;
    BOOL m_bDragging;
    INT m_xDown;
    INT m_yDown;
    BOOL m_bSelected;

public:
    CDirLight(CUIElements* pUIElements);

    virtual void Render( IDirect3DDevice9* pd3dDevice );
    virtual void SetEffectParameters( LPD3DXEFFECT pEffect );
    virtual BOOL IsDragging() { return m_bDragging; }
    virtual void SetParam( LPD3DXEFFECT pEffect, D3DXHANDLE hParam, BOOL bPickUpDefault );
    virtual void HandleMouseDown( INT x, INT y, BOOL* pbSetCapture );
    virtual void HandleMouseMove( INT x, INT y );
    virtual void HandleMouseUp();
    void Update();
    BOOL MouseOverLight(INT x, INT y);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UIELEMENTS_H__5E5BABDA_4318_4644_8CCA_A0599B3925DF__INCLUDED_)
