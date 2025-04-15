//-----------------------------------------------------------------------------
// File: FileWatch.h
//
// Desc: Class to watch a set of file to see if any change.  If they do
//       then HaveFilesChanged() will return true.
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

#define MAX_WATCH_FILES 10

class CFileWatch  
{
public:
    CFileWatch();
    virtual ~CFileWatch();

    HRESULT AddFileToWatch( TCHAR* strWatchFile );
    HRESULT Start();
    BOOL    HaveFilesChanged( BOOL bResetChangeFlag );
    HRESULT Cleanup();
  
public:

protected:
    DWORD   m_dwFileChangeThreadId;
    HANDLE  m_hFileChangeThread;
    
    TCHAR   m_strFilesToWatch[MAX_WATCH_FILES][MAX_PATH];
    int     m_nFilesToWatch;
    BOOL    m_bFileChanged;    

    static DWORD WINAPI StaticFileChangeThreadFunc( LPVOID lpParam );
    DWORD FileChangeThreadFunc();    
};
