#include<vector>
#include<queue>
#include<stack>
#define DIST 1
#include"constant.hpp"
std::vector<int> ans;

void EdgeList::RemoveEdge(int id){
  edge &e  = list[id];
  st.push(id);
  list[id - e.prev].next += e.next;
  list[id + e.next].prev += e.prev;
  s--;
}

int EdgeList::RestoreEdge(){
  if(st.size() == 0){
    std::cerr << "stack is empty" << std::endl;
    exit(1);
  }
  int id = st.top();
  st.pop();
  edge &e  = list[id];
  list[id - e.prev].next = e.prev;
  list[id + e.next].prev = e.next;
  s++;
  return list[id + e.next].id;
}

void RestoreSomeEdges(std::stack<piii> &st, EdgeList &addlist,
               Graph &g, int &p, int dist){
  while(not st.empty() and st.top().first >= dist){
    int v = st.top().second.first;
    g[v].RestoreEdge();
    v = st.top().second.second;
    g[v].RestoreEdge();
    st.pop();
    if(addlist.RestoreEdge() == p){
      p -= addlist[p].prev;
    }
  }
}

int Normal(int x, EdgeList &addlist, Graph &g,
           std::stack<piii> &st, int &p){
  std::queue<pii> coordinate, border;
  std::queue<piii> que;
  que.push(piii(0, pii(x, -1)));
  for (int i = g[x][0].next; i < g[x].end() - 1; i+=g[x][i].next) {
    coordinate.push(pii(g[x][i].to, g[x][i].id));
  }
  int res = 0;
  while(not que.empty()){
    int d = que.front().first;
    int v = que.front().second.first;
    int prev = que.front().second.second;
    que.pop();
    if(d > DIST){
      if(g[v].size() != 0)border.push(pii(v, prev));
      continue;
    }
    for (int i = g[v][0].next; i < g[v].end() - 1; i+=g[v][i].next) {
      edge &e = g[v][i];
      que.push(piii(d + 1, pii(e.to, v)));
      g[v].RemoveEdge(i);
      g[e.to].RemoveEdge(e.rev);
      addlist.RemoveEdge(e.id);
      if(e.id == p){
        p += addlist[p].next;
      }
      st.push(piii(d, pii(v, e.to)));
    }
  }
  
  while(not coordinate.empty()){
    while(not border.empty() and border.front().second == coordinate.front().first){
      int v = border.front().first;
      border.pop();
      for (int i = g[v][0].next; i < g[v].end() - 1; i+=g[v][i].next) {
        edge &e = g[v][i];
        g[v].RemoveEdge(i);
        g[e.to].RemoveEdge(e.rev);
        addlist.RemoveEdge(e.id);
        if(e.id == p){
          p += addlist[p].next;
        }
        st.push(piii(1e9, pii(v, e.to)));
      }
    }
    //ans.push_back(coordinate.front().second);
    coordinate.pop();
    res += EnumIMatch(addlist, g, p);
    //ans.pop_back();
    RestoreSomeEdges(st, addlist, g, p, 1e9);
  }
  RestoreSomeEdges(st, addlist, g, p, 1);
  return res;
}

int ManyChildren(int x, EdgeList &addlist, Graph &g,
                std::stack<piii> &st, int &p){
  std::queue<int> v;
  for (int i = g[x][0].next; i < g[x].end() - 1; i+=g[x][i].next) {
    v.push(g[x][i].to);
 }
  int res = Normal(x, addlist, g, st, p);
  while(not v.empty()){
    res += Normal(v.front(), addlist, g, st, p);
    v.pop();
 }
  return res;
}

int countNeighbor(int x, Graph &g){
  int neigbor = 0;
  for (int i = g[x][0].next; i < g[x].end() - 1; i+=g[x][i].next) {
    neigbor += g[i].size();
  }
  return neigbor;
}

int EnumIMatch(EdgeList &addlist, Graph &g, int p){
  if(p >= addlist.end() - 1){
    //std::cout << "ans:";
    // for (int i = 0; i < ans.size(); i++) {
    //   std::cout << ans[i] << " ";
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
    return 1;
  }
  int x;
  if(g[addlist[p].from].size() > g[addlist[p].to].size()){
    x = addlist[p].from;
  }else{
    x = addlist[p].to;
  }
  int res;
  std::stack<piii> st;
  if(countNeighbor(x, g) >= addlist.size()/2){
    res = ManyChildren(x, addlist, g, st, p);
  }else{
    res = Normal(x, addlist, g, st, p);
  }
  res += EnumIMatch(addlist, g, p);
  RestoreSomeEdges(st, addlist, g, p, 0);
  return res;
}
