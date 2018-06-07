#include<iostream>
#include<vector>
#include<memory>

#include"Element.hpp"
#include"AddibleList.hpp"
#include"AddibleDigraph.hpp"
#include"AddibleGraph.hpp"
// #include"Graph.hpp"

int main(){
  std::vector<std::vector<edge> > tmp;
  int n, m;
  std::cin >> n >> m;
  tmp.resize(n);
  for (int i = 0; i < m; i++){
    int x, y;
    std::cin >> x >> y;
    tmp[x].push_back(edge(x, y, i));
    tmp[y].push_back(edge(y, x, i));
  } 
  AddibleGraph G;
  G.init(tmp);
  G.print();
  G.AddEdge(3);
  G.print();
  G.undo();
  G.print();
  return 0;
}
