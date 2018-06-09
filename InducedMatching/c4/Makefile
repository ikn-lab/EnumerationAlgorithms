SRCS	 = main.cpp Graph.cpp constant.cpp
CXX		 = g++-7
CXXFLAGS = -std=c++17 -O3 -fdiagnostics-color -I ~/boost_1_63_0 
EXE		 = EIM

EIM:$(SRCS)
	$(CXX)  $(SRCS) -o $@ $(CXXFLAGS)

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f EIM
