#include<vector>
#include<iostream>
#include<algorithm>
#include<queue>

#include"graph.hpp"
#include"enum.hpp"

int RecEST(Graph &g, int v){
  std::cout << "start RecEST" << std::endl;
  if(g.empty())return 1;
  edge &e = g[v][g[v][0].next];
  int to = g[v][g[v][0].next].to, res = 0, parallel = 0;
  for (int i = g[v][0].next; i < g[v].end(); i = g[v][i].next) {
    if(g[v][i].to == to)parallel++;
  }
  std::cout << "v :" << v;
  std::cout << " to:" << to << " size:" << g[v].size() << std::endl;
  g.Contract(v, to);
  std::cout << "next vertex:" << g.GetNode() << std::endl;
  res += parallel*RecEST(g, g.GetNode());
  g.Uncontract();
  
  g[v].RemoveEdge(g[v][0].next);
  g[to].RemoveEdge(e.rev);
  int bridge_size = g.EnumBridgeAndContract();
  res += RecEST(g, g.GetNode());
  for (int i = 0; i < bridge_size; i++) g.Uncontract();
  g[v].RestoreEdge();
  g[to].RestoreEdge();
  std::cout << "end RecEST" << std::endl;
  return res;
}

bool Connected(Graph &g){
  std::vector<bool> visited(g.size(), false);
  std::queue<int> que;
  que.push(0);
  visited[0] = true;
  while(not que.empty()){
    int v = que.front();
    que.pop();
    for (int i = g[v][0].next; i != g[v].end(); i = g[v][i].next) {
      int to = g[v][i].to;
      if(visited[to])continue;
      visited[to] = true;
      que.push(to);
    }
  }
  return all_of(visited.begin(), visited.end(), [](bool x){return x;});
}

int EnumSpanningTree(Graph &g){
  if(not Connected(g))return 0;
  g.EnumBridgeAndContract();
  std::cout << "the number of vertices:" << g.size() << std::endl;
  std::cout << std::endl;
  for (int i = 0; i < g.g_tail; i++) {
    std::cout << "id:" << i << std::endl;
    g[i].print();
  }
  return RecEST(g, g.GetNode());
}
