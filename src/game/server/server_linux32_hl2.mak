ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=server_hl2
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
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=server -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DGAME_DLL -DVECTOR -DVERSION_SAFE_STEAM_API_INTERFACES -DPROTECTED_THINGS_ENABLE -Dsprintf=use_Q_snprintf_instead_of_sprintf -Dstrncpy=use_Q_strncpy_instead -D_snprintf=use_Q_snprintf_instead -DSWDS -DHL2_DLL -DUSES_SAVERESTORE -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/game/server -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 ../../game/server/generated_proto_hl2 ../../thirdparty/protobuf-2.6.1/src ./ ../../game/shared ../../utils/common ../../game/shared/econ ../../game/server/NextBot ../../game/shared/hl2 ./hl2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../../game/hl2/bin/server.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/server.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../common/language.cpp \
    ../../common/randoverride.cpp \
    ../../common/steamid.cpp \
    ../../game/server/serverbenchmark_base.cpp \
    ../../game/server/vote_controller.cpp \
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
    ../../game/shared/hl2/survival_gamerules.cpp \
    ../../game/shared/igamesystem.cpp \
    ../../game/shared/interval.cpp \
    ../../game/shared/mapentities_shared.cpp \
    ../../game/shared/ModelSoundsCache.cpp \
    ../../game/shared/movevars_shared.cpp \
    ../../game/shared/mp_shareddefs.cpp \
    ../../game/shared/multiplay_gamerules.cpp \
    ../../game/shared/obstacle_pushaway.cpp \
    ../../game/shared/particlesystemquery.cpp \
    ../../game/shared/particle_parse.cpp \
    ../../game/shared/physics_main_shared.cpp \
    ../../game/shared/physics_saverestore.cpp \
    ../../game/shared/physics_shared.cpp \
    ../../game/shared/point_bonusmaps_accessor.cpp \
    ../../game/shared/point_posecontroller.cpp \
    ../../game/shared/precache_register.cpp \
    ../../game/shared/predictableid.cpp \
    ../../game/shared/props_shared.cpp \
    ../../game/shared/querycache.cpp \
    ../../game/shared/ragdoll_shared.cpp \
    ../../game/shared/rope_helpers.cpp \
    ../../game/shared/saverestore.cpp \
    ../../game/shared/SceneCache.cpp \
    ../../game/shared/sceneentity_shared.cpp \
    ../../game/shared/script_intro_shared.cpp \
    ../../game/shared/sequence_Transitioner.cpp \
    ../../game/shared/sheetsimulator.cpp \
    ../../game/shared/simtimer.cpp \
    ../../game/shared/singleplay_gamerules.cpp \
    ../../game/shared/SoundEmitterSystem.cpp \
    ../../game/shared/soundenvelope.cpp \
    ../../game/shared/Sprite.cpp \
    ../../game/shared/SpriteTrail.cpp \
    ../../game/shared/studio_shared.cpp \
    ../../game/shared/takedamageinfo.cpp \
    ../../game/shared/teamplay_gamerules.cpp \
    ../../game/shared/test_ehandle.cpp \
    ../../game/shared/usercmd.cpp \
    ../../game/shared/usermessages.cpp \
    ../../game/shared/util_shared.cpp \
    ../../game/shared/vehicle_viewblend_shared.cpp \
    ../../game/shared/voice_gamemgr.cpp \
    ../../game/shared/weapon_parse.cpp \
    ../../game/shared/weapon_parse_default.cpp \
    ../../game/shared/weapon_proficiency.cpp \
    ../../public/bone_setup.cpp \
    ../../public/collisionutils.cpp \
    ../../public/dt_send.cpp \
    ../../public/dt_utlvector_common.cpp \
    ../../public/dt_utlvector_send.cpp \
    ../../public/editor_sendcommand.cpp \
    ../../public/filesystem_helpers.cpp \
    ../../public/haptics/haptic_msgs.cpp \
    ../../public/interpolatortypes.cpp \
    ../../public/keyframe/keyframe.cpp \
    ../../public/map_utils.cpp \
    ../../public/networkvar.cpp \
    ../../public/registry.cpp \
    ../../public/rope_physics.cpp \
    ../../public/scratchpad3d.cpp \
    ../../public/ScratchPadUtils.cpp \
    ../../public/server_class.cpp \
    ../../public/simple_physics.cpp \
    ../../public/SoundParametersInternal.cpp \
    ../../public/stringregistry.cpp \
    ../../public/studio.cpp \
    ../../public/tier0/memoverride.cpp \
    ai_activity.cpp \
    ai_baseactor.cpp \
    ai_basehumanoid.cpp \
    ai_basenpc.cpp \
    ai_basenpc_flyer.cpp \
    ai_basenpc_flyer_new.cpp \
    ai_basenpc_movement.cpp \
    ai_basenpc_physicsflyer.cpp \
    ai_basenpc_schedule.cpp \
    ai_basenpc_squad.cpp \
    ai_behavior.cpp \
    ai_behavior_assault.cpp \
    ai_behavior_fear.cpp \
    ai_behavior_follow.cpp \
    ai_behavior_lead.cpp \
    ai_behavior_rappel.cpp \
    ai_behavior_standoff.cpp \
    ai_blended_movement.cpp \
    ai_concommands.cpp \
    ai_condition.cpp \
    AI_Criteria.cpp \
    ai_default.cpp \
    ai_dynamiclink.cpp \
    ai_event.cpp \
    ai_eventresponse.cpp \
    ai_goalentity.cpp \
    ai_hint.cpp \
    ai_hull.cpp \
    ai_initutils.cpp \
    AI_Interest_Target.cpp \
    ai_link.cpp \
    ai_localnavigator.cpp \
    ai_looktarget.cpp \
    ai_memory.cpp \
    ai_motor.cpp \
    ai_moveprobe.cpp \
    ai_moveshoot.cpp \
    ai_movesolver.cpp \
    ai_namespaces.cpp \
    ai_navigator.cpp \
    ai_network.cpp \
    ai_networkmanager.cpp \
    ai_node.cpp \
    ai_pathfinder.cpp \
    ai_planesolver.cpp \
    ai_playerally.cpp \
    ai_relationship.cpp \
    AI_ResponseSystem.cpp \
    ai_route.cpp \
    ai_saverestore.cpp \
    ai_schedule.cpp \
    ai_scriptconditions.cpp \
    ai_senses.cpp \
    ai_sentence.cpp \
    ai_speech.cpp \
    ai_speechfilter.cpp \
    ai_squad.cpp \
    ai_squadslot.cpp \
    ai_tacticalservices.cpp \
    ai_task.cpp \
    ai_trackpather.cpp \
    ai_utils.cpp \
    ai_waypoint.cpp \
    baseanimating.cpp \
    BaseAnimatingOverlay.cpp \
    basebludgeonweapon.cpp \
    basecombatcharacter.cpp \
    basecombatweapon.cpp \
    baseentity.cpp \
    baseflex.cpp \
    basegrenade_concussion.cpp \
    basegrenade_contact.cpp \
    basegrenade_timed.cpp \
    basemultiplayerplayer.cpp \
    basetempentity.cpp \
    baseviewmodel.cpp \
    base_gameinterface.cpp \
    base_transmit_proxy.cpp \
    bitstring.cpp \
    bmodels.cpp \
    buttons.cpp \
    cbase.cpp \
    client.cpp \
    colorcorrection.cpp \
    colorcorrectionvolume.cpp \
    CommentarySystem.cpp \
    controlentities.cpp \
    cplane.cpp \
    CRagdollMagnet.cpp \
    damagemodifier.cpp \
    doors.cpp \
    dynamiclight.cpp \
    effects.cpp \
    EffectsServer.cpp \
    entityblocker.cpp \
    EntityDissolve.cpp \
    EntityFlame.cpp \
    entitylist.cpp \
    EntityParticleTrail.cpp \
    entity_tools_server.cpp \
    EnvBeam.cpp \
    EnvFade.cpp \
    EnvHudHint.cpp \
    EnvLaser.cpp \
    EnvMessage.cpp \
    envmicrophone.cpp \
    EnvShake.cpp \
    EnvSpark.cpp \
    env_debughistory.cpp \
    env_effectsscript.cpp \
    env_entity_maker.cpp \
    env_particlescript.cpp \
    env_player_surface_trigger.cpp \
    env_projectedtexture.cpp \
    env_screenoverlay.cpp \
    env_texturetoggle.cpp \
    env_tonemap_controller.cpp \
    env_zoom.cpp \
    EventLog.cpp \
    event_tempentity_tester.cpp \
    explode.cpp \
    filters.cpp \
    fire.cpp \
    fire_smoke.cpp \
    fish.cpp \
    fogcontroller.cpp \
    fourwheelvehiclephysics.cpp \
    func_areaportal.cpp \
    func_areaportalbase.cpp \
    func_areaportalwindow.cpp \
    func_break.cpp \
    func_breakablesurf.cpp \
    func_dust.cpp \
    func_ladder_endpoint.cpp \
    func_lod.cpp \
    func_movelinear.cpp \
    func_occluder.cpp \
    func_reflective_glass.cpp \
    func_smokevolume.cpp \
    game.cpp \
    gamedll_replay.cpp \
    gamehandle.cpp \
    gameinterface.cpp \
    GameStats_BasicStatsFunctions.cpp \
    gametrace_dll.cpp \
    gameweaponmanager.cpp \
    game_ui.cpp \
    genericactor.cpp \
    genericmonster.cpp \
    gib.cpp \
    globals.cpp \
    globalstate.cpp \
    grenadethrown.cpp \
    guntarget.cpp \
    hierarchy.cpp \
    hl2/ai_allymanager.cpp \
    hl2/ai_behavior_actbusy.cpp \
    hl2/ai_behavior_functank.cpp \
    hl2/ai_behavior_holster.cpp \
    hl2/ai_behavior_operator.cpp \
    hl2/ai_behavior_police.cpp \
    hl2/ai_goal_police.cpp \
    hl2/ai_spotlight.cpp \
    hl2/antlion_dust.cpp \
    hl2/antlion_maker.cpp \
    hl2/ar2_explosion.cpp \
    hl2/basehlcombatweapon.cpp \
    hl2/cbasehelicopter.cpp \
    hl2/cbasespriteprojectile.cpp \
    hl2/citadel_effects.cpp \
    hl2/combine_mine.cpp \
    hl2/env_alyxemp.cpp \
    hl2/env_headcrabcanister.cpp \
    hl2/env_speaker.cpp \
    hl2/env_starfield.cpp \
    hl2/Func_Monitor.cpp \
    hl2/func_recharge.cpp \
    hl2/func_tank.cpp \
    hl2/grenade_ar2.cpp \
    hl2/grenade_beam.cpp \
    hl2/grenade_bugbait.cpp \
    hl2/grenade_frag.cpp \
    hl2/grenade_homer.cpp \
    hl2/grenade_pathfollower.cpp \
    hl2/hl2_ai_network.cpp \
    hl2/hl2_client.cpp \
    hl2/hl2_eventlog.cpp \
    hl2/hl2_gamestats.cpp \
    hl2/hl2_player.cpp \
    hl2/hl2_playerlocaldata.cpp \
    hl2/hl2_triggers.cpp \
    hl2/hl_playermove.cpp \
    hl2/info_darknessmode_lightsource.cpp \
    hl2/info_teleporter_countdown.cpp \
    hl2/item_ammo.cpp \
    hl2/item_battery.cpp \
    hl2/item_dynamic_resupply.cpp \
    hl2/item_healthkit.cpp \
    hl2/item_itemcrate.cpp \
    hl2/item_suit.cpp \
    hl2/look_door.cpp \
    hl2/monster_dummy.cpp \
    hl2/npc_alyx.cpp \
    hl2/npc_antlion.cpp \
    hl2/npc_antlionguard.cpp \
    hl2/npc_apcdriver.cpp \
    hl2/npc_attackchopper.cpp \
    hl2/npc_barnacle.cpp \
    hl2/npc_barney.cpp \
    hl2/npc_basescanner.cpp \
    hl2/npc_BaseZombie.cpp \
    hl2/npc_blob.cpp \
    hl2/npc_breen.cpp \
    hl2/npc_bullseye.cpp \
    hl2/npc_citizen17.cpp \
    hl2/npc_combine.cpp \
    hl2/npc_combinecamera.cpp \
    hl2/npc_combinedropship.cpp \
    hl2/npc_combinegunship.cpp \
    hl2/npc_combines.cpp \
    hl2/npc_cranedriver.cpp \
    hl2/npc_crow.cpp \
    hl2/npc_dog.cpp \
    hl2/npc_eli.cpp \
    hl2/npc_enemyfinder.cpp \
    hl2/npc_fastzombie.cpp \
    hl2/npc_fisherman.cpp \
    hl2/npc_gman.cpp \
    hl2/npc_headcrab.cpp \
    hl2/npc_ichthyosaur.cpp \
    hl2/npc_kleiner.cpp \
    hl2/npc_launcher.cpp \
    hl2/npc_manhack.cpp \
    hl2/npc_metropolice.cpp \
    hl2/npc_missiledefense.cpp \
    hl2/npc_monk.cpp \
    hl2/npc_mossman.cpp \
    hl2/npc_playercompanion.cpp \
    hl2/npc_PoisonZombie.cpp \
    hl2/npc_rollermine.cpp \
    hl2/npc_scanner.cpp \
    hl2/npc_stalker.cpp \
    hl2/npc_strider.cpp \
    hl2/npc_turret_ceiling.cpp \
    hl2/npc_turret_floor.cpp \
    hl2/npc_turret_ground.cpp \
    hl2/npc_vortigaunt_episodic.cpp \
    hl2/npc_zombie.cpp \
    hl2/point_apc_controller.cpp \
    hl2/prop_combine_ball.cpp \
    hl2/prop_thumper.cpp \
    hl2/proto_sniper.cpp \
    hl2/rotorwash.cpp \
    hl2/script_intro.cpp \
    hl2/te_gaussexplosion.cpp \
    hl2/vehicle_airboat.cpp \
    hl2/vehicle_apc.cpp \
    hl2/vehicle_cannon.cpp \
    hl2/vehicle_crane.cpp \
    hl2/vehicle_jeep.cpp \
    hl2/vehicle_prisoner_pod.cpp \
    hl2/vehicle_viewcontroller.cpp \
    hl2/weapon_357.cpp \
    hl2/weapon_alyxgun.cpp \
    hl2/weapon_annabelle.cpp \
    hl2/weapon_ar2.cpp \
    hl2/weapon_bugbait.cpp \
    hl2/weapon_cguard.cpp \
    hl2/weapon_citizenpackage.cpp \
    hl2/weapon_crossbow.cpp \
    hl2/weapon_crowbar.cpp \
    hl2/weapon_flaregun.cpp \
    hl2/weapon_frag.cpp \
    hl2/weapon_physcannon.cpp \
    hl2/weapon_pistol.cpp \
    hl2/weapon_rpg.cpp \
    hl2/weapon_shotgun.cpp \
    hl2/weapon_smg1.cpp \
    hl2/weapon_stunstick.cpp \
    hltvdirector.cpp \
    h_ai.cpp \
    h_cycler.cpp \
    h_export.cpp \
    info_camera_link.cpp \
    info_overlay_accessor.cpp \
    init_factory.cpp \
    intermission.cpp \
    item_world.cpp \
    lightglow.cpp \
    lights.cpp \
    logicauto.cpp \
    logicentities.cpp \
    logicrelay.cpp \
    logic_achievement.cpp \
    logic_measure_movement.cpp \
    logic_navigation.cpp \
    mapentities.cpp \
    maprules.cpp \
    MaterialModifyControl.cpp \
    message_entity.cpp \
    modelentities.cpp \
    monstermaker.cpp \
    movehelper_server.cpp \
    movement.cpp \
    movie_explosion.cpp \
    ndebugoverlay.cpp \
    npc_talker.cpp \
    npc_vehicledriver.cpp \
    particle_fire.cpp \
    particle_light.cpp \
    particle_smokegrenade.cpp \
    particle_system.cpp \
    pathcorner.cpp \
    pathtrack.cpp \
    physconstraint.cpp \
    physics.cpp \
    physics_bone_follower.cpp \
    physics_cannister.cpp \
    physics_fx.cpp \
    physics_impact_damage.cpp \
    physics_main.cpp \
    physics_npc_solver.cpp \
    physics_prop_ragdoll.cpp \
    physobj.cpp \
    phys_controller.cpp \
    plasma.cpp \
    player.cpp \
    playerinfomanager.cpp \
    playerlocaldata.cpp \
    player_command.cpp \
    player_lagcompensation.cpp \
    player_pickup.cpp \
    player_resource.cpp \
    plugin_check.cpp \
    pointanglesensor.cpp \
    PointAngularVelocitySensor.cpp \
    pointhurt.cpp \
    pointteleport.cpp \
    point_camera.cpp \
    point_devshot_camera.cpp \
    point_playermoveconstraint.cpp \
    point_spotlight.cpp \
    point_template.cpp \
    props.cpp \
    RagdollBoogie.cpp \
    ragdoll_manager.cpp \
    recipientfilter.cpp \
    rope.cpp \
    saverestore_gamedll.cpp \
    sceneentity.cpp \
    scratchpad_gamedll_helpers.cpp \
    scripted.cpp \
    scriptedtarget.cpp \
    sendproxy.cpp \
    ServerNetworkProperty.cpp \
    shadowcontrol.cpp \
    SkyCamera.cpp \
    slideshow_display.cpp \
    smokestack.cpp \
    smoke_trail.cpp \
    sound.cpp \
    soundent.cpp \
    soundscape.cpp \
    soundscape_system.cpp \
    spotlightend.cpp \
    sprite_perfmonitor.cpp \
    stdafx.cpp \
    steamjet.cpp \
    subs.cpp \
    sun.cpp \
    tactical_mission.cpp \
    tanktrain.cpp \
    te.cpp \
    team.cpp \
    team_spawnpoint.cpp \
    TemplateEntities.cpp \
    tempmonster.cpp \
    tesla.cpp \
    testfunctions.cpp \
    testtraceline.cpp \
    test_proxytoggle.cpp \
    test_stressentities.cpp \
    textstatsmgr.cpp \
    te_armorricochet.cpp \
    te_basebeam.cpp \
    te_beamentpoint.cpp \
    te_beaments.cpp \
    te_beamfollow.cpp \
    te_beamlaser.cpp \
    te_beampoints.cpp \
    te_beamring.cpp \
    te_beamringpoint.cpp \
    te_beamspline.cpp \
    te_bloodsprite.cpp \
    te_bloodstream.cpp \
    te_breakmodel.cpp \
    te_bspdecal.cpp \
    te_bubbles.cpp \
    te_bubbletrail.cpp \
    te_clientprojectile.cpp \
    te_decal.cpp \
    te_dynamiclight.cpp \
    te_effect_dispatch.cpp \
    te_energysplash.cpp \
    te_explosion.cpp \
    te_fizz.cpp \
    te_footprintdecal.cpp \
    te_glassshatter.cpp \
    te_glowsprite.cpp \
    te_impact.cpp \
    te_killplayerattachments.cpp \
    te_largefunnel.cpp \
    te_muzzleflash.cpp \
    te_particlesystem.cpp \
    te_physicsprop.cpp \
    te_playerdecal.cpp \
    te_projecteddecal.cpp \
    te_showline.cpp \
    te_smoke.cpp \
    te_sparks.cpp \
    te_sprite.cpp \
    te_spritespray.cpp \
    te_worlddecal.cpp \
    timedeventmgr.cpp \
    toolframework_server.cpp \
    trains.cpp \
    triggers.cpp \
    util.cpp \
    variant_t.cpp \
    vehicle_base.cpp \
    vehicle_baseserver.cpp \
    vehicle_choreo_generic.cpp \
    vguiscreen.cpp \
    waterbullet.cpp \
    WaterLODControl.cpp \
    wcedit.cpp \
    weapon_cubemap.cpp \
    weight_button.cpp \
    world.cpp \


LIBFILES = \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/choreoobjects.a \
    ../../lib/public/linux32/dmxloader.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/particles.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../lib/public/linux32/choreoobjects.a \
    ../../lib/public/linux32/dmxloader.a \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/particles.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/language.P
endif

$(OBJ_DIR)/language.o : $(abspath ../../common/language.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/randoverride.P
endif

$(OBJ_DIR)/randoverride.o : $(abspath ../../common/randoverride.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamid.P
endif

$(OBJ_DIR)/steamid.o : $(abspath ../../common/steamid.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/serverbenchmark_base.P
endif

$(OBJ_DIR)/serverbenchmark_base.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/serverbenchmark_base.o : $(abspath ../../game/server/serverbenchmark_base.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vote_controller.P
endif

$(OBJ_DIR)/vote_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vote_controller.o : $(abspath ../../game/server/vote_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievementmgr.P
endif

$(OBJ_DIR)/achievementmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievementmgr.o : $(abspath ../../game/shared/achievementmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievements_hlx.P
endif

$(OBJ_DIR)/achievements_hlx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievements_hlx.o : $(abspath ../../game/shared/achievements_hlx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievement_saverestore.P
endif

$(OBJ_DIR)/achievement_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievement_saverestore.o : $(abspath ../../game/shared/achievement_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/activitylist.P
endif

$(OBJ_DIR)/activitylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/activitylist.o : $(abspath ../../game/shared/activitylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ammodef.P
endif

$(OBJ_DIR)/ammodef.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ammodef.o : $(abspath ../../game/shared/ammodef.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animation.P
endif

$(OBJ_DIR)/animation.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animation.o : $(abspath ../../game/shared/animation.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseachievement.P
endif

$(OBJ_DIR)/baseachievement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseachievement.o : $(abspath ../../game/shared/baseachievement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatcharacter_shared.P
endif

$(OBJ_DIR)/basecombatcharacter_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatcharacter_shared.o : $(abspath ../../game/shared/basecombatcharacter_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatweapon_shared.P
endif

$(OBJ_DIR)/basecombatweapon_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatweapon_shared.o : $(abspath ../../game/shared/basecombatweapon_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseentity_shared.P
endif

$(OBJ_DIR)/baseentity_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseentity_shared.o : $(abspath ../../game/shared/baseentity_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_shared.P
endif

$(OBJ_DIR)/basegrenade_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_shared.o : $(abspath ../../game/shared/basegrenade_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseparticleentity.P
endif

$(OBJ_DIR)/baseparticleentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseparticleentity.o : $(abspath ../../game/shared/baseparticleentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseplayer_shared.P
endif

$(OBJ_DIR)/baseplayer_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseplayer_shared.o : $(abspath ../../game/shared/baseplayer_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseprojectile.P
endif

$(OBJ_DIR)/baseprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseprojectile.o : $(abspath ../../game/shared/baseprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseviewmodel_shared.P
endif

$(OBJ_DIR)/baseviewmodel_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseviewmodel_shared.o : $(abspath ../../game/shared/baseviewmodel_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_playeranimstate.P
endif

$(OBJ_DIR)/base_playeranimstate.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/base_playeranimstate.o : $(abspath ../../game/shared/base_playeranimstate.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/beam_shared.P
endif

$(OBJ_DIR)/beam_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/beam_shared.o : $(abspath ../../game/shared/beam_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionproperty.P
endif

$(OBJ_DIR)/collisionproperty.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/collisionproperty.o : $(abspath ../../game/shared/collisionproperty.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/death_pose.P
endif

$(OBJ_DIR)/death_pose.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/death_pose.o : $(abspath ../../game/shared/death_pose.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugoverlay_shared.P
endif

$(OBJ_DIR)/debugoverlay_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/debugoverlay_shared.o : $(abspath ../../game/shared/debugoverlay_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/decals.P
endif

$(OBJ_DIR)/decals.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/decals.o : $(abspath ../../game/shared/decals.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/effect_dispatch_data.P
endif

$(OBJ_DIR)/effect_dispatch_data.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/effect_dispatch_data.o : $(abspath ../../game/shared/effect_dispatch_data.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ehandle.P
endif

$(OBJ_DIR)/ehandle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ehandle.o : $(abspath ../../game/shared/ehandle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entitylist_base.P
endif

$(OBJ_DIR)/entitylist_base.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entitylist_base.o : $(abspath ../../game/shared/entitylist_base.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityParticleTrail_Shared.P
endif

$(OBJ_DIR)/EntityParticleTrail_Shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityParticleTrail_Shared.o : $(abspath ../../game/shared/EntityParticleTrail_Shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_detail_controller.P
endif

$(OBJ_DIR)/env_detail_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_detail_controller.o : $(abspath ../../game/shared/env_detail_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_wind_shared.P
endif

$(OBJ_DIR)/env_wind_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_wind_shared.o : $(abspath ../../game/shared/env_wind_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eventlist.P
endif

$(OBJ_DIR)/eventlist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/eventlist.o : $(abspath ../../game/shared/eventlist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_ladder.P
endif

$(OBJ_DIR)/func_ladder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_ladder.o : $(abspath ../../game/shared/func_ladder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamemovement.P
endif

$(OBJ_DIR)/gamemovement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamemovement.o : $(abspath ../../game/shared/gamemovement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamerules.P
endif

$(OBJ_DIR)/gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamerules.o : $(abspath ../../game/shared/gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamerules_register.P
endif

$(OBJ_DIR)/gamerules_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamerules_register.o : $(abspath ../../game/shared/gamerules_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameStats.P
endif

$(OBJ_DIR)/GameStats.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/GameStats.o : $(abspath ../../game/shared/GameStats.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamestringpool.P
endif

$(OBJ_DIR)/gamestringpool.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamestringpool.o : $(abspath ../../game/shared/gamestringpool.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamevars_shared.P
endif

$(OBJ_DIR)/gamevars_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamevars_shared.o : $(abspath ../../game/shared/gamevars_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hintmessage.P
endif

$(OBJ_DIR)/hintmessage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hintmessage.o : $(abspath ../../game/shared/hintmessage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hintsystem.P
endif

$(OBJ_DIR)/hintsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hintsystem.o : $(abspath ../../game/shared/hintsystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievements_hl2.P
endif

$(OBJ_DIR)/achievements_hl2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievements_hl2.o : $(abspath ../../game/shared/hl2/achievements_hl2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basehlcombatweapon_shared.P
endif

$(OBJ_DIR)/basehlcombatweapon_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basehlcombatweapon_shared.o : $(abspath ../../game/shared/hl2/basehlcombatweapon_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_headcrabcanister_shared.P
endif

$(OBJ_DIR)/env_headcrabcanister_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_headcrabcanister_shared.o : $(abspath ../../game/shared/hl2/env_headcrabcanister_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_gamerules.P
endif

$(OBJ_DIR)/hl2_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_gamerules.o : $(abspath ../../game/shared/hl2/hl2_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_usermessages.P
endif

$(OBJ_DIR)/hl2_usermessages.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_usermessages.o : $(abspath ../../game/shared/hl2/hl2_usermessages.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_gamemovement.P
endif

$(OBJ_DIR)/hl_gamemovement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_gamemovement.o : $(abspath ../../game/shared/hl2/hl_gamemovement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/survival_gamerules.P
endif

$(OBJ_DIR)/survival_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/survival_gamerules.o : $(abspath ../../game/shared/hl2/survival_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/igamesystem.P
endif

$(OBJ_DIR)/igamesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/igamesystem.o : $(abspath ../../game/shared/igamesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interval.P
endif

$(OBJ_DIR)/interval.o : $(abspath ../../game/shared/interval.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mapentities_shared.P
endif

$(OBJ_DIR)/mapentities_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mapentities_shared.o : $(abspath ../../game/shared/mapentities_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ModelSoundsCache.P
endif

$(OBJ_DIR)/ModelSoundsCache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ModelSoundsCache.o : $(abspath ../../game/shared/ModelSoundsCache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movevars_shared.P
endif

$(OBJ_DIR)/movevars_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movevars_shared.o : $(abspath ../../game/shared/movevars_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mp_shareddefs.P
endif

$(OBJ_DIR)/mp_shareddefs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mp_shareddefs.o : $(abspath ../../game/shared/mp_shareddefs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/multiplay_gamerules.P
endif

$(OBJ_DIR)/multiplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/multiplay_gamerules.o : $(abspath ../../game/shared/multiplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/obstacle_pushaway.P
endif

$(OBJ_DIR)/obstacle_pushaway.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/obstacle_pushaway.o : $(abspath ../../game/shared/obstacle_pushaway.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlesystemquery.P
endif

$(OBJ_DIR)/particlesystemquery.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particlesystemquery.o : $(abspath ../../game/shared/particlesystemquery.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_parse.P
endif

$(OBJ_DIR)/particle_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_parse.o : $(abspath ../../game/shared/particle_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_main_shared.P
endif

$(OBJ_DIR)/physics_main_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_main_shared.o : $(abspath ../../game/shared/physics_main_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_saverestore.P
endif

$(OBJ_DIR)/physics_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_saverestore.o : $(abspath ../../game/shared/physics_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_shared.P
endif

$(OBJ_DIR)/physics_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_shared.o : $(abspath ../../game/shared/physics_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_bonusmaps_accessor.P
endif

$(OBJ_DIR)/point_bonusmaps_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_bonusmaps_accessor.o : $(abspath ../../game/shared/point_bonusmaps_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_posecontroller.P
endif

$(OBJ_DIR)/point_posecontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_posecontroller.o : $(abspath ../../game/shared/point_posecontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/precache_register.P
endif

$(OBJ_DIR)/precache_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/precache_register.o : $(abspath ../../game/shared/precache_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/predictableid.P
endif

$(OBJ_DIR)/predictableid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/predictableid.o : $(abspath ../../game/shared/predictableid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/props_shared.P
endif

$(OBJ_DIR)/props_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/props_shared.o : $(abspath ../../game/shared/props_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/querycache.P
endif

$(OBJ_DIR)/querycache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/querycache.o : $(abspath ../../game/shared/querycache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll_shared.P
endif

$(OBJ_DIR)/ragdoll_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ragdoll_shared.o : $(abspath ../../game/shared/ragdoll_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope_helpers.P
endif

$(OBJ_DIR)/rope_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/rope_helpers.o : $(abspath ../../game/shared/rope_helpers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/saverestore.P
endif

$(OBJ_DIR)/saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/saverestore.o : $(abspath ../../game/shared/saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SceneCache.P
endif

$(OBJ_DIR)/SceneCache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SceneCache.o : $(abspath ../../game/shared/SceneCache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sceneentity_shared.P
endif

$(OBJ_DIR)/sceneentity_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sceneentity_shared.o : $(abspath ../../game/shared/sceneentity_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/script_intro_shared.P
endif

$(OBJ_DIR)/script_intro_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/script_intro_shared.o : $(abspath ../../game/shared/script_intro_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sequence_Transitioner.P
endif

$(OBJ_DIR)/sequence_Transitioner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sequence_Transitioner.o : $(abspath ../../game/shared/sequence_Transitioner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sheetsimulator.P
endif

$(OBJ_DIR)/sheetsimulator.o : $(abspath ../../game/shared/sheetsimulator.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simtimer.P
endif

$(OBJ_DIR)/simtimer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/simtimer.o : $(abspath ../../game/shared/simtimer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/singleplay_gamerules.P
endif

$(OBJ_DIR)/singleplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/singleplay_gamerules.o : $(abspath ../../game/shared/singleplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SoundEmitterSystem.P
endif

$(OBJ_DIR)/SoundEmitterSystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SoundEmitterSystem.o : $(abspath ../../game/shared/SoundEmitterSystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundenvelope.P
endif

$(OBJ_DIR)/soundenvelope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundenvelope.o : $(abspath ../../game/shared/soundenvelope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Sprite.P
endif

$(OBJ_DIR)/Sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/Sprite.o : $(abspath ../../game/shared/Sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SpriteTrail.P
endif

$(OBJ_DIR)/SpriteTrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SpriteTrail.o : $(abspath ../../game/shared/SpriteTrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio_shared.P
endif

$(OBJ_DIR)/studio_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/studio_shared.o : $(abspath ../../game/shared/studio_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/takedamageinfo.P
endif

$(OBJ_DIR)/takedamageinfo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/takedamageinfo.o : $(abspath ../../game/shared/takedamageinfo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teamplay_gamerules.P
endif

$(OBJ_DIR)/teamplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/teamplay_gamerules.o : $(abspath ../../game/shared/teamplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/test_ehandle.P
endif

$(OBJ_DIR)/test_ehandle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/test_ehandle.o : $(abspath ../../game/shared/test_ehandle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/usercmd.P
endif

$(OBJ_DIR)/usercmd.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/usercmd.o : $(abspath ../../game/shared/usercmd.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/usermessages.P
endif

$(OBJ_DIR)/usermessages.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/usermessages.o : $(abspath ../../game/shared/usermessages.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/util_shared.P
endif

$(OBJ_DIR)/util_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/util_shared.o : $(abspath ../../game/shared/util_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_viewblend_shared.P
endif

$(OBJ_DIR)/vehicle_viewblend_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_viewblend_shared.o : $(abspath ../../game/shared/vehicle_viewblend_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_gamemgr.P
endif

$(OBJ_DIR)/voice_gamemgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/voice_gamemgr.o : $(abspath ../../game/shared/voice_gamemgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_parse.P
endif

$(OBJ_DIR)/weapon_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_parse.o : $(abspath ../../game/shared/weapon_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_parse_default.P
endif

$(OBJ_DIR)/weapon_parse_default.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_parse_default.o : $(abspath ../../game/shared/weapon_parse_default.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_proficiency.P
endif

$(OBJ_DIR)/weapon_proficiency.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_proficiency.o : $(abspath ../../game/shared/weapon_proficiency.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bone_setup.P
endif

$(OBJ_DIR)/bone_setup.o : $(abspath ../../public/bone_setup.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionutils.P
endif

$(OBJ_DIR)/collisionutils.o : $(abspath ../../public/collisionutils.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_send.P
endif

$(OBJ_DIR)/dt_send.o : $(abspath ../../public/dt_send.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_common.P
endif

$(OBJ_DIR)/dt_utlvector_common.o : $(abspath ../../public/dt_utlvector_common.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_send.P
endif

$(OBJ_DIR)/dt_utlvector_send.o : $(abspath ../../public/dt_utlvector_send.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/editor_sendcommand.P
endif

$(OBJ_DIR)/editor_sendcommand.o : $(abspath ../../public/editor_sendcommand.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../../public/filesystem_helpers.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/haptic_msgs.P
endif

$(OBJ_DIR)/haptic_msgs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/haptic_msgs.o : $(abspath ../../public/haptics/haptic_msgs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interpolatortypes.P
endif

$(OBJ_DIR)/interpolatortypes.o : $(abspath ../../public/interpolatortypes.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/keyframe.P
endif

$(OBJ_DIR)/keyframe.o : $(abspath ../../public/keyframe/keyframe.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/map_utils.P
endif

$(OBJ_DIR)/map_utils.o : $(abspath ../../public/map_utils.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkvar.P
endif

$(OBJ_DIR)/networkvar.o : $(abspath ../../public/networkvar.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/registry.P
endif

$(OBJ_DIR)/registry.o : $(abspath ../../public/registry.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope_physics.P
endif

$(OBJ_DIR)/rope_physics.o : $(abspath ../../public/rope_physics.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scratchpad3d.P
endif

$(OBJ_DIR)/scratchpad3d.o : $(abspath ../../public/scratchpad3d.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScratchPadUtils.P
endif

$(OBJ_DIR)/ScratchPadUtils.o : $(abspath ../../public/ScratchPadUtils.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/server_class.P
endif

$(OBJ_DIR)/server_class.o : $(abspath ../../public/server_class.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simple_physics.P
endif

$(OBJ_DIR)/simple_physics.o : $(abspath ../../public/simple_physics.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SoundParametersInternal.P
endif

$(OBJ_DIR)/SoundParametersInternal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SoundParametersInternal.o : $(abspath ../../public/SoundParametersInternal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stringregistry.P
endif

$(OBJ_DIR)/stringregistry.o : $(abspath ../../public/stringregistry.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio.P
endif

$(OBJ_DIR)/studio.o : $(abspath ../../public/studio.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_activity.P
endif

$(OBJ_DIR)/ai_activity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_activity.o : $(abspath ai_activity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_baseactor.P
endif

$(OBJ_DIR)/ai_baseactor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_baseactor.o : $(abspath ai_baseactor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basehumanoid.P
endif

$(OBJ_DIR)/ai_basehumanoid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basehumanoid.o : $(abspath ai_basehumanoid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc.P
endif

$(OBJ_DIR)/ai_basenpc.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc.o : $(abspath ai_basenpc.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_flyer.P
endif

$(OBJ_DIR)/ai_basenpc_flyer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_flyer.o : $(abspath ai_basenpc_flyer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_flyer_new.P
endif

$(OBJ_DIR)/ai_basenpc_flyer_new.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_flyer_new.o : $(abspath ai_basenpc_flyer_new.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_movement.P
endif

$(OBJ_DIR)/ai_basenpc_movement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_movement.o : $(abspath ai_basenpc_movement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_physicsflyer.P
endif

$(OBJ_DIR)/ai_basenpc_physicsflyer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_physicsflyer.o : $(abspath ai_basenpc_physicsflyer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_schedule.P
endif

$(OBJ_DIR)/ai_basenpc_schedule.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_schedule.o : $(abspath ai_basenpc_schedule.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_squad.P
endif

$(OBJ_DIR)/ai_basenpc_squad.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_squad.o : $(abspath ai_basenpc_squad.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior.P
endif

$(OBJ_DIR)/ai_behavior.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior.o : $(abspath ai_behavior.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_assault.P
endif

$(OBJ_DIR)/ai_behavior_assault.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_assault.o : $(abspath ai_behavior_assault.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_fear.P
endif

$(OBJ_DIR)/ai_behavior_fear.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_fear.o : $(abspath ai_behavior_fear.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_follow.P
endif

$(OBJ_DIR)/ai_behavior_follow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_follow.o : $(abspath ai_behavior_follow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_lead.P
endif

$(OBJ_DIR)/ai_behavior_lead.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_lead.o : $(abspath ai_behavior_lead.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_rappel.P
endif

$(OBJ_DIR)/ai_behavior_rappel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_rappel.o : $(abspath ai_behavior_rappel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_standoff.P
endif

$(OBJ_DIR)/ai_behavior_standoff.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_standoff.o : $(abspath ai_behavior_standoff.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_blended_movement.P
endif

$(OBJ_DIR)/ai_blended_movement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_blended_movement.o : $(abspath ai_blended_movement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_concommands.P
endif

$(OBJ_DIR)/ai_concommands.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_concommands.o : $(abspath ai_concommands.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_condition.P
endif

$(OBJ_DIR)/ai_condition.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_condition.o : $(abspath ai_condition.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AI_Criteria.P
endif

$(OBJ_DIR)/AI_Criteria.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/AI_Criteria.o : $(abspath AI_Criteria.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_default.P
endif

$(OBJ_DIR)/ai_default.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_default.o : $(abspath ai_default.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_dynamiclink.P
endif

$(OBJ_DIR)/ai_dynamiclink.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_dynamiclink.o : $(abspath ai_dynamiclink.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_event.P
endif

$(OBJ_DIR)/ai_event.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_event.o : $(abspath ai_event.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_eventresponse.P
endif

$(OBJ_DIR)/ai_eventresponse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_eventresponse.o : $(abspath ai_eventresponse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_goalentity.P
endif

$(OBJ_DIR)/ai_goalentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_goalentity.o : $(abspath ai_goalentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_hint.P
endif

$(OBJ_DIR)/ai_hint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_hint.o : $(abspath ai_hint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_hull.P
endif

$(OBJ_DIR)/ai_hull.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_hull.o : $(abspath ai_hull.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_initutils.P
endif

$(OBJ_DIR)/ai_initutils.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_initutils.o : $(abspath ai_initutils.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AI_Interest_Target.P
endif

$(OBJ_DIR)/AI_Interest_Target.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/AI_Interest_Target.o : $(abspath AI_Interest_Target.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_link.P
endif

$(OBJ_DIR)/ai_link.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_link.o : $(abspath ai_link.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_localnavigator.P
endif

$(OBJ_DIR)/ai_localnavigator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_localnavigator.o : $(abspath ai_localnavigator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_looktarget.P
endif

$(OBJ_DIR)/ai_looktarget.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_looktarget.o : $(abspath ai_looktarget.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_memory.P
endif

$(OBJ_DIR)/ai_memory.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_memory.o : $(abspath ai_memory.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_motor.P
endif

$(OBJ_DIR)/ai_motor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_motor.o : $(abspath ai_motor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_moveprobe.P
endif

$(OBJ_DIR)/ai_moveprobe.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_moveprobe.o : $(abspath ai_moveprobe.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_moveshoot.P
endif

$(OBJ_DIR)/ai_moveshoot.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_moveshoot.o : $(abspath ai_moveshoot.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_movesolver.P
endif

$(OBJ_DIR)/ai_movesolver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_movesolver.o : $(abspath ai_movesolver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_namespaces.P
endif

$(OBJ_DIR)/ai_namespaces.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_namespaces.o : $(abspath ai_namespaces.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_navigator.P
endif

$(OBJ_DIR)/ai_navigator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_navigator.o : $(abspath ai_navigator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_network.P
endif

$(OBJ_DIR)/ai_network.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_network.o : $(abspath ai_network.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_networkmanager.P
endif

$(OBJ_DIR)/ai_networkmanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_networkmanager.o : $(abspath ai_networkmanager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_node.P
endif

$(OBJ_DIR)/ai_node.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_node.o : $(abspath ai_node.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_pathfinder.P
endif

$(OBJ_DIR)/ai_pathfinder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_pathfinder.o : $(abspath ai_pathfinder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_planesolver.P
endif

$(OBJ_DIR)/ai_planesolver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_planesolver.o : $(abspath ai_planesolver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_playerally.P
endif

$(OBJ_DIR)/ai_playerally.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_playerally.o : $(abspath ai_playerally.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_relationship.P
endif

$(OBJ_DIR)/ai_relationship.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_relationship.o : $(abspath ai_relationship.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AI_ResponseSystem.P
endif

$(OBJ_DIR)/AI_ResponseSystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/AI_ResponseSystem.o : $(abspath AI_ResponseSystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_route.P
endif

$(OBJ_DIR)/ai_route.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_route.o : $(abspath ai_route.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_saverestore.P
endif

$(OBJ_DIR)/ai_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_saverestore.o : $(abspath ai_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_schedule.P
endif

$(OBJ_DIR)/ai_schedule.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_schedule.o : $(abspath ai_schedule.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_scriptconditions.P
endif

$(OBJ_DIR)/ai_scriptconditions.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_scriptconditions.o : $(abspath ai_scriptconditions.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_senses.P
endif

$(OBJ_DIR)/ai_senses.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_senses.o : $(abspath ai_senses.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_sentence.P
endif

$(OBJ_DIR)/ai_sentence.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_sentence.o : $(abspath ai_sentence.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_speech.P
endif

$(OBJ_DIR)/ai_speech.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_speech.o : $(abspath ai_speech.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_speechfilter.P
endif

$(OBJ_DIR)/ai_speechfilter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_speechfilter.o : $(abspath ai_speechfilter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_squad.P
endif

$(OBJ_DIR)/ai_squad.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_squad.o : $(abspath ai_squad.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_squadslot.P
endif

$(OBJ_DIR)/ai_squadslot.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_squadslot.o : $(abspath ai_squadslot.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_tacticalservices.P
endif

$(OBJ_DIR)/ai_tacticalservices.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_tacticalservices.o : $(abspath ai_tacticalservices.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_task.P
endif

$(OBJ_DIR)/ai_task.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_task.o : $(abspath ai_task.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_trackpather.P
endif

$(OBJ_DIR)/ai_trackpather.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_trackpather.o : $(abspath ai_trackpather.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_utils.P
endif

$(OBJ_DIR)/ai_utils.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_utils.o : $(abspath ai_utils.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_waypoint.P
endif

$(OBJ_DIR)/ai_waypoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_waypoint.o : $(abspath ai_waypoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseanimating.P
endif

$(OBJ_DIR)/baseanimating.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseanimating.o : $(abspath baseanimating.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseAnimatingOverlay.P
endif

$(OBJ_DIR)/BaseAnimatingOverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/BaseAnimatingOverlay.o : $(abspath BaseAnimatingOverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basebludgeonweapon.P
endif

$(OBJ_DIR)/basebludgeonweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basebludgeonweapon.o : $(abspath basebludgeonweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatcharacter.P
endif

$(OBJ_DIR)/basecombatcharacter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatcharacter.o : $(abspath basecombatcharacter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatweapon.P
endif

$(OBJ_DIR)/basecombatweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatweapon.o : $(abspath basecombatweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseentity.P
endif

$(OBJ_DIR)/baseentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseentity.o : $(abspath baseentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseflex.P
endif

$(OBJ_DIR)/baseflex.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseflex.o : $(abspath baseflex.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_concussion.P
endif

$(OBJ_DIR)/basegrenade_concussion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_concussion.o : $(abspath basegrenade_concussion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_contact.P
endif

$(OBJ_DIR)/basegrenade_contact.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_contact.o : $(abspath basegrenade_contact.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_timed.P
endif

$(OBJ_DIR)/basegrenade_timed.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_timed.o : $(abspath basegrenade_timed.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basemultiplayerplayer.P
endif

$(OBJ_DIR)/basemultiplayerplayer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basemultiplayerplayer.o : $(abspath basemultiplayerplayer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basetempentity.P
endif

$(OBJ_DIR)/basetempentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basetempentity.o : $(abspath basetempentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseviewmodel.P
endif

$(OBJ_DIR)/baseviewmodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseviewmodel.o : $(abspath baseviewmodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_gameinterface.P
endif

$(OBJ_DIR)/base_gameinterface.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/base_gameinterface.o : $(abspath base_gameinterface.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_transmit_proxy.P
endif

$(OBJ_DIR)/base_transmit_proxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/base_transmit_proxy.o : $(abspath base_transmit_proxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bitstring.P
endif

$(OBJ_DIR)/bitstring.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bitstring.o : $(abspath bitstring.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bmodels.P
endif

$(OBJ_DIR)/bmodels.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bmodels.o : $(abspath bmodels.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/buttons.P
endif

$(OBJ_DIR)/buttons.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/buttons.o : $(abspath buttons.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cbase.P
endif

$(OBJ_DIR)/cbase.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cbase.o : $(abspath cbase.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client.P
endif

$(OBJ_DIR)/client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/client.o : $(abspath client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrection.P
endif

$(OBJ_DIR)/colorcorrection.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/colorcorrection.o : $(abspath colorcorrection.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrectionvolume.P
endif

$(OBJ_DIR)/colorcorrectionvolume.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/colorcorrectionvolume.o : $(abspath colorcorrectionvolume.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CommentarySystem.P
endif

$(OBJ_DIR)/CommentarySystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/CommentarySystem.o : $(abspath CommentarySystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/controlentities.P
endif

$(OBJ_DIR)/controlentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/controlentities.o : $(abspath controlentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cplane.P
endif

$(OBJ_DIR)/cplane.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cplane.o : $(abspath cplane.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CRagdollMagnet.P
endif

$(OBJ_DIR)/CRagdollMagnet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/CRagdollMagnet.o : $(abspath CRagdollMagnet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/damagemodifier.P
endif

$(OBJ_DIR)/damagemodifier.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/damagemodifier.o : $(abspath damagemodifier.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/doors.P
endif

$(OBJ_DIR)/doors.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/doors.o : $(abspath doors.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dynamiclight.P
endif

$(OBJ_DIR)/dynamiclight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/dynamiclight.o : $(abspath dynamiclight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/effects.P
endif

$(OBJ_DIR)/effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/effects.o : $(abspath effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EffectsServer.P
endif

$(OBJ_DIR)/EffectsServer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EffectsServer.o : $(abspath EffectsServer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entityblocker.P
endif

$(OBJ_DIR)/entityblocker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entityblocker.o : $(abspath entityblocker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityDissolve.P
endif

$(OBJ_DIR)/EntityDissolve.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityDissolve.o : $(abspath EntityDissolve.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityFlame.P
endif

$(OBJ_DIR)/EntityFlame.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityFlame.o : $(abspath EntityFlame.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entitylist.P
endif

$(OBJ_DIR)/entitylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entitylist.o : $(abspath entitylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityParticleTrail.P
endif

$(OBJ_DIR)/EntityParticleTrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityParticleTrail.o : $(abspath EntityParticleTrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entity_tools_server.P
endif

$(OBJ_DIR)/entity_tools_server.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entity_tools_server.o : $(abspath entity_tools_server.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvBeam.P
endif

$(OBJ_DIR)/EnvBeam.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvBeam.o : $(abspath EnvBeam.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvFade.P
endif

$(OBJ_DIR)/EnvFade.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvFade.o : $(abspath EnvFade.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvHudHint.P
endif

$(OBJ_DIR)/EnvHudHint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvHudHint.o : $(abspath EnvHudHint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvLaser.P
endif

$(OBJ_DIR)/EnvLaser.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvLaser.o : $(abspath EnvLaser.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvMessage.P
endif

$(OBJ_DIR)/EnvMessage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvMessage.o : $(abspath EnvMessage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/envmicrophone.P
endif

$(OBJ_DIR)/envmicrophone.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/envmicrophone.o : $(abspath envmicrophone.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvShake.P
endif

$(OBJ_DIR)/EnvShake.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvShake.o : $(abspath EnvShake.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvSpark.P
endif

$(OBJ_DIR)/EnvSpark.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvSpark.o : $(abspath EnvSpark.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_debughistory.P
endif

$(OBJ_DIR)/env_debughistory.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_debughistory.o : $(abspath env_debughistory.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_effectsscript.P
endif

$(OBJ_DIR)/env_effectsscript.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_effectsscript.o : $(abspath env_effectsscript.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_entity_maker.P
endif

$(OBJ_DIR)/env_entity_maker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_entity_maker.o : $(abspath env_entity_maker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_particlescript.P
endif

$(OBJ_DIR)/env_particlescript.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_particlescript.o : $(abspath env_particlescript.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_player_surface_trigger.P
endif

$(OBJ_DIR)/env_player_surface_trigger.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_player_surface_trigger.o : $(abspath env_player_surface_trigger.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_projectedtexture.P
endif

$(OBJ_DIR)/env_projectedtexture.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_projectedtexture.o : $(abspath env_projectedtexture.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_screenoverlay.P
endif

$(OBJ_DIR)/env_screenoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_screenoverlay.o : $(abspath env_screenoverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_texturetoggle.P
endif

$(OBJ_DIR)/env_texturetoggle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_texturetoggle.o : $(abspath env_texturetoggle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_tonemap_controller.P
endif

$(OBJ_DIR)/env_tonemap_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_tonemap_controller.o : $(abspath env_tonemap_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_zoom.P
endif

$(OBJ_DIR)/env_zoom.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_zoom.o : $(abspath env_zoom.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EventLog.P
endif

$(OBJ_DIR)/EventLog.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EventLog.o : $(abspath EventLog.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/event_tempentity_tester.P
endif

$(OBJ_DIR)/event_tempentity_tester.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/event_tempentity_tester.o : $(abspath event_tempentity_tester.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/explode.P
endif

$(OBJ_DIR)/explode.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/explode.o : $(abspath explode.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filters.P
endif

$(OBJ_DIR)/filters.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/filters.o : $(abspath filters.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fire.P
endif

$(OBJ_DIR)/fire.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fire.o : $(abspath fire.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fire_smoke.P
endif

$(OBJ_DIR)/fire_smoke.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fire_smoke.o : $(abspath fire_smoke.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fish.P
endif

$(OBJ_DIR)/fish.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fish.o : $(abspath fish.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fogcontroller.P
endif

$(OBJ_DIR)/fogcontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fogcontroller.o : $(abspath fogcontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fourwheelvehiclephysics.P
endif

$(OBJ_DIR)/fourwheelvehiclephysics.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fourwheelvehiclephysics.o : $(abspath fourwheelvehiclephysics.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_areaportal.P
endif

$(OBJ_DIR)/func_areaportal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_areaportal.o : $(abspath func_areaportal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_areaportalbase.P
endif

$(OBJ_DIR)/func_areaportalbase.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_areaportalbase.o : $(abspath func_areaportalbase.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_areaportalwindow.P
endif

$(OBJ_DIR)/func_areaportalwindow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_areaportalwindow.o : $(abspath func_areaportalwindow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_break.P
endif

$(OBJ_DIR)/func_break.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_break.o : $(abspath func_break.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_breakablesurf.P
endif

$(OBJ_DIR)/func_breakablesurf.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_breakablesurf.o : $(abspath func_breakablesurf.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_dust.P
endif

$(OBJ_DIR)/func_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_dust.o : $(abspath func_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_ladder_endpoint.P
endif

$(OBJ_DIR)/func_ladder_endpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_ladder_endpoint.o : $(abspath func_ladder_endpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_lod.P
endif

$(OBJ_DIR)/func_lod.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_lod.o : $(abspath func_lod.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_movelinear.P
endif

$(OBJ_DIR)/func_movelinear.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_movelinear.o : $(abspath func_movelinear.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_occluder.P
endif

$(OBJ_DIR)/func_occluder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_occluder.o : $(abspath func_occluder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_reflective_glass.P
endif

$(OBJ_DIR)/func_reflective_glass.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_reflective_glass.o : $(abspath func_reflective_glass.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_smokevolume.P
endif

$(OBJ_DIR)/func_smokevolume.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_smokevolume.o : $(abspath func_smokevolume.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/game.P
endif

$(OBJ_DIR)/game.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/game.o : $(abspath game.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamedll_replay.P
endif

$(OBJ_DIR)/gamedll_replay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamedll_replay.o : $(abspath gamedll_replay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamehandle.P
endif

$(OBJ_DIR)/gamehandle.o : $(abspath gamehandle.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gameinterface.P
endif

$(OBJ_DIR)/gameinterface.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gameinterface.o : $(abspath gameinterface.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameStats_BasicStatsFunctions.P
endif

$(OBJ_DIR)/GameStats_BasicStatsFunctions.o : $(abspath GameStats_BasicStatsFunctions.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gametrace_dll.P
endif

$(OBJ_DIR)/gametrace_dll.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gametrace_dll.o : $(abspath gametrace_dll.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gameweaponmanager.P
endif

$(OBJ_DIR)/gameweaponmanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gameweaponmanager.o : $(abspath gameweaponmanager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/game_ui.P
endif

$(OBJ_DIR)/game_ui.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/game_ui.o : $(abspath game_ui.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/genericactor.P
endif

$(OBJ_DIR)/genericactor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/genericactor.o : $(abspath genericactor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/genericmonster.P
endif

$(OBJ_DIR)/genericmonster.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/genericmonster.o : $(abspath genericmonster.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gib.P
endif

$(OBJ_DIR)/gib.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gib.o : $(abspath gib.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/globals.P
endif

$(OBJ_DIR)/globals.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/globals.o : $(abspath globals.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/globalstate.P
endif

$(OBJ_DIR)/globalstate.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/globalstate.o : $(abspath globalstate.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenadethrown.P
endif

$(OBJ_DIR)/grenadethrown.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenadethrown.o : $(abspath grenadethrown.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/guntarget.P
endif

$(OBJ_DIR)/guntarget.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/guntarget.o : $(abspath guntarget.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hierarchy.P
endif

$(OBJ_DIR)/hierarchy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hierarchy.o : $(abspath hierarchy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_allymanager.P
endif

$(OBJ_DIR)/ai_allymanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_allymanager.o : $(abspath hl2/ai_allymanager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_actbusy.P
endif

$(OBJ_DIR)/ai_behavior_actbusy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_actbusy.o : $(abspath hl2/ai_behavior_actbusy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_functank.P
endif

$(OBJ_DIR)/ai_behavior_functank.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_functank.o : $(abspath hl2/ai_behavior_functank.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_holster.P
endif

$(OBJ_DIR)/ai_behavior_holster.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_holster.o : $(abspath hl2/ai_behavior_holster.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_operator.P
endif

$(OBJ_DIR)/ai_behavior_operator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_operator.o : $(abspath hl2/ai_behavior_operator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_police.P
endif

$(OBJ_DIR)/ai_behavior_police.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_police.o : $(abspath hl2/ai_behavior_police.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_goal_police.P
endif

$(OBJ_DIR)/ai_goal_police.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_goal_police.o : $(abspath hl2/ai_goal_police.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_spotlight.P
endif

$(OBJ_DIR)/ai_spotlight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_spotlight.o : $(abspath hl2/ai_spotlight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/antlion_dust.P
endif

$(OBJ_DIR)/antlion_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/antlion_dust.o : $(abspath hl2/antlion_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/antlion_maker.P
endif

$(OBJ_DIR)/antlion_maker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/antlion_maker.o : $(abspath hl2/antlion_maker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ar2_explosion.P
endif

$(OBJ_DIR)/ar2_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ar2_explosion.o : $(abspath hl2/ar2_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basehlcombatweapon.P
endif

$(OBJ_DIR)/basehlcombatweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basehlcombatweapon.o : $(abspath hl2/basehlcombatweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cbasehelicopter.P
endif

$(OBJ_DIR)/cbasehelicopter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cbasehelicopter.o : $(abspath hl2/cbasehelicopter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cbasespriteprojectile.P
endif

$(OBJ_DIR)/cbasespriteprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cbasespriteprojectile.o : $(abspath hl2/cbasespriteprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/citadel_effects.P
endif

$(OBJ_DIR)/citadel_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/citadel_effects.o : $(abspath hl2/citadel_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/combine_mine.P
endif

$(OBJ_DIR)/combine_mine.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/combine_mine.o : $(abspath hl2/combine_mine.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_alyxemp.P
endif

$(OBJ_DIR)/env_alyxemp.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_alyxemp.o : $(abspath hl2/env_alyxemp.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_headcrabcanister.P
endif

$(OBJ_DIR)/env_headcrabcanister.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_headcrabcanister.o : $(abspath hl2/env_headcrabcanister.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_speaker.P
endif

$(OBJ_DIR)/env_speaker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_speaker.o : $(abspath hl2/env_speaker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_starfield.P
endif

$(OBJ_DIR)/env_starfield.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_starfield.o : $(abspath hl2/env_starfield.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Func_Monitor.P
endif

$(OBJ_DIR)/Func_Monitor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/Func_Monitor.o : $(abspath hl2/Func_Monitor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_recharge.P
endif

$(OBJ_DIR)/func_recharge.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_recharge.o : $(abspath hl2/func_recharge.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_tank.P
endif

$(OBJ_DIR)/func_tank.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_tank.o : $(abspath hl2/func_tank.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_ar2.P
endif

$(OBJ_DIR)/grenade_ar2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_ar2.o : $(abspath hl2/grenade_ar2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_beam.P
endif

$(OBJ_DIR)/grenade_beam.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_beam.o : $(abspath hl2/grenade_beam.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_bugbait.P
endif

$(OBJ_DIR)/grenade_bugbait.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_bugbait.o : $(abspath hl2/grenade_bugbait.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_frag.P
endif

$(OBJ_DIR)/grenade_frag.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_frag.o : $(abspath hl2/grenade_frag.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_homer.P
endif

$(OBJ_DIR)/grenade_homer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_homer.o : $(abspath hl2/grenade_homer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_pathfollower.P
endif

$(OBJ_DIR)/grenade_pathfollower.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_pathfollower.o : $(abspath hl2/grenade_pathfollower.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_ai_network.P
endif

$(OBJ_DIR)/hl2_ai_network.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_ai_network.o : $(abspath hl2/hl2_ai_network.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_client.P
endif

$(OBJ_DIR)/hl2_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_client.o : $(abspath hl2/hl2_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_eventlog.P
endif

$(OBJ_DIR)/hl2_eventlog.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_eventlog.o : $(abspath hl2/hl2_eventlog.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_gamestats.P
endif

$(OBJ_DIR)/hl2_gamestats.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_gamestats.o : $(abspath hl2/hl2_gamestats.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_player.P
endif

$(OBJ_DIR)/hl2_player.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_player.o : $(abspath hl2/hl2_player.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_playerlocaldata.P
endif

$(OBJ_DIR)/hl2_playerlocaldata.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_playerlocaldata.o : $(abspath hl2/hl2_playerlocaldata.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_triggers.P
endif

$(OBJ_DIR)/hl2_triggers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_triggers.o : $(abspath hl2/hl2_triggers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_playermove.P
endif

$(OBJ_DIR)/hl_playermove.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_playermove.o : $(abspath hl2/hl_playermove.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/info_darknessmode_lightsource.P
endif

$(OBJ_DIR)/info_darknessmode_lightsource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/info_darknessmode_lightsource.o : $(abspath hl2/info_darknessmode_lightsource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/info_teleporter_countdown.P
endif

$(OBJ_DIR)/info_teleporter_countdown.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/info_teleporter_countdown.o : $(abspath hl2/info_teleporter_countdown.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_ammo.P
endif

$(OBJ_DIR)/item_ammo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_ammo.o : $(abspath hl2/item_ammo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_battery.P
endif

$(OBJ_DIR)/item_battery.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_battery.o : $(abspath hl2/item_battery.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_dynamic_resupply.P
endif

$(OBJ_DIR)/item_dynamic_resupply.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_dynamic_resupply.o : $(abspath hl2/item_dynamic_resupply.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_healthkit.P
endif

$(OBJ_DIR)/item_healthkit.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_healthkit.o : $(abspath hl2/item_healthkit.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_itemcrate.P
endif

$(OBJ_DIR)/item_itemcrate.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_itemcrate.o : $(abspath hl2/item_itemcrate.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_suit.P
endif

$(OBJ_DIR)/item_suit.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_suit.o : $(abspath hl2/item_suit.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/look_door.P
endif

$(OBJ_DIR)/look_door.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/look_door.o : $(abspath hl2/look_door.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/monster_dummy.P
endif

$(OBJ_DIR)/monster_dummy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/monster_dummy.o : $(abspath hl2/monster_dummy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_alyx.P
endif

$(OBJ_DIR)/npc_alyx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_alyx.o : $(abspath hl2/npc_alyx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_antlion.P
endif

$(OBJ_DIR)/npc_antlion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_antlion.o : $(abspath hl2/npc_antlion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_antlionguard.P
endif

$(OBJ_DIR)/npc_antlionguard.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_antlionguard.o : $(abspath hl2/npc_antlionguard.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_apcdriver.P
endif

$(OBJ_DIR)/npc_apcdriver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_apcdriver.o : $(abspath hl2/npc_apcdriver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_attackchopper.P
endif

$(OBJ_DIR)/npc_attackchopper.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_attackchopper.o : $(abspath hl2/npc_attackchopper.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_barnacle.P
endif

$(OBJ_DIR)/npc_barnacle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_barnacle.o : $(abspath hl2/npc_barnacle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_barney.P
endif

$(OBJ_DIR)/npc_barney.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_barney.o : $(abspath hl2/npc_barney.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_basescanner.P
endif

$(OBJ_DIR)/npc_basescanner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_basescanner.o : $(abspath hl2/npc_basescanner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_BaseZombie.P
endif

$(OBJ_DIR)/npc_BaseZombie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_BaseZombie.o : $(abspath hl2/npc_BaseZombie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_blob.P
endif

$(OBJ_DIR)/npc_blob.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_blob.o : $(abspath hl2/npc_blob.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_breen.P
endif

$(OBJ_DIR)/npc_breen.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_breen.o : $(abspath hl2/npc_breen.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_bullseye.P
endif

$(OBJ_DIR)/npc_bullseye.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_bullseye.o : $(abspath hl2/npc_bullseye.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_citizen17.P
endif

$(OBJ_DIR)/npc_citizen17.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_citizen17.o : $(abspath hl2/npc_citizen17.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combine.P
endif

$(OBJ_DIR)/npc_combine.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combine.o : $(abspath hl2/npc_combine.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combinecamera.P
endif

$(OBJ_DIR)/npc_combinecamera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combinecamera.o : $(abspath hl2/npc_combinecamera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combinedropship.P
endif

$(OBJ_DIR)/npc_combinedropship.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combinedropship.o : $(abspath hl2/npc_combinedropship.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combinegunship.P
endif

$(OBJ_DIR)/npc_combinegunship.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combinegunship.o : $(abspath hl2/npc_combinegunship.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combines.P
endif

$(OBJ_DIR)/npc_combines.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combines.o : $(abspath hl2/npc_combines.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_cranedriver.P
endif

$(OBJ_DIR)/npc_cranedriver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_cranedriver.o : $(abspath hl2/npc_cranedriver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_crow.P
endif

$(OBJ_DIR)/npc_crow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_crow.o : $(abspath hl2/npc_crow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_dog.P
endif

$(OBJ_DIR)/npc_dog.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_dog.o : $(abspath hl2/npc_dog.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_eli.P
endif

$(OBJ_DIR)/npc_eli.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_eli.o : $(abspath hl2/npc_eli.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_enemyfinder.P
endif

$(OBJ_DIR)/npc_enemyfinder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_enemyfinder.o : $(abspath hl2/npc_enemyfinder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_fastzombie.P
endif

$(OBJ_DIR)/npc_fastzombie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_fastzombie.o : $(abspath hl2/npc_fastzombie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_fisherman.P
endif

$(OBJ_DIR)/npc_fisherman.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_fisherman.o : $(abspath hl2/npc_fisherman.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_gman.P
endif

$(OBJ_DIR)/npc_gman.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_gman.o : $(abspath hl2/npc_gman.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_headcrab.P
endif

$(OBJ_DIR)/npc_headcrab.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_headcrab.o : $(abspath hl2/npc_headcrab.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_ichthyosaur.P
endif

$(OBJ_DIR)/npc_ichthyosaur.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_ichthyosaur.o : $(abspath hl2/npc_ichthyosaur.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_kleiner.P
endif

$(OBJ_DIR)/npc_kleiner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_kleiner.o : $(abspath hl2/npc_kleiner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_launcher.P
endif

$(OBJ_DIR)/npc_launcher.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_launcher.o : $(abspath hl2/npc_launcher.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_manhack.P
endif

$(OBJ_DIR)/npc_manhack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_manhack.o : $(abspath hl2/npc_manhack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_metropolice.P
endif

$(OBJ_DIR)/npc_metropolice.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_metropolice.o : $(abspath hl2/npc_metropolice.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_missiledefense.P
endif

$(OBJ_DIR)/npc_missiledefense.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_missiledefense.o : $(abspath hl2/npc_missiledefense.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_monk.P
endif

$(OBJ_DIR)/npc_monk.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_monk.o : $(abspath hl2/npc_monk.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_mossman.P
endif

$(OBJ_DIR)/npc_mossman.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_mossman.o : $(abspath hl2/npc_mossman.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_playercompanion.P
endif

$(OBJ_DIR)/npc_playercompanion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_playercompanion.o : $(abspath hl2/npc_playercompanion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_PoisonZombie.P
endif

$(OBJ_DIR)/npc_PoisonZombie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_PoisonZombie.o : $(abspath hl2/npc_PoisonZombie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_rollermine.P
endif

$(OBJ_DIR)/npc_rollermine.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_rollermine.o : $(abspath hl2/npc_rollermine.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_scanner.P
endif

$(OBJ_DIR)/npc_scanner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_scanner.o : $(abspath hl2/npc_scanner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_stalker.P
endif

$(OBJ_DIR)/npc_stalker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_stalker.o : $(abspath hl2/npc_stalker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_strider.P
endif

$(OBJ_DIR)/npc_strider.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_strider.o : $(abspath hl2/npc_strider.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_turret_ceiling.P
endif

$(OBJ_DIR)/npc_turret_ceiling.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_turret_ceiling.o : $(abspath hl2/npc_turret_ceiling.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_turret_floor.P
endif

$(OBJ_DIR)/npc_turret_floor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_turret_floor.o : $(abspath hl2/npc_turret_floor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_turret_ground.P
endif

$(OBJ_DIR)/npc_turret_ground.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_turret_ground.o : $(abspath hl2/npc_turret_ground.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_vortigaunt_episodic.P
endif

$(OBJ_DIR)/npc_vortigaunt_episodic.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_vortigaunt_episodic.o : $(abspath hl2/npc_vortigaunt_episodic.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_zombie.P
endif

$(OBJ_DIR)/npc_zombie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_zombie.o : $(abspath hl2/npc_zombie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_apc_controller.P
endif

$(OBJ_DIR)/point_apc_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_apc_controller.o : $(abspath hl2/point_apc_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/prop_combine_ball.P
endif

$(OBJ_DIR)/prop_combine_ball.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/prop_combine_ball.o : $(abspath hl2/prop_combine_ball.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/prop_thumper.P
endif

$(OBJ_DIR)/prop_thumper.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/prop_thumper.o : $(abspath hl2/prop_thumper.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/proto_sniper.P
endif

$(OBJ_DIR)/proto_sniper.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/proto_sniper.o : $(abspath hl2/proto_sniper.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rotorwash.P
endif

$(OBJ_DIR)/rotorwash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/rotorwash.o : $(abspath hl2/rotorwash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/script_intro.P
endif

$(OBJ_DIR)/script_intro.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/script_intro.o : $(abspath hl2/script_intro.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_gaussexplosion.P
endif

$(OBJ_DIR)/te_gaussexplosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_gaussexplosion.o : $(abspath hl2/te_gaussexplosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_airboat.P
endif

$(OBJ_DIR)/vehicle_airboat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_airboat.o : $(abspath hl2/vehicle_airboat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_apc.P
endif

$(OBJ_DIR)/vehicle_apc.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_apc.o : $(abspath hl2/vehicle_apc.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_cannon.P
endif

$(OBJ_DIR)/vehicle_cannon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_cannon.o : $(abspath hl2/vehicle_cannon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_crane.P
endif

$(OBJ_DIR)/vehicle_crane.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_crane.o : $(abspath hl2/vehicle_crane.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_jeep.P
endif

$(OBJ_DIR)/vehicle_jeep.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_jeep.o : $(abspath hl2/vehicle_jeep.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_prisoner_pod.P
endif

$(OBJ_DIR)/vehicle_prisoner_pod.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_prisoner_pod.o : $(abspath hl2/vehicle_prisoner_pod.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_viewcontroller.P
endif

$(OBJ_DIR)/vehicle_viewcontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_viewcontroller.o : $(abspath hl2/vehicle_viewcontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_357.P
endif

$(OBJ_DIR)/weapon_357.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_357.o : $(abspath hl2/weapon_357.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_alyxgun.P
endif

$(OBJ_DIR)/weapon_alyxgun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_alyxgun.o : $(abspath hl2/weapon_alyxgun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_annabelle.P
endif

$(OBJ_DIR)/weapon_annabelle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_annabelle.o : $(abspath hl2/weapon_annabelle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_ar2.P
endif

$(OBJ_DIR)/weapon_ar2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_ar2.o : $(abspath hl2/weapon_ar2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_bugbait.P
endif

$(OBJ_DIR)/weapon_bugbait.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_bugbait.o : $(abspath hl2/weapon_bugbait.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_cguard.P
endif

$(OBJ_DIR)/weapon_cguard.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_cguard.o : $(abspath hl2/weapon_cguard.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_citizenpackage.P
endif

$(OBJ_DIR)/weapon_citizenpackage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_citizenpackage.o : $(abspath hl2/weapon_citizenpackage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_crossbow.P
endif

$(OBJ_DIR)/weapon_crossbow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_crossbow.o : $(abspath hl2/weapon_crossbow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_crowbar.P
endif

$(OBJ_DIR)/weapon_crowbar.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_crowbar.o : $(abspath hl2/weapon_crowbar.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_flaregun.P
endif

$(OBJ_DIR)/weapon_flaregun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_flaregun.o : $(abspath hl2/weapon_flaregun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_frag.P
endif

$(OBJ_DIR)/weapon_frag.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_frag.o : $(abspath hl2/weapon_frag.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_physcannon.P
endif

$(OBJ_DIR)/weapon_physcannon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_physcannon.o : $(abspath hl2/weapon_physcannon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_pistol.P
endif

$(OBJ_DIR)/weapon_pistol.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_pistol.o : $(abspath hl2/weapon_pistol.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_rpg.P
endif

$(OBJ_DIR)/weapon_rpg.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_rpg.o : $(abspath hl2/weapon_rpg.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_shotgun.P
endif

$(OBJ_DIR)/weapon_shotgun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_shotgun.o : $(abspath hl2/weapon_shotgun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_smg1.P
endif

$(OBJ_DIR)/weapon_smg1.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_smg1.o : $(abspath hl2/weapon_smg1.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_stunstick.P
endif

$(OBJ_DIR)/weapon_stunstick.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_stunstick.o : $(abspath hl2/weapon_stunstick.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvdirector.P
endif

$(OBJ_DIR)/hltvdirector.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hltvdirector.o : $(abspath hltvdirector.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/h_ai.P
endif

$(OBJ_DIR)/h_ai.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/h_ai.o : $(abspath h_ai.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/h_cycler.P
endif

$(OBJ_DIR)/h_cycler.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/h_cycler.o : $(abspath h_cycler.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/h_export.P
endif

$(OBJ_DIR)/h_export.o : $(abspath h_export.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/info_camera_link.P
endif

$(OBJ_DIR)/info_camera_link.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/info_camera_link.o : $(abspath info_camera_link.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/info_overlay_accessor.P
endif

$(OBJ_DIR)/info_overlay_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/info_overlay_accessor.o : $(abspath info_overlay_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/init_factory.P
endif

$(OBJ_DIR)/init_factory.o : $(abspath init_factory.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/intermission.P
endif

$(OBJ_DIR)/intermission.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/intermission.o : $(abspath intermission.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_world.P
endif

$(OBJ_DIR)/item_world.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_world.o : $(abspath item_world.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightglow.P
endif

$(OBJ_DIR)/lightglow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/lightglow.o : $(abspath lightglow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lights.P
endif

$(OBJ_DIR)/lights.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/lights.o : $(abspath lights.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logicauto.P
endif

$(OBJ_DIR)/logicauto.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logicauto.o : $(abspath logicauto.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logicentities.P
endif

$(OBJ_DIR)/logicentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logicentities.o : $(abspath logicentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logicrelay.P
endif

$(OBJ_DIR)/logicrelay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logicrelay.o : $(abspath logicrelay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logic_achievement.P
endif

$(OBJ_DIR)/logic_achievement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logic_achievement.o : $(abspath logic_achievement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logic_measure_movement.P
endif

$(OBJ_DIR)/logic_measure_movement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logic_measure_movement.o : $(abspath logic_measure_movement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logic_navigation.P
endif

$(OBJ_DIR)/logic_navigation.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logic_navigation.o : $(abspath logic_navigation.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mapentities.P
endif

$(OBJ_DIR)/mapentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mapentities.o : $(abspath mapentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/maprules.P
endif

$(OBJ_DIR)/maprules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/maprules.o : $(abspath maprules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MaterialModifyControl.P
endif

$(OBJ_DIR)/MaterialModifyControl.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/MaterialModifyControl.o : $(abspath MaterialModifyControl.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/message_entity.P
endif

$(OBJ_DIR)/message_entity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/message_entity.o : $(abspath message_entity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/modelentities.P
endif

$(OBJ_DIR)/modelentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/modelentities.o : $(abspath modelentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/monstermaker.P
endif

$(OBJ_DIR)/monstermaker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/monstermaker.o : $(abspath monstermaker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movehelper_server.P
endif

$(OBJ_DIR)/movehelper_server.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movehelper_server.o : $(abspath movehelper_server.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movement.P
endif

$(OBJ_DIR)/movement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movement.o : $(abspath movement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movie_explosion.P
endif

$(OBJ_DIR)/movie_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movie_explosion.o : $(abspath movie_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ndebugoverlay.P
endif

$(OBJ_DIR)/ndebugoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ndebugoverlay.o : $(abspath ndebugoverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_talker.P
endif

$(OBJ_DIR)/npc_talker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_talker.o : $(abspath npc_talker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_vehicledriver.P
endif

$(OBJ_DIR)/npc_vehicledriver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_vehicledriver.o : $(abspath npc_vehicledriver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_fire.P
endif

$(OBJ_DIR)/particle_fire.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_fire.o : $(abspath particle_fire.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_light.P
endif

$(OBJ_DIR)/particle_light.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_light.o : $(abspath particle_light.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_smokegrenade.P
endif

$(OBJ_DIR)/particle_smokegrenade.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_smokegrenade.o : $(abspath particle_smokegrenade.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_system.P
endif

$(OBJ_DIR)/particle_system.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_system.o : $(abspath particle_system.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pathcorner.P
endif

$(OBJ_DIR)/pathcorner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pathcorner.o : $(abspath pathcorner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pathtrack.P
endif

$(OBJ_DIR)/pathtrack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pathtrack.o : $(abspath pathtrack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physconstraint.P
endif

$(OBJ_DIR)/physconstraint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physconstraint.o : $(abspath physconstraint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics.P
endif

$(OBJ_DIR)/physics.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics.o : $(abspath physics.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_bone_follower.P
endif

$(OBJ_DIR)/physics_bone_follower.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_bone_follower.o : $(abspath physics_bone_follower.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_cannister.P
endif

$(OBJ_DIR)/physics_cannister.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_cannister.o : $(abspath physics_cannister.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_fx.P
endif

$(OBJ_DIR)/physics_fx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_fx.o : $(abspath physics_fx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_impact_damage.P
endif

$(OBJ_DIR)/physics_impact_damage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_impact_damage.o : $(abspath physics_impact_damage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_main.P
endif

$(OBJ_DIR)/physics_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_main.o : $(abspath physics_main.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_npc_solver.P
endif

$(OBJ_DIR)/physics_npc_solver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_npc_solver.o : $(abspath physics_npc_solver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_prop_ragdoll.P
endif

$(OBJ_DIR)/physics_prop_ragdoll.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_prop_ragdoll.o : $(abspath physics_prop_ragdoll.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physobj.P
endif

$(OBJ_DIR)/physobj.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physobj.o : $(abspath physobj.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/phys_controller.P
endif

$(OBJ_DIR)/phys_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/phys_controller.o : $(abspath phys_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/plasma.P
endif

$(OBJ_DIR)/plasma.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/plasma.o : $(abspath plasma.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player.P
endif

$(OBJ_DIR)/player.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player.o : $(abspath player.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/playerinfomanager.P
endif

$(OBJ_DIR)/playerinfomanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/playerinfomanager.o : $(abspath playerinfomanager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/playerlocaldata.P
endif

$(OBJ_DIR)/playerlocaldata.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/playerlocaldata.o : $(abspath playerlocaldata.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player_command.P
endif

$(OBJ_DIR)/player_command.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player_command.o : $(abspath player_command.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player_lagcompensation.P
endif

$(OBJ_DIR)/player_lagcompensation.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player_lagcompensation.o : $(abspath player_lagcompensation.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player_pickup.P
endif

$(OBJ_DIR)/player_pickup.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player_pickup.o : $(abspath player_pickup.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player_resource.P
endif

$(OBJ_DIR)/player_resource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player_resource.o : $(abspath player_resource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/plugin_check.P
endif

$(OBJ_DIR)/plugin_check.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/plugin_check.o : $(abspath plugin_check.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pointanglesensor.P
endif

$(OBJ_DIR)/pointanglesensor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pointanglesensor.o : $(abspath pointanglesensor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PointAngularVelocitySensor.P
endif

$(OBJ_DIR)/PointAngularVelocitySensor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/PointAngularVelocitySensor.o : $(abspath PointAngularVelocitySensor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pointhurt.P
endif

$(OBJ_DIR)/pointhurt.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pointhurt.o : $(abspath pointhurt.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pointteleport.P
endif

$(OBJ_DIR)/pointteleport.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pointteleport.o : $(abspath pointteleport.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_camera.P
endif

$(OBJ_DIR)/point_camera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_camera.o : $(abspath point_camera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_devshot_camera.P
endif

$(OBJ_DIR)/point_devshot_camera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_devshot_camera.o : $(abspath point_devshot_camera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_playermoveconstraint.P
endif

$(OBJ_DIR)/point_playermoveconstraint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_playermoveconstraint.o : $(abspath point_playermoveconstraint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_spotlight.P
endif

$(OBJ_DIR)/point_spotlight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_spotlight.o : $(abspath point_spotlight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_template.P
endif

$(OBJ_DIR)/point_template.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_template.o : $(abspath point_template.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/props.P
endif

$(OBJ_DIR)/props.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/props.o : $(abspath props.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/RagdollBoogie.P
endif

$(OBJ_DIR)/RagdollBoogie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/RagdollBoogie.o : $(abspath RagdollBoogie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll_manager.P
endif

$(OBJ_DIR)/ragdoll_manager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ragdoll_manager.o : $(abspath ragdoll_manager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/recipientfilter.P
endif

$(OBJ_DIR)/recipientfilter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/recipientfilter.o : $(abspath recipientfilter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope.P
endif

$(OBJ_DIR)/rope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/rope.o : $(abspath rope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/saverestore_gamedll.P
endif

$(OBJ_DIR)/saverestore_gamedll.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/saverestore_gamedll.o : $(abspath saverestore_gamedll.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sceneentity.P
endif

$(OBJ_DIR)/sceneentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sceneentity.o : $(abspath sceneentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scratchpad_gamedll_helpers.P
endif

$(OBJ_DIR)/scratchpad_gamedll_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/scratchpad_gamedll_helpers.o : $(abspath scratchpad_gamedll_helpers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scripted.P
endif

$(OBJ_DIR)/scripted.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/scripted.o : $(abspath scripted.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scriptedtarget.P
endif

$(OBJ_DIR)/scriptedtarget.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/scriptedtarget.o : $(abspath scriptedtarget.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sendproxy.P
endif

$(OBJ_DIR)/sendproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sendproxy.o : $(abspath sendproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerNetworkProperty.P
endif

$(OBJ_DIR)/ServerNetworkProperty.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ServerNetworkProperty.o : $(abspath ServerNetworkProperty.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadowcontrol.P
endif

$(OBJ_DIR)/shadowcontrol.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/shadowcontrol.o : $(abspath shadowcontrol.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SkyCamera.P
endif

$(OBJ_DIR)/SkyCamera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SkyCamera.o : $(abspath SkyCamera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/slideshow_display.P
endif

$(OBJ_DIR)/slideshow_display.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/slideshow_display.o : $(abspath slideshow_display.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/smokestack.P
endif

$(OBJ_DIR)/smokestack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/smokestack.o : $(abspath smokestack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/smoke_trail.P
endif

$(OBJ_DIR)/smoke_trail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/smoke_trail.o : $(abspath smoke_trail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sound.P
endif

$(OBJ_DIR)/sound.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sound.o : $(abspath sound.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundent.P
endif

$(OBJ_DIR)/soundent.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundent.o : $(abspath soundent.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundscape.P
endif

$(OBJ_DIR)/soundscape.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundscape.o : $(abspath soundscape.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundscape_system.P
endif

$(OBJ_DIR)/soundscape_system.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundscape_system.o : $(abspath soundscape_system.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spotlightend.P
endif

$(OBJ_DIR)/spotlightend.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/spotlightend.o : $(abspath spotlightend.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sprite_perfmonitor.P
endif

$(OBJ_DIR)/sprite_perfmonitor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sprite_perfmonitor.o : $(abspath sprite_perfmonitor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stdafx.P
endif

$(OBJ_DIR)/cbase.h.gch : cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/cbase.h.P : $(OBJ_DIR)/cbase.h.gch

vpath cbase.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/cbase.h.P
endif

$(OBJ_DIR)/cbase.h : cbase.h $(OBJ_DIR)/cbase.h.gch $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/cbase.h

$(OBJ_DIR)/stdafx.o : $(abspath stdafx.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamjet.P
endif

$(OBJ_DIR)/steamjet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/steamjet.o : $(abspath steamjet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/subs.P
endif

$(OBJ_DIR)/subs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/subs.o : $(abspath subs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sun.P
endif

$(OBJ_DIR)/sun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sun.o : $(abspath sun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tactical_mission.P
endif

$(OBJ_DIR)/tactical_mission.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/tactical_mission.o : $(abspath tactical_mission.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tanktrain.P
endif

$(OBJ_DIR)/tanktrain.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/tanktrain.o : $(abspath tanktrain.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te.P
endif

$(OBJ_DIR)/te.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te.o : $(abspath te.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/team.P
endif

$(OBJ_DIR)/team.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/team.o : $(abspath team.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/team_spawnpoint.P
endif

$(OBJ_DIR)/team_spawnpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/team_spawnpoint.o : $(abspath team_spawnpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TemplateEntities.P
endif

$(OBJ_DIR)/TemplateEntities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/TemplateEntities.o : $(abspath TemplateEntities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tempmonster.P
endif

$(OBJ_DIR)/tempmonster.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/tempmonster.o : $(abspath tempmonster.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tesla.P
endif

$(OBJ_DIR)/tesla.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/tesla.o : $(abspath tesla.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/testfunctions.P
endif

$(OBJ_DIR)/testfunctions.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/testfunctions.o : $(abspath testfunctions.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/testtraceline.P
endif

$(OBJ_DIR)/testtraceline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/testtraceline.o : $(abspath testtraceline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/test_proxytoggle.P
endif

$(OBJ_DIR)/test_proxytoggle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/test_proxytoggle.o : $(abspath test_proxytoggle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/test_stressentities.P
endif

$(OBJ_DIR)/test_stressentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/test_stressentities.o : $(abspath test_stressentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/textstatsmgr.P
endif

$(OBJ_DIR)/textstatsmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/textstatsmgr.o : $(abspath textstatsmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_armorricochet.P
endif

$(OBJ_DIR)/te_armorricochet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_armorricochet.o : $(abspath te_armorricochet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_basebeam.P
endif

$(OBJ_DIR)/te_basebeam.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_basebeam.o : $(abspath te_basebeam.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamentpoint.P
endif

$(OBJ_DIR)/te_beamentpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamentpoint.o : $(abspath te_beamentpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beaments.P
endif

$(OBJ_DIR)/te_beaments.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beaments.o : $(abspath te_beaments.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamfollow.P
endif

$(OBJ_DIR)/te_beamfollow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamfollow.o : $(abspath te_beamfollow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamlaser.P
endif

$(OBJ_DIR)/te_beamlaser.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamlaser.o : $(abspath te_beamlaser.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beampoints.P
endif

$(OBJ_DIR)/te_beampoints.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beampoints.o : $(abspath te_beampoints.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamring.P
endif

$(OBJ_DIR)/te_beamring.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamring.o : $(abspath te_beamring.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamringpoint.P
endif

$(OBJ_DIR)/te_beamringpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamringpoint.o : $(abspath te_beamringpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamspline.P
endif

$(OBJ_DIR)/te_beamspline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamspline.o : $(abspath te_beamspline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bloodsprite.P
endif

$(OBJ_DIR)/te_bloodsprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bloodsprite.o : $(abspath te_bloodsprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bloodstream.P
endif

$(OBJ_DIR)/te_bloodstream.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bloodstream.o : $(abspath te_bloodstream.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_breakmodel.P
endif

$(OBJ_DIR)/te_breakmodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_breakmodel.o : $(abspath te_breakmodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bspdecal.P
endif

$(OBJ_DIR)/te_bspdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bspdecal.o : $(abspath te_bspdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bubbles.P
endif

$(OBJ_DIR)/te_bubbles.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bubbles.o : $(abspath te_bubbles.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bubbletrail.P
endif

$(OBJ_DIR)/te_bubbletrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bubbletrail.o : $(abspath te_bubbletrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_clientprojectile.P
endif

$(OBJ_DIR)/te_clientprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_clientprojectile.o : $(abspath te_clientprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_decal.P
endif

$(OBJ_DIR)/te_decal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_decal.o : $(abspath te_decal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_dynamiclight.P
endif

$(OBJ_DIR)/te_dynamiclight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_dynamiclight.o : $(abspath te_dynamiclight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_effect_dispatch.P
endif

$(OBJ_DIR)/te_effect_dispatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_effect_dispatch.o : $(abspath te_effect_dispatch.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_energysplash.P
endif

$(OBJ_DIR)/te_energysplash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_energysplash.o : $(abspath te_energysplash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_explosion.P
endif

$(OBJ_DIR)/te_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_explosion.o : $(abspath te_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_fizz.P
endif

$(OBJ_DIR)/te_fizz.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_fizz.o : $(abspath te_fizz.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_footprintdecal.P
endif

$(OBJ_DIR)/te_footprintdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_footprintdecal.o : $(abspath te_footprintdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_glassshatter.P
endif

$(OBJ_DIR)/te_glassshatter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_glassshatter.o : $(abspath te_glassshatter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_glowsprite.P
endif

$(OBJ_DIR)/te_glowsprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_glowsprite.o : $(abspath te_glowsprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_impact.P
endif

$(OBJ_DIR)/te_impact.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_impact.o : $(abspath te_impact.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_killplayerattachments.P
endif

$(OBJ_DIR)/te_killplayerattachments.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_killplayerattachments.o : $(abspath te_killplayerattachments.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_largefunnel.P
endif

$(OBJ_DIR)/te_largefunnel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_largefunnel.o : $(abspath te_largefunnel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_muzzleflash.P
endif

$(OBJ_DIR)/te_muzzleflash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_muzzleflash.o : $(abspath te_muzzleflash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_particlesystem.P
endif

$(OBJ_DIR)/te_particlesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_particlesystem.o : $(abspath te_particlesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_physicsprop.P
endif

$(OBJ_DIR)/te_physicsprop.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_physicsprop.o : $(abspath te_physicsprop.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_playerdecal.P
endif

$(OBJ_DIR)/te_playerdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_playerdecal.o : $(abspath te_playerdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_projecteddecal.P
endif

$(OBJ_DIR)/te_projecteddecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_projecteddecal.o : $(abspath te_projecteddecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_showline.P
endif

$(OBJ_DIR)/te_showline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_showline.o : $(abspath te_showline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_smoke.P
endif

$(OBJ_DIR)/te_smoke.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_smoke.o : $(abspath te_smoke.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_sparks.P
endif

$(OBJ_DIR)/te_sparks.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_sparks.o : $(abspath te_sparks.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_sprite.P
endif

$(OBJ_DIR)/te_sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_sprite.o : $(abspath te_sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_spritespray.P
endif

$(OBJ_DIR)/te_spritespray.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_spritespray.o : $(abspath te_spritespray.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_worlddecal.P
endif

$(OBJ_DIR)/te_worlddecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_worlddecal.o : $(abspath te_worlddecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/timedeventmgr.P
endif

$(OBJ_DIR)/timedeventmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/timedeventmgr.o : $(abspath timedeventmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/toolframework_server.P
endif

$(OBJ_DIR)/toolframework_server.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/toolframework_server.o : $(abspath toolframework_server.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/trains.P
endif

$(OBJ_DIR)/trains.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/trains.o : $(abspath trains.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/triggers.P
endif

$(OBJ_DIR)/triggers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/triggers.o : $(abspath triggers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/util.P
endif

$(OBJ_DIR)/util.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/util.o : $(abspath util.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/variant_t.P
endif

$(OBJ_DIR)/variant_t.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/variant_t.o : $(abspath variant_t.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_base.P
endif

$(OBJ_DIR)/vehicle_base.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_base.o : $(abspath vehicle_base.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_baseserver.P
endif

$(OBJ_DIR)/vehicle_baseserver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_baseserver.o : $(abspath vehicle_baseserver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_choreo_generic.P
endif

$(OBJ_DIR)/vehicle_choreo_generic.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_choreo_generic.o : $(abspath vehicle_choreo_generic.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vguiscreen.P
endif

$(OBJ_DIR)/vguiscreen.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vguiscreen.o : $(abspath vguiscreen.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/waterbullet.P
endif

$(OBJ_DIR)/waterbullet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/waterbullet.o : $(abspath waterbullet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WaterLODControl.P
endif

$(OBJ_DIR)/WaterLODControl.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/WaterLODControl.o : $(abspath WaterLODControl.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/wcedit.P
endif

$(OBJ_DIR)/wcedit.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/wcedit.o : $(abspath wcedit.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_cubemap.P
endif

$(OBJ_DIR)/weapon_cubemap.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_cubemap.o : $(abspath weapon_cubemap.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weight_button.P
endif

$(OBJ_DIR)/weight_button.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weight_button.o : $(abspath weight_button.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/world.P
endif

$(OBJ_DIR)/world.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/world.o : $(abspath world.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
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
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=server -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DGAME_DLL -DVECTOR -DVERSION_SAFE_STEAM_API_INTERFACES -DPROTECTED_THINGS_ENABLE -Dsprintf=use_Q_snprintf_instead_of_sprintf -Dstrncpy=use_Q_strncpy_instead -D_snprintf=use_Q_snprintf_instead -DSWDS -DHL2_DLL -DUSES_SAVERESTORE -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/game/server -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 ../../game/server/generated_proto_hl2 ../../thirdparty/protobuf-2.6.1/src ./ ../../game/shared ../../utils/common ../../game/shared/econ ../../game/server/NextBot ../../game/shared/hl2 ./hl2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../../../game/hl2/bin/server.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/server.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../common/language.cpp \
    ../../common/randoverride.cpp \
    ../../common/steamid.cpp \
    ../../game/server/serverbenchmark_base.cpp \
    ../../game/server/vote_controller.cpp \
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
    ../../game/shared/hl2/survival_gamerules.cpp \
    ../../game/shared/igamesystem.cpp \
    ../../game/shared/interval.cpp \
    ../../game/shared/mapentities_shared.cpp \
    ../../game/shared/ModelSoundsCache.cpp \
    ../../game/shared/movevars_shared.cpp \
    ../../game/shared/mp_shareddefs.cpp \
    ../../game/shared/multiplay_gamerules.cpp \
    ../../game/shared/obstacle_pushaway.cpp \
    ../../game/shared/particlesystemquery.cpp \
    ../../game/shared/particle_parse.cpp \
    ../../game/shared/physics_main_shared.cpp \
    ../../game/shared/physics_saverestore.cpp \
    ../../game/shared/physics_shared.cpp \
    ../../game/shared/point_bonusmaps_accessor.cpp \
    ../../game/shared/point_posecontroller.cpp \
    ../../game/shared/precache_register.cpp \
    ../../game/shared/predictableid.cpp \
    ../../game/shared/props_shared.cpp \
    ../../game/shared/querycache.cpp \
    ../../game/shared/ragdoll_shared.cpp \
    ../../game/shared/rope_helpers.cpp \
    ../../game/shared/saverestore.cpp \
    ../../game/shared/SceneCache.cpp \
    ../../game/shared/sceneentity_shared.cpp \
    ../../game/shared/script_intro_shared.cpp \
    ../../game/shared/sequence_Transitioner.cpp \
    ../../game/shared/sheetsimulator.cpp \
    ../../game/shared/simtimer.cpp \
    ../../game/shared/singleplay_gamerules.cpp \
    ../../game/shared/SoundEmitterSystem.cpp \
    ../../game/shared/soundenvelope.cpp \
    ../../game/shared/Sprite.cpp \
    ../../game/shared/SpriteTrail.cpp \
    ../../game/shared/studio_shared.cpp \
    ../../game/shared/takedamageinfo.cpp \
    ../../game/shared/teamplay_gamerules.cpp \
    ../../game/shared/test_ehandle.cpp \
    ../../game/shared/usercmd.cpp \
    ../../game/shared/usermessages.cpp \
    ../../game/shared/util_shared.cpp \
    ../../game/shared/vehicle_viewblend_shared.cpp \
    ../../game/shared/voice_gamemgr.cpp \
    ../../game/shared/weapon_parse.cpp \
    ../../game/shared/weapon_parse_default.cpp \
    ../../game/shared/weapon_proficiency.cpp \
    ../../public/bone_setup.cpp \
    ../../public/collisionutils.cpp \
    ../../public/dt_send.cpp \
    ../../public/dt_utlvector_common.cpp \
    ../../public/dt_utlvector_send.cpp \
    ../../public/editor_sendcommand.cpp \
    ../../public/filesystem_helpers.cpp \
    ../../public/haptics/haptic_msgs.cpp \
    ../../public/interpolatortypes.cpp \
    ../../public/keyframe/keyframe.cpp \
    ../../public/map_utils.cpp \
    ../../public/networkvar.cpp \
    ../../public/registry.cpp \
    ../../public/rope_physics.cpp \
    ../../public/scratchpad3d.cpp \
    ../../public/ScratchPadUtils.cpp \
    ../../public/server_class.cpp \
    ../../public/simple_physics.cpp \
    ../../public/SoundParametersInternal.cpp \
    ../../public/stringregistry.cpp \
    ../../public/studio.cpp \
    ../../public/tier0/memoverride.cpp \
    ai_activity.cpp \
    ai_baseactor.cpp \
    ai_basehumanoid.cpp \
    ai_basenpc.cpp \
    ai_basenpc_flyer.cpp \
    ai_basenpc_flyer_new.cpp \
    ai_basenpc_movement.cpp \
    ai_basenpc_physicsflyer.cpp \
    ai_basenpc_schedule.cpp \
    ai_basenpc_squad.cpp \
    ai_behavior.cpp \
    ai_behavior_assault.cpp \
    ai_behavior_fear.cpp \
    ai_behavior_follow.cpp \
    ai_behavior_lead.cpp \
    ai_behavior_rappel.cpp \
    ai_behavior_standoff.cpp \
    ai_blended_movement.cpp \
    ai_concommands.cpp \
    ai_condition.cpp \
    AI_Criteria.cpp \
    ai_default.cpp \
    ai_dynamiclink.cpp \
    ai_event.cpp \
    ai_eventresponse.cpp \
    ai_goalentity.cpp \
    ai_hint.cpp \
    ai_hull.cpp \
    ai_initutils.cpp \
    AI_Interest_Target.cpp \
    ai_link.cpp \
    ai_localnavigator.cpp \
    ai_looktarget.cpp \
    ai_memory.cpp \
    ai_motor.cpp \
    ai_moveprobe.cpp \
    ai_moveshoot.cpp \
    ai_movesolver.cpp \
    ai_namespaces.cpp \
    ai_navigator.cpp \
    ai_network.cpp \
    ai_networkmanager.cpp \
    ai_node.cpp \
    ai_pathfinder.cpp \
    ai_planesolver.cpp \
    ai_playerally.cpp \
    ai_relationship.cpp \
    AI_ResponseSystem.cpp \
    ai_route.cpp \
    ai_saverestore.cpp \
    ai_schedule.cpp \
    ai_scriptconditions.cpp \
    ai_senses.cpp \
    ai_sentence.cpp \
    ai_speech.cpp \
    ai_speechfilter.cpp \
    ai_squad.cpp \
    ai_squadslot.cpp \
    ai_tacticalservices.cpp \
    ai_task.cpp \
    ai_trackpather.cpp \
    ai_utils.cpp \
    ai_waypoint.cpp \
    baseanimating.cpp \
    BaseAnimatingOverlay.cpp \
    basebludgeonweapon.cpp \
    basecombatcharacter.cpp \
    basecombatweapon.cpp \
    baseentity.cpp \
    baseflex.cpp \
    basegrenade_concussion.cpp \
    basegrenade_contact.cpp \
    basegrenade_timed.cpp \
    basemultiplayerplayer.cpp \
    basetempentity.cpp \
    baseviewmodel.cpp \
    base_gameinterface.cpp \
    base_transmit_proxy.cpp \
    bitstring.cpp \
    bmodels.cpp \
    buttons.cpp \
    cbase.cpp \
    client.cpp \
    colorcorrection.cpp \
    colorcorrectionvolume.cpp \
    CommentarySystem.cpp \
    controlentities.cpp \
    cplane.cpp \
    CRagdollMagnet.cpp \
    damagemodifier.cpp \
    doors.cpp \
    dynamiclight.cpp \
    effects.cpp \
    EffectsServer.cpp \
    entityblocker.cpp \
    EntityDissolve.cpp \
    EntityFlame.cpp \
    entitylist.cpp \
    EntityParticleTrail.cpp \
    entity_tools_server.cpp \
    EnvBeam.cpp \
    EnvFade.cpp \
    EnvHudHint.cpp \
    EnvLaser.cpp \
    EnvMessage.cpp \
    envmicrophone.cpp \
    EnvShake.cpp \
    EnvSpark.cpp \
    env_debughistory.cpp \
    env_effectsscript.cpp \
    env_entity_maker.cpp \
    env_particlescript.cpp \
    env_player_surface_trigger.cpp \
    env_projectedtexture.cpp \
    env_screenoverlay.cpp \
    env_texturetoggle.cpp \
    env_tonemap_controller.cpp \
    env_zoom.cpp \
    EventLog.cpp \
    event_tempentity_tester.cpp \
    explode.cpp \
    filters.cpp \
    fire.cpp \
    fire_smoke.cpp \
    fish.cpp \
    fogcontroller.cpp \
    fourwheelvehiclephysics.cpp \
    func_areaportal.cpp \
    func_areaportalbase.cpp \
    func_areaportalwindow.cpp \
    func_break.cpp \
    func_breakablesurf.cpp \
    func_dust.cpp \
    func_ladder_endpoint.cpp \
    func_lod.cpp \
    func_movelinear.cpp \
    func_occluder.cpp \
    func_reflective_glass.cpp \
    func_smokevolume.cpp \
    game.cpp \
    gamedll_replay.cpp \
    gamehandle.cpp \
    gameinterface.cpp \
    GameStats_BasicStatsFunctions.cpp \
    gametrace_dll.cpp \
    gameweaponmanager.cpp \
    game_ui.cpp \
    genericactor.cpp \
    genericmonster.cpp \
    gib.cpp \
    globals.cpp \
    globalstate.cpp \
    grenadethrown.cpp \
    guntarget.cpp \
    hierarchy.cpp \
    hl2/ai_allymanager.cpp \
    hl2/ai_behavior_actbusy.cpp \
    hl2/ai_behavior_functank.cpp \
    hl2/ai_behavior_holster.cpp \
    hl2/ai_behavior_operator.cpp \
    hl2/ai_behavior_police.cpp \
    hl2/ai_goal_police.cpp \
    hl2/ai_spotlight.cpp \
    hl2/antlion_dust.cpp \
    hl2/antlion_maker.cpp \
    hl2/ar2_explosion.cpp \
    hl2/basehlcombatweapon.cpp \
    hl2/cbasehelicopter.cpp \
    hl2/cbasespriteprojectile.cpp \
    hl2/citadel_effects.cpp \
    hl2/combine_mine.cpp \
    hl2/env_alyxemp.cpp \
    hl2/env_headcrabcanister.cpp \
    hl2/env_speaker.cpp \
    hl2/env_starfield.cpp \
    hl2/Func_Monitor.cpp \
    hl2/func_recharge.cpp \
    hl2/func_tank.cpp \
    hl2/grenade_ar2.cpp \
    hl2/grenade_beam.cpp \
    hl2/grenade_bugbait.cpp \
    hl2/grenade_frag.cpp \
    hl2/grenade_homer.cpp \
    hl2/grenade_pathfollower.cpp \
    hl2/hl2_ai_network.cpp \
    hl2/hl2_client.cpp \
    hl2/hl2_eventlog.cpp \
    hl2/hl2_gamestats.cpp \
    hl2/hl2_player.cpp \
    hl2/hl2_playerlocaldata.cpp \
    hl2/hl2_triggers.cpp \
    hl2/hl_playermove.cpp \
    hl2/info_darknessmode_lightsource.cpp \
    hl2/info_teleporter_countdown.cpp \
    hl2/item_ammo.cpp \
    hl2/item_battery.cpp \
    hl2/item_dynamic_resupply.cpp \
    hl2/item_healthkit.cpp \
    hl2/item_itemcrate.cpp \
    hl2/item_suit.cpp \
    hl2/look_door.cpp \
    hl2/monster_dummy.cpp \
    hl2/npc_alyx.cpp \
    hl2/npc_antlion.cpp \
    hl2/npc_antlionguard.cpp \
    hl2/npc_apcdriver.cpp \
    hl2/npc_attackchopper.cpp \
    hl2/npc_barnacle.cpp \
    hl2/npc_barney.cpp \
    hl2/npc_basescanner.cpp \
    hl2/npc_BaseZombie.cpp \
    hl2/npc_blob.cpp \
    hl2/npc_breen.cpp \
    hl2/npc_bullseye.cpp \
    hl2/npc_citizen17.cpp \
    hl2/npc_combine.cpp \
    hl2/npc_combinecamera.cpp \
    hl2/npc_combinedropship.cpp \
    hl2/npc_combinegunship.cpp \
    hl2/npc_combines.cpp \
    hl2/npc_cranedriver.cpp \
    hl2/npc_crow.cpp \
    hl2/npc_dog.cpp \
    hl2/npc_eli.cpp \
    hl2/npc_enemyfinder.cpp \
    hl2/npc_fastzombie.cpp \
    hl2/npc_fisherman.cpp \
    hl2/npc_gman.cpp \
    hl2/npc_headcrab.cpp \
    hl2/npc_ichthyosaur.cpp \
    hl2/npc_kleiner.cpp \
    hl2/npc_launcher.cpp \
    hl2/npc_manhack.cpp \
    hl2/npc_metropolice.cpp \
    hl2/npc_missiledefense.cpp \
    hl2/npc_monk.cpp \
    hl2/npc_mossman.cpp \
    hl2/npc_playercompanion.cpp \
    hl2/npc_PoisonZombie.cpp \
    hl2/npc_rollermine.cpp \
    hl2/npc_scanner.cpp \
    hl2/npc_stalker.cpp \
    hl2/npc_strider.cpp \
    hl2/npc_turret_ceiling.cpp \
    hl2/npc_turret_floor.cpp \
    hl2/npc_turret_ground.cpp \
    hl2/npc_vortigaunt_episodic.cpp \
    hl2/npc_zombie.cpp \
    hl2/point_apc_controller.cpp \
    hl2/prop_combine_ball.cpp \
    hl2/prop_thumper.cpp \
    hl2/proto_sniper.cpp \
    hl2/rotorwash.cpp \
    hl2/script_intro.cpp \
    hl2/te_gaussexplosion.cpp \
    hl2/vehicle_airboat.cpp \
    hl2/vehicle_apc.cpp \
    hl2/vehicle_cannon.cpp \
    hl2/vehicle_crane.cpp \
    hl2/vehicle_jeep.cpp \
    hl2/vehicle_prisoner_pod.cpp \
    hl2/vehicle_viewcontroller.cpp \
    hl2/weapon_357.cpp \
    hl2/weapon_alyxgun.cpp \
    hl2/weapon_annabelle.cpp \
    hl2/weapon_ar2.cpp \
    hl2/weapon_bugbait.cpp \
    hl2/weapon_cguard.cpp \
    hl2/weapon_citizenpackage.cpp \
    hl2/weapon_crossbow.cpp \
    hl2/weapon_crowbar.cpp \
    hl2/weapon_flaregun.cpp \
    hl2/weapon_frag.cpp \
    hl2/weapon_physcannon.cpp \
    hl2/weapon_pistol.cpp \
    hl2/weapon_rpg.cpp \
    hl2/weapon_shotgun.cpp \
    hl2/weapon_smg1.cpp \
    hl2/weapon_stunstick.cpp \
    hltvdirector.cpp \
    h_ai.cpp \
    h_cycler.cpp \
    h_export.cpp \
    info_camera_link.cpp \
    info_overlay_accessor.cpp \
    init_factory.cpp \
    intermission.cpp \
    item_world.cpp \
    lightglow.cpp \
    lights.cpp \
    logicauto.cpp \
    logicentities.cpp \
    logicrelay.cpp \
    logic_achievement.cpp \
    logic_measure_movement.cpp \
    logic_navigation.cpp \
    mapentities.cpp \
    maprules.cpp \
    MaterialModifyControl.cpp \
    message_entity.cpp \
    modelentities.cpp \
    monstermaker.cpp \
    movehelper_server.cpp \
    movement.cpp \
    movie_explosion.cpp \
    ndebugoverlay.cpp \
    npc_talker.cpp \
    npc_vehicledriver.cpp \
    particle_fire.cpp \
    particle_light.cpp \
    particle_smokegrenade.cpp \
    particle_system.cpp \
    pathcorner.cpp \
    pathtrack.cpp \
    physconstraint.cpp \
    physics.cpp \
    physics_bone_follower.cpp \
    physics_cannister.cpp \
    physics_fx.cpp \
    physics_impact_damage.cpp \
    physics_main.cpp \
    physics_npc_solver.cpp \
    physics_prop_ragdoll.cpp \
    physobj.cpp \
    phys_controller.cpp \
    plasma.cpp \
    player.cpp \
    playerinfomanager.cpp \
    playerlocaldata.cpp \
    player_command.cpp \
    player_lagcompensation.cpp \
    player_pickup.cpp \
    player_resource.cpp \
    plugin_check.cpp \
    pointanglesensor.cpp \
    PointAngularVelocitySensor.cpp \
    pointhurt.cpp \
    pointteleport.cpp \
    point_camera.cpp \
    point_devshot_camera.cpp \
    point_playermoveconstraint.cpp \
    point_spotlight.cpp \
    point_template.cpp \
    props.cpp \
    RagdollBoogie.cpp \
    ragdoll_manager.cpp \
    recipientfilter.cpp \
    rope.cpp \
    saverestore_gamedll.cpp \
    sceneentity.cpp \
    scratchpad_gamedll_helpers.cpp \
    scripted.cpp \
    scriptedtarget.cpp \
    sendproxy.cpp \
    ServerNetworkProperty.cpp \
    shadowcontrol.cpp \
    SkyCamera.cpp \
    slideshow_display.cpp \
    smokestack.cpp \
    smoke_trail.cpp \
    sound.cpp \
    soundent.cpp \
    soundscape.cpp \
    soundscape_system.cpp \
    spotlightend.cpp \
    sprite_perfmonitor.cpp \
    stdafx.cpp \
    steamjet.cpp \
    subs.cpp \
    sun.cpp \
    tactical_mission.cpp \
    tanktrain.cpp \
    te.cpp \
    team.cpp \
    team_spawnpoint.cpp \
    TemplateEntities.cpp \
    tempmonster.cpp \
    tesla.cpp \
    testfunctions.cpp \
    testtraceline.cpp \
    test_proxytoggle.cpp \
    test_stressentities.cpp \
    textstatsmgr.cpp \
    te_armorricochet.cpp \
    te_basebeam.cpp \
    te_beamentpoint.cpp \
    te_beaments.cpp \
    te_beamfollow.cpp \
    te_beamlaser.cpp \
    te_beampoints.cpp \
    te_beamring.cpp \
    te_beamringpoint.cpp \
    te_beamspline.cpp \
    te_bloodsprite.cpp \
    te_bloodstream.cpp \
    te_breakmodel.cpp \
    te_bspdecal.cpp \
    te_bubbles.cpp \
    te_bubbletrail.cpp \
    te_clientprojectile.cpp \
    te_decal.cpp \
    te_dynamiclight.cpp \
    te_effect_dispatch.cpp \
    te_energysplash.cpp \
    te_explosion.cpp \
    te_fizz.cpp \
    te_footprintdecal.cpp \
    te_glassshatter.cpp \
    te_glowsprite.cpp \
    te_impact.cpp \
    te_killplayerattachments.cpp \
    te_largefunnel.cpp \
    te_muzzleflash.cpp \
    te_particlesystem.cpp \
    te_physicsprop.cpp \
    te_playerdecal.cpp \
    te_projecteddecal.cpp \
    te_showline.cpp \
    te_smoke.cpp \
    te_sparks.cpp \
    te_sprite.cpp \
    te_spritespray.cpp \
    te_worlddecal.cpp \
    timedeventmgr.cpp \
    toolframework_server.cpp \
    trains.cpp \
    triggers.cpp \
    util.cpp \
    variant_t.cpp \
    vehicle_base.cpp \
    vehicle_baseserver.cpp \
    vehicle_choreo_generic.cpp \
    vguiscreen.cpp \
    waterbullet.cpp \
    WaterLODControl.cpp \
    wcedit.cpp \
    weapon_cubemap.cpp \
    weight_button.cpp \
    world.cpp \


LIBFILES = \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/choreoobjects.a \
    ../../lib/public/linux32/dmxloader.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/particles.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \
    -L../../lib/public/linux32 -ltier0 \
    -L../../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../../lib/public/linux32/choreoobjects.a \
    ../../lib/public/linux32/dmxloader.a \
    ../../lib/public/linux32/libtier0.so \
    ../../lib/public/linux32/libvstdlib.so \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/particles.a \
    ../../lib/public/linux32/tier1.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/language.P
endif

$(OBJ_DIR)/language.o : $(abspath ../../common/language.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/randoverride.P
endif

$(OBJ_DIR)/randoverride.o : $(abspath ../../common/randoverride.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamid.P
endif

$(OBJ_DIR)/steamid.o : $(abspath ../../common/steamid.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/serverbenchmark_base.P
endif

$(OBJ_DIR)/serverbenchmark_base.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/serverbenchmark_base.o : $(abspath ../../game/server/serverbenchmark_base.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vote_controller.P
endif

$(OBJ_DIR)/vote_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vote_controller.o : $(abspath ../../game/server/vote_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievementmgr.P
endif

$(OBJ_DIR)/achievementmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievementmgr.o : $(abspath ../../game/shared/achievementmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievements_hlx.P
endif

$(OBJ_DIR)/achievements_hlx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievements_hlx.o : $(abspath ../../game/shared/achievements_hlx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievement_saverestore.P
endif

$(OBJ_DIR)/achievement_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievement_saverestore.o : $(abspath ../../game/shared/achievement_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/activitylist.P
endif

$(OBJ_DIR)/activitylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/activitylist.o : $(abspath ../../game/shared/activitylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ammodef.P
endif

$(OBJ_DIR)/ammodef.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ammodef.o : $(abspath ../../game/shared/ammodef.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/animation.P
endif

$(OBJ_DIR)/animation.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/animation.o : $(abspath ../../game/shared/animation.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseachievement.P
endif

$(OBJ_DIR)/baseachievement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseachievement.o : $(abspath ../../game/shared/baseachievement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatcharacter_shared.P
endif

$(OBJ_DIR)/basecombatcharacter_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatcharacter_shared.o : $(abspath ../../game/shared/basecombatcharacter_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatweapon_shared.P
endif

$(OBJ_DIR)/basecombatweapon_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatweapon_shared.o : $(abspath ../../game/shared/basecombatweapon_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseentity_shared.P
endif

$(OBJ_DIR)/baseentity_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseentity_shared.o : $(abspath ../../game/shared/baseentity_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_shared.P
endif

$(OBJ_DIR)/basegrenade_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_shared.o : $(abspath ../../game/shared/basegrenade_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseparticleentity.P
endif

$(OBJ_DIR)/baseparticleentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseparticleentity.o : $(abspath ../../game/shared/baseparticleentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseplayer_shared.P
endif

$(OBJ_DIR)/baseplayer_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseplayer_shared.o : $(abspath ../../game/shared/baseplayer_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseprojectile.P
endif

$(OBJ_DIR)/baseprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseprojectile.o : $(abspath ../../game/shared/baseprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseviewmodel_shared.P
endif

$(OBJ_DIR)/baseviewmodel_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseviewmodel_shared.o : $(abspath ../../game/shared/baseviewmodel_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_playeranimstate.P
endif

$(OBJ_DIR)/base_playeranimstate.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/base_playeranimstate.o : $(abspath ../../game/shared/base_playeranimstate.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/beam_shared.P
endif

$(OBJ_DIR)/beam_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/beam_shared.o : $(abspath ../../game/shared/beam_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionproperty.P
endif

$(OBJ_DIR)/collisionproperty.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/collisionproperty.o : $(abspath ../../game/shared/collisionproperty.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/death_pose.P
endif

$(OBJ_DIR)/death_pose.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/death_pose.o : $(abspath ../../game/shared/death_pose.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/debugoverlay_shared.P
endif

$(OBJ_DIR)/debugoverlay_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/debugoverlay_shared.o : $(abspath ../../game/shared/debugoverlay_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/decals.P
endif

$(OBJ_DIR)/decals.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/decals.o : $(abspath ../../game/shared/decals.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/effect_dispatch_data.P
endif

$(OBJ_DIR)/effect_dispatch_data.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/effect_dispatch_data.o : $(abspath ../../game/shared/effect_dispatch_data.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ehandle.P
endif

$(OBJ_DIR)/ehandle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ehandle.o : $(abspath ../../game/shared/ehandle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entitylist_base.P
endif

$(OBJ_DIR)/entitylist_base.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entitylist_base.o : $(abspath ../../game/shared/entitylist_base.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityParticleTrail_Shared.P
endif

$(OBJ_DIR)/EntityParticleTrail_Shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityParticleTrail_Shared.o : $(abspath ../../game/shared/EntityParticleTrail_Shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_detail_controller.P
endif

$(OBJ_DIR)/env_detail_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_detail_controller.o : $(abspath ../../game/shared/env_detail_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_wind_shared.P
endif

$(OBJ_DIR)/env_wind_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_wind_shared.o : $(abspath ../../game/shared/env_wind_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/eventlist.P
endif

$(OBJ_DIR)/eventlist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/eventlist.o : $(abspath ../../game/shared/eventlist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_ladder.P
endif

$(OBJ_DIR)/func_ladder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_ladder.o : $(abspath ../../game/shared/func_ladder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamemovement.P
endif

$(OBJ_DIR)/gamemovement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamemovement.o : $(abspath ../../game/shared/gamemovement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamerules.P
endif

$(OBJ_DIR)/gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamerules.o : $(abspath ../../game/shared/gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamerules_register.P
endif

$(OBJ_DIR)/gamerules_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamerules_register.o : $(abspath ../../game/shared/gamerules_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameStats.P
endif

$(OBJ_DIR)/GameStats.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/GameStats.o : $(abspath ../../game/shared/GameStats.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamestringpool.P
endif

$(OBJ_DIR)/gamestringpool.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamestringpool.o : $(abspath ../../game/shared/gamestringpool.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamevars_shared.P
endif

$(OBJ_DIR)/gamevars_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamevars_shared.o : $(abspath ../../game/shared/gamevars_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hintmessage.P
endif

$(OBJ_DIR)/hintmessage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hintmessage.o : $(abspath ../../game/shared/hintmessage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hintsystem.P
endif

$(OBJ_DIR)/hintsystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hintsystem.o : $(abspath ../../game/shared/hintsystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievements_hl2.P
endif

$(OBJ_DIR)/achievements_hl2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/achievements_hl2.o : $(abspath ../../game/shared/hl2/achievements_hl2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basehlcombatweapon_shared.P
endif

$(OBJ_DIR)/basehlcombatweapon_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basehlcombatweapon_shared.o : $(abspath ../../game/shared/hl2/basehlcombatweapon_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_headcrabcanister_shared.P
endif

$(OBJ_DIR)/env_headcrabcanister_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_headcrabcanister_shared.o : $(abspath ../../game/shared/hl2/env_headcrabcanister_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_gamerules.P
endif

$(OBJ_DIR)/hl2_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_gamerules.o : $(abspath ../../game/shared/hl2/hl2_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_usermessages.P
endif

$(OBJ_DIR)/hl2_usermessages.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_usermessages.o : $(abspath ../../game/shared/hl2/hl2_usermessages.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_gamemovement.P
endif

$(OBJ_DIR)/hl_gamemovement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_gamemovement.o : $(abspath ../../game/shared/hl2/hl_gamemovement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/survival_gamerules.P
endif

$(OBJ_DIR)/survival_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/survival_gamerules.o : $(abspath ../../game/shared/hl2/survival_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/igamesystem.P
endif

$(OBJ_DIR)/igamesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/igamesystem.o : $(abspath ../../game/shared/igamesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interval.P
endif

$(OBJ_DIR)/interval.o : $(abspath ../../game/shared/interval.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mapentities_shared.P
endif

$(OBJ_DIR)/mapentities_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mapentities_shared.o : $(abspath ../../game/shared/mapentities_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ModelSoundsCache.P
endif

$(OBJ_DIR)/ModelSoundsCache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ModelSoundsCache.o : $(abspath ../../game/shared/ModelSoundsCache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movevars_shared.P
endif

$(OBJ_DIR)/movevars_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movevars_shared.o : $(abspath ../../game/shared/movevars_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mp_shareddefs.P
endif

$(OBJ_DIR)/mp_shareddefs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mp_shareddefs.o : $(abspath ../../game/shared/mp_shareddefs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/multiplay_gamerules.P
endif

$(OBJ_DIR)/multiplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/multiplay_gamerules.o : $(abspath ../../game/shared/multiplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/obstacle_pushaway.P
endif

$(OBJ_DIR)/obstacle_pushaway.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/obstacle_pushaway.o : $(abspath ../../game/shared/obstacle_pushaway.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particlesystemquery.P
endif

$(OBJ_DIR)/particlesystemquery.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particlesystemquery.o : $(abspath ../../game/shared/particlesystemquery.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_parse.P
endif

$(OBJ_DIR)/particle_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_parse.o : $(abspath ../../game/shared/particle_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_main_shared.P
endif

$(OBJ_DIR)/physics_main_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_main_shared.o : $(abspath ../../game/shared/physics_main_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_saverestore.P
endif

$(OBJ_DIR)/physics_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_saverestore.o : $(abspath ../../game/shared/physics_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_shared.P
endif

$(OBJ_DIR)/physics_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_shared.o : $(abspath ../../game/shared/physics_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_bonusmaps_accessor.P
endif

$(OBJ_DIR)/point_bonusmaps_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_bonusmaps_accessor.o : $(abspath ../../game/shared/point_bonusmaps_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_posecontroller.P
endif

$(OBJ_DIR)/point_posecontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_posecontroller.o : $(abspath ../../game/shared/point_posecontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/precache_register.P
endif

$(OBJ_DIR)/precache_register.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/precache_register.o : $(abspath ../../game/shared/precache_register.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/predictableid.P
endif

$(OBJ_DIR)/predictableid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/predictableid.o : $(abspath ../../game/shared/predictableid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/props_shared.P
endif

$(OBJ_DIR)/props_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/props_shared.o : $(abspath ../../game/shared/props_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/querycache.P
endif

$(OBJ_DIR)/querycache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/querycache.o : $(abspath ../../game/shared/querycache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll_shared.P
endif

$(OBJ_DIR)/ragdoll_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ragdoll_shared.o : $(abspath ../../game/shared/ragdoll_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope_helpers.P
endif

$(OBJ_DIR)/rope_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/rope_helpers.o : $(abspath ../../game/shared/rope_helpers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/saverestore.P
endif

$(OBJ_DIR)/saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/saverestore.o : $(abspath ../../game/shared/saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SceneCache.P
endif

$(OBJ_DIR)/SceneCache.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SceneCache.o : $(abspath ../../game/shared/SceneCache.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sceneentity_shared.P
endif

$(OBJ_DIR)/sceneentity_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sceneentity_shared.o : $(abspath ../../game/shared/sceneentity_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/script_intro_shared.P
endif

$(OBJ_DIR)/script_intro_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/script_intro_shared.o : $(abspath ../../game/shared/script_intro_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sequence_Transitioner.P
endif

$(OBJ_DIR)/sequence_Transitioner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sequence_Transitioner.o : $(abspath ../../game/shared/sequence_Transitioner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sheetsimulator.P
endif

$(OBJ_DIR)/sheetsimulator.o : $(abspath ../../game/shared/sheetsimulator.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simtimer.P
endif

$(OBJ_DIR)/simtimer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/simtimer.o : $(abspath ../../game/shared/simtimer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/singleplay_gamerules.P
endif

$(OBJ_DIR)/singleplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/singleplay_gamerules.o : $(abspath ../../game/shared/singleplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SoundEmitterSystem.P
endif

$(OBJ_DIR)/SoundEmitterSystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SoundEmitterSystem.o : $(abspath ../../game/shared/SoundEmitterSystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundenvelope.P
endif

$(OBJ_DIR)/soundenvelope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundenvelope.o : $(abspath ../../game/shared/soundenvelope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Sprite.P
endif

$(OBJ_DIR)/Sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/Sprite.o : $(abspath ../../game/shared/Sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SpriteTrail.P
endif

$(OBJ_DIR)/SpriteTrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SpriteTrail.o : $(abspath ../../game/shared/SpriteTrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio_shared.P
endif

$(OBJ_DIR)/studio_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/studio_shared.o : $(abspath ../../game/shared/studio_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/takedamageinfo.P
endif

$(OBJ_DIR)/takedamageinfo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/takedamageinfo.o : $(abspath ../../game/shared/takedamageinfo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/teamplay_gamerules.P
endif

$(OBJ_DIR)/teamplay_gamerules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/teamplay_gamerules.o : $(abspath ../../game/shared/teamplay_gamerules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/test_ehandle.P
endif

$(OBJ_DIR)/test_ehandle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/test_ehandle.o : $(abspath ../../game/shared/test_ehandle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/usercmd.P
endif

$(OBJ_DIR)/usercmd.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/usercmd.o : $(abspath ../../game/shared/usercmd.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/usermessages.P
endif

$(OBJ_DIR)/usermessages.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/usermessages.o : $(abspath ../../game/shared/usermessages.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/util_shared.P
endif

$(OBJ_DIR)/util_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/util_shared.o : $(abspath ../../game/shared/util_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_viewblend_shared.P
endif

$(OBJ_DIR)/vehicle_viewblend_shared.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_viewblend_shared.o : $(abspath ../../game/shared/vehicle_viewblend_shared.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/voice_gamemgr.P
endif

$(OBJ_DIR)/voice_gamemgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/voice_gamemgr.o : $(abspath ../../game/shared/voice_gamemgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_parse.P
endif

$(OBJ_DIR)/weapon_parse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_parse.o : $(abspath ../../game/shared/weapon_parse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_parse_default.P
endif

$(OBJ_DIR)/weapon_parse_default.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_parse_default.o : $(abspath ../../game/shared/weapon_parse_default.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_proficiency.P
endif

$(OBJ_DIR)/weapon_proficiency.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_proficiency.o : $(abspath ../../game/shared/weapon_proficiency.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bone_setup.P
endif

$(OBJ_DIR)/bone_setup.o : $(abspath ../../public/bone_setup.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/collisionutils.P
endif

$(OBJ_DIR)/collisionutils.o : $(abspath ../../public/collisionutils.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_send.P
endif

$(OBJ_DIR)/dt_send.o : $(abspath ../../public/dt_send.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_common.P
endif

$(OBJ_DIR)/dt_utlvector_common.o : $(abspath ../../public/dt_utlvector_common.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dt_utlvector_send.P
endif

$(OBJ_DIR)/dt_utlvector_send.o : $(abspath ../../public/dt_utlvector_send.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/editor_sendcommand.P
endif

$(OBJ_DIR)/editor_sendcommand.o : $(abspath ../../public/editor_sendcommand.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../../public/filesystem_helpers.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/haptic_msgs.P
endif

$(OBJ_DIR)/haptic_msgs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/haptic_msgs.o : $(abspath ../../public/haptics/haptic_msgs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/interpolatortypes.P
endif

$(OBJ_DIR)/interpolatortypes.o : $(abspath ../../public/interpolatortypes.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/keyframe.P
endif

$(OBJ_DIR)/keyframe.o : $(abspath ../../public/keyframe/keyframe.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/map_utils.P
endif

$(OBJ_DIR)/map_utils.o : $(abspath ../../public/map_utils.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/networkvar.P
endif

$(OBJ_DIR)/networkvar.o : $(abspath ../../public/networkvar.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/registry.P
endif

$(OBJ_DIR)/registry.o : $(abspath ../../public/registry.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope_physics.P
endif

$(OBJ_DIR)/rope_physics.o : $(abspath ../../public/rope_physics.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scratchpad3d.P
endif

$(OBJ_DIR)/scratchpad3d.o : $(abspath ../../public/scratchpad3d.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScratchPadUtils.P
endif

$(OBJ_DIR)/ScratchPadUtils.o : $(abspath ../../public/ScratchPadUtils.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/server_class.P
endif

$(OBJ_DIR)/server_class.o : $(abspath ../../public/server_class.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/simple_physics.P
endif

$(OBJ_DIR)/simple_physics.o : $(abspath ../../public/simple_physics.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SoundParametersInternal.P
endif

$(OBJ_DIR)/SoundParametersInternal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SoundParametersInternal.o : $(abspath ../../public/SoundParametersInternal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stringregistry.P
endif

$(OBJ_DIR)/stringregistry.o : $(abspath ../../public/stringregistry.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/studio.P
endif

$(OBJ_DIR)/studio.o : $(abspath ../../public/studio.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_activity.P
endif

$(OBJ_DIR)/ai_activity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_activity.o : $(abspath ai_activity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_baseactor.P
endif

$(OBJ_DIR)/ai_baseactor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_baseactor.o : $(abspath ai_baseactor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basehumanoid.P
endif

$(OBJ_DIR)/ai_basehumanoid.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basehumanoid.o : $(abspath ai_basehumanoid.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc.P
endif

$(OBJ_DIR)/ai_basenpc.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc.o : $(abspath ai_basenpc.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_flyer.P
endif

$(OBJ_DIR)/ai_basenpc_flyer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_flyer.o : $(abspath ai_basenpc_flyer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_flyer_new.P
endif

$(OBJ_DIR)/ai_basenpc_flyer_new.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_flyer_new.o : $(abspath ai_basenpc_flyer_new.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_movement.P
endif

$(OBJ_DIR)/ai_basenpc_movement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_movement.o : $(abspath ai_basenpc_movement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_physicsflyer.P
endif

$(OBJ_DIR)/ai_basenpc_physicsflyer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_physicsflyer.o : $(abspath ai_basenpc_physicsflyer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_schedule.P
endif

$(OBJ_DIR)/ai_basenpc_schedule.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_schedule.o : $(abspath ai_basenpc_schedule.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_basenpc_squad.P
endif

$(OBJ_DIR)/ai_basenpc_squad.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_basenpc_squad.o : $(abspath ai_basenpc_squad.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior.P
endif

$(OBJ_DIR)/ai_behavior.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior.o : $(abspath ai_behavior.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_assault.P
endif

$(OBJ_DIR)/ai_behavior_assault.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_assault.o : $(abspath ai_behavior_assault.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_fear.P
endif

$(OBJ_DIR)/ai_behavior_fear.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_fear.o : $(abspath ai_behavior_fear.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_follow.P
endif

$(OBJ_DIR)/ai_behavior_follow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_follow.o : $(abspath ai_behavior_follow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_lead.P
endif

$(OBJ_DIR)/ai_behavior_lead.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_lead.o : $(abspath ai_behavior_lead.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_rappel.P
endif

$(OBJ_DIR)/ai_behavior_rappel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_rappel.o : $(abspath ai_behavior_rappel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_standoff.P
endif

$(OBJ_DIR)/ai_behavior_standoff.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_standoff.o : $(abspath ai_behavior_standoff.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_blended_movement.P
endif

$(OBJ_DIR)/ai_blended_movement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_blended_movement.o : $(abspath ai_blended_movement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_concommands.P
endif

$(OBJ_DIR)/ai_concommands.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_concommands.o : $(abspath ai_concommands.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_condition.P
endif

$(OBJ_DIR)/ai_condition.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_condition.o : $(abspath ai_condition.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AI_Criteria.P
endif

$(OBJ_DIR)/AI_Criteria.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/AI_Criteria.o : $(abspath AI_Criteria.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_default.P
endif

$(OBJ_DIR)/ai_default.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_default.o : $(abspath ai_default.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_dynamiclink.P
endif

$(OBJ_DIR)/ai_dynamiclink.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_dynamiclink.o : $(abspath ai_dynamiclink.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_event.P
endif

$(OBJ_DIR)/ai_event.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_event.o : $(abspath ai_event.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_eventresponse.P
endif

$(OBJ_DIR)/ai_eventresponse.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_eventresponse.o : $(abspath ai_eventresponse.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_goalentity.P
endif

$(OBJ_DIR)/ai_goalentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_goalentity.o : $(abspath ai_goalentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_hint.P
endif

$(OBJ_DIR)/ai_hint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_hint.o : $(abspath ai_hint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_hull.P
endif

$(OBJ_DIR)/ai_hull.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_hull.o : $(abspath ai_hull.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_initutils.P
endif

$(OBJ_DIR)/ai_initutils.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_initutils.o : $(abspath ai_initutils.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AI_Interest_Target.P
endif

$(OBJ_DIR)/AI_Interest_Target.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/AI_Interest_Target.o : $(abspath AI_Interest_Target.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_link.P
endif

$(OBJ_DIR)/ai_link.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_link.o : $(abspath ai_link.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_localnavigator.P
endif

$(OBJ_DIR)/ai_localnavigator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_localnavigator.o : $(abspath ai_localnavigator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_looktarget.P
endif

$(OBJ_DIR)/ai_looktarget.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_looktarget.o : $(abspath ai_looktarget.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_memory.P
endif

$(OBJ_DIR)/ai_memory.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_memory.o : $(abspath ai_memory.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_motor.P
endif

$(OBJ_DIR)/ai_motor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_motor.o : $(abspath ai_motor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_moveprobe.P
endif

$(OBJ_DIR)/ai_moveprobe.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_moveprobe.o : $(abspath ai_moveprobe.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_moveshoot.P
endif

$(OBJ_DIR)/ai_moveshoot.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_moveshoot.o : $(abspath ai_moveshoot.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_movesolver.P
endif

$(OBJ_DIR)/ai_movesolver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_movesolver.o : $(abspath ai_movesolver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_namespaces.P
endif

$(OBJ_DIR)/ai_namespaces.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_namespaces.o : $(abspath ai_namespaces.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_navigator.P
endif

$(OBJ_DIR)/ai_navigator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_navigator.o : $(abspath ai_navigator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_network.P
endif

$(OBJ_DIR)/ai_network.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_network.o : $(abspath ai_network.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_networkmanager.P
endif

$(OBJ_DIR)/ai_networkmanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_networkmanager.o : $(abspath ai_networkmanager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_node.P
endif

$(OBJ_DIR)/ai_node.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_node.o : $(abspath ai_node.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_pathfinder.P
endif

$(OBJ_DIR)/ai_pathfinder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_pathfinder.o : $(abspath ai_pathfinder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_planesolver.P
endif

$(OBJ_DIR)/ai_planesolver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_planesolver.o : $(abspath ai_planesolver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_playerally.P
endif

$(OBJ_DIR)/ai_playerally.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_playerally.o : $(abspath ai_playerally.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_relationship.P
endif

$(OBJ_DIR)/ai_relationship.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_relationship.o : $(abspath ai_relationship.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AI_ResponseSystem.P
endif

$(OBJ_DIR)/AI_ResponseSystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/AI_ResponseSystem.o : $(abspath AI_ResponseSystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_route.P
endif

$(OBJ_DIR)/ai_route.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_route.o : $(abspath ai_route.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_saverestore.P
endif

$(OBJ_DIR)/ai_saverestore.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_saverestore.o : $(abspath ai_saverestore.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_schedule.P
endif

$(OBJ_DIR)/ai_schedule.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_schedule.o : $(abspath ai_schedule.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_scriptconditions.P
endif

$(OBJ_DIR)/ai_scriptconditions.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_scriptconditions.o : $(abspath ai_scriptconditions.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_senses.P
endif

$(OBJ_DIR)/ai_senses.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_senses.o : $(abspath ai_senses.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_sentence.P
endif

$(OBJ_DIR)/ai_sentence.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_sentence.o : $(abspath ai_sentence.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_speech.P
endif

$(OBJ_DIR)/ai_speech.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_speech.o : $(abspath ai_speech.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_speechfilter.P
endif

$(OBJ_DIR)/ai_speechfilter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_speechfilter.o : $(abspath ai_speechfilter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_squad.P
endif

$(OBJ_DIR)/ai_squad.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_squad.o : $(abspath ai_squad.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_squadslot.P
endif

$(OBJ_DIR)/ai_squadslot.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_squadslot.o : $(abspath ai_squadslot.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_tacticalservices.P
endif

$(OBJ_DIR)/ai_tacticalservices.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_tacticalservices.o : $(abspath ai_tacticalservices.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_task.P
endif

$(OBJ_DIR)/ai_task.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_task.o : $(abspath ai_task.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_trackpather.P
endif

$(OBJ_DIR)/ai_trackpather.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_trackpather.o : $(abspath ai_trackpather.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_utils.P
endif

$(OBJ_DIR)/ai_utils.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_utils.o : $(abspath ai_utils.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_waypoint.P
endif

$(OBJ_DIR)/ai_waypoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_waypoint.o : $(abspath ai_waypoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseanimating.P
endif

$(OBJ_DIR)/baseanimating.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseanimating.o : $(abspath baseanimating.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseAnimatingOverlay.P
endif

$(OBJ_DIR)/BaseAnimatingOverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/BaseAnimatingOverlay.o : $(abspath BaseAnimatingOverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basebludgeonweapon.P
endif

$(OBJ_DIR)/basebludgeonweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basebludgeonweapon.o : $(abspath basebludgeonweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatcharacter.P
endif

$(OBJ_DIR)/basecombatcharacter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatcharacter.o : $(abspath basecombatcharacter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basecombatweapon.P
endif

$(OBJ_DIR)/basecombatweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basecombatweapon.o : $(abspath basecombatweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseentity.P
endif

$(OBJ_DIR)/baseentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseentity.o : $(abspath baseentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseflex.P
endif

$(OBJ_DIR)/baseflex.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseflex.o : $(abspath baseflex.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_concussion.P
endif

$(OBJ_DIR)/basegrenade_concussion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_concussion.o : $(abspath basegrenade_concussion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_contact.P
endif

$(OBJ_DIR)/basegrenade_contact.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_contact.o : $(abspath basegrenade_contact.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basegrenade_timed.P
endif

$(OBJ_DIR)/basegrenade_timed.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basegrenade_timed.o : $(abspath basegrenade_timed.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basemultiplayerplayer.P
endif

$(OBJ_DIR)/basemultiplayerplayer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basemultiplayerplayer.o : $(abspath basemultiplayerplayer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basetempentity.P
endif

$(OBJ_DIR)/basetempentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basetempentity.o : $(abspath basetempentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baseviewmodel.P
endif

$(OBJ_DIR)/baseviewmodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/baseviewmodel.o : $(abspath baseviewmodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_gameinterface.P
endif

$(OBJ_DIR)/base_gameinterface.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/base_gameinterface.o : $(abspath base_gameinterface.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/base_transmit_proxy.P
endif

$(OBJ_DIR)/base_transmit_proxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/base_transmit_proxy.o : $(abspath base_transmit_proxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bitstring.P
endif

$(OBJ_DIR)/bitstring.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bitstring.o : $(abspath bitstring.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/bmodels.P
endif

$(OBJ_DIR)/bmodels.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/bmodels.o : $(abspath bmodels.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/buttons.P
endif

$(OBJ_DIR)/buttons.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/buttons.o : $(abspath buttons.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cbase.P
endif

$(OBJ_DIR)/cbase.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cbase.o : $(abspath cbase.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/client.P
endif

$(OBJ_DIR)/client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/client.o : $(abspath client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrection.P
endif

$(OBJ_DIR)/colorcorrection.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/colorcorrection.o : $(abspath colorcorrection.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/colorcorrectionvolume.P
endif

$(OBJ_DIR)/colorcorrectionvolume.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/colorcorrectionvolume.o : $(abspath colorcorrectionvolume.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CommentarySystem.P
endif

$(OBJ_DIR)/CommentarySystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/CommentarySystem.o : $(abspath CommentarySystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/controlentities.P
endif

$(OBJ_DIR)/controlentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/controlentities.o : $(abspath controlentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cplane.P
endif

$(OBJ_DIR)/cplane.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cplane.o : $(abspath cplane.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CRagdollMagnet.P
endif

$(OBJ_DIR)/CRagdollMagnet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/CRagdollMagnet.o : $(abspath CRagdollMagnet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/damagemodifier.P
endif

$(OBJ_DIR)/damagemodifier.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/damagemodifier.o : $(abspath damagemodifier.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/doors.P
endif

$(OBJ_DIR)/doors.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/doors.o : $(abspath doors.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dynamiclight.P
endif

$(OBJ_DIR)/dynamiclight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/dynamiclight.o : $(abspath dynamiclight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/effects.P
endif

$(OBJ_DIR)/effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/effects.o : $(abspath effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EffectsServer.P
endif

$(OBJ_DIR)/EffectsServer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EffectsServer.o : $(abspath EffectsServer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entityblocker.P
endif

$(OBJ_DIR)/entityblocker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entityblocker.o : $(abspath entityblocker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityDissolve.P
endif

$(OBJ_DIR)/EntityDissolve.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityDissolve.o : $(abspath EntityDissolve.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityFlame.P
endif

$(OBJ_DIR)/EntityFlame.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityFlame.o : $(abspath EntityFlame.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entitylist.P
endif

$(OBJ_DIR)/entitylist.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entitylist.o : $(abspath entitylist.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EntityParticleTrail.P
endif

$(OBJ_DIR)/EntityParticleTrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EntityParticleTrail.o : $(abspath EntityParticleTrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/entity_tools_server.P
endif

$(OBJ_DIR)/entity_tools_server.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/entity_tools_server.o : $(abspath entity_tools_server.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvBeam.P
endif

$(OBJ_DIR)/EnvBeam.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvBeam.o : $(abspath EnvBeam.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvFade.P
endif

$(OBJ_DIR)/EnvFade.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvFade.o : $(abspath EnvFade.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvHudHint.P
endif

$(OBJ_DIR)/EnvHudHint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvHudHint.o : $(abspath EnvHudHint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvLaser.P
endif

$(OBJ_DIR)/EnvLaser.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvLaser.o : $(abspath EnvLaser.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvMessage.P
endif

$(OBJ_DIR)/EnvMessage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvMessage.o : $(abspath EnvMessage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/envmicrophone.P
endif

$(OBJ_DIR)/envmicrophone.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/envmicrophone.o : $(abspath envmicrophone.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvShake.P
endif

$(OBJ_DIR)/EnvShake.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvShake.o : $(abspath EnvShake.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EnvSpark.P
endif

$(OBJ_DIR)/EnvSpark.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EnvSpark.o : $(abspath EnvSpark.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_debughistory.P
endif

$(OBJ_DIR)/env_debughistory.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_debughistory.o : $(abspath env_debughistory.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_effectsscript.P
endif

$(OBJ_DIR)/env_effectsscript.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_effectsscript.o : $(abspath env_effectsscript.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_entity_maker.P
endif

$(OBJ_DIR)/env_entity_maker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_entity_maker.o : $(abspath env_entity_maker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_particlescript.P
endif

$(OBJ_DIR)/env_particlescript.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_particlescript.o : $(abspath env_particlescript.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_player_surface_trigger.P
endif

$(OBJ_DIR)/env_player_surface_trigger.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_player_surface_trigger.o : $(abspath env_player_surface_trigger.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_projectedtexture.P
endif

$(OBJ_DIR)/env_projectedtexture.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_projectedtexture.o : $(abspath env_projectedtexture.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_screenoverlay.P
endif

$(OBJ_DIR)/env_screenoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_screenoverlay.o : $(abspath env_screenoverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_texturetoggle.P
endif

$(OBJ_DIR)/env_texturetoggle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_texturetoggle.o : $(abspath env_texturetoggle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_tonemap_controller.P
endif

$(OBJ_DIR)/env_tonemap_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_tonemap_controller.o : $(abspath env_tonemap_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_zoom.P
endif

$(OBJ_DIR)/env_zoom.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_zoom.o : $(abspath env_zoom.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EventLog.P
endif

$(OBJ_DIR)/EventLog.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/EventLog.o : $(abspath EventLog.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/event_tempentity_tester.P
endif

$(OBJ_DIR)/event_tempentity_tester.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/event_tempentity_tester.o : $(abspath event_tempentity_tester.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/explode.P
endif

$(OBJ_DIR)/explode.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/explode.o : $(abspath explode.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filters.P
endif

$(OBJ_DIR)/filters.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/filters.o : $(abspath filters.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fire.P
endif

$(OBJ_DIR)/fire.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fire.o : $(abspath fire.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fire_smoke.P
endif

$(OBJ_DIR)/fire_smoke.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fire_smoke.o : $(abspath fire_smoke.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fish.P
endif

$(OBJ_DIR)/fish.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fish.o : $(abspath fish.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fogcontroller.P
endif

$(OBJ_DIR)/fogcontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fogcontroller.o : $(abspath fogcontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/fourwheelvehiclephysics.P
endif

$(OBJ_DIR)/fourwheelvehiclephysics.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/fourwheelvehiclephysics.o : $(abspath fourwheelvehiclephysics.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_areaportal.P
endif

$(OBJ_DIR)/func_areaportal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_areaportal.o : $(abspath func_areaportal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_areaportalbase.P
endif

$(OBJ_DIR)/func_areaportalbase.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_areaportalbase.o : $(abspath func_areaportalbase.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_areaportalwindow.P
endif

$(OBJ_DIR)/func_areaportalwindow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_areaportalwindow.o : $(abspath func_areaportalwindow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_break.P
endif

$(OBJ_DIR)/func_break.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_break.o : $(abspath func_break.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_breakablesurf.P
endif

$(OBJ_DIR)/func_breakablesurf.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_breakablesurf.o : $(abspath func_breakablesurf.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_dust.P
endif

$(OBJ_DIR)/func_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_dust.o : $(abspath func_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_ladder_endpoint.P
endif

$(OBJ_DIR)/func_ladder_endpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_ladder_endpoint.o : $(abspath func_ladder_endpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_lod.P
endif

$(OBJ_DIR)/func_lod.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_lod.o : $(abspath func_lod.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_movelinear.P
endif

$(OBJ_DIR)/func_movelinear.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_movelinear.o : $(abspath func_movelinear.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_occluder.P
endif

$(OBJ_DIR)/func_occluder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_occluder.o : $(abspath func_occluder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_reflective_glass.P
endif

$(OBJ_DIR)/func_reflective_glass.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_reflective_glass.o : $(abspath func_reflective_glass.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_smokevolume.P
endif

$(OBJ_DIR)/func_smokevolume.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_smokevolume.o : $(abspath func_smokevolume.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/game.P
endif

$(OBJ_DIR)/game.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/game.o : $(abspath game.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamedll_replay.P
endif

$(OBJ_DIR)/gamedll_replay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gamedll_replay.o : $(abspath gamedll_replay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gamehandle.P
endif

$(OBJ_DIR)/gamehandle.o : $(abspath gamehandle.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gameinterface.P
endif

$(OBJ_DIR)/gameinterface.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gameinterface.o : $(abspath gameinterface.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameStats_BasicStatsFunctions.P
endif

$(OBJ_DIR)/GameStats_BasicStatsFunctions.o : $(abspath GameStats_BasicStatsFunctions.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gametrace_dll.P
endif

$(OBJ_DIR)/gametrace_dll.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gametrace_dll.o : $(abspath gametrace_dll.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gameweaponmanager.P
endif

$(OBJ_DIR)/gameweaponmanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gameweaponmanager.o : $(abspath gameweaponmanager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/game_ui.P
endif

$(OBJ_DIR)/game_ui.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/game_ui.o : $(abspath game_ui.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/genericactor.P
endif

$(OBJ_DIR)/genericactor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/genericactor.o : $(abspath genericactor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/genericmonster.P
endif

$(OBJ_DIR)/genericmonster.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/genericmonster.o : $(abspath genericmonster.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gib.P
endif

$(OBJ_DIR)/gib.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/gib.o : $(abspath gib.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/globals.P
endif

$(OBJ_DIR)/globals.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/globals.o : $(abspath globals.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/globalstate.P
endif

$(OBJ_DIR)/globalstate.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/globalstate.o : $(abspath globalstate.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenadethrown.P
endif

$(OBJ_DIR)/grenadethrown.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenadethrown.o : $(abspath grenadethrown.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/guntarget.P
endif

$(OBJ_DIR)/guntarget.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/guntarget.o : $(abspath guntarget.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hierarchy.P
endif

$(OBJ_DIR)/hierarchy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hierarchy.o : $(abspath hierarchy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_allymanager.P
endif

$(OBJ_DIR)/ai_allymanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_allymanager.o : $(abspath hl2/ai_allymanager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_actbusy.P
endif

$(OBJ_DIR)/ai_behavior_actbusy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_actbusy.o : $(abspath hl2/ai_behavior_actbusy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_functank.P
endif

$(OBJ_DIR)/ai_behavior_functank.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_functank.o : $(abspath hl2/ai_behavior_functank.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_holster.P
endif

$(OBJ_DIR)/ai_behavior_holster.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_holster.o : $(abspath hl2/ai_behavior_holster.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_operator.P
endif

$(OBJ_DIR)/ai_behavior_operator.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_operator.o : $(abspath hl2/ai_behavior_operator.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_behavior_police.P
endif

$(OBJ_DIR)/ai_behavior_police.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_behavior_police.o : $(abspath hl2/ai_behavior_police.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_goal_police.P
endif

$(OBJ_DIR)/ai_goal_police.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_goal_police.o : $(abspath hl2/ai_goal_police.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ai_spotlight.P
endif

$(OBJ_DIR)/ai_spotlight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ai_spotlight.o : $(abspath hl2/ai_spotlight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/antlion_dust.P
endif

$(OBJ_DIR)/antlion_dust.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/antlion_dust.o : $(abspath hl2/antlion_dust.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/antlion_maker.P
endif

$(OBJ_DIR)/antlion_maker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/antlion_maker.o : $(abspath hl2/antlion_maker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ar2_explosion.P
endif

$(OBJ_DIR)/ar2_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ar2_explosion.o : $(abspath hl2/ar2_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basehlcombatweapon.P
endif

$(OBJ_DIR)/basehlcombatweapon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/basehlcombatweapon.o : $(abspath hl2/basehlcombatweapon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cbasehelicopter.P
endif

$(OBJ_DIR)/cbasehelicopter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cbasehelicopter.o : $(abspath hl2/cbasehelicopter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cbasespriteprojectile.P
endif

$(OBJ_DIR)/cbasespriteprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/cbasespriteprojectile.o : $(abspath hl2/cbasespriteprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/citadel_effects.P
endif

$(OBJ_DIR)/citadel_effects.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/citadel_effects.o : $(abspath hl2/citadel_effects.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/combine_mine.P
endif

$(OBJ_DIR)/combine_mine.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/combine_mine.o : $(abspath hl2/combine_mine.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_alyxemp.P
endif

$(OBJ_DIR)/env_alyxemp.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_alyxemp.o : $(abspath hl2/env_alyxemp.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_headcrabcanister.P
endif

$(OBJ_DIR)/env_headcrabcanister.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_headcrabcanister.o : $(abspath hl2/env_headcrabcanister.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_speaker.P
endif

$(OBJ_DIR)/env_speaker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_speaker.o : $(abspath hl2/env_speaker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/env_starfield.P
endif

$(OBJ_DIR)/env_starfield.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/env_starfield.o : $(abspath hl2/env_starfield.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Func_Monitor.P
endif

$(OBJ_DIR)/Func_Monitor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/Func_Monitor.o : $(abspath hl2/Func_Monitor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_recharge.P
endif

$(OBJ_DIR)/func_recharge.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_recharge.o : $(abspath hl2/func_recharge.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/func_tank.P
endif

$(OBJ_DIR)/func_tank.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/func_tank.o : $(abspath hl2/func_tank.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_ar2.P
endif

$(OBJ_DIR)/grenade_ar2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_ar2.o : $(abspath hl2/grenade_ar2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_beam.P
endif

$(OBJ_DIR)/grenade_beam.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_beam.o : $(abspath hl2/grenade_beam.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_bugbait.P
endif

$(OBJ_DIR)/grenade_bugbait.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_bugbait.o : $(abspath hl2/grenade_bugbait.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_frag.P
endif

$(OBJ_DIR)/grenade_frag.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_frag.o : $(abspath hl2/grenade_frag.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_homer.P
endif

$(OBJ_DIR)/grenade_homer.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_homer.o : $(abspath hl2/grenade_homer.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/grenade_pathfollower.P
endif

$(OBJ_DIR)/grenade_pathfollower.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/grenade_pathfollower.o : $(abspath hl2/grenade_pathfollower.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_ai_network.P
endif

$(OBJ_DIR)/hl2_ai_network.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_ai_network.o : $(abspath hl2/hl2_ai_network.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_client.P
endif

$(OBJ_DIR)/hl2_client.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_client.o : $(abspath hl2/hl2_client.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_eventlog.P
endif

$(OBJ_DIR)/hl2_eventlog.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_eventlog.o : $(abspath hl2/hl2_eventlog.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_gamestats.P
endif

$(OBJ_DIR)/hl2_gamestats.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_gamestats.o : $(abspath hl2/hl2_gamestats.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_player.P
endif

$(OBJ_DIR)/hl2_player.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_player.o : $(abspath hl2/hl2_player.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_playerlocaldata.P
endif

$(OBJ_DIR)/hl2_playerlocaldata.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_playerlocaldata.o : $(abspath hl2/hl2_playerlocaldata.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl2_triggers.P
endif

$(OBJ_DIR)/hl2_triggers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl2_triggers.o : $(abspath hl2/hl2_triggers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hl_playermove.P
endif

$(OBJ_DIR)/hl_playermove.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hl_playermove.o : $(abspath hl2/hl_playermove.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/info_darknessmode_lightsource.P
endif

$(OBJ_DIR)/info_darknessmode_lightsource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/info_darknessmode_lightsource.o : $(abspath hl2/info_darknessmode_lightsource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/info_teleporter_countdown.P
endif

$(OBJ_DIR)/info_teleporter_countdown.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/info_teleporter_countdown.o : $(abspath hl2/info_teleporter_countdown.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_ammo.P
endif

$(OBJ_DIR)/item_ammo.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_ammo.o : $(abspath hl2/item_ammo.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_battery.P
endif

$(OBJ_DIR)/item_battery.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_battery.o : $(abspath hl2/item_battery.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_dynamic_resupply.P
endif

$(OBJ_DIR)/item_dynamic_resupply.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_dynamic_resupply.o : $(abspath hl2/item_dynamic_resupply.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_healthkit.P
endif

$(OBJ_DIR)/item_healthkit.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_healthkit.o : $(abspath hl2/item_healthkit.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_itemcrate.P
endif

$(OBJ_DIR)/item_itemcrate.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_itemcrate.o : $(abspath hl2/item_itemcrate.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_suit.P
endif

$(OBJ_DIR)/item_suit.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_suit.o : $(abspath hl2/item_suit.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/look_door.P
endif

$(OBJ_DIR)/look_door.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/look_door.o : $(abspath hl2/look_door.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/monster_dummy.P
endif

$(OBJ_DIR)/monster_dummy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/monster_dummy.o : $(abspath hl2/monster_dummy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_alyx.P
endif

$(OBJ_DIR)/npc_alyx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_alyx.o : $(abspath hl2/npc_alyx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_antlion.P
endif

$(OBJ_DIR)/npc_antlion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_antlion.o : $(abspath hl2/npc_antlion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_antlionguard.P
endif

$(OBJ_DIR)/npc_antlionguard.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_antlionguard.o : $(abspath hl2/npc_antlionguard.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_apcdriver.P
endif

$(OBJ_DIR)/npc_apcdriver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_apcdriver.o : $(abspath hl2/npc_apcdriver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_attackchopper.P
endif

$(OBJ_DIR)/npc_attackchopper.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_attackchopper.o : $(abspath hl2/npc_attackchopper.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_barnacle.P
endif

$(OBJ_DIR)/npc_barnacle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_barnacle.o : $(abspath hl2/npc_barnacle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_barney.P
endif

$(OBJ_DIR)/npc_barney.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_barney.o : $(abspath hl2/npc_barney.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_basescanner.P
endif

$(OBJ_DIR)/npc_basescanner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_basescanner.o : $(abspath hl2/npc_basescanner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_BaseZombie.P
endif

$(OBJ_DIR)/npc_BaseZombie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_BaseZombie.o : $(abspath hl2/npc_BaseZombie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_blob.P
endif

$(OBJ_DIR)/npc_blob.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_blob.o : $(abspath hl2/npc_blob.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_breen.P
endif

$(OBJ_DIR)/npc_breen.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_breen.o : $(abspath hl2/npc_breen.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_bullseye.P
endif

$(OBJ_DIR)/npc_bullseye.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_bullseye.o : $(abspath hl2/npc_bullseye.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_citizen17.P
endif

$(OBJ_DIR)/npc_citizen17.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_citizen17.o : $(abspath hl2/npc_citizen17.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combine.P
endif

$(OBJ_DIR)/npc_combine.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combine.o : $(abspath hl2/npc_combine.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combinecamera.P
endif

$(OBJ_DIR)/npc_combinecamera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combinecamera.o : $(abspath hl2/npc_combinecamera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combinedropship.P
endif

$(OBJ_DIR)/npc_combinedropship.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combinedropship.o : $(abspath hl2/npc_combinedropship.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combinegunship.P
endif

$(OBJ_DIR)/npc_combinegunship.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combinegunship.o : $(abspath hl2/npc_combinegunship.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_combines.P
endif

$(OBJ_DIR)/npc_combines.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_combines.o : $(abspath hl2/npc_combines.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_cranedriver.P
endif

$(OBJ_DIR)/npc_cranedriver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_cranedriver.o : $(abspath hl2/npc_cranedriver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_crow.P
endif

$(OBJ_DIR)/npc_crow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_crow.o : $(abspath hl2/npc_crow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_dog.P
endif

$(OBJ_DIR)/npc_dog.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_dog.o : $(abspath hl2/npc_dog.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_eli.P
endif

$(OBJ_DIR)/npc_eli.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_eli.o : $(abspath hl2/npc_eli.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_enemyfinder.P
endif

$(OBJ_DIR)/npc_enemyfinder.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_enemyfinder.o : $(abspath hl2/npc_enemyfinder.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_fastzombie.P
endif

$(OBJ_DIR)/npc_fastzombie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_fastzombie.o : $(abspath hl2/npc_fastzombie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_fisherman.P
endif

$(OBJ_DIR)/npc_fisherman.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_fisherman.o : $(abspath hl2/npc_fisherman.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_gman.P
endif

$(OBJ_DIR)/npc_gman.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_gman.o : $(abspath hl2/npc_gman.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_headcrab.P
endif

$(OBJ_DIR)/npc_headcrab.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_headcrab.o : $(abspath hl2/npc_headcrab.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_ichthyosaur.P
endif

$(OBJ_DIR)/npc_ichthyosaur.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_ichthyosaur.o : $(abspath hl2/npc_ichthyosaur.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_kleiner.P
endif

$(OBJ_DIR)/npc_kleiner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_kleiner.o : $(abspath hl2/npc_kleiner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_launcher.P
endif

$(OBJ_DIR)/npc_launcher.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_launcher.o : $(abspath hl2/npc_launcher.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_manhack.P
endif

$(OBJ_DIR)/npc_manhack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_manhack.o : $(abspath hl2/npc_manhack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_metropolice.P
endif

$(OBJ_DIR)/npc_metropolice.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_metropolice.o : $(abspath hl2/npc_metropolice.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_missiledefense.P
endif

$(OBJ_DIR)/npc_missiledefense.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_missiledefense.o : $(abspath hl2/npc_missiledefense.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_monk.P
endif

$(OBJ_DIR)/npc_monk.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_monk.o : $(abspath hl2/npc_monk.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_mossman.P
endif

$(OBJ_DIR)/npc_mossman.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_mossman.o : $(abspath hl2/npc_mossman.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_playercompanion.P
endif

$(OBJ_DIR)/npc_playercompanion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_playercompanion.o : $(abspath hl2/npc_playercompanion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_PoisonZombie.P
endif

$(OBJ_DIR)/npc_PoisonZombie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_PoisonZombie.o : $(abspath hl2/npc_PoisonZombie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_rollermine.P
endif

$(OBJ_DIR)/npc_rollermine.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_rollermine.o : $(abspath hl2/npc_rollermine.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_scanner.P
endif

$(OBJ_DIR)/npc_scanner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_scanner.o : $(abspath hl2/npc_scanner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_stalker.P
endif

$(OBJ_DIR)/npc_stalker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_stalker.o : $(abspath hl2/npc_stalker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_strider.P
endif

$(OBJ_DIR)/npc_strider.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_strider.o : $(abspath hl2/npc_strider.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_turret_ceiling.P
endif

$(OBJ_DIR)/npc_turret_ceiling.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_turret_ceiling.o : $(abspath hl2/npc_turret_ceiling.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_turret_floor.P
endif

$(OBJ_DIR)/npc_turret_floor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_turret_floor.o : $(abspath hl2/npc_turret_floor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_turret_ground.P
endif

$(OBJ_DIR)/npc_turret_ground.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_turret_ground.o : $(abspath hl2/npc_turret_ground.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_vortigaunt_episodic.P
endif

$(OBJ_DIR)/npc_vortigaunt_episodic.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_vortigaunt_episodic.o : $(abspath hl2/npc_vortigaunt_episodic.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_zombie.P
endif

$(OBJ_DIR)/npc_zombie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_zombie.o : $(abspath hl2/npc_zombie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_apc_controller.P
endif

$(OBJ_DIR)/point_apc_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_apc_controller.o : $(abspath hl2/point_apc_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/prop_combine_ball.P
endif

$(OBJ_DIR)/prop_combine_ball.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/prop_combine_ball.o : $(abspath hl2/prop_combine_ball.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/prop_thumper.P
endif

$(OBJ_DIR)/prop_thumper.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/prop_thumper.o : $(abspath hl2/prop_thumper.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/proto_sniper.P
endif

$(OBJ_DIR)/proto_sniper.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/proto_sniper.o : $(abspath hl2/proto_sniper.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rotorwash.P
endif

$(OBJ_DIR)/rotorwash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/rotorwash.o : $(abspath hl2/rotorwash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/script_intro.P
endif

$(OBJ_DIR)/script_intro.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/script_intro.o : $(abspath hl2/script_intro.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_gaussexplosion.P
endif

$(OBJ_DIR)/te_gaussexplosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_gaussexplosion.o : $(abspath hl2/te_gaussexplosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_airboat.P
endif

$(OBJ_DIR)/vehicle_airboat.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_airboat.o : $(abspath hl2/vehicle_airboat.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_apc.P
endif

$(OBJ_DIR)/vehicle_apc.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_apc.o : $(abspath hl2/vehicle_apc.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_cannon.P
endif

$(OBJ_DIR)/vehicle_cannon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_cannon.o : $(abspath hl2/vehicle_cannon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_crane.P
endif

$(OBJ_DIR)/vehicle_crane.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_crane.o : $(abspath hl2/vehicle_crane.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_jeep.P
endif

$(OBJ_DIR)/vehicle_jeep.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_jeep.o : $(abspath hl2/vehicle_jeep.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_prisoner_pod.P
endif

$(OBJ_DIR)/vehicle_prisoner_pod.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_prisoner_pod.o : $(abspath hl2/vehicle_prisoner_pod.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_viewcontroller.P
endif

$(OBJ_DIR)/vehicle_viewcontroller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_viewcontroller.o : $(abspath hl2/vehicle_viewcontroller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_357.P
endif

$(OBJ_DIR)/weapon_357.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_357.o : $(abspath hl2/weapon_357.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_alyxgun.P
endif

$(OBJ_DIR)/weapon_alyxgun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_alyxgun.o : $(abspath hl2/weapon_alyxgun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_annabelle.P
endif

$(OBJ_DIR)/weapon_annabelle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_annabelle.o : $(abspath hl2/weapon_annabelle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_ar2.P
endif

$(OBJ_DIR)/weapon_ar2.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_ar2.o : $(abspath hl2/weapon_ar2.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_bugbait.P
endif

$(OBJ_DIR)/weapon_bugbait.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_bugbait.o : $(abspath hl2/weapon_bugbait.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_cguard.P
endif

$(OBJ_DIR)/weapon_cguard.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_cguard.o : $(abspath hl2/weapon_cguard.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_citizenpackage.P
endif

$(OBJ_DIR)/weapon_citizenpackage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_citizenpackage.o : $(abspath hl2/weapon_citizenpackage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_crossbow.P
endif

$(OBJ_DIR)/weapon_crossbow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_crossbow.o : $(abspath hl2/weapon_crossbow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_crowbar.P
endif

$(OBJ_DIR)/weapon_crowbar.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_crowbar.o : $(abspath hl2/weapon_crowbar.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_flaregun.P
endif

$(OBJ_DIR)/weapon_flaregun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_flaregun.o : $(abspath hl2/weapon_flaregun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_frag.P
endif

$(OBJ_DIR)/weapon_frag.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_frag.o : $(abspath hl2/weapon_frag.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_physcannon.P
endif

$(OBJ_DIR)/weapon_physcannon.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_physcannon.o : $(abspath hl2/weapon_physcannon.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_pistol.P
endif

$(OBJ_DIR)/weapon_pistol.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_pistol.o : $(abspath hl2/weapon_pistol.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_rpg.P
endif

$(OBJ_DIR)/weapon_rpg.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_rpg.o : $(abspath hl2/weapon_rpg.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_shotgun.P
endif

$(OBJ_DIR)/weapon_shotgun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_shotgun.o : $(abspath hl2/weapon_shotgun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_smg1.P
endif

$(OBJ_DIR)/weapon_smg1.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_smg1.o : $(abspath hl2/weapon_smg1.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_stunstick.P
endif

$(OBJ_DIR)/weapon_stunstick.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_stunstick.o : $(abspath hl2/weapon_stunstick.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hltvdirector.P
endif

$(OBJ_DIR)/hltvdirector.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/hltvdirector.o : $(abspath hltvdirector.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/h_ai.P
endif

$(OBJ_DIR)/h_ai.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/h_ai.o : $(abspath h_ai.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/h_cycler.P
endif

$(OBJ_DIR)/h_cycler.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/h_cycler.o : $(abspath h_cycler.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/h_export.P
endif

$(OBJ_DIR)/h_export.o : $(abspath h_export.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/info_camera_link.P
endif

$(OBJ_DIR)/info_camera_link.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/info_camera_link.o : $(abspath info_camera_link.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/info_overlay_accessor.P
endif

$(OBJ_DIR)/info_overlay_accessor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/info_overlay_accessor.o : $(abspath info_overlay_accessor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/init_factory.P
endif

$(OBJ_DIR)/init_factory.o : $(abspath init_factory.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/intermission.P
endif

$(OBJ_DIR)/intermission.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/intermission.o : $(abspath intermission.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/item_world.P
endif

$(OBJ_DIR)/item_world.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/item_world.o : $(abspath item_world.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lightglow.P
endif

$(OBJ_DIR)/lightglow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/lightglow.o : $(abspath lightglow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/lights.P
endif

$(OBJ_DIR)/lights.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/lights.o : $(abspath lights.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logicauto.P
endif

$(OBJ_DIR)/logicauto.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logicauto.o : $(abspath logicauto.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logicentities.P
endif

$(OBJ_DIR)/logicentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logicentities.o : $(abspath logicentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logicrelay.P
endif

$(OBJ_DIR)/logicrelay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logicrelay.o : $(abspath logicrelay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logic_achievement.P
endif

$(OBJ_DIR)/logic_achievement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logic_achievement.o : $(abspath logic_achievement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logic_measure_movement.P
endif

$(OBJ_DIR)/logic_measure_movement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logic_measure_movement.o : $(abspath logic_measure_movement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/logic_navigation.P
endif

$(OBJ_DIR)/logic_navigation.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/logic_navigation.o : $(abspath logic_navigation.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/mapentities.P
endif

$(OBJ_DIR)/mapentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/mapentities.o : $(abspath mapentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/maprules.P
endif

$(OBJ_DIR)/maprules.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/maprules.o : $(abspath maprules.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MaterialModifyControl.P
endif

$(OBJ_DIR)/MaterialModifyControl.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/MaterialModifyControl.o : $(abspath MaterialModifyControl.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/message_entity.P
endif

$(OBJ_DIR)/message_entity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/message_entity.o : $(abspath message_entity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/modelentities.P
endif

$(OBJ_DIR)/modelentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/modelentities.o : $(abspath modelentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/monstermaker.P
endif

$(OBJ_DIR)/monstermaker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/monstermaker.o : $(abspath monstermaker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movehelper_server.P
endif

$(OBJ_DIR)/movehelper_server.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movehelper_server.o : $(abspath movehelper_server.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movement.P
endif

$(OBJ_DIR)/movement.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movement.o : $(abspath movement.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/movie_explosion.P
endif

$(OBJ_DIR)/movie_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/movie_explosion.o : $(abspath movie_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ndebugoverlay.P
endif

$(OBJ_DIR)/ndebugoverlay.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ndebugoverlay.o : $(abspath ndebugoverlay.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_talker.P
endif

$(OBJ_DIR)/npc_talker.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_talker.o : $(abspath npc_talker.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/npc_vehicledriver.P
endif

$(OBJ_DIR)/npc_vehicledriver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/npc_vehicledriver.o : $(abspath npc_vehicledriver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_fire.P
endif

$(OBJ_DIR)/particle_fire.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_fire.o : $(abspath particle_fire.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_light.P
endif

$(OBJ_DIR)/particle_light.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_light.o : $(abspath particle_light.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_smokegrenade.P
endif

$(OBJ_DIR)/particle_smokegrenade.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_smokegrenade.o : $(abspath particle_smokegrenade.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/particle_system.P
endif

$(OBJ_DIR)/particle_system.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/particle_system.o : $(abspath particle_system.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pathcorner.P
endif

$(OBJ_DIR)/pathcorner.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pathcorner.o : $(abspath pathcorner.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pathtrack.P
endif

$(OBJ_DIR)/pathtrack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pathtrack.o : $(abspath pathtrack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physconstraint.P
endif

$(OBJ_DIR)/physconstraint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physconstraint.o : $(abspath physconstraint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics.P
endif

$(OBJ_DIR)/physics.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics.o : $(abspath physics.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_bone_follower.P
endif

$(OBJ_DIR)/physics_bone_follower.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_bone_follower.o : $(abspath physics_bone_follower.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_cannister.P
endif

$(OBJ_DIR)/physics_cannister.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_cannister.o : $(abspath physics_cannister.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_fx.P
endif

$(OBJ_DIR)/physics_fx.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_fx.o : $(abspath physics_fx.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_impact_damage.P
endif

$(OBJ_DIR)/physics_impact_damage.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_impact_damage.o : $(abspath physics_impact_damage.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_main.P
endif

$(OBJ_DIR)/physics_main.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_main.o : $(abspath physics_main.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_npc_solver.P
endif

$(OBJ_DIR)/physics_npc_solver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_npc_solver.o : $(abspath physics_npc_solver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physics_prop_ragdoll.P
endif

$(OBJ_DIR)/physics_prop_ragdoll.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physics_prop_ragdoll.o : $(abspath physics_prop_ragdoll.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/physobj.P
endif

$(OBJ_DIR)/physobj.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/physobj.o : $(abspath physobj.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/phys_controller.P
endif

$(OBJ_DIR)/phys_controller.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/phys_controller.o : $(abspath phys_controller.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/plasma.P
endif

$(OBJ_DIR)/plasma.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/plasma.o : $(abspath plasma.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player.P
endif

$(OBJ_DIR)/player.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player.o : $(abspath player.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/playerinfomanager.P
endif

$(OBJ_DIR)/playerinfomanager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/playerinfomanager.o : $(abspath playerinfomanager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/playerlocaldata.P
endif

$(OBJ_DIR)/playerlocaldata.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/playerlocaldata.o : $(abspath playerlocaldata.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player_command.P
endif

$(OBJ_DIR)/player_command.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player_command.o : $(abspath player_command.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player_lagcompensation.P
endif

$(OBJ_DIR)/player_lagcompensation.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player_lagcompensation.o : $(abspath player_lagcompensation.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player_pickup.P
endif

$(OBJ_DIR)/player_pickup.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player_pickup.o : $(abspath player_pickup.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/player_resource.P
endif

$(OBJ_DIR)/player_resource.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/player_resource.o : $(abspath player_resource.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/plugin_check.P
endif

$(OBJ_DIR)/plugin_check.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/plugin_check.o : $(abspath plugin_check.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pointanglesensor.P
endif

$(OBJ_DIR)/pointanglesensor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pointanglesensor.o : $(abspath pointanglesensor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PointAngularVelocitySensor.P
endif

$(OBJ_DIR)/PointAngularVelocitySensor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/PointAngularVelocitySensor.o : $(abspath PointAngularVelocitySensor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pointhurt.P
endif

$(OBJ_DIR)/pointhurt.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pointhurt.o : $(abspath pointhurt.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pointteleport.P
endif

$(OBJ_DIR)/pointteleport.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/pointteleport.o : $(abspath pointteleport.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_camera.P
endif

$(OBJ_DIR)/point_camera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_camera.o : $(abspath point_camera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_devshot_camera.P
endif

$(OBJ_DIR)/point_devshot_camera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_devshot_camera.o : $(abspath point_devshot_camera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_playermoveconstraint.P
endif

$(OBJ_DIR)/point_playermoveconstraint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_playermoveconstraint.o : $(abspath point_playermoveconstraint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_spotlight.P
endif

$(OBJ_DIR)/point_spotlight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_spotlight.o : $(abspath point_spotlight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/point_template.P
endif

$(OBJ_DIR)/point_template.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/point_template.o : $(abspath point_template.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/props.P
endif

$(OBJ_DIR)/props.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/props.o : $(abspath props.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/RagdollBoogie.P
endif

$(OBJ_DIR)/RagdollBoogie.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/RagdollBoogie.o : $(abspath RagdollBoogie.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ragdoll_manager.P
endif

$(OBJ_DIR)/ragdoll_manager.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ragdoll_manager.o : $(abspath ragdoll_manager.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/recipientfilter.P
endif

$(OBJ_DIR)/recipientfilter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/recipientfilter.o : $(abspath recipientfilter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rope.P
endif

$(OBJ_DIR)/rope.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/rope.o : $(abspath rope.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/saverestore_gamedll.P
endif

$(OBJ_DIR)/saverestore_gamedll.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/saverestore_gamedll.o : $(abspath saverestore_gamedll.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sceneentity.P
endif

$(OBJ_DIR)/sceneentity.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sceneentity.o : $(abspath sceneentity.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scratchpad_gamedll_helpers.P
endif

$(OBJ_DIR)/scratchpad_gamedll_helpers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/scratchpad_gamedll_helpers.o : $(abspath scratchpad_gamedll_helpers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scripted.P
endif

$(OBJ_DIR)/scripted.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/scripted.o : $(abspath scripted.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scriptedtarget.P
endif

$(OBJ_DIR)/scriptedtarget.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/scriptedtarget.o : $(abspath scriptedtarget.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sendproxy.P
endif

$(OBJ_DIR)/sendproxy.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sendproxy.o : $(abspath sendproxy.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerNetworkProperty.P
endif

$(OBJ_DIR)/ServerNetworkProperty.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/ServerNetworkProperty.o : $(abspath ServerNetworkProperty.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shadowcontrol.P
endif

$(OBJ_DIR)/shadowcontrol.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/shadowcontrol.o : $(abspath shadowcontrol.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SkyCamera.P
endif

$(OBJ_DIR)/SkyCamera.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/SkyCamera.o : $(abspath SkyCamera.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/slideshow_display.P
endif

$(OBJ_DIR)/slideshow_display.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/slideshow_display.o : $(abspath slideshow_display.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/smokestack.P
endif

$(OBJ_DIR)/smokestack.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/smokestack.o : $(abspath smokestack.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/smoke_trail.P
endif

$(OBJ_DIR)/smoke_trail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/smoke_trail.o : $(abspath smoke_trail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sound.P
endif

$(OBJ_DIR)/sound.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sound.o : $(abspath sound.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundent.P
endif

$(OBJ_DIR)/soundent.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundent.o : $(abspath soundent.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundscape.P
endif

$(OBJ_DIR)/soundscape.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundscape.o : $(abspath soundscape.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/soundscape_system.P
endif

$(OBJ_DIR)/soundscape_system.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/soundscape_system.o : $(abspath soundscape_system.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spotlightend.P
endif

$(OBJ_DIR)/spotlightend.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/spotlightend.o : $(abspath spotlightend.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sprite_perfmonitor.P
endif

$(OBJ_DIR)/sprite_perfmonitor.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sprite_perfmonitor.o : $(abspath sprite_perfmonitor.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stdafx.P
endif

$(OBJ_DIR)/cbase.h.gch : cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/cbase.h.P : $(OBJ_DIR)/cbase.h.gch

vpath cbase.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/cbase.h.P
endif

$(OBJ_DIR)/cbase.h : cbase.h $(OBJ_DIR)/cbase.h.gch $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/cbase.h

$(OBJ_DIR)/stdafx.o : $(abspath stdafx.cpp) $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamjet.P
endif

$(OBJ_DIR)/steamjet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/steamjet.o : $(abspath steamjet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/subs.P
endif

$(OBJ_DIR)/subs.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/subs.o : $(abspath subs.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sun.P
endif

$(OBJ_DIR)/sun.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/sun.o : $(abspath sun.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tactical_mission.P
endif

$(OBJ_DIR)/tactical_mission.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/tactical_mission.o : $(abspath tactical_mission.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tanktrain.P
endif

$(OBJ_DIR)/tanktrain.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/tanktrain.o : $(abspath tanktrain.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te.P
endif

$(OBJ_DIR)/te.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te.o : $(abspath te.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/team.P
endif

$(OBJ_DIR)/team.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/team.o : $(abspath team.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/team_spawnpoint.P
endif

$(OBJ_DIR)/team_spawnpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/team_spawnpoint.o : $(abspath team_spawnpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TemplateEntities.P
endif

$(OBJ_DIR)/TemplateEntities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/TemplateEntities.o : $(abspath TemplateEntities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tempmonster.P
endif

$(OBJ_DIR)/tempmonster.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/tempmonster.o : $(abspath tempmonster.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tesla.P
endif

$(OBJ_DIR)/tesla.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/tesla.o : $(abspath tesla.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/testfunctions.P
endif

$(OBJ_DIR)/testfunctions.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/testfunctions.o : $(abspath testfunctions.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/testtraceline.P
endif

$(OBJ_DIR)/testtraceline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/testtraceline.o : $(abspath testtraceline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/test_proxytoggle.P
endif

$(OBJ_DIR)/test_proxytoggle.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/test_proxytoggle.o : $(abspath test_proxytoggle.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/test_stressentities.P
endif

$(OBJ_DIR)/test_stressentities.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/test_stressentities.o : $(abspath test_stressentities.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/textstatsmgr.P
endif

$(OBJ_DIR)/textstatsmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/textstatsmgr.o : $(abspath textstatsmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_armorricochet.P
endif

$(OBJ_DIR)/te_armorricochet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_armorricochet.o : $(abspath te_armorricochet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_basebeam.P
endif

$(OBJ_DIR)/te_basebeam.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_basebeam.o : $(abspath te_basebeam.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamentpoint.P
endif

$(OBJ_DIR)/te_beamentpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamentpoint.o : $(abspath te_beamentpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beaments.P
endif

$(OBJ_DIR)/te_beaments.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beaments.o : $(abspath te_beaments.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamfollow.P
endif

$(OBJ_DIR)/te_beamfollow.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamfollow.o : $(abspath te_beamfollow.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamlaser.P
endif

$(OBJ_DIR)/te_beamlaser.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamlaser.o : $(abspath te_beamlaser.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beampoints.P
endif

$(OBJ_DIR)/te_beampoints.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beampoints.o : $(abspath te_beampoints.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamring.P
endif

$(OBJ_DIR)/te_beamring.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamring.o : $(abspath te_beamring.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamringpoint.P
endif

$(OBJ_DIR)/te_beamringpoint.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamringpoint.o : $(abspath te_beamringpoint.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_beamspline.P
endif

$(OBJ_DIR)/te_beamspline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_beamspline.o : $(abspath te_beamspline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bloodsprite.P
endif

$(OBJ_DIR)/te_bloodsprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bloodsprite.o : $(abspath te_bloodsprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bloodstream.P
endif

$(OBJ_DIR)/te_bloodstream.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bloodstream.o : $(abspath te_bloodstream.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_breakmodel.P
endif

$(OBJ_DIR)/te_breakmodel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_breakmodel.o : $(abspath te_breakmodel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bspdecal.P
endif

$(OBJ_DIR)/te_bspdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bspdecal.o : $(abspath te_bspdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bubbles.P
endif

$(OBJ_DIR)/te_bubbles.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bubbles.o : $(abspath te_bubbles.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_bubbletrail.P
endif

$(OBJ_DIR)/te_bubbletrail.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_bubbletrail.o : $(abspath te_bubbletrail.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_clientprojectile.P
endif

$(OBJ_DIR)/te_clientprojectile.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_clientprojectile.o : $(abspath te_clientprojectile.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_decal.P
endif

$(OBJ_DIR)/te_decal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_decal.o : $(abspath te_decal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_dynamiclight.P
endif

$(OBJ_DIR)/te_dynamiclight.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_dynamiclight.o : $(abspath te_dynamiclight.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_effect_dispatch.P
endif

$(OBJ_DIR)/te_effect_dispatch.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_effect_dispatch.o : $(abspath te_effect_dispatch.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_energysplash.P
endif

$(OBJ_DIR)/te_energysplash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_energysplash.o : $(abspath te_energysplash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_explosion.P
endif

$(OBJ_DIR)/te_explosion.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_explosion.o : $(abspath te_explosion.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_fizz.P
endif

$(OBJ_DIR)/te_fizz.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_fizz.o : $(abspath te_fizz.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_footprintdecal.P
endif

$(OBJ_DIR)/te_footprintdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_footprintdecal.o : $(abspath te_footprintdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_glassshatter.P
endif

$(OBJ_DIR)/te_glassshatter.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_glassshatter.o : $(abspath te_glassshatter.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_glowsprite.P
endif

$(OBJ_DIR)/te_glowsprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_glowsprite.o : $(abspath te_glowsprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_impact.P
endif

$(OBJ_DIR)/te_impact.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_impact.o : $(abspath te_impact.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_killplayerattachments.P
endif

$(OBJ_DIR)/te_killplayerattachments.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_killplayerattachments.o : $(abspath te_killplayerattachments.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_largefunnel.P
endif

$(OBJ_DIR)/te_largefunnel.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_largefunnel.o : $(abspath te_largefunnel.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_muzzleflash.P
endif

$(OBJ_DIR)/te_muzzleflash.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_muzzleflash.o : $(abspath te_muzzleflash.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_particlesystem.P
endif

$(OBJ_DIR)/te_particlesystem.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_particlesystem.o : $(abspath te_particlesystem.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_physicsprop.P
endif

$(OBJ_DIR)/te_physicsprop.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_physicsprop.o : $(abspath te_physicsprop.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_playerdecal.P
endif

$(OBJ_DIR)/te_playerdecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_playerdecal.o : $(abspath te_playerdecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_projecteddecal.P
endif

$(OBJ_DIR)/te_projecteddecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_projecteddecal.o : $(abspath te_projecteddecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_showline.P
endif

$(OBJ_DIR)/te_showline.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_showline.o : $(abspath te_showline.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_smoke.P
endif

$(OBJ_DIR)/te_smoke.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_smoke.o : $(abspath te_smoke.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_sparks.P
endif

$(OBJ_DIR)/te_sparks.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_sparks.o : $(abspath te_sparks.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_sprite.P
endif

$(OBJ_DIR)/te_sprite.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_sprite.o : $(abspath te_sprite.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_spritespray.P
endif

$(OBJ_DIR)/te_spritespray.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_spritespray.o : $(abspath te_spritespray.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/te_worlddecal.P
endif

$(OBJ_DIR)/te_worlddecal.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/te_worlddecal.o : $(abspath te_worlddecal.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/timedeventmgr.P
endif

$(OBJ_DIR)/timedeventmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/timedeventmgr.o : $(abspath timedeventmgr.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/toolframework_server.P
endif

$(OBJ_DIR)/toolframework_server.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/toolframework_server.o : $(abspath toolframework_server.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/trains.P
endif

$(OBJ_DIR)/trains.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/trains.o : $(abspath trains.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/triggers.P
endif

$(OBJ_DIR)/triggers.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/triggers.o : $(abspath triggers.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/util.P
endif

$(OBJ_DIR)/util.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/util.o : $(abspath util.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/variant_t.P
endif

$(OBJ_DIR)/variant_t.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/variant_t.o : $(abspath variant_t.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_base.P
endif

$(OBJ_DIR)/vehicle_base.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_base.o : $(abspath vehicle_base.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_baseserver.P
endif

$(OBJ_DIR)/vehicle_baseserver.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_baseserver.o : $(abspath vehicle_baseserver.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vehicle_choreo_generic.P
endif

$(OBJ_DIR)/vehicle_choreo_generic.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vehicle_choreo_generic.o : $(abspath vehicle_choreo_generic.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vguiscreen.P
endif

$(OBJ_DIR)/vguiscreen.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/vguiscreen.o : $(abspath vguiscreen.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/waterbullet.P
endif

$(OBJ_DIR)/waterbullet.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/waterbullet.o : $(abspath waterbullet.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WaterLODControl.P
endif

$(OBJ_DIR)/WaterLODControl.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/WaterLODControl.o : $(abspath WaterLODControl.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/wcedit.P
endif

$(OBJ_DIR)/wcedit.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/wcedit.o : $(abspath wcedit.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weapon_cubemap.P
endif

$(OBJ_DIR)/weapon_cubemap.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weapon_cubemap.o : $(abspath weapon_cubemap.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/weight_button.P
endif

$(OBJ_DIR)/weight_button.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/weight_button.o : $(abspath weight_button.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/world.P
endif

$(OBJ_DIR)/world.o : TARGET_PCH_FILE = $(OBJ_DIR)/cbase.h
$(OBJ_DIR)/world.o : $(abspath world.cpp) $(OBJ_DIR)/cbase.h.gch $(OBJ_DIR)/cbase.h $(PWD)/server_linux32_hl2.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)


endif # (CFG=release)



