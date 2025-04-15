//------------------------------------------------------------------------------
// File: SourceInfo.cpp
//
// Desc: DirectShow sample code
//       Implementation of CMediaList, play-list of media files
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SourceInfo.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMediaList::CMediaList() :
                m_avgDuration(0L),
                m_N(0),
                m_ppSI(NULL)
{
}

CMediaList::~CMediaList()
{
    Clean();
}


//------------------------------------------------------------------------------
// CMediaList::Clean
// Desc: clean up the media list
// return: 
//------------------------------------------------------------------------------
void CMediaList::Clean()
{
    for( int i=0; i<m_N; i++)
    {
        delete m_ppSI[i];
        m_ppSI[i] = NULL;
    }

    delete[] m_ppSI;
    m_ppSI = NULL;
    m_N = 0;
}

//------------------------------------------------------------------------------
// CMediaList::Add
// Desc: adds a new source to the media list
// return: true if success, false otherwise
//------------------------------------------------------------------------------
bool CMediaList::Add( SourceInfo * pSI)
{
    CheckPointer(pSI,false);
    
    SourceInfo ** ppSInew = NULL;

    ppSInew = new SourceInfo * [m_N+1];
    if( !ppSInew )
        return false;

    for( int i=0; i<m_N; i++)
    {
        ppSInew[i] = m_ppSI[i];
    }

    ppSInew[m_N] = pSI;
    delete[] m_ppSI;

    m_ppSI = ppSInew;
    m_N++;

    return true;
}
    
//------------------------------------------------------------------------------
// CMediaList::Shuffle()
// Desc: randomly shuffles media list content to 
//       have different playback settings every time
//------------------------------------------------------------------------------
void CMediaList::Shuffle()
{
    SourceInfo *pSIaux = NULL;
    int n1;
    int n2;

    for(int i=0; i< m_N; i++)
    {
        n1 = rand() * (m_N+1) / RAND_MAX;
        n2 = rand() * (m_N+1) / RAND_MAX;

        n1 = ( n1<0) ? 0 : n1;
        n2 = ( n2<0) ? 0 : n2;

        n1 = ( n1>m_N-1) ? m_N-1 : n1;
        n2 = ( n2>m_N-1) ? m_N-1 : n2;

        if( n1 == n2 )
            continue;

        pSIaux = m_ppSI[n1];
        m_ppSI[n1] = m_ppSI[n2];
        m_ppSI[n2] = pSIaux;
    }
}

//------------------------------------------------------------------------------
// Name: SetInitialParameters
// Purpose: calculates initial demonstration parameters for each media file --
//          destination rectangles and alpha levels
//          Note that these values are used as parameters in CDemonstration and 
//          that changing them can cause different appearence of the demonstration          
//------------------------------------------------------------------------------
void CMediaList::SetInitialParameters()
{
    NORMALIZEDRECT rectD;
    double Alpha;
    int i;

    // set alpha levels and destination rectangles here
    for( i=0; i< m_N; i++)
    {
        Alpha = 0.3 + 0.68 * (double)rand() / RAND_MAX; // random in [0.3; 0.98]
        
        rectD.left = rectD.top = 0.1f;
        rectD.right = rectD.bottom = 0.9f;

        this->GetItem(i)->m_fAlpha = Alpha;
        this->GetItem(i)->m_rD = rectD;
    }
}

//------------------------------------------------------------------------------
// Name: Initialize
// Purpose: go through m_szMediaFolder and retrieve all media files
// Parameters: none
// Return: true if folder contains at least one valid file;
//         false otherewise
//------------------------------------------------------------------------------
bool CMediaList::Initialize(TCHAR *szFolder)
{
    long filehandle = -1L;
    int nRes;
    int nCounter = 0; // to prevent loading huge number of files,
                      // let's restrict it to 50
    TCHAR szMask[MAX_PATH];
    TCHAR szExt[] = TEXT("*.AVI;*.MOV;*.MPG;*.MPEG;*.VOB;*.QT;");
    TCHAR szCurExt[MAX_PATH];
    TCHAR szFilePath[MAX_PATH];
    TCHAR *psz = NULL;

    // clean the list
    Clean();

    if( !_tcsicmp(szFolder,_T("")))
        return false;

    do
    {
        _tcscpy(szCurExt,szExt);
        psz = _tcsstr(szCurExt, _T(";"));
        if( psz)
        {
            *psz = 0;
            psz = NULL;
            psz = _tcsstr( szExt, _T(";"));
            if( psz )
            {
                _tcscpy( szExt, psz+1);
            }
        }
        else
        {
            _tcscpy( szExt, _T(""));
        }

        _sntprintf(szMask, MAX_PATH-1, _T("%s%s\0"), szFolder, szCurExt);
        szMask[MAX_PATH-1] = 0;

        #ifndef UNICODE
            struct _finddata_t fileinfo;
        #else
            struct _wfinddata_t fileinfo;
        #endif

        filehandle = (long) _tfindfirst(szMask, &fileinfo);
        if( filehandle == -1L)
            continue;
        
        SourceInfo * pSI = NULL;
        pSI = new SourceInfo;
        if( !pSI )
        {
            _findclose(filehandle);
            return false;
        }

        _sntprintf( szFilePath, MAX_PATH, _T("%s%s\0"), szFolder, fileinfo.name);
        _tcsncpy( pSI->m_szPath, (const TCHAR*)szFilePath, NUMELMS(pSI->m_szPath));

        #ifndef UNICODE
            MultiByteToWideChar(CP_ACP, 0, (const TCHAR*)szFilePath, -1, pSI->m_wszPath, MAX_PATH); 
        #else
            USES_CONVERSION;
            _tcsncpy(pSI->m_wszPath, T2W(szFilePath), MAX_PATH-1);
            pSI->m_wszPath[MAX_PATH-1] = 0;
        #endif
        
        Add( pSI );
        nCounter++;

        nRes = _tfindnext(filehandle, &fileinfo);

        while( -1L != nRes )
        {
            pSI = NULL;
            pSI = new SourceInfo;
            if( !pSI )
            {
                _findclose(filehandle);
                return false;
            }

            _sntprintf( szFilePath, MAX_PATH, _T("%s%s\0"), szFolder,fileinfo.name);
            _tcsncpy( pSI->m_szPath, (const TCHAR*)szFilePath, NUMELMS(pSI->m_szPath));

        #ifndef UNICODE
            MultiByteToWideChar(CP_ACP, 0, (const TCHAR*)szFilePath, -1, pSI->m_wszPath, MAX_PATH); 
        #else
            USES_CONVERSION;
            _tcsncpy(pSI->m_wszPath, T2W(szFilePath), MAX_PATH-1);
            pSI->m_wszPath[MAX_PATH-1] = 0;
        #endif

            Add( pSI );
            nCounter++;
            nRes = _tfindnext(filehandle, &fileinfo); 
        }// while

    } while( _tcsicmp(szExt, _T("")) && nCounter < 50 );

    if (filehandle != -1)
        _findclose(filehandle);

    if( 0 == Size() )
    {
        return false;
    }
    else
    {
        return true;
    }
}

//------------------------------------------------------------------------------
// Name: Clone
// Purpose: copies elements (nStart; nStart+n) to the list pML
// Parameters: n      - number of elements
//             pML    - cloned media list
//             nStart - start position in (this) list; default: 0
// Return: true if success;
//         false otherewise
//------------------------------------------------------------------------------
bool CMediaList::Clone(int n, CMediaList *pML, int nStart /* = 0 */)
{
    bool bRes = true;

    if( n < 1 || nStart < 0 || nStart + n > m_N)
        return false;

    pML->Clean();

    for(int i = nStart; i< nStart + n; i++)
    {
        SourceInfo *pSI = NULL;
        
        pSI = new SourceInfo;
        if( !pSI )
            goto cleanup;

        bRes = bRes && GetItem(i)->CopyTo( pSI);

        if( false == bRes)
        {
            delete pSI;
            goto cleanup;
        }

        pSI->m_bInUse = false;

        bRes = bRes && pML->Add(pSI);
        if( false == bRes)
            goto cleanup;
    }
    return true;

cleanup:
    pML->Clean();
    return false;
}

//------------------------------------------------------------------------------
// Name: AdjustDuration
// Purpose: calculates demonstration time. Here, it is duration of the longest file.
//          Change this function to set a fixed time, average time etc.         
//------------------------------------------------------------------------------
void CMediaList::AdjustDuration()
{
    m_avgDuration = 0L;
    
    if( 0 == m_N )
    {
        return;
    }

    for( int i=0; i<m_N; i++)
    {     
        m_avgDuration = (this->GetItem(i)->m_llDuration > m_avgDuration) ?
            this->GetItem(i)->m_llDuration : m_avgDuration;
    }
}


