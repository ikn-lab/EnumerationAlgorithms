#include<iostream>
#include<vector>

#include"List.hpp"
#include"Graph.hpp"

int main(){
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<edge> > G(n);
  std::cout << G.size() << std::endl;
  for (int i = 0; i < m; i++) {
    edge e;
    std::cin >> e.u >> e.v;
    e.cost = 1;
    e.id = i;
    G[e.u].push_back(e);
    G[e.v].push_back(edge(e.v, e.u, i, e.cost));
  }
  Graph H(G);
  H.print();
  // H.undo();
  return 0;
}
