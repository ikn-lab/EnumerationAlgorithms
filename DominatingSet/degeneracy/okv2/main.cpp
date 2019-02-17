////////////////////////////////////
/*                                */
/* Enumeration dominating set     */
/* O(k) time per solution  */
/* kurita                         */
/*                                */
////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

#include"Graph.hpp"
#include"Digraph.hpp"
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
  std::vector<std::vector<edge> > H(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    H[u].push_back(edge(u, v, cnt));
    H[v].push_back(edge(v, u, cnt++));
  }
  std::cout << n << " " << m << std::endl;
  EDS eds(H);
  std::cout << "degeneracy:" << eds.GetDegeneracy() << std::endl;
  std::cout << "n:" << eds.size() << std::endl;
  
  auto start = std::chrono::system_clock::now();
  eds.Enumerate();
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()
            << std::endl;  
  eds.print();
  std::cout << "time:"
            << std::chrono::duration_cast<std::chrono::milliseconds>(eds.time).count()
            << std::endl;
  //msec
  return 0;
}
