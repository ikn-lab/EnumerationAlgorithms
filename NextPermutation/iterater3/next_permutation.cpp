#include<stack>
#include<iostream>
#include"next_permutation.hpp"

next_permutation::next_permutation(int n_): n(n_) {
  perm.resize(n);
  for (int i = 0; i < n; i++) perm[i] = i;
  elem.init(n);
  st.resize(n*n + 10);
  st.push(std::tuple<int, int>(1, 0));//d, i, is_left
}


bool next_permutation::next(){
  while(not st.empty()){
    d = std::get<0>(st.top());
    i = std::get<1>(st.top());
    st.pop();
    if(d < 0){
      elem.undo();
      continue;
    }
    elem.remove(i);
    if(d == n){
      perm[d - 1] = i;
      // std::cout << "perm: ";
      // for (int j = 0; j < n; j++) {
      //   std::cout << perm[j] << " ";
      // }
      // std::cout << std::endl;
      elem.undo();
      return true;
    }

    perm[d - 1] = i;
    st.push(std::tuple<int, int>(-d, i));//d, i
    for (i = elem.GetPrev(elem.end()); i != elem.end(); i = elem.GetPrev(i)) {
      st.push(std::tuple<int, int>(d + 1, i));//d, i
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
