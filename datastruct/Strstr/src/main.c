#include "strstr.h"

int main(int argn , char **args) {
  char* str1 = "dfadafdaPARTICIPATE IN PARACHUTEfda";
  char* pattern = "PARTICIPATE IN PARACHUTE";
  printf("%s\n%s\n",str1,pattern);
  char* ret = NULL;
  ret = kmpSearch(str1,pattern);
  printf("%x ",ret);
  printf("%s", ret);
}
