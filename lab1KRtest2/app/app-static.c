#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <malloc.h>
#include <math.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include<dirent.h>
#include <png.h>

#define WIDTH   1440
#define HEIGHT  720
unsigned char image[HEIGHT][WIDTH];
int maxx = 0;
int maxy = 0;

//////////////////////////////////////////////////
struct name_of_files
{
	char list_of_files[100][100];
	int rows;
};
const char* path;
struct name_of_files files;
int get_files_names(void)
{
    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(".");

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }


    int i=0;
    while ((de = readdir(dr)) != NULL)
	{
	   if( (!strcmp(de->d_name,"."))  )
	   {
		continue;
	   }
	   if( (!strcmp(de->d_name,"..")) )
	   {
		continue;
	   }
	   	sprintf(files.list_of_files[i++],"%s",de->d_name);
	}
	//printf("%d\n",i);
	files.rows=i;
    int j=0;
    //for(j=0;j<i;j++)
	 //printf("%s\n",files.list_of_files[j]);

    closedir(dr);
    return 0;
}


void draw_bitmap( FT_Bitmap*  bitmap, FT_Int x, FT_Int y)
{
  FT_Int  i, j, p, q;
  FT_Int  x_max = x + bitmap->width;
  FT_Int  y_max = y + bitmap->rows;
  for ( i = x, p = 0; i < x_max; i++, p++ )
  {
    for ( j = y, q = 0; j < y_max; j++, q++ )
    {
      if ( i < 0      || j < 0       ||
           i >= WIDTH || j >= HEIGHT )
        continue;
      image[j][i] |= bitmap->buffer[q * bitmap->width + p];
    }
  }
}

typedef struct
{
	char* font_file;
	char* name_png;
	char* text;
	int size;
	int anti_alias;
} conf_t;

char* parse_args(int argc, char** argv, conf_t* conf)
{
	get_files_names();
	memset(conf, 0, sizeof(conf_t));
	//conf->size = 72;
	if (argc == 1)
	{
        //conf->font_file="../*.ttf";
        char buf[500]="\0";
        int k=0;
        for(k=0;k<files.rows;k++)
        {
            if(strstr(files.list_of_files[k],".ttf"))
            {
                //strcat(buf,"../");
                strcat(buf,files.list_of_files[k]);
            }
        }
        conf->font_file=(char*)calloc(strlen(buf)+1,sizeof(char));
        memcpy(conf->font_file,buf,(strlen(buf)+1)*sizeof(char));
        conf->name_png="default_name.png";
        conf->text="default";
        //conf->size=72;
       //то это всегда путь к проге, а значит и остальных аргументов нет
	}
	if(argc==2)
	{
        //пришёл хотя бы один аргумент,надо выяснить какой
        //проверяем пришёл ли файл со шрифтом
        if(strstr(argv[1],".ttf"))
        {

            conf->font_file=argv[1];
            conf->name_png="default.png";
            conf->text="default";
        }
        else
        {
            if(strstr(argv[1],".png"))
            {
                conf->name_png=argv[1];



		char buf[500]="\0";
       	 	int k=0;
        	for(k=0;k<files.rows;k++)
        	{
            		if(strstr(files.list_of_files[k],".ttf"))
            		{
                	//strcat(buf,"../");
                	strcat(buf,files.list_of_files[k]);
            		}
        	}
        	conf->font_file=(char*)calloc(strlen(buf)+1,sizeof(char));
        	memcpy(conf->font_file,buf,(strlen(buf)+1)*sizeof(char));



                //conf->font_file="../*.ttf";
                conf->text="default";
            }
            else
            {

		char buf[500]="\0";
       	 	int k=0;
        	for(k=0;k<files.rows;k++)
        	{
            		if(strstr(files.list_of_files[k],".ttf"))
            		{
                	//strcat(buf,"../");
                	strcat(buf,files.list_of_files[k]);
            		}
        	}
		conf->font_file=(char*)calloc(strlen(buf)+1,sizeof(char));
        	memcpy(conf->font_file,buf,(strlen(buf)+1)*sizeof(char));

                //conf->font_file="../*.ttf";

		conf->name_png=(char*)calloc(strlen(argv[1])+1,sizeof(char));
		memcpy(conf->name_png,argv[1],(strlen(argv[1])+1)*sizeof(char));
                //conf->name_png=argv[1];
		conf->name_png=(char*)realloc(conf->name_png,(strlen(conf->name_png)+strlen(".png")+1)*sizeof(char));
                strcat(conf->name_png,".png");
                conf->text=argv[1];
            }
        }
    }
    if(argc==3)
    {
        if  (  (strstr(argv[1],".ttf") && strstr(argv[2],".png")) )
        {
            conf->font_file=argv[1];
            conf->name_png=argv[2];
            conf->text="default";
        }
        if((strstr(argv[1],".png") && strstr(argv[2],".ttf")))
        {
            conf->font_file=argv[2];
            conf->name_png=argv[1];
            conf->text="default";
        }
        if( strstr(argv[1],".ttf") && ( !strstr(argv[2],".png") && !strstr(argv[2],".ttf")))
        {
            conf->font_file=argv[1];
            conf->text=argv[2];

            //strcat(argv[2],".png");
            conf->name_png=argv[2];
            strcat(argv[2],".png");
        }
        if( strstr(argv[1],".png") && (!strstr(argv[2],".ttf") && !strstr(argv[2],".png")) )
        {

		char buf[500]="\0";
       	 	int k=0;
        	for(k=0;k<files.rows;k++)
        	{
            		if(strstr(files.list_of_files[k],".ttf"))
            		{
                	//strcat(buf,"../");
                	strcat(buf,files.list_of_files[k]);
            		}
        	}
		conf->font_file=(char*)calloc(strlen(buf)+1,sizeof(char));
        	memcpy(conf->font_file,buf,(strlen(buf)+1)*sizeof(char));


            //conf->font_file="../*.ttf";

            conf->name_png=argv[1];
            conf->text="default";
        }
    }
    if(argc==4)
    {
        if(strstr(argv[1],".ttf") && strstr(argv[2],".png") && (!strstr(argv[3],".png") && !strstr(argv[3],".ttf")) )
        {
            conf->font_file=argv[1];
            conf->name_png=argv[2];
            conf->text=argv[3];
        }
        if(strstr(argv[1],".ttf") &&  ( !strstr(argv[2],".png") && !strstr(argv[2],".ttf") ) &&  (strstr(argv[3],".png"))      )
        {
            conf->font_file=argv[1];
            conf->name_png=argv[3];
            conf->text=argv[2];

        }
        if(  (!strstr(argv[1],".png") && !strstr(argv[1],".ttf"))  &&  strstr(argv[2],".ttf") && strstr(argv[3],".png")     )
        {
            conf->font_file=argv[2];
            conf->name_png=argv[3];
            conf->text=argv[1];
        }
        //if(strstr(argv[1],".png")&&strstr(argv[2],".ttf")&&(!strstr(argv[3],".png") && !strstr(argv[3],".ttf")))
        if(strstr(argv[1],".png")&&(strstr(argv[2],".ttf")) && (!strstr(argv[3],".png") && !strstr(argv[3],".ttf")) )
        {
            conf->font_file=argv[2];
            conf->name_png=argv[1];
            conf->text=argv[3];
        }
        if(  strstr(argv[1],".png")  && (!strstr(argv[2],".png") && !strstr(argv[2],".ttf") ) && strstr(argv[3],".ttf"))
        {
            conf->font_file=argv[3];
            conf->name_png=argv[1];
            conf->text=argv[2];
        }

        if(   (!strstr(argv[1],".png") && !strstr(argv[1],".ttf"))  && strstr(argv[2],".png") && strstr(argv[3],".ttf")   )
        {
            conf->font_file=argv[3];
            conf->name_png=argv[2];
            conf->text=argv[1];
        }


    }

	//conf->font_file = argv[1];
	//conf->name_png=argv[2];
	//conf->text = argv[3];

		conf->size = 72;//atoi(argv[3]);

	//if (argc > 4)
	//{
		conf->anti_alias = 1;
	//}

  for ( int i = 0; i < HEIGHT; i++ )
  {
    for ( int j = 0; j < WIDTH; j++ )
    {
      image[i][j] = 0;
    }
  }
		//printf("init_image\n");

	return NULL;
}

char* render_glyph(FT_Face* face, conf_t conf)
{
	FT_Library ft;
	FT_Error err;

	err = FT_Init_FreeType(&ft);
	if (err) return "freetype init error";

	err = FT_New_Face(ft, conf.font_file, 0, face);
	if (err == FT_Err_Unknown_File_Format)
		return "unknown font file format";
	else if (err)
		return "error reading font file";

	err = FT_Set_Pixel_Sizes(*face, 0, conf.size);
	if (err) return "error setting font size";

		/*
				FT_UInt index = FT_Get_Char_Index(*face, *conf.text);
				printf("FT_UInt index = %u\n", index);
				if (index == 0) return "no glyph found for char";
				err = FT_Load_Glyph(*face, index, FT_LOAD_DEFAULT);
				if (err) return "error loading glyph";
				err = FT_Render_Glyph((*face)->glyph, conf.anti_alias ?
				                      FT_RENDER_MODE_NORMAL :
				                      FT_RENDER_MODE_MONO);
				if (err) return "error rendering glyph";
		*/

  int target_height;
  target_height = HEIGHT;
  FT_Vector     pen;
  FT_GlyphSlot  slot;
  slot = (*face)->glyph;
  pen.x = 300 * 64;
  pen.y = ( target_height - 200 ) * 64;
  int wid = 0;
	for (int i = 0; i < strlen(conf.text); ++i)
	{
		FT_UInt index = FT_Get_Char_Index(*face, conf.text[i]);
		//printf("FT_UInt index = %u\n", index);
		if (index == 0) return "no glyph found for char";
		err = FT_Load_Glyph(*face, index, FT_LOAD_DEFAULT);
		if (err) return "error loading glyph";
		err = FT_Render_Glyph((*face)->glyph, conf.anti_alias ?
		                      FT_RENDER_MODE_NORMAL :
		                      FT_RENDER_MODE_MONO);
		if (err) return "error rendering glyph";
		//draw_bitmap((*face)->glyph->bitmap);
	    //draw_bitmap( &slot->bitmap, slot->bitmap_left, target_height - slot->bitmap_top );
	    draw_bitmap( &slot->bitmap,
	    	slot->bitmap_left + wid,
	    	target_height - slot->bitmap_top-500);
	    wid += slot->bitmap.width;
	    pen.x += slot->advance.x;
	    pen.y += slot->advance.y;
	}


	return NULL;
}

char* cool_render_png(char* out, int aa)
{
    //char buf[500]="\0";
    //strcat(buf,"../");
    //strcat(buf,out);
	FILE* f = fopen(out, "wb");
	if (!f)
		return "failed to open output file";
	png_structp png_out = png_create_write_struct(
	                          PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_out)
		return "failed to create png write struct";

	png_infop png_info = png_create_info_struct(png_out);
	if (!png_info)
		return "failed to create png info struct";
		//printf("init_begin\n");
	//
	if (setjmp(png_jmpbuf(png_out)))
		return "png init io error";

	png_init_io(png_out, f);

	if (setjmp(png_jmpbuf(png_out)))
		return "IHDR write error";
		//printf("png_property\n");
	//
	png_set_IHDR(png_out,
	             png_info,
	             WIDTH,
	             HEIGHT,
	             aa ? 8 : 1,
	             PNG_COLOR_TYPE_GRAY,
	             PNG_INTERLACE_NONE,
	             PNG_COMPRESSION_TYPE_DEFAULT,
	             PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_out, png_info);
		//printf("another_png_property\n");
	//
	if (setjmp(png_jmpbuf(png_out)))
		return "png write error";

	int i;
	for (i = 0; i < HEIGHT; ++i)
	{
		//printf("\ti - %i\n",i);
		const unsigned char* rowptr = image[i];
		png_write_row(png_out, rowptr);
	}
		//printf("write\n");

	if (setjmp(png_jmpbuf(png_out)))
	{
		//printf("setjmp_error\n");
		return "png end error";
	}
		//printf("setjmp\n");
	png_write_end(png_out, NULL);
		//printf("png_write_end\n");

	fclose(f);
	return NULL;
}



int main(int argc, char** argv)
{
    clock_t begin =clock();
	conf_t conf;
	char* conf_err = parse_args(argc, argv, &conf);
	/*if (conf_err != NULL)
	{
		printf("Error: %s\n", conf_err);
		puts("Usage: render-text <font> <text> [<size> ]");
		puts("Example: render-text myfont.ttf foobar 24 yes");
		puts("         render-text myfont.ttf lorem");
		return 1;
	}*/

	//printf("font: %s, text: %s, size: %d, anti-alias: %s\n",
	       //conf.font_file,
	      // conf.text,
	      // conf.size,
	       //conf.anti_alias ? "yes" : "no");

	FT_Face face;


	char* ft_err = render_glyph(&face, conf);
		//printf("render_glyph\n");
	if (ft_err != NULL)
	{
		printf("freetype error: %s\n", ft_err);
		return 2;
	}

	//printf("bitmap rows: %d, width: %d\n",
	      // face->glyph->bitmap.rows,
	      // face->glyph->bitmap.width);

	//char* png_err = render_png(face, "a.png", conf.anti_alias);
	char* png_err = cool_render_png(conf.name_png, conf.anti_alias);
		//printf("cool_render_png\n");


	if (png_err != NULL)
	{
		printf("png error: %s\n", png_err);
		return 3;
	}
	/*if(argc==1)
	{
        free(conf.font_file);
	}*/
	//printf("OK! File wa created!\n");
    clock_t end=clock();
    double time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
    printf("\n%f\n",time_spent);
	return 0;
}

