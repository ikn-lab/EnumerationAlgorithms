#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<unordered_set>
#include<set>
#include<string>

#include"graph.hpp"
#include"constant.hpp"

#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int bigint;
// typedef long long int bigint;

std::queue<pii> que;
std::queue<int> update;

bigint CallOneChildren(Graph &g, int v, std::vector<bigint> &ans, int size, int marge){
  //for bfs, vertex, distance
  std::stack<int>& log = g.log;
  std::stack<int>& vs  = g.vs;
  int vssize = vs.size(), cnt = 0;
  bigint res = 0;
  que.push(pii(v, 0));
  log.push(g[v].size());
  

  //bfs
  g.dist[v] = 0;
  update.push(v);
  while(not que.empty()){
    v = que.front().first;
    int d = que.front().second;
    que.pop();
    if(d >= 2) break;
    g.RemoveVertex(v);
    if(d == 1)vs.push(-1);
    for (int i = g[v][0].next; i < g[v].end(); i=g[v][i].next) {
      if(g.dist[g[v][i].to] <= d)continue;
      if(g.dist[g[v][i].to] > d + 1)
        update.push(g[v][i].to);
      g.dist[g[v][i].to] = d + 1;
      que.push(pii(g[v][i].to, d + 1));
      if(d == 1)vs.push(g[v][i].to);
    }
  }
  //bfs
  
  std::queue<pii>().swap(que);
  while(not update.empty()){
    g.dist[update.front()] = 1e9;
    update.pop();
  }
  int empty_edge = 0;
  while(vs.size() > vssize){
    while(vs.top() != -1){
      cnt++;
      g.RemoveVertex(vs.top());
      vs.pop();
    }
    vs.pop();
    if(cnt > 0)res += EnumIMatch(g, ans, size + 1, marge);
    else empty_edge++;
    for (;cnt > 0; cnt--)
      g.RestoreVertex();
  }
  if(empty_edge > 0)res += EnumIMatch(g, ans, size + 1, marge*empty_edge);
  return res;
}


bigint EnumIMatch(Graph &g, std::vector<bigint> &ans, int size, int marge){
  if(g.MaximumDeg().deg == 0){
    ans[size] += marge;
    return marge;
  } 
  bigint res = 0;
  int pivot = g.MaximumDeg().id;
  int lsize = g.log.size();
  res += CallOneChildren(g, pivot, ans, size, marge); 
  while(g.log.size() > lsize){
    int tmp = g.log.top();
    g.log.pop();
    for (int i = 0;i < tmp; i++) g.RestoreVertex();
  }
  
  res += EnumIMatch(g, ans, size, marge); // 0-child
  g.RestoreVertex();
  return res;
}
