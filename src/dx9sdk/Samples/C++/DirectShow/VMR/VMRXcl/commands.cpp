//----------------------------------------------------------------------------
//  File:   commands.cpp
//
//  Desc:   DirectShow sample code
//          Processes commands from the user.
//
//  Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "project.h"

#include <io.h>

// Function prototypes
void RepositionMovie(HWND hwnd);
bool FindMediaFile(TCHAR * achFileName, TCHAR * achFoundFile);

// External data
extern TCHAR    g_achFileName[];
extern CMovie * pMovie;


//----------------------------------------------------------------------------
//  ProcessOpen
// 
//  Creates instance of CMovie and plays it. Called from user UI functions.
//
//  Parameters:
//          achFileName - path to the file to play
//          bPlay       - start demonstration if true
//----------------------------------------------------------------------------
BOOL
ProcessOpen(
    TCHAR *achFileName,
    BOOL bPlay
    )
{
    TCHAR achFoundFile[MAX_PATH];
    TCHAR achErrorMessage[1024];

    achErrorMessage[0] = 0;

    if( !FindMediaFile(achFileName, achFoundFile) )
    {
        InvalidateRect( hwndApp, NULL, FALSE );
        UpdateWindow( hwndApp );
        return false;
    }

    // Copy the file name.  You MUST ensure that the g_achFileName buffer
    // is at least MAX_PATH characters in size.
    lstrcpyn(g_achFileName, achFoundFile, MAX_PATH);

    pMovie = new CMovie(hwndApp);

    if (pMovie) 
    {
        HRESULT hr = pMovie->OpenMovie(g_achFileName, achErrorMessage, 1024);
        if (SUCCEEDED(hr)) 
        {
            g_State = (VCD_LOADED | VCD_STOPPED);

            RepositionMovie(hwndApp);
            InvalidateRect(hwndApp, NULL, TRUE);

            if (bPlay)
                pMovie->PlayMovie();
        }
        else 
        {
            if( 0 == _tclen(achErrorMessage))
            {
                wsprintf(achErrorMessage, TEXT("Failed to open the selected file (hr=0x%x)\r\n")\
                        TEXT("This sample will now exit."),
                        hr);
            }
            MessageBox(hwndApp,  achErrorMessage, IdStr(STR_APP_TITLE), MB_OK );

            pMovie->CloseMovie();
            delete pMovie;
            pMovie = NULL;

            return FALSE;
        }
    }
    else
        return FALSE;

    InvalidateRect( hwndApp, NULL, FALSE );
    UpdateWindow( hwndApp );
    return TRUE;
}

//----------------------------------------------------------------------------
//  FindMediaFile
// 
//  Provides FileOpen dialog to select media file or processes command line
//
//  Parameters:
//          achFileName     - command line
//          achFoundFile    - path to the file to play
//
//  Return: true if success 
//----------------------------------------------------------------------------
bool FindMediaFile(TCHAR * achFileName, TCHAR * achFoundFile)
{
    long lFindRes;
#ifdef UNICODE
    struct _wfinddata_t fileinfo;
#else
    struct _finddata_t fileinfo;
#endif

    lFindRes = (long) _tfindfirst( achFileName, &fileinfo );
    if( -1 != lFindRes )
    {
        lstrcpy(achFoundFile, achFileName);
        return true;
    }

    OPENFILENAME ofn;
    TCHAR  szBuffer[MAX_PATH];

    lstrcpy(szBuffer, TEXT(""));
    static TCHAR szFilter[] = _T("Video Files (.AVI, MOV, .MPG, .QT)\0*.AVI;*.MOV;*.MPG;*.QT\0") \
                              _T("All Files (*.*)\0*.*\0\0");
    ofn.lStructSize         = sizeof(OPENFILENAME);
    ofn.hwndOwner           = NULL;
    ofn.hInstance           = NULL;
    ofn.lpstrFilter         = szFilter;
    ofn.nFilterIndex        = 1;
    ofn.lpstrCustomFilter   = NULL;
    ofn.nMaxCustFilter      = 0;
    ofn.lpstrFile           = szBuffer;
    ofn.nMaxFile            = _MAX_PATH;
    ofn.lpstrFileTitle      = NULL;
    ofn.nMaxFileTitle       = 0;
    ofn.lpstrInitialDir     = NULL;
    ofn.lpstrTitle          = _T("VMRXCL: Select a video file to play...\0");
    ofn.Flags               = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.nFileOffset         = 0;
    ofn.nFileExtension      = 0;
    ofn.lpstrDefExt         = _T("avi");
    ofn.lCustData           = 0L;
    ofn.lpfnHook            = NULL;
    ofn.lpTemplateName  = NULL; 
    
    if (GetOpenFileName (&ofn))  // user specified a file
    {
        lstrcpyn(achFoundFile, ofn.lpstrFile, MAX_PATH);
        return true;
    }

    return false;
}