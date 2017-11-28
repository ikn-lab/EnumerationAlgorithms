SRCS	 = main.cpp graph.cpp enum.cpp
CXX		 = g++-6
CXXFLAGS = -std=c++11 -O3
EXE		 = EST

ESP:$(SRCS)
	$(CXX)  $(SRCS) -o $@ $(CXXFLAGS)

debug:$(SRCS)
	$(CXX) $(CXXFLAGS) -D_GLIBCXX_DEBUG $(SRCS) -o $@

clean:
	-rm -f ESP
