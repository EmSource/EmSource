ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=ivp_compactbuilder
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
DEFINES += -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DIVP_VERSION_SDK -DHAVOK_MOPP -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/ivp_compact_builder -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
else
DEFINES += -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DIVP_VERSION_SDK -DHAVOK_MOPP -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/ivp/ivp_compact_builder -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
endif
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 ../../ivp/ivp_intern ../../ivp/ivp_collision ../../ivp/ivp_physics ../../ivp/ivp_surface_manager ../../ivp/ivp_utility ../../ivp/ivp_controller ../../ivp/ivp_compact_builder ../../ivp/havana/havok ../../ivp/havana 
CONFTYPE=lib
GAMEOUTPUTFILE=../../lib/common/linux32/ivp_compactbuilder.a
TARGETCOPIES=
OUTPUTFILE=ivp_compactbuilder.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../ivp/ivp_compact_builder/3dsimport_co.cxx \
    ../../ivp/ivp_compact_builder/geompack_cutfac.cxx \
    ../../ivp/ivp_compact_builder/geompack_cvdec3.cxx \
    ../../ivp/ivp_compact_builder/geompack_drdec3.cxx \
    ../../ivp/ivp_compact_builder/geompack_dsphdc.cxx \
    ../../ivp/ivp_compact_builder/geompack_edght.cxx \
    ../../ivp/ivp_compact_builder/geompack_initcb.cxx \
    ../../ivp/ivp_compact_builder/geompack_insed3.cxx \
    ../../ivp/ivp_compact_builder/geompack_insfac.cxx \
    ../../ivp/ivp_compact_builder/geompack_insvr3.cxx \
    ../../ivp/ivp_compact_builder/geompack_prime.cxx \
    ../../ivp/ivp_compact_builder/geompack_ptpolg.cxx \
    ../../ivp/ivp_compact_builder/geompack_resedg.cxx \
    ../../ivp/ivp_compact_builder/ivp_compact_ledge_gen.cxx \
    ../../ivp/ivp_compact_builder/ivp_compact_modify.cxx \
    ../../ivp/ivp_compact_builder/ivp_compact_recursive.cxx \
    ../../ivp/ivp_compact_builder/ivp_convex_decompositor.cxx \
    ../../ivp/ivp_compact_builder/ivp_halfspacesoup.cxx \
    ../../ivp/ivp_compact_builder/ivp_i_fpoint_vhash.cxx \
    ../../ivp/ivp_compact_builder/ivp_i_point_vhash.cxx \
    ../../ivp/ivp_compact_builder/ivp_object_polygon_tetra.cxx \
    ../../ivp/ivp_compact_builder/ivp_rot_inertia_solver.cxx \
    ../../ivp/ivp_compact_builder/ivp_surbuild_halfspacesoup.cxx \
    ../../ivp/ivp_compact_builder/ivp_surbuild_ledge_soup.cxx \
    ../../ivp/ivp_compact_builder/ivp_surbuild_pointsoup.cxx \
    ../../ivp/ivp_compact_builder/ivp_surbuild_polygon_convex.cxx \
    ../../ivp/ivp_compact_builder/ivp_surbuild_polyhdrn_cncv.cxx \
    ../../ivp/ivp_compact_builder/ivp_surbuild_q12.cxx \
    ../../ivp/ivp_compact_builder/ivp_templates_intern.cxx \
    ../../ivp/ivp_compact_builder/ivp_tetra_intrude.cxx \
    ../../ivp/ivp_compact_builder/ivv_cluster_min_hash.cxx \
    ../../ivp/ivp_compact_builder/qhull.cxx \
    ../../ivp/ivp_compact_builder/qhull_geom.cxx \
    ../../ivp/ivp_compact_builder/qhull_geom2.cxx \
    ../../ivp/ivp_compact_builder/qhull_global.cxx \
    ../../ivp/ivp_compact_builder/qhull_io.cxx \
    ../../ivp/ivp_compact_builder/qhull_mem.cxx \
    ../../ivp/ivp_compact_builder/qhull_merge.cxx \
    ../../ivp/ivp_compact_builder/qhull_poly.cxx \
    ../../ivp/ivp_compact_builder/qhull_poly2.cxx \
    ../../ivp/ivp_compact_builder/qhull_qset.cxx \
    ../../ivp/ivp_compact_builder/qhull_stat.cxx \
    ../../ivp/ivp_compact_builder/qhull_user.cxx \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/3dsimport_co.P
endif

$(OBJ_DIR)/3dsimport_co.o : $(abspath ../../ivp/ivp_compact_builder/3dsimport_co.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_cutfac.P
endif

$(OBJ_DIR)/geompack_cutfac.o : $(abspath ../../ivp/ivp_compact_builder/geompack_cutfac.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_cvdec3.P
endif

$(OBJ_DIR)/geompack_cvdec3.o : $(abspath ../../ivp/ivp_compact_builder/geompack_cvdec3.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_drdec3.P
endif

$(OBJ_DIR)/geompack_drdec3.o : $(abspath ../../ivp/ivp_compact_builder/geompack_drdec3.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_dsphdc.P
endif

$(OBJ_DIR)/geompack_dsphdc.o : $(abspath ../../ivp/ivp_compact_builder/geompack_dsphdc.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_edght.P
endif

$(OBJ_DIR)/geompack_edght.o : $(abspath ../../ivp/ivp_compact_builder/geompack_edght.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_initcb.P
endif

$(OBJ_DIR)/geompack_initcb.o : $(abspath ../../ivp/ivp_compact_builder/geompack_initcb.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_insed3.P
endif

$(OBJ_DIR)/geompack_insed3.o : $(abspath ../../ivp/ivp_compact_builder/geompack_insed3.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_insfac.P
endif

$(OBJ_DIR)/geompack_insfac.o : $(abspath ../../ivp/ivp_compact_builder/geompack_insfac.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_insvr3.P
endif

$(OBJ_DIR)/geompack_insvr3.o : $(abspath ../../ivp/ivp_compact_builder/geompack_insvr3.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_prime.P
endif

$(OBJ_DIR)/geompack_prime.o : $(abspath ../../ivp/ivp_compact_builder/geompack_prime.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_ptpolg.P
endif

$(OBJ_DIR)/geompack_ptpolg.o : $(abspath ../../ivp/ivp_compact_builder/geompack_ptpolg.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geompack_resedg.P
endif

$(OBJ_DIR)/geompack_resedg.o : $(abspath ../../ivp/ivp_compact_builder/geompack_resedg.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_compact_ledge_gen.P
endif

$(OBJ_DIR)/ivp_physics.hxx.gch : ivp_physics.hxx $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/ivp_physics.hxx.P : $(OBJ_DIR)/ivp_physics.hxx.gch

vpath ivp_physics.hxx . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/ivp_physics.hxx.P
endif

$(OBJ_DIR)/ivp_physics.hxx : ivp_physics.hxx $(OBJ_DIR)/ivp_physics.hxx.gch $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/ivp_physics.hxx

$(OBJ_DIR)/ivp_compact_ledge_gen.o : $(abspath ../../ivp/ivp_compact_builder/ivp_compact_ledge_gen.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_compact_modify.P
endif

$(OBJ_DIR)/ivp_compact_modify.o : $(abspath ../../ivp/ivp_compact_builder/ivp_compact_modify.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_compact_recursive.P
endif

$(OBJ_DIR)/ivp_compact_recursive.o : $(abspath ../../ivp/ivp_compact_builder/ivp_compact_recursive.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_convex_decompositor.P
endif

$(OBJ_DIR)/ivp_convex_decompositor.o : $(abspath ../../ivp/ivp_compact_builder/ivp_convex_decompositor.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_halfspacesoup.P
endif

$(OBJ_DIR)/ivp_halfspacesoup.o : $(abspath ../../ivp/ivp_compact_builder/ivp_halfspacesoup.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_i_fpoint_vhash.P
endif

$(OBJ_DIR)/ivp_i_fpoint_vhash.o : $(abspath ../../ivp/ivp_compact_builder/ivp_i_fpoint_vhash.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_i_point_vhash.P
endif

$(OBJ_DIR)/ivp_i_point_vhash.o : $(abspath ../../ivp/ivp_compact_builder/ivp_i_point_vhash.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_object_polygon_tetra.P
endif

$(OBJ_DIR)/ivp_object_polygon_tetra.o : $(abspath ../../ivp/ivp_compact_builder/ivp_object_polygon_tetra.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_rot_inertia_solver.P
endif

$(OBJ_DIR)/ivp_rot_inertia_solver.o : $(abspath ../../ivp/ivp_compact_builder/ivp_rot_inertia_solver.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surbuild_halfspacesoup.P
endif

$(OBJ_DIR)/ivp_surbuild_halfspacesoup.o : $(abspath ../../ivp/ivp_compact_builder/ivp_surbuild_halfspacesoup.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surbuild_ledge_soup.P
endif

$(OBJ_DIR)/ivp_surbuild_ledge_soup.o : $(abspath ../../ivp/ivp_compact_builder/ivp_surbuild_ledge_soup.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surbuild_pointsoup.P
endif

$(OBJ_DIR)/ivp_surbuild_pointsoup.o : $(abspath ../../ivp/ivp_compact_builder/ivp_surbuild_pointsoup.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surbuild_polygon_convex.P
endif

$(OBJ_DIR)/ivp_surbuild_polygon_convex.o : $(abspath ../../ivp/ivp_compact_builder/ivp_surbuild_polygon_convex.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surbuild_polyhdrn_cncv.P
endif

$(OBJ_DIR)/ivp_surbuild_polyhdrn_cncv.o : $(abspath ../../ivp/ivp_compact_builder/ivp_surbuild_polyhdrn_cncv.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_surbuild_q12.P
endif

$(OBJ_DIR)/ivp_surbuild_q12.o : $(abspath ../../ivp/ivp_compact_builder/ivp_surbuild_q12.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_templates_intern.P
endif

$(OBJ_DIR)/ivp_templates_intern.o : $(abspath ../../ivp/ivp_compact_builder/ivp_templates_intern.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivp_tetra_intrude.P
endif

$(OBJ_DIR)/ivp_tetra_intrude.o : $(abspath ../../ivp/ivp_compact_builder/ivp_tetra_intrude.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ivv_cluster_min_hash.P
endif

$(OBJ_DIR)/ivv_cluster_min_hash.o : $(abspath ../../ivp/ivp_compact_builder/ivv_cluster_min_hash.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull.P
endif

$(OBJ_DIR)/qhull.o : $(abspath ../../ivp/ivp_compact_builder/qhull.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_geom.P
endif

$(OBJ_DIR)/qhull_geom.o : $(abspath ../../ivp/ivp_compact_builder/qhull_geom.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_geom2.P
endif

$(OBJ_DIR)/qhull_geom2.o : $(abspath ../../ivp/ivp_compact_builder/qhull_geom2.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_global.P
endif

$(OBJ_DIR)/qhull_global.o : $(abspath ../../ivp/ivp_compact_builder/qhull_global.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_io.P
endif

$(OBJ_DIR)/qhull_io.o : $(abspath ../../ivp/ivp_compact_builder/qhull_io.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_mem.P
endif

$(OBJ_DIR)/qhull_mem.o : $(abspath ../../ivp/ivp_compact_builder/qhull_mem.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_merge.P
endif

$(OBJ_DIR)/qhull_merge.o : $(abspath ../../ivp/ivp_compact_builder/qhull_merge.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_poly.P
endif

$(OBJ_DIR)/qhull_poly.o : $(abspath ../../ivp/ivp_compact_builder/qhull_poly.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_poly2.P
endif

$(OBJ_DIR)/qhull_poly2.o : $(abspath ../../ivp/ivp_compact_builder/qhull_poly2.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_qset.P
endif

$(OBJ_DIR)/qhull_qset.o : $(abspath ../../ivp/ivp_compact_builder/qhull_qset.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_stat.P
endif

$(OBJ_DIR)/qhull_stat.o : $(abspath ../../ivp/ivp_compact_builder/qhull_stat.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/qhull_user.P
endif

$(OBJ_DIR)/qhull_user.o : $(abspath ../../ivp/ivp_compact_builder/qhull_user.cxx) $(PWD)/ivp_compactbuilder_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)
