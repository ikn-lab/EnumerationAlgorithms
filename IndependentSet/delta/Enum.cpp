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
  solution.resize(n);
  for (int i = 0; i < n; i++) G[i].resize(n);
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; j++)
      G[i][j] = H[i][j];
  std::vector<int> c(n);
  for (int i = 0; i < n; i++) c[i] = i;
  cand.init(c);
}


void EIS::Enumerate(){
  RecEnum();
}


void EIS::RecEnum(int v) {
  if(cand.member(v)){
    int stack = 0;
    cand.remove(v);
    if(cand.size() > 0) RecEnum(v + 1);
    else ans[solution.size()]++;
    for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
      if(G[v][i] == 1) i = cand.remove(i), stack++;
    }
    solution.push(v);
    if(cand.size() > 0) RecEnum(v + 1);
    else ans[solution.size()]++;
    solution.pop();
    for (int i = 0; i < stack + 1; i++) cand.undo();
  }else{
    if(cand.size() > 0) RecEnum(v + 1);
    else ans[solution.size()]++;
  }
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
