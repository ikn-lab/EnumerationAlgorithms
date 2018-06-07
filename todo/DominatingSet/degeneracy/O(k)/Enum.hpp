#ifndef __ENUM__
#define __ENUM__
#include<memory>
#include<queue>

#include"Graph.hpp"
#include"AddibleList.hpp"
#include"AddibleGraph.hpp"
#include"List.hpp"
using bigint = long long int;

class EDS{
public:
  EDS(std::vector<std::vector<edge> > _G);
  ~EDS(){};
  inline int GetDegeneracy(){return G.GetDegeneracy();}
  inline int size(){return G.size();}
  void Enumerate();
  void print();
private:
  Graph FW;//For any v \in C(X), N(v)^{v<} \cap X
  Graph C;//G[C(X)]
  Graph G;//Input Graph
  AddibleGraph domList;//For any v \in X, N(v)^{v<} \cap (X \ C(X)). Otherewise, N(v) \cap (X \ C(X))
  std::vector<int> dominated, counter;
  std::vector<bigint> result;
  int depth = 0;
  std::vector<std::queue<int> >diff;
  List<int> solution, cand;
  int updateCand(int v);
  int updateDomList(int v, int cnt);
  void restore(int cand_cnt, int dom_del);
};
#endif // __ENUM__
