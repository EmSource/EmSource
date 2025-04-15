//------------------------------------------------------------------------------
// File: Utils.h
//
// Desc: DirectShow sample code
//       Helper function prototypes
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#if !defined(UTILS_H)
#define UTILS_H

#include "stdafx.h"

// helper function prototypes

DWORD MyMessage(TCHAR *szQuestion, TCHAR *szTitle);
void  ShellAbort(CVMRCore *core);

const TCHAR * hresultNameLookup(HRESULT hres);

bool MySleep(DWORD  dwTime = 2500);
void GetMessageName(LPTSTR Name, UINT msg);

#endif