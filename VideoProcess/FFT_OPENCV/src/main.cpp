#include <cv.h>
#include <highgui.h>
#include "../include/fft2d.h"
#include "../include/extend_opencv.h"

int
main(int argn,char **argv)
{
	
	IplImage *ipl = cvLoadImage(argv[1],IPL_DEPTH_64F);
	size_t W = ipl->width;
	size_t H = ipl->height;

	cvShowImage("src",ipl);
	
	cvWaitKey(-1);

	CvMat *re = cvCreateMat(W,H,CV_64FC1);
	CvMat *im = cvCreateMat(W,H,CV_64FC1);
	CvMat *amp = cvCreateMat(W,H,CV_64FC1);
	CvMat *fft = cvCreateMat(W,H,CV_64FC1);
	CvMat *ifft = cvCreateMat(W,H,CV_64FC1);
	
	convert_to_gray32(re,ipl);
	cvSetZero(im);

	fft2d(re,im,1);
	calculate_amplitude(re,im,amp);

	cvShowImage("fft_re",re);
	cvShowImage("fft_im",im);
	cvShowImage("fft_amp",amp);
	cvSaveImage("fft_re.jpg",re);
	cvSaveImage("fft_im.jpg",im);
	cvSaveImage("fft_amp.jpg",amp);
	cvWaitKey(-1);

	ifft2d(re,im,1);

	cvShowImage("ifft_re",re);
	cvShowImage("ifft_im",im);
	cvSaveImage("ifft_re.jpg",re);
	cvSaveImage("ifft_im.jpg",im);
	cvWaitKey(-1);
}
