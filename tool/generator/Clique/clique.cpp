#include<iostream>
using namespace std;

int main(){
  int n = 8;
  std::cout << n << " " << n*(n-1)/2<< std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      std::cout << i << " " << j << std::endl;
    }
  }
  return 0;
}
