//------------------------------------------------------------------------------
// File: MultiPlayer.h
//
// Desc: DirectShow sample code - main header file for MultiPlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CMultiPlayerApp:
// See DefaultMultiPlayer.cpp for the implementation of this class
//

class CMultiPlayerApp : public CWinApp
{
public:
    CMultiPlayerApp();
    BOOL VerifyVMR9(void);

// Overrides
    public:
    virtual BOOL InitInstance();

// Implementation

    DECLARE_MESSAGE_MAP()
public:

};

extern CMultiPlayerApp theApp;

