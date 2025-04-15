Imports System
Imports System.Windows.Forms
Imports System.Drawing

'/ <summary>
'/ This class is where the Drawing routines
'/ for non-Direct3D and non-DirectDraw 
'/ applications reside.
'/ </summary>
Public Class GraphicsClass
    Private spriteSize As Single = 50
    Private owner As Control = Nothing
    Private graphicsWindow As Graphics = Nothing


    Public Sub New(ByVal owner As Control)
        Me.owner = owner
    End Sub 'New


    Public Sub RenderGraphics(ByVal destination As Point)
        If Not owner.Created Then
            Return
        End If
        graphicsWindow = owner.CreateGraphics()
        graphicsWindow.Clear(Color.Blue)
        graphicsWindow.FillEllipse(Brushes.Black, destination.X, destination.Y, spriteSize, spriteSize)
    End Sub 'RenderGraphics
End Class 'GraphicsClass
