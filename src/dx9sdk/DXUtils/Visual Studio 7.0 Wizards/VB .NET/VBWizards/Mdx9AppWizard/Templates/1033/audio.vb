Imports System
Imports System.Windows.Forms
Imports Microsoft.DirectX.AudioVideoPlayback
Imports Microsoft.DirectX.DirectSound
Imports Buffer = Microsoft.DirectX.DirectSound.Buffer

'/ <summary>
'/ Summary description for audio.
'/ </summary>
Public Class AudioClass
    Private localDevice As Device = Nothing
    Private localBuffer As Buffer = Nothing
    Private audioPlayer As Audio = Nothing


    Public Sub New(ByVal owner As Control)
        Dim desc As New BufferDescription()

        localDevice = New Device()
        localDevice.SetCooperativeLevel(owner, CooperativeLevel.Normal)

        localBuffer = New Buffer(DXUtil.FindMediaFile(Nothing, "drumpad-bass_drum.wav"), desc, localDevice)
        audioPlayer = New Audio(DXUtil.FindMediaFile(Nothing, "DirectX Theme.wma"))
    End Sub 'New


    Public Sub PlaySound()
        localBuffer.Play(0, BufferPlayFlags.Default)
    End Sub 'PlaySound


    Public Sub PlayAudio()
        audioPlayer.Stop()
        audioPlayer.Play()
    End Sub 'PlayAudio
End Class 'AudioClass