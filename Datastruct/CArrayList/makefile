CC=gcc
CFLAGS="-std=c99"

main : array.o point.o main.o 
	$(CC) $(CFLAGS) bin/main.o bin/array.o bin/point.o -o bin/main

main.o : src/main.c src/main.h src/common.h
	$(CC) $(CFLAGS) src/main.c -c -o bin/main.o

array.o: src/array.c src/array.h src/common.h
	$(CC) $(CFLAGS) src/array.c -c -o bin/array.o

point.o: src/point.h src/point.c src/common.h
	$(CC) $(CFLAGS) src/point.c -c -o bin/point.o

clean:
	rm bin/ -r 

run:
	bin/main
