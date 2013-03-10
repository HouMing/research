#include "configuration.h"
#ifndef CONV_KERNAL_HM
#define CONV_KERNAL_HM

typedef struct
{
	u_int width;
	u_int height;
	int* values;
}ConvKernal;

extern ConvKernal* initConvKernal(u_int width,u_int height,int* values);
extern ConvKernal* ReleaseConv(ConvKernal*);

#endif