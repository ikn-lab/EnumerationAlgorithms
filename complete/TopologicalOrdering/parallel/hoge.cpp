#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<unistd.h>
using namespace std;


int main(int argc, char *argv[]){
  int num_of_threads = (int)sysconf(_SC_NPROCESSORS_ONLN);
  std::cout << num_of_threads << std::endl;
  return 0;
}


