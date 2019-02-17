#ifndef __ENUM__
#define __ENUM__
#include<vector>

#include"Graph.hpp"
#include"Element.hpp"


class EMDS{
public:
  EMDS(std::vecotr<std::vector<edge> > &H){init(H);};
  void init(Graph H);
  void Enumerate();
private:
  Graph G;
}

#endif // __ENUM__
