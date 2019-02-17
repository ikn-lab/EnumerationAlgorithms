#include<iostream>
#include<vector>

#include"AddibleDigraph.hpp"
#include"AddibleList.hpp"
#include"Element.hpp"
// #define DEBUG

void AddibleDigraph::init(std::vector<std::vector<edge> > H){
  n = H.size(), m = 0;
  G.resize(n), RevG.resize(n);
  std::vector<int> tmp(n);
  std::vector<vector<edge> > RevH(n);
  for (int i = 0; i < n; i++) tmp[i] = i;
  vlist.init(tmp);
  for (int i = 0; i < n; i++) m += H[i].size();
  current_edge_size = m;
  pos.resize(m);
  std::vector<edge> ve(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < H[i].size(); j++) {
      edge e = H[i][j];
      ve[e.id] = H[i][j];
      RevH[e.to].push_back(edge(e.to, e.from, e.id));
      pos[e.id].first  = j;
      pos[e.id].second = RevH[e.to].size() - 1;
    }
  }
  elist.init(ve);
  for (int i = 0; i < n; i++) G[i].init(H[i]), RevG[i].init(RevH[i]);
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
    int u = RevG[id][i].to;
    int eid = RevG[id][i].id;
    G[u].remove(pos[eid].first);
    elist.remove(eid);
    current_edge_size--;
  }
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int u = G[id][i].to;
    int eid = G[id][i].id;
    RevG[u].remove(pos[eid].second);
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
  if(m <= head and head < n + m){//RemoveVertex
    int id = head - m;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      u = G[id][i].to;
      RevG[u].undo();
      elist.undo();
      current_edge_size++;
    }
    for (int i = RevG[id].begin(); i != RevG[id].end(); i = RevG[id].GetNext(i)) {
      u = G[id][i].to;
      G[u].undo();
      elist.undo();
      current_edge_size++;
    }
    vlist.undo();
  }else if(head < m){//RemoveEdge
    u = elist[head].from, v = elist[head].to;
    G[u].undo();
    RevG[v].undo();
    // if(G[u].size() == 0 and RevG[u].size() == 0)vlist.undo();
    // if(G[v].size() == 0 and RevG[v].size() == 0)vlist.undo();
    elist.undo();
    current_edge_size++;
  }else if(n + m <= head and head < 2*m + n){//AddVertex
    // int id = head - (n + m);
    // for (int i = RevG[id].begin(); i != RevG[id].end(); i = RevG[id].GetNext[i]) {
    //   int eid = G[id][i].id;
    //   int u = elist[id].from, v = elist[id].to;
    //   if(not vlist.member(v))continue;
    //   G[u].add(pos[eid].first);
    //   RevG[v].add(pos[eid].second);
    //   elist.add(eid);
    //   current_edge_size++;
    // }
  }else{//AddEdge
    u = elist[head - (2*n + m)], v = elist[head - (2*n + m)];
    G[u].undo();
    RevG[v].undo();
    elist.undo();
    current_edge_size--;
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
  // if(G[u].size() == 0 and RevG[u].size() == 0)vlist.add(u);
  // if(G[v].size() == 0 and RevG[v].size() == 0)vlist.add(v);
  G[u].add(pos[id].first);
  RevG[v].add(pos[id].second);
  elist.add(id);
  current_edge_size++;
  next[id] = head;
  head = id + 2*m + n;
  res = G[u].GetNext(pos[G[u].back().id].first);
  return res;
}

int AddibleDigraph::AddVertex(int id){
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int eid = G[id][i].id;
    int u = elist[id].from, v = elist[id].to;
    if(not vlist.member(v))continue;
    G[u].add(pos[eid].first);
    RevG[v].add(pos[eid].second);
    elist.add(eid);
    current_edge_size++;
  }
  for (int i = RevG[id].begin(); i != RevG[id].end(); i = RevG[id].GetNext(i))  {
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
  head = id + n + m;
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
