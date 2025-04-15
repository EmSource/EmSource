//------------------------------------------------------------------------------
// File: Compressor.cpp
//
// Desc: DirectShow sample code - Defines the class behaviors for the application
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "Compressor.h"
#include "CompressorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompressorApp

BEGIN_MESSAGE_MAP(CCompressorApp, CWinApp)
    //{{AFX_MSG_MAP(CCompressorApp)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompressorApp construction

CCompressorApp::CCompressorApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCompressorApp object

CCompressorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCompressorApp initialization

BOOL CCompressorApp::InitInstance()
{
    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

    CCompressorDlg dlg;
    m_pMainWnd = &dlg;

    // Display the main dialog
    dlg.DoModal();

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}
