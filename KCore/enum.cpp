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
    if(dom[i] == false) return false; 
  }
  return true;
}


void RecDS(Graph &G, std::vector<bigint> &res, std::vector<int> &count, int size, int depth = 0){
  count[depth]++;
  if(depth == G.size()){
    res[size]++;
    return;
  }
  int v = G.size() - depth - 1;
  G.used[v] = false;
  if(checkDominatingSet(G)) RecDS(G, res, count, size - 1, depth + 1);          
  G.used[v] = true;
  RecDS(G, res, count, size, depth + 1);
}

std::vector<bigint> EDSMain(Graph &g){
  std::vector<bigint> res(g.size() + 1, 0);
  std::vector<int> count(g.size() + 1, 0);
  RecDS(g, res, count, g.size());
  int sum = 0;
  for (int i = 0; i < count.size(); i++) sum += count[i];
  std::cout << sum << std::endl;
  for (int i = 0; i < count.size(); i++) {
    // std::cout << "count[" << i << "]:";
    std::cout << count[i] << std::endl;
  }
  std::cout << std::endl;
  return res;
}
