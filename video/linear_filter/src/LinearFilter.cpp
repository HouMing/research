#include "../include/LinearFilter.h"


/* 加权线性滤波 */
/*
YUVFile* linearFilter(YUVFile* src,ConvKernal* conv,YUVFile* dst)
@param src
@param conv
@param dst
notice:该函数默认src 和 dst 是一样的大小，没有做相关的错误检测和错误处理，请注
意
*/ 

void linearFiltering(u_int x,u_int y,ConvKernal*,YUVFile *src,YUVFile *dst);

extern YUVFile*
linearFilter(YUVFile* src,ConvKernal* conv,YUVFile* dst)
{
	assert(src != NULL);
	assert(conv != NULL);
	assert(dst != NULL);
	u_int srcWidth = src->width;
	u_int srcHeight = src->height;
	for(u_int y = 0 ; y < srcHeight ; y++)
		for(u_int x = 0 ; x < srcWidth ; x++)
		{
			if(x == 0 && y == 0)
			linearFiltering(x+1,y+1,conv,src,dst);
			else if(y == 0)
			linearFiltering(x,y+1,conv,src,dst);
			else if(x == 0)
			linearFiltering(x+1,y,conv,src,dst);
			else if((x == srcWidth - 1) && (y == srcHeight -1))
			linearFiltering(x-1,y-1,conv,src,dst);
			else if(y == srcHeight -1)
			linearFiltering(x,y-1,conv,src,dst);
			else if(x == srcWidth - 1)
			linearFiltering(x-1,y,conv,src,dst);
			else
			linearFiltering(x,y,conv,src,dst);
		}
	return dst;
}


void
linearFiltering(u_int x,u_int y,ConvKernal* conv,YUVFile *src,YUVFile *dst)
{
	/* */
	const int convW = conv->width;
	const int convH = conv->height;
	YUVFilePoint* pSrc=(YUVFilePoint*)malloc(sizeof(YUVFilePoint)*convW*convH);

	for(int j = 0 ; j < convH; j++)
		for(int i = 0; i <convW;i++)
		{
			pSrc[j*convW + i] = getPointXY(src,x+i-1,y+j-1);
		}
	/* */
	u_int divisor = 0;
	u_int sumY = 0;
	u_int sumU = 0;
	u_int sumV = 0;
	for(int i = 0; i < convH; i++)
	{
		for(int j = 0 ; j < convW; j++)
		{
			sumY += *(pSrc[j*convW + i].subY) * (*(conv->values + i*convW + j));
			sumU += *(pSrc[j*convW + i].subU) * (*(conv->values + i*convW + j));
			sumV += *(pSrc[j*convW + i].subV) * (*(conv->values + i*convW + j));
			divisor +=(*(conv->values + i*convW + j));
		}
	}
	sumY = sumY / divisor;
	sumU = sumU / divisor;
	sumV = sumV / divisor;
		
	YUVFilePoint pDst = getPointXY(dst,x,y);
 	*(pDst.subY) = sumY;
	*(pDst.subU) = sumU;
	*(pDst.subV) = sumV;
}

/* Laplace */
void laplaceFiltering(u_int x,u_int y,ConvKernal* conv,YUVFile *src,YUVFile *dst);
YUVFile*
LaplaceFilter(YUVFile* src,ConvKernal* conv,YUVFile* dst)
{
	assert(src != NULL);
	assert(conv != NULL);
	assert(dst != NULL);
	u_int srcWidth = src->width;
	u_int srcHeight = src->height;
	for(u_int y = 0 ; y < srcHeight ; y++)
		for(u_int x = 0 ; x < srcWidth ; x++)
		{
			if(x == 0 && y == 0)
				laplaceFiltering(x+1,y+1,conv,src,dst);
			else if(y == 0)
				laplaceFiltering(x,y+1,conv,src,dst);
			else if(x == 0)
				laplaceFiltering(x+1,y,conv,src,dst);
			else if((x == srcWidth - 1) && (y == srcHeight -1))
				laplaceFiltering(x-1,y-1,conv,src,dst);
			else if(y == srcHeight -1)
				laplaceFiltering(x,y-1,conv,src,dst);
			else if(x == srcWidth - 1)
				laplaceFiltering(x-1,y,conv,src,dst);
			else
				laplaceFiltering(x,y,conv,src,dst);
		}
		return dst;
}
void
laplaceFiltering(u_int x,u_int y,ConvKernal* conv,YUVFile *src,YUVFile *dst)
{
	/* */
	const int convW = conv->width;
	const int convH = conv->height;
	YUVFilePoint* pSrc=(YUVFilePoint*)malloc(sizeof(YUVFilePoint)*convW*convH);

	for(int j = 0 ; j < convH; j++)
		for(int i = 0; i <convW;i++)
		{
			pSrc[j*convW + i] = getPointXY(src,x+i-1,y+j-1);
		}
	/* */
	u_int sumY = 0;
	u_int sumU = 0;
	u_int sumV = 0;
	for(int i = 0; i < convH; i++)
	{
		for(int j = 0 ; j < convW; j++)
		{
			sumY += *(pSrc[j*convW + i].subY) * (*(conv->values + i*convW + j));
			sumU += *(pSrc[j*convW + i].subU) * (*(conv->values + i*convW + j));
			sumV += *(pSrc[j*convW + i].subV) * (*(conv->values + i*convW + j));
		}
	}

	YUVFilePoint pDst = getPointXY(dst,x,y);
	*(pDst.subY) = sumY;
	*(pDst.subU) = sumU;
	*(pDst.subV) = sumV;
}