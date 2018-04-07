#include<iostream>
#include<vector>

#include"Digraph.hpp"
#include"AddibleList.hpp"
#include"Element.hpp"
// #define DEBUG

void Digraph::init(std::vector<std::vector<edge> > _G){
  n = _G.size(), m = 0;
  G.resize(n), RevG.resize(n);
  std::vector<std::vector<edge> > _RevG(n);
  std::vector<int> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = i;
  vlist.init(tmp);
  for (int i = 0; i < n; i++) m += _G[i].size();
  m /= 2;
  current_edge_size = m;
  std::vector<edge> ve(m);
  pos.resize(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < _G[i].size(); j++) {
      if(_G[i][j].u != i)std::swap(_G[i][j].u, _G[i][j].v);
      edge e = _G[i][j];
      ve[e.id] = _G[i][j];
      pos[e.id] = j;
      _RevG[e.to].push_back(edge(e.to, e.from, e.id));
    }
  }
  elist.init(ve);
  for (int i = 0; i < n; i++) G[i].init(_G[i]), RevG[i].init(_RevG[i]);
  next.resize(n + m);
}


int Digraph::RemoveEdge(int id){
#ifdef DEBUG
  if(id != elist.GetNext(elist.GetPrev(id))){
    printf("%d is already removed. \n", id);
    exit(1);
  }
#endif
  int u = elist[id].u, v = elist[id].v, res;
  if(u > v)std::swap(u, v);
  res = G[u].GetPrev(pos[id]);  
  G[u].remove(pos[id]);
  RevG[v].remove(pos[id]);
  elist.remove(id);
  current_edge_size--;
  next[id] = head;
  head = id;
  return res;
}

int Digraph::RemoveVertex(int id){
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int u = G[id][i].u ,v = G[id][i].v;
    int eid = G[id][i].id;
    int maxi = std::max(pos[eid].first, pos[eid].second);
    int mini = std::min(pos[eid].first, pos[eid].second);
    if(u == id)G[v].remove(maxi);
    else G[u].remove(mini);
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
  if(head >= m){
    int id = head - m;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      u = G[id][i].u, v = G[id][i].v;
      if(u == id)G[v].undo();
      else G[u].undo();
      elist.undo();
      current_edge_size++;
    }
  }else{
    u = elist[head].u, v = elist[head].v;
    G[u].undo();
    G[v].undo();
    elist.undo();
    current_edge_size++;
  }
  head = next[head];
}

void Digraph::print(){
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << "i:" << i << std::endl;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].u << " "  << G[i][j].v << std::endl;
    }
    std::cout << std::endl;
  }
}

