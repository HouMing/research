#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>

int HistogramBins = 256;
float HistogramRange1[2]={0,255};
float *HistogramRange[1]={&HistogramRange1[0]};

int main(int argn,char** argv)
{
	IplImage *Image1;
	CvHistogram *Histogram1;
	IplImage *HistogramImage1;

	Image1=cvLoadImage("lena.jpg",0);
	cvShowImage("src",Image1);

	Histogram1 = cvCreateHist(1,&HistogramBins,CV_HIST_ARRAY,HistogramRange);
	HistogramImage1 = cvCreateImage(cvSize(512,512),8,3);
	HistogramImage1->origin=1;

	cvCalcHist(&Image1,Histogram1);

	printf("type is : %d\n",Histogram1->type);
	printf("Low Bound is : %.f\n",Histogram1->thresh[0][0]);
	printf("Up Bound is : %.f\n",Histogram1->thresh[0][1]);
	printf("The Bins are : %d\n",((CvMatND *) Histogram1->bins)->dim[0].size);

	printf("\nGray Level Values:\n");
	for(int i=0;i<HistogramBins;i++)
	{
		printf("%.f \n",((CvMatND *) Histogram1->bins)->data.fl[i]);
		cvLine(HistogramImage1,cvPoint(i,0),cvPoint(i,(int)(cvQueryHistValue_1D(Histogram1,i)/10)),CV_RGB(127,127,127));
	}

	cvNamedWindow("Histogram",1);
	cvNamedWindow("Riverbank",1);
	cvShowImage("Riverbank",Image1);
	cvShowImage("Histogram",HistogramImage1);
	cvWaitKey(0);
}