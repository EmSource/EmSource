'----------------------------------------------------------------------------
' File: VoiceConnect.vb
'
' Desc: The main file for VoiceConnect that shows how use DirectPlay along 
'       with DirectPlayVoice to allow talking in a conference situation.
'
' Copyright (c) 2000-2002 Microsoft Corp. All rights reserved.
'-----------------------------------------------------------------------------
Imports System
Imports Microsoft.DirectX
Imports Voice = Microsoft.DirectX.DirectPlay.Voice
Imports Microsoft.DirectX.DirectPlay
Imports Microsoft.DirectX.DirectSound
Imports System.Windows.Forms
Imports System.Collections

 _

'/ <summary>
'/ Summary description for NetVoice.
'/ </summary>
Public Class VoiceWizard
    Private client As Voice.Client
    Private server As Voice.Server
    Private mConfigForm As DPlayVoiceConfigForm
    Private mClientConfig As Voice.ClientConfig
    Private mHalfDuplex, mInSession, mIsHost As Boolean




    Public Sub New()
        mClientConfig = New Voice.ClientConfig()
        mClientConfig.BufferAggressiveness = Voice.BufferAggressiveness.Default
        mClientConfig.BufferQuality = Voice.BufferQuality.Default
        mClientConfig.Flags = Voice.ClientConfigFlags.AutoVoiceActivated Or Voice.ClientConfigFlags.AutoRecordVolume
        mClientConfig.Threshold = Voice.Threshold.Default
        mClientConfig.NotifyPeriod = 0
        mClientConfig.PlaybackVolume = CInt(Voice.PlaybackVolume.Default)
        mClientConfig.RecordVolume = CInt(Voice.RecordVolume.Last)

        mConfigForm = New DPlayVoiceConfigForm()
        mInSession = False
        mIsHost = False
    End Sub 'New


    Public ReadOnly Property HalfDuplex() As Boolean
        Get
            Return mHalfDuplex
        End Get
    End Property

    Public ReadOnly Property IsHost() As Boolean
        Get
            Return mIsHost
        End Get
    End Property

    Public ReadOnly Property InSession() As Boolean
        Get
            Return mInSession
        End Get
    End Property


    Public Sub InitVoiceClient(ByVal dpp As Peer, ByVal dpvc As Voice.Client, ByVal wnd As Form)
        Try
            TestAudioSetup(wnd)

            'Audio Setup was successful, open the configuration form	
            mConfigForm.ShowDialog(mClientConfig, False)

            mClientConfig = mConfigForm.ClientConfig
            client = dpvc

            'connect to the voice session
            ConnectToVoiceSession(dpp, wnd)
        Catch e As Exception
            MessageBox.Show("Error attempting to connect to a Voice Server.  This sample will now exit.", "Exiting", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Throw e
        End Try
    End Sub 'InitVoiceClient


    Public Sub InitVoiceHost(ByVal host As Peer, ByVal dpvs As Voice.Server, ByVal dpvc As Voice.Client, ByVal wnd As Form)
        Try

            server = dpvs
            client = dpvc

            TestAudioSetup(wnd)

            'Audio Setup was successful, open the configuration form	
            mConfigForm.ShowDialog(mClientConfig, dpvs.CompressionTypes, False)
            If mConfigForm.DialogResult = DialogResult.Cancel Then
                Throw New Exception("Voice configuration cancelled")
            End If
            mClientConfig = mConfigForm.ClientConfig

            'create the voice session
            CreateVoiceSession(host, Voice.SessionType.Peer, mConfigForm.CompressionGuid)

            'Connect to the voice session
            ConnectToVoiceSession(host, wnd)
        Catch e As Exception
            MessageBox.Show("Error attempting to start Voice Server Session.  This sample will now exit.", "Exiting", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Throw e
        End Try
    End Sub 'InitVoiceHost


    Public Sub ShowClientSetupDialog(ByVal hWnd As IntPtr)
        Try
            Dim __unknown = New DPlayVoiceConfigForm()
            Try
                mConfigForm.ShowDialog(mClientConfig, mInSession)
                mClientConfig = mConfigForm.ClientConfig
                client.ClientConfig = mClientConfig
            Finally
                __unknown.Dispose()
            End Try
        Catch e As Exception
            Throw e
        End Try
    End Sub 'ShowClientSetupDialog


    Public Sub ChangeVoiceClientSettings(ByVal config As Voice.ClientConfig)
        Try
            client.ClientConfig = config
        Catch e As Exception
            Throw e
        End Try
    End Sub 'ChangeVoiceClientSettings


    Public Sub HostMigrate(ByVal dpvs As Voice.Server)
        server = dpvs
        mIsHost = True
    End Sub 'HostMigrate



    Protected Sub CreateVoiceSession(ByVal dpp As Peer, ByVal type As Voice.SessionType, ByVal compressionType As Guid)
        Try
            'set up session description for the voice server
            Dim sessionDesc As New Voice.SessionDescription()
            sessionDesc.BufferAggressiveness = Voice.BufferAggressiveness.Default
            sessionDesc.BufferQuality = Voice.BufferQuality.Default
            sessionDesc.Flags = 0
            sessionDesc.SessionType = type
            sessionDesc.GuidCompressionType = compressionType

            'start the session
            Try
                server.StartSession(sessionDesc)
                mIsHost = True
                mInSession = True
            Catch dxe As DirectXException
                Throw dxe
            End Try
        Catch e As Exception
            Throw e
        End Try
    End Sub 'CreateVoiceSession


    Protected Sub TestAudioSetup(ByVal wnd As Form)
        Try

            Dim test As New Voice.Test()
            Try
                test.CheckAudioSetup(DSoundHelper.DefaultPlaybackDevice, DSoundHelper.DefaultCaptureDevice, wnd, Voice.TestFlags.QueryOnly)
            Catch
                Try
                    test.CheckAudioSetup(DSoundHelper.DefaultPlaybackDevice, DSoundHelper.DefaultCaptureDevice, wnd, Voice.TestFlags.AllowBack)
                Catch dxeUser As DirectXException
                    Throw dxeUser
                End Try
            End Try

        Catch e As Exception
            Throw e
        End Try
    End Sub 'TestAudioSetup


    Protected Sub ConnectToVoiceSession(ByVal dpp As Peer, ByVal wnd As Form)
        Try
            Dim soundConfig As New Voice.SoundDeviceConfig()

            'Set sound config to defaults
            soundConfig.GuidPlaybackDevice = DSoundHelper.DefaultVoicePlaybackDevice
            soundConfig.GuidCaptureDevice = DSoundHelper.DefaultVoiceCaptureDevice
            soundConfig.Window = wnd

            'TODO: add error message for specific failures?
            'Connect to voice session
            client.Connect(soundConfig, mClientConfig, Voice.VoiceFlags.Sync)

            'set state
            mInSession = True

            'set transmit targets to all players
            Dim xmitTargets(0) As Integer
            xmitTargets(0) = CInt(PlayerID.AllPlayers)
            client.TransmitTargets = xmitTargets

            'get sound device config to check for half-duplex
            soundConfig = client.SoundDeviceConfig
            mHalfDuplex = (soundConfig.Flags And Voice.SoundConfigFlags.HalfDuplex) <> 0

        Catch e As Exception
            Throw e
        End Try
    End Sub 'ConnectToVoiceSession
End Class 'VoiceWizard
 _

'/ <summary>
'/ Summary description for DPlayVoiceConfigForm.
'/ </summary>
Public Class DPlayVoiceConfigForm
    Inherits System.Windows.Forms.Form
    Private groupBoxPlaybackVolume As System.Windows.Forms.GroupBox
    Private groupBoxClient As System.Windows.Forms.GroupBox
    Private groupBoxRecordVolume As System.Windows.Forms.GroupBox
    Private groupBoxThreshold As System.Windows.Forms.GroupBox
    Private groupBox2 As System.Windows.Forms.GroupBox
    Private CompressionTypeComboBox As System.Windows.Forms.ComboBox
    Private radioButtonPlaybackDefault As System.Windows.Forms.RadioButton
    Private radioButtonPlaybackSet As System.Windows.Forms.RadioButton
    Private WithEvents trackBarPlaybackVolume As System.Windows.Forms.TrackBar
    Private radioButtonRecordVolumeSet As System.Windows.Forms.RadioButton
    Private radioButtonRecordVolumeAuto As System.Windows.Forms.RadioButton

    '/ <summary>
    '/ Application Specific members
    '/ </summary>
    Private mSelectedCompressionGuid As Guid
    Private radioButtonThresholdAuto As System.Windows.Forms.RadioButton
    Private radioButtonThresholdSet As System.Windows.Forms.RadioButton
    Private radioButtonThresholdDefault As System.Windows.Forms.RadioButton
    Private WithEvents trackBarThreshold As System.Windows.Forms.TrackBar
    Private WithEvents trackBarRecordVolume As System.Windows.Forms.TrackBar
    Private groupBoxServer As System.Windows.Forms.GroupBox

    Private mConfig As Voice.ClientConfig
    Private mCompressionInfo() As Voice.CompressionInformation
    Private WithEvents buttonOK As System.Windows.Forms.Button
    Private WithEvents buttonCancel As System.Windows.Forms.Button

    Private mIsHost As Boolean
    Private radioButtonRecordVolumeDefault As System.Windows.Forms.RadioButton
    Private mInSession As Boolean


    Public ReadOnly Property CompressionGuid() As Guid
        Get
            Return mSelectedCompressionGuid
        End Get
    End Property


    Public ReadOnly Property ClientConfig() As Voice.ClientConfig
        Get
            Return mConfig
        End Get
    End Property


    Public Overloads Function ShowDialog(ByVal config As Voice.ClientConfig, ByVal inSession As Boolean) As DialogResult
        mConfig = config
        mCompressionInfo = Nothing
        mIsHost = False
        mInSession = inSession
        UpdateControls()
        Return Me.ShowDialog()
    End Function 'ShowDialog

    Public Overloads Function ShowDialog(ByVal config As Voice.ClientConfig, ByVal cInfo() As Voice.CompressionInformation, ByVal inSession As Boolean) As DialogResult
        mConfig = config
        mCompressionInfo = cInfo
        mIsHost = True
        mInSession = inSession
        UpdateControls()
        Return Me.ShowDialog()
    End Function 'ShowDialog


    Public Sub New()
        InitializeComponent()
    End Sub 'New


    Private Sub UpdateControls()
        If mConfig.PlaybackVolume = CInt(Voice.PlaybackVolume.Default) Then
            radioButtonPlaybackDefault.Checked = True
        Else
            radioButtonPlaybackSet.Checked = True
            trackBarPlaybackVolume.Value = CInt((mConfig.PlaybackVolume - CInt(Volume.Min)) * 100.0F / (Volume.Max - Volume.Min))
        End If

        ' Set the record controls
        If (mConfig.Flags And Voice.ClientConfigFlags.AutoRecordVolume) <> 0 Then
            radioButtonRecordVolumeAuto.Checked = True
        ElseIf mConfig.RecordVolume = CInt(Voice.PlaybackVolume.Default) Then
            radioButtonRecordVolumeDefault.Checked = True
        Else
            radioButtonRecordVolumeSet.Checked = True
            trackBarRecordVolume.Value = CInt((mConfig.RecordVolume - CInt(Volume.Min)) * 100.0F / (Volume.Max - Volume.Min))
        End If

        ' Set the threshold controls
        If (mConfig.Flags And Voice.ClientConfigFlags.AutoVoiceActivated) <> 0 Then
            radioButtonThresholdAuto.Checked = True
        ElseIf mConfig.Threshold = Voice.Threshold.Default Then
            radioButtonThresholdDefault.Checked = True
        Else
            radioButtonThresholdSet.Checked = True
            trackBarThreshold.Value = CInt((CInt(mConfig.Threshold) - CInt(Voice.Threshold.Min)) * 100.0F / (CInt(Voice.Threshold.Max) - CInt(Voice.Threshold.Min)))
        End If

        If mIsHost And Not mInSession Then
            Dim ci As Voice.CompressionInformation
            For Each ci In mCompressionInfo
                CompressionTypeComboBox.Items.Add(ci.Name)
                If ci.GuidType.Equals(Voice.CompressionGuid.Default) Then
                    CompressionTypeComboBox.SelectedIndex = CompressionTypeComboBox.Items.Count - 1
                End If
            Next ci
            mSelectedCompressionGuid = mCompressionInfo(0).GuidType

        Else
            'We are are either not the host player or we are in session
            'so we disable all the server only options
            CompressionTypeComboBox.Enabled = False
            groupBoxServer.Enabled = False
        End If
    End Sub 'UpdateControls


    '/ <summary>
    '/ Required method for Designer support - do not modify
    '/ the contents of this method with the code editor.
    '/ </summary>
    Private Sub InitializeComponent()
        Me.groupBoxPlaybackVolume = New System.Windows.Forms.GroupBox()
        Me.trackBarPlaybackVolume = New System.Windows.Forms.TrackBar()
        Me.radioButtonPlaybackSet = New System.Windows.Forms.RadioButton()
        Me.radioButtonPlaybackDefault = New System.Windows.Forms.RadioButton()
        Me.groupBoxClient = New System.Windows.Forms.GroupBox()
        Me.groupBoxThreshold = New System.Windows.Forms.GroupBox()
        Me.radioButtonThresholdAuto = New System.Windows.Forms.RadioButton()
        Me.trackBarThreshold = New System.Windows.Forms.TrackBar()
        Me.radioButtonThresholdSet = New System.Windows.Forms.RadioButton()
        Me.radioButtonThresholdDefault = New System.Windows.Forms.RadioButton()
        Me.groupBoxRecordVolume = New System.Windows.Forms.GroupBox()
        Me.radioButtonRecordVolumeAuto = New System.Windows.Forms.RadioButton()
        Me.trackBarRecordVolume = New System.Windows.Forms.TrackBar()
        Me.radioButtonRecordVolumeSet = New System.Windows.Forms.RadioButton()
        Me.radioButtonRecordVolumeDefault = New System.Windows.Forms.RadioButton()
        Me.groupBoxServer = New System.Windows.Forms.GroupBox()
        Me.groupBox2 = New System.Windows.Forms.GroupBox()
        Me.CompressionTypeComboBox = New System.Windows.Forms.ComboBox()
        Me.buttonOK = New System.Windows.Forms.Button()
        Me.buttonCancel = New System.Windows.Forms.Button()
        Me.groupBoxPlaybackVolume.SuspendLayout()
        CType(Me.trackBarPlaybackVolume, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.groupBoxClient.SuspendLayout()
        Me.groupBoxThreshold.SuspendLayout()
        CType(Me.trackBarThreshold, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.groupBoxRecordVolume.SuspendLayout()
        CType(Me.trackBarRecordVolume, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.groupBoxServer.SuspendLayout()
        Me.groupBox2.SuspendLayout()
        Me.SuspendLayout()
        '
        'groupBoxPlaybackVolume
        '
        Me.groupBoxPlaybackVolume.Controls.AddRange(New System.Windows.Forms.Control() {Me.trackBarPlaybackVolume, Me.radioButtonPlaybackSet, Me.radioButtonPlaybackDefault})
        Me.groupBoxPlaybackVolume.Location = New System.Drawing.Point(8, 16)
        Me.groupBoxPlaybackVolume.Name = "groupBoxPlaybackVolume"
        Me.groupBoxPlaybackVolume.Size = New System.Drawing.Size(184, 100)
        Me.groupBoxPlaybackVolume.TabIndex = 0
        Me.groupBoxPlaybackVolume.TabStop = False
        Me.groupBoxPlaybackVolume.Text = "Playback Volume"
        '
        'trackBarPlaybackVolume
        '
        Me.trackBarPlaybackVolume.LargeChange = 25
        Me.trackBarPlaybackVolume.Location = New System.Drawing.Point(8, 48)
        Me.trackBarPlaybackVolume.Maximum = 99
        Me.trackBarPlaybackVolume.Name = "trackBarPlaybackVolume"
        Me.trackBarPlaybackVolume.Size = New System.Drawing.Size(168, 45)
        Me.trackBarPlaybackVolume.TabIndex = 2
        Me.trackBarPlaybackVolume.TickFrequency = 5
        '
        'radioButtonPlaybackSet
        '
        Me.radioButtonPlaybackSet.Location = New System.Drawing.Point(88, 18)
        Me.radioButtonPlaybackSet.Name = "radioButtonPlaybackSet"
        Me.radioButtonPlaybackSet.Size = New System.Drawing.Size(56, 16)
        Me.radioButtonPlaybackSet.TabIndex = 1
        Me.radioButtonPlaybackSet.Text = "Set"
        '
        'radioButtonPlaybackDefault
        '
        Me.radioButtonPlaybackDefault.Location = New System.Drawing.Point(16, 16)
        Me.radioButtonPlaybackDefault.Name = "radioButtonPlaybackDefault"
        Me.radioButtonPlaybackDefault.Size = New System.Drawing.Size(64, 20)
        Me.radioButtonPlaybackDefault.TabIndex = 0
        Me.radioButtonPlaybackDefault.Text = "Default"
        '
        'groupBoxClient
        '
        Me.groupBoxClient.Controls.AddRange(New System.Windows.Forms.Control() {Me.groupBoxThreshold, Me.groupBoxRecordVolume, Me.groupBoxPlaybackVolume})
        Me.groupBoxClient.Location = New System.Drawing.Point(8, 8)
        Me.groupBoxClient.Name = "groupBoxClient"
        Me.groupBoxClient.Size = New System.Drawing.Size(584, 128)
        Me.groupBoxClient.TabIndex = 1
        Me.groupBoxClient.TabStop = False
        Me.groupBoxClient.Text = "Client Options (adjust any time)"
        '
        'groupBoxThreshold
        '
        Me.groupBoxThreshold.Controls.AddRange(New System.Windows.Forms.Control() {Me.radioButtonThresholdAuto, Me.trackBarThreshold, Me.radioButtonThresholdSet, Me.radioButtonThresholdDefault})
        Me.groupBoxThreshold.Location = New System.Drawing.Point(392, 16)
        Me.groupBoxThreshold.Name = "groupBoxThreshold"
        Me.groupBoxThreshold.Size = New System.Drawing.Size(184, 100)
        Me.groupBoxThreshold.TabIndex = 2
        Me.groupBoxThreshold.TabStop = False
        Me.groupBoxThreshold.Text = "Threshold"
        '
        'radioButtonThresholdAuto
        '
        Me.radioButtonThresholdAuto.Location = New System.Drawing.Point(72, 14)
        Me.radioButtonThresholdAuto.Name = "radioButtonThresholdAuto"
        Me.radioButtonThresholdAuto.Size = New System.Drawing.Size(48, 24)
        Me.radioButtonThresholdAuto.TabIndex = 13
        Me.radioButtonThresholdAuto.Text = "Auto"
        '
        'trackBarThreshold
        '
        Me.trackBarThreshold.LargeChange = 25
        Me.trackBarThreshold.Location = New System.Drawing.Point(8, 48)
        Me.trackBarThreshold.Maximum = 99
        Me.trackBarThreshold.Name = "trackBarThreshold"
        Me.trackBarThreshold.Size = New System.Drawing.Size(168, 45)
        Me.trackBarThreshold.TabIndex = 12
        Me.trackBarThreshold.TickFrequency = 5
        '
        'radioButtonThresholdSet
        '
        Me.radioButtonThresholdSet.Location = New System.Drawing.Point(128, 18)
        Me.radioButtonThresholdSet.Name = "radioButtonThresholdSet"
        Me.radioButtonThresholdSet.Size = New System.Drawing.Size(40, 16)
        Me.radioButtonThresholdSet.TabIndex = 11
        Me.radioButtonThresholdSet.Text = "Set"
        '
        'radioButtonThresholdDefault
        '
        Me.radioButtonThresholdDefault.Location = New System.Drawing.Point(8, 16)
        Me.radioButtonThresholdDefault.Name = "radioButtonThresholdDefault"
        Me.radioButtonThresholdDefault.Size = New System.Drawing.Size(64, 20)
        Me.radioButtonThresholdDefault.TabIndex = 10
        Me.radioButtonThresholdDefault.Text = "Default"
        '
        'groupBoxRecordVolume
        '
        Me.groupBoxRecordVolume.Controls.AddRange(New System.Windows.Forms.Control() {Me.radioButtonRecordVolumeAuto, Me.trackBarRecordVolume, Me.radioButtonRecordVolumeSet, Me.radioButtonRecordVolumeDefault})
        Me.groupBoxRecordVolume.Location = New System.Drawing.Point(200, 16)
        Me.groupBoxRecordVolume.Name = "groupBoxRecordVolume"
        Me.groupBoxRecordVolume.Size = New System.Drawing.Size(184, 100)
        Me.groupBoxRecordVolume.TabIndex = 1
        Me.groupBoxRecordVolume.TabStop = False
        Me.groupBoxRecordVolume.Text = "Record Volume"
        '
        'radioButtonRecordVolumeAuto
        '
        Me.radioButtonRecordVolumeAuto.Location = New System.Drawing.Point(72, 14)
        Me.radioButtonRecordVolumeAuto.Name = "radioButtonRecordVolumeAuto"
        Me.radioButtonRecordVolumeAuto.Size = New System.Drawing.Size(48, 24)
        Me.radioButtonRecordVolumeAuto.TabIndex = 9
        Me.radioButtonRecordVolumeAuto.Text = "Auto"
        '
        'trackBarRecordVolume
        '
        Me.trackBarRecordVolume.LargeChange = 25
        Me.trackBarRecordVolume.Location = New System.Drawing.Point(8, 48)
        Me.trackBarRecordVolume.Maximum = 99
        Me.trackBarRecordVolume.Name = "trackBarRecordVolume"
        Me.trackBarRecordVolume.Size = New System.Drawing.Size(168, 45)
        Me.trackBarRecordVolume.TabIndex = 8
        Me.trackBarRecordVolume.TickFrequency = 5
        '
        'radioButtonRecordVolumeSet
        '
        Me.radioButtonRecordVolumeSet.Location = New System.Drawing.Point(128, 18)
        Me.radioButtonRecordVolumeSet.Name = "radioButtonRecordVolumeSet"
        Me.radioButtonRecordVolumeSet.Size = New System.Drawing.Size(40, 16)
        Me.radioButtonRecordVolumeSet.TabIndex = 7
        Me.radioButtonRecordVolumeSet.Text = "Set"
        '
        'radioButtonRecordVolumeDefault
        '
        Me.radioButtonRecordVolumeDefault.Location = New System.Drawing.Point(8, 16)
        Me.radioButtonRecordVolumeDefault.Name = "radioButtonRecordVolumeDefault"
        Me.radioButtonRecordVolumeDefault.Size = New System.Drawing.Size(64, 20)
        Me.radioButtonRecordVolumeDefault.TabIndex = 6
        Me.radioButtonRecordVolumeDefault.Text = "Default"
        '
        'groupBoxServer
        '
        Me.groupBoxServer.Controls.AddRange(New System.Windows.Forms.Control() {Me.groupBox2})
        Me.groupBoxServer.Location = New System.Drawing.Point(8, 144)
        Me.groupBoxServer.Name = "groupBoxServer"
        Me.groupBoxServer.Size = New System.Drawing.Size(584, 80)
        Me.groupBoxServer.TabIndex = 2
        Me.groupBoxServer.TabStop = False
        Me.groupBoxServer.Text = "Server Options (set only when creating a new session)"
        '
        'groupBox2
        '
        Me.groupBox2.Controls.AddRange(New System.Windows.Forms.Control() {Me.CompressionTypeComboBox})
        Me.groupBox2.Location = New System.Drawing.Point(8, 24)
        Me.groupBox2.Name = "groupBox2"
        Me.groupBox2.Size = New System.Drawing.Size(568, 48)
        Me.groupBox2.TabIndex = 0
        Me.groupBox2.TabStop = False
        Me.groupBox2.Text = "Compression Type"
        '
        'CompressionTypeComboBox
        '
        Me.CompressionTypeComboBox.Location = New System.Drawing.Point(16, 16)
        Me.CompressionTypeComboBox.Name = "CompressionTypeComboBox"
        Me.CompressionTypeComboBox.Size = New System.Drawing.Size(544, 21)
        Me.CompressionTypeComboBox.TabIndex = 0
        '
        'buttonOK
        '
        Me.buttonOK.Location = New System.Drawing.Point(432, 240)
        Me.buttonOK.Name = "buttonOK"
        Me.buttonOK.TabIndex = 3
        Me.buttonOK.Text = "OK"
        '
        'buttonCancel
        '
        Me.buttonCancel.Location = New System.Drawing.Point(517, 240)
        Me.buttonCancel.Name = "buttonCancel"
        Me.buttonCancel.TabIndex = 4
        Me.buttonCancel.Text = "Cancel"
        '
        'DPlayVoiceConfigForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(600, 272)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.buttonCancel, Me.buttonOK, Me.groupBoxServer, Me.groupBoxClient})
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Name = "DPlayVoiceConfigForm"
        Me.Text = "DirectPlayVoice Configuration"
        Me.groupBoxPlaybackVolume.ResumeLayout(False)
        CType(Me.trackBarPlaybackVolume, System.ComponentModel.ISupportInitialize).EndInit()
        Me.groupBoxClient.ResumeLayout(False)
        Me.groupBoxThreshold.ResumeLayout(False)
        CType(Me.trackBarThreshold, System.ComponentModel.ISupportInitialize).EndInit()
        Me.groupBoxRecordVolume.ResumeLayout(False)
        CType(Me.trackBarRecordVolume, System.ComponentModel.ISupportInitialize).EndInit()
        Me.groupBoxServer.ResumeLayout(False)
        Me.groupBox2.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub 'InitializeComponent

    Private Sub buttonOK_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles buttonOK.Click '

        'clear the config
        mConfig = New Voice.ClientConfig()

        mConfig.Flags = 0

        ' Set playback parameters
        If radioButtonPlaybackDefault.Checked Then
            mConfig.PlaybackVolume = CInt(Voice.PlaybackVolume.Default)
        Else
            mConfig.PlaybackVolume = CInt(Volume.Min) + CInt(trackBarPlaybackVolume.Value / 100.0F * (Volume.Max - Volume.Min))
        End If

        ' Set recording parameters
        If radioButtonRecordVolumeAuto.Checked Then
            mConfig.RecordVolume = 0
            mConfig.Flags = mConfig.Flags Or Voice.ClientConfigFlags.AutoRecordVolume
        ElseIf radioButtonRecordVolumeDefault.Checked Then
            mConfig.RecordVolume = CInt(Voice.PlaybackVolume.Default)
        Else
            mConfig.RecordVolume = CInt(Volume.Min) + CInt(trackBarRecordVolume.Value / 100.0F * (Volume.Max - Volume.Min))
        End If

        ' Set threshold parameters
        If radioButtonThresholdAuto.Checked Then
            mConfig.Threshold = Voice.Threshold.Unused
            mConfig.Flags = mConfig.Flags Or Voice.ClientConfigFlags.AutoVoiceActivated
        ElseIf radioButtonThresholdDefault.Checked Then
            mConfig.Threshold = Voice.Threshold.Default
            mConfig.Flags = mConfig.Flags Or Voice.ClientConfigFlags.ManualVoiceActivated
        Else
            mConfig.Threshold = CType(CInt(Voice.Threshold.Min) + trackBarThreshold.Value / 100.0F * (CInt(Voice.Threshold.Max) - CInt(Voice.Threshold.Min)), Voice.Threshold)
            mConfig.Flags = mConfig.Flags Or Voice.ClientConfigFlags.ManualVoiceActivated
        End If

        'Can only be set at the beginning, when the host is not in a session
        If mIsHost And Not mInSession Then
            mSelectedCompressionGuid = mCompressionInfo(CompressionTypeComboBox.SelectedIndex).GuidType
        End If

        Me.DialogResult = DialogResult.OK
        Me.Hide()
    End Sub 'buttonOK_Click


    Private Sub trackBarPlaybackVolume_Scroll(ByVal sender As Object, ByVal e As System.EventArgs) Handles trackBarPlaybackVolume.Scroll
        radioButtonPlaybackSet.Checked = True
    End Sub 'trackBarPlaybackVolume_Scroll


    Private Sub trackBarRecordVolume_Scroll(ByVal sender As Object, ByVal e As System.EventArgs) Handles trackBarRecordVolume.Scroll
        radioButtonRecordVolumeSet.Checked = True
    End Sub 'trackBarRecordVolume_Scroll


    Private Sub trackBarThreshold_Scroll(ByVal sender As Object, ByVal e As System.EventArgs) Handles trackBarThreshold.Scroll
        radioButtonThresholdSet.Checked = True
    End Sub 'trackBarThreshold_Scroll


    Private Sub buttonCancel_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles buttonCancel.Click
        Me.DialogResult = DialogResult.Cancel
        Me.Hide()
    End Sub 'buttonCancel_Click
End Class 'DPlayVoiceConfigForm 