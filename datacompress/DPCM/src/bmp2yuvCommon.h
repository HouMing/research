#pragma once


struct tagPCMImage
{
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwSize;
	BYTE* pbPCM;
	int* pbPredict;
	BYTE* pbBack;
};

typedef tagPCMImage PCMImage;

struct tagBMPImage
{
	BITMAPINFOHEADER* pBMIH;
	PVOID  pvColorTable;			//ptr to DIB palette
	int nByteWidth;					//width of image (incl. zeropadding)
	DWORD dwSizeImage;				//size of image (incl. zeropadding)
	LPBYTE pbImage;					//address of DIB bits
};

typedef tagBMPImage BMPImage;

struct tagYUVImage
{
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwSizeY;
	DWORD dwSizeU;
	DWORD dwSizeV;
	BYTE* Y;
	BYTE* U;
	BYTE* V;
};

typedef tagYUVImage YUVImage;
