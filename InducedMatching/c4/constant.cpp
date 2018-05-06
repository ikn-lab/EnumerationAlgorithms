#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<unordered_set>
#include<set>
#include<string>

#include"graph.hpp"
#include"constant.hpp"
#include"basicDataStructure.hpp"
using pii = std::pair<int, int>;

bigint EIMRec(Graph &G,
              std::vector<bigint> &ans,
              FixedQueue<pii> &update,
              FixedStack<int> &stack_V,
              int k, 
              int size = 0,
              int marge = 1);
              

bigint CallAllChildren(Graph &G,
                       std::vector<bigint> &ans,
                       FixedQueue<pii> &update,
                       FixedStack<int> &stack_V, 
                       int k, 
                       int size,
                       int marge){
  int v = G.MaximumDeg();
  //for bfs, vertex, distance
  int SVsize = stack_V.size(), cnt = 0;
  int num_children = G.GetDeg(G.MaximumDeg());
  bigint res = 0;
  update.push(pii(v, 0));

  //bfs
  G.dist[v] = 0;
  while(not update.empty()){
    v = update.front().first;
    int d = update.front().second;
    update.pop();
    if(d >= 2) break;
    G.RemoveVertex(v);
    if(d == 1)stack_V.push(-1);
    for (int i = G[v].begin(); i != G[v].end(); i=G[v].GetNext(i)) {
      if(G.dist[G[v][i].to] > d + 1){
        G.dist[G[v][i].to] = d + 1;
        update.push(pii(G[v][i].to, d + 1));
      }
      if(G.dist[G[v][i].to] == 2)stack_V.push(G[v][i].to);
    }
  }
  //bfs
  
  for (int i = 0; i < update.end(); i++) {
    G.dist[update[i].first] = 1e9;    
  }
  update.clear();
  
  int empty_edge = 0;
  while(stack_V.size() > SVsize){
    while(stack_V.top() != -1){
      cnt++;
      G.RemoveVertex(stack_V.top());
      stack_V.pop();
    }
    stack_V.pop();
    // res += EIMRec(G, ans, update, stack_V, k, size + 1, marge);
    // for counting
    if(cnt > 0)res += EIMRec(G, ans, update, stack_V, k, size + 1, marge);
    else empty_edge++;
    for (;cnt > 0; cnt--)G.undo();
  }
  //for counting
  if(empty_edge > 0)
    res += EIMRec(G, ans, update, stack_V, k, size + 1, marge*empty_edge);
  
  for (int i = 0; i < num_children; i++) G.undo();
  res += EIMRec(G, ans, update, stack_V, k, size, marge); // 0-child
  G.undo();
  return res;
}
bigint EIMRec(Graph &G,
              std::vector<bigint> &ans,
              FixedQueue<pii> &update,
              FixedStack<int> &stack_V,
              int k, 
              int size,
              int marge){
  // std::cout << "pivot:" << G.MaximumDeg() << std::endl;
  int tmp = 2*G.GetDeg(G.MinimumDeg());
  if(G.size() == 0 or G.size() < (k - size - 1)*tmp){
    ans[size] += marge;
    return marge;
  }
  return CallAllChildren(G, ans, update, stack_V, k, size, marge);
}


bigint EIM(Graph &G, std::vector<bigint> &ans, int k){
  FixedQueue<pii> update(2*G.size() + 10);
  FixedStack<int> stack_V(2*G.edgeSize() + 10);
  return EIMRec(G, ans, update, stack_V, k);
}
