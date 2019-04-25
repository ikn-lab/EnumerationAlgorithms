////////////////////////////////////////
/*                                    */
/* Enumeration of independnet set     */
/* O(1) time per solution             */
/* constraint: \omega(G) is constant  */
/* kurita                             */
/*                                    */
////////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

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
  std::vector<std::vector<int> > G(n, std::vector<int>(n, 0));
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    G[u][v] = G[v][u] = 1;
  }
  std::cout << n << " " << m << std::endl;
  // PARALLEL_EIS eis(G);
  EIS eis(G);
  // std::cout << "degeneracy:" << eds.GetDegeneracy() << std::endl;
  // std::cout << "n:" << eds.size() << std::endl;
  
  auto start = std::chrono::system_clock::now();
  eis.Enumerate();
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  std::cout << "elapsed time = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()
            << " msec."
            << std::endl;  
  eis.print();
  // std::cout << "time:"
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(eds.time).count()
  //           << std::endl;
  return 0;
}





