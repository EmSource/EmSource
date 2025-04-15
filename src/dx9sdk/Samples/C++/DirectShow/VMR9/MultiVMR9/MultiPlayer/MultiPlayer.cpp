//------------------------------------------------------------------------------
// File: MultiPlayer.cpp
//
// Desc: DirectShow sample code - MultiVMR9 MultiPlayer sample
//       Defines the class behaviors for the application
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MultiPlayer.h"
#include "MultiPlayerDlg.h"
#include "MultiVMR9_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HINSTANCE g_hInstance = NULL;;

// CMultiPlayerApp

BEGIN_MESSAGE_MAP(CMultiPlayerApp, CWinApp)
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMultiPlayerApp construction

CMultiPlayerApp::CMultiPlayerApp()
{
}


// The one and only CMultiPlayerApp object

CMultiPlayerApp theApp;


//----------------------------------------------------------------------------
//  VerifyVMR9
// 
//  Verifies that VMR9 COM objects exist on the system and that the VMR9
//  can be instantiated.
//
//  Returns: FALSE if the VMR9 can't be created
//----------------------------------------------------------------------------

BOOL CMultiPlayerApp::VerifyVMR9()
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

// CMultiPlayerApp initialization

BOOL CMultiPlayerApp::InitInstance()
{
    CWinApp::InitInstance();

    CMultiPlayerDlg dlg;
    m_pMainWnd = &dlg;

    g_hInstance = AfxGetInstanceHandle();
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    // Verify that the VMR9 is present on this system
    if(!VerifyVMR9())
    {
        CoUninitialize();
        return FALSE;
    }

    // Display the main dialog
    dlg.DoModal();

    // CoUninitialize();
    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}

#ifdef _DEBUG
    void DbgMsg( char* szMessage, ... )
    {
        char szFullMessage[MAX_PATH];
        char szFormatMessage[MAX_PATH];

        // format message
        va_list ap;
        va_start(ap, szMessage);
        _vsnprintf( szFormatMessage, MAX_PATH, szMessage, ap);
        va_end(ap);
        strncat( szFormatMessage, "\n", MAX_PATH);
        strcpy( szFullMessage, "~*~*~*~*~*~ ");
        strcat( szFullMessage, szFormatMessage );
        OutputDebugStringA( szFullMessage );
    }
#else
    void DbgMsg( char* szMessage, ... ){;}
#endif

