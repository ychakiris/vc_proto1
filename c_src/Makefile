# Based on c_src.mk from erlang.mk by Loic Hoguin <essen@ninenines.eu>

VC_PROJ_DIR             := /home/ychakiris/vc_projects
VC_PROJ_INCLUDE_DIR     := $(VC_PROJ_DIR)/include
VC_PROJ_LIB_DIR         := $(VC_PROJ_DIR)/lib

FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil                          \

FFMPEG_BUILD_DIR := $(VC_PROJ_DIR)/ffmpeg_vc_build
FFMPEG_SRC_DIR   := $(VC_PROJ_DIR)/ffmpeg-3.3

FFMPEG_OTHER_OBJECTS  := $(FFMPEG_BUILD_DIR)/cmdutils.o

FFMPEG_OTHER_INCLUDES += -I $(FFMPEG_BUILD_DIR)
FFMPEG_OTHER_INCLUDES += -I $(FFMPEG_SRC_DIR)
FFMPEG_OTHER_INCLUDES += -I $(FFMPEG_SRC_DIR)/compat

CURDIR := $(shell pwd)
BASEDIR := $(abspath $(CURDIR)/..)


PKG_CONFIG_DIR := $(VC_PROJ_DIR)/lib/pkgconfig

PROJECT ?= $(notdir $(BASEDIR))
PROJECT := $(strip $(PROJECT))

ERTS_INCLUDE_DIR ?= $(shell erl -noshell -s init stop -eval "io:format(\"~s/erts-~s/include/\", [code:root_dir(), erlang:system_info(version)]).")
ERL_INTERFACE_INCLUDE_DIR ?= $(shell erl -noshell -s init stop -eval "io:format(\"~s\", [code:lib_dir(erl_interface, include)]).")
ERL_INTERFACE_LIB_DIR ?= $(shell erl -noshell -s init stop -eval "io:format(\"~s\", [code:lib_dir(erl_interface, lib)]).")

C_SRC_DIR = $(CURDIR)
C_SRC_OUTPUT ?= $(CURDIR)/../priv/$(PROJECT)

# System type and C compiler/flags.

UNAME_SYS := $(shell uname -s)
ifeq ($(UNAME_SYS), Darwin)
	CC ?= cc
	CFLAGS ?= -O3 -std=c99 -arch x86_64 -finline-functions -Wall -Wmissing-prototypes
	CXXFLAGS ?= -O3 -arch x86_64 -finline-functions -Wall
	LDFLAGS ?= -arch x86_64 -flat_namespace -undefined suppress
else ifeq ($(UNAME_SYS), FreeBSD)
	CC ?= cc
	CFLAGS ?= -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes
	CXXFLAGS ?= -O3 -finline-functions -Wall
else ifeq ($(UNAME_SYS), Linux)
	CC ?= gcc
	CFLAGS ?= -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes
	CXXFLAGS ?= -O3 -finline-functions -Wall
endif

CFLAGS += -fPIC -I $(ERTS_INCLUDE_DIR) -I $(ERL_INTERFACE_INCLUDE_DIR)
CFLAGS += -I $(VC_PROJ_INCLUDE_DIR)
CFLAGS += $(FFMPEG_OTHER_INCLUDES)
CFLAGS += $(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_DIR); pkg-config --cflags $(FFMPEG_LIBS))
CFLAGS += $(shell freetype-config --cflags)
CFLAGS += $(shell sdl2-config --cflags) 



# CXXFLAGS += -fPIC -I $(ERTS_INCLUDE_DIR) -I $(ERL_INTERFACE_INCLUDE_DIR)

LDLIBS += -L $(VC_PROJ_LIB_DIR)
LDLIBS += $(shell export PKG_CONFIG_PATH=$(PKG_CONFIG_DIR); pkg-config --libs $(FFMPEG_LIBS))
LDLIBS += $(shell freetype-config --libs)
LDLIBS += $(shell sdl2-config --libs)
LDLIBS += -L $(ERL_INTERFACE_LIB_DIR) -lerl_interface -lei

## LDFLAGS += -shared

# Verbosity.

c_verbose_0 = @echo " C     " $(?F);
c_verbose = $(c_verbose_$(V))

cpp_verbose_0 = @echo " CPP   " $(?F);
cpp_verbose = $(cpp_verbose_$(V))

link_verbose_0 = @echo " LD    " $(@F);
link_verbose = $(link_verbose_$(V))

SOURCES := $(shell find $(C_SRC_DIR) -type f \( -name "*.c" -o -name "*.C" -o -name "*.cc" -o -name "*.cpp" \))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))
EXOBJECTS = $(FFMPEG_OTHER_OBJECTS)

COMPILE_C = $(c_verbose) $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE_CPP = $(cpp_verbose) $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

$(C_SRC_OUTPUT): $(OBJECTS)
	@mkdir -p $(BASEDIR)/priv/
	$(link_verbose) $(CC) $(OBJECTS) $(EXOBJECTS) $(LDFLAGS) $(LDLIBS) -o $(C_SRC_OUTPUT)

%.o: %.c
	$(COMPILE_C) $(OUTPUT_OPTION) $<

%.o: %.cc
	$(COMPILE_CPP) $(OUTPUT_OPTION) $<

%.o: %.C
	$(COMPILE_CPP) $(OUTPUT_OPTION) $<

%.o: %.cpp
	$(COMPILE_CPP) $(OUTPUT_OPTION) $<

clean:
	@rm -f $(C_SRC_OUTPUT) $(OBJECTS)
