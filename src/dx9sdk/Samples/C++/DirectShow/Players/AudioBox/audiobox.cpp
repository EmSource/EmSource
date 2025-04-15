//------------------------------------------------------------------------------
// File: Audiobox.cpp
//
// Desc: DirectShow sample code - an MFC based C++ jukebox application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "Audiobox.h"
#include "AudioboxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudioboxApp

BEGIN_MESSAGE_MAP(CAudioboxApp, CWinApp)
    //{{AFX_MSG_MAP(CAudioboxApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioboxApp construction

CAudioboxApp::CAudioboxApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAudioboxApp object

CAudioboxApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAudioboxApp initialization

BOOL CAudioboxApp::InitInstance()
{
    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#if (_MSC_VER <= 1200)
#ifdef _AFXDLL
	// In MFC 5.0, Enable3dControls and Enable3dControlsStatic are obsolete because
	// their functionality is incorporated into Microsoft's 32-bit operating systems.
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

    CAudioboxDlg dlg;
    m_pMainWnd = &dlg;

    dlg.DoModal();

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
