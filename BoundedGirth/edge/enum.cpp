#include<vector>
#include<tuple>
#include<iostream>

#include"Enum.hpp"
#include"Graph.hpp"
#include"AddibleList.hpp"
#define DELIM 0
// #define DEBUG
using bigint = long long int;

void print(AddibleList<edge> &list){
  std::cout << "Graph:" << std::endl;
  for (int i = list.begin(); i != list.end(); i = list.GetNext(i)) {
    printf("%d %d %d\n", list[i].u, list[i].v, list[i].id);
  }
}

void EBGIterator::NextCand(edge e, bool isInner){
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

void EBGIterator::updateCand(edge e, bool isInner) {
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
    stack_G[++head_G] = DELIM;
    for (int i = G[v].begin(); i != G[v].end() and deg[v] == 0; i = G[v].GetNext(i)) {
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
    for (int i = G[u].begin(); i != G[u].end() and deg[u] == 0; i = G[u].GetNext(i)) {
      edge &f = G[u][i];
      if(v == f.v)continue;
       head_G++;
      if(D[v][f.v] + e.cost + f.cost < k){
        i = G.RemoveEdge(f.id, u);
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
  deg[e.u]++, deg[e.v]++;
}


void EBGIterator::updateDistance(edge e) {
  int u = e.u, v = e.v, size = 0, n = G.size();
  for (int i = Cin.begin(); i != Cin.end(); i=Cin.GetNext(i)){
    if(A[n + Cin[i].u] == 0) A[size++] = Cin[i].u;
    if(A[n + Cin[i].v] == 0) A[size++] = Cin[i].v;
    A[n + Cin[i].u]++, A[n + Cin[i].v]++;
  }
  for (int i = Cout.begin(); i != Cout.end(); i=Cout.GetNext(i)) {
    edge &f = Cout[i];
    if(deg[f.u] > 0 and A[n + f.u] == 0)A[size++] = f.u;
    if(deg[f.v] > 0 and A[n + f.v] == 0)A[size++] = f.v;
    A[n + f.u]++, A[n + f.v]++;
  }
  for (int i = Cin.begin(); i != Cin.end(); i=Cin.GetNext(i))
    A[n + Cin[i].u]--, A[n + Cin[i].v]--;
  for (int i = Cout.begin(); i != Cout.end(); i=Cout.GetNext(i))
    A[n + Cout[i].u]--, A[n + Cout[i].v]--;
  int cnt = 0;
  for (int i = 0; i < size; i++){
    for (int j = i + 1; j < size; j++){
      int x = A[i], y = A[j];
      int val = std::min(D[x][v] + D[u][y], D[x][u] + D[v][y]) + e.cost;
      if(val >= D[x][y])continue;
      stack_D[++head_D] = x;
      stack_D[++head_D] = y;
      stack_D[++head_D] = D[x][y];
      D[x][y] = D[y][x] = val;
      cnt++;
    }
  }
  stack_D[++head_D] = -1;
  stack_D[++head_D] = -1;
  stack_D[++head_D] = cnt;
}

void EBGIterator::restore(edge e, bool isInner){
  int u = e.u, v = e.v, cost = e.cost;
  solution.undo();
  if(isInner){//inner edge
    for (int i = 0; i < stack_G[head_G] - 1; i++) {
      Cin.undo();
      G.undo();
    }
    head_G--;
  }else{//outer edge
    for(; stack_G[head_G] < 0; head_G--){
      if(stack_G[head_G] == -1)G.undo();
      if(stack_G[head_G] == -2)Cin.undo();
      Cout.undo();
    }
    head_G--;
  }
  int cnt = stack_D[head_D];
  head_D -= 3
  for (int i = 0; i < cnt; i++) {
    cost = stack_D[head_D--];
    v    = stack_D[head_D--];
    u    = stack_D[head_D--];
    D[u][v] = D[v][u] = cost;
  }
  deg[e.u]--, deg[e.v]--;
}

bool EBGIterator::GetCand(edge &e){
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

void EBGIterator::NextCandFirstEdge(edge e){
  int u = e.u, v = e.v;
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
  D[e.u][e.v] = D[e.v][e.u] = 1;
  G.RemoveEdge(e.id);
  solution.add(e.id);
  deg[e.u]++, deg[e.v]++;
}

void EBGIterator::restoreFirstEdge(edge e){
  int u = e.u, v = e.v;
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
  D[e.u][e.v] = D[e.v][e.u] = 1e9;
  solution.undo();
  deg[e.u]--, deg[e.v]--;
}


void EBGIterator::RecEBG(Graph &G, int k){
  {
#ifdef DEBUG
  printf("sol size %d\n", solution.size());
  printf("Cin\n");
  print(Cin);
  printf("Cout\n");
  print(Cout);
  printf("degree\n");
  for (int i = 0; i < G.size(); i++)
    printf("%d ", deg[i]);
  printf("\n\n");
#endif
  }
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


bool EBGIterator::next(){
  int i = stack_L[head_L];
  edge e;
  bool isInner;
  if(head_L == 0){
    if(i == m)return false;
    e = G.GetEdge(i);
    NextCandFirstEdge(e);
    stack_L[++head_L] = 0;
    stack_I[++haed_I] = false;
    stack_E[++haed_E] = e;
  }else{
    if(Cin.empty() and Cout.empty()){
      if(head_L == 1)restoreFirstEdge(e);
      else restore(e);
      head_L--, head_I--, head_E--;
      return next();
    }
    e = stack_E[head_E];
    isInner = GetCand(e);
    NextCand(e, isInner);
    stack_L[head_L]++;
    stack_I[++head_I] = isInner;
    stack_E[++head_E] = e;
  }
  return true;
}


EBGIterator::EBGIterator(std::vector<std::vector<edge> > _G, int _k):k(_k){
  G.init(_G);
  int n = G.size(), m = G.edgeSize();
  std::vector<edge> ve(m);
  result.resize(m + 1, 0);
  D.resize(n);
  stack_D = new int[3*n*n*n];
  stack_G = new int[2*m];
  stack_L = new int[m];
  stack_I = new bool[m];
  stack_E = new edge[m];
  deg = new int[n];
  A = new int[2*n];
  stack_L[0] = 0;
  
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) 
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) 
      ve[G[i][j].id] = G[i][j];
  
  Cin.init(ve), Cout.init(ve);
  solution.init(ve);
  
  for (int i = 0; i < n; i++) {
    deg[i] = A[i] = A[i + n] = 0;
    D[i].resize(n, 1e9);
    D[i][i] = 0; 
  }
  
  result[0] = 1;
}

EBGIterator::~EBGIterator(){
  delete stack_G;
  delete stack_D;
  delete stack_L;
  delete stack_I;
  delete stack_E;
  delete A;
  delete deg;
}
