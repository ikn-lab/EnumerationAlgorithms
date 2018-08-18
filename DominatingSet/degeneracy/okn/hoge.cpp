#include<iostream>
using namespace std;

int main(){
  int n = 30;
  std::cout << n << std::endl;
  for (int i = 0; i < n - 1; i++) {
    std::cout << i << " " << i + 1 << std::endl;
  }
  return 0;
}

