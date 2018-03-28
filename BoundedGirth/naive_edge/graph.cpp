#include<iostream>
#include<cstdio>

#include"graph.hpp"
using namespace std;

void Graph::AddEdge(int u, int v){
  edge_id[m++] = piiii(pii(u, g[u].size()), pii(v, g[v].size()));
  g[u].push_back(v);
  g[v].push_back(u);
  used[u].push_back(false);
  used[v].push_back(false);
}


