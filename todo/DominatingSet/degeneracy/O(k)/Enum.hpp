#ifndef __ENUM__
#define __ENUM__
#include<memory>
#include<queue>
#include<stack>

#include"Graph.hpp"
#include"Digraph.hpp"
#include"AddibleList.hpp"
#include"AddibleGraph.hpp"
#include"AddibleDigraph.hpp"
#include"List.hpp"
using bigint = long long int;

class EDS{
public:
  EDS(std::vector<std::vector<edge> > H);
  ~EDS(){};
  inline int size(){return G.size();}
  inline int GetDegeneracy(){return degeneracy;};
  void Enumerate();
  void print();
  void printDomList();
  void printSolution();

  void printCand();
private:
  Digraph FW;//For any v \in C(X), N(v)^{v<} \cap X
  Graph C;//G[C(X)]
  Graph G;//Input Graph
  std::vector<AddibleList<edge> > domList;// For any v \in X, N(v)^{<v} \cap (X \ C(X)). Otherewise, N(v) \cap (X \ C(X))
  std::stack<pii> domLog;// vertex, plus or minus
  std::vector<int> dominated; // the number of vertices such that |N(v)^{<v} \cap C|
  std::vector<int> counter; // counter[i] is the number of vertex i in diff[depth]
  std::vector<int> ord, reverse;
  std::vector<bigint> result;
  int depth = 0, degeneracy;
  std::vector<std::queue<int> >diff;
  List<int> solution, cand;
  void ordering(std::vector<std::vector<edge> > &H);
  int  updateCand(int v);
  int  updateDomList(int v);
  void restore(int cand_cnt, int dom_del);
};
#endif // __ENUM__
