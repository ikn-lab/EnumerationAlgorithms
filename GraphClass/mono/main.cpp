#include<iostream>
#include<vector>

#include"List.hpp"
#include"Digraph.hpp"

int main(){
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<edge> > G(n);
  std::cout << G.size() << std::endl;
  for (int i = 0; i < m; i++) {
    edge e;
    std::cin >> e.from >> e.to;
    e.cost = 1;
    e.id = i;
    G[e.from].push_back(e);
  }
  Digraph H(G);
  H.print();
  for (int i = 0; i < 4; i++) {
    H.RemoveEdge(i*2);
  }
  // H.print();
  for (int i = 0; i < 4; i++)H.undo();
    
  H.print();
  return 0;
}

