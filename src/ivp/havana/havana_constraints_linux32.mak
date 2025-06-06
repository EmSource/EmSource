ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=havana_constraints
SRCROOT=../..
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
DLL_EXT=.wasm
SYM_EXT=.dbg
FORCEINCLUDES= 
ifeq "$(CFG)" "debug"
DEFINES += -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -DIVP_VERSION_SDK -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/havana -D_DLL_EXT=.wasm -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
else
DEFINES += -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -DIVP_VERSION_SDK -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/havana -D_DLL_EXT=.wasm -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
endif
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 ../../ivp/ivp_intern ../../ivp/ivp_collision ../../ivp/ivp_physics ../../ivp/ivp_surface_manager ../../ivp/ivp_utility ../../ivp/ivp_controller ../../ivp/ivp_compact_builder ../../ivp/havana/havok ../../ivp/havana 
CONFTYPE=lib
GAMEOUTPUTFILE=../../lib/common/linux32/havana_constraints.a
TARGETCOPIES=
OUTPUTFILE=havana_constraints.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../ivp/havana/havok/hk_physics/constraint/ball_socket/ball_socket_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/breakable_constraint/breakable_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/fixed/fixed_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/hinge/hinge_bp_builder.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/hinge/hinge_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/limited_ball_socket/limited_ball_socket_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/local_constraint_system/local_constraint_system.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/prismatic/prismatic_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/pulley/pulley_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/ragdoll/ragdoll_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/ragdoll/ragdoll_constraint_bp_builder.cpp \
    ../../ivp/havana/havok/hk_physics/constraint/stiff_spring/stiff_spring_constraint.cpp \
    ../../ivp/havana/havok/hk_physics/core/rigid_body_core.cpp \
    ../../ivp/havana/havok/hk_physics/effector/rigid_body_binary_effector.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ball_socket_constraint.P
endif

$(OBJ_DIR)/ball_socket_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/ball_socket/ball_socket_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/breakable_constraint.P
endif

$(OBJ_DIR)/breakable_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/breakable_constraint/breakable_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/constraint.P
endif

$(OBJ_DIR)/constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fixed_constraint.P
endif

$(OBJ_DIR)/fixed_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/fixed/fixed_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hinge_bp_builder.P
endif

$(OBJ_DIR)/hinge_bp_builder.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/hinge/hinge_bp_builder.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hinge_constraint.P
endif

$(OBJ_DIR)/hinge_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/hinge/hinge_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/limited_ball_socket_constraint.P
endif

$(OBJ_DIR)/limited_ball_socket_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/limited_ball_socket/limited_ball_socket_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/local_constraint_system.P
endif

$(OBJ_DIR)/local_constraint_system.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/local_constraint_system/local_constraint_system.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/prismatic_constraint.P
endif

$(OBJ_DIR)/prismatic_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/prismatic/prismatic_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pulley_constraint.P
endif

$(OBJ_DIR)/pulley_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/pulley/pulley_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll_constraint.P
endif

$(OBJ_DIR)/ragdoll_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/ragdoll/ragdoll_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll_constraint_bp_builder.P
endif

$(OBJ_DIR)/ragdoll_constraint_bp_builder.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/ragdoll/ragdoll_constraint_bp_builder.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stiff_spring_constraint.P
endif

$(OBJ_DIR)/stiff_spring_constraint.o : $(abspath ../../ivp/havana/havok/hk_physics/constraint/stiff_spring/stiff_spring_constraint.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rigid_body_core.P
endif

$(OBJ_DIR)/rigid_body_core.o : $(abspath ../../ivp/havana/havok/hk_physics/core/rigid_body_core.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rigid_body_binary_effector.P
endif

$(OBJ_DIR)/rigid_body_binary_effector.o : $(abspath ../../ivp/havana/havok/hk_physics/effector/rigid_body_binary_effector.cpp) $(PWD)/havana_constraints_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)
