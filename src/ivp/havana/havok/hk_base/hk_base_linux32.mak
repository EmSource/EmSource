ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=hk_base
SRCROOT=../../../..
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
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/havana/havok/hk_base -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../../../../common ../../../../public ../../../../public/tier0 ../../../../public/tier1 ../../../../thirdparty/SDL2 ../../../../ivp/havana/havok ../../../../ivp/havana 
CONFTYPE=lib
GAMEOUTPUTFILE=../../../../lib/common/linux32/hk_base.a
TARGETCOPIES=
OUTPUTFILE=hk_base.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    array/array.cpp \
    base_types.cpp \
    console.cpp \
    hash/hash.cpp \
    id_server/id_server.cpp \
    memory/memory.cpp \
    memory/memory_util.cpp \
    stopwatch/stopwatch.cpp \
    string/string.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/array.P
endif

$(OBJ_DIR)/array.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/array.o : $(abspath array/array.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_types.P
endif

$(OBJ_DIR)/base.h.gch : hk_base/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/base.h.P : $(OBJ_DIR)/base.h.gch

vpath hk_base/base.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/base.h.P
endif

$(OBJ_DIR)/base.h : hk_base/base.h $(OBJ_DIR)/base.h.gch $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/base.h

$(OBJ_DIR)/base_types.o : $(abspath base_types.cpp) $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/console.P
endif

$(OBJ_DIR)/console.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/console.o : $(abspath console.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hash.P
endif

$(OBJ_DIR)/hash.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/hash.o : $(abspath hash/hash.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/id_server.P
endif

$(OBJ_DIR)/id_server.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/id_server.o : $(abspath id_server/id_server.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memory.P
endif

$(OBJ_DIR)/memory.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/memory.o : $(abspath memory/memory.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memory_util.P
endif

$(OBJ_DIR)/memory_util.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/memory_util.o : $(abspath memory/memory_util.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stopwatch.P
endif

$(OBJ_DIR)/stopwatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/stopwatch.o : $(abspath stopwatch/stopwatch.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/string.P
endif

$(OBJ_DIR)/string.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/string.o : $(abspath string/string.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
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
OptimizerLevel=-gdwarf-4 -g2 $(OptimizerLevel_CompilerSpecific)
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/havana/havok/hk_base -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../../../../common ../../../../public ../../../../public/tier0 ../../../../public/tier1 ../../../../thirdparty/SDL2 ../../../../ivp/havana/havok ../../../../ivp/havana 
CONFTYPE=lib
GAMEOUTPUTFILE=../../../../lib/common/linux32/hk_base.a
TARGETCOPIES=
OUTPUTFILE=hk_base.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    array/array.cpp \
    base_types.cpp \
    console.cpp \
    hash/hash.cpp \
    id_server/id_server.cpp \
    memory/memory.cpp \
    memory/memory_util.cpp \
    stopwatch/stopwatch.cpp \
    string/string.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/array.P
endif

$(OBJ_DIR)/array.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/array.o : $(abspath array/array.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_types.P
endif

$(OBJ_DIR)/base.h.gch : hk_base/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/base.h.P : $(OBJ_DIR)/base.h.gch

vpath hk_base/base.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/base.h.P
endif

$(OBJ_DIR)/base.h : hk_base/base.h $(OBJ_DIR)/base.h.gch $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/base.h

$(OBJ_DIR)/base_types.o : $(abspath base_types.cpp) $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/console.P
endif

$(OBJ_DIR)/console.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/console.o : $(abspath console.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hash.P
endif

$(OBJ_DIR)/hash.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/hash.o : $(abspath hash/hash.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/id_server.P
endif

$(OBJ_DIR)/id_server.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/id_server.o : $(abspath id_server/id_server.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memory.P
endif

$(OBJ_DIR)/memory.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/memory.o : $(abspath memory/memory.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memory_util.P
endif

$(OBJ_DIR)/memory_util.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/memory_util.o : $(abspath memory/memory_util.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stopwatch.P
endif

$(OBJ_DIR)/stopwatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/stopwatch.o : $(abspath stopwatch/stopwatch.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/string.P
endif

$(OBJ_DIR)/string.o : TARGET_PCH_FILE = $(OBJ_DIR)/base.h
$(OBJ_DIR)/string.o : $(abspath string/string.cpp) $(OBJ_DIR)/base.h.gch $(OBJ_DIR)/base.h $(PWD)/hk_base_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)


endif # (CFG=release)



