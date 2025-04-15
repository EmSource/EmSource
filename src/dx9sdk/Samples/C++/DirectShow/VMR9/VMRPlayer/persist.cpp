//------------------------------------------------------------------------------
// File: persist.cpp
//
// Desc: DirectShow sample code
//       - State persistence helper functions
//
// Copyright (c) 1994 - 2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"


// Global data
RECENTFILES aRecentFiles[MAX_RECENT_FILES]={0};
int         nRecentFiles=0;

// Global static data
static TCHAR cszWindow[] = TEXT("Window\0");
static TCHAR cszAppKey[] = TEXT("Software\\Microsoft\\Multimedia Tools\\VMRPlayer9\0");


// 
// Include the utility code in the common persist.cpp file
//
#include "..\inc\persist.cpp"


