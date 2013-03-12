#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

#ifndef __int64
#define __int64 long long
#else
#endif

int main()
{
  __int64 n;
  while(scanf("%Ld",&n)!=EOF)
  {
    __int64 s = 0;
    s = (n%2==0 ? (n>>1)*(n+1) : ((n+1)>>1)*n);
    printf("%Ld\n",s);
  }
  return 0;
}
