
.PHONY: all clean

# Define required raylib variables
PROJECT_NAME       ?= draw
RAYLIB_VERSION     ?= 3.0.0
RAYLIB_API_VERSION ?= 3
RAYLIB_PATH        ?= C:\raylib\raylib

# Define default options

# One of PLATFORM_DESKTOP, PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM           ?= PLATFORM_WEB


DESTDIR ?= ../..

RAYLIB_INSTALL_PATH ?= C:\raylib\raylib\src
# RAYLIB_H_INSTALL_PATH locates the installed raylib header and associated source files.
RAYLIB_H_INSTALL_PATH ?= C:\raylib\raylib\src

# Library type used for raylib: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE        ?= STATIC

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= RELEASE


USE_EXTERNAL_GLFW     ?= FALSE


USE_WAYLAND_DISPLAY   ?= FALSE

EMSDK_PATH         ?= C:/emsdk
EMSCRIPTEN_PATH    ?= $(EMSDK_PATH)/upstream/emscripten
CLANG_PATH          = $(EMSDK_PATH)/upstream/bin
PYTHON_PATH         = $(EMSDK_PATH)/python/3.7.4-pywin32_64bit
NODE_PATH           = $(EMSDK_PATH)/node/12.18.1_64bit/bin
export PATH         = $(EMSDK_PATH);$(EMSCRIPTEN_PATH);$(CLANG_PATH);$(NODE_PATH);$(PYTHON_PATH);C:\raylib\MinGW\bin:$$(PATH)


# Define raylib release directory for compiled library.
# RAYLIB_RELEASE_PATH points to provided binaries or your freshly built version
RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src

EXAMPLE_RUNTIME_PATH   ?= $(RAYLIB_RELEASE_PATH)

CC = emcc

MAKE = mingw32-make

CFLAGS += -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g
    ifeq ($(PLATFORM),PLATFORM_WEB)
        CFLAGS += -s ASSERTIONS=1 --profiling
    endif
else
    ifeq ($(PLATFORM),PLATFORM_WEB)
        CFLAGS += -Os
    else
        CFLAGS += -s -O1
    endif
endif


ifeq ($(PLATFORM),PLATFORM_WEB)
   
    CFLAGS += -s USE_GLFW=3 -s TOTAL_MEMORY=16777216 -s WASM=1 -s ASYNCIFY --preload-file ../../Resources

    # Define a custom shell .html and output extension
    CFLAGS += --shell-file $(RAYLIB_PATH)/src/shell.html
    EXT = .html
endif

# Define include paths for required headers
# NOTE: Several external required libraries (stb and others)
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external

# Define library paths containing required libs.
LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src

ifeq ($(PLATFORM),PLATFORM_WEB)
    # Libraries for web (HTML5) compiling
    LDLIBS = $(RAYLIB_RELEASE_PATH)/libraylib.bc
endif

# Define all source files required
PROJECT_SOURCE_FILES ?= C:\raylib\draw_game\main.c

# Define all object files from source files
OBJS = $(patsubst %.c, %.o, $(PROJECT_SOURCE_FILES))

# For Android platform we call a custom Makefile.Android
ifeq ($(PLATFORM),PLATFORM_ANDROID)
    MAKEFILE_PARAMS = -f Makefile.Android 
    export PROJECT_NAME
    export PROJECT_SOURCE_FILES
else
    MAKEFILE_PARAMS = $(PROJECT_NAME)
endif

# Default target entry
# NOTE: We call this Makefile target or Makefile.Android target
all:
	$(MAKE) $(MAKEFILE_PARAMS)

# Project target defined by PROJECT_NAME
$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile source files
# NOTE: This pattern will compile every module defined on $(OBJS)
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

