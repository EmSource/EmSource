//------------------------------------------------------------------------------
// File: Helpers.cpp
//
// Desc: DirectShow sample code - a simple full screen video playback sample.
//       Using the Windows XP Video Mixing Renderer, a video is played back in
//       a full screen exclusive mode.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

// Pre compiled header
#include "stdafx.h"

// DirectX and global headers
#include <commdlg.h>
#include <vfwmsgs.h>

// Project headers
#include "Helpers.h"

namespace Helpers {

//-----------------------------------------------------------------------------------------
//  Function:   hresultNameLookup
//  Purpose:    Returns a string value for the given hresult
//  Arguments:  HRESULT that needs verifying
//  Returns:    string
//-----------------------------------------------------------------------------------------*/
const TCHAR * hresultNameLookup(HRESULT hres)
{
    switch(hres)
    {
        case VFW_E_CANNOT_RENDER:
            return _T("VFW_E_CANNOT_RENDER\0");
            break;
        case VFW_E_INVALID_FILE_FORMAT:
            return _T("VFW_E_INVALID_FILE_FORMAT\0");
            break;
        case VFW_E_NOT_FOUND:
            return _T("VFW_E_NOT_FOUND\0");
            break;
        case VFW_E_NOT_IN_GRAPH:
            return _T("VFW_E_NOT_IN_GRAPH\0");
            break;
        case VFW_E_UNKNOWN_FILE_TYPE:
            return _T("VFW_E_UNKNOWN_FILE_TYPE\0");
            break;
        case VFW_E_UNSUPPORTED_STREAM:
            return _T("VFW_E_UNSUPPORTED_STREAM\0");
            break;
        case VFW_E_CANNOT_CONNECT:
            return _T("VFW_E_CANNOT_CONNECT\0");
            break;
        case VFW_E_CANNOT_LOAD_SOURCE_FILTER:
            return _T("VFW_E_CANNOT_LOAD_SOURCE_FILTER\0");
            break;
        case VFW_S_PARTIAL_RENDER:
            return _T("VFW_S_PARTIAL_RENDER\0");
            break;
        case VFW_S_VIDEO_NOT_RENDERED:
            return _T("VFW_S_VIDEO_NOT_RENDERED\0");
            break;
        case VFW_S_AUDIO_NOT_RENDERED:
            return _T("VFW_S_AUDIO_NOT_RENDERED\0");
            break;
        case VFW_S_DUPLICATE_NAME:
            return _T("VFW_S_DUPLICATE_NAME\0");
            break;
        case VFW_S_MEDIA_TYPE_IGNORED:
            return _T("VFW_S_MEDIA_TYPE_IGNORED\0");
            break;
        case VFW_E_NO_DISPLAY_PALETTE:
            return _T("VFW_E_NO_DISPLAY_PALETTE\0");
            break;
        case VFW_E_NO_COLOR_KEY_FOUND:
            return _T("VFW_E_NO_COLOR_KEY_FOUND\0");
            break;
        case VFW_E_PALETTE_SET:
            return _T("VFW_E_PALETTE_SET\0");
            break;
        case VFW_E_BUFFERS_OUTSTANDING:
            return _T("VFW_E_BUFFERS_OUTSTANDING\0");
            break;
        case VFW_E_NO_ADVISE_SET:
            return _T("VFW_E_NO_ADVISE_SET\0");
            break;

        case DDERR_INCOMPATIBLEPRIMARY:
            return _T("DDERR_INCOMPATIBLEPRIMARY\0");
            break;
        case DDERR_INVALIDCAPS:
            return _T("DDERR_INVALIDCAPS\0");
            break;
        case DDERR_INVALIDOBJECT :
            return _T("DDERR_INVALIDOBJECT\0");
            break;
        case DDERR_INVALIDPIXELFORMAT:
            return _T("DDERR_INVALIDPIXELFORMAT\0");
            break;
        case DDERR_NOALPHAHW :
            return _T("DDERR_NOALPHAHW\0");
            break;
        case DDERR_NOCOOPERATIVELEVELSET :
            return _T("DDERR_NOCOOPERATIVELEVELSET\0");
            break;
        case DDERR_NODIRECTDRAWHW :
            return _T("DDERR_NODIRECTDRAWHW\0");
            break;
        case DDERR_NOEMULATION :
            return _T("DDERR_NOEMULATION\0");
            break;
        case DDERR_NOEXCLUSIVEMODE :
            return _T("DDERR_NOEXCLUSIVEMODE \0");
            break;
        case DDERR_NOFLIPHW:
            return _T("DDERR_NOFLIPHW\0");
            break;
        case DDERR_NOMIPMAPHW:
            return _T("DDERR_NOMIPMAPHW\0");
            break;
        case DDERR_NOOVERLAYHW :
            return _T("DDERR_NOOVERLAYHW \0");
            break;
        case E_OUTOFMEMORY:
            return _T("E_OUTOFMEMORY\0");
            break;
        case DDERR_NOZBUFFERHW :
            return _T("DDERR_NOZBUFFERHW \0");
            break;
        case DDERR_OUTOFVIDEOMEMORY :
            return _T("DDERR_OUTOFVIDEOMEMORY\0");
            break;
        case DDERR_PRIMARYSURFACEALREADYEXISTS:
            return _T("DDERR_PRIMARYSURFACEALREADYEXISTS \0");
            break;
        case DDERR_UNSUPPORTEDMODE:
            return _T("DDERR_UNSUPPORTEDMODE\0");
            break;

        case S_OK:
            return _T("S_OK\0");
            break;
        case S_FALSE:
            return _T("S_FALSE\0");
            break;
        case E_FAIL:
            return _T("E_FAIL\0");
            break;
        case E_INVALIDARG:
            return _T("E_INVALIDARG\0");
            break;
        case E_NOTIMPL:
            return _T("E_NOTIMPL\0");
            break;
        case E_NOINTERFACE:
            return _T("E_NOINTERFACE\0");
            break;
        case E_POINTER:
            return _T("E_POINTER\0");
            break;
        case E_UNEXPECTED:
            return _T("E_UNEXPECTED\0");
            break;
        case E_PROP_SET_UNSUPPORTED:
            return _T("E_PROP_SET_UNSUPPORTED\0");
            break;

        case VFW_S_CONNECTIONS_DEFERRED:
            return _T("VFW_S_CONNECTIONS_DEFERRED\0");
            break;

        case 0x80040154:
            return _T("Class not registered\0");
            break;
        case VFW_E_DVD_OPERATION_INHIBITED:
            return _T("VFW_E_DVD_OPERATION_INHIBITED\0");
            break;
        case VFW_E_DVD_INVALIDDOMAIN:
            return _T("VFW_E_DVD_INVALIDDOMAIN\0");
            break;
        case VFW_E_WRONG_STATE:
            return _T("VFW_E_WRONG_STATE\0");
            break;
        case VFW_E_NO_PALETTE_AVAILABLE:
            return _T("VFW_E_NO_PALETTE_AVAILABLE\0");
            break;
        case VFW_E_DVD_NO_BUTTON:
            return _T("VFW_E_DVD_NO_BUTTON\0");
            break;
        case VFW_E_DVD_GRAPHNOTREADY:
            return _T("VFW_E_DVD_GRAPHNOTREADY\0");
            break;
        case VFW_E_NOT_OVERLAY_CONNECTION:
            return _T("VFW_E_NOT_OVERLAY_CONNECTION\0");
            break;
        case VFW_E_DVD_RENDERFAIL:
            return _T("VFW_E_DVD_RENDERFAIL\0");
            break;
        case VFW_E_NOT_CONNECTED:
            return _T("VFW_E_NOT_CONNECTED\0");
            break;
        case VFW_E_NO_COLOR_KEY_SET :
            return _T("VFW_E_NO_COLOR_KEY_SET \0");
            break;
        case VFW_E_NO_INTERFACE:
            return _T("VFW_E_NO_INTERFACE\0");
            break;

        case 0x8004020c:
            return _T("VFW_E_BUFFER_NOTSET\0");
            break;
        case 0x80040225:
            return _T("VFW_E_NOT_PAUSED\0");
            break;
        case 0x80070002:
            return _T("System cannot find the file specified\0");
            break;
        case 0x80070003:
            return _T("System cannot find the path specified\0");
            break;

        case VFW_E_DVD_DECNOTENOUGH:
            return _T("VFW_E_DVD_DECNOTENOUGH\0");
            break;
        case VFW_E_ADVISE_ALREADY_SET:
            return _T("VFW_E_ADVISE_ALREADY_SET\0");
            break;
        case VFW_E_DVD_CMD_CANCELLED:
            return _T("VFW_E_DVD_CMD_CANCELLED\0");
            break;
        case VFW_E_DVD_MENU_DOES_NOT_EXIST:
            return _T("VFW_E_DVD_MENU_DOES_NOT_EXIST\0");
            break;
        case VFW_E_DVD_WRONG_SPEED:
            return _T("VFW_E_DVD_WRONG_SPEED\0");
            break;
        case VFW_S_DVD_NON_ONE_SEQUENTIAL:
            return _T("VFW_S_DVD_NON_ONE_SEQUENTIAL\0");
            break;
        case VFW_E_DVD_NOT_IN_KARAOKE_MODE:
            return _T("VFW_E_DVD_NOT_IN_KARAOKE_MODE\0");
            break;
        case VFW_E_DVD_INVALID_DISC:
            return _T("VFW_E_DVD_INVALID_DISC\0");
            break;
        case VFW_E_DVD_STREAM_DISABLED:
            return _T("VFW_E_DVD_STREAM_DISABLED\0");
            break;
        case VFW_E_NOT_STOPPED:
            return _T("VFW_E_NOT_STOPPED\0");
            break;

        default:        
            return _T("Unrecognized\0");
            break;
    }
}


//----------------------------------------------------------------------------
//  FindMediaFile
// 
//  Provides FileOpen dialog to select media file 
//
//  Parameters:
//          instance -- application instance
//          owner - owner window
//          achFoundFile    - path to the file to play // pass MAX_PATH
//
//  Return: true if success 
//----------------------------------------------------------------------------
bool FindMediaFile(HINSTANCE instance, HWND owner, LPTSTR achFoundFile)
{
    TCHAR  szBuffer[MAX_PATH];
    lstrcpy(szBuffer,_T(""));

    static TCHAR szFilter[]  =  
        TEXT("Video Files (*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v)\0*.avi;*.qt;*.mov;*.mpg;*.mpeg;*.m1v\0All Files\0*.*\0\0");
   
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof( ofn ) );
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = owner;
    ofn.hInstance         = instance;
    ofn.lpstrFilter       = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nFilterIndex      = 1;
    ofn.lpstrFile         = szBuffer;
    ofn.nMaxFile          = MAX_PATH;
    ofn.lpstrTitle        = TEXT("VMRXCLBasic: Open a video file...\0");
    ofn.lpstrFileTitle    = NULL;
    ofn.lpstrDefExt       = TEXT("MPG");
    ofn.Flags             = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;
    
    if (GetOpenFileName (&ofn))  // user specified a file
    {
        lstrcpy(achFoundFile, ofn.lpstrFile);
        return true;
    }

    return false;
}


}


