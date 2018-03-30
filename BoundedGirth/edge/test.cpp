#include<vector>
#include<tuple>
#include<iostream>

#include"Enum.hpp"
#include"Graph.hpp"
#include"AddibleList.hpp"
#define DELIM 0

using bigint = long long int;
using triple = std::tuple<int, int, int>;//x, y, cost

std::vector<bigint> result;
AddibleList<edge> solution;

std::vector<int> A, tmp;
std::vector<std::vector<int> > D;
std::vector<triple> stack_D;//a stack for D
std::vector<int> stack_G;
int head_D = -1, head_G = -1, k;
AddibleList<edge> Cin, Cout;
std::vector<int> deg;

void print(AddibleList<edge> &list){
  for (int i = list.begin(); i != list.end(); i = list.GetNext(i)) {
    printf("%d %d %d\n", list[i].u, list[i].v, list[i].id);
  }
}

void NextCand(Graph &G, edge e, bool isInner){
#ifdef DEBUG
  printf("start NextCand\n");
#endif // DEBUG
  solution.add(e.id);
  G.RemoveEdge(e.id);
  updateCand(G, e, isInner);
  updateDistance(G, e);
#ifdef DEBUG
  printf("end NextCand\n");
#endif // DEBUG
}

void updateCand(Graph &G, edge e, bool isInner) {
  int u = e.u, v = e.v;
  if(isInner) {
#ifdef DEBUG
    printf("inner edge\n");
#endif
    stack_G[++head_G] = 1;
    for (int i = Cin.begin(); i != Cin.end(); i=Cin.GetNext(i)) {
      edge &f = Cin[i];
      int girth = std::min(D[f.u][u] + D[v][f.v], D[f.u][v] + D[u][f.v]) + e.cost + f.cost;
      girth = std::min(girth, D[f.u][f.v] + f.cost);
      if(girth >= k)continue;
      i = Cin.remove(f.id);
      G.RemoveEdge(f.id);
      stack_G[head_G]++;
    }
  }else{
#ifdef DEBUG
    printf("outer edge\n");
#endif
    if(deg[v] != 0) std::swap(u, v);
    stack_G[++head_G] = DELIM;
    for (int i = G[v].begin(); i != G[v].end(); i = G[v].GetNext(i)) {
      edge &f = G[v][i];
      if(u == f.v)continue;
      head_G++;
      if(D[u][f.v] + e.cost + f.cost < k){
        i = G.RemoveEdge(f.id, v);
        Cout.remove(f.id);
        stack_G[head_G] = -1;
      }else if(deg[f.v] > 0){
        Cin.add(f.id);
        Cout.remove(f.id);
        stack_G[head_G] = -2;
      }else{
        Cout.add(f.id);
        stack_G[head_G] = -3;
      }
    }
  }
  deg[u]++, deg[v]++;
}


void updateDistance(Graph &G, edge e) {
  int u = e.u, v = e.v, size = 0;
  for (int i = Cin.begin(); i != Cin.end(); i=Cin.GetNext(i)){
    if(tmp[Cin[i].u] == 0) A[size++] = Cin[i].u;
    if(tmp[Cin[i].v] == 0) A[size++] = Cin[i].v;
    tmp[Cin[i].u]++, tmp[Cin[i].v]++;
  }
  for (int i = Cout.begin(); i != Cout.end(); i=Cout.GetNext(i)) {
    edge &f = Cout[i];
    if(deg[f.u] > 0 and tmp[f.u] == 0)A[size++] = f.u;
    if(deg[f.v] > 0 and tmp[f.v] == 0)A[size++] = f.v;
    tmp[f.u]++, tmp[f.v]++;
  }
  for (int i = Cin.begin(); i != Cin.end(); i=Cin.GetNext(i))
    tmp[Cin[i].u]--, tmp[Cin[i].v]--;
  for (int i = Cout.begin(); i != Cout.end(); i=Cout.GetNext(i))
    tmp[Cout[i].u]--, tmp[Cout[i].v]--;
  int cnt = 0;
  for (int i = 0; i < size; i++){
    for (int j = i + 1; j < size; j++){
      int x = A[i], y = A[j];
      int val = std::min(D[x][v] + D[u][y], D[x][u] + D[v][y]) + e.cost;
      if(val >= D[x][y])continue;
      stack_D[++head_D] = triple(x, y, D[x][y]);
      D[x][y] = D[y][x] = val;
      cnt++;
    }
  }
  stack_D[++head_D] = triple(-1, -1, cnt);
}

void restore(Graph &G, edge e, bool isInner){
  int u, v, c;
  solution.undo();
  if(isInner){//inner edge
    for (int i = 0; i < stack_G[head_G] - 1; i++) 
      Cin.undo(), G.undo();
    head_G--;
  }else{//outer edge
    for(; stack_G[head_G] < 0; head_G--){
      if(stack_G[head_G] == -1)G.undo();
      if(stack_G[head_G] == -2)Cin.undo();
      Cout.undo();
    }
    head_G--;
  }
  int cnt = std::get<2>(stack_D[head_D--]);
  for (int i = 0; i < cnt; i++) {
    u = std::get<0>(stack_D[head_D]);
    v = std::get<1>(stack_D[head_D]);
    c = std::get<2>(stack_D[head_D--]);
    D[u][v] = D[v][u] = c;
  }
  deg[e.u]--, deg[e.v]--;
}

bool GetCand(edge &e){
  if(not Cin.empty()){
    e = Cin[Cin.begin()];
    Cin.remove(e.id);
    return true;
  }else{
    e = Cout[Cout.begin()];
    Cout.remove(e.id);
    return false;
  }
}

void NextCandFirstEdge(Graph &G, edge e){
  const int u = e.u, v = e.v;
  for (int i = G[v].begin(); i != G[v].end(); i = G[v].GetNext(i)) {
    edge &f = G[v][i];
    if(u == f.v)continue;
    Cout.add(f.id);
  }
  for (int i = G[u].begin(); i != G[u].end(); i = G[u].GetNext(i)) {
    edge &f = G[u][i];
    if(v == f.v)continue;
    Cout.add(f.id);
  }
  D[u][v] = D[v][u] = 1;
  G.RemoveEdge(e.id);
  solution.add(e.id);
  deg[u]++, deg[v]++;
}

void restoreFirstEdge(Graph &G, edge e){
  const int u = e.u, v = e.v;
  for (int i = G[v].begin(); i != G[v].end(); i = G[v].GetNext(i)) {
    edge &f = G[v][i];
    if(u == f.v)continue;
    Cout.undo();
  }
  for (int i = G[u].begin(); i != G[u].end(); i = G[u].GetNext(i)) {
    edge &f = G[u][i];
    if(v == f.v)continue;
    Cout.undo();
  }
  D[u][v] = D[v][u] = 1e9;
  solution.undo();
  deg[u]--, deg[v]--;
}


void RecEBG(Graph &G, int k){
#ifdef DEBUG
  printf("sol size %lld\n", solution.size());
  printf("Cin\n");
  print(Cin);
  printf("Cout\n");
  print(Cout);
  printf("degree\n");
  for (int i = 0; i < G.size(); i++)
    printf("%d ", deg[i]);
  printf("\n\n");
#endif  
  if(Cin.empty() and Cout.empty()){
    result[solution.size()]++;
    return;
  }
  edge e;
  bool isInner = GetCand(e);
  NextCand(G, e, isInner);
  RecEBG(G, k);
  restore(G, e, isInner);
  
  RecEBG(G, k);
  G.undo();
  if(isInner)Cin.undo();
  else Cout.undo();
}

std::vector<bigint> EBGMain(Graph &G, int _k){
  int n = G.size(), m = G.edgeSize();
  std::vector<edge> ve(m);
  result.resize(m + 1, 0);
  result[0] = 1;
  k = _k;
  
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) 
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) 
      ve[G[i][j].id] = G[i][j];
  
  Cin.init(ve), Cout.init(ve);
  solution.init(ve);
  D.resize(n), deg.resize(n, 0);
  for (int i = 0; i < G.size(); i++) {
    D[i].resize(n, 1e9);
    D[i][i] = 0; 
  }
  stack_D.resize(n*n*n);
  stack_G.resize(2*m, 1e9);
  A.resize(n, 0), tmp.resize(n, 0);
  for (int i = 0; i < m; i++) {
    printf("now %d\n", i);
    edge &e = ve[i];
    NextCandFirstEdge(G, e);
    RecEBG(G, k);
#ifdef DEBUG
    printf("end Rec:%d/%d\n", i, m);
#endif
    restoreFirstEdge(G, e);
    // G.print();
  }
  return result;
}
