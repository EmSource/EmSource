Imports System
Imports System.Drawing
Imports System.Windows.Forms
Imports Microsoft.DirectX
Imports Microsoft.DirectX.Direct3D
Imports Direct3D = Microsoft.DirectX.Direct3D

[!if USE_DIRECTPLAY]
Public Delegate Sub PeerCloseCallback() ' This delegate will be called when the session terminated event is fired.
Public Delegate Sub MessageDelegate(message As Byte) ' Delegate for messages arriving via DirectPlay.
[!endif]
[!if USE_AUDIO]
Public Delegate Sub AudioDelegate() ' Delegate to handle audio playback.
[!endif]

Public Class GraphicsClass
    Inherits GraphicsSample
[!if GRAPHICSTARGET_PICTUREBOX]
    Private target As System.Windows.Forms.PictureBox = nothing
    Private groupBox1 As System.Windows.Forms.GroupBox = nothing
[!endif]
    Private drawingFont As D3DXFont = nothing
    Private destination As Point = New Point(0, 0)
[!if USE_AUDIO]
    Private audio As AudioClass  = nothing
[!endif]
[!if USE_DIRECTINPUT]
    Private input As InputClass = nothing
[!endif]
[!if USE_DIRECTPLAY]

    Private play As PlayClass = nothing

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
[!endif]

    public Sub New()
        Me.Text = "[!output PROJECT_NAME]"
[!if USE_AUDIO]
        audio = New AudioClass(Me)
[!endif]
[!if USE_DIRECTPLAY]
        play = New PlayClass(Me)
[!endif]
[!if USE_DIRECTINPUT && USE_AUDIO]
        input = New InputClass(Me, audio[!if USE_DIRECTPLAY], play[!endif])
[!endif]
[!if USE_DIRECTINPUT && !USE_AUDIO]
        input = New InputClass(Me[!if USE_DIRECTPLAY], play[!endif])
[!endif]
[!if !USE_DIRECTINPUT]
        AddHandler Me.KeyDown, AddressOf Me.OnPrivateKeyDown
        AddHandler Me.KeyUp, AddressOf Me.OnPrivateKeyUp
[!endif]
        drawingFont = New D3DXFont("Arial", System.Drawing.FontStyle.Bold)
[!if GRAPHICSTARGET_PICTUREBOX]

        target = New System.Windows.Forms.PictureBox()
        groupBox1 = New System.Windows.Forms.GroupBox()
        target.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        target.Location = New System.Drawing.Point(155, 20)
        target.Name = "pictureBox1"
        target.Size = New System.Drawing.Size(220, 260)
        target.TabIndex = 0
        target.TabStop = False
        target.Anchor = (AnchorStyles.Top Or AnchorStyles.Bottom Or AnchorStyles.Left Or AnchorStyles.Right)
        groupBox1.Anchor = (AnchorStyles.Top Or AnchorStyles.Bottom Or AnchorStyles.Left)
        groupBox1.Location = New System.Drawing.Point(8, 20)
        groupBox1.Name = "groupBox1"
        groupBox1.Size = New System.Drawing.Size(110, 260)
        groupBox1.TabIndex = 1
        groupBox1.TabStop = False
        groupBox1.Text = "Insert Your UI"

        Me.Controls.AddRange(New System.Windows.Forms.Control[] {Me.groupBox1, Me.target})
        Me.RenderTarget = target
[!endif]
    End Sub

[!if !USE_DIRECTINPUT]
    '/ <summary>
    '/ Event Handler for windows messages
    '/ </summary>
    Private Sub OnPrivateKeyDown(sender As Object, e As KeyEventArgs)

        Select Case (e.KeyCode)
            Case Keys.Up:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgUp)
[!else]
                destination.X = 1
[!endif]
            Case Keys.Down:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgDown)
[!else]
                destination.X = -1
[!endif]
            Case Keys.Left:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgLeft)
[!else]
                destination.Y = 1
[!endif]
            Case Keys.Right:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgRight)
[!else]
                destination.Y = -1
[!endif]
[!if USE_AUDIO]
            Case Keys.W:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgSound)
[!else]
                audio.PlaySound()
[!endif]
            Case Keys.Q:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgAudio)
[!else]
                audio.PlayAudio()
[!endif]
[!endif]
        End Select
    End Sub
    Private Sub OnPrivateKeyUp(sender As Object , e As KeyEventArgs)

        Select Case (e.KeyCode)
                Case Keys.Up:
[!if USE_DIRECTPLAY]
                    play.WriteMessage(msgCancelUp)
[!endif]
                Case Keys.Down:
[!if USE_DIRECTPLAY]
                    play.WriteMessage(msgCancelDown)
[!endif]
[!if !USE_DIRECTPLAY]
                    destination.X = 0
[!endif]
                Case Keys.Left:
[!if USE_DIRECTPLAY]
                    play.WriteMessage(msgCancelLeft)
[!endif]
                Case Keys.Right:
[!if USE_DIRECTPLAY]
                    play.WriteMessage(msgCancelRight)
[!endif]
[!if !USE_DIRECTPLAY]                   
                    destination.Y = 0
[!endif]
        End Select
    End Sub
[!endif]

    '/ <summary>
    '/ Called once per frame, the call is the entry point for 3d rendering. This 
    '/ function sets up render states, clears the viewport, and renders the scene.
    '/ </summary>
    Protected Overrides Sub Render()
[!if USE_DIRECTINPUT && !USE_DIRECTPLAY]
        destination = input.GetInputState()
[!endif]
[!if USE_DIRECTINPUT && USE_DIRECTPLAY]
        input.GetInputState()
[!endif]

        'Clear the backbuffer to a Blue color 
        device.Clear(ClearFlags.Target Or ClearFlags.ZBuffer, Color.Blue, 1.0f, 0)
        'Begin the scene
        device.BeginScene()
[!if !USE_DIRECTINPUT && !USE_DIRECTPLAY]
        drawingFont.DrawText(5, 5, Color.White.ToArgb(), "X: " & destination.X & " Y: " & destination.Y)

[!endif]
[!if USE_DIRECTINPUT && USE_DIRECTPLAY]
        drawingFont.DrawText(5, 5, Color.White.ToArgb(), "X: " & destination.X & " Y: " & destination.Y)

[!endif]
        '
        ' TODO: Insert application rendering code here.
        '
        device.EndScene()
    End Sub

    '/ <summary>
    '/ Initialize scene objects.
    '/ </summary>
    Protected Overrides Sub InitializeDeviceObjects()
        drawingFont.InitializeDeviceObjects(device)

        '
        ' TODO: Insert application device initialization code here.
        '
    End Sub

    '/ <summary>
    '/ Called when a device needs to be restored.
    '/ </summary>
    Protected Overrides Sub RestoreDeviceObjects(sender As System.Object, e As System.EventArgs)
        '
        ' TODO: Insert application device restoration code here.
        '
    End Sub
[!if USE_DIRECTPLAY]

    public Sub MessageArrived(message As byte)

        Select Case (message)
            Case msgUp:
                destination.X = 1
            Case msgDown:
                destination.X = -1
            Case msgLeft:
                destination.Y = 1
            Case msgRight:
                destination.Y = -1
            Case msgCancelUp:
                destination.X = 0
            Case msgCancelDown:
                destination.X = 0
            Case msgCancelLeft:
                destination.Y = 0
            Case msgCancelRight:
                destination.Y = 0
[!if USE_AUDIO]
            Case msgAudio:
                Me.BeginInvoke(New AudioDelegate(AddressOf audio.PlayAudio))
            Case msgSound:
                audio.PlaySound()
[!endif]
        End Select
    End Sub

'/ <summary>
' When the peer closes, the code here is executed.
'/ </summary>
    Public Sub PeerClose()
        ' The session was terminated, go ahead and shut down
        Me.Dispose()
    End Sub
[!endif]

End Class