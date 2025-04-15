Imports System
Imports System.Drawing
Imports System.Windows.Forms
Imports Microsoft.DirectX
Imports Microsoft.DirectX.DirectInput

'/ <summary>
'/ This class is where the DirectInput routines
'/ for the application resides.
'/ </summary>
Public class InputClass

    Private Const msgUp As Byte = 0
    Private Const msgDown As Byte = 1
    Private Const msgLeft As Byte = 2
    Private Const msgRight As Byte = 3
    Private Const msgCancelUp As Byte = 4
    Private Const msgCancelDown As Byte = 5
    Private Const msgCancelLeft As Byte = 6
    Private Const msgCancelRight As Byte = 7
[!if USE_AUDIO]
    Private Const msgAudio As Byte = 8
    Private Const msgSound As Byte = 9
[!endif]

[!if USE_DIRECTPLAY]
    Private pressedUp As Boolean = False
    Private pressedDown As Boolean = False
    Private pressedLeft As Boolean = False
    Private pressedRight As Boolean = False
[!endif]

    Private owner As Control = Nothing
    Private localDevice As Device = Nothing
[!if USE_AUDIO]
    Private audio As AudioClass = Nothing
[!endif]
[!if USE_DIRECTPLAY]
    Private play As PlayClass = Nothing
[!endif]

    Public Sub New(owner As Control [!if USE_AUDIO], audio As AudioClass [!endif][!if USE_DIRECTPLAY], play As PlayClass [!endif])
        Me.owner = owner
[!if USE_AUDIO]
        Me.audio = audio
[!endif]
[!if USE_DIRECTPLAY]
        Me.play = play
[!endif]

        localDevice = new Device(SystemGuid.Keyboard)
        localDevice.SetDataFormat(DeviceDataFormat.Keyboard)
        localDevice.SetCooperativeLevel(owner, CooperativeLevelFlags.Foreground Or CooperativeLevelFlags.NonExclusive)         
    End Sub
    
    Public Function GetInputState() As Point
        Dim state As KeyboardState = Nothing
        Dim p As Point = new Point(0)
        Dim continue as Boolean

        Try
            state = localDevice.GetCurrentKeyboardState()
        Catch e As InputException
            Do
                Continue = False
                Application.DoEvents()
                Try 
                    localDevice.Acquire() 
                Catch e2 As InputLostException
                    continue = True
                Catch e3 As OtherApplicationHasPriorityException
                    continue = True
                End Try
                If Not owner.Created Then Exit Do
            Loop While continue 
        End Try

        if(Nothing Is state) Then
            Return p
        End If

        if(state.Item(Key.Down)) Then
[!if USE_DIRECTPLAY]
            pressedDown = True
            play.WriteMessage(msgDown)
[!else]
[!if GRAPHICSTYPE_DIRECT3D]
            p.X = -1
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
            p.Y = 1
[!endif]
[!endif]
[!if USE_DIRECTPLAY]
        Else If (pressedDown = True) Then
            pressedDown = False
            play.WriteMessage(msgCancelDown)
[!endif]
        End If

        If(state(Key.Up)) Then
[!if USE_DIRECTPLAY]
            pressedUp = True
            play.WriteMessage(msgUp)
[!else]
[!if GRAPHICSTYPE_DIRECT3D]
            p.X = 1
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
            p.Y = -1
[!endif]
[!endif]            
[!if USE_DIRECTPLAY]
        Else If (pressedUp = True) Then
            pressedUp = False
            play.WriteMessage(msgCancelUp)
[!endif]
        End If

        If(state(Key.Left)) Then
[!if USE_DIRECTPLAY]
            pressedLeft = True
            play.WriteMessage(msgLeft)
[!else]
[!if GRAPHICSTYPE_DIRECT3D]
            p.Y = 1
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
            p.X = -1
[!endif]               
[!endif]
[!if USE_DIRECTPLAY]
        Else if (pressedLeft = True)
            pressedLeft = False
            play.WriteMessage(msgCancelLeft)
[!endif]
        End If

        If(state(Key.Right)) Then
[!if USE_DIRECTPLAY]
            pressedRight  = True
            play.WriteMessage(msgRight)
[!else]
[!if GRAPHICSTYPE_DIRECT3D]
            p.Y = -1
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
            p.X = 1
[!endif]                
[!endif]            
[!if USE_DIRECTPLAY]
        Else If (pressedRight = True) Then
            pressedRight = False
            play.WriteMessage(msgCancelRight)
[!endif]
        End If
[!if USE_AUDIO]
        If(state(Key.Q)) Then
[!if USE_DIRECTPLAY]
            play.WriteMessage(msgSound)
[!else]
            audio.PlaySound()
[!endif]
        End If

        If(state(Key.W)) Then
[!if USE_DIRECTPLAY]
            play.WriteMessage(msgAudio)
[!else]
            audio.PlayAudio()
[!endif]
        End If
[!endif]

        Return p
    End Function
End Class