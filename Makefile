CXX=g++
CXXFLAGS=-std=c++11 -pthread -Wall -I include -g
SRC=merge.cc bilist.cc multithread-merge-sort.cc
OBJ=$(SRC:.cc=.o)
RUN=multithread-merge-sort
DEBUGER=gdb

build: $(SRC) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(RUN)

$(RUN): $(OBJ)

multithread-merge-sort.o: merge.o bilist.o

debug:
	$(DEBUGER) $(RUN)

.PHONY clean:
	rm *.o

