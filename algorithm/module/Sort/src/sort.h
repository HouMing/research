#ifndef _ALGORITHM_SORT_SORT_H_
#define _ALGORITHM_SORT_SORT_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>


/*
 * 1. Exchanging Sort
 *
 * 1.1
 * Bubble Sort(冒泡排序, 泡沫排序, 气泡排序)
 *
 * #best n
 * #average n^2
 * #worst n^2
 * #memory 1
 * #stable yes
 *
 */
int bubbleSort(int *base, size_t n);

/*
 * 1.2
 * Cocktail Sort(鸡尾酒排序), Bidirectional Bubble Sort(定向冒泡排序),
 * Cocktail Shaker Sort(鸡尾酒搅拌排序), Shaker Sort(搅拌排序),
 * Ripple Sort(涟漪排序), Shuffle Sort(混洗排序),
 * Shuttle Sort(来回排序), Happy Hour Sort(快乐小时排序).
 *
 * #best n
 * #average n^2
 * #worst n^2
 * #memory 1
 * #stable yes
 *
 */
int cocktailSort(int *base, size_t n);

/*
 * 1.3
 * Odd-even Sort(奇偶排序),
 * Odd-even Transposition Sort(奇偶换位排序), Brick Sort(砖排序).
 *
 * #best ?
 * #average ?
 * #worst ?
 * #memery 1
 * #stable ?
 *
 */
int oddEvenSort(int *base, size_t n);

/*
 * 1.4
 * Comb Sort(梳排序).
 *
 * #best n
 * #average n*log(n)
 * #worst n^2
 * #memery 1
 * #stable no
 *
 */
int combSort(int *base, size_t n);

/*
 * 1.5
 * Quick Sort(快速排序),
 * Partition-exchange Sort(分区交换排序).
 *
 * #best ?
 * #average ?
 * #worst ?
 * #memery 1
 * #stable no
 *
 */
int quickSort(int *base, size_t n);

/*
 * 2 Selection Sort 
 *
 * 2.1 Selection Sort(选择排序)
 * #best n
 * #average n^2
 * #worst n^2
 * #memery 1
 * #stable no
 *
 */
int selectionSort(int *base, size_t n);

int heapSort(int *base, size_t n);

int insertionSort(int *base, size_t n);

int mergeSort(int *base, size_t n);

int bogoSort(int *base, size_t n);

#endif
