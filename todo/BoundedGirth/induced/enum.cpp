#include<vector>
#include<iostream>

#include"enum.hpp"
#include"graph.hpp"

using bigint = long long int;
std::vector<bigint> ans;

void RecELG(Graph &g){
  // g.print();
  if(g.cand.empty()){
    ans[g.CurrentSolutionSize()]++;
    return;
  }
  int v = *g.cand.begin();
  g.cand.erase(g.cand.begin());
  
  g.erase(v);
  RecELG(g);
  g.used[v] = false;
  g.NextCand(v);
  RecELG(g);
  g.restore(v);
}

std::vector<bigint> ELGMain(Graph &g){
  ans.resize(g.size() + 1, 0);
  ans[0] = 1;
  for (int i = 0; i < g.size(); i++) {
    g.NextCand(i);
    RecELG(g);
    g.restore(i);
    // g.print();
    g.erase(i);
  }
  return ans;
}
