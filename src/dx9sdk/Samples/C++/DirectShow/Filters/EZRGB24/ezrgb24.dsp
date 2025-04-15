# Microsoft Developer Studio Project File - Name="ezrgb24" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ezrgb24 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ezrgb24.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ezrgb24.mak" CFG="ezrgb24 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ezrgb24 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ezrgb24 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ezrgb24 - Win32 Release Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ezrgb24 - Win32 Debug Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ezrgb24 - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gz /MD /W4 /Gy /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /D DBG=0 /D WINVER=0x400 /D "INC_OLE2" /D "STRICT" /D "WIN32" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /YX"streams.h" /Oxs /GF /D_WIN32_WINNT=-0x0400 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\BaseClasses" /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\BaseClasses\release\strmbase.lib msvcrt.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib /nologo /stack:0x200000,0x200000 /dll /pdb:none /machine:I386 /nodefaultlib /def:".\ezrgb24.def" /out:".\Release\ezrgb24.ax" /libpath:"..\..\..\..\lib" /subsystem:windows,4.0 /opt:ref /release /debug:none /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "ezrgb24 - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /Gz /MDd /W4 /Zi /Od /Gy /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /D _WIN32_WINNT=0x0400 /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /D "_DEBUG" /D "INC_OLE2" /D "STRICT" /D "WIN32" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /YX"streams.h" /Oid /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\BaseClasses" /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\BaseClasses\debug\strmbasd.lib msvcrtd.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib /nologo /stack:0x200000,0x200000 /dll /pdb:none /debug /machine:I386 /nodefaultlib /out:".\Debug\ezrgb24.ax" /libpath:"..\..\..\..\lib" /debug:mapped,full /subsystem:windows,4.0 /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "ezrgb24 - Win32 Release Unicode"

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
# ADD CPP /nologo /Gz /MD /W4 /Gy /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /D DBG=0 /D WINVER=0x400 /D "INC_OLE2" /D "STRICT" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"streams.h" /Oxs /GF /D_WIN32_WINNT=-0x0400 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\BaseClasses" /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\BaseClasses\release_unicode\strmbase.lib msvcrt.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib /nologo /stack:0x200000,0x200000 /dll /pdb:none /machine:I386 /nodefaultlib /out:".\Release_Unicode\ezrgb24.ax" /libpath:"..\..\..\..\lib" /subsystem:windows,4.0 /opt:ref /release /debug:none /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "ezrgb24 - Win32 Debug Unicode"

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
# ADD CPP /nologo /Gz /MDd /W4 /Zi /Od /Gy /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /D _WIN32_WINNT=0x0400 /D WINVER=0x0400 /D DBG=1 /D "DEBUG" /D "_DEBUG" /D "INC_OLE2" /D "STRICT" /D "_WIN32" /D "_MT" /D "_DLL" /D _X86_=1 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"streams.h" /Oid /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\BaseClasses" /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\BaseClasses\debug_unicode\strmbasd.lib msvcrtd.lib quartz.lib vfw32.lib winmm.lib kernel32.lib advapi32.lib version.lib largeint.lib user32.lib gdi32.lib comctl32.lib ole32.lib olepro32.lib oleaut32.lib uuid.lib /nologo /stack:0x200000,0x200000 /dll /pdb:none /debug /machine:I386 /nodefaultlib /out:".\Debug_Unicode\ezrgb24.ax" /libpath:"..\..\..\..\lib" /debug:mapped,full /subsystem:windows,4.0 /ignore:4089 /ignore:4078

!ENDIF 

# Begin Target

# Name "ezrgb24 - Win32 Release"
# Name "ezrgb24 - Win32 Debug"
# Name "ezrgb24 - Win32 Release Unicode"
# Name "ezrgb24 - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ezprop.cpp
DEP_CPP_EZPRO=\
	"..\..\BaseClasses\amextra.h"\
	"..\..\BaseClasses\amfilter.h"\
	"..\..\BaseClasses\cache.h"\
	"..\..\BaseClasses\combase.h"\
	"..\..\BaseClasses\cprop.h"\
	"..\..\BaseClasses\ctlutil.h"\
	"..\..\BaseClasses\dllsetup.h"\
	"..\..\BaseClasses\dsschedule.h"\
	"..\..\BaseClasses\fourcc.h"\
	"..\..\BaseClasses\measure.h"\
	"..\..\BaseClasses\msgthrd.h"\
	"..\..\BaseClasses\mtype.h"\
	"..\..\BaseClasses\outputq.h"\
	"..\..\BaseClasses\pstream.h"\
	"..\..\BaseClasses\refclock.h"\
	"..\..\BaseClasses\reftime.h"\
	"..\..\BaseClasses\renbase.h"\
	"..\..\BaseClasses\source.h"\
	"..\..\BaseClasses\streams.h"\
	"..\..\BaseClasses\strmctl.h"\
	"..\..\BaseClasses\sysclock.h"\
	"..\..\BaseClasses\transfrm.h"\
	"..\..\BaseClasses\transip.h"\
	"..\..\BaseClasses\videoctl.h"\
	"..\..\BaseClasses\vtrans.h"\
	"..\..\BaseClasses\winctrl.h"\
	"..\..\BaseClasses\winutil.h"\
	"..\..\BaseClasses\wxdebug.h"\
	"..\..\BaseClasses\wxlist.h"\
	"..\..\BaseClasses\wxutil.h"\
	".\EZprop.h"\
	".\EZrgb24.h"\
	".\EZuids.h"\
	".\iEZ.h"\
	".\resource.h"\
	
NODEP_CPP_EZPRO=\
	".\udevcod.h"\
	
# End Source File
# Begin Source File

SOURCE=.\ezprop.rc
# End Source File
# Begin Source File

SOURCE=.\ezrgb24.cpp
DEP_CPP_EZRGB=\
	"..\..\BaseClasses\amextra.h"\
	"..\..\BaseClasses\amfilter.h"\
	"..\..\BaseClasses\cache.h"\
	"..\..\BaseClasses\combase.h"\
	"..\..\BaseClasses\cprop.h"\
	"..\..\BaseClasses\ctlutil.h"\
	"..\..\BaseClasses\dllsetup.h"\
	"..\..\BaseClasses\dsschedule.h"\
	"..\..\BaseClasses\fourcc.h"\
	"..\..\BaseClasses\measure.h"\
	"..\..\BaseClasses\msgthrd.h"\
	"..\..\BaseClasses\mtype.h"\
	"..\..\BaseClasses\outputq.h"\
	"..\..\BaseClasses\pstream.h"\
	"..\..\BaseClasses\refclock.h"\
	"..\..\BaseClasses\reftime.h"\
	"..\..\BaseClasses\renbase.h"\
	"..\..\BaseClasses\source.h"\
	"..\..\BaseClasses\streams.h"\
	"..\..\BaseClasses\strmctl.h"\
	"..\..\BaseClasses\sysclock.h"\
	"..\..\BaseClasses\transfrm.h"\
	"..\..\BaseClasses\transip.h"\
	"..\..\BaseClasses\videoctl.h"\
	"..\..\BaseClasses\vtrans.h"\
	"..\..\BaseClasses\winctrl.h"\
	"..\..\BaseClasses\winutil.h"\
	"..\..\BaseClasses\wxdebug.h"\
	"..\..\BaseClasses\wxlist.h"\
	"..\..\BaseClasses\wxutil.h"\
	".\EZprop.h"\
	".\EZrgb24.h"\
	".\EZuids.h"\
	".\iEZ.h"\
	".\resource.h"\
	
NODEP_CPP_EZRGB=\
	".\udevcod.h"\
	
# End Source File
# Begin Source File

SOURCE=.\ezrgb24.def

!IF  "$(CFG)" == "ezrgb24 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ezrgb24 - Win32 Debug"

!ELSEIF  "$(CFG)" == "ezrgb24 - Win32 Release Unicode"

!ELSEIF  "$(CFG)" == "ezrgb24 - Win32 Debug Unicode"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\EZprop.h
# End Source File
# Begin Source File

SOURCE=.\EZrgb24.h
# End Source File
# Begin Source File

SOURCE=.\EZuids.h
# End Source File
# Begin Source File

SOURCE=.\iEZ.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# End Target
# End Project
