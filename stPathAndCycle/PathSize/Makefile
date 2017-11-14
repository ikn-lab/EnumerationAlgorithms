SRCS	 = main.cpp graph.cpp enumPath.cpp
CXX		 = g++-6
# CXXFLAGS = -std=c++11 -O3 -I ~/boost_1_63_0
CXXFLAGS = -std=c++11 -O3
EXE		 = EP

EP:$(SRCS)
	$(CXX)  $(SRCS) -o $@ $(CXXFLAGS)

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f EP
