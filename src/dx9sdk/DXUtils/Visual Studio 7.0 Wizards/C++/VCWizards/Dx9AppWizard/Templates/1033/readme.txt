Classes created:    
[!if D3D]
[!if WINDOW]
    CMyD3DApplication in [!output SAFE_PROJECT_NAME].cpp
[!else]
    Application: CApp and CAppForm in [!output SAFE_PROJECT_NAME].cpp
[!endif]
    Base Application: CD3DApplication in D3DApp.cpp
    Direct3D Settings: CD3DSettingsDialog in D3DSettings.cpp
    Direct3D Enumeration: CD3DEnumeration in D3DEnumeration.cpp
[!else]
[!if WINDOW]
    Application in [!output SAFE_PROJECT_NAME].cpp
[!else]
    Application: C[!output SAFE_PROJECT_NAME]App in [!output SAFE_PROJECT_NAME].cpp
    Dialog: C[!output SAFE_PROJECT_NAME]Dlg in [!output SAFE_PROJECT_NAME]Dlg.cpp
[!endif]
[!endif]
[!if D3DFONT]
    3D Font Texture Support: CD3DFont in D3DFont.cpp
[!endif]
[!if X_FILE]
    .X File Support: CD3DFile in D3DFile.cpp
[!endif]
[!if DINPUT]
    DirectInput Support: CInputDeviceManager in DIUtil.cpp
[!endif]
[!if DMUSIC]
    DirectMusic Support: CMusicManager in DMUtil.cpp
[!endif]
[!if DSOUND]
    DirectSound Support: CSoundManager in DSUtil.cpp
[!endif]
[!if DPLAY]
    DirectPlay Peer-to-Peer Support: CNetConnectWizard in NetConnect.cpp
[!endif]
[!if DPLAYVOICE]
    DirectPlay Voice Support: CNetVoice in NetVoice.cpp
[!endif]
[!if D3D]
    Generic Direct3D Support in D3DUtil.cpp
[!endif]
    Generic DirectX Support in DXUtil.cpp
