#include<vector>
#include<string>
#include<algorithm>

#include"graph.hpp"
#include"basicDataStructure.hpp"

void EdgeList::print(){
  std::cout << std::endl;
  std::cout << "print elist" << std::endl;
  for (int i = elist[0].next; i < (int)elist.size() - 1; i=elist[i].next) {
    std::cout << "from:" << i << " to:" << elist[i].to << std::endl;
  }
  std::cout << std::endl;
}

void EdgeList::RemoveEdge(int id){
  st.push(id);
  elist[elist[id].prev].next = elist[id].next;
  elist[elist[id].next].prev = elist[id].prev;
  --s;
}

void EdgeList::RestoreEdge(){
#ifdef DEBUG
  if(st.empty()){
    std::cerr << "stack is empty(edge)" << std::endl;
    exit(1);
  }
#endif
  int id = st.top();
  ++s;
  st.pop();
  elist[elist[id].prev].next = elist[elist[id].next].prev = id;    
}

void EdgeList::push_back(edge e){
  ++s;
  elist.push_back(e);
  if(s >= ss){
    ss <<= 1;
    st.resize(ss);
  }
}

Graph::Graph(int n){
  g.resize(n);
  bt.resize(n);
  ord.resize(n);
  low.resize(n);
  v_to_bt.resize(n, -1);
  st.resize(n + 10);
  for (int i = 0; i < n; i++) {
    g[i].push_back(edge(-1, -1, 1, -1));
    g[i].push_back(edge(-1, -1, 1e9, 0));
  }
}

void Graph::AddEdge(int from, int to){
  int prev = g[from][1].prev;
  g[from][1].prev    = g[from].size() + 2;
  g[from][prev].next = g[from].size() + 2;
  g[from].push_back(edge(to, g[to].size() + 2, 1, prev));

  prev = g[to][1].prev;
  g[to][1].prev    = g[to].size() + 2;
  g[to][prev].next = g[to].size() + 2;
  g[to].push_back(edge(from, g[from].size() + 1, 1, prev));
}


void Graph::RemoveVertex(int id){
  st.push(id);
  for (int i = g[id][0].next; i != g[id].end(); i=g[id][i].next) {
    int adj_id  = g[id][i].to;
    int    rev = g[id][i].rev;
    g[adj_id].RemoveEdge(rev);
  }
}

void Graph::RestoreVertex(int cnt){
  for (;cnt > 0;--cnt) {
#ifdef DEBUG
    if(st.empty()){
      std::cerr << "stack is empty(vertex)" << std::endl;
      exit(1);
    }
#endif
    int id = st.top();
    st.pop();
    for (int i = g[id][0].next; i != g[id].end(); i=g[id][i].next) {
      int adj_id  = g[id][i].to;
      g[adj_id].RestoreEdge();
    }
  }
}
void Graph::init(int n){
  g.resize(n);
  st.resize(n + 10);
  for (int i = 0; i < n; i++) {
    g[i].push_back(edge(-1, -1, 1, -1));
    g[i].push_back(edge(-1, -1, 1e9, 0));
  }
}
void Graph::dfs(int v, int previous){
  int to, cnt = 0, isAP = 0;
  ord[v] = low[v] = v_ord++;
  for (int i = 0; i < g[v].size(); i++) {
    to = g[v][i].to;
    if(previous == to)continue;
    cnt += (ord[to] == -1);
    if(ord[to] == -1){
      dfs(to, v); 
      low[v] = std::min(low[v], low[to]);
      if(ord[v] != 0 and ord[v] <= low[to]){
        isAP++;
        bt[bt_size].AddEdge(bt_size, bt_size + isAP);
      }
    }
    low[v] = std::min(low[v], ord[to]);
  }
  if(cnt > 1 and ord[v] == 0)isAP = 1;
  // if(isAP)articulation.push_back(v);
  bt_size += isAP;
  v_to_bt[v] = bt_size;
}


void Graph::print(){
  std::cout << "Graph:" << std::endl;
  std::cout << "--------------------" << std::endl;
  for (int i = 0; i < (int)g.size(); i++) {
    std::cout << "node:" << i << std::endl;
    for (int j = g[i][0].next; j != g[i].end(); j=g[i][j].next) {
      std::cout << g[i][j].to << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
