bin_PROGRAMS=luckyMe
luckyMe_SOURCES=luckyme.c
EXTRA_DIST=luckyme.h

luckyMe_CFLAGS =-std=gnu99

luckyMe_LDFLAGS =-lhaggle -lxml2 -L/usr/local/haggle/lib
luckyMe_CPPFLAGS = -I/usr/local/haggle/include/ -I/usr/local/haggle/include/libhaggle -I/usr/local/haggle/include/utils

all-local:

clean-local:
	rm -f *~
