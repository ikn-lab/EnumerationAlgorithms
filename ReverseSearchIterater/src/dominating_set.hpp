#ifndef __DOMINATING_SET__
#define __DOMINATING_SET__
#include"graph.hpp"
#include"reverse_search.hpp"

class DominatingSetEnumerator:
  public ReverseSearch<Graph, std::vector<int> >{
public:
  Graph G;
  DominatingSetEnumerator(Graph _G);
private:
  std::vector<int>* Parent(std::vector<int>* X);
  std::vector<int>* Child(std::vector<int>* X, int k);
  bool isDominate(std::vector<int> X);
};

#endif // __DOMINATING_SET__
