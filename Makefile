#o Makefile for building the port binary
#
# Makefile targets:
#
# all/install   build and install
# clean         clean build products and intermediates
#
# Variables to override:
#
# MIX_APP_PATH  path to the build directory
#
# CC            C compiler
# CROSSCOMPILE	crosscompiler prefix, if any
# CFLAGS	compiler flags for compiling all C files
# LDFLAGS	linker flags for linking all binaries

PREFIX = $(MIX_APP_PATH)/priv
BUILD  = $(MIX_APP_PATH)/obj

ERL_CFLAGS ?= -I$(ERL_EI_INCLUDE_DIR)
ERL_LDFLAGS ?= -L$(ERL_EI_LIBDIR) -lei


LDFLAGS += -lm -lpthread

CFLAGS ?= -O2 -Wall -Wextra -Wno-unused-parameter

# Enable for debug messages
CFLAGS += -DDEBUG

CFLAGS += $(shell pkg-config --cflags cairo)
LDFLAGS += $(shell pkg-config --libs cairo)

OBJECTS += $(BUILD)/main.o \
			 $(BUILD)/erlcmd.o \
			 $(BUILD)/transport.o \
			 $(BUILD)/eio.o \
			 $(BUILD)/router.o \
			 $(BUILD)/strres.o \
			 $(BUILD)/resmgr.o \
			 $(BUILD)/api/surface.o \
			 $(BUILD)/api/path.o \
			 $(BUILD)/api/transformations.o \
			 $(BUILD)/api/context.o


HEADERS = $(wildcard src/*.h)
BIN = $(PREFIX)/cairo_ex

BUILD_DIRS = $(BUILD) $(BUILD)/api

calling_from_make:
	mix compile

all: $(PREFIX) $(BUILD_DIRS) $(BIN)

$(BUILD)/%.o: src/%.c
	$(CC) -c $(ERL_CFLAGS) $(CFLAGS) -o $@ $<

$(BIN): $(OBJECTS)
	$(CC) -o $@ $^ $(ERL_LDFLAGS) $(LDFLAGS)

$(PREFIX) $(BUILD_DIRS):
	mkdir -p $@

clean:
	$(RM) $(BIN) $(OBJECTS)

format:
	astyle \
		--style=kr \
		--indent=spaces=4 \
		--align-pointer=name \
		--align-reference=name \
		--convert-tabs \
		--attach-namespaces \
		--max-code-length=100 \
		--max-instatement-indent=120 \
		--pad-header \
		--pad-oper \
		$(SRC)

.PHONY: all clean calling_from_make install format
