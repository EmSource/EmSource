ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=hk_math
SRCROOT=../../../..
TARGET_PLATFORM=linux32
TARGET_PLATFORM_EXT=
USE_VALVE_BINDIR=0
PWD:=$(shell $(TOOL_PATH)pwd)
# If no configuration is specified, "release" will be used.
ifeq "$(CFG)" ""
	CFG = release
endif

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
ifeq "$(CFG)" "debug"
DEFINES += -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -D_DEBUG -D_LIB -DHK_DEBUG -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/havana/havok/hk_math -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
else
DEFINES += -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/havana/havok/hk_math -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
endif
INCLUDEDIRS += ../../../../common ../../../../public ../../../../public/tier0 ../../../../public/tier1 ../../../../thirdparty/SDL2 ../../../../ivp/havana/havok ../../../../ivp/havana 
CONFTYPE=lib
GAMEOUTPUTFILE=../../../../lib/common/linux32/hk_math.a
TARGETCOPIES=
OUTPUTFILE=hk_math.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    densematrix.cpp \
    densematrix_util.cpp \
    eulerangles.cpp \
    gauss_elimination/gauss_elimination.cpp \
    incr_lu/incr_lu.cpp \
    lcp/lcp_solver.cpp \
    math.cpp \
    matrix3.cpp \
    odesolve.cpp \
    plane.cpp \
    quaternion/quaternion.cpp \
    quaternion/quaternion_util.cpp \
    rotation.cpp \
    spatial_matrix.cpp \
    spatial_vector.cpp \
    transform.cpp \
    vector3/vector3.cpp \
    vector3/vector3_util.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/densematrix.P
endif

$(OBJ_DIR)/vecmath.h.gch : hk_math/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/vecmath.h.P : $(OBJ_DIR)/vecmath.h.gch

vpath hk_math/vecmath.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/vecmath.h.P
endif

$(OBJ_DIR)/vecmath.h : hk_math/vecmath.h $(OBJ_DIR)/vecmath.h.gch $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/vecmath.h

$(OBJ_DIR)/densematrix.o : $(abspath densematrix.cpp) $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/densematrix_util.P
endif

$(OBJ_DIR)/densematrix_util.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/densematrix_util.o : $(abspath densematrix_util.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eulerangles.P
endif

$(OBJ_DIR)/eulerangles.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/eulerangles.o : $(abspath eulerangles.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gauss_elimination.P
endif

$(OBJ_DIR)/gauss_elimination.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/gauss_elimination.o : $(abspath gauss_elimination/gauss_elimination.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/incr_lu.P
endif

$(OBJ_DIR)/incr_lu.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/incr_lu.o : $(abspath incr_lu/incr_lu.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lcp_solver.P
endif

$(OBJ_DIR)/lcp_solver.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/lcp_solver.o : $(abspath lcp/lcp_solver.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/math.P
endif

$(OBJ_DIR)/math.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/math.o : $(abspath math.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matrix3.P
endif

$(OBJ_DIR)/matrix3.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/matrix3.o : $(abspath matrix3.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/odesolve.P
endif

$(OBJ_DIR)/odesolve.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/odesolve.o : $(abspath odesolve.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/plane.P
endif

$(OBJ_DIR)/plane.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/plane.o : $(abspath plane.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/quaternion.P
endif

$(OBJ_DIR)/quaternion.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/quaternion.o : $(abspath quaternion/quaternion.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/quaternion_util.P
endif

$(OBJ_DIR)/quaternion_util.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/quaternion_util.o : $(abspath quaternion/quaternion_util.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rotation.P
endif

$(OBJ_DIR)/rotation.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/rotation.o : $(abspath rotation.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spatial_matrix.P
endif

$(OBJ_DIR)/spatial_matrix.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/spatial_matrix.o : $(abspath spatial_matrix.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spatial_vector.P
endif

$(OBJ_DIR)/spatial_vector.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/spatial_vector.o : $(abspath spatial_vector.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/transform.P
endif

$(OBJ_DIR)/transform.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/transform.o : $(abspath transform.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vector3.P
endif

$(OBJ_DIR)/vector3.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/vector3.o : $(abspath vector3/vector3.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vector3_util.P
endif

$(OBJ_DIR)/vector3_util.o : TARGET_PCH_FILE = $(OBJ_DIR)/vecmath.h
$(OBJ_DIR)/vector3_util.o : $(abspath vector3/vector3_util.cpp) $(OBJ_DIR)/vecmath.h.gch $(OBJ_DIR)/vecmath.h $(PWD)/hk_math_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)
