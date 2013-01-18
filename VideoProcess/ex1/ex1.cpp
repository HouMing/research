// ex1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CIF2QCIF.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int main(int argc, char* argv[])
{	

	/* internal variables */
	FILE* cif_file = NULL;
	FILE* qcif_file = NULL;
	u_int8_t* cifA = NULL;
	u_int8_t* qcifY = NULL;
	u_int8_t* qcifU = NULL;
	u_int8_t* qcifV = NULL;
	int flag = atoi(argv[3]);
	/* begin process command line */
	/* point to the specified file names */
	/* open the CIF file */
	cif_file = fopen(argv[1],"rb");
	if(cif_file == NULL){
		printf("cann't read the cif file %s \n",argv[1]);
		system("pause");
		exit(0);
	}
	/* open the QCIF file in RAW */
	qcif_file = fopen(argv[2],"wb");
	if (qcif_file == NULL)
	{
		printf("cannot find qcif file %s \n",argv[2]);
		system("pause");
		exit(0);
	}
	/* get an input buffer for a frame */
	cifA = (u_int8_t*)malloc(SZ_CIF*sizeof(u_int8_t));
	/* get an output buffer for a frame */
	qcifY = (u_int8_t*)malloc(SZ_QCIF_Y*sizeof(u_int8_t));
	qcifU = (u_int8_t*)malloc(SZ_QCIF_U*sizeof(u_int8_t));
	qcifV = (u_int8_t*)malloc(SZ_QCIF_V*sizeof(u_int8_t));

	while(fread(cifA,1,SZ_CIF,cif_file)){
		clock_t start, finish;
		double   duration;
		/* 测量一个事件持续的时间*/
		start = clock();
		cif2qcif(cifA,qcifY,qcifU,qcifV,flag);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf( "%f seconds\n", duration );
		fwrite(qcifY,1,SZ_QCIF_Y,qcif_file);
		fwrite(qcifU,1,SZ_QCIF_U,qcif_file);
		fwrite(qcifV,1,SZ_QCIF_V,qcif_file);
	}
	free(cifA);free(qcifY);free(qcifU);free(qcifV);
/*
		if(!qcifBuf)
		qcifBuf = (u_int8_t*)malloc(SZ_QCIF*sizeof(u_int8_t));
		else{
			free(cifBuf);
			qcifBuf = (u_int8_t*)malloc(SZ_QCIF*sizeof(u_int8_t));
		}
		//Y 赋值
		const int x_dim = CIF_W;
		const int y_dim = CIF_H;
		for(int i = 0;i<y_dim;i++){
			for(int j =0;j<x_dim;j++){
				if(j%2 && i%2)
					*(qcifBuf+i*x_dim/2+j/2) = *(cifBuf+i*x_dim+j);
			}
		}
		//U 赋值
		int Ysize = CIF_W*CIF_H;
		int Ysize2 =  QCIF_W*QCIF_H;
		for(int i = 0;i<y_dim;i++){
			for(int j =0;j<x_dim;j++){
				if(j%2 && i%2)
					*(qcifBuf+Ysize2+i*x_dim/2+j/2) = *(cifBuf+Ysize+i*x_dim+j);
			}
		}
		int YUsize = CIF_W*CIF_H*5/4;
		int YUsize2 = QCIF_W*QCIF_H*5/4;
		for(int i = 0;i<CIF_H*CIF_W/4;i++){
			if(i%2){
				int t_ = i/2;
				*(qcifBuf+YUsize2+t_+YUsize) = *(cifBuf+YUsize + i + YUsize);
			}
		}
		fwrite(qcifBuf,1,SZ_QCIF,qcif_file);

		if(!cifBuf)
			cifBuf = (u_int8_t*)malloc(SZ_CIF*sizeof(u_int8_t));
		else{
			free(cifBuf);
			cifBuf = (u_int8_t*)malloc(SZ_CIF*sizeof(u_int8_t));
		}
	}
	
*/
	system("pause");
	return 0;
}

