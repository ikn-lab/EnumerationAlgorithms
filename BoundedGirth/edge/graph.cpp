#include<iostream>
#include<cstdio>

#include"graph.hpp"
#include"edgelist.hpp"

// #define DEBUG

// Tail: 0, Head:1
void Graph::AddEdge(int from, int to, int cost){
  G[from].push_back(edge{from, to, G[to].size(), G[from].size(), cost});
  G[to].push_back(edge{to, from, G[from].size() - 1, G[to].size(), cost});
}
        

void Graph::NextCand(edge e){
#ifdef DEBUG
  std::cerr << "start NextCand" << std::endl;
#endif // DEBUG
  solution_size++;
  updateCand(e);
  updateDistance(e);
#ifdef DEBUG
  std::cerr << "end NextCand" << std::endl;
#endif // DEBUG
}

void Graph::updateCand(edge e){
  out2in.push(e), in2del.push(e), out2del.push(e);
  int u = e.from, v = e.to;
  if(deg[u] > 0 and deg[v] > 0){
#ifdef DEBUG
    std::cerr << "inner edge" << std::endl;
#endif
    int tail = 0;
    for (int i = 0; i < (int)Cin.size(); i++) {
      edge &f = Cin[i];
      if(D[f.from][f.to] >= k){
        Cin[tail++] = Cin[i];
        continue;
      }
      int rev = G[f.from][f.pos].rev;
      G[f.from].RemoveEdge(f.pos);
      G[f.to].RemoveEdge(rev);
      in2del.push(f);
    }
    Cin.erase(Cin.begin() + tail, Cin.end());
  }else{
#ifdef DEBUG
    std::cerr << "outer edge" << std::endl;
#endif
    if(deg[v] != 0) std::swap(u, v);
    for (int i = G[v][0].next; i != G[v].end(); i = G[v][i].next) {
      edge &f = G[v][i];
      int w = f.to;
      if(u == w)continue; 
      if(D[u][v] < k){
        int rev = G[v][i].rev;
        G[v].RemoveEdge(i);
        G[w].RemoveEdge(rev);
        out2del.push(f);
      }else if(deg[w] > 0){
        Cin.push_back(f);
        out2in.push(f);
      }else{
        Cout.push_back(f);
        out2del.push(f);
      }
    }
  }
  deg[u]++, deg[v]++;
}


void Graph::updateDistance(edge e){
  int u = e.from, v = e.to;
  dist.push(std::tuple<int, int, int>(-1, -1, -1));
  std::vector<int> A;
  for (int i = 0; i < (int)Cin.size(); i++) {
    if(tmp[Cin[i].from] == 0) A.push_back(Cin[i].from);
    if(tmp[Cin[i].to] == 0) A.push_back(Cin[i].to);
    tmp[Cin[i].from]++, tmp[Cin[i].to]++;
  }
  int tail = 0;
  for (int i = 0; i < (int)Cout.size(); i++) {
    edge &f = Cout[i];
    if(deg[f.from] > 0 and deg[f.to] > 0)continue;
    Cout[tail++] = Cout[i];
    if(deg[f.from] > 0 and tmp[f.from] == 0)A.push_back(f.from);
    if(deg[f.to] > 0 and tmp[f.to] == 0)A.push_back(f.to);
    tmp[f.from]++, tmp[f.to]++;
  }
  Cout.erase(Cout.begin() + tail, Cout.end());
  for (int i = 0; i < (int)Cin.size(); i++) 
    tmp[Cin[i].from]--, tmp[Cin[i].to]--;

  for (int i = 0; i < (int)Cout.size(); i++) 
    tmp[Cout[i].from]--, tmp[Cout[i].to]--;

  for (int x: A){
    for (int y: A){
      int val = std::min(D[x][v] + D[u][y], D[x][u] + D[v][y]);
      D[x][y] = D[y][x] = std::min(D[x][y], val + e.cost);
      dist.push(std::tuple<int, int, int>(x, y, D[x][y]));
    }
  }
}


void Graph::restore(edge e){
  int u = e.from, v = e.to, cost;
  solution_size--;
  if(deg[u] == 1 or deg[v] == 1){//outer edge
    Cin = std::vector<edge>{};
    while(out2in.top() != e){
      Cout.push_back(out2in.top());
      out2in.pop();
    }
    out2in.pop();
    while(out2del.top() != e){
      edge f = out2del.top();
      out2del.pop();
      Cout.push_back(f);
      G[f.from].RestoreEdge();
      G[f.to].RestoreEdge();
    }
    out2del.pop();
    Cout.push_back(e);
  }else{//inner edge
    while(in2del.top() != e){
      edge f = in2del.top();
      in2del.pop();
      Cin.push_back(f);
      G[f.from].RestoreEdge();
      G[f.to].RestoreEdge();
    }
    in2del.pop();
    Cin.push_back(e);
  }
  while(std::get<0>(dist.top()) != -1){
    u    = std::get<0>(dist.top());
    v    = std::get<1>(dist.top());
    cost = std::get<2>(dist.top());
    dist.pop();    
    D[u][v] = D[v][u] = cost;
  }
  dist.pop();
}

edge Graph::GetCand(){
#ifdef DEBUG
  std::cout << "start GetCand" << std::endl;
#endif
  edge res;
  if(not Cin.empty()){
    res = Cin.back();
    Cin.erase(Cin.end() - 1, Cin.end());
  }else{
    res = Cout.back();
    Cout.erase(Cout.end() - 1, Cout.end());
  }
#ifdef DEBUG
  std::cout << "end GetCand" << std::endl;
#endif
  return res; 
}

void Graph::print(){
}
