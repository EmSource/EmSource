//------------------------------------------------------------------------------
// File: TextType.cpp
//
// Desc: DirectShow sample code - implementation of CTextMediaType class.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <atlbase.h>

#include <streams.h>

#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <wchar.h>

#include "resource.h"
#include "texttype.h"


//
// AsText
//
// Return the media type as a text string. Will place szAfterMajor after
// the text string for the major type and szAfterOthers after all other
// strings, apart from the last one.
//
void CTextMediaType::AsText(LPTSTR szType,
                            unsigned int iLen,
                            LPTSTR szAfterMajor,
                            LPTSTR szAfterOthers,
                            LPTSTR szAtEnd)
{
    ASSERT(szType);

    //
    // Convert Majortype to string
    //
    TCHAR szMajorType[100];
    UINT  iMajorType = 100;

    CLSID2String(szMajorType, iMajorType, &majortype);
    szMajorType[99] = 0;        // Ensure null-termination

    //
    // Convert Subtype to string
    //
    TCHAR szSubType[100];
    UINT  iSubType = 100;
    CLSID2String(szSubType, iSubType, &subtype);
    szSubType[99] = 0;        // Ensure null-termination

    //
    // Convert Format to string
    //
    TCHAR szFormat[300];
    UINT  iFormat = 300;
    Format2String(szFormat, iFormat, FormatType(), Format(), FormatLength());
    szFormat[299] = 0;        // Ensure null-termination

    //
    // Obtain the strings preceeding the Major Type, Sub Type and Format.
    //
    TCHAR szPreMajor[50];
    TCHAR szPreSub[50];
    TCHAR szPreFormat[50];

    LoadString(g_hInst, IDS_PREMAJOR,  szPreMajor,  50);
    LoadString(g_hInst, IDS_PRESUB,    szPreSub,    50);
    LoadString(g_hInst, IDS_PREFORMAT, szPreFormat, 50);
    szPreMajor[49] = szPreSub[49] = szPreFormat[49] = 0;    // Ensure NULL-term

    _sntprintf(szType, iLen, TEXT("%s%s%s%s%s%s%s%s%s\0"),
                szPreMajor,  szMajorType, szAfterMajor,
                szPreSub,    szSubType,   szAfterOthers,
                szPreFormat, szFormat,    szAtEnd);
}


//
// CLSID2String
//
// Find a string description for a given GUID
//
void CTextMediaType::CLSID2String(LPTSTR szBuffer,
                                  UINT iLength,
                                  const GUID* pGuid)
{
    ASSERT(szBuffer);
    ASSERT(pGuid);

    USES_CONVERSION;

    // Read the GUID name from the global table.  Use A2T macro
    // to convert to UNICODE string if necessary.
    TCHAR *pszGuidName = A2T(GuidNames[*pGuid]);

    UINT nLength = _tcslen(pszGuidName);

    _tcsncpy(szBuffer, pszGuidName, min(nLength, iLength));
    szBuffer[nLength] = 0;      // Ensure null-termination
}


//
// Format2String
//
// Converts a format block to a string
//
void CTextMediaType::Format2String(LPTSTR szBuffer,
                                   UINT iLength,
                                   const GUID* pFormatType,
                                   BYTE* pFormat,
                                   ULONG lFormatLength)
{
    UNREFERENCED_PARAMETER(lFormatLength);
    ASSERT(szBuffer);
    ASSERT(pFormatType);
    ASSERT(pFormat);

    //
    // Get the name of the format
    //
    TCHAR szName[50];
    UINT iName = 50;
    CLSID2String(szName, iName, pFormatType);
    szName[49] = 0;     // Ensure null-termination

    //
    // Video Format
    //
    if (IsEqualGUID(*pFormatType, FORMAT_VideoInfo) ||
        IsEqualGUID(*pFormatType, FORMAT_MPEGVideo)) 
    {
        VIDEOINFOHEADER * pVideoFormat = (VIDEOINFOHEADER *) pFormat;

        _sntprintf(szBuffer, iLength, TEXT("%4.4hs %dx%d, %d bits\0")
                   , (pVideoFormat->bmiHeader.biCompression == 0) ? TEXT("RGB\0") :
                         ((pVideoFormat->bmiHeader.biCompression == BI_BITFIELDS) ? TEXT("BITF\0") :
                             (LPTSTR) &pVideoFormat->bmiHeader.biCompression )
                   , pVideoFormat->bmiHeader.biWidth
                   , pVideoFormat->bmiHeader.biHeight
                   , pVideoFormat->bmiHeader.biBitCount);

         return;
    }

    //
    // Audio Format
    //
    if (IsEqualGUID(*pFormatType, FORMAT_WaveFormatEx)) 
    {
        WAVEFORMATEX *pWaveFormat = (WAVEFORMATEX *) pFormat;

        // !!! use ACM to get format type name?
        _sntprintf(szBuffer, iLength, TEXT("%s: %.3f KHz %d bit %s \0")
                   , szName
                   , (double) pWaveFormat->nSamplesPerSec / 1000.0
                   , pWaveFormat->wBitsPerSample
                   , pWaveFormat->nChannels == 1 ? TEXT("mono\0") : TEXT("stereo\0")
                  );

        return;
    }

    _sntprintf(szBuffer, iLength, TEXT("%s\0"), szName);
}
