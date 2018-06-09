SRCS	= main.cpp graph.cpp dominating_set.cpp
CXX		= g++ -std=c++14 -Wall
CXXFLAGS = -O3
TDATA	= ../data/dag.dat
IDATA	= ../data/roadNet-CA-add.txt
EXE		= EDS

EDS:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

test:
	./$(EXE) $(TDATA) naive out_rev out_swap

exe:
	./$(EXE) $(IDATA)

clean:
	-rm -f EDS
