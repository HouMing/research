CC=gcc
CFLAGS="-std=c99" -Wall -g

main : memery.o main.o 
	$(CC) $(CFLAGS) bin/main.o bin/memery.o -o bin/main

main.o : 
	$(CC) $(CFLAGS) src/main.c -c -o bin/main.o

memery.o: 
	$(CC) $(CFLAGS) src/memery.c -c -o bin/memery.o

clean:
	rm bin/ -r 

run:
	bin/main
