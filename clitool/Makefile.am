bin_PROGRAMS=clitool
clitool_SOURCES=clitool.cpp

clitool_CFLAGS =-std=gnu99

clitool_LDFLAGS =-lhaggle -lxml2 -L/usr/local/haggle/lib -lhaggleutils
clitool_CPPFLAGS = -I/usr/local/haggle/include/ -I/usr/local/haggle/include/libhaggle -I/usr/local/haggle/include/utils

EXTRA_DIST=Android.mk

all-local:

clean-local:
	rm -f *~
