#include<iostream>
#include<vector>

#include"Graph.hpp"
#include"List.hpp"
#include"Element.hpp"
#define DEBUG

void Graph::init(std::vector<std::vector<edge> > _G){
  n = _G.size(), m = 0;
  G.resize(n), deg.resize(n);
  std::vector<int> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = i;
  vlist.init(tmp);
  for (int i = 0; i < n; i++) m += _G[i].size(), deg[i] = _G[i].size();
  m /= 2;
  std::vector<edge> ve(m);
  edge2vertex.resize(m);
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
  for (int i = 0; i < n; i++) G[i].init(_G[i]);
  next.resize(n + m);
}


int Graph::RemoveEdge(int id, int x){
#ifdef DEBUG
  if(id != elist.GetNext(elist.GetPrev(id))){
    printf("%d is already removed. \n", id);
    exit(1);
  }
#endif
  int u = elist[id].u, v = elist[id].v, res;
  if(u > v)std::swap(u, v);
  if(x == u)res = G[u].GetPrev(edge2vertex[id].first);
  else res = G[v].GetPrev(edge2vertex[id].second);
  G[u].remove(edge2vertex[id].first);
  G[v].remove(edge2vertex[id].second);
  elist.remove(id);
  deg[u]--, deg[v]--;
  next[id] = head;
  head = id;
  return res;
}

int Graph::RemoveVertex(int id){
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int u = G[id][i].u ,v = G[id][i].v;
    int eid = G[id][i].id;
    int maxi = std::max(edge2vertex[eid].first, edge2vertex[eid].second);
    int mini = std::min(edge2vertex[eid].first, edge2vertex[eid].second);
    if(u == id)G[v].remove(maxi);
    else G[u].remove(mini);
    elist.remove(eid);
    deg[u]--, deg[v]--;
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
      u = G[id][i].u, v = G[id][i].v;
      if(u == id)G[v].undo();
      else G[u].undo();
      elist.undo();
      deg[u]++, deg[v]++;
    }
  }else{
    u = elist[head].u, v = elist[head].v;
    G[u].undo();
    G[v].undo();
    elist.undo();
    deg[u]++, deg[v]++;
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

