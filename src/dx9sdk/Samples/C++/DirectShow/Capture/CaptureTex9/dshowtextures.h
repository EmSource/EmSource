//-----------------------------------------------------------------------------
// File: DShowTextures.h
//
// Desc: DirectShow sample code - adds support for DirectShow video capture
//       onto a DirectX 9 texture surface.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Define GUID for Texture Renderer used in CaptureTex9 sample
// {7A013080-900F-4c19-918B-5560C2819EFB}
//-----------------------------------------------------------------------------
struct __declspec(uuid("{7A013080-900F-4c19-918B-5560C2819EFB}")) CLSID_TextureRenderer9;

//-----------------------------------------------------------------------------
// CTextureRenderer Class Declarations
//-----------------------------------------------------------------------------
class CTextureRenderer : public CBaseVideoRenderer
{
public:
    CTextureRenderer(CCustomPresentation *pPres, LPUNKNOWN pUnk,HRESULT *phr);
    ~CTextureRenderer();

public:
    HRESULT CheckMediaType(const CMediaType *pmt );     // Format acceptable?
    HRESULT SetMediaType(const CMediaType *pmt );       // Video format notification
    HRESULT DoRenderSample(IMediaSample *pMediaSample); // New video sample

private:
    CCustomPresentation* m_pCP;
    CComPtr<IDirect3DSurface9>      m_pSurfBuf;     // we use this surface to copy media sample to -- 
                                                    // then we will use Blt from m_pSurfBuf to 
                                                    // m_pTexture to provide format translation
    D3DFORMAT  m_MediaFormat;                       // format of the surface that gets media samples

    LONG m_lVidWidth;   // Video width
    LONG m_lVidHeight;  // Video Height
    LONG m_lVidPitch;   // Video Pitch
};


