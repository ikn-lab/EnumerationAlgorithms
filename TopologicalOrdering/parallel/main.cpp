/****************************************/
/*                                      */
/*  reverse search for enumeration      */
/*  of topological ordering             */
/*                                      */
/****************************************/
#include<iostream>
#include<fstream>
#include<sys/time.h>
#include"graph.hpp"
#include"topological.hpp"
#include"reverse_search_parallel.hpp"
#include"enum_naive.hpp"
#include"swap_and_stack.hpp"
#include"topological_ordering_enumeration.hpp"
using namespace std;


//this function is used for time measurement
double gettimeofday_sec(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}


int main(int argc, char *argv[]){
  const int num_file = 5;
  if(argc != num_file){
    cerr << "Error : The number of input file is not " <<
      num_file << endl;
    return 0;
  }
  //opening input file
  ifstream ist(argv[1], ios::in);
  if(!ist){
    cerr << "can't open input file: " << argv[1] << endl;
    return 0;
  }
  //opening output files
  FILE *naive, *rev, *swap;
  if((naive = fopen(argv[2], "w")) == NULL){
    std::cerr << "can't write file open" << std::endl;
  }
  if((rev = fopen(argv[3], "w")) == NULL){
    std::cerr << "can't write file open" << std::endl;
  }
  if((swap = fopen(argv[4], "w")) == NULL){
    std::cerr << "can't write file open" << std::endl;
  }    
 
  int n, m;
  double t1, t2;//for time measurement
    
  TopologicalOrderingEnumeration toe;
  SwapAndStack sas;
  Graph G;

  //initialize Graph
  string tmp;
  getline(ist, tmp);
  sscanf(tmp.c_str(), "%d %d\n", &n, &m);
  G.resize(n);
  while(getline(ist, tmp)){
    int to, from;
    sscanf(tmp.c_str(), "%d %d\n", &from, &to);
    G.AddEdge(to, from);
  }
  toe.init(G);
  sas.init(G);
  
  std::cout << "initial state:" << std::endl;
  toe.printState();

  
  
  //naive calclation
  std::cout << "naive enumeration" << std::endl;
  t1 = gettimeofday_sec();
  NaiveEnumeration(G, naive);
  t2 = gettimeofday_sec();
  std::cout << "time:" << t2 - t1 << std::endl;
  std::cout << std::endl;


  //reverse search
  std::cout << "reverseSearch" << std::endl;
  t1 = gettimeofday_sec();
  toe.Search(rev);
  t2 = gettimeofday_sec();
  std::cout << "time:" << t2 - t1 << std::endl;
  std::cout << std::endl;

  //O(1) enumeration 
  std::cout << "swapAndStack" << std::endl;
  t1 = gettimeofday_sec();
  sas.Search(swap);
  t2 = gettimeofday_sec();
  std::cout << "time:" << t2 - t1 << std::endl;
  std::cout << std::endl;
  return 0;
}
