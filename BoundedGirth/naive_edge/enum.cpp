#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

#include"enum.hpp"
#include"graph.hpp"
using namespace std;
using pii = std::pair<int, int>;
using bigint = long long int;
std::vector<bigint> ans;

void dfs(Graph &g, vector<bool> &used, int v){
  used[v] = true;
  for (int i = 0; i < g[v].size(); i++) {
    if(not g.used[v][i])continue;
    int to = g[v][i];
    if(used[to])continue;
    dfs(g, used, to);
  }
}

bool Connectivity(Graph &g){
  int v = -1; 
  for (int i = 0; i < g.size() and v == -1; i++) {
    for (int j = 0; j < g[i].size() and v == -1; j++) {
      if(g.used[i][j]){
        v = i;
      }
    }
  }
  std::vector<bool> used(g.size(), false);
  dfs(g, used, v);
  bool res = true;
  for (int i = 0; i < g.size(); i++) {
    bool f = false;
    for (int j = 0; j < g[i].size(); j++) {
      f |= g.used[i][j];
    }
    if(f) res &= used[i];
  }
  return res;
}

bool Girth(Graph &g){
  std::queue<int> que;
  int girth = 1e9, n = g.size();
  for (int i = 0; i < n; i++) {
    que.push(i);
    std::vector<int> dist(n, 1e9);
    dist[i] = 0;
    while(not que.empty()){
      int v = que.front();
      que.pop();
      for (int j = 0; j < g[v].size(); j++) {
        int to = g[v][j];
        if(g.used[v][j] == false)continue;
        if(dist[to] < dist[v])continue;
        girth = min(girth, dist[v] + dist[to] + 1);
        if(dist[to] > dist[v] + 1){
          dist[to] = dist[v] + 1;
          que.push(to);
        }
      }
      if(girth < g.k)return false;
    }
  }
  return girth >= g.k;
}


std::vector<bigint> ELGMain(Graph &g){
  long long int m = 0;
  for (int i = 0; i < g.size(); i++) {
    m += g[i].size();
  }
  m /= 2LL;
  std::cout << m << std::endl;
  ans.resize(m + 1, 0);
  for (int i = 1; i < (1LL<<m); i++) {
    int size = 0;
    // if(i == (1LL<<m)/16)std::cout << "1/16" << std::endl;
    // if(i == (1LL<<m)/8)std::cout << "1/8" << std::endl;
    // if(i == (1LL<<m)/4)std::cout << "1/4" << std::endl;
    // if(i == (1LL<<m)/2)std::cout << "1/2" << std::endl;
    for (int j = 0; j < m; j++) {
      pii p = g.edge_id[j].first;
      pii q = g.edge_id[j].second;
      if(i&(1<<j)){
        g.used[p.first][p.second] = g.used[q.first][q.second] = true;
      }else{
        g.used[p.first][p.second] = g.used[q.first][q.second] = false;
      }
      size += ((i&(1<<j)) > 0);
    }
    ans[size] += Connectivity(g) and Girth(g);
  }
  return ans;
}
