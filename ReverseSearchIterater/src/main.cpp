/****************************************/
/*                                      */
/*  reverse search for enumeration      */
/*  of topological ordering             */
/*                                      */
/****************************************/
#include<iostream>
#include<fstream>
#include<sys/time.h>
#include"dominating_set.hpp"
#include"graph.hpp"
#include"reverse_search.hpp"

//this function is used for time measurement
double gettimeofday_sec(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}


int main(int argc, char *argv[]){
  const int num_file = 2;
  if(argc != num_file){
    std::cerr << "Error : The number of input file is not " <<
      num_file << std::endl;
    return 0;
  }
  //opening input file
  std::ifstream ist(argv[1], std::ios::in);
  if(!ist){
    std::cerr << "can't open input file: " << argv[1] << std::endl;
    return 0;
  }
 
  int n, m;
  double t1, t2;//for time measurement
    


  //initialize Graph
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.c_str(), "%d %d\n", &n, &m);
  Graph G(n);
  while(getline(ist, tmp)){
    int to, from;
    sscanf(tmp.c_str(), "%d %d\n", &from, &to);
    G.AddEdge(to, from);
  }
  std::cout << G.size() << std::endl;
  DominatingSetEnumerator EDS(G);
  while(getchar() == '\n'){
    std::vector<int>* X = EDS.next();
    if(X == NULL)break;
    for (int i = 0; i < X->size(); i++) {
      std::cout << (*X)[i] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
