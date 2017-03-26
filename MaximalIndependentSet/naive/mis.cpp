#include<vector>
#include<iostream>
#include<set>

#include"mis.hpp"
typedef long long int lli;

bool check(Graph &g, lli used){
  int n = g.size();
  bool res = true;
  std::vector<int> neighbor(n, 0);
  for (int i = 0; i < n; i++) {
    bool s = ((used&(1LL<<i)) > 0);
    for (int j = 0; j < g[i].size() and s; j++) {
      neighbor[g[i][j]]++;
    }
  }
  for (int i = 0; i < n; i++) {
    if( ((used&(1LL<<i)) > 0) ){
      res &= (neighbor[i] == 0);
    }else{
      res &= (neighbor[i] > 0);
    }
  }
  return res;
}

lli MIS(Graph &g, int v){
  int n = g.size();
  lli res = 0;
  for (lli i = 0; i < (1LL<<n); i++) {
    if(check(g, i)){
      res++;
      for (int j = 0; j < n; j++) {
        if((i&(1LL<<j)) > 0)std::cout << j << " ";
      }
      std::cout << std::endl;
    }
  }
  return res;
}
