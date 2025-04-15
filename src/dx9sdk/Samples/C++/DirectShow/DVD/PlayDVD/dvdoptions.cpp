//------------------------------------------------------------------------------
// File: DVDOptions.cpp
//
// Desc: DirectShow sample code - methods for controlling DVD options
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "playdvd.h"


void ReadDVDInformation(void)
{
    // Read the number of available audio streams
    GetAudioInfo();
    UpdateAudioInfo();

    // Read the number of available angles
    GetAngleInfo();
    UpdateAngleInfo();

    // Read the number of subpicture streams supported and configure
    // the subpicture stream menu (often subtitle languages)
    GetSubpictureInfo();
    UpdateSubpictureInfo();

    // Read the number of available titles
    GetTitleInfo();

    // Find out whether this title supports 4x3 PanScan, Letterbox, etc.
    GetPresentationCaps();

    // Read the available menu languages
    GetMenuLanguageInfo();
}


HRESULT SetDVDPlaybackOptions()
{
    HRESULT hr;

    if (pLine21Dec)
    {
        // Disable Line21 (closed captioning) by default
        hr = pLine21Dec->SetServiceState(AM_L21_CCSTATE_Off) ; 
        if (FAILED(hr))
            return hr;
    }

    // Don't reset DVD on stop.  This prevents the DVD from entering
    // DOMAIN_Stop when we stop playback or during resolution modes changes
    hr = pDvdControl->SetOption(DVD_ResetOnStop, FALSE); 
    if (FAILED(hr))
        return hr;

    // Ignore parental control for this application
    // If this is TRUE, then the nav will send an event and wait for you
    // to respond with AcceptParentalLevelChangeNotification()
    //
    hr = pDvdControl->SetOption(DVD_NotifyParentalLevelChange, FALSE);
    if (FAILED(hr))
        return hr;

    // Use HMSF timecode format (instead of binary coded decimal)
    hr = pDvdControl->SetOption(DVD_HMSF_TimeCodeEvents, TRUE); 
    if (FAILED(hr))
        return hr;

    return hr;
}


HRESULT GetPresentationCaps()
{
    HRESULT hr;
    DVD_VideoAttributes va={0};

    hr = pDvdInfo->GetCurrentVideoAttributes(&va);
    if (FAILED(hr))
    {
        Msg(TEXT("Failed to read video attributes. hr=0x%x"), hr);
        return hr;
    }

    // Read the attributes supplied by the returned structure to 
    // determine which presentation modes are supported by this disc
    EnablePresentationMenuItem(ID_DVD_PANSCAN,   va.fPanscanPermitted);
    EnablePresentationMenuItem(ID_DVD_LETTERBOX, va.fLetterboxPermitted);

#if 0
    // Determine the current aspect ratio / presentation mode
    int nActive = ID_DVD_PRESENTATION_DEFAULT;

    if ((va.ulAspectX == 4) && (va.ulAspectY == 3))
    {
        // 4x3 mode
        if (va.fIsSourceLetterboxed)
            nActive = ID_DVD_LETTERBOX;   // 4x3 Letterbox
        else
            nActive = ID_DVD_PANSCAN;     // 4x3 Pan and Scan
    }
    else if ((va.ulAspectX == 16) && (va.ulAspectY == 9))
    {
        // 16x9 mode
        nActive = ID_DVD_16x9;
    }
#endif

    return hr;
}


HRESULT SetPresentationMode(int nMode)
{
    HRESULT hr;

    hr = pDvdControl->SelectVideoModePreference(nMode);
    if (FAILED(hr))
    {
        if (hr == VFW_E_DVD_OPERATION_INHIBITED)
            ShowValidUOPS(TEXT("Presentation Mode"));
        else if (hr == VFW_E_DVD_INVALIDDOMAIN)
            Msg(TEXT("Changing presentation mode is not allowed in this domain."));
    }

    return hr;
}


HRESULT GetTitleInfo()
{
    HRESULT hr;
    DVD_DISC_SIDE DiscSide;
    ULONG ulNumVolumes=0, ulCurrentVolume=0, ulNumTitles=0;

    // Read the number of titles available on this disc
    hr = pDvdInfo->GetDVDVolumeInfo(&ulNumVolumes, &ulCurrentVolume,
                                    &DiscSide, &ulNumTitles);

    if (SUCCEEDED(hr))
    {
        // Save the number of titles on this disc
        g_ulNumTitles = ulNumTitles;

        // Remove any existing submenu items
        ClearSubmenu(ghTitleMenu);

        // Add an entry to the menu for each available title.
        //
        // NOTE: Since titles range from 1 to 99, start counting at 1
        // and compare with '<=' instead of '<'.
        for (unsigned int i=1; i <= ulNumTitles; i++)
        {
            TCHAR szTitle[32];
            wsprintf(szTitle, TEXT("Title %d\0"), i);

            // Add the angle to the menu
            AppendMenu(ghTitleMenu, MF_STRING, ID_DVD_TITLE_BASE + i, szTitle);
        }

        // Check the first (default) title in the list
        CheckMenuItem(ghTitleMenu, 0, MF_CHECKED | MF_BYPOSITION);
    }

    return S_OK;
}


void UpdateCurrentTitle(ULONG ulCurTitle)
{
    // If the title menu hasn't yet been created, just return success
    if (!ghTitleMenu || !g_ulNumTitles)
        return;

    // Update the current title selection
    //
    // NOTE: Since titles range from 1 to 99, start counting at 1
    // and compare with '<=' instead of '<'.
    for (ULONG i=1; i <= g_ulNumTitles; i++)
    {
        CheckMenuItem(ghTitleMenu, (UINT) ID_DVD_TITLE_BASE + i,
                     (UINT) (ulCurTitle == i) ? MF_CHECKED : MF_UNCHECKED);
    }

    // Update the chapter menu and check the current chapter
    ClearSubmenu(ghChapterMenu);
}


void ConfigureChapterMenu(void)
{
    HRESULT hr;
    DVD_PLAYBACK_LOCATION2 loc={0};

    hr = pDvdInfo->GetCurrentLocation(&loc);
    if (SUCCEEDED(hr))
    {
        UpdateChapterCount(loc.TitleNum);
        UpdateCurrentChapter(loc.ChapterNum);
    }
}


HRESULT UpdateChapterCount(ULONG ulTitle)
{
    HRESULT hr;
    int i;
    ULONG ulNumChapters=0;

    // If we haven't yet read the number of titles on the disc, return success
    if (!g_ulNumTitles)
        return S_OK;

    hr = pDvdInfo->GetNumberOfChapters(ulTitle, &ulNumChapters);
    if (SUCCEEDED(hr))
    {
        // Save the number of chapters in this title
        g_ulNumChapters = ulNumChapters;

        // Remove any existing submenu items
        ClearSubmenu(ghChapterMenu);

        // Add an entry to the menu for each available chapter
        // in the current title
        //
        // NOTE: Since chapters range from 1 to 999, start counting at 1
        // and compare with '<=' instead of '<'.
        for (i=1; i <= (int) ulNumChapters; i++)
        {
            TCHAR szChapter[32];
            wsprintf(szChapter, TEXT("Chapter %d\0"), i);

            // Add the angle to the menu
            AppendMenu(ghChapterMenu, MF_STRING, ID_DVD_CHAPTER_BASE + i, szChapter);
        }

        // Check the first (default) chapter in the list
        CheckMenuItem(ghChapterMenu, 0, MF_CHECKED | MF_BYPOSITION);
    }

    return hr;
}


HRESULT UpdateCurrentChapter(ULONG ulCurChapter)
{
    HRESULT hr;
    ULONG ulNumChapters=0;

    // If the chapter menu hasn't yet been created, just return success
    if (!ghChapterMenu)
        return S_OK;

    // If we haven't yet read the number of titles on the disc, return success
    if (!g_ulNumTitles)
        return S_OK;

    // How many chapters are in the current title?
    hr = pDvdInfo->GetNumberOfChapters(g_ulCurTitle, &ulNumChapters);
    if (SUCCEEDED(hr))
    {
        // Update the current chapter selection
        for (ULONG i=1; i <= ulNumChapters; i++)
        {
            CheckMenuItem(ghChapterMenu, (UINT) ID_DVD_CHAPTER_BASE + i,
                         (UINT) (ulCurChapter == i) ? MF_CHECKED : MF_UNCHECKED);
        }
    }

    return S_OK;
}


HRESULT SetTitle(int nTitle)
{
    HRESULT hr;
 
    // Play the selected title
    hr = pDvdControl->PlayTitle(nTitle, DVD_CMD_FLAG_Block, NULL);
    if (FAILED(hr))
    {
        if (hr == VFW_E_DVD_OPERATION_INHIBITED)
            ShowValidUOPS(TEXT("Title"));
    }

    return hr;
}


HRESULT SetChapter(int nChapter)
{
    HRESULT hr;
 
    // Play the selected chapter
    hr = pDvdControl->PlayChapter(nChapter, DVD_CMD_FLAG_Block, NULL);
    if (FAILED(hr))
    {
        if (hr == VFW_E_DVD_OPERATION_INHIBITED)
            ShowValidUOPS(TEXT("Chapter"));
    }

    return hr;
}


HRESULT GetSubpictureInfo()
{
    HRESULT hr;
    int i;

    // Read the number of subpicture streams available
    ULONG ulStreamsAvailable=0, ulCurrentStream=0;
    BOOL bIsDisabled=1;

    hr = pDvdInfo->GetCurrentSubpicture(&ulStreamsAvailable, &ulCurrentStream, 
                                        &bIsDisabled);
    if (SUCCEEDED(hr))
    {
        // Update the on/off menu item
        g_bDisplaySubpicture = !bIsDisabled;
        EnableSubpicture(g_bDisplaySubpicture);

        // Clear the current subpicture selection menu
        ghSubpictureMenu = GetSubMenu(ghOptionsMenu, esmSubpicture);
        int nCount = GetMenuItemCount(ghSubpictureMenu);

        // Delete items after the "Show subpicture" item and separator
        for (i=2; i < nCount; i++)
            DeleteMenu(ghSubpictureMenu, i, MF_BYPOSITION);

        // Add an entry to the menu for each available subpicture stream
        for (i=0; i < (int) ulStreamsAvailable; i++)
        {
            LCID lcid;
            TCHAR szLang[128];

            // Get the language ID for this stream
            if (FAILED(hr = pDvdInfo->GetSubpictureLanguage(i, &lcid)))
            {
                Msg(TEXT("GetSubpictureLanguage Failed for language #%d!  hr=0x%x"), i, hr);
                continue;
            }

            // Skip this entry if there is no language ID
            if (lcid == 0)
                continue;

            // Convert the language ID to a string.
            // (0 is the failure code for GetLocaleInfo)
            if (0 == GetLocaleInfo(lcid, LOCALE_SLANGUAGE, szLang, NUMELMS(szLang))) 
            {
                Msg(TEXT("Failed to convert language ID #%d to string!"), i);
                continue;
            }

            // Add the language to the menu
            AppendMenu(ghSubpictureMenu, MF_STRING, ID_DVD_SUBPICTURE_BASE + i, szLang);            
        }
    }

    return S_OK;
}


HRESULT UpdateSubpictureInfo()
{
    HRESULT hr;

    // Read the number of subpicture streams and the current state
    ULONG ulStreamsAvailable=0, ulCurrentStream=0;
    BOOL bIsDisabled=1;

    hr = pDvdInfo->GetCurrentSubpicture(&ulStreamsAvailable, &ulCurrentStream, 
                                        &bIsDisabled);
    if (SUCCEEDED(hr))
    {
        // Update the on/off menu item check
        g_bDisplaySubpicture = !bIsDisabled;

        CheckMenuItem(ghSubpictureMenu, (UINT) ID_DVD_SHOWSUBPICTURE,
                     (UINT) (g_bDisplaySubpicture) ? MF_CHECKED : MF_UNCHECKED);

        // Update the current subpicture language selection
        for (ULONG i=0; i < ulStreamsAvailable; i++)
        {
            CheckMenuItem(ghSubpictureMenu, (UINT) ID_DVD_SUBPICTURE_BASE + i,
                         (UINT) (ulCurrentStream == i) ? MF_CHECKED : MF_UNCHECKED);
        }
    }

    return S_OK;
}


HRESULT SetSubpictureStream(int nStream)
{
    HRESULT hr;
 
    // Set the subpicture stream to the requested value
    // Note that this does not affect the spoken dialog - it's just the subpicture data
    hr = pDvdControl->SelectSubpictureStream(nStream, DVD_CMD_FLAG_None, NULL);

    if (FAILED(hr))
    {
        switch (hr)
        {
            case VFW_E_DVD_OPERATION_INHIBITED:
                ShowValidUOPS(TEXT("Subpicture Stream"));
                break;

            case VFW_E_DVD_INVALIDDOMAIN:
                Msg(TEXT("Can't change the subpicture stream in this domain."));
                break;

            case VFW_E_DVD_STREAM_DISABLED:
                Msg(TEXT("The selected stream (#%d) is currently disabled."), nStream+1);
                break;
        }
    }

    return hr;
}


HRESULT GetAudioInfo()
{
    HRESULT hr;
    ULONG ulStreamsAvailable=0, ulCurrentStream=0;

    // Read the number of audio streams available
    hr = pDvdInfo->GetCurrentAudio(&ulStreamsAvailable, &ulCurrentStream); 
    if (SUCCEEDED(hr))
    {
        // Clear the current audio stream menu
        ghAudioMenu = GetSubMenu(ghOptionsMenu, esmAudio);

        // Remove any existing submenu items
        ClearSubmenu(ghAudioMenu);

        // Add an entry to the menu for each available audio stream
        for (ULONG i=0; i < ulStreamsAvailable; i++)
        {
            LCID lcid;
            TCHAR szLang[80];

            // Get the language ID for this stream
            if (FAILED(hr = pDvdInfo->GetAudioLanguage(i, &lcid)))
            {
                Msg(TEXT("GetAudioLanguage Failed for language #%d!  hr=0x%x"), i, hr);
                continue;
            }

            // Skip this entry if there is no language ID
            if (lcid == 0)
                continue;

            // Convert the language ID to a string.
            // 0 is the failure code for GetLocaleInfo
            if (0 == GetLocaleInfo(lcid, LOCALE_SLANGUAGE, szLang, NUMELMS(szLang))) 
            {
                Msg(TEXT("Failed to convert audio language ID #%d to string!"), i);
                continue;
            }

            // Add the language to the menu
            AppendMenu(ghAudioMenu, MF_STRING, ID_DVD_AUDIO_BASE + i, szLang);            
        }
    }

    return S_OK;
}


HRESULT UpdateAudioInfo()
{
    HRESULT hr;

    // Read the number of audio streams and the current state
    ULONG ulStreamsAvailable=0, ulCurrentStream=0;

    hr = pDvdInfo->GetCurrentAudio(&ulStreamsAvailable, &ulCurrentStream);
    if (SUCCEEDED(hr))
    {
        // Update the current audio language selection
        for (ULONG i=0; i < ulStreamsAvailable; i++)
        {
            CheckMenuItem(ghAudioMenu, (UINT) ID_DVD_AUDIO_BASE + i,
                         (UINT) (ulCurrentStream == i) ? MF_CHECKED : MF_UNCHECKED);
        }
    }

    return S_OK;
}


HRESULT SetAudioStream(int nStream)
{
    HRESULT hr;
 
    // Set the audio stream to the requested value
    // Note that this does not affect the subpicture data (subtitles)
    hr = pDvdControl->SelectAudioStream(nStream, DVD_CMD_FLAG_None, NULL);

    if (FAILED(hr))
    {
        if (hr == VFW_E_DVD_OPERATION_INHIBITED)
            ShowValidUOPS(TEXT("Audio Stream"));
    }

    return hr;
}


HRESULT GetAngleInfo()
{
    HRESULT hr;

    ULONG ulAnglesAvailable=0, ulCurrentAngle=0;

    // Read the number of angles available
    hr = pDvdInfo->GetCurrentAngle(&ulAnglesAvailable, &ulCurrentAngle); 
    if (SUCCEEDED(hr))
    {
        // Clear the current angle menu
        ghAngleMenu = GetSubMenu(ghOptionsMenu, esmAngle);

        // Remove any existing submenu items
        ClearSubmenu(ghAngleMenu);

        //
        // Add an entry to the menu for each available angle
        //

        // An angle count of 1 means that the DVD is not in an 
        // angle block, so disable angle selection.
        if (ulAnglesAvailable < 2)
        {
            AppendMenu(ghAngleMenu, MF_STRING, ID_DVD_ANGLE_BASE, TEXT("Default Angle"));
            EnableAngleMenu(FALSE);
        }
        else
        {
            // Enable angle selection with this menu
            EnableAngleMenu(TRUE);

            //
            // NOTE: Since angles range from 1 to 9, start counting at 1
            // and compare with '<=' instead of '<'.
            for (ULONG i=1; i <= ulAnglesAvailable; i++)
            {
                TCHAR szAngle[32];
                wsprintf(szAngle, TEXT("Angle %d\0"), i);

                // Add the angle to the menu
                AppendMenu(ghAngleMenu, MF_STRING, ID_DVD_ANGLE_BASE + i, szAngle);
            }
        }
    }

    // Check the first (default) angle in the list
    CheckMenuItem(ghAngleMenu, 0, MF_CHECKED | MF_BYPOSITION);

    return S_OK;
}


HRESULT UpdateAngleInfo()
{
    HRESULT hr;

    // If the angle menu hasn't yet been created, just return success
    if (!ghAngleMenu)
        return S_OK;

    // Read the number of angles and the current selection
    ULONG ulAnglesAvailable=0, ulCurrentAngle=0;

    hr = pDvdInfo->GetCurrentAngle(&ulAnglesAvailable, &ulCurrentAngle); 
    if (SUCCEEDED(hr))
    {
        // Update the current angle selection
        for (ULONG i=1; i <= ulAnglesAvailable; i++)
        {
            CheckMenuItem(ghAngleMenu, (UINT) ID_DVD_ANGLE_BASE + i,
                         (UINT) (ulCurrentAngle == i) ? MF_CHECKED : MF_UNCHECKED);
        }
    }

    return S_OK;
}


HRESULT SetAngle(int nAngle)
{
    HRESULT hr;
 
    // Set the angle to the requested value.
    hr = pDvdControl->SelectAngle(nAngle, DVD_CMD_FLAG_None, NULL);

    if (FAILED(hr))
    {
        if (hr == VFW_E_DVD_OPERATION_INHIBITED)
            ShowValidUOPS(TEXT("Angle"));
    }

    return hr;
}


HRESULT GetMenuLanguageInfo()
{
    HRESULT hr;
    int i;

    // Read the number of available menu languages
    ULONG ulLanguagesAvailable=0;

    hr = pDvdInfo->GetMenuLanguages(NULL, 10, &ulLanguagesAvailable);
    if (FAILED(hr))
        return hr;

    // Allocate a language array large enough to hold the language list
    g_pLanguageList = new LCID[ulLanguagesAvailable];

    // Now fill the language array with the menu languages
    hr = pDvdInfo->GetMenuLanguages(g_pLanguageList, ulLanguagesAvailable, 
                                    &ulLanguagesAvailable);
    if (SUCCEEDED(hr))
    {
        // Clear the current menu language menu
        ClearSubmenu(ghMenuLanguageMenu);

        // Add an entry to the menu for each available menu language
        for (i=0; i < (int) ulLanguagesAvailable; i++)
        {
            TCHAR szLang[128], szMenu[150];

            // Skip this entry if there is no language ID
            if (g_pLanguageList[i] == 0)
                continue;

            // Convert the language ID to a string.
            // (0 is the failure code for GetLocaleInfo)
            if (0 == GetLocaleInfo(g_pLanguageList[i], LOCALE_SLANGUAGE, 
                                   szLang, NUMELMS(szLang)))
            {
                Msg(TEXT("Failed to convert menu language ID #%d to string!"), i);
                continue;
            }

            _stprintf(szMenu, TEXT("%s (0x%x)\0"), szLang, g_pLanguageList[i]);

            // Add the language to the menu
            AppendMenu(ghMenuLanguageMenu, MF_STRING, ID_DVD_MENULANG_BASE + i, szMenu);
        }
    }

    // Check the first (default) language in the list
    CheckMenuItem(ghMenuLanguageMenu, 0, MF_CHECKED | MF_BYPOSITION);

    return S_OK;
}


HRESULT SetMenuLanguage(int nLanguageIndex)
{
    HRESULT hr;
    
    // Set ResetOnStop option
    hr = pDvdControl->SetOption(DVD_ResetOnStop, TRUE); 

    // Changing menu language is only valid in the DVD_DOMAIN_Stop domain
    hr = pDvdControl->Stop();

    if (SUCCEEDED(hr))
    {
        LCID lcid = g_pLanguageList[nLanguageIndex];

        // Change the default menu language
        hr = pDvdControl->SelectDefaultMenuLanguage(lcid);

        // Display the root menu
        hr = pDvdControl->ShowMenu(DVD_MENU_Root, DVD_CMD_FLAG_Block | DVD_CMD_FLAG_Flush, NULL);
    }

    // Turn off ResetOnStop option
    hr = pDvdControl->SetOption(DVD_ResetOnStop, FALSE); 

    return hr;
}


void ShowValidUOPS(TCHAR *szAttemptedAction)
{
    TCHAR szMsg[1024];

    // Read the current disc UOPS
    ULONG ulCurrentUOPS=0;
    HRESULT hr = pDvdInfo->GetCurrentUOPS(&ulCurrentUOPS);
    if (FAILED(hr))
    {
        Msg(TEXT("Failed to read disc UOPS!  hr=0x%x\0"), hr);
        return;
    }

    // Compare what the disc reports to what our EC_DVD_VALID_UOPS_CHANGE
    // event callback has received.
    if (ulCurrentUOPS != g_ulValidUOPS)
    {
        Msg(TEXT("Disc UOPS don't match event-provided UOPS!\n")
            TEXT("Event UOPS: 0x%x\nDisc  UOPS: 0x%x\0"),
            ulCurrentUOPS, g_ulValidUOPS);
    }

    // Format the message
    wsprintf(szMsg, TEXT("Changing %s is not valid at this time (prohibited by DVD).\n\n")
             TEXT("The valid user operations (UOPS) allowed now are:\n\0"),
             szAttemptedAction);

#define HANDLE_UOP(c)                       \
        if ((g_ulValidUOPS & c) == 0)       \
            _tcscat(szMsg, _T("\t") _T(#c) _T("\n\0")); \

    // Add the names of the valid UOPS flags to the message.
    // Since the UOPS field indicates actions that are prohibited,
    // if a flag is NOT set, then the action is valid.
    HANDLE_UOP(UOP_FLAG_Play_Title_Or_AtTime);
    HANDLE_UOP(UOP_FLAG_Play_Chapter);
    HANDLE_UOP(UOP_FLAG_Play_Title);
    HANDLE_UOP(UOP_FLAG_Stop);
    HANDLE_UOP(UOP_FLAG_ReturnFromSubMenu);
    HANDLE_UOP(UOP_FLAG_Play_Chapter_Or_AtTime);
    HANDLE_UOP(UOP_FLAG_PlayPrev_Or_Replay_Chapter);
    HANDLE_UOP(UOP_FLAG_PlayNext_Chapter);
    HANDLE_UOP(UOP_FLAG_Play_Forwards);
    HANDLE_UOP(UOP_FLAG_Play_Backwards);
    HANDLE_UOP(UOP_FLAG_ShowMenu_Title);
    HANDLE_UOP(UOP_FLAG_ShowMenu_Root);
    HANDLE_UOP(UOP_FLAG_ShowMenu_SubPic);
    HANDLE_UOP(UOP_FLAG_ShowMenu_Audio);
    HANDLE_UOP(UOP_FLAG_ShowMenu_Angle);
    HANDLE_UOP(UOP_FLAG_ShowMenu_Chapter);
    HANDLE_UOP(UOP_FLAG_Resume);
    HANDLE_UOP(UOP_FLAG_Select_Or_Activate_Button);
    HANDLE_UOP(UOP_FLAG_Still_Off);
    HANDLE_UOP(UOP_FLAG_Pause_On);
    HANDLE_UOP(UOP_FLAG_Select_Audio_Stream);
    HANDLE_UOP(UOP_FLAG_Select_SubPic_Stream);
    HANDLE_UOP(UOP_FLAG_Select_Angle);
    HANDLE_UOP(UOP_FLAG_Select_Karaoke_Audio_Presentation_Mode);
    HANDLE_UOP(UOP_FLAG_Select_Video_Mode_Preference);

    MessageBox(ghApp, szMsg, TEXT("Requested action prevented by DVD"), MB_OK);
}