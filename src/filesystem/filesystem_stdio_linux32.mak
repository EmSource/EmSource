ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=filesystem_stdio
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
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=filesystem_stdio -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DFILESYSTEM_STDIO_EXPORTS -DDONT_PROTECT_FILEIO_FUNCTIONS -DPROTECTED_THINGS_ENABLE -D_USE_32BIT_TIME_T -DSUPPORT_PACKED_STORE -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/filesystem -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/filesystem_stdio.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/filesystem_stdio.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/kevvaluescompiler.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/zip_utils.cpp \
    basefilesystem.cpp \
    filesystem_async.cpp \
    filesystem_stdio.cpp \
    filetracker.cpp \
    linux_support.cpp \
    packfile.cpp \
    QueuedLoader.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vpklib.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vpklib.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/kevvaluescompiler.P
endif

$(OBJ_DIR)/kevvaluescompiler.o : $(abspath ../public/kevvaluescompiler.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/zip_utils.P
endif

$(OBJ_DIR)/zip_utils.o : $(abspath ../public/zip_utils.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basefilesystem.P
endif

$(OBJ_DIR)/basefilesystem.o : $(abspath basefilesystem.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_async.P
endif

$(OBJ_DIR)/filesystem_async.o : $(abspath filesystem_async.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_stdio.P
endif

$(OBJ_DIR)/filesystem_stdio.o : $(abspath filesystem_stdio.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filetracker.P
endif

$(OBJ_DIR)/filetracker.o : $(abspath filetracker.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/linux_support.P
endif

$(OBJ_DIR)/linux_support.o : $(abspath linux_support.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/packfile.P
endif

$(OBJ_DIR)/packfile.o : $(abspath packfile.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/QueuedLoader.P
endif

$(OBJ_DIR)/QueuedLoader.o : $(abspath QueuedLoader.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


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
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=filesystem_stdio -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DFILESYSTEM_STDIO_EXPORTS -DDONT_PROTECT_FILEIO_FUNCTIONS -DPROTECTED_THINGS_ENABLE -D_USE_32BIT_TIME_T -DSUPPORT_PACKED_STORE -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/filesystem -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/filesystem_stdio.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/filesystem_stdio.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/kevvaluescompiler.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/zip_utils.cpp \
    basefilesystem.cpp \
    filesystem_async.cpp \
    filesystem_stdio.cpp \
    filetracker.cpp \
    linux_support.cpp \
    packfile.cpp \
    QueuedLoader.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vpklib.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vpklib.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/kevvaluescompiler.P
endif

$(OBJ_DIR)/kevvaluescompiler.o : $(abspath ../public/kevvaluescompiler.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/zip_utils.P
endif

$(OBJ_DIR)/zip_utils.o : $(abspath ../public/zip_utils.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basefilesystem.P
endif

$(OBJ_DIR)/basefilesystem.o : $(abspath basefilesystem.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_async.P
endif

$(OBJ_DIR)/filesystem_async.o : $(abspath filesystem_async.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_stdio.P
endif

$(OBJ_DIR)/filesystem_stdio.o : $(abspath filesystem_stdio.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filetracker.P
endif

$(OBJ_DIR)/filetracker.o : $(abspath filetracker.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/linux_support.P
endif

$(OBJ_DIR)/linux_support.o : $(abspath linux_support.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/packfile.P
endif

$(OBJ_DIR)/packfile.o : $(abspath packfile.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/QueuedLoader.P
endif

$(OBJ_DIR)/QueuedLoader.o : $(abspath QueuedLoader.cpp) $(PWD)/filesystem_stdio_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



