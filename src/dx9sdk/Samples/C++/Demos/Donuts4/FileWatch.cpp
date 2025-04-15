//-----------------------------------------------------------------------------
// File: FileWatch.cpp
//
// Copyright (C) Microsoft Corporation. All Rights Reserved.
//-----------------------------------------------------------------------------
#include "stdafx.h"




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
CFileWatch::CFileWatch()
{
    m_nFilesToWatch         = 0;
    m_hFileChangeThread     = NULL;
    m_dwFileChangeThreadId  = 0;
    m_bFileChanged          = FALSE;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
CFileWatch::~CFileWatch()
{
    Cleanup();
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT CFileWatch::AddFileToWatch( TCHAR* strWatchFile )
{
    strcpy( m_strFilesToWatch[m_nFilesToWatch++], strWatchFile );
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT CFileWatch::Start()
{
    m_hFileChangeThread = CreateThread( NULL, 0, StaticFileChangeThreadFunc, 
                                        this, 0, &m_dwFileChangeThreadId );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
BOOL CFileWatch::HaveFilesChanged( BOOL bResetChangeFlag )
{
    BOOL bFileChanged = m_bFileChanged;

    if( bResetChangeFlag )
        m_bFileChanged = FALSE;

    return bFileChanged;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
DWORD WINAPI CFileWatch::StaticFileChangeThreadFunc( LPVOID lpParam )
{
    CFileWatch* pApp = (CFileWatch*) lpParam;
    return pApp->FileChangeThreadFunc();
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
DWORD CFileWatch::FileChangeThreadFunc()
{
    HANDLE      hFileHandles[MAX_WATCH_FILES];
    FILETIME    aLastWriteTime[MAX_WATCH_FILES];
    TCHAR       astrFileDir[MAX_WATCH_FILES][MAX_PATH];
    TCHAR*      strFilePart;
    FILETIME    lastWriteTime;
    DWORD       dwResult;
    int         i;
    int         j;
    HANDLE      hWatchHandles[MAX_WATCH_FILES];
    int         nWatchHandles = 0;

    for( i=0; i<m_nFilesToWatch; i++ )
    {
        hFileHandles[i] = CreateFile( m_strFilesToWatch[i], GENERIC_READ, 
                                    FILE_SHARE_READ|FILE_SHARE_WRITE, 
                                    NULL, OPEN_EXISTING, 0, NULL );
        GetFileTime( hFileHandles[i], NULL, NULL, &aLastWriteTime[i] );
        GetFullPathName( m_strFilesToWatch[i], MAX_PATH, 
                         astrFileDir[i], &strFilePart );
        if( strFilePart ) 
            *strFilePart = 0;

        BOOL bFound = FALSE;
        for( j=0; j<i; j++ )
        {
            if( strcmp( astrFileDir[i], astrFileDir[j] ) == 0 )
            {
                bFound = TRUE;
                break;
            }
        }

        if( !bFound )
        {
            hWatchHandles[nWatchHandles++] = FindFirstChangeNotification( 
                                                astrFileDir[i], FALSE, 
                                                FILE_NOTIFY_CHANGE_LAST_WRITE );
        }
    }
    
    BOOL bDone = FALSE;
    while( !bDone )
    {   
        dwResult = MsgWaitForMultipleObjects( nWatchHandles, hWatchHandles, FALSE, INFINITE, QS_ALLEVENTS );
        if( dwResult == WAIT_OBJECT_0 + nWatchHandles )
        {
            MSG msg;
            if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
            {
                if ( msg.message == WM_QUIT )
                    bDone = TRUE;
            }
        }
        else
        {
            int nIndex = dwResult - WAIT_OBJECT_0;
            assert( nIndex >= 0 || nIndex < 10 );

            for( i=0; i<m_nFilesToWatch; i++ )
            {
                GetFileTime( hFileHandles[i], NULL, NULL, &lastWriteTime );
                if( memcmp(&lastWriteTime, &aLastWriteTime[i], sizeof(FILETIME) ) ) 
                {
                    m_bFileChanged = TRUE;
                }
            }

            FindNextChangeNotification( hWatchHandles[nIndex] );
            FindNextChangeNotification( hWatchHandles[nIndex] ); 
        }
    }

    for( i=0; i<nWatchHandles; i++ )
        FindCloseChangeNotification( hWatchHandles[i] );

    for( i=0; i<m_nFilesToWatch; i++ )
        CloseHandle( hFileHandles[i] );

    return 0;
}




//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------
HRESULT CFileWatch::Cleanup()
{
    if( m_hFileChangeThread )
    {
        PostThreadMessage( m_dwFileChangeThreadId, WM_QUIT, 0, 0 );
        WaitForSingleObject( m_hFileChangeThread, INFINITE );
        CloseHandle( m_hFileChangeThread );
        m_hFileChangeThread = NULL;
    }

    return S_OK;
}
