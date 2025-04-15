# Microsoft Developer Studio Project File - Name="VMRXcl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VMRXcl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VMRXcl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VMRXcl.mak" CFG="VMRXcl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VMRXcl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VMRXcl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "VMRXcl - Win32 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE "VMRXcl - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VMRXcl - Win32 Release"

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
# ADD CPP /nologo /MD /W4 /O2 /I "..\..\BaseClasses" /I "..\..\BaseClasses" /I "..\inc" /D "_WINDOWS" /D WINVER=0x501 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D _WIN32_WINNT=0x400 /YX"project.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\BaseClasses\Release\strmbase.lib d3dx.lib strmiids.lib comctl32.lib winmm.lib gdi32.lib ddraw.lib comdlg32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt" /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "VMRXcl - Win32 Debug"

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
# ADD BASE CPP /nologo /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /ZI /Od /I "..\..\BaseClasses" /I "..\inc" /D "DEBUG" /D "_WINDOWS" /D WINVER=0x501 /D "WIN32" /D "_DEBUG" /D "_MBCS" /D _WIN32_WINNT=0x400 /YX"project.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\BaseClasses\Debug\strmbasd.lib d3dx.lib strmiids.lib comctl32.lib winmm.lib gdi32.lib ddraw.lib comdlg32.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"libcmtd" /pdbtype:sept /ignore:4089 /ignore:4078

!ELSEIF  "$(CFG)" == "VMRXcl - Win32 Release Unicode"

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
# ADD CPP /nologo /MD /W4 /O2 /I "..\..\BaseClasses" /I "..\..\BaseClasses" /I "..\inc" /D "_WINDOWS" /D WINVER=0x501 /D "NDEBUG" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"project.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\BaseClasses\Release_unicode\strmbase.lib d3dx.lib strmiids.lib comctl32.lib winmm.lib gdi32.lib ddraw.lib comdlg32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt" /OPT:NOREF /OPT:ICF /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "VMRXcl - Win32 Debug Unicode"

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
# ADD BASE CPP /nologo /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /ZI /Od /I "..\..\BaseClasses" /I "..\inc" /D "DEBUG" /D "_WINDOWS" /D WINVER=0x501 /D "_DEBUG" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "WIN32" /D "UNICODE" /D "_UNICODE" /YX"project.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\BaseClasses\Debug_unicode\strmbasd.lib d3dx.lib strmiids.lib comctl32.lib winmm.lib gdi32.lib ddraw.lib comdlg32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmtd" /pdbtype:sept /ignore:4089 /ignore:4078
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "VMRXcl - Win32 Release"
# Name "VMRXcl - Win32 Debug"
# Name "VMRXcl - Win32 Release Unicode"
# Name "VMRXcl - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AllocPresenter.cpp
# End Source File
# Begin Source File

SOURCE=.\app.cpp
# End Source File
# Begin Source File

SOURCE=.\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dfont.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dtextr.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dutil.cpp
# End Source File
# Begin Source File

SOURCE=.\DDrawSupport.cpp
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdplyer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\app.h
# End Source File
# Begin Source File

SOURCE=.\BltAlpha.h
# End Source File
# Begin Source File

SOURCE=.\d3dfont.h
# End Source File
# Begin Source File

SOURCE=.\d3dtextr.h
# End Source File
# Begin Source File

SOURCE=.\d3dutil.h
# End Source File
# Begin Source File

SOURCE=.\DDrawSupport.h
# End Source File
# Begin Source File

SOURCE=.\project.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\vcdplyer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\VMRXcl.ico
# End Source File
# Begin Source File

SOURCE=.\VMRXcl.rc
# End Source File
# Begin Source File

SOURCE=.\VMRxclMenu.bmp
# End Source File
# End Group
# End Target
# End Project
