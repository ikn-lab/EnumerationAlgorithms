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
  SLO.resize(n);
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


void EIS::ComputeSLO(){
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i))
    deg[i] = 0;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      deg[i] += G[i][j];
    }
  }
  int size = 0;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    int v, mini =  1e9;
    if(deg[i] < mini) v = i, mini = deg[i];
    // int v, max =  -1e9;
    // if(deg[i] > max) v = i, max = deg[i];
    SLO[size++ + tail] = v;
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      deg[j] -= G[i][j];
    }
  }
}

void EIS::RecEnum() {
  ans[solution.size()]++;  
  int v, stack, num_children = cand.size();
  ComputeSLO();
  for (int i = 0; i < num_children; i++) {
    cand.remove(SLO[tail++]);
  }
  // solution.push(v);
  for (int i = 0; i < num_children; i++) {
    v = SLO[tail--];
    stack = 0;
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)){
      if(G[v][j] == 1) j = cand.remove(j), stack++;
    }
    solution.push(v);
    if(not cand.empty()) RecEnum();
    else ans[solution.size()]++;
    solution.pop();
    for (int j = 0; j < stack + 1; j++) cand.undo();
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
