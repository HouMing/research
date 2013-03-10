#include "bmp2yuv.h"
#include "stdio.h"

BITMAPFILEHEADER bm2fh;
BITMAPINFOHEADER* pBMIH2;
int nSize2;
// PVOID pPalette;

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

	// release previous data
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


	fp=fopen(szPath, "rb");
	if (fp == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}


	nBytesRead = 0;
	nBytesRead = fread(&bmfh, sizeof(bmfh), 1, fp);			//读取文件头信息
	/*if (nBytesRead != sizeof(bmfh))
	{
		bRes = FALSE;
		goto Exit;
	}*/

    bm2fh=bmfh;

	//check if it is a bmp file
	if(bmfh.bfType != 0x4d42) // 'BM'即说明此文件是BMP文件
	{
		bRes = FALSE;
		goto Exit;
	}

	// read info header and palette (optional)用来计算文件信息头字节数
	nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);/* 说明从BITMAPFILEHEADER结构开始到实际的图像数
据之间的字节偏移量 */
	//nSize = sizeof(BITMAPINFOHEADER);	//zhangjun
	
	pBMP->pBMIH = (BITMAPINFOHEADER*) new BYTE[nSize];
	if (pBMP->pBMIH == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	nBytesRead = fread(pBMP->pBMIH, nSize, 1, fp);
	/*if (nBytesRead != nSize)
	{
		bRes = FALSE;
		goto Exit;
	}*/

	pBMIH2=pBMP->pBMIH;
    nSize2=nSize;

	// set some bitmap info
	pBMP->pvColorTable = (LPBYTE) pBMP->pBMIH + sizeof(BITMAPINFOHEADER);

   //  pPalette = (LPBYTE) pBMP->pBMIH + sizeof(BITMAPINFOHEADER);

	pBMP->nByteWidth = (((pBMP->pBMIH->biWidth)*(pBMP->pBMIH->biBitCount) + 31) / 32 * 4);	//计算每一行的字节数，每行的字节数必须是4的整数倍，如果不是则会填充0来补齐
	pBMP->dwSizeImage = pBMP->nByteWidth * pBMP->pBMIH->biHeight;							//计算整个数据部分的大小

	// read image data
	pBMP->pbImage = (LPBYTE) new char[pBMP->dwSizeImage];//开辟大小为数据部分大小的空间
	if (pBMP->pbImage == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	nBytesRead = fread(pBMP->pbImage, pBMP->dwSizeImage, 1, fp);//从文件中读取整幅图像的数据部分
	/*if (nBytesRead != pBMP->dwSizeImage)
	{
		bRes = FALSE;
		goto Exit;
	}*/

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
	pPCM->pbPredict = new int[pPCM->dwSize];
	pPCM->pbBack = (LPBYTE) new BYTE[pPCM->dwSize];
    
	if (pPCM->pbPCM == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}

	switch (pBMP->pBMIH->biBitCount)
	{
	case 8:
		{
#define bitone 1
#ifdef bitone
			LPBYTE bpPCMPoint = pPCM->pbPCM;
			LPBYTE bpBMPPoint = pBMP->pbImage;
			LPBYTE back_buf = pPCM->pbBack;
			int *predict_buf = pPCM->pbPredict;		
			for(unsigned int i = 0; i < pPCM->dwHeight; i++)// 用左像素点预测
			{
				bpPCMPoint[i*pPCM->dwWidth] = (BYTE)(bpBMPPoint[i*pPCM->dwWidth]);
				predict_buf[i*pPCM->dwWidth] = 0;
				back_buf[i*pPCM->dwWidth] = (BYTE)(bpBMPPoint[i*pPCM->dwWidth]);
				for(unsigned int j = 1; j < pPCM->dwWidth; j++)
				{
					predict_buf[i*pPCM->dwWidth+j] = bpBMPPoint[i*pPCM->dwWidth+j]-0.95*(back_buf[i*pPCM->dwWidth+j-1]);
					if( predict_buf[i*pPCM->dwWidth+j]>0)
					{
					bpPCMPoint[i*pPCM->dwWidth+j] =255;
					back_buf[i*pPCM->dwWidth+j] = (0.934*back_buf[i*pPCM->dwWidth+j-1]+12)>255?255:(0.934*back_buf[i*pPCM->dwWidth+j-1]+12);
					}
					else 
					{
					bpPCMPoint[i*pPCM->dwWidth+j] = 0;
					back_buf[i*pPCM->dwWidth+j] = (0.934*back_buf[i*pPCM->dwWidth+j-1]-12)<0?0:(0.934*back_buf[i*pPCM->dwWidth+j-1]-12);
					}
				}
			}
#endif
#ifdef left_predict_feedback
			LPBYTE bpPCMPoint = pPCM->pbPCM;
			LPBYTE bpBMPPoint = pBMP->pbImage;
			LPBYTE back_buf = pPCM->pbBack;
			int *predict_buf = pPCM->pbPredict;		
			for(unsigned int i = 0; i < pPCM->dwHeight; i++)// 用左像素点预测
			{
				bpPCMPoint[i*pPCM->dwWidth] = (BYTE)(bpBMPPoint[i*pPCM->dwWidth]);
				predict_buf[i*pPCM->dwWidth] = 0;
				back_buf[i*pPCM->dwWidth] = (BYTE)(bpBMPPoint[i*pPCM->dwWidth]);
				for(unsigned int j = 1; j < pPCM->dwWidth; j++)
				{
					predict_buf[i*pPCM->dwWidth+j] = bpBMPPoint[i*pPCM->dwWidth+j]-0.95*(back_buf[i*pPCM->dwWidth+j-1]);
					bpPCMPoint[i*pPCM->dwWidth+j] = predict_buf[i*pPCM->dwWidth+j]/2 + 128;
					back_buf[i*pPCM->dwWidth+j] = 0.95*back_buf[i*pPCM->dwWidth+j-1]+(bpPCMPoint[i*pPCM->dwWidth+j]-128)*2;
				}
			}
#endif
#ifdef left_predict
			LPBYTE bpPCMPoint = pPCM->pbPCM;
			LPBYTE bpBMPPoint = pBMP->pbImage;
			for(unsigned int i = 0; i < pPCM->dwHeight; i++)// 用左像素点预测
			{
			 	*(bpPCMPoint++)= (u_char)(bpBMPPoint[i*pPCM->dwWidth]);
				for(unsigned int j = 1; j < pPCM->dwWidth; j++)
				{
					*(bpPCMPoint++)= (u_char)(bpBMPPoint[i*pPCM->dwWidth+j]-0.95*bpBMPPoint[i*pPCM->dwWidth+j-1]+128);
				}
			}
#endif
#ifdef up_predict
			LPBYTE bpPCMPoint = NULL;
			LPBYTE bpBMPPoint = pBMP->pbImage;
			for(unsigned int i = 0; i < pPCM->dwWidth; i++)// 用上像素点预测
			{
				bpPCMPoint = pPCM->pbPCM + i;
				*(bpPCMPoint) = (u_char)(bpBMPPoint[i]);
				bpPCMPoint += pPCM->dwWidth;
				for(unsigned int j = 1; j < pPCM->dwHeight; j++)
				{
					*(bpPCMPoint)= (u_char)(bpBMPPoint[j*pPCM->dwWidth+i]-0.95*bpBMPPoint[j*pPCM->dwWidth+i-pPCM->dwWidth]+128);
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
	
	
	fp=fopen(szPath, "wb");
	if (fp == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}


	fwrite(&bm2fh, 1, sizeof(bm2fh), fp);
	/*  nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER)；
	bmfh.bfOffBits为BITMAPFILEHEADER结构开始到实际的图像数
	据之间的字节偏移量 */
	fwrite(pBMIH2, 1, nSize2, fp);
// 	fwrite(pPalette, 1,1024, fp);
    fwrite(pPCM->pbPCM, 1, pPCM->dwSize, fp);

Exit:
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
	return bRes;
}

BOOL WritePCM_back(const char* szPath, const PCMImage* pPCM)
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
	
	
	fp=fopen(szPath, "wb");
	if (fp == NULL)
	{
		bRes = FALSE;
		goto Exit;
	}


	fwrite(&bm2fh, 1, sizeof(bm2fh), fp);
	/*  nSize = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER)；
	bmfh.bfOffBits为BITMAPFILEHEADER结构开始到实际的图像数
	据之间的字节偏移量 */
	fwrite(pBMIH2, 1, nSize2, fp);
// 	fwrite(pPalette, 1,1024, fp);
    fwrite(pPCM->pbBack, 1, pPCM->dwSize, fp);

Exit:
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
	return bRes;
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
	if (pPCM->pbPredict != NULL)
	{
		delete [] pPCM->pbPredict;
		pPCM->pbPredict = NULL;
	}
	if (pPCM->pbBack != NULL)
	{
		delete [] pPCM->pbBack;
		pPCM->pbBack = NULL;
	}
	memset(pPCM, 0, sizeof(PCMImage));
	}
}

BOOL Create1bitsPCMImage(const BMPImage* pBMP, PCMImage* pPCM)
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
			LPBYTE bpPCMPoint = pPCM->pbPCM;
			int *bpBMPPoint = pPCM->pbPredict;
			for(unsigned int i = 0; i < pPCM->dwHeight; i++)// 用左像素点预测(1bits量化)
			{
				for(unsigned int j = 0; j < pPCM->dwWidth; j++)
				{
					if (j==0)
					{
                     bpPCMPoint[i*pPCM->dwWidth]= (u_char)(pBMP->pbImage[i*pPCM->dwWidth]);
					} 
					else
					{
					bpPCMPoint[i*pPCM->dwWidth+j]= (u_char)(bpBMPPoint[i*pPCM->dwWidth+j]);
					if (bpBMPPoint[i*pPCM->dwWidth+j]<0)
						bpPCMPoint[i*pPCM->dwWidth+j]=0;
					if (bpBMPPoint[i*pPCM->dwWidth+j]>=0)
						bpPCMPoint[i*pPCM->dwWidth+j]=255;
					}
				}
			}
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

BOOL Create2bitsPCMImage(const BMPImage* pBMP, PCMImage* pPCM)
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
			LPBYTE bpPCMPoint = pPCM->pbPCM;
			int *bpBMPPoint = pPCM->pbPredict;
			for(unsigned int i = 0; i < pPCM->dwHeight; i++)// 用左像素点预测(1bits量化)
			{
				for(unsigned int j = 0; j < pPCM->dwWidth; j++)
				{
					if (j==0)
					{
						bpPCMPoint[i*pPCM->dwWidth]= (u_char)(pBMP->pbImage[i*pPCM->dwWidth]);
					} 
					else
					{
						bpPCMPoint[i*pPCM->dwWidth+j]= (u_char)(bpBMPPoint[i*pPCM->dwWidth+j]);
						if (bpBMPPoint[i*pPCM->dwWidth+j]<-128)
							bpPCMPoint[i*pPCM->dwWidth+j]=0;
						else if(bpBMPPoint[i*pPCM->dwWidth+j]<0)
							bpPCMPoint[i*pPCM->dwWidth+j]=85;
						else if(bpBMPPoint[i*pPCM->dwWidth+j]<128)
							bpPCMPoint[i*pPCM->dwWidth+j]=170;
						if (bpBMPPoint[i*pPCM->dwWidth+j]>=128)
							bpPCMPoint[i*pPCM->dwWidth+j]=255;
					}

				}
			}
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
	
	
