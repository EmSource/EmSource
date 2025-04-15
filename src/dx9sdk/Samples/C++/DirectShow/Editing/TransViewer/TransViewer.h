// ---------------------------------------------------------------------------
// File: Transviewer.h
// 
// Desc: Main include file for the project.
//      
// Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------


#ifndef _TRANSVIEWER_H
#define _TRANSVIEWER_H

#define STRICT

#include <windows.h>
#include <objbase.h>    // Defines CoIntializeEx

#include <crtdbg.h>
#include <atlbase.h>

#include <dshow.h>      // Main DirectShow include file
#include <qedit.h>      // Include file for Editing Services
#include <streams.h>    // DirectShow base class library

#include "resource.h"

// If building this sample with Visual C++ 6.0's headers, these two
// includes generate several warnings.  Suppress the warnings, since
// these headers are beyond our control.
#pragma warning(push, 2)
#include <vector>
#include <iterator>
#pragma warning(pop)

using namespace std;


#define DEMO_NAME       TEXT("DirectShow Transition Previewer\0")

const long WM_NEXTITEM = WM_APP + 2;
const long WM_ERRORLOG = WM_APP + 3;   // Sent by the error log object


struct hresult_exception
{
    HRESULT hr;
    hresult_exception(HRESULT hr) { this->hr = hr; }
};


// Converts between RGB format and BGR format.
inline DWORD SwapRGB(COLORREF color)
{
    return (GetRValue(color) << 16) + (GetGValue(color) << 8) + GetBValue(color);
}



#endif // _TRANSVIEWER_H