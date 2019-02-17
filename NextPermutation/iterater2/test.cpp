#include<iostream>
#include<vector>
#include<sys/time.h>
#include<algorithm>
using namespace std;

//this function is used for time measurement
double gettimeofday_sec(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}


int main(){
  int n;
  std::cin >> n;
  vector<int> a(n, 0);
  double t1, t2;//for time measurement
  for (int i = 0; i < n; i++) a[i] = i;
  t1 = gettimeofday_sec();
  while(next_permutation(a.begin(), a.end()));
  t2 = gettimeofday_sec();
  std::cout << t2 - t1 << std::endl;
  
  return 0;
}
