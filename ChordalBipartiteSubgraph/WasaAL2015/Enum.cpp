#include<iostream>
#include<algorithm>
#include"Enum.hpp"

#define DELETED -2

void ECIB::init(std::vector<std::vector<edge>> _G){
  n = _G.size();
  G.init(_G);
  ans.resize(n + 1, 0);
  for (int i = 0; i < n; i++) {
    delta = std::max(delta, (int)_G[i].size());
  }
  cand.init(n);
  for (int i = 0; i < n; i++) cand.set(i, i);
  tp.resize(n);
  
  for (int i = 0; i < n; i++) {
    tp[i].resize(delta);
    for (int j = 0; j < delta; j++) {
      tp[i][j].resize(delta);
      for (int k = 0; k < delta; k++) {
        tp[i][j][k].resize(n + 2, DELETED);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < _G[i].size(); j++) {
      for (int k = 0; k < _G[i].size(); k++) {
        int u = _G[i][j].to, w = _G[i][k].to;
        for (int l = 0; l < n + 2; l++) {
          tp[i][j][k][l] = l;
        }
        for (int l = 0; l < _G[i].size(); l++) {
          tp[i][j][k][_G[i][l].to] = DELETED;
        }
        for (int l = 0; l < _G[u].size(); l++) {
          tp[i][j][k][_G[u][l].to] = n;
        }
        for (int l = 0; l < _G[w].size(); l++) {
          int y = _G[w][l].to;
          if(tp[i][j][k][y] == n)tp[i][j][k][y] = DELETED;
          else tp[i][j][k][y] = n + 1;
        }
      }
    }
  }
}

void ECIB::Enumerate(){
  stack.resize(n*n*n);
  for (int i = 0; i < n; i++) {
    G.AddVertex(i);
    cand.add(i);
    cand.remove(i);
    int cntTP = updateTP(i);
    int cntCand = updateCand(i);
    if(not cand.empty())RecEnum();
    else ans[G.currentSize()]++;
    restoreTP(cntTP);
    for (int j = 0; j < cntCand; j++){
      cand.undo();
    }
    G.RemoveVertex(i);
  }
}

int ECIB::GetParent(int v, int a, int b, int u){
  if(a > b)std::swap(a, b);
  while(u != DELETED and tp[v][a][b][u] != u)
    u = tp[v][a][b][u];
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
      if(not G.useVertex(G[i][j].to))continue;
      for (int k = j + 1; not esc and k < G[i].end(); k++) {
        if(not G.useVertex(G[i][k].to))continue;
        if(GetConnect(i, j, k, n, n + 1)){
          i = cand.remove(i);
          esc = true;
          res++;
        }
      }
    }
  }
  return res;
}

int ECIB::updateParent(int v, int a, int b, int u){
  if(a > b)std::swap(a, b);
  int init = stack.size(), root = GetParent(v, a, b, u);
  if(root == DELETED) return 0;
  for (int i = 0; i < G[u].end(); i++) {
    if(not G.useVertex(G[u][i].to))continue;
    int w = GetParent(v, a, b, G[u][i].to);
    if(w == DELETED)continue;
    stack.push(log(v, a, b, w));
    tp[v][a][b][w] = root;
  }
  return stack.size() - init;
}

int ECIB::updateTP(int u){
  int res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < G[i].end(); j++) {
      for (int k = j + 1; k < G[i].end(); k++) {
        res += updateParent(i, j, k, u);
      }
    }
  }
  return res;
}


void ECIB::restoreTP(int cnt){
  for (int i = 0; i < cnt; i++) {
    int v = std::get<0>(stack.top());
    int a = std::get<1>(stack.top());
    int b = std::get<2>(stack.top());
    int w = std::get<3>(stack.top());
    tp[v][a][b][w] = w;
    stack.pop();
  }
}

bool ECIB::GetConnect(int v, int a, int b, int u, int w){
  int t = GetParent(v, a, b, u), tt = GetParent(v, a, b, w);
  return (t != DELETED and t != DELETED) and t == tt;
}

void ECIB::RecEnum(){
  int u = cand.begin();
  cand.remove(u);
  if(not cand.empty())RecEnum();//0 branch
  else ans[G.currentSize()]++;
  G.AddVertex(u);
  int cntTP = updateTP(u);
  int cntCand = updateCand(u);
  
  if(not cand.empty())RecEnum();//1 branch
  else ans[G.currentSize()]++;
  
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
