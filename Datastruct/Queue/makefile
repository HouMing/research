CC=gcc
CFLAGS="-std=c99"

main : queue.o main.o 
	$(CC) $(CFLAGS) bin/main.o bin/queue.o -o bin/main

main.o : 
	$(CC) $(CFLAGS) src/main.c -c -o bin/main.o

queue.o: 
	$(CC) $(CFLAGS) src/queue.c -c -o bin/queue.o

clean:
	rm bin/ -r 

run:
	bin/main
