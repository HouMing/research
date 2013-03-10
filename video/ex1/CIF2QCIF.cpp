#include "stdafx.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "CIF2QCIF.h"

bool cif2qcif(u_int8_t* flame,u_int8_t* outY,u_int8_t* outU,u_int8_t* outV,int flag){
	switch(flag){
		case 1:{
			printf("flag=1	:未使用opencv库	:Natural Neighbor interpolation自然邻点插值法 \n");
			u_int8_t* sub_cifY = NULL;
			u_int8_t* sub_cifU = NULL;
			u_int8_t* sub_cifV = NULL;
			u_int8_t* cifY = NULL;
			u_int8_t* cifU = NULL;
			u_int8_t* cifV = NULL;
			u_int8_t* sub_qcifY = NULL;
			u_int8_t* sub_qcifU = NULL;
			u_int8_t* sub_qcifV = NULL;
			u_int8_t* qcifY = NULL;
			u_int8_t* qcifU = NULL;
			u_int8_t* qcifV = NULL;
			sub_qcifY = (u_int8_t*)malloc(SZ_QCIF_Y*sizeof(u_int8_t));
			sub_qcifU = (u_int8_t*)malloc(SZ_QCIF_U*sizeof(u_int8_t));
			sub_qcifV = (u_int8_t*)malloc(SZ_QCIF_V*sizeof(u_int8_t));
			qcifY = sub_qcifY;
			qcifU = sub_qcifU;
			qcifV = sub_qcifV;
			sub_cifY = (u_int8_t*)malloc(SZ_CIF_Y*sizeof(u_int8_t));
			sub_cifU = (u_int8_t*)malloc(SZ_CIF_U*sizeof(u_int8_t));
			sub_cifV = (u_int8_t*)malloc(SZ_CIF_V*sizeof(u_int8_t));
			memcpy(sub_cifY,flame,SZ_CIF_Y);
			memcpy(sub_cifU,flame+SZ_CIF_Y,SZ_CIF_U);
			memcpy(sub_cifV,flame+SZ_CIF_Y+SZ_CIF_U,SZ_CIF_V);
			for(int y_dim =0;y_dim<CIF_H;y_dim++){
				if(y_dim%2 == 0){	
					cifY = sub_cifY + CIF_W*y_dim;
					for(int x_dim=0;x_dim<CIF_W;x_dim++){
						if(x_dim%2 == 0){
							*(qcifY)= *(cifY);
							qcifY++;
						}
						cifY++;
					}
				}	
			}
			for(int y = 0;y<CIF_H/2;y++){
				if(y%2 == 0){
					cifU = sub_cifU + CIF_W/2*y/2;
					cifV = sub_cifV + CIF_W/2*y/2;
					for(int x = 0 ; x < CIF_W/2;x++){
						if(x%2 == 0){
							*(qcifU)= *(cifU);
							*(qcifV)= *(cifV);
							qcifU++;
							qcifV++;
						}
						cifU++;
						cifV++;
					}
				}
			}
			memcpy(outY,sub_qcifY,SZ_QCIF_Y);
			memcpy(outU,sub_qcifU,SZ_QCIF_U);
			memcpy(outV,sub_qcifV,SZ_QCIF_V);
			free(sub_qcifV);
			free(sub_qcifU);
			free(sub_qcifY);
			free(sub_cifV);
			free(sub_cifU);
			free(sub_cifY); 
			return TRUE;
		}
		case 2:{
			printf("flag=2	:未使用opencv库	:Bilinear interpolation双线性插值\n");
			u_int8_t* sub_cifY = NULL;
			u_int8_t* sub_cifU = NULL;
			u_int8_t* sub_cifV = NULL;
			u_int8_t* cifY1 = NULL;
			u_int8_t* cifU1 = NULL;
			u_int8_t* cifV1 = NULL;
			u_int8_t* cifY2 = NULL;
			u_int8_t* cifU2 = NULL;
			u_int8_t* cifV2 = NULL;
			u_int8_t* sub_qcifY = NULL;
			u_int8_t* sub_qcifU = NULL;
			u_int8_t* sub_qcifV = NULL;
			u_int8_t* qcifY = NULL;
			u_int8_t* qcifU = NULL;
			u_int8_t* qcifV = NULL;
			sub_qcifY = (u_int8_t*)malloc(SZ_QCIF_Y*sizeof(u_int8_t));
			sub_qcifU = (u_int8_t*)malloc(SZ_QCIF_U*sizeof(u_int8_t));
			sub_qcifV = (u_int8_t*)malloc(SZ_QCIF_V*sizeof(u_int8_t));
			qcifY = sub_qcifY;
			qcifU = sub_qcifU;
			qcifV = sub_qcifV;
			sub_cifY = (u_int8_t*)malloc(SZ_CIF_Y*sizeof(u_int8_t));
			sub_cifU = (u_int8_t*)malloc(SZ_CIF_U*sizeof(u_int8_t));
			sub_cifV = (u_int8_t*)malloc(SZ_CIF_V*sizeof(u_int8_t));
			memcpy(sub_cifY,flame,SZ_CIF_Y);
			memcpy(sub_cifU,flame+SZ_CIF_Y,SZ_CIF_U);
			memcpy(sub_cifV,flame+SZ_CIF_Y+SZ_CIF_U,SZ_CIF_V);
			for(int y =0;y<CIF_H;y+=2){
					cifY2 = sub_cifY + (y+1)*CIF_W;
					cifY1 = sub_cifY + y*CIF_W;
					for(int x=0;x<CIF_W;x=x+2){
							*(qcifY)= (*(cifY1) +*(cifY2) + *(cifY1+1) + *(cifY2+1)) /4;
							qcifY++;
							cifY1 +=2;
							cifY2 +=2;
					}	
			}
			for(int y =0;y<CIF_H/2;y+=2){
				cifU2 = sub_cifU + (y+1)*CIF_W/2;
				cifV2 = sub_cifV + (y+1)*CIF_W/2;
				cifU1 = sub_cifU + y*CIF_W/2;
				cifV1 = sub_cifV + y*CIF_W/2;
				for(int x=0;x<CIF_W/2;x=x+2){
					*qcifU= (*(cifU1) +*(cifU2) + *(cifU1+1)+*(cifU2+1))/4;
					*qcifV= (*(cifV1) +*(cifV2) + *(cifV1+1)+*(cifV2+1))/4;
					qcifU++;
					qcifV++;
					cifU1 +=2;
					cifU2 +=2;
					cifV1 +=2;
					cifV2 +=2;
				}	
			}
			memcpy(outY,sub_qcifY,SZ_QCIF_Y);
			memcpy(outU,sub_qcifU,SZ_QCIF_U);
			memcpy(outV,sub_qcifV,SZ_QCIF_V);
			free(sub_qcifV);
			free(sub_qcifU);
			free(sub_qcifY);
			free(sub_cifV);
			free(sub_cifU);
			free(sub_cifY); 
			return TRUE;
		}
		case 3:{
			//TODO 完成一个三次卷积法
			return FALSE;
		}
		case 10:{
			printf("flag=10	:使用opencv库	:Natural Neighbor interpolation自然邻点插值法	\n");
			IplImage* srcY = cvCreateImage(cvSize(CIF_W,CIF_H),IPL_DEPTH_8U,1);
			IplImage* dstY = cvCreateImage(cvSize(QCIF_W,QCIF_H),IPL_DEPTH_8U,1);
			IplImage* srcU = cvCreateImage(cvSize(CIF_W/2,CIF_H/2),IPL_DEPTH_8U,1);
			IplImage* dstU = cvCreateImage(cvSize(QCIF_W/2,QCIF_H/2),IPL_DEPTH_8U,1);
			IplImage* srcV =  cvCreateImage(cvSize(CIF_W/2,CIF_H/2),IPL_DEPTH_8U,1);
			IplImage* dstV = cvCreateImage(cvSize(QCIF_W/2,QCIF_H/2),IPL_DEPTH_8U,1);
			memcpy(srcY->imageData,flame,SZ_CIF_Y);
			memcpy(srcU->imageData,flame+SZ_CIF_Y,SZ_CIF_U);
			memcpy(srcV->imageData,flame+SZ_CIF_Y+SZ_CIF_U,SZ_CIF_V);
			for(int y=0;y<srcY->height;y++){
				if(y%2 == 0){
					for(int x = 0;x < srcY->width ; x++){
						if(x%2 ==0){
							CvScalar t = cvGet2D(srcY,y,x);
							cvSet2D(dstY,y/2,x/2,t);
						}
					}
				}
			}
			for(int y=0;y<srcU->height;y++){
				if(y%2 == 0){
					for(int x = 0;x < srcU->width ; x++){
						if(x%2 ==0){
							CvScalar t = cvGet2D(srcU,y,x);
							cvSet2D(dstU,y/2,x/2,t);
						}
					}
				}
			}
			for(int y=0;y<srcV->height;y++){
				if(y%2 == 0){
					for(int x = 0;x < srcV->width ; x++){
						if(x%2 ==0){
							CvScalar t = cvGet2D(srcV,y,x);
							cvSet2D(dstV,y/2,x/2,t);
						}
					}
				}
			}
			memcpy(outY,dstY->imageData,SZ_QCIF_Y);
			memcpy(outU,dstU->imageData,SZ_QCIF_U);
			memcpy(outV,dstV->imageData,SZ_QCIF_V);
			cvReleaseImageData(srcY);
			cvReleaseImageData(srcU);
			cvReleaseImageData(srcV);
			cvReleaseImageData(dstY);
			cvReleaseImageData(dstU);
			cvReleaseImageData(dstV);
			return TRUE;
				}
		case 11:{
			printf("flag=11 :使用opencv库 采用矩阵变换\n");
			/* mem malloc */
			IplImage* srcY = cvCreateImage(cvSize(CIF_W,CIF_H),IPL_DEPTH_8U,1);
			IplImage* dstY = cvCreateImage(cvSize(QCIF_W,QCIF_H),IPL_DEPTH_8U,1);
			IplImage* srcU = cvCreateImage(cvSize(CIF_W/2,CIF_H/2),IPL_DEPTH_8U,1);
			IplImage* dstU = cvCreateImage(cvSize(QCIF_W/2,QCIF_H/2),IPL_DEPTH_8U,1);
			IplImage* srcV = cvCreateImage(cvSize(CIF_W/2,CIF_H/2),IPL_DEPTH_8U,1);
			IplImage* dstV = cvCreateImage(cvSize(QCIF_W/2,QCIF_H/2),IPL_DEPTH_8U,1);
			/* mem init */
			memcpy(srcY->imageData,flame,SZ_CIF_Y);
			memcpy(srcU->imageData,flame+SZ_CIF_Y,SZ_CIF_U);
			memcpy(srcV->imageData,flame+SZ_CIF_Y+SZ_CIF_U,SZ_CIF_V);
			// Y
			CvMat* warp_matY = cvCreateMat(2,3,CV_32FC1);
			CvPoint2D32f srcTriY[3],dstTriY[3];
			srcTriY[0].x = 0;
			srcTriY[0].y = 0;
			srcTriY[1].x = srcY->width - 1;
			srcTriY[1].y = 0;
			srcTriY[2].x = 0;
			srcTriY[2].y = srcY->height -1;
			dstTriY[0].x = 0;
			dstTriY[0].y = 0;
			dstTriY[1].x = dstY->width - 1;
			dstTriY[1].y = 0;
			dstTriY[2].x = 0;
			dstTriY[2].y = dstY->height - 1;
			cvGetAffineTransform(srcTriY,dstTriY,warp_matY);
			cvWarpAffine(srcY,dstY,warp_matY);
			memcpy(outY,dstY->imageData,SZ_QCIF_Y);
			cvReleaseMat(&warp_matY);
			// U
			CvMat* warp_matU = cvCreateMat(2,3,CV_32FC1);
			CvPoint2D32f srcTriU[3],dstTriU[3];
			srcTriU[0].x = 0;
			srcTriU[0].y = 0;
			srcTriU[1].x = srcU->width - 1;
			srcTriU[1].y = 0;
			srcTriU[2].x = 0;
			srcTriU[2].y = srcU->height -1;
			dstTriU[0].x = 0;
			dstTriU[0].y = 0;
			dstTriU[1].x = dstU->width - 1;
			dstTriU[1].y = 0;
			dstTriU[2].x = 0;
			dstTriU[2].y = dstU->height - 1;
			cvGetAffineTransform(srcTriU,dstTriU,warp_matU);
			cvWarpAffine(srcU,dstU,warp_matU);
			memcpy(outU,dstU->imageData,SZ_QCIF_U);
			cvReleaseMat(&warp_matU);
			// V
			CvMat* warp_matV = cvCreateMat(2,3,CV_32FC1);
			CvPoint2D32f srcTriV[3],dstTriV[3];
			srcTriV[0].x = 0;
			srcTriV[0].y = 0;
			srcTriV[1].x = srcV->width - 1;
			srcTriV[1].y = 0;
			srcTriV[2].x = 0;
			srcTriV[2].y = srcV->height -1;
			dstTriV[0].x = 0;
			dstTriV[0].y = 0;
			dstTriV[1].x = dstV->width - 1;
			dstTriV[1].y = 0;
			dstTriV[2].x = 0;
			dstTriV[2].y = dstV->height - 1;
			cvGetAffineTransform(srcTriV,dstTriV,warp_matV);
			cvWarpAffine(srcV,dstV,warp_matV);
			cvReleaseMat(&warp_matV);
			memcpy(outV,dstV->imageData,SZ_QCIF_V);
			cvReleaseImageData(srcY);
			cvReleaseImageData(srcU);
			cvReleaseImageData(srcV);
			cvReleaseImageData(dstY);
			cvReleaseImageData(dstU);
			cvReleaseImageData(dstV);
			return TRUE;
				}
		default:{
			printf("flag error! \n");
			return FALSE;
				}
	}

}

/*

*/

/*
for(int i=0;i<SZ_QCIF_Y;i++){
*(dstY + i) = *(cifY + i*2);
}

for(int i=0;i<SZ_QCIF_U;i++){
*(dstU + i) = *(cifU + i*2);
}

for(int i=0;i<SZ_QCIF_V;i++){
*(dstV + i) = *(cifV + i*2);
}
*/