'-----------------------------------------------------------------------------
' File: DPlayConnect.vb
'
' Desc: Application class for the DirectPlay samples framework.
'
' Copyright (c) Microsoft Corporation. All rights reserved.
'-----------------------------------------------------------------------------
Imports System
Imports System.Collections
Imports System.Windows.Forms
Imports System.Threading
Imports System.Timers
Imports Microsoft.DirectX
Imports Microsoft.DirectX.DirectPlay
Imports System.Runtime.InteropServices

 _

'/ <summary>
'/ The connection wizard will allow our users to pick a service provider,
'/ and then connect to an existing application, or create a new one as the host.
'/ </summary>
Public Class ConnectWizard
    Private peerObject As Peer
    Private deviceAddress As Address

    Private serviceProviderForm As ChooseServiceProviderForm
    Private createJoinForm As CreateJoinForm

    Private serviceProviderGuid As Guid
    Private usersname As String
    Private samplesname As String
    Private isInSession As Boolean = False
    Private isUserHost As Boolean = False
    Private port As Integer = 0

    Private appGuid As Guid


    '/ <summary>
    '/ Constructor
    '/ </summary>
    '/ <param name="peer"></param>
    '/ <param name="applicationGuid"></param>
    '/ <param name="sampleName"></param>
    Public Sub New(ByVal peer As Peer, ByVal application As Guid, ByVal sampleName As String)
        peerObject = peer
        appGuid = application
        sampleName = sampleName
    End Sub 'New


    '/ <summary>
    '/ The guid for the current service provider
    '/ </summary>
    Public Property ServiceProvider() As Guid
        Get
            Return serviceProviderGuid
        End Get
        Set(ByVal Value As Guid)
            serviceProviderGuid = Value
        End Set
    End Property



    '/ <summary>
    '/ The game's default port number
    '/ </summary>
    Public Property DefaultPort() As Integer
        Get
            Return port
        End Get
        Set(ByVal Value As Integer)
            port = Value
        End Set
    End Property



    '/ <summary>
    '/ Am I the host
    '/ </summary>
    Public Property IsHost() As Boolean
        Get
            Return isUserHost
        End Get
        Set(ByVal Value As Boolean)
            isUserHost = Value
        End Set
    End Property


    '/ <summary>
    '/ The username
    '/ </summary>
    Public Property Username() As String
        Get
            Return usersname
        End Get
        Set(ByVal Value As String)
            usersname = Value
        End Set
    End Property

    '/ <summary>
    '/ The sample name
    '/ </summary>

    Public ReadOnly Property SampleName() As String
        Get
            Return samplesname
        End Get
    End Property

    '/ <summary>
    '/ The applications guid
    '/ </summary>

    Public ReadOnly Property ApplicationGuid() As Guid
        Get
            Return appGuid
        End Get
    End Property
    '/ <summary>
    '/ Are we in a session
    '/ </summary>

    Public Property InSession() As Boolean
        Get
            Return isInSession
        End Get
        Set(ByVal Value As Boolean)
            isInSession = Value
        End Set
    End Property



    '/ <summary>
    '/ Returns true if the given provider requires a port component
    '/ </summary>
    '/ <param name="provider">ServiceProvider Guid</param>
    Public Shared Function ProviderRequiresPort(ByVal provider As Guid) As Boolean
        Return Not (provider.Equals(Address.ServiceProviderSerial) Or _
                    provider.Equals(Address.ServiceProviderModem) Or _
                    provider.Equals(Address.ServiceProviderBlueTooth))
    End Function

    '/ <summary>
    '/ Handler for when our form is disposed
    '/ </summary>
    Public Sub FormDisposed(ByVal sender As Object, ByVal e As EventArgs)
        If sender Is createJoinForm Then
            createJoinForm = Nothing
        End If
        If sender Is serviceProviderForm Then
            serviceProviderForm = Nothing
        End If
    End Sub 'FormDisposed


    '/ <summary>
    '/ Set the user information 
    '/ </summary>
    Public Sub SetUserInfo()
        'Before we call host, let's actually call SetPeerInformation
        Dim myinformation As New PlayerInformation()
        myinformation.Name = Username

        peerObject.SetPeerInformation(myinformation, SyncFlags.PeerInformation)
    End Sub 'SetUserInfo



    '/ <summary>
    '/ Show the service providers form
    '/ </summary>
    '/ <returns>True if a service provider was picked, false otherwise</returns>
    Public Function DoShowServiceProviders() As Boolean
        If serviceProviderForm Is Nothing Then
            Username = Nothing
            serviceProviderForm = New ChooseServiceProviderForm(peerObject, Me)
            AddHandler serviceProviderForm.Disposed, AddressOf Me.FormDisposed
        End If
        If serviceProviderForm.ShowDialog() = DialogResult.OK Then
            Return True
        End If
        ' The didn't hit ok
        Return False
    End Function 'DoShowServiceProviders



    '/ <summary>
    '/ Show the create or join screen
    '/ </summary>
    '/ <returns>True if we will be in a session, false otherwise</returns>
    Public Function DoCreateJoinGame() As Boolean
        If deviceAddress Is Nothing Then
            deviceAddress = New Address()
        End If
        If createJoinForm Is Nothing Then
            createJoinForm = New CreateJoinForm(peerObject, deviceAddress, Me)
            AddHandler createJoinForm.Disposed, AddressOf Me.FormDisposed
        End If

        'Set the address's service provider (this will be the device address)
        deviceAddress.ServiceProvider = serviceProviderGuid
        Dim drCreateJoin As DialogResult = createJoinForm.ShowDialog()
        If drCreateJoin = DialogResult.Cancel Then
            Return False
        End If
        Me.isUserHost = drCreateJoin = DialogResult.Yes
        Return True
    End Function 'DoCreateJoinGame




    '/ <summary>
    '/ Start the wizard
    '/ </summary>
    '/ <returns>True if we are in a session, false otherwise</returns>
    Public Function StartWizard() As Boolean
        isInSession = False

        While Me.DoShowServiceProviders()
            'Now let's create a game or join a session
            If Me.DoCreateJoinGame() Then
                ' A game has been created or joined now, set our flag
                isInSession = True
                Exit While
            End If
        End While
        Return isInSession
    End Function 'StartWizard
End Class 'ConnectWizard
