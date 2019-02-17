#include<iostream>
#include<vector>

#include"DigraphNoUndo.hpp"
#include"List.hpp"
#include"Element.hpp"
// #define DEBUG

void DigraphNoUndo::init(std::vector<std::vector<edge> > H){
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


int DigraphNoUndo::RemoveEdge(int id){
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
  return res;
}

int DigraphNoUndo::AddEdge(int id){
  int u = elist[id].from, v = elist[id].to;
  int res = G[u].GetPrev(pos[id].first);
  if(elist.member(id))return res;
  G[u].add(pos[id].first);
  RevG[v].add(pos[id].second);
  elist.add(id);
  current_edge_size++;
  return res;
}

//バグっている。
int DigraphNoUndo::RemoveVertex(int id){
  for (int i = RevG[id].begin(); i != RevG[id].end(); i = RevG[id].GetNext(i)) {
    int u = RevG[id][i].from ,v = RevG[id][i].to;
    int eid = RevG[id][i].id;
    G[v].remove(pos[eid].first);
    elist.remove(eid);
    current_edge_size--;
  }
  vlist.remove(id);
  return vlist.GetPrev(id);
}



void DigraphNoUndo::print(){
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << i << ": ";
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].to << " ";
    }
    std::cout << std::endl;
  }
}
