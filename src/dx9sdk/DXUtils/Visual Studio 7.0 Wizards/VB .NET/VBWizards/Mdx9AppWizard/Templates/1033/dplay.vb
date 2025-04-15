Imports System
Imports System.Collections
Imports System.Windows.Forms
Imports Microsoft.DirectX
Imports Microsoft.DirectX.DirectPlay
[!if USE_VOICE]
Imports Voice = Microsoft.DirectX.DirectPlay.Voice
[!endif]

'/ <summary>
'/ The Class that houses DirectPlay code for the application.
'/ </summary>
Public Class PlayClass
    Private message As MessageDelegate = Nothing

[!if GRAPHICSTYPE_DIRECT3D]
    Private parent As GraphicsClass = Nothing
[!else]
    Private parent As MainClass = Nothing
[!endif]

    Public  peerObject As Peer = Nothing
[!if USE_VOICE]
    Private voiceClient As Voice.Client = Nothing
    Private voiceServer As Voice.Server = Nothing
    Private voiceWizard As VoiceWizard = Nothing
[!endif]
    Private Connect As ConnectWizard = Nothing
    Private PlayerList As ArrayList = New ArrayList()
    Private LocalPlayerID As Integer = 0
[!if GRAPHICSTYPE_DIRECT3D]
[!if USE_VOICE]
    Public AppGuid As Guid = New Guid("876a3036-ffd7-46bc-9209-b42f617b9bF0")
[!else]
    Public AppGuid As Guid = New Guid("{876a3036-ffd7-46bc-9209-b42f617b9bF1}")
[!endif]
[!endif]
[!if GRAPHICSTYPE_DIRECTDRAW || GRAPHICSTYPE_NOGRAPHICS]
[!if USE_VOICE]
    Public AppGuid As Guid = New Guid("{876a3036-ffd7-46bc-9209-b42f617b9bF2}")
[!else]
    Public AppGuid As Guid = New Guid("{876a3036-ffd7-46bc-9209-b42f617b9bF3}")
[!endif]
[!endif]

    Public Structure Players
        Public dpnID As Integer 
        Public Name As string 
        Public Sub New(id As Integer , n As string)
            dpnID = id 
            Name = n
        End Sub
    End Structure

[!if GRAPHICSTYPE_DIRECT3D]
    Public Sub New(parent As GraphicsClass)
[!else]
    Public Sub New(parent As MainClass)
[!endif]
        Me.parent = parent
        Me.peerObject = peerObject
        Me.message = New MessageDelegate(AddressOf parent.MessageArrived)

        peerObject = New Peer()
        ' First set up our event handlers (We only need events for the ones we care about)
        AddHandler peerObject.PlayerCreated, AddressOf Me.PlayerCreated
        AddHandler peerObject.PlayerDestroyed, AddressOf  Me.PlayerDestroyed
        AddHandler peerObject.HostMigrated, AddressOf Me.HostMigrated
        AddHandler peerObject.Receive, AddressOf Me.DataReceived
        AddHandler peerObject.SessionTerminated, AddressOf Me.SessionTerminated

        Connect = New ConnectWizard(peerObject, AppGuid, "[!output PROJECT_NAME]")
        If (Not Connect.StartWizard()) Then
            Me.parent.Show()
            MessageBox.Show("DirectPlay initialization was incomplete. Application will terminate.")
            Throw New DirectXException()
        End If
[!if USE_VOICE]
        voiceClient = New Voice.Client(peerObject)
        voiceWizard = New VoiceWizard()

        If (Connect.IsHost) Then
            'create the voice server
            voiceServer = New Voice.Server(peerObject)

            'init the voice server
            voiceWizard.InitVoiceHost(peerObject, voiceServer, voiceClient, parent)
        Else
            ' Connect as a client.
            voiceWizard.InitVoiceClient(peerObject, voiceClient, parent)
        End If
[!endif]
    End Sub

    Public Sub WriteMessage(msg As Byte)
        Dim packet As NetworkPacket = New NetworkPacket()

        packet.Write(msg)
        peerObject.SendTo(PlayerID.AllPlayers, packet, 0, SendFlags.Guaranteed)
    End Sub

    #Region "DirectPlayEvents"
    '/ <summary>
    ' These are the events the app will handle
    ' when DPlay fires them.
    '/ </summary>
    Private Sub PlayerCreated(sender As Object, dpMessage As PlayerCreatedEventArgs)
        ' Get the PlayerInformation and store it 
        Dim dpPeer As PlayerInformation = peerObject.GetPeerInformation(dpMessage.Message.PlayerID)
        Dim oPlayer As Players = New Players(dpMessage.Message.PlayerID,dpPeer.Name)
        ' We lock the data here since it is shared across multiple threads.
        SyncLock(PlayerList)
            PlayerList.Add(oPlayer)
        End SyncLock
        ' Save Me player id if it's ourselves
        If (dpPeer.Local)
            LocalPlayerID = dpMessage.Message.PlayerID
        End If
    End Sub
    Private Sub PlayerDestroyed(sender As Object, dpMessage As PlayerDestroyedEventArgs)
        ' Remove Me player from our list
        ' We lock the data here since it is shared across multiple threads.
        SyncLock (PlayerList)
            Dim player As Players 
            For Each player In PlayerList
                If (dpMessage.Message.PlayerID = player.dpnID)
                    PlayerList.Remove(player)
                    Exit For
                End If
            Next
        End SyncLock
    End Sub
    Private Sub HostMigrated(sender As Object, dpMessage As HostMigratedEventArgs)
        If (LocalPlayerID = dpMessage.Message.NewHostID) 
            ' This application instance is the New host, update the UI
            parent.Text += " (HOST)"
        End If
    End Sub
    Private Sub DataReceived(sender As Object, dpMessage As ReceiveEventArgs)
        SyncLock(Me)
            Dim data as Byte = dpMessage.Message.ReceiveData.Read(GetType(Byte))
            message(data)
        End SyncLock
    End Sub
    Private Sub SessionTerminated(sender As Object, dpMessage As SessionTerminatedEventArgs)
        ' This session is being terminated, let the user know
        If (dpMessage.Message.ResultCode = ResultCode.HostTerminatedSession)
            MessageBox.Show("The Host has terminated Me session.  This sample will now exit.", "Exiting", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Else
            MessageBox.Show("The session has been lost.  This sample will now exit.", "Exiting", MessageBoxButtons.OK, MessageBoxIcon.Information)
        End If

        ' This will post a message on the main thread to shut down our form
        parent.BeginInvoke(New PeerCloseCallback(AddressOf parent.PeerClose))
    End Sub
    #End Region
End Class