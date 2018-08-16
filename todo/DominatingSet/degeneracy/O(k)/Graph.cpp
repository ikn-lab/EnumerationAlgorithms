#include<iostream>
#include<algorithm>
#include<vector>

#include"Graph.hpp"
#include"List.hpp"
#include"Element.hpp"
#define INF 1e9
// #define DEBUG

void Graph::init(std::vector<std::vector<edge> > H){
  n = H.size(), m = 0;
  G.resize(n);
  std::vector<int> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = i;
  vlist.init(tmp);
  for (int i = 0; i < n; i++) m += H[i].size();
  m /= 2;
  current_edge_size = m;
  std::vector<edge> ve(m);
  pos.resize(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < H[i].size(); j++) {
      if(H[i][j].from != i)std::swap(H[i][j].from, H[i][j].to);
      int id = H[i][j].id;
      ve[id] = H[i][j];
      pos[id].first = pos[id].second;
      pos[id].second = j;
    }
  }
  elist.init(ve);
  for (int i = 0; i < n; i++) G[i].init(H[i]);
  next.resize(n + m);
}


int Graph::RemoveEdge(int id, int x){
#ifdef DEBUG
  if(id != elist.GetNext(elist.GetPrev(id))){
    printf("%d is already removed. \n", id);
    exit(1);
  }
#endif
  // std::cout << "remove edge" << std::endl;
  // std::cout << "elist size:" << elist.size() << std::endl;
  int u = elist[id].from, v = elist[id].to, a = -1, b = -1;
  a = G[std::min(u, v)].remove(pos[id].first);
  b = G[std::max(u, v)].remove(pos[id].second);
  elist.remove(id);
  current_edge_size--;
  next[id] = head;
  head = id;
  // std::cout << "end remove edge" << std::endl;
  if(x == std::min(u, v))return a;
  else return b;
}

int Graph::RemoveVertex(int id){
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int u = G[id][i].from ,v = G[id][i].to;
    int eid = G[id][i].id;
    if(v < u) G[v].remove(pos[eid].first);
    else G[v].remove(pos[eid].second);
    elist.remove(eid);
    current_edge_size--;
  }
  vlist.remove(id);
  next[id] = head;
  head = id + m;
  return vlist.GetPrev(id);
}

void Graph::undo(){
  int u, v;
  if(head >= m){
    int id = head - m;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      u = G[id][i].from, v = G[id][i].to;
      if(u == id)G[v].undo();
      else G[u].undo();
      elist.undo();
      current_edge_size++;
    }
    vlist.undo();    
  }else{
    u = elist[head].from, v = elist[head].to;
    // if(not vlist.member(u)) vlist.undo();
    // if(not vlist.member(v)) vlist.undo();
    G[u].undo();
    G[v].undo();
    elist.undo();
    current_edge_size++;
  }
  head = next[head];
}

void Graph::print(){
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << i << ": ";
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout  << G[i][j].to << " ";
    }
    std::cout << std::endl;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout  << G[i][j].id << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
}


int Graph::GetRev(int eid, int x){
  int u = elist[eid].from, v = elist[eid].to;
  // std::cout << "GetRev:";
  // if(x == std::min(u, v))std::cout << pos[eid].second << std::endl;
  // else std::cout << pos[eid].first << std::endl;
  if(x == std::min(u, v)) return pos[eid].second;
  else return pos[eid].first;
}


