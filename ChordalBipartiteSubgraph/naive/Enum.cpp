#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include"Enum.hpp"

#define DELETED -2

void ECIB::init(std::vector<std::vector<edge>> _G){
  n = _G.size();

  G.init(_G);
  ans.resize(n + 1, 0);
}

void ECIB::Enumerate(){
  solution.init(n);
  for (int i = 0; i < n; i++) solution.set(i, i);
  RecEnum();
}

bool ECIB::isConnected(){
  if(solution.size() == 0)return true;
  std::vector<bool> visited(n, false);
  dfs(visited, solution.begin());
  for (int i = solution.begin(); i != solution.end(); i = solution.GetNext(i)) {
    if(visited[i] == false)return false;
  }
  return true;
}

void ECIB::GetDiferentNeighbor(int x, int y, std::set<int> &nx, std::set<int> &ny){
  for (int i = G[x].begin(); i != G[x].end(); i = G[x].GetNext(i)) {
    int v = G[x][i].to;
    if(not solution.member(v))continue;
    bool same_neighbor = false;
    for (int j = G[v].begin(); j != G[v].end(); j = G[v].GetNext(j)) {
      same_neighbor |= (G[v][j].to == y);
    }
    if(not same_neighbor)nx.insert(v);
    else del.insert(v);
  }

  for (int i = G[y].begin(); i != G[y].end(); i = G[y].GetNext(i)) {
    int v = G[y][i].to;
    if(not solution.member(v))continue;
    bool same_neighbor = false;
    for (int j = G[v].begin(); j != G[v].end(); j = G[v].GetNext(j)) {
      same_neighbor |= (G[v][j].to == x);
    }
    if(not same_neighbor)ny.insert(v);
    else del.insert(v);
  }
}

bool ECIB::isSetConnected(int x, int y, std::set<int> &S, std::set<int> &T){
  std::queue<int> que;
  for (int v: S) que.push(v);
  std::vector<bool> visited(n, false);
  while(not que.empty()){
    int v = que.front();
    visited[v] = true;
    que.pop();
    for (int i = G[v].begin(); i != G[v].end(); i = G[v].GetNext(i)) {
      int u = G[v][i].to;
      if(visited[u])continue;
      if(del.count(u) > 0 or not solution.member(u))continue;
      que.push(u);
    }
  }
  for (int v: T)  if(visited[v])return true;
  return false;
}

bool ECIB::isCB(){
  for (int i = solution.begin(); i != solution.end(); i = solution.GetNext(i)) {
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      del.insert(G[i][j].to);
    }
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) {
      int x = G[i][j].to;
      if(not solution.member(x))continue;
      for (int k = G[i].GetNext(j); k != G[i].end(); k = G[i].GetNext(k)) {
        int y = G[i][k].to;
        if(not solution.member(y))continue;
        std::set<int> nx, ny, tmp = del;
        GetDiferentNeighbor(x, y, nx, ny);
        if(isSetConnected(x, y, nx, ny)) return false;
        del = tmp;
      }
    }
    del.clear();
  }
  return true;
}

void ECIB::dfs(std::vector<bool> &visited, int v){
  visited[v] = true;
  for (int i = G[v].begin(); i != G[v].end(); i = G[v].GetNext(i)) {
    int u = G[v][i].to;
    if(not solution.member(u))continue;
    if(visited[u])continue;
    dfs(visited, u);
  }
}

void ECIB::RecEnum(){
  if(current_node == n) {
    ans[solution.size()] += (isConnected() and isCB());
    return; 
  }
  solution.add(current_node++);
  RecEnum();
  solution.undo();
  RecEnum();
  current_node--;
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
