SRCS	= main.cpp topological.cpp topological_ordering_enumeration.cpp enum_naive.cpp graph.cpp swap_and_stack.cpp
CXX		= g++ -std=c++11 -Wall -Wno-sign-compare
CXXFLAGS = -O3
TDATA	= ../data/dag.dat
IDATA	= ../data/roadNet-CA-add.txt
EXE		= enum

enum:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

test:
	./$(EXE) $(TDATA) naive out_rev out_swap

exe:
	./$(EXE) $(IDATA)

clean:
	-rm -f enum
