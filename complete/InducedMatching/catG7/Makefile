SRCS	 = main.cpp constant.cpp
CXX		 = g++-7
CXXFLAGS = -Wall -O3 -std=c++11 -fdiagnostics-color
EXE		 = EIM

EIM:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f EIM
