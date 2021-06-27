CC=gcc
L1=freetype
L2=libpng
L3=zlib
STATIC=app/app-static.c
DYNAMIC=app/app-dynamic.c
STATIC_OUT=app-static
DYNAMIC_OUT=app-dynamic
PathZlibConf:=zlib
PathLibpng:=libpng
PathFreetype:=freetype
PathApp:=app



mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path)) 
#to know the folder

#./configure --prefix=/home/elvin/lab1/libpng-1.6.37 --enable-static

LIB:=lib 
empty:=
space:= $(empty) $(empty)
mkfile_dir:=$(subst $(space),$(empty),$(mkfile_dir))
mkfile_dir:=$(mkfile_dir)$(PathFreetype)




mkfile_path2 := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir2 := $(dir $(mkfile_path2)) 

mkfile_dir2:=$(subst $(space),$(empty),$(mkfile_dir2))
mkfile_dir2:=$(mkfile_dir2)$(PathLibpng)





mkfile_path3 := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir3 := $(dir $(mkfile_path3)) 

mkfile_dir3:=$(subst $(space),$(empty),$(mkfile_dir3))
mkfile_dir3:=$(mkfile_dir3)$(PathZlibConf)


mkfile_path4 := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir4 := $(dir $(mkfile_path4)) 

mkfile_dir4:=$(subst $(space),$(empty),$(mkfile_dir4))
mkfile_dir4:=$(mkfile_dir4)$(PathApp)




all: clean static dynamic blob
rebuild:
	@cd $(L1)/ && make all 
	@cd $(L2)/ && make all 
	@cd $(L3)/ && make all

static:
	cd freetype && $(MAKE) clean && $(MAKE) static
	cd libpng && $(MAKE) clean && $(MAKE) static
	cd zlib && $(MAKE) clean && $(MAKE) static
	@$(CC) $(STATIC) -L $(L1)/ -l $(L1) -L $(L2)/ -l stpng -L $(L3)/ -l zlib -lm -I ./$(L2)/ -I ./$(L1)/ -std=gnu99 -o $(STATIC_OUT)

dynamic:
	cd freetype && $(MAKE) clean && $(MAKE) dynamic
	cd libpng && $(MAKE) clean && $(MAKE) dynamic
	cd zlib && $(MAKE) clean && $(MAKE) dynamic
	gcc $(mkfile_dir4)/app-dynamic.c -L$(mkfile_dir) -lfreetype  -I$(mkfile_dir)       -L$(mkfile_dir2) -lpng  -I$(mkfile_dir2)    -L$(mkfile_dir3) -lz     -I$(mkfile_dir3)      -Wl,-rpath=$(mkfile_dir):$(mkfile_dir2):$(mkfile_dir3)  -Wall -ldl -o  app-dynamic 
#cd app && gcc app-dynamic.c -Wl,-rpath,/freetype,-rpath,/libpng,-rpath,/zlib -L../freetype -lfreetype -I ../freetype  -L../libpng -lpng -L../zlib/zlib.so  -I ../zlib/ -ldl -o ../app-dynamic

#@$(CC) -I ./$(L1)/ -I ./$(L2)/ -std=gnu99 -rdynamic $(DYNAMIC) -o $(DYNAMIC_OUT) -ldl
blob:
	cd freetype && $(MAKE) clean && $(MAKE) blob
	cd libpng && $(MAKE) clean && $(MAKE) blob
	cd zlib && $(MAKE) clean && $(MAKE) blob
	gcc -c -fPIC $(mkfile_dir4)/app-blob.c -I$(mkfile_dir) -I$(mkfile_dir2) -lm -o $(mkfile_dir4)/app-blob.o && ar -rsc $(mkfile_dir4)/libblob.a $(mkfile_dir4)/*.o && gcc -shared -fPIC -o blob.bin -Wl,--whole-archive $(mkfile_dir4)/libblob.a $(mkfile_dir)/libfreetype.a $(mkfile_dir2)/libstpng.a $(mkfile_dir3)/libzlib.a -Wl,--no-whole-archive -lm && gcc -Wall -g -o app-blob $(mkfile_dir4)/elf_loader.c $(mkfile_dir4)/main.c $(mkfile_dir4)/wheelc/list.c -ldl
#@cd app && gcc -c -fPIC app-blob.c -I ../freetype/ -I ../libpng/ -I ../zlib/ -lm && ar -rsc libblob.a *.o &&  gcc -shared -fPIC -o blob.bin -Wl,--whole-archive libblob.a ../freetype/libfreetype.a ../libpng/libstpng.a ../zlib/libzlib.a   -Wl,--no-whole-archive -lm && gcc -Wall -g -o app-blob elf_loader.c main.c wheelc/list.c -ldl && mv blob.bin ../ && mv app-blob ../
clean:
	cd freetype && $(MAKE) clean
	cd libpng && $(MAKE) clean
	cd zlib && $(MAKE) clean
#rm -f  app-blob
#rm -f app-static
#rm -f app-dynamic
#rm -f *.png
	rm -f *.so
	rm -f *.txt
	@cd app &&  rm -f *.o && rm -f *.a 


