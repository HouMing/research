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
					AscII \
					UglyClock \
					HM323 \
					HM323_2

all: ${TARGETS}

${TARGETS}: %${TARGET:.o}: %.cpp
	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o out/$@ 

clean:
	rm -rf *.o ${TARGETS} core* out/*
