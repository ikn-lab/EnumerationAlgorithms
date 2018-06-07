#ifndef NAIVE_HPP
#define NAIVE_HPP
#include<vector>
#include<stack>
#include<queue>
#include<unordered_set>
#include<iostream>
class edge{
public:
  edge():from(-1), to(-1), rev(-1),id(-1),
         next(1), prev(0){};         
  int from, to, rev, id, next, prev;
  edge(int f , int t, int r, int i, int n, int p){
    from = f;
    to = t;
    rev = r;
    id = i;
    next = n;
    prev = p;
  }
};

class EdgeList{
public:
  EdgeList(){}
  void push_back(edge e){s++,list.push_back(e);};
  void RemoveEdge(int id);
  int RestoreEdge();
  inline int size(){return s - 2;}
  inline int end(){return list.size();}
  inline edge& operator[](const int id){return list[id];}
private:
  int s = 0;
  std::vector<edge> list;
  std::stack<int> st;
};

typedef std::vector<EdgeList> Graph;
typedef std::pair<int, int> pii;
typedef std::pair<int, pii> piii;

int Normal(int x, EdgeList &addlist, Graph &g,
           std::stack<piii> &st, int &next);

int ManyChildren(int x, EdgeList &addlist, Graph &g,
                std::stack<piii> &st, int &next);

int EnumIMatch(EdgeList &addlist, Graph &g, int p);
#endif
