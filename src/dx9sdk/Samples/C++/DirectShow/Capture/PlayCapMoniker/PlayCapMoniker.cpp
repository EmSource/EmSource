//------------------------------------------------------------------------------
// File: PlayCapMoniker.cpp
//
// Desc: DirectShow sample code - a very basic application using video capture
//       devices.  It creates a window and uses the first available capture
//       device to render and preview video capture data.
//
//       Instead of building the capture graph manually using the
//       ICaptureGraphBuilder2 interface, this sample simply finds the moniker 
//       of the first available capture device, reads its display name, adds
//       the associated filter to the graph, and renders its output pins.
//
// NOTE: For DirectX 8.0 and 8.1, you could call RenderFile() on the 
//       source filter's moniker display name to create the graph.
//       This functionality was *removed* for DirectX 9.0, so this sample
//       demonstrates a different method for achieving the same result.
//       Instead of IGraphBuilder::RenderFile(), you use 
//       IFilterGraph2::AddSourceFilterForMoniker() to build the graph.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include <atlbase.h>
#include <windows.h>
#include <dshow.h>
#include <stdio.h>

#include "PlayCapMoniker.h"

// An application can advertise the existence of its filter graph
// by registering the graph with a global Running Object Table (ROT).
// The GraphEdit application can detect and remotely view the running
// filter graph, allowing you to 'spy' on the graph with GraphEdit.
//
// To enable registration in this sample, define REGISTER_FILTERGRAPH.
//
#define REGISTER_FILTERGRAPH


//
// Global data
//
HWND ghApp=0;
DWORD g_dwGraphRegister=0;

IVideoWindow  * g_pVW = NULL;
IMediaControl * g_pMC = NULL;
IMediaEventEx * g_pME = NULL;
IFilterGraph2 * g_pGraph = NULL;  // IFilterGraph2 provides AddSourceFileForMoniker()
ICaptureGraphBuilder2 * g_pCapture = NULL;


HRESULT CaptureVideoByMoniker()
{
    HRESULT hr;
    IMoniker *pMoniker =NULL;

    // Get DirectShow interfaces
    hr = GetInterfaces();
    if (FAILED(hr))
    {
        Msg(TEXT("Failed to get video interfaces!  hr=0x%x"), hr);
        return hr;
    }

    // Use the system device enumerator and class enumerator to find
    // a moniker that represents a video capture/preview device, 
    // such as a desktop USB video camera.
    hr = FindCaptureDeviceMoniker(&pMoniker);
    if (FAILED(hr))
    {
        // FindCaptureDeviceMoniker will display an error message
        return hr;
    }

    //
    // NOTE: For DirectX 8.0 and 8.1, you could call RenderFile() on the 
    //       source filter's moniker display name to create the graph.
    //       This functionality was *removed* for DirectX 9.0, so this sample
    //       demonstrates a different method for achieving the same result.
    //       Instead of IGraphBuilder::RenderFile(), you use 
    //       IFilterGraph2::AddSourceFilterForMoniker().
    //
    hr = AddCaptureMonikerToGraph(pMoniker);
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't add the capture filter to the graph!  hr=0x%x\r\n\r\n") 
            TEXT("If you have a working video capture device, please make sure\r\n")
            TEXT("that it is connected and is not being used by another application.\r\n\r\n")
            TEXT("The sample will now close."), hr);
        return hr;
    }

    // Release the IMoniker interface for the capture source filter
    pMoniker->Release();

    // Set video window style and position
    hr = SetupVideoWindow();
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't initialize video window!  hr=0x%x"), hr);
        return hr;
    }

#ifdef REGISTER_FILTERGRAPH
    // Add our graph to the running object table, which will allow
    // the GraphEdit application to "spy" on our graph
    hr = AddGraphToRot(g_pGraph, &g_dwGraphRegister);
    if (FAILED(hr))
    {
        Msg(TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
        g_dwGraphRegister = 0;
    }
#endif

    // Start previewing video data
    hr = g_pMC->Run();
    if (FAILED(hr))
    {
        Msg(TEXT("Couldn't run the graph!  hr=0x%x"), hr);
        return hr;
    }

    return S_OK;
}


HRESULT AddCaptureMonikerToGraph(IMoniker *pMoniker)
{
    USES_CONVERSION;

    HRESULT hr;
    IBaseFilter *pBaseFilter=0;

    // Get the display name of the moniker
    LPOLESTR strMonikerName=0;
    hr = pMoniker->GetDisplayName(NULL, NULL, &strMonikerName);
    if (FAILED(hr))
    {
        // Msg(TEXT("Couldn't get moniker's display name!  hr=0x%x"), hr);
        return hr;
    }

#ifdef DEBUG
    // Get a human-readable string for evaluation during debugging
    TCHAR szMonikerName[256];
    _tcsncpy(szMonikerName, W2T(strMonikerName), 255);
    szMonikerName[255] = 0;     // Null-terminate
    //  Msg(TEXT("Moniker: %s\r\n"), szMonikerName);
#endif

    // Create a bind context needed for working with the moniker
    IBindCtx *pContext=0;
    hr = CreateBindCtx(0, &pContext);
    if (FAILED(hr))
    {
        // Msg(TEXT("Couldn't create a bind context for moniker!  hr=0x%x"), hr);
        return hr;
    }
  
    hr = g_pGraph->AddSourceFilterForMoniker(pMoniker, pContext, 
                                             strMonikerName, &pBaseFilter);
    if (FAILED(hr))
    {
        // Msg(TEXT("Failed in AddSourceFilterForMoniker()!  hr=0x%x"), hr);
        return hr;
    }

    // Attach the filter graph to the capture graph
    hr = g_pCapture->SetFiltergraph(g_pGraph);
    if (FAILED(hr))
    {
        // Msg(TEXT("Failed to set capture filter graph!  hr=0x%x"), hr);
        return hr;
    }

    // Render the preview pin on the video capture filter
    // Use this instead of g_pGraph->RenderFile
    hr = g_pCapture->RenderStream (&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
                                   pBaseFilter, NULL, NULL);
//  if (FAILED(hr))
//  {
//      Msg(TEXT("Couldn't render capture stream.  ")
//          TEXT("The device may already be in use.\r\n\r\nhr=0x%x"), hr);
//  }

    SAFE_RELEASE(pContext);
    SAFE_RELEASE(pBaseFilter);

    return hr;
}


HRESULT FindCaptureDeviceMoniker(IMoniker **ppMoniker)
{
    HRESULT hr;
    ULONG cFetched;

    if (!ppMoniker)
        return E_POINTER;
   
    // Create the system device enumerator
    CComPtr <ICreateDevEnum> pDevEnum = NULL;

    hr = CoCreateInstance (CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           IID_ICreateDevEnum, (void ** ) &pDevEnum);
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
        MessageBox(ghApp,TEXT("No video capture device was detected.\r\n\r\n")
                   TEXT("This sample requires a video capture device, such as a USB WebCam,\r\n")
                   TEXT("to be installed and working properly.  The sample will now close."),
                   TEXT("No Video Capture Hardware"), MB_OK | MB_ICONINFORMATION);
        return E_FAIL;
    }

    // Use the first video capture device on the device list.
    // Note that if the Next() call succeeds but there are no monikers,
    // it will return S_FALSE (which is not a failure).  Therefore, we
    // check that the return code is S_OK instead of using SUCCEEDED() macro.
    if (S_OK == (pClassEnum->Next (1, ppMoniker, &cFetched)))
    {
        return S_OK;
    }
    else
    {
        Msg(TEXT("Unable to access a video capture device!"));   
        return E_FAIL;
    }
}


HRESULT GetInterfaces(void)
{
    HRESULT hr;

    // Create the filter graph
    hr = CoCreateInstance (CLSID_FilterGraph, NULL, CLSCTX_INPROC,
                           IID_IFilterGraph2, (void **) &g_pGraph);
    if (FAILED(hr))
        return hr;

    // Create the capture graph builder
    hr = CoCreateInstance (CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC,
                           IID_ICaptureGraphBuilder2, (void **) &g_pCapture);
    if (FAILED(hr))
        return hr;
    
    // Obtain interfaces for media control and Video Window
    hr = g_pGraph->QueryInterface(IID_IMediaControl,(LPVOID *) &g_pMC);
    if (FAILED(hr))
        return hr;

    hr = g_pGraph->QueryInterface(IID_IVideoWindow, (LPVOID *) &g_pVW);
    if (FAILED(hr))
        return hr;

    hr = g_pGraph->QueryInterface(IID_IMediaEvent, (LPVOID *) &g_pME);
    if (FAILED(hr))
        return hr;

    // Set the window handle used to process graph events
    hr = g_pME->SetNotifyWindow((OAHWND)ghApp, WM_GRAPHNOTIFY, 0);

    return hr;
}


void CloseInterfaces(void)
{
    // Stop previewing data
    if (g_pMC)
        g_pMC->StopWhenReady();

    // Stop receiving events
    if (g_pME)
        g_pME->SetNotifyWindow(NULL, WM_GRAPHNOTIFY, 0);

    // Relinquish ownership (IMPORTANT!) of the video window.
    // Failing to call put_Owner can lead to assert failures within
    // the video renderer, as it still assumes that it has a valid
    // parent window.
    if(g_pVW)
    {
        g_pVW->put_Visible(OAFALSE);
        g_pVW->put_Owner(NULL);
    }

#ifdef REGISTER_FILTERGRAPH
    // Remove filter graph from the running object table   
    if (g_dwGraphRegister)
        RemoveGraphFromRot(g_dwGraphRegister);
#endif

    // Release DirectShow interfaces
    SAFE_RELEASE(g_pMC);
    SAFE_RELEASE(g_pME);
    SAFE_RELEASE(g_pVW);
    SAFE_RELEASE(g_pCapture);
    SAFE_RELEASE(g_pGraph);
}


HRESULT SetupVideoWindow(void)
{
    HRESULT hr;

    // Set the video window to be a child of the main window
    hr = g_pVW->put_Owner((OAHWND)ghApp);
    if (FAILED(hr))
        return hr;
    
    // Set video window style
    hr = g_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
    if (FAILED(hr))
        return hr;

    // Use helper function to position video window in client rect 
    // of main application window
    ResizeVideoWindow();

    // Make the video window visible, now that it is properly positioned
    hr = g_pVW->put_Visible(OATRUE);
    if (FAILED(hr))
        return hr;

    return hr;
}


void ResizeVideoWindow(void)
{
    // Resize the video preview window to match owner window size
    if (g_pVW)
    {
        RECT rc;
        
        // Make the preview video fill our window
        GetClientRect(ghApp, &rc);
        g_pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);
    }
}


#ifdef REGISTER_FILTERGRAPH

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
    IMoniker * pMoniker;
    IRunningObjectTable *pROT;
    WCHAR wsz[128];
    HRESULT hr;

    if (!pUnkGraph || !pdwRegister)
        return E_POINTER;

    if (FAILED(GetRunningObjectTable(0, &pROT)))
        return E_FAIL;

    wsprintfW(wsz, L"FilterGraph %08x pid %08x\0", (DWORD_PTR)pUnkGraph, 
              GetCurrentProcessId());

    hr = CreateItemMoniker(L"!", wsz, &pMoniker);
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
                            pMoniker, pdwRegister);
        pMoniker->Release();
    }

    pROT->Release();
    return hr;
}


// Removes a filter graph from the Running Object Table
void RemoveGraphFromRot(DWORD pdwRegister)
{
    IRunningObjectTable *pROT;

    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) 
    {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
}

#endif


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

    MessageBox(NULL, szBuffer, TEXT("PlayCapMoniker"), MB_OK | MB_ICONERROR);
}


HRESULT HandleGraphEvent(void)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

    if (!g_pME)
        return E_POINTER;

    // Process all queued events
    while(SUCCEEDED(g_pME->GetEvent(&evCode, (LONG_PTR *) &evParam1, 
                   (LONG_PTR *) &evParam2, 0)))
    {
        // Insert event processing code here, if desired
        switch (evCode)
        {
            // When the user closes the capture window, close the app.
            case EC_DEVICE_LOST:
            case EC_ERRORABORT:
            case EC_USERABORT:
                Msg(TEXT("Received an error event: 0x%x.  Closing app.\0"), evCode);
                PostMessage(ghApp, WM_CLOSE, 0, 0);
                break;
        }

        //
        // Free event parameters to prevent memory leaks associated with
        // event parameter data.  While this application is not interested
        // in the received events, applications should always process them.
        //
        hr = g_pME->FreeEventParams(evCode, evParam1, evParam2);        
    }

    return hr;
}


LRESULT CALLBACK WndMainProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_GRAPHNOTIFY:    // Process events from the filter graph
            HandleGraphEvent();
            break;

        case WM_SIZE:
            ResizeVideoWindow();
            break;

        case WM_CLOSE:            
            // Hide the main window while the graph is destroyed
            ShowWindow(ghApp, SW_HIDE);
            CloseInterfaces();  // Stop capturing and release interfaces
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    // Pass this message to the video window for notification of system changes
    if (g_pVW)
        g_pVW->NotifyOwnerMessage((LONG_PTR) hwnd, message, wParam, lParam);

    return DefWindowProc (hwnd, message, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstP, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg={0};
    WNDCLASS wc;

    // Initialize COM
    if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        Msg(TEXT("CoInitialize Failed!\r\n"));   
        exit(1);
    } 

    // Register the window class
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc   = WndMainProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASSNAME;
    wc.lpszMenuName  = NULL;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VIDPREVIEW));
    if(!RegisterClass(&wc))
    {
        Msg(TEXT("RegisterClass Failed! Error=0x%x\r\n"), GetLastError());
        CoUninitialize();
        exit(1);
    }

    // Create the main window.  The WS_CLIPCHILDREN style is required.
    ghApp = CreateWindow(CLASSNAME, APPLICATIONNAME,
                         WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_CLIPCHILDREN,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT,
                         0, 0, hInstance, 0);
    if(ghApp)
    {
        HRESULT hr;

        // Create DirectShow graph and start capturing video
        hr = CaptureVideoByMoniker();
        if (FAILED (hr))
        {
            CloseInterfaces();
            DestroyWindow(ghApp);
        }
        else
        {
            // Don't display the main window until the DirectShow
            // preview graph has been created.  Once video data is
            // being received and processed, the window will appear
            // and immediately have useful video data to dispay.
            // Otherwise, it will be black until video data arrives.
            ShowWindow(ghApp, nCmdShow);
        }       

        // Main message loop
        while(GetMessage(&msg,NULL,0,0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Release COM
    CoUninitialize();

    return ((int) msg.wParam);
}



