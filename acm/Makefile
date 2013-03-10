CXX ?= g++

CXXFLAGS = -g -Wall -O0 -DFILE_OFFSET_BITS=64 
LDFLAGS  = -g -static 

SOURCES = 1000.cpp

HEADERS =

OBJECTS = $(SOURCES:.cpp=.o)

TARGET := 1000

all: ${TARGET}

${TARGET}: ${OBJECTS}
	${CXX} $^ $(LDFLAGS) -o bin/$@

${OBJECTS}: ${HEADERS} Makefile

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o ${TARGET}
