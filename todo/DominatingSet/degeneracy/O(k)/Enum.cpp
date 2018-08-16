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
  revDomList.resize(H.size());
  result.resize(G.size() + 1, 0);
  dominated.resize(G.size());
  counter.resize(G.size(), 0);
  diff.resize(G.size());
  std::vector<std::vector<edge> > tmpG(G.size());
  int num_edge = 0;
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
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
  printSolution();
  printCand();
  result[solution.size()]++;
  if(not checkDominatingSet(G, solution)){
    std::cerr << "error: not dominating set " << std::endl;
    printSolution();
    exit(1);
  }
  
  if(cand.size() == 0) {
    std::cout << "backtrack" << std::endl;
    return;
  }
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
  int store, log = domLog.size();
  for (int i = cand.back(); i != cand.end();) {
    int v = i;
    solution.remove(v);
    i = cand.remove(v);
    // diff[depth].push(v);
    // counter[v]++;
    int size = diff[depth].size();
    store   = updateCand(v);
    updateDomList(v, size);
    depth++;
    Enumerate();
    depth--;
    solution.undo();
    for (int j = 0; j < store; j++) cand.undo();
    printSolution();
    std::cout << "current vertex:" << v << std::endl;
    printCand();
    printDomList();
    for (int j = G[v].begin(); v < G[v][j].to and j != G[v].end(); j = G[v].GetNext(j)) {
      int rev = G.GetRev(G[v][j].id, v);
      if(domList[v].member(j)) domList[v].remove(j);
      domList[G[v][j].to].add(rev);
      revDomList[v].push(j);
    }
    // for (int j = C[v].begin(); j != C[v].end(); j = C[v].GetNext(j)) {
      // if(domList[v].member(j)){
      //   std::cout << "v:" << v << " memver:" << j << std::endl;
      //   std::cout << "from:" << domList[v][j].from << " to:" << domList[v][j].to  << std::endl;
      //   domList[v].remove(j);
      // }
    // }
    std::cout << "endddd" << std::endl;
    printDomList();
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
  // while(not revDomList[i].empty()) {
  //   int j = revDomList[i].front();
  //   int rev = G.GetRev(G[i][j].to, i);
  //   domList[G[i][j].to].remove(rev);
  //   revDomList[i].pop();
  // } 
  std::cout << "backtrack. " << std::endl;
}

int EDS::updateCand(int v){
  std::cout << "start updateCand" << std::endl;
  printCand();
  int res = 0;
  //forward
  std::cout << "forward" << std::endl;
  bool v_dom = false;
  for (int i = G[v].begin(); v < G[v][i].to and i != G[v].end(); i = G[v].GetNext(i)){
    int u = G[v][i].to;
    std::cout << "forward:" << u << std::endl;
    if(solution.member(u)){
      v_dom = true;
      continue; 
    }
    std::cout << "dominated:";
    for (int i = 0; i < dominated.size(); i++) {
      std::cout << dominated[i] << " ";
    }
    std::cout << std::endl;
    if(not domList[u].empty() or dominated[u] > 2) continue;
    if(cand.member(G[u].back().to)) {
      std::cout << "remove: FW:" << u << " " << G[u].back().to << std::endl;
      cand.remove(G[u].back().to);
      diff[depth].push(G[u].back().to);
      counter[G[u].back().to]++;
      res++;
    }
  }
  //back
  std::cout << "back" << std::endl;
  std::cout << "back v:" << v << std::endl;
  std::cout << "C:" << std::endl;
  C.print();
  for (int i = C[v].GetPrev(C[v].end()); C[v][i].to < v and i != C[v].end(); i = C[v].GetPrev(i)){
    int u = C[v][i].to;
    std::cout << "back u:" << u << std::endl;
    if(G[u].back().to < v)continue;
    std::cout << "FW size:" << FW[u].size() << std::endl;
    for (int j = FW[u].begin(); j != FW[u].end(); j = FW[u].GetNext(j)) {
      std::cout << FW[u][j].to << "  ";
    }
    std::cout << std::endl;
    if(FW[u].size() == 1 and FW[u][FW[u].begin()].to == v and cand.member(u)){
      std::cout << "remove C:" << u << std::endl;
      cand.remove(u);  
      diff[depth].push(u);
      counter[u]++;
      res++;
    }
  }

  //the vertex with v as a private vertex.
  // if(not v_dom and dominated[v] == 1 and C[v].size() == 1){
  if(not v_dom and C[v].size() == 1){
    edge e = C[v][C[v].begin()];
    if(cand.member(e.to)){
      cand.remove(e.to);
      diff[depth].push(e.to);
      counter[e.to]++;
      res++;
    }
    // for (int i = G[e.to].begin(); i != G[e.to].end(); i = G[e.to].GetNext(i)) {
    //   dominated[G[e.to][i].to]--;
    // }
  }
  // printCand();
  std::cout << "end updateCand" << std::endl;
  return res;
}

int EDS::updateDomList(int v, int size){
  std::cout << "start udpateDomlist" << std::endl;
  printDomList();
  int res = 0, hoge = diff[depth].size();
  for (int i = 0; i < G.size(); i++) {
    if(i == 0)std::cout << "counter: "; 
    std::cout << counter[i] << " ";
    if(i == G.size() - 1)std::cout << std::endl;
  }
  for (int i = 0; i < hoge; i++) {
    if(i == 0)std::cout << "diff[" << depth << "]:";                
    std::cout << diff[depth].front() << " ";
    diff[depth].push(diff[depth].front());
    diff[depth].pop();
  }
  std::cout << std::endl;
  for (int s = 0; s < size; s++) {
    int u = diff[depth].front();
    diff[depth].pop();
    std::cout << "counter[" << u << "]:" << counter[u] << std::endl;
    counter[u]--;
    if(counter[u] == 1)continue;
    if(counter[u] != 0){
      std::cout << "error: counter" << std::endl;
      exit(1);
    }
    for (int i = G[u].begin(); u < G[u][i].to and i != G[u].end(); i = G[u].GetNext(i)) {
      edge e = G[u][i];
      int rev = G.GetRev(e.id, u);
      std::cout << "e.from:" << e.from <<  " e.to:" << e.to << " rev:" << rev << std::endl;
      if(domList[e.to].member(rev)) domList[e.to].remove(rev);
      if(domList[u].member(i)) domList[u].remove(i);
      dominated[e.to]++;
      domLog.push(pii(e.to, 1));
      res++;
      // revDomList[u].push(i);
    }
  }
  std::cout << "end size:udpateDomList" << std::endl;
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
    std::cout << "vertex:" << u << std::endl;
    printCand();
    printSolution();
    std::cout << "u:" << u << " v:" << v << std::endl;
    for (int i = G[u].begin(); u < G[u][i].to and i != G[u].end(); i = G[u].GetNext(i)) {
      edge e = G[u][i];
      int rev = G.GetRev(e.id, u);
      std::cout << "to:" << e.to << " rev:" << rev<< std::endl; 
      std::cout << domList[e.to].size() << std::endl;
      if(not domList[e.to].member(rev))domList[e.to].add(rev);
      std::cout << domList[e.to].size() << std::endl;
      revDomList[u].push(i);
      dominated[e.to]--;
      domLog.push(pii(e.to, -1));
      res++;
    }
    std::cout << "hoge" << std::endl;
  }
  std::cout << "hoge" << std::endl;
  bool f = false;
  for (int i = G[v].begin(); v < G[v][i].to and i != G[v].end(); i = G[v].GetNext(i)) {
    f |= solution.member(G[v][i].to);
    if(counter[v] == 0)dominated[G[v][i].to]--;
    domLog.push(pii(-G[v][i].to - 1, -1));
    int rev = G.GetRev(G[v][i].id, v);
    if(solution.member(G[v][i].to))domList[v].add(i);
    if(domList[G[v][i].to].member(rev)) domList[G[v][i].to].remove(rev);
    domLog.push(pii(v, 0));
    // domLog.push(G[v][i].to);
    res++;
  }
  std::cout << "C size:" << C[v].size() << std::endl;
  if(dominated[v] == 1 and not f and not domList[v].member(C[v].GetPrev(C[v].end()))) domList[v].add(C[v].GetPrev(C[v].end()));
  printDomList();
  std::cout << "end updateDomList" << std::endl;
  return res;
}

// void EDS::restore(int cand_cnt, int dom_cnt){
//   for (int i = 0; i < cand_cnt; i++) cand.undo(), diff.undo();
//   for (int i = 0; i < dom_cnt; i++) domList.undo();
// }

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

