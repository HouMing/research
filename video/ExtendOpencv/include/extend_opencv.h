#ifndef EXTEND_OPENCV
#define EXTEND_OPENCV

#include <stdio.h>
#include <cv.h>

#ifdef __cplusplus
extern "C"{
#endif

void convert_to_gray32(CvMat *dst,IplImage *ipl);

void convert_to_gray8(IplImage *ipl,CvMat *src);

#ifdef __cplusplus
};
#endif

#endif