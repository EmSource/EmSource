//------------------------------------------------------------------------------
// File: AllocLib.h
//
// Desc: DirectShow sample code - header file for VMR sample applications
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#ifndef __INC_ALLOCLIB_H__
#define __INC_ALLOCLIB_H__

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

const DWORD*
GetBitMasks(
    const BITMAPINFOHEADER *pHeader
    );

LPBITMAPINFOHEADER
GetbmiHeader(
    const AM_MEDIA_TYPE *pMediaType
    );

void
FixupMediaType(
    AM_MEDIA_TYPE* pmt
    );

LPRECT
GetTargetRectFromMediaType(
    const AM_MEDIA_TYPE *pMediaType
    );

struct TargetScale
{
    float fX;
    float fY;
};

void
GetTargetScaleFromMediaType(
    const AM_MEDIA_TYPE *pMediaType,
    TargetScale* pScale
    );

LPRECT
GetSourceRectFromMediaType(
    const AM_MEDIA_TYPE *pMediaType
    );

HRESULT
ConvertSurfaceDescToMediaType(
    const LPDDSURFACEDESC2 pSurfaceDesc,
    const AM_MEDIA_TYPE* pTemplateMediaType,
    AM_MEDIA_TYPE** ppMediaType
    );


HRESULT
PaintDDrawSurfaceBlack(
    LPDIRECTDRAWSURFACE7 pDDrawSurface
    );

HRESULT
GetImageAspectRatio(
    const AM_MEDIA_TYPE* pMediaType,
    long* lpARWidth,
    long* lpARHeight
    );


bool
EqualSizeRect(
    const RECT* lpRc1,
    const RECT* lpRc2
    );


bool
ContainedRect(
    const RECT* lpRc1,
    const RECT* lpRc2
    );

void
LetterBoxDstRect(
    LPRECT lprcLBDst,
    const RECT& rcSrc,
    const RECT& rcDst,
    LPRECT lprcBdrTL,
    LPRECT lprcBdrBR
    );


void
AspectRatioCorrectSize(
    LPSIZE lpSizeImage,
    const SIZE& sizeAr
    );

enum {
    TXTR_POWER2 = 0x01,
    TXTR_AGPMEM = 0x02,
    TXTR_SRCKEY = 0x04
};

HRESULT
GetTextureCaps(
    LPDIRECTDRAW7 pDD,
    DWORD* ptc
    );

DWORD
DDColorMatch(
    IDirectDrawSurface7 *pdds,
    COLORREF rgb,
    HRESULT& hr
    );

HRESULT
VMRCopyFourCC(
    LPDIRECTDRAWSURFACE7 lpDst,
    LPDIRECTDRAWSURFACE7 lpSrc
    );


#ifdef DEBUG
void __inline DumpDDSAddress(const TCHAR *szText, LPDIRECTDRAWSURFACE7 lpDDS)
{
    DDSURFACEDESC2 ddSurfaceDesc;
    INITDDSTRUCT(ddSurfaceDesc);

    HRESULT hr;

    hr = lpDDS->Lock(NULL, &ddSurfaceDesc, DDLOCK_NOSYSLOCK | DDLOCK_WAIT, (HANDLE)NULL);
    if (hr != DD_OK) {
        DbgLog((LOG_TRACE, 0, TEXT("Lock failed hr = %#X"), hr));
    }

    hr = lpDDS->Unlock(NULL);
    if (hr != DD_OK) {
        DbgLog((LOG_TRACE, 0, TEXT("Unlock failed hr = %#X"), hr));
    }

    DbgLog((LOG_TRACE, 0, TEXT("%s%p"), szText, ddSurfaceDesc.lpSurface));
}
#else
#define DumpDDSAddress( _x_, _y_ )
#endif


#endif
