SRCS	 = main.cpp Enum.cpp Graph.cpp
CXX		 = g++
CXXFLAGS = -Wall -std=c++11 -fdiagnostics-color -O3
EXE		 = EBG

EBG:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

clean:
	-rm -f EBG
