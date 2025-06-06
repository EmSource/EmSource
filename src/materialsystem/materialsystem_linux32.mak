ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=materialsystem
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
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=materialsystem -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DDEFINE_MATERIALSYSTEM_INTERFACE -DMATERIALSYSTEM_EXPORTS -DPROTECTED_THINGS_ENABLE -Dstrncpy=use_Q_strncpy_instead -D_snprintf=use_Q_snprintf_instead -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/materialsystem -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ./ 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/materialsystem.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/materialsystem.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/filesystem_helpers.cpp \
    ../public/tier0/memoverride.cpp \
    CColorCorrection.cpp \
    cmaterial.cpp \
    cmaterialdict.cpp \
    CMaterialSubRect.cpp \
    cmaterialsystem.cpp \
    cmaterialvar.cpp \
    cmaterial_queuefriendly.cpp \
    cmatlightmaps.cpp \
    cmatnullrendercontext.cpp \
    cmatqueuedrendercontext.cpp \
    cmatrendercontext.cpp \
    colorspace.cpp \
    ctexture.cpp \
    ctexturecompositor.cpp \
    imagepacker.cpp \
    materialsystem_global.cpp \
    mat_stub.cpp \
    morph.cpp \
    occlusionquerymgr.cpp \
    pch_materialsystem.cpp \
    shadersystem.cpp \
    texturemanager.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/shaderlib.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vtf.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/shaderlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vtf.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../public/filesystem_helpers.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CColorCorrection.P
endif

$(OBJ_DIR)/CColorCorrection.o : $(abspath CColorCorrection.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterial.P
endif

$(OBJ_DIR)/cmaterial.o : $(abspath cmaterial.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterialdict.P
endif

$(OBJ_DIR)/cmaterialdict.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmaterialdict.o : $(abspath cmaterialdict.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CMaterialSubRect.P
endif

$(OBJ_DIR)/CMaterialSubRect.o : $(abspath CMaterialSubRect.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterialsystem.P
endif

$(OBJ_DIR)/cmaterialsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmaterialsystem.o : $(abspath cmaterialsystem.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterialvar.P
endif

$(OBJ_DIR)/cmaterialvar.o : $(abspath cmaterialvar.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterial_queuefriendly.P
endif

$(OBJ_DIR)/cmaterial_queuefriendly.o : $(abspath cmaterial_queuefriendly.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmatlightmaps.P
endif

$(OBJ_DIR)/cmatlightmaps.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmatlightmaps.o : $(abspath cmatlightmaps.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmatnullrendercontext.P
endif

$(OBJ_DIR)/cmatnullrendercontext.o : $(abspath cmatnullrendercontext.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmatqueuedrendercontext.P
endif

$(OBJ_DIR)/cmatqueuedrendercontext.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmatqueuedrendercontext.o : $(abspath cmatqueuedrendercontext.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmatrendercontext.P
endif

$(OBJ_DIR)/cmatrendercontext.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmatrendercontext.o : $(abspath cmatrendercontext.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorspace.P
endif

$(OBJ_DIR)/colorspace.o : $(abspath colorspace.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ctexture.P
endif

$(OBJ_DIR)/ctexture.o : $(abspath ctexture.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ctexturecompositor.P
endif

$(OBJ_DIR)/ctexturecompositor.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/ctexturecompositor.o : $(abspath ctexturecompositor.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/imagepacker.P
endif

$(OBJ_DIR)/imagepacker.o : $(abspath imagepacker.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/materialsystem_global.P
endif

$(OBJ_DIR)/materialsystem_global.o : $(abspath materialsystem_global.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mat_stub.P
endif

$(OBJ_DIR)/mat_stub.o : $(abspath mat_stub.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/morph.P
endif

$(OBJ_DIR)/morph.o : $(abspath morph.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/occlusionquerymgr.P
endif

$(OBJ_DIR)/occlusionquerymgr.o : $(abspath occlusionquerymgr.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pch_materialsystem.P
endif

$(OBJ_DIR)/pch_materialsystem.h.gch : pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/pch_materialsystem.h.P : $(OBJ_DIR)/pch_materialsystem.h.gch

vpath pch_materialsystem.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/pch_materialsystem.h.P
endif

$(OBJ_DIR)/pch_materialsystem.h : pch_materialsystem.h $(OBJ_DIR)/pch_materialsystem.h.gch $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/pch_materialsystem.h

$(OBJ_DIR)/pch_materialsystem.o : $(abspath pch_materialsystem.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadersystem.P
endif

$(OBJ_DIR)/shadersystem.o : $(abspath shadersystem.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/texturemanager.P
endif

$(OBJ_DIR)/texturemanager.o : $(abspath texturemanager.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=materialsystem -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DDEFINE_MATERIALSYSTEM_INTERFACE -DMATERIALSYSTEM_EXPORTS -DPROTECTED_THINGS_ENABLE -Dstrncpy=use_Q_strncpy_instead -D_snprintf=use_Q_snprintf_instead -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/materialsystem -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ./ 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/materialsystem.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/materialsystem.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/filesystem_helpers.cpp \
    ../public/tier0/memoverride.cpp \
    CColorCorrection.cpp \
    cmaterial.cpp \
    cmaterialdict.cpp \
    CMaterialSubRect.cpp \
    cmaterialsystem.cpp \
    cmaterialvar.cpp \
    cmaterial_queuefriendly.cpp \
    cmatlightmaps.cpp \
    cmatnullrendercontext.cpp \
    cmatqueuedrendercontext.cpp \
    cmatrendercontext.cpp \
    colorspace.cpp \
    ctexture.cpp \
    ctexturecompositor.cpp \
    imagepacker.cpp \
    materialsystem_global.cpp \
    mat_stub.cpp \
    morph.cpp \
    occlusionquerymgr.cpp \
    pch_materialsystem.cpp \
    shadersystem.cpp \
    texturemanager.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/shaderlib.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vtf.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/shaderlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vtf.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../public/filesystem_helpers.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CColorCorrection.P
endif

$(OBJ_DIR)/CColorCorrection.o : $(abspath CColorCorrection.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterial.P
endif

$(OBJ_DIR)/cmaterial.o : $(abspath cmaterial.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterialdict.P
endif

$(OBJ_DIR)/cmaterialdict.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmaterialdict.o : $(abspath cmaterialdict.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CMaterialSubRect.P
endif

$(OBJ_DIR)/CMaterialSubRect.o : $(abspath CMaterialSubRect.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterialsystem.P
endif

$(OBJ_DIR)/cmaterialsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmaterialsystem.o : $(abspath cmaterialsystem.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterialvar.P
endif

$(OBJ_DIR)/cmaterialvar.o : $(abspath cmaterialvar.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmaterial_queuefriendly.P
endif

$(OBJ_DIR)/cmaterial_queuefriendly.o : $(abspath cmaterial_queuefriendly.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmatlightmaps.P
endif

$(OBJ_DIR)/cmatlightmaps.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmatlightmaps.o : $(abspath cmatlightmaps.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmatnullrendercontext.P
endif

$(OBJ_DIR)/cmatnullrendercontext.o : $(abspath cmatnullrendercontext.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmatqueuedrendercontext.P
endif

$(OBJ_DIR)/cmatqueuedrendercontext.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmatqueuedrendercontext.o : $(abspath cmatqueuedrendercontext.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmatrendercontext.P
endif

$(OBJ_DIR)/cmatrendercontext.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/cmatrendercontext.o : $(abspath cmatrendercontext.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorspace.P
endif

$(OBJ_DIR)/colorspace.o : $(abspath colorspace.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ctexture.P
endif

$(OBJ_DIR)/ctexture.o : $(abspath ctexture.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ctexturecompositor.P
endif

$(OBJ_DIR)/ctexturecompositor.o : TARGET_PCH_FILE = $(OBJ_DIR)/pch_materialsystem.h
$(OBJ_DIR)/ctexturecompositor.o : $(abspath ctexturecompositor.cpp) $(OBJ_DIR)/pch_materialsystem.h.gch $(OBJ_DIR)/pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/imagepacker.P
endif

$(OBJ_DIR)/imagepacker.o : $(abspath imagepacker.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/materialsystem_global.P
endif

$(OBJ_DIR)/materialsystem_global.o : $(abspath materialsystem_global.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mat_stub.P
endif

$(OBJ_DIR)/mat_stub.o : $(abspath mat_stub.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/morph.P
endif

$(OBJ_DIR)/morph.o : $(abspath morph.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/occlusionquerymgr.P
endif

$(OBJ_DIR)/occlusionquerymgr.o : $(abspath occlusionquerymgr.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pch_materialsystem.P
endif

$(OBJ_DIR)/pch_materialsystem.h.gch : pch_materialsystem.h $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/pch_materialsystem.h.P : $(OBJ_DIR)/pch_materialsystem.h.gch

vpath pch_materialsystem.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/pch_materialsystem.h.P
endif

$(OBJ_DIR)/pch_materialsystem.h : pch_materialsystem.h $(OBJ_DIR)/pch_materialsystem.h.gch $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/pch_materialsystem.h

$(OBJ_DIR)/pch_materialsystem.o : $(abspath pch_materialsystem.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadersystem.P
endif

$(OBJ_DIR)/shadersystem.o : $(abspath shadersystem.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/texturemanager.P
endif

$(OBJ_DIR)/texturemanager.o : $(abspath texturemanager.cpp) $(PWD)/materialsystem_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



