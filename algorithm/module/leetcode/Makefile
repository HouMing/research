CC=g++
CFLAGS=-g -Wall
SRC=c

vpath %.cpp $(SRC)/

all:AddBinary 3Sum 3SumClosest

3Sum:3Sum.o
	bin/3Sum

3SumClosest:3SumClosest.o
	bin/3SumClosest

AddBinary:AddBinary.o
	bin/AddBinary

AddBinary.o:
	$(CC) $(SRC)/AddBinary.cpp -o bin/AddBinary $(CFLAGS)

3Sum.o:
	$(CC) $(SRC)/3Sum.cpp -o bin/3Sum $(CFLAGS)

3SumClosest.o:
	$(CC) $(SRC)/3SumClosest.cpp -o bin/3SumClosest $(CFLAGS)

