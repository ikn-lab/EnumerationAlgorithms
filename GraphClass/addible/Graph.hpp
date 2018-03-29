#ifndef __GRAPH__
#define __GRAPH__
#include<vector>

#include"AddibleList.hpp"
#include"Element.hpp"

using pii = std::pair<int, int>;

class Graph{
public:
  Graph(std::vector<std::vector<edge> > _G);
  int size(){return n;}
  AddibleList<edge>& operator[](const int id){return G[id];}
  void RemoveEdge(int id);
  void AddEdge(int id);
  void RemoveVertex(int id);
  void AddVertex(int id);
  void undo();
  int GetNext(int id){return vlist.GetNext(id);};
  int GetPrev(int id){return vlist.GetPrev(id);};
  void print();
  // int begin(){return G[n]}
private:
  int n, m;
  std::vector<AddibleList<edge> > G;
  AddibleList<int> vlist;
  AddibleList<edge> elist;
  std::vector<pii> edge2vertex;//u: first, v:second
  int head = -10;
  std::vector<int> next;
};

Graph::Graph(std::vector<std::vector<edge> > _G) {
  n = _G.size();
  G.resize(n);
  std::vector<int> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = i;
  vlist.init(tmp);
  for (int i = 0; i < n; i++) m += _G[i].size();
  m /= 2;
  std::vector<edge> ve(m);
  edge2vertex.resize(m, pii(-1, -2));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < _G[i].size(); j++) {
      if(_G[i][j].u != i)std::swap(_G[i][j].u, _G[i][j].v);
      int id = _G[i][j].id;
      ve[id] = _G[i][j];
      edge2vertex[id].first = edge2vertex[id].second;
      edge2vertex[id].second = j;
    }
  }
  elist.init(ve);
  for (int i = 0; i < n; i++)G[i].init(_G[i]);
  next.resize(2*(n + m), -1);
}

void Graph::RemoveEdge(int id){
  int u = elist[id].u, v = elist[id].v;
  if(u > v)std::swap(u, v);
  G[u].remove(edge2vertex[id].first);
  G[v].remove(edge2vertex[id].second);
  elist.remove(id);
  next[id + m + n] = head;
  head = id + m + n;
}

void Graph::AddEdge(int id){
  int u = elist[id].u, v = elist[id].v;
  if(u > v)std::swap(u, v);
  G[u].add(edge2vertex[id].first);
  G[v].add(edge2vertex[id].second);
  elist.add(id);
  next[id] = head;
  head = id;
}


void Graph::RemoveVertex(int id){
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int u = G[id][i].u ,v = G[id][i].v;
    int eid = G[id][i].id;
    if(u > v)G[v].remove(edge2vertex[eid].second);
    else G[v].remove(edge2vertex[eid].first);
    elist.remove(eid);
  }
  vlist.remove(id);
  next[id + 2*m + n] = head;
  head = id + 2*m + n;
}

void Graph::AddVertex(int id){
  for (int i = 0; i != G[id].end(); i++) {
    int u = G[id][i].u ,v = G[id][i].v, eid = G[id][i].id;
    if(next[v + 2*m + n] == -1 or next[v + m] != -1)continue;
    if(u > v)std::swap(u, v);
    G[u].add(edge2vertex[eid].first);
    G[v].add(edge2vertex[eid].second);
    elist.add(eid);
  }
  vlist.add(id);
  next[id + 2*m + n] = head;
  head = id + 2*m + n;
}


void Graph::undo(){
  int u, v, id;
  if(2*m + n <= head){//undo add vertex
    id = head - 2*m - n;
    int cnt = 0;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      G[G[id][i].v].undo();
      elist.undo();
    }
    for (int i = 0; i < cnt; i++) G[id].undo();
    vlist.undo();
  }else if(m + n <= head){//undo add edge
    id = head - m - n;
    G[elist[id].u].undo();
    G[elist[id].v].undo();
    elist.undo();
  }else if(m <= head){
    id = head - m;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      u = G[id][i].u, v = G[id][i].v;
      if(u == id)G[v].undo();
      else G[u].undo();
      elist.undo();
    }
    vlist.undo();
  }else{
    u = elist[head].u, v = elist[head].v;
    G[u].undo();
    G[v].undo();
    elist.undo();
  }
  int tmp = head;
  head = next[head];
  next[tmp] = -1;
}

void Graph::print(){
  std::cout << "print start. " << std::endl;
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << "i:" << i << std::endl;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].u << " "  << G[i][j].v << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << "print end. " << std::endl;
}

#endif // __GRAPH__
