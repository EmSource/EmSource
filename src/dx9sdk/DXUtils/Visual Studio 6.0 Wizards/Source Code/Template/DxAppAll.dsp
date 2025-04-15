# Microsoft Developer Studio Project File - Name="DxApp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DxApp - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DxAppAll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DxAppAll.mak" CFG="DxApp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DxApp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DxApp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DxApp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\framework\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 dsound.lib dinput8.lib dxerr8.lib d3dx8.lib d3d8.lib d3dxof.lib dxguid.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\framework\lib"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 dsound.lib dinput8.lib dxerr8.lib d3dx8dt.lib d3d8.lib d3dxof.lib dxguid.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\..\framework\lib"

!ENDIF 

# Begin Target

# Name "DxApp - Win32 Release"
# Name "DxApp - Win32 Debug"
# Begin Group "DirectX Framework Classes"

# PROP Default_Filter "*.*"
# Begin Source File

SOURCE=.\confirm.inf
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3dapp.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3dapp.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3denumeration.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3denumeration.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3dfile.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3dfile.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3dfont.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3dfont.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3dsettings.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3dsettings.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3dutil.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3dutil.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DirectX.ico

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\diutil.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\diutil.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dmutil.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dmutil.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dsutil.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dsutil.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DxAppAll.dsp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\dxutil.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dxutil.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netclient.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netclient.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netclientres.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netconnect.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netconnect.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netconnectres.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netvoice.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\netvoice.h

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newproj.inf
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "D3D Dlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\d3d_dlg\d3d_dlg.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3d_dlg\d3d_dlg.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3d_dlg\d3d_dlg.rc
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3d_dlg\d3d_dlgres.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3d_dlg\d3d_dlgStdafx.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3d_dlg\d3d_dlgStdafx.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "D3D Win"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\d3d_win\d3d_win.cpp

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3d_win\d3d_win.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\d3d_win\d3d_win.rc

!IF  "$(CFG)" == "DxApp - Win32 Release"

!ELSEIF  "$(CFG)" == "DxApp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\d3d_win\d3d_winres.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "GDI Win"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gdi_win\gdi_win.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\gdi_win\gdi_win.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\gdi_win\gdi_win.rc
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\gdi_win\gdi_winres.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "GDI Dlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gdi_dlg\gdi_dlg.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\gdi_dlg\gdi_dlg.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\gdi_dlg\gdi_dlg.rc
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\gdi_dlg\gdi_dlgres.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\gdi_dlg\gdi_dlgStdAfx.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\gdi_dlg\gdi_dlgStdAfx.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Target
# End Project
