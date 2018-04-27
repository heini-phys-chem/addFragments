XX = g++

OBDIR = /home/stefan/openbabel

INCLUDE = -I$(OBDIR)/include/openbabel-2.0/
LIBS = -L$(OBDIR)/lib
CXX_FLAGS = -std=c++11 -O3 -march=native -Wall
LINKER_FLAGS = -lopenbabel

all: main

main: src/exchangeFG.cpp 
	$(CXX) $(INCLUDE) $(LIBS) $(CXX_FLAGS) src/exchangeFG.cpp -o main $(LINKER_FLAGS)

main.o: main.o src/func.hpp src/utils.cpp
	$(CXX) $(INCLUDE) $(LIBS) $(CXX_FLAGS) -c src/exchangeFG.cpp $(LINKER_FLAGS

clean:
	rm -rf main
	rm -rf *.o *.gch
	rm -rf test.xyz
