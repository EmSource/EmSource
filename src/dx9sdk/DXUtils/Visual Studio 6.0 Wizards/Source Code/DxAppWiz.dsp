# Microsoft Developer Studio Project File - Name="DxAppWiz" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DxAppWiz - Win32 Pseudo-Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DxAppWiz.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DxAppWiz.mak" CFG="DxAppWiz - Win32 Pseudo-Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DxAppWiz - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DxAppWiz - Win32 Pseudo-Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DxAppWiz - Win32 export" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "awx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Ext "awx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"Release/DxAppWiz.awx"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Release
TargetPath=.\Release\DxAppWiz.awx
TargetName=DxAppWiz
InputPath=.\Release\DxAppWiz.awx
SOURCE="$(InputPath)"

BuildCmds= \
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" \
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" \
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" \
	

"$(MSDEVDIR)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

# End Custom Build

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "awx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Ext "awx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386 /out:"Debug/DxAppWiz.awx"
# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\Debug
TargetPath=.\Debug\DxAppWiz.awx
TargetName=DxAppWiz
InputPath=.\Debug\DxAppWiz.awx
SOURCE="$(InputPath)"

"$(MSDEVDIR)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DxAppWiz___Win32_export"
# PROP BASE Intermediate_Dir "DxAppWiz___Win32_export"
# PROP BASE Target_Ext "awx"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "DxAppWiz___Win32_export"
# PROP Intermediate_Dir "DxAppWiz___Win32_export"
# PROP Target_Ext "awx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_PSEUDO_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_PSEUDO_DEBUG" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_PSEUDO_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386 /out:"Debug/DxAppWiz.awx"
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /debug /machine:I386 /out:"Debug/DxAppWiz.awx"
# Begin Custom Build - Copying custom AppWizard to Template directory...
OutDir=.\DxAppWiz___Win32_export
TargetPath=.\Debug\DxAppWiz.awx
TargetName=DxAppWiz
InputPath=.\Debug\DxAppWiz.awx
SOURCE="$(InputPath)"

"$(MSDEVDIR)\Template\$(TargetName).awx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if not exist "$(MSDEVDIR)\Template\nul" md "$(MSDEVDIR)\Template" 
	copy "$(TargetPath)" "$(MSDEVDIR)\Template" 
	if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb" "$(MSDEVDIR)\Template" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "DxAppWiz - Win32 Release"
# Name "DxAppWiz - Win32 Pseudo-Debug"
# Name "DxAppWiz - Win32 export"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Chooser.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm1Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm2Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm3Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm4Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm5Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm6Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm7Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cstm8Dlg.cpp
# End Source File
# Begin Source File

SOURCE=..\DxApp\d3d_dlg\d3d_dlg.cpp

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\d3d_dlg\d3d_dlg.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\DxApp\d3d_dlg\d3d_dlgStdafx.cpp

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Debug.cpp
# End Source File
# Begin Source File

SOURCE=.\DXAw.cpp
# End Source File
# Begin Source File

SOURCE=.\DxAppWiz.cpp
# End Source File
# Begin Source File

SOURCE=.\DxAppWiz.rc
# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlg.cpp

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlg.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlgDlg.cpp

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlgStdAfx.cpp

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_win\gdi_win.cpp

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_win\gdi_win.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Chooser.h
# End Source File
# Begin Source File

SOURCE=.\Cstm1Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm2Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm3Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm4Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm5Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm6Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm7Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Cstm8Dlg.h
# End Source File
# Begin Source File

SOURCE=..\DxApp\d3d_dlg\d3d_dlg.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\d3d_dlg\d3d_dlgres.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\d3d_dlg\d3d_dlgStdafx.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\d3d_win\d3d_winres.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Debug.h
# End Source File
# Begin Source File

SOURCE=.\DXAw.h
# End Source File
# Begin Source File

SOURCE=.\DxAppWiz.h
# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlg.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlgDlg.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlgres.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlgStdAfx.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_win\gdi_winres.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\DxApp\resource.h

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\backgro.bmp
# End Source File
# Begin Source File

SOURCE=.\blank.BMP
# End Source File
# Begin Source File

SOURCE=.\c.bmp
# End Source File
# Begin Source File

SOURCE=..\DxApp\directx.ico
# End Source File
# Begin Source File

SOURCE=".\dlg-bla.bmp"
# End Source File
# Begin Source File

SOURCE=".\dlg-gdi.bmp"
# End Source File
# Begin Source File

SOURCE=".\dlg-tea.bmp"
# End Source File
# Begin Source File

SOURCE=".\dlg-tri.bmp"
# End Source File
# Begin Source File

SOURCE=..\DxApp\gdi_dlg\gdi_dlg.rc2

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gdidlg.bmp
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\teapot.BMP
# End Source File
# Begin Source File

SOURCE=.\triangle.BMP
# End Source File
# Begin Source File

SOURCE=".\win-bla.BMP"
# End Source File
# Begin Source File

SOURCE=".\win-gdi.bmp"
# End Source File
# Begin Source File

SOURCE=".\win-tea.BMP"
# End Source File
# Begin Source File

SOURCE=".\win-tri.BMP"
# End Source File
# End Group
# Begin Group "Template Files"

# PROP Default_Filter "<templates>"
# Begin Source File

SOURCE=.\Template\bounce.wav
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\confirm.inf
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3d_dlg\d3d_dlg.cpp
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\d3d_dlg\d3d_dlg.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\d3d_dlg\d3d_dlg.rc
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\d3d_dlg\d3d_dlgres.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\d3d_dlg\d3d_dlgStdafx.cpp
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\d3d_dlg\d3d_dlgStdafx.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\d3d_win\d3d_win.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3d_win\d3d_win.rc
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3d_win\d3d_winres.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\d3dapp.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3dapp.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3dfile.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3dfile.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3dfont.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3dfont.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3dutil.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\d3dutil.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\DirectX.ico
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\diutil.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\diutil.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\dmutil.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\dmutil.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\dsutil.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\dsutil.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\dxutil.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\dxutil.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlg.cpp
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlg.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlg.rc
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlg.rc2
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlgDlg.cpp
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlgDlg.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlgres.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlgStdAfx.cpp
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_dlg\gdi_dlgStdAfx.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_win\gdi_win.cpp
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_win\gdi_win.rc
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\gdi_win\gdi_winres.h
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "DxAppWiz - Win32 Release"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 Pseudo-Debug"

!ELSEIF  "$(CFG)" == "DxAppWiz - Win32 export"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Template\netclient.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\netclient.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\netclientres.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\netconnect.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\netconnect.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\netconnectres.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\netvoice.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\netvoice.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\netvoiceres.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Template\newproj.inf
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=..\DxApp\DxApp.dsp
# End Source File
# Begin Source File

SOURCE=..\DxApp\DxApp.dsw
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
