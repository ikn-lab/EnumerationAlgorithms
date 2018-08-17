#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>

#include"Graph.hpp"
#include"Digraph.hpp"
#include"Enum.hpp"

#define INF 1e9
using bigint = long long int;


EDS::EDS(std::vector<std::vector<edge> > H){
  ordering(H);
  int n = H.size();
  G.init(H), C.init(H);
  domList.resize(H.size());
  result.resize(G.size() + 1, 0);
  dominated.resize(G.size());
  counter.resize(G.size(), 0);
  diff.resize(G.size());
  std::vector<std::vector<edge> > tmpG(G.size());
  int num_edge = 0;
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
    diff[i].resize(n);
    for (int j = G[i].begin(); j != G[i].end() and G[i][j].to > i; j = G.GetNext(j)) {
      edge e  = G[i][j];
      e.id = num_edge++;
      tmpG[i].push_back(e);
      dominated[e.to]++;
    }
  }
  FW.init(tmpG);
  std::vector<int> tmp;
  for (int i = 0; i < G.size(); i++) tmp.push_back(i);
  solution.init(tmp), cand.init(tmp);
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i))domList[i].init(H[i]);
  std::cout << "G      :" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << "trans G:" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << ord[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << ord[i] << ": ";
    for (int j = G[i].begin(); j < G[i].end(); j = G[i].GetNext(j)) {
      std::cout << ord[G[i][j].to] << " ";
    }
    std::cout << std::endl;
  }
  G.print();
}

void EDS::ordering(std::vector<std::vector<edge> > &H) {
  int n = H.size();
  std::vector<int> deg(n, 0);
  for (int i = 0; i < n; i++) deg[i] = H[i].size();
  ord.resize(n), reverse.resize(n);
  degeneracy = 0;
  for (int i = 0; i < n; i++) {
    int v = -1, tmp = INF;
    for (int j = 0; j < n; j++) {
      if(deg[j] < tmp) v = j, tmp = deg[j];
    }
    ord[i] = v;
    reverse[v] = i;
    degeneracy = std::max(degeneracy, deg[v]);
    deg[v] = INF;
    for (int j = 0; j < H[v].size(); j++) deg[H[v][j].to]--;
  }
  std::vector<std::vector<edge> > tmp(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < H[ord[i]].size(); j++) {
      edge e = H[ord[i]][j];
      e.from = reverse[e.from];
      e.to   = reverse[e.to];
      tmp[i].push_back(e);
    }
  }
  for (int i = 0; i < n; i++) std::sort(tmp[i].begin(), tmp[i].end());
  H = tmp;
}

bool checkDominatingSet(Graph &G, List<int> &solution){
  int n = G.size();
  std::vector<int> dom(n, 0);
  for (int i = 0; i < n; i++) {
    if(not solution.member(i))continue;
    dom[i]++;
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      dom[G[i][j].to]++;
    }
  }
  bool f = false;
  for (int i = 0; i < n; i++) {
    if(dom[i] == 0) {
      f = true;
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;
  if(f)return false;
  return true;
}

void EDS::Enumerate(){
  result[solution.size()]++;
  if(cand.size() == 0) return;
  int FW_cnt = 0, cand_cnt = cand.size(), dom_cnt = 0, C_cnt = 0;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    for (int j = FW[i].begin(); j != FW[i].end(); j = FW[i].GetNext(j)) {
      int u = FW[i][j].to;
      if(solution.member(u))continue;
      j = FW.RemoveEdge(FW[i][j].id);
      FW_cnt++;
    }
    for (int j = C[i].begin(); j != C[i].end(); j = C[i].GetNext(j)) {
      int u = C[i][j].to;
      if(cand.member(u))continue;
      j = C.RemoveEdge(C[i][j].id, i);
      C_cnt++;
    }
  }

  int store;
  for (int i = cand.back(); i != cand.end();) {
    int v = i;
    solution.remove(v);
    i = cand.remove(v);
    int size = diff[depth].size();
    store    = updateCand(v);
    updateDomList(v, size);
    depth++;
    Enumerate();
    depth--;
    solution.undo();
    for (int j = 0; j < store; j++) cand.undo();
    for (int j = G[v].begin(); v < G[v][j].to and j != G[v].end(); j = G[v].GetNext(j)) {
      int rev = G.GetRev(G[v][j].id, v);
      if(domList[v].member(j)) domList[v].remove(j);
      domList[G[v][j].to].add(rev);
    }
  }
  for (int i = 0; i < FW_cnt; i++) FW.undo();
  for (int i = 0; i < C_cnt; i++) C.undo();
  for (int i = 0; i < cand_cnt; i++) cand.undo();
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    for (int j = G[i].begin(); i < G[i][j].to and j != G[i].end(); j = G[i].GetNext(j)) {
      dominated[G[i][j].to]++;
      edge e =  G[i][j];
      int rev = G.GetRev(e.id, i);
      if(domList[e.to].member(rev))domList[e.to].remove(rev);
      if(domList[i].member(j))domList[i].remove(j);
    }
  }
  // std::cout << "backtrack. " << std::endl;
}

int EDS::updateCand(int v){
  int res = 0;
  bool v_dom = false;
  for (int i = G[v].begin(); v < G[v][i].to and i != G[v].end(); i = G[v].GetNext(i)){
    int u = G[v][i].to;
    if(solution.member(u)){
      v_dom = true;
      continue; 
    }
    if((domList[u].size() + dominated[u]) == 2 and cand.member(G[u].back().to)) {
      cand.remove(G[u].back().to);
      diff[depth].push(G[u].back().to);
      counter[G[u].back().to]++;
      res++;
    }
  }
  int C_back = 0;
  for (int i = C[v].GetPrev(C[v].end()); C[v][i].to < v and i != C[v].end(); i = C[v].GetPrev(i), C_back++){
    int u = C[v][i].to;
    if(G[u].back().to < u)continue;
    if(FW[u].size() == 1 and FW[u][FW[u].begin()].to == v and cand.member(u)){
      cand.remove(u);  
      diff[depth].push(u);
      counter[u]++;
      res++;
    }
  }

  //the vertex with v as a private vertex.
  if(not v_dom and (dominated[v] + domList[v].size()) == 1){
    edge e = C[v].back();
    if(cand.member(e.to)){
      cand.remove(e.to);
      diff[depth].push(e.to);
      counter[e.to]++;
      res++;
    }
  }
  return res;
}

int EDS::updateDomList(int v, int size){
  int res = 0;
  for (int s = 0; s < size; s++) {
    int u = diff[depth].front();
    diff[depth].pop();
    if(counter[u] == 2)continue;
    counter[u]--;
    for (int i = G[u].begin(); u < G[u][i].to and i != G[u].end(); i = G[u].GetNext(i)) {
      edge e = G[u][i];
      int rev = G.GetRev(e.id, u);
      if(domList[e.to].member(rev)) domList[e.to].remove(rev);
      if(domList[u].member(i)) domList[u].remove(i);
      dominated[e.to]++;
      res++;
    }
  }
  int loop = diff[depth].size();
  for (int l = 0; l < loop; l++) {
    int u = diff[depth].front();
    diff[depth].pop();
    diff[depth].push(u);
    if(counter[u] == 2){
      counter[u]--;
      continue;
    }
    if(u == v)continue;
    for (int i = G[u].begin(); u < G[u][i].to and i != G[u].end(); i = G[u].GetNext(i)) {
      edge e = G[u][i];
      int rev = G.GetRev(e.id, u);
      if(not domList[e.to].member(rev))domList[e.to].add(rev);
      dominated[e.to]--;
      res++;
    }
  }
  bool f = false;
  for (int i = G[v].begin(); v < G[v][i].to and i != G[v].end(); i = G[v].GetNext(i)) {
    f |= solution.member(G[v][i].to);
    dominated[G[v][i].to]--;
    int rev = G.GetRev(G[v][i].id, v);
    if(solution.member(G[v][i].to))domList[v].add(i);
    if(domList[G[v][i].to].member(rev)) domList[G[v][i].to].remove(rev);
    res++;
  }
  if(dominated[v] == 1 and not f and not domList[v].member(C[v].GetPrev(C[v].end()))) {
    domList[v].add(C[v].GetPrev(C[v].end())); 
  }
  return res;
}

void EDS::print(){
  int sum = 0, n = G.size();
  for (int i = 0; i <= n; i++) sum += result[i];
  std::cout << "sum:" << sum << std::endl;
  std::cout << "size:" << std::endl;
  for (int i = 0; i <= n; i++) {
    std::cout << i << ":" << result[i] << std::endl;
  }
  std::cout << "Graph G" << std::endl;
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
    std::cout << i << ":";
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      std::cout <<  G[i][j].to << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "dominated: ";
  for (int i = 0; i < dominated.size(); i++) {
    std::cout << dominated[i] << " ";
  }
  std::cout << std::endl;
}

void EDS::printDomList(){
  for (int i = 0; i < domList.size(); i++) {
    std::cout << "domList[" << i << "]: ";
    for (int j = domList[i].begin(); j != domList[i].end(); j = domList[i].GetNext(j)) {
      std::cout << domList[i][j].to << " ";
    }
    std::cout << std::endl;
  }
}

void EDS::printSolution(){
  std::cout << "solution: ";
  for (int i = solution.begin(); i != solution.end(); i = solution.GetNext(i)) {
    // std::cout << ord[i] << " ";
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

void EDS::printCand(){
  std::cout << "cand    : ";
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
