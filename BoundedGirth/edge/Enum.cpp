#include<vector>
#include<tuple>
#include<iostream>

#include"Enum.hpp"
#include"Graph.hpp"
#include"AddibleList.hpp"
#define DELIM 0
#define DEBUG
using bigint = long long int;

void print(AddibleList<edge> &list){
  std::cout << "Graph:" << std::endl;
  for (int i = list.begin(); i != list.end(); i = list.GetNext(i)) {
    printf("%d %d %d\n", list[i].u, list[i].v, list[i].id);
  }
}

void EBGIterator::nextCand(edge e, bool isInner){
#ifdef DEBUG
  printf("start nextCand\n");
#endif // DEBUG
  solution.add(e.id);
  G.RemoveEdge(e.id);
  updateCand(e, isInner);
  updateDistance(e);
#ifdef DEBUG
  printf("end nextCand\n");
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
    int V[2] = {u, v};
    stack_G[++head_G] = DELIM;
    for (int i = 0; i < 2; i++) {
      int x = V[i], y = V[((i + 1)&1)];
      if(deg[x] != 0)continue;
      for (int j = G[x].begin(); j != G[x].end(); j = G[x].GetNext(j)) {
        edge &f = G[x][j];
        if(y == f.v)continue;
        if(D[y][f.v] + e.cost + f.cost < k){
          j = G.RemoveEdge(f.id, x);
          Cout.remove(f.id);
          stack_G[++head_G] = -1;
        }else if(deg[f.v] > 0){
          Cin.add(f.id);
          Cout.remove(f.id);
          stack_G[++head_G] = -2;
        }else{
          Cout.add(f.id);
          stack_G[++head_G] = -3;
        }
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
      stack_D[head_D + 1] = x;
      stack_D[head_D + 2] = y;
      stack_D[head_D + 3] = D[x][y];
      head_D += 3;
      D[x][y] = D[y][x] = val;
      cnt++;
    }
  }
  stack_D[head_D + 1] = -1;
  stack_D[head_D + 2] = -1;
  stack_D[head_D + 3] = cnt;
  head_D += 3;
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
  for (int i = 0; i < cnt; i++, head_D -= 3) {
    cost = stack_D[head_D    ];
    v    = stack_D[head_D - 1];
    u    = stack_D[head_D - 2];
    D[u][v] = D[v][u] = cost;
  }
  deg[e.u]--, deg[e.v]--;
}

bool EBGIterator::GetCand(edge &e){
  if(depth == 0) {
    e = G.GetEdge(loop++);
    return false;
  }else if(not Cin.empty()){
    e = Cin[Cin.begin()];
    Cin.remove(e.id);
    return true;
  }else{
    e = Cout[Cout.begin()];
    Cout.remove(e.id);
    return false;
  }

}

// void EBGIterator::RecEBG(Graph &G, int k){
//   {
// #ifdef DEBUG
//   printf("sol size %d\n", solution.size());
//   printf("Cin\n");
//   print(Cin);
//   printf("Cout\n");
//   print(Cout);
//   printf("degree\n");
//   for (int i = 0; i < G.size(); i++)
//     printf("%d ", deg[i]);
//   printf("\n\n");
// #endif
//   }
//   if(Cin.empty() and Cout.empty()){
//     result[solution.size()]++;
//     return;
//   }
//   edge e;
//   bool isInner = GetCand(e);
//   nextCand(G, e, isInner);
//   RecEBG(G, k); //back track 0
//   restore(G, e, isInner);
  
//   RecEBG(G, k); //back track 1
//   G.undo();
//   if(isInner)Cin.undo();
//   else Cout.undo();
// }


bool EBGIterator::next(bool isBackTrack) {
  std::cout << "depth:" << depth << std::endl;
  if(solution.size() == 0 and loop == G.edgeSize())return false;//end
  edge e;
  bool isInner = false;

  // leaf iteration
  if(solution.size() != 0 and not isBackTrack and
     Cin.empty() and Cout.empty()) return next(true);    
  
  if(isBackTrack){
    if(head_P == 0){//first forward tracking
      restore(stack_E[head_E], false);
      return next();
    }else if(stack_P[head_P] == 0){//down right
      restore(stack_E[head_E], stack_I[head_I]);
      stack_P[head_P] = 1;
      return next();
    }else{//back tracking
      G.undo();
      if(stack_I[head_I])Cin.undo();
      else Cout.undo();
      head_I--, head_E--, head_P--;
      return next(true);
    }
  }
    
  //down left
  isInner = GetCand(e);
  nextCand(e, isInner);
  head_E++, head_I++, head_P++;
  stack_E[head_E] = e;
  stack_I[head_I] = isInner;
  stack_P[head_P] = 0;
  result[solution.size()]++;
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
  stack_P = new int[m];
  stack_I = new bool[m];
  stack_E = new edge[m];
  deg = new int[n];
  A = new int[2*n];
  
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
  delete stack_I;
  delete stack_E;
  delete stack_P;
  delete A;
  delete deg;
}
