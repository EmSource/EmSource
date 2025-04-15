//-----------------------------------------------------------------------------
// File: NetVoice.h
//
// Desc: 
//-----------------------------------------------------------------------------
#ifndef NETVOICE_H
#define NETVOICE_H


#include <windows.h>
#include <dvoice.h>


class CNetVoice
{
public:
    CNetVoice( LPDVMESSAGEHANDLER pfnDirectPlayClientVoiceMessageHandler,
               LPDVMESSAGEHANDLER pfnDirectPlayServerVoiceMessageHandler );
    virtual ~CNetVoice();

    HRESULT Init( HWND hDlg, BOOL bCreateSession, BOOL bConnectToSession, 
                  LPUNKNOWN pDirectPlay, DWORD dwSessionType, GUID* pGuidCT, 
                  DVCLIENTCONFIG* pdvClientConfig, LPDIRECTSOUND lpds = NULL );
    HRESULT Free();

    HRESULT HostMigrate( LPDIRECTPLAYVOICESERVER pdvServerInterface );
    bool    IsHalfDuplex() { return m_bHalfDuplex; }
    HRESULT ChangeVoiceClientSettings( DVCLIENTCONFIG* pdvClientConfig );

    LPDIRECTPLAYVOICECLIENT GetVoiceClient() { return m_pVoiceClient; }
    LPDIRECTPLAYVOICESERVER GetVoiceServer() { return m_pVoiceServer; }

    HRESULT DoVoiceSetupDialog( HINSTANCE hInst, HWND hWndParent, GUID* pguidDVSessionCT, DVCLIENTCONFIG* pdvClientConfig );

protected:  
    LPDIRECTPLAYVOICECLIENT m_pVoiceClient;
    LPDIRECTPLAYVOICESERVER m_pVoiceServer;                                                                             
    LPDVMESSAGEHANDLER m_pfnDirectPlayClientVoiceMessageHandler;
    LPDVMESSAGEHANDLER m_pfnDirectPlayServerVoiceMessageHandler;

    HRESULT VoiceSessionCreate( LPUNKNOWN pDirectPlay, DWORD dwSessionType, GUID* pGuidCT );
    HRESULT VoiceSessionTestAudioSetup( HWND hDlg );
    HRESULT VoiceSessionConnect( HWND hDlg, LPUNKNOWN pDirectPlay, 
                                 DVCLIENTCONFIG* pdvClientConfig, LPDIRECTSOUND lpds = NULL );
    HRESULT VoiceSessionDisconnect();
    HRESULT VoiceSessionDestroy();

    bool    m_bHalfDuplex;

    // Voice settings dialog vars and functions
    BOOL    m_bVoiceSessionInProgress;   // True if voice has been init'ed
    DVCLIENTCONFIG m_dvClientConfig;     // Voice client config
    GUID    m_guidDVSessionCT;           // GUID for chosen voice compression
    BOOL    m_bHostPlayer;               // TRUE if host player

    INT_PTR CALLBACK VoiceConfigDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
    static INT_PTR CALLBACK StaticVoiceConfigDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );

    HRESULT VoiceConfigEnumCompressionCodecs( HWND hDlg );
    VOID    VoiceConfigDlgOnOK( HWND hDlg );
};


#endif // NETVOICE_H

