bin_PROGRAMS = myapplication 
myapplication_SOURCES = myapplication.cpp databuffer.cpp

myapplication_LDFLAGS =-lhaggle -lxml2 -L/usr/local/haggle/lib
myapplication_CPPFLAGS = -I/usr/local/haggle/include/ -I/usr/local/haggle/include/libhaggle -I/usr/local/haggle/include/utils

EXTRA_DIST = myapplication.h databuffer.h

all-local:

clean-local:
	rm -f *~

