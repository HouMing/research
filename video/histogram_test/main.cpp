#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <malloc.h>


#define u_char unsigned char

#define W 500
#define H 500

int
main(int argn,char** argc)
{
	FILE *seed = NULL;
	seed = fopen("seed.yuv","r");
	FILE *dst_file = NULL;
	dst_file = fopen("dst.yuv","w");
	u_char *src_seed = (u_char*)malloc(sizeof(char)*W*H*3);
	u_char *dst_seed = (u_char*)malloc(sizeof(char)*W*H*3);
	static int hist[256];
	static u_char dst_hist[256];
	u_char law_num = 0;
	u_char high_num = 256;
	fread(src_seed,1,W*H*3,seed);
	memcpy(dst_seed,src_seed,W*H*3);
	for(int i=0;i<W*H;i++)
	{
		hist[src_seed[i]]++;
	}

#if 0
	for(int i=0;i<256;i++)
	{
		fhist[i] = (0.0+hist[i])/sum;
		printf("%d:%f ",i,fhist[i]);

	}
#endif
	for(u_char i=0;i != 0xff;i++)
	{
		if(hist[i] != 0)
		{
			law_num =i;
			break;
		}
	}

	for(u_char i=0xff;i!=0x00;i--)
	{
		if(hist[i] != 0)
		{
			high_num = i;
			break;
		}
	}

	for(int i=0;i<256;i++)
	{
		if(i<law_num)
			dst_hist[i] = 0;
		else if(i>high_num)
			dst_hist[i] = 255;
		else
		dst_hist[i] = ((255.0/(0.0+high_num-law_num)*(i-law_num))+0.5);
	}
#if 0
	printf("\n");
	for(int i=0;i<256;i++)
	{
		printf("%d:%d ",i,dst_hist[i]);
	}
#endif
	for(int i=0;i<W*H;i++)
	{
		dst_seed[i] = dst_hist[src_seed[i]];
	}
	
	fwrite(dst_seed,1,H*W*3,dst_file);

	return 0;
}	