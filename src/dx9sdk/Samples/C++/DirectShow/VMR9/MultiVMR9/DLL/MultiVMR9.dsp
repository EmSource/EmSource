# Microsoft Developer Studio Project File - Name="MultiVMR9" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MultiVMR9 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MultiVMR9.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MultiVMR9.mak" CFG="MultiVMR9 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MultiVMR9 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MultiVMR9 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MultiVMR9 - Win32 Release Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MultiVMR9 - Win32 Debug Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MultiVMR9 - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTIVMR9_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\BaseClasses" /I "..\..\inc" /I ".\Release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTIVMR9_EXPORTS" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ..\..\..\BaseClasses\Release\strmbase.lib strmiids.lib ddraw.lib dxguid.lib version.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib d3d9.lib quartz.lib advapi32.lib ole32.lib oleaut32.lib user32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "MultiVMR9 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MultiVMR9___Win32_Debug"
# PROP BASE Intermediate_Dir "MultiVMR9___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTIVMR9_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /Gi /GX /Zi /Od /I "..\..\..\BaseClasses" /I "..\..\inc" /I ".\Debug" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /D "MULTIVMR9_EXPORTS" /D _WIN32_WINNT=0x400 /D WINVER=0x400 /D "_WIN32_DCOM" /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\BaseClasses\Debug\strmbasd.lib strmiids.lib ddraw.lib dxguid.lib version.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib d3d9.lib quartz.lib advapi32.lib ole32.lib oleaut32.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "MultiVMR9 - Win32 Release Unicode"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTIVMR9_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\BaseClasses" /I "..\..\inc" /I ".\Release" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTIVMR9_EXPORTS" /D "UNICODE" /D "_UNICODE" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ..\..\..\BaseClasses\Release_Unicode\strmbase.lib strmiids.lib ddraw.lib dxguid.lib version.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib d3d9.lib quartz.lib advapi32.lib ole32.lib oleaut32.lib user32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "MultiVMR9 - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MultiVMR9___Win32_Debug"
# PROP BASE Intermediate_Dir "MultiVMR9___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTIVMR9_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /Gi /GX /Zi /Od /I "..\..\..\BaseClasses" /I "..\..\inc" /I ".\Debug" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /D "MULTIVMR9_EXPORTS" /D _WIN32_WINNT=0x400 /D WINVER=0x400 /D "_WIN32_DCOM" /D "UNICODE" /D "_UNICODE" /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\BaseClasses\Debug_Unicode\strmbasd.lib strmiids.lib ddraw.lib dxguid.lib version.lib odbc32.lib odbccp32.lib winmm.lib comctl32.lib d3d9.lib quartz.lib advapi32.lib ole32.lib oleaut32.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "MultiVMR9 - Win32 Release"
# Name "MultiVMR9 - Win32 Debug"
# Name "MultiVMR9 - Win32 Release Unicode"
# Name "MultiVMR9 - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MixerControl.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiVMR9.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiVMR9.def
# End Source File
# Begin Source File

SOURCE=.\MultiVMR9.idl

!IF  "$(CFG)" == "MultiVMR9 - Win32 Release"

# ADD MTL /h "MultiVMR9.h"
# SUBTRACT MTL /mktyplib203

!ELSEIF  "$(CFG)" == "MultiVMR9 - Win32 Debug"

# PROP Intermediate_Dir "Debug"
# ADD MTL /h "MultiVMR9.h"
# SUBTRACT MTL /mktyplib203

!ELSEIF  "$(CFG)" == "MultiVMR9 - Win32 Release Unicode"

!ELSEIF  "$(CFG)" == "MultiVMR9 - Win32 Debug Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MultiVMR9_i.c
# End Source File
# Begin Source File

SOURCE=.\RenderEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\UILayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Wizard.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MixerControl.h
# End Source File
# Begin Source File

SOURCE=.\MultiVMRguids.h
# End Source File
# Begin Source File

SOURCE=.\RenderEngine.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\UILayer.h
# End Source File
# Begin Source File

SOURCE=.\Wizard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\MultiVMR9.rc
# End Source File
# End Group
# End Target
# End Project
