# Microsoft Developer Studio Project File - Name="dsnet" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=dsnet - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DSNetwork.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DSNetwork.mak" CFG="dsnet - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dsnet - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dsnet - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dsnet - Win32 Release Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dsnet - Win32 Debug Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dsnet - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gz /MD /W4 /O2 /I "..\idl" /I "..\receiver" /I "..\sender" /I "..\include" /I "..\..\..\BaseClasses" /I "..\filter" /D DBG=0 /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /YX /Oxs /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\BaseClasses" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\BaseClasses\Release\strmbase.lib msvcrt.lib dsnetifc.lib dsrecv.lib dssend.lib nutil.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib ws2_32.lib /nologo /base:"0x1d1c0000" /dll /pdb:none /machine:I386 /nodefaultlib /out:"release\dsnet.ax" /libpath:"..\idl\release" /libpath:"..\sender\release" /libpath:"..\receiver\release" /libpath:"..\util\release" /subsystem:windows,4.0 /opt:ref /release /debug:none /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "dsnet - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gz /MDd /W4 /Gm /Zi /Od /I "..\..\..\..\..\..\include" /I "..\filter" /I "..\..\..\BaseClasses" /I "..\idl" /I "..\receiver" /I "..\sender" /I "..\include" /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /D "_DEBUG" /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /FR /YX /Oid /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\..\BaseClasses" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\BaseClasses\Debug\strmbasd.lib msvcrtd.lib dsnetifc.lib dsrecv.lib dssend.lib nutil.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib ws2_32.lib /nologo /base:"0x1d1c0000" /dll /pdb:"debug\dsnet.pdb" /debug /machine:I386 /nodefaultlib:"libcmtd" /out:"debug\dsnet.ax" /libpath:"..\idl\debug" /libpath:"..\sender\debug" /libpath:"..\receiver\debug" /libpath:"..\util\debug" /debug:mapped,full /subsystem:windows,4.0 /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "dsnet - Win32 Release Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode"
# PROP Intermediate_Dir "Release_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gz /MD /W4 /O2 /I "..\idl" /I "..\receiver" /I "..\sender" /I "..\include" /I "..\..\..\BaseClasses" /I "..\filter" /D DBG=0 /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX /Oxs /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\BaseClasses" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\BaseClasses\Release_unicode\strmbase.lib msvcrt.lib dsnetifc.lib dsrecv.lib dssend.lib nutil.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib ws2_32.lib /nologo /base:"0x1d1c0000" /dll /pdb:none /machine:I386 /nodefaultlib /out:"Release_Unicode\dsnet.ax" /libpath:"..\idl\release_unicode" /libpath:"..\sender\release_unicode" /libpath:"..\receiver\release_unicode" /libpath:"..\util\release_unicode" /subsystem:windows,4.0 /opt:ref /release /debug:none /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "dsnet - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gz /MDd /W4 /Gm /Zi /Od /I "..\..\..\..\..\..\include" /I "..\filter" /I "..\..\..\BaseClasses" /I "..\idl" /I "..\receiver" /I "..\sender" /I "..\include" /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /D "_DEBUG" /D "INC_OLE2" /D "STRICT" /D _WIN32_WINNT=0x0400 /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D "WIN32" /D "UNICODE" /D "_UNICODE" /FR /YX /Oid /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\..\BaseClasses" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\BaseClasses\Debug_unicode\strmbasd.lib msvcrtd.lib dsnetifc.lib dsrecv.lib dssend.lib nutil.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib ws2_32.lib /nologo /base:"0x1d1c0000" /dll /pdb:"debug\dsnet.pdb" /debug /machine:I386 /nodefaultlib:"libcmtd" /out:"Debug_Unicode\dsnet.ax" /libpath:"..\idl\debug_unicode" /libpath:"..\sender\debug_unicode" /libpath:"..\receiver\debug_unicode" /libpath:"..\util\debug_unicode" /debug:mapped,full /subsystem:windows,4.0 /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "dsnet - Win32 Release"
# Name "dsnet - Win32 Debug"
# Name "dsnet - Win32 Release Unicode"
# Name "dsnet - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dsnet.def
# End Source File
# Begin Source File

SOURCE=.\main.cpp
DEP_CPP_MAIN_=\
	"..\..\..\BaseClasses\amextra.h"\
	"..\..\..\BaseClasses\amfilter.h"\
	"..\..\..\BaseClasses\cache.h"\
	"..\..\..\BaseClasses\combase.h"\
	"..\..\..\BaseClasses\cprop.h"\
	"..\..\..\BaseClasses\ctlutil.h"\
	"..\..\..\BaseClasses\dllsetup.h"\
	"..\..\..\BaseClasses\dsschedule.h"\
	"..\..\..\BaseClasses\fourcc.h"\
	"..\..\..\BaseClasses\measure.h"\
	"..\..\..\BaseClasses\msgthrd.h"\
	"..\..\..\BaseClasses\mtype.h"\
	"..\..\..\BaseClasses\outputq.h"\
	"..\..\..\BaseClasses\pstream.h"\
	"..\..\..\BaseClasses\refclock.h"\
	"..\..\..\BaseClasses\reftime.h"\
	"..\..\..\BaseClasses\renbase.h"\
	"..\..\..\BaseClasses\source.h"\
	"..\..\..\BaseClasses\streams.h"\
	"..\..\..\BaseClasses\strmctl.h"\
	"..\..\..\BaseClasses\sysclock.h"\
	"..\..\..\BaseClasses\transfrm.h"\
	"..\..\..\BaseClasses\transip.h"\
	"..\..\..\BaseClasses\videoctl.h"\
	"..\..\..\BaseClasses\vtrans.h"\
	"..\..\..\BaseClasses\winctrl.h"\
	"..\..\..\BaseClasses\winutil.h"\
	"..\..\..\BaseClasses\wxdebug.h"\
	"..\..\..\BaseClasses\wxlist.h"\
	"..\..\..\BaseClasses\wxutil.h"\
	"..\IDL\dsnetifc.h"\
	"..\include\projpch.h"\
	"..\receiver\dsrecv.h"\
	"..\receiver\proprecv.h"\
	"..\sender\dssend.h"\
	"..\sender\propsend.h"\
	".\precomp.h"\
	
NODEP_CPP_MAIN_=\
	".\udevcod.h"\
	
# ADD CPP /Yu"precomp.h"
# End Source File
# Begin Source File

SOURCE=.\precomp.cpp
DEP_CPP_PRECO=\
	"..\..\..\BaseClasses\amextra.h"\
	"..\..\..\BaseClasses\amfilter.h"\
	"..\..\..\BaseClasses\cache.h"\
	"..\..\..\BaseClasses\combase.h"\
	"..\..\..\BaseClasses\cprop.h"\
	"..\..\..\BaseClasses\ctlutil.h"\
	"..\..\..\BaseClasses\dllsetup.h"\
	"..\..\..\BaseClasses\dsschedule.h"\
	"..\..\..\BaseClasses\fourcc.h"\
	"..\..\..\BaseClasses\measure.h"\
	"..\..\..\BaseClasses\msgthrd.h"\
	"..\..\..\BaseClasses\mtype.h"\
	"..\..\..\BaseClasses\outputq.h"\
	"..\..\..\BaseClasses\pstream.h"\
	"..\..\..\BaseClasses\refclock.h"\
	"..\..\..\BaseClasses\reftime.h"\
	"..\..\..\BaseClasses\renbase.h"\
	"..\..\..\BaseClasses\source.h"\
	"..\..\..\BaseClasses\streams.h"\
	"..\..\..\BaseClasses\strmctl.h"\
	"..\..\..\BaseClasses\sysclock.h"\
	"..\..\..\BaseClasses\transfrm.h"\
	"..\..\..\BaseClasses\transip.h"\
	"..\..\..\BaseClasses\videoctl.h"\
	"..\..\..\BaseClasses\vtrans.h"\
	"..\..\..\BaseClasses\winctrl.h"\
	"..\..\..\BaseClasses\winutil.h"\
	"..\..\..\BaseClasses\wxdebug.h"\
	"..\..\..\BaseClasses\wxlist.h"\
	"..\..\..\BaseClasses\wxutil.h"\
	"..\include\projpch.h"\
	".\precomp.h"\
	
NODEP_CPP_PRECO=\
	".\udevcod.h"\
	
# ADD CPP /Yc"precomp.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\precomp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "*.rc"
# Begin Source File

SOURCE=.\filter.rc
# End Source File
# End Group
# End Target
# End Project
