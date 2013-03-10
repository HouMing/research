#include "common.h"
#include "point.h"

Point* createPoint1() {
  Point *ret = (Point *)malloc(sizeof(Point));
  ret->x = 0;
  ret->y = 0;
  return ret;
}

Point* createPoint (int x,int y)
{
  Point *ret = (Point *)malloc(sizeof(Point));
  if(ret == NULL)
  {
    return NULL;
  }
  ret->x = x;
  ret->y = y;
  return ret;
}

Point* clonePoint (Point *pPoint)
{
 Point *ret = (Point *)malloc(sizeof(Point));
 if(ret == NULL)
 {
   return NULL;
 }
  ret->x = pPoint->x;
  ret->y = pPoint->y;
  return ret;
}

int comparePoint (Point *a,Point *b)
{
  int a_val = a->x * a->x + a->y * a->y;
  int b_val = b->x * b->x + b->y * b->y;
  if(a_val - b_val < 0)
    return -1;
  else if( a_val - b_val > 0)
    return 1;
  else
    return 0;
}

