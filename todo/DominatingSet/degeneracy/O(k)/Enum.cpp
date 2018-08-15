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
  std::cout << "ordering:" << std::endl;
  for (int i = 0; i < n; i++) {
    printf("%2d ", i);
  }
  std::cout << std::endl;
  for (int i = 0; i < n; i++) {
    printf("%2d ", ord[i]);
  }
  std::cout << std::endl;
  G.init(H), C.init(H);
  domList.resize(H.size());
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
  // FW.print();
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
  for (int i = 0; i < n; i++) {
    if(dom[i] == 0)return false;
  }
  return true;
}

void EDS::Enumerate(){
  printSolution();
  printCand();
  // printDomList();
  // std::cout << "depth:" << depth << std::endl;
  // std::cout << std::endl;
  result[solution.size()]++;
  // if(solution.size() == 2)printSolution();
  // printSolution();
  // printCand();
  if(not checkDominatingSet(G, solution)){
    std::cerr << "error. " << std::endl;
    printSolution();
    exit(1);
  }
  
  if(cand.size() == 0) {
    // std::cout << "backtrack" << std::endl;
    return;
  }
  // std::cout << "depth:" << depth << " solution size:" << solution.size() << std::endl;
  // printCand();
  int FW_cnt = 0, cand_cnt = cand.size(), dom_cnt = 0, C_cnt = 0;
  // std::cout << "FW" << std::endl;
  // FW.print();
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) { 
    // std::cout << "FW v:" << i << std::endl;
    for (int j = FW[i].begin(); j != FW[i].end(); j = FW[i].GetNext(j)) {
      int u = FW[i][j].to;
      if(solution.member(u))continue;
      // std::cout <<  "remove i:" << i << " j:" << FW[i][j].to << std::endl;
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
  // FW.print();
  // std::cout << std::endl;
  // std::cout << "C" << std::endl;
  // C.print();
  // std::cout << "branching" << std::endl;
  int store, log = domLog.size();
  for (int i = cand.back(); i != cand.end();) {
    int v = i;
    solution.remove(v);
    i = cand.remove(v);
    // diff[depth].push(u);
    // counter[v]++;
    // std::cout << "v:" << v << " i:" << i << std::endl;
    store   = updateCand(v);
    // std::cout << "bef" << std::endl;
    // printDomList();
    dom_cnt = updateDomList(v);
    
    // std::cout << "aft" << std::endl;
    // printDomList();
    depth++;
    Enumerate();
    // printSolution();
    // printCand();
    depth--;
    solution.undo();
    for (int j = 0; j < store; j++) cand.undo();
    for (int j = 0; j < dom_cnt; j++) {
      if(domLog.top().first < 0){
        dominated[-domLog.top().first + 1] -= domLog.top().second;
      }else{
        domList[domLog.top().first].undo();
        dominated[domLog.top().first] -= domLog.top().second;
      }
      domLog.pop();        
    }
    for (int j = G[v].begin(); v < G[v][j].to and j != G[v].end(); j = G[v].GetNext(j)) {
      int rev = G.GetRev(G[v][j].id, v);
      domList[G[v][j].to].add(rev);
      domLog.push(pii(G[v][j].to, 0));
    }
  }
  for (int i = 0; i < FW_cnt; i++) FW.undo();
  for (int i = 0; i < C_cnt; i++) C.undo();
  for (int i = 0; i < cand_cnt; i++) cand.undo();
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) 
    for (int j = G[i].begin(); i < G[i][j].to and j != G[i].end(); j = G[i].GetNext(j)) dominated[G[i][j].to]++;
  
  while(domLog.size() > log){
    domList[domLog.top().first].undo();    
    domLog.pop();
  }
  // std::cout << "backtrack. " << std::endl;
}

int EDS::updateCand(int v){
  int res = 0;
  //forward
  // std::cout << "forward" << std::endl;
  // std::cout << "updateCand:";
  // printCand();
  bool v_dom = false;
  for (int i = G[v].begin(); v < G[v][i].to and i != G[v].end(); i = G[v].GetNext(i)){
    int u = G[v][i].to;
    // std::cout << u << std::endl;
    // std::cout << "forward:" << u << std::endl;
    if(solution.member(u)){
      v_dom = true;
      continue; 
    }
    if(not domList[u].empty() or dominated[u] > 2) continue;
    if(cand.member(G[u].back().to)) {
      std::cout << "remove: FW:" << u << " " << G[u].back().to << std::endl;
      cand.remove(G[u].back().to);
      diff[depth].push(G[u].back().to);
      counter[C[u].back().to]++;
      // counter[C[u].back().to] = (counter[C[u].back().to] + 1)&1;
      res++;
    }
  }
  //back
  // std::cout << "back" << std::endl;
  std::cout << "back v:" << v << std::endl;
  printDomList();
  C.print();
  for (int i = C[v].GetPrev(C[v].end()); C[v][i].to < v and i != C[v].end(); i = C[v].GetPrev(i)){
    int u = C[v][i].to;
    std::cout << "back u:" << u << std::endl;
    if(not domList[u].empty() or G[u].back().to < v)continue;
    if(FW[u].size() == 1 and cand.member(u)){
      std::cout << "remove C:" << u << std::endl;
      cand.remove(u);  
      diff[depth].push(u);
      counter[u]++;
      // counter[u] = (counter[u] + 1)&1;
      res++;
    }
  }

  //the vertex with v as a private vertex.
  if(not v_dom and C[v].size() == 1){
    if(cand.member(C[v][C[v].begin()].to)){
      // std::cout << "vertex id:" << C[v][C[v].begin()].to << std::endl;
      cand.remove(C[v][C[v].GetPrev(C[v].end())].to);
      diff[depth].push(C[v][C[v].GetPrev(C[v].end())].to);
      counter[C[v][C[v].GetPrev(C[v].end())].to]++;
      res++;
    }
  }
  // printCand();
  return res;
}

int EDS::updateDomList(int v){
  int res = 0, loop = diff[depth].size();
  for (int l = 0; l < loop; l++) {
    int u = diff[depth].front();
    diff[depth].pop();
    counter[u]--;
    if(counter[u] != 0) {
      diff[depth].push(u);
      continue; 
    }
    for (int i = G[u].begin(); u < G[u][i].to and i != G[u].end(); i = G[u].GetNext(i)) {
      edge e = G[u][i];
      int rev = G.GetRev(e.id, u);
      // std::cout << "e.from:" << e.from <<  " e.to:" << e.to << " rev:" << rev << std::endl;
      if(not cand.member(u)) domList[e.to].add(rev), dominated[e.to]--, domLog.push(pii(e.to, -1));
      else domList[e.to].remove(rev), dominated[e.to]++, domLog.push(pii(e.to, 1));
      res++;
    }
  }
  for (int i = G[v].begin(); v < G[v][i].to and i != G[v].end(); i = G[v].GetNext(i)) {
    dominated[G[v][i].to]--;
    domLog.push(pii(-G[v][i].to - 1, -1));
    if(not solution.member(G[v][i].to))continue;
    // int rev = G.GetRev(G[v][i].id, v);
    domList[v].add(i);
    // domList[G[v][i].to].add(rev);
    domLog.push(pii(v, 0));
    // domLog.push(G[v][i].to);
    res++;
  }
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

