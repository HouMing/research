#ifndef FFT_2D
#define FFT_2D

#define TRUE 1
#define FALSE 0

#include <math.h>
#include <stdio.h>
#include <memory.h>
#include <cv.h>

#ifdef __cplusplus
extern "C" {
#endif

void fft2d(CvMat *re,CvMat *im,int shift);

void ifft2d(CvMat *re,CvMat *im,int shift);

void calculate_amplitude(CvMat *re,CvMat *im,CvMat *amp);

#ifdef __cplusplus
};
#endif

#endif