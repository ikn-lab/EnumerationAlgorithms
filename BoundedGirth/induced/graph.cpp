#include<iostream>
#include<cstdio>

#include"graph.hpp"

void Graph::AddEdge(int u, int v){
  g[u].push_back(v), g[v].push_back(u);
};

void Graph::NextCand(int v){
  // s.insert(v);
  stv.push(v);
  solution_size++;
  used[v] = true;
  st1.push(std::tuple<int, int, int>(-1, -1, -1));
  updateCand(v);
  update1(v);
  update2(v);
}

void Graph::updateCand(int v){
  // cand.erase(v);
  for (int i = 0; i < (int)g[v].size(); i++) {
    int u = g[v][i];
    if(not used[u] and cand.find(u) == cand.end()) {
      st1.push(std::tuple<int, int, int>(v, u, 1e9));
      m[v][u] = m[u][v] = 1;
      cand.insert(u); 
    }
  }
  for (auto u = cand.begin(); u != cand.end();){
    if(m[v][*u] + ms[v][*u] >= k) {
      u++;
      continue;
    }
    used[*u] = true;
    stv.push(*u);
    u = cand.erase(u);
  }
}

void Graph::update1(int v){
  for (int u: cand) {
    for (int w: cand) {
      if(m[u][w] > m[u][v] + m[v][w]){
        st1.push(std::tuple<int, int, int>(u, w, m[u][w]));
        m[u][w] = m[u][v] + m[v][w];
      }
    }
    for (int w: s){
      if(m[u][w] >  m[u][v] + m[v][w]){
        st1.push(std::tuple<int, int, int>(u, w, m[u][w]));
        m[u][w] = m[u][v] + m[v][w];
      }
    }
  }
}


void Graph::update2(int v){
  st2.push(std::tuple<int, int, int>(-1, -1, -1));
  for (int u: cand){
    for (int w: cand){
      int p1 = std::min(m[u][w], m[u][v] + m[v][w]);
      int p2 = std::min(ms[u][w], std::max(m[u][w], m[u][v] + m[v][w]));
      if(p1 + p2 >= k) p2 = findSecondMininum(u, w);
      if(ms[u][w] > p2){
        st2.push(std::tuple<int, int, int>(u, w, ms[u][w]));
        ms[u][w] = p2;
      }
    }
  }
}

int Graph::findSecondMininum(int from, int to){
  int mini = 1e9, mini2 = 1e9;
  for (int i = 0; i < (int)g[from].size(); i++) {
    int v = g[from][i];
    if(used[v] and mini >= m[v][to] + 1){
      mini2 = mini;
      mini = m[v][to] + 1;
    }
  }
  return mini2;
}

void Graph::restore(int v){
  used[v] = false;
  // s.erase(v);
  solution_size--;
  int u, w, cost;
  while(std::get<0>(st1.top()) != -1){
    u    = std::get<0>(st1.top());
    w    = std::get<1>(st1.top());
    cost = std::get<2>(st1.top());
    st1.pop();    
    m[u][w] = m[w][u] = cost;
  }
  st1.pop();
  while(std::get<0>(st2.top()) != -1){
    u    = std::get<0>(st2.top());
    w    = std::get<1>(st2.top());
    cost = std::get<2>(st2.top());
    st2.pop();
    ms[u][w] = cost;
  }
  st2.pop();
  while(stv.top() != v){
    used[stv.top()] = false;
    stv.pop();
  }
  stv.pop();
}

void Graph::print(){
  printf("status used\n");
  for (int i = 0; i < (int)g.size(); i++) {
    printf("%d ", (int)used[i]);
  }
  printf("\n");
  printf("status m\n");
  for (int i = 0; i < (int)g.size(); i++) {
    for (int j = 0; j < (int)g.size(); j++) {
      printf("%10d ", m[i][j]);
    }
    printf("\n");
  }

  printf("status ms\n");
  for (int i = 0; i < (int)g.size(); i++) {
    for (int j = 0; j < (int)g.size(); j++) {
      printf("%10d ", ms[i][j]);
    }
    printf("\n");
  }
  std::cout << "size of cand:" << cand.size() << std::endl;
  std::cout << std::endl;
}
