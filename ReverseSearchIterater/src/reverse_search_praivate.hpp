#ifndef REVERSE_SEARCH_PRAIVATE_HPP
#define REVERSE_SEARCH_PRAIVATE_HPP

template<typename Input, typename Output>
Output* ReverseSearch<Input, Output>::
next(){
  if(current_sol == NULL){
    current_sol = new Output;
    tmp = new Output;
    *current_sol = InitialState[0];     
    return current_sol;
  }
  Output *c;
  for (;neighbor_counter < delta; neighbor_counter++) {
    c = Child(current_sol, neighbor_counter);
    if(c == NULL)break;
    *tmp = *c;
    delete c;
    if(*tmp != InitialState[tree_id]){
      //reverse traverse
      if(*Parent(tmp) == *current_sol){
        *current_sol = *tmp;
        neighbor_counter = 0;
        return current_sol;
      }
    }
  }
  //forward traverse
  if(*current_sol != InitialState[tree_id]){
    // counter++;
    *tmp = *current_sol;
    *current_sol = *Parent(current_sol);
    neighbor_counter = 0;
    c = Child(current_sol, neighbor_counter);
    if(c == NULL){
      std::cerr << "c is NULL. " << std::endl;
      abort();
    }
    while(*c != *tmp){
      neighbor_counter++;
      c = Child(current_sol, neighbor_counter);
      if(c == NULL){
        std::cerr << "c is NULL. " << std::endl;
        abort();
      }
    }
    neighbor_counter++;
    return next();
  }else{
    if(tree_id == InitialState.size() - 1){
      current_sol = tmp = NULL;
      neighbor_counter = tree_id = 0;
      return NULL;
    }
    neighbor_counter = 0;
    *current_sol = InitialState[++tree_id];
  }
  return current_sol;
}

template<typename Input, typename Output>
void ReverseSearch<Input, Output>::
playout(){
  if(current_sol == NULL)return;
  for (int i = tree_id; i < InitialState.size(); i++) {
    if(i == tree_id) *current_sol = InitialState[tree_id];
    while(*current_sol != InitialState[tree_id] or neighbor_counter < delta){
      for (;neighbor_counter < delta; neighbor_counter++) {
        Output* c = Child(current_sol, neighbor_counter);
        if(c == NULL)break;
        *tmp = *c;
        if(*tmp != InitialState[tree_id]){
          //reverse traverse
          if(*Parent(tmp) == *current_sol){
            *current_sol = *tmp;
            neighbor_counter = 0;
          }
        }
      }
    }
    //forward traverse
    if(*current_sol != InitialState[tree_id]){
      *tmp = *current_sol;
      *current_sol = *Parent(current_sol);
      neighbor_counter = 0;
      while(*Child(current_sol, neighbor_counter) != *tmp)neighbor_counter++;
    }
  }
  *current_sol = *tmp = NULL;
  neighbor_counter = tree_id = 0;
  return;
}

template<typename Input, typename Output>
ReverseSearch<Input, Output> ReverseSearch<Input, Output>::
CopyIterater(){
  ReverseSearch<Input, Output> res(input_data);
  res->current_sol = new Output;
  res->current_sol = *current_sol;
  res.tree_id = tree_id;
  res.neighbor_counter = neighbor_counter;
}
  
#endif
