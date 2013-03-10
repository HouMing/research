#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#define P_INFO printf("chld %u, self %u, father %u \n", pid, getpid(), getppid())

void err_sys (const char* val)
{
  fprintf(stdout, val);
  return;
}

int func (void)
{
  pid_t pid = -1;
  pid = vfork();
  if (pid < 0) {
    err_sys("vfork failed\n");
  }
  if ( pid == 0) {
    printf("child 2\n");
    P_INFO;
    return pid;
  }
  if (pid > 0) {
    printf("father 1 func\n");
    P_INFO;    
    return pid;
  }
}

void funf (void)
{
  pid_t pid = getpgrp();
  P_INFO;
  return;
}

int main (int argc, char** argv) 
{
  pid_t pid = getpgrp();
  printf("father 1\n");
  func();
  printf("father 1, out func to funf\n");
  funf();
  printf("father 1, out funf to exit\n");
  P_INFO;
  return 0;
}
