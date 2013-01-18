CC=g++
CFLAGS=-g -Wall

vpath %.cpp cc/

all:AddBinary 3Sum

3Sum:3Sum.o
	bin/3Sum

AddBinary:AddBinary.o
	bin/AddBinary

AddBinary.o:
	$(CC) cc/AddBinary.cpp -o bin/AddBinary $(CFLAGS)

3Sum.o:
	$(CC) cc/3Sum.cpp -o bin/3Sum $(CFLAGS)

