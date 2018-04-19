#include<iostream>
#include<vector>
#include<memory>

#include"Graph.hpp"
#include"Enum.hpp"

using bigint = long long int;

EDS::EDS(std::vector<std::vector<edge> > _G){
  G.init(_G), C.init(_G), FW.init(_G), domList.init(_G);
  std::vector<int> tmp;
  for (int i = 0; i < G.size(); i++) tmp.push_back(i);
  solution.init(tmp), cand.init(tmp);
  diff.init(tmp, tmp.size());
  result    = std::make_unique<bigint[]>(G.size() + 1);
  dominated = std::make_unique<int[]>(G.size());
  for (int i = 0; i <= G.size(); i++) result[i] = 0;
  for (int i = 0; i < G.size(); i++)dominated[i] = _G[i].size() + 1;
}

void EDS::Enumerate(){
  std::cout << "depth:" << depth << std::endl;
  result[solution.size()]++;
  int FW_cnt = 0, cand_cnt = cand.size(), dom_cnt = 0, C_cnt = 0;
  for (int i = FW.begin(); i != FW.end(); i = FW.GetNext(i)) {
    for (int j = FW[i].begin(); j != FW[i].end(); j = FW[i].GetNext(j)) {
      int u = FW[i][j].to;
      if(solution.member(u))continue;
      FW.RemoveEdge(FW[i][j].id);
      FW_cnt++;
    }
  }
  for (int i = C.begin(); i != C.end(); i = C.GetNext(i)) {
    for (int j = C[i].begin(); i < j; j = C[i].GetNext(j)) {
      if(cand.member(C[i][j].to))continue;
      C.RemoveEdge(C[i][j].id);
      C_cnt++;
    }
  }
  int tmp, prev = 0;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    int v = i;
    i = cand.remove(v);
    tmp = updateCand(v);
    dom_cnt = updateDomList(v);
    depth++;
    Enumerate();
    depth--;
    for (int j = 0; j < tmp; j++) cand.undo();
    for (int j = 0; j < dom_cnt; j++) domList.undo();
    for (int j = 0; j < prev; j++) diff.undo();
    prev = tmp;
    for (int j = C[v].begin(); v < j; j = C[v].GetNext(j)) {
      j = C.RemoveEdge(C[v][j].id);
    }
  }
  for (int i = 0; i < FW_cnt; i++) FW.undo();
  for (int i = 0; i < cand_cnt; i++) cand.undo();
  for (int i = 0; i < prev; i++) diff.undo();
}

int EDS::updateCand(int v){
  int res = 0;
  for (int i = FW[v].begin(); i != FW[v].end(); i = FW[v].GetNext(i)){
    int u = FW[v][i].to;
    if(solution.member(u))continue;
    if(not domList[u].empty() or C[u].size() != 2)continue;
    cand.remove(C[u].back().to);
    if(not diff.member(u))diff.add(u, depth);
    else diff.remove(u, depth);
    res++;
  }
  
  for (int i = C[v].GetPrev(C[v].end()); C[v][i].to < v; i = C[v].GetPrev(i)){
    int u = C[v][i].to;
    if(not domList[u].empty() or FW.size() != 0)continue;
    cand.remove(u);
    if(not diff.member(u))diff.add(u, depth);
    else diff.remove(u, depth);
    res++;
  }
  return res;
}

int EDS::updateDomList(int v){
  int res = 0;
  for (int u = diff.begin(); u != diff.end(); u = diff.GetNext(u)) {
    for (int w = G[u].begin(); u < G[u][w].to; w = G[u].GetNext(u)) {
      edge e = G[u][w];
      int pos = domList.rev(e.id, e.from);
      if(domList[w].member(pos))continue;
      if(not cand.member(u))domList.AddEdge(e.id);
      else domList.RemoveEdge(e.id);
      res++;
    }
  }
  for (int u = G[v].begin(); v < u; u = G[v].GetNext(u)) {
    if(solution.member(G[v][u].to)){
      domList.AddEdge(G[v][u].id);
      res++;
    }
  }
  return res;
}

// void EDS::restore(int cand_cnt, int dom_cnt){
//   for (int i = 0; i < cand_cnt; i++) cand.undo(), diff.undo();
//   for (int i = 0; i < dom_cnt; i++) domList.undo();
// }

void EDS::print(){
  int sum = 0, n = G.size();
  for (int i = 0; i < n; i++) sum += result[i];
  std::cout << "sum:" << sum << std::endl;
  std::cout << "size:" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << i << ":" << result[i] << std::endl;
  }
}
