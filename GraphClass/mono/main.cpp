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
    std::cin >> e.from >> e.to;
    e.cost = 1;
    e.id = i;
    G[e.from].push_back(e);
    G[e.to].push_back(edge(e.to, e.from, i, e.cost));
  }
  Graph H(G);
  H.print();
  for (int i = 0; i < 4; i++) {
    H.RemoveEdge(i*2);
  }
  H.print();
  return 0;
}

