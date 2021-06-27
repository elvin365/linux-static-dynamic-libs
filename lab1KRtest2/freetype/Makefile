CC=gcc
LD=ld
CFLAGS=-c -Wall
LDFLAGS=
SOURCES = \
        autofit.c \
        bdf.c \
        cff.c \
        pfr.c \
        pcf.c \
        sfnt.c \
        raster.c \
        pshinter.c \
        winfnt.c \
        truetype.c \
        type1.c \
        type42.c \
        psaux.c \
        psnames.c \
        type1cid.c \
        ftbase.c \
        ftbitmap.c \
        ftcache.c \
        ftdebug.c \
        ftgasp.c \
        ftglyph.c \
        ftgzip.c \
        ftinit.c \
        ftlzw.c \
        ftstroke.c \
        ftsystem.c \
        smooth.c \

DYNFLAGS=-c -shared -fPIC -ldl

all: clean static dynamic blob

dynamic:
	gcc -c -Wall -fpic $(SOURCES) -I. ft2build.h
	gcc -shared -o "libfreetype.so" *.o -ldl -I. ft2build.h


blob: static2

static:
	gcc -c $(SOURCES) -I. ft2build.h
	ar rc libfreetype.a *.o
	ranlib libfreetype.a

static2:
	gcc -c -shared -ldl -fPIC $(SOURCES) -I. ft2build.h 
	ar rc libfreetype.a *.o
	ranlib libfreetype.a



clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so








