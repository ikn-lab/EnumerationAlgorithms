#include<iostream>
#include<vector>

#include"Enum.hpp"
void EDS::init(std::vector<std::vector<int> > H){
  G = H;
  dominated.resize(G.size());
  for (int i = 0; i < G.size(); i++)  dominated[i] = G[i].size() + 1;
  ans.resize(G.size(), 0);
}




void EDS::Enumerate(){
  int n = G.size();
  for (int j = 0; j < n; j++) dominated[j] = 0;
  for (int i = 0; i < (1<<n); i++) {
    int size = 0;
    for (int j = 0; j < n; j++) {
      if((i&(1<<j))){
        dominated[j]++;
        size++;
        for (int k = 0; k < G[j].size(); k++) dominated[G[j][k]]++;
      }
    }
    bool isDom = true;
    for (int j = 0; j < n; j++) isDom &= (dominated[j] != 0);
    ans[size]++;
    for (int j = 0; j < n; j++) dominated[j] = 0;
  }
}

// void EDS::dfs(int size, int depth){
//   if(depth == G.size()){
//     bool isDom = true;
//     for (int i = 0; i < G.size() and isDom; i++) isDom &= (dominated[i] != 0);
//     ans[size] += isDom;
//     return;
//   }
//   for (int i = 0; i < G[depth].size(); i++) {
//     dominated[G[depth][i]]--;
//   }
//   dominated[depth]--;  
//   dfs(size - 1, depth + 1);
//   dominated[depth]++;  
//   for (int i = 0; i < G[depth].size(); i++) dominated[G[depth][i]]++;
//   dfs(size, depth + 1);
// }

void EDS::print(){
  bigint sum = 0;
  for (int i = 0; i <= G.size(); i++) sum += ans[i];
  std::cout << sum << std::endl;
  for (int i = 0; i <= G.size(); i++) {
    std::cout << ans[i] << std::endl;
  }
}
