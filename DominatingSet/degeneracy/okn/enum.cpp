#include<iostream>
#include<vector>

#include"graph.hpp"
#include"enum.hpp"

bool checkDominatingSet(Graph &G){
  int n = G.size();
  std::vector<bool> dom(n, false);
  for (int i = 0; i < G.size(); i++) {
    if(not G.used[i])continue;
    dom[i] = true;
    for (int j = 0; j < G[i].size(); j++) {
      dom[G[i][j]] = true;
    }
  }
  for (int i = 0; i < n; i++) {
    if(dom[i] == false) {
      return false; 
    }
  }
  return true;
}


long long int sum = 0;
void RecDS(Graph &g, std::vector<bigint> &res, std::vector<int> &count, int size, int depth = 0){
  count[depth]++;
  if(depth == g.size()){
    // if(not checkDominatingSet(g)){
    //   std::cout << "error" << std::endl;
    //   exit(1);
    // }
    res[size]++;
    sum++;
    return;
  }
  if(sum >= 1e5)return;
  int v = g.size() - depth - 1;
  bool has_private = (g.dominated[v] == 1);
  for (int i = 0; i < g[v].size(); i++) {
    int u = g[v][i];
    //Is u a private vertex?
    has_private |= (g.dominated[u] == 1);
  }
  if(not has_private) {
    for (int i = 0; i < g[v].size(); i++) {
      g.dominated[g[v][i]]--;
    }
    g.dominated[v]--;
    g.used[v] = false;
    RecDS(g, res, count, size - 1, depth + 1);    
    g.used[v] = true;
    g.dominated[v]++;
    for (int i = 0; i < g[v].size(); i++) {
      g.dominated[g[v][i]]++;
    }
  }
  RecDS(g, res, count, size, depth + 1);
}

std::vector<bigint> EDSMain(Graph &g){
  std::vector<bigint> res(g.size() + 1, 0);
  std::vector<int> count(g.size() + 1, 0);
  RecDS(g, res, count, g.size());
  int sum = 0;
  // for (int i = 0; i < count.size(); i++) sum += count[i];
  // std::cout << sum << std::endl;
  // for (int i = 0; i < count.size(); i++) {
  //   // std::cout << "count[" << i << "]:";
  //   std::cout << count[i] << std::endl;
  // }
  // std::cout << std::endl;
  return res;
}
