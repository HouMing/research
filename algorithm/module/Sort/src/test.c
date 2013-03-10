#include "sort.h"

int main(int argc, char** argv)
{
  int base[100];
  srand( time(NULL));
  for(int i = 0; i < 100; ++i) {
    base[i] = rand()>>24;
    printf("%d ", base[i]);
  }
  printf("\n");

  combSort( base, 100);
  for(int i = 0; i < 100; ++i) {
    printf("%d ", base[i]);
  }
  printf("\n");
  return 0;
}
