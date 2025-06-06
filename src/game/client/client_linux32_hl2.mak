ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=client_hl2
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
SystemLibraries=-lrt 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=client -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DNO_STRING_T -DCLIENT_DLL -DVECTOR -DVERSION_SAFE_STEAM_API_INTERFACES -DPROTECTED_THINGS_ENABLE -Dstrncpy=use_Q_strncpy_instead -D_snprintf=use_Q_snprintf_instead -DUSE_WEBM_FOR_REPLAY -DHL2_CLIENT_DLL -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/game/client -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ./hl2 ./hl2/elements ../../game/shared/hl2 ./ ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 ../../game/client/generated_proto_hl2 ../../thirdparty/protobuf-2.6.1/src ../../vgui2/include ../../vgui2/controls ../../game/shared ./game_controls ../../thirdparty/sixensesdk/include 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../../game/hl2/bin/client.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/client.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../common/compiledcaptionswap.cpp \
    ../../common/language.cpp \
    ../../common/randoverride.cpp \
    ../../common/steamid.cpp \
    ../../game/client/c_vote_controller.cpp \
    ../../game/shared/achievementmgr.cpp \
    ../../game/shared/achievements_hlx.cpp \
    ../../game/shared/achievement_saverestore.cpp \
    ../../game/shared/activitylist.cpp \
    ../../game/shared/ammodef.cpp \
    ../../game/shared/animation.cpp \
    ../../game/shared/baseachievement.cpp \
    ../../game/shared/basecombatcharacter_shared.cpp \
    ../../game/shared/basecombatweapon_shared.cpp \
    ../../game/shared/baseentity_shared.cpp \
    ../../game/shared/basegrenade_shared.cpp \
    ../../game/shared/baseparticleentity.cpp \
    ../../game/shared/baseplayer_shared.cpp \
    ../../game/shared/baseprojectile.cpp \
    ../../game/shared/baseviewmodel_shared.cpp \
    ../../game/shared/base_playeranimstate.cpp \
    ../../game/shared/beam_shared.cpp \
    ../../game/shared/cam_thirdperson.cpp \
    ../../game/shared/collisionproperty.cpp \
    ../../game/shared/death_pose.cpp \
    ../../game/shared/debugoverlay_shared.cpp \
    ../../game/shared/decals.cpp \
    ../../game/shared/effect_dispatch_data.cpp \
    ../../game/shared/ehandle.cpp \
    ../../game/shared/entitylist_base.cpp \
    ../../game/shared/EntityParticleTrail_Shared.cpp \
    ../../game/shared/env_detail_controller.cpp \
    ../../game/shared/env_wind_shared.cpp \
    ../../game/shared/eventlist.cpp \
    ../../game/shared/func_ladder.cpp \
    ../../game/shared/gamemovement.cpp \
    ../../game/shared/gamerules.cpp \
    ../../game/shared/gamerules_register.cpp \
    ../../game/shared/GameStats.cpp \
    ../../game/shared/gamestringpool.cpp \
    ../../game/shared/gamevars_shared.cpp \
    ../../game/shared/hintmessage.cpp \
    ../../game/shared/hintsystem.cpp \
    ../../game/shared/hl2/achievements_hl2.cpp \
    ../../game/shared/hl2/basehlcombatweapon_shared.cpp \
    ../../game/shared/hl2/env_headcrabcanister_shared.cpp \
    ../../game/shared/hl2/hl2_gamerules.cpp \
    ../../game/shared/hl2/hl2_usermessages.cpp \
    ../../game/shared/hl2/hl_gamemovement.cpp \
    ../../game/shared/igamesystem.cpp \
    ../../game/shared/interval.cpp \
    ../../game/shared/mapentities_shared.cpp \
    ../../game/shared/movevars_shared.cpp \
    ../../game/shared/mp_shareddefs.cpp \
    ../../game/shared/multiplay_gamerules.cpp \
    ../../game/shared/obstacle_pushaway.cpp \
    ../../game/shared/particlesystemquery.cpp \
    ../../game/shared/particle_parse.cpp \
    ../../game/shared/particle_property.cpp \
    ../../game/shared/physics_main_shared.cpp \
    ../../game/shared/physics_saverestore.cpp \
    ../../game/shared/physics_shared.cpp \
    ../../game/shared/point_bonusmaps_accessor.cpp \
    ../../game/shared/point_posecontroller.cpp \
    ../../game/shared/precache_register.cpp \
    ../../game/shared/predictableid.cpp \
    ../../game/shared/predictioncopy.cpp \
    ../../game/shared/props_shared.cpp \
    ../../game/shared/ragdoll_shared.cpp \
    ../../game/shared/rope_helpers.cpp \
    ../../game/shared/saverestore.cpp \
    ../../game/shared/sceneentity_shared.cpp \
    ../../game/shared/script_intro_shared.cpp \
    ../../game/shared/sequence_Transitioner.cpp \
    ../../game/shared/sheetsimulator.cpp \
    ../../game/shared/simtimer.cpp \
    ../../game/shared/singleplay_gamerules.cpp \
    ../../game/shared/sixense/sixense_convars.cpp \
    ../../game/shared/SoundEmitterSystem.cpp \
    ../../game/shared/soundenvelope.cpp \
    ../../game/shared/Sprite.cpp \
    ../../game/shared/SpriteTrail.cpp \
    ../../game/shared/studio_shared.cpp \
    ../../game/shared/takedamageinfo.cpp \
    ../../game/shared/teamplayroundbased_gamerules.cpp \
    ../../game/shared/teamplay_gamerules.cpp \
    ../../game/shared/test_ehandle.cpp \
    ../../game/shared/usercmd.cpp \
    ../../game/shared/usermessages.cpp \
    ../../game/shared/util_shared.cpp \
    ../../game/shared/vehicle_viewblend_shared.cpp \
    ../../game/shared/voice_banmgr.cpp \
    ../../game/shared/voice_status.cpp \
    ../../game/shared/weapon_parse.cpp \
    ../../game/shared/weapon_parse_default.cpp \
    ../../public/bone_accessor.cpp \
    ../../public/bone_setup.cpp \
    ../../public/client_class.cpp \
    ../../public/collisionutils.cpp \
    ../../public/crtmemdebug.cpp \
    ../../public/dt_recv.cpp \
    ../../public/dt_utlvector_common.cpp \
    ../../public/dt_utlvector_recv.cpp \
    ../../public/filesystem_helpers.cpp \
    ../../public/haptics/haptic_msgs.cpp \
    ../../public/interpolatortypes.cpp \
    ../../public/jigglebones.cpp \
    ../../public/networkvar.cpp \
    ../../public/posedebugger.cpp \
    ../../public/renamed_recvtable_compat.cpp \
    ../../public/rope_physics.cpp \
    ../../public/scratchpad3d.cpp \
    ../../public/ScratchPadUtils.cpp \
    ../../public/sentence.cpp \
    ../../public/simple_physics.cpp \
    ../../public/SoundParametersInternal.cpp \
    ../../public/stringregistry.cpp \
    ../../public/studio.cpp \
    ../../public/tier0/memoverride.cpp \
    ../../public/tools/bonelist.cpp \
    ../../public/vallocator.cpp \
    ../../public/vgui_controls/vgui_controls.cpp \
    achievement_notification_panel.cpp \
    alphamaterialproxy.cpp \
    animatedentitytextureproxy.cpp \
    animatedoffsettextureproxy.cpp \
    animatedtextureproxy.cpp \
    AnimateSpecificTextureProxy.cpp \
    baseanimatedtextureproxy.cpp \
    baseclientrendertargets.cpp \
    basepresence.cpp \
    beamdraw.cpp \
    bone_merge_cache.cpp \
    camomaterialproxy.cpp \
    cdll_bounded_cvars.cpp \
    cdll_client_int.cpp \
    cdll_util.cpp \
    classmap.cpp \
    clienteffectprecachesystem.cpp \
    cliententitylist.cpp \
    clientleafsystem.cpp \
    clientmode_shared.cpp \
    clientshadowmgr.cpp \
    clientsideeffects.cpp \
    clientsideeffects_test.cpp \
    clientsteamcontext.cpp \
    client_factorylist.cpp \
    client_thinklist.cpp \
    client_virtualreality.cpp \
    cl_mat_stub.cpp \
    colorcorrectionmgr.cpp \
    commentary_modelviewer.cpp \
    c_ai_basehumanoid.cpp \
    c_ai_basenpc.cpp \
    c_baseanimating.cpp \
    c_baseanimatingoverlay.cpp \
    c_basecombatcharacter.cpp \
    c_basecombatweapon.cpp \
    c_basedoor.cpp \
    c_baseentity.cpp \
    c_baseflex.cpp \
    c_baseplayer.cpp \
    c_basetempentity.cpp \
    c_baseviewmodel.cpp \
    c_breakableprop.cpp \
    c_colorcorrection.cpp \
    c_colorcorrectionvolume.cpp \
    c_dynamiclight.cpp \
    c_effects.cpp \
    c_entitydissolve.cpp \
    c_entityparticletrail.cpp \
    c_env_fog_controller.cpp \
    c_env_particlescript.cpp \
    c_env_projectedtexture.cpp \
    c_env_screenoverlay.cpp \
    c_env_tonemap_controller.cpp \
    c_fire_smoke.cpp \
    c_fish.cpp \
    c_func_areaportalwindow.cpp \
    c_func_breakablesurf.cpp \
    c_func_conveyor.cpp \
    c_func_dust.cpp \
    c_func_lod.cpp \
    c_func_occluder.cpp \
    c_func_reflective_glass.cpp \
    c_func_rotating.cpp \
    c_func_smokevolume.cpp \
    c_func_tracktrain.cpp \
    c_gib.cpp \
    c_hairball.cpp \
    c_impact_effects.cpp \
    c_info_overlay_accessor.cpp \
    c_lightglow.cpp \
    C_MaterialModifyControl.cpp \
    c_movie_explosion.cpp \
    c_particle_fire.cpp \
    c_particle_smokegrenade.cpp \
    c_particle_system.cpp \
    c_physbox.cpp \
    c_physicsprop.cpp \
    c_physmagnet.cpp \
    c_pixel_visibility.cpp \
    c_plasma.cpp \
    c_playerresource.cpp \
    c_point_camera.cpp \
    c_point_commentary_node.cpp \
    c_props.cpp \
    c_prop_vehicle.cpp \
    c_ragdoll_manager.cpp \
    c_recipientfilter.cpp \
    c_rope.cpp \
    c_rumble.cpp \
    c_sceneentity.cpp \
    c_shadowcontrol.cpp \
    c_slideshow_display.cpp \
    c_smokestack.cpp \
    c_smoke_trail.cpp \
    c_soundscape.cpp \
    c_spotlight_end.cpp \
    c_sprite.cpp \
    c_sprite_perfmonitor.cpp \
    c_steamjet.cpp \
    c_stickybolt.cpp \
    c_sun.cpp \
    c_te.cpp \
    c_team.cpp \
    c_team_objectiveresource.cpp \
    c_tesla.cpp \
    c_testtraceline.cpp \
    c_test_proxytoggle.cpp \
    c_te_armorricochet.cpp \
    c_te_basebeam.cpp \
    c_te_beamentpoint.cpp \
    c_te_beaments.cpp \
    c_te_beamfollow.cpp \
    c_te_beamlaser.cpp \
    c_te_beampoints.cpp \
    c_te_beamring.cpp \
    c_te_beamringpoint.cpp \
    c_te_beamspline.cpp \
    c_te_bloodsprite.cpp \
    c_te_bloodstream.cpp \
    c_te_breakmodel.cpp \
    c_te_bspdecal.cpp \
    c_te_bubbles.cpp \
    c_te_bubbletrail.cpp \
    c_te_clientprojectile.cpp \
    c_te_decal.cpp \
    c_te_dynamiclight.cpp \
    c_te_effect_dispatch.cpp \
    c_te_energysplash.cpp \
    c_te_explosion.cpp \
    c_te_fizz.cpp \
    c_te_footprint.cpp \
    c_te_glassshatter.cpp \
    c_te_glowsprite.cpp \
    c_te_impact.cpp \
    c_te_killplayerattachments.cpp \
    c_te_largefunnel.cpp \
    c_te_legacytempents.cpp \
    c_te_muzzleflash.cpp \
    c_te_particlesystem.cpp \
    c_te_physicsprop.cpp \
    c_te_playerdecal.cpp \
    c_te_projecteddecal.cpp \
    c_te_showline.cpp \
    c_te_smoke.cpp \
    c_te_sparks.cpp \
    c_te_sprite.cpp \
    c_te_spritespray.cpp \
    c_te_worlddecal.cpp \
    c_tracer.cpp \
    c_user_message_register.cpp \
    c_vehicle_choreo_generic.cpp \
    c_vehicle_jeep.cpp \
    c_vguiscreen.cpp \
    C_WaterLODControl.cpp \
    c_world.cpp \
    death.cpp \
    detailobjectsystem.cpp \
    dummyproxy.cpp \
    EffectsClient.cpp \
    entityoriginmaterialproxy.cpp \
    entity_client_tools.cpp \
    episodic/c_vort_charge_token.cpp \
    flashlighteffect.cpp \
    functionproxy.cpp \
    fx.cpp \
    fx_blood.cpp \
    fx_cube.cpp \
    fx_discreetline.cpp \
    fx_envelope.cpp \
    fx_explosion.cpp \
    fx_fleck.cpp \
    fx_impact.cpp \
    fx_interpvalue.cpp \
    fx_line.cpp \
    fx_quad.cpp \
    fx_shelleject.cpp \
    fx_sparks.cpp \
    fx_staticline.cpp \
    fx_tracer.cpp \
    fx_trail.cpp \
    fx_water.cpp \
    gametrace_client.cpp \
    game_controls/basemodelpanel.cpp \
    game_controls/basemodel_panel.cpp \
    game_controls/baseviewport.cpp \
    game_controls/ClientScoreBoardDialog.cpp \
    game_controls/commandmenu.cpp \
    game_controls/IconPanel.cpp \
    game_controls/intromenu.cpp \
    game_controls/MapOverview.cpp \
    game_controls/NavProgress.cpp \
    game_controls/SpectatorGUI.cpp \
    game_controls/teammenu.cpp \
    game_controls/vguitextwindow.cpp \
    geiger.cpp \
    glow_outline_effect.cpp \
    glow_overlay.cpp \
    history_resource.cpp \
    hl2/clientmode_hlnormal.cpp \
    hl2/c_antlion_dust.cpp \
    hl2/c_ar2_explosion.cpp \
    hl2/c_barnacle.cpp \
    hl2/c_barney.cpp \
    hl2/c_basehelicopter.cpp \
    hl2/c_basehlcombatweapon.cpp \
    hl2/c_basehlplayer.cpp \
    hl2/c_citadel_effects.cpp \
    hl2/c_corpse.cpp \
    hl2/c_env_alyxtemp.cpp \
    hl2/c_env_headcrabcanister.cpp \
    hl2/c_env_starfield.cpp \
    hl2/C_Func_Monitor.cpp \
    hl2/c_func_tankmortar.cpp \
    hl2/c_hl2_playerlocaldata.cpp \
    hl2/c_info_teleporter_countdown.cpp \
    hl2/c_npc_antlionguard.cpp \
    hl2/c_npc_combinegunship.cpp \
    hl2/c_npc_manhack.cpp \
    hl2/c_npc_rollermine.cpp \
    hl2/c_plasma_beam_node.cpp \
    hl2/c_prop_combine_ball.cpp \
    hl2/c_rotorwash.cpp \
    hl2/c_script_intro.cpp \
    hl2/c_strider.cpp \
    hl2/c_te_concussiveexplosion.cpp \
    hl2/c_te_flare.cpp \
    hl2/c_thumper_dust.cpp \
    hl2/c_vehicle_airboat.cpp \
    hl2/c_vehicle_cannon.cpp \
    hl2/c_vehicle_crane.cpp \
    hl2/c_vehicle_prisoner_pod.cpp \
    hl2/c_waterbullet.cpp \
    hl2/c_weapon_crossbow.cpp \
    hl2/c_weapon_physcannon.cpp \
    hl2/c_weapon_stunstick.cpp \
    hl2/c_weapon__stubs_hl2.cpp \
    hl2/fx_antlion.cpp \
    hl2/fx_bugbait.cpp \
    hl2/fx_hl2_impacts.cpp \
    hl2/fx_hl2_tracers.cpp \
    hl2/hl2_clientmode.cpp \
    hl2/hl_in_main.cpp \
    hl2/hl_prediction.cpp \
    hl2/hud_ammo.cpp \
    hl2/hud_autoaim.cpp \
    hl2/hud_battery.cpp \
    hl2/hud_blood.cpp \
    hl2/hud_credits.cpp \
    hl2/hud_damageindicator.cpp \
    hl2/hud_filmdemo.cpp \
    hl2/hud_flashlight.cpp \
    hl2/hud_hdrdemo.cpp \
    hl2/hud_health.cpp \
    hl2/hud_poisondamageindicator.cpp \
    hl2/hud_quickinfo.cpp \
    hl2/hud_suitpower.cpp \
    hl2/hud_weaponselection.cpp \
    hl2/hud_zoom.cpp \
    hl2/shieldproxy.cpp \
    hl2/vgui_rootpanel_hl2.cpp \
    hltvcamera.cpp \
    hud.cpp \
    hud_animationinfo.cpp \
    hud_basechat.cpp \
    hud_basetimer.cpp \
    hud_bitmapnumericdisplay.cpp \
    hud_chat.cpp \
    hud_closecaption.cpp \
    hud_crosshair.cpp \
    hud_element_helper.cpp \
    hud_hintdisplay.cpp \
    hud_lcd.cpp \
    hud_msg.cpp \
    hud_numericdisplay.cpp \
    hud_pdump.cpp \
    hud_posture.cpp \
    hud_redraw.cpp \
    hud_squadstatus.cpp \
    hud_vehicle.cpp \
    hud_weapon.cpp \
    initializer.cpp \
    interpolatedvar.cpp \
    in_camera.cpp \
    in_joystick.cpp \
    in_main.cpp \
    in_mouse.cpp \
    in_steamcontroller.cpp \
    IsNPCProxy.cpp \
    lampbeamproxy.cpp \
    lamphaloproxy.cpp \
    mathproxy.cpp \
    matrixproxy.cpp \
    menu.cpp \
    message.cpp \
    movehelper_client.cpp \
    mp3player.cpp \
    mumble.cpp \
    panelmetaclassmgr.cpp \
    particlemgr.cpp \
    particlesphererenderer.cpp \
    particles_attractor.cpp \
    particles_ez.cpp \
    particles_localspace.cpp \
    particles_new.cpp \
    particles_simple.cpp \
    particle_collision.cpp \
    particle_litsmokeemitter.cpp \
    particle_proxies.cpp \
    particle_simple3d.cpp \
    perfvisualbenchmark.cpp \
    physics.cpp \
    physics_main_client.cpp \
    physpropclientside.cpp \
    playerandobjectenumerator.cpp \
    playerspawncache.cpp \
    prediction.cpp \
    proxyentity.cpp \
    ProxyHealth.cpp \
    proxyplayer.cpp \
    proxypupil.cpp \
    ragdoll.cpp \
    recvproxy.cpp \
    rendertexture.cpp \
    replay/cdll_replay.cpp \
    replay/replaycamera.cpp \
    ScreenSpaceEffects.cpp \
    simple_keys.cpp \
    sixense/in_sixense.cpp \
    sixense/in_sixense_gesture_bindings.cpp \
    smoke_fog_overlay.cpp \
    splinepatch.cpp \
    spritemodel.cpp \
    stdafx.cpp \
    studio_stats.cpp \
    texturescrollmaterialproxy.cpp \
    text_message.cpp \
    timematerialproxy.cpp \
    toggletextureproxy.cpp \
    toolframework_client.cpp \
    train.cpp \
    vgui_avatarimage.cpp \
    vgui_basepanel.cpp \
    vgui_bitmapbutton.cpp \
    vgui_bitmapimage.cpp \
    vgui_bitmappanel.cpp \
    vgui_centerstringpanel.cpp \
    vgui_consolepanel.cpp \
    vgui_debugoverlaypanel.cpp \
    vgui_fpspanel.cpp \
    vgui_game_viewport.cpp \
    vgui_grid.cpp \
    vgui_int.cpp \
    vgui_loadingdiscpanel.cpp \
    vgui_messagechars.cpp \
    vgui_netgraphpanel.cpp \
    vgui_schemevisualizer.cpp \
    vgui_slideshow_display_screen.cpp \
    vgui_video.cpp \
    vgui_video_player.cpp \
    view.cpp \
    viewangleanim.cpp \
    ViewConeImage.cpp \
    viewdebug.cpp \
    viewpostprocess.cpp \
    viewrender.cpp \
    view_beams.cpp \
    view_effects.cpp \
    view_scene.cpp \
    warp_overlay.cpp \
    WaterLODMaterialProxy.cpp \
    weapons_resource.cpp \
    weapon_selection.cpp \
    WorldDimsProxy.cpp \


LIBFILES = \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/bitmap.a \
    ../../lib/public/linux32/choreoobjects.a \
    ../../lib/public/linux32/dmxloader.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/matsys_controls.a \
    ../../lib/public/linux32/particles.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \
    ../../lib/public/linux32/vgui_controls.a \
    ../../lib/public/linux32/vtf.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \
    -L../../lib/public/linux32 -lsteam_api \


LIBFILENAMES = \
    ../../lib/public/linux32/bitmap.a \
    ../../lib/public/linux32/choreoobjects.a \
    ../../lib/public/linux32/dmxloader.a \
    ../../lib/public/linux32/libsteam_api.so \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/matsys_controls.a \
    ../../lib/public/linux32/particles.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \
    ../../lib/public/linux32/vgui_controls.a \
    ../../lib/public/linux32/vtf.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/compiledcaptionswap.P
endif

$(OBJ_DIR)/compiledcaptionswap.o : $(abspath ../../common/compiledcaptionswap.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/language.P
endif

$(OBJ_DIR)/language.o : $(abspath ../../common/language.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/randoverride.P
endif

$(OBJ_DIR)/randoverride.o : $(abspath ../../common/randoverride.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamid.P
endif

$(OBJ_DIR)/steamid.o : $(abspath ../../common/steamid.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vote_controller.P
endif

$(OBJ_DIR)/c_vote_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vote_controller.o : $(abspath ../../game/client/c_vote_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievementmgr.P
endif

$(OBJ_DIR)/achievementmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievementmgr.o : $(abspath ../../game/shared/achievementmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievements_hlx.P
endif

$(OBJ_DIR)/achievements_hlx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievements_hlx.o : $(abspath ../../game/shared/achievements_hlx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievement_saverestore.P
endif

$(OBJ_DIR)/achievement_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievement_saverestore.o : $(abspath ../../game/shared/achievement_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/activitylist.P
endif

$(OBJ_DIR)/activitylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/activitylist.o : $(abspath ../../game/shared/activitylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ammodef.P
endif

$(OBJ_DIR)/ammodef.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ammodef.o : $(abspath ../../game/shared/ammodef.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animation.P
endif

$(OBJ_DIR)/animation.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animation.o : $(abspath ../../game/shared/animation.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseachievement.P
endif

$(OBJ_DIR)/baseachievement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseachievement.o : $(abspath ../../game/shared/baseachievement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatcharacter_shared.P
endif

$(OBJ_DIR)/basecombatcharacter_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatcharacter_shared.o : $(abspath ../../game/shared/basecombatcharacter_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatweapon_shared.P
endif

$(OBJ_DIR)/basecombatweapon_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatweapon_shared.o : $(abspath ../../game/shared/basecombatweapon_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseentity_shared.P
endif

$(OBJ_DIR)/baseentity_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseentity_shared.o : $(abspath ../../game/shared/baseentity_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_shared.P
endif

$(OBJ_DIR)/basegrenade_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_shared.o : $(abspath ../../game/shared/basegrenade_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseparticleentity.P
endif

$(OBJ_DIR)/baseparticleentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseparticleentity.o : $(abspath ../../game/shared/baseparticleentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseplayer_shared.P
endif

$(OBJ_DIR)/baseplayer_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseplayer_shared.o : $(abspath ../../game/shared/baseplayer_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseprojectile.P
endif

$(OBJ_DIR)/baseprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseprojectile.o : $(abspath ../../game/shared/baseprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseviewmodel_shared.P
endif

$(OBJ_DIR)/baseviewmodel_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseviewmodel_shared.o : $(abspath ../../game/shared/baseviewmodel_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_playeranimstate.P
endif

$(OBJ_DIR)/base_playeranimstate.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/base_playeranimstate.o : $(abspath ../../game/shared/base_playeranimstate.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/beam_shared.P
endif

$(OBJ_DIR)/beam_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/beam_shared.o : $(abspath ../../game/shared/beam_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cam_thirdperson.P
endif

$(OBJ_DIR)/cam_thirdperson.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cam_thirdperson.o : $(abspath ../../game/shared/cam_thirdperson.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionproperty.P
endif

$(OBJ_DIR)/collisionproperty.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/collisionproperty.o : $(abspath ../../game/shared/collisionproperty.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/death_pose.P
endif

$(OBJ_DIR)/death_pose.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/death_pose.o : $(abspath ../../game/shared/death_pose.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugoverlay_shared.P
endif

$(OBJ_DIR)/debugoverlay_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/debugoverlay_shared.o : $(abspath ../../game/shared/debugoverlay_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/decals.P
endif

$(OBJ_DIR)/decals.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/decals.o : $(abspath ../../game/shared/decals.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/effect_dispatch_data.P
endif

$(OBJ_DIR)/effect_dispatch_data.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/effect_dispatch_data.o : $(abspath ../../game/shared/effect_dispatch_data.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ehandle.P
endif

$(OBJ_DIR)/ehandle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ehandle.o : $(abspath ../../game/shared/ehandle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entitylist_base.P
endif

$(OBJ_DIR)/entitylist_base.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entitylist_base.o : $(abspath ../../game/shared/entitylist_base.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityParticleTrail_Shared.P
endif

$(OBJ_DIR)/EntityParticleTrail_Shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityParticleTrail_Shared.o : $(abspath ../../game/shared/EntityParticleTrail_Shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_detail_controller.P
endif

$(OBJ_DIR)/env_detail_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_detail_controller.o : $(abspath ../../game/shared/env_detail_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_wind_shared.P
endif

$(OBJ_DIR)/env_wind_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_wind_shared.o : $(abspath ../../game/shared/env_wind_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eventlist.P
endif

$(OBJ_DIR)/eventlist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/eventlist.o : $(abspath ../../game/shared/eventlist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_ladder.P
endif

$(OBJ_DIR)/func_ladder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_ladder.o : $(abspath ../../game/shared/func_ladder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamemovement.P
endif

$(OBJ_DIR)/gamemovement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamemovement.o : $(abspath ../../game/shared/gamemovement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamerules.P
endif

$(OBJ_DIR)/gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamerules.o : $(abspath ../../game/shared/gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamerules_register.P
endif

$(OBJ_DIR)/gamerules_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamerules_register.o : $(abspath ../../game/shared/gamerules_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameStats.P
endif

$(OBJ_DIR)/GameStats.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/GameStats.o : $(abspath ../../game/shared/GameStats.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamestringpool.P
endif

$(OBJ_DIR)/gamestringpool.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamestringpool.o : $(abspath ../../game/shared/gamestringpool.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamevars_shared.P
endif

$(OBJ_DIR)/gamevars_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamevars_shared.o : $(abspath ../../game/shared/gamevars_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hintmessage.P
endif

$(OBJ_DIR)/hintmessage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hintmessage.o : $(abspath ../../game/shared/hintmessage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hintsystem.P
endif

$(OBJ_DIR)/hintsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hintsystem.o : $(abspath ../../game/shared/hintsystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievements_hl2.P
endif

$(OBJ_DIR)/achievements_hl2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievements_hl2.o : $(abspath ../../game/shared/hl2/achievements_hl2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basehlcombatweapon_shared.P
endif

$(OBJ_DIR)/basehlcombatweapon_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basehlcombatweapon_shared.o : $(abspath ../../game/shared/hl2/basehlcombatweapon_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_headcrabcanister_shared.P
endif

$(OBJ_DIR)/env_headcrabcanister_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_headcrabcanister_shared.o : $(abspath ../../game/shared/hl2/env_headcrabcanister_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_gamerules.P
endif

$(OBJ_DIR)/hl2_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_gamerules.o : $(abspath ../../game/shared/hl2/hl2_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_usermessages.P
endif

$(OBJ_DIR)/hl2_usermessages.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_usermessages.o : $(abspath ../../game/shared/hl2/hl2_usermessages.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_gamemovement.P
endif

$(OBJ_DIR)/hl_gamemovement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_gamemovement.o : $(abspath ../../game/shared/hl2/hl_gamemovement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/igamesystem.P
endif

$(OBJ_DIR)/igamesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/igamesystem.o : $(abspath ../../game/shared/igamesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interval.P
endif

$(OBJ_DIR)/interval.o : $(abspath ../../game/shared/interval.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mapentities_shared.P
endif

$(OBJ_DIR)/mapentities_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mapentities_shared.o : $(abspath ../../game/shared/mapentities_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movevars_shared.P
endif

$(OBJ_DIR)/movevars_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movevars_shared.o : $(abspath ../../game/shared/movevars_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mp_shareddefs.P
endif

$(OBJ_DIR)/mp_shareddefs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mp_shareddefs.o : $(abspath ../../game/shared/mp_shareddefs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/multiplay_gamerules.P
endif

$(OBJ_DIR)/multiplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/multiplay_gamerules.o : $(abspath ../../game/shared/multiplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/obstacle_pushaway.P
endif

$(OBJ_DIR)/obstacle_pushaway.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/obstacle_pushaway.o : $(abspath ../../game/shared/obstacle_pushaway.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlesystemquery.P
endif

$(OBJ_DIR)/particlesystemquery.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particlesystemquery.o : $(abspath ../../game/shared/particlesystemquery.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_parse.P
endif

$(OBJ_DIR)/particle_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_parse.o : $(abspath ../../game/shared/particle_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_property.P
endif

$(OBJ_DIR)/particle_property.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_property.o : $(abspath ../../game/shared/particle_property.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_main_shared.P
endif

$(OBJ_DIR)/physics_main_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_main_shared.o : $(abspath ../../game/shared/physics_main_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_saverestore.P
endif

$(OBJ_DIR)/physics_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_saverestore.o : $(abspath ../../game/shared/physics_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_shared.P
endif

$(OBJ_DIR)/physics_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_shared.o : $(abspath ../../game/shared/physics_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_bonusmaps_accessor.P
endif

$(OBJ_DIR)/point_bonusmaps_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_bonusmaps_accessor.o : $(abspath ../../game/shared/point_bonusmaps_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_posecontroller.P
endif

$(OBJ_DIR)/point_posecontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_posecontroller.o : $(abspath ../../game/shared/point_posecontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/precache_register.P
endif

$(OBJ_DIR)/precache_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/precache_register.o : $(abspath ../../game/shared/precache_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/predictableid.P
endif

$(OBJ_DIR)/predictableid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/predictableid.o : $(abspath ../../game/shared/predictableid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/predictioncopy.P
endif

$(OBJ_DIR)/predictioncopy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/predictioncopy.o : $(abspath ../../game/shared/predictioncopy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/props_shared.P
endif

$(OBJ_DIR)/props_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/props_shared.o : $(abspath ../../game/shared/props_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll_shared.P
endif

$(OBJ_DIR)/ragdoll_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ragdoll_shared.o : $(abspath ../../game/shared/ragdoll_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope_helpers.P
endif

$(OBJ_DIR)/rope_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/rope_helpers.o : $(abspath ../../game/shared/rope_helpers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/saverestore.P
endif

$(OBJ_DIR)/saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/saverestore.o : $(abspath ../../game/shared/saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sceneentity_shared.P
endif

$(OBJ_DIR)/sceneentity_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sceneentity_shared.o : $(abspath ../../game/shared/sceneentity_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/script_intro_shared.P
endif

$(OBJ_DIR)/script_intro_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/script_intro_shared.o : $(abspath ../../game/shared/script_intro_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sequence_Transitioner.P
endif

$(OBJ_DIR)/sequence_Transitioner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sequence_Transitioner.o : $(abspath ../../game/shared/sequence_Transitioner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sheetsimulator.P
endif

$(OBJ_DIR)/sheetsimulator.o : $(abspath ../../game/shared/sheetsimulator.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simtimer.P
endif

$(OBJ_DIR)/simtimer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/simtimer.o : $(abspath ../../game/shared/simtimer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/singleplay_gamerules.P
endif

$(OBJ_DIR)/singleplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/singleplay_gamerules.o : $(abspath ../../game/shared/singleplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sixense_convars.P
endif

$(OBJ_DIR)/sixense_convars.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sixense_convars.o : $(abspath ../../game/shared/sixense/sixense_convars.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SoundEmitterSystem.P
endif

$(OBJ_DIR)/SoundEmitterSystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SoundEmitterSystem.o : $(abspath ../../game/shared/SoundEmitterSystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundenvelope.P
endif

$(OBJ_DIR)/soundenvelope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundenvelope.o : $(abspath ../../game/shared/soundenvelope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Sprite.P
endif

$(OBJ_DIR)/Sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/Sprite.o : $(abspath ../../game/shared/Sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SpriteTrail.P
endif

$(OBJ_DIR)/SpriteTrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SpriteTrail.o : $(abspath ../../game/shared/SpriteTrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio_shared.P
endif

$(OBJ_DIR)/studio_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/studio_shared.o : $(abspath ../../game/shared/studio_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/takedamageinfo.P
endif

$(OBJ_DIR)/takedamageinfo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/takedamageinfo.o : $(abspath ../../game/shared/takedamageinfo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teamplayroundbased_gamerules.P
endif

$(OBJ_DIR)/teamplayroundbased_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/teamplayroundbased_gamerules.o : $(abspath ../../game/shared/teamplayroundbased_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teamplay_gamerules.P
endif

$(OBJ_DIR)/teamplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/teamplay_gamerules.o : $(abspath ../../game/shared/teamplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/test_ehandle.P
endif

$(OBJ_DIR)/test_ehandle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/test_ehandle.o : $(abspath ../../game/shared/test_ehandle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/usercmd.P
endif

$(OBJ_DIR)/usercmd.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/usercmd.o : $(abspath ../../game/shared/usercmd.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/usermessages.P
endif

$(OBJ_DIR)/usermessages.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/usermessages.o : $(abspath ../../game/shared/usermessages.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/util_shared.P
endif

$(OBJ_DIR)/util_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/util_shared.o : $(abspath ../../game/shared/util_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_viewblend_shared.P
endif

$(OBJ_DIR)/vehicle_viewblend_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_viewblend_shared.o : $(abspath ../../game/shared/vehicle_viewblend_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_banmgr.P
endif

$(OBJ_DIR)/voice_banmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/voice_banmgr.o : $(abspath ../../game/shared/voice_banmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_status.P
endif

$(OBJ_DIR)/voice_status.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/voice_status.o : $(abspath ../../game/shared/voice_status.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_parse.P
endif

$(OBJ_DIR)/weapon_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_parse.o : $(abspath ../../game/shared/weapon_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_parse_default.P
endif

$(OBJ_DIR)/weapon_parse_default.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_parse_default.o : $(abspath ../../game/shared/weapon_parse_default.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bone_accessor.P
endif

$(OBJ_DIR)/bone_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bone_accessor.o : $(abspath ../../public/bone_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bone_setup.P
endif

$(OBJ_DIR)/bone_setup.o : $(abspath ../../public/bone_setup.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_class.P
endif

$(OBJ_DIR)/client_class.o : $(abspath ../../public/client_class.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionutils.P
endif

$(OBJ_DIR)/collisionutils.o : $(abspath ../../public/collisionutils.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/crtmemdebug.P
endif

$(OBJ_DIR)/crtmemdebug.o : $(abspath ../../public/crtmemdebug.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_recv.P
endif

$(OBJ_DIR)/dt_recv.o : $(abspath ../../public/dt_recv.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_common.P
endif

$(OBJ_DIR)/dt_utlvector_common.o : $(abspath ../../public/dt_utlvector_common.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_recv.P
endif

$(OBJ_DIR)/dt_utlvector_recv.o : $(abspath ../../public/dt_utlvector_recv.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../../public/filesystem_helpers.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/haptic_msgs.P
endif

$(OBJ_DIR)/haptic_msgs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/haptic_msgs.o : $(abspath ../../public/haptics/haptic_msgs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interpolatortypes.P
endif

$(OBJ_DIR)/interpolatortypes.o : $(abspath ../../public/interpolatortypes.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/jigglebones.P
endif

$(OBJ_DIR)/jigglebones.o : $(abspath ../../public/jigglebones.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkvar.P
endif

$(OBJ_DIR)/networkvar.o : $(abspath ../../public/networkvar.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/posedebugger.P
endif

$(OBJ_DIR)/posedebugger.o : $(abspath ../../public/posedebugger.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/renamed_recvtable_compat.P
endif

$(OBJ_DIR)/renamed_recvtable_compat.o : $(abspath ../../public/renamed_recvtable_compat.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope_physics.P
endif

$(OBJ_DIR)/rope_physics.o : $(abspath ../../public/rope_physics.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scratchpad3d.P
endif

$(OBJ_DIR)/scratchpad3d.o : $(abspath ../../public/scratchpad3d.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScratchPadUtils.P
endif

$(OBJ_DIR)/ScratchPadUtils.o : $(abspath ../../public/ScratchPadUtils.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sentence.P
endif

$(OBJ_DIR)/sentence.o : $(abspath ../../public/sentence.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simple_physics.P
endif

$(OBJ_DIR)/simple_physics.o : $(abspath ../../public/simple_physics.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SoundParametersInternal.P
endif

$(OBJ_DIR)/SoundParametersInternal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SoundParametersInternal.o : $(abspath ../../public/SoundParametersInternal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stringregistry.P
endif

$(OBJ_DIR)/stringregistry.o : $(abspath ../../public/stringregistry.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio.P
endif

$(OBJ_DIR)/studio.o : $(abspath ../../public/studio.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bonelist.P
endif

$(OBJ_DIR)/bonelist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bonelist.o : $(abspath ../../public/tools/bonelist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vallocator.P
endif

$(OBJ_DIR)/vallocator.o : $(abspath ../../public/vallocator.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../../public/vgui_controls/vgui_controls.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievement_notification_panel.P
endif

$(OBJ_DIR)/achievement_notification_panel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievement_notification_panel.o : $(abspath achievement_notification_panel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/alphamaterialproxy.P
endif

$(OBJ_DIR)/alphamaterialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/alphamaterialproxy.o : $(abspath alphamaterialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animatedentitytextureproxy.P
endif

$(OBJ_DIR)/animatedentitytextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animatedentitytextureproxy.o : $(abspath animatedentitytextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animatedoffsettextureproxy.P
endif

$(OBJ_DIR)/animatedoffsettextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animatedoffsettextureproxy.o : $(abspath animatedoffsettextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animatedtextureproxy.P
endif

$(OBJ_DIR)/animatedtextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animatedtextureproxy.o : $(abspath animatedtextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AnimateSpecificTextureProxy.P
endif

$(OBJ_DIR)/AnimateSpecificTextureProxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/AnimateSpecificTextureProxy.o : $(abspath AnimateSpecificTextureProxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseanimatedtextureproxy.P
endif

$(OBJ_DIR)/baseanimatedtextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseanimatedtextureproxy.o : $(abspath baseanimatedtextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseclientrendertargets.P
endif

$(OBJ_DIR)/baseclientrendertargets.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseclientrendertargets.o : $(abspath baseclientrendertargets.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basepresence.P
endif

$(OBJ_DIR)/basepresence.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basepresence.o : $(abspath basepresence.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/beamdraw.P
endif

$(OBJ_DIR)/beamdraw.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/beamdraw.o : $(abspath beamdraw.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bone_merge_cache.P
endif

$(OBJ_DIR)/bone_merge_cache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bone_merge_cache.o : $(abspath bone_merge_cache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/camomaterialproxy.P
endif

$(OBJ_DIR)/camomaterialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/camomaterialproxy.o : $(abspath camomaterialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_bounded_cvars.P
endif

$(OBJ_DIR)/cdll_bounded_cvars.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cdll_bounded_cvars.o : $(abspath cdll_bounded_cvars.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_client_int.P
endif

$(OBJ_DIR)/cdll_client_int.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cdll_client_int.o : $(abspath cdll_client_int.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_util.P
endif

$(OBJ_DIR)/cdll_util.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cdll_util.o : $(abspath cdll_util.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/classmap.P
endif

$(OBJ_DIR)/classmap.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/classmap.o : $(abspath classmap.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clienteffectprecachesystem.P
endif

$(OBJ_DIR)/clienteffectprecachesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clienteffectprecachesystem.o : $(abspath clienteffectprecachesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cliententitylist.P
endif

$(OBJ_DIR)/cliententitylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cliententitylist.o : $(abspath cliententitylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientleafsystem.P
endif

$(OBJ_DIR)/clientleafsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientleafsystem.o : $(abspath clientleafsystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientmode_shared.P
endif

$(OBJ_DIR)/clientmode_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientmode_shared.o : $(abspath clientmode_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientshadowmgr.P
endif

$(OBJ_DIR)/clientshadowmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientshadowmgr.o : $(abspath clientshadowmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientsideeffects.P
endif

$(OBJ_DIR)/clientsideeffects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientsideeffects.o : $(abspath clientsideeffects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientsideeffects_test.P
endif

$(OBJ_DIR)/clientsideeffects_test.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientsideeffects_test.o : $(abspath clientsideeffects_test.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientsteamcontext.P
endif

$(OBJ_DIR)/clientsteamcontext.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientsteamcontext.o : $(abspath clientsteamcontext.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_factorylist.P
endif

$(OBJ_DIR)/client_factorylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/client_factorylist.o : $(abspath client_factorylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_thinklist.P
endif

$(OBJ_DIR)/client_thinklist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/client_thinklist.o : $(abspath client_thinklist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_virtualreality.P
endif

$(OBJ_DIR)/client_virtualreality.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/client_virtualreality.o : $(abspath client_virtualreality.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_mat_stub.P
endif

$(OBJ_DIR)/cl_mat_stub.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cl_mat_stub.o : $(abspath cl_mat_stub.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrectionmgr.P
endif

$(OBJ_DIR)/colorcorrectionmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/colorcorrectionmgr.o : $(abspath colorcorrectionmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/commentary_modelviewer.P
endif

$(OBJ_DIR)/commentary_modelviewer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/commentary_modelviewer.o : $(abspath commentary_modelviewer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_ai_basehumanoid.P
endif

$(OBJ_DIR)/c_ai_basehumanoid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_ai_basehumanoid.o : $(abspath c_ai_basehumanoid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_ai_basenpc.P
endif

$(OBJ_DIR)/c_ai_basenpc.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_ai_basenpc.o : $(abspath c_ai_basenpc.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseanimating.P
endif

$(OBJ_DIR)/c_baseanimating.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseanimating.o : $(abspath c_baseanimating.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseanimatingoverlay.P
endif

$(OBJ_DIR)/c_baseanimatingoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseanimatingoverlay.o : $(abspath c_baseanimatingoverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basecombatcharacter.P
endif

$(OBJ_DIR)/c_basecombatcharacter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basecombatcharacter.o : $(abspath c_basecombatcharacter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basecombatweapon.P
endif

$(OBJ_DIR)/c_basecombatweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basecombatweapon.o : $(abspath c_basecombatweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basedoor.P
endif

$(OBJ_DIR)/c_basedoor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basedoor.o : $(abspath c_basedoor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseentity.P
endif

$(OBJ_DIR)/c_baseentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseentity.o : $(abspath c_baseentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseflex.P
endif

$(OBJ_DIR)/c_baseflex.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseflex.o : $(abspath c_baseflex.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseplayer.P
endif

$(OBJ_DIR)/c_baseplayer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseplayer.o : $(abspath c_baseplayer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basetempentity.P
endif

$(OBJ_DIR)/c_basetempentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basetempentity.o : $(abspath c_basetempentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseviewmodel.P
endif

$(OBJ_DIR)/c_baseviewmodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseviewmodel.o : $(abspath c_baseviewmodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_breakableprop.P
endif

$(OBJ_DIR)/c_breakableprop.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_breakableprop.o : $(abspath c_breakableprop.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_colorcorrection.P
endif

$(OBJ_DIR)/c_colorcorrection.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_colorcorrection.o : $(abspath c_colorcorrection.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_colorcorrectionvolume.P
endif

$(OBJ_DIR)/c_colorcorrectionvolume.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_colorcorrectionvolume.o : $(abspath c_colorcorrectionvolume.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_dynamiclight.P
endif

$(OBJ_DIR)/c_dynamiclight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_dynamiclight.o : $(abspath c_dynamiclight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_effects.P
endif

$(OBJ_DIR)/c_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_effects.o : $(abspath c_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_entitydissolve.P
endif

$(OBJ_DIR)/c_entitydissolve.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_entitydissolve.o : $(abspath c_entitydissolve.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_entityparticletrail.P
endif

$(OBJ_DIR)/c_entityparticletrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_entityparticletrail.o : $(abspath c_entityparticletrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_fog_controller.P
endif

$(OBJ_DIR)/c_env_fog_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_fog_controller.o : $(abspath c_env_fog_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_particlescript.P
endif

$(OBJ_DIR)/c_env_particlescript.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_particlescript.o : $(abspath c_env_particlescript.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_projectedtexture.P
endif

$(OBJ_DIR)/c_env_projectedtexture.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_projectedtexture.o : $(abspath c_env_projectedtexture.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_screenoverlay.P
endif

$(OBJ_DIR)/c_env_screenoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_screenoverlay.o : $(abspath c_env_screenoverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_tonemap_controller.P
endif

$(OBJ_DIR)/c_env_tonemap_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_tonemap_controller.o : $(abspath c_env_tonemap_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_fire_smoke.P
endif

$(OBJ_DIR)/c_fire_smoke.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_fire_smoke.o : $(abspath c_fire_smoke.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_fish.P
endif

$(OBJ_DIR)/c_fish.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_fish.o : $(abspath c_fish.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_areaportalwindow.P
endif

$(OBJ_DIR)/c_func_areaportalwindow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_areaportalwindow.o : $(abspath c_func_areaportalwindow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_breakablesurf.P
endif

$(OBJ_DIR)/c_func_breakablesurf.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_breakablesurf.o : $(abspath c_func_breakablesurf.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_conveyor.P
endif

$(OBJ_DIR)/c_func_conveyor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_conveyor.o : $(abspath c_func_conveyor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_dust.P
endif

$(OBJ_DIR)/c_func_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_dust.o : $(abspath c_func_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_lod.P
endif

$(OBJ_DIR)/c_func_lod.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_lod.o : $(abspath c_func_lod.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_occluder.P
endif

$(OBJ_DIR)/c_func_occluder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_occluder.o : $(abspath c_func_occluder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_reflective_glass.P
endif

$(OBJ_DIR)/c_func_reflective_glass.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_reflective_glass.o : $(abspath c_func_reflective_glass.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_rotating.P
endif

$(OBJ_DIR)/c_func_rotating.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_rotating.o : $(abspath c_func_rotating.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_smokevolume.P
endif

$(OBJ_DIR)/c_func_smokevolume.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_smokevolume.o : $(abspath c_func_smokevolume.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_tracktrain.P
endif

$(OBJ_DIR)/c_func_tracktrain.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_tracktrain.o : $(abspath c_func_tracktrain.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_gib.P
endif

$(OBJ_DIR)/c_gib.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_gib.o : $(abspath c_gib.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_hairball.P
endif

$(OBJ_DIR)/c_hairball.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_hairball.o : $(abspath c_hairball.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_impact_effects.P
endif

$(OBJ_DIR)/c_impact_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_impact_effects.o : $(abspath c_impact_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_info_overlay_accessor.P
endif

$(OBJ_DIR)/c_info_overlay_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_info_overlay_accessor.o : $(abspath c_info_overlay_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_lightglow.P
endif

$(OBJ_DIR)/c_lightglow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_lightglow.o : $(abspath c_lightglow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/C_MaterialModifyControl.P
endif

$(OBJ_DIR)/C_MaterialModifyControl.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/C_MaterialModifyControl.o : $(abspath C_MaterialModifyControl.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_movie_explosion.P
endif

$(OBJ_DIR)/c_movie_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_movie_explosion.o : $(abspath c_movie_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_particle_fire.P
endif

$(OBJ_DIR)/c_particle_fire.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_particle_fire.o : $(abspath c_particle_fire.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_particle_smokegrenade.P
endif

$(OBJ_DIR)/c_particle_smokegrenade.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_particle_smokegrenade.o : $(abspath c_particle_smokegrenade.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_particle_system.P
endif

$(OBJ_DIR)/c_particle_system.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_particle_system.o : $(abspath c_particle_system.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_physbox.P
endif

$(OBJ_DIR)/c_physbox.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_physbox.o : $(abspath c_physbox.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_physicsprop.P
endif

$(OBJ_DIR)/c_physicsprop.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_physicsprop.o : $(abspath c_physicsprop.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_physmagnet.P
endif

$(OBJ_DIR)/c_physmagnet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_physmagnet.o : $(abspath c_physmagnet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_pixel_visibility.P
endif

$(OBJ_DIR)/c_pixel_visibility.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_pixel_visibility.o : $(abspath c_pixel_visibility.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_plasma.P
endif

$(OBJ_DIR)/c_plasma.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_plasma.o : $(abspath c_plasma.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_playerresource.P
endif

$(OBJ_DIR)/c_playerresource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_playerresource.o : $(abspath c_playerresource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_point_camera.P
endif

$(OBJ_DIR)/c_point_camera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_point_camera.o : $(abspath c_point_camera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_point_commentary_node.P
endif

$(OBJ_DIR)/c_point_commentary_node.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_point_commentary_node.o : $(abspath c_point_commentary_node.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_props.P
endif

$(OBJ_DIR)/c_props.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_props.o : $(abspath c_props.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_prop_vehicle.P
endif

$(OBJ_DIR)/c_prop_vehicle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_prop_vehicle.o : $(abspath c_prop_vehicle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_ragdoll_manager.P
endif

$(OBJ_DIR)/c_ragdoll_manager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_ragdoll_manager.o : $(abspath c_ragdoll_manager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_recipientfilter.P
endif

$(OBJ_DIR)/c_recipientfilter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_recipientfilter.o : $(abspath c_recipientfilter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_rope.P
endif

$(OBJ_DIR)/c_rope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_rope.o : $(abspath c_rope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_rumble.P
endif

$(OBJ_DIR)/c_rumble.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_rumble.o : $(abspath c_rumble.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_sceneentity.P
endif

$(OBJ_DIR)/c_sceneentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_sceneentity.o : $(abspath c_sceneentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_shadowcontrol.P
endif

$(OBJ_DIR)/c_shadowcontrol.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_shadowcontrol.o : $(abspath c_shadowcontrol.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_slideshow_display.P
endif

$(OBJ_DIR)/c_slideshow_display.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_slideshow_display.o : $(abspath c_slideshow_display.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_smokestack.P
endif

$(OBJ_DIR)/c_smokestack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_smokestack.o : $(abspath c_smokestack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_smoke_trail.P
endif

$(OBJ_DIR)/c_smoke_trail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_smoke_trail.o : $(abspath c_smoke_trail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_soundscape.P
endif

$(OBJ_DIR)/c_soundscape.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_soundscape.o : $(abspath c_soundscape.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_spotlight_end.P
endif

$(OBJ_DIR)/c_spotlight_end.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_spotlight_end.o : $(abspath c_spotlight_end.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_sprite.P
endif

$(OBJ_DIR)/c_sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_sprite.o : $(abspath c_sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_sprite_perfmonitor.P
endif

$(OBJ_DIR)/c_sprite_perfmonitor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_sprite_perfmonitor.o : $(abspath c_sprite_perfmonitor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_steamjet.P
endif

$(OBJ_DIR)/c_steamjet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_steamjet.o : $(abspath c_steamjet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_stickybolt.P
endif

$(OBJ_DIR)/c_stickybolt.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_stickybolt.o : $(abspath c_stickybolt.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_sun.P
endif

$(OBJ_DIR)/c_sun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_sun.o : $(abspath c_sun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te.P
endif

$(OBJ_DIR)/c_te.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te.o : $(abspath c_te.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_team.P
endif

$(OBJ_DIR)/c_team.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_team.o : $(abspath c_team.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_team_objectiveresource.P
endif

$(OBJ_DIR)/c_team_objectiveresource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_team_objectiveresource.o : $(abspath c_team_objectiveresource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_tesla.P
endif

$(OBJ_DIR)/c_tesla.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_tesla.o : $(abspath c_tesla.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_testtraceline.P
endif

$(OBJ_DIR)/c_testtraceline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_testtraceline.o : $(abspath c_testtraceline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_test_proxytoggle.P
endif

$(OBJ_DIR)/c_test_proxytoggle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_test_proxytoggle.o : $(abspath c_test_proxytoggle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_armorricochet.P
endif

$(OBJ_DIR)/c_te_armorricochet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_armorricochet.o : $(abspath c_te_armorricochet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_basebeam.P
endif

$(OBJ_DIR)/c_te_basebeam.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_basebeam.o : $(abspath c_te_basebeam.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamentpoint.P
endif

$(OBJ_DIR)/c_te_beamentpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamentpoint.o : $(abspath c_te_beamentpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beaments.P
endif

$(OBJ_DIR)/c_te_beaments.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beaments.o : $(abspath c_te_beaments.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamfollow.P
endif

$(OBJ_DIR)/c_te_beamfollow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamfollow.o : $(abspath c_te_beamfollow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamlaser.P
endif

$(OBJ_DIR)/c_te_beamlaser.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamlaser.o : $(abspath c_te_beamlaser.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beampoints.P
endif

$(OBJ_DIR)/c_te_beampoints.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beampoints.o : $(abspath c_te_beampoints.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamring.P
endif

$(OBJ_DIR)/c_te_beamring.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamring.o : $(abspath c_te_beamring.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamringpoint.P
endif

$(OBJ_DIR)/c_te_beamringpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamringpoint.o : $(abspath c_te_beamringpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamspline.P
endif

$(OBJ_DIR)/c_te_beamspline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamspline.o : $(abspath c_te_beamspline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bloodsprite.P
endif

$(OBJ_DIR)/c_te_bloodsprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bloodsprite.o : $(abspath c_te_bloodsprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bloodstream.P
endif

$(OBJ_DIR)/c_te_bloodstream.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bloodstream.o : $(abspath c_te_bloodstream.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_breakmodel.P
endif

$(OBJ_DIR)/c_te_breakmodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_breakmodel.o : $(abspath c_te_breakmodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bspdecal.P
endif

$(OBJ_DIR)/c_te_bspdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bspdecal.o : $(abspath c_te_bspdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bubbles.P
endif

$(OBJ_DIR)/c_te_bubbles.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bubbles.o : $(abspath c_te_bubbles.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bubbletrail.P
endif

$(OBJ_DIR)/c_te_bubbletrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bubbletrail.o : $(abspath c_te_bubbletrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_clientprojectile.P
endif

$(OBJ_DIR)/c_te_clientprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_clientprojectile.o : $(abspath c_te_clientprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_decal.P
endif

$(OBJ_DIR)/c_te_decal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_decal.o : $(abspath c_te_decal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_dynamiclight.P
endif

$(OBJ_DIR)/c_te_dynamiclight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_dynamiclight.o : $(abspath c_te_dynamiclight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_effect_dispatch.P
endif

$(OBJ_DIR)/c_te_effect_dispatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_effect_dispatch.o : $(abspath c_te_effect_dispatch.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_energysplash.P
endif

$(OBJ_DIR)/c_te_energysplash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_energysplash.o : $(abspath c_te_energysplash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_explosion.P
endif

$(OBJ_DIR)/c_te_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_explosion.o : $(abspath c_te_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_fizz.P
endif

$(OBJ_DIR)/c_te_fizz.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_fizz.o : $(abspath c_te_fizz.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_footprint.P
endif

$(OBJ_DIR)/c_te_footprint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_footprint.o : $(abspath c_te_footprint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_glassshatter.P
endif

$(OBJ_DIR)/c_te_glassshatter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_glassshatter.o : $(abspath c_te_glassshatter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_glowsprite.P
endif

$(OBJ_DIR)/c_te_glowsprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_glowsprite.o : $(abspath c_te_glowsprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_impact.P
endif

$(OBJ_DIR)/c_te_impact.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_impact.o : $(abspath c_te_impact.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_killplayerattachments.P
endif

$(OBJ_DIR)/c_te_killplayerattachments.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_killplayerattachments.o : $(abspath c_te_killplayerattachments.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_largefunnel.P
endif

$(OBJ_DIR)/c_te_largefunnel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_largefunnel.o : $(abspath c_te_largefunnel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_legacytempents.P
endif

$(OBJ_DIR)/c_te_legacytempents.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_legacytempents.o : $(abspath c_te_legacytempents.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_muzzleflash.P
endif

$(OBJ_DIR)/c_te_muzzleflash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_muzzleflash.o : $(abspath c_te_muzzleflash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_particlesystem.P
endif

$(OBJ_DIR)/c_te_particlesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_particlesystem.o : $(abspath c_te_particlesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_physicsprop.P
endif

$(OBJ_DIR)/c_te_physicsprop.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_physicsprop.o : $(abspath c_te_physicsprop.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_playerdecal.P
endif

$(OBJ_DIR)/c_te_playerdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_playerdecal.o : $(abspath c_te_playerdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_projecteddecal.P
endif

$(OBJ_DIR)/c_te_projecteddecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_projecteddecal.o : $(abspath c_te_projecteddecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_showline.P
endif

$(OBJ_DIR)/c_te_showline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_showline.o : $(abspath c_te_showline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_smoke.P
endif

$(OBJ_DIR)/c_te_smoke.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_smoke.o : $(abspath c_te_smoke.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_sparks.P
endif

$(OBJ_DIR)/c_te_sparks.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_sparks.o : $(abspath c_te_sparks.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_sprite.P
endif

$(OBJ_DIR)/c_te_sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_sprite.o : $(abspath c_te_sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_spritespray.P
endif

$(OBJ_DIR)/c_te_spritespray.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_spritespray.o : $(abspath c_te_spritespray.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_worlddecal.P
endif

$(OBJ_DIR)/c_te_worlddecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_worlddecal.o : $(abspath c_te_worlddecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_tracer.P
endif

$(OBJ_DIR)/c_tracer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_tracer.o : $(abspath c_tracer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_user_message_register.P
endif

$(OBJ_DIR)/c_user_message_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_user_message_register.o : $(abspath c_user_message_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_choreo_generic.P
endif

$(OBJ_DIR)/c_vehicle_choreo_generic.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_choreo_generic.o : $(abspath c_vehicle_choreo_generic.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_jeep.P
endif

$(OBJ_DIR)/c_vehicle_jeep.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_jeep.o : $(abspath c_vehicle_jeep.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vguiscreen.P
endif

$(OBJ_DIR)/c_vguiscreen.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vguiscreen.o : $(abspath c_vguiscreen.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/C_WaterLODControl.P
endif

$(OBJ_DIR)/C_WaterLODControl.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/C_WaterLODControl.o : $(abspath C_WaterLODControl.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_world.P
endif

$(OBJ_DIR)/c_world.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_world.o : $(abspath c_world.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/death.P
endif

$(OBJ_DIR)/death.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/death.o : $(abspath death.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/detailobjectsystem.P
endif

$(OBJ_DIR)/detailobjectsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/detailobjectsystem.o : $(abspath detailobjectsystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dummyproxy.P
endif

$(OBJ_DIR)/dummyproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/dummyproxy.o : $(abspath dummyproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EffectsClient.P
endif

$(OBJ_DIR)/EffectsClient.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EffectsClient.o : $(abspath EffectsClient.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entityoriginmaterialproxy.P
endif

$(OBJ_DIR)/entityoriginmaterialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entityoriginmaterialproxy.o : $(abspath entityoriginmaterialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entity_client_tools.P
endif

$(OBJ_DIR)/entity_client_tools.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entity_client_tools.o : $(abspath entity_client_tools.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vort_charge_token.P
endif

$(OBJ_DIR)/c_vort_charge_token.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vort_charge_token.o : $(abspath episodic/c_vort_charge_token.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/flashlighteffect.P
endif

$(OBJ_DIR)/flashlighteffect.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/flashlighteffect.o : $(abspath flashlighteffect.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/functionproxy.P
endif

$(OBJ_DIR)/functionproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/functionproxy.o : $(abspath functionproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx.P
endif

$(OBJ_DIR)/fx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx.o : $(abspath fx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_blood.P
endif

$(OBJ_DIR)/fx_blood.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_blood.o : $(abspath fx_blood.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_cube.P
endif

$(OBJ_DIR)/fx_cube.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_cube.o : $(abspath fx_cube.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_discreetline.P
endif

$(OBJ_DIR)/fx_discreetline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_discreetline.o : $(abspath fx_discreetline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_envelope.P
endif

$(OBJ_DIR)/fx_envelope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_envelope.o : $(abspath fx_envelope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_explosion.P
endif

$(OBJ_DIR)/fx_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_explosion.o : $(abspath fx_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_fleck.P
endif

$(OBJ_DIR)/fx_fleck.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_fleck.o : $(abspath fx_fleck.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_impact.P
endif

$(OBJ_DIR)/fx_impact.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_impact.o : $(abspath fx_impact.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_interpvalue.P
endif

$(OBJ_DIR)/fx_interpvalue.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_interpvalue.o : $(abspath fx_interpvalue.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_line.P
endif

$(OBJ_DIR)/fx_line.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_line.o : $(abspath fx_line.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_quad.P
endif

$(OBJ_DIR)/fx_quad.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_quad.o : $(abspath fx_quad.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_shelleject.P
endif

$(OBJ_DIR)/fx_shelleject.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_shelleject.o : $(abspath fx_shelleject.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_sparks.P
endif

$(OBJ_DIR)/fx_sparks.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_sparks.o : $(abspath fx_sparks.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_staticline.P
endif

$(OBJ_DIR)/fx_staticline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_staticline.o : $(abspath fx_staticline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_tracer.P
endif

$(OBJ_DIR)/fx_tracer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_tracer.o : $(abspath fx_tracer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_trail.P
endif

$(OBJ_DIR)/fx_trail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_trail.o : $(abspath fx_trail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_water.P
endif

$(OBJ_DIR)/fx_water.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_water.o : $(abspath fx_water.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gametrace_client.P
endif

$(OBJ_DIR)/gametrace_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gametrace_client.o : $(abspath gametrace_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basemodelpanel.P
endif

$(OBJ_DIR)/basemodelpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basemodelpanel.o : $(abspath game_controls/basemodelpanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basemodel_panel.P
endif

$(OBJ_DIR)/basemodel_panel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basemodel_panel.o : $(abspath game_controls/basemodel_panel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseviewport.P
endif

$(OBJ_DIR)/baseviewport.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseviewport.o : $(abspath game_controls/baseviewport.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ClientScoreBoardDialog.P
endif

$(OBJ_DIR)/ClientScoreBoardDialog.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ClientScoreBoardDialog.o : $(abspath game_controls/ClientScoreBoardDialog.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/commandmenu.P
endif

$(OBJ_DIR)/commandmenu.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/commandmenu.o : $(abspath game_controls/commandmenu.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/IconPanel.P
endif

$(OBJ_DIR)/IconPanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/IconPanel.o : $(abspath game_controls/IconPanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/intromenu.P
endif

$(OBJ_DIR)/intromenu.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/intromenu.o : $(abspath game_controls/intromenu.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MapOverview.P
endif

$(OBJ_DIR)/MapOverview.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/MapOverview.o : $(abspath game_controls/MapOverview.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/NavProgress.P
endif

$(OBJ_DIR)/NavProgress.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/NavProgress.o : $(abspath game_controls/NavProgress.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SpectatorGUI.P
endif

$(OBJ_DIR)/SpectatorGUI.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SpectatorGUI.o : $(abspath game_controls/SpectatorGUI.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teammenu.P
endif

$(OBJ_DIR)/teammenu.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/teammenu.o : $(abspath game_controls/teammenu.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vguitextwindow.P
endif

$(OBJ_DIR)/vguitextwindow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vguitextwindow.o : $(abspath game_controls/vguitextwindow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geiger.P
endif

$(OBJ_DIR)/geiger.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/geiger.o : $(abspath geiger.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/glow_outline_effect.P
endif

$(OBJ_DIR)/glow_outline_effect.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/glow_outline_effect.o : $(abspath glow_outline_effect.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/glow_overlay.P
endif

$(OBJ_DIR)/glow_overlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/glow_overlay.o : $(abspath glow_overlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/history_resource.P
endif

$(OBJ_DIR)/history_resource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/history_resource.o : $(abspath history_resource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientmode_hlnormal.P
endif

$(OBJ_DIR)/clientmode_hlnormal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientmode_hlnormal.o : $(abspath hl2/clientmode_hlnormal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_antlion_dust.P
endif

$(OBJ_DIR)/c_antlion_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_antlion_dust.o : $(abspath hl2/c_antlion_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_ar2_explosion.P
endif

$(OBJ_DIR)/c_ar2_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_ar2_explosion.o : $(abspath hl2/c_ar2_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_barnacle.P
endif

$(OBJ_DIR)/c_barnacle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_barnacle.o : $(abspath hl2/c_barnacle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_barney.P
endif

$(OBJ_DIR)/c_barney.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_barney.o : $(abspath hl2/c_barney.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basehelicopter.P
endif

$(OBJ_DIR)/c_basehelicopter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basehelicopter.o : $(abspath hl2/c_basehelicopter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basehlcombatweapon.P
endif

$(OBJ_DIR)/c_basehlcombatweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basehlcombatweapon.o : $(abspath hl2/c_basehlcombatweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basehlplayer.P
endif

$(OBJ_DIR)/c_basehlplayer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basehlplayer.o : $(abspath hl2/c_basehlplayer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_citadel_effects.P
endif

$(OBJ_DIR)/c_citadel_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_citadel_effects.o : $(abspath hl2/c_citadel_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_corpse.P
endif

$(OBJ_DIR)/c_corpse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_corpse.o : $(abspath hl2/c_corpse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_alyxtemp.P
endif

$(OBJ_DIR)/c_env_alyxtemp.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_alyxtemp.o : $(abspath hl2/c_env_alyxtemp.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_headcrabcanister.P
endif

$(OBJ_DIR)/c_env_headcrabcanister.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_headcrabcanister.o : $(abspath hl2/c_env_headcrabcanister.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_starfield.P
endif

$(OBJ_DIR)/c_env_starfield.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_starfield.o : $(abspath hl2/c_env_starfield.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/C_Func_Monitor.P
endif

$(OBJ_DIR)/C_Func_Monitor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/C_Func_Monitor.o : $(abspath hl2/C_Func_Monitor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_tankmortar.P
endif

$(OBJ_DIR)/c_func_tankmortar.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_tankmortar.o : $(abspath hl2/c_func_tankmortar.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_hl2_playerlocaldata.P
endif

$(OBJ_DIR)/c_hl2_playerlocaldata.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_hl2_playerlocaldata.o : $(abspath hl2/c_hl2_playerlocaldata.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_info_teleporter_countdown.P
endif

$(OBJ_DIR)/c_info_teleporter_countdown.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_info_teleporter_countdown.o : $(abspath hl2/c_info_teleporter_countdown.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_npc_antlionguard.P
endif

$(OBJ_DIR)/c_npc_antlionguard.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_npc_antlionguard.o : $(abspath hl2/c_npc_antlionguard.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_npc_combinegunship.P
endif

$(OBJ_DIR)/c_npc_combinegunship.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_npc_combinegunship.o : $(abspath hl2/c_npc_combinegunship.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_npc_manhack.P
endif

$(OBJ_DIR)/c_npc_manhack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_npc_manhack.o : $(abspath hl2/c_npc_manhack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_npc_rollermine.P
endif

$(OBJ_DIR)/c_npc_rollermine.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_npc_rollermine.o : $(abspath hl2/c_npc_rollermine.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_plasma_beam_node.P
endif

$(OBJ_DIR)/c_plasma_beam_node.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_plasma_beam_node.o : $(abspath hl2/c_plasma_beam_node.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_prop_combine_ball.P
endif

$(OBJ_DIR)/c_prop_combine_ball.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_prop_combine_ball.o : $(abspath hl2/c_prop_combine_ball.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_rotorwash.P
endif

$(OBJ_DIR)/c_rotorwash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_rotorwash.o : $(abspath hl2/c_rotorwash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_script_intro.P
endif

$(OBJ_DIR)/c_script_intro.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_script_intro.o : $(abspath hl2/c_script_intro.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_strider.P
endif

$(OBJ_DIR)/c_strider.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_strider.o : $(abspath hl2/c_strider.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_concussiveexplosion.P
endif

$(OBJ_DIR)/c_te_concussiveexplosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_concussiveexplosion.o : $(abspath hl2/c_te_concussiveexplosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_flare.P
endif

$(OBJ_DIR)/c_te_flare.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_flare.o : $(abspath hl2/c_te_flare.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_thumper_dust.P
endif

$(OBJ_DIR)/c_thumper_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_thumper_dust.o : $(abspath hl2/c_thumper_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_airboat.P
endif

$(OBJ_DIR)/c_vehicle_airboat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_airboat.o : $(abspath hl2/c_vehicle_airboat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_cannon.P
endif

$(OBJ_DIR)/c_vehicle_cannon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_cannon.o : $(abspath hl2/c_vehicle_cannon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_crane.P
endif

$(OBJ_DIR)/c_vehicle_crane.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_crane.o : $(abspath hl2/c_vehicle_crane.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_prisoner_pod.P
endif

$(OBJ_DIR)/c_vehicle_prisoner_pod.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_prisoner_pod.o : $(abspath hl2/c_vehicle_prisoner_pod.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_waterbullet.P
endif

$(OBJ_DIR)/c_waterbullet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_waterbullet.o : $(abspath hl2/c_waterbullet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_weapon_crossbow.P
endif

$(OBJ_DIR)/c_weapon_crossbow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_weapon_crossbow.o : $(abspath hl2/c_weapon_crossbow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_weapon_physcannon.P
endif

$(OBJ_DIR)/c_weapon_physcannon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_weapon_physcannon.o : $(abspath hl2/c_weapon_physcannon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_weapon_stunstick.P
endif

$(OBJ_DIR)/c_weapon_stunstick.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_weapon_stunstick.o : $(abspath hl2/c_weapon_stunstick.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_weapon__stubs_hl2.P
endif

$(OBJ_DIR)/c_weapon__stubs_hl2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_weapon__stubs_hl2.o : $(abspath hl2/c_weapon__stubs_hl2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_antlion.P
endif

$(OBJ_DIR)/fx_antlion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_antlion.o : $(abspath hl2/fx_antlion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_bugbait.P
endif

$(OBJ_DIR)/fx_bugbait.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_bugbait.o : $(abspath hl2/fx_bugbait.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_hl2_impacts.P
endif

$(OBJ_DIR)/fx_hl2_impacts.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_hl2_impacts.o : $(abspath hl2/fx_hl2_impacts.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_hl2_tracers.P
endif

$(OBJ_DIR)/fx_hl2_tracers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_hl2_tracers.o : $(abspath hl2/fx_hl2_tracers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_clientmode.P
endif

$(OBJ_DIR)/hl2_clientmode.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_clientmode.o : $(abspath hl2/hl2_clientmode.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_in_main.P
endif

$(OBJ_DIR)/hl_in_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_in_main.o : $(abspath hl2/hl_in_main.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_prediction.P
endif

$(OBJ_DIR)/hl_prediction.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_prediction.o : $(abspath hl2/hl_prediction.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_ammo.P
endif

$(OBJ_DIR)/hud_ammo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_ammo.o : $(abspath hl2/hud_ammo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_autoaim.P
endif

$(OBJ_DIR)/hud_autoaim.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_autoaim.o : $(abspath hl2/hud_autoaim.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_battery.P
endif

$(OBJ_DIR)/hud_battery.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_battery.o : $(abspath hl2/hud_battery.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_blood.P
endif

$(OBJ_DIR)/hud_blood.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_blood.o : $(abspath hl2/hud_blood.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_credits.P
endif

$(OBJ_DIR)/hud_credits.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_credits.o : $(abspath hl2/hud_credits.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_damageindicator.P
endif

$(OBJ_DIR)/hud_damageindicator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_damageindicator.o : $(abspath hl2/hud_damageindicator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_filmdemo.P
endif

$(OBJ_DIR)/hud_filmdemo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_filmdemo.o : $(abspath hl2/hud_filmdemo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_flashlight.P
endif

$(OBJ_DIR)/hud_flashlight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_flashlight.o : $(abspath hl2/hud_flashlight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_hdrdemo.P
endif

$(OBJ_DIR)/hud_hdrdemo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_hdrdemo.o : $(abspath hl2/hud_hdrdemo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_health.P
endif

$(OBJ_DIR)/hud_health.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_health.o : $(abspath hl2/hud_health.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_poisondamageindicator.P
endif

$(OBJ_DIR)/hud_poisondamageindicator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_poisondamageindicator.o : $(abspath hl2/hud_poisondamageindicator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_quickinfo.P
endif

$(OBJ_DIR)/hud_quickinfo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_quickinfo.o : $(abspath hl2/hud_quickinfo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_suitpower.P
endif

$(OBJ_DIR)/hud_suitpower.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_suitpower.o : $(abspath hl2/hud_suitpower.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_weaponselection.P
endif

$(OBJ_DIR)/hud_weaponselection.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_weaponselection.o : $(abspath hl2/hud_weaponselection.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_zoom.P
endif

$(OBJ_DIR)/hud_zoom.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_zoom.o : $(abspath hl2/hud_zoom.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shieldproxy.P
endif

$(OBJ_DIR)/shieldproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/shieldproxy.o : $(abspath hl2/shieldproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_rootpanel_hl2.P
endif

$(OBJ_DIR)/vgui_rootpanel_hl2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_rootpanel_hl2.o : $(abspath hl2/vgui_rootpanel_hl2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvcamera.P
endif

$(OBJ_DIR)/hltvcamera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hltvcamera.o : $(abspath hltvcamera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud.P
endif

$(OBJ_DIR)/hud.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud.o : $(abspath hud.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_animationinfo.P
endif

$(OBJ_DIR)/hud_animationinfo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_animationinfo.o : $(abspath hud_animationinfo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_basechat.P
endif

$(OBJ_DIR)/hud_basechat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_basechat.o : $(abspath hud_basechat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_basetimer.P
endif

$(OBJ_DIR)/hud_basetimer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_basetimer.o : $(abspath hud_basetimer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_bitmapnumericdisplay.P
endif

$(OBJ_DIR)/hud_bitmapnumericdisplay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_bitmapnumericdisplay.o : $(abspath hud_bitmapnumericdisplay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_chat.P
endif

$(OBJ_DIR)/hud_chat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_chat.o : $(abspath hud_chat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_closecaption.P
endif

$(OBJ_DIR)/hud_closecaption.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_closecaption.o : $(abspath hud_closecaption.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_crosshair.P
endif

$(OBJ_DIR)/hud_crosshair.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_crosshair.o : $(abspath hud_crosshair.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_element_helper.P
endif

$(OBJ_DIR)/hud_element_helper.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_element_helper.o : $(abspath hud_element_helper.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_hintdisplay.P
endif

$(OBJ_DIR)/hud_hintdisplay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_hintdisplay.o : $(abspath hud_hintdisplay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_lcd.P
endif

$(OBJ_DIR)/hud_lcd.o : $(abspath hud_lcd.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_msg.P
endif

$(OBJ_DIR)/hud_msg.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_msg.o : $(abspath hud_msg.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_numericdisplay.P
endif

$(OBJ_DIR)/hud_numericdisplay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_numericdisplay.o : $(abspath hud_numericdisplay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_pdump.P
endif

$(OBJ_DIR)/hud_pdump.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_pdump.o : $(abspath hud_pdump.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_posture.P
endif

$(OBJ_DIR)/hud_posture.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_posture.o : $(abspath hud_posture.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_redraw.P
endif

$(OBJ_DIR)/hud_redraw.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_redraw.o : $(abspath hud_redraw.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_squadstatus.P
endif

$(OBJ_DIR)/hud_squadstatus.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_squadstatus.o : $(abspath hud_squadstatus.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_vehicle.P
endif

$(OBJ_DIR)/hud_vehicle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_vehicle.o : $(abspath hud_vehicle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_weapon.P
endif

$(OBJ_DIR)/hud_weapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_weapon.o : $(abspath hud_weapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/initializer.P
endif

$(OBJ_DIR)/initializer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/initializer.o : $(abspath initializer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interpolatedvar.P
endif

$(OBJ_DIR)/interpolatedvar.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/interpolatedvar.o : $(abspath interpolatedvar.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_camera.P
endif

$(OBJ_DIR)/in_camera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_camera.o : $(abspath in_camera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_joystick.P
endif

$(OBJ_DIR)/in_joystick.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_joystick.o : $(abspath in_joystick.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_main.P
endif

$(OBJ_DIR)/in_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_main.o : $(abspath in_main.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_mouse.P
endif

$(OBJ_DIR)/in_mouse.o : $(abspath in_mouse.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_steamcontroller.P
endif

$(OBJ_DIR)/in_steamcontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_steamcontroller.o : $(abspath in_steamcontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/IsNPCProxy.P
endif

$(OBJ_DIR)/IsNPCProxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/IsNPCProxy.o : $(abspath IsNPCProxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lampbeamproxy.P
endif

$(OBJ_DIR)/lampbeamproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/lampbeamproxy.o : $(abspath lampbeamproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lamphaloproxy.P
endif

$(OBJ_DIR)/lamphaloproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/lamphaloproxy.o : $(abspath lamphaloproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mathproxy.P
endif

$(OBJ_DIR)/mathproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mathproxy.o : $(abspath mathproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matrixproxy.P
endif

$(OBJ_DIR)/matrixproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/matrixproxy.o : $(abspath matrixproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/menu.P
endif

$(OBJ_DIR)/menu.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/menu.o : $(abspath menu.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/message.P
endif

$(OBJ_DIR)/message.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/message.o : $(abspath message.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movehelper_client.P
endif

$(OBJ_DIR)/movehelper_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movehelper_client.o : $(abspath movehelper_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mp3player.P
endif

$(OBJ_DIR)/mp3player.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mp3player.o : $(abspath mp3player.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mumble.P
endif

$(OBJ_DIR)/mumble.o : $(abspath mumble.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/panelmetaclassmgr.P
endif

$(OBJ_DIR)/panelmetaclassmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/panelmetaclassmgr.o : $(abspath panelmetaclassmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlemgr.P
endif

$(OBJ_DIR)/particlemgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particlemgr.o : $(abspath particlemgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlesphererenderer.P
endif

$(OBJ_DIR)/particlesphererenderer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particlesphererenderer.o : $(abspath particlesphererenderer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_attractor.P
endif

$(OBJ_DIR)/particles_attractor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_attractor.o : $(abspath particles_attractor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_ez.P
endif

$(OBJ_DIR)/particles_ez.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_ez.o : $(abspath particles_ez.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_localspace.P
endif

$(OBJ_DIR)/particles_localspace.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_localspace.o : $(abspath particles_localspace.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_new.P
endif

$(OBJ_DIR)/particles_new.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_new.o : $(abspath particles_new.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_simple.P
endif

$(OBJ_DIR)/particles_simple.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_simple.o : $(abspath particles_simple.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_collision.P
endif

$(OBJ_DIR)/particle_collision.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_collision.o : $(abspath particle_collision.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_litsmokeemitter.P
endif

$(OBJ_DIR)/particle_litsmokeemitter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_litsmokeemitter.o : $(abspath particle_litsmokeemitter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_proxies.P
endif

$(OBJ_DIR)/particle_proxies.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_proxies.o : $(abspath particle_proxies.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_simple3d.P
endif

$(OBJ_DIR)/particle_simple3d.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_simple3d.o : $(abspath particle_simple3d.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/perfvisualbenchmark.P
endif

$(OBJ_DIR)/perfvisualbenchmark.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/perfvisualbenchmark.o : $(abspath perfvisualbenchmark.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics.P
endif

$(OBJ_DIR)/physics.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics.o : $(abspath physics.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_main_client.P
endif

$(OBJ_DIR)/physics_main_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_main_client.o : $(abspath physics_main_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physpropclientside.P
endif

$(OBJ_DIR)/physpropclientside.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physpropclientside.o : $(abspath physpropclientside.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/playerandobjectenumerator.P
endif

$(OBJ_DIR)/playerandobjectenumerator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/playerandobjectenumerator.o : $(abspath playerandobjectenumerator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/playerspawncache.P
endif

$(OBJ_DIR)/playerspawncache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/playerspawncache.o : $(abspath playerspawncache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/prediction.P
endif

$(OBJ_DIR)/prediction.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/prediction.o : $(abspath prediction.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/proxyentity.P
endif

$(OBJ_DIR)/proxyentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/proxyentity.o : $(abspath proxyentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ProxyHealth.P
endif

$(OBJ_DIR)/ProxyHealth.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ProxyHealth.o : $(abspath ProxyHealth.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/proxyplayer.P
endif

$(OBJ_DIR)/proxyplayer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/proxyplayer.o : $(abspath proxyplayer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/proxypupil.P
endif

$(OBJ_DIR)/proxypupil.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/proxypupil.o : $(abspath proxypupil.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll.P
endif

$(OBJ_DIR)/ragdoll.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ragdoll.o : $(abspath ragdoll.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/recvproxy.P
endif

$(OBJ_DIR)/recvproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/recvproxy.o : $(abspath recvproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rendertexture.P
endif

$(OBJ_DIR)/rendertexture.o : $(abspath rendertexture.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_replay.P
endif

$(OBJ_DIR)/cdll_replay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cdll_replay.o : $(abspath replay/cdll_replay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replaycamera.P
endif

$(OBJ_DIR)/replaycamera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/replaycamera.o : $(abspath replay/replaycamera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScreenSpaceEffects.P
endif

$(OBJ_DIR)/ScreenSpaceEffects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ScreenSpaceEffects.o : $(abspath ScreenSpaceEffects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simple_keys.P
endif

$(OBJ_DIR)/simple_keys.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/simple_keys.o : $(abspath simple_keys.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_sixense.P
endif

$(OBJ_DIR)/in_sixense.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_sixense.o : $(abspath sixense/in_sixense.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_sixense_gesture_bindings.P
endif

$(OBJ_DIR)/in_sixense_gesture_bindings.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_sixense_gesture_bindings.o : $(abspath sixense/in_sixense_gesture_bindings.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/smoke_fog_overlay.P
endif

$(OBJ_DIR)/smoke_fog_overlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/smoke_fog_overlay.o : $(abspath smoke_fog_overlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/splinepatch.P
endif

$(OBJ_DIR)/splinepatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/splinepatch.o : $(abspath splinepatch.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spritemodel.P
endif

$(OBJ_DIR)/spritemodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/spritemodel.o : $(abspath spritemodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stdafx.P
endif

$(OBJ_DIR)/cbase.h.gch : cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/cbase.h.P : $(OBJ_DIR)/cbase.h.gch

vpath cbase.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/cbase.h.P
endif

$(OBJ_DIR)/cbase.h : cbase.h $(OBJ_DIR)/cbase.h.gch $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/cbase.h

$(OBJ_DIR)/stdafx.o : $(abspath stdafx.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio_stats.P
endif

$(OBJ_DIR)/studio_stats.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/studio_stats.o : $(abspath studio_stats.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/texturescrollmaterialproxy.P
endif

$(OBJ_DIR)/texturescrollmaterialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/texturescrollmaterialproxy.o : $(abspath texturescrollmaterialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/text_message.P
endif

$(OBJ_DIR)/text_message.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/text_message.o : $(abspath text_message.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/timematerialproxy.P
endif

$(OBJ_DIR)/timematerialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/timematerialproxy.o : $(abspath timematerialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/toggletextureproxy.P
endif

$(OBJ_DIR)/toggletextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/toggletextureproxy.o : $(abspath toggletextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/toolframework_client.P
endif

$(OBJ_DIR)/toolframework_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/toolframework_client.o : $(abspath toolframework_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/train.P
endif

$(OBJ_DIR)/train.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/train.o : $(abspath train.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_avatarimage.P
endif

$(OBJ_DIR)/vgui_avatarimage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_avatarimage.o : $(abspath vgui_avatarimage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_basepanel.P
endif

$(OBJ_DIR)/vgui_basepanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_basepanel.o : $(abspath vgui_basepanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_bitmapbutton.P
endif

$(OBJ_DIR)/vgui_bitmapbutton.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_bitmapbutton.o : $(abspath vgui_bitmapbutton.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_bitmapimage.P
endif

$(OBJ_DIR)/vgui_bitmapimage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_bitmapimage.o : $(abspath vgui_bitmapimage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_bitmappanel.P
endif

$(OBJ_DIR)/vgui_bitmappanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_bitmappanel.o : $(abspath vgui_bitmappanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_centerstringpanel.P
endif

$(OBJ_DIR)/vgui_centerstringpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_centerstringpanel.o : $(abspath vgui_centerstringpanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_consolepanel.P
endif

$(OBJ_DIR)/vgui_consolepanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_consolepanel.o : $(abspath vgui_consolepanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_debugoverlaypanel.P
endif

$(OBJ_DIR)/vgui_debugoverlaypanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_debugoverlaypanel.o : $(abspath vgui_debugoverlaypanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_fpspanel.P
endif

$(OBJ_DIR)/vgui_fpspanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_fpspanel.o : $(abspath vgui_fpspanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_game_viewport.P
endif

$(OBJ_DIR)/vgui_game_viewport.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_game_viewport.o : $(abspath vgui_game_viewport.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_grid.P
endif

$(OBJ_DIR)/vgui_grid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_grid.o : $(abspath vgui_grid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_int.P
endif

$(OBJ_DIR)/vgui_int.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_int.o : $(abspath vgui_int.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_loadingdiscpanel.P
endif

$(OBJ_DIR)/vgui_loadingdiscpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_loadingdiscpanel.o : $(abspath vgui_loadingdiscpanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_messagechars.P
endif

$(OBJ_DIR)/vgui_messagechars.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_messagechars.o : $(abspath vgui_messagechars.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_netgraphpanel.P
endif

$(OBJ_DIR)/vgui_netgraphpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_netgraphpanel.o : $(abspath vgui_netgraphpanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_schemevisualizer.P
endif

$(OBJ_DIR)/vgui_schemevisualizer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_schemevisualizer.o : $(abspath vgui_schemevisualizer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_slideshow_display_screen.P
endif

$(OBJ_DIR)/vgui_slideshow_display_screen.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_slideshow_display_screen.o : $(abspath vgui_slideshow_display_screen.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_video.P
endif

$(OBJ_DIR)/vgui_video.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_video.o : $(abspath vgui_video.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_video_player.P
endif

$(OBJ_DIR)/vgui_video_player.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_video_player.o : $(abspath vgui_video_player.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view.P
endif

$(OBJ_DIR)/view.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/view.o : $(abspath view.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/viewangleanim.P
endif

$(OBJ_DIR)/viewangleanim.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/viewangleanim.o : $(abspath viewangleanim.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ViewConeImage.P
endif

$(OBJ_DIR)/ViewConeImage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ViewConeImage.o : $(abspath ViewConeImage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/viewdebug.P
endif

$(OBJ_DIR)/viewdebug.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/viewdebug.o : $(abspath viewdebug.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/viewpostprocess.P
endif

$(OBJ_DIR)/viewpostprocess.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/viewpostprocess.o : $(abspath viewpostprocess.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/viewrender.P
endif

$(OBJ_DIR)/viewrender.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/viewrender.o : $(abspath viewrender.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view_beams.P
endif

$(OBJ_DIR)/view_beams.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/view_beams.o : $(abspath view_beams.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view_effects.P
endif

$(OBJ_DIR)/view_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/view_effects.o : $(abspath view_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view_scene.P
endif

$(OBJ_DIR)/view_scene.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/view_scene.o : $(abspath view_scene.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/warp_overlay.P
endif

$(OBJ_DIR)/warp_overlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/warp_overlay.o : $(abspath warp_overlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WaterLODMaterialProxy.P
endif

$(OBJ_DIR)/WaterLODMaterialProxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/WaterLODMaterialProxy.o : $(abspath WaterLODMaterialProxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapons_resource.P
endif

$(OBJ_DIR)/weapons_resource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapons_resource.o : $(abspath weapons_resource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_selection.P
endif

$(OBJ_DIR)/weapon_selection.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_selection.o : $(abspath weapon_selection.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WorldDimsProxy.P
endif

$(OBJ_DIR)/WorldDimsProxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/WorldDimsProxy.o : $(abspath WorldDimsProxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
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
SystemLibraries=-lrt 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=client -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DNO_STRING_T -DCLIENT_DLL -DVECTOR -DVERSION_SAFE_STEAM_API_INTERFACES -DPROTECTED_THINGS_ENABLE -Dstrncpy=use_Q_strncpy_instead -D_snprintf=use_Q_snprintf_instead -DUSE_WEBM_FOR_REPLAY -DHL2_CLIENT_DLL -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/game/client -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ./hl2 ./hl2/elements ../../game/shared/hl2 ./ ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 ../../game/client/generated_proto_hl2 ../../thirdparty/protobuf-2.6.1/src ../../vgui2/include ../../vgui2/controls ../../game/shared ./game_controls ../../thirdparty/sixensesdk/include 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../../game/hl2/bin/client.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/client.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../common/compiledcaptionswap.cpp \
    ../../common/language.cpp \
    ../../common/randoverride.cpp \
    ../../common/steamid.cpp \
    ../../game/client/c_vote_controller.cpp \
    ../../game/shared/achievementmgr.cpp \
    ../../game/shared/achievements_hlx.cpp \
    ../../game/shared/achievement_saverestore.cpp \
    ../../game/shared/activitylist.cpp \
    ../../game/shared/ammodef.cpp \
    ../../game/shared/animation.cpp \
    ../../game/shared/baseachievement.cpp \
    ../../game/shared/basecombatcharacter_shared.cpp \
    ../../game/shared/basecombatweapon_shared.cpp \
    ../../game/shared/baseentity_shared.cpp \
    ../../game/shared/basegrenade_shared.cpp \
    ../../game/shared/baseparticleentity.cpp \
    ../../game/shared/baseplayer_shared.cpp \
    ../../game/shared/baseprojectile.cpp \
    ../../game/shared/baseviewmodel_shared.cpp \
    ../../game/shared/base_playeranimstate.cpp \
    ../../game/shared/beam_shared.cpp \
    ../../game/shared/cam_thirdperson.cpp \
    ../../game/shared/collisionproperty.cpp \
    ../../game/shared/death_pose.cpp \
    ../../game/shared/debugoverlay_shared.cpp \
    ../../game/shared/decals.cpp \
    ../../game/shared/effect_dispatch_data.cpp \
    ../../game/shared/ehandle.cpp \
    ../../game/shared/entitylist_base.cpp \
    ../../game/shared/EntityParticleTrail_Shared.cpp \
    ../../game/shared/env_detail_controller.cpp \
    ../../game/shared/env_wind_shared.cpp \
    ../../game/shared/eventlist.cpp \
    ../../game/shared/func_ladder.cpp \
    ../../game/shared/gamemovement.cpp \
    ../../game/shared/gamerules.cpp \
    ../../game/shared/gamerules_register.cpp \
    ../../game/shared/GameStats.cpp \
    ../../game/shared/gamestringpool.cpp \
    ../../game/shared/gamevars_shared.cpp \
    ../../game/shared/hintmessage.cpp \
    ../../game/shared/hintsystem.cpp \
    ../../game/shared/hl2/achievements_hl2.cpp \
    ../../game/shared/hl2/basehlcombatweapon_shared.cpp \
    ../../game/shared/hl2/env_headcrabcanister_shared.cpp \
    ../../game/shared/hl2/hl2_gamerules.cpp \
    ../../game/shared/hl2/hl2_usermessages.cpp \
    ../../game/shared/hl2/hl_gamemovement.cpp \
    ../../game/shared/igamesystem.cpp \
    ../../game/shared/interval.cpp \
    ../../game/shared/mapentities_shared.cpp \
    ../../game/shared/movevars_shared.cpp \
    ../../game/shared/mp_shareddefs.cpp \
    ../../game/shared/multiplay_gamerules.cpp \
    ../../game/shared/obstacle_pushaway.cpp \
    ../../game/shared/particlesystemquery.cpp \
    ../../game/shared/particle_parse.cpp \
    ../../game/shared/particle_property.cpp \
    ../../game/shared/physics_main_shared.cpp \
    ../../game/shared/physics_saverestore.cpp \
    ../../game/shared/physics_shared.cpp \
    ../../game/shared/point_bonusmaps_accessor.cpp \
    ../../game/shared/point_posecontroller.cpp \
    ../../game/shared/precache_register.cpp \
    ../../game/shared/predictableid.cpp \
    ../../game/shared/predictioncopy.cpp \
    ../../game/shared/props_shared.cpp \
    ../../game/shared/ragdoll_shared.cpp \
    ../../game/shared/rope_helpers.cpp \
    ../../game/shared/saverestore.cpp \
    ../../game/shared/sceneentity_shared.cpp \
    ../../game/shared/script_intro_shared.cpp \
    ../../game/shared/sequence_Transitioner.cpp \
    ../../game/shared/sheetsimulator.cpp \
    ../../game/shared/simtimer.cpp \
    ../../game/shared/singleplay_gamerules.cpp \
    ../../game/shared/sixense/sixense_convars.cpp \
    ../../game/shared/SoundEmitterSystem.cpp \
    ../../game/shared/soundenvelope.cpp \
    ../../game/shared/Sprite.cpp \
    ../../game/shared/SpriteTrail.cpp \
    ../../game/shared/studio_shared.cpp \
    ../../game/shared/takedamageinfo.cpp \
    ../../game/shared/teamplayroundbased_gamerules.cpp \
    ../../game/shared/teamplay_gamerules.cpp \
    ../../game/shared/test_ehandle.cpp \
    ../../game/shared/usercmd.cpp \
    ../../game/shared/usermessages.cpp \
    ../../game/shared/util_shared.cpp \
    ../../game/shared/vehicle_viewblend_shared.cpp \
    ../../game/shared/voice_banmgr.cpp \
    ../../game/shared/voice_status.cpp \
    ../../game/shared/weapon_parse.cpp \
    ../../game/shared/weapon_parse_default.cpp \
    ../../public/bone_accessor.cpp \
    ../../public/bone_setup.cpp \
    ../../public/client_class.cpp \
    ../../public/collisionutils.cpp \
    ../../public/crtmemdebug.cpp \
    ../../public/dt_recv.cpp \
    ../../public/dt_utlvector_common.cpp \
    ../../public/dt_utlvector_recv.cpp \
    ../../public/filesystem_helpers.cpp \
    ../../public/haptics/haptic_msgs.cpp \
    ../../public/interpolatortypes.cpp \
    ../../public/jigglebones.cpp \
    ../../public/networkvar.cpp \
    ../../public/posedebugger.cpp \
    ../../public/renamed_recvtable_compat.cpp \
    ../../public/rope_physics.cpp \
    ../../public/scratchpad3d.cpp \
    ../../public/ScratchPadUtils.cpp \
    ../../public/sentence.cpp \
    ../../public/simple_physics.cpp \
    ../../public/SoundParametersInternal.cpp \
    ../../public/stringregistry.cpp \
    ../../public/studio.cpp \
    ../../public/tier0/memoverride.cpp \
    ../../public/tools/bonelist.cpp \
    ../../public/vallocator.cpp \
    ../../public/vgui_controls/vgui_controls.cpp \
    achievement_notification_panel.cpp \
    alphamaterialproxy.cpp \
    animatedentitytextureproxy.cpp \
    animatedoffsettextureproxy.cpp \
    animatedtextureproxy.cpp \
    AnimateSpecificTextureProxy.cpp \
    baseanimatedtextureproxy.cpp \
    baseclientrendertargets.cpp \
    basepresence.cpp \
    beamdraw.cpp \
    bone_merge_cache.cpp \
    camomaterialproxy.cpp \
    cdll_bounded_cvars.cpp \
    cdll_client_int.cpp \
    cdll_util.cpp \
    classmap.cpp \
    clienteffectprecachesystem.cpp \
    cliententitylist.cpp \
    clientleafsystem.cpp \
    clientmode_shared.cpp \
    clientshadowmgr.cpp \
    clientsideeffects.cpp \
    clientsideeffects_test.cpp \
    clientsteamcontext.cpp \
    client_factorylist.cpp \
    client_thinklist.cpp \
    client_virtualreality.cpp \
    cl_mat_stub.cpp \
    colorcorrectionmgr.cpp \
    commentary_modelviewer.cpp \
    c_ai_basehumanoid.cpp \
    c_ai_basenpc.cpp \
    c_baseanimating.cpp \
    c_baseanimatingoverlay.cpp \
    c_basecombatcharacter.cpp \
    c_basecombatweapon.cpp \
    c_basedoor.cpp \
    c_baseentity.cpp \
    c_baseflex.cpp \
    c_baseplayer.cpp \
    c_basetempentity.cpp \
    c_baseviewmodel.cpp \
    c_breakableprop.cpp \
    c_colorcorrection.cpp \
    c_colorcorrectionvolume.cpp \
    c_dynamiclight.cpp \
    c_effects.cpp \
    c_entitydissolve.cpp \
    c_entityparticletrail.cpp \
    c_env_fog_controller.cpp \
    c_env_particlescript.cpp \
    c_env_projectedtexture.cpp \
    c_env_screenoverlay.cpp \
    c_env_tonemap_controller.cpp \
    c_fire_smoke.cpp \
    c_fish.cpp \
    c_func_areaportalwindow.cpp \
    c_func_breakablesurf.cpp \
    c_func_conveyor.cpp \
    c_func_dust.cpp \
    c_func_lod.cpp \
    c_func_occluder.cpp \
    c_func_reflective_glass.cpp \
    c_func_rotating.cpp \
    c_func_smokevolume.cpp \
    c_func_tracktrain.cpp \
    c_gib.cpp \
    c_hairball.cpp \
    c_impact_effects.cpp \
    c_info_overlay_accessor.cpp \
    c_lightglow.cpp \
    C_MaterialModifyControl.cpp \
    c_movie_explosion.cpp \
    c_particle_fire.cpp \
    c_particle_smokegrenade.cpp \
    c_particle_system.cpp \
    c_physbox.cpp \
    c_physicsprop.cpp \
    c_physmagnet.cpp \
    c_pixel_visibility.cpp \
    c_plasma.cpp \
    c_playerresource.cpp \
    c_point_camera.cpp \
    c_point_commentary_node.cpp \
    c_props.cpp \
    c_prop_vehicle.cpp \
    c_ragdoll_manager.cpp \
    c_recipientfilter.cpp \
    c_rope.cpp \
    c_rumble.cpp \
    c_sceneentity.cpp \
    c_shadowcontrol.cpp \
    c_slideshow_display.cpp \
    c_smokestack.cpp \
    c_smoke_trail.cpp \
    c_soundscape.cpp \
    c_spotlight_end.cpp \
    c_sprite.cpp \
    c_sprite_perfmonitor.cpp \
    c_steamjet.cpp \
    c_stickybolt.cpp \
    c_sun.cpp \
    c_te.cpp \
    c_team.cpp \
    c_team_objectiveresource.cpp \
    c_tesla.cpp \
    c_testtraceline.cpp \
    c_test_proxytoggle.cpp \
    c_te_armorricochet.cpp \
    c_te_basebeam.cpp \
    c_te_beamentpoint.cpp \
    c_te_beaments.cpp \
    c_te_beamfollow.cpp \
    c_te_beamlaser.cpp \
    c_te_beampoints.cpp \
    c_te_beamring.cpp \
    c_te_beamringpoint.cpp \
    c_te_beamspline.cpp \
    c_te_bloodsprite.cpp \
    c_te_bloodstream.cpp \
    c_te_breakmodel.cpp \
    c_te_bspdecal.cpp \
    c_te_bubbles.cpp \
    c_te_bubbletrail.cpp \
    c_te_clientprojectile.cpp \
    c_te_decal.cpp \
    c_te_dynamiclight.cpp \
    c_te_effect_dispatch.cpp \
    c_te_energysplash.cpp \
    c_te_explosion.cpp \
    c_te_fizz.cpp \
    c_te_footprint.cpp \
    c_te_glassshatter.cpp \
    c_te_glowsprite.cpp \
    c_te_impact.cpp \
    c_te_killplayerattachments.cpp \
    c_te_largefunnel.cpp \
    c_te_legacytempents.cpp \
    c_te_muzzleflash.cpp \
    c_te_particlesystem.cpp \
    c_te_physicsprop.cpp \
    c_te_playerdecal.cpp \
    c_te_projecteddecal.cpp \
    c_te_showline.cpp \
    c_te_smoke.cpp \
    c_te_sparks.cpp \
    c_te_sprite.cpp \
    c_te_spritespray.cpp \
    c_te_worlddecal.cpp \
    c_tracer.cpp \
    c_user_message_register.cpp \
    c_vehicle_choreo_generic.cpp \
    c_vehicle_jeep.cpp \
    c_vguiscreen.cpp \
    C_WaterLODControl.cpp \
    c_world.cpp \
    death.cpp \
    detailobjectsystem.cpp \
    dummyproxy.cpp \
    EffectsClient.cpp \
    entityoriginmaterialproxy.cpp \
    entity_client_tools.cpp \
    episodic/c_vort_charge_token.cpp \
    flashlighteffect.cpp \
    functionproxy.cpp \
    fx.cpp \
    fx_blood.cpp \
    fx_cube.cpp \
    fx_discreetline.cpp \
    fx_envelope.cpp \
    fx_explosion.cpp \
    fx_fleck.cpp \
    fx_impact.cpp \
    fx_interpvalue.cpp \
    fx_line.cpp \
    fx_quad.cpp \
    fx_shelleject.cpp \
    fx_sparks.cpp \
    fx_staticline.cpp \
    fx_tracer.cpp \
    fx_trail.cpp \
    fx_water.cpp \
    gametrace_client.cpp \
    game_controls/basemodelpanel.cpp \
    game_controls/basemodel_panel.cpp \
    game_controls/baseviewport.cpp \
    game_controls/ClientScoreBoardDialog.cpp \
    game_controls/commandmenu.cpp \
    game_controls/IconPanel.cpp \
    game_controls/intromenu.cpp \
    game_controls/MapOverview.cpp \
    game_controls/NavProgress.cpp \
    game_controls/SpectatorGUI.cpp \
    game_controls/teammenu.cpp \
    game_controls/vguitextwindow.cpp \
    geiger.cpp \
    glow_outline_effect.cpp \
    glow_overlay.cpp \
    history_resource.cpp \
    hl2/clientmode_hlnormal.cpp \
    hl2/c_antlion_dust.cpp \
    hl2/c_ar2_explosion.cpp \
    hl2/c_barnacle.cpp \
    hl2/c_barney.cpp \
    hl2/c_basehelicopter.cpp \
    hl2/c_basehlcombatweapon.cpp \
    hl2/c_basehlplayer.cpp \
    hl2/c_citadel_effects.cpp \
    hl2/c_corpse.cpp \
    hl2/c_env_alyxtemp.cpp \
    hl2/c_env_headcrabcanister.cpp \
    hl2/c_env_starfield.cpp \
    hl2/C_Func_Monitor.cpp \
    hl2/c_func_tankmortar.cpp \
    hl2/c_hl2_playerlocaldata.cpp \
    hl2/c_info_teleporter_countdown.cpp \
    hl2/c_npc_antlionguard.cpp \
    hl2/c_npc_combinegunship.cpp \
    hl2/c_npc_manhack.cpp \
    hl2/c_npc_rollermine.cpp \
    hl2/c_plasma_beam_node.cpp \
    hl2/c_prop_combine_ball.cpp \
    hl2/c_rotorwash.cpp \
    hl2/c_script_intro.cpp \
    hl2/c_strider.cpp \
    hl2/c_te_concussiveexplosion.cpp \
    hl2/c_te_flare.cpp \
    hl2/c_thumper_dust.cpp \
    hl2/c_vehicle_airboat.cpp \
    hl2/c_vehicle_cannon.cpp \
    hl2/c_vehicle_crane.cpp \
    hl2/c_vehicle_prisoner_pod.cpp \
    hl2/c_waterbullet.cpp \
    hl2/c_weapon_crossbow.cpp \
    hl2/c_weapon_physcannon.cpp \
    hl2/c_weapon_stunstick.cpp \
    hl2/c_weapon__stubs_hl2.cpp \
    hl2/fx_antlion.cpp \
    hl2/fx_bugbait.cpp \
    hl2/fx_hl2_impacts.cpp \
    hl2/fx_hl2_tracers.cpp \
    hl2/hl2_clientmode.cpp \
    hl2/hl_in_main.cpp \
    hl2/hl_prediction.cpp \
    hl2/hud_ammo.cpp \
    hl2/hud_autoaim.cpp \
    hl2/hud_battery.cpp \
    hl2/hud_blood.cpp \
    hl2/hud_credits.cpp \
    hl2/hud_damageindicator.cpp \
    hl2/hud_filmdemo.cpp \
    hl2/hud_flashlight.cpp \
    hl2/hud_hdrdemo.cpp \
    hl2/hud_health.cpp \
    hl2/hud_poisondamageindicator.cpp \
    hl2/hud_quickinfo.cpp \
    hl2/hud_suitpower.cpp \
    hl2/hud_weaponselection.cpp \
    hl2/hud_zoom.cpp \
    hl2/shieldproxy.cpp \
    hl2/vgui_rootpanel_hl2.cpp \
    hltvcamera.cpp \
    hud.cpp \
    hud_animationinfo.cpp \
    hud_basechat.cpp \
    hud_basetimer.cpp \
    hud_bitmapnumericdisplay.cpp \
    hud_chat.cpp \
    hud_closecaption.cpp \
    hud_crosshair.cpp \
    hud_element_helper.cpp \
    hud_hintdisplay.cpp \
    hud_lcd.cpp \
    hud_msg.cpp \
    hud_numericdisplay.cpp \
    hud_pdump.cpp \
    hud_posture.cpp \
    hud_redraw.cpp \
    hud_squadstatus.cpp \
    hud_vehicle.cpp \
    hud_weapon.cpp \
    initializer.cpp \
    interpolatedvar.cpp \
    in_camera.cpp \
    in_joystick.cpp \
    in_main.cpp \
    in_mouse.cpp \
    in_steamcontroller.cpp \
    IsNPCProxy.cpp \
    lampbeamproxy.cpp \
    lamphaloproxy.cpp \
    mathproxy.cpp \
    matrixproxy.cpp \
    menu.cpp \
    message.cpp \
    movehelper_client.cpp \
    mp3player.cpp \
    mumble.cpp \
    panelmetaclassmgr.cpp \
    particlemgr.cpp \
    particlesphererenderer.cpp \
    particles_attractor.cpp \
    particles_ez.cpp \
    particles_localspace.cpp \
    particles_new.cpp \
    particles_simple.cpp \
    particle_collision.cpp \
    particle_litsmokeemitter.cpp \
    particle_proxies.cpp \
    particle_simple3d.cpp \
    perfvisualbenchmark.cpp \
    physics.cpp \
    physics_main_client.cpp \
    physpropclientside.cpp \
    playerandobjectenumerator.cpp \
    playerspawncache.cpp \
    prediction.cpp \
    proxyentity.cpp \
    ProxyHealth.cpp \
    proxyplayer.cpp \
    proxypupil.cpp \
    ragdoll.cpp \
    recvproxy.cpp \
    rendertexture.cpp \
    replay/cdll_replay.cpp \
    replay/replaycamera.cpp \
    ScreenSpaceEffects.cpp \
    simple_keys.cpp \
    sixense/in_sixense.cpp \
    sixense/in_sixense_gesture_bindings.cpp \
    smoke_fog_overlay.cpp \
    splinepatch.cpp \
    spritemodel.cpp \
    stdafx.cpp \
    studio_stats.cpp \
    texturescrollmaterialproxy.cpp \
    text_message.cpp \
    timematerialproxy.cpp \
    toggletextureproxy.cpp \
    toolframework_client.cpp \
    train.cpp \
    vgui_avatarimage.cpp \
    vgui_basepanel.cpp \
    vgui_bitmapbutton.cpp \
    vgui_bitmapimage.cpp \
    vgui_bitmappanel.cpp \
    vgui_centerstringpanel.cpp \
    vgui_consolepanel.cpp \
    vgui_debugoverlaypanel.cpp \
    vgui_fpspanel.cpp \
    vgui_game_viewport.cpp \
    vgui_grid.cpp \
    vgui_int.cpp \
    vgui_loadingdiscpanel.cpp \
    vgui_messagechars.cpp \
    vgui_netgraphpanel.cpp \
    vgui_schemevisualizer.cpp \
    vgui_slideshow_display_screen.cpp \
    vgui_video.cpp \
    vgui_video_player.cpp \
    view.cpp \
    viewangleanim.cpp \
    ViewConeImage.cpp \
    viewdebug.cpp \
    viewpostprocess.cpp \
    viewrender.cpp \
    view_beams.cpp \
    view_effects.cpp \
    view_scene.cpp \
    warp_overlay.cpp \
    WaterLODMaterialProxy.cpp \
    weapons_resource.cpp \
    weapon_selection.cpp \
    WorldDimsProxy.cpp \


LIBFILES = \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/bitmap.a \
    ../../lib/public/linux32/choreoobjects.a \
    ../../lib/public/linux32/dmxloader.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/matsys_controls.a \
    ../../lib/public/linux32/particles.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \
    ../../lib/public/linux32/vgui_controls.a \
    ../../lib/public/linux32/vtf.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \
    -L../../lib/public/linux32 -lsteam_api \


LIBFILENAMES = \
    ../../lib/public/linux32/bitmap.a \
    ../../lib/public/linux32/choreoobjects.a \
    ../../lib/public/linux32/dmxloader.a \
    ../../lib/public/linux32/libsteam_api.so \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/matsys_controls.a \
    ../../lib/public/linux32/particles.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \
    ../../lib/public/linux32/vgui_controls.a \
    ../../lib/public/linux32/vtf.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/compiledcaptionswap.P
endif

$(OBJ_DIR)/compiledcaptionswap.o : $(abspath ../../common/compiledcaptionswap.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/language.P
endif

$(OBJ_DIR)/language.o : $(abspath ../../common/language.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/randoverride.P
endif

$(OBJ_DIR)/randoverride.o : $(abspath ../../common/randoverride.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamid.P
endif

$(OBJ_DIR)/steamid.o : $(abspath ../../common/steamid.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vote_controller.P
endif

$(OBJ_DIR)/c_vote_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vote_controller.o : $(abspath ../../game/client/c_vote_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievementmgr.P
endif

$(OBJ_DIR)/achievementmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievementmgr.o : $(abspath ../../game/shared/achievementmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievements_hlx.P
endif

$(OBJ_DIR)/achievements_hlx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievements_hlx.o : $(abspath ../../game/shared/achievements_hlx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievement_saverestore.P
endif

$(OBJ_DIR)/achievement_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievement_saverestore.o : $(abspath ../../game/shared/achievement_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/activitylist.P
endif

$(OBJ_DIR)/activitylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/activitylist.o : $(abspath ../../game/shared/activitylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ammodef.P
endif

$(OBJ_DIR)/ammodef.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ammodef.o : $(abspath ../../game/shared/ammodef.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animation.P
endif

$(OBJ_DIR)/animation.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animation.o : $(abspath ../../game/shared/animation.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseachievement.P
endif

$(OBJ_DIR)/baseachievement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseachievement.o : $(abspath ../../game/shared/baseachievement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatcharacter_shared.P
endif

$(OBJ_DIR)/basecombatcharacter_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatcharacter_shared.o : $(abspath ../../game/shared/basecombatcharacter_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatweapon_shared.P
endif

$(OBJ_DIR)/basecombatweapon_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatweapon_shared.o : $(abspath ../../game/shared/basecombatweapon_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseentity_shared.P
endif

$(OBJ_DIR)/baseentity_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseentity_shared.o : $(abspath ../../game/shared/baseentity_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_shared.P
endif

$(OBJ_DIR)/basegrenade_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_shared.o : $(abspath ../../game/shared/basegrenade_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseparticleentity.P
endif

$(OBJ_DIR)/baseparticleentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseparticleentity.o : $(abspath ../../game/shared/baseparticleentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseplayer_shared.P
endif

$(OBJ_DIR)/baseplayer_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseplayer_shared.o : $(abspath ../../game/shared/baseplayer_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseprojectile.P
endif

$(OBJ_DIR)/baseprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseprojectile.o : $(abspath ../../game/shared/baseprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseviewmodel_shared.P
endif

$(OBJ_DIR)/baseviewmodel_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseviewmodel_shared.o : $(abspath ../../game/shared/baseviewmodel_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_playeranimstate.P
endif

$(OBJ_DIR)/base_playeranimstate.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/base_playeranimstate.o : $(abspath ../../game/shared/base_playeranimstate.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/beam_shared.P
endif

$(OBJ_DIR)/beam_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/beam_shared.o : $(abspath ../../game/shared/beam_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cam_thirdperson.P
endif

$(OBJ_DIR)/cam_thirdperson.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cam_thirdperson.o : $(abspath ../../game/shared/cam_thirdperson.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionproperty.P
endif

$(OBJ_DIR)/collisionproperty.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/collisionproperty.o : $(abspath ../../game/shared/collisionproperty.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/death_pose.P
endif

$(OBJ_DIR)/death_pose.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/death_pose.o : $(abspath ../../game/shared/death_pose.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugoverlay_shared.P
endif

$(OBJ_DIR)/debugoverlay_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/debugoverlay_shared.o : $(abspath ../../game/shared/debugoverlay_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/decals.P
endif

$(OBJ_DIR)/decals.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/decals.o : $(abspath ../../game/shared/decals.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/effect_dispatch_data.P
endif

$(OBJ_DIR)/effect_dispatch_data.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/effect_dispatch_data.o : $(abspath ../../game/shared/effect_dispatch_data.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ehandle.P
endif

$(OBJ_DIR)/ehandle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ehandle.o : $(abspath ../../game/shared/ehandle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entitylist_base.P
endif

$(OBJ_DIR)/entitylist_base.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entitylist_base.o : $(abspath ../../game/shared/entitylist_base.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityParticleTrail_Shared.P
endif

$(OBJ_DIR)/EntityParticleTrail_Shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityParticleTrail_Shared.o : $(abspath ../../game/shared/EntityParticleTrail_Shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_detail_controller.P
endif

$(OBJ_DIR)/env_detail_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_detail_controller.o : $(abspath ../../game/shared/env_detail_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_wind_shared.P
endif

$(OBJ_DIR)/env_wind_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_wind_shared.o : $(abspath ../../game/shared/env_wind_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eventlist.P
endif

$(OBJ_DIR)/eventlist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/eventlist.o : $(abspath ../../game/shared/eventlist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_ladder.P
endif

$(OBJ_DIR)/func_ladder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_ladder.o : $(abspath ../../game/shared/func_ladder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamemovement.P
endif

$(OBJ_DIR)/gamemovement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamemovement.o : $(abspath ../../game/shared/gamemovement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamerules.P
endif

$(OBJ_DIR)/gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamerules.o : $(abspath ../../game/shared/gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamerules_register.P
endif

$(OBJ_DIR)/gamerules_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamerules_register.o : $(abspath ../../game/shared/gamerules_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameStats.P
endif

$(OBJ_DIR)/GameStats.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/GameStats.o : $(abspath ../../game/shared/GameStats.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamestringpool.P
endif

$(OBJ_DIR)/gamestringpool.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamestringpool.o : $(abspath ../../game/shared/gamestringpool.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamevars_shared.P
endif

$(OBJ_DIR)/gamevars_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamevars_shared.o : $(abspath ../../game/shared/gamevars_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hintmessage.P
endif

$(OBJ_DIR)/hintmessage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hintmessage.o : $(abspath ../../game/shared/hintmessage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hintsystem.P
endif

$(OBJ_DIR)/hintsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hintsystem.o : $(abspath ../../game/shared/hintsystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievements_hl2.P
endif

$(OBJ_DIR)/achievements_hl2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievements_hl2.o : $(abspath ../../game/shared/hl2/achievements_hl2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basehlcombatweapon_shared.P
endif

$(OBJ_DIR)/basehlcombatweapon_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basehlcombatweapon_shared.o : $(abspath ../../game/shared/hl2/basehlcombatweapon_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_headcrabcanister_shared.P
endif

$(OBJ_DIR)/env_headcrabcanister_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_headcrabcanister_shared.o : $(abspath ../../game/shared/hl2/env_headcrabcanister_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_gamerules.P
endif

$(OBJ_DIR)/hl2_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_gamerules.o : $(abspath ../../game/shared/hl2/hl2_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_usermessages.P
endif

$(OBJ_DIR)/hl2_usermessages.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_usermessages.o : $(abspath ../../game/shared/hl2/hl2_usermessages.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_gamemovement.P
endif

$(OBJ_DIR)/hl_gamemovement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_gamemovement.o : $(abspath ../../game/shared/hl2/hl_gamemovement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/igamesystem.P
endif

$(OBJ_DIR)/igamesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/igamesystem.o : $(abspath ../../game/shared/igamesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interval.P
endif

$(OBJ_DIR)/interval.o : $(abspath ../../game/shared/interval.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mapentities_shared.P
endif

$(OBJ_DIR)/mapentities_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mapentities_shared.o : $(abspath ../../game/shared/mapentities_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movevars_shared.P
endif

$(OBJ_DIR)/movevars_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movevars_shared.o : $(abspath ../../game/shared/movevars_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mp_shareddefs.P
endif

$(OBJ_DIR)/mp_shareddefs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mp_shareddefs.o : $(abspath ../../game/shared/mp_shareddefs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/multiplay_gamerules.P
endif

$(OBJ_DIR)/multiplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/multiplay_gamerules.o : $(abspath ../../game/shared/multiplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/obstacle_pushaway.P
endif

$(OBJ_DIR)/obstacle_pushaway.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/obstacle_pushaway.o : $(abspath ../../game/shared/obstacle_pushaway.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlesystemquery.P
endif

$(OBJ_DIR)/particlesystemquery.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particlesystemquery.o : $(abspath ../../game/shared/particlesystemquery.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_parse.P
endif

$(OBJ_DIR)/particle_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_parse.o : $(abspath ../../game/shared/particle_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_property.P
endif

$(OBJ_DIR)/particle_property.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_property.o : $(abspath ../../game/shared/particle_property.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_main_shared.P
endif

$(OBJ_DIR)/physics_main_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_main_shared.o : $(abspath ../../game/shared/physics_main_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_saverestore.P
endif

$(OBJ_DIR)/physics_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_saverestore.o : $(abspath ../../game/shared/physics_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_shared.P
endif

$(OBJ_DIR)/physics_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_shared.o : $(abspath ../../game/shared/physics_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_bonusmaps_accessor.P
endif

$(OBJ_DIR)/point_bonusmaps_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_bonusmaps_accessor.o : $(abspath ../../game/shared/point_bonusmaps_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_posecontroller.P
endif

$(OBJ_DIR)/point_posecontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_posecontroller.o : $(abspath ../../game/shared/point_posecontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/precache_register.P
endif

$(OBJ_DIR)/precache_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/precache_register.o : $(abspath ../../game/shared/precache_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/predictableid.P
endif

$(OBJ_DIR)/predictableid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/predictableid.o : $(abspath ../../game/shared/predictableid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/predictioncopy.P
endif

$(OBJ_DIR)/predictioncopy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/predictioncopy.o : $(abspath ../../game/shared/predictioncopy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/props_shared.P
endif

$(OBJ_DIR)/props_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/props_shared.o : $(abspath ../../game/shared/props_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll_shared.P
endif

$(OBJ_DIR)/ragdoll_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ragdoll_shared.o : $(abspath ../../game/shared/ragdoll_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope_helpers.P
endif

$(OBJ_DIR)/rope_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/rope_helpers.o : $(abspath ../../game/shared/rope_helpers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/saverestore.P
endif

$(OBJ_DIR)/saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/saverestore.o : $(abspath ../../game/shared/saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sceneentity_shared.P
endif

$(OBJ_DIR)/sceneentity_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sceneentity_shared.o : $(abspath ../../game/shared/sceneentity_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/script_intro_shared.P
endif

$(OBJ_DIR)/script_intro_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/script_intro_shared.o : $(abspath ../../game/shared/script_intro_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sequence_Transitioner.P
endif

$(OBJ_DIR)/sequence_Transitioner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sequence_Transitioner.o : $(abspath ../../game/shared/sequence_Transitioner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sheetsimulator.P
endif

$(OBJ_DIR)/sheetsimulator.o : $(abspath ../../game/shared/sheetsimulator.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simtimer.P
endif

$(OBJ_DIR)/simtimer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/simtimer.o : $(abspath ../../game/shared/simtimer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/singleplay_gamerules.P
endif

$(OBJ_DIR)/singleplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/singleplay_gamerules.o : $(abspath ../../game/shared/singleplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sixense_convars.P
endif

$(OBJ_DIR)/sixense_convars.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sixense_convars.o : $(abspath ../../game/shared/sixense/sixense_convars.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SoundEmitterSystem.P
endif

$(OBJ_DIR)/SoundEmitterSystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SoundEmitterSystem.o : $(abspath ../../game/shared/SoundEmitterSystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundenvelope.P
endif

$(OBJ_DIR)/soundenvelope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundenvelope.o : $(abspath ../../game/shared/soundenvelope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Sprite.P
endif

$(OBJ_DIR)/Sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/Sprite.o : $(abspath ../../game/shared/Sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SpriteTrail.P
endif

$(OBJ_DIR)/SpriteTrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SpriteTrail.o : $(abspath ../../game/shared/SpriteTrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio_shared.P
endif

$(OBJ_DIR)/studio_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/studio_shared.o : $(abspath ../../game/shared/studio_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/takedamageinfo.P
endif

$(OBJ_DIR)/takedamageinfo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/takedamageinfo.o : $(abspath ../../game/shared/takedamageinfo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teamplayroundbased_gamerules.P
endif

$(OBJ_DIR)/teamplayroundbased_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/teamplayroundbased_gamerules.o : $(abspath ../../game/shared/teamplayroundbased_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teamplay_gamerules.P
endif

$(OBJ_DIR)/teamplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/teamplay_gamerules.o : $(abspath ../../game/shared/teamplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/test_ehandle.P
endif

$(OBJ_DIR)/test_ehandle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/test_ehandle.o : $(abspath ../../game/shared/test_ehandle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/usercmd.P
endif

$(OBJ_DIR)/usercmd.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/usercmd.o : $(abspath ../../game/shared/usercmd.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/usermessages.P
endif

$(OBJ_DIR)/usermessages.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/usermessages.o : $(abspath ../../game/shared/usermessages.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/util_shared.P
endif

$(OBJ_DIR)/util_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/util_shared.o : $(abspath ../../game/shared/util_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_viewblend_shared.P
endif

$(OBJ_DIR)/vehicle_viewblend_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_viewblend_shared.o : $(abspath ../../game/shared/vehicle_viewblend_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_banmgr.P
endif

$(OBJ_DIR)/voice_banmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/voice_banmgr.o : $(abspath ../../game/shared/voice_banmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_status.P
endif

$(OBJ_DIR)/voice_status.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/voice_status.o : $(abspath ../../game/shared/voice_status.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_parse.P
endif

$(OBJ_DIR)/weapon_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_parse.o : $(abspath ../../game/shared/weapon_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_parse_default.P
endif

$(OBJ_DIR)/weapon_parse_default.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_parse_default.o : $(abspath ../../game/shared/weapon_parse_default.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bone_accessor.P
endif

$(OBJ_DIR)/bone_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bone_accessor.o : $(abspath ../../public/bone_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bone_setup.P
endif

$(OBJ_DIR)/bone_setup.o : $(abspath ../../public/bone_setup.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_class.P
endif

$(OBJ_DIR)/client_class.o : $(abspath ../../public/client_class.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionutils.P
endif

$(OBJ_DIR)/collisionutils.o : $(abspath ../../public/collisionutils.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/crtmemdebug.P
endif

$(OBJ_DIR)/crtmemdebug.o : $(abspath ../../public/crtmemdebug.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_recv.P
endif

$(OBJ_DIR)/dt_recv.o : $(abspath ../../public/dt_recv.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_common.P
endif

$(OBJ_DIR)/dt_utlvector_common.o : $(abspath ../../public/dt_utlvector_common.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_recv.P
endif

$(OBJ_DIR)/dt_utlvector_recv.o : $(abspath ../../public/dt_utlvector_recv.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../../public/filesystem_helpers.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/haptic_msgs.P
endif

$(OBJ_DIR)/haptic_msgs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/haptic_msgs.o : $(abspath ../../public/haptics/haptic_msgs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interpolatortypes.P
endif

$(OBJ_DIR)/interpolatortypes.o : $(abspath ../../public/interpolatortypes.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/jigglebones.P
endif

$(OBJ_DIR)/jigglebones.o : $(abspath ../../public/jigglebones.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkvar.P
endif

$(OBJ_DIR)/networkvar.o : $(abspath ../../public/networkvar.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/posedebugger.P
endif

$(OBJ_DIR)/posedebugger.o : $(abspath ../../public/posedebugger.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/renamed_recvtable_compat.P
endif

$(OBJ_DIR)/renamed_recvtable_compat.o : $(abspath ../../public/renamed_recvtable_compat.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope_physics.P
endif

$(OBJ_DIR)/rope_physics.o : $(abspath ../../public/rope_physics.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scratchpad3d.P
endif

$(OBJ_DIR)/scratchpad3d.o : $(abspath ../../public/scratchpad3d.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScratchPadUtils.P
endif

$(OBJ_DIR)/ScratchPadUtils.o : $(abspath ../../public/ScratchPadUtils.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sentence.P
endif

$(OBJ_DIR)/sentence.o : $(abspath ../../public/sentence.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simple_physics.P
endif

$(OBJ_DIR)/simple_physics.o : $(abspath ../../public/simple_physics.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SoundParametersInternal.P
endif

$(OBJ_DIR)/SoundParametersInternal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SoundParametersInternal.o : $(abspath ../../public/SoundParametersInternal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stringregistry.P
endif

$(OBJ_DIR)/stringregistry.o : $(abspath ../../public/stringregistry.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio.P
endif

$(OBJ_DIR)/studio.o : $(abspath ../../public/studio.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bonelist.P
endif

$(OBJ_DIR)/bonelist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bonelist.o : $(abspath ../../public/tools/bonelist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vallocator.P
endif

$(OBJ_DIR)/vallocator.o : $(abspath ../../public/vallocator.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../../public/vgui_controls/vgui_controls.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievement_notification_panel.P
endif

$(OBJ_DIR)/achievement_notification_panel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievement_notification_panel.o : $(abspath achievement_notification_panel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/alphamaterialproxy.P
endif

$(OBJ_DIR)/alphamaterialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/alphamaterialproxy.o : $(abspath alphamaterialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animatedentitytextureproxy.P
endif

$(OBJ_DIR)/animatedentitytextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animatedentitytextureproxy.o : $(abspath animatedentitytextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animatedoffsettextureproxy.P
endif

$(OBJ_DIR)/animatedoffsettextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animatedoffsettextureproxy.o : $(abspath animatedoffsettextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animatedtextureproxy.P
endif

$(OBJ_DIR)/animatedtextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animatedtextureproxy.o : $(abspath animatedtextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AnimateSpecificTextureProxy.P
endif

$(OBJ_DIR)/AnimateSpecificTextureProxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/AnimateSpecificTextureProxy.o : $(abspath AnimateSpecificTextureProxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseanimatedtextureproxy.P
endif

$(OBJ_DIR)/baseanimatedtextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseanimatedtextureproxy.o : $(abspath baseanimatedtextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseclientrendertargets.P
endif

$(OBJ_DIR)/baseclientrendertargets.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseclientrendertargets.o : $(abspath baseclientrendertargets.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basepresence.P
endif

$(OBJ_DIR)/basepresence.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basepresence.o : $(abspath basepresence.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/beamdraw.P
endif

$(OBJ_DIR)/beamdraw.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/beamdraw.o : $(abspath beamdraw.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bone_merge_cache.P
endif

$(OBJ_DIR)/bone_merge_cache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bone_merge_cache.o : $(abspath bone_merge_cache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/camomaterialproxy.P
endif

$(OBJ_DIR)/camomaterialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/camomaterialproxy.o : $(abspath camomaterialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_bounded_cvars.P
endif

$(OBJ_DIR)/cdll_bounded_cvars.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cdll_bounded_cvars.o : $(abspath cdll_bounded_cvars.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_client_int.P
endif

$(OBJ_DIR)/cdll_client_int.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cdll_client_int.o : $(abspath cdll_client_int.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_util.P
endif

$(OBJ_DIR)/cdll_util.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cdll_util.o : $(abspath cdll_util.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/classmap.P
endif

$(OBJ_DIR)/classmap.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/classmap.o : $(abspath classmap.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clienteffectprecachesystem.P
endif

$(OBJ_DIR)/clienteffectprecachesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clienteffectprecachesystem.o : $(abspath clienteffectprecachesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cliententitylist.P
endif

$(OBJ_DIR)/cliententitylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cliententitylist.o : $(abspath cliententitylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientleafsystem.P
endif

$(OBJ_DIR)/clientleafsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientleafsystem.o : $(abspath clientleafsystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientmode_shared.P
endif

$(OBJ_DIR)/clientmode_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientmode_shared.o : $(abspath clientmode_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientshadowmgr.P
endif

$(OBJ_DIR)/clientshadowmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientshadowmgr.o : $(abspath clientshadowmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientsideeffects.P
endif

$(OBJ_DIR)/clientsideeffects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientsideeffects.o : $(abspath clientsideeffects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientsideeffects_test.P
endif

$(OBJ_DIR)/clientsideeffects_test.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientsideeffects_test.o : $(abspath clientsideeffects_test.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientsteamcontext.P
endif

$(OBJ_DIR)/clientsteamcontext.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientsteamcontext.o : $(abspath clientsteamcontext.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_factorylist.P
endif

$(OBJ_DIR)/client_factorylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/client_factorylist.o : $(abspath client_factorylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_thinklist.P
endif

$(OBJ_DIR)/client_thinklist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/client_thinklist.o : $(abspath client_thinklist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client_virtualreality.P
endif

$(OBJ_DIR)/client_virtualreality.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/client_virtualreality.o : $(abspath client_virtualreality.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_mat_stub.P
endif

$(OBJ_DIR)/cl_mat_stub.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cl_mat_stub.o : $(abspath cl_mat_stub.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrectionmgr.P
endif

$(OBJ_DIR)/colorcorrectionmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/colorcorrectionmgr.o : $(abspath colorcorrectionmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/commentary_modelviewer.P
endif

$(OBJ_DIR)/commentary_modelviewer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/commentary_modelviewer.o : $(abspath commentary_modelviewer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_ai_basehumanoid.P
endif

$(OBJ_DIR)/c_ai_basehumanoid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_ai_basehumanoid.o : $(abspath c_ai_basehumanoid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_ai_basenpc.P
endif

$(OBJ_DIR)/c_ai_basenpc.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_ai_basenpc.o : $(abspath c_ai_basenpc.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseanimating.P
endif

$(OBJ_DIR)/c_baseanimating.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseanimating.o : $(abspath c_baseanimating.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseanimatingoverlay.P
endif

$(OBJ_DIR)/c_baseanimatingoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseanimatingoverlay.o : $(abspath c_baseanimatingoverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basecombatcharacter.P
endif

$(OBJ_DIR)/c_basecombatcharacter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basecombatcharacter.o : $(abspath c_basecombatcharacter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basecombatweapon.P
endif

$(OBJ_DIR)/c_basecombatweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basecombatweapon.o : $(abspath c_basecombatweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basedoor.P
endif

$(OBJ_DIR)/c_basedoor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basedoor.o : $(abspath c_basedoor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseentity.P
endif

$(OBJ_DIR)/c_baseentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseentity.o : $(abspath c_baseentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseflex.P
endif

$(OBJ_DIR)/c_baseflex.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseflex.o : $(abspath c_baseflex.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseplayer.P
endif

$(OBJ_DIR)/c_baseplayer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseplayer.o : $(abspath c_baseplayer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basetempentity.P
endif

$(OBJ_DIR)/c_basetempentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basetempentity.o : $(abspath c_basetempentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_baseviewmodel.P
endif

$(OBJ_DIR)/c_baseviewmodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_baseviewmodel.o : $(abspath c_baseviewmodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_breakableprop.P
endif

$(OBJ_DIR)/c_breakableprop.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_breakableprop.o : $(abspath c_breakableprop.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_colorcorrection.P
endif

$(OBJ_DIR)/c_colorcorrection.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_colorcorrection.o : $(abspath c_colorcorrection.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_colorcorrectionvolume.P
endif

$(OBJ_DIR)/c_colorcorrectionvolume.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_colorcorrectionvolume.o : $(abspath c_colorcorrectionvolume.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_dynamiclight.P
endif

$(OBJ_DIR)/c_dynamiclight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_dynamiclight.o : $(abspath c_dynamiclight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_effects.P
endif

$(OBJ_DIR)/c_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_effects.o : $(abspath c_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_entitydissolve.P
endif

$(OBJ_DIR)/c_entitydissolve.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_entitydissolve.o : $(abspath c_entitydissolve.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_entityparticletrail.P
endif

$(OBJ_DIR)/c_entityparticletrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_entityparticletrail.o : $(abspath c_entityparticletrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_fog_controller.P
endif

$(OBJ_DIR)/c_env_fog_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_fog_controller.o : $(abspath c_env_fog_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_particlescript.P
endif

$(OBJ_DIR)/c_env_particlescript.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_particlescript.o : $(abspath c_env_particlescript.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_projectedtexture.P
endif

$(OBJ_DIR)/c_env_projectedtexture.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_projectedtexture.o : $(abspath c_env_projectedtexture.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_screenoverlay.P
endif

$(OBJ_DIR)/c_env_screenoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_screenoverlay.o : $(abspath c_env_screenoverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_tonemap_controller.P
endif

$(OBJ_DIR)/c_env_tonemap_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_tonemap_controller.o : $(abspath c_env_tonemap_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_fire_smoke.P
endif

$(OBJ_DIR)/c_fire_smoke.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_fire_smoke.o : $(abspath c_fire_smoke.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_fish.P
endif

$(OBJ_DIR)/c_fish.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_fish.o : $(abspath c_fish.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_areaportalwindow.P
endif

$(OBJ_DIR)/c_func_areaportalwindow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_areaportalwindow.o : $(abspath c_func_areaportalwindow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_breakablesurf.P
endif

$(OBJ_DIR)/c_func_breakablesurf.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_breakablesurf.o : $(abspath c_func_breakablesurf.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_conveyor.P
endif

$(OBJ_DIR)/c_func_conveyor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_conveyor.o : $(abspath c_func_conveyor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_dust.P
endif

$(OBJ_DIR)/c_func_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_dust.o : $(abspath c_func_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_lod.P
endif

$(OBJ_DIR)/c_func_lod.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_lod.o : $(abspath c_func_lod.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_occluder.P
endif

$(OBJ_DIR)/c_func_occluder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_occluder.o : $(abspath c_func_occluder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_reflective_glass.P
endif

$(OBJ_DIR)/c_func_reflective_glass.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_reflective_glass.o : $(abspath c_func_reflective_glass.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_rotating.P
endif

$(OBJ_DIR)/c_func_rotating.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_rotating.o : $(abspath c_func_rotating.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_smokevolume.P
endif

$(OBJ_DIR)/c_func_smokevolume.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_smokevolume.o : $(abspath c_func_smokevolume.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_tracktrain.P
endif

$(OBJ_DIR)/c_func_tracktrain.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_tracktrain.o : $(abspath c_func_tracktrain.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_gib.P
endif

$(OBJ_DIR)/c_gib.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_gib.o : $(abspath c_gib.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_hairball.P
endif

$(OBJ_DIR)/c_hairball.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_hairball.o : $(abspath c_hairball.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_impact_effects.P
endif

$(OBJ_DIR)/c_impact_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_impact_effects.o : $(abspath c_impact_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_info_overlay_accessor.P
endif

$(OBJ_DIR)/c_info_overlay_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_info_overlay_accessor.o : $(abspath c_info_overlay_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_lightglow.P
endif

$(OBJ_DIR)/c_lightglow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_lightglow.o : $(abspath c_lightglow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/C_MaterialModifyControl.P
endif

$(OBJ_DIR)/C_MaterialModifyControl.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/C_MaterialModifyControl.o : $(abspath C_MaterialModifyControl.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_movie_explosion.P
endif

$(OBJ_DIR)/c_movie_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_movie_explosion.o : $(abspath c_movie_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_particle_fire.P
endif

$(OBJ_DIR)/c_particle_fire.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_particle_fire.o : $(abspath c_particle_fire.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_particle_smokegrenade.P
endif

$(OBJ_DIR)/c_particle_smokegrenade.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_particle_smokegrenade.o : $(abspath c_particle_smokegrenade.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_particle_system.P
endif

$(OBJ_DIR)/c_particle_system.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_particle_system.o : $(abspath c_particle_system.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_physbox.P
endif

$(OBJ_DIR)/c_physbox.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_physbox.o : $(abspath c_physbox.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_physicsprop.P
endif

$(OBJ_DIR)/c_physicsprop.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_physicsprop.o : $(abspath c_physicsprop.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_physmagnet.P
endif

$(OBJ_DIR)/c_physmagnet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_physmagnet.o : $(abspath c_physmagnet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_pixel_visibility.P
endif

$(OBJ_DIR)/c_pixel_visibility.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_pixel_visibility.o : $(abspath c_pixel_visibility.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_plasma.P
endif

$(OBJ_DIR)/c_plasma.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_plasma.o : $(abspath c_plasma.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_playerresource.P
endif

$(OBJ_DIR)/c_playerresource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_playerresource.o : $(abspath c_playerresource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_point_camera.P
endif

$(OBJ_DIR)/c_point_camera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_point_camera.o : $(abspath c_point_camera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_point_commentary_node.P
endif

$(OBJ_DIR)/c_point_commentary_node.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_point_commentary_node.o : $(abspath c_point_commentary_node.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_props.P
endif

$(OBJ_DIR)/c_props.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_props.o : $(abspath c_props.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_prop_vehicle.P
endif

$(OBJ_DIR)/c_prop_vehicle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_prop_vehicle.o : $(abspath c_prop_vehicle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_ragdoll_manager.P
endif

$(OBJ_DIR)/c_ragdoll_manager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_ragdoll_manager.o : $(abspath c_ragdoll_manager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_recipientfilter.P
endif

$(OBJ_DIR)/c_recipientfilter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_recipientfilter.o : $(abspath c_recipientfilter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_rope.P
endif

$(OBJ_DIR)/c_rope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_rope.o : $(abspath c_rope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_rumble.P
endif

$(OBJ_DIR)/c_rumble.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_rumble.o : $(abspath c_rumble.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_sceneentity.P
endif

$(OBJ_DIR)/c_sceneentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_sceneentity.o : $(abspath c_sceneentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_shadowcontrol.P
endif

$(OBJ_DIR)/c_shadowcontrol.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_shadowcontrol.o : $(abspath c_shadowcontrol.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_slideshow_display.P
endif

$(OBJ_DIR)/c_slideshow_display.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_slideshow_display.o : $(abspath c_slideshow_display.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_smokestack.P
endif

$(OBJ_DIR)/c_smokestack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_smokestack.o : $(abspath c_smokestack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_smoke_trail.P
endif

$(OBJ_DIR)/c_smoke_trail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_smoke_trail.o : $(abspath c_smoke_trail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_soundscape.P
endif

$(OBJ_DIR)/c_soundscape.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_soundscape.o : $(abspath c_soundscape.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_spotlight_end.P
endif

$(OBJ_DIR)/c_spotlight_end.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_spotlight_end.o : $(abspath c_spotlight_end.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_sprite.P
endif

$(OBJ_DIR)/c_sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_sprite.o : $(abspath c_sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_sprite_perfmonitor.P
endif

$(OBJ_DIR)/c_sprite_perfmonitor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_sprite_perfmonitor.o : $(abspath c_sprite_perfmonitor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_steamjet.P
endif

$(OBJ_DIR)/c_steamjet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_steamjet.o : $(abspath c_steamjet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_stickybolt.P
endif

$(OBJ_DIR)/c_stickybolt.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_stickybolt.o : $(abspath c_stickybolt.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_sun.P
endif

$(OBJ_DIR)/c_sun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_sun.o : $(abspath c_sun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te.P
endif

$(OBJ_DIR)/c_te.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te.o : $(abspath c_te.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_team.P
endif

$(OBJ_DIR)/c_team.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_team.o : $(abspath c_team.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_team_objectiveresource.P
endif

$(OBJ_DIR)/c_team_objectiveresource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_team_objectiveresource.o : $(abspath c_team_objectiveresource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_tesla.P
endif

$(OBJ_DIR)/c_tesla.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_tesla.o : $(abspath c_tesla.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_testtraceline.P
endif

$(OBJ_DIR)/c_testtraceline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_testtraceline.o : $(abspath c_testtraceline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_test_proxytoggle.P
endif

$(OBJ_DIR)/c_test_proxytoggle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_test_proxytoggle.o : $(abspath c_test_proxytoggle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_armorricochet.P
endif

$(OBJ_DIR)/c_te_armorricochet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_armorricochet.o : $(abspath c_te_armorricochet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_basebeam.P
endif

$(OBJ_DIR)/c_te_basebeam.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_basebeam.o : $(abspath c_te_basebeam.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamentpoint.P
endif

$(OBJ_DIR)/c_te_beamentpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamentpoint.o : $(abspath c_te_beamentpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beaments.P
endif

$(OBJ_DIR)/c_te_beaments.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beaments.o : $(abspath c_te_beaments.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamfollow.P
endif

$(OBJ_DIR)/c_te_beamfollow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamfollow.o : $(abspath c_te_beamfollow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamlaser.P
endif

$(OBJ_DIR)/c_te_beamlaser.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamlaser.o : $(abspath c_te_beamlaser.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beampoints.P
endif

$(OBJ_DIR)/c_te_beampoints.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beampoints.o : $(abspath c_te_beampoints.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamring.P
endif

$(OBJ_DIR)/c_te_beamring.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamring.o : $(abspath c_te_beamring.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamringpoint.P
endif

$(OBJ_DIR)/c_te_beamringpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamringpoint.o : $(abspath c_te_beamringpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_beamspline.P
endif

$(OBJ_DIR)/c_te_beamspline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_beamspline.o : $(abspath c_te_beamspline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bloodsprite.P
endif

$(OBJ_DIR)/c_te_bloodsprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bloodsprite.o : $(abspath c_te_bloodsprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bloodstream.P
endif

$(OBJ_DIR)/c_te_bloodstream.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bloodstream.o : $(abspath c_te_bloodstream.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_breakmodel.P
endif

$(OBJ_DIR)/c_te_breakmodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_breakmodel.o : $(abspath c_te_breakmodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bspdecal.P
endif

$(OBJ_DIR)/c_te_bspdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bspdecal.o : $(abspath c_te_bspdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bubbles.P
endif

$(OBJ_DIR)/c_te_bubbles.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bubbles.o : $(abspath c_te_bubbles.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_bubbletrail.P
endif

$(OBJ_DIR)/c_te_bubbletrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_bubbletrail.o : $(abspath c_te_bubbletrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_clientprojectile.P
endif

$(OBJ_DIR)/c_te_clientprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_clientprojectile.o : $(abspath c_te_clientprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_decal.P
endif

$(OBJ_DIR)/c_te_decal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_decal.o : $(abspath c_te_decal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_dynamiclight.P
endif

$(OBJ_DIR)/c_te_dynamiclight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_dynamiclight.o : $(abspath c_te_dynamiclight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_effect_dispatch.P
endif

$(OBJ_DIR)/c_te_effect_dispatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_effect_dispatch.o : $(abspath c_te_effect_dispatch.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_energysplash.P
endif

$(OBJ_DIR)/c_te_energysplash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_energysplash.o : $(abspath c_te_energysplash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_explosion.P
endif

$(OBJ_DIR)/c_te_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_explosion.o : $(abspath c_te_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_fizz.P
endif

$(OBJ_DIR)/c_te_fizz.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_fizz.o : $(abspath c_te_fizz.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_footprint.P
endif

$(OBJ_DIR)/c_te_footprint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_footprint.o : $(abspath c_te_footprint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_glassshatter.P
endif

$(OBJ_DIR)/c_te_glassshatter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_glassshatter.o : $(abspath c_te_glassshatter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_glowsprite.P
endif

$(OBJ_DIR)/c_te_glowsprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_glowsprite.o : $(abspath c_te_glowsprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_impact.P
endif

$(OBJ_DIR)/c_te_impact.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_impact.o : $(abspath c_te_impact.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_killplayerattachments.P
endif

$(OBJ_DIR)/c_te_killplayerattachments.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_killplayerattachments.o : $(abspath c_te_killplayerattachments.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_largefunnel.P
endif

$(OBJ_DIR)/c_te_largefunnel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_largefunnel.o : $(abspath c_te_largefunnel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_legacytempents.P
endif

$(OBJ_DIR)/c_te_legacytempents.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_legacytempents.o : $(abspath c_te_legacytempents.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_muzzleflash.P
endif

$(OBJ_DIR)/c_te_muzzleflash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_muzzleflash.o : $(abspath c_te_muzzleflash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_particlesystem.P
endif

$(OBJ_DIR)/c_te_particlesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_particlesystem.o : $(abspath c_te_particlesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_physicsprop.P
endif

$(OBJ_DIR)/c_te_physicsprop.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_physicsprop.o : $(abspath c_te_physicsprop.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_playerdecal.P
endif

$(OBJ_DIR)/c_te_playerdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_playerdecal.o : $(abspath c_te_playerdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_projecteddecal.P
endif

$(OBJ_DIR)/c_te_projecteddecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_projecteddecal.o : $(abspath c_te_projecteddecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_showline.P
endif

$(OBJ_DIR)/c_te_showline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_showline.o : $(abspath c_te_showline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_smoke.P
endif

$(OBJ_DIR)/c_te_smoke.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_smoke.o : $(abspath c_te_smoke.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_sparks.P
endif

$(OBJ_DIR)/c_te_sparks.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_sparks.o : $(abspath c_te_sparks.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_sprite.P
endif

$(OBJ_DIR)/c_te_sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_sprite.o : $(abspath c_te_sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_spritespray.P
endif

$(OBJ_DIR)/c_te_spritespray.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_spritespray.o : $(abspath c_te_spritespray.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_worlddecal.P
endif

$(OBJ_DIR)/c_te_worlddecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_worlddecal.o : $(abspath c_te_worlddecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_tracer.P
endif

$(OBJ_DIR)/c_tracer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_tracer.o : $(abspath c_tracer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_user_message_register.P
endif

$(OBJ_DIR)/c_user_message_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_user_message_register.o : $(abspath c_user_message_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_choreo_generic.P
endif

$(OBJ_DIR)/c_vehicle_choreo_generic.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_choreo_generic.o : $(abspath c_vehicle_choreo_generic.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_jeep.P
endif

$(OBJ_DIR)/c_vehicle_jeep.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_jeep.o : $(abspath c_vehicle_jeep.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vguiscreen.P
endif

$(OBJ_DIR)/c_vguiscreen.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vguiscreen.o : $(abspath c_vguiscreen.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/C_WaterLODControl.P
endif

$(OBJ_DIR)/C_WaterLODControl.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/C_WaterLODControl.o : $(abspath C_WaterLODControl.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_world.P
endif

$(OBJ_DIR)/c_world.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_world.o : $(abspath c_world.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/death.P
endif

$(OBJ_DIR)/death.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/death.o : $(abspath death.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/detailobjectsystem.P
endif

$(OBJ_DIR)/detailobjectsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/detailobjectsystem.o : $(abspath detailobjectsystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dummyproxy.P
endif

$(OBJ_DIR)/dummyproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/dummyproxy.o : $(abspath dummyproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EffectsClient.P
endif

$(OBJ_DIR)/EffectsClient.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EffectsClient.o : $(abspath EffectsClient.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entityoriginmaterialproxy.P
endif

$(OBJ_DIR)/entityoriginmaterialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entityoriginmaterialproxy.o : $(abspath entityoriginmaterialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entity_client_tools.P
endif

$(OBJ_DIR)/entity_client_tools.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entity_client_tools.o : $(abspath entity_client_tools.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vort_charge_token.P
endif

$(OBJ_DIR)/c_vort_charge_token.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vort_charge_token.o : $(abspath episodic/c_vort_charge_token.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/flashlighteffect.P
endif

$(OBJ_DIR)/flashlighteffect.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/flashlighteffect.o : $(abspath flashlighteffect.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/functionproxy.P
endif

$(OBJ_DIR)/functionproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/functionproxy.o : $(abspath functionproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx.P
endif

$(OBJ_DIR)/fx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx.o : $(abspath fx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_blood.P
endif

$(OBJ_DIR)/fx_blood.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_blood.o : $(abspath fx_blood.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_cube.P
endif

$(OBJ_DIR)/fx_cube.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_cube.o : $(abspath fx_cube.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_discreetline.P
endif

$(OBJ_DIR)/fx_discreetline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_discreetline.o : $(abspath fx_discreetline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_envelope.P
endif

$(OBJ_DIR)/fx_envelope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_envelope.o : $(abspath fx_envelope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_explosion.P
endif

$(OBJ_DIR)/fx_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_explosion.o : $(abspath fx_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_fleck.P
endif

$(OBJ_DIR)/fx_fleck.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_fleck.o : $(abspath fx_fleck.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_impact.P
endif

$(OBJ_DIR)/fx_impact.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_impact.o : $(abspath fx_impact.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_interpvalue.P
endif

$(OBJ_DIR)/fx_interpvalue.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_interpvalue.o : $(abspath fx_interpvalue.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_line.P
endif

$(OBJ_DIR)/fx_line.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_line.o : $(abspath fx_line.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_quad.P
endif

$(OBJ_DIR)/fx_quad.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_quad.o : $(abspath fx_quad.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_shelleject.P
endif

$(OBJ_DIR)/fx_shelleject.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_shelleject.o : $(abspath fx_shelleject.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_sparks.P
endif

$(OBJ_DIR)/fx_sparks.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_sparks.o : $(abspath fx_sparks.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_staticline.P
endif

$(OBJ_DIR)/fx_staticline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_staticline.o : $(abspath fx_staticline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_tracer.P
endif

$(OBJ_DIR)/fx_tracer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_tracer.o : $(abspath fx_tracer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_trail.P
endif

$(OBJ_DIR)/fx_trail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_trail.o : $(abspath fx_trail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_water.P
endif

$(OBJ_DIR)/fx_water.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_water.o : $(abspath fx_water.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gametrace_client.P
endif

$(OBJ_DIR)/gametrace_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gametrace_client.o : $(abspath gametrace_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basemodelpanel.P
endif

$(OBJ_DIR)/basemodelpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basemodelpanel.o : $(abspath game_controls/basemodelpanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basemodel_panel.P
endif

$(OBJ_DIR)/basemodel_panel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basemodel_panel.o : $(abspath game_controls/basemodel_panel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseviewport.P
endif

$(OBJ_DIR)/baseviewport.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseviewport.o : $(abspath game_controls/baseviewport.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ClientScoreBoardDialog.P
endif

$(OBJ_DIR)/ClientScoreBoardDialog.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ClientScoreBoardDialog.o : $(abspath game_controls/ClientScoreBoardDialog.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/commandmenu.P
endif

$(OBJ_DIR)/commandmenu.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/commandmenu.o : $(abspath game_controls/commandmenu.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/IconPanel.P
endif

$(OBJ_DIR)/IconPanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/IconPanel.o : $(abspath game_controls/IconPanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/intromenu.P
endif

$(OBJ_DIR)/intromenu.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/intromenu.o : $(abspath game_controls/intromenu.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MapOverview.P
endif

$(OBJ_DIR)/MapOverview.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/MapOverview.o : $(abspath game_controls/MapOverview.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/NavProgress.P
endif

$(OBJ_DIR)/NavProgress.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/NavProgress.o : $(abspath game_controls/NavProgress.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SpectatorGUI.P
endif

$(OBJ_DIR)/SpectatorGUI.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SpectatorGUI.o : $(abspath game_controls/SpectatorGUI.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teammenu.P
endif

$(OBJ_DIR)/teammenu.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/teammenu.o : $(abspath game_controls/teammenu.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vguitextwindow.P
endif

$(OBJ_DIR)/vguitextwindow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vguitextwindow.o : $(abspath game_controls/vguitextwindow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/geiger.P
endif

$(OBJ_DIR)/geiger.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/geiger.o : $(abspath geiger.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/glow_outline_effect.P
endif

$(OBJ_DIR)/glow_outline_effect.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/glow_outline_effect.o : $(abspath glow_outline_effect.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/glow_overlay.P
endif

$(OBJ_DIR)/glow_overlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/glow_overlay.o : $(abspath glow_overlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/history_resource.P
endif

$(OBJ_DIR)/history_resource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/history_resource.o : $(abspath history_resource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/clientmode_hlnormal.P
endif

$(OBJ_DIR)/clientmode_hlnormal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/clientmode_hlnormal.o : $(abspath hl2/clientmode_hlnormal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_antlion_dust.P
endif

$(OBJ_DIR)/c_antlion_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_antlion_dust.o : $(abspath hl2/c_antlion_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_ar2_explosion.P
endif

$(OBJ_DIR)/c_ar2_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_ar2_explosion.o : $(abspath hl2/c_ar2_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_barnacle.P
endif

$(OBJ_DIR)/c_barnacle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_barnacle.o : $(abspath hl2/c_barnacle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_barney.P
endif

$(OBJ_DIR)/c_barney.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_barney.o : $(abspath hl2/c_barney.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basehelicopter.P
endif

$(OBJ_DIR)/c_basehelicopter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basehelicopter.o : $(abspath hl2/c_basehelicopter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basehlcombatweapon.P
endif

$(OBJ_DIR)/c_basehlcombatweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basehlcombatweapon.o : $(abspath hl2/c_basehlcombatweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_basehlplayer.P
endif

$(OBJ_DIR)/c_basehlplayer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_basehlplayer.o : $(abspath hl2/c_basehlplayer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_citadel_effects.P
endif

$(OBJ_DIR)/c_citadel_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_citadel_effects.o : $(abspath hl2/c_citadel_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_corpse.P
endif

$(OBJ_DIR)/c_corpse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_corpse.o : $(abspath hl2/c_corpse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_alyxtemp.P
endif

$(OBJ_DIR)/c_env_alyxtemp.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_alyxtemp.o : $(abspath hl2/c_env_alyxtemp.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_headcrabcanister.P
endif

$(OBJ_DIR)/c_env_headcrabcanister.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_headcrabcanister.o : $(abspath hl2/c_env_headcrabcanister.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_env_starfield.P
endif

$(OBJ_DIR)/c_env_starfield.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_env_starfield.o : $(abspath hl2/c_env_starfield.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/C_Func_Monitor.P
endif

$(OBJ_DIR)/C_Func_Monitor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/C_Func_Monitor.o : $(abspath hl2/C_Func_Monitor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_func_tankmortar.P
endif

$(OBJ_DIR)/c_func_tankmortar.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_func_tankmortar.o : $(abspath hl2/c_func_tankmortar.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_hl2_playerlocaldata.P
endif

$(OBJ_DIR)/c_hl2_playerlocaldata.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_hl2_playerlocaldata.o : $(abspath hl2/c_hl2_playerlocaldata.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_info_teleporter_countdown.P
endif

$(OBJ_DIR)/c_info_teleporter_countdown.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_info_teleporter_countdown.o : $(abspath hl2/c_info_teleporter_countdown.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_npc_antlionguard.P
endif

$(OBJ_DIR)/c_npc_antlionguard.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_npc_antlionguard.o : $(abspath hl2/c_npc_antlionguard.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_npc_combinegunship.P
endif

$(OBJ_DIR)/c_npc_combinegunship.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_npc_combinegunship.o : $(abspath hl2/c_npc_combinegunship.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_npc_manhack.P
endif

$(OBJ_DIR)/c_npc_manhack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_npc_manhack.o : $(abspath hl2/c_npc_manhack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_npc_rollermine.P
endif

$(OBJ_DIR)/c_npc_rollermine.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_npc_rollermine.o : $(abspath hl2/c_npc_rollermine.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_plasma_beam_node.P
endif

$(OBJ_DIR)/c_plasma_beam_node.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_plasma_beam_node.o : $(abspath hl2/c_plasma_beam_node.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_prop_combine_ball.P
endif

$(OBJ_DIR)/c_prop_combine_ball.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_prop_combine_ball.o : $(abspath hl2/c_prop_combine_ball.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_rotorwash.P
endif

$(OBJ_DIR)/c_rotorwash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_rotorwash.o : $(abspath hl2/c_rotorwash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_script_intro.P
endif

$(OBJ_DIR)/c_script_intro.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_script_intro.o : $(abspath hl2/c_script_intro.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_strider.P
endif

$(OBJ_DIR)/c_strider.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_strider.o : $(abspath hl2/c_strider.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_concussiveexplosion.P
endif

$(OBJ_DIR)/c_te_concussiveexplosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_concussiveexplosion.o : $(abspath hl2/c_te_concussiveexplosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_te_flare.P
endif

$(OBJ_DIR)/c_te_flare.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_te_flare.o : $(abspath hl2/c_te_flare.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_thumper_dust.P
endif

$(OBJ_DIR)/c_thumper_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_thumper_dust.o : $(abspath hl2/c_thumper_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_airboat.P
endif

$(OBJ_DIR)/c_vehicle_airboat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_airboat.o : $(abspath hl2/c_vehicle_airboat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_cannon.P
endif

$(OBJ_DIR)/c_vehicle_cannon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_cannon.o : $(abspath hl2/c_vehicle_cannon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_crane.P
endif

$(OBJ_DIR)/c_vehicle_crane.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_crane.o : $(abspath hl2/c_vehicle_crane.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_vehicle_prisoner_pod.P
endif

$(OBJ_DIR)/c_vehicle_prisoner_pod.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_vehicle_prisoner_pod.o : $(abspath hl2/c_vehicle_prisoner_pod.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_waterbullet.P
endif

$(OBJ_DIR)/c_waterbullet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_waterbullet.o : $(abspath hl2/c_waterbullet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_weapon_crossbow.P
endif

$(OBJ_DIR)/c_weapon_crossbow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_weapon_crossbow.o : $(abspath hl2/c_weapon_crossbow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_weapon_physcannon.P
endif

$(OBJ_DIR)/c_weapon_physcannon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_weapon_physcannon.o : $(abspath hl2/c_weapon_physcannon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_weapon_stunstick.P
endif

$(OBJ_DIR)/c_weapon_stunstick.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_weapon_stunstick.o : $(abspath hl2/c_weapon_stunstick.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/c_weapon__stubs_hl2.P
endif

$(OBJ_DIR)/c_weapon__stubs_hl2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/c_weapon__stubs_hl2.o : $(abspath hl2/c_weapon__stubs_hl2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_antlion.P
endif

$(OBJ_DIR)/fx_antlion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_antlion.o : $(abspath hl2/fx_antlion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_bugbait.P
endif

$(OBJ_DIR)/fx_bugbait.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_bugbait.o : $(abspath hl2/fx_bugbait.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_hl2_impacts.P
endif

$(OBJ_DIR)/fx_hl2_impacts.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_hl2_impacts.o : $(abspath hl2/fx_hl2_impacts.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fx_hl2_tracers.P
endif

$(OBJ_DIR)/fx_hl2_tracers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fx_hl2_tracers.o : $(abspath hl2/fx_hl2_tracers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_clientmode.P
endif

$(OBJ_DIR)/hl2_clientmode.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_clientmode.o : $(abspath hl2/hl2_clientmode.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_in_main.P
endif

$(OBJ_DIR)/hl_in_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_in_main.o : $(abspath hl2/hl_in_main.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_prediction.P
endif

$(OBJ_DIR)/hl_prediction.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_prediction.o : $(abspath hl2/hl_prediction.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_ammo.P
endif

$(OBJ_DIR)/hud_ammo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_ammo.o : $(abspath hl2/hud_ammo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_autoaim.P
endif

$(OBJ_DIR)/hud_autoaim.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_autoaim.o : $(abspath hl2/hud_autoaim.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_battery.P
endif

$(OBJ_DIR)/hud_battery.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_battery.o : $(abspath hl2/hud_battery.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_blood.P
endif

$(OBJ_DIR)/hud_blood.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_blood.o : $(abspath hl2/hud_blood.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_credits.P
endif

$(OBJ_DIR)/hud_credits.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_credits.o : $(abspath hl2/hud_credits.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_damageindicator.P
endif

$(OBJ_DIR)/hud_damageindicator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_damageindicator.o : $(abspath hl2/hud_damageindicator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_filmdemo.P
endif

$(OBJ_DIR)/hud_filmdemo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_filmdemo.o : $(abspath hl2/hud_filmdemo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_flashlight.P
endif

$(OBJ_DIR)/hud_flashlight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_flashlight.o : $(abspath hl2/hud_flashlight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_hdrdemo.P
endif

$(OBJ_DIR)/hud_hdrdemo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_hdrdemo.o : $(abspath hl2/hud_hdrdemo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_health.P
endif

$(OBJ_DIR)/hud_health.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_health.o : $(abspath hl2/hud_health.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_poisondamageindicator.P
endif

$(OBJ_DIR)/hud_poisondamageindicator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_poisondamageindicator.o : $(abspath hl2/hud_poisondamageindicator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_quickinfo.P
endif

$(OBJ_DIR)/hud_quickinfo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_quickinfo.o : $(abspath hl2/hud_quickinfo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_suitpower.P
endif

$(OBJ_DIR)/hud_suitpower.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_suitpower.o : $(abspath hl2/hud_suitpower.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_weaponselection.P
endif

$(OBJ_DIR)/hud_weaponselection.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_weaponselection.o : $(abspath hl2/hud_weaponselection.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_zoom.P
endif

$(OBJ_DIR)/hud_zoom.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_zoom.o : $(abspath hl2/hud_zoom.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shieldproxy.P
endif

$(OBJ_DIR)/shieldproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/shieldproxy.o : $(abspath hl2/shieldproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_rootpanel_hl2.P
endif

$(OBJ_DIR)/vgui_rootpanel_hl2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_rootpanel_hl2.o : $(abspath hl2/vgui_rootpanel_hl2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvcamera.P
endif

$(OBJ_DIR)/hltvcamera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hltvcamera.o : $(abspath hltvcamera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud.P
endif

$(OBJ_DIR)/hud.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud.o : $(abspath hud.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_animationinfo.P
endif

$(OBJ_DIR)/hud_animationinfo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_animationinfo.o : $(abspath hud_animationinfo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_basechat.P
endif

$(OBJ_DIR)/hud_basechat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_basechat.o : $(abspath hud_basechat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_basetimer.P
endif

$(OBJ_DIR)/hud_basetimer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_basetimer.o : $(abspath hud_basetimer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_bitmapnumericdisplay.P
endif

$(OBJ_DIR)/hud_bitmapnumericdisplay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_bitmapnumericdisplay.o : $(abspath hud_bitmapnumericdisplay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_chat.P
endif

$(OBJ_DIR)/hud_chat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_chat.o : $(abspath hud_chat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_closecaption.P
endif

$(OBJ_DIR)/hud_closecaption.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_closecaption.o : $(abspath hud_closecaption.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_crosshair.P
endif

$(OBJ_DIR)/hud_crosshair.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_crosshair.o : $(abspath hud_crosshair.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_element_helper.P
endif

$(OBJ_DIR)/hud_element_helper.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_element_helper.o : $(abspath hud_element_helper.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_hintdisplay.P
endif

$(OBJ_DIR)/hud_hintdisplay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_hintdisplay.o : $(abspath hud_hintdisplay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_lcd.P
endif

$(OBJ_DIR)/hud_lcd.o : $(abspath hud_lcd.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_msg.P
endif

$(OBJ_DIR)/hud_msg.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_msg.o : $(abspath hud_msg.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_numericdisplay.P
endif

$(OBJ_DIR)/hud_numericdisplay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_numericdisplay.o : $(abspath hud_numericdisplay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_pdump.P
endif

$(OBJ_DIR)/hud_pdump.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_pdump.o : $(abspath hud_pdump.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_posture.P
endif

$(OBJ_DIR)/hud_posture.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_posture.o : $(abspath hud_posture.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_redraw.P
endif

$(OBJ_DIR)/hud_redraw.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_redraw.o : $(abspath hud_redraw.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_squadstatus.P
endif

$(OBJ_DIR)/hud_squadstatus.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_squadstatus.o : $(abspath hud_squadstatus.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_vehicle.P
endif

$(OBJ_DIR)/hud_vehicle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_vehicle.o : $(abspath hud_vehicle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hud_weapon.P
endif

$(OBJ_DIR)/hud_weapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hud_weapon.o : $(abspath hud_weapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/initializer.P
endif

$(OBJ_DIR)/initializer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/initializer.o : $(abspath initializer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interpolatedvar.P
endif

$(OBJ_DIR)/interpolatedvar.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/interpolatedvar.o : $(abspath interpolatedvar.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_camera.P
endif

$(OBJ_DIR)/in_camera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_camera.o : $(abspath in_camera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_joystick.P
endif

$(OBJ_DIR)/in_joystick.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_joystick.o : $(abspath in_joystick.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_main.P
endif

$(OBJ_DIR)/in_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_main.o : $(abspath in_main.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_mouse.P
endif

$(OBJ_DIR)/in_mouse.o : $(abspath in_mouse.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_steamcontroller.P
endif

$(OBJ_DIR)/in_steamcontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_steamcontroller.o : $(abspath in_steamcontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/IsNPCProxy.P
endif

$(OBJ_DIR)/IsNPCProxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/IsNPCProxy.o : $(abspath IsNPCProxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lampbeamproxy.P
endif

$(OBJ_DIR)/lampbeamproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/lampbeamproxy.o : $(abspath lampbeamproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lamphaloproxy.P
endif

$(OBJ_DIR)/lamphaloproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/lamphaloproxy.o : $(abspath lamphaloproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mathproxy.P
endif

$(OBJ_DIR)/mathproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mathproxy.o : $(abspath mathproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matrixproxy.P
endif

$(OBJ_DIR)/matrixproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/matrixproxy.o : $(abspath matrixproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/menu.P
endif

$(OBJ_DIR)/menu.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/menu.o : $(abspath menu.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/message.P
endif

$(OBJ_DIR)/message.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/message.o : $(abspath message.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movehelper_client.P
endif

$(OBJ_DIR)/movehelper_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movehelper_client.o : $(abspath movehelper_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mp3player.P
endif

$(OBJ_DIR)/mp3player.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mp3player.o : $(abspath mp3player.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mumble.P
endif

$(OBJ_DIR)/mumble.o : $(abspath mumble.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/panelmetaclassmgr.P
endif

$(OBJ_DIR)/panelmetaclassmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/panelmetaclassmgr.o : $(abspath panelmetaclassmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlemgr.P
endif

$(OBJ_DIR)/particlemgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particlemgr.o : $(abspath particlemgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlesphererenderer.P
endif

$(OBJ_DIR)/particlesphererenderer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particlesphererenderer.o : $(abspath particlesphererenderer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_attractor.P
endif

$(OBJ_DIR)/particles_attractor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_attractor.o : $(abspath particles_attractor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_ez.P
endif

$(OBJ_DIR)/particles_ez.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_ez.o : $(abspath particles_ez.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_localspace.P
endif

$(OBJ_DIR)/particles_localspace.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_localspace.o : $(abspath particles_localspace.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_new.P
endif

$(OBJ_DIR)/particles_new.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_new.o : $(abspath particles_new.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particles_simple.P
endif

$(OBJ_DIR)/particles_simple.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particles_simple.o : $(abspath particles_simple.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_collision.P
endif

$(OBJ_DIR)/particle_collision.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_collision.o : $(abspath particle_collision.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_litsmokeemitter.P
endif

$(OBJ_DIR)/particle_litsmokeemitter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_litsmokeemitter.o : $(abspath particle_litsmokeemitter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_proxies.P
endif

$(OBJ_DIR)/particle_proxies.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_proxies.o : $(abspath particle_proxies.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_simple3d.P
endif

$(OBJ_DIR)/particle_simple3d.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_simple3d.o : $(abspath particle_simple3d.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/perfvisualbenchmark.P
endif

$(OBJ_DIR)/perfvisualbenchmark.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/perfvisualbenchmark.o : $(abspath perfvisualbenchmark.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics.P
endif

$(OBJ_DIR)/physics.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics.o : $(abspath physics.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_main_client.P
endif

$(OBJ_DIR)/physics_main_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_main_client.o : $(abspath physics_main_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physpropclientside.P
endif

$(OBJ_DIR)/physpropclientside.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physpropclientside.o : $(abspath physpropclientside.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/playerandobjectenumerator.P
endif

$(OBJ_DIR)/playerandobjectenumerator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/playerandobjectenumerator.o : $(abspath playerandobjectenumerator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/playerspawncache.P
endif

$(OBJ_DIR)/playerspawncache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/playerspawncache.o : $(abspath playerspawncache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/prediction.P
endif

$(OBJ_DIR)/prediction.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/prediction.o : $(abspath prediction.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/proxyentity.P
endif

$(OBJ_DIR)/proxyentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/proxyentity.o : $(abspath proxyentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ProxyHealth.P
endif

$(OBJ_DIR)/ProxyHealth.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ProxyHealth.o : $(abspath ProxyHealth.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/proxyplayer.P
endif

$(OBJ_DIR)/proxyplayer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/proxyplayer.o : $(abspath proxyplayer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/proxypupil.P
endif

$(OBJ_DIR)/proxypupil.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/proxypupil.o : $(abspath proxypupil.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll.P
endif

$(OBJ_DIR)/ragdoll.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ragdoll.o : $(abspath ragdoll.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/recvproxy.P
endif

$(OBJ_DIR)/recvproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/recvproxy.o : $(abspath recvproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rendertexture.P
endif

$(OBJ_DIR)/rendertexture.o : $(abspath rendertexture.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cdll_replay.P
endif

$(OBJ_DIR)/cdll_replay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cdll_replay.o : $(abspath replay/cdll_replay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replaycamera.P
endif

$(OBJ_DIR)/replaycamera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/replaycamera.o : $(abspath replay/replaycamera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScreenSpaceEffects.P
endif

$(OBJ_DIR)/ScreenSpaceEffects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ScreenSpaceEffects.o : $(abspath ScreenSpaceEffects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simple_keys.P
endif

$(OBJ_DIR)/simple_keys.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/simple_keys.o : $(abspath simple_keys.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_sixense.P
endif

$(OBJ_DIR)/in_sixense.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_sixense.o : $(abspath sixense/in_sixense.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/in_sixense_gesture_bindings.P
endif

$(OBJ_DIR)/in_sixense_gesture_bindings.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/in_sixense_gesture_bindings.o : $(abspath sixense/in_sixense_gesture_bindings.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/smoke_fog_overlay.P
endif

$(OBJ_DIR)/smoke_fog_overlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/smoke_fog_overlay.o : $(abspath smoke_fog_overlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/splinepatch.P
endif

$(OBJ_DIR)/splinepatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/splinepatch.o : $(abspath splinepatch.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spritemodel.P
endif

$(OBJ_DIR)/spritemodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/spritemodel.o : $(abspath spritemodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stdafx.P
endif

$(OBJ_DIR)/cbase.h.gch : cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/cbase.h.P : $(OBJ_DIR)/cbase.h.gch

vpath cbase.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/cbase.h.P
endif

$(OBJ_DIR)/cbase.h : cbase.h $(OBJ_DIR)/cbase.h.gch $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/cbase.h

$(OBJ_DIR)/stdafx.o : $(abspath stdafx.cpp) $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio_stats.P
endif

$(OBJ_DIR)/studio_stats.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/studio_stats.o : $(abspath studio_stats.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/texturescrollmaterialproxy.P
endif

$(OBJ_DIR)/texturescrollmaterialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/texturescrollmaterialproxy.o : $(abspath texturescrollmaterialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/text_message.P
endif

$(OBJ_DIR)/text_message.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/text_message.o : $(abspath text_message.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/timematerialproxy.P
endif

$(OBJ_DIR)/timematerialproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/timematerialproxy.o : $(abspath timematerialproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/toggletextureproxy.P
endif

$(OBJ_DIR)/toggletextureproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/toggletextureproxy.o : $(abspath toggletextureproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/toolframework_client.P
endif

$(OBJ_DIR)/toolframework_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/toolframework_client.o : $(abspath toolframework_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/train.P
endif

$(OBJ_DIR)/train.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/train.o : $(abspath train.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_avatarimage.P
endif

$(OBJ_DIR)/vgui_avatarimage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_avatarimage.o : $(abspath vgui_avatarimage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_basepanel.P
endif

$(OBJ_DIR)/vgui_basepanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_basepanel.o : $(abspath vgui_basepanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_bitmapbutton.P
endif

$(OBJ_DIR)/vgui_bitmapbutton.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_bitmapbutton.o : $(abspath vgui_bitmapbutton.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_bitmapimage.P
endif

$(OBJ_DIR)/vgui_bitmapimage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_bitmapimage.o : $(abspath vgui_bitmapimage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_bitmappanel.P
endif

$(OBJ_DIR)/vgui_bitmappanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_bitmappanel.o : $(abspath vgui_bitmappanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_centerstringpanel.P
endif

$(OBJ_DIR)/vgui_centerstringpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_centerstringpanel.o : $(abspath vgui_centerstringpanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_consolepanel.P
endif

$(OBJ_DIR)/vgui_consolepanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_consolepanel.o : $(abspath vgui_consolepanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_debugoverlaypanel.P
endif

$(OBJ_DIR)/vgui_debugoverlaypanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_debugoverlaypanel.o : $(abspath vgui_debugoverlaypanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_fpspanel.P
endif

$(OBJ_DIR)/vgui_fpspanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_fpspanel.o : $(abspath vgui_fpspanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_game_viewport.P
endif

$(OBJ_DIR)/vgui_game_viewport.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_game_viewport.o : $(abspath vgui_game_viewport.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_grid.P
endif

$(OBJ_DIR)/vgui_grid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_grid.o : $(abspath vgui_grid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_int.P
endif

$(OBJ_DIR)/vgui_int.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_int.o : $(abspath vgui_int.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_loadingdiscpanel.P
endif

$(OBJ_DIR)/vgui_loadingdiscpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_loadingdiscpanel.o : $(abspath vgui_loadingdiscpanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_messagechars.P
endif

$(OBJ_DIR)/vgui_messagechars.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_messagechars.o : $(abspath vgui_messagechars.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_netgraphpanel.P
endif

$(OBJ_DIR)/vgui_netgraphpanel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_netgraphpanel.o : $(abspath vgui_netgraphpanel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_schemevisualizer.P
endif

$(OBJ_DIR)/vgui_schemevisualizer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_schemevisualizer.o : $(abspath vgui_schemevisualizer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_slideshow_display_screen.P
endif

$(OBJ_DIR)/vgui_slideshow_display_screen.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_slideshow_display_screen.o : $(abspath vgui_slideshow_display_screen.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_video.P
endif

$(OBJ_DIR)/vgui_video.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_video.o : $(abspath vgui_video.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_video_player.P
endif

$(OBJ_DIR)/vgui_video_player.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vgui_video_player.o : $(abspath vgui_video_player.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view.P
endif

$(OBJ_DIR)/view.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/view.o : $(abspath view.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/viewangleanim.P
endif

$(OBJ_DIR)/viewangleanim.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/viewangleanim.o : $(abspath viewangleanim.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ViewConeImage.P
endif

$(OBJ_DIR)/ViewConeImage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ViewConeImage.o : $(abspath ViewConeImage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/viewdebug.P
endif

$(OBJ_DIR)/viewdebug.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/viewdebug.o : $(abspath viewdebug.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/viewpostprocess.P
endif

$(OBJ_DIR)/viewpostprocess.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/viewpostprocess.o : $(abspath viewpostprocess.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/viewrender.P
endif

$(OBJ_DIR)/viewrender.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/viewrender.o : $(abspath viewrender.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view_beams.P
endif

$(OBJ_DIR)/view_beams.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/view_beams.o : $(abspath view_beams.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view_effects.P
endif

$(OBJ_DIR)/view_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/view_effects.o : $(abspath view_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/view_scene.P
endif

$(OBJ_DIR)/view_scene.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/view_scene.o : $(abspath view_scene.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/warp_overlay.P
endif

$(OBJ_DIR)/warp_overlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/warp_overlay.o : $(abspath warp_overlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WaterLODMaterialProxy.P
endif

$(OBJ_DIR)/WaterLODMaterialProxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/WaterLODMaterialProxy.o : $(abspath WaterLODMaterialProxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapons_resource.P
endif

$(OBJ_DIR)/weapons_resource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapons_resource.o : $(abspath weapons_resource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_selection.P
endif

$(OBJ_DIR)/weapon_selection.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_selection.o : $(abspath weapon_selection.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WorldDimsProxy.P
endif

$(OBJ_DIR)/WorldDimsProxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/WorldDimsProxy.o : $(abspath WorldDimsProxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/client_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)


endif # (CFG=release)



