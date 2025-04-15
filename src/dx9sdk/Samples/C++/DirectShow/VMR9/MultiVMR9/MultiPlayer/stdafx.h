//------------------------------------------------------------------------------
// File: StdAfx.h
//
// Desc: DirectShow sample code
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Windows Header Files:
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <objbase.h>
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <comdef.h>
#include <atlbase.h>
#include <commdlg.h>
#include <tchar.h>
#include <streams.h>
#include <dshow.h>
#include <d3d9.h>
#include <vmr9.h>

// Local Header Files
#include "MultiVMR9.h"

#ifndef RELEASE
#define RELEASE(p){ if(p){p->Release(); p=NULL;}}
#endif

#ifndef CHECK_HR
#define CHECK_HR(hr,f){ if( FAILED(hr)){f;throw hr;}}
#endif

// global prototypes
void DbgMsg( char* szMessage, ... );

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)

