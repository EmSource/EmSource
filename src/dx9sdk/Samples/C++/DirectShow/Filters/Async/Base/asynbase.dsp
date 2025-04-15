# Microsoft Developer Studio Project File - Name="asynbase" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=asynbase - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "asynbase.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "asynbase.mak" CFG="asynbase - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "asynbase - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "asynbase - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "asynbase - Win32 Release Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "asynbase - Win32 Debug Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "asynbase - Win32 Release"

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
# ADD CPP /nologo /Gz /MT /W4 /GX /O2 /I "..\..\..\BaseClasses" /I "..\..\..\..\..\..\include" /I "..\include" /I "..\filter" /D "NDEBUG" /D "_MBCS" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WIN32" /D "_MT" /D "_LIB" /D WINVER=0x0400 /YX"streams.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "asynbase - Win32 Debug"

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
# ADD BASE CPP /nologo /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MTd /W4 /Gm /GX /Zi /Od /I "..\..\..\BaseClasses" /I "..\..\..\..\..\..\include" /I "..\include" /I "..\filter" /D "INC_OLE2" /D "STRICT" /D _X86_=1 /D DBG=1 /D "DEBUG" /D "_DEBUG" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WIN32" /D "_MT" /D "_LIB" /D WINVER=0x0400 /YX"streams.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "asynbase - Win32 Release Unicode"

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
# ADD CPP /nologo /Gz /MT /W4 /GX /O2 /I "..\..\..\BaseClasses" /I "..\..\..\..\..\..\include" /I "..\include" /I "..\filter" /D "NDEBUG" /D "_MBCS" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_LIB" /D WINVER=0x0400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"streams.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "asynbase - Win32 Debug Unicode"

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
# ADD BASE CPP /nologo /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MTd /W4 /Gm /GX /Zi /Od /I "..\..\..\BaseClasses" /I "..\..\..\..\..\..\include" /I "..\include" /I "..\filter" /D "INC_OLE2" /D "STRICT" /D _X86_=1 /D DBG=1 /D "DEBUG" /D "_DEBUG" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_LIB" /D WINVER=0x0400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"streams.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "asynbase - Win32 Release"
# Name "asynbase - Win32 Debug"
# Name "asynbase - Win32 Release Unicode"
# Name "asynbase - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\asyncio.cpp
# End Source File
# Begin Source File

SOURCE=.\asyncrdr.cpp
# End Source File
# End Group
# End Target
# End Project
