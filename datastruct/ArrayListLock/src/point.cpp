#include "common.h"
#include "point.h"

namespace xtool
{
  Point::Point()
  {
    x_m = 0;
    y_m = 0;
  }

  Point::Point(int x_,int y_)
  {
    x_m = x_;
    y_m = y_;
  }

  Point::~Point()
  {
    x_m = 0;
    y_m = 0;
  }

  Point* Point::clone()
  {
    return new Point(x_m,y_m);
  }

  bool Point::equal(const Point &b)
  {
    return (b.x_m == x_m) && (b.y_m == y_m);
  }

}
