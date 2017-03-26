#include<iostream>
#include<vector>
#include"graph.hpp"
using namespace std;

Graph::Graph(int _n){
  n = _n;
  adj_mat.resize(n);
  for (int i = 0; i < n; i++) {
    adj_mat[i].resize(n);
  }
}

void Graph::resize(int _n){
  n = _n;
  adj_mat.resize(n);
  for (int i = 0; i < n; i++) {
    adj_mat[i].resize(n);
  }
}

void Graph::AddEdge(int to, int from){
  adj_mat[to][from] = -1;
  adj_mat[from][to] = 1;
}

vector<int>& Graph::operator[](int i) {
  if(i >= n){
    std::cerr << "Error adjcent matrix size is " << n << std::endl;
    abort();
  }
  return adj_mat[i];
}

Graph& Graph::operator=(Graph &G){
  this->resize(G.size());
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      adj_mat[i][j] = G[i][j];
    }
  }
  return *this;
}

void Graph::printGraph(){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << adj_mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int Graph::size() const{
  return n;
};

bool Graph::isEdge(int to, int from){
  if(adj_mat[to][from] == 1 ||
     adj_mat[from][to] == 1){
    return true;
  }else{
    return false;
  }
}
