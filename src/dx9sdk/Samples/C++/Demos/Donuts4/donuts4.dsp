# Microsoft Developer Studio Project File - Name="Donuts4" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Donuts4 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Donuts4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Donuts4.mak" CFG="Donuts4 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Donuts4 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Donuts4 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\common\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 d3dx9.lib d3d9.lib dxerr9.lib d3dxof.lib dinput8.lib dsound.lib winspool.lib ole32.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib /nologo /stack:0x1f4000,0x1f4000 /subsystem:windows /machine:I386 /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\..\common\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 d3dx9.lib d3d9.lib dxerr9.lib d3dxof.lib dinput8.lib dsound.lib winspool.lib ole32.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib /nologo /stack:0x1f4000,0x1f4000 /subsystem:windows /debug /machine:I386 /pdbtype:sept /ignore:4089 /ignore:4078

!ENDIF 

# Begin Target

# Name "Donuts4 - Win32 Release"
# Name "Donuts4 - Win32 Debug"
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Common\src\d3dfile.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\Common\include\d3dfile.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\d3dfont.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\Common\include\d3dfont.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\d3dutil.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\Common\include\d3dutil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\diutil.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\Common\include\diutil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\dmutil.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\Common\include\dmutil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\dsutil.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\Common\include\dsutil.h
# End Source File
# Begin Source File

SOURCE=..\..\Common\src\dxutil.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\Common\include\dxutil.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\3DDisplayObject.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3DDisplayObject.h
# End Source File
# Begin Source File

SOURCE=.\3DDrawManager.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3DDrawManager.h
# End Source File
# Begin Source File

SOURCE=.\3DModel.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\3DModel.h
# End Source File
# Begin Source File

SOURCE=.\Bullet.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Bullet.h
# End Source File
# Begin Source File

SOURCE=.\DisplayObject.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DisplayObject.h
# End Source File
# Begin Source File

SOURCE=.\donuts.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\donuts.h
# End Source File
# Begin Source File

SOURCE=.\donuts.rc
# End Source File
# Begin Source File

SOURCE=.\EnemyShip.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

# ADD CPP /YX"stdafx.h"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EnemyShip.h
# End Source File
# Begin Source File

SOURCE=.\FileWatch.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FileWatch.h
# End Source File
# Begin Source File

SOURCE=.\GameMenu.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gamemenu.h
# End Source File
# Begin Source File

SOURCE=.\HeightMap.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HeightMap.h
# End Source File
# Begin Source File

SOURCE=.\InputManager.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\InputManager.h
# End Source File
# Begin Source File

SOURCE=.\NotifyTool.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NotifyTool.h
# End Source File
# Begin Source File

SOURCE=.\ParticleSystem.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ParticleSystem.h
# End Source File
# Begin Source File

SOURCE=.\PlayerShip.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PlayerShip.h
# End Source File
# Begin Source File

SOURCE=.\profile.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Profile.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TerrainEngine.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TerrainEngine.h
# End Source File
# Begin Source File

SOURCE=.\TerrainMesh.cpp

!IF  "$(CFG)" == "Donuts4 - Win32 Release"

!ELSEIF  "$(CFG)" == "Donuts4 - Win32 Debug"

# ADD CPP /YX"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TerrainMesh.h
# End Source File
# End Target
# End Project
