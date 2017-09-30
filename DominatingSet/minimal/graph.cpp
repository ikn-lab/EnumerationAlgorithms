#include<cmath>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>

#include"graph.hpp"

constexpr int INF = 1e9;

Graph::Graph(int n){
  g.resize(n);
  used.resize(n, true);
}

void Graph::print(){
  std::cout << "degeneracy:" << degeneracy << std::endl;
  std::cout << "n:" << g.size() << std::endl;
  for (int i = 0; i < g.size(); i++) {
    std::cout << i << ": ";
    for (int j = 0; j < g[i].size(); j++) {
      std::cout << g[i][j] << " ";
    }
    std::cout << std::endl;
  }
  for (int i = 0; i < g.size(); i++) {
    std::cout << used[i] << " ";
  }
  std::cout << std::endl;
}

// 面倒臭いのでO(n^2)の実装になっています。
// ちゃんと頑張ればO(n + m)で実装できます。
// degenerate orderingのO(n + m)アルゴリズムの論文:
// Matula, D.W., Beck, L.L.: Smallest-last ordering and clustering and graph coloring algorithms. J. ACM 30(3), 417–427 (1983)
void Graph::DegenerateOrder(){
  int n = g.size();
  std::vector<int> degree(n, 0);
  for (int i = 0; i < n; i++) degree[i] = g[i].size();
  std::vector<int> ordering(n), reverse(n);
  for (int i = 0; i < n; i++) {
    int v = -1, deg = INF;
    for (int j = 0; j < n; j++) {
      if(degree[j] < deg) v = j, deg = degree[j];
    }
    ordering[i] = v;
    reverse[v] = i;
    degeneracy = std::max(degeneracy, degree[v]);
    degree[v] = INF;
    for (int j = 0; j < g[v].size(); j++) degree[g[v][j]]--;
  }
  std::vector<std::vector<int> > tmp(n);
  for (int i = 0; i < n; i++) {
    int v = ordering[i];
    for (int j = 0; j < g[v].size(); j++) {
      tmp[i].push_back(reverse[g[v][j]]);
    }
  }
  for (int i = 0; i < n; i++){
    std::sort(tmp[i].begin(), tmp[i].end());
    std::reverse(tmp[i].begin(), tmp[i].end());
  }
  g = tmp;
}
