//------------------------------------------------------------------------------
// File: commands.cpp
//
// Desc: DirectShow sample code - Processes commands from the user
//
// Copyright (c) 1994-2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "project.h"

// Function prototypes
extern void RepositionMovie(HWND hwnd);

// Global data
extern TCHAR    g_achFileName[];
extern CMovie * pMovie;


/******************************Public*Routine******************************\
* ProcessOpen
*
\**************************************************************************/
void
ProcessOpen(
    TCHAR *achFileName,
    BOOL bPlay
    )
{
    /*
    ** If we currently have a video loaded we need to discard it here.
    */
    if(g_State & VCD_LOADED)
    {
        VcdPlayerCloseCmd();
    }

    // Copy the filename.  
    // The size of achFileName should not be more than MAX_PATH.
    lstrcpy(g_achFileName, achFileName);

    pMovie = new CMovie(hwndApp);
    if(pMovie)
    {
        HRESULT hr = pMovie->OpenMovie(g_achFileName);
        if(SUCCEEDED(hr))
        {
            TCHAR achTmp[MAX_PATH];

            wsprintf(achTmp, IdStr(STR_APP_TITLE_LOADED), g_achFileName);
            g_State = (VCD_LOADED | VCD_STOPPED);

            RepositionMovie(hwndApp);
            InvalidateRect(hwndApp, NULL, TRUE);

            if(bPlay)
            {
                pMovie->PlayMovie();
            }
        }
        else
        {
            MessageBox(hwndApp, TEXT("Failed to open the movie! "),
                       IdStr(STR_APP_TITLE), MB_OK);

            pMovie->CloseMovie();
            delete pMovie;
            pMovie = NULL;
        }
    }

    InvalidateRect(hwndApp, NULL, FALSE);
    UpdateWindow(hwndApp);
}


/******************************Public*Routine******************************\
* VcdPlayerOpenCmd
*
\**************************************************************************/
BOOL
VcdPlayerOpenCmd(
    void
    )
{
    static OPENFILENAME ofn;
    static BOOL fFirstTime = TRUE;
    BOOL fRet;
    TCHAR achFileName[MAX_PATH];
    TCHAR achFilter[MAX_PATH];
    LPTSTR lp;

    if(fFirstTime)
    {
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner   = hwndApp;
        ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST |
                    OFN_SHAREAWARE | OFN_PATHMUSTEXIST;
    }

    lstrcpy(achFilter, IdStr(STR_FILE_FILTER));
    ofn.lpstrFilter = achFilter;

    /*
    ** Convert the resource string into to something suitable for
    ** GetOpenFileName ie.  replace '#' characters with '\0' characters.
    */
    for(lp = achFilter; *lp; lp++)
    {
        if(*lp == TEXT('#'))
        {
            *lp = TEXT('\0');
        }
    }

    ofn.lpstrFile = achFileName;
    ofn.nMaxFile = sizeof(achFileName) / sizeof(TCHAR);
    ZeroMemory(achFileName, sizeof(achFileName));

    fRet = GetOpenFileName(&ofn);
    if(fRet)
    {
        fFirstTime = FALSE;
        ProcessOpen(achFileName);
    }

    return fRet;
}


/******************************Public*Routine******************************\
* VcdPlayerCloseCmd
*
\**************************************************************************/
BOOL
VcdPlayerCloseCmd(
    void
    )
{
    if(pMovie)
    {
        g_State = VCD_NO_CD;
        pMovie->StopMovie();
        pMovie->CloseMovie();

        delete pMovie;
        pMovie = NULL;
    }

    // Redraw main window
    InvalidateRect(hwndApp, NULL, FALSE);
    UpdateWindow(hwndApp);

    return TRUE;
}

/******************************Public*Routine******************************\
* VcdPlayerPlayCmd
*
\**************************************************************************/
BOOL
VcdPlayerPlayCmd(
    void
    )
{
    BOOL fStopped = (g_State & VCD_STOPPED);
    BOOL fPaused  = (g_State & VCD_PAUSED);

    if((fStopped || fPaused))
    {
        if(pMovie)
        {
            pMovie->PlayMovie();
        }

        g_State &= ~(fStopped ? VCD_STOPPED : VCD_PAUSED);
        g_State |= VCD_PLAYING;
    }

    return TRUE;
}


/******************************Public*Routine******************************\
* VcdPlayerStopCmd
*
\**************************************************************************/
BOOL
VcdPlayerStopCmd(
    void
    )
{
    BOOL fPlaying = (g_State & VCD_PLAYING);
    BOOL fPaused  = (g_State & VCD_PAUSED);

    if((fPlaying || fPaused))
    {
        if(pMovie)
        {
            pMovie->StopMovie();
            pMovie->SetFullScreenMode(FALSE);
        }

        g_State &= ~(fPlaying ? VCD_PLAYING : VCD_PAUSED);
        g_State |= VCD_STOPPED;
    }
    return TRUE;
}


/******************************Public*Routine******************************\
* VcdPlayerPauseCmd
*
\**************************************************************************/
BOOL
VcdPlayerPauseCmd(
    void
    )
{
    BOOL fPlaying = (g_State & VCD_PLAYING);
    BOOL fPaused  = (g_State & VCD_PAUSED);

    if(fPlaying)
    {
        if(pMovie)
        {
            pMovie->PauseMovie();
        }

        g_State &= ~VCD_PLAYING;
        g_State |= VCD_PAUSED;
    }
    else if(fPaused)
    {
        if(pMovie)
        {
            pMovie->PlayMovie();
        }

        g_State &= ~VCD_PAUSED;
        g_State |= VCD_PLAYING;
    }

    return TRUE;
}


/******************************Public*Routine******************************\
* VcdPlayerRewindCmd
*
\**************************************************************************/
BOOL
VcdPlayerRewindCmd(
    void
    )
{
    if(pMovie)
    {
        pMovie->SeekToPosition((REFTIME)0,FALSE);
    }

    return TRUE;
}

