#include "strstr.h"

char *naiveSearch(const char *str1, const char *pattern) {
  while(*str1) {
    int s2 = 0;
    while(1) {
      if(pattern[s2] == str1[s2]) {
        s2++;
      }else{
        break;
      }
      if(pattern[s2] == '\0') {
        return str1;
      }
    }
    str1++;
  }
}

void preKmp( const char *pattern, int *overlay ,int pos) {
  if(pos == 1) {
    overlay[0] = -1;
    overlay[pos] = 0;
    return;
  }
  preKmp( pattern, overlay, pos-1 );
  int j = overlay[pos - 1];
  if(pattern[pos] == pattern[j+1] ) {
    overlay[pos] = j + 1;
  } else {
    overlay[pos] = 0;
  }
  return;
}

char *kmpSearch(const char *str,const char *pattern) {
  int i,j, *kmp_next;
  int len = strlen(str);
  int plen = strlen(pattern);
  /* Preprocessing */
  kmp_next = (int *)malloc(sizeof(int) * len);
  memset(kmp_next,0,sizeof(int)*len);
  preKmp(pattern, kmp_next, plen);
  /* Searching */
  i = j = 0;
  while(i+j < len) {
    if( pattern[i] == str[i+j] ) {
      if(i == plen - 1 ) {
        return str + j;
      }
      i++;
    } else {
      j = j - kmp_next[i] + i;
      if(kmp_next[i] > -1 ) {
        i = kmp_next[i];
      } else {
        i = 0;
      }
    } 
  }
  return NULL;
}
