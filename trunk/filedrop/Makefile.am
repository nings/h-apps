bin_PROGRAMS = filedrop
filedrop_SOURCES = filedrop.c

filedrop_LDFLAGS =-lhaggle -lxml2 -L/usr/local/haggle/lib
filedrop_CPPFLAGS = -I/usr/local/haggle/include/ -I/usr/local/haggle/include/libhaggle -I/usr/local/haggle/include/utils

EXTRA_DIST = filedrop.c

all-local:

clean-local:
	rm -f *~
