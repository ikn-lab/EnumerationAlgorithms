#include<iostream>
#include<vector>

#include"graph.hpp"
#include"enum.hpp"


void RecDS(Graph &g, std::vector<bigint> &res, int size, int depth = 0){
  if(depth == g.size()){
    res[size]++;
    return;
  }
  int v = g.size() - depth - 1;
  bool is_removed = (g[v].back() < v);
  for (int i = 0; i < g[v].size() and g[v][i] > v; i++) {
    int u = g[v][i];
    if(not g.used[u] and g[u].back() == v) is_removed = false;
    if(not is_removed)break;
    is_removed |= g.used[u];
  }
  if(is_removed){
    g.used[v] = false;
    RecDS(g, res, size - 1, depth + 1);
    g.used[v] = true;
  }
  // if(not (g[v].back() > v and is_removed))
  RecDS(g, res, size, depth + 1);
}

std::vector<bigint> EDSMain(Graph &g){
  std::vector<bigint> res(g.size() + 1, 0);
  RecDS(g, res, g.size());
  return res;
}

