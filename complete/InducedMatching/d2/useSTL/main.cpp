////////////////////////////////////
/*                                */
/* Enumeration induced matching   */
/* amortize O(|Δ^2|) kurita       */
/*                                */
////////////////////////////////////
#include<iostream>
#include<vector>
#include<fstream>
#include"d2.hpp"
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
  int n, m = 0;
  sscanf(tmp.data(), "%d %d", &n, &m);
  m = 0;
  Graph g(n);
  for (int i = 0; i < n; i++) {
    g[i].push_back(edge());
  }
  int u, v, id = 0;
  EdgeList addlist;
  addlist.push_back(edge());
  while(getline(ist, tmp)){
    sscanf(tmp.data(), "%d %d", &u, &v);
    g[u].push_back(edge(u, v, g[v].size(), ++id, 1, 1));
    g[v].push_back(edge(v, u, g[u].size()-1, id, 1, 1));
    addlist.push_back(edge(u, v, -1, id, 1, 1));
    m++;
  }
  addlist.push_back(edge(-1,-1,-1,-1,0,1));
  for (int i = 0; i < n; i++) {
    g[i].push_back(edge(-1,-1,-1,-1,0,1));
  }
  std::vector<bigint> ans(n/2, 0);
  std::cout << EIMMain(addlist, g, 0, ans) << std::endl;
  for (int i = 0; i < n; i++) {
    if(ans[i] == 0)break;
    printf("%2d ", i);
    std::cout << ans[i] << std::endl;
  }
  std::cout << "density:" << (double)m/n << std::endl;
  return 0;
}
