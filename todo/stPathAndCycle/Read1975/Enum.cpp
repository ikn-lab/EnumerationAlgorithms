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
    if(Reachable(v, t)) {
      int tmp = nextStartPoint(v);
      RecEnum(v, t);
      for (int i = 0; i < tmp; i++) solution.undo();
    } 
  }
  G.undo();
}

int ESTP::nextStartPoint(int v){
  for (int i = 0; i < n; i++) used[i] = false;
  used[v] = true;
  return v;
}
// int ESTP::nextStartPoint(int v){
//   for (int i = 0; i < n; i++) used[i] = false;
//   used[v] = true;
//   return dfs(v);
// }

// int dfs(int v, int t){
//   if(v == t)return 1;
//   int res = 0, cnt = 0, x;
//   for (int i = G[v].begin(); i != G[v].end(); i = G[v].GetNext(i)) {
//     int u = G[v][i].to;
//     if(used[u])continue;
//     cnt++;
//     used[u] = true;
//     x = dfs(u, t);
//     cnt += (x != 0);
//     res += x;
//   }
//   if(cnt > 1)return -1;
//   else return res;
// }

bool ESTP::Reachable(int s, int t){
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
 
