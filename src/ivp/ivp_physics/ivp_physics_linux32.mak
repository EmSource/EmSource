ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=ivp_physics
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
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
ifeq "$(CFG)" "debug"
DEFINES += -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DDEBUG -DVPHYSICS_EXPORTS -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -DIVP_VERSION_SDK -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/ivp_physics -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
else
DEFINES += -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVPHYSICS_EXPORTS -DIVP_VERSION_SDK -DHAVANA_CONSTRAINTS -DHAVOK_MOPP -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/ivp_physics -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
endif
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 ../../ivp/ivp_intern ../../ivp/ivp_collision ../../ivp/ivp_physics ../../ivp/ivp_surface_manager ../../ivp/ivp_utility ../../ivp/ivp_controller ../../ivp/ivp_compact_builder ../../ivp/havana/havok ../../ivp/havana 
CONFTYPE=lib
GAMEOUTPUTFILE=../../lib/common/linux32/ivp_physics.a
TARGETCOPIES=
OUTPUTFILE=ivp_physics.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../ivp/ivp_collision/ivp_3d_solver.cxx \
    ../../ivp/ivp_collision/ivp_clustering_longrange.cxx \
    ../../ivp/ivp_collision/ivp_clustering_lrange_hash.cxx \
    ../../ivp/ivp_collision/ivp_clustering_visualizer.cxx \
    ../../ivp/ivp_collision/ivp_clustering_visual_hash.cxx \
    ../../ivp/ivp_collision/ivp_collision_filter.cxx \
    ../../ivp/ivp_collision/ivp_coll_del_root_mindist.cxx \
    ../../ivp/ivp_collision/ivp_compact_ledge.cxx \
    ../../ivp/ivp_collision/ivp_compact_ledge_solver.cxx \
    ../../ivp/ivp_collision/ivp_i_collision_vhash.cxx \
    ../../ivp/ivp_collision/ivp_mindist.cxx \
    ../../ivp/ivp_collision/ivp_mindist_debug.cxx \
    ../../ivp/ivp_collision/ivp_mindist_event.cxx \
    ../../ivp/ivp_collision/ivp_mindist_mcases.cxx \
    ../../ivp/ivp_collision/ivp_mindist_minimize.cxx \
    ../../ivp/ivp_collision/ivp_mindist_recursive.cxx \
    ../../ivp/ivp_collision/ivp_oo_watcher.cxx \
    ../../ivp/ivp_collision/ivp_range_manager.cxx \
    ../../ivp/ivp_collision/ivp_ray_solver.cxx \
    ../../ivp/ivp_controller/ivp_actuator.cxx \
    ../../ivp/ivp_controller/ivp_actuator_spring.cxx \
    ../../ivp/ivp_controller/ivp_buoyancy_solver.cxx \
    ../../ivp/ivp_controller/ivp_car_system.cxx \
    ../../ivp/ivp_controller/ivp_constraint.cxx \
    ../../ivp/ivp_controller/ivp_constraint_car.cxx \
    ../../ivp/ivp_controller/ivp_constraint_fixed_keyed.cxx \
    ../../ivp/ivp_controller/ivp_constraint_local.cxx \
    ../../ivp/ivp_controller/ivp_controller_airboat.cpp \
    ../../ivp/ivp_controller/ivp_controller_buoyancy.cxx \
    ../../ivp/ivp_controller/ivp_controller_floating.cxx \
    ../../ivp/ivp_controller/ivp_controller_motion.cxx \
    ../../ivp/ivp_controller/ivp_controller_raycast_car.cxx \
    ../../ivp/ivp_controller/ivp_controller_stiff_spring.cxx \
    ../../ivp/ivp_controller/ivp_controller_world_frict.cxx \
    ../../ivp/ivp_controller/ivp_forcefield.cxx \
    ../../ivp/ivp_controller/ivp_multidimensional_interp.cxx \
    ../../ivp/ivp_controller/ivp_template_constraint.cxx \
    ../../ivp/ivp_intern/ivp_ball.cxx \
    ../../ivp/ivp_intern/ivp_calc_next_psi_solver.cxx \
    ../../ivp/ivp_intern/ivp_controller_phantom.cxx \
    ../../ivp/ivp_intern/ivp_core.cxx \
    ../../ivp/ivp_intern/ivp_environment.cxx \
    ../../ivp/ivp_intern/ivp_friction.cxx \
    ../../ivp/ivp_intern/ivp_friction_gaps.cxx \
    ../../ivp/ivp_intern/ivp_great_matrix.cxx \
    ../../ivp/ivp_intern/ivp_hull_manager.cxx \
    ../../ivp/ivp_intern/ivp_impact.cxx \
    ../../ivp/ivp_intern/ivp_i_friction_hash.cxx \
    ../../ivp/ivp_intern/ivp_i_object_vhash.cxx \
    ../../ivp/ivp_intern/ivp_merge_core.cxx \
    ../../ivp/ivp_intern/ivp_mindist_friction.cxx \
    ../../ivp/ivp_intern/ivp_object.cxx \
    ../../ivp/ivp_intern/ivp_object_attach.cxx \
    ../../ivp/ivp_intern/ivp_physic.cxx \
    ../../ivp/ivp_intern/ivp_physic_private.cxx \
    ../../ivp/ivp_intern/ivp_polygon.cxx \
    ../../ivp/ivp_intern/ivp_sim_unit.cxx \
    ../../ivp/ivp_intern/ivp_solver_core_reaction.cxx \
    ../../ivp/ivp_intern/ivp_time.cxx \
    ../../ivp/ivp_physics/ivp_anomaly_manager.cxx \
    ../../ivp/ivp_physics/ivp_betterdebugmanager.cxx \
    ../../ivp/ivp_physics/ivp_betterstatisticsmanager.cxx \
    ../../ivp/ivp_physics/ivp_cache_object.cxx \
    ../../ivp/ivp_physics/ivp_liquid_surface_descript.cxx \
    ../../ivp/ivp_physics/ivp_material.cxx \
    ../../ivp/ivp_physics/ivp_performancecounter.cxx \
    ../../ivp/ivp_physics/ivp_stat_manager_cback_con.cxx \
    ../../ivp/ivp_physics/ivp_surface_manager.cxx \
    ../../ivp/ivp_physics/ivp_templates.cxx \
    ../../ivp/ivp_surface_manager/ivp_compact_surface.cxx \
    ../../ivp/ivp_surface_manager/ivp_gridbuild_array.cxx \
    ../../ivp/ivp_surface_manager/ivp_surman_grid.cxx \
    ../../ivp/ivp_surface_manager/ivp_surman_polygon.cxx \
    ../../ivp/ivp_utility/ivu_active_value.cxx \
    ../../ivp/ivp_utility/ivu_bigvector.cxx \
    ../../ivp/ivp_utility/ivu_geometry.cxx \
    ../../ivp/ivp_utility/ivu_hash.cxx \
    ../../ivp/ivp_utility/ivu_linear.cxx \
    ../../ivp/ivp_utility/ivu_memory.cxx \
    ../../ivp/ivp_utility/ivu_min_hash.cxx \
    ../../ivp/ivp_utility/ivu_min_list.cxx \
    ../../ivp/ivp_utility/ivu_os_dep.cxx \
    ../../ivp/ivp_utility/ivu_quat.cxx \
    ../../ivp/ivp_utility/ivu_string.cxx \
    ../../ivp/ivp_utility/ivu_types.cxx \
    ../../ivp/ivp_utility/ivu_vector.cxx \
    ../../ivp/ivp_utility/ivu_vhash.cxx \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_3d_solver.P
endif

$(OBJ_DIR)/ivp_3d_solver.o : $(abspath ../../ivp/ivp_collision/ivp_3d_solver.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_clustering_longrange.P
endif

$(OBJ_DIR)/ivp_clustering_longrange.o : $(abspath ../../ivp/ivp_collision/ivp_clustering_longrange.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_clustering_lrange_hash.P
endif

$(OBJ_DIR)/ivp_clustering_lrange_hash.o : $(abspath ../../ivp/ivp_collision/ivp_clustering_lrange_hash.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_clustering_visualizer.P
endif

$(OBJ_DIR)/ivp_clustering_visualizer.o : $(abspath ../../ivp/ivp_collision/ivp_clustering_visualizer.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_clustering_visual_hash.P
endif

$(OBJ_DIR)/ivp_clustering_visual_hash.o : $(abspath ../../ivp/ivp_collision/ivp_clustering_visual_hash.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_collision_filter.P
endif

$(OBJ_DIR)/ivp_collision_filter.o : $(abspath ../../ivp/ivp_collision/ivp_collision_filter.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_coll_del_root_mindist.P
endif

$(OBJ_DIR)/ivp_coll_del_root_mindist.o : $(abspath ../../ivp/ivp_collision/ivp_coll_del_root_mindist.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_compact_ledge.P
endif

$(OBJ_DIR)/ivp_compact_ledge.o : $(abspath ../../ivp/ivp_collision/ivp_compact_ledge.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_compact_ledge_solver.P
endif

$(OBJ_DIR)/ivp_compact_ledge_solver.o : $(abspath ../../ivp/ivp_collision/ivp_compact_ledge_solver.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_i_collision_vhash.P
endif

$(OBJ_DIR)/ivp_i_collision_vhash.o : $(abspath ../../ivp/ivp_collision/ivp_i_collision_vhash.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_mindist.P
endif

$(OBJ_DIR)/ivp_mindist.o : $(abspath ../../ivp/ivp_collision/ivp_mindist.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_mindist_debug.P
endif

$(OBJ_DIR)/ivp_mindist_debug.o : $(abspath ../../ivp/ivp_collision/ivp_mindist_debug.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_mindist_event.P
endif

$(OBJ_DIR)/ivp_mindist_event.o : $(abspath ../../ivp/ivp_collision/ivp_mindist_event.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_mindist_mcases.P
endif

$(OBJ_DIR)/ivp_mindist_mcases.o : $(abspath ../../ivp/ivp_collision/ivp_mindist_mcases.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_mindist_minimize.P
endif

$(OBJ_DIR)/ivp_mindist_minimize.o : $(abspath ../../ivp/ivp_collision/ivp_mindist_minimize.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_mindist_recursive.P
endif

$(OBJ_DIR)/ivp_mindist_recursive.o : $(abspath ../../ivp/ivp_collision/ivp_mindist_recursive.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_oo_watcher.P
endif

$(OBJ_DIR)/ivp_oo_watcher.o : $(abspath ../../ivp/ivp_collision/ivp_oo_watcher.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_range_manager.P
endif

$(OBJ_DIR)/ivp_range_manager.o : $(abspath ../../ivp/ivp_collision/ivp_range_manager.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_ray_solver.P
endif

$(OBJ_DIR)/ivp_ray_solver.o : $(abspath ../../ivp/ivp_collision/ivp_ray_solver.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_actuator.P
endif

$(OBJ_DIR)/ivp_actuator.o : $(abspath ../../ivp/ivp_controller/ivp_actuator.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_actuator_spring.P
endif

$(OBJ_DIR)/ivp_actuator_spring.o : $(abspath ../../ivp/ivp_controller/ivp_actuator_spring.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_buoyancy_solver.P
endif

$(OBJ_DIR)/ivp_buoyancy_solver.o : $(abspath ../../ivp/ivp_controller/ivp_buoyancy_solver.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_car_system.P
endif

$(OBJ_DIR)/ivp_car_system.o : $(abspath ../../ivp/ivp_controller/ivp_car_system.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_constraint.P
endif

$(OBJ_DIR)/ivp_constraint.o : $(abspath ../../ivp/ivp_controller/ivp_constraint.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_constraint_car.P
endif

$(OBJ_DIR)/ivp_constraint_car.o : $(abspath ../../ivp/ivp_controller/ivp_constraint_car.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_constraint_fixed_keyed.P
endif

$(OBJ_DIR)/ivp_constraint_fixed_keyed.o : $(abspath ../../ivp/ivp_controller/ivp_constraint_fixed_keyed.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_constraint_local.P
endif

$(OBJ_DIR)/ivp_constraint_local.o : $(abspath ../../ivp/ivp_controller/ivp_constraint_local.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_controller_airboat.P
endif

$(OBJ_DIR)/ivp_controller_airboat.o : $(abspath ../../ivp/ivp_controller/ivp_controller_airboat.cpp) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_controller_buoyancy.P
endif

$(OBJ_DIR)/ivp_controller_buoyancy.o : $(abspath ../../ivp/ivp_controller/ivp_controller_buoyancy.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_controller_floating.P
endif

$(OBJ_DIR)/ivp_controller_floating.o : $(abspath ../../ivp/ivp_controller/ivp_controller_floating.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_controller_motion.P
endif

$(OBJ_DIR)/ivp_controller_motion.o : $(abspath ../../ivp/ivp_controller/ivp_controller_motion.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_controller_raycast_car.P
endif

$(OBJ_DIR)/ivp_controller_raycast_car.o : $(abspath ../../ivp/ivp_controller/ivp_controller_raycast_car.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_controller_stiff_spring.P
endif

$(OBJ_DIR)/ivp_controller_stiff_spring.o : $(abspath ../../ivp/ivp_controller/ivp_controller_stiff_spring.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_controller_world_frict.P
endif

$(OBJ_DIR)/ivp_controller_world_frict.o : $(abspath ../../ivp/ivp_controller/ivp_controller_world_frict.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_forcefield.P
endif

$(OBJ_DIR)/ivp_forcefield.o : $(abspath ../../ivp/ivp_controller/ivp_forcefield.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_multidimensional_interp.P
endif

$(OBJ_DIR)/ivp_multidimensional_interp.o : $(abspath ../../ivp/ivp_controller/ivp_multidimensional_interp.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_template_constraint.P
endif

$(OBJ_DIR)/ivp_template_constraint.o : $(abspath ../../ivp/ivp_controller/ivp_template_constraint.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_ball.P
endif

$(OBJ_DIR)/ivp_ball.o : $(abspath ../../ivp/ivp_intern/ivp_ball.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_calc_next_psi_solver.P
endif

$(OBJ_DIR)/ivp_calc_next_psi_solver.o : $(abspath ../../ivp/ivp_intern/ivp_calc_next_psi_solver.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_controller_phantom.P
endif

$(OBJ_DIR)/ivp_controller_phantom.o : $(abspath ../../ivp/ivp_intern/ivp_controller_phantom.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_core.P
endif

$(OBJ_DIR)/ivp_core.o : $(abspath ../../ivp/ivp_intern/ivp_core.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_environment.P
endif

$(OBJ_DIR)/ivp_environment.o : $(abspath ../../ivp/ivp_intern/ivp_environment.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_friction.P
endif

$(OBJ_DIR)/ivp_friction.o : $(abspath ../../ivp/ivp_intern/ivp_friction.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_friction_gaps.P
endif

$(OBJ_DIR)/ivp_friction_gaps.o : $(abspath ../../ivp/ivp_intern/ivp_friction_gaps.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_great_matrix.P
endif

$(OBJ_DIR)/ivp_great_matrix.o : $(abspath ../../ivp/ivp_intern/ivp_great_matrix.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_hull_manager.P
endif

$(OBJ_DIR)/ivp_hull_manager.o : $(abspath ../../ivp/ivp_intern/ivp_hull_manager.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_impact.P
endif

$(OBJ_DIR)/ivp_impact.o : $(abspath ../../ivp/ivp_intern/ivp_impact.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_i_friction_hash.P
endif

$(OBJ_DIR)/ivp_i_friction_hash.o : $(abspath ../../ivp/ivp_intern/ivp_i_friction_hash.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_i_object_vhash.P
endif

$(OBJ_DIR)/ivp_i_object_vhash.o : $(abspath ../../ivp/ivp_intern/ivp_i_object_vhash.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_merge_core.P
endif

$(OBJ_DIR)/ivp_merge_core.o : $(abspath ../../ivp/ivp_intern/ivp_merge_core.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_mindist_friction.P
endif

$(OBJ_DIR)/ivp_mindist_friction.o : $(abspath ../../ivp/ivp_intern/ivp_mindist_friction.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_object.P
endif

$(OBJ_DIR)/ivp_object.o : $(abspath ../../ivp/ivp_intern/ivp_object.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_object_attach.P
endif

$(OBJ_DIR)/ivp_object_attach.o : $(abspath ../../ivp/ivp_intern/ivp_object_attach.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_physic.P
endif

$(OBJ_DIR)/ivp_physics.hxx.gch : ivp_physics.hxx $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/ivp_physics.hxx.P : $(OBJ_DIR)/ivp_physics.hxx.gch

vpath ivp_physics.hxx . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/ivp_physics.hxx.P
endif

$(OBJ_DIR)/ivp_physics.hxx : ivp_physics.hxx $(OBJ_DIR)/ivp_physics.hxx.gch $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/ivp_physics.hxx

$(OBJ_DIR)/ivp_physic.o : $(abspath ../../ivp/ivp_intern/ivp_physic.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_physic_private.P
endif

$(OBJ_DIR)/ivp_physic_private.o : $(abspath ../../ivp/ivp_intern/ivp_physic_private.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_polygon.P
endif

$(OBJ_DIR)/ivp_polygon.o : $(abspath ../../ivp/ivp_intern/ivp_polygon.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_sim_unit.P
endif

$(OBJ_DIR)/ivp_sim_unit.o : $(abspath ../../ivp/ivp_intern/ivp_sim_unit.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_solver_core_reaction.P
endif

$(OBJ_DIR)/ivp_solver_core_reaction.o : $(abspath ../../ivp/ivp_intern/ivp_solver_core_reaction.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_time.P
endif

$(OBJ_DIR)/ivp_time.o : $(abspath ../../ivp/ivp_intern/ivp_time.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_anomaly_manager.P
endif

$(OBJ_DIR)/ivp_anomaly_manager.o : $(abspath ../../ivp/ivp_physics/ivp_anomaly_manager.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_betterdebugmanager.P
endif

$(OBJ_DIR)/ivp_betterdebugmanager.o : $(abspath ../../ivp/ivp_physics/ivp_betterdebugmanager.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_betterstatisticsmanager.P
endif

$(OBJ_DIR)/ivp_betterstatisticsmanager.o : $(abspath ../../ivp/ivp_physics/ivp_betterstatisticsmanager.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_cache_object.P
endif

$(OBJ_DIR)/ivp_cache_object.o : $(abspath ../../ivp/ivp_physics/ivp_cache_object.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_liquid_surface_descript.P
endif

$(OBJ_DIR)/ivp_liquid_surface_descript.o : $(abspath ../../ivp/ivp_physics/ivp_liquid_surface_descript.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_material.P
endif

$(OBJ_DIR)/ivp_material.o : $(abspath ../../ivp/ivp_physics/ivp_material.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_performancecounter.P
endif

$(OBJ_DIR)/ivp_performancecounter.o : $(abspath ../../ivp/ivp_physics/ivp_performancecounter.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_stat_manager_cback_con.P
endif

$(OBJ_DIR)/ivp_stat_manager_cback_con.o : $(abspath ../../ivp/ivp_physics/ivp_stat_manager_cback_con.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surface_manager.P
endif

$(OBJ_DIR)/ivp_surface_manager.o : $(abspath ../../ivp/ivp_physics/ivp_surface_manager.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_templates.P
endif

$(OBJ_DIR)/ivp_templates.o : $(abspath ../../ivp/ivp_physics/ivp_templates.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_compact_surface.P
endif

$(OBJ_DIR)/ivp_compact_surface.o : $(abspath ../../ivp/ivp_surface_manager/ivp_compact_surface.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_gridbuild_array.P
endif

$(OBJ_DIR)/ivp_gridbuild_array.o : $(abspath ../../ivp/ivp_surface_manager/ivp_gridbuild_array.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surman_grid.P
endif

$(OBJ_DIR)/ivp_surman_grid.o : $(abspath ../../ivp/ivp_surface_manager/ivp_surman_grid.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surman_polygon.P
endif

$(OBJ_DIR)/ivp_surman_polygon.o : $(abspath ../../ivp/ivp_surface_manager/ivp_surman_polygon.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_active_value.P
endif

$(OBJ_DIR)/ivu_active_value.o : $(abspath ../../ivp/ivp_utility/ivu_active_value.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_bigvector.P
endif

$(OBJ_DIR)/ivu_bigvector.o : $(abspath ../../ivp/ivp_utility/ivu_bigvector.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_geometry.P
endif

$(OBJ_DIR)/ivu_geometry.o : $(abspath ../../ivp/ivp_utility/ivu_geometry.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_hash.P
endif

$(OBJ_DIR)/ivu_hash.o : $(abspath ../../ivp/ivp_utility/ivu_hash.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_linear.P
endif

$(OBJ_DIR)/ivu_linear.o : $(abspath ../../ivp/ivp_utility/ivu_linear.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_memory.P
endif

$(OBJ_DIR)/ivu_memory.o : $(abspath ../../ivp/ivp_utility/ivu_memory.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_min_hash.P
endif

$(OBJ_DIR)/ivu_min_hash.o : $(abspath ../../ivp/ivp_utility/ivu_min_hash.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_min_list.P
endif

$(OBJ_DIR)/ivu_min_list.o : $(abspath ../../ivp/ivp_utility/ivu_min_list.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_os_dep.P
endif

$(OBJ_DIR)/ivu_os_dep.o : $(abspath ../../ivp/ivp_utility/ivu_os_dep.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_quat.P
endif

$(OBJ_DIR)/ivu_quat.o : $(abspath ../../ivp/ivp_utility/ivu_quat.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_string.P
endif

$(OBJ_DIR)/ivu_string.o : $(abspath ../../ivp/ivp_utility/ivu_string.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_types.P
endif

$(OBJ_DIR)/ivu_types.o : $(abspath ../../ivp/ivp_utility/ivu_types.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_vector.P
endif

$(OBJ_DIR)/ivu_vector.o : $(abspath ../../ivp/ivp_utility/ivu_vector.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivu_vhash.P
endif

$(OBJ_DIR)/ivu_vhash.o : $(abspath ../../ivp/ivp_utility/ivu_vhash.cxx) $(PWD)/ivp_physics_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)
