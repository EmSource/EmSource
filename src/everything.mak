# VPC MASTER MAKEFILE

# Fuck chrooting
export NO_CHROOT = 1
# Disable built-in rules/variables. We don't depend on them, and they slow down make processing.
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
ifeq ($(MAKE_VERBOSE),)
MAKEFLAGS += --no-print-directory
endif

ifneq "$(LINUX_TOOLS_PATH)" ""
    TOOL_PATH = $(LINUX_TOOLS_PATH)/
    SHELL := $(TOOL_PATH)bash
else
    SHELL := /bin/bash
endif
ifndef NO_CHROOT
    export CHROOT_NAME ?= $(subst /,_,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
    RUNTIME_NAME ?= steamrt_scout_i386
    CHROOT_PERSONALITY ?= linux32
    CHROOT_CONF := /etc/schroot/chroot.d/$(CHROOT_NAME).conf
    CHROOT_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/tools/runtime/linux)

    export MAKE_CHROOT = 1
    ifneq ("$(SCHROOT_CHROOT_NAME)", "$(CHROOT_NAME)")
        SHELL := schroot --chroot $(CHROOT_NAME) -- /bin/bash
    endif
endif

ECHO = $(TOOL_PATH)echo
ETAGS = $(TOOL_PATH)etags
FIND = $(TOOL_PATH)find
UNAME = $(TOOL_PATH)uname
XARGS = $(TOOL_PATH)xargs

# to control parallelism, set the MAKE_JOBS environment variable
ifeq ($(strip $(MAKE_JOBS)),)
    ifeq ($(shell $(UNAME)),Darwin)
        CPUS := $(shell /usr/sbin/sysctl -n hw.ncpu)
    endif
    ifeq ($(shell $(UNAME)),Linux)
        CPUS := $(shell $(TOOL_PATH)grep processor /proc/cpuinfo | $(TOOL_PATH)wc -l)
    endif
    MAKE_JOBS := $(CPUS)
endif

ifeq ($(strip $(MAKE_JOBS)),)
    MAKE_JOBS := 8
endif

# make VALVE_NO_PROJECT_DEPS 1 or empty (so VALVE_NO_PROJECT_DEPS=0 works as expected)
ifeq ($(strip $(VALVE_NO_PROJECT_DEPS)),1)
	VALVE_NO_PROJECT_DEPS := 1
else
	VALVE_NO_PROJECT_DEPS :=
endif

# make VALVE_NO_PROJECT_DEPS 1 or empty (so VALVE_NO_PROJECT_DEPS=0 works as expected)
ifeq ($(strip $(VALVE_NO_PROJECT_DEPS)),1)
	VALVE_NO_PROJECT_DEPS := 1
else
	VALVE_NO_PROJECT_DEPS :=
endif

# All projects (default target)
all: $(CHROOT_CONF)
	$(MAKE) -f $(lastword $(MAKEFILE_LIST)) -j$(MAKE_JOBS) all-targets

all-targets : vaudio_minimp3 appframework bitmap bsppack bzip2 choreoobjects client_hl2 datacache dedicated dedicated_main dmxloader engine filesystem_stdio gameui gcsdk havana_constraints hk_base hk_math inputsystem ivp_compactbuilder ivp_physics jpeglib launcher launcher_main lzma materialsystem mathlib matsys_controls panel_zoo particles raytrace replay replay_common scenefilecache server_hl2 serverbrowser serverplugin_empty shaderapidx9 shaderapiempty shaderlib simdtest soundemittersystem sourcevr stdshader_dbg stdshader_dx9 studiorender tier0 tier1 tier2 tier3 togl vaudio_speex vgui_controls vgui2 vgui_surfacelib vguimatsurface video_services vphysics vpklib vstdlib vtex_dll vtf vtf2tga 


# Individual projects + dependencies

vaudio_minimp3 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 vstdlib )
	@echo "Building: vaudio_minimp3"
	@+cd /home/guest/Downloads/src/src/engine/voice_codecs/minimp3 && $(MAKE) -f vaudio_minimp3_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

appframework : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: appframework"
	@+cd /home/guest/Downloads/src/src/appframework && $(MAKE) -f appframework_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

bitmap : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: bitmap"
	@+cd /home/guest/Downloads/src/src/bitmap && $(MAKE) -f bitmap_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

bsppack : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) lzma mathlib tier0 tier1 tier2 vstdlib )
	@echo "Building: bsppack"
	@+cd /home/guest/Downloads/src/src/utils/bsppack && $(MAKE) -f bsppack_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

bzip2 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: bzip2"
	@+cd /home/guest/Downloads/src/src/utils/bzip2 && $(MAKE) -f bzip2_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

choreoobjects : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: choreoobjects"
	@+cd /home/guest/Downloads/src/src/choreoobjects && $(MAKE) -f choreoobjects_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

client_hl2 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap choreoobjects dmxloader mathlib matsys_controls particles tier0 tier1 tier2 tier3 vgui_controls vstdlib vtf )
	@echo "Building: client_hl2"
	@+cd /home/guest/Downloads/src/src/game/client && $(MAKE) -f client_linux32_hl2.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

datacache : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 tier2 tier3 vstdlib )
	@echo "Building: datacache"
	@+cd /home/guest/Downloads/src/src/datacache && $(MAKE) -f datacache_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

dedicated : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) appframework mathlib tier0 tier1 tier2 tier3 vstdlib )
	@echo "Building: dedicated"
	@+cd /home/guest/Downloads/src/src/dedicated && $(MAKE) -f dedicated_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

dedicated_main : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: dedicated_main"
	@+cd /home/guest/Downloads/src/src/dedicated_main && $(MAKE) -f dedicated_main_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

dmxloader : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: dmxloader"
	@+cd /home/guest/Downloads/src/src/dmxloader && $(MAKE) -f dmxloader_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

engine : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) appframework bitmap bzip2 dmxloader mathlib matsys_controls replay_common tier0 tier1 tier2 tier3 vgui_controls vstdlib vtf )
	@echo "Building: engine"
	@+cd /home/guest/Downloads/src/src/engine && $(MAKE) -f engine_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

filesystem_stdio : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 tier2 vpklib vstdlib )
	@echo "Building: filesystem_stdio"
	@+cd /home/guest/Downloads/src/src/filesystem && $(MAKE) -f filesystem_stdio_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

gameui : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap mathlib matsys_controls tier0 tier1 tier2 tier3 vgui_controls vstdlib vtf )
	@echo "Building: gameui"
	@+cd /home/guest/Downloads/src/src/gameui && $(MAKE) -f GameUI_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

gcsdk : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: gcsdk"
	@+cd /home/guest/Downloads/src/src/gcsdk && $(MAKE) -f gcsdk_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

havana_constraints : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: havana_constraints"
	@+cd /home/guest/Downloads/src/src/ivp/havana && $(MAKE) -f havana_constraints_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

hk_base : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: hk_base"
	@+cd /home/guest/Downloads/src/src/ivp/havana/havok/hk_base && $(MAKE) -f hk_base_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

hk_math : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: hk_math"
	@+cd /home/guest/Downloads/src/src/ivp/havana/havok/hk_math && $(MAKE) -f hk_math_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

inputsystem : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 tier2 vstdlib )
	@echo "Building: inputsystem"
	@+cd /home/guest/Downloads/src/src/inputsystem && $(MAKE) -f inputsystem_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

ivp_compactbuilder : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: ivp_compactbuilder"
	@+cd /home/guest/Downloads/src/src/ivp/ivp_compact_builder && $(MAKE) -f ivp_compactbuilder_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

ivp_physics : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: ivp_physics"
	@+cd /home/guest/Downloads/src/src/ivp/ivp_physics && $(MAKE) -f ivp_physics_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

jpeglib : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: jpeglib"
	@+cd /home/guest/Downloads/src/src/utils/jpeglib && $(MAKE) -f jpeglib_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

launcher : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) appframework mathlib tier0 tier1 tier2 tier3 togl vstdlib )
	@echo "Building: launcher"
	@+cd /home/guest/Downloads/src/src/launcher && $(MAKE) -f launcher_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

launcher_main : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: launcher_main"
	@+cd /home/guest/Downloads/src/src/launcher_main && $(MAKE) -f launcher_main_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

lzma : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: lzma"
	@+cd /home/guest/Downloads/src/src/utils/lzma && $(MAKE) -f lzma_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

materialsystem : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap mathlib shaderlib tier0 tier1 tier2 vstdlib vtf )
	@echo "Building: materialsystem"
	@+cd /home/guest/Downloads/src/src/materialsystem && $(MAKE) -f materialsystem_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

mathlib : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: mathlib"
	@+cd /home/guest/Downloads/src/src/mathlib && $(MAKE) -f mathlib_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

matsys_controls : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: matsys_controls"
	@+cd /home/guest/Downloads/src/src/vgui2/matsys_controls && $(MAKE) -f matsys_controls_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

panel_zoo : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) appframework mathlib tier2 tier3 vgui_controls )
	@echo "Building: panel_zoo"
	@+cd /home/guest/Downloads/src/src/utils/vgui_panel_zoo && $(MAKE) -f panel_zoo_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

particles : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: particles"
	@+cd /home/guest/Downloads/src/src/particles && $(MAKE) -f particles_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

raytrace : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: raytrace"
	@+cd /home/guest/Downloads/src/src/raytrace && $(MAKE) -f raytrace_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

replay : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap bzip2 lzma mathlib replay_common tier0 tier1 tier2 vstdlib vtf )
	@echo "Building: replay"
	@+cd /home/guest/Downloads/src/src/replay && $(MAKE) -f replay_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

replay_common : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: replay_common"
	@+cd /home/guest/Downloads/src/src/replay/common && $(MAKE) -f replay_common_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

scenefilecache : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 vstdlib )
	@echo "Building: scenefilecache"
	@+cd /home/guest/Downloads/src/src/scenefilecache && $(MAKE) -f scenefilecache_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

server_hl2 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) choreoobjects dmxloader mathlib particles tier0 tier1 tier2 tier3 vstdlib )
	@echo "Building: server_hl2"
	@+cd /home/guest/Downloads/src/src/game/server && $(MAKE) -f server_linux32_hl2.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

serverbrowser : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) mathlib tier0 tier1 tier2 tier3 vgui_controls vstdlib )
	@echo "Building: serverbrowser"
	@+cd /home/guest/Downloads/src/src/serverbrowser && $(MAKE) -f ServerBrowser_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

serverplugin_empty : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) mathlib tier0 tier1 tier2 vstdlib )
	@echo "Building: serverplugin_empty"
	@+cd /home/guest/Downloads/src/src/utils/serverplugin_sample && $(MAKE) -f serverplugin_empty_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

shaderapidx9 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap bzip2 mathlib tier0 tier1 tier2 togl vstdlib )
	@echo "Building: shaderapidx9"
	@+cd /home/guest/Downloads/src/src/materialsystem/shaderapidx9 && $(MAKE) -f shaderapidx9_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

shaderapiempty : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 vstdlib )
	@echo "Building: shaderapiempty"
	@+cd /home/guest/Downloads/src/src/materialsystem/shaderapiempty && $(MAKE) -f shaderapiempty_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

shaderlib : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: shaderlib"
	@+cd /home/guest/Downloads/src/src/materialsystem/shaderlib && $(MAKE) -f shaderlib_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

simdtest : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) mathlib tier0 tier1 tier2 )
	@echo "Building: simdtest"
	@+cd /home/guest/Downloads/src/src/utils/simdtest && $(MAKE) -f simdtest_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

soundemittersystem : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 vstdlib )
	@echo "Building: soundemittersystem"
	@+cd /home/guest/Downloads/src/src/soundemittersystem && $(MAKE) -f soundemittersystem_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

sourcevr : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) appframework filesystem_stdio mathlib tier0 tier1 tier2 tier3 vstdlib )
	@echo "Building: sourcevr"
	@+cd /home/guest/Downloads/src/src/sourcevr && $(MAKE) -f sourcevr_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

stdshader_dbg : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) mathlib shaderlib tier0 tier1 vstdlib )
	@echo "Building: stdshader_dbg"
	@+cd /home/guest/Downloads/src/src/materialsystem/stdshaders && $(MAKE) -f stdshader_dbg_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

stdshader_dx9 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) mathlib shaderlib tier0 tier1 vstdlib )
	@echo "Building: stdshader_dx9"
	@+cd /home/guest/Downloads/src/src/materialsystem/stdshaders && $(MAKE) -f stdshader_dx9_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

studiorender : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap mathlib tier0 tier1 tier2 tier3 vstdlib )
	@echo "Building: studiorender"
	@+cd /home/guest/Downloads/src/src/studiorender && $(MAKE) -f studiorender_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

tier0 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: tier0"
	@+cd /home/guest/Downloads/src/src/tier0 && $(MAKE) -f tier0_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

tier1 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: tier1"
	@+cd /home/guest/Downloads/src/src/tier1 && $(MAKE) -f tier1_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

tier2 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: tier2"
	@+cd /home/guest/Downloads/src/src/tier2 && $(MAKE) -f tier2_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

tier3 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: tier3"
	@+cd /home/guest/Downloads/src/src/tier3 && $(MAKE) -f tier3_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

togl : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) mathlib tier0 tier1 tier2 vstdlib )
	@echo "Building: togl"
	@+cd /home/guest/Downloads/src/src/togl && $(MAKE) -f togl_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vaudio_speex : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 vstdlib )
	@echo "Building: vaudio_speex"
	@+cd /home/guest/Downloads/src/src/engine/voice_codecs/speex && $(MAKE) -f vaudio_speex_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vgui_controls : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: vgui_controls"
	@+cd /home/guest/Downloads/src/src/vgui2/vgui_controls && $(MAKE) -f vgui_controls_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vgui2 : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 tier2 tier3 vgui_surfacelib vstdlib )
	@echo "Building: vgui2"
	@+cd /home/guest/Downloads/src/src/vgui2/src && $(MAKE) -f vgui_dll_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vgui_surfacelib : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: vgui_surfacelib"
	@+cd /home/guest/Downloads/src/src/vgui2/vgui_surfacelib && $(MAKE) -f vgui_surfacelib_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vguimatsurface : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap mathlib tier0 tier1 tier2 tier3 vgui_controls vgui_surfacelib vstdlib )
	@echo "Building: vguimatsurface"
	@+cd /home/guest/Downloads/src/src/vguimatsurface && $(MAKE) -f vguimatsurface_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

video_services : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 tier2 tier3 vstdlib )
	@echo "Building: video_services"
	@+cd /home/guest/Downloads/src/src/video && $(MAKE) -f video_services_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vphysics : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) havana_constraints hk_base hk_math ivp_compactbuilder ivp_physics mathlib tier0 tier1 tier2 vstdlib )
	@echo "Building: vphysics"
	@+cd /home/guest/Downloads/src/src/vphysics && $(MAKE) -f vphysics_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vpklib : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: vpklib"
	@+cd /home/guest/Downloads/src/src/vpklib && $(MAKE) -f vpklib_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vstdlib : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) tier0 tier1 )
	@echo "Building: vstdlib"
	@+cd /home/guest/Downloads/src/src/vstdlib && $(MAKE) -f vstdlib_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vtex_dll : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap mathlib tier0 tier1 tier2 vstdlib vtf )
	@echo "Building: vtex_dll"
	@+cd /home/guest/Downloads/src/src/utils/vtex && $(MAKE) -f vtex_dll_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vtf : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) )
	@echo "Building: vtf"
	@+cd /home/guest/Downloads/src/src/vtf && $(MAKE) -f vtf_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

vtf2tga : $(if $(VALVE_NO_PROJECT_DEPS),,$(CHROOT_CONF) bitmap mathlib tier0 tier1 tier2 vstdlib vtf )
	@echo "Building: vtf2tga"
	@+cd /home/guest/Downloads/src/src/utils/vtf2tga && $(MAKE) -f vtf2tga_linux32.mak $(SUBMAKE_PARAMS) $(CLEANPARAM)

# this is a bit over-inclusive, but the alternative (actually adding each referenced c/cpp/h file to
# the tags file) seems like more work than it's worth.  feel free to fix that up if it bugs you. 
TAGS:
	@rm -f TAGS
	@$(FIND) /home/guest/Downloads/src/src/engine/voice_codecs/minimp3 -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/engine/voice_codecs/minimp3 -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/engine/voice_codecs/minimp3 -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/appframework -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/appframework -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/appframework -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/bitmap -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/bitmap -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/bitmap -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/bsppack -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/bsppack -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/bsppack -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/bzip2 -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/bzip2 -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/bzip2 -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/choreoobjects -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/choreoobjects -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/choreoobjects -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/game/client -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/game/client -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/game/client -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/datacache -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/datacache -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/datacache -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dedicated -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dedicated -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dedicated -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dedicated_main -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dedicated_main -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dedicated_main -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dmxloader -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dmxloader -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/dmxloader -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/engine -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/engine -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/engine -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/filesystem -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/filesystem -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/filesystem -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/gameui -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/gameui -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/gameui -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/gcsdk -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/gcsdk -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/gcsdk -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana/havok/hk_base -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana/havok/hk_base -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana/havok/hk_base -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana/havok/hk_math -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana/havok/hk_math -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/havana/havok/hk_math -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/inputsystem -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/inputsystem -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/inputsystem -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/ivp_compact_builder -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/ivp_compact_builder -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/ivp_compact_builder -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/ivp_physics -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/ivp_physics -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/ivp/ivp_physics -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/jpeglib -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/jpeglib -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/jpeglib -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/launcher -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/launcher -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/launcher -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/launcher_main -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/launcher_main -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/launcher_main -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/lzma -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/lzma -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/lzma -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/mathlib -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/mathlib -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/mathlib -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/matsys_controls -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/matsys_controls -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/matsys_controls -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vgui_panel_zoo -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vgui_panel_zoo -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vgui_panel_zoo -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/particles -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/particles -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/particles -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/raytrace -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/raytrace -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/raytrace -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/replay -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/replay -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/replay -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/replay/common -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/replay/common -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/replay/common -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/scenefilecache -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/scenefilecache -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/scenefilecache -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/game/server -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/game/server -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/game/server -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/serverbrowser -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/serverbrowser -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/serverbrowser -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/serverplugin_sample -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/serverplugin_sample -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/serverplugin_sample -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderapidx9 -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderapidx9 -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderapidx9 -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderapiempty -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderapiempty -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderapiempty -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderlib -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderlib -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/shaderlib -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/simdtest -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/simdtest -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/simdtest -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/soundemittersystem -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/soundemittersystem -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/soundemittersystem -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/sourcevr -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/sourcevr -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/sourcevr -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/stdshaders -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/stdshaders -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/stdshaders -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/stdshaders -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/stdshaders -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/materialsystem/stdshaders -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/studiorender -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/studiorender -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/studiorender -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier0 -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier0 -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier0 -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier1 -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier1 -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier1 -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier2 -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier2 -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier2 -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier3 -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier3 -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/tier3 -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/togl -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/togl -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/togl -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/engine/voice_codecs/speex -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/engine/voice_codecs/speex -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/engine/voice_codecs/speex -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/vgui_controls -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/vgui_controls -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/vgui_controls -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/src -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/src -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/src -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/vgui_surfacelib -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/vgui_surfacelib -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vgui2/vgui_surfacelib -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vguimatsurface -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vguimatsurface -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vguimatsurface -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/video -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/video -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/video -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vphysics -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vphysics -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vphysics -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vpklib -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vpklib -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vpklib -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vstdlib -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vstdlib -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vstdlib -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vtex -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vtex -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vtex -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vtf -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vtf -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/vtf -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vtf2tga -name '*.cpp' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vtf2tga -name '*.h' -print0 | $(XARGS) -0 $(ETAGS) --language=c++ --declarations --ignore-indentation --append
	@$(FIND) /home/guest/Downloads/src/src/utils/vtf2tga -name '*.c' -print0 | $(XARGS) -0 $(ETAGS) --declarations --ignore-indentation --append



# Mark all the projects as phony or else make will see the directories by the same name and think certain targets 

.PHONY: TAGS showtargets regen showregen clean cleantargets cleanandremove relink vaudio_minimp3 appframework bitmap bsppack bzip2 choreoobjects client_hl2 datacache dedicated dedicated_main dmxloader engine filesystem_stdio gameui gcsdk havana_constraints hk_base hk_math inputsystem ivp_compactbuilder ivp_physics jpeglib launcher launcher_main lzma materialsystem mathlib matsys_controls panel_zoo particles raytrace replay replay_common scenefilecache server_hl2 serverbrowser serverplugin_empty shaderapidx9 shaderapiempty shaderlib simdtest soundemittersystem sourcevr stdshader_dbg stdshader_dx9 studiorender tier0 tier1 tier2 tier3 togl vaudio_speex vgui_controls vgui2 vgui_surfacelib vguimatsurface video_services vphysics vpklib vstdlib vtex_dll vtf vtf2tga 



# The standard clean command to clean it all out.

clean: 
	@$(MAKE) -f $(lastword $(MAKEFILE_LIST)) -j$(MAKE_JOBS) all-targets CLEANPARAM=clean



# clean targets, so we re-link next time.

cleantargets: 
	@$(MAKE) -f $(lastword $(MAKEFILE_LIST)) -j$(MAKE_JOBS) all-targets CLEANPARAM=cleantargets



# p4 edit and remove targets, so we get an entirely clean build.

cleanandremove: 
	@$(MAKE) -f $(lastword $(MAKEFILE_LIST)) -j$(MAKE_JOBS) all-targets CLEANPARAM=cleanandremove



#relink

relink: cleantargets 
	@$(MAKE) -f $(lastword $(MAKEFILE_LIST)) -j$(MAKE_JOBS) all-targets



# Here's a command to list out all the targets


showtargets: 
	@$(ECHO) '-------------------' && \
	$(ECHO) '----- TARGETS -----' && \
	$(ECHO) '-------------------' && \
	$(ECHO) 'clean' && \
	$(ECHO) 'regen' && \
	$(ECHO) 'showregen' && \
	$(ECHO) 'vaudio_minimp3' && \
	$(ECHO) 'appframework' && \
	$(ECHO) 'bitmap' && \
	$(ECHO) 'bsppack' && \
	$(ECHO) 'bzip2' && \
	$(ECHO) 'choreoobjects' && \
	$(ECHO) 'client_hl2' && \
	$(ECHO) 'datacache' && \
	$(ECHO) 'dedicated' && \
	$(ECHO) 'dedicated_main' && \
	$(ECHO) 'dmxloader' && \
	$(ECHO) 'engine' && \
	$(ECHO) 'filesystem_stdio' && \
	$(ECHO) 'gameui' && \
	$(ECHO) 'gcsdk' && \
	$(ECHO) 'havana_constraints' && \
	$(ECHO) 'hk_base' && \
	$(ECHO) 'hk_math' && \
	$(ECHO) 'inputsystem' && \
	$(ECHO) 'ivp_compactbuilder' && \
	$(ECHO) 'ivp_physics' && \
	$(ECHO) 'jpeglib' && \
	$(ECHO) 'launcher' && \
	$(ECHO) 'launcher_main' && \
	$(ECHO) 'lzma' && \
	$(ECHO) 'materialsystem' && \
	$(ECHO) 'mathlib' && \
	$(ECHO) 'matsys_controls' && \
	$(ECHO) 'panel_zoo' && \
	$(ECHO) 'particles' && \
	$(ECHO) 'raytrace' && \
	$(ECHO) 'replay' && \
	$(ECHO) 'replay_common' && \
	$(ECHO) 'scenefilecache' && \
	$(ECHO) 'server_hl2' && \
	$(ECHO) 'serverbrowser' && \
	$(ECHO) 'serverplugin_empty' && \
	$(ECHO) 'shaderapidx9' && \
	$(ECHO) 'shaderapiempty' && \
	$(ECHO) 'shaderlib' && \
	$(ECHO) 'simdtest' && \
	$(ECHO) 'soundemittersystem' && \
	$(ECHO) 'sourcevr' && \
	$(ECHO) 'stdshader_dbg' && \
	$(ECHO) 'stdshader_dx9' && \
	$(ECHO) 'studiorender' && \
	$(ECHO) 'tier0' && \
	$(ECHO) 'tier1' && \
	$(ECHO) 'tier2' && \
	$(ECHO) 'tier3' && \
	$(ECHO) 'togl' && \
	$(ECHO) 'vaudio_speex' && \
	$(ECHO) 'vgui_controls' && \
	$(ECHO) 'vgui2' && \
	$(ECHO) 'vgui_surfacelib' && \
	$(ECHO) 'vguimatsurface' && \
	$(ECHO) 'video_services' && \
	$(ECHO) 'vphysics' && \
	$(ECHO) 'vpklib' && \
	$(ECHO) 'vstdlib' && \
	$(ECHO) 'vtex_dll' && \
	$(ECHO) 'vtf' && \
	$(ECHO) 'vtf2tga'



# Here's a command to regenerate this makefile


regen: 
	


# Here's a command to list out all the targets


showregen: 
	@$(ECHO) 

ifdef CHROOT_CONF
$(CHROOT_CONF): $(CHROOT_DIR)/$(RUNTIME_NAME)/timestamp
$(CHROOT_CONF): SHELL = /bin/bash
$(CHROOT_DIR)/$(RUNTIME_NAME)/timestamp: $(CHROOT_DIR)/$(RUNTIME_NAME).tar.xz
	@echo "Configuring schroot at $(CHROOT_DIR) (requires sudo)"
	sudo $(CHROOT_DIR)/configure_runtime.sh ${CHROOT_NAME} $(RUNTIME_NAME) $(CHROOT_PERSONALITY)
endif
