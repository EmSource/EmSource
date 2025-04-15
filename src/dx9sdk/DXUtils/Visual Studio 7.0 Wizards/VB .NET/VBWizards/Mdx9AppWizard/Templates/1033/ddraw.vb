Imports System
Imports System.Windows.Forms
Imports System.Drawing
Imports Microsoft.DirectX
Imports Microsoft.DirectX.DirectDraw

'/ <summary>
'/ This class is where the Drawing routines
'/ for non-Direct3D and non-DirectDraw 
'/ applications reside.
'/ </summary>
Public Class GraphicsClass
    Private owner As Control = Nothing

[!if !VISUALTYPE_BLANK]
    Private Const spriteSize As Integer= 50
[!endif]
[!if VISUALTYPE_BLANK]
    Private surfaceText As Surface = Nothing
[!endif]
    Private localDevice As Device = Nothing
    Private localClipper As Clipper = Nothing
    Private surfacePrimary As Surface = Nothing
    Private surfaceSecondary As Surface = Nothing

    Public Sub New(ByRef owner As Control)
        Me.owner = owner

        localDevice = New Device()
        localDevice.SetCooperativeLevel(owner, CooperativeLevelFlags.Normal)
        
        CreateSurfaces()
    End Sub

    Private Sub CreateSurfaces()
        Dim desc As SurfaceDescription = New SurfaceDescription()
        Dim caps As SurfaceCaps = New SurfaceCaps() 

        localClipper = New Clipper(localDevice)
        localClipper.Window = owner

        desc.SurfaceCaps.PrimarySurface = true
        surfacePrimary = New Surface(desc, localDevice)
        surfacePrimary.Clipper = localClipper
        
        desc.Clear()
        desc.SurfaceCaps.OffScreenPlain = true
        desc.Width = surfacePrimary.SurfaceDescription.Width
        desc.Height = surfacePrimary.SurfaceDescription.Height
        
        surfaceSecondary = New Surface(desc, localDevice)            
[!if !VISUALTYPE_BLANK]
        surfaceSecondary.FillStyle = 0
[!endif]

[!if VISUALTYPE_BLANK]
        desc.Clear()
        desc.SurfaceCaps.OffScreenPlain = True
        desc.Width = 100
        desc.Height = 50
        surfaceText = New Surface(desc, localDevice)
        surfaceText.ForeColor = Color.Black
[!endif]
    End Sub

[!if !VISUALTYPE_BLANK]
    Public Sub RenderGraphics(ByVal destination As Point)
        If (Not owner.Created) Then
            Return
        End If

        Dim dest As Rectangle = New Rectangle(owner.PointToScreen(New Point(destination.X, destination.Y)), New Size(spriteSize, spriteSize))

        If (Nothing Is surfacePrimary Or Nothing Is surfaceSecondary) Then
            Return
        End If

        Try
            surfaceSecondary.ColorFill(Color.Blue)
            surfaceSecondary.DrawEllipse(dest.Left, dest.Top, dest.Right, dest.Bottom)
            surfacePrimary.Draw(surfaceSecondary, DrawFlags.DoNotWait)
        Catch e As SurfaceLostException
            ' The surface can be lost if power saving
            ' mode kicks in, or any other number of
            ' reasons.
            CreateSurfaces()
        End Try
    End Sub
[!else]
    Public Sub RenderGraphics(ByVal text As String)
        Dim r As New Rectangle(New Point(owner.Left, owner.Top), New Size(surfacePrimary.SurfaceDescription.Width, surfacePrimary.SurfaceDescription.Height))

        If (Not owner.Created) Then
            Return
        End If

        If (Nothing Is surfacePrimary Or Nothing Is surfaceSecondary) Then
            Return
        End If

        Try
            surfaceSecondary.ColorFill(Color.Blue)
            surfaceText.ColorFill(Color.Blue)
            surfaceText.DrawText(0, 0, text, True)
            surfaceSecondary.Draw(New Rectangle(10, 40, 100, 50), surfaceText, DrawFlags.DoNotWait)
            surfacePrimary.Draw(r, surfaceSecondary, DrawFlags.DoNotWait)
        Catch e As SurfaceLostException
            ' The surface can be lost if power saving
            ' mode kicks in, or any other number of
            ' reasons.
            CreateSurfaces()
        End Try
    End Sub
[!endif]
End Class