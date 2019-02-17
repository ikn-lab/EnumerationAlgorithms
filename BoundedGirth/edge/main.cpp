///////////////////////////////////////////////////////////////////
/*                                                               */
/* Enumeration of connected incued subgraph with large girth     */
/* O(\sum_{S \in \mathcal S}\size{N[S]}) total time              */
/* writer: kazuhiro kurita                                       */
/*                                                               */
///////////////////////////////////////////////////////////////////
// #define DEBUG

#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>

#include"Graph.hpp"
#include"Enum.hpp"
#include"List.hpp"
#include"Element.hpp"
#include"AddibleList.hpp"
#include"Fraction.hpp"
using bigint = long long int;

int main(int argc, char *argv[]){
#ifdef DEBUG
  std::cerr << "Debug mode" << std::endl;
#endif //Debug mode
  
  if(argc != 3 and argc != 4){
    std::cerr << "Error : The number of input file is not 3 or 4" <<std::endl;
    return 0;
  }
  std::ifstream ist(argv[1], std::ios::in);
  if(!ist){
    std::cerr << "can't open input file: " << argv[1] << std::endl;
    return 0;
  }
  std::string prune = "";
  if(argc == 4){
    if(std::string(argv[3]) != "-p"){
      std::cerr << "error. " << std::endl;
      exit(1);
    }
    prune = "-p";
  }
  int n, m, k = std::stoi(argv[2]), id = 0;
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d %d", &n, &m);
  std::vector<std::vector<edge> > G(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    G[u].push_back(edge(u, v, id));
    G[v].push_back(edge(v, u, id++));
  }
  auto start = std::chrono::system_clock::now();
  
  bigint* ans;
  ans = new bigint[m + 1];
  for (int i = 0; i <= m; i++) ans[i] = 0;
  EBGIterator EBG(G, k);
  // std::cerr << "run" << std::endl;
  if(prune == "-p"){
    std::cout << "prune. " << std::endl;
    while(EBG.next()) {
      while(EBG.density.GetNume()*EBG.solutionSizeV() >
            EBG.density.GetDeno()*EBG.upperBound()){
        ans[EBG.solution.size()]++;
        if(EBG.skip() == false) break;
      }
      ans[EBG.solution.size()]++;
    }
  }else{
    while(EBG.next()){
      ans[EBG.solution.size()]++;
    }
  }
  // std::cout << "dentist solution" << std::endl;
  // EBG.density.print();
  // for (int i = 0; i < EBG.dense_solution_size; i++) {
  //   std::cout << EBG.dentist_solution[i].from << " " <<
  //             EBG.dentist_solution[i].to << std::endl;
  // }
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  printf("%lld\n", std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
  bigint sum = 0;
  for(int i = 0; i < m + 1; i++) {
    sum += ans[i];
  }
  std::cout << sum << std::endl;
  std::cout << m << std::endl;
  for(int i = 0; i < m + 1; i++) {
    fprintf(stdin, "%2d ", i);
    std::cout << ans[i] << std::endl;
    sum += ans[i];
  }
  delete ans;
  return 0;
}
