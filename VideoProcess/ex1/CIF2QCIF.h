#include "stdafx.h"

#define SZ_CIF (352*288*3/2)
#define SZ_CIF_Y (352*288)
#define SZ_CIF_U (352*288/4)
#define SZ_CIF_V (352*288/4)
#define CIF_W 352
#define CIF_H 288


#define SZ_QCIF (176*144*3/2)
#define SZ_QCIF_Y (176*144)
#define SZ_QCIF_U (176*144/4)
#define SZ_QCIF_V (176*144/4)
#define QCIF_W 176
#define QCIF_H 144

extern bool cif2qcif(u_int8_t* flame,u_int8_t* dstY,u_int8_t* dstU,u_int8_t* dstV,int flag);