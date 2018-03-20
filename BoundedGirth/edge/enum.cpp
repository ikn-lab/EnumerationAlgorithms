#include<vector>
#include<iostream>

#include"enum.hpp"
#include"graph.hpp"
#include"edgelist.hpp"
// #define DEBUG

using bigint = long long int;
std::vector<bigint> ans;

void RecELG(Graph &G){
  // g.print();
#ifdef DEBUG
  std::cerr << "sol size:" << G.CurrentSolutionSize() << std::endl;
  std::cout << G.Cin.size()  << " " << G.Cout.size() << std::endl;
#endif  
  if(G.candEmpty()){
    ans[G.CurrentSolutionSize()]++;
    return;
  }
  edge e = G.GetCand();
  G[e.from].RemoveEdge(e.pos);
  // e.print();
  G[e.to].RemoveEdge(e.rev);
  RecELG(G);
  G[e.from].RestoreEdge();
  G[e.to].RestoreEdge();
  G.NextCand(e);
  RecELG(G);
  G.restore(e);
}

std::vector<bigint> ELGMain(Graph &G){
  ans.resize(G.size() + 1, 0);
  ans[0] = 1;
  for (int i = 0; i < G.size(); i++) {
    for (int j = G[i][0].next; j != G[i].end(); j=G[i][j].next) {
      edge &e = G[i][j];
      G.NextCand(e);
      RecELG(G);
#ifdef DEBUG
      std::cout << "end Rec" << std::endl;
#endif
      G.restore(e);
      // G.print();
      G[e.from].RemoveEdge(e.pos);
      G[e.to].RemoveEdge(e.rev);
    }
  }
  return ans;
}
