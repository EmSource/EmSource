# Microsoft Developer Studio Project File - Name="RGBFilters" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RGBFilters - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RGBFilters.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RGBFilters.mak" CFG="RGBFilters - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RGBFilters - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RGBFilters - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RGBFilters - Win32 Release Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RGBFilters - Win32 Debug Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RGBFilters - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RGBFilters_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gz /MD /W4 /GX /O2 /I "..\..\BaseClasses" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RGBFilters_EXPORTS" /D "RELEASE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ..\..\BaseClasses\release\strmbase.lib msvcrt.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x200000,0x200000 /dll /machine:I386 /nodefaultlib /def:".\RGBFilters.def" /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "RGBFilters - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RGBFilters_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Gz /MDd /W4 /Gm /GX /Zi /Od /I "..\..\BaseClasses" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEBUG" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\BaseClasses\debug\strmbasd.lib msvcrtd.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x200000,0x200000 /dll /debug /machine:I386 /nodefaultlib /def:".\RGBFilters.def" /pdbtype:sept /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "RGBFilters - Win32 Release Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode"
# PROP Intermediate_Dir "Release_Unicode"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RGBFilters_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Gz /MD /W4 /GX /O2 /I "..\..\BaseClasses" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RGBFilters_EXPORTS" /D "RELEASE" /D "WIN32" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ..\..\BaseClasses\release_unicode\strmbase.lib msvcrt.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x200000,0x200000 /dll /machine:I386 /nodefaultlib /def:".\RGBFilters.def" /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "RGBFilters - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "RGBFilters_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Gz /MDd /W4 /Gm /GX /Zi /Od /I "..\..\BaseClasses" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DEBUG" /D "WIN32" /D "UNICODE" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "WIN32"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\BaseClasses\debug_unicode\strmbasd.lib msvcrtd.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x200000,0x200000 /dll /debug /machine:I386 /nodefaultlib /def:".\RGBFilters.def" /pdbtype:sept /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "RGBFilters - Win32 Release"
# Name "RGBFilters - Win32 Debug"
# Name "RGBFilters - Win32 Release Unicode"
# Name "RGBFilters - Win32 Debug Unicode"
# Begin Group "RGBFilters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RGBFilters.cpp
# End Source File
# Begin Source File

SOURCE=.\RGBFilters.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\RGBFilters.idl
# ADD MTL /h "iRGBFilters.h"
# SUBTRACT MTL /mktyplib203
# End Source File
# Begin Source File

SOURCE=.\setup.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "AlphaRenderer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AlphaRenderer\AlphaRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\AlphaRenderer\AlphaRenderer.h
# End Source File
# End Group
# Begin Group "RateSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ratesource\ratesource.cpp
# End Source File
# Begin Source File

SOURCE=.\ratesource\ratesource.h
# End Source File
# Begin Source File

SOURCE=.\ratesource\ratestream.cpp
# End Source File
# End Group
# Begin Group "AlphaSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AlphaSource\AlphaSource.cpp
# End Source File
# Begin Source File

SOURCE=.\AlphaSource\AlphaSource.h
# End Source File
# Begin Source File

SOURCE=.\AlphaSource\AlphaStream.cpp
# End Source File
# End Group
# Begin Group "Source8Bit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source8Bit\Source8Bit.cpp
# End Source File
# Begin Source File

SOURCE=.\Source8Bit\Source8Bit.h
# End Source File
# Begin Source File

SOURCE=.\Source8Bit\Source8BitStream.cpp
# End Source File
# End Group
# Begin Group "Source555"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source555\Source555.cpp
# End Source File
# Begin Source File

SOURCE=.\Source555\Source555.h
# End Source File
# Begin Source File

SOURCE=.\Source555\Source555stream.cpp
# End Source File
# End Group
# Begin Group "Source565"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source565\Source565.cpp
# End Source File
# Begin Source File

SOURCE=.\Source565\Source565.h
# End Source File
# Begin Source File

SOURCE=.\Source565\Source565stream.cpp
# End Source File
# End Group
# Begin Group "Source24"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source24\Source24.cpp
# End Source File
# Begin Source File

SOURCE=.\Source24\Source24.h
# End Source File
# Begin Source File

SOURCE=.\Source24\Source24stream.cpp
# End Source File
# End Group
# Begin Group "Source32Bit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source32\Source32.cpp
# End Source File
# Begin Source File

SOURCE=.\Source32\Source32.h
# End Source File
# Begin Source File

SOURCE=.\Source32\Source32stream.cpp
# End Source File
# End Group
# Begin Group "TransNulls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TransNulls\TransNull24.cpp
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull24.h
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull32.cpp
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull32.h
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull32a.cpp
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull32a.h
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull555.cpp
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull555.h
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull565.cpp
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull565.h
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull8.cpp
# End Source File
# Begin Source File

SOURCE=.\TransNulls\TransNull8.h
# End Source File
# End Group
# Begin Group "TransSmpte"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TransSmpte\TransSmpte.cpp
# End Source File
# Begin Source File

SOURCE=.\TransSmpte\TransSmpte.h
# End Source File
# End Group
# End Target
# End Project
