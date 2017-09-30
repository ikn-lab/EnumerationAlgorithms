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
  bool has_private = false;
  for (int i = 0; i < g[v].size() and g[v][i] > v; i++) {
    int& u = g[v][i];
    //Is u a private vertex?
    has_private |= (g.dominated[u] == 0 and not g.used[u] and g[u].back() == v);
    g.dominated[v] += g.used[u];
  }
  if(not g[v].empty() and not has_private)
    if(g.dominated[v] > 0 or (g[v].back() < v)){
      g.used[v] = false;
      RecDS(g, res, size - 1, depth + 1);    
      g.used[v] = true;
    }
  
  for (int i = 0; i < g[v].size() and g[v][i] > v; i++) 
    g.dominated[g[v][i]]++;
  RecDS(g, res, size, depth + 1);
  for (int i = 0; i < g[v].size() and g[v][i] > v; i++){
    g.dominated[g[v][i]]--;
    g.dominated[v] -= g.used[g[v][i]];
  }
}

std::vector<bigint> EDSMain(Graph &g){
  std::vector<bigint> res(g.size() + 1, 0);
  RecDS(g, res, g.size());
  return res;
}
