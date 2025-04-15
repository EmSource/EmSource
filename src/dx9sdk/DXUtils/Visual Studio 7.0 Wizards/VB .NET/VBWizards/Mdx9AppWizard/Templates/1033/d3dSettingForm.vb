'-----------------------------------------------------------------------------
' File: D3DSettingsForm.vb
'
' Desc: Application form for setting up user defined display settings
'
' Copyright (c) 2001-2002 Microsoft Corporation. All rights reserved.
'-----------------------------------------------------------------------------
Imports System
Imports System.Collections
Imports System.Windows.Forms
Imports Microsoft.DirectX.Direct3D

 _

'/ <summary>
'/ Current D3D settings: adapter, device, mode, formats, etc.
'/ </summary>
Public Class D3DSettings
    Public IsWindowed As Boolean

    Public WindowedAdapterInfo As GraphicsAdapterInfo
    Public WindowedDeviceInfo As GraphicsDeviceInfo
    Public WindowedDeviceCombo As DeviceCombo
    Public WindowedDisplayMode As DisplayMode ' not changable by the user
    Public WindowedDepthStencilBufferFormat As DepthFormat
    Public WindowedMultisampleType As MultisampleType
    Public WindowedMultisampleQuality As Integer
    Public WindowedVertexProcessingType As VertexProcessingType
    Public WindowedPresentInterval As PresentInterval
    Public WindowedWidth As Integer
    Public WindowedHeight As Integer

    Public FullscreenAdapterInfo As GraphicsAdapterInfo
    Public FullscreenDeviceInfo As GraphicsDeviceInfo
    Public FullscreenDeviceCombo As DeviceCombo
    Public FullscreenDisplayMode As DisplayMode ' changable by the user
    Public FullscreenDepthStencilBufferFormat As DepthFormat
    Public FullscreenMultisampleType As MultisampleType
    Public FullscreenMultisampleQuality As Integer
    Public FullscreenVertexProcessingType As VertexProcessingType
    Public FullscreenPresentInterval As PresentInterval


    Public Property AdapterInfo() As GraphicsAdapterInfo
        Get
            Return IIf(IsWindowed, WindowedAdapterInfo, FullscreenAdapterInfo)
        End Get
        Set(ByVal Value As GraphicsAdapterInfo)
            If IsWindowed Then
                WindowedAdapterInfo = Value
            Else
                FullscreenAdapterInfo = Value
            End If
        End Set
    End Property

    Public Property DeviceInfo() As GraphicsDeviceInfo
        Get
            Return IIf(IsWindowed, WindowedDeviceInfo, FullscreenDeviceInfo)
        End Get
        Set(ByVal Value As GraphicsDeviceInfo)
            If IsWindowed Then
                WindowedDeviceInfo = Value
            Else
                FullscreenDeviceInfo = Value
            End If
        End Set
    End Property

    Public Property DeviceCombo() As DeviceCombo
        Get
            Return IIf(IsWindowed, WindowedDeviceCombo, FullscreenDeviceCombo)
        End Get
        Set(ByVal Value As DeviceCombo)
            If IsWindowed Then
                WindowedDeviceCombo = Value
            Else
                FullscreenDeviceCombo = Value
            End If
        End Set
    End Property

    Public ReadOnly Property AdapterOrdinal() As Integer
        Get
            Return DeviceCombo.AdapterOrdinal
        End Get
    End Property

    Public ReadOnly Property DevType() As DeviceType
        Get
            Return DeviceCombo.DevType
        End Get
    End Property

    Public ReadOnly Property BackBufferFormat() As Format
        Get
            Return DeviceCombo.BackBufferFormat
        End Get
    End Property

    Public Property DisplayMode() As DisplayMode
        Get
            Return IIf(IsWindowed, WindowedDisplayMode, FullscreenDisplayMode)
        End Get
        Set(ByVal Value As DisplayMode)
            If IsWindowed Then
                WindowedDisplayMode = Value
            Else
                FullscreenDisplayMode = Value
            End If
        End Set
    End Property

    Public Property DepthStencilBufferFormat() As DepthFormat
        Get
            Return IIf(IsWindowed, WindowedDepthStencilBufferFormat, FullscreenDepthStencilBufferFormat)
        End Get
        Set(ByVal Value As DepthFormat)
            If IsWindowed Then
                WindowedDepthStencilBufferFormat = Value
            Else
                FullscreenDepthStencilBufferFormat = Value
            End If
        End Set
    End Property

    Public Property MultisampleType() As MultisampleType
        Get
            Return IIf(IsWindowed, WindowedMultisampleType, FullscreenMultisampleType)
        End Get
        Set(ByVal Value As MultisampleType)
            If IsWindowed Then
                WindowedMultisampleType = Value
            Else
                FullscreenMultisampleType = Value
            End If
        End Set
    End Property

    Public Property MultisampleQuality() As Integer
        Get
            Return IIf(IsWindowed, WindowedMultisampleQuality, FullscreenMultisampleQuality)
        End Get
        Set(ByVal Value As Integer)
            If IsWindowed Then
                WindowedMultisampleQuality = Value
            Else
                FullscreenMultisampleQuality = Value
            End If
        End Set
    End Property

    Public Property VertexProcessingType() As VertexProcessingType
        Get
            Return IIf(IsWindowed, WindowedVertexProcessingType, FullscreenVertexProcessingType)
        End Get
        Set(ByVal Value As VertexProcessingType)
            If IsWindowed Then
                WindowedVertexProcessingType = Value
            Else
                FullscreenVertexProcessingType = Value
            End If
        End Set
    End Property

    Public Property PresentInterval() As PresentInterval
        Get
            Return IIf(IsWindowed, WindowedPresentInterval, FullscreenPresentInterval)
        End Get
        Set(ByVal Value As PresentInterval)
            If IsWindowed Then
                WindowedPresentInterval = Value
            Else
                FullscreenPresentInterval = Value
            End If
        End Set
    End Property

    Public Function Clone() As D3DSettings
        Return CType(MemberwiseClone(), D3DSettings)
    End Function 'Clone
End Class 'D3DSettings
 _


'/ <summary>
'/ A form to allow the user to change the current D3D settings.
'/ </summary>
Public Class D3DSettingsForm
    Inherits System.Windows.Forms.Form
    Private enumeration As D3DEnumeration
    Public settings As D3DSettings ' Potential new D3D settings
    Private WithEvents adapterDeviceGroupBox As System.Windows.Forms.GroupBox
    Private WithEvents displayAdapterLabel As System.Windows.Forms.Label
    Private WithEvents adapterComboBox As System.Windows.Forms.ComboBox
    Private WithEvents deviceLabel As System.Windows.Forms.Label
    Private WithEvents deviceComboBox As System.Windows.Forms.ComboBox
    Private WithEvents modeSettingsGroupBox As System.Windows.Forms.GroupBox
    Private WithEvents windowedRadioButton As System.Windows.Forms.RadioButton
    Private WithEvents fullscreenRadioButton As System.Windows.Forms.RadioButton
    Private WithEvents adapterFormatLabel As System.Windows.Forms.Label
    Private WithEvents adapterFormatComboBox As System.Windows.Forms.ComboBox
    Private WithEvents resolutionLabel As System.Windows.Forms.Label
    Private WithEvents resolutionComboBox As System.Windows.Forms.ComboBox
    Private WithEvents refreshRateLabel As System.Windows.Forms.Label
    Private WithEvents refreshRateComboBox As System.Windows.Forms.ComboBox
    Private WithEvents otherSettingsGroupBox As System.Windows.Forms.GroupBox
    Private WithEvents backBufferFormatLabel As System.Windows.Forms.Label
    Private WithEvents backBufferFormatComboBox As System.Windows.Forms.ComboBox
    Private WithEvents depthStencilBufferLabel As System.Windows.Forms.Label
    Private WithEvents depthStencilBufferComboBox As System.Windows.Forms.ComboBox
    Private WithEvents multisampleLabel As System.Windows.Forms.Label
    Private WithEvents multisampleComboBox As System.Windows.Forms.ComboBox
    Private WithEvents vertexProcLabel As System.Windows.Forms.Label
    Private WithEvents vertexProcComboBox As System.Windows.Forms.ComboBox
    Private WithEvents presentIntervalLabel As System.Windows.Forms.Label
    Private WithEvents presentIntervalComboBox As System.Windows.Forms.ComboBox
    Private WithEvents okButton As System.Windows.Forms.Button
    Private WithEvents btnCancel As System.Windows.Forms.Button
    Private WithEvents multisampleQualityComboBox As System.Windows.Forms.ComboBox
    Private WithEvents multisampleQualityLabel As System.Windows.Forms.Label

    '/ <summary>
    '/ Required designer variable.
    '/ </summary>
    Private components As System.ComponentModel.Container = Nothing


    '/ <summary>
    '/ Constructor.  Pass in an enumeration and the current D3D settings.
    '/ </summary>
    Public Sub New(ByVal enumerationParam As D3DEnumeration, ByVal settingsParam As D3DSettings)
        enumeration = enumerationParam
        settings = settingsParam.Clone()

        ' Required for Windows Form Designer support
        InitializeComponent()

        ' Fill adapter combo box.  Updating the selected adapter will trigger
        ' updates of the rest of the dialog.
        Dim adapterInfo As GraphicsAdapterInfo
        For Each adapterInfo In enumeration.AdapterInfoList
            adapterComboBox.Items.Add(adapterInfo)
            If adapterInfo.AdapterOrdinal = settings.AdapterOrdinal Then
                adapterComboBox.SelectedItem = adapterInfo
            End If
        Next adapterInfo
        If adapterComboBox.SelectedItem Is Nothing And adapterComboBox.Items.Count > 0 Then
            adapterComboBox.SelectedIndex = 0
        End If
    End Sub 'New

    '/ <summary>
    '/ Clean up any resources being used.
    '/ </summary>
    Protected Shadows Sub Dispose()
        MyBase.Dispose(Disposing)
        If Not (components Is Nothing) Then
            components.Dispose()
        End If
    End Sub 'Dispose

    '/ <summary>
    '/ Required method for Designer support - do not modify
    '/ the contents of this method with the code editor.
    '/ </summary>
    Private Sub InitializeComponent()
        Me.adapterDeviceGroupBox = New System.Windows.Forms.GroupBox()
        Me.deviceComboBox = New System.Windows.Forms.ComboBox()
        Me.deviceLabel = New System.Windows.Forms.Label()
        Me.adapterComboBox = New System.Windows.Forms.ComboBox()
        Me.displayAdapterLabel = New System.Windows.Forms.Label()
        Me.fullscreenRadioButton = New System.Windows.Forms.RadioButton()
        Me.btnCancel = New System.Windows.Forms.Button()
        Me.otherSettingsGroupBox = New System.Windows.Forms.GroupBox()
        Me.multisampleQualityComboBox = New System.Windows.Forms.ComboBox()
        Me.multisampleQualityLabel = New System.Windows.Forms.Label()
        Me.multisampleComboBox = New System.Windows.Forms.ComboBox()
        Me.backBufferFormatComboBox = New System.Windows.Forms.ComboBox()
        Me.multisampleLabel = New System.Windows.Forms.Label()
        Me.depthStencilBufferLabel = New System.Windows.Forms.Label()
        Me.backBufferFormatLabel = New System.Windows.Forms.Label()
        Me.depthStencilBufferComboBox = New System.Windows.Forms.ComboBox()
        Me.vertexProcComboBox = New System.Windows.Forms.ComboBox()
        Me.vertexProcLabel = New System.Windows.Forms.Label()
        Me.presentIntervalComboBox = New System.Windows.Forms.ComboBox()
        Me.presentIntervalLabel = New System.Windows.Forms.Label()
        Me.resolutionComboBox = New System.Windows.Forms.ComboBox()
        Me.windowedRadioButton = New System.Windows.Forms.RadioButton()
        Me.resolutionLabel = New System.Windows.Forms.Label()
        Me.refreshRateComboBox = New System.Windows.Forms.ComboBox()
        Me.adapterFormatLabel = New System.Windows.Forms.Label()
        Me.refreshRateLabel = New System.Windows.Forms.Label()
        Me.okButton = New System.Windows.Forms.Button()
        Me.modeSettingsGroupBox = New System.Windows.Forms.GroupBox()
        Me.adapterFormatComboBox = New System.Windows.Forms.ComboBox()
        Me.adapterDeviceGroupBox.SuspendLayout()
        Me.otherSettingsGroupBox.SuspendLayout()
        Me.modeSettingsGroupBox.SuspendLayout()
        Me.SuspendLayout()
        ' 
        ' adapterDeviceGroupBox
        ' 
        Me.adapterDeviceGroupBox.Controls.AddRange(New System.Windows.Forms.Control() {Me.deviceComboBox, Me.deviceLabel, Me.adapterComboBox, Me.displayAdapterLabel})
        Me.adapterDeviceGroupBox.Location = New System.Drawing.Point(16, 8)
        Me.adapterDeviceGroupBox.Name = "adapterDeviceGroupBox"
        Me.adapterDeviceGroupBox.Size = New System.Drawing.Size(400, 80)
        Me.adapterDeviceGroupBox.TabIndex = 0
        Me.adapterDeviceGroupBox.TabStop = False
        Me.adapterDeviceGroupBox.Text = "Adapter and device"
        ' 
        ' deviceComboBox
        ' 
        Me.deviceComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.deviceComboBox.DropDownWidth = 121
        Me.deviceComboBox.Location = New System.Drawing.Point(160, 48)
        Me.deviceComboBox.Name = "deviceComboBox"
        Me.deviceComboBox.Size = New System.Drawing.Size(232, 21)
        Me.deviceComboBox.TabIndex = 3
        ' 
        ' deviceLabel
        ' 
        Me.deviceLabel.Location = New System.Drawing.Point(8, 48)
        Me.deviceLabel.Name = "deviceLabel"
        Me.deviceLabel.Size = New System.Drawing.Size(152, 23)
        Me.deviceLabel.TabIndex = 2
        Me.deviceLabel.Text = "Render &Device:"
        ' 
        ' adapterComboBox
        ' 
        Me.adapterComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.adapterComboBox.DropDownWidth = 121
        Me.adapterComboBox.Location = New System.Drawing.Point(160, 24)
        Me.adapterComboBox.Name = "adapterComboBox"
        Me.adapterComboBox.Size = New System.Drawing.Size(232, 21)
        Me.adapterComboBox.TabIndex = 1
        ' 
        ' displayAdapterLabel
        ' 
        Me.displayAdapterLabel.Location = New System.Drawing.Point(8, 24)
        Me.displayAdapterLabel.Name = "displayAdapterLabel"
        Me.displayAdapterLabel.Size = New System.Drawing.Size(152, 23)
        Me.displayAdapterLabel.TabIndex = 0
        Me.displayAdapterLabel.Text = "Display &Adapter:"
        ' 
        ' fullscreenRadioButton
        ' 
        Me.fullscreenRadioButton.Location = New System.Drawing.Point(9, 38)
        Me.fullscreenRadioButton.Name = "fullscreenRadioButton"
        Me.fullscreenRadioButton.Size = New System.Drawing.Size(152, 24)
        Me.fullscreenRadioButton.TabIndex = 1
        Me.fullscreenRadioButton.Text = "&Fullscreen"
        ' 
        ' btnCancel
        ' 
        Me.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.btnCancel.Location = New System.Drawing.Point(248, 464)
        Me.btnCancel.Name = "btnCancel"
        Me.btnCancel.TabIndex = 4
        Me.btnCancel.Text = "Cancel"
        ' 
        ' otherSettingsGroupBox
        ' 
        Me.otherSettingsGroupBox.Controls.AddRange(New System.Windows.Forms.Control() {Me.multisampleQualityComboBox, Me.multisampleQualityLabel, Me.multisampleComboBox, Me.backBufferFormatComboBox, Me.multisampleLabel, Me.depthStencilBufferLabel, Me.backBufferFormatLabel, Me.depthStencilBufferComboBox, Me.vertexProcComboBox, Me.vertexProcLabel, Me.presentIntervalComboBox, Me.presentIntervalLabel})
        Me.otherSettingsGroupBox.Location = New System.Drawing.Point(16, 264)
        Me.otherSettingsGroupBox.Name = "otherSettingsGroupBox"
        Me.otherSettingsGroupBox.Size = New System.Drawing.Size(400, 176)
        Me.otherSettingsGroupBox.TabIndex = 2
        Me.otherSettingsGroupBox.TabStop = False
        Me.otherSettingsGroupBox.Text = "Device settings"
        ' 
        ' multisampleQualityComboBox
        ' 
        Me.multisampleQualityComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.multisampleQualityComboBox.DropDownWidth = 144
        Me.multisampleQualityComboBox.Location = New System.Drawing.Point(160, 96)
        Me.multisampleQualityComboBox.Name = "multisampleQualityComboBox"
        Me.multisampleQualityComboBox.Size = New System.Drawing.Size(232, 21)
        Me.multisampleQualityComboBox.TabIndex = 7
        ' 
        ' multisampleQualityLabel
        ' 
        Me.multisampleQualityLabel.Location = New System.Drawing.Point(8, 96)
        Me.multisampleQualityLabel.Name = "multisampleQualityLabel"
        Me.multisampleQualityLabel.Size = New System.Drawing.Size(152, 23)
        Me.multisampleQualityLabel.TabIndex = 6
        Me.multisampleQualityLabel.Text = "Multisample &Quality:"
        ' 
        ' multisampleComboBox
        ' 
        Me.multisampleComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.multisampleComboBox.DropDownWidth = 144
        Me.multisampleComboBox.Location = New System.Drawing.Point(160, 72)
        Me.multisampleComboBox.Name = "multisampleComboBox"
        Me.multisampleComboBox.Size = New System.Drawing.Size(232, 21)
        Me.multisampleComboBox.TabIndex = 5
        ' 
        ' backBufferFormatComboBox
        ' 
        Me.backBufferFormatComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.backBufferFormatComboBox.DropDownWidth = 144
        Me.backBufferFormatComboBox.Location = New System.Drawing.Point(160, 24)
        Me.backBufferFormatComboBox.Name = "backBufferFormatComboBox"
        Me.backBufferFormatComboBox.Size = New System.Drawing.Size(232, 21)
        Me.backBufferFormatComboBox.TabIndex = 1
        ' 
        ' multisampleLabel
        ' 
        Me.multisampleLabel.Location = New System.Drawing.Point(8, 72)
        Me.multisampleLabel.Name = "multisampleLabel"
        Me.multisampleLabel.Size = New System.Drawing.Size(152, 23)
        Me.multisampleLabel.TabIndex = 4
        Me.multisampleLabel.Text = "&Multisample Type:"
        ' 
        ' depthStencilBufferLabel
        ' 
        Me.depthStencilBufferLabel.Location = New System.Drawing.Point(8, 48)
        Me.depthStencilBufferLabel.Name = "depthStencilBufferLabel"
        Me.depthStencilBufferLabel.Size = New System.Drawing.Size(152, 23)
        Me.depthStencilBufferLabel.TabIndex = 2
        Me.depthStencilBufferLabel.Text = "De&pth/Stencil Buffer Format:"
        ' 
        ' backBufferFormatLabel
        ' 
        Me.backBufferFormatLabel.Location = New System.Drawing.Point(8, 24)
        Me.backBufferFormatLabel.Name = "backBufferFormatLabel"
        Me.backBufferFormatLabel.Size = New System.Drawing.Size(152, 23)
        Me.backBufferFormatLabel.TabIndex = 0
        Me.backBufferFormatLabel.Text = "&Back Buffer Format:"
        ' 
        ' depthStencilBufferComboBox
        ' 
        Me.depthStencilBufferComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.depthStencilBufferComboBox.DropDownWidth = 144
        Me.depthStencilBufferComboBox.Location = New System.Drawing.Point(160, 48)
        Me.depthStencilBufferComboBox.Name = "depthStencilBufferComboBox"
        Me.depthStencilBufferComboBox.Size = New System.Drawing.Size(232, 21)
        Me.depthStencilBufferComboBox.TabIndex = 3
        ' 
        ' vertexProcComboBox
        ' 
        Me.vertexProcComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.vertexProcComboBox.DropDownWidth = 121
        Me.vertexProcComboBox.Location = New System.Drawing.Point(160, 120)
        Me.vertexProcComboBox.Name = "vertexProcComboBox"
        Me.vertexProcComboBox.Size = New System.Drawing.Size(232, 21)
        Me.vertexProcComboBox.TabIndex = 9
        ' 
        ' vertexProcLabel
        ' 
        Me.vertexProcLabel.Location = New System.Drawing.Point(8, 120)
        Me.vertexProcLabel.Name = "vertexProcLabel"
        Me.vertexProcLabel.Size = New System.Drawing.Size(152, 23)
        Me.vertexProcLabel.TabIndex = 8
        Me.vertexProcLabel.Text = "&Vertex Processing:"
        ' 
        ' presentIntervalComboBox
        ' 
        Me.presentIntervalComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.presentIntervalComboBox.DropDownWidth = 121
        Me.presentIntervalComboBox.Location = New System.Drawing.Point(160, 144)
        Me.presentIntervalComboBox.Name = "presentIntervalComboBox"
        Me.presentIntervalComboBox.Size = New System.Drawing.Size(232, 21)
        Me.presentIntervalComboBox.TabIndex = 11
        ' 
        ' presentIntervalLabel
        ' 
        Me.presentIntervalLabel.Location = New System.Drawing.Point(8, 144)
        Me.presentIntervalLabel.Name = "presentIntervalLabel"
        Me.presentIntervalLabel.Size = New System.Drawing.Size(152, 23)
        Me.presentIntervalLabel.TabIndex = 10
        Me.presentIntervalLabel.Text = "Present &Interval:"
        ' 
        ' resolutionComboBox
        ' 
        Me.resolutionComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.resolutionComboBox.DropDownWidth = 144
        Me.resolutionComboBox.Location = New System.Drawing.Point(161, 94)
        Me.resolutionComboBox.MaxDropDownItems = 14
        Me.resolutionComboBox.Name = "resolutionComboBox"
        Me.resolutionComboBox.Size = New System.Drawing.Size(232, 21)
        Me.resolutionComboBox.TabIndex = 5
        ' 
        ' windowedRadioButton
        ' 
        Me.windowedRadioButton.Location = New System.Drawing.Point(9, 14)
        Me.windowedRadioButton.Name = "windowedRadioButton"
        Me.windowedRadioButton.Size = New System.Drawing.Size(152, 24)
        Me.windowedRadioButton.TabIndex = 0
        Me.windowedRadioButton.Text = "&Windowed"
        ' 
        ' resolutionLabel
        ' 
        Me.resolutionLabel.Location = New System.Drawing.Point(8, 94)
        Me.resolutionLabel.Name = "resolutionLabel"
        Me.resolutionLabel.Size = New System.Drawing.Size(152, 23)
        Me.resolutionLabel.TabIndex = 4
        Me.resolutionLabel.Text = "&Resolution:"
        ' 
        ' refreshRateComboBox
        ' 
        Me.refreshRateComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.refreshRateComboBox.DropDownWidth = 144
        Me.refreshRateComboBox.Location = New System.Drawing.Point(161, 118)
        Me.refreshRateComboBox.MaxDropDownItems = 14
        Me.refreshRateComboBox.Name = "refreshRateComboBox"
        Me.refreshRateComboBox.Size = New System.Drawing.Size(232, 21)
        Me.refreshRateComboBox.TabIndex = 7
        ' 
        ' adapterFormatLabel
        ' 
        Me.adapterFormatLabel.Location = New System.Drawing.Point(8, 72)
        Me.adapterFormatLabel.Name = "adapterFormatLabel"
        Me.adapterFormatLabel.Size = New System.Drawing.Size(152, 23)
        Me.adapterFormatLabel.TabIndex = 2
        Me.adapterFormatLabel.Text = "Adapter F&ormat:"
        ' 
        ' refreshRateLabel
        ' 
        Me.refreshRateLabel.Location = New System.Drawing.Point(8, 118)
        Me.refreshRateLabel.Name = "refreshRateLabel"
        Me.refreshRateLabel.Size = New System.Drawing.Size(152, 23)
        Me.refreshRateLabel.TabIndex = 6
        Me.refreshRateLabel.Text = "R&efresh Rate:"
        ' 
        ' okButton
        ' 
        Me.okButton.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.okButton.Location = New System.Drawing.Point(112, 464)
        Me.okButton.Name = "okButton"
        Me.okButton.TabIndex = 3
        Me.okButton.Text = "OK"
        ' 
        ' modeSettingsGroupBox
        ' 
        Me.modeSettingsGroupBox.Controls.AddRange(New System.Windows.Forms.Control() {Me.adapterFormatLabel, Me.refreshRateLabel, Me.resolutionComboBox, Me.adapterFormatComboBox, Me.resolutionLabel, Me.refreshRateComboBox, Me.windowedRadioButton, Me.fullscreenRadioButton})
        Me.modeSettingsGroupBox.Location = New System.Drawing.Point(16, 96)
        Me.modeSettingsGroupBox.Name = "modeSettingsGroupBox"
        Me.modeSettingsGroupBox.Size = New System.Drawing.Size(400, 160)
        Me.modeSettingsGroupBox.TabIndex = 1
        Me.modeSettingsGroupBox.TabStop = False
        Me.modeSettingsGroupBox.Text = "Display mode settings"
        ' 
        ' adapterFormatComboBox
        ' 
        Me.adapterFormatComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.adapterFormatComboBox.DropDownWidth = 121
        Me.adapterFormatComboBox.Location = New System.Drawing.Point(161, 70)
        Me.adapterFormatComboBox.MaxDropDownItems = 14
        Me.adapterFormatComboBox.Name = "adapterFormatComboBox"
        Me.adapterFormatComboBox.Size = New System.Drawing.Size(232, 21)
        Me.adapterFormatComboBox.TabIndex = 3
        ' 
        ' D3DSettingsForm
        ' 
        Me.AcceptButton = Me.okButton
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.CancelButton = Me.btnCancel
        Me.ClientSize = New System.Drawing.Size(438, 512)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.btnCancel, Me.okButton, Me.adapterDeviceGroupBox, Me.modeSettingsGroupBox, Me.otherSettingsGroupBox})
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.Name = "D3DSettingsForm"
        Me.Text = "Direct3D Settings"
        Me.adapterDeviceGroupBox.ResumeLayout(False)
        Me.otherSettingsGroupBox.ResumeLayout(False)
        Me.modeSettingsGroupBox.ResumeLayout(False)
        Me.ResumeLayout(False)
    End Sub 'InitializeComponent

    '
    '/ <summary>
    '/ Respond to a change of selected adapter by rebuilding the device 
    '/ list.  Updating the selected device will trigger updates of the 
    '/ rest of the dialog.
    '/ </summary>
    Private Sub AdapterChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles adapterComboBox.SelectedIndexChanged
        Dim adapterInfo As GraphicsAdapterInfo = CType(adapterComboBox.SelectedItem, GraphicsAdapterInfo)
        settings.AdapterInfo = adapterInfo

        ' Update device combo box
        deviceComboBox.Items.Clear()
        Dim deviceInfo As GraphicsDeviceInfo
        For Each deviceInfo In adapterInfo.DeviceInfoList
            deviceComboBox.Items.Add(deviceInfo)
            If deviceInfo.DevType = settings.DevType Then
                deviceComboBox.SelectedItem = deviceInfo
            End If
        Next deviceInfo
        If deviceComboBox.SelectedItem Is Nothing And deviceComboBox.Items.Count > 0 Then
            deviceComboBox.SelectedIndex = 0
        End If
    End Sub 'AdapterChanged

    '/ <summary>
    '/ Respond to a change of selected device by resetting the 
    '/ fullscreen/windowed radio buttons.  Updating these buttons
    '/ will trigger updates of the rest of the dialog.
    '/ </summary>
    Private Sub DeviceChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles deviceComboBox.SelectedIndexChanged
        Dim adapterInfo As GraphicsAdapterInfo = CType(adapterComboBox.SelectedItem, GraphicsAdapterInfo)
        Dim deviceInfo As GraphicsDeviceInfo = CType(deviceComboBox.SelectedItem, GraphicsDeviceInfo)

        settings.DeviceInfo = deviceInfo

        ' Update fullscreen/windowed radio buttons
        Dim HasWindowedDeviceCombo As Boolean = False
        Dim HasFullscreenDeviceCombo As Boolean = False
        Dim deviceCombo As DeviceCombo
        For Each deviceCombo In deviceInfo.DeviceComboList
            If deviceCombo.IsWindowed Then
                HasWindowedDeviceCombo = True
            Else
                HasFullscreenDeviceCombo = True
            End If
        Next deviceCombo
        windowedRadioButton.Enabled = HasWindowedDeviceCombo
        fullscreenRadioButton.Enabled = HasFullscreenDeviceCombo
        If settings.IsWindowed And HasWindowedDeviceCombo Then
            windowedRadioButton.Checked = True
        Else
            fullscreenRadioButton.Checked = True
        End If
        WindowedFullscreenChanged(Nothing, Nothing)
    End Sub 'DeviceChanged


    '/ <summary>
    '/ Respond to a change of windowed/fullscreen state by rebuilding the
    '/ adapter format list, resolution list, and refresh rate list.
    '/ Updating the selected adapter format will trigger updates of the 
    '/ rest of the dialog.
    '/ </summary>
    Private Sub WindowedFullscreenChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles windowedRadioButton.CheckedChanged
        Dim adapterInfo As GraphicsAdapterInfo = CType(adapterComboBox.SelectedItem, GraphicsAdapterInfo)
        Dim deviceInfo As GraphicsDeviceInfo = CType(deviceComboBox.SelectedItem, GraphicsDeviceInfo)

        If windowedRadioButton.Checked Then
            settings.IsWindowed = True
            settings.WindowedAdapterInfo = adapterInfo
            settings.WindowedDeviceInfo = deviceInfo

            ' Update adapter format combo box
            adapterFormatComboBox.Items.Clear()
            adapterFormatComboBox.Items.Add(settings.WindowedDisplayMode.Format)
            adapterFormatComboBox.SelectedIndex = 0
            adapterFormatComboBox.Enabled = False

            ' Update resolution combo box
            resolutionComboBox.Items.Clear()
            resolutionComboBox.Items.Add(FormatResolution(settings.WindowedDisplayMode.Width, settings.WindowedDisplayMode.Height))
            resolutionComboBox.SelectedIndex = 0
            resolutionComboBox.Enabled = False

            ' Update refresh rate combo box
            refreshRateComboBox.Items.Clear()
            refreshRateComboBox.Items.Add(FormatRefreshRate(settings.WindowedDisplayMode.RefreshRate))
            refreshRateComboBox.SelectedIndex = 0
            refreshRateComboBox.Enabled = False
        Else
            settings.IsWindowed = False
            settings.FullscreenAdapterInfo = adapterInfo
            settings.FullscreenDeviceInfo = deviceInfo

            ' Update adapter format combo box
            adapterFormatComboBox.Items.Clear()
            Dim deviceCombo As DeviceCombo
            For Each deviceCombo In deviceInfo.DeviceComboList
                If Not deviceCombo.IsWindowed Then
                    If Not adapterFormatComboBox.Items.Contains(deviceCombo.AdapterFormat) Then
                        adapterFormatComboBox.Items.Add(deviceCombo.AdapterFormat)
                        If deviceCombo.AdapterFormat = IIf(settings.IsWindowed, settings.WindowedDisplayMode.Format, settings.FullscreenDisplayMode.Format) Then
                            adapterFormatComboBox.SelectedItem = deviceCombo.AdapterFormat
                        End If
                    End If
                End If
            Next deviceCombo
            If adapterFormatComboBox.SelectedItem Is Nothing And adapterFormatComboBox.Items.Count > 0 Then
                adapterFormatComboBox.SelectedIndex = 0
            End If
            adapterFormatComboBox.Enabled = True

            ' Update resolution combo box
            resolutionComboBox.Enabled = True

            ' Update refresh rate combo box
            refreshRateComboBox.Enabled = True
        End If
    End Sub 'WindowedFullscreenChanged


    '/ <summary>
    '/ Converts the given width and height into a formatted string
    '/ </summary>
    Private Function FormatResolution(ByVal width As Integer, ByVal height As Integer) As String
        Dim sb As New System.Text.StringBuilder(20)
        sb.AppendFormat("{0} by {1}", width, height)
        Return sb.ToString()
    End Function 'FormatResolution


    '/ <summary>
    '/ Converts the given refresh rate into a formatted string
    '/ </summary>
    Private Function FormatRefreshRate(ByVal refreshRate As Integer) As String
        If refreshRate = 0 Then
            Return "Default Rate"
        Else
            Dim sb As New System.Text.StringBuilder(20)
            sb.AppendFormat("{0} Hz", refreshRate)
            Return sb.ToString()
        End If
    End Function 'FormatRefreshRate


    '/ <summary>
    '/ Respond to a change of selected adapter format by rebuilding the
    '/ resolution list and back buffer format list.  Updating the selected 
    '/ resolution and back buffer format will trigger updates of the rest 
    '/ of the dialog.
    '/ </summary>
    Private Sub AdapterFormatChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles adapterFormatComboBox.SelectedValueChanged
        If Not windowedRadioButton.Checked Then
            Dim adapterInfo As GraphicsAdapterInfo = CType(adapterComboBox.SelectedItem, GraphicsAdapterInfo)
            Dim adapterFormat As Format = CType(adapterFormatComboBox.SelectedItem, Format)
            settings.FullscreenDisplayMode.Format = adapterFormat
            Dim sb As New System.Text.StringBuilder(20)

            resolutionComboBox.Items.Clear()
            Dim displayMode As DisplayMode
            For Each displayMode In adapterInfo.DisplayModeList
                If displayMode.Format = adapterFormat Then
                    Dim resolutionString As String = FormatResolution(displayMode.Width, displayMode.Height)
                    If Not resolutionComboBox.Items.Contains(resolutionString) Then
                        resolutionComboBox.Items.Add(resolutionString)
                        If settings.FullscreenDisplayMode.Width = displayMode.Width And settings.FullscreenDisplayMode.Height = displayMode.Height Then
                            resolutionComboBox.SelectedItem = resolutionString
                        End If
                    End If
                End If
            Next displayMode
            If resolutionComboBox.SelectedItem Is Nothing And resolutionComboBox.Items.Count > 0 Then
                resolutionComboBox.SelectedIndex = 0
            End If
        End If
        ' Update backbuffer format combo box
        Dim deviceInfo As GraphicsDeviceInfo = CType(deviceComboBox.SelectedItem, GraphicsDeviceInfo)
        backBufferFormatComboBox.Items.Clear()
        Dim deviceCombo As DeviceCombo
        For Each deviceCombo In deviceInfo.DeviceComboList
            If deviceCombo.IsWindowed = settings.IsWindowed And deviceCombo.AdapterFormat = settings.DisplayMode.Format Then
                If Not backBufferFormatComboBox.Items.Contains(deviceCombo.BackBufferFormat) Then
                    backBufferFormatComboBox.Items.Add(deviceCombo.BackBufferFormat)
                    If deviceCombo.BackBufferFormat = settings.BackBufferFormat Then
                        backBufferFormatComboBox.SelectedItem = deviceCombo.BackBufferFormat
                    End If
                End If
            End If
        Next deviceCombo
        If backBufferFormatComboBox.SelectedItem Is Nothing And backBufferFormatComboBox.Items.Count > 0 Then
            backBufferFormatComboBox.SelectedIndex = 0
        End If
    End Sub 'AdapterFormatChanged

    '/ <summary>
    '/ Respond to a change of selected resolution by rebuilding the
    '/ refresh rate list.
    '/ </summary>
    Private Sub ResolutionChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles resolutionComboBox.SelectedIndexChanged
        If settings.IsWindowed Then
            Return
        End If
        Dim adapterInfo As GraphicsAdapterInfo = CType(adapterComboBox.SelectedItem, GraphicsAdapterInfo)

        ' Update settings with new resolution
        Dim resolution As String = CStr(resolutionComboBox.SelectedItem)
        Dim resolutionSplitStringArray As String() = resolution.Split()
        Dim width As Integer = Integer.Parse(resolutionSplitStringArray(0))
        Dim height As Integer = Integer.Parse(resolutionSplitStringArray(2))
        settings.FullscreenDisplayMode.Width = width
        settings.FullscreenDisplayMode.Height = height

        ' Update refresh rate list based on new resolution
        Dim adapterFormat As Format = CType(adapterFormatComboBox.SelectedItem, Format)
        refreshRateComboBox.Items.Clear()
        Dim displayMode As DisplayMode
        For Each displayMode In adapterInfo.DisplayModeList
            If displayMode.Format = adapterFormat And displayMode.Width = width And displayMode.Height = height Then
                Dim refreshRateString As String = FormatRefreshRate(displayMode.RefreshRate)
                If Not refreshRateComboBox.Items.Contains(refreshRateString) Then
                    refreshRateComboBox.Items.Add(refreshRateString)
                    If settings.FullscreenDisplayMode.RefreshRate = displayMode.RefreshRate Then
                        refreshRateComboBox.SelectedItem = refreshRateString
                    End If
                End If
            End If
        Next displayMode
        If refreshRateComboBox.SelectedItem Is Nothing And refreshRateComboBox.Items.Count > 0 Then
            refreshRateComboBox.SelectedIndex = refreshRateComboBox.Items.Count - 1
        End If
    End Sub 'ResolutionChanged

    '/ <summary>
    '/ Respond to a change of selected refresh rate.
    '/ </summary>
    Private Sub RefreshRateChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles refreshRateComboBox.SelectedIndexChanged
        If settings.IsWindowed Then
            Return
        End If
        ' Update settings with new refresh rate
        Dim refreshRateString As String = CStr(refreshRateComboBox.SelectedItem)
        Dim refreshRate As Integer = 0
        If refreshRateString <> "Default Rate" Then
            Dim refreshRateSplitStringArray As String() = refreshRateString.Split()
            refreshRate = Integer.Parse(refreshRateSplitStringArray(0))
        End If
        settings.FullscreenDisplayMode.RefreshRate = refreshRate
    End Sub 'RefreshRateChanged


    '/ <summary>
    '/ Respond to a change of selected back buffer format by rebuilding
    '/ the depth/stencil format list, multisample type list, and vertex
    '/ processing type list.
    '/ </summary>
    Private Sub BackBufferFormatChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles backBufferFormatComboBox.SelectedIndexChanged
        Dim deviceInfo As GraphicsDeviceInfo = CType(deviceComboBox.SelectedItem, GraphicsDeviceInfo)
        Dim adapterFormat As Format = CType(adapterFormatComboBox.SelectedItem, Format)
        Dim backBufferFormat As Format = CType(backBufferFormatComboBox.SelectedItem, Format)

        Dim deviceCombo As DeviceCombo
        For Each deviceCombo In deviceInfo.DeviceComboList
            If deviceCombo.IsWindowed = settings.IsWindowed And deviceCombo.AdapterFormat = adapterFormat And deviceCombo.BackBufferFormat = backBufferFormat Then
                deviceCombo.BackBufferFormat = backBufferFormat
                settings.DeviceCombo = deviceCombo

                depthStencilBufferComboBox.Items.Clear()
                If enumeration.AppUsesDepthBuffer Then
                    Dim fmt As DepthFormat
                    For Each fmt In deviceCombo.DepthStencilFormatList
                        depthStencilBufferComboBox.Items.Add(fmt)
                        If fmt = settings.DepthStencilBufferFormat Then
                            depthStencilBufferComboBox.SelectedItem = fmt
                        End If
                    Next fmt
                    If depthStencilBufferComboBox.SelectedItem Is Nothing And depthStencilBufferComboBox.Items.Count > 0 Then
                        depthStencilBufferComboBox.SelectedIndex = 0
                    End If
                Else
                    depthStencilBufferComboBox.Enabled = False
                    depthStencilBufferComboBox.Items.Add("(not used)")
                    depthStencilBufferComboBox.SelectedIndex = 0
                End If

                vertexProcComboBox.Items.Clear()
                Dim vpt As VertexProcessingType
                For Each vpt In deviceCombo.VertexProcessingTypeList
                    vertexProcComboBox.Items.Add(vpt)
                    If vpt = settings.VertexProcessingType Then
                        vertexProcComboBox.SelectedItem = vpt
                    End If
                Next vpt
                If vertexProcComboBox.SelectedItem Is Nothing And vertexProcComboBox.Items.Count > 0 Then
                    vertexProcComboBox.SelectedIndex = 0
                End If
                presentIntervalComboBox.Items.Clear()
                Dim pi As PresentInterval
                For Each pi In deviceCombo.PresentIntervalList
                    presentIntervalComboBox.Items.Add(pi)
                    If pi = settings.PresentInterval Then
                        presentIntervalComboBox.SelectedItem = pi
                    End If
                Next pi
                If presentIntervalComboBox.SelectedItem Is Nothing And presentIntervalComboBox.Items.Count > 0 Then
                    presentIntervalComboBox.SelectedIndex = 0
                End If
                Exit For
            End If
        Next deviceCombo
    End Sub 'BackBufferFormatChanged


    '/ <summary>
    '/ Respond to a change of selected depth/stencil buffer format.
    '/ </summary>
    Private Sub DepthStencilBufferFormatChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles depthStencilBufferComboBox.SelectedIndexChanged
        If enumeration.AppUsesDepthBuffer Then
            settings.DepthStencilBufferFormat = CType(depthStencilBufferComboBox.SelectedItem, Format)
        End If

        multisampleComboBox.Items.Clear()
        Dim msType As MultiSampleType
        For Each msType In settings.DeviceCombo.MultiSampleTypeList
            Dim conflictFound As Boolean = False
            Dim DSMSConflict As DepthStencilMultiSampleConflict
            For Each DSMSConflict In settings.DeviceCombo.DepthStencilMultiSampleConflictList
                If DSMSConflict.DepthStencilFormat = settings.DepthStencilBufferFormat And DSMSConflict.MultiSampleType = msType Then
                    conflictFound = True
                    Exit For
                End If
            Next DSMSConflict
            If Not conflictFound Then
                multisampleComboBox.Items.Add(msType)
                If msType = settings.MultisampleType Then
                    multisampleComboBox.SelectedItem = msType
                End If
            End If
        Next msType
        If multisampleComboBox.SelectedItem Is Nothing And multisampleComboBox.Items.Count > 0 Then
            multisampleComboBox.SelectedIndex = 0
        End If
    End Sub 'DepthStencilBufferFormatChanged

    '/ <summary>
    '/ Respond to a change of selected multisample type.
    '/ </summary>
    Private Sub MultisampleTypeChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles multisampleComboBox.SelectedIndexChanged
        settings.MultisampleType = CType(multisampleComboBox.SelectedItem, MultiSampleType)

        ' Find current max multisample quality
        Dim maxQuality As Integer = 0
        Dim deviceCombo As DeviceCombo = settings.DeviceCombo
        Dim i As Integer
        For i = 0 To deviceCombo.MultiSampleQualityList.Count - 1
            If CType(deviceCombo.MultiSampleTypeList(i), MultiSampleType) = settings.MultisampleType Then
                maxQuality = CInt(deviceCombo.MultiSampleQualityList(i))
                Exit For
            End If
        Next i

        ' Update multisample quality list based on new type
        multisampleQualityComboBox.Items.Clear()
        Dim iLevel As Integer
        For iLevel = 0 To maxQuality - 1
            multisampleQualityComboBox.Items.Add(iLevel)
            If settings.MultisampleQuality = iLevel Then
                multisampleQualityComboBox.SelectedItem = iLevel
            End If
        Next iLevel
        If multisampleQualityComboBox.SelectedItem Is Nothing And multisampleQualityComboBox.Items.Count > 0 Then
            multisampleQualityComboBox.SelectedIndex = 0
        End If
    End Sub 'MultisampleTypeChanged

    '/ <summary>
    '/ Respond to a change of selected multisample quality.
    '/ </summary>
    Private Sub MultisampleQualityChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles multisampleQualityComboBox.SelectedIndexChanged
        settings.MultisampleQuality = CInt(multisampleQualityComboBox.SelectedItem)
    End Sub 'MultisampleQualityChanged


    '/ <summary>
    '/ Respond to a change of selected vertex processing type.
    '/ </summary>
    Private Sub VertexProcessingChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles vertexProcComboBox.SelectedIndexChanged
        settings.VertexProcessingType = CType(vertexProcComboBox.SelectedItem, VertexProcessingType)
    End Sub 'VertexProcessingChanged


    '/ <summary>
    '/ Respond to a change of selected vertex processing type.
    '/ </summary>
    Private Sub PresentIntervalChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles presentIntervalComboBox.SelectedValueChanged
        settings.PresentInterval = CType(presentIntervalComboBox.SelectedItem, PresentInterval)
    End Sub 'PresentIntervalChanged
End Class 'D3DSettingsForm