ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=vpk
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
GCC_ExtraLinkerFlags=-Wl,--no-as-needed -Wl,--as-needed
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
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DEXENAME=bin\vpk_linux32 -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/universe/Documents/EmSource/utils/vpk -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/emscripten/system/include ../common 
CONFTYPE=exe
GAMEOUTPUTFILE=
TARGETCOPIES=
OUTPUTFILE=../../../game/bin/vpk_linux32


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../common/crypto.cpp \
    ../../public/tier0/memoverride.cpp \
    packtest.cpp \


LIBFILES = \
    ../../lib/public/linux32/vpklib.a \
    ../../lib/common/$(CRYPTOPPDIR)/libcrypto.a \
    ../../lib/common/$(CRYPTOPPDIR)/libcryptopp.a \
    ../../lib/public/linux32/bitmap.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier1.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../lib/common/$(CRYPTOPPDIR)/libcrypto.a \
    ../../lib/common/$(CRYPTOPPDIR)/libcryptopp.a \
    ../../lib/public/linux32/bitmap.a \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/vpklib.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_emscripten.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/crypto.P
endif

$(OBJ_DIR)/crypto.o : $(abspath ../../common/crypto.cpp) $(PWD)/vpk_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/vpk_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/packtest.P
endif

$(OBJ_DIR)/packtest.o : $(abspath packtest.cpp) $(PWD)/vpk_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
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
GCC_ExtraLinkerFlags=-Wl,--no-as-needed -Wl,--as-needed
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
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DEXENAME=bin\vpk_linux32 -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/universe/Documents/EmSource/utils/vpk -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/emscripten/system/include ../common 
CONFTYPE=exe
GAMEOUTPUTFILE=
TARGETCOPIES=
OUTPUTFILE=../../../game/bin/vpk_linux32


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../common/crypto.cpp \
    ../../public/tier0/memoverride.cpp \
    packtest.cpp \


LIBFILES = \
    ../../lib/public/linux32/vpklib.a \
    ../../lib/common/$(CRYPTOPPDIR)/libcrypto.a \
    ../../lib/common/$(CRYPTOPPDIR)/libcryptopp.a \
    ../../lib/public/linux32/bitmap.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier1.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../lib/common/$(CRYPTOPPDIR)/libcrypto.a \
    ../../lib/common/$(CRYPTOPPDIR)/libcryptopp.a \
    ../../lib/public/linux32/bitmap.a \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/vpklib.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_emscripten.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/crypto.P
endif

$(OBJ_DIR)/crypto.o : $(abspath ../../common/crypto.cpp) $(PWD)/vpk_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/vpk_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/packtest.P
endif

$(OBJ_DIR)/packtest.o : $(abspath packtest.cpp) $(PWD)/vpk_linux32.mak $(SRCROOT)/devtools/makefile_base_emscripten.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



