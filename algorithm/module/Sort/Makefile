CC=gcc
CFLAGS=-g -Wall -std="c99"

INC=include/
OBJ=obj/
BIN=bin/
SRC=src/

all:Test

Test:test.o sort.o
	$(CC) $(OBJ)test.o $(OBJ)sort.o -o $(BIN)$@ $(CFLAGS)

test.o:
	$(CC) $(SRC)test.c -c -o $(OBJ)$@ $(CFLAGS)

sort.o:
	$(CC) $(SRC)sort.c -c -o $(OBJ)$@ $(CFLAGS)

run:
	bin/Test

clean:
	rm $(BIN)* $(OBJ)*
