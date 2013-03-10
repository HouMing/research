CXX := g++

CXXFLAGS = -g -Wall -O0 -DFILE_OFFSET_BITS=64 
LDFLAGS  = -g -static 

TARGETS = 1000 1001

all: ${TARGETS}

${TARGETS}: %${TARGET:.o}: %.cpp
	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o $@ 

clean:
	rm -rf *.o ${TARGETS}
