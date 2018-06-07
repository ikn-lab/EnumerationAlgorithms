#ifndef NAIVE_HPP
#define NAIVE_HPP
#include<vector>
#include<iostream>

#include"basicDataStructure.hpp"
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int bigint;
typedef std::pair<int, int> pii;

class edge{
public:
  edge():from(-1), to(-1), rev(-1),
         id(-1), next(1), prev(0){};
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
  void push_back(edge e){list.push_back(e),st.resize(list.size());};
  void RemoveEdge(int id);
  void RestoreEdge();
  inline int size(){return list.size();}
  inline edge& operator[](const int id){return list[id];}
private:
  std::vector<edge> list;
  FixedStack<int> st;
};

class Graph{
public:
  Graph(){};
  Graph(int n){g.resize(n);};
  int size(){return g.size();};
  EdgeList& operator[](const int id){return g[id];};
  std::vector<int> dist;
private:
  std::vector<EdgeList> g;
};

typedef std::pair<int, int> pii;

bigint EIMMain(EdgeList &addlist, Graph &g, std::vector<bigint> &ans);
#endif
