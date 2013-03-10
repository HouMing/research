#ifndef _PROJECT_DATASTRUCT_ARRAYLIST_ARRAY_H_
#define _PROJECT_DATASTRUCT_ARRAYLIST_ARRAY_H_ 

#include "common.h"
#include "point.h"

namespace xtool
{
  class Vector
  {
    public:
      Vector();
      Vector(int capacity_);
      virtual ~Vector();

      bool add(Point *point_);
      int capacity();
      void clear();
      bool expand(int times_);
      bool curtail(int times_);
      int indexOf(const Point *point_);
      bool isEmpty();
      int size();
      Point* popFront();
      Point* popBack();
      bool pushFront(Point *point_);
      bool pushBack(Point *point_);
//    Stack funcion
      Point* pop();
      bool push(Point *point_);
      Point* peek();
    protected:
      int head_m;
      int tail_m;
      int capacity_m;
      Point **data_m;

//      void regulate();
      Point* get(int index_);
      bool set(int index_, Point *point_);

  };
}
#endif
