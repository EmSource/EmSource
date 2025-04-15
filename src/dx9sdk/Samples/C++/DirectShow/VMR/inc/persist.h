//------------------------------------------------------------------------------
// File: persist.h
//
// Desc: DirectShow sample code
//       - State persistence helper functions used by VMR samples
//
// Copyright (c) 1994 - 2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


/* -------------------------------------------------------------------------
** Recent filename constants
** -------------------------------------------------------------------------
*/
typedef TCHAR RECENTFILES[MAX_PATH];

#define MAX_RECENT_FILES    10
#define ID_RECENT_FILE_BASE 500

int GetRecentFiles(int LastCount, int iMenuPosition);
int SetRecentFiles(TCHAR *FileName, int iCount, int iMenuPosition);

