//------------------------------------------------------------------------------
// File: PlayUtil.cpp
//
// Desc: DirectShow sample code - utility funtions for a simple windowed
//       DVD player application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "playdvd.h"

// Global data
BOOL g_bDisplayCC=0, g_bDisplaySubpicture=0;
HWND ghMessageDrain=0;


//
// Some video renderers support stepping media frame by frame with the
// IVideoFrameStep interface.  See the interface documentation for more
// details on frame stepping.
//
BOOL GetFrameStepInterface(void)
{
    HRESULT hr;
    IVideoFrameStep *pFSTest = NULL;

    // Get the frame step interface, if supported
    hr = pGB->QueryInterface(__uuidof(IVideoFrameStep), (PVOID *)&pFSTest);
    if (FAILED(hr))
        return FALSE;

    // Check if this decoder can step
    hr = pFSTest->CanStep(0L, NULL);

    if (hr == S_OK)
    {
        pFS = pFSTest;  // Save interface to global variable for later use
        return TRUE;
    }
    else
    {
        pFSTest->Release();
        return FALSE;
    }
}


HRESULT StepOneFrame(void)
{
    HRESULT hr=S_OK;

    // If the Frame Stepping interface exists, use it to step one frame
    if (pFS)
    {
        // The graph must be paused for frame stepping to work
        if (g_psCurrent != State_Paused)
            PauseDVD();

        // Step one frame
        hr = pFS->Step(1, NULL);
    }

    return hr;
}


HRESULT SetRate(double dRate)
{
    HRESULT hr=S_OK;

    if (pDvdControl)
    {
        // Enforce the maximum supported scan rate, accounting for
        // negative scan rates
        if ((dRate > 0) && (dRate > MAX_SCAN_RATE))
            return E_UNEXPECTED;
        if ((dRate < 0) && (-dRate > MAX_SCAN_RATE))
            return E_UNEXPECTED;

        // Use absolute value of rate for forward/backward playback.  Since
        // backward playback is indicated by passing in a negative dRate value,
        // use its absolute value in the PlayBackwards call.
        if (dRate > 0)
            hr = pDvdControl->PlayForwards(dRate, DVD_CMD_FLAG_Block | DVD_CMD_FLAG_Flush, NULL);
        else
            hr = pDvdControl->PlayBackwards(-dRate, DVD_CMD_FLAG_Block | DVD_CMD_FLAG_Flush, NULL);

        // Save global rate and display on title bar
        if (SUCCEEDED(hr))
            g_PlaybackRate = dRate;

        UpdateMainTitle();
    }

    return hr;
}


HRESULT ModifyRate(double dRateAdjust)
{
    if (dRateAdjust != 0)
    {
        // Add current rate to adjustment value
        double dNewRate = g_PlaybackRate + dRateAdjust;

        // Handle transition from scanning in reverse to playing normally
        if ((g_PlaybackRate < 0) && (dNewRate == 0))
            dNewRate = 1.0;

        // Set the new scan rate
        return SetRate(dNewRate);
    }

    return S_OK;
}


void ResetRate(void)
{
    g_PlaybackRate = 1.0;
    SetRate(g_PlaybackRate);
}


HRESULT ToggleMute(void)
{
    HRESULT hr=S_OK;

    if ((!pGB) || (!pBA))
        return S_OK;

    // Read current volume
    hr = pBA->get_Volume(&g_lVolume);
    if (hr == E_NOTIMPL)
    {
        // Fail quietly if this is a video-only media file
        return S_OK;
    }
    else if (FAILED(hr))
    {
        return hr;
    }

    // Switch volume levels
    if (g_lVolume == VOLUME_FULL)
        g_lVolume = VOLUME_SILENCE;
    else
        g_lVolume = VOLUME_FULL;

    // Set new volume
    JIF(pBA->put_Volume(g_lVolume));

    UpdateMainTitle();
    return hr;
}


HRESULT SetFullScreen(void)
{
    HRESULT hr=S_OK;
    LONG lMode;

    if (!pVW)
        return S_OK;

    // Read current state
    JIF(pVW->get_FullScreenMode(&lMode));

    if (lMode == OAFALSE)
    {
        // Save current message drain
        LIF(pVW->get_MessageDrain((OAHWND *) &ghMessageDrain));

        // Set message drain to application main window
        LIF(pVW->put_MessageDrain((OAHWND) ghApp));

        // Switch to full-screen mode
        lMode = OATRUE;
        JIF(pVW->put_FullScreenMode(lMode));
        g_bFullscreen = TRUE;
    }

    return hr;
}


HRESULT ClearFullScreen(void)
{
    HRESULT hr=S_OK;
    LONG lMode;

    if (!pVW)
        return S_OK;

    // Read current state
    JIF(pVW->get_FullScreenMode(&lMode));

    if (lMode == OATRUE)
    {
        // Switch back to windowed mode
        lMode = OAFALSE;
        JIF(pVW->put_FullScreenMode(lMode));

        // Undo change of message drain
        LIF(pVW->put_MessageDrain((OAHWND) ghMessageDrain));

        // Reset video window
        LIF(pVW->SetWindowForeground(-1));

        // Reclaim keyboard focus for player application
        UpdateWindow(ghApp);
        SetForegroundWindow(ghApp);
        SetFocus(ghApp);
        g_bFullscreen = FALSE;
    }

    return hr;
}


void ToggleCaptioning(void)
{
    HRESULT hr;
    g_bDisplayCC ^= 1;

    // Enable or disable Line21 Closed Captioning display
    if (pLine21Dec)
        hr = pLine21Dec->SetServiceState(g_bDisplayCC ? AM_L21_CCSTATE_On : AM_L21_CCSTATE_Off);

    // Update menu item to indicate new state
    CheckMenuItem(ghMenu, (UINT) ID_DVD_SHOWCC,
                 (UINT) (g_bDisplayCC) ? MF_CHECKED : MF_UNCHECKED);
}


void EnableSubpicture(BOOL bEnable)
{
    HRESULT hr;

    // Enable or disable subpicture stream display (which may contain text)
    if (pDvdControl)
        hr = pDvdControl->SetSubpictureState(bEnable, DVD_CMD_FLAG_None, NULL);

    // Update menu item to indicate new state
    CheckMenuItem(ghMenu, (UINT) ID_DVD_SHOWSUBPICTURE,
                 (UINT) (bEnable) ? MF_CHECKED : MF_UNCHECKED);
}


void CheckSizeMenu(WPARAM wParam)
{
    WPARAM nItems[4] = {ID_SIZE_HALF,    ID_SIZE_DOUBLE,
                        ID_SIZE_NORMAL,  ID_SIZE_THREEQUARTER};

    // Set/clear checkboxes that indicate the size of the video clip
    for (int i=0; i<4; i++)
    {
        // Check the selected item
        CheckMenuItem(ghMenu, (UINT) nItems[i],
                     (UINT) (wParam == nItems[i]) ? MF_CHECKED : MF_UNCHECKED);
    }
}


LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            if (wParam == IDOK)
            {
                EndDialog(hWnd, TRUE);
                return TRUE;
            }
            break;

        case WM_CLOSE:
            EndDialog(hWnd, TRUE);
            return TRUE;
    }
    return FALSE;
}


void Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    // Display a message box with the formatted string
    MessageBox(NULL, szBuffer, TEXT("PlayDVD Sample"), MB_OK | MB_APPLMODAL);
}


#ifdef REGISTER_FILTERGRAPH

HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
    IMoniker * pMoniker;
    IRunningObjectTable *pROT;
    if (FAILED(GetRunningObjectTable(0, &pROT))) 
    {
        return E_FAIL;
    }

    WCHAR wsz[128];
    wsprintfW(wsz, L"FilterGraph %08x pid %08x", (DWORD_PTR)pUnkGraph, 
              GetCurrentProcessId());

    HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
    if (SUCCEEDED(hr)) 
    {
        // Use the ROTFLAGS_REGISTRATIONKEEPSALIVE to ensure a strong reference
        // to the object.  Using this flag will cause the object to remain
        // registered until it is explicitly revoked with the Revoke() method.
        //
        // Not using this flag means that if GraphEdit remotely connects
        // to this graph and then GraphEdit exits, this object registration 
        // will be deleted, causing future attempts by GraphEdit to fail until
        // this application is restarted or until the graph is registered again.
        hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph, 
                            pMoniker, pdwRegister);
        pMoniker->Release();
    }

    pROT->Release();
    return hr;
}

void RemoveGraphFromRot(DWORD pdwRegister)
{
    IRunningObjectTable *pROT;

    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) 
    {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
}

#endif


DWORD GetStatusText(AM_DVD_RENDERSTATUS *pStatus, PTSTR pszStatusText, DWORD dwMaxText)
{
    TCHAR szBuffer[1000] ; // verified this is larger than any possible string we create
    
    int iChars ;
    PTSTR pszBuff = szBuffer ;
    ZeroMemory(szBuffer, sizeof(TCHAR) * NUMELMS( szBuffer ) ) ;

    if (pStatus->iNumStreamsFailed > 0)
    {
        iChars = wsprintf(pszBuff, 
            TEXT("* %d out of %d DVD-Video streams failed to render properly!\n"), 
            pStatus->iNumStreamsFailed, pStatus->iNumStreams) ;

        pszBuff += iChars ;
        
        if (pStatus->dwFailedStreamsFlag & AM_DVD_STREAM_VIDEO)
        {
            iChars = wsprintf(pszBuff, TEXT("    - video stream\n")) ;
            pszBuff += iChars ;
        }
        if (pStatus->dwFailedStreamsFlag & AM_DVD_STREAM_AUDIO)
        {
            iChars = wsprintf(pszBuff, TEXT("    - audio stream\n")) ;
            pszBuff += iChars ;
        }
        if (pStatus->dwFailedStreamsFlag & AM_DVD_STREAM_SUBPIC)
        {
            iChars = wsprintf(pszBuff, TEXT("    - subpicture stream\n")) ;
            pszBuff += iChars ;
        }
    }
    
    if (FAILED(pStatus->hrVPEStatus))
    {
        lstrcat(pszBuff, TEXT("* ")) ;
        pszBuff += lstrlen(TEXT("* ")) ;
        iChars = AMGetErrorText(pStatus->hrVPEStatus, pszBuff, 200) ;
        pszBuff += iChars ;
        lstrcat(pszBuff, TEXT("\n")) ;
        pszBuff += lstrlen(TEXT("\n")) ;
    }
    
    if (pStatus->bDvdVolInvalid)
    {
        iChars = wsprintf(pszBuff, TEXT("* Specified DVD-Video volume was invalid!\n")) ;
        pszBuff += iChars ;
    }
    else if (pStatus->bDvdVolUnknown)
    {
        iChars = wsprintf(pszBuff, TEXT("* No valid DVD-Video volume could be located!\n")) ;
        pszBuff += iChars ;
    }
    
    if (pStatus->bNoLine21In)
    {
        iChars = wsprintf(pszBuff, TEXT("* The video decoder doesn't produce closed captioning data.\n")) ;
        pszBuff += iChars ;
    }
    if (pStatus->bNoLine21Out)
    {
        iChars = wsprintf(pszBuff, TEXT("* Decoded closed caption data not rendered properly!\n")) ;
        pszBuff += iChars ;
    }
    
    DWORD dwLength = (pszBuff - szBuffer) * sizeof(*pszBuff) ;
    dwLength = min(dwLength, dwMaxText) ;
    lstrcpyn(pszStatusText, szBuffer, dwLength) ;
    
    return dwLength ;

}


void GetMenuHandles(void)
{
    // Main menu
    ghMenu = GetMenu(ghApp);

    // Submenus
    ghControlMenu  = GetSubMenu(ghMenu, emControl);
    ghNavigateMenu = GetSubMenu(ghMenu, emNavigate);
    ghOptionsMenu  = GetSubMenu(ghMenu, emOptions);

    // Submenu popups
    ghPresentationMenu = GetSubMenu(ghOptionsMenu, esmPresentation);
    ghMenuLanguageMenu = GetSubMenu(ghOptionsMenu, esmMenuLanguage);
    ghTitleMenu        = GetSubMenu(ghNavigateMenu, esmTitle);
    ghChapterMenu      = GetSubMenu(ghNavigateMenu, esmChapter);
}


void ClearSubmenu(HMENU hMenu)
{
    // Clear the menu
    int nCount = GetMenuItemCount(hMenu);

    // Delete all previous menu items
    for (int i=0; i < nCount; i++)
        DeleteMenu(hMenu, 0, MF_BYPOSITION);
}


void EnableAngleMenu(BOOL bEnable)
{
    int nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION;

    // Enable/disable the submenu
    EnableMenuItem(ghOptionsMenu, esmAngle, nState);      // Angle menu

    // Refresh the menu state
    DrawMenuBar(ghApp);
}


void EnablePlaybackMenu(BOOL bEnable)
{
    int nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION;

    // Enable/disable the submenus
    EnableMenuItem(ghMenu, emControl, nState);  // Control menu
    EnableMenuItem(ghMenu, emNavigate, nState); // Navigate menu
    EnableMenuItem(ghMenu, emOptions, nState);  // Options menu
    EnableMenuItem(ghMenu, emRate, nState);     // Rate menu

    // If we are disabling the menu, clear the check marks
    if (!bEnable)
    {
        CheckMenuItem(ghMenu, (UINT) ID_DVD_SHOWCC, MF_UNCHECKED);
        CheckMenuItem(ghMenu, (UINT) ID_DVD_SHOWSUBPICTURE, MF_UNCHECKED);
    }

    // Refresh the menu state
    DrawMenuBar(ghApp);
}


void EnablePresentationMenuItem(int nItem, BOOL bEnable)
{
    int nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND;

    // Enable/disable the submenu
    EnableMenuItem(ghPresentationMenu, nItem, nState);      // Angle menu

    // Refresh the menu state
    DrawMenuBar(ghApp);
}


void EnableOptionsMenus(BOOL bEnable)
{
    int nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION;

    // Enable/disable the submenus related to being in the menu state
    EnableMenuItem(ghMenu, emOptions, nState);  // Options menu
    EnableMenuItem(ghMenu, emRate, nState);     // Rate menu

    // Enable/disable the chapter navigation menu items
    nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND;
    EnableMenuItem(ghNavigateMenu, ID_DVD_NEXTCHAPTER, nState);
    EnableMenuItem(ghNavigateMenu, ID_DVD_PREVIOUSCHAPTER, nState);
    EnableMenuItem(ghNavigateMenu, ID_DVD_REPLAYCHAPTER, nState);

    // Enable/disable the playback control menu items.
    // In the menu domains, playback controls aren't valid.
    nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND;
    EnableMenuItem(ghControlMenu, ID_PAUSE, nState);
    EnableMenuItem(ghControlMenu, ID_PLAY,  nState);
    EnableMenuItem(ghControlMenu, ID_STOP,  nState);
    EnableMenuItem(ghControlMenu, ID_MUTE,  nState);
    EnableMenuItem(ghControlMenu, ID_SINGLE_STEP, nState);

    // Refresh the menu state
    DrawMenuBar(ghApp);
}


void EnableStopDomainMenus(BOOL bEnable)
{
    int nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYPOSITION;

    // Enable/disable the submenus related to being in the DOMAIN_Stop domain
    EnableMenuItem(ghMenu, emNavigate, nState); // Navigate menu
    EnableMenuItem(ghMenu, emOptions, nState);  // Options menu
    EnableMenuItem(ghMenu, emRate, nState);     // Rate menu

    // Enable/disable the playback control menu items.
    // In the DOMAIN_Stop domain, only Play is valid.
    nState = (UINT) ((bEnable) ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND;
    EnableMenuItem(ghControlMenu, ID_PAUSE, nState);
    EnableMenuItem(ghControlMenu, ID_STOP,  nState);
    EnableMenuItem(ghControlMenu, ID_MUTE,  nState);
    EnableMenuItem(ghControlMenu, ID_SINGLE_STEP, nState);

    // Refresh the menu state
    DrawMenuBar(ghApp);
}


