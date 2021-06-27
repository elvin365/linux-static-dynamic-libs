CC=gcc
LD=ld
CFLAGS=-c -Wall
LDFLAGS=
SOURCES = png.c pngerror.c pngget.c pngmem.c pngpread.c pngrio.c pngrtran.c pngrutil.c pngset.c pngtrans.c pngwio.c pngwrite.c pngwtran.c pngwutil.c
DYNFLAGS=-c -shared -fPIC -ldl
INCLUDE = ../zlib

all: clean static dynamic blob

dynamic:
	gcc -c -Wall -fpic $(SOURCES) -I. zlib.h zconf.h
	gcc -shared -o "libpng.so" *.o -ldl


blob:static2

static: 
	gcc -c $(SOURCES) -I. zlib.h
	ar rc libstpng.a *.o
	ranlib libstpng.a



static2:
	gcc  -c -shared -ldl -fPIC $(SOURCES) -I. zlib.h zconf.h
	ar rc libstpng.a *.o
	ranlib libstpng.a






clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
