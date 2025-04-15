'-----------------------------------------------------------------------------
' File: D3DUtil.vb
'
' Desc: Shortcut functions for using DX objects
'
' Copyright (c) 2001-2002 Microsoft Corporation. All rights reserved
'-----------------------------------------------------------------------------
Imports System
Imports System.Windows.Forms
Imports System.Drawing
Imports Microsoft.DirectX
Imports Microsoft.DirectX.Direct3D
Imports Direct3D = Microsoft.DirectX.Direct3D

 _

Public Class GraphicsUtility

    Private Sub New() ' Private Constructor 
    End Sub 'New



    '-----------------------------------------------------------------------------
    ' Name: GraphicsUtility.InitMaterial()
    ' Desc: Initializes a Material structure, setting the diffuse and ambient
    '       colors. It does not set emissive or specular colors.
    '-----------------------------------------------------------------------------
    Public Shared Function InitMaterial(ByVal c As System.Drawing.Color) As Direct3D.Material
        Dim mtrl As New Material()
        mtrl.Ambient = c : mtrl.Diffuse = c
        Return mtrl
    End Function 'InitMaterial




    '-----------------------------------------------------------------------------
    ' Name: GraphicsUtility.InitLight()
    ' Desc: Initializes a LightType structure, setting the light position. The
    '       diffuse color is set to white; specular and ambient are left as black.
    '-----------------------------------------------------------------------------
    Public Shared Sub InitLight(ByVal l As Light, ByVal ltType As LightType, ByVal x As Single, ByVal y As Single, ByVal z As Single)
        l.Type = ltType
        l.Diffuse = System.Drawing.Color.White
        l.Position = New Vector3(x, y, z)
        l.Direction = Vector3.Normalize(l.Position)
        l.Range = 1000.0F
    End Sub 'InitLight




    '-----------------------------------------------------------------------------
    ' Name: GraphicsUtility.CreateTexture()
    ' Desc: Helper function to create a texture. It checks the root path first,
    '       then tries the DXSDK media path (as specified in the system registry).
    '-----------------------------------------------------------------------------
    Public Overloads Shared Function CreateTexture(ByVal d3dDevice As Device, ByVal sTexture As String, ByVal d3dFormat As Format) As Texture
        ' Get the path to the texture
        Dim sPath As String = DXUtil.FindMediaFile(Nothing, sTexture)

        ' Create the texture using D3DX
        Return TextureLoader.FromFile(d3dDevice, sPath, D3DX.Default, D3DX.Default, D3DX.Default, 0, d3dFormat, Pool.Managed, Filter.Triangle Or Filter.Mirror, Filter.Triangle Or Filter.Mirror, 0)
    End Function 'CreateTexture

    Public Overloads Shared Function CreateTexture(ByVal d3dDevice As Device, ByVal sTexture As String) As Texture
        Return GraphicsUtility.CreateTexture(d3dDevice, sTexture, Format.Unknown)
    End Function 'CreateTexture






    '-----------------------------------------------------------------------------
    ' Name: GraphicsUtility.GetCubeMapViewMatrix()
    ' Desc: Returns a view matrix for rendering to a face of a cubemap.
    '-----------------------------------------------------------------------------
    Public Shared Function GetCubeMapViewMatrix(ByVal uiFace As CubeMapFace) As Matrix
        Dim vEyePt As New Vector3(0.0F, 0.0F, 0.0F)
        Dim vLookDir As New Vector3()
        Dim vUpDir As New Vector3()

        Select Case uiFace
            Case CubeMapFace.PositiveX
                vLookDir = New Vector3(1.0F, 0.0F, 0.0F)
                vUpDir = New Vector3(0.0F, 1.0F, 0.0F)
            Case CubeMapFace.NegativeX
                vLookDir = New Vector3(-1.0F, 0.0F, 0.0F)
                vUpDir = New Vector3(0.0F, 1.0F, 0.0F)
            Case CubeMapFace.PositiveY
                vLookDir = New Vector3(0.0F, 1.0F, 0.0F)
                vUpDir = New Vector3(0.0F, 0.0F, -1.0F)
            Case CubeMapFace.NegativeY
                vLookDir = New Vector3(0.0F, -1.0F, 0.0F)
                vUpDir = New Vector3(0.0F, 0.0F, 1.0F)
            Case CubeMapFace.PositiveZ
                vLookDir = New Vector3(0.0F, 0.0F, 1.0F)
                vUpDir = New Vector3(0.0F, 1.0F, 0.0F)
            Case CubeMapFace.NegativeZ
                vLookDir = New Vector3(0.0F, 0.0F, -1.0F)
                vUpDir = New Vector3(0.0F, 1.0F, 0.0F)
        End Select

        ' Set the view transform for this cubemap surface
        Dim matView As Matrix = Matrix.LookAtLH(vEyePt, vLookDir, vUpDir)
        Return matView
    End Function 'GetCubeMapViewMatrix





    '-----------------------------------------------------------------------------
    ' Name: GraphicsUtility.GetRotationFromCursor()
    ' Desc: Returns a quaternion for the rotation implied by the window's cursor
    '       position.
    '-----------------------------------------------------------------------------
    Public Overloads Shared Function GetRotationFromCursor(ByVal control As System.Windows.Forms.Form, ByVal fTrackBallRadius As Single) As Quaternion
        Dim pt As System.Drawing.Point = System.Windows.Forms.Cursor.Position
        Dim rc As System.Drawing.Rectangle = control.ClientRectangle
        pt = control.PointToClient(pt)
        Dim sx As Single = 2.0F * pt.X / (rc.Right - rc.Left) - 1
        Dim sy As Single = 2.0F * pt.Y / (rc.Bottom - rc.Top) - 1
        Dim sz As Single

        If sx = 0.0F And sy = 0.0F Then
            Return New Quaternion(0.0F, 0.0F, 0.0F, 1.0F)
        End If
        Dim d2 As Single = CSng(Math.Sqrt((sx * sx + sy * sy)))

        If d2 < fTrackBallRadius * 0.707106781186548 Then ' Inside sphere
            sz = CSng(Math.Sqrt((fTrackBallRadius * fTrackBallRadius - d2 * d2)))
            ' On hyperbola
        Else
            sz = fTrackBallRadius * fTrackBallRadius / (2.0F * d2)
        End If
        ' Get two points on trackball's sphere
        Dim p1 As New Vector3(sx, sy, sz)
        Dim p2 As New Vector3(0.0F, 0.0F, fTrackBallRadius)

        ' Get axis of rotation, which is cross product of p1 and p2
        Dim vAxis As Vector3 = Vector3.Cross(p1, p2)

        ' Calculate angle for the rotation about that axis
        Dim t As Single = Vector3.Length(Vector3.Subtract(p2, p1)) / (2.0F * fTrackBallRadius)
        If t > +1.0F Then
            t = +1.0F
        End If
        If t < -1.0F Then
            t = -1.0F
        End If
        Dim fAngle As Single = CSng(2.0F * Math.Asin(t))

        ' Convert axis to quaternion
        Return Quaternion.RotationAxis(vAxis, fAngle)
    End Function 'GetRotationFromCursor





    '-----------------------------------------------------------------------------
    ' Name: GraphicsUtility.GetRotationFromCursor()
    ' Desc: Returns a quaternion for the rotation implied by the window's cursor
    '       position.
    '-----------------------------------------------------------------------------
    Public Overloads Shared Function GetRotationFromCursor(ByVal control As System.Windows.Forms.Form) As Quaternion
        Return GetRotationFromCursor(control, 1.0F)
    End Function 'GetRotationFromCursor





    '-----------------------------------------------------------------------------
    ' Name: D3DXQuaternionUnitAxisToUnitAxis2
    ' Desc: Axis to axis quaternion double angle (no normalization)
    '       Takes two points on unit sphere an angle THETA apart, returns
    '       quaternion that represents a rotation around cross product by 2*THETA.
    '-----------------------------------------------------------------------------
    Public Shared Function D3DXQuaternionUnitAxisToUnitAxis2(ByVal vFrom As Vector3, ByVal vTo As Vector3) As Quaternion
        Dim vAxis As Vector3 = Vector3.Cross(vFrom, vTo) ' proportional to sin(theta)
        Return New Quaternion(vAxis.X, vAxis.Y, vAxis.Z, Vector3.Dot(vFrom, vTo))
    End Function 'D3DXQuaternionUnitAxisToUnitAxis2





    '-----------------------------------------------------------------------------
    ' Name: D3DXQuaternionAxisToAxis
    ' Desc: Axis to axis quaternion 
    '       Takes two points on unit sphere an angle THETA apart, returns
    '       quaternion that represents a rotation around cross product by theta.
    '-----------------------------------------------------------------------------
    Public Shared Function D3DXQuaternionAxisToAxis(ByVal vFrom As Vector3, ByVal vTo As Vector3) As Quaternion
        Dim vA As Vector3 = Vector3.Normalize(vFrom)
        Dim vB As Vector3 = Vector3.Normalize(vTo)
        Dim vHalf As Vector3 = Vector3.Add(vA, vB)
        vHalf = Vector3.Normalize(vHalf)
        Return GraphicsUtility.D3DXQuaternionUnitAxisToUnitAxis2(vA, vHalf)
    End Function 'D3DXQuaternionAxisToAxis


    Public Shared Function ColorChannelBits(ByVal fmt As Format) As Integer
        Select Case fmt
            Case Format.R8G8B8
                Return 8
            Case Format.A8R8G8B8
                Return 8
            Case Format.X8R8G8B8
                Return 8
            Case Format.R5G6B5
                Return 5
            Case Format.X1R5G5B5
                Return 5
            Case Format.A1R5G5B5
                Return 5
            Case Format.A4R4G4B4
                Return 4
            Case Format.R3G3B2
                Return 2
            Case Format.A8R3G3B2
                Return 2
            Case Format.X4R4G4B4
                Return 4
            Case Format.A2B10G10R10
                Return 10
            Case Format.A2R10G10B10
                Return 10
            Case Else
                Return 0
        End Select
    End Function 'ColorChannelBits


    Public Shared Function AlphaChannelBits(ByVal fmt As Format) As Integer
        Select Case fmt
            Case Format.R8G8B8
                Return 0
            Case Format.A8R8G8B8
                Return 8
            Case Format.X8R8G8B8
                Return 0
            Case Format.R5G6B5
                Return 0
            Case Format.X1R5G5B5
                Return 0
            Case Format.A1R5G5B5
                Return 1
            Case Format.A4R4G4B4
                Return 4
            Case Format.R3G3B2
                Return 0
            Case Format.A8R3G3B2
                Return 8
            Case Format.X4R4G4B4
                Return 0
            Case Format.A2B10G10R10
                Return 2
            Case Format.A2R10G10B10
                Return 2
            Case Else
                Return 0
        End Select
    End Function 'AlphaChannelBits


    Public Shared Function DepthBits(ByVal fmt As DepthFormat) As Integer
        Select Case fmt
            Case DepthFormat.D16
                Return 16
            Case DepthFormat.D15S1
                Return 15
            Case DepthFormat.D24X8
                Return 24
            Case DepthFormat.D24S8
                Return 24
            Case DepthFormat.D24X4S4
                Return 24
            Case DepthFormat.D32
                Return 32
            Case Else
                Return 0
        End Select
    End Function 'DepthBits


    Public Shared Function StencilBits(ByVal fmt As DepthFormat) As Integer
        Select Case fmt
            Case DepthFormat.D16
                Return 0
            Case DepthFormat.D15S1
                Return 1
            Case DepthFormat.D24X8
                Return 0
            Case DepthFormat.D24S8
                Return 8
            Case DepthFormat.D24X4S4
                Return 4
            Case DepthFormat.D32
                Return 0
            Case Else
                Return 0
        End Select
    End Function 'StencilBits





    '-----------------------------------------------------------------------------
    ' Name: GraphicsUtility.CreateVertexShader()
    ' Desc: Assembles and creates a file-based vertex shader
    '-----------------------------------------------------------------------------
    Public Shared Function CreateVertexShader(ByVal pd3dDevice As Device, ByVal strFilename As String) As VertexShader
        Dim code As GraphicsStream = Nothing
        Dim path As String = Nothing

        ' Get the path to the vertex shader file
        path = DXUtil.FindMediaFile(Nothing, strFilename)

        ' Assemble the vertex shader file
        code = ShaderLoader.FromFile(path, Nothing, 0)

        ' Create the vertex shader
        Return New VertexShader(pd3dDevice, code)
    End Function 'CreateVertexShader
End Class 'GraphicsUtility
 _
Public Class GraphicsArcBall
    Private internalWidth As Integer ' ArcBall's window width
    Private internalHeight As Integer ' ArcBall's window height
    Private internalradius As Single ' ArcBall's radius in screen coords
    Private internalradiusTranslation As Single ' ArcBall's radius for translating the target
    Private internaldownQuat As Quaternion ' Quaternion before button down
    Private internalnowQuat As Quaternion ' Composite quaternion for current drag
    Private internalrotationMatrix As Matrix ' Matrix for arcball's orientation
    Private internalrotationDelta As Matrix ' Matrix for arcball's orientation
    Private internaltranslationMatrix As Matrix ' Matrix for arcball's position
    Private internaltranslationDelta As Matrix ' Matrix for arcball's position
    Private internaldragging As Boolean ' Whether user is dragging arcball
    Private internaluseRightHanded As Boolean ' Whether to use RH coordinate system
    Private saveMouseX As Integer = 0 ' Saved mouse position
    Private saveMouseY As Integer = 0
    Private internalvectorDown As Vector3 ' Button down vector
    Private parent As System.Windows.Forms.Control
    ' parent
    '-----------------------------------------------------------------------------
    ' Name: Constructor
    ' Desc: Initialize variables
    '-----------------------------------------------------------------------------
    Public Sub New(ByVal p As System.Windows.Forms.Control)
        internaldownQuat = Quaternion.Identity
        internalnowQuat = Quaternion.Identity
        internalrotationMatrix = Matrix.Identity
        internalrotationDelta = Matrix.Identity
        internaltranslationMatrix = Matrix.Identity
        internaltranslationDelta = Matrix.Identity
        internaldragging = False
        internalradiusTranslation = 1.0F
        internaluseRightHanded = False

        parent = p
        ' Hook the events 
        AddHandler p.MouseDown, AddressOf Me.OnContainerMouseDown
        AddHandler p.MouseUp, AddressOf Me.OnContainerMouseUp
        AddHandler p.MouseMove, AddressOf Me.OnContainerMouseMove
    End Sub 'New





    '-----------------------------------------------------------------------------
    ' Name: SetWindow
    ' Desc: Set the window dimensions
    '-----------------------------------------------------------------------------
    Public Sub SetWindow(ByVal iWidth As Integer, ByVal iHeight As Integer, ByVal fRadius As Single)
        ' Set ArcBall info
        internalWidth = iWidth
        internalHeight = iHeight
        internalradius = fRadius
    End Sub 'SetWindow





    '-----------------------------------------------------------------------------
    ' Name: ScreenToVector
    ' Desc: Screen coords to a vector
    '-----------------------------------------------------------------------------
    Private Function ScreenToVector(ByVal sx As Integer, ByVal sy As Integer) As Vector3
        ' Scale to screen
        Dim x As Single = -(sx - internalWidth / 2) / (internalradius * internalWidth / 2)
        Dim y As Single = (sy - internalHeight / 2) / (internalradius * internalHeight / 2)

        If internaluseRightHanded Then
            x = -x
            y = -y
        End If

        Dim z As Single = 0.0F
        Dim mag As Single = x * x + y * y

        If mag > 1.0F Then
            Dim scale As Single = 1.0F / CSng(Math.Sqrt(mag))
            x *= scale
            y *= scale
        Else
            z = CSng(Math.Sqrt((1.0F - mag)))
        End If
        ' Return vector
        Return New Vector3(x, y, z)
    End Function 'ScreenToVector




    Private Sub OnContainerMouseDown(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs)
        ' Store off the position of the cursor when the button is pressed
        saveMouseX = e.X
        saveMouseY = e.Y

        If e.Button = System.Windows.Forms.MouseButtons.Left Then
            ' Start drag mode
            internaldragging = True
            internalvectorDown = ScreenToVector(e.X, e.Y)
            internaldownQuat = internalnowQuat
        End If
    End Sub 'OnContainerMouseDown

    Private Sub OnContainerMouseUp(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs)
        If e.Button = System.Windows.Forms.MouseButtons.Left Then
            ' End drag mode
            internaldragging = False
        End If
    End Sub 'OnContainerMouseUp

    Private Sub OnContainerMouseMove(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs)
        If e.Button = System.Windows.Forms.MouseButtons.Left Then
            If internaldragging Then
                ' recompute nowQuat
                Dim vCur As Vector3 = ScreenToVector(e.X, e.Y)
                Dim qAxisToAxis As Quaternion = GraphicsUtility.D3DXQuaternionAxisToAxis(internalvectorDown, vCur)
                internalnowQuat = internaldownQuat
                internalnowQuat = Quaternion.Multiply(internalnowQuat, qAxisToAxis)
                internalrotationDelta = Matrix.RotationQuaternion(qAxisToAxis)
            Else
                internalrotationDelta = Matrix.Identity
            End If
            internalrotationMatrix = Matrix.RotationQuaternion(internalnowQuat)
            internaldragging = True
        End If

        If e.Button = System.Windows.Forms.MouseButtons.Right Or e.Button = System.Windows.Forms.MouseButtons.Middle Then
            ' Normalize based on size of window and bounding sphere radius
            Dim fDeltaX As Single = (saveMouseX - e.X) * internalradiusTranslation / internalWidth
            Dim fDeltaY As Single = (saveMouseY - e.Y) * internalradiusTranslation / internalHeight

            If e.Button = System.Windows.Forms.MouseButtons.Right Then
                internaltranslationDelta = Matrix.Translation(-2 * fDeltaX, 2 * fDeltaY, 0.0F)
                internaltranslationMatrix = Matrix.Multiply(internaltranslationMatrix, internaltranslationDelta)
            End If
            If e.Button = System.Windows.Forms.MouseButtons.Middle Then
                internaltranslationDelta = Matrix.Translation(0.0F, 0.0F, 5 * fDeltaY)
                internaltranslationMatrix = Matrix.Multiply(internaltranslationMatrix, internaltranslationDelta)
            End If

            ' Store mouse coordinate
            saveMouseX = e.X
            saveMouseY = e.Y
        End If
    End Sub 'OnContainerMouseMove

    WriteOnly Property Radius() As Single
        Set(ByVal Value As Single)
            internalradiusTranslation = Value
        End Set
    End Property

    Public Property RightHanded() As Boolean
        Get
            Return internaluseRightHanded
        End Get
        Set(ByVal Value As Boolean)
            internaluseRightHanded = Value
        End Set
    End Property

    Public ReadOnly Property RotationMatrix() As Matrix
        Get
            Return internalrotationMatrix
        End Get
    End Property

    Public ReadOnly Property RotationDeltaMatrix() As Matrix
        Get
            Return internalrotationDelta
        End Get
    End Property

    Public ReadOnly Property TranslationMatrix() As Matrix
        Get
            Return internaltranslationMatrix
        End Get
    End Property

    Public ReadOnly Property TranslationDeltaMatrix() As Matrix
        Get
            Return internaltranslationDelta
        End Get
    End Property

    Public ReadOnly Property IsBeingDragged() As Boolean
        Get
            Return internaldragging
        End Get
    End Property '
End Class 'GraphicsArcBall
Public Class GraphicsCamera '
    Private eyePart As Vector3 ' Attributes for view matrix
    Private lookAtPart As Vector3
    Private upVector As Vector3

    Private viewVector As Vector3
    Private crossVector As Vector3

    Private internalviewMatrix As Matrix
    Private internalbillboardMatrix As Matrix ' Special matrix for billboarding effects
    Private fieldOfView As Single ' Attributes for projection matrix
    Private aspectRatio As Single
    Private nearPlane As Single
    Private farPlane As Single
    Private projectionMatrix As Matrix


    Public Sub New()
        ' Set attributes for the view matrix
        SetViewParams(New Vector3(0.0F, 0.0F, 0.0F), New Vector3(0.0F, 0.0F, 1.0F), New Vector3(0.0F, 1.0F, 0.0F))

        ' Set attributes for the projection matrix
        SetProjParams(CSng(Math.PI) / 4, 1.0F, 1.0F, 1000.0F)
    End Sub 'New

    ReadOnly Property EyePt() As Vector3
        Get
            Return eyePart
        End Get
    End Property

    Public ReadOnly Property LookatPt() As Vector3
        Get
            Return lookAtPart
        End Get
    End Property

    Public ReadOnly Property UpVec() As Vector3
        Get
            Return upVector
        End Get
    End Property

    Public ReadOnly Property ViewDir() As Vector3
        Get
            Return viewVector
        End Get
    End Property

    Public ReadOnly Property Cross() As Vector3
        Get
            Return crossVector
        End Get
    End Property

    Public ReadOnly Property ViewMatrix() As Matrix
        Get
            Return internalviewMatrix
        End Get
    End Property

    Public ReadOnly Property BillboardMatrix() As Matrix
        Get
            Return internalbillboardMatrix
        End Get
    End Property

    Public ReadOnly Property ProjMatrix() As Matrix
        Get
            Return projectionMatrix
        End Get
    End Property


    '-----------------------------------------------------------------------------
    ' Name: SetViewParams
    ' Desc: Set the viewing parameters
    '-----------------------------------------------------------------------------
    Public Sub SetViewParams(ByVal vEyePt As Vector3, ByVal vLookatPt As Vector3, ByVal vUpVec As Vector3)
        ' Set attributes for the view matrix
        eyePart = vEyePt
        lookAtPart = vLookatPt
        upVector = vUpVec
        viewVector = Vector3.Normalize(Vector3.Subtract(lookAtPart, eyePart))
        crossVector = Vector3.Cross(viewVector, upVector)

        internalviewMatrix = Matrix.LookAtLH(eyePart, lookAtPart, upVector)
        internalbillboardMatrix = Matrix.Invert(ViewMatrix)
        internalbillboardMatrix.M41 = 0.0F
        internalbillboardMatrix.M42 = 0.0F
        internalbillboardMatrix.M43 = 0.0F
    End Sub 'SetViewParams





    '-----------------------------------------------------------------------------
    ' Name: SetProjParams
    ' Desc: Set the project parameters
    '-----------------------------------------------------------------------------
    Public Sub SetProjParams(ByVal fFOV As Single, ByVal fAspect As Single, ByVal fNearPlane As Single, ByVal fFarPlane As Single)
        ' Set attributes for the projection matrix
        fieldOfView = fFOV
        aspectRatio = fAspect
        nearPlane = fNearPlane
        farPlane = fFarPlane

        projectionMatrix = Matrix.PerspectiveFovLH(fFOV, fAspect, fNearPlane, fFarPlane)
    End Sub 'SetProjParams
End Class 'GraphicsCamera
Public Class GraphicsMesh
    Implements IDisposable
    Private fileName As String = Nothing
    Private systemMemoryMesh As Mesh = Nothing ' SysMem mesh, lives through resize
    Private localMemoryMesh As Mesh = Nothing ' Local mesh, rebuilt on resize
    Private materials As Direct3D.Material() = Nothing
    Private textures As Texture() = Nothing
    Private useMaterials As Boolean = True
    Private systemMemoryVertexBuffer As VertexBuffer = Nothing
    Private localMemoryVertexBuffer As VertexBuffer = Nothing
    Private systemMemoryIndexBuffer As IndexBuffer = Nothing
    Private localMemoryIndexBuffer As IndexBuffer = Nothing






    '-----------------------------------------------------------------------------
    ' Name: Constructor
    ' Desc: Initialize the string variable
    '-----------------------------------------------------------------------------
    Public Sub New(ByVal strName As String)
        fileName = strName
    End Sub 'New

    Public Sub New()
        fileName = "CD3DFile_Mesh"
    End Sub 'New

    ' Mesh access

    Public ReadOnly Property SysMemMesh() As Mesh
        Get
            Return systemMemoryMesh
        End Get
    End Property

    Public ReadOnly Property LocalMesh() As Mesh
        Get
            Return localMemoryMesh
        End Get
    End Property ' Rendering options

    Public WriteOnly Property UseMeshMaterials() As Boolean
        Set(ByVal Value As Boolean)
            useMaterials = Value
        End Set
    End Property




    '-----------------------------------------------------------------------------
    ' Name: Create
    ' Desc: Creates a new Mesh object
    '-----------------------------------------------------------------------------
    Public Sub Create(ByVal pd3dDevice As Device, ByVal strFilename As String)
        Dim strPath As String = Nothing
        Dim adjacencyBuffer As GraphicsStream
        Dim Mat() As ExtendedMaterial

        If Not (pd3dDevice Is Nothing) Then
            AddHandler pd3dDevice.DeviceLost, AddressOf Me.InvalidateDeviceObjects
            AddHandler pd3dDevice.Disposing, AddressOf Me.InvalidateDeviceObjects
            AddHandler pd3dDevice.DeviceReset, AddressOf Me.RestoreDeviceObjects
        End If

        ' Find the path for the file, and convert it to ANSI (for the D3DX API)
        strPath = DXUtil.FindMediaFile(Nothing, strFilename)

        ' Load the mesh
        systemMemoryMesh = Mesh.FromFile(strPath, MeshFlags.SystemMemory, pd3dDevice, adjacencyBuffer, Mat)

        ' Optimize the mesh for performance
        systemMemoryMesh.OptimizeInPlace(MeshFlags.OptimizeCompact Or MeshFlags.OptimizeAttrSort Or MeshFlags.OptimizeVertexCache, adjacencyBuffer)

        textures = New Texture(Mat.Length) {}
        materials = New Direct3D.Material(Mat.Length) {}

        Dim i As Integer
        For i = 0 To Mat.Length - 1
            materials(i) = Mat(i).Material3D
            ' Set the ambient color for the material (D3DX does not do this)
            materials(i).Ambient = materials(i).Diffuse

            If Not (Mat(i).TextureFilename Is Nothing) Then
                ' Create the texture
                Dim sFile As String = DXUtil.FindMediaFile(Nothing, Mat(i).TextureFilename)
                textures(i) = TextureLoader.FromFile(pd3dDevice, sFile)
            End If
        Next i

        adjacencyBuffer.Close()
        adjacencyBuffer = Nothing
    End Sub 'Create






    '-----------------------------------------------------------------------------
    ' Name: SetFVF
    ' Desc: Set the flexible vertex format
    '-----------------------------------------------------------------------------
    Public Sub SetFVF(ByVal pd3dDevice As Device, ByVal format As VertexFormats)
        Dim pTempSysMemMesh As Mesh = Nothing
        Dim pTempLocalMesh As Mesh = Nothing

        If Not (systemMemoryMesh Is Nothing) Then
            pTempSysMemMesh = systemMemoryMesh.Clone(MeshFlags.SystemMemory, format, pd3dDevice)
        End If
        If Not (localMemoryMesh Is Nothing) Then
            Try
                pTempLocalMesh = localMemoryMesh.Clone(0, format, pd3dDevice)
            Catch e As Exception
                pTempSysMemMesh.Dispose()
                pTempSysMemMesh = Nothing
                Throw e
            End Try
        End If

        If Not (systemMemoryMesh Is Nothing) Then
            systemMemoryMesh.Dispose()
        End If
        systemMemoryMesh = Nothing

        If Not (localMemoryMesh Is Nothing) Then
            localMemoryMesh.Dispose()
        End If
        localMemoryMesh = Nothing

        ' Clean up any vertex/index buffers
        DisposeLocalBuffers(True, True)

        If Not (pTempSysMemMesh Is Nothing) Then
            systemMemoryMesh = pTempSysMemMesh
        End If
        If Not (pTempLocalMesh Is Nothing) Then
            localMemoryMesh = pTempLocalMesh
        End If
        ' Compute normals in case the meshes have them
        If Not (systemMemoryMesh Is Nothing) Then
            systemMemoryMesh.ComputeNormals()
        End If
        If Not (localMemoryMesh Is Nothing) Then
            localMemoryMesh.ComputeNormals()
        End If
    End Sub 'SetFVF




    '-----------------------------------------------------------------------------
    ' Name: RestoreDeviceObjects
    ' Desc: Restore the device objects
    '-----------------------------------------------------------------------------
    Public Sub RestoreDeviceObjects(ByVal sender As Object, ByVal e As EventArgs)
        If Nothing Is systemMemoryMesh Then
            Throw New ArgumentException()
        End If
        Dim pd3dDevice As Device = CType(sender, Device)
        ' Make a local memory version of the mesh. Note: because we are passing in
        ' no flags, the default behavior is to clone into local memory.
        localMemoryMesh = systemMemoryMesh.Clone(0, systemMemoryMesh.VertexFormat, pd3dDevice)
        ' Clean up any vertex/index buffers
        DisposeLocalBuffers(False, True)
    End Sub 'RestoreDeviceObjects



    '-----------------------------------------------------------------------------
    ' Name: InvalidateDeviceObjects
    ' Desc: Invalidate our local mesh
    '-----------------------------------------------------------------------------
    Public Sub InvalidateDeviceObjects(ByVal sender As Object, ByVal e As EventArgs)
        If Not (localMemoryMesh Is Nothing) Then
            localMemoryMesh.Dispose()
        End If
        localMemoryMesh = Nothing
        ' Clean up any vertex/index buffers
        DisposeLocalBuffers(False, True)
    End Sub 'InvalidateDeviceObjects



    '-----------------------------------------------------------------------------
    ' Name: SystemVertexBuffer
    ' Desc: Get the vertex buffer assigned to the system mesh
    '-----------------------------------------------------------------------------

    Public ReadOnly Property SystemVertexBuffer() As VertexBuffer
        Get
            If Not (systemMemoryVertexBuffer Is Nothing) Then
                Return systemMemoryVertexBuffer
            End If
            If systemMemoryMesh Is Nothing Then
                Return Nothing
            End If
            systemMemoryVertexBuffer = systemMemoryMesh.VertexBuffer
            Return systemMemoryVertexBuffer
        End Get
    End Property



    '-----------------------------------------------------------------------------
    ' Name: LocalVertexBuffer
    ' Desc: Get the vertex buffer assigned to the Local mesh
    '-----------------------------------------------------------------------------

    Public ReadOnly Property LocalVertexBuffer() As VertexBuffer
        Get
            If Not (localMemoryVertexBuffer Is Nothing) Then
                Return localMemoryVertexBuffer
            End If
            If localMemoryMesh Is Nothing Then
                Return Nothing
            End If
            localMemoryVertexBuffer = localMemoryMesh.VertexBuffer
            Return localMemoryVertexBuffer
        End Get
    End Property



    '-----------------------------------------------------------------------------
    ' Name: SystemIndexBuffer
    ' Desc: Get the Index buffer assigned to the system mesh
    '-----------------------------------------------------------------------------

    Public ReadOnly Property SystemIndexBuffer() As IndexBuffer
        Get
            If Not (systemMemoryIndexBuffer Is Nothing) Then
                Return systemMemoryIndexBuffer
            End If
            If systemMemoryMesh Is Nothing Then
                Return Nothing
            End If
            systemMemoryIndexBuffer = systemMemoryMesh.IndexBuffer
            Return systemMemoryIndexBuffer
        End Get
    End Property



    '-----------------------------------------------------------------------------
    ' Name: LocalIndexBuffer
    ' Desc: Get the Index buffer assigned to the Local mesh
    '-----------------------------------------------------------------------------

    Public ReadOnly Property LocalIndexBuffer() As IndexBuffer
        Get
            If Not (localMemoryIndexBuffer Is Nothing) Then
                Return localMemoryIndexBuffer
            End If
            If localMemoryMesh Is Nothing Then
                Return Nothing
            End If
            localMemoryIndexBuffer = localMemoryMesh.IndexBuffer
            Return localMemoryIndexBuffer
        End Get
    End Property



    '-----------------------------------------------------------------------------
    ' Name: Dispose
    ' Desc: Clean up any resources
    '-----------------------------------------------------------------------------
    Public Sub Dispose() Implements IDisposable.Dispose
        If Not (textures Is Nothing) Then
            Dim i As Integer
            For i = 0 To textures.Length - 1
                If Not (textures(i) Is Nothing) Then
                    textures(i).Dispose()
                End If
                textures(i) = Nothing
            Next i
            textures = Nothing
        End If

        ' Clean up any vertex/index buffers
        DisposeLocalBuffers(True, True)

        ' Clean up any memory
        If Not (systemMemoryMesh Is Nothing) Then
            systemMemoryMesh.Dispose()
        End If
        systemMemoryMesh = Nothing

        ' In case the finalizer hasn't been called yet.
        GC.SuppressFinalize(Me)
    End Sub 'Dispose





    '-----------------------------------------------------------------------------
    ' Name: Render
    ' Desc: Actually draw the mesh
    '-----------------------------------------------------------------------------
    Public Overloads Sub Render(ByVal pd3dDevice As Device, ByVal bDrawOpaqueSubsets As Boolean, ByVal bDrawAlphaSubsets As Boolean)
        If Nothing Is localMemoryMesh Then
            Throw New ArgumentException()
        End If
        Dim rs As RenderStates = pd3dDevice.RenderState
        ' Frist, draw the subsets without alpha
        If bDrawOpaqueSubsets Then
            Dim i As Integer
            For i = 0 To materials.Length - 1
                If useMaterials Then
                    If bDrawAlphaSubsets Then
                        If materials(i).Diffuse.A < &HFF Then
                            GoTo ContinueFor1
                        End If
                    End If
                    pd3dDevice.Material = materials(i)
                    pd3dDevice.SetTexture(0, textures(i))
                End If
                localMemoryMesh.DrawSubset(i)
ContinueFor1:
            Next i
        End If

        ' Then, draw the subsets with alpha
        If bDrawAlphaSubsets And useMaterials Then
            ' Enable alpha blending
            rs.AlphaBlendEnable = True
            rs.SourceBlend = Blend.SourceAlpha
            rs.DestinationBlend = Blend.InvSourceAlpha
            Dim i As Integer
            For i = 0 To materials.Length - 1
                If materials(i).Diffuse.A = &HFF Then
                    GoTo ContinueFor2
                End If
                ' Set the material and texture
                pd3dDevice.Material = materials(i)
                pd3dDevice.SetTexture(0, textures(i))
                localMemoryMesh.DrawSubset(i)
ContinueFor2:
            Next i
            ' Restore state
            rs.AlphaBlendEnable = False
        End If
    End Sub 'Render

    Public Overloads Sub Render(ByVal pd3dDevice As Device)
        Render(pd3dDevice, True, True)
    End Sub 'Render




    '-----------------------------------------------------------------------------
    ' Name: DisposeLocalBuffers
    ' Desc: Cleans up the local vertex buffers/index buffers
    '-----------------------------------------------------------------------------
    Private Sub DisposeLocalBuffers(ByVal bSysBuffers As Boolean, ByVal bLocalBuffers As Boolean)
        If bSysBuffers Then
            If Not (systemMemoryIndexBuffer Is Nothing) Then
                systemMemoryIndexBuffer.Dispose()
            End If
            systemMemoryIndexBuffer = Nothing

            If Not (systemMemoryVertexBuffer Is Nothing) Then
                systemMemoryVertexBuffer.Dispose()
            End If
            systemMemoryVertexBuffer = Nothing
        End If
        If bLocalBuffers Then
            If Not (localMemoryIndexBuffer Is Nothing) Then
                localMemoryIndexBuffer.Dispose()
            End If
            localMemoryIndexBuffer = Nothing

            If Not (localMemoryVertexBuffer Is Nothing) Then
                localMemoryVertexBuffer.Dispose()
            End If
            localMemoryVertexBuffer = Nothing
        End If
    End Sub 'DisposeLocalBuffers
End Class 'GraphicsMesh
    _
Public Class D3DXFont
    Implements IDisposable
    Protected systemFont As System.Drawing.Font
    Private drawingFont As Direct3D.Font = Nothing





    '-----------------------------------------------------------------------------
    ' Name: Constructor
    ' Desc: Create a new font object
    '-----------------------------------------------------------------------------
    Public Sub New(ByVal f As System.Drawing.Font)
        systemFont = f
    End Sub 'New

    Public Sub New(ByVal strFontName As String)
        systemFont = New System.Drawing.Font(strFontName, 12)
    End Sub 'New

    Public Sub New(ByVal strFontName As String, ByVal Style As FontStyle)
        systemFont = New System.Drawing.Font(strFontName, 12, Style)
    End Sub 'New

    Public Sub New(ByVal strFontName As String, ByVal Style As FontStyle, ByVal size As Integer)
        systemFont = New System.Drawing.Font(strFontName, size, Style)
    End Sub 'New





    '-----------------------------------------------------------------------------
    ' Name: InitializeDeviceObjects
    ' Desc: Initialize the device objects
    '-----------------------------------------------------------------------------
    Public Sub InitializeDeviceObjects(ByVal dev As Device)
        drawingFont = New Direct3D.Font(dev, systemFont)
    End Sub 'InitializeDeviceObjects




    '-----------------------------------------------------------------------------
    ' Name: BeginText
    ' Desc: Call Begin on our font object
    '-----------------------------------------------------------------------------
    Public Sub BeginText()
        If drawingFont Is Nothing Then
            Return
        End If
        drawingFont.Begin()
    End Sub 'BeginText



    '-----------------------------------------------------------------------------
    ' Name: DrawText
    ' Desc: Draw some text on the screen
    '-----------------------------------------------------------------------------
    Public Sub DrawText(ByVal x As Integer, ByVal y As Integer, ByVal color As Integer, ByVal strText As String)
        If drawingFont Is Nothing Then
            Return
        End If
        Dim rcText As New System.Drawing.Rectangle(x, y, 0, 0)
        ' Start drawing the text
        drawingFont.DrawText(strText, rcText, 0, color)
    End Sub 'DrawText




    '-----------------------------------------------------------------------------
    ' Name: EndText
    ' Desc: Call End on our font object
    '-----------------------------------------------------------------------------
    Public Sub EndText()
        If drawingFont Is Nothing Then
            Return
        End If
        drawingFont.End()
    End Sub 'EndText







    '-----------------------------------------------------------------------------
    ' Name: Dispose
    ' Desc: Cleanup any resources being used
    '-----------------------------------------------------------------------------
    Public Sub Dispose() Implements IDisposable.Dispose
        If Not (systemFont Is Nothing) Then
            systemFont.Dispose()
        End If
        systemFont = Nothing
    End Sub 'Dispose
End Class 'D3DXFont
