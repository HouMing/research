#ifndef NOLINEAR_FILTER_HM
#define NOLINEAR_FILTER_HM

#include "configuration.h"
#include "ConvKernal.h"
#include "YUVFile.h"

extern YUVFile* medianFilter(YUVFile* src,ConvKernal* conv,YUVFile* dst);

#endif
