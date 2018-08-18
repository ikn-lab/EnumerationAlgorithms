SRCS	 = main.cpp d2.cpp
CXX		 = g++-6
CXXFLAGS = -std=c++14 -O3 -I ~/boost_1_63_0
EXE		 = EIM

EIM:$(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f EIM
