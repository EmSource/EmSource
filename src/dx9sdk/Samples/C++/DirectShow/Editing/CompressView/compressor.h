//------------------------------------------------------------------------------
// File: Compressor.h
//
// Desc: DirectShow sample code - header file for CompressView sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#if !defined(AFX_COMPRESSOR_H__93887C87_F627_4CEA_9213_94F0D4A95F5E__INCLUDED_)
#define AFX_COMPRESSOR_H__93887C87_F627_4CEA_9213_94F0D4A95F5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompressorApp:
// See Compressor.cpp for the implementation of this class
//

class CCompressorApp : public CWinApp
{
public:
    CCompressorApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCompressorApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CCompressorApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPRESSOR_H__93887C87_F627_4CEA_9213_94F0D4A95F5E__INCLUDED_)
