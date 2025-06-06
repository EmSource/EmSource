ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=vaudio_speex
SRCROOT=../../..
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
DLL_EXT=.wasm
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=vaudio_speex -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DSPEEX_EXPORTS -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/engine/voice_codecs/speex -D_DLL_EXT=.wasm -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../../../common ../../../public ../../../public/tier0 ../../../public/tier1 ../../../thirdparty/SDL2 ../frame_encoder ../../../public ../../../public/tier1 ../.. ../../../common ./source/libspeex ../../audio/public 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../../lib/public/linux32/vaudio_speex.wasm
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/vaudio_speex.wasm


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../../public/tier0/memoverride.cpp \
    ../../../tier1/interface.cpp \
    ../frame_encoder/voice_codec_frame.cpp \
    VoiceEncoder_Speex.cpp \


LIBFILES = \
    ../../../lib/public/linux32/tier1.a \
    ../../../lib/common/linux32/libspeex.a \
    -L../../../lib/public/linux32 -ltier0 \
    -L../../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../../lib/common/linux32/libspeex.a \
    ../../../lib/public/linux32/libtier0.so \
    ../../../lib/public/linux32/libvstdlib.so \
    ../../../lib/public/linux32/tier1.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../../public/tier0/memoverride.cpp) $(PWD)/vaudio_speex_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interface.P
endif

$(OBJ_DIR)/interface.o : $(abspath ../../../tier1/interface.cpp) $(PWD)/vaudio_speex_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_codec_frame.P
endif

$(OBJ_DIR)/voice_codec_frame.o : $(abspath ../frame_encoder/voice_codec_frame.cpp) $(PWD)/vaudio_speex_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/VoiceEncoder_Speex.P
endif

$(OBJ_DIR)/VoiceEncoder_Speex.o : $(abspath VoiceEncoder_Speex.cpp) $(PWD)/vaudio_speex_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
DLL_EXT=.wasm
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=vaudio_speex -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DSPEEX_EXPORTS -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/engine/voice_codecs/speex -D_DLL_EXT=.wasm -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../../../common ../../../public ../../../public/tier0 ../../../public/tier1 ../../../thirdparty/SDL2 ../frame_encoder ../../../public ../../../public/tier1 ../.. ../../../common ./source/libspeex ../../audio/public 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../../lib/public/linux32/vaudio_speex.wasm
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/vaudio_speex.wasm


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../../public/tier0/memoverride.cpp \
    ../../../tier1/interface.cpp \
    ../frame_encoder/voice_codec_frame.cpp \
    VoiceEncoder_Speex.cpp \


LIBFILES = \
    ../../../lib/public/linux32/tier1.a \
    ../../../lib/common/linux32/libspeex.a \
    -L../../../lib/public/linux32 -ltier0 \
    -L../../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../../lib/common/linux32/libspeex.a \
    ../../../lib/public/linux32/libtier0.so \
    ../../../lib/public/linux32/libvstdlib.so \
    ../../../lib/public/linux32/tier1.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../../public/tier0/memoverride.cpp) $(PWD)/vaudio_speex_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interface.P
endif

$(OBJ_DIR)/interface.o : $(abspath ../../../tier1/interface.cpp) $(PWD)/vaudio_speex_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_codec_frame.P
endif

$(OBJ_DIR)/voice_codec_frame.o : $(abspath ../frame_encoder/voice_codec_frame.cpp) $(PWD)/vaudio_speex_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/VoiceEncoder_Speex.P
endif

$(OBJ_DIR)/VoiceEncoder_Speex.o : $(abspath VoiceEncoder_Speex.cpp) $(PWD)/vaudio_speex_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



