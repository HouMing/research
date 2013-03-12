CC=g++
CFLAGS="-std=c99"

CPPS:= HashTable.cpp Main.cpp

OBJS:= ${CPPS:.o}

all: main

main: ${OBJS} 
  $(CC) $(CFLAGS) $< -o $@ 

${OBJS}: %.o: %.cpp
  $(CC) $(CFLAGS) src/main.c -c -o bin/main.o

clean:
  rm bin/ -r 

