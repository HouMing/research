#include "../include/extend_opencv.h"

void
convert_to_gray32(CvMat *dst,IplImage *ipl)
{
	IplImage* gray8;
	if(ipl->nChannels == 1)
		gray8 = (IplImage*)cvClone(ipl);
	else
		cvCvtColor( ipl, gray8, CV_RGB2GRAY);
	cvConvertScale(ipl,dst,1.0/255.0,0);
}

void
convert_to_gray8(IplImage *ipl,CvMat* src)
{
	cvConvertScale(src,ipl,255.0,0);
}