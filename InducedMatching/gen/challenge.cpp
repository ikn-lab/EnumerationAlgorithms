#include<iostream>

int main(int argc, char *argv[]){
  int bip = 100, n = 4*bip - 1;
  std::cout << n << std::endl;
  for (int i = 1; i <= 2*bip; i++) {
    std::cout << "0 " << i << std::endl;
  }
  for (int i = 1; i <= bip;i++) {
    for (int j = 2*bip + 1; j <= 3*bip - 1; j++) {
      std::cout << i << " " << j << std::endl;
    }
  }

  for (int i = bip + 1; i <= 2*bip; i++) {
    for (int j = 3*bip; j <= 4*bip - 2; j++) {
      std::cout << i << " " << j << std::endl;
    }
  }
  for (int i = 2*bip + 1; i <= 3*bip - 1; i++) {
    for (int j = 3*bip; j <= 4*bip - 2; j++) {
      std::cout << i << " " << j << std::endl;
    }
  }
  return 0;
}
