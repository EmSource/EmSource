# Microsoft Developer Studio Project File - Name="Jukebox" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Jukebox - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Jukebox.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Jukebox.mak" CFG="Jukebox - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Jukebox - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Jukebox - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Jukebox - Win32 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE "Jukebox - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE "Jukebox - Win32 WMF9 Release" (based on "Win32 (x86) Application")
!MESSAGE "Jukebox - Win32 WMF9 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Jukebox - Win32 WMF9 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE "Jukebox - Win32 WMF9 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Jukebox - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /Gi /GX /O2 /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /I "..\..\common" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "WIN32" /D "NDEBUG" /D _WIN32_WINNT=0x400 /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 strmiids.lib ..\..\common\wmstub.lib ..\..\common\wmvcore.lib msvcrt.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /machine:I386 /nodefaultlib:"libcmt.lib" /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "Jukebox - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /I "..\..\common" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "WIN32" /D "_DEBUG" /D _WIN32_WINNT=0x400 /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmiids.lib ..\..\common\wmstub.lib ..\..\common\wmvcore.lib msvcrtd.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /pdbtype:sept /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "Jukebox - Win32 Release Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode"
# PROP Intermediate_Dir "Release_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /Gi /GX /O2 /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /I "..\..\common" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NDEBUG" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 strmiids.lib ..\..\common\wmstub.lib ..\..\common\wmvcore.lib msvcrt.lib /nologo /stack:0x200000,0x200000 /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"libcmt.lib" /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "Jukebox - Win32 Debug Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /I "..\..\common" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_DEBUG" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmiids.lib ..\..\common\wmstub.lib ..\..\common\wmvcore.lib msvcrtd.lib /nologo /stack:0x200000,0x200000 /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /pdbtype:sept /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "Jukebox - Win32 WMF9 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_WMF9"
# PROP Intermediate_Dir "Release_WMF9"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /Gi /GX /O2 /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /I "..\..\common" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "WIN32" /D "NDEBUG" /D _WIN32_WINNT=0x400 /D "TARGET_WMF9" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 strmiids.lib ..\..\common\wmvcore.lib msvcrt.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /machine:I386 /nodefaultlib:"libcmt.lib" /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "Jukebox - Win32 WMF9 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_WMF9"
# PROP Intermediate_Dir "Debug_WMF9"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /I "..\..\common" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "WIN32" /D "_DEBUG" /D _WIN32_WINNT=0x400 /D "TARGET_WMF9" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmiids.lib ..\..\common\wmvcore.lib msvcrtd.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /pdbtype:sept /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "Jukebox - Win32 WMF9 Release Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode_WMF9"
# PROP Intermediate_Dir "Release_Unicode_WMF9"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /Gi /GX /O2 /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /I "..\..\common" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NDEBUG" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /D "TARGET_WMF9" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 strmiids.lib ..\..\common\wmvcore.lib msvcrt.lib /nologo /stack:0x200000,0x200000 /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /nodefaultlib:"libcmt.lib" /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "Jukebox - Win32 WMF9 Debug Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode_WMF9"
# PROP Intermediate_Dir "Debug_Unicode_WMF9"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /I "..\..\common" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_DEBUG" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /D "TARGET_WMF9" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 strmiids.lib ..\..\common\wmvcore.lib msvcrtd.lib /nologo /stack:0x200000,0x200000 /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /pdbtype:sept /ignore:4089 /ignore:4078

!ENDIF 

# Begin Target

# Name "Jukebox - Win32 Release"
# Name "Jukebox - Win32 Debug"
# Name "Jukebox - Win32 Release Unicode"
# Name "Jukebox - Win32 Debug Unicode"
# Name "Jukebox - Win32 WMF9 Release"
# Name "Jukebox - Win32 WMF9 Debug"
# Name "Jukebox - Win32 WMF9 Release Unicode"
# Name "Jukebox - Win32 WMF9 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\globals.cpp
# End Source File
# Begin Source File

SOURCE=.\Jukebox.cpp
# End Source File
# Begin Source File

SOURCE=.\JukeboxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\keyprovider.cpp
# End Source File
# Begin Source File

SOURCE=.\playvideo.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Jukebox.h
# End Source File
# Begin Source File

SOURCE=.\JukeboxDlg.h
# End Source File
# Begin Source File

SOURCE=.\keyprovider.h
# End Source File
# Begin Source File

SOURCE=.\mediatypes.h
# End Source File
# Begin Source File

SOURCE=.\playvideo.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Jukebox.ico
# End Source File
# Begin Source File

SOURCE=.\Jukebox.rc
# End Source File
# Begin Source File

SOURCE=.\res\Jukebox.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
