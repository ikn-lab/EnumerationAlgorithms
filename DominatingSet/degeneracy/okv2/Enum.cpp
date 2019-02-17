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
  //Hを縮退順に並び替える．  
  ordering(H);
  
  int n = H.size();

  //計算に必要な構造の初期化
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
  C2FW.resize(num_c_edges);
  FW2C.resize(num_fw_edges);
  FW.init(tmpFW), C.init(tmpC);
  for (int i = 0; i < FW.size(); i++) {
    for (int j = FW[i].begin(); j != FW[i].end(); j = FW[i].GetNext(j)) {
      int u = FW[i][j].to;
      for (int k = C[u].begin(); k != C[u].end(); k = C[u].GetNext(k)) {
        if(C[u][k].to == i)C2FW[C[u][k].id] = FW[i][j].id;
      }
    }
  }
  for (int i = 0; i < C.size(); i++) {
    for (int j = C[i].begin(); j != C[i].end(); j = C[i].GetNext(j)) {
      int u = C[i][j].to;
      for (int k = FW[u].begin(); k != FW[u].end(); k = FW[u].GetNext(k)) {
        if(FW[u][k].to == i)FW2C[FW[u][k].id] = C[i][j].id;
      }
    }
  }
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
    back[0][i] = G[i].back().to;
    back[1][i] = G[i][G[i].GetPrev(G[i].GetPrev(G[i].end()))].to;
  }
  std::vector<int> tmp;
  for (int i = 0; i < G.size(); i++) tmp.push_back(i);
  solution.init(tmp), cand.init(tmp);
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i))domList[i].init(H[i]);
  //初期化終了

  //テスト用プリント関数
  // std::cout << "C2FW:";
  // for (int i = 0; i < C2FW.size(); i++) {
  //   std::cout <<  C2FW[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "FW: " << std::endl;
  // FW.print();
  // std::cout << "C : " << std::endl;
  // C.print();
}

//Hを縮退順に並び替える関数: O(n^2)時間
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

//solutionがGのdominating setかどうかのチェック関数．テスト用の関数
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

//列挙のメイン関数
void EDS::Enumerate(){
  //大きさがsolution.size()のdominating setの発見
  result[solution.size()]++;
  
  //FW_cnt  : updateDomListでFW中の削除した辺の本数
  //cand_cnt: backtrackする際のcandをundoする回数
  //C_cnt   : updateCandでcandがremoveされた回数
  int FW_cnt = 0, cand_cnt = cand.size(), C_cnt = 0;
  for (int i = cand.back(); i != cand.end();) {
    int v = i;
    solution.remove(v);
    i = cand.remove(v);
    int size = diff[depth].size();
    C_cnt  = updateCand(v);
    FW_cnt = updateDomList(v, size);
    if(cand.size() != 0) depth++, Enumerate(), depth--;
    else result[solution.size()]++;
    solution.undo();
    for (int j = 0; j < C_cnt; j++) cand.undo();
    for (int j = 0; j < FW_cnt; j++) FW.undo();

    //Cの復元: この操作の後，C[u]はN(u)^{<u} \cap C(X)^{<v}と等しい
    for (int j = 0; j < diff[depth].size(); j++) {
      int u = diff[depth][j];
      // for (int k = FW[u].begin(); k != FW[u].end(); k = FW[u].GetNext(k)) {
      for (int k = 0; k < FW[u].maxSize(); k++) {
        edge e = FW[u][k];
        if(cand.member(e.to))C.AddEdge(FW2C[e.id]);
      }
    }
    // domListの復元: この操作の後，domList[u]はu \in Xに対し，
    // N(u)^{<u} \cap (X \ (cand \cup diff[depth]))と等しく，それ以外の頂点uでは
    // N(u) \cap (X \ (cand \cup diff[depth]))と等しい
    for (int j = 0; j < FW[v].maxSize(); j++) {
      int rev = G.GetRev(G[v][j].id, v);
      domList[v].remove(j);
      domList[G[v][j].to].add(rev);
    }
  }
  // backtrackの際の復元
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
  int res = cand.size();
  bool v_dom = false;
  // Del_2(X, v)の発見: vより番号の大きな支配集合に含まれない頂点uを参照する．
  // uがX/C(X)に支配されず，N(u) \cap C(X) = {u, v}なら，uをcandから削除する．
  for (int i = 0; i < FW[v].maxSize(); i++) {
    int u = G[v][i].to;
    if(solution.member(u)){
      v_dom = true;
      continue; 
    }
    int a = domList[u].back().to;
    int b = domList[u][domList[u].GetPrev(domList[u].GetPrev(domList[u].end()))].to;
    int mini = std::min(a, b), maxi = std::max(a, b);
    
    // N(u) \cap C(X) = {u, v}かどうかのチェック
    // domList中に消しっぱなしになっている頂点があるので，
    // domList[u]がemptyの場合，sizeが1もしくは2の場合の3パターンを試す必要がある．
    if((cand.member(back[0][u]) and back[1][u] == v) and
       (domList[u].empty() or
        (domList[u].size() == 1 and (a == back[0][u] or a == back[1][u])) or
        (domList[u].size() == 2 and mini == back[0][u] and maxi == back[1][u]))){
      cand.remove(back[0][u]);
      if(counter[back[0][u]] == 0) diff[depth].push(back[0][u]);
      counter[back[0][u]]++;
    }
  }

  // vより小さい順序を持つ頂点の情報を更新
  for (int i = C[v].begin(); i != C[v].end(); i = C[v].GetNext(i)){
    int u = C[v][i].to;
    if(back[0][u] < u)continue;
    if(FW[u].size() == 1 and FW[u][FW[u].begin()].to == v and cand.member(u)){
      cand.remove(u);  
      if(counter[u] == 0) diff[depth].push(u);
      counter[u]++;
    }
  }
  
  // vをprivate vertexとして持つ頂点が存在するかのチェック
  if(not v_dom and G[v].size() - FW[v].maxSize() == 1 and cand.member(back[0][v])){
    edge e = C[v].back();
    cand.remove(e.to);
    if(counter[e.to] == 0) diff[depth].push(e.to);
    counter[e.to]++;
  }
  return res - cand.size();
}

int EDS::updateDomList(int v, int size){
  // diff内に含まれる頂点をチェックする．
  // diff内に含まれる頂点はC(X)とC(X \ {v})の和が含まれる．
  int loop = diff[depth].size(), cnt = 0;
  for (int l = 0; l < loop; l++) {
    int u = diff[depth][l - cnt];

    // counter[u]が2の場合，次の候補集合でも削除されているので，消しっぱなしにしておく
    if(counter[u] == 2){
      diff[depth].pop();
      diff[depth].push(u);
      cnt++;
      counter[u]--;
      continue;
    }
    // l < sizeの時，頂点uを候補集合に戻す．
    if(l < size) counter[u]--, diff[depth].pop(), cnt++;
    for (int i = 0; i < FW[u].maxSize(); i++) {
      edge e  = FW[u][i];
      int rev = G.GetRev(G[u][i].id, u);
      edge c_edge = C.GetEdge(FW2C[e.id]);
      // uを候補集合に戻す．
      if(l < size){
        if(cand.member(c_edge.to))C.AddEdge(c_edge.id);
        domList[e.to].remove(rev);
        domList[u].remove(i);
        dominated[e.to]++;
      }else{
        // uを候補集合から削除する．
        if(cand.member(c_edge.to))C.RemoveEdge(c_edge.id);
        domList[e.to].add(rev);
        dominated[e.to]--;
      }
    }
  }
  // domList[v]の情報を更新する．
  for (int i = 0; i < FW[v].maxSize(); i++) {
    edge e = G[v][i];
    dominated[e.to]--;
    if(solution.member(e.to))domList[v].add(i);
    int rev = G.GetRev(e.id, v);
    domList[e.to].remove(rev);
  }
  int res = 0;
  // FWの情報を更新する．
  for (int i = C[v].begin(); i != C[v].end(); i = C[v].GetNext(i)) {
    edge e = FW.GetEdge(C2FW[C[v][i].id]);
    // if(FW.member(e.id))FW.RemoveEdge(e.id), res++;
    FW.RemoveEdge(e.id), res++;//if 文を入れないでも問題ないはず
  }
  // vをprivate vertexとして持つ頂点がある場合の情報更新
  if((domList[v].size() + dominated[v]) == 1) {
    domList[v].add(C[v].GetPrev(C[v].end())); 
  }
  return res;
}

// テスト用プリント関数
void EDS::print(){
  int sum = 0, n = G.size();
  for (int i = 0; i <= n; i++) sum += result[i];
  std::cout << sum << std::endl;
  // std::cout << "size:" << std::endl;
  for (int i = 0; i <= n; i++) {
    std::cout << result[i] << std::endl;
  }
  std::cout << std::endl;
  // std::cout << "Graph G" << std::endl;
  // for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
  //   std::cout << i << ":";
  //   for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
  //     std::cout <<  G[i][j].to << " ";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << "dominated: ";
  // for (int i = 0; i < dominated.size(); i++) {
  //   std::cout << dominated[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "counter  : ";
  // for (int i = 0; i < dominated.size(); i++) {
  //   std::cout << counter[i] << " ";
  // }
  // std::cout << std::endl;
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
