// DPCM_DECODER_1.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "bmp2yuv.h"



BITMAPFILEHEADER bm2fh;
BITMAPINFOHEADER* pBMIH2;
int nSize2;

int main(int argc, char* argv[])
{
	BOOL bRes = TRUE;
	BMPImage bmpImage;
	PCMImage pcmImage;
	
	Initialize(&bmpImage, &pcmImage);
	
	if (bRes = ReadBMP(argv[1], &bmpImage) == FALSE)
	{
		goto Exit;
	}

	if (bRes = CreatePCMImage(&bmpImage, &pcmImage) == FALSE)
	{
		goto Exit;
	}
	
	if (bRes = WritePCM(argv[2], &pcmImage) == FALSE)
	{
		goto Exit;
	}
	
Exit:
	Uninitialize(&bmpImage, &pcmImage);
	return 0;
}


void Initialize(BMPImage* pBMP, PCMImage* pPCM)
{
	if (pBMP != NULL)
	{
		memset(pBMP, 0, sizeof(BMPImage));
	}
	if (pPCM != NULL)
	{
		memset(pPCM, 0, sizeof(PCMImage));
	}
}

void Uninitialize(BMPImage* pBMP, PCMImage* pPCM)
{
	if (pBMP != NULL)
	{
		if (pBMP->pbImage != NULL)
		{
			delete [] pBMP->pbImage;
			pBMP->pbImage = NULL;
		}
		
		if (pBMP->pBMIH != NULL)
		{
			delete [] pBMP->pBMIH;
			pBMP->pBMIH = NULL;
		}
		memset(pBMP, 0, sizeof(BMPImage));
	}
	
	if (pPCM != NULL)
	{
		if (pPCM->pbPCM != NULL)
		{
			delete [] pPCM->pbPCM;
			pPCM->pbPCM = NULL;
		}
		memset(pPCM, 0, sizeof(PCMImage));
	}
}



BOOL ReadBMP(const char* szPath, BMPImage* pBMP)
{
	BOOL bRes = TRUE;
	BITMAPFILEHEADER bmfh;			//位图文件头
	int nSize;
	int nBytesRead;
	FILE* fp = NULL;
	if (szPath == NULL || pBMP == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	if (pBMP->pbImage != NULL)
	{
		delete [] pBMP->pbImage;
		pBMP->pbImage = NULL;
	}

	if (pBMP->pBMIH != NULL)
	{
		delete [] pBMP->pBMIH;
		pBMP->pBMIH = NULL;
	}

	if ((fp=fopen(szPath, "rb")) == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	nBytesRead = 0;

	nBytesRead = fread(&bmfh, sizeof(bmfh), 1, fp);

    bm2fh=bmfh;

	//check if it is a bmp file
	if(bmfh.bfType != 0x4d42) 
	{
		bRes = FALSE;
		goto Exit;
	}

	nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);
	
	pBMP->pBMIH = (BITMAPINFOHEADER*) new BYTE[nSize];
	if (pBMP->pBMIH == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	nBytesRead = fread(pBMP->pBMIH, nSize, 1, fp);

	pBMIH2=pBMP->pBMIH;
    nSize2=nSize;

	// set some bitmap info
	pBMP->pvColorTable = (LPBYTE) pBMP->pBMIH + sizeof(BITMAPINFOHEADER);

	pBMP->nByteWidth = (((pBMP->pBMIH->biWidth)*(pBMP->pBMIH->biBitCount) + 31) / 32 * 4);	
	pBMP->dwSizeImage = pBMP->nByteWidth * pBMP->pBMIH->biHeight;						

	// read image data
	pBMP->pbImage = (LPBYTE) new char[pBMP->dwSizeImage];
	if (pBMP->pbImage == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	nBytesRead = fread(pBMP->pbImage, pBMP->dwSizeImage, 1, fp);

Exit:
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
	if (bRes == FALSE && pBMP != NULL)
	{
		if (pBMP->pbImage != NULL)
		{
			delete [] pBMP->pbImage;
			pBMP->pbImage = NULL;
		}

		if (pBMP->pBMIH != NULL)
		{
			delete [] pBMP->pBMIH;
			pBMP->pBMIH = NULL;
		}
		memset(pBMP, 0, sizeof(BMPImage));
	}

	return bRes;
}

BOOL CreatePCMImage(const BMPImage* pBMP, PCMImage* pPCM)
{
	BOOL bRes = TRUE;
	if (pBMP == NULL || pPCM == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}
	
	if (pPCM->pbPCM != NULL)		//清空PCM的旧数据
	{
		delete [] pPCM->pbPCM;
		pPCM->pbPCM = NULL;
	}
	
	pPCM->dwHeight = pBMP->pBMIH->biHeight;
	pPCM->dwWidth = pBMP->pBMIH->biWidth;
	pPCM->dwSize = pPCM->dwHeight * pPCM->dwWidth ;
	pPCM->pbPCM = (LPBYTE) new BYTE[pPCM->dwSize];//创建空间大小
    
	if (pPCM->pbPCM == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	switch (pBMP->pBMIH->biBitCount)
	{
	case 8:
		{
#define left_predict_1bit 1
#ifdef left_predict_1bit
			LPBYTE bpPCMPoint = pPCM->pbPCM;
			LPBYTE bpBMPPoint = pBMP->pbImage;
			for(unsigned int i = 0; i < pPCM->dwHeight; i++)// 用左像素点预测
			{
				bpPCMPoint[i*pPCM->dwWidth]= (BYTE)(bpBMPPoint[i*pPCM->dwWidth]);
				for(unsigned int j = 1; j < pPCM->dwWidth; j++)
				{
					if(bpBMPPoint[i*pPCM->dwWidth+j] == 255)
					bpPCMPoint[i*pPCM->dwWidth + j] = (BYTE)(0.95*bpPCMPoint[i*pPCM->dwWidth+j-1]+2);
					else
					bpPCMPoint[i*pPCM->dwWidth + j] = (BYTE)(0.95*bpPCMPoint[i*pPCM->dwWidth+j-1]-2);
				}
			}
#endif
#ifdef left_predict_8bit
			LPBYTE bpPCMPoint = pPCM->pbPCM;
			LPBYTE bpBMPPoint = pBMP->pbImage;
			for(unsigned int i = 0; i < pPCM->dwHeight; i++)// 用左像素点预测
			{
				bpPCMPoint[i*pPCM->dwWidth]= (BYTE)(bpBMPPoint[i*pPCM->dwWidth]);
				for(unsigned int j = 1; j < pPCM->dwWidth; j++)
				{
					bpPCMPoint[i*pPCM->dwWidth + j] = (BYTE)(((bpBMPPoint[i*pPCM->dwWidth+j]-128)*2)+0.95*bpPCMPoint[i*pPCM->dwWidth+j-1]);
				}
			}
#endif
#ifdef left_predict
			LPBYTE bpPCMPoint = pPCM->pbPCM;
			LPBYTE bpBMPPoint = pBMP->pbImage;
			for(unsigned int i = 0; i < pPCM->dwHeight; i++)// 用左像素点预测
			{
			 	*(bpPCMPoint++)= (unsigned char)(bpBMPPoint[i*pPCM->dwWidth]);
				for(unsigned int j = 1; j < pPCM->dwWidth; j++)
				{
					*(bpPCMPoint++)= (unsigned char)(bpBMPPoint[i*pPCM->dwWidth+j]+0.95*pPCM->pbPCM[i*pPCM->dwWidth+j-1]-128);
				}
			}
#endif
#ifdef up_predict
			LPBYTE bpPCMPoint = NULL;
			LPBYTE bpBMPPoint = pBMP->pbImage;
			for(unsigned int i = 0; i < pPCM->dwWidth; i++)// 用上像素点预测
			{
				bpPCMPoint = pPCM->pbPCM + i;
				*(bpPCMPoint) = (unsigned char)(bpBMPPoint[i]);
				bpPCMPoint += pPCM->dwWidth;
				for(unsigned int j = 1; j < pPCM->dwHeight; j++)
				{
					*(bpPCMPoint)= (unsigned char)(bpBMPPoint[j*pPCM->dwWidth+i]+0.95*bpBMPPoint[(j-1)*pPCM->dwWidth+i]-128);
					bpPCMPoint += pPCM->dwWidth;
				}
			}
#endif
		}
		break;
	default:
		bRes = FALSE;
		goto Exit;
	}
Exit:
	if (bRes == FALSE && pPCM != NULL)
	{
		if (pPCM->pbPCM != NULL)
		{
			delete [] pPCM->pbPCM;
			pPCM->pbPCM = NULL;
		}
		memset(pPCM, 0, sizeof(PCMImage));
	}
	return bRes;
}

BOOL WritePCM(const char* szPath, const PCMImage* pPCM)
{
	BOOL bRes = TRUE;
	FILE* fp = NULL;
	if (szPath == NULL || 
		pPCM == NULL || 
		pPCM->pbPCM == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}
	
	if ((fp=fopen(szPath, "wb")) == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	fwrite(&bm2fh, 1, sizeof(bm2fh), fp);
	fwrite(pBMIH2, 1, nSize2, fp);
    fwrite(pPCM->pbPCM, 1, pPCM->dwSize, fp);

Exit:
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
	return bRes;
}

