//------------------------------------------------------------------------------
// File: project.h
//
// Desc: DirectShow sample code
//       - Master header file that includes all other header files used
//         by the project.  This enables precompiled headers during build.
//
// Copyright (c) 1994 - 2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <windows.h>
#include <commdlg.h>
#include <shellapi.h>
#include <stdio.h>

#include <streams.h>
#include <mmreg.h>
#include <commctrl.h>

#include <atlbase.h>

#include "persist.h"
#include "app.h"
#include "vcdplyer.h"
#include "resource.h"


void InitStreamParams(int i);
