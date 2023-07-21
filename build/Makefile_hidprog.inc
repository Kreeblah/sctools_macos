
#OS = LINUX
#OS = MACOSX
#OS = WINDOWS

# To set up Ubuntu Linux to cross compile for Windows:
#
#    apt-get install mingw32 mingw32-binutils mingw32-runtime
#
# Just edit the variable above for WINDOWS, then use "make" to build rawhid.exe

ifeq ($(OS), LINUX)
TARGET = $(PROG)
CC = gcc
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS) -std=c99
LIBS = -lusb
else ifeq ($(OS), MACOSX)
ifndef ARCH
$(error ARCH is not set.  Pass ARCH=x86_64 or ARCH=arm64 to the make command.)
exit 1
endif
TARGET = $(PROG)
CC = clang
STRIP = strip
ifdef MACOS_SDK
MACOS_SDK_PATH = $(MACOS_SDK)
else
MACOS_SDK_PATH = /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk
endif
ifdef MIN_MACOS_VER
MIN_MACOS_OPTION = -mmacosx-version-min=$(MIN_MACOS_VER)
endif
CFLAGS = -Wall -O2 -DOS_$(OS) -std=c99 -isysroot $(MACOS_SDK_PATH) $(MIN_MACOS_OPTION) -arch $(ARCH)
LIBS = $(MIN_MACOS_OPTION) -arch $(ARCH) -Wl,-syslibroot,$(MACOS_SDK_PATH) -framework IOKit -framework CoreFoundation
else ifeq ($(OS), WINDOWS)
TARGET = $(PROG).exe
CC = i586-mingw32msvc-gcc
STRIP = i586-mingw32msvc-strip
CFLAGS = -Wall -O2 -DOS_$(OS) -std=c99
LIBS = -lhid -lsetupapi
endif

OBJS += ../common/hid_$(OS).o

include ../build/Makefile_rules.inc
