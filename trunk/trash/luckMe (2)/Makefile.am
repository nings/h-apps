bin_PROGRAMS=testx1
testx1_SOURCES=testx1.c
EXTRA_DIST=testx1.h

testx1_CFLAGS =-std=gnu99

testx1_LDFLAGS =-lhaggle -lxml2 -L/usr/local/haggle/lib
testx1_CPPFLAGS = -I/usr/local/haggle/include/ -I/usr/local/haggle/include/libhaggle -I/usr/local/haggle/include/utils

all-local:

clean-local:
	rm -f *~
