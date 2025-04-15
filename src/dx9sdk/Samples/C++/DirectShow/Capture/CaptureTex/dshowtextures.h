//-----------------------------------------------------------------------------
// File: DShowTextures.h
//
// Desc: DirectShow sample code - adds support for DirectShow video capture
//       onto a DirectX 8 texture surface.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//-----------------------------------------------------------------------------

#include <streams.h>

//-----------------------------------------------------------------------------
// Define GUID for Texture Renderer used in CaptureTex sample
// {D7A2CE2F-8221-4b80-B086-B795D9C845F5}
//-----------------------------------------------------------------------------
struct __declspec(uuid("{D7A2CE2F-8221-4b80-B086-B795D9C845F5}")) CLSID_TextureRenderer;

//-----------------------------------------------------------------------------
// CTextureRenderer Class Declarations
//-----------------------------------------------------------------------------
class CTextureRenderer : public CBaseVideoRenderer
{
public:
    CTextureRenderer(LPUNKNOWN pUnk,HRESULT *phr);
    ~CTextureRenderer();

public:
    HRESULT CheckMediaType(const CMediaType *pmt );     // Format acceptable?
    HRESULT SetMediaType(const CMediaType *pmt );       // Video format notification
    HRESULT DoRenderSample(IMediaSample *pMediaSample); // New video sample
    
	LONG m_lVidWidth;	// Video width
	LONG m_lVidHeight;	// Video Height
	LONG m_lVidPitch;	// Video Pitch
};


