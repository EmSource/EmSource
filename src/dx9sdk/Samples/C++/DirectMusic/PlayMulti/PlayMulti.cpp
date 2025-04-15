//-----------------------------------------------------------------------------
// File: PlayMulti.cpp
//
// Desc: 
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
VOID    OnOpenSoundFile( HWND hDlg, int nSegNumber );
HRESULT LoadSegmentFile( HWND hDlg, TCHAR* strFileName, int nSegNumber );
HRESULT OnPlay( HWND hDlg, int nSegNumber );
HRESULT Ramp(int nPath, REFERENCE_TIME rtStart, bool fRampUp, MUSIC_TIME mtDuration);
VOID    EnablePlayUI( HWND hDlg, BOOL bEnable, int nSegNumber );




//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
CMusicManager*     g_pMusicManager          = NULL;
CMusicSegment*     g_pMusicSegment1         = NULL;
CMusicSegment*     g_pMusicSegment2         = NULL;
CMusicSegment*     g_pMusicSegment3         = NULL;
HINSTANCE          g_hInst                  = NULL;
HANDLE             g_hDMusicMessageEvent    = NULL;




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point for the application.  Since we use a simple dialog for 
//       user interaction we don't need to pump messages.
//-----------------------------------------------------------------------------
INT APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, 
                      INT nCmdShow )
{
    HWND    hDlg = NULL;
    BOOL    bDone = FALSE;
    int     nExitCode = 0;
    HRESULT hr; 
    DWORD   dwResult;
    MSG     msg;

    g_hInst = hInst;

    InitCommonControls();

    // Display the main dialog box.
    hDlg = CreateDialog( hInst, MAKEINTRESOURCE(IDD_MAIN), 
                         NULL, MainDlgProc );

    while( !bDone ) 
    { 
        dwResult = MsgWaitForMultipleObjects( 1, &g_hDMusicMessageEvent, 
                                              FALSE, INFINITE, QS_ALLEVENTS );
        switch( dwResult )
        {
            case WAIT_OBJECT_0 + 0:
                // g_hDPMessageEvent is signaled, so there are
                // DirectPlay messages available
                if( FAILED( hr = ProcessDirectMusicMessages( hDlg ) ) ) 
                {
                    DXTRACE_ERR_MSGBOX( TEXT("ProcessDirectMusicMessages"), hr );
                    return FALSE;
                }
                break;

            case WAIT_OBJECT_0 + 1:
                // Windows messages are available
                while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
                { 
                    if( !IsDialogMessage( hDlg, &msg ) )  
                    {
                        TranslateMessage( &msg ); 
                        DispatchMessage( &msg ); 
                    }

                    if( msg.message == WM_QUIT )
                    {
                        nExitCode = (int)msg.wParam;
                        bDone     = TRUE;
                        DestroyWindow( hDlg );
                    }
                }
                break;
        }
    }

    return nExitCode;
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
                case IDC_SOUNDFILE1:
                case IDC_SOUNDFILE2:
                case IDC_SOUNDFILE3:
                    OnOpenSoundFile( hDlg, LOWORD(wParam) - IDC_SOUNDFILE1 + 1 );
                    break;

                case IDCANCEL:
                    PostQuitMessage( IDCANCEL );
                    break;

                case IDC_PLAY1:
                case IDC_PLAY2:
                case IDC_PLAY3:
                    if( FAILED( hr = OnPlay( hDlg, LOWORD(wParam) - IDC_PLAY1 + 1 ) ) )
                    {
                        DXTRACE_ERR_MSGBOX( TEXT("OnPlay"), hr );
                        MessageBox( hDlg, "Error playing DirectMusic segment. "
                                    "Sample will now exit.", "DirectMusic Sample", 
                                    MB_OK | MB_ICONERROR );
                        PostQuitMessage( IDABORT );
                    }
                    break;

                case IDC_STOPALL:
                    // Simply calling Stop() on the segment won't stop any MIDI 
                    // sustain pedals, but calling StopAll() will.
                    if( g_pMusicManager )
                        g_pMusicManager->StopAll(); 
                    EnablePlayUI( hDlg, TRUE, 1 );
                    EnablePlayUI( hDlg, TRUE, 2 );
                    EnablePlayUI( hDlg, TRUE, 3 );
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
            SAFE_DELETE( g_pMusicSegment3 );
            SAFE_DELETE( g_pMusicManager );
            CloseHandle( g_hDMusicMessageEvent );
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

    g_hDMusicMessageEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    g_pMusicManager = new CMusicManager();
    if( NULL == g_pMusicManager )
        return E_OUTOFMEMORY;

    if( FAILED( hr = g_pMusicManager->Initialize( hDlg ) ) )
        return DXTRACE_ERR_MSGBOX( TEXT("Initialize"), hr );

    // Register segment notification
    IDirectMusicPerformance* pPerf = g_pMusicManager->GetPerformance();
    GUID guid = GUID_NOTIFICATION_SEGMENT;
    pPerf->AddNotificationType( guid );
    pPerf->SetNotificationHandle( g_hDMusicMessageEvent, 0 );  

    // Load a default music segment 
    TCHAR strFileName[MAX_PATH];
    DXUtil_GetDXSDKMediaPathCb( strFileName, sizeof(strFileName) );
    strcat( strFileName, "audiopath1.sgt" );
    if( S_FALSE == LoadSegmentFile( hDlg, strFileName, 1 ) )
    {
        // Set the UI controls
        SetDlgItemText( hDlg, IDC_FILENAME1, TEXT("No file loaded.") );
        EnableWindow( GetDlgItem( hDlg, IDC_PLAY1 ), FALSE);        
    }

    DXUtil_GetDXSDKMediaPathCb( strFileName, sizeof(strFileName) );
    strcat( strFileName, "audiopath2.sgt" );
    if( S_FALSE == LoadSegmentFile( hDlg, strFileName, 2 ) )
    {
        // Set the UI controls
        SetDlgItemText( hDlg, IDC_FILENAME2, TEXT("No file loaded.") );
        EnableWindow( GetDlgItem( hDlg, IDC_PLAY2 ), FALSE);        
    }

    DXUtil_GetDXSDKMediaPathCb( strFileName, sizeof(strFileName) );
    strcat( strFileName, "audiopath4.sgt" );
    if( S_FALSE == LoadSegmentFile( hDlg, strFileName, 3 ) )
    {
        // Set the UI controls
        SetDlgItemText( hDlg, IDC_FILENAME3, TEXT("No file loaded.") );
        EnableWindow( GetDlgItem( hDlg, IDC_PLAY3 ), FALSE);        
    }

    CheckDlgButton( hDlg, IDC_LOOPED1, BST_CHECKED );
    CheckDlgButton( hDlg, IDC_LOOPED2, BST_CHECKED );
    CheckDlgButton( hDlg, IDC_LOOPED3, BST_CHECKED );

    CheckRadioButton( hDlg, IDC_RADIO_DEFAULT2, IDC_RADIO_MEASURE2, IDC_RADIO_DEFAULT2 );
    CheckRadioButton( hDlg, IDC_RADIO_DEFAULT3, IDC_RADIO_MEASURE3, IDC_RADIO_DEFAULT3 );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: OnOpenSoundFile()
// Desc: Called when the user requests to open a sound file
//-----------------------------------------------------------------------------
VOID OnOpenSoundFile( HWND hDlg, int nSegNumber ) 
{
    static TCHAR strFileName[MAX_PATH] = TEXT("");
    static TCHAR strPath[MAX_PATH] = TEXT("");
    int nFileID = IDC_FILENAME1;
    int nPlayID = IDC_PLAY1;

    switch( nSegNumber )
    {
        case 1: nFileID = IDC_FILENAME1; nPlayID = IDC_PLAY1; break;
        case 2: nFileID = IDC_FILENAME2; nPlayID = IDC_PLAY2; break;
        case 3: nFileID = IDC_FILENAME3; nPlayID = IDC_PLAY3; break;
    }

    // Get the default media path (something like C:\MSSDK\SAMPLES\DMUSIC\MEDIA)
    if( '\0' == strPath[0] )
    {
        DXUtil_GetDXSDKMediaPathCb( strPath, sizeof(strPath) );
    }

    // Setup the OPENFILENAME structure
    OPENFILENAME ofn = { sizeof(OPENFILENAME), hDlg, NULL,
                         TEXT("Audio Files\0*.sgt;*.mid;*.rmi;*.wav\0DirectMusic Content Files\0*.sgt;*.mid;*.rmi\0Wave Files\0*.wav\0All Files\0*.*\0\0"), NULL,
                         0, 1, strFileName, MAX_PATH, NULL, 0, strPath,
                         TEXT("Open Audio File"),
                         OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, 0, 0,
                         TEXT(".sgt"), 0, NULL, NULL };
   
    // Simply calling Stop() on the segment won't stop any MIDI 
    // sustain pedals, but calling StopAll() will.
    if( g_pMusicManager )
        g_pMusicManager->StopAll(); 
    EnablePlayUI( hDlg, TRUE, 1 );
    EnablePlayUI( hDlg, TRUE, 2 );
    EnablePlayUI( hDlg, TRUE, 3 );

    // Update the UI controls to show the sound as loading a file
    EnableWindow(  GetDlgItem( hDlg, nPlayID ), FALSE);
    SetDlgItemText( hDlg, nFileID, TEXT("Loading file...") );

    // Display the OpenFileName dialog. Then, try to load the specified file
    if( TRUE != GetOpenFileName( &ofn ) )
    {
        SetDlgItemText( hDlg, nFileID, TEXT("Load aborted.") );
        switch( nSegNumber )
        {
            case 1: SAFE_DELETE( g_pMusicSegment1 ); break;
            case 2: SAFE_DELETE( g_pMusicSegment2 ); break;
            case 3: SAFE_DELETE( g_pMusicSegment3 ); break;
        }
        return;
    }

    if( S_FALSE == LoadSegmentFile( hDlg, strFileName, nSegNumber ) )
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
HRESULT LoadSegmentFile( HWND hDlg, TCHAR* strFileName, int nSegNumber )
{
    HRESULT hr;
    int nFileID = IDC_FILENAME1;
    CMusicSegment** ppSeg = NULL;

    switch( nSegNumber )
    {
        case 1: nFileID = IDC_FILENAME1; ppSeg = &g_pMusicSegment1; break;
        case 2: nFileID = IDC_FILENAME2; ppSeg = &g_pMusicSegment2; break;
        case 3: nFileID = IDC_FILENAME3; ppSeg = &g_pMusicSegment3; break;
    }

    SetDlgItemText( hDlg, nFileID, TEXT("") );

    // Free any previous segment, and make a new one
    switch( nSegNumber )
    {
        case 1: SAFE_DELETE( g_pMusicSegment1 ); break;
        case 2: SAFE_DELETE( g_pMusicSegment2 ); break;
        case 3: SAFE_DELETE( g_pMusicSegment3 ); break;
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
    switch( nSegNumber )
    {
        case 1: SAFE_DELETE( g_pMusicSegment1 ); break;
        case 2: SAFE_DELETE( g_pMusicSegment2 ); break;
        case 3: SAFE_DELETE( g_pMusicSegment3 ); break;
    }

    if( FAILED( g_pMusicManager->CreateSegmentFromFile( ppSeg, strFileName, 
                                                        TRUE, FALSE ) ) )
    {
        // Not a critical failure, so just update the status
        return S_FALSE; 
    }

    // Update the UI controls to show the segment is loaded
    SetDlgItemText( hDlg, nFileID, strFileName );

    EnablePlayUI( hDlg, TRUE, nSegNumber );
    
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: OnPlay()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT OnPlay( HWND hDlg, int nSegNumber )
{
    HRESULT hr;
    CMusicSegment** ppSeg = NULL;
    int nLoopID = IDC_LOOPED1;
    DWORD dwPlayFlags = 0;

    switch( nSegNumber )
    {
        case 1: dwPlayFlags = 0;                   ppSeg = &g_pMusicSegment1; nLoopID = IDC_LOOPED1; break;
        case 2: dwPlayFlags = DMUS_SEGF_SECONDARY; ppSeg = &g_pMusicSegment2; nLoopID = IDC_LOOPED2; break;
        case 3: dwPlayFlags = DMUS_SEGF_SECONDARY; ppSeg = &g_pMusicSegment3; nLoopID = IDC_LOOPED3; break;
    }

    if( *ppSeg == NULL )
        return S_OK;

    if( (*ppSeg)->IsPlaying() )
    {
        // Stop the segment.  This does not stop any MIDI 
        // sustain pedals, but calling StopAll() will.
        if( FAILED( hr = (*ppSeg)->Stop() ) )
            return DXTRACE_ERR_MSGBOX( TEXT("Stop"), hr );

        EnablePlayUI( hDlg, TRUE, nSegNumber );
    }
    else
    {
        BOOL bLooped = ( SendMessage( GetDlgItem( hDlg, nLoopID ), BM_GETSTATE, 0, 0 ) == BST_CHECKED );

        switch( nSegNumber )
        {
            case 2: 
                if( IsDlgButtonChecked( hDlg, IDC_CONTROL2 ) )
                    dwPlayFlags |= DMUS_SEGF_CONTROL;

                if( IsDlgButtonChecked( hDlg, IDC_RADIO_DEFAULT2 ) )
                    dwPlayFlags |= DMUS_SEGF_DEFAULT;
                else if( IsDlgButtonChecked( hDlg, IDC_RADIO_IMMEDIATE2 ) )
                    dwPlayFlags |= 0;
                else if( IsDlgButtonChecked( hDlg, IDC_RADIO_GRID2 ) )
                    dwPlayFlags |= DMUS_SEGF_GRID;
                else if( IsDlgButtonChecked( hDlg, IDC_RADIO_BEAT2 ) )
                    dwPlayFlags |= DMUS_SEGF_BEAT;
                else if( IsDlgButtonChecked( hDlg, IDC_RADIO_MEASURE2 ) )
                    dwPlayFlags |= DMUS_SEGF_MEASURE;
                break;
            case 3: 
                if( IsDlgButtonChecked( hDlg, IDC_CONTROL3 ) )
                    dwPlayFlags |= DMUS_SEGF_CONTROL;

                if( IsDlgButtonChecked( hDlg, IDC_RADIO_DEFAULT3 ) )
                    dwPlayFlags |= DMUS_SEGF_DEFAULT;
                else if( IsDlgButtonChecked( hDlg, IDC_RADIO_IMMEDIATE3 ) )
                    dwPlayFlags |= 0;
                else if( IsDlgButtonChecked( hDlg, IDC_RADIO_GRID3 ) )
                    dwPlayFlags |= DMUS_SEGF_GRID;
                else if( IsDlgButtonChecked( hDlg, IDC_RADIO_BEAT3 ) )
                    dwPlayFlags |= DMUS_SEGF_BEAT;
                else if( IsDlgButtonChecked( hDlg, IDC_RADIO_MEASURE3 ) )
                    dwPlayFlags |= DMUS_SEGF_MEASURE;
                break;
        }

        if( bLooped )
        {
            // Set the segment to repeat many times
            if( FAILED( hr = (*ppSeg)->SetRepeats( DMUS_SEG_REPEAT_INFINITE ) ) )
                return DXTRACE_ERR_MSGBOX( TEXT("SetRepeats"), hr );
        }
        else
        {
            // Set the segment to not repeat
            if( FAILED( hr = (*ppSeg)->SetRepeats( 0 ) ) )
                return DXTRACE_ERR_MSGBOX( TEXT("SetRepeats"), hr );
        }

        // Play the segment 
        if( FAILED( hr = (*ppSeg)->Play( dwPlayFlags ) ) )
            return DXTRACE_ERR_MSGBOX( TEXT("Play"), hr );

        EnablePlayUI( hDlg, FALSE, nSegNumber );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: EnablePlayUI( hDlg,)
// Desc: Enables or disables the Play UI controls 
//-----------------------------------------------------------------------------
VOID EnablePlayUI( HWND hDlg, BOOL bEnable, int nSegNumber )
{
    int nPlayID = IDC_PLAY1;
    CMusicSegment** ppSeg = NULL;

    switch( nSegNumber )
    {
        case 1: nPlayID = IDC_PLAY1; ppSeg = &g_pMusicSegment1; break;
        case 2: nPlayID = IDC_PLAY2; ppSeg = &g_pMusicSegment2; break;
        case 3: nPlayID = IDC_PLAY3; ppSeg = &g_pMusicSegment3; break;
    }

    if( *ppSeg )
        EnableWindow( GetDlgItem( hDlg, nPlayID ), TRUE );
    else
        EnableWindow( GetDlgItem( hDlg, nPlayID ), FALSE );

    if( bEnable )
    {
        SetWindowText( GetDlgItem( hDlg, nPlayID ), TEXT("Play" ) );
    }
    else
    {
        SetWindowText( GetDlgItem( hDlg, nPlayID ), TEXT("Stop" ) );
    }
}



//-----------------------------------------------------------------------------
// Name: ProcessDirectMusicMessages()
// Desc: Handle DirectMusic notification messages
//-----------------------------------------------------------------------------
HRESULT ProcessDirectMusicMessages( HWND hDlg )
{
    HRESULT hr;
    IDirectMusicPerformance8* pPerf = NULL;
    DMUS_NOTIFICATION_PMSG* pPMsg;
        
    if( NULL == g_pMusicManager )
        return S_OK;

    pPerf = g_pMusicManager->GetPerformance();

    // Get waiting notification message from the performance
    while( S_OK == pPerf->GetNotificationPMsg( &pPMsg ) )
    {
        switch( pPMsg->dwNotificationOption )
        {
        case DMUS_NOTIFICATION_SEGEND:
            if( pPMsg->punkUser )
            {
                IDirectMusicSegmentState8* pSegmentState   = NULL;
                IDirectMusicSegment*       pNotifySegment   = NULL;
                IDirectMusicSegment8*      pNotifySegment8  = NULL;
                IDirectMusicSegment8*      pPrimarySegment1 = NULL;
                IDirectMusicSegment8*      pPrimarySegment2 = NULL;
                IDirectMusicSegment8*      pPrimarySegment3 = NULL;

                // The pPMsg->punkUser contains a IDirectMusicSegmentState8, 
                // which we can query for the segment that the SegmentState refers to.
                if( FAILED( hr = pPMsg->punkUser->QueryInterface( IID_IDirectMusicSegmentState8,
                                                                  (VOID**) &pSegmentState ) ) )
                    return DXTRACE_ERR_MSGBOX( TEXT("QueryInterface"), hr );

                if( FAILED( hr = pSegmentState->GetSegment( &pNotifySegment ) ) )
                {
                    // Sometimes the segend arrives after the segment is gone
                    // This can happen when you load another segment as 
                    // a motif or the segment is ending
                    if( hr == DMUS_E_NOT_FOUND )
                    {
                        SAFE_RELEASE( pSegmentState );
                        return S_OK;
                    }

                    return DXTRACE_ERR_MSGBOX( TEXT("GetSegment"), hr );
                }

                if( FAILED( hr = pNotifySegment->QueryInterface( IID_IDirectMusicSegment8,
                                                                 (VOID**) &pNotifySegment8 ) ) )
                    return DXTRACE_ERR_MSGBOX( TEXT("QueryInterface"), hr );

                // Get the IDirectMusicSegment8 for the primary segment
                if( g_pMusicSegment1 )
                    pPrimarySegment1 = g_pMusicSegment1->GetSegment();
                if( g_pMusicSegment2 )
                    pPrimarySegment2 = g_pMusicSegment2->GetSegment();
                if( g_pMusicSegment3 )
                    pPrimarySegment3 = g_pMusicSegment3->GetSegment();

                // Figure out which segment this is and 
                // update the UI controls to show the sound as stopped
                if( pNotifySegment8 == pPrimarySegment1 )
                    EnablePlayUI( hDlg, TRUE, 1 );
                if( pNotifySegment8 == pPrimarySegment2 )
                    EnablePlayUI( hDlg, TRUE, 2 );
                if( pNotifySegment8 == pPrimarySegment3 )
                    EnablePlayUI( hDlg, TRUE, 3 );

                // Cleanup
                SAFE_RELEASE( pSegmentState );
                SAFE_RELEASE( pNotifySegment );
                SAFE_RELEASE( pNotifySegment8 );
            }
            break;
        }

        pPerf->FreePMsg( (DMUS_PMSG*)pPMsg ); 
    }

    return S_OK;
}



