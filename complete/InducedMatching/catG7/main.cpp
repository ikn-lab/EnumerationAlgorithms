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
#include"constant.hpp"

int main(int argc, char *argv[]){
  if(argc != 2){
    std::cerr << "Error : The number of input file is not 2" << std::endl;
    return 0;
  }
  
  std::ifstream ist(argv[1], std::ios::in);
  if(!ist){
    std::cerr << "can't open input file: " << argv[1] << std::endl;
    return 0;
  }
  std::string tmp;
  getline(ist, tmp);
  int n;
  sscanf(tmp.data(), "%d", &n);
  Graph g(n);
  for (int i = 0; i < n; i++) {
    g[i].push_back(edge());
  }
  int u, v, id = 0;
  EdgeList addlist;
  addlist.push_back(edge());
  while(getline(ist, tmp)){
    sscanf(tmp.data(), "%d %d", &u, &v);
    g[u].push_back(edge(u, v, g[v].end(), ++id, 1, 1));
    g[v].push_back(edge(v, u, g[u].end()-1, id, 1, 1));
    addlist.push_back(edge(u, v, -1, id, 1, 1));
  }
  addlist.push_back(edge(-1,-1,-1,++id,0,1));
  for (int i = 0; i < n; i++) {
    g[i].push_back(edge(-1,-1,-1,id,0,1));
  }
  std::cout << EnumIMatch(addlist, g, 1) << std::endl;
  return 0;
}
