'-----------------------------------------------------------------------------
' File: D3DApp.vb
'
' Desc: Application class for the Direct3D samples framework library.
'
' Copyright (c) 2001-2002 Microsoft Corporation. All rights reserved.
'-----------------------------------------------------------------------------
Imports System
Imports Microsoft.DirectX
Imports Microsoft.DirectX.Direct3D
Imports Direct3D = Microsoft.DirectX.Direct3D

'/ Messages that can be used when displaying an error
'/ </summary>
Public Enum ApplicationMessage
    None
    ApplicationMustExit
    WarnSwitchToRef
End Enum 'ApplicationMessage

'/ The default sample exception type
'/ </summary>
Public Class SampleException
    Inherits System.ApplicationException


    '/ <summary>
    '/ Return information about the exception
    '/ </summary>

    Public Overrides ReadOnly Property Message() As String
        Get
            Dim strMsg As String = String.Empty

            strMsg = "Generic application error. Enable" + ControlChars.Lf
            strMsg += "debug output for detailed information."

            Return strMsg
        End Get
    End Property
End Class 'SampleException
 _


'/ <summary>
'/ Exception informing user no compatible devices were found
'/ </summary>
Public Class NoCompatibleDevicesException
    Inherits SampleException


    '/ <summary>
    '/ Return information about the exception
    '/ </summary>

    Public Overrides ReadOnly Property Message() As String
        Get
            Dim strMsg As String = String.Empty
            strMsg = "This sample cannot run in a desktop" + ControlChars.Lf
            strMsg += "window with the current display settings." + ControlChars.Lf
            strMsg += "Please change your desktop settings to a" + ControlChars.Lf
            strMsg += "16- or 32-bit display mode and re-run this" + ControlChars.Lf
            strMsg += "sample."

            Return strMsg
        End Get
    End Property
End Class 'NoCompatibleDevicesException
 _


'/ <summary>
'/ An exception for when the ReferenceDevice is null
'/ </summary>
Public Class NullReferenceDeviceException
    Inherits SampleException
    '/ <summary>
    '/ Return information about the exception
    '/ </summary>

    Public Overrides ReadOnly Property Message() As String
        Get
            Dim strMsg As String = String.Empty
            strMsg = "Warning: Nothing will be rendered." + ControlChars.Lf
            strMsg += "The reference rendering device was selected, but your" + ControlChars.Lf
            strMsg += "computer only has a reduced-functionality reference device" + ControlChars.Lf
            strMsg += "installed.  Install the DirectX SDK to get the full" + ControlChars.Lf
            strMsg += "reference device." + ControlChars.Lf

            Return strMsg
        End Get
    End Property
End Class 'NullReferenceDeviceException
 _

'/ <summary>
'/ An exception for when reset fails
'/ </summary>
Public Class ResetFailedException
    Inherits SampleException
    '/ <summary>
    '/ Return information about the exception
    '/ </summary>

    Public Overrides ReadOnly Property Message() As String
        Get
            Dim strMsg As String = String.Empty
            strMsg = "Could not reset the Direct3D device."

            Return strMsg
        End Get
    End Property
End Class 'ResetFailedException
 _

'/ <summary>
'/ The exception thrown when media couldn't be found
'/ </summary>
Public Class MediaNotFoundException
    Inherits SampleException
    Private mediaFile As String

    Public Sub New(ByVal filename As String)
        mediaFile = filename
    End Sub 'New

    Public Sub New()
        mediaFile = String.Empty
    End Sub 'New
    '/ <summary>
    '/ Return information about the exception
    '/ </summary>

    Public Overrides ReadOnly Property Message() As String
        Get
            Dim strMsg As String = String.Empty
            strMsg = "Could not load required media."
            If mediaFile.Length > 0 Then
                strMsg += String.Format(ControlChars.Cr + ControlChars.Lf + "File: {0}", mediaFile)
            End If
            Return strMsg
        End Get
    End Property
End Class 'MediaNotFoundException
 _

'
'/ <summary>
'/ The base class for all the graphics (D3D) samples, it derives from windows forms
'/ </summary>
Public Class GraphicsSample
    Inherits System.Windows.Forms.Form

    ' The menu items that *all* samples will need
    Protected mnuMain As System.Windows.Forms.MainMenu '
    Protected mnuFile As System.Windows.Forms.MenuItem
    Private WithEvents mnuGo As System.Windows.Forms.MenuItem
    Private WithEvents mnuSingle As System.Windows.Forms.MenuItem
    Private mnuBreak1 As System.Windows.Forms.MenuItem
    Private WithEvents mnuChange As System.Windows.Forms.MenuItem
    Private mnuBreak2 As System.Windows.Forms.MenuItem
    Protected WithEvents mnuExit As System.Windows.Forms.MenuItem

    ' The window we will render too
    Private ourRenderTarget As System.Windows.Forms.Control
    ' Should we use the default windows
    Protected isUsingMenus As Boolean = True

    ' We need to keep track of our enumeration settings
    Protected enumerationSettings As New D3DEnumeration()
    Protected graphicsSettings As New D3DSettings()
    Private isMaximized As Boolean = False ' Are we maximized?
    Private isHandlingSizeChanges As Boolean = True ' Are we handling size changes?
    Private isClosing As Boolean = False ' Are we closing?
    Private isChangingFormStyle As Boolean = False ' Are we changing the form style?
    Private isWindowActive As Boolean = True ' Are we waiting for the window to get focus?

    Private lastTime As Single = 0.0F ' The last time
    Private frames As Integer = 0 ' Number of rames since our last update
    Private appPausedCount As Integer = 0 ' How many times has the app been paused (and when can it resume)?
    ' Internal variables for the state of the app
    Protected windowed As Boolean
    Protected active As Boolean
    Protected ready As Boolean
    Protected hasFocus As Boolean
    Protected isMultiThreaded As Boolean = False

    ' Internal variables used for timing
    Protected frameMoving As Boolean
    Protected isSingleStep As Boolean
    ' Main objects used for creating and rendering the 3D scene
    Protected presentParams As New PresentParameters() ' Parameters for CreateDevice/Reset
    Protected device As device ' The rendering device
    Protected renderState As RenderStates
    Protected sampleState As SamplerStates
    Protected textureStates As textureStates
    Private graphicsCaps As Caps ' Caps for the device

    Protected ReadOnly Property Caps() As Caps
        Get
            Return graphicsCaps
        End Get ' Indicate sw or hw vertex processing
    End Property
    Private behavior As CreateFlags

    Protected ReadOnly Property BehaviorFlags() As BehaviorFlags
        Get
            Return New BehaviorFlags(behavior)
        End Get
    End Property

    Protected Property RenderTarget() As System.Windows.Forms.Control
        Get
            Return ourRenderTarget
        End Get
        Set(ByVal Value As System.Windows.Forms.Control)
            ourRenderTarget = Value
        End Set
    End Property ' Variables for timing
    Protected appTime As Single ' Current time in seconds
    Protected elapsedTime As Single ' Time elapsed since last frame
    Protected framePerSecond As Single ' Instanteous frame rate
    Protected deviceStats As String ' String to hold D3D device stats
    Protected frameStats As String ' String to hold frame stats
    Private deviceLost As Boolean = False

    ' Overridable variables for the app
    Private MinimumDepthBits As Integer ' Minimum number of bits needed in depth buffer

    Protected Property MinDepthBits() As Integer
        Get
            Return MinimumDepthBits
        End Get
        Set(ByVal Value As Integer)
            MinimumDepthBits = Value
            enumerationSettings.AppMinDepthBits = Value
        End Set ' Minimum number of bits needed in stencil buffer
    End Property
    Private minimumStencilBits As Integer

    Protected Property MinStencilBits() As Integer
        Get
            Return minimumStencilBits
        End Get
        Set(ByVal Value As Integer)
            minimumStencilBits = Value
            enumerationSettings.AppMinStencilBits = Value
        End Set ' Whether to show cursor when fullscreen
    End Property
    Protected showCursorWhenFullscreen As Boolean
    Protected clipCursorWhenFullscreen As Boolean ' Whether to limit cursor pos when fullscreen
    Protected startFullscreen As Boolean ' Whether to start up the app in fullscreen mode

    Private storedSize As System.Drawing.Size
    Private storedLocation As System.Drawing.Point

    ' Overridable functions for the 3D scene created by the app
    Protected Overridable Function ConfirmDevice(ByVal caps As Caps, ByVal vertexProcessingType As VertexProcessingType, ByVal adapterFormat As Format, ByVal backBufferFormat As Format) As Boolean
        Return True
    End Function 'ConfirmDevice

    Protected Overridable Sub OneTimeSceneInitialization() ' Do Nothing 
    End Sub 'OneTimeSceneInitialization

    Protected Overridable Sub InitializeDeviceObjects() ' Do Nothing 
    End Sub 'InitializeDeviceObjects

    Protected Overridable Sub RestoreDeviceObjects(ByVal sender As System.Object, ByVal e As System.EventArgs) ' Do Nothing 
    End Sub 'RestoreDeviceObjects

    Protected Overridable Sub FrameMove() ' Do Nothing 
    End Sub 'FrameMove

    Protected Overridable Sub Render() ' Do Nothing 
    End Sub 'Render

    Protected Overridable Sub InvalidateDeviceObjects(ByVal sender As System.Object, ByVal e As System.EventArgs) ' Do Nothing 
    End Sub 'InvalidateDeviceObjects

    Protected Overridable Sub DeleteDeviceObjects(ByVal sender As System.Object, ByVal e As System.EventArgs) ' Do Nothing 
    End Sub 'DeleteDeviceObjects





    '/ <summary>
    '/ Constructor
    '/ </summary>
    Public Sub New()
        device = Nothing
        active = False
        ready = False
        hasFocus = False
        behavior = 0

        ourRenderTarget = Me
        frameMoving = True
        isSingleStep = False
        framePerSecond = 0.0F
        deviceStats = Nothing
        frameStats = Nothing

        Me.Text = "D3D9 Sample"
        Me.ClientSize = New System.Drawing.Size(400, 300)
        Me.KeyPreview = True

        MinDepthBits = 16
        MinStencilBits = 0
        showCursorWhenFullscreen = False
        startFullscreen = False

        ' When clipCursorWhenFullscreen is TRUE, the cursor is limited to
        ' the device window when the app goes fullscreen.  This prevents users
        ' from accidentally clicking outside the app window on a multimon system.
        ' This flag is turned off by default for debug builds, since it makes 
        ' multimon debugging difficult.
        '
#If DEBUG Then
        clipCursorWhenFullscreen = False
#Else
        clipCursorWhenFullscreen = True
#End If
        InitializeComponent()
    End Sub 'New




    '/ <summary>
    '/ Picks the best graphics device, and initializes it
    '/ </summary>
    '/ <returns>true if a good device was found, false otherwise</returns>
    Public Function CreateGraphicsSample() As Boolean
        enumerationSettings.ConfirmDeviceCallback = New D3DEnumeration.ConfirmDeviceCallbackType(AddressOf Me.ConfirmDevice)
        enumerationSettings.Enumerate()

        If ourRenderTarget.Cursor Is Nothing Then
            ' Set up a default cursor
            ourRenderTarget.Cursor = System.Windows.Forms.Cursors.Default
        End If
        ' if our render target is the main window and we haven't said 
        ' ignore the menus, add our menu
        If ourRenderTarget Is Me And isUsingMenus Then
            Me.Menu = mnuMain
        End If
        Try
            ChooseInitialSettings()

            ' Initialize the application timer
            DXUtil.Timer(DirectXTimer.Start)
            ' Initialize the app's custom scene stuff
            OneTimeSceneInitialization()
            ' Initialize the 3D environment for the app
            InitializeEnvironment()
        Catch d3de As SampleException
            HandleSampleException(d3de, ApplicationMessage.ApplicationMustExit)
            Return False
        Catch
            HandleSampleException(New SampleException(), ApplicationMessage.ApplicationMustExit)
            Return False
        End Try

        ' The app is ready to go
        ready = True

        Return True
    End Function 'CreateGraphicsSample




    '/ <summary>
    '/ Sets up graphicsSettings with best available windowed mode, subject to 
    '/ the doesRequireHardware and doesRequireReference constraints.  
    '/ </summary>
    '/ <param name="doesRequireHardware">Does the device require hardware support</param>
    '/ <param name="doesRequireReference">Does the device require the ref device</param>
    '/ <returns>true if a mode is found, false otherwise</returns>
    Public Function FindBestWindowedMode(ByVal doesRequireHardware As Boolean, ByVal doesRequireReference As Boolean) As Boolean
        ' Get display mode of primary adapter (which is assumed to be where the window 
        ' will appear)
        Dim primaryDesktopDisplayMode As DisplayMode = Manager.Adapters(0).CurrentDisplayMode

        Dim bestAdapterInfo As GraphicsAdapterInfo = Nothing
        Dim bestDeviceInfo As GraphicsDeviceInfo = Nothing
        Dim bestDeviceCombo As DeviceCombo = Nothing

        Dim adapterInfo As GraphicsAdapterInfo
        For Each adapterInfo In enumerationSettings.AdapterInfoList
            Dim deviceInfo As GraphicsDeviceInfo
            For Each deviceInfo In adapterInfo.DeviceInfoList
                If doesRequireHardware And deviceInfo.DevType <> DeviceType.Hardware Then
                    GoTo ContinueForEach2
                End If
                If doesRequireReference And deviceInfo.DevType <> DeviceType.Reference Then
                    GoTo ContinueForEach2
                End If
                Dim deviceCombo As DeviceCombo
                For Each deviceCombo In deviceInfo.DeviceComboList
                    Dim adapterMatchesBackBuffer As Boolean = deviceCombo.BackBufferFormat = deviceCombo.AdapterFormat
                    If Not deviceCombo.IsWindowed Then
                        GoTo ContinueForEach3
                    End If
                    If deviceCombo.AdapterFormat <> primaryDesktopDisplayMode.Format Then
                        GoTo ContinueForEach3
                    End If ' If we haven't found a compatible DeviceCombo yet, or if this set
                    ' is better (because it's a HAL, and/or because formats match better),
                    ' save it
                    If bestDeviceCombo Is Nothing Then
                        bestAdapterInfo = adapterInfo
                        bestDeviceInfo = deviceInfo
                        bestDeviceCombo = deviceCombo
                        If deviceInfo.DevType = DeviceType.Hardware And adapterMatchesBackBuffer Then
                            ' This windowed device combo looks great -- take it
                            GoTo EndWindowedDeviceComboSearch
                        End If
                    ElseIf (bestDeviceCombo.DevType <> DeviceType.Hardware And deviceInfo.DevType = DeviceType.Hardware) Or (deviceCombo.DevType = DeviceType.Hardware And adapterMatchesBackBuffer) Then
                        bestAdapterInfo = adapterInfo
                        bestDeviceInfo = deviceInfo
                        bestDeviceCombo = deviceCombo
                        If deviceInfo.DevType = DeviceType.Hardware And adapterMatchesBackBuffer Then
                            ' This windowed device combo looks great -- take it
                            GoTo EndWindowedDeviceComboSearch
                        End If
                    End If
ContinueForEach3:   ' Otherwise keep looking for a better windowed device combo
                Next deviceCombo
ContinueForEach2:
            Next deviceInfo
        Next adapterInfo
EndWindowedDeviceComboSearch:
        If bestDeviceCombo Is Nothing Then
            Return False
        End If
        graphicsSettings.WindowedAdapterInfo = bestAdapterInfo
        graphicsSettings.WindowedDeviceInfo = bestDeviceInfo
        graphicsSettings.WindowedDeviceCombo = bestDeviceCombo
        graphicsSettings.IsWindowed = True
        graphicsSettings.WindowedDisplayMode = primaryDesktopDisplayMode
        graphicsSettings.WindowedWidth = ourRenderTarget.ClientRectangle.Right - ourRenderTarget.ClientRectangle.Left
        graphicsSettings.WindowedHeight = ourRenderTarget.ClientRectangle.Bottom - ourRenderTarget.ClientRectangle.Top
        If enumerationSettings.AppUsesDepthBuffer Then
            graphicsSettings.WindowedDepthStencilBufferFormat = CType(bestDeviceCombo.DepthStencilFormatList(0), DepthFormat)
        End If
        graphicsSettings.WindowedMultisampleType = CType(bestDeviceCombo.MultiSampleTypeList(0), MultiSampleType)
        graphicsSettings.WindowedMultisampleQuality = 0
        graphicsSettings.WindowedVertexProcessingType = CType(bestDeviceCombo.VertexProcessingTypeList(0), VertexProcessingType)
        graphicsSettings.WindowedPresentInterval = CType(bestDeviceCombo.PresentIntervalList(0), PresentInterval)
        Return True
    End Function 'FindBestWindowedMode





    '/ <summary>
    '/ Sets up graphicsSettings with best available fullscreen mode, subject to 
    '/ the doesRequireHardware and doesRequireReference constraints.  
    '/ </summary>
    '/ <param name="doesRequireHardware">Does the device require hardware support</param>
    '/ <param name="doesRequireReference">Does the device require the ref device</param>
    '/ <returns>true if a mode is found, false otherwise</returns>
    Public Function FindBestFullscreenMode(ByVal doesRequireHardware As Boolean, ByVal doesRequireReference As Boolean) As Boolean
        ' For fullscreen, default to first HAL DeviceCombo that supports the current desktop 
        ' display mode, or any display mode if HAL is not compatible with the desktop mode, or 
        ' non-HAL if no HAL is available
        Dim adapterDesktopDisplayMode As New DisplayMode()
        Dim bestAdapterDesktopDisplayMode As New DisplayMode()
        Dim bestDisplayMode As New DisplayMode()
        bestAdapterDesktopDisplayMode.Width = 0
        bestAdapterDesktopDisplayMode.Height = 0
        bestAdapterDesktopDisplayMode.Format = 0
        bestAdapterDesktopDisplayMode.RefreshRate = 0

        Dim bestAdapterInfo As GraphicsAdapterInfo = Nothing
        Dim bestDeviceInfo As GraphicsDeviceInfo = Nothing
        Dim bestDeviceCombo As DeviceCombo = Nothing

        Dim adapterInfo As GraphicsAdapterInfo
        For Each adapterInfo In enumerationSettings.AdapterInfoList
            adapterDesktopDisplayMode = Manager.Adapters(adapterInfo.AdapterOrdinal).CurrentDisplayMode
            Dim deviceInfo As GraphicsDeviceInfo
            For Each deviceInfo In adapterInfo.DeviceInfoList
                If doesRequireHardware And deviceInfo.DevType <> DeviceType.Hardware Then
                    GoTo ContinueForEach2
                End If
                If doesRequireReference And deviceInfo.DevType <> DeviceType.Reference Then
                    GoTo ContinueForEach2
                End If
                Dim deviceCombo As DeviceCombo
                For Each deviceCombo In deviceInfo.DeviceComboList
                    Dim adapterMatchesBackBuffer As Boolean = deviceCombo.BackBufferFormat = deviceCombo.AdapterFormat
                    Dim adapterMatchesDesktop As Boolean = deviceCombo.AdapterFormat = adapterDesktopDisplayMode.Format
                    If deviceCombo.IsWindowed Then
                        GoTo ContinueForEach3
                    End If ' If we haven't found a compatible set yet, or if this set
                    ' is better (because it's a HAL, and/or because formats match better),
                    ' save it
                    If bestDeviceCombo Is Nothing Then
                        bestAdapterDesktopDisplayMode = adapterDesktopDisplayMode
                        bestAdapterInfo = adapterInfo
                        bestDeviceInfo = deviceInfo
                        bestDeviceCombo = deviceCombo
                        If deviceInfo.DevType = DeviceType.Hardware And adapterMatchesDesktop And adapterMatchesBackBuffer Then

                            ' This fullscreen device combo looks great -- take it
                            GoTo EndFullscreenDeviceComboSearch
                        End If
                    ElseIf (bestDeviceCombo.DevType <> DeviceType.Hardware And deviceInfo.DevType = DeviceType.Hardware) Or (bestDeviceCombo.DevType = DeviceType.Hardware And bestDeviceCombo.AdapterFormat <> adapterDesktopDisplayMode.Format And adapterMatchesDesktop) Or (bestDeviceCombo.DevType = DeviceType.Hardware And adapterMatchesDesktop And adapterMatchesBackBuffer) Then
                        bestAdapterDesktopDisplayMode = adapterDesktopDisplayMode
                        bestAdapterInfo = adapterInfo
                        bestDeviceInfo = deviceInfo
                        bestDeviceCombo = deviceCombo
                        If deviceInfo.DevType = DeviceType.Hardware And adapterMatchesDesktop And adapterMatchesBackBuffer Then

                            ' This fullscreen device combo looks great -- take it
                            GoTo EndFullscreenDeviceComboSearch
                        End If
                    End If
ContinueForEach3:   ' Otherwise keep looking for a better fullscreen device combo
                Next deviceCombo
ContinueForEach2:
            Next deviceInfo
        Next adapterInfo
EndFullscreenDeviceComboSearch:
        If bestDeviceCombo Is Nothing Then
            Return False
        End If
        ' Need to find a display mode on the best adapter that uses pBestDeviceCombo->AdapterFormat
        ' and is as close to bestAdapterDesktopDisplayMode's res as possible
        bestDisplayMode.Width = 0
        bestDisplayMode.Height = 0
        bestDisplayMode.Format = 0
        bestDisplayMode.RefreshRate = 0
        Dim displayMode As DisplayMode
        For Each displayMode In bestAdapterInfo.DisplayModeList
            If displayMode.Format <> bestDeviceCombo.AdapterFormat Then
                GoTo ContinueForEach1
            End If
            If displayMode.Width = bestAdapterDesktopDisplayMode.Width And displayMode.Height = bestAdapterDesktopDisplayMode.Height And displayMode.RefreshRate = bestAdapterDesktopDisplayMode.RefreshRate Then
                ' found a perfect match, so stop
                bestDisplayMode = displayMode
                Exit For
            ElseIf displayMode.Width = bestAdapterDesktopDisplayMode.Width And displayMode.Height = bestAdapterDesktopDisplayMode.Height And displayMode.RefreshRate > bestDisplayMode.RefreshRate Then
                ' refresh rate doesn't match, but width/height match, so keep this
                ' and keep looking
                bestDisplayMode = displayMode
            ElseIf bestDisplayMode.Width = bestAdapterDesktopDisplayMode.Width Then
                ' width matches, so keep this and keep looking
                bestDisplayMode = displayMode
            ElseIf bestDisplayMode.Width = 0 Then
                ' we don't have anything better yet, so keep this and keep looking
                bestDisplayMode = displayMode
            End If
ContinueForEach1:
        Next displayMode
        graphicsSettings.FullscreenAdapterInfo = bestAdapterInfo
        graphicsSettings.FullscreenDeviceInfo = bestDeviceInfo
        graphicsSettings.FullscreenDeviceCombo = bestDeviceCombo
        graphicsSettings.IsWindowed = False
        graphicsSettings.FullscreenDisplayMode = bestDisplayMode
        If enumerationSettings.AppUsesDepthBuffer Then
            graphicsSettings.FullscreenDepthStencilBufferFormat = CType(bestDeviceCombo.DepthStencilFormatList(0), DepthFormat)
        End If
        graphicsSettings.FullscreenMultisampleType = CType(bestDeviceCombo.MultiSampleTypeList(0), MultiSampleType)
        graphicsSettings.FullscreenMultisampleQuality = 0
        graphicsSettings.FullscreenVertexProcessingType = CType(bestDeviceCombo.VertexProcessingTypeList(0), VertexProcessingType)
        graphicsSettings.FullscreenPresentInterval = PresentInterval.Default
        Return True
    End Function 'FindBestFullscreenMode




    '/ <summary>
    '/ Choose the initial settings for the application
    '/ </summary>
    '/ <returns>true if the settings were initialized</returns>
    Public Function ChooseInitialSettings() As Boolean
        Dim foundFullscreenMode As Boolean = FindBestFullscreenMode(False, False)
        Dim foundWindowedMode As Boolean = FindBestWindowedMode(False, False)
        If startFullscreen And foundFullscreenMode Then
            graphicsSettings.IsWindowed = False
        End If
        If Not foundFullscreenMode And Not foundWindowedMode Then
            Throw New NoCompatibleDevicesException()
        End If
        Return foundFullscreenMode Or foundWindowedMode
    End Function 'ChooseInitialSettings




    '/ <summary>
    '/ Build presentation parameters from the current settings
    '/ </summary>
    Public Sub BuildPresentParamsFromSettings()
        presentParams.Windowed = graphicsSettings.IsWindowed
        presentParams.BackBufferCount = 1
        presentParams.MultiSample = graphicsSettings.MultisampleType
        presentParams.MultiSampleQuality = graphicsSettings.MultisampleQuality
        presentParams.SwapEffect = SwapEffect.Discard
        presentParams.EnableAutoDepthStencil = enumerationSettings.AppUsesDepthBuffer
        presentParams.AutoDepthStencilFormat = graphicsSettings.DepthStencilBufferFormat
        presentParams.PresentFlag = PresentFlag.None
        If windowed Then
            presentParams.BackBufferWidth = ourRenderTarget.ClientRectangle.Right - ourRenderTarget.ClientRectangle.Left
            presentParams.BackBufferHeight = ourRenderTarget.ClientRectangle.Bottom - ourRenderTarget.ClientRectangle.Top
            presentParams.BackBufferFormat = graphicsSettings.DeviceCombo.BackBufferFormat
            presentParams.FullScreenRefreshRateInHz = 0
            presentParams.PresentationInterval = PresentInterval.Immediate
            presentParams.DeviceWindow = ourRenderTarget
        Else
            presentParams.BackBufferWidth = graphicsSettings.DisplayMode.Width
            presentParams.BackBufferHeight = graphicsSettings.DisplayMode.Height
            presentParams.BackBufferFormat = graphicsSettings.DeviceCombo.BackBufferFormat
            presentParams.FullScreenRefreshRateInHz = graphicsSettings.DisplayMode.RefreshRate
            presentParams.PresentationInterval = graphicsSettings.PresentInterval
            presentParams.DeviceWindow = Me
        End If
    End Sub 'BuildPresentParamsFromSettings



    '-----------------------------------------------------------------------------
    ' Name: InitializeEnvironment()
    ' Desc: Initialize the graphics environment
    '-----------------------------------------------------------------------------
    Public Sub InitializeEnvironment()
        Dim adapterInfo As GraphicsAdapterInfo = graphicsSettings.AdapterInfo
        Dim deviceInfo As GraphicsDeviceInfo = graphicsSettings.DeviceInfo

        windowed = graphicsSettings.IsWindowed

        ' Set up the presentation parameters
        BuildPresentParamsFromSettings()

        If deviceInfo.Caps.PrimitiveMiscCaps.IsNullReference Then
            ' Warn user about null ref device that can't render anything
            HandleSampleException(New NullReferenceDeviceException(), ApplicationMessage.None)
        End If

        Dim createFlags As New CreateFlags()
        If graphicsSettings.VertexProcessingType = VertexProcessingType.Software Then
            createFlags = createFlags.SoftwareVertexProcessing
        ElseIf graphicsSettings.VertexProcessingType = VertexProcessingType.Mixed Then
            createFlags = createFlags.MixedVertexProcessing
        ElseIf graphicsSettings.VertexProcessingType = VertexProcessingType.Hardware Then
            createFlags = createFlags.HardwareVertexProcessing
        ElseIf graphicsSettings.VertexProcessingType = VertexProcessingType.PureHardware Then
            createFlags = createFlags.HardwareVertexProcessing Or createFlags.PureDevice
        Else
            Throw New ApplicationException()
        End If
        'Make sure to allow multithreaded apps if we need them
        If (isMultiThreaded) Then createFlags = createFlags Or createFlags.MultiThreaded

        Try
            ' Create the device
            device = New Device(graphicsSettings.AdapterOrdinal, graphicsSettings.DevType, CType(IIf(windowed, ourRenderTarget, Me), System.Windows.Forms.Control), createFlags, presentParams)

            ' Cache our local objects
            renderState = device.RenderState
            sampleState = device.SamplerState
            textureStates = device.TextureState
            ' When moving from fullscreen to windowed mode, it is important to
            ' adjust the window size after recreating the device rather than
            ' beforehand to ensure that you get the window size you want.  For
            ' example, when switching from 640x480 fullscreen to windowed with
            ' a 1000x600 window on a 1024x768 desktop, it is impossible to set
            ' the window size to 1000x600 until after the display mode has
            ' changed to 1024x768, because windows cannot be larger than the
            ' desktop.
            If windowed Then
                ' Make sure main window isn't topmost, so error message is visible
                Dim currentClientSize As System.Drawing.Size = Me.ClientSize
                Me.Size = Me.ClientSize
                Me.SendToBack()
                Me.BringToFront()
                Me.ClientSize = currentClientSize
            End If

            ' Store device Caps
            graphicsCaps = device.DeviceCaps
            behavior = createFlags

            ' Store device description
            If deviceInfo.DevType = DeviceType.Reference Then
                deviceStats = "REF"
            ElseIf deviceInfo.DevType = DeviceType.Hardware Then
                deviceStats = "HAL"
            ElseIf deviceInfo.DevType = DeviceType.Software Then
                deviceStats = "SW"
            End If
            Dim behaviorFlags As New BehaviorFlags(createFlags)
            If behaviorFlags.HardwareVertexProcessing And behaviorFlags.PureDevice Then
                If deviceInfo.DevType = DeviceType.Hardware Then
                    deviceStats += " (pure hw vp)"
                Else
                    deviceStats += " (simulated pure hw vp)"
                End If
            ElseIf behaviorFlags.HardwareVertexProcessing Then
                If deviceInfo.DevType = DeviceType.Hardware Then
                    deviceStats += " (hw vp)"
                Else
                    deviceStats += " (simulated hw vp)"
                End If
            ElseIf behaviorFlags.MixedVertexProcessing Then
                If deviceInfo.DevType = DeviceType.Hardware Then
                    deviceStats += " (mixed vp)"
                Else
                    deviceStats += " (simulated mixed vp)"
                End If
            ElseIf behaviorFlags.SoftwareVertexProcessing Then
                deviceStats += " (sw vp)"
            End If

            If deviceInfo.DevType = DeviceType.Hardware Then
                deviceStats += ": "
                deviceStats += adapterInfo.AdapterDetails.Description
            End If

            ' Set up the fullscreen cursor
            If showCursorWhenFullscreen And Not windowed Then
                Dim ourCursor As System.Windows.Forms.Cursor = Me.Cursor
                device.SetCursor(ourCursor, True)
                device.ShowCursor(True)
            End If

            ' Confine cursor to fullscreen window
            If clipCursorWhenFullscreen Then
                If Not windowed Then
                    Dim rcWindow As System.Drawing.Rectangle = Me.ClientRectangle
                End If
            End If

            ' Setup the event handlers for our device
            AddHandler device.DeviceLost, AddressOf Me.InvalidateDeviceObjects
            AddHandler device.DeviceReset, AddressOf Me.RestoreDeviceObjects
            AddHandler device.Disposing, AddressOf Me.DeleteDeviceObjects
            AddHandler device.DeviceResizing, AddressOf Me.EnvironmentResized


            ' Initialize the app's device-dependent objects
            Try
                InitializeDeviceObjects()
                RestoreDeviceObjects(Nothing, Nothing)
                active = True
                Return
            Catch
                ' Cleanup before we try again
                InvalidateDeviceObjects(Nothing, Nothing)
                DeleteDeviceObjects(Nothing, Nothing)
                device.Dispose()
                device = Nothing
                If Me.Disposing Then
                    Return
                End If
            End Try
        Catch
            ' If that failed, fall back to the reference rasterizer
            If deviceInfo.DevType = DeviceType.Hardware Then
                If FindBestWindowedMode(False, True) Then
                    windowed = True
                    ' Make sure main window isn't topmost, so error message is visible
                    Dim currentClientSize As System.Drawing.Size = Me.ClientSize
                    Me.Size = Me.ClientSize
                    Me.SendToBack()
                    Me.BringToFront()
                    Me.ClientSize = currentClientSize

                    ' Let the user know we are switching from HAL to the reference rasterizer
                    HandleSampleException(Nothing, ApplicationMessage.WarnSwitchToRef)

                    InitializeEnvironment()
                End If
            End If
        End Try
    End Sub 'InitializeEnvironment





    '/ <summary>
    '/ Displays sample exceptions to the user
    '/ </summary>
    '/ <param name="e">The exception that was thrown</param>
    '/ <param name="Type">Extra information on how to handle the exception</param>
    Public Sub HandleSampleException(ByVal e As SampleException, ByVal Type As ApplicationMessage)
        ' Build a message to display to the user
        Dim strMsg As String = String.Empty
        If Not (e Is Nothing) Then
            strMsg = e.Message
        End If
        If ApplicationMessage.ApplicationMustExit = Type Then
            strMsg += ControlChars.Lf + ControlChars.Lf + "This sample will now exit."
            System.Windows.Forms.MessageBox.Show(strMsg, Me.Text, System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error)

            ' Close the window, which shuts down the app
            If Me.IsHandleCreated Then
                Me.Close()
            End If
        Else
            If ApplicationMessage.WarnSwitchToRef = Type Then
                strMsg = ControlChars.Lf + ControlChars.Lf + "Switching to the reference rasterizer," + ControlChars.Lf
            End If
            strMsg += "a software device that implements the entire" + ControlChars.Lf
            strMsg += "Direct3D feature set, but runs very slowly."

            System.Windows.Forms.MessageBox.Show(strMsg, Me.Text, System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Information)
        End If
    End Sub 'HandleSampleException





    '/ <summary>
    '/ Fired when our environment was resized
    '/ </summary>
    '/ <param name="sender">the device that's resizing our environment</param>
    '/ <param name="e">Set the cancel member to true to turn off automatic device reset</param>
    Public Sub EnvironmentResized(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs)

        ' Check to see if we're closing or changing the form style
        If ((isClosing) Or (isChangingFormStyle)) Then
            'We are, cancel our reset and exit
            e.Cancel = True
            Return
        End If

        ' Check to see if we're minimizing and our rendering object
        ' is not the form, if so, cancel the resize
        If Not (ourRenderTarget Is Me) And (Me.WindowState = System.Windows.Forms.FormWindowState.Minimized) Then
            e.Cancel = True
        End If

        If (Not isWindowActive) Then
            e.Cancel = True
        End If

        ' Set up the fullscreen cursor
        If showCursorWhenFullscreen And Not windowed Then
            Dim ourCursor As System.Windows.Forms.Cursor = Me.Cursor
            device.SetCursor(ourCursor, True)
            device.ShowCursor(True)
        End If

        ' If the app is paused, trigger the rendering of the current frame
        If False = frameMoving Then
            isSingleStep = True
            DXUtil.Timer(DirectXTimer.Start)
            DXUtil.Timer(DirectXTimer.Stop)
        End If
    End Sub 'EnvironmentResized





    '/ <summary>
    '/ Called when user toggles between fullscreen mode and windowed mode
    '/ </summary>
    Public Sub ToggleFullscreen()
        Dim AdapterOrdinalOld As Integer = graphicsSettings.AdapterOrdinal
        Dim DevTypeOld As DeviceType = graphicsSettings.DevType

        isHandlingSizeChanges = False
        ready = False

        ' Toggle the windowed state
        windowed = Not windowed
        ' Save our maximized settings..
        If Not windowed And isMaximized Then
            Me.WindowState = System.Windows.Forms.FormWindowState.Normal
        End If


        graphicsSettings.IsWindowed = windowed

        ' If AdapterOrdinal and DevType are the same, we can just do a Reset().
        ' If they've changed, we need to do a complete device teardown/rebuild.
        If graphicsSettings.AdapterOrdinal = AdapterOrdinalOld And graphicsSettings.DevType = DevTypeOld Then
            ' Resize the 3D device
            Try
                BuildPresentParamsFromSettings()
                device.Reset(presentParams)
                EnvironmentResized(device, New System.ComponentModel.CancelEventArgs())
            Catch
                If windowed Then
                    ForceWindowed()
                Else
                    Throw New Exception()
                End If
            End Try
        Else
            device.Dispose()
            device = Nothing
            InitializeEnvironment()
        End If

        ' When moving from fullscreen to windowed mode, it is important to
        ' adjust the window size after resetting the device rather than
        ' beforehand to ensure that you get the window size you want.  For
        ' example, when switching from 640x480 fullscreen to windowed with
        ' a 1000x600 window on a 1024x768 desktop, it is impossible to set
        ' the window size to 1000x600 until after the display mode has
        ' changed to 1024x768, because windows cannot be larger than the
        ' desktop.

        If windowed Then
            isChangingFormStyle = True
            ' if our render target is the main window and we haven't said 
            ' ignore the menus, add our menu
            If ourRenderTarget Is Me And isUsingMenus Then
                Me.Menu = mnuMain
            End If
            Me.FormBorderStyle = Windows.Forms.FormBorderStyle.Sizable
            isChangingFormStyle = False
            ' We were maximized, restore that state
            If isMaximized Then
                Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
            End If
            Me.SendToBack()
            Me.BringToFront()
            Me.ClientSize = storedSize
            Me.Location = storedLocation
        Else
            isChangingFormStyle = True
            If Not (Me.Menu Is Nothing) Then
                Me.Menu = Nothing
            End If
            Me.FormBorderStyle = Windows.Forms.FormBorderStyle.None
            isChangingFormStyle = False
        End If
        isHandlingSizeChanges = True
        ready = True
    End Sub 'ToggleFullscreen





    '/ <summary>
    '/ Switch to a windowed mode, even if that means picking a new device and/or adapter
    '/ </summary>
    Public Sub ForceWindowed()
        If windowed Then
            Return
        End If
        If Not FindBestWindowedMode(False, False) Then
            Return
        End If
        windowed = True

        ' Now destroy the current 3D device objects, then reinitialize
        ready = False

        ' Release display objects, so a new device can be created
        device.Dispose()
        device = Nothing

        ' Create the new device
        Try
            InitializeEnvironment()
        Catch e As SampleException
            HandleSampleException(e, ApplicationMessage.ApplicationMustExit)
        Catch
            HandleSampleException(New SampleException(), ApplicationMessage.ApplicationMustExit)
        End Try
        ready = True
    End Sub 'ForceWindowed





    '/ <summary>
    '/ Called when our sample has nothing else to do, and it's time to render
    '/ </summary>
    Private Sub FullRender()
        ' Render a frame during idle time (no messages are waiting)
        If active And ready Then
            Try
                If deviceLost Or (Not (System.Windows.Forms.Form.ActiveForm Is Me)) Then
                    ' Yield some CPU time to other processes
                    System.Threading.Thread.Sleep(100) ' 100 milliseconds
                End If
                ' Render a frame during idle time
                If active Then
                    Render3DEnvironment()
                End If
            Catch ee As Exception
                System.Windows.Forms.MessageBox.Show("An exception has occurred.  This sample must exit." + ControlChars.Cr + ControlChars.Lf + ControlChars.Cr + ControlChars.Lf + ee.ToString(), "Exception", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Information)
                Me.Close()
            End Try
        End If
    End Sub 'FullRender


    '/ <summary>
    '/ Run the simulation
    '/ </summary>
    Public Sub Run()
        ' Now we're ready to recieve and process Windows messages.
        Dim mainWindow As System.Windows.Forms.Control = Me

        ' If the render target is a form and *not* this form, use that form instead,
        ' otherwise, use the main form.
        If (Not (ourRenderTarget Is Me) And (ourRenderTarget.GetType() Is GetType(System.Windows.Forms.Form))) Then
            mainWindow = ourRenderTarget
        End If

        mainWindow.Show()
        While mainWindow.Created
            FullRender()
            System.Windows.Forms.Application.DoEvents()
        End While
    End Sub 'Run





    '/ <summary>
    '/ Draws the scene 
    '/ </summary>
    Public Sub Render3DEnvironment()
        If deviceLost Then
            Try
                ' Test the cooperative level to see if it's okay to render
                device.TestCooperativeLevel()
            Catch e As DeviceLostException
                ' If the device was lost, do not render until we get it back
                isHandlingSizeChanges = False
                isWindowActive = False
                Return
            Catch e As DeviceNotResetException
                ' Check if the device needs to be resized.
                ' If we are windowed, read the desktop mode and use the same format for
                ' the back buffer
                If windowed Then
                    Dim adapterInfo As GraphicsAdapterInfo = graphicsSettings.AdapterInfo
                    graphicsSettings.WindowedDisplayMode = Manager.Adapters(adapterInfo.AdapterOrdinal).CurrentDisplayMode
                    presentParams.BackBufferFormat = graphicsSettings.WindowedDisplayMode.Format
                End If

                ' Reset the device and resize it
                device.Reset(device.PresentationParameters)
                EnvironmentResized(device, New System.ComponentModel.CancelEventArgs())
            End Try
            deviceLost = False
        End If

        ' Get the app's time, in seconds. Skip rendering if no time elapsed
        Dim fAppTime As Single = DXUtil.Timer(DirectXTimer.GetApplicationTime)
        Dim fElapsedAppTime As Single = DXUtil.Timer(DirectXTimer.GetElapsedTime)
        If 0.0F = fElapsedAppTime And frameMoving Then
            Return
        End If
        ' FrameMove (animate) the scene
        If frameMoving Or isSingleStep Then
            ' Store the time for the app
                appTime = fAppTime
                elapsedTime = fElapsedAppTime
            ' Frame move the scene
            FrameMove()

            isSingleStep = False
        End If

        ' Render the scene as normal
        Render()

        UpdateStats()

        Try
            ' Show the frame on the primary surface.
            device.Present()
        Catch e As DeviceLostException
            deviceLost = True
        End Try
    End Sub 'Render3DEnvironment




    '/ <summary>
    '/ Update the various statistics the simulation keeps track of
    '/ </summary>
    Public Sub UpdateStats()
        ' Keep track of the frame count
        Dim time As Single = DXUtil.Timer(DirectXTimer.GetAbsoluteTime)
        frames += 1

        ' Update the scene stats once per second
        If time - lastTime > 1.0F Then
            framePerSecond = frames / (time - lastTime)
            lastTime = time
            frames = 0

            Dim strFmt As String
            Dim fmtAdapter As Format = graphicsSettings.DisplayMode.Format
            If fmtAdapter = device.PresentationParameters.BackBufferFormat Then
                strFmt = fmtAdapter.ToString()
            Else
                strFmt = [String].Format("backbuf {0}, adapter {1}", device.PresentationParameters.BackBufferFormat.ToString(), fmtAdapter.ToString())
            End If

            Dim strDepthFmt As String
            If enumerationSettings.AppUsesDepthBuffer Then
                strDepthFmt = [String].Format(" ({0})", graphicsSettings.DepthStencilBufferFormat.ToString())
            Else
                ' No depth buffer
                strDepthFmt = ""
            End If

            Dim strMultiSample As String
            Select Case graphicsSettings.MultisampleType
                Case Direct3D.MultiSampleType.NonMaskable
                    strMultiSample = " (NonMaskable Multisample)"
                Case Direct3D.MultiSampleType.TwoSamples
                    strMultiSample = " (2x Multisample)"
                Case Direct3D.MultiSampleType.ThreeSamples
                    strMultiSample = " (3x Multisample)"
                Case Direct3D.MultiSampleType.FourSamples
                    strMultiSample = " (4x Multisample)"
                Case Direct3D.MultiSampleType.FiveSamples
                    strMultiSample = " (5x Multisample)"
                Case Direct3D.MultiSampleType.SixSamples
                    strMultiSample = " (6x Multisample)"
                Case Direct3D.MultiSampleType.SevenSamples
                    strMultiSample = " (7x Multisample)"
                Case Direct3D.MultiSampleType.EightSamples
                    strMultiSample = " (8x Multisample)"
                Case Direct3D.MultiSampleType.NineSamples
                    strMultiSample = " (9x Multisample)"
                Case Direct3D.MultiSampleType.TenSamples
                    strMultiSample = " (10x Multisample)"
                Case Direct3D.MultiSampleType.ElevenSamples
                    strMultiSample = " (11x Multisample)"
                Case Direct3D.MultiSampleType.TwelveSamples
                    strMultiSample = " (12x Multisample)"
                Case Direct3D.MultiSampleType.ThirteenSamples
                    strMultiSample = " (13x Multisample)"
                Case Direct3D.MultiSampleType.FourteenSamples
                    strMultiSample = " (14x Multisample)"
                Case Direct3D.MultiSampleType.FifteenSamples
                    strMultiSample = " (15x Multisample)"
                Case Direct3D.MultiSampleType.SixteenSamples
                    strMultiSample = " (16x Multisample)"
                Case Else
                    strMultiSample = String.Empty
            End Select
            frameStats = [String].Format("{0} fps ({1}x{2}), {3}{4}{5}", framePerSecond.ToString("f2"), device.PresentationParameters.BackBufferWidth, device.PresentationParameters.BackBufferHeight, strFmt, strDepthFmt, strMultiSample)
        End If
    End Sub 'UpdateStats




    '/ <summary>
    '/ Called in to toggle the pause state of the app.
    '/ </summary>
    '/ <param name="pause">true if the simulation should pause</param>
    Public Sub PauseSample(ByVal pause As Boolean)

        appPausedCount += CInt(IIf(pause, +1, -1))
        ready = IIf(appPausedCount > 0, False, True)

        ' Handle the first pause request (of many, nestable pause requests)
        If pause And 1 = appPausedCount Then
            ' Stop the scene from animating
            If frameMoving Then
                DXUtil.Timer(DirectXTimer.Stop)
            End If
        End If
        If 0 = appPausedCount Then
            ' Restart the timers
            If frameMoving Then
                DXUtil.Timer(DirectXTimer.Start)
            End If
        End If
    End Sub 'Pause




    '/ <summary>
    '/ Set our variables to not active and not ready
    '/ </summary>
    Public Sub CleanupEnvironment()
        active = False
        ready = False
        If Not (device Is Nothing) Then
            device.Dispose()
        End If
        device = Nothing
    End Sub 'CleanupEnvironment


    '/ <summary>
    '/ Prepares the simulation for a new device being selected
    '/ </summary>
    Public Sub UserSelectNewDevice(ByVal sender As Object, ByVal e As EventArgs) Handles mnuChange.Click
        ' Prompt the user to select a new device or mode
        If active And ready Then
            PauseSample(True)

            DoSelectNewDevice()

            PauseSample(False)
        End If
    End Sub 'UserSelectNewDevice




    '/ <summary>
    '/ Displays a dialog so the user can select a new adapter, device, or
    '/ display mode, and then recreates the 3D environment if needed
    '/ </summary>
    Private Sub DoSelectNewDevice()
        isHandlingSizeChanges = False
        ' Can't display dialogs in fullscreen mode
        If windowed = False Then
            Try
                ToggleFullscreen()
                isHandlingSizeChanges = False
            Catch
                HandleSampleException(New ResetFailedException(), ApplicationMessage.ApplicationMustExit)
                Return
            End Try
        End If

        ' Make sure the main form is in the background
        Me.SendToBack()
        Dim settingsForm As New D3DSettingsForm(enumerationSettings, graphicsSettings)
        Dim result As System.Windows.Forms.DialogResult = settingsForm.ShowDialog(Nothing)
        If result <> System.Windows.Forms.DialogResult.OK Then
            isHandlingSizeChanges = True
            Return
        End If
        graphicsSettings = settingsForm.settings

        windowed = graphicsSettings.IsWindowed

        ' Release display objects, so a new device can be created
        device.Dispose()
        device = Nothing

        ' Inform the display class of the change. It will internally
        ' re-create valid surfaces, a d3ddevice, etc.
        Try
            InitializeEnvironment()
        Catch d3de As SampleException
            HandleSampleException(d3de, ApplicationMessage.ApplicationMustExit)
        Catch
            HandleSampleException(New SampleException(), ApplicationMessage.ApplicationMustExit)
        End Try

        ' If the app is paused, trigger the rendering of the current frame
        If False = frameMoving Then
            isSingleStep = True
            DXUtil.Timer(DirectXTimer.Start)
            DXUtil.Timer(DirectXTimer.Stop)
        End If
        isHandlingSizeChanges = True
    End Sub 'DoSelectNewDevice




    '/ <summary>
    '/ Will start (or stop) simulation
    '/ </summary>
    Private Sub ToggleStart(ByVal sender As Object, ByVal e As EventArgs) Handles mnuGo.Click
        'Toggle frame movement
        frameMoving = Not frameMoving
        DXUtil.Timer(IIf(frameMoving, DirectXTimer.Start, DirectXTimer.Stop))
    End Sub 'ToggleStart




    '/ <summary>
    '/ Will single step the simulation
    '/ </summary>
    Private Sub SingleStep(ByVal sender As Object, ByVal e As EventArgs) Handles mnuSingle.Click
        ' Single-step frame movement
        If False = frameMoving Then
            DXUtil.Timer(DirectXTimer.Advance)
        Else
            DXUtil.Timer(DirectXTimer.Stop)
        End If
        frameMoving = False
        isSingleStep = True
    End Sub 'SingleStep




    '/ <summary>
    '/ Will end the simulation
    '/ </summary>
    Private Sub ExitSample(ByVal sender As Object, ByVal e As EventArgs) Handles mnuExit.Click
        Me.Close()
    End Sub 'ExitSample

    '/ <summary>
    '/ Clean up any resources
    '/ </summary>
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        CleanupEnvironment()
        mnuMain.Dispose()
        MyBase.Dispose(disposing)
    End Sub 'Dispose


    '/ <summary>
    '/ Handle any key presses
    '/ </summary>
    Protected Overrides Sub OnKeyPress(ByVal e As System.Windows.Forms.KeyPressEventArgs)

        If isUsingMenus Then
            ' Check for our shortcut keys (Space)
            If e.KeyChar = " "c Then
                mnuSingle.PerformClick()
                e.Handled = True
            End If

            ' Check for our shortcut keys (Return to start or stop)
            If e.KeyChar = ControlChars.Cr Then
                mnuGo.PerformClick()
                e.Handled = True
            End If
        End If

        ' Check for our shortcut keys (Escape to quit)
        If Asc(e.KeyChar) = CByte(CInt(System.Windows.Forms.Keys.Escape)) Then
            mnuExit.PerformClick()
            e.Handled = True
        End If

        ' Allow the control to handle the keystroke now
        MyBase.OnKeyPress(e)
    End Sub 'OnKeyPress



    '/ <summary>
    '/ Handle system keystrokes (ie, alt-enter)
    '/ </summary>
    Protected Overrides Sub OnKeyDown(ByVal e As System.Windows.Forms.KeyEventArgs)
        If isUsingMenus Then
            If e.Alt And e.KeyCode = System.Windows.Forms.Keys.Return Then
                ' Toggle the fullscreen/window mode
                If active And ready Then
                    PauseSample(True)

                    Try
                        ToggleFullscreen()
                        PauseSample(False)
                        Return
                    Catch
                        HandleSampleException(New ResetFailedException(), ApplicationMessage.ApplicationMustExit)
                    Finally
                        e.Handled = True
                    End Try
                End If
            End If
        End If
        ' Allow the control to handle the keystroke now
        MyBase.OnKeyDown(e)
    End Sub 'OnKeyDown




    '/ <summary>
    '/ Winforms generated code for initializing the form
    '/ </summary>
    Private Sub InitializeComponent()
        ' 
        ' GraphicsSample
        ' 
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.MinimumSize = New System.Drawing.Size(100, 100)
        '
        Me.mnuMain = New System.Windows.Forms.MainMenu()
        Me.mnuFile = New System.Windows.Forms.MenuItem() '

        Me.mnuGo = New System.Windows.Forms.MenuItem()
        Me.mnuSingle = New System.Windows.Forms.MenuItem()
        Me.mnuBreak1 = New System.Windows.Forms.MenuItem()
        Me.mnuChange = New System.Windows.Forms.MenuItem()
        Me.mnuBreak2 = New System.Windows.Forms.MenuItem()
        Me.mnuExit = New System.Windows.Forms.MenuItem()
        ' 
        ' mainMenu1
        ' 
        Me.mnuMain.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuFile})
        ' 
        ' mnuFile
        ' 
        Me.mnuFile.Index = 0
        Me.mnuFile.MenuItems.AddRange(New System.Windows.Forms.MenuItem() {Me.mnuGo, Me.mnuSingle, Me.mnuBreak1, Me.mnuChange, Me.mnuBreak2, Me.mnuExit})
        Me.mnuFile.Text = "&File"
        ' 
        ' mnuGo
        ' 
        Me.mnuGo.Index = 0
        Me.mnuGo.Text = "&Go/stop" + ControlChars.Tab + "Enter"
        ' 
        ' mnuSingle
        ' 
        Me.mnuSingle.Index = 1
        Me.mnuSingle.Text = "&Single step" + ControlChars.Tab + "Space"
        ' 
        ' mnuBreak1
        ' 
        Me.mnuBreak1.Index = 2
        Me.mnuBreak1.Text = "-"
        ' 
        ' mnuChange
        ' 
        Me.mnuChange.Index = 3
        Me.mnuChange.Shortcut = System.Windows.Forms.Shortcut.F2
        Me.mnuChange.ShowShortcut = True
        Me.mnuChange.Text = "&Change Device..."
        ' 
        ' mnuBreak2
        ' 
        Me.mnuBreak2.Index = 4
        Me.mnuBreak2.Text = "-"
        ' 
        ' mnuExit
        ' 
        Me.mnuExit.Index = 5
        Me.mnuExit.Text = "E&xit" + ControlChars.Tab + "ESC"
    End Sub 'InitializeComponent


    '/ <summary>
    '/ When the menu is starting pause our simulation
    '/ </summary>
    Protected Overrides Sub OnMenuStart(ByVal e As System.EventArgs)
        PauseSample(True) ' Pause the simulation while the menu starts
    End Sub 'OnMenuStart



    '/ <summary>
    '/ When the menu is complete our simulation can continue
    '/ </summary>
    Protected Overrides Sub OnMenuComplete(ByVal e As System.EventArgs)
        PauseSample(False) ' Unpause the simulation 
    End Sub 'OnMenuComplete



    '/ <summary>
    '/ Make sure our graphics cursor (if available) moves with the cursor
    '/ </summary>
    Protected Overrides Sub OnMouseMove(ByVal e As System.Windows.Forms.MouseEventArgs)

        If Not (device Is Nothing) Then
            ' Move the D3D cursor
            device.SetCursorPosition(e.X, e.Y, False)
        End If
        ' Let the control handle the mouse now
        MyBase.OnMouseMove(e)
    End Sub 'OnMouseMove



    '/ <summary>
    '/ Handle size changed events
    '/ </summary>
    Protected Overrides Sub OnSizeChanged(ByVal e As System.EventArgs)
        Me.OnResize(e)
        MyBase.OnSizeChanged(e)
    End Sub 'OnSizeChanged




    '/ <summary>
    '/ Handle resize events
    '/ </summary>
    Protected Overrides Sub OnResize(ByVal e As System.EventArgs)
        If isHandlingSizeChanges Then
            ' Are we maximized?
            isMaximized = Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
            If (Not isMaximized) Then
                storedSize = Me.ClientSize
                storedLocation = Me.Location
            End If
        End If
        active = Not (Me.WindowState = System.Windows.Forms.FormWindowState.Minimized Or Me.Visible = False)
        MyBase.OnResize(e)
    End Sub 'OnResize





    '/ <summary>
    '/ Once the form has focus again, we can continue to handle our resize
    '/ and resets..
    '/ </summary>
    Protected Overrides Sub OnGotFocus(ByVal e As System.EventArgs)
        isHandlingSizeChanges = True
        isWindowActive = True
        MyBase.OnGotFocus(e)
    End Sub 'OnGotFocus




    '/ <summary>
    '/ Handle move events
    '/ </summary>
    Protected Overrides Sub OnMove(ByVal e As System.EventArgs)
        If isHandlingSizeChanges Then
            storedLocation = Me.Location
        End If
        MyBase.OnMove(e)
    End Sub 'OnMove




    '/ <summary>
    '/ Handle closing event
    '/ </summary>
    Protected Overrides Sub OnClosing(ByVal e As System.ComponentModel.CancelEventArgs)
        MyBase.OnClosing(e)
    End Sub 'OnClosing
End Class 'GraphicsSample '
