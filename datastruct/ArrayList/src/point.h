#ifndef _PROJECT_DATASTRUCT_ARRAYLIST_ELEM_H_
#define _PROJECT_DATASTRUCT_ARRAYLIST_ELEM_H_

#include "common.h"

namespace xtool 
{
  class Point
  {
    public:
      int x_m;
      int y_m;

      Point();
      Point(int x, int y);
      virtual ~Point();

      Point* clone();
      bool equal(const Point &b);

  };
}
#endif
