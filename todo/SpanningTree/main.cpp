///////////////////////////////////////////////////
/*                                               */
/* Enumeration spanning tree                     */
/* constant amortize time                        */
/* constant time enumeration by amortization     */
/* kurita                                        */
/*                                               */
///////////////////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>

#include"enum.hpp"
#include"graph.hpp"
#define DEBUG

// #include <boost/multiprecision/cpp_int.hpp>

// typedef boost::multiprecision::cpp_int bigint;
typedef long long int bigint;

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
  sscanf(tmp.data(), "%d", &n);
  Graph g(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    g.AddEdge(u, v);
    m++;
  }
  
  
  int ans = EnumSpanningTree(g);
  std::cout << ans << std::endl;
  // bigint sum = 0;
  // for(int i = 0; i < ans.size(); i++) {
  //   sum += ans[i];
  // }
  // std::cout << sum << std::endl;
  // for(int i = 0; i < ans.size(); i++) {
  //   if(ans[i] == 0)break;
  //   printf("%2d ", i);
  //   std::cout << (ans[i]) << std::endl;
  //   sum += ans[i];
  // }
  // std::cout << "density:" << (double)m/n << std::endl;
  return 0;
}
