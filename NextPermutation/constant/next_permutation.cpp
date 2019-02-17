#include<stack>
#include"next_permutation.hpp"

next_permutation::next_permutation(int n_): n(n_) {
  ordering.resize(n), next.resize(n);
  for (int i = 0; i < n; i++) ordering[i] = next[i] = i;
  st.resize(n*n + 10);
}

inline int next_permutation::minIndex(){
  for (int i = 0; i < next.size() - 1; i++) {
    if(next[i] <= next[i + 1])continue;
    return i;
  }
  return -1;
}


void next_permutation::Enumerate(FILE *output_file){
  //neighbor_counter
  int j = -1, back = 0, counter = 1;
  next[0] = 1;
  next[1] = 0;
  while(not (st.size() == 0 and j == n - 1)){
    std::swap(next[back], next[back + 1]);
    while(++j < n - 1){
      std::swap(next[j], next[j + 1]);
      back = minIndex();
      //reverse traverse
      if(back != j){
        std::swap(next[j], next[j + 1]);
      }else{
        st.push(j);
        std::swap(ordering[back], ordering[back + 1]);
        j = -1;
      }
    }
    //forward traverse
    if(not st.empty()){
      counter++;
      back = j = st.top();
      std::swap(ordering[st.top()], ordering[st.top() + 1]);
      st.pop();
    }
  }
  fprintf(output_file, "%d\n", counter);
  return;
}
