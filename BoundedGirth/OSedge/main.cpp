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

#include"Enum.hpp"
using bigint = long long int;

int main(int argc, char *argv[]){
#ifdef DEBUG
  std::cerr << "Debug mode" << std::endl;
#endif //Debug mode
  
  if(argc != 3 and argc != 4){
    std::cerr << "Error : The number of input file is not 3 or 4" <<std::endl;
    return 0;
  }
  std::ifstream ist(argv[1], std::ios::in);
  if(!ist){
    std::cerr << "can't open input file: " << argv[1] << std::endl;
    return 0;
  }
  std::string prune = "";
  if(argc == 4){
    if(std::string(argv[3]) != "-p"){
      std::cerr << "error. " << std::endl;
      exit(1);
    }
    prune = "-p";
  }
  int n, m, k = std::stoi(argv[2]);
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d %d", &n, &m);
  std::vector<std::vector<int> > G(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  auto start = std::chrono::system_clock::now();
  
  EBG ebg(G, k);
  // std::cerr << "run" << std::endl;
  ebg.Enumerate();
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  printf("%lld\n", std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
  ebg.print();
  return 0;
}
