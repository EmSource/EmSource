# Microsoft Developer Studio Project File - Name="dssend" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dssend - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dssend.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dssend.mak" CFG="dssend - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dssend - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "dssend - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "dssend - Win32 Release Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "dssend - Win32 Debug Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dssend - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Gz /MD /W4 /GX /O2 /I "..\include" /I "..\..\..\BaseClasses" /I "..\idl" /I "..\receiver" /I "..\sender" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\filter" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "dssend - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MDd /W4 /Gm /GX /Zi /Od /I "..\..\..\..\..\..\include" /I "..\idl" /I "..\filter" /I "..\include" /I "..\..\..\BaseClasses" /I "..\receiver" /I "..\sender" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\filter" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "dssend - Win32 Release Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode"
# PROP Intermediate_Dir "Release_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Gz /MD /W4 /GX /O2 /I "..\include" /I "..\..\..\BaseClasses" /I "..\idl" /I "..\receiver" /I "..\sender" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\filter" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "dssend - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MDd /W4 /Gm /GX /Zi /Od /I "..\..\..\..\..\..\include" /I "..\idl" /I "..\filter" /I "..\include" /I "..\..\..\BaseClasses" /I "..\receiver" /I "..\sender" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /D "WIN32" /D "UNICODE" /D "_UNICODE" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\filter" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "dssend - Win32 Release"
# Name "dssend - Win32 Debug"
# Name "dssend - Win32 Release Unicode"
# Name "dssend - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dssend.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\netsend.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\precomp.cpp
# ADD CPP /Yc"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\propsend.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dssend.h
# End Source File
# Begin Source File

SOURCE=.\netsend.h
# End Source File
# Begin Source File

SOURCE=..\include\nutil.h
# End Source File
# Begin Source File

SOURCE=.\precomp.h
# End Source File
# Begin Source File

SOURCE=..\include\projpch.h
# End Source File
# Begin Source File

SOURCE=.\propsend.h
# End Source File
# End Group
# End Target
# End Project
