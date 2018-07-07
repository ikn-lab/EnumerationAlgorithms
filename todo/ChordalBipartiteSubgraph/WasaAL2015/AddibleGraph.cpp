#include<iostream>
#include<vector>

#include"AddibleGraph.hpp"
#include"AddibleList.hpp"
#include"Element.hpp"
// #define DEBUG

void AddibleGraph::init(std::vector<std::vector<edge> > _G){
  n = _G.size(), m = 0;
  G.resize(n);
  std::vector<int> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = i;
  vlist.init(tmp);
  for (int i = 0; i < n; i++) m += _G[i].size();
  m /= 2;
  current_edge_size = 0;
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
  next.resize(2*(n + m));
}

int AddibleGraph::RemoveEdge(int id, int x){
#ifdef DEBUG
  if(id != elist.GetNext(elist.GetPrev(id))){
    printf("%d is already removed. \n", id);
    exit(1);
  }
#endif
  int u = elist[id].from, v = elist[id].to, res;
  if(G[u].size() == 1)vlist.remove(u);
  if(G[v].size() == 1)vlist.remove(v);
  if(u > v)std::swap(u, v);
  if(x == u)res = G[u].GetPrev(pos[id].first);
  if(x == v)res = G[v].GetPrev(pos[id].second);
  G[u].remove(pos[id].first);
  G[v].remove(pos[id].second);
  elist.remove(id);
  current_edge_size--;
  next[id + n + m] = head;
  head = id + n + m;
  return res;
}

int AddibleGraph::AddEdge(int id, int x){
#ifdef DEBUG
  if(id == elist.GetNext(elist.GetPrev(id))){
    printf("%d is already added. \n", id);
    exit(1);
  }
#endif
  int u = elist[id].from, v = elist[id].to, res;
  if(vlist.elementRemoved(u) or vlist.elementRemoved(v)){
    printf("%d or %d is already removed from G. ", u, v);
    exit(1);
  }
  // if u or v is deleted, an error occurs. 
  if(not vlist.useElement(u))vlist.add(u);
  if(not vlist.useElement(v))vlist.add(v);
  if(u > v)std::swap(u, v);
  G[u].add(pos[id].first);
  G[v].add(pos[id].second);
  elist.add(id);
  current_edge_size--;
  next[id] = head;
  head = id;
  if(x == u) res = G[x].GetNext(pos[G[x].back().id].first);
  if(x == v) res = G[x].GetNext(pos[G[x].back().id].second);
  return res;
}

int AddibleGraph::RemoveVertex(int id){
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int eid = G[id][i].id;
    int u = elist[eid].from ,v = elist[eid].to;
    int mini = std::min(pos[eid].first, pos[eid].second);
    int maxi = std::max(pos[eid].first, pos[eid].second);
    if(u == id)G[v].remove(maxi);
    else G[u].remove(mini);
    elist.remove(eid);
    current_edge_size--;
  }
  vlist.remove(id);
  next[id + n + 2*m] = head;
  head = id + n + 2*m;
  return vlist.GetPrev(id);
}

int AddibleGraph::AddVertex(int id){
  for (int i = 0; i < G[id].end(); i++) {
    int eid = G[id][i].id;
    int v = elist[eid].to;
    if(v == id)v = elist[eid].from;
    if(not vlist.member(v))continue;
    int mini = std::min(id, v), maxi = std::max(id, v);
    G[mini].add(pos[eid].first);
    G[maxi].add(pos[eid].second);
    elist.add(eid);
    current_edge_size++;
  }
  vlist.add(id);
  next[id + m] = head;
  head = id + m;
  return vlist.GetNext(id);
}

void AddibleGraph::undo(){
  int u, v;
  if(head >= n + 2*m){//RemoveVertex
    int id = head - n - 2*m;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      u = G[id][i].from, v = G[id][i].to;
      if(u == id) G[v].undo();
      else G[u].undo();
      if(G[v].size() == 0)vlist.undo();
      elist.undo();
      current_edge_size++;
    }
    vlist.undo();
  }else if(head >= n + m or head < m){//AddEdge or RemoveEdge
    if(head < m)u = elist[head].from, v = elist[head].to;
    else u = elist[head - n - m].from, v = elist[head - n - m].to;
    G[u].undo();
    G[v].undo();
    if(G[u].size() == 0)vlist.undo();
    if(G[v].size() == 0)vlist.undo();
    elist.undo();
    current_edge_size++;
  }else{//condition: m < head <= n + m, AddVertex
    u = head - m;
    int cnt = 0;
    for (int i = G[u].begin(); i != G[u].end(); i = G[u].GetNext(i)) {
      v = G[u][i].to;
      cnt++;
      G[v].undo();
      elist.undo();
      current_edge_size--;
    }
    for (int i = 0; i < cnt; i++) G[u].undo();
    vlist.undo();
  }
  head = next[head];
}


void AddibleGraph::print(){
  std::cout << "vertex:" << currentSize() << " edge:" << current_edge_size << std::endl;
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << "i:" << i << std::endl;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].from << " "  << G[i][j].to << std::endl;
    }
    std::cout << std::endl;
  }
}
