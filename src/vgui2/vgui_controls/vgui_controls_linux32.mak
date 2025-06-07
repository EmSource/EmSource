ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=vgui_controls
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
DLL_EXT=.wasm
SYM_EXT=.dbg
FORCEINCLUDES= 
ifeq "$(CFG)" "debug"
DEFINES += -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/vgui2/vgui_controls -D_DLL_EXT=.wasm -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
else
DEFINES += -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.wasm -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/vgui2/vgui_controls -D_DLL_EXT=.wasm -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
endif
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 generated_proto ../../thirdparty/protobuf-2.6.1/src ../../thirdparty ../../thirdparty/cef generated_proto 
CONFTYPE=lib
GAMEOUTPUTFILE=../../lib/public/linux32/vgui_controls.a
TARGETCOPIES=
OUTPUTFILE=vgui_controls.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../public/filesystem_helpers.cpp \
    ../../vgui2/src/vgui_key_translation.cpp \
    AnalogBar.cpp \
    AnimatingImagePanel.cpp \
    AnimationController.cpp \
    BitmapImagePanel.cpp \
    BuildFactoryHelper.cpp \
    BuildGroup.cpp \
    BuildModeDialog.cpp \
    Button.cpp \
    CheckButton.cpp \
    CheckButtonList.cpp \
    CircularProgressBar.cpp \
    ComboBox.cpp \
    consoledialog.cpp \
    ControllerMap.cpp \
    controls.cpp \
    cvartogglecheckbutton.cpp \
    DirectorySelectDialog.cpp \
    Divider.cpp \
    EditablePanel.cpp \
    ExpandButton.cpp \
    FileOpenDialog.cpp \
    FileOpenStateMachine.cpp \
    FocusNavGroup.cpp \
    Frame.cpp \
    GraphPanel.cpp \
    Image.cpp \
    ImageList.cpp \
    ImagePanel.cpp \
    InputDialog.cpp \
    KeyBindingHelpDialog.cpp \
    KeyBoardEditorDialog.cpp \
    KeyRepeat.cpp \
    Label.cpp \
    ListPanel.cpp \
    ListViewPanel.cpp \
    Menu.cpp \
    MenuBar.cpp \
    MenuButton.cpp \
    MenuItem.cpp \
    MessageBox.cpp \
    MessageDialog.cpp \
    Panel.cpp \
    PanelListPanel.cpp \
    PerforceFileExplorer.cpp \
    PerforceFileList.cpp \
    perforcefilelistframe.cpp \
    ProgressBar.cpp \
    ProgressBox.cpp \
    PropertyDialog.cpp \
    PropertyPage.cpp \
    PropertySheet.cpp \
    QueryBox.cpp \
    RadioButton.cpp \
    RichText.cpp \
    RotatingProgressBar.cpp \
    savedocumentquery.cpp \
    ScalableImagePanel.cpp \
    ScrollableEditablePanel.cpp \
    ScrollBar.cpp \
    ScrollBarSlider.cpp \
    SectionedListPanel.cpp \
    Slider.cpp \
    Splitter.cpp \
    subrectimage.cpp \
    TextEntry.cpp \
    TextImage.cpp \
    ToggleButton.cpp \
    Tooltip.cpp \
    ToolWindow.cpp \
    TreeView.cpp \
    TreeViewListControl.cpp \
    URLLabel.cpp \
    WizardPanel.cpp \
    WizardSubPanel.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/filesystem_helpers.P
endif

$(OBJ_DIR)/filesystem_helpers.o : $(abspath ../../public/filesystem_helpers.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_key_translation.P
endif

$(OBJ_DIR)/vgui_key_translation.o : $(abspath ../../vgui2/src/vgui_key_translation.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AnalogBar.P
endif

$(OBJ_DIR)/AnalogBar.o : $(abspath AnalogBar.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AnimatingImagePanel.P
endif

$(OBJ_DIR)/AnimatingImagePanel.o : $(abspath AnimatingImagePanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AnimationController.P
endif

$(OBJ_DIR)/AnimationController.o : $(abspath AnimationController.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BitmapImagePanel.P
endif

$(OBJ_DIR)/BitmapImagePanel.o : $(abspath BitmapImagePanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BuildFactoryHelper.P
endif

$(OBJ_DIR)/BuildFactoryHelper.o : $(abspath BuildFactoryHelper.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BuildGroup.P
endif

$(OBJ_DIR)/BuildGroup.o : $(abspath BuildGroup.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/BuildModeDialog.P
endif

$(OBJ_DIR)/BuildModeDialog.o : $(abspath BuildModeDialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Button.P
endif

$(OBJ_DIR)/Button.o : $(abspath Button.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CheckButton.P
endif

$(OBJ_DIR)/CheckButton.o : $(abspath CheckButton.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CheckButtonList.P
endif

$(OBJ_DIR)/CheckButtonList.o : $(abspath CheckButtonList.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CircularProgressBar.P
endif

$(OBJ_DIR)/CircularProgressBar.o : $(abspath CircularProgressBar.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ComboBox.P
endif

$(OBJ_DIR)/ComboBox.o : $(abspath ComboBox.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/consoledialog.P
endif

$(OBJ_DIR)/consoledialog.o : $(abspath consoledialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ControllerMap.P
endif

$(OBJ_DIR)/ControllerMap.o : $(abspath ControllerMap.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/controls.P
endif

$(OBJ_DIR)/controls.o : $(abspath controls.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/cvartogglecheckbutton.P
endif

$(OBJ_DIR)/cvartogglecheckbutton.o : $(abspath cvartogglecheckbutton.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DirectorySelectDialog.P
endif

$(OBJ_DIR)/DirectorySelectDialog.o : $(abspath DirectorySelectDialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Divider.P
endif

$(OBJ_DIR)/Divider.o : $(abspath Divider.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EditablePanel.P
endif

$(OBJ_DIR)/EditablePanel.o : $(abspath EditablePanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ExpandButton.P
endif

$(OBJ_DIR)/ExpandButton.o : $(abspath ExpandButton.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FileOpenDialog.P
endif

$(OBJ_DIR)/FileOpenDialog.o : $(abspath FileOpenDialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FileOpenStateMachine.P
endif

$(OBJ_DIR)/FileOpenStateMachine.o : $(abspath FileOpenStateMachine.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FocusNavGroup.P
endif

$(OBJ_DIR)/FocusNavGroup.o : $(abspath FocusNavGroup.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Frame.P
endif

$(OBJ_DIR)/Frame.o : $(abspath Frame.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/GraphPanel.P
endif

$(OBJ_DIR)/GraphPanel.o : $(abspath GraphPanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Image.P
endif

$(OBJ_DIR)/Image.o : $(abspath Image.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ImageList.P
endif

$(OBJ_DIR)/ImageList.o : $(abspath ImageList.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ImagePanel.P
endif

$(OBJ_DIR)/ImagePanel.o : $(abspath ImagePanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/InputDialog.P
endif

$(OBJ_DIR)/InputDialog.o : $(abspath InputDialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/KeyBindingHelpDialog.P
endif

$(OBJ_DIR)/KeyBindingHelpDialog.o : $(abspath KeyBindingHelpDialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/KeyBoardEditorDialog.P
endif

$(OBJ_DIR)/KeyBoardEditorDialog.o : $(abspath KeyBoardEditorDialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/KeyRepeat.P
endif

$(OBJ_DIR)/KeyRepeat.o : $(abspath KeyRepeat.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Label.P
endif

$(OBJ_DIR)/Label.o : $(abspath Label.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ListPanel.P
endif

$(OBJ_DIR)/ListPanel.o : $(abspath ListPanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ListViewPanel.P
endif

$(OBJ_DIR)/ListViewPanel.o : $(abspath ListViewPanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Menu.P
endif

$(OBJ_DIR)/Menu.o : $(abspath Menu.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MenuBar.P
endif

$(OBJ_DIR)/MenuBar.o : $(abspath MenuBar.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MenuButton.P
endif

$(OBJ_DIR)/MenuButton.o : $(abspath MenuButton.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MenuItem.P
endif

$(OBJ_DIR)/MenuItem.o : $(abspath MenuItem.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MessageBox.P
endif

$(OBJ_DIR)/MessageBox.o : $(abspath MessageBox.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MessageDialog.P
endif

$(OBJ_DIR)/MessageDialog.o : $(abspath MessageDialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Panel.P
endif

$(OBJ_DIR)/Panel.o : $(abspath Panel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PanelListPanel.P
endif

$(OBJ_DIR)/PanelListPanel.o : $(abspath PanelListPanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PerforceFileExplorer.P
endif

$(OBJ_DIR)/PerforceFileExplorer.o : $(abspath PerforceFileExplorer.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PerforceFileList.P
endif

$(OBJ_DIR)/PerforceFileList.o : $(abspath PerforceFileList.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/perforcefilelistframe.P
endif

$(OBJ_DIR)/perforcefilelistframe.o : $(abspath perforcefilelistframe.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ProgressBar.P
endif

$(OBJ_DIR)/ProgressBar.o : $(abspath ProgressBar.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ProgressBox.P
endif

$(OBJ_DIR)/ProgressBox.o : $(abspath ProgressBox.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PropertyDialog.P
endif

$(OBJ_DIR)/PropertyDialog.o : $(abspath PropertyDialog.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PropertyPage.P
endif

$(OBJ_DIR)/PropertyPage.o : $(abspath PropertyPage.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/PropertySheet.P
endif

$(OBJ_DIR)/PropertySheet.o : $(abspath PropertySheet.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/QueryBox.P
endif

$(OBJ_DIR)/QueryBox.o : $(abspath QueryBox.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/RadioButton.P
endif

$(OBJ_DIR)/RadioButton.o : $(abspath RadioButton.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/RichText.P
endif

$(OBJ_DIR)/RichText.o : $(abspath RichText.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/RotatingProgressBar.P
endif

$(OBJ_DIR)/RotatingProgressBar.o : $(abspath RotatingProgressBar.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/savedocumentquery.P
endif

$(OBJ_DIR)/savedocumentquery.o : $(abspath savedocumentquery.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScalableImagePanel.P
endif

$(OBJ_DIR)/ScalableImagePanel.o : $(abspath ScalableImagePanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScrollableEditablePanel.P
endif

$(OBJ_DIR)/ScrollableEditablePanel.o : $(abspath ScrollableEditablePanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScrollBar.P
endif

$(OBJ_DIR)/ScrollBar.o : $(abspath ScrollBar.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScrollBarSlider.P
endif

$(OBJ_DIR)/ScrollBarSlider.o : $(abspath ScrollBarSlider.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SectionedListPanel.P
endif

$(OBJ_DIR)/SectionedListPanel.o : $(abspath SectionedListPanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Slider.P
endif

$(OBJ_DIR)/Slider.o : $(abspath Slider.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Splitter.P
endif

$(OBJ_DIR)/Splitter.o : $(abspath Splitter.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/subrectimage.P
endif

$(OBJ_DIR)/subrectimage.o : $(abspath subrectimage.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextEntry.P
endif

$(OBJ_DIR)/TextEntry.o : $(abspath TextEntry.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextImage.P
endif

$(OBJ_DIR)/TextImage.o : $(abspath TextImage.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ToggleButton.P
endif

$(OBJ_DIR)/ToggleButton.o : $(abspath ToggleButton.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Tooltip.P
endif

$(OBJ_DIR)/Tooltip.o : $(abspath Tooltip.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ToolWindow.P
endif

$(OBJ_DIR)/ToolWindow.o : $(abspath ToolWindow.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TreeView.P
endif

$(OBJ_DIR)/TreeView.o : $(abspath TreeView.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TreeViewListControl.P
endif

$(OBJ_DIR)/TreeViewListControl.o : $(abspath TreeViewListControl.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/URLLabel.P
endif

$(OBJ_DIR)/URLLabel.o : $(abspath URLLabel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WizardPanel.P
endif

$(OBJ_DIR)/WizardPanel.o : $(abspath WizardPanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WizardSubPanel.P
endif

$(OBJ_DIR)/WizardSubPanel.o : $(abspath WizardSubPanel.cpp) $(PWD)/vgui_controls_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)
