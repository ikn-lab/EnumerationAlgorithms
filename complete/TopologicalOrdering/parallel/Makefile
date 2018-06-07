SRCS	= main.cpp topological.cpp topological_ordering_enumeration.cpp enum_naive.cpp graph.cpp swap_and_stack.cpp
OBJS	= $(SRC:*.cpp=*.o)
CXX		= g++
CXXFLAGS = -std=c++11 -Wall -Wno-sign-compare -pthread -fdiagnostics-color -O3 -g
TDATA	= ../data/dag.dat
EXE		= enum

enum:$(SRCS)
	touch main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

.cpp.o:
	$(CXX) -c $<

test:
	./$(EXE) $(TDATA) naive out_rev out_swap

clean:
	-rm -f enum

main.o: reverse_search_parallel.hpp
main.o: reverse_search_praivate_parallel.hpp
