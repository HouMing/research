#include "sort.h"

///////////////////////////////////////
// Exchanging Sort
///////////////////////////////////////
void swap(int* a, int* b)
{
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

int bubbleSort(int *base, size_t n)
{
  size_t i = n - 1;
  size_t j = 0;

  for ( ; i != 1; --i) {
    for ( j = 0 ; j < i ; ++j ) {
      if (base[j] > base[j + 1]) {
        swap(base + j, base + j + 1);
      }
    }
  }
  return 0;
}

int cocktailSort(int *base, size_t n)
{
  size_t bottem = 0;
  size_t top = n - 1;
  bool swapper = true;
  while( swapper == true) {
    swapper = false;
    for (int i = bottem; i < top; ++i) {
      if ( base[i] > base[i + 1] ) {
        swap( base + i, base + i + 1);
        swapper = true;
      }
    }
    --top;
    for (int i = top; i > bottem ; --i) {
      if(base[i] < base[i - 1]) {
        swap( base + i, base -1 + i);
        swapper = true;
      }
    }
    ++bottem;
  }
  return 0;
}

int oddEvenSort(int *base, size_t n)
{
  size_t i;
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (i = 1; i < n -1; i += 2) {
     if (base[i] > base[i+1]) {
       sorted = false;
      swap( base + i, base + i + 1);
     }
    }
    for (i = 0; i < n -1; i += 2) {
      if (base[i] > base[i + 1]) {
        sorted = false;
        swap( base + i, base + i + 1);
      }
    }
  }
  return 0;
}

int newGap(size_t gap)
{
  gap = gap * 10 / 13;
  if (gap == 9 || gap == 11) {
    gap = 11;
  }
  if (gap < 1) {
    gap = 1;
  }
  return gap;
}

int combSort(int *base, size_t n) 
{
  size_t gap = n;
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    gap = newGap( gap);
    for (int i = 0; i < n - gap ; ++i) {
      if (base[i] > base[i + gap]) {
        swap( base + i, base + i + gap);
        sorted = false;
      }
    }
    if(gap == 1 && !sorted)
      break;
  }
  return 0;
}

//////////////////////////////////////////
// Selection Sort
//////////////////////////////////////////
int selectionSort(int *base, size_t n)
{
  size_t i;
  size_t j;
  size_t t;
  for ( i = 0 ; i < n ; ++i) {
    t = i;
    for ( j = i ; j < n ; ++j) {
      if ( base[j] < base[t]) {
        t = j;
      }
    } 
    swap( base + i, base + t);
  }
  return 0;
}

int insertionSort(int *base, size_t n);

int quickSort(int *base, size_t n);

int mergeSort(int *base, size_t n);

int heapSort(int *base, size_t n);

int bogoSort(int *base, size_t n);

