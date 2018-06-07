#ifndef GRAPH_HPP
#define GRAPH_HPP
#include<vector>
#include<stack>
#include<queue>
#include<iostream>
#include<cstdio>
typedef std::pair<int, int> pii;

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
  void push_back(edge e){s++, elist.push_back(e);};
  void RemoveEdge(int id);
  void RestoreEdge();
  void print();
  inline int size(){return s - 2;}
  inline int end(){return elist.size() - 1;}
  inline edge& operator[](const int id){return elist[id];}
private:
  int s = 0;
  std::vector<edge> elist;
  std::stack<int> st;
};


class Graph{
public:
  Graph(int n){g.resize(n), dist.resize(n, 1e9);};
  Graph(){};
  void MakeVlist();
  void AddEdge(int from, edge e);
  void RemoveVertex(int id);
  void RestoreVertex();
  inline vertex MaximumDeg(){return vlist[vlist[deg_boundary[deg]].next];}
  inline int size(){return g.size();}
  void print();
  inline EdgeList& operator[](int id){return g[id];}
  std::vector<int> dist;
  std::stack<int> log, vs;
private:
  int deg;  
  std::vector<EdgeList> g;
  std::vector<int> deg_boundary, id_to_pos;
  std::vector<vertex> vlist;//このデータ構造をバケットキューというらしい
  std::stack<int> st;
  inline void Detach(int id);
  inline void Insert(int id);
};

#endif
