#include<set>
#include<algorithm>
#include"graph.hpp"
#include"reverse_search.hpp"
#include"dominating_set.hpp"

DominatingSetEnumerator::DominatingSetEnumerator(Graph _G):ReverseSearch<Graph, std::vector<int> >(_G){
  G = input_data = _G;
  std::vector<int> S(G.size());
  for (int i = 0; i < G.size(); i++) S[i] = i;
  InitialState.push_back(S);
  delta = G.size();
}


std::vector<int>* DominatingSetEnumerator::Child(std::vector<int> *X, int k){
  // std::cout << "child start" << k << std::endl;
  std::vector<int>* tmp = new std::vector<int>;
  int pos = X->size() - 1;
  for (int i = 0; i < X->size(); i++) {
    if(i != (*X)[i]){
      pos = i;
      break;
    }
  }
  // std::cout << pos << std::endl;
  for (int i = pos; k >= 0 and i >= 0; i--) {
    *tmp = *X;
    tmp->erase(tmp->begin() + i);
    if(isDominate(*tmp)){
      k--;
      if(k < 0)break;
    }
    if(i == 0)return NULL; 
  }
  // for (int i = 0; i < tmp.size(); i++) {
  //   std::cout << tmp[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "child end" << std::endl;
  return tmp;
}

std::vector<int>* DominatingSetEnumerator::Parent(std::vector<int> *X){
  if(X == NULL){
    std::cerr << "null parent. " << std::endl;
    return NULL; 
  }
  std::vector<int>* res = new std::vector<int>;
  *res = *X;
  // std::cout << "parent start:" <<  G.size() << std::endl;
  for (int i = 0; i < G.size(); i++) {
    if(i != (*X)[i] or i >= X->size()){
      res->push_back(i);
      break;
    }
  }
  sort(res->begin(), res->end());
  // for (int i = 0; i < X.size(); i++) {
  //   std::cout << X[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "parent end" << std::endl;
  return res;
}

bool DominatingSetEnumerator::isDominate(std::vector<int> X){
  // std::cout << "isDominate start" << std::endl;
  std::set<int> S;
  for (int i = 0; i < X.size(); i++) {
    S.insert(X[i]);
    for (int j = 0; j < G[X[i]].size(); j++) {
      S.insert(G[X[i]][j]);
    }
  }
  // std::cout << "isDominate end" << std::endl;
  return S.size() == G.size();
}
