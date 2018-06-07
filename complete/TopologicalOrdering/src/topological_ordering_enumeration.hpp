#ifndef TOPOLOGICAL_ORDERING_ENUMERATION_HPP
#define TOPOLOGICAL_ORDERING_ENUMERATION_HPP
#include"reverse_search.hpp"
#include<vector>
class TopologicalOrderingEnumeration :
  public ReverseSearch<vector<int> >{
  Graph G;
  //topological ordering
  vector<int> tp;
public:
  TopologicalOrderingEnumeration(){};
  TopologicalOrderingEnumeration(Graph &g);
  void init(Graph &g);
  void printPerm(vector<int> &v, FILE *rev);
  void printVertex(vector<int> &v, FILE *rev);
  void printState();
  vector<int> LocalSearch(vector<int> v);
  vector<int> Adj(vector<int> v, int k);
};

#endif
