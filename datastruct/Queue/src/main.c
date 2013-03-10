#include "common.h"
#include "queue.h"

int main(int argn, char **args) {
  printf("hello world!\n");
  Queue *queue = init();
  for(int i = 0 ; i < 1025 ; ++i) {
    printf("%d\n",i);
    push(queue,i);
  }
  for(int i = 0 ; i < 25 ; ++i) {
    int tmp = 0;
    bool ret = pop(queue,&tmp);
    if(ret)
    printf("[i,pop] %d:%d\n",i,tmp);
  }

  for(int i = 568 ; i < 1025 ; ++i) {
    printf("%d\n",i);
    push(queue,i);
  }
  printf("all:\n");
  int tmp = 0;
  int i = 0;
  while(pop(queue,&tmp)){
    printf("[i,pop] %d:%d\n",i,tmp);
    i++;
  }


}
