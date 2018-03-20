#ifndef GRAPH_HPP
#define GRAPH_HPP
#include<iostream>
#include<vector>

class Graph{
public:
  Graph(int _n = 0);
  void AddEdge(int to, int from);
  int size() const;
  std::vector<int> &operator[](int i);
  void printGraph();
  ~Graph(){}
private:
  int n;
  std::vector<std::vector<int> > g;
};

#endif
