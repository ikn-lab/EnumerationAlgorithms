#include<iostream>
#include<vector>

#include"AddibleDigraph.hpp"
#include"AddibleList.hpp"
#include"Element.hpp"
// #define DEBUG

void AddibleDigraph::init(std::vector<std::vector<edge> > _G){
  n = _G.size(), m = 0;
  G.resize(n), RevG.resize(n);
  std::vector<std::vector<edge> > _RevG(n);
  std::vector<int> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = i;
  vlist.init(tmp);
  for (int i = 0; i < n; i++) m += _G[i].size();
  current_edge_size = m;
  std::vector<edge> ve(m);
  pos.resize(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < _G[i].size(); j++) {
      edge e = _G[i][j];
      ve[e.id] = _G[i][j];
      pos[e.id].first  = j;
      pos[e.id].second = _RevG[e.to].size();
      _RevG[e.to].push_back(edge(e.to, e.from, e.id));
    }
  }
  elist.init(ve);
  for (int i = 0; i < n; i++) G[i].init(_G[i]), RevG[i].init(_RevG[i]);
  next.resize(n + m);
}


int AddibleDigraph::RemoveEdge(int id){
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

int AddibleDigraph::RemoveVertex(int id){
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

void AddibleDigraph::undo(){
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
    if(G[u].size() == 0 and RevG[u].size() == 0)vlist.undo();
    if(G[v].size() == 0 and RevG[v].size() == 0)vlist.undo();
    elist.undo();
    current_edge_size++;
  }
  head = next[head];
}



int AddibleDigraph::AddEdge(int id){
#ifdef DEBUG
  if(id == elist.GetNext(elist.GetPrev(id))){
    printf("%d is already added. \n", id);
    exit(1);
  }
#endif
  int u = elist[id].from, v = elist[id].to, res;
  if(G[u].size() == 0 and RevG[u].size() == 0)vlist.add(u);
  if(G[v].size() == 0 and RevG[v].size() == 0)vlist.add(v);
  G[u].add(pos[id].first);
  RevG[v].add(pos[id].second);
  elist.add(id);
  current_edge_size++;
  next[id] = head;
  head = id;
  res = G[u].GetNext(pos[G[u].back().id].first);
  return res;
}

int AddibleDigraph::AddVertex(int id){
  for (int i = 0; i < G[id].end(); i++) {
    int eid = G[id][i].id;
    int u = elist[id].from, v = elist[id].to;
    if(not vlist.member(v))continue;
    G[u].add(pos[eid].first);
    RevG[v].add(pos[eid].second);
    elist.add(eid);
    current_edge_size++;
  }
  vlist.add(id);
  next[id] = head;
  head = id + m;
  return vlist.GetPrev(id);
}


void AddibleDigraph::print(){
  for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
    std::cout << "i:" << i << std::endl;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].from << " "  << G[i][j].to << std::endl;
    }
    std::cout << std::endl;
  }
}
