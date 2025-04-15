//------------------------------------------------------------------------------
// File: DVDHelper.cpp
//
// Desc: DirectShow sample code - event handling code for PlayDVD sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "playdvd.h"
#include <wxdebug.h>

// Global data
ULONG g_ulCurChapter=0, g_ulNumChapters=0;
ULONG g_ulCurTitle=0, g_ulNumTitles=0;    
ULONG g_ulValidUOPS=0;

DVD_HMSF_TIMECODE g_CurTime={0};  // track the current playback time
DVD_DOMAIN g_DVDDomain = DVD_DOMAIN_FirstPlay;
bool g_bStillOn=false, g_bMenuOn=false;

DWORD g_nCurrentSubpicture=(DWORD)-1, g_nCurrentAngle=0, 
      g_nCurrentAudioStream=0, g_nNumChapters=0;


LRESULT OnDvdEvent(LONG lEvent, LONG lParam1, LONG lParam2)
{
    // Field DVD-specific events
    switch(lEvent)
    {
        case EC_DVD_CURRENT_HMSF_TIME:
        {
            DVD_HMSF_TIMECODE * pTC = reinterpret_cast<DVD_HMSF_TIMECODE *>(&lParam1);
            g_CurTime = *pTC;
            // If we have reached the beginning of the movie, perhaps through
            // seeking backward, then reset the rate to 1.0
            if (lParam1 == 0)
                ResetRate();

            UpdateMainTitle();  // Update the current time on the title bar
        }
        break;

        case EC_DVD_CHAPTER_START:
            g_ulCurChapter = lParam1;

            // Indicate the change of chapter
            UpdateChapterCount(g_ulCurTitle);
            UpdateCurrentChapter(g_ulCurChapter);
            break;

        case EC_DVD_TITLE_CHANGE:
            g_ulCurTitle = lParam1;
            ResetRate();

            // Indicate the change of title and refresh the chapter list
            UpdateCurrentTitle(g_ulCurTitle);
            GetAudioInfo();
            UpdateAudioInfo();
            UpdateMainTitle();
            break;

        case EC_DVD_NO_FP_PGC:
            ResetRate();
            PostMessage(ghApp, WM_COMMAND, ID_DVD_STARTMOVIE, 0);
            break;

        case EC_DVD_SUBPICTURE_STREAM_CHANGE:
            // Update the subpicture menu settings (on/off, current language, etc.)
            g_nCurrentSubpicture = lParam1;
            UpdateSubpictureInfo();
            break;

        case EC_DVD_AUDIO_STREAM_CHANGE:
            g_nCurrentAudioStream = lParam1;
            UpdateAudioInfo();
            break;

        case EC_DVD_ANGLE_CHANGE:
            // lParam1 is the number of available angles (1 means no multiangle support)
            // lParam2 is the current angle
            g_nCurrentAngle = lParam2;  
            UpdateAngleInfo();
            break;

        case EC_DVD_ANGLES_AVAILABLE:
            // Read the number of available angles
            GetAngleInfo();
            UpdateAngleInfo();

            // Enable or gray out the angle menu, depending on whether
            // we are in an angle block and angles are available.
            // Zero (0) indicates that playback is not in an angle block 
            // and angles are not available, One (1) indicates that an angle
            // block is being played back and angle changes can be performed. 
            EnableAngleMenu((BOOL) lParam1);
            break;

        case EC_DVD_STILL_ON:
            ResetRate();
            // if there is a still without buttons, we can call StillOff
            if (TRUE == lParam1)    
                g_bStillOn = true;
            break;

        case EC_DVD_STILL_OFF:
            ResetRate();
            g_bStillOn = false;     // we are no longer in a still
            break;

        case EC_DVD_PLAYBACK_STOPPED:
            ResetRate();
            break;

        case EC_DVD_DISC_EJECTED:
            HandleDiscEject();
            break;

        // When the valid UOPS values change, this event is generated.
        // Processing this event and saving the value is more efficient
        // than polling the GetCurrentUOPS() method (and prevents race conditions).
        //
        // This event indicates only which operations are explicitly disabled 
        // by the content on the DVD disc. It does not guarantee that it is 
        // valid to call methods that are not disabled. 
        case EC_DVD_VALID_UOPS_CHANGE:
            g_ulValidUOPS = (ULONG) lParam1;
            break;

        case EC_DVD_DOMAIN_CHANGE:
            switch (lParam1)
            {
                // The DVD started playing outside of the main title
                case DVD_DOMAIN_FirstPlay:  // = 1
                    // Read information about this DVD volume
                    // (audio, angles, subpicture, titles, presentation caps)
                    ReadDVDInformation();

                    // Now that the DVD volume is rendered and has started
                    // playing content, enable the options/navigation menus.
                    EnablePlaybackMenu(TRUE);
                    break;

                case DVD_DOMAIN_Stop:       // = 5
                    break ;
        
                case DVD_DOMAIN_VideoManagerMenu:  // = 2
                case DVD_DOMAIN_VideoTitleSetMenu: // = 3
                    g_bMenuOn = true;       // now menu is "On"

                    // Disable and gray out specific menus
                    EnableOptionsMenus(FALSE);
                    break ;
        
                case DVD_DOMAIN_Title:      // = 4
                    g_bMenuOn = false ;     // we are no longer in a menu

                    // Enable specific menus
                    EnableOptionsMenus(TRUE);

                    // Find out whether this title supports 4x3 PanScan, Letterbox, etc.
                    GetPresentationCaps();
                    break ;
            }

            // Remember the current domain
            g_DVDDomain = (DVD_DOMAIN) lParam1;
            ResetRate();
            break;

        case EC_DVD_ERROR:
            DbgLog((LOG_TRACE, 3, TEXT("DVD Event: Error event received (code %ld)!\0"), lParam1)) ;
            switch (lParam1)
            {
                case DVD_ERROR_Unexpected:
                    MessageBox(ghApp, 
                        TEXT("An unexpected error (possibly incorrectly authored content)")
                        TEXT("\nwas encountered.")
                        TEXT("\n\nCan't playback this DVD-Video disc.\0"),
                        TEXT("Error"), MB_OK | MB_ICONINFORMATION) ;
                    StopDVD();
                    break ;
            
                case DVD_ERROR_CopyProtectFail:
                    MessageBox(ghApp, 
                        TEXT("Key exchange for DVD copy protection failed.")
                        TEXT("\n\nCan't playback this DVD-Video disc.\0"),
                        TEXT("Error"), MB_OK | MB_ICONINFORMATION) ;
                    StopDVD();
                    break ;
            
                case DVD_ERROR_InvalidDVD1_0Disc:
                    MessageBox(ghApp, 
                        TEXT("This DVD-Video disc is incorrectly authored for v1.0  of the spec.")
                        TEXT("\n\nCan't playback this disc.\0"),
                        TEXT("Error"), MB_OK | MB_ICONINFORMATION) ;
                    StopDVD();
                    break ;
            
                case DVD_ERROR_InvalidDiscRegion:
                    MessageBox(ghApp, 
                        TEXT("This DVD-Video disc cannot be played, because it is not")
                        TEXT("\nauthored to play in the current system region.")
                        TEXT("\nThe region mismatch may be fixed by changing the")
                        TEXT("\nsystem region (with DVDRgn.exe).\0"),
                        TEXT("Error"), MB_OK | MB_ICONINFORMATION) ;
                    StopDVD();
                    break ;
            
                case DVD_ERROR_LowParentalLevel:
                    MessageBox(ghApp, 
                        TEXT("Player parental level is set lower than the lowest parental")
                        TEXT("\nlevel available in this DVD-Video content.")
                        TEXT("\n\nCan't playback this DVD-Video disc.\0"),
                        TEXT("Error"), MB_OK | MB_ICONINFORMATION) ;
                    StopDVD();
                    break ;
            
                case DVD_ERROR_MacrovisionFail:
                    MessageBox(ghApp, 
                        TEXT("This DVD-Video content is protected by Macrovision.")
                        TEXT("\nThe system does not satisfy Macrovision requirement.")
                        TEXT("\n\nCan't continue playing this disc.\0"),
                        TEXT("Error"), MB_OK | MB_ICONINFORMATION) ;
                    StopDVD();
                    break ;
            
                case DVD_ERROR_IncompatibleSystemAndDecoderRegions:
                    MessageBox(ghApp, 
                        TEXT("No DVD-Video disc can be played on this system, because ")
                        TEXT("\nthe system region does not match the decoder region.")
                        TEXT("\n\nPlease contact the manufacturer of this system.\0"),
                        TEXT("Error"), MB_OK | MB_ICONINFORMATION) ;
                    StopDVD();
                    break ;
            
                case DVD_ERROR_IncompatibleDiscAndDecoderRegions:
                    MessageBox(ghApp, 
                        TEXT("This DVD-Video disc cannot be played on this system, because it is")
                        TEXT("\nnot authored to be played in the installed decoder's region.\0"),
                        TEXT("Error"), MB_OK | MB_ICONINFORMATION) ;
                    StopDVD();
                    break ;
            }  // end of switch (lParam1)
            break ;
        

        case EC_DVD_WARNING:
            switch (lParam1)
            {
                case DVD_WARNING_InvalidDVD1_0Disc:
                    DbgLog((LOG_ERROR, 1, TEXT("DVD Warning: Current disc is not v1.0 spec compliant"))) ;
                    break ;

                case DVD_WARNING_FormatNotSupported:
                    DbgLog((LOG_ERROR, 1, TEXT("DVD Warning: The decoder does not support the new format."))) ;
                    break ;

                case DVD_WARNING_IllegalNavCommand:
                    DbgLog((LOG_ERROR, 1, TEXT("DVD Warning: An illegal navigation command was encountered."))) ;
                    break ;

                case DVD_WARNING_Open:
                    DbgLog((LOG_ERROR, 1, TEXT("DVD Warning: Could not open a file on the DVD disc."))) ;
                    MessageBox(ghApp, 
                        TEXT("A file on the DVD disc could not be opened.  ")
                        TEXT("Playback may not continue.\0"), 
                        TEXT("Warning"), MB_OK | MB_ICONINFORMATION) ;
                    break ;

                case DVD_WARNING_Seek:
                    DbgLog((LOG_ERROR, 1, TEXT("DVD Warning: Could not seek in a file on the DVD disc."))) ;
                    MessageBox(ghApp, 
                        TEXT("Could not move to a different part of a file on the DVD disc.  ")
                        TEXT("Playback may not continue.\0"), 
                        TEXT("Warning"), MB_OK | MB_ICONINFORMATION) ;
                    break ;

                case DVD_WARNING_Read:
                    DbgLog((LOG_ERROR, 1, TEXT("DVD Warning: Could not read a file on the DVD disc."))) ;
                    MessageBox(ghApp, 
                        TEXT("Could not read part of a file on the DVD disc.  ")
                        TEXT("Playback may not continue.\0"), 
                        TEXT("Warning"), MB_OK | MB_ICONINFORMATION) ;
                    break ;

                default:
                    DbgLog((LOG_ERROR, 1, TEXT("DVD Warning: An unknown warning (%ld) was received."), lParam1)) ;
                    break ;
            }
            break ;

        //
        // Ignore some messages for this sample application
        //
        case EC_DVD_PLAYBACK_RATE_CHANGE:
        case EC_DVD_BUTTON_CHANGE:
        case EC_DVD_PARENTAL_LEVEL_CHANGE:
        case EC_DVD_CHAPTER_AUTOSTOP:
        case EC_DVD_PLAYPERIOD_AUTOSTOP:
            break;

    } // end of switch(lEvent)

    return 0;
}


LRESULT OnMouseEvent(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    HRESULT hr;

    if (!pDvdControl)
        return 0;

    switch (uMessage)
    {
        case WM_MOUSEMOVE:
        {
            POINT pt;
            pt.x = GET_X_LPARAM(lParam); 
            pt.y = GET_Y_LPARAM(lParam); 

            // Select the button at the current position, if it exists
            hr = pDvdControl->SelectAtPosition(pt);
            break;
        }

        case WM_LBUTTONUP:
        {
            POINT pt;
            pt.x = GET_X_LPARAM(lParam); 
            pt.y = GET_Y_LPARAM(lParam); 

            // Highlight the button at the current position, if it exists
            hr = pDvdControl->ActivateAtPosition(pt);
            break;
        }
    }

    return 0;
}


void HandleDVDCommand(WPARAM wParam, LPARAM lParam)
{
    HRESULT hr;
    DWORD dwFlags = DVD_CMD_FLAG_Block | DVD_CMD_FLAG_Flush;

    // Handle DVD-specific commands
    switch (wParam)
    {
        case ID_DVD_SHOWCC:
            ToggleCaptioning();                     // Closed captioning display
            break;

        case ID_DVD_SHOWSUBPICTURE:
            g_bDisplaySubpicture ^= 1;
            EnableSubpicture(g_bDisplaySubpicture); // Subpicture stream display
            break;

        case ID_DVD_NEXTCHAPTER:
            if (pDvdControl)
            {
                hr = pDvdControl->PlayNextChapter(dwFlags, NULL);
                ResetRate();            // Reset playback rate
            }
            break;

        case ID_DVD_PREVIOUSCHAPTER:
            if (pDvdControl)
            {
                hr = pDvdControl->PlayPrevChapter(dwFlags, NULL);
                ResetRate();            // Reset playback rate
            }
            break;

        case ID_DVD_REPLAYCHAPTER:
            if (pDvdControl)
            {
                hr = pDvdControl->ReplayChapter(dwFlags, NULL);
                ResetRate();            // Reset playback rate
            }
            break;

        case ID_DVD_STARTMOVIE:
            if (pDvdControl)            // Play the first title
            {
                hr = pDvdControl->PlayTitle(1, dwFlags, NULL);
                ResetRate();            // Reset playback rate
            }
            break;

        case ID_MENU_ROOT:
            if (pDvdControl)            // Display root menu
            {
                pDvdControl->ShowMenu(DVD_MENU_Root, dwFlags, NULL);
                ResetRate();            // Reset playback rate
            }
            break;

        case ID_MENU_TITLE:
            if (pDvdControl)            // Display root menu
            {
                pDvdControl->ShowMenu(DVD_MENU_Title, dwFlags, NULL);
                ResetRate();            // Reset playback rate
            }
            break;

        case ID_MENU_RESUME:
            if (pDvdControl)            // Display root menu
            {
                pDvdControl->Resume(dwFlags, NULL);
                ResetRate();            // Reset playback rate
            }
            break;
    }
}


void HandleDiscEject(void)
{
    // By default, the navigator will automatically start playing another disc
    // when it is inserted if the graph is still running.
    
    // If you do not want this behavior, then you can handle the eject message, 
    // you must set the DVD_ResetOnStop flag to TRUE with the SetOption 
    // method and then call IMediaControl::Stop before closing the 
    // application or playing another disc.  Both of these calls are made within
    // the StopDVD() function.

    StopDVD();
    CloseDVDVolume();

    Msg(TEXT("The DVD was ejected from the drive."));
}
