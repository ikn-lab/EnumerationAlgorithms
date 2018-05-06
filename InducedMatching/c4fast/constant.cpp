#include"graph.hpp"
#include"constant.hpp"
#include"basicDataStructure.hpp"

FixedQueue<pii> que;
FixedQueue<int> update;
std::vector<int> dist;
FixedStack<int> incident, vs;
std::vector<bigint> ans;
bigint res = 0;

std::vector<bigint> EIMMain(Graph &g) {
  int d = g.MaximumDeg().deg;
  que.resize(d*d + 10);
  update.resize(d*d + 10);
  dist.resize(g.size(), 1e9);
  vs.resize(d*g.size() + 10);
  incident.resize(2*g.size() + 10);
  ans.resize(g.size()/2);
  RecIM(g);
  return ans;
}

bigint RecIM(Graph &g, int size, int marge) { 
  ans[size] += marge;
  int cnt = 0;
  res += marge;
  while(g.MaximumDeg().deg != 0){
    ++cnt;
    int pivot = g.MaximumDeg().id;
    int isize = incident.size();
    CallOneChildren(g, pivot, size, marge);
    // res += CallOneChildren(g, pivot, size, marge);
    while(incident.size() > isize){
      g.RestoreVertex(incident.top());
      incident.pop();
    }
  }
  g.RestoreVertex(cnt);
  //return res;
}
bigint CallOneChildren(Graph &g, int v, int size, int marge) {
  //for bfs, vertex, distance
  int vssize = vs.size();
  que.push(pii(v, 0));
  incident.push(g[v].size());
  
  //start bfs
  dist[v] = 0;
  update.push(v);
  while(not que.empty()){
    v = que.front().first;
    int d = que.front().second;
    que.pop();
    g.RemoveVertex(v);
    if(d == 1)vs.push(-1);
    for (int i = g[v][0].next; i != g[v].end(); i=g[v][i].next) {
      if(dist[g[v][i].to] <= d)continue;
      if(dist[g[v][i].to] > d + 1)
        update.push(g[v][i].to);
      dist[g[v][i].to] = d + 1;
      switch(d){
      case 0:
        que.push(pii(g[v][i].to, d + 1));
        break;
      case 1:
        vs.push(g[v][i].to);
      }
    }
  }
  // end bfs

  //que.clear();
  while(not update.empty()){
    dist[update.front()] = 1e9;
    update.pop();
  }
  int empty_edge = 0, cnt;
  while(vs.size() > vssize){
    cnt = 0;
    while(vs.top() != -1){
      ++cnt;
      g.RemoveVertex(vs.top());
      vs.pop();
    }
    vs.pop();
    if(cnt != 0){
      RecIM(g, size + 1, marge);
      // res += RecIM(g, size + 1, marge);
      g.RestoreVertex(cnt);
    }else{
      ++empty_edge;
    }
  }
  if(empty_edge != 0){
    RecIM(g, size + 1, marge*empty_edge);
    // res += RecIM(g, size + 1, marge*empty_edge);
  }
  // return res;
}
