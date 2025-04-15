//-----------------------------------------------------------------------------
// File: DShowTextures.cpp
//
// Desc: DirectShow sample code - adds support for DirectShow video capture
//       onto a DirectX 9 texture surface.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

#include "Textures.h"
#include "DShowTextures.h"

// An application can advertise the existence of its filter graph
// by registering the graph with a global Running Object Table (ROT).
// The GraphEdit application can detect and remotely view the running
// filter graph, allowing you to 'spy' on the graph with GraphEdit.
//
// To enable registration in this sample, define REGISTER_FILTERGRAPH.
//
#define REGISTER_FILTERGRAPH

//-----------------------------------------------------------------------------
// CTextureRenderer constructor
//-----------------------------------------------------------------------------
CTextureRenderer::CTextureRenderer( CCustomPresentation *pPres, LPUNKNOWN pUnk, HRESULT *phr )
                                  : CBaseVideoRenderer(__uuidof(CLSID_TextureRenderer9), 
                                    NAME("Texture Renderer"), pUnk, phr)
                                  , m_pCP( pPres)
{
    // Store and AddRef the texture for our use.
    ASSERT(phr);
    if (phr)
    {
        if( !pPres )
        {
            *phr = E_INVALIDARG;
        }
        else
        {
            *phr = S_OK;
        }
    }
}


//-----------------------------------------------------------------------------
// CTextureRenderer destructor
//-----------------------------------------------------------------------------
CTextureRenderer::~CTextureRenderer()
{
    // Do nothing
}


//-----------------------------------------------------------------------------
// CheckMediaType: This method forces the graph to give us an R8G8B8 video
// type, making our copy to texture memory trivial.
//-----------------------------------------------------------------------------
HRESULT CTextureRenderer::CheckMediaType(const CMediaType *pmt)
{
    HRESULT   hr = E_FAIL;
    VIDEOINFO *pvi=0;
    CComPtr<IDirect3DTexture9> pSurfBuffer;
    D3DSURFACE_DESC ddsd;
    
    CheckPointer(pmt,E_POINTER);
    ZeroMemory( &ddsd, sizeof( D3DSURFACE_DESC ));

    ASSERT( m_pCP && m_pCP->GetDevice());
    try
    {
        // Reject the connection if this is not a video type
        if( *pmt->FormatType() != FORMAT_VideoInfo ) 
        {
            return E_INVALIDARG;
        }
        
        // Only accept RGB24 or YUYV video
        pvi = (VIDEOINFO *)pmt->Format();

        if( IsEqualGUID( *pmt->Type(), MEDIATYPE_Video) )
        {
            hr = S_OK;

            if( IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_RGB24) )
            {
                m_MediaFormat = D3DFMT_R8G8B8;
            }
            else if( IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_YUYV ) )
            {
                m_MediaFormat = D3DFMT_YUY2;
            }
            else
            {
                hr = DDERR_INVALIDPIXELFORMAT;
            }
        }
        if( FAILED(hr))
        {
            return hr;
        }
        
        if( D3DFMT_YUY2 == m_MediaFormat)
        {
            hr = m_pCP->GetDevice()->CreateTexture( pvi->bmiHeader.biWidth, 
                                                    pvi->bmiHeader.biHeight,
                                                    1, 0, 
                                                    m_MediaFormat, 
                                                    D3DPOOL_MANAGED, 
                                                    &pSurfBuffer, 
                                                    NULL);
            if( FAILED(hr))
            {
                Msg(TEXT("Failed to create buffer texture.  hr=0x%x"), hr);
                return hr;
            }

            hr = pSurfBuffer->GetSurfaceLevel(0, &m_pSurfBuf);
            if( FAILED(hr))
            {
                Msg(TEXT("Cannot find IDirect3DSurface9 from buffer texture.  hr=0x%x"), hr);
                return hr;
            }

            hr = m_pSurfBuf->GetDesc( &ddsd );
        }
    }// try
    catch(...)
    {
        Msg(TEXT("Failed to check media type in the renderer. Unhandled exception hr=0x%x"), E_UNEXPECTED);
        hr = E_UNEXPECTED;
    }   
    return hr;
}


//-----------------------------------------------------------------------------
// SetMediaType: Graph connection has been made. 
//-----------------------------------------------------------------------------
HRESULT CTextureRenderer::SetMediaType(const CMediaType *pmt)
{
    HRESULT hr = S_OK;
    VIDEOINFO *pviBmp = NULL;   // Bitmap info header
    CComPtr<IDirect3DTexture9> pTexture;

    try
    {
        // Retreive the size of this media type
        pviBmp = (VIDEOINFO *)pmt->Format();

        m_lVidWidth  = pviBmp->bmiHeader.biWidth;
        m_lVidHeight = abs(pviBmp->bmiHeader.biHeight);
        m_lVidPitch  = (m_lVidWidth * 3 + 3) & ~(3); // We are forcing RGB24

        // Create the texture that fits this media type
        ASSERT( m_pCP && m_pCP->GetDevice());

        hr = m_pCP->CreateTexture( m_lVidWidth, m_lVidHeight, D3DFMT_A8R8G8B8);
        if( FAILED(hr))
        {
            Msg(TEXT("Could not create the D3DX texture.  hr=0x%x"), hr);
            return hr;
        }

    }// try
    catch(...)
    {
        Msg(TEXT("Failed to set media type in the renderer. Unhandled exception hr=0x%x"), E_UNEXPECTED);
        return hr;
    }

    return hr;
}


//-----------------------------------------------------------------------------
// DoRenderSample: A sample has been delivered. Copy it to the texture.
//-----------------------------------------------------------------------------
HRESULT CTextureRenderer::DoRenderSample( IMediaSample * pSample )
{
    HRESULT hr = S_OK;

#ifdef RENDER_PERF
    DWORD dwStart;
    DWORD dwElapsed;
    TCHAR sz[MAX_PATH];
#endif    

    try
    {
        if( D3DFMT_YUY2 == m_MediaFormat )
        {
            // first, we copy sample onto m_pSurfBuf, then ...
            ASSERT(0);
        }
        else // media format is RGB24
        {

#ifdef RENDER_PERF
            dwStart = timeGetTime();
#endif

            // Copy the media sample to the texture
            hr = m_pCP->CopyMediaSample( pSample, m_lVidPitch );

#ifdef RENDER_PERF
            dwElapsed = timeGetTime() - dwStart;
            wsprintf( sz, TEXT("\nCopy sample: %ld ticks"), dwElapsed);
            OutputDebugString( sz);
#endif

        }
    }
    catch(...)
    {
    
    }
    return hr;
}


//-----------------------------------------------------------------------------
// Msg: Display an error message box if needed
//-----------------------------------------------------------------------------
void Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    MessageBox(NULL, szBuffer, TEXT("DirectShow CaptureTex9 Sample\0"), 
               MB_OK | MB_ICONERROR);
}






