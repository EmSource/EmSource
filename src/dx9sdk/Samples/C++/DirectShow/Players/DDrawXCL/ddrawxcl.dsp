# Microsoft Developer Studio Project File - Name="DDrawXCL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DDrawXCL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DDrawXCL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DDrawXCL.mak" CFG="DDrawXCL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DDrawXCL - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DDrawXCL - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "DDrawXCL - Win32 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE "DDrawXCL - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DDrawXCL - Win32 Release"

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
# ADD BASE CPP /nologo /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D _WIN32_WINNT=0x400 /YX"streams.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\baseclasses\release\strmbase.lib quartz.lib kernel32.lib user32.lib comdlg32.lib ole32.lib oleaut32.lib gdi32.lib ddraw.lib msvcrt.lib uuid.lib advapi32.lib winmm.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /pdb:none /machine:I386 /nodefaultlib /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "DDrawXCL - Win32 Debug"

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
# ADD BASE CPP /nologo /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W4 /GX /Zi /Od /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /D "_WINDOWS" /D "DEBUG" /D "WIN32" /D "_DEBUG" /D _WIN32_WINNT=0x400 /YX"streams.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\baseclasses\debug\strmbasd.lib quartz.lib kernel32.lib user32.lib comdlg32.lib ole32.lib oleaut32.lib gdi32.lib ddraw.lib msvcrtd.lib uuid.lib advapi32.lib winmm.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /pdb:none /debug /machine:I386 /nodefaultlib /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "DDrawXCL - Win32 Release Unicode"

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
# ADD BASE CPP /nologo /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /D "_WINDOWS" /D "NDEBUG" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"streams.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\baseclasses\release_unicode\strmbase.lib quartz.lib kernel32.lib user32.lib comdlg32.lib ole32.lib oleaut32.lib gdi32.lib ddraw.lib msvcrt.lib uuid.lib advapi32.lib winmm.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /pdb:none /machine:I386 /nodefaultlib /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "DDrawXCL - Win32 Debug Unicode"

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
# ADD BASE CPP /nologo /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W4 /GX /Zi /Od /I "..\..\BaseClasses" /I "..\..\..\..\..\include" /D "_WINDOWS" /D "DEBUG" /D "_DEBUG" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"streams.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\baseclasses\debug_unicode\strmbasd.lib quartz.lib kernel32.lib user32.lib comdlg32.lib ole32.lib oleaut32.lib gdi32.lib ddraw.lib msvcrtd.lib uuid.lib advapi32.lib winmm.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /pdb:none /debug /machine:I386 /nodefaultlib /ignore:4089 /ignore:4078

!ENDIF 

# Begin Target

# Name "DDrawXCL - Win32 Release"
# Name "DDrawXCL - Win32 Debug"
# Name "DDrawXCL - Win32 Release Unicode"
# Name "DDrawXCL - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "*.cpp;*.rc;*.ico"
# Begin Source File

SOURCE=.\ddrawobj.cpp
# End Source File
# Begin Source File

SOURCE=.\DDrawXCL.cpp
# End Source File
# Begin Source File

SOURCE=.\DDrawXCL.ico
# End Source File
# Begin Source File

SOURCE=.\vidplay.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\ddrawobj.h
# End Source File
# Begin Source File

SOURCE=.\DDrawXCL.h
# End Source File
# Begin Source File

SOURCE=.\vidplay.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\DDrawXCL.rc
# End Source File
# End Group
# End Target
# End Project
