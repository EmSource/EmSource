'-----------------------------------------------------------------------------
' File: DXUtil.vb
'
' Desc: Shortcut macros and functions for using DX objects
'
' Copyright (c) 2001-2002 Microsoft Corporation. All rights reserved
'-----------------------------------------------------------------------------
Imports System
Imports System.IO
Imports System.Runtime.InteropServices

 _
Public Enum DirectXTimer
    Reset
    Start
    [Stop]
    Advance
    GetAbsoluteTime
    GetApplicationTime
    GetElapsedTime
End Enum 'DirectXTimer
 _

Public Class DXUtil

    ' We won't use this maliciously
    <System.Security.SuppressUnmanagedCodeSecurity()> Private Declare Function QueryPerformanceFrequency Lib "kernel32" (ByRef PerformanceFrequency As Long) As Boolean
    ' We won't use this maliciously
    <System.Security.SuppressUnmanagedCodeSecurity()> Private Declare Function QueryPerformanceCounter Lib "kernel32" (ByRef PerformanceCount As Long) As Boolean
    ' We won't use this maliciously
    <System.Security.SuppressUnmanagedCodeSecurity()> Public Declare Function timeGetTime Lib "winmm.dll" () As Integer
        Private Shared isTimerInitialized As Boolean = False
        Private Shared m_bUsingQPF As Boolean = False
        Private Shared m_bTimerStopped As Boolean = True
        Private Shared m_llQPFTicksPerSec As Long = 0
        Private Shared m_llStopTime As Long = 0
        Private Shared m_llLastElapsedTime As Long = 0
        Private Shared m_llBaseTime As Long = 0
        Private Shared m_fLastElapsedTime As Double = 0.0
        Private Shared m_fBaseTime As Double = 0.0
        Private Shared m_fStopTime As Double = 0.0

    ' Constants for SDK Path registry keys
    Private Const sdkPath As String = "Software\Microsoft\DirectX SDK"
    Private Const sdkKey As String = "DX9SDK Samples Path"


    Private Sub New() ' Private Constructor 
    End Sub 'New 


    '-----------------------------------------------------------------------------
    ' Name: DXUtil.SdkMediaPath
    ' Desc: Returns the DirectX SDK media path
    '-----------------------------------------------------------------------------

    Public Shared ReadOnly Property SdkMediaPath() As String
        Get
            Dim rKey As Microsoft.Win32.RegistryKey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(sdkPath)
            Dim sReg As String = String.Empty
            If Not (rKey Is Nothing) Then
                sReg = CStr(rKey.GetValue(sdkKey))
                rKey.Close()
            End If
            If Not (sReg Is Nothing) Then
                sReg += "\Media\"
            Else
                Return String.Empty
            End If

            Return sReg
        End Get
    End Property




    '-----------------------------------------------------------------------------
    ' Name: DXUtil.Timer()
    ' Desc: Performs timer opertations. Use the following commands:
    '          DirectXTimer.Reset           - to reset the timer
    '          DirectXTimer.Start           - to start the timer
    '          DirectXTimer.Stop            - to stop (or pause) the timer
    '          DirectXTimer.Advance         - to advance the timer by 0.1 seconds
    '          DirectXTimer.GetAbsoluteTime - to get the absolute system time
    '          DirectXTimer.GetApplicationTime      - to get the current time
    '          DirectXTimer.GetElapsedTime  - to get the time that elapsed between 
    '                                  TIMER_GETELAPSEDTIME calls
    '-----------------------------------------------------------------------------
    Public Shared Function Timer(ByVal command As DirectXTimer) As Single
        If Not isTimerInitialized Then
            isTimerInitialized = True

            ' Use QueryPerformanceFrequency() to get frequency of timer.  If QPF is
            ' not supported, we will timeGetTime() which returns milliseconds.
            Dim qwTicksPerSec As Long = 0
            m_bUsingQPF = QueryPerformanceFrequency(qwTicksPerSec)
            If m_bUsingQPF Then
                m_llQPFTicksPerSec = qwTicksPerSec
            End If
        End If
        If m_bUsingQPF Then
            Dim time As Double
            Dim fElapsedTime As Double
            Dim qwTime As Long = 0

            ' Get either the current time or the stop time, depending
            ' on whether we're stopped and what command was sent
            If m_llStopTime <> 0 And command <> DirectXTimer.Start And command <> DirectXTimer.GetAbsoluteTime Then
                qwTime = m_llStopTime
            Else
                QueryPerformanceCounter(qwTime)
            End If
            ' Return the elapsed time
            If command = DirectXTimer.GetElapsedTime Then
                fElapsedTime = CDbl(qwTime - m_llLastElapsedTime) / CDbl(m_llQPFTicksPerSec)
                m_llLastElapsedTime = qwTime
                Return CSng(fElapsedTime)
            End If

            ' Return the current time
            If command = DirectXTimer.GetApplicationTime Then
                Dim fAppTime As Double = CDbl(qwTime - m_llBaseTime) / CDbl(m_llQPFTicksPerSec)
                Return CSng(fAppTime)
            End If

            ' Reset the timer
            If command = DirectXTimer.Reset Then
                m_llBaseTime = qwTime
                m_llLastElapsedTime = qwTime
                m_llStopTime = 0
                m_bTimerStopped = False
                Return 0.0F
            End If

            ' Start the timer
            If command = DirectXTimer.Start Then
                If m_bTimerStopped Then
                    m_llBaseTime += qwTime - m_llStopTime
                End If
                m_llStopTime = 0
                m_llLastElapsedTime = qwTime
                m_bTimerStopped = False
                Return 0.0F
            End If

            ' Stop the timer
            If command = DirectXTimer.Stop Then
                If Not m_bTimerStopped Then
                    m_llStopTime = qwTime
                    m_llLastElapsedTime = qwTime
                    m_bTimerStopped = True
                End If
                Return 0.0F
            End If

            ' Advance the timer by 1/10th second
            If command = DirectXTimer.Advance Then
                m_llStopTime += m_llQPFTicksPerSec / 10
                Return 0.0F
            End If

            If command = DirectXTimer.GetAbsoluteTime Then
                time = qwTime / CDbl(m_llQPFTicksPerSec)
                Return CSng(time)
            End If

            Return -1.0F ' Invalid command specified
        Else
            ' Get the time using timeGetTime()
            Dim time As Double
            Dim fElapsedTime As Double

            ' Get either the current time or the stop time, depending
            ' on whether we're stopped and what command was sent
            If m_fStopTime <> 0.0 And command <> DirectXTimer.Start And command <> DirectXTimer.GetAbsoluteTime Then
                time = m_fStopTime
            Else
                time = timeGetTime() * 0.001
            End If
            ' Return the elapsed time
            If command = DirectXTimer.GetElapsedTime Then
                fElapsedTime = CDbl(time - m_fLastElapsedTime)
                m_fLastElapsedTime = time
                Return CSng(fElapsedTime)
            End If

            ' Return the current time
            If command = DirectXTimer.GetApplicationTime Then
                Return CSng(time - m_fBaseTime)
            End If

            ' Reset the timer
            If command = DirectXTimer.Reset Then
                m_fBaseTime = time
                m_fLastElapsedTime = time
                m_fStopTime = 0
                m_bTimerStopped = False
                Return 0.0F
            End If

            ' Start the timer
            If command = DirectXTimer.Start Then
                If m_bTimerStopped Then
                    m_fBaseTime += time - m_fStopTime
                End If
                m_fStopTime = 0.0F
                m_fLastElapsedTime = time
                m_bTimerStopped = False
                Return 0.0F
            End If

            ' Stop the timer
            If command = DirectXTimer.Stop Then
                If Not m_bTimerStopped Then
                    m_fStopTime = time
                    m_fLastElapsedTime = time
                    m_bTimerStopped = True
                End If
                Return 0.0F
            End If

            ' Advance the timer by 1/10th second
            If command = DirectXTimer.Advance Then
                m_fStopTime += 0.1F
                Return 0.0F
            End If

            If command = DirectXTimer.GetAbsoluteTime Then
                Return CSng(time)
            End If

            Return -1.0F ' Invalid command specified
            End If
    End Function 'Timer




    '-----------------------------------------------------------------------------
    ' Name: DXUtil.FindMediaFile()
    ' Desc: Returns a valid path to a DXSDK media file
    '-----------------------------------------------------------------------------
    Public Shared Function FindMediaFile(ByVal sPath As String, ByVal sFilename As String) As String
        ' First try to load the file in the full path
        If Not (sPath Is Nothing) Then
            If File.Exists((AppendDirSep(sPath) + sFilename)) Then
                Return AppendDirSep(sPath) + sFilename
            End If
        End If
        ' if not try to find the filename in the current folder.
        If File.Exists(sFilename) Then
            Return AppendDirSep(Directory.GetCurrentDirectory()) + sFilename
        End If
        ' last, check if the file exists in the media directory
        If File.Exists((AppendDirSep(SdkMediaPath) + sFilename)) Then
            Return AppendDirSep(SdkMediaPath) + sFilename
        End If
        Throw New FileNotFoundException("Could not find this file.", sFilename)
    End Function 'FindMediaFile




    '-----------------------------------------------------------------------------
    ' Name: DXUtil.AppendDirSep()
    ' Desc: Returns a valid string with a directory separator at the end.
    '-----------------------------------------------------------------------------
    Private Shared Function AppendDirSep(ByVal sFile As String) As String
        If Not sFile.EndsWith("\") Then
            Return sFile + "\"
        End If

        Return sFile '
    End Function 'AppendDirSep
End Class 'DXUtil