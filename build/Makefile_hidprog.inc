
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
$(error ARCH is not set.  Pass -DARCH=x86_64 or ARCH=arm64 to the make command.)
endif
TARGET = $(PROG)
SDK = /Library/Developer/CommandLineTools/SDKs/MacOSX11.sdk
MIN_OS = -mmacosx-version-min=10.15
CC = gcc
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS) -std=c99 -isysroot $(SDK) $(MIN_OS) -arch $(ARCH)
LIBS = $(MIN_OS) -arch $(ARCH) -Wl,-syslibroot,$(SDK) -framework IOKit -framework CoreFoundation
else ifeq ($(OS), WINDOWS)
TARGET = $(PROG).exe
CC = i586-mingw32msvc-gcc
STRIP = i586-mingw32msvc-strip
CFLAGS = -Wall -O2 -DOS_$(OS) -std=c99
LIBS = -lhid -lsetupapi
endif

OBJS += ../common/hid_$(OS).o

include ../build/Makefile_rules.inc


