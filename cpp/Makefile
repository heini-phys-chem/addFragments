XX = g++

OBDIR = /home/stefan/openbabel

INCLUDE = -I$(OBDIR)/include/openbabel-2.0/
LIBS = -L$(OBDIR)/lib
CXX_FLAGS = -std=c++11 -O3 -march=native -Wall
LINKER_FLAGS = -lopenbabel

all: main

main: opt_ff.cpp 
	$(CXX) $(INCLUDE) $(LIBS) $(CXX_FLAGS) opt_ff.cpp -o main $(LINKER_FLAGS)

clean:
	rm -rf main
	rm -rf *.o *.gch
