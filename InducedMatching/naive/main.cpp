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
using pii = std::pair<int, int>;
using piii = std::pair<pii ,int>;

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
  Graph G(n);
  int u, v, id = 0;
  std::vector<edge> m;
  while(getline(ist, tmp)){
    sscanf(tmp.data(), "%d %d", &u, &v);
    G[u].push_back((edge){u, v, id});
    G[v].push_back((edge){v, u, id});
    m.push_back((edge){u, v, id++});
  }
  std::vector<int> ans(m.size(), 0), solution(m.size(), 0), count(n, 0);
  auto start = std::chrono::system_clock::now();
  std::cout << EnumIMatch(m, ans, G, solution, count) << std::endl;
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  printf("%lld\n", std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
  for (int i = 0; i < ans.size(); i++) {
    if(ans[i] == 0)break;
    std::cout << ans[i] << std::endl;    
  }
  std::cout << std::endl;
  for (int i = 0; i < count.size(); i++) {
    std::cout << count[i] << std::endl;
  }
  return 0;
}



