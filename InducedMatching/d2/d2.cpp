#include<vector>
#include<unordered_set>

#include"d2.hpp"
#include"basicDataStructure.hpp"
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

FixedQueue<pii> que;
FixedStack<int> st;

bigint RecIM(EdgeList &addlist, Graph &g, std::vector<bigint> &ans, int p = 1, int size =  0){
  if(p >= addlist.size() - 1){
    ans[size]++;
    return 1;
  }
  int qsize = que.size();
  int ssize =  st.size();
  que.push(pii(0, addlist[p].from));
  que.push(pii(0 ,addlist[p].to));
  int next = p + addlist[p].next;
  while(que.size() > qsize){
    int v = que.front().second;
    int dist = que.front().first;
    que.pop();
    if(dist >= 2)continue;
    for (int i = g[v][0].next; i < g[v].size() - 1; i+=g[v][i].next) {
      edge &e = g[v][i];
      que.push(pii(dist + 1, e.to));
      g[v].RemoveEdge(i);
      g[e.to].RemoveEdge(e.rev);
      addlist.RemoveEdge(e.id);
      if(e.id == next){
        next += addlist[next].next;
      }
      st.push(v);
      st.push(e.to);
    }
  }
  bigint res = RecIM(addlist, g, ans, next, size + 1);
  while(st.size() > ssize){
    int v = st.top();
    st.pop();
    g[v].RestoreEdge();
    v = st.top();
    st.pop();
    g[v].RestoreEdge();
    addlist.RestoreEdge();
  }
  res += RecIM(addlist, g, ans, p + addlist[p].next, size);
  return res;
}

bigint EIMMain(EdgeList &addlist, Graph &g, std::vector<bigint> &ans){
  int n = g.size(), d = 0;
  for (int i = 0; i < n; i++) {
    d = std::max(d, g[i].size());
  }
  que.resize(g.size()*d*d);
  st.resize(g.size()*d*d);
  return RecIM(addlist, g, ans);
}
