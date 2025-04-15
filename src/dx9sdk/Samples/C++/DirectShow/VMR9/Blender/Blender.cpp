//------------------------------------------------------------------------------
// File: Blender.cpp
//
// Desc: DirectShow sample code - an MFC application that blends two video
//       streams using the Video Mixing Renderer.  Controls are provided for
//       manipulating each video stream's X, Y, size, and alpha values.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Blender.h"
#include "BlenderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlenderApp

BEGIN_MESSAGE_MAP(CBlenderApp, CWinApp)
    //{{AFX_MSG_MAP(CBlenderApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlenderApp construction

CBlenderApp::CBlenderApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBlenderApp object

CBlenderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBlenderApp initialization

BOOL CBlenderApp::InitInstance()
{
    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#if (_MSC_VER <= 1200)
#ifdef _AFXDLL
    // In MFC 5.0, Enable3dControls and Enable3dControlsStatic are obsolete because
    // their functionality is incorporated into Microsoft's 32-bit operating systems.
    Enable3dControls();         // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif
#endif

    CBlenderDlg dlg;
    m_pMainWnd = &dlg;

    // Display the main application dialog    
    dlg.DoModal();

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
