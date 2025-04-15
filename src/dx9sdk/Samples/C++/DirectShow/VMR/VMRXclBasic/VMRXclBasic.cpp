//------------------------------------------------------------------------------
// File: VmrXclBasic.cpp
//
// Desc: DirectShow sample code - a simple full screen video playback sample.
//       Using the Windows XP Video Mixing Renderer, a video is played back in
//       full screen exclusive mode.
//      
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

// Precompiled header
#include "stdafx.h"

// DirectX and global headers
#include <evcode.h>

// Project headers
#include "resource.h"
#include "VMRXclBasic.h"
#include "DShowUtils.h"
#include "VmrGlobals.h"

using namespace DShowUtils;
using namespace Helpers;


// Global Variables:
DWORD_PTR   g_userId=0;
TCHAR       g_szTitle[MAX_LOADSTRING]={0};        // The title bar text
TCHAR       g_szWindowClass[MAX_LOADSTRING]={0};  

// Module level variables
// they are included in an anonymous namespace so no one can
// get to them through extern
namespace 
{
    HWND            hwndMain=0;
    IMediaEventEx*  mediaEvent=0;
    const DWORD  WM_GRAPHNOTIFY = WM_APP + 1;   // Private message.
}

// Forward declarations of functions included in this code module:
BOOL                InitInstance(   HINSTANCE hInstance,
                                    HWND& createdWindow,
                                    DWORD& screenWidth, DWORD& screenHeight);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void HandleGraphEvent();



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    MSG msg;
    HACCEL hAccelTable;
    DWORD  screenWidth=0;
    DWORD  screenHeight=0;
    TCHAR  achFoundFile[MAX_PATH];
    IVMRWindowlessControl* pWC = NULL;

    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(hPrevInstance);

    // Initialize COM and don't go on if there are errors
    // DirectX is a COM based API, w/o COM we can't access DirectShow
    HRESULT hres = ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if ( FAILED( hres ) ) 
    {
        OutputDebugString( Helpers::hresultNameLookup(hres));
        OutputDebugString( _T("\n"));
        return FALSE;
    }

    // Verify the presence of VMR
    if( ! VerifyVMR() )
    {
        CoUninitialize();
        return FALSE;   
    }

    if( ! CreateVMRGlobals() )
    {
        ReleaseVMRGlobals();
        CoUninitialize();
        return FALSE;
    }
  
    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, g_szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_VMRXCLBASIC, g_szWindowClass, MAX_LOADSTRING);

    // Register the window class
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.hInstance     = hInstance;
    wc.lpfnWndProc   = WndProc;
    wc.lpszClassName = g_szWindowClass;
    wc.lpszMenuName  = NULL;        // No menu
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VMRXCLBASIC));
    if(!RegisterClass(&wc))
    {
        CoUninitialize();
        return FALSE;
    }

    // Perform application initialization:
    if (!InitInstance (hInstance, hwndMain, screenWidth, screenHeight)) 
    {
        ReleaseVMRGlobals();
        CoUninitialize();
        return FALSE;
    }
    else // by this time the window should be created
    {
        achFoundFile[0] = NULL;     // Set to empty string

        if( ! FindMediaFile(hInstance, hwndMain, achFoundFile) )
        {
            ReleaseVMRGlobals();
            CoUninitialize();
            return FALSE;
        }
        else
        {
           ShowWindow( hwndMain , nCmdShow);
           UpdateWindow( hwndMain ); 
        }

        if(     FAILED( CreateDDObjects(hwndMain, 
                                        screenWidth, 
                                        screenHeight,
                                        BIT_DEPTH ) )

            ||  FAILED ( ConfigureExclusiveMode(g_pVmr, 
                                                g_dd7, 
                                                g_primarySurface,
                                                g_userId,
                                                hwndMain,
                                                &pWC) ) )
        {
            RELEASE(pWC);
            ::DestroyWindow( hwndMain );
            ReleaseVMRGlobals();
            CoUninitialize();
            return FALSE;
        } 
    }

    // Open the media file and configure DirectShow
    if( FAILED( OpenMediaFile(hwndMain, g_pGraphBuilder, achFoundFile ) ))
    {
        RELEASE(pWC);
        ::DestroyWindow( hwndMain );
        ReleaseVMRGlobals();
        CoUninitialize();
        return FALSE;
    }

    SetVideoPosition(pWC, screenWidth, screenHeight);

    // Set up the event notification
    hres = g_pFilterGraph->QueryInterface(IID_IMediaEventEx, (void**)&mediaEvent);
    if( SUCCEEDED( hres ) )
    {
        hres = mediaEvent->SetNotifyWindow((OAHWND)hwndMain, WM_GRAPHNOTIFY, 0);
    }

    if( FAILED( hres ) ) 
    {
        RELEASE(mediaEvent);
        RELEASE(pWC);
        ::DestroyWindow( hwndMain );
        ReleaseVMRGlobals();
        CoUninitialize();
        return FALSE;
    }

    // Begin playing the movie    
    IMediaControl* mediaControl;
    hres = g_pFilterGraph->QueryInterface(IID_IMediaControl, (LPVOID *)&mediaControl);
    if( SUCCEEDED( hres ) )
    {
        mediaControl->Run();
        mediaControl->Release();
    }

    hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_VMRXCLBASIC);

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Cleanup and free resources
    RELEASE(mediaEvent);
    RELEASE(pWC);

    ::DestroyWindow( hwndMain );
    ReleaseVMRGlobals();
    CoUninitialize();

    return ((int) msg.wParam);
}


//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

BOOL
InitInstance(   HINSTANCE hInstance,
                HWND& hwndCreated,
                DWORD& screenWidth, DWORD& screenHeight)
{
   // create a window that occupies the whole screen
   HDC hdcScreen = GetDC(NULL);

   if( hdcScreen ) 
   {
       screenWidth  = GetDeviceCaps(hdcScreen,HORZRES);
       screenHeight = GetDeviceCaps(hdcScreen,VERTRES);
       ReleaseDC(NULL, hdcScreen);

       hwndCreated = CreateWindow(g_szWindowClass, g_szTitle, WS_POPUP,
                                  0, 0, 
                                  screenWidth, screenHeight, 
                                  NULL, NULL, hInstance, NULL);
       if ( hwndCreated )
           return TRUE;
   }

   return FALSE;
}


//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;

    switch (message) 
    {
        case WM_COMMAND:
            wmId    = LOWORD(wParam); 
            wmEvent = HIWORD(wParam); 

            // Parse the menu selections:
            switch (wmId)
            {
                case IDM_EXIT:
                   DestroyWindow(hWnd);
                   break;

                default:
                   return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;

        case WM_DESTROY:
            if( mediaEvent )
            {
                mediaEvent->SetNotifyWindow(NULL,WM_GRAPHNOTIFY,NULL);      
            }
            PostQuitMessage(0);
            break;

        case WM_GRAPHNOTIFY:
            HandleGraphEvent();
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
   }

   return 0;
}


void HandleGraphEvent()
{
    if( mediaEvent ) 
    {
        HRESULT hr; 
        LONG  evCode, lParam1, lParam2;

        while (hr = mediaEvent->GetEvent(&evCode, (LONG_PTR *) &lParam1, 
                                        (LONG_PTR *) &lParam2, 0), SUCCEEDED(hr)) 
        {
            if(EC_COMPLETE == evCode)
            {
                ::DestroyWindow(hwndMain);
            }

            // Free any memory associated with this event
            hr = mediaEvent->FreeEventParams(evCode, lParam1, lParam2);
        }
    }
}


