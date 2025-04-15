'-----------------------------------------------------------------------------
' File: D3DEnumeration.vb
'
' Desc: Enumerates D3D adapters, devices, modes, etc.
'
' Copyright (c) 2001-2002 Microsoft Corporation. All rights reserved.
'-----------------------------------------------------------------------------
Imports System
Imports System.Collections
Imports Microsoft.DirectX
Imports Microsoft.DirectX.Direct3D

 _

'/ <summary>
'/ Enumeration of all possible D3D vertex processing types
'/ </summary>
Public Enum VertexProcessingType
    Software
    Mixed
    Hardware
    PureHardware
End Enum 'VertexProcessingType
 _

'/ <summary>
'/ Info about a display adapter
'/ </summary>
Public Class GraphicsAdapterInfo
    Public AdapterOrdinal As Integer
    Public AdapterDetails As AdapterDetails
    Public DisplayModeList As New ArrayList() ' List of D3DDISPLAYMODEs
    Public DeviceInfoList As New ArrayList()
    ' List of D3DDeviceInfos
    Public Overrides Function ToString() As String
        Return AdapterDetails.Description
    End Function 'ToString
End Class 'GraphicsAdapterInfo
 _ 
'/ <summary>
'/ Info about a D3D device, including a list of DeviceCombos (see below) 
'/ that work with the device
'/ </summary>
Public Class GraphicsDeviceInfo
    Public AdapterOrdinal As Integer
    Public DevType As DeviceType
    Public Caps As Caps
    Public DeviceComboList As New ArrayList()
    ' List of D3DDeviceCombos
    Public Overrides Function ToString() As String
        Return DevType.ToString()
    End Function 'ToString
End Class 'GraphicsDeviceInfo
 _ 
'/ <summary>
'/ A depth/stencil buffer format that is incompatible with a multisample type.
'/ </summary>
Public Class DepthStencilMultiSampleConflict
    Public DepthStencilFormat As DepthFormat
    Public MultiSampleType As MultiSampleType
End Class 'DepthStencilMultiSampleConflict
 _ 
'/ <summary>
'/ A combination of adapter format, back buffer format, and windowed/fullscreen 
'/ that is compatible with a particular D3D device (and the app)
'/ </summary>
Public Class DeviceCombo
    Public AdapterOrdinal As Integer
    Public DevType As DeviceType
    Public AdapterFormat As Format
    Public BackBufferFormat As Format
    Public IsWindowed As Boolean
    Public DepthStencilFormatList As New ArrayList() ' List of D3DFORMATs
    Public MultiSampleTypeList As New ArrayList() ' List of D3DMULTISAMPLE_TYPEs
    Public MultiSampleQualityList As New ArrayList() ' List of ints (maxQuality per multisample type)
    Public DepthStencilMultiSampleConflictList As New ArrayList() ' List of DepthStencilMultiSampleConflicts
    Public VertexProcessingTypeList As New ArrayList() ' List of VertexProcessingTypes
    Public PresentIntervalList As New ArrayList() ' List of D3DPRESENT_INTERVALs
End Class 'DeviceCombo
 _

'/ <summary>
'/ Used to sort D3DDISPLAYMODEs
'/ </summary>
Class DisplayModeComparer
    Implements System.Collections.IComparer

    Public Function Compare(ByVal x As Object, ByVal y As Object) As Integer Implements IComparer.Compare
        Dim dx As DisplayMode = CType(x, DisplayMode)
        Dim dy As DisplayMode = CType(y, DisplayMode)

        If dx.Width > dy.Width Then
            Return 1
        End If
        If dx.Width < dy.Width Then
            Return -1
        End If
        If dx.Height > dy.Height Then
            Return 1
        End If
        If dx.Height < dy.Height Then
            Return -1
        End If
        If dx.Format > dy.Format Then
            Return 1
        End If
        If dx.Format < dy.Format Then
            Return -1
        End If
        If dx.RefreshRate > dy.RefreshRate Then
            Return 1
        End If
        If dx.RefreshRate < dy.RefreshRate Then
            Return -1
        End If
        Return 0
    End Function 'Compare
End Class 'DisplayModeComparer
 _

'/ <summary>
'/ Enumerates available D3D adapters, devices, modes, etc.
'/ </summary>
Public Class D3DEnumeration

    Delegate Function ConfirmDeviceCallbackType(ByVal caps As Caps, ByVal vertexProcessingType As VertexProcessingType, ByVal adapterFormat As Format, ByVal backBufferFormat As Format) As Boolean

    Public ConfirmDeviceCallback As ConfirmDeviceCallbackType
    Public AdapterInfoList As New ArrayList() ' List of D3DAdapterInfos
    ' The following variables can be used to limit what modes, formats, 
    ' etc. are enumerated.  Set them to the values you want before calling
    ' Enumerate().
    Public AppMinFullscreenWidth As Integer = 640
    Public AppMinFullscreenHeight As Integer = 480
    Public AppMinColorChannelBits As Integer = 5 ' min color bits per channel in adapter format
    Public AppMinAlphaChannelBits As Integer = 0 ' min alpha bits per pixel in back buffer format
    Public AppMinDepthBits As Integer = 15
    Public AppMinStencilBits As Integer = 0
    Public AppUsesDepthBuffer As Boolean = True
    Public AppUsesMixedVP As Boolean = False ' whether app can take advantage of mixed vp mode
    Public AppRequiresWindowed As Boolean = False
    Public AppRequiresFullscreen As Boolean = False


    '/ <summary>
    '/ Enumerates available D3D adapters, devices, modes, etc.
    '/ </summary>
    Public Sub Enumerate()
        Dim ai As AdapterInformation
        For Each ai In Manager.Adapters
            Dim adapterFormatList As New ArrayList()
            Dim adapterInfo As New GraphicsAdapterInfo()
            adapterInfo.AdapterOrdinal = ai.Adapter
            adapterInfo.AdapterDetails = ai.Information

            ' Get list of all display modes on this adapter.  
            ' Also build a temporary list of all display adapter formats.
            Dim allowedAdapterFormat As Format
            Dim displayMode As DisplayMode
            For Each displayMode In ai.SupportedDisplayModes()
                If displayMode.Width < AppMinFullscreenWidth Then
                    GoTo ContinueForEach3
                End If
                If displayMode.Height < AppMinFullscreenHeight Then
                    GoTo ContinueForEach3
                End If
                If GraphicsUtility.ColorChannelBits(displayMode.Format) < AppMinColorChannelBits Then
                    GoTo ContinueForEach3
                End If
                adapterInfo.DisplayModeList.Add(displayMode)
                If Not adapterFormatList.Contains(displayMode.Format) Then
                    adapterFormatList.Add(displayMode.Format)
                End If
ContinueForEach3:
            Next displayMode
            ' Sort displaymode list
            Dim dmc As New DisplayModeComparer()
            adapterInfo.DisplayModeList.Sort(dmc)

            ' Get info for each device on this adapter
            EnumerateDevices(adapterInfo, adapterFormatList)

            ' If at least one device on this adapter is available and compatible
            ' with the app, add the adapterInfo to the list
            If adapterInfo.DeviceInfoList.Count = 0 Then
                GoTo ContinueForEach1
            End If
            AdapterInfoList.Add(adapterInfo)
ContinueForEach1:
        Next ai
    End Sub 'Enumerate


    '/ <summary>
    '/ Enumerates D3D devices for a particular adapter
    '/ </summary>
    Protected Sub EnumerateDevices(ByVal adapterInfo As GraphicsAdapterInfo, ByVal adapterFormatList As ArrayList)
        Dim devTypeArray() As DeviceType = {DeviceType.Hardware, DeviceType.Software, DeviceType.Reference}

        Dim devType As DeviceType
        For Each devType In devTypeArray
            Dim deviceInfo As New GraphicsDeviceInfo()
            deviceInfo.AdapterOrdinal = adapterInfo.AdapterOrdinal
            deviceInfo.DevType = devType
            Try
                deviceInfo.Caps = Manager.GetDeviceCaps(adapterInfo.AdapterOrdinal, devType)
            Catch
                GoTo ContinueForEach1
            End Try
            ' Get info for each devicecombo on this device
            EnumerateDeviceCombos(deviceInfo, adapterFormatList)

            ' If at least one devicecombo for this device is found, 
            ' add the deviceInfo to the list
            If deviceInfo.DeviceComboList.Count = 0 Then
                GoTo ContinueForEach1
            End If
            adapterInfo.DeviceInfoList.Add(deviceInfo)
ContinueForEach1:
        Next devType
    End Sub 'EnumerateDevices


    '/ <summary>
    '/ Enumerates DeviceCombos for a particular device
    '/ </summary>
    Protected Sub EnumerateDeviceCombos(ByVal deviceInfo As GraphicsDeviceInfo, ByVal adapterFormatList As ArrayList)
        Dim backBufferFormatArray() As Format = {Format.A8R8G8B8, Format.X8R8G8B8, Format.A2R10G10B10, Format.R5G6B5, Format.A1R5G5B5, Format.X1R5G5B5}
        Dim isWindowedArray() As Boolean = {False, True}

        ' See which adapter formats are supported by this device
        Dim adapterFormat As Format
        For Each adapterFormat In adapterFormatList
            Dim backBufferFormat As Format
            For Each backBufferFormat In backBufferFormatArray
                If GraphicsUtility.AlphaChannelBits(backBufferFormat) < AppMinAlphaChannelBits Then
                    GoTo ContinueForEach2
                End If
                Dim isWindowed As Boolean
                For Each isWindowed In isWindowedArray
                    If Not isWindowed And AppRequiresWindowed Then
                        GoTo ContinueForEach3
                    End If
                    If isWindowed And AppRequiresFullscreen Then
                        GoTo ContinueForEach3
                    End If
                    If Not Manager.CheckDeviceType(deviceInfo.AdapterOrdinal, deviceInfo.DevType, adapterFormat, backBufferFormat, isWindowed) Then
                        GoTo ContinueForEach3
                    End If
                    ' At this point, we have an adapter/device/adapterformat/backbufferformat/iswindowed
                    ' DeviceCombo that is supported by the system.  We still need to confirm that it's 
                    ' compatible with the app, and find one or more suitable depth/stencil buffer format,
                    ' multisample type, vertex processing type, and present interval.
                    Dim deviceCombo As New DeviceCombo()
                    deviceCombo.AdapterOrdinal = deviceInfo.AdapterOrdinal
                    deviceCombo.DevType = deviceInfo.DevType
                    deviceCombo.AdapterFormat = adapterFormat
                    deviceCombo.BackBufferFormat = backBufferFormat
                    deviceCombo.IsWindowed = isWindowed
                    If AppUsesDepthBuffer Then
                        BuildDepthStencilFormatList(deviceCombo)
                        If deviceCombo.DepthStencilFormatList.Count = 0 Then
                            GoTo ContinueForEach3
                        End If
                    End If
                    BuildMultiSampleTypeList(deviceCombo)
                    If deviceCombo.MultiSampleTypeList.Count = 0 Then
                        GoTo ContinueForEach3
                    End If
                    BuildDepthStencilMultiSampleConflictList(deviceCombo)
                    BuildVertexProcessingTypeList(deviceInfo, deviceCombo)
                    If deviceCombo.VertexProcessingTypeList.Count = 0 Then
                        GoTo ContinueForEach3
                    End If
                    BuildPresentIntervalList(deviceInfo, deviceCombo)
                    If deviceCombo.PresentIntervalList.Count = 0 Then
                        GoTo ContinueForEach3
                    End If
                    deviceInfo.DeviceComboList.Add(deviceCombo)
ContinueForEach3:
                Next isWindowed
ContinueForEach2:
            Next backBufferFormat
        Next adapterFormat
    End Sub 'EnumerateDeviceCombos


    '/ <summary>
    '/ Adds all depth/stencil formats that are compatible with the device and app to
    '/ the given deviceCombo
    '/ </summary>
    Public Sub BuildDepthStencilFormatList(ByVal deviceCombo As DeviceCombo)
        Dim depthStencilFormatArray As DepthFormat() = {DepthFormat.D16, DepthFormat.D15S1, DepthFormat.D24X8, DepthFormat.D24S8, DepthFormat.D24X4S4, DepthFormat.D32}

        Dim depthStencilFmt As Format
        For Each depthStencilFmt In depthStencilFormatArray
            If GraphicsUtility.DepthBits(depthStencilFmt) < AppMinDepthBits Then
                GoTo ContinueForEach1
            End If
            If GraphicsUtility.StencilBits(depthStencilFmt) < AppMinStencilBits Then
                GoTo ContinueForEach1
            End If
            If Manager.CheckDeviceFormat(deviceCombo.AdapterOrdinal, deviceCombo.DevType, deviceCombo.AdapterFormat, Usage.DepthStencil, ResourceType.Surface, depthStencilFmt) Then
                If Manager.CheckDepthStencilMatch(deviceCombo.AdapterOrdinal, deviceCombo.DevType, deviceCombo.AdapterFormat, deviceCombo.BackBufferFormat, depthStencilFmt) Then
                    deviceCombo.DepthStencilFormatList.Add(depthStencilFmt)
                End If
            End If
ContinueForEach1:
        Next depthStencilFmt
    End Sub 'BuildDepthStencilFormatList


    '/ <summary>
    '/ Adds all multisample types that are compatible with the device and app to
    '/ the given deviceCombo
    '/ </summary>
    Public Sub BuildMultiSampleTypeList(ByVal deviceCombo As DeviceCombo)
        Dim msTypeArray As MultiSampleType() = {MultiSampleType.None, MultiSampleType.NonMaskable, MultiSampleType.TwoSamples, MultiSampleType.ThreeSamples, MultiSampleType.FourSamples, MultiSampleType.FiveSamples, MultiSampleType.SixSamples, MultiSampleType.SevenSamples, MultiSampleType.EightSamples, MultiSampleType.NineSamples, MultiSampleType.TenSamples, MultiSampleType.ElevenSamples, MultiSampleType.TwelveSamples, MultiSampleType.ThirteenSamples, MultiSampleType.FourteenSamples, MultiSampleType.FifteenSamples, MultiSampleType.SixteenSamples}
        Dim msType As MultiSampleType
        For Each msType In msTypeArray
            Dim result As Integer
            Dim qualityLevels As Integer = 0
            If Manager.CheckDeviceMultiSampleType(deviceCombo.AdapterOrdinal, deviceCombo.DevType, deviceCombo.BackBufferFormat, deviceCombo.IsWindowed, msType, result, qualityLevels) Then
                deviceCombo.MultiSampleTypeList.Add(msType)
                deviceCombo.MultiSampleQualityList.Add(qualityLevels)
            End If
        Next msType
    End Sub 'BuildMultiSampleTypeList


    '/ <summary>
    '/ Finds any depthstencil formats that are incompatible with multisample types and
    '/  builds a list of them.
    '/ </summary>
    Public Sub BuildDepthStencilMultiSampleConflictList(ByVal deviceCombo As DeviceCombo)
        Dim DSMSConflict As DepthStencilMultiSampleConflict
        Dim dsFmt As DepthFormat
        Dim msType As MultiSampleType
        For Each dsFmt In deviceCombo.DepthStencilFormatList
            For Each msType In deviceCombo.MultiSampleTypeList
                If Not Manager.CheckDeviceMultiSampleType(deviceCombo.AdapterOrdinal, deviceCombo.DevType, dsFmt, deviceCombo.IsWindowed, msType) Then
                    DSMSConflict = New DepthStencilMultiSampleConflict()
                    DSMSConflict.DepthStencilFormat = dsFmt
                    DSMSConflict.MultiSampleType = msType
                    deviceCombo.DepthStencilMultiSampleConflictList.Add(DSMSConflict)
                End If
            Next
        Next dsFmt
    End Sub 'BuildMultiSampleTypeList


    '/ <summary>
    '/ Adds all vertex processing types that are compatible with the device and app to
    '/ the given deviceCombo
    '/ </summary>
    Public Sub BuildVertexProcessingTypeList(ByVal deviceInfo As GraphicsDeviceInfo, ByVal deviceCombo As DeviceCombo)
        If deviceInfo.Caps.DeviceCaps.SupportsHardwareTransformAndLight Then
            If deviceInfo.Caps.DeviceCaps.SupportsPureDevice Then
                If ConfirmDeviceCallback Is Nothing Or ConfirmDeviceCallback(deviceInfo.Caps, VertexProcessingType.PureHardware, deviceCombo.AdapterFormat, deviceCombo.BackBufferFormat) Then
                    deviceCombo.VertexProcessingTypeList.Add(VertexProcessingType.PureHardware)
                End If
            End If
            If ConfirmDeviceCallback Is Nothing Or ConfirmDeviceCallback(deviceInfo.Caps, VertexProcessingType.Hardware, deviceCombo.AdapterFormat, deviceCombo.BackBufferFormat) Then
                deviceCombo.VertexProcessingTypeList.Add(VertexProcessingType.Hardware)
            End If
            If AppUsesMixedVP And (ConfirmDeviceCallback Is Nothing Or ConfirmDeviceCallback(deviceInfo.Caps, VertexProcessingType.Mixed, deviceCombo.AdapterFormat, deviceCombo.BackBufferFormat)) Then
                deviceCombo.VertexProcessingTypeList.Add(VertexProcessingType.Mixed)
            End If
        End If
        If ConfirmDeviceCallback Is Nothing Or ConfirmDeviceCallback(deviceInfo.Caps, VertexProcessingType.Software, deviceCombo.AdapterFormat, deviceCombo.BackBufferFormat) Then
            deviceCombo.VertexProcessingTypeList.Add(VertexProcessingType.Software)
        End If
    End Sub 'BuildVertexProcessingTypeList


    '/ <summary>
    '/ Adds all present intervals that are compatible with the device and app to
    '/ the given deviceCombo
    '/ </summary>
    Public Sub BuildPresentIntervalList(ByVal deviceInfo As GraphicsDeviceInfo, ByVal deviceCombo As DeviceCombo)
        Dim piArray As PresentInterval() = {PresentInterval.Immediate, PresentInterval.Default, PresentInterval.One, PresentInterval.Two, PresentInterval.Three, PresentInterval.Four}

        Dim pi As PresentInterval
        For Each pi In piArray
            If deviceCombo.IsWindowed Then
                If pi = PresentInterval.Two Or pi = PresentInterval.Three Or pi = PresentInterval.Four Then
                    ' These intervals are not supported in windowed mode.
                    GoTo ContinueForEach1
                End If
            End If
            ' Note that PresentInterval.Default is zero, so you
            ' can't do a caps check for it -- it is always available.
            If pi = PresentInterval.Default Or ((deviceInfo.Caps.PresentationIntervals And pi) <> 0) Then
                deviceCombo.PresentIntervalList.Add(pi)
            End If
ContinueForEach1:
        Next pi
    End Sub 'BuildPresentIntervalList
End Class 'D3DEnumeration