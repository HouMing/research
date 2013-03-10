#include <malloc.h>
#include <stdio.h>
#include <memory.h>
#include "cif.h"

cif_type*
init_cif(cif_type *obj,int _width,int _height,int cnt_frame,int _format)
{
	obj = (cif_type *)malloc(sizeof(cif_type));
	if(obj == NULL)
		return NULL;
	obj->buf_size = _width*_height*_format*cnt_frame/2;
	obj->pt_begin = (u_char *)malloc(obj->buf_size);
	obj->pt_end = obj->pt_begin + obj->buf_size;
	obj->width = _width;
	obj->height = _height;
	obj->cnt_frame = cnt_frame;
	obj->yuv_type = _format;
	return obj;	
}

int
cif_open(cif_type *obj,FILE *_file)
{
	fread(obj->pt_begin,obj->buf_size,1,_file);
	obj->pt_end = obj->pt_begin + obj->buf_size;
	return 0;
}

int
yuv420toyuv444(cif_type *_cif_420,cif_type *_cif_444)
{
	int cnt = _cif_420->cnt_frame;
	int w = _cif_444->width;
	int h = _cif_444->height;
	u_char *src_y,*src_u,*src_v;
	u_char *dst_y,*dst_u,*dst_v;
	src_y = _cif_420->pt_begin;
	src_u = src_y + w*h;
	src_v = src_u + w*h/4;
	dst_y = _cif_444->pt_begin;
	dst_u = dst_y + w*h;
	dst_v = dst_u + w*h;
	for(int cur_cnt = 0; cur_cnt < cnt ; cur_cnt++)
	{
		//Y U V
		for(int cur_h =0 ; cur_h<h;cur_h++)
		{
			for(int cur_w=0; cur_w<w; cur_w++)
			{
				dst_y[cur_h*w + cur_w] = src_y[cur_h*w + cur_w];
				dst_u[cur_h*w + cur_w] = src_u[cur_h/2*w/2+cur_w/2];
				dst_v[cur_h*w + cur_w] = src_v[cur_h/2*w/2+cur_w/2];
			}
		}
			src_y += w*h*3/2;
			src_u = src_y + w*h;
			src_v = src_u + w*h/4;
			dst_y += w*h*3;
			dst_u = dst_y + w*h;
			dst_v = dst_u + w*h;
	}
	return 0;
}