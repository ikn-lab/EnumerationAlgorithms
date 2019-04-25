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
  for (int i = 0; i < n; i++) G[i].resize(n), SLO[i].resize(n, -1); 
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


void EIS::ComputeSLO(int d){
  
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i))
    deg[i] = 0;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      deg[i] += G[i][j];
    }
  }
  // int size = 0;
  int size = 0, v, maxi = -1e9;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    // mini =   1e9;
    maxi =  -1e9;
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      // if(deg[j] < mini) v = j, mini = deg[j];
      if(deg[j] > maxi) v = j, maxi = deg[j];
    }
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      deg[j] -= G[v][j];
    }
    deg[v] = -1e9;
    SLO[d][size++] = v;
    // std::cout << "v:" << v << " ";
  }
  // std::cout << std::endl;
  int s = 0;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i))
    SLO[d][s++] = i;
}

void EIS::RecEnum() {
  ans[solution.size()]++;  
  int v, stack, num_children = cand.size();
  ComputeSLO(solution.size());
  // for (int i = 0; i < num_children; i++) {
  //   std::cout << SLO[solution.size()][i] << " ";
  // }
  // std::cout << std::endl;
  for (int i = 0; i < num_children; i++) {
    v = SLO[solution.size()][i];
    stack = 0;
    cand.remove(v);
    for (int j = cand.begin(); j != cand.end(); j = cand.GetNext(j)) {
      if(G[v][j] == 1) j = cand.remove(j), stack++;
    }
    solution.push(v);
    if(not cand.empty()) RecEnum();
    else ans[solution.size()]++;
    solution.pop();
    for (int j = 0; j < stack; j++) cand.undo();
  }
  for (int i = 0; i < num_children; i++) cand.undo();  
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
