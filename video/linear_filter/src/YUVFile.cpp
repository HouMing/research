#include "../include/YUVFile.h"
YUVFile*
loadYUVFile(char* fname,u_int width,u_int height,char* mod)
{
	YUVFile *handle = (YUVFile *)malloc(sizeof(YUVFile));
	FILE* pFile = fopen(fname,mod);
	handle->file = pFile;
	handle->width = width;
	handle->height = height;
	
	handle->subY = (u_int8_t *)malloc(sizeof(u_int8_t)*width*height);
	handle->subU = (u_int8_t *)malloc(sizeof(u_int8_t)*width*height);
	handle->subV = (u_int8_t *)malloc(sizeof(u_int8_t)*width*height);

	fread(handle->subY,sizeof(u_int8_t),width*height,handle->file);
	fread(handle->subU,sizeof(u_int8_t),width*height,handle->file);
	fread(handle->subV,sizeof(u_int8_t),width*height,handle->file);
	rewind(handle->file);
	return handle;
}

YUVFilePoint
getPointXY(YUVFile* yuvStream,u_int x, u_int y)
{
	YUVFilePoint pt;
	pt.x = x;
	pt.y = y;
	pt.subY = yuvStream->subY + y*yuvStream->width + x;
	pt.subU = yuvStream->subU + y*yuvStream->width + x;
	pt.subV = yuvStream->subV + y*yuvStream->width + x;
	return pt;
}

extern int
overWrite(YUVFile* yuvStream)
{
	FILE* tmp = yuvStream->file;
	if(tmp)
	{
	fwrite(yuvStream->subY,1,yuvStream->width*yuvStream->height,tmp);
	fwrite(yuvStream->subU,1,yuvStream->width*yuvStream->height,tmp);
	fwrite(yuvStream->subV,1,yuvStream->width*yuvStream->height,tmp);
	return 0;
	}
	else
	{
		return -1;
	}
}

YUVFile*
closeYUVFile(YUVFile* handle)
{
	if(!handle->file)
	{
		free(handle->file);
		handle->file = NULL;
	}
	if(!handle->subY)
	{
		free(handle->subY);
		handle->subY = NULL;
	}
	if(!handle->subU)
	{
		free(handle->subU);
		handle->subU = NULL;
	}if(!handle->subV)
	{
		free(handle->subV);
		handle->subV = NULL;
	}
	if(!handle)
	{
		free(handle);
		handle = NULL;
	}
	return handle;
}

void
setPointXY(YUVFile *yuvStream,u_int x,u_int y,YUVFilePoint value)
{
	u_int8_t yVal = *(value.subY);
	u_int8_t uVal = *(value.subU);
	u_int8_t vVal = *(value.subV);
	u_int yuvW = yuvStream->width;
	u_int yuvH = yuvStream->height;
	yuvStream->subY[y*yuvW+x] = yVal;
	yuvStream->subU[y*yuvW+x] = uVal;
	yuvStream->subV[y*yuvW+x] = vVal;

}

/* Point  */
YUVFilePoint*
initYUVFilePoint(YUVFilePoint* ptIn)
{
	if(ptIn != NULL)
	//ptIn = (YUVFilePoint *)malloc(sizeof(YUVFilePoint));
	;
	else
	return NULL;

	ptIn->subY = (u_int8_t *)malloc(sizeof(u_int8_t));
	if(ptIn->subY == NULL)
	{
		free(ptIn);
		return NULL;
	}
	ptIn->subU = (u_int8_t *)malloc(sizeof(u_int8_t));
	if(ptIn->subU == NULL)
	{
		free(ptIn->subY);
		free(ptIn);
		return NULL;
	}
	ptIn->subV = (u_int8_t *)malloc(sizeof(u_int8_t));
	if(ptIn->subV == NULL)
	{
		free(ptIn->subY);
		free(ptIn->subU);
		free(ptIn);
		return NULL;
	}

	return ptIn;
}

void
releaseYUVFilePoint(YUVFilePoint *pt)
{
	free(pt->subY);
	free(pt->subU);
	free(pt->subV);
	free(pt);
	return;
}

void
releaseYUVFilePoint(YUVFilePoint pt)
{
	free(pt.subY);
	free(pt.subU);
	free(pt.subV);
	free(&pt);
	return;
}