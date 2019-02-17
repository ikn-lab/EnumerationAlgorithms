/****************************************/
/*                                      */
/*  reverse search for enumeration      */
/*  of topological ordering             */
/*                                      */
/****************************************/
#include<iostream>
#include<fstream>
#include<sys/time.h>
#include"next_permutation.hpp"

//this function is used for time measurement
double gettimeofday_sec(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}


int main(int argc, char *argv[]){
  const int num_file = 3;
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
  //opening output files
  FILE *output;
  if((output = fopen(argv[2], "w")) == NULL){
    std::cerr << "can't write file open" << std::endl;
  }
 
  int n;
  double t1, t2;//for time measurement
    

  //initialize Graph
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.c_str(), "%d\n", &n);
  
    next_permutation np(n);
  
  //O(1) enumeration 
  std::cout << "swapAndStack" << std::endl;
  t1 = gettimeofday_sec();
  np.Enumerate(output);
  t2 = gettimeofday_sec();
  std::cout << "time:" << t2 - t1 << std::endl;
  std::cout << std::endl;
  return 0;
}
