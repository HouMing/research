#include "queue.h"

Queue* init() {
  Queue *ret = (Queue *) malloc(sizeof(Queue));
  if(!ret) {
    exit(-1);
  }
  ret->count_ = 0;
  ret->head_ = 0;
  ret->tail_ = 0;
  ret->data_ = (int *) malloc(sizeof(int) * DEFAULT_SIZE);
  if(!ret->data_) {
    exit(-2);
  }
  return ret;
}

bool pop(Queue *queue, int *ret) {
  if(queue->count_ == 0) {
    return false;
  }
  queue->head_ = (queue->head_ + 1) % DEFAULT_SIZE;
  *ret = queue->data_[queue->head_] ;
  queue->count_--;
  return true;
}

bool push(Queue *queue, const int elem) {
  if(queue->count_ == DEFAULT_SIZE) {
    return false;
  }
  queue->tail_ = (queue->tail_ + 1) % DEFAULT_SIZE;
  queue->data_[queue->tail_] = elem;
  queue->count_++;
  return true;
}

bool top(Queue *queue, int *ret) {
  if(queue->count_ == 0) {
    return false;
  }
  *ret =  queue->data_[queue->head_];
  return true;
}

