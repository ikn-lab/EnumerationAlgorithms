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
  solution.init(tmp), cand.init(tmp), is_not_pv.init(tmp);
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i))domList[i].init(H[i]);
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
    back[0][i] = G[i].back().to;
    back[1][i] = G[i][G[i].GetPrev(G[i].GetPrev(G[i].end()))].to;
  }
  
  //テスト用プリント処理
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
  std::cout << "dominated: ";
  for (int i = 0; i < n; i++) {
    std::cout << dominated[i] << " ";
  }
  std::cout << std::endl;
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
  // result[solution.size()]++;
  int FW_cnt = 0, cand_cnt = 0, dom_cnt = 0, C_cnt = 0, last = cand.end();
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
  int store;
  for (int i = cand.back(); i != cand.end();) {
    cand_cnt++;
    int v = last = i, npv = 1;
    solution.remove(v);
    i = cand.remove(v);
    is_not_pv.remove(v);
    int size = diff[depth].size();
    store    = updateCand(v, npv);
    updateDomList(v, size);
    if(cand.size() != 0) depth++, Enumerate(), depth--;
    else if(is_not_pv.empty()) result[solution.size()]++;
    solution.undo();
    for (int j = 0; j < store; j++) cand.undo();
    for (int j = 0; j < npv; j++) is_not_pv.undo();
    
    for (int j = 0; j < FW[v].maxSize(); j++) {
      int rev = G.GetRev(G[v][j].id, v);
      domList[v].remove(j);
      domList[G[v][j].to].add(rev);
    }
    bool minimal = true;
    for (int j = 0; j < FW[v].maxSize(); j++) {
      int u = G[v][j].to;
      if(solution.member(u)){
        bool neighbor = false;
        for (int k = 0; k < G[u].size(); k++) {
          int w = G[u][k].to;
          if(solution.member(w))continue;
          neighbor |= (domList[w].size() <= 200);
        }
        minimal &= neighbor;
      }else{
        for (int k = domList[u].begin(); k != domList[u].end(); k = domList[u].GetNext(k)) {
          int w = domList[u][k].to;
          if(not is_not_pv.member(w))continue;
          bool neighbor = false;
          int sol = 0;
          for (int l = 0; l < G[w].size(); l++) {
            int z = G[w][l].to;
            if(not solution.member(z)){
              neighbor |= (domList[z].size() <= 200);
            }else if(not cand.member(z)){
              sol++;
            }
          }
          minimal &= (neighbor or (sol == 0));
        }
      }
    }
    if(not minimal) break;      
  }
  for (int i = 0; i < FW_cnt; i++) FW.undo();
  for (int i = 0; i < C_cnt; i++) C.undo();
  for (int i = 0; i < cand_cnt; i++) cand.undo();

  int loop = diff[depth].size();
  for (int l = 0; l < loop; l++) {
    int u = diff[depth][0];
    // 頂点uを候補集合に戻す．
    counter[u]--, diff[depth].pop();
    for (int i = 0; i < FW[u].maxSize(); i++) {
      edge e  = FW[u][i];
      int rev = G.GetRev(G[u][i].id, u);
      // uを候補集合に戻す．
      domList[e.to].remove(rev);
      domList[u].remove(i);
      dominated[e.to]++;
    }
  }

  
  for (int i = last; i != cand.end(); i = cand.GetNext(i)) {
    for (int j = 0; j < FW[i].maxSize(); j++) {
      edge e =  G[i][j];
      dominated[e.to]++;
      int rev = G.GetRev(e.id, i);
      domList[e.to].remove(rev);
      domList[i].remove(j);
    }
  }
}

int EDS::updateCand(int v, int &npv){
  int res = cand.size();
  int v_dom = 0, x = -1;
  for (int i = 0; i < FW[v].maxSize(); i++) {
    int u = G[v][i].to;
    if(solution.member(u)){
      v_dom++, x = u;
      if(domList[u].size() == 0 and back[0][u] == v and is_not_pv.member(u)) {
        int cnt = 0;
        //ここはあとで高速化しないと計算量が悪化している．
        for (int k = 0; k < FW[u].maxSize(); k++) cnt += solution.member(G[u][k].to);
        if(cnt == 0){
          is_not_pv.remove(u);
          npv++;
        }
      }
      if(domList[u].size() == 1 and back[0][u] == v and domList[u][domList[u].begin()].to == v and is_not_pv.member(u)){
        int cnt = 0;
        for (int k = 0; k < FW[u].maxSize(); k++) cnt += solution.member(G[u][k].to);
        if(cnt == 0){
          is_not_pv.remove(u);
          npv++;
        }
      }
      continue; 
    }
    
    if(domList[u].size() == 1 and back[0][u] == v and is_not_pv.member(domList[u][domList[u].begin()].to)){
      is_not_pv.remove(domList[u][domList[u].begin()].to);
      npv++;
    }
    if(domList[u].size() == 2 and back[0][u] == v){
      int w = domList[u].begin(), z = domList[u].GetNext(w);
      w = domList[u][w].to, z = domList[u][z].to;
      if(w == v and is_not_pv.member(z)) is_not_pv.remove(z), npv++;
      if(z == v and is_not_pv.member(w)) is_not_pv.remove(w), npv++;
    }
    
    int a = domList[u].back().to;
    int b = domList[u][domList[u].GetPrev(domList[u].GetPrev(domList[u].end()))].to;
    int mini = std::min(a, b), maxi = std::max(a, b);
    if(cand.member(back[0][u]) and back[1][u] == v and
       (domList[u].empty() or
        (domList[u].size() == 2 and mini == back[0][u] and maxi == back[1][u]) or
        (domList[u].size() == 1 and (domList[u].back().to == back[0][u] or domList[u].back().to == back[1][u])))){
      cand.remove(back[0][u]);
      is_not_pv.remove(back[0][u]);
      if(counter[back[0][u]] == 0) diff[depth].push(back[0][u]);
      counter[back[0][u]]++;
    }
  }
  for (int i = C[v].begin(); i != C[v].end(); i = C[v].GetNext(i)){
    int u = C[v][i].to;
    if(back[0][u] < u)continue;
    if(FW[u].size() == 1 and FW[u][FW[u].begin()].to == v and cand.member(u)){
      cand.remove(u);  
      is_not_pv.remove(u);
      if(counter[u] == 0) diff[depth].push(u);
      counter[u]++;
    }
  }

  if(v_dom == 0 and G[v].size() - FW[v].maxSize() == 1 and cand.member(back[0][v])){
    edge e = C[v].back();
    cand.remove(e.to);
    is_not_pv.remove(e.to);
    if(counter[e.to] == 0) diff[depth].push(e.to);
    counter[e.to]++;
  }
  if(v_dom == 1 and G[v].size() == FW[v].maxSize() and is_not_pv.member(x)){
    is_not_pv.remove(x);
    npv++;
  }
  npv += res - cand.size();
  return res - cand.size();
}

void EDS::updateDomList(int v, int size){
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
}

void EDS::print(){
  int sum = 0, n = G.size();
  for (int i = 0; i <= n; i++) sum += result[i];
  std::cout << "sum:" << sum << std::endl;
  std::cout << "size:" << std::endl;
  for (int i = 0; i <= n; i++) {
    std::cout << i << ":" << result[i] << std::endl;
  }
  // std::cout << "Graph G" << std::endl;
  // for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
  //   std::cout << i << ":";
  //   for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
  //     std::cout <<  G[i][j].to << " ";
  //   }
  //   std::cout << std::endl;
  // }
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
