#if !defined(AFX_OPTIONSVIEW_H__93AE1BE4_0D08_429E_9A48_22E073A11943__INCLUDED_)
#define AFX_OPTIONSVIEW_H__93AE1BE4_0D08_429E_9A48_22E073A11943__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CEffectDoc;

class COptionsView : public CFormView
{
protected:
	COptionsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COptionsView)

// Form Data
public:
	//{{AFX_DATA(COptionsView)
	enum { IDD = IDD_OPTIONS_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CEffectDoc* GetDocument();

// Operations
public:
    void SetTechniqueNameList( CStringList& techniqueNameList, int iTechniqueCur);
    void SetPassNameList( CStringList& passNameList, int iPassCur);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COptionsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(COptionsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChangeTechnique();
	afx_msg void OnChangePass();
	afx_msg void OnShowStats();
	afx_msg void OnFillModeChange();
	afx_msg void OnChangeRenderPass();
	afx_msg void OnResetCamera();
	afx_msg void OnChangeRenderTiming();
	afx_msg void OnRender();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OptionsView.cpp
inline CEffectDoc* COptionsView::GetDocument()
   { return (CEffectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSVIEW_H__93AE1BE4_0D08_429E_9A48_22E073A11943__INCLUDED_)
