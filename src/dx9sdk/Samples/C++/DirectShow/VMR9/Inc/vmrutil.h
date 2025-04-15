//------------------------------------------------------------------------------
// File: VMRUtil.h
//
// Desc: DirectShow sample code - header file for C++ VMR9 sample applications
//       that do not use MFC.  This header contains several methods useful
//       for creating filter graphs with the Video Mixing Renderer 9.
//
//       Because graph building with the VMR9 requires a few extra steps
//       in order to guarantee that the VMR9 is used instead of another
//       video renderer, these helper methods are implemented in a header file
//       so that they can be easily integrated into a non-MFC application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#ifndef __INC_VMRUTIL_H__
#define __INC_VMRUTIL_H__

#pragma once

#ifndef JIF
#define JIF(x) if (FAILED(hr=(x))) {return hr;}
#endif

//----------------------------------------------------------------------------
//  VerifyVMR9
// 
//  Verifies that VMR9 COM objects exist on the system and that the VMR9
//  can be instantiated.
//
//  Returns: FALSE if the VMR9 can't be created
//----------------------------------------------------------------------------

BOOL VerifyVMR9(void)
{
    HRESULT hr;

    // Verify that the VMR exists on this system
    IBaseFilter* pBF = NULL;
    hr = CoCreateInstance(CLSID_VideoMixingRenderer9, NULL,
                          CLSCTX_INPROC,
                          IID_IBaseFilter,
                          (LPVOID *)&pBF);
    if(SUCCEEDED(hr))
    {
        pBF->Release();
        return TRUE;
    }
    else
    {
        MessageBox(NULL, 
            TEXT("This application requires the Video Mixing Renderer, which is present\r\n")
            TEXT("only on DirectX 9 systems with hardware video acceleration enabled.\r\n\r\n")

            TEXT("The Video Mixing Renderer (VMR9) is not enabled when viewing a \r\n")
            TEXT("remote Windows XP machine through a Remote Desktop session.\r\n")
            TEXT("You can run VMR-enabled applications only on your local machine.\r\n\r\n")

            TEXT("To verify that hardware acceleration is enabled on a Windows XP\r\n")
            TEXT("system, follow these steps:\r\n")
            TEXT("-----------------------------------------------------------------------\r\n")
            TEXT(" - Open 'Display Properties' in the Control Panel\r\n")
            TEXT(" - Click the 'Settings' tab\r\n")
            TEXT(" - Click on the 'Advanced' button at the bottom of the page\r\n")
            TEXT(" - Click on the 'Troubleshooting' tab in the window that appears\r\n")
            TEXT(" - Verify that the 'Hardware Acceleration' slider is at the rightmost position\r\n")

            TEXT("\r\nThis sample will now exit."),

            TEXT("Video Mixing Renderer (VMR9) capabilities are required"), MB_OK);

        return FALSE;
    }
}


BOOL IsWindowsMediaFile(WCHAR *lpszFile)
{
    USES_CONVERSION;
    TCHAR szFilename[MAX_PATH];

    // Copy the file name to a local string and convert to lowercase
    _tcsncpy(szFilename, W2T(lpszFile), NUMELMS(szFilename));
    szFilename[MAX_PATH-1] = 0;
    _tcslwr(szFilename);

    if (_tcsstr(szFilename, TEXT(".asf")) ||
        _tcsstr(szFilename, TEXT(".wma")) ||
        _tcsstr(szFilename, TEXT(".wmv")))
        return TRUE;
    else
        return FALSE;
}


HRESULT GetUnconnectedPin(
    IBaseFilter *pFilter,   // Pointer to the filter.
    PIN_DIRECTION PinDir,   // Direction of the pin to find.
    IPin **ppPin)           // Receives a pointer to the pin.
{
    IEnumPins *pEnum = 0;
    IPin *pPin = 0;

    if (!ppPin)
        return E_POINTER;
    *ppPin = 0;

    // Get a pin enumerator
    HRESULT hr = pFilter->EnumPins(&pEnum);
    if (FAILED(hr))
        return hr;

    // Look for the first unconnected pin
    while (pEnum->Next(1, &pPin, NULL) == S_OK)
    {
        PIN_DIRECTION ThisPinDir;

        pPin->QueryDirection(&ThisPinDir);
        if (ThisPinDir == PinDir)
        {
            IPin *pTmp = 0;

            hr = pPin->ConnectedTo(&pTmp);
            if (SUCCEEDED(hr))  // Already connected, not the pin we want.
            {
                pTmp->Release();
            }
            else  // Unconnected, this is the pin we want.
            {
                pEnum->Release();
                *ppPin = pPin;
                return S_OK;
            }
        }
        pPin->Release();
    }

    // Release the enumerator
    pEnum->Release();

    // Did not find a matching pin
    return E_FAIL;
}


HRESULT RenderFileToVMR9(IGraphBuilder *pGB, WCHAR *wFileName, 
                         IBaseFilter *pRenderer, BOOL bRenderAudio=TRUE)
{
    HRESULT hr=S_OK;
    CComPtr <IPin> pOutputPin;
    CComPtr <IBaseFilter> pSource;
    CComPtr <IBaseFilter> pAudioRenderer;
    CComPtr <IFilterGraph2> pFG;

    // Add a file source filter for this media file
    if (!IsWindowsMediaFile(wFileName))
    {
        // Add the source filter to the graph
        if (FAILED(hr = pGB->AddSourceFilter(wFileName, L"SOURCE", &pSource)))
        {
            USES_CONVERSION;
            TCHAR szMsg[MAX_PATH + 128];

            wsprintf(szMsg, TEXT("Failed to add the source filter to the graph!  hr=0x%x\r\n\r\n")
                     TEXT("Filename: %s\0"), hr, W2T(wFileName));
            MessageBox(NULL, szMsg, TEXT("Failed to render file to VMR9"), MB_OK | MB_ICONERROR);

            return hr;
        }

        // Get the interface for the first unconnected output pin
        JIF(GetUnconnectedPin(pSource, PINDIR_OUTPUT, &pOutputPin));
    }
    else
    {
        MessageBox(NULL, TEXT("Windows Media files (ASF,WMA,WMV) are not supported by this application.\r\n\r\n")
                   TEXT("For a full example of Windows Media support using the\r\n")
                   TEXT("DirectShow WM ASF Reader filter and implementing a key provider\r\n")
                   TEXT("for Windows Media content, refer to the following SDK samples:\r\n\r\n")
                   TEXT("\t- ASFCopy\t- AudioBox\r\n\t- Jukebox  \t- PlayWndASF\r\n\r\n")
                   TEXT("Each of the listed samples provides the necessary extra code\r\n")
                   TEXT("and links with the required Windows Media libraries.\0"),
                   TEXT("Windows Media files are not supported"), MB_OK);
        return E_FAIL;
    }

    // Render audio if requested (defaults to TRUE)
    if (bRenderAudio)
    {
        // Because we will be rendering with the RENDERTOEXISTINGRENDERERS flag,
        // we need to create an audio renderer and add it to the graph.  
        // Create an instance of the DirectSound renderer (for each media file).
        //
        // Note that if the system has no sound card (or if the card is disabled),
        // then creating the DirectShow renderer will fail.  In that case,
        // handle the failure quietly.
        if (SUCCEEDED(CoCreateInstance(CLSID_DSoundRender, NULL, CLSCTX_INPROC_SERVER, 
                                       IID_IBaseFilter, (void **)&pAudioRenderer)))
        {
            // The audio renderer was successfully created, so add it to the graph
            JIF(pGB->AddFilter(pAudioRenderer, L"Audio Renderer"));
        }
    }

    // Get an IFilterGraph2 interface to assist in building the
    // multifile graph with the non-default VMR9 renderer
    JIF(pGB->QueryInterface(IID_IFilterGraph2, (void **)&pFG));

    // Render the output pin, using the VMR9 as the specified renderer.  This is 
    // necessary in case the GraphBuilder needs to insert a Color Space convertor,
    // or if multiple filters insist on using multiple allocators.
    // The audio renderer will also be used, if the media file contains audio.
    JIF(pFG->RenderEx(pOutputPin, AM_RENDEREX_RENDERTOEXISTINGRENDERERS, NULL));

    // If this media file does not contain an audio stream, then the 
    // audio renderer that we created will be unconnected.  If left in the 
    // graph, it could interfere with rate changes and timing.
    // Therefore, if the audio renderer is unconnected, remove it from the graph.
    if (pAudioRenderer != NULL)
    {
        IPin *pUnconnectedPin=0;

        // Is the audio renderer's input pin connected?
        HRESULT hrPin = GetUnconnectedPin(pAudioRenderer, PINDIR_INPUT, &pUnconnectedPin);

        // If there is an unconnected pin, then remove the unused filter
        if (SUCCEEDED(hrPin) && (pUnconnectedPin != NULL))
        {
            // Release the returned IPin interface
            pUnconnectedPin->Release();

            // Remove the audio renderer from the graph
            hrPin = pGB->RemoveFilter(pAudioRenderer);
        }
    }

    return hr;
}


#endif

