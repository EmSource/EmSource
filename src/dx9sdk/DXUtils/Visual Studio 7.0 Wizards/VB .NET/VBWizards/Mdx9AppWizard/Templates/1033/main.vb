Imports System
Imports System.Drawing
Imports Container = System.ComponentModel.Container
Imports Microsoft.DirectX
[!if !GRAPHICSTYPE_DIRECT3D]
Imports System.Windows.Forms
[!endif]

[!if USE_DIRECTPLAY && !GRAPHICSTYPE_DIRECT3D]
Public Delegate Sub MessageDelegate(message As Byte) ' Delegate for messages arriving via DirectPlay.
Public Delegate Sub AudioDelegate() ' Delegate to handle audio playback.
Public Delegate Sub PeerCloseCallback() ' This Delegate will be called when the session terminated event Is fired.
[!endif]
'/ <summary>
'/ The main windows form for the application.
'/ </summary>
Public class MainClass
[!if !GRAPHICSTYPE_DIRECT3D]
    Inherits System.Windows.Forms.Form
[!endif]
[!if GRAPHICSTYPE_NOGRAPHICS || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]
    Private Const spriteSize As Single = 50
[!endif]
[!if USE_DIRECTINPUT && !GRAPHICSTYPE_DIRECT3D]
    Private input As InputClass = Nothing
[!endif]
[!if GRAPHICSTARGET_PICTUREBOX && !GRAPHICSTYPE_DIRECT3D]
    Private pbTarget As System.Windows.Forms.PictureBox 
    Private groupBox1 As System.Windows.Forms.GroupBox 
[!endif]
[!if USE_AUDIO && !GRAPHICSTYPE_DIRECT3D]
    Public audio As AudioClass = Nothing
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
    Public destination As Point = New Point(10, 10)
[!endif]
    Private graphics As GraphicsClass = Nothing
[!if !GRAPHICSTYPE_DIRECT3D]
    Private components As Container = Nothing
    Private target As Control = Nothing ' Target for rendering operations.
[!endif]
[!if USE_DIRECTPLAY && !GRAPHICSTYPE_DIRECT3D]
    Private play As PlayClass = Nothing

    Private Const msgUp As Byte = 0
    Private Const msgDown As Byte = 1
    Private Const msgLeft As Byte = 2
    Private Const msgRight As Byte = 3
[!if USE_AUDIO]
    Private Const msgAudio As Byte = 8
    Private Const msgSound As Byte = 9
[!endif]
[!endif]

    '/ <summary>
    ' Main entry point of the application.
    '/ </summary>
    Public shared Sub Main()
        Dim m As New MainClass()
[!if !GRAPHICSTYPE_DIRECT3D]
        Application.Exit()
[!endif]
    End Sub

    Public Sub New()
[!if !GRAPHICSTYPE_DIRECT3D]
        '
        ' Required for Windows Form Designer support
        '
        InitializeComponent()
[!endif]
[!if GRAPHICSTARGET_PICTUREBOX && !GRAPHICSTYPE_DIRECT3D]
        target = pbTarget
[!endif]
[!if !GRAPHICSTARGET_PICTUREBOX && !GRAPHICSTYPE_DIRECT3D]
        target = Me
[!endif]
[!if USE_AUDIO && !GRAPHICSTYPE_DIRECT3D]
        audio = New AudioClass(Me)
[!endif]
[!if USE_DIRECTPLAY && !GRAPHICSTYPE_DIRECT3D]
        Try
            play = New PlayClass(Me)
        Catch e As DirectXException
            MessageBox.Show("DirectPlay initialization was incomplete. Application will terminate.")
            Return
        End Try
[!endif]
[!if USE_DIRECTINPUT && !GRAPHICSTYPE_DIRECT3D]
        input = New InputClass(Me[!if USE_AUDIO], audio[!endif][!if USE_DIRECTPLAY], play[!endif])
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
        graphics = New GraphicsClass(target)
        Show()
        StartLoop()
[!else]
        Try
            graphics = New GraphicsClass()
        Catch e As DirectXException
            Return
        End Try
        If graphics.CreateGraphicsSample() Then
            graphics.Run()
        End If
[!endif]
    End Sub
[!if !GRAPHICSTYPE_DIRECT3D]
    '/ <summary>
    '/ Clean up any resources being used.
    '/ </summary>
    Protected Overloads Sub Dispose(disposing as Boolean)
        if( disposing )
            if (Not Nothing Is components) 
                components.Dispose()
            End if
        End if
        MyBase.Dispose( disposing )
    End Sub

    '/ <summary>
    ' This Is the main Loop of the application.
    '/ </summary>
    Private Sub StartLoop()
[!if VISUALTYPE_BLANK]
        Dim text As String = String.Empty
[!endif]
        Do While(Created)
[!if USE_DIRECTINPUT && !USE_DIRECTPLAY]
            Dim p As Point = input.GetInputState()

            destination.X += p.X
            destination.Y += p.Y
[!endif]
[!if USE_DIRECTINPUT && USE_DIRECTPLAY]
            input.GetInputState()
[!endif]                
[!if GRAPHICSTYPE_DIRECTDRAW && VISUALTYPE_BLANK]
            text = "X: " + destination.X.ToString() + " Y: " + destination.Y.ToString()
            graphics.RenderGraphics(text)
[!endif]
[!if GRAPHICSTYPE_NOGRAPHICS || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]
            CheckBounds()
            graphics.RenderGraphics(destination)
[!endif]
            Application.DoEvents()
        Loop
    End Sub
[!endif]
[!if !GRAPHICSTYPE_DIRECT3D]
    #Region "Windows Form Designer generated code"
    '/ <summary>
    '/ Required method for Designer support - do Not modify
    '/ the contents of Me method with the code editor.
    '/ </summary>
    Private Sub InitializeComponent()
        Me.SuspendLayout()
[!if GRAPHICSTARGET_PICTUREBOX]
        Me.pbTarget = New System.Windows.Forms.PictureBox()
        Me.groupBox1 = New System.Windows.Forms.GroupBox()
        
        ' 
        ' pbTarget
        ' 
        Me.pbTarget.Anchor = (((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) 
            Or System.Windows.Forms.AnchorStyles.Left) 
            Or System.Windows.Forms.AnchorStyles.Right)
        Me.pbTarget.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.pbTarget.Location = New System.Drawing.Point(136, 8)
        Me.pbTarget.Name = "pbTarget"
        Me.pbTarget.Size = New System.Drawing.Size(264, 264)
        Me.pbTarget.TabIndex = 0
        Me.pbTarget.TabStop = false
        ' 
        ' groupBox1
        ' 
        Me.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) 
            Or System.Windows.Forms.AnchorStyles.Left)
        Me.groupBox1.Location = New System.Drawing.Point(8, 8)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Size = New System.Drawing.Size(112, 264)
        Me.groupBox1.TabIndex = 1
        Me.groupBox1.TabStop = false
        Me.groupBox1.Text = "Insert Your UI"

        Me.Controls.AddRange(New System.Windows.Forms.Control[] {
                                                                        Me.groupBox1,
                                                                        Me.pbTarget})
[!endif]
        ' 
        ' MainClass
        ' 
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(408, 294)
        Me.KeyPreview = true
        Me.Name = "MainClass"
        Me.Text = "[!output PROJECT_NAME]"
[!if !USE_DIRECTINPUT]
        AddHandler Me.KeyDown, AddressOf Me.MainClass_KeyDown
[!endif]
[!if GRAPHICSTYPE_NOGRAPHICS || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]
        AddHandler Me.Resize, AddressOf Me.Repaint
        AddHandler Me.Activated, AddressOf Me.Repaint
[!endif]
        Me.ResumeLayout(false)
    End Sub
    #End Region
[!endif]
[!if !USE_DIRECTINPUT]

[!if !GRAPHICSTYPE_DIRECT3D]
    '/ <summary>
    ' Handles keyboard events.
    '/ </summary>
    Private Sub MainClass_KeyDown(sender As Object, e As System.Windows.Forms.KeyEventArgs)
        Select Case (e.KeyCode)
            Case Keys.Up:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgUp)
[!else]
                destination.Y = destination.Y - 1
[!endif]
            Case Keys.Down:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgDown)
[!else]
                destination.Y = destination.Y + 1
[!endif]
            Case Keys.Left:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgLeft)
[!else]
                destination.X = destination.X - 1
[!endif]
            Case Keys.Right:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgRight)
[!else]
                destination.X = destination.X + 1
[!endif]
[!if USE_AUDIO]
            Case Keys.Q:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgSound)
[!else]
                audio.PlaySound()
[!endif]
            Case Keys.W:
[!if USE_DIRECTPLAY]
                play.WriteMessage(msgAudio)
[!else]
                audio.PlayAudio()
[!endif]
[!endif]
        End Select
[!if GRAPHICSTYPE_NOGRAPHICS  || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]
        CheckBounds()
        graphics.RenderGraphics(destination)
[!endif]
    End Sub
[!endif]
[!endif]
[!if GRAPHICSTYPE_NOGRAPHICS || GRAPHICSTYPE_DIRECTDRAW && !VISUALTYPE_BLANK]

    '/ <summary>
    ' Checks the boundaries of graphics
    ' objects to ensure they stay in bounds.
    '/ </summary>
    Private Sub CheckBounds()
        if (destination.X < 0)
            destination.X = 0
        End if
        if (destination.X > target.ClientSize.Width - spriteSize)
            destination.X = target.ClientSize.Width  - spriteSize
        End if
        if (destination.Y < 0)
            destination.Y = 0
        End if
        if (destination.Y > target.ClientSize.Height - spriteSize)
            destination.Y = target.ClientSize.Height - spriteSize
        End if
    End Sub

    Private Sub Repaint(sender As Object, e As System.EventArgs)
        if (Not Nothing Is graphics)
            graphics.RenderGraphics(destination)
        End if
    End Sub
[!endif]
[!if USE_DIRECTPLAY && !GRAPHICSTYPE_DIRECT3D]

    Public Sub MessageArrived(byte message)
        Select Case (message)
            Case msgUp:
                destination.Y--
            Case msgDown:
                destination.Y++
            Case msgLeft:
                destination.X--
            Case msgRight:
                destination.X++
[!if USE_AUDIO]
            Case msgAudio:
                audio.PlayAudio()
            Case msgSound:
                Me.BeginInvoke(New AudioDelegate(audio.PlayAudio))
[!endif]
        End Select
    End Sub

    '/ <summary>
    ' When the peer closes, the code here Is executed.
    '/ </summary>
    Public Sub PeerClose()        
        ' The session was terminated, go ahead and shut down
        Me.Dispose()
    End Sub
[!endif]
End class