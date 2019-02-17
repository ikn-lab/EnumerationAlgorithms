#include<stack>
#include<iostream>
#include"next_permutation.hpp"

next_permutation::next_permutation(int n_): n(n_) {
  perm.resize(n);
  for (int i = 0; i < n; i++) perm[i] = i;
  elem.init(n);
  st.resize(n*n + 10);
  st.push(std::tuple<int, int, int>(1, 0, -1));//d, i, is_left
}


bool next_permutation::next(){
  while(not st.empty()){
    d = std::get<0>(st.top());
    i = std::get<1>(st.top());
    is_left = std::get<2>(st.top());
    st.pop();
    if(d < 0){
      if(is_left >= 0)elem.undo();
      continue;
    }
    if(is_left >= 0){
      if(i == is_left)i = elem.GetNext(i);
      elem.remove(is_left);
    }
    if(d == n + 1){
      elem.undo();
      return true;
    }
    if(i == elem.end())continue; 

    perm[d - 1] = i;
    st.push(std::tuple<int, int, int>(-d, 0, is_left));//d, i
    st.push(std::tuple<int, int, int>(d + 1, elem.begin(), i));//d, i
    st.push(std::tuple<int, int, int>(d, elem.GetNext(i), -1));//d, i
  }
  return false;
}
