//-----------------------------------------------------------------------------
// File: DXUtil.cpp
//
// Desc: Shortcut macros and functions for using DirectX objects
//
// Copyright (c) 1997-2002 Microsoft Corporation. All rights reserved
//-----------------------------------------------------------------------------

#include "Textures.h"

#include <tchar.h>
#include <stdarg.h>

#include "DXUtil.h"


//-----------------------------------------------------------------------------
// Name: DXUtil_GetDXSDKMediaPath()
// Desc: Returns the DirectX SDK media path
//-----------------------------------------------------------------------------
const TCHAR* DXUtil_GetDXSDKMediaPath()
{
    static TCHAR strNull[2] = {0};
    static TCHAR strPath[MAX_PATH + 10];
    HKEY  hKey=0;
    DWORD type=0, size=MAX_PATH;

    strPath[0] = 0;     // Initialize to NULL
    
    // Open the appropriate registry key
    LONG result = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                _T("Software\\Microsoft\\DirectX SDK"),
                                0, KEY_READ, &hKey );
    if( ERROR_SUCCESS != result )
        return strNull;

    result = RegQueryValueEx( hKey, _T("DX9SDK Samples Path"), NULL,
                              &type, (BYTE*)strPath, &size );

    if( ERROR_SUCCESS != result )
    {
        size = MAX_PATH;    // Reset size field
        result = RegQueryValueEx( hKey, _T("DX81SDK Samples Path"), NULL,
                                  &type, (BYTE*)strPath, &size );

        if( ERROR_SUCCESS != result )
        {
            size = MAX_PATH;    // Reset size field
            result = RegQueryValueEx( hKey, _T("DX8SDK Samples Path"), NULL,
                                      &type, (BYTE*)strPath, &size );

            if( ERROR_SUCCESS != result )
            {
                RegCloseKey( hKey );
                return strNull;
            }
        }
    }

    RegCloseKey( hKey );
    lstrcat( strPath, _T("\\Media\\\0") );

    return strPath;
}


