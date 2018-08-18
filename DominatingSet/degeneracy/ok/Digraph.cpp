#include<iostream>
#include<vector>

#include"Digraph.hpp"
#include"List.hpp"
#include"Element.hpp"
// #define DEBUG

void Digraph::init(std::vector<std::vector<edge> > H){
  n = H.size(), m = 0;
  G.resize(n), RevG.resize(n);
  std::vector<std::vector<edge> > RevH(n);
  std::vector<int> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = i;
  vlist.init(tmp);
  for (int i = 0; i < n; i++) m += H[i].size();
  current_edge_size = m;
  std::vector<edge> ve(m);
  pos.resize(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < H[i].size(); j++) {
      edge e = H[i][j];
      ve[e.id] = H[i][j];
      pos[e.id].first  = j;
      pos[e.id].second = RevH[e.to].size();
      RevH[e.to].push_back(edge(e.to, e.from, e.id));
    }
  }
  elist.init(ve);
  for (int i = 0; i < n; i++) G[i].init(H[i]), RevG[i].init(RevH[i]);
  next.resize(n + m);
}


int Digraph::RemoveEdge(int id){
#ifdef DEBUG
  if(id != elist.GetNext(elist.GetPrev(id))){
    printf("%d is already removed. \n", id);
    exit(1);
  }
#endif
  int u = elist[id].from, v = elist[id].to;
  int res = G[u].GetPrev(pos[id].first);
  G[u].remove(pos[id].first);
  RevG[v].remove(pos[id].second);
  elist.remove(id);
  current_edge_size--;
  next[id] = head;
  head = id;
  return res;
}

//バグっている。
int Digraph::RemoveVertex(int id){
  for (int i = RevG[id].begin(); i != RevG[id].end(); i = RevG[id].GetNext(i)) {
    int u = RevG[id][i].from ,v = RevG[id][i].to;
    int eid = RevG[id][i].id;
    G[v].remove(pos[eid].first);
    elist.remove(eid);
    current_edge_size--;
  }
  vlist.remove(id);
  next[id] = head;
  head = id + m;
  return vlist.GetPrev(id);
}

void Digraph::undo(){
  int u, v;
  if(head >= m){//vertex
    int id = head - m;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      u = G[id][i].from, v = G[id][i].to;
      G[v].undo();
      RevG[u].undo();
      elist.undo();
      current_edge_size++;
    }
    vlist.undo();
  }else{//edge
    u = elist[head].from, v = elist[head].to;
    G[u].undo();
    RevG[v].undo();
    elist.undo();
    current_edge_size++;
  }
  head = next[head];
}

void Digraph::print(){
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << i << ": ";
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].to << " ";
    }
    std::cout << std::endl;
  }
}
