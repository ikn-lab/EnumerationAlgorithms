#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<unordered_set>
#include<set>
#include<string>

#include"Graph.hpp"
#include"constant.hpp"
#include"basicDataStructure.hpp"
using pii = std::pair<int, int>;
using bigint = long long int;

bigint EIMRec(Graph &G,
              std::vector<bigint> &ans,
              FixedQueue<pii> &update,
              FixedStack<int> &stack_V,
              int k, 
              bigint size = 0,
              bigint marge = 1);

bigint CallAllChildren(Graph &G,
                       std::vector<bigint> &ans,
                       FixedQueue<pii> &update,
                       FixedStack<int> &stack_V, 
                       int k, 
                       bigint size,
                       bigint marge){
  int v = G.MaximumDeg();
  //for bfs, vertex, distance
  int SVsize = stack_V.size(), cnt = 0;
  int num_children = G.GetDeg(G.MaximumDeg());
  bigint res = 0;
  update.push(pii(v, 0));

  //bfs
  G.dist.set(v, 0);
  while(not update.empty()){
    v = update.front().first;
    int d = update.front().second;
    update.pop();
    if(d >= 2) break;
    G.RemoveVertex(v);
    if(d == 1)stack_V.push(-1);
    for (int i = G[v].begin(); i != G[v].end(); i=G[v].GetNext(i)) {
      if(G.dist[G[v][i].to] > d + 1){
        G.dist.set(G[v][i].to, d + 1);
        update.push(pii(G[v][i].to, d + 1));
      }
      if(G.dist[G[v][i].to] == 2)stack_V.push(G[v][i].to);
    }
  }
  //bfs
  
  G.dist.initialize();
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
              bigint size,
              bigint marge){
  // std::cout << "pivot:" << G.MaximumDeg() << std::endl;
  int maxi = G.GetDeg(G.MaximumDeg()),
    mini = G.GetDeg(G.MinimumDeg());
  // if(maxi == 1 and mini == 1 and G.edgeSize() + size < k){
  //   ans[size] += marge;
  //   return marge;
  // }
  
  if(G.size() == 0){
    ans[size] += marge;
    return marge;
  }
  // if(G.size() - maxi < (k - size - 1)*mini or 
  //    (maxi == 1 and mini == 1 and G.edgeSize() + size < k) or 
  //    (maxi == 2 and mini == 1 and G.GetDegNum(2) + 1 < 3*(k - size - (G.GetDegNum(1)>>1))) or
  //    (maxi == 2 and mini == 2 and G.edgeSize() < 3*(k - size)) or
  //    (maxi == 3 and 3*(3*G.GetDegNum(3) + G.GetDegNum(1)) + 2*G.GetDegNum(2) + 2 < 6*(k - size))){
  //   ans[size] += marge;
  //   return marge;
  // }

  return CallAllChildren(G, ans, update, stack_V, k, size, marge);
}


bigint EIM(Graph &G, std::vector<bigint> &ans, int k){
  FixedQueue<pii> update(20*G.size() + 10);
  FixedStack<int> stack_V(20*G.edgeSize() + 10);
  return EIMRec(G, ans, update, stack_V, k);
}
