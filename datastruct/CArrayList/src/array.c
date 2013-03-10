#include "common.h"
#include "array.h"

Vector* createVector1(void) {
  Vector *ret = (Vector *)malloc(sizeof(Vector));
  ret->data = (Object **)malloc(sizeof(Object*)*(XTOOL_DEFAULT_CAPACITY+2));
  if(ret == NULL || ret->data == NULL) {
    free(ret->data);
    free(ret);
    return NULL; 
  }
  ret->phead = ret->data+0;
  ret->ptail = ret->data+1;
  ret->phead[0] = NULL;
  ret->ptail[0] = NULL;
  ret->capacity = XTOOL_DEFAULT_CAPACITY;
  return ret;
}

Vector* createVector (int capacity) {
  Vector *ret = (Vector *)malloc(sizeof(Vector));
  ret->data = (Object **)malloc(sizeof(Object*)*(capacity+2));
  if(ret == NULL || ret->data == NULL) {
    free(ret->data);
    free(ret);
    return NULL; 
  }
  ret->phead = ret->data+0;
  ret->ptail = ret->data+1;
  ret->phead[0] = NULL;
  ret->ptail[0] = NULL;
  ret->capacity = capacity;
  return ret;
}

int destroyVector (Vector *vector) {
  vector->phead[0] = NULL;
  vector->ptail[0] = NULL;
  vector->capacity = 0;
  if(vector != NULL || vector->data != NULL) {
    free(vector->data);
    free(vector);
  }
  return 0;
}

int size (Vector *vector) {
  if( vector->phead - vector->ptail == 0  ) {
    return -1;//这是不可能的，是个错误
  }
  if( vector->phead - vector->ptail < 0 ) {
    return vector->ptail - vector->phead - 1;
  }
  if( vector->phead - vector->ptail > 0 ) {
    return vector->ptail - vector->phead + vector->capacity + 1;
  }
  return -1;//这里是不可能到达的
}

bool expand ( Vector *vector, int times) {
  if(vector == NULL) {
    return false;
  }
  if(times <= 0) {
    return false;
  }
  Object **tmp_data = (Object **) malloc( sizeof(Object *) * (vector->capacity * times+2));
  if(vector->ptail == vector->phead) {
    abort();
  }
  if(vector->ptail - vector->phead > 0) {
    memcpy(vector->data,tmp_data,sizeof(Object*) * (vector->capacity+2) );
  }
  if(vector->ptail - vector->phead < 0) {
    int head_len = vector->data + vector->capacity + 2 - vector->phead;
    int tail_len = vector->ptail - vector->data + 1;
    memcpy(vector->phead,tmp_data,sizeof(Object*) * head_len);
    memcpy(vector->data,tmp_data,sizeof(Object*) * tail_len); 
  }
  return false;
}

int capacity (Vector *vector) {
  return vector->capacity;
}

bool isEmpty (Vector *vector) {
  if( size(vector) == 0 ) {
    return true;
  } else {
    return false;
  }
}

bool add (Vector *vector, Object *point) {
  return pushBack(vector,point);
}

Object clear (Vector *vector) {
  if(vector != NULL) {
    memset(vector->data,0,sizeof(Object *) * (vector->capacity));
  }
}

Object** get(Vector *vector, int i){
  if( vector == NULL || i < 0 || i >= size(vector) ) {
    return NULL;
  }
  int cap = capacity(vector);
  Object **ret = NULL;
  int head = vector->phead - vector->data;
  int offset = (head + i + 1)%(cap + 2); 
  return vector->data + offset;
}

bool set(Vector *vector, int i,Object *p_obj){
  if( vector == NULL || i < 0 || i >= size(vector) ) {
    return false;
  }
  int cap = capacity(vector);
  Object **ret = NULL;
  int head = vector->phead - vector->data;
  int offset = (head + i + 1)%(cap + 2);
  *(vector->data + offset) = p_obj ;
  return true;
}

//bool curtail ( Vector *vector, int times);

//front queue
Object* popFront ( Vector *vector){
  if(isEmpty(vector)){
    return NULL;
  }
  Object* ret = get(vector,0);
  set(vector,0,NULL);
  int head = vector->phead - vector->data;
  int offset = (head + 1 + 1)%(vector->capacity + 2);
  vector->phead = vector->data + offset;
  return ret;
}

bool pushBack ( Vector *vector, Object *point) {
  if(size(vector) == capacity(vector)) {
    if(!expand(vector,XTOOL_EXPAND_SPEED)) {
      return false;
    }
  }
  int tail = vector->ptail - vector->data;
  int offset = (tail + 1 + 1)%(vector->capacity + 2);
  vector->ptail[0] = point; 
  vector->ptail = vector->data + offset;
  vector->ptail[0] = NULL;
  return true;
}

//back queue
Object* popBack ( Vector *vector) {
  if(isEmpty(vector)){
    return NULL;
  }
  Object* ret = get(vector,size(vector) - 1);
  set(vector,size(vector) - 1, NULL);
  int tail = vector->ptail - vector->data;
  int offset = (tail + 1 + 1)%(vector->capacity + 2);
  vector->ptail = vector->data + offset;
  return ret;
}

bool pushFront ( Vector *vector, Object *point) {
  if(size(vector) == capacity(vector)) {
    if(!expand(vector, XTOOL_EXPAND_SPEED)) {
      return false;
    }
  }
  int tail = vector->ptail - vector->data;
  int offset = (tail + 1 + 1)%(vector->capacity + 2);
  vector->ptail[0] = point; 
  vector->ptail = vector->data + offset;
  vector->ptail[0] = NULL;
  return true;
}

int indexOf ( Vector *vector, const Object *point) {
  for(int i = 0 ; i < size(vector) ; ++i) {
    if(get(vector,i) == point) {
      return i;
    }
  }
  return -1;
}

//Stack funcion
Object* pop ( Vector *vector) {
  return popFront(vector);
}

bool push (Vector *vector, Object *point) {
 return pushFront(vector,point); 
}

Object* peek (Vector *vector) {
 return get(vector,0);
}


