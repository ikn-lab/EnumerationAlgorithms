#include<iostream>
#include<cstdio>

#include"graph.hpp"
#include"edgelist.hpp"

#define DEBUG

// Tail: 0, Head:1
void Graph::AddEdge(int from, int to, int cost){
  Cin.push_back(edge{from, to, G[to].size(), G[from].size(), cost});
  Cout.push_back(edge{from, to, G[to].size(), G[from].size(), cost});
  Cin[0].next = Cout[0].next = 1;
  Cin[1].prev = Cout[1].prev = 0;

  Cin.NotUsed();
  Cout.NotUsed();

  edge_id[from].push_back(m + 2);
  edge_id[to].push_back(m + 2);
  m++;
  
  G[from].push_back(edge{from, to, G[to].size(), G[from].size(), cost});
  G[to].push_back(edge{to, from, G[from].size() - 1, G[to].size(), cost});


  G[from].AllUsed();
  G[to].AllUsed();
}
        

void Graph::NextCand(edge e){
#ifdef DEBUG
  std::cout << "start NextCand" << std::endl;
#endif // DEBUG
  solution_size++;
  updateCand(e);
  updateDistance(e);
#ifdef DEBUG
  std::cout << "end NextCand" << std::endl;
#endif // DEBUG
}

void Graph::updateDistance(edge e){
  int u = e.from, v = e.to;
  dist.push(std::tuple<int, int, int>(-1, -1, -1));
  std::vector<int> A;
  for (int i = Cin[0].next; i != Cin.end(); i=Cin[i].next) {
    if(tmp[Cin[i].from] == 0) A.push_back(Cin[i].from);
    if(tmp[Cin[i].to] == 0) A.push_back(Cin[i].to);
    tmp[Cin[i].from]++, tmp[Cin[i].to]++;
  }
  for (int i = Cout[0].next; i != Cout.end(); i=Cout[i].next) {
    edge &f = Cout[i];
    if(deg[f.from] > 0 and tmp[f.from] == 0)A.push_back(f.from);
    if(deg[f.to] > 0 and tmp[f.to] == 0)A.push_back(f.to);
    tmp[f.from]++, tmp[f.to]++;
  }
  for (int i = Cin[0].next; i != Cin.end(); i=Cin[i].next) 
    tmp[Cin[i].from]--, tmp[Cin[i].to]--;
  for (int i = Cout[0].next; i != Cout.end(); i=Cout[i].next)
    tmp[Cout[i].from]--, tmp[Cout[i].to]--;
  for (int x: A){
    for (int y: A){
      int val = std::min(D[x][v] + D[u][y], D[x][u] + D[v][y]);
      dist.push(std::tuple<int, int, int>(x, y, D[x][y]));
      D[x][y] = D[y][x] = std::min(D[x][y], val + e.cost);
    }
  }
}


void Graph::updateCand(edge e){
  stack.push(element(-1, e));
  int u = e.from, v = e.to;
  if(deg[u] > 0 and deg[v] > 0){
#ifdef DEBUG
    std::cout << "inner edge" << std::endl;
#endif
    for (int i = Cin[0].next; i != Cin.end(); i=Cin[i].next) {
      edge &f = Cin[i];
      if(D[f.from][f.to] >= k)continue;
      Cin.RemoveEdge(i);
      G[f.from].RemoveEdge(f.pos);
      G[f.to].RemoveEdge(f.rev);
      stack.push(element(0, f));
    }
  }else if(deg[u] == 0 and deg[v] == 0){
#ifdef DEBUG
    std::cout << "first edge" << std::endl;
#endif    
    for (int i = G[v][0].next; i != G[v].end(); i = G[v][i].next) {
      edge &f = G[v][i];
      int w = f.to;
      if(u == w)continue;
      Cout.push_back(edge_id[f.from][f.pos]);
      stack.push(element(3, f));
    }
    for (int i = G[u][0].next; i != G[u].end(); i = G[u][i].next) {
      edge &f = G[u][i];
      int w = f.to;
      if(v == w)continue;
      Cout.push_back(edge_id[f.from][f.pos]);
      stack.push(element(3, f));
    }
  }else{
#ifdef DEBUG
    std::cout << "outer edge" << std::endl;
#endif
    if(deg[v] != 0) std::swap(u, v);
    for (int i = G[v][0].next; i != G[v].end(); i = G[v][i].next) {
      edge &f = G[v][i];
      int w = f.to;
      // std::cout << "edge:" << f.from << " " << w << std::endl;
      if(u == w)continue;
      if(D[u][v] < k){
        std::cout << "1" << std::endl;
        G[v].RemoveEdge(i);
        G[w].RemoveEdge(f.rev);
        Cout.RemoveEdge(edge_id[f.from][f.pos]);
        stack.push(element(1, f));
      }else if(deg[w] > 0){
        std::cout << "2" << std::endl;
        Cin.push_back(edge_id[f.from][f.pos]);
        Cout.RemoveEdge(edge_id[f.from][f.pos]);        
        stack.push(element(2, f));
      }else{
        std::cout << "3" << std::endl;
        Cout.push_back(edge_id[f.from][f.pos]);
        stack.push(element(3, f));
      }
    }
  }
  deg[u]++, deg[v]++;
}



void Graph::restore(edge e){
  std::cout << "restore1" << std::endl;
  int u = e.from, v = e.to, cost;
  solution_size--;
  while(stack.top().first != -1){
    int mode = stack.top().first;
    edge f = stack.top().second;
    std::cout << "mode:" << mode << std::endl;
    stack.pop();
    if(mode == 0){// in2del
      Cin.RestoreEdge();
      G[f.from].RestoreEdge();
      G[f.to].RestoreEdge();
    }else if(mode == 1){//out2del
      Cout.RestoreEdge();
      G[f.from].RestoreEdge();
      G[f.to].RestoreEdge();
    }else if(mode == 2){//out2in
      Cout.RestoreEdge();
      Cin.UndoAdd();
    }else if(mode == 3){
      Cout.UndoAdd();
    }else{
      std::cerr << "error" << std::endl;
      std::exit(1);
    }
  }
  stack.pop();
  while(std::get<0>(dist.top()) != -1){
    u    = std::get<0>(dist.top());
    v    = std::get<1>(dist.top());
    cost = std::get<2>(dist.top());
    dist.pop();    
    D[u][v] = D[v][u] = cost;
  }
  dist.pop();
  std::cout << "restore1" << std::endl;
}

  
edge Graph::GetCand(){
#ifdef DEBUG
  std::cout << "start GetCand" << std::endl;
#endif
  edge res;
  if(not Cin.empty()){
    res = Cin[Cin[1].prev];
    Cin.RemoveEdge(Cin[1].prev);
  }else{
    std::cout << "Cout prev" << Cout[1].prev << std::endl;
    int size = 0;
      std::cout << Cout[0].next << " " << Cout[0].prev << " " << 0 << std::endl;    
    for (int i = Cout[0].next; i != Cout.end(); i=Cout[i].next) {
      std::cout << Cout[i].next << " " << Cout[i].prev << " " << i << std::endl;
      size++;
    }
    std::cout << Cout[1].next << " " << Cout[1].prev << " " << 1 << std::endl;        
    std::cout << "Cout size:" << size << std::endl;
    res = Cout[Cout[1].prev];
    Cout.RemoveEdge(Cout[1].prev);
  }
#ifdef DEBUG
  std::cout << "end GetCand" << std::endl;
#endif
  return res; 
}

void Graph::print(){
}


void Graph::addCandidateSet(edge e, EdgeList &cand){
  cand[cand[1].prev].next = edge_id[e.from][e.pos];
  cand[edge_id[e.from][e.pos]].next = 1;
  cand[edge_id[e.from][e.pos]].prev = cand[1].prev;
  cand[1].prev = edge_id[e.from][e.pos];
}
