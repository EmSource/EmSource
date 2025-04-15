'-----------------------------------------------------------------------------
' File: D3DFont.vb
'
' Desc: Shortcut functions for using DX objects
'
' Copyright (c) 2001-2002 Microsoft Corporation. All rights reserved
'-----------------------------------------------------------------------------
Imports System
Imports System.Drawing
Imports Microsoft.DirectX
Imports Microsoft.DirectX.Direct3D
Imports Direct3D = Microsoft.DirectX.Direct3D

 _


Public Class GraphicsFont
    Public Const MaxNumfontVertices As Integer = 50 * 6
    ' Font rendering flags
    <System.Flags()> Public Enum RenderFlags
        Centered = &H1
        TwoSided = &H2
        Filtered = &H4
    End Enum 'RenderFlags
    Private systemFont As System.Drawing.Font

    Private isZEnable As Boolean = False

    Public Property ZBufferEnable() As Boolean
        Get
            Return isZEnable
        End Get
        Set(ByVal Value As Boolean)
            isZEnable = Value
        End Set ' Font properties
    End Property
    Private ourFontName As String
    Private ourFontHeight As Integer

    Private device As Direct3D.Device
    Private textureState0 As TextureState
    Private textureState1 As TextureState
    Private samplerState0 As Sampler
    Private renderState As RenderStates
    Private fontTexture As Direct3D.Texture
    Private vertexBuffer As Direct3D.VertexBuffer
    Private fontVertices(MaxNumfontVertices - 1) As CustomVertex.TransformedColoredTextured

    Private textureWidth As Integer ' Texture dimensions
    Private textureHeight As Integer
    Private textureScale As Single
    Private spacingChar As Integer
    Private textureCoords(128 - 32, 4) As Single

    ' Stateblocks for setting and restoring render states
    Private savedStateBlock As StateBlock
    Private drawTextStateBlock As StateBlock





    '-----------------------------------------------------------------------------
    ' Name: Constructor
    ' Desc: Create a new font object
    '-----------------------------------------------------------------------------
    Public Sub New(ByVal f As System.Drawing.Font)
        ourFontName = f.Name
        ourFontHeight = CType(f.Size, Integer)
        systemFont = f
    End Sub 'New

    Public Sub New(ByVal strFontName As String)
        ourFontName = strFontName
        ourFontHeight = 12
        systemFont = New System.Drawing.Font(ourFontName, ourFontHeight)
    End Sub 'New

    Public Sub New(ByVal strFontName As String, ByVal Style As FontStyle)
        ourFontName = strFontName
        ourFontHeight = 12
        systemFont = New System.Drawing.Font(ourFontName, ourFontHeight, Style)
    End Sub 'New

    Public Sub New(ByVal strFontName As String, ByVal Style As FontStyle, ByVal size As Integer)
        ourFontName = strFontName
        ourFontHeight = size
        systemFont = New System.Drawing.Font(ourFontName, ourFontHeight, Style)
    End Sub 'New




    '-----------------------------------------------------------------------------
    ' Name: PaintAlphabet
    ' Desc: Attempt to draw the systemFont alphabet onto the provided graphics
    '-----------------------------------------------------------------------------
    public Sub PaintAlphabet(ByVal g as Graphics, ByVal measureOnly as Boolean)
        Dim str As String = ""
        Dim x As Single = 0
        Dim y As Single = 0
        Dim p As New PointF(0, 0)
        Dim size As New Size(0, 0)

        ' Calculate the spacing between characters based on line height
        size = g.MeasureString(" ", systemFont).ToSize()
        x = spacingChar = Math.Ceiling(size.Height * 0.3)

        Dim c As Byte
        For c = 32 To 127 - 1
            str = Chr(c).ToString()

            ' We need to do some things here to get the right sizes.  The default implemententation of MeasureString
            ' will return a resolution independant size.  For our height, this is what we want.  However, for our width, we 
            ' want a resolution dependant size.
            Dim resSize As Size = g.MeasureString(str, systemFont).ToSize()
            size.Height = resSize.Height

            ' Now the Resolution independent width
            If Chr(c) <> " " Then ' We need the special case here because a space has a 0 width in GenericTypoGraphic stringformats
                resSize = g.MeasureString(str, systemFont, p, StringFormat.GenericTypographic).ToSize()
                size.Width = resSize.Width
            Else
                size.Width = resSize.Width
            End If
            If x + size.Width + 1 > textureWidth Then
                x = 0
                y += size.Height
            End If

            If y + size.Height > textureHeight Then
                Throw New System.InvalidOperationException("Texture too small for alphabet")
            End If

            If Not measureOnly Then
                If Chr(c) <> " " Then ' We need the special case here because a space has a 0 width in GenericTypoGraphic stringformats
                    g.DrawString(str, systemFont, Brushes.White, New PointF(CInt(x), CInt(y)), StringFormat.GenericTypographic)
                Else
                    g.DrawString(str, systemFont, Brushes.White, New PointF(CInt(x), CInt(y)))
                End If
                textureCoords(c - 32, 0) = CSng(x / textureWidth)
                textureCoords(c - 32, 1) = CSng(y / textureHeight)
                textureCoords(c - 32, 2) = CSng((x + size.Width) / textureWidth)
                textureCoords(c - 32, 3) = CSng((y + size.Height) / textureHeight)
            End If

            x += size.Width + 1
        Next c

    End Sub 'PaintAlphabet




    '-----------------------------------------------------------------------------
    ' Name: InitializeDeviceObjects
    ' Desc: Initialize the device objects
    '-----------------------------------------------------------------------------
    Public Sub InitializeDeviceObjects(ByVal dev As device)
        If Not (dev Is Nothing) Then
            ' Set up our events
            AddHandler dev.DeviceReset, AddressOf Me.RestoreDeviceObjects
        End If

        ' Keep a local copy of the device
        device = dev
        textureState0 = device.TextureState(0)
        textureState1 = device.TextureState(1)
        samplerState0 = device.SamplerState(0)
        renderState = device.RenderState

        ' Create a bitmap on which to measure the alphabet
        Dim bmp As New Bitmap(1, 1, System.Drawing.Imaging.PixelFormat.Format32bppArgb)
        Dim g As Graphics = Graphics.FromImage(bmp)
        g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias
        g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias
        g.TextContrast = 0

        ' Establish the font and texture size
        textureScale = 1.0F ' Draw fonts into texture without scaling

        ' Calculate the dimensions for the smallest power-of-two texture which can
        ' hold all the printable characters
        textureWidth = 128 : textureHeight = 128
        While True
            Try
                ' Measure the alphabet
                PaintAlphabet(g, True)
                Exit While
            Catch ex As System.InvalidOperationException
                ' Scale up the texture size and try again
                textureWidth *= 2
                textureHeight *= 2
            End Try
        End While

        ' If requested texture is too big, use a smaller texture and smaller font,
        ' and scale up when rendering.
        Dim d3dCaps As Direct3D.Caps = device.DeviceCaps

        ' If the needed texture is too large for the video card...
        If textureWidth > d3dCaps.MaxTextureWidth Then
            ' Scale the font size down to fit on the largest possible texture
            textureScale = CSng(d3dCaps.MaxTextureWidth) / CSng(textureWidth)
            textureWidth = d3dCaps.MaxTextureWidth : textureHeight = d3dCaps.MaxTextureWidth

            While True
                ' Create a new, smaller font
                ourFontHeight = Math.Floor(ourFontHeight * textureScale)
                systemFont = New System.Drawing.Font(systemFont.Name, ourFontHeight, systemFont.Style)

                Try
                    ' Measure the alphabet
                    PaintAlphabet(g, True)
                    Exit While
                Catch ex As System.InvalidOperationException
                    ' If that still doesn't fit, scale down again and continue
                    textureScale *= 0.9F
                End Try

            End While
        End If

        ' Release the bitmap used for measuring and create one for drawing
        bmp.Dispose()
        bmp = New Bitmap(textureWidth, textureHeight, System.Drawing.Imaging.PixelFormat.Format32bppArgb)
        g = Graphics.FromImage(bmp)
        g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias
        g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias
        g.TextContrast = 0

        ' Draw the alphabet
        PaintAlphabet(g, False)

        ' Create a new texture for the font from the bitmap we just created
        fontTexture = Texture.FromBitmap(device, bmp, 0, Pool.Managed)
        RestoreDeviceObjects(Nothing, Nothing)
    End Sub 'InitializeDeviceObjects




    Public Overloads Sub DrawText(ByVal sx As Single, ByVal sy As Single, ByVal color As Color, ByVal strText As String)
        DrawText(sx, sy, color, strText, RenderFlags.Filtered)
    End Sub 'DrawText






    '-----------------------------------------------------------------------------
    ' Name: RestoreDeviceObjects
    ' Desc: Restore the font
    '-----------------------------------------------------------------------------
    Public Sub RestoreDeviceObjects(ByVal sender As Object, ByVal e As EventArgs)
        vertexBuffer = New VertexBuffer(GetType(CustomVertex.TransformedColoredTextured), MaxNumfontVertices, device, Usage.WriteOnly Or Usage.Dynamic, 0, Pool.Default)

        Dim surf As Surface = device.GetRenderTarget(0)
        Dim supportsAlphaBlend As Boolean = Manager.CheckDeviceFormat(device.DeviceCaps.AdapterOrdinal, device.DeviceCaps.DeviceType, device.DisplayMode.Format, Usage.RenderTarget Or Usage.QueryPostPixelShaderBlending, ResourceType.Surface, surf.Description.Format)

        ' Create the state blocks for rendering text
        Dim which As Integer
        For which = 0 To 1
            device.BeginStateBlock()
            device.SetTexture(0, fontTexture)

            If isZEnable Then
                renderState.ZBufferEnable = True
            Else
                renderState.ZBufferEnable = False
            End If
            If supportsAlphaBlend Then
                renderState.AlphaBlendEnable = True
                renderState.SourceBlend = Blend.SourceAlpha
                renderState.DestinationBlend = Blend.InvSourceAlpha
            Else
                renderState.AlphaBlendEnable = False
            End If
            renderState.AlphaTestEnable = True
            renderState.ReferenceAlpha = &H8
            renderState.AlphaFunction = Compare.GreaterEqual
            renderState.FillMode = FillMode.Solid
            renderState.CullMode = Cull.CounterClockwise
            renderState.StencilEnable = False
            renderState.Clipping = True
            device.ClipPlanes.DisableAll()
            renderState.VertexBlend = VertexBlend.Disable
            renderState.IndexedVertexBlendEnable = False
            renderState.FogEnable = False
            renderState.ColorWriteEnable = ColorWriteEnable.RedGreenBlueAlpha
            textureState0.ColorOperation = TextureOperation.Modulate
            textureState0.ColorArgument1 = TextureArgument.TextureColor
            textureState0.ColorArgument2 = TextureArgument.Diffuse
            textureState0.AlphaOperation = TextureOperation.Modulate
            textureState0.AlphaArgument1 = TextureArgument.TextureColor
            textureState0.AlphaArgument2 = TextureArgument.Diffuse
            textureState0.TextureCoordinateIndex = 0
            textureState0.TextureTransform = TextureTransform.Disable ' REVIEW
            textureState1.ColorOperation = TextureOperation.Disable
            textureState1.AlphaOperation = TextureOperation.Disable
            samplerState0.MinFilter = TextureFilter.Point
            samplerState0.MagFilter = TextureFilter.Point
            samplerState0.MipFilter = TextureFilter.None

            If which = 0 Then
                savedStateBlock = device.EndStateBlock()
            Else
                drawTextStateBlock = device.EndStateBlock()
            End If
        Next which
    End Sub 'RestoreDeviceObjects


    '-----------------------------------------------------------------------------
    ' Name: DrawText
    ' Desc: Draw some text on the screen
    '-----------------------------------------------------------------------------
    Public Overloads Sub DrawText(ByVal sx As Single, ByVal sy As Single, ByVal color As Color, ByVal strText As String, ByVal flags As RenderFlags)
        If strText Is Nothing Then
            Return
        End If
        ' Setup renderstate
        savedStateBlock.Capture()
        drawTextStateBlock.Apply()
        device.SetTexture(0, fontTexture)
        device.VertexFormat = CustomVertex.TransformedColoredTextured.Format
        device.PixelShader = Nothing
        device.SetStreamSource(0, vertexBuffer, 0)

        ' Set filter states
        If (flags And RenderFlags.Filtered) <> 0 Then
            samplerState0.MinFilter = TextureFilter.Linear
            samplerState0.MagFilter = TextureFilter.Linear
        End If

        Dim fStartX As Single = sx

        ' Fill vertex buffer
        Dim iv As Integer
        Dim dwNumTriangles As Integer = 0

        Dim c As Char
        For Each c In strText
            If c = ControlChars.Lf Then
                sx = fStartX
                sy += (textureCoords(0, 3) - textureCoords(0, 1)) * textureHeight
            End If

            If Asc(c) - 32 < 0 Or Asc(c) - 32 >= 128 - 32 Then
                GoTo ContinueForEach1
            End If
            Dim tx1 As Single = textureCoords(Asc(c) - 32, 0)
            Dim ty1 As Single = textureCoords(Asc(c) - 32, 1)
            Dim tx2 As Single = textureCoords(Asc(c) - 32, 2)
            Dim ty2 As Single = textureCoords(Asc(c) - 32, 3)

            Dim w As Single = (tx2 - tx1) * textureWidth / textureScale
            Dim h As Single = (ty2 - ty1) * textureHeight / textureScale

            Dim intColor As Integer = color.ToArgb()
            If c <> " "c Then
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + 0 - 0.5F, sy + h - 0.5F, 0.9F, 1.0F), intColor, tx1, ty2) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + 0 - 0.5F, sy + 0 - 0.5F, 0.9F, 1.0F), intColor, tx1, ty1) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + w - 0.5F, sy + h - 0.5F, 0.9F, 1.0F), intColor, tx2, ty2) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + w - 0.5F, sy + 0 - 0.5F, 0.9F, 1.0F), intColor, tx2, ty1) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + w - 0.5F, sy + h - 0.5F, 0.9F, 1.0F), intColor, tx2, ty2) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + 0 - 0.5F, sy + 0 - 0.5F, 0.9F, 1.0F), intColor, tx1, ty1) : iv += 1
                dwNumTriangles += 2

                If dwNumTriangles * 3 > MaxNumfontVertices - 6 Then
                    ' Set the data for the vertexbuffer
                    vertexBuffer.SetData(fontVertices, 0, LockFlags.Discard)
                    device.DrawPrimitives(PrimitiveType.TriangleList, 0, dwNumTriangles)
                    dwNumTriangles = 0
                    iv = 0
                End If
            End If

            sx += w
ContinueForEach1:
        Next c

        ' Set the data for the vertex buffer
        vertexBuffer.SetData(fontVertices, 0, LockFlags.Discard)
        If dwNumTriangles > 0 Then
            device.DrawPrimitives(PrimitiveType.TriangleList, 0, dwNumTriangles)
        End If
        ' Restore the modified renderstates
        savedStateBlock.Apply()
    End Sub 'DrawText





    '-----------------------------------------------------------------------------
    ' Name: DrawTextScaled()
    ' Desc: Draws scaled 2D text.  Note that x and y are in viewport coordinates
    '       (ranging from -1 to +1).  fXScale and fYScale are the size fraction 
    '       relative to the entire viewport.  For example, a fXScale of 0.25 is
    '       1/8th of the screen width.  This allows you to output text at a fixed
    '       fraction of the viewport, even if the screen or window size changes.
    '-----------------------------------------------------------------------------
    Public Overloads Sub DrawTextScaled(ByVal x As Single, ByVal y As Single, ByVal z As Single, ByVal fXScale As Single, ByVal fYScale As Single, ByVal color As System.Drawing.Color, ByVal [text] As String, ByVal flags As RenderFlags)
        If device Is Nothing Then
            Throw New System.ArgumentNullException()
        End If
        ' Set up renderstate
        savedStateBlock.Capture()
        drawTextStateBlock.Apply()
        device.VertexFormat = CustomVertex.TransformedColoredTextured.Format
        device.PixelShader = Nothing
        device.SetStreamSource(0, vertexBuffer, 0)

        ' Set filter states
        If (flags And RenderFlags.Filtered) <> 0 Then
            samplerState0.MinFilter = TextureFilter.Linear
            samplerState0.MagFilter = TextureFilter.Linear
        End If

        Dim vp As Viewport = device.Viewport
        Dim sx As Single = (x + 1.0F) * vp.Width / 2
        Dim sy As Single = (y + 1.0F) * vp.Height / 2
        Dim sz As Single = z
        Dim rhw As Single = 1.0F
        Dim fLineHeight As Single = (textureCoords(0, 3) - textureCoords(0, 1)) * textureHeight

        ' Adjust for character spacing
        sx -= spacingChar * (fXScale * vp.Height) / fLineHeight
        Dim fStartX As Single = sx

        ' Fill vertex buffer
        Dim numTriangles As Integer = 0
        Dim realColor As Integer = color.ToArgb()
        Dim iv As Integer = 0

        Dim c As Char
        For Each c In [text]
            If c = ControlChars.Lf Then
                sx = fStartX
                sy += fYScale * vp.Height
            End If

            If Asc(c) - 32 < 0 Or Asc(c) - 32 >= 128 - 32 Then
                GoTo ContinueForEach1
            End If
            Dim tx1 As Single = textureCoords(Asc(c) - 32, 0)
            Dim ty1 As Single = textureCoords(Asc(c) - 32, 1)
            Dim tx2 As Single = textureCoords(Asc(c) - 32, 2)
            Dim ty2 As Single = textureCoords(Asc(c) - 32, 3)

            Dim w As Single = (tx2 - tx1) * textureWidth
            Dim h As Single = (ty2 - ty1) * textureHeight

            w *= fXScale * vp.Height / fLineHeight
            h *= fYScale * vp.Height / fLineHeight

            If c <> " "c Then
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + 0 - 0.5F, sy + h - 0.5F, sz, rhw), realColor, tx1, ty2) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + 0 - 0.5F, sy + 0 - 0.5F, sz, rhw), realColor, tx1, ty1) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + w - 0.5F, sy + h - 0.5F, sz, rhw), realColor, tx2, ty2) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + w - 0.5F, sy + 0 - 0.5F, sz, rhw), realColor, tx2, ty1) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + w - 0.5F, sy + h - 0.5F, sz, rhw), realColor, tx2, ty2) : iv += 1
                fontVertices(iv) = New CustomVertex.TransformedColoredTextured(New Vector4(sx + 0 - 0.5F, sy + 0 - 0.5F, sz, rhw), realColor, tx1, ty1) : iv += 1
                numTriangles += 2

                If numTriangles * 3 > MaxNumfontVertices - 6 Then
                    ' Unlock, render, and relock the vertex buffer
                    vertexBuffer.SetData(fontVertices, 0, LockFlags.Discard)
                    device.DrawPrimitives(PrimitiveType.TriangleList, 0, numTriangles)
                    numTriangles = 0
                    iv = 0
                End If
            End If

            sx += w - 2 * spacingChar * (fXScale * vp.Height) / fLineHeight
ContinueForEach1:
        Next c

        ' Unlock and render the vertex buffer
        vertexBuffer.SetData(fontVertices, 0, LockFlags.Discard)
        If numTriangles > 0 Then
            device.DrawPrimitives(PrimitiveType.TriangleList, 0, numTriangles)
        End If
        ' Restore the modified renderstates
        savedStateBlock.Apply()
    End Sub 'DrawTextScaled

    Public Overloads Sub DrawTextScaled(ByVal x As Single, ByVal y As Single, ByVal z As Single, ByVal fXScale As Single, ByVal fYScale As Single, ByVal color As System.Drawing.Color, ByVal [text] As String)
        Me.DrawTextScaled(x, y, z, fXScale, fYScale, color, [text], 0)
    End Sub 'DrawTextScaled






    '-----------------------------------------------------------------------------
    ' Name: Render3DText()
    ' Desc: Renders 3D text
    '-----------------------------------------------------------------------------
    Public Sub Render3DText(ByVal [text] As String, ByVal flags As RenderFlags)
        If device Is Nothing Then
            Throw New System.ArgumentNullException()
        End If
        ' Set up renderstate
        savedStateBlock.Capture()
        drawTextStateBlock.Apply()
        device.VertexFormat = CustomVertex.PositionNormalTextured.Format
        device.PixelShader = Nothing
        device.SetStreamSource(0, vertexBuffer, 0, VertexInformation.GetFormatSize(CustomVertex.PositionNormalTextured.Format))

        ' Set filter states
        If (flags And RenderFlags.Filtered) <> 0 Then
            samplerState0.MinFilter = TextureFilter.Linear
            samplerState0.MagFilter = TextureFilter.Linear
        End If

        ' Position for each text element
        Dim x As Single = 0.0F
        Dim y As Single = 0.0F

        ' Center the text block at the origin
        If (flags And RenderFlags.Centered) <> 0 Then
            Dim sz As System.Drawing.SizeF = GetTextExtent([text])
            x = -(CSng(sz.Width) / 10.0F) / 2.0F
            y = -(CSng(sz.Height) / 10.0F) / 2.0F
        End If

        ' Turn off culling for two-sided text
        If (flags And RenderFlags.TwoSided) <> 0 Then
            renderState.CullMode = Cull.None
        End If
        ' Adjust for character spacing
        x -= spacingChar / 10.0F
        Dim fStartX As Single = x

        ' Fill vertex buffer
        Dim strm As GraphicsStream = vertexBuffer.Lock(0, 0, LockFlags.Discard)
        Dim numTriangles As Integer = 0

        Dim c As Char
        For Each c In [text]
            If c = ControlChars.Lf Then
                x = fStartX
                y -= (textureCoords(0, 3) - textureCoords(0, 1)) * textureHeight / 10.0F
            End If

            If Asc(c) - 32 < 0 Or Asc(c) - 32 >= 128 - 32 Then
                GoTo ContinueForEach1
            End If
            Dim tx1 As Single = textureCoords(Asc(c) - 32, 0)
            Dim ty1 As Single = textureCoords(Asc(c) - 32, 1)
            Dim tx2 As Single = textureCoords(Asc(c) - 32, 2)
            Dim ty2 As Single = textureCoords(Asc(c) - 32, 3)

            Dim w As Single = (tx2 - tx1) * textureWidth / (10.0F * textureScale)
            Dim h As Single = (ty2 - ty1) * textureHeight / (10.0F * textureScale)

            If c <> " "c Then
                strm.Write(New CustomVertex.PositionNormalTextured(New Vector3(x + 0, y + 0, 0), New Vector3(0, 0, -1), tx1, ty2))
                strm.Write(New CustomVertex.PositionNormalTextured(New Vector3(x + 0, y + h, 0), New Vector3(0, 0, -1), tx1, ty1))
                strm.Write(New CustomVertex.PositionNormalTextured(New Vector3(x + w, y + 0, 0), New Vector3(0, 0, -1), tx2, ty2))
                strm.Write(New CustomVertex.PositionNormalTextured(New Vector3(x + w, y + h, 0), New Vector3(0, 0, -1), tx2, ty1))
                strm.Write(New CustomVertex.PositionNormalTextured(New Vector3(x + w, y + 0, 0), New Vector3(0, 0, -1), tx2, ty2))
                strm.Write(New CustomVertex.PositionNormalTextured(New Vector3(x + 0, y + h, 0), New Vector3(0, 0, -1), tx1, ty1))
                numTriangles += 2

                If numTriangles * 3 > MaxNumfontVertices - 6 Then
                    ' Unlock, render, and relock the vertex buffer
                    vertexBuffer.Unlock()
                    device.DrawPrimitives(PrimitiveType.TriangleList, 0, numTriangles)
                    strm = vertexBuffer.Lock(0, 0, LockFlags.Discard)
                    numTriangles = 0
                End If
            End If

            x += w - 2 * spacingChar / 10.0F
ContinueForEach1:
        Next c

        ' Unlock and render the vertex buffer
        vertexBuffer.Unlock()
        If numTriangles > 0 Then
            device.DrawPrimitives(PrimitiveType.TriangleList, 0, numTriangles)
        End If
        ' Restore the modified renderstates
        savedStateBlock.Apply()
    End Sub 'Render3DText





    '-----------------------------------------------------------------------------
    ' Name: GetTextExtent()
    ' Desc: Get the dimensions of a text string
    '-----------------------------------------------------------------------------
    Private Function GetTextExtent(ByVal [text] As String) As System.Drawing.SizeF
        If Nothing = [text] Or [text] = String.Empty Then
            Throw New System.ArgumentNullException()
        End If
        Dim fRowWidth As Single = 0.0F
        Dim fRowHeight As Single = (textureCoords(0, 3) - textureCoords(0, 1)) * textureHeight
        Dim fWidth As Single = 0.0F
        Dim fHeight As Single = fRowHeight

        Dim c As Char
        For Each c In [text]
            If c = ControlChars.Lf Then
                fRowWidth = 0.0F
                fHeight += fRowHeight
            End If

            If Asc(c) - 32 < 0 Or Asc(c) - 32 >= 128 - 32 Then
                GoTo ContinueForEach1
            End If
            Dim tx1 As Single = textureCoords(Asc(c) - 32, 0)
            Dim tx2 As Single = textureCoords(Asc(c) - 32, 2)

            fRowWidth += (tx2 - tx1) * textureWidth - 2 * spacingChar

            If fRowWidth > fWidth Then
                fWidth = fRowWidth
            End If
ContinueForEach1:
        Next c
        Return New System.Drawing.SizeF(fWidth, fHeight)
    End Function 'GetTextExtent



    '-----------------------------------------------------------------------------
    ' Name: Dispose
    ' Desc: Cleanup any resources being used
    '-----------------------------------------------------------------------------
    Public Sub Dispose(ByVal sender As Object, ByVal e As EventArgs)
        If Not (systemFont Is Nothing) Then
            systemFont.Dispose()
        End If
        systemFont = Nothing
    End Sub 'Dispose 
End Class 'GraphicsFont