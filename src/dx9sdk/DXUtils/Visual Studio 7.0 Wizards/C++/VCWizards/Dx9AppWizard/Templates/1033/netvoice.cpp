//-----------------------------------------------------------------------------
// File: NetVoice.cpp
//
// Desc: DirectPlay Voice framework class. Feel free to use 
//       this class as a starting point for adding extra functionality.
//-----------------------------------------------------------------------------
#define STRICT
[!if DLG]
#include "stdafx.h"
[!endif]
#include <windows.h>
#include <commctrl.h>
#include <dxerr9.h>
#include <dvoice.h>
#include "NetVoice.h"
#include "NetVoiceRes.h"
#include "DXUtil.h"


//-----------------------------------------------------------------------------
// Global access to the app (needed for the global WndProc())
//-----------------------------------------------------------------------------
static CNetVoice* g_pNetVoice = NULL;




//-----------------------------------------------------------------------------
// Name: CNetVoice
// Desc: 
//-----------------------------------------------------------------------------
CNetVoice::CNetVoice( LPDVMESSAGEHANDLER pfnDirectPlayClientVoiceMessageHandler,
                      LPDVMESSAGEHANDLER pfnDirectPlayServerVoiceMessageHandler )
{
    g_pNetVoice = this;
    m_bHalfDuplex  = FALSE;
    m_pVoiceClient = NULL;
    m_pVoiceServer = NULL;
    m_bVoiceSessionInProgress = FALSE;
    m_pfnDirectPlayClientVoiceMessageHandler = pfnDirectPlayClientVoiceMessageHandler;
    m_pfnDirectPlayServerVoiceMessageHandler = pfnDirectPlayServerVoiceMessageHandler;
}




//-----------------------------------------------------------------------------
// Name: ~CNetVoice
// Desc: 
//-----------------------------------------------------------------------------
CNetVoice::~CNetVoice()
{
    Free();
}




//-----------------------------------------------------------------------------
// Name: Init()
// Desc: Initializes DirectPlay Voice.  
// Params:  hDlg: the HWND of the parent window for use by the voice setup wizard
//          bCreateSession:     if TRUE then it creates the DirectPlay Voice sesson.
//          bConnectToSession:  if TRUE then it connects to the DirectPlay Voice
//                              session.  
//          pDirectPlay:        inteface to the IDirectPlay8Client or 
//                              IDirectPlay8Peer interface 
//          pGuidCT:            guid of the voice compression codec
//          pdvClientConfig:    client config. Can be NULL if bConnectToSession is FALSE.
//          lpds:               pointer to an existing DirectSound object, or NULL 
//                              if none exists yet.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::Init( HWND hDlg, BOOL bCreateSession, BOOL bConnectToSession,
                         LPUNKNOWN pDirectPlay, DWORD dwSessionType, 
                         GUID* pGuidCT, DVCLIENTCONFIG* pdvClientConfig, LPDIRECTSOUND lpds )
{
    HRESULT hr;

    // Typically the host player creates the voice session 
    if( bCreateSession )
    {
        if( FAILED( hr = VoiceSessionCreate( pDirectPlay, dwSessionType, pGuidCT ) ) )
            return DXTRACE_ERR( TEXT("VoiceSessionCreate"), hr );
    }

    if( bConnectToSession )
    {
        // Test the voice setup to make sure the voice setup wizard has been run
        if( FAILED( hr = VoiceSessionTestAudioSetup( hDlg ) ) )
        {
            if( hr == DVERR_USERCANCEL || hr == DVERR_ALREADYPENDING )
                return hr;
            
            return DXTRACE_ERR( TEXT("VoiceSessionTestAudioSetup"), hr );
        }

        // Typically all of the clients connect to the voice session
        if( FAILED( hr = VoiceSessionConnect( hDlg, pDirectPlay, pdvClientConfig, lpds ) ) )
            return DXTRACE_ERR( TEXT("VoiceSessionConnect"), hr );
    }

    m_bVoiceSessionInProgress = TRUE;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Free()
// Desc: Frees DirectPlayVoice
//-----------------------------------------------------------------------------
HRESULT CNetVoice::Free()
{
    HRESULT hr;

    if( m_pVoiceClient )
    {
        // Have all the clients disconnect from the session
        if( FAILED( hr = VoiceSessionDisconnect() ) )
            return DXTRACE_ERR( TEXT("VoiceSessionDisconnect"), hr );
    }

    if( m_pVoiceServer )
    {
        // Have all the host player destroy the session 
        if( FAILED( hr = VoiceSessionDestroy() ) )
            return DXTRACE_ERR( TEXT("VoiceSessionDestroy"), hr );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: HostMigrate()
// Desc: Starts the DirectPlayVoice session
//       The host player should call this to create the voice session.  It
//       stores the server interface, and addref's it.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::HostMigrate( LPDIRECTPLAYVOICESERVER pdvServerInterface )
{
    if( pdvServerInterface == NULL )
        return E_INVALIDARG;

    SAFE_RELEASE( m_pVoiceServer );

    m_pVoiceServer = pdvServerInterface;

    // Addref the server since we are storing the pointer.
    m_pVoiceServer->AddRef();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: VoiceSessionTestAudioSetup()
// Desc: Uses IDirectPlayVoiceSetup to test the voice setup.
//       All clients should call this once to test the voice audio setup.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::VoiceSessionTestAudioSetup( HWND hDlg )
{
    HRESULT hr;
    LPDIRECTPLAYVOICETEST pVoiceSetup = NULL;

    // Create a DirectPlayVoice setup interface.
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlayVoiceTest, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlayVoiceTest, 
                                       (LPVOID*) &pVoiceSetup) ) )
        return DXTRACE_ERR( TEXT("CoCreateInstance"), hr );

    // Check to see if the audio tests have been run yet
    GUID guidPlayback = DSDEVID_DefaultVoicePlayback;
    GUID guidCapture  = DSDEVID_DefaultVoiceCapture;
    hr = pVoiceSetup->CheckAudioSetup( &guidPlayback, 
                                       &guidCapture, 
                                       hDlg, DVFLAGS_QUERYONLY );
    if( hr == DVERR_RUNSETUP )
    {
        // Perform the audio tests, since they need to be done before 
        // any of the DPVoice calls will work.
        hr = pVoiceSetup->CheckAudioSetup( &guidPlayback, &guidCapture, hDlg, DVFLAGS_ALLOWBACK );
        if( FAILED(hr) )
        {
            SAFE_RELEASE( pVoiceSetup );
            
            if( hr == DVERR_USERCANCEL || hr == DVERR_ALREADYPENDING )
                return hr;
            
            return DXTRACE_ERR( TEXT("CheckAudioSetup"), hr );
        }
    }

    // Done with setup
    SAFE_RELEASE( pVoiceSetup );

    return hr;
}




//-----------------------------------------------------------------------------
// Name: VoiceSessionCreate()
// Desc: Starts the DirectPlayVoice session
//       The host player should call this to create the voice session.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::VoiceSessionCreate( LPUNKNOWN pDirectPlay, DWORD dwSessionType, 
                                       GUID* pGuidCT )
{
    HRESULT hr;

    // Create a DirectPlayVoice server interface.
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlayVoiceServer, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlayVoiceServer, 
                                       (LPVOID*) &m_pVoiceServer ) ) )
        return DXTRACE_ERR( TEXT("CoCreateInstance"), hr );

    // Init the DirectPlayVoice server
    if( FAILED( hr = m_pVoiceServer->Initialize( pDirectPlay, m_pfnDirectPlayServerVoiceMessageHandler, 
                                                 NULL, 0, 0 ) ) )
        return DXTRACE_ERR( TEXT("Initialize"), hr );

    // Setup and start a DirectPlay session based on globals set by user choices 
    // in the config dlg box.
    DVSESSIONDESC dvSessionDesc;
    ZeroMemory( &dvSessionDesc, sizeof(DVSESSIONDESC) );
    dvSessionDesc.dwSize                 = sizeof( DVSESSIONDESC );
    dvSessionDesc.dwBufferAggressiveness = DVBUFFERAGGRESSIVENESS_DEFAULT;
    dvSessionDesc.dwBufferQuality        = DVBUFFERQUALITY_DEFAULT;
    dvSessionDesc.dwFlags                = 0;
    dvSessionDesc.dwSessionType          = dwSessionType;
    dvSessionDesc.guidCT                 = *pGuidCT;

    if( FAILED( hr = m_pVoiceServer->StartSession( &dvSessionDesc, 0 ) ) )
        return DXTRACE_ERR( TEXT("StartSession"), hr );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: VoiceSessionConnect()
// Desc: Connects to the DirectPlayVoice session.  
///      All clients should call this once to join the voice session.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::VoiceSessionConnect( HWND hDlg, LPUNKNOWN pDirectPlay, 
                                        DVCLIENTCONFIG* pdvClientConfig, LPDIRECTSOUND lpds )
{
    HRESULT hr;
    DVSOUNDDEVICECONFIG  dvSoundDeviceConfig  = {0};
    DVSOUNDDEVICECONFIG* pdvSoundDeviceConfig = NULL;
    

    // Create a DirectPlayVoice client interface.
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlayVoiceClient, NULL, 
                                       CLSCTX_INPROC_SERVER,
                                       IID_IDirectPlayVoiceClient, 
                                       (LPVOID*) &m_pVoiceClient ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("CoCreateInstance"), hr );
        goto LCleanReturn;
    }

    // Init the DirectPlayVoice client, passing in VoiceMessageHandler() as the
    // callback handler for any messages sent to us.
    if( FAILED( hr = m_pVoiceClient->Initialize( pDirectPlay, 
                                                 m_pfnDirectPlayClientVoiceMessageHandler, 
                                                 (LPVOID*) hDlg, // context value
                                                 0, 0 ) ) )
    {
         DXTRACE_ERR_MSGBOX( TEXT("Initialize"), hr );
         goto LCleanReturn;
    }

    // Setup the DirectPlayVoice sound devices.  This just uses the defaults.
    dvSoundDeviceConfig.dwSize                    = sizeof( DVSOUNDDEVICECONFIG );
    dvSoundDeviceConfig.dwFlags                   = 0;
    dvSoundDeviceConfig.guidPlaybackDevice        = DSDEVID_DefaultVoicePlayback; 
    dvSoundDeviceConfig.lpdsPlaybackDevice        = lpds;
    dvSoundDeviceConfig.guidCaptureDevice         = DSDEVID_DefaultVoiceCapture; 
    dvSoundDeviceConfig.lpdsCaptureDevice         = NULL;
    dvSoundDeviceConfig.hwndAppWindow             = hDlg;
    dvSoundDeviceConfig.lpdsMainBuffer            = NULL;
    dvSoundDeviceConfig.dwMainBufferFlags         = 0;
    dvSoundDeviceConfig.dwMainBufferPriority      = 0;

    // Connect to the voice session
    if( FAILED( hr = m_pVoiceClient->Connect( &dvSoundDeviceConfig, 
                                              pdvClientConfig, 
                                              DVFLAGS_SYNC ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("Connect"), hr );
        goto LCleanReturn;
    }
        
    // Talk to everyone in the session
    DVID dvid;
    dvid = DVID_ALLPLAYERS;
    if( FAILED( hr = m_pVoiceClient->SetTransmitTargets( &dvid, 1, 0 ) ) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("SetTransmitTargets"), hr );
        goto LCleanReturn;
    }

    // Get the sound device config and extract if its half duplex
    DWORD dwSize;
    dwSize = 0;
    hr = m_pVoiceClient->GetSoundDeviceConfig( pdvSoundDeviceConfig, &dwSize );
    if( FAILED(hr) && hr != DVERR_BUFFERTOOSMALL )
    {
        DXTRACE_ERR_MSGBOX( TEXT("GetSoundDeviceConfig"), hr );
        goto LCleanReturn;
    }

    pdvSoundDeviceConfig = (DVSOUNDDEVICECONFIG*) new BYTE[ dwSize ];
    if( NULL == pdvSoundDeviceConfig )
    {
        hr = E_OUTOFMEMORY;
        DXTRACE_ERR_MSGBOX( TEXT("VoiceSessionConnect"), hr );
        goto LCleanReturn;
    }

    ZeroMemory( pdvSoundDeviceConfig, dwSize );
    pdvSoundDeviceConfig->dwSize = sizeof(DVSOUNDDEVICECONFIG);
    hr = m_pVoiceClient->GetSoundDeviceConfig( pdvSoundDeviceConfig, &dwSize );
    if( FAILED(hr) )
    {
        DXTRACE_ERR_MSGBOX( TEXT("GetSoundDeviceConfig"), hr );
        goto LCleanReturn;
    }

    m_bHalfDuplex = ( (pdvSoundDeviceConfig->dwFlags & DVSOUNDCONFIG_HALFDUPLEX) != 0 );
    
    hr = S_OK;

LCleanReturn:
    SAFE_DELETE_ARRAY( pdvSoundDeviceConfig );

    return hr;
}




//-----------------------------------------------------------------------------
// Name: ChangeVoiceClientSettings()
// Desc: Changes the client config to globals set by user choices 
//       in the config dlg box.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::ChangeVoiceClientSettings( DVCLIENTCONFIG* pdvClientConfig )
{
    HRESULT hr;

    if( m_pVoiceClient == NULL )
        return CO_E_NOTINITIALIZED;

    // Change the client config
    if( FAILED( hr = m_pVoiceClient->SetClientConfig( pdvClientConfig) ) )
        return DXTRACE_ERR( TEXT("SetClientConfig"), hr );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: VoiceSessionDisconnect()
// Desc: Disconnects from the DirectPlayVoice session
//       All clients should call this once to leave the voice session.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::VoiceSessionDisconnect()
{
    if( m_pVoiceClient )
    {
        m_pVoiceClient->Disconnect( DVFLAGS_SYNC );
        SAFE_RELEASE( m_pVoiceClient );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: VoiceSessionDestroy()
// Desc: Stops the DirectPlayVoice session
//       The host player should call this once to destroy the voice session.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::VoiceSessionDestroy()
{
    if( m_pVoiceServer )
    {
        m_pVoiceServer->StopSession( 0 );
        SAFE_RELEASE( m_pVoiceServer );
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DoVoiceSetupDialog()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CNetVoice::DoVoiceSetupDialog( HINSTANCE hInst, HWND hWndParent, GUID* pguidDVSessionCT, DVCLIENTCONFIG* pdvClientConfig )
{
    if( NULL == pguidDVSessionCT || NULL == pdvClientConfig )
        return E_INVALIDARG;

    m_guidDVSessionCT = *pguidDVSessionCT;
    m_dvClientConfig = *pdvClientConfig;

    // Ask user to change m_dvClientConfig, g_guidDVSessionCT
    DWORD dwResult = (DWORD)DialogBox( hInst, MAKEINTRESOURCE(IDD_VOICE_SETUP), 
                                       hWndParent, (DLGPROC) StaticVoiceConfigDlgProc );
    if( dwResult == IDCANCEL )
        return DVERR_USERCANCEL;

    *pguidDVSessionCT = m_guidDVSessionCT;
    *pdvClientConfig = m_dvClientConfig;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: StaticVoiceConfigDlgProc()
// Desc: Static callback helper to call into CNetVoice class
//-----------------------------------------------------------------------------
INT_PTR CALLBACK CNetVoice::StaticVoiceConfigDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    if( g_pNetVoice )
        return g_pNetVoice->VoiceConfigDlgProc( hDlg, msg, wParam, lParam );
    return 0;
}





//-----------------------------------------------------------------------------
// Name: VoiceConfigDlgProc()
// Desc: Prompt the user for DirectPlayVoice setup options
//-----------------------------------------------------------------------------
INT_PTR CALLBACK CNetVoice::VoiceConfigDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    DWORD dwSliderPos;

    switch( msg ) 
    {
        case WM_INITDIALOG:
            // Set the range on the sliders
            SendDlgItemMessage( hDlg, IDC_PLAYBACK_SLIDER,       TBM_SETRANGE, FALSE, MAKELONG( 0, 100 ) );
            SendDlgItemMessage( hDlg, IDC_RECORD_SLIDER,         TBM_SETRANGE, FALSE, MAKELONG( 0, 100 ) );
            SendDlgItemMessage( hDlg, IDC_QUALITY_SLIDER,        TBM_SETRANGE, FALSE, MAKELONG( DVBUFFERQUALITY_MIN, DVBUFFERQUALITY_MAX ) );
            SendDlgItemMessage( hDlg, IDC_THRESHOLD_SLIDER,    TBM_SETRANGE, FALSE, MAKELONG( DVTHRESHOLD_MIN,  DVTHRESHOLD_MAX ) );
            SendDlgItemMessage( hDlg, IDC_AGGRESSIVENESS_SLIDER, TBM_SETRANGE, FALSE, MAKELONG( DVBUFFERAGGRESSIVENESS_MIN, DVBUFFERAGGRESSIVENESS_MAX ) );

            // Setup the dialog based on the globals 

            // Set the playback controls
            if( m_dvClientConfig.lPlaybackVolume == DVPLAYBACKVOLUME_DEFAULT )
            {
                CheckRadioButton( hDlg, IDC_PLAYBACK_DEFAULT, IDC_PLAYBACK_SET, IDC_PLAYBACK_DEFAULT );
            }
            else
            {
                dwSliderPos = (DWORD) ( ( m_dvClientConfig.lPlaybackVolume - DSBVOLUME_MIN ) * 
                                          100.0f / (DSBVOLUME_MAX-DSBVOLUME_MIN) );
                CheckRadioButton( hDlg, IDC_PLAYBACK_DEFAULT, IDC_PLAYBACK_SET, IDC_PLAYBACK_SET );
                SendDlgItemMessage( hDlg, IDC_PLAYBACK_SLIDER, TBM_SETPOS, TRUE, dwSliderPos );
            }

            // Set the record controls
            if( m_dvClientConfig.dwFlags & DVCLIENTCONFIG_AUTORECORDVOLUME )
            {
                CheckRadioButton( hDlg, IDC_RECORD_DEFAULT, IDC_RECORD_AUTO, IDC_RECORD_AUTO );
            }
            else if( m_dvClientConfig.lRecordVolume == DVPLAYBACKVOLUME_DEFAULT )
            {
                CheckRadioButton( hDlg, IDC_RECORD_DEFAULT, IDC_RECORD_AUTO, IDC_RECORD_DEFAULT );
            }
            else
            {
                dwSliderPos = (DWORD) ( ( m_dvClientConfig.lRecordVolume - DSBVOLUME_MIN ) * 
                                          100.0f / (DSBVOLUME_MAX-DSBVOLUME_MIN) );
                CheckRadioButton( hDlg, IDC_RECORD_DEFAULT, IDC_RECORD_AUTO, IDC_RECORD_SET );
                SendDlgItemMessage( hDlg, IDC_RECORD_SLIDER, TBM_SETPOS, TRUE, dwSliderPos );
            }

            // Set the threshold controls
            if( m_dvClientConfig.dwFlags & DVCLIENTCONFIG_AUTOVOICEACTIVATED )
            {
                CheckRadioButton( hDlg, IDC_THRESHOLD_DEFAULT, IDC_THRESHOLD_AUTO, IDC_THRESHOLD_AUTO );
            }
            else if( m_dvClientConfig.dwThreshold == DVTHRESHOLD_DEFAULT )
            {
                CheckRadioButton( hDlg, IDC_THRESHOLD_DEFAULT, IDC_THRESHOLD_AUTO, IDC_THRESHOLD_DEFAULT );
            }
            else
            {
                CheckRadioButton( hDlg, IDC_THRESHOLD_DEFAULT, IDC_THRESHOLD_AUTO, IDC_THRESHOLD_SET );
                SendDlgItemMessage( hDlg, IDC_THRESHOLD_SLIDER, TBM_SETPOS, TRUE, m_dvClientConfig.dwThreshold );
            }

            // Set the quality controls
            if( m_dvClientConfig.dwBufferQuality == DVBUFFERQUALITY_DEFAULT )
            {
                CheckRadioButton( hDlg, IDC_QUALITY_DEFAULT, IDC_QUALITY_SET, IDC_QUALITY_DEFAULT );
            }
            else
            {
                CheckRadioButton( hDlg, IDC_QUALITY_DEFAULT, IDC_QUALITY_SET, IDC_QUALITY_SET );
                SendDlgItemMessage( hDlg, IDC_QUALITY_SLIDER, TBM_SETPOS, TRUE, m_dvClientConfig.dwBufferQuality );
            }

            // Set the aggressiveness controls
            if( m_dvClientConfig.dwBufferAggressiveness == DVBUFFERAGGRESSIVENESS_DEFAULT )
            {
                CheckRadioButton( hDlg, IDC_AGGRESSIVENESS_DEFAULT, IDC_AGGRESSIVENESS_SET, IDC_AGGRESSIVENESS_DEFAULT );
            }
            else
            {
                CheckRadioButton( hDlg, IDC_AGGRESSIVENESS_DEFAULT, IDC_AGGRESSIVENESS_SET, IDC_AGGRESSIVENESS_SET );
                SendDlgItemMessage( hDlg, IDC_AGGRESSIVENESS_SLIDER, TBM_SETPOS, TRUE, m_dvClientConfig.dwBufferAggressiveness );
            }

            if( !m_bHostPlayer || m_bVoiceSessionInProgress )
            {
                // We are are not the host player then disable all the server only options 
                EnableWindow( GetDlgItem( hDlg, IDC_COMPRESSION_COMBO ), FALSE );
                EnableWindow( GetDlgItem( hDlg, IDC_SESSIONCOMPRESION_GROUP ), FALSE );
            }
            else
            {
                VoiceConfigEnumCompressionCodecs( hDlg );   
                EnableWindow( GetDlgItem( hDlg, IDCANCEL ), FALSE );
            }

            return TRUE;

        case WM_NOTIFY:
            #ifndef NM_RELEASEDCAPTURE
                #define NM_RELEASEDCAPTURE (NM_FIRST-16)
            #endif
            if( ((LPNMHDR) lParam)->code == NM_RELEASEDCAPTURE )
            {
                // If this is a release capture from a slider, then automatically check 
                // its 'Set' radio button.
                switch( ((LPNMHDR) lParam)->idFrom )
                {
                case IDC_PLAYBACK_SLIDER:
                    CheckRadioButton( hDlg, IDC_PLAYBACK_DEFAULT, IDC_PLAYBACK_SET, IDC_PLAYBACK_SET );
                    break;
    
                case IDC_RECORD_SLIDER:
                    CheckRadioButton( hDlg, IDC_RECORD_DEFAULT, IDC_RECORD_AUTO, IDC_RECORD_SET );
                    break;
    
                case IDC_THRESHOLD_SLIDER:
                    CheckRadioButton( hDlg, IDC_THRESHOLD_DEFAULT, IDC_THRESHOLD_AUTO, IDC_THRESHOLD_SET );
                    break;
    
                case IDC_QUALITY_SLIDER:
                    CheckRadioButton( hDlg, IDC_QUALITY_DEFAULT, IDC_QUALITY_SET, IDC_QUALITY_SET );
                    break;
    
                case IDC_AGGRESSIVENESS_SLIDER:
                    CheckRadioButton( hDlg, IDC_AGGRESSIVENESS_DEFAULT, IDC_AGGRESSIVENESS_SET, IDC_AGGRESSIVENESS_SET );
                    break;
                }
            }
            return TRUE;            

        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                case IDOK:
                    VoiceConfigDlgOnOK( hDlg );
                    return TRUE;

                case IDCANCEL:
                    EndDialog( hDlg, IDCANCEL );
                    return TRUE;
            }
            break;

        case WM_DESTROY:
        {
            GUID* pGuid;
            int nCount = (int)SendDlgItemMessage( hDlg, IDC_COMPRESSION_COMBO, CB_GETCOUNT, 0, 0 );
            for( int i=0; i<nCount; i++ )
            {
                pGuid = (LPGUID) SendDlgItemMessage( hDlg, IDC_COMPRESSION_COMBO, CB_GETITEMDATA, i, 0 );
                SAFE_DELETE( pGuid );
            }
            break;
        }
    }

    return FALSE; // Didn't handle message
}




//-----------------------------------------------------------------------------
// Name: VoiceConfigEnumCompressionCodecs()
// Desc: Asks DirectPlayVoice what voice compression codecs are availible
//       and fills the combo box thier names and GUIDs.
//-----------------------------------------------------------------------------
HRESULT CNetVoice::VoiceConfigEnumCompressionCodecs( HWND hDlg )
{
    LPDIRECTPLAYVOICECLIENT pVoiceClient        = NULL;
    LPDVCOMPRESSIONINFO     pdvCompressionInfo  = NULL;
    LPGUID  pGuid         = NULL;
    LPBYTE  pBuffer       = NULL;
    DWORD   dwSize        = 0;
    DWORD   dwNumElements = 0;
    HWND    hPulldown     = GetDlgItem( hDlg, IDC_COMPRESSION_COMBO );
    HRESULT hr;
    LONG    lIndex;
    LONG    lFirst = 0;

    CoInitializeEx( NULL, COINIT_MULTITHREADED );
    if( FAILED( hr = CoCreateInstance( CLSID_DirectPlayVoiceClient, NULL, 
                                       CLSCTX_INPROC_SERVER, IID_IDirectPlayVoiceClient, 
                                       (VOID**) &pVoiceClient ) ) )
        return DXTRACE_ERR( TEXT("CoCreateInstance"), hr );

    hr = pVoiceClient->GetCompressionTypes( pBuffer, &dwSize, &dwNumElements, 0 );
    if( hr != DVERR_BUFFERTOOSMALL && FAILED(hr) )
        return DXTRACE_ERR( TEXT("GetCompressionTypes"), hr );

    pBuffer = new BYTE[dwSize];
    if( FAILED( hr = pVoiceClient->GetCompressionTypes( pBuffer, &dwSize, 
                                                        &dwNumElements, 0 ) ) )
        return DXTRACE_ERR( TEXT("GetCompressionTypes"), hr );

    SAFE_RELEASE( pVoiceClient );
    CoUninitialize();

    pdvCompressionInfo = (LPDVCOMPRESSIONINFO) pBuffer;
    for( DWORD dwIndex = 0; dwIndex < dwNumElements; dwIndex++ )
    {
        TCHAR strName[MAX_PATH];
        DXUtil_ConvertWideStringToGenericCch( strName, 
                                           pdvCompressionInfo[dwIndex].lpszName, MAX_PATH );

        lIndex = (LONG)SendMessage( hPulldown, CB_ADDSTRING, 0, (LPARAM) strName );

        pGuid = new GUID;
        (*pGuid) = pdvCompressionInfo[dwIndex].guidType;
        SendMessage( hPulldown, CB_SETITEMDATA, lIndex, (LPARAM) pGuid );

        if( pdvCompressionInfo[dwIndex].guidType == DPVCTGUID_SC03 )
            lFirst = lIndex;
    }

    SAFE_DELETE_ARRAY( pBuffer );
    SendMessage( hPulldown, CB_SETCURSEL, lFirst, 0 );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: VoiceConfigDlgOnOK()
// Desc: Figure out all the DirectPlayVoice setup params from the dialog box,
//       and store them in global vars.
//-----------------------------------------------------------------------------
VOID CNetVoice::VoiceConfigDlgOnOK( HWND hDlg )
{
    DWORD dwSliderPos;

    m_dvClientConfig.dwFlags = 0;

    // Figure out the playback params
    if( IsDlgButtonChecked( hDlg, IDC_PLAYBACK_DEFAULT ) )
    {
        m_dvClientConfig.lPlaybackVolume = DVPLAYBACKVOLUME_DEFAULT;
    }
    else 
    {
        dwSliderPos = (DWORD)SendDlgItemMessage( hDlg, IDC_PLAYBACK_SLIDER, TBM_GETPOS, 0, 0 );
        m_dvClientConfig.lPlaybackVolume = DSBVOLUME_MIN + (LONG) ( dwSliderPos / 100.0f * 
                                                                    (DSBVOLUME_MAX-DSBVOLUME_MIN) );
    }

    // Figure out the record params
    if( IsDlgButtonChecked( hDlg, IDC_RECORD_AUTO ) )
    {
        m_dvClientConfig.lRecordVolume = 0;
        m_dvClientConfig.dwFlags       |= DVCLIENTCONFIG_AUTORECORDVOLUME;
    }
    else if( IsDlgButtonChecked( hDlg, IDC_RECORD_DEFAULT ) )
    {
        m_dvClientConfig.lRecordVolume = DVPLAYBACKVOLUME_DEFAULT;
    }
    else 
    {
        dwSliderPos = (DWORD)SendDlgItemMessage( hDlg, IDC_RECORD_SLIDER, TBM_GETPOS, 0, 0 );
        m_dvClientConfig.lRecordVolume = DSBVOLUME_MIN + (LONG) ( dwSliderPos / 100.0f * 
                                                                  (DSBVOLUME_MAX-DSBVOLUME_MIN) );
    }

    // Figure out the threshold params
    if( IsDlgButtonChecked( hDlg, IDC_THRESHOLD_AUTO ) )
    {
        m_dvClientConfig.dwThreshold = DVTHRESHOLD_UNUSED;
        m_dvClientConfig.dwFlags       |= DVCLIENTCONFIG_AUTOVOICEACTIVATED;
    }
    else if( IsDlgButtonChecked( hDlg, IDC_THRESHOLD_DEFAULT ) )
    {
        m_dvClientConfig.dwThreshold = DVTHRESHOLD_DEFAULT;
        m_dvClientConfig.dwFlags       |= DVCLIENTCONFIG_MANUALVOICEACTIVATED;
    }
    else 
    {
        dwSliderPos = (DWORD)SendDlgItemMessage( hDlg, IDC_THRESHOLD_SLIDER, TBM_GETPOS, 0, 0 );
        m_dvClientConfig.dwThreshold = dwSliderPos;
        m_dvClientConfig.dwFlags       |= DVCLIENTCONFIG_MANUALVOICEACTIVATED;
    }

    // Figure out the quality params
    if( IsDlgButtonChecked( hDlg, IDC_QUALITY_DEFAULT ) )
    {
        m_dvClientConfig.dwBufferQuality = DVBUFFERQUALITY_DEFAULT;
    }
    else 
    {
        dwSliderPos = (DWORD)SendDlgItemMessage( hDlg, IDC_QUALITY_SLIDER, TBM_GETPOS, 0, 0 );
        m_dvClientConfig.dwBufferQuality = dwSliderPos;
    }

    // Figure out the aggressiveness params
    if( IsDlgButtonChecked( hDlg, IDC_AGGRESSIVENESS_DEFAULT ) )
    {
        m_dvClientConfig.dwBufferAggressiveness = DVBUFFERAGGRESSIVENESS_DEFAULT;
    }
    else 
    {
        dwSliderPos = (DWORD)SendDlgItemMessage( hDlg, IDC_AGGRESSIVENESS_SLIDER, TBM_GETPOS, 0, 0 );
        m_dvClientConfig.dwBufferAggressiveness = dwSliderPos;
    }

    if( m_bHostPlayer )
    {
        // Figure out the compression codec
        LONG lCurSelection;
        LPGUID pGuidCT;

        lCurSelection = (LONG)SendDlgItemMessage( hDlg, IDC_COMPRESSION_COMBO, CB_GETCURSEL, 0, 0 );
        if( lCurSelection != CB_ERR )
        {
            pGuidCT = (LPGUID) SendDlgItemMessage( hDlg, IDC_COMPRESSION_COMBO, 
                                                   CB_GETITEMDATA, lCurSelection, 0 );
            if( pGuidCT != NULL )
                m_guidDVSessionCT = (*pGuidCT);
        }
    }

    EndDialog( hDlg, IDOK );
}
