ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=stdshader_dbg
SRCROOT=../..
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
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=stdshader_dbg -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DSTDSHADER_DBG_DLL_EXPORT -DFAST_MATERIALVAR_ACCESS -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/materialsystem/stdshaders -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../lib/public/linux32/stdshader_dbg.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/stdshader_dbg.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../public/tier0/memoverride.cpp \
    BaseVSShader.cpp \
    debugdepth.cpp \
    DebugDrawEnvmapMask.cpp \
    debugluxel.cpp \
    debugnormalmap.cpp \
    debugtangentspace.cpp \
    fillrate.cpp \


LIBFILES = \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/shaderlib.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/shaderlib.a \
    ../../lib/public/linux32/tier1.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseVSShader.P
endif

$(OBJ_DIR)/BaseVSShader.o : $(abspath BaseVSShader.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugdepth.P
endif

$(OBJ_DIR)/debugdepth.o : $(abspath debugdepth.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DebugDrawEnvmapMask.P
endif

$(OBJ_DIR)/DebugDrawEnvmapMask.o : $(abspath DebugDrawEnvmapMask.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugluxel.P
endif

$(OBJ_DIR)/debugluxel.o : $(abspath debugluxel.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugnormalmap.P
endif

$(OBJ_DIR)/debugnormalmap.o : $(abspath debugnormalmap.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugtangentspace.P
endif

$(OBJ_DIR)/debugtangentspace.o : $(abspath debugtangentspace.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fillrate.P
endif

$(OBJ_DIR)/fillrate.o : $(abspath fillrate.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=stdshader_dbg -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DSTDSHADER_DBG_DLL_EXPORT -DFAST_MATERIALVAR_ACCESS -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/materialsystem/stdshaders -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../lib/public/linux32/stdshader_dbg.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/stdshader_dbg.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../public/tier0/memoverride.cpp \
    BaseVSShader.cpp \
    debugdepth.cpp \
    DebugDrawEnvmapMask.cpp \
    debugluxel.cpp \
    debugnormalmap.cpp \
    debugtangentspace.cpp \
    fillrate.cpp \


LIBFILES = \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/shaderlib.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/shaderlib.a \
    ../../lib/public/linux32/tier1.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseVSShader.P
endif

$(OBJ_DIR)/BaseVSShader.o : $(abspath BaseVSShader.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugdepth.P
endif

$(OBJ_DIR)/debugdepth.o : $(abspath debugdepth.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DebugDrawEnvmapMask.P
endif

$(OBJ_DIR)/DebugDrawEnvmapMask.o : $(abspath DebugDrawEnvmapMask.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugluxel.P
endif

$(OBJ_DIR)/debugluxel.o : $(abspath debugluxel.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugnormalmap.P
endif

$(OBJ_DIR)/debugnormalmap.o : $(abspath debugnormalmap.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugtangentspace.P
endif

$(OBJ_DIR)/debugtangentspace.o : $(abspath debugtangentspace.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fillrate.P
endif

$(OBJ_DIR)/fillrate.o : $(abspath fillrate.cpp) $(PWD)/stdshader_dbg_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



