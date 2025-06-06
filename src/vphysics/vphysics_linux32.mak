ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=vphysics
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
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=vphysics -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/vphysics -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 . ../ivp/ivp_intern ../ivp/ivp_collision ../ivp/ivp_physics ../ivp/ivp_surface_manager ../ivp/ivp_utility ../ivp/ivp_controller ../ivp/ivp_compact_builder ../ivp/havana/havok ../ivp/havana 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/vphysics.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/vphysics.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/filesystem_helpers.cpp \
    ../public/tier0/memoverride.cpp \
    convert.cpp \
    ledgewriter.cpp \
    main.cpp \
    physics_airboat.cpp \
    physics_collide.cpp \
    physics_constraint.cpp \
    physics_controller_raycast_vehicle.cpp \
    physics_environment.cpp \
    physics_fluid.cpp \
    physics_friction.cpp \
    physics_material.cpp \
    physics_motioncontroller.cpp \
    physics_object.cpp \
    physics_shadow.cpp \
    physics_spring.cpp \
    physics_vehicle.cpp \
    physics_virtualmesh.cpp \
    stdafx.cpp \
    trace.cpp \
    vcollide_parse.cpp \
    vphysics_saverestore.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/common/linux32/havana_constraints.a \
    ../lib/common/linux32/hk_base.a \
    ../lib/common/linux32/hk_math.a \
    ../lib/common/linux32/ivp_compactbuilder.a \
    ../lib/common/linux32/ivp_physics.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier2.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../lib/common/linux32/havana_constraints.a \
    ../lib/common/linux32/hk_base.a \
    ../lib/common/linux32/hk_math.a \
    ../lib/common/linux32/ivp_compactbuilder.a \
    ../lib/common/linux32/ivp_physics.a \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../public/filesystem_helpers.cpp) $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/convert.P
endif

$(OBJ_DIR)/convert.o : $(abspath convert.cpp) $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ledgewriter.P
endif

$(OBJ_DIR)/ledgewriter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ledgewriter.o : $(abspath ledgewriter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/main.P
endif

$(OBJ_DIR)/main.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/main.o : $(abspath main.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_airboat.P
endif

$(OBJ_DIR)/physics_airboat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_airboat.o : $(abspath physics_airboat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_collide.P
endif

$(OBJ_DIR)/physics_collide.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_collide.o : $(abspath physics_collide.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_constraint.P
endif

$(OBJ_DIR)/physics_constraint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_constraint.o : $(abspath physics_constraint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_controller_raycast_vehicle.P
endif

$(OBJ_DIR)/physics_controller_raycast_vehicle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_controller_raycast_vehicle.o : $(abspath physics_controller_raycast_vehicle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_environment.P
endif

$(OBJ_DIR)/physics_environment.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_environment.o : $(abspath physics_environment.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_fluid.P
endif

$(OBJ_DIR)/physics_fluid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_fluid.o : $(abspath physics_fluid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_friction.P
endif

$(OBJ_DIR)/physics_friction.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_friction.o : $(abspath physics_friction.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_material.P
endif

$(OBJ_DIR)/physics_material.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_material.o : $(abspath physics_material.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_motioncontroller.P
endif

$(OBJ_DIR)/physics_motioncontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_motioncontroller.o : $(abspath physics_motioncontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_object.P
endif

$(OBJ_DIR)/physics_object.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_object.o : $(abspath physics_object.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_shadow.P
endif

$(OBJ_DIR)/physics_shadow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_shadow.o : $(abspath physics_shadow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_spring.P
endif

$(OBJ_DIR)/physics_spring.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_spring.o : $(abspath physics_spring.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_vehicle.P
endif

$(OBJ_DIR)/physics_vehicle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_vehicle.o : $(abspath physics_vehicle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_virtualmesh.P
endif

$(OBJ_DIR)/physics_virtualmesh.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_virtualmesh.o : $(abspath physics_virtualmesh.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stdafx.P
endif

$(OBJ_DIR)/cbase.h.gch : cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/cbase.h.P : $(OBJ_DIR)/cbase.h.gch

vpath cbase.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/cbase.h.P
endif

$(OBJ_DIR)/cbase.h : cbase.h $(OBJ_DIR)/cbase.h.gch $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/cbase.h

$(OBJ_DIR)/stdafx.o : $(abspath stdafx.cpp) $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/trace.P
endif

$(OBJ_DIR)/trace.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/trace.o : $(abspath trace.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vcollide_parse.P
endif

$(OBJ_DIR)/vcollide_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vcollide_parse.o : $(abspath vcollide_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vphysics_saverestore.P
endif

$(OBJ_DIR)/vphysics_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vphysics_saverestore.o : $(abspath vphysics_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
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
OptimizerLevel=$(SAFE_OPTFLAGS_GCC_422)
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=vphysics -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/vphysics -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 . ../ivp/ivp_intern ../ivp/ivp_collision ../ivp/ivp_physics ../ivp/ivp_surface_manager ../ivp/ivp_utility ../ivp/ivp_controller ../ivp/ivp_compact_builder ../ivp/havana/havok ../ivp/havana 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/vphysics.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/vphysics.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../public/filesystem_helpers.cpp \
    ../public/tier0/memoverride.cpp \
    convert.cpp \
    ledgewriter.cpp \
    main.cpp \
    physics_airboat.cpp \
    physics_collide.cpp \
    physics_constraint.cpp \
    physics_controller_raycast_vehicle.cpp \
    physics_environment.cpp \
    physics_fluid.cpp \
    physics_friction.cpp \
    physics_material.cpp \
    physics_motioncontroller.cpp \
    physics_object.cpp \
    physics_shadow.cpp \
    physics_spring.cpp \
    physics_vehicle.cpp \
    physics_virtualmesh.cpp \
    stdafx.cpp \
    trace.cpp \
    vcollide_parse.cpp \
    vphysics_saverestore.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/common/linux32/havana_constraints.a \
    ../lib/common/linux32/hk_base.a \
    ../lib/common/linux32/hk_math.a \
    ../lib/common/linux32/ivp_compactbuilder.a \
    ../lib/common/linux32/ivp_physics.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier2.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../lib/common/linux32/havana_constraints.a \
    ../lib/common/linux32/hk_base.a \
    ../lib/common/linux32/hk_math.a \
    ../lib/common/linux32/ivp_compactbuilder.a \
    ../lib/common/linux32/ivp_physics.a \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../public/filesystem_helpers.cpp) $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/convert.P
endif

$(OBJ_DIR)/convert.o : $(abspath convert.cpp) $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ledgewriter.P
endif

$(OBJ_DIR)/ledgewriter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ledgewriter.o : $(abspath ledgewriter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/main.P
endif

$(OBJ_DIR)/main.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/main.o : $(abspath main.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_airboat.P
endif

$(OBJ_DIR)/physics_airboat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_airboat.o : $(abspath physics_airboat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_collide.P
endif

$(OBJ_DIR)/physics_collide.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_collide.o : $(abspath physics_collide.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_constraint.P
endif

$(OBJ_DIR)/physics_constraint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_constraint.o : $(abspath physics_constraint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_controller_raycast_vehicle.P
endif

$(OBJ_DIR)/physics_controller_raycast_vehicle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_controller_raycast_vehicle.o : $(abspath physics_controller_raycast_vehicle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_environment.P
endif

$(OBJ_DIR)/physics_environment.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_environment.o : $(abspath physics_environment.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_fluid.P
endif

$(OBJ_DIR)/physics_fluid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_fluid.o : $(abspath physics_fluid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_friction.P
endif

$(OBJ_DIR)/physics_friction.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_friction.o : $(abspath physics_friction.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_material.P
endif

$(OBJ_DIR)/physics_material.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_material.o : $(abspath physics_material.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_motioncontroller.P
endif

$(OBJ_DIR)/physics_motioncontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_motioncontroller.o : $(abspath physics_motioncontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_object.P
endif

$(OBJ_DIR)/physics_object.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_object.o : $(abspath physics_object.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_shadow.P
endif

$(OBJ_DIR)/physics_shadow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_shadow.o : $(abspath physics_shadow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_spring.P
endif

$(OBJ_DIR)/physics_spring.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_spring.o : $(abspath physics_spring.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_vehicle.P
endif

$(OBJ_DIR)/physics_vehicle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_vehicle.o : $(abspath physics_vehicle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_virtualmesh.P
endif

$(OBJ_DIR)/physics_virtualmesh.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_virtualmesh.o : $(abspath physics_virtualmesh.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stdafx.P
endif

$(OBJ_DIR)/cbase.h.gch : cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/cbase.h.P : $(OBJ_DIR)/cbase.h.gch

vpath cbase.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/cbase.h.P
endif

$(OBJ_DIR)/cbase.h : cbase.h $(OBJ_DIR)/cbase.h.gch $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/cbase.h

$(OBJ_DIR)/stdafx.o : $(abspath stdafx.cpp) $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/trace.P
endif

$(OBJ_DIR)/trace.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/trace.o : $(abspath trace.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vcollide_parse.P
endif

$(OBJ_DIR)/vcollide_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vcollide_parse.o : $(abspath vcollide_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vphysics_saverestore.P
endif

$(OBJ_DIR)/vphysics_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vphysics_saverestore.o : $(abspath vphysics_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/vphysics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)


endif # (CFG=release)



