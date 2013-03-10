CC=g++
CFLAGS=

main : main.o array.o point.o
	${CC} ${CFLAGS} bin/main.o bin/array.o bin/point.o -o bin/main

main.o : src/main.cpp src/main.h src/common.h
	${CC} ${CFLAGS} -c src/main.cpp -o bin/main.o

array.o : src/array.cpp src/array.h src/common.h
	${CC} ${CFLAGS} -c src/array.cpp -o bin/array.o

point.o : src/point.h src/point.cpp src/common.h
	${CC} ${CFLAGS} -c src/point.cpp -o bin/point.o

clean:
	rm bin/main 

run:
	bin/main
