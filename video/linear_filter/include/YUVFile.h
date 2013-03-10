#include "configuration.h"
#ifndef YUV_FILE_HM
#define YUV_FILE_HM

typedef struct
{
	u_int width;
	u_int height;
	u_int8_t *subY;
	u_int8_t *subU;
	u_int8_t *subV;
	FILE *file;
}YUVFile;

typedef struct
{
	u_int x;
	u_int y;
	u_int8_t *subY;
	u_int8_t *subU;
	u_int8_t *subV;
}YUVFilePoint;

/* File */
extern YUVFile* loadYUVFile(char *fName,u_int width,u_int height,char *mod);

extern YUVFilePoint getPointXY(YUVFile *yuvStream,u_int x, u_int y);

extern void setPointXY(YUVFile *yuvStream,u_int x,u_int y,YUVFilePoint value);

extern int overWrite(YUVFile *yuvStream);

extern YUVFile* closeYUVFile(YUVFile *yuvFile);
/* Point */
extern YUVFilePoint *initYUVFilePoint(YUVFilePoint*);
extern void releaseYUVFilePoint(YUVFilePoint*);

#endif