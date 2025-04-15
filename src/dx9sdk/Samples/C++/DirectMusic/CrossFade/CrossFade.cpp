//-----------------------------------------------------------------------------
// File: CrossFade.cpp
//
// Desc: Crossfades between 2 primary segments using DirectMusic
//
// Copyright (c) 2001-2002 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <basetsd.h>
#include <commdlg.h>
#include <commctrl.h>
#include <dmusicc.h>
#include <dmusici.h>
#include <dxerr9.h>
#include <tchar.h>
#include "resource.h"
#include "DMUtil.h"
#include "DXUtil.h"




//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT OnInitDialog( HWND hDlg );
HRESULT ProcessDirectMusicMessages( HWND hDlg );
VOID    OnOpenSoundFile( HWND hDlg, BOOL bLoadFirstSegment );
HRESULT LoadSegmentFile( HWND hDlg, TCHAR* strFileName, BOOL bLoadFirstSegment );
HRESULT OnPlay( HWND hDlg );
HRESULT OnCrossFade( HWND hDlg );
HRESULT Ramp(int nPath, REFERENCE_TIME rtStart, bool fRampUp, MUSIC_TIME mtDuration);
VOID    EnablePlayUI( HWND hDlg, BOOL bEnable );




//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
const BYTE MIDI_CC_VOLUME = 0x07;               // 7 is the MIDI volume controller
const BYTE MIDI_MIN_VOL   = 0x00;               // 0 maps to -96 db
const BYTE MIDI_MAX_VOL   = 0x7F;               // 127 maps to 0 db

CMusicManager*     g_pMusicManager          = NULL;
CMusicSegment*     g_pMusicSegment1         = NULL;
CMusicSegment*     g_pMusicSegment2         = NULL;
IDirectMusicAudioPath8* g_pPath[2]          = {NULL};            // Two audio paths: one per sound
IDirectMusicGraph8*     g_pGraphs[2]        = {NULL};            // The graph of each audio path
HINSTANCE          g_hInst                  = NULL;
int                g_nActivePath            = 0;




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------
INT APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, 
                      INT nCmdShow )
{
    HWND    hDlg = NULL;
    MSG     msg;

    g_hInst = hInst;

    InitCommonControls();

    // Display the main dialog box.
    hDlg = CreateDialog( hInst, MAKEINTRESOURCE(IDD_MAIN), 
                         NULL, MainDlgProc );

    while( GetMessage( &msg, NULL, 0, 0 ) ) 
    { 
        if( !IsDialogMessage( hDlg, &msg ) )  
        {
            TranslateMessage( &msg ); 
            DispatchMessage( &msg ); 
        }
    }

    DestroyWindow( hDlg );

    return 0;
}




//-----------------------------------------------------------------------------
// Name: MainDlgProc()
// Desc: Handles dialog messages
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    HRESULT hr;

    switch( msg ) 
    {
        case WM_INITDIALOG:
            if( FAILED( hr = OnInitDialog( hDlg ) ) )
            {
                DXTRACE_ERR_MSGBOX( TEXT("OnInitDialog"), hr );
                MessageBox( hDlg, "Error initializing DirectMusic.  Sample will now exit.", 
                                  "DirectMusic Sample", MB_OK | MB_ICONERROR );
                EndDialog( hDlg, 0 );
                return TRUE;
            }
            break;

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDC_SOUNDFILE:
                    OnOpenSoundFile( hDlg, TRUE );
                    break;

                case IDC_SOUNDFILE2:
                    OnOpenSoundFile( hDlg, FALSE );
                    break;

                case IDCANCEL:
                    PostQuitMessage( IDCANCEL );
                    break;

                case IDC_PLAY:
                    if( FAILED( hr = OnPlay( hDlg ) ) )
                    {
                        DXTRACE_ERR_MSGBOX( TEXT("OnPlay"), hr );
                        MessageBox( hDlg, "Error playing DirectMusic segment. "
                                    "Sample will now exit.", "DirectMusic Sample", 
                                    MB_OK | MB_ICONERROR );
                        PostQuitMessage( IDABORT );
                    }
                    break;

                case IDC_CROSSFADE:
                    if( FAILED( hr = OnCrossFade( hDlg ) ) )
                    {
                        DXTRACE_ERR_MSGBOX( TEXT("OnCrossFade"), hr );
                        MessageBox( hDlg, "Error crossfading DirectMusic segments. "
                                    "Sample will now exit.", "DirectMusic Sample", 
                                    MB_OK | MB_ICONERROR );
                        PostQuitMessage( IDABORT );
                    }
                    break;

                case IDC_STOP:
                    // Simply calling Stop() on the segment won't stop any MIDI 
                    // sustain pedals, but calling StopAll() will.
                    if( g_pMusicManager )
                        g_pMusicManager->StopAll(); 
                    EnablePlayUI( hDlg, TRUE );
                    break;

                case IDHELP:
                    DXUtil_LaunchReadme( hDlg );
                    break;

                default:
                    return FALSE; // Didn't handle message
            }
            break;

        case WM_DESTROY:
            // Cleanup everything
            SAFE_DELETE( g_pMusicSegment1 );
            SAFE_DELETE( g_pMusicSegment2 );
            SAFE_DELETE( g_pMusicManager );
            break; 

        default:
            return FALSE; // Didn't handle message
    }

    return TRUE; // Handled message
}




//-----------------------------------------------------------------------------
// Name: OnInitDialog()
// Desc: Initializes the dialogs (sets up UI controls, etc.)
//-----------------------------------------------------------------------------
HRESULT OnInitDialog( HWND hDlg )
{
    HRESULT hr; 

    // Load the icon
    HICON hIcon = LoadIcon( g_hInst, MAKEINTRESOURCE( IDR_MAINFRAME ) );

    // Set the icon for this dialog.
    SendMessage( hDlg, WM_SETICON, ICON_BIG,   (LPARAM) hIcon );  // Set big icon
    SendMessage( hDlg, WM_SETICON, ICON_SMALL, (LPARAM) hIcon );  // Set small icon

    g_pMusicManager = new CMusicManager();
    if( NULL == g_pMusicManager )
        return E_OUTOFMEMORY;

    if( FAILED( hr = g_pMusicManager->Initialize( hDlg, 0, 0, NULL ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Initialize"), hr );

    IDirectMusicPerformance8* pPerformance = g_pMusicManager->GetPerformance();
    for (int i = 0; i < 2; i++)
    {
        // Create a standard stereo audio path with 16 pchannels.
        //
        hr = pPerformance->CreateStandardAudioPath( DMUS_APATH_DYNAMIC_STEREO, 
                                                    16, true, 
                                                    &g_pPath[i] );
        if( FAILED(hr) ) 
            return DXTRACE_ERR_MSGBOX( TEXT("CreateStandardAudioPath"), hr );
            
        // Get the audio path's graph. The graph is an object in the audio path
        // which routes performance messages. We'll use a performance message (PMSG)
        // to tell the audio path to ramp up or down in volume later.
        // 
        hr = g_pPath[i]->GetObjectInPath(
                                0,
                                DMUS_PATH_AUDIOPATH,
                                0,                          // Index of buffer
                                GUID_NULL,                  // guidObject
                                0,                          // dwIndex
                                IID_IDirectMusicGraph8,
                                (LPVOID*)&g_pGraphs[i] );
        if( FAILED(hr) ) 
            return DXTRACE_ERR_MSGBOX( TEXT("GetObjectInPath"), hr );
    }

    // Load a default music segment 
    TCHAR strFileName[MAX_PATH];
    DXUtil_GetDXSDKMediaPathCb( strFileName, sizeof(strFileName) );
    strcat( strFileName, "sound1.wav" );
    if( S_FALSE == LoadSegmentFile( hDlg, strFileName, TRUE ) )
    {
        // Set the UI controls
        SetDlgItemText( hDlg, IDC_FILENAME, TEXT("No file loaded.") );
    }

    DXUtil_GetDXSDKMediaPathCb( strFileName, sizeof(strFileName) );
    strcat( strFileName, "sound2.wav" );
    if( S_FALSE == LoadSegmentFile( hDlg, strFileName, FALSE ) )
    {
        // Set the UI controls
        SetDlgItemText( hDlg, IDC_FILENAME2, TEXT("No file loaded.") );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: OnOpenSoundFile()
// Desc: Called when the user requests to open a sound file
//-----------------------------------------------------------------------------
VOID OnOpenSoundFile( HWND hDlg, BOOL bLoadFirstSegment ) 
{
    static TCHAR strFileName[MAX_PATH] = TEXT("");
    static TCHAR strPath[MAX_PATH] = TEXT("");
    int nFileID;
    if( bLoadFirstSegment )
        nFileID = IDC_FILENAME;
    else
        nFileID = IDC_FILENAME2;

    // Get the default media path (something like C:\MSSDK\SAMPLES\DMUSIC\MEDIA)
    if( '\0' == strPath[0] )
    {
        DXUtil_GetDXSDKMediaPathCb( strPath, sizeof(strPath) );
    }

    // Setup the OPENFILENAME structure
    OPENFILENAME ofn = { sizeof(OPENFILENAME), hDlg, NULL,
                         TEXT("Wave Files\0*.wav\0All Files\0*.*\0\0"), NULL,
                         0, 1, strFileName, MAX_PATH, NULL, 0, strPath,
                         TEXT("Open Wave File"),
                         OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, 0, 0,
                         TEXT(".sgt"), 0, NULL, NULL };
   
    // Simply calling Stop() on the segment won't stop any MIDI 
    // sustain pedals, but calling StopAll() will.
    if( g_pMusicManager )
        g_pMusicManager->StopAll(); 

    // Update the UI controls to show the sound as loading a file
    EnableWindow(  GetDlgItem( hDlg, IDC_PLAY ), FALSE);
    EnableWindow(  GetDlgItem( hDlg, IDC_STOP ), FALSE);
    SetDlgItemText( hDlg, nFileID, TEXT("Loading file...") );

    // Display the OpenFileName dialog. Then, try to load the specified file
    if( TRUE != GetOpenFileName( &ofn ) )
    {
        SetDlgItemText( hDlg, nFileID, TEXT("Load aborted.") );
        if( bLoadFirstSegment )
        {
            SAFE_DELETE( g_pMusicSegment1 );
        }
        else
        {
            SAFE_DELETE( g_pMusicSegment2 );
        }
        return;
    }

    if( S_FALSE == LoadSegmentFile( hDlg, strFileName, bLoadFirstSegment ) )
    {
        // Not a critical failure, so just update the status
        SetDlgItemText( hDlg, nFileID, TEXT("Could not create segment from file.") );
    }

    // Remember the path for next time
    strcpy( strPath, strFileName );
    char* strLastSlash = strrchr( strPath, '\\' );
    if( strLastSlash )
        strLastSlash[0] = '\0';
}




//-----------------------------------------------------------------------------
// Name: LoadSegmentFile()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT LoadSegmentFile( HWND hDlg, TCHAR* strFileName, BOOL bLoadFirstSegment )
{
    HRESULT hr;

    if( bLoadFirstSegment )
        SetDlgItemText( hDlg, IDC_FILENAME, TEXT("") );
    else
        SetDlgItemText( hDlg, IDC_FILENAME2, TEXT("") );

    // Free any previous segment, and make a new one
    if( bLoadFirstSegment )
    {
        SAFE_DELETE( g_pMusicSegment1 );
    }
    else
    {
        SAFE_DELETE( g_pMusicSegment2 );
    }

    // Have the loader collect any garbage now that the old 
    // segment has been released
    g_pMusicManager->CollectGarbage();

    // Set the media path based on the file name (something like C:\MEDIA)
    // to be used as the search directory for finding DirectMusic content
    // related to this file.
    TCHAR strMediaPath[MAX_PATH];
    _tcsncpy( strMediaPath, strFileName, MAX_PATH );
    strMediaPath[MAX_PATH-1] = 0;
    TCHAR* strLastSlash = _tcsrchr(strMediaPath, TEXT('\\'));
    if( strLastSlash )
    {
        *strLastSlash = 0;
        if( FAILED( hr = g_pMusicManager->SetSearchDirectory( strMediaPath ) ) )
            return DXTRACE_ERR_MSGBOX( TEXT("SetSearchDirectory"), hr );
    }

    // Load the file into a DirectMusic segment 
    if( bLoadFirstSegment )
    {
        if( FAILED( g_pMusicManager->CreateSegmentFromFile( &g_pMusicSegment1, strFileName, 
                                                            TRUE, FALSE ) ) )
        {
            // Not a critical failure, so just update the status
            return S_FALSE; 
        }

        // Update the UI controls to show the segment is loaded
        SetDlgItemText( hDlg, IDC_FILENAME, strFileName );
    }
    else
    {
        if( FAILED( g_pMusicManager->CreateSegmentFromFile( &g_pMusicSegment2, strFileName, 
                                                            TRUE, FALSE ) ) )
        {
            // Not a critical failure, so just update the status
            return S_FALSE; 
        }

        // Update the UI controls to show the segment is loaded
        SetDlgItemText( hDlg, IDC_FILENAME2, strFileName );
    }

    if( NULL != g_pMusicSegment1 &&
        NULL != g_pMusicSegment2 )
    {
        EnablePlayUI( hDlg, TRUE );
    }
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: OnPlay()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT OnPlay( HWND hDlg )
{
    HRESULT hr;

    // Set the segment to repeat forever 
    if( FAILED( hr = g_pMusicSegment1->SetRepeats( DMUS_SEG_REPEAT_INFINITE ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("SetRepeats"), hr );
    if( FAILED( hr = g_pMusicSegment2->SetRepeats( DMUS_SEG_REPEAT_INFINITE ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("SetRepeats"), hr );

    // We always start with path 0.
    g_nActivePath = 0;

    // Set the initial ramps. path 0 is playing, path 1 is muted.
    Ramp(0, 0, true, 1);
    Ramp(1, 0, false, 1);

    // Play the segments
    if( FAILED( hr = g_pMusicSegment1->Play( DMUS_SEGF_SECONDARY, g_pPath[0] ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Play"), hr );
    if( FAILED( hr = g_pMusicSegment2->Play( DMUS_SEGF_SECONDARY, g_pPath[1] ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Play"), hr );

    EnablePlayUI( hDlg, FALSE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Ramp
// Desc: 
// This is the interesting function. Here we send a PMSG to the audio path's 
// graph to tell it to ramp the volume. A curve can set many other things
// (pan, pitch bend, etc.); here we're just using it to do a smooth volume
// fade.
//
// The IDirectMusicAudioPath8::SetVolume call lets us set the volume on the 
// audio path, but it doesn't give any control over scheduling the curve. 
// By using a PMSG, we can put the starting point of the ramp slightly in 
// the future and make sure ramping of both audio paths happen at exactly the
// same time.
//-----------------------------------------------------------------------------
HRESULT Ramp(int nPath, REFERENCE_TIME rtStart, bool fRampUp, MUSIC_TIME mtDuration)
{
    HRESULT hr = S_OK;
    DMUS_CURVE_PMSG *pCurve;

    IDirectMusicPerformance8* pPerformance = g_pMusicManager->GetPerformance();

    hr = pPerformance->AllocPMsg(sizeof(DMUS_CURVE_PMSG), (DMUS_PMSG**)&pCurve);
    if( FAILED(hr) )
        return DXTRACE_ERR_MSGBOX( TEXT("AllocPMsg"), hr );

    // Set up the curve parameters.
    //
    pCurve->rtTime              = rtStart;
    pCurve->dwFlags             = DMUS_PMSGF_REFTIME | DMUS_PMSGF_LOCKTOREFTIME;
    pCurve->dwPChannel          = DMUS_PCHANNEL_BROADCAST_AUDIOPATH;
    pCurve->dwVirtualTrackID    = 0;
    pCurve->dwType              = DMUS_PMSGT_CURVE;
    pCurve->dwVoiceID           = 0;
    pCurve->dwGroupID           = 0xFFFFFFFF;
    pCurve->punkUser            = NULL;

    pCurve->mtDuration          = mtDuration;
    pCurve->mtOriginalStart     = 0;
    pCurve->nStartValue         = 0;
    pCurve->nEndValue           = fRampUp ? MIDI_MAX_VOL : MIDI_MIN_VOL;
    pCurve->wMeasure            = 0;
    pCurve->bType               = DMUS_CURVET_CCCURVE;
    pCurve->bCurveShape         = DMUS_CURVES_SINE;
    pCurve->bCCData             = MIDI_CC_VOLUME;
    pCurve->bFlags              = DMUS_CURVE_START_FROM_CURRENT;

    // StampPMsg tells the PMSG where it should go when it gets sent.
    // Here we're indicating the graph belonging to one of our audio paths.
    //
    g_pGraphs[nPath]->StampPMsg((DMUS_PMSG*)pCurve);

    // Once SendPMsg succeeds, we know longer own the PMSG and aren't allowed
    // to touch it anymore. The system is responsible for free'ing it when processing
    // is complete. If the send fails, we are responsible for cleaning up.
    //
    hr = pPerformance->SendPMsg((DMUS_PMSG*)pCurve);
    if (FAILED(hr))
    {
        pPerformance->FreePMsg((DMUS_PMSG*)pCurve);
        return DXTRACE_ERR_MSGBOX( TEXT("SendPMsg"), hr );
    }
    
    return hr;
}




//-----------------------------------------------------------------------------
// Name: OnCrossFade()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT OnCrossFade( HWND hDlg )
{
    HRESULT hr;
    REFERENCE_TIME rtPlay = 0;

    // We want to make sure the ramp requests play on time and not late
    // so they'll be synchronized. So we're going to schedule them 15 
    // milliseconds after the current latency time.
    IDirectMusicPerformance8* pPerformance = g_pMusicManager->GetPerformance();
    hr = pPerformance->GetLatencyTime(&rtPlay);   
    if( FAILED(hr) )
        return DXTRACE_ERR_MSGBOX( TEXT("GetLatencyTime"), hr );

    // Convert time from milliseconds to reference time, which
    // is in 100 nanosecond units.
    rtPlay += (15 * (REFERENCE_TIME)(10 * 1000));

    // Ramp the muted path up. 1536 music time quanta is one second;
    // 3840 is 2.5sec, so this lets us hear the crossfade.
    Ramp(1 - g_nActivePath, rtPlay, true, 3840);            

    // Ramp the playing path down.
    Ramp(g_nActivePath, rtPlay, false, 3840);

    // We're now hearing (or about to hear, in a few milliseconds) the 
    // other path.
    g_nActivePath = 1 - g_nActivePath;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: EnablePlayUI( hDlg,)
// Desc: Enables or disables the Play UI controls 
//-----------------------------------------------------------------------------
VOID EnablePlayUI( HWND hDlg, BOOL bEnable )
{
    if( bEnable )
    {
        EnableWindow(   GetDlgItem( hDlg, IDC_STOP ),       FALSE );
        EnableWindow(  GetDlgItem( hDlg, IDC_CROSSFADE ),   FALSE );
        EnableWindow(   GetDlgItem( hDlg, IDC_PLAY ),       TRUE );
        SetFocus(       GetDlgItem( hDlg, IDC_PLAY ) );
    }
    else
    {
        EnableWindow(  GetDlgItem( hDlg, IDC_STOP ),       TRUE );
        EnableWindow(  GetDlgItem( hDlg, IDC_CROSSFADE ),  TRUE );
        SetFocus(      GetDlgItem( hDlg, IDC_STOP ) );
        EnableWindow(  GetDlgItem( hDlg, IDC_PLAY ),       FALSE );
    }
}



