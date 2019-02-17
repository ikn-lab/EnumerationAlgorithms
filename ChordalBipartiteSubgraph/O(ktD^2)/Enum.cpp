#include<iostream>
#include<vector>
#include"Graph.hpp"
#include"Enum.hpp"

void ECIB::init(std::vector<std::vector<edge> > H) {
  int n = H.size();
  std::vector<int> deg(n);
  std::vector<int> new_ordering(n, -1);
  std::vector<int> old_ordering(n, -1);
  for (int i = 0; i < n; i++) deg[i] = H[i].size();
  for (int i = 0; i < n; i++) {
    int mini = 1e9, id = -1;
    for (int j = 0; j < n; j++) {
      if(deg[j] < mini) mini = deg[j], id = j;
    }
    new_ordering[i]  = id;
    old_ordering[id] = i;
    for (int j = 0; j < H[id].size(); j++) deg[H[id][j].to]--;
    deg[id] = 1e9;
  }
  for (int i = 0; i < n; i++) {
    std::cout << new_ordering[i] << std::endl;
  }
  std::vector<std::vector<edge> > CopyH(n);
  std::vector<int> tmp;
  for (int i = 0; i < n; i++) CopyH[i] = new_ordering[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < CopyH[i].size(); j++)
      CopyH[i].from = i, CopyH[i].to = old_ordering[CopyH[i].to];
  }
  G.init(CopyH);
  AWS.init();
}

void ECIB::Enumerate(){
  
}
