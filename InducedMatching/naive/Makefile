SRCS	 = main.cpp naive.cpp
# CXX		 = g++-6.0 -std=c++11 -fdiagnostics-color
CXX		 = g++ 
CXXFLAGS = -std=c++11 -O3 -I ~/boost_1_63_0
# CXXFLAGS = -std=c++11  -Wall -O3
RDATA    = ../gen/random.in
SDATA    = ../gen/noShortCycle.in
EXE		 = EIM

EIM:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

random:
	./$(EXE) $(RDATA)
noShortCycle:
	./$(EXE) $(SDATA)
clean:
	-rm -f EIM
