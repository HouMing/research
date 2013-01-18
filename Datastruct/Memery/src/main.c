#include "memery.h"

int main(int argn, char **args) {
  char move[10] = "0123456789";
  char cpy[10] = "0123456789";
  char *ret=NULL;
  printf("move:%s\n", move);
  printf("cpy:%s\n", cpy);
  ret = memmovei(move+3,move+0,6);
  printf("ret:%x move:%s\n", ret, move);
  ret = memcpyi(cpy+3,cpy+0,6);
  printf("ret:%x cpy:%s\n", ret, cpy);

  char move2[10] = "0123456789";
  char cpy2[10] = "0123456789";
 
  printf("move:%s\n", move2);
  printf("cpy:%s\n", cpy2);
  ret = memmovei(move2+0,move2+3,6);
  printf("ret:%x move:%s\n", ret, move2);
  ret = memcpyi(cpy2+0,cpy2+3,6);
  printf("ret:%x cpy:%s\n", ret, cpy2);
 
  return 0;
}
