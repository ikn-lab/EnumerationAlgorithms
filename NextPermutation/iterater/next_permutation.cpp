#include<stack>
#include<iostream>
#include"next_permutation.hpp"

next_permutation::next_permutation(int n_): n(n_) {
  perm = new int[n];
  for (int i = 0; i < n; i++) perm[i] = i;
  elem = (1 << n) - 1;
  st.resize(n*n + 10);
  for (int i = n - 1; i >= 0; i--) {
    st.push(std::tuple<int, int>(1, i));//d, i        
  }
}


bool next_permutation::next(){
  while(not st.empty()){
    d = std::get<0>(st.top());
    i = std::get<1>(st.top());
    st.pop();
    if(d < 0){
      elem += (1 << i); //add
    }else if(d == n){
      perm[d - 1] = i;
      return true;
    }else{
      elem -= (1 << i); //remove
      perm[d - 1] = i;
      tmp = elem;
      st.push(std::tuple<int, int>(-d, i));//d, i
      for (i = 32 - __builtin_clz(tmp); tmp != 0; i = 32 - __builtin_clz(tmp)) {
        st.push(std::tuple<int, int>(d + 1, i - 1));//d, i
        tmp -= (1 << (i - 1));
      }
    }
  }
  return false;
}

void next_permutation::printPerm(){
  for (int i = 1; i < n; i++) {
    std::cout << perm[i] - 1 << " ";
  }
  std::cout << std::endl;
}
