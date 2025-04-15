//----------------------------------------------------------------------------
//  File:   Utils.h
//
//  Desc:   DirectShow sample code
//          External (global) utilities specific for VMRXcl app
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "project.h"
#include "utils.h"
#include "vmrutil.h"

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



void ReportDDrawSurfDesc( DDSURFACEDESC2 ddsd)
{
    TCHAR szFlags[4096];
    TCHAR szMsg[4096];

    OutputDebugString(_T("*** Surface description ***\n"));
    
    SurfaceDescHelper( ddsd.dwFlags, szFlags);
    OutputDebugString(szFlags);

    wsprintf( szMsg, _T("  dwWidth x dwHeight: %ld x %ld\n"), ddsd.dwWidth, ddsd.dwHeight);
    OutputDebugString(szMsg);

    wsprintf( szMsg, _T("  lPitch: %ld\n"), ddsd.lPitch);
    OutputDebugString(szMsg);
    OutputDebugString(_T("  (dwLinearSize)\n"));

    wsprintf( szMsg, _T("  dwBackBufferCount: %ld\n"), ddsd.dwBackBufferCount);
    OutputDebugString(szMsg);

    wsprintf( szMsg, _T("  dwMipMapCount: %ld\n"), ddsd.dwMipMapCount);
    OutputDebugString(szMsg);
    OutputDebugString(_T("  (dwRefreshRate)"));

    wsprintf( szMsg, _T("  dwAlphaBitDepth: %ld\n"), (LONG)ddsd.dwAlphaBitDepth);
    OutputDebugString(szMsg);

    wsprintf( szMsg, _T("  lpSurface: %x\n"), (LONG_PTR)(ddsd.lpSurface));
    OutputDebugString(szMsg);

    ReportPixelFormat( ddsd.ddpfPixelFormat );
    ReportDDSCAPS2( ddsd.ddsCaps );

    wsprintf( szMsg, _T("  dwTextureStage: %ld\n"), ddsd.dwTextureStage);
    OutputDebugString(szMsg);

    OutputDebugString(_T("***************************\n"));
}


void ReportDDSCAPS2( DDSCAPS2 ddscaps )
{
    TCHAR sz[4096];

    lstrcpy( sz, _T("  DDSCAPS2::dwCaps: "));
    if( ddscaps.dwCaps & DDSCAPS_3DDEVICE )     lstrcat( sz, _T("DDSCAPS_3DDEVICE, "));
    if( ddscaps.dwCaps & DDSCAPS_ALLOCONLOAD )  lstrcat( sz, _T("DDSCAPS_ALLOCONLOAD, "));
    if( ddscaps.dwCaps & DDSCAPS_ALPHA )        lstrcat( sz, _T("DDSCAPS_ALPHA, "));
    if( ddscaps.dwCaps & DDSCAPS_BACKBUFFER )   lstrcat( sz, _T("DDSCAPS_BACKBUFFER, "));
    if( ddscaps.dwCaps & DDSCAPS_COMPLEX )      lstrcat( sz, _T("DDSCAPS_COMPLEX, "));
    if( ddscaps.dwCaps & DDSCAPS_FLIP )         lstrcat( sz, _T("DDSCAPS_FLIP, "));
    if( ddscaps.dwCaps & DDSCAPS_FRONTBUFFER )  lstrcat( sz, _T("DDSCAPS_FRONTBUFFER, "));
    if( ddscaps.dwCaps & DDSCAPS_HWCODEC )      lstrcat( sz, _T("DDSCAPS_HWCODEC, "));
    if( ddscaps.dwCaps & DDSCAPS_LIVEVIDEO )    lstrcat( sz, _T("DDSCAPS_LIVEVIDEO, "));
    if( ddscaps.dwCaps & DDSCAPS_LOCALVIDMEM )  lstrcat( sz, _T("DDSCAPS_LOCALVIDMEM, "));
    if( ddscaps.dwCaps & DDSCAPS_MIPMAP )       lstrcat( sz, _T("DDSCAPS_MIPMAP, "));
    if( ddscaps.dwCaps & DDSCAPS_MODEX )        lstrcat( sz, _T("DDSCAPS_MODEX, "));
    if( ddscaps.dwCaps & DDSCAPS_NONLOCALVIDMEM ) lstrcat( sz, _T("DDSCAPS_NONLOCALVIDMEM, "));
    if( ddscaps.dwCaps & DDSCAPS_OFFSCREENPLAIN ) lstrcat( sz, _T("DDSCAPS_OFFSCREENPLAIN, "));
    if( ddscaps.dwCaps & DDSCAPS_OPTIMIZED )    lstrcat( sz, _T("DDSCAPS_OPTIMIZED, "));
    if( ddscaps.dwCaps & DDSCAPS_OVERLAY )      lstrcat( sz, _T("DDSCAPS_OVERLAY, "));
    if( ddscaps.dwCaps & DDSCAPS_OWNDC )        lstrcat( sz, _T("DDSCAPS_OWNDC, "));
    if( ddscaps.dwCaps & DDSCAPS_PALETTE )      lstrcat( sz, _T("DDSCAPS_PALETTE, "));
    if( ddscaps.dwCaps & DDSCAPS_PRIMARYSURFACE )  lstrcat( sz, _T("DDSCAPS_PRIMARYSURFACE, "));
    if( ddscaps.dwCaps & DDSCAPS_STANDARDVGAMODE ) lstrcat( sz, _T("DDSCAPS_STANDARDVGAMODE, "));
    if( ddscaps.dwCaps & DDSCAPS_SYSTEMMEMORY ) lstrcat( sz, _T("DDSCAPS_SYSTEMMEMORY, "));
    if( ddscaps.dwCaps & DDSCAPS_TEXTURE )      lstrcat( sz, _T("DDSCAPS_TEXTURE, "));
    if( ddscaps.dwCaps & DDSCAPS_VIDEOMEMORY )  lstrcat( sz, _T("DDSCAPS_VIDEOMEMORY, "));
    if( ddscaps.dwCaps & DDSCAPS_VIDEOPORT )    lstrcat( sz, _T("DDSCAPS_VIDEOPORT, "));
    if( ddscaps.dwCaps & DDSCAPS_VISIBLE )      lstrcat( sz, _T("DDSCAPS_VISIBLE, "));
    if( ddscaps.dwCaps & DDSCAPS_WRITEONLY )    lstrcat( sz, _T("DDSCAPS_WRITEONLY, "));
    if( ddscaps.dwCaps & DDSCAPS_ZBUFFER )      lstrcat( sz, _T("DDSCAPS_ZBUFFER, "));

    lstrcat( sz, _T("\n"));
    OutputDebugString(sz);
    lstrcpy( sz, _T("  DDSCAPS2::dwCaps2: "));

    if( ddscaps.dwCaps2 & DDSCAPS2_CUBEMAP )            lstrcat( sz, _T("DDSCAPS2_CUBEMAP, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_CUBEMAP_POSITIVEX )  lstrcat( sz, _T("DDSCAPS2_CUBEMAP_POSITIVEX, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_CUBEMAP_NEGATIVEX )  lstrcat( sz, _T("DDSCAPS2_CUBEMAP_NEGATIVEX, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_CUBEMAP_POSITIVEY )  lstrcat( sz, _T("DDSCAPS2_CUBEMAP_POSITIVEY, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_CUBEMAP_NEGATIVEY )  lstrcat( sz, _T("DDSCAPS2_CUBEMAP_NEGATIVEY, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_CUBEMAP_POSITIVEZ )  lstrcat( sz, _T("DDSCAPS2_CUBEMAP_POSITIVEZ, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_CUBEMAP_NEGATIVEZ )  lstrcat( sz, _T("DDSCAPS2_CUBEMAP_NEGATIVEZ, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_CUBEMAP_ALLFACES )   lstrcat( sz, _T("DDSCAPS2_CUBEMAP_ALLFACES, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_D3DTEXTUREMANAGE )   lstrcat( sz, _T("DDSCAPS2_D3DTEXTUREMANAGE, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_DONOTPERSIST )       lstrcat( sz, _T("DDSCAPS2_DONOTPERSIST, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_HARDWAREDEINTERLACE) lstrcat( sz, _T("DDSCAPS2_HARDWAREDEINTERLACE, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_HINTANTIALIASING )   lstrcat( sz, _T("DDSCAPS2_HINTANTIALIASING, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_HINTDYNAMIC )        lstrcat( sz, _T("DDSCAPS2_HINTDYNAMIC, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_HINTSTATIC )         lstrcat( sz, _T("DDSCAPS2_HINTSTATIC, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_MIPMAPSUBLEVEL )     lstrcat( sz, _T("DDSCAPS2_MIPMAPSUBLEVEL, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_OPAQUE )             lstrcat( sz, _T("DDSCAPS2_OPAQUE, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_STEREOSURFACELEFT )  lstrcat( sz, _T("DDSCAPS2_STEREOSURFACELEFT, "));
    if( ddscaps.dwCaps2 & DDSCAPS2_TEXTUREMANAGE )      lstrcat( sz, _T("DDSCAPS2_TEXTUREMANAGE, "));
    
    lstrcat( sz, _T("\n"));
    OutputDebugString(sz);
}


void ReportPixelFormat( DDPIXELFORMAT ddpf)
{
    TCHAR szFlags[4096];
    TCHAR szMsg[MAX_PATH];

    PixelFormatHelper( ddpf.dwFlags, szFlags);

    OutputDebugString(szFlags);

    wsprintf( szMsg, _T("    dwFourCC: %ld\n"), ddpf.dwFourCC);
    OutputDebugString(szMsg);

    wsprintf( szMsg, _T("    dwRGBBitCount: %ld\n"), ddpf.dwRGBBitCount);
    OutputDebugString(szMsg);
    OutputDebugString(_T("    (dwYUVBitCount, dwZBufferBitDepth, dwAlphaBitDepth, dwLuminanceBitCount, dwBumpBitCount)\n"));

    wsprintf( szMsg, _T("    dwRBitMask: %ld\n"), ddpf.dwRBitMask);
    OutputDebugString(szMsg);
    OutputDebugString(_T("    (dwYBitMask, dwStencilBitDepth, dwLuminanceBitMask, dwBumpDuBitMask)\n"));

    wsprintf( szMsg, _T("    dwGBitMask: %ld\n"), ddpf.dwGBitMask);
    OutputDebugString(szMsg);
    OutputDebugString(_T("    (dwUBitMask, dwZBitMask, dwBumpDvBitMask)\n"));

    wsprintf( szMsg, _T("    dwBBitMask: %ld\n"), ddpf.dwBBitMask);
    OutputDebugString(szMsg);
    OutputDebugString(_T("    (dwVBitMask, dwStencilBitMask, dwBumpLuminanceBitMask)\n"));

    wsprintf( szMsg, _T("    dwRGBAlphaBitMask: %ld\n"), ddpf.dwRGBAlphaBitMask);
    OutputDebugString(szMsg);
    OutputDebugString(_T("    (dwYUVAlphaBitMask, dwLuminanceAlphaBitMask, dwRGBZBitMask, dwYUVZBitMask)\n"));
}


void SurfaceDescHelper( DWORD dwFlags, TCHAR * pszFlags )
{
    if( !pszFlags )
        return;

    lstrcpy( pszFlags, _T("  dwFlags: "));

    if( dwFlags & DDSD_ALL )
        lstrcat( pszFlags, _T("DDSD_ALL\n"));

    if( dwFlags & DDSD_ALPHABITDEPTH  )
        lstrcat( pszFlags, _T("DDSD_ALPHABITDEPTH\n"));

    if( dwFlags & DDSD_BACKBUFFERCOUNT  )
        lstrcat( pszFlags, _T("DDSD_BACKBUFFERCOUNT\n"));

    if( dwFlags & DDSD_CAPS  )
        lstrcat( pszFlags, _T("DDSD_CAPS\n"));

    if( dwFlags & DDSD_CKDESTBLT   )
        lstrcat( pszFlags, _T("DDSD_CKDESTBLT\n"));

    if( dwFlags & DDSD_CKDESTOVERLAY   )
        lstrcat( pszFlags, _T("DDSD_CKDESTOVERLAY\n"));

    if( dwFlags & DDSD_CKSRCBLT   )
        lstrcat( pszFlags, _T("DDSD_CKSRCBLT\n"));

    if( dwFlags & DDSD_CKSRCOVERLAY    )
        lstrcat( pszFlags, _T("DDSD_CKSRCOVERLAY\n"));

    if( dwFlags & DDSD_HEIGHT    )
        lstrcat( pszFlags, _T("DDSD_HEIGHT\n"));

    if( dwFlags & DDSD_LINEARSIZE    )
        lstrcat( pszFlags, _T("DDSD_LINEARSIZE\n"));

    if( dwFlags & DDSD_LPSURFACE    )
        lstrcat( pszFlags, _T("DDSD_LPSURFACE\n"));

    if( dwFlags & DDSD_MIPMAPCOUNT     )
        lstrcat( pszFlags, _T("DDSD_MIPMAPCOUNT\n"));

    if( dwFlags & DDSD_PITCH     )
        lstrcat( pszFlags, _T("DDSD_PITCH\n"));

    if( dwFlags & DDSD_PIXELFORMAT     )
        lstrcat( pszFlags, _T("DDSD_PIXELFORMAT\n"));

    if( dwFlags & DDSD_REFRESHRATE     )
        lstrcat( pszFlags, _T("DDSD_REFRESHRATE\n"));

    if( dwFlags & DDSD_TEXTURESTAGE      )
        lstrcat( pszFlags, _T("DDSD_TEXTURESTAGE\n"));

    if( dwFlags & DDSD_WIDTH      )
        lstrcat( pszFlags, _T("DDSD_WIDTH\n"));

    lstrcat(pszFlags, _T("\n"));
}


void PixelFormatHelper( DWORD dwFlags, TCHAR * pszFlags)
{
    if( !pszFlags )
        return;

    lstrcpy( pszFlags, _T("    dwFlags: "));

    if( dwFlags & DDPF_ALPHA )
        lstrcat( pszFlags, _T("DDPF_ALPHA, "));

    if( dwFlags & DDPF_ALPHAPIXELS  )
        lstrcat( pszFlags, _T("DDPF_ALPHAPIXELS, "));

    if( dwFlags & DDPF_ALPHAPREMULT  )
        lstrcat( pszFlags, _T("DDPF_ALPHAPREMULT, "));

    if( dwFlags & DDPF_BUMPLUMINANCE  )
        lstrcat( pszFlags, _T("DDPF_BUMPLUMINANCE, "));

    if( dwFlags & DDPF_BUMPDUDV   )
        lstrcat( pszFlags, _T("DDPF_BUMPDUDV, "));

    if( dwFlags & DDPF_COMPRESSED   )
        lstrcat( pszFlags, _T("DDPF_COMPRESSED, "));

    if( dwFlags & DDPF_FOURCC   )
        lstrcat( pszFlags, _T("DDPF_FOURCC, "));

    if( dwFlags & DDPF_LUMINANCE    )
        lstrcat( pszFlags, _T("DDPF_LUMINANCE, "));

    if( dwFlags & DDPF_PALETTEINDEXED1    )
        lstrcat( pszFlags, _T("DDPF_PALETTEINDEXED1, "));

    if( dwFlags & DDPF_PALETTEINDEXED2    )
        lstrcat( pszFlags, _T("DDPF_PALETTEINDEXED2, "));

    if( dwFlags & DDPF_PALETTEINDEXED4    )
        lstrcat( pszFlags, _T("DDPF_PALETTEINDEXED4, "));

    if( dwFlags & DDPF_PALETTEINDEXED8    )
        lstrcat( pszFlags, _T("DDPF_PALETTEINDEXED8, "));

    if( dwFlags & DDPF_PALETTEINDEXEDTO8  )
        lstrcat( pszFlags, _T("DDPF_PALETTEINDEXEDTO8, "));
    
    if( dwFlags & DDPF_RGB   )
        lstrcat( pszFlags, _T("DDPF_RGB, "));

    if( dwFlags & DDPF_RGBTOYUV    )
        lstrcat( pszFlags, _T("DDPF_RGBTOYUV, "));

    if( dwFlags & DDPF_STENCILBUFFER     )
        lstrcat( pszFlags, _T("DDPF_STENCILBUFFER, "));

    if( dwFlags & DDPF_YUV     )
        lstrcat( pszFlags, _T("DDPF_YUV, "));

    if( dwFlags & DDPF_ZBUFFER     )
        lstrcat( pszFlags, _T("DDPF_ZBUFFER, "));

    if( dwFlags & DDPF_ZPIXELS     )
        lstrcat( pszFlags, _T("DDPF_ZPIXELS, "));

    lstrcat( pszFlags, _T("\n"));
}


