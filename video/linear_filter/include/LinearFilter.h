#ifndef LINEAR_FILTER_HM
#define LINEAR_FILTER_HM

#include "configuration.h"
#include "ConvKernal.h"
#include "YUVFile.h"

extern YUVFile* linearFilter(YUVFile* src,ConvKernal* conv,YUVFile* dst);
extern YUVFile* LaplaceFilter(YUVFile* src,ConvKernal* conv,YUVFile* dst);

#endif
