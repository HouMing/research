#include "../include/fft2d.h"
#include "../include/fft.h"
#include "cv.h"

void
calculate_amplitude(CvMat *re,CvMat *im,CvMat *amp)
{
	int W = amp->width;
	int H = amp->height;
	int i,j;
	for(i=0 ; i<H ; i++)
	{
		for( j=0 ; j<W ; j++)
		{
			amp->data.db[i*W+j] = sqrt(pow(re->data.db[i*W+j],2)+pow(im->data.db[i*W+j],2));
		}
	}
}

void
fft2d(CvMat *re,CvMat *im,int shift)
{
	unsigned int W = re->width;
	unsigned int H = re->height;

	double *cache_re = re->data.db;
	double *cache_im = im->data.db;

	_fft_2d(W,H,cache_re,cache_im,shift);
	
}

void
ifft2d(CvMat *re,CvMat *im,int shift)
{
	unsigned int W = re->width;
	unsigned int H = re->height;

	double *tmp_re = re->data.db;
	double *tmp_im = im->data.db;
	
	_ifft_2d(W,H,tmp_re,tmp_im,shift);
}
