ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=gameui
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
SystemLibraries=-lrt 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=GameUI -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DGAMEUI_EXPORTS -DVERSION_SAFE_STEAM_API_INTERFACES -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/gameui -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ./ ../vgui2/include ../vgui2/controls ../common/GameUI 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/GameUI.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/GameUI.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../common/GameUI/cvarslider.cpp \
    ../common/GameUI/ObjectList.cpp \
    ../common/GameUI/scriptobject.cpp \
    ../common/imageutils.cpp \
    ../common/language.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/vgui_controls/vgui_controls.cpp \
    BackgroundMenuButton.cpp \
    BasePanel.cpp \
    BaseSaveGameDialog.cpp \
    BenchmarkDialog.cpp \
    BitmapImagePanel.cpp \
    BonusMapsDatabase.cpp \
    BonusMapsDialog.cpp \
    CommandCheckButton.cpp \
    CommentaryDialog.cpp \
    CommentaryExplanationDialog.cpp \
    ContentControlDialog.cpp \
    ControllerDialog.cpp \
    CreateMultiplayerGameBotPage.cpp \
    CreateMultiplayerGameDialog.cpp \
    CreateMultiplayerGameGameplayPage.cpp \
    CreateMultiplayerGameServerPage.cpp \
    CustomTabExplanationDialog.cpp \
    CvarNegateCheckButton.cpp \
    CvarTextEntry.cpp \
    CvarToggleCheckButton.cpp \
    GameConsole.cpp \
    GameConsoleDialog.cpp \
    GameUI_Interface.cpp \
    gameui_util.cpp \
    HapticControlBox.cpp \
    KeyToggleCheckButton.cpp \
    LabeledCommandComboBox.cpp \
    LoadCommentaryDialog.cpp \
    LoadGameDialog.cpp \
    LoadGameDialog_Xbox.cpp \
    LoadingDialog.cpp \
    matchmaking/achievementsdialog.cpp \
    matchmaking/basedialog.cpp \
    matchmaking/dialogmenu.cpp \
    matchmaking/leaderboarddialog.cpp \
    matchmaking/matchmakingbasepanel.cpp \
    matchmaking/pausedialog.cpp \
    matchmaking/sessionbrowserdialog.cpp \
    matchmaking/sessionlobbydialog.cpp \
    matchmaking/sessionoptionsdialog.cpp \
    matchmaking/welcomedialog.cpp \
    ModInfo.cpp \
    MouseMessageForwardingPanel.cpp \
    MultiplayerAdvancedDialog.cpp \
    NewGameDialog.cpp \
    OptionsDialog.cpp \
    OptionsDialog_Xbox.cpp \
    OptionsSubAudio.cpp \
    OptionsSubDifficulty.cpp \
    OptionsSubGame.cpp \
    OptionsSubKeyboard.cpp \
    OptionsSubMouse.cpp \
    OptionsSubMultiplayer.cpp \
    OptionsSubPortal.cpp \
    OptionsSubVideo.cpp \
    OptionsSubVoice.cpp \
    PanelListPanel.cpp \
    PlayerListDialog.cpp \
    RunGameEngine.cpp \
    SaveGameBrowserDialog.cpp \
    SaveGameDialog.cpp \
    SaveGameDialog_Xbox.cpp \
    Sys_Utils.cpp \
    TextEntryBox.cpp \
    TGAImagePanel.cpp \
    URLButton.cpp \
    vcontrolslistpanel.cpp \
    VGuiSystemModuleLoader.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/matsys_controls.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/vtf.a \
    ../lib/common/linux32/libjpeg.a \
    ../lib/public/linux32/libpng.a \
    ../lib/public/linux32/libz.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lsteam_api \
    -L../lib/public/linux32 -lSDL2 \


LIBFILENAMES = \
    ../lib/common/linux32/libjpeg.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/libpng.a \
    ../lib/public/linux32/libSDL2.so \
    ../lib/public/linux32/libsteam_api.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/libz.a \
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
-include $(OBJ_DIR)/cvarslider.P
endif

$(OBJ_DIR)/cvarslider.o : $(abspath ../common/GameUI/cvarslider.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ObjectList.P
endif

$(OBJ_DIR)/ObjectList.o : $(abspath ../common/GameUI/ObjectList.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scriptobject.P
endif

$(OBJ_DIR)/scriptobject.o : $(abspath ../common/GameUI/scriptobject.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/imageutils.P
endif

$(OBJ_DIR)/imageutils.o : $(abspath ../common/imageutils.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/language.P
endif

$(OBJ_DIR)/language.o : $(abspath ../common/language.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../public/vgui_controls/vgui_controls.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BackgroundMenuButton.P
endif

$(OBJ_DIR)/BackgroundMenuButton.o : $(abspath BackgroundMenuButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BasePanel.P
endif

$(OBJ_DIR)/BasePanel.o : $(abspath BasePanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseSaveGameDialog.P
endif

$(OBJ_DIR)/BaseSaveGameDialog.o : $(abspath BaseSaveGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BenchmarkDialog.P
endif

$(OBJ_DIR)/BenchmarkDialog.o : $(abspath BenchmarkDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BitmapImagePanel.P
endif

$(OBJ_DIR)/BitmapImagePanel.o : $(abspath BitmapImagePanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BonusMapsDatabase.P
endif

$(OBJ_DIR)/BonusMapsDatabase.o : $(abspath BonusMapsDatabase.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BonusMapsDialog.P
endif

$(OBJ_DIR)/BonusMapsDialog.o : $(abspath BonusMapsDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CommandCheckButton.P
endif

$(OBJ_DIR)/CommandCheckButton.o : $(abspath CommandCheckButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CommentaryDialog.P
endif

$(OBJ_DIR)/CommentaryDialog.o : $(abspath CommentaryDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CommentaryExplanationDialog.P
endif

$(OBJ_DIR)/CommentaryExplanationDialog.o : $(abspath CommentaryExplanationDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ContentControlDialog.P
endif

$(OBJ_DIR)/ContentControlDialog.o : $(abspath ContentControlDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ControllerDialog.P
endif

$(OBJ_DIR)/ControllerDialog.o : $(abspath ControllerDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CreateMultiplayerGameBotPage.P
endif

$(OBJ_DIR)/CreateMultiplayerGameBotPage.o : $(abspath CreateMultiplayerGameBotPage.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CreateMultiplayerGameDialog.P
endif

$(OBJ_DIR)/CreateMultiplayerGameDialog.o : $(abspath CreateMultiplayerGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CreateMultiplayerGameGameplayPage.P
endif

$(OBJ_DIR)/CreateMultiplayerGameGameplayPage.o : $(abspath CreateMultiplayerGameGameplayPage.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CreateMultiplayerGameServerPage.P
endif

$(OBJ_DIR)/CreateMultiplayerGameServerPage.o : $(abspath CreateMultiplayerGameServerPage.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CustomTabExplanationDialog.P
endif

$(OBJ_DIR)/CustomTabExplanationDialog.o : $(abspath CustomTabExplanationDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CvarNegateCheckButton.P
endif

$(OBJ_DIR)/CvarNegateCheckButton.o : $(abspath CvarNegateCheckButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CvarTextEntry.P
endif

$(OBJ_DIR)/CvarTextEntry.o : $(abspath CvarTextEntry.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CvarToggleCheckButton.P
endif

$(OBJ_DIR)/CvarToggleCheckButton.o : $(abspath CvarToggleCheckButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameConsole.P
endif

$(OBJ_DIR)/GameConsole.o : $(abspath GameConsole.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameConsoleDialog.P
endif

$(OBJ_DIR)/GameConsoleDialog.o : $(abspath GameConsoleDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameUI_Interface.P
endif

$(OBJ_DIR)/GameUI_Interface.o : $(abspath GameUI_Interface.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gameui_util.P
endif

$(OBJ_DIR)/gameui_util.o : $(abspath gameui_util.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HapticControlBox.P
endif

$(OBJ_DIR)/HapticControlBox.o : $(abspath HapticControlBox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/KeyToggleCheckButton.P
endif

$(OBJ_DIR)/KeyToggleCheckButton.o : $(abspath KeyToggleCheckButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LabeledCommandComboBox.P
endif

$(OBJ_DIR)/LabeledCommandComboBox.o : $(abspath LabeledCommandComboBox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadCommentaryDialog.P
endif

$(OBJ_DIR)/LoadCommentaryDialog.o : $(abspath LoadCommentaryDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadGameDialog.P
endif

$(OBJ_DIR)/LoadGameDialog.o : $(abspath LoadGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadGameDialog_Xbox.P
endif

$(OBJ_DIR)/LoadGameDialog_Xbox.o : $(abspath LoadGameDialog_Xbox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadingDialog.P
endif

$(OBJ_DIR)/LoadingDialog.o : $(abspath LoadingDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievementsdialog.P
endif

$(OBJ_DIR)/achievementsdialog.o : $(abspath matchmaking/achievementsdialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basedialog.P
endif

$(OBJ_DIR)/basedialog.o : $(abspath matchmaking/basedialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dialogmenu.P
endif

$(OBJ_DIR)/dialogmenu.o : $(abspath matchmaking/dialogmenu.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/leaderboarddialog.P
endif

$(OBJ_DIR)/leaderboarddialog.o : $(abspath matchmaking/leaderboarddialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingbasepanel.P
endif

$(OBJ_DIR)/matchmakingbasepanel.o : $(abspath matchmaking/matchmakingbasepanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pausedialog.P
endif

$(OBJ_DIR)/pausedialog.o : $(abspath matchmaking/pausedialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sessionbrowserdialog.P
endif

$(OBJ_DIR)/sessionbrowserdialog.o : $(abspath matchmaking/sessionbrowserdialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sessionlobbydialog.P
endif

$(OBJ_DIR)/sessionlobbydialog.o : $(abspath matchmaking/sessionlobbydialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sessionoptionsdialog.P
endif

$(OBJ_DIR)/sessionoptionsdialog.o : $(abspath matchmaking/sessionoptionsdialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/welcomedialog.P
endif

$(OBJ_DIR)/welcomedialog.o : $(abspath matchmaking/welcomedialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ModInfo.P
endif

$(OBJ_DIR)/ModInfo.o : $(abspath ModInfo.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MouseMessageForwardingPanel.P
endif

$(OBJ_DIR)/MouseMessageForwardingPanel.o : $(abspath MouseMessageForwardingPanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MultiplayerAdvancedDialog.P
endif

$(OBJ_DIR)/MultiplayerAdvancedDialog.o : $(abspath MultiplayerAdvancedDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/NewGameDialog.P
endif

$(OBJ_DIR)/NewGameDialog.o : $(abspath NewGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsDialog.P
endif

$(OBJ_DIR)/OptionsDialog.o : $(abspath OptionsDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsDialog_Xbox.P
endif

$(OBJ_DIR)/OptionsDialog_Xbox.o : $(abspath OptionsDialog_Xbox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubAudio.P
endif

$(OBJ_DIR)/OptionsSubAudio.o : $(abspath OptionsSubAudio.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubDifficulty.P
endif

$(OBJ_DIR)/OptionsSubDifficulty.o : $(abspath OptionsSubDifficulty.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubGame.P
endif

$(OBJ_DIR)/OptionsSubGame.o : $(abspath OptionsSubGame.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubKeyboard.P
endif

$(OBJ_DIR)/OptionsSubKeyboard.o : $(abspath OptionsSubKeyboard.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubMouse.P
endif

$(OBJ_DIR)/OptionsSubMouse.o : $(abspath OptionsSubMouse.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubMultiplayer.P
endif

$(OBJ_DIR)/OptionsSubMultiplayer.o : $(abspath OptionsSubMultiplayer.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubPortal.P
endif

$(OBJ_DIR)/OptionsSubPortal.o : $(abspath OptionsSubPortal.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubVideo.P
endif

$(OBJ_DIR)/OptionsSubVideo.o : $(abspath OptionsSubVideo.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubVoice.P
endif

$(OBJ_DIR)/OptionsSubVoice.o : $(abspath OptionsSubVoice.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PanelListPanel.P
endif

$(OBJ_DIR)/PanelListPanel.o : $(abspath PanelListPanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PlayerListDialog.P
endif

$(OBJ_DIR)/PlayerListDialog.o : $(abspath PlayerListDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/RunGameEngine.P
endif

$(OBJ_DIR)/RunGameEngine.o : $(abspath RunGameEngine.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SaveGameBrowserDialog.P
endif

$(OBJ_DIR)/SaveGameBrowserDialog.o : $(abspath SaveGameBrowserDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SaveGameDialog.P
endif

$(OBJ_DIR)/SaveGameDialog.o : $(abspath SaveGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SaveGameDialog_Xbox.P
endif

$(OBJ_DIR)/SaveGameDialog_Xbox.o : $(abspath SaveGameDialog_Xbox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Sys_Utils.P
endif

$(OBJ_DIR)/Sys_Utils.o : $(abspath Sys_Utils.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextEntryBox.P
endif

$(OBJ_DIR)/TextEntryBox.o : $(abspath TextEntryBox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TGAImagePanel.P
endif

$(OBJ_DIR)/TGAImagePanel.o : $(abspath TGAImagePanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/URLButton.P
endif

$(OBJ_DIR)/URLButton.o : $(abspath URLButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vcontrolslistpanel.P
endif

$(OBJ_DIR)/vcontrolslistpanel.o : $(abspath vcontrolslistpanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/VGuiSystemModuleLoader.P
endif

$(OBJ_DIR)/VGuiSystemModuleLoader.o : $(abspath VGuiSystemModuleLoader.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
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
SystemLibraries=-lrt 
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
DEFINES= -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DDLLNAME=GameUI -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DGAMEUI_EXPORTS -DVERSION_SAFE_STEAM_API_INTERFACES -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/gameui -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ./ ../vgui2/include ../vgui2/controls ../common/GameUI 
CONFTYPE=dll
IMPORTLIBRARY=
GAMEOUTPUTFILE=../lib/public/linux32/GameUI.so
TARGETCOPIES=
OUTPUTFILE=$(OBJ_DIR)/GameUI.so


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../common/GameUI/cvarslider.cpp \
    ../common/GameUI/ObjectList.cpp \
    ../common/GameUI/scriptobject.cpp \
    ../common/imageutils.cpp \
    ../common/language.cpp \
    ../public/tier0/memoverride.cpp \
    ../public/vgui_controls/vgui_controls.cpp \
    BackgroundMenuButton.cpp \
    BasePanel.cpp \
    BaseSaveGameDialog.cpp \
    BenchmarkDialog.cpp \
    BitmapImagePanel.cpp \
    BonusMapsDatabase.cpp \
    BonusMapsDialog.cpp \
    CommandCheckButton.cpp \
    CommentaryDialog.cpp \
    CommentaryExplanationDialog.cpp \
    ContentControlDialog.cpp \
    ControllerDialog.cpp \
    CreateMultiplayerGameBotPage.cpp \
    CreateMultiplayerGameDialog.cpp \
    CreateMultiplayerGameGameplayPage.cpp \
    CreateMultiplayerGameServerPage.cpp \
    CustomTabExplanationDialog.cpp \
    CvarNegateCheckButton.cpp \
    CvarTextEntry.cpp \
    CvarToggleCheckButton.cpp \
    GameConsole.cpp \
    GameConsoleDialog.cpp \
    GameUI_Interface.cpp \
    gameui_util.cpp \
    HapticControlBox.cpp \
    KeyToggleCheckButton.cpp \
    LabeledCommandComboBox.cpp \
    LoadCommentaryDialog.cpp \
    LoadGameDialog.cpp \
    LoadGameDialog_Xbox.cpp \
    LoadingDialog.cpp \
    matchmaking/achievementsdialog.cpp \
    matchmaking/basedialog.cpp \
    matchmaking/dialogmenu.cpp \
    matchmaking/leaderboarddialog.cpp \
    matchmaking/matchmakingbasepanel.cpp \
    matchmaking/pausedialog.cpp \
    matchmaking/sessionbrowserdialog.cpp \
    matchmaking/sessionlobbydialog.cpp \
    matchmaking/sessionoptionsdialog.cpp \
    matchmaking/welcomedialog.cpp \
    ModInfo.cpp \
    MouseMessageForwardingPanel.cpp \
    MultiplayerAdvancedDialog.cpp \
    NewGameDialog.cpp \
    OptionsDialog.cpp \
    OptionsDialog_Xbox.cpp \
    OptionsSubAudio.cpp \
    OptionsSubDifficulty.cpp \
    OptionsSubGame.cpp \
    OptionsSubKeyboard.cpp \
    OptionsSubMouse.cpp \
    OptionsSubMultiplayer.cpp \
    OptionsSubPortal.cpp \
    OptionsSubVideo.cpp \
    OptionsSubVoice.cpp \
    PanelListPanel.cpp \
    PlayerListDialog.cpp \
    RunGameEngine.cpp \
    SaveGameBrowserDialog.cpp \
    SaveGameDialog.cpp \
    SaveGameDialog_Xbox.cpp \
    Sys_Utils.cpp \
    TextEntryBox.cpp \
    TGAImagePanel.cpp \
    URLButton.cpp \
    vcontrolslistpanel.cpp \
    VGuiSystemModuleLoader.cpp \


LIBFILES = \
    ../lib/public/linux32/tier1.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/mathlib.a \
    ../lib/public/linux32/matsys_controls.a \
    ../lib/public/linux32/tier2.a \
    ../lib/public/linux32/tier3.a \
    ../lib/public/linux32/vgui_controls.a \
    ../lib/public/linux32/vtf.a \
    ../lib/common/linux32/libjpeg.a \
    ../lib/public/linux32/libpng.a \
    ../lib/public/linux32/libz.a \
    -L../lib/public/linux32 -ltier0 \
    -L../lib/public/linux32 -lvstdlib \
    -L../lib/public/linux32 -lsteam_api \
    -L../lib/public/linux32 -lSDL2 \


LIBFILENAMES = \
    ../lib/common/linux32/libjpeg.a \
    ../lib/public/linux32/bitmap.a \
    ../lib/public/linux32/libpng.a \
    ../lib/public/linux32/libSDL2.so \
    ../lib/public/linux32/libsteam_api.so \
    ../lib/public/linux32/libtier0.so \
    ../lib/public/linux32/libvstdlib.so \
    ../lib/public/linux32/libz.a \
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
-include $(OBJ_DIR)/cvarslider.P
endif

$(OBJ_DIR)/cvarslider.o : $(abspath ../common/GameUI/cvarslider.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ObjectList.P
endif

$(OBJ_DIR)/ObjectList.o : $(abspath ../common/GameUI/ObjectList.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/scriptobject.P
endif

$(OBJ_DIR)/scriptobject.o : $(abspath ../common/GameUI/scriptobject.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/imageutils.P
endif

$(OBJ_DIR)/imageutils.o : $(abspath ../common/imageutils.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/language.P
endif

$(OBJ_DIR)/language.o : $(abspath ../common/language.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../public/tier0/memoverride.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../public/vgui_controls/vgui_controls.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BackgroundMenuButton.P
endif

$(OBJ_DIR)/BackgroundMenuButton.o : $(abspath BackgroundMenuButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BasePanel.P
endif

$(OBJ_DIR)/BasePanel.o : $(abspath BasePanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BaseSaveGameDialog.P
endif

$(OBJ_DIR)/BaseSaveGameDialog.o : $(abspath BaseSaveGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BenchmarkDialog.P
endif

$(OBJ_DIR)/BenchmarkDialog.o : $(abspath BenchmarkDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BitmapImagePanel.P
endif

$(OBJ_DIR)/BitmapImagePanel.o : $(abspath BitmapImagePanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BonusMapsDatabase.P
endif

$(OBJ_DIR)/BonusMapsDatabase.o : $(abspath BonusMapsDatabase.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BonusMapsDialog.P
endif

$(OBJ_DIR)/BonusMapsDialog.o : $(abspath BonusMapsDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CommandCheckButton.P
endif

$(OBJ_DIR)/CommandCheckButton.o : $(abspath CommandCheckButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CommentaryDialog.P
endif

$(OBJ_DIR)/CommentaryDialog.o : $(abspath CommentaryDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CommentaryExplanationDialog.P
endif

$(OBJ_DIR)/CommentaryExplanationDialog.o : $(abspath CommentaryExplanationDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ContentControlDialog.P
endif

$(OBJ_DIR)/ContentControlDialog.o : $(abspath ContentControlDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ControllerDialog.P
endif

$(OBJ_DIR)/ControllerDialog.o : $(abspath ControllerDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CreateMultiplayerGameBotPage.P
endif

$(OBJ_DIR)/CreateMultiplayerGameBotPage.o : $(abspath CreateMultiplayerGameBotPage.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CreateMultiplayerGameDialog.P
endif

$(OBJ_DIR)/CreateMultiplayerGameDialog.o : $(abspath CreateMultiplayerGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CreateMultiplayerGameGameplayPage.P
endif

$(OBJ_DIR)/CreateMultiplayerGameGameplayPage.o : $(abspath CreateMultiplayerGameGameplayPage.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CreateMultiplayerGameServerPage.P
endif

$(OBJ_DIR)/CreateMultiplayerGameServerPage.o : $(abspath CreateMultiplayerGameServerPage.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CustomTabExplanationDialog.P
endif

$(OBJ_DIR)/CustomTabExplanationDialog.o : $(abspath CustomTabExplanationDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CvarNegateCheckButton.P
endif

$(OBJ_DIR)/CvarNegateCheckButton.o : $(abspath CvarNegateCheckButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CvarTextEntry.P
endif

$(OBJ_DIR)/CvarTextEntry.o : $(abspath CvarTextEntry.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CvarToggleCheckButton.P
endif

$(OBJ_DIR)/CvarToggleCheckButton.o : $(abspath CvarToggleCheckButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameConsole.P
endif

$(OBJ_DIR)/GameConsole.o : $(abspath GameConsole.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameConsoleDialog.P
endif

$(OBJ_DIR)/GameConsoleDialog.o : $(abspath GameConsoleDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GameUI_Interface.P
endif

$(OBJ_DIR)/GameUI_Interface.o : $(abspath GameUI_Interface.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gameui_util.P
endif

$(OBJ_DIR)/gameui_util.o : $(abspath gameui_util.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HapticControlBox.P
endif

$(OBJ_DIR)/HapticControlBox.o : $(abspath HapticControlBox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/KeyToggleCheckButton.P
endif

$(OBJ_DIR)/KeyToggleCheckButton.o : $(abspath KeyToggleCheckButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LabeledCommandComboBox.P
endif

$(OBJ_DIR)/LabeledCommandComboBox.o : $(abspath LabeledCommandComboBox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadCommentaryDialog.P
endif

$(OBJ_DIR)/LoadCommentaryDialog.o : $(abspath LoadCommentaryDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadGameDialog.P
endif

$(OBJ_DIR)/LoadGameDialog.o : $(abspath LoadGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadGameDialog_Xbox.P
endif

$(OBJ_DIR)/LoadGameDialog_Xbox.o : $(abspath LoadGameDialog_Xbox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LoadingDialog.P
endif

$(OBJ_DIR)/LoadingDialog.o : $(abspath LoadingDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/achievementsdialog.P
endif

$(OBJ_DIR)/achievementsdialog.o : $(abspath matchmaking/achievementsdialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/basedialog.P
endif

$(OBJ_DIR)/basedialog.o : $(abspath matchmaking/basedialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/dialogmenu.P
endif

$(OBJ_DIR)/dialogmenu.o : $(abspath matchmaking/dialogmenu.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/leaderboarddialog.P
endif

$(OBJ_DIR)/leaderboarddialog.o : $(abspath matchmaking/leaderboarddialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/matchmakingbasepanel.P
endif

$(OBJ_DIR)/matchmakingbasepanel.o : $(abspath matchmaking/matchmakingbasepanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/pausedialog.P
endif

$(OBJ_DIR)/pausedialog.o : $(abspath matchmaking/pausedialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sessionbrowserdialog.P
endif

$(OBJ_DIR)/sessionbrowserdialog.o : $(abspath matchmaking/sessionbrowserdialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sessionlobbydialog.P
endif

$(OBJ_DIR)/sessionlobbydialog.o : $(abspath matchmaking/sessionlobbydialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sessionoptionsdialog.P
endif

$(OBJ_DIR)/sessionoptionsdialog.o : $(abspath matchmaking/sessionoptionsdialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/welcomedialog.P
endif

$(OBJ_DIR)/welcomedialog.o : $(abspath matchmaking/welcomedialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ModInfo.P
endif

$(OBJ_DIR)/ModInfo.o : $(abspath ModInfo.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MouseMessageForwardingPanel.P
endif

$(OBJ_DIR)/MouseMessageForwardingPanel.o : $(abspath MouseMessageForwardingPanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MultiplayerAdvancedDialog.P
endif

$(OBJ_DIR)/MultiplayerAdvancedDialog.o : $(abspath MultiplayerAdvancedDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/NewGameDialog.P
endif

$(OBJ_DIR)/NewGameDialog.o : $(abspath NewGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsDialog.P
endif

$(OBJ_DIR)/OptionsDialog.o : $(abspath OptionsDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsDialog_Xbox.P
endif

$(OBJ_DIR)/OptionsDialog_Xbox.o : $(abspath OptionsDialog_Xbox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubAudio.P
endif

$(OBJ_DIR)/OptionsSubAudio.o : $(abspath OptionsSubAudio.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubDifficulty.P
endif

$(OBJ_DIR)/OptionsSubDifficulty.o : $(abspath OptionsSubDifficulty.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubGame.P
endif

$(OBJ_DIR)/OptionsSubGame.o : $(abspath OptionsSubGame.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubKeyboard.P
endif

$(OBJ_DIR)/OptionsSubKeyboard.o : $(abspath OptionsSubKeyboard.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubMouse.P
endif

$(OBJ_DIR)/OptionsSubMouse.o : $(abspath OptionsSubMouse.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubMultiplayer.P
endif

$(OBJ_DIR)/OptionsSubMultiplayer.o : $(abspath OptionsSubMultiplayer.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubPortal.P
endif

$(OBJ_DIR)/OptionsSubPortal.o : $(abspath OptionsSubPortal.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubVideo.P
endif

$(OBJ_DIR)/OptionsSubVideo.o : $(abspath OptionsSubVideo.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/OptionsSubVoice.P
endif

$(OBJ_DIR)/OptionsSubVoice.o : $(abspath OptionsSubVoice.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PanelListPanel.P
endif

$(OBJ_DIR)/PanelListPanel.o : $(abspath PanelListPanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PlayerListDialog.P
endif

$(OBJ_DIR)/PlayerListDialog.o : $(abspath PlayerListDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/RunGameEngine.P
endif

$(OBJ_DIR)/RunGameEngine.o : $(abspath RunGameEngine.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SaveGameBrowserDialog.P
endif

$(OBJ_DIR)/SaveGameBrowserDialog.o : $(abspath SaveGameBrowserDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SaveGameDialog.P
endif

$(OBJ_DIR)/SaveGameDialog.o : $(abspath SaveGameDialog.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SaveGameDialog_Xbox.P
endif

$(OBJ_DIR)/SaveGameDialog_Xbox.o : $(abspath SaveGameDialog_Xbox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Sys_Utils.P
endif

$(OBJ_DIR)/Sys_Utils.o : $(abspath Sys_Utils.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextEntryBox.P
endif

$(OBJ_DIR)/TextEntryBox.o : $(abspath TextEntryBox.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TGAImagePanel.P
endif

$(OBJ_DIR)/TGAImagePanel.o : $(abspath TGAImagePanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/URLButton.P
endif

$(OBJ_DIR)/URLButton.o : $(abspath URLButton.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vcontrolslistpanel.P
endif

$(OBJ_DIR)/vcontrolslistpanel.o : $(abspath vcontrolslistpanel.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/VGuiSystemModuleLoader.P
endif

$(OBJ_DIR)/VGuiSystemModuleLoader.o : $(abspath VGuiSystemModuleLoader.cpp) $(PWD)/GameUI_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)


endif # (CFG=release)



