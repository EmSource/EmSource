ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=vaudio_celt
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
OptimizerLevel=-gdwarf-4 -g2 $(OptimizerLevel_CompilerSpecific)
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=vaudio_celt -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DCELT_EXPORTS -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/universe/Documents/EmSource/engine/voice_codecs/celt -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../../../common ../../../public ../../../public/tier0 ../../../public/tier1 ../../../thirdparty/SDL2 ../frame_encoder ../celt ../../../public ../../../public/tier1 ../.. ../../../common ./source/libcelt ../../audio/public 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../../../game/bin/vaudio_celt.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/vaudio_celt.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../../public/tier0/memoverride.cpp \
    ../../../tier1/interface.cpp \
    ../frame_encoder/voice_codec_frame.cpp \
    voiceencoder_celt.cpp \


LIBFILES = \
    ../../../lib/public/linux32/tier1.a \
    -L../../../lib/public/linux32 -ltier0 \
    -L../../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../../lib/public/linux32/libtier0.so \
    ../../../lib/public/linux32/libvstdlib.so \
    ../../../lib/public/linux32/tier1.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_emscripten.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../../public/tier0/memoverride.cpp) $(PWD)/vaudio_celt_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interface.P
endif

$(OBJ_DIR)/interface.o : $(abspath ../../../tier1/interface.cpp) $(PWD)/vaudio_celt_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_codec_frame.P
endif

$(OBJ_DIR)/voice_codec_frame.o : $(abspath ../frame_encoder/voice_codec_frame.cpp) $(PWD)/vaudio_celt_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voiceencoder_celt.P
endif

$(OBJ_DIR)/voiceencoder_celt.o : $(abspath voiceencoder_celt.cpp) $(PWD)/vaudio_celt_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
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
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=vaudio_celt -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DCELT_EXPORTS -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/universe/Documents/EmSource/engine/voice_codecs/celt -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../../../common ../../../public ../../../public/tier0 ../../../public/tier1 ../../../thirdparty/SDL2 ../frame_encoder ../celt ../../../public ../../../public/tier1 ../.. ../../../common ./source/libcelt ../../audio/public 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../../../game/bin/vaudio_celt.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/vaudio_celt.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../../public/tier0/memoverride.cpp \
    ../../../tier1/interface.cpp \
    ../frame_encoder/voice_codec_frame.cpp \
    voiceencoder_celt.cpp \


LIBFILES = \
    ../../../lib/public/linux32/tier1.a \
    -L../../../lib/public/linux32 -ltier0 \
    -L../../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../../lib/public/linux32/libtier0.so \
    ../../../lib/public/linux32/libvstdlib.so \
    ../../../lib/public/linux32/tier1.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_emscripten.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../../public/tier0/memoverride.cpp) $(PWD)/vaudio_celt_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interface.P
endif

$(OBJ_DIR)/interface.o : $(abspath ../../../tier1/interface.cpp) $(PWD)/vaudio_celt_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_codec_frame.P
endif

$(OBJ_DIR)/voice_codec_frame.o : $(abspath ../frame_encoder/voice_codec_frame.cpp) $(PWD)/vaudio_celt_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voiceencoder_celt.P
endif

$(OBJ_DIR)/voiceencoder_celt.o : $(abspath voiceencoder_celt.cpp) $(PWD)/vaudio_celt_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



