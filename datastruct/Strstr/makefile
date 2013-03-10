CC=gcc
CFLAGS="-std=c99" -Wall -g

main : strstr.o main.o 
	$(CC) $(CFLAGS) bin/main.o bin/strstr.o -o bin/main

main.o : 
	$(CC) $(CFLAGS) src/main.c -c -o bin/main.o

strstr.o: 
	$(CC) $(CFLAGS) src/strstr.c -c -o bin/strstr.o

clean:
	rm bin/ -r 

run:
	bin/main
