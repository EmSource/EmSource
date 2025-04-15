//------------------------------------------------------------------------------
// File: Helpers.h
//
// Desc: DirectShow sample code - a simple full screen video playback sample.
//       Using the Windows XP Video Mixing Renderer, a video is played back in
//       a full screen exclusive mode.
//      
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#if !defined(AFX_HELPERS_H__C2EEE5A1_3779_4D7C_8DA1_C4D6DE9DA876__INCLUDED_)
#define AFX_HELPERS_H__C2EEE5A1_3779_4D7C_8DA1_C4D6DE9DA876__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Helpers {

//-----------------------------------------------------------------------------------------
//  Function:   hresultNameLookup
//  Purpose:    returns a string value for the given hresult
//  Arguments:  HRESULT that needs verifying
//  Returns:    string
//-----------------------------------------------------------------------------------------*/
const TCHAR * hresultNameLookup(HRESULT hres);

//----------------------------------------------------------------------------
//  FindMediaFile
// 
//  Provides FileOpen dialog to select media file or processes command line
//
//  Parameters:
//          instance -- application instance
//          owner - owner window
//          achFoundFile    - path to the file to play // pass MAX_PATH
//
//  Return: true if success 
//----------------------------------------------------------------------------
bool FindMediaFile(HINSTANCE hInstance, HWND hwndOwner, LPTSTR achFoundFile);

//----------------------------------------------------------------------------
//  Release the object and set the reference to null
//  this is preferred to a MACRO definition because this will also 
//  check the type of an object
// 
//
//  Parameters:
//      p - reference to a pointer of a type T
//
//  Return: 
//----------------------------------------------------------------------------
template<typename T>
inline void RELEASE( T* &p )
{
    if( p ) {
        p->Release();
        p = NULL;
    }
}

}

#endif // !defined(AFX_HELPERS_H__C2EEE5A1_3779_4D7C_8DA1_C4D6DE9DA876__INCLUDED_)
