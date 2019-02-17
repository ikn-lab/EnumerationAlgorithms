#include<vector>
#include<unordered_set>
#include<queue>

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
  // std::cout << "foo" << std::endl;
  if(p >= addlist.size() - 1){
    // std::cout << "size:" << size << std::endl;
    // std::cout << "ans[" << size << "]:" << ans[size] << std::endl;
    ans[size]++;
    // std::cout << "size:" << size << std::endl;
    return 1;
  }
  // std::cout << "fuga" << std::endl;
  int qsize = que.size();
  int ssize =  st.size();
  que.push(pii(0, addlist[p].from));
  que.push(pii(0 ,addlist[p].to));
  g.dist[addlist[p].from] = 0;
  g.dist[addlist[p].to  ] = 0;

  // std::cout << "hoge" << std::endl;
  std::queue<int> visited;
  visited.push(addlist[p].from);
  visited.push(addlist[p].to);
  int next = p + addlist[p].next;
  int u = addlist[p].to;
  for (int i = g[u][0].next; i < g[u].size() - 1; i+=g[u][i].next) {
    if(g[u][i].to == addlist[p].from)g[u].RemoveEdge(i), g[g[u][i].to].RemoveEdge(g[u][i].rev);
  }
  while(que.size() > qsize){
    int v = que.front().second;
    int dist = que.front().first;
    que.pop();
    if(dist  >= 2)continue;
    for (int i = g[v][0].next; i < g[v].size() - 1; i+=g[v][i].next) {
      edge &e = g[v][i];
      if(g.dist[e.to] <= dist)continue;
      g.dist[e.to] = dist;
      que.push(pii(dist + 1, e.to));
      visited.push(e.to);
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
  while(not visited.empty())g.dist[visited.front()] = 1e9, visited.pop();
  // std::cout << "traverse 1" << std::endl;
  bigint res = RecIM(addlist, g, ans, next, size + 1);
  // std::cout << "rec 1" << std::endl;
  // std::cout << "hoge " << p << " " << ssize << " " << st.size() << std::endl;
  while(st.size() > ssize){
    // std::cout << st.size() << std::endl;
    int v = st.top();
    st.pop();
    // std::cout << "v:" << v << std::endl;
    g[v].RestoreEdge();
    v = st.top();
    // std::cout << "u:" << v << std::endl;
    st.pop();
    g[v].RestoreEdge();
    addlist.RestoreEdge();
  }
  // std::cout << "fuga" << std::endl;
  // std::cout << "traverse 2" << std::endl;
  res += RecIM(addlist, g, ans, p + addlist[p].next, size);
  // std::cout << "rec 2" << std::endl;
  g[addlist[p].from].RestoreEdge();
  g[addlist[p].to  ].RestoreEdge();
  return res;
}

bigint EIMMain(EdgeList &addlist, Graph &g, std::vector<bigint> &ans){
  int n = g.size(), d = 0;
  for (int i = 0; i < n; i++) {
    d = std::max(d, g[i].size());
  }
  que.resize(g.size()*d*d*3);
  st.resize(g.size()*d*d*3);
  return RecIM(addlist, g, ans);
}
