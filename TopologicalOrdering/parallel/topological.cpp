#include"graph.hpp"
#include"topological.hpp"
using namespace std;

bool hasInputEdge(Graph &dag, int node){
  for (int i = 0; i < dag.size(); i++) {
    if(dag[node][i] != -1)continue;
    return false;
  }
  return true;
}

vector<int> topoSort(Graph dag){
  int n = dag.size();
  queue<int> s;
  vector<int> res;
  //入力辺の持たないノードをqueue sに入れる
  for(int i = 0; i < n; i++){
    if(hasInputEdge(dag, i))
      s.push(i);
  }
  //std::cout << s.size() << std::endl;
  while(s.empty() != true){
    res.push_back(s.front());
    int s_front = s.front();
    s.pop();
    //delete input edge
    for (int i = 0; i < n; i++) {
      if(dag[s_front][i] == 1){
        dag[s_front][i] = 0;
        dag[i][s_front] = 0;
        if(hasInputEdge(dag, i))
          s.push(i);
      }
    }
  }
  return res;
}

