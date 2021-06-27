CC=gcc
LD=ld
CFLAGS=-c -Wall
LDFLAGS=
SOURCES = adler32.c compress.c crc32.c deflate.c gzclose.c gzlib.c gzread.c gzwrite.c infback.c inffast.c inflate.c inftrees.c trees.c uncompr.c zutil.c
DYNFLAGS=-c -shared -fPIC -ldl

all: clean static dynamic blob

dynamic: 
	gcc -c -Wall -fpic $(SOURCES)
	gcc -shared -o "libz.so" *.o -ldl


blob: static2

static:
	gcc -c $(SOURCES)
	ar rc libzlib.a *.o
	ranlib libzlib.a



static2:
	gcc -c -shared -ldl -fPIC $(SOURCES)
	ar rc libzlib.a *.o
	ranlib libzlib.a







clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so
