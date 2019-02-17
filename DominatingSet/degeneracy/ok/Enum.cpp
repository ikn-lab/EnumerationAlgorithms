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
  G.init(H);
  domList.resize(H.size());
  result.resize(G.size() + 1, 0);
  dominated.resize(G.size());
  counter.resize(G.size(), 0);
  diff.resize(G.size());
  back.resize(2);
  back[0].resize(G.size());
  back[1].resize(G.size());
  std::vector<std::vector<edge> > tmpFW(G.size()), tmpC(G.size());
  int num_fw_edges = 0, num_c_edges = 0;
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
    diff[i].resize(n);
    for (int j = G[i].begin(); j != G[i].end(); j = G.GetNext(j)) {
      edge e  = G[i][j];
      if(i < G[i][j].to){
        e.id = num_fw_edges++;
        tmpFW[i].push_back(e);
        dominated[e.to]++;
      }else{
        e.id = num_c_edges++;
        tmpC[i].push_back(e);
      }
    }
  }
  FW.init(tmpFW), C.init(tmpC);
  std::vector<int> tmp;
  for (int i = 0; i < G.size(); i++) tmp.push_back(i);
  solution.init(tmp), cand.init(tmp);
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i))domList[i].init(H[i]);
  // std::cout << "G      :" << std::endl;
  // for (int i = 0; i < n; i++) {
  //   std::cout << i << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "trans G:" << std::endl;
  // for (int i = 0; i < n; i++) {
  //   std::cout << ord[i] << " ";
  // }
  // std::cout << std::endl;
  // for (int i = 0; i < n; i++) {
  //   std::cout << ord[i] << ": ";
  //   for (int j = G[i].begin(); j < G[i].end(); j = G[i].GetNext(j)) {
  //     std::cout << ord[G[i][j].to] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << "G: " << std::endl;
  // G.print();
  // std::cout << "FW: " << std::endl;
  // FW.print();
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
    back[0][i] = G[i].back().to;
    back[1][i] = G[i][G[i].GetPrev(G[i].GetPrev(G[i].end()))].to;
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
  bool f = false;
  for (int i = 0; i < n; i++) {
    if(dom[i] == 0) {
      f = true;
      std::cout << i << " ";
    }
    if(i == n - 1 and f)std::cout << std::endl;
  }
  if(f)return false;
  return true;
}

void EDS::Enumerate(){
  result[solution.size()]++;
  sum++;
  // if(not checkDominatingSet(G, solution)){
  //   std::cout << "error. " << std::endl;
  //   printSolution();
  //   solution.undo();
  //   printSolution();
  //   solution.undo();
  //   printSolution();
  //   solution.undo();
  //   printSolution();
  //   for (int i = 0; i < G[5].size(); i++) {
  //     if(i == 0)std::cout << "G[" << 5 <<  "]:";
  //     std::cout << G[5][i].to << " ";
  //     if(i == G[5].size() - 1)std::cout << std::endl;
  //   }
  //   exit(1);
  // }
  int FW_cnt = 0, cand_cnt = cand.size(), dom_cnt = 0, C_cnt = 0;
  // std::cout << "start prepro" << std::endl;
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
      j = C.RemoveEdge(C[i][j].id);
      C_cnt++;
    }
  }
  // std::cout << "end prepro" << std::endl;  
  int store;
  for (int i = cand.back(); i != cand.end();) {
    int v = i;
    solution.remove(v);
    i = cand.remove(v);
    int size = diff[depth].size();
    store    = updateCand(v);
    updateDomList(v, size);
    depth++;
    if(cand.size() != 0){
      Enumerate();
    }else{
      result[solution.size()]++;
      sum++;
    }
    if(sum >= 1e5) return;
    depth--;
    solution.undo();
    for (int j = 0; j < store; j++) cand.undo();
    // std::cout << "start next" << std::endl;
    for (int j = 0; j < FW[v].maxSize(); j++) {
      int rev = G.GetRev(G[v][j].id, v);
      domList[v].remove(j);
      domList[G[v][j].to].add(rev);
    }
    // std::cout << "end next" << std::endl;
  }
  for (int i = 0; i < FW_cnt; i++) FW.undo();
  for (int i = 0; i < C_cnt; i++) C.undo();
  for (int i = 0; i < cand_cnt; i++) cand.undo();
  
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    for (int j = 0; j < FW[i].maxSize(); j++) {
      edge e =  G[i][j];
      dominated[e.to]++;
      int rev = G.GetRev(e.id, i);
      domList[e.to].remove(rev);
      domList[i].remove(j);
    }
  }
  // std::cout << "backtrack" << std::endl;
}

int EDS::updateCand(int v){
  // std::cout << "start cand" << std::endl;
  int res = cand.size();
  bool v_dom = false;
  bool f = false;
  int c = 0;
  for (int i = 0; i < FW[v].maxSize(); i++) {
    int u = G[v][i].to;
    f = false;
    c = 0;
    if(solution.member(u)){
      v_dom = true;
      continue; 
    }
    // for (int j = 0; j < G[u].size(); j++) {
    //   f |= (solution.member(G[u][j].to) and not cand.member(G[u][j].to));
    //   c += (cand.member(G[u][j].to));
    // }
    // std::cout << "v:" << v << " u:" << u << std::endl;
    // printSolution();
    // printCand();
    // std::cout << "f:" << f << " c:" << c << std::endl;
    // if(not f and c == 1){
    // if(v == 3 and u == 23) {
    //   std::cout << "domList[" << u << "]: ";
    //   for (int i = domList[u].begin(); i != domList[u].end(); i = domList[u].GetNext(i)) {
    //     std::cout << domList[u][i].to << " ";
    //   }
    //   std::cout << std::endl;
    //   std::cout << "domList[" << u << "]: ";
    //   for (int i = 0; i != domList[u].end(); i++) {
    //     std::cout << domList[u][i].to << " ";
    //   }
    //   std::cout << std::endl;
    //   std::cout << back[0][u] << std::endl;
    // }
    // if(cand.member(back[0][u]) and back[1][u] == v and
    //    (domList[u].empty() or (domList[u].size() == 1 and (domList[u].back().to == v or domList[u].back().to == back[0][u])))){
    int a = domList[u].back().to;
    int b = domList[u][domList[u].GetPrev(domList[u].GetPrev(domList[u].end()))].to;
    // std::cout << "a:" << a << " b:" << b << std::endl;
    int mini = std::min(a, b), maxi = std::max(a, b);
    if(cand.member(back[0][u]) and back[1][u] == v and
       (domList[u].empty() or
        (domList[u].size() == 2 and mini == back[0][u] and maxi == back[1][u]) or
        (domList[u].size() == 1 and (domList[u].back().to == back[0][u] or domList[u].back().to == back[1][u])))){
                                                           
      cand.remove(back[0][u]);
      if(counter[back[0][u]] == 0) diff[depth].push(back[0][u]);
      counter[back[0][u]]++;
    }
    // if(v == 3 and u == 23) printSolution(), printCand(), std::cout << std::endl;;
  }
  for (int i = C[v].begin(); i != C[v].end(); i = C[v].GetNext(i)){
    int u = C[v][i].to;
    if(back[0][u] < u)continue;
    f = false;
    c = 0;
    // for (int j = 0; j < G[u].size(); j++) {
    //   f |= (solution.member(G[u][j].to) and not cand.member(G[u][j].to));
    //   c += (cand.member(G[u][j].to));
    // }
    // if(not f and c == 0){
    if(FW[u].size() == 1 and FW[u][FW[u].begin()].to == v and cand.member(u)){
      cand.remove(u);  
      if(counter[u] == 0) diff[depth].push(u);
      counter[u]++;
    }
  }
  // f = false;
  // c = 0;
  // for (int j = 0; j < G[v].size(); j++) {
  //   f |= (solution.member(G[v][j].to) and not cand.member(G[v][j].to));
  //   c += (cand.member(G[v][j].to));
  // }
  // if(not f and c == 1){
  if(not v_dom and G[v].size() - FW[v].maxSize() == 1 and cand.member(back[0][v])){
    edge e = C[v].back();
    cand.remove(e.to);
    if(counter[e.to] == 0) diff[depth].push(e.to);
    counter[e.to]++;
  }
  // std::cout << "end cand" << std::endl;
  return res - cand.size();
}

void EDS::updateDomList(int v, int size){
  // std::cout << "start DomList" << std::endl;
  int loop = diff[depth].size();
  for (int l = 0; l < loop; l++) {
    int u = diff[depth].front();
    diff[depth].pop();
    if(counter[u] == 2){
      counter[u]--;
      diff[depth].push(u);
      continue;
    }
    if(l < size) counter[u]--;
    else  diff[depth].push(u); 
    for (int i = 0; i < FW[u].maxSize(); i++) {
      edge e = G[u][i];
      int rev = G.GetRev(e.id, u);
      if(l < size){
        domList[e.to].remove(rev);
        domList[u].remove(i);
        dominated[e.to]++;
      }else{
        domList[e.to].add(rev);
        dominated[e.to]--;
      }
    }
  }
  for (int i = 0; i < FW[v].maxSize(); i++) {
    edge e = G[v][i];
    dominated[e.to]--;
    if(solution.member(e.to))domList[v].add(i);
    int rev = G.GetRev(e.id, v);
    domList[e.to].remove(rev);
  }
  if((domList[v].size() + dominated[v]) == 1) {
    domList[v].add(C[v].GetPrev(C[v].end())); 
  }
  // std::cout << "end DomList" << std::endl;
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
  std::cout << "counter  : ";
  for (int i = 0; i < dominated.size(); i++) {
    std::cout << counter[i] << " ";
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
