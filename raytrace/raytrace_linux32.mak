ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=raytrace
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
OptimizerLevel=-gdwarf-4 -g2 $(OptimizerLevel_CompilerSpecific)
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/universe/Documents/EmSource/raytrace -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ../utils/common 
CONFTYPE=lib
GAMEOUTPUTFILE=../lib/public/linux32/raytrace.a
TARGETCOPIES=
OUTPUTFILE=raytrace.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    raytrace.cpp \
    trace2.cpp \
    trace3.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_emscripten.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/raytrace.P
endif

$(OBJ_DIR)/raytrace.o : $(abspath raytrace.cpp) $(PWD)/raytrace_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/trace2.P
endif

$(OBJ_DIR)/trace2.o : $(abspath trace2.cpp) $(PWD)/raytrace_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/trace3.P
endif

$(OBJ_DIR)/trace3.o : $(abspath trace3.cpp) $(PWD)/raytrace_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
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
OptimizerLevel=-gdwarf-4 -g2 $(OptimizerLevel_CompilerSpecific)
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/universe/Documents/EmSource/raytrace -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ../utils/common 
CONFTYPE=lib
GAMEOUTPUTFILE=../lib/public/linux32/raytrace.a
TARGETCOPIES=
OUTPUTFILE=raytrace.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    raytrace.cpp \
    trace2.cpp \
    trace3.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_emscripten.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/raytrace.P
endif

$(OBJ_DIR)/raytrace.o : $(abspath raytrace.cpp) $(PWD)/raytrace_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/trace2.P
endif

$(OBJ_DIR)/trace2.o : $(abspath trace2.cpp) $(PWD)/raytrace_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/trace3.P
endif

$(OBJ_DIR)/trace3.o : $(abspath trace3.cpp) $(PWD)/raytrace_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



