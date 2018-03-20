#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

#include"graph.hpp"
using pii = std::pair<int, int>;

void EdgeList::print(){
  std::cout << "print elist" << std::endl;
  for (int i = elist[0].next; i != end(); i=elist[i].next) {
    std::cout << "from:" << i << " to:" << elist[i].to << std::endl;
  }
  std::cout << std::endl;
}

void EdgeList::RemoveEdge(int id){
  st.push(id);
  elist[elist[id].prev].next = elist[id].next;
  elist[elist[id].next].prev = elist[id].prev;
  s--;
}

void EdgeList::RestoreEdge(){
  if(st.empty()){
    std::cerr << "stack is empty(edge)" << std::endl;
    exit(1);
  }
  int id = st.top();
  st.pop();
  elist[elist[id].prev].next = id;
  elist[elist[id].next].prev = id;
  s++;
}

void Graph::AddEdge(int u, int v){
  m++;
  if((int)history.size() - n < m){
    history.resize(2*m + n + 9);
    bridge.resize(2*m + 9);
  }
  int next = 1, prev = g[u][1].prev;
  g[u][prev].next = g[u][next].prev = g[u].size() + 2;
  g[u].push_back(edge(v, g[v].size() + 2, 1, prev));
  prev = g[v][1].prev;
  g[v][prev].next = g[v][next].prev = g[v].size() + 2;
  g[v].push_back(edge(u, g[u].size() + 1, 1, prev));
}


int Graph::Contract(int u, int v){
  printf("start contract: %d %d\n", u, v);
  g_tail++, n--;
  history[history_size++] = pii(-1, -1);
  int x = g_tail, x_size = 2;
  g[x][0] = edge(-1, -1, 1, -1);
  g[x][1] = edge(-1, -1, 1e9, 0);
  for (int w: std::vector<int>{u, v}){
    std::cout << "w:" << w << std::endl;
    std::cout << "to:";
    for (int i = g[w][0].next; i != g[w].end(); i = g[w][i].next) {
      // std::cout << "i:" << i << std::endl;
      int to = g[w][i].to, rev = g[w][i].rev;
      std::cout << to  << " ";
#ifdef DEBUG
      if(i == 0){
        std::cerr << "error: i do not become 0 in Contract" << std::endl;
        exit(0);
      }
#endif
      history[history_size++] = pii(w, i);
      if(to == u or to == v)continue;
      // AddEdge(g_tail, to);
      
      int next = 1, prev = g[x][1].prev;
      g[x][prev].next = g[x][next].prev = x_size++;
      g[x].push_back(edge(to, rev, next, prev));
      // if(x_size - 2 >= g[x].size()){
      //   g[x].push_back(edge(to, rev, next, prev));
      // }else{
      //   g[x][x_size] = edge(to, rev, next, prev);
      // }
      g[to][rev].to = x;
      g[to][rev].rev = g[x].size() + 2;
    }
    std::cout << std::endl;
  }
  std::cout << "x_size:" << g[x].size() << std::endl;
  std::cout << "end contract" << std::endl;
  return g_tail;
}

void Graph::Uncontract(){
  std::cout << "start uncotract" << std::endl;
  g[g_tail--] = EdgeList();
  n++;
  while(history[--history_size] != pii(-1, -1)){
    m--;
    int w  = history[history_size].first;
    std::cout << "history:" << history[history_size].second << std::endl;
    edge& e = g[w][history[history_size].second];
    std::cout << "w  in uncotract:" << w    << std::endl;
    std::cout << "to in uncotract:" << e.to << std::endl;
    g[e.to][e.rev].to = w;
    g[e.to][e.rev].rev = history[history_size].second;
  }
  history_size--;
  std::cout << "end uncotract" << std::endl;
}



int Graph::EnumBridgeAndContract(){
  std::cout << "start EnumBridgeAndContract" << std::endl;
  for (int i = 0; i < node.size(); i++)
    node[i] = Node{-1, (int)1e9};
  v_ord = bridge_size = 0, Dfs(g_tail, -1);
  std::cout << "end EnumBridgeAndContract" << std::endl;
  return bridge_size;
}

int Graph::Dfs(int v, int previous){
  node[v].ord = node[v].low = v_ord++;
  std::cout << "bridge_size:" << bridge_size << std::endl;
  std::cout << "v:" << v << " previous:" << previous << std::endl;
  bool first = true;
  for (int i = g[v][0].next; i != g[v].end(); i = g[v][i].next) {
    int to = g[v][i].to;
    printf("to: %d, i: %d\n", to, i);
    if(previous == to and first) {
      first = false;
      continue; 
    }else if(node[to].ord == -1){
      if(Dfs(to, v) != -1){
        v = g_tail, i = g[v][0].next;
      }
      to = g[v][i].to; 
    }
    node[v].low = std::min(node[v].low, node[to].low);
  }
  if(node[v].low == node[v].ord and previous != -1){
    // bridge[bridge_size++] = pii(previous, v);
    bridge_size++;
    Contract(v, previous);
    node[g_tail] = node[previous];
    std::cout << "low:" << node[previous].low << std::endl;
    std::cout << "ord:" << node[previous].ord << std::endl;
    std::cout << "low:" << node[v].low << std::endl;
    std::cout << "ord:" << node[v].ord << std::endl;
  std::cout << "backtracking v:" << v << " previous:" << previous << std::endl;

    std::cout << v_ord << std::endl;
    return g_tail;
  }
  return -1;
}

