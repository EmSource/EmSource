# Microsoft Developer Studio Project File - Name="MultiPlayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MultiPlayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MultiPlayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MultiPlayer.mak" CFG="MultiPlayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MultiPlayer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MultiPlayer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MultiPlayer - Win32 Release Unicode" (based on "Win32 (x86) Application")
!MESSAGE "MultiPlayer - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MultiPlayer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\BaseClasses" /I "..\..\inc" /I ".\Release" /I "..\DLL" /I "..\DLL\Release" /I "..\..\..\..\Common\include" /I "..\..\..\..\Common\src" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\BaseClasses\Release\strmbase.lib strmiids.lib ddraw.lib dxguid.lib version.lib winmm.lib comctl32.lib quartz.lib d3dx9.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /machine:I386 /OPT:NOREF /OPT:ICF
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MultiPlayer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\BaseClasses" /I "..\..\inc" /I ".\Debug" /I "..\DLL" /I "..\DLL\Debug" /I "..\..\..\..\Common\include" /I "..\..\..\..\Common\src" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\BaseClasses\Debug\strmbasd.lib strmiids.lib ddraw.lib dxguid.lib version.lib winmm.lib comctl32.lib quartz.lib d3dx9.lib /nologo /stack:0x200000,0x200000 /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "MultiPlayer - Win32 Release Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode"
# PROP Intermediate_Dir "Release_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\BaseClasses" /I "..\..\inc" /I ".\Release" /I "..\DLL" /I "..\DLL\Release" /I "..\..\..\..\Common\include" /I "..\..\..\..\Common\src" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "UNICODE" /D "_UNICODE" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\BaseClasses\Release_Unicode\strmbase.lib strmiids.lib ddraw.lib dxguid.lib version.lib winmm.lib comctl32.lib quartz.lib d3dx9.lib /nologo /stack:0x200000,0x200000 /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /OPT:NOREF /OPT:ICF
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MultiPlayer - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\BaseClasses" /I "..\..\inc" /I ".\Debug" /I "..\DLL" /I "..\DLL\Debug" /I "..\..\..\..\Common\include" /I "..\..\..\..\Common\src" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "UNICODE" /D "_UNICODE" /FR /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\BaseClasses\Debug_Unicode\strmbasd.lib strmiids.lib ddraw.lib dxguid.lib version.lib winmm.lib comctl32.lib quartz.lib d3dx9.lib /nologo /stack:0x200000,0x200000 /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MultiPlayer - Win32 Release"
# Name "MultiPlayer - Win32 Debug"
# Name "MultiPlayer - Win32 Release Unicode"
# Name "MultiPlayer - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MultiGraphSession.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiPlayerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\VMR9Subgraph.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MultiGraphSession.h
# End Source File
# Begin Source File

SOURCE=.\MultiPlayer.h
# End Source File
# Begin Source File

SOURCE=.\MultiPlayerDlg.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\VMR9Subgraph.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Bitmaps\BtnColor.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnColorGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnEnd.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnEndGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnFF.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnFFGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnMinus.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnMinusGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnPause.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnPauseGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnPlay.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnPlayGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnPlus.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnPlusGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnRec.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnRecGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnRW.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnRWGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnScale.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnScaleGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnStart.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnStartGray.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnStop.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmaps\BtnStopGray.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DefaultMultiPlayer.ico
# End Source File
# Begin Source File

SOURCE=.\DefaultMultiPlayer.rc
# End Source File
# Begin Source File

SOURCE=.\res\DefaultMultiPlayer.rc2
# End Source File
# End Group
# End Target
# End Project
