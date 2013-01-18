#include "../include/ConvKernal.h"

ConvKernal*
initConvKernal(u_int width,u_int height,int* values)
{
	ConvKernal* handle = (ConvKernal *)malloc(sizeof(ConvKernal));
	handle->width = width;
	handle->height = height;
	handle->values = (int *)malloc(sizeof(int) * width * height);
	for(u_int y = 0 ; y < height ; y++)
	{
		for(u_int x = 0 ; x < width ; x++)
		{
			*(handle->values + y * width + x) = *(values + y * width + x);
		}
	}
	return handle;
}

ConvKernal*
ReleaseConv(ConvKernal* handle)
{
	if(handle != NULL)
	{
	free(handle->values);
	free(handle);
	return NULL;
	}
	else
	{
	return NULL;
	}
}