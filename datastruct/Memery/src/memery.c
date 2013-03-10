#include "memery.h"

void* memcpyi(void *dst, void *src, size_t n) {
  if( dst == NULL || src == NULL) {
    return NULL;
  }
  while( n > 0 ) {
    n--;
    *((char *)dst + n) = *((char *)src + n);
  }
  return dst;
}

void* memmovei(void *dst, void *src, size_t n) {
  if( dst == NULL || src == NULL) {
    return NULL;
  }
  if( ((char *)dst+n < (char *)src+n) && ((char*)dst+n >(char *)src) ) {
    int i = 0;
    while( n > i ) {
      *((char *)dst + i) = *((char *)src + i);
      i++;
    }
    return dst;
  } else {
    return memcpyi(dst,src,n);
  }
}

