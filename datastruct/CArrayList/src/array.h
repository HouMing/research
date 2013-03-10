#ifndef _DATASTRUCT_ARRAYLISTLOCK_ARRAY_H_
#define _DATASTRUCT_ARRAYLISTLOCK_ARRAY_H_

#include "common.h"

#define Object void

typedef struct{
  Object **phead;
  Object **ptail;  
  int capacity;
  Object **data;
}Vector;

Vector* createVector1(void);
Vector* createVector(int capacity);
int destroyVector (Vector *vector);

bool add (Vector *vector, Object *point);
int capacity (Vector *vector);
Object clear (Vector *vector);
bool expand ( Vector *vector, int times);
int indexOf ( Vector *vector, const Object *point);
bool isEmpty (Vector *vector);
int size (Vector *vector);
Object* popFront ( Vector *vector);
Object* popBack ( Vector *vector);
bool pushFront ( Vector *vector, Object *point);
bool pushBack ( Vector *vector, Object *point);
//    Stack funcion
Object* pop ( Vector *vector);
bool push (Vector *vector, Object *point);
Object* peek (Vector *vector);
Object** get(Vector *vector, int i);
bool set(Vector *vector, int i,Object *p_obj);

#endif
