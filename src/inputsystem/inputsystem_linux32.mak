ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=inputsystem
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
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=inputsystem -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVERSION_SAFE_STEAM_API_INTERFACES -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/inputsystem -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/inputsystem.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/inputsystem.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/tier0/memoverride.cpp \
    inputsystem.cpp \
    joystick_sdl.cpp \
    key_translation.cpp \
    steamcontroller.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lSDL2 \
    -L../lib/public/linux32 -lsteam_api \


LIBFILENAMES = \
    ../lib/public/linux32/libSDL2.so \
    ../lib/public/linux32/libsteam_api.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/inputsystem.P
endif

$(OBJ_DIR)/inputsystem.o : $(abspath inputsystem.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/joystick_sdl.P
endif

$(OBJ_DIR)/joystick_sdl.o : $(abspath joystick_sdl.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/key_translation.P
endif

$(OBJ_DIR)/key_translation.o : $(abspath key_translation.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamcontroller.P
endif

$(OBJ_DIR)/steamcontroller.o : $(abspath steamcontroller.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=inputsystem -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVERSION_SAFE_STEAM_API_INTERFACES -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/inputsystem -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/inputsystem.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/inputsystem.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/tier0/memoverride.cpp \
    inputsystem.cpp \
    joystick_sdl.cpp \
    key_translation.cpp \
    steamcontroller.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lSDL2 \
    -L../lib/public/linux32 -lsteam_api \


LIBFILENAMES = \
    ../lib/public/linux32/libSDL2.so \
    ../lib/public/linux32/libsteam_api.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/inputsystem.P
endif

$(OBJ_DIR)/inputsystem.o : $(abspath inputsystem.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/joystick_sdl.P
endif

$(OBJ_DIR)/joystick_sdl.o : $(abspath joystick_sdl.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/key_translation.P
endif

$(OBJ_DIR)/key_translation.o : $(abspath key_translation.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamcontroller.P
endif

$(OBJ_DIR)/steamcontroller.o : $(abspath steamcontroller.cpp) $(PWD)/inputsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



