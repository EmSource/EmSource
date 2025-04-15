//------------------------------------------------------------------------------
// File: Utils.h
//
// Desc: DirectShow sample code
//       Helper functions for VMRMix sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "utils.h"
    
//-----------------------------------------------------------------------------------------
//  Function:   MyMessage
//  Purpose:    Displays a quick message box
//  Arguments:  Input strings that will be displayed
//  Returns:    Pass or fail return code
//-----------------------------------------------------------------------------------------*/
DWORD MyMessage(TCHAR *szQuestion, TCHAR *szTitle)
{
    int iReturn = AfxMessageBox( szQuestion, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1);
    return iReturn == IDYES  ? FNS_PASS : FNS_FAIL;
}


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


//-----------------------------------------------------------------------------------------
//  Function:   MySleep
//  Purpose:    If the application is in automated mode, then sleep func is turned off
//  Arguments:  Checks m_bAutomatedStatus to see if the func is in automation
//  Returns:    true if automated, false otherwist
//-----------------------------------------------------------------------------------------*/    
bool MySleep(DWORD  dwTime)
{
    HANDLE hNeverHappensEvent;

    hNeverHappensEvent = CreateEvent(NULL, FALSE, FALSE, _T("EVENTTHATNEVERHAPPENS\0"));
    WaitForSingleObject( hNeverHappensEvent, dwTime);
    return false;

} // end of checkHResult method


//-----------------------------------------------------------------------------------------
//  Function:   ShellAbort
//  Purpose:    Prints a crash message text to the appropriate log(s)
//  Arguments:  none
//  Returns:    NULL
//-----------------------------------------------------------------------------------------*/
void ShellAbort(CVMRCore *core)
{
    AfxMessageBox(TEXT("Unhandled exception, press OK to abort...\0"));
    exit(-1);
}


//-----------------------------------------------------------------------------------------
//  Function:   GetMessageName
//  Purpose:    Updates Name to the string version of the windows message
//  Arguments:  Name - long pointer to a string that will be updated
//              msg - message id that we want displayed
//-----------------------------------------------------------------------------------------*/
void GetMessageName(LPTSTR Name, UINT msg)
{   
    switch(msg)
    {
        // For put_MessageDrain and get_MessageDrain   

        case WM_KEYDOWN:           _tcscpy(Name, _T("WM_KEYDOWN\0"));         break;
        case WM_KEYUP:             _tcscpy(Name, _T("WM_KEYUP\0"));           break; 
        case WM_LBUTTONDBLCLK:     _tcscpy(Name, _T("WM_LBUTTONDBLCLK\0"));   break;
        case WM_LBUTTONDOWN:       _tcscpy(Name, _T("WM_LBUTTONDOWN\0"));     break;
        case WM_LBUTTONUP:         _tcscpy(Name, _T("WM_LBUTTONUP\0"));       break;
        case WM_MBUTTONDBLCLK:     _tcscpy(Name, _T("WM_MBUTTONDBLCLK\0"));   break;
        case WM_MBUTTONDOWN:       _tcscpy(Name, _T("WM_MBUTTONDOWN\0"));     break;
        case WM_MBUTTONUP:         _tcscpy(Name, _T("WM_MBUTTONUP\0"));       break;
        case WM_MOUSEACTIVATE:     _tcscpy(Name, _T("WM_MOUSEACTIVATE\0"));   break;
        case WM_MOUSEMOVE:         _tcscpy(Name, _T("WM_MOUSEMOVE\0"));       break;
        case WM_NCHITTEST:         _tcscpy(Name, _T("WM_NCHITTEST\0"));       break;
        case WM_NCLBUTTONDBLCLK:   _tcscpy(Name, _T("WM_NCLBUTTONDBLCLK\0")); break;
        case WM_NCLBUTTONDOWN:     _tcscpy(Name, _T("WM_NCLBUTTONDOWN\0"));   break;
        case WM_NCLBUTTONUP:       _tcscpy(Name, _T("WM_NCLBUTTONUP\0"));     break;
        case WM_NCMBUTTONDBLCLK:   _tcscpy(Name, _T("WM_NCMBUTTONDBLCLK\0")); break;
        case WM_NCMBUTTONDOWN:     _tcscpy(Name, _T("WM_NCMBUTTONDOWN\0"));   break;
        case WM_NCMBUTTONUP:       _tcscpy(Name, _T("WM_NCMBUTTONUP\0"));     break;
        case WM_NCMOUSEMOVE:       _tcscpy(Name, _T("WM_NCMOUSEMOVE\0"));     break;
        case WM_NCRBUTTONDBLCLK:   _tcscpy(Name, _T("WM_NCRBUTTONDBLCLK\0")); break;
        case WM_NCRBUTTONDOWN:     _tcscpy(Name, _T("WM_NCRBUTTONDOWN\0"));   break;
        case WM_NCRBUTTONUP:       _tcscpy(Name, _T("WM_NCRBUTTONUP\0"));     break;
        case WM_RBUTTONDBLCLK:     _tcscpy(Name, _T("WM_RBUTTONDBLCLK\0"));   break;
        case WM_RBUTTONDOWN:       _tcscpy(Name, _T("WM_RBUTTONDOWN\0"));     break;
        case WM_RBUTTONUP:         _tcscpy(Name, _T("WM_RBUTTONUP\0"));       break;

        // For NotifyOwnerMessage
            
        case WM_DEVMODECHANGE:     _tcscpy(Name, _T("WM_DEVMODECHANGE\0"));     break;
        case WM_DISPLAYCHANGE:     _tcscpy(Name, _T("WM_DISPLAYCHANGE\0"));     break;
        case WM_MOVE:              _tcscpy(Name, _T("WM_MOVE\0"));              break;
        case WM_PALETTECHANGED:    _tcscpy(Name, _T("WM_PALETTECHANGED\0"));    break;
        case WM_PALETTEISCHANGING: _tcscpy(Name, _T("WM_PALETTEISCHANGING\0")); break;
        case WM_QUERYNEWPALETTE:   _tcscpy(Name, _T("WM_QUERYNEWPALETTE\0"));   break;
        case WM_SYSCOLORCHANGE:    _tcscpy(Name, _T("WM_SYSCOLORCHANGE\0"));    break;

        default:                   _stprintf(Name, _T("Unknown Messgage [%u]\0"), msg);
    }

    return;
}


