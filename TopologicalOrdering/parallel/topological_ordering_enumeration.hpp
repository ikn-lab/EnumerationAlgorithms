#ifndef TOPOLOGICAL_ORDERING_ENUMERATION_HPP
#define TOPOLOGICAL_ORDERING_ENUMERATION_HPP
#include"reverse_search_parallel.hpp"
#include<vector>
class TopologicalOrderingEnumeration :
  public ReverseSearchParallel<vector<int> >{
  Graph G;
  //topological ordering
  vector<int> tp;
public:
  TopologicalOrderingEnumeration(){};
  TopologicalOrderingEnumeration(Graph &g);
  void init(Graph &g);
  void printPerm(vector<int> &v, FILE *rev);
  void print(vector<int> v);
  void printState();
  vector<int> LocalSearch(vector<int> v);
  vector<int> Adj(vector<int> v, int k);
};

#endif
