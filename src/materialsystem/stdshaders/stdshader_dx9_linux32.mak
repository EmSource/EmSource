ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=stdshader_dx9
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
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=stdshader_dx9 -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DSTDSHADER_DX9_DLL_EXPORT -DFAST_MATERIALVAR_ACCESS -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/materialsystem/stdshaders -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 fxctmp9 vshtmp9 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../lib/public/linux32/stdshader_dx9.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/stdshader_dx9.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../public/tier0/memoverride.cpp \
    AccumBuff4Sample.cpp \
    accumbuff5sample.cpp \
    aftershock.cpp \
    aftershock_helper.cpp \
    BaseVSShader.cpp \
    bik_dx90.cpp \
    Bloom.cpp \
    BlurFilterX.cpp \
    BlurFilterY.cpp \
    BufferClearObeyStencil_dx9.cpp \
    cable_dx9.cpp \
    cloak.cpp \
    cloak_blended_pass_helper.cpp \
    cloak_dx9_helper.cpp \
    cloud_dx9.cpp \
    colorcorrection.cpp \
    color_projection.cpp \
    compositor.cpp \
    core_dx9.cpp \
    debugmrttexture.cpp \
    DebugTextureView.cpp \
    DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.cpp \
    DecalModulate_dx9.cpp \
    depthwrite.cpp \
    Downsample.cpp \
    downsample_nohdr.cpp \
    emissive_scroll_blended_pass_helper.cpp \
    Engine_Post_dx9.cpp \
    eyeglint_dx9.cpp \
    eyes_dx8_dx9_helper.cpp \
    eyes_dx9.cpp \
    eye_refract.cpp \
    eye_refract_helper.cpp \
    filmdust_dx8_dx9.cpp \
    filmgrain_dx8_dx9.cpp \
    flesh_interior_blended_pass_helper.cpp \
    floatcombine.cpp \
    floatcombine_autoexpose.cpp \
    floattoscreen.cpp \
    floattoscreen_vanilla.cpp \
    HDRCombineTo16Bit.cpp \
    HDRSelectRange.cpp \
    hsl_filmgrain_pass1.cpp \
    hsl_filmgrain_pass2.cpp \
    hsv.cpp \
    introscreenspaceeffect.cpp \
    lightmappedgeneric_dx9.cpp \
    lightmappedgeneric_dx9_helper.cpp \
    lightmappedreflective.cpp \
    modulate_dx9.cpp \
    MonitorScreen_dx9.cpp \
    motion_blur_dx9.cpp \
    occlusion_dx9.cpp \
    particlelitgeneric_dx9.cpp \
    particlelitgeneric_dx9_helper.cpp \
    particlesphere_dx9.cpp \
    portal.cpp \
    portalstaticoverlay.cpp \
    portal_refract.cpp \
    portal_refract_helper.cpp \
    pyro_vision.cpp \
    refract.cpp \
    refract_dx9_helper.cpp \
    sample4x4.cpp \
    sample4x4_blend.cpp \
    screenspace_general.cpp \
    sfm_blurfilterx.cpp \
    sfm_blurfiltery.cpp \
    sfm_downsample.cpp \
    sfm_integercombine.cpp \
    shadow.cpp \
    shadowbuild_dx9.cpp \
    shadowmodel_dx9.cpp \
    shatteredglass.cpp \
    showz.cpp \
    skin_dx9_helper.cpp \
    sky_dx9.cpp \
    sky_hdr_dx9.cpp \
    spritecard.cpp \
    sprite_dx9.cpp \
    teeth.cpp \
    TreeLeaf.cpp \
    unlitgeneric_dx9.cpp \
    unlittwotexture_dx9.cpp \
    vertexlitgeneric_dx9.cpp \
    vertexlitgeneric_dx9_helper.cpp \
    volume_clouds.cpp \
    volume_clouds_helper.cpp \
    vortwarp_dx9.cpp \
    vr_distort_hud.cpp \
    vr_distort_texture.cpp \
    warp.cpp \
    water.cpp \
    weapon_sheen_pass_helper.cpp \
    windowimposter_dx90.cpp \
    wireframe_dx9.cpp \
    worldtwotextureblend.cpp \
    worldvertexalpha.cpp \
    worldvertextransition.cpp \
    worldvertextransition_dx8_helper.cpp \
    writestencil_dx9.cpp \
    writez_dx9.cpp \


LIBFILES = \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/shaderlib.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/shaderlib.a \
    ../../lib/public/linux32/tier1.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AccumBuff4Sample.P
endif

$(OBJ_DIR)/AccumBuff4Sample.o : $(abspath AccumBuff4Sample.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/accumbuff5sample.P
endif

$(OBJ_DIR)/accumbuff5sample.o : $(abspath accumbuff5sample.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/aftershock.P
endif

$(OBJ_DIR)/aftershock.o : $(abspath aftershock.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/aftershock_helper.P
endif

$(OBJ_DIR)/aftershock_helper.o : $(abspath aftershock_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseVSShader.P
endif

$(OBJ_DIR)/BaseVSShader.o : $(abspath BaseVSShader.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bik_dx90.P
endif

$(OBJ_DIR)/bik_dx90.o : $(abspath bik_dx90.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Bloom.P
endif

$(OBJ_DIR)/Bloom.o : $(abspath Bloom.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BlurFilterX.P
endif

$(OBJ_DIR)/BlurFilterX.o : $(abspath BlurFilterX.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BlurFilterY.P
endif

$(OBJ_DIR)/BlurFilterY.o : $(abspath BlurFilterY.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BufferClearObeyStencil_dx9.P
endif

$(OBJ_DIR)/BufferClearObeyStencil_dx9.o : $(abspath BufferClearObeyStencil_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cable_dx9.P
endif

$(OBJ_DIR)/cable_dx9.o : $(abspath cable_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cloak.P
endif

$(OBJ_DIR)/cloak.o : $(abspath cloak.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cloak_blended_pass_helper.P
endif

$(OBJ_DIR)/cloak_blended_pass_helper.o : $(abspath cloak_blended_pass_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cloak_dx9_helper.P
endif

$(OBJ_DIR)/cloak_dx9_helper.o : $(abspath cloak_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cloud_dx9.P
endif

$(OBJ_DIR)/cloud_dx9.o : $(abspath cloud_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrection.P
endif

$(OBJ_DIR)/colorcorrection.o : $(abspath colorcorrection.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/color_projection.P
endif

$(OBJ_DIR)/color_projection.o : $(abspath color_projection.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/compositor.P
endif

$(OBJ_DIR)/compositor.o : $(abspath compositor.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/core_dx9.P
endif

$(OBJ_DIR)/core_dx9.o : $(abspath core_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugmrttexture.P
endif

$(OBJ_DIR)/debugmrttexture.o : $(abspath debugmrttexture.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DebugTextureView.P
endif

$(OBJ_DIR)/DebugTextureView.o : $(abspath DebugTextureView.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.P
endif

$(OBJ_DIR)/DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.o : $(abspath DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DecalModulate_dx9.P
endif

$(OBJ_DIR)/DecalModulate_dx9.o : $(abspath DecalModulate_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/depthwrite.P
endif

$(OBJ_DIR)/depthwrite.o : $(abspath depthwrite.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Downsample.P
endif

$(OBJ_DIR)/Downsample.o : $(abspath Downsample.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/downsample_nohdr.P
endif

$(OBJ_DIR)/downsample_nohdr.o : $(abspath downsample_nohdr.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/emissive_scroll_blended_pass_helper.P
endif

$(OBJ_DIR)/emissive_scroll_blended_pass_helper.o : $(abspath emissive_scroll_blended_pass_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Engine_Post_dx9.P
endif

$(OBJ_DIR)/Engine_Post_dx9.o : $(abspath Engine_Post_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eyeglint_dx9.P
endif

$(OBJ_DIR)/eyeglint_dx9.o : $(abspath eyeglint_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eyes_dx8_dx9_helper.P
endif

$(OBJ_DIR)/eyes_dx8_dx9_helper.o : $(abspath eyes_dx8_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eyes_dx9.P
endif

$(OBJ_DIR)/eyes_dx9.o : $(abspath eyes_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eye_refract.P
endif

$(OBJ_DIR)/eye_refract.o : $(abspath eye_refract.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eye_refract_helper.P
endif

$(OBJ_DIR)/eye_refract_helper.o : $(abspath eye_refract_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filmdust_dx8_dx9.P
endif

$(OBJ_DIR)/filmdust_dx8_dx9.o : $(abspath filmdust_dx8_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filmgrain_dx8_dx9.P
endif

$(OBJ_DIR)/filmgrain_dx8_dx9.o : $(abspath filmgrain_dx8_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/flesh_interior_blended_pass_helper.P
endif

$(OBJ_DIR)/flesh_interior_blended_pass_helper.o : $(abspath flesh_interior_blended_pass_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/floatcombine.P
endif

$(OBJ_DIR)/floatcombine.o : $(abspath floatcombine.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/floatcombine_autoexpose.P
endif

$(OBJ_DIR)/floatcombine_autoexpose.o : $(abspath floatcombine_autoexpose.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/floattoscreen.P
endif

$(OBJ_DIR)/floattoscreen.o : $(abspath floattoscreen.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/floattoscreen_vanilla.P
endif

$(OBJ_DIR)/floattoscreen_vanilla.o : $(abspath floattoscreen_vanilla.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HDRCombineTo16Bit.P
endif

$(OBJ_DIR)/HDRCombineTo16Bit.o : $(abspath HDRCombineTo16Bit.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HDRSelectRange.P
endif

$(OBJ_DIR)/HDRSelectRange.o : $(abspath HDRSelectRange.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hsl_filmgrain_pass1.P
endif

$(OBJ_DIR)/hsl_filmgrain_pass1.o : $(abspath hsl_filmgrain_pass1.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hsl_filmgrain_pass2.P
endif

$(OBJ_DIR)/hsl_filmgrain_pass2.o : $(abspath hsl_filmgrain_pass2.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hsv.P
endif

$(OBJ_DIR)/hsv.o : $(abspath hsv.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/introscreenspaceeffect.P
endif

$(OBJ_DIR)/introscreenspaceeffect.o : $(abspath introscreenspaceeffect.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightmappedgeneric_dx9.P
endif

$(OBJ_DIR)/lightmappedgeneric_dx9.o : $(abspath lightmappedgeneric_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightmappedgeneric_dx9_helper.P
endif

$(OBJ_DIR)/lightmappedgeneric_dx9_helper.o : $(abspath lightmappedgeneric_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightmappedreflective.P
endif

$(OBJ_DIR)/lightmappedreflective.o : $(abspath lightmappedreflective.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/modulate_dx9.P
endif

$(OBJ_DIR)/modulate_dx9.o : $(abspath modulate_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MonitorScreen_dx9.P
endif

$(OBJ_DIR)/MonitorScreen_dx9.o : $(abspath MonitorScreen_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/motion_blur_dx9.P
endif

$(OBJ_DIR)/motion_blur_dx9.o : $(abspath motion_blur_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/occlusion_dx9.P
endif

$(OBJ_DIR)/occlusion_dx9.o : $(abspath occlusion_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlelitgeneric_dx9.P
endif

$(OBJ_DIR)/particlelitgeneric_dx9.o : $(abspath particlelitgeneric_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlelitgeneric_dx9_helper.P
endif

$(OBJ_DIR)/particlelitgeneric_dx9_helper.o : $(abspath particlelitgeneric_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlesphere_dx9.P
endif

$(OBJ_DIR)/particlesphere_dx9.o : $(abspath particlesphere_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/portal.P
endif

$(OBJ_DIR)/portal.o : $(abspath portal.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/portalstaticoverlay.P
endif

$(OBJ_DIR)/portalstaticoverlay.o : $(abspath portalstaticoverlay.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/portal_refract.P
endif

$(OBJ_DIR)/portal_refract.o : $(abspath portal_refract.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/portal_refract_helper.P
endif

$(OBJ_DIR)/portal_refract_helper.o : $(abspath portal_refract_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pyro_vision.P
endif

$(OBJ_DIR)/pyro_vision.o : $(abspath pyro_vision.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/refract.P
endif

$(OBJ_DIR)/refract.o : $(abspath refract.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/refract_dx9_helper.P
endif

$(OBJ_DIR)/refract_dx9_helper.o : $(abspath refract_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sample4x4.P
endif

$(OBJ_DIR)/sample4x4.o : $(abspath sample4x4.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sample4x4_blend.P
endif

$(OBJ_DIR)/sample4x4_blend.o : $(abspath sample4x4_blend.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/screenspace_general.P
endif

$(OBJ_DIR)/screenspace_general.o : $(abspath screenspace_general.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sfm_blurfilterx.P
endif

$(OBJ_DIR)/sfm_blurfilterx.o : $(abspath sfm_blurfilterx.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sfm_blurfiltery.P
endif

$(OBJ_DIR)/sfm_blurfiltery.o : $(abspath sfm_blurfiltery.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sfm_downsample.P
endif

$(OBJ_DIR)/sfm_downsample.o : $(abspath sfm_downsample.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sfm_integercombine.P
endif

$(OBJ_DIR)/sfm_integercombine.o : $(abspath sfm_integercombine.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadow.P
endif

$(OBJ_DIR)/shadow.o : $(abspath shadow.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadowbuild_dx9.P
endif

$(OBJ_DIR)/shadowbuild_dx9.o : $(abspath shadowbuild_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadowmodel_dx9.P
endif

$(OBJ_DIR)/shadowmodel_dx9.o : $(abspath shadowmodel_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shatteredglass.P
endif

$(OBJ_DIR)/shatteredglass.o : $(abspath shatteredglass.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/showz.P
endif

$(OBJ_DIR)/showz.o : $(abspath showz.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/skin_dx9_helper.P
endif

$(OBJ_DIR)/skin_dx9_helper.o : $(abspath skin_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sky_dx9.P
endif

$(OBJ_DIR)/sky_dx9.o : $(abspath sky_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sky_hdr_dx9.P
endif

$(OBJ_DIR)/sky_hdr_dx9.o : $(abspath sky_hdr_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spritecard.P
endif

$(OBJ_DIR)/spritecard.o : $(abspath spritecard.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sprite_dx9.P
endif

$(OBJ_DIR)/sprite_dx9.o : $(abspath sprite_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teeth.P
endif

$(OBJ_DIR)/teeth.o : $(abspath teeth.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TreeLeaf.P
endif

$(OBJ_DIR)/TreeLeaf.o : $(abspath TreeLeaf.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/unlitgeneric_dx9.P
endif

$(OBJ_DIR)/unlitgeneric_dx9.o : $(abspath unlitgeneric_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/unlittwotexture_dx9.P
endif

$(OBJ_DIR)/unlittwotexture_dx9.o : $(abspath unlittwotexture_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vertexlitgeneric_dx9.P
endif

$(OBJ_DIR)/vertexlitgeneric_dx9.o : $(abspath vertexlitgeneric_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vertexlitgeneric_dx9_helper.P
endif

$(OBJ_DIR)/vertexlitgeneric_dx9_helper.o : $(abspath vertexlitgeneric_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/volume_clouds.P
endif

$(OBJ_DIR)/volume_clouds.o : $(abspath volume_clouds.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/volume_clouds_helper.P
endif

$(OBJ_DIR)/volume_clouds_helper.o : $(abspath volume_clouds_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vortwarp_dx9.P
endif

$(OBJ_DIR)/vortwarp_dx9.o : $(abspath vortwarp_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vr_distort_hud.P
endif

$(OBJ_DIR)/vr_distort_hud.o : $(abspath vr_distort_hud.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vr_distort_texture.P
endif

$(OBJ_DIR)/vr_distort_texture.o : $(abspath vr_distort_texture.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/warp.P
endif

$(OBJ_DIR)/warp.o : $(abspath warp.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/water.P
endif

$(OBJ_DIR)/water.o : $(abspath water.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_sheen_pass_helper.P
endif

$(OBJ_DIR)/weapon_sheen_pass_helper.o : $(abspath weapon_sheen_pass_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/windowimposter_dx90.P
endif

$(OBJ_DIR)/windowimposter_dx90.o : $(abspath windowimposter_dx90.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/wireframe_dx9.P
endif

$(OBJ_DIR)/wireframe_dx9.o : $(abspath wireframe_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/worldtwotextureblend.P
endif

$(OBJ_DIR)/worldtwotextureblend.o : $(abspath worldtwotextureblend.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/worldvertexalpha.P
endif

$(OBJ_DIR)/worldvertexalpha.o : $(abspath worldvertexalpha.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/worldvertextransition.P
endif

$(OBJ_DIR)/worldvertextransition.o : $(abspath worldvertextransition.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/worldvertextransition_dx8_helper.P
endif

$(OBJ_DIR)/worldvertextransition_dx8_helper.o : $(abspath worldvertextransition_dx8_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/writestencil_dx9.P
endif

$(OBJ_DIR)/writestencil_dx9.o : $(abspath writestencil_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/writez_dx9.P
endif

$(OBJ_DIR)/writez_dx9.o : $(abspath writez_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=stdshader_dx9 -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DSTDSHADER_DX9_DLL_EXPORT -DFAST_MATERIALVAR_ACCESS -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/materialsystem/stdshaders -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 fxctmp9 vshtmp9 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../lib/public/linux32/stdshader_dx9.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/stdshader_dx9.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../public/tier0/memoverride.cpp \
    AccumBuff4Sample.cpp \
    accumbuff5sample.cpp \
    aftershock.cpp \
    aftershock_helper.cpp \
    BaseVSShader.cpp \
    bik_dx90.cpp \
    Bloom.cpp \
    BlurFilterX.cpp \
    BlurFilterY.cpp \
    BufferClearObeyStencil_dx9.cpp \
    cable_dx9.cpp \
    cloak.cpp \
    cloak_blended_pass_helper.cpp \
    cloak_dx9_helper.cpp \
    cloud_dx9.cpp \
    colorcorrection.cpp \
    color_projection.cpp \
    compositor.cpp \
    core_dx9.cpp \
    debugmrttexture.cpp \
    DebugTextureView.cpp \
    DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.cpp \
    DecalModulate_dx9.cpp \
    depthwrite.cpp \
    Downsample.cpp \
    downsample_nohdr.cpp \
    emissive_scroll_blended_pass_helper.cpp \
    Engine_Post_dx9.cpp \
    eyeglint_dx9.cpp \
    eyes_dx8_dx9_helper.cpp \
    eyes_dx9.cpp \
    eye_refract.cpp \
    eye_refract_helper.cpp \
    filmdust_dx8_dx9.cpp \
    filmgrain_dx8_dx9.cpp \
    flesh_interior_blended_pass_helper.cpp \
    floatcombine.cpp \
    floatcombine_autoexpose.cpp \
    floattoscreen.cpp \
    floattoscreen_vanilla.cpp \
    HDRCombineTo16Bit.cpp \
    HDRSelectRange.cpp \
    hsl_filmgrain_pass1.cpp \
    hsl_filmgrain_pass2.cpp \
    hsv.cpp \
    introscreenspaceeffect.cpp \
    lightmappedgeneric_dx9.cpp \
    lightmappedgeneric_dx9_helper.cpp \
    lightmappedreflective.cpp \
    modulate_dx9.cpp \
    MonitorScreen_dx9.cpp \
    motion_blur_dx9.cpp \
    occlusion_dx9.cpp \
    particlelitgeneric_dx9.cpp \
    particlelitgeneric_dx9_helper.cpp \
    particlesphere_dx9.cpp \
    portal.cpp \
    portalstaticoverlay.cpp \
    portal_refract.cpp \
    portal_refract_helper.cpp \
    pyro_vision.cpp \
    refract.cpp \
    refract_dx9_helper.cpp \
    sample4x4.cpp \
    sample4x4_blend.cpp \
    screenspace_general.cpp \
    sfm_blurfilterx.cpp \
    sfm_blurfiltery.cpp \
    sfm_downsample.cpp \
    sfm_integercombine.cpp \
    shadow.cpp \
    shadowbuild_dx9.cpp \
    shadowmodel_dx9.cpp \
    shatteredglass.cpp \
    showz.cpp \
    skin_dx9_helper.cpp \
    sky_dx9.cpp \
    sky_hdr_dx9.cpp \
    spritecard.cpp \
    sprite_dx9.cpp \
    teeth.cpp \
    TreeLeaf.cpp \
    unlitgeneric_dx9.cpp \
    unlittwotexture_dx9.cpp \
    vertexlitgeneric_dx9.cpp \
    vertexlitgeneric_dx9_helper.cpp \
    volume_clouds.cpp \
    volume_clouds_helper.cpp \
    vortwarp_dx9.cpp \
    vr_distort_hud.cpp \
    vr_distort_texture.cpp \
    warp.cpp \
    water.cpp \
    weapon_sheen_pass_helper.cpp \
    windowimposter_dx90.cpp \
    wireframe_dx9.cpp \
    worldtwotextureblend.cpp \
    worldvertexalpha.cpp \
    worldvertextransition.cpp \
    worldvertextransition_dx8_helper.cpp \
    writestencil_dx9.cpp \
    writez_dx9.cpp \


LIBFILES = \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/shaderlib.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/shaderlib.a \
    ../../lib/public/linux32/tier1.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AccumBuff4Sample.P
endif

$(OBJ_DIR)/AccumBuff4Sample.o : $(abspath AccumBuff4Sample.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/accumbuff5sample.P
endif

$(OBJ_DIR)/accumbuff5sample.o : $(abspath accumbuff5sample.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/aftershock.P
endif

$(OBJ_DIR)/aftershock.o : $(abspath aftershock.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/aftershock_helper.P
endif

$(OBJ_DIR)/aftershock_helper.o : $(abspath aftershock_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseVSShader.P
endif

$(OBJ_DIR)/BaseVSShader.o : $(abspath BaseVSShader.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bik_dx90.P
endif

$(OBJ_DIR)/bik_dx90.o : $(abspath bik_dx90.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Bloom.P
endif

$(OBJ_DIR)/Bloom.o : $(abspath Bloom.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BlurFilterX.P
endif

$(OBJ_DIR)/BlurFilterX.o : $(abspath BlurFilterX.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BlurFilterY.P
endif

$(OBJ_DIR)/BlurFilterY.o : $(abspath BlurFilterY.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BufferClearObeyStencil_dx9.P
endif

$(OBJ_DIR)/BufferClearObeyStencil_dx9.o : $(abspath BufferClearObeyStencil_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cable_dx9.P
endif

$(OBJ_DIR)/cable_dx9.o : $(abspath cable_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cloak.P
endif

$(OBJ_DIR)/cloak.o : $(abspath cloak.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cloak_blended_pass_helper.P
endif

$(OBJ_DIR)/cloak_blended_pass_helper.o : $(abspath cloak_blended_pass_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cloak_dx9_helper.P
endif

$(OBJ_DIR)/cloak_dx9_helper.o : $(abspath cloak_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cloud_dx9.P
endif

$(OBJ_DIR)/cloud_dx9.o : $(abspath cloud_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrection.P
endif

$(OBJ_DIR)/colorcorrection.o : $(abspath colorcorrection.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/color_projection.P
endif

$(OBJ_DIR)/color_projection.o : $(abspath color_projection.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/compositor.P
endif

$(OBJ_DIR)/compositor.o : $(abspath compositor.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/core_dx9.P
endif

$(OBJ_DIR)/core_dx9.o : $(abspath core_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugmrttexture.P
endif

$(OBJ_DIR)/debugmrttexture.o : $(abspath debugmrttexture.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DebugTextureView.P
endif

$(OBJ_DIR)/DebugTextureView.o : $(abspath DebugTextureView.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.P
endif

$(OBJ_DIR)/DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.o : $(abspath DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DecalModulate_dx9.P
endif

$(OBJ_DIR)/DecalModulate_dx9.o : $(abspath DecalModulate_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/depthwrite.P
endif

$(OBJ_DIR)/depthwrite.o : $(abspath depthwrite.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Downsample.P
endif

$(OBJ_DIR)/Downsample.o : $(abspath Downsample.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/downsample_nohdr.P
endif

$(OBJ_DIR)/downsample_nohdr.o : $(abspath downsample_nohdr.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/emissive_scroll_blended_pass_helper.P
endif

$(OBJ_DIR)/emissive_scroll_blended_pass_helper.o : $(abspath emissive_scroll_blended_pass_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Engine_Post_dx9.P
endif

$(OBJ_DIR)/Engine_Post_dx9.o : $(abspath Engine_Post_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eyeglint_dx9.P
endif

$(OBJ_DIR)/eyeglint_dx9.o : $(abspath eyeglint_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eyes_dx8_dx9_helper.P
endif

$(OBJ_DIR)/eyes_dx8_dx9_helper.o : $(abspath eyes_dx8_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eyes_dx9.P
endif

$(OBJ_DIR)/eyes_dx9.o : $(abspath eyes_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eye_refract.P
endif

$(OBJ_DIR)/eye_refract.o : $(abspath eye_refract.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eye_refract_helper.P
endif

$(OBJ_DIR)/eye_refract_helper.o : $(abspath eye_refract_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filmdust_dx8_dx9.P
endif

$(OBJ_DIR)/filmdust_dx8_dx9.o : $(abspath filmdust_dx8_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filmgrain_dx8_dx9.P
endif

$(OBJ_DIR)/filmgrain_dx8_dx9.o : $(abspath filmgrain_dx8_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/flesh_interior_blended_pass_helper.P
endif

$(OBJ_DIR)/flesh_interior_blended_pass_helper.o : $(abspath flesh_interior_blended_pass_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/floatcombine.P
endif

$(OBJ_DIR)/floatcombine.o : $(abspath floatcombine.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/floatcombine_autoexpose.P
endif

$(OBJ_DIR)/floatcombine_autoexpose.o : $(abspath floatcombine_autoexpose.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/floattoscreen.P
endif

$(OBJ_DIR)/floattoscreen.o : $(abspath floattoscreen.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/floattoscreen_vanilla.P
endif

$(OBJ_DIR)/floattoscreen_vanilla.o : $(abspath floattoscreen_vanilla.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HDRCombineTo16Bit.P
endif

$(OBJ_DIR)/HDRCombineTo16Bit.o : $(abspath HDRCombineTo16Bit.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HDRSelectRange.P
endif

$(OBJ_DIR)/HDRSelectRange.o : $(abspath HDRSelectRange.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hsl_filmgrain_pass1.P
endif

$(OBJ_DIR)/hsl_filmgrain_pass1.o : $(abspath hsl_filmgrain_pass1.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hsl_filmgrain_pass2.P
endif

$(OBJ_DIR)/hsl_filmgrain_pass2.o : $(abspath hsl_filmgrain_pass2.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hsv.P
endif

$(OBJ_DIR)/hsv.o : $(abspath hsv.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/introscreenspaceeffect.P
endif

$(OBJ_DIR)/introscreenspaceeffect.o : $(abspath introscreenspaceeffect.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightmappedgeneric_dx9.P
endif

$(OBJ_DIR)/lightmappedgeneric_dx9.o : $(abspath lightmappedgeneric_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightmappedgeneric_dx9_helper.P
endif

$(OBJ_DIR)/lightmappedgeneric_dx9_helper.o : $(abspath lightmappedgeneric_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightmappedreflective.P
endif

$(OBJ_DIR)/lightmappedreflective.o : $(abspath lightmappedreflective.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/modulate_dx9.P
endif

$(OBJ_DIR)/modulate_dx9.o : $(abspath modulate_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MonitorScreen_dx9.P
endif

$(OBJ_DIR)/MonitorScreen_dx9.o : $(abspath MonitorScreen_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/motion_blur_dx9.P
endif

$(OBJ_DIR)/motion_blur_dx9.o : $(abspath motion_blur_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/occlusion_dx9.P
endif

$(OBJ_DIR)/occlusion_dx9.o : $(abspath occlusion_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlelitgeneric_dx9.P
endif

$(OBJ_DIR)/particlelitgeneric_dx9.o : $(abspath particlelitgeneric_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlelitgeneric_dx9_helper.P
endif

$(OBJ_DIR)/particlelitgeneric_dx9_helper.o : $(abspath particlelitgeneric_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlesphere_dx9.P
endif

$(OBJ_DIR)/particlesphere_dx9.o : $(abspath particlesphere_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/portal.P
endif

$(OBJ_DIR)/portal.o : $(abspath portal.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/portalstaticoverlay.P
endif

$(OBJ_DIR)/portalstaticoverlay.o : $(abspath portalstaticoverlay.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/portal_refract.P
endif

$(OBJ_DIR)/portal_refract.o : $(abspath portal_refract.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/portal_refract_helper.P
endif

$(OBJ_DIR)/portal_refract_helper.o : $(abspath portal_refract_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pyro_vision.P
endif

$(OBJ_DIR)/pyro_vision.o : $(abspath pyro_vision.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/refract.P
endif

$(OBJ_DIR)/refract.o : $(abspath refract.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/refract_dx9_helper.P
endif

$(OBJ_DIR)/refract_dx9_helper.o : $(abspath refract_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sample4x4.P
endif

$(OBJ_DIR)/sample4x4.o : $(abspath sample4x4.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sample4x4_blend.P
endif

$(OBJ_DIR)/sample4x4_blend.o : $(abspath sample4x4_blend.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/screenspace_general.P
endif

$(OBJ_DIR)/screenspace_general.o : $(abspath screenspace_general.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sfm_blurfilterx.P
endif

$(OBJ_DIR)/sfm_blurfilterx.o : $(abspath sfm_blurfilterx.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sfm_blurfiltery.P
endif

$(OBJ_DIR)/sfm_blurfiltery.o : $(abspath sfm_blurfiltery.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sfm_downsample.P
endif

$(OBJ_DIR)/sfm_downsample.o : $(abspath sfm_downsample.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sfm_integercombine.P
endif

$(OBJ_DIR)/sfm_integercombine.o : $(abspath sfm_integercombine.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadow.P
endif

$(OBJ_DIR)/shadow.o : $(abspath shadow.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadowbuild_dx9.P
endif

$(OBJ_DIR)/shadowbuild_dx9.o : $(abspath shadowbuild_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadowmodel_dx9.P
endif

$(OBJ_DIR)/shadowmodel_dx9.o : $(abspath shadowmodel_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shatteredglass.P
endif

$(OBJ_DIR)/shatteredglass.o : $(abspath shatteredglass.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/showz.P
endif

$(OBJ_DIR)/showz.o : $(abspath showz.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/skin_dx9_helper.P
endif

$(OBJ_DIR)/skin_dx9_helper.o : $(abspath skin_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sky_dx9.P
endif

$(OBJ_DIR)/sky_dx9.o : $(abspath sky_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sky_hdr_dx9.P
endif

$(OBJ_DIR)/sky_hdr_dx9.o : $(abspath sky_hdr_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spritecard.P
endif

$(OBJ_DIR)/spritecard.o : $(abspath spritecard.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sprite_dx9.P
endif

$(OBJ_DIR)/sprite_dx9.o : $(abspath sprite_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teeth.P
endif

$(OBJ_DIR)/teeth.o : $(abspath teeth.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TreeLeaf.P
endif

$(OBJ_DIR)/TreeLeaf.o : $(abspath TreeLeaf.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/unlitgeneric_dx9.P
endif

$(OBJ_DIR)/unlitgeneric_dx9.o : $(abspath unlitgeneric_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/unlittwotexture_dx9.P
endif

$(OBJ_DIR)/unlittwotexture_dx9.o : $(abspath unlittwotexture_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vertexlitgeneric_dx9.P
endif

$(OBJ_DIR)/vertexlitgeneric_dx9.o : $(abspath vertexlitgeneric_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vertexlitgeneric_dx9_helper.P
endif

$(OBJ_DIR)/vertexlitgeneric_dx9_helper.o : $(abspath vertexlitgeneric_dx9_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/volume_clouds.P
endif

$(OBJ_DIR)/volume_clouds.o : $(abspath volume_clouds.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/volume_clouds_helper.P
endif

$(OBJ_DIR)/volume_clouds_helper.o : $(abspath volume_clouds_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vortwarp_dx9.P
endif

$(OBJ_DIR)/vortwarp_dx9.o : $(abspath vortwarp_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vr_distort_hud.P
endif

$(OBJ_DIR)/vr_distort_hud.o : $(abspath vr_distort_hud.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vr_distort_texture.P
endif

$(OBJ_DIR)/vr_distort_texture.o : $(abspath vr_distort_texture.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/warp.P
endif

$(OBJ_DIR)/warp.o : $(abspath warp.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/water.P
endif

$(OBJ_DIR)/water.o : $(abspath water.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_sheen_pass_helper.P
endif

$(OBJ_DIR)/weapon_sheen_pass_helper.o : $(abspath weapon_sheen_pass_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/windowimposter_dx90.P
endif

$(OBJ_DIR)/windowimposter_dx90.o : $(abspath windowimposter_dx90.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/wireframe_dx9.P
endif

$(OBJ_DIR)/wireframe_dx9.o : $(abspath wireframe_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/worldtwotextureblend.P
endif

$(OBJ_DIR)/worldtwotextureblend.o : $(abspath worldtwotextureblend.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/worldvertexalpha.P
endif

$(OBJ_DIR)/worldvertexalpha.o : $(abspath worldvertexalpha.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/worldvertextransition.P
endif

$(OBJ_DIR)/worldvertextransition.o : $(abspath worldvertextransition.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/worldvertextransition_dx8_helper.P
endif

$(OBJ_DIR)/worldvertextransition_dx8_helper.o : $(abspath worldvertextransition_dx8_helper.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/writestencil_dx9.P
endif

$(OBJ_DIR)/writestencil_dx9.o : $(abspath writestencil_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/writez_dx9.P
endif

$(OBJ_DIR)/writez_dx9.o : $(abspath writez_dx9.cpp) $(PWD)/stdshader_dx9_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



