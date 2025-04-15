//------------------------------------------------------------------------------
// File: TransViewer.cpp
//
// Desc: DirectShow sample code - TransViewer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "Transviewer.h"

#include "CPoster.h"
#include "Graph.h"
#include "Timeline.h"

#include <initguid.h>
#include "cerrorlog.h"
#include <commdlg.h>


//-----------------------------------------------------------------------------
//  Function prototypes
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

HRESULT SetTransition();
HRESULT SetFileName(int nSource);
HRESULT PickSolidColor(int nSource);
HRESULT SetSolidColor(int nSource, COLORREF color);
HRESULT RenderTimeline();
HRESULT EnableErrorLogging(bool fEnable);

void    OnInitDialog(HWND hDlg);
void    GraphEventCallback(long evCode, long Param1, long Param2);
void    PlayNextTransition(HWND hDlg);
void    EnablePreview(BOOL fPreview);
void    DoSetProperties();
void    Stop(void);
void    Pause(void);
void    CleanUp();

void AddAboutMenuItem(HWND hWnd);
LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//-----------------------------------------------------------------------------
//  Defines, constants, and global variables
//-----------------------------------------------------------------------------
HWND                g_hwnd=0;         // Main dialog window
HINSTANCE           g_hinst=0;        // App instance

// Helper objects
CGraphHelper        g_Graph;          // Controls the graph
CTimeline           *g_pTimeline=0;   // Cuilds/renders the timeline
CPosterImage        *g_pPoster1=0, *g_pPoster2=0;  // These display the preview images

//-----------------------------------------------------------------------------
//  Helper macros
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p); (p) = NULL; } }


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------

INT APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, 
                      INT nCmdShow )
{
    // Save instance handle
    g_hinst = hInst; 

    // Initialize COM   
    if(FAILED(CoInitialize(NULL))) 
    {
        MessageBox(NULL, TEXT("Could not initialize COM library."), 
                   DEMO_NAME, MB_OK | MB_ICONERROR );
        return FALSE;
    }

    // Display the main dialog box.
    DialogBox( hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc );

    // Release COM
    CoUninitialize();

    return TRUE;
}


//-----------------------------------------------------------------------------
// Name: MainDlgProc
// Desc: DialogProc for the main dialog.
//-----------------------------------------------------------------------------

INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch (msg) 
    {   
        case WM_INITDIALOG:
            OnInitDialog( hDlg );
            return FALSE;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;      

        case WM_DESTROY:
            CleanUp();
            EndDialog(hDlg, 0);
            break;

        case WM_NEXTITEM:
            PlayNextTransition(hDlg);
            break;
                    
        case WM_COMMAND:        
            switch (LOWORD(wParam))
            {
                case IDC_PREVIEW:
                    RenderTimeline();
                    break;
                    
                case IDC_TRANS:
                    switch (HIWORD(wParam))
                    {
                        case LBN_SELCHANGE:
                            Stop();          // Stop the current transition
                            EnablePreview(TRUE);
                            SetTransition();
                            break;

                        default: 
                            return FALSE;    // Did not handle this message
                    }
                    break;

                case IDC_STOP:
                    Stop();
                    EnablePreview(TRUE);
                    break;
                    
                case IDC_PAUSE:
                    Pause();
                    break;
                    
                case IDC_PICK_CLIP1:
                    SetFileName(1);
                    break;

                case IDC_PICK_CLIP2:
                    SetFileName(2);
                    break;

                case IDC_PICK_COLOR1:
                    PickSolidColor(1);
                    break;

                case IDC_PICK_COLOR2:
                    PickSolidColor(2);
                    break;

                case IDM_PROPERTIES:
                    DoSetProperties();
                    break;

                default:
                    return FALSE; // Did not handle this message
            }                           
            break;

        case WM_PAINT:
        {
            if (g_pPoster1) 
                g_pPoster1->Draw();
            if (g_pPoster2) 
                g_pPoster2->Draw();

            return FALSE;
        }
        break;
            
        case WM_GRAPHNOTIFY:
            // Handle graph events on a callback
            g_Graph.ProcessEvents(GraphEventCallback);  
            break;

        case WM_ERRORLOG:
        {
            USES_CONVERSION;
            BSTR bstrError = (LPOLESTR)wParam;
            SetWindowText(GetDlgItem(g_hwnd, IDC_ERRORLOG), OLE2T(bstrError));
            SysFreeString(bstrError);
        }
        break;

        case WM_SYSCOMMAND:
        {
            switch (wParam)
            {
                case IDM_ABOUTBOX:
                    DialogBox(g_hinst, MAKEINTRESOURCE(IDD_ABOUTBOX), hDlg, 
                             (DLGPROC) AboutDlgProc);
            }
            return FALSE;
        }

        default:
            return FALSE; // Did not handle the message             
    }
    
    return TRUE; // Handled the message;
}


//-----------------------------------------------------------------------------
// Name: OnInitDialog
// Desc: Initializes the main dialog
//-----------------------------------------------------------------------------

void OnInitDialog( HWND hDlg )
{
    HRESULT hr;

    // Save window handle
    g_hwnd = hDlg;

    HICON hIcon = LoadIcon( g_hinst, MAKEINTRESOURCE( IDI_ICON ) );

    // Set the icon for this dialog.
    SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
    SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon
    SetWindowText(hDlg, DEMO_NAME);

    g_pPoster1 = new CPosterImage(GetDlgItem(hDlg, IDC_CLIP1));
    g_pPoster2 = new CPosterImage(GetDlgItem(hDlg, IDC_CLIP2));

    g_pTimeline = new CTimeline();

    // Initialize the timeline with our video dimensions
    RECT rect;
    GetClientRect(GetDlgItem(hDlg, IDC_VIDWIN), &rect);
    hr = g_pTimeline->InitTimeline(rect);

    // Populate the list of transitions
    g_pTimeline->InitTransitionList(GetDlgItem(hDlg, IDC_TRANS));

    // Create an error logging object
    CComPtr<IAMErrorLog> pErrLog;

    hr = CErrorLog::CreateErrorLog(&pErrLog);
    if (SUCCEEDED(hr))
    {
        g_pTimeline->SetErrorLog(pErrLog);
    }

    // Initialize the preview colors 
    hr = SetSolidColor(1, RGB(0xFF, 0xFF, 0x00));
    hr = SetSolidColor(2, RGB(0x0, 0x0, 0x0));

    // Add a menu item to the app's system menu
    AddAboutMenuItem(hDlg);
}


//-----------------------------------------------------------------------------
// Name: GraphEventCallback
// Desc: Process one DirectShow event. The graph helper object (CGraphHelper) 
//       uses this callback to process graph events.
//-----------------------------------------------------------------------------

void GraphEventCallback(long evCode, long Param1, long Param2)
{
    // We only care about stopping events
    switch (evCode) 
    {
        case EC_COMPLETE:   // fall through
        case EC_ERRORABORT: // fall through
        case EC_USERABORT:

            Stop();
        
            // If we're looping items, restart the current transition
            if (IsDlgButtonChecked(g_hwnd, IDC_CHECK_LOOP))
                RenderTimeline();
        
            // If we're cycling items, move on to the next one
            else if (IsDlgButtonChecked(g_hwnd, IDC_CHECK_CYCLE))
                PostMessage(g_hwnd, WM_NEXTITEM, 0, 0L);
        
            else
                EnablePreview(TRUE);

            break;
    }
    
    // Event memory is freed by the caller
}


//-----------------------------------------------------------------------------
// Name: SetTransition
// Desc: Sets the transition object from the current listbox selection
//-----------------------------------------------------------------------------

HRESULT SetTransition()
{
    HWND hListBox = GetDlgItem(g_hwnd, IDC_TRANS);
    int nTransition = (int) SendMessage(hListBox, LB_GETCURSEL, 0, 0);

    HRESULT hr = g_pTimeline->SetTransition(nTransition);

    return hr;
}


//-----------------------------------------------------------------------------
// Name: SetFileName
// Desc: Presents an Open File dialog to the user. Sets the file name on
//       the source object and updates the poster image.
//       
//       nSource: Index of the source in the timeline (1 or 2)
//-----------------------------------------------------------------------------

// File filter for OpenFile dialog
#define FILE_FILTER_TEXT \
    TEXT("Video Files (*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v)\0*.avi; *.qt; *.mov; *.mpg; *.mpeg; *.m1v\0")\
    TEXT("Image Files (*.jpg, *.bmp, *.gif, *.tga)\0*.jpg; *.bmp; *.gif; *.tga\0\0")


HRESULT SetFileName(int nSource)
{
    HRESULT hr;
    OPENFILENAME ofn;
    TCHAR tszFileName[MAX_PATH] = TEXT("\0");
    TCHAR tszFileTitle[MAX_PATH] = TEXT("\0");

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = g_hwnd;
    ofn.lpstrFilter  = FILE_FILTER_TEXT;
    ofn.lpstrFile    = tszFileName;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrFileTitle = tszFileTitle;
    ofn.nMaxFileTitle  = MAX_PATH;
    ofn.lpstrTitle   = TEXT("Select a Source Clip...");
    ofn.Flags        = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY;

    if (!GetOpenFileName(&ofn))
        return S_FALSE;

    hr = g_pTimeline->SetFileName(nSource, ofn.lpstrFile);

    HWND hLabel = GetDlgItem(g_hwnd, (nSource == 1 ? IDC_CLIP1_CAPTION : IDC_CLIP2_CAPTION));

    SendMessage(hLabel, WM_SETTEXT, 0, (LPARAM)tszFileTitle);

    if (nSource == 1) 
    {
        g_pPoster1->SetBitmap(ofn.lpstrFile);
    }
    else
    {
        g_pPoster2->SetBitmap(ofn.lpstrFile);
    }

    EnablePreview(TRUE);
    return hr;
}


//-----------------------------------------------------------------------------
// Name: PickSolidColor
// Desc: Presents a Choose Color dialog to the user. Sets a solid color on a
//       source object and updates the poster image.
//       
//       nSource: Index of the source in the timeline (1 or 2)
//-----------------------------------------------------------------------------

HRESULT PickSolidColor(int nSource)
{
    static COLORREF acrCustomClr[16];
    CHOOSECOLOR cc;

    ZeroMemory(&cc, sizeof(CHOOSECOLOR));
    cc.lStructSize  = sizeof(CHOOSECOLOR);
    cc.hwndOwner    = g_hwnd;
    cc.lpCustColors = (LPDWORD)acrCustomClr;
    cc.Flags        = CC_RGBINIT;

    // Get a default color for dialog.
    if (nSource == 1)
    {
        g_pPoster1->GetColor(&(cc.rgbResult));
    }
    else
    {
        g_pPoster2->GetColor(&(cc.rgbResult));
    }

    if (!ChooseColor(&cc))
    {
        return S_FALSE;
    }

    // Set the color on the timeline source.
    HRESULT hr = SetSolidColor(nSource, cc.rgbResult);

    if (SUCCEEDED(hr))
    {
        // Set the caption to "0xGGBBRR"
        TCHAR szColorName[9];

        HWND hLabel = GetDlgItem(g_hwnd, (nSource == 1 ? IDC_CLIP1_CAPTION : IDC_CLIP2_CAPTION));
        wsprintf(szColorName, TEXT("0x%06X\0"), cc.rgbResult);

        SendMessage(hLabel, WM_SETTEXT, 0, (LPARAM)szColorName);
    }

    return hr;
}


//-----------------------------------------------------------------------------
// Name: SetSolidColor
// Desc: Sets a solid color on a source object and updates the poster image.
//       
//       nSource: Index of the source in the timeline (1 or 2)
//       color:   Color value for the source.
//------------------------------------------------------------------------------

HRESULT SetSolidColor(int nSource, COLORREF color)
{
    HRESULT hr = g_pTimeline->SetSolidColor(nSource, color);

    if (SUCCEEDED(hr))
    {
        // Set the color on the poster image 
        if (nSource == 1) {
            g_pPoster1->SetColor(color);
        }
        else {
            g_pPoster2->SetColor(color);
        }
    }

    EnablePreview(TRUE);
    return hr;
}


//-----------------------------------------------------------------------------
// Name: RenderTimeline
// Desc: Starts previewing the timeline.
//       
//-----------------------------------------------------------------------------

HRESULT RenderTimeline() 
{
    HRESULT hr;
    static bool bFirstRender = true;

    // Disable the "Preview" button while playing this transition
    EnablePreview(FALSE);
    EnableErrorLogging(TRUE);

    g_Graph.Stop();

    // Clear the error window
    SendMessage(GetDlgItem(g_hwnd, IDC_ERRORLOG), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)TEXT(""));

    g_pTimeline->RenderTimeline();

    // Get the filter graph and set up the video window.
    if (bFirstRender) 
    {
        CComPtr<IGraphBuilder> pGraph;

        hr = g_pTimeline->GetFilterGraph(&pGraph);

        g_Graph.SetFilterGraph(pGraph);
        g_Graph.SetVideoWindow(GetDlgItem(g_hwnd, IDC_VIDWIN));
        g_Graph.SetEventWindow(g_hwnd);

        bFirstRender = false;
    }

    // Run the graph.  When the playback completes, an EC_COMPLETE event 
    // will be generated and processed.
    return g_Graph.Run();
}


//-----------------------------------------------------------------------------
// Name: EnablePreview
// Desc: Enable or disable the preview button.
//-----------------------------------------------------------------------------

void EnablePreview(BOOL fPreview)
{
    EnableWindow(GetDlgItem(g_hwnd, IDC_PREVIEW), fPreview);
}


//-----------------------------------------------------------------------------
// Name: Stop
// Desc: Stop previewing.
//-----------------------------------------------------------------------------

void Stop()
{
    // Stopping the graph can trigger a bogus error sometimes, 
    // so disable logging temporarily.
    EnableErrorLogging(FALSE);

    g_Graph.Stop();

    // Do not enable the preview button, because this method is called
    // while cycling between transitions.
}    


//-----------------------------------------------------------------------------
// Name: Pause
// Desc: Pause previewing.
//-----------------------------------------------------------------------------

void Pause()
{
    // If we are currently paused, resume playing
    if (g_Graph.State() == State_Paused)
    {
        g_Graph.Run();
    }
    // Don't transition to Paused state if we are in the stopped state,
    // since pause is only valid when we are playing a transition
    else if (g_Graph.State() != State_Stopped)
    {
        g_Graph.Pause();
    }

    EnablePreview(TRUE);
}


//-----------------------------------------------------------------------------
// Name: PlayNextTransition
// Desc: Cycles to the next transition in the list and previews.
//-----------------------------------------------------------------------------

void PlayNextTransition(HWND hDlg)
{
    HWND hwndList = GetDlgItem(g_hwnd, IDC_TRANS);
    int nItems  = (int) SendMessage(hwndList, LB_GETCOUNT, 0, 0L);

    // Return if the list is empty
    if (!nItems)
        return;

    // Select the next item in the list, wrapping to top if needed
    int nCurSel = (int) SendMessage(hwndList, LB_GETCURSEL, 0, 0L);
    int nNewSel = (nCurSel + 1) % nItems;
    SendMessage(hwndList, LB_SETCURSEL, nNewSel, 0L);

    // Play the next transition
    SetTransition();
    RenderTimeline();
}


//-----------------------------------------------------------------------------
// Name: EnableErrorLogging
// Desc: Enable or disable the error logging object.
//-----------------------------------------------------------------------------

HRESULT EnableErrorLogging(bool fEnable)
{
    CComPtr<IAMErrorLog> pLog;
    HRESULT hr = g_pTimeline->GetErrorLog(&pLog);

    if (SUCCEEDED(hr))
    {
        // Our error logger exposes a custom interface ...
        CComQIPtr<IAMErrorLogEx, &IID_IAMErrorLogEx> pErrEx(pLog);
        if (pErrEx)
        {
            pErrEx->Enable(fEnable);
        }
    }  

    return hr;
}


//-----------------------------------------------------------------------------
// Name: DoSetProperties
// Desc: Show a dialog for the user to set transition properties.
//       This is actually handled by the CTimeline helper object.
//-----------------------------------------------------------------------------

void DoSetProperties()
{
    if (g_pTimeline != 0)
    {
        g_pTimeline->SetProperties(g_hinst, g_hwnd);
    }
}


//-----------------------------------------------------------------------------
// Name: CleanUp
// Desc: Dispose of everything. Called before the application exits.
//-----------------------------------------------------------------------------

void CleanUp()
{
    // We use smart pointers so there's not much to do here.

    // Tell the graph helper object to free resources.
    g_Graph.SetFilterGraph(0);

    SAFE_DELETE(g_pPoster1);
    SAFE_DELETE(g_pPoster2);
    SAFE_DELETE(g_pTimeline);
}


//-----------------------------------------------------------------------------
// Name: AboutDlgProc()
// Desc: Message handler for About box
//-----------------------------------------------------------------------------

LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            if (wParam == IDOK)
            {
                EndDialog(hWnd, TRUE);
                return TRUE;
            }
            break;
    }
    return FALSE;
}

//-----------------------------------------------------------------------------
// Name: AddAboutMenuItem()
// Desc: Adds a menu item to the end of the app's system menu
//-----------------------------------------------------------------------------
void AddAboutMenuItem(HWND hWnd)
{
    // Add About box menu item
    HMENU hwndMain = GetSystemMenu(hWnd, FALSE);

    // Add separator
    BOOL rc = AppendMenu(hwndMain, MF_SEPARATOR, 0, NULL);

    // Add menu item
    rc = AppendMenu(hwndMain, MF_STRING | MF_ENABLED, 
                    IDM_ABOUTBOX,
                    TEXT("About TransViewer...\0"));
}

