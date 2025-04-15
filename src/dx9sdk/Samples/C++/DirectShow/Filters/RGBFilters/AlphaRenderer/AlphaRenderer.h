//------------------------------------------------------------------------------
// File: AlphaRenderer.h
//
// Desc: DirectShow sample code - header for RGBFilters component
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#ifndef __RGBFilters__AlphaRenderer_H
#define __RGBFilters__AlphaRenderer_H

extern AMOVIESETUP_FILTER sudAlphaRenderer;

class CAlphaRenderer : public CBaseRenderer
{
    HWND m_hWnd;
    HDC m_hDC;
    long m_nWidth;
    long m_nHeight;
    BITMAPINFOHEADER m_BMI;
    DWORD * m_pCheckers;

    void _Clear( );

    CAlphaRenderer( IUnknown * pUnk, HRESULT * phr );
    ~CAlphaRenderer( );
    DECLARE_IUNKNOWN
    
    // make sure media type is what we want
    //
    HRESULT CheckMediaType( const CMediaType *pmtIn );

    // have to ovverride this
    //
    HRESULT DoRenderSample( IMediaSample *pMediaSample );

    // have to override this
    //
    HRESULT SetMediaType( const CMediaType *pmt );

    // override these to receive indication of when we change
    // to Pause/Play (Active) or Stop (Inactive) state.
    HRESULT Active();
    HRESULT Inactive();

public:
     
    // only way to make one of these
    //
    static CUnknown * WINAPI CreateInstance(LPUNKNOWN lpunk, HRESULT *phr);

};

#endif