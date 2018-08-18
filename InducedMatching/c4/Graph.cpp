#include<iostream>
#include<vector>
#include<algorithm>

#include"Graph.hpp"
#include"List.hpp"
#include"Element.hpp"
// #define DEBUG
using pii = std::pair<int, int>;

//This function sorts the vertices in _G in descending order of degree. 
void sort(std::vector<std::vector<edge> > &_G, std::vector<int> &sorted, std::vector<int> &rev){
  int n = _G.size();
  std::vector<pii> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = pii(_G[i].size(), i);
  sort(tmp.begin(), tmp.end(), std::greater<pii>());
  for (int i = 0; i < n; i++)
    sorted[i] = tmp[i].second, rev[tmp[i].second] = i;
  std::vector<std::vector<edge> > tmp_G(n);
  for (int i = 0; i < n; i++) {
    tmp_G[i] = _G[sorted[i]];
    for (int j = 0; j < tmp_G[i].size(); j++) {
      int id = tmp_G[i][j].id, cost = tmp_G[i][j].cost;
      tmp_G[i][j] = edge(i, rev[tmp_G[i][j].to], id, cost);
    }
  }
  _G = tmp_G;
}

void Graph::init(std::vector<std::vector<edge> > _G){
  n = _G.size(), m = 0, isolated = 0;
  G.resize(n);
  std::vector<int> sorted(n), rev(n);
  sort(_G, sorted, rev);
  org_deg = deg = _G[0].size();
  degDistribution.resize(_G[0].size() + 1);
  for (int i = 0; i < n; i++) {
    degDistribution[_G[i].size()]++;
  }
  vlist.init(n + deg + 1);
  for (int i = 0; i < n + deg + 1; i++) vlist.set(i, i);
  std::vector<int> boundary(deg + 1, 0);
  for (int i = 0; i < n; i++) {
    m += _G[i].size();
    boundary[_G[i].size() - 1]++;
  }
  for (int i = deg - 1; i >= 0; i--)
    boundary[i] += boundary[i + 1];

  vlist.move(n + deg, vlist.end());
  for (int i = deg - 1; i >= 0; i--) {
    if(boundary[i + 1] == boundary[i]){
      vlist.move(n + i, n + i + 1);
    }else{
      vlist.move(n + i, boundary[i] - 1);
    }
    
      
  }
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
  for (int i = 0; i < n; i++) isolated += (GetDeg(i) == 0);
  next.resize(n + m);
  dist.resize(n, 1e9);
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
  if(not vlist.member(id))return -1;
  for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
    int u = G[id][i].from ,v = G[id][i].to;
    int eid = G[id][i].id;
    elist.remove(eid);
    current_edge_size--;
    degDistribution[GetDeg(v)]--;
    degDistribution[GetDeg(v) - 1]++;

    if(vlist.GetNext(deg + n) > n)
      deg = vlist.GetPrev(GetNext(deg + n)) - n;
    if(v < u) G[v].remove(pos[eid].first);
    else G[v].remove(pos[eid].second);
    vlist.move(v, GetDeg(v) + n);
    if(GetDeg(v) == 0)isolated++;
  }
  degDistribution[GetDeg(id)]--;  
  if(GetDeg(id) == 0)isolated--;
  vlist.remove(id);
  if(vlist.GetNext(deg + n) > n)
    deg = vlist.GetPrev(GetNext(deg + n)) - n;
  next[id + m] = head;
  head = id + m;
  return GetPrev(id);
}

void Graph::undo(){
  int u, v;
  if(head >= m){
    int id = head - m;
    for (int i = G[id].begin(); i != G[id].end(); i = G[id].GetNext(i)) {
      u = G[id][i].from, v = G[id][i].to;
      if(u == id){
        G[v].undo(); 
        degDistribution[GetDeg(v) - 1]--;
        degDistribution[GetDeg(v)]++;
        vlist.move(v, GetDeg(v) + n);
        deg = std::max(GetDeg(v), deg);
        if(GetDeg(v) == 1)isolated--;
      }else{
        G[u].undo();
        degDistribution[GetDeg(u) - 1]--;
        degDistribution[GetDeg(u)]++;
        vlist.move(u, GetDeg(u) + n);
        deg = std::max(GetDeg(u), deg);
        if(GetDeg(u) == 1)isolated--;
      }
      elist.undo();
      current_edge_size++;
    }
    degDistribution[GetDeg(id)]++;
    if(GetDeg(id) == 0)isolated++;
    vlist.undo();
    vlist.move(id, GetDeg(id) + n);
    deg = std::max(GetDeg(id), deg);
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
  for (int i = begin(); i != vlist.end(); i = GetNext(i)) {
    std::cout << "i:" << i << std::endl;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout << G[i][j].from << " "  << G[i][j].to << std::endl;
    }
    std::cout << std::endl;
  }
}
