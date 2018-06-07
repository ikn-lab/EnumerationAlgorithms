#ifndef GRAPH_HPP
#define GRAPH_HPP
#include<vector>
#include<cstdio>

#include"basicDataStructure.hpp"

class edge{
public:
  edge():to(-1), rev(-1), next(1), prev(-1){};
  edge(int t, int r, int n, int p){
    to   = t;
    rev  = r;
    next = n;
    prev = p;
  }
  int to, rev, next, prev;
};

class vertex{
public:
  vertex(){};
  vertex(int i, int d, int n, int p) {
    id   = i;
    deg  = d;
    next = n;
    prev = p;
  };
  void print(){printf("id:%3d deg:%3d next:%3d prev:%3d\n", id, deg, next, prev);}
  int id, deg, next, prev;
};
  
class EdgeList{
public:
  EdgeList(){}
  void push_back(edge e);
  void RemoveEdge(int id);
  void RestoreEdge();
  void print();
  inline int size(){return s - 2;}
  inline int end(){return 1;}
  inline edge& operator[](const int id){return elist[id];}
private:
  int s = 0, ss = 1;
  std::vector<edge> elist;
  FixedStack<int> st;
};


class Graph{
public:
  Graph(int n);
  void init(int n);
  void AddEdge(int from, int v);
  void RemoveVertex(int id);
  void RestoreVertex(int cnt = 1);
  inline int size(){return g.size();}
  void print();
  inline EdgeList& operator[](int id){return g[id];}
private:
  std::vector<EdgeList> g;
  FixedStack<int> st;
};

#endif
