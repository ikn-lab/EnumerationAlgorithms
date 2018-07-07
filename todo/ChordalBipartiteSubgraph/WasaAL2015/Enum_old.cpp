#include<iostream>
#include<algorithm>
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
        tp[i][j][k].resize(n + 2, DELETED);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < _G[i].size(); j++) {
      int u = _G[i][j].to;
      for (int k = 0; k < _G[i].size(); k++) {
        int w = _G[i][k].to;
        // if(u == w)continue;
        // if(u > w)std::swap(u, w);
        for (int l = 0; l < n + 2; l++) {
          tp[i][u][w][l] = l;
        }
        for (int l = 0; l < _G[i].size(); l++) {
          tp[i][u][w][G[i][l].to] = DELETED;
        }
        for (int l = 0; l < _G[u].size(); l++) {
          tp[i][u][w][_G[u][l].to] = n;
        }
        for (int l = 0; l < _G[w].size(); l++) {
          int y = _G[w][l].to;
          if(tp[i][u][w][y] == n)tp[i][u][w][y] = DELETED;
          else tp[i][u][w][y] = n + 1;
        }
        tp[i][u][w][i] = DELETED;
      }
    }
  }
}

void ECIB::Enumerate(){
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
  // if(x > y)std::swap(x, y);
  while(u != DELETED and tp[v][x][y][u] != u) u = tp[v][x][y][u];
  return u;
}

int ECIB::updateCand(int u){
  int res = 0;
  for (int i = 0; i < G[u].end(); i++) {
    res += (cand.add(G[u][i].to) != -1);
  }
  
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    bool esc = false;
    for (int j = 0; not esc and j < G[i].end(); j++) {
      int x = G[i][j].to;
      if(not G.useVertex(x))continue;
      for (int k = j + 1; not esc and k < G[i].end(); k++) {
        int y = G[i][k].to;
        if(not G.useVertex(y))continue;
        if(GetConnect(i, x, y, n, n + 1)){
          i = cand.remove(i);
          esc = true;
          res++;
        }
      }
    }
  }
  return res;
}

int ECIB::updateParent(int v, int x, int y, int u){
  // if(x > y)std::swap(x, y);
  int init = stack.size(), root = GetParent(v, x, y, u);
  if(root == DELETED) return 0;
  for (int i = 0; i < G[u].end(); i++) {
    int w = GetParent(v, x, y, G[u][i].to);
    if(w == DELETED)continue;
    stack.push(log(v, x, y, w));
    tp[v][x][y][w] = root;
    // if(w >= n and root < n){
    //   stack.push(log(v, x, y, root));
    //   tp[v][x][y][root] = w;
    //   root = w;
    // }else{
    //   stack.push(log(v, x, y, w));
    //   tp[v][x][y][w] = root;
    // }
  }
  return stack.size() - init;
}

int ECIB::updateTP(int u){
  int res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < G[i].end(); j++) {
      for (int k = 0; k < G[i].end(); k++) {
        if(j == k) continue;
        res += updateParent(i, G[i][j].to, G[i][k].to, u);
      }
    }
  }
  return res;
}


void ECIB::restoreTP(int cnt){
  for (int i = 0; i < cnt; i++) {
    int v = std::get<0>(stack.top());
    int x = std::get<1>(stack.top());
    int y = std::get<2>(stack.top());
    int w = std::get<3>(stack.top());
    tp[v][x][y][w] = w;
    stack.pop();
  }
}

bool ECIB::GetConnect(int v, int x, int y, int u, int w){
  int a = GetParent(v, x, y, u), b = GetParent(v, x, y, w);
  if(a == DELETED or b == DELETED) return false;  
  else return a == b;
}

void ECIB::RecEnum(){
  // std::cout << "print solution.  ";
  // for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) {
  //   std::cout << i << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "print candidate. ";
  // for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
  //   std::cout << cand[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << std::endl;
  if(cand.empty()){
    ans[G.currentSize()]++;
    return; 
  }
  int u = cand.begin();
  cand.remove(u);
  RecEnum();//0 branch
  G.AddVertex(u);
  int cntTP = updateTP(u);
  int cntCand = updateCand(u);
  
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
