#include "../include/NonlinearFilter.h"

void _sortSequence(u_int*,int);

void trans2SparseArray(u_int,u_int,ConvKernal*,YUVFile*,YUVFile*);
YUVFilePoint mediumSparseArray(YUVFilePoint**,int);


extern YUVFile*
medianFilter(YUVFile* src,ConvKernal* conv,YUVFile* dst)
{
	u_int srcW = src->width;
	u_int srcH = src->height;

	u_int convH = conv->height;
	u_int convW = conv->width;

	for(u_int j = 0; j< srcH; j++)
		for(u_int i = 0; i <srcW; i++)
		{
			if(i>srcW - convW/2 || j>srcH - convH/2)
				trans2SparseArray(i-convW/2,j-convH/2,conv,src,dst);
			else if(i < convW/2 || j < convH/2)
				trans2SparseArray(i+convW/2,j+convH/2,conv,src,dst);
			else
				trans2SparseArray(i,j,conv,src,dst);
		}
	return dst;
}

void
trans2SparseArray(u_int x,u_int y,ConvKernal* conv,YUVFile* src,YUVFile* dst)
{
	u_int convH = conv->height;
	u_int convW = conv->width;

	int lenArray = 0;
	for(u_int j = 0 ; j <convH ; j++)
	{
		for(u_int i = 0 ; i < convW ; i++)
		{
			if(conv->values[j*convW+i] != 0)
			{
				lenArray++;
			}
		}
	}

	YUVFilePoint **sparseArray = (YUVFilePoint **)malloc(sizeof(YUVFilePoint*)*lenArray);
	
	assert(sparseArray != NULL);
	for(int i = 0 ; i < lenArray;i++)
	{
		sparseArray[i] = (YUVFilePoint*)malloc(sizeof(YUVFilePoint));
		assert(sparseArray[i] != NULL);
		initYUVFilePoint(sparseArray[i]);
	}

	int srcH = src->height;
	int srcW = src->width;
	int keyArray = 0;

	for(u_int j = 0 ; j <convH ; j++)
	{
		for(u_int i = 0 ; i < convW ; i++)
		{
			if(conv->values[j*convW+i] != 0)
			{
				*(sparseArray[keyArray++]) = getPointXY(src,x-convW/2+i,y-convH/2+j);
			}
		}
	}
	setPointXY(dst,x,y,mediumSparseArray(sparseArray,lenArray));
	/* free */
	assert(sparseArray != NULL);
	for(int i = 0 ; i < lenArray;i++)
	{
		assert(sparseArray[i] != NULL);
		releaseYUVFilePoint(sparseArray[i]);
	}
}

YUVFilePoint
mediumSparseArray(YUVFilePoint **points,int len)
{
	YUVFilePoint max;
	initYUVFilePoint(&max);
	u_int *sequenceY = (u_int * )malloc(sizeof(u_int)*len);
	u_int *sequenceU = (u_int * )malloc(sizeof(u_int)*len);
	u_int *sequenceV = (u_int * )malloc(sizeof(u_int)*len);
	for(int j = 0 ; j < len  ; j++)
	{
		sequenceY[j] = points[j]->subY[0];
		sequenceU[j] = points[j]->subU[0];
		sequenceV[j] = points[j]->subV[0];
	}
	
	_sortSequence(sequenceY,len);
	_sortSequence(sequenceU,len);
	_sortSequence(sequenceV,len);

	*(max.subY) = sequenceY[len/2];
	*(max.subU) = sequenceU[len/2];
	*(max.subV) = sequenceV[len/2];
	
	free(sequenceY);
	free(sequenceU);
	free(sequenceV);

	return max;
}

void _sortSequence(u_int *sqnc,int len)
{
	u_int tmp;
	for(int i = 0 ; i < len ; i ++)
		for(int j = 0 ; j < len - 1 ; j++)
		{
			if(sqnc[j] > sqnc[j+1])
			{
				tmp = sqnc[j];
				sqnc[j] = sqnc[j+1];
				sqnc[j+1] = tmp;
			}
			else if(sqnc[j] == sqnc[j+1])
			{

			}
			else if(sqnc[j] < sqnc[j+1]) 
			{

			}
			else
			{
				fprintf(stderr,"there is something error in _sortSequence!");
			}
		}
}