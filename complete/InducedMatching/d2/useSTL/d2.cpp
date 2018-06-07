#include<vector>
#include<queue>
#include<unordered_set>
#include<stack>
#include"d2.hpp"

#include <boost/multiprecision/cpp_int.hpp>
typedef boost::multiprecision::cpp_int bigint;

void EdgeList::RemoveEdge(int id){
  edge &e  = list[id];
  st.push(id);
  list[id - e.prev].next += e.next;
  list[id + e.next].prev += e.prev;
}
void EdgeList::RestoreEdge(){
  if(st.size() == 0){
    std::cerr << "stack is empty" << std::endl;
    exit(1);
  }
  int id = st.top();
  st.pop();
  edge &e  = list[id];
  list[id - e.prev].next = e.prev;
  list[id + e.next].prev = e.next;
}

bigint EIMMain(EdgeList &addlist, Graph &g, int p, std::vector<bigint> &ans, int size){
  if(p >= addlist.size() - 1){
    ans[size]++;
    return 1;
  }
  int qsize = g.que.size();
  int ssize = g.st.size();
  
  g.que.push(pii(0, addlist[p].from));
  g.que.push(pii(0 ,addlist[p].to));
  int next = p + addlist[p].next;
  while(g.que.size() > qsize){
    int v = g.que.front().second;
    int dist = g.que.front().first;
    g.que.pop();
    if(dist >= 2)continue;
    for (int i = g[v][0].next; i < g[v].size() - 1; i+=g[v][i].next) {
      edge &e = g[v][i];
      g.que.push(pii(dist + 1, e.to));
      g[v].RemoveEdge(i);
      g[e.to].RemoveEdge(e.rev);
      addlist.RemoveEdge(e.id);
      if(e.id == next){
        next += addlist[next].next;
      }
      g.st.push(v);
      g.st.push(e.to);
    }
  }
  bigint res = EIMMain(addlist, g, next, ans, size + 1);
  while(g.st.size() > ssize){
    int v = g.st.top();
    g.st.pop();
    g[v].RestoreEdge();
    v = g.st.top();
    g.st.pop();
    g[v].RestoreEdge();
    addlist.RestoreEdge();
  }
  res += EIMMain(addlist, g, p + addlist[p].next, ans, size);
  return res;
}
