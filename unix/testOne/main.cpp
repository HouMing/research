#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char** argv) 
{
  char name[1024];
  sprintf(name, "/proc/%d/cmdline\0", getpid());
  printf("%s\n", name);
  FILE *fl = fopen(name, "r");
  char *line = (char*)malloc(1024);
  size_t t = 1024;
  ssize_t read = 0;
  read = getline(&line, &t, fl);
  line[read] = 0;
  printf("file line:%d\n", read);
  while () {
    t = strcspn(line, "\0");
    line[t] = '\n';
  }
  printf("%s", line);
#if 1 
  while (1) {
    sleep(1);
  }
#endif
  return 0;
}
