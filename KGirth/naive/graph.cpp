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
  st.resize(n + 10);
  for (int i = 0; i < n; i++) {
    g[i].push_back(edge(-1, -1, 1, -1));
    g[i].push_back(edge(-1, -1, 1e9, 0));
  }
}
void Graph::MakeVlist(){
  int n = g.size();
  deg = 0;
  for (int i = 0; i < n; i++) {
    deg = std::max(deg, g[i].size());
  }
  deg_boundary.resize(deg + 1, 0);
  id_to_pos.resize(n);
  std::vector<int> bucket[deg + 1];
  for (int i = 0; i < n; i++) {
    bucket[g[i].size()].emplace_back(i);
  }
  
  for (int i = 0; i <= deg; i++) {
    deg_boundary[i] = vlist.size();
    vlist.emplace_back(vertex(-1, 0, vlist.size() + 1, vlist.size() - 1));
    for (int j = 0; j < (int)bucket[i].size(); j++) {
      int id = bucket[i][j];
      id_to_pos[id] = vlist.size();
      vlist.emplace_back(vertex(id, i, vlist.size() + 1, vlist.size() - 1));
    }
  }
  vlist.emplace_back(vertex(-1, 0, vlist.size() + 1, vlist.size() - 1));  
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
inline void Graph::Detach(int id){
  int pos = id_to_pos[id];
  vlist[vlist[pos].prev].next = vlist[pos].next;
  vlist[vlist[pos].next].prev = vlist[pos].prev;
}
inline void Graph::Insert(int id){
  int pos = id_to_pos[id];
  
  // insert position
  int ipos = deg_boundary[vlist[pos].deg];
  vlist[pos].prev = ipos;
  vlist[pos].next = vlist[ipos].next;
  vlist[vlist[ipos].next].prev = vlist[ipos].next = pos;
}
void Graph::RemoveVertex(int id){
  Detach(id);
  st.push(id);
  for (int i = g[id][0].next; i != g[id].end(); i=g[id][i].next) {
    int adj_id  = g[id][i].to;
    int adj_pos = id_to_pos[adj_id];
    int     rev = g[id][i].rev;
    g[adj_id].RemoveEdge(rev);
    Detach(adj_id);
    --vlist[adj_pos].deg;
    Insert(adj_id);
  }
  while(deg != 0 and vlist[vlist[deg_boundary[deg]].next].id == -1)--deg;
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
    Insert(id);
    deg = std::max(deg, vlist[id_to_pos[id]].deg);
    for (int i = g[id][0].next; i != g[id].end(); i=g[id][i].next) {
      int adj_id  = g[id][i].to, adj_pos = id_to_pos[adj_id];
      g[adj_id].RestoreEdge();
      Detach(adj_id);
      ++vlist[adj_pos].deg;
      deg = std::max(deg, vlist[adj_pos].deg);
      Insert(adj_id);
    }
  }
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
  std::cout << "--------------------" << std::endl;
  std::cout << "vlist size:" << vlist.size() << std::endl;
  
  for (int i = vlist[0].next; i < (int)vlist.size(); i=vlist[i].next) {
    vlist[i].print();
  }

  std::cout << std::endl;
}
