#ifndef __ENUM__
#define __ENUM__
#include<vector>
#include"Graph.hpp"


class ECIB{
public:
  ECIB(std::vector<std::vector<edge> > H){init(H);};
  void init(std::vector<std::vector<edge> > H);
  void Enumerate();
  List<int> solution;
private:
  Graph G;
  List<int> AWS, WS;
}

#endif // __ENUM__
