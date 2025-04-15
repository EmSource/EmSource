//------------------------------------------------------------------------------
// File: commands.cpp
//
// Desc: DirectShow sample code - Processes commands from the user
//
// Copyright (c) 1994-2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"

#include <commctrl.h>
#include <stdio.h>

// Function prototypes
extern void RepositionMovie(HWND hwnd);

// Global data
extern CMovie  *g_pMovie;


/******************************Public*Routine******************************\
* ProcessOpen
*
\**************************************************************************/
void
ProcessOpen(
    TCHAR achFileName[][MAX_PATH],
    DWORD dwNumFiles,
    BOOL bPlay
    )
{
    /*
    ** If we currently have a video loaded, we need to discard it here
    */
    if(GetMovieMode() != MOVIE_NOTOPENED )
    {
        CubeCloseCmd();
    }

    // Create a CMovie class
    g_pMovie = new CMovie(g_hwndApp);
    if(g_pMovie)
    {
        HRESULT hr = g_pMovie->OpenMovie(achFileName, dwNumFiles);
        if(SUCCEEDED(hr))
        {
            RepositionMovie(g_hwndApp);
            InvalidateRect(g_hwndApp, NULL, TRUE);

            if(bPlay)
                g_pMovie->PlayMovie();
        }
        else
        {
            TCHAR appTitle[100];
            MessageBox(g_hwndApp, TEXT("Failed to render the movie with Video Mixing Renderer! "),
                       IdStr(STR_APP_TITLE, appTitle, sizeof appTitle ), MB_OK);
            g_pMovie->CloseMovie();
            delete g_pMovie;
            g_pMovie = NULL;
        }
    }

    InvalidateRect(g_hwndApp, NULL, FALSE);
    UpdateWindow(g_hwndApp);
}


/******************************Public*Routine******************************\
* CubeOpenCmd
*
\**************************************************************************/
BOOL
CubeOpenCmd(
    void
    )
{
    static OPENFILENAME ofn;
    static BOOL fFirstTime = TRUE;

    BOOL fRet = FALSE;
    TCHAR achFileName[MAXSTREAMS][MAX_PATH];
    TCHAR achFilter[MAX_PATH], achfileFilter[MAX_PATH];
    LPTSTR lp = 0;
    DWORD dwNumFiles = 0;

    if(fFirstTime)
    {
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = g_hwndApp;
        ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST |
                    OFN_SHAREAWARE | OFN_PATHMUSTEXIST;
    }

    lstrcpyn(achFilter, IdStr(STR_FILE_FILTER, achfileFilter, sizeof(achfileFilter)), NUMELMS(achFilter)-1);
    achFilter[MAX_PATH-1] = 0;  // Ensure NULL-termination
    ofn.lpstrFilter = achFilter;

    /*
    ** Convert the resource string into to something suitable for
    ** GetOpenFileName (ie.  replace '#' characters with '\0' characters).
    */
    for(lp = achFilter; *lp; lp++)
    {
        if(*lp == TEXT('#'))
        {
            *lp = TEXT('\0');
        }
    }

    for (DWORD i = 0; i < MAXSTREAMS; i++)
    {
        ofn.lpstrFile = achFileName[i];
        ofn.nMaxFile  = sizeof(achFileName[i]) / sizeof(TCHAR);
        ZeroMemory(achFileName[i], sizeof(achFileName[i]));

        switch (i)
        {
            case 0:
                // load first file
                ofn.lpstrTitle = TEXT("Select First Media File\0");
                break;
            case 1:
                // load first file
                ofn.lpstrTitle = TEXT("Select Second Media File\0");
                break;
            case 2:
                // load first file
                ofn.lpstrTitle = TEXT("Select Third Media File\0");
                break;
        }

        fRet = GetOpenFileName(&ofn);
        if(!fRet)
            break;

        dwNumFiles++;
    }

    fFirstTime = FALSE;

    if (0 == dwNumFiles)
    {
        return fRet;
    }

    ProcessOpen(achFileName, dwNumFiles);

    return fRet;
}


/******************************Public*Routine******************************\
* CubeCloseCmd
*
\**************************************************************************/
BOOL
CubeCloseCmd(
    void
    )
{
    if(g_pMovie)
    {
        g_pMovie->StopMovie();
        g_pMovie->CloseMovie();
        delete g_pMovie;
        g_pMovie = NULL;
    }

    // Redraw main window
    InvalidateRect(g_hwndApp, NULL, FALSE);
    UpdateWindow(g_hwndApp);

    return TRUE;
}


/******************************Public*Routine******************************\
* CubePlayCmd
*
\**************************************************************************/
BOOL
CubePlayCmd(
    void
    )
{
    if(g_pMovie)
        g_pMovie->PlayMovie();
    return TRUE;
}


/******************************Public*Routine******************************\
* CubeStopCmd
*
\**************************************************************************/
BOOL
CubeStopCmd(
    void
    )
{
    if(g_pMovie)
        g_pMovie->StopMovie();
    return TRUE;
}


/******************************Public*Routine******************************\
* CubePauseCmd
*
\**************************************************************************/
BOOL
CubePauseCmd(
    void
    )
{
    if( GetMovieMode() == MOVIE_PLAYING )
    {
        if(g_pMovie)
            g_pMovie->PauseMovie();
    }
    else if( GetMovieMode() == MOVIE_PAUSED )
    {
        if(g_pMovie)
            g_pMovie->PlayMovie();
    }

    return TRUE;
}


/******************************Public*Routine******************************\
* CubeRewindCmd
*
\**************************************************************************/
BOOL
CubeRewindCmd(
    void
    )
{
    if(g_pMovie)
        g_pMovie->SeekToPosition((REFTIME)0,FALSE);

    return TRUE;
}


