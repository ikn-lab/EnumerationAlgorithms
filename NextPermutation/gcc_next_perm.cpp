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
  vector<vector<int> > ans;
  // do{
  //   vector<int> tmp;
  //   for (int i = 0; i < n; i++) {
  //     tmp.push_back(a[i]);
  //   }
  //   ans.push_back(tmp);
  // }while(next_permutation(a.begin(), a.end()));
  while(next_permutation(a.begin(), a.end()));
  // for (int i = ans.size() - 1; i >= 0; i--) {
  //   for (int j = 0; j < ans[i].size(); j++) {
  //     std::cout << ans[i][j] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  t2 = gettimeofday_sec();
  std::cout << t2 - t1 << std::endl;
  
  return 0;
}
