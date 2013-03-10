#include "common.h"
#include "array.h"
#include "point.h"

using namespace std;

namespace xtool
{
  /* 
   *
   * public
   *
   */
  Vector::Vector()
  {
    if(XTOOL_DEBUG)
      cout<<"constructing a Vector!"<<endl<<"capacity is "<<XTOOL_DEFAULT_CAPACITY;
    data_m = new Point*[XTOOL_DEFAULT_CAPACITY];
    if(data_m == NULL)
    {
      //I haven't kenw what to do with the situation of OutOfMemery;
      exit(-1);
    }
    head_m = 0;
    tail_m = 0;
    capacity_m = XTOOL_DEFAULT_CAPACITY;
  }

  Vector::Vector(int capacity_)
  {
    if( XTOOL_DEBUG )
      cout<<"constructing a Vector!"<<endl<<"capacity is "<<capacity_;
    data_m = new Point*[capacity_];
    if( data_m == NULL )
    {
      exit(-1);
    }
    head_m = 0;
    tail_m = 0;
    capacity_m = capacity_;
  }

  Vector::~Vector()
  {
    if(data_m != NULL)
      delete [] data_m;
    data_m = NULL;
    capacity_m = 0;
    head_m = 0;
    tail_m = 0;
  }

  bool Vector::isEmpty()
  {
    return (head_m-tail_m) != 0;
  }

  int Vector::size()
  {
    return (head_m - tail_m + capacity_m) % capacity_m;
  }

  int Vector::capacity()
  {
    return capacity_m;
  }

  Point* Vector::popFront()
  {
    Point *ret = data_m[head_m];
    data_m[head_m] = NULL;
    head_m = (head_m + 1 + capacity_m)%capacity_m;
    return ret;
  }

  Point* Vector::popBack()
  {
    Point *ret = data_m[tail_m];
    data_m[tail_m] = NULL;
    tail_m = (tail_m -1+capacity_m)%capacity_m;
    return ret;
  }

  bool Vector::pushFront(Point *point_)
  {
    if(size() == capacity())
    {
      if(!expand(XTOOL_EXPAND_SPEED))
        return false;
    }
    int pos = (head_m-1+capacity_m)%capacity_m; 
    data_m[pos] = point_;
    head_m = pos;
    return true;
  }

  bool Vector::pushBack(Point *point_)
  {
    if(size() == capacity())
    {
      if(!expand(XTOOL_EXPAND_SPEED))
        return false;
    }
    int pos = (tail_m+1+capacity_m)%capacity_m;
    data_m[pos] = point_;
    tail_m = pos;
    return true;
  }

  bool Vector::add(Point *point_)
  {
    return pushBack(point_);
  }

  void Vector::clear()
  {

  }

  bool Vector::expand(int times_)
  {
    Point **tmp_ = new Point*[capacity_m * times_];

    if(tmp_ == NULL)
    {
      return false;
    }

    int tmp_size = size();
    for(int i = 0; i < tmp_size ; ++i)
    {
      tmp_[i] = get(i);
    }
    data_m = tmp_;
    capacity_m *= times_; 
    delete [] data_m;
    data_m = tmp_;
  }

  bool Vector::curtail(int times_)
  {
    if((capacity_m/times_) < size())
    {
      return false;
    }
    Point **tmp_ = new Point*[capacity_m / times_];

    if(tmp_ == NULL)
    {
      return false;
    }

    int tmp_size = size();
    for(int i = 0; i < tmp_size ; ++i)
    {
      tmp_[i] = get(i);
    }
    data_m = tmp_;
    capacity_m /= times_; 
    delete [] data_m;
    data_m = tmp_;

  }

  int Vector::indexOf(const Point *point_)
  {
    for(int i = 0 ; i < size() ; ++i)
    {
      if(point_ == get(i))
      {
        return i;
      }
      else
      {
        return -1;
      }
    } 
  }

  Point* Vector::pop()
  {
    return popFront();
  }

  bool Vector::push(Point *point_)
  {
    return pushFront(point_);
  }

  Point* Vector::peek()
  {
    return data_m[head_m];
  }

  Point* Vector::get(int index_)
  {
    if((head_m + index_ + capacity_m)%capacity_m > tail_m)
      return NULL;
    return data_m[(head_m + index_ + capacity_m)%capacity_m];
  }

  bool Vector::set(int index_, Point *point_)
  {
    if((head_m + index_ + capacity_m)%capacity_m > tail_m)
      return false;
    data_m[(head_m + index_ + capacity_m)%capacity_m] = point_;
  }
}
