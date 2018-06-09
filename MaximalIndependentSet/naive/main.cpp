////////////////////////////////////
/*                                */
/* Enumeration MIS                */
/* O(nm) Tsukiyama:1977           */
/* writer: kurita                 */
/*                                */
////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

#include"mis.hpp"
typedef long long int lli;

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
  int n;
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d", &n);
  Graph g(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    g[v].emplace_back(u);
    g[u].emplace_back(v);
  }
  for (int i = 0; i < n; i++) {
    sort(g[i].begin(), g[i].end());
  }
  std::cout << "node:" << n << std::endl;
  lli ans = MIS(g);
  std::cout << ans << std::endl;
  return 0;
}







