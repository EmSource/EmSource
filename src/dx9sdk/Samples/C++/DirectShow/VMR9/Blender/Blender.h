//------------------------------------------------------------------------------
// File: Blender.h
//
// Desc: main header file for the VMR Blender application
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#if !defined(AFX_BLENDER_H__76C2081E_3C39_4E9B_B84D_CC5A7CD29C3D__INCLUDED_)
#define AFX_BLENDER_H__76C2081E_3C39_4E9B_B84D_CC5A7CD29C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBlenderApp:
// See Blender.cpp for the implementation of this class
//

class CBlenderApp : public CWinApp
{
public:
	CBlenderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlenderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBlenderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLENDER_H__76C2081E_3C39_4E9B_B84D_CC5A7CD29C3D__INCLUDED_)
