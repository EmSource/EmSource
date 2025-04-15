//----------------------------------------------------------------------------
//  File:   Project.h
//
//  Desc:   DirectShow sample code
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#pragma once

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <ddraw.h>
#define D3D_OVERLOADS
#include <d3d.h>

#include <atlbase.h>
#include <mmreg.h>

#include <DShow.h>
#include <streams.h>

#include "vmruuids.h"

#ifndef _T
#define _T TEXT
#endif

#ifndef SAFERELEASE
#define SAFERELEASE(punk)    if (NULL != punk) { (punk)->Release(); (punk) = NULL; }
#endif

#ifndef __ZEROSTRUCT_DEFINED
#define __ZEROSTRUCT_DEFINED
template <typename T>
__inline void ZeroStruct(T& t)
{
    ZeroMemory(&t, sizeof(t));
}
#endif

#ifndef __INITDDSTRUCT_DEFINED
#define __INITDDSTRUCT_DEFINED
template <typename T>
__inline void INITDDSTRUCT(T& dd)
{
    ZeroStruct(dd);
    dd.dwSize = sizeof(dd);
}
#endif


#include "resource.h"
#include "DDrawSupport.h"
#include "movie.h"
#include "effects\effect.h"
#include "sparkles\sparkles.h"
#include "cMultiSAP.h"


#ifndef DECLSPEC_SELECTANY
#if (_MSC_VER >= 1100)
#define DECLSPEC_SELECTANY  __declspec(selectany)
#else
#define DECLSPEC_SELECTANY
#endif
#endif

EXTERN_C const GUID DECLSPEC_SELECTANY IID_IDirectDraw7 =
{
    0x15e65ec0, 0x3b9c, 0x11d2,
    {
        0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b
    }
};

//-------------------------------------------------------------------------
//  sMovieInfo
//  Basic information on the movie clip
//-------------------------------------------------------------------------
typedef struct sMovieInfo
{
    WCHAR            achPath[MAX_PATH];
    DWORD_PTR        pdwUserID;

} sMovieInfo;

#define MOVIEINFO_PATH_CHARS    MAX_PATH

// this line defines if there is "sparkles" source filter on the background
// for low-performance HW, comment it out
#define SPARKLE 1

