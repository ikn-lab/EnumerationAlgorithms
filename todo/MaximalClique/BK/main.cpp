//////////////////////////////////////////////////////////////////
/*                                                               */
/*  title:Enumeration Algorihtms for Chordal Induced  Bipaprtite */
/*        Graphs of a Bipartite Graph                            */
/*  author: Bron, Kerbosch                                       */
/*                                                               */
/*                                                               */
/*                                                               */
/* Enumeration Clique                                            */
/* kurita                                                        */
/*                                                               */
//////////////////////////////////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

#include"Graph.hpp"
#include"Enum.hpp"
// #define DEBUG

using bigint = long long int;

int main(int argc, char *argv[]){
  if(argc != 2){
    std::cerr << "Error : The number of input file is not 2" <<std::endl;
    return 0;
  }
  
  std::ifstream ist(argv[1], std::ios::in);
  if(!ist){
    std::cerr << "can't open input file: " << argv[1] << std::endl;
    return 0;
  }
  int n, m, cnt = 0;
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d %d", &n, &m);
  std::vector<std::vector<edge> > _G(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    _G[u].push_back(edge(u, v, cnt));
    _G[v].push_back(edge(v, u, cnt++));
  }
  std::cout << "vertices:" << n << " edges:" << m << std::endl;
  // if(not isBipartite(_G)){
  //   std::cerr << "The input graph is not bipartite grpah. " << std::endl;
  //   return 0;
  // }
  EC ec(_G);
  auto start = std::chrono::system_clock::now();
  ec.Enumerate();
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  std::cout << "elapsed time = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()
            << " msec."
            << std::endl;  
  ecib.print();
  return 0;
}

