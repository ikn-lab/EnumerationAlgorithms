////////////////////////////////////
/*                                */
/* Enumeration induced matching   */
/* amortize O(|D^2|)  kurita      */
/*                                */
////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include"naive.hpp"
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int bigint;

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
  std::string tmp;
  getline(ist, tmp);
  int n, gomi;
  sscanf(tmp.data(), "%d %d", &n, &gomi);
  Graph g(n);
  int u, v, id = 0;
  std::vector<edge> m;
  while(getline(ist, tmp)){
    sscanf(tmp.data(), "%d %d", &u, &v);
    g[u].push_back((edge){u, v, id});
    g[v].push_back((edge){v, u, id});
    m.push_back((edge){u, v, id++});
  }
  std::vector<int> addlist(m.size(), 0);
  std::vector<int> ans(m.size(), 0);
  std::cout << EnumIMatch(m, addlist, ans, g) << std::endl;
  for (int i = 0; i < ans.size(); i++) {
    if(ans[i] == 0)break;
    std::cout << i << " " << ans[i] << std::endl;    
  }
  return 0;
}
