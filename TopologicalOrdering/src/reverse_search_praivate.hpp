#ifndef REVERSE_SEARCH_PRAIVATE_HPP
#define REVERSE_SEARCH_PRAIVATE_HPP

template<typename T>
void ReverseSearch<T>::
Search(FILE *output_file){
  int counter = 1;
  //neighbor_counter
  int j;
  T v, next;
  for (int i = 0; i < S.size(); i++) {
    v = S[i];
    j = -1;
    while(!(v == S[i] && j == delta)){
      while(j < delta){
        j++;
        next = Adj(v, j);
        if(next != init_val){
          //reverse traverse
          if(LocalSearch(next) == v){
            v = next;
            j = -1;
          }
        }
      }

      //forward traverse
      if(v != S[i]){
        counter++;
        T u = v;
        v = LocalSearch(v);
        j = 0;
        while(Adj(v, j) != u)j++;
        //std::cout << j << std::endl;
      }
    }
  }
  fprintf(output_file, "%d\n", counter);
  std::cout << counter << std::endl;
  return;
}
#endif
