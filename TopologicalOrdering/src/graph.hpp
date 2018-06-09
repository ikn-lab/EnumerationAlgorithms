#ifndef GRAPH_HPP
#define GRAPH_HPP
#include<iostream>
#include<vector>
using namespace std;

// O(n^2) space
class Graph{
  int n;
  vector<vector<int> > adj_mat;
public:
  // -1 express input edge, 1 express output edge, 0 express no edge
  Graph(int _n = 0);
  bool isEdge(int to, int from);
  void resize(int _n);
  void AddEdge(int to, int from);
  int size() const;
  vector<int> &operator[](int i);
  Graph& operator=(Graph &G);
  void printGraph();
  ~Graph(){}
};

#endif
