#include<iostream>
#include<cmath>
using namespace std;

int main(int argc, char *argv[]){
  for (int i = 0; i < 10; i++) {
    int n = pow(2, i + 1) - 1;
    std::cout << n << std::endl;
    for (int j = 0; j < n/2; j++) {
      std::cout << j << " " << 2*j + 1 << std::endl;
      std::cout << j << " " << 2*j + 2 << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
