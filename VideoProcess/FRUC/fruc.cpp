#include "fruc.h"

typedef struct
{
	u_char val[8][8];
}block;

typedef struct
{
	float x;
	float y;
}m_vector;

int 
get_block(cif_type *src,int cnt_frame,int x,int y,block *in)
{
	if(cnt_frame<0)
		return -1;
	int w = src->width;
	int h = src->height;
	u_char *frame = src->pt_begin + cnt_frame*h*w*src->yuv_type/2;
	u_char *block_top;
	block_top = frame + x + y*w ;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			in->val[i][j] = block_top[i*w+j];
		}
	return 0;
}

int
set_block(cif_type *dst,int cnt_frame,int x,int y,block *blc)
{
	if(cnt_frame<0)
		return -1;
	int w = dst->width;
	int h = dst->height;
	u_char *frame = dst->pt_begin + (cnt_frame-1)*h*w*dst->yuv_type/2;
	u_char *block_top;
	block_top = frame + x + y*w ;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			block_top[i*w+j]=blc->val[i][j];
		}
	return 0;
}

int 
cmp_block(block *a,block *b)
{
	int sum;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			sum += abs(a->val[i][j]-b->val[i][j]);
		}
}

int
test_fruc(cif_type* dst,cif_type *src)
{
	block fst_blc;
	block a;
	block b;
	int cnt_frame = dst->cnt_frame;
	for(int cur_cnt=0;cur_cnt<cnt_frame;cur_cnt++)
		for(int i=0;i<36;i++)
			for(int j=0;j<44;j++)
			{
				for()
				get_block(src,cur_cnt,j*8,i*8,&fst_blc);
				set_block(dst,cur_cnt,j*8,i*8,&fst_blc);
			}
		return 0;
}