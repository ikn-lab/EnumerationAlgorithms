#ifndef __ENUM__
#define __ENUM__
#include<memory>

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
  Graph FW;//for any v \in C(X), N(v)^{v<} \cap X
  Graph C;//G[C(X)]
  Graph G;//Input Graph
  AddibleGraph domList;// N(v)^{v<} \cap (X \ C(X)) or N(v) \cap (X \ C(X))
  std::unique_ptr<int[]> dominated;
  int depth = 0;
  AddibleList<int> diff;
  List<int> solution, cand;
  std::unique_ptr<bigint[]> result;
  int updateCand(int v);
  int updateDomList(int v);
  void restore(int cand_cnt, int dom_del);
};
#endif // __ENUM__
