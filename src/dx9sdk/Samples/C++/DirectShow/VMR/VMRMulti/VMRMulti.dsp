# Microsoft Developer Studio Project File - Name="VMRMulti" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VMRMulti - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VMRMulti.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VMRMulti.mak" CFG="VMRMulti - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VMRMulti - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VMRMulti - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "VMRMulti - Win32 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE "VMRMulti - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VMRMulti - Win32 Release"

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
# ADD BASE CPP /nologo /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\BaseClasses" /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /YX"project.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\BaseClasses\Release\strmbase.lib quartz.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt" /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "VMRMulti - Win32 Debug"

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
# ADD BASE CPP /nologo /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /I "..\..\BaseClasses" /I "..\inc" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /YX"project.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\BaseClasses\Debug\strmbasd.lib strmiids.lib quartz.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmtd" /pdbtype:sept /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none /incremental:no

!ELSEIF  "$(CFG)" == "VMRMulti - Win32 Release Unicode"

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
# ADD BASE CPP /nologo /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\BaseClasses" /I "..\inc" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"project.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\BaseClasses\Release_unicode\strmbase.lib quartz.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt" /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "VMRMulti - Win32 Debug Unicode"

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
# ADD BASE CPP /nologo /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /Gi /GX /Zi /Od /I "..\..\BaseClasses" /I "..\inc" /D "_DEBUG" /D "DEBUG" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"project.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\BaseClasses\Debug_unicode\strmbasd.lib strmiids.lib quartz.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmtd" /pdbtype:sept /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none /incremental:no

!ENDIF 

# Begin Target

# Name "VMRMulti - Win32 Release"
# Name "VMRMulti - Win32 Debug"
# Name "VMRMulti - Win32 Release Unicode"
# Name "VMRMulti - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=AP.cpp
# End Source File
# Begin Source File

SOURCE=CMultiSAP.cpp
# End Source File
# Begin Source File

SOURCE=DDrawSupport.cpp
# End Source File
# Begin Source File

SOURCE=Movie.cpp
# End Source File
# Begin Source File

SOURCE=resource.rc
# End Source File
# Begin Source File

SOURCE=VMRMulti.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=CMultiSAP.h
# End Source File
# Begin Source File

SOURCE=DDrawSupport.h
# End Source File
# Begin Source File

SOURCE=Movie.h
# End Source File
# Begin Source File

SOURCE=project.h
# End Source File
# Begin Source File

SOURCE=resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=res\DX5.bmp
# End Source File
# Begin Source File

SOURCE=res\DX7.bmp
# End Source File
# Begin Source File

SOURCE=res\eject.bmp
# End Source File
# Begin Source File

SOURCE=res\FLARE1.BMP
# End Source File
# Begin Source File

SOURCE=res\FLARE2.BMP
# End Source File
# Begin Source File

SOURCE=res\FLARE3.BMP
# End Source File
# Begin Source File

SOURCE=res\FLARE4.BMP
# End Source File
# Begin Source File

SOURCE=res\FLARE5.BMP
# End Source File
# Begin Source File

SOURCE=res\FLARE6.BMP
# End Source File
# Begin Source File

SOURCE=res\FLARE7.bmp
# End Source File
# Begin Source File

SOURCE=res\FLARE8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Frame.bmp
# End Source File
# Begin Source File

SOURCE=res\play.bmp
# End Source File
# Begin Source File

SOURCE=res\SHINE1.bmp
# End Source File
# Begin Source File

SOURCE=res\SHINE2.bmp
# End Source File
# Begin Source File

SOURCE=res\SHINE3.bmp
# End Source File
# Begin Source File

SOURCE=res\SHINE4.bmp
# End Source File
# Begin Source File

SOURCE=res\SHINE5.bmp
# End Source File
# Begin Source File

SOURCE=res\SHINE6.bmp
# End Source File
# Begin Source File

SOURCE=res\stop.bmp
# End Source File
# Begin Source File

SOURCE=res\trans.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\vmrsample.ico
# End Source File
# End Group
# Begin Group "Effects"

# PROP Default_Filter "*.cpp;*.h"
# Begin Source File

SOURCE=effects\Effect.cpp
# End Source File
# Begin Source File

SOURCE=effects\Effect.h
# End Source File
# End Group
# Begin Group "D3DHelpers"

# PROP Default_Filter "*.cpp;*.h"
# Begin Source File

SOURCE=D3DHelpers\d3dmath.cpp
# ADD CPP /I "."
# End Source File
# Begin Source File

SOURCE=D3DHelpers\d3dmath.h
# End Source File
# Begin Source File

SOURCE=D3DHelpers\d3dtextr.cpp
# ADD CPP /I "."
# End Source File
# Begin Source File

SOURCE=D3DHelpers\d3dtextr.h
# End Source File
# Begin Source File

SOURCE=D3DHelpers\d3dutil.cpp
# ADD CPP /I "."
# End Source File
# Begin Source File

SOURCE=D3DHelpers\d3dutil.h
# End Source File
# End Group
# Begin Group "Sparkle"

# PROP Default_Filter "*.cpp;*.h"
# Begin Source File

SOURCE=Sparkles\sparkles.cpp
# End Source File
# Begin Source File

SOURCE=Sparkles\sparkles.h
# End Source File
# End Group
# End Target
# End Project
