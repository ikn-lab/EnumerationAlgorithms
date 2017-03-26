#include<iostream>
#include<vector>
#include<random>
#include<queue>
using namespace std;

bool bfs(int n, vector<vector<int> > &dag, int node){
  bool visited[n];
  memset(visited, 0, sizeof(visited));
  queue<int> que;
  que.push(node);
  while(!que.empty()){
    int pos = que.front();que.pop();
    visited[pos] = true;
    for (int i: dag[pos]) {
      if(visited[i] == false){
        visited[i] = true;
        que.push(i);
      }else{
        return false;
      }
    }
  }
  return true;
}

int main(int argc, char *argv[]){
  if(argc != 3){
    cerr << "Error input size is 3" << endl;
  }
    
  vector<vector<int> > dag;
  std::random_device rd;
  std::mt19937 mt(rd());
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  std::uniform_int_distribution<int> edge(0, n - 1);
  dag.resize(n);
  
  std::cout << n << " " << m << std::endl;
  for (int i = 0; i < m; i++) {
    int to = edge(mt), from = edge(mt);
    bool multi_edge = false;
    for (int j = 0; j < dag[from].size(); j++) {
      if(to == dag[from][j])multi_edge = true;
    }
    dag[from].push_back(to);
    if(!bfs(n, dag, from) || to == from || multi_edge){
      dag[from].pop_back();
      i--;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j: dag[i]){
      std::cout << i << " " << j << std::endl;
    }
  }
  
  return 0;
}
