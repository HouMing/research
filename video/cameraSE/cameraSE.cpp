
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <math.h>

#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

#define PI 3.14

void SEDraw( Mat& img,Mat& img2);
void WarpCam(Mat& grey);
void WarpCam2(Mat& grey);
void WarpCam3(Mat& grey);

int main( int argc, const char** argv )
{
    CvCapture* capture = 0;
	Mat frame,frameCopy,image;
    char* cap_name;
	
    capture = cvCaptureFromCAM(0);
    
	cvNamedWindow( "result", 1 );
	cvNamedWindow("src",1);
    if( capture)
    {
        for(;;)
        {
            IplImage* iplImg = cvQueryFrame(capture);
			frame = iplImg;
	
            if( frame.empty())
                break;

            if( iplImg->origin == IPL_ORIGIN_TL )
                frame.copyTo( frameCopy );
            else
                flip( frame, frameCopy, 0 );

			cv::imshow("src",frameCopy);
            SEDraw( frameCopy,frameCopy);       

            if( waitKey( 10 ) >= 0 )
                goto _cleanup_;
       }
	
        waitKey(0);
_cleanup_:
        cvReleaseCapture( &capture );
    }
    else
    {
        fprintf(stderr,"no camera detected!");
    }

    cvDestroyWindow("result");

    return 0;
}

void
SEDraw( Mat& img,Mat& img2)
{
	WarpCam3(img);
	cv::imshow("result",img);
	WarpCam2(img);
    cv::imshow( "sin", img );   
}

/*
	2D 透视变换
*/
void
WarpCam(Mat& grey)
{
	Mat old = grey.clone();
	CvMat Img_old = old;
	CvMat newp = grey;

	CvPoint2D32f src_point[4];
	CvPoint2D32f dst_point[4];

	//设定源观察面，即指定四边形的四个顶点
	src_point[0].x=0;            
	src_point[0].y=0;

	src_point[1].x=Img_old.width;                   
	src_point[1].y=0;

	src_point[2].x=0;
	src_point[2].y=Img_old.height;

	src_point[3].x=Img_old.width;
	src_point[3].y=Img_old.height;


	//设定目标观察面，即指定四边形的四个顶点
	dst_point[0].x=newp.width*0.10;            
	dst_point[0].y=newp.height*0.10;

	dst_point[1].x=0.9*newp.width;                   
	dst_point[1].y=0.3*newp.height;

	dst_point[2].x=newp.width*0.10;
	dst_point[2].y=newp.height*0.9;

	dst_point[3].x=newp.width*0.9;
	dst_point[3].y=newp.height*0.70;

	float newm[9];           
	CvMat newM = cvMat( 3, 3, CV_32F, newm );
	//获得透视转换矩阵
	cvWarpPerspectiveQMatrix(src_point,dst_point,&newM);
	//透视转换
	cvWarpPerspective(&Img_old,&newp,&newM,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0) );

}

/*
	变换2
*/
void
WarpCam2(Mat& grey)
{
	//
	int t_mark = clock()*1;

	Mat old = grey.clone();
	CvMat Img_old = old;
	CvMat newp = grey;

	CvPoint2D32f src_point[4];
	CvPoint2D32f dst_point[4];

	//设定源观察面，即指定四边形的四个顶点

	src_point[0].x=0;            
	src_point[0].y=0;

	src_point[1].x=Img_old.width-1;                   
	src_point[1].y=0;

	src_point[2].x=0;
	src_point[2].y=Img_old.height-1;

	src_point[3].x=Img_old.width-1;
	src_point[3].y=Img_old.height-1;

	
	int w = newp.width*0.4;

	//设定目标观察面，即指定四边形的四个顶点
	dst_point[0].x=newp.width*0.5 + w*sin(t_mark*PI);            
	dst_point[0].y=newp.height*0.1;

	dst_point[1].x=newp.width*0.5+w*sin(t_mark*PI + PI);                   
	dst_point[1].y=newp.height*0.1;

	dst_point[2].x=newp.width*0.5 + w*sin(t_mark*PI);
	dst_point[2].y=newp.height*0.9;

	dst_point[3].x=newp.width*0.5 + w*sin(t_mark*PI + PI);
	dst_point[3].y=newp.height*0.9;

	float newm[9];           
	CvMat newM = cvMat( 3, 3, CV_32F, newm );
	//获得透视转换矩阵
	cvWarpPerspectiveQMatrix(src_point,dst_point,&newM);
	//透视转换
	cvWarpPerspective(&Img_old,&newp,&newM,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0) );

}


void
WarpCam3(Mat& grey)
{
	//
	int t_mark = clock()*1;

	Mat old = grey.clone();
	CvMat Img_old = old;
	CvMat newp = grey;

	CvPoint2D32f src_point[4];
	CvPoint2D32f dst_point[4];

	//设定源观察面，即指定四边形的四个顶点

	src_point[0].x=0;            
	src_point[0].y=0;

	src_point[1].x=Img_old.width-1;                   
	src_point[1].y=0;

	src_point[2].x=0;
	src_point[2].y=Img_old.height-1;

	src_point[3].x=Img_old.width-1;
	src_point[3].y=Img_old.height-1;

	
	int w = newp.height*0.4;

	//设定目标观察面，即指定四边形的四个顶点
	dst_point[0].x=newp.width*0.1;            
	dst_point[0].y=newp.height*0.5+w*sin(t_mark*PI);

	dst_point[1].x=newp.width*0.9;                   
	dst_point[1].y=newp.height*0.5+w*sin(t_mark*PI);

	dst_point[2].x=newp.width*0.1;
	dst_point[2].y=newp.height*0.5+w*sin(t_mark*PI+PI);

	dst_point[3].x=newp.width*0.9 ;
	dst_point[3].y=newp.height*0.5+w*sin(t_mark*PI + PI);

	float newm[9];           
	CvMat newM = cvMat( 3, 3, CV_32F, newm );
	//获得透视转换矩阵
	cvWarpPerspectiveQMatrix(src_point,dst_point,&newM);
	//透视转换
	cvWarpPerspective(&Img_old,&newp,&newM,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS, cvScalarAll(0) );

}
