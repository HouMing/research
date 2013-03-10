#include "../include/main.h"
#include "../include/LinearFilter.h"
#include "../include/NonlinearFilter.h"
#include "../include/ConvKernal.h"
#include "../include/YUVFile.h"

#define Width 464
#define Height 538

int
main(int argn,char** argv)
{
	char src[255];
	char dst[255];
	printf("输入源图像路径：\n");
	scanf("%s",src);
	printf("输入目的图像路径：\n");
	scanf("%s",dst);
	
	YUVFile *srcF,*dstF;
	
	srcF = loadYUVFile(src,Width,Height,"rb");
	dstF = loadYUVFile(dst,Width,Height,"wb");

	ConvKernal* conv;

	int tmp[5][5] = 
	{
		{0,0,1,0,0},
		{0,0,1,0,0},
		{1,1,1,1,1},
		{0,0,1,0,0},
		{0,0,1,0,0}
	};

	int *convValues = (int *)tmp;


	conv =initConvKernal(5,5,convValues);

	medianFilter(srcF,conv,dstF);
	overWrite(dstF);
	
	closeYUVFile(srcF);
	closeYUVFile(dstF);
	ReleaseConv(conv);

	return 11;
}