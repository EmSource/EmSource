//------------------------------------------------------------------------------
// File: Audiobox.h
//
// Desc: DirectShow sample code - main header file for the Audiobox
//       application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#if !defined(AFX_AUDIOBOX_H__A0CFADEB_2EC4_463F_947A_D0552C0D1CC1__INCLUDED_)
#define AFX_AUDIOBOX_H__A0CFADEB_2EC4_463F_947A_D0552C0D1CC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAudioboxApp:
// See Audiobox.cpp for the implementation of this class
//

class CAudioboxApp : public CWinApp
{
public:
    CAudioboxApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAudioboxApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CAudioboxApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

extern CAudioboxApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIOBOX_H__A0CFADEB_2EC4_463F_947A_D0552C0D1CC1__INCLUDED_)
