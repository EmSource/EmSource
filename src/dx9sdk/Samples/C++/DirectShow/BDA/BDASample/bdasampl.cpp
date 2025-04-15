//------------------------------------------------------------------------------
// File: Bdasampl.cpp
//
// Desc: Sample code implementing BDA graph building.
//
// Copyright (c) 2000-2002, Microsoft Corporation. All rights reserved.
//------------------------------------------------------------------------------

#include "bdasampl.h"
#include "graph.h"
#include "resource.h"

#include <initguid.h>
#include <objbase.h>

// 
// NOTE: In this sample, text strings are hard-coded for 
// simplicity and for readability.  For product code, you should
// use string tables and LoadString().
//

// Global data
HWND                hwndMain=0;
HWND                g_hwndDlg=0;
HINSTANCE           hInst=0;
TCHAR               szAppName[]  = TEXT("BDASampl\0");
TCHAR               szAppTitle[] = TEXT("BDA Sample\0");

CBDAFilterGraph*    g_pfg = NULL;

// Constants
const int MAJOR_CHANNEL_LOWER_LIMIT = -1;
const int MAJOR_CHANNEL_UPPER_LIMIT = 126;
const int MINOR_CHANNEL_LOWER_LIMIT = -1;
const int MINOR_CHANNEL_UPPER_LIMIT = 126;



INT WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine,
    INT nCmdShow)
{
    MSG         msg={0};
    WNDCLASS    wndclass={0};
    HWND        hwnd=0;
    HACCEL      hAccel=0;

    // Save application instance handle for later use
    hInst = hInstance;

    // Initialize COM library
    HRESULT hr = CoInitializeEx (NULL, COINIT_APARTMENTTHREADED);
    if (FAILED (hr))
    {
        MessageBox(NULL,  TEXT("Failed to initialize COM library!\0"),
                   TEXT("Initialization Error\0"), MB_ICONEXCLAMATION);
        return 0;
    }

    // Register window class
    wndclass.style         = 0;
    wndclass.lpfnWndProc   = WndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = hInst;
    wndclass.hIcon         = LoadIcon(hInst, TEXT("BDASAMPLICON"));
    wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wndclass.lpszMenuName  = szAppName;
    wndclass.lpszClassName = szAppName;
    RegisterClass(&wndclass);

    hwnd = CreateWindow(szAppName, szAppTitle, 
                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 
                200, 200, 500, 280, 
                NULL, NULL, hInst, NULL);
    ASSERT(hwnd);

    // Create the BDA filter graph and initialize its components
    g_pfg = new CBDAFilterGraph();
    ASSERT(g_pfg);

    // If the graph failed to build, don't go any further.
    if (!g_pfg)
    {
        MessageBox(hwnd, TEXT("Failed to create the filter graph!"),
                   TEXT("Initialization Error"), MB_ICONEXCLAMATION);
        return 0;
    }

    // Display main window and configure accelerators    
    ShowWindow(hwnd, nCmdShow);
    hwndMain = hwnd;

    hAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(ACC_GRAPH));

    // Main message loop
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        if(!TranslateAccelerator(hwnd, hAccel, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Release the BDA components and clean up
    delete g_pfg;
    CoUninitialize ();
    
    return msg.wParam;
}


// WndProc                                                                    
LRESULT CALLBACK
WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_CREATE:
        {
            DbgInitialise (hInst);
            break;
        }

        case WM_SIZE:
        {
            if(g_pfg && g_pfg->m_fGraphBuilt)
                g_pfg->SetVideoWindow(hwndMain);
            break;
        }
        
        case WM_COMMAND:
        switch(LOWORD(wParam))
        {
            case IDM_BUILD_ATSC:
            {
                if (!g_pfg)
                    break;
                    
                if(FAILED(g_pfg->BuildGraph(ATSC)))
                {
                    ErrorMessageBox(TEXT("Could not Build the ATSC BDA FilterGraph."));
                }
                else
                {
                    g_pfg->SetVideoWindow(hwndMain);
                }
        
                HMENU hMenu = GetSubMenu(GetMenu(hwnd), 1);

                EnableMenuItem(hMenu, IDM_BUILD_ATSC, MF_GRAYED | MF_BYCOMMAND);

                EnableMenuItem(hMenu, IDM_STOP_GRAPH, 
                    (g_pfg->m_fGraphRunning) ? (MF_BYCOMMAND|MF_ENABLED) : (MF_BYCOMMAND|MF_GRAYED));

                EnableMenuItem(hMenu, IDM_SELECT_CHANNEL, 
                    (g_pfg->m_fGraphBuilt) ? (MF_BYCOMMAND|MF_ENABLED) : (MF_BYCOMMAND|MF_GRAYED));

                break;
            }
            
            case IDM_RUN_GRAPH:
            {
                if (!g_pfg)
                    break;
                    
                if(g_pfg->m_fGraphBuilt)
                {   
                    if(!g_pfg->m_fGraphRunning)
                    {
                        if(FAILED(g_pfg->RunGraph()))
                        {
                            ErrorMessageBox(TEXT("Could not play the FilterGraph."));
                        }
                    }
                }
                else
                {
                    ErrorMessageBox(TEXT("The FilterGraph is not yet built."));
                }

                break;
            }
            
            case IDM_STOP_GRAPH:
            {
                if (!g_pfg)
                    break;
                    
                if(g_pfg->m_fGraphBuilt)
                {
                    if(g_pfg->m_fGraphRunning)
                    {
                        if(FAILED(g_pfg->StopGraph()))
                        {
                            ErrorMessageBox(TEXT("Could not stop the FilterGraph,"));
                        }
                    }
                }
                else
                {
                    ErrorMessageBox(TEXT("The FilterGraph is not yet built."));
                }

                HMENU hMenu = GetSubMenu (GetMenu (hwnd), 1);
                EnableMenuItem (hMenu, IDM_SELECT_CHANNEL, MF_BYCOMMAND | MF_GRAYED);
                break;
            }
            
            case IDM_SELECT_CHANNEL:
            {
                if (!g_pfg)
                    break;
                    
                if(g_pfg->m_fGraphBuilt)
                {
                    g_hwndDlg = reinterpret_cast <HWND> ( DialogBox(
                        hInst, 
                        MAKEINTRESOURCE(IDD_SELECT_CHANNEL),
                        hwnd, 
                        reinterpret_cast<DLGPROC>(SelectChannelDlgProc)
                        ) );
                }
                else
                {
                    ErrorMessageBox(TEXT("The FilterGraph is not yet built."));
                }
                break;
            }
            
            case IDM_ABOUT:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, 
                          reinterpret_cast<DLGPROC>(AboutDlgProc));
                break;
            }
            
            case IDM_EXIT:
            {
                PostMessage(hwnd, WM_CLOSE, 0, 0);
                break;
            }
            
        default:
            break;
        }

    case WM_INITMENU:
        if (!g_pfg)
            break;
                    
        if(g_pfg->m_fGraphFailure)
        {
            EnableMenuItem((HMENU)wParam, IDM_BUILD_ATSC, MF_BYCOMMAND| MF_GRAYED);
            EnableMenuItem((HMENU)wParam, IDM_RUN_GRAPH, MF_BYCOMMAND| MF_GRAYED);
            EnableMenuItem((HMENU)wParam, IDM_STOP_GRAPH, MF_BYCOMMAND| MF_GRAYED);
        }
        else
        {
            EnableMenuItem((HMENU)wParam, IDM_RUN_GRAPH, 
                g_pfg->m_fGraphRunning ? MF_BYCOMMAND|MF_GRAYED : MF_BYCOMMAND|MF_ENABLED);

            EnableMenuItem((HMENU)wParam, IDM_BUILD_ATSC, 
                g_pfg->m_fGraphBuilt ? MF_BYCOMMAND|MF_GRAYED : MF_BYCOMMAND|MF_ENABLED);
        
            // we can stop viewing if it's currently viewing
            EnableMenuItem((HMENU)wParam, IDM_STOP_GRAPH, 
                (g_pfg->m_fGraphRunning) ? MF_BYCOMMAND|MF_ENABLED : MF_BYCOMMAND|MF_GRAYED);
        }

        EnableMenuItem((HMENU)wParam, IDM_SELECT_CHANNEL, 
            g_pfg->m_fGraphBuilt ? MF_BYCOMMAND|MF_ENABLED : MF_BYCOMMAND|MF_GRAYED);

        break;

    case WM_CLOSE:
        DbgTerminate();
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}


// SelectChannelDlgProc
// Dialog Procedure for the "Select Channel" dialog box.
//                                                                              
BOOL CALLBACK
SelectChannelDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    LONG    lChannelMaj, lChannelMin, lChannelPhysical;
    BOOL    bRet = FALSE;
    
    if (!g_pfg)
        return FALSE;;    

    lChannelMaj       = g_pfg->GetMajorChannel ();
    lChannelMin       = g_pfg->GetMinorChannel ();
    lChannelPhysical  = g_pfg->GetPhysicalChannel ();

    switch(message)
    {
    case WM_INITDIALOG:
        {
            //refresh the controls
            SetDlgItemInt (hDlg, IDC_MAJOR_CHANNEL, lChannelMaj, TRUE);
            SetDlgItemInt (hDlg, IDC_MINOR_CHANNEL, lChannelMin, TRUE);
            SetDlgItemInt (hDlg, IDC_PHYSICAL_CHANNEL, lChannelPhysical, TRUE);

            //set the spin controls
            HWND hWndSpin = GetDlgItem (hDlg, IDC_SPIN_MAJOR);
            ::SendMessage(
                hWndSpin, 
                UDM_SETRANGE32, 
                static_cast <WPARAM> (MINOR_CHANNEL_LOWER_LIMIT),
                static_cast <LPARAM> (MAJOR_CHANNEL_UPPER_LIMIT)
                ); 

            hWndSpin = GetDlgItem (hDlg, IDC_SPIN_MINOR);
            ::SendMessage(
                hWndSpin, 
                UDM_SETRANGE32, 
                static_cast <WPARAM> (MINOR_CHANNEL_LOWER_LIMIT), 
                static_cast <LPARAM> (MINOR_CHANNEL_UPPER_LIMIT)
                ); 

            hWndSpin = GetDlgItem (hDlg, IDC_SPIN_PHYSICAL);
            ::SendMessage(
                hWndSpin, 
                UDM_SETRANGE32, 
                static_cast <WPARAM> (MINOR_CHANNEL_LOWER_LIMIT), 
                static_cast <LPARAM> (MINOR_CHANNEL_UPPER_LIMIT)
                );
            break;
        }

    case WM_DESTROY:
        {
            EndDialog (hDlg, 0);
            return TRUE;
        }

    case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
            case IDOK:
                {
                    lChannelMaj = (LONG) GetDlgItemInt(hDlg, IDC_MAJOR_CHANNEL, &bRet, TRUE);
                    lChannelMin = (LONG) GetDlgItemInt(hDlg, IDC_MINOR_CHANNEL, &bRet, TRUE);
                    lChannelPhysical = (LONG) GetDlgItemInt(hDlg, IDC_PHYSICAL_CHANNEL, &bRet, TRUE);
                    g_pfg->ChangeChannel (lChannelPhysical, lChannelMaj, lChannelMin);
                    EndDialog (hDlg, 0);
                    break;
                }
            case IDC_ENTER:
                {
                    lChannelMaj = (LONG) GetDlgItemInt(hDlg, IDC_MAJOR_CHANNEL, &bRet, TRUE);
                    lChannelMin = (LONG) GetDlgItemInt(hDlg, IDC_MINOR_CHANNEL, &bRet, TRUE);
                    lChannelPhysical = (LONG) GetDlgItemInt(hDlg, IDC_PHYSICAL_CHANNEL, &bRet, TRUE);
                    g_pfg->ChangeChannel (lChannelPhysical, lChannelMaj, lChannelMin);
                    break;
                }
            case IDCANCEL:
                {
                    EndDialog (hDlg, 0);
                    break;
                }
            }
            break;
        }
    }
    return FALSE;
}


// AboutDlgProc
//
// Dialog Procedure for the "about" dialog box.
//
BOOL CALLBACK 
AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg) 
    {
        case WM_COMMAND:
            EndDialog(hwnd, TRUE);
            return TRUE;
    
        case WM_INITDIALOG:
            return TRUE;
    }
    return FALSE;
}


// ErrorMessageBox
//
// Opens a Message box with a error message in it.  The user can     
// select the OK button to continue.
//
VOID
ErrorMessageBox(LPTSTR szFormat, ...)
{
    static TCHAR szBuffer[2048];  // Large buffer
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

    // Display a message box with the formatted string
    MessageBox(hwndMain, szBuffer, TEXT("Error!\0"), MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);
}

