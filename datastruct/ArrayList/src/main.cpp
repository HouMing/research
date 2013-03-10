#include "common.h"
#include "main.h"
#include "array.h"

using namespace std;
using namespace xtool;

  int
main(int argn,char **args)
{
  cout<<endl<<"INFO:HELLO WORLD"<<endl;
  //新建一个大小为 10 XVector
  Vector _pV = Vector(10); 
  //赋值
  for(int i = 0 ; i < 10 ; ++i)
  {
    _pV.add(new Point(i,1));
  }
  while(_pV.size() > 0)
  {
    cout<<_pV.pop()<<endl;
  }
  //扩容
  _pV.expand(2);
  //赋值
  for(int i = 10 ; i < 20 ; ++i )
  {
    _pV.add(new Point(i,1));
  }
  //销毁
  _pV.clear();
  cout<<endl<<"INFO:ENDING WORLD"<<endl;
}
