#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>

#include"Enum.hpp"

#define INF 1e9
using bigint = long long int;

EIS::EIS(std::vector<std::vector<int> > H){
  n = H.size();
  ans.resize(n, 0);
  G.resize(H.size());
  deg.resize(n, 0);
  solution.resize(n);
  for (int i = 0; i < n; i++) G[i].resize(n);
  for (int i = 0; i < n; i++) {
    int d = 0;
    for (int j = 0; j < n; j++){
      G[i][j] = H[i][j], d += H[i][j];
    }
    deg[i] = d;
    sum_deg += d;
  }
  std::vector<int> c(n);
  for (int i = 0; i < n; i++) c[i] = i;
  cand.init(c);
}


void EIS::Enumerate(){
  RecEnum();
}


void EIS::RecEnum() {
  int v, stack = 0;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    if(cand.size()*deg[i] < sum_deg) continue;
    sum_deg -= 2*deg[i];
    v = i, cand.remove(i);
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      deg[j] -= G[i][j];
    }
    break;
  }
  if(cand.size() > 0) RecEnum();
  else ans[solution.size()]++;
  
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    if(G[v][i] == 0)continue;
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      deg[j] -= G[i][j];
    }
    sum_deg -= 2*deg[i];
    i = cand.remove(i), stack++;
  }
  solution.push(v);
  
  if(cand.size() > 0) RecEnum();
  else ans[solution.size()]++;
  
  solution.pop();
  for (int i = 0; i < stack + 1; i++) {
    int u = cand.undo();
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      deg[j] += G[u][j];
    }
    sum_deg += 2*deg[u];
  }
  return;
}


void EIS::print(){
  int sum = 0;
  for (int i = 0; i < ans.size(); i++) sum += ans[i];
  std::cout << "sum:" << sum << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "[" << i << "]:" << ans[i] << std::endl;
    if(ans[i] == 0)break;
  }
}
