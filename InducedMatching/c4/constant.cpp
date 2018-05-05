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

bigint EIMRec(Graph &G,
              std::vector<bigint> &ans,
              FixedQueue<pii> &update,
              FixedStack<int> &stack_V,
              int size = 0,
              int marge = 1);
              

bigint CallAllChildren(Graph &G,
                       std::vector<bigint> &ans,
                       FixedQueue<pii> &update,
                       FixedStack<int> &stack_V, 
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
      if(G.dist[G[v][i].to] <= d + 1)continue;
      G.dist[G[v][i].to] = d + 1;
      update.push(pii(G[v][i].to, d + 1));
      if(d == 1)stack_V.push(G[v][i].to);
    }
  }
  //bfs
  for (int i = 0; i < update.end(); i++) 
    G.dist[update[i].first] = 1e9;
  update.clear();
  
  int empty_edge = 0;
  while(stack_V.size() > SVsize){
    while(stack_V.top() != -1){
      cnt++;
      G.RemoveVertex(stack_V.top());
      stack_V.pop();
    }
    stack_V.pop();
    // res += EIMRec(G, ans, update, stack_V, size + 1, marge);
    // for counting
    if(cnt > 0)res += EIMRec(G, ans, update, stack_V, size + 1, marge);
    else empty_edge++;
    for (;cnt > 0; cnt--)G.undo();
      // G.RestoreVertex();
      
  }
  //for counting
  if(empty_edge > 0)
    res += EIMRec(G, ans, update, stack_V, size + 1, marge*empty_edge);
  
  for (int i = 0; i < num_children; i++) G.undo();
  res += EIMRec(G, ans, update, stack_V, size, marge); // 0-child
  G.undo();
  return res;
}

bigint EIMRec(Graph &G,
              std::vector<bigint> &ans,
              FixedQueue<pii> &update,
              FixedStack<int> &stack_V,
              int size,
              int marge){
  if(G.GetDeg(G.MaximumDeg()) <= 0){
    ans[size] += marge;
    return marge;
  } 
  bigint res = 0;
  res += CallAllChildren(G, ans, update, stack_V, size, marge);
  return res;
}


bigint EIM(Graph &G, std::vector<bigint> &ans){
  std::cout << "start" << std::endl;
  FixedQueue<pii> update(2*G.size() + 10);
  FixedStack<int> stack_V(3*G.size() + 10);
  return EIMRec(G, ans, update, stack_V, 0, 1);
}
