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
  G.print();
  for (int i = 0; i < n; i++) {
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      int u = G[i][j].to;
      for (int k = G[i].begin(); k != G[i].end(); k = G[i].GetNext(k)) {
        int w = G[i][k].to;
        if(u == w)continue;
        for (int l = 0; l < n + 2; l++) {
          tp[i][u][w][l] = l;
        }
        for (int x = G[u].begin(); x != G[u].end(); x = G[u].GetNext(x)) {
          tp[i][u][w][G[u][x].to] = n;
        }
        for (int y = G[w].begin(); y != G[w].end(); y = G[w].GetNext(y)) {
          if(tp[i][u][w][G[w][y].to] == n)tp[i][u][w][G[w][y].to] = DELETED;
          else tp[i][u][w][G[w][y].to] = n + 1;
        }
      }
    }
  }
}

void ECIB::Enumerate(){
  solution.init(n);
  for (int i = 0; i < n; i++) solution.set(i, i);

  for (int i = 0; i < n; i++) {
    solution.add(i);
    cand.add(i);
    cand.remove(i);
    int cntCand = updateCand(i);
    int cntTP = updateTP(i);
    for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
      std::cout << cand[i] << " ";
    }
    std::cout << std::endl;
    
    RecEnum();
    restoreTP(cntTP);
    for (int j = 0; j < cntCand; j++){
      cand.undo();
    }
    solution.undo();
  }
}

int ECIB::GetParent(int v, int x, int y, int u){
  if(tp[v][x][y][v] == DELETED)return DELETED;
  int res = u;
  while(tp[v][x][y][res] != res){
    res = tp[v][x][y][res]; 
  }
  return res;
}

int ECIB::updateTP(int u){
  // std::cout << "start TP. " << std::endl;
  int res = 0;
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      for (int k = G[i].GetNext(j); k != G[i].end(); k = G[i].GetNext(k)) {
        int root = u;
        int x = G[i][j].to, y = G[i][k].to;
        if(tp[i][x][y][root] == DELETED)continue;
        root = GetParent(i, x, u, root);
        if(root < n){
          for (int l = G[u].begin(); l != G[u].end(); l = G[u].GetNext(l)) {
            int w = G[u][l].to;
            w = GetParent(i, x, y, w);
            if(root != w){
              stack.push(log(i, x, y, w));
              tp[i][x][y][w] = u;
              res++;
            }
          }
        }else{
          std::vector<int> neighbor;
          if(root == n){
            for (int l = G[x].begin(); l != G[x].end(); l = G[x].GetNext(l)) {
              int w = GetParent(i, x, y, G[x][l].to);
              if(w == n)neighbor.push_back(G[x][l].to);
            }
          }
          if(root == n + 1) {
            for (int l = G[y].begin(); l != G[y].end(); l = G[y].GetNext(l)) {
              int w = GetParent(i, x, y, G[y][l].to);
              if(w == n + 1)neighbor.push_back(G[y][l].to);
            }
          }
          for (int l = 0; l < neighbor.size(); l++) {
            for (int m = G[l].begin(); m < G[l].end(); m = G[l].GetNext(m)) {
              int w = GetParent(i, x, y, G[neighbor[l]][m].to);
              if(root != w){
                stack.push(log(i, x, y, w));
                tp[i][x][y][w] = u;
                res++;
              }
            }
          }
        }
      }
    }
  }
  // std::cout << "end TP. " << std::endl;
  return res;
}

int ECIB::updateCand(int u){
  // std::cout << "start Cand. " << std::endl;
  int res = 0;
  bool escape = false;
  for (int i = G[u].begin(); i != G[u].end(); i = G[u].GetNext(i)) {
    if(cand.add(G[u][i].to) != -1)res++;
  }
  
  for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
    escape = false;
    for (int j = G[i].begin(); j != G[i].end() and not escape; j = G[i].GetNext(j)) {
      if(not solution.member(j))continue;
      for (int k = G[i].GetNext(j); k != G[i].end() and not escape; k = G[i].GetNext(k)) {
        if(not solution.member(k))continue;
        if(GetConnect(i, j, k, n, n + 1)){
          i = cand.remove(i);
          // std::cout << "escape" << std::endl;
          escape = true;
          res++;
        }
      }
    }
  }
  // std::cout << "end Cand. " << std::endl;
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
  while(tp[v][x][y][u] != u)u = tp[v][x][y][u];
  while(tp[v][x][y][w] != w)w = tp[v][x][y][w];
  return u == w;
}

void ECIB::RecEnum(){
  // std::cout << "rec enum" << std::endl;
  // std::cout << "cand" << std::endl;
  // for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
  //   std::cout << cand[i] << " ";
  // }
  // std::cout << std::endl;
  if(cand.empty()){
    ans[solution.size()]++;
    if(solution.size() == 9) std::cout << "size 9 "; 
    std::cout << "print solution. ";
    for (int i = solution.begin(); i != solution.end(); i = solution.GetNext(i)) {
      std::cout << solution[i] << " ";
    }
    std::cout << std::endl;
    //    std::cout << "end solution. " << std::endl;
    return; 
  }
  int u = cand.begin();
  // std::cout << "begin:" << u << std::endl;
  cand.remove(u);
  RecEnum();//0 branch
  int cntCand = updateCand(u);
  int cntTP = updateTP(u);
  // std::cout << "cand:" << std::endl;
  // for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
  //   std::cout << cand[i] << " ";
  // }
  // std::cout << std::endl;
  
  // std::cout << "sol:" << u << std::endl;
  solution.add(u);
  // std::cout << "sol" << std::endl;
  
  RecEnum();//1 branch
  restoreTP(cntTP);
  // std::cout << "cntCand:" << cntCand << std::endl;
  for (int i = 0; i < cntCand + 1; i++) cand.undo();
  solution.undo();
  // std::cout << "end enum" << std::endl;
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
