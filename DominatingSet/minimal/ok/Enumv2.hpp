#ifndef __ENUM__
#define __ENUM__
#include<memory>
#include<queue>
#include<stack>
#include<chrono>

#include"Graph.hpp"
#include"Digraph.hpp"
#include"DigraphNoUndo.hpp"
// #include"AddibleList.hpp"
#include"AddibleListNoUndo.hpp"
#include"basicDataStructure.hpp"
// #include"AddibleGraph.hpp"
// #include"AddibleDigraph.hpp"
#include"List.hpp"
#include"ListNoUndo.hpp"
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
  std::chrono::duration<double> time; 
private:
  Digraph FW;//For any v \in C(X), N(v)^{v<} \cap X
  DigraphNoUndo C;//For any v \in C(X), N(v)^{<v} \cap C(X)
  // Graph C;//  G[C(X)]
  Graph G;//Input Graph
  std::vector<AddibleListNoUndo<edge> > domList;// For any v \in X, N(v)^{<v} \cap (X \ C(X)). Otherewise, N(v) \cap (X \ C(X))
  std::vector<int> dominated; // the number of vertices such that |N(v)^{<v} \cap C|
  std::vector<int> counter; // counter[i] is the number of vertex i in diff[depth]
  std::vector<int> ord, reverse, backEdge;
  std::vector<int> C2FW, FW2C;
  std::vector<std::vector<int> > back; //0: a tail, 1: a next of a tail
  std::vector<bigint> result;
  int depth = 0, degeneracy;
  std::vector<FixedQueue<int> > diff;
  List<int> solution, cand, is_not_pv;
  void ordering(std::vector<std::vector<edge> > &H);
  int  updateCand(int v, int &npv);
  int updateDomList(int v, int size);
};
#endif // __ENUM__
