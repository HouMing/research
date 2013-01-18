#ifndef _DATASTRUCT_ARRAYLISTLOCK_POINT_H_
#define _DATASTRUCT_ARRAYLISTLOCK_POINT_H_

typedef struct
{
  int x;
  int y;
}Point;

extern Point* createPoint ();
extern Point* createPoint (int x,int y);
extern Point* clonePoint (Point *pPoint);
extern int comparePoint (Point *a,Point *b);

#endif
