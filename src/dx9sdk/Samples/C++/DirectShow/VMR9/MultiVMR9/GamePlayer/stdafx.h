//------------------------------------------------------------------------------
// File: StdAfx.h
//
// Desc: DirectShow sample code - include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
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
#include <d3dx9math.h>
#include <d3dx9anim.h>

// Local Header Files
#include "MultiVMR9.h"
#include "Character.h"

#ifndef RELEASE
#define RELEASE(p){ if(p){p->Release(); p=NULL;}}
#endif

#ifndef CHECK_HR
#define CHECK_HR(hr,f){ if( FAILED(hr)){f;throw hr;}}
#endif

// global prototypes
void DbgMsg( char* szMessage, ... );
HRESULT FindMediaFile(  TCHAR* achPath, 
                        DWORD size, 
                        TCHAR* achShortName, 
                        LPCTSTR lpResourceName, 
                        LPCTSTR lpResourceType );

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif
