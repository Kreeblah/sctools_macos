
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
CC = g++
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS)
CXXFLAGS = $(CFLAGS)
LIBS = 
else ifeq ($(OS), MACOSX)
TARGET = $(PROG)
SDK = /usr/local/SDKs/MacOSX.platform/MacOSX10.15.sdk
ARCH = -mmacosx-version-min=10.15 -arch x86_64
CC = g++
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS) -isysroot $(SDK) $(ARCH)
CXXFLAGS = $(CFLAGS)
LIBS = $(ARCH) -Wl,-syslibroot,$(SDK) -framework IOKit -framework CoreFoundation
else ifeq ($(OS), WINDOWS)
TARGET = $(PROG).exe
CC = i586-mingw32msvc-g++
CXX = i586-mingw32msvc-g++
STRIP = i586-mingw32msvc-strip
CFLAGS = -Wall -O2 -DOS_$(OS) -mwin32 -mconsole
CXXFLAGS = $(CFLAGS)
#LIBS = -lsetupapi
#LIBS = -lsetupapi -lstdc++ -lgcc -lmsvcrt
LIBS = 
endif

#OBJS = $(OBJS)

include ../build/Makefile_rules.inc


