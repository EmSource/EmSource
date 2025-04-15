//------------------------------------------------------------------------------
// File: BmpMix9.cpp
//
// Desc: DirectShow sample code - a bitmap-mixing VMR9 media file player
//       using Direct3D9 surfaces
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "bmpmix9.h"
#include "vmrutil.h"

// Constants
#define MAX_LOADSTRING 100
#define TIMER_INTERVAL 500      // Refresh bitmap every 500ms
#define ALPHA_VALUE    0.6f     // Alpha value for bitmap (0.0 to 1.0)
#define BMP_SIZE_X     0.3f     // Width of bitmap in comp. space
#define BMP_SIZE_Y     0.3f     // Height of bitmap in comp. space
#define MOVE_TOLERANCE 0.05f    // Min. distance for mouse move before refresh
#define BMP_INIT_X     0.6f
#define BMP_INIT_Y     0.6f

// Global Variables
HINSTANCE hInst;                         // current instance
TCHAR szTitle[MAX_LOADSTRING];           // title bar text
TCHAR szWindowClass[MAX_LOADSTRING];
UINT_PTR g_nTimerID = 0xFCDCACCC;
int g_nCurrentImage=0;
float g_fCurrentX=BMP_INIT_X, g_fCurrentY=BMP_INIT_Y;
BOOL g_bRunning=FALSE;

// Foward declarations of functions included in this code module
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int, HWND& );
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HWND hwnd);
void OnFileClose( HWND hWnd );
void HandleMouseClick(LPARAM lParam);

// DirectShow and D3D routines
HRESULT             StartGraph(HWND window);
HRESULT             D3DStart( HWND hWnd );
BOOL                GetImageDimensions(long& lHeight, long& lWidth);
HRESULT             SetInitialAlphaBitmap();
HRESULT             UpdateAlphaBitmap(int nIndex);
HRESULT             SetUpAlphaBitmap( VMR9AlphaBitmap& alphaBitmap, int nIndex );
void                ClearD3D(void);
void                ClearDirectShow(void);

// DirectShow objects
HWND                            g_hWnd;
CComPtr<IGraphBuilder>          g_pGB;
CComPtr<IBaseFilter>            g_pVMR;
CComPtr<IVMRFilterConfig9>      g_pFilterConfig;
CComPtr<IVMRWindowlessControl9> g_pWC;
CComPtr<IMediaControl>          g_pMC;
CComPtr<IVMRMixerBitmap9>       g_pMixerBitmap;

// D3D objects
CComPtr<IDirect3D9>             g_pD3D;
CComPtr<IDirect3DDevice9>       g_pD3DDevice;

const int   NUMBITMAPS          = 3;
CComPtr<IDirect3DSurface9>      g_pSurfaces[NUMBITMAPS];



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    int nReturn = -1;

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    // Verify that the VMR9 is present on this system
    if(!VerifyVMR9())
    {
        CoUninitialize();
        return FALSE;
    }

    __try 
    {
        MSG msg;
        HACCEL hAccelTable;

        // Initialize global strings
        LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadString(hInstance, IDC_BMPMIX9, szWindowClass, MAX_LOADSTRING);
        if (!MyRegisterClass(hInstance)) 
        {
            MessageBox(NULL, TEXT("Failed to register main window class!"), 
                       TEXT("BmpMix9"), MB_ICONERROR | MB_OK);
            __leave;
        }

        // Perform application initialization
        if (!InitInstance (hInstance, nCmdShow, g_hWnd)) 
        {
            MessageBox(NULL, TEXT("Failed to initialize main window!"), 
                       TEXT("BmpMix9"), MB_ICONERROR | MB_OK);
            __leave;
        }

        hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_BMPMIX9);

        // Main message loop
        while (GetMessage(&msg, NULL, 0, 0)) 
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        nReturn = (int) msg.wParam;
    }
    __finally
    {
        // Delete resources
        // Release the CComPtr interfaces before uninitializing COM
        ClearD3D();
        ClearDirectShow();
        CoUninitialize();
    }
    
    return nReturn;
}

_bstr_t GetMoviePath()
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    TCHAR szBuffer[MAX_PATH];
    szBuffer[0] = NULL;

    // Initialize the open file dialog structure
    static const TCHAR szFilter[]  
                            = TEXT("Video Files (.ASF, .AVI, .MPG, .MPEG, .VOB, .QT, .WMV)\0*.ASF;*.AVI;*.MPG;*.MPEG;*.VOB;*.QT;*.WMV\0") \
                              TEXT("All Files (*.*)\0*.*\0\0");
    ofn.lStructSize         = sizeof(OPENFILENAME);
    ofn.hwndOwner           = g_hWnd;
    ofn.hInstance           = NULL;
    ofn.lpstrFilter         = szFilter;
    ofn.nFilterIndex        = 1;
    ofn.lpstrCustomFilter   = NULL;
    ofn.nMaxCustFilter      = 0;
    ofn.lpstrFile           = szBuffer;
    ofn.nMaxFile            = MAX_PATH;
    ofn.lpstrFileTitle      = NULL;
    ofn.nMaxFileTitle       = 0;
    ofn.lpstrInitialDir     = NULL;
    ofn.lpstrTitle          = TEXT("Select a video file to play...");
    ofn.Flags               = OFN_HIDEREADONLY;
    ofn.nFileOffset         = 0;
    ofn.nFileExtension      = 0;
    ofn.lpstrDefExt         = TEXT("AVI");
    ofn.lCustData           = 0L;
    ofn.lpfnHook            = NULL;
    ofn.lpTemplateName  = NULL; 
    
    if (GetOpenFileName (&ofn))  // user specified a file
        return _bstr_t( szBuffer );
    else    
        return "";
}

void ClearD3D(void)
{
    // Initialize global data
    for( int i = 0; i < NUMBITMAPS; ++i )
        g_pSurfaces[i] = NULL;

    // Zero CComPtrs to release interfaces and free memory
    g_pD3DDevice = NULL;
    g_pD3D = NULL;
}

void ClearDirectShow(void)
{
    // Zero CComPtrs to release interfaces and free memory
    g_pMixerBitmap  = NULL;
    g_pFilterConfig = NULL;

    g_pMC  = NULL;
    g_pWC  = NULL;
    g_pVMR = NULL;
    g_pGB  = NULL;

    g_fCurrentX = BMP_INIT_X;
    g_fCurrentY = BMP_INIT_Y;
}

HRESULT StartGraph(HWND hwnd)
{
    HRESULT hr;

    // Prompt the user for a media file name
    _bstr_t path = GetMoviePath();
    if( ! path.length() )
    {
        return E_FAIL;
    }

    // Stop any currently running timer
    KillTimer(g_hWnd, g_nTimerID);
    UpdateWindow(g_hWnd);

    // Initialize global data
    ClearDirectShow();

    // Create a filter graph   
    FAIL_RET( g_pGB.CoCreateInstance(CLSID_FilterGraph) )

    // Create a VMR9 rendering filter and add it to the empty graph
    FAIL_RET( g_pVMR.CoCreateInstance(CLSID_VideoMixingRenderer9, 
                                      NULL, CLSCTX_INPROC_SERVER) )

    FAIL_RET( g_pGB->AddFilter(g_pVMR, L"Video Mixing Renderer 9") )
    
    // Get the filter configuration interface and set VMR to Windowless rendering
    FAIL_RET( g_pVMR->QueryInterface(IID_IVMRFilterConfig9, 
              reinterpret_cast<void**>(&g_pFilterConfig)) )

    FAIL_RET( g_pFilterConfig->SetRenderingMode( VMR9Mode_Windowless ) )
    
    // Bound the video clipping region to our application window
    FAIL_RET( g_pVMR->QueryInterface(IID_IVMRWindowlessControl9, 
              reinterpret_cast<void**>(&g_pWC)) )

    FAIL_RET( g_pWC->SetVideoClippingWindow( g_hWnd ) )

    // Position the video within our application window
    RECT clientRect;
    if( ::GetClientRect(g_hWnd, &clientRect ) )
    {
        FAIL_RET( g_pWC->SetVideoPosition( NULL, &clientRect ) )
    }

    // Get the remaining necessary COM interfaces
    FAIL_RET( g_pGB->QueryInterface(IID_IMediaControl, 
              reinterpret_cast<void**>(&g_pMC)) )

    FAIL_RET( g_pVMR->QueryInterface(IID_IVMRMixerBitmap9, 
              reinterpret_cast<void**>(&g_pMixerBitmap)) )

    // Initialize Direct3D 9
    FAIL_RET( D3DStart( hwnd ) )

    // Render and run the user-selected media file.
    FAIL_RET( RenderFileToVMR9(g_pGB, path, g_pVMR));

    // Associate an alpha-blended bitmap with the VMR
    FAIL_RET( SetInitialAlphaBitmap( ) );

    FAIL_RET( g_pMC->Run() )

    // Start the timer for updating the alpha-blended bitmap
    SetTimer( g_hWnd, g_nTimerID, TIMER_INTERVAL, NULL ); 

    g_bRunning = TRUE;
    return hr;
}

HRESULT D3DStart(HWND hWnd)
{
    HRESULT hr;

    ClearD3D();

    // Initialize D3D
    g_pD3D.Release();  // just in case this is called twice
    g_pD3D.Attach(Direct3DCreate9( D3D_SDK_VERSION ) );
    if( g_pD3D == NULL )
        return E_FAIL;

    D3DDISPLAYMODE d3ddm;
    FAIL_RET( g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) );

    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed         = TRUE;
    d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.hDeviceWindow    = g_hWnd;

    FAIL_RET( g_pD3D->CreateDevice( 
        D3DADAPTER_DEFAULT, // always the primary display adapter
        D3DDEVTYPE_HAL,
        NULL,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &g_pD3DDevice) )

    // Read the dimensions of our alpha-blended bitmap
    long lWidth, lHeight;
    if( ! GetImageDimensions( lHeight, lWidth ) )
        return E_FAIL;

    // Create an offscreen D3D surface for each bitmap (in the set of 3)
    for( int i = 0; i < NUMBITMAPS; ++i )
    {
        FAIL_RET( g_pD3DDevice->CreateOffscreenPlainSurface( 
            lWidth, lHeight,
            D3DFMT_X8R8G8B8,
            D3DPOOL_SYSTEMMEM,
            &g_pSurfaces[i], NULL ) );
    }

    // Load the bitmaps into memory
    FAIL_RET( D3DXLoadSurfaceFromResource (
            g_pSurfaces[0],
            NULL,       // palette
            NULL,       // entire surface - created to be the proper height
            GetModuleHandle(NULL), // current module
            MAKEINTRESOURCE(IDB_BITMAP1),
            NULL,       // entire image
            D3DX_DEFAULT, 
            0,          // disable color key
            NULL        // source info
            ));

    FAIL_RET( D3DXLoadSurfaceFromResource (
            g_pSurfaces[1],
            NULL,
            NULL,
            GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDB_BITMAP2),
            NULL, // entire image
            D3DX_DEFAULT, 
            0,
            NULL
            ));

    FAIL_RET( D3DXLoadSurfaceFromResource (
            g_pSurfaces[2],
            NULL,
            NULL,
            GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDB_BITMAP3),
            NULL, // entire image
            D3DX_DEFAULT, 
            0,
            NULL
            ));

    return hr;
}

BOOL GetImageDimensions(long& lHeight, long& lWidth)
{
    BOOL ret = false;

    HANDLE hBitmap = LoadImage(::GetModuleHandle(NULL),
                              MAKEINTRESOURCE(IDB_BITMAP1),
                              IMAGE_BITMAP,
                              0,0, // size
                              LR_DEFAULTCOLOR | LR_DEFAULTSIZE );
    if( hBitmap )
    {
        BITMAP bmpInfo;
        if( ::GetObject( hBitmap, sizeof(bmpInfo), &bmpInfo ) )
        {
            lHeight = bmpInfo.bmHeight;
            lWidth  = bmpInfo.bmWidth;
            ret = true;
        }    
    }

    DeleteObject( hBitmap );
    return ret;
}

HRESULT SetInitialAlphaBitmap()
{
    HRESULT hr = E_FAIL;
    VMR9AlphaBitmap alphaBitmap;

    // Initialize the alpha bitmap
    FAIL_RET( SetUpAlphaBitmap( alphaBitmap, 0 ) );
    
    // Apply the bitmap to the VMR
    FAIL_RET( g_pMixerBitmap->SetAlphaBitmap( &alphaBitmap ) );

    return hr;
}

HRESULT UpdateAlphaBitmap(int nIndex)
{
    HRESULT hr = E_FAIL;
    VMR9AlphaBitmap alphaBitmap;

    // Update the bitmap by index
    FAIL_RET( SetUpAlphaBitmap( alphaBitmap, nIndex ) );

    // Apply the bitmap to the VMR
    FAIL_RET( g_pMixerBitmap->SetAlphaBitmap( &alphaBitmap ) );

    return hr;
}

HRESULT SetUpAlphaBitmap( VMR9AlphaBitmap& alphaBitmap, int nIndex )
{
    if( g_pMixerBitmap == NULL || g_pSurfaces[nIndex] == NULL )
    {
        return E_FAIL;
    }

    ZeroMemory( &alphaBitmap, sizeof VMR9AlphaBitmap);

    // Initialize VMR9AlphaBitmap structure
    alphaBitmap.dwFlags   = VMR9AlphaBitmap_EntireDDS | VMR9AlphaBitmap_SrcColorKey;
    alphaBitmap.hdc       = NULL;
    alphaBitmap.pDDS      = g_pSurfaces[nIndex];
    alphaBitmap.clrSrcKey = RGB(255,255,255);  // white background

    // Position the bitmap within the VMR's composition space (0.0 - 1.0).
    // Because the bitmap can move on mouse clicks, keep track of the
    // current X and Y positions.  The width/height of the alpha-bitmap are
    // predetermined by constant sizes.
    alphaBitmap.rDest.top    = g_fCurrentY - BMP_SIZE_Y / 2;
    alphaBitmap.rDest.left   = g_fCurrentX - BMP_SIZE_X / 2;
    alphaBitmap.rDest.bottom = g_fCurrentY + BMP_SIZE_Y / 2;
    alphaBitmap.rDest.right  = g_fCurrentX + BMP_SIZE_X / 2;
    alphaBitmap.fAlpha       = ALPHA_VALUE;

    return S_OK;
}

HRESULT MoveAlphaBitmap(float fX, float fY)
{
    HRESULT hr=S_OK;
    VMR9AlphaBitmap alphaBitmap;

    if( g_pMixerBitmap == NULL || g_pSurfaces[g_nCurrentImage] == NULL )
    {
        return E_FAIL;
    }

    ZeroMemory( &alphaBitmap, sizeof VMR9AlphaBitmap);

    // Initialize VMR9AlphaBitmap structure
    alphaBitmap.dwFlags   = VMR9AlphaBitmap_EntireDDS | VMR9AlphaBitmap_SrcColorKey;
    alphaBitmap.hdc       = NULL;
    alphaBitmap.pDDS      = g_pSurfaces[g_nCurrentImage];
    alphaBitmap.clrSrcKey = RGB(255,255,255);

    // Position the bitmap within the VMR's composition space (0.0 - 1.0)
    // centered around the mouse point
    alphaBitmap.rDest.top    = fY - BMP_SIZE_Y / 2;
    alphaBitmap.rDest.left   = fX - BMP_SIZE_X / 2;
    alphaBitmap.rDest.bottom = fY + BMP_SIZE_Y / 2;
    alphaBitmap.rDest.right  = fX + BMP_SIZE_X / 2;
    alphaBitmap.fAlpha       = ALPHA_VALUE;

    // Apply the bitmap to the VMR
    FAIL_RET( g_pMixerBitmap->SetAlphaBitmap( &alphaBitmap ) );

    // We successfully set the value, so remember the current coordinates
    g_fCurrentX = fX;
    g_fCurrentY = fY;

    return S_OK;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex));

    // Set the members of the window class structure.
    // Don't provide a background brush, because we process the WM_PAINT
    // messages in OnPaint().  If a movie is active, we tell the VMR to
    // repaint the window; otherwise, we repaint with COLOR_WINDOW+1.
    // If a background brush is provided, you will see a white flicker
    // whenever you resize the main application window, because Windows
    // will repaint the window before the application also repaints.
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc    = (WNDPROC)WndProc;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, (LPCTSTR)IDI_BMPMIX9);
    wcex.hIconSm        = LoadIcon(hInstance, (LPCTSTR)IDI_BMPMIX9);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.lpszMenuName   = (LPCTSTR)IDC_BMPMIX9;
    wcex.lpszClassName  = szWindowClass;
    
    return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& hWnd)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, 
                       NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// Message handler for about box
LRESULT CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
                return TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
            {
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;
    }
    return FALSE;
}


//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HRESULT hr;

    switch (message) 
    {
        case WM_COMMAND:
        {
            int nId, nEvent;
            nId    = LOWORD(wParam); 
            nEvent = HIWORD(wParam); 

            // Parse the menu selections:
            switch (nId)
            {
                case IDM_PLAY_FILE:
                    hr = StartGraph(g_hWnd);
                    if( FAILED(hr) )
                    {
                        MessageBox(NULL, TEXT("Failed to create the VMR9 graph!"), 
                                   TEXT("BitmapMix9 failure!"), MB_OK);
                    }
                    g_nCurrentImage = 0;
                    break;

                case IDM_FILE_CLOSE:
                    OnFileClose( hWnd );
                    break;

                case IDM_ABOUT:
                   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)AboutDlgProc);
                   break;

                case IDM_EXIT:
                   DestroyWindow(hWnd);
                   break;
            }
            break;
        }

        case WM_PAINT:
            OnPaint(hWnd);
            break;

        case WM_MOUSEMOVE:
            // If the left mouse button is down, treat this as a drag operation
            if (wParam & MK_LBUTTON)
                HandleMouseClick(lParam);
            break;

        case WM_LBUTTONDOWN:
            HandleMouseClick(lParam);
            break;

        case WM_DISPLAYCHANGE:
            if( g_pWC )
                g_pWC->DisplayModeChanged();
            break;

        case WM_SIZE:
            if( g_pWC )
            {
                RECT clientRect;
                if( ::GetClientRect( g_hWnd, &clientRect ) )
                {
                    g_pWC->SetVideoPosition(NULL, &clientRect );            
                }
            }
            break;

        case WM_TIMER:
            if( (UINT_PTR) wParam == g_nTimerID )
            {
                // Rotate through our list of bitmaps
                g_nCurrentImage++;
                g_nCurrentImage %= NUMBITMAPS;

                hr = UpdateAlphaBitmap(g_nCurrentImage);
                if( FAILED( hr ) )
                    return 0;
            }
            break;

        case WM_DESTROY:
            KillTimer(g_hWnd, g_nTimerID);
            PostQuitMessage(0);
            break;
   }

   return DefWindowProc(hWnd, message, wParam, lParam);
}

void OnFileClose( HWND hWnd )
{
    if( g_pMC != NULL ) 
    {
        OAFilterState state;
        do {
            g_pMC->Stop();
            g_pMC->GetState(0, & state );
        } while( state != State_Stopped ) ;
    }

    ClearD3D();
    ClearDirectShow();
    ::InvalidateRect( hWnd, NULL, TRUE );
}

void OnPaint(HWND hwnd) 
{
    HRESULT hr;
    PAINTSTRUCT ps; 
    HDC         hdc; 
    RECT        rcClient; 

    GetClientRect(hwnd, &rcClient); 
    hdc = BeginPaint(hwnd, &ps); 

    if(g_pWC) 
    { 
        // When using VMR Windowless mode, you must explicitly tell the
        // renderer when to repaint the video in response to WM_PAINT
        // messages.  This is most important when the video is stopped
        // or paused, since the VMR won't be automatically updating the
        // window as the video plays.
        if (g_pWC)
            hr = g_pWC->RepaintVideo(hwnd, hdc);  
    } 
    else  // No video image. Just paint the whole client area. 
    { 
        FillRect(hdc, &rcClient, (HBRUSH)(COLOR_WINDOW + 1)); 
    } 

    EndPaint(hwnd, &ps); 
} 


void HandleMouseClick(LPARAM lParam)
{
    // Make sure that we're already playing the movie
    if (!g_bRunning)
        return;

    // Get the window coordinates of the mouse pointer
    int xPos = GET_X_LPARAM(lParam);
    int yPos = GET_Y_LPARAM(lParam);

    // Get the window client area rectangle
    RECT rcClient; 
    GetClientRect(g_hWnd, &rcClient); 

    // Convert the click position into composition space coordinates,
    // which range from 0.0 to 1.0
    float fX, fY;
    fX = (float) ((float)xPos / (float)rcClient.right );
    fY = (float) ((float)yPos / (float)rcClient.bottom );

    // Bound coordinates to allowed space
    if (fX > 1.0) fX = 1.0;    if (fX < 0.0) fX = 0.0;
    if (fY > 1.0) fY = 1.0;    if (fY < 0.0) fY = 0.0;

    // Because mouse movement messages can be very frequent,
    // only update the bitmap if it has moved a sufficient distance.
    if ((fabs(fX - g_fCurrentX) >= MOVE_TOLERANCE) ||
        (fabs(fY - g_fCurrentY) >= MOVE_TOLERANCE))
    {
        MoveAlphaBitmap(fX, fY);
    }
}
