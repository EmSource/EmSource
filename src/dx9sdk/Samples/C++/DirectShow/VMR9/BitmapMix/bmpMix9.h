//------------------------------------------------------------------------------
// File: BmpMix9.cpp
//
// Desc: DirectShow sample code - a bitmap-mixing VMR9 media file player
//       using Direct3D9 surfaces
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#if !defined(AFX_BMPMIX9_H__CA30736C_ACAF_4108_A46A_0E8854AF657B__INCLUDED_)
#define AFX_BMPMIX9_H__CA30736C_ACAF_4108_A46A_0E8854AF657B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Windows Header Files
#include <windows.h>
#include <objbase.h>
#include <tchar.h>

#include <atlbase.h>
#include <comdef.h>
#include <commdlg.h>
#include <assert.h>

// DirectX header files
#include <dshow.h>
#include <d3d9.h>
#include <d3dx9tex.h> // for D3DXLoadSurfaceFromResource 
#include <vmr9.h>

// Application header files
#include "resource.h"

// Helper macro
#define FAIL_RET(x) if( FAILED( hr = ( x ) ) )     \
                    {                              \
                        assert( SUCCEEDED( hr ) ); \
                        return hr;                 \
                    }

#endif // !defined(AFX_BMPMIX9_H__CA30736C_ACAF_4108_A46A_0E8854AF657B__INCLUDED_)


