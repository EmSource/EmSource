ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=panel_zoo
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
GCC_ExtraLinkerFlags=-Wl,--no-as-needed -Wl,--as-needed
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
DEFINES += -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DEXENAME=panel_zoo -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/utils/vgui_panel_zoo -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
else
DEFINES += -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DEXENAME=panel_zoo -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/utils/vgui_panel_zoo -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
endif
INCLUDEDIRS += ../../common ../../public ../../public/tier0 ../../public/tier1 ../../thirdparty/SDL2 ../../vgui2/vlocalize ../../vgui2/controls ../../vgui2/include ../../vgui2/controls 
CONFTYPE=exe
GAMEOUTPUTFILE=
TARGETCOPIES=
OUTPUTFILE=../../../game/panel_zoo


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../../public/tier0/memoverride.cpp \
    ../../public/vgui_controls/vgui_controls.cpp \
    AnimatingImagePanelDemo.cpp \
    ButtonDemo.cpp \
    ButtonDemo2.cpp \
    CascadingMenu.cpp \
    CControlCatalog.cpp \
    CheckButtonDemo.cpp \
    ComboBox2.cpp \
    ComboBoxDemo.cpp \
    DefaultColors.cpp \
    DemoPage.cpp \
    EditablePanel2Demo.cpp \
    EditablePanelDemo.cpp \
    FileOpenDialogDemo.cpp \
    FrameDemo.cpp \
    HTMLDemo.cpp \
    HTMLDemo2.cpp \
    ImageDemo.cpp \
    ImagePanelDemo.cpp \
    Label2Demo.cpp \
    LabelDemo.cpp \
    ListPanelDemo.cpp \
    MenuBarDemo.cpp \
    MenuDemo.cpp \
    MenuDemo2.cpp \
    MessageBoxDemo.cpp \
    ProgressBarDemo.cpp \
    QueryBoxDemo.cpp \
    RadioButtonDemo.cpp \
    SampleButtons.cpp \
    SampleCheckButtons.cpp \
    SampleDropDowns.cpp \
    SampleEditFields.cpp \
    SampleListCategories.cpp \
    SampleListPanelBoth.cpp \
    SampleListPanelColumns.cpp \
    SampleMenus.cpp \
    SampleRadioButtons.cpp \
    SampleSliders.cpp \
    SampleTabs.cpp \
    ScrollBar2Demo.cpp \
    ScrollBarDemo.cpp \
    testfile.cpp \
    TextEntryDemo.cpp \
    TextEntryDemo2.cpp \
    TextEntryDemo3.cpp \
    TextEntryDemo4.cpp \
    TextEntryDemo5.cpp \
    TextImageDemo.cpp \
    ToggleButtonDemo.cpp \
    TooltipDemo.cpp \
    WizardPanelDemo.cpp \


LIBFILES = \
    ../../lib/public/linux32/appframework.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \
    ../../lib/public/linux32/vgui_controls.a \
    ../../lib/public/linux32/mathlib.a \


LIBFILENAMES = \
    ../../lib/public/linux32/appframework.a \
    ../../lib/public/linux32/mathlib.a \
    ../../lib/public/linux32/tier2.a \
    ../../lib/public/linux32/tier3.a \
    ../../lib/public/linux32/vgui_controls.a \



OTHER_DEPENDENCIES = \


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/memoverride.P
endif

$(OBJ_DIR)/memoverride.o : $(abspath ../../public/tier0/memoverride.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/vgui_controls.P
endif

$(OBJ_DIR)/vgui_controls.o : $(abspath ../../public/vgui_controls/vgui_controls.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/AnimatingImagePanelDemo.P
endif

$(OBJ_DIR)/AnimatingImagePanelDemo.o : $(abspath AnimatingImagePanelDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ButtonDemo.P
endif

$(OBJ_DIR)/ButtonDemo.o : $(abspath ButtonDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ButtonDemo2.P
endif

$(OBJ_DIR)/ButtonDemo2.o : $(abspath ButtonDemo2.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CascadingMenu.P
endif

$(OBJ_DIR)/CascadingMenu.o : $(abspath CascadingMenu.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CControlCatalog.P
endif

$(OBJ_DIR)/CControlCatalog.o : $(abspath CControlCatalog.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/CheckButtonDemo.P
endif

$(OBJ_DIR)/CheckButtonDemo.o : $(abspath CheckButtonDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ComboBox2.P
endif

$(OBJ_DIR)/ComboBox2.o : $(abspath ComboBox2.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ComboBoxDemo.P
endif

$(OBJ_DIR)/ComboBoxDemo.o : $(abspath ComboBoxDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DefaultColors.P
endif

$(OBJ_DIR)/DefaultColors.o : $(abspath DefaultColors.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/DemoPage.P
endif

$(OBJ_DIR)/DemoPage.o : $(abspath DemoPage.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EditablePanel2Demo.P
endif

$(OBJ_DIR)/EditablePanel2Demo.o : $(abspath EditablePanel2Demo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/EditablePanelDemo.P
endif

$(OBJ_DIR)/EditablePanelDemo.o : $(abspath EditablePanelDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FileOpenDialogDemo.P
endif

$(OBJ_DIR)/FileOpenDialogDemo.o : $(abspath FileOpenDialogDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/FrameDemo.P
endif

$(OBJ_DIR)/FrameDemo.o : $(abspath FrameDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HTMLDemo.P
endif

$(OBJ_DIR)/HTMLDemo.o : $(abspath HTMLDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/HTMLDemo2.P
endif

$(OBJ_DIR)/HTMLDemo2.o : $(abspath HTMLDemo2.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ImageDemo.P
endif

$(OBJ_DIR)/ImageDemo.o : $(abspath ImageDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ImagePanelDemo.P
endif

$(OBJ_DIR)/ImagePanelDemo.o : $(abspath ImagePanelDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/Label2Demo.P
endif

$(OBJ_DIR)/Label2Demo.o : $(abspath Label2Demo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/LabelDemo.P
endif

$(OBJ_DIR)/LabelDemo.o : $(abspath LabelDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ListPanelDemo.P
endif

$(OBJ_DIR)/ListPanelDemo.o : $(abspath ListPanelDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MenuBarDemo.P
endif

$(OBJ_DIR)/MenuBarDemo.o : $(abspath MenuBarDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MenuDemo.P
endif

$(OBJ_DIR)/MenuDemo.o : $(abspath MenuDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MenuDemo2.P
endif

$(OBJ_DIR)/MenuDemo2.o : $(abspath MenuDemo2.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/MessageBoxDemo.P
endif

$(OBJ_DIR)/MessageBoxDemo.o : $(abspath MessageBoxDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ProgressBarDemo.P
endif

$(OBJ_DIR)/ProgressBarDemo.o : $(abspath ProgressBarDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/QueryBoxDemo.P
endif

$(OBJ_DIR)/QueryBoxDemo.o : $(abspath QueryBoxDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/RadioButtonDemo.P
endif

$(OBJ_DIR)/RadioButtonDemo.o : $(abspath RadioButtonDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleButtons.P
endif

$(OBJ_DIR)/SampleButtons.o : $(abspath SampleButtons.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleCheckButtons.P
endif

$(OBJ_DIR)/SampleCheckButtons.o : $(abspath SampleCheckButtons.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleDropDowns.P
endif

$(OBJ_DIR)/SampleDropDowns.o : $(abspath SampleDropDowns.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleEditFields.P
endif

$(OBJ_DIR)/SampleEditFields.o : $(abspath SampleEditFields.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleListCategories.P
endif

$(OBJ_DIR)/SampleListCategories.o : $(abspath SampleListCategories.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleListPanelBoth.P
endif

$(OBJ_DIR)/SampleListPanelBoth.o : $(abspath SampleListPanelBoth.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleListPanelColumns.P
endif

$(OBJ_DIR)/SampleListPanelColumns.o : $(abspath SampleListPanelColumns.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleMenus.P
endif

$(OBJ_DIR)/SampleMenus.o : $(abspath SampleMenus.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleRadioButtons.P
endif

$(OBJ_DIR)/SampleRadioButtons.o : $(abspath SampleRadioButtons.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleSliders.P
endif

$(OBJ_DIR)/SampleSliders.o : $(abspath SampleSliders.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/SampleTabs.P
endif

$(OBJ_DIR)/SampleTabs.o : $(abspath SampleTabs.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScrollBar2Demo.P
endif

$(OBJ_DIR)/ScrollBar2Demo.o : $(abspath ScrollBar2Demo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ScrollBarDemo.P
endif

$(OBJ_DIR)/ScrollBarDemo.o : $(abspath ScrollBarDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/testfile.P
endif

$(OBJ_DIR)/testfile.o : $(abspath testfile.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextEntryDemo.P
endif

$(OBJ_DIR)/TextEntryDemo.o : $(abspath TextEntryDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextEntryDemo2.P
endif

$(OBJ_DIR)/TextEntryDemo2.o : $(abspath TextEntryDemo2.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextEntryDemo3.P
endif

$(OBJ_DIR)/TextEntryDemo3.o : $(abspath TextEntryDemo3.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextEntryDemo4.P
endif

$(OBJ_DIR)/TextEntryDemo4.o : $(abspath TextEntryDemo4.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextEntryDemo5.P
endif

$(OBJ_DIR)/TextEntryDemo5.o : $(abspath TextEntryDemo5.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TextImageDemo.P
endif

$(OBJ_DIR)/TextImageDemo.o : $(abspath TextImageDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/ToggleButtonDemo.P
endif

$(OBJ_DIR)/ToggleButtonDemo.o : $(abspath ToggleButtonDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/TooltipDemo.P
endif

$(OBJ_DIR)/TooltipDemo.o : $(abspath TooltipDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/WizardPanelDemo.P
endif

$(OBJ_DIR)/WizardPanelDemo.o : $(abspath WizardPanelDemo.cpp) $(PWD)/panel_zoo_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)
