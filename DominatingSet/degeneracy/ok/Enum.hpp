#ifndef __ENUM__
#define __ENUM__
#include<memory>
#include<queue>
#include<stack>
#include<chrono>

#include"Graph.hpp"
#include"Digraph.hpp"
// #include"AddibleList.hpp"
#include"AddibleListNoUndo.hpp"
#include"basicDataStructure.hpp"
// #include"AddibleGraph.hpp"
// #include"AddibleDigraph.hpp"
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
  std::chrono::duration<double> time; 
private:
  Digraph FW;//For any v \in C(X), N(v)^{v<} \cap X
  Digraph C;//For any v \in C(X), N(v)^{<v} \cap C
  // Graph C;//  G[C(X)]
  Graph G;//Input Graph
  std::vector<AddibleListNoUndo<edge> > domList;// For any v \in X, N(v)^{<v} \cap (X \ C(X)). Otherewise, N(v) \cap (X \ C(X))
  std::vector<int> dominated; // the number of vertices such that |N(v)^{<v} \cap C|
  std::vector<int> counter; // counter[i] is the number of vertex i in diff[depth]
  std::vector<int> ord, reverse;
  std::vector<std::vector<int> > back;
  std::vector<bigint> result;
  bigint sum = 0;
  int depth = 0, degeneracy;
  std::vector<FixedQueue<int> > diff;//0: a tail, 1: a next of a tail
  List<int> solution, cand;
  void ordering(std::vector<std::vector<edge> > &H);
  int  updateCand(int v);
  void updateDomList(int v, int size);
};
#endif // __ENUM__
