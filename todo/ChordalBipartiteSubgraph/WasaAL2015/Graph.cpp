#include<iostream>
#include<algorithm>
#include<vector>

#include"Graph.hpp"
#include"List.hpp"
#include"Element.hpp"
#define INF 1e9
// #define DEBUG

void Graph::init(std::vector<std::vector<edge> > _G){
  n = _G.size(), m = 0;
  G.resize(n);
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
      if(_G[i][j].from != i)std::swap(_G[i][j].from, _G[i][j].to);
      int id = _G[i][j].id;
      ve[id] = _G[i][j];
      pos[id].first = pos[id].second;
      pos[id].second = j;
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
  int u = elist[id].from, v = elist[id].to, res;
  if(u > v)std::swap(u, v);
  if(x == u)res = G[u].GetPrev(pos[id].first);
  if(x == v)res = G[v].GetPrev(pos[id].second);
  G[u].remove(pos[id].first);
  G[v].remove(pos[id].second);
  elist.remove(id);
  current_edge_size--;
  next[id] = head;
  head = id;
  return res;
}

int Graph::RemoveVertex(int id){
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int u = G[id][i].from ,v = G[id][i].to;
    int eid = G[id][i].id;
    int maxi = std::max(pos[eid].first, pos[eid].second);
    int mini = std::min(pos[eid].first, pos[eid].second);
    if(u == id)G[v].remove(maxi);
    else G[u].remove(mini);
    elist.remove(eid);
    current_edge_size--;
  }
  vlist.remove(id);
  next[id + m] = head;
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
  }else{
    u = elist[head].from, v = elist[head].to;
    G[u].undo();
    G[v].undo();
    elist.undo();
    current_edge_size++;
  }
  head = next[head];
}

void Graph::print(){
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << "i:" << i << std::endl;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].from << " "  << G[i][j].to << std::endl;
    }
    std::cout << std::endl;
  }
}


void Graph::ordering(std::vector<std::vector<edge> > &_G) {
  int n = _G.size();
  std::vector<int> deg(n, 0);
  for (int i = 0; i < n; i++) deg[i] = _G[i].size();
  std::vector<int> ord(n), reverse(n);
  for (int i = 0; i < n; i++) {
    int v = -1, tmp = INF;
    for (int j = 0; j < n; j++) {
      if(deg[j] < tmp) v = j, tmp = deg[j];
    }
    ord[i] = v;
    reverse[v] = i;
    degeneracy = std::max(degeneracy, deg[v]);
    deg[v] = INF;
    for (int j = 0; j < _G[v].size(); j++) deg[_G[v][j].to]--;
  }
  std::vector<std::vector<edge> > H(n);
  for (int i = 0; i < n; i++) {
    int v = ord[i];
    H[i] = _G[v];
  }
  for (int i = 0; i < n; i++){
    std::sort(H[i].begin(), H[i].end());
    std::reverse(H[i].begin(), H[i].end());
  }
  _G = H;
}

