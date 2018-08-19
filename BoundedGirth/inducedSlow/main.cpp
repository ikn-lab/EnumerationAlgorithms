///////////////////////////////////////////////////////////////////
/*                                                               */
/* Enumeration of connected incued subgraph with large girth     */
/* O(\sum_{S \in \mathcal S}\size{N[S]}) total time              */
/* writer: kazuhiro kurita                                       */
/*                                                               */
///////////////////////////////////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

#include"graph.hpp"
#include"enum.hpp"
// #define DEBUG

using bigint = long long int;

int main(int argc, char *argv[]){
  if(argc != 3){
    std::cerr << "Error : The number of input file is not 3" <<std::endl;
    return 0;
  }
  
  std::ifstream ist(argv[1], std::ios::in);
  if(!ist){
    std::cerr << "can't open input file: " << argv[1] << std::endl;
    return 0;
  }
  int n, m = 0, k = std::stoi(argv[2]);
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d", &n);
  Graph g(n, k);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    g.AddEdge(u, v);
    m++;
  }
  // g.print();
  std::cout << "n:" << g.size() << std::endl;
  
  auto start = std::chrono::system_clock::now();
  std::vector<bigint> ans = ELGMain(g);
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
