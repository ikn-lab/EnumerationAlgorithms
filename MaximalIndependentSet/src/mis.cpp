#include<vector>
#include<iostream>
#include<set>

#include"mis.hpp"
typedef long long int lli;
lli typeOne(Graph &g, int v){
  lli res = 0;
  for (int i = 0; i < g[v].size() and g[v][i] < v; i++)
    g.IncrementNeighbor(g[v][i]);
         
  res += MIS(g, v + 1);
  
  for (int i = 0; i < g[v].size() and g[v][i] < v; i++)
    g.decrementNeighbor(g[v][i]);
  
  return res;
}

lli typeTwoThree(Graph &g, int v, int v_neghbor){
  lli res = 0;
  //タイプ2の列挙
  g.AssignmentNeighbor(v, v_neghbor);
  res += MIS(g, v + 1);
  g.AssignmentNeighbor(v, 0);

  //タイプ3の列挙
  bool f = true;//このMISがタイプ3かどうかを判定するbool値
  std::vector<int> bucket;
  for (int i = 0; i < g[v].size() and g[v][i] < v; i++) {
    int &u = g[v][i];
    if(g.N(u) == 0){
      bucket.emplace_back(u);
      for (int j = 0; j < g[u].size() and g[u][j] < v; j++) {
        g.decrementNeighbor(g[u][j]);
        //先にvのneighborだけインクリメントされるからcondition Bを満たすようになる．
        f &= (g.N(g[u][j]) > 0);
      }
    }
    g.IncrementNeighbor(u);
  }

  if(f) res += MIS(g, v + 1);
  for (int i = 0; i < g[v].size() and g[v][i] < v; i++) 
    g.decrementNeighbor(g[v][i]);
    
  for (int i = 0; i < bucket.size(); i++) {
    int &u = bucket[i];
    for (int j = 0; j < g[u].size() and g[u][j] < v; j++) {
      g.IncrementNeighbor(g[u][j]);
    }
  }
  return res;
}


lli MIS(Graph &g, int v){
  if(v == g.size()){
    // bool check = false;
    // std::cout << "MIS" << std::endl;
    // for (int i = 0; i < g.size(); i++) {
    //   if(g.N(i) == 0){
    //     std::cout << i << " ";
    //     for (int j = 0; j < g[i].size(); j++) {
    //       if(g.N(g[i][j]) == 0)check = true;
    //     }
    //   }
    // }
    // std::cout << std::endl;
    // // if(check){
    // //   std::cerr << "miss" << std::endl;
    // //   exit(1);
    // // }
    return 1; 
  }
  int v_neghbor = 0;
  lli res = 0;
    
  for (int i = 0; i < g[v].size() and g[v][i] < v; i++) {
    if(g.N(g[v][i]) == 0)v_neghbor++;
  }
  
  if(v_neghbor == 0){
    //タイプ1の列挙
    res += typeOne(g, v);
  }else{
    //タイプ2と3の列挙
    res += typeTwoThree(g, v, v_neghbor);
  }
  return res;
}
