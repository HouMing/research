#pragma once
#include "type.h"
#include "stdio.h"

#define YUV444 6 
#define	YUV422 4 
#define	YUV420 3

typedef struct
{
	u_char *pt_begin;
	u_char *pt_end;
	int buf_size;
	int width;
	int height;
	int cnt_frame;
	int yuv_type;
}cif_type;

cif_type* init_cif(cif_type *obj,int _width,int _height,int cnt_frame,int _format);

int cif_open(cif_type *obj,FILE *_file);

int yuv420toyuv444(cif_type *_cif_420,cif_type *_cif_444);