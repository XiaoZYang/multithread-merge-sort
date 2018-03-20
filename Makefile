CXX=g++
CXXFLAGS=-g -std=c++11 -pthread -Wall
SRC=merge.cc multithread-merge-sort.cc
OBJ=$(SRC:.cc=.o)
RUN=multithread-merge-sort
DEBUGER=gdb

build: $(SRC) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(RUN)

multithread-merge-sort.o: multithread-merge-sort.cc
merge.o: merge.cc

debug:
	$(DEBUGER) $(RUN)

.PHONY clean:
	rm *.o

