ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=vguimatsurface
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
GCC_ExtraLinkerFlags=-L/usr/lib32 -L/usr/lib -L/usr/lib/i386-linux-gnu
GCC_CustomVersionScript=
EntryPoint=
IgnoreAllDefaultLibraries=no
BufferSecurityCheck=Yes
SymbolVisibility=hidden
TreatWarningsAsErrors=false
OptimizerLevel=$(SAFE_OPTFLAGS_GCC_422)
SystemLibraries=-lfontconfig -lfreetype 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=vguimatsurface -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DBENCHMARK -DVGUIMATSURFACE_DLL_EXPORT -DGAMEUI_EXPORTS -DDONT_PROTECT_FILEIO_FUNCTIONS -DPROTECTED_THINGS_ENABLE -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/vguimatsurface -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ./ /usr/include/freetype2/ 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/vguimatsurface.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/vguimatsurface.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/filesystem_helpers.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/vgui_controls/vgui_controls.cpp \
    ../vgui2/src/vgui_key_translation.cpp \
    Clip2D.cpp \
    Cursor.cpp \
    FontTextureCache.cpp \
    Input.cpp \
    MatSystemSurface.cpp \
    TextureDictionary.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/vgui_surfacelib.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lSDL2 \


LIBFILENAMES = \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/libSDL2.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/vgui_surfacelib.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../public/filesystem_helpers.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../public/vgui_controls/vgui_controls.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_key_translation.P
endif

$(OBJ_DIR)/vgui_key_translation.o : $(abspath ../vgui2/src/vgui_key_translation.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Clip2D.P
endif

$(OBJ_DIR)/Clip2D.o : $(abspath Clip2D.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Cursor.P
endif

$(OBJ_DIR)/Cursor.o : $(abspath Cursor.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FontTextureCache.P
endif

$(OBJ_DIR)/FontTextureCache.o : $(abspath FontTextureCache.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Input.P
endif

$(OBJ_DIR)/Input.o : $(abspath Input.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MatSystemSurface.P
endif

$(OBJ_DIR)/MatSystemSurface.o : $(abspath MatSystemSurface.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextureDictionary.P
endif

$(OBJ_DIR)/TextureDictionary.o : $(abspath TextureDictionary.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
GCC_ExtraLinkerFlags=-L/usr/lib32 -L/usr/lib -L/usr/lib/i386-linux-gnu
GCC_CustomVersionScript=
EntryPoint=
IgnoreAllDefaultLibraries=no
BufferSecurityCheck=Yes
SymbolVisibility=hidden
TreatWarningsAsErrors=false
OptimizerLevel=$(SAFE_OPTFLAGS_GCC_422)
SystemLibraries=-lfontconfig -lfreetype 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=vguimatsurface -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DBENCHMARK -DVGUIMATSURFACE_DLL_EXPORT -DGAMEUI_EXPORTS -DDONT_PROTECT_FILEIO_FUNCTIONS -DPROTECTED_THINGS_ENABLE -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/vguimatsurface -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ./ /usr/include/freetype2/ 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/vguimatsurface.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/vguimatsurface.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/filesystem_helpers.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/vgui_controls/vgui_controls.cpp \
    ../vgui2/src/vgui_key_translation.cpp \
    Clip2D.cpp \
    Cursor.cpp \
    FontTextureCache.cpp \
    Input.cpp \
    MatSystemSurface.cpp \
    TextureDictionary.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/vgui_surfacelib.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lSDL2 \


LIBFILENAMES = \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/libSDL2.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/vgui_surfacelib.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../public/filesystem_helpers.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../public/vgui_controls/vgui_controls.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_key_translation.P
endif

$(OBJ_DIR)/vgui_key_translation.o : $(abspath ../vgui2/src/vgui_key_translation.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Clip2D.P
endif

$(OBJ_DIR)/Clip2D.o : $(abspath Clip2D.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Cursor.P
endif

$(OBJ_DIR)/Cursor.o : $(abspath Cursor.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FontTextureCache.P
endif

$(OBJ_DIR)/FontTextureCache.o : $(abspath FontTextureCache.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Input.P
endif

$(OBJ_DIR)/Input.o : $(abspath Input.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MatSystemSurface.P
endif

$(OBJ_DIR)/MatSystemSurface.o : $(abspath MatSystemSurface.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextureDictionary.P
endif

$(OBJ_DIR)/TextureDictionary.o : $(abspath TextureDictionary.cpp) $(PWD)/vguimatsurface_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



