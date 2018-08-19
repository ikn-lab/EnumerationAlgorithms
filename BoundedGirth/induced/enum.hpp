#ifndef __ENUM__
#define __ENUM__
#include<vector>
#include"graph.hpp"
using bigint = long long int;

class EBG{
public:
  EBG(){};
  EBG(Graph H){init(H)};
  int Enumerate();
  init(Graph H);
private:
  Graph G;
  std::vector<std::vector<int> > dist;
  std::vector<int> result;
  List<int> solution, cand;
}

#endif // __ENUM__







