# Microsoft Developer Studio Project File - Name="dsrecv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=dsrecv - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dsrecv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dsrecv.mak" CFG="dsrecv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dsrecv - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "dsrecv - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "dsrecv - Win32 Release Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "dsrecv - Win32 Debug Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dsrecv - Win32 Release"

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

!ELSEIF  "$(CFG)" == "dsrecv - Win32 Debug"

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

!ELSEIF  "$(CFG)" == "dsrecv - Win32 Release Unicode"

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

!ELSEIF  "$(CFG)" == "dsrecv - Win32 Debug Unicode"

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

# Name "dsrecv - Win32 Release"
# Name "dsrecv - Win32 Debug"
# Name "dsrecv - Win32 Release Unicode"
# Name "dsrecv - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\alloc.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\buffpool.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\dsrecv.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\mspool.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\netrecv.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\precomp.cpp
# ADD CPP /Yc"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\proprecv.cpp
# ADD CPP /Yu"precomp.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\alloc.h
# End Source File
# Begin Source File

SOURCE=.\buffpool.h
# End Source File
# Begin Source File

SOURCE=.\dsrecv.h
# End Source File
# Begin Source File

SOURCE=.\le.h
# End Source File
# Begin Source File

SOURCE=.\mspool.h
# End Source File
# Begin Source File

SOURCE=.\netrecv.h
# End Source File
# Begin Source File

SOURCE=.\precomp.h
# End Source File
# Begin Source File

SOURCE=..\include\projpch.h
# End Source File
# Begin Source File

SOURCE=.\proprecv.h
# End Source File
# End Group
# End Target
# End Project
