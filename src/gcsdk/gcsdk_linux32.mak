ifneq "$(LINUX_TOOLS_PATH)" ""
TOOL_PATH = $(LINUX_TOOLS_PATH)/
endif

NAME=gcsdk
SRCROOT=..
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
DLL_EXT=.so
SYM_EXT=.dbg
FORCEINCLUDES= 
ifeq "$(CFG)" "debug"
DEFINES += -DVPC -DDEBUG -D_DEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DTF -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/gcsdk -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
else
DEFINES += -DVPC -DNDEBUG -DGNUC -DPOSIX -DCOMPILER_GCC -D_DLL_EXT=.so -D_LINUX -DLINUX -DPOSIX -D_POSIX -DBINK_VIDEO -DGL_GLEXT_PROTOTYPES -DDX_TO_GL_ABSTRACTION -DUSE_SDL -DDEV_BUILD -DFRAME_POINTER_OMISSION_DISABLED -DTF -D_EXTERNAL_DLL_EXT=.wasm -D_EMSCRIPTEN=1 -DVPCGAMECAPS=HL2 -DEMSCRIPTEN=1 -DPROJECTDIR=/home/guest/Downloads/src/src/gcsdk -D_DLL_EXT=.so -DSOURCE1=1 -DVPCGAME=hl2 -D_POSIX=1 -DPOSIX=1 
endif
INCLUDEDIRS += ../common ../public ../public/tier0 ../public/tier1 ../thirdparty/SDL2 ../gcsdk/generated_proto ../thirdparty/protobuf-2.6.1/src ../gcsdk/steamextra .. ../public ../public/gcsdk ../thirdparty/JSON_parser . 
CONFTYPE=lib
GAMEOUTPUTFILE=../lib/public/linux32/gcsdk.a
TARGETCOPIES=
OUTPUTFILE=gcsdk.a


POSTBUILDCOMMAND=/bin/true



CPPFILES= \
    ../gcsdk/generated_proto/gcsdk_gcmessages.pb.cc \
    ../gcsdk/generated_proto/gcsystemmsgs.pb.cc \
    ../gcsdk/generated_proto/steammessages.pb.cc \
    ../thirdparty/JSON_parser/JSON_parser.c \
    gcclient.cpp \
    gcclient_sharedobjectcache.cpp \
    gcconstants.cpp \
    gclogger.cpp \
    gcmsg.cpp \
    job.cpp \
    jobmgr.cpp \
    jobtime.cpp \
    messagelist.cpp \
    msgprotobuf.cpp \
    netpacket.cpp \
    netpacketpool.cpp \
    protobufsharedobject.cpp \
    sharedobject.cpp \
    sharedobjectcache.cpp \
    stdafx.cpp \
    steamextra/misc.cpp \
    steamextra/rtime.cpp \
    steamextra/steamid.cpp \
    steamextra/tier1/hashglobals.cpp \
    steamextra/tier1/tsmempool.cpp \
    steamextra/tier1/tsmultimempool.cpp \
    webapi_response.cpp \
    workthreadpool.cpp \


LIBFILES = \


LIBFILENAMES = \



OTHER_DEPENDENCIES = \
	$(abspath ../gcsdk/generated_proto/gcsdk_gcmessages.pb.cc) \
	$(abspath ../gcsdk/generated_proto/gcsdk_gcmessages.pb.h) \
	$(abspath ../gcsdk/generated_proto/steammessages.pb.cc) \
	$(abspath ../gcsdk/generated_proto/steammessages.pb.h) \
	$(abspath ../gcsdk/generated_proto/gcsystemmsgs.pb.cc) \
	$(abspath ../gcsdk/generated_proto/gcsystemmsgs.pb.h)


-include $(OBJ_DIR)/_other_deps.P


# Include the base makefile now.
include $(SRCROOT)/devtools/makefile_base_posix.mak



$(OBJ_DIR)/_custombuildstep_0.touchfile : $(abspath ../gcsdk/gcsdk_gcmessages.proto) gcsdk_linux32.mak $(abspath ../gcsdk/gcsdk_gcmessages.proto)
	 @echo "Running Protocol Buffer Compiler on gcsdk_gcmessages.proto...";mkdir -p $(OBJ_DIR) 2> /dev/null;
	 mkdir ../gcsdk/generated_proto 2> /dev/null;../thirdparty/protobuf-2.6.1/bin/linux32/protoc --proto_path=../thirdparty/protobuf-2.6.1/src --proto_path=../gcsdk/ --proto_path=../gcsdk --proto_path=../game/shared  --cpp_out=../gcsdk/generated_proto ../gcsdk/gcsdk_gcmessages.proto
	 @touch $(OBJ_DIR)/_custombuildstep_0.touchfile

$(abspath ../gcsdk/generated_proto/gcsdk_gcmessages.pb.cc) : $(OBJ_DIR)/_custombuildstep_0.touchfile gcsdk_linux32.mak
	 @touch ../gcsdk/generated_proto/gcsdk_gcmessages.pb.cc

$(abspath ../gcsdk/generated_proto/gcsdk_gcmessages.pb.h) : $(OBJ_DIR)/_custombuildstep_0.touchfile gcsdk_linux32.mak
	 @touch ../gcsdk/generated_proto/gcsdk_gcmessages.pb.h


ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gcsdk_gcmessages.pb.P
endif

$(OBJ_DIR)/gcsdk_gcmessages.pb.o : $(abspath ../gcsdk/generated_proto/gcsdk_gcmessages.pb.cc) $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gcsystemmsgs.pb.P
endif

$(OBJ_DIR)/gcsystemmsgs.pb.o : $(abspath ../gcsdk/generated_proto/gcsystemmsgs.pb.cc) $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steammessages.pb.P
endif

$(OBJ_DIR)/steammessages.pb.o : $(abspath ../gcsdk/generated_proto/steammessages.pb.cc) $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

$(OBJ_DIR)/_custombuildstep_1.touchfile : $(abspath ../gcsdk/steammessages.proto) gcsdk_linux32.mak $(abspath ../gcsdk/steammessages.proto)
	 @echo "Running Protocol Buffer Compiler on steammessages.proto...";mkdir -p $(OBJ_DIR) 2> /dev/null;
	 mkdir ../gcsdk/generated_proto 2> /dev/null;../thirdparty/protobuf-2.6.1/bin/linux32/protoc --proto_path=../thirdparty/protobuf-2.6.1/src --proto_path=../gcsdk/ --proto_path=../gcsdk --proto_path=../game/shared  --cpp_out=../gcsdk/generated_proto ../gcsdk/steammessages.proto
	 @touch $(OBJ_DIR)/_custombuildstep_1.touchfile

$(abspath ../gcsdk/generated_proto/steammessages.pb.cc) : $(OBJ_DIR)/_custombuildstep_1.touchfile gcsdk_linux32.mak
	 @touch ../gcsdk/generated_proto/steammessages.pb.cc

$(abspath ../gcsdk/generated_proto/steammessages.pb.h) : $(OBJ_DIR)/_custombuildstep_1.touchfile gcsdk_linux32.mak
	 @touch ../gcsdk/generated_proto/steammessages.pb.h


ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/JSON_parser.P
endif

$(OBJ_DIR)/JSON_parser.o : $(abspath ../thirdparty/JSON_parser/JSON_parser.c) $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gcclient.P
endif

$(OBJ_DIR)/gcclient.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/gcclient.o : $(abspath gcclient.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gcclient_sharedobjectcache.P
endif

$(OBJ_DIR)/gcclient_sharedobjectcache.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/gcclient_sharedobjectcache.o : $(abspath gcclient_sharedobjectcache.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gcconstants.P
endif

$(OBJ_DIR)/gcconstants.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/gcconstants.o : $(abspath gcconstants.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gclogger.P
endif

$(OBJ_DIR)/gclogger.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/gclogger.o : $(abspath gclogger.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/gcmsg.P
endif

$(OBJ_DIR)/gcmsg.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/gcmsg.o : $(abspath gcmsg.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/_custombuildstep_2.touchfile : $(abspath gcsystemmsgs.proto) gcsdk_linux32.mak $(abspath gcsystemmsgs.proto)
	 @echo "Running Protocol Buffer Compiler on csystemmsgs.proto...";mkdir -p $(OBJ_DIR) 2> /dev/null;
	 mkdir ../gcsdk/generated_proto 2> /dev/null;../thirdparty/protobuf-2.6.1/bin/linux32/protoc --proto_path=../thirdparty/protobuf-2.6.1/src --proto_path=. --proto_path=../gcsdk --proto_path=../game/shared  --cpp_out=../gcsdk/generated_proto gcsystemmsgs.proto
	 @touch $(OBJ_DIR)/_custombuildstep_2.touchfile

$(abspath ../gcsdk/generated_proto/gcsystemmsgs.pb.cc) : $(OBJ_DIR)/_custombuildstep_2.touchfile gcsdk_linux32.mak
	 @touch ../gcsdk/generated_proto/gcsystemmsgs.pb.cc

$(abspath ../gcsdk/generated_proto/gcsystemmsgs.pb.h) : $(OBJ_DIR)/_custombuildstep_2.touchfile gcsdk_linux32.mak
	 @touch ../gcsdk/generated_proto/gcsystemmsgs.pb.h


ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/job.P
endif

$(OBJ_DIR)/job.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/job.o : $(abspath job.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/jobmgr.P
endif

$(OBJ_DIR)/jobmgr.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/jobmgr.o : $(abspath jobmgr.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/jobtime.P
endif

$(OBJ_DIR)/jobtime.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/jobtime.o : $(abspath jobtime.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/messagelist.P
endif

$(OBJ_DIR)/messagelist.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/messagelist.o : $(abspath messagelist.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/msgprotobuf.P
endif

$(OBJ_DIR)/msgprotobuf.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/msgprotobuf.o : $(abspath msgprotobuf.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/netpacket.P
endif

$(OBJ_DIR)/netpacket.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/netpacket.o : $(abspath netpacket.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/netpacketpool.P
endif

$(OBJ_DIR)/netpacketpool.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/netpacketpool.o : $(abspath netpacketpool.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/protobufsharedobject.P
endif

$(OBJ_DIR)/protobufsharedobject.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/protobufsharedobject.o : $(abspath protobufsharedobject.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sharedobject.P
endif

$(OBJ_DIR)/sharedobject.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/sharedobject.o : $(abspath sharedobject.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/sharedobjectcache.P
endif

$(OBJ_DIR)/sharedobjectcache.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/sharedobjectcache.o : $(abspath sharedobjectcache.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/stdafx.P
endif

$(OBJ_DIR)/stdafx.h.gch : stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_PCH) $(POST_COMPILE_FILE)

$(OBJ_DIR)/stdafx.h.P : $(OBJ_DIR)/stdafx.h.gch

vpath stdafx.h . $(INCLUDEDIRS)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
include $(OBJ_DIR)/stdafx.h.P
endif

$(OBJ_DIR)/stdafx.h : stdafx.h $(OBJ_DIR)/stdafx.h.gch $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	cp -f $< $(OBJ_DIR)/stdafx.h

$(OBJ_DIR)/stdafx.o : $(abspath stdafx.cpp) $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/misc.P
endif

$(OBJ_DIR)/misc.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/misc.o : $(abspath steamextra/misc.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/rtime.P
endif

$(OBJ_DIR)/rtime.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/rtime.o : $(abspath steamextra/rtime.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/steamid.P
endif

$(OBJ_DIR)/steamid.o : $(abspath steamextra/steamid.cpp) $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak $(OTHER_DEPENDENCIES)
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/hashglobals.P
endif

$(OBJ_DIR)/hashglobals.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/hashglobals.o : $(abspath steamextra/tier1/hashglobals.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tsmempool.P
endif

$(OBJ_DIR)/tsmempool.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/tsmempool.o : $(abspath steamextra/tier1/tsmempool.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/tsmultimempool.P
endif

$(OBJ_DIR)/tsmultimempool.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/tsmultimempool.o : $(abspath steamextra/tier1/tsmultimempool.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/webapi_response.P
endif

$(OBJ_DIR)/webapi_response.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/webapi_response.o : $(abspath webapi_response.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)

ifneq (clean, $(findstring clean, $(MAKECMDGOALS)))
-include $(OBJ_DIR)/workthreadpool.P
endif

$(OBJ_DIR)/workthreadpool.o : TARGET_PCH_FILE = $(OBJ_DIR)/stdafx.h
$(OBJ_DIR)/workthreadpool.o : $(abspath workthreadpool.cpp) $(OBJ_DIR)/stdafx.h.gch $(OBJ_DIR)/stdafx.h $(PWD)/gcsdk_linux32.mak $(SRCROOT)/devtools/makefile_base_posix.mak
	$(PRE_COMPILE_FILE)
	$(COMPILE_FILE_WITH_PCH) $(POST_COMPILE_FILE)
