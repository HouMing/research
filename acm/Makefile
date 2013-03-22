CXX := g++

CXXFLAGS = -g -Wall -O0 -DFILE_OFFSET_BITS=64 -std=c++0x 
LDFLAGS  = -g -static 

TARGETS = 1000 \
          1001 \
          1002 \
          1_1_3 \
          Elevator \
          Financial \
          LeapYear \
					QuickSum \
					Pythagorean \
					GPA \
					AscII

all: ${TARGETS}

${TARGETS}: %${TARGET:.o}: %.cpp
	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o $@ 

clean:
	rm -rf *.o ${TARGETS} core*
