//-----------------------------------------------------------------------------
// File: DShowTextures.cpp
//
// Desc: DirectShow sample code - adds support for DirectShow video capture
//       onto a DirectX 8 texture surface.
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
// Global DirectShow pointers
//-----------------------------------------------------------------------------
CComPtr<IGraphBuilder>  g_pGB;          // GraphBuilder
CComPtr<IMediaControl>  g_pMC;          // Media Control
CComPtr<IBaseFilter>    g_pRenderer;    // Texture Renderer Filter

IBaseFilter           * g_pSrcFilter=NULL;
ICaptureGraphBuilder2 * g_pCapture = NULL;  // Helps to render capture graphs
CCritSec g_cs;

D3DFORMAT               g_TextureFormat; // Texture format


//-----------------------------------------------------------------------------
// InitDShowTextureRenderer : Create and run DirectShow capture filter graph
//-----------------------------------------------------------------------------
HRESULT InitDShowTextureRenderer()
{
    HRESULT hr = S_OK;
    CComPtr<IBaseFilter>    pFSrc;          // Source Filter
    CComPtr<IPin>           pFSrcPinOut;    // Source Filter Output Pin   
    CTextureRenderer        *pCTR=0;        // DirectShow Texture renderer
    
    // Create the filter graph
    if (FAILED(g_pGB.CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC)))
        return E_FAIL;

    // Get the graph's media control interface
    g_pGB.QueryInterface(&g_pMC);
    
    // Create the Texture Renderer object
    pCTR = new CTextureRenderer(NULL, &hr);
    if (FAILED(hr) || !pCTR)
    {
        Msg(TEXT("Could not create texture renderer object!  hr=0x%x"), hr);
        return E_FAIL;
    }
    
    // Get a pointer to the IBaseFilter interface on the TextureRenderer
    // and add it to the existing graph.  Save the renderer interface
    // for later reconnection, if needed.
    g_pRenderer = pCTR;

    if (FAILED(hr = g_pGB->AddFilter(g_pRenderer, L"Texture Renderer")))
    {
        Msg(TEXT("Could not add renderer filter to graph!  hr=0x%x"), hr);
        return hr;
    }

    // Initialize the first attached video capture device and set
    // our 3D renderer to render the incoming video    
    if (FAILED(hr = CaptureVideo(g_pRenderer)))
    {
        // CaptureVideo will display an appropriate error message
        return hr;
    }
  
#ifdef REGISTER_FILTERGRAPH
    // Register the graph in the Running Object Table (for debug purposes)
    AddToROT(g_pGB);
#endif
    
    // Start the graph running;
    if (FAILED(hr = g_pMC->Run()))
    {
        Msg(TEXT("Could not run the DirectShow graph!  hr=0x%x"), hr);
        return hr;
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// ReconnectDShowRenderer : Rebuild graph after D3D surface loss
//-----------------------------------------------------------------------------
HRESULT ReconnectDShowRenderer()
{
    CAutoLock lock(&g_cs);

    HRESULT hr;
    CTextureRenderer * pCTR=0;        // DirectShow Texture renderer

    // Stop the graph
    hr = g_pMC->Stop();

    // Wait for the stop to complete.  The graph must be completely stopped
    // in order to properly disconnect the pins and remove the renderer filter.
    OAFilterState fs;
    hr = g_pMC->GetState(1000, &fs);      

    // Remove the current renderer from the graph to disconnect its input pin
    // from the output pin of the capture filter
    hr = g_pGB->RemoveFilter(g_pRenderer);

    // Add the renderer back to the graph
    if (FAILED(hr = g_pGB->AddFilter(g_pRenderer, L"Texture Renderer")))
    {
        Msg(TEXT("Could not add renderer filter back to graph!  hr=0x%x"), hr);
        return hr;
    }

    // Render the preview pin on the video capture filter to reconnect the renderer
    hr = g_pCapture->RenderStream (&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
                                   g_pSrcFilter, NULL, g_pRenderer);
    if (FAILED(hr))
    {
        Msg(TEXT("Could not render the capture stream after surface loss.  hr=0x%x"), hr);
        return hr;
    }   

    // Resume playback
    hr = g_pMC->Run();

    return hr;
}

//-----------------------------------------------------------------------------
// CleanupDShow
//-----------------------------------------------------------------------------
void CleanupDShow(void)
{
#ifdef REGISTER_FILTERGRAPH
    // Remove graph from Running Object Table
    RemoveFromROT();
#endif

    // Shut down the graph
    if (!(!g_pMC)) g_pMC->Stop();

    // Release interfaces
    SAFE_RELEASE(g_pSrcFilter);
    SAFE_RELEASE(g_pCapture);

    // Release smart COM pointers
    if (!(!g_pMC)) g_pMC.Release();
    if (!(!g_pGB)) g_pGB.Release();
}
    

//-----------------------------------------------------------------------------
// CTextureRenderer constructor
//-----------------------------------------------------------------------------
CTextureRenderer::CTextureRenderer( LPUNKNOWN pUnk, HRESULT *phr )
                                  : CBaseVideoRenderer(__uuidof(CLSID_TextureRenderer), 
                                        NAME("Texture Renderer"), pUnk, phr)
{
    // Store and AddRef the texture for our use.
    ASSERT(phr);
    if (phr)
        *phr = S_OK;
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
    
    CheckPointer(pmt,E_POINTER);

    // Reject the connection if this is not a video type
    if( *pmt->FormatType() != FORMAT_VideoInfo ) {
        return E_INVALIDARG;
    }
    
    // Only accept RGB24 video
    pvi = (VIDEOINFO *)pmt->Format();

    if(IsEqualGUID( *pmt->Type(),    MEDIATYPE_Video)  &&
       IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_RGB24))
    {
        hr = S_OK;
    }
    
    return hr;
}


//-----------------------------------------------------------------------------
// SetMediaType: Graph connection has been made. 
//-----------------------------------------------------------------------------
HRESULT CTextureRenderer::SetMediaType(const CMediaType *pmt)
{
    CAutoLock lock(&g_cs);

    HRESULT hr;

    // Retreive the size of this media type
    VIDEOINFO *pviBmp;                      // Bitmap info header
    pviBmp = (VIDEOINFO *)pmt->Format();

    m_lVidWidth  = pviBmp->bmiHeader.biWidth;
    m_lVidHeight = abs(pviBmp->bmiHeader.biHeight);
    m_lVidPitch  = (m_lVidWidth * 3 + 3) & ~(3); // We are forcing RGB24

    // Create the texture that maps to this media type
    hr = D3DXCreateTexture(g_pd3dDevice,
                           m_lVidWidth, m_lVidHeight,
                           1, 0, 
                           D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &g_pTexture );
    if ( FAILED( hr ))
    {
        Msg(TEXT("Could not create the D3DX texture!  hr=0x%x"), hr);
        return hr;
    }

    // D3DXCreateTexture can silently change the parameters on us
    D3DSURFACE_DESC ddsd;
    ZeroMemory(&ddsd, sizeof(ddsd));

    if ( FAILED( hr = g_pTexture->GetLevelDesc( 0, &ddsd ) ) ) {
        Msg(TEXT("Could not get level Description of D3DX texture! hr = 0x%x"), hr);
        return hr;
    }

    // Save format info
    g_TextureFormat = ddsd.Format;

    if (g_TextureFormat != D3DFMT_X8R8G8B8 &&
        g_TextureFormat != D3DFMT_A1R5G5B5) {
        Msg(TEXT("Texture is format we can't handle! Format = 0x%x"), g_TextureFormat);
        return VFW_E_TYPE_NOT_ACCEPTED;
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// DoRenderSample: A sample has been delivered. Copy it to the texture.
//-----------------------------------------------------------------------------
HRESULT CTextureRenderer::DoRenderSample( IMediaSample * pSample )
{
    CAutoLock lock(&g_cs);

    BYTE  *pBmpBuffer, *pTxtBuffer; // Bitmap buffer, texture buffer
    LONG  lTxtPitch;                // Pitch of bitmap, texture

    BYTE  * pbS = NULL;
    DWORD * pdwS = NULL;
    DWORD * pdwD = NULL;
    UINT row, col, dwordWidth;
    
    // If we have lost the Direct3D device or surface, don't render now
    if (!g_pTexture || (g_bDeviceLost))
        return E_FAIL;

    // Get the video bitmap buffer
    CheckPointer(pSample,E_POINTER);
    pSample->GetPointer( &pBmpBuffer );

    // Lock the Texture
    D3DLOCKED_RECT d3dlr;
    if (FAILED(g_pTexture->LockRect(0, &d3dlr, 0, 0)))
        return E_FAIL;
    
    // Get the texture buffer & pitch
    pTxtBuffer = static_cast<byte *>(d3dlr.pBits);
    lTxtPitch = d3dlr.Pitch;
    
    // Copy the bits    
    if (g_TextureFormat == D3DFMT_X8R8G8B8) 
    {
        // Instead of copying data bytewise, we use DWORD alignment here.
        // We also unroll loop by copying 4 pixels at once.
        //
        // original BYTE array is [b0][g0][r0][b1][g1][r1][b2][g2][r2][b3][g3][r3]
        //
        // aligned DWORD array is     [b1 r0 g0 b0][g2 b2 r1 g1][r3 g3 b3 r2]
        //
        // We want to transform it to [ff r0 g0 b0][ff r1 g1 b1][ff r2 g2 b2][ff r3 b3 g3]
        // below, bitwise operations do exactly this.

        dwordWidth = m_lVidWidth / 4; // aligned width of the row, in DWORDS
                                      // (pixel by 3 bytes over sizeof(DWORD))

        for( row = 0; row< (UINT)m_lVidHeight; row++)
        {
            pdwS = ( DWORD*)pBmpBuffer;
            pdwD = ( DWORD*)pTxtBuffer;

            for( col = 0; col < dwordWidth; col ++ )
            {
                pdwD[0] =  pdwS[0] | 0xFF000000;
                pdwD[1] = ((pdwS[1]<<8)  | 0xFF000000) | (pdwS[0]>>24);
                pdwD[2] = ((pdwS[2]<<16) | 0xFF000000) | (pdwS[1]>>16);
                pdwD[3] = 0xFF000000 | (pdwS[2]>>8);
                pdwD +=4;
                pdwS +=3;
            }

            // we might have remaining (misaligned) bytes here
            pbS = (BYTE*) pdwS;
            for( col = 0; col < (UINT)m_lVidWidth % 4; col++)
            {
                *pdwD = 0xFF000000     |
                        (pbS[2] << 16) |
                        (pbS[1] <<  8) |
                        (pbS[0]);
                pdwD++;
                pbS += 3;           
            }

            pBmpBuffer  += m_lVidPitch;
            pTxtBuffer += lTxtPitch;
        }// for rows
    }

    if (g_TextureFormat == D3DFMT_A1R5G5B5) 
    {
        for(int y = 0; y < m_lVidHeight; y++ ) 
        {
            BYTE *pBmpBufferOld = pBmpBuffer;
            BYTE *pTxtBufferOld = pTxtBuffer;   

            for (int x = 0; x < m_lVidWidth; x++) 
            {
                *(WORD *)pTxtBuffer = (WORD)
                    (0x8000 +
                    ((pBmpBuffer[2] & 0xF8) << 7) +
                    ((pBmpBuffer[1] & 0xF8) << 2) +
                    (pBmpBuffer[0] >> 3));

                pTxtBuffer += 2;
                pBmpBuffer += 3;
            }

            pBmpBuffer = pBmpBufferOld + m_lVidPitch;
            pTxtBuffer = pTxtBufferOld + lTxtPitch;
        }
    }

    // Unlock the Texture
    if (FAILED(g_pTexture->UnlockRect(0)))
        return E_FAIL;
    
    return S_OK;
}


#ifdef REGISTER_FILTERGRAPH

//-----------------------------------------------------------------------------
// Running Object Table functions: Used to debug. By registering the graph
// in the running object table, GraphEdit is able to connect to the running
// graph. This code should be removed before the application is shipped in
// order to avoid third parties from spying on your graph.
//-----------------------------------------------------------------------------
DWORD dwROTReg = 0xfedcba98;

HRESULT AddToROT(IUnknown *pUnkGraph) 
{
    IMoniker * pmk;
    IRunningObjectTable *pROT;
    if (FAILED(GetRunningObjectTable(0, &pROT))) {
        return E_FAIL;
    }

    WCHAR wsz[256];
    wsprintfW(wsz, L"FilterGraph %08x  pid %08x\0", (DWORD_PTR) 0, GetCurrentProcessId());

    HRESULT hr = CreateItemMoniker(L"!", wsz, &pmk);
    if (SUCCEEDED(hr)) 
    {
        // Use the ROTFLAGS_REGISTRATIONKEEPSALIVE to ensure a strong reference
        // to the object.  Using this flag will cause the object to remain
        // registered until it is explicitly revoked with the Revoke() method.
        //
        // Not using this flag means that if GraphEdit remotely connects
        // to this graph and then GraphEdit exits, this object registration 
        // will be deleted, causing future attempts by GraphEdit to fail until
        // this application is restarted or until the graph is registered again.
        hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, 
                            pmk, &dwROTReg);
        pmk->Release();
    }

    pROT->Release();
    return hr;
}


void RemoveFromROT(void)
{
    IRunningObjectTable *pirot=0;

    if (SUCCEEDED(GetRunningObjectTable(0, &pirot))) 
    {
        pirot->Revoke(dwROTReg);
        pirot->Release();
    }
}

#endif


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

    MessageBox(NULL, szBuffer, TEXT("DirectShow CaptureTex Sample\0"), 
               MB_OK | MB_ICONERROR);
}


HRESULT CaptureVideo(IBaseFilter *pRenderer)
{
    HRESULT hr;

    // Create the capture graph builder object to assist in
    // building the video capture filter graph
    hr = CoCreateInstance (CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC,
                           IID_ICaptureGraphBuilder2, (void **) &g_pCapture);
    if (FAILED(hr))
    {
        Msg(TEXT("Could not create the capture graph builder!  hr=0x%x\0"), hr);
        return hr;
    }
    
    // Attach the existing filter graph to the capture graph
    hr = g_pCapture->SetFiltergraph(g_pGB);
    if (FAILED(hr))
    {
        Msg(TEXT("Failed to set capture filter graph!  hr=0x%x\0"), hr);
        return hr;
    }

    // Use the system device enumerator and class enumerator to find
    // a video capture/preview device, such as a desktop USB video camera.
    hr = FindCaptureDevice(&g_pSrcFilter);
    if (FAILED(hr))
    {
        // Don't display a message because FindCaptureDevice will handle it
        return hr;
    }
   
    // Add the returned capture filter to our graph.
    hr = g_pGB->AddFilter(g_pSrcFilter, L"Video Capture");
    if (FAILED(hr))
    {
        Msg(TEXT("Could not add the capture filter to the graph.  hr=0x%x\r\n\r\n")
            TEXT("Make sure that a video capture device is connected and functional\n")
            TEXT("and is not being used by another capture application.\0"), hr);
        SAFE_RELEASE(g_pSrcFilter);
        return hr;
    }

    // Render the preview pin on the video capture filter.
    // This will create and connect any necessary transform filters.
    // We pass a pointer to the IBaseFilter interface of our CTextureRenderer
    // video renderer, which will draw the incoming video onto a D3D surface.
    hr = g_pCapture->RenderStream (&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
                                   g_pSrcFilter, NULL, pRenderer);
    if (FAILED(hr))
    {
        Msg(TEXT("Could not render the capture stream.  hr=0x%x\r\n\r\n")
            TEXT("Make sure that a video capture device is connected and functional\n")
            TEXT("and is not being used by another capture application.\0"), hr);
        SAFE_RELEASE(g_pSrcFilter);
        return hr;
    }

    return S_OK;
}


HRESULT FindCaptureDevice(IBaseFilter ** ppSrcFilter)
{
    HRESULT hr;
    IBaseFilter * pSrc = NULL;
    CComPtr <IMoniker> pMoniker =NULL;
    ULONG cFetched;

    if (!ppSrcFilter)
        return E_POINTER;
   
    // Create the system device enumerator
    CComPtr <ICreateDevEnum> pDevEnum =NULL;

    hr = CoCreateInstance (CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           IID_ICreateDevEnum, (void **) &pDevEnum);
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't create system enumerator!  hr=0x%x"), hr);
        return hr;
    }

    // Create an enumerator for the video capture devices
    CComPtr <IEnumMoniker> pClassEnum = NULL;

    hr = pDevEnum->CreateClassEnumerator (CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't create class enumerator!  hr=0x%x"), hr);
        return hr;
    }

    // If there are no enumerators for the requested type, then 
    // CreateClassEnumerator will succeed, but pClassEnum will be NULL.
    if (pClassEnum == NULL)
    {
        MessageBox(NULL,TEXT("No video capture device was detected.\r\n\r\n")
                   TEXT("This sample requires a video capture device, such as a USB WebCam,\r\n")
                   TEXT("to be installed and working properly.  The sample will now close."),
                   TEXT("No Video Capture Hardware"), MB_OK | MB_ICONINFORMATION);
        return E_FAIL;
    }

    // Use the first video capture device on the device list.
    // Note that if the Next() call succeeds but there are no monikers,
    // it will return S_FALSE (which is not a failure).  Therefore, we
    // check that the return code is S_OK instead of using SUCCEEDED() macro.
    if (S_OK == (pClassEnum->Next (1, &pMoniker, &cFetched)))
    {
        // Bind Moniker to a filter object
        hr = pMoniker->BindToObject(0,0,IID_IBaseFilter, (void**)&pSrc);
        if (FAILED(hr))
        {
            Msg(TEXT("Couldn't bind moniker to filter object!  hr=0x%x"), hr);
            return hr;
        }
    }
    else
    {
        Msg(TEXT("Unable to access video capture device!"));   
        return E_FAIL;
    }

    // Copy the found filter pointer to the output parameter.
    // Do NOT Release() the reference, since it will still be used
    // by the calling function.
    *ppSrcFilter = pSrc;

    return hr;
}


