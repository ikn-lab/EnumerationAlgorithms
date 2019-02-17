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
  //opening output files
 
  int n;
  double t1, t2;//for time measurement
    

  //initialize Graph
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.c_str(), "%d\n", &n);
  
  next_permutation np(n);
  
  //O(1) enumeration 
  t1 = gettimeofday_sec();
  int cnt = 0;
  while(np.next()){
    // np.printPerm();
    cnt++;
  }
  std::cout << cnt << std::endl;
  t2 = gettimeofday_sec();
  std::cout << "time:" << t2 - t1 << std::endl;
  std::cout << std::endl;
  return 0;
}
