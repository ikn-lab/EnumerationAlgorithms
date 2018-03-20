SRCS	 = main.cpp enum.cpp graph.cpp
CXX		 = g++-6
CXXFLAGS = -Wall -O3 -std=c++11 -fdiagnostics-color
EXE		 = ELG

ELG:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f ELG
