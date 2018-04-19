SRCS	 = main.cpp graph.cpp enum.cpp
CXX		 = g++-7
CXXFLAGS = -std=c++11 -O3
EXE		 = EDS

EDS:$(SRCS)
	$(CXX)  $(SRCS) -o $@ $(CXXFLAGS)

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f EDS
