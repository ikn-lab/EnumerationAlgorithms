////////////////////////////////////
/*                                */
/* Enumeration dominating set     */
/* O(\Delta^2) time per solution  */
/* kurita                         */
/*                                */
////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

#include"graph.hpp"
#include"enum.hpp"
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
  int n, m = 0;
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d %d", &n, &m);
  Graph g(n);
  m = 0;
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    g.AddEdge(u, v);
    m++;
  }
  // g.DegenerateOrder();
  for (int i = 0; i < g.size(); i++) {
    g.dominated[i] = g[i].size() + 1;
  }
  
  // g.print();
  // std::cout << "degeneracy:" << g.degeneracy << std::endl;
  std::cout << "n:" << g.size() << std::endl;
  std::cout << m << std::endl;
  // std::cout << "dominated:";
  // for (int i = 0; i < n; i++) {
  //   std::cout << g.dominated[i] << " ";
  // }
  // std::cout << std::endl;
  // g.sort();
  
  auto start = std::chrono::system_clock::now();
  std::vector<bigint> ans = EDSMain(g);
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  // std::cout <<  std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()
  //           << std::endl;  
  std::cout <<  "time:" << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()
            << std::endl;  
  bigint sum = 0;
  for(int i = 0; i < ans.size(); i++) {
    sum += ans[i];
  }
  std::cout << sum << std::endl;
  // for(int i = 0; i < ans.size(); i++) {
  //   // printf("%2d ", i);
  //   std::cout << ans[i] << std::endl;
  //   sum += ans[i];
  // }
  // g.print();
  return 0;
}
