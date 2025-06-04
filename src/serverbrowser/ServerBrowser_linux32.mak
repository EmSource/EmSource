ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=serverbrowser
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
OptimizerLevel=-gdwarf-4 -g2 $(OptimizerLevel_CompilerSpecific)
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=ServerBrowser -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVERSION_SAFE_STEAM_API_INTERFACES -DSERVERBROWSER_EXPORTS -DGAME_SRC -D_USE_32BIT_TIME_T -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/guest/Downloads/src/src/serverbrowser -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/ServerBrowser.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/ServerBrowser.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../common/ServerBrowser/blacklisted_server_manager.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/vgui_controls/vgui_controls.cpp \
    BaseGamesPage.cpp \
    BlacklistedServers.cpp \
    CustomGames.cpp \
    DialogAddServer.cpp \
    DialogGameInfo.cpp \
    DialogServerPassword.cpp \
    FavoriteGames.cpp \
    FriendsGames.cpp \
    HistoryGames.cpp \
    InternetGames.cpp \
    LanGames.cpp \
    ModList.cpp \
    QuickListPanel.cpp \
    ServerBrowser.cpp \
    ServerBrowserDialog.cpp \
    ServerContextMenu.cpp \
    ServerListCompare.cpp \
    SpectateGames.cpp \
    VACBannedConnRefusedDialog.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/mathlib.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lsteam_api \


LIBFILENAMES = \
    ../lib/public/linux32/libsteam_api.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/blacklisted_server_manager.P
endif

$(OBJ_DIR)/blacklisted_server_manager.o : $(abspath ../common/ServerBrowser/blacklisted_server_manager.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../public/vgui_controls/vgui_controls.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseGamesPage.P
endif

$(OBJ_DIR)/BaseGamesPage.o : $(abspath BaseGamesPage.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BlacklistedServers.P
endif

$(OBJ_DIR)/BlacklistedServers.o : $(abspath BlacklistedServers.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CustomGames.P
endif

$(OBJ_DIR)/CustomGames.o : $(abspath CustomGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DialogAddServer.P
endif

$(OBJ_DIR)/DialogAddServer.o : $(abspath DialogAddServer.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DialogGameInfo.P
endif

$(OBJ_DIR)/DialogGameInfo.o : $(abspath DialogGameInfo.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DialogServerPassword.P
endif

$(OBJ_DIR)/DialogServerPassword.o : $(abspath DialogServerPassword.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FavoriteGames.P
endif

$(OBJ_DIR)/FavoriteGames.o : $(abspath FavoriteGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FriendsGames.P
endif

$(OBJ_DIR)/FriendsGames.o : $(abspath FriendsGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HistoryGames.P
endif

$(OBJ_DIR)/HistoryGames.o : $(abspath HistoryGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/InternetGames.P
endif

$(OBJ_DIR)/InternetGames.o : $(abspath InternetGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LanGames.P
endif

$(OBJ_DIR)/LanGames.o : $(abspath LanGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ModList.P
endif

$(OBJ_DIR)/ModList.o : $(abspath ModList.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/QuickListPanel.P
endif

$(OBJ_DIR)/QuickListPanel.o : $(abspath QuickListPanel.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerBrowser.P
endif

$(OBJ_DIR)/ServerBrowser.o : $(abspath ServerBrowser.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerBrowserDialog.P
endif

$(OBJ_DIR)/ServerBrowserDialog.o : $(abspath ServerBrowserDialog.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerContextMenu.P
endif

$(OBJ_DIR)/ServerContextMenu.o : $(abspath ServerContextMenu.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerListCompare.P
endif

$(OBJ_DIR)/ServerListCompare.o : $(abspath ServerListCompare.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SpectateGames.P
endif

$(OBJ_DIR)/SpectateGames.o : $(abspath SpectateGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/VACBannedConnRefusedDialog.P
endif

$(OBJ_DIR)/VACBannedConnRefusedDialog.o : $(abspath VACBannedConnRefusedDialog.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
OptimizerLevel=-gdwarf-4 -g2 $(OptimizerLevel_CompilerSpecific)
SystemLibraries=
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=ServerBrowser -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DVERSION_SAFE_STEAM_API_INTERFACES -DSERVERBROWSER_EXPORTS -DGAME_SRC -D_USE_32BIT_TIME_T -D_EXTERNAL_DLL_EXT=.so -DVPCGAMECAPS=HL2 -DPROJECTDIR=/home/guest/Downloads/src/src/serverbrowser -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_LINUX=1 -D_POSIX=1 -DLINUX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/ServerBrowser.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/ServerBrowser.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../common/ServerBrowser/blacklisted_server_manager.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/vgui_controls/vgui_controls.cpp \
    BaseGamesPage.cpp \
    BlacklistedServers.cpp \
    CustomGames.cpp \
    DialogAddServer.cpp \
    DialogGameInfo.cpp \
    DialogServerPassword.cpp \
    FavoriteGames.cpp \
    FriendsGames.cpp \
    HistoryGames.cpp \
    InternetGames.cpp \
    LanGames.cpp \
    ModList.cpp \
    QuickListPanel.cpp \
    ServerBrowser.cpp \
    ServerBrowserDialog.cpp \
    ServerContextMenu.cpp \
    ServerListCompare.cpp \
    SpectateGames.cpp \
    VACBannedConnRefusedDialog.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/mathlib.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lsteam_api \


LIBFILENAMES = \
    ../lib/public/linux32/libsteam_api.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/blacklisted_server_manager.P
endif

$(OBJ_DIR)/blacklisted_server_manager.o : $(abspath ../common/ServerBrowser/blacklisted_server_manager.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../public/vgui_controls/vgui_controls.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseGamesPage.P
endif

$(OBJ_DIR)/BaseGamesPage.o : $(abspath BaseGamesPage.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BlacklistedServers.P
endif

$(OBJ_DIR)/BlacklistedServers.o : $(abspath BlacklistedServers.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CustomGames.P
endif

$(OBJ_DIR)/CustomGames.o : $(abspath CustomGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DialogAddServer.P
endif

$(OBJ_DIR)/DialogAddServer.o : $(abspath DialogAddServer.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DialogGameInfo.P
endif

$(OBJ_DIR)/DialogGameInfo.o : $(abspath DialogGameInfo.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DialogServerPassword.P
endif

$(OBJ_DIR)/DialogServerPassword.o : $(abspath DialogServerPassword.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FavoriteGames.P
endif

$(OBJ_DIR)/FavoriteGames.o : $(abspath FavoriteGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FriendsGames.P
endif

$(OBJ_DIR)/FriendsGames.o : $(abspath FriendsGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HistoryGames.P
endif

$(OBJ_DIR)/HistoryGames.o : $(abspath HistoryGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/InternetGames.P
endif

$(OBJ_DIR)/InternetGames.o : $(abspath InternetGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LanGames.P
endif

$(OBJ_DIR)/LanGames.o : $(abspath LanGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ModList.P
endif

$(OBJ_DIR)/ModList.o : $(abspath ModList.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/QuickListPanel.P
endif

$(OBJ_DIR)/QuickListPanel.o : $(abspath QuickListPanel.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerBrowser.P
endif

$(OBJ_DIR)/ServerBrowser.o : $(abspath ServerBrowser.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerBrowserDialog.P
endif

$(OBJ_DIR)/ServerBrowserDialog.o : $(abspath ServerBrowserDialog.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerContextMenu.P
endif

$(OBJ_DIR)/ServerContextMenu.o : $(abspath ServerContextMenu.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ServerListCompare.P
endif

$(OBJ_DIR)/ServerListCompare.o : $(abspath ServerListCompare.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SpectateGames.P
endif

$(OBJ_DIR)/SpectateGames.o : $(abspath SpectateGames.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/VACBannedConnRefusedDialog.P
endif

$(OBJ_DIR)/VACBannedConnRefusedDialog.o : $(abspath VACBannedConnRefusedDialog.cpp) $(PWD)/ServerBrowser_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



