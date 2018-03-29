///////////////////////////////////////////////////////////////////
/*                                                               */
/* Enumeration of connected incued subgraph with large girth     */
/* O(\sum_{S \in \mathcal S}\size{N[S]}) total time              */
/* writer: kazuhiro kurita                                       */
/*                                                               */
///////////////////////////////////////////////////////////////////
// #define DEBUG

#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

#include"Graph.hpp"
#include"Enum.hpp"
#include"List.hpp"
#include"Element.hpp"
#include"AddibleList.hpp"

using bigint = long long int;

int main(int argc, char *argv[]){
#ifdef DEBUG
  std::cerr << "Debug mode" << std::endl;
#endif //Debug mode
  
  if(argc != 3){
    std::cerr << "Error : The number of input file is not 3" <<std::endl;
    return 0;
  }
  std::ifstream ist(argv[1], std::ios::in);
  if(!ist){
    std::cerr << "can't open input file: " << argv[1] << std::endl;
    return 0;
  }
  int n, m, k = std::stoi(argv[2]), id = 0;
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d %d", &n, &m);
  std::vector<std::vector<edge> > _G(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    _G[u].push_back(edge(u, v, id));
    _G[v].push_back(edge(v, u, id++));
  }
  Graph G(_G);
  std::cout << "n:" << G.size() << std::endl;
  
  auto start = std::chrono::system_clock::now();
  std::vector<bigint> ans = EBGMain(G, k);
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  printf("elapsed time = %lld msec.\n", std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
  bigint sum = 0;
  for(int i = 0; i < (int)ans.size(); i++) {
    sum += ans[i];
  }
  std::cout << sum << std::endl;
  for(int i = 0; i < (int)ans.size(); i++) {
    printf("%2d ", i);
    std::cout << ans[i] << std::endl;
    sum += ans[i];
  }
  // g.print();
  return 0;
}
