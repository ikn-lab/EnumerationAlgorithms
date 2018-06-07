#include"topological.hpp"
#include"reverse_search.hpp"
#include"topological_ordering_enumeration.hpp"

TopologicalOrderingEnumeration::
TopologicalOrderingEnumeration(Graph &g){
  init(g);
}

void TopologicalOrderingEnumeration::
init(Graph &g){
  G = g;
  tp = topoSort(G);
  init_val = vector<int>();
  S.resize(1);
  S[0].resize(tp.size());
  for (int i = 0; i < S[0].size(); i++) {
    S[0][i] = i;
  }
  delta = tp.size() - 2;
};

void TopologicalOrderingEnumeration::
printState(){
  std::cout << "delta  :" << delta << std::endl;
  std::cout << "n      :" << G.size() << std::endl;
  std::cout << "topological sort:" << std::endl;
  for (int i = 0; i < tp.size(); i++) {
    std::cout << tp[i] << " ";
  }
  std::cout << std::endl;

  // std::cout << "adj_mat:" << std::endl;
  // for (int i = 0; i < G.size(); i++) {
  //   for (int j = 0; j < G.size(); j++) {
  //     printf("%2d ", G[i][j]);
  //   }
  //   std::cout << std::endl;
  // }
  std::cout << std::endl;
}


vector<int> TopologicalOrderingEnumeration::
LocalSearch(vector<int> v){
  for (int i = 0; i < v.size() - 1; i++) {
    if(v[i] <= v[i + 1] ||
       G.isEdge(tp[ v[i] ], tp[ v[i + 1] ]))continue;
    swap(v[i], v[i + 1]);
    break;
  }

  return v;
}


vector<int> TopologicalOrderingEnumeration::
Adj(vector<int> v, int k){
  if(G.isEdge(tp[ v[k] ], tp[ v[k + 1] ]) == false){
    swap(v[k], v[k + 1]);
    return v;
  }
  return vector<int>();
}

void TopologicalOrderingEnumeration::
printPerm(vector<int> &v, FILE *rev){
  for (int i = 0; i < v.size(); i++) {
    fprintf(rev, "%d ", v[i]);
  }
  fprintf(rev, "\n");
}

void TopologicalOrderingEnumeration::
printVertex(vector<int> &v, FILE *rev){
  for (int i = 0; i < v.size(); i++) {
    fprintf(rev, "%d ", tp[ v[i] ]);
  }
  fprintf(rev, "\n");
}
