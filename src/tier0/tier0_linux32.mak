ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=tier0
SRCROOT=..
TARGET_PLATFORM=linux32
TARGET_PLATFORM_EXT=
USE_VALVE_BINDIR=0
PWD:=$(shell $(TOOL_PATH)pwd)
# If no configuration is specified, "release" will be used.
ifeq "$(CFG)" ""
	CFG = release
endif

#
#
# CFG=debug
#
#

ifeq "$(CFG)" "debug"

GCC_ExtraCompilerFlags=
GCC_ExtraLinkerFlags=
GCC_CustomVersionScript=
EntryPoint=
IgnoreAllDefaultLibraries=no
BufferSecurityCheck=Yes
SymbolVisibility=hidden
TreatWarningsAsErrors=false
OptimizerLevel=$(SAFE_OPTFLAGS_GCC_422)
SystemLibraries=-lrt 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=tier0 -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DTIER0_DLL_EXPORT -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/tier0 -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=../lib/public/linux32/libtier0.so
GAMEOUTPUTFILE=../lib/public/linux32/libtier0.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/libtier0.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/tier0/memoverride.cpp \
    ../tier1/pathmatch.cpp \
    assert_dialog.cpp \
    commandline.cpp \
    cpumonitoring.cpp \
    cpu_usage.cpp \
    dbg.cpp \
    dynfunction.cpp \
    fasttimer.cpp \
    mem.cpp \
    memdbg.cpp \
    memstd.cpp \
    memvalidate.cpp \
    mem_helpers.cpp \
    minidump.cpp \
    pch_tier0.cpp \
    platform_posix.cpp \
    PMELib.cpp \
    pme_posix.cpp \
    progressbar.cpp \
    security.cpp \
    stacktools.cpp \
    systeminformation.cpp \
    thread.cpp \
    threadtools.cpp \
    tier0_strtools.cpp \
    tslist.cpp \
    vcrmode_posix.cpp \
    vprof.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pathmatch.P
endif

$(OBJ_DIR)/pathmatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/pathmatch.o : $(abspath ../tier1/pathmatch.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/assert_dialog.P
endif

$(OBJ_DIR)/assert_dialog.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/assert_dialog.o : $(abspath assert_dialog.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/commandline.P
endif

$(OBJ_DIR)/commandline.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/commandline.o : $(abspath commandline.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cpumonitoring.P
endif

$(OBJ_DIR)/cpumonitoring.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/cpumonitoring.o : $(abspath cpumonitoring.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cpu_usage.P
endif

$(OBJ_DIR)/cpu_usage.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/cpu_usage.o : $(abspath cpu_usage.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dbg.P
endif

$(OBJ_DIR)/dbg.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/dbg.o : $(abspath dbg.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dynfunction.P
endif

$(OBJ_DIR)/dynfunction.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/dynfunction.o : $(abspath dynfunction.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fasttimer.P
endif

$(OBJ_DIR)/fasttimer.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/fasttimer.o : $(abspath fasttimer.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mem.P
endif

$(OBJ_DIR)/mem.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/mem.o : $(abspath mem.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memdbg.P
endif

$(OBJ_DIR)/memdbg.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/memdbg.o : $(abspath memdbg.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memstd.P
endif

$(OBJ_DIR)/memstd.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/memstd.o : $(abspath memstd.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memvalidate.P
endif

$(OBJ_DIR)/memvalidate.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/memvalidate.o : $(abspath memvalidate.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mem_helpers.P
endif

$(OBJ_DIR)/mem_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/mem_helpers.o : $(abspath mem_helpers.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/minidump.P
endif

$(OBJ_DIR)/minidump.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/minidump.o : $(abspath minidump.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pch_tier0.P
endif

$(OBJ_DIR)/pch_tier0.h.gch : pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/pch_tier0.h.P : $(OBJ_DIR)/pch_tier0.h.gch

vpath pch_tier0.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/pch_tier0.h.P
endif

$(OBJ_DIR)/pch_tier0.h : pch_tier0.h $(OBJ_DIR)/pch_tier0.h.gch $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/pch_tier0.h

$(OBJ_DIR)/pch_tier0.o : $(abspath pch_tier0.cpp) $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/platform_posix.P
endif

$(OBJ_DIR)/platform_posix.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/platform_posix.o : $(abspath platform_posix.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PMELib.P
endif

$(OBJ_DIR)/PMELib.o : $(abspath PMELib.cpp) $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pme_posix.P
endif

$(OBJ_DIR)/pme_posix.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/pme_posix.o : $(abspath pme_posix.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/progressbar.P
endif

$(OBJ_DIR)/progressbar.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/progressbar.o : $(abspath progressbar.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/security.P
endif

$(OBJ_DIR)/security.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/security.o : $(abspath security.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stacktools.P
endif

$(OBJ_DIR)/stacktools.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/stacktools.o : $(abspath stacktools.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/systeminformation.P
endif

$(OBJ_DIR)/systeminformation.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/systeminformation.o : $(abspath systeminformation.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/thread.P
endif

$(OBJ_DIR)/thread.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/thread.o : $(abspath thread.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/threadtools.P
endif

$(OBJ_DIR)/threadtools.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/threadtools.o : $(abspath threadtools.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tier0_strtools.P
endif

$(OBJ_DIR)/tier0_strtools.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/tier0_strtools.o : $(abspath tier0_strtools.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tslist.P
endif

$(OBJ_DIR)/tslist.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/tslist.o : $(abspath tslist.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vcrmode_posix.P
endif

$(OBJ_DIR)/vcrmode_posix.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/vcrmode_posix.o : $(abspath vcrmode_posix.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vprof.P
endif

$(OBJ_DIR)/vprof.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/vprof.o : $(abspath vprof.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)


endif # (CFG=debug)



#
#
# CFG=release
#
#

ifeq "$(CFG)" "release"

GCC_ExtraCompilerFlags=
GCC_ExtraLinkerFlags=
GCC_CustomVersionScript=
EntryPoint=
IgnoreAllDefaultLibraries=no
BufferSecurityCheck=Yes
SymbolVisibility=hidden
TreatWarningsAsErrors=false
OptimizerLevel=$(SAFE_OPTFLAGS_GCC_422)
SystemLibraries=-lrt 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=tier0 -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DTIER0_DLL_EXPORT -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/tier0 -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=../lib/public/linux32/libtier0.so
GAMEOUTPUTFILE=../lib/public/linux32/libtier0.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/libtier0.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/tier0/memoverride.cpp \
    ../tier1/pathmatch.cpp \
    assert_dialog.cpp \
    commandline.cpp \
    cpumonitoring.cpp \
    cpu_usage.cpp \
    dbg.cpp \
    dynfunction.cpp \
    fasttimer.cpp \
    mem.cpp \
    memdbg.cpp \
    memstd.cpp \
    memvalidate.cpp \
    mem_helpers.cpp \
    minidump.cpp \
    pch_tier0.cpp \
    platform_posix.cpp \
    PMELib.cpp \
    pme_posix.cpp \
    progressbar.cpp \
    security.cpp \
    stacktools.cpp \
    systeminformation.cpp \
    thread.cpp \
    threadtools.cpp \
    tier0_strtools.cpp \
    tslist.cpp \
    vcrmode_posix.cpp \
    vprof.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pathmatch.P
endif

$(OBJ_DIR)/pathmatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/pathmatch.o : $(abspath ../tier1/pathmatch.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/assert_dialog.P
endif

$(OBJ_DIR)/assert_dialog.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/assert_dialog.o : $(abspath assert_dialog.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/commandline.P
endif

$(OBJ_DIR)/commandline.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/commandline.o : $(abspath commandline.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cpumonitoring.P
endif

$(OBJ_DIR)/cpumonitoring.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/cpumonitoring.o : $(abspath cpumonitoring.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cpu_usage.P
endif

$(OBJ_DIR)/cpu_usage.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/cpu_usage.o : $(abspath cpu_usage.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dbg.P
endif

$(OBJ_DIR)/dbg.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/dbg.o : $(abspath dbg.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dynfunction.P
endif

$(OBJ_DIR)/dynfunction.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/dynfunction.o : $(abspath dynfunction.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fasttimer.P
endif

$(OBJ_DIR)/fasttimer.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/fasttimer.o : $(abspath fasttimer.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mem.P
endif

$(OBJ_DIR)/mem.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/mem.o : $(abspath mem.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memdbg.P
endif

$(OBJ_DIR)/memdbg.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/memdbg.o : $(abspath memdbg.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memstd.P
endif

$(OBJ_DIR)/memstd.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/memstd.o : $(abspath memstd.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memvalidate.P
endif

$(OBJ_DIR)/memvalidate.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/memvalidate.o : $(abspath memvalidate.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mem_helpers.P
endif

$(OBJ_DIR)/mem_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/mem_helpers.o : $(abspath mem_helpers.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/minidump.P
endif

$(OBJ_DIR)/minidump.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/minidump.o : $(abspath minidump.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pch_tier0.P
endif

$(OBJ_DIR)/pch_tier0.h.gch : pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/pch_tier0.h.P : $(OBJ_DIR)/pch_tier0.h.gch

vpath pch_tier0.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/pch_tier0.h.P
endif

$(OBJ_DIR)/pch_tier0.h : pch_tier0.h $(OBJ_DIR)/pch_tier0.h.gch $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/pch_tier0.h

$(OBJ_DIR)/pch_tier0.o : $(abspath pch_tier0.cpp) $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/platform_posix.P
endif

$(OBJ_DIR)/platform_posix.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/platform_posix.o : $(abspath platform_posix.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PMELib.P
endif

$(OBJ_DIR)/PMELib.o : $(abspath PMELib.cpp) $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pme_posix.P
endif

$(OBJ_DIR)/pme_posix.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/pme_posix.o : $(abspath pme_posix.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/progressbar.P
endif

$(OBJ_DIR)/progressbar.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/progressbar.o : $(abspath progressbar.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/security.P
endif

$(OBJ_DIR)/security.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/security.o : $(abspath security.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stacktools.P
endif

$(OBJ_DIR)/stacktools.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/stacktools.o : $(abspath stacktools.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/systeminformation.P
endif

$(OBJ_DIR)/systeminformation.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/systeminformation.o : $(abspath systeminformation.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/thread.P
endif

$(OBJ_DIR)/thread.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/thread.o : $(abspath thread.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/threadtools.P
endif

$(OBJ_DIR)/threadtools.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/threadtools.o : $(abspath threadtools.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tier0_strtools.P
endif

$(OBJ_DIR)/tier0_strtools.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/tier0_strtools.o : $(abspath tier0_strtools.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tslist.P
endif

$(OBJ_DIR)/tslist.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/tslist.o : $(abspath tslist.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vcrmode_posix.P
endif

$(OBJ_DIR)/vcrmode_posix.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/vcrmode_posix.o : $(abspath vcrmode_posix.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vprof.P
endif

$(OBJ_DIR)/vprof.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_tier0.h
$(OBJ_DIR)/vprof.o : $(abspath vprof.cpp) $(OBJ_DIR)/pch_tier0.h.gch $(OBJ_DIR)/pch_tier0.h $(PWD)/tier0_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)


endif # (CFG=release)



