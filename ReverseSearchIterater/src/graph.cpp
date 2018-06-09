#include<iostream>
#include<vector>
#include"graph.hpp"
using namespace std;

Graph::Graph(int _n){
  n = _n;
  g.resize(n);
}


void Graph::AddEdge(int to, int from){
  g[from].push_back(to);
  g[to].push_back(from);
}

vector<int>& Graph::operator[](int i) {
  if(not(0 <= i and i < n)){
    std::cerr << "Error: graph size is " << n << std::endl;
    std::cerr << "Vertex id: " << i << std::endl;
    abort();
  }
  return g[i];
}


void Graph::printGraph(){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < g[i].size(); j++) {
      std::cout << g[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int Graph::size() const{
  return n;
};
