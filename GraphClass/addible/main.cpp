#include<iostream>
#include<vector>

#include"AddibleList.hpp"
#include"Graph.hpp"

int main(){
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<edge> > G(n);
  for (int i = 0; i < m; i++) {
    edge e;
    std::cin >> e.u >> e.v;
    e.cost = 1;
    e.id = i;
    G[e.u].push_back(e);
    G[e.v].push_back(e);
  }
  Graph H(G);
  for (int i = 0; i < 8; i++) {
    H.AddVertex(i);
  }
  // H.print();
  for (int i = 0; i < 3; i++) {
    H.undo();    
  }
  // H.print();
  return 0;
}
