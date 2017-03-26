SRCS	 = main.cpp graph.cpp constant.cpp
CXX		 = g++-6
CXXFLAGS = -std=c++11 -O3 -I ~/boost_1_63_0
EXE		 = EIM

EIM:$(SRCS)
	$(CXX)  $(SRCS) -o $@ $(CXXFLAGS)

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f EIM
