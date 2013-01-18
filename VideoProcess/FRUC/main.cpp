#include <stdio.h>
#include <malloc.h>

#include "type.h"
#include "cif.h"
#include "fruc.h"

#define CIF_WIDTH 352
#define CIF_HEIGHT 288
#define CIF_CNT_FRAME 24

int
main(int argc,char** argv)
{
	FILE *cif = fopen(argv[1],"rb");
	FILE *cif444 = fopen(argv[2],"wb");
	cif_type *buf_cif420;
	cif_type *buf_cif444;
	cif_type *dst_cif444;
	buf_cif420=init_cif(buf_cif420,CIF_WIDTH,CIF_HEIGHT,CIF_CNT_FRAME,YUV420);
	buf_cif444=init_cif(buf_cif444,CIF_WIDTH,CIF_HEIGHT,CIF_CNT_FRAME,YUV444);
	dst_cif444=init_cif(dst_cif444,CIF_WIDTH,CIF_HEIGHT,CIF_CNT_FRAME*2-1,YUV444);
	cif_open(buf_cif420,cif);
	yuv420toyuv444(buf_cif420,buf_cif444);
	test_fruc(dst_cif444,buf_cif444);
	fwrite(dst_cif444->pt_begin,dst_cif444->buf_size,1,cif444);
	return 0;
}