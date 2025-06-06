ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=replay
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
SystemLibraries=-lrt -lcurl-gnutls 
DLL_EXT=.wasm
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=replay -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DREPLAY_DLL -DREPLAY_ENABLED -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/replay -D_DLL_EXT=.wasm -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/replay.wasm
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/replay.wasm


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../common/imageutils.cpp \
    ../common/netmessages.cpp \
    ../public/tier0/memoverride.cpp \
    baserecordingsession.cpp \
    baserecordingsessionblock.cpp \
    baserecordingsessionblockmanager.cpp \
    baserecordingsessionmanager.cpp \
    basethinker.cpp \
    cl_commands.cpp \
    cl_cvars.cpp \
    cl_downloader.cpp \
    cl_performancecontroller.cpp \
    cl_performancemanager.cpp \
    cl_recordingsession.cpp \
    cl_recordingsessionblock.cpp \
    cl_recordingsessionblockmanager.cpp \
    cl_recordingsessionmanager.cpp \
    cl_renderqueue.cpp \
    cl_replaycontext.cpp \
    cl_replaymanager.cpp \
    cl_replaymovie.cpp \
    cl_replaymoviemanager.cpp \
    cl_screenshotmanager.cpp \
    cl_sessionblockdownloader.cpp \
    cl_sessioninfodownloader.cpp \
    compression.cpp \
    errorsystem.cpp \
    managertest.cpp \
    replaysystem.cpp \
    replay_dbg.cpp \
    replay_reconstructor.cpp \
    sessioninfoheader.cpp \
    shared_cvars.cpp \
    shared_replaycontext.cpp \
    spew.cpp \
    sv_basejob.cpp \
    sv_commands.cpp \
    sv_cvars.cpp \
    sv_filepublish.cpp \
    sv_fileservercleanup.cpp \
    sv_publishtest.cpp \
    sv_recordingsession.cpp \
    sv_recordingsessionblock.cpp \
    sv_recordingsessionblockmanager.cpp \
    sv_recordingsessionmanager.cpp \
    sv_replaycontext.cpp \
    sv_sessionblockpublisher.cpp \
    sv_sessioninfopublisher.cpp \
    sv_sessionpublishmanager.cpp \
    sv_sessionrecorder.cpp \
    thinkmanager.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/common/linux32/replay_common.a \
    ../lib/common/linux32/lzma.a \
    ../lib/public/linux32/vtf.a \
    ../lib/common/linux32/bzip2.a \
    ../lib/common/linux32/libjpeg.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../lib/common/linux32/bzip2.a \
    ../lib/common/linux32/libjpeg.a \
    ../lib/common/linux32/lzma.a \
    ../lib/common/linux32/replay_common.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vtf.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/imageutils.P
endif

$(OBJ_DIR)/imageutils.o : $(abspath ../common/imageutils.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/netmessages.P
endif

$(OBJ_DIR)/netmessages.o : $(abspath ../common/netmessages.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baserecordingsession.P
endif

$(OBJ_DIR)/baserecordingsession.o : $(abspath baserecordingsession.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baserecordingsessionblock.P
endif

$(OBJ_DIR)/baserecordingsessionblock.o : $(abspath baserecordingsessionblock.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baserecordingsessionblockmanager.P
endif

$(OBJ_DIR)/baserecordingsessionblockmanager.o : $(abspath baserecordingsessionblockmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baserecordingsessionmanager.P
endif

$(OBJ_DIR)/baserecordingsessionmanager.o : $(abspath baserecordingsessionmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basethinker.P
endif

$(OBJ_DIR)/basethinker.o : $(abspath basethinker.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_commands.P
endif

$(OBJ_DIR)/cl_commands.o : $(abspath cl_commands.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_cvars.P
endif

$(OBJ_DIR)/cl_cvars.o : $(abspath cl_cvars.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_downloader.P
endif

$(OBJ_DIR)/cl_downloader.o : $(abspath cl_downloader.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_performancecontroller.P
endif

$(OBJ_DIR)/cl_performancecontroller.o : $(abspath cl_performancecontroller.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_performancemanager.P
endif

$(OBJ_DIR)/cl_performancemanager.o : $(abspath cl_performancemanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_recordingsession.P
endif

$(OBJ_DIR)/cl_recordingsession.o : $(abspath cl_recordingsession.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_recordingsessionblock.P
endif

$(OBJ_DIR)/cl_recordingsessionblock.o : $(abspath cl_recordingsessionblock.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_recordingsessionblockmanager.P
endif

$(OBJ_DIR)/cl_recordingsessionblockmanager.o : $(abspath cl_recordingsessionblockmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_recordingsessionmanager.P
endif

$(OBJ_DIR)/cl_recordingsessionmanager.o : $(abspath cl_recordingsessionmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_renderqueue.P
endif

$(OBJ_DIR)/cl_renderqueue.o : $(abspath cl_renderqueue.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_replaycontext.P
endif

$(OBJ_DIR)/cl_replaycontext.o : $(abspath cl_replaycontext.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_replaymanager.P
endif

$(OBJ_DIR)/cl_replaymanager.o : $(abspath cl_replaymanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_replaymovie.P
endif

$(OBJ_DIR)/cl_replaymovie.o : $(abspath cl_replaymovie.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_replaymoviemanager.P
endif

$(OBJ_DIR)/cl_replaymoviemanager.o : $(abspath cl_replaymoviemanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_screenshotmanager.P
endif

$(OBJ_DIR)/cl_screenshotmanager.o : $(abspath cl_screenshotmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_sessionblockdownloader.P
endif

$(OBJ_DIR)/cl_sessionblockdownloader.o : $(abspath cl_sessionblockdownloader.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_sessioninfodownloader.P
endif

$(OBJ_DIR)/cl_sessioninfodownloader.o : $(abspath cl_sessioninfodownloader.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/compression.P
endif

$(OBJ_DIR)/compression.o : $(abspath compression.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/errorsystem.P
endif

$(OBJ_DIR)/errorsystem.o : $(abspath errorsystem.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/managertest.P
endif

$(OBJ_DIR)/managertest.o : $(abspath managertest.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replaysystem.P
endif

$(OBJ_DIR)/replaysystem.o : $(abspath replaysystem.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replay_dbg.P
endif

$(OBJ_DIR)/replay_dbg.o : $(abspath replay_dbg.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replay_reconstructor.P
endif

$(OBJ_DIR)/replay_reconstructor.o : $(abspath replay_reconstructor.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sessioninfoheader.P
endif

$(OBJ_DIR)/sessioninfoheader.o : $(abspath sessioninfoheader.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shared_cvars.P
endif

$(OBJ_DIR)/shared_cvars.o : $(abspath shared_cvars.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shared_replaycontext.P
endif

$(OBJ_DIR)/shared_replaycontext.o : $(abspath shared_replaycontext.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spew.P
endif

$(OBJ_DIR)/spew.o : $(abspath spew.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_basejob.P
endif

$(OBJ_DIR)/sv_basejob.o : $(abspath sv_basejob.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_commands.P
endif

$(OBJ_DIR)/sv_commands.o : $(abspath sv_commands.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_cvars.P
endif

$(OBJ_DIR)/sv_cvars.o : $(abspath sv_cvars.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_filepublish.P
endif

$(OBJ_DIR)/sv_filepublish.o : $(abspath sv_filepublish.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_fileservercleanup.P
endif

$(OBJ_DIR)/sv_fileservercleanup.o : $(abspath sv_fileservercleanup.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_publishtest.P
endif

$(OBJ_DIR)/sv_publishtest.o : $(abspath sv_publishtest.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_recordingsession.P
endif

$(OBJ_DIR)/sv_recordingsession.o : $(abspath sv_recordingsession.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_recordingsessionblock.P
endif

$(OBJ_DIR)/sv_recordingsessionblock.o : $(abspath sv_recordingsessionblock.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_recordingsessionblockmanager.P
endif

$(OBJ_DIR)/sv_recordingsessionblockmanager.o : $(abspath sv_recordingsessionblockmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_recordingsessionmanager.P
endif

$(OBJ_DIR)/sv_recordingsessionmanager.o : $(abspath sv_recordingsessionmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_replaycontext.P
endif

$(OBJ_DIR)/sv_replaycontext.o : $(abspath sv_replaycontext.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_sessionblockpublisher.P
endif

$(OBJ_DIR)/sv_sessionblockpublisher.o : $(abspath sv_sessionblockpublisher.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_sessioninfopublisher.P
endif

$(OBJ_DIR)/sv_sessioninfopublisher.o : $(abspath sv_sessioninfopublisher.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_sessionpublishmanager.P
endif

$(OBJ_DIR)/sv_sessionpublishmanager.o : $(abspath sv_sessionpublishmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_sessionrecorder.P
endif

$(OBJ_DIR)/sv_sessionrecorder.o : $(abspath sv_sessionrecorder.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/thinkmanager.P
endif

$(OBJ_DIR)/thinkmanager.o : $(abspath thinkmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
SystemLibraries=-lrt -lcurl-gnutls 
DLL_EXT=.wasm
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=replay -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DREPLAY_DLL -DREPLAY_ENABLED -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/replay -D_DLL_EXT=.wasm -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/replay.wasm
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/replay.wasm


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../common/imageutils.cpp \
    ../common/netmessages.cpp \
    ../public/tier0/memoverride.cpp \
    baserecordingsession.cpp \
    baserecordingsessionblock.cpp \
    baserecordingsessionblockmanager.cpp \
    baserecordingsessionmanager.cpp \
    basethinker.cpp \
    cl_commands.cpp \
    cl_cvars.cpp \
    cl_downloader.cpp \
    cl_performancecontroller.cpp \
    cl_performancemanager.cpp \
    cl_recordingsession.cpp \
    cl_recordingsessionblock.cpp \
    cl_recordingsessionblockmanager.cpp \
    cl_recordingsessionmanager.cpp \
    cl_renderqueue.cpp \
    cl_replaycontext.cpp \
    cl_replaymanager.cpp \
    cl_replaymovie.cpp \
    cl_replaymoviemanager.cpp \
    cl_screenshotmanager.cpp \
    cl_sessionblockdownloader.cpp \
    cl_sessioninfodownloader.cpp \
    compression.cpp \
    errorsystem.cpp \
    managertest.cpp \
    replaysystem.cpp \
    replay_dbg.cpp \
    replay_reconstructor.cpp \
    sessioninfoheader.cpp \
    shared_cvars.cpp \
    shared_replaycontext.cpp \
    spew.cpp \
    sv_basejob.cpp \
    sv_commands.cpp \
    sv_cvars.cpp \
    sv_filepublish.cpp \
    sv_fileservercleanup.cpp \
    sv_publishtest.cpp \
    sv_recordingsession.cpp \
    sv_recordingsessionblock.cpp \
    sv_recordingsessionblockmanager.cpp \
    sv_recordingsessionmanager.cpp \
    sv_replaycontext.cpp \
    sv_sessionblockpublisher.cpp \
    sv_sessioninfopublisher.cpp \
    sv_sessionpublishmanager.cpp \
    sv_sessionrecorder.cpp \
    thinkmanager.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/common/linux32/replay_common.a \
    ../lib/common/linux32/lzma.a \
    ../lib/public/linux32/vtf.a \
    ../lib/common/linux32/bzip2.a \
    ../lib/common/linux32/libjpeg.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \


LIBFILENAMES = \
    ../lib/common/linux32/bzip2.a \
    ../lib/common/linux32/libjpeg.a \
    ../lib/common/linux32/lzma.a \
    ../lib/common/linux32/replay_common.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/vtf.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/imageutils.P
endif

$(OBJ_DIR)/imageutils.o : $(abspath ../common/imageutils.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/netmessages.P
endif

$(OBJ_DIR)/netmessages.o : $(abspath ../common/netmessages.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baserecordingsession.P
endif

$(OBJ_DIR)/baserecordingsession.o : $(abspath baserecordingsession.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baserecordingsessionblock.P
endif

$(OBJ_DIR)/baserecordingsessionblock.o : $(abspath baserecordingsessionblock.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baserecordingsessionblockmanager.P
endif

$(OBJ_DIR)/baserecordingsessionblockmanager.o : $(abspath baserecordingsessionblockmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/baserecordingsessionmanager.P
endif

$(OBJ_DIR)/baserecordingsessionmanager.o : $(abspath baserecordingsessionmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basethinker.P
endif

$(OBJ_DIR)/basethinker.o : $(abspath basethinker.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_commands.P
endif

$(OBJ_DIR)/cl_commands.o : $(abspath cl_commands.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_cvars.P
endif

$(OBJ_DIR)/cl_cvars.o : $(abspath cl_cvars.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_downloader.P
endif

$(OBJ_DIR)/cl_downloader.o : $(abspath cl_downloader.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_performancecontroller.P
endif

$(OBJ_DIR)/cl_performancecontroller.o : $(abspath cl_performancecontroller.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_performancemanager.P
endif

$(OBJ_DIR)/cl_performancemanager.o : $(abspath cl_performancemanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_recordingsession.P
endif

$(OBJ_DIR)/cl_recordingsession.o : $(abspath cl_recordingsession.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_recordingsessionblock.P
endif

$(OBJ_DIR)/cl_recordingsessionblock.o : $(abspath cl_recordingsessionblock.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_recordingsessionblockmanager.P
endif

$(OBJ_DIR)/cl_recordingsessionblockmanager.o : $(abspath cl_recordingsessionblockmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_recordingsessionmanager.P
endif

$(OBJ_DIR)/cl_recordingsessionmanager.o : $(abspath cl_recordingsessionmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_renderqueue.P
endif

$(OBJ_DIR)/cl_renderqueue.o : $(abspath cl_renderqueue.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_replaycontext.P
endif

$(OBJ_DIR)/cl_replaycontext.o : $(abspath cl_replaycontext.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_replaymanager.P
endif

$(OBJ_DIR)/cl_replaymanager.o : $(abspath cl_replaymanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_replaymovie.P
endif

$(OBJ_DIR)/cl_replaymovie.o : $(abspath cl_replaymovie.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_replaymoviemanager.P
endif

$(OBJ_DIR)/cl_replaymoviemanager.o : $(abspath cl_replaymoviemanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_screenshotmanager.P
endif

$(OBJ_DIR)/cl_screenshotmanager.o : $(abspath cl_screenshotmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_sessionblockdownloader.P
endif

$(OBJ_DIR)/cl_sessionblockdownloader.o : $(abspath cl_sessionblockdownloader.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cl_sessioninfodownloader.P
endif

$(OBJ_DIR)/cl_sessioninfodownloader.o : $(abspath cl_sessioninfodownloader.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/compression.P
endif

$(OBJ_DIR)/compression.o : $(abspath compression.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/errorsystem.P
endif

$(OBJ_DIR)/errorsystem.o : $(abspath errorsystem.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/managertest.P
endif

$(OBJ_DIR)/managertest.o : $(abspath managertest.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replaysystem.P
endif

$(OBJ_DIR)/replaysystem.o : $(abspath replaysystem.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replay_dbg.P
endif

$(OBJ_DIR)/replay_dbg.o : $(abspath replay_dbg.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/replay_reconstructor.P
endif

$(OBJ_DIR)/replay_reconstructor.o : $(abspath replay_reconstructor.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sessioninfoheader.P
endif

$(OBJ_DIR)/sessioninfoheader.o : $(abspath sessioninfoheader.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shared_cvars.P
endif

$(OBJ_DIR)/shared_cvars.o : $(abspath shared_cvars.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/shared_replaycontext.P
endif

$(OBJ_DIR)/shared_replaycontext.o : $(abspath shared_replaycontext.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/spew.P
endif

$(OBJ_DIR)/spew.o : $(abspath spew.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_basejob.P
endif

$(OBJ_DIR)/sv_basejob.o : $(abspath sv_basejob.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_commands.P
endif

$(OBJ_DIR)/sv_commands.o : $(abspath sv_commands.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_cvars.P
endif

$(OBJ_DIR)/sv_cvars.o : $(abspath sv_cvars.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_filepublish.P
endif

$(OBJ_DIR)/sv_filepublish.o : $(abspath sv_filepublish.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_fileservercleanup.P
endif

$(OBJ_DIR)/sv_fileservercleanup.o : $(abspath sv_fileservercleanup.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_publishtest.P
endif

$(OBJ_DIR)/sv_publishtest.o : $(abspath sv_publishtest.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_recordingsession.P
endif

$(OBJ_DIR)/sv_recordingsession.o : $(abspath sv_recordingsession.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_recordingsessionblock.P
endif

$(OBJ_DIR)/sv_recordingsessionblock.o : $(abspath sv_recordingsessionblock.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_recordingsessionblockmanager.P
endif

$(OBJ_DIR)/sv_recordingsessionblockmanager.o : $(abspath sv_recordingsessionblockmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_recordingsessionmanager.P
endif

$(OBJ_DIR)/sv_recordingsessionmanager.o : $(abspath sv_recordingsessionmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_replaycontext.P
endif

$(OBJ_DIR)/sv_replaycontext.o : $(abspath sv_replaycontext.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_sessionblockpublisher.P
endif

$(OBJ_DIR)/sv_sessionblockpublisher.o : $(abspath sv_sessionblockpublisher.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_sessioninfopublisher.P
endif

$(OBJ_DIR)/sv_sessioninfopublisher.o : $(abspath sv_sessioninfopublisher.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_sessionpublishmanager.P
endif

$(OBJ_DIR)/sv_sessionpublishmanager.o : $(abspath sv_sessionpublishmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sv_sessionrecorder.P
endif

$(OBJ_DIR)/sv_sessionrecorder.o : $(abspath sv_sessionrecorder.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/thinkmanager.P
endif

$(OBJ_DIR)/thinkmanager.o : $(abspath thinkmanager.cpp) $(PWD)/replay_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



