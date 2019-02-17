#include<vector>
#include<tuple>
#include<iostream>

#include"Enum.hpp"
#include"Graph.hpp"
#include"AddibleList.hpp"
#define DELIM 0
// #define DEBUG
// using bigint = long long int;

void EBGIterator::nextCand(edge e, bool isInner){
  solution.add(e.id);
  G.RemoveEdge(e.id);
  updateCand(e, isInner);
  updateDistance(e);
}

void EBGIterator::updateCand(edge e, bool isInner) {
  int u = e.from, v = e.to;
  if(isInner) {
    stack_G[++head_G] = 1;
    for (int i = Cin.begin(); i != Cin.end(); i=Cin.GetNext(i)) {
      edge &f = Cin[i];
      int girth = std::min(D[f.from][u] + D[v][f.to], D[f.from][v] + D[u][f.to]) + e.cost + f.cost;
      girth = std::min(girth, D[f.from][f.to] + f.cost);
      if(girth >= k)continue;
      i = Cin.remove(f.id);
      G.RemoveEdge(f.id);
      stack_G[head_G]++;
    }
  }else{
    int V[2] = {u, v};
    stack_G[++head_G] = DELIM;
    for (int i = 0; i < 2; i++) {
      int x = V[i], y = V[((i + 1)&1)];
      if(deg[x] != 0)continue;
      for (int j = G[x].begin(); j != G[x].end(); j = G[x].GetNext(j)) {
        edge &f = G[x][j];
        if(y == f.to)continue;
        if(D[y][f.to] + e.cost + f.cost < k){
          j = G.RemoveEdge(f.id, x);
          Cout.remove(f.id);
          stack_G[++head_G] = -1;
        }else if(deg[f.to] > 0){
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
  sol_size += (deg[e.from] == 0) + (deg[e.to] == 0);
  deg[e.from]++, deg[e.to]++;
}

void EBGIterator::updateDistance(edge e) {
  int u = e.from, v = e.to, size = 0;
  for (int i = Cin.begin(); i != Cin.end(); i=Cin.GetNext(i)){
    if(A[n + Cin[i].from] == 0) A[size++] = Cin[i].from;
    if(A[n + Cin[i].to] == 0) A[size++] = Cin[i].to;
    A[n + Cin[i].from]++, A[n + Cin[i].to]++;
  }
  for (int i = Cout.begin(); i != Cout.end(); i=Cout.GetNext(i)) {
    edge &f = Cout[i];
    if(deg[f.from] > 0 and A[n + f.from] == 0)A[size++] = f.from;
    if(deg[f.to] > 0 and A[n + f.to] == 0)A[size++] = f.to;
    A[n + f.from]++, A[n + f.to]++;
  }
  for (int i = Cin.begin(); i != Cin.end(); i=Cin.GetNext(i))
    A[n + Cin[i].from]--, A[n + Cin[i].to]--;
  for (int i = Cout.begin(); i != Cout.end(); i=Cout.GetNext(i))
    A[n + Cout[i].from]--, A[n + Cout[i].to]--;
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
  stack_D[++head_D] = cnt;
}

void EBGIterator::restore(edge e, bool isInner){
  int u = e.from, v = e.to, cost = e.cost;
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
  int cnt = stack_D[head_D--];
  for (int i = 0; i < cnt; i++, head_D -= 3) {
    cost = stack_D[head_D    ];
    v    = stack_D[head_D - 1];
    u    = stack_D[head_D - 2];
    D[u][v] = D[v][u] = cost;
  }
  deg[e.from]--, deg[e.to]--;
  sol_size -= (deg[e.from] == 0) + (deg[e.to] == 0);
}

edge EBGIterator::GetCand(){
  edge e;
  if(solution.size() == 0) {
    return G.GetEdge(loop++);
  }else if(not Cin.empty()){
    e = Cin[Cin.begin()];
    Cin.remove(e.id);
  }else{
    e = Cout[Cout.begin()];
    Cout.remove(e.id);
  }
  return e;
}

bool EBGIterator::skip(){
  if(head == -1)return false;
  if(head == 0){
    restore(stack_E[0], false);
    loop++;
    if(loop >= m)return false;
    head--;
    return traverse();
  }
  return next(true);
}

bool EBGIterator::next(bool isBackTrack) {
  // pruning for dentist solution. 
  // if(density.GetNume()*sol_size < solution.size()*density.GetDeno()){
  //   density = Fraction{solution.size(), sol_size};
  //   dense_solution_size = 0;
    // for (int i = solution.begin(); i != solution.end(); i = solution.GetNext(i))
    //   std::cout << solution[i] << " ";
    // std::cout << std::endl;
  
  if(loop >= m)return false;//end
  //root iteration
  if(isBackTrack){
    edge &e = stack_E[head];
    if(head == 0){
      head--;
      restore(stack_E[0], false);
      return traverse();
    }
    if(stack_P[head] == 0){//down right
      restore(e, (deg[e.from] > 1 and deg[e.to] > 1));
      stack_P[head] = 1;
      return next();
    }
    head--;
    //back tracking
    G.undo();
    if(deg[e.from] > 0 and deg[e.to] > 0)Cin.undo();
    else Cout.undo();
    return next(true);
  }
  if(head == -1)return traverse();
  // leaf iteration
  if(Cin.empty() and Cout.empty()) return next(true);
  return traverse();  
}


bool EBGIterator::traverse(){
  edge e = GetCand();
  head++;
  stack_E[head] = e;
  stack_P[head] = 0;
  nextCand(e, (deg[e.from] > 0 and deg[e.to] > 0));
  result[solution.size()]++;
  return true;
}

EBGIterator::EBGIterator(std::vector<std::vector<edge> > _G, int _k):k(_k){
  G.init(_G);
  n = G.size(), m = G.edgeSize();
  std::vector<edge> ve(m);
  result = new bigint[m + 1];
  result[0] = 1;
  dentist_solution = new edge[m];
  D = new int*[n];
  stack_D = new int[4*n*n*n];
  stack_G = new int[3*m];
  stack_P = new int[m];
  stack_E = new edge[m];
  deg = new int[n];
  A = new int[2*n];
  
  for (int i = 1; i < m; i++) result[i] = 0, stack_P[i] = 1e9;
  
  for (int i = G.begin(); i != G.end(); i = G.GetNext(i)) 
    for (int j = G[i].begin(); j != G[i].end(); j = G[i].GetNext(j)) 
      ve[G[i][j].id] = G[i][j];

  Cin.init(ve), Cout.init(ve);
  solution.init(ve);
  
  for (int i = 0; i < n; i++) {
    D[i] = new int[n];
    for (int j = 0; j < n; j++) D[i][j] = 1e9;
    deg[i] = A[i] = A[i + n] = 0;
    D[i][i] = 0; 
  }
}

EBGIterator::~EBGIterator(){
  delete stack_G;
  delete stack_D;
  delete stack_E;
  delete stack_P;
  delete A;
  delete deg;
  for (int i = 0; i < n; i++)delete D[i];
  delete D;
  delete result;
}

void EBGIterator::printSolution(){
  std::cout << "solution:" << std::endl;
  for (int i = solution.begin(); i != solution.end(); i = solution.GetNext(i)) {
    std::cout << solution[i].from << " " << solution[i].to << std::endl;
  }
}
