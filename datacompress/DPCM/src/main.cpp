#include <stdio.h>
#include "bmp2yuv.h"

int main(int argc,char *argv[])
{
	BOOL bRes = TRUE;
	BMPImage bmpImage;
	PCMImage pcmImage;
	
	Initialize(&bmpImage, &pcmImage);
	
	// Read bmp from file
	bRes = ReadBMP(argv[1], &bmpImage);// ¶ÁÈëBMPÎÄ¼ş test.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = CreatePCMImage(&bmpImage, &pcmImage);//Ô¤²âÎó²îÍ¼Ïñ
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = WritePCM(argv[2], &pcmImage);//Êä³öÔ¤²âÎó²îÍ¼Ïñ t0.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = WritePCM_back(argv[3], &pcmImage);//Êä³ö8bit»Ö¸´Í¼Ïñ t8.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = Create1bitsPCMImage(&bmpImage, &pcmImage);//1bitÁ¿»¯Ô¤²âÎó²îÍ¼Ïñ 
	if (bRes == FALSE)
	{
		goto Exit;
	}
	
	bRes = WritePCM(argv[4], &pcmImage);//Êä³ö1bitÁ¿»¯Ô¤²âÎó²îÍ¼Ïñ t1.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = Create2bitsPCMImage(&bmpImage, &pcmImage);//2bitÁ¿»¯Ô¤²âÎó²îÍ¼Ïñ
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = WritePCM(argv[5], &pcmImage);//Êä³ö2bitÁ¿»¯Ô¤²âÎó²îÍ¼Ïñ t2.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}
	
Exit:
	Uninitialize(&bmpImage, &pcmImage);
	return 0;
}