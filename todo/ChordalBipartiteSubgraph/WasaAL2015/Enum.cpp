#include<iostream>
#include"Enum.hpp"

#define DELETED -2

void ECIB::init(std::vector<std::vector<edge>> _G){
  n = _G.size();
  G.init(_G);
  ans.resize(n + 1, 0);
  for (int i = 0; i < n; i++) {
    delta = std::max(delta, G[i].size());
  }
  cand.init(n);
  for (int i = 0; i < n; i++) cand.set(i, i);
  tp.resize(n);
  for (int i = 0; i < n; i++) {
    tp[i].resize(n);
    for (int j = 0; j < n; j++) {
      tp[i][j].resize(n);
      for (int k = 0; k < n; k++) {
        tp[i][j][k].resize(n + 2, 0);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < _G[i].size(); j++) {
      int u = _G[i][j].to;
      for (int k = 0; k < _G[i].size(); k++) {
        int w = _G[i][k].to;
        for (int l = 0; l < n + 2; l++) {
          tp[i][u][w][l] = l;
        }
        for (int l = 0; l < _G[i].size(); l++) {
          if(_G[i][l].to == u or _G[i][l].to == w)continue;
          tp[i][u][w][l] == DELETED;
        }
        for (int l = 0; l < _G[u].size(); l++) {
          int x = _G[u][l].to;
          if(x != i)tp[i][u][w][x] = n;
        }
        for (int l = 0; l < _G[w].size(); l++) {
          int y = _G[w][l].to;
          if(tp[i][u][w][y] == n)tp[i][u][w][y] = DELETED;
          else if(y != i)tp[i][u][w][y] = n + 1;
        }
      }
    }
  }
}

void ECIB::Enumerate(){
  // solution.init(n);
  // for (int i = 0; i < n; i++) solution.set(i, i);

  for (int i = 0; i < n; i++) {
    G.AddVertex(i);
    cand.add(i);
    cand.remove(i);
    int cntTP = updateTP(i);
    int cntCand = updateCand(i);
    RecEnum();
    restoreTP(cntTP);
    for (int j = 0; j < cntCand; j++){
      cand.undo();
    }
    G.undo();
  }
}

int ECIB::GetParent(int v, int x, int y, int u){
  if(tp[v][x][y][u] == DELETED)return DELETED;
  int res = u;
  while(tp[v][x][y][res] != res){
    // std::cout << res << std::endl;
    res = tp[v][x][y][res]; 
  }
  return res;
}

int ECIB::updateCand(int u){
  int res = 0;
  for (int i = 0; i < G[u].end(); i++) {
    if(cand.add(G[u][i].to) != -1) res++;
  }
  
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    bool escape = false;
    for (int j = G[i].begin(); j != G[i].end() and not escape; j = G[i].GetNext(j)) {
      int x = G[i][j].to;
      for (int k = G[i].GetNext(j); k != G[i].end() and not escape; k = G[i].GetNext(k)) {
        int y = G[i][k].to;
        if(GetConnect(i, x, y, n, n + 1)){
          i = cand.remove(i);
          escape = true;
          res++;
        }
      }
    }
  }
  return res;
}

int ECIB::updateParent(int v, int x, int y, int root){
  int res = 0;
  // std::cout << "v:" << v << " x:" << x << " y:" << y << " root:" << root << std::endl;
  root = GetParent(v, x, y, root);
  if(root < n){
    for (int i = G[root].begin(); i != G[root].end(); i = G[root].GetNext(i)) {
      int w = G[root][i].to;
      w = GetParent(v, x, y, w);
      if(w == DELETED)continue;
      // std::cout << "w:" << G[root][i].to << " x:" << x << " y:" << y << " v:" << v << " parent:" << w << " root:" << root << " tp:" << tp[v][x][y][root] << std::endl;
      // std::cout << w << " " << tp[v][x][y][w] << std::endl;      
      if(root != w){
        if(w >= n and tp[v][x][y][root] == root){
          stack.push(log(v, x, y, root));
          stack.push(log(v, y, x, root));
          tp[v][x][y][root] = w;
          tp[v][y][x][root] = w;
          res += 2;
        }else if(w != tp[v][x][y][root]){
          stack.push(log(v, x, y, w));
          stack.push(log(v, y, x, w));
          tp[v][x][y][w] = root;
          tp[v][y][x][w] = root;
          res += 2;
        }
      }
    }
  }else{
    std::vector<int> neighbor;
    for (int i = G[x].begin(); i != G[x].end(); i = G[x].GetNext(i)) {
      // std::cout << G[x][i].to << " " << tp[v][x][y][G[x][i].to] << std::endl;
      int w = GetParent(v, x, y, G[x][i].to);
      if(w == root)neighbor.push_back(G[x][i].to);
    }
    for (int i = G[y].begin(); i != G[y].end(); i = G[y].GetNext(i)) {
      // std::cout << G[y][i].to << std::endl;
      int w = GetParent(v, x, y, G[y][i].to);
      if(w == root)neighbor.push_back(G[y][i].to);
    }
    for (int w: neighbor) {
      for (int i = G[w].begin(); i != G[w].end(); i = G[w].GetNext(i)) {
        int z = GetParent(v, x, y, G[w][i].to);
        // std::cout << "z:" << G[w][i].to << " parent:" << z << std::endl;
        if(z == DELETED)continue;
        if(root != z){
          stack.push(log(v, x, y, z));
          stack.push(log(v, y, x, z));
          tp[v][x][y][z] = root;
          tp[v][y][x][z] = root;
          res += 2;
        }
      }
    }
  }
  // std::cout << "end updateParent" << std::endl;
  return res;
}

int ECIB::updateTP(int u){
  int res = 0;
  // std::cout << "updateTP" << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      // std::cout << "j:" << j << std::endl;
      for (int k = G[i].begin(); k != G[i].end(); k = G[i].GetNext(k)) {
        // std::cout << "k:" << k << std::endl;
        int x = G[i][j].to, y = G[i][k].to, root = GetParent(i, x, y, u);
        if(root == DELETED) continue;
        res += updateParent(i, x, y, root);
      }
    }
  }
  // std::cout << "end updateTP" << std::endl;
  return res;
}


void ECIB::restoreTP(int cnt){
  // std::cout << "start restoreTP" << std::endl;
  for (int i = 0; i < cnt; i++) {
    int v = std::get<0>(stack.top());
    int x = std::get<1>(stack.top());
    int y = std::get<2>(stack.top());
    int w = std::get<3>(stack.top());
    tp[v][x][y][w] = w;
    stack.pop();
  }
  // std::cout << "end restoreTP" << std::endl;
}

bool ECIB::GetConnect(int v, int x, int y, int u, int w){
  return GetParent(v, x, y, u) == GetParent(v, x, y, w);
}

void ECIB::RecEnum(){
  std::cout << "print solution.  ";
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  std::cout << "print candidate. ";
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    std::cout << cand[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  
  if(cand.empty()){
    ans[G.currentSize()]++;
    return; 
  }
  int u = cand.begin();
  cand.remove(u);
  RecEnum();//0 branch
  int cntTP = updateTP(u);
  int cntCand = updateCand(u);
  G.AddVertex(u);
  
  RecEnum();//1 branch
  restoreTP(cntTP);
  for (int i = 0; i < cntCand + 1; i++) cand.undo();
  G.undo();
}

void ECIB::print(){
  int sum = 0;
  for (int i = 0; i < ans.size(); i++) {
    sum += ans[i];
  }
  std::cout << "size:" << sum << std::endl;
  for (int i = 0; i < ans.size(); i++) {
    std::cout << i << ":" << ans[i] << std::endl;
  }
}
