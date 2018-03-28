#ifndef __GRAPH__
#define __GRAPH__
#include<vector>

#include"List.hpp"
#include"Element.hpp"

using pii = std::pair<int, int>;

class Graph{
public:
  Graph(std::vector<std::vector<edge> > _G);
  int size(){return n;}
  List<edge>& operator[](const int id){return G[id];}
  void EdgeRemove(int id);
  void VertexRemove(int id);
  void undo();
  int GetNext(int id){return vlist.GetNext(id);};
  int GetPrev(int id){return vlist.GetPrev(id);};
  void print();
  // int begin(){return G[n]}
private:
  int n, m;
  std::vector<List<edge> > G;
  List<int> vlist;
  List<edge> elist;
  std::vector<pii> edge2vertex;//u: first, v:second
  int head;
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
      int id = _G[i][j].id;
      ve[id] = _G[i][j];
      if(edge2vertex[id].first == -1){
        edge2vertex[id].first = j;
      }else{
        edge2vertex[id].second = j;        
      }
    }
  }
  elist.init(ve);
  for (int i = 0; i < n; i++) G[i].init(_G[i]);
  next.resize(n + m);
}

void Graph::EdgeRemove(int id){
  int u = elist[id].u, v = elist[id].v;
  G[u].remove(edge2vertex[id].first);
  G[v].remove(edge2vertex[id].second);
  elist.remove(id);
  next[id] = head;
  head = id;
}

void Graph::VertexRemove(int id){
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int u = G[id][i].u ,v = G[id][i].v;
    int eid = G[id][i].id;
    if(u == id)G[v].remove(edge2vertex[eid].second);
    else G[u].remove(edge2vertex[eid].first);
    elist.remove(eid);
  }
  vlist.remove(id);
  next[id] = head;
  head = id + m;
}

void Graph::undo(){
  int u, v;
  if(head >= m){
    int id = head - m;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      u = G[id][i].u, v = G[id][i].v;
      if(u == id)G[v].undo();
      else G[u].undo();
      elist.undo();
    }
  }else{
    u = elist[head].u, v = elist[head].v;
    G[u].undo();
    G[v].undo();
    elist.undo();
  }
  head = next[head];
}

void Graph::print(){
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << "i:" << i << std::endl;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].u << " "  << G[i][j].v << std::endl;
    }
    std::cout << std::endl;
  }
}

#endif // __GRAPH__
