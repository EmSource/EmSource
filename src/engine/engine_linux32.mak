ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=engine
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
GCC_ExtraLinkerFlags=-L/usr/lib32 -L/usr/lib
GCC_CustomVersionScript=
EntryPoint=
IgnoreAllDefaultLibraries=no
BufferSecurityCheck=Yes
SymbolVisibility=hidden
TreatWarningsAsErrors=false
OptimizerLevel=$(SAFE_OPTFLAGS_GCC_422)
SystemLibraries=-lrt -lopenal -lcurl-gnutls 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=engine -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DREPLAY_ENABLED -DUSE_CONVARS -DVOICE_OVER_IP -DBUMPMAP -D__USEA3D -D_ADD_EAX_ -DENGINE_DLL -DVERSION_SAFE_STEAM_API_INTERFACES -DUSE_BREAKPAD_HANDLER -DUSE_WEBM_FOR_REPLAY -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/engine -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ./ audio audio/private audio/public ../vgui2/include ../vgui2/controls 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/engine.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/engine.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../common/language.cpp \
    ../common/netmessages.cpp \
    ../common/randoverride.cpp \
    ../common/SourceAppInfo.cpp \
    ../common/steamid.cpp \
    ../common/vgui/vgui_basebudgetpanel.cpp \
    ../common/vgui/vgui_budgetbargraphpanel.cpp \
    ../common/vgui/vgui_budgethistorypanel.cpp \
    ../common/vgui/vgui_budgetpanelshared.cpp \
    ../public/blockingudpsocket.cpp \
    ../public/bsptreedata.cpp \
    ../public/builddisp.cpp \
    ../public/collisionutils.cpp \
    ../public/crtmemdebug.cpp \
    ../public/dispcoll_common.cpp \
    ../public/disp_common.cpp \
    ../public/disp_powerinfo.cpp \
    ../public/dt_recv.cpp \
    ../public/dt_send.cpp \
    ../public/dt_utlvector_common.cpp \
    ../public/dt_utlvector_recv.cpp \
    ../public/dt_utlvector_send.cpp \
    ../public/editor_sendcommand.cpp \
    ../public/filesystem_helpers.cpp \
    ../public/filesystem_init.cpp \
    ../public/lumpfiles.cpp \
    ../public/networkvar.cpp \
    ../public/registry.cpp \
    ../public/scratchpad3d.cpp \
    ../public/sentence.cpp \
    ../public/studio.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/vallocator.cpp \
    ../public/vgui_controls/vgui_controls.cpp \
    ../public/XUnzip.cpp \
    ../public/XZip.cpp \
    audio/audio_pch.cpp \
    audio/private/circularbuffer.cpp \
    audio/private/MPAFile.cpp \
    audio/private/MPAHeader.cpp \
    audio/private/snd_dev_common.cpp \
    audio/private/snd_dev_sdl.cpp \
    audio/private/snd_dma.cpp \
    audio/private/snd_dsp.cpp \
    audio/private/snd_mix.cpp \
    audio/private/snd_mp3_source.cpp \
    audio/private/snd_posix.cpp \
    audio/private/snd_sentence_mixer.cpp \
    audio/private/snd_wave_data.cpp \
    audio/private/snd_wave_mixer.cpp \
    audio/private/snd_wave_mixer_adpcm.cpp \
    audio/private/snd_wave_mixer_mp3.cpp \
    audio/private/snd_wave_source.cpp \
    audio/private/snd_wave_temp.cpp \
    audio/private/snd_win.cpp \
    audio/private/VBRHeader.cpp \
    audio/private/voice.cpp \
    audio/private/voice_gain.cpp \
    audio/private/voice_mixer_controls_openal.cpp \
    audio/private/voice_record_openal.cpp \
    audio/private/voice_sound_engine_interface.cpp \
    audio/private/voice_wavefile.cpp \
    audio/private/vox.cpp \
    baseautocompletefilelist.cpp \
    baseclient.cpp \
    baseclientstate.cpp \
    baseserver.cpp \
    bitbuf_errorhandler.cpp \
    bugreporter.cpp \
    buildcubemaps.cpp \
    cbenchmark.cpp \
    ccs.cpp \
    cdll_engine_int.cpp \
    changeframelist.cpp \
    cheatcodes.cpp \
    checksum_engine.cpp \
    client.cpp \
    clientframe.cpp \
    client_pch.cpp \
    clockdriftmgr.cpp \
    cl_bounded_cvars.cpp \
    cl_check_process.cpp \
    cl_demo.cpp \
    cl_demoaction.cpp \
    cl_demoactioneditors.cpp \
    cl_demoactionmanager.cpp \
    cl_demoaction_types.cpp \
    cl_demoeditorpanel.cpp \
    cl_demosmootherpanel.cpp \
    cl_demouipanel.cpp \
    cl_entityreport.cpp \
    cl_ents_parse.cpp \
    cl_foguipanel.cpp \
    cl_localnetworkbackdoor.cpp \
    cl_main.cpp \
    cl_parse_event.cpp \
    cl_pluginhelpers.cpp \
    cl_pred.cpp \
    cl_rcon.cpp \
    cl_steamauth.cpp \
    cl_texturelistpanel.cpp \
    cl_txviewpanel.cpp \
    cmd.cpp \
    cmodel.cpp \
    cmodel_bsp.cpp \
    cmodel_disp.cpp \
    colorcorrectionpanel.cpp \
    common.cpp \
    console.cpp \
    cvar.cpp \
    debugoverlay.cpp \
    debug_leafvis.cpp \
    decals.cpp \
    decal_clip.cpp \
    demofile.cpp \
    DevShotGenerator.cpp \
    disp.cpp \
    disp_defs.cpp \
    disp_helpers.cpp \
    disp_interface.cpp \
    disp_mapload.cpp \
    download.cpp \
    DownloadListGenerator.cpp \
    downloadthread.cpp \
    dt.cpp \
    dt_common_eng.cpp \
    dt_encode.cpp \
    dt_instrumentation.cpp \
    dt_instrumentation_server.cpp \
    dt_localtransfer.cpp \
    dt_recv_decoder.cpp \
    dt_recv_eng.cpp \
    dt_send_eng.cpp \
    dt_stack.cpp \
    dt_test.cpp \
    enginesingleuserfilter.cpp \
    EngineSoundClient.cpp \
    EngineSoundServer.cpp \
    enginestats.cpp \
    enginethreads.cpp \
    enginetool.cpp \
    enginetrace.cpp \
    engine_replay_int.cpp \
    engsoundservice.cpp \
    filesystem_engine.cpp \
    filetransfermgr.cpp \
    GameEventManager.cpp \
    GameEventManagerOld.cpp \
    gametrace_engine.cpp \
    gl_draw.cpp \
    gl_drawlights.cpp \
    gl_lightmap.cpp \
    gl_matsysiface.cpp \
    gl_rlight.cpp \
    gl_rmain.cpp \
    gl_rmisc.cpp \
    gl_rsurf.cpp \
    gl_screen.cpp \
    gl_shader.cpp \
    gl_warp.cpp \
    hltvclient.cpp \
    hltvclientstate.cpp \
    hltvdemo.cpp \
    hltvserver.cpp \
    hltvtest.cpp \
    host.cpp \
    host_cmd.cpp \
    host_listmaps.cpp \
    host_phonehome.cpp \
    host_saverestore.cpp \
    host_state.cpp \
    initmathlib.cpp \
    keys.cpp \
    lightcache.cpp \
    LoadScreenUpdate.cpp \
    LocalNetworkBackdoor.cpp \
    l_studio.cpp \
    MapReslistGenerator.cpp \
    matchmakingclient.cpp \
    matchmakinghost.cpp \
    matchmakingmigrate.cpp \
    matchmakingqos.cpp \
    matchmakingshared.cpp \
    materialproxyfactory.cpp \
    matsys_interface.cpp \
    mem_fgets.cpp \
    ModelInfo.cpp \
    modelloader.cpp \
    mod_vis.cpp \
    networkstringtable.cpp \
    networkstringtableclient.cpp \
    NetworkStringTableItem.cpp \
    networkstringtableserver.cpp \
    net_chan.cpp \
    net_synctags.cpp \
    net_ws.cpp \
    net_ws_queued_packet_sender.cpp \
    OcclusionSystem.cpp \
    Overlay.cpp \
    packed_entity.cpp \
    perfuipanel.cpp \
    precache.cpp \
    pr_edict.cpp \
    pure_server.cpp \
    quakedef.cpp \
    randomstream.cpp \
    render_pch.cpp \
    replaydemo.cpp \
    replaydemoplayer.cpp \
    replayserver.cpp \
    replay_internal.cpp \
    rpt_engine.cpp \
    r_areaportal.cpp \
    r_decal.cpp \
    r_efx.cpp \
    r_linefile.cpp \
    saverestore_filesystem.cpp \
    servermsghandler.cpp \
    server_pch.cpp \
    Session.cpp \
    shadowmgr.cpp \
    snd_io.cpp \
    socketcreator.cpp \
    sound_shared.cpp \
    spatialpartition.cpp \
    staticpropmgr.cpp \
    sv_client.cpp \
    sv_ents_write.cpp \
    sv_filter.cpp \
    sv_framesnapshot.cpp \
    sv_ipratelimit.cpp \
    sv_log.cpp \
    sv_main.cpp \
    sv_packedentities.cpp \
    sv_plugin.cpp \
    sv_precache.cpp \
    sv_rcon.cpp \
    sv_redirect.cpp \
    sv_remoteaccess.cpp \
    sv_steamauth.cpp \
    sv_uploaddata.cpp \
    sv_uploadgamestats.cpp \
    sys_dll.cpp \
    sys_dll2.cpp \
    sys_engine.cpp \
    sys_getmodes.cpp \
    sys_linuxwind.cpp \
    sys_mainwind.cpp \
    testscriptmgr.cpp \
    tmessage.cpp \
    toolframework.cpp \
    traceinit.cpp \
    vengineserver_impl.cpp \
    vgui_askconnectpanel.cpp \
    vgui_basepanel.cpp \
    vgui_baseui_interface.cpp \
    vgui_budgetpanel.cpp \
    vgui_DebugSystemPanel.cpp \
    vgui_drawtreepanel.cpp \
    vgui_helpers.cpp \
    vgui_texturebudgetpanel.cpp \
    vgui_vprofgraphpanel.cpp \
    vgui_vprofpanel.cpp \
    view.cpp \
    voiceserver_impl.cpp \
    vprof_engine.cpp \
    vprof_record.cpp \
    world.cpp \
    xboxsystem.cpp \
    zone.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/common/linux32/replay_common.a \
    ../lib/public/linux32/appframework.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/common/linux32/bzip2.a \
    ../lib/common/linux32/libjpeg.a \
    ../lib/public/linux32/dmxloader.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/matsys_controls.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vtf.a \
    ../lib/public/linux32/vgui_controls.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lSDL2 \


LIBFILENAMES = \
    ../lib/common/linux32/bzip2.a \
    ../lib/common/linux32/libjpeg.a \
    ../lib/common/linux32/replay_common.a \
    ../lib/public/linux32/appframework.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/dmxloader.a \
    ../lib/public/linux32/libSDL2.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/matsys_controls.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/vtf.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/language.P
endif

$(OBJ_DIR)/language.o : $(abspath ../common/language.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/netmessages.P
endif

$(OBJ_DIR)/netmessages.o : $(abspath ../common/netmessages.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/randoverride.P
endif

$(OBJ_DIR)/randoverride.o : $(abspath ../common/randoverride.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SourceAppInfo.P
endif

$(OBJ_DIR)/SourceAppInfo.o : $(abspath ../common/SourceAppInfo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamid.P
endif

$(OBJ_DIR)/steamid.o : $(abspath ../common/steamid.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_basebudgetpanel.P
endif

$(OBJ_DIR)/vgui_basebudgetpanel.o : $(abspath ../common/vgui/vgui_basebudgetpanel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_budgetbargraphpanel.P
endif

$(OBJ_DIR)/vgui_budgetbargraphpanel.o : $(abspath ../common/vgui/vgui_budgetbargraphpanel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_budgethistorypanel.P
endif

$(OBJ_DIR)/vgui_budgethistorypanel.o : $(abspath ../common/vgui/vgui_budgethistorypanel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_budgetpanelshared.P
endif

$(OBJ_DIR)/vgui_budgetpanelshared.o : $(abspath ../common/vgui/vgui_budgetpanelshared.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/blockingudpsocket.P
endif

$(OBJ_DIR)/blockingudpsocket.o : $(abspath ../public/blockingudpsocket.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bsptreedata.P
endif

$(OBJ_DIR)/bsptreedata.o : $(abspath ../public/bsptreedata.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/builddisp.P
endif

$(OBJ_DIR)/builddisp.o : $(abspath ../public/builddisp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionutils.P
endif

$(OBJ_DIR)/collisionutils.o : $(abspath ../public/collisionutils.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/crtmemdebug.P
endif

$(OBJ_DIR)/crtmemdebug.o : $(abspath ../public/crtmemdebug.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dispcoll_common.P
endif

$(OBJ_DIR)/dispcoll_common.o : $(abspath ../public/dispcoll_common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_common.P
endif

$(OBJ_DIR)/disp_common.o : $(abspath ../public/disp_common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_powerinfo.P
endif

$(OBJ_DIR)/disp_powerinfo.o : $(abspath ../public/disp_powerinfo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_recv.P
endif

$(OBJ_DIR)/dt_recv.o : $(abspath ../public/dt_recv.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_send.P
endif

$(OBJ_DIR)/dt_send.o : $(abspath ../public/dt_send.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_common.P
endif

$(OBJ_DIR)/dt_utlvector_common.o : $(abspath ../public/dt_utlvector_common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_recv.P
endif

$(OBJ_DIR)/dt_utlvector_recv.o : $(abspath ../public/dt_utlvector_recv.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_send.P
endif

$(OBJ_DIR)/dt_utlvector_send.o : $(abspath ../public/dt_utlvector_send.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/editor_sendcommand.P
endif

$(OBJ_DIR)/editor_sendcommand.o : $(abspath ../public/editor_sendcommand.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../public/filesystem_helpers.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_init.P
endif

$(OBJ_DIR)/filesystem_init.o : $(abspath ../public/filesystem_init.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lumpfiles.P
endif

$(OBJ_DIR)/lumpfiles.o : $(abspath ../public/lumpfiles.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkvar.P
endif

$(OBJ_DIR)/networkvar.o : $(abspath ../public/networkvar.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/registry.P
endif

$(OBJ_DIR)/registry.o : $(abspath ../public/registry.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scratchpad3d.P
endif

$(OBJ_DIR)/scratchpad3d.o : $(abspath ../public/scratchpad3d.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sentence.P
endif

$(OBJ_DIR)/sentence.o : $(abspath ../public/sentence.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio.P
endif

$(OBJ_DIR)/studio.o : $(abspath ../public/studio.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vallocator.P
endif

$(OBJ_DIR)/vallocator.o : $(abspath ../public/vallocator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../public/vgui_controls/vgui_controls.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/XUnzip.P
endif

$(OBJ_DIR)/XUnzip.o : $(abspath ../public/XUnzip.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/XZip.P
endif

$(OBJ_DIR)/XZip.o : $(abspath ../public/XZip.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/audio_pch.P
endif

$(OBJ_DIR)/audio_pch.h.gch : audio/audio_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/audio_pch.h.P : $(OBJ_DIR)/audio_pch.h.gch

vpath audio/audio_pch.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/audio_pch.h.P
endif

$(OBJ_DIR)/audio_pch.h : audio/audio_pch.h $(OBJ_DIR)/audio_pch.h.gch $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/audio_pch.h

$(OBJ_DIR)/audio_pch.o : $(abspath audio/audio_pch.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/circularbuffer.P
endif

$(OBJ_DIR)/circularbuffer.o : $(abspath audio/private/circularbuffer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MPAFile.P
endif

$(OBJ_DIR)/MPAFile.o : $(abspath audio/private/MPAFile.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MPAHeader.P
endif

$(OBJ_DIR)/MPAHeader.o : $(abspath audio/private/MPAHeader.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_dev_common.P
endif

$(OBJ_DIR)/snd_dev_common.o : $(abspath audio/private/snd_dev_common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_dev_sdl.P
endif

$(OBJ_DIR)/snd_dev_sdl.o : $(abspath audio/private/snd_dev_sdl.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_dma.P
endif

$(OBJ_DIR)/snd_dma.o : $(abspath audio/private/snd_dma.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_dsp.P
endif

$(OBJ_DIR)/snd_dsp.o : $(abspath audio/private/snd_dsp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_mix.P
endif

$(OBJ_DIR)/snd_mix.o : $(abspath audio/private/snd_mix.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_mp3_source.P
endif

$(OBJ_DIR)/snd_mp3_source.o : $(abspath audio/private/snd_mp3_source.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_posix.P
endif

$(OBJ_DIR)/snd_posix.o : $(abspath audio/private/snd_posix.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_sentence_mixer.P
endif

$(OBJ_DIR)/snd_sentence_mixer.o : $(abspath audio/private/snd_sentence_mixer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_data.P
endif

$(OBJ_DIR)/snd_wave_data.o : $(abspath audio/private/snd_wave_data.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_mixer.P
endif

$(OBJ_DIR)/snd_wave_mixer.o : $(abspath audio/private/snd_wave_mixer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_mixer_adpcm.P
endif

$(OBJ_DIR)/snd_wave_mixer_adpcm.o : $(abspath audio/private/snd_wave_mixer_adpcm.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_mixer_mp3.P
endif

$(OBJ_DIR)/snd_wave_mixer_mp3.o : $(abspath audio/private/snd_wave_mixer_mp3.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_source.P
endif

$(OBJ_DIR)/snd_wave_source.o : $(abspath audio/private/snd_wave_source.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_temp.P
endif

$(OBJ_DIR)/snd_wave_temp.o : $(abspath audio/private/snd_wave_temp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_win.P
endif

$(OBJ_DIR)/snd_win.o : $(abspath audio/private/snd_win.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/VBRHeader.P
endif

$(OBJ_DIR)/VBRHeader.o : $(abspath audio/private/VBRHeader.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice.P
endif

$(OBJ_DIR)/voice.o : $(abspath audio/private/voice.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_gain.P
endif

$(OBJ_DIR)/voice_gain.o : $(abspath audio/private/voice_gain.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_mixer_controls_openal.P
endif

$(OBJ_DIR)/voice_mixer_controls_openal.o : $(abspath audio/private/voice_mixer_controls_openal.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_record_openal.P
endif

$(OBJ_DIR)/voice_record_openal.o : $(abspath audio/private/voice_record_openal.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_sound_engine_interface.P
endif

$(OBJ_DIR)/voice_sound_engine_interface.o : $(abspath audio/private/voice_sound_engine_interface.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_wavefile.P
endif

$(OBJ_DIR)/voice_wavefile.o : $(abspath audio/private/voice_wavefile.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vox.P
endif

$(OBJ_DIR)/vox.o : $(abspath audio/private/vox.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseautocompletefilelist.P
endif

$(OBJ_DIR)/baseautocompletefilelist.o : $(abspath baseautocompletefilelist.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseclient.P
endif

$(OBJ_DIR)/baseclient.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/baseclient.o : $(abspath baseclient.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseclientstate.P
endif

$(OBJ_DIR)/baseclientstate.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/baseclientstate.o : $(abspath baseclientstate.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseserver.P
endif

$(OBJ_DIR)/baseserver.o : $(abspath baseserver.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bitbuf_errorhandler.P
endif

$(OBJ_DIR)/bitbuf_errorhandler.o : $(abspath bitbuf_errorhandler.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bugreporter.P
endif

$(OBJ_DIR)/bugreporter.o : $(abspath bugreporter.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/buildcubemaps.P
endif

$(OBJ_DIR)/buildcubemaps.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/buildcubemaps.o : $(abspath buildcubemaps.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cbenchmark.P
endif

$(OBJ_DIR)/cbenchmark.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cbenchmark.o : $(abspath cbenchmark.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ccs.P
endif

$(OBJ_DIR)/ccs.o : $(abspath ccs.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_engine_int.P
endif

$(OBJ_DIR)/cdll_engine_int.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cdll_engine_int.o : $(abspath cdll_engine_int.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/changeframelist.P
endif

$(OBJ_DIR)/changeframelist.o : $(abspath changeframelist.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cheatcodes.P
endif

$(OBJ_DIR)/cheatcodes.o : $(abspath cheatcodes.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/checksum_engine.P
endif

$(OBJ_DIR)/checksum_engine.o : $(abspath checksum_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client.P
endif

$(OBJ_DIR)/client.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/client.o : $(abspath client.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientframe.P
endif

$(OBJ_DIR)/clientframe.o : $(abspath clientframe.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_pch.P
endif

$(OBJ_DIR)/client_pch.h.gch : client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/client_pch.h.P : $(OBJ_DIR)/client_pch.h.gch

vpath client_pch.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/client_pch.h.P
endif

$(OBJ_DIR)/client_pch.h : client_pch.h $(OBJ_DIR)/client_pch.h.gch $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/client_pch.h

$(OBJ_DIR)/client_pch.o : $(abspath client_pch.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clockdriftmgr.P
endif

$(OBJ_DIR)/clockdriftmgr.o : $(abspath clockdriftmgr.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_bounded_cvars.P
endif

$(OBJ_DIR)/cl_bounded_cvars.o : $(abspath cl_bounded_cvars.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_check_process.P
endif

$(OBJ_DIR)/cl_check_process.o : $(abspath cl_check_process.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demo.P
endif

$(OBJ_DIR)/cl_demo.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demo.o : $(abspath cl_demo.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoaction.P
endif

$(OBJ_DIR)/cl_demoaction.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoaction.o : $(abspath cl_demoaction.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoactioneditors.P
endif

$(OBJ_DIR)/cl_demoactioneditors.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoactioneditors.o : $(abspath cl_demoactioneditors.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoactionmanager.P
endif

$(OBJ_DIR)/cl_demoactionmanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoactionmanager.o : $(abspath cl_demoactionmanager.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoaction_types.P
endif

$(OBJ_DIR)/cl_demoaction_types.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoaction_types.o : $(abspath cl_demoaction_types.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoeditorpanel.P
endif

$(OBJ_DIR)/cl_demoeditorpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoeditorpanel.o : $(abspath cl_demoeditorpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demosmootherpanel.P
endif

$(OBJ_DIR)/cl_demosmootherpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demosmootherpanel.o : $(abspath cl_demosmootherpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demouipanel.P
endif

$(OBJ_DIR)/cl_demouipanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demouipanel.o : $(abspath cl_demouipanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_entityreport.P
endif

$(OBJ_DIR)/cl_entityreport.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_entityreport.o : $(abspath cl_entityreport.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_ents_parse.P
endif

$(OBJ_DIR)/cl_ents_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_ents_parse.o : $(abspath cl_ents_parse.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_foguipanel.P
endif

$(OBJ_DIR)/cl_foguipanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_foguipanel.o : $(abspath cl_foguipanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_localnetworkbackdoor.P
endif

$(OBJ_DIR)/cl_localnetworkbackdoor.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_localnetworkbackdoor.o : $(abspath cl_localnetworkbackdoor.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_main.P
endif

$(OBJ_DIR)/cl_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_main.o : $(abspath cl_main.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_parse_event.P
endif

$(OBJ_DIR)/cl_parse_event.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_parse_event.o : $(abspath cl_parse_event.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_pluginhelpers.P
endif

$(OBJ_DIR)/cl_pluginhelpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_pluginhelpers.o : $(abspath cl_pluginhelpers.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_pred.P
endif

$(OBJ_DIR)/cl_pred.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_pred.o : $(abspath cl_pred.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_rcon.P
endif

$(OBJ_DIR)/cl_rcon.o : $(abspath cl_rcon.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_steamauth.P
endif

$(OBJ_DIR)/cl_steamauth.o : $(abspath cl_steamauth.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_texturelistpanel.P
endif

$(OBJ_DIR)/cl_texturelistpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_texturelistpanel.o : $(abspath cl_texturelistpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_txviewpanel.P
endif

$(OBJ_DIR)/cl_txviewpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_txviewpanel.o : $(abspath cl_txviewpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmd.P
endif

$(OBJ_DIR)/cmd.o : $(abspath cmd.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmodel.P
endif

$(OBJ_DIR)/cmodel.o : $(abspath cmodel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmodel_bsp.P
endif

$(OBJ_DIR)/cmodel_bsp.o : $(abspath cmodel_bsp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmodel_disp.P
endif

$(OBJ_DIR)/cmodel_disp.o : $(abspath cmodel_disp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrectionpanel.P
endif

$(OBJ_DIR)/colorcorrectionpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/colorcorrectionpanel.o : $(abspath colorcorrectionpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/common.P
endif

$(OBJ_DIR)/common.o : $(abspath common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/console.P
endif

$(OBJ_DIR)/console.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/console.o : $(abspath console.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cvar.P
endif

$(OBJ_DIR)/cvar.o : $(abspath cvar.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugoverlay.P
endif

$(OBJ_DIR)/debugoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/debugoverlay.o : $(abspath debugoverlay.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debug_leafvis.P
endif

$(OBJ_DIR)/debug_leafvis.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/debug_leafvis.o : $(abspath debug_leafvis.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/decals.P
endif

$(OBJ_DIR)/decals.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/decals.o : $(abspath decals.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/decal_clip.P
endif

$(OBJ_DIR)/decal_clip.o : $(abspath decal_clip.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/demofile.P
endif

$(OBJ_DIR)/demofile.o : $(abspath demofile.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DevShotGenerator.P
endif

$(OBJ_DIR)/DevShotGenerator.o : $(abspath DevShotGenerator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp.P
endif

$(OBJ_DIR)/disp.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/disp.o : $(abspath disp.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_defs.P
endif

$(OBJ_DIR)/disp_defs.o : $(abspath disp_defs.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_helpers.P
endif

$(OBJ_DIR)/disp_helpers.o : $(abspath disp_helpers.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_interface.P
endif

$(OBJ_DIR)/disp_interface.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/disp_interface.o : $(abspath disp_interface.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_mapload.P
endif

$(OBJ_DIR)/disp_mapload.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/disp_mapload.o : $(abspath disp_mapload.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/download.P
endif

$(OBJ_DIR)/download.o : $(abspath download.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DownloadListGenerator.P
endif

$(OBJ_DIR)/DownloadListGenerator.o : $(abspath DownloadListGenerator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/downloadthread.P
endif

$(OBJ_DIR)/downloadthread.o : $(abspath downloadthread.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt.P
endif

$(OBJ_DIR)/dt.o : $(abspath dt.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_common_eng.P
endif

$(OBJ_DIR)/dt_common_eng.o : $(abspath dt_common_eng.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_encode.P
endif

$(OBJ_DIR)/dt_encode.o : $(abspath dt_encode.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_instrumentation.P
endif

$(OBJ_DIR)/dt_instrumentation.o : $(abspath dt_instrumentation.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_instrumentation_server.P
endif

$(OBJ_DIR)/dt_instrumentation_server.o : $(abspath dt_instrumentation_server.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_localtransfer.P
endif

$(OBJ_DIR)/dt_localtransfer.o : $(abspath dt_localtransfer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_recv_decoder.P
endif

$(OBJ_DIR)/dt_recv_decoder.o : $(abspath dt_recv_decoder.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_recv_eng.P
endif

$(OBJ_DIR)/dt_recv_eng.o : $(abspath dt_recv_eng.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_send_eng.P
endif

$(OBJ_DIR)/dt_send_eng.o : $(abspath dt_send_eng.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_stack.P
endif

$(OBJ_DIR)/dt_stack.o : $(abspath dt_stack.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_test.P
endif

$(OBJ_DIR)/dt_test.o : $(abspath dt_test.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginesingleuserfilter.P
endif

$(OBJ_DIR)/enginesingleuserfilter.o : $(abspath enginesingleuserfilter.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EngineSoundClient.P
endif

$(OBJ_DIR)/EngineSoundClient.o : $(abspath EngineSoundClient.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EngineSoundServer.P
endif

$(OBJ_DIR)/EngineSoundServer.o : $(abspath EngineSoundServer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginestats.P
endif

$(OBJ_DIR)/enginestats.o : $(abspath enginestats.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginethreads.P
endif

$(OBJ_DIR)/enginethreads.o : $(abspath enginethreads.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginetool.P
endif

$(OBJ_DIR)/enginetool.o : $(abspath enginetool.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginetrace.P
endif

$(OBJ_DIR)/enginetrace.o : $(abspath enginetrace.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/engine_replay_int.P
endif

$(OBJ_DIR)/engine_replay_int.o : $(abspath engine_replay_int.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/engsoundservice.P
endif

$(OBJ_DIR)/engsoundservice.o : $(abspath engsoundservice.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_engine.P
endif

$(OBJ_DIR)/filesystem_engine.o : $(abspath filesystem_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filetransfermgr.P
endif

$(OBJ_DIR)/filetransfermgr.o : $(abspath filetransfermgr.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameEventManager.P
endif

$(OBJ_DIR)/GameEventManager.o : $(abspath GameEventManager.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameEventManagerOld.P
endif

$(OBJ_DIR)/GameEventManagerOld.o : $(abspath GameEventManagerOld.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gametrace_engine.P
endif

$(OBJ_DIR)/gametrace_engine.o : $(abspath gametrace_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_draw.P
endif

$(OBJ_DIR)/gl_draw.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_draw.o : $(abspath gl_draw.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_drawlights.P
endif

$(OBJ_DIR)/gl_drawlights.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_drawlights.o : $(abspath gl_drawlights.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_lightmap.P
endif

$(OBJ_DIR)/gl_lightmap.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_lightmap.o : $(abspath gl_lightmap.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_matsysiface.P
endif

$(OBJ_DIR)/gl_matsysiface.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_matsysiface.o : $(abspath gl_matsysiface.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_rlight.P
endif

$(OBJ_DIR)/gl_rlight.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_rlight.o : $(abspath gl_rlight.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_rmain.P
endif

$(OBJ_DIR)/gl_rmain.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_rmain.o : $(abspath gl_rmain.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_rmisc.P
endif

$(OBJ_DIR)/gl_rmisc.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_rmisc.o : $(abspath gl_rmisc.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_rsurf.P
endif

$(OBJ_DIR)/gl_rsurf.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_rsurf.o : $(abspath gl_rsurf.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_screen.P
endif

$(OBJ_DIR)/gl_screen.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_screen.o : $(abspath gl_screen.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_shader.P
endif

$(OBJ_DIR)/gl_shader.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_shader.o : $(abspath gl_shader.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_warp.P
endif

$(OBJ_DIR)/gl_warp.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_warp.o : $(abspath gl_warp.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvclient.P
endif

$(OBJ_DIR)/hltvclient.o : $(abspath hltvclient.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvclientstate.P
endif

$(OBJ_DIR)/hltvclientstate.o : $(abspath hltvclientstate.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvdemo.P
endif

$(OBJ_DIR)/hltvdemo.o : $(abspath hltvdemo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvserver.P
endif

$(OBJ_DIR)/hltvserver.o : $(abspath hltvserver.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvtest.P
endif

$(OBJ_DIR)/hltvtest.o : $(abspath hltvtest.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host.P
endif

$(OBJ_DIR)/host.o : $(abspath host.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_cmd.P
endif

$(OBJ_DIR)/host_cmd.o : $(abspath host_cmd.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_listmaps.P
endif

$(OBJ_DIR)/host_listmaps.o : $(abspath host_listmaps.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_phonehome.P
endif

$(OBJ_DIR)/host_phonehome.o : $(abspath host_phonehome.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_saverestore.P
endif

$(OBJ_DIR)/host_saverestore.o : $(abspath host_saverestore.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_state.P
endif

$(OBJ_DIR)/host_state.o : $(abspath host_state.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/initmathlib.P
endif

$(OBJ_DIR)/initmathlib.o : $(abspath initmathlib.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/keys.P
endif

$(OBJ_DIR)/keys.o : $(abspath keys.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightcache.P
endif

$(OBJ_DIR)/lightcache.o : $(abspath lightcache.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadScreenUpdate.P
endif

$(OBJ_DIR)/LoadScreenUpdate.o : $(abspath LoadScreenUpdate.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LocalNetworkBackdoor.P
endif

$(OBJ_DIR)/LocalNetworkBackdoor.o : $(abspath LocalNetworkBackdoor.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/l_studio.P
endif

$(OBJ_DIR)/l_studio.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/l_studio.o : $(abspath l_studio.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MapReslistGenerator.P
endif

$(OBJ_DIR)/MapReslistGenerator.o : $(abspath MapReslistGenerator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingclient.P
endif

$(OBJ_DIR)/matchmakingclient.o : $(abspath matchmakingclient.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakinghost.P
endif

$(OBJ_DIR)/matchmakinghost.o : $(abspath matchmakinghost.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingmigrate.P
endif

$(OBJ_DIR)/matchmakingmigrate.o : $(abspath matchmakingmigrate.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingqos.P
endif

$(OBJ_DIR)/matchmakingqos.o : $(abspath matchmakingqos.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingshared.P
endif

$(OBJ_DIR)/matchmakingshared.o : $(abspath matchmakingshared.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/materialproxyfactory.P
endif

$(OBJ_DIR)/materialproxyfactory.o : $(abspath materialproxyfactory.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matsys_interface.P
endif

$(OBJ_DIR)/matsys_interface.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/matsys_interface.o : $(abspath matsys_interface.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mem_fgets.P
endif

$(OBJ_DIR)/mem_fgets.o : $(abspath mem_fgets.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ModelInfo.P
endif

$(OBJ_DIR)/ModelInfo.o : $(abspath ModelInfo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/modelloader.P
endif

$(OBJ_DIR)/modelloader.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/modelloader.o : $(abspath modelloader.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mod_vis.P
endif

$(OBJ_DIR)/mod_vis.o : $(abspath mod_vis.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkstringtable.P
endif

$(OBJ_DIR)/networkstringtable.o : $(abspath networkstringtable.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkstringtableclient.P
endif

$(OBJ_DIR)/networkstringtableclient.o : $(abspath networkstringtableclient.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/NetworkStringTableItem.P
endif

$(OBJ_DIR)/NetworkStringTableItem.o : $(abspath NetworkStringTableItem.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkstringtableserver.P
endif

$(OBJ_DIR)/networkstringtableserver.o : $(abspath networkstringtableserver.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/net_chan.P
endif

$(OBJ_DIR)/net_chan.o : $(abspath net_chan.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/net_synctags.P
endif

$(OBJ_DIR)/net_synctags.o : $(abspath net_synctags.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/net_ws.P
endif

$(OBJ_DIR)/net_ws.o : $(abspath net_ws.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/net_ws_queued_packet_sender.P
endif

$(OBJ_DIR)/net_ws_queued_packet_sender.o : $(abspath net_ws_queued_packet_sender.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OcclusionSystem.P
endif

$(OBJ_DIR)/OcclusionSystem.o : $(abspath OcclusionSystem.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Overlay.P
endif

$(OBJ_DIR)/Overlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/Overlay.o : $(abspath Overlay.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/packed_entity.P
endif

$(OBJ_DIR)/packed_entity.o : $(abspath packed_entity.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/perfuipanel.P
endif

$(OBJ_DIR)/perfuipanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/perfuipanel.o : $(abspath perfuipanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/precache.P
endif

$(OBJ_DIR)/precache.o : $(abspath precache.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pr_edict.P
endif

$(OBJ_DIR)/pr_edict.o : $(abspath pr_edict.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pure_server.P
endif

$(OBJ_DIR)/pure_server.o : $(abspath pure_server.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/quakedef.P
endif

$(OBJ_DIR)/quakedef.o : $(abspath quakedef.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/randomstream.P
endif

$(OBJ_DIR)/randomstream.o : $(abspath randomstream.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/render_pch.P
endif

$(OBJ_DIR)/render_pch.h.gch : render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/render_pch.h.P : $(OBJ_DIR)/render_pch.h.gch

vpath render_pch.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/render_pch.h.P
endif

$(OBJ_DIR)/render_pch.h : render_pch.h $(OBJ_DIR)/render_pch.h.gch $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/render_pch.h

$(OBJ_DIR)/render_pch.o : $(abspath render_pch.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replaydemo.P
endif

$(OBJ_DIR)/replaydemo.o : $(abspath replaydemo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replaydemoplayer.P
endif

$(OBJ_DIR)/replaydemoplayer.o : $(abspath replaydemoplayer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replayserver.P
endif

$(OBJ_DIR)/replayserver.o : $(abspath replayserver.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replay_internal.P
endif

$(OBJ_DIR)/replay_internal.o : $(abspath replay_internal.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rpt_engine.P
endif

$(OBJ_DIR)/rpt_engine.o : $(abspath rpt_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/r_areaportal.P
endif

$(OBJ_DIR)/r_areaportal.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/r_areaportal.o : $(abspath r_areaportal.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/r_decal.P
endif

$(OBJ_DIR)/r_decal.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/r_decal.o : $(abspath r_decal.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/r_efx.P
endif

$(OBJ_DIR)/r_efx.o : $(abspath r_efx.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/r_linefile.P
endif

$(OBJ_DIR)/r_linefile.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/r_linefile.o : $(abspath r_linefile.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/saverestore_filesystem.P
endif

$(OBJ_DIR)/saverestore_filesystem.o : $(abspath saverestore_filesystem.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/servermsghandler.P
endif

$(OBJ_DIR)/servermsghandler.o : $(abspath servermsghandler.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/server_pch.P
endif

$(OBJ_DIR)/server_pch.h.gch : server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/server_pch.h.P : $(OBJ_DIR)/server_pch.h.gch

vpath server_pch.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/server_pch.h.P
endif

$(OBJ_DIR)/server_pch.h : server_pch.h $(OBJ_DIR)/server_pch.h.gch $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/server_pch.h

$(OBJ_DIR)/server_pch.o : $(abspath server_pch.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Session.P
endif

$(OBJ_DIR)/Session.o : $(abspath Session.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadowmgr.P
endif

$(OBJ_DIR)/shadowmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/shadowmgr.o : $(abspath shadowmgr.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_io.P
endif

$(OBJ_DIR)/snd_io.o : $(abspath snd_io.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/socketcreator.P
endif

$(OBJ_DIR)/socketcreator.o : $(abspath socketcreator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sound_shared.P
endif

$(OBJ_DIR)/sound_shared.o : $(abspath sound_shared.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spatialpartition.P
endif

$(OBJ_DIR)/spatialpartition.o : $(abspath spatialpartition.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/staticpropmgr.P
endif

$(OBJ_DIR)/staticpropmgr.o : $(abspath staticpropmgr.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_client.P
endif

$(OBJ_DIR)/sv_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_client.o : $(abspath sv_client.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_ents_write.P
endif

$(OBJ_DIR)/sv_ents_write.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_ents_write.o : $(abspath sv_ents_write.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_filter.P
endif

$(OBJ_DIR)/sv_filter.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_filter.o : $(abspath sv_filter.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_framesnapshot.P
endif

$(OBJ_DIR)/sv_framesnapshot.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_framesnapshot.o : $(abspath sv_framesnapshot.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_ipratelimit.P
endif

$(OBJ_DIR)/sv_ipratelimit.o : $(abspath sv_ipratelimit.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_log.P
endif

$(OBJ_DIR)/sv_log.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_log.o : $(abspath sv_log.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_main.P
endif

$(OBJ_DIR)/sv_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_main.o : $(abspath sv_main.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_packedentities.P
endif

$(OBJ_DIR)/sv_packedentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_packedentities.o : $(abspath sv_packedentities.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_plugin.P
endif

$(OBJ_DIR)/sv_plugin.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_plugin.o : $(abspath sv_plugin.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_precache.P
endif

$(OBJ_DIR)/sv_precache.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_precache.o : $(abspath sv_precache.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_rcon.P
endif

$(OBJ_DIR)/sv_rcon.o : $(abspath sv_rcon.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_redirect.P
endif

$(OBJ_DIR)/sv_redirect.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_redirect.o : $(abspath sv_redirect.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_remoteaccess.P
endif

$(OBJ_DIR)/sv_remoteaccess.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_remoteaccess.o : $(abspath sv_remoteaccess.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_steamauth.P
endif

$(OBJ_DIR)/sv_steamauth.o : $(abspath sv_steamauth.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_uploaddata.P
endif

$(OBJ_DIR)/sv_uploaddata.o : $(abspath sv_uploaddata.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_uploadgamestats.P
endif

$(OBJ_DIR)/sv_uploadgamestats.o : $(abspath sv_uploadgamestats.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_dll.P
endif

$(OBJ_DIR)/sys_dll.o : $(abspath sys_dll.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_dll2.P
endif

$(OBJ_DIR)/sys_dll2.o : $(abspath sys_dll2.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_engine.P
endif

$(OBJ_DIR)/sys_engine.o : $(abspath sys_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_getmodes.P
endif

$(OBJ_DIR)/sys_getmodes.o : $(abspath sys_getmodes.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_linuxwind.P
endif

$(OBJ_DIR)/sys_linuxwind.o : $(abspath sys_linuxwind.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_mainwind.P
endif

$(OBJ_DIR)/sys_mainwind.o : $(abspath sys_mainwind.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/testscriptmgr.P
endif

$(OBJ_DIR)/testscriptmgr.o : $(abspath testscriptmgr.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tmessage.P
endif

$(OBJ_DIR)/tmessage.o : $(abspath tmessage.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/toolframework.P
endif

$(OBJ_DIR)/toolframework.o : $(abspath toolframework.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/traceinit.P
endif

$(OBJ_DIR)/traceinit.o : $(abspath traceinit.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vengineserver_impl.P
endif

$(OBJ_DIR)/vengineserver_impl.o : $(abspath vengineserver_impl.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_askconnectpanel.P
endif

$(OBJ_DIR)/vgui_askconnectpanel.o : $(abspath vgui_askconnectpanel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_basepanel.P
endif

$(OBJ_DIR)/vgui_basepanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_basepanel.o : $(abspath vgui_basepanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_baseui_interface.P
endif

$(OBJ_DIR)/vgui_baseui_interface.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_baseui_interface.o : $(abspath vgui_baseui_interface.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_budgetpanel.P
endif

$(OBJ_DIR)/vgui_budgetpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_budgetpanel.o : $(abspath vgui_budgetpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_DebugSystemPanel.P
endif

$(OBJ_DIR)/vgui_DebugSystemPanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_DebugSystemPanel.o : $(abspath vgui_DebugSystemPanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_drawtreepanel.P
endif

$(OBJ_DIR)/vgui_drawtreepanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_drawtreepanel.o : $(abspath vgui_drawtreepanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_helpers.P
endif

$(OBJ_DIR)/vgui_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_helpers.o : $(abspath vgui_helpers.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_texturebudgetpanel.P
endif

$(OBJ_DIR)/vgui_texturebudgetpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_texturebudgetpanel.o : $(abspath vgui_texturebudgetpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_vprofgraphpanel.P
endif

$(OBJ_DIR)/vgui_vprofgraphpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_vprofgraphpanel.o : $(abspath vgui_vprofgraphpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_vprofpanel.P
endif

$(OBJ_DIR)/vgui_vprofpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_vprofpanel.o : $(abspath vgui_vprofpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view.P
endif

$(OBJ_DIR)/view.o : $(abspath view.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voiceserver_impl.P
endif

$(OBJ_DIR)/voiceserver_impl.o : $(abspath voiceserver_impl.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vprof_engine.P
endif

$(OBJ_DIR)/vprof_engine.o : $(abspath vprof_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vprof_record.P
endif

$(OBJ_DIR)/vprof_record.o : $(abspath vprof_record.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/world.P
endif

$(OBJ_DIR)/world.o : $(abspath world.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/xboxsystem.P
endif

$(OBJ_DIR)/xboxsystem.o : $(abspath xboxsystem.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/zone.P
endif

$(OBJ_DIR)/zone.o : $(abspath zone.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
GCC_ExtraLinkerFlags=-L/usr/lib32 -L/usr/lib
GCC_CustomVersionScript=
EntryPoint=
IgnoreAllDefaultLibraries=no
BufferSecurityCheck=Yes
SymbolVisibility=hidden
TreatWarningsAsErrors=false
OptimizerLevel=$(SAFE_OPTFLAGS_GCC_422)
SystemLibraries=-lrt -lopenal -lcurl-gnutls 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=engine -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DREPLAY_ENABLED -DUSE_CONVARS -DVOICE_OVER_IP -DBUMPMAP -D__USEA3D -D_ADD_EAX_ -DENGINE_DLL -DVERSION_SAFE_STEAM_API_INTERFACES -DUSE_BREAKPAD_HANDLER -DUSE_WEBM_FOR_REPLAY -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/engine -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ./ audio audio/private audio/public ../vgui2/include ../vgui2/controls 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/engine.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/engine.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../common/language.cpp \
    ../common/netmessages.cpp \
    ../common/randoverride.cpp \
    ../common/SourceAppInfo.cpp \
    ../common/steamid.cpp \
    ../common/vgui/vgui_basebudgetpanel.cpp \
    ../common/vgui/vgui_budgetbargraphpanel.cpp \
    ../common/vgui/vgui_budgethistorypanel.cpp \
    ../common/vgui/vgui_budgetpanelshared.cpp \
    ../public/blockingudpsocket.cpp \
    ../public/bsptreedata.cpp \
    ../public/builddisp.cpp \
    ../public/collisionutils.cpp \
    ../public/crtmemdebug.cpp \
    ../public/dispcoll_common.cpp \
    ../public/disp_common.cpp \
    ../public/disp_powerinfo.cpp \
    ../public/dt_recv.cpp \
    ../public/dt_send.cpp \
    ../public/dt_utlvector_common.cpp \
    ../public/dt_utlvector_recv.cpp \
    ../public/dt_utlvector_send.cpp \
    ../public/editor_sendcommand.cpp \
    ../public/filesystem_helpers.cpp \
    ../public/filesystem_init.cpp \
    ../public/lumpfiles.cpp \
    ../public/networkvar.cpp \
    ../public/registry.cpp \
    ../public/scratchpad3d.cpp \
    ../public/sentence.cpp \
    ../public/studio.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/vallocator.cpp \
    ../public/vgui_controls/vgui_controls.cpp \
    ../public/XUnzip.cpp \
    ../public/XZip.cpp \
    audio/audio_pch.cpp \
    audio/private/circularbuffer.cpp \
    audio/private/MPAFile.cpp \
    audio/private/MPAHeader.cpp \
    audio/private/snd_dev_common.cpp \
    audio/private/snd_dev_sdl.cpp \
    audio/private/snd_dma.cpp \
    audio/private/snd_dsp.cpp \
    audio/private/snd_mix.cpp \
    audio/private/snd_mp3_source.cpp \
    audio/private/snd_posix.cpp \
    audio/private/snd_sentence_mixer.cpp \
    audio/private/snd_wave_data.cpp \
    audio/private/snd_wave_mixer.cpp \
    audio/private/snd_wave_mixer_adpcm.cpp \
    audio/private/snd_wave_mixer_mp3.cpp \
    audio/private/snd_wave_source.cpp \
    audio/private/snd_wave_temp.cpp \
    audio/private/snd_win.cpp \
    audio/private/VBRHeader.cpp \
    audio/private/voice.cpp \
    audio/private/voice_gain.cpp \
    audio/private/voice_mixer_controls_openal.cpp \
    audio/private/voice_record_openal.cpp \
    audio/private/voice_sound_engine_interface.cpp \
    audio/private/voice_wavefile.cpp \
    audio/private/vox.cpp \
    baseautocompletefilelist.cpp \
    baseclient.cpp \
    baseclientstate.cpp \
    baseserver.cpp \
    bitbuf_errorhandler.cpp \
    bugreporter.cpp \
    buildcubemaps.cpp \
    cbenchmark.cpp \
    ccs.cpp \
    cdll_engine_int.cpp \
    changeframelist.cpp \
    cheatcodes.cpp \
    checksum_engine.cpp \
    client.cpp \
    clientframe.cpp \
    client_pch.cpp \
    clockdriftmgr.cpp \
    cl_bounded_cvars.cpp \
    cl_check_process.cpp \
    cl_demo.cpp \
    cl_demoaction.cpp \
    cl_demoactioneditors.cpp \
    cl_demoactionmanager.cpp \
    cl_demoaction_types.cpp \
    cl_demoeditorpanel.cpp \
    cl_demosmootherpanel.cpp \
    cl_demouipanel.cpp \
    cl_entityreport.cpp \
    cl_ents_parse.cpp \
    cl_foguipanel.cpp \
    cl_localnetworkbackdoor.cpp \
    cl_main.cpp \
    cl_parse_event.cpp \
    cl_pluginhelpers.cpp \
    cl_pred.cpp \
    cl_rcon.cpp \
    cl_steamauth.cpp \
    cl_texturelistpanel.cpp \
    cl_txviewpanel.cpp \
    cmd.cpp \
    cmodel.cpp \
    cmodel_bsp.cpp \
    cmodel_disp.cpp \
    colorcorrectionpanel.cpp \
    common.cpp \
    console.cpp \
    cvar.cpp \
    debugoverlay.cpp \
    debug_leafvis.cpp \
    decals.cpp \
    decal_clip.cpp \
    demofile.cpp \
    DevShotGenerator.cpp \
    disp.cpp \
    disp_defs.cpp \
    disp_helpers.cpp \
    disp_interface.cpp \
    disp_mapload.cpp \
    download.cpp \
    DownloadListGenerator.cpp \
    downloadthread.cpp \
    dt.cpp \
    dt_common_eng.cpp \
    dt_encode.cpp \
    dt_instrumentation.cpp \
    dt_instrumentation_server.cpp \
    dt_localtransfer.cpp \
    dt_recv_decoder.cpp \
    dt_recv_eng.cpp \
    dt_send_eng.cpp \
    dt_stack.cpp \
    dt_test.cpp \
    enginesingleuserfilter.cpp \
    EngineSoundClient.cpp \
    EngineSoundServer.cpp \
    enginestats.cpp \
    enginethreads.cpp \
    enginetool.cpp \
    enginetrace.cpp \
    engine_replay_int.cpp \
    engsoundservice.cpp \
    filesystem_engine.cpp \
    filetransfermgr.cpp \
    GameEventManager.cpp \
    GameEventManagerOld.cpp \
    gametrace_engine.cpp \
    gl_draw.cpp \
    gl_drawlights.cpp \
    gl_lightmap.cpp \
    gl_matsysiface.cpp \
    gl_rlight.cpp \
    gl_rmain.cpp \
    gl_rmisc.cpp \
    gl_rsurf.cpp \
    gl_screen.cpp \
    gl_shader.cpp \
    gl_warp.cpp \
    hltvclient.cpp \
    hltvclientstate.cpp \
    hltvdemo.cpp \
    hltvserver.cpp \
    hltvtest.cpp \
    host.cpp \
    host_cmd.cpp \
    host_listmaps.cpp \
    host_phonehome.cpp \
    host_saverestore.cpp \
    host_state.cpp \
    initmathlib.cpp \
    keys.cpp \
    lightcache.cpp \
    LoadScreenUpdate.cpp \
    LocalNetworkBackdoor.cpp \
    l_studio.cpp \
    MapReslistGenerator.cpp \
    matchmakingclient.cpp \
    matchmakinghost.cpp \
    matchmakingmigrate.cpp \
    matchmakingqos.cpp \
    matchmakingshared.cpp \
    materialproxyfactory.cpp \
    matsys_interface.cpp \
    mem_fgets.cpp \
    ModelInfo.cpp \
    modelloader.cpp \
    mod_vis.cpp \
    networkstringtable.cpp \
    networkstringtableclient.cpp \
    NetworkStringTableItem.cpp \
    networkstringtableserver.cpp \
    net_chan.cpp \
    net_synctags.cpp \
    net_ws.cpp \
    net_ws_queued_packet_sender.cpp \
    OcclusionSystem.cpp \
    Overlay.cpp \
    packed_entity.cpp \
    perfuipanel.cpp \
    precache.cpp \
    pr_edict.cpp \
    pure_server.cpp \
    quakedef.cpp \
    randomstream.cpp \
    render_pch.cpp \
    replaydemo.cpp \
    replaydemoplayer.cpp \
    replayserver.cpp \
    replay_internal.cpp \
    rpt_engine.cpp \
    r_areaportal.cpp \
    r_decal.cpp \
    r_efx.cpp \
    r_linefile.cpp \
    saverestore_filesystem.cpp \
    servermsghandler.cpp \
    server_pch.cpp \
    Session.cpp \
    shadowmgr.cpp \
    snd_io.cpp \
    socketcreator.cpp \
    sound_shared.cpp \
    spatialpartition.cpp \
    staticpropmgr.cpp \
    sv_client.cpp \
    sv_ents_write.cpp \
    sv_filter.cpp \
    sv_framesnapshot.cpp \
    sv_ipratelimit.cpp \
    sv_log.cpp \
    sv_main.cpp \
    sv_packedentities.cpp \
    sv_plugin.cpp \
    sv_precache.cpp \
    sv_rcon.cpp \
    sv_redirect.cpp \
    sv_remoteaccess.cpp \
    sv_steamauth.cpp \
    sv_uploaddata.cpp \
    sv_uploadgamestats.cpp \
    sys_dll.cpp \
    sys_dll2.cpp \
    sys_engine.cpp \
    sys_getmodes.cpp \
    sys_linuxwind.cpp \
    sys_mainwind.cpp \
    testscriptmgr.cpp \
    tmessage.cpp \
    toolframework.cpp \
    traceinit.cpp \
    vengineserver_impl.cpp \
    vgui_askconnectpanel.cpp \
    vgui_basepanel.cpp \
    vgui_baseui_interface.cpp \
    vgui_budgetpanel.cpp \
    vgui_DebugSystemPanel.cpp \
    vgui_drawtreepanel.cpp \
    vgui_helpers.cpp \
    vgui_texturebudgetpanel.cpp \
    vgui_vprofgraphpanel.cpp \
    vgui_vprofpanel.cpp \
    view.cpp \
    voiceserver_impl.cpp \
    vprof_engine.cpp \
    vprof_record.cpp \
    world.cpp \
    xboxsystem.cpp \
    zone.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/common/linux32/replay_common.a \
    ../lib/public/linux32/appframework.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/common/linux32/bzip2.a \
    ../lib/common/linux32/libjpeg.a \
    ../lib/public/linux32/dmxloader.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/matsys_controls.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vtf.a \
    ../lib/public/linux32/vgui_controls.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lSDL2 \


LIBFILENAMES = \
    ../lib/common/linux32/bzip2.a \
    ../lib/common/linux32/libjpeg.a \
    ../lib/common/linux32/replay_common.a \
    ../lib/public/linux32/appframework.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/dmxloader.a \
    ../lib/public/linux32/libSDL2.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/matsys_controls.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/vtf.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/language.P
endif

$(OBJ_DIR)/language.o : $(abspath ../common/language.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/netmessages.P
endif

$(OBJ_DIR)/netmessages.o : $(abspath ../common/netmessages.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/randoverride.P
endif

$(OBJ_DIR)/randoverride.o : $(abspath ../common/randoverride.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SourceAppInfo.P
endif

$(OBJ_DIR)/SourceAppInfo.o : $(abspath ../common/SourceAppInfo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamid.P
endif

$(OBJ_DIR)/steamid.o : $(abspath ../common/steamid.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_basebudgetpanel.P
endif

$(OBJ_DIR)/vgui_basebudgetpanel.o : $(abspath ../common/vgui/vgui_basebudgetpanel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_budgetbargraphpanel.P
endif

$(OBJ_DIR)/vgui_budgetbargraphpanel.o : $(abspath ../common/vgui/vgui_budgetbargraphpanel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_budgethistorypanel.P
endif

$(OBJ_DIR)/vgui_budgethistorypanel.o : $(abspath ../common/vgui/vgui_budgethistorypanel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_budgetpanelshared.P
endif

$(OBJ_DIR)/vgui_budgetpanelshared.o : $(abspath ../common/vgui/vgui_budgetpanelshared.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/blockingudpsocket.P
endif

$(OBJ_DIR)/blockingudpsocket.o : $(abspath ../public/blockingudpsocket.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bsptreedata.P
endif

$(OBJ_DIR)/bsptreedata.o : $(abspath ../public/bsptreedata.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/builddisp.P
endif

$(OBJ_DIR)/builddisp.o : $(abspath ../public/builddisp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionutils.P
endif

$(OBJ_DIR)/collisionutils.o : $(abspath ../public/collisionutils.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/crtmemdebug.P
endif

$(OBJ_DIR)/crtmemdebug.o : $(abspath ../public/crtmemdebug.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dispcoll_common.P
endif

$(OBJ_DIR)/dispcoll_common.o : $(abspath ../public/dispcoll_common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_common.P
endif

$(OBJ_DIR)/disp_common.o : $(abspath ../public/disp_common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_powerinfo.P
endif

$(OBJ_DIR)/disp_powerinfo.o : $(abspath ../public/disp_powerinfo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_recv.P
endif

$(OBJ_DIR)/dt_recv.o : $(abspath ../public/dt_recv.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_send.P
endif

$(OBJ_DIR)/dt_send.o : $(abspath ../public/dt_send.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_common.P
endif

$(OBJ_DIR)/dt_utlvector_common.o : $(abspath ../public/dt_utlvector_common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_recv.P
endif

$(OBJ_DIR)/dt_utlvector_recv.o : $(abspath ../public/dt_utlvector_recv.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_send.P
endif

$(OBJ_DIR)/dt_utlvector_send.o : $(abspath ../public/dt_utlvector_send.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/editor_sendcommand.P
endif

$(OBJ_DIR)/editor_sendcommand.o : $(abspath ../public/editor_sendcommand.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../public/filesystem_helpers.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_init.P
endif

$(OBJ_DIR)/filesystem_init.o : $(abspath ../public/filesystem_init.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lumpfiles.P
endif

$(OBJ_DIR)/lumpfiles.o : $(abspath ../public/lumpfiles.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkvar.P
endif

$(OBJ_DIR)/networkvar.o : $(abspath ../public/networkvar.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/registry.P
endif

$(OBJ_DIR)/registry.o : $(abspath ../public/registry.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scratchpad3d.P
endif

$(OBJ_DIR)/scratchpad3d.o : $(abspath ../public/scratchpad3d.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sentence.P
endif

$(OBJ_DIR)/sentence.o : $(abspath ../public/sentence.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio.P
endif

$(OBJ_DIR)/studio.o : $(abspath ../public/studio.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vallocator.P
endif

$(OBJ_DIR)/vallocator.o : $(abspath ../public/vallocator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../public/vgui_controls/vgui_controls.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/XUnzip.P
endif

$(OBJ_DIR)/XUnzip.o : $(abspath ../public/XUnzip.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/XZip.P
endif

$(OBJ_DIR)/XZip.o : $(abspath ../public/XZip.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/audio_pch.P
endif

$(OBJ_DIR)/audio_pch.h.gch : audio/audio_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/audio_pch.h.P : $(OBJ_DIR)/audio_pch.h.gch

vpath audio/audio_pch.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/audio_pch.h.P
endif

$(OBJ_DIR)/audio_pch.h : audio/audio_pch.h $(OBJ_DIR)/audio_pch.h.gch $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/audio_pch.h

$(OBJ_DIR)/audio_pch.o : $(abspath audio/audio_pch.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/circularbuffer.P
endif

$(OBJ_DIR)/circularbuffer.o : $(abspath audio/private/circularbuffer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MPAFile.P
endif

$(OBJ_DIR)/MPAFile.o : $(abspath audio/private/MPAFile.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MPAHeader.P
endif

$(OBJ_DIR)/MPAHeader.o : $(abspath audio/private/MPAHeader.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_dev_common.P
endif

$(OBJ_DIR)/snd_dev_common.o : $(abspath audio/private/snd_dev_common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_dev_sdl.P
endif

$(OBJ_DIR)/snd_dev_sdl.o : $(abspath audio/private/snd_dev_sdl.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_dma.P
endif

$(OBJ_DIR)/snd_dma.o : $(abspath audio/private/snd_dma.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_dsp.P
endif

$(OBJ_DIR)/snd_dsp.o : $(abspath audio/private/snd_dsp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_mix.P
endif

$(OBJ_DIR)/snd_mix.o : $(abspath audio/private/snd_mix.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_mp3_source.P
endif

$(OBJ_DIR)/snd_mp3_source.o : $(abspath audio/private/snd_mp3_source.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_posix.P
endif

$(OBJ_DIR)/snd_posix.o : $(abspath audio/private/snd_posix.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_sentence_mixer.P
endif

$(OBJ_DIR)/snd_sentence_mixer.o : $(abspath audio/private/snd_sentence_mixer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_data.P
endif

$(OBJ_DIR)/snd_wave_data.o : $(abspath audio/private/snd_wave_data.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_mixer.P
endif

$(OBJ_DIR)/snd_wave_mixer.o : $(abspath audio/private/snd_wave_mixer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_mixer_adpcm.P
endif

$(OBJ_DIR)/snd_wave_mixer_adpcm.o : $(abspath audio/private/snd_wave_mixer_adpcm.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_mixer_mp3.P
endif

$(OBJ_DIR)/snd_wave_mixer_mp3.o : $(abspath audio/private/snd_wave_mixer_mp3.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_source.P
endif

$(OBJ_DIR)/snd_wave_source.o : $(abspath audio/private/snd_wave_source.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_wave_temp.P
endif

$(OBJ_DIR)/snd_wave_temp.o : $(abspath audio/private/snd_wave_temp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_win.P
endif

$(OBJ_DIR)/snd_win.o : $(abspath audio/private/snd_win.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/VBRHeader.P
endif

$(OBJ_DIR)/VBRHeader.o : $(abspath audio/private/VBRHeader.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice.P
endif

$(OBJ_DIR)/voice.o : $(abspath audio/private/voice.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_gain.P
endif

$(OBJ_DIR)/voice_gain.o : $(abspath audio/private/voice_gain.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_mixer_controls_openal.P
endif

$(OBJ_DIR)/voice_mixer_controls_openal.o : $(abspath audio/private/voice_mixer_controls_openal.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_record_openal.P
endif

$(OBJ_DIR)/voice_record_openal.o : $(abspath audio/private/voice_record_openal.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_sound_engine_interface.P
endif

$(OBJ_DIR)/voice_sound_engine_interface.o : $(abspath audio/private/voice_sound_engine_interface.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_wavefile.P
endif

$(OBJ_DIR)/voice_wavefile.o : $(abspath audio/private/voice_wavefile.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vox.P
endif

$(OBJ_DIR)/vox.o : $(abspath audio/private/vox.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseautocompletefilelist.P
endif

$(OBJ_DIR)/baseautocompletefilelist.o : $(abspath baseautocompletefilelist.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseclient.P
endif

$(OBJ_DIR)/baseclient.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/baseclient.o : $(abspath baseclient.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseclientstate.P
endif

$(OBJ_DIR)/baseclientstate.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/baseclientstate.o : $(abspath baseclientstate.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseserver.P
endif

$(OBJ_DIR)/baseserver.o : $(abspath baseserver.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bitbuf_errorhandler.P
endif

$(OBJ_DIR)/bitbuf_errorhandler.o : $(abspath bitbuf_errorhandler.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bugreporter.P
endif

$(OBJ_DIR)/bugreporter.o : $(abspath bugreporter.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/buildcubemaps.P
endif

$(OBJ_DIR)/buildcubemaps.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/buildcubemaps.o : $(abspath buildcubemaps.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cbenchmark.P
endif

$(OBJ_DIR)/cbenchmark.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cbenchmark.o : $(abspath cbenchmark.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ccs.P
endif

$(OBJ_DIR)/ccs.o : $(abspath ccs.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_engine_int.P
endif

$(OBJ_DIR)/cdll_engine_int.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cdll_engine_int.o : $(abspath cdll_engine_int.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/changeframelist.P
endif

$(OBJ_DIR)/changeframelist.o : $(abspath changeframelist.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cheatcodes.P
endif

$(OBJ_DIR)/cheatcodes.o : $(abspath cheatcodes.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/checksum_engine.P
endif

$(OBJ_DIR)/checksum_engine.o : $(abspath checksum_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client.P
endif

$(OBJ_DIR)/client.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/client.o : $(abspath client.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientframe.P
endif

$(OBJ_DIR)/clientframe.o : $(abspath clientframe.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_pch.P
endif

$(OBJ_DIR)/client_pch.h.gch : client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/client_pch.h.P : $(OBJ_DIR)/client_pch.h.gch

vpath client_pch.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/client_pch.h.P
endif

$(OBJ_DIR)/client_pch.h : client_pch.h $(OBJ_DIR)/client_pch.h.gch $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/client_pch.h

$(OBJ_DIR)/client_pch.o : $(abspath client_pch.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clockdriftmgr.P
endif

$(OBJ_DIR)/clockdriftmgr.o : $(abspath clockdriftmgr.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_bounded_cvars.P
endif

$(OBJ_DIR)/cl_bounded_cvars.o : $(abspath cl_bounded_cvars.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_check_process.P
endif

$(OBJ_DIR)/cl_check_process.o : $(abspath cl_check_process.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demo.P
endif

$(OBJ_DIR)/cl_demo.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demo.o : $(abspath cl_demo.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoaction.P
endif

$(OBJ_DIR)/cl_demoaction.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoaction.o : $(abspath cl_demoaction.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoactioneditors.P
endif

$(OBJ_DIR)/cl_demoactioneditors.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoactioneditors.o : $(abspath cl_demoactioneditors.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoactionmanager.P
endif

$(OBJ_DIR)/cl_demoactionmanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoactionmanager.o : $(abspath cl_demoactionmanager.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoaction_types.P
endif

$(OBJ_DIR)/cl_demoaction_types.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoaction_types.o : $(abspath cl_demoaction_types.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demoeditorpanel.P
endif

$(OBJ_DIR)/cl_demoeditorpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demoeditorpanel.o : $(abspath cl_demoeditorpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demosmootherpanel.P
endif

$(OBJ_DIR)/cl_demosmootherpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demosmootherpanel.o : $(abspath cl_demosmootherpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_demouipanel.P
endif

$(OBJ_DIR)/cl_demouipanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_demouipanel.o : $(abspath cl_demouipanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_entityreport.P
endif

$(OBJ_DIR)/cl_entityreport.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_entityreport.o : $(abspath cl_entityreport.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_ents_parse.P
endif

$(OBJ_DIR)/cl_ents_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_ents_parse.o : $(abspath cl_ents_parse.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_foguipanel.P
endif

$(OBJ_DIR)/cl_foguipanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_foguipanel.o : $(abspath cl_foguipanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_localnetworkbackdoor.P
endif

$(OBJ_DIR)/cl_localnetworkbackdoor.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_localnetworkbackdoor.o : $(abspath cl_localnetworkbackdoor.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_main.P
endif

$(OBJ_DIR)/cl_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_main.o : $(abspath cl_main.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_parse_event.P
endif

$(OBJ_DIR)/cl_parse_event.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_parse_event.o : $(abspath cl_parse_event.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_pluginhelpers.P
endif

$(OBJ_DIR)/cl_pluginhelpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_pluginhelpers.o : $(abspath cl_pluginhelpers.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_pred.P
endif

$(OBJ_DIR)/cl_pred.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_pred.o : $(abspath cl_pred.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_rcon.P
endif

$(OBJ_DIR)/cl_rcon.o : $(abspath cl_rcon.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_steamauth.P
endif

$(OBJ_DIR)/cl_steamauth.o : $(abspath cl_steamauth.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_texturelistpanel.P
endif

$(OBJ_DIR)/cl_texturelistpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_texturelistpanel.o : $(abspath cl_texturelistpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_txviewpanel.P
endif

$(OBJ_DIR)/cl_txviewpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/cl_txviewpanel.o : $(abspath cl_txviewpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmd.P
endif

$(OBJ_DIR)/cmd.o : $(abspath cmd.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmodel.P
endif

$(OBJ_DIR)/cmodel.o : $(abspath cmodel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmodel_bsp.P
endif

$(OBJ_DIR)/cmodel_bsp.o : $(abspath cmodel_bsp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cmodel_disp.P
endif

$(OBJ_DIR)/cmodel_disp.o : $(abspath cmodel_disp.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrectionpanel.P
endif

$(OBJ_DIR)/colorcorrectionpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/colorcorrectionpanel.o : $(abspath colorcorrectionpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/common.P
endif

$(OBJ_DIR)/common.o : $(abspath common.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/console.P
endif

$(OBJ_DIR)/console.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/console.o : $(abspath console.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cvar.P
endif

$(OBJ_DIR)/cvar.o : $(abspath cvar.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugoverlay.P
endif

$(OBJ_DIR)/debugoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/debugoverlay.o : $(abspath debugoverlay.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debug_leafvis.P
endif

$(OBJ_DIR)/debug_leafvis.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/debug_leafvis.o : $(abspath debug_leafvis.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/decals.P
endif

$(OBJ_DIR)/decals.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/decals.o : $(abspath decals.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/decal_clip.P
endif

$(OBJ_DIR)/decal_clip.o : $(abspath decal_clip.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/demofile.P
endif

$(OBJ_DIR)/demofile.o : $(abspath demofile.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DevShotGenerator.P
endif

$(OBJ_DIR)/DevShotGenerator.o : $(abspath DevShotGenerator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp.P
endif

$(OBJ_DIR)/disp.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/disp.o : $(abspath disp.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_defs.P
endif

$(OBJ_DIR)/disp_defs.o : $(abspath disp_defs.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_helpers.P
endif

$(OBJ_DIR)/disp_helpers.o : $(abspath disp_helpers.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_interface.P
endif

$(OBJ_DIR)/disp_interface.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/disp_interface.o : $(abspath disp_interface.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/disp_mapload.P
endif

$(OBJ_DIR)/disp_mapload.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/disp_mapload.o : $(abspath disp_mapload.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/download.P
endif

$(OBJ_DIR)/download.o : $(abspath download.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DownloadListGenerator.P
endif

$(OBJ_DIR)/DownloadListGenerator.o : $(abspath DownloadListGenerator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/downloadthread.P
endif

$(OBJ_DIR)/downloadthread.o : $(abspath downloadthread.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt.P
endif

$(OBJ_DIR)/dt.o : $(abspath dt.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_common_eng.P
endif

$(OBJ_DIR)/dt_common_eng.o : $(abspath dt_common_eng.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_encode.P
endif

$(OBJ_DIR)/dt_encode.o : $(abspath dt_encode.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_instrumentation.P
endif

$(OBJ_DIR)/dt_instrumentation.o : $(abspath dt_instrumentation.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_instrumentation_server.P
endif

$(OBJ_DIR)/dt_instrumentation_server.o : $(abspath dt_instrumentation_server.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_localtransfer.P
endif

$(OBJ_DIR)/dt_localtransfer.o : $(abspath dt_localtransfer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_recv_decoder.P
endif

$(OBJ_DIR)/dt_recv_decoder.o : $(abspath dt_recv_decoder.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_recv_eng.P
endif

$(OBJ_DIR)/dt_recv_eng.o : $(abspath dt_recv_eng.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_send_eng.P
endif

$(OBJ_DIR)/dt_send_eng.o : $(abspath dt_send_eng.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_stack.P
endif

$(OBJ_DIR)/dt_stack.o : $(abspath dt_stack.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_test.P
endif

$(OBJ_DIR)/dt_test.o : $(abspath dt_test.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginesingleuserfilter.P
endif

$(OBJ_DIR)/enginesingleuserfilter.o : $(abspath enginesingleuserfilter.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EngineSoundClient.P
endif

$(OBJ_DIR)/EngineSoundClient.o : $(abspath EngineSoundClient.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EngineSoundServer.P
endif

$(OBJ_DIR)/EngineSoundServer.o : $(abspath EngineSoundServer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginestats.P
endif

$(OBJ_DIR)/enginestats.o : $(abspath enginestats.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginethreads.P
endif

$(OBJ_DIR)/enginethreads.o : $(abspath enginethreads.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginetool.P
endif

$(OBJ_DIR)/enginetool.o : $(abspath enginetool.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/enginetrace.P
endif

$(OBJ_DIR)/enginetrace.o : $(abspath enginetrace.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/engine_replay_int.P
endif

$(OBJ_DIR)/engine_replay_int.o : $(abspath engine_replay_int.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/engsoundservice.P
endif

$(OBJ_DIR)/engsoundservice.o : $(abspath engsoundservice.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_engine.P
endif

$(OBJ_DIR)/filesystem_engine.o : $(abspath filesystem_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filetransfermgr.P
endif

$(OBJ_DIR)/filetransfermgr.o : $(abspath filetransfermgr.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameEventManager.P
endif

$(OBJ_DIR)/GameEventManager.o : $(abspath GameEventManager.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameEventManagerOld.P
endif

$(OBJ_DIR)/GameEventManagerOld.o : $(abspath GameEventManagerOld.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gametrace_engine.P
endif

$(OBJ_DIR)/gametrace_engine.o : $(abspath gametrace_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_draw.P
endif

$(OBJ_DIR)/gl_draw.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_draw.o : $(abspath gl_draw.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_drawlights.P
endif

$(OBJ_DIR)/gl_drawlights.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_drawlights.o : $(abspath gl_drawlights.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_lightmap.P
endif

$(OBJ_DIR)/gl_lightmap.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_lightmap.o : $(abspath gl_lightmap.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_matsysiface.P
endif

$(OBJ_DIR)/gl_matsysiface.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_matsysiface.o : $(abspath gl_matsysiface.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_rlight.P
endif

$(OBJ_DIR)/gl_rlight.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_rlight.o : $(abspath gl_rlight.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_rmain.P
endif

$(OBJ_DIR)/gl_rmain.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_rmain.o : $(abspath gl_rmain.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_rmisc.P
endif

$(OBJ_DIR)/gl_rmisc.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_rmisc.o : $(abspath gl_rmisc.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_rsurf.P
endif

$(OBJ_DIR)/gl_rsurf.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_rsurf.o : $(abspath gl_rsurf.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_screen.P
endif

$(OBJ_DIR)/gl_screen.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_screen.o : $(abspath gl_screen.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_shader.P
endif

$(OBJ_DIR)/gl_shader.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_shader.o : $(abspath gl_shader.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gl_warp.P
endif

$(OBJ_DIR)/gl_warp.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/gl_warp.o : $(abspath gl_warp.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvclient.P
endif

$(OBJ_DIR)/hltvclient.o : $(abspath hltvclient.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvclientstate.P
endif

$(OBJ_DIR)/hltvclientstate.o : $(abspath hltvclientstate.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvdemo.P
endif

$(OBJ_DIR)/hltvdemo.o : $(abspath hltvdemo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvserver.P
endif

$(OBJ_DIR)/hltvserver.o : $(abspath hltvserver.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvtest.P
endif

$(OBJ_DIR)/hltvtest.o : $(abspath hltvtest.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host.P
endif

$(OBJ_DIR)/host.o : $(abspath host.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_cmd.P
endif

$(OBJ_DIR)/host_cmd.o : $(abspath host_cmd.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_listmaps.P
endif

$(OBJ_DIR)/host_listmaps.o : $(abspath host_listmaps.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_phonehome.P
endif

$(OBJ_DIR)/host_phonehome.o : $(abspath host_phonehome.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_saverestore.P
endif

$(OBJ_DIR)/host_saverestore.o : $(abspath host_saverestore.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/host_state.P
endif

$(OBJ_DIR)/host_state.o : $(abspath host_state.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/initmathlib.P
endif

$(OBJ_DIR)/initmathlib.o : $(abspath initmathlib.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/keys.P
endif

$(OBJ_DIR)/keys.o : $(abspath keys.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightcache.P
endif

$(OBJ_DIR)/lightcache.o : $(abspath lightcache.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadScreenUpdate.P
endif

$(OBJ_DIR)/LoadScreenUpdate.o : $(abspath LoadScreenUpdate.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LocalNetworkBackdoor.P
endif

$(OBJ_DIR)/LocalNetworkBackdoor.o : $(abspath LocalNetworkBackdoor.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/l_studio.P
endif

$(OBJ_DIR)/l_studio.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/l_studio.o : $(abspath l_studio.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MapReslistGenerator.P
endif

$(OBJ_DIR)/MapReslistGenerator.o : $(abspath MapReslistGenerator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingclient.P
endif

$(OBJ_DIR)/matchmakingclient.o : $(abspath matchmakingclient.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakinghost.P
endif

$(OBJ_DIR)/matchmakinghost.o : $(abspath matchmakinghost.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingmigrate.P
endif

$(OBJ_DIR)/matchmakingmigrate.o : $(abspath matchmakingmigrate.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingqos.P
endif

$(OBJ_DIR)/matchmakingqos.o : $(abspath matchmakingqos.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingshared.P
endif

$(OBJ_DIR)/matchmakingshared.o : $(abspath matchmakingshared.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/materialproxyfactory.P
endif

$(OBJ_DIR)/materialproxyfactory.o : $(abspath materialproxyfactory.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matsys_interface.P
endif

$(OBJ_DIR)/matsys_interface.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/matsys_interface.o : $(abspath matsys_interface.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mem_fgets.P
endif

$(OBJ_DIR)/mem_fgets.o : $(abspath mem_fgets.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ModelInfo.P
endif

$(OBJ_DIR)/ModelInfo.o : $(abspath ModelInfo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/modelloader.P
endif

$(OBJ_DIR)/modelloader.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/modelloader.o : $(abspath modelloader.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mod_vis.P
endif

$(OBJ_DIR)/mod_vis.o : $(abspath mod_vis.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkstringtable.P
endif

$(OBJ_DIR)/networkstringtable.o : $(abspath networkstringtable.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkstringtableclient.P
endif

$(OBJ_DIR)/networkstringtableclient.o : $(abspath networkstringtableclient.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/NetworkStringTableItem.P
endif

$(OBJ_DIR)/NetworkStringTableItem.o : $(abspath NetworkStringTableItem.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkstringtableserver.P
endif

$(OBJ_DIR)/networkstringtableserver.o : $(abspath networkstringtableserver.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/net_chan.P
endif

$(OBJ_DIR)/net_chan.o : $(abspath net_chan.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/net_synctags.P
endif

$(OBJ_DIR)/net_synctags.o : $(abspath net_synctags.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/net_ws.P
endif

$(OBJ_DIR)/net_ws.o : $(abspath net_ws.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/net_ws_queued_packet_sender.P
endif

$(OBJ_DIR)/net_ws_queued_packet_sender.o : $(abspath net_ws_queued_packet_sender.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OcclusionSystem.P
endif

$(OBJ_DIR)/OcclusionSystem.o : $(abspath OcclusionSystem.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Overlay.P
endif

$(OBJ_DIR)/Overlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/Overlay.o : $(abspath Overlay.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/packed_entity.P
endif

$(OBJ_DIR)/packed_entity.o : $(abspath packed_entity.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/perfuipanel.P
endif

$(OBJ_DIR)/perfuipanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/perfuipanel.o : $(abspath perfuipanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/precache.P
endif

$(OBJ_DIR)/precache.o : $(abspath precache.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pr_edict.P
endif

$(OBJ_DIR)/pr_edict.o : $(abspath pr_edict.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pure_server.P
endif

$(OBJ_DIR)/pure_server.o : $(abspath pure_server.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/quakedef.P
endif

$(OBJ_DIR)/quakedef.o : $(abspath quakedef.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/randomstream.P
endif

$(OBJ_DIR)/randomstream.o : $(abspath randomstream.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/render_pch.P
endif

$(OBJ_DIR)/render_pch.h.gch : render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/render_pch.h.P : $(OBJ_DIR)/render_pch.h.gch

vpath render_pch.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/render_pch.h.P
endif

$(OBJ_DIR)/render_pch.h : render_pch.h $(OBJ_DIR)/render_pch.h.gch $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/render_pch.h

$(OBJ_DIR)/render_pch.o : $(abspath render_pch.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replaydemo.P
endif

$(OBJ_DIR)/replaydemo.o : $(abspath replaydemo.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replaydemoplayer.P
endif

$(OBJ_DIR)/replaydemoplayer.o : $(abspath replaydemoplayer.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replayserver.P
endif

$(OBJ_DIR)/replayserver.o : $(abspath replayserver.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replay_internal.P
endif

$(OBJ_DIR)/replay_internal.o : $(abspath replay_internal.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rpt_engine.P
endif

$(OBJ_DIR)/rpt_engine.o : $(abspath rpt_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/r_areaportal.P
endif

$(OBJ_DIR)/r_areaportal.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/r_areaportal.o : $(abspath r_areaportal.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/r_decal.P
endif

$(OBJ_DIR)/r_decal.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/r_decal.o : $(abspath r_decal.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/r_efx.P
endif

$(OBJ_DIR)/r_efx.o : $(abspath r_efx.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/r_linefile.P
endif

$(OBJ_DIR)/r_linefile.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/r_linefile.o : $(abspath r_linefile.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/saverestore_filesystem.P
endif

$(OBJ_DIR)/saverestore_filesystem.o : $(abspath saverestore_filesystem.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/servermsghandler.P
endif

$(OBJ_DIR)/servermsghandler.o : $(abspath servermsghandler.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/server_pch.P
endif

$(OBJ_DIR)/server_pch.h.gch : server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/server_pch.h.P : $(OBJ_DIR)/server_pch.h.gch

vpath server_pch.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/server_pch.h.P
endif

$(OBJ_DIR)/server_pch.h : server_pch.h $(OBJ_DIR)/server_pch.h.gch $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/server_pch.h

$(OBJ_DIR)/server_pch.o : $(abspath server_pch.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Session.P
endif

$(OBJ_DIR)/Session.o : $(abspath Session.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadowmgr.P
endif

$(OBJ_DIR)/shadowmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/render_pch.h
$(OBJ_DIR)/shadowmgr.o : $(abspath shadowmgr.cpp) $(OBJ_DIR)/render_pch.h.gch $(OBJ_DIR)/render_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/snd_io.P
endif

$(OBJ_DIR)/snd_io.o : $(abspath snd_io.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/socketcreator.P
endif

$(OBJ_DIR)/socketcreator.o : $(abspath socketcreator.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sound_shared.P
endif

$(OBJ_DIR)/sound_shared.o : $(abspath sound_shared.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spatialpartition.P
endif

$(OBJ_DIR)/spatialpartition.o : $(abspath spatialpartition.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/staticpropmgr.P
endif

$(OBJ_DIR)/staticpropmgr.o : $(abspath staticpropmgr.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_client.P
endif

$(OBJ_DIR)/sv_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_client.o : $(abspath sv_client.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_ents_write.P
endif

$(OBJ_DIR)/sv_ents_write.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_ents_write.o : $(abspath sv_ents_write.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_filter.P
endif

$(OBJ_DIR)/sv_filter.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_filter.o : $(abspath sv_filter.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_framesnapshot.P
endif

$(OBJ_DIR)/sv_framesnapshot.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_framesnapshot.o : $(abspath sv_framesnapshot.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_ipratelimit.P
endif

$(OBJ_DIR)/sv_ipratelimit.o : $(abspath sv_ipratelimit.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_log.P
endif

$(OBJ_DIR)/sv_log.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_log.o : $(abspath sv_log.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_main.P
endif

$(OBJ_DIR)/sv_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_main.o : $(abspath sv_main.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_packedentities.P
endif

$(OBJ_DIR)/sv_packedentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_packedentities.o : $(abspath sv_packedentities.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_plugin.P
endif

$(OBJ_DIR)/sv_plugin.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_plugin.o : $(abspath sv_plugin.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_precache.P
endif

$(OBJ_DIR)/sv_precache.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_precache.o : $(abspath sv_precache.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_rcon.P
endif

$(OBJ_DIR)/sv_rcon.o : $(abspath sv_rcon.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_redirect.P
endif

$(OBJ_DIR)/sv_redirect.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_redirect.o : $(abspath sv_redirect.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_remoteaccess.P
endif

$(OBJ_DIR)/sv_remoteaccess.o : TARGET_PCH_FILE = $(OBJ_DIR)/server_pch.h
$(OBJ_DIR)/sv_remoteaccess.o : $(abspath sv_remoteaccess.cpp) $(OBJ_DIR)/server_pch.h.gch $(OBJ_DIR)/server_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_steamauth.P
endif

$(OBJ_DIR)/sv_steamauth.o : $(abspath sv_steamauth.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_uploaddata.P
endif

$(OBJ_DIR)/sv_uploaddata.o : $(abspath sv_uploaddata.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_uploadgamestats.P
endif

$(OBJ_DIR)/sv_uploadgamestats.o : $(abspath sv_uploadgamestats.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_dll.P
endif

$(OBJ_DIR)/sys_dll.o : $(abspath sys_dll.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_dll2.P
endif

$(OBJ_DIR)/sys_dll2.o : $(abspath sys_dll2.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_engine.P
endif

$(OBJ_DIR)/sys_engine.o : $(abspath sys_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_getmodes.P
endif

$(OBJ_DIR)/sys_getmodes.o : $(abspath sys_getmodes.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_linuxwind.P
endif

$(OBJ_DIR)/sys_linuxwind.o : $(abspath sys_linuxwind.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sys_mainwind.P
endif

$(OBJ_DIR)/sys_mainwind.o : $(abspath sys_mainwind.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/testscriptmgr.P
endif

$(OBJ_DIR)/testscriptmgr.o : $(abspath testscriptmgr.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tmessage.P
endif

$(OBJ_DIR)/tmessage.o : $(abspath tmessage.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/toolframework.P
endif

$(OBJ_DIR)/toolframework.o : $(abspath toolframework.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/traceinit.P
endif

$(OBJ_DIR)/traceinit.o : $(abspath traceinit.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vengineserver_impl.P
endif

$(OBJ_DIR)/vengineserver_impl.o : $(abspath vengineserver_impl.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_askconnectpanel.P
endif

$(OBJ_DIR)/vgui_askconnectpanel.o : $(abspath vgui_askconnectpanel.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_basepanel.P
endif

$(OBJ_DIR)/vgui_basepanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_basepanel.o : $(abspath vgui_basepanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_baseui_interface.P
endif

$(OBJ_DIR)/vgui_baseui_interface.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_baseui_interface.o : $(abspath vgui_baseui_interface.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_budgetpanel.P
endif

$(OBJ_DIR)/vgui_budgetpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_budgetpanel.o : $(abspath vgui_budgetpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_DebugSystemPanel.P
endif

$(OBJ_DIR)/vgui_DebugSystemPanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_DebugSystemPanel.o : $(abspath vgui_DebugSystemPanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_drawtreepanel.P
endif

$(OBJ_DIR)/vgui_drawtreepanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_drawtreepanel.o : $(abspath vgui_drawtreepanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_helpers.P
endif

$(OBJ_DIR)/vgui_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_helpers.o : $(abspath vgui_helpers.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_texturebudgetpanel.P
endif

$(OBJ_DIR)/vgui_texturebudgetpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_texturebudgetpanel.o : $(abspath vgui_texturebudgetpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_vprofgraphpanel.P
endif

$(OBJ_DIR)/vgui_vprofgraphpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_vprofgraphpanel.o : $(abspath vgui_vprofgraphpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_vprofpanel.P
endif

$(OBJ_DIR)/vgui_vprofpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/client_pch.h
$(OBJ_DIR)/vgui_vprofpanel.o : $(abspath vgui_vprofpanel.cpp) $(OBJ_DIR)/client_pch.h.gch $(OBJ_DIR)/client_pch.h $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view.P
endif

$(OBJ_DIR)/view.o : $(abspath view.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voiceserver_impl.P
endif

$(OBJ_DIR)/voiceserver_impl.o : $(abspath voiceserver_impl.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vprof_engine.P
endif

$(OBJ_DIR)/vprof_engine.o : $(abspath vprof_engine.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vprof_record.P
endif

$(OBJ_DIR)/vprof_record.o : $(abspath vprof_record.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/world.P
endif

$(OBJ_DIR)/world.o : $(abspath world.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/xboxsystem.P
endif

$(OBJ_DIR)/xboxsystem.o : $(abspath xboxsystem.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/zone.P
endif

$(OBJ_DIR)/zone.o : $(abspath zone.cpp) $(PWD)/engine_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



