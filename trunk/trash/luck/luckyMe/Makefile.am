bin_PROGRAMS=mytest
mytest_SOURCES=luckyme.c
EXTRA_DIST=luckyme.h

mytest_CFLAGS =-std=gnu99

mytest_LDFLAGS =-lhaggle -lxml2 -L/usr/local/haggle/lib
mytest_CPPFLAGS = -I/usr/local/haggle/include/ -I/usr/local/haggle/include/libhaggle -I/usr/local/haggle/include/utils

all-local:

clean-local:
	rm -f *~
