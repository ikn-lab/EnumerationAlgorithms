////////////////////////////////////
/*                                */
/* Enumeration induced matching   */
/* constant amortize time         */
/* kurita                         */
/*                                */
////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

#include"constant.hpp"
#include"graph.hpp"
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int bigint;
// typedef long long int bigint;

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
  for (int i = 0; i < n; i++) {
    g.AddEdge(i, edge(-1, -1, 1, -1));
  }
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    g.AddEdge(u, edge(v, g[v].end() + 1, g[u].end() + 2, g[u].end()));
    g.AddEdge(v, edge(u, g[u].end()    , g[v].end() + 2, g[v].end()));
    m++;
  }
  for (int i = 0; i < n; i++) {
    g.AddEdge(i, edge(-1, -1, 1e9, g[i].end()));
  }
  g.MakeVlist();

  std::vector<bigint> ans(n/2, 0);
  auto start = std::chrono::system_clock::now();
  bigint solution = EnumIMatch(g, ans);
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  printf("%lld\n", std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
  std::cout << (solution) << std::endl;
  // printf("elapsed time = %lld msec.\n", std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
  // std::cout << "the number of induced matching:" << (solution) << std::endl;
  // bigint sum = 0;
  // for(int i = 0; i < ans.size(); i++) {
  //   if(ans[i] == 0)break;
  //   printf("%2d ", i);
  //   std::cout << (ans[i]) << std::endl;
  //   sum += ans[i];
  // }
  // if(solution != sum){
  //   std::cout << "error" << std::endl;
  //   std::cout << "solution:" << (solution) << std::endl;
  //   std::cout << " sum:" << (sum) << std::endl;
  // }
  // std::cout << "density:" << (double)m/n << std::endl;
  return 0;
}
