#include<vector>
#include<iostream>

#include"enum.hpp"
#include"graph.hpp"

using bigint = long long int;
std::vector<bigint> ans;

bool dfs(Graph &g, vector<bool> &used, int v, int depth = 0){
  if(depth == g.size())return true;
  used[v] = true;
  bool res = false, ;
  for (int i = 0; i < g[v].size(); i++) {
    int to = g[v][i];
    if(used[to])continue;
    res |= dfs(g, used, to, + 1);
  }
  return res;  
}

bool Connectivity(Graph &g){
  int v;
  for (int i = 0; i < g.size(); i++) {
    if(used[i]){
      v = i;
      break;
    }
  }
  std::vector<bool> used(g.size(), false);
  return dfs(g, used, v);
}

std::vector<bigint> ELGMain(Graph &g){
  for (int i = 0; i < (1<<g.size()) - 1; i++) {
    int size = 0;
    for (int j = 0; j < n; j++) {
      if(i&(1<<j))g.used[j] = true, size++;
      else g.used[j] = false;
    }
    ans[size] += (Connectivity(g) and Girth(g) >= g.k);
  }
  return ans;
}

