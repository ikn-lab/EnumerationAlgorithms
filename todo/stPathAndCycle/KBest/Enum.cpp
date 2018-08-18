#include<iostream>
#include<algorithm>
#include"Enum.hpp"

#define DELETED -2

void ESTP::init(std::vector<std::vector<edge>> _G){
  n = _G.size();
  G.init(_G);
  for (int i = 0; i < _G.size(); i++) m += _G[i].size();
  solution.init(m);
  for (int i = 0; i < m; i++) solution.set(i, i);
  used.resize(n);
  ans.resize(n + 1, 0);
}

void ESTP::Enumerate(int s, int t){
  solution.add(s);
  RecEnum(s, t);
  solution.undo();
}

void ESTP::RecEnum(int s, int t){
  if(s == t){
    for (int i = solution.begin(); i != solution.end(); i = solution.GetNext(i)) {
      printf("%d ", i);
    }
      printf("\n");
    ans[solution.size()]++;
    return;    
  }
  G.RemoveVertex(s);
  for (int i = G[s].begin(); i != G[s].end(); i = G[s].GetNext(i)) {
    int v = G[s][i].to;
    if(Reacable(v, t)) {
      solution.add(v);
      RecEnum(v, t);
      solution.undo();
    } 
  }
  G.undo();
}

bool ESTP::Reacable(int s, int t){
  if(s == t)return true;
  for (int i = 0; i < n; i++) used[i] = false;
  que.push(s);
  used[s] = true;
  while(not que.empty()){
    int v = que.front();
    que.pop();
    for (int i = G[v].begin(); i != G[v].end(); i = G[v].GetNext(i)) {
      int u = G[v][i].to;
      if(used[u] == true)continue;
      if(u == t)return true;
      used[u] = true;
      que.push(u);
    }
  }
  return false;
}

void ESTP::print(){
  int sum = 0;
  for (int i = 0; i < ans.size(); i++) {
    sum += ans[i];
  }
  std::cout << "size:" << sum << std::endl;
  for (int i = 0; i < ans.size(); i++) {
    std::cout << i << ":" << ans[i] << std::endl;
  }
}
