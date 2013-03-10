#include <stdio.h>
#include "bmp2yuv.h"

int main(int argc,char *argv[])
{
	BOOL bRes = TRUE;
	BMPImage bmpImage;
	PCMImage pcmImage;
	
	Initialize(&bmpImage, &pcmImage);
	
	// Read bmp from file
	bRes = ReadBMP(argv[1], &bmpImage);// ����BMP�ļ� test.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = CreatePCMImage(&bmpImage, &pcmImage);//Ԥ�����ͼ��
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = WritePCM(argv[2], &pcmImage);//���Ԥ�����ͼ�� t0.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = WritePCM_back(argv[3], &pcmImage);//���8bit�ָ�ͼ�� t8.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = Create1bitsPCMImage(&bmpImage, &pcmImage);//1bit����Ԥ�����ͼ�� 
	if (bRes == FALSE)
	{
		goto Exit;
	}
	
	bRes = WritePCM(argv[4], &pcmImage);//���1bit����Ԥ�����ͼ�� t1.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = Create2bitsPCMImage(&bmpImage, &pcmImage);//2bit����Ԥ�����ͼ��
	if (bRes == FALSE)
	{
		goto Exit;
	}

	bRes = WritePCM(argv[5], &pcmImage);//���2bit����Ԥ�����ͼ�� t2.bmp
	if (bRes == FALSE)
	{
		goto Exit;
	}
	
Exit:
	Uninitialize(&bmpImage, &pcmImage);
	return 0;
}