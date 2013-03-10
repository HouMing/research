#ifndef _PROJECT_DATASTRUCT_QUEUE_H_
#define _PROJECT_DATASTRUCT_QUEUE_H_

#include "common.h"

typedef struct {
  int count_;
  int tail_;
  int head_;
  int *data_;
}Queue; 

Queue* init();
bool pop(Queue *queue, int *ret);
bool push(Queue *queue, const int elem);
bool top(Queue *queue, int *ret);

#endif
