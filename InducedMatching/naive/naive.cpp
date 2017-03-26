#include<vector>
#include<queue>
#include<unordered_set>
#include"naive.hpp"
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int bigint;

std::unordered_set<int> id;
std::queue<pii> que;

bigint EnumIMatch(std::vector<edge> &m,
                  std::vector<int> &addlist,
                  std::vector<int> &ans,
                  Graph &g,
                  size_t p,
                  int IMsize){
  if(p == addlist.size()){
    ans[IMsize]++;
    return 1;
  }
  
  if(addlist[p] > 0){
    return EnumIMatch(m, addlist, ans, g, p + 1, IMsize);
  }
  
  que.push(pii(0, m[p].from));
  que.push(pii(0 ,m[p].to));
  while(not que.empty()){
    int v = que.front().second;
    int dist = que.front().first;
    que.pop();
    if(dist > 1)continue;
    for (size_t i = 0; i < g[v].size(); i++) {
      edge &e = g[v][i];
      que.push(pii(dist + 1, e.to));
      id.insert(e.id);
    }
  }
  for (auto i:id) {
    addlist[i]++;
  }
  id.clear();
  bigint res = EnumIMatch(m, addlist, ans, g, p + 1, IMsize + 1);
  que.push(pii(0, m[p].from));
  que.push(pii(0 ,m[p].to));
  while(not que.empty()){
    int v = que.front().second;
    int dist = que.front().first;
    que.pop();
    if(dist > 1)continue;
    for (size_t i = 0; i < g[v].size(); i++) {
      edge &e = g[v][i];
      que.push(pii(dist + 1, e.to));
      id.insert(e.id);
    }
  }
  for (auto i:id) {
    addlist[i]--;
  }
  id.clear();
  addlist[m[p].id]++;
  res += EnumIMatch(m, addlist, ans, g, p + 1, IMsize);
  addlist[m[p].id]--;
  return res;
}
