SRCS	 = main.cpp Enum.cpp Graph.cpp Fraction.cpp
CXX		 = g++-7
CXXFLAGS = -Wall -std=c++17 -fdiagnostics-color -O3
EXE		 = EBG

EBG:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

clean:
	-rm -f EBG
